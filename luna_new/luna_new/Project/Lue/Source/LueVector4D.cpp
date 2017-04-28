
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueVector4D.h"


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

	値をベクトルに設定し、そのベクトルを取得します。<BR>
	w値は1.0fで初期化されています。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Set( float fPx, float fPy, float fPz )
{
	LueVector4D vOut = { fPx, fPy, fPz, 1.0f };
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
	その結果のベクトルを取得します。<BR>
	ただしw値は1.0fが設定されています。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Add( LueVector4D In1, LueVector4D In2 )
{
	LueVector4D vOut = { In1.x + In2.x, In1.y + In2.z, In1.z + In2.z, 1.0f };
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
	その結果のベクトルを取得します。<BR>
	ただしw値は1.0fが設定されています。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Sub( LueVector4D In1, LueVector4D In2 )
{
	LueVector4D vOut = { In1.x - In2.x, In1.y - In2.z, In1.z - In2.z, 1.0f };
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
float LueVector4D_LengthSq( LueVector4D In )
{
	CVector4D v( In.x, In.y, In.z );
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
float LueVector4D_Length( LueVector4D In )
{
	CVector4D v( In.x, In.y, In.z );
	return v.Length();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Normalize( LueVector4D In )
{
	CVector4D v( In.x, In.y, In.z );
	v.Normalize();

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
float LueVector4D_DotProduct( LueVector4D In1, LueVector4D In2 )
{
	CVector4D v1( In1.x, In1.y, In1.z );
	CVector4D v2( In2.x, In2.y, In2.z );
	return v1.Dot( v2 );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_CrossProduct( LueVector4D In1, LueVector4D In2 )
{
	CVector4D v1( In1.x, In1.y, In1.z );
	CVector4D v2( In2.x, In2.y, In2.z );
	CVector4D v3;

	v3.Cross( v1, v2 );

	LueVector4D vOut = { v3.x, v3.y, v3.z, 1.0f };
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
	反射後のベクトルを取得します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Reflect( LueVector4D In1, LueVector4D In2 )
{
	CVector4D v1( In1.x, In1.y, In1.z );
	CVector4D v2( In2.x, In2.y, In2.z );
	CVector4D v3;

	v3.Reflect( v1, v2 );

	LueVector4D vOut = { v3.x, v3.y, v3.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの回転拡縮変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小変換を行います。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_TransformNormal( LueVector4D In1, LueMatrix4x4 In2 )
{
	CVector4D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformNormal( m );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの回転拡縮移動変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動変換を行います。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_TransformCoord( LueVector4D In1, LueMatrix4x4 In2 )
{
	CVector4D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformCoord( m );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルの回転拡縮移動透視変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動・透視変換を行います。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_TransformProjection( LueVector4D In1, LueMatrix4x4 In2 )
{
	CVector4D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformProjection( m );

	LueVector4D vOut = { v.x, v.y, v.z, v.w };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルのX軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをX軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationX( LueVector4D In, int Angle )
{
	CVector4D v( In.x, In.y, In.z );
	v.RotationX( Angle );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルのY軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをY軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationY( LueVector4D In, int Angle )
{
	CVector4D v( In.x, In.y, In.z );
	v.RotationY( Angle );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ベクトルのZ軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをZ軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationZ( LueVector4D In, int Angle )
{
	CVector4D v( In.x, In.y, In.z );
	v.RotationZ( Angle );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
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

	ベクトルを任意の軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationAxis( LueVector4D In, int Angle, LueVector3D Axis )
{
	CVector4D v( In.x, In.y, In.z );
	CVector3D vAxis( Axis.x, Axis.y, Axis.z );
	v.RotationAxis( Angle, vAxis );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


}

