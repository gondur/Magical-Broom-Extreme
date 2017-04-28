

#ifndef ___SELENE__LOCAL___
#define ___SELENE__LOCAL___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	void MBCStoWCS( const char *pSrc, wchar_t *pDst );
	void WCStoMBCS( const wchar_t *pSrc, char *pDst );

	wchar_t *GetSocketError( Sint32 ErrorCode, wchar_t *pErrStr = NULL, Uint32 ErrStrSize = 0 );
	wchar_t *GetPixelFormat( D3DFORMAT Format, wchar_t *pErrStr = NULL, Uint32 ErrStrSize = 0 );
	wchar_t *GetD3DError( HRESULT hr, wchar_t *pErrStr = NULL, Uint32 ErrStrSize = 0 );

	void Log_Initialize( const wchar_t *pDir );
	void Log_Finalize( void );
	void Log_Print( Uint32 Color, const wchar_t *pStr,... );
	void Log_PrintStrong( Uint32 Color, const wchar_t *pStr,... );
	void Log_PrintLine( Uint32 Color, const wchar_t *pStr,... );
	void Log_PrintStrongLine( Uint32 Color, const wchar_t *pStr,... );
	void Log_PrintTable( Uint32 Width, const wchar_t *pTitle, const wchar_t *pStr,... );
	void Log_PrintTable( Uint32 ColorTitle, Uint32 Color, const wchar_t *pTitle, const wchar_t *pKind, const wchar_t *pStr,... );
	void Log_PrintCellTitle( Uint32 Color, const wchar_t *pTitle );
	void Log_PrintCellKind( const wchar_t *pKind,... );
	void Log_TableBegin( void );
	void Log_TableEnd( void );
	void Log_TableLine( Uint32 Bold );
	void Log_CellBegin( Uint32 Width );
	void Log_CellEnd( void );

	void SetWindowCenter( HWND hWnd, HWND hWndParent );

	void GetLongFullPathName( const wchar_t *pSrcPath, wchar_t *pDstPath, Uint32 DstPathSize );
	Bool GetDesktopDirectory( wchar_t *pPath, Uint32 PathSize );

	void CopyToUpper( wchar_t *pDst, const wchar_t *pSrc );
}


#endif // ___SELENE__LOCAL___

