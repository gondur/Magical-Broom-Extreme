

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CCore.h"
#include "Math/Vector4D.h"
#include "Render/3D/CPrimitive3DBase.h"
#include "Render/CVertexBuffer.h"
#include "Render/CIndexBuffer.h"
#include "Render/CShader.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive3DBase::CPrimitive3DBase( CRender *pRender, CBaseMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
	, m_BumpMode	( TECHNIQUE_BUMPMAP_DISABLE )
	, m_ReflexMode	( TECHNIQUE_REFLEX_DISABLE )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive3DBase::~CPrimitive3DBase()
{
	wchar_t Temp[64] = L"";
	::StringCbPrintf( Temp, sizeof(Temp), L"0x%08X", (Uint64)this );
	Log_PrintTable( 0xFF0000, 0x000000, L"解放", m_Name, Temp );
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( Uint16 *pIndex, Uint32 IndexCount )
{
	if ( m_pIB == NULL ) return false;
	if ( !m_pIB->Push( pIndex, IndexCount ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( SVertex3DBase *pVtx, Uint32 Count )
{
	if ( m_pVB_Base == NULL ) return false;
	if ( !m_pVB_Base->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( SVertex3DTexture *pVtx, Uint32 Count )
{
	if ( m_pVB_Tex == NULL ) return false;
	if ( !m_pVB_Tex->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( SVertex3DLight *pVtx, Uint32 Count )
{
	if ( m_pVB_Light == NULL ) return false;
	if ( !m_pVB_Light->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( SVertex3DBump *pVtx, Uint32 Count )
{
	if ( m_pVB_Bump == NULL ) return false;
	if ( !m_pVB_Bump->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( SVertex3DAnimation *pVtx, Uint32 Count )
{
	if ( m_pVB_Animation == NULL ) return false;
	if ( !m_pVB_Animation->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Get( SVertex3DBase &Vtx, Uint32 Index )
{
	if ( m_pVB_Base == NULL ) return false;
	if ( !m_pVB_Base->Get( &Vtx, Index ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Get( SVertex3DTexture &Vtx, Uint32 Index )
{
	if ( m_pVB_Tex == NULL ) return false;
	if ( !m_pVB_Tex->Get( &Vtx, Index ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Get( SVertex3DLight &Vtx, Uint32 Index )
{
	if ( m_pVB_Light == NULL ) return false;
	if ( !m_pVB_Light->Get( &Vtx, Index ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Get( SVertex3DBump &Vtx, Uint32 Index )
{
	if ( m_pVB_Bump == NULL ) return false;
	if ( !m_pVB_Bump->Get( &Vtx, Index ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Get( SVertex3DAnimation &Vtx, Uint32 Index )
{
	if ( m_pVB_Animation == NULL ) return false;
	if ( !m_pVB_Animation->Get( &Vtx, Index ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive3DBase::GetVertexCount( void )
{
	if ( m_pVB_Base == NULL ) return 0;

	return m_pVB_Base->GetRequestedCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive3DBase::GetIndexCount( void )
{
	if ( m_pIB == NULL ) return 0;

	return m_pIB->GetRequestedCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3DBase::Begin( void )
{
	// 各情報初期化
	if ( m_pVB_Base      != NULL ) m_pVB_Base->Flush();
	if ( m_pVB_Tex       != NULL ) m_pVB_Tex->Flush();
	if ( m_pVB_Light     != NULL ) m_pVB_Light->Flush();
	if ( m_pVB_Bump      != NULL ) m_pVB_Bump->Flush();
	if ( m_pVB_Animation != NULL ) m_pVB_Animation->Flush();
	if ( m_pIB           != NULL ) m_pIB->Flush();
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファをアップデートします

	@param lPrim	[fIn] プリミティブハンドル
*/
//-----------------------------------------------------------------------------------
void CPrimitive3DBase::End( void )
{
	if ( m_pVB_Base      != NULL ) m_pVB_Base->Update();
	if ( m_pVB_Tex       != NULL ) m_pVB_Tex->Update();
	if ( m_pVB_Light     != NULL ) m_pVB_Light->Update();
	if ( m_pVB_Bump      != NULL ) m_pVB_Bump->Update();
	if ( m_pVB_Animation != NULL ) m_pVB_Animation->Update();
	if ( m_pIB           != NULL ) m_pIB->Update();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3DBase::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3DBase::OnResetDevice( void )
{
}

#endif // ENABLE_3D
