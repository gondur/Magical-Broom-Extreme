//======================================================================================
//======================================================================================
//
//
//			�{��
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
typedef class CBOMB : public CSPRITE
{
protected:

public:

	// function
	CBOMB( void );
	virtual ~CBOMB() {}
	virtual bool Action( void );

	virtual void Damage( long pow ) {}
}
CBOMB, *LPCBOMB;