

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Peripheral/CKeyboard.h"
#include "Peripheral/CInput.h"
#include "Local.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// SKeyBoardData
//-----------------------------------------------------------------------------------
static DIOBJECTDATAFORMAT g_KeyboardDataFormat[KEYBOARD_DATA_MAX];

static DIDATAFORMAT g_DIKeyboardDataFormat = { 
	sizeof(DIDATAFORMAT),			// この構造体のサイズ
	sizeof(DIOBJECTDATAFORMAT),		// オブジェクト データ形式のサイズ
	DIDF_RELAXIS,					// 絶対軸の座標
	sizeof(SKeyBoardData),			// デバイス データのサイズ
	KEYBOARD_DATA_MAX,				// オブジェクト数
	g_KeyboardDataFormat,			// データ位置
};


CKeyboard::CKeyboard( HWND hWnd )
{
	m_hWindow			= hWnd;

	m_pDevKeyboard		= NULL;
	m_KeyBufferCount	= 0;
	m_KeyBufferMax		= 0;

	MemoryClear( &m_KeyboardData, sizeof(m_KeyboardData) );
	MemoryClear( m_KeyBuffer, sizeof(m_KeyBuffer) );
}

CKeyboard::~CKeyboard()
{
	// デバイス解放
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"解放" );

	if ( m_pDevKeyboard != NULL )
	{
		m_pDevKeyboard->Unacquire();
		Uint32 Num = m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;

		Log_PrintCellKind( L"IDirectInputDevice<BR>Keyboard" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, L"参照数 %d", Num );
		Log_CellEnd();
	}

	Log_TableEnd();
	Log_TableLine( 2 );
}

void CKeyboard::Initialize( void )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"初期化" );
	Log_PrintCellKind( L"キーボード" );
	Log_CellBegin( 0 );

	try
	{
		HRESULT hr;

		//----------------------------------------------------------
		// デバイス初期化
		//----------------------------------------------------------
		hr = ((CInput*)GetParent())->GetDirectInputPointer()->CreateDevice( GUID_SysKeyboard, &m_pDevKeyboard, NULL );
		if FAILED( hr )
		{
			throw L"キーボードデバイスの生成に失敗";
		}

		//----------------------------------------------------------
		// データフォーマットの設定
		//----------------------------------------------------------
		for ( Sint32 i = 0; i < KEYBOARD_DATA_MAX; i ++ )
		{
			g_DIKeyboardDataFormat.rgodf[i].pguid	= &GUID_Key;
			g_DIKeyboardDataFormat.rgodf[i].dwOfs	= FIELD_OFFSET(SKeyBoardData, Key[i]);
			g_DIKeyboardDataFormat.rgodf[i].dwType	= 0x80000000 | DIDFT_BUTTON | DIDFT_ENUMCOLLECTION(i);
			g_DIKeyboardDataFormat.rgodf[i].dwFlags	= 0;
		}

		hr = m_pDevKeyboard->SetDataFormat( &g_DIKeyboardDataFormat );
		if FAILED( hr )
		{
			throw L"キーボードのデータフォーマットの設定に失敗";
		}

		//----------------------------------------------------------
		// 協調レベルの設定
		//----------------------------------------------------------
		hr = m_pDevKeyboard->SetCooperativeLevel( m_hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
		if FAILED( hr )
		{
			throw L"キーボードの協調レベルの設定に失敗";
		}

		//----------------------------------------------------------
		// バッファ・サイズを設定
		//----------------------------------------------------------
		DIPROPDWORD diprop = { sizeof(DIPROPDWORD), sizeof(DIPROPHEADER) }; 
		diprop.diph.dwObj	= 0;
		diprop.diph.dwHow	= DIPH_DEVICE;
		diprop.dwData		= KEYBOARD_BUFFER_MAX;

		hr = m_pDevKeyboard->SetProperty( DIPROP_BUFFERSIZE, &diprop.diph );
		if FAILED( hr )
		{
			throw L"キーボードのプロパティの設定に失敗";
		}

		//----------------------------------------------------------
		// デバイス情報取得
		//----------------------------------------------------------
		DIDEVCAPS DiCaps = { sizeof(DIDEVCAPS) };
		m_pDevKeyboard->GetCapabilities( &DiCaps );

		Log_PrintLine( 0x000000, L"%dキー キーボード", DiCaps.dwButtons );

		//----------------------------------------------------------
		// 入力制御開始
		//----------------------------------------------------------
		m_pDevKeyboard->Acquire();
	}
	catch ( const wchar_t *pErrMsg )
	{
		Log_PrintLine( 0xFF0000, pErrMsg );
		SAFE_RELEASE( m_pDevKeyboard );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
	キーボードのデータの更新を行います

*/
//-----------------------------------------------------------------------------------
void CKeyboard::Refresh( void )
{
	if ( m_pDevKeyboard != NULL )
	{
		HRESULT hr;

		//--------------------------------------------------------
		// キーバッファ
		//--------------------------------------------------------
		m_KeyBufferMax = KEYBOARD_BUFFER_MAX;
		m_KeyBufferCount = 0;
		hr = m_pDevKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), m_KeyBuffer, &m_KeyBufferMax, 0 );
		if FAILED( hr )
		{
			m_pDevKeyboard->Acquire();
		}
		else
		{
			if ( hr == DI_BUFFEROVERFLOW )
			{
				// バッファがオーバーフローした
			}
		}

		//--------------------------------------------------------
		// キーボード状態取得
		//--------------------------------------------------------
		hr = m_pDevKeyboard->GetDeviceState( KEYBOARD_DATA_MAX, m_KeyboardData.Key );
		if FAILED( hr )
		{
			// デバイス再アクセス
			m_pDevKeyboard->Acquire();
			MemoryClear( m_KeyboardData.Key, sizeof(m_KeyboardData.Key) );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	キーボードのデータの更新を行います

	@param Key		[in] 仮想キーコード

	@retval true	キーは押されている
	@retval false	キーは押されていない
*/
//-----------------------------------------------------------------------------------
Bool CKeyboard::GetKeyData( eVirtualKeyCode Key )
{
	return m_KeyboardData.Key[Key] < 0;
}

//-----------------------------------------------------------------------------------
/**
	キーボードのバッファリングデータをフラッシュします

*/
//-----------------------------------------------------------------------------------
void CKeyboard::ClearKeyBuffer( void )
{
	m_KeyBufferMax = 0;
	m_KeyBufferCount = 0;
}

//-----------------------------------------------------------------------------------
/**
	キーボードのバッファリングデータを取得します

	@param pKey		[out] キーデータを受け取るための変数へのポインタ

	@retval true	バッファ内にデータが残っている
	@retval false	バッファ内のデータは空
*/
//-----------------------------------------------------------------------------------
eVirtualKeyCode CKeyboard::GetKeyBuffer( void )
{
	Uint32 Key = 0x00;

	if ( m_KeyBufferCount < m_KeyBufferMax )
	{
		if ( m_KeyBuffer[m_KeyBufferCount].dwData < 0 )
		{
			Key = m_KeyBuffer[m_KeyBufferCount].dwOfs;
		}
		
		m_KeyBufferCount++;
	}

	return (eVirtualKeyCode)Key;
}


