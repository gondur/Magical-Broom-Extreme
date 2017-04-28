

#ifndef ___LUE_VECTOR4D_H___
#define ___LUE_VECTOR4D_H___


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
	@param fPz	[in] z�l

	@return �l�ݒ��̃x�N�g��

	�l���x�N�g���ɐݒ肵�A���̃x�N�g�����擾���܂��B<BR>
	w�l��1.0f�ŏ���������Ă��܂��B
*/
LueVector4D LueVector4D_Set( float fPx, float fPy, float fPz );

/**
	@brief �x�N�g�����m�̉��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B<BR>
	������w�l��1.0f���ݒ肳��Ă��܂��B
*/
LueVector4D LueVector4D_Add( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g�����m�̌��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B<BR>
	������w�l��1.0f���ݒ肳��Ă��܂��B
*/
LueVector4D LueVector4D_Sub( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
float LueVector4D_LengthSq( LueVector4D In );

/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
float LueVector4D_Length( LueVector4D In );

/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_Normalize( LueVector4D In );

/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
float LueVector4D_DotProduct( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_CrossProduct( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̔��˂��擾
	@author �t���`

	@param In1	[in] ���˃x�N�g��
	@param In2	[in] ���ˎ��x�N�g��

	@return ���ˌ�̃x�N�g��

	���˃x�N�g���𔽎ˎ��x�N�g����@��Ƃ��镽�ʂŔ��˂�������<BR>
	���ˌ�̃x�N�g�����擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_Reflect( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̉�]�g�k�ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���ϊ����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_TransformNormal( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ��ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��ϊ����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_TransformCoord( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ������ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��E�����ϊ����s���܂��B
*/
LueVector4D LueVector4D_TransformProjection( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g����X����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����X���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationX( LueVector4D In, int Angle );

/**
	@brief �x�N�g����Y����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Y���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationY( LueVector4D In, int Angle );

/**
	@brief �x�N�g����Z����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Z���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationZ( LueVector4D In, int Angle );

/**
	@brief �x�N�g���̔C�ӎ���]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x
	@param Axis		[in] ��]�̊��

	@return �ϊ���̃x�N�g��

	�x�N�g����C�ӂ̎��ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationAxis( LueVector4D In, int Angle, LueVector3D Axis );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_VECTOR4D_H___



