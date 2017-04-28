

#ifndef ___SELENE__CMODEL___
#define ___SELENE__CMODEL___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Object/CRenderObject.h"
#include "Interface/Render/Model/IModel.h"
#include "Math/Style.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CFrame;
	class CMesh;

	class CModel : public CRenderObject, public IModel
	{
	private:
		CStyle m_Style;
		CFrame **m_pFrameList;
		CMesh **m_pMeshList;
		Uint32 m_FrameListCount;
		Uint32 m_MeshListCount;
		CBaseMgr *m_pMeshMgr;

	private:
		virtual void OnLostDevice( void ){}
		virtual void OnResetDevice( void ){}

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CModel( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CModel();

		virtual void CreateFrameList( Uint32 FrameCount );
		virtual void CreateMeshList( Uint32 MeshCount );

		virtual CFrame *GetFramePointer( Uint32 Index );
		virtual CMesh *GetMeshPointer( Uint32 Index );

		virtual void UpdateMesh( void );

	public:
		virtual void SetTransform( CStyle &Style );
		virtual void Rendering( void );

		virtual Bool GetFrame( Uint32 FrameIndex, IFrame *&pFrame );
		virtual Uint32 GetFrameCount( void );
		virtual Bool GetMesh( Uint32 MeshIndex, IMesh *&pMesh );
		virtual Uint32 GetMeshCount( void );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CMODEL___


