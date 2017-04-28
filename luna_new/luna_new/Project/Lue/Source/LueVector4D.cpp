
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueVector4D.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Set( float fPx, float fPy, float fPz )
{
	LueVector4D vOut = { fPx, fPy, fPz, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Add( LueVector4D In1, LueVector4D In2 )
{
	LueVector4D vOut = { In1.x + In2.x, In1.y + In2.z, In1.z + In2.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Sub( LueVector4D In1, LueVector4D In2 )
{
	LueVector4D vOut = { In1.x - In2.x, In1.y - In2.z, In1.z - In2.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
//------------------------------------------------------------------------------------------------
float LueVector4D_LengthSq( LueVector4D In )
{
	CVector4D v( In.x, In.y, In.z );
	return v.LengthSq();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
//------------------------------------------------------------------------------------------------
float LueVector4D_Length( LueVector4D In )
{
	CVector4D v( In.x, In.y, In.z );
	return v.Length();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Normalize( LueVector4D In )
{
	CVector4D v( In.x, In.y, In.z );
	v.Normalize();

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
float LueVector4D_DotProduct( LueVector4D In1, LueVector4D In2 )
{
	CVector4D v1( In1.x, In1.y, In1.z );
	CVector4D v2( In2.x, In2.y, In2.z );
	return v1.Dot( v2 );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_CrossProduct( LueVector4D In1, LueVector4D In2 )
{
	CVector4D v1( In1.x, In1.y, In1.z );
	CVector4D v2( In2.x, In2.y, In2.z );
	CVector4D v3;

	v3.Cross( v1, v2 );

	LueVector4D vOut = { v3.x, v3.y, v3.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_Reflect( LueVector4D In1, LueVector4D In2 )
{
	CVector4D v1( In1.x, In1.y, In1.z );
	CVector4D v2( In2.x, In2.y, In2.z );
	CVector4D v3;

	v3.Reflect( v1, v2 );

	LueVector4D vOut = { v3.x, v3.y, v3.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̉�]�g�k�ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���ϊ����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_TransformNormal( LueVector4D In1, LueMatrix4x4 In2 )
{
	CVector4D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformNormal( m );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̉�]�g�k�ړ��ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��ϊ����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_TransformCoord( LueVector4D In1, LueMatrix4x4 In2 )
{
	CVector4D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformCoord( m );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g���̉�]�g�k�ړ������ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��E�����ϊ����s���܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_TransformProjection( LueVector4D In1, LueMatrix4x4 In2 )
{
	CVector4D v( In1.x, In1.y, In1.z );
	CMatrix m(
		In2.x.x, In2.x.y, In2.x.z, In2.x.w,
		In2.y.x, In2.y.y, In2.y.z, In2.y.w,
		In2.z.x, In2.z.y, In2.z.z, In2.z.w,
		In2.w.x, In2.w.y, In2.w.z, In2.w.w );

	v.TransformProjection( m );

	LueVector4D vOut = { v.x, v.y, v.z, v.w };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g����X����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����X���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationX( LueVector4D In, int Angle )
{
	CVector4D v( In.x, In.y, In.z );
	v.RotationX( Angle );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g����Y����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Y���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationY( LueVector4D In, int Angle )
{
	CVector4D v( In.x, In.y, In.z );
	v.RotationY( Angle );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �x�N�g����Z����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Z���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationZ( LueVector4D In, int Angle )
{
	CVector4D v( In.x, In.y, In.z );
	v.RotationZ( Angle );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LueVector4D LueVector4D_RotationAxis( LueVector4D In, int Angle, LueVector3D Axis )
{
	CVector4D v( In.x, In.y, In.z );
	CVector3D vAxis( Axis.x, Axis.y, Axis.z );
	v.RotationAxis( Angle, vAxis );

	LueVector4D vOut = { v.x, v.y, v.z, 1.0f };
	return vOut;
}


}

