

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

	// �t�@�C���̌��݈ʒu���擾
	Uint32 Pos = CFileBase::GetFilePosition();

	// ���ۂɏ�������o�C�g��
	WriteByte = Size;
	if ( WriteByte > m_Size - Pos )
	{
		WriteByte = m_Size - Pos;
	}

	// �t�@�C����������
	return CFileBase::Write( pData, WriteByte );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::Read( void *pData, Uint32 Size )
{
	Uint32 ReadByte = 0;

	// �t�@�C���̌��݈ʒu���擾
	Uint32 Pos = CFileBase::GetFilePosition();

	// ���ۂɏ�������o�C�g��
	ReadByte = Size;
	if ( ReadByte > m_Size - Pos )
	{
		ReadByte = m_Size - Pos;
	}

	// �t�@�C���ǂݍ���
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
	// �t�@�C���̌��݈ʒu���擾
	Uint32 Pos = GetFilePosition();

	Pos = m_Start + Offset;

	// �ʒu���s�����`�F�b�N
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// �t�@�C���ʒu�ݒ�
	CFileBase::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::SeekEnd( Sint32 Offset )
{
	// �t�@�C���̌��݈ʒu���擾
	Uint32 Pos = GetFilePosition();

	Pos = m_Start + m_Size + Offset;

	// �ʒu���s�����`�F�b�N
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// �t�@�C���ʒu�ݒ�
	CFileBase::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CResourceFile::Seek( Sint32 Offset )
{
	// �t�@�C���̌��݈ʒu���擾
	Uint32 Pos = GetFilePosition();

	Pos += Offset;

	// �ʒu���s�����`�F�b�N
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// �t�@�C���ʒu�ݒ�
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

