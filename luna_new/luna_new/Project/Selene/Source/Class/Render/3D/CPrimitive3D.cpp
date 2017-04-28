

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
	SetName( L"3D�v���~�e�B�u" );
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
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	Bool bRet = true;

	try
	{
		//--------------------------------------------------------------
		// �t���O�`�F�b�N
		//--------------------------------------------------------------
		if ( (VertexFlag & VERTEX_ELEMENT_SPRITE) != 0 )
		{
			throw L"VERTEX_ELEMENT_SPRITE�t���O�̓T�|�[�g����Ă��܂���";
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DBASE) == 0 )
		{
			throw L"VERTEX_ELEMENT_3DBASE�t���O������܂���";
		}

		//--------------------------------------------------------------
		// �|���S���^�C�v
		//--------------------------------------------------------------
		m_RenderData.SetPolygonType( VertexFlag );

		//--------------------------------------------------------------
		// ���_�o�b�t�@
		//--------------------------------------------------------------
		if ( (VertexFlag & VERTEX_ELEMENT_3DBASE) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBASE );
			m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Base == NULL )
			{
				throw L"���_�o�b�t�@�̐����Ɏ��s";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DTEXTURE) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DTEXTURE );
			m_pVB_Tex = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Tex == NULL )
			{
				throw L"���_�o�b�t�@�̐����Ɏ��s";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DLIGHT) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DLIGHT );
			m_pVB_Light = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Light == NULL )
			{
				throw L"���_�o�b�t�@�̐����Ɏ��s";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DBUMP) != 0 )
		{
			m_BumpMode = TECHNIQUE_BUMPMAP_ENABLE;
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBUMP );
			m_pVB_Bump = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Bump == NULL )
			{
				throw L"���_�o�b�t�@�̐����Ɏ��s";
			}
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DANIMATION) != 0 )
		{
			Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DANIMATION );
			m_pVB_Animation = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
			if ( m_pVB_Animation == NULL )
			{
				throw L"���_�o�b�t�@�̐����Ɏ��s";
			}
		}

		//--------------------------------------------------------------
		// �C���f�b�N�X�o�b�t�@
		//--------------------------------------------------------------
		m_pIB = GetRenderPointer()->CreateIndexBuffer( IndexMax, IsDynamic );
		if ( m_pIB == NULL )
		{
			throw L"�C���f�b�N�X�o�b�t�@�̐����Ɏ��s";
		}

		//--------------------------------------------------------------
		// ���_�X�g���[��
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VertexFlag );
		if ( m_pVS == NULL )
		{
			throw L"���_�X�g���[���̐����Ɏ��s";
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
	�`��p���_�o�b�t�@���A�b�v�f�[�g���܂�

	@param lPrim	[fIn] �v���~�e�B�u�n���h��
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
	// �����_�����O
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

	// �X�e�[�g
	GetRenderPointer()->StatePush();
	GetRenderPointer()->SetTextureAddressType( 0, TEXTURE_ADDRESS_CLAMP );

	// �e�N�X�`���Ȃ�
	if ( m_pVB_Tex == NULL )
	{
		GetRenderPointer()->SetTextureOperationType( 1, TEXTURE_OP_NONE );
		GetRenderPointer()->SetTexture( 0, NULL );
		GetRenderPointer()->SetTexture( 1, NULL );
	}

	// �f�[�^
	GetRenderPointer()->SetStream( m_pVS );
	GetRenderPointer()->SetIndex( m_pIB );

	// ���_
	GetRenderPointer()->SetVertex( 0, m_pVB_Base );
	GetRenderPointer()->SetVertex( 1, m_pVB_Tex );
	GetRenderPointer()->SetVertex( 2, m_pVB_Light );
	GetRenderPointer()->SetVertex( 3, m_pVB_Bump );
	GetRenderPointer()->SetVertex( 4, m_pVB_Animation );

	// �����[�x
	if ( SD.hParallaxDepth != NULL )
	{
		SD.pShader->SetFloat( SD.hParallaxDepth, 0.0f );
	}

	// �p�����[�^�[�X�V
	SD.pShader->UpdateParameter();

	Uint32 Pass;
	if ( SD.pShader->Begin( &Pass ) )
	{
		// �p�X���̏���
		for ( Uint32 i = 0; i < Pass; i++ )
		{
			// �p�X�J�n
			SD.pShader->BeginPass( i );
			// �����_�����O
			GetRenderPointer()->DrawIndexedPrimitive( PRIMITIVE_TRIANGLE, VertexCount, PrimitiveCount );
			// �p�X�I��
			SD.pShader->EndPass();
			// �`��|���S�����ǉ�
			GetCorePointer()->DrawPolygon3D( PrimitiveCount );
		}
		SD.pShader->End();
	}

	// �X�e�[�g
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
