//======================================================================================
//======================================================================================
//
//
//			�V���b�g
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
typedef class CSHOT : public CSPRITE
{
public:

	// function
	CSHOT( float x, float y, long angle );
	virtual ~CSHOT(){}
	virtual bool Action( void );

	virtual void Damage( long pow );
}
CSHOT, *LPCSHOT;