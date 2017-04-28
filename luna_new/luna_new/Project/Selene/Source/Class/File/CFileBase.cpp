

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "File/CFileBase.h"
#include "System.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
CFileBase::CFileBase( const wchar_t *pFileName, eFileOpenType Type )
{
	Uint32 Generic;
	Uint32 Create;

	m_hFile = INVALID_HANDLE_VALUE;
	m_Type  = FILE_OPEN_TYPE_INVALID;

	switch ( Type )
	{
	case FILE_OPEN_TYPE_WRITE:
		Generic = GENERIC_WRITE;
		Create  = CREATE_ALWAYS;
		break;

	case FILE_OPEN_TYPE_READ:
		Generic = GENERIC_READ;
		Create  = OPEN_EXISTING;
		break;

	case FILE_OPEN_TYPE_READ_WRITE:
		Generic = GENERIC_READ | GENERIC_WRITE;
		Create  = OPEN_EXISTING;
		break;

	default:
		return;
	}

	System::ResetCurrentDirectory();

	m_hFile = ::CreateFile( pFileName, Generic, FILE_SHARE_READ, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( m_hFile == INVALID_HANDLE_VALUE ) return;

	::GetFileTime( m_hFile, &m_TimeCreate, &m_TimeAccess, &m_TimeLastWrite );
	m_Type = Type;
}

CFileBase::~CFileBase()
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return;

	::SetFileTime( m_hFile, &m_TimeCreate, &m_TimeAccess, &m_TimeLastWrite );
	::CloseHandle( m_hFile );
}

Bool CFileBase::IsOpened( void )
{
	return m_hFile != INVALID_HANDLE_VALUE;
}

Uint32 CFileBase::Write( const void *pData, Uint32 Size )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	Uint32 WriteBytes;
	::WriteFile( m_hFile, pData, Size, &WriteBytes, NULL);
	return WriteBytes;
}

Uint32 CFileBase::Read( void *pData, Uint32 Size )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	Uint32 ReadBytes;
	::ReadFile( m_hFile, pData, Size, &ReadBytes, NULL);
	return ReadBytes;
}

Uint32 CFileBase::GetFileSize( void )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::GetFileSize( m_hFile, NULL );
}

Uint32 CFileBase::SeekStart( Sint32 Offset )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::SetFilePointer( m_hFile, Offset, NULL, FILE_BEGIN );
}

Uint32 CFileBase::SeekEnd( Sint32 Offset )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::SetFilePointer( m_hFile, Offset, NULL, FILE_END );
}

Uint32 CFileBase::Seek( Sint32 Offset )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::SetFilePointer( m_hFile, Offset, NULL, FILE_CURRENT );
}

Uint32 CFileBase::GetFilePosition( void )
{
	return Seek( 0 );
}	
