
#ifndef ___LUE_LINEPRIMITIVE2D_H___
#define ___LUE_LINEPRIMITIVE2D_H___


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
	@brief ラインプリミティブの解放
	@author 葉迩倭

	@param Handle	[in] ラインプリミティブハンドル

	ラインプリミティブの解放を行います。
*/
void LueLinePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief ラインプリミティブ生成
	@author 葉迩倭

	@param LinePrimitiveMax		[in] ラインプリミティブ最大数

	@return ラインプリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	ラインプリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズです。
*/
LUE_HANDLE LueLinePrimitive2D_Create( unsigned int LinePrimitiveMax );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでリクエストされたラインプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LueLinePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでラインプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LueLinePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでラインプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LueLinePrimitive2D_End( LUE_HANDLE Handle );

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
eLueBool LueLinePrimitive2D_Push( LUE_HANDLE Handle, LueLinePrimitiveVertex2D *pPrimitive, unsigned int Count );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_LINEPRIMITIVE2D_H___
