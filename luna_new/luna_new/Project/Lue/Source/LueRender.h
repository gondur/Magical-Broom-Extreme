
#ifndef ___LUE_RENDER_H___
#define ___LUE_RENDER_H___


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
	@brief �V�[���J�n�錾
	@author �t���`

	@retval LTRUE	�V�[���J�n����
	@retval LFALSE	�V�[���J�n���s�i�V�[�����������ĂȂ��ꍇ��A��ʂ̃V�[�����牺�ʂ̃V�[���֓��낤�Ƃ����ꍇ���j

	��ʂ̕`�揈�����J�n���邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo������<BR>
	�łȂ���΂Ȃ�܂���B
*/
eLueBool LueRender_SceneStart( void );

/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐���<BR>
	�Ăяo���O�łȂ���΂Ȃ�܂���B
*/
void LueRender_SceneExit( void );

/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo���O<BR>
	�łȂ���΂Ȃ�܂���B
*/
void LueRender_Printf( const char *pStr, ... );

/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo���O<BR>
	�łȂ���΂Ȃ�܂���B
*/
void LueRender_ClsPrintf( void );

/**
	@brief �`�惂�[�h�ݒ�
	@author �t���`

	@param DrawMode		[in] �`�惂�[�h

	��ʂւ̕`����s���ۂ̕`����@���w�肵�܂�<BR>
	�s����/������/���Z/��Z�Ȃǂ��w��\�ł��B
*/
void LueRender_SetDrawMode( eLueDrawMode DrawMode );

/**
	@brief �e�N�X�`���̐ݒ�
	@author �t���`

	@param hTexture	[in] �e�N�X�`���n���h��

	�����_���[�ɑ΂��ĕ`��Ɏg�p����e�N�X�`����ݒ肵�܂��B<BR>
	INVALID_LUE_HANDLE ���w�肷��ƃe�N�X�`�����g��Ȃ��悤�ɂȂ�܂��B<BR>
	�܂��t�� INVALID_LUE_HANDLE ���w�肷��܂Őݒ肵���e�N�X�`����<BR>
	�g���鑱���鎖�ɂȂ�܂��B
	����� LueSprite2D �� LueFontSprite2D �̂悤�ɓ����Ńe�N�X�`����<BR>
	�����I�ɐ؂�ւ���֐����Ăяo������͕ύX���ꂽ�܂܂ɂȂ��Ă��܂��̂�<BR>
	�A�v���P�[�V�������Ŏg�p����ۂɂ͍ēx�ݒ肷��悤�ɂ��ĉ������B
*/
void LueRender_SetTexture( LUE_HANDLE hTexture );

/**
	@brief �e�N�X�`���̒��ڕ`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`���𒼐ډ�ʂɃ����_�����O���܂��B<BR>
	�ȈՓI�ɉ�ʂւ̕`����\�ɂ��邽�߂̊֐��ł��̂ŁA<BR>
	��ʂɕ`�悵�����ꍇ���A���x��D�悷��ꍇ�� LueSprite2D ��<BR>
	�g���Ă܂Ƃ߂ĕ`�悷��悤�ɂ��ĉ������B
*/
void LueRender_DrawSingleTexture( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �e�N�X�`���̃O���[�X�P�[���`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param fRate	[in] �O���[�X�P�[���K�p�x(0.0�`1.0)

	�e�N�X�`�����O���[�X�P�[�������ă����_�����O���܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawGrayscale( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, float fRate );

/**
	@brief �e�N�X�`���̃��j�o�[�T���g�����W�V�����`��
	@author �t���`

	@param HandleBase	[in] �J���[�e�N�X�`���n���h��
	@param HandleRule	[in] ���[���e�N�X�`���n���h��
	@param Dst			[in] �`���̋�`
	@param SrcBase		[in] �J���[�e�N�X�`���̕`�挳��`
	@param SrcRule		[in] ���[���e�N�X�`���̕`�挳��`
	@param fRate		[in] �������K�p�x(0.0�`1.0)

	���[���摜��p���ă��j�o�[�T���g�����W�V���������_�����O���܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawUniversalTransition( LUE_HANDLE HandleBase, LUE_HANDLE HandleRule, LueRect Dst, LueRect SrcBase, LueRect SrcRule, float fRate );

/**
	@brief �e�N�X�`���̂ڂ����`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`����3x3�{�b�N�X�t�B���^�����O�������Ăڂ����܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawBlur9Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �e�N�X�`���̂ڂ����`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`����4x4�{�b�N�X�t�B���^�����O�������Ăڂ����܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawBlur16Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �e�N�X�`���̂ڂ����`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`����8x8�{�b�N�X�t�B���^�����O�������Ăڂ����܂��B<BR>
	�s�N�Z���V�F�[�_�[2.0���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawBlur16Box()�ɒu���������܂��B
*/
void LueRender_DrawBlur64Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );



//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_RENDER_H___
