//======================================================================================
//======================================================================================
//
//
//			�L�����N�^���
//
//
//======================================================================================
//======================================================================================

#pragma once

//======================================================================================
// INCLUDE
//======================================================================================
#include "Base.h"
#include "Luna.h"


//======================================================================================
// �L�������
//======================================================================================
enum eCharSort
{
	SORT_NULL,
	SORT_EVENT,
	SORT_PLAYER,
	SORT_PLAYERSHOT,
	SORT_PLAYERLASER,
	SORT_ENEMY,
	SORT_ENEMYSHOT,
	SORT_COIN,
	SORT_ITEM,
	sizeof_eSort
};


//======================================================================================
// CLASS
//======================================================================================
typedef class CSPRITE : public CListBase
{
public:
	bool bHit;
	bool bDeath;					// ���S�t���O
	eCharSort Sort;					// ���

	long HitCount;					// �����蔻�萔
	POINT2D *lpHitPt;				// �����蔻��ʒu

	float Px, Py;					// �ʒu���
	float x1, x2, x3, x4;			// �ėp
	float y1, y2, y3, y4;			// �ėp
	float Speed;					// ���x
	long Angle;						// �p�x
	long Scale;						// �g�嗦

	long Life;						// ���C�t
	long Power;						// �p���[

	long Phase;						// �t�F�[�Y�Ǘ��p
	long Time, Count;				// ���ԊǗ��p

	// function
	CSPRITE( eCharSort sort );
	virtual ~CSPRITE();
	virtual bool Action( void ) = 0;
	virtual void Draw( void ){}
	virtual void Damage( long pow ){}

	virtual void SetDeath( void ) { bDeath = true; Phase = 0; }
	virtual void SetHitCount( long num );
	virtual void Reference( float *x, float *y, eCharSort sort );
	virtual void ReferenceNear( float *x, float *y, eCharSort sort );
}
CSPRITE, *LPCSPRITE;