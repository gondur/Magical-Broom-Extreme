

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Selene.h"


//=============================================================================
// NAMESPACE
//=============================================================================
using namespace Selene;


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��
#define FRAME_RATE		(60)		// �t���[�����[�g

#define PRIMITIVE_MAX	(64)		// �v���~�e�B�u��


//=============================================================================
/**
	@brief ���C���֐�

	@param hInstance		[in] ���݂̃C���X�^���X�̃n���h��
	@param hPrevInstance	[in] �ȑO�̃C���X�^���X�̃n���h��
	@param lpCmdPoint		[in] �R�}���h�v���~�e�B�u
	@param nCmdShow			[in] �\�����

	�R���\�[���A�v���P�[�V�����ł������� main() �֐��ł��B
	�E�B���h�E�Y�A�v���P�[�V�����ł͈ȉ��̊֐��� main() �ɂȂ�܂��B
*/
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdPoint, int nCmdShow )
{
	unsigned long ColTbl[] = {
		LUE_RGB(255,128,128), LUE_RGB(128,255,128), LUE_RGB(128,128,255),
	};

	LUE_HANDLE hPrimitive;
	LuePrimitiveVertex2D Prim[2];
	unsigned long Time;
	long i, Angle;

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
	// �v���~�e�B�u�p�`��I�u�W�F�N�g����
	//--------------------------------------------------------
	hPrimitive = LuePrimitive2D_Create( PRIMITIVE_MAX );

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
		Time = Lue_GetTime() * 8;

		///////////////////////////////////////////////////////////////// �v���~�e�B�u�ւ̕`�惊�N�G�X�g

		// �v���~�e�B�u�ւ̕`��J�n��ʒm
		LuePrimitive2D_Begin( hPrimitive );

		// �w�i�i�E��j
		Prim[0].v[0].Pos.x = 0.0f;
		Prim[0].v[0].Pos.y = 0.0f;
		Prim[0].v[0].Pos.z = 0.0f;
		Prim[0].v[0].Pos.w = 1.0f;
		Prim[0].v[0].Col = LUE_RGB(255,64,64);
		Prim[0].v[1].Pos.x = (float)SCREEN_WIDTH;
		Prim[0].v[1].Pos.y = 0.0f;
		Prim[0].v[1].Pos.z = 0.0f;
		Prim[0].v[1].Pos.w = 1.0f;
		Prim[0].v[1].Col = LUE_RGB(64,255,64);
		Prim[0].v[2].Pos.x = (float)SCREEN_WIDTH;
		Prim[0].v[2].Pos.y = (float)SCREEN_HEIGHT;
		Prim[0].v[2].Pos.z = 0.0f;
		Prim[0].v[2].Pos.w = 1.0f;
		Prim[0].v[2].Col = LUE_RGB(64,64,255);
		// �w�i�i�����j
		Prim[1].v[0].Pos.x = 0.0f;
		Prim[1].v[0].Pos.y = 0.0f;
		Prim[1].v[0].Pos.z = 0.0f;
		Prim[1].v[0].Pos.w = 1.0f;
		Prim[1].v[0].Col = LUE_RGB(64,64,255);
		Prim[1].v[1].Pos.x = 0.0f;
		Prim[1].v[1].Pos.y = (float)SCREEN_HEIGHT;
		Prim[1].v[1].Pos.z = 0.0f;
		Prim[1].v[1].Pos.w = 1.0f;
		Prim[1].v[1].Col = LUE_RGB(64,255,64);
		Prim[1].v[2].Pos.x = (float)SCREEN_WIDTH;
		Prim[1].v[2].Pos.y = (float)SCREEN_HEIGHT;
		Prim[1].v[2].Pos.z = 0.0f;
		Prim[1].v[2].Pos.w = 1.0f;
		Prim[1].v[2].Col = LUE_RGB(255,64,64);
		// �o�b�t�@�ɒǉ�
		LuePrimitive2D_Push( hPrimitive, Prim, 2 );

		// ���ŉ�]
		for ( i = 0; i < 3; i++ )
		{
			Angle = Time + (i * LUE_ANGLE_MAX / 3);
			Prim[0].v[i].Pos.x = (LueMath_Cos( Angle ) * 150.0f) + 160.0f;
			Prim[0].v[i].Pos.y = (LueMath_Sin( Angle ) * 200.0f) + 240.0f;
			Prim[0].v[i].Pos.z = 0.0f;
			Prim[0].v[i].Pos.w = 1.0f;
			Prim[0].v[i].Col = ColTbl[i];
		}
		// �o�b�t�@�ɒǉ�
		LuePrimitive2D_Push( hPrimitive, Prim, 1 );

		// �v���~�e�B�u�ւ̕`�抮����ʒm
		LuePrimitive2D_End( hPrimitive );

		///////////////////////////////////////////////////////////////// �����_���[�ւ̕`�揈��

		// �`��J�n�錾
		LueRender_SceneStart( LSCENE_2D_BACKGROUND );	// 2D�w�i�ŃV�[���J�n

		// �e�N�X�`���ݒ薳��
		LueRender_SetTexture( INVALID_LUE_HANDLE );

		// �v���~�e�B�u�o�b�t�@�̓��e����ʂɕ`��
		LuePrimitive2D_Render( hPrimitive );

		// �`��I���錾
		LueRender_SceneExit();

		///////////////////////////////////////////////////////////////// �v���~�e�B�u�ւ̕`�惊�N�G�X�g

		// �v���~�e�B�u�ւ̕`��J�n��ʒm
		LuePrimitive2D_Begin( hPrimitive );

		// �E�Ŕ�������]
		for ( i = 0; i < 3; i++ )
		{
			Angle = Time + (i * LUE_ANGLE_MAX / 3);
			Prim[0].v[i].Pos.x = (LueMath_Cos( Angle ) * 150.0f) + 480.0f;
			Prim[0].v[i].Pos.y = (LueMath_Sin( Angle ) * 200.0f) + 240.0f;
			Prim[0].v[i].Pos.z = 0.0f;
			Prim[0].v[i].Pos.w = 1.0f;
			Prim[0].v[i].Col = (ColTbl[i] & 0x00FFFFFF) | (0x80000000);
		}
		// �o�b�t�@�ɒǉ�
		LuePrimitive2D_Push( hPrimitive, Prim, 1 );

		// �v���~�e�B�u�ւ̕`�抮����ʒm
		LuePrimitive2D_End( hPrimitive );

		///////////////////////////////////////////////////////////////// �����_���[�ւ̕`�揈��

		// �`��J�n�錾
		LueRender_SceneStart( LSCENE_2D_FOREGROUND );	// 2D�O�i�ŃV�[���J�n

		// ������ON
		LueRender_SetDrawMode( LDRAW_MODE_BLEND );

		// �e�N�X�`���ݒ薳��
		LueRender_SetTexture( INVALID_LUE_HANDLE );

		// �v���~�e�B�u�o�b�t�@�̓��e����ʂɕ`��
		LuePrimitive2D_Render( hPrimitive );

		// �`��I���錾
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// �v���~�e�B�u�I�u�W�F�N�g���
	//--------------------------------------------------------
	LuePrimitive2D_Release( hPrimitive );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


