

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��

#define LINE_MAX		(512)		// ���C����
#define LINE_SIZE_X		(20.0f)		// ���C��X�T�C�Y
#define LINE_SIZE_Y		(50.0f)		// ���C��Y�T�C�Y


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
	LueLinePrimitiveVertex2D Line;
	LUE_HANDLE hLine;
	long i;

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
	// ���C���p�`��I�u�W�F�N�g����
	//  �����͒��_�Q���琬��̂ł��Q�œn��
	//  �����̓V�U�����O�����Ă����_�����ς��Ȃ��̂�
	//  �]���Ɋm�ۂ���K�v�͂Ȃ��B
	//--------------------------------------------------------
	hLine = LueLinePrimitive2D_Create( LINE_MAX * 2 );

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
		///////////////////////////////////////////////////////////////// ���C���ւ̕`�惊�N�G�X�g

		// ���C���ւ̕`��J�n��ʒm
		LueLinePrimitive2D_Begin( hLine );

		// ���C���ɑ΂��ĕ`��
		for ( i = 0; i < LINE_MAX; i++ )
		{
			// ���_�P
			Line.v[0].Pos.x = (float)(rand() % SCREEN_WIDTH)  - (LINE_SIZE_X / 2.0f);
			Line.v[0].Pos.y = (float)(rand() % SCREEN_HEIGHT) - (LINE_SIZE_Y / 2.0f);
			Line.v[0].Pos.z = 0.0f;
			Line.v[0].Pos.w = 1.0f;
			Line.v[0].Col   = LUE_RGB(128,128,128);
			// ���_�Q
			Line.v[1] = Line.v[0];
			Line.v[1].Pos.x += LINE_SIZE_X;
			Line.v[1].Pos.y += LINE_SIZE_Y;
			// ���C���ɕ`������N�G�X�g
			LueLinePrimitive2D_Push( hLine, &Line, 1 );
		}

		// ���C���ւ̕`�抮����ʒm
		LueLinePrimitive2D_End( hLine );

		///////////////////////////////////////////////////////////////// �����_���[�ւ̕`�揈��

		// �`��J�n�錾
		LueRender_SceneStart();

		// �e�N�X�`���ݒ薳��
		LueRender_SetTexture( INVALID_LUE_HANDLE );

		// ���C���o�b�t�@�̓��e����ʂɕ`��
		LueLinePrimitive2D_Rendering( hLine );

		// �`��I���錾
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// ���C���I�u�W�F�N�g���
	//--------------------------------------------------------
	LueLinePrimitive2D_Release( hLine );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


