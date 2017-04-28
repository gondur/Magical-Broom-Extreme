

#ifndef ___SELENE__VECTOR3D___
#define ___SELENE__VECTOR3D___


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
	class SELENE_DLL_API CVector3D
	{
	public:
		Float x;
		Float y;
		Float z;

	public:
		CVector3D();
		CVector3D( const CVector3D &v );
		CVector3D( Float fPx, Float fPy, Float fPz );

		void Add( CVector3D &In1, CVector3D &In2 );
		void Sub( CVector3D &In1, CVector3D &In2 );
		void Set( Float fPx, Float fPy, Float fPz );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector3D &In );

		void Normalize( void );
		void Cross( CVector3D &In1, CVector3D &In2 );
		void Reflect( CVector3D &In1, CVector3D &In2 );
		void TransformNormal( CVector3D &In1, CMatrix &In2 );
		void TransformCoord( CVector3D &In1, CMatrix &In2 );
		void TransformProjection( CVector3D &In1, CMatrix &In2 );

		void Normalize( CVector3D &In );
		void Cross( CVector3D &In );
		void Reflect( CVector3D &In );
		void TransformNormal( CMatrix &In );
		void TransformCoord( CMatrix &In );
		void TransformProjection( CMatrix &In );

		void RotationX( Sint32 Angle );
		void RotationY( Sint32 Angle );
		void RotationZ( Sint32 Angle );
		void RotationAxis( Sint32 Angle, CVector3D &Axis );
		void Scaling( Float sx, Float sy, Float sz );
		void Translation( Float px, Float py, Float pz );

		CVector3D& operator += ( const CVector3D& );
		CVector3D& operator -= ( const CVector3D& );
		CVector3D& operator *= ( Float );
		CVector3D& operator /= ( Float );

		CVector3D operator + () const;
		CVector3D operator - () const;

		CVector3D operator + ( const CVector3D& ) const;
		CVector3D operator - ( const CVector3D& ) const;
		CVector3D operator * ( Float ) const;
		CVector3D operator / ( Float ) const;
	};
}


#endif // ___SELENE__VECTOR3D___
