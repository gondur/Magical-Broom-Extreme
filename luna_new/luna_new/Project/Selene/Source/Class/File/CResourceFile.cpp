

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "File/CResourceFile.h"
#include "System.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CResourceFile::CResourceFile( const wchar_t *pFileName ) : CFileBase( pFileName, FILE_OPEN_TYPE_READ )
	, m_IsPack	( false )
	, m_Start	( 0 )
	, m_Size	( 0 )
{
	::StringCbCopy( m_FileName, sizeof(m_FileName), pFileName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CResourceFile::~CResourceFile()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::Write( const void *pData, Uint32 Size )
{
	Uint32 WriteByte = 0;

	// ファイルの現在位置を取得
	Uint32 Pos = CFileBase::GetFilePosition();

	// 実際に処理するバイト数
	WriteByte = Size;
	if ( WriteByte > m_Size - Pos )
	{
		WriteByte = m_Size - Pos;
	}

	// ファイル書き込み
	return CFileBase::Write( pData, WriteByte );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::Read( void *pData, Uint32 Size )
{
	Uint32 ReadByte = 0;

	// ファイルの現在位置を取得
	Uint32 Pos = CFileBase::GetFilePosition();

	// 実際に処理するバイト数
	ReadByte = Size;
	if ( ReadByte > m_Size - Pos )
	{
		ReadByte = m_Size - Pos;
	}

	// ファイル読み込み
	return CFileBase::Read( pData, ReadByte );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::GetFileStart( void )
{
	return m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::GetFileSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::SeekStart( Sint32 Offset )
{
	// ファイルの現在位置を取得
	Uint32 Pos = GetFilePosition();

	Pos = m_Start + Offset;

	// 位置が不正かチェック
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// ファイル位置設定
	CFileBase::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::SeekEnd( Sint32 Offset )
{
	// ファイルの現在位置を取得
	Uint32 Pos = GetFilePosition();

	Pos = m_Start + m_Size + Offset;

	// 位置が不正かチェック
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// ファイル位置設定
	CFileBase::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::Seek( Sint32 Offset )
{
	// ファイルの現在位置を取得
	Uint32 Pos = GetFilePosition();

	Pos += Offset;

	// 位置が不正かチェック
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// ファイル位置設定
	CFileBase::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::GetFilePosition( void )
{
	return CFileBase::Seek( 0 );
}	

