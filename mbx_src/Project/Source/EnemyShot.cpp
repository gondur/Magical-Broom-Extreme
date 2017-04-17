//======================================================================================
//======================================================================================
//
//
//			�G�V���b�g
//
//
//======================================================================================
//======================================================================================


//======================================================================================
//	include
//======================================================================================
#include "EnemyShot.h"
#include "Application.h"
#include "Sound.h"


long CENEMYSHOT::ShotCounter;

//======================================================================================
//
//	�e�Ǘ�
//
//		no �ɂ���
//
//			0 : �ʏ�e�i�ݒ肵�������֐ݒ肵�����x�ňړ��B��ʊO�ŏ��ŁB
//			1 : �U���e�i���@�Ɍ������Đi�s�A��ʊO�ŏ��ŁB
//			2 : ��^�e�i�ݒ肵�������֐ݒ肵�����x�ňړ��B��ʊO�ŏ��ŁB
//			3 : ��^�U���e�i�����Ɍ������Đi�s�A��ʊO�ŏ���
//			4 : ���[�U�[�W��
//
//======================================================================================
void CENEMYSHOT::Create( float x, float y, float speed, long angle, long no, LPCSPRITE p )
{
	// �������̒e�̎�
	if ( no == 0 || no == 1 || no == 2 )
	{
		// ���@�Ƃ̋������߂�����ꍇ�͖���
		float px = (CApplication::GetPlayer()->Px+45) - x;
		float py = (CApplication::GetPlayer()->Py+25) - y;
		if ( ((px*px) + (py*py)) < 120*120 ) return;

		// ��ʊO����̍U���͖���
		if ( x < 0 || y < 0 || x > 640 || y > 400 ) return;
	}


	// ��ʏ�ɏo���ł���e�̍ő吔
	long RateLevel = CApplication::GetRate() / 1000 / 3;
	long max = RateLevel + CApplication::GetLevel();
	max++;

	// �e������
	if ( no == 0 || no == 1 )
	{
		if ( ShotCounter > max ) return;
	}

	// �e����
	new CENEMYSHOT( x, y, speed, angle, no, p );
}

//======================================================================================
//
//	�R���X�g���N�^
//
//		no �ɂ���
//
//			0 : �ʏ�e�i�ݒ肵�������֐ݒ肵�����x�ňړ��B��ʊO�ŏ��ŁB
//			1 : �U���e�i���@�Ɍ������Đi�s�A��ʊO�ŏ��ŁB
//			2 : ��^�e�i�ݒ肵�������֐ݒ肵�����x�ňړ��B��ʊO�ŏ��ŁB
//			3 : ��^�U���e�i�����Ɍ������Đi�s�A��ʊO�ŏ���
//			4 : ���[�U�[�W��
//
//======================================================================================
CENEMYSHOT::CENEMYSHOT( float x, float y, float speed, long angle, long no, LPCSPRITE p ) : CSPRITE( SORT_ENEMYSHOT )
{
	No = no;
	Px = x;
	Py = y;
	lpParent = p;
	Speed = speed;
	Angle = angle;
	Color = D3DCOLOR_XRGB(255,255,255);
	if ( lpParent != NULL ) lpParent->AddRef();

	switch ( no )
	{
	//------------------------------------------------------------ �ʏ�e
	case 0:
		{
			bHit = true;
			SetHitCount( 5 );
			CSound::Play( SE_ENEMY_SHOT );
			ShotCounter++;
			x1 = LunaMath::CosF( ANGLE2PAI(angle) ) * speed;
			y1 = LunaMath::SinF( ANGLE2PAI(angle) ) * speed;
		}
		break;
	//------------------------------------------------------------ �U���e
	case 1:
		{
			bHit = true;
			SetHitCount( 5 );
			CSound::Play( SE_ENEMY_SHOT );
			ShotCounter++;
			x = CApplication::GetPlayer()->Px + 43;
			y = CApplication::GetPlayer()->Py + 35;
			x -= Px;
			y -= Py;
			float len = F(speed / sqrt( x*x + y*y ));
			x1 = x * len;
			y1 = y * len;
		}
		break;
	//------------------------------------------------------------ ��^�e
	case 2:
		{
			bHit = true;
			SetHitCount( 5 );
			CSound::Play( SE_ENEMY_SHOT );
			x1 = LunaMath::CosF( ANGLE2PAI(angle) ) * speed;
			y1 = LunaMath::SinF( ANGLE2PAI(angle) ) * speed;
		}
		break;
	//------------------------------------------------------------ ��^�U���e
	case 3:
		{
			bHit = true;
			SetHitCount( 5 );
			CSound::Play( SE_ENEMY_SHOT );
			x = CApplication::GetPlayer()->Px + 43;
			y = CApplication::GetPlayer()->Py + 35;
			x -= Px;
			y -= Py;
			float len = F(speed / sqrt( x*x + y*y ));
			x1 = x * len;
			y1 = y * len;
		}
		break;
	//------------------------------------------------------------ ���[�U�[���߃G�t�F�N�g
	case 4:
		{
			x2 = x;
			y2 = y;
			Angle = RAND(0,4095);
			Scale = RAND(0,200);
			x1 = x2 + F(LunaMath::Cos( Angle, Scale ));
			y1 = y2 + F(LunaMath::Sin( Angle, Scale ));
		}
		break;
	//------------------------------------------------------------ ���[�U�[
	case 5:
		{
			bHit = true;
			SetHitCount( 5 );
			CSound::Play( SE_BIG_LASER );
		}
		break;
	}
}

//======================================================================================
//
//	�f�X�g���N�^
//
//======================================================================================
CENEMYSHOT::~CENEMYSHOT()
{
	switch ( No )
	{
	case 0:
	////////////////////////////////////////////////////////////// �ʏ�e
		ShotCounter--;
		break;
	////////////////////////////////////////////////////////////// �U���e
	case 1:
		ShotCounter--;
		break;
	}

	if ( lpParent != NULL ) lpParent->Release();
}

//======================================================================================
//
//	����
//
//======================================================================================
bool CENEMYSHOT::Action( void )
{
	switch ( No )
	{
	////////////////////////////////////////////////////////////// �ʏ�e
	case 0:
	case 1:
		{
			Angle += 192;
			Px += x1;
			Py += y1;
			if ( Px < -30 || Px > 670 ) bDeath = true;
			if ( Py < -30 || Py > 430 ) bDeath = true;

			// �`��
			RECT src = { 736, 414, 736+33, 414+33 };
			RECT dest = { (long)Px-8, (long)Py-8, (long)Px+8, (long)Py+8 };
			Sprite[8][0]->DrawRotate( &dest, D3DCOLOR_XRGB(255,255,255), ANGLE2PAI(Angle), &src );

			// �����蔻��
			lpHitPt[0].x = -8;	lpHitPt[0].y = -8;
			lpHitPt[1].x = +8;	lpHitPt[1].y = -8;
			lpHitPt[2].x = +8;	lpHitPt[2].y = +8;
			lpHitPt[3].x = -8;	lpHitPt[3].y = +8;
			for ( long i = 0; i < 4; i++ )
			{
				LunaMath::RotatePoint( &lpHitPt[i].x, &lpHitPt[i].y, Angle );
				lpHitPt[i].x += (long)Px;
				lpHitPt[i].y += (long)Py;
			}
			lpHitPt[4] = lpHitPt[0];
		}
		break;
	//////////////////////////////////////////////////////////////
	case 2:
	case 3:
		{
			Angle += 192;
			Px += x1;
			Py += y1;
			if ( Px < -30 || Px > 670 ) bDeath = true;
			if ( Py < -30 || Py > 430 ) bDeath = true;

			// �`��
			RECT src = { 736, 414, 736+33, 414+33 };
			RECT dest = { (long)Px-15, (long)Py-8, (long)Px+15, (long)Py+8 };
			Sprite[8][0]->DrawRotate( &dest, D3DCOLOR_XRGB(255,255,255), ANGLE2PAI(Angle), &src );

			// �����蔻��
			lpHitPt[0].x = -15;	lpHitPt[0].y = -8;
			lpHitPt[1].x = +15;	lpHitPt[1].y = -8;
			lpHitPt[2].x = +15;	lpHitPt[2].y = +8;
			lpHitPt[3].x = -15;	lpHitPt[3].y = +8;
			for ( long i = 0; i < 4; i++ )
			{
				LunaMath::RotatePoint( &lpHitPt[i].x, &lpHitPt[i].y, Angle );
				lpHitPt[i].x += (long)Px;
				lpHitPt[i].y += (long)Py;
			}
			lpHitPt[4] = lpHitPt[0];
		}
		break;
	////////////////////////////////////////////////////////////// ���[�U�[�W��
	case 4:
		{
			x3 = LunaMath::FlatSpeed( 0.0f, 50.0f, 50, Time );
			y3 = LunaMath::FlatSpeed( 0.0f, 50.0f, 50, Time );
			Px = LunaMath::AddSpeed( x1, x2, 50, Time );
			Py = LunaMath::AddSpeed( y1, y2, 50, Time );
			if ( ++Time > 50 ) bDeath = true;

			// �`��
			RECT src = { 736, 478, 768, 510 };
			RECT dest = { (long)(Px-x3), (long)(Py-y3), (long)(Px+x3), (long)(Py+y3) };
			Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
		}
		break;
	////////////////////////////////////////////////////////////// ���[�U�[
	case 5:
		{
			switch ( Phase )
			{
			case 0:
				{
					RECT dest, src = { 320, 556, 520, 656 };
					// �`��
					SetRect( &dest, (long)Px, (long)Py-50+RAND(-1,1), 640, (long)Py+50+RAND(-1,1) );
					Sprite[5][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
					SetRect( &dest, (long)Px, (long)Py-60+RAND(-1,1), 640, (long)Py+60+RAND(-1,1) );
					Sprite[5][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
					// �_��
					if ( Time & 0x01 )
					{
						// �`��
						SetRect( &dest, (long)Px, (long)Py-50+RAND(-1,1), 640, (long)Py+50+RAND(-1,1) );
						Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
						SetRect( &dest, (long)Px, (long)Py-60+RAND(-1,1), 640, (long)Py+60+RAND(-1,1) );
						Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
					}
					// �����蔻��
					lpHitPt[0].x = Px+30;	lpHitPt[0].y = Py-50;
					lpHitPt[1].x = 640;		lpHitPt[1].y = Py-50;
					lpHitPt[2].x = 640;		lpHitPt[2].y = Py+50;
					lpHitPt[3].x = Px+30;	lpHitPt[3].y = Py+50;

					if ( ++Time > 150 )
					{
						Time = 0;
						Phase++;
					}
					lpHitPt[4] = lpHitPt[0];
				}
				break;
			case 1:
				{
					y1 = LunaMath::FlatSpeed( 50.0f, 0.0f, 100, Time );
					y2 = LunaMath::FlatSpeed( 60.0f, 0.0f, 100, Time );

					RECT dest, src = { 320, 556, 520, 656 };
					// �`��
					SetRect( &dest, (long)Px, (long)(Py-y1)+RAND(-1,1), 640, (long)(Py+y1)+RAND(-1,1) );
					Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
					SetRect( &dest, (long)Px, (long)(Py-y2)+RAND(-1,1), 640, (long)(Py+y2)+RAND(-1,1) );
					Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
					// �_��
					if ( Time & 0x01 )
					{
						// �`��
						SetRect( &dest, (long)Px, (long)(Py-y1)+RAND(-1,1), 640, (long)(Py+y1)+RAND(-1,1) );
						Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
						SetRect( &dest, (long)Px, (long)(Py-y2)+RAND(-1,1), 640, (long)(Py+y2)+RAND(-1,1) );
						Sprite[8][1]->Draw( &dest, D3DCOLOR_ARGB(255,255,128,128), &src );
					}
					// �����蔻��
					lpHitPt[0].x = Px+30;	lpHitPt[0].y = (Py-y1);
					lpHitPt[1].x = 640;		lpHitPt[1].y = (Py-y1);
					lpHitPt[2].x = 640;		lpHitPt[2].y = (Py+y1);
					lpHitPt[3].x = Px+30;	lpHitPt[3].y = (Py+y1);
					if ( ++Time > 100 )
					{
						bDeath = true;
					}
					lpHitPt[4] = lpHitPt[0];
				}
				break;
			}
		}
		break;
	}

	//-----------------------------------------
	// �e�����񂾂�I���ł���
	//-----------------------------------------
	if ( lpParent != NULL && lpParent->bDeath ) bDeath = true;

	return bDeath;
}

//======================================================================================
//
//	�_���[�W
//
//======================================================================================
void CENEMYSHOT::Damage( long pow )
{
	switch ( No )
	{
	case 0:
	case 1:
	case 2:
	case 3:
		bHit = false;
		bDeath = true;
		break;
	}
}