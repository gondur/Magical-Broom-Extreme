

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueCore.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
#define VERSION_NO_HIGH		0
#define VERSION_NO_LOW		1


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern HINSTANCE GetDLLInstance( void );
extern void LueTexture_Initialize( void );
extern void LueTexture_Finalize( void );
extern void LueSurface_Initialize( void );
extern void LueSurface_Finalize( void );
extern void LueFontSprite2D_Initialize( void );
extern void LueFontSprite2D_Finalize( void );
extern void LueSprite2D_Initialize( void );
extern void LueSprite2D_Finalize( void );
extern void LuePrimitive2D_Initialize( void );
extern void LuePrimitive2D_Finalize( void );
extern void LueLinePrimitive2D_Initialize( void );
extern void LueLinePrimitive2D_Finalize( void );
extern void LuePointPrimitive2D_Initialize( void );
extern void LuePointPrimitive2D_Finalize( void );
extern void LueSound_Initialize( void );
extern void LueSound_Finalize( void );
extern void LueRender_Initialize( void );
extern void LueRender_Finalize( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ICore *g_pCore				= NULL;
static IGraphicCard *g_pGraphicCard	= NULL;
static IDevice *g_pDevice			= NULL;
static IRender *g_pRender			= NULL;
static IFileManager *g_pFileMgr		= NULL;
static IMouse *g_pMouse				= NULL;
static IKeyboard *g_pKeyboard		= NULL;


//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���̏��������s���܂�
	@author �t���`

	@param pAppName		[in] �A�v���P�[�V������
	@param ScreenW		[in] ��ʉ���
	@param ScreenH		[in] ��ʏc��
	@param FrameRate	[in] �t���[�����[�g
	@param IsWindowMode	[in] �E�B���h�E���[�h�ŋN�����邩�ǂ���
	@param Type			[in] �g�p����API�i���݂� LAPI_TYPE_DIRECTX9 �Œ�j

	@retval LTRUE	����������
	@retval LFALSE	���������s

	Lue�V�X�e���̏������������s���܂��B<BR>
	���̊֐������������i�K�ł��ׂĂ�Lue�n�̊֐����g�����Ƃ��\�ɂȂ�܂��B
*/
//------------------------------------------------------------------------------------------------
eLueBool Lue_Initialize( const char *pAppName, unsigned int ScreenW, unsigned int ScreenH, eLueFrameRata FrameRate, eLueBool IsWindowMode, eLueAPIType Type )
{
	HICON hIcon;
	wchar_t wTemp[128] = L"";
	MBCStoWCS( pAppName, wTemp );

	// ���d�N���͋����Ȃ�
	if ( !System::BlockDualBoot( wTemp ) )
	{
		::MessageBox( ::GetDesktopWindow(), L"���ɓ����̃A�v���P�[�V�������N�����Ă��܂��B", L"�G���[", MB_ICONERROR );
		return LFALSE;
	}

	// �V�X�e��������
	if ( !System::Initialize() ) goto EXIT;

	// �R�A�̐���
	g_pCore = System::CreateCore();
	if ( g_pCore == NULL ) goto EXIT;

	// �R�A�̏�����
	if ( !g_pCore->Initialize( wTemp, (eFrameRate)FrameRate ) )
	{
		goto EXIT;
	}

	// �O���t�B�b�N�J�[�h���擾
	g_pGraphicCard = g_pCore->CreateGraphicCard( 0, VERTEXSHADER_VERSION_2_0 );
	if ( g_pGraphicCard == NULL ) goto EXIT;

	// �A�C�R��
	hIcon = (HICON)::LoadImage( GetDLLInstance(), L"ICON_SMALL", IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( g_pCore->GetWindowHandle(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon );
	hIcon = (HICON)::LoadImage( GetDLLInstance(), L"ICON_BIG", IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( g_pCore->GetWindowHandle(), WM_SETICON, ICON_BIG, (LPARAM)hIcon );

	g_pCore->Start( ScreenW, ScreenH, IsWindowMode != LFALSE );

	g_pDevice = g_pGraphicCard->CreateDevice();
	if ( g_pDevice == NULL ) goto EXIT;

	// �����_���[���擾
	g_pRender = g_pDevice->CreateRender();
	if ( g_pRender == NULL ) goto EXIT;

	// �e�I�u�W�F�N�g������
	LueSurface_Initialize();
	LueTexture_Initialize();
	LueLinePrimitive2D_Initialize();
	LuePointPrimitive2D_Initialize();
	LuePrimitive2D_Initialize();
	LueSprite2D_Initialize();
	LueFontSprite2D_Initialize();
	LueSound_Initialize();

	// �����_���[������
	LueRender_Initialize();

	// �t�@�C���o�^
	g_pFileMgr = g_pCore->CreateFileMgr();
	g_pCore->SetFileManager( g_pFileMgr );

	// �}�E�X�擾
	g_pMouse = g_pCore->GetMouse();

	// �L�[�{�[�h�擾
	g_pKeyboard = g_pCore->GetKeyboard();

	return LTRUE;

EXIT:
	Lue_Finalize();

	return LFALSE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���̏I��
	@author �t���`

	Lue�V�X�e�������ׂĉ�����܂��B<BR>
	���̊֐����Ă΂ꂽ���Lue�n�̊֐����Ăяo�����Ƃ͋֎~����Ă��܂��B
*/
//------------------------------------------------------------------------------------------------
void Lue_Finalize( void )
{
	LueRender_Finalize();

	LueFontSprite2D_Finalize();
	LueSprite2D_Finalize();
	LuePrimitive2D_Finalize();
	LueLinePrimitive2D_Finalize();
	LuePointPrimitive2D_Finalize();
	LueTexture_Finalize();
	LueSurface_Finalize();
	LueSound_Finalize();

	// �L�[�{�[�h���
	SAFE_RELEASE( g_pKeyboard );

	// �}�E�X���
	SAFE_RELEASE( g_pMouse );

	// �t�@�C�����
	SAFE_RELEASE( g_pFileMgr );

	// �����_���[���
	SAFE_RELEASE( g_pRender );

	// �f�o�C�X���
	SAFE_RELEASE( g_pDevice );

	// �r�f�I�J�[�h
	SAFE_RELEASE( g_pGraphicCard );

	// �R�A���
	SAFE_RELEASE( g_pCore );

	// �V�X�e���I��
	System::Finalize();
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���Ŏg�p���Ă���R�A�I�u�W�F�N�g�擾
	@author �t���`

	@return Lue�R�A�C���^�[�t�F�[�X

	�V�X�e�������Ŏg�p���Ă���Lue�̃R�A���擾���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
ICore *Lue_GetCore( void )
{
	return g_pCore;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���Ŏg�p���Ă���f�o�C�X�擾
	@author �t���`

	@return Lue�f�o�C�X�C���^�[�t�F�[�X

	�V�X�e�������Ŏg�p���Ă���Lue�̃f�o�C�X���擾���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
IDevice *Lue_GetDevice( void )
{
	return g_pDevice;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���Ŏg�p���Ă��郌���_���[�擾
	@author �t���`

	@return Lue�����_���[�C���^�[�t�F�[�X

	�V�X�e�������Ŏg�p���Ă���Lue�̃����_���[���擾���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
IRender *Lue_GetRenderer( void )
{
	return g_pRender;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���Ŏg�p���Ă���}�E�X�擾
	@author �t���`

	@return Lue�}�E�X�C���^�[�t�F�[�X

	�V�X�e�������Ŏg�p���Ă���Lue�̃}�E�X���擾���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
IMouse *Lue_GetMouse( void )
{
	return g_pMouse;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���Ŏg�p���Ă���L�[�{�[�h�擾
	@author �t���`

	@return Lue�L�[�{�[�h�C���^�[�t�F�[�X

	�V�X�e�������Ŏg�p���Ă���Lue�̃L�[�{�[�h���擾���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
IKeyboard *Lue_GetKeyboard( void )
{
	return g_pKeyboard;
}

//------------------------------------------------------------------------------------------------
/**
	@brief Lue�V�X�e���̃��C������
	@author �t���`

	@param IsActive	[in] LTRUE �̎��A�t�H�[�J�X�������Ă����삵������B

	@retval LTRUE	�A�v���P�[�V�������쒆
	@retval LFALSE	�A�v���P�[�V������~

	Lue�V�X�e���̃��C���������s���܂��B<BR>
	���t���[���Ăяo���悤�ɂ��Ă��������B<BR>
	�܂��Ԃ�l��LFALSE�̂Ƃ��͒����Ƀ��C�����[�v���甲���ĉ������B
*/
//------------------------------------------------------------------------------------------------
eLueBool Lue_Run( eLueBool IsActive )
{
	// ���b�Z�[�W����
	if ( !Lue_GetCore()->Run( IsActive != LFALSE ) )
	{
		return LFALSE;
	}

	g_pDevice->Clear();

	return LTRUE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief �o�[�W����������擾
	@author �t���`

	@param pStr		[out] �o�[�W����������i�[��
	@param Size		[in] pStr�̃o�b�t�@�T�C�Y

	Lue�̃o�[�W�����𕶎���Ŏ擾���܂��B<BR>
	���̊֐����Ăяo�����Ƃ� DLL �̃o�[�W�������擾���邱�Ƃ��\�ł��B
*/
//------------------------------------------------------------------------------------------------
void Lue_GetVersionString( char *pStr, unsigned int Size )
{
	sprintf_s( pStr, Size, "\"Lue for DirectX9.0c\" Phase %02d.%02d", VERSION_NO_HIGH, VERSION_NO_LOW );
}

//------------------------------------------------------------------------------------------------
/**
	@brief �o�[�W�����ԍ��擾
	@author �t���`

	@return �o�[�W�����ԍ�

	Lue�̃o�[�W�����𐔒l�Ŏ擾���܂��B<BR>
	���16Bit�Ƀ��W���[�o�[�W�����A����16Bit�Ƀ}�C�i�[�o�[�W�������i�[����Ă��܂��B
*/
//------------------------------------------------------------------------------------------------
unsigned int Lue_GetVersionNumber( void )
{
	return (VERSION_NO_HIGH << 16) | (VERSION_NO_LOW << 0);
}

//------------------------------------------------------------------------------------------------
/**
	@brief OS�N������̎��Ԏ擾
	@author �t���`

	@return 1/1000�b�P�ʂ̎���

	OS���N�����Ă���̎��Ԃ��擾���܂��B<BR>
	32Bit�ϐ��Ȃ̂Ŗ�48����1������0�ɖ߂��Ă��܂��܂��B
*/
//------------------------------------------------------------------------------------------------
unsigned int Lue_GetTime( void )
{
	return ::timeGetTime();
}


} // extern "C"

