
#ifndef ___LUE_FONTSPRITE2D_H___
#define ___LUE_FONTSPRITE2D_H___


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
	@brief �t�H���g�X�v���C�g�̉��
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��

	�t�H���g�X�v���C�g�̉�����s���܂��B
*/
void LueFontSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief �t�H���g�X�v���C�g����
	@author �t���`

	@param pBuffer		[in] �e�N�X�`���쐬�p������
	@param FontMax		[in] �t�H���g�X�v���C�g��
	@param pFontFace	[in] �t�H���g����
	@param FontSize		[in] �t�H���g�T�C�Y�i�s�N�Z��
	@param IsItalic		[in] �Α̂�ON/OFF
	@param IsBold		[in] ������ON/OFF
	@param IsAntialias	[in] �A���`�G�C���A�X��ON/OFF

	@return �t�H���g�X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�����񂩂�t�H���g�X�v���C�g�𐶐����܂��B<BR>
	pBuffer �Ŏw�肳�ꂽ����������̑������ɉ����ăe�N�X�`���ɓW�J���܂��B<BR>
	FontMax�͍ő�`��\���ł���A�V�U�����O�Ȃǂœ����o�b�t�@��<BR>
	���N�G�X�g��葽���g���邱�Ƃ�����܂��̂ŁA���Ȃ��\���ȑ傫�����w�肵�Ă��������B
*/
LUE_HANDLE LueFontSprite2D_Create( const char *pBuffer, unsigned int FontMax, const char *pFontFace, unsigned int FontSize, eLueBool IsItalic, eLueBool IsBold, eLueBool IsAntialias );

/**
	@brief �t�H���g�X�v���C�g����
	@author �t���`

	@param pFileName	[in] �e�N�X�`���쐬�p������
	@param pExt			[in] �e�N�X�`���g���q�iFont_00.tga�̏ꍇ��"tga"�j
	@param FontMax		[in] �t�H���g�X�v���C�g��

	@return �t�H���g�X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	���O�ɍ쐬���ꂽ�t�H���g�f�[�^����t�H���g�X�v���C�g�𐶐����܂��B<BR>
	FontMax�͍ő�`��\���ł���A�V�U�����O�Ȃǂœ����o�b�t�@��<BR>
	���N�G�X�g��葽���g���邱�Ƃ�����܂��̂ŁA���Ȃ��\���ȑ傫�����w�肵�Ă��������B
*/
LUE_HANDLE LueFontSprite2D_CreateFromFile( const char *pFileName, const char *pExt, unsigned int FontMax );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃt�H���g�X�v���C�g�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LueFontSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃt�H���g�X�v���C�g�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LueFontSprite2D_End( LUE_HANDLE Handle );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�t�H���g�X�v���C�g�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LueFontSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g���������t�H���g�ł̕�����`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
void LueFontSprite2D_DrawString( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g�����v���|�[�V���i���t�H���g�ł̕�����`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
void LueFontSprite2D_DrawStringP( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief �����`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶��
	@param Dst		[in] �`���`
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g���������`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
int LueFontSprite2D_DrawChara( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color );

/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Dst		[in] �`���`
	@param Color	[in] ���_�F
	@param Angle	[in] 1��65536�Ƃ�����]�p�x

	�t�H���g�X�v���C�g���g������]�t��������`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
int LueFontSprite2D_DrawCharaRotate( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color, int Angle );

/**
	@brief ������`��ʒu�擾
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l

	�t�H���g�X�v���C�g���g���������t�H���g�ł̕�����`����s������́B<BR>
	�ŏI�I�Ȉʒu���擾���܂��B<BR>
	�����ĕ������`�悷��ꍇ��A������̍����╝���擾����̂ɗL���ł��B
*/
LuePoint LueFontSprite2D_GetStringLastPos( LUE_HANDLE Handle, const char *pStr, int Px, int Py );

/**
	@brief ������`��ʒu�擾
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l

	�t�H���g�X�v���C�g���g�����v���|�[�V���i���t�H���g�ł̕�����`����s������́B<BR>
	�ŏI�I�Ȉʒu���擾���܂��B<BR>
	�����ĕ������`�悷��ꍇ��A������̍����╝���擾����̂ɗL���ł��B
*/
LuePoint LueFontSprite2D_GetStringLastPosP( LUE_HANDLE Handle, const char *pStr, int Px, int Py );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_FONTSPRITE2D_H___
