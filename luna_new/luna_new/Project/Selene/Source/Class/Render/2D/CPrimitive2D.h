

#ifndef ___SELENE__CPRIMITIVE2D___
#define ___SELENE__CPRIMITIVE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Render/CRender.h"
#include "Render/2D/CPrimitive2DBase.h"
#include "Interface/Render/2D/IPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
	*/
	class CPrimitive2D : public CPrimitive2DBase, public IPrimitive2D
	{
		enum { PRIMITIVE_POINT_COUNT = 3 };

	protected:
		virtual Uint32 ScissorPolygon( SVertex2DTex *pDst, SVertex2DTex *pSrc );
		virtual Uint32 ScissorPolygonLeft( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum );
		virtual Uint32 ScissorPolygonTop( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum );
		virtual Uint32 ScissorPolygonRight( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum );
		virtual Uint32 ScissorPolygonBottom( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CPrimitive2D( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CPrimitive2D();

		virtual Bool Create( Uint32 PrimitiveMax );

		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count );
		virtual void Begin( void );
		virtual void End( void );
		virtual void Rendering( void );

		virtual void Square( CRect2D<Sint32> &DstRect, CColor Color );
		virtual void SquareRotate( CRect2D<Sint32> &DstRect, CColor Color, Sint32 Angle );

		virtual void Polygon( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num );
		virtual void PolygonRotate( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle );

		virtual void Ring( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num );
		virtual void RingRotate( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle );
	};
}


#endif // ___SELENE__CPRIMITIVE2D___


