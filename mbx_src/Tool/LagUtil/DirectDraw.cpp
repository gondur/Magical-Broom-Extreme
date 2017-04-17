//==========================================================================
//
//
//		DirectDraw �t�@�C���֘A
//
//
//==========================================================================


#define INITGUID

//==========================================================================
// INCLUDE
//==========================================================================
#include <windows.h>
#include <ddraw.h>

#include "DirectDraw.h"
#include "LagUtil.h"
#include "Lag.h"


//==========================================================================
// GLOBAL
//==========================================================================
LPDIRECTDRAW lpDirectDraw = NULL;			// DirectDraw�I�u�W�F�N�g

LPDIRECTDRAWSURFACE lpBackBuffer = NULL;	// �o�b�N�o�b�t�@�p
LPDIRECTDRAWSURFACE lpSurface = NULL;		// �O���t�B�b�N�p
LPDIRECTDRAWSURFACE lpAlpha = NULL;			// �A���t�@�p

DDSURFACEDESC SurfaceDesc = { sizeof( DDSURFACEDESC ) };

long GraphicWidth;							// �摜����
long GraphicHeight;							// �摜��


//==========================================================================
// PROTOTYPE
//==========================================================================
bool CreateSurface( LPDIRECTDRAWSURFACE *ppSurf, long w, long h );
bool BMP2Surface( char *file, LPDIRECTDRAWSURFACE *ppSurf, long *w, long *h );
bool BlitToAlphaChannel( LPDIRECTDRAWSURFACE *pSurf );
void RefreshBackBuffer( void );


//==========================================================================
//
//
//		DirectDraw������
//
//
//==========================================================================
bool InitDirectX( HWND hWnd )
{
	HRESULT hr;

	//=================================================
	//	DirectDraw����
	//=================================================
	hr = CoCreateInstance(
			CLSID_DirectDraw,
			NULL,
			CLSCTX_ALL,
			IID_IDirectDraw,
			(LPVOID *)&lpDirectDraw
			);
	if FAILED( hr )
	{
		MsgBox( "Error","DirectDraw�̎擾�Ɏ��s" );
		return false;
	}
	
	//=================================================
	//	DirectDraw������
	//=================================================
	hr = lpDirectDraw->Initialize( (GUID *)DDCREATE_EMULATIONONLY );
	if FAILED( hr )
	{
		MsgBox( "Error","DirectDraw�̏������Ɏ��s" );
		return false;
	}
	
	//=================================================
	// �������x���̐ݒ�
	//=================================================
	hr = lpDirectDraw->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
	if FAILED( hr )
	{
		MsgBox( "Error", "�������x���̐ݒ�Ɏ��s" );
		return false;
	}

	GraphicWidth = -1;
	GraphicHeight = -1;

	return true;
}

//==========================================================================
//
//
//		DirectDraw�J��
//
//
//==========================================================================
void UninitDirectX( void )
{
	SAFE_RELEASE( lpAlpha );
	SAFE_RELEASE( lpSurface );
	SAFE_RELEASE( lpBackBuffer );
	SAFE_RELEASE( lpDirectDraw );
}

//==========================================================================
//
//
//		��ʍX�V
//
//
//==========================================================================
bool Refresh( HWND hWnd, long dx, long dy )
{
	if ( lpBackBuffer != NULL )
	{
		PAINTSTRUCT ps;
		HDC hdc1, hdc2;
		long w, h;

		// �o�b�N�o�b�t�@�̃f�o�C�X�R���e�L�X�g�擾
		if SUCCEEDED( lpBackBuffer->GetDC( &hdc2 ) )
		{
			// �E�B���h�E�̃f�o�C�X�R���e�L�X�g�擾
			hdc1 = BeginPaint( hWnd, &ps );

			// �E�B���h�E�Ƀo�b�N�o�b�t�@�̓��e��]��
			BitBlt( hdc1, dx, dy, GraphicWidth, GraphicHeight, hdc2, 0, 0, SRCCOPY );

			// �f�o�C�X�R���e�L�X�g�J��
			lpBackBuffer->ReleaseDC( hdc2 );
			EndPaint( hWnd, &ps );

			return true;
		}
	}

	return false;
}


//==========================================================================
//
//
//		DirectDrawSurface ����
//
//
//==========================================================================
bool CreateSurface( LPDIRECTDRAWSURFACE *ppSurf, long w, long h )
{
	SAFE_RELEASE( *ppSurf );

	DDSURFACEDESC ddsd = { sizeof(DDSURFACEDESC) };
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

	// ����
	if FAILED( lpDirectDraw->CreateSurface( &ddsd, ppSurf, NULL ) )
	{
		MsgBox( "Error", "�T�[�t�F�C�X�̐����Ɏ��s" );
		return false;
	}
	
	return true;
}

//==========================================================================
//
//
//		BMP�t�@�C���ǂݍ���
//
//
//==========================================================================
bool LoadBMP( char *file, eFormat fmt )
{
	bool ret = false;
	long w = -1, h = -1;

	switch ( fmt )
	{
	case FMT_GRAPHIC:
		// �摜�ǂݍ���
		if ( BMP2Surface( file, &lpSurface, &w, &h ) == false ) return false;
		if ( CreateSurface( &lpBackBuffer, w, h ) == false ) return false;
		// �摜�T�C�Y�ۑ�
		GraphicWidth = w;
		GraphicHeight = h;
		// �A���t�@�f�[�^�]��
		BlitToAlphaChannel( NULL );
		// ����
		ret = true;
		break;
	case FMT_ALPHA:
		// �`�F�b�N
		if ( GraphicWidth < 0 || GraphicHeight < 0 )
		{
			SAFE_RELEASE( lpAlpha );
			MsgBox( "Error", "���摜���ǂݍ��܂�Ă��Ȃ��̂�\n�A���t�@�p�摜��ǂݍ������Ƃ��Ă��܂�" );
			return false;
		}
		// �摜�ǂݍ���
		if ( BMP2Surface( file, &lpAlpha, &w, &h ) == false ) return false;
		// �摜�T�C�Y�`�F�b�N
		if ( w != GraphicWidth || h != GraphicHeight )
		{
			SAFE_RELEASE( lpAlpha );
			MsgBox( "Error", "�摜�̃T�C�Y����v���܂���" );
			return false;
		}
		// �A���t�@�f�[�^�]��
		BlitToAlphaChannel( &lpAlpha );
		// ����
		SAFE_RELEASE( lpAlpha );
		break;
	}

	// �o�b�N�o�b�t�@�̓��e�X�V
	RefreshBackBuffer();

	return true;
}

//==========================================================================
//
//
//		BMP�t�@�C�����T�[�t�F�C�X�ɓW�J
//
//
//==========================================================================
bool BMP2Surface( char *file, LPDIRECTDRAWSURFACE *ppSurf, long *w, long *h )
{
	//=======================================================
	// �t�@�C���I�[�v��
	//=======================================================
	HBITMAP hBitmap = ( HBITMAP )LoadImage( NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
	if ( hBitmap == NULL )
	{
		return false;
	}

	//=======================================================
	// �T�[�t�F�C�X����
	//=======================================================
	BITMAP BitMap;
	GetObject( hBitmap, sizeof(BITMAP), &BitMap );

	if ( CreateSurface( ppSurf, BitMap.bmWidth, BitMap.bmHeight )  == false ) return false;

	//=======================================================
	// �r�b�g�}�b�v���T�[�t�F�C�X�ɓ]��
	//=======================================================
	HDC hdcBitmap;
	HDC hdc;
	HBITMAP hbmOld;
	
	hdcBitmap = CreateCompatibleDC( NULL );
	hbmOld = (HBITMAP)SelectObject( hdcBitmap, hBitmap );
	
	if FAILED( (*ppSurf)->GetDC( &hdc ) )
	{
		MsgBox( "Error", "Bitmap�t�@�C���̓W�J�Ɏ��s" );
		return false;
	}

	BitBlt( hdc, 0, 0, BitMap.bmWidth, BitMap.bmHeight, hdcBitmap, 0, 0, SRCCOPY );

	(*ppSurf)->ReleaseDC( hdc );
	
	SelectObject( hdcBitmap, hbmOld );
	DeleteDC( hdcBitmap );

	*w = BitMap.bmWidth;
	*h = BitMap.bmHeight;

	return true;
}

//==========================================================================
//
//
//		�摜�T�C�Y�擾
//
//
//==========================================================================
void GetGraphicSize( long *w, long *h )
{
	if ( w != NULL ) *w = GraphicWidth;
	if ( h != NULL ) *h = GraphicHeight;
}

//==========================================================================
//
//
//		�A���t�@�`�����l���f�[�^�X�V
//
//
//==========================================================================
bool BlitToAlphaChannel( LPDIRECTDRAWSURFACE *pSurf )
{
	if ( pSurf == NULL )
	{
		HRESULT hr;
		DDSURFACEDESC ddsd = { sizeof( DDSURFACEDESC ) };
		hr = lpSurface->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
		if SUCCEEDED( hr )
		{
			PIXELDATA32 *pData = (PIXELDATA32 *)ddsd.lpSurface;
			unsigned long Pitch = ddsd.lPitch / sizeof(PIXELDATA32);
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					pData[x].a = 0xFF;
				}
				pData += Pitch;
			}

			lpSurface->Unlock( &ddsd );
		}
	}
	else
	{
		HRESULT hr;
		DDSURFACEDESC ddsd1 = { sizeof( DDSURFACEDESC ) };
		DDSURFACEDESC ddsd2 = { sizeof( DDSURFACEDESC ) };

		hr = (*pSurf)->Lock( NULL, &ddsd1, DDLOCK_WAIT, NULL );
		if SUCCEEDED( hr )
		{
			hr = lpSurface->Lock( NULL, &ddsd2, DDLOCK_WAIT, NULL );
			if SUCCEEDED( hr )
			{
				PIXELDATA32 *pData1 = (PIXELDATA32 *)ddsd1.lpSurface;
				PIXELDATA32 *pData2 = (PIXELDATA32 *)ddsd2.lpSurface;
				unsigned long Pitch1 = ddsd1.lPitch / sizeof(PIXELDATA32);
				unsigned long Pitch2 = ddsd2.lPitch / sizeof(PIXELDATA32);
				for ( long y = 0; y < GraphicHeight; y++ )
				{
					for ( long x = 0; x < GraphicWidth; x++ )
					{
						long alpha = pData1[x].r + pData1[x].g + pData1[x].b;
						pData2[x].a = (char)(alpha / 3);
					}
					pData1 += Pitch1;
					pData2 += Pitch2;
				}

				lpSurface->Unlock( &ddsd2 );
			}
			(*pSurf)->Unlock( &ddsd1 );
		}
	}

	return true;
}

//==========================================================================
//
//
//		�o�b�N�o�b�t�@�X�V
//
//
//==========================================================================
void RefreshBackBuffer( void )
{
	if ( lpBackBuffer == NULL ) return;
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd1 = { sizeof( DDSURFACEDESC ) };
	DDSURFACEDESC ddsd2 = { sizeof( DDSURFACEDESC ) };

	hr = lpBackBuffer->Lock( NULL, &ddsd1, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		hr = lpSurface->Lock( NULL, &ddsd2, DDLOCK_WAIT, NULL );
		if SUCCEEDED( hr )
		{
			PIXELDATA32 *pData1 = (PIXELDATA32 *)ddsd1.lpSurface;
			PIXELDATA32 *pData2 = (PIXELDATA32 *)ddsd2.lpSurface;
			unsigned long Pitch1 = ddsd1.lPitch / sizeof(PIXELDATA32);
			unsigned long Pitch2 = ddsd2.lPitch / sizeof(PIXELDATA32);
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					long bg[2][2] = { 0xC0, 0x40, 0x40, 0xC0 };
					long c = bg[(x & 0x2F)>>5][(y & 0x2F)>>5];
					long alpha = pData2[x].a;
					pData1[x].a = 0xFF;
					pData1[x].r = (char)( ((pData2[x].r - c) * alpha / 255) + c );
					pData1[x].g = (char)( ((pData2[x].g - c) * alpha / 255) + c );
					pData1[x].b = (char)( ((pData2[x].b - c) * alpha / 255) + c );
				}
				pData1 += Pitch1;
				pData2 += Pitch2;
			}
			lpSurface->Unlock( &ddsd2 );
		}
		lpBackBuffer->Unlock( &ddsd1 );
	}

	InvalidateRect( GetActiveWindow(), NULL, 0 );
}


//==========================================================================
//
//
//		�J���[�擾
//
//
//==========================================================================
void GetColor( long *r, long *g, long *b, long x, long y )
{
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd = { sizeof( DDSURFACEDESC ) };
	hr = lpSurface->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		PIXELDATA32 *pData = (PIXELDATA32 *)ddsd.lpSurface;
		unsigned long Pitch = ddsd.lPitch / sizeof(PIXELDATA32);

		PIXELDATA32 pd = pData[x + y*Pitch];
		*r = pd.r;
		*g = pd.g;
		*b = pd.b;

		lpSurface->Unlock( &ddsd );
	}
}

//==========================================================================
//
//
//		�J���[�L�[�ݒ�
//
//
//==========================================================================
void SetColorKey( long r, long g, long b )
{
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd = { sizeof( DDSURFACEDESC ) };
	hr = lpSurface->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		PIXELDATA32 *pData = (PIXELDATA32 *)ddsd.lpSurface;
		unsigned long Pitch = ddsd.lPitch / sizeof(PIXELDATA32);
		for ( long y = 0; y < GraphicHeight; y++ )
		{
			for ( long x = 0; x < GraphicWidth; x++ )
			{
				if ( pData[x].r == r )
				{
					if ( pData[x].g == g )
					{
						if ( pData[x].b == b )
						{
							pData[x].a = 0x00;
						}
					}
				}
			}
			pData += Pitch;
		}

		lpSurface->Unlock( &ddsd );
	}

	// ��ʍX�V
	RefreshBackBuffer();
}

//==========================================================================
//
//
//		�J���[�L�[����
//
//
//==========================================================================
void RestoreColorKey( void )
{
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd = { sizeof( DDSURFACEDESC ) };
	hr = lpSurface->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		PIXELDATA32 *pData = (PIXELDATA32 *)ddsd.lpSurface;
		unsigned long Pitch = ddsd.lPitch / sizeof(PIXELDATA32);
		for ( long y = 0; y < GraphicHeight; y++ )
		{
			for ( long x = 0; x < GraphicWidth; x++ )
			{
				pData[x].a = 0xFF;
			}
			pData += Pitch;
		}

		lpSurface->Unlock( &ddsd );
	}

	// ��ʍX�V
	RefreshBackBuffer();
}

//==========================================================================
//
//
//		�f�[�^���b�N�J�n
//
//
//==========================================================================
PIXELDATA32 *LockSurface( long *pitch )
{
	if ( lpSurface == NULL ) return NULL;

	if SUCCEEDED( lpSurface->Lock( NULL, &SurfaceDesc, DDLOCK_WAIT, NULL ) )
	{
		*pitch = SurfaceDesc.lPitch / sizeof(PIXELDATA32);
		return (PIXELDATA32 *)SurfaceDesc.lpSurface;
	}
	else
	{
		return NULL;
	}
}

//==========================================================================
//
//
//		�f�[�^���b�N����
//
//
//==========================================================================
void UnlockSurface( void )
{
	lpSurface->Unlock( &SurfaceDesc );
}

//==========================================================================
//
//
//		���E���]
//
//
//==========================================================================
void GraphciLeftRight( void )
{
	if ( lpBackBuffer == NULL ) return;
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd1 = { sizeof( DDSURFACEDESC ) };
	DDSURFACEDESC ddsd2 = { sizeof( DDSURFACEDESC ) };

	hr = lpBackBuffer->Lock( NULL, &ddsd1, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		hr = lpSurface->Lock( NULL, &ddsd2, DDLOCK_WAIT, NULL );
		if SUCCEEDED( hr )
		{
			PIXELDATA32 *pData1 = (PIXELDATA32 *)ddsd1.lpSurface;
			PIXELDATA32 *pData2 = (PIXELDATA32 *)ddsd2.lpSurface;
			unsigned long Pitch1 = ddsd1.lPitch / sizeof(PIXELDATA32);
			unsigned long Pitch2 = ddsd2.lPitch / sizeof(PIXELDATA32);

			// �Ƃ肠�����R�s�[
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				long dy = Pitch2 * y;
				long sy = Pitch1 * y;
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					pData1[x + dy] = pData2[x + sy];
				}
			}

			// ���E���]�R�s�[
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				long dy = Pitch2 * y;
				long sy = Pitch1 * y;
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					pData2[x + dy] = pData1[(GraphicWidth-1-x) + sy];
				}
			}
			lpSurface->Unlock( &ddsd2 );
		}
		lpBackBuffer->Unlock( &ddsd1 );
	}

	// ��ʍX�V
	RefreshBackBuffer();
}

//==========================================================================
//
//
//		�㉺���]
//
//
//==========================================================================
void GraphciUpDown( void )
{
	if ( lpBackBuffer == NULL ) return;
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd1 = { sizeof( DDSURFACEDESC ) };
	DDSURFACEDESC ddsd2 = { sizeof( DDSURFACEDESC ) };

	hr = lpBackBuffer->Lock( NULL, &ddsd1, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		hr = lpSurface->Lock( NULL, &ddsd2, DDLOCK_WAIT, NULL );
		if SUCCEEDED( hr )
		{
			PIXELDATA32 *pData1 = (PIXELDATA32 *)ddsd1.lpSurface;
			PIXELDATA32 *pData2 = (PIXELDATA32 *)ddsd2.lpSurface;
			unsigned long Pitch1 = ddsd1.lPitch / sizeof(PIXELDATA32);
			unsigned long Pitch2 = ddsd2.lPitch / sizeof(PIXELDATA32);

			// �Ƃ肠�����R�s�[
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				long dy = Pitch2 * y;
				long sy = Pitch1 * y;
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					pData1[x + dy] = pData2[x + sy];
				}
			}

			// �㉺���]�R�s�[
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				long dy = Pitch2 * y;
				long sy = Pitch1 * (GraphicHeight-1-y);
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					pData2[x + dy] = pData1[x + sy];
				}
			}
			lpSurface->Unlock( &ddsd2 );
		}
		lpBackBuffer->Unlock( &ddsd1 );
	}

	// ��ʍX�V
	RefreshBackBuffer();
}

//==========================================================================
//
//
//		�摜���]
//
//
//==========================================================================
void GraphciReverse( void )
{
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd = { sizeof( DDSURFACEDESC ) };
	hr = lpSurface->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		PIXELDATA32 *pData = (PIXELDATA32 *)ddsd.lpSurface;
		unsigned long Pitch = ddsd.lPitch / sizeof(PIXELDATA32);
		for ( long y = 0; y < GraphicHeight; y++ )
		{
			for ( long x = 0; x < GraphicWidth; x++ )
			{
				pData[x].r = (unsigned char)~pData[x].r;
				pData[x].g = (unsigned char)~pData[x].g;
				pData[x].b = (unsigned char)~pData[x].b;
			}
			pData += Pitch;
		}

		lpSurface->Unlock( &ddsd );
	}

	// ��ʍX�V
	RefreshBackBuffer();
}


//==========================================================================
//
//
//		�摜�g��k��
//
//
//==========================================================================
void BiLinearFilter( float sx, float sy )
{
	if ( lpBackBuffer == NULL ) return;
	if ( lpSurface == NULL ) return;

	HRESULT hr;
	DDSURFACEDESC ddsd1 = { sizeof( DDSURFACEDESC ) };
	DDSURFACEDESC ddsd2 = { sizeof( DDSURFACEDESC ) };

	hr = lpBackBuffer->Lock( NULL, &ddsd1, DDLOCK_WAIT, NULL );
	if SUCCEEDED( hr )
	{
		hr = lpSurface->Lock( NULL, &ddsd2, DDLOCK_WAIT, NULL );
		if SUCCEEDED( hr )
		{
			PIXELDATA32 *pData1 = (PIXELDATA32 *)ddsd1.lpSurface;
			PIXELDATA32 *pData2 = (PIXELDATA32 *)ddsd2.lpSurface;
			unsigned long Pitch1 = ddsd1.lPitch / sizeof(PIXELDATA32);
			unsigned long Pitch2 = ddsd2.lPitch / sizeof(PIXELDATA32);

			// �Ƃ肠�����R�s�[
			for ( long y = 0; y < GraphicHeight; y++ )
			{
				long dy = Pitch2 * y;
				long sy = Pitch1 * y;
				for ( long x = 0; x < GraphicWidth; x++ )
				{
					pData1[x + dy] = pData2[x + sy];
				}
			}

			// �㉺���]�R�s�[
			lpSurface->Unlock( &ddsd2 );
		}
		lpBackBuffer->Unlock( &ddsd1 );
	}

	// ��ʍX�V
	RefreshBackBuffer();
}