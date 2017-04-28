

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// PROTOTYPE
//=============================================================================
static BOOL FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter );


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// ��ʉ���
#define SCREEN_HEIGHT	(480)		// ��ʏc��


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
	LUE_HANDLE hSound;			// �T�E���h�n���h��
	char FilePath[MAX_PATH];

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
	// �T�E���h�t�@�C���̓ǂݍ���
	//--------------------------------------------------------
	if ( !FileOpenDialog( FilePath, "�T�E���h�I��", "�T�E���h�t�@�C��(*.wav *.ogg)\0*.wav;*.ogg\0\0" ) )
	{
		// �t�@�C�����ǂݍ��߂Ȃ�����
		Lue_Finalize();
		return 1;
	}

	//--------------------------------------------------------
	// �T�E���h�t�@�C����ǂݍ��݂܂��B
	//   Lue�ł̓T�E���h�̃h���C�o��Ayame���̗p���Ă���̂ŁA
	//   Ayame�őΉ����Ă���T�E���h�t�H�[�}�b�g���g���܂��B
	//   ��̓I�� �����kwave�A���kwave�AOggVorbis ��3��ނł��B
	//--------------------------------------------------------
	hSound = LueSound_CreateFromFile( FilePath, LFALSE );

	// �T�E���h�̍Đ�
	LueSound_Loop(
		hSound,					// �T�E���h�n���h��
		SOUND_LOOP_INFINITY,	// ���[�v�񐔁i����
		0 );					// ���[�v��̐擪�ʒu�i�T���v�����O�w��

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
	// �T�E���h�t�@�C���̉��
	//--------------------------------------------------------
	LueSound_Release( hSound );

	//--------------------------------------------------------
	// Lue�I��
    //   Lue�Ŏg�p���Ă���S�f�[�^��������܂��B
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}

//=============================================================================
/**
	@brief �t�@�C���I��p�_�C�A���O�������܂��B

	@param pPath	[out] �t�@�C�����i�[�����p�X�iMAX_PATH�o�C�g��char�z��j
	@param pTitle	[in] �_�C�A���O�̃^�C�g��
	@param pFilter	[in] �g���q�̎w��
	@param pExt		[in] �g���q

	@retval true	����
	@retval false	���s
*/
//=============================================================================
BOOL FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter )
{
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };
	ofn.hwndOwner		= GetActiveWindow();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= MAX_PATH;
	ofn.lpstrDefExt		= ".";
	ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	pPath[0] = '\0';

	return GetOpenFileName( &ofn );
}


