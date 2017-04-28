
#ifndef ___LUE_SOUND_H___
#define ___LUE_SOUND_H___


//=============================================================================
// INCLUDE
//=============================================================================
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
	@brief ファイルからサウンドを読み込み、<BR>
	そのサウンドのハンドルを取得します。
	@author 葉迩倭

	@param pFileName	[in] ファイル名
	@param IsAllActive	[in] LTRUE にするとウィンドウが非アクティブでも停止しない

	@return 未使用のサウンドハンドル

	サウンドファイルを読み込み、そのサウンドの操作用のハンドルを取得します。<BR>
	取得したサウンドは不要になったら解放して下さい。
*/
LUE_HANDLE LueSound_CreateFromFile( const char *pFileName, eLueBool IsAllActive );

/**
	@brief サウンドを解放します。
	@author 葉迩倭

	@param Handle	[in] サウンドハンドル

	読み込んだサウンドをメモリから解放します。
*/
void LueSound_Release( LUE_HANDLE Handle );

/**
	@brief サウンドを再生開始
	@author 葉迩倭

	@param Handle	[in] サウンドハンドル

	読み込んだサウンドをメモリから解放します。
*/
void LueSound_Play( LUE_HANDLE Handle );

/**
	@brief サウンドをループ再生開始
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param LoopCount	[in] ループ回数<BR>無限ループの場合は SOUND_LOOP_INFINITY を指定。
	@param LoopSample	[in] ループ開始位置（サンプリング数で指定）

	サウンドのループ再生を行います。
*/
void LueSound_Loop( LUE_HANDLE Handle, unsigned int LoopCount, unsigned int LoopSample );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	再生中のサウンドを停止します。
*/
void LueSound_Stop( LUE_HANDLE Handle );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	再生中のサウンドを停止します。
*/
void LueSound_Pause( LUE_HANDLE Handle );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param fParam		[in] ボリューム値(+0～+100)

	再生中のサウンドを停止します。
*/
void LueSound_SetVolume( LUE_HANDLE Handle, float fParam );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param fParam		[in] パン値(-100～+100)

	再生中のサウンドを停止します。
*/
void LueSound_SetPan( LUE_HANDLE Handle, float fParam );

/**
	@brief サウンドが再生中であるかチェック
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	@retval true		再生中（一時停止含む）
	@retval false		停止中

	再生中のサウンドであるかどうかを調べます。
*/
eLueBool LueSound_IsPlay( LUE_HANDLE Handle );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_SOUND_H___
