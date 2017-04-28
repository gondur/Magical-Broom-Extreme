

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Render/CVertexBuffer.h"
#include "Render/2D/CLinePrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLinePrimitive2D::CLinePrimitive2D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( L"2D���C���v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLinePrimitive2D::~CLinePrimitive2D()
{
}

//-----------------------------------------------------------------------------------
/**
	��̃��C���𐶐����܂��B

	@param VertexMax	[in] �ő咸�_��

	@return		���C���n���h��
*/
//-----------------------------------------------------------------------------------
Bool CLinePrimitive2D::Create( Uint32 LineMax )
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
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( LineMax, GetRenderPointer()->GetSize(VERTEX_ELEMENT_PRIMITIVE), true );
		if ( m_pVB_Base == NULL )
		{
			throw L"���_�o�b�t�@�̐����Ɏ��s";
		}

		//--------------------------------------------------------------
		// ���_�X�g���[��
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VERTEX_ELEMENT_PRIMITIVE);
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

	@param lLine		[in] ���C���n���h��
	@param pPoint		[in] �|�C���g�f�[�^�R�_�łP�|���S��
	@param Count		[in] �|���S�����i�|�C���g���^�R�j

	@retval true		����
	@retval false		���s
*/
//-----------------------------------------------------------------------------------
Bool CLinePrimitive2D::Push( SLineVertex2D *pLine, Uint32 Count )
{
	static SVertex2D ScissorPoint[2];
	static SLineVertex2D LineTemp;

	//-------------------------------------------------------------------------------------
	// �|���S������
	//-------------------------------------------------------------------------------------
	for ( Uint32 i = 0; i < Count; i++ )
	{
		//--------------------------------------------------
		// �������
		//--------------------------------------------------
		LineTemp.v1.Pos.x = GetCorePointer()->Virtual2RealX( pLine[i].v1.Pos.x ) - 0.5f;
		LineTemp.v1.Pos.y = GetCorePointer()->Virtual2RealY( pLine[i].v1.Pos.y ) - 0.5f;
		LineTemp.v2.Pos.x = GetCorePointer()->Virtual2RealX( pLine[i].v2.Pos.x ) - 0.5f;
		LineTemp.v2.Pos.y = GetCorePointer()->Virtual2RealY( pLine[i].v2.Pos.y ) - 0.5f;
	
		LineTemp.v1.Pos.z = pLine[i].v1.Pos.z;
		LineTemp.v1.Pos.w = pLine[i].v1.Pos.w;
		LineTemp.v1.Col = pLine[i].v1.Col;

		LineTemp.v2.Pos.z = pLine[i].v2.Pos.z;
		LineTemp.v2.Pos.w = pLine[i].v2.Pos.w;
		LineTemp.v2.Col = pLine[i].v2.Col;

		//--------------------------------------------------
		// �V�U�����O
		//--------------------------------------------------
		Uint32 AddVertexCount = ScissorPolygon( ScissorPoint, (SVertex2D*)&LineTemp );
		if ( AddVertexCount == 0 ) continue;

		//--------------------------------------------------
		// �f�[�^�R�s�[
		//--------------------------------------------------
		m_pVB_Base->Push( ScissorPoint, AddVertexCount );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�`��p���_�o�b�t�@���X�V���܂�

	@param lLine	[in] ���C���n���h��
*/
//-----------------------------------------------------------------------------------
void CLinePrimitive2D::Begin( void )
{
	// �e��񏉊���
	m_pVB_Base->Flush();
}

//-----------------------------------------------------------------------------------
/**
	�`��p���_�o�b�t�@���X�V���܂�

	@param lLine	[in] ���C���n���h��
*/
//-----------------------------------------------------------------------------------
void CLinePrimitive2D::End( void )
{
	m_pVB_Base->Update();
}

//-----------------------------------------------------------------------------------
/**
	�`��p���_�o�b�t�@�������_�����O���܂�

	@param lLine	[in] ���C���n���h��
*/
//-----------------------------------------------------------------------------------
void CLinePrimitive2D::Rendering( void )
{
	Uint32 PrimitiveCount = m_pVB_Base->GetCount() / LINE_POINT_COUNT;

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
		GetRenderPointer()->DrawPrimitive( PRIMITIVE_LINE, PrimitiveCount );

		// �X�e�[�g
		GetRenderPointer()->StatePop();

		// �`��|���S�����ǉ�
		GetCorePointer()->DrawPolygon( PrimitiveCount );
	}
}

//-----------------------------------------------------------------------------------
/**
	�|���S�����V�U�����O���܂�

	@param pDst		[out] �o�̓|�C���g�A�h���X
	@param pSrc		[in] ���̓|�C���g�A�h���X
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygon( SVertex2D *pDst, SVertex2D *pSrc )
{
	if ( m_IsScissoring )
	{
		if ( (pSrc[0].Pos.x < m_ScissorX1) && (pSrc[1].Pos.x < m_ScissorX1) && (pSrc[2].Pos.x < m_ScissorX1) ) return 0;
		if ( (pSrc[0].Pos.x > m_ScissorX2) && (pSrc[1].Pos.x > m_ScissorX2) && (pSrc[2].Pos.x > m_ScissorX2) ) return 0;
		if ( (pSrc[0].Pos.y < m_ScissorY1) && (pSrc[1].Pos.y < m_ScissorY1) && (pSrc[2].Pos.y < m_ScissorY1) ) return 0;
		if ( (pSrc[0].Pos.y > m_ScissorY2) && (pSrc[1].Pos.y > m_ScissorY2) && (pSrc[2].Pos.y > m_ScissorY2) ) return 0;

		static SVertex2D VxResult[4][16];
		Uint32 VertexCount = LINE_POINT_COUNT;
		Uint32 VertexNum = 0;

		// ��
		VertexCount = ScissorPolygonLeft( pSrc, VxResult[0], VertexCount );

		// �E
		VertexCount = ScissorPolygonRight( VxResult[0], VxResult[1], VertexCount );

		// ��
		VertexCount = ScissorPolygonTop( VxResult[1], VxResult[2], VertexCount );

		// ��
		VertexCount = ScissorPolygonBottom( VxResult[2], VxResult[3], VertexCount );

		if ( VertexCount == 0 ) return 0;

		// ���X�g�ɓW�J
		pDst[VertexNum++] = VxResult[3][0];
		pDst[VertexNum++] = VxResult[3][1];

		return VertexNum;
	}
	else
	{
		for ( Sint32 i = 0; i < LINE_POINT_COUNT; i++ )
		{
			pDst[i] = pSrc[i];
		}

		return 2;
	}
}

//-----------------------------------------------------------------------------------
/**
	�����̃V�U�����O�����܂�

	@param pPtIn	[in] ���̓|�C���g�A�h���X
	@param pPtOut	[out] �o�̓|�C���g�A�h���X
	@param VxNum	[in] ���_��

	@return		�V�U�����O��̒��_��
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonLeft( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.x < m_ScissorX1);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
	�E���̃V�U�����O�����܂�

	@param pPtIn	[in] ���̓|�C���g�A�h���X
	@param pPtOut	[out] �o�̓|�C���g�A�h���X
	@param VxNum	[in] ���_��

	@return		�V�U�����O��̒��_��
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonRight( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.x > m_ScissorX2);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
	�㑤�̃V�U�����O�����܂�

	@param pPtIn	[in] ���̓|�C���g�A�h���X
	@param pPtOut	[out] �o�̓|�C���g�A�h���X
	@param VxNum	[in] ���_��

	@return		�V�U�����O��̒��_��
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonTop( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.y < m_ScissorY1);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
	�����̃V�U�����O�����܂�

	@param pPtIn	[in] ���̓|�C���g�A�h���X
	@param pPtOut	[out] �o�̓|�C���g�A�h���X
	@param VxNum	[in] ���_��

	@return		�V�U�����O��̒��_��
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonBottom( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.y > m_ScissorY2);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

