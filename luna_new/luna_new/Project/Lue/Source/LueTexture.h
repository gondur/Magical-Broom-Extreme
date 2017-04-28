
#ifndef ___LUE_TEXTURE_H___
#define ___LUE_TEXTURE_H___


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
	@brief �e�N�X�`�������p�R���t�B�O�ݒ�
	@author �t���`

	@param Color	[in] �J���[�L�[�̐F�i0�Ŕ����ݒ�Ȃ�

	�e�N�X�`�������p�̐ݒ���s���܂��B
*/
void LueTexture_SetConfig( unsigned int Color );

/**
	@brief �e�N�X�`���̉��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��

	�e�N�X�`���̉�����s���܂��B
*/
void LueTexture_Release( LUE_HANDLE Handle );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param Width	[in] �e�N�X�`���̉���
	@param Height	[in] �e�N�X�`���̏c��

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�w�肵���T�C�Y�̃e�N�X�`���̐������s���܂��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_Create( unsigned int Width, unsigned int Height );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�摜�t�@�C������e�N�X�`���̐������s���܂��B<BR>
	�T�|�[�g���Ă���摜�t�H�[�}�b�g�� TGA/PNG/JPG/DDS/BMP �ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_CreateFromFile( const char *pFileName );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param pData	[in] �e�N�X�`���t�@�C���̊i�[���ꂽ�������̃A�h���X
	@param Size		[in] pData�̃f�[�^�T�C�Y

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	���������̉摜�t�@�C������e�N�X�`���̐������s���܂��B<BR>
	�T�|�[�g���Ă���摜�t�H�[�}�b�g�� TGA/PNG/JPG/DDS/BMP �ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_CreateFromMemory( void *pData, unsigned int Size );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param Width	[in] �e�N�X�`���̉���
	@param Height	[in] �e�N�X�`���̏c��

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�����_�����O�^�[�Q�b�g�Ƃ��ăe�N�X�`���𐶐����܂��B<BR>
	�����_�����O�^�[�Q�b�g�Ƃ��Đ������ꂽ�e�N�X�`���ɑ΂��Ă�<BR>
	���ڃ����_�����O���鎖���\�ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_CreateRenderTarget( unsigned int Width, unsigned int Height );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_TEXTURE_H___
