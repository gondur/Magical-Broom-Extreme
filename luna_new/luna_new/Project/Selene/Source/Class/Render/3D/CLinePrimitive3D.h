

#ifndef ___SELENE__CLINEPRIMITIVE3D___
#define ___SELENE__CLINEPRIMITIVE3D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Scene/CSceneObject.h"
#include "Render/CRender.h"
#include "Render/3D/CPrimitive3DBase.h"
#include "Interface/Render/3D/ILinePrimitive3D.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CRender;

	class CLinePrimitive3D : public CPrimitive3DBase, public CSceneObject, public ILinePrimitive3D
	{
		friend CRender;
		friend CSceneManager;

	protected:
		CStyle m_Style;										///< Žp¨§Œä—p
		CVector3D m_vCenter;
		CVector4D m_vMaterialColor;

	protected:
		virtual void RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD );
		virtual Bool Create( Uint32 VertexMax, Bool IsDynamic );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CLinePrimitive3D( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CLinePrimitive3D();

		virtual Sint32 Rendering( void );

		virtual Bool Push( SPrimitive3DVertexLine *pLine, Uint32 LineCount );

		virtual void Begin( void );
		virtual void End( void );

		virtual void SetTransform( CStyle &Style );
		virtual void SetMaterialColor( CColor Color );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CLINEPRIMITIVE3D___


