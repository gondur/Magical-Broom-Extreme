//======================================================================================
//======================================================================================
//
//
//			���C�t�j��
//
//
//======================================================================================
//======================================================================================


//======================================================================================
//	include
//======================================================================================
#include "Laser.h"
#include "Application.h"
#include "EnemyFx.h"
#include "Player.h"
#include "Sound.h"


//======================================================================================
//
//	�R���X�g���N�^
//
//======================================================================================
CLASER::CLASER( float x, float y, float w, long angle ) : CSPRITE( SORT_PLAYERLASER )
{
	SetHitCount( LASER_DIV );
	bHit = true;
	Speed = 15;

	CSound::Play( SE_LASER );

	long shot, bit;
	CApplication::GetPlayer()->GetShotLevel( &shot, &bit );
	Power = ( (shot+1) + (bit+1) ) * 2;

	// ���[�U�[������
	for ( long i = 0; i < LASER_DIV; i++ )
	{
		Lx[i] = x;
		Ly[i] = y;
		Lw[i] = w;
		Langle[i] = angle;
		Lcolor[i] = D3DCOLOR_ARGB(255,255,255,255);
	}
}

//======================================================================================
//
//	����
//
//======================================================================================
bool CLASER::Action( void )
{
	//===============================================
	// �Â����W�R�s�[
	for ( long i = LASER_DIV-2; i >= 0; i-- )
	{
		Lx[i+1]		= Lx[i];
		Ly[i+1]		= Ly[i];
		Langle[i+1]	= Langle[i];
	}

	switch ( Phase )
	{
	case 0:
		{
			//===============================================
			// ���W�v�Z

			// �K���ȓG����
			ReferenceNear( &x4, &y4, SORT_ENEMY );

			// �ڕW�Ƃ̊p�x�Z�o
			long a = LunaMath::Atan( (long)(x4-Lx[0]), (long)(y4-Ly[0]) );

			// ���݂̊p�x�Ƃ̑��Ίp�x�Z�o
			a = Langle[0] - a;
			a &= 4095;

			// �p�x�ɉ���������
			Langle[0] += ((a > 2048)?(+80):(-80));
			Langle[0] &= 4095;

			Lx[0] += LunaMath::Cos( (long)Langle[0], (long)Speed );
			Ly[0] += LunaMath::Sin( (long)Langle[0], (long)Speed );

			if ( ++Time > 75 ) Phase++;
		}
		break;
	case 1:
		{
			Lx[0] += LunaMath::Cos( (long)Langle[0], (long)Speed );
			Ly[0] += LunaMath::Sin( (long)Langle[0], (long)Speed );
			if ( ++Time > 150 ) bDeath = true;
		}
		break;
	}

	// �`��
	RECT uv = { 704, 0, 704+32, 360 };
	Sprite[6][1]->DrawLaser( Lx, Ly, Lw, Langle, Lcolor, &uv );

	// �����蔻��
	for ( long i = 0; i < LASER_DIV; i++ )
	{
		lpHitPt[i].x = Lx[i];
		lpHitPt[i].y = Ly[i];
	}

	return bDeath;
}
