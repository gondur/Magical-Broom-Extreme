

#ifndef ___SELENE__NULLPRIMITIVE2D___
#define ___SELENE__NULLPRIMITIVE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/IPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullPrimitive2D : public IPrimitive2D
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Uint32 Release( void )
		{
			return 0;
		}

		virtual Uint32 AddRef( void )
		{
			return 0;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )
		{
			return false;
		}

		virtual void Rendering( void )
		{
		}

		virtual void Square( CRect2D<Sint32> &DstRect, CColor Color )
		{
		}

		virtual void SquareRotate( CRect2D<Sint32> &DstRect, CColor Color, Sint32 Angle )
		{
		}

		virtual void Polygon( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num )
		{
		}

		virtual void PolygonRotate( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )
		{
		}

		virtual void Ring( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )
		{
		}

		virtual void RingRotate( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )
		{
		}
	};
}


#endif // ___SELENE__NULLPRIMITIVE2D___


