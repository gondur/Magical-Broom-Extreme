

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��
#define FRAME_RATE		(60)		// �t���[�����[�g

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
	long Px = (SCREEN_WIDTH  - TEX_W) / 2;		// �����ʒu
	long Py = (SCREEN_HEIGHT - TEX_H) / 2;		// �����ʒu

	//--------------------------------------------------------
	// Lue������
	//--------------------------------------------------------
	if ( !Lue_Initialize(
			"Lue Sample Program",		// �A�v���P�[�V������
			SCREEN_WIDTH,				// �E�B���h�E����
			SCREEN_HEIGHT,				// �E�B���h�E�c��
			FRAME_RATE,					// �t���[�����[�g�i1�b�Ԃ̃t���[�����j
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
	LueTexture_SetConfig( LFALSE, LUE_ARGB(0,0,0,0) );

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
		/////////////////////////////////////////////////////////////// �L�[���͏���

		// �L�[�{�[�h�̓��͂ɉ����ĊG�̈ړ�
		//  �L�[�̒�`�Ɋւ��Ă̓��t�@�����X���Q�Ƃ��ĉ������B
		if ( LueInput_GetKeyData( LUE_VK_UP    ) ) Py -= 2;	// ��
		if ( LueInput_GetKeyData( LUE_VK_DOWN  ) ) Py += 2;	// ��
		if ( LueInput_GetKeyData( LUE_VK_LEFT  ) ) Px -= 2;	// ��
		if ( LueInput_GetKeyData( LUE_VK_RIGHT ) ) Px += 2;	// �E

		/////////////////////////////////////////////////////////////// �`�揈��

		// �`��J�n�錾
		LueRender_SceneStart( LSCENE_2D_FOREGROUND );	// 2D�O�i�ŃV�[���J�n

		// �`��ʒu
		Dst.Px = Px;
		Dst.Py = Py;
		Dst.Sx = TEX_W;
		Dst.Sy = TEX_H;
		// �e�N�X�`���Q�ƈʒu
		Src.Px = 0;
		Src.Py = 0;
		Src.Sx = TEX_W;
		Src.Sy = TEX_H;
		// �ǂݍ��񂾃e�N�X�`������ʂɕ`��
		LueTexture_Draw( hTex, Dst, Src, LUE_RGB(255,255,255) );

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

