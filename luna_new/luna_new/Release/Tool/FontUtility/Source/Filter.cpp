

//==========================================================================
// INCLUDE
//==========================================================================
#include "Filter.h"


//==========================================================================
// PROTOTYPE
//==========================================================================
CSurface *FilterShadow( CSurface *pSurf, long dir );
CSurface *FilterEdge( CSurface *pSurf );


//==========================================================================
//
//		エッジフィルター
//
//==========================================================================
void FilterEdge( CSurface **ppSurf, long pow )
{
	CSurface *pSrc = *ppSurf;
	CSurface *pDst = NULL;

	for ( long i = 0; i < pow; i++ )
	{
		pDst = FilterEdge( pSrc );
		delete pSrc;
		pSrc = pDst;
	}

	*ppSurf = pDst;
}

//==========================================================================
//
//		影フィルター
//
//==========================================================================
void FilterShadow( CSurface **ppSurf, long dir, long pow )
{
	CSurface *pSrc = *ppSurf;
	CSurface *pDst = NULL;

	for ( long i = 0; i < pow; i++ )
	{
		pDst = FilterShadow( pSrc, dir );
		delete pSrc;
		pSrc = pDst;
	}

	*ppSurf = pDst;
}

//==========================================================================
//
//		エッジフィルター
//
//==========================================================================
CSurface *FilterEdge( CSurface *pSurf )
{
	CSurface *pDst = new CSurface();
	pDst->Create( pSurf->GetWidth()+1, pSurf->GetHeight()+1 );

	return pDst;
}

//==========================================================================
//
//		影フィルター
//
//==========================================================================
CSurface *FilterShadow( CSurface *pSurf, long dir )
{
	CSurface *pDst = new CSurface();
	pDst->Create( pSurf->GetWidth()+1, pSurf->GetHeight()+1 );

	return pDst;
}
