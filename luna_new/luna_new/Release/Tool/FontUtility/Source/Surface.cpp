

//==========================================================================
// INCLUDE
//==========================================================================
#include "Surface.h"


//==========================================================================
// STRUCT
//==========================================================================
struct TGA_HEADER
{
	unsigned char	No_ID;			// 0=�C���[�W�h�c����
	unsigned char	CMap_Type;		// 0=�J���[�}�b�v����
	unsigned char	Image_Type;		// 2=�����kRGB�^�C�v 10=���kRGB�^�C�v
	unsigned char	CMap_Spec[5];	// �X�L�b�v�����
	unsigned short	Ox;				// ��� ���� X 0�Œ�
	unsigned short	Oy;				// ��� ���� Y 0�Œ�
	unsigned short	Width;			// �� (dot)
	unsigned short	Hight;			// ���� (dot)
	unsigned char	Pixel;			// Pixel Size. 32=32bit
	unsigned char	IDesc_Type;		// 8=TGA32 �A�g���r���[�g
};


//==========================================================================
// DEFINE
//==========================================================================
#define OUTPUT_TGA		1


//==========================================================================
/**
	�R���X�g���N�^
*/
//==========================================================================
CSurface::CSurface()
{
	m_pPixel	= NULL;
	m_Width		= 0;
	m_Height	= 0;

	m_pColorBox			= NULL;
	m_pPaletteSurface	= NULL;
	m_pPaletteUseCount	= NULL;
	m_pPalette			= NULL;
	m_PaletteCount		= 0;
}

//==========================================================================
/**
	�f�X�g���N�^
*/
//==========================================================================
CSurface::~CSurface()
{
	Release();
}

//==========================================================================
/**
	�������ǂ���
*/
//==========================================================================
bool CSurface::IsInvalid( void )
{
	return (m_pPixel == NULL); 
}

//==========================================================================
/**
	���b�N
*/
//==========================================================================
bool CSurface::GetData( PIXELDATA32 **ppAddr, long *pPitch )
{
	if ( !IsInvalid() )
	{
		*ppAddr = m_pPixel;
		*pPitch = m_Width;
		return true;
	}

	return false;
}

//==========================================================================
/**
	����
*/
//==========================================================================
bool CSurface::Create( long Width, long Height )
{
	Release();

	m_pPixel = (PIXELDATA32*)SAFE_ALLOC( sizeof(PIXELDATA32) * Width * Height );
	if ( m_pPixel != NULL )
	{
		m_Width = Width;
		m_Height = Height;
		Clear();
		return true;
	}

	return false;
}

//==========================================================================
//
//		�R�s�[
//
//==========================================================================
void CSurface::Create( CSurface *pSurf )
{
	Create( pSurf->m_Width, pSurf->m_Height );

	::CopyMemory( m_pPixel, pSurf->m_pPixel, sizeof(PIXELDATA32) * m_Width * m_Height );
}

//==========================================================================
/**
	�r�b�g�}�b�v�ǂݍ���
*/
//==========================================================================
bool CSurface::LoadBMP( char *pFileName )
{
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpih;
	RGBQUAD Palette[256];
	FILE *fp;

	// �摜�ǂݍ���
	fp = fopen( pFileName, "rb" );
	if ( fp == NULL ) return false;

	// �w�b�_�ǂݍ���
	fread( &bmpfh, sizeof(BITMAPFILEHEADER), 1, fp );
	fread( &bmpih, sizeof(BITMAPINFOHEADER), 1, fp );
	if ( (bmpih.biBitCount != 4) && (bmpih.biBitCount != 8) && (bmpih.biBitCount != 24) )
	{
		fclose( fp );
		return false;
	}

	// ���T�[�t�F�C�X����
	Create( bmpih.biWidth, bmpih.biHeight );

	// �F�����Ƃ̓ǂݍ���
	switch ( bmpih.biBitCount )
	{
	case 4:
		// �p���b�g
		fread( Palette, sizeof(RGBQUAD), 16, fp );
		// �f�[�^�ʒu�ɃV�[�N
		fseek( fp, bmpfh.bfOffBits, SEEK_SET );
		// �C���[�W�ǂݍ���
		for ( long y = 0; y < bmpih.biHeight; y++ )
		{
			long yy = bmpih.biHeight - 1 - y;
			long xx = 0;
			for ( long x = 0; x < bmpih.biWidth / 2; x++ )
			{
				unsigned char Index;
				fread( &Index, sizeof(unsigned char), 1, fp );
				SetColor( xx, yy, (PIXELDATA32*)&Palette[(Index>>4)&0x0F] );
				xx++;
				SetColor( xx, yy, (PIXELDATA32*)&Palette[(Index>>0)&0x0F] );
				xx++;
			}
		}
		break;
	case 8:
		// �p���b�g
		fread( Palette, sizeof(RGBQUAD), 256, fp );
		// �f�[�^�ʒu�ɃV�[�N
		fseek( fp, bmpfh.bfOffBits, SEEK_SET );
		// �C���[�W�ǂݍ���
		for ( long y = 0; y < bmpih.biHeight; y++ )
		{
			long yy = bmpih.biHeight - 1 - y;
			for ( long x = 0; x < bmpih.biWidth; x++ )
			{
				unsigned char Index;
				fread( &Index, sizeof(unsigned char), 1, fp );
				SetColor( x, yy, (PIXELDATA32*)&Palette[Index] );
			}
		}
		break;
	case 24:
		// �f�[�^�ʒu�ɃV�[�N
		fseek( fp, bmpfh.bfOffBits, SEEK_SET );
		// �C���[�W�ǂݍ���
		for ( long y = 0; y < bmpih.biHeight; y++ )
		{
			long yy = bmpih.biHeight - 1 - y;
			for ( long x = 0; x < bmpih.biWidth; x++ )
			{
				PIXELDATA32 Pixel = { 0, 0, 0, 0xFF };
				fread( &Pixel, sizeof(unsigned char), 3, fp );
				SetColor( x, yy, &Pixel );
			}
		}
		break;
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	return true;
}

//==========================================================================
/**
	���
*/
//==========================================================================
void CSurface::Release( void )
{
	ReleasePalette();

	SAFE_FREE( m_pPixel );
	m_Width		= 0;
	m_Height	= 0;
}

//==========================================================================
/**
	���擾
*/
//==========================================================================
long CSurface::GetWidth( void )
{
	return m_Width;
}

//==========================================================================
/**
	�����擾
*/
//==========================================================================
long CSurface::GetHeight( void )
{
	return m_Height;
}

//==========================================================================
/**
	�N���A
*/
//==========================================================================
void CSurface::Clear( void )
{
	::ZeroMemory( m_pPixel, sizeof(PIXELDATA32) * m_Width * m_Height );
}

//==========================================================================
/**
	�N���A
*/
//==========================================================================
void CSurface::Clear( PIXELDATA32 Color )
{
	PIXELDATA32 *pPix = m_pPixel;

	long Size = m_Width * m_Height;
	while ( Size-- != 0 ) *pPix++ = Color;
}

//==========================================================================
//
//		�R�s�[
//
//==========================================================================
void CSurface::Draw( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h )
{
	if ( IsInvalid() ) return;

	long w = m_Width;
	long h = m_Height;

	long dst_x1 = x;
	long dst_y1 = y;
	long dst_x2 = x + src_w;
	long dst_y2 = y + src_h;

	long src_x1 = src_x;
	long src_y1 = src_y;
	long src_x2 = src_x + src_w;
	long src_y2 = src_y + src_h;

	if ( dst_x1 < 0 ) { src_x1 -= dst_x1; dst_x1 = 0; };
	if ( dst_y1 < 0 ) { src_y1 -= dst_y1; dst_y1 = 0; };
	if ( dst_x2 > w ) { long tmp = dst_x2 - w; dst_x2 = w; src_x2 -= tmp; }
	if ( dst_y2 > h ) { long tmp = dst_y2 - h; dst_y2 = h; src_y2 -= tmp; }

	src_w = src_x2 - src_x1;
	src_h = src_y2 - src_y1;

	PIXELDATA32 *pDst, *pSrc;
	long dst_pitch, src_pitch;

	if ( GetData( &pDst, &dst_pitch ) )
	{
		if ( pSurf->GetData( &pSrc, &src_pitch ) )
		{
			pDst += dst_x1 + (dst_y1 * dst_pitch);
			pSrc += src_x1 + (src_y1 * src_pitch);

			for ( long py = 0; py < src_h; py++ )
			{
				for ( long px = 0; px < src_w; px++ )
				{
					long a1 = pSrc[px].a;
					long r1 = pSrc[px].r;
					long g1 = pSrc[px].g;
					long b1 = pSrc[px].b;
					long a2 = pDst[px].a;
					long r2 = pDst[px].r;
					long g2 = pDst[px].g;
					long b2 = pDst[px].b;

					long r = r2 + (((r1 - r2) * a1) / 0xFF);
					long g = g2 + (((g1 - g2) * a1) / 0xFF);
					long b = b2 + (((b1 - b2) * a1) / 0xFF);

					pDst[px].b = (unsigned char)b;
					pDst[px].g = (unsigned char)g;
					pDst[px].r = (unsigned char)r;
					pDst[px].a = (unsigned char)(a1 > 0x00 ? 0xFF : a2);
				}

				pSrc += src_pitch;
				pDst += dst_pitch;
			}
		}
	}
}


//==========================================================================
//
//		�R�s�[
//
//==========================================================================
void CSurface::DrawNoAlpha( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h )
{
	if ( IsInvalid() ) return;

	long w = m_Width;
	long h = m_Height;

	long dst_x1 = x;
	long dst_y1 = y;
	long dst_x2 = x + src_w;
	long dst_y2 = y + src_h;

	long src_x1 = src_x;
	long src_y1 = src_y;
	long src_x2 = src_x + src_w;
	long src_y2 = src_y + src_h;

	if ( dst_x1 < 0 ) { src_x1 -= dst_x1; dst_x1 = 0; };
	if ( dst_y1 < 0 ) { src_y1 -= dst_y1; dst_y1 = 0; };
	if ( dst_x2 > w ) { long tmp = dst_x2 - w; dst_x2 = w; src_x2 -= tmp; }
	if ( dst_y2 > h ) { long tmp = dst_y2 - h; dst_y2 = h; src_y2 -= tmp; }

	src_w = src_x2 - src_x1;
	src_h = src_y2 - src_y1;

	PIXELDATA32 *pDst, *pSrc;
	long dst_pitch, src_pitch;

	if ( GetData( &pDst, &dst_pitch ) )
	{
		if ( pSurf->GetData( &pSrc, &src_pitch ) )
		{
			pDst += dst_x1 + (dst_y1 * dst_pitch);
			pSrc += src_x1 + (src_y1 * src_pitch);

			for ( long py = 0; py < src_h; py++ )
			{
				for ( long px = 0; px < src_w; px++ )
				{
					long a1 = pSrc[px].a;
					long r1 = pSrc[px].r;
					long g1 = pSrc[px].g;
					long b1 = pSrc[px].b;
					long a2 = pDst[px].a;
					long r2 = pDst[px].r;
					long g2 = pDst[px].g;
					long b2 = pDst[px].b;

					long a = a1 + a2;
					long r = r1;
					long g = g1;
					long b = b1;
					if ( a > 255 ) a = 255;

					PIXELDATA32 pixel = {
						(unsigned char)b,
						(unsigned char)g,
						(unsigned char)r,
						(unsigned char)a,
					};
					pDst[px] = pixel;
				}
				pSrc += src_pitch;
				pDst += dst_pitch;
			}
		}
	}
}

//==========================================================================
//
//		�R�s�[
//
//==========================================================================
void CSurface::ColorDraw( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h, PIXELDATA32 Pixel )
{
	if ( IsInvalid() ) return;

	long w = m_Width;
	long h = m_Height;

	long dst_x1 = x;
	long dst_y1 = y;
	long dst_x2 = x + src_w;
	long dst_y2 = y + src_h;

	long src_x1 = src_x;
	long src_y1 = src_y;
	long src_x2 = src_x + src_w;
	long src_y2 = src_y + src_h;

	if ( dst_x1 < 0 ) { src_x1 -= dst_x1; dst_x1 = 0; };
	if ( dst_y1 < 0 ) { src_y1 -= dst_y1; dst_y1 = 0; };
	if ( dst_x2 > w ) { long tmp = dst_x2 - w; dst_x2 = w; src_x2 -= tmp; }
	if ( dst_y2 > h ) { long tmp = dst_y2 - h; dst_y2 = h; src_y2 -= tmp; }

	src_w = src_x2 - src_x1;
	src_h = src_y2 - src_y1;

	PIXELDATA32 *pDst, *pSrc;
	long dst_pitch, src_pitch;

	if ( GetData( &pDst, &dst_pitch ) )
	{
		if ( pSurf->GetData( &pSrc, &src_pitch ) )
		{
			pDst += dst_x1 + (dst_y1 * dst_pitch);
			pSrc += src_x1 + (src_y1 * src_pitch);

			for ( long py = 0; py < src_h; py++ )
			{
				for ( long px = 0; px < src_w; px++ )
				{
					long a1 = pSrc[px].a;
					long a2 = pDst[px].a;

					Pixel.a = (unsigned char)((a1 > a2) ? (a1) : (a2));

					pDst[px] = Pixel;
				}
				pSrc += src_pitch;
				pDst += dst_pitch;
			}
		}
	}
}


//==========================================================================
//
//		�R�s�[
//
//==========================================================================
void CSurface::ColorDrawNoAlpha( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h, PIXELDATA32 Pixel )
{
	if ( IsInvalid() ) return;

	long w = m_Width;
	long h = m_Height;

	long dst_x1 = x;
	long dst_y1 = y;
	long dst_x2 = x + src_w;
	long dst_y2 = y + src_h;

	long src_x1 = src_x;
	long src_y1 = src_y;
	long src_x2 = src_x + src_w;
	long src_y2 = src_y + src_h;

	if ( dst_x1 < 0 ) { src_x1 -= dst_x1; dst_x1 = 0; };
	if ( dst_y1 < 0 ) { src_y1 -= dst_y1; dst_y1 = 0; };
	if ( dst_x2 > w ) { long tmp = dst_x2 - w; dst_x2 = w; src_x2 -= tmp; }
	if ( dst_y2 > h ) { long tmp = dst_y2 - h; dst_y2 = h; src_y2 -= tmp; }

	src_w = src_x2 - src_x1;
	src_h = src_y2 - src_y1;

	PIXELDATA32 *pDst, *pSrc;
	long dst_pitch, src_pitch;

	if ( GetData( &pDst, &dst_pitch ) )
	{
		if ( pSurf->GetData( &pSrc, &src_pitch ) )
		{
			pDst += dst_x1 + (dst_y1 * dst_pitch);
			pSrc += src_x1 + (src_y1 * src_pitch);

			for ( long py = 0; py < src_h; py++ )
			{
				for ( long px = 0; px < src_w; px++ )
				{
					long a1 = pSrc[px].a;
					long r1 = Pixel.r;
					long g1 = Pixel.g;
					long b1 = Pixel.b;
					long a2 = pDst[px].a;
					long r2 = pDst[px].r;
					long g2 = pDst[px].g;
					long b2 = pDst[px].b;

					long a = a1 + a2;
					long r = Pixel.r;
					long g = Pixel.g;
					long b = Pixel.b;
					if ( a > 255 ) a = 255;

					PIXELDATA32 pixel = {
						(unsigned char)b,
						(unsigned char)g,
						(unsigned char)r,
						(unsigned char)a
					};
					pDst[px] = pixel;
				}
				pSrc += src_pitch;
				pDst += dst_pitch;
			}
		}
	}
}

//==========================================================================
//
//		�R�s�[
//
//==========================================================================
void CSurface::DirectDraw( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h )
{
	if ( IsInvalid() ) return;

	long w = m_Width;
	long h = m_Height;

	long dst_x1 = x;
	long dst_y1 = y;
	long dst_x2 = x + src_w;
	long dst_y2 = y + src_h;

	long src_x1 = src_x;
	long src_y1 = src_y;
	long src_x2 = src_x + src_w;
	long src_y2 = src_y + src_h;

	if ( dst_x1 < 0 ) { src_x1 -= dst_x1; dst_x1 = 0; };
	if ( dst_y1 < 0 ) { src_y1 -= dst_y1; dst_y1 = 0; };
	if ( dst_x2 > w ) { long tmp = dst_x2 - w; dst_x2 = w; src_x2 -= tmp; }
	if ( dst_y2 > h ) { long tmp = dst_y2 - h; dst_y2 = h; src_y2 -= tmp; }

	src_w = src_x2 - src_x1;
	src_h = src_y2 - src_y1;

	PIXELDATA32 *pDst, *pSrc;
	long dst_pitch, src_pitch;

	if ( GetData( &pDst, &dst_pitch ) )
	{
		if ( pSurf->GetData( &pSrc, &src_pitch ) )
		{
			pDst += dst_x1 + (dst_y1 * dst_pitch);
			pSrc += src_x1 + (src_y1 * src_pitch);

			for ( long py = 0; py < src_h; py++ )
			{
				for ( long px = 0; px < src_w; px++ )
				{
					pDst[px] = pSrc[px];
				}
				pSrc += src_pitch;
				pDst += dst_pitch;
			}
		}
	}
}

//==========================================================================
//
//		�F�擾
//
//==========================================================================
bool CSurface::GetColor( long x, long y, PIXELDATA32 *pPixel )
{
	if ( (0 <= x) && (x < m_Width) )
	{
		if ( (0 <= y) && (y < m_Height) )
		{
			long Pitch;
			PIXELDATA32 *pDst;
			if ( GetData( &pDst, &Pitch ) )
			{
				*pPixel = pDst[x + (y * Pitch)];
				return true;
			}
		}
	}

	pPixel->a = pPixel->r = pPixel->g = pPixel->b = 0;

	return false;
}

//==========================================================================
//
//		�F�ݒ�
//
//==========================================================================
void CSurface::SetColor( long x, long y, PIXELDATA32 *pPixel )
{
	if ( (0 <= x) && (x < m_Width) )
	{
		if ( (0 <= y) && (y < m_Height) )
		{
			long Pitch;
			PIXELDATA32 *pDst;
			if ( GetData( &pDst, &Pitch ) )
			{
				pDst[x + (y * Pitch)] = *pPixel;
			}
		}
	}
}

//==========================================================================
/**
	BMP�ۑ�
*/
//==========================================================================
bool CSurface::SaveBMP16( char *pFileName, long SaveHeight )
{
	long Width  = m_Width;
	long Height = m_Height;

	//------------------------------------------------------------
	// �e�N�X�`�������J�b�g�p
	//------------------------------------------------------------
	if ( SaveHeight > 0 )
	{
		for ( Height = 1; Height < SaveHeight; Height <<= 1 );
	}

	//------------------------------------------------------------
	// �p���b�g����
	//------------------------------------------------------------
	CreatePalette( 4 );

	//------------------------------------------------------------
	// �p���b�g�p�T�[�t�F�C�X����
	//------------------------------------------------------------
	CreatePaletteSurface( 4 );

	//------------------------------------------------------------
	// �p���b�g�Đ���
	//------------------------------------------------------------
	CreateBoxPalette( 4 );

	//------------------------------------------------------------
	// �r�b�g�}�b�v�\���̊m��
	//------------------------------------------------------------
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpih;

	bmpfh.bfType			= ('B' << 0) | ('M' << 8);
	bmpfh.bfSize			= sizeof(RGBQUAD[16]) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (Width * Height / 2);
	bmpfh.bfReserved1		= 0;
	bmpfh.bfReserved2		= 0;
	bmpfh.bfOffBits			= sizeof(RGBQUAD[16]) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmpih.biSize			= sizeof(BITMAPINFOHEADER);
	bmpih.biWidth			= Width;
	bmpih.biHeight			= Height;
	bmpih.biPlanes			= 1;
	bmpih.biBitCount		= 4;
	bmpih.biCompression		= BI_RGB;
	bmpih.biSizeImage		= 0;
	bmpih.biXPelsPerMeter	= 0;
	bmpih.biYPelsPerMeter	= 0;
	bmpih.biClrUsed			= 0;
	bmpih.biClrImportant	= 0;

	//------------------------------------------------------------
	// �摜�ۑ�
	//------------------------------------------------------------
	HANDLE hFile = FILE_OPEN_WRITE( pFileName );
	if ( hFile == INVALID_HANDLE_VALUE ) return false;

	// �w�b�_
	FILE_WRITE( hFile, &bmpfh, sizeof(BITMAPFILEHEADER) );
	FILE_WRITE( hFile, &bmpih, sizeof(BITMAPINFOHEADER) );

	// �p���b�g
	FILE_WRITE( hFile, m_pPalette, sizeof(RGBQUAD[16]) );

	// �摜�f�[�^
	long Pitch = Width / 2;
	unsigned char *pSrc = m_pPaletteSurface + ((Height - 1) * Pitch);
	for ( long y = 0; y < Height; y++ )
	{
		FILE_WRITE( hFile, pSrc, Pitch );
		pSrc -= Pitch;
	}

	FILE_CLOSE( hFile );

#if OUTPUT_TGA
	//------------------------------------------------------------
	// �t�@�C���w�b�_
	//------------------------------------------------------------
	TGA_HEADER TgaHeader = { 0 };
	TgaHeader.No_ID			= 0;
	TgaHeader.CMap_Type		= 0;
	TgaHeader.Image_Type	= 2;
	TgaHeader.Ox			= 0;
	TgaHeader.Oy			= 0;
	TgaHeader.Width			= (unsigned short)Width;
	TgaHeader.Hight			= (unsigned short)Height;
	TgaHeader.Pixel			= 32;
	TgaHeader.IDesc_Type	= 0x28;

	//------------------------------------------------------------
	// �ۑ�
	//------------------------------------------------------------
	char File[256];
	sprintf( File, "%s.tga", pFileName );
	hFile = FILE_OPEN_WRITE( File );
	if ( hFile == INVALID_HANDLE_VALUE ) return false;

	// �w�b�_
	FILE_WRITE( hFile, &TgaHeader, sizeof(TGA_HEADER) );

	// �摜�f�[�^
	Width /= 2;
	for ( long y = 0; y < Height; y++ )
	{
		for ( long x = 0; x < Width; x++ )
		{
			FILE_WRITE( hFile, &m_pPalette[(m_pPaletteSurface[x + (y * Width)]>>4)&0x0F], sizeof(RGBQUAD) );
			FILE_WRITE( hFile, &m_pPalette[(m_pPaletteSurface[x + (y * Width)]>>0)&0x0F], sizeof(RGBQUAD) );
		}
	}

	FILE_CLOSE( hFile );
#endif // OUTPUT_TGA

	return true;
}

//==========================================================================
/**
	BMP�ۑ�
*/
//==========================================================================
bool CSurface::SaveBMP256( char *pFileName, long SaveHeight )
{
	long Width  = m_Width;
	long Height = m_Height;

	//------------------------------------------------------------
	// �e�N�X�`�������J�b�g�p
	//------------------------------------------------------------
	if ( SaveHeight > 0 )
	{
		for ( Height = 1; Height < SaveHeight; Height <<= 1 );
	}

	//------------------------------------------------------------
	// �p���b�g����
	//------------------------------------------------------------
	CreatePalette( 8 );

	//------------------------------------------------------------
	// �p���b�g�p�T�[�t�F�C�X����
	//------------------------------------------------------------
	CreatePaletteSurface( 8 );

	//------------------------------------------------------------
	// �p���b�g�Đ���
	//------------------------------------------------------------
	CreateBoxPalette( 8 );

	//------------------------------------------------------------
	// �r�b�g�}�b�v�\���̊m��
	//------------------------------------------------------------
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpih;

	bmpfh.bfType			= ('B' << 0) | ('M' << 8);
	bmpfh.bfSize			= sizeof(RGBQUAD[256]) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (Width * Height);
	bmpfh.bfReserved1		= 0;
	bmpfh.bfReserved2		= 0;
	bmpfh.bfOffBits			= sizeof(RGBQUAD[256]) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmpih.biSize			= sizeof(BITMAPINFOHEADER);
	bmpih.biWidth			= Width;
	bmpih.biHeight			= Height;
	bmpih.biPlanes			= 1;
	bmpih.biBitCount		= 8;
	bmpih.biCompression		= BI_RGB;
	bmpih.biSizeImage		= 0;
	bmpih.biXPelsPerMeter	= 0;
	bmpih.biYPelsPerMeter	= 0;
	bmpih.biClrUsed			= 0;
	bmpih.biClrImportant	= 0;

	//------------------------------------------------------------
	// �摜�ۑ�
	//------------------------------------------------------------
	HANDLE hFile = FILE_OPEN_WRITE( pFileName );
	if ( hFile == INVALID_HANDLE_VALUE ) return false;

	// �w�b�_
	FILE_WRITE( hFile, &bmpfh, sizeof(BITMAPFILEHEADER) );
	FILE_WRITE( hFile, &bmpih, sizeof(BITMAPINFOHEADER) );

	// �p���b�g
	FILE_WRITE( hFile, m_pPalette, sizeof(RGBQUAD[256]) );

	// �摜�f�[�^
	unsigned char *pSrc = m_pPaletteSurface + ((Height - 1) * Width);
	for ( long y = 0; y < Height; y++ )
	{
		FILE_WRITE( hFile, pSrc, Width );
		pSrc -= Width;
	}

	FILE_CLOSE( hFile );

#if OUTPUT_TGA
	//------------------------------------------------------------
	// �t�@�C���w�b�_
	//------------------------------------------------------------
	TGA_HEADER TgaHeader = { 0 };
	TgaHeader.No_ID			= 0;
	TgaHeader.CMap_Type		= 0;
	TgaHeader.Image_Type	= 2;
	TgaHeader.Ox			= 0;
	TgaHeader.Oy			= 0;
	TgaHeader.Width			= (unsigned short)Width;
	TgaHeader.Hight			= (unsigned short)Height;
	TgaHeader.Pixel			= 32;
	TgaHeader.IDesc_Type	= 0x28;

	//------------------------------------------------------------
	// �ۑ�
	//------------------------------------------------------------
	char File[256];
	sprintf( File, "%s.tga", pFileName );
	hFile = FILE_OPEN_WRITE( File );
	if ( hFile == INVALID_HANDLE_VALUE ) return false;

	// �w�b�_
	FILE_WRITE( hFile, &TgaHeader, sizeof(TGA_HEADER) );

	// �摜�f�[�^
	for ( long y = 0; y < Height; y++ )
	{
		for ( long x = 0; x < Width; x++ )
		{
			FILE_WRITE( hFile, &m_pPalette[m_pPaletteSurface[x + (y * Width)]], sizeof(RGBQUAD) );
		}
	}

	FILE_CLOSE( hFile );
#endif // OUTPUT_TGA

	return true;
}

//==========================================================================
/**
	TGA�ۑ�
*/
//==========================================================================
bool CSurface::SaveTGA( char *pFileName, long SaveHeight )
{
	long Width  = m_Width;
	long Height = m_Height;

	//------------------------------------------------------------
	// �e�N�X�`�������J�b�g�p
	//------------------------------------------------------------
	if ( SaveHeight > 0 )
	{
		for ( Height = 1; Height < SaveHeight; Height <<= 1 );
	}

	//------------------------------------------------------------
	// �t�@�C���w�b�_
	//------------------------------------------------------------
	TGA_HEADER TgaHeader = { 0 };
	TgaHeader.No_ID			= 0;
	TgaHeader.CMap_Type		= 0;
	TgaHeader.Image_Type	= 2;
	TgaHeader.Ox			= 0;
	TgaHeader.Oy			= 0;
	TgaHeader.Width			= (unsigned short)Width;
	TgaHeader.Hight			= (unsigned short)Height;
	TgaHeader.Pixel			= 32;
	TgaHeader.IDesc_Type	= 0x28;

	//------------------------------------------------------------
	// �ۑ�
	//------------------------------------------------------------
	HANDLE hFile = FILE_OPEN_WRITE( pFileName );
	if ( hFile == INVALID_HANDLE_VALUE ) return false;

	// �w�b�_
	FILE_WRITE( hFile, &TgaHeader, sizeof(TGA_HEADER) );

	// �摜�f�[�^
	long Cnt = 0;
	for ( long y = 0; y < Height; y++ )
	{
//		unsigned long Color = (y % 48) / 24 ? 0xFFAAAAAA : 0xFFDDDDDD;
		unsigned long Color = 0x00808080;
		for ( long x = 0; x < Width; x++ )
		{
			if ( m_pPixel[Cnt].a == 0 )
			{
				FILE_WRITE( hFile, &Color, sizeof(unsigned long) );
			}
			else
			{
				FILE_WRITE( hFile, &m_pPixel[Cnt], sizeof(unsigned long) );
			}
			Cnt++;
		}
	}

	FILE_CLOSE( hFile );

	return true;
}

//==========================================================================
/**
	�p���b�g����
*/
//==========================================================================
void CSurface::CreateBoxPalette( long Bit )
{
	for ( long i = 0; i < (1 << Bit); i++ )
	{
		m_pPalette[i] = m_pColorBox[i].Color;
	}
}

//==========================================================================
/**
	�p���b�g����
*/
//==========================================================================
void CSurface::ReleasePalette( void )
{
	SAFE_FREE( m_pColorBox );
	SAFE_FREE( m_pPalette );
	SAFE_FREE( m_pPaletteSurface );
	SAFE_FREE( m_pPaletteUseCount );

	m_PaletteCount = 0;
}

//==========================================================================
/**
	�p���b�g�T�[�t�F�C�X����
*/
//==========================================================================
void CSurface::CreatePaletteSurface( long Color )
{
	PIXELDATA32 *pSrc;
	long Pitch;

	if ( GetData( &pSrc, &Pitch ) )
	{
		long Height = m_Height;
		long Width  = m_Width;

		unsigned char *pDst = (unsigned char *)SAFE_ALLOC( Height * Pitch / (8 / Color) );
		m_pPaletteSurface = pDst;

		switch ( Color )
		{
		case 4:
			for ( long y = 0; y < Height; y++ )
			{
				for ( long x = 0; x < Width; x += 2 )
				{
					*pDst = 0x00;

					*pDst |= (unsigned char)(SearchNearPalette( *pSrc, 4 ) << 4);
					pSrc++;
					*pDst |= (unsigned char)(SearchNearPalette( *pSrc, 4 ) << 0);
					pSrc++;

					pDst++;
				}
			}
			break;

		case 8:
			for ( long y = 0; y < Height; y++ )
			{
				for ( long x = 0; x < Width; x++ )
				{
					*pDst = (unsigned char)SearchNearPalette( *pSrc, 8 );
					pDst++;
					pSrc++;
				}
			}
			break;
		}
	}
}

//==========================================================================
/**
	�p���b�g���ёւ�
*/
//==========================================================================
void CSurface::SwapPalette( long No1, long No2 )
{
	long Temp = m_pPaletteUseCount[No1];
	m_pPaletteUseCount[No1] = m_pPaletteUseCount[No2];
	m_pPaletteUseCount[No2] = Temp;

	RGBQUAD TempQuad = m_pPalette[No1];
	m_pPalette[No1] = m_pPalette[No2];
	m_pPalette[No2] = TempQuad;
}

//==========================================================================
/**
	�p���b�g����
*/
//==========================================================================
long CSurface::SearchNearPalette( PIXELDATA32 Pix, long Bit )
{
	long box_count = (Bit == 4) ? (16) : (256);

	long index = SearchPalette( Pix );
	for ( long i = 0; i < box_count; i++ )
	{
		if ( m_pColorBox[i].Start <= index )
		{
			if ( index < m_pColorBox[i].Start + m_pColorBox[i].Count )
			{
				return i;
			}
		}
	}

	return (1 << Bit) - 1;
}

//==========================================================================
/**
	�p���b�g����
*/
//==========================================================================
void CSurface::CreatePalette( long Bit )
{
	PIXELDATA32 Null = { 0x00, 0xFF, 0x00, 0x00 };
	PIXELDATA32 *pSrc;
	long Pitch;

	if ( GetData( &pSrc, &Pitch ) )
	{
		ReleasePalette();

		m_pPalette			= (RGBQUAD*)SAFE_ALLOC( sizeof(RGBQUAD) * Pitch * m_Height );
		m_pPaletteUseCount	= (long*)SAFE_ALLOC( sizeof(long) * Pitch * m_Height );
		m_PaletteCount		= 0;

		long Size = Pitch * m_Height;
		while ( Size-- != 0 )
		{
			pSrc[Size].a = (unsigned char)(((((long)pSrc[Size].a * Bit) / 255) * 255) / Bit);
			if ( pSrc[Size].a == 0 )
			{
				pSrc[Size] = Null;
			}
			AddPalette( pSrc[Size] );
		}

		// �p���b�g�{�b�N�X�쐬
		CreatePaletteBox( Bit );
	}
}

//==========================================================================
/**
	�p���b�g���擾
*/
//==========================================================================
long CSurface::GetPaletteCount( long start, long count )
{
	long palette_count = 0;

	for ( long i = start; i < start + count; i++ )
	{
		palette_count += m_pPaletteUseCount[i];
	}

	return palette_count;
}

//==========================================================================
/**
	�p���b�g�{�b�N�X�쐬
*/
//==========================================================================
void CSurface::CreatePaletteBox( long Bit )
{
	long box_count = (Bit == 4) ? (16) : (256);
	long palette_max = m_PaletteCount;

	//----------------------------------------------------------------------------------------
	// �{�b�N�X�쐬
	//----------------------------------------------------------------------------------------
	m_pColorBox = (COLORBOX*)SAFE_ALLOC( sizeof(COLORBOX) * box_count );

	m_pColorBox[0].Start = 0;
	m_pColorBox[0].Count = palette_max;
	m_pColorBox[0].Pixels = GetPaletteCount( 0, palette_max );
	long color_box_count = 1;

	//----------------------------------------------------------------------------------------
	// �{�b�N�X��������
	//----------------------------------------------------------------------------------------
	while ( color_box_count < box_count )
	{
		long max = color_box_count;
		long no = -1;
		long count = 1;

		//--------------------------------------------------------------
		// ��ԉ�f���̑����{�b�N�X�����߂�
		//--------------------------------------------------------------
		for ( long i = 0; i < max; i++ )
		{
			if ( (count < m_pColorBox[i].Pixels) && (m_pColorBox[i].Count > 1) )
			{
				count = m_pColorBox[i].Pixels;
				no = i;
			}
		}

		if ( no == -1 ) break;

		//--------------------------------------------------------------
		// ��ԕӂ̒����F�����߂�
		//--------------------------------------------------------------
		long r[] = { 0xFF, 0x00, 0x00 };
		long g[] = { 0xFF, 0x00, 0x00 };
		long b[] = { 0xFF, 0x00, 0x00 };
		long a[] = { 0xFF, 0x00, 0x00 };
		long start = m_pColorBox[no].Start;
		long end   = m_pColorBox[no].Start + m_pColorBox[no].Count;
		for ( long i = start; i < end; i++ )
		{
			// �ŏ�
			if ( r[0] > m_pPalette[i].rgbRed      ) r[0] = m_pPalette[i].rgbRed;
			if ( g[0] > m_pPalette[i].rgbGreen    ) g[0] = m_pPalette[i].rgbGreen;
			if ( b[0] > m_pPalette[i].rgbBlue     ) b[0] = m_pPalette[i].rgbBlue;
			if ( a[0] > m_pPalette[i].rgbReserved ) a[0] = m_pPalette[i].rgbReserved;
			// �ő�
			if ( r[1] < m_pPalette[i].rgbRed      ) r[1] = m_pPalette[i].rgbRed;
			if ( g[1] < m_pPalette[i].rgbGreen    ) g[1] = m_pPalette[i].rgbGreen;
			if ( b[1] < m_pPalette[i].rgbBlue     ) b[1] = m_pPalette[i].rgbBlue;
			if ( a[1] < m_pPalette[i].rgbReserved ) a[1] = m_pPalette[i].rgbReserved;
		}

		// ��
		r[2] = r[1] - r[0];
		g[2] = g[1] - g[0];
		b[2] = b[1] - b[0];
		a[2] = a[1] - a[0];

		if ( (b[2] >= g[2]) && (b[2] >= r[2]) && (b[2] >= a[2]) ) PaletteSortB( m_pColorBox[no].Start, m_pColorBox[no].Count );
		if ( (g[2] >= r[2]) && (g[2] >= b[2]) && (g[2] >= a[2]) ) PaletteSortG( m_pColorBox[no].Start, m_pColorBox[no].Count );
		if ( (r[2] >= b[2]) && (r[2] >= g[2]) && (r[2] >= a[2]) ) PaletteSortR( m_pColorBox[no].Start, m_pColorBox[no].Count );
		if ( (a[2] >= r[2]) && (a[2] >= g[2]) && (a[2] >= b[2]) ) PaletteSortA( m_pColorBox[no].Start, m_pColorBox[no].Count );

		//--------------------------------------------------------------
		// �{�b�N�X�𕪊�
		//--------------------------------------------------------------
		long pixel_max = m_pColorBox[no].Pixels;
		long pixel_count = m_pPaletteUseCount[0];
		long palette_no = m_pColorBox[no].Start + 1;
		long palette_end = m_pColorBox[no].Start + m_pColorBox[no].Count;
		while ( palette_no < palette_end - 1 )
		{
			if ( pixel_count >= pixel_max / 2 ) break;

			pixel_count += m_pPaletteUseCount[palette_no];
			palette_no++;
		}

		m_pColorBox[no].Count = palette_no - m_pColorBox[no].Start;
		m_pColorBox[max].Start = m_pColorBox[no].Start + m_pColorBox[no].Count;
		m_pColorBox[max].Count = palette_end - (m_pColorBox[no].Start + m_pColorBox[no].Count);

		m_pColorBox[no].Pixels = GetPaletteCount( m_pColorBox[no].Start, m_pColorBox[no].Count );
		m_pColorBox[max].Pixels = GetPaletteCount( m_pColorBox[max].Start, m_pColorBox[max].Count );

		color_box_count++;
	}

	//----------------------------------------------------------------------------------------
	// �{�b�N�X���̕��ϐF���Z�o
	//----------------------------------------------------------------------------------------
	for ( long i = 0; i < box_count; i++ )
	{
		long r = 0, g = 0, b = 0, a = 0;
		long start = m_pColorBox[i].Start;
		long end   = m_pColorBox[i].Start + m_pColorBox[i].Count;
		for ( long j = start; j < end; j++ )
		{
			long cnt = m_pPaletteUseCount[j];
			r += m_pPalette[j].rgbRed      * cnt;
			g += m_pPalette[j].rgbGreen    * cnt;
			b += m_pPalette[j].rgbBlue     * cnt;
			a += m_pPalette[j].rgbReserved * cnt;
		}

		if ( m_pColorBox[i].Pixels > 0 )
		{
			m_pColorBox[i].Color.rgbRed      = (unsigned char)(r / m_pColorBox[i].Pixels);
			m_pColorBox[i].Color.rgbGreen    = (unsigned char)(g / m_pColorBox[i].Pixels);
			m_pColorBox[i].Color.rgbBlue     = (unsigned char)(b / m_pColorBox[i].Pixels);
			m_pColorBox[i].Color.rgbReserved = (unsigned char)(a / m_pColorBox[i].Pixels);
		}
	}
}

//==========================================================================
/**
	�p���b�g�\�[�g
*/
//==========================================================================
void CSurface::PaletteSortR( long start, long count )
{
	RGBQUAD *pPal = &m_pPalette[start];
	for ( long i = 0; i < count; i++ )
	{
		for ( long j = i; j < count; j++ )
		{
			if ( pPal[i].rgbRed < pPal[j].rgbRed )
			{
				SwapPalette( start + i, start + j );
			}
		}
	}
}

//==========================================================================
/**
	�p���b�g�\�[�g
*/
//==========================================================================
void CSurface::PaletteSortG( long start, long count )
{
	RGBQUAD *pPal = &m_pPalette[start];
	for ( long i = 0; i < count; i++ )
	{
		for ( long j = i; j < count; j++ )
		{
			if ( pPal[i].rgbGreen < pPal[j].rgbGreen )
			{
				SwapPalette( start + i, start + j );
			}
		}
	}
}

//==========================================================================
/**
	�p���b�g�\�[�g
*/
//==========================================================================
void CSurface::PaletteSortB( long start, long count )
{
	RGBQUAD *pPal = &m_pPalette[start];
	for ( long i = 0; i < count; i++ )
	{
		for ( long j = i; j < count; j++ )
		{
			if ( pPal[i].rgbBlue < pPal[j].rgbBlue )
			{
				SwapPalette( start + i, start + j );
			}
		}
	}
}

//==========================================================================
/**
	�p���b�g�\�[�g
*/
//==========================================================================
void CSurface::PaletteSortA( long start, long count )
{
	RGBQUAD *pPal = &m_pPalette[start];
	for ( long i = 0; i < count; i++ )
	{
		for ( long j = i; j < count; j++ )
		{
			if ( pPal[i].rgbReserved < pPal[j].rgbReserved )
			{
				SwapPalette( start + i, start + j );
			}
		}
	}
}

//==========================================================================
/**
	�p���b�g�ǉ�
*/
//==========================================================================
void CSurface::AddPalette( PIXELDATA32 Pix )
{
	long No = SearchPalette( Pix );
	if ( No == -1 )
	{
		CopyMemory( &m_pPalette[m_PaletteCount], &Pix, sizeof(PIXELDATA32) );
		m_pPaletteUseCount[m_PaletteCount] = 1;
		m_PaletteCount++;
	}
	else
	{
		m_pPaletteUseCount[No]++;
	}
}

//==========================================================================
/**
	�p���b�g����
*/
//==========================================================================
long CSurface::SearchPalette( PIXELDATA32 Pix )
{
	unsigned long Src = *((unsigned long*)&Pix);
	unsigned long *pDst = (unsigned long *)m_pPalette;

	long Cnt = m_PaletteCount;
	for ( long i = 0; i < Cnt; i++ )
	{
		if ( Src == pDst[i] )
		{
			return i;
		}
	}

	return -1;
}
