

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Math/Math.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CStyle::CStyle()
{
	TransformReset();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CStyle::CStyle( const CStyle &Style )
{
	*this = Style;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::TransformReset( void )
{
	// 姿勢
	m_mStyle.Identity();
	// 逆姿勢
	m_mStyleInverse.Identity();
	// トランスフォーム
	m_mTransform.Identity();
	// 逆トランスフォーム
	m_mTransformInverse.Identity();
	// 上
	m_vUp.Set( 0.0f, 1.0f, 0.0f );
	// 右
	m_vRight.Set( 1.0f, 0.0f, 0.0f );
	// 前
	m_vFront.Set( 0.0f, 0.0f, 1.0f );
	// 位置
	m_vPosition.Set( 0.0f, 0.0f, 0.0f );
	// 拡大縮小
	m_vScale.Set( 1.0f, 1.0f, 1.0f );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::TransformUpdate( void )
{
	CMatrix mTemp;
	CMatrix *pMat;

	//------------------------------------------------------------
	// 姿勢行列
	//------------------------------------------------------------
	pMat = &m_mStyle;

	pMat->x.x = m_vRight.x; pMat->x.y = m_vRight.y; pMat->x.z = m_vRight.z; pMat->x.w = 0.0f;
	pMat->y.x = m_vUp.x;    pMat->y.y = m_vUp.y;    pMat->y.z = m_vUp.z;    pMat->y.w = 0.0f;
	pMat->z.x = m_vFront.x; pMat->z.y = m_vFront.y; pMat->z.z = m_vFront.z; pMat->z.w = 0.0f;
	pMat->w.x = 0.0f;       pMat->w.y = 0.0f;       pMat->w.z = 0.0f;       pMat->w.w = 1.0f;

	//------------------------------------------------------------
	// トランスフォーム行列生成
	//------------------------------------------------------------
	pMat = &m_mTransform;

	pMat->x.x = m_vRight.x;    pMat->x.y = m_vRight.y;    pMat->x.z = m_vRight.z;    pMat->x.w = 0.0f;
	pMat->y.x = m_vUp.x;       pMat->y.y = m_vUp.y;       pMat->y.z = m_vUp.z;       pMat->y.w = 0.0f;
	pMat->z.x = m_vFront.x;    pMat->z.y = m_vFront.y;    pMat->z.z = m_vFront.z;    pMat->z.w = 0.0f;
	pMat->w.x = m_vPosition.x; pMat->w.y = m_vPosition.y; pMat->w.z = m_vPosition.z; pMat->w.w = 1.0f;

	mTemp.Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	m_mTransform = mTemp * m_mTransform;

	//------------------------------------------------------------
	// 逆姿勢行列
	//------------------------------------------------------------
	pMat = &m_mStyleInverse;

	pMat->x.x = m_vRight.x; pMat->x.y = m_vUp.x; pMat->x.z = m_vFront.x; pMat->x.w = 0.0f;
	pMat->y.x = m_vRight.y; pMat->y.y = m_vUp.y; pMat->y.z = m_vFront.y; pMat->y.w = 0.0f;
	pMat->z.x = m_vRight.z; pMat->z.y = m_vUp.z; pMat->z.z = m_vFront.z; pMat->z.w = 0.0f;
	pMat->w.x = 0.0f;       pMat->w.y = 0.0f;    pMat->w.z = 0.0f;       pMat->w.w = 1.0f;

	//------------------------------------------------------------
	// 逆トランスフォーム行列生成
	//------------------------------------------------------------
	pMat = &m_mTransformInverse;

	pMat->x.x = m_vRight.x; pMat->x.y = m_vUp.x; pMat->x.z = m_vFront.x; pMat->x.w = 0.0f;
	pMat->y.x = m_vRight.y; pMat->y.y = m_vUp.y; pMat->y.z = m_vFront.y; pMat->y.w = 0.0f;
	pMat->z.x = m_vRight.z; pMat->z.y = m_vUp.z; pMat->z.z = m_vFront.z; pMat->z.w = 0.0f;

	pMat->w.x = -m_vPosition.Dot( m_vRight );
	pMat->w.y = -m_vPosition.Dot( m_vUp );
	pMat->w.z = -m_vPosition.Dot( m_vFront );
	pMat->w.w = 1.0f;

	mTemp.Scaling( 1.0f/m_vScale.x, 1.0f/m_vScale.y, 1.0f/m_vScale.z );
	m_mTransform = m_mTransform * mTemp;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::FromMatrix( CMatrix &Mat )
{
	m_vRight.x = Mat.x.x;
	m_vRight.y = Mat.x.y;
	m_vRight.z = Mat.x.z;

	m_vUp.x = Mat.y.x;
	m_vUp.y = Mat.y.y;
	m_vUp.z = Mat.y.z;

	m_vFront.x = Mat.z.x;
	m_vFront.y = Mat.z.y;
	m_vFront.z = Mat.z.z;

	m_vPosition.x = Mat.w.x;
	m_vPosition.y = Mat.w.y;
	m_vPosition.z = Mat.w.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CStyle::GetAngleX( void )
{
	return PI_TO_ANGLE( toF(asinf(m_vFront.y)) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CStyle::GetAngleY( void )
{
	if ( (m_vFront.y == -1.0f) || (m_vFront.y == +1.0f) )
	{
		return PI_TO_ANGLE( toF(atan2f(m_vUp.x, m_vUp.z)) );
	}
	else
	{
		return PI_TO_ANGLE( toF(atan2f(m_vFront.x, m_vFront.z)) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CStyle::GetAngleZ( void )
{
	Float fTemp = toF(asin(m_vRight.y / toF(sqrt(1.0f - m_vFront.y * m_vFront.y))));

	if ( m_vUp.y < 0 )
	{
		return PI_TO_ANGLE( PI - fTemp );
	}
	else
	{
		return PI_TO_ANGLE( fTemp );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::RotationX( Sint32 Rot )
{
	static CMatrix Mt[2];
	static CMatrix *pMt[2] = { &Mt[0], &Mt[1] };

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	pMt[0]->x.x = m_vRight.x;  pMt[0]->x.y = m_vRight.y;  pMt[0]->x.z = m_vRight.z;  pMt[0]->x.w = 0;
	pMt[0]->y.x = m_vUp.x;     pMt[0]->y.y = m_vUp.y;     pMt[0]->y.z = m_vUp.z;     pMt[0]->y.w = 0;
	pMt[0]->z.x = m_vFront.x;  pMt[0]->z.y = m_vFront.y;  pMt[0]->z.z = m_vFront.z;  pMt[0]->z.w = 0;
	pMt[0]->w.x = 0;           pMt[0]->w.y = 0;           pMt[0]->w.z = 0;           pMt[0]->w.w = 1;

	pMt[1]->x.x = 1;  pMt[1]->x.y =     0;  pMt[1]->x.z =    0;  pMt[1]->x.w = 0;
	pMt[1]->y.x = 0;  pMt[1]->y.y =  fCos;  pMt[1]->y.z = fSin;  pMt[1]->y.w = 0;
	pMt[1]->z.x = 0;  pMt[1]->z.y = -fSin;  pMt[1]->z.z = fCos;  pMt[1]->z.w = 0;
	pMt[1]->w.x = 0;  pMt[1]->w.y =     0;  pMt[1]->w.z =    0;  pMt[1]->w.w = 1;

	Mt[0] *= Mt[1];

	m_vRight.x = pMt[0]->x.x;
	m_vRight.y = pMt[0]->x.y;
	m_vRight.z = pMt[0]->x.z;
	m_vUp.x    = pMt[0]->y.x;
	m_vUp.y    = pMt[0]->y.y;
	m_vUp.z    = pMt[0]->y.z;
	m_vFront.x = pMt[0]->z.x;
	m_vFront.y = pMt[0]->z.y;
	m_vFront.z = pMt[0]->z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::RotationY( Sint32 Rot )
{
	static CMatrix Mt[2];
	static CMatrix *pMt[2] = { &Mt[0], &Mt[1] };

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	pMt[0]->x.x = m_vRight.x;  pMt[0]->x.y = m_vRight.y;  pMt[0]->x.z = m_vRight.z;  pMt[0]->x.w = 0;
	pMt[0]->y.x = m_vUp.x;     pMt[0]->y.y = m_vUp.y;     pMt[0]->y.z = m_vUp.z;     pMt[0]->y.w = 0;
	pMt[0]->z.x = m_vFront.x;  pMt[0]->z.y = m_vFront.y;  pMt[0]->z.z = m_vFront.z;  pMt[0]->z.w = 0;
	pMt[0]->w.x = 0;           pMt[0]->w.y = 0;           pMt[0]->w.z = 0;           pMt[0]->w.w = 1;

	pMt[1]->x.x = fCos;  pMt[1]->x.y = 0;  pMt[1]->x.z = -fSin;  pMt[1]->x.w = 0;
	pMt[1]->y.x =    0;  pMt[1]->y.y = 1;  pMt[1]->y.z =     0;  pMt[1]->y.w = 0;
	pMt[1]->z.x = fSin;  pMt[1]->z.y = 0;  pMt[1]->z.z =  fCos;  pMt[1]->z.w = 0;
	pMt[1]->w.x =    0;  pMt[1]->w.y = 0;  pMt[1]->w.z =     0;  pMt[1]->w.w = 1;

	Mt[0] *= Mt[1];

	m_vRight.x = pMt[0]->x.x;
	m_vRight.y = pMt[0]->x.y;
	m_vRight.z = pMt[0]->x.z;
	m_vUp.x    = pMt[0]->y.x;
	m_vUp.y    = pMt[0]->y.y;
	m_vUp.z    = pMt[0]->y.z;
	m_vFront.x = pMt[0]->z.x;
	m_vFront.y = pMt[0]->z.y;
	m_vFront.z = pMt[0]->z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::RotationZ( Sint32 Rot )
{
	static CMatrix Mt[2];
	static CMatrix *pMt[2] = { &Mt[0], &Mt[1] };

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	pMt[0]->x.x = m_vRight.x;  pMt[0]->x.y = m_vRight.y;  pMt[0]->x.z = m_vRight.z;  pMt[0]->x.w = 0;
	pMt[0]->y.x = m_vUp.x;     pMt[0]->y.y = m_vUp.y;     pMt[0]->y.z = m_vUp.z;     pMt[0]->y.w = 0;
	pMt[0]->z.x = m_vFront.x;  pMt[0]->z.y = m_vFront.y;  pMt[0]->z.z = m_vFront.z;  pMt[0]->z.w = 0;
	pMt[0]->w.x = 0;           pMt[0]->w.y = 0;           pMt[0]->w.z = 0;           pMt[0]->w.w = 1;

	pMt[1]->x.x =  fCos;  pMt[1]->x.y = fSin;  pMt[1]->x.z = 0;  pMt[1]->x.w = 0;
	pMt[1]->y.x = -fSin;  pMt[1]->y.y = fCos;  pMt[1]->y.z = 0;  pMt[1]->y.w = 0;
	pMt[1]->z.x =     0;  pMt[1]->z.y =    0;  pMt[1]->z.z = 1;  pMt[1]->z.w = 0;
	pMt[1]->w.x =     0;  pMt[1]->w.y =    0;  pMt[1]->w.z = 0;  pMt[1]->w.w = 1;

	Mt[0] *= Mt[1];

	m_vRight.x = pMt[0]->x.x;
	m_vRight.y = pMt[0]->x.y;
	m_vRight.z = pMt[0]->x.z;
	m_vUp.x    = pMt[0]->y.x;
	m_vUp.y    = pMt[0]->y.y;
	m_vUp.z    = pMt[0]->y.z;
	m_vFront.x = pMt[0]->z.x;
	m_vFront.y = pMt[0]->z.y;
	m_vFront.z = pMt[0]->z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::Pitching( Sint32 Rot )
{
	static CVector3D vTemp[3];
	vTemp[0] = m_vRight;
	vTemp[1] = m_vUp;
	vTemp[2] = m_vFront;

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	m_vUp.x		= (+fCos * vTemp[1].x) + (+fSin * vTemp[2].x);
	m_vUp.y		= (+fCos * vTemp[1].y) + (+fSin * vTemp[2].y);
	m_vUp.z		= (+fCos * vTemp[1].z) + (+fSin * vTemp[2].z);

	m_vFront.x	= (-fSin * vTemp[1].x) + (+fCos * vTemp[2].x);
	m_vFront.y	= (-fSin * vTemp[1].y) + (+fCos * vTemp[2].y);
	m_vFront.z	= (-fSin * vTemp[1].z) + (+fCos * vTemp[2].z);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::Heading( Sint32 Rot )
{
	static CVector3D vTemp[3];
	vTemp[0] = m_vRight;
	vTemp[1] = m_vUp;
	vTemp[2] = m_vFront;

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	m_vRight.x	= (+fCos * vTemp[0].x) + (-fSin * vTemp[2].x);
	m_vRight.y	= (+fCos * vTemp[0].y) + (-fSin * vTemp[2].y);
	m_vRight.z	= (+fCos * vTemp[0].z) + (-fSin * vTemp[2].z);

	m_vFront.x	= (+fSin * vTemp[0].x) + (+fCos * vTemp[2].x);
	m_vFront.y	= (+fSin * vTemp[0].y) + (+fCos * vTemp[2].y);
	m_vFront.z	= (+fSin * vTemp[0].z) + (+fCos * vTemp[2].z);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::Rolling( Sint32 Rot )
{
	static CVector3D vTemp[3];
	vTemp[0] = m_vRight;
	vTemp[1] = m_vUp;
	vTemp[2] = m_vFront;

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	m_vRight.x	= (+fCos * vTemp[0].x) + (+fSin * vTemp[1].x);
	m_vRight.y	= (+fCos * vTemp[0].y) + (+fSin * vTemp[1].y);
	m_vRight.z	= (+fCos * vTemp[0].z) + (+fSin * vTemp[1].z);

	m_vUp.x		= (-fSin * vTemp[0].x) + (+fCos * vTemp[1].x);
	m_vUp.y		= (-fSin * vTemp[0].y) + (+fCos * vTemp[1].y);
	m_vUp.z		= (-fSin * vTemp[0].z) + (+fCos * vTemp[1].z);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::RotationQuaternion( CQuaternion &Quat )
{
	CMatrix Mat = Quat;

	m_vRight.x	= Mat.x.x;
	m_vRight.y	= Mat.x.y;
	m_vRight.z	= Mat.x.z;

	m_vUp.x		= Mat.y.x;
	m_vUp.y		= Mat.y.y;
	m_vUp.z		= Mat.y.z;

	m_vFront.x	= Mat.z.x;
	m_vFront.y	= Mat.z.y;
	m_vFront.z	= Mat.z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::Translation( Float fPx, Float fPy, Float fPz )
{
	m_vPosition.Set( fPx, fPy, fPz );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::Scaling( Float fSx, Float fSy, Float fSz )
{
	m_vScale.Set( fSx, fSy, fSz );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::LookAt( CVector3D &vEye, CVector3D &vAt, CVector3D &vUp )
{
	static CVector3D vFront, vRight;

	//--------------------------------------------------------
	// カメラ視線
	//--------------------------------------------------------
	vFront.Sub( vAt, vEye );
	vFront.Normalize();

	//--------------------------------------------------------
	// 前方向が完全に真上か真下の時
	//--------------------------------------------------------
	if ( (vFront.y == 1.0) || (vFront.y == -1.0) )
	{
		// ＵＰベクトルを変えておく
		vUp.Set( 0, 0, -vFront.y );
	}

	//--------------------------------------------------------
	// カメラ右方向
	//--------------------------------------------------------
	vRight.Cross( vFront, vUp );
	vRight.Normalize();
	vRight.x = -vRight.x;
	vRight.y = -vRight.y;
	vRight.z = -vRight.z;

	//--------------------------------------------------------
	// 上方向
	//--------------------------------------------------------
	vUp.Cross( vFront, vRight );
	vUp.Normalize();

	//--------------------------------------------------------
	// コピー
	//--------------------------------------------------------
	m_vFront	= vFront;
	m_vUp		= vUp;
	m_vRight	= vRight;
	m_vPosition	= vEye;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::SetPosition( CVector3D &Pos )
{
	m_vPosition = Pos;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::SetFront( CVector3D &Vec )
{
	m_vFront = Vec;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::SetRight( CVector3D &Vec )
{
	m_vRight = Vec;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::SetUp( CVector3D &Vec )
{
	m_vUp = Vec;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetPosition( CVector3D &vPos )
{
	vPos = m_vPosition;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetFront( CVector3D &Vec )
{
	Vec = m_vFront;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetRight( CVector3D &Vec )
{
	Vec = m_vRight;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetUp( CVector3D &Vec )
{
	Vec = m_vUp;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetStyle( CMatrix &Mat )
{
	Mat = m_mStyle;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetStyleInverse( CMatrix &Mat )
{
	Mat = m_mStyleInverse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetTransform( CMatrix &Mat )
{
	Mat = m_mTransform;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStyle::GetTransformInverse( CMatrix &Mat )
{
	Mat = m_mTransformInverse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CStyle &CStyle::operator = ( const CStyle &In )
{
	TransformReset();

	m_mStyle			= In.m_mStyle;
	m_mStyleInverse		= In.m_mStyleInverse;
	m_mTransform		= In.m_mTransform;
	m_mTransformInverse	= In.m_mTransformInverse;

	m_vUp		= In.m_vUp;
	m_vRight	= In.m_vRight;
	m_vFront	= In.m_vFront;
	m_vPosition	= In.m_vPosition;
	m_vScale	= In.m_vScale;

	return *this;
}
