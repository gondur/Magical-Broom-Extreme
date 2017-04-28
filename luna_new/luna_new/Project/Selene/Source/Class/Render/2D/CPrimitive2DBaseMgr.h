

#ifndef ___SELENE__PRIMITIVE2DBASEMGR___
#define ___SELENE__PRIMITIVE2DBASEMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CPrimitive2DBaseMgr : public CDeviceObjectMgr
	{
	public:
		CPrimitive2DBaseMgr( CDevice *pDevice );
		virtual ~CPrimitive2DBaseMgr();

		virtual void SetScissoring( RECT *pRect );
	};
}

#endif // ___SELENE__PRIMITIVE2DBASEMGR___

