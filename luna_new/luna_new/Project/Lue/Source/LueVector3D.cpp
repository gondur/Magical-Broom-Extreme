
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueVector3D.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルに値を設定
	@author 葉迩倭

	@param fPx	[in] x値
	@param fPy	[in] y値
	@param fPz	[in] z値

	@return 値設定後のベクトル

	値をベクトルに設定し、そのベクトルを取得します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_Set( float fPx, float fPy, float fPz )
{
	LueVector3D vOut = { fPx, fPy, fPz };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトル同士の加算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を加算し、<BR>
	その結果のベクトルを取得します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_Add( LueVector3D In1, LueVector3D In2 )
{
	LueVector3D vOut = { In1.x + In2.x, In1.y + In2.z, In1.z + In2.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトル同士の減算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を減算し、<BR>
	その結果のベクトルを取得します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_Sub( LueVector3D In1, LueVector3D In2 )
{
	LueVector3D vOut = { In1.x - In2.x, In1.y - In2.z, In1.z - In2.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの長さの二乗を取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さの二乗

	指定ベクトルの長さの二乗を取得します。
*/
//------------------------------------------------------------------------------------------------
float LueVector3D_LengthSq( LueVector3D In )
{
	CVector3D v( In.x, In.y, In.z );
	return v.LengthSq();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの長さを取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さ

	指定ベクトルの長さを取得します。
*/
//------------------------------------------------------------------------------------------------
float LueVector3D_Length( LueVector3D In )
{
	CVector3D v( In.x, In.y, In.z );
	return v.Length();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_Normalize( LueVector3D In )
{
	CVector3D v( In.x, In.y, In.z );
	v.Normalize();

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。
*/
//------------------------------------------------------------------------------------------------
float LueVector3D_DotProduct( LueVector3D In1, LueVector3D In2 )
{
	CVector3D v1( In1.x, In1.y, In1.z );
	CVector3D v2( In2.x, In2.y, In2.z );
	return v1.Dot( v2 );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_CrossProduct( LueVector3D In1, LueVector3D In2 )
{
	CVector3D v1( In1.x, In1.y, In1.z );
	CVector3D v2( In2.x, In2.y, In2.z );
	CVector3D v3;

	v3.Cross( v1, v2 );

	LueVector3D vOut = { v3.x, v3.y, v3.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの反射を取得
	@author 葉迩倭

	@param In1	[in] 入射ベクトル
	@param In2	[in] 反射軸ベクトル

	@return 反射後のベクトル

	入射ベクトルを反射軸ベクトルを法泉とする平面で反射した時の<BR>
	反射後のベクトルを取得します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_Reflect( LueVector3D In1, LueVector3D In2 )
{
	CVector3D v1( In1.x, In1.y, In1.z );
	CVector3D v2( In2.x, In2.y, In2.z );
	CVector3D v3;

	v3.Reflect( v1, v2 );

	LueVector3D vOut = { v3.x, v3.y, v3.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの回転拡縮変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小変換を行います。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_TransformNormal( LueVector3D In1, LueMatrix4x4 In2 )
{
	CVector3D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformNormal( m );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの回転拡縮移動変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動変換を行います。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_TransformCoord( LueVector3D In1, LueMatrix4x4 In2 )
{
	CVector3D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformCoord( m );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの回転拡縮移動透視変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動・透視変換を行います。<BR>
	演算後のw値がほしい場合は LueVector4D_TransformProjection 使ってください。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_TransformProjection( LueVector3D In1, LueMatrix4x4 In2 )
{
	CVector3D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformProjection( m );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルのX軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをX軸で回転します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_RotationX( LueVector3D In, int Angle )
{
	CVector3D v( In.x, In.y, In.z );
	v.RotationX( Angle );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルのY軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをY軸で回転します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_RotationY( LueVector3D In, int Angle )
{
	CVector3D v( In.x, In.y, In.z );
	v.RotationY( Angle );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルのZ軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをZ軸で回転します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_RotationZ( LueVector3D In, int Angle )
{
	CVector3D v( In.x, In.y, In.z );
	v.RotationZ( Angle );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの任意軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度
	@param Axis		[in] 回転の基準軸

	@return 変換後のベクトル

	ベクトルを任意の軸で回転します。
*/
//------------------------------------------------------------------------------------------------
LueVector3D LueVector3D_RotationAxis( LueVector3D In, int Angle, LueVector3D Axis )
{
	CVector3D v( In.x, In.y, In.z );
	CVector3D vAxis( Axis.x, Axis.y, Axis.z );
	v.RotationAxis( Angle, vAxis );

	LueVector3D vOut = { v.x, v.y, v.z };
	return vOut;
}


}

