

//=====================================================================
// INCLDUE
//=====================================================================
#include "Application.h"
#include "Io.h"
#include "BossLaser.h"

//=====================================================================
// STRUCT
//=====================================================================
// �R���t�B�O
typedef struct _CONFIGDATA
{
	unsigned char IsWindow;
	unsigned char IsFullColor;
	unsigned char IsFullColorTexture;
}
CONFIGDATA, *LPCONFIGDATA;

//=====================================================================
// GLOBAL
//=====================================================================
CList SpriteList;
LTEXTURE SubGraphic;
LSPRITE Sprite[10][2];
RECT RefreshSrc = { 0, 0, 640, 480 };
RECT RefreshDest = { 0, 0, 640, 480 };
long QuakePhase = -1;
long QuakeType = -1;
CONFIGDATA Config = { 0, 0, 0 };


//=====================================================================
//
//		�����ݒ�
//
//=====================================================================
void Luna::SetInfo( void )
{
	FILE *fp = fopen( "config.dat", "rb" );
	if ( fp != NULL )
	{
		fread( &Config, sizeof(CONFIGDATA), 1, fp );
		fclose( fp );
	}

	Luna::SetScreenMode( 640, 480, Config.IsWindow );

	// �E�B���h�E�^�C�g��
	Luna::SetWindowTitle( "�܂�����Ԃ�`�ނ������Ƃ股��" );

	// �X�N���[�����[�h���̐ݒ�
	if ( !Config.IsWindow )
	{
		// �}�E�X�̕\���ݒ�
		Luna::SetShowMouse( FALSE );
		// IME�ז��Ȃ̂ŏ���
		LunaSystem::SetShowIME( FALSE );
	}
	else
	{
		// FPS�\���ݒ�
		Luna::SetShowFPS( true );
	}

	// �t���J���[
	if ( Config.IsFullColor ) Luna3D::EnableFullColorMode();

	// �t���J���[�e�N�X�`��
	if ( Config.IsFullColorTexture ) Luna3D::EnableFullColorTexture();

	// ���O�t�@�C����
	Luna::SetLogFile( "Boot_Log.txt" );

	// FPS�ݒ�
	Luna::SetFPS( 50 );

	// �g�p����DirectX
	Luna::SetUseOption( USE_DIRECT3D | USE_DIRECTSOUND | USE_DIRECTINPUT );
}

//=====================================================================
//
//		����������
//
//=====================================================================
void Luna::Init( void )
{
	SpriteList.Init();

	// �O���t�B�b�N�ǂݍ���
	LTEXTURE Graphic = LunaTexture::LoadLAG( "graphic.lag", "graphic", TRUE );
	SubGraphic = LunaTexture::LoadLAG( "graphic.lag", "sub_graphic", TRUE );

	// �X�v���C�g����
	for ( long i = 0; i < 10; i++ )
	{
		if ( i == 6 )
		{
			Sprite[i][0] = LunaSprite::Create( 512, Graphic, BLEND_NORMAL );
			RECT uv = { 0 };
			Sprite[i][1] = LunaSprite::CreateLaser( LASER_DIV, &uv, Graphic, BLEND_ADD );
		}
		else
		{
			Sprite[i][0] = LunaSprite::Create( 512, Graphic, BLEND_NORMAL );
			Sprite[i][1] = LunaSprite::Create( 512, Graphic, BLEND_ADD );
		}
	}

	// �J��
	Graphic->Release();

	// �f�B�U
	Luna3D::SetRenderState( STATE_DITHER, ENABLE );

	// �o�C���j�A�t�B���^
	Luna3D::SetSmoothFilter( TRUE );

	// ������
	CApplication::Initialize();
}

//=====================================================================
//
//		�I������
//
//=====================================================================
void Luna::UnInit( void )
{
	// IME���A
	LunaSystem::SetShowIME( true );

	// �I��
	CApplication::UnInitialize();

	// �X�v���C�g
	for ( long i = 0; i < 8; i++ )
	{
		Sprite[i][0]->Release();
		Sprite[i][1]->Release();
	}

	SpriteList.Release();
	SubGraphic->Release();
}

//=====================================================================
//
//		���C�����[�v
//
//=====================================================================
void Luna::MainLoop( void )
{
	// �L�[���X�V
	IO::RefreshKeyState();

	// �V�[���Ăяo��
	CApplication::Main();

	// ��ʐU������
	QuakeScreen();

	// ��ʍX�V
	Luna3D::Refresh( &RefreshDest, &RefreshSrc );
}

//=====================================================================
//
//		��ʐU������
//
//=====================================================================
void QuakeScreen( void )
{
	static long Angle, Time;
	long x = 320, y = 240, scale = 0;

	switch ( QuakeType )
	{
	/////////////////////////////////////////////////////////// �c
	case 0:
		switch ( QuakePhase )
		{
		case 0:
			Angle = 0;
			Time = 0;
			QuakePhase++;
			break;
		case 1:
			scale = LunaMath::FlatSpeed( 6L, 0L, 50, Time );
			y = 240 + LunaMath::Sin( Angle+=384, scale );
			if ( ++Time == 50 ) QuakePhase++;
			break;
		}
		break;
	/////////////////////////////////////////////////////////// ��
	case 1:
		switch ( QuakePhase )
		{
		case 0:
			Angle = 0;
			Time = 0;
			QuakePhase++;
			break;
		case 1:
			scale = LunaMath::FlatSpeed( 8L, 0L, 50, Time );
			x = 320 + LunaMath::Sin( Angle+=384 , scale );
			if ( ++Time == 50 ) QuakePhase++;
			break;
		}
		break;
	}

	// �J�����ݒ�
	RECT src = { 0, 0, 640, 480 };
	RECT dest = { x-320, y-240, x+320, y+240 };
	SetCamera( &dest, &src );
}

//=====================================================================
//
//		��ʐU���ݒ�
//
//=====================================================================
void SetQuake( long type )
{
	QuakePhase = 0;
	QuakeType = type;
}

//=====================================================================
//
//		�X�V��ʐݒ�
//
//=====================================================================
void SetCamera( RECT *dest, RECT *src )
{
	RefreshDest = *dest;
	RefreshSrc = *src;
}