

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Peripheral/CInput.h"
#include "Peripheral/CMouse.h"
#include "Peripheral/CKeyboard.h"
#include "Local.h"
#include "Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭

	@param hIsnt	[in] インスタンスハンドル
*/
//-----------------------------------------------------------------------------------
CInput::CInput( HINSTANCE hInst )
{
	HRESULT hr;

	m_pKeyboard	= NULL;
	m_pMouse	= NULL;

	//----------------------------------------------------------
	// DirectInputオブジェクト取得
	//----------------------------------------------------------
	hr = CoCreateInstance(
				CLSID_DirectInput8,
				NULL, 
				CLSCTX_ALL,
				IID_IDirectInput8,
				(void **)&m_pDirectInput );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, L"DirectInputオブジェクトの生成に失敗" );
		Log_TableLine( 1 );
		return;
	}

	//----------------------------------------------------------
	// DirectInputオブジェクト初期化
	//----------------------------------------------------------
	hr = m_pDirectInput->Initialize( hInst, DIRECTINPUT_VERSION );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, L"DirectInputオブジェクトの初期化に失敗" );
		Log_TableLine( 1 );
		return;
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CInput::~CInput()
{
	// 所有オブジェクトの解体
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pMouse );

	// DirectInputオブジェクト解放
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"解放" );

	if ( m_pDirectInput != NULL )
	{
		Uint32 Num = m_pDirectInput->Release();
		m_pDirectInput = NULL;

		Log_PrintCellKind( L"IDirectInput" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, L"参照数 %d", Num );
		Log_CellEnd();
	}

	Log_TableEnd();
	Log_TableLine( 2 );
}

//-----------------------------------------------------------------------------------
/**
	@brief デバイスの状態を更新
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CInput::Refresh( void )
{
	// マウス
	if ( m_pMouse != NULL )
	{
		m_pMouse->Refresh();
	}

	// キーボード
	if ( m_pKeyboard != NULL )
	{
		m_pKeyboard->Refresh();
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief キーボードオブジェクトを取得
	@author 葉迩倭

	@param ppKeyboard	[in/out] キーボードオブジェクトの格納先
*/
//-----------------------------------------------------------------------------------
Bool CInput::GetKeyboard( CKeyboard **ppKeyboard )
{
	if ( m_pKeyboard == NULL )
	{
		m_pKeyboard = new CKeyboard( ((CCore*)GetParent())->GetWindowHandle() );
		AddChild( m_pKeyboard );
		m_pKeyboard->Initialize();
		*ppKeyboard = m_pKeyboard;
	}

	m_pKeyboard->AddRef();

	return m_pKeyboard != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief マウスオブジェクトを取得
	@author 葉迩倭

	@param ppMouse	[in/out] マウスオブジェクトの格納先
*/
//-----------------------------------------------------------------------------------
Bool CInput::GetMouse( CMouse **ppMouse )
{
	if ( m_pMouse == NULL )
	{
		m_pMouse = new CMouse( ((CCore*)GetParent())->GetWindowHandle() );
		AddChild( m_pMouse );
		*ppMouse = m_pMouse;
	}

	m_pMouse->AddRef();

	return m_pMouse != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief IDirectInputオブジェクトへアクセス
	@author 葉迩倭

	@return IDirectInputオブジェクトのポインタ
*/
//-----------------------------------------------------------------------------------
IDirectInput8 *CInput::GetDirectInputPointer( void ) const
{
	return m_pDirectInput;
}

