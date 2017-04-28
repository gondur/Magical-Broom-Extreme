
#ifndef ___LUE_TEXTURE_H___
#define ___LUE_TEXTURE_H___


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
	@brief テクスチャ生成用コンフィグ設定
	@author 葉迩倭

	@param Color	[in] カラーキーの色（0で抜け設定なし

	テクスチャ生成用の設定を行います。
*/
void LueTexture_SetConfig( unsigned int Color );

/**
	@brief テクスチャの解放
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル

	テクスチャの解放を行います。
*/
void LueTexture_Release( LUE_HANDLE Handle );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param Width	[in] テクスチャの横幅
	@param Height	[in] テクスチャの縦幅

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	指定したサイズのテクスチャの生成を行います。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_Create( unsigned int Width, unsigned int Height );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	画像ファイルからテクスチャの生成を行います。<BR>
	サポートしている画像フォーマットは TGA/PNG/JPG/DDS/BMP です。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_CreateFromFile( const char *pFileName );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param pData	[in] テクスチャファイルの格納されたメモリのアドレス
	@param Size		[in] pDataのデータサイズ

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	メモリ内の画像ファイルからテクスチャの生成を行います。<BR>
	サポートしている画像フォーマットは TGA/PNG/JPG/DDS/BMP です。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_CreateFromMemory( void *pData, unsigned int Size );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param Width	[in] テクスチャの横幅
	@param Height	[in] テクスチャの縦幅

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	レンダリングターゲットとしてテクスチャを生成します。<BR>
	レンダリングターゲットとして生成されたテクスチャに対しては<BR>
	直接レンダリングする事が可能です。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_CreateRenderTarget( unsigned int Width, unsigned int Height );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_TEXTURE_H___
