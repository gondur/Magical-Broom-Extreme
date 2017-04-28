
#ifndef ___LUE_VECTOR3D_H___
#define ___LUE_VECTOR3D_H___


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

	�l���x�N�g���ɐݒ肵�A���̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Set( float fPx, float fPy, float fPz );

/**
	@brief �x�N�g�����m�̉��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Add( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g�����m�̌��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Sub( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
float LueVector3D_LengthSq( LueVector3D In );

/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
float LueVector3D_Length( LueVector3D In );

/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B
*/
LueVector3D LueVector3D_Normalize( LueVector3D In );

/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B
*/
float LueVector3D_DotProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B
*/
LueVector3D LueVector3D_CrossProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̔��˂��擾
	@author �t���`

	@param In1	[in] ���˃x�N�g��
	@param In2	[in] ���ˎ��x�N�g��

	@return ���ˌ�̃x�N�g��

	���˃x�N�g���𔽎ˎ��x�N�g����@��Ƃ��镽�ʂŔ��˂�������<BR>
	���ˌ�̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Reflect( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̉�]�g�k�ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���ϊ����s���܂��B
*/
LueVector3D LueVector3D_TransformNormal( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ��ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��ϊ����s���܂��B
*/
LueVector3D LueVector3D_TransformCoord( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ������ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��E�����ϊ����s���܂��B<BR>
	���Z���w�l���ق����ꍇ�� LueVector4D_TransformProjection �g���Ă��������B
*/
LueVector3D LueVector3D_TransformProjection( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g����X����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����X���ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationX( LueVector3D In, int Angle );

/**
	@brief �x�N�g����Y����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Y���ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationY( LueVector3D In, int Angle );

/**
	@brief �x�N�g����Z����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Z���ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationZ( LueVector3D In, int Angle );

/**
	@brief �x�N�g���̔C�ӎ���]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x
	@param Axis		[in] ��]�̊��

	@return �ϊ���̃x�N�g��

	�x�N�g����C�ӂ̎��ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationAxis( LueVector3D In, int Angle, LueVector3D Axis );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_VECTOR3D_H___

