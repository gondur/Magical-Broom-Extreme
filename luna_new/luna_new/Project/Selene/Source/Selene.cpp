
//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH


//-----------------------------------------------------------------------------------
// LIB
//-----------------------------------------------------------------------------------
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "msacm32.lib" )

#ifndef LIB_SELENE
#ifdef _DEBUG
#pragma comment( lib, "Lib/Ayame_debug.lib" )
#pragma comment( lib, "Lib/vorbisfile_static_debug.lib" )
#pragma comment( lib, "Lib/vorbis_static_debug.lib" )
#pragma comment( lib, "Lib/ogg_static_debug.lib" )
#else // _DEBUG
#ifdef ENABLE_SSE
#pragma comment( lib, "Lib/Ayame_SSE.lib" )
#pragma comment( lib, "Lib/vorbisfile_static_sse.lib" )
#pragma comment( lib, "Lib/vorbis_static_sse.lib" )
#pragma comment( lib, "Lib/ogg_static_sse.lib" )
#else // ENABLE_SSE
#pragma comment( lib, "Lib/Ayame.lib" )
#pragma comment( lib, "Lib/vorbisfile_static.lib" )
#pragma comment( lib, "Lib/vorbis_static.lib" )
#pragma comment( lib, "Lib/ogg_static.lib" )
#endif // ENABLE_SSE
#endif // _DEBUG
#endif // LIB_SELENE


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
#ifndef LIB_SELENE
long APIENTRY DllMain( HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved )
{
	return TRUE;
}
#endif // LIB_SELENE

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void GetVersioinInfo( wchar_t *pVersionStr, Uint32 Length )
{
	::StringCbCopy( pVersionStr, Length, L"Selene - Phase 0.01 - 2007.11.24.A" );
}
