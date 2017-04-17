//======================================================================================
//======================================================================================
//
//
//			�C�x���g�Ǘ�
//
//
//======================================================================================
//======================================================================================


//======================================================================================
//	include
//======================================================================================
#include <stdio.h>
#include "Event.h"
#include "Warning.h"
#include "Enemy.h"
#include "Application.h"
#include "Sound.h"


//======================================================================================
// DATA
//======================================================================================
long CEVENT::Attribute;
long CEVENT::Counter;
long CEVENT::EventNo;
long CEVENT::AddCounter;

EVENTDATA CEVENT::EventData[ENEMY_EVENT_MAX];

void (CEVENT::*CEVENT::EventTbl[20])( void ) =
{
	&CEVENT::Event000,
	&CEVENT::Event001,
	&CEVENT::Event002,
	&CEVENT::Event003,
	&CEVENT::Event004,
	&CEVENT::Event005,
	&CEVENT::Event006,
	&CEVENT::Event007,
	&CEVENT::Event008,
	&CEVENT::Event009,
	&CEVENT::Event010,
	&CEVENT::Event011,
	&CEVENT::Event012,
	&CEVENT::Event013,
	&CEVENT::Event014,
	&CEVENT::Event015,
	&CEVENT::Event016,
	&CEVENT::Event017,
	&CEVENT::Event018,
	&CEVENT::Event019,
};

//======================================================================================
//
//	������
//
//======================================================================================
void CEVENT::Init( void )
{
	EventNo = 0;
	Counter = 0;
	Attribute = 0;
	SetCounter( true );

	memset( EventData, 0x00, sizeof(EVENTDATA)*ENEMY_EVENT_MAX );

	// �}�b�v�ǂݍ���
	FILE *fp = fopen( "enemy.map", "rb" );
	if ( fp == NULL )
	{
		Luna::MsgBox( "Error", "�}�b�v�t�@�C����������܂���" );
		Luna::Exit();
	}

	// �t�@�C���`�F�b�N
	char guid[4] = "";
	fread( guid, sizeof(char), 4, fp );
	if ( strcmp( guid, "MAP" ) != 0 )
	{
		Luna::MsgBox( "Error", "�}�b�v�f�[�^���J���܂���ł���" );
		Luna::Exit();
	}

	// �}�b�v�f�[�^�ǂݍ���
	for ( long i = 0; i < ENEMY_EVENT_MAX; i++ )
	{
		fread( &EventData[i], sizeof(EVENTDATA), 1, fp );
		if ( feof( fp ) ) break;
	}

	fclose( fp );
}

//======================================================================================
//
//	�C�x���g����
//
//======================================================================================
void CEVENT::Drive( void )
{
	Counter += AddCounter;
	while ( Counter == EventData[EventNo].Time )
	{
		new CEVENT( &EventData[EventNo++] );
	}
}

//======================================================================================
//
//	�R���X�g���N�^
//
//======================================================================================
CEVENT::CEVENT( LPEVENTDATA p ) : CSPRITE( SORT_EVENT )
{
	EvData = *p;
	Attribute++;
}

//======================================================================================
//
//	����
//
//======================================================================================
bool CEVENT::Action( void )
{
	(this->*EventTbl[EvData.Type])();

	return bDeath;
}

//======================================================================================
//
//	�C�x���g000
//
//		�{�X
//
//======================================================================================
void CEVENT::Event000( void )
{
	switch ( Phase )
	{
	//------------------------------------------------------------------------------- ������
	case 0:
		{
			CSound::Play( SE_BOSS );
			Px = 320;
			Py = 200;
			SetCounter( false );
			Phase++;
		}
		break;
	//------------------------------------------------------------------------------- WARNING�\���J�n
	case 1:
		{
			x1 = LunaMath::Neville( 640.0f, 226.0f, 256.0f, F(Time)/15.0f );
			y1 = LunaMath::Neville(   0.0f, 100.0f,  80.0f, F(Time)/15.0f );
			if ( ++Time > 15 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �{�X�o��
	case 2:
		{
			if ( ++Time > 100 )
			{
				CSound::Play( SE_BOMB02 );
				CSound::Play( BGM_BOSS );
				new CENEMY( &EvData, Attribute );
				Time = 0;
				Phase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- �E�F�C�g
	case 3:
		{
			if ( ++Time > 100 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//------------------------------------------------------------------------------- WARNING�\���I��
	case 4:
		{
			x1 = LunaMath::Neville( 256.0f, 226.0f, 640.0f, F(Time)/15.0f );
			y1 = LunaMath::Neville(  80.0f, 100.0f,   0.0f, F(Time)/15.0f );
			if ( ++Time > 15 )
			{
				bDeath = true;
			}
		}
		break;
	}

	//------------------------------------------------------------------------------- WARNING�\��
	RECT src = { 270, 300, 530, 385 };
	RECT dest = { (long)(Px-x1), (long)(Py-y1), (long)(Px+x1), (long)(Py+y1) };
	Sprite[7][1]->Draw( &dest, D3DCOLOR_ARGB(128,255,255,255), &src );
	if ( Time & 0x01 )
	{
		Sprite[9][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,255,255), &src );
	}
}

//======================================================================================
//
//	�C�x���g001
//
//		�������̃��[�U�[�΂�
//
//======================================================================================
void CEVENT::Event001( void )
{
	switch ( Phase )
	{
	//------------------------------------------------------------------------------- WARNING
	case 0:
		EvData.Sy = (short)RAND(80,320);
		new CWARNING( 50, EvData.Sy );
		Phase++;
		break;
	case 1:
		if ( ++Time > 50 )
		{
			new CENEMY( &EvData, Attribute );
			bDeath = true;
		}
		break;
	}
}

//======================================================================================
//
//	�C�x���g002
//
//		�A�C�e���r�o
//
//======================================================================================
void CEVENT::Event002( void )
{
	new CENEMY( &EvData, Attribute );
	bDeath = true;
}

//======================================================================================
//
//	�C�x���g003
//
//		�E�� - ���� - �E�� - ����
//
//======================================================================================
void CEVENT::Event003( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%20) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 100 ) bDeath = true;
		}
		break;
	}
}

//======================================================================================
//
//	�C�x���g004
//
//		�E�� - ���� - �E�� - ����
//
//======================================================================================
void CEVENT::Event004( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%20) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 100 ) bDeath = true;
		}
		break;
	}
}

//======================================================================================
//
//	�C�x���g005
//
//		�E�� - ���� - �E��
//
//======================================================================================
void CEVENT::Event005( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%40) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 120 ) bDeath = true;
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g006
//
//		�E�� - ���� - �E��
//
//======================================================================================
void CEVENT::Event006( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%40) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 120 ) bDeath = true;
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g007
//
//		�E�� - ���� - ���� - ����
//
//======================================================================================
void CEVENT::Event007( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%40) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 120 ) bDeath = true;
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g008
//
//		�E�� - ���� - ���� - ����
//
//======================================================================================
void CEVENT::Event008( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%40) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 120 ) bDeath = true;
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g009
//
//		�� - ��
//
//======================================================================================
void CEVENT::Event009( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%25) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 150 ) bDeath = true;
		}
		break;
	}
}

//======================================================================================
//
//	�C�x���g010
//
//		��
//
//======================================================================================
void CEVENT::Event010( void )
{
	switch ( Phase )
	{
	case 0:
		if ( EvData.Sx < 0 )
		{
			new CWARNING( 50, EvData.Sy );
		}
		else
		{
			new CWARNING( 590, EvData.Sy );
		}
		Phase++;
		break;
	case 1:
		if ( ++Time == 40 )
		{
			new CENEMY( &EvData, Attribute );
			bDeath = true;
		}
	}
}

//======================================================================================
//
//	�C�x���g011
//
//		�ォ��Ɖ�����
//
//======================================================================================
void CEVENT::Event011( void )
{
	switch ( Phase )
	{
	case 0:
		EvData.Sx = (short)RAND( 300, 600 );
		if ( EvData.Sy < 0 )
		{
			new CWARNING( EvData.Sx, 50 );
		}
		else
		{
			new CWARNING( EvData.Sx, 350 );
		}
		Time = 0;
		Phase++;
		break;
	case 1:
		if ( ++Time == 50 )
		{
			new CENEMY( &EvData, Attribute );
			Phase = 0;
			if ( ++EvData.Temp[0] > EvData.Temp[1] )
			{
				bDeath = true;
			}
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g012
//
//		��납��ȉ~
//
//======================================================================================
void CEVENT::Event012( void )
{
	switch ( Phase )
	{
	case 0:
		if ( (++Time%10) == 0 )
		{
			new CWARNING( 50, F(Time*7) );
		}
		if ( Time == 50 )
		{
			Time = 0;
			Phase++;
		}
		break;
	case 1:
		for ( long i = 0; i < 8; i++ )
		{
			EvData.Temp[0] = (short)(4096 * i / 8);
			new CENEMY( &EvData, Attribute );
		}
		bDeath = true;
		break;
	}
}


//======================================================================================
//
//	�C�x���g013
//
//		��납��ґ�
//
//======================================================================================
void CEVENT::Event013( void )
{
	switch ( Phase )
	{
	case 0:
		EvData.Sx = -50;
		EvData.Sy = (short)RAND(30,370);
		new CWARNING( 50, EvData.Sy );
		Time = 0;
		Phase++;
		break;
	case 1:
		if ( ++Time > 40 )
		{
			Phase = 0;
			new CENEMY( &EvData, Attribute );
			if ( ++EvData.Temp[0] > EvData.Temp[1] )
			{
				bDeath = true;
			}
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g014
//
//		����
//
//======================================================================================
void CEVENT::Event014( void )
{
	const float px[] = {
		50, 110, 50, 170, 110, 50,
	};
	const float py[] = {
		50, 50, 110, 50, 110, 170,
	};

	switch ( Phase )
	{
	case 0:
		if ( (++Time%5) == 0 )
		{
			long id = (Time/5) - 1;
			new CWARNING( px[id], py[id] );
		}
		if ( Time == 30 )
		{
			Time = 0;
			Phase++;
		}
		break;
	case 1:
		if ( ++Time == 100 )
		{
			new CENEMY( &EvData, Attribute );
			bDeath = true;
		}
		break;
	}
}


//======================================================================================
//
//	�C�x���g015
//
//		����������
//
//======================================================================================
void CEVENT::Event015( void )
{
	switch ( Phase )
	{
	case 0:
		EvData.Sx = -50;
		if ( EvData.Sy < 0 )
		{
			EvData.Sy = 200-150;
			EvData.Temp[0] = 3072;
			EvData.Temp[1] = 3072 + 2048;
		}
		else
		{
			EvData.Sy = 200+150;
			EvData.Temp[0] = 1024;
			EvData.Temp[1] = -1024;
		}
		Phase++;
		break;
	case 1:
		if ( (++Time%40) == 0 )
		{
			new CENEMY( &EvData, Attribute );
			if ( Time == 160 ) bDeath = true;
		}
	}
}


//======================================================================================
//
//	�C�x���g016
//
//======================================================================================
void CEVENT::Event016( void )
{
	switch ( EvData.Temp[0] )
	{
	case 0: //------------------------------------ ��
		EvData.Sx = 700;
		EvData.Sy = 200;
		new CENEMY( &EvData, Attribute );
		break;
	case 1: //------------------------------------ ��
		EvData.Sx = 700;
		EvData.Sy = 120;
		new CENEMY( &EvData, Attribute );
		break;
	case 2: //------------------------------------ ��
		EvData.Sx = 700;
		EvData.Sy = 280;
		new CENEMY( &EvData, Attribute );
		break;
	case 3: //------------------------------------ ��E��
		EvData.Sx = 700;
		EvData.Sy = 120;
		new CENEMY( &EvData, Attribute );
		EvData.Sx = 700;
		EvData.Sy = 280;
		new CENEMY( &EvData, Attribute );
		break;
	case 4: //------------------------------------ ��E���E��
		EvData.Sx = 700;
		EvData.Sy = 100;
		new CENEMY( &EvData, Attribute );
		EvData.Sx = 700;
		EvData.Sy = 200;
		new CENEMY( &EvData, Attribute );
		EvData.Sx = 700;
		EvData.Sy = 300;
		new CENEMY( &EvData, Attribute );
		break;
	}

	bDeath = true;
}


//======================================================================================
//
//	�C�x���g017
//
//		�X�e�[�W�J�n����
//
//======================================================================================
void CEVENT::Event017( void )
{
	long alpha = 255;
	switch ( Phase )
	{
	case 0:
		{
			Px = 320;
			SetCounter( false );
			Phase++;
		}
	case 1:
		{
			alpha = LunaMath::FlatSpeed( 0L, 255L, 50, Time );
			Py = LunaMath::SubSpeed( 400.0f, 280.0f, 50, Time );
			if ( ++Time > 50 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	case 2:
		{
			if ( ++Time > 150 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	case 3:
		{
			alpha = LunaMath::FlatSpeed( 255L, 0L, 50, Time );
			Py = LunaMath::AddSpeed( 280.0f, 400.0f, 50, Time );
			if ( ++Time > 50 )
			{
				SetCounter( true );
				bDeath = true;
			}
		}
		break;
	}

	// �`�惊�X�g�ɒǉ�
	RECT dest = { (long)Px-192, (long)Py-128, (long)Px+192, (long)Py+128 };
	RECT src = { 768, 576, 1024, 768 };
	Sprite[7][1]->Draw( &dest, D3DCOLOR_ARGB(alpha,255,255,255), &src );
}


//======================================================================================
//
//	�C�x���g018
//
//======================================================================================
void CEVENT::Event018( void )
{
	CApplication::SetScene( SCENE_CLEAR );
	CApplication::GetPlayer()->SetHit( false );
	bDeath = true;
}


//======================================================================================
//
//	�C�x���g019
//
//======================================================================================
void CEVENT::Event019( void ){}