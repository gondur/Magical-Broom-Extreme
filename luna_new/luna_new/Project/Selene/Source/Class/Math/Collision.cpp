

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Math/Collision.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// STRUCT
//-----------------------------------------------------------------------------------

/**
	@brief ������`

	Collision�N���X�����Ŏg�p����Ă���
	������`�\���̂ł��B
*/
typedef struct CLine3D2
{
	struct {
		Float a;
		Float b;
	} x, y, z;
}
CLine3D2, *LPCLine3D2;


//-----------------------------------------------------------------------------------
/**
	@brief �_(x,y)�������� l �̂ǂ��瑤�ɂ��邩���ׂ�

	@param x		[in] �]������_�̂w���W
	@param y		[in] �]������_�̂x���W
	@param pLine	[in] �]���������

	@retval > 0		������ l �̉E���ɂ���
	@retval ==0		������ l �̒�����ɂ���
	@retval < 0		������ l �̍����ɂ���

*/
//-----------------------------------------------------------------------------------
static inline Float Side( Float x, Float y, CLine2D *pLine )
{
	return ((x - pLine->Pt0.x) * (y - pLine->Pt1.y) - (y - pLine->Pt0.y) * (x - pLine->Pt1.x));
}

//-----------------------------------------------------------------------------------
/**
	@brief �����̃x�N�g��������

	@param pDst		[out] �x�N�g���������i�[��
	@param pSrc		[in] ���ɂȂ钼��
*/
//-----------------------------------------------------------------------------------
static inline void CreateLine2( CLine3D2 *pDst, CLine3D *pSrc )
{
	pDst->x.a = pSrc->Pt0.x;
	pDst->x.b = pSrc->Pt1.x - pSrc->Pt0.x;

	pDst->y.a = pSrc->Pt0.y;
	pDst->y.b = pSrc->Pt1.y - pSrc->Pt0.y;

	pDst->z.a = pSrc->Pt0.z;
	pDst->z.b = pSrc->Pt1.z - pSrc->Pt0.z;
}

//-----------------------------------------------------------------------------------
/**
	�_�ƒ����̓��蔻����s���܂�

	@param pPt1		[in] �]������Q�c���ʏ�̓_
	@param pPt2		[in] �]������Q�c���ʏ�̓_

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Point( CVector2D *pPt1, CVector2D *pPt2 )
{
	CCircle Cir1( pPt1->x, pPt1->y, 1.0f );
	CCircle Cir2( pPt2->x, pPt2->y, 1.0f );

	return Circle_Circle( &Cir1, &Cir2 );
}

//-----------------------------------------------------------------------------------
/**
	�_�ƒ����̓��蔻����s���܂�

	@param pPt		[in] �]������Q�c���ʏ�̓_
	@param pLine	[in] �]������Q�c���ʏ�̐���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Line( CVector2D *pPt, CLine2D *pLine )
{
	CCircle Cir( pPt->x, pPt->y, 0.1f );

	return Circle_Line( &Cir, pLine );
}

//-----------------------------------------------------------------------------------
/**
	�_�Ǝl�p�̓��蔻����s���܂�

	@param pPt		[in] �]������Q�c���ʏ�̓_
	@param pRect	[in] �]������Q�c���ʏ�̋�`

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Rect( CVector2D *pPt, CRect2D<Float> *pRect )
{
	Float x0 = pRect->x;
	Float y0 = pRect->y;
	Float x1 = pRect->x + pRect->w;
	Float y1 = pRect->y + pRect->h;

	if ( pPt->x < x0 ) return false;
	if ( pPt->y < y0 ) return false;
	if ( pPt->x > x1 ) return false;
	if ( pPt->y > y1 ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�_�Ɖ~�̓��蔻����s���܂�

	@param pPt		[in] �]������Q�c���ʏ�̓_
	@param pCir		[in] �]������Q�c���ʏ�̉~

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Circle( CVector2D *pPt, CCircle *pCir )
{
	Float rx = pPt->x - pCir->Center.x;
	Float ry = pPt->y - pCir->Center.y;
	Float r = pCir->Radius;

	if ( ((rx * rx) + (ry * ry)) > (r * r) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�_�Ƒ��p�`�̓��蔻����s���܂�

	@param pPt		[in] �]������Q�c���ʏ�̓_
	@param pPoly	[in] �]������Q�c���ʏ�̃|���S��

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Polygon( CVector2D *pPt, CPolygon2D *pPoly )
{
	Sint32 num = 0;
	Sint32 cnt = pPoly->Count-1;

	for ( Sint32 i = 0; i < cnt; i++ )
	{
		Float x1 = pPoly->pPts[i+0].x;
		Float y1 = pPoly->pPts[i+0].y;
		Float x2 = pPoly->pPts[i+1].x;
		Float y2 = pPoly->pPts[i+1].y;

		Float x = pPt->x;
		Float y = pPt->y;

		Float n = (x - x1) * (y - y2) - (y - y1) * (x-x2);
		if ( n < 0 ) num++;
	}

	return ( (0 == num) || (num == cnt) );
}

//-----------------------------------------------------------------------------------
/**
	�l�p�Ǝl�p�̓��蔻����s���܂�

	@param pRect1	[in] �]������Q�c���ʏ�̋�`
	@param pRect2	[in] �]������Q�c���ʏ�̋�`

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Rect( CRect2D<Float> *pRect1, CRect2D<Float> *pRect2 )
{
	Float x00 = pRect1->x;
	Float y00 = pRect1->y;
	Float x01 = pRect1->x + pRect1->w;
	Float y01 = pRect1->y + pRect1->h;

	Float x10 = pRect2->x;
	Float y10 = pRect2->y;
	Float x11 = pRect2->x + pRect2->w;
	Float y11 = pRect2->y + pRect2->h;

	if ( x00 > x01 ) SWAP( x00, x01 );
	if ( y00 > y01 ) SWAP( y00, y01 );
	if ( x10 > x11 ) SWAP( x10, x11 );
	if ( y10 > y11 ) SWAP( y10, y11 );

	if ( x00 > x11 ) return false;
	if ( x01 < x10 ) return false;
	if ( y00 > y11 ) return false;
	if ( y01 < y10 ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�l�p�Ɖ~�̓��蔻����s���܂�

	@param pRect	[in] �]������Q�c���ʏ�̋�`
	@param pCir		[in] �]������Q�c���ʏ�̉~

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Circle( CRect2D<Float> *pRect, CCircle *pCir )
{
	Float x0 = pRect->x;
	Float y0 = pRect->y;
	Float x1 = pRect->x + pRect->w;
	Float y1 = pRect->y + pRect->h;

	CVector2D Pts[5] = {
		CVector2D( x0, y0 ),
		CVector2D( x1, y0 ),
		CVector2D( x1, y1 ),
		CVector2D( x0, y1 ),
		CVector2D( x0, y0 ),
	};

	CPolygon2D Poly( 5, Pts );

	return Circle_Polygon( pCir, &Poly );
}

//-----------------------------------------------------------------------------------
/**
	�l�p�ƒ����̓��蔻����s���܂�

	@param pRect	[in] �]������Q�c���ʏ�̋�`
	@param pLine	[in] �]������Q�c���ʏ�̐���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Line( CRect2D<Float> *pRect, CLine2D *pLine )
{
	Float x0 = pRect->x;
	Float y0 = pRect->y;
	Float x1 = pRect->x + pRect->w;
	Float y1 = pRect->y + pRect->h;

	CLine2D Lines[4] = {
		CLine2D( x0, y0, x1, y0 ),
		CLine2D( x1, y0, x1, y1 ),
		CLine2D( x1, y1, x0, y1 ),
		CLine2D( x0, y1, x0, y0 ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		if ( Line_Line( &Lines[i], pLine ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�l�p�Ƒ��p�`�̓��蔻����s���܂�

	@param pRect	[in] �]������Q�c���ʏ�̋�`
	@param pPoly	[in] �]������Q�c���ʏ�̃|���S��

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Polygon( CRect2D<Float> *pRect, CPolygon2D *pPoly )
{
	Float x0 = pRect->x;
	Float y0 = pRect->y;
	Float x1 = pRect->x + pRect->w;
	Float y1 = pRect->y + pRect->h;

	CVector2D Pts[5] = {
		CVector2D( x0, y0 ),
		CVector2D( x1, y0 ),
		CVector2D( x1, y1 ),
		CVector2D( x0, y1 ),
		CVector2D( x0, y0 ),
	};

	CPolygon2D Poly( 5, Pts );

	return Polygon_Polygon( pPoly, &Poly );
}

//-----------------------------------------------------------------------------------
/**
	�~�Ɖ~�̓��蔻����s���܂�

	@param pCir1	[in] �]������Q�c���ʏ�̉~
	@param pCir2	[in] �]������Q�c���ʏ�̉~

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Circle( CCircle *pCir1, CCircle *pCir2 )
{
	Float rx = pCir1->Center.x - pCir2->Center.x;
	Float ry = pCir1->Center.y - pCir2->Center.y;
	Float r = pCir1->Radius + pCir2->Radius;

	return ( (rx * rx + ry * ry) < (r * r) );
}

//-----------------------------------------------------------------------------------
/**
	�~�ƒ����̓��蔻����s���܂�

	@param pCir		[in] �]������Q�c���ʏ�̉~
	@param pLine	[in] �]������Q�c���ʏ�̐���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Line( CCircle *pCir, CLine2D *pLine )
{
	//====================================================
	// �܂��͒������̗��[���~�Ɋ܂܂��΂n�j
	//====================================================
	if ( Point_Circle( &pLine->Pt0, pCir ) ) return true;
	if ( Point_Circle( &pLine->Pt1, pCir ) ) return true;

	//====================================================
	// �~�̒��_�ƒ������܂ł̋��������߂�.
	//====================================================

	// �_���璼�����ɐ����ȒP�ʃx�N�g��(t1)�����߂�B
	static CVector2D s1, s2, s3, t1, t2, v;
	static Float z;

	// �x�N�g�� la - lb
	s1.x = pLine->Pt1.x - pLine->Pt0.x;
	s1.y = pLine->Pt1.y - pLine->Pt0.y;

	// �x�N�g�� la - cir
	s2.x = pCir->Center.x - pLine->Pt0.x;
	s2.y = pCir->Center.y - pLine->Pt0.y;

	// �x�N�g�� s1 �� s2 �̊O��
	// �Q������ԂȂ̂ły���ɕ��s�ȃx�N�g��
	z = s1.Cross( s2 );

	// �~�̒��S��������ɑ��݂���Ƃ��i�O�ς��O�ɂȂ�
	if ( z == 0 )
	{
		v.x = pCir->Center.x;
		v.y = pCir->Center.y;
	}
	else
	{
		// �x�N�g�� s1 �� s3 �̊O��
		// ���̃x�N�g���� la - lb �̐������ɂȂ�
		s3.x = +(s1.y * z);
		s3.y = -(s1.x * z);

		// �������x�N�g���̐��K��
		t1.Normalize( s3 );

		// ���ς��狗�����Z�o
		t2.x = pLine->Pt0.x - pCir->Center.x;
		t2.y = pLine->Pt0.y - pCir->Center.y;
		Float len = t1.Dot( t2 );

		// ��_�Ɖ~�̒��S�̋��������a�ȏ�Ȃ�m�f
		if ( len > pCir->Radius ) return false;

		// �~�̒��S���� la - lb �Ɉ������������̑��̍��W�����߂�
		v.x = pCir->Center.x + (t1.x * len);
		v.y = pCir->Center.y + (t1.y * len);
	}

	// v �� pLine->Pt0 - pLine->Pt1 �̊Ԃɂ���΂n�j
	if ( (pLine->Pt0.x < v.x) && (v.x < pLine->Pt1.x) ) return true;
	if ( (pLine->Pt1.x < v.x) && (v.x < pLine->Pt0.x) ) return true;
	if ( (pLine->Pt0.y < v.y) && (v.y < pLine->Pt1.y) ) return true;
	if ( (pLine->Pt1.y < v.y) && (v.y < pLine->Pt0.y) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�~�Ƒ��p�`�̓��蔻����s���܂�

	@param pCir		[in] �]������Q�c���ʏ�̉~
	@param pPoly	[in] �]������Q�c���ʏ�̃|���S��

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Polygon( CCircle *pCir, CPolygon2D *pPoly )
{
	Sint32 cnt = pPoly->Count - 1;

	// �~�̒��S�����p�`�Ɋ܂܂�Ă���Ȃ�n�j
	if ( Point_Polygon( &pCir->Center, pPoly ) ) return true;

	// ���p�`�̊e�ӂƉ~�̌�������
	for ( Sint32 i = 0; i < cnt; i++ )
	{
		CLine2D Line( pPoly->pPts[i+0].x, pPoly->pPts[i+0].y, pPoly->pPts[i+1].x, pPoly->pPts[i+1].y );

		if ( Circle_Line( pCir, &Line ) ) return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�����ƒ����̓��蔻����s���܂�

	@param pLine1	[in] �]������Q�c���ʏ�̐���
	@param pLine2	[in] �]������Q�c���ʏ�̐���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Line( CLine2D *pLine1, CLine2D *pLine2 )
{
	Float ret1, ret2;
	Float n1, n2;

	//-------------------------------------------
	// ��Ƀo�E���f�B���O�Ŕ���
	//-------------------------------------------
	CRect2D<Float> Rc1( pLine1->Pt0.x, pLine1->Pt0.y, pLine1->Pt1.x, pLine1->Pt1.y );
	CRect2D<Float> Rc2( pLine2->Pt0.x, pLine2->Pt0.y, pLine2->Pt1.x, pLine2->Pt1.y );
	if ( !Rect_Rect( &Rc1, &Rc2 ) ) return false;

	//-------------------------------------------
	// l1 �� l2 ���܂����ł��邩�ۂ�
	//-------------------------------------------
	n1 = Side( pLine2->Pt0.x, pLine2->Pt0.y, pLine1 );
	n2 = Side( pLine2->Pt1.x, pLine2->Pt1.y, pLine1 );
	ret1 = (n1 * n2);

	//-------------------------------------------
	// l2 �� l1 ���܂����ł��邩�ۂ�
	//-------------------------------------------
	n1 = Side( pLine1->Pt0.x, pLine1->Pt0.y, pLine2 );
	n2 = Side( pLine1->Pt1.x, pLine1->Pt1.y, pLine2 );
	ret2 = (n1 * n2);

	return ((ret1 <= 0.0f) && (ret2 <= 0.0f));
}

//-----------------------------------------------------------------------------------
/**
	�����Ƒ��p�`�̓��蔻����s���܂�

	@param pLine	[in] �]������Q�c���ʏ�̐���
	@param pPoly	[in] �]������Q�c���ʏ�̃|���S��

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Polygon( CLine2D *pLine, CPolygon2D *pPoly )
{
	Sint32 cnt = pPoly->Count;

	// �������̊e�[�����p�`�Ɋ܂܂�Ă��邩�`�F�b�N
	if ( Point_Polygon( &pLine->Pt0, pPoly ) ) return true;
	if ( Point_Polygon( &pLine->Pt1, pPoly ) ) return true;

	// ���p�`�̊e�ӂƒ������̌�������
	for ( Sint32 i = 0; i < cnt - 1; i++ )
	{
		CLine2D Line( pPoly->pPts[i+0].x, pPoly->pPts[i+0].y, pPoly->pPts[i+1].x, pPoly->pPts[i+1].y );

		if ( Line_Line( &Line, pLine ) ) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------
/**
	���p�`�Ƒ��p�`�̓��蔻����s���܂�

	@param pPoly1	[in] �]������Q�c���ʏ�̃|���S��
	@param pPoly2	[in] �]������Q�c���ʏ�̃|���S��

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Polygon_Polygon( CPolygon2D *pPoly1, CPolygon2D *pPoly2 )
{
	Sint32 cnt1 = pPoly1->Count-1;
	Sint32 cnt2 = pPoly2->Count-1;

	//==========================================================
	// �o�E���f�B���O�{�b�N�X�Z�o
	//==========================================================
	Float x11 = pPoly1->pPts[0].x, x12 = pPoly1->pPts[0].x;
	Float y11 = pPoly1->pPts[0].y, y12 = pPoly1->pPts[0].y;
	Float x21 = pPoly2->pPts[0].x, x22 = pPoly2->pPts[0].x;
	Float y21 = pPoly2->pPts[0].y, y22 = pPoly2->pPts[0].y;

	for ( Sint32 i = 1; i < cnt1; i++ )
	{
		if ( pPoly1->pPts[i].x < x11 ) x11 = pPoly1->pPts[i].x;
		ef ( pPoly1->pPts[i].x > x12 ) x12 = pPoly1->pPts[i].x;
		if ( pPoly1->pPts[i].y < y11 ) y11 = pPoly1->pPts[i].y;
		ef ( pPoly1->pPts[i].y > y12 ) y12 = pPoly1->pPts[i].y;
	}
	for ( Sint32 i = 1; i < cnt2; i++ )
	{
		if ( pPoly2->pPts[i].x < x21 ) x21 = pPoly2->pPts[i].x;
		ef ( pPoly2->pPts[i].x > x22 ) x22 = pPoly2->pPts[i].x;
		if ( pPoly2->pPts[i].y < y21 ) y21 = pPoly2->pPts[i].y;
		ef ( pPoly2->pPts[i].y > y22 ) y22 = pPoly2->pPts[i].y;
	}

	//----------------------------------------------------------
	// �o�E���f�B���O�{�b�N�X�̐ڐG����
	//----------------------------------------------------------
	if ( x11 > x22 ) return false;
	if ( x12 < x21 ) return false;
	if ( y11 > y22 ) return false;
	if ( y12 < y21 ) return false;

	//==========================================================
	// �O�ςŔ���
	//==========================================================

	//----------------------------------------------------------
	// p1�̊e���_��p2�̋�`���ɓ����Ă��邩
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < cnt1; i++ )
	{
		if ( Point_Polygon( &pPoly1->pPts[i], pPoly2 ) )
		{
			return true;
		}
	}

	//----------------------------------------------------------
	// p2�̊e���_��p1�̋�`���ɓ����Ă��邩
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < cnt2; i++ )
	{
		if ( Point_Polygon( &pPoly2->pPts[i], pPoly1 ) )
		{
			return true;
		}
	}

	//==========================================================
	// �e���_���������̌�������
	//==========================================================
	for ( Sint32 i = 0; i < cnt1; i++ )
	{
		for ( Sint32 j = 0; j < cnt2; j++ )
		{
			CLine2D Line1( pPoly1->pPts[i+0].x, pPoly1->pPts[i+0].y, pPoly1->pPts[i+1].x, pPoly1->pPts[i+1].y );
			CLine2D Line2( pPoly2->pPts[j+0].x, pPoly2->pPts[j+0].y, pPoly2->pPts[j+1].x, pPoly2->pPts[j+1].y );

			if ( Line_Line( &Line1, &Line2 ) ) return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�_�Ɠ_�̓��蔻����s���܂�

	@param pPt1	[in] �]������R�c��ԓ��̓_
	@param pPt2	[in] �]������R�c��ԓ��̓_

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Point_3D( CVector3D *pPt1, CVector3D *pPt2 )
{
	if ( pPt1->x != pPt2->x ) return false;
	if ( pPt1->y != pPt2->y ) return false;
	if ( pPt1->z != pPt2->z ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�_�Ƌ��̓��蔻����s���܂�

	@param pPt		[in] �]������R�c��ԓ��̓_
	@param pSph		[in] �]������R�c��ԓ��̋�

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Sphere_3D( CVector3D *pPt, CSphere *pSph )
{
	CSphere Cir( *pPt, 0.0f );

	return Sphere_Sphere_3D( pSph, &Cir );
}

//-----------------------------------------------------------------------------------
/**
	�_�ƒ����̓��蔻����s���܂�

	@param pPt		[in] �]������R�c��ԓ��̓_
	@param pLine	[in] �]������R�c��ԓ��̐���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Line_3D( CVector3D *pPt, CLine3D *pLine )
{
	CSphere Cir( *pPt, 1.0f );

	return Sphere_Line_3D( &Cir, pLine );
}

//-----------------------------------------------------------------------------------
/**
	�_�Ɩʂ̓��蔻����s���܂�

	@param pPt		[in] �]������R�c��ԓ��̓_
	@param pPlane	[in] �]������R�c��ԓ��̕���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Plane_3D( CVector3D *pPt, CPlane *pPlane )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
	�_�Ɣ��̓��蔻����s���܂�

	@param pPt	[in] �]������R�c��ԓ��̓_
	@param pBox	[in] �]������R�c��ԓ��̔�

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Box_3D( CVector3D *pPt, CBox *pBox )
{
	Uint8 bOutside = 0x00;
	for ( Sint32 i = 0; i < 6; i++ )
	{
		Float res =
			pBox->Planes[i].a * pPt->x +
			pBox->Planes[i].b * pPt->y +
			pBox->Planes[i].c * pPt->z +
			pBox->Planes[i].d;

		if ( res < 0 ) bOutside |= (1 << i);
	}

	// �|�C���g��6�̕��ʂ��ׂĂ̓����ł���ꍇ�{�b�N�X���ɂ���܂�
	return (bOutside == 0);
}

//-----------------------------------------------------------------------------------
/**
	���Ƌ��̓��蔻����s���܂�

	@param pSph1	[in] �]������R�c��ԓ��̋�
	@param pSph2	[in] �]������R�c��ԓ��̋�

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Sphere_3D( CSphere *pSph1, CSphere *pSph2 )
{
	Float rx = pSph1->Center.x - pSph2->Center.x;
	Float ry = pSph1->Center.y - pSph2->Center.y;
	Float rz = pSph1->Center.z - pSph2->Center.z;
	Float r = pSph1->Radius + pSph2->Radius;

	return (rx * rx) + (ry * ry) + (rz * rz) < (r * r);
}

//-----------------------------------------------------------------------------------
/**
	���ƒ����̓��蔻����s���܂�

	@param pSph		[in] �]������R�c��ԓ��̋�
	@param pLine	[in] �]������R�c��ԓ��̐���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Line_3D( CSphere *pSph, CLine3D *pLine )
{
	//====================================================
	// �܂��͒������̗��[�����Ɋ܂܂�Ă��邩�`�F�b�N
	//====================================================
	Float r = pSph->Radius;
	Float rx1 = pSph->Center.x - pLine->Pt0.x;
	Float ry1 = pSph->Center.y - pLine->Pt0.y;
	Float rz1 = pSph->Center.z - pLine->Pt0.z;
	Float rx2 = pSph->Center.x - pLine->Pt1.x;
	Float ry2 = pSph->Center.y - pLine->Pt1.y;
	Float rz2 = pSph->Center.z - pLine->Pt1.z;

	if ( ((rx1 * rx1) + (ry1 * ry1) + (rz1 * rz1)) < (r * r) ) return true;
	if ( ((rx2 * rx2) + (ry2 * ry2) + (rz2 * rz2)) < (r * r) ) return true;

	//====================================================
	// ���̒��_�ƒ����܂ł̋��������߂�.
	//====================================================

	// �_���璼���ɐ����ȒP�ʃx�N�g��(t1)�����߂�B
	static CVector3D s1, s2, s3, s4, t1, t2, v;

	// �x�N�g�� la - lb
	s1.x = pLine->Pt1.x - pLine->Pt0.x;
	s1.y = pLine->Pt1.y - pLine->Pt0.y;
	s1.z = pLine->Pt1.z - pLine->Pt0.z;

	// �x�N�g�� la - cir
	s2.x = pSph->Center.x - pLine->Pt0.x;
	s2.y = pSph->Center.y - pLine->Pt0.y;
	s2.z = pSph->Center.z - pLine->Pt0.z;

	// s1, s2 �̊O�� s3
	s3.Cross( s1, s2 );

	// s1, s3 �̊O�� s4 = ������
	s4.Cross( s1, s3 );

	// ���K��
	t1.Normalize( s4 );

	// ���ς��狗�����Z�o
	t2.x = pLine->Pt0.x - pSph->Center.x;
	t2.y = pLine->Pt0.y - pSph->Center.y;
	t2.z = pLine->Pt0.z - pSph->Center.z;
	Float len = t1.Dot( t2 );

	// ��_�Ɖ~�̒��S�̋��������a�ȏ�Ȃ�m�f
	if ( len > r ) return false;

	// ���̒��S(cir)���璼��(pLine->a, pLine->b)�Ɉ������������̑��̍��W(v)
	v.x = pSph->Center.x + (t1.x * len);
	v.y = pSph->Center.y + (t1.y * len);
	v.z = pSph->Center.z + (t1.z * len);
	
	// v��pLine->a��pLine->b�̊Ԃɂ���΂n�j
	if ( (pLine->Pt0.x < v.x) && (v.x < pLine->Pt1.x) ) return true;
	if ( (pLine->Pt1.x < v.x) && (v.x < pLine->Pt0.x) ) return true;
	if ( (pLine->Pt0.y < v.y) && (v.y < pLine->Pt1.y) ) return true;
	if ( (pLine->Pt1.y < v.y) && (v.y < pLine->Pt0.y) ) return true;
	if ( (pLine->Pt0.z < v.z) && (v.z < pLine->Pt1.z) ) return true;
	if ( (pLine->Pt1.z < v.z) && (v.z < pLine->Pt0.z) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
	���Ɩʂ̓��蔻����s���܂�<BR>
	���̊֐��͖������ł��̂ŁA���̕��@�ł̔���𐄏����܂��B

	@param pSph		[in] �]������R�c��ԓ��̋�
	@param pPlane	[in] �]������R�c��ԓ��̕���

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Plane( CSphere *pSph, CPlane *pPlane )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
	���Ɣ��̓��蔻����s���܂�<BR>
	���̊֐��͖������ł��̂ŁA���̕��@�ł̔���𐄏����܂��B

	@param pSph		[in] �]������R�c��ԓ��̋�
	@param pBox		[in] �]������R�c��ԓ��̔�

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Box_3D( CSphere *pSph, CBox *pBox )
{
	// ���̒��S�����̒��ɓ����Ă���΂n�j
	if ( Point_Box_3D( &pSph->Center, pBox ) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�����Ɩʂ̓��蔻����s���܂�

	@param pLine	[in] �]������R�c��ԓ��̐���
	@param pPlane	[in] �]������R�c��ԓ��̕���
	@param pPoints	[in] pPlane��̔C�ӂ̂R�_
	@param pPos		[out] �Փˍ��W�i�[��


	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Plane_3D( CLine3D *pLine, CPlane *pPlane, CVector3D *pPoints, CVector3D *pPos )
{
	CVector3D VecP;
	CVector3D VecQ;
	CVector3D VecT;
	Float fDet;
	Float fInvDet;
	Float ParamT, ParamU, ParamV;

	// �����̗��[�������ʂ��܂����ő��݂��Ă��邩���`�F�b�N
	Float fDist0 = (pPlane->a * pLine->Pt0.x) + (pPlane->b * pLine->Pt0.y) + (pPlane->c * pLine->Pt0.z) + pPlane->d;
	Float fDist1 = (pPlane->a * pLine->Pt1.x) + (pPlane->b * pLine->Pt1.y) + (pPlane->c * pLine->Pt1.z) + pPlane->d;
	if ( (fDist0 * fDist1) >= 0.0f ) return false;

	CVector3D Start = CVector3D(pLine->Pt0.x,pLine->Pt0.y,pLine->Pt0.z);
	CVector3D Dir = CVector3D(pLine->Pt1.x,pLine->Pt1.y,pLine->Pt1.z) - Start;
	CVector3D Vx[] = {
		CVector3D(pPoints[0].x,pPoints[0].y,pPoints[0].z),
		CVector3D(pPoints[1].x,pPoints[1].y,pPoints[1].z),
		CVector3D(pPoints[2].x,pPoints[2].y,pPoints[2].z),
	};

	// Vx[0]�����L����Q�x�N�g�����Z�o
	CVector3D Edge1 = Vx[1] - Vx[0];
	CVector3D Edge2 = Vx[2] - Vx[0];

	// U�p�����[�^�[���v�Z
	VecP.Cross( Dir, Edge2 );

    // ���ς��O�ɋ߂��ꍇ�͎O�p�`�̕��ʂɂ���
	fDet = Edge1.Dot( VecP );
	if ( fDet > 0 )
	{
		VecT = Start - Vx[0];
	}
	else
	{
		VecT = Vx[0] - Start;
		fDet = -fDet;
	}

	if ( fDet < 0.0001f ) return false;

	// U�p�����[�^�[����уe�X�g���E���v�Z
	ParamU = VecT.Dot( VecP );
	if ( (ParamU < 0.0f) || (ParamU > fDet) ) return false;

	// V�p�����[�^�[���e�X�g���鏀�������܂�
	VecQ.Cross( VecT, Edge1 );

	// V�p�����[�^�[����уe�X�g���E���v�Z
	ParamV = Dir.Dot( VecQ );
	if ( (ParamV < 0.0f) || ((ParamU + ParamV) > fDet) ) return false;

	// T���v�Z���A�X�P�[�����O
	ParamT = Edge2.Dot( VecQ );
	fInvDet = 1.0f / fDet;
	ParamT *= fInvDet;
	ParamU *= fInvDet;
	ParamV *= fInvDet;

	// �ʒu����ۑ�
	if ( pPos != NULL )
	{
		pPos->x = Vx[0].x + (ParamU * (Vx[1].x - Vx[0].x)) + (ParamV * (Vx[2].x - Vx[0].x));
		pPos->y = Vx[0].y + (ParamU * (Vx[1].y - Vx[0].y)) + (ParamV * (Vx[2].y - Vx[0].y));
		pPos->z = Vx[0].z + (ParamU * (Vx[1].z - Vx[0].z)) + (ParamV * (Vx[2].z - Vx[0].z));
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�����Ɣ��̓��蔻����s���܂�

	@param pLine	[in] �]������R�c��ԓ��̐���
	@param pBox		[in] �]������R�c��ԓ��̔�

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Box_3D( CLine3D *pLine, CBox *pBox )
{
	// ���̒��ɓ_�������Ă��邩�`�F�b�N
	if ( Point_Box_3D( &pLine->Pt0, pBox ) ) return true;
	if ( Point_Box_3D( &pLine->Pt1, pBox ) ) return true;

	// ���ʂƐ������������Ă��邩�`�F�b�N
	CVector3D Face[][4] =
	{
		{ pBox->Points[0], pBox->Points[2], pBox->Points[3], pBox->Points[1] }, // front
		{ pBox->Points[4], pBox->Points[5], pBox->Points[7], pBox->Points[6] }, // back
		{ pBox->Points[0], pBox->Points[4], pBox->Points[6], pBox->Points[2] }, // left
		{ pBox->Points[1], pBox->Points[3], pBox->Points[7], pBox->Points[5] }, // right
		{ pBox->Points[2], pBox->Points[6], pBox->Points[7], pBox->Points[3] }, // top
		{ pBox->Points[0], pBox->Points[4], pBox->Points[5], pBox->Points[1] }, // bottom
	};

	for ( Sint32 j = 0; j < 6; j++ )
	{
		if ( EdgeIntersectsQuad( (CVector3D*)pLine, Face[j], &pBox->Planes[j], NULL ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�����ƎO�p�`�̓��蔻����s���܂�

	@param pLine	[in] �]������R�c��ԓ��̐���
	@param Points	[in] �]������R�c��ԓ��̎O�p�`���\������_
	@param pT		[out] T�p�����[�^�[�i�[��
	@param pU		[out] U�p�����[�^�[�i�[��
	@param pV		[out] V�p�����[�^�[�i�[��

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Triangle_3D( CLine3D* pLine, CVector3D Points[], Float *pT, Float *pU, Float *pV )
{
	CVector3D VecP;
	CVector3D VecQ;
	CVector3D VecT;
	Float fDet;
	Float fInvDet;

	CVector3D Start = CVector3D(pLine->Pt0.x,pLine->Pt0.y,pLine->Pt0.z);
	CVector3D Dir = CVector3D(pLine->Pt1.x,pLine->Pt1.y,pLine->Pt1.z) - Start;
	CVector3D Vx[] = {
		CVector3D(Points[0].x,Points[0].y,Points[0].z),
		CVector3D(Points[1].x,Points[1].y,Points[1].z),
		CVector3D(Points[2].x,Points[2].y,Points[2].z),
	};

	Dir.Normalize();

	// pV0�����L����Q�x�N�g�����Z�o
	CVector3D Edge1 = Vx[1] - Vx[0];
	CVector3D Edge2 = Vx[2] - Vx[0];

	// U�p�����[�^�[���v�Z
	VecP.Cross( Dir, Edge2 );

    // ���ς��O�ɋ߂��ꍇ�͎O�p�`�̕��ʂɂ���
	fDet = Edge1.Dot( VecP );
	if ( fDet > 0 )
	{
		VecT = Start - Vx[0];
	}
	else
	{
		VecT = Vx[0] - Start;
		fDet = -fDet;
	}

	if ( fDet < 0.0001f ) return false;

	// U�p�����[�^�[����уe�X�g���E���v�Z
	*pU = VecT.Dot( VecP );
	if ( (*pU < 0.0f) || (*pU > fDet) ) return false;

	// V�p�����[�^�[���e�X�g���鏀�������܂�
	VecQ.Cross( VecT, Edge1 );

	// V�p�����[�^�[����уe�X�g���E���v�Z
	*pV = Dir.Dot( VecQ );
	if ( (*pV < 0.0f) || ((*pU + *pV) > fDet) ) return false;

	// T���v�Z���A�X�P�[�����O
	*pT = Edge2.Dot( VecQ );
	fInvDet = 1.0f / fDet;
	*pT *= fInvDet;
	*pU *= fInvDet;
	*pV *= fInvDet;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�ʂƖʂ̐ڐG��������܂�

	@param pPlane1			[in] ���ʂP
	@param pPlane2			[in] ���ʂQ
	@param Points1[]		[in] ���ʂP���\������S�_
	@param Points2[]		[in] ���ʂQ���\������S�_

	@retval true		�������Ă���
	@retval false		�������Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Plane_Plane_3D( CPlane *pPlane1, CPlane *pPlane2, CVector3D Points1[], CVector3D Points2[] )
{
	CVector3D Edge[2];

	Edge[0] = Points1[0]; Edge[1] = Points1[1];
	if ( EdgeIntersectsQuad( Edge, Points2, pPlane2, NULL ) ) return true;

	Edge[0] = Points1[1]; Edge[1] = Points1[2];
	if ( EdgeIntersectsQuad( Edge, Points2, pPlane2, NULL ) ) return true;

	Edge[0] = Points1[2]; Edge[1] = Points1[3];
	if ( EdgeIntersectsQuad( Edge, Points2, pPlane2, NULL ) ) return true;

	Edge[0] = Points1[3]; Edge[1] = Points1[4];
	if ( EdgeIntersectsQuad( Edge, Points2, pPlane2, NULL ) ) return true;

	Edge[0] = Points2[0]; Edge[1] = Points2[1];
	if ( EdgeIntersectsQuad( Edge, Points1, pPlane1, NULL ) ) return true;

	Edge[0] = Points2[1]; Edge[1] = Points2[2];
	if ( EdgeIntersectsQuad( Edge, Points1, pPlane1, NULL ) ) return true;

	Edge[0] = Points2[2]; Edge[1] = Points2[3];
	if ( EdgeIntersectsQuad( Edge, Points1, pPlane1, NULL ) ) return true;

	Edge[0] = Points2[3]; Edge[1] = Points2[4];
	if ( EdgeIntersectsQuad( Edge, Points1, pPlane1, NULL ) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�S�_�ō\������镽�ʂƒ����̌���������s���܂�

	@param pEdges		[in] ����
	@param pFacePoints	[in] ���ʂ̓_�i�S�_�j
	@param pPlane		[in] �`�F�b�N���镽��
	@param pHitPos		[out] ���ʂƂ̌����ʒu

	@retval true		�������Ă���
	@retval false		���������Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::EdgeIntersectsQuad( CVector3D* pEdges, CVector3D* pFacePoints, CPlane* pPlane, CVector3D *pHitPos )
{
	CVector3D Intersection;
	CVector2D FacePoints[5];
	CVector2D Point;

	// ���[�̃|�C���g�����ʂ̓������ɂ���ꍇ�A�ʂƌ������܂���
	Float fDist1 = pPlane->a * pEdges[0].x + pPlane->b * pEdges[0].y + pPlane->c * pEdges[0].z + pPlane->d;
	Float fDist2 = pPlane->a * pEdges[1].x + pPlane->b * pEdges[1].y + pPlane->c * pEdges[1].z + pPlane->d;
	if ( (fDist1 * fDist2) > 0 ) return false;

	// ��������ѕ��ʂ̊Ԃ̌�_�������܂�
	//  ����炪���s�̏ꍇ�A�����Ɩʂ͌������܂���
	//  ���̂Ƃ� ::D3DXPlaneIntersectLine() �� NULL ��Ԃ��܂�
	if ( !LineIntersectPlane( Intersection, *pPlane, pEdges[0], pEdges[1] ) ) return false;
	if ( pHitPos != NULL ) *pHitPos = Intersection;

	// �|���S�����̒��_�ʒu���e�X�g���邽�߂Q�c���ʏ�ւ̃v���W�F�N�g
	Float fAbsA = (pPlane->a > 0 ? pPlane->a : -pPlane->a);
	Float fAbsB = (pPlane->b > 0 ? pPlane->b : -pPlane->b);
	Float fAbsC = (pPlane->c > 0 ? pPlane->c : -pPlane->c);
	if ( (fAbsA > fAbsB) && (fAbsA > fAbsC) )
	{
		// �w�����s�Ȃ̂łx�Ƃy���g�p���Čv�Z
		for( Sint32 i = 0; i < 4; i++)
		{
			FacePoints[i].x = pFacePoints[i].y;
			FacePoints[i].y = pFacePoints[i].z;
		}
		Point.x = Intersection.y;
		Point.y = Intersection.z;
	}
	ef ( (fAbsB > fAbsA) && (fAbsB > fAbsC) )
	{
		// �x�����s�Ȃ̂łw�Ƃy���g�p���Čv�Z
		for ( Sint32 i = 0; i < 4; i++)
		{
			FacePoints[i].x = pFacePoints[i].x;
			FacePoints[i].y = pFacePoints[i].z;
		}
		Point.x = Intersection.x;
		Point.y = Intersection.z;
	}
	else
	{
		// �y�����s�Ȃ̂łw�Ƃx���g�p���Čv�Z
		for ( Sint32 i = 0; i < 4; i++)
		{
			FacePoints[i].x = pFacePoints[i].x;
			FacePoints[i].y = pFacePoints[i].y;
		}
		Point.x = Intersection.x;
		Point.y = Intersection.y;
	}

	FacePoints[4] = FacePoints[0];

	// ���_�����ʂ̂̊O����ɂ���ꍇ�A���̒��_�����ʂ̊O���ɂ���܂�
	// ���̃}�g���b�N�X�̌���v�f���Ƃ邱�Ƃɂ�肱������邱�Ƃ��ł��܂�
	// | x0 y0 1 |
	// | x1 y1 1 |
	// | x2 y2 1 |
	Float x0 = FacePoints[0].x;
	Float y0 = FacePoints[0].y;
	Float x1 = FacePoints[1].x;
	Float y1 = FacePoints[1].y;
	Float x2 = FacePoints[2].x;
	Float y2 = FacePoints[2].y;
	Bool bClockwise = ((x1*y2 - y1*x2 - x0*y2 + y0*x2 + x0*y1 - y0*x1) < 0);

	x2 = Point.x;
	y2 = Point.y;
	for ( Sint32 i = 0; i < 4; i++ )
	{
		x0 = FacePoints[i].x;
		y0 = FacePoints[i].y;
		x1 = FacePoints[i+1].x;
		y1 = FacePoints[i+1].y;

		if ( ((x1*y2 - y1*x2 - x0*y2 + y0*x2 + x0*y1 - y0*x1) > 0) == bClockwise ) return false;
	}

	// �|�C���g�͖ʂ��ׂĂ̓����ɂ���܂�
	return true;
}


//-----------------------------------------------------------------------------------
/**
	���Ɣ��̓��蔻����s���܂�

	@param pBox1	[in] �]������R�c��ԓ��̔�
	@param pBox2	[in] �]������R�c��ԓ��̔�

	@retval true	�Փ˂��Ă���
	@retval false	�Փ˂��Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Box_Box_3D( CBox &Box0, CBox &Box1 )
{
	Uint8 bOutside[8];

	//-----------------------------------------------------------------------------------======================
	// �r���[�t���X�^���̒[�̃G�b�W�̂ǂꂩ���o�E���f�B���O�{�b�N�X�̖ʂ̂����̂ǂꂩ�ɐڐG���邩
	// �݂��̔��̒��Ɍ݂��̓_�������Ă��邩�`�F�b�N
	//-----------------------------------------------------------------------------------======================
	for ( Uint32 i = 0; i < 8; i++ )
	{
		bOutside[i] = 0x00;
		for ( Sint32 j = 0; j < 6; j++ )
		{
			Float fRet =
				Box0.Planes[j].a * Box1.Points[i].x +
				Box0.Planes[j].b * Box1.Points[i].y +
				Box0.Planes[j].c * Box1.Points[i].z +
				Box0.Planes[j].d;

			if ( fRet < 0 ) bOutside[i] |= (1 << j);
		}

		// �|�C���g���U�̃r���[�t���X�^�����ʂ��ׂĂ̓����ł���ꍇ
		// �r���[�t���X�^�����ɂ���܂�
		if ( bOutside[i] == 0 ) return true;
	}

	// �|�C���g�����ׂĔC�ӂ̒P��̃r���[�t���X�^�����ʂ̊O���ɂ���ꍇ
	// �I�u�W�F�N�g�̓r���[�t���X�^���O�ɂ���܂��B
	if ( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0x00 )
	{
		return false;
	}

	//-----------------------------------------------------------------------------------======================
	// �r���[�t���X�^���̒[�̃G�b�W�̂ǂꂩ���o�E���f�B���O�{�b�N�X�̖ʂ̂����̂ǂꂩ�ɐڐG���邩
	// �݂��̔��̒��Ɍ݂��̓_�������Ă��邩�`�F�b�N
	//-----------------------------------------------------------------------------------======================
	for ( Uint32 i = 0; i < 8; i++ )
	{
		bOutside[i] = 0x00;
		for ( Sint32 j = 0; j < 6; j++ )
		{
			Float fRet =
				Box1.Planes[j].a * Box0.Points[i].x +
				Box1.Planes[j].b * Box0.Points[i].y +
				Box1.Planes[j].c * Box0.Points[i].z +
				Box1.Planes[j].d;

			if ( fRet < 0 ) bOutside[i] |= (1 << j);
		}

		// �|�C���g���U�̃r���[�t���X�^�����ʂ��ׂĂ̓����ł���ꍇ
		// �r���[�t���X�^�����ɂ���܂�
		if ( bOutside[i] == 0 ) return true;
	}

	// �|�C���g�����ׂĔC�ӂ̒P��̃r���[�t���X�^�����ʂ̊O���ɂ���ꍇ
	// �I�u�W�F�N�g�̓r���[�t���X�^���O�ɂ���܂��B
	if ( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0x00 )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	// ���f��OBB�G�b�W�̂ǂꂩ���J����OBB�ʂ̂����̂ǂꂩ�ɐڐG���邩
	//------------------------------------------------------------------------------
	{
		CVector3D *pEdge[12][2] = {
			{ &Box1.Points[0], &Box1.Points[1] },
			{ &Box1.Points[1], &Box1.Points[2] },
			{ &Box1.Points[2], &Box1.Points[3] },
			{ &Box1.Points[3], &Box1.Points[0] },
			{ &Box1.Points[4], &Box1.Points[5] },
			{ &Box1.Points[5], &Box1.Points[6] },
			{ &Box1.Points[6], &Box1.Points[7] },
			{ &Box1.Points[7], &Box1.Points[4] },
			{ &Box1.Points[0], &Box1.Points[4] },
			{ &Box1.Points[1], &Box1.Points[5] },
			{ &Box1.Points[2], &Box1.Points[6] },
			{ &Box1.Points[3], &Box1.Points[7] },
		};
		CVector3D *pPlanePoint[6][4] = {
			{ &Box0.Points[0], &Box0.Points[1], &Box0.Points[5], &Box0.Points[4] }, // front
			{ &Box0.Points[2], &Box0.Points[3], &Box0.Points[7], &Box0.Points[6] }, // back
			{ &Box0.Points[3], &Box0.Points[2], &Box0.Points[1], &Box0.Points[0] }, // left
			{ &Box0.Points[4], &Box0.Points[5], &Box0.Points[6], &Box0.Points[7] }, // right
			{ &Box0.Points[1], &Box0.Points[2], &Box0.Points[6], &Box0.Points[5] }, // top
			{ &Box0.Points[0], &Box0.Points[4], &Box0.Points[7], &Box0.Points[3] }, // bottom
		};

		for( long iEdge = 0; iEdge < 12; iEdge++ )
		{
			for( long iPlane = 0; iPlane < 6; iPlane++ )
			{
				if ( LineIntersectPolygon( pEdge[iEdge], Box0.Planes[iPlane], pPlanePoint[iPlane], 4 ) )
				{
					return true;
				}
			}
		}
	}

	//------------------------------------------------------------------------------
	// �J����OBB�G�b�W�̂ǂꂩ�����f��OBB�ʂ̂����̂ǂꂩ�ɐڐG���邩
	//------------------------------------------------------------------------------
	{
		CVector3D *pEdge[12][2] = {
			{ &Box0.Points[0], &Box0.Points[1] },
			{ &Box0.Points[1], &Box0.Points[2] },
			{ &Box0.Points[2], &Box0.Points[3] },
			{ &Box0.Points[3], &Box0.Points[0] },
			{ &Box0.Points[4], &Box0.Points[5] },
			{ &Box0.Points[5], &Box0.Points[6] },
			{ &Box0.Points[6], &Box0.Points[7] },
			{ &Box0.Points[7], &Box0.Points[4] },
			{ &Box0.Points[0], &Box0.Points[4] },
			{ &Box0.Points[1], &Box0.Points[5] },
			{ &Box0.Points[2], &Box0.Points[6] },
			{ &Box0.Points[3], &Box0.Points[7] },
		};
		CVector3D *pPlanePoint[6][4] = {
			{ &Box1.Points[0], &Box1.Points[1], &Box1.Points[5], &Box1.Points[4] }, // front
			{ &Box1.Points[2], &Box1.Points[3], &Box1.Points[7], &Box1.Points[6] }, // back
			{ &Box1.Points[3], &Box1.Points[2], &Box1.Points[1], &Box1.Points[0] }, // left
			{ &Box1.Points[4], &Box1.Points[5], &Box1.Points[6], &Box1.Points[7] }, // right
			{ &Box1.Points[1], &Box1.Points[2], &Box1.Points[6], &Box1.Points[5] }, // top
			{ &Box1.Points[0], &Box1.Points[4], &Box1.Points[7], &Box1.Points[3] }, // bottom
		};

		for( long iEdge = 0; iEdge < 12; iEdge++ )
		{
			for( long iPlane = 0; iPlane < 6; iPlane++ )
			{
				if ( LineIntersectPolygon( pEdge[iEdge], Box1.Planes[iPlane], pPlanePoint[iPlane], 4 ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	�|���S���Ɛ����̌�_���Z�o���܂��B

	@param Intersection	[out] ��_�i�[��
	@param Plane		[in] ����
	@param Pt0			[in] �����̒[
	@param Pt1			[in] �����̒[

	@retval true		�������Ă���
	@retval false		�������Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::LineIntersectPolygon( CVector3D *pPtTbl[], CPlane &Plane, CVector3D *pPlanePoints[], Uint32 Count )
{
	// ��������ѕ��ʂ̊Ԃ̌�_�������܂�
	CVector3D Intersect;
	if ( !LineIntersectPlane( Intersect, Plane, *pPtTbl[0], *pPtTbl[1] ) )
	{
		return false;
	}

	// ���ʂ̖@��
	CVector3D vNorm( Plane.a, Plane.b, Plane.c );

	// �e�G�b�W�ƌ�_�̊O�ς����߂�
	for ( Uint32 i = 0; i < Count; i++ )
	{
		CVector3D v1 = *pPlanePoints[(i + 0) % Count] - Intersect;
		CVector3D v2 = *pPlanePoints[(i + 1) % Count] - Intersect;

		// ��_���g�����ꍇ�̖@��
		CVector3D vOut;
		vOut.Cross( v1, v2 );

		// �����`�F�b�N
		// ���������̃x�N�g�����m�̓��ς́{�ɂȂ�
		if ( vOut.Dot( vNorm ) < 0.0f )
		{
			return false;
		}
	}

	// �|�C���g�̓G�b�W�̓����ɂ���
	return true;
}

//-----------------------------------------------------------------------------------
/**
	�ʂƒ����̌�_���Z�o���܂�

	@param Intersection		[out] ��_�i�[��
	@param pPlane			[in] ����
	@param pPt0			[in] �����̒[
	@param pPt1			[in] �����̒[

	@retval true		�������Ă���
	@retval false		�������Ă��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::LineIntersectPlane( CVector3D &vIntersection, CPlane &Plane, CVector3D &Pt0, CVector3D &Pt1 )
{
	// ���[�̃|�C���g�����ʂ̓������ɂ���ꍇ�͖ʂƌ������܂���
	Float fDot0 = Plane.Dot( Pt0 );
	Float fDot1 = Plane.Dot( Pt1 );
	if ( fDot0 * fDot1 >= 0.0f )
	{
		return false;
	}

	// �����x�N�g��
	CVector3D vDir = Pt1 - Pt0;

	// �}��ϐ������߂�
	Float t = -fDot0 / Plane.Dot( vDir, 0.0f );
	if ( (t < 0.0f) || (t > 1.0f) )
	{
		return false;
	}

	// �}��ϐ������_�����߂�
	vIntersection = Pt0 + (vDir * t);

	return true;
}

//-----------------------------------------------------------------------------------
/**
	Collision�N���X�Ŏg�p���锠�f�[�^�̍쐬���s���܂�

	@param Out		[out] ���f�[�^�i�[��
	@param MinPt	[in] ���̃o�E���f�B���O�{�b�N�X�ŏ��_
	@param MaxPt	[in] ���̃o�E���f�B���O�{�b�N�X�ő�_
	@param Matrix	[in] ���ʏ�̔C�ӂ̓_
*/
//-----------------------------------------------------------------------------------
void Selene::Collision::CreateBox( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix )
{
	CVector3D LocalBB[] = {
		CVector3D( MinPt.x, MinPt.y, MinPt.z ), // xyz
		CVector3D( MinPt.x, MaxPt.y, MinPt.z ), // xYz
		CVector3D( MinPt.x, MaxPt.y, MaxPt.z ), // xYZ
		CVector3D( MinPt.x, MinPt.y, MaxPt.z ), // xyZ
		CVector3D( MaxPt.x, MinPt.y, MinPt.z ), // Xyz
		CVector3D( MaxPt.x, MaxPt.y, MinPt.z ), // XYz
		CVector3D( MaxPt.x, MaxPt.y, MaxPt.z ), // XYZ
		CVector3D( MaxPt.x, MinPt.y, MaxPt.z ), // XyZ
	};

	// ���[�J�����W�n���烏�[���h���W�n�Ƀo�E���f�B���O�{�b�N�X���g�����X�t�H�[�����܂�
	for ( Uint32 i = 0; i < 8; i++ )
	{
		Out.Points[i].TransformCoord( LocalBB[i], Matrix );
	}

    // �o�E���f�B���O�{�b�N�X�̖ʂ𐶐����܂�
	Out.Update();
}

//-----------------------------------------------------------------------------------
/**
	Collision�N���X�Ŏg�p���锠�f�[�^�̍쐬���s���܂�<BR>
	�v���W�F�N�V�������l�����ăf�[�^�쐬���s���̂ŁA<BR>
	�r���[�t���X�^���Ȃǂ̐����ɓK���Ă��܂��B

	@param Out		[out] ���f�[�^�i�[��
	@param MinPt	[in] ���̃o�E���f�B���O�{�b�N�X�ŏ��_
	@param MaxPt	[in] ���̃o�E���f�B���O�{�b�N�X�ő�_
	@param Matrix	[in] ���ʏ�̔C�ӂ̓_
*/
//-----------------------------------------------------------------------------------
void Selene::Collision::CreateBoxProjection( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix )
{
	CVector3D LocalBB[] = {
		CVector3D( MinPt.x, MinPt.y, MinPt.z ), // xyz
		CVector3D( MinPt.x, MaxPt.y, MinPt.z ), // xYz
		CVector3D( MinPt.x, MaxPt.y, MaxPt.z ), // xYZ
		CVector3D( MinPt.x, MinPt.y, MaxPt.z ), // xyZ
		CVector3D( MaxPt.x, MinPt.y, MinPt.z ), // Xyz
		CVector3D( MaxPt.x, MaxPt.y, MinPt.z ), // XYz
		CVector3D( MaxPt.x, MaxPt.y, MaxPt.z ), // XYZ
		CVector3D( MaxPt.x, MinPt.y, MaxPt.z ), // XyZ
	};

	// ���[�J�����W�n���烏�[���h���W�n�Ƀo�E���f�B���O�{�b�N�X���g�����X�t�H�[�����܂�
	for ( Uint32 i = 0; i < 8; i++ )
	{
		Out.Points[i].TransformProjection( LocalBB[i], Matrix );
	}

    // �o�E���f�B���O�{�b�N�X�̖ʂ𐶐����܂�
	Out.Update();
}

