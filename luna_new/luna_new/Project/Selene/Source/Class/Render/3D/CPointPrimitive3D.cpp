

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Scene/CSceneManager.h"
#include "Surface/CTexture.h"
#include "Render/CVertexBuffer.h"
#include "Render/CIndexBuffer.h"
#include "Render/3D/CPointPrimitive3D.h"
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
CPointPrimitive3D::CPointPrimitive3D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive3DBase( pRender, pMgr )
	, m_vMaterialColor		( 1.0f, 1.0f, 1.0f, 1.0f )
	, m_vCenter				( 0.0f, 0.0f, 0.0f )
{
	SetName( L"3D�|�C���g�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPointPrimitive3D::~CPointPrimitive3D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPointPrimitive3D::Create( Uint32 VertexMax, Bool IsDynamic )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	Bool bRet = true;

	try
	{
		//--------------------------------------------------------------
		// �|���S���^�C�v
		//--------------------------------------------------------------
		m_RenderData.SetPolygonType( VERTEX_ELEMENT_3DBASE );

		//--------------------------------------------------------------
		// ���_�o�b�t�@
		//--------------------------------------------------------------
		Uint32 SIze = GetRenderPointer()->GetSize( VERTEX_ELEMENT_3DBASE );
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( VertexMax, SIze, IsDynamic );
		if ( m_pVB_Base == NULL )
		{
			throw L"���_�o�b�t�@�̐����Ɏ��s";
		}

		//--------------------------------------------------------------
		// ���_�X�g���[��
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VERTEX_ELEMENT_3DBASE );
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
Bool CPointPrimitive3D::Push( SVertex3DBase *pPoint, Uint32 PointCount )
{
	for ( Uint32 i = 0; i < PointCount; i++ )
	{
		m_vCenter += pPoint[i].Pos;
	}

	return CPrimitive3DBase::Push( pPoint, PointCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive3D::Begin( void )
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
void CPointPrimitive3D::End( void )
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
Sint32 CPointPrimitive3D::Rendering( void )
{
	CSceneManager *pScene = GetRenderPointer()->GetSceneManagerPointer();
	if ( pScene == NULL ) return -1;

	//-------------------------------------------------------------------------------------
	// �����_�����O
	//-------------------------------------------------------------------------------------
	if ( m_pVB_Base->GetCount() >= 1 )
	{
		CRenderData &RD = m_RenderData;

		// �e�N�X�`��
		for ( Uint32 i = 0; i < MESH_TEXTURE_MAX; i++ )
		{
			RD.Material[0].pTexture[i] = NULL;
		}

		// �}�e���A���F
		RD.Material[0].vMaterialColor = m_vMaterialColor;
		RD.MaterialCount = 1;

		RD.IsCullTest = false;

		RD.BumpMode = TECHNIQUE_BUMPMAP_DISABLE;
		RD.ReflexMode = TECHNIQUE_REFLEX_DISABLE;

		m_Style.GetTransform( RD.mWorld );
		m_Style.GetTransformInverse( RD.mWorldInverse );

		return pScene->AddObject( this, RD, m_vCenter );
	}

	return -1;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive3D::RenderSubstance( Uint32 MaterialNo, SRenderShaderData &SD )
{
	Uint32 PrimitiveCount = m_pVB_Base->GetCount();

	// �X�e�[�g
	GetRenderPointer()->StatePush();
	GetRenderPointer()->SetTextureOperationType( 1, TEXTURE_OP_NONE );
	GetRenderPointer()->SetTexture( MESH_TEXTURE_COLORMAP, NULL );
	GetRenderPointer()->SetTexture( MESH_TEXTURE_LIGHTMAP, NULL );
	GetRenderPointer()->SetTexture( MESH_TEXTURE_NORMALMAP, NULL );
	GetRenderPointer()->SetTexture( MESH_TEXTURE_SHADOWMAP, NULL );

	GetRenderPointer()->SetStream( m_pVS );
	GetRenderPointer()->SetVertex( 0, m_pVB_Base );

	Uint32 Pass;
	if ( SD.pShader->Begin( &Pass ) )
	{
		// �p�����[�^�[�X�V
		SD.pShader->UpdateParameter();
		// �p�X���̏���
		for ( Uint32 i = 0; i < Pass; i++ )
		{
			// �p�X�J�n
			SD.pShader->BeginPass( i );
			// �����_�����O
			GetRenderPointer()->DrawPrimitive( PRIMITIVE_POINT, PrimitiveCount );
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
void CPointPrimitive3D::SetTransform( CStyle &Style )
{
	m_Style = Style;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive3D::SetMaterialColor( CColor Color )
{
	const Float fInv = 1.0f / 255.0f;

	m_vMaterialColor.x = toF(Color.r) * fInv;
	m_vMaterialColor.y = toF(Color.g) * fInv;
	m_vMaterialColor.z = toF(Color.b) * fInv;
	m_vMaterialColor.w = toF(Color.a) * fInv;
}

#endif // ENABLE_3D
