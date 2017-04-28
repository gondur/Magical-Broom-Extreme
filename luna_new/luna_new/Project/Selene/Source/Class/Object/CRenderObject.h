

#ifndef ___SELENE__RENDEROBJECT___
#define ___SELENE__RENDEROBJECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObject.h"
#include "Object/CBaseMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CRender;

	class CRenderObject : public CDeviceObject
	{
	protected:
		CRender *m_pRender;

	public:
		CRenderObject( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CRenderObject();

	public:
		virtual void OnLostDevice( void )			= 0;
		virtual void OnResetDevice( void )			= 0;

	public:
		virtual CRender *GetRenderPointer( void ) const;
	};
}

#endif // ___SELENE__RENDEROBJECT___


