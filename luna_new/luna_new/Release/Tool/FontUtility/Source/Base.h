
#pragma once

//==========================================================================
// DEFINE
//==========================================================================
#define _CRT_SECURE_NO_DEPRECATE

//==========================================================================
// INCLUDE
//==========================================================================
#include <windows.h>
#include <winnls32.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <shlobj.h>
#include <ddraw.h>


//=============================================================================
// DEFINE
//=============================================================================
#define SAFE_ALLOC(size)					(::VirtualAlloc( NULL, (size), MEM_COMMIT, PAGE_READWRITE ))
#define SAFE_FREE(ptr)						if ( (ptr) != NULL ) { ::VirtualFree( (ptr), 0, MEM_RELEASE ); (ptr) = NULL; }

#define SAFE_DELETE(ptr)					if ( (ptr) != NULL ) { delete (ptr); (ptr) = NULL; }
#define SAFE_DELETES(ptr)					if ( (ptr) != NULL ) { delete [] (ptr); (ptr) = NULL; }

#define SAFE_RELEASE(ptr)					if ( (ptr) != NULL ) { (ptr)->Release(); (ptr) = NULL; }

#define FILE_OPEN_READ(name)				::CreateFile( name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_WRITE(name)				::CreateFile( name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_READ_WRITE(name)			::CreateFile( name, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_CLOSE(handle)					::CloseHandle( handle )
#define FILE_GET_SIZE(handle)				::GetFileSize( handle, NULL )
#define FILE_READ(handle,ptr,size)			{DWORD ReadBytes; ::ReadFile( handle, ptr, size, &ReadBytes, NULL);}
#define FILE_WRITE(handle,ptr,size)			{DWORD WriteBytes; ::WriteFile( handle, ptr, size, &WriteBytes, NULL);}
#define FILE_SEEK_BEGIN(handle,pos)			::SetFilePointer( handle, pos, NULL, FILE_BEGIN )
#define FILE_SEEK_CURRENT(handle,pos)		::SetFilePointer( handle, pos, NULL, FILE_CURRENT )
#define FILE_SEEK_END(handle,pos)			::SetFilePointer( handle, pos, NULL, FILE_END )
#define FILE_SET_TIME(handle,ft0,ft1,ft2)	::SetFileTime( handle, ft0, ft1, ft2 )
#define FILE_GET_TIME(handle,ft0,ft1,ft2)	::GetFileTime( handle, ft0, ft1, ft2 )

#define ef									else if

#define PI									(3.141592653589793238462643383279f)											///< ƒÎ
#define PI2									(6.283185307179586476925286766559f)											///< 2ƒÎ

