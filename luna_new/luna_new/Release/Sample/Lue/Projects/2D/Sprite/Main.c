

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��

#define BALL_MAX		(256)		// �{�[���̐�
#define BALL_SIZE		(32)		// �{�[���̉摜�T�C�Y
#define BALL_TYPE_MAX	(9)			// �{�[���̎��


//=============================================================================
// STRUCT
//=============================================================================
typedef struct SBallData
{
	float Px;
	float Py;
	float Mx;
	float My;
}
SBallData;


//=============================================================================
// VARIABLE
//=============================================================================
static SBallData g_BallData[BALL_MAX];


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
	LUE_HANDLE hTex = INVALID_LUE_HANDLE;	// �e�N�X�`���n���h��
	LUE_HANDLE lSpr = INVALID_LUE_HANDLE;	// �X�v���C�g�n���h��
	LueRect Src, Dst;
	long i, Type, Angle;

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
	LueFile_SetCurrentDirectory( "2D\\Sprite" );

	//--------------------------------------------------------
	// �e�N�X�`���̓ǂݍ���
	//--------------------------------------------------------
	// �e�N�X�`�������p�̃I�v�V�����ݒ�
	//  0,255,0 �̐F���J���[�L�[�ɐݒ�
	LueTexture_SetConfig( LUE_RGB(0,255,0) );

	// �摜�t�@�C������e�N�X�`���ǂݍ���
	//  DirectX�ň����e�N�X�`���̃T�C�Y�͂Q�̊K��ł���K�v������܂��B
	//  �P�ӂ̃s�N�Z������ 1�A2�A4�A8�A16�A32�A64�A128�A256�A512�A1024�A2048 �ł���K�v������܂��B
	hTex = LueTexture_CreateFromFile( "Ball.bmp" );

	// �X�v���C�g�p�o�b�t�@�𐶐�
	//  �O�p�`2���Ŏl�p�`�����̂ŁA�l�p�`1�ɑ債��6�̒��_���K�v�ł��B
	//  �܂��쐬���Ɏg�p����e�N�X�`����n���܂��B
	lSpr = LueSprite2D_Create( BALL_MAX * 6, hTex );

	//--------------------------------------------------------
	// �{�[����񏉊���
	//--------------------------------------------------------
	for ( i = 0; i < BALL_MAX; i++ )
	{
		Angle = rand() % LUE_ANGLE_MAX;
		g_BallData[i].Px = (float)(rand() % (SCREEN_WIDTH  - BALL_SIZE));	// �����ʒu
		g_BallData[i].Py = (float)(rand() % (SCREEN_HEIGHT - BALL_SIZE));	// �����ʒu
		g_BallData[i].Mx = LueMath_Cos( Angle ) * 2.0f;						// �ړ�����
		g_BallData[i].My = LueMath_Sin( Angle ) * 2.0f;						// �ړ�����
	}

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
		///////////////////////////////////////////////////////////////// �{�[���̃f�[�^�X�V
		// �{�[���̈ʒu�����X�V
		for ( i = 0; i < BALL_MAX; i++ )
		{
			g_BallData[i].Px += g_BallData[i].Mx;
			g_BallData[i].Py += g_BallData[i].My;

			// ���ړ����A��ʒ[�܂Ō��������]
			if ( (g_BallData[i].Mx < 0) && (g_BallData[i].Px <= 0) )
			{
				g_BallData[i].Mx = -g_BallData[i].Mx;
			}
			// �E�ړ����A��ʒ[�܂Ō��������]
			if ( (g_BallData[i].Mx > 0) && (g_BallData[i].Px + BALL_SIZE >= SCREEN_WIDTH) )
			{
				g_BallData[i].Mx = -g_BallData[i].Mx;
			}
			// ��ړ����A��ʒ[�܂Ō��������]
			if ( (g_BallData[i].My < 0) && (g_BallData[i].Py <= 0) )
			{
				g_BallData[i].My = -g_BallData[i].My;
			}
			// ���ړ����A��ʒ[�܂Ō��������]
			if ( (g_BallData[i].My > 0) && (g_BallData[i].Py + BALL_SIZE >= SCREEN_HEIGHT) )
			{
				g_BallData[i].My = -g_BallData[i].My;
			}
		}

		///////////////////////////////////////////////////////////////// �X�v���C�g�ւ̕`�惊�N�G�X�g

		// �X�v���C�g�ւ̕`��J�n��ʒm
		LueSprite2D_Begin( lSpr );

		// �X�v���C�g�ɑ΂��ă{�[����`��
		for ( i = 0; i < BALL_MAX; i++ )
		{
			// �`��ʒu
			Dst.x = (int)g_BallData[i].Px;
			Dst.y = (int)g_BallData[i].Py;
			Dst.w = BALL_SIZE;
			Dst.h = BALL_SIZE;
			// �e�N�X�`���ʒu
			Type = i % BALL_TYPE_MAX;
			Src.x = (Type % 3) * BALL_SIZE;
			Src.y = (Type / 3) * BALL_SIZE;
			Src.w = BALL_SIZE;
			Src.h = BALL_SIZE;
			// �X�v���C�g�ɕ`������N�G�X�g
			LueSprite2D_DrawSquare( lSpr, Dst, Src, LUE_RGB(255,255,255) ); 
		}

		// �X�v���C�g�ւ̕`�抮����ʒm
		LueSprite2D_End( lSpr );

		///////////////////////////////////////////////////////////////// �����_���[�ւ̕`�揈��

		// �`��J�n�錾
		LueRender_SceneStart();

		// �X�v���C�g�o�b�t�@�̓��e����ʂɕ`��
		LueSprite2D_Rendering( lSpr );

		// �`��I���錾
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// �I������
	//--------------------------------------------------------
	// �쐬�����X�v���C�g�����
	LueSprite2D_Release( lSpr );
	// �ǂݍ��񂾃e�N�X�`�������
	LueTexture_Release( hTex );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


