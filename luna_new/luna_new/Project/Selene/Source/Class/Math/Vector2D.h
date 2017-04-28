

#ifndef ___SELENE__VECTOR2D___
#define ___SELENE__VECTOR2D___


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
	class SELENE_DLL_API CVector2D
	{
	public:
		Float x;
		Float y;

	public:
		CVector2D();
		CVector2D( const CVector2D &v );
		CVector2D( Float fPx, Float fPy );

		void Add( CVector2D &In1, CVector2D &In2 );
		void Sub( CVector2D &In1, CVector2D &In2 );
		void Set( Float fPx, Float fPy );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector2D &In );
		void Reflect( CVector2D &In1, CVector2D &In2 );

		void Normalize( void );
		Float Cross( CVector2D &In1, CVector2D &In2 );

		void Normalize( CVector2D &In );
		Float Cross( CVector2D &In );
		void Reflect( CVector2D &In );

		void Scaling( Float sx, Float sy );
		void Translation( Float px, Float py );

		CVector2D& operator += ( const CVector2D& );
		CVector2D& operator -= ( const CVector2D& );
		CVector2D& operator *= ( Float );
		CVector2D& operator /= ( Float );

		// unary operators
		CVector2D operator + () const;
		CVector2D operator - () const;

		// binary operators
		CVector2D operator + ( const CVector2D& ) const;
		CVector2D operator - ( const CVector2D& ) const;
		CVector2D operator * ( Float ) const;
		CVector2D operator / ( Float ) const;
	};
}


#endif // ___SELENE__VECTOR2D___
