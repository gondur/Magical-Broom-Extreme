

#ifndef ___SELENE__NULLTEXTURE___
#define ___SELENE__NULLTEXTURE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Surface/ITexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullTexture : public ITexture
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

		virtual Bool Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel )
		{
			return false;
		}

		virtual Bool DownloadRenderTarget( void )
		{
			return false;
		}

		virtual void UpdateTexture( void )
		{
		}

		virtual Bool SaveToTGA( const wchar_t *pFileName )
		{
			return NULL;
		}

		virtual CPoint2D<Uint32> GetSize( void )
		{
			return CPoint2D<Uint32>( 1, 1 );
		}
	};
}

#endif // ___SELENE__NULLTEXTURE___


