

//----------------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------------
#include "../../../../../Include/Selene.h"


//----------------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------------
using namespace Selene;


//----------------------------------------------------------------------------------
// DEFINE
//----------------------------------------------------------------------------------
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��


//----------------------------------------------------------------------------------
/**
	@brief ���C���֐�

	@param hInstance		[in] ���݂̃C���X�^���X�̃n���h��
	@param hPrevInstance	[in] �ȑO�̃C���X�^���X�̃n���h��
	@param lpCmdLine		[in] �R�}���h���C��
	@param nCmdShow			[in] �\�����

	�R���\�[���A�v���P�[�V�����ł������� main() �֐��ł��B
	�E�B���h�E�Y�A�v���P�[�V�����ł͈ȉ��̊֐��� main() �ɂȂ�܂��B
*/
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ICore *pCore				= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;

	//----------------------------------------------------------------------------
	// �V�X�e���̏�����
	//----------------------------------------------------------------------------
	// Selene�̃V�X�e�������������Ă��܂��B
	// �N�����ɕK���Ăяo���Ă��������B
	System::Initialize();

	//----------------------------------------------------------------------------
	// �R�A�̐���
	//----------------------------------------------------------------------------
	// �V�X�e������ICore�C���^�[�t�F�C�X���擾���Ă��܂��B
	// �v����ɃA�v���P�[�V�����E�B���h�E�ł��B
	// �X���b�h���ɕ����쐬���邱�ƂŃE�B���h�E����������܂��B
	pCore = System::CreateCore();

	//----------------------------------------------------------------------------
	// ������
	//----------------------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X�̏��������s���܂��B
	// �A�v���P�[�V�����E�B���h�E�Ɋւ��Ă̊e�평�������s���܂��B
	if ( pCore->Initialize( L"Selene Sample Program", FRAME_RATE_60 ) )
	{
		//-----------------------------------------------------------------
		// �O���t�B�b�N�J�[�h���擾
		//-----------------------------------------------------------------
		// �O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���܂��B
		// IGraphicCard�C���^�[�t�F�C�X����͐ڑ����ꂽ
		// �O���t�B�b�N�J�[�h�̔\�͂��擾���鎖���\�ł��B
		// IGraphicCard�C���^�[�t�F�C�X��1��ICore�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
		pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO, VERTEXSHADER_VERSION_2_0 );
		if ( pGraphicCard == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// �E�B���h�E�쐬
		//-----------------------------------------------------------------
		// ICore�C���^�[�t�F�C�X���̏��ɏ]���ăA�v���P�[�V����
		// �E�B���h�E�𐶐����܂��B
		// IGraphicCard����̏������ɉ�ʉ𑜓x�Ȃǂ�ύX����ꍇ�́A
		// ICore::Start()���Ăяo���O�ɍs���Ă��������B
		pCore->Start( SCREEN_WIDTH, SCREEN_HEIGHT, true );

		//-----------------------------------------------------------------
		// �f�o�C�X���擾
		//-----------------------------------------------------------------
		// IGraphicCard�Őڑ�����Ă���O���t�B�b�N�J�[�h����
		// �`��p�̃f�o�C�X���쐬���܂��B
		// IDevice�C���^�[�t�F�C�X��1��IGraphicCard�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
		pDevice = pGraphicCard->CreateDevice();
		if ( pDevice == NULL ) goto EXIT;

		//--------------------------------------------------------
		// ��ʂɕ����`��
		//   C�W����printf()�����̊֐��ł��B
		//   �E�B���h�E���R���\�[���Ɍ����Ăĕ�����`�悵�܂��B
		//--------------------------------------------------------
		pDevice->Printf( L"�ȈՕ����`��̃e�X�g\n" );
		pDevice->Printf( L"printf()�����̂��̂ł����������x���ėp��������܂���B\n" );
		pDevice->Printf( L"pDevice->Cls()���ĂԂ܂ŏ����������͏����܂���B\n" );
		pDevice->Printf( L"�f�o�b�O�p�Ƃ��Ċ��p���Ă��������B\n" );

		//-----------------------------------------------------------------
		// ���C�����[�v
		//-----------------------------------------------------------------
		// �A�v���P�[�V�����E�B���h�E�̃E�B���h�E���b�Z�[�W�̏����ƁA
		// ICore�C���^�[�t�F�C�X�o�R�Őݒ肳�ꂽ�t���[��������s���܂��B
		// �܂��L�[���͂̍X�V���ʂ̍X�V�����̊֐����ōs���܂��B
		// ���̊֐��̓E�B���h�E���I��������false��Ԃ��܂��B
		// ���̏ꍇ�A�������ɃA�v���P�[�V�������I������悤�ɂ��ĉ������B
		while ( pCore->Run() )
		{
			// ����ʂ̃N���A
			pDevice->Clear( 0x00303030 );
		}

EXIT:
		// �f�o�C�X�̉��
		SAFE_RELEASE( pDevice );

		// �O���t�B�b�N�J�[�h�̉��
		SAFE_RELEASE( pGraphicCard );
	}

	// �R�A�̉��
	SAFE_RELEASE( pCore );

	//--------------------------------------------------------
	// �V�X�e���̉��
	//--------------------------------------------------------
	// �A�v���P�[�V�����̏I�����ɕK���Ăяo���ĉ������B
	// �܂����̊֐����Ăяo���O�Ɏ擾�����S�Ă�
	// �C���^�[�t�F�C�X��������Ă��������B
	System::Finalize();

	return 0;
/*
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
	}

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();
*/
}

