

#ifndef ___SELENE__CMESH___
#define ___SELENE__CMESH___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Scene/CSceneObject.h"
#include "Object/CRenderPrimitiveObject.h"
#include "Interface/Render/Model/IMesh.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CRender;
	class CFrame;
	class CMaterial;

	class CMesh : public CRenderPrimitiveObject, public IMesh, public CSceneObject
	{
		friend CRender;
		friend CSceneManager;

	protected:
		CRenderData m_RenderData;
		CFrame *m_pParentFrame;
		CMaterial *m_pMaterials;
		Uint32 m_MaterialCount;
		CSceneBounding m_Bounding;
		Uint32 m_VertexFlag;
		eTechniqueBumpmap m_BumpMode;
		eTechniqueReflex m_ReflexMode;
		Float m_fParallaxDepth;
		ILinePrimitive3D *m_pLineNormal;
		ILinePrimitive3D *m_pLineBounding;
		Sint32 m_RenderID;

	protected:
		virtual void RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD );

	public:
		CMesh( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CMesh();

		virtual void CreateMaterialList( Uint32 MaterialCount );
		virtual void SetMaterial( Uint32 Index, CMaterial &Mtrl );
		virtual void SetBouding( CSceneBounding &Bound );

		virtual void CreateVertex( eVertexElement Type, Uint32 Count );
		virtual void CreateIndex( Uint32 Count );
		virtual void UpdateStream( void );

		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count );

		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount );

		virtual Bool GetSupportTexture( void );

		virtual void SetParentFrame( CFrame *pFrame );

		virtual Sint32 Rendering( void );

		virtual void OnLostDevice( void ){}
		virtual void OnResetDevice( void ){}

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void ConvertReflexMesh( void );
		virtual void ConvertBumpMesh( ITexture *pTexNormal );
		virtual void ConvertParallaxMesh( ITexture *pTexNormal, Float fParallaxDepth );
		virtual Uint32 GetMaterialCount( void );
		virtual void SetSpecularColor( Uint32 MaterialIndex, CColor Color );
		virtual void SetSpecularRefractive( Uint32 MaterialIndex, Float fRefractive );
		virtual void SetSpecularRoughly( Uint32 MaterialIndex, Float fRoughly );
		virtual void NormalVisible( Float fLength );
		virtual void BoundingVisible( void );
		virtual Sint32 GetRenderID( void );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CMESH___


