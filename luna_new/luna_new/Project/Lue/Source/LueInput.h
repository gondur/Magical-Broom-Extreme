
#ifndef ___LUE_INPUT_H___
#define ___LUE_INPUT_H___

#include "LueBase.h"

//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//=============================================================================
// PROTOTYPE
//=============================================================================
/**
	@brief キーボッドの入力バッファをクリア
	@author 葉迩倭

	キーボードの情報が格納されている入力バッファをクリアします。
*/
void LueInput_ClearKeyBuffer( void );

/**
	@brief キーボード入力バッファの取得
	@author 葉迩倭

	@retval 0		入力なし
	@return 0以外	押されたキーのキーコード

	キーボード入力バッファ内のデータを１つづつ取り出します。<BR>
	バッファが空になった時点で LUE_VK_NONE が返ります。
*/
eLueVirtualKey LueInput_GetKeyBuffer( void );

/**
	@brief キーボード情報取得
	@author 葉迩倭

	@param Key	[in] 調べたいキーのキーコード

	@retval LTRUE	押されている
	@retval LFALSE	押されていない
*/
eLueBool LueInput_GetKeyData( eLueVirtualKey Key );

/**
	@brief マウス情報取得
	@author 葉迩倭

	@return マウスデータ

	マウスの情報を取得します。
*/
LueMouseData LueInput_GetMouseData( void );

/**
	@brief ジョイスティック情報取得
	@author 葉迩倭

	@param No	[in] ジョイスティック番号

	@return ジョイスティックデータ

	指定接続番号のジョイスティックのデータを取得します。<BR>
	指定接続番号のジョイスティックが接続されていない場合は<BR>
	IsActive メンバ変数に LFALSE が設定されます。
*/
LueJoyStickData LueInput_GetJoystickData( int No );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_INPUT_H___
