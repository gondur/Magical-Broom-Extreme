

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Math/Random.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static const Uint32 M			= 397UL;
static const Uint32 MATRIX_A	= 0x9908B0DFUL;
static const Uint32 UPPER_MASK	= 0x80000000UL;
static const Uint32 LOWER_MASK	= 0x7FFFFFFFUL;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRandom::CRandom()
{
	Seed( ::timeGetTime() );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRandom::CRandom( Uint32 Param )
{
	Seed( Param );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CRandom::GenerateInt32( void )
{
    Uint32 Mag01[2] = { 0x00000000UL, MATRIX_A };
    Uint32 Param;

    if ( MersenneTwisterCount >= N )
	{
        Sint32 kk = 0;

		while ( kk < N - M )
		{
            Param = (MersenneTwister[kk] & UPPER_MASK) | (MersenneTwister[kk+1] & LOWER_MASK);
            MersenneTwister[kk] = MersenneTwister[kk + M] ^ (Param >> 1) ^ Mag01[Param & 0x01];

			kk++;
		}

		while ( kk < N - 1 )
		{
            Param = (MersenneTwister[kk] & UPPER_MASK) | (MersenneTwister[kk + 1] & LOWER_MASK);
            MersenneTwister[kk] = MersenneTwister[kk + (M - N)] ^ (Param >> 1) ^ Mag01[Param & 0x00000001UL];

			kk++;
		}

		Param = (MersenneTwister[N - 1]&UPPER_MASK) | (MersenneTwister[0] & LOWER_MASK);
        MersenneTwister[N - 1] = MersenneTwister[M-1] ^ (Param >> 1) ^ Mag01[Param & 0x00000001UL];

        MersenneTwisterCount = 0;
    }
  
    Param = MersenneTwister[MersenneTwisterCount++];

    /* Tempering */
    Param ^= (Param >> 11);
    Param ^= (Param <<  7) & 0x9D2C5680UL;
    Param ^= (Param << 15) & 0xEFC60000UL;
    Param ^= (Param >> 18);

    return Param;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRandom::Seed( Uint32 Param )
{
    MersenneTwister[0] = Param & 0xFFFFFFFFUL;
    for ( MersenneTwisterCount = 1; MersenneTwisterCount < N; MersenneTwisterCount++ )
	{
        MersenneTwister[MersenneTwisterCount] = (1812433253UL * (MersenneTwister[MersenneTwisterCount-1] ^ (MersenneTwister[MersenneTwisterCount-1] >> 30)) + MersenneTwisterCount); 
        MersenneTwister[MersenneTwisterCount] &= 0xFFFFFFFFUL;
    }
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CRandom::GetInt32( void )
{
    return GenerateInt32();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint64 CRandom::GetInt64( void )
{
	Uint64 a = GenerateInt32();
	Uint64 b = GenerateInt32();

	return (a << 32) | b;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRandom::GetFloat32( void )
{
	const Uint32 RANDOM_MAX	= 100000000;

    return toF(GenerateInt32() % (RANDOM_MAX+1)) / toF(RANDOM_MAX);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRandom::GetInt( Sint32 Min, Sint32 Max )
{
	Sint32 a = (Sint32)(GetInt32() >> 1);

	return Min + (a % (Max + 1 - Min));
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRandom::GetFloat( Float Min, Float Max )
{
	Float a = GetFloat32();

	return Min + (a * (Max - Min));
}

