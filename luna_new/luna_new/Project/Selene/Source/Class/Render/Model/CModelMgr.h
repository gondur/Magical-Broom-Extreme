

#ifndef ___SELENE__MODELMGR___
#define ___SELENE__MODELMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Core/CDevice.h"
#include "Object/CDeviceObjectMgr.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CModel;
	class CRender;

	class CModelMgr : public CDeviceObjectMgr
	{
	protected:

	public:
		CModelMgr( CDevice *pDevice );
		virtual ~CModelMgr();

		CModel *SearchInstance( const wchar_t *pFileName );

		virtual CModel *CreateFromFile( const wchar_t *pFileName, CRender *pRender );
		virtual CModel *CreateFromMemory( const void *pData, Uint32 Size, CRender *pRender );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__MODELMGR___

