

#ifndef ___SELENE__PRIMITIVE3DBASE___
#define ___SELENE__PRIMITIVE3DBASE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CRenderPrimitiveObject.h"
#include "Render/CRender.h"
#include "Render/CRenderData.h"
#include "Math/Matrix.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CPrimitive3DBaseMgr;
	class CShader;

	/**
		@brief プリミティブクラス

		２Ｄ平面状に単一のポリゴンを描画するためのクラスです。
		このクラス自身は単純なポリゴンを描画するだけのものですが、
		SeleneEffectクラスやSeleneSpriteクラスがより扱いやすいような
		ラッパーになっており、直接このクラスを使用するのは
		凝ったエフェクトを使用したいときなどだけになると思います。
	*/
	class CPrimitive3DBase : public CRenderPrimitiveObject
	{
		friend CPrimitive3DBaseMgr;

	protected:
		CRenderData m_RenderData;
		eTechniqueBumpmap m_BumpMode;
		eTechniqueReflex m_ReflexMode;

	protected:
		CPrimitive3DBase( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CPrimitive3DBase();

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

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
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__PRIMITIVE3DBASE___


