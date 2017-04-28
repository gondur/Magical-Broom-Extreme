

#ifndef ___SELENE__NULLFONTSPRITE2D___
#define ___SELENE__NULLFONTSPRITE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/IFontSprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullFontSprite2D : public IFontSprite2D
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Uint32 Release( void )
		{
			return 0;
		}

		virtual Uint32 AddRef( void )
		{
			return 0;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void Rendering( void )
		{
		}

		virtual void DrawString( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )
		{
		}

		virtual void DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )
		{
		}

		virtual Sint32 DrawChara( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color )
		{
			return 0;
		}

		virtual Sint32 DrawCharaRotate( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color, Sint32 Angle )
		{
			return 0;
		}

		virtual CPoint2D<Sint32> GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos )
		{
			return CPoint2D<Sint32>( 0, 0 );
		}

		virtual CPoint2D<Sint32> GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos )
		{
			return CPoint2D<Sint32>( 0, 0 );
		}
	};
}

#endif // ___SELENE__NULLFONTSPRITE2D___

