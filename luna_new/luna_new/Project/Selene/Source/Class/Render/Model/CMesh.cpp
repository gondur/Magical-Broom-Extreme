

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Scene/CSceneManager.h"
#include "Render/Model/CMesh.h"
#include "Render/Model/CMaterial.h"
#include "Render/Model/CFrame.h"
#include "Render/CIndexBuffer.h"
#include "Render/CVertexBuffer.h"
#include "Render/CVertexStream.h"
#include "Render/CShader.h"
#include "Render/3D/CLinePrimitive3D.h"
#include "Surface/CTexture.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh::CMesh( CRender *pRender, CBaseMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
	, m_pParentFrame		( NULL )
	, m_pMaterials			( NULL )
	, m_VertexFlag			( 0 )
	, m_BumpMode			( TECHNIQUE_BUMPMAP_DISABLE )
	, m_ReflexMode			( TECHNIQUE_REFLEX_DISABLE )
	, m_fParallaxDepth		( 0.0f )
	, m_pLineNormal			( NULL )
	, m_pLineBounding		( NULL )
	, m_RenderID			( -1 )
{
	SetName( L"メッシュ" );

	MemoryClear( m_RenderData.Material, sizeof(m_RenderData.Material) );

	m_RenderData.MaterialCount	= 0;
	m_RenderData.BoneCount		= 0;

	m_RenderData.mWorld.Identity();
	m_RenderData.mWorldInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh::~CMesh()
{
	SAFE_RELEASE( m_pLineBounding );
	SAFE_RELEASE( m_pLineNormal );
	SAFE_DELETE_ARRAY( m_pMaterials );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetParentFrame( CFrame *pFrame )
{
	m_pParentFrame = pFrame;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateMaterialList( Uint32 MaterialCount )
{
	m_MaterialCount = MaterialCount;
	m_pMaterials = new CMaterial [ MaterialCount ];
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetMaterial( Uint32 Index, CMaterial &Mtrl )
{
	m_pMaterials[Index] = Mtrl;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetBouding( CSceneBounding &Bound )
{
	m_Bounding = Bound;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateVertex( eVertexElement Type, Uint32 Count )
{
	Uint32 Size;

	// フラグ追加
	m_VertexFlag |= Type;

	// フラグ毎にバッファ生成
	switch ( Type )
	{
	// 位置＋色
	case VERTEX_ELEMENT_3DBASE:
		SAFE_RELEASE( m_pVB_Base );
		Size = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBASE );
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( Count, Size, false );
		break;
	// テクスチャＵＶｘ２
	case VERTEX_ELEMENT_3DTEXTURE:
		SAFE_RELEASE( m_pVB_Tex );
		Size = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DTEXTURE );
		m_pVB_Tex = GetRenderPointer()->CreateVertexBuffer( Count, Size, false );
		break;
	// 法線
	case VERTEX_ELEMENT_3DLIGHT:
		SAFE_RELEASE( m_pVB_Light );
		Size = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DLIGHT );
		m_pVB_Light = GetRenderPointer()->CreateVertexBuffer( Count, Size, false );
		break;
	// 接線
	case VERTEX_ELEMENT_3DBUMP:
		SAFE_RELEASE( m_pVB_Bump );
		Size = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBUMP );
		m_pVB_Bump = GetRenderPointer()->CreateVertexBuffer( Count, Size, false );
		break;
	// ウェイト＋インデックス
	case VERTEX_ELEMENT_3DANIMATION:
		SAFE_RELEASE( m_pVB_Animation );
		Size = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DANIMATION );
		m_pVB_Animation = GetRenderPointer()->CreateVertexBuffer( Count, Size, false );
		break;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateIndex( Uint32 Count )
{
	m_pIB = GetRenderPointer()->CreateIndexBuffer( Count, false );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::UpdateStream( void )
{
	if ( m_pVB_Base      != NULL ) m_pVB_Base->Update();
	if ( m_pVB_Tex       != NULL ) m_pVB_Tex->Update();
	if ( m_pVB_Light     != NULL ) m_pVB_Light->Update();
	if ( m_pVB_Bump      != NULL ) m_pVB_Bump->Update();
	if ( m_pVB_Animation != NULL ) m_pVB_Animation->Update();
	if ( m_pIB           != NULL ) m_pIB->Update();

	Uint32 Flag = m_VertexFlag;

	// 必須データがそろってないときはバンプOFF
	if ( (m_BumpMode == TECHNIQUE_BUMPMAP_DISABLE) || (m_pVB_Bump == NULL) || (m_pVB_Light == NULL) || (m_pVB_Tex == NULL) )
	{
		Flag &= ~VERTEX_ELEMENT_3DBUMP;
	}

	// ストリーム再生成
	SAFE_RELEASE( m_pVS );
	m_pVS = GetRenderPointer()->CreateVertexStream( Flag );

	// シェーダー更新
	m_RenderData.SetPolygonType( Flag );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( Uint16 *pIndex, Uint32 IndexCount )
{
	if ( m_pIB == NULL ) return false;
	if ( !m_pIB->Push( pIndex, IndexCount ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( SVertex3DBase *pVtx, Uint32 Count )
{
	if ( m_pVB_Base == NULL ) return false;
	if ( !m_pVB_Base->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( SVertex3DTexture *pVtx, Uint32 Count )
{
	if ( m_pVB_Tex == NULL ) return false;
	if ( !m_pVB_Tex->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( SVertex3DLight *pVtx, Uint32 Count )
{
	if ( m_pVB_Light == NULL ) return false;
	if ( !m_pVB_Light->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( SVertex3DBump *pVtx, Uint32 Count )
{
	if ( m_pVB_Bump == NULL ) return false;
	if ( !m_pVB_Bump->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( SVertex3DAnimation *pVtx, Uint32 Count )
{
	if ( m_pVB_Animation == NULL ) return false;
	if ( !m_pVB_Animation->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::GetSupportTexture( void )
{
	return m_pVB_Tex != NULL;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Sint32 CMesh::Rendering( void )
{
	CSceneManager *pScene = GetRenderPointer()->GetSceneManagerPointer();
	if ( pScene == NULL ) return -1;

	CRenderData &RD = m_RenderData;

	//--------------------------------------------------------------------
	// トランスフォーム
	//--------------------------------------------------------------------
	m_pParentFrame->GetTransform( RD.mWorld );
	m_pParentFrame->GetTransformInverse( RD.mWorldInverse );

	//--------------------------------------------------------------------
	// モード
	//--------------------------------------------------------------------
	RD.BumpMode = m_BumpMode;
	RD.ReflexMode = m_ReflexMode;

	//--------------------------------------------------------------------
	// マテリアル数
	//--------------------------------------------------------------------
	RD.MaterialCount = m_MaterialCount;

	//--------------------------------------------------------------------
	// マテリアルデータ
	//--------------------------------------------------------------------
	Uint32 Max = m_MaterialCount;
	for ( Uint32 i = 0; i < Max; i++ )
	{
		for ( Uint32 j = 0; j < MESH_TEXTURE_MAX; j++ )
		{
			RD.Material[i].pTexture[j] = m_pMaterials[i].GetTexturePointer( j );
		}
		RD.Material[i].vMaterialColor = m_pMaterials[i].GetColor();
		RD.Material[i].vSpecularColor = m_pMaterials[i].GetSpecularColor();
		RD.Material[i].fRefractive = m_pMaterials[i].GetSpecularRefractive();
		RD.Material[i].fRoughly = m_pMaterials[i].GetSpecularRoughly();
	}

	//--------------------------------------------------------------------
	// カリング用データ
	//--------------------------------------------------------------------
	RD.IsCullTest = true;
	for ( Uint32 i = 0; i < 8; i++ )
	{
		RD.CullBox.Points[i].TransformCoord( m_Bounding.vPoint[i], RD.mWorld );
	}
	RD.CullBox.Update();

	//--------------------------------------------------------------------
	// 法線可視
	//--------------------------------------------------------------------
	if ( m_pLineNormal != NULL )
	{
		CStyle Style;
		Style.TransformReset();
		Style.FromMatrix( RD.mWorld );
		Style.TransformUpdate();
		m_pLineNormal->SetTransform( Style );
		m_pLineNormal->Rendering();
	}

	//--------------------------------------------------------------------
	// バウンディング可視
	//--------------------------------------------------------------------
	if ( m_pLineBounding != NULL )
	{
		CStyle Style;
		Style.TransformReset();
		Style.FromMatrix( RD.mWorld );
		Style.TransformUpdate();
		m_pLineBounding->SetTransform( Style );
		m_pLineBounding->Rendering();
	}

	//--------------------------------------------------------------------
	// レンダリングリクエスト
	//--------------------------------------------------------------------
	CVector3D vCenter;
	vCenter.TransformCoord( m_Bounding.vCenter, RD.mWorld );

	m_RenderID = pScene->AddObject( this, RD, vCenter );

	return m_RenderID;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD )
{
	CMaterial &Mtrl = m_pMaterials[MaterialNo];

	Uint32 VertexStart		= Mtrl.GetVertexStart();
	Uint32 VertexCount		= Mtrl.GetVertexCount();
	Uint32 IndexStart		= Mtrl.GetIndexStart();
	Uint32 PrimitiveCount	= Mtrl.GetIndexCount() / 3;

	GetRenderPointer()->SetStream( m_pVS );
	GetRenderPointer()->SetIndex( m_pIB );

	GetRenderPointer()->SetVertex( 0, m_pVB_Base );
	GetRenderPointer()->SetVertex( 1, m_pVB_Tex );
	GetRenderPointer()->SetVertex( 2, m_pVB_Light );
	GetRenderPointer()->SetVertex( 3, m_pVB_Bump );
	GetRenderPointer()->SetVertex( 4, m_pVB_Animation );

	// 視差深度
	if ( SD.hParallaxDepth != NULL )
	{
		SD.pShader->SetFloat( SD.hParallaxDepth, m_fParallaxDepth );
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
			GetRenderPointer()->DrawMesh( VertexStart, VertexCount, IndexStart, PrimitiveCount );
			// パス終了
			SD.pShader->EndPass();
			// 描画ポリゴン数追加
			GetCorePointer()->DrawPolygon3D( PrimitiveCount );
		}
		SD.pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::ConvertReflexMesh( void )
{
	// ピクセルシェーダー2.0必須
	// シェーダー分岐が面倒とかいうのはとりあえずおいといて
	// 1.1だと正規化出来ないから変になるので未サポート
	if ( GetGraphicCardPointer()->GetPixelShaderSupport( 2, 0 ) )
	{
		m_ReflexMode = TECHNIQUE_REFLEX_ENABLE;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::ConvertBumpMesh( ITexture *pTexNormal )
{
	if ( pTexNormal == NULL ) return;

	// ピクセルシェーダー2.0必須
	// シェーダー分岐が面倒とかいうのはとりあえずおいといて
	// 1.1だと正規化出来ないから変になるので未サポート
	if ( GetGraphicCardPointer()->GetPixelShaderSupport( 2, 0 ) )
	{
		// バンプ情報＆テクスチャ情報がある
		if ( (m_pVB_Bump != NULL) && (m_pVB_Light != NULL) && (m_pVB_Tex != NULL) )
		{
			// バンプONじゃないとき変換
			if ( m_BumpMode == TECHNIQUE_BUMPMAP_DISABLE )
			{
				m_BumpMode = TECHNIQUE_BUMPMAP_ENABLE;
				UpdateStream();
			}

			// バンプ用のテクスチャをマテリアルに適用
			Uint32 Max = m_MaterialCount;
			for ( Uint32 i = 0; i < Max; i++ )
			{
				m_pMaterials[i].SetTexture( MESH_TEXTURE_NORMALMAP, dynamic_cast<CTexture*>(pTexNormal) );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::ConvertParallaxMesh( ITexture *pTexNormal, Float fParallaxDepth )
{
	if ( pTexNormal == NULL ) return;

	// ピクセルシェーダー2.0必須
	// シェーダー分岐が面倒とかいうのはとりあえずおいといて
	// 1.1だと正規化出来ないから変になるので未サポート
	if ( GetGraphicCardPointer()->GetPixelShaderSupport( 2, 0 ) )
	{
		// バンプ情報＆テクスチャ情報がある
		if ( (m_pVB_Bump != NULL) && (m_pVB_Light != NULL) && (m_pVB_Tex != NULL) )
		{
			// バンプONじゃないとき変換
			if ( m_BumpMode == TECHNIQUE_BUMPMAP_DISABLE )
			{
				m_BumpMode = TECHNIQUE_BUMPMAP_PARALLAX;
				UpdateStream();
			}

			// 視差深度
			m_fParallaxDepth = fParallaxDepth;

			// バンプ用のテクスチャをマテリアルに適用
			Uint32 Max = m_MaterialCount;
			for ( Uint32 i = 0; i < Max; i++ )
			{
				m_pMaterials[i].SetTexture( MESH_TEXTURE_NORMALMAP, dynamic_cast<CTexture*>(pTexNormal) );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CMesh::GetMaterialCount( void )
{
	return m_MaterialCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::SetSpecularColor( Uint32 MaterialIndex, CColor Color )
{
	CVector4D vColor( toF(Color.r)/255.0f, toF(Color.g)/255.0f, toF(Color.b)/255.0f, toF(Color.a)/255.0f );
	m_pMaterials[MaterialIndex].SetSpecularColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::SetSpecularRefractive( Uint32 MaterialIndex, Float fRefractive )
{
	m_pMaterials[MaterialIndex].SetSpecularRefractive( fRefractive );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::SetSpecularRoughly( Uint32 MaterialIndex, Float fRoughly )
{
	m_pMaterials[MaterialIndex].SetSpecularRoughly( fRoughly );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::BoundingVisible( void )
{
	m_pLineBounding = GetRenderPointer()->CreateLinePrimitive3D( (12 + 6) * 2, false );

	m_pLineBounding->Begin();

	// 枠
	SPrimitive3DVertexLine Line[] = {
		{ { m_Bounding.vPoint[0], 0xFFFFFFFF }, { m_Bounding.vPoint[1], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[1], 0xFFFFFFFF }, { m_Bounding.vPoint[2], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[2], 0xFFFFFFFF }, { m_Bounding.vPoint[3], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[3], 0xFFFFFFFF }, { m_Bounding.vPoint[0], 0xFFFFFFFF } },

		{ { m_Bounding.vPoint[4], 0xFFFFFFFF }, { m_Bounding.vPoint[5], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[5], 0xFFFFFFFF }, { m_Bounding.vPoint[6], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[6], 0xFFFFFFFF }, { m_Bounding.vPoint[7], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[7], 0xFFFFFFFF }, { m_Bounding.vPoint[4], 0xFFFFFFFF } },

		{ { m_Bounding.vPoint[0], 0xFFFFFFFF }, { m_Bounding.vPoint[4], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[1], 0xFFFFFFFF }, { m_Bounding.vPoint[5], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[2], 0xFFFFFFFF }, { m_Bounding.vPoint[6], 0xFFFFFFFF } },
		{ { m_Bounding.vPoint[3], 0xFFFFFFFF }, { m_Bounding.vPoint[7], 0xFFFFFFFF } },
	};

	m_pLineBounding->Push( Line, sizeof(Line) / sizeof(SPrimitive3DVertexLine) );

	m_pLineBounding->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMesh::NormalVisible( Float fLength )
{
	// 頂点データあるの？
	if ( m_pVB_Base  == NULL ) return;
	if ( m_pVB_Light == NULL ) return;
	if ( m_pVB_Bump  == NULL ) return;

	// データ
	SVertex3DBase	v1;
	SVertex3DLight	v2;
	SVertex3DBump	v3;
	SPrimitive3DVertexLine Line;

	// 頂点数
	Uint32 Cnt = m_pVB_Base->GetCount();

	// ラインデータ生成
	m_pLineNormal = GetRenderPointer()->CreateLinePrimitive3D( Cnt * 2 * 2 * 2, false );
	m_pLineNormal->Begin();
	for ( Uint32 i = 0; i < Cnt; i++ )
	{
		m_pVB_Base->Get( &v1, i );
		m_pVB_Light->Get( &v2, i );
		m_pVB_Bump->Get( &v3, i );

		// Zファイティング対策
		CVector3D vPos = v1.Pos + v2.Norm * 0.001f;

		// 従法線
		CVector3D vBiNorm;
		vBiNorm.Cross( v2.Norm, v3.Tangent ); 

		// 法線
		Line.v1.Pos = vPos;
		Line.v1.Col = CColor(  0,  0,  0,255);
		Line.v2.Pos = vPos + v2.Norm * fLength;
		Line.v2.Col = CColor(255,  0,255,255);
		m_pLineNormal->Push( &Line, 1 );

		// 接線
		Line.v1.Pos = vPos;
		Line.v1.Col = CColor(  0,  0,  0,255);
		Line.v2.Pos = vPos + v3.Tangent * fLength;
		Line.v2.Col = CColor(  0,  0,255,255);
		m_pLineNormal->Push( &Line, 1 );

		// 従法線
		Line.v1.Pos = vPos;
		Line.v1.Col = CColor(  0,  0,  0,255);
		Line.v2.Pos = vPos + vBiNorm * fLength;
		Line.v2.Col = CColor(  0,255,  0,255);
		m_pLineNormal->Push( &Line, 1 );
	}
	m_pLineNormal->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMesh::GetRenderID( void )
{
	return m_RenderID;
}

#endif // ENABLE_3D
