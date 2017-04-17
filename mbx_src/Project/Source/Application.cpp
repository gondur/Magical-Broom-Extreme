//======================================================================================
//======================================================================================
//
//
//			�A�v���P�[�V�������
//
//
//======================================================================================
//======================================================================================


//======================================================================================
//	include
//======================================================================================
#include <stdio.h>
#include "Application.h"
#include "Io.h"
#include "Event.h"
#include "CharaBase.h"
#include "Title.h"
#include "Window.h"
#include "Bonus.h"
#include "Bg.h"
#include "Snow.h"
#include "Scroll.h"
#include "Parts.h"
#include "Sound.h"
#include "Voice.h"


//======================================================================================
//
//	�f�[�^�����o
//
//======================================================================================
D3DCOLOR CApplication::FadeColor;
unsigned long CApplication::NoMissCounter;
unsigned long CApplication::EnemyDestroy;
LPCPLAYER CApplication::lpPlayer;
LPCWINDOW CApplication::lpWindow;
LPCCOMBO CApplication::lpCombo;
eScene CApplication::NowScene;
long CApplication::ScenePhase;
long CApplication::Difficulty;
long CApplication::Stage;

LPCSPRITE CApplication::EffectList[EFFECT_MAX];
unsigned long CApplication::EffectNum;

// �X�R�A�f�[�^
SCOREDATA CApplication::ScoreData[10] = 
{
	"RENGE",	1000000,
	"AYAME",	800000,
	"KIKYOU",	500000,
	"MADOKA",	300000,
	"KASUMI",	100000,
	"SAKURA",	80000,
	"YURI",		50000,
	"MOMIJI",	30000,
	"SUMIRE",	10000,
	"HANIWA",	1,
};

// �֐��e�[�u��
void (*CApplication::SceneFunc[sizeof_eScene])( void ) =
{
	CApplication::SceneLogo,
	CApplication::SceneTitle,
	CApplication::SceneStg,
	CApplication::SceneRanking,
	CApplication::SceneOption,
	CApplication::SceneGameover,
	CApplication::SceneClear,
};

//======================================================================================
//
//	�V�[���ݒ�
//
//======================================================================================
void CApplication::SetScene( eScene scene )
{
	NowScene = scene;
	ScenePhase = 0;
}

//======================================================================================
//
//	������
//
//======================================================================================
void CApplication::Initialize( void )
{
	EffectNum = 0;
	Difficulty = 1;

	// �T�E���h������
	CSound::Init();

	// �{�C�X������
	CVoice::Init();

	// �X�R�A�f�[�^�ǂݍ���
	LoadScore();

	// �ŏ��̃V�[����ݒ�
	SetScene( SCENE_LOGO );
}

//======================================================================================
//
//	�I��
//
//======================================================================================
void CApplication::UnInitialize( void )
{
	CVoice::Uninit();
	CSound::Uninit();
}

//======================================================================================
//
//	���C��
//
//======================================================================================
void CApplication::Main( void )
{
	//-------------------------------------------
	// ���X�g���Z����
	//-------------------------------------------
	// ���X�g�̐擪�擾
	LPCSPRITE p = (LPCSPRITE)SpriteList.Top();
	// ���X�g�̏I�[�܂ť��
	while ( p != NULL )
	{
		// ���炩���ߎ����擾
		LPCSPRITE _p = (LPCSPRITE)p->Next;
		// ����
		if ( p->Action() ) p->Release();
		// ��
		p = _p;
	}

	//-------------------------------------------
	// �`�揈��
	//-------------------------------------------
	if ( Luna3D::BeginScene() )
	{
		//-------------------------------------------
		// �e�V�[�����Ƃ̏���
		//-------------------------------------------
		SceneFunc[NowScene]();

		//-------------------------------------------
		// ��ʕ`��
		//-------------------------------------------
		for ( long i = 0; i < 10; i++ )
		{
			Sprite[i][0]->Rendering();
			Sprite[i][1]->Rendering();
		}
		// �G�t�F�N�g�̕`��
		ScreenEffect();

		//-------------------------------------------
		// �`��V�[���I��
		//-------------------------------------------
		Luna3D::EndScene();
	}

	//-------------------------------------------
	// �����蔻�菈��
	//-------------------------------------------
	AllHitCheck();
/*
	//-------------------------------------------
	// �f�o�b�O�p�f�[�^�\��
	//-------------------------------------------
	if ( Luna3D::BeginScene() )
	{
		// �����蔻��\��
		LunaEffect::Begin( BLEND_NORMAL );
		// ���X�g�̐擪�擾
		LPCSPRITE p = (LPCSPRITE)SpriteList.Top();
		// ���X�g�̏I�[�܂ť��
		while ( p != NULL )
		{
			if ( p->bHit )
			{
				// ����
				long cnt = p->HitCount-1;
				for ( long i = 0; i < cnt; i++ )
				{
					LunaEffect::Line(
							p->lpHitPt[i+0].x, p->lpHitPt[i+0].y,
							p->lpHitPt[i+1].x, p->lpHitPt[i+1].y,
							D3DCOLOR_XRGB(255,255,0) );
				}
			}
			// ��
			p = (LPCSPRITE)p->Next;
		}
		LunaEffect::End();

		// �`��V�[���I��
		Luna3D::EndScene();
	}
*/
}

//======================================================================================
//
//	���S
//
//======================================================================================
void CApplication::SceneLogo( void )
{
	static long FadeLevel;

	// �w�i
	Luna3D::ColorFill( D3DCOLOR_XRGB(255,255,255) );

	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- ������
	case 0:
		{
			CSound::Play( SE_LOGO );
			FadeLevel = 255;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�C��
	case 1:
		{
			// ���S
			RECT src = { 0, 411, 256, 488 };
			RECT dest = { 320-128, 240-40, 320+128, 240+37 }; 
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
			// ���X�Ƀt�F�[�h�C��
			SetFade( D3DCOLOR_ARGB(FadeLevel,0,0,0) );
			FadeLevel -= 2;
			if ( FadeLevel < 0 )
			{
				FadeLevel = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �E�F�C�g
	case 2:
		{
			// ���S
			RECT src = { 0, 411, 256, 488 };
			RECT dest = { 320-128, 240-40, 320+128, 240+37 };
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
			// �^�C�}�[����i1�b�ҋ@
			FadeLevel++;
			if ( FadeLevel > 50 )
			{
				FadeLevel = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�A�E�g
	case 3:
		{
			// ���S
			RECT src = { 0, 411, 256, 488 };
			RECT dest = { 320-128, 240-40, 320+128, 240+37 };
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
			// ���X�Ƀt�F�[�h�A�E�g
			SetFade( D3DCOLOR_ARGB(FadeLevel,0,0,0) );
			FadeLevel += 5;
			if ( FadeLevel > 255 )
			{
				Luna3D::Clear();
				// �^�C�g����ʂ�
				SetScene( SCENE_TITLE );
			}
		}
		break;
	}
}

//======================================================================================
//
//	�^�C�g��
//
//======================================================================================
void CApplication::SceneTitle( void )
{
	static LPCTITLE lpTitle[4];		// �^�C�g���\���p

	static long Select;
	static long FadeLevel;

	RECT src, dest;


	//-----------------------------------------------------------
	// �^�C�g�����
	//-----------------------------------------------------------
	if ( ScenePhase > 0 )
	{
		// �w�i
		SetRect( &dest, 0, 0, 640, 480 );
		D3DCOLOR color[] = {
			D3DCOLOR_XRGB(192,192,255),
			D3DCOLOR_XRGB(64,64,96),
			D3DCOLOR_XRGB(192,192,255),
			D3DCOLOR_XRGB(64,64,96),
		};
		LunaEffect::Begin( BLEND_NORMAL );
		LunaEffect::Gradation( &dest, color );
		LunaEffect::End();
		// �^�C�g��
		SetRect( &src, 0, 0, 512, 140 );
		SetRect( &dest, 320-256, 50, 320+256, 190 );
		SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
		// �^�C�g���I��
		for ( long i = 0; i < 4; i++ )
		{
			if ( lpTitle[i] != NULL )
			{
				lpTitle[i]->GetRect( &dest, &src );
				// �I�𒆂Ȃ疾�邭����
				if ( i == Select )
				{
					SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_ADD );
				}
				else
				{
					SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(32,64,64), BLEND_ADD );
				}
			}
		}
	}

	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- ������
	case 0:
		{
			CSound::Play( BGM_TITLE );
			Luna3D::Clear();
			// �^�C�g���p�I��������
			for ( long i = 0; i < 4; i++ )
			{
				lpTitle[i] = new CTITLE( F(320), F(280+(i*60)), i );
			}
			Select = 0;
			FadeLevel = 255;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�C��
	case 1:
		{
			// ���X�Ƀt�F�[�h�C��
			SetFade( D3DCOLOR_ARGB(FadeLevel,0,0,0) );
			FadeLevel -= 5;
			if ( FadeLevel < 0 )
			{
				FadeLevel = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �I��
	case 2:
		{
			// �L�[����
			if ( IO::GetKey( KEYSTATE_PUSH, KEY_UP ) )		// ��
			{
				CSound::Play( SE_CURSOR );
				lpTitle[Select]->SetSelect( false, 0 );
				if ( --Select < 0 ) Select = 2;
				lpTitle[Select]->SetSelect( true, 1 );
			}
			if ( IO::GetKey( KEYSTATE_PUSH, KEY_DOWN ) )	// ��
			{
				CSound::Play( SE_CURSOR );
				lpTitle[Select]->SetSelect( false, 0 );
				if ( ++Select > 2 ) Select = 0;
				lpTitle[Select]->SetSelect( true, 0 );
			}
			if ( IO::GetKey( KEYSTATE_PUSH, KEY_01 ) )		// �{�^��1
			{
				CSound::Play( SE_DECIDE );
				switch ( Select )
				{
				case 0: ScenePhase = 10; break;		// �X�^�[�g
				case 1: ScenePhase = 20; break;		// �X�R�A�����L���O
				case 2: ScenePhase = 30; break;		// �I��
				}
			}
		}
		break;
	//------------------------------------------------------------------------------- �X�^�[�g
	case 10:
		{
			for ( long i = 0; i < 4; i++ )
			{
				lpTitle[i]->Release();
				lpTitle[i] = NULL;
			}
			Select = 1;
			ScenePhase++;
		}
		break;
	case 11:
		{
			// �L�[����
			if ( IO::GetKey( KEYSTATE_PUSH, KEY_UP ) )		// ��
			{
				CSound::Play( SE_CURSOR );
				if ( --Select < 0 ) Select = 2;
			}
			if ( IO::GetKey( KEYSTATE_PUSH, KEY_DOWN ) )	// ��
			{
				CSound::Play( SE_CURSOR );
				if ( ++Select > 2 ) Select = 0;
			}
			if ( IO::GetKey( KEYSTATE_PUSH, KEY_01 ) )		// �{�^��1
			{
				CSound::Play( SE_DECIDE );
				SetLevel( Select );
				ScenePhase++;
			}
			for ( long i = 0; i < 3; i++ )
			{
				long alpha = ((i==Select)?(255):(32));
				long py = 220 + (i*54);
				long sy = 140 + (i*32);
				RECT dest = { 320-96, py, 320+96, py+48 };
				RECT src = { 352, sy, 352+128, sy+32 };
				SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_ARGB(alpha,255,255,255), BLEND_ADD );
			}
		}
		break;
	case 12:
		{
			LSURFACE pSurf = LunaSurface::Create( 640, 480, FORMAT_BACKBUFFER );
			pSurf->CopyFromBackBuffer( 0, 0, 0, 0, 640, 480 );
			for ( long y = 0; y < 480; y += 80 )
			{
				for ( long x = 0; x < 640; x += 80 )
				{
					RECT rect = { x, y, x+80, y+80 };
					new CPARTS( F(x), F(y), &rect, pSurf );
				}
			}
			pSurf->Release();
			SetScene( SCENE_STG );
		}
		break;
	//------------------------------------------------------------------------------- �X�R�A
	case 20:
		{
			LSURFACE pSurf = LunaSurface::Create( 640, 480, FORMAT_BACKBUFFER );
			pSurf->CopyFromBackBuffer( 0, 0, 0, 0, 640, 480 );
			for ( long y = 0; y < 480; y += 80 )
			{
				for ( long x = 0; x < 640; x += 80 )
				{
					RECT rect = { x, y, x+80, y+80 };
					new CPARTS( F(x), F(y), &rect, pSurf );
				}
			}
			pSurf->Release();
			for ( long i = 0; i < 4; i++ )
			{
				lpTitle[i]->Release();
				lpTitle[i] = NULL;
			}
			SetScene( SCENE_RANKING );
		}
		break;
	//------------------------------------------------------------------------------- �I��
	case 30:
		{
			// ���X�Ƀt�F�[�h�C��
			SetFade( D3DCOLOR_ARGB(FadeLevel,0,0,0) );
			FadeLevel += 5;
			if ( FadeLevel > 255 )
			{
				for ( long i = 0; i < 4; i++ )
				{
					lpTitle[i]->Release();
					lpTitle[i] = NULL;
				}
				// �I��
				Luna::Exit();
			}
		}
		break;
	}
}

//======================================================================================
//
//	�V���[�e�B���O
//
//======================================================================================
void CApplication::SceneStg( void )
{
	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- ������
	case 0:
		{
			CSound::Play( BGM_STG );
			// �C�x���g������
			CEVENT::Init();
			// �E�B���h�E����
			SetWindow( new CWINDOW() );
			// ���@����
			SetPlayer( new CPLAYER() );
			// �R���{
			SetCombo( new CCOMBO() );
			// ��
			for ( long i = 0; i < 64; i++ )
			{
				new CBG( F(RAND(0,640)), F(RAND(0,400)), 736, 382, 768, 414, RAND(10,100)/500.0f );
			}
			// ��
			for ( long i = 0; i < 96; i++ )
			{
				new CSNOW( F(RAND(0,640)), F(RAND(0,400)), F(RAND(50,100)/400.0f), -F(RAND(256,768)+2048)*PAI2/4096.0f );
			}
			// ��
			new CBG( 320, 100, 586, 360, 736, 510 );
			// �w�i
			new CSCROLL( 320, 400-180, 0, 0, 640, 180, -3 );
			new CSCROLL( 320, 400-120, 0, 180, 640, 300, -5 );
			// ������
			NoMissCounter = EnemyDestroy = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- ���C��
	case 1:
		{
			//------------------------------------------------------
			// �w�i�`�揈��
			//------------------------------------------------------
			RECT dest;
			D3DCOLOR color[4];

			LunaEffect::Begin( BLEND_NORMAL );

			color[0] = D3DCOLOR_XRGB(4,4,64),
			color[1] = D3DCOLOR_XRGB(4,4,64),
			color[2] = D3DCOLOR_XRGB(16,16,128),
			color[3] = D3DCOLOR_XRGB(16,16,128),
			SetRect( &dest, 0, 0, 640, 250 );
			LunaEffect::Gradation( &dest, color );

			color[0] = D3DCOLOR_XRGB(16,16,128),
			color[1] = D3DCOLOR_XRGB(16,16,128),
			color[2] = D3DCOLOR_XRGB(64,64,255),
			color[3] = D3DCOLOR_XRGB(64,64,255),
			SetRect( &dest, 0, 250, 640, 400 );
			LunaEffect::Gradation( &dest, color );

			LunaEffect::End();
			//------------------------------------------------------
			// �C�x���g����
			//------------------------------------------------------
			CEVENT::Drive();
		}
		break;
	}
}

//======================================================================================
//
//	�����L���O
//
//======================================================================================
void CApplication::SceneRanking( void )
{
	static long SceneTime = 0;
	static long Angle = 0;
	RECT src, dest;

	//------------------------------------------------------------------------------- �w�i
	SetRect( &dest, 0, 0, 640, 480 );
	D3DCOLOR color[] = {
		D3DCOLOR_XRGB(64,64,32),
		D3DCOLOR_XRGB(64,64,32),
		D3DCOLOR_XRGB(192,192,96),
		D3DCOLOR_XRGB(192,192,96),
	};
	LunaEffect::Begin( BLEND_NORMAL );
	LunaEffect::Gradation( &dest, color );
	LunaEffect::End();

	//------------------------------------------------------------------------------- �^�C�g������
	SetRect( &src, 256, 464, 512, 512 );
	SetRect( &dest, 320-256, 40-32, 320+256, 40+32 );
	SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_ADD );

	Angle += 96;
	long rot1 = Angle;

	//------------------------------------------------------------------------------- �e�X�R�A�f�[�^�\��
	for ( long i = 0; i < 10; i++ )
	{
		long py = 85 + (i*38);
		char score[11] = "";
		char *name = ScoreData[i].Name;
		sprintf( score, "%010d", ScoreData[i].Score );

		long rot2 = rot1;

		//---------------------------------------------
		// ���O�`��
		//---------------------------------------------
		for ( long j = 0; j < 8; j++ )
		{
			long c = name[j];
			long px = 80 + (j*18);
			long dy = py + LunaMath::Sin( rot2, 3 );

			SetRect( &dest, px, dy, px+16, dy+32 );

			if ( c != '\0' && c != ' ' )
			{
				switch ( c )
				{
				case '-':
					SetRect( &src, 224, 268, 224+16, 268+32 );
					break;
				case '^':
					SetRect( &src, 240, 268, 240+16, 268+32 );
					break;
				case '.':
					SetRect( &src, 256, 268, 256+16, 268+32 );
					break;
				default:
					if ( '0' <= c && c <= '9' )
					{
						c = (c - '0') * 16;
						SetRect( &src, 192+c, 140, 192+c+16, 172 );
					}
					ef ( 'A' <= c && c <= 'Z' )
					{
						long xx = ((c-'A')  & 7) * 16;
						long yy = ((c-'A') >> 3) * 32;
						SetRect( &src, 192+xx, 172+yy, 192+xx+16, 172+yy+32 );
					}
					break;
				}
				src.right++;
				src.bottom++;
				SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
			}
			rot2 += 256;
		}

		//---------------------------------------------
		// ���}�[�N�`��
		//---------------------------------------------
		long dy = py + LunaMath::Sin( rot2, 3 );
		SetRect( &dest, 360, dy, 360+16, dy+32 );
		SetRect( &src, 320, 268, 320+16, 268+32 );
		src.right++;
		src.bottom++;
		SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
		rot2 += 256;

		//---------------------------------------------
		// �X�R�A�`��
		//---------------------------------------------
		for ( long j = 0; j < 10; j++ )
		{
			long c = (score[j] - '0') * 16;
			long px = 380 + (j*18);
			long dy = py + LunaMath::Sin( rot2, 3 );

			SetRect( &dest, px, dy, px+16, dy+32 );
			SetRect( &src, 192+c, 140, 192+c+16, 172 );
			src.right++;
			src.bottom++;
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );

			rot2 += 256;
		}
		rot1 += 384;
	}

	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- �j�ЏI���܂ł��΂��ҋ@
	case 0:
		if ( ++SceneTime > 100 )
		{
			SceneTime = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- �L�[���͂ŏI��
	case 1:
		if ( IO::GetKey( KEYSTATE_PUSH, KEY_01 ) || IO::GetKey( KEYSTATE_PUSH, KEY_02 ) )
		{
			CSound::Play( SE_DECIDE );
			SceneTime = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�A�E�g�@
	case 2:
		{
			long fade = LunaMath::FlatSpeed( 0L, 255L, 50, SceneTime );
			SetFade( D3DCOLOR_ARGB(fade,0,0,0) );
			if ( ++SceneTime > 50 )
			{
				SceneTime = 0;
				SetScene( SCENE_TITLE );
			}
		}
		break;
	}
}

//======================================================================================
//
//	�I�v�V����
//
//======================================================================================
void CApplication::SceneOption( void )
{
	static long SceneTime;
	RECT src, dest;

	//------------------------------------------------------------------------------- �w�i
	SetRect( &dest, 0, 0, 640, 480 );
	D3DCOLOR color[] = {
		D3DCOLOR_XRGB(64,32,64),
		D3DCOLOR_XRGB(192,96,192),
		D3DCOLOR_XRGB(64,32,64),
		D3DCOLOR_XRGB(192,96,192),
	};
	LunaEffect::Begin( BLEND_NORMAL );
	LunaEffect::Gradation( &dest, color );
	LunaEffect::End();

	//------------------------------------------------------------------------------- �^�C�g������
	SetRect( &src, 256, 416, 512, 464 );
	SetRect( &dest, 320-256, 40-32, 320+256, 40+32 );
	SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_ADD );


	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- �j�ЏI���܂ł��΂��ҋ@
	case 0:
		if ( ++SceneTime > 100 )
		{
			SceneTime = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- �L�[���͂ŏI��
	case 1:
		if ( IO::GetKey( KEYSTATE_PUSH, KEY_02 ) )
		{
			SceneTime = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�A�E�g�@
	case 2:
		{
			long fade = LunaMath::FlatSpeed( 0L, 255L, 50, SceneTime );
			SetFade( D3DCOLOR_ARGB(fade,0,0,0) );
			if ( ++SceneTime > 50 )
			{
				SceneTime = 0;
				SetScene( SCENE_TITLE );
			}
		}
		break;
	}
}

//======================================================================================
//
//	�Q�[���I�[�o�[
//
//======================================================================================
void CApplication::SceneGameover( void )
{
	static long Px, Py, Sx, Sy, Time;
	static unsigned long Gold;

	//------------------------------------------------------------------------------- STG�p�[�g�w�i
	if ( ScenePhase < 5 )
	{
		RECT dest;
		D3DCOLOR color[4];

		LunaEffect::Begin( BLEND_NORMAL );

		color[0] = D3DCOLOR_XRGB(4,4,64),
		color[1] = D3DCOLOR_XRGB(4,4,64),
		color[2] = D3DCOLOR_XRGB(16,16,128),
		color[3] = D3DCOLOR_XRGB(16,16,128),
		SetRect( &dest, 0, 0, 640, 250 );
		LunaEffect::Gradation( &dest, color );

		color[0] = D3DCOLOR_XRGB(16,16,128),
		color[1] = D3DCOLOR_XRGB(16,16,128),
		color[2] = D3DCOLOR_XRGB(64,64,255),
		color[3] = D3DCOLOR_XRGB(64,64,255),
		SetRect( &dest, 0, 250, 640, 400 );
		LunaEffect::Gradation( &dest, color );

		LunaEffect::End();
	}

	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- ������
	case 0:
		{
			// �V���[�e�B���O�p�[�g�ł̃f�[�^�擾
			Gold = 0;
			GetData( NULL, &Gold, NULL );
			// ������
			Px = 320;
			Py = 160;
			Sx = 0;
			Sy = 0;
			Time = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- GAMEOVER �\���J�n
	case 1:
		{
			Sx = (long)LunaMath::Neville( 1000.0f, 230.0f, 256.0f, F(Time)/25.0f );
			Sy = (long)LunaMath::Neville(    0.0f,  80.0f,  64.0f, F(Time)/25.0f );
			RECT dest = { Px-Sx, Py-Sy, Px+Sx, Py+Sy };
			RECT src = { 768, 446-64, 1024, 510-64 };
			Sprite[9][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
			if ( ++Time > 25 )
			{
				Time = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- GAMEOVER �\��
	case 2:
		{
			RECT dest = { Px-Sx, Py-Sy, Px+Sx, Py+Sy };
			RECT src = { 768, 446-64, 1024, 510-64 };
			Sprite[9][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
			if ( ++Time > 100 )
			{
				Time = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- GAMEOVER �\���I��
	case 3:
		{
			Sx = (long)LunaMath::Neville( 256.0f, 230.0f, 1000.0f, F(Time)/25.0f );
			Sy = (long)LunaMath::Neville(  64.0f,  80.0f,    0.0f, F(Time)/25.0f );
			RECT dest = { Px-Sx, Py-Sy, Px+Sx, Py+Sy };
			RECT src = { 768, 446-64, 1024, 510-64 };
			Sprite[9][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
			if ( ++Time > 25 )
			{
				Time = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�A�E�g
	case 4:
		{
			long alpha = LunaMath::FlatSpeed( 0L, 255L, 200, Time );
			SetFade( D3DCOLOR_ARGB(alpha,0,0,0) );
			if ( ++Time > 200 )
			{
				Luna3D::Clear();
				// ���X�g�J��
				SpriteReset();
				Time = 0;
				// �l�[���G���g���[���邩�`�F�b�N
				if ( ScoreData[9].Score < Gold )
				{
					ScenePhase = 5;
				}
				else
				{
					ScenePhase = 6;
				}
			}
		}
		break;
	//------------------------------------------------------------------------------- �l�[���G���g���[
	case 5:
		if ( NameEntry( Gold ) ) ScenePhase++;
		break;
	//------------------------------------------------------------------------------- ���b�Z�[�W�\���J�n
	case 6:
		if ( Message() ) SetScene( SCENE_TITLE );
		break;
	}
}

//======================================================================================
//
//	�N���A�[
//
//======================================================================================
void CApplication::SceneClear( void )
{
	static long Px, Py, Sx, Sy, Time;
	static unsigned long Gold;
	static char Name[10] = "";

	//------------------------------------------------------------------------------- STG�p�[�g�w�i
	if ( ScenePhase < 5 )
	{
		RECT dest;
		D3DCOLOR color[4];

		LunaEffect::Begin( BLEND_NORMAL );

		color[0] = D3DCOLOR_XRGB(4,4,64),
		color[1] = D3DCOLOR_XRGB(4,4,64),
		color[2] = D3DCOLOR_XRGB(16,16,128),
		color[3] = D3DCOLOR_XRGB(16,16,128),
		SetRect( &dest, 0, 0, 640, 250 );
		LunaEffect::Gradation( &dest, color );

		color[0] = D3DCOLOR_XRGB(16,16,128),
		color[1] = D3DCOLOR_XRGB(16,16,128),
		color[2] = D3DCOLOR_XRGB(64,64,255),
		color[3] = D3DCOLOR_XRGB(64,64,255),
		SetRect( &dest, 0, 250, 640, 400 );
		LunaEffect::Gradation( &dest, color );

		LunaEffect::End();
	}

	switch ( ScenePhase )
	{
	//------------------------------------------------------------------------------- ������
	case 0:
		{
			// �V���[�e�B���O�p�[�g�ł̃f�[�^�擾
			Gold = 0;
			GetData( NULL, &Gold, NULL );
			// ������
			Px = 320;
			Py = 160;
			Sx = 0;
			Sy = 0;
			Time = 0;
			ScenePhase++;
		}
		break;
	//------------------------------------------------------------------------------- CLEAR �\���J�n
	case 1:
		{
			Sx = (long)LunaMath::Neville( 1000.0f, 230.0f, 256.0f, F(Time)/25.0f );
			Sy = (long)LunaMath::Neville(    0.0f,  80.0f,  64.0f, F(Time)/25.0f );
			RECT dest = { Px-Sx, Py-Sy, Px+Sx, Py+Sy };
			RECT src = { 768, 446, 1024, 510 };
			Sprite[9][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
			if ( ++Time > 25 )
			{
				Time = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- CLEAR �\��
	case 2:
		{
			RECT dest = { Px-Sx, Py-Sy, Px+Sx, Py+Sy };
			RECT src = { 768, 446, 1024, 510 };
			Sprite[9][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
			if ( ++Time > 100 )
			{
				Time = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- CLEAR �\���I��
	case 3:
		{
			Sx = (long)LunaMath::Neville( 256.0f, 230.0f, 1000.0f, F(Time)/25.0f );
			Sy = (long)LunaMath::Neville(  64.0f,  80.0f,    0.0f, F(Time)/25.0f );
			RECT dest = { Px-Sx, Py-Sy, Px+Sx, Py+Sy };
			RECT src = { 768, 446, 1024, 510 };
			Sprite[9][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
			if ( ++Time > 25 )
			{
				Time = 0;
				ScenePhase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �t�F�[�h�A�E�g
	case 4:
		{
			long alpha = LunaMath::FlatSpeed( 0L, 255L, 200, Time );
			SetFade( D3DCOLOR_ARGB(alpha,0,0,0) );
			if ( ++Time > 200 )
			{
				Luna3D::Clear();
				// ���X�g�J��
				SpriteReset();
				Time = 0;
				// �l�[���G���g���[���邩�`�F�b�N
				if ( ScoreData[9].Score < Gold )
				{
					ScenePhase = 5;
				}
				else
				{
					ScenePhase = 6;
				}
			}
		}
		break;
	//------------------------------------------------------------------------------- �l�[���G���g���[
	case 5:
		if ( NameEntry( Gold ) ) ScenePhase++;
		break;
	//------------------------------------------------------------------------------- ���b�Z�[�W�\���J�n
	case 6:
		if ( Message() ) SetScene( SCENE_TITLE );
		break;
	}
}

//======================================================================================
//
//	�l�[���G���g���[
//
//======================================================================================
bool CApplication::NameEntry( unsigned long gold )
{
	static long Phase = 0;
	static long Cursor, Select, KeyTime, Time, Fade;
	static char Name[12];
	char GoldStr[12] = "";
	RECT src, dest;

	// �ʒu�e�[�u��
	const long px[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7,
	};
	// �ʒu�e�[�u��
	const long py[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4, 4, 4,
	};
	// �����ϊ��e�[�u��
	const char StrTbl[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '-', '^', '.', '\0', '\b', ' ',
	};

	// �w�i
	SetRect( &dest, 0, 0, 640, 480 );
	D3DCOLOR color[] = {
		D3DCOLOR_XRGB(192,192,192),
		D3DCOLOR_XRGB(192,192,192),
		D3DCOLOR_XRGB(64,64,64),
		D3DCOLOR_XRGB(64,64,64),
	};
	LunaEffect::Begin( BLEND_NORMAL );
	LunaEffect::Gradation( &dest, color );
	LunaEffect::End();

	sprintf( GoldStr, "%010d", gold );

	switch ( Phase )
	{
	// ------------------------------------------------------------------------- ������
	case 0:
		memset( Name, 0x00, sizeof(char[12]) );
		Time = 0;
		Cursor = 0;
		Select = 10;
		KeyTime = 0;
		Luna3D::Clear();
		CSound::Play( BGM_TITLE );
		Phase++;
		break;
	// ------------------------------------------------------------------------- �t�F�[�h�C��
	case 1:
		Fade = LunaMath::FlatSpeed( 255L, 0L, 50, Time );
		SetFade( D3DCOLOR_ARGB(Fade,0,0,0) );
		if ( ++Time > 50 )
		{
			Time = 0;
			Phase++;
		}
		break;
	// ------------------------------------------------------------------------- ���͉��
	case 2:
		break;
	// ------------------------------------------------------------------------- �t�F�[�h�A�E�g
	case 3:
		Fade = LunaMath::FlatSpeed( 0L, 255L, 50, Time );
		SetFade( D3DCOLOR_ARGB(Fade,0,0,0) );
		if ( ++Time > 50 )
		{
			SetFade( 0 );
			Phase = 0;
			// ���O�f�[�^�R���o�[�g
			for ( long i = 0; i < 8; i++ )
			{
				Name[i] = StrTbl[Name[i]];
			}
			if ( Name[0] == '\0' ) strcpy( Name, "AYAME" );
			// �f�[�^�ۑ�
			SaveScore( gold, Name );
			Luna3D::Clear();
			return true;
		}
		break;
	}

	// �Ō�̕����ɑI�����͂Ȃ�
	if ( Cursor == 8 ) Select = 39;

	// ���}�[�N�`��
	SetRect( &dest, 210, 150, 210+16, 150+32 );
	SetRect( &src, 320, 268, 320+16, 268+32 );
	src.right++;
	src.bottom++;
	SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );

	// �X�R�A�`��
	for ( long j = 0; j < 10; j++ )
	{
		long c = (GoldStr[j] - '0') * 16;
		long dx = 230 + (j*18);
		long dy = 150;

		SetRect( &dest, dx, dy, dx+16, dy+32 );
		SetRect( &src, 192+c, 140, 192+c+16, 140+32 );
		src.right++;
		src.bottom++;
		SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_XRGB(255,255,255), BLEND_NORMAL );
	}

	// ���O�`��
	for ( long i = 0; i < Cursor+1; i++ )
	{
		static long cnt = 0;
		long num = Name[i];
		D3DCOLOR c = D3DCOLOR_XRGB(255,255,255);

		if ( i == Cursor )
		{
			num = Select;
			c = D3DCOLOR_XRGB(0,255,255);
		}
		// �r���̃X�y�[�X�͕`�悵�Ȃ�
		if ( !(StrTbl[num] == ' ' && i != Cursor) )
		{
			long sx = 192 + (px[num] * 16);
			long sy = 140 + (py[num] * 32);
			long dx = 230 + (i*18);
			long dy = 230;
			SetRect( &dest, dx, dy, dx+16, dy+32 );
			SetRect( &src, sx, sy, sx+16, sy+32 );
			src.right++;
			src.bottom++;
			SubGraphic->BlitToTarget( &dest, &src, c, BLEND_NORMAL );
		}
	}

	if ( Phase < 3 )
	{
		// ���{�^��
		if ( IO::GetKey( KEYSTATE_PUSH, KEY_UP ) )
		{
			CSound::Play( SE_CURSOR );
			KeyTime = 0;
			if ( --Select < 0 ) Select = 41;
		}
		// ��{�^��
		if ( IO::GetKey( KEYSTATE_PUSH, KEY_DOWN ) )
		{
			CSound::Play( SE_CURSOR );
			KeyTime = 0;
			if ( ++Select > 41 ) Select = 0;
		}
		// ��E�L�[���s�[�g
		if ( IO::GetKey( KEYSTATE_HOLD, KEY_UP ) )
		{
			// 1/2�b�ԉ������ςȂ���
			if ( ++KeyTime > 25 )
			{
				// �T�N�T�N�i�߂�
				static long cnt = 0;
				if ( (++cnt%3) == 0 )
				{
					CSound::Play( SE_CURSOR );
					if ( --Select == -1 ) Select = 41;
				}
			}
		}
		// ���E�L�[���s�[�g
		if ( IO::GetKey( KEYSTATE_HOLD, KEY_DOWN ) )
		{
			// 1/2�b�ԉ������ςȂ���
			if ( ++KeyTime > 25 )
			{
				// �T�N�T�N�i�߂�
				static long cnt = 0;
				if ( (++cnt%3) == 0 )
				{
					CSound::Play( SE_CURSOR );
					if ( ++Select == 42 ) Select = 0;
				}
			}
		}
		if ( IO::GetKey( KEYSTATE_PUSH, KEY_02 ) )
		{
			CSound::Play( SE_CANCEL );
			if ( Cursor > 0 )
			{
				// �o�b�N�X�y�[�X
				Name[Cursor] = '\0';
				Select = Name[Cursor-1];
				Cursor--;
			}
		}
		if ( IO::GetKey( KEYSTATE_PUSH, KEY_01 ) )
		{
			CSound::Play( SE_DECIDE );
			Name[Cursor] = (char)Select;
			// �I��
			if ( StrTbl[Select] == '\0' )
			{
				// ��
				Phase++;
			}
			// �o�b�N�X�y�[�X
			ef ( StrTbl[Select] == '\b' )
			{
				if ( Cursor > 0 )
				{
					Name[Cursor] = '\0';
					Select = Name[Cursor-1];
					Cursor--;
				}
			}
			// ��
			else
			{
				Cursor++;
			}
		}
	}

	return false;
}

//======================================================================================
//
//	���b�Z�[�W
//
//======================================================================================
bool CApplication::Message( void )
{
	static long Phase = 0;
	static long Time = 0;

	switch ( Phase )
	{
	//------------------------------------------------------------------------------- ���b�Z�[�W�\���J�n
	case 0:
		{
			SetFade( 0 );
			Luna3D::Clear();
			long alpha = LunaMath::FlatSpeed( 0L, 255L, 50, Time );
			RECT src = { 0, 512-24, 256, 512 };
			RECT dest = { 640-20-256, 480-10-24, 640-20, 480-10 };
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_ARGB(alpha,255,255,255), BLEND_ADD );
			if ( ++Time > 50 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- ���b�Z�[�W�\��
	case 1:
		{
			Luna3D::Clear();
			RECT src = { 0, 512-24, 256, 512 };
			RECT dest = { 640-20-256, 480-10-24, 640-20, 480-10 };
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_ARGB(255,255,255,255), BLEND_ADD );
			if ( ++Time > 150 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- ���b�Z�[�W�\���I��
	case 2:
		{
			Luna3D::Clear();
			long alpha = LunaMath::FlatSpeed( 255L, 0L, 50, Time );
			RECT src = { 0, 512-24, 256, 512 };
			RECT dest = { 640-20-256, 480-10-24, 640-20, 480-10 };
			SubGraphic->BlitToTarget( &dest, &src, D3DCOLOR_ARGB(alpha,255,255,255), BLEND_ADD );
			if ( ++Time > 50 )
			{
				Luna3D::Clear();
				SetScene( SCENE_TITLE );
				Time = 0;
				Phase = 0;
				return true;
			}
		}
		break;
	}

	return false;
}

//======================================================================================
//
//	�X�R�A�����o��
//
//======================================================================================
void CApplication::SaveScore( unsigned long score, char *name )
{
	ScoreData[9].Score = score;
	memset( ScoreData[9].Name, 0x00, sizeof(char[12]) );
	for ( long i = 0; name[i] != '\0'; i++ )
	{
		ScoreData[9].Name[i] = name[i];
	}

	// �\�[�g
	for ( long i = 0; i < 10; i++ )
	{
		for ( long j = 0; j < 10; j++ )
		{
			if ( ScoreData[i].Score > ScoreData[j].Score )
			{
				SCOREDATA sd = ScoreData[i];
				ScoreData[i] = ScoreData[j];
				ScoreData[j] = sd;
			}
		}
	}

	LunaSystem::SaveData( "score.dat", ScoreData, sizeof(SCOREDATA[10]) );
}

//======================================================================================
//
//	�X�R�A�ǂݍ���
//
//======================================================================================
void CApplication::LoadScore( void )
{
	LunaSystem::LoadData( "score.dat", ScoreData, sizeof(SCOREDATA[10]) );
}

//======================================================================================
//
//	��ʃG�t�F�N�g
//
//======================================================================================
void CApplication::ScreenEffect( void )
{
	LunaEffect::Begin( BLEND_NORMAL );

	// �G�t�F�N�g�n
	for ( unsigned long i = 0; i < EffectNum; i++ )
	{
		EffectList[i]->Draw();
		EffectList[i]->Release();
	}
	EffectNum = 0;

	// ��ʃt�F�[�h�p
	if ( FadeColor )
	{
		RECT dest = { 0, 0, 640, 480 };
		LunaEffect::FillSquare( &dest, FadeColor );
	}

	LunaEffect::End();
}

//======================================================================================
//
//	��ʃG�t�F�N�g�ǉ�
//
//======================================================================================
void CApplication::AddEffect( LPCSPRITE p )
{
	// �G�t�F�N�g�ǉ�
	if ( EffectNum < EFFECT_MAX )
	{
		EffectList[EffectNum] = p;
		EffectList[EffectNum]->AddRef();
		EffectNum++;
	}
}

//======================================================================================
//
//	�m�[�~�X�{�[�i�X�J�E���^�[
//
//======================================================================================
void CApplication::SetNoMissCounter( bool flag )
{
	// �G�𓦂����Ƃ�
	if ( !flag )
	{
		NoMissCounter = 0;
	}
	// �G��|�����Ƃ�
	else
	{
		if ( ++NoMissCounter == 15 )
		{
			NoMissCounter = 0;
			new CBONUS( BONUS_NOMISS );
		}
	}
}

//======================================================================================
//
//	�f�[�^�擾
//
//======================================================================================
void CApplication::GetData( unsigned long *score, unsigned long *gold, long *hit )
{
	if ( score != NULL ) *score = lpWindow->Score;
	if ( gold != NULL ) *gold = lpWindow->Gold;
	if ( hit != NULL ) *hit = lpCombo->MaxHit;
}

//======================================================================================
//
//	�X�v���C�g�f�[�^���Z�b�g
//
//======================================================================================
void CApplication::SpriteReset( void )
{
	SpriteList.Release();
	for ( long i = 0; i < 8; i++ )
	{
		Sprite[i][0]->InitDraw();
		Sprite[i][1]->InitDraw();
	}
}

//======================================================================================
//
//	�����蔻��
//
//======================================================================================
void CApplication::AllHitCheck( void )
{
	//--------------------------------------------
	// ���@���d���ƃR�C��
	//--------------------------------------------
	{
		LPCSPRITE p1 = (LPCSPRITE)SpriteList.Top();
		while ( p1 != NULL )
		{
			if ( p1->Sort == SORT_PLAYER )
			{
				LPCSPRITE p2 = (LPCSPRITE)SpriteList.Top();
				while ( p2 != NULL )
				{
					if ( p2->Sort == SORT_COIN )
					{
						POLYGON2D poly1 = { p1->HitCount, p1->lpHitPt };
						POLYGON2D poly2 = { p2->HitCount, p2->lpHitPt };
						if ( LunaCollision::Polygon_Polygon( poly1, poly2 ) )
						{
							AddGold( 50000 );
							p2->Damage( 0 );
						}
					}
					p2 = (LPCSPRITE)p2->Next;
				}
			}
			p1 = (LPCSPRITE)p1->Next;
		}
	}
	//--------------------------------------------
	// ���@�ƃA�C�e��
	//--------------------------------------------
	{
		LPCPLAYER p = lpPlayer;
		if ( p != NULL )
		{
			LPCSPRITE p1 = (LPCSPRITE)SpriteList.Top();
			while ( p1 != NULL )
			{
				if ( p1->Sort == SORT_ITEM )
				{
					POLYGON2D poly1 = { p->HitCount, p->lpHitPt };
					POLYGON2D poly2 = { p1->HitCount, p1->lpHitPt };
					if ( LunaCollision::Polygon_Polygon( poly1, poly2 ) )
					{
						p1->Damage( 0 );
					}
				}
				p1 = (LPCSPRITE)p1->Next;
			}
		}
	}
	//--------------------------------------------
	// ���@�ƓG�@���G�@�e
	//--------------------------------------------
	{
		LPCPLAYER p = lpPlayer;
		if ( p != NULL )
		{
			if ( p->bHit )
			{
				LPCSPRITE p1 = (LPCSPRITE)SpriteList.Top();
				while ( p1 != NULL )
				{
					if ( p1->bHit )
					{
						if ( p1->Sort == SORT_ENEMY )
						{
							POLYGON2D poly1 = { p->HitCount, p->lpHitPt };
							POLYGON2D poly2 = { p1->HitCount, p1->lpHitPt };
							if ( LunaCollision::Polygon_Polygon( poly1, poly2 ) )
							{
								p->Damage( p1->Power );
								goto NEXT;
							}
						}						
						if ( p1->Sort == SORT_ENEMYSHOT )
						{
							POLYGON2D poly1 = { p->HitCount, p->lpHitPt };
							POLYGON2D poly2 = { p1->HitCount, p1->lpHitPt };
							if ( LunaCollision::Polygon_Polygon( poly1, poly2 ) )
							{
								p->Damage( p1->Power );
								p1->Damage( p->Power );
								goto NEXT;
							}
						}
					}
					p1 = (LPCSPRITE)p1->Next;
				}
			}
		}
	}
NEXT:
	//--------------------------------------------
	// ���@�e�ƓG�@
	//--------------------------------------------
	{
		LPCSPRITE p1 = (LPCSPRITE)SpriteList.Top();
		while ( p1 != NULL )
		{
			if ( p1->bHit && (p1->Sort == SORT_ENEMY) )
			{
				LPCSPRITE p2 = (LPCSPRITE)SpriteList.Top();
				while ( p2 != NULL )
				{
					if ( p2->bHit && (p2->Sort == SORT_PLAYERSHOT) )
					{
						POLYGON2D poly1 = { p1->HitCount, p1->lpHitPt };
						POLYGON2D poly2 = { p2->HitCount, p2->lpHitPt };
						if ( LunaCollision::Polygon_Polygon( poly1, poly2 ) )
						{
							p1->Damage( p2->Power );
							p2->Damage( p1->Power );
						}
					}
					p2 = (LPCSPRITE)p2->Next;
				}
			}
			p1 = (LPCSPRITE)p1->Next;
		}
	}
	//--------------------------------------------
	// ���@���[�U�[�ƓG�@
	//--------------------------------------------
	{
		LPCSPRITE p1 = (LPCSPRITE)SpriteList.Top();
		while ( p1 != NULL )
		{
			if ( p1->bHit && (p1->Sort == SORT_ENEMY) )
			{
				LPCSPRITE p2 = (LPCSPRITE)SpriteList.Top();
				while ( p2 != NULL )
				{
					if ( p2->bHit && (p2->Sort == SORT_PLAYERLASER) )
					{
						long num = p1->HitCount-1;
						for ( long i = 0; i < num; i++ )
						{
							LINE2D l = { 
								p2->lpHitPt[i+0].x, p2->lpHitPt[i+0].y,
								p2->lpHitPt[i+1].x, p2->lpHitPt[i+1].y
							};
							POLYGON2D poly = { p1->HitCount, p1->lpHitPt };
							if ( LunaCollision::Line_Polygon( l, poly ) )
							{
								p1->Damage( p2->Power );
								p2->Damage( p1->Power );
							}
						}
					}
					p2 = (LPCSPRITE)p2->Next;
				}
			}
			p1 = (LPCSPRITE)p1->Next;
		}
	}
}
