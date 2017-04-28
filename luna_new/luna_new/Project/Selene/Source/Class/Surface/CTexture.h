

#ifndef ___SELENE__CTEXTURE___
#define ___SELENE__CTEXTURE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Core/CDevice.h"
#include "Object/CBaseMgr.h"
#include "Surface/CBaseSurface.h"
#include "Interface/Surface/ITexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CTextureMgr;

	/**
		@brief テクスチャクラス
		@author 葉迩倭
	*/
	class CTexture : public CBaseSurface, public ITexture
	{
		friend CTextureMgr;

	protected:
		IDirect3DTexture9	*m_pTexture;					///< テクスチャ
		IDirect3DTexture9	*m_pBaseTexture;				///< 復帰用バックアップテクスチャ
		D3DPOOL				m_Pool;							///< テクスチャPOOL

	protected:
		CTexture( CBaseMgr *pMgr );
		virtual ~CTexture();

		virtual Bool LoadImageFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor );
		virtual Bool LoadImageFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor );
		virtual Bool CreateTextureFromImageInfo( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor );
		virtual Bool ConvertNormalMap( Float fHeight );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool LockRect( RECT *pRect, void **ppBites, Uint32 *pPitch, Uint32 *pWidth, Uint32 *pHeight, D3DFORMAT *pFormat );
		virtual void UnLockRect( void );
		virtual Bool Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel = false );

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );
		virtual Bool SetRenderTarget( void );
		virtual Bool SetDepthStencil( void );

		virtual Bool DownloadRenderTarget( void );

		virtual void UpdateTexture( void );
		virtual Bool GetSurface( IDirect3DSurface9 **ppSurface );
		virtual Bool GetBaseSurface( IDirect3DSurface9 **ppSurface );
		virtual Bool GetTexture( IDirect3DTexture9 **ppTexture );
		virtual Bool GetBaseTexture( IDirect3DTexture9 **ppTexture );

		virtual Float PixelToTexelU( Float fParam );
		virtual Float PixelToTexelV( Float fParam );

		virtual Bool SaveToTGA( const wchar_t *pFileName );

		virtual Bool Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual Bool CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual Bool CreateFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor );
		virtual Bool CreateFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor );
		virtual Bool CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight );
		virtual Bool CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight );

		virtual CPoint2D<Uint32> GetSize( void );
	};
}

#endif // ___SELENE__CTEXTURE___


