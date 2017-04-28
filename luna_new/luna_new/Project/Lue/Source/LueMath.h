
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
	@brief sin�l���擾����
	@author �t���`

	@param Angle	[in] 1��65536�Ƃ����p�x

	@return sin�l

	sin�̒l���擾���܂��B
*/
float LueMath_Sin( int Angle );

/**
	@brief cos�l���擾����
	@author �t���`

	@param Angle	[in] 1��65536�Ƃ����p�x

	@return cos�l

	cos�̒l���擾���܂��B
*/
float LueMath_Cos( int Angle );

/**
	@brief atan2�l���擾����
	@author �t���`

	@param fPx	[in] arc tangent �v�Z�p��x�l
	@param fPy	[in] arc tangent �v�Z�p��y�l

	@return sin�l

	arc tangent �̒l���擾���܂��B
*/
int LueMath_ATan2( float fPx, float fPy );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_MATH_H___
