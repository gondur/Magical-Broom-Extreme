
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueFontSprite2D.h"

//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;

//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {

//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const Uint32 FONTSPRITE2D_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static IFontSprite2D *g_pFontSpr2DTbl[FONTSPRITE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
/**
	@brief フォントスプライト管理クラスの初期化
	@author 葉迩倭

	フォントスプライト管理クラスの初期化を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Initialize( void )
{
	for ( Uint32 i = 0; i < FONTSPRITE2D_MAX; i++ )
	{
		g_pFontSpr2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief フォントスプライト管理クラスの解放
	@author 葉迩倭

	フォントスプライト管理クラスの解放を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Finalize( void )
{
	for ( Uint32 i = 0; i < FONTSPRITE2D_MAX; i++ )
	{
		if ( g_pFontSpr2DTbl[i] != NULL )
		{
			g_pFontSpr2DTbl[i]->Release();
			g_pFontSpr2DTbl[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief 未使用フォントスプライトの検索
	@author 葉迩倭

	@return 未使用のフォントスプライトハンドル

	未使用のフォントスプライトオブジェクトの検索をします。<BR>
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueFontSprite2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < FONTSPRITE2D_MAX; i++ )
	{
		if ( g_pFontSpr2DTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}



//------------------------------------------------------------------------------------------------
/**
	@brief フォントスプライトの解放
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル

	フォントスプライトの解放を行います。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;

	if ( g_pFontSpr2DTbl[Handle] != NULL )
	{
		g_pFontSpr2DTbl[Handle]->Release();
		g_pFontSpr2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueFontSprite2D_Create( const char *pBuffer, unsigned int FontMax, const char *pFontFace, unsigned int FontSize, eLueBool IsItalic, eLueBool IsBold, eLueBool IsAntialias )
{
	LUE_HANDLE Handle = LueFontSprite2D_SearchFreeHandle();
	if ( Handle >= FONTSPRITE2D_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp[64] = L"";
	MBCStoWCS( pFontFace, wTemp );
	wchar_t wBuffer[4096] = L"";
	MBCStoWCS( pBuffer, wBuffer );

	g_pFontSpr2DTbl[Handle] = Lue_GetRenderer()->CreateFontSprite2D( wBuffer, FontMax, wTemp, FontSize, IsItalic != LFALSE, IsBold != LFALSE, IsAntialias != LFALSE );
	if ( g_pFontSpr2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueFontSprite2D_CreateFromFile( const char *pFileName, const char *pExt, unsigned int FontMax )
{
	LUE_HANDLE Handle = LueFontSprite2D_SearchFreeHandle();
	if ( Handle >= FONTSPRITE2D_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp0[MAX_PATH] = L"";
	wchar_t wTemp1[32] = L"";
	MBCStoWCS( pFileName, wTemp0 );
	MBCStoWCS( pExt, wTemp1 );
	g_pFontSpr2DTbl[Handle] = Lue_GetRenderer()->CreateFontSprite2DFromFile( wTemp0, wTemp1, FontMax );
	if ( g_pFontSpr2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでフォントスプライトの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	g_pFontSpr2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでフォントスプライトの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	g_pFontSpr2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでリクエストされたフォントスプライトデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	g_pFontSpr2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param x		[in] 描画X値
	@param y		[in] 描画Y値
	@param Color	[in] 頂点色

	フォントスプライトを使った等幅フォントでの文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_DrawString( LUE_HANDLE Handle, const char *pStr, int x, int y, unsigned int Color )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	g_pFontSpr2DTbl[Handle]->DrawString( Temp, CPoint2D<Sint32>(x, y), Color );
}


//------------------------------------------------------------------------------------------------
/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param x		[in] 描画X値
	@param y		[in] 描画Y値
	@param Color	[in] 頂点色

	フォントスプライトを使ったプロポーショナルフォントでの文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_DrawStringP( LUE_HANDLE Handle, const char *pStr, int x, int y, unsigned int Color )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	g_pFontSpr2DTbl[Handle]->DrawStringP( Temp, CPoint2D<Sint32>(x, y), Color );
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
int LueFontSprite2D_DrawChara( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return 0;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return 0;

	wchar_t Temp[8] = L"";
	MBCStoWCS( pStr, Temp );
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	return g_pFontSpr2DTbl[Handle]->DrawChara( Temp[0], DstRc, Color );
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
int LueFontSprite2D_DrawCharaRotate( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color, int Angle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return 0;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return 0;

	wchar_t Temp[8] = L"";
	MBCStoWCS( pStr, Temp );
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	return g_pFontSpr2DTbl[Handle]->DrawCharaRotate( Temp[0], DstRc, Color, Angle );
}


//------------------------------------------------------------------------------------------------
/**
	@brief 文字列描画位置取得
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param x		[in] 描画X値
	@param y		[in] 描画Y値

	フォントスプライトを使った等幅フォントでの文字列描画を行った後の。<BR>
	最終的な位置を取得します。<BR>
	続けて文字列を描画する場合や、文字列の高さや幅を取得するのに有効です。
*/
//------------------------------------------------------------------------------------------------
LuePoint LueFontSprite2D_GetStringLastPos( LUE_HANDLE Handle, const char *pStr, int x, int y )
{
	LuePoint Pt = { 0, 0 };
	if ( Handle >= FONTSPRITE2D_MAX ) return Pt;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return Pt;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	CPoint2D<Sint32> Ret = g_pFontSpr2DTbl[Handle]->GetStringLastPos( Temp, CPoint2D<Sint32>(x, y) );
	Pt.x = Ret.x;
	Pt.y = Ret.y;

	return Pt;
}


//------------------------------------------------------------------------------------------------
/**
	@brief 文字列描画位置取得
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param x		[in] 描画X値
	@param y		[in] 描画Y値

	フォントスプライトを使ったプロポーショナルフォントでの文字列描画を行った後の。<BR>
	最終的な位置を取得します。<BR>
	続けて文字列を描画する場合や、文字列の高さや幅を取得するのに有効です。
*/
//------------------------------------------------------------------------------------------------
LuePoint LueFontSprite2D_GetStringLastPosP( LUE_HANDLE Handle, const char *pStr, int x, int y )
{
	LuePoint Pt = { 0, 0 };
	if ( Handle >= FONTSPRITE2D_MAX ) return Pt;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return Pt;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	CPoint2D<Sint32> Ret = g_pFontSpr2DTbl[Handle]->GetStringLastPosP( Temp, CPoint2D<Sint32>(x, y) );
	Pt.x = Ret.x;
	Pt.y = Ret.y;

	return Pt;
}


} // extern "C"

