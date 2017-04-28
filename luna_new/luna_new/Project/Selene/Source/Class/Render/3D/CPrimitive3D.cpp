

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Scene/CSceneManager.h"
#include "Surface/CTexture.h"
#include "Render/3D/CPrimitive3D.h"
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
CPrimitive3D::CPrimitive3D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive3DBase( pRender, pMgr )
	, m_vMaterialColor		( 1.0f, 1.0f, 1.0f, 1.0f )
	, m_vSpecularColor		( 0.5f, 0.5f, 0.5f, 0.5f )
	, m_fRefractive			( 20.0f * 20.0f )
	, m_fRoughly			( 0.5f * 0.5f )
	, m_vCenter				( 0.0f, 0.0f, 0.0f )
	, m_BoneCount			( 0 )
{
	SetName( L"3Dプリミティブ" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive3D::~CPrimitive3D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Create( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	Bool bRet = true;

	try
	{
		//--------------------------------------------------------------
		// フラグチェック
		//--------------------------------------------------------------
		if ( (VertexFlag & VERTEX_ELEMENT_SPRITE) != 0 )
		{
			throw L"VERTEX_ELEMENT_SPRITEフラグはサポートされていません";
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DBASE) == 0 )
		{
			throw L"VERTEX_ELEMENT_3DBASEフラグがありません";
		}

		//--------------------------------------------------------------
		// ポリゴンタイプ
		//--------------------------------------------------------------
		m_RenderData.SetPolygonType( VertexFlag );

		//--------------------------------------------------------------
		// 頂点バッファ
		//--------------------------------------------------------------
		if ( (VertexFlag & VERTEX_ELEMENT_3DBASE) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBASE );
			m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Base == NULL )
			{
				throw L"頂点バッファの生成に失敗";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DTEXTURE) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DTEXTURE );
			m_pVB_Tex = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Tex == NULL )
			{
				throw L"頂点バッファの生成に失敗";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DLIGHT) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DLIGHT );
			m_pVB_Light = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Light == NULL )
			{
				throw L"頂点バッファの生成に失敗";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DBUMP) != 0 )
		{
			m_BumpMode = TECHNIQUE_BUMPMAP_ENABLE;
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBUMP );
			m_pVB_Bump = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Bump == NULL )
			{
				throw L"頂点バッファの生成に失敗";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DANIMATION) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DANIMATION );
			m_pVB_Animation = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Animation == NULL )
			{
				throw L"頂点バッファの生成に失敗";
			}
		}

		//--------------------------------------------------------------
		// インデックスバッファ
		//--------------------------------------------------------------
		m_pIB = GetRenderPointer()->CreateIndexBuffer( IndexMax, IsDynamic );
		if ( m_pIB == NULL )
		{
			throw L"インデックスバッファの生成に失敗";
		}

		//--------------------------------------------------------------
		// 頂点ストリーム
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VertexFlag );
		if ( m_pVS == NULL )
		{
			throw L"頂点ストリームの生成に失敗";
		}

		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"0x%08X", (Uint32)this );
		Log_PrintLine( 0x0000000, Temp );
	}
	catch ( const wchar_t *pErrMsg )
	{
		Log_PrintStrong( 0xFF0000, pErrMsg );
		bRet = false;
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return bRet;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( Uint16 *pIndex, Uint32 IndexCount )
{
	return CPrimitive3DBase::Push( pIndex, IndexCount );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( SVertex3DBase *pVtx, Uint32 Count )
{
	for ( Uint32 i = 0; i < Count; i++ )
	{
		m_vCenter += pVtx[i].Pos;
	}

	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( SVertex3DTexture *pVtx, Uint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( SVertex3DLight *pVtx, Uint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( SVertex3DBump *pVtx, Uint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( SVertex3DAnimation *pVtx, Uint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Get( SVertex3DBase &Vtx, Uint32 Index )
{
	return CPrimitive3DBase::Get( Vtx, Index );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Get( SVertex3DTexture &Vtx, Uint32 Index )
{
	return CPrimitive3DBase::Get( Vtx, Index );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Get( SVertex3DLight &Vtx, Uint32 Index )
{
	return CPrimitive3DBase::Get( Vtx, Index );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Get( SVertex3DBump &Vtx, Uint32 Index )
{
	return CPrimitive3DBase::Get( Vtx, Index );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Get( SVertex3DAnimation &Vtx, Uint32 Index )
{
	return CPrimitive3DBase::Get( Vtx, Index );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive3D::GetVertexCount( void )
{
	return CPrimitive3DBase::GetVertexCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive3D::GetIndexCount( void )
{
	return CPrimitive3DBase::GetIndexCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::Begin( void )
{
	CPrimitive3DBase::Begin();

	m_vCenter = CVector3D(0.0f,0.0f,0.0f);
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファをアップデートします

	@param lPrim	[fIn] プリミティブハンドル
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::End( void )
{
	CPrimitive3DBase::End();

	if ( GetVertexCount() > 0 )
	{
		m_vCenter /= toF(GetVertexCount());
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetBoneCount( Sint32 BoneCount )
{
	m_BoneCount = BoneCount;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix )
{
	m_mBoneOffset[No] = Matrix;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix )
{
	m_mBone[No] = Matrix;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive3D::Rendering( void )
{
	CSceneManager *pScene = GetRenderPointer()->GetSceneManagerPointer();
	if ( pScene == NULL ) return -1;

	//-------------------------------------------------------------------------------------
	// レンダリング
	//-------------------------------------------------------------------------------------
	if ( m_pIB->GetCount() >= 3 )
	{
		CRenderData &RD = m_RenderData;

		for ( Uint32 i = 0; i < MESH_TEXTURE_MAX; i++ )
		{
			RD.Material[0].pTexture[i] = GetRenderPointer()->GetTexture( i );
		}
		RD.Material[0].vMaterialColor = m_vMaterialColor;
		RD.Material[0].vSpecularColor = m_vSpecularColor;
		RD.Material[0].fRefractive = m_fRefractive;
		RD.Material[0].fRoughly = m_fRoughly;
		RD.MaterialCount = 1;

		RD.IsCullTest = false;

		RD.BumpMode = m_BumpMode;
		RD.ReflexMode = m_ReflexMode;

		m_Style.GetTransform( RD.mWorld );
		m_Style.GetTransformInverse( RD.mWorldInverse );
		RD.BoneCount = m_BoneCount;
		for ( Uint32 i = 0; i < RD.BoneCount; i++ )
		{
			CMatrix mTemp;
			mTemp.Multiply( m_mBoneOffset[i], m_mBone[i] );

			RD.mBone[i] = mTemp;
		}

		return pScene->AddObject( this, RD, m_vCenter );
	}

	return -1;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD )
{
	Uint32 PrimitiveCount = m_pIB->GetCount() / 3;
	Uint32 VertexCount = m_pVB_Base->GetCount();

	// ステート
	GetRenderPointer()->StatePush();
	GetRenderPointer()->SetTextureAddressType( 0, TEXTURE_ADDRESS_CLAMP );

	// テクスチャなし
	if ( m_pVB_Tex == NULL )
	{
		GetRenderPointer()->SetTextureOperationType( 1, TEXTURE_OP_NONE );
		GetRenderPointer()->SetTexture( 0, NULL );
		GetRenderPointer()->SetTexture( 1, NULL );
	}

	// データ
	GetRenderPointer()->SetStream( m_pVS );
	GetRenderPointer()->SetIndex( m_pIB );

	// 頂点
	GetRenderPointer()->SetVertex( 0, m_pVB_Base );
	GetRenderPointer()->SetVertex( 1, m_pVB_Tex );
	GetRenderPointer()->SetVertex( 2, m_pVB_Light );
	GetRenderPointer()->SetVertex( 3, m_pVB_Bump );
	GetRenderPointer()->SetVertex( 4, m_pVB_Animation );

	// 視差深度
	if ( SD.hParallaxDepth != NULL )
	{
		SD.pShader->SetFloat( SD.hParallaxDepth, 0.0f );
	}

	// パラメーター更新
	SD.pShader->UpdateParameter();

	Uint32 Pass;
	if ( SD.pShader->Begin( &Pass ) )
	{
		// パス分の処理
		for ( Uint32 i = 0; i < Pass; i++ )
		{
			// パス開始
			SD.pShader->BeginPass( i );
			// レンダリング
			GetRenderPointer()->DrawIndexedPrimitive( PRIMITIVE_TRIANGLE, VertexCount, PrimitiveCount );
			// パス終了
			SD.pShader->EndPass();
			// 描画ポリゴン数追加
			GetCorePointer()->DrawPolygon3D( PrimitiveCount );
		}
		SD.pShader->End();
	}

	// ステート
	GetRenderPointer()->StatePop();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetTransform( CStyle &Style )
{
	m_Style = Style;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetMaterialColor( CColor Color )
{
	const Float fInv = 1.0f / 255.0f;

	m_vMaterialColor.x = toF(Color.r) * fInv;
	m_vMaterialColor.y = toF(Color.g) * fInv;
	m_vMaterialColor.z = toF(Color.b) * fInv;
	m_vMaterialColor.w = toF(Color.a) * fInv;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetSpecularColor( CColor Color )
{
	const Float fInv = 1.0f / 255.0f;

	m_vSpecularColor.x = toF(Color.r) * fInv;
	m_vSpecularColor.y = toF(Color.g) * fInv;
	m_vSpecularColor.z = toF(Color.b) * fInv;
	m_vSpecularColor.w = toF(Color.a) * fInv;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetSpecularRefractive( Float fRefractive )
{
	m_fRefractive = fRefractive * fRefractive;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::SetSpecularRoughly( Float fRoughly )
{
	m_fRoughly = fRoughly * fRoughly;
}

#endif // ENABLE_3D
