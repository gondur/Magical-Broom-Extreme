
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueRender.h"

//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern ICore *Lue_GetCore( void );
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern ITexture *LueTexture_Get( LUE_HANDLE Handle );
extern void LueTexture_SetRender( LUE_HANDLE Handle );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static Bool g_IsBeginScene = false;
static IPostEffect *g_pPostEffect = NULL;


//------------------------------------------------------------------------------------------------
/**
	@brief �����_���[�����̏�����
	@author �t���`

	�����_���[�Ɋւ���ݒ�����������܂��B<BR>
	�����_�����O�^�[�Q�b�g�p�̃T�[�t�F�C�X��e��|�X�g�G�t�F�N�g�A
	�[�x�o�b�t�@�Ɋւ��鏈���͂����ŏ���������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueRender_Initialize( void )
{
	// �|�X�g�G�t�F�N�g�p
	g_pPostEffect = Lue_GetRenderer()->CreatePostEffect();

	g_IsBeginScene = false;
}

//------------------------------------------------------------------------------------------------
/**
	@brief �����_���[�����̉��
	@author �t���`

	�����_���[�Ɋւ���ݒ��������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueRender_Finalize( void )
{
	SAFE_RELEASE( g_pPostEffect );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �V�[���J�n�錾
	@author �t���`

	@param Scene	[in] �`�悷��V�[����ݒ�<BR>
                         �r���������Ă����͂���܂��񂪁A�K���ォ�牺�̏��ŌĂяo���悤�ɂ��ĉ������B<BR>
							LSCENE_2D_BACKGROUND		2D�F�w�i�p�i�A���t�@�֌W�g�p�s�j<BR>
							LSCENE_3D_BLEND_DISABLE		3D�F�s�����i�A���t�@�֌W�g�p�s�j<BR>
							LSCENE_3D_BLEND_ENABLE		3D�F�������i�A���t�@�֌W�g�p�\�j<BR>
							LSCENE_2D_FOREGROUND		2D�F�O�i��2D�Q�[���p�i�A���t�@�֌W�g�p�\�j

	@retval LTRUE	�V�[���J�n����
	@retval LFALSE	�V�[���J�n���s�i�V�[�����������ĂȂ��ꍇ��A��ʂ̃V�[�����牺�ʂ̃V�[���֓��낤�Ƃ����ꍇ���j

	��ʂ̕`�揈�����J�n���邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo������<BR>
	�łȂ���΂Ȃ�܂���B
*/
//------------------------------------------------------------------------------------------------
eLueBool LueRender_SceneStart( void )
{
	if ( g_IsBeginScene ) return LFALSE;

	//----------------------------------------------------------------------
	// �X�e�[�g
	//----------------------------------------------------------------------
	Lue_GetRenderer()->SetCullType( CULL_NONE );
	Lue_GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	Lue_GetRenderer()->SetTextureFilterType( 0, TEXTURE_FILTER_DISABLE );
	Lue_GetRenderer()->SetTextureAddressType( 0, TEXTURE_ADDRESS_REPEAT );

	//----------------------------------------------------------------------
	// �V�[���J�n
	//----------------------------------------------------------------------
	g_IsBeginScene = true;
	Lue_GetRenderer()->Begin();

	return LTRUE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐���<BR>
	�Ăяo���O�łȂ���΂Ȃ�܂���B
*/
//------------------------------------------------------------------------------------------------
void LueRender_SceneExit( void )
{
	if ( !g_IsBeginScene ) return;

	g_IsBeginScene = false;
	Lue_GetRenderer()->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo���O<BR>
	�łȂ���΂Ȃ�܂���B
*/
//------------------------------------------------------------------------------------------------
void LueRender_Printf( const char *pStr, ... )
{
	char Temp[1024] = "";
	vsprintf_s( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

	wchar_t wTemp[1024] = L"";
	MBCStoWCS( Temp, wTemp );
	Lue_GetDevice()->Printf( wTemp );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo���O<BR>
	�łȂ���΂Ȃ�܂���B
*/
//------------------------------------------------------------------------------------------------
void LueRender_ClsPrintf( void )
{
	Lue_GetDevice()->Cls();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惂�[�h�ݒ�
	@author �t���`

	@param DrawMode		[in] �`�惂�[�h

	��ʂւ̕`����s���ۂ̕`����@���w�肵�܂�<BR>
	�s����/������/���Z/��Z�Ȃǂ��w��\�ł��B
*/
//------------------------------------------------------------------------------------------------
void LueRender_SetDrawMode( eLueDrawMode DrawMode )
{
	eDrawType ModeTbl[] = {
		DRAW_TYPE_NORMAL,					///< �ʏ�`��
		DRAW_TYPE_BLEND,					///< �������`��
		DRAW_TYPE_ADD,						///< ���Z�`��
		DRAW_TYPE_ADD_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB,						///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_MULTIPLE,					///< ��Z�`��
		DRAW_TYPE_SCREEN,					///< �X�N���[���`��
	};

	Lue_GetRenderer()->SetDrawType( ModeTbl[DrawMode] );
}


//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_SetTexture( LUE_HANDLE hTexture )
{
	LueTexture_SetRender( hTexture );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawSingleTexture( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->SingleTexture( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawGrayscale( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, float fRate )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Grayscale( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ), fRate );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawUniversalTransition( LUE_HANDLE HandleBase, LUE_HANDLE HandleRule, LueRect Dst, LueRect SrcBase, LueRect SrcRule, float fRate )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcBaseRc( SrcBase.x, SrcBase.y, SrcBase.w, SrcBase.h );
	CRect2D<Sint32> SrcRuleRc( SrcRule.x, SrcRule.y, SrcRule.w, SrcRule.h );
	g_pPostEffect->UniversalTransition( DstRc, fRate, SrcBaseRc, LueTexture_Get( HandleBase ), SrcRuleRc, LueTexture_Get( HandleRule ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawBlur9Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Blur9Box( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawBlur16Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Blur16Box( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void LueRender_DrawBlur64Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pPostEffect->Blur64Box( DstRc, CColor(Color), SrcRc, LueTexture_Get( Handle ) );
}


} // extern "C"

