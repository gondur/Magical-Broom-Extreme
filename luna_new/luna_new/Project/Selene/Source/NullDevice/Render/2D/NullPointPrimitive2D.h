

#ifndef ___SELENE__NULLPOINTPRIMITIVE2D___
#define ___SELENE__NULLPOINTPRIMITIVE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/IPointPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullPointPrimitive2D : public IPointPrimitive2D
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

		virtual Bool Push( SVertex2D *pPoint, Uint32 Count )
		{
			return false;
		}

		virtual void Rendering( void )
		{
		}
	};
}


#endif // ___SELENE__NULLPOINTPRIMITIVE2D___


