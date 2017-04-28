

//=============================================================================
// INCLUDE
//=============================================================================
#include <stdio.h>
#include <windows.h>
#include "FilePack.h"


//=============================================================================
// DEFINE
//=============================================================================
#define FILE_MAX						(65536)

#define FILE_OPEN_READ(name)			CreateFile( name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_WRITE(name)			CreateFile( name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_CLOSE(handle)				CloseHandle( handle )
#define FILE_GET_SIZE(handle)			GetFileSize( handle, NULL )
#define FILE_READ(handle,ptr,size)		{DWORD ReadBytes; ReadFile( handle, ptr, size, &ReadBytes, NULL);}
#define FILE_WRITE(handle,ptr,size)		{DWORD WriteBytes; WriteFile( handle, ptr, size, &WriteBytes, NULL);}
#define FILE_SEEK(handle,pos,start)		SetFilePointer( handle, pos, NULL, start )


//=============================================================================
/**
*/
//=============================================================================
CFilePack::CFilePack()
{
	m_pFileData = NULL;
	m_FileCount = 0;
}

//=============================================================================
/**
*/
//=============================================================================
CFilePack::~CFilePack()
{
}

//=============================================================================
/**
*/
//=============================================================================
bool CFilePack::CutAfterStr( char *pDst, const char *pSrc, char c )
{
	strcpy( pDst, pSrc );
	size_t Len = strlen( pDst );

	while ( pDst[Len] != c )
	{
		if ( --Len < 0 )
		{
			return false;
		}
	}

	pDst[Len] = '\0';

	return true;
}

//=============================================================================
/**
*/
//=============================================================================
bool CFilePack::CreateDirectory( const char *pPath )
{
	SECURITY_ATTRIBUTES Attribute = { sizeof(SECURITY_ATTRIBUTES) };
	char Temp[MAX_PATH] = "";
	unsigned long No = 0;
	unsigned long Len = (unsigned long)strlen( pPath );
	
	while ( No < Len )
	{
		// �t�H���_���擾
		while ( No < Len )
		{
			if ( (pPath[No] == '\\') && (No != '\0') )
			{
				if ( Temp[No-1] != ':' )
				{
					break;
				}
			}
			Temp[No] = pPath[No];
			No++;
		}
		Temp[No] = '\0';

		::CreateDirectory( Temp, &Attribute );

		Temp[No++] = '\\';
	}
	
	return true;
}

//=============================================================================
/**
*/
//=============================================================================
unsigned long CFilePack::GetCRC( unsigned char Data[], unsigned long Size )
{
	unsigned long r = 0xFFFFFFFF;

	for ( unsigned long i = 0; i < Size; i++ )
	{
		r ^= (unsigned long)Data[i];
		for ( unsigned long j = 0; j < 8; j++ )
		{
			if ( (r & 1) != 0 )
			{
				r = (r >> 1) ^ 0xEDB88320;
			}
			else
			{
				r >>= 1;
			}
		}
	}

	return r ^ 0xFFFFFFFF;
}

//=============================================================================
/**
*/
//=============================================================================
bool CFilePack::IsKanji( unsigned char Chara )
{
	if ( Chara <= 0x80 ) return false;	// ����R�[�h������
	if ( Chara <= 0x9F ) return true;
	if ( Chara <= 0xDF ) return false;	// ���p�J�i
	if ( Chara <= 0xFE ) return true;

	return false;
}

//=============================================================================
/**
*/
//=============================================================================
void CFilePack::CreateFileList( const char *pSearchDir, const char *pRootDir )
{
	WIN32_FIND_DATA FindData;
	char FilePath[MAX_PATH] = "";
	HANDLE hFile;

	//-------------------------------------------------
	// �t�@�C���̃��C���h�J�[�h�ݒ�
	//-------------------------------------------------
	sprintf( FilePath, "%s\\*.*", pSearchDir );
	printf( "Search Directory [%s]\n", FilePath );

	//-------------------------------------------------
	// ��ڂ̃t�@�C��
	//-------------------------------------------------
	hFile = FindFirstFile( FilePath, &FindData );
	if ( hFile == INVALID_HANDLE_VALUE ) return;

	//-------------------------------------------------
	// �t�@�C������
	//-------------------------------------------------
	do
	{
		char *pFile = FindData.cFileName;

		// ���݂̃f�B���N�g��
		if ( strcmp( pFile, "." ) == 0 )
		{
		}
		// �ЂƂ�̃f�B���N�g��
		else
		if ( strcmp( pFile, ".." ) == 0 )
		{
		}
		// �B���t�@�C���̓X���[
		else
		if( (FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0 )
		{
		}
		// �T�u�f�B���N�g��
		else
		if ( (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 )
		{
			char Directory[256] = "";
			sprintf( Directory, "%s\\%s", pSearchDir, pFile );
			CreateFileList( Directory, pRootDir );
		}
		// �t�@�C��
		else
		{
			// �T�C�Y�`�F�b�N
			if ( FindData.nFileSizeLow == 0 )
			{
				printf( "  �T�C�Y 0Byte �̃t�@�C�� [%s]\n", pFile );
			}
			else
			{
				char Temp[MAX_PATH] = "";

				// ���΃p�X�H
				if ( pFile[1] != ':' )
				{
					// ��΃p�X��
					sprintf( Temp, "%s\\%s", pSearchDir, pFile );
					pFile = Temp;
				}

				// �p�X����t�@�C�������擾����
				size_t Len = strlen( pRootDir );

				// �t�@�C����
				strcpy( m_pFileData[m_FileCount].FileName, pFile + Len + 1 );
				// �t�@�C���T�C�Y
				m_pFileData[m_FileCount].Size = FindData.nFileSizeLow;
				// �t�@�C�������Z
				m_FileCount++;
			}
		}
	}
	while ( ::FindNextFile( hFile, &FindData ) );

	::FindClose( hFile );
}

//=============================================================================
/**
*/
//=============================================================================
unsigned long CFilePack::ComputeAligned( unsigned long Aligned )
{
	if ( Aligned != 0 )
	{
		// �r�b�g�̗����Ă��鐔���Z�o
		long Bit = 0;
		for ( long i = 0; i < 32; i++ )
		{
			if ( (Aligned & (1 << i)) != 0 )
			{
				Bit++;
			}
		}

		// �r�b�g�������Ă���ӏ���1�Ŗ����Ƃ�
		if ( Bit != 1 )
		{
			// �A���C�����g�Ȃ�
			Aligned = 0;
		}
		else
		{
			Aligned -= 1;
		}
	}

	return Aligned;
}

//=============================================================================
/**
*/
//=============================================================================
void CFilePack::ComputeNameCRC( void )
{
	// �t�@�C��������CRC�擾
	for ( unsigned long i = 0; i < m_FileCount; i++ )
	{
		// �S�p�t�@�C�����`�F�b�N
		unsigned char *pStr = (unsigned char *)m_pFileData[i].FileName;
		while ( *pStr != '\0' )
		{
			if ( IsKanji( *pStr ) )
			{
				pStr++;
			}
			else
			if ( *pStr == '/' )
			{
				*pStr = '\\';
			}
			else
			if ( ('a' <= *pStr) && (*pStr <= 'z') )
			{
				*pStr -= 'a' - 'A';
			}

			pStr++;
		}

		// �t�@�C����CRC�擾
		m_pFileData[i].NameCrc = GetCRC( (unsigned char*)m_pFileData[i].FileName, (unsigned long)strlen(m_pFileData[i].FileName) );
	}
}

//=============================================================================
/**
*/
//=============================================================================
bool CFilePack::Encode( const char *pSrcDirName, unsigned long Aligned )
{
	FILEPACK_HEADER Bin = { 'P','A','C','K', 0 };
	unsigned long Address = sizeof(FILEPACK_HEADER);
	char SrcDir[MAX_PATH] = "";
	char SrcFile[MAX_PATH] = "";
	char PackFile[MAX_PATH] = "";
	HANDLE hWrite, hRead;

	//----------------------------------------------------------------------------------------
	// �p�b�N�t�@�C����
	//----------------------------------------------------------------------------------------
	sprintf( PackFile, "%s.bin", pSrcDirName );

	//----------------------------------------------------------------------------------------
	// ���̓f�B���N�g��
	//----------------------------------------------------------------------------------------
	strcpy( SrcDir, pSrcDirName );
	size_t Len = strlen( SrcDir );
	if ( SrcDir[Len-1] == '\\' )
	{
		SrcDir[Len-1] = '\0';
	}

	//----------------------------------------------------------------------------------------
	// �A���C�����g�l
	//----------------------------------------------------------------------------------------
	Aligned = ComputeAligned( Aligned );

	//----------------------------------------------------------------------------------------
	// �f�B���N�g���H
	//----------------------------------------------------------------------------------------
	if ( (::GetFileAttributes( SrcDir ) & FILE_ATTRIBUTE_DIRECTORY) != 0 )
	{
		printf( "Packing...... [%s] -> [%s]\n", SrcDir, PackFile );

		m_FileCount = 0;

		//----------------------------------------------------------------------------
		// �t�@�C���Ǘ��p�������m��
		//----------------------------------------------------------------------------
		m_pFileData = (FILEPACK_DATA*)SAFE_ALLOC( sizeof(FILEPACK_DATA[FILE_MAX]) );
		if ( m_pFileData != NULL )
		{
			//-------------------------------------------------------
			// �t�@�C�����X�g����
			//-------------------------------------------------------
			CreateFileList( SrcDir, pSrcDirName );
			printf( "Find : %d\n", m_FileCount );

			Bin.FileCount = m_FileCount;
			Address += sizeof(FILEPACK_DATA) * Bin.FileCount;

			//-------------------------------------------------------
			// �t�@�C������CRC���Z�o
			//-------------------------------------------------------
			ComputeNameCRC();

			//-------------------------------------------------------
			// �t�@�C���A�N�Z�X�p�A�h���X�ݒ�
			//-------------------------------------------------------
			for ( unsigned long i = 0; i < m_FileCount; i++ )
			{
				// �A�h���X�̃A���C�����g
				Address = (Address + Aligned) & ~Aligned;
				// �A�h���X
				m_pFileData[i].Address = Address;
				// �A�h���X���Z
				Address += m_pFileData[i].Size;
			}

			//-------------------------------------------------------
			// �������ݗp�t�@�C���I�[�v��
			//-------------------------------------------------------
			hWrite = FILE_OPEN_WRITE( PackFile );
			if ( hWrite != INVALID_HANDLE_VALUE )
			{
				// �t�@�C���w�b�_�����o��
				FILE_WRITE( hWrite, &Bin, sizeof(FILEPACK_HEADER) );
				// �t�@�C���f�[�^�e�[�u�������o��
				FILE_WRITE( hWrite, m_pFileData, sizeof(FILEPACK_DATA) * m_FileCount );

				// �t�@�C�������o��
				for ( unsigned long i = 0; i < m_FileCount; i++ )
				{
					sprintf( SrcFile, "%s\\%s", pSrcDirName, m_pFileData[i].FileName );
					hRead = FILE_OPEN_READ( SrcFile );
					if ( hRead != INVALID_HANDLE_VALUE )
					{
						unsigned long Size = FILE_GET_SIZE( hRead );
						void *pData = SAFE_ALLOC( Size );
						if ( pData != NULL )
						{
							// �t�@�C���ǂݍ���
							FILE_READ( hRead, pData, Size );
							// �t�@�C����CRC�Z�o
							m_pFileData[i].DataCrc = GetCRC( (unsigned char *)pData, Size );
							// �Y���A�h���X�܂łO�Ŗ��߂�
							while ( FILE_SEEK( hWrite, 0, FILE_CURRENT ) != m_pFileData[i].Address )
							{
								unsigned char Data = 0x00;
								FILE_WRITE( hWrite, &Data, sizeof(unsigned char) );
							}
							// �t�@�C���o��
							FILE_WRITE( hWrite, pData, Size );

							SAFE_FREE( pData );

							printf( "Packing... [0x%08X] [%9d byte] [%s]\n", m_pFileData[i].NameCrc, m_pFileData[i].Size, m_pFileData[i].FileName );
						}

						// �t�@�C������
						FILE_CLOSE( hRead );
					}
				}

				// �t�@�C�������Ƀo�C�i���T�[�`���g����悤��CRC�Ńt�@�C�����X�g���\�[�g
				for ( unsigned long i = 0; i < m_FileCount; i++ )
				{
					for ( unsigned long j = 0; j < m_FileCount; j++ )
					{
						if ( m_pFileData[i].NameCrc < m_pFileData[j].NameCrc )
						{
							FILEPACK_DATA Temp = m_pFileData[i];
							m_pFileData[i] = m_pFileData[j];
							m_pFileData[j] = Temp;
						}
					}
				}

				// �t�@�C���f�[�^�e�[�u�������o������
				FILE_SEEK( hWrite, sizeof(FILEPACK_HEADER), FILE_BEGIN );
				FILE_WRITE( hWrite, m_pFileData, sizeof(FILEPACK_DATA) * m_FileCount );

				// �t�@�C������
				FILE_CLOSE( hWrite );
			}

			// �t�@�C���Ǘ��p���������
			SAFE_FREE( m_pFileData );
		}

		printf( "End...\n" );

		return true;
	}

	return false;
}

//=============================================================================
/**
*/
//=============================================================================
bool CFilePack::Decode( const char *pPackFileName )
{
	char Guid[8]				= "";
	char Temp[MAX_PATH]			= "";
	char FilePath[MAX_PATH]		= "";
	char DirPath[MAX_PATH]		= "";
	unsigned long FileCount		= 0;
	FILEPACK_DATA *pFileData	= NULL;

	//----------------------------------------------------------------------------------------
	// �f�B���N�g���H
	//----------------------------------------------------------------------------------------
	if ( (::GetFileAttributes( pPackFileName ) & FILE_ATTRIBUTE_DIRECTORY) == 0 )
	{
		printf( "UnPacking...... [%s]\n", pPackFileName );

		//---------------------------------------------------------------------------------
		// �t�@�C���I�[�v��
		//---------------------------------------------------------------------------------
		HANDLE hPack = FILE_OPEN_READ( pPackFileName );
		if ( hPack != INVALID_HANDLE_VALUE )
		{
			//---------------------------------------------------------------------------
			// �t�@�C���w�b�_
			//---------------------------------------------------------------------------
			FILE_READ( hPack, Guid, sizeof(char[4]) );
			if ( !strcmp( Guid, "PACK" ) )
			{
				//-------------------------------------------------------------------
				// �t�@�C����
				//-------------------------------------------------------------------
				FILE_READ( hPack, &FileCount, sizeof(unsigned long) );
				printf( "  File Count [%d]\n", FileCount );

				pFileData = (FILEPACK_DATA*)SAFE_ALLOC( sizeof(FILEPACK_DATA) * FileCount );
				if ( pFileData != NULL )
				{
					CutAfterStr( DirPath, pPackFileName, '.' );

					// �t�@�C���f�[�^�e�[�u�������o��
					FILE_READ( hPack, pFileData, sizeof(FILEPACK_DATA) * FileCount );

					// �t�@�C���W�J
					for ( int i = 0; i < FileCount; i++ )
					{
						void *pData = SAFE_ALLOC( pFileData[i].Size );
						if ( pData != NULL )
						{
							sprintf( FilePath, "%s\\%s", DirPath, pFileData[i].FileName );
							printf( "    File Path        [%s]\n", FilePath );
							CutAfterStr( Temp, FilePath, '\\' );
							CreateDirectory( Temp );
							printf( "    Create Directory [%s]\n", Temp );

							// �t�@�C�������o��
							HANDLE hWritePack = FILE_OPEN_WRITE( FilePath );
							if ( hWritePack != INVALID_HANDLE_VALUE )
							{
								printf( "        Save [%s]\n", FilePath );

								FILE_SEEK( hPack, pFileData[i].Address, FILE_BEGIN );
								FILE_READ( hPack, pData, pFileData[i].Size );

								FILE_WRITE( hWritePack, pData, pFileData[i].Size );
								FILE_CLOSE( hWritePack );
							}
		
							SAFE_FREE( pData );
						}
					}

					SAFE_FREE( pFileData );
	
					printf( "End...\n" );
				}
			}

			FILE_CLOSE( hPack );
		}
	}

	return false;
}

//=============================================================================
/**
*/
//=============================================================================
bool CFilePack::Load( const char *pPackFile, const char *pDataName, void **ppData, unsigned long *pSize )
{
	HANDLE hRead;

	(*pSize) = 0;
	(*ppData) = NULL;

	hRead = FILE_OPEN_READ( pPackFile );
	if ( hRead != INVALID_HANDLE_VALUE )
	{
		char Guid[8];
		unsigned long FileCount;
		FILEPACK_DATA *pFileData;

		// �w�b�_�擾
		FILE_READ( hRead, &Guid, sizeof(char[4]) );
		if ( !strcmp( Guid, "PACK" ) )
		{
			// �t�@�C�����擾
			FILE_READ( hRead, &FileCount, sizeof(unsigned long) );
			// �t�@�C���f�[�^�擾
			pFileData = (FILEPACK_DATA*)SAFE_ALLOC( sizeof(FILEPACK_DATA) * FileCount );
			if ( pFileData != NULL )
			{
				unsigned long NameCRC = GetCRC( (unsigned char*)pDataName, (unsigned long)strlen( pDataName ) );
				for ( unsigned long i = 0; i < FileCount; i++ )
				{
					if ( pFileData[i].NameCrc == NameCRC )
					{
						(*pSize) = pFileData[i].Size;
						(*ppData) = SAFE_ALLOC( *pSize );

						FILE_SEEK( hRead, pFileData[i].Address, FILE_BEGIN );
						FILE_READ( hRead, *ppData, pFileData[i].Size );

						break;
					}
				}
				SAFE_FREE( pFileData );
			}
		}

		FILE_CLOSE( hRead );
	}

	return ((*ppData) != NULL) && ((*pSize) > 0);
}


