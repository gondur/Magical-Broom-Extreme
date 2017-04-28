

#ifndef ___SELENE__CPOINTPRIMITIVE2D___
#define ___SELENE__CPOINTPRIMITIVE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Render/CRender.h"
#include "Render/2D/CPrimitive2DBase.h"
#include "Interface/Render/2D/IPointPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
	*/
	class CPointPrimitive2D : public CPrimitive2DBase, public IPointPrimitive2D
	{
	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CPointPrimitive2D( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CPointPrimitive2D();

		virtual Bool Create( Uint32 PointMax );

		virtual Bool Push( SVertex2D *pPoint, Uint32 Count );
		virtual void Rendering( void );
		virtual void Begin( void );
		virtual void End( void );
	};
}


#endif // ___SELENE__CPOINTPRIMITIVE2D___


