
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LuePrimitive2D.h"

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
const unsigned int PRIMITIVE2D_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static IPrimitive2D *g_pPrim2DTbl[PRIMITIVE2D_MAX];

//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern ITexture *LueTexture_Get( LUE_HANDLE Handle );

//------------------------------------------------------------------------------------------------
/**
	@brief プリミティブ管理クラスの初期化
	@author 葉迩倭

	プリミティブ管理クラスの初期化を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Initialize( void )
{
	for ( Uint32 i = 0; i < PRIMITIVE2D_MAX; i++ )
	{
		g_pPrim2DTbl[i] = NULL;
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief プリミティブ管理クラスの解放
	@author 葉迩倭

	プリミティブ管理クラスの解放を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Finalize( void )
{
	for ( Uint32 i = 0; i < PRIMITIVE2D_MAX; i++ )
	{
		if ( g_pPrim2DTbl[i] != NULL )
		{
			g_pPrim2DTbl[i]->Release();
			g_pPrim2DTbl[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief 未使用プリミティブの検索
	@author 葉迩倭

	@return 未使用のプリミティブハンドル

	未使用のプリミティブオブジェクトの検索をします。<BR>
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LuePrimitive2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < PRIMITIVE2D_MAX; i++ )
	{
		if ( g_pPrim2DTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief プリミティブの解放
	@author 葉迩倭

	@param Handle	[in] プリミティブハンドル

	プリミティブの解放を行います。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;

	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		g_pPrim2DTbl[Handle]->Release();
		g_pPrim2DTbl[Handle] = NULL;
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief プリミティブ生成
	@author 葉迩倭

	@param PrimitiveMax		[in] プリミティブ最大数

	@return プリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	プリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズであり、<BR>
	シザリング等を行うとリクエストした頂点数よりも多く消費されるので<BR>
	目安程度として溢れない十分な大きさを指定するようにしてください。
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LuePrimitive2D_Create( unsigned int PrimitiveMax )
{
	LUE_HANDLE Handle = LuePrimitive2D_SearchFreeHandle();
	if ( Handle >= PRIMITIVE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pPrim2DTbl[Handle] = Lue_GetRenderer()->CreatePrimitive2D( PrimitiveMax );
	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでリクエストされたプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Rendering();
}

//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Begin();
}

//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->End();
}

//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param pPrimitive	[in] プリミティブ頂点データ
	@param Count		[in] pPrimitiveの数

	@retval LTRUE	正常に追加できた
	@retval LFALSE	追加できなかった（バッファオーバーフロー

	描画プリミティブ頂点を追加します。<BR>
	必ず Begin() と End() の間で呼んでください。<BR>
	この関数は実際に描画を行いません<BR>
	バッファに追加するだけで実際の描画は Render() 時に行われます。
*/
//------------------------------------------------------------------------------------------------
eLueBool LuePrimitive2D_Push( LUE_HANDLE Handle, LuePrimitiveVertex2D *pPrimitive, unsigned int Count )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return LFALSE;
	if ( g_pPrim2DTbl[Handle] == NULL ) return LFALSE;

	return g_pPrim2DTbl[Handle]->Push( (SPrimitiveVertex2D*)pPrimitive, Count ) ? LTRUE : LFALSE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief 四角形描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param DstRect		[in] 描画矩形
	@param Color		[in] 描画色

	四角形の描画を行います。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Square( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> Dst( DstRect.x, DstRect.y, DstRect.w, DstRect.h );
	g_pPrim2DTbl[Handle]->Square( Dst, Color );
}

//------------------------------------------------------------------------------------------------
/**
	@brief 回転四角形描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param DstRect		[in] 描画矩形
	@param Color		[in] 描画色
	@param Angle		[in] 回転角度

	四角形の描画を行います。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_SquareRotate( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color, int Angle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> Dst( DstRect.x, DstRect.y, DstRect.w, DstRect.h );
	g_pPrim2DTbl[Handle]->SquareRotate( Dst, Color, Angle );
}

//------------------------------------------------------------------------------------------------
/**
	@brief 正多角形
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] 多角形中心位置
	@param fRadius		[in] 多角形半径
	@param Color		[in] 多角形色
	@param Num			[in] 画数（３～

	正多角形を描画します。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Polygon( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	CPoint2D<Sint32> vPos( Pos.x, Pos.y );
	g_pPrim2DTbl[Handle]->Polygon( vPos, fRadius, Color, Num );
}

//------------------------------------------------------------------------------------------------
/**
	@brief 回転正多角形
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] 多角形中心位置
	@param fRadius		[in] 多角形半径
	@param Color		[in] 多角形色
	@param Num			[in] 画数（３～
	@param Angle		[in] 回転角度

	正多角形を描画します。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_PolygonRotate( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num, int Angle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	CPoint2D<Sint32> vPos( Pos.x, Pos.y );
	g_pPrim2DTbl[Handle]->PolygonRotate( vPos, fRadius, Color, Num, Angle );
}

//------------------------------------------------------------------------------------------------
/**
	@brief リング状ポリゴン
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] リングの中心位置
	@param fInRadius	[in] リングの内径
	@param fOutRadius	[in] リングの外形
	@param InColor		[in] リングの内色
	@param OutColor		[in] リングの外色
    @param Num			[in] リングを構成する頂点数

	リング状のポリゴンを描画します。<BR>
	内径外径で別々の色が指定できるので衝撃波のようなエフェクトが作れます。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_Ring( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	CPoint2D<Sint32> vPos( Pos.x, Pos.y );
	g_pPrim2DTbl[Handle]->Ring( vPos, fInRadius, fOutRadius, InColor, OutColor, Num );
}

//------------------------------------------------------------------------------------------------
/**
	@brief 回転リング状ポリゴン
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] リングの中心位置
	@param fInRadius	[in] リングの内径
	@param fOutRadius	[in] リングの外形
	@param InColor		[in] リングの内色
	@param OutColor		[in] リングの外色
    @param Num			[in] リングを構成する頂点数
	@param Angle		[in] 回転角度

	リング状のポリゴンを描画します。<BR>
	内径外径で別々の色が指定できるので衝撃波のようなエフェクトが作れます。
*/
//------------------------------------------------------------------------------------------------
void LuePrimitive2D_RingRotate( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num, int Angle )
{
	if ( Handle >= PRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	CPoint2D<Sint32> vPos( Pos.x, Pos.y );
	g_pPrim2DTbl[Handle]->RingRotate( vPos, fInRadius, fOutRadius, InColor, OutColor, Num, Angle );
}


} // extern "C"

