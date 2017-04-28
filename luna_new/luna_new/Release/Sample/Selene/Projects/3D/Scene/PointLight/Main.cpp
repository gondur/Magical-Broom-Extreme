

//----------------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------------
#include "../../../../../../Include/Selene.h"


//----------------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------------
using namespace Selene;


//----------------------------------------------------------------------------------
// DEFINE
//----------------------------------------------------------------------------------
#define SCREEN_WIDTH			(640)
#define SCREEN_HEIGHT			(480)


//----------------------------------------------------------------------------------
/**
	��ʓI�ȃE�B���h�E�Y�A�v���P�[�V�����ł�main()�֐��ɑ���������̂ł��B

	@param hInstance		[in] �C���X�^���X�̃n���h��
	@param hPrevInstance	[in] Win3.1����̖��c�iNULL)
	@param lpCmdLine		[in] �R�}���h���C�����i�[���ꂽ������ւ̃|�C���^
	@param nCmdShow			[in] �E�B���h�E���ǂ̂悤�ɕ\�����邩�̎w��

	@return		�I���R�[�h
*/
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ICore *pCore				= NULL;
	IFileManager *pFileMgr		= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IModel *pModel				= NULL;
	ISceneManager *pSceneMgr	= NULL;
	ISceneCamera *pCamera		= NULL;

	CStyle Style;
	Sint32 i, j, k;

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
		pFileMgr->SetCurrentDirectory( L"3D\\Scene" );

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
		// �V�[��
		//-----------------------------------------------------------------
		// �V�[���}�l�[�W���[���擾
		//   �����_���[�Ɋ֘A�t����ꂽ�V�[���Ǘ��p�̃C���^�[�t�F�C�X���擾���܂��B
		//   3D��Ԃ��̂��̂��Ǘ����Ă���̂ŁA���f���Ȃǂ̃����_�����O�ɕK�v�Ƃ��܂��B
		pSceneMgr = pRender->CreateSceneManager();
		pSceneMgr->SetRenderTargetSize( CPoint2D<Uint32>( SCREEN_WIDTH, SCREEN_HEIGHT ) );

		//-----------------------------------------------------------------
		// �J����
		//-----------------------------------------------------------------
		// �V�[������J�������擾
		//   �V�[��1�ɑ΂��āA1�̃J�������������Ă��܂��B
		//   �V�[���̃J�����𑀍삷�邽�߂ɁA�J�����̃C���^�[�t�F�C�X��
		//   �V�[������擾���܂��B
		pCamera = pSceneMgr->GetSceneCamera();
		// �J�����̃v���W�F�N�V������ݒ�
		//   �J�����̌�����͈͂ƌ�������ݒ肵�܂��B
		//   ������͈͂��L���قǂy�o�b�t�@�̐��x�̖���
		//   ������Ղ��Ȃ�̂Œ��ӂ��Đݒ肵�Ă��������B
		pCamera->UpdateProjection( 50.0f, 200.0f, DEG_TO_ANGLE(45), SCREEN_WIDTH, SCREEN_HEIGHT );

		//-----------------------------------------------------------------
		// �`��I�u�W�F�N�g����
		//-----------------------------------------------------------------
		// ���f���f�[�^�̓ǂݍ���
		//   Selene�ł͐�p�̃��f���t�H�[�}�b�g���̗p���Ă��܂��B
		//   ����͓ǂݍ��ݑ��x�̍�������e��t�����𓾂邽�߂ł��B
		//   ConvertX2SMF���g�����ƂŁAX�t�@�C������R���o�[�g���鎖���\�ł��B
		pModel = pRender->CreateModelFromFile( L"cube.smf" );

		//-----------------------------------------------------------------
		// �`��X�e�[�g
		//-----------------------------------------------------------------
		// �t�B���^�����O
		//   3D�p�̂����������掿�ȃt�B���^���g�p���܂��B
		pRender->SetTextureFilterType( 0, TEXTURE_FILTER_ANISOTROPY_LOW );

		// �[�x�����̃X�e�[�g�ݒ�
		//   �[�x�o�b�t�@�Ɋւ��Ă̐ݒ���s���܂��B
		//   �[�x�o�b�t�@�ւ̏������݂�L���ɂ��A
		//   �[�x�o�b�t�@�̃e�X�g��L���ɂ��Ă��܂��B
		pRender->SetDepthTestEnable( true );
		pRender->SetDepthWriteEnable( true );

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
			// �V�[���}�l�[�W���[�̓��e�����ۂɃ����_�����O
			/////////////////////////////////////////////////////////////////////////////////////////////

			// ��ʂւ̕`����J�n
			//   IRender�C���^�[�t�F�C�X�։�ʂւ̕`����J�n���邱�Ƃ�ʒm���܂��B
			//   ���̊֐����Ă΂Ȃ��Ɖ�ʂւ̕`�悪�������s���܂���B
			pRender->Begin();

			// �V�[���̓��e�������_�����O
			//   �����܂łō\�z���ꂽ�V�[���������Ɏ��ۂɕ`�揈�����s���܂��B
			//   ���̊֐���IRender::End()���Ăяo���O�łȂ���Ύ��s���܂��B
			pSceneMgr->Rendering();

			// ��ʂւ̕`�������
			//  IRender�C���^�[�t�F�C�X�ɑ΂��āA
			//  ��ʂւ̕`�悪�����������Ƃ�ʒm���܂��B
			pRender->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
			// �V�[�����\�z
			/////////////////////////////////////////////////////////////////////////////////////////////

			// �V�[����񃊃Z�b�g
			//   ISceneManager�C���^�[�t�F�C�X���g�����V�[���Ǘ��������������܂��B
			pSceneMgr->Reset();

			// �J�����̈ړ��E��]
			//   CStyle�N���X�ŕϊ������������̂�
			//   �J�����ɓn���܂��B
			CVector3D vEye( 0.0f, 50.0f, -100.0f );
			CVector3D vAt( 0.0f, 0.0f, 0.0f );
			CVector3D vUp( 0.0f, 1.0f, 0.0f );
			Style.TransformReset();
			Style.LookAt( vEye, vAt, vUp );
			Style.TransformUpdate();
			// �J�����̏�Ԃ�������
			pCamera->Reset();
			// CStyle�̕ϊ���K�p
			pCamera->SetTransform( Style );
			// �J�����̓����f�[�^�𗘗p�\�ȏ�ԂɍX�V
			//   ���̊֐����ĂԂ��ƂŎ��ۂɂ��̃J�����ł̃����_�����O�\�ɂȂ�܂��B
			pCamera->Update();

			// ���s����
			//   �V�[���ɑ΂��ĕ��s������ݒ肵�܂��B
			CVector3D vDir( 0.3f, -0.3f, 0.3f );
			CVector3D vCol( 0.1f, 0.1f, 0.1f );
			pSceneMgr->SetDirectionLight( vDir, vCol );

			// �A���r�G���g
			// �������C�e�B���O���s���Ă���̂ŁA�V���ƒn�\�̏Ƃ�Ԃ��̐F��ݒ肵�܂��B
			CVector3D vColSky( 0.2f, 0.2f, 0.2f );
			CVector3D vColEarth( 0.1f, 0.1f, 0.1f );
			pSceneMgr->SetAmbientLight( vColSky, vColEarth );

			// �|�C���g���C�g
			//   Selene�ł͂P�̃V�[���ɑ΂��čő�U�S�̃|�C���g���C�g���o�^�ł��A
			//   �e������ő�S�̃|�C���g���C�g���P��̃����_�����O�Ɏg���܂��B
			CVector3D vPos[] = {
				CVector3D(
					Math::Cos( pCore->GetSyncCount() * 512 ) * 25.0f,
					0.0f,
					Math::Sin( pCore->GetSyncCount() * 512 ) * 25.0f ),
				CVector3D(
					Math::Cos( pCore->GetSyncCount() * 384 ) * 25.0f,
					Math::Sin( pCore->GetSyncCount() * 384 ) * 25.0f,
					0.0f ),
				CVector3D(
					0.0f,
					Math::Sin( pCore->GetSyncCount() * 256 ) * 25.0f,
					Math::Cos( pCore->GetSyncCount() * 256 ) * 25.0f ),
			};
			CVector3D vColor[] = {
				CVector3D( 1.0f, 0.2f, 0.2f ),
				CVector3D( 0.2f, 1.0f, 0.2f ),
				CVector3D( 0.2f, 0.2f, 1.0f ),
			};
			for ( i = 0; i < 3; i++ )
			{
				pSceneMgr->AddPointLight( vPos[i], vColor[i], 40.0f );
			}

			/////////////////////////////////////////////////////////////////////////////////////////////
			// �V�[���ւ̃����_�����O���N�G�X�g
			/////////////////////////////////////////////////////////////////////////////////////////////

			// �V�[���Ǘ�
			//   ISceneManager�C���^�[�t�F�C�X���g�����V�[���Ǘ����J�n���܂��B
			pSceneMgr->Begin( false );

			// �����_�����O
			//   IModel�C���^�[�t�F�C�X�̓��e��`�悵�܂��B
			//   ���̊֐��ł�IRender�C���^�[�t�F�C�X�Ɋ֘A�t����ꂽISceneManager�C���^�[�t�F�C�X�ɑ΂���
			//   �`�惊�N�G�X�g�𔭍s���邾���ŁA�`���҂����ɋA���Ă��܂��B
			Sint32 Cnt = 3;
			Sint32 Angle = 0;
			for ( i = -Cnt; i <= +Cnt; i++ )
			{
				for ( j = -Cnt; j <= +Cnt; j++ )
				{
					for ( k = -Cnt; k <= +Cnt; k++ )
					{
						CPoint2D<Float> Pos( toF(i*8), toF(j*8) );
						Pos = Pos.Rotate( pCore->GetSyncCount() * 32 );

						// �v���~�e�B�u�̕ϊ�����
						//   CStyle�̕ϊ���IPrimitive3D�ɓn���Ă��܂��B
						Style.TransformReset();
						Style.Translation( Pos.x, toF(k*8), Pos.y );
						Style.RotationX( Angle + (pCore->GetSyncCount() * 128) );
						Style.RotationY( Angle + (pCore->GetSyncCount() *  64) );
						Style.TransformUpdate();

						pModel->SetTransform( Style );
						pModel->Rendering();

						Angle += 4096;
					}
				}
			}

			// �V�[���Ǘ����I��
			//   �����܂łō\�z���ꂽ�V�[���������Ɏ��ۂɕ`��p�f�[�^�̍\�z���s���܂��B
			pSceneMgr->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
		}

EXIT:
		// ���f���̉��
		SAFE_RELEASE( pModel );

		// �J�����̉��
		SAFE_RELEASE( pCamera );

		// �V�[���}�l�[�W���[���
		SAFE_RELEASE( pSceneMgr );

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
