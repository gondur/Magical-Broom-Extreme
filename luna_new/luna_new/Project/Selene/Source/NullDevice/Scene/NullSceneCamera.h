

#ifndef ___SELENE__NULLSCENECAMERA___
#define ___SELENE__NULLSCENECAMERA___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Scene/ISceneCamera.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullSceneCamera : public ISceneCamera
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

		virtual const CMatrix &WorldToScreen( void ) const
		{
			static CMatrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const CMatrix &WorldToView( void ) const
		{
			static CMatrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const CMatrix &ScreenToWorld( void ) const
		{
			static CMatrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const CMatrix &ViewToWorld( void ) const
		{
			static CMatrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual Float GetNearClip( void ) const
		{
			return 1.0f;
		}

		virtual Float GetFarClip( void ) const
		{
			return 100.0f;
		}

		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )
		{
		}

		virtual void Reset( void )
		{
		}

		virtual void Update( void )
		{
		}

		virtual void SetTransform( CStyle &Style )
		{
		}
	};
}

#endif // ___SELENE__NULLSCENECAMERA___


