
#ifndef ___LUE_MATH_H___
#define ___LUE_MATH_H___


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
	@brief sin値を取得する
	@author 葉迩倭

	@param Angle	[in] 1周65536とした角度

	@return sin値

	sinの値を取得します。
*/
float LueMath_Sin( int Angle );

/**
	@brief cos値を取得する
	@author 葉迩倭

	@param Angle	[in] 1周65536とした角度

	@return cos値

	cosの値を取得します。
*/
float LueMath_Cos( int Angle );

/**
	@brief atan2値を取得する
	@author 葉迩倭

	@param fPx	[in] arc tangent 計算用のx値
	@param fPy	[in] arc tangent 計算用のy値

	@return sin値

	arc tangent の値を取得します。
*/
int LueMath_ATan2( float fPx, float fPy );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_MATH_H___
