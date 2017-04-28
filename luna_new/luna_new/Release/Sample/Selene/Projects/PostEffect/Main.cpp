

//----------------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------------
#include "../../../../Include/Selene.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define SCREEN_WIDTH			(256*2)
#define SCREEN_HEIGHT			(256*2)


//-----------------------------------------------------------------------------------
/**
	��ʓI�ȃE�B���h�E�Y�A�v���P�[�V�����ł�main()�֐��ɑ���������̂ł��B

	@param hInstance		[in] �C���X�^���X�̃n���h��
	@param hPrevInstance	[in] Win3.1����̖��c�iNULL)
	@param lpCmdLine		[in] �R�}���h���C�����i�[���ꂽ������ւ̃|�C���^
	@param nCmdShow			[in] �E�B���h�E���ǂ̂悤�ɕ\�����邩�̎w��

	@return		�I���R�[�h
*/
//-----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ICore *pCore				= NULL;
	IFileManager *pFileMgr		= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IPostEffect *pPostEffect	= NULL;
	ITexture *pTexBase			= NULL;
	ITexture *pTexRule			= NULL;

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
		// �t�@�C���o�^
		//-----------------------------------------------------------------
		// �t�@�C���}�l�[�W���[�𐶐�
		pFileMgr = pCore->CreateFileMgr();
		// �R�A�ɐݒ�
		pCore->SetFileManager( pFileMgr );
		// �ǂݍ��ݐ惋�[�g�f�B���N�g���ݒ�
		pFileMgr->SetLoadPath( 0, L"Data", L"Data.bin" );
		// ���[�g�f�B���N�g���ɑ΂��ēǂݍ��ރJ�����g�f�B���N�g���ݒ�
		pFileMgr->SetCurrentDirectory( L"PostEffect" );

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
		// �|�X�g�G�t�F�N�g�C���^�[�t�F�C�X�擾
		//-----------------------------------------------------------------
		// �쐬���������_���[�����ʕ`��p�̃|�X�g�G�t�F�N�g���擾���܂��B
		pPostEffect = pRender->CreatePostEffect();
		if ( pPostEffect == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// �e�N�X�`���ǂݍ���
		//-----------------------------------------------------------------
		pTexBase = pRender->CreateTextureFromFile( L"Base.bmp" );
		pTexRule = pRender->CreateTextureFromFile( L"Rule.bmp" );

		//-----------------------------------------------------------------
		// �`��X�e�[�g
		//-----------------------------------------------------------------
		// �`�惂�[�h�ݒ�
		//   �`�惂�[�h��ݒ肵�Ă��܂��B
		//   �����ł͂��̂܂܂̏�Ԃŕ`�悵�܂��B
		pRender->SetDrawType( DRAW_TYPE_BLEND );

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
			// ��ʂւ̃����_�����O
			/////////////////////////////////////////////////////////////////////////////////////////////

			// ��ʂւ̕`����J�n
			//   IRender�C���^�[�t�F�C�X�։�ʂւ̕`����J�n���邱�Ƃ�ʒm���܂��B
			//   ���̊֐����Ă΂Ȃ��Ɖ�ʂւ̕`�悪�������s���܂���B
			pRender->Begin();

			// 0.0�`1.0
			Float fRate = (Math::Cos( pCore->GetSyncCount() * 256 ) + 1.0f) * 0.5f;

			// �e�N�X�`����p�����P���ȃ����_�����O
			{
				CRect2D<Sint32> Dst( 0, 0, 256, 256 );
				CRect2D<Sint32> Src( 0, 0, 256, 256 );
				pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, pTexBase );
			}

			// �e�N�X�`�����O���[�X�P�[�������ă����_�����O
			// �s�N�Z���V�F�[�_�[1.1�T�|�[�g�K�{
			{
				CRect2D<Sint32> Dst( 256, 0, 256, 256 );
				CRect2D<Sint32> Src(   0, 0, 256, 256 );
				pPostEffect->Grayscale( Dst, 0xFFFFFFFF, Src, pTexBase, fRate );
			}

			// ���[���摜��p���ă��j�o�[�T���g�����W�V����
			// �s�N�Z���V�F�[�_�[1.1�T�|�[�g�K�{
			{
				CRect2D<Sint32> Dst( 0, 256, 256, 256 );
				CRect2D<Sint32> SrcBase( 0, 0, 256, 256 );
				CRect2D<Sint32> SrcRule( 0, 0, 128, 128 );
				pPostEffect->UniversalTransition( Dst, fRate, SrcBase, pTexBase, SrcRule, pTexRule );
			}

			// �e�N�X�`�����ڂ����ă����_�����O
			// �s�N�Z���V�F�[�_�[1.1�T�|�[�g�K�{
			{
				CRect2D<Sint32> Dst( 256, 256, 256, 256 );
				CRect2D<Sint32> Src(   0, 0, 256, 256 );
				pPostEffect->Blur16Box( Dst, 0xFFFFFFFF, Src, pTexBase );
			}

			// ��ʂւ̕`�������
			//  IRender�C���^�[�t�F�C�X�ɑ΂��āA
			//  ��ʂւ̕`�悪�����������Ƃ�ʒm���܂��B
			pRender->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
		}

EXIT:
		// �e�N�X�`���̉��
		SAFE_RELEASE( pTexRule );
		SAFE_RELEASE( pTexBase );

		// �|�X�g�G�t�F�N�g�̉��
		SAFE_RELEASE( pPostEffect );

		// �����_���[�̉��
		SAFE_RELEASE( pRender );

		// �f�o�C�X�̉��
		SAFE_RELEASE( pDevice );

		// �O���t�B�b�N�J�[�h�̉��
		SAFE_RELEASE( pGraphicCard );

		// �t�@�C���}�l�[�W���[���
		SAFE_RELEASE( pFileMgr );
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

