

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
	ICore *pCore				= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IFileManager *pFileMgr		= NULL;
	IMouse *pMouse				= NULL;

	CColor Color;

	//----------------------------------------------------------------------------
	// �V�X�e���̏�����
	//----------------------------------------------------------------------------
	// Selene�̃V�X�e�������������Ă��܂��B
	// �N�����ɕK���Ăяo���Ă��������B
	CSystem::Initialize();

	//----------------------------------------------------------------------------
	// �R�A�̐���
	//----------------------------------------------------------------------------
	// �V�X�e������ICore�C���^�[�t�F�C�X���擾���Ă��܂��B
	// �v����ɃA�v���P�[�V�����E�B���h�E�ł��B
	// �X���b�h���ɕ����쐬���邱�ƂŃE�B���h�E����������܂��B
	pCore = CSystem::CreateCore();

	//----------------------------------------------------------------------------
	// ������
	//----------------------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X�̏��������s���܂��B
	// �A�v���P�[�V�����E�B���h�E�Ɋւ��Ă̊e�평�������s���܂��B
	if ( pCore->Initialize( "Selene Sample Program", FRAME_RATE ) )
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

		//-----------------------------------------------------------------
		// �����_���[���擾
		//-----------------------------------------------------------------
		// �쐬�����f�o�C�X�����ʕ`��p�̃����_���[���擾���܂��B
		// IRender�C���^�[�t�F�C�X��1��IDevice�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
		pRender = pDevice->CreateRender();
		if ( pRender == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// �}�E�X�擾
		//-----------------------------------------------------------------
		pMouse = pCore->GetMouse();
		if ( pMouse == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// �t�@�C���o�^
		//-----------------------------------------------------------------
		// �t�@�C���}�l�[�W���[�𐶐�
		pFileMgr = pCore->CreateFileMgr();
		// �R�A�ɐݒ�
		pCore->SetFileManager( pFileMgr );
		// ���[�g�̃f�B���N�g����ݒ�
		pFileMgr->SetLoadPath( 0, "Data", "Data.bin" );
		pFileMgr->SetCurrentDirectory( "2D\\DrawTexture" );

		//-----------------------------------------------------------------
		// �`��X�e�[�g
		//-----------------------------------------------------------------
		// ���ʃ����_�����OOFF
		//   ���ʂ������_�����O���邩�ǂ����ł��B
		pRender->SetDoubleSide( false );
		// �J���[�L�[����OFF
		//   �e�N�X�`���J���[�L�[���������邩�ǂ����ł��B
		pRender->SetColorkeyEnable( false );
		// �`�惂�[�h�ݒ�
		//   �`�惂�[�h��ݒ肵�Ă��܂��B
		//   �����ł͂��̂܂܂̏�Ԃŕ`�悵�܂��B
		pRender->SetDrawMode( DRAW_MODE_NORMAL );

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
			/////////////////////////////////////////////////////////////// �}�E�X���͏���

			// �}�E�X�̈ʒu�ɊG��\��
			Px = Mouse.Px - (TEX_W / 2);
			Py = Mouse.Py - (TEX_H / 2);

			// ���N���b�N�Ő�
			if ( Mouse.ClickL )
			{
				Color = CColor(255,128,128);
			}
			// �E�N���b�N�ŗ�
			else if ( Mouse.ClickR )
			{
				Color = CColor(128,255,128);
			}
			//�z�C�[���N���b�N�Ő�

			else if ( Mouse.ClickW )
			{
				Color = CColor(128,128,255);
			}
			// ������Ă��Ȃ����͂��̂܂�
			else
			{
				Color = CColor(255,255,255);
			}

			//////////////////////////////////////////////////////////////// ��ʃN���A

			// ����ʂ̃N���A
			pDevice->Clear( 0x00303030 );

			//////////////////////////////////////////////////////////////// ��ʕ`��

			// ��ʂւ̕`����J�n
			//   IRender�C���^�[�t�F�C�X�։�ʂւ̕`����J�n���邱�Ƃ�ʒm���܂��B
			//   ���̊֐����Ă΂Ȃ��Ɖ�ʂւ̕`�悪�������s���܂���B
			pRender->Begin();

			// ��ʂւ̕`�������
			//  IRender�C���^�[�t�F�C�X�ɑ΂��āA
			//  ��ʂւ̕`�悪�����������Ƃ�ʒm���܂��B
			pRender->End();

			/////////////////////////////////////////////////////////////// �I���
		}

EXIT:
		// �t�@�C���}�l�[�W���[���
		SAFE_RELEASE( pFileMgr );

		// �}�E�X���
		SAFE_RELEASE( pMouse );

		// �����_���[�̉��
		SAFE_RELEASE( pRender );

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
	CSystem::Finalize();

	return 0;
/*
	LUE_HANDLE hTex = INVALID_LUE_HANDLE;		// �e�N�X�`���n���h��
	LueRect Dst, Src;							// �`��p��`
	long Px = (SCREEN_WIDTH  - TEX_W) / 2;		// �����ʒu
	long Py = (SCREEN_HEIGHT - TEX_H) / 2;		// �����ʒu
	LueMouseData Mouse;							// �}�E�X�p�\����
	unsigned long Color;						// �G�̐F

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
		/////////////////////////////////////////////////////////////// �}�E�X���͏���

		// �}�E�X�����擾
		Mouse = LueInput_GetMouseData();

		// �}�E�X�̈ʒu�ɊG��\��
		Px = Mouse.Px - (TEX_W / 2);
		Py = Mouse.Py - (TEX_H / 2);

		// ���N���b�N�Ő�
		if ( Mouse.ClickL )
		{
			Color = CColor(255,128,128);
		}
		// �E�N���b�N�ŗ�
		else if ( Mouse.ClickR )
		{
			Color = CColor(128,255,128);
		}
		//�z�C�[���N���b�N�Ő�

		else if ( Mouse.ClickW )
		{
			Color = CColor(128,128,255);
		}
		// ������Ă��Ȃ����͂��̂܂�
		else
		{
			Color = CColor(255,255,255);
		}

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
		LueTexture_Draw( hTex, Dst, Src, Color );

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
*/
	return 0;
}

