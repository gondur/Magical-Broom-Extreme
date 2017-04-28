

#ifndef ___SELENE__INPUT___
#define ___SELENE__INPUT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CMouse;
	class CKeyboard;

	/**
		@brief ���̓f�o�C�X�Ǘ��N���X
		@author �t���`
	*/
	class CInput : public CBaseObject
	{
		friend CKeyboard;

	protected:
		IDirectInput8 *m_pDirectInput;				///< DirectInput�I�u�W�F�N�g
		CKeyboard *m_pKeyboard;						///< �L�[�{�[�h
		CMouse *m_pMouse;							///< �}�E�X

	protected:
		virtual IDirectInput8 *GetDirectInputPointer( void ) const;

	public:
		CInput( HINSTANCE hInst );
		virtual ~CInput();

	public:
		virtual void Refresh( void );
		virtual Bool GetKeyboard( CKeyboard **pKeyboard );
		virtual Bool GetMouse( CMouse **pMouse );
	};
}

#endif // ___SELENE__INPUT___

