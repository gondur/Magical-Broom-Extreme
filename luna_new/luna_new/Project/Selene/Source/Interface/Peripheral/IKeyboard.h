

#ifndef ___SELENE__IKEYBOARD___
#define ___SELENE__IKEYBOARD___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief 仮想キーコード
		@author 葉迩倭
	*/
	enum eVirtualKeyCode
	{
		SELENE_VK_ESCAPE          = 0x01,
		SELENE_VK_1               = 0x02,
		SELENE_VK_2               = 0x03,
		SELENE_VK_3               = 0x04,
		SELENE_VK_4               = 0x05,
		SELENE_VK_5               = 0x06,
		SELENE_VK_6               = 0x07,
		SELENE_VK_7               = 0x08,
		SELENE_VK_8               = 0x09,
		SELENE_VK_9               = 0x0A,
		SELENE_VK_0               = 0x0B,
		SELENE_VK_MINUS           = 0x0C,
		SELENE_VK_EQUALS          = 0x0D,
		SELENE_VK_BACK            = 0x0E,
		SELENE_VK_TAB             = 0x0F,
		SELENE_VK_Q               = 0x10,
		SELENE_VK_W               = 0x11,
		SELENE_VK_E               = 0x12,
		SELENE_VK_R               = 0x13,
		SELENE_VK_T               = 0x14,
		SELENE_VK_Y               = 0x15,
		SELENE_VK_U               = 0x16,
		SELENE_VK_I               = 0x17,
		SELENE_VK_O               = 0x18,
		SELENE_VK_P               = 0x19,
		SELENE_VK_LBRACKET        = 0x1A,
		SELENE_VK_RBRACKET        = 0x1B,
		SELENE_VK_RETURN          = 0x1C,
		SELENE_VK_LCONTROL        = 0x1D,
		SELENE_VK_A               = 0x1E,
		SELENE_VK_S               = 0x1F,
		SELENE_VK_D               = 0x20,
		SELENE_VK_F               = 0x21,
		SELENE_VK_G               = 0x22,
		SELENE_VK_H               = 0x23,
		SELENE_VK_J               = 0x24,
		SELENE_VK_K               = 0x25,
		SELENE_VK_L               = 0x26,
		SELENE_VK_SEMICOLON       = 0x27,
		SELENE_VK_APOSTROPHE      = 0x28,
		SELENE_VK_GRAVE           = 0x29,
		SELENE_VK_LSHIFT          = 0x2A,
		SELENE_VK_BACKSLASH       = 0x2B,
		SELENE_VK_Z               = 0x2C,
		SELENE_VK_X               = 0x2D,
		SELENE_VK_C               = 0x2E,
		SELENE_VK_V               = 0x2F,
		SELENE_VK_B               = 0x30,
		SELENE_VK_N               = 0x31,
		SELENE_VK_M               = 0x32,
		SELENE_VK_COMMA           = 0x33,
		SELENE_VK_PERIOD          = 0x34,
		SELENE_VK_SLASH           = 0x35,
		SELENE_VK_RSHIFT          = 0x36,
		SELENE_VK_MULTIPLY        = 0x37,
		SELENE_VK_LMENU           = 0x38,
		SELENE_VK_SPACE           = 0x39,
		SELENE_VK_CAPITAL         = 0x3A,
		SELENE_VK_F1              = 0x3B,
		SELENE_VK_F2              = 0x3C,
		SELENE_VK_F3              = 0x3D,
		SELENE_VK_F4              = 0x3E,
		SELENE_VK_F5              = 0x3F,
		SELENE_VK_F6              = 0x40,
		SELENE_VK_F7              = 0x41,
		SELENE_VK_F8              = 0x42,
		SELENE_VK_F9              = 0x43,
		SELENE_VK_F10             = 0x44,
		SELENE_VK_NUMLOCK         = 0x45,
		SELENE_VK_SCROLL          = 0x46,
		SELENE_VK_NUMPAD7         = 0x47,
		SELENE_VK_NUMPAD8         = 0x48,
		SELENE_VK_NUMPAD9         = 0x49,
		SELENE_VK_SUBTRACT        = 0x4A,
		SELENE_VK_NUMPAD4         = 0x4B,
		SELENE_VK_NUMPAD5         = 0x4C,
		SELENE_VK_NUMPAD6         = 0x4D,
		SELENE_VK_ADD             = 0x4E,
		SELENE_VK_NUMPAD1         = 0x4F,
		SELENE_VK_NUMPAD2         = 0x50,
		SELENE_VK_NUMPAD3         = 0x51,
		SELENE_VK_NUMPAD0         = 0x52,
		SELENE_VK_DECIMAL         = 0x53,
		SELENE_VK_OEM_102         = 0x56,
		SELENE_VK_F11             = 0x57,
		SELENE_VK_F12             = 0x58,
		SELENE_VK_KANA            = 0x70,
		SELENE_VK_ABNT_C1         = 0x73,
		SELENE_VK_CONVERT         = 0x79,
		SELENE_VK_NOCONVERT       = 0x7B,
		SELENE_VK_YEN             = 0x7D,
		SELENE_VK_ABNT_C2         = 0x7E,
		SELENE_VK_NUMPADEQUALS    = 0x8D,
		SELENE_VK_PREVTRACK       = 0x90,
		SELENE_VK_NUMPADENTER     = 0x9C,
		SELENE_VK_RCONTROL        = 0x9D,
		SELENE_VK_NUMPADCOMMA     = 0xB3,
		SELENE_VK_DIVIDE          = 0xB5,
		SELENE_VK_SYSRQ           = 0xB7,
		SELENE_VK_RMENU           = 0xB8,
		SELENE_VK_PAUSE           = 0xC5,
		SELENE_VK_HOME            = 0xC7,
		SELENE_VK_UP              = 0xC8,
		SELENE_VK_PRIOR           = 0xC9,
		SELENE_VK_LEFT            = 0xCB,
		SELENE_VK_RIGHT           = 0xCD,
		SELENE_VK_END             = 0xCF,
		SELENE_VK_DOWN            = 0xD0,
		SELENE_VK_NEXT            = 0xD1,
		SELENE_VK_INSERT          = 0xD2,
		SELENE_VK_DELETE          = 0xD3,
		SELENE_VK_LWIN            = 0xDB,
		SELENE_VK_RWIN            = 0xDC,

		SELENE_VK_NONE            = 0x00000000
	};

	/**
		@brief キーボード管理インターフェイス
		@author 葉迩倭
	*/
	class IKeyboard
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )						= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )						= 0;

		/**
			@brief キー入力バッファフラッシュ
			@author 葉迩倭

			キー入力バッファに蓄積した入力バッファをクリアします。
		*/
		virtual void ClearKeyBuffer( void )					= 0;

		/**
			@brief キー入力バッファからデータ取得
			@author 葉迩倭
			@return 入力されたキーのキーコード

			キー入力バッファに蓄積されたデータを取り出します。<BR>
			押されたキーを全て取り出す時はwhile()文等で処理してください。
		*/
		virtual eVirtualKeyCode GetKeyBuffer( void )		= 0;

		/**
			@brief キーが押されているかチェックする
			@author 葉迩倭
			@retval false	押されていない
			@retval true	押されている

			指定されたキーが現在押されているかチェックします。<BR>
			純粋にキーのON/OFFのみ取得できます。
		*/
		virtual Bool GetKeyData( eVirtualKeyCode Key )		= 0;
	};
}

#endif // ___SELENE__IKEYBOARD___

