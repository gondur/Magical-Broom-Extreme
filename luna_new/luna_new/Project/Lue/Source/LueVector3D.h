
#ifndef ___LUE_VECTOR3D_H___
#define ___LUE_VECTOR3D_H___


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
	@param fPz	[in] z値

	@return 値設定後のベクトル

	値をベクトルに設定し、そのベクトルを取得します。
*/
LueVector3D LueVector3D_Set( float fPx, float fPy, float fPz );

/**
	@brief ベクトル同士の加算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を加算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector3D LueVector3D_Add( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトル同士の減算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を減算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector3D LueVector3D_Sub( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの長さの二乗を取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さの二乗

	指定ベクトルの長さの二乗を取得します。
*/
float LueVector3D_LengthSq( LueVector3D In );

/**
	@brief ベクトルの長さを取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さ

	指定ベクトルの長さを取得します。
*/
float LueVector3D_Length( LueVector3D In );

/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。
*/
LueVector3D LueVector3D_Normalize( LueVector3D In );

/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。
*/
float LueVector3D_DotProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。
*/
LueVector3D LueVector3D_CrossProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの反射を取得
	@author 葉迩倭

	@param In1	[in] 入射ベクトル
	@param In2	[in] 反射軸ベクトル

	@return 反射後のベクトル

	入射ベクトルを反射軸ベクトルを法泉とする平面で反射した時の<BR>
	反射後のベクトルを取得します。
*/
LueVector3D LueVector3D_Reflect( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの回転拡縮変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小変換を行います。
*/
LueVector3D LueVector3D_TransformNormal( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルの回転拡縮移動変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動変換を行います。
*/
LueVector3D LueVector3D_TransformCoord( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルの回転拡縮移動透視変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動・透視変換を行います。<BR>
	演算後のw値がほしい場合は LueVector4D_TransformProjection 使ってください。
*/
LueVector3D LueVector3D_TransformProjection( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルのX軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをX軸で回転します。
*/
LueVector3D LueVector3D_RotationX( LueVector3D In, int Angle );

/**
	@brief ベクトルのY軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをY軸で回転します。
*/
LueVector3D LueVector3D_RotationY( LueVector3D In, int Angle );

/**
	@brief ベクトルのZ軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをZ軸で回転します。
*/
LueVector3D LueVector3D_RotationZ( LueVector3D In, int Angle );

/**
	@brief ベクトルの任意軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度
	@param Axis		[in] 回転の基準軸

	@return 変換後のベクトル

	ベクトルを任意の軸で回転します。
*/
LueVector3D LueVector3D_RotationAxis( LueVector3D In, int Angle, LueVector3D Axis );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_VECTOR3D_H___

