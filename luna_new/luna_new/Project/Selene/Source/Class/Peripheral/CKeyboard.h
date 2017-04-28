

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
		@brief キーステータス定義
		@author 葉迩倭
	*/
	enum eKeyState
	{
		KEY_STATE_FREE,						///< キーはフリー状態
		KEY_STATE_PULL,						///< キーは離された瞬間
		KEY_STATE_PUSH,						///< キーは押された瞬間
		KEY_STATE_HOLD,						///< キーは押され続けている
	};

	/**
		@brief キーボードデータ
		@author 葉迩倭
	*/
	struct SKeyBoardData
	{
		char Key[KEYBOARD_DATA_MAX];		///< ボタン情報
	};

	/**
		@brief キーボード管理クラス
		@author 葉迩倭
	*/
	class CKeyboard : public CBaseObject, public IKeyboard
	{
		friend class CInput;

	protected:
		HWND					m_hWindow;							///< ウィンドウハンドル
		IDirectInputDevice8		*m_pDevKeyboard;					///< キーボードデバイス
		SKeyBoardData			m_KeyboardData;						///< キーボードデータ
		DIDEVICEOBJECTDATA		m_KeyBuffer[KEYBOARD_BUFFER_MAX];	///< キーボードバッファ
		Uint32					m_KeyBufferCount;					///< キーボードバッファカウント
		Uint32					m_KeyBufferMax;						///< キーボードバッファ最大数

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

