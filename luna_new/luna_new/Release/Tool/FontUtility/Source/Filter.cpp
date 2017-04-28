

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
//		�G�b�W�t�B���^�[
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
//		�e�t�B���^�[
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
//		�G�b�W�t�B���^�[
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
//		�e�t�B���^�[
//
//==========================================================================
CSurface *FilterShadow( CSurface *pSurf, long dir )
{
	CSurface *pDst = new CSurface();
	pDst->Create( pSurf->GetWidth()+1, pSurf->GetHeight()+1 );

	return pDst;
}
