
#pragma once


//==========================================================================
// INCLUDE
//==========================================================================
#include "Base.h"
#include "Surface.h"


//==========================================================================
// ENUM
//==========================================================================
enum eFileFormat
{
	FF_BMP_16,
	FF_BMP_256,
	FF_TGA,
};


//==========================================================================
// PROTOTYPE
//==========================================================================
bool DxInitialize( HWND hWnd );
void DxFinalize( void );
void DxUpdateBackBuffer( CSurface *pSurf );
void DxRefreshBackBuffer( HWND hWnd );
char *DxGetError( HRESULT hr );

