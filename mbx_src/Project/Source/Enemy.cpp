//======================================================================================
//======================================================================================
//
//
//			�G�L����
//
//
//======================================================================================
//======================================================================================


//======================================================================================
// INCLUDE
//======================================================================================
#include "Enemy.h"
#include "EnemyFx.h"
#include "EnemyShot.h"
#include "Application.h"
#include "Sonic.h"
#include "Coin.h"
#include "Item.h"
#include "Smoke.h"
#include "BossLaser.h"
#include "BossLife.h"
#include "Sound.h"
#include "Voice.h"


//======================================================================================
// GLOBAL
//======================================================================================
bool (CENEMY::*CENEMY::ActionTbl[20])( void ) = 
{
	&CENEMY::Action000,
	&CENEMY::Action001,
	&CENEMY::Action002,
	&CENEMY::Action003,
	&CENEMY::Action004,
	&CENEMY::Action005,
	&CENEMY::Action006,
	&CENEMY::Action007,
	&CENEMY::Action008,
	&CENEMY::Action009,
	&CENEMY::Action010,
	&CENEMY::Action011,
	&CENEMY::Action012,
	&CENEMY::Action013,
	&CENEMY::Action014,
	&CENEMY::Action015,
	&CENEMY::Action016,
	&CENEMY::Action017,
	&CENEMY::Action018,
	&CENEMY::Action019,
};

bool (CENEMY::*CENEMY::DeathTbl[20])( void ) = 
{
	&CENEMY::Death000,
	&CENEMY::Death001,
	&CENEMY::Death002,
	&CENEMY::Death003,
	&CENEMY::Death004,
	&CENEMY::Death005,
	&CENEMY::Death006,
	&CENEMY::Death007,
	&CENEMY::Death008,
	&CENEMY::Death009,
	&CENEMY::Death010,
	&CENEMY::Death011,
	&CENEMY::Death012,
	&CENEMY::Death013,
	&CENEMY::Death014,
	&CENEMY::Death015,
	&CENEMY::Death016,
	&CENEMY::Death017,
	&CENEMY::Death018,
	&CENEMY::Death019,
};

void (CENEMY::*CENEMY::DamageTbl[20])( long pow ) = 
{
	&CENEMY::Damage000,
	&CENEMY::Damage001,
	&CENEMY::Damage002,
	&CENEMY::Damage003,
	&CENEMY::Damage004,
	&CENEMY::Damage005,
	&CENEMY::Damage006,
	&CENEMY::Damage007,
	&CENEMY::Damage008,
	&CENEMY::Damage009,
	&CENEMY::Damage010,
	&CENEMY::Damage011,
	&CENEMY::Damage012,
	&CENEMY::Damage013,
	&CENEMY::Damage014,
	&CENEMY::Damage015,
	&CENEMY::Damage016,
	&CENEMY::Damage017,
	&CENEMY::Damage018,
	&CENEMY::Damage019,
};


//======================================================================================
//
//	����O���[�v����
//
//======================================================================================
bool CENEMY::Search( long att )
{
	LPCSPRITE p = (LPCSPRITE)SpriteList.Top();
	while ( p != NULL )
	{
		if ( p->Sort == SORT_ENEMY )
		{
			LPCENEMY pp = (LPCENEMY)p;
			if ( !pp->bDeath && pp->Attribute == att )
			{
				// ����������
				return true;
			}
		}
		p = (LPCSPRITE)p->Next;
	}
	// �Ȃ�
	return false;
}

//======================================================================================
//
//	�R���X�g���N�^
//
//======================================================================================
CENEMY::CENEMY( LPEVENTDATA p, long att ) : CSPRITE( SORT_ENEMY )
{
	EvData = *p;
	Attribute = att;
	AnimeNo = 0;
	AnimeCount = 0;
	LifeTimer = 0;
	Px = 5000;
	Py = 5000;
	HitTimer = 0;
	Color = D3DCOLOR_ARGB(255,255,255,255);
	const float mul_life[] = { 0.75f, 1.0f, 1.25f };
	Life = (long)( F(p->Life) * mul_life[CApplication::GetLevel()]);
	MaxLife = Life;
}

//======================================================================================
//
//	����
//
//======================================================================================
bool CENEMY::Action( void )
{
	if ( bDeath )
	{
		return (this->*DeathTbl[EvData.Type])();
	}
	else
	{
		if ( (this->*ActionTbl[EvData.Type])() )
		{
			if ( EvData.Type != 10 || EvData.Type != 14 )
			{
				CApplication::SetNoMissCounter( false );
			}
			return true;
		}
		CApplication::AddEffect( this );
	}

	return false;
}

//======================================================================================
//
//	�_���[�W
//
//======================================================================================
void CENEMY::Damage( long pow )
{
	if ( bHit )
	{
		Life -= pow;
		if ( Life < 0 )
		{
			CApplication::DestroyEnemy();
			CApplication::AddCombo();
			CApplication::SetNoMissCounter( true );
			MaxLife = Life = 0;
			bHit = false;
			bDeath = true;
			Phase = 0;
		}
		else
		{
			switch ( EvData.Type )
			{
			case 0:			// �{�X
			case 10:		// ��
			case 14:		// ��
				break;
			default:
				LifeTimer = 50;
			}
		}

		(this->*DamageTbl[EvData.Type])( pow );
	}
}

//======================================================================================
//
//	���C�t�Q�[�W�`��
//
//======================================================================================
void CENEMY::Draw( void )
{
	if ( LifeTimer > 0 )
	{
		LifeTimer--;

		RECT dest;
		long x = (long)Px;
		long y = (long)Py+30;
		long lv = LunaMath::FlatSpeed( x-24L, x+24L, MaxLife, Life );

		// �w�i
		SetRect( &dest, x-25, y, x+25, y+5 );
		LunaEffect::FillSquare( &dest, D3DCOLOR_XRGB(255,255,255) );

		SetRect( &dest, x-24, y+1, lv, y+4 );
		LunaEffect::FillSquare( &dest, D3DCOLOR_XRGB(255,64,64) );
	}
}

//======================================================================================
//
//	�G���A�j���������蔻�菈��
//
//======================================================================================
void CENEMY::ActionSubZako( long no, bool shot )
{
	//-------------------------------------------------------------- �C�܂���Œe����
	if ( bHit && shot ) 
	{
		if ( RAND(0,30) == 0 )
		{
			CENEMYSHOT::Create( Px, Py, F(RAND(20,30))/5.0f, 0, 1 );
		}
	}

	//-------------------------------------------------------------- �A�j���[�V����
	if ( ++AnimeCount == 3 )
	{
		AnimeCount = 0;
		if ( ++AnimeNo == 8 )
		{
			AnimeNo = 0;
		}
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-x2), (long)(Py-y2), (long)(Px+x2), (long)(Py+y2) };
	RECT src = { AnimeNo*40, 624+40*no, AnimeNo*40+40, 624+40*no+40 };
	Sprite[4][0]->Draw( &dest, Color, &src );

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = Px-15;	lpHitPt[0].y = Py-15;
	lpHitPt[1].x = Px+15;	lpHitPt[1].y = Py-15;
	lpHitPt[2].x = Px+15;	lpHitPt[2].y = Py+15;
	lpHitPt[3].x = Px-15;	lpHitPt[3].y = Py+15;
	lpHitPt[4] = lpHitPt[0];
}

//======================================================================================
//
//	�G�����S����
//
//======================================================================================
bool CENEMY::DeathZako( long no )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ���S����
	case 0:
		{
			CSound::Play( SE_BOMB01 );
			long r = RAND( 0x40, 0xA0 );
			long g = RAND( 0x40, 0xA0 );
			long b = RAND( 0x40, 0xA0 );
			CApplication::AddScore( 1000 );
			new CSONIC( Px, Py, 200, 50, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 200, 50, true, 1, D3DCOLOR_XRGB(r,g,b) );
			for ( long i = 0; i < 32; i++ )
			{
				float speed[2] = { 5, 3 };
				new CENEMYFX(
						Px, Py,
						speed[i&0x01],
						i*4096/32,
						D3DCOLOR_XRGB(r,g,b) );
			}
			long coin_num = CApplication::GetCombo()/5+5;
			for ( long i = 0; i < coin_num; i++ )
			{
				new CCOIN( Px, Py, RAND(0,4095) );
			}
			Time = 0;
			x1 = 3.0f;
			y1 = -5.0f;
			x2 = 0.0f;
			y2 = 0.3f;
			Color = D3DCOLOR_XRGB(192,192,192);
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ����
	case 1:
		{
			Angle += 256;
			Px += x1 += x2;
			Py += y1 += y2;
			if ( Py > 480 ) return true;
		}
		break;
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-20), (long)(Py-20), (long)(Px+20), (long)(Py+20) };
	RECT src = { AnimeNo*40, 624+40*no, AnimeNo*40+40, 624+40*no+40 };
	Sprite[4][0]->DrawRotate( &dest, Color, ANGLE2PAI(Angle), &src );

	return false;
}

//======================================================================================
//
//	�G000
//
//======================================================================================
bool CENEMY::Action000( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		{
			SetHitCount( 5 );
			if ( ++Time > 25 )
			{
				for ( long i = 0; i < 32; i++ )
				{
					CENEMYSHOT::Create( Px+RAND(-25,25), Py+RAND(-25,25), 0, 0, 4, this );
					CENEMYSHOT::Create( Px+RAND(-25,25), Py+RAND(-25,25), 0, 0, 4, this );
				}
				Color = D3DCOLOR_ARGB(0,255,255,255);
				x1 = 0;
				y1 = 0;
				Px = 500;
				Py = 200;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		{
			if ( ++Time > 25 )
			{
				new CBOSSLIFE( Life, this );
				long r = RAND( 0x40, 0xA0 );
				long g = RAND( 0x40, 0xA0 );
				long b = RAND( 0x40, 0xA0 );
				new CSONIC( Px, Py, 1000, 20, false, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 40, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 60, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 80, false, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 100, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 120, false, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 140, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 20, false, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 40, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 60, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 80, false, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 100, true, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 120, false, 1, D3DCOLOR_XRGB(r,g,b) );
				new CSONIC( Px, Py, 1000, 140, true, 1, D3DCOLOR_XRGB(r,g,b) );
				Color = D3DCOLOR_ARGB(255,255,255,255);
				x1 = 52;
				y1 = 57;
				Time = 0;
				bHit = true;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �x�e
	case 2:
		{
			if ( ++Time > 100 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �R�`�V�v�`�x
	case 3:
		{
			if ( (++Time%30) == 0 )
			{
				const long num[] = { 3, 5, 7 };
				for ( long i = 0; i < num[CApplication::GetLevel()]; i++ )
				{
					long angle[] = { 0, -256, +256, -128, +128, -384, +384 };
					CENEMYSHOT::Create( Px-50, Py, 3, 2048+angle[i], 2, this );
				}
				if ( Time == 150 )
				{
					Angle = 0;
					Time = 0;
					Phase++;
				}
			}
		}
		break;
	//-------------------------------------------------------------- �㉺�ړ�
	case 4:
		{
			Angle = (long)LunaMath::Neville( 0, 4096, 8192, F(Time)/200.0f );
			Py = 200 + F(LunaMath::Sin( Angle, 120 ));
			const long num[] = { 20, 15, 10 };
			if ( (Time%num[CApplication::GetLevel()]) == 0 )
			{
				CENEMYSHOT::Create( Px-50, Py, 5, 2048, 2, this );
			}
			if ( ++Time > 200 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �~�e
	case 5:
		{
			if ( ++Time > 100 )
			{
				const long num[] = { 8, 5, 3 };
				if ( (Time%num[CApplication::GetLevel()]) == 0 )
				{
					Angle += 192;
					Angle &= 4095;
					CENEMYSHOT::Create( Px, Py, 5, +Angle, 2, this );
					CENEMYSHOT::Create( Px, Py, 5, -Angle, 2, this );
				}
			}
			if ( Time == 200 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- ����
	case 6:
		{
			if ( ++Time == 1 )
			{
				EVENTDATA ed = { -1, 14, 0, 0, 0, 0, 0 };
				new CEVENT( &ed );
			}
			if ( Time == 50 )
			{
				EVENTDATA ed = { -1, 10, -1, 120, 0, 0, 0 };
				new CEVENT( &ed );
			}
			if ( Time == 100 )
			{
				EVENTDATA ed = { -1, 10, -1, 280, 0, 0, 0 };
				new CEVENT( &ed );
			}
			if ( Time == 150 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �x�e
	case 7:
		{
			if ( ++Time > 200 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �z�[�~���O���[�U�[
	case 8:
		{
			if ( ++Time == 1 )
			{
				const long num[] = { 3, 5, 9 };
				for ( long i = 0; i < num[CApplication::GetLevel()]; i++ )
				{
					const long angle[] = { 0, -256, +256, -512, +512, -384, +384, -768, +768 };
					new CBOSSLASER( Px+50, Py, angle[i] );
				}
			}
			ef ( Time > 150 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �~�e
	case 9:
		{
			if ( ++Time > 100 )
			{
				const long num[] = { 3, 2, 1 };
				if ( (Time%num[CApplication::GetLevel()]) == 0 )
				{
					Angle += 128;
					Angle &= 4095;
					CENEMYSHOT::Create( Px, Py, 5, +Angle, 2, this );
					CENEMYSHOT::Create( Px, Py, 5, -Angle, 2, this );
				}
			}
			if ( Time == 500 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �㉺�ړ�
	case 10:
		{
			Angle = (long)LunaMath::Neville( 0, 4096, 8192, F(Time)/200.0f );
			Py = 200 + F(LunaMath::Sin( Angle, 120 ));
			const long num[] = { 20, 15, 10 };
			if ( (Time%num[CApplication::GetLevel()]) == 0 )
			{
				CENEMYSHOT::Create( Px-50, Py, 5, 2048, 2, this );
			}
			if ( ++Time > 200 ) 
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �z�[�~���O���[�U�[
	case 11:
		{
			if ( ++Time == 1 )
			{
				const long num[] = { 3, 5, 9 };
				for ( long i = 0; i < num[CApplication::GetLevel()]; i++ )
				{
					const long angle[] = { 0, -256, +256, -512, +512, -384, +384, -768, +768 };
					new CBOSSLASER( Px+50, Py, angle[i] );
				}
			}
			ef ( Time > 150 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �~�e
	case 12:
		{
			if ( ++Time > 100 )
			{
				const long num[] = { 5, 4, 3 };
				if ( (Time%num[CApplication::GetLevel()]) == 0 )
				{
					Angle += 8;
					for ( long i = 0; i < 4096; i += 192 )
					{
						CENEMYSHOT::Create( Px, Py, 8, (i+Angle)&4095, 2, this );
					}
				}
			}
			if ( Time == 300 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �㉺�ړ�
	case 13:
		{
			Angle = (long)LunaMath::Neville( 0, 4096, 8192, F(Time)/200.0f );
			Py = 200 + F(LunaMath::Sin( Angle, 120 ));
			const long num[] = { 20, 15, 10 };
			if ( (Time%num[CApplication::GetLevel()]) == 0 )
			{
				new CBOSSLASER( Px+100, Py, 0 );
			}
			if ( ++Time > 200 )
			{
				Angle = 0;
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- ����
	case 14:
		{
			if ( ++Time == 1 )
			{
				EVENTDATA ed = { -1, 14, 0, 0, 0, 0, 0 };
				new CEVENT( &ed );
			}
			if ( Time == 50 )
			{
				EVENTDATA ed = { -1, 10, -1, 120, 0, 0, 0 };
				new CEVENT( &ed );
			}
			if ( Time == 100 )
			{
				EVENTDATA ed = { -1, 10, -1, 280, 0, 0, 0 };
				new CEVENT( &ed );
			}
			if ( Time == 150 )
			{
				Angle = 0;
				Time = 0;
				Phase = 2;
			}
		}
		break;
	}

	//-------------------------------------------------------------- �����点�e
	if ( Phase > 2 )
	{
		if ( RAND(0,30) == 0 )
		{
			CENEMYSHOT::Create( Px, Py, F(RAND(20,30))/5.0f, 0, 1, this );
		}
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-x1), (long)(Py-y1), (long)(Px+x1), (long)(Py+y1) };
	RECT src = { 0, 470, 104, 584 };
	Sprite[4][0]->Draw( &dest, Color, &src );

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = Px-30;	lpHitPt[0].y = Py-30;
	lpHitPt[1].x = Px+25;	lpHitPt[1].y = Py-30;
	lpHitPt[2].x = Px+25;	lpHitPt[2].y = Py+50;
	lpHitPt[3].x = Px-30;	lpHitPt[3].y = Py+50;
	lpHitPt[4] = lpHitPt[0];

	return false;
}
bool CENEMY::Death000( void )
{
	switch ( Phase )
	{
	case 0:
		{
			CVoice::Play( VOICE_CLEAR );
			CSound::Play( SE_BOMB02 );
			CApplication::AddScore( 50000 );
			CApplication::GetPlayer()->SetHit( false );
			long r = RAND( 0x40, 0xA0 );
			long g = RAND( 0x40, 0xA0 );
			long b = RAND( 0x40, 0xA0 );
			//------------------------------------------------------ �Ռ��g
			new CSONIC( Px, Py, 1000, 20, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 40, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 60, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 80, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 100, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 120, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 140, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 20, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 40, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 60, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 80, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 100, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 120, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 140, true, 1, D3DCOLOR_XRGB(r,g,b) );
			//------------------------------------------------------ ����
			for ( long i = 0; i < 32; i++ )
			{
				new CSMOKE(
						Px+RAND(-100,100), Py+RAND(-75,75),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(30,50), 80, 1 );
				new CSMOKE(
						Px+RAND(-100,100), Py+RAND(-75,75),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(30,50), 40, 0 );
				new CSMOKE(
						Px+RAND(-100,100), Py+RAND(-75,75),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(30,50), 60, 2 );
			}
			//------------------------------------------------------ �R�C��
			for ( long i = 0; i < 128; i++ )
			{
				new CCOIN( Px, Py, RAND(0,4095) );
			}
			Time = 0;
			Phase++;
		}
		break;
	case 1:
		{
			if ( ++Time == 100 )
			{
				unsigned long Gold = 0;
				CApplication::GetData( NULL, &Gold, NULL );
				if ( Gold > 300000000 )
				{
					CVoice::Play( VOICE_CLEAR03 );
				}
				ef ( Gold > 100000000 )
				{
					CVoice::Play( VOICE_CLEAR02 );
				}
				else
				{
					CVoice::Play( VOICE_CLEAR01 );
				}
				CEVENT::SetCounter( true );
				return true;
			}
		}
	}

	return false;
}
void CENEMY::Damage000( long pow )
{
}

//======================================================================================
//
//	�G001
//
//======================================================================================
bool CENEMY::Action001( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 4 );
		Color = D3DCOLOR_XRGB(255,255,255);
		Px = -150;
		Py = EvData.Sy;
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		Px = LunaMath::SubSpeed( -180.0f, 50.0f, 150, Time );
		if ( ++Time > 150 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ���@�̂x���W�܂ňړ�
	case 2:
		y3 = Py;
		y4 = CApplication::GetPlayer()->Py+30;
		Phase++;
		break;
	//-------------------------------------------------------------- ���[�U�[�`���[�W
	case 3:
		Py = LunaMath::SubSpeed( y3, y4, 50, Time );
		if ( ++Time > 50 )
		{
			CSound::Play( SE_BIG_LASER_CHARGE );
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ���[�U�[����
	case 4:
		if ( (++Time%2) == 0 )
		{
			if ( Time < 100 )
			{
				CENEMYSHOT::Create( Px+50, Py, 0, 0, 4, this );
				CENEMYSHOT::Create( Px+50, Py, 0, 0, 4, this );
			}
			ef ( Time == 100 )
			{
				for ( long i = 0; i < 64; i++ )
				{
					CENEMYSHOT::Create( Px+RAND(50,640), Py+RAND(-40,40), 0, 0, 4, this );
				}
			}
			ef ( Time == 150 )
			{
				CENEMYSHOT::Create( Px, Py, 0, 0, 5, this );
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �ꎞ�x�e
	case 5:
		{
			const long wait[] = { 500, 400, 300 };
			if ( ++Time > wait[CApplication::GetLevel()] )
			{
				Time = 0;
				Phase = 2;
			}
		}
		break;
	}

	// �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-98), (long)(Py-64), (long)(Px+158), (long)(Py+64) };
	RECT src = { 320, 656, 576, 783 };
	Sprite[4][0]->Draw( &dest, Color, &src );

	// �����蔻��
	lpHitPt[0].x = Px+30;	lpHitPt[0].y = Py;
	lpHitPt[1].x = Px-35;	lpHitPt[1].y = Py+15;
	lpHitPt[2].x = Px-35;	lpHitPt[2].y = Py-15;
	lpHitPt[3] = lpHitPt[0];

	return false;
}
bool CENEMY::Death001( void )
{
	switch ( Phase )
	{
	case 0:
		{
			CSound::Play( SE_BOMB02 );
			CApplication::AddScore( 5000 );
			long r = RAND( 0x40, 0xA0 );
			long g = RAND( 0x40, 0xA0 );
			long b = RAND( 0x40, 0xA0 );
			//------------------------------------------------------ �Ռ��g
			new CSONIC( Px, Py, 1000, 20, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 40, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 60, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 80, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 100, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 120, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 1000, 140, true, 1, D3DCOLOR_XRGB(r,g,b) );
			//------------------------------------------------------ ����
			for ( long i = 0; i < 32; i++ )
			{
				new CSMOKE(
						Px+RAND(-100,100), Py+RAND(-75,75),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(30,50), 80, 1 );
				new CSMOKE(
						Px+RAND(-100,100), Py+RAND(-75,75),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(30,50), 40, 0 );
				new CSMOKE(
						Px+RAND(-100,100), Py+RAND(-75,75),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(30,50), 60, 2 );
			}
			return true;
		}
		break;
	}

	return false;
}
void CENEMY::Damage001( long pow )
{
}

//======================================================================================
//
//	�G002
//
//======================================================================================
bool CENEMY::Action002( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		x2 = y2 = 15;
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		Px = LunaMath::FlatSpeed( -30.0f, 670.0f, 120, Time );
		Py = LunaMath::FlatSpeed( 250.0f, 10.0f, 120, Time );
		x2 = y2 = 20;
		y1 = F(RAND( 100, 300 ));
		if ( ++Time > 120 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			bHit = true;
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �W�����v
	case 2:
		Px -= 1.5f;
		Py = LunaMath::Neville( 20.0f, y1, 20.0f, F(Time)/60 );
		if ( ++Time == 60 )
		{
			Time = 0;
			y1 = F(RAND( 100, 300 ));
		}
		if ( Px < -30 )
		{
			return true;
		}
		break;
	}

	//-------------------------------------------------------------- �A�j���[�V����
	if ( ++AnimeCount == 3 )
	{
		AnimeCount = 0;
		if ( ++AnimeNo == 8 )
		{
			AnimeNo = 0;
		}
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-x2), (long)(Py-y2), (long)(Px+x2), (long)(Py+y2) };
	RECT src = { AnimeNo*40, 585, AnimeNo*40+40, 585+40 };
	Sprite[4][0]->Draw( &dest, Color, &src );

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = Px-15;	lpHitPt[0].y = Py-15;
	lpHitPt[1].x = Px+15;	lpHitPt[1].y = Py-15;
	lpHitPt[2].x = Px+15;	lpHitPt[2].y = Py+15;
	lpHitPt[3].x = Px-15;	lpHitPt[3].y = Py+15;
	lpHitPt[4] = lpHitPt[0];

	return false;
}
bool CENEMY::Death002( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- �����J�n
	case 0:
		{
			CSound::Play( SE_BOMB01 );
			CApplication::AddScore( 1000 );
			long r = RAND( 0x40, 0xA0 );
			long g = RAND( 0x40, 0xA0 );
			long b = RAND( 0x40, 0xA0 );
			// ����
			new CSONIC( Px, Py, 300, 50, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 500, 30, true, 1, D3DCOLOR_XRGB(r,g,b) );
			new CITEM( Px, Py );
			for ( long i = 0; i < 32; i++ )
			{
				new CSMOKE(
						Px+RAND(-25,25), Py+RAND(-25,25),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(10,20), 75, 1 );
				new CSMOKE(
						Px+RAND(-25,25), Py+RAND(-25,25),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(10,20), 50, 0 );
				new CSMOKE(
						Px+RAND(-25,25), Py+RAND(-25,25),
						RAND(0,4095), RAND(0,15)/10.0f, RAND(10,20), 50, 2 );
			}
			// �R�C������
			long coin_num = CApplication::GetCombo()/5+5;
			for ( long i = 0; i < coin_num; i++ )
			{
				new CCOIN( Px, Py, RAND(0,4095) );
			}
			Time = 0;
			x1 = 3.0f;
			y1 = -5.0f;
			x2 = 0.0f;
			y2 = 0.3f;
			Color = D3DCOLOR_XRGB(192,192,192);
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ����
	case 1:
		{
			Angle += 256;
			Px += x1 += x2;
			Py += y1 += y2;
			if ( Py > 480 )
			{
				return true;
			}
		}
		break;
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-20), (long)(Py-20), (long)(Px+20), (long)(Py+20) };
	RECT src = { AnimeNo*40, 585, AnimeNo*40+40, 585+40 };
	Sprite[4][0]->DrawRotate( &dest, Color, ANGLE2PAI(Angle), &src );

	return false;
}
void CENEMY::Damage002( long pow )
{
}

//======================================================================================
//
//	�G003
//
//======================================================================================
bool CENEMY::Action003( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 480.0f, 700.0f, 50, Time );
		Py = LunaMath::FlatSpeed( 150.0f,  50.0f, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			Time = 0;
			bHit = true;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �E��->����
	case 2:
		Px = LunaMath::FlatSpeed( 700.0f, 50.0f, 150, Time );
		if ( ++Time > 150 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ����->�E��
	case 3:
		Px = LunaMath::FlatSpeed( 50.0f, 600.0f, 150, Time );
		Py = LunaMath::FlatSpeed( 50.0f, 350.0f, 150, Time );
		if ( ++Time > 150 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �E��->����
	case 4:
		Px = LunaMath::FlatSpeed( 600.0f, -50.0f, 150, Time );
		if ( ++Time > 150 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 0, true );

	return false;
}
bool CENEMY::Death003( void )
{
	return DeathZako( 0 );
}
void CENEMY::Damage003( long pow )
{
}

//======================================================================================
//
//	�G004
//
//======================================================================================
bool CENEMY::Action004( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 480.0f, 700.0f, 50, Time );
		Py = LunaMath::FlatSpeed( 250.0f, 350.0f, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			Time = 0;
			bHit = true;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �E��->����
	case 2:
		Px = LunaMath::FlatSpeed( 700.0f, 50.0f, 150, Time );
		if ( ++Time > 150 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ����->�E��
	case 3:
		Px = LunaMath::FlatSpeed(  50.0f, 600.0f, 150, Time );
		Py = LunaMath::FlatSpeed( 350.0f,  50.0f, 150, Time );
		if ( ++Time > 150 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �E��->����
	case 4:
		Px = LunaMath::FlatSpeed( 600.0f, -50.0f, 150, Time );
		if ( ++Time > 150 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 0, true );

	return false;
}
bool CENEMY::Death004( void )
{
	return DeathZako( 0 );
}
void CENEMY::Damage004( long pow )
{
}

//======================================================================================
//
//	�G005
//
//======================================================================================
bool CENEMY::Action005( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 390.0f, 690.0f, 50, Time );
		Py = LunaMath::FlatSpeed( 150.0f,  50.0f, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			Time = 0;
			bHit = true;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �E��->����->�E��
	case 2:
		Px = LunaMath::Neville( 690,  50, 690, F(Time)/300.0f );
		Py = LunaMath::Neville(  50, 350, 300, F(Time)/300.0f );
		if ( ++Time > 300 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 1, true );

	return false;
}

bool CENEMY::Death005( void )
{
	return DeathZako( 1 );
}
void CENEMY::Damage005( long pow ) {}


//======================================================================================
//
//	�G006
//
//======================================================================================
bool CENEMY::Action006( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 390.0f, 690.0f, 50, Time );
		Py = LunaMath::FlatSpeed( 250.0f, 350.0f, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			Time = 0;
			bHit = true;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �E��->����->�E��
	case 2:
		Px = LunaMath::Neville( 690, 50, 690, F(Time)/300.0f );
		Py = LunaMath::Neville( 350, 50, 100, F(Time)/300.0f );
		if ( ++Time > 300 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 1, true );

	return false;
}
bool CENEMY::Death006( void )
{
	return DeathZako( 1 );
}

void CENEMY::Damage006( long pow )
{
}


//======================================================================================
//
//	�G007
//
//======================================================================================
bool CENEMY::Action007( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 390.0f, 690.0f, 50, Time );
		Py = LunaMath::FlatSpeed( 400.0f, 320.0f, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			Time = 0;
			bHit = true;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ��ʉE���璆�S��
	case 2:
		Px = LunaMath::Neville( 690, 400, 320, F(Time)/80.0f );
		Py = LunaMath::Neville( 350, 250, 200, F(Time)/80.0f );
		if ( ++Time > 80 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ���S�����ʍ���
	case 3:
		Px = LunaMath::Neville( 320, 240, -50, F(Time)/80.0f );
		Py = LunaMath::Neville( 200, 150, 50, F(Time)/80.0f );
		if ( ++Time > 80 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 2, true );

	return false;
}
bool CENEMY::Death007( void )
{
	return DeathZako( 2 );
}
void CENEMY::Damage007( long pow )
{
}


//======================================================================================
//
//	�G008
//
//======================================================================================
bool CENEMY::Action008( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Color = D3DCOLOR_XRGB(192,192,192);
		Phase++;
		break;
	//-------------------------------------------------------------- �o��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 390.0f, 690.0f, 50, Time );
		Py = LunaMath::FlatSpeed(   0.0f,  80.0f, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			Time = 0;
			bHit = true;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ��ʉE���璆�S��
	case 2:
		Px = LunaMath::Neville( 690, 400, 320, F(Time)/80.0f );
		Py = LunaMath::Neville( 50, 150, 200, F(Time)/80.0f );
		if ( ++Time > 80 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ���S�����ʍ���
	case 3:
		Px = LunaMath::Neville( 320, 240, -50, F(Time)/80.0f );
		Py = LunaMath::Neville( 200, 250, 350, F(Time)/80.0f );
		if ( ++Time > 80 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 2, true );

	return false;
}
bool CENEMY::Death008( void )
{
	return DeathZako( 2 );
}
void CENEMY::Damage008( long pow )
{
}


//======================================================================================
//
//	�G009
//
//======================================================================================
bool CENEMY::Action009( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		Py = 450;
		x2 = F(RAND( 300, 620 ));
		Color = D3DCOLOR_XRGB(255,255,255);
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- �ӂ�ӂ�Ə�Ɉړ�
	case 1:
		Px = x2 + LunaMath::Sin( Angle+=64, 8 );
		Py -= 1.5f;
		if ( Py < -50 ) 
		{
			return true;
		}
		break;
	}

	//-------------------------------------------------------------- �C�܂���Œe����
	if ( bHit ) 
	{
		if ( RAND(0,30) == 0 )
		{
			CENEMYSHOT::Create( Px, Py, F(RAND(20,30))/5.0f, 0, 1 );
		}
	}

	//-------------------------------------------------------------- �A�j���[�V����
	long AnimeTbl[] = { 0, 1, 2, 3, 4, 3, 2, 1, -1 };
	if ( ++AnimeCount == 4 )
	{
		AnimeCount = 0;
		if ( AnimeTbl[++AnimeNo] == -1 )
		{
			AnimeNo = 0;
		}
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-19), (long)(Py-25), (long)(Px+19), (long)(Py+25) };
	RECT src = { AnimeTbl[AnimeNo]*38, 371, AnimeTbl[AnimeNo]*38+38, 421 }; 
	Sprite[4][0]->Draw( &dest, Color, &src );

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = Px-10;	lpHitPt[0].y = Py-25;
	lpHitPt[1].x = Px+10;	lpHitPt[1].y = Py-25;
	lpHitPt[2].x = Px+10;	lpHitPt[2].y = Py-5;
	lpHitPt[3].x = Px-10;	lpHitPt[3].y = Py-5;
	lpHitPt[4] = lpHitPt[0];

	return false;
}
bool CENEMY::Death009( void )
{
	switch( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		{
			CSound::Play( SE_BOMB01 );
			long r = RAND( 0x40, 0xA0 );
			long g = RAND( 0x40, 0xA0 );
			long b = RAND( 0x40, 0xA0 );
			CApplication::AddScore( 1000 );
			new CSONIC( Px, Py, 200, 50, false, 1, D3DCOLOR_XRGB(r,g,b) );
			new CSONIC( Px, Py, 200, 50, true, 1, D3DCOLOR_XRGB(r,g,b) );
			for ( long i = 0; i < 32; i++ )
			{
				float speed[2] = { 5, 3 };
				new CENEMYFX(
						Px, Py,
						speed[i&0x01],
						i*4096/32,
						D3DCOLOR_XRGB(r,g,b) );
			}
			CApplication::AddScore( 1000 );
			long coin_num = CApplication::GetCombo()/5+5;
			for ( long i = 0; i < coin_num; i++ )
			{
				new CCOIN( Px, Py, RAND(0,4095) );
			}
			Color = D3DCOLOR_XRGB(192,192,192);
			y1 = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- ����
	case 1:
		{
			Py += y1 += 0.25f;
			if ( Py > 400 ) return true; 
		}
		break;
	}

	//-------------------------------------------------------------- �A�j���[�V����
	long AnimeTbl[] = { 0, 1, 2, 3, 4, 3, 2, 1, -1 };
	if ( ++AnimeCount == 4 )
	{
		AnimeCount = 0;
		if ( AnimeTbl[++AnimeNo] == -1 )
		{
			AnimeNo = 0;
		}
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-19), (long)(Py-5), (long)(Px+19), (long)(Py+25) };
	RECT src = { AnimeTbl[AnimeNo]*38, 391, AnimeTbl[AnimeNo]*38+38, 421 }; 
	Sprite[4][0]->Draw( &dest, Color, &src );

	return false;
}
void CENEMY::Damage009( long pow )
{
}


//======================================================================================
//
//	�G010
//
//======================================================================================
bool CENEMY::Action010( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		MaxLife = Life = 0x0FFFFFFF;
		Py = EvData.Sy;
		if ( EvData.Sx < 0 )
		{
			x1 = -200;
			x2 =  840;
		}
		else
		{
			x1 =  840;
			x2 = -200;
		}
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- ���U
	case 1:
		Px = LunaMath::FlatSpeed( x1, x2, 120, Time );
		if ( ++Time > 120 )
		{
			return true;
		}
		break;
	}

	//-------------------------------------------------------------- �A�j���[�V����
	AnimeCount = 0;
	if ( x1 < 0 )
	{
		if ( ++AnimeNo == 12 ) AnimeNo = 0;
	}
	else
	{
		if ( --AnimeNo == -1 ) AnimeNo = 11;
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-90), (long)(Py-80), (long)(Px+90), (long)(Py+80) };
	long x = 321+90*(AnimeNo/3);
	long y = 784+80*(AnimeNo%3);
	RECT src = { x, y, x+90, y+80 };
	Sprite[4][0]->Draw( &dest, Color, &src );

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = Px-70;	lpHitPt[0].y = Py-70;
	lpHitPt[1].x = Px+70;	lpHitPt[1].y = Py-70;
	lpHitPt[2].x = Px+70;	lpHitPt[2].y = Py+70;
	lpHitPt[3].x = Px-70;	lpHitPt[3].y = Py+70;
	lpHitPt[4] = lpHitPt[0];

	return false;
}
bool CENEMY::Death010( void )
{
	return true;
}
void CENEMY::Damage010( long pow )
{
}


//======================================================================================
//
//	�G011
//
//======================================================================================
bool CENEMY::Action011( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		x1 = EvData.Sx;
		x3 = EvData.Sx;
		x4 = EvData.Sx-F(RAND(-100,100));
		if ( EvData.Sy < 0 )
		{
			y1 = -50;
			y3 = 450;
			y4 = F(RAND(150,250));
		}
		else
		{
			y1 = 450;
			y3 = -50;
			y4 = F(RAND(150,250));
		}
		Color = D3DCOLOR_XRGB(255,255,255);
		x2 = 20.0f;
		y2 = 19.0f;
		Time = 0;
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- ��ʓ��ɏ㉺����o��
	case 1:
		Px = LunaMath::SubSpeed( x1, x4, 50, Time );
		Py = LunaMath::SubSpeed( y1, y4, 50, Time );
		if ( ++Time > 50 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �e��������
	case 2:
		{
			switch ( CApplication::GetLevel() )
			{
			case 0:
				break;
			case 1:
				CENEMYSHOT::Create( Px, Py, 6.0f, 0, 3 );
				break;
			case 2:
				CENEMYSHOT::Create( Px, Py, 6.0f, 0, 3 );
				CENEMYSHOT::Create( Px, Py, 8.0f, 2048, 2 );
				break;
			}
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �t�����ɓP��
	case 3:
		Px = LunaMath::AddSpeed( x4, x3, 50, Time );
		Py = LunaMath::AddSpeed( y4, y3, 50, Time );
		if ( ++Time > 50 )
		{
			return true;
		}
		break;
	}

	ActionSubZako( 3, false );

	return false;
}
bool CENEMY::Death011( void )
{
	return DeathZako( 3 );
}
void CENEMY::Damage011( long pow )
{
}

//======================================================================================
//
//	�G012
//
//======================================================================================
bool CENEMY::Action012( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		x3 = -200;
		y3 = 200;
		Angle = EvData.Temp[0];
		Color = D3DCOLOR_XRGB(255,255,255);
		x2 = 20.0f;
		y2 = 19.0f;
		Time = 0;
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- �ȉ~�ړ�
	case 1:
		{
			x3 += 2;
			Angle += 24;
			long x = LunaMath::Cos( Angle, 160 ) / 2;
			long y = LunaMath::Sin( Angle, 160 );
			LunaMath::RotatePoint( &x, &y, 384 );
			Px = x3 + x;
			Py = y3 + y;
			if ( x3 > 840 )
			{
				return true;
			}
		}
		break;
	}

	ActionSubZako( 4, false );

	return false;
}
bool CENEMY::Death012( void )
{
	return DeathZako( 4 );
}
void CENEMY::Damage012( long pow )
{
}


//======================================================================================
//
//	�G013
//
//======================================================================================
bool CENEMY::Action013( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		x2 = 20.0f;
		y2 = 19.0f;
		x3 = EvData.Sx;
		y3 = EvData.Sy;
		x4 = x3 + F(RAND(200,250));
		y4 = y3 + F(RAND(30,30));
		Color = D3DCOLOR_XRGB(255,255,255);
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- �������֍s�������Ă���
	case 1:
		{
			x3 += 4;
			Angle += 192;
			Px = x3;
			Py = y3 + LunaMath::Sin( Angle, 8 );
			if ( x3 > 700 )
			{
				return true;
			}
		}
		break;
	}

	ActionSubZako( 4, false );

	return false;
}
bool CENEMY::Death013( void )
{ 
	return DeathZako( 4 );
}
void CENEMY::Damage013( long pow )
{
}


//======================================================================================
//
//	�G014
//
//======================================================================================
bool CENEMY::Action014( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		MaxLife = Life = 0x0FFFFFFF;
		Px = -90;
		Py = -90;
		x1 = 3;
		y1 = 0;
		bHit = true;
		Phase++;
		break;
	//-------------------------------------------------------------- �o�E���h���Ȃ����ʊO��
	case 1:
		Px += x1;
		Py += y1 += 0.1f;
		if ( Py > 400-90 )
		{
			y1 *= -0.75f;
		}
		if ( Px > 750 )
		{
			return true;
		}
		break;
	}

	//-------------------------------------------------------------- �A�j���[�V����
	if ( ++AnimeCount == 2 )
	{
		AnimeCount = 0;
		if ( ++AnimeNo == 12 )
		{
			AnimeNo = 0;
		}
	}

	//-------------------------------------------------------------- �`�惊�X�g�ɒǉ�
	RECT dest = { (long)(Px-90), (long)(Py-80), (long)(Px+90), (long)(Py+80) };
	long x = 321+90*(AnimeNo/3);
	long y = 784+80*(AnimeNo%3);
	RECT src = { x, y, x+90, y+80 };
	Angle += 64;
	Sprite[4][0]->DrawRotate( &dest, Color, ANGLE2PAI(Angle), &src );

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = -70;	lpHitPt[0].y = -70;
	lpHitPt[1].x = +70;	lpHitPt[1].y = -70;
	lpHitPt[2].x = +70;	lpHitPt[2].y = +70;
	lpHitPt[3].x = -70;	lpHitPt[3].y = +70;
	for ( long i = 0; i < 4; i++ )
	{
		LunaMath::RotatePoint( &lpHitPt[i].x, &lpHitPt[i].y, Angle );
		lpHitPt[i].x += (long)Px;
		lpHitPt[i].y += (long)Py;
	}
	lpHitPt[4] = lpHitPt[0];

	return false;
}
bool CENEMY::Death014( void )
{
	return true;
}
void CENEMY::Damage014( long pow )
{
}


//======================================================================================
//
//	�G015
//
//======================================================================================
bool CENEMY::Action015( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		y3 = EvData.Sy;
		y4 = EvData.Sy + F(RAND(-50,50));
		Color = D3DCOLOR_XRGB(192,192,192);
		Angle = EvData.Temp[0];
		Py = F(LunaMath::Sin( Angle, 150 ));
		Phase++;
		break;
	//-------------------------------------------------------------- ��ʉ�����o��\��
	case 1:
		x2 = LunaMath::SubSpeed( 0.0f, 20.0f, 50, Time );
		y2 = LunaMath::SubSpeed( 0.0f, 19.0f, 50, Time );
		Px = LunaMath::FlatSpeed( 200.0f, -50.0f, 50, Time );
		Py = LunaMath::FlatSpeed( y4, y3, 50, Time );
		if ( ++Time > 50 )
		{
			Color = D3DCOLOR_XRGB(255,255,255);
			bHit = true;
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �������ˊ�
	case 2:
		{
			Px = LunaMath::FlatSpeed( -50.0f, 500.0f, 75, Time );
			if ( ++Time > 75 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- ����
	case 3:
		{
			Angle = LunaMath::FlatSpeed( (long)EvData.Temp[0], (long)EvData.Temp[1], 60, Time );
			Px = 500 + F(LunaMath::Cos( Angle, 150 )) * 0.7f;
			Py = 200+F(LunaMath::Sin( Angle, 150 ));
			if ( ++Time > 60 )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- �P��
	case 4:
		{
			Px = LunaMath::FlatSpeed( 500.0f, -50.0f, 75, Time );
			if ( ++Time > 75 )
			{
				return true;
			}
		}
		break;
	}

	ActionSubZako( 5, true );

	return false;
}
bool CENEMY::Death015( void )
{
	return DeathZako( 5 );
}
void CENEMY::Damage015( long pow )
{
}


//======================================================================================
//
//	�G016
//
//======================================================================================
bool CENEMY::Action016( void )
{
	switch ( Phase )
	{
	//-------------------------------------------------------------- ������
	case 0:
		SetHitCount( 5 );
		bHit = true;
		x1 = 700;
		x2 = 520;
		x3 = 500;
		Py = EvData.Sy;
		Color = D3DCOLOR_XRGB(255,255,255);
		Phase++;
		break;
	//-------------------------------------------------------------- ��ʓ�����O�i
	case 1:
		Px = LunaMath::Neville( x1, x2, x3, F(Time)/100 );
		if ( ++Time > 100 )
		{
			Time = 0;
			Phase++;
		}
		break;
	//-------------------------------------------------------------- �e����
	case 2:
		if ( (++Time%25) == 0 )
		{
			CENEMYSHOT::Create( Px-40, Py, 5.0f, 2048    , 2 );
			CENEMYSHOT::Create( Px-40, Py, 5.0f, 2048-384, 2 );
			CENEMYSHOT::Create( Px-40, Py, 5.0f, 2048+384, 2 );
			const long num[] = { 25, 75, 125 };
			if ( Time == num[CApplication::GetLevel()] )
			{
				Time = 0;
				Phase++;
			}
		}
		break;
	//-------------------------------------------------------------- ��ʊO�܂őO�i
	case 3:
		Px = LunaMath::AddSpeed( x3, -100, 100, Time );
		if ( ++Time > 100 )
		{
			return true;
		}
	}

	//-------------------------------------------------------------- �����蔻��
	lpHitPt[0].x = Px-45;	lpHitPt[0].y = Py-10;
	lpHitPt[1].x = Px+45;	lpHitPt[1].y = Py-10;
	lpHitPt[2].x = Px+45;	lpHitPt[2].y = Py+25;
	lpHitPt[3].x = Px-45;	lpHitPt[3].y = Py+25;
	lpHitPt[4] = lpHitPt[0];

	++AnimeNo &= 0x01;

	//-------------------------------------------------------------- �`��
	RECT src = { AnimeNo*91, 421, 91+AnimeNo*91, 470 };
	RECT dest = { (long)Px-45, (long)Py-24, (long)Px+46, (long)Py+25 };
	Sprite[4][0]->Draw( &dest, Color, &src );

	return false;
}
bool CENEMY::Death016( void )
{
	CSound::Play( SE_BOMB01 );
	CApplication::AddScore( 1000 );
	long r = RAND( 0x40, 0xA0 );
	long g = RAND( 0x40, 0xA0 );
	long b = RAND( 0x40, 0xA0 );
	//-------------------------------------------------------------- �Ռ��g
	new CSONIC( Px, Py, 300, 50, false, 1, D3DCOLOR_XRGB(r,g,b) );
	new CSONIC( Px, Py, 500, 30, true, 1, D3DCOLOR_XRGB(r,g,b) );
	//-------------------------------------------------------------- ����
	for ( long i = 0; i < 32; i++ )
	{
		new CSMOKE(
				Px+RAND(-25,25), Py+RAND(-25,25),
				RAND(0,4095), RAND(0,15)/10.0f, RAND(10,20), 75, 1 );
		new CSMOKE(
				Px+RAND(-25,25), Py+RAND(-25,25),
				RAND(0,4095), RAND(0,15)/10.0f, RAND(10,20), 50, 0 );
		new CSMOKE(
				Px+RAND(-25,25), Py+RAND(-25,25),
				RAND(0,4095), RAND(0,15)/10.0f, RAND(10,20), 50, 2 );
	}
	//-------------------------------------------------------------- �R�C��
	long coin_num = CApplication::GetCombo()/5+5;
	for ( long i = 0; i < coin_num; i++ )
	{
		new CCOIN( Px, Py, RAND(0,4095) );
	}

	return true;
}
void CENEMY::Damage016( long pow )
{
}


//======================================================================================
//
//	�G017
//
//======================================================================================
bool CENEMY::Action017( void ) { return true; }
bool CENEMY::Death017( void ) { return true; }
void CENEMY::Damage017( long pow ) {}


//======================================================================================
//
//	�G018
//
//======================================================================================
bool CENEMY::Action018( void ) { return true; }
bool CENEMY::Death018( void ) { return true; }
void CENEMY::Damage018( long pow ) {}


//======================================================================================
//
//	�G019
//
//======================================================================================
bool CENEMY::Action019( void ) { return true; }
bool CENEMY::Death019( void ) { return true; }
void CENEMY::Damage019( long pow ) {}