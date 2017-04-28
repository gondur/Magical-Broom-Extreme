

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Core/CCore.h"
#include "Math/Math.h"
#include "Math/Vector2D.h"
#include "Math/Vector4D.h"
#include "Surface/CTexture.h"
#include "Render/2D/CSprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSprite2D::CSprite2D( CRender *pRender, CBaseMgr *pMgr, CTexture *pTexture ) : CPrimitive2D( pRender, pMgr )
{
	SetName( L"2Dスプライト" );

	m_pTexture = pTexture;
	if ( pTexture != NULL )
	{
		pTexture->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSprite2D::~CSprite2D()
{
	SAFE_RELEASE( m_pTexture )
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::Rendering( void )
{
	// テクスチャをデバイスに設定
	GetRenderPointer()->SetTexture( 0, m_pTexture );

	// プリミティブレンダリング
	CPrimitive2D::Rendering();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSprite2D::Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )
{
	return CPrimitive2D::Push( pPrimitive, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::Begin( void )
{
	CPrimitive2D::Begin();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::End( void )
{
	CPrimitive2D::End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color )
{
	Float fOffsetX = SrcRect.w == DstRect.w ? 0.0f : GetRenderPointer()->GetTextureOffset( 0 );
	Float fOffsetY = SrcRect.h == DstRect.h ? 0.0f : GetRenderPointer()->GetTextureOffset( 0 );

	Float x1 = toF(DstRect.x);
	Float y1 = toF(DstRect.y);
	Float x2 = toF(DstRect.x + DstRect.w);
	Float y2 = toF(DstRect.y + DstRect.h);

	Float u1 = 0.0f;
	Float v1 = 0.0f;
	Float u2 = 0.0f;
	Float v2 = 0.0f;

	// ＵＶ変換
	if ( m_pTexture != NULL )
	{
		u1 = m_pTexture->PixelToTexelU( toF(SrcRect.x            ) + fOffsetX );
		v1 = m_pTexture->PixelToTexelV( toF(SrcRect.y            ) + fOffsetY );
		u2 = m_pTexture->PixelToTexelU( toF(SrcRect.x + SrcRect.w) - fOffsetX );
		v2 = m_pTexture->PixelToTexelV( toF(SrcRect.y + SrcRect.h) - fOffsetY );
	}

	SPrimitiveVertex2D Primitive[] = {
		{
			{ CVector4D( x1, y1, 0.0f, 1.0f ), Color, CVector2D( u1, v1 ) },
			{ CVector4D( x2, y1, 0.0f, 1.0f ), Color, CVector2D( u2, v1 ) },
			{ CVector4D( x2, y2, 0.0f, 1.0f ), Color, CVector2D( u2, v2 ) },
		},
		{
			{ CVector4D( x2, y2, 0.0f, 1.0f ), Color, CVector2D( u2, v2 ) },
			{ CVector4D( x1, y2, 0.0f, 1.0f ), Color, CVector2D( u1, v2 ) },
			{ CVector4D( x1, y1, 0.0f, 1.0f ), Color, CVector2D( u1, v1 ) },
		},
	};

	// プリミティブに追加
	Push( Primitive, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle )
{
	Float fOffset = GetRenderPointer()->GetTextureOffset( 0 );

	Float x1 = toF(DstRect.x);
	Float y1 = toF(DstRect.y);
	Float x2 = toF(DstRect.x + DstRect.w);
	Float y2 = toF(DstRect.y + DstRect.h);

	Float u1 = 0.0f;
	Float v1 = 0.0f;
	Float u2 = 0.0f;
	Float v2 = 0.0f;

	CPoint2D<Float> Center( (x1 + x2) * 0.5f, (y1 + y2) * 0.5f );

	// 回転
	CPoint2D<Float> Pt[4] = {
		CPoint2D<Float>( x1, y1 ), CPoint2D<Float>( x2, y1 ),
		CPoint2D<Float>( x1, y2 ), CPoint2D<Float>( x2, y2 ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i] -= Center;
		Pt[i] = Pt[i].Rotate( Angle );
		Pt[i] += Center;
	}

	// ＵＶ変換
	if ( m_pTexture != NULL )
	{
		u1 = m_pTexture->PixelToTexelU( toF(SrcRect.x            ) + fOffset );
		v1 = m_pTexture->PixelToTexelV( toF(SrcRect.y            ) + fOffset );
		u2 = m_pTexture->PixelToTexelU( toF(SrcRect.x + SrcRect.w) - fOffset );
		v2 = m_pTexture->PixelToTexelV( toF(SrcRect.y + SrcRect.h) - fOffset );
	}

	SPrimitiveVertex2D Primitive[] = {
		{
			{ CVector4D( Pt[0].x, Pt[0].y, 0.0f, 1.0f ), Color, CVector2D( u1, v1 ) },
			{ CVector4D( Pt[1].x, Pt[1].y, 0.0f, 1.0f ), Color, CVector2D( u2, v1 ) },
			{ CVector4D( Pt[3].x, Pt[3].y, 0.0f, 1.0f ), Color, CVector2D( u2, v2 ) },
		},
		{
			{ CVector4D( Pt[3].x, Pt[3].y, 0.0f, 1.0f ), Color, CVector2D( u2, v2 ) },
			{ CVector4D( Pt[2].x, Pt[2].y, 0.0f, 1.0f ), Color, CVector2D( u1, v2 ) },
			{ CVector4D( Pt[0].x, Pt[0].y, 0.0f, 1.0f ), Color, CVector2D( u1, v1 ) },
		},
	};

	// プリミティブに追加
	Push( Primitive, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src )
{
	Float fOffset = GetRenderPointer()->GetTextureOffset( 0 );

	Float u1 = 0.0f;
	Float v1 = 0.0f;
	Float u2 = 0.0f;
	Float v2 = 0.0f;

	// ＵＶ変換
	if ( m_pTexture != NULL )
	{
		u1 = m_pTexture->PixelToTexelU( toF(Src.x         ) + fOffset );
		v1 = m_pTexture->PixelToTexelV( toF(Src.y         ) + fOffset );
		u2 = m_pTexture->PixelToTexelU( toF(Src.x +  Src.w) - fOffset );
		v2 = m_pTexture->PixelToTexelV( toF(Src.y +  Src.h) - fOffset );
	}

	// 頂点データ生成
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		CPoint2D<Float> Pt1 = CPoint2D<Float>( 0, Width[i+0] );
		CPoint2D<Float> Pt2 = CPoint2D<Float>( 0, Width[i+1] );

		Pt1 = Pt1.Rotate( Angle[i+0] );
		Pt2 = Pt2.Rotate( Angle[i+1] );

		Float x[] = {
			Pos[i+0].x - Pt1.x,
			Pos[i+0].x + Pt1.x,
			Pos[i+1].x - Pt2.x,
			Pos[i+1].x + Pt2.x,
		};

		Float y[] = {
			Pos[i+0].y - Pt1.y,
			Pos[i+0].y + Pt1.y,
			Pos[i+1].y - Pt2.y,
			Pos[i+1].y + Pt2.y,
		};

		Float u[] = {
			u1,
			u2
		};
		Float v[] = {
			v1 + ((v2 - v1) * toF(i+0) / toF(Count - 1)),
			v1 + ((v2 - v1) * toF(i+1) / toF(Count - 1))
		};

		SPrimitiveVertex2D Primitive[] = {
			{
				{ CVector4D( x[0], y[0], 0.0f, 1.0f ), Color[i+0], CVector2D( u[0], v[0] ) },
				{ CVector4D( x[1], y[1], 0.0f, 1.0f ), Color[i+0], CVector2D( u[1], v[0] ) },
				{ CVector4D( x[2], y[2], 0.0f, 1.0f ), Color[i+1], CVector2D( u[0], v[1] ) },
			},
			{
				{ CVector4D( x[2], y[2], 0.0f, 1.0f ), Color[i+1], CVector2D( u[0], v[1] ) },
				{ CVector4D( x[3], y[3], 0.0f, 1.0f ), Color[i+1], CVector2D( u[1], v[1] ) },
				{ CVector4D( x[1], y[1], 0.0f, 1.0f ), Color[i+0], CVector2D( u[1], v[0] ) },
			}
		};

		// プリミティブに追加
		Push( Primitive, 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
{
	Float fOffset = GetRenderPointer()->GetTextureOffset( 0 );

	Float fRange;
	Float u0 = 0.0f, v0 = 0.0f, u1 = 0.0f, v1 = 0.0f;
	Uint32 w, h, cx, cy;

	// 画面サイズ取得
	GetCorePointer()->GetScreenData( &w, &h, NULL );
	cx = w / 2;
	cy = h / 2;

	Float fW = 1.0f / toF(w);
	Float fH = 1.0f / toF(h);

	fRange = sqrtf( toF((cx * cx) + (cy * cy)) ) * 1.1f;

	// テクスチャ情報
	if ( m_pTexture != NULL )
	{
		u0 = m_pTexture->PixelToTexelU( toF(SrcRect.x            ) + fOffset );
		v0 = m_pTexture->PixelToTexelV( toF(SrcRect.y            ) + fOffset );
		u1 = m_pTexture->PixelToTexelU( toF(SrcRect.x + SrcRect.w) - fOffset );
		v1 = m_pTexture->PixelToTexelV( toF(SrcRect.y + SrcRect.h) - fOffset );
	}

	// 円状に展開
	for ( Sint32 i = 0; i < Side; i++ )
	{
		Sint32 alpha0 = 255 - (255 * (i + 0) / Side) + Alpha;
		Sint32 alpha1 = 255 - (255 * (i + 1) / Side) + Alpha;
		Float fIn  = toF(i + 0) * fRange / toF(Side);
		Float fOut = toF(i + 1) * fRange / toF(Side);

		if ( alpha0 <   0 ) alpha0 =   0;
		if ( alpha0 > 255 ) alpha0 = 255;

		if ( alpha1 <   0 ) alpha1 =   0;
		if ( alpha1 > 255 ) alpha1 = 255;

		for ( Sint32 j = 0; j < Divide; j++ )
		{
			Sint32 angle0 = (j + 0) * ANGLE_MAX / Divide;
			Sint32 angle1 = (j + 1) * ANGLE_MAX / Divide;

			Float x0 = cx + Math::Cos( angle0 ) * fOut;
			Float y0 = cy + Math::Sin( angle0 ) * fOut;
			Float x1 = cx + Math::Cos( angle1 ) * fOut;
			Float y1 = cy + Math::Sin( angle1 ) * fOut;
			Float x2 = cx + Math::Cos( angle1 ) * fIn;
			Float y2 = cy + Math::Sin( angle1 ) * fIn;
			Float x3 = cx + Math::Cos( angle0 ) * fIn;
			Float y3 = cy + Math::Sin( angle0 ) * fIn;

			CColor Col0( 255, 255, 255, (Uint8)alpha0 );
			CColor Col1( 255, 255, 255, (Uint8)alpha1 );

			SPrimitiveVertex2D Vtx[] = {
				{
					{ CVector4D(x0, y0, 0.0f, 1.0f), Col1, CVector2D(u0 + (u1 * x0 * fW), v0 + (v1 * y0 * fH)) },
					{ CVector4D(x1, y1, 0.0f, 1.0f), Col1, CVector2D(u0 + (u1 * x1 * fW), v0 + (v1 * y1 * fH)) },
					{ CVector4D(x2, y2, 0.0f, 1.0f), Col0, CVector2D(u0 + (u1 * x2 * fW), v0 + (v1 * y2 * fH)) },
				},
				{
					{ CVector4D(x2, y2, 0.0f, 1.0f), Col0, CVector2D(u0 + (u1 * x2 * fW), v0 + (v1 * y2 * fH)) },
					{ CVector4D(x3, y3, 0.0f, 1.0f), Col0, CVector2D(u0 + (u1 * x3 * fW), v0 + (v1 * y3 * fH)) },
					{ CVector4D(x0, y0, 0.0f, 1.0f), Col1, CVector2D(u0 + (u1 * x0 * fW), v0 + (v1 * y0 * fH)) },
				},
			};

			// プリミティブに追加
			Push( Vtx, 2 );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
{
	Float fOffset = GetRenderPointer()->GetTextureOffset( 0 );

	Float fRange;
	Float u0 = 0.0f, v0 = 0.0f, u1 = 0.0f, v1 = 0.0f;
	Uint32 w, h, cx, cy;

	// 画面サイズ取得
	GetCorePointer()->GetScreenData( &w, &h, NULL );
	cx = w / 2;
	cy = h / 2;

	Float fW = 1.0f / toF(w);
	Float fH = 1.0f / toF(h);

	fRange = sqrtf( toF((cx * cx) + (cy * cy)) ) * 1.1f;

	// テクスチャ情報
	if ( m_pTexture != NULL )
	{
		u0 = m_pTexture->PixelToTexelU( toF(SrcRect.x            ) + fOffset );
		v0 = m_pTexture->PixelToTexelV( toF(SrcRect.y            ) + fOffset );
		u1 = m_pTexture->PixelToTexelU( toF(SrcRect.x + SrcRect.w) - fOffset );
		v1 = m_pTexture->PixelToTexelV( toF(SrcRect.y + SrcRect.h) - fOffset );
	}

	// 円状に展開
	for ( Sint32 i = 0; i < Side; i++ )
	{
		Float fIn  = toF(i + 0) * fRange / toF(Side);
		Float fOut = toF(i + 1) * fRange / toF(Side);

		for ( Sint32 j = 0; j < Divide; j++ )
		{
			Sint32 alpha0 = 255 - (255 * (j + 0) / Divide) + Alpha;
			Sint32 alpha1 = 255 - (255 * (j + 1) / Divide) + Alpha;

			if ( alpha0 <   0 ) alpha0 =   0;
			if ( alpha0 > 255 ) alpha0 = 255;

			if ( alpha1 <   0 ) alpha1 =   0;
			if ( alpha1 > 255 ) alpha1 = 255;

			Sint32 angle0 = ((j + 0) * ANGLE_MAX / Divide) - (ANGLE_MAX / 4);
			Sint32 angle1 = ((j + 1) * ANGLE_MAX / Divide) - (ANGLE_MAX / 4);

			Float x0 = cx + Math::Cos( angle0 ) * fOut;
			Float y0 = cy + Math::Sin( angle0 ) * fOut;
			Float x1 = cx + Math::Cos( angle1 ) * fOut;
			Float y1 = cy + Math::Sin( angle1 ) * fOut;
			Float x2 = cx + Math::Cos( angle1 ) * fIn;
			Float y2 = cy + Math::Sin( angle1 ) * fIn;
			Float x3 = cx + Math::Cos( angle0 ) * fIn;
			Float y3 = cy + Math::Sin( angle0 ) * fIn;

			CColor Col0( 255, 255, 255, (Uint8)alpha0 );
			CColor Col1( 255, 255, 255, (Uint8)alpha1 );

			SPrimitiveVertex2D Vtx[] = {
				{
					{ CVector4D(x0, y0, 0.0f, 1.0f), Col0, CVector2D(u0 + (u1 * x0 * fW), v0 + (v1 * y0 * fH)) },
					{ CVector4D(x1, y1, 0.0f, 1.0f), Col1, CVector2D(u0 + (u1 * x1 * fW), v0 + (v1 * y1 * fH)) },
					{ CVector4D(x2, y2, 0.0f, 1.0f), Col1, CVector2D(u0 + (u1 * x2 * fW), v0 + (v1 * y2 * fH)) },
				},
				{
					{ CVector4D(x2, y2, 0.0f, 1.0f), Col1, CVector2D(u0 + (u1 * x2 * fW), v0 + (v1 * y2 * fH)) },
					{ CVector4D(x3, y3, 0.0f, 1.0f), Col0, CVector2D(u0 + (u1 * x3 * fW), v0 + (v1 * y3 * fH)) },
					{ CVector4D(x0, y0, 0.0f, 1.0f), Col0, CVector2D(u0 + (u1 * x0 * fW), v0 + (v1 * y0 * fH)) },
				},
			};

			// プリミティブに追加
			Push( Vtx, 2 );
		}
	}
}

