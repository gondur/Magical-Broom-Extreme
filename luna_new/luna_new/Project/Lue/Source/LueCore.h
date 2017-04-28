
#ifndef ___LUE_CORE_H___
#define ___LUE_CORE_H___


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
	@brief Lueシステムの初期化を行います
	@author 葉迩倭

	@param pAppName		[in] アプリケーション名
	@param ScreenW		[in] 画面横幅
	@param ScreenH		[in] 画面縦幅
	@param FrameRate	[in] フレームレート
	@param IsWindowMode	[in] ウィンドウモードで起動するかどうか
	@param Type			[in] 使用するAPI（現在は LAPI_TYPE_DIRECTX9 固定）

	@retval LTRUE	初期化成功
	@retval LFALSE	初期化失敗

	Lueシステムの初期化処理を行います。<BR>
	この関数が完了した段階ですべてのLue系の関数を使うことが可能になります。
*/
eLueBool Lue_Initialize( const char *pAppName, unsigned int ScreenW, unsigned int ScreenH, eLueFrameRata FrameRate, eLueBool IsWindowMode, eLueAPIType Type );

/**
	@brief Lueシステムの終了
	@author 葉迩倭

	Lueシステムをすべて解放します。<BR>
	この関数が呼ばれた後にLue系の関数を呼び出すことは禁止されています。
*/
void Lue_Finalize( void );

/**
	@brief Lueシステムのメイン処理
	@author 葉迩倭

	@param IsActive	[in] LTRUE の時、フォーカスを失っても動作し続ける。

	@retval LTRUE	アプリケーション動作中
	@retval LFALSE	アプリケーション停止

	Lueシステムのメイン処理を行います。<BR>
	毎フレーム呼び出すようにしてください。<BR>
	また返り値がLFALSEのときは直ちにメインループから抜けて下さい。
*/
eLueBool Lue_Run( eLueBool IsActive );

/**
	@brief バージョン文字列取得
	@author 葉迩倭

	@param pStr		[out] バージョン文字列格納先
	@param Size		[in] pStrのバッファサイズ

	Lueのバージョンを文字列で取得します。<BR>
	この関数を呼び出すことで DLL のバージョンを取得することが可能です。
*/
void Lue_GetVersionString( char *pStr, unsigned int Size );

/**
	@brief バージョン番号取得
	@author 葉迩倭

	@return バージョン番号

	Lueのバージョンを数値で取得します。<BR>
	上位16Bitにメジャーバージョン、下位16Bitにマイナーバージョンが格納されています。
*/
unsigned int Lue_GetVersionNumber( void );

/**
	@brief OS起動からの時間取得
	@author 葉迩倭

	@return 1/1000秒単位の時間

	OSが起動してからの時間を取得します。<BR>
	32Bit変数なので約48日で1周して0に戻ってしまいます。
*/
unsigned int Lue_GetTime( void );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_CORE_H___
