

#ifndef ___SELENE__VECTOR4D___
#define ___SELENE__VECTOR4D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief ベクトル演算クラス
	*/
	class SELENE_DLL_API CVector4D
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		CVector4D();
		CVector4D( const CVector3D &v );
		CVector4D( const CVector4D &v );
		CVector4D( Float fPx, Float fPy, Float fPz, Float fPw = 1.0f );

		void Add( CVector4D &In1, CVector4D &In2 );
		void Sub( CVector4D &In1, CVector4D &In2 );
		void Set( Float fPx, Float fPy, Float fPz );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector4D &In );

		void Normalize( void );
		void Cross( CVector4D &In1, CVector4D &In2 );
		void Reflect( CVector4D &In1, CVector4D &In2 );
		void TransformNormal( CVector4D &In1, CMatrix &In2 );
		void TransformCoord( CVector4D &In1, CMatrix &In2 );
		void TransformProjection( CVector4D &In1, CMatrix &In2 );

		void Normalize( CVector4D &In );
		void Cross( CVector4D &In );
		void Reflect( CVector4D &In );
		void TransformNormal( CMatrix &In );
		void TransformCoord( CMatrix &In );
		void TransformProjection( CMatrix &In );

		void RotationX( Sint32 Angle );
		void RotationY( Sint32 Angle );
		void RotationZ( Sint32 Angle );
		void RotationAxis( Sint32 Angle, CVector3D &Axis );
		void Scaling( Float sx, Float sy, Float sz );
		void Translation( Float px, Float py, Float pz );

		CVector4D& operator += ( const CVector4D& );
		CVector4D& operator -= ( const CVector4D& );
		CVector4D& operator *= ( Float );
		CVector4D& operator /= ( Float );

		CVector4D operator + () const;
		CVector4D operator - () const;

		CVector4D operator + ( const CVector4D& ) const;
		CVector4D operator - ( const CVector4D& ) const;
		CVector4D operator * ( Float ) const;
		CVector4D operator / ( Float ) const;
	};
}

#endif // ___SELENE__VECTOR4D___
