
#ifndef ___LUE_PRIMITIVE2D_H___
#define ___LUE_PRIMITIVE2D_H___


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
	@brief �v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] �v���~�e�B�u�n���h��

	�v���~�e�B�u�̉�����s���܂��B
*/
void LuePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief �v���~�e�B�u����
	@author �t���`

	@param PrimitiveMax		[in] �v���~�e�B�u�ő吔

	@return �v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł���A<BR>
	�V�U�����O�����s���ƃ��N�G�X�g�������_����������������̂�<BR>
	�ڈ����x�Ƃ��Ĉ��Ȃ��\���ȑ傫�����w�肷��悤�ɂ��Ă��������B
*/
LUE_HANDLE LuePrimitive2D_Create( unsigned int PrimitiveMax );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LuePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LuePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LuePrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param pPrimitive	[in] �v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`��v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
eLueBool LuePrimitive2D_Push( LUE_HANDLE Handle, LuePrimitiveVertex2D *pPrimitive, unsigned int Count );

/**
	@brief �l�p�`�`��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param DstRect		[in] �`���`
	@param Color		[in] �`��F

	�l�p�`�̕`����s���܂��B
*/
void LuePrimitive2D_Square( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color );

/**
	@brief ��]�l�p�`�`��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param DstRect		[in] �`���`
	@param Color		[in] �`��F
	@param Angle		[in] ��]�p�x

	�l�p�`�̕`����s���܂��B
*/
void LuePrimitive2D_SquareRotate( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color, int Angle );

/**
	@brief �����p�`
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] ���p�`���S�ʒu
	@param fRadius		[in] ���p�`���a
	@param Color		[in] ���p�`�F
	@param Num			[in] �搔�i�R�`

	�����p�`��`�悵�܂��B
*/
void LuePrimitive2D_Polygon( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num );

/**
	@brief ��]�����p�`
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] ���p�`���S�ʒu
	@param fRadius		[in] ���p�`���a
	@param Color		[in] ���p�`�F
	@param Num			[in] �搔�i�R�`
	@param Angle		[in] ��]�p�x

	�����p�`��`�悵�܂��B
*/
void LuePrimitive2D_PolygonRotate( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num, int Angle );

/**
	@brief �����O��|���S��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] �����O�̒��S�ʒu
	@param fInRadius	[in] �����O�̓��a
	@param fOutRadius	[in] �����O�̊O�`
	@param InColor		[in] �����O�̓��F
	@param OutColor		[in] �����O�̊O�F
    @param Num			[in] �����O���\�����钸�_��

	�����O��̃|���S����`�悵�܂��B<BR>
	���a�O�a�ŕʁX�̐F���w��ł���̂ŏՌ��g�̂悤�ȃG�t�F�N�g�����܂��B
*/
void LuePrimitive2D_Ring( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num );

/**
	@brief ��]�����O��|���S��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] �����O�̒��S�ʒu
	@param fInRadius	[in] �����O�̓��a
	@param fOutRadius	[in] �����O�̊O�`
	@param InColor		[in] �����O�̓��F
	@param OutColor		[in] �����O�̊O�F
    @param Num			[in] �����O���\�����钸�_��
	@param Angle		[in] ��]�p�x

	�����O��̃|���S����`�悵�܂��B<BR>
	���a�O�a�ŕʁX�̐F���w��ł���̂ŏՌ��g�̂悤�ȃG�t�F�N�g�����܂��B
*/
void LuePrimitive2D_RingRotate( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num, int Angle );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_PRIMITIVE2D_H___
