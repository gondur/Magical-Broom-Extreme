

#ifndef ___SELENE__NULLPOINTPRIMITIVE3D___
#define ___SELENE__NULLPOINTPRIMITIVE3D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/3D/IPointPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullPointPrimitive3D : public IPointPrimitive3D
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

		virtual Uint32 AddRef( void	)
		{
			return 0;
		}

		virtual Sint32 Rendering( void )
		{
			return -1;
		}

		virtual Bool Push( SVertex3DBase *pPoint, Uint32 PointCount )
		{
			return false;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void SetTransform( CStyle &Style )
		{
		}

		virtual void SetMaterialColor( CColor Color )
		{
		}
	};
}


#endif // ___SELENE__NULLPOINTPRIMITIVE3D___


