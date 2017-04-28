

#ifndef ___SELENE__CSCENEOBJECT___
#define ___SELENE__CSCENEOBJECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"
#include "Render/CRenderData.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CSceneManager;
	/**
		@brief シーン管理用オブジェクト
		@author 葉迩倭
	*/
	class CSceneObject
	{
		friend CSceneManager;

	protected:
		CSceneObject();
		virtual ~CSceneObject();

		virtual Sint32 Rendering( void )																							= 0;
		virtual void RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD )	= 0;
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CSCENEOBJECT___


