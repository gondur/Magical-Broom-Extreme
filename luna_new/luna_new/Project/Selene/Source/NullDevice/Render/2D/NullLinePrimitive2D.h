

#ifndef ___SELENE__NULLLINEPRIMITIVE2D___
#define ___SELENE__NULLLINEPRIMITIVE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/ILinePrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullLinePrimitive2D : public ILinePrimitive2D
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

		virtual Bool Push( SLineVertex2D *pLine, Uint32 Count )
		{
			return false;
		}

		virtual void Rendering( void )
		{
		}
	};
}


#endif // ___SELENE__NULLLINEPRIMITIVE2D___


