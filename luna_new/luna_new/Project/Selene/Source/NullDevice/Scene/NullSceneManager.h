

#ifndef ___SELENE__NULLSCENEMANAGER___
#define ___SELENE__NULLSCENEMANAGER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Scene/ISceneManager.h"
#include "NullDevice/Scene/NullSceneCamera.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullSceneManager : public ISceneManager
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

		virtual ISceneCamera *GetSceneCamera( void )
		{
			static NullSceneCamera Dummy;
			return &Dummy;
		}

		virtual void Reset( void )
		{
		}

		virtual void Begin( Bool IsSort )
		{
		}

		virtual void End( void )
		{
		}

		virtual void Rendering( Bool IsDrawBuffer )
		{
		}

		virtual void SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias )
		{
		}

		virtual void SetFogEnable( Bool Enable )
		{
		}

		virtual void SetFog( Float fNear, Float fFar, CColor Color )
		{
		}

		virtual void SetDepthOfFieldForcus( Float fForcusZ, Float fPower )
		{
		}

		virtual void SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth )
		{
		}

		virtual void SetDirectionLight( CVector3D &vDirect, CVector3D &vColor )
		{
		}

		virtual void AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance )
		{
		}

		virtual CPoint2D<Uint32> SetRenderTargetSize( CPoint2D<Uint32> Size )
		{
			return CPoint2D<Uint32>( 0, 0 );
		}

		virtual Uint32 GetRenderingRequestCount( void )
		{
			return 0;
		}

		virtual Uint32 GetRenderingCount( void )
		{
			return 0;
		}

		virtual Uint32 GetOcculusion( Uint32 Index )
		{
			return 0xFFFFFFFF;
		}
	};

}

#endif // ___SELENE__NULLSCENEMANAGER___


