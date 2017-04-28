

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��

#define TEX_W			(256)		// �e�N�X�`������
#define TEX_H			(256)		// �e�N�X�`���c��


//=============================================================================
/**
	@brief ���C���֐�

	@param hInstance		[in] ���݂̃C���X�^���X�̃n���h��
	@param hPrevInstance	[in] �ȑO�̃C���X�^���X�̃n���h��
	@param lpCmdLine		[in] �R�}���h���C��
	@param nCmdShow			[in] �\�����

	�R���\�[���A�v���P�[�V�����ł������� main() �֐��ł��B
	�E�B���h�E�Y�A�v���P�[�V�����ł͈ȉ��̊֐��� main() �ɂȂ�܂��B
*/
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	LUE_HANDLE hTex = INVALID_LUE_HANDLE;		// �e�N�X�`���n���h��
	LueRect Dst, Src;							// �`��p��`
	float Px = (SCREEN_WIDTH  - TEX_W) / 2;		// �����ʒu
	float Py = (SCREEN_HEIGHT - TEX_H) / 2;		// �����ʒu
	LueMouseData Mouse;							// �}�E�X�p�\����
	unsigned long Color;						// �G�̐F

	//--------------------------------------------------------
	// Lue������
	//--------------------------------------------------------
	if ( !Lue_Initialize(
			"Lue Sample Program",		// �A�v���P�[�V������
			SCREEN_WIDTH,				// �E�B���h�E����
			SCREEN_HEIGHT,				// �E�B���h�E�c��
			LFRAME_RATE_60,				// �t���[�����[�g�i1�b�Ԃ̃t���[�����j
			LTRUE,						// �E�B���h�E���[�h�ŋN�����邩�ǂ���
			LAPI_TYPE_DIRECTX9 ) )		// �Œ�
	{
		return 1;
	}

	//--------------------------------------------------------
	// �t�@�C���ǂݍ��ݏꏊ�̐ݒ�
	//--------------------------------------------------------
	// �t�@�C���ǂݍ��݂̃��[�g�f�B���N�g���ݒ�
	LueFile_SetLoadPath( 0, "Data", "Data.bin" );

	// �t�@�C���ǂݍ��݂̊�f�B���N�g���ݒ�
	LueFile_SetCurrentDirectory( "2D\\DrawTexture" );

	//--------------------------------------------------------
	// �e�N�X�`���̓ǂݍ���
	//--------------------------------------------------------
	// �e�N�X�`�������p�̃I�v�V�����ݒ�
	LueTexture_SetConfig( LUE_ARGB(0,0,0,0) );

	// �摜�t�@�C������e�N�X�`���ǂݍ���
	//  DirectX�ň����e�N�X�`���̃T�C�Y�͂Q�̊K��ł���K�v������܂��B
	//  �P�ӂ̃s�N�Z������ 1�A2�A4�A8�A16�A32�A64�A128�A256�A512�A1024�A2048 �ł���K�v������܂��B
	hTex = LueTexture_CreateFromFile( "Sample.bmp" );

	//--------------------------------------------------------
	// ���C�����[�v
	//   ALT+F4�ŃA�v���P�[�V�����̏I���B
	//   ALT+ENTER�ŉ�ʃ��[�h�̐؂�ւ�
	//
	// Lue_Run()�̓E�B���h�E���g�����Q�[���ŕK�{�̏�����
	// �����ɑg�ݍ��܂�Ă��܂��B
	// �E�B���h�E�𐳏�ɏI���������ꍇ�� LFASE ���Ԃ�܂��̂�
	// ���̎��̓��[�v���甲����悤�ȍ��ɂ��ĉ������B
	//--------------------------------------------------------
	while ( Lue_Run( LFALSE ) )
	{
		/////////////////////////////////////////////////////////////// �}�E�X���͏���

		// �}�E�X�����擾
		Mouse = LueInput_GetMouseData();

		// �}�E�X�̈ʒu�ɊG��\��
		Px = (float)(Mouse.Px - (TEX_W / 2));
		Py = (float)(Mouse.Py - (TEX_H / 2));

		// ���N���b�N�Ő�
		if ( Mouse.ClickL )
		{
			Color = LUE_RGB(255,128,128);
		}
		// �E�N���b�N�ŗ�
		else if ( Mouse.ClickR )
		{
			Color = LUE_RGB(128,255,128);
		}
		//�z�C�[���N���b�N�Ő�

		else if ( Mouse.ClickW )
		{
			Color = LUE_RGB(128,128,255);
		}
		// ������Ă��Ȃ����͂��̂܂�
		else
		{
			Color = LUE_RGB(255,255,255);
		}

		/////////////////////////////////////////////////////////////// �`�揈��

		// �`��J�n�錾
		LueRender_SceneStart();

		// �`��ʒu
		Dst.x = (int)Px;
		Dst.y = (int)Py;
		Dst.w = TEX_W;
		Dst.h = TEX_H;
		// �e�N�X�`���Q�ƈʒu
		Src.x = 0;
		Src.y = 0;
		Src.w = TEX_W;
		Src.h = TEX_H;
		// �ǂݍ��񂾃e�N�X�`������ʂɕ`��
		LueRender_DrawSingleTexture( hTex, Dst, Src, Color );

		// �`��I���錾
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// �I������
	//--------------------------------------------------------
	// �ǂݍ��񂾃e�N�X�`�������
	LueTexture_Release( hTex );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


