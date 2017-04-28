

#ifndef ___SELENE__BASESURFACE___
#define ___SELENE__BASESURFACE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Object/CDeviceObject.h"
#include "Object/CBaseMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief サーフェイス種類
		@author 葉迩倭
	*/
	enum eSurfaceType
	{
		SURFACE_TYPE_OFFSCREEN,
		SURFACE_TYPE_RENDERTARGET,
		SURFACE_TYPE_DEPTHSTENCIL,
		SURFACE_TYPE_INVALID,
	};

	/**
		@brief サーフェイス管理用基底クラス
		@author 葉迩倭
	*/
	class CBaseSurface : public CDeviceObject
	{
	protected:
		D3DXIMAGE_INFO		m_ImageInfo;				///< 画像イメージ情報
		D3DFORMAT			m_Format;					///< テクスチャフォーマット
		CPoint2D<Uint32>	m_Size;						///< テクスチャサイズ
		Bool				m_IsLock;					///< ロック中か否か
		eSurfaceType		m_SurfaceType;				///< サーフェイス種類

	protected:
		virtual HRESULT LoadImageToBaseSurface( IDirect3DSurface9 *pSurface, const void *pData, Uint32 Size, Uint32 Width, Uint32 Height, CColor KeyColor );

	public:
		CBaseSurface( CBaseMgr *pMgr );
		virtual ~CBaseSurface();

		virtual Bool GetImageInfoFromMemory( const void *pData, Uint32 Size );

		virtual Uint32 GetImageWidth( void );
		virtual Uint32 GetImageHeight( void );
		virtual CPoint2D<Uint32> GetSize( void );
		virtual D3DFORMAT GetFormat( void );

	public:
		virtual void OnLostDevice( void ) = 0;
		virtual void OnResetDevice( void ) = 0;
		virtual Bool SetRenderTarget( void ) = 0;
		virtual Bool SetDepthStencil( void ) = 0;
	};
}

#endif // ___SELENE__BASESURFACE___


