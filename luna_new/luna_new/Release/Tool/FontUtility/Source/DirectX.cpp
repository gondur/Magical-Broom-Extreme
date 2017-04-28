

//==========================================================================
// INCLUDE
//==========================================================================
#include "Surface.h"
#include "DirectX.h"


//==========================================================================
// CONSTANT
//==========================================================================
extern "C" const GUID CLSID_DirectDraw = { 0xD7B70EE0, 0x4340, 0x11CF, 0xB0, 0x63, 0x00, 0x20, 0xAF, 0xC2, 0xCD, 0x35 };
extern "C" const GUID IID_IDirectDraw  = { 0x6C14DB80, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60 };


//==========================================================================
// VARIABLE
//==========================================================================
static IDirectDraw* pDirectDraw = NULL;
static IDirectDrawSurface *pSurface = NULL;
static long Width;
static long Height;


//==========================================================================
// VARIABLE
//==========================================================================
static bool CreateSurface( IDirectDrawSurface **ppSurf, long w, long h );


//==========================================================================
/**
	DirectX初期化
*/
//==========================================================================
bool DxInitialize( HWND hWnd )
{
	HRESULT hr;

	//=================================================
	// ＣＯＭ初期化
	//=================================================
	::CoInitialize( NULL );

	//=================================================
	//	DirectDraw生成
	//=================================================
	hr = ::CoCreateInstance(
				CLSID_DirectDraw,
				NULL,
				CLSCTX_ALL,
				IID_IDirectDraw,
				(LPVOID *)&pDirectDraw );
	if FAILED( hr ) return false;

	//=================================================
	//	DirectDraw初期化
	//=================================================
	hr = pDirectDraw->Initialize( (GUID *)DDCREATE_EMULATIONONLY );
	if FAILED( hr ) return false;

	//=================================================
	// 協調レベルの設定
	//=================================================
	hr = pDirectDraw->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
	if FAILED( hr ) return false;

	//=================================================
	// バックバッファ生成
	//=================================================
	RECT rect;
	::GetWindowRect( hWnd, &rect );
	Width = rect.right - rect.left;
	Height = rect.bottom - rect.top;
	if ( !CreateSurface( &pSurface, Width, Height ) ) return false;

	return true;
}

//==========================================================================
/**
	DirectX解放
*/
//==========================================================================
void DxFinalize( void )
{
	if ( pSurface != NULL )
	{
		pSurface->Release();
		pSurface = NULL;
	}

	if ( pDirectDraw != NULL )
	{
		pDirectDraw->Release();
		pDirectDraw = NULL;
	}

	CoUninitialize();
}

//==========================================================================
/**
	バックバッファ更新
*/
//==========================================================================
void DxUpdateBackBuffer( CSurface *pSurf )
{
	DDSURFACEDESC ddsd = { sizeof(DDSURFACEDESC) };

	if ( pSurface == NULL ) return;

	if SUCCEEDED( pSurface->Lock( NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL ) )
	{
		::FillMemory( ddsd.lpSurface, ddsd.lPitch*ddsd.dwHeight, 0x80 );

		PIXELDATA32 *pDst	= (PIXELDATA32*)ddsd.lpSurface;
		long DstPitch		= ddsd.lPitch / 4;

		PIXELDATA32 *pSrc;
		long SrcPitch;

		if ( pSurf->GetData( &pSrc, &SrcPitch ) )
		{
			long w = pSurf->GetWidth();
			long h = pSurf->GetHeight();

			for ( long y = 0; y < h; y++ )
			{
				for ( long x = 0; x < w; x++ )
				{
					long r1 = pSrc[x].r;
					long g1 = pSrc[x].g;
					long b1 = pSrc[x].b;
					long r2 = pDst[x].r;
					long g2 = pDst[x].g;
					long b2 = pDst[x].b;

					long r = r2 + (((r1 - r2) * pSrc[x].a) / 0xFF);
					long g = g2 + (((g1 - g2) * pSrc[x].a) / 0xFF);
					long b = b2 + (((b1 - b2) * pSrc[x].a) / 0xFF);

					pDst[x].a = pSrc[x].a;
					pDst[x].r = (unsigned char)r;
					pDst[x].g = (unsigned char)g;
					pDst[x].b = (unsigned char)b;
				}
				pSrc += SrcPitch;
				pDst += DstPitch;
			}

			pSurface->Unlock( &ddsd );
		}
	}
}

//==========================================================================
/**
	バックバッファ更新
*/
//==========================================================================
void DxRefreshBackBuffer( HWND hWnd )
{
	HDC src_dc;
	HDC dst_dc;

	pSurface->GetDC( &src_dc );
	dst_dc = ::GetDC( hWnd );

	::BitBlt( dst_dc, 0, 0, Width, Height, src_dc, 0, 0, SRCCOPY );

	::ReleaseDC( hWnd, dst_dc );
	pSurface->ReleaseDC( src_dc );
}

//==========================================================================
//
//		DirectDrawSurface生成
//
//==========================================================================
bool CreateSurface( IDirectDrawSurface **ppSurf, long w, long h )
{
	if ( (*ppSurf) != NULL )
	{
		(*ppSurf)->Release();
		(*ppSurf) = NULL;
	}

	DDSURFACEDESC ddsd	= { sizeof(DDSURFACEDESC) };
	ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth		= w;
	ddsd.dwHeight		= h;

	ddsd.ddpfPixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags			= DDPF_RGB | DDPF_ALPHAPIXELS;
	ddsd.ddpfPixelFormat.dwRGBBitCount		= 32;
	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask	= 0xFF000000;
	ddsd.ddpfPixelFormat.dwRBitMask			= 0x00FF0000;
	ddsd.ddpfPixelFormat.dwGBitMask			= 0x0000FF00;
	ddsd.ddpfPixelFormat.dwBBitMask			= 0x000000FF;

	// 生成
	return SUCCEEDED( pDirectDraw->CreateSurface( &ddsd, ppSurf, NULL ) );
}

