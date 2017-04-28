
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueMatrix.h"


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
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Identity( void )
{
	LueMatrix4x4 mOut = {
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Transpose( LueMatrix4x4 In )
{
	CMatrix m(
		In.x.x, In.x.y, In.x.z, In.x.w,
		In.y.x, In.y.y, In.y.z, In.y.w,
		In.z.x, In.z.y, In.z.z, In.z.w,
		In.w.x, In.w.y, In.w.z, In.w.w );

	m.Transpose();

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Inverse( LueMatrix4x4 In )
{
	CMatrix m(
		In.x.x, In.x.y, In.x.z, In.x.w,
		In.y.x, In.y.y, In.y.z, In.y.w,
		In.z.x, In.z.y, In.z.z, In.z.w,
		In.w.x, In.w.y, In.w.z, In.w.w );

	m.Inverse();

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Multiply( LueMatrix4x4 In1, LueMatrix4x4 In2 )
{
	CMatrix m1(
		In1.x.x, In1.x.y, In1.x.z, In1.x.w,
		In1.y.x, In1.y.y, In1.y.z, In1.y.w,
		In1.z.x, In1.z.y, In1.z.z, In1.z.w,
		In1.w.x, In1.w.y, In1.w.z, In1.w.w );
	CMatrix m2(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );
	CMatrix m3;

	m3.Multiply( m1, m2 );

	LueMatrix4x4 mOut = {
		{ m3.x.x, m3.x.y, m3.x.z, m3.x.w },
		{ m3.y.x, m3.y.y, m3.y.z, m3.y.w },
		{ m3.z.x, m3.z.y, m3.z.z, m3.z.w },
		{ m3.w.x, m3.w.y, m3.w.z, m3.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_RotationX( int Angle )
{
	CMatrix m;
	m.RotationX( Angle );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_RotationY( int Angle )
{
	CMatrix m;
	m.RotationY( Angle );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_RotationZ( int Angle )
{
	CMatrix m;
	m.RotationZ( Angle );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_RotationZXY( int AngleX, int AngleY, int AngleZ )
{
	CMatrix m;
	m.RotationZXY( AngleX, AngleY, AngleZ );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_RotationAxis( int Angle, LueVector3D Axis )
{
	CMatrix m;
	CVector3D v( Axis.x, Axis.y, Axis.z );

	m.RotationAxis( Angle, v );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}

//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Scaling( float sx, float sy, float sz )
{
	CMatrix m;
	m.Scaling( sx, sy, sz );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Translation( float px, float py, float pz )
{
	CMatrix m;
	m.Translation( px, py, pz );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Perspective( int fov, float near_z, float far_z, float aspect )
{
	CMatrix m;
	m.Perspective( fov, near_z, far_z, aspect );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_Ortho( float w, float h, float near_z, float far_z )
{
	CMatrix m;
	m.Ortho( w, h, near_z, far_z );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
LueMatrix4x4 LueMatrix_LookAt( LueVector3D Eye, LueVector3D At, LueVector3D Up )
{
	CVector3D vEye( Eye.x, Eye.y, Eye.z );
	CVector3D vAt( At.x, At.y, At.z );
	CVector3D vUp( Up.x, Up.y, Up.z );

	CMatrix m;
	m.LookAt( vEye, vAt, vUp );

	LueMatrix4x4 mOut = {
		{ m.x.x, m.x.y, m.x.z, m.x.w },
		{ m.y.x, m.y.y, m.y.z, m.y.w },
		{ m.z.x, m.z.y, m.z.z, m.z.w },
		{ m.w.x, m.w.y, m.w.z, m.w.w },
	};

	return mOut;
}




}

