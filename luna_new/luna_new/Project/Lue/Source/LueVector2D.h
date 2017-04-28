
#ifndef ___LUE_VECTOR2D_H___
#define ___LUE_VECTOR2D_H___


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
	@brief ベクトルに値を設定
	@author 葉迩倭

	@param fPx	[in] x値
	@param fPy	[in] y値

	@return 値設定後のベクトル

	値をベクトルに設定し、そのベクトルを取得します。
*/
LueVector2D LueVector2D_Set( float fPx, float fPy );

/**
	@brief ベクトル同士の加算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を加算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector2D LueVector2D_Add( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトル同士の減算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を減算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector2D LueVector2D_Sub( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトルの長さの二乗を取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さの二乗

	指定ベクトルの長さの二乗を取得します。
*/
float LueVector2D_LengthSq( LueVector2D In );

/**
	@brief ベクトルの長さを取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さ

	指定ベクトルの長さを取得します。
*/
float LueVector2D_Length( LueVector2D In );

/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。
*/
LueVector2D LueVector2D_Normalize( LueVector2D In );

/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。
*/
float LueVector2D_DotProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。
*/
float LueVector2D_CrossProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトルの反射を取得
	@author 葉迩倭

	@param In1	[in] 入射ベクトル
	@param In2	[in] 反射軸ベクトル

	@return 反射後のベクトル

	入射ベクトルを反射軸ベクトルを法泉とする平面で反射した時の<BR>
	反射後のベクトルを取得します。
*/
LueVector2D LueVector2D_Reflect( LueVector2D In1, LueVector2D In2 );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_VECTOR2D_H___

