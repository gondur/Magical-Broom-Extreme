

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Render/Model/CModel.h"
#include "Render/Model/CFrame.h"
#include "Render/Model/CMesh.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModel::CModel( CRender *pRender, CBaseMgr *pMgr ) : CRenderObject( pRender, pMgr )
	, m_FrameListCount	( 0 )
	, m_MeshListCount	( 0 )
	, m_pFrameList		( NULL )
	, m_pMeshList		( NULL )
	, m_pMeshMgr		( NULL )
{
	SetName( L"モデル" );

	m_pMeshMgr = new CBaseMgr( pRender->GetDevicePointer() );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModel::~CModel()
{
	Uint32 Max;
	// フレーム解放
	Max = m_FrameListCount;
	for ( Uint32 i = 0; i < Max; i++ )
	{
		SAFE_RELEASE( m_pFrameList[i] );
	}
	SAFE_DELETE_ARRAY( m_pFrameList );
	// メッシュ解放
	Max = m_MeshListCount;
	for ( Uint32 i = 0; i < Max; i++ )
	{
		SAFE_RELEASE( m_pMeshList[i] );
	}
	SAFE_DELETE_ARRAY( m_pMeshList );

	SAFE_DELETE( m_pMeshMgr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::CreateFrameList( Uint32 FrameCount )
{
	m_FrameListCount = FrameCount;
	m_pFrameList = new CFrame * [ FrameCount ];
	// フレーム生成
	for ( Uint32 i = 0; i < FrameCount; i++ )
	{
		m_pFrameList[i] = new CFrame();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::CreateMeshList( Uint32 MeshCount )
{
	m_MeshListCount = MeshCount;
	m_pMeshList = new CMesh * [ MeshCount ];
	// メッシュ生成
	for ( Uint32 i = 0; i < MeshCount; i++ )
	{
		m_pMeshList[i] = new CMesh( GetRenderPointer(), m_pMeshMgr );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFrame *CModel::GetFramePointer( Uint32 Index )
{
	return m_pFrameList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh *CModel::GetMeshPointer( Uint32 Index )
{
	return m_pMeshList[Index];
}	
	
//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::UpdateMesh( void )
{
	Uint32 Max = m_MeshListCount;
	for ( Uint32 i = 0; i < Max; i++ )
	{
		m_pMeshList[i]->UpdateStream();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::SetTransform( CStyle &Style )
{
	m_Style = Style;

	CMatrix mWorld;
	m_Style.GetTransform( mWorld );

	m_pFrameList[0]->UpdateTransform( mWorld );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::Rendering( void )
{
	Uint32 Max = m_MeshListCount;
	for ( Uint32 i = 0; i < Max; i++ )
	{
		m_pMeshList[i]->Rendering();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModel::GetFrame( Uint32 FrameIndex, IFrame *&pFrame )
{
	if ( FrameIndex < m_FrameListCount )
	{
		pFrame = m_pFrameList[FrameIndex];
		pFrame->AddRef();
		return true;
	}
	else
	{
		pFrame = NULL;
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CModel::GetFrameCount( void )
{
	return m_FrameListCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModel::GetMesh( Uint32 MeshIndex, IMesh *&pMesh )
{
	if ( MeshIndex < m_MeshListCount )
	{
		pMesh = m_pMeshList[MeshIndex];
		pMesh->AddRef();
		return true;
	}
	else
	{
		pMesh = NULL;
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CModel::GetMeshCount( void )
{
	return m_MeshListCount;
}

#endif // ENABLE_3D