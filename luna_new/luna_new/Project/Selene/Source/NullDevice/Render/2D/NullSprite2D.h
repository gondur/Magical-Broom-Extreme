

#ifndef ___SELENE_NULLSPRITE2D___
#define ___SELENE_NULLSPRITE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/ISprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullSprite2D : public ISprite2D
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

		virtual void DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color )
		{
		}

		virtual void DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle )
		{
		}

		virtual void DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src )
		{
		}

		virtual void CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
		{
		}

		virtual void CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
		{
		}
	};
}


#endif // ___SELENE_NULLSPRITE2D___

