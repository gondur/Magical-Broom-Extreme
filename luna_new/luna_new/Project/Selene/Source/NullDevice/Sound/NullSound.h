

#ifndef ___SELENE__NULLSOUND___
#define ___SELENE__NULLSOUND___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Sound/ISound.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullSound : public ISound
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

		virtual void Play( Uint32 LoopCount, Uint32 LoopInSample )
		{
		}

		virtual void Stop( void )
		{
		}

		virtual void Pause( void )
		{
		}

		virtual void SetVolume( Float fVolume )
		{
		}

		virtual void SetPan( Float fPan )
		{
		}

		virtual Bool IsPlay( void )
		{
			return false;
		}
	};
}

#endif // ___SELENE__NULLSOUND___

