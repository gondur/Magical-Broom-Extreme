

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Surface/CTexture.h"
#include "Render/CVertexBuffer.h"
#include "Render/2D/CPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive2D::CPrimitive2D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( L"2D�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive2D::~CPrimitive2D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive2D::Create( Uint32 PrimitiveMax )
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
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( PrimitiveMax, GetRenderPointer()->GetSize(VERTEX_ELEMENT_SPRITE), true );
		if ( m_pVB_Base == NULL )
		{
			throw L"���_�o�b�t�@�̐����Ɏ��s";
		}

		//--------------------------------------------------------------
		// ���_�X�g���[��
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VERTEX_ELEMENT_SPRITE );
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
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive2D::Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )
{
	static SVertex2DTex ScissorPoint[32];

	//-------------------------------------------------------------------------------------
	// �|���S������
	//-------------------------------------------------------------------------------------
	for ( Uint32 i = 0; i < Count; i++ )
	{
		SPrimitiveVertex2D PrimitiveTemp = pPrimitive[i];

		//--------------------------------------------------
		// �������
		//--------------------------------------------------
		PrimitiveTemp.v1.Pos.x = GetCorePointer()->Virtual2RealX( PrimitiveTemp.v1.Pos.x ) - 0.5f;
		PrimitiveTemp.v1.Pos.y = GetCorePointer()->Virtual2RealY( PrimitiveTemp.v1.Pos.y ) - 0.5f;
		PrimitiveTemp.v2.Pos.x = GetCorePointer()->Virtual2RealX( PrimitiveTemp.v2.Pos.x ) - 0.5f;
		PrimitiveTemp.v2.Pos.y = GetCorePointer()->Virtual2RealY( PrimitiveTemp.v2.Pos.y ) - 0.5f;
		PrimitiveTemp.v3.Pos.x = GetCorePointer()->Virtual2RealX( PrimitiveTemp.v3.Pos.x ) - 0.5f;
		PrimitiveTemp.v3.Pos.y = GetCorePointer()->Virtual2RealY( PrimitiveTemp.v3.Pos.y ) - 0.5f;

		//--------------------------------------------------
		// �V�U�����O
		//--------------------------------------------------
		Uint32 AddVertexCount = ScissorPolygon( ScissorPoint, (SVertex2DTex*)&PrimitiveTemp );
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
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Begin( void )
{
	// �e��񏉊���
	m_pVB_Base->Flush();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::End( void )
{
	m_pVB_Base->Update();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Rendering( void )
{
	Uint32 PrimitiveCount = m_pVB_Base->GetCount() / PRIMITIVE_POINT_COUNT;

	//--------------------------------------------------------------------------
	// �����_�����O
	//--------------------------------------------------------------------------
	if ( PrimitiveCount > 0 )
	{
		// �X�e�[�g
		GetRenderPointer()->StatePush();
		GetRenderPointer()->SetTextureAddressType( 0, TEXTURE_ADDRESS_CLAMP );
		GetRenderPointer()->SetTextureOperationType( 1, TEXTURE_OP_NONE );

		// �`��
		GetRenderPointer()->SetStream( m_pVS );
		GetRenderPointer()->SetVertex( 0, m_pVB_Base );
		GetRenderPointer()->DrawPrimitive( PRIMITIVE_TRIANGLE, PrimitiveCount );

		// �X�e�[�g
		GetRenderPointer()->StatePop();

		// �`��|���S�����ǉ�
		GetCorePointer()->DrawPolygon( PrimitiveCount );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive2D::ScissorPolygon( SVertex2DTex *pDst, SVertex2DTex *pSrc )
{
	if ( m_IsScissoring )
	{
		if ( (pSrc[0].Pos.x < m_ScissorX1) && (pSrc[1].Pos.x < m_ScissorX1) && (pSrc[2].Pos.x < m_ScissorX1) ) return 0;
		if ( (pSrc[0].Pos.x > m_ScissorX2) && (pSrc[1].Pos.x > m_ScissorX2) && (pSrc[2].Pos.x > m_ScissorX2) ) return 0;
		if ( (pSrc[0].Pos.y < m_ScissorY1) && (pSrc[1].Pos.y < m_ScissorY1) && (pSrc[2].Pos.y < m_ScissorY1) ) return 0;
		if ( (pSrc[0].Pos.y > m_ScissorY2) && (pSrc[1].Pos.y > m_ScissorY2) && (pSrc[2].Pos.y > m_ScissorY2) ) return 0;

		static SVertex2DTex VxResult[4][16];
		Uint32 VertexCount = PRIMITIVE_POINT_COUNT;
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
		for ( Uint32 i = 0; i < VertexCount - 2; i++ )
		{
			pDst[VertexNum++] = VxResult[3][0];
			pDst[VertexNum++] = VxResult[3][i + 1];
			pDst[VertexNum++] = VxResult[3][i + 2];
		}

		return VertexNum;
	}
	else
	{
		pDst[0] = pSrc[0];
		pDst[1] = pSrc[1];
		pDst[2] = pSrc[2];

		return 3;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive2D::ScissorPolygonLeft( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

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
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive2D::ScissorPolygonRight( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

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
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorX2 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive2D::ScissorPolygonTop( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

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
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CPrimitive2D::ScissorPolygonBottom( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

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
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Square( CRect2D<Sint32> &DstRect, CColor Color )
{
	Float x1 = toF(DstRect.x);
	Float y1 = toF(DstRect.y);
	Float x2 = toF(DstRect.x + DstRect.w);
	Float y2 = toF(DstRect.y + DstRect.h);

	SPrimitiveVertex2D Vtx[] = {
		{
			{ CVector4D(x1, y1, 0.0f, 1.0f), Color },
			{ CVector4D(x2, y1, 0.0f, 1.0f), Color },
			{ CVector4D(x2, y2, 0.0f, 1.0f), Color },
		},
		{
			{ CVector4D(x2, y2, 0.0f, 1.0f), Color },
			{ CVector4D(x1, y2, 0.0f, 1.0f), Color },
			{ CVector4D(x1, y1, 0.0f, 1.0f), Color },
		},
	};

	// �v���~�e�B�u�ɒǉ�
	Push( Vtx, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::SquareRotate( CRect2D<Sint32> &DstRect, CColor Color, Sint32 Angle )
{
	Float x1 = toF(DstRect.x);
	Float y1 = toF(DstRect.y);
	Float x2 = toF(DstRect.x + DstRect.w);
	Float y2 = toF(DstRect.y + DstRect.h);

	CPoint2D<Float> Center( (x1 + x2) * 0.5f, (y1 + y2) * 0.5f );
	CPoint2D<Float> Offset(0.5f, 0.5f);

	// ��]
	CPoint2D<Float> Pt[4] = {
		CPoint2D<Float>( x1, y1 ),
		CPoint2D<Float>( x2, y1 ),
		CPoint2D<Float>( x1, y2 ),
		CPoint2D<Float>( x2, y2 ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i] -= Center;
		Pt[i] = Pt[i].Rotate( Angle );
		Pt[i] += Center;
		Pt[i] -= Offset;
	}

	SPrimitiveVertex2D Vtx[] = {
		{
			{ CVector4D( Pt[0].x, Pt[0].y, 0.0f, 1.0f), Color },
			{ CVector4D( Pt[1].x, Pt[1].y, 0.0f, 1.0f), Color },
			{ CVector4D( Pt[3].x, Pt[3].y, 0.0f, 1.0f), Color },
		},
		{
			{ CVector4D( Pt[3].x, Pt[3].y, 0.0f, 1.0f), Color },
			{ CVector4D( Pt[2].x, Pt[2].y, 0.0f, 1.0f), Color },
			{ CVector4D( Pt[0].x, Pt[0].y, 0.0f, 1.0f), Color },
		},
	};

	// �v���~�e�B�u�ɒǉ�
	Push( Vtx, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Polygon( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num )
{
	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2);
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2);

		SPrimitiveVertex2D Vtx[] = {
			{ CVector4D(toF(Pos.x                           ), toF(Pos.y                           ), 0.0f, 1.0f), Color },
			{ CVector4D(toF(Pos.x+toI(Math::Cos(a1)*fRadius)), toF(Pos.y+toI(Math::Sin(a1)*fRadius)), 0.0f, 1.0f), Color },
			{ CVector4D(toF(Pos.x+toI(Math::Cos(a2)*fRadius)), toF(Pos.y+toI(Math::Sin(a2)*fRadius)), 0.0f, 1.0f), Color },
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 1 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::PolygonRotate( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )
{
	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2) + Angle;
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2) + Angle;

		SPrimitiveVertex2D Vtx[] = {
			{ CVector4D(toF(Pos.x                           ), toF(Pos.y                           ), 0.0f, 1.0f), Color },
			{ CVector4D(toF(Pos.x+toI(Math::Cos(a1)*fRadius)), toF(Pos.y+toI(Math::Sin(a1)*fRadius)), 0.0f, 1.0f), Color },
			{ CVector4D(toF(Pos.x+toI(Math::Cos(a2)*fRadius)), toF(Pos.y+toI(Math::Sin(a2)*fRadius)), 0.0f, 1.0f), Color },
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 1 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Ring( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )
{
	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2);
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2);

		SPrimitiveVertex2D Vtx[] = {
			{
				{ CVector4D(Pos.x+Math::Cos(a1)* fInRadius, Pos.y+Math::Sin(a1)* fInRadius, 0.0f, 1.0f),  InColor },
				{ CVector4D(Pos.x+Math::Cos(a1)*fOutRadius, Pos.y+Math::Sin(a1)*fOutRadius, 0.0f, 1.0f), OutColor },
				{ CVector4D(Pos.x+Math::Cos(a2)*fOutRadius, Pos.y+Math::Sin(a2)*fOutRadius, 0.0f, 1.0f), OutColor },
			},
			{
				{ CVector4D(Pos.x+Math::Cos(a2)*fOutRadius, Pos.y+Math::Sin(a2)*fOutRadius, 0.0f, 1.0f), OutColor },
				{ CVector4D(Pos.x+Math::Cos(a2)* fInRadius, Pos.y+Math::Sin(a2)* fInRadius, 0.0f, 1.0f),  InColor },
				{ CVector4D(Pos.x+Math::Cos(a1)* fInRadius, Pos.y+Math::Sin(a1)* fInRadius, 0.0f, 1.0f),  InColor },
			},
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::RingRotate( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )
{
	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2) + Angle;
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2) + Angle;

		SPrimitiveVertex2D Vtx[] = {
			{
				{ CVector4D(toF(Pos.x+toI(Math::Cos(a1)* fInRadius)), toF(Pos.y+toI(Math::Sin(a1)* fInRadius)), 0.0f, 1.0f),  InColor },
				{ CVector4D(toF(Pos.x+toI(Math::Cos(a1)*fOutRadius)), toF(Pos.y+toI(Math::Sin(a1)*fOutRadius)), 0.0f, 1.0f), OutColor },
				{ CVector4D(toF(Pos.x+toI(Math::Cos(a2)*fOutRadius)), toF(Pos.y+toI(Math::Sin(a2)*fOutRadius)), 0.0f, 1.0f), OutColor },
			},
			{
				{ CVector4D(toF(Pos.x+toI(Math::Cos(a2)*fOutRadius)), toF(Pos.y+toI(Math::Sin(a2)*fOutRadius)), 0.0f, 1.0f), OutColor },
				{ CVector4D(toF(Pos.x+toI(Math::Cos(a2)* fInRadius)), toF(Pos.y+toI(Math::Sin(a2)* fInRadius)), 0.0f, 1.0f),  InColor },
				{ CVector4D(toF(Pos.x+toI(Math::Cos(a1)* fInRadius)), toF(Pos.y+toI(Math::Sin(a1)* fInRadius)), 0.0f, 1.0f),  InColor },
			},
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 2 );
	}
}




