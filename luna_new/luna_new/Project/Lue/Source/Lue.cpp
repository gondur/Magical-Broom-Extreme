

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"


//------------------------------------------------------------------------------------------------
// LIB
//------------------------------------------------------------------------------------------------
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "msacm32.lib" )

#ifdef _DEBUG
#	pragma comment( lib, "../../Selene/Project/Lib/Ayame_debug.lib" )
#	pragma comment( lib, "../../Selene/Project/Lib/vorbisfile_static_debug.lib" )
#	pragma comment( lib, "../../Selene/Project/Lib/vorbis_static_debug.lib" )
#	pragma comment( lib, "../../Selene/Project/Lib/ogg_static_debug.lib" )
#else // _DEBUG
#	ifdef ENABLE_SSE
#		pragma comment( lib, "../../Selene/Project/Lib/Ayame_SSE.lib" )
#		pragma comment( lib, "../../Selene/Project/Lib/vorbisfile_static_sse.lib" )
#		pragma comment( lib, "../../Selene/Project/Lib/vorbis_static_sse.lib" )
#		pragma comment( lib, "../../Selene/Project/Lib/ogg_static_sse.lib" )
#	else // ENABLE_SSE
#		pragma comment( lib, "../../Selene/Project/Lib/Ayame.lib" )
#		pragma comment( lib, "../../Selene/Project/Lib/vorbisfile_static.lib" )
#		pragma comment( lib, "../../Selene/Project/Lib/vorbis_static.lib" )
#		pragma comment( lib, "../../Selene/Project/Lib/ogg_static.lib" )
#	endif // ENABLE_SSE
#endif // _DEBUG


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
HINSTANCE g_hInstanceDLL = NULL;


//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
int APIENTRY DllMain( HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved )
{
	g_hInstanceDLL = hModule;

	return TRUE;
}

//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
HINSTANCE GetDLLInstance( void )
{
	return g_hInstanceDLL;
}

//------------------------------------------------------------------------------------------------
/**
*/
//------------------------------------------------------------------------------------------------
void MBCStoWCS( const char *pSrc, wchar_t *pDst )
{
	size_t Len = ::MultiByteToWideChar( CP_ACP, 0, pSrc, -1, NULL ,0 );
	MultiByteToWideChar( CP_ACP, 0, pSrc, -1, pDst, (Sint32)Len );
}


} // extern "C"

