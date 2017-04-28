

#ifndef ___SELENE__NULLSURFACE___
#define ___SELENE__NULLSURFACE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullSurface : public ISurface
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

		virtual Bool CopyToBackBuffer( void )
		{
			return false;
		}

		virtual Bool Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )
		{
			return false;
		}
	};
}

#endif // ___SELENE__NULLSURFACE___


