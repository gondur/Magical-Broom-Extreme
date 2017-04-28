
#ifndef ___LUE_SURFACE_H___
#define ___LUE_SURFACE_H___


//=============================================================================
// INCLUDE
//=============================================================================
#include "LueBase.h"


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//=============================================================================
// PROTOTYPE
//=============================================================================
/**
	@brief サーフェイスの解放
	@author 葉迩倭

	@param Handle	[in] サーフェイスハンドル

	サーフェイスの解放を行います。
*/
void LueSurface_Release( LUE_HANDLE Handle );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_SURFACE_H___
