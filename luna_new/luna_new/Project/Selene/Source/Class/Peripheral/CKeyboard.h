

#ifndef ___SELENE__CKEYBOARD___
#define ___SELENE__CKEYBOARD___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Object/CBaseObject.h"
#include "Interface/Peripheral/IKeyboard.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CInput;

	#define KEYBOARD_DATA_MAX		(256)
	#define KEYBOARD_BUFFER_MAX		(32)

	/**
		@brief �L�[�X�e�[�^�X��`
		@author �t���`
	*/
	enum eKeyState
	{
		KEY_STATE_FREE,						///< �L�[�̓t���[���
		KEY_STATE_PULL,						///< �L�[�͗����ꂽ�u��
		KEY_STATE_PUSH,						///< �L�[�͉����ꂽ�u��
		KEY_STATE_HOLD,						///< �L�[�͉����ꑱ���Ă���
	};

	/**
		@brief �L�[�{�[�h�f�[�^
		@author �t���`
	*/
	struct SKeyBoardData
	{
		char Key[KEYBOARD_DATA_MAX];		///< �{�^�����
	};

	/**
		@brief �L�[�{�[�h�Ǘ��N���X
		@author �t���`
	*/
	class CKeyboard : public CBaseObject, public IKeyboard
	{
		friend class CInput;

	protected:
		HWND					m_hWindow;							///< �E�B���h�E�n���h��
		IDirectInputDevice8		*m_pDevKeyboard;					///< �L�[�{�[�h�f�o�C�X
		SKeyBoardData			m_KeyboardData;						///< �L�[�{�[�h�f�[�^
		DIDEVICEOBJECTDATA		m_KeyBuffer[KEYBOARD_BUFFER_MAX];	///< �L�[�{�[�h�o�b�t�@
		Uint32					m_KeyBufferCount;					///< �L�[�{�[�h�o�b�t�@�J�E���g
		Uint32					m_KeyBufferMax;						///< �L�[�{�[�h�o�b�t�@�ő吔

	protected:
		CKeyboard( HWND hWnd );
		virtual ~CKeyboard();

	protected:
		virtual void Initialize( void );
		virtual void Refresh( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void ClearKeyBuffer( void );
		virtual eVirtualKeyCode GetKeyBuffer( void );
		virtual Bool GetKeyData( eVirtualKeyCode Key );
	};
}

#endif // ___SELENE__CKEYBOARD___

