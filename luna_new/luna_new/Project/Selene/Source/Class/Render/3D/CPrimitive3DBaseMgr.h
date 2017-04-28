

#ifndef ___SELENE__PRIMITIVE3DBASEMGR___
#define ___SELENE__PRIMITIVE3DBASEMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObjectMgr.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CPrimitive3DBaseMgr : public CDeviceObjectMgr
	{
	public:
		CPrimitive3DBaseMgr( CDevice *pDevice );
		virtual ~CPrimitive3DBaseMgr();
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__PRIMITIVE3DBASEMGR___

