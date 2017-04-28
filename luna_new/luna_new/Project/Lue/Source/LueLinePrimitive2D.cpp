
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueLinePrimitive2D.h"

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
const unsigned int LINEPRIMITIVE2D_MAX = 1024;


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ILinePrimitive2D *g_pPrim2DTbl[LINEPRIMITIVE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );


//------------------------------------------------------------------------------------------------
/**
	@brief ラインプリミティブ管理クラスの初期化
	@author 葉迩倭

	ラインプリミティブ管理クラスの初期化を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Initialize( void )
{
	for ( Uint32 i = 0; i < LINEPRIMITIVE2D_MAX; i++ )
	{
		g_pPrim2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ラインプリミティブ管理クラスの解放
	@author 葉迩倭

	ラインプリミティブ管理クラスの解放を行います。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Finalize( void )
{
	for ( Uint32 i = 0; i < LINEPRIMITIVE2D_MAX; i++ )
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
	@brief 未使用ラインプリミティブの検索
	@author 葉迩倭

	@return 未使用のラインプリミティブハンドル

	未使用のラインプリミティブオブジェクトの検索をします。<BR>
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueLinePrimitive2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < LINEPRIMITIVE2D_MAX; i++ )
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
	@brief ラインプリミティブの解放
	@author 葉迩倭

	@param Handle	[in] ラインプリミティブハンドル

	ラインプリミティブの解放を行います。
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;

	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		g_pPrim2DTbl[Handle]->Release();
		g_pPrim2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ラインプリミティブ生成
	@author 葉迩倭

	@param PrimitiveMax		[in] ラインプリミティブ最大数

	@return ラインプリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	ラインプリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズです。
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueLinePrimitive2D_Create( unsigned int PrimitiveMax )
{
	LUE_HANDLE Handle = LueLinePrimitive2D_SearchFreeHandle();
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pPrim2DTbl[Handle] = Lue_GetRenderer()->CreateLinePrimitive2D( PrimitiveMax );
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

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでリクエストされたラインプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでラインプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでラインプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル
	@param pPrimitive	[in] ラインプリミティブ頂点データ
	@param Count		[in] pPrimitiveの数

	@retval LTRUE	正常に追加できた
	@retval LFALSE	追加できなかった（バッファオーバーフロー

	描画ラインプリミティブ頂点を追加します。<BR>
	必ず Begin() と End() の間で呼んでください。<BR>
	この関数は実際に描画を行いません<BR>
	バッファに追加するだけで実際の描画は Render() 時に行われます。
*/
//------------------------------------------------------------------------------------------------
eLueBool LueLinePrimitive2D_Push( LUE_HANDLE Handle, LueLinePrimitiveVertex2D *pPrimitive, unsigned int Count )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return LFALSE;
	if ( g_pPrim2DTbl[Handle] == NULL ) return LFALSE;

	return g_pPrim2DTbl[Handle]->Push( (SLineVertex2D*)pPrimitive, Count ) ? LTRUE : LFALSE;
}


} // extern "C"

