

#ifndef ___SELENE_CSPRITE2D___
#define ___SELENE_CSPRITE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Render/2D/CPrimitive2D.h"
#include "Interface/Render/2D/ISprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CTexture;

	class CSprite2D : public CPrimitive2D, public ISprite2D
	{
	protected:
		CTexture *m_pTexture;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CSprite2D( CRender *pRender, CBaseMgr *pMgr, CTexture *pTex );
		virtual ~CSprite2D();

		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count );
		virtual void Begin( void );
		virtual void End( void );
		virtual void Rendering( void );

		virtual void DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color );
		virtual void DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle );
		virtual void DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src );
		virtual void CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha );
		virtual void CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha );
	};
}


#endif // ___SELENE_CSPRITE2D___

