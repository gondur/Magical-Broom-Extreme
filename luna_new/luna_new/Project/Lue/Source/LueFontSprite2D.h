
#ifndef ___LUE_FONTSPRITE2D_H___
#define ___LUE_FONTSPRITE2D_H___


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
	@brief フォントスプライトの解放
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル

	フォントスプライトの解放を行います。
*/
void LueFontSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief フォントスプライト生成
	@author 葉迩倭

	@param pBuffer		[in] テクスチャ作成用文字列
	@param FontMax		[in] フォントスプライト数
	@param pFontFace	[in] フォント書体
	@param FontSize		[in] フォントサイズ（ピクセル
	@param IsItalic		[in] 斜体のON/OFF
	@param IsBold		[in] 太字のON/OFF
	@param IsAntialias	[in] アンチエイリアスのON/OFF

	@return フォントスプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	文字列からフォントスプライトを生成します。<BR>
	pBuffer で指定された文字列をその他引数に応じてテクスチャに展開します。<BR>
	FontMaxは最大描画可能個数であり、シザリングなどで内部バッファが<BR>
	リクエストより多く使われることもありますので、溢れない十分な大きさを指定してください。
*/
LUE_HANDLE LueFontSprite2D_Create( const char *pBuffer, unsigned int FontMax, const char *pFontFace, unsigned int FontSize, eLueBool IsItalic, eLueBool IsBold, eLueBool IsAntialias );

/**
	@brief フォントスプライト生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャ作成用文字列
	@param pExt			[in] テクスチャ拡張子（Font_00.tgaの場合は"tga"）
	@param FontMax		[in] フォントスプライト数

	@return フォントスプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	事前に作成されたフォントデータからフォントスプライトを生成します。<BR>
	FontMaxは最大描画可能個数であり、シザリングなどで内部バッファが<BR>
	リクエストより多く使われることもありますので、溢れない十分な大きさを指定してください。
*/
LUE_HANDLE LueFontSprite2D_CreateFromFile( const char *pFileName, const char *pExt, unsigned int FontMax );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでフォントスプライトの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LueFontSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでフォントスプライトの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LueFontSprite2D_End( LUE_HANDLE Handle );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでリクエストされたフォントスプライトデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LueFontSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値
	@param Color	[in] 頂点色

	フォントスプライトを使った等幅フォントでの文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
void LueFontSprite2D_DrawString( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値
	@param Color	[in] 頂点色

	フォントスプライトを使ったプロポーショナルフォントでの文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
void LueFontSprite2D_DrawStringP( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief 文字描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字
	@param Dst		[in] 描画矩形
	@param Color	[in] 頂点色

	フォントスプライトを使った文字描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
int LueFontSprite2D_DrawChara( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color );

/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Dst		[in] 描画矩形
	@param Color	[in] 頂点色
	@param Angle	[in] 1周65536とした回転角度

	フォントスプライトを使った回転付き文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
int LueFontSprite2D_DrawCharaRotate( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color, int Angle );

/**
	@brief 文字列描画位置取得
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値

	フォントスプライトを使った等幅フォントでの文字列描画を行った後の。<BR>
	最終的な位置を取得します。<BR>
	続けて文字列を描画する場合や、文字列の高さや幅を取得するのに有効です。
*/
LuePoint LueFontSprite2D_GetStringLastPos( LUE_HANDLE Handle, const char *pStr, int Px, int Py );

/**
	@brief 文字列描画位置取得
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値

	フォントスプライトを使ったプロポーショナルフォントでの文字列描画を行った後の。<BR>
	最終的な位置を取得します。<BR>
	続けて文字列を描画する場合や、文字列の高さや幅を取得するのに有効です。
*/
LuePoint LueFontSprite2D_GetStringLastPosP( LUE_HANDLE Handle, const char *pStr, int Px, int Py );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_FONTSPRITE2D_H___
