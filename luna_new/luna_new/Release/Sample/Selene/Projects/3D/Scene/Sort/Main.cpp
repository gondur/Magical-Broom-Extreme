

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

#define SPHERE_SIZE				(10)


//----------------------------------------------------------------------------------
// PROTOTYPE
//----------------------------------------------------------------------------------
static void CreateSphere( IPrimitive3D *pPrimitive, Float fSx, Float fSy, Float fSz, Uint32 Slices, Uint32 Stacks );


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
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IPrimitive3D *pPrimitive	= NULL;
	ISceneManager *pSceneMgr	= NULL;
	ISceneCamera *pCamera		= NULL;

	CStyle Style;

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
		pCamera->UpdateProjection( 1.0f, 1000.0f, DEG_TO_ANGLE(45), SCREEN_WIDTH, SCREEN_HEIGHT );

		//-----------------------------------------------------------------
		// �`��I�u�W�F�N�g����
		//-----------------------------------------------------------------
		// 3D�v���~�e�B�u�𐶐�
		//   IPrimitive3D�͍ł��჌�x���Ȃ�C���^�[�t�F�C�X�ł��B
		//   �����Œ��_�f�[�^�A�C���f�b�N�X�f�[�^��ݒ肵�����_�����O���s���܂��B
		//   VERTEX_ELEMENT_3DBASE       �ʒu�E�F�̊܂܂ꂽ�K�{�t���O�ł��B
		pPrimitive = pRender->CreatePrimitive3D( 1500, 6000, VERTEX_ELEMENT_3DBASE, false );

		// ������
		//   �֐����ŋ��̃f�[�^���쐬���Ă��܂��B
		// �f�[�^�ǉ��J�n
		pPrimitive->Begin();
		// ������
		CreateSphere( pPrimitive, SPHERE_SIZE, SPHERE_SIZE, SPHERE_SIZE, 24, 24 );
		// �f�[�^�ǉ�����
		pPrimitive->End();

		// �}�e���A���̐F��ύX
		//   �����ł͔�������
		pPrimitive->SetMaterialColor( CColor(255,255,255,128) );

		//-----------------------------------------------------------------
		// �`��X�e�[�g
		//-----------------------------------------------------------------
		// �`�惂�[�h�ݒ�
		//   �`�惂�[�h��ݒ肵�Ă��܂��B
		//   �������u�����hON
		pRender->SetDrawType( DRAW_TYPE_BLEND );

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
			////////////////////////////////////////////////////////////////////////////////////////////

			// ����ʂ̃N���A
			pDevice->Clear( 0x00303030 );

			////////////////////////////////////////////////////////////////////////////////////////////

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

			////////////////////////////////////////////////////////////////////////////////////////////

			// �V�[����񃊃Z�b�g
			//   ISceneManager�C���^�[�t�F�C�X���g�����V�[���Ǘ��������������܂��B
			pSceneMgr->Reset();

			// �J�����̈ړ��E��]
			//   CStyle�N���X�ŕϊ������������̂�
			//   �J�����ɓn���܂��B
			CVector3D vEye( Math::Cos(pCore->GetSyncCount()*64)*300.0f, 70.0f, Math::Sin(pCore->GetSyncCount()*64)*300.0f );
			CVector3D vAt( 0.0f, 1.0f, 0.0f );
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

			// �V�[���Ǘ�
			//   ISceneManager�C���^�[�t�F�C�X���g�����V�[���Ǘ����J�n���܂��B
			//   �������̃��f����`�悷��̂Ő������o��悤�Ƀ\�[�g���s���B
			pSceneMgr->Begin( true );

			// �t�H�OOFF
			//   �V�[���ւ̃t�H�O�̓K�p��OFF
			pSceneMgr->SetFogEnable( false );

			// �����_�����O
			//   IPrimitive3D�C���^�[�t�F�C�X�̓��e��`�悵�܂��B
			//   ���̊֐��ł�IRender�C���^�[�t�F�C�X�Ɋ֘A�t����ꂽISceneManager�C���^�[�t�F�C�X�ɑ΂���
			//   �`�惊�N�G�X�g�𔭍s���邾���ŁA�`���҂����ɋA���Ă��܂��B

			Sint32 Cnt = 4;
			for ( Sint32 i = -Cnt; i <= +Cnt; i++ )
			{
				for ( Sint32 j = -Cnt; j <= +Cnt; j++ )
				{
					// �v���~�e�B�u�̕ϊ�����
					//   CStyle�̕ϊ���IPrimitive3D�ɓn���Ă��܂��B
					Style.TransformReset();
					Style.Translation( toF(i*25), 0.0f, toF(j*25) );
					Style.TransformUpdate();

					pPrimitive->SetTransform( Style );
					pPrimitive->Rendering();
				}
			}

			// �V�[���Ǘ����I��
			//   �����܂łō\�z���ꂽ�V�[���������Ɏ��ۂɕ`��p�f�[�^�̍\�z���s���܂��B
			pSceneMgr->End();

			////////////////////////////////////////////////////////////////////////////////////////////
		}

EXIT:
		// �v���~�e�B�u�̉��
		SAFE_RELEASE( pPrimitive );

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

//----------------------------------------------------------------------------------
/**
*/
//----------------------------------------------------------------------------------
void CreateSphere( IPrimitive3D *pPrimitive, Float fSx, Float fSy, Float fSz, Uint32 Slices, Uint32 Stacks )
{
	SVertex3DBase v1;
	SVertex3DTexture v2;
	SVertex3DLight v3;

	CVector3D vTemp;
	CMatrix Mtx;

	pPrimitive->Begin();

	//=============================================================
	// ���_�f�[�^����
	//=============================================================
	{
		Float fHorz = PI2 / (Stacks);
		Float fVert = PI  / (Slices-1);

		Sint32 Num = 0;
		for ( Uint32 i = 0; i < Slices; i++ )
		{
			CVector3D Vertex( 0, 1, 0 );

			Mtx.RotationX( PI_TO_ANGLE(fVert * i) );
			vTemp.TransformNormal( Vertex, Mtx );

			for ( Uint32 j = 0; j < Stacks+1; j++ )
			{
				Mtx.RotationY( PI_TO_ANGLE( PI2 - fHorz * j ) );
				Vertex.TransformCoord( vTemp, Mtx );

				CVector3D vNorm;
				CVector3D vPos( Vertex.x * fSx, Vertex.y * fSy, Vertex.z * fSz );
				CVector2D vUV( 1.0f - toF(j)/toF(Stacks), (1.0f - Vertex.y) * 0.5f );
				vNorm.Normalize( vPos );

				v1.Pos = vPos;							// ���_���W
				v1.Col = 0xFFFFFFFF;					// ���_�F
				v2.TexColor = vUV;						// �e�N�X�`��UV
				v2.TexLight = vUV;						// �e�N�X�`��UV
				v3.Norm = vNorm;						// �@��

				pPrimitive->Push( &v1, 1 );
				pPrimitive->Push( &v2, 1 );
				pPrimitive->Push( &v3, 1 );

				Num++;
			}
		}
	}

	//=============================================================
	// �C���f�b�N�X����
	//=============================================================
	{
		Sint32 Num = 0;
		for ( Uint32 i = 1; i < Slices; i++ )
		{
			for ( Uint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks+1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pPrimitive->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}
	}

	pPrimitive->End();
}



