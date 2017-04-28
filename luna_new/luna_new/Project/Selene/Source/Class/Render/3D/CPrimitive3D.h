

#ifndef ___SELENE__CPRIMITIVE3D___
#define ___SELENE__CPRIMITIVE3D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Scene/CSceneObject.h"
#include "Render/CRender.h"
#include "Render/3D/CPrimitive3DBase.h"
#include "Interface/Render/3D/IPrimitive3D.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CRender;

	class CPrimitive3D : public CPrimitive3DBase, public CSceneObject, public IPrimitive3D
	{
		friend CRender;
		friend CSceneManager;

	protected:
		CVector3D m_vCenter;
		CVector4D m_vMaterialColor;
		CVector4D m_vSpecularColor;
		Float m_fRefractive;
		Float m_fRoughly;
		CStyle m_Style;										///< 姿勢制御用
		Sint32 m_BoneCount;									///< ボーン数
		CMatrix m_mBoneOffset[SHADER_BONE_MAX];				///< ボーンオフセット行列
		CMatrix m_mBone[SHADER_BONE_MAX];					///< ボーン行列

	protected:
		virtual void RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD );
		virtual Bool Create( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CPrimitive3D( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CPrimitive3D();

		virtual Sint32 Rendering( void );

		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount );

		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count );
		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count );

		virtual Bool Get( SVertex3DBase &Vtx, Uint32 Index );
		virtual Bool Get( SVertex3DTexture &Vtx, Uint32 Index );
		virtual Bool Get( SVertex3DLight &Vtx, Uint32 Index );
		virtual Bool Get( SVertex3DBump &Vtx, Uint32 Index );
		virtual Bool Get( SVertex3DAnimation &Vtx, Uint32 Index );

		virtual Uint32 GetVertexCount( void );
		virtual Uint32 GetIndexCount( void );

		virtual void Begin( void );
		virtual void End( void );

		virtual void SetBoneCount( Sint32 BoneCount );
		virtual void SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix );
		virtual void SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix );

		virtual void SetTransform( CStyle &Style );
		virtual void SetMaterialColor( CColor Color );
		virtual void SetSpecularColor( CColor Color );
		virtual void SetSpecularRefractive( Float fRefractive );
		virtual void SetSpecularRoughly( Float fRoughly );
	};
}

#endif ENABLE_3D

#endif // ___SELENE__CPRIMITIVE3D___


