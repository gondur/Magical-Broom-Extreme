

#ifndef ___SELENE__SURFACEMGR___
#define ___SELENE__SURFACEMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObjectMgr.h"
#include "Core/CDevice.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �}�e���A���Ǘ��N���X
		@author �t���`
	*/
	class CSurfaceMgr : public CDeviceObjectMgr
	{
	protected:

	public:
		CSurfaceMgr( CDevice *pDevice );
		virtual ~CSurfaceMgr();

		virtual CSurface *CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual CSurface *CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format, CSurface *pCopyTarget );
	};
}

#endif // ___SELENE__SURFACEMGR___

