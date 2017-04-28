

#ifndef ___SELENE__SURFACE___
#define ___SELENE__SURFACE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Object/CBaseMgr.h"
#include "Surface/CBaseSurface.h"
#include "Interface/Surface/ISurface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CSurfaceMgr;

	/**
		@brief マテリアルクラス
		@author 葉迩倭
	*/
	class CSurface : public CBaseSurface, public ISurface
	{
		friend CSurfaceMgr;

	protected:
		IDirect3DSurface9 *m_pSurface;				///< マテリアル
		eSurfaceFormat m_BaseFormat;				///< 要求フォーマット

	protected:
		CSurface( CBaseMgr *pMgr );
		virtual ~CSurface();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Bool CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual Bool CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format, CSurface *pCopyTarget );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool SetRenderTarget( void );
		virtual Bool SetDepthStencil( void );
		virtual Bool CopyToBackBuffer( void );

		virtual Bool Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect );

		virtual Bool GetSurface( IDirect3DSurface9 **ppSurface );
	};
}

#endif // ___SELENE__SURFACE___


