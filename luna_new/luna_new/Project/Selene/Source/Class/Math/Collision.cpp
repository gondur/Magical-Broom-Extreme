

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
	@brief 直線定義

	Collisionクラス内部で使用されている
	直線定義構造体です。
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
	@brief 点(x,y)が直線分 l のどちら側にあるか調べる

	@param x		[in] 評価する点のＸ座標
	@param y		[in] 評価する点のＹ座標
	@param pLine	[in] 評価する線分

	@retval > 0		直線分 l の右側にある
	@retval ==0		直線分 l の直線上にある
	@retval < 0		直線分 l の左側にある

*/
//-----------------------------------------------------------------------------------
static inline Float Side( Float x, Float y, CLine2D *pLine )
{
	return ((x - pLine->Pt0.x) * (y - pLine->Pt1.y) - (y - pLine->Pt0.y) * (x - pLine->Pt1.x));
}

//-----------------------------------------------------------------------------------
/**
	@brief 直線のベクトル方程式

	@param pDst		[out] ベクトル方程式格納先
	@param pSrc		[in] 元になる直線
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
	点と直線の当り判定を行います

	@param pPt1		[in] 評価する２Ｄ平面上の点
	@param pPt2		[in] 評価する２Ｄ平面上の点

	@retval true	衝突している
	@retval false	衝突していない
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
	点と直線の当り判定を行います

	@param pPt		[in] 評価する２Ｄ平面上の点
	@param pLine	[in] 評価する２Ｄ平面状の線分

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Line( CVector2D *pPt, CLine2D *pLine )
{
	CCircle Cir( pPt->x, pPt->y, 0.1f );

	return Circle_Line( &Cir, pLine );
}

//-----------------------------------------------------------------------------------
/**
	点と四角の当り判定を行います

	@param pPt		[in] 評価する２Ｄ平面上の点
	@param pRect	[in] 評価する２Ｄ平面上の矩形

	@retval true	衝突している
	@retval false	衝突していない
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
	点と円の当り判定を行います

	@param pPt		[in] 評価する２Ｄ平面上の点
	@param pCir		[in] 評価する２Ｄ平面状の円

	@retval true	衝突している
	@retval false	衝突していない
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
	点と多角形の当り判定を行います

	@param pPt		[in] 評価する２Ｄ平面上の点
	@param pPoly	[in] 評価する２Ｄ平面状のポリゴン

	@retval true	衝突している
	@retval false	衝突していない
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
	四角と四角の当り判定を行います

	@param pRect1	[in] 評価する２Ｄ平面上の矩形
	@param pRect2	[in] 評価する２Ｄ平面上の矩形

	@retval true	衝突している
	@retval false	衝突していない
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
	四角と円の当り判定を行います

	@param pRect	[in] 評価する２Ｄ平面上の矩形
	@param pCir		[in] 評価する２Ｄ平面状の円

	@retval true	衝突している
	@retval false	衝突していない
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
	四角と直線の当り判定を行います

	@param pRect	[in] 評価する２Ｄ平面上の矩形
	@param pLine	[in] 評価する２Ｄ平面状の線分

	@retval true	衝突している
	@retval false	衝突していない
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
	四角と多角形の当り判定を行います

	@param pRect	[in] 評価する２Ｄ平面上の矩形
	@param pPoly	[in] 評価する２Ｄ平面状のポリゴン

	@retval true	衝突している
	@retval false	衝突していない
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
	円と円の当り判定を行います

	@param pCir1	[in] 評価する２Ｄ平面状の円
	@param pCir2	[in] 評価する２Ｄ平面状の円

	@retval true	衝突している
	@retval false	衝突していない
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
	円と直線の当り判定を行います

	@param pCir		[in] 評価する２Ｄ平面状の円
	@param pLine	[in] 評価する２Ｄ平面状の線分

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Line( CCircle *pCir, CLine2D *pLine )
{
	//====================================================
	// まずは直線分の両端が円に含まれればＯＫ
	//====================================================
	if ( Point_Circle( &pLine->Pt0, pCir ) ) return true;
	if ( Point_Circle( &pLine->Pt1, pCir ) ) return true;

	//====================================================
	// 円の中点と直直線までの距離を求める.
	//====================================================

	// 点から直直線に垂直な単位ベクトル(t1)を求める。
	static CVector2D s1, s2, s3, t1, t2, v;
	static Float z;

	// ベクトル la - lb
	s1.x = pLine->Pt1.x - pLine->Pt0.x;
	s1.y = pLine->Pt1.y - pLine->Pt0.y;

	// ベクトル la - cir
	s2.x = pCir->Center.x - pLine->Pt0.x;
	s2.y = pCir->Center.y - pLine->Pt0.y;

	// ベクトル s1 と s2 の外積
	// ２次元空間なのでＺ軸に平行なベクトル
	z = s1.Cross( s2 );

	// 円の中心が直線上に存在するとき（外積が０になる
	if ( z == 0 )
	{
		v.x = pCir->Center.x;
		v.y = pCir->Center.y;
	}
	else
	{
		// ベクトル s1 と s3 の外積
		// このベクトルが la - lb の垂直線になる
		s3.x = +(s1.y * z);
		s3.y = -(s1.x * z);

		// 垂直線ベクトルの正規化
		t1.Normalize( s3 );

		// 内積から距離を算出
		t2.x = pLine->Pt0.x - pCir->Center.x;
		t2.y = pLine->Pt0.y - pCir->Center.y;
		Float len = t1.Dot( t2 );

		// 交点と円の中心の距離が半径以上ならＮＧ
		if ( len > pCir->Radius ) return false;

		// 円の中心から la - lb に引いた垂直線の足の座標を求める
		v.x = pCir->Center.x + (t1.x * len);
		v.y = pCir->Center.y + (t1.y * len);
	}

	// v が pLine->Pt0 - pLine->Pt1 の間にあればＯＫ
	if ( (pLine->Pt0.x < v.x) && (v.x < pLine->Pt1.x) ) return true;
	if ( (pLine->Pt1.x < v.x) && (v.x < pLine->Pt0.x) ) return true;
	if ( (pLine->Pt0.y < v.y) && (v.y < pLine->Pt1.y) ) return true;
	if ( (pLine->Pt1.y < v.y) && (v.y < pLine->Pt0.y) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
	円と多角形の当り判定を行います

	@param pCir		[in] 評価する２Ｄ平面状の円
	@param pPoly	[in] 評価する２Ｄ平面状のポリゴン

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Polygon( CCircle *pCir, CPolygon2D *pPoly )
{
	Sint32 cnt = pPoly->Count - 1;

	// 円の中心が多角形に含まれているならＯＫ
	if ( Point_Polygon( &pCir->Center, pPoly ) ) return true;

	// 多角形の各辺と円の交差判定
	for ( Sint32 i = 0; i < cnt; i++ )
	{
		CLine2D Line( pPoly->pPts[i+0].x, pPoly->pPts[i+0].y, pPoly->pPts[i+1].x, pPoly->pPts[i+1].y );

		if ( Circle_Line( pCir, &Line ) ) return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	直線と直線の当り判定を行います

	@param pLine1	[in] 評価する２Ｄ平面状の線分
	@param pLine2	[in] 評価する２Ｄ平面状の線分

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Line( CLine2D *pLine1, CLine2D *pLine2 )
{
	Float ret1, ret2;
	Float n1, n2;

	//-------------------------------------------
	// 先にバウンディングで判定
	//-------------------------------------------
	CRect2D<Float> Rc1( pLine1->Pt0.x, pLine1->Pt0.y, pLine1->Pt1.x, pLine1->Pt1.y );
	CRect2D<Float> Rc2( pLine2->Pt0.x, pLine2->Pt0.y, pLine2->Pt1.x, pLine2->Pt1.y );
	if ( !Rect_Rect( &Rc1, &Rc2 ) ) return false;

	//-------------------------------------------
	// l1 が l2 をまたいでいるか否か
	//-------------------------------------------
	n1 = Side( pLine2->Pt0.x, pLine2->Pt0.y, pLine1 );
	n2 = Side( pLine2->Pt1.x, pLine2->Pt1.y, pLine1 );
	ret1 = (n1 * n2);

	//-------------------------------------------
	// l2 が l1 をまたいでいるか否か
	//-------------------------------------------
	n1 = Side( pLine1->Pt0.x, pLine1->Pt0.y, pLine2 );
	n2 = Side( pLine1->Pt1.x, pLine1->Pt1.y, pLine2 );
	ret2 = (n1 * n2);

	return ((ret1 <= 0.0f) && (ret2 <= 0.0f));
}

//-----------------------------------------------------------------------------------
/**
	直線と多角形の当り判定を行います

	@param pLine	[in] 評価する２Ｄ平面状の線分
	@param pPoly	[in] 評価する２Ｄ平面状のポリゴン

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Polygon( CLine2D *pLine, CPolygon2D *pPoly )
{
	Sint32 cnt = pPoly->Count;

	// 直線分の各端が多角形に含まれているかチェック
	if ( Point_Polygon( &pLine->Pt0, pPoly ) ) return true;
	if ( Point_Polygon( &pLine->Pt1, pPoly ) ) return true;

	// 多角形の各辺と直線分の交差判定
	for ( Sint32 i = 0; i < cnt - 1; i++ )
	{
		CLine2D Line( pPoly->pPts[i+0].x, pPoly->pPts[i+0].y, pPoly->pPts[i+1].x, pPoly->pPts[i+1].y );

		if ( Line_Line( &Line, pLine ) ) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------
/**
	多角形と多角形の当り判定を行います

	@param pPoly1	[in] 評価する２Ｄ平面状のポリゴン
	@param pPoly2	[in] 評価する２Ｄ平面状のポリゴン

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Polygon_Polygon( CPolygon2D *pPoly1, CPolygon2D *pPoly2 )
{
	Sint32 cnt1 = pPoly1->Count-1;
	Sint32 cnt2 = pPoly2->Count-1;

	//==========================================================
	// バウンディングボックス算出
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
	// バウンディングボックスの接触判定
	//----------------------------------------------------------
	if ( x11 > x22 ) return false;
	if ( x12 < x21 ) return false;
	if ( y11 > y22 ) return false;
	if ( y12 < y21 ) return false;

	//==========================================================
	// 外積で判定
	//==========================================================

	//----------------------------------------------------------
	// p1の各頂点がp2の矩形内に入っているか
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < cnt1; i++ )
	{
		if ( Point_Polygon( &pPoly1->pPts[i], pPoly2 ) )
		{
			return true;
		}
	}

	//----------------------------------------------------------
	// p2の各頂点がp1の矩形内に入っているか
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < cnt2; i++ )
	{
		if ( Point_Polygon( &pPoly2->pPts[i], pPoly1 ) )
		{
			return true;
		}
	}

	//==========================================================
	// 各頂点が作る線分の交差判定
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
	点と点の当り判定を行います

	@param pPt1	[in] 評価する３Ｄ空間内の点
	@param pPt2	[in] 評価する３Ｄ空間内の点

	@retval true	衝突している
	@retval false	衝突していない
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
	点と球の当り判定を行います

	@param pPt		[in] 評価する３Ｄ空間内の点
	@param pSph		[in] 評価する３Ｄ空間内の球

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Sphere_3D( CVector3D *pPt, CSphere *pSph )
{
	CSphere Cir( *pPt, 0.0f );

	return Sphere_Sphere_3D( pSph, &Cir );
}

//-----------------------------------------------------------------------------------
/**
	点と直線の当り判定を行います

	@param pPt		[in] 評価する３Ｄ空間内の点
	@param pLine	[in] 評価する３Ｄ空間内の線分

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Line_3D( CVector3D *pPt, CLine3D *pLine )
{
	CSphere Cir( *pPt, 1.0f );

	return Sphere_Line_3D( &Cir, pLine );
}

//-----------------------------------------------------------------------------------
/**
	点と面の当り判定を行います

	@param pPt		[in] 評価する３Ｄ空間内の点
	@param pPlane	[in] 評価する３Ｄ空間内の平面

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Plane_3D( CVector3D *pPt, CPlane *pPlane )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
	点と箱の当り判定を行います

	@param pPt	[in] 評価する３Ｄ空間内の点
	@param pBox	[in] 評価する３Ｄ空間内の箱

	@retval true	衝突している
	@retval false	衝突していない
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

	// ポイントが6つの平面すべての内部である場合ボックス内にあります
	return (bOutside == 0);
}

//-----------------------------------------------------------------------------------
/**
	球と球の当り判定を行います

	@param pSph1	[in] 評価する３Ｄ空間内の球
	@param pSph2	[in] 評価する３Ｄ空間内の球

	@retval true	衝突している
	@retval false	衝突していない
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
	球と直線の当り判定を行います

	@param pSph		[in] 評価する３Ｄ空間内の球
	@param pLine	[in] 評価する３Ｄ空間内の線分

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Line_3D( CSphere *pSph, CLine3D *pLine )
{
	//====================================================
	// まずは直線分の両端が球に含まれているかチェック
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
	// 球の中点と直線までの距離を求める.
	//====================================================

	// 点から直線に垂直な単位ベクトル(t1)を求める。
	static CVector3D s1, s2, s3, s4, t1, t2, v;

	// ベクトル la - lb
	s1.x = pLine->Pt1.x - pLine->Pt0.x;
	s1.y = pLine->Pt1.y - pLine->Pt0.y;
	s1.z = pLine->Pt1.z - pLine->Pt0.z;

	// ベクトル la - cir
	s2.x = pSph->Center.x - pLine->Pt0.x;
	s2.y = pSph->Center.y - pLine->Pt0.y;
	s2.z = pSph->Center.z - pLine->Pt0.z;

	// s1, s2 の外積 s3
	s3.Cross( s1, s2 );

	// s1, s3 の外積 s4 = 垂直線
	s4.Cross( s1, s3 );

	// 正規化
	t1.Normalize( s4 );

	// 内積から距離を算出
	t2.x = pLine->Pt0.x - pSph->Center.x;
	t2.y = pLine->Pt0.y - pSph->Center.y;
	t2.z = pLine->Pt0.z - pSph->Center.z;
	Float len = t1.Dot( t2 );

	// 交点と円の中心の距離が半径以上ならＮＧ
	if ( len > r ) return false;

	// 球の中心(cir)から直線(pLine->a, pLine->b)に引いた垂直線の足の座標(v)
	v.x = pSph->Center.x + (t1.x * len);
	v.y = pSph->Center.y + (t1.y * len);
	v.z = pSph->Center.z + (t1.z * len);
	
	// vがpLine->aとpLine->bの間にあればＯＫ
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
	球と面の当り判定を行います<BR>
	この関数は未完成ですので、他の方法での判定を推奨します。

	@param pSph		[in] 評価する３Ｄ空間内の球
	@param pPlane	[in] 評価する３Ｄ空間内の平面

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Plane( CSphere *pSph, CPlane *pPlane )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
	球と箱の当り判定を行います<BR>
	この関数は未完成ですので、他の方法での判定を推奨します。

	@param pSph		[in] 評価する３Ｄ空間内の球
	@param pBox		[in] 評価する３Ｄ空間内の箱

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Box_3D( CSphere *pSph, CBox *pBox )
{
	// 球の中心が箱の中に入っていればＯＫ
	if ( Point_Box_3D( &pSph->Center, pBox ) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
	線分と面の当り判定を行います

	@param pLine	[in] 評価する３Ｄ空間内の線分
	@param pPlane	[in] 評価する３Ｄ空間内の平面
	@param pPoints	[in] pPlane上の任意の３点
	@param pPos		[out] 衝突座標格納先


	@retval true	衝突している
	@retval false	衝突していない
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

	// 線分の両端がが平面をまたいで存在しているかをチェック
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

	// Vx[0]を共有する２ベクトルを算出
	CVector3D Edge1 = Vx[1] - Vx[0];
	CVector3D Edge2 = Vx[2] - Vx[0];

	// Uパラメーターを計算
	VecP.Cross( Dir, Edge2 );

    // 内積が０に近い場合は三角形の平面にある
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

	// Uパラメーターおよびテスト境界を計算
	ParamU = VecT.Dot( VecP );
	if ( (ParamU < 0.0f) || (ParamU > fDet) ) return false;

	// Vパラメーターをテストする準備をします
	VecQ.Cross( VecT, Edge1 );

	// Vパラメーターおよびテスト境界を計算
	ParamV = Dir.Dot( VecQ );
	if ( (ParamV < 0.0f) || ((ParamU + ParamV) > fDet) ) return false;

	// Tを計算し、スケーリング
	ParamT = Edge2.Dot( VecQ );
	fInvDet = 1.0f / fDet;
	ParamT *= fInvDet;
	ParamU *= fInvDet;
	ParamV *= fInvDet;

	// 位置情報を保存
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
	線分と箱の当り判定を行います

	@param pLine	[in] 評価する３Ｄ空間内の線分
	@param pBox		[in] 評価する３Ｄ空間内の箱

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Box_3D( CLine3D *pLine, CBox *pBox )
{
	// 箱の中に点が入っているかチェック
	if ( Point_Box_3D( &pLine->Pt0, pBox ) ) return true;
	if ( Point_Box_3D( &pLine->Pt1, pBox ) ) return true;

	// 平面と線分が交差しているかチェック
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
	線分と三角形の当り判定を行います

	@param pLine	[in] 評価する３Ｄ空間内の線分
	@param Points	[in] 評価する３Ｄ空間内の三角形を構成する点
	@param pT		[out] Tパラメーター格納先
	@param pU		[out] Uパラメーター格納先
	@param pV		[out] Vパラメーター格納先

	@retval true	衝突している
	@retval false	衝突していない
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

	// pV0を共有する２ベクトルを算出
	CVector3D Edge1 = Vx[1] - Vx[0];
	CVector3D Edge2 = Vx[2] - Vx[0];

	// Uパラメーターを計算
	VecP.Cross( Dir, Edge2 );

    // 内積が０に近い場合は三角形の平面にある
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

	// Uパラメーターおよびテスト境界を計算
	*pU = VecT.Dot( VecP );
	if ( (*pU < 0.0f) || (*pU > fDet) ) return false;

	// Vパラメーターをテストする準備をします
	VecQ.Cross( VecT, Edge1 );

	// Vパラメーターおよびテスト境界を計算
	*pV = Dir.Dot( VecQ );
	if ( (*pV < 0.0f) || ((*pU + *pV) > fDet) ) return false;

	// Tを計算し、スケーリング
	*pT = Edge2.Dot( VecQ );
	fInvDet = 1.0f / fDet;
	*pT *= fInvDet;
	*pU *= fInvDet;
	*pV *= fInvDet;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	面と面の接触判定をします

	@param pPlane1			[in] 平面１
	@param pPlane2			[in] 平面２
	@param Points1[]		[in] 平面１を構成する４点
	@param Points2[]		[in] 平面２を構成する４点

	@retval true		交差している
	@retval false		交差していない
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
	４点で構成される平面と直線の交差判定を行います

	@param pEdges		[in] 線分
	@param pFacePoints	[in] 平面の点（４点）
	@param pPlane		[in] チェックする平面
	@param pHitPos		[out] 平面との交差位置

	@retval true		交差している
	@retval false		交差座していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::EdgeIntersectsQuad( CVector3D* pEdges, CVector3D* pFacePoints, CPlane* pPlane, CVector3D *pHitPos )
{
	CVector3D Intersection;
	CVector2D FacePoints[5];
	CVector2D Point;

	// 両端のポイントが平面の同じ側にある場合、面と交差しません
	Float fDist1 = pPlane->a * pEdges[0].x + pPlane->b * pEdges[0].y + pPlane->c * pEdges[0].z + pPlane->d;
	Float fDist2 = pPlane->a * pEdges[1].x + pPlane->b * pEdges[1].y + pPlane->c * pEdges[1].z + pPlane->d;
	if ( (fDist1 * fDist2) > 0 ) return false;

	// 直線および平面の間の交点を見つけます
	//  それらが平行の場合、直線と面は交差しません
	//  そのとき ::D3DXPlaneIntersectLine() は NULL を返します
	if ( !LineIntersectPlane( Intersection, *pPlane, pEdges[0], pEdges[1] ) ) return false;
	if ( pHitPos != NULL ) *pHitPos = Intersection;

	// ポリゴン内の頂点位置をテストするため２Ｄ平面上へのプロジェクト
	Float fAbsA = (pPlane->a > 0 ? pPlane->a : -pPlane->a);
	Float fAbsB = (pPlane->b > 0 ? pPlane->b : -pPlane->b);
	Float fAbsC = (pPlane->c > 0 ? pPlane->c : -pPlane->c);
	if ( (fAbsA > fAbsB) && (fAbsA > fAbsC) )
	{
		// Ｘ軸並行なのでＹとＺを使用して計算
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
		// Ｙ軸並行なのでＸとＺを使用して計算
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
		// Ｚ軸並行なのでＸとＹを使用して計算
		for ( Sint32 i = 0; i < 4; i++)
		{
			FacePoints[i].x = pFacePoints[i].x;
			FacePoints[i].y = pFacePoints[i].y;
		}
		Point.x = Intersection.x;
		Point.y = Intersection.y;
	}

	FacePoints[4] = FacePoints[0];

	// 頂点が平面のの外部上にある場合、その頂点が平面の外部にあります
	// 次のマトリックスの決定要素をとることによりこれをすることができます
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

	// ポイントは面すべての内部にあります
	return true;
}


//-----------------------------------------------------------------------------------
/**
	箱と箱の当り判定を行います

	@param pBox1	[in] 評価する３Ｄ空間内の箱
	@param pBox2	[in] 評価する３Ｄ空間内の箱

	@retval true	衝突している
	@retval false	衝突していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Box_Box_3D( CBox &Box0, CBox &Box1 )
{
	Uint8 bOutside[8];

	//-----------------------------------------------------------------------------------======================
	// ビューフラスタムの端のエッジのどれかがバウンディングボックスの面のうちのどれかに接触するか
	// 互いの箱の中に互いの点が入っているかチェック
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

		// ポイントが６つのビューフラスタム平面すべての内部である場合
		// ビューフラスタム内にあります
		if ( bOutside[i] == 0 ) return true;
	}

	// ポイントがすべて任意の単一のビューフラスタム平面の外部にある場合
	// オブジェクトはビューフラスタム外にあります。
	if ( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0x00 )
	{
		return false;
	}

	//-----------------------------------------------------------------------------------======================
	// ビューフラスタムの端のエッジのどれかがバウンディングボックスの面のうちのどれかに接触するか
	// 互いの箱の中に互いの点が入っているかチェック
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

		// ポイントが６つのビューフラスタム平面すべての内部である場合
		// ビューフラスタム内にあります
		if ( bOutside[i] == 0 ) return true;
	}

	// ポイントがすべて任意の単一のビューフラスタム平面の外部にある場合
	// オブジェクトはビューフラスタム外にあります。
	if ( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0x00 )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	// モデルOBBエッジのどれかがカメラOBB面のうちのどれかに接触するか
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
	// カメラOBBエッジのどれかがモデルOBB面のうちのどれかに接触するか
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
	ポリゴンと線分の交点を算出します。

	@param Intersection	[out] 交点格納先
	@param Plane		[in] 平面
	@param Pt0			[in] 線分の端
	@param Pt1			[in] 線分の端

	@retval true		交差している
	@retval false		交差していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::LineIntersectPolygon( CVector3D *pPtTbl[], CPlane &Plane, CVector3D *pPlanePoints[], Uint32 Count )
{
	// 直線および平面の間の交点を見つけます
	CVector3D Intersect;
	if ( !LineIntersectPlane( Intersect, Plane, *pPtTbl[0], *pPtTbl[1] ) )
	{
		return false;
	}

	// 平面の法線
	CVector3D vNorm( Plane.a, Plane.b, Plane.c );

	// 各エッジと交点の外積を求める
	for ( Uint32 i = 0; i < Count; i++ )
	{
		CVector3D v1 = *pPlanePoints[(i + 0) % Count] - Intersect;
		CVector3D v2 = *pPlanePoints[(i + 1) % Count] - Intersect;

		// 交点を使った場合の法線
		CVector3D vOut;
		vOut.Cross( v1, v2 );

		// 方向チェック
		// 同じ方向のベクトル同士の内積は＋になる
		if ( vOut.Dot( vNorm ) < 0.0f )
		{
			return false;
		}
	}

	// ポイントはエッジの内部にある
	return true;
}

//-----------------------------------------------------------------------------------
/**
	面と直線の交点を算出します

	@param Intersection		[out] 交点格納先
	@param pPlane			[in] 平面
	@param pPt0			[in] 線分の端
	@param pPt1			[in] 線分の端

	@retval true		交差している
	@retval false		交差していない
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::LineIntersectPlane( CVector3D &vIntersection, CPlane &Plane, CVector3D &Pt0, CVector3D &Pt1 )
{
	// 両端のポイントが平面の同じ側にある場合は面と交差しません
	Float fDot0 = Plane.Dot( Pt0 );
	Float fDot1 = Plane.Dot( Pt1 );
	if ( fDot0 * fDot1 >= 0.0f )
	{
		return false;
	}

	// 方向ベクトル
	CVector3D vDir = Pt1 - Pt0;

	// 媒介変数を求める
	Float t = -fDot0 / Plane.Dot( vDir, 0.0f );
	if ( (t < 0.0f) || (t > 1.0f) )
	{
		return false;
	}

	// 媒介変数から交点を求める
	vIntersection = Pt0 + (vDir * t);

	return true;
}

//-----------------------------------------------------------------------------------
/**
	Collisionクラスで使用する箱データの作成を行います

	@param Out		[out] 箱データ格納先
	@param MinPt	[in] 箱のバウンディングボックス最小点
	@param MaxPt	[in] 箱のバウンディングボックス最大点
	@param Matrix	[in] 平面状の任意の点
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

	// ローカル座標系からワールド座標系にバウンディングボックスをトランスフォームします
	for ( Uint32 i = 0; i < 8; i++ )
	{
		Out.Points[i].TransformCoord( LocalBB[i], Matrix );
	}

    // バウンディングボックスの面を生成します
	Out.Update();
}

//-----------------------------------------------------------------------------------
/**
	Collisionクラスで使用する箱データの作成を行います<BR>
	プロジェクションも考慮してデータ作成を行うので、<BR>
	ビューフラスタムなどの生成に適しています。

	@param Out		[out] 箱データ格納先
	@param MinPt	[in] 箱のバウンディングボックス最小点
	@param MaxPt	[in] 箱のバウンディングボックス最大点
	@param Matrix	[in] 平面状の任意の点
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

	// ローカル座標系からワールド座標系にバウンディングボックスをトランスフォームします
	for ( Uint32 i = 0; i < 8; i++ )
	{
		Out.Points[i].TransformProjection( LocalBB[i], Matrix );
	}

    // バウンディングボックスの面を生成します
	Out.Update();
}

