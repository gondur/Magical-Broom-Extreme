

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Math/Math.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::CMatrix()
	: Mtx		( *((SMatrix4x4*)(((Uint32)m_Data + 0xF) & ~0xF)) )
	, x			( Mtx.x )
	, y			( Mtx.y )
	, z			( Mtx.z )
	, w			( Mtx.w )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::CMatrix( CMatrix &Mat )
	: Mtx		( *((SMatrix4x4*)(((Uint32)m_Data + 0xF) & ~0xF)) )
	, x			( Mtx.x )
	, y			( Mtx.y )
	, z			( Mtx.z )
	, w			( Mtx.w )
{
	MemoryCopy( &Mtx, &Mat.Mtx, sizeof(SMatrix4x4) );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::CMatrix( SMatrix4x4 &Mat )
	: Mtx		( *((SMatrix4x4*)(((Uint32)m_Data + 0xF) & ~0xF)) )
	, x			( Mtx.x )
	, y			( Mtx.y )
	, z			( Mtx.z )
	, w			( Mtx.w )
{
	MemoryCopy( &Mtx, &Mat, sizeof(SMatrix4x4) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::CMatrix( CQuaternion &In )
	: Mtx		( *((SMatrix4x4*)(((Uint32)m_Data + 0xF) & ~0xF)) )
	, x			( Mtx.x )
	, y			( Mtx.y )
	, z			( Mtx.z )
	, w			( Mtx.w )
{
	Float xx = In.x * In.x;
	Float yy = In.y * In.y;
	Float zz = In.z * In.z;
	Float xy = In.x * In.y;
	Float xz = In.x * In.z;
	Float yz = In.y * In.z;
	Float wx = In.w * In.x;
	Float wy = In.w * In.y;
	Float wz = In.w * In.z;

	x.x = 1.0f - 2.0f * (yy + zz);
	x.y =        2.0f * (xy - wz);
	x.z =        2.0f * (xz + wy);
	x.w = 0.0f;

	y.x =        2.0f * (xy + wz);
	y.y = 1.0f - 2.0f * (xx + zz);
	y.z =        2.0f * (yz - wx);
	y.w = 0.0f;

	z.x =        2.0f * (xz - wy);
	z.y =        2.0f * (yz + wx);
	z.z = 1.0f - 2.0f * (xx + yy);
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::CMatrix(
		Float _11, Float _12, Float _13, Float _14,
		Float _21, Float _22, Float _23, Float _24,
		Float _31, Float _32, Float _33, Float _34,
		Float _41, Float _42, Float _43, Float _44 )
	: Mtx		( *((SMatrix4x4*)(((Uint32)m_Data + 0xF) & ~0xF)) )
	, x			( Mtx.x )
	, y			( Mtx.y )
	, z			( Mtx.z )
	, w			( Mtx.w )
{
	x.x = _11;  x.y = _12;  x.z = _13;  x.w = _14;
	y.x = _21;  y.y = _22;  y.z = _23;  y.w = _24;
	z.x = _31;  z.y = _32;  z.z = _33;  z.w = _34;
	w.x = _41;  w.y = _42;  w.z = _43;  w.w = _44;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Identity( void )
{
	x.x = 1.0f;  x.y = 0.0f;  x.z = 0.0f;  x.w = 0.0f;
	y.x = 0.0f;  y.y = 1.0f;  y.z = 0.0f;  y.w = 0.0f;
	z.x = 0.0f;  z.y = 0.0f;  z.z = 1.0f;  z.w = 0.0f;
	w.x = 0.0f;  w.y = 0.0f;  w.z = 0.0f;  w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Transpose( CMatrix &In )
{
	::D3DXMatrixTranspose( (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&In.Mtx );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Inverse( CMatrix &In )
{
	::D3DXMatrixInverse( (D3DXMATRIX*)&Mtx, NULL, (D3DXMATRIX*)&In.Mtx );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Multiply( CMatrix &In1, CMatrix &In2 )
{
	::D3DXMatrixMultiply( (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&In1.Mtx, (D3DXMATRIX*)&In2.Mtx );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Transpose( void )
{
	::D3DXMatrixTranspose( (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&Mtx );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Inverse( void )
{
	::D3DXMatrixInverse( (D3DXMATRIX*)&Mtx, NULL, (D3DXMATRIX*)&Mtx );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Multiply( CMatrix &In )
{
	::D3DXMatrixMultiply( (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&In.Mtx );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::RotationX( Sint32 Angle )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x = 1;  x.y =  0;  x.z = 0;  x.w = 0;
	y.x = 0;  y.y =  c;  y.z = s;  y.w = 0;
	z.x = 0;  z.y = -s;  z.z = c;  z.w = 0;
	w.x = 0;  w.y =  0;  w.z = 0;  w.w = 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::RotationY( Sint32 Angle )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x = c;  x.y = 0;  x.z = -s;  x.w = 0;
	y.x = 0;  y.y = 1;  y.z =  0;  y.w = 0;
	z.x = s;  z.y = 0;  z.z =  c;  z.w = 0;
	w.x = 0;  w.y = 0;  w.z =  0;  w.w = 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::RotationZ( Sint32 Angle )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x =  c;  x.y = s;  x.z = 0;  x.w = 0;
	y.x = -s;  y.y = c;  y.z = 0;  y.w = 0;
	z.x =  0;  z.y = 0;  z.z = 1;  z.w = 0;
	w.x =  0;  w.y = 0;  w.z = 0;  w.w = 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ )
{
	AngleX >>= 1;
	AngleY >>= 1;
	AngleZ >>= 1;

	Float SinAx = Math::Sin( AngleX );
	Float SinAy = Math::Sin( AngleY );
	Float SinAz = Math::Sin( AngleZ );
	Float CosAx = Math::Cos( AngleX );
	Float CosAy = Math::Cos( AngleY );
	Float CosAz = Math::Cos( AngleZ ); 

	Float _x = (SinAx * CosAy * CosAz) - (CosAx * SinAy * SinAz);
	Float _y = (CosAx * SinAy * CosAz) + (SinAx * CosAy * SinAz);
	Float _z = (CosAx * CosAy * SinAz) - (SinAx * SinAy * CosAz);
	Float _w = (CosAx * CosAy * CosAz) + (SinAx * SinAy * SinAz);

	Float xx = _x * _x;
	Float yy = _y * _y;
	Float zz = _z * _z;
	Float xy = _x * _y;
	Float xz = _x * _z;
	Float yz = _y * _z;
	Float wx = _w * _x;
	Float wy = _w * _y;
	Float wz = _w * _z;

	x.x = 1.0f - (2.0f * (yy + zz));
	x.y =        (2.0f * (xy - wz));
	x.z =        (2.0f * (xz + wy));
	x.w = 0.0f;

	y.x =        (2.0f * (xy + wz));
	y.y = 1.0f - (2.0f * (xx + zz));
	y.z =        (2.0f * (yz - wx));
	y.w = 0.0f;

	z.x =        (2.0f * (xz - wy));
	z.y =        (2.0f * (yz + wx));
	z.z = 1.0f - (2.0f * (xx + yy));
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::RotationAxis( Sint32 Angle, class CVector3D &Axis )
{
	CVector3D vAxis;

	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x = (1.0f-c)*(vAxis.x*vAxis.x) + c;
	x.y = (1.0f-c)*(vAxis.x*vAxis.y) - (vAxis.z*s);
	x.z = (1.0f-c)*(vAxis.z*vAxis.x) + (vAxis.y*s);
	x.w = 0.0f;

	y.x = (1.0f-c)*(vAxis.x*vAxis.y) + (vAxis.z*s);
	y.y = (1.0f-c)*(vAxis.y*vAxis.y) + c;
	y.z = (1.0f-c)*(vAxis.y*vAxis.z) - (vAxis.x*s);
	y.w = 0.0f;

	z.x = (1.0f-c)*(vAxis.z*vAxis.x) - (vAxis.y*s);
	z.y = (1.0f-c)*(vAxis.y*vAxis.z) + (vAxis.x*s);
	z.z = (1.0f-c)*(vAxis.z*vAxis.z) + c;
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Scaling( Float sx, Float sy, Float sz )
{
	x.x = sx;  x.y =  0;  x.z =  0;  x.w = 0;
	y.x =  0;  y.y = sy;  y.z =  0;  y.w = 0;
	z.x =  0;  z.y =  0;  z.z = sz;  z.w = 0;
	w.x =  0;  w.y =  0;  w.z =  0;  w.w = 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Translation( Float px, Float py, Float pz )
{
	x.x = 1;  x.y = 0;  x.z = 0;  x.w = 0;
	y.x = 0;  y.y = 1;  y.z = 0;  y.w = 0;
	z.x = 0;  z.y = 0;  z.z = 1;  z.w = 0;

	w.x = px;
	w.y = py;
	w.z = pz;
	w.w = 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect )
{
	::D3DXMatrixPerspectiveFovLH( (D3DXMATRIX*)&Mtx, ANGLE_TO_PI(Fov), Aspect, NearZ, FarZ );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::Ortho( Float Width, Float Height, Float NearZ, Float FarZ )
{
	::D3DXMatrixOrthoLH( (D3DXMATRIX*)&Mtx, Width, Height, NearZ, FarZ );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMatrix::LookAt( class CVector3D &Eye, class CVector3D &At, class CVector3D &Up )
{
	::D3DXMatrixLookAtLH( (D3DXMATRIX*)&Mtx, (D3DXVECTOR3*)&Eye, (D3DXVECTOR3*)&At, (D3DXVECTOR3*)&Up );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::operator SMatrix4x4 & ()
{
	return Mtx;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::operator SMatrix4x4 & () const
{
	return Mtx;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::operator SMatrix4x4 * ()
{
	return &Mtx;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix::operator SMatrix4x4 * () const
{
	return &Mtx;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix &CMatrix::operator = ( const CMatrix &In )
{
	Mtx = In.Mtx;
	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix &CMatrix::operator = ( const CQuaternion &In )
{
	Float xx = In.x * In.x;
	Float yy = In.y * In.y;
	Float zz = In.z * In.z;
	Float xy = In.x * In.y;
	Float xz = In.x * In.z;
	Float yz = In.y * In.z;
	Float wx = In.w * In.x;
	Float wy = In.w * In.y;
	Float wz = In.w * In.z;

	x.x = 1.0f - 2.0f * (yy + zz);
	x.y =        2.0f * (xy - wz);
	x.z =        2.0f * (xz + wy);
	x.w = 0.0f;

	y.x =        2.0f * (xy + wz);
	y.y = 1.0f - 2.0f * (xx + zz);
	y.z =        2.0f * (yz - wx);
	y.w = 0.0f;

	z.x =        2.0f * (xz - wy);
	z.y =        2.0f * (yz + wx);
	z.z = 1.0f - 2.0f * (xx + yy);
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix CMatrix::operator * ( const CMatrix &In )
{
	CMatrix mTemp;
	::D3DXMatrixMultiply( (D3DXMATRIX*)&mTemp.Mtx, (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&In.Mtx );
	return mTemp;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMatrix& CMatrix::operator *= ( const CMatrix &In )
{
	::D3DXMatrixMultiply( (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&Mtx, (D3DXMATRIX*)&In.Mtx );
	return *this;
}

