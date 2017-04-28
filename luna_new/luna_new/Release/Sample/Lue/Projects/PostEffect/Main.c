

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(256 * 2)		// ��ʉ���
#define SCREEN_HEIGHT	(256 * 2)		// ��ʏc��


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
	LUE_HANDLE hTexBase = INVALID_LUE_HANDLE;		// �e�N�X�`���n���h��
	LUE_HANDLE hTexRule = INVALID_LUE_HANDLE;		// �e�N�X�`���n���h��
	float fRate;

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
	LueFile_SetCurrentDirectory( "PostEffect" );

	//--------------------------------------------------------
	// �e�N�X�`���̓ǂݍ���
	//--------------------------------------------------------
	// �e�N�X�`�������p�̃I�v�V�����ݒ�
	LueTexture_SetConfig( LUE_ARGB(0,0,0,0) );

	// �摜�t�@�C������e�N�X�`���ǂݍ���
	//  DirectX�ň����e�N�X�`���̃T�C�Y�͂Q�̊K��ł���K�v������܂��B
	//  �P�ӂ̃s�N�Z������ 1�A2�A4�A8�A16�A32�A64�A128�A256�A512�A1024�A2048 �ł���K�v������܂��B
	hTexBase = LueTexture_CreateFromFile( "Base.bmp" );
	hTexRule = LueTexture_CreateFromFile( "Rule.bmp" );

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
		// 0�`1
		fRate = (LueMath_Sin( Lue_GetTime() * 16 ) + 1.0f) / 2.0f;

		// �`��J�n�錾
		LueRender_SceneStart();

		// �P���ȕ`��
		{
			LueRect Dst = { 0, 0, 256, 256 };	// �`��ʒu
			LueRect Src = { 0, 0, 256, 256 };	// �e�N�X�`���Q�ƈʒu
			// �`��
			LueRender_DrawSingleTexture( hTexBase, Dst, Src, LUE_RGB(255,255,255) );
		}
		// �O���[�X�P�[��
		{
			LueRect Dst = { 256, 0, 256, 256 };	// �`��ʒu
			LueRect Src = {     0, 0, 256, 256 };	// �e�N�X�`���Q�ƈʒu
			// �`��
			LueRender_DrawGrayscale( hTexBase, Dst, Src, LUE_RGB(255,255,255), fRate );
		}
		// ���j�o�[�T���g�����W�V����
		{
			LueRect Dst = { 0, 256, 256, 256 };	// �`��ʒu
			LueRect SrcBase = { 0,     0, 256, 256 };	// �e�N�X�`���Q�ƈʒu
			LueRect SrcRule = { 0,     0, 128, 128};	// �e�N�X�`���Q�ƈʒu
			// �`��
			LueRender_DrawUniversalTransition( hTexBase, hTexRule, Dst, SrcBase, SrcRule, fRate );
		}
		// �ڂ���
		{
			LueRect Dst = { 256, 256, 256, 256 };	// �`��ʒu
			LueRect Src = {   0,   0, 256, 256 };	// �e�N�X�`���Q�ƈʒu
			// �`��
			LueRender_DrawBlur16Box( hTexBase, Dst, Src, LUE_RGB(255,255,255) );
		}

		// �`��I���錾
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// �I������
	//--------------------------------------------------------
	// �ǂݍ��񂾃e�N�X�`�������
	LueTexture_Release( hTexRule );
	LueTexture_Release( hTexBase );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


