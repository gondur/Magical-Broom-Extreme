
#pragma once


//==========================================================================
// INCLUDE
//==========================================================================
#include "Base.h"
#include "Surface.h"


//==========================================================================
// CLASS
//==========================================================================
void FilterShadow( CSurface **ppSurf, long dir, long pow );
void FilterEdge( CSurface **ppSurf, long pow );