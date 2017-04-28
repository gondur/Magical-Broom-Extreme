
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LuePointPrimitive2D.h"

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
const unsigned int POINTPRIMITIVE2D_MAX = 1024;


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static IPointPrimitive2D *g_pPrim2DTbl[POINTPRIMITIVE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );


//------------------------------------------------------------------------------------------------
/**
	@brief ポイントプリミティブ管理クラスの初期化
	@author 葉迩倭

	ポイントプリミティブ管理クラスの初期化を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Initialize( void )
{
	for ( Uint32 i = 0; i < POINTPRIMITIVE2D_MAX; i++ )
	{
		g_pPrim2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ポイントプリミティブ管理クラスの解放
	@author 葉迩倭

	ポイントプリミティブ管理クラスの解放を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Finalize( void )
{
	for ( Uint32 i = 0; i < POINTPRIMITIVE2D_MAX; i++ )
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
	@brief 未使用ポイントプリミティブの検索
	@author 葉迩倭

	@return 未使用のポイントプリミティブハンドル

	未使用のポイントプリミティブオブジェクトの検索をします。<BR>
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LuePointPrimitive2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < POINTPRIMITIVE2D_MAX; i++ )
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
	@brief ポイントプリミティブの解放
	@author 葉迩倭

	@param Handle	[in] ポイントプリミティブハンドル

	ポイントプリミティブの解放を行います。
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;

	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		g_pPrim2DTbl[Handle]->Release();
		g_pPrim2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ポイントプリミティブ生成
	@author 葉迩倭

	@param PrimitiveMax		[in] ポイントプリミティブ最大数

	@return ポイントプリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	ポイントプリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズです。
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LuePointPrimitive2D_Create( unsigned int PrimitiveMax )
{
	LUE_HANDLE Handle = LuePointPrimitive2D_SearchFreeHandle();
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pPrim2DTbl[Handle] = Lue_GetRenderer()->CreatePointPrimitive2D( PrimitiveMax );
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

	@param Handle		[in] ポイントプリミティブハンドル

	この関数を呼び出すことでリクエストされたポイントプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル

	この関数を呼び出すことでポイントプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル

	この関数を呼び出すことでポイントプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル
	@param pPrimitive	[in] ポイントプリミティブ頂点データ
	@param Count		[in] pPrimitiveの数

	@retval LTRUE	正常に追加できた
	@retval LFALSE	追加できなかった（バッファオーバーフロー

	描画ポイントプリミティブ頂点を追加します。<BR>
	必ず Begin() と End() の間で呼んでください。<BR>
	この関数は実際に描画を行いません<BR>
	バッファに追加するだけで実際の描画は Render() 時に行われます。
*/
//------------------------------------------------------------------------------------------------
eLueBool LuePointPrimitive2D_Push( LUE_HANDLE Handle, LueVertex2D *pPrimitive, unsigned int Count )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return LFALSE;
	if ( g_pPrim2DTbl[Handle] == NULL ) return LFALSE;

	return g_pPrim2DTbl[Handle]->Push( (SVertex2D*)pPrimitive, Count ) ? LTRUE : LFALSE;
}


} // extern "C"

