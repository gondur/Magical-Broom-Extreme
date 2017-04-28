
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueSprite2D.h"

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
extern ITexture *LueTexture_Get( LUE_HANDLE Handle );


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const unsigned int SPRITE2D_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ISprite2D *g_pSpr2DTbl[SPRITE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );


//------------------------------------------------------------------------------------------------
/**
	@brief �X�v���C�g�Ǘ��N���X�̏�����
	@author �t���`

	�X�v���C�g�Ǘ��N���X�̏��������s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Initialize( void )
{
	for ( Uint32 i = 0; i < SPRITE2D_MAX; i++ )
	{
		g_pSpr2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �X�v���C�g�Ǘ��N���X�̉��
	@author �t���`

	�X�v���C�g�Ǘ��N���X�̉�����s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Finalize( void )
{
	for ( Uint32 i = 0; i < SPRITE2D_MAX; i++ )
	{
		if ( g_pSpr2DTbl[i] != NULL )
		{
			g_pSpr2DTbl[i]->Release();
			g_pSpr2DTbl[i] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ���g�p�X�v���C�g�̌���
	@author �t���`

	@return ���g�p�̃X�v���C�g�n���h��

	���g�p�̃X�v���C�g�I�u�W�F�N�g�̌��������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueSprite2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < SPRITE2D_MAX; i++ )
	{
		if ( g_pSpr2DTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �X�v���C�g�̉��
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��

	�X�v���C�g�̉�����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;

	if ( g_pSpr2DTbl[Handle] != NULL )
	{
		g_pSpr2DTbl[Handle]->Release();
		g_pSpr2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �X�v���C�g����
	@author �t���`

	@param PrimitiveMax		[in] �v���~�e�B�u�ő吔
	@param hTexture			[in] �ڑ�����e�N�X�`���̃n���h��

	@return �X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�X�v���C�g�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł���A<BR>
	�V�U�����O�����s���ƃ��N�G�X�g�������_����������������̂�<BR>
	�ڈ����x�Ƃ��Ĉ��Ȃ��\���ȑ傫�����w�肷��悤�ɂ��Ă��������B<BR>
	�܂� hTeture �Ŏw�肵���e�N�X�`�����g���ĕ`�悳��܂��B
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueSprite2D_Create( unsigned int PrimitiveMax, LUE_HANDLE hTexture )
{
	LUE_HANDLE Handle = LueSprite2D_SearchFreeHandle();
	if ( Handle >= SPRITE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pSpr2DTbl[Handle] = Lue_GetRenderer()->CreateSprite2D( PrimitiveMax, LueTexture_Get( hTexture ) );
	if ( g_pSpr2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	g_pSpr2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	g_pSpr2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	g_pSpr2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��
	@param Dst		[in] �`����`
	@param Src		[in] �e�N�X�`��UV��`
	@param Color	[in] ���_�F

	�X�v���C�g���g������`�̕`����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_DrawSquare( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pSpr2DTbl[Handle]->DrawSquare( DstRc, SrcRc, Color );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��
	@param Dst		[in] �`����`
	@param Src		[in] �e�N�X�`��UV��`
	@param Color	[in] ���_�F
	@param Angle	[in] 1��65536�Ƃ�����]�p�x

	�X�v���C�g���g������`�̉�]�`����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_DrawSquareRotate( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, unsigned int Angle )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pSpr2DTbl[Handle]->DrawSquareRotate( DstRc, SrcRc, Color, Angle );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��
	@param Px		[in] �|�C���g��X�l���i�[���ꂽ�z��
	@param Py		[in] �|�C���g��Y�l���i�[���ꂽ�z��
	@param Width	[in] �|�C���g�̕����i�[���ꂽ�z��
	@param Angle	[in] �|�C���g��1��65536�Ƃ�����]�p�x���i�[���ꂽ�z��
	@param Color	[in] 1��65536�Ƃ�����]�p�x
	@param Count	[in] �e�z��̗v�f��
	@param Src		[in] �e�N�X�`��UV��`

	�X�v���C�g���g�������X�g��̕`����s���܂�<BR>
	�Ȃ��郌�[�U�[�̂悤�ȑ��֐ߌn�̕\������̂ɓK���Ă��܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_DrawList( LUE_HANDLE Handle, LuePoint Pos[], float Width[], int Angle[], unsigned int Color[], int Count, LueRect Src )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> SrcRc( Src.x, Src.y, Src.w, Src.h );
	g_pSpr2DTbl[Handle]->DrawList( (CPoint2D<Float>*)Pos, Width, (Sint32*)Angle, (CColor*)Color, Count, SrcRc );
}

//------------------------------------------------------------------------------------------------
/**
	@brief �~��t�F�[�h
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��
	@param SrcRect		[in] �e�N�X�`���̓K����`
	@param Divide		[in] ��]�����������i�P�U���x�����j
	@param Side			[in] ���ʕ������i�P�U���x�����j
	@param Alpha		[in] �������x�i-255�`+255)

	��ʒ��S�Ɍ������ăt�F�[�h�C���^�t�F�[�h�A�E�g�����܂�<BR>
	��ʌ��ʂƂ��Ă悭����������ʂł����ȒP�Ɏg�����ʌ��ʂƂ��Ď������Ă���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_CircleFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> Src( SrcRect.x, SrcRect.y, SrcRect.w, SrcRect.h );
	g_pSpr2DTbl[Handle]->CircleFade( Src, Divide, Side, Alpha );
}

//------------------------------------------------------------------------------------------------
/**
	@brief ��]�t�F�[�h
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��
	@param SrcRect		[in] �e�N�X�`���̓K����`
	@param Divide		[in] ��]�����������i�P�U���x�����j
	@param Side			[in] ���ʕ������i�P�U���x�����j
	@param Alpha		[in] �������x�i-255�`+255)

	���v���ɉ�]����悤�Ƀt�F�[�h�C���^�t�F�[�h�A�E�g�����܂�<BR>
	��ʌ��ʂƂ��Ă悭����������ʂł����ȒP�Ɏg�����ʌ��ʂƂ��Ď������Ă���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSprite2D_CircleRoundFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha )
{
	if ( Handle >= SPRITE2D_MAX ) return;
	if ( g_pSpr2DTbl[Handle] == NULL ) return;

	CRect2D<Sint32> Src( SrcRect.x, SrcRect.y, SrcRect.w, SrcRect.h );
	g_pSpr2DTbl[Handle]->CircleRoundFade( Src, Divide, Side, Alpha );
}

} // extern "C"

