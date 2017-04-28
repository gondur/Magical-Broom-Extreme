
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueTexture.h"

//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;

//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {

//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const Uint32 TEXTURE_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ITexture *g_pTextureTbl[TEXTURE_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���Ǘ��N���X������
	@author �t���`

	�e�N�X�`���֘A�̏��������������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueTexture_Initialize( void )
{
	for ( Sint32 i = 0; i < TEXTURE_MAX; i++ )
	{
		g_pTextureTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���Ǘ��N���X�I��
	@author �t���`

	�e�N�X�`���֘A�̏������I�����܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueTexture_Finalize( void )
{
	for ( Uint32 i = 0; i < TEXTURE_MAX; i++ )
	{
		if ( g_pTextureTbl[i] != NULL )
		{
			g_pTextureTbl[i]->Release();
			g_pTextureTbl[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief ���g�p�e�N�X�`���̌���
	@author �t���`

	@return ���g�p�̃e�N�X�`���n���h��

	���g�p�̃e�N�X�`���I�u�W�F�N�g�̌��������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < TEXTURE_MAX; i++ )
	{
		if ( g_pTextureTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���N���X�̃C���^�[�t�F�[�X���擾
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��

	@return �e�N�X�`���N���X�̃C���^�[�t�F�[�X

	�w�肵���e�N�X�`���n���h�������L����e�N�X�`���C���^�[�t�F�[�X�N���X���擾���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
ITexture *LueTexture_Get( LUE_HANDLE Handle )
{
	if ( Handle >= TEXTURE_MAX ) return NULL;
	return g_pTextureTbl[Handle];
}



//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`�������p�R���t�B�O�ݒ�
	@author �t���`

	@param IsMipmap	[in] �~�b�v�}�b�v�̗L��
	@param Color	[in] �J���[�L�[�̐F�i0�Ŕ����ݒ�Ȃ�

	�e�N�X�`�������p�̐ݒ���s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueTexture_SetConfig( unsigned int Color )
{
	CTextureConfig Conf;
	Conf.SetColorKey( Color );
	Conf.SetFormat( FORMAT_TEXTURE_2D );

	Lue_GetRenderer()->SetTextureConfig( Conf );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���̉��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��

	�e�N�X�`���̉�����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueTexture_Release( LUE_HANDLE Handle )
{
	if ( Handle >= TEXTURE_MAX ) return;

	if ( g_pTextureTbl[Handle] != NULL )
	{
		g_pTextureTbl[Handle]->Release();
		g_pTextureTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param Width	[in] �e�N�X�`���̉���
	@param Height	[in] �e�N�X�`���̏c��

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�w�肵���T�C�Y�̃e�N�X�`���̐������s���܂��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_Create( unsigned int Width, unsigned int Height )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTexture( Width, Height );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// ����
		return Handle;
	}

	// ���s�Ȃ̂ŉ��
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�摜�t�@�C������e�N�X�`���̐������s���܂��B<BR>
	�T�|�[�g���Ă���摜�t�H�[�}�b�g�� TGA/PNG/JPG/DDS/BMP �ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_CreateFromFile( const char *pFileName )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFileName, wTemp );

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTextureFromFile( wTemp );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// ����
		return Handle;
	}

	// ���s�Ȃ̂ŉ��
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_CreateFromMemory( void *pData, unsigned int Size )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTextureFromMemory( pData, Size );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// ����
		return Handle;
	}

	// ���s�Ȃ̂ŉ��
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_CreateRenderTarget( unsigned int Width, unsigned int Height )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTextureRenderTarget( Width, Height );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// ����
		return Handle;
	}

	// ���s�Ȃ̂ŉ��
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���̐ݒ�
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��

	�����_���[�ɑ΂��ĕ`��Ɏg�p����e�N�X�`����ݒ肵�܂��B<BR>
	INVALID_LUE_HANDLE ���w�肷��ƃe�N�X�`�����g��Ȃ��悤�ɂȂ�܂��B<BR>
	�܂��t�� INVALID_LUE_HANDLE ���w�肷��܂Őݒ肵���e�N�X�`����<BR>
	�g���鑱���鎖�ɂȂ�܂��B
	����� LueSprite2D �� LueFontSprite2D �̂悤�ɓ����Ńe�N�X�`����<BR>
	�����I�ɐ؂�ւ���֐����Ăяo������͕ύX���ꂽ�܂܂ɂȂ��Ă��܂��̂�<BR>
	�A�v���P�[�V�������Ŏg�p����ۂɂ͍ēx�ݒ肷��悤�ɂ��ĉ������B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueTexture_SetRender( LUE_HANDLE Handle )
{
	if ( (Handle >= TEXTURE_MAX) )
	{
		Lue_GetRenderer()->SetTexture( 0, NULL );
	}
	else
	{
		Lue_GetRenderer()->SetTexture( 0, g_pTextureTbl[Handle] );
	}
}


} // extern "C"

