

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

#define FONT_MAX		(1024)		// �t�H���g�X�v���C�g��


//----------------------------------------------------------------------------------
/**
	@brief ���C���֐�

	@param hInstance		[in] ���݂̃C���X�^���X�̃n���h��
	@param hPrevInstance	[in] �ȑO�̃C���X�^���X�̃n���h��
	@param lpCmdPoint		[in] �R�}���h�t�H���g�X�v���C�g
	@param nCmdShow			[in] �\�����

	�R���\�[���A�v���P�[�V�����ł������� main() �֐��ł��B
	�E�B���h�E�Y�A�v���P�[�V�����ł͈ȉ��̊֐��� main() �ɂȂ�܂��B
*/
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdPoint, int nCmdShow )
{
	ICore *pCore				= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IFontSprite2D *pFontSpr		= NULL;
	IFileManager *pFileMgr		= NULL;

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
	// �A�v���P�[�V�����E�B���h�E�Ɋւ���C���^�[�t�F�C�X�ł���A
	// �V�X�e�����ɂP�������݂��܂��B
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
		// �t�@�C���o�^
		//-----------------------------------------------------------------
		// �t�@�C���}�l�[�W���[�𐶐�
		pFileMgr = pCore->CreateFileMgr();
		// �R�A�ɐݒ�
		pCore->SetFileManager( pFileMgr );
		// �ǂݍ��ݐ惋�[�g�f�B���N�g���ݒ�
		pFileMgr->SetLoadPath( 0, L"Data", L"Data.bin" );
		// ���[�g�f�B���N�g���ɑ΂��ēǂݍ��ރJ�����g�f�B���N�g���ݒ�
		pFileMgr->SetCurrentDirectory( L"2D\\FontSprite" );

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
		// �t�H���g�X�v���C�g����
		//-----------------------------------------------------------------
		pFontSpr = pRender->CreateFontSprite2DFromFile( L"Font.lfd", L"tga", FONT_MAX );
		if ( pFontSpr == NULL ) goto EXIT;

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
			/////////////////////////////////////////////////////////////////////////////////////////////
			// ��ʃN���A
			/////////////////////////////////////////////////////////////////////////////////////////////

			// ����ʂ̃N���A
			pDevice->Clear( 0x00303030 );

			/////////////////////////////////////////////////////////////////////////////////////////////
			// ��ʂւ̃t�H���g�X�v���C�g�̕`��
			/////////////////////////////////////////////////////////////////////////////////////////////

			// ��ʂւ̕`����J�n
			//   IRender�C���^�[�t�F�C�X�։�ʂւ̕`����J�n���邱�Ƃ�ʒm���܂��B
			//   ���̊֐����Ă΂Ȃ��Ɖ�ʂւ̕`�悪�������s���܂���B
			pRender->Begin();

			// �t�H���g�X�v���C�g�̃����_�����O
			//   �����ō쐬�����o�b�t�@����ʂɃ����_�����O���܂��B
			pFontSpr->Rendering();

			// ��ʂւ̕`�������
			//  IRender�C���^�[�t�F�C�X�ɑ΂��āA
			//  ��ʂւ̕`�悪�����������Ƃ�ʒm���܂��B
			pRender->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
			// �t�H���g�X�v���C�g�ւ̕`�惊�N�G�X�g
			/////////////////////////////////////////////////////////////////////////////////////////////

			// �t�H���g�X�v���C�g�ւ̕`��J�n��ʒm
			pFontSpr->Begin();

			// �t�H���g�X�v���C�g�ɑ΂��ĕ`��
			pFontSpr->DrawString( L"����Ղ�e�L�X�g", CPoint2D<Sint32>( 100, 100 ), CColor(255,255,255,255) );
			pFontSpr->DrawString( L"�ݶ��������܂�", CPoint2D<Sint32>( 100, 130 ), CColor(255,255,255,255) );
			pFontSpr->DrawString( L"ABCabc�`�a�b������012�O�P�Q", CPoint2D<Sint32>( 100, 160 ), CColor(255,255,255,255) );

			// �t�H���g�X�v���C�g�ւ̕`�抮����ʒm
			pFontSpr->End();
		}

EXIT:
		// �t�@�C���}�l�[�W���[���
		SAFE_RELEASE( pFileMgr );

		// �t�H���g�X�v���C�g�̉��
		SAFE_RELEASE( pFontSpr );

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
	System::Finalize();

	return 0;
}
