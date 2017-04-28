
#pragma once


//==========================================================================
// INCLUDE
//==========================================================================
#include "Base.h"


//==========================================================================
// STRUCT
//==========================================================================
typedef struct STRING
{
	char Buff[4];
	unsigned short Code;
}
STRING, *LPSTRING;


//==========================================================================
// PROTOTYPE
//==========================================================================
void CutString( char *pFileName );
long GetStringCount( void );
STRING *GetStringBuffer( void );
bool IsKanji( unsigned char c );
unsigned short GetCharCode( unsigned char *pStr );

