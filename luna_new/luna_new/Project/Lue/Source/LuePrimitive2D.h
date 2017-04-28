
#ifndef ___LUE_PRIMITIVE2D_H___
#define ___LUE_PRIMITIVE2D_H___


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
	@brief プリミティブの解放
	@author 葉迩倭

	@param Handle	[in] プリミティブハンドル

	プリミティブの解放を行います。
*/
void LuePrimitive2D_Release( LUE_HANDLE Handle );

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
LUE_HANDLE LuePrimitive2D_Create( unsigned int PrimitiveMax );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでリクエストされたプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LuePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LuePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LuePrimitive2D_End( LUE_HANDLE Handle );

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
eLueBool LuePrimitive2D_Push( LUE_HANDLE Handle, LuePrimitiveVertex2D *pPrimitive, unsigned int Count );

/**
	@brief 四角形描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param DstRect		[in] 描画矩形
	@param Color		[in] 描画色

	四角形の描画を行います。
*/
void LuePrimitive2D_Square( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color );

/**
	@brief 回転四角形描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param DstRect		[in] 描画矩形
	@param Color		[in] 描画色
	@param Angle		[in] 回転角度

	四角形の描画を行います。
*/
void LuePrimitive2D_SquareRotate( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color, int Angle );

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
void LuePrimitive2D_Polygon( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num );

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
void LuePrimitive2D_PolygonRotate( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num, int Angle );

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
void LuePrimitive2D_Ring( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num );

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
void LuePrimitive2D_RingRotate( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num, int Angle );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_PRIMITIVE2D_H___
