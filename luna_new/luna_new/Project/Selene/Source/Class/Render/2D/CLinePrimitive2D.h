

#ifndef ___SELENE__CLINEPRIMITIVE2D___
#define ___SELENE__CLINEPRIMITIVE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Render/CRender.h"
#include "Render/2D/CPrimitive2DBase.h"
#include "Interface/Render/2D/ILinePrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
	*/
	class CLinePrimitive2D : public CPrimitive2DBase, public ILinePrimitive2D
	{
		enum { LINE_POINT_COUNT = 2 };

	protected:
		virtual Uint32 ScissorPolygon( SVertex2D *pDst, SVertex2D *pSrc );
		virtual Uint32 ScissorPolygonLeft( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum );
		virtual Uint32 ScissorPolygonTop( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum );
		virtual Uint32 ScissorPolygonRight( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum );
		virtual Uint32 ScissorPolygonBottom( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CLinePrimitive2D( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CLinePrimitive2D();

		virtual Bool Create( Uint32 LineMax );

		virtual Bool Push( SLineVertex2D *pLine, Uint32 Count );
		virtual void Rendering( void );
		virtual void Begin( void );
		virtual void End( void );
	};
}


#endif // ___SELENE__CLINEPRIMITIVE2D___


