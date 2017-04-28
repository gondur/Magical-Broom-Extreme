

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��

#define POINT_MAX		(4096)		// �|�C���g��


//=============================================================================
/**
	@brief ���C���֐�

	@param hInstance		[in] ���݂̃C���X�^���X�̃n���h��
	@param hPrevInstance	[in] �ȑO�̃C���X�^���X�̃n���h��
	@param lpCmdPoint		[in] �R�}���h�|�C���g
	@param nCmdShow			[in] �\�����

	�R���\�[���A�v���P�[�V�����ł������� main() �֐��ł��B
	�E�B���h�E�Y�A�v���P�[�V�����ł͈ȉ��̊֐��� main() �ɂȂ�܂��B
*/
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdPoint, int nCmdShow )
{
	LueVertex2D Point;
	LUE_HANDLE hPoint;
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
	// �|�C���g�p�`��I�u�W�F�N�g����
	//  �_�̓V�U�����O�����Ă����_�����ς��Ȃ��̂�
	//  �]���Ɋm�ۂ���K�v�͂Ȃ��B
	//--------------------------------------------------------
	hPoint = LuePointPrimitive2D_Create( POINT_MAX );

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
		///////////////////////////////////////////////////////////////// �|�C���g�ւ̕`�惊�N�G�X�g

		// �|�C���g�ւ̕`��J�n��ʒm
		LuePointPrimitive2D_Begin( hPoint );

		// �|�C���g�ɑ΂��ĕ`��
		for ( i = 0; i < POINT_MAX; i++ )
		{
			// ���_
			Point.Pos.x = (float)(rand() % (SCREEN_WIDTH/2))  + (SCREEN_WIDTH /4);
			Point.Pos.y = (float)(rand() % (SCREEN_HEIGHT/2)) + (SCREEN_HEIGHT/4);
			Point.Pos.z = 0.0f;
			Point.Pos.w = 1.0f;
			Point.Col   = LUE_RGB(255,255,255);
			// �|�C���g�ɕ`������N�G�X�g
			LuePointPrimitive2D_Push( hPoint, &Point, 1 );
		}

		// �|�C���g�ւ̕`�抮����ʒm
		LuePointPrimitive2D_End( hPoint );

		///////////////////////////////////////////////////////////////// �����_���[�ւ̕`�揈��

		// �`��J�n�錾
		LueRender_SceneStart();

		// �e�N�X�`���ݒ薳��
		LueRender_SetTexture( INVALID_LUE_HANDLE );

		// �|�C���g�o�b�t�@�̓��e����ʂɕ`��
		LuePointPrimitive2D_Rendering( hPoint );

		// �`��I���錾
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// �|�C���g�I�u�W�F�N�g���
	//--------------------------------------------------------
	LuePointPrimitive2D_Release( hPoint );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


