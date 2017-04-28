

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Render/CVertexBuffer.h"
#include "Render/2D/CPointPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPointPrimitive2D::CPointPrimitive2D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( L"2D�|�C���g�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPointPrimitive2D::~CPointPrimitive2D()
{
}

//-----------------------------------------------------------------------------------
/**
	��̃��C���𐶐����܂��B

	@param VertexMax	[in] �ő咸�_��

	@return		���C���n���h��
*/
//-----------------------------------------------------------------------------------
Bool CPointPrimitive2D::Create( Uint32 PointMax )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	Bool bRet = true;

	try
	{
		//--------------------------------------------------------------
		// ���_�o�b�t�@
		//--------------------------------------------------------------
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( PointMax, GetRenderPointer()->GetSize(VERTEX_ELEMENT_PRIMITIVE), true );
		if ( m_pVB_Base == NULL )
		{
			throw L"���_�o�b�t�@�̐����Ɏ��s";
		}

		//--------------------------------------------------------------
		// ���_�X�g���[��
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VERTEX_ELEMENT_PRIMITIVE );
		if ( m_pVS == NULL )
		{
			throw L"���_�X�g���[���̐����Ɏ��s";
		}

		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"0x%08X", (Uint64)this );
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
/**
	�|���S����`��o�b�t�@�ɒǉ����܂�

	@param lPoint		[in] ���C���n���h��
	@param pPoint		[in] �|�C���g�f�[�^�R�_�łP�|���S��
	@param Count		[in] �|���S�����i�|�C���g���^�R�j

	@retval true		����
	@retval false		���s
*/
//-----------------------------------------------------------------------------------
Bool CPointPrimitive2D::Push( SVertex2D *pPoint, Uint32 Count )
{
	SVertex2D PointTemp;

	//-------------------------------------------------------------------------------------
	// �|���S������
	//-------------------------------------------------------------------------------------
	for ( Uint32 i = 0; i < Count; i++ )
	{
		//--------------------------------------------------
		// �������
		//--------------------------------------------------
		PointTemp.Pos.x = GetCorePointer()->Virtual2RealX( pPoint[i].Pos.x ) - 0.5f;
		PointTemp.Pos.y = GetCorePointer()->Virtual2RealY( pPoint[i].Pos.y ) - 0.5f;
		PointTemp.Pos.z = pPoint[i].Pos.z;
		PointTemp.Pos.w = pPoint[i].Pos.w;
		PointTemp.Col = pPoint[i].Col;

		//--------------------------------------------------
		// �V�U�����O
		//--------------------------------------------------
		if ( m_IsScissoring )
		{
			if ( PointTemp.Pos.x < m_ScissorX1 ) continue;
			if ( PointTemp.Pos.x > m_ScissorX2 ) continue;
			if ( PointTemp.Pos.y < m_ScissorY1 ) continue;
			if ( PointTemp.Pos.y > m_ScissorY2 ) continue;
		}

		//--------------------------------------------------
		// �f�[�^�R�s�[
		//--------------------------------------------------
		if ( !m_pVB_Base->Push( &PointTemp, 1 ) )
		{
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�`��p���_�o�b�t�@���X�V���܂�

	@param lPoint	[in] ���C���n���h��
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive2D::Begin( void )
{
	// �e��񏉊���
	m_pVB_Base->Flush();
}

//-----------------------------------------------------------------------------------
/**
	�`��p���_�o�b�t�@���X�V���܂�

	@param lPoint	[in] ���C���n���h��
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive2D::End( void )
{
	m_pVB_Base->Update();
}

//-----------------------------------------------------------------------------------
/**
	�`��p���_�o�b�t�@�������_�����O���܂�

	@param lPoint	[in] ���C���n���h��
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive2D::Rendering( void )
{
	Uint32 PrimitiveCount = m_pVB_Base->GetCount();

	//-------------------------------------------------------------------------------------
	// �����_�����O
	//-------------------------------------------------------------------------------------
	if ( PrimitiveCount > 0 )
	{
		// �X�e�[�g
		GetRenderPointer()->StatePush();
		GetRenderPointer()->SetTextureOperationType( 1, TEXTURE_OP_NONE );
		GetRenderPointer()->SetTexture( 0, NULL );
		GetRenderPointer()->SetTexture( 1, NULL );

		// �`��
		GetRenderPointer()->SetStream( m_pVS );
		GetRenderPointer()->SetVertex( 0, m_pVB_Base );
		GetRenderPointer()->DrawPrimitive( PRIMITIVE_POINT, PrimitiveCount );

		// �X�e�[�g
		GetRenderPointer()->StatePop();

		// �`��|���S�����ǉ�
		GetCorePointer()->DrawPolygon( PrimitiveCount );
	}
}

