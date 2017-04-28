
#pragma once


//==========================================================================
// INCLUDE
//==========================================================================
#include "Base.h"
#include "Surface.h"
#include "StrBuffer.h"


//==========================================================================
// STRUCT
//==========================================================================
typedef struct _FONTDATA
{
	char Face[256];
	BOOL IsBold;
	BOOL IsEdge;
	BOOL IsBevel;
	BOOL IsItalic;
	BOOL IsFixPitch;
	long EdgeSize;
	long BevelSize;
	long FontSize;
	long BevelDir;
	long SamplingCount;
	float fAspectX;
	float fAspectY;

	COLORREF FontColor;
	COLORREF BevelColor;
	COLORREF EdgeColor;

	TEXTMETRIC TextMetric;
	ABC abc;
	long PosY;
	HFONT hFont, hFontOld;
	HDC hDC;
}
FONTDATA, *LPFONTDATA;


//==========================================================================
// PROTOTYPE
//==========================================================================
void DrawFont( HWND hWnd, CSurface *pDst, FONTDATA *pFont, char *str );
void FilterAntialias( CSurface *pDst, FONTDATA *pFont );

