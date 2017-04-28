

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Object/CBaseList.h"

using namespace Selene;

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseList::CBaseList()
{
	m_pTop	= NULL;
	m_pEnd	= NULL;
	m_Count	= 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseList::~CBaseList()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::Init( void )
{
	m_pTop	= NULL;
	m_pEnd	= NULL;
	m_Count	= 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::InsertTop( CBaseObject *pObj )
{
	if ( m_pTop != NULL )
	{
		pObj->m_pPrev = NULL;
		pObj->m_pNext = m_pTop;
		m_pTop = pObj;
		if ( m_pTop->m_pNext != NULL )
		{
			m_pTop->m_pNext->m_pPrev = m_pTop;
		}
	}
	else
	{
		m_pTop = pObj;
		m_pEnd = pObj;
		pObj->m_pPrev = NULL;
		pObj->m_pNext = NULL;
	}
	m_Count++;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::InsertEnd( CBaseObject *pObj )
{
	if ( m_pEnd != NULL )
	{
		pObj->m_pPrev = m_pEnd;
		pObj->m_pNext = NULL;
		m_pEnd->m_pNext = pObj;
		m_pEnd = pObj;
	}
	else
	{
		m_pTop = pObj;
		m_pEnd = pObj;
		pObj->m_pPrev = NULL;
		pObj->m_pNext = NULL;
	}
	m_Count++;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::Erase( CBaseObject *pObj )
{
	if ( pObj->m_pPrev == NULL )
	{
		if ( pObj->m_pNext == NULL )
		{
			m_pTop = NULL;
			m_pEnd = NULL;
		}
		else
		{
			m_pTop = pObj->m_pNext;
			pObj->m_pNext->m_pPrev = NULL;
		}
	}
	else
	{
		if ( pObj->m_pNext == NULL )
		{
			m_pEnd = m_pEnd->m_pPrev;
			m_pEnd->m_pNext = NULL;
		}
		else
		{
			pObj->m_pNext->m_pPrev = pObj->m_pPrev;
			pObj->m_pPrev->m_pNext = pObj->m_pNext;
		}
	}
	m_Count--;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetTop( void )
{
	return m_pTop;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetEnd( void )
{
	return m_pEnd;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetPrev( CBaseObject *pObj )
{
	return pObj->m_pPrev;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetNext( CBaseObject *pObj )
{
	return pObj->m_pNext;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetByIndex( Uint32 Index )
{
	CBaseObject *pObj = m_pTop;
	while ( pObj != NULL )
	{
		if ( Index == 0 )
		{
			return pObj;
		}
		pObj = pObj->m_pNext;
		Index--;
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseList::GetCount( void )
{
	return m_Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::SearchFromName( const wchar_t *pName )
{
	CBaseObject *pObj = m_pTop;
	while ( pObj != NULL )
	{
		if ( pObj->IsSame( pName ) )
		{
			return pObj;
		}

		pObj = pObj->m_pNext;
	}

	return NULL;
}

