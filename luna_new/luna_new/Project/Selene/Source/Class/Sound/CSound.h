

#ifndef ___SELENE__CSOUND___
#define ___SELENE__CSOUND___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"
#include "Interface/Sound/ISound.h"


//-----------------------------------------------------------------------------------
// CLASS
//-----------------------------------------------------------------------------------
class CAyame;


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CCore;
	/**
		@brief サウンド管理クラス
		@author 葉迩倭

		サウンドの処理を行うクラスです。<BR>
		WAV/圧縮WAVE/OGGの再生に対応しています。
	*/
	class CSound : public CBaseObject, public ISound
	{
		friend CCore;

	protected:
		CAyame	*m_pDriver;				///< ドライバー

	private:
		CSound( CCore *pCore );
		virtual ~CSound( void );

	protected:
		virtual Bool CreateFromFile( const wchar_t *pFileName, Bool IsGlobalScope );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void Play( Uint32 LoopCount = 0, Uint32 LoopInSample = 0 );
		virtual void Stop( void );
		virtual void Pause( void );
		virtual void SetVolume( Float fVolume );
		virtual void SetPan( Float fPan );
		virtual Bool IsPlay( void );
	};
}


#endif // ___SELENE__CSOUND___

