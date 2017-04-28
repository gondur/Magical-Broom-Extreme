
#ifndef ___LUE_RENDER_H___
#define ___LUE_RENDER_H___


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
	@brief シーン開始宣言
	@author 葉迩倭

	@retval LTRUE	シーン開始成功
	@retval LFALSE	シーン開始失敗（シーンを完了してない場合や、上位のシーンから下位のシーンへ入ろうとした場合等）

	画面の描画処理を開始することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出した後<BR>
	でなければなりません。
*/
eLueBool LueRender_SceneStart( void );

/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を<BR>
	呼び出す前でなければなりません。
*/
void LueRender_SceneExit( void );

/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出す前<BR>
	でなければなりません。
*/
void LueRender_Printf( const char *pStr, ... );

/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出す前<BR>
	でなければなりません。
*/
void LueRender_ClsPrintf( void );

/**
	@brief 描画モード設定
	@author 葉迩倭

	@param DrawMode		[in] 描画モード

	画面への描画を行う際の描画方法を指定します<BR>
	不透明/半透明/加算/乗算などが指定可能です。
*/
void LueRender_SetDrawMode( eLueDrawMode DrawMode );

/**
	@brief テクスチャの設定
	@author 葉迩倭

	@param hTexture	[in] テクスチャハンドル

	レンダラーに対して描画に使用するテクスチャを設定します。<BR>
	INVALID_LUE_HANDLE を指定するとテクスチャを使わないようになります。<BR>
	また逆に INVALID_LUE_HANDLE を指定するまで設定したテクスチャが<BR>
	使われる続ける事になります。
	さらに LueSprite2D や LueFontSprite2D のように内部でテクスチャを<BR>
	自動的に切り替える関数を呼び出した後は変更されたままになっていますので<BR>
	アプリケーション側で使用する際には再度設定するようにして下さい。
*/
void LueRender_SetTexture( LUE_HANDLE hTexture );

/**
	@brief テクスチャの直接描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを直接画面にレンダリングします。<BR>
	簡易的に画面への描画を可能にするための関数ですので、<BR>
	大量に描画したい場合等、速度を優先する場合は LueSprite2D を<BR>
	使ってまとめて描画するようにして下さい。
*/
void LueRender_DrawSingleTexture( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief テクスチャのグレースケール描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成
	@param Src		[in] テクスチャの描画元矩形
	@param fRate	[in] グレースケール適用度(0.0～1.0)

	テクスチャをグレースケール化してレンダリングします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawGrayscale( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, float fRate );

/**
	@brief テクスチャのユニバーサルトランジション描画
	@author 葉迩倭

	@param HandleBase	[in] カラーテクスチャハンドル
	@param HandleRule	[in] ルールテクスチャハンドル
	@param Dst			[in] 描画先の矩形
	@param SrcBase		[in] カラーテクスチャの描画元矩形
	@param SrcRule		[in] ルールテクスチャの描画元矩形
	@param fRate		[in] 半透明適用度(0.0～1.0)

	ルール画像を用いてユニバーサルトランジションレンダリングします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawUniversalTransition( LUE_HANDLE HandleBase, LUE_HANDLE HandleRule, LueRect Dst, LueRect SrcBase, LueRect SrcRule, float fRate );

/**
	@brief テクスチャのぼかし描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを3x3ボックスフィルタリングをかけてぼかします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawBlur9Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief テクスチャのぼかし描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを4x4ボックスフィルタリングをかけてぼかします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawBlur16Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief テクスチャのぼかし描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを8x8ボックスフィルタリングをかけてぼかします。<BR>
	ピクセルシェーダー2.0をサポートしないビデオカードの場合<BR>
	LueRender_DrawBlur16Box()に置き換えられます。
*/
void LueRender_DrawBlur64Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );



//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_RENDER_H___
