

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
	sizeof(DIDATAFORMAT),			// ���̍\���̂̃T�C�Y
	sizeof(DIOBJECTDATAFORMAT),		// �I�u�W�F�N�g �f�[�^�`���̃T�C�Y
	DIDF_RELAXIS,					// ��Ύ��̍��W
	sizeof(SKeyBoardData),			// �f�o�C�X �f�[�^�̃T�C�Y
	KEYBOARD_DATA_MAX,				// �I�u�W�F�N�g��
	g_KeyboardDataFormat,			// �f�[�^�ʒu
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
	// �f�o�C�X���
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"���" );

	if ( m_pDevKeyboard != NULL )
	{
		m_pDevKeyboard->Unacquire();
		Uint32 Num = m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;

		Log_PrintCellKind( L"IDirectInputDevice<BR>Keyboard" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, L"�Q�Ɛ� %d", Num );
		Log_CellEnd();
	}

	Log_TableEnd();
	Log_TableLine( 2 );
}

void CKeyboard::Initialize( void )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"������" );
	Log_PrintCellKind( L"�L�[�{�[�h" );
	Log_CellBegin( 0 );

	try
	{
		HRESULT hr;

		//----------------------------------------------------------
		// �f�o�C�X������
		//----------------------------------------------------------
		hr = ((CInput*)GetParent())->GetDirectInputPointer()->CreateDevice( GUID_SysKeyboard, &m_pDevKeyboard, NULL );
		if FAILED( hr )
		{
			throw L"�L�[�{�[�h�f�o�C�X�̐����Ɏ��s";
		}

		//----------------------------------------------------------
		// �f�[�^�t�H�[�}�b�g�̐ݒ�
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
			throw L"�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s";
		}

		//----------------------------------------------------------
		// �������x���̐ݒ�
		//----------------------------------------------------------
		hr = m_pDevKeyboard->SetCooperativeLevel( m_hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
		if FAILED( hr )
		{
			throw L"�L�[�{�[�h�̋������x���̐ݒ�Ɏ��s";
		}

		//----------------------------------------------------------
		// �o�b�t�@�E�T�C�Y��ݒ�
		//----------------------------------------------------------
		DIPROPDWORD diprop = { sizeof(DIPROPDWORD), sizeof(DIPROPHEADER) }; 
		diprop.diph.dwObj	= 0;
		diprop.diph.dwHow	= DIPH_DEVICE;
		diprop.dwData		= KEYBOARD_BUFFER_MAX;

		hr = m_pDevKeyboard->SetProperty( DIPROP_BUFFERSIZE, &diprop.diph );
		if FAILED( hr )
		{
			throw L"�L�[�{�[�h�̃v���p�e�B�̐ݒ�Ɏ��s";
		}

		//----------------------------------------------------------
		// �f�o�C�X���擾
		//----------------------------------------------------------
		DIDEVCAPS DiCaps = { sizeof(DIDEVCAPS) };
		m_pDevKeyboard->GetCapabilities( &DiCaps );

		Log_PrintLine( 0x000000, L"%d�L�[ �L�[�{�[�h", DiCaps.dwButtons );

		//----------------------------------------------------------
		// ���͐���J�n
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
	�L�[�{�[�h�̃f�[�^�̍X�V���s���܂�

*/
//-----------------------------------------------------------------------------------
void CKeyboard::Refresh( void )
{
	if ( m_pDevKeyboard != NULL )
	{
		HRESULT hr;

		//--------------------------------------------------------
		// �L�[�o�b�t�@
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
				// �o�b�t�@���I�[�o�[�t���[����
			}
		}

		//--------------------------------------------------------
		// �L�[�{�[�h��Ԏ擾
		//--------------------------------------------------------
		hr = m_pDevKeyboard->GetDeviceState( KEYBOARD_DATA_MAX, m_KeyboardData.Key );
		if FAILED( hr )
		{
			// �f�o�C�X�ăA�N�Z�X
			m_pDevKeyboard->Acquire();
			MemoryClear( m_KeyboardData.Key, sizeof(m_KeyboardData.Key) );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	�L�[�{�[�h�̃f�[�^�̍X�V���s���܂�

	@param Key		[in] ���z�L�[�R�[�h

	@retval true	�L�[�͉�����Ă���
	@retval false	�L�[�͉�����Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool CKeyboard::GetKeyData( eVirtualKeyCode Key )
{
	return m_KeyboardData.Key[Key] < 0;
}

//-----------------------------------------------------------------------------------
/**
	�L�[�{�[�h�̃o�b�t�@�����O�f�[�^���t���b�V�����܂�

*/
//-----------------------------------------------------------------------------------
void CKeyboard::ClearKeyBuffer( void )
{
	m_KeyBufferMax = 0;
	m_KeyBufferCount = 0;
}

//-----------------------------------------------------------------------------------
/**
	�L�[�{�[�h�̃o�b�t�@�����O�f�[�^���擾���܂�

	@param pKey		[out] �L�[�f�[�^���󂯎�邽�߂̕ϐ��ւ̃|�C���^

	@retval true	�o�b�t�@���Ƀf�[�^���c���Ă���
	@retval false	�o�b�t�@���̃f�[�^�͋�
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


