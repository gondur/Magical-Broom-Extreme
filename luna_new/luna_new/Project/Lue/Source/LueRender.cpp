
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueRender.h"

//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern ICore *Lue_GetCore( void );
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern ITexture *LueTexture_Get( LUE_HANDLE Handle );
extern void LueTexture_SetRender( LUE_HANDLE Handle );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static Bool g_IsBeginScene = false;
static IPostEffect *g_pPostEffect = NULL;


//------------------------------------------------------------------------------------------------
/**
	@brief レンダラー処理の初期化
	@author 葉迩倭

	レンダラーに関する設定を初期化します。<BR>
	レンダリングターゲット用のサーフェイスや各種ポストエフェクト、
	深度バッファに関する処理はここで初期化されます。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueRender_Initialize( void )
{
	// ポストエフェクト用
	g_pPostEffect = Lue_GetRenderer()->CreatePostEffect();

	g_IsBeginScene = false;
}

//------------------------------------------------------------------------------------------------
/**
	@brief レンダラー処理の解放
	@author 葉迩倭

	レンダラーに関する設定を解放します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueRender_Finalize( void )
{
	SAFE_RELEASE( g_pPostEffect );
}


//------------------------------------------------------------------------------------------------
/**
	@brief シーン開始宣言
	@author 葉迩倭

	@param Scene	[in] 描画するシーンを設定<BR>
                         途中が抜けても問題はありませんが、必ず上から下の順で呼び出すようにして下さい。<BR>
							LSCENE_2D_BACKGROUND		2D：背景用（アルファ関係使用不可）<BR>
							LSCENE_3D_BLEND_DISABLE		3D：不透明（アルファ関係使用不可）<BR>
							LSCENE_3D_BLEND_ENABLE		3D：半透明（アルファ関係使用可能）<BR>
							LSCENE_2D_FOREGROUND		2D：前景＆2Dゲーム用（アルファ関係使用可能）

	@retval LTRUE	シーン開始成功
	@retval LFALSE	シーン開始失敗（シーンを完了してない場合や、上位のシーンから下位のシーンへ入ろうとした場合等）

	画面の描画処理を開始することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出した後<BR>
	でなければなりません。
*/
//------------------------------------------------------------------------------------------------
eLueBool LueRender_SceneStart( void )
{
	if ( g_IsBeginScene ) return LFALSE;

	//----------------------------------------------------------------------
	// ステート
	//----------------------------------------------------------------------
	Lue_GetRenderer()->SetCullType( CULL_NONE );
	Lue_GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	Lue_GetRenderer()->SetTextureFilterType( 0, TEXTURE_FILTER_DISABLE );
	Lue_GetRenderer()->SetTextureAddressType( 0, TEXTURE_ADDRESS_REPEAT );

	//----------------------------------------------------------------------
	// シーン開始
	//----------------------------------------------------------------------
	g_IsBeginScene = true;
	Lue_GetRenderer()->Begin();

	return LTRUE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を<BR>
	呼び出す前でなければなりません。
*/
//------------------------------------------------------------------------------------------------
void LueRender_SceneExit( void )
{
	if ( !g_IsBeginScene ) return;

	g_IsBeginScene = false;
	Lue_GetRenderer()->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出す前<BR>
	でなければなりません。
*/
//------------------------------------------------------------------------------------------------
void LueRender_Printf( const char *pStr, ... )
{
	char Temp[1024] = "";
	vsprintf_s( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

	wchar_t wTemp[1024] = L"";
	MBCStoWCS( Temp, wTemp );
	Lue_GetDevice()->Printf( wTemp );
}


//------------------------------------------------------------------------------------------------
/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出す前<BR>
	でなければなりません。
*/
//------------------------------------------------------------------------------------------------
void LueRender_ClsPrintf( void )
{
	Lue_GetDevice()->Cls();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画モード設定
	@author 葉迩倭

	@param DrawMode		[in] 描画モード

	画面への描画を行う際の描画方法を指定します<BR>
	不透明/半透明/加算/乗算などが指定可能です。
*/
//------------------------------------------------------------------------------------------------
void LueRender_SetDrawMode( eLueDrawMode DrawMode )
{
	eDrawType ModeTbl[] = {
		DRAW_TYPE_NORMAL,					///< 通常描画
		DRAW_TYPE_BLEND,					///< 半透明描画
		DRAW_TYPE_ADD,						///< 加算描画
		DRAW_TYPE_ADD_NOALPHA,				///< 加算描画（アルファ値無効）
		DRAW_TYPE_SUB,						///< 減算描画（アルファ値無効）
		DRAW_TYPE_SUB_NOALPHA,				///< 減算描画（アルファ値無効）
		DRAW_TYPE_MULTIPLE,					///< 乗算描画
		DRAW_TYPE_SCREEN,					///< スクリーン描画
	};

	Lue_GetRenderer()->SetDrawType( ModeTbl[DrawMode] );
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_SetTexture( LUE_HANDLE hTexture )
{
	LueTexture_SetRender( hTexture );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawSingleTexture( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->SingleTexture( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawGrayscale( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, float fRate )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Grayscale( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ), fRate );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawUniversalTransition( LUE_HANDLE HandleBase, LUE_HANDLE HandleRule, LueRect Dst, LueRect SrcBase, LueRect SrcRule, float fRate )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcBaseRc( SrcBase.x, SrcBase.y, SrcBase.w, SrcBase.h );
	CRect2D<Sint32> SrcRuleRc( SrcRule.x, SrcRule.y, SrcRule.w, SrcRule.h );
	g_pPostEffect->UniversalTransition( DstRc, fRate, SrcBaseRc, LueTexture_Get( HandleBase ), SrcRuleRc, LueTexture_Get( HandleRule ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawBlur9Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Blur9Box( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawBlur16Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Blur16Box( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawBlur64Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Blur64Box( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}


} // extern "C"

