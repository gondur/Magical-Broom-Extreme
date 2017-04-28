
#pragma once


//==========================================================================
// INCLUDE
//==========================================================================
#include "Base.h"


//==========================================================================
// STRUCT
//==========================================================================
typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
}
PIXELDATA32;

typedef struct
{
	long Start;
	long Count;
	long Pixels;

	RGBQUAD Color;
}
COLORBOX;


//==========================================================================
// CLASS
//==========================================================================
typedef class CSurface
{
private:
	PIXELDATA32 *m_pPixel;
	long m_Width;
	long m_Height;

	COLORBOX *m_pColorBox;

	unsigned char *m_pPaletteSurface;
	RGBQUAD *m_pPalette;
	long *m_pPaletteUseCount;
	long m_PaletteCount;

	void CreatePalette( long Bit );
	void AddPalette( PIXELDATA32 Pix );
	long SearchPalette( PIXELDATA32 Pix );
	void ReleasePalette( void );
	void CreatePaletteSurface( long Color );
	void SwapPalette( long No1, long No2 );
	long SearchNearPalette( PIXELDATA32 Pix, long Bit );
	void CreatePaletteBox( long Bit );
	void PaletteSortR( long start, long count );
	void PaletteSortG( long start, long count );
	void PaletteSortB( long start, long count );
	void PaletteSortA( long start, long count );
	long GetPaletteCount( long start, long count );
	void CreateBoxPalette( long Bit );

public:
	CSurface();
	virtual ~CSurface();

	bool IsInvalid( void );

	bool GetData( PIXELDATA32 **ppAddr, long *pPitch );

	bool LoadBMP( char *pFileName );
	bool Create( long Width, long Height );
	void Create( CSurface *pSurf );
	void Release( void );

	bool SaveBMP16( char *pFileName, long SaveHeight );
	bool SaveBMP256( char *pFileName, long SaveHeight );
	bool SaveTGA( char *pFileName, long SaveHeight );

	long GetWidth( void );
	long GetHeight( void );

	void Clear( void );
	void Clear( PIXELDATA32 Color );

	void DirectDraw( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h );

	void ColorDraw( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h, PIXELDATA32 Pixel );
	void ColorDrawNoAlpha( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h, PIXELDATA32 Pixel );

	void Draw( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h );
	void DrawNoAlpha( long x, long y, CSurface *pSurf, long src_x, long src_y, long src_w, long src_h );

	bool GetColor( long x, long y, PIXELDATA32 *pPixel );
	void SetColor( long x, long y, PIXELDATA32 *pPixel );
}
CSurface, *LPCSurface;

