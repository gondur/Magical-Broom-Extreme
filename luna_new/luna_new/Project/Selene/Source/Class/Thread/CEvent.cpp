

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "CEvent.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CEvent::CEvent( Bool IsSignal, Uint32 Count )
{
	for ( Uint32 i = 0; i < MAXIMUM_WAIT_OBJECTS; i++ )
	{
		m_EventHandle[i] = NULL;
	}

	m_HandleCount = Count;
	for ( Uint32 i = 0; i < Count; i++ )
	{
		m_EventHandle[i] = ::CreateEvent( NULL, false, IsSignal, NULL );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CEvent::~CEvent()
{
	for ( Uint32 i = 0; i < m_HandleCount; i++ )
	{
		::CloseHandle( m_EventHandle[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CEvent::Set( Uint32 No )
{
	if ( m_EventHandle[No] != NULL )
	{
		::SetEvent( m_EventHandle[No] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CEvent::Reset( Uint32 No )
{
	if ( m_EventHandle[No] != NULL )
	{
		::ResetEvent( m_EventHandle[No] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CEvent::IsSignal( Uint32 No )
{
	Uint32 Ret = ::WaitForMultipleObjects( m_HandleCount, m_EventHandle, false, 0 );
	return Ret - WAIT_OBJECT_0 == No;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CEvent::IsSignalAll( void )
{
	Uint32 Ret = ::WaitForMultipleObjects( m_HandleCount, m_EventHandle, true, 0 );
	return Ret != WAIT_TIMEOUT;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CEvent::Wait( Uint32 TimeOut )
{
	Uint32 Ret = ::WaitForMultipleObjects( m_HandleCount, m_EventHandle, false, TimeOut == -1 ? INFINITE : TimeOut );
	return Ret == WAIT_TIMEOUT ? -1 : Ret - WAIT_OBJECT_0;
}

