

#ifndef ___SELENE__IMOUSE___
#define ___SELENE__IMOUSE___


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
		@brief マウスボタン状態定義
		@author 葉迩倭
	*/
	enum eMouseState
	{
		MOUSE_FREE,							///< マウスボタンは押されていない
		MOUSE_PULL,							///< マウスボタンは離された
		MOUSE_PUSH,							///< マウスボタンは押された
		MOUSE_HOLD,							///< マウスボタンは押されつづけている
	};

	/**
		@brief マウス管理インターフェイス
		@author 葉迩倭
	*/
	class IMouse
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
		virtual Uint32 Release( void )					= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )					= 0;

		/**
			@brief マウスのX座標取得
			@author 葉迩倭
			@return X座標

			マウスポインターのスクリーン座標上のX座標を取得します。
		*/
		virtual Sint32 GetPosX( void ) const			= 0;

		/**
			@brief マウスのY座標取得
			@author 葉迩倭
			@return Y座標

			マウスポインターのスクリーン座標上のY座標を取得します。
		*/
		virtual Sint32 GetPosY( void ) const			= 0;

		/**
			@brief マウスのホイール回転量取得
			@author 葉迩倭
			@return ホイール回転量

			マウスホイールの回転量を取得します。
		*/
		virtual Sint32 GetPosW( void ) const			= 0;

		/**
			@brief マウスのX移動量取得
			@author 葉迩倭
			@return X移動量

			マウスポインターのスクリーン移動量上のX移動量を取得します。
		*/
		virtual Sint32 GetMoveX( void ) const			= 0;

		/**
			@brief マウスのY移動量取得
			@author 葉迩倭
			@return Y移動量

			マウスポインターのスクリーン移動量上のY移動量を取得します。
		*/
		virtual Sint32 GetMoveY( void ) const			= 0;

		/**
			@brief マウスの左クリック状態取得
			@author 葉迩倭
			@retval false	左ボタンは押されていない
			@retval true	左ボタンは押されている

			マウスの左ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickL( void ) const			= 0;

		/**
			@brief マウスの右クリック状態取得
			@author 葉迩倭
			@retval false	右ボタンは押されていない
			@retval true	右ボタンは押されている

			マウスの右ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickR( void ) const			= 0;

		/**
			@brief マウスのホイールクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンは押されていない
			@retval true	ホイールボタンは押されている

			マウスのホイールボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickW( void ) const			= 0;

		/**
			@brief マウスの左ダブルクリック状態取得
			@author 葉迩倭
			@retval false	左ボタンはダブルクリックされていない
			@retval true	左ボタンはダブルクリックされた

			マウスの左ボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickL( void ) const		= 0;

		/**
			@brief マウスの右ダブルクリック状態取得
			@author 葉迩倭
			@retval false	右ボタンはダブルクリックされていない
			@retval true	右ボタンはダブルクリックされた

			マウスの右ボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickR( void ) const		= 0;

		/**
			@brief マウスのホイールダブルクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンはダブルクリックされていない
			@retval true	ホイールボタンはダブルクリックされた

			マウスのホイールボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickW( void ) const		= 0;

		/**
			@brief マウスの左ボタン状態取得
			@author 葉迩倭
			@return		左ボタンの状態

			マウスの左ボタンの詳細な情報を取得します。
		*/
		virtual eMouseState GetStateL( void ) const		= 0;

		/**
			@brief マウスの右ボタン状態取得
			@author 葉迩倭
			@return		右ボタンの状態

			マウスの右ボタンの詳細な情報を取得します。
		*/
		virtual eMouseState	GetStateR( void ) const		= 0;

		/**
			@brief マウスのホイールボタン状態取得
			@author 葉迩倭
			@return		ホイールボタンの状態

			マウスのホイールボタンの詳細な情報を取得します。
		*/
		virtual eMouseState	GetStateW( void ) const		= 0;
	};
}

#endif // ___SELENE__IMOUSE___

