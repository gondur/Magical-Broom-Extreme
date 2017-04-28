
#ifndef ___LUE_VECTOR2D_H___
#define ___LUE_VECTOR2D_H___


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
	@brief �x�N�g���ɒl��ݒ�
	@author �t���`

	@param fPx	[in] x�l
	@param fPy	[in] y�l

	@return �l�ݒ��̃x�N�g��

	�l���x�N�g���ɐݒ肵�A���̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Set( float fPx, float fPy );

/**
	@brief �x�N�g�����m�̉��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Add( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g�����m�̌��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Sub( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
float LueVector2D_LengthSq( LueVector2D In );

/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
float LueVector2D_Length( LueVector2D In );

/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B
*/
LueVector2D LueVector2D_Normalize( LueVector2D In );

/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B
*/
float LueVector2D_DotProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B
*/
float LueVector2D_CrossProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g���̔��˂��擾
	@author �t���`

	@param In1	[in] ���˃x�N�g��
	@param In2	[in] ���ˎ��x�N�g��

	@return ���ˌ�̃x�N�g��

	���˃x�N�g���𔽎ˎ��x�N�g����@��Ƃ��镽�ʂŔ��˂�������<BR>
	���ˌ�̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Reflect( LueVector2D In1, LueVector2D In2 );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_VECTOR2D_H___

