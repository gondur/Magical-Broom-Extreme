//======================================================================================
//======================================================================================
//
//
//			���C�t�j��
//
//
//======================================================================================
//======================================================================================

#pragma once

//======================================================================================
// INCLUDE
//======================================================================================
#include "Base.h"
#include "CharaBase.h"


//======================================================================================
// CLASS
//======================================================================================
typedef class CBOSSLASER : public CSPRITE
{
protected:
	float Lx[LASER_DIV];
	float Ly[LASER_DIV];
	float Lw[LASER_DIV];
	long Langle[LASER_DIV];
	D3DCOLOR Lcolor[LASER_DIV];

public:

	// function
	CBOSSLASER( float x, float y, long angle );
	virtual ~CBOSSLASER(){}
	virtual bool Action( void );
}
CBOSSLASER, *LPCBOSSLASER;