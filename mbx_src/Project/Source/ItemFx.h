//======================================================================================
//======================================================================================
//
//
//			�A�C�e���擾�G�t�F�N�g
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
typedef class CITEMFX : public CSPRITE
{
protected:
	long No;

public:

	// function
	CITEMFX( float x, float y, long no );
	virtual ~CITEMFX(){}
	virtual bool Action( void );
}
CITEMFX, *LPCITEMFX;