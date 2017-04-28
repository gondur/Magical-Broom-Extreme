
#ifndef ___LUE_LINEPRIMITIVE2D_H___
#define ___LUE_LINEPRIMITIVE2D_H___


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
	@brief ���C���v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] ���C���v���~�e�B�u�n���h��

	���C���v���~�e�B�u�̉�����s���܂��B
*/
void LueLinePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief ���C���v���~�e�B�u����
	@author �t���`

	@param LinePrimitiveMax		[in] ���C���v���~�e�B�u�ő吔

	@return ���C���v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	���C���v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł��B
*/
LUE_HANDLE LueLinePrimitive2D_Create( unsigned int LinePrimitiveMax );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ���C���v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LueLinePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��C���v���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LueLinePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��C���v���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LueLinePrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��
	@param pPrimitive	[in] ���C���v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`�惉�C���v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
eLueBool LueLinePrimitive2D_Push( LUE_HANDLE Handle, LueLinePrimitiveVertex2D *pPrimitive, unsigned int Count );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_LINEPRIMITIVE2D_H___
