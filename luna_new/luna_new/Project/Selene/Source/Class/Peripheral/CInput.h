

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
		@brief 入力デバイス管理クラス
		@author 葉迩倭
	*/
	class CInput : public CBaseObject
	{
		friend CKeyboard;

	protected:
		IDirectInput8 *m_pDirectInput;				///< DirectInputオブジェクト
		CKeyboard *m_pKeyboard;						///< キーボード
		CMouse *m_pMouse;							///< マウス

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

