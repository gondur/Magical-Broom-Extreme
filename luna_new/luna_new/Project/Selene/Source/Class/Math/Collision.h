

#ifndef ___SELENE__COLLISION___
#define ___SELENE__COLLISION___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	Bool Point_Point( CVector2D *pPt1, CVector2D *pPt2 );
	Bool Point_Line( CVector2D *pPt, CLine2D *pLine );
	Bool Point_Rect( CVector2D *pPt, CRect2D<Float> *pRect );
	Bool Point_Circle( CVector2D *pPt, CCircle *pCir );
	Bool Point_Polygon( CVector2D *pPt, CPolygon2D *pPoly );
	Bool Rect_Rect( CRect2D<Float> *pRect1, CRect2D<Float> *pRect2 );
	Bool Rect_Circle( CRect2D<Float> *pRect, CCircle *pCir );
	Bool Rect_Line( CRect2D<Float> *pRect, CLine2D *pLine );
	Bool Rect_Polygon( CRect2D<Float> *pRect, CPolygon2D *pPoly );
	Bool Circle_Circle( CCircle *pCir1, CCircle *pCir2 );
	Bool Circle_Line( CCircle *pCir, CLine2D *pLine );
	Bool Circle_Polygon( CCircle *pCir, CPolygon2D *pPoly );
	Bool Line_Line( CLine2D *pLine1, CLine2D *pLine2 );
	Bool Line_Polygon( CLine2D *pLine, CPolygon2D *pPoly );
	Bool Polygon_Polygon( CPolygon2D *pPoly1, CPolygon2D *pPoly2 );

	Bool Point_Point_3D( CVector3D *pPt1, CVector3D *pPt2 );
	Bool Point_Sphere_3D( CVector3D *pPt, CSphere *pSph );
	Bool Point_Line_3D( CVector3D *pPt, CLine3D *pLine );
	Bool Point_Plane_3D( CVector3D *pPt, CPlane *pPlane );
	Bool Point_Box_3D( CVector3D *pPt, CBox *pBox );
	Bool Sphere_Sphere_3D( CSphere *pSph1, CSphere *pSph2 );
	Bool Sphere_Line_3D( CSphere *pSph, CLine3D *pLine );
	Bool Sphere_Plane( CSphere *pSph, CPlane *pPlane );
	Bool Sphere_Box_3D( CSphere *pSph, CBox *pBox );
	Bool Line_Plane_3D( CLine3D *pLine, CPlane *pPlane, CVector3D *pPoints, CVector3D *pPos );
	Bool Line_Box_3D( CLine3D *pLine, CBox *pBox );
	Bool Line_Triangle_3D( CLine3D* pLine, CVector3D Points[], Float *pT, Float *pU, Float *pV );
	Bool Plane_Plane_3D( CPlane *pPlane1, CPlane *pPlane2, CVector3D Points1[], CVector3D Points2[] );
	Bool Box_Box_3D( CBox &Box1, CBox &Box2 );

	// コリジョンデータ作成関数
	void CreateBox( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix );
	void CreateBoxProjection( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix );

	Bool EdgeIntersectsQuad( CVector3D* pEdges, CVector3D* pFacePoints, CPlane* pPlane, CVector3D *pHitPos );

	Bool LineIntersectPolygon( CVector3D *pPtTbl[], CPlane &Plane, CVector3D *pPlanePoints[], Uint32 Count );
	Bool LineIntersectPlane( CVector3D &vIntersection, CPlane &Plane, CVector3D &Pt0, CVector3D &Pt1 );
}
}


#endif // ___SELENE__COLLISION___

