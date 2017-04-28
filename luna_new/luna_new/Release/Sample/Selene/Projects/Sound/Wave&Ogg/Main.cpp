

//----------------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------------
#include "../../../../../Include/Selene.h"


//----------------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------------
using namespace Selene;


//----------------------------------------------------------------------------------
// PROTOTYPE
//----------------------------------------------------------------------------------
static BOOL FileOpenDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter );


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
	wchar_t FilePath[MAX_PATH];
	ICore *pCore			= NULL;
	ISound *pSound			= NULL;
	IFileManager *pFileMgr	= NULL;

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
		// �E�B���h�E�쐬
		//-----------------------------------------------------------------
		// ICore�C���^�[�t�F�C�X���̏��ɏ]���ăA�v���P�[�V����
		// �E�B���h�E�𐶐����܂��B
		// IGraphicCard����̏������ɉ�ʉ𑜓x�Ȃǂ�ύX����ꍇ�́A
		// ICore::Start()���Ăяo���O�ɍs���Ă��������B
		pCore->Start( SCREEN_WIDTH, SCREEN_HEIGHT, true );

		//--------------------------------------------------------
		// �t�@�C���o�^
		//--------------------------------------------------------
		// �t�@�C���}�l�[�W���[�𐶐�
		pFileMgr = pCore->CreateFileMgr();
		// �R�A�ɐݒ�
		pCore->SetFileManager( pFileMgr );

		//--------------------------------------------------------
		// �T�E���h�t�@�C���̓ǂݍ���
		//--------------------------------------------------------
		if ( !FileOpenDialog( FilePath, L"�T�E���h�I��", L"�T�E���h�t�@�C��(*.wav *.ogg)\0*.wav;*.ogg\0\0" ) )
		{
			// �t�@�C�����ǂݍ��߂Ȃ�����
			goto EXIT;
		}

		// �T�E���h�̓ǂݍ���
		//   �T�E���h���t�@�C���w�肵�ēǂݍ��݂܂��B
		//   �h���C�o�[��Ayame���g�p���Ă���̂ŁA
		//   WAVE/���kWAVE/OGG�̍Đ����s���܂��B
		pSound = pCore->CreateSoundFromFile( FilePath, false );
		if ( pSound == NULL )
		{
			goto EXIT;
		}

		// �T�E���h�̍Đ�
		pSound->Play(
			0xFFFFFFFF,				// ���[�v�񐔁i����
			0 );					// ���[�v��̐擪�ʒu�i�T���v�����O�w��

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
		}

EXIT:
		// �T�E���h�̉��
		SAFE_RELEASE( pSound );

		// �t�@�C���}�l�[�W���[�̉��
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

//----------------------------------------------------------------------------------
/**
	@brief �t�@�C���I��p�_�C�A���O�������܂��B

	@param pPath	[out] �t�@�C�����i�[�����p�X�iMAX_PATH�o�C�g��char�z��j
	@param pTitle	[in] �_�C�A���O�̃^�C�g��
	@param pFilter	[in] �g���q�̎w��
	@param pExt		[in] �g���q

	@retval true	����
	@retval false	���s
*/
//----------------------------------------------------------------------------------
BOOL FileOpenDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter )
{
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };
	ofn.hwndOwner		= GetActiveWindow();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= MAX_PATH;
	ofn.lpstrDefExt		= L".";
	ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	pPath[0] = L'\0';

	return GetOpenFileName( &ofn );
}


