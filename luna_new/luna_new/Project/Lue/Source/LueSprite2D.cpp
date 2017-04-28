
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueSprite2D.h"

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
extern ITexture *LueTexture_Get( LUE_HANDLE Handle );


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const unsigned int SPRITE2D_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ISprite2D *g_pSpr2DTbl[SPRITE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );


//------------------------------------------------------------------------------------------------
/**
	@brief スプライト管理クラスの初期化
	@author 葉迩倭

	スプライト管理クラスの初期化を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Initialize( void )
{
	for ( Uint32 i = 0; i < SPRITE2D_MAX; i++ )
	{
		g_pSpr2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief スプライト管理クラスの解放
	@author 葉迩倭

	スプライト管理クラスの解放を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Finalize( void )
{
	for ( Uint32 i = 0; i < SPRITE2D_MAX; i++ )
	{
		if ( g_pSpr2DTbl[i] != NULL )
		{
			g_pSpr2DTbl[i]->Release();
			g_pSpr2DTbl[i] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief 未使用スプライトの検索
	@author 葉迩倭

	@return 未使用のスプライトハンドル

	未使用のスプライトオブジェクトの検索をします。<BR>
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueSprite2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < SPRITE2D_MAX; i++ )
	{
		if ( g_pSpr2DTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief スプライトの解放
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル

	スプライトの解放を行います。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;

	if ( g_pSpr2DTbl[Handle] != NULL )
	{
		g_pSpr2DTbl[Handle]->Release();
		g_pSpr2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief スプライト生成
	@author 葉迩倭

	@param PrimitiveMax		[in] プリミティブ最大数
	@param hTexture			[in] 接続するテクスチャのハンドル

	@return スプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	スプライトオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズであり、<BR>
	シザリング等を行うとリクエストした頂点数よりも多く消費されるので<BR>
	目安程度として溢れない十分な大きさを指定するようにしてください。<BR>
	また hTeture で指定したテクスチャを使って描画されます。
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueSprite2D_Create( unsigned int PrimitiveMax, LUE_HANDLE hTexture )
{
	LUE_HANDLE Handle = LueSprite2D_SearchFreeHandle();
	if ( Handle >= SPRITE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pSpr2DTbl[Handle] = Lue_GetRenderer()->CreateSprite2D( PrimitiveMax, LueTexture_Get( hTexture ) );
	if ( g_pSpr2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでリクエストされたプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	g_pSpr2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	g_pSpr2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	g_pSpr2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Dst		[in] 描画先矩形
	@param Src		[in] テクスチャUV矩形
	@param Color	[in] 頂点色

	スプライトを使った矩形の描画を行います。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_DrawSquare( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pSpr2DTbl[Handle]->DrawSquare( DstRc, SrcRc, Color );
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Dst		[in] 描画先矩形
	@param Src		[in] テクスチャUV矩形
	@param Color	[in] 頂点色
	@param Angle	[in] 1周65536とした回転角度

	スプライトを使った矩形の回転描画を行います。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_DrawSquareRotate( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, unsigned int Angle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pSpr2DTbl[Handle]->DrawSquareRotate( DstRc, SrcRc, Color, Angle );
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Px		[in] ポイントのX値が格納された配列
	@param Py		[in] ポイントのY値が格納された配列
	@param Width	[in] ポイントの幅が格納された配列
	@param Angle	[in] ポイントの1周65536とした回転角度が格納された配列
	@param Color	[in] 1周65536とした回転角度
	@param Count	[in] 各配列の要素数
	@param Src		[in] テクスチャUV矩形

	スプライトを使ったリスト状の描画を行います<BR>
	曲がるレーザーのような多関節系の表現するのに適しています。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_DrawList( LUE_HANDLE Handle, LuePoint Pos[], float Width[], int Angle[], unsigned int Color[], int Count, LueRect Src )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pSpr2DTbl[Handle]->DrawList( (CPoint2D<Float>*)Pos, Width, (Sint32*)Angle, (CColor*)Color, Count, SrcRc );
}

//------------------------------------------------------------------------------------------------
/**
	@brief 円状フェード
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル
	@param SrcRect		[in] テクスチャの適応矩形
	@param Divide		[in] 回転部分分割数（１６程度推奨）
	@param Side			[in] 側面分割数（１６程度推奨）
	@param Alpha		[in] 半透明度（-255～+255)

	画面中心に向かってフェードイン／フェードアウトをします<BR>
	画面効果としてよく見かける効果ですが簡単に使える画面効果として実装してあります。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_CircleFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> Src( SrcRect.x, SrcRect.y, SrcRect.w, SrcRect.h );
	g_pSpr2DTbl[Handle]->CircleFade( Src, Divide, Side, Alpha );
}

//------------------------------------------------------------------------------------------------
/**
	@brief 回転フェード
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル
	@param SrcRect		[in] テクスチャの適応矩形
	@param Divide		[in] 回転部分分割数（１６程度推奨）
	@param Side			[in] 側面分割数（１６程度推奨）
	@param Alpha		[in] 半透明度（-255～+255)

	時計回りに回転するようにフェードイン／フェードアウトをします<BR>
	画面効果としてよく見かける効果ですが簡単に使える画面効果として実装してあります。
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_CircleRoundFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> Src( SrcRect.x, SrcRect.y, SrcRect.w, SrcRect.h );
	g_pSpr2DTbl[Handle]->CircleRoundFade( Src, Divide, Side, Alpha );
}

} // extern "C"

