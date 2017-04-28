

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
	@brief �R���X�g���N�^
	@author �t���`

	@param hIsnt	[in] �C���X�^���X�n���h��
*/
//-----------------------------------------------------------------------------------
CInput::CInput( HINSTANCE hInst )
{
	HRESULT hr;

	m_pKeyboard	= NULL;
	m_pMouse	= NULL;

	//----------------------------------------------------------
	// DirectInput�I�u�W�F�N�g�擾
	//----------------------------------------------------------
	hr = CoCreateInstance(
				CLSID_DirectInput8,
				NULL, 
				CLSCTX_ALL,
				IID_IDirectInput8,
				(void **)&m_pDirectInput );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, L"DirectInput�I�u�W�F�N�g�̐����Ɏ��s" );
		Log_TableLine( 1 );
		return;
	}

	//----------------------------------------------------------
	// DirectInput�I�u�W�F�N�g������
	//----------------------------------------------------------
	hr = m_pDirectInput->Initialize( hInst, DIRECTINPUT_VERSION );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, L"DirectInput�I�u�W�F�N�g�̏������Ɏ��s" );
		Log_TableLine( 1 );
		return;
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CInput::~CInput()
{
	// ���L�I�u�W�F�N�g�̉��
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pMouse );

	// DirectInput�I�u�W�F�N�g���
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"���" );

	if ( m_pDirectInput != NULL )
	{
		Uint32 Num = m_pDirectInput->Release();
		m_pDirectInput = NULL;

		Log_PrintCellKind( L"IDirectInput" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, L"�Q�Ɛ� %d", Num );
		Log_CellEnd();
	}

	Log_TableEnd();
	Log_TableLine( 2 );
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�o�C�X�̏�Ԃ��X�V
	@author �t���`
*/
//-----------------------------------------------------------------------------------
void CInput::Refresh( void )
{
	// �}�E�X
	if ( m_pMouse != NULL )
	{
		m_pMouse->Refresh();
	}

	// �L�[�{�[�h
	if ( m_pKeyboard != NULL )
	{
		m_pKeyboard->Refresh();
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief �L�[�{�[�h�I�u�W�F�N�g���擾
	@author �t���`

	@param ppKeyboard	[in/out] �L�[�{�[�h�I�u�W�F�N�g�̊i�[��
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
	@brief �}�E�X�I�u�W�F�N�g���擾
	@author �t���`

	@param ppMouse	[in/out] �}�E�X�I�u�W�F�N�g�̊i�[��
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
	@brief IDirectInput�I�u�W�F�N�g�փA�N�Z�X
	@author �t���`

	@return IDirectInput�I�u�W�F�N�g�̃|�C���^
*/
//-----------------------------------------------------------------------------------
IDirectInput8 *CInput::GetDirectInputPointer( void ) const
{
	return m_pDirectInput;
}

