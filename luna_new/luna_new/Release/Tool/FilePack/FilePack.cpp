

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
		// フォルダ名取得
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
	if ( Chara <= 0x80 ) return false;	// 制御コード＆文字
	if ( Chara <= 0x9F ) return true;
	if ( Chara <= 0xDF ) return false;	// 半角カナ
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
	// ファイルのワイルドカード設定
	//-------------------------------------------------
	sprintf( FilePath, "%s\\*.*", pSearchDir );
	printf( "Search Directory [%s]\n", FilePath );

	//-------------------------------------------------
	// 一つ目のファイル
	//-------------------------------------------------
	hFile = FindFirstFile( FilePath, &FindData );
	if ( hFile == INVALID_HANDLE_VALUE ) return;

	//-------------------------------------------------
	// ファイル検索
	//-------------------------------------------------
	do
	{
		char *pFile = FindData.cFileName;

		// 現在のディレクトリ
		if ( strcmp( pFile, "." ) == 0 )
		{
		}
		// ひとつ上のディレクトリ
		else
		if ( strcmp( pFile, ".." ) == 0 )
		{
		}
		// 隠しファイルはスルー
		else
		if( (FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0 )
		{
		}
		// サブディレクトリ
		else
		if ( (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 )
		{
			char Directory[256] = "";
			sprintf( Directory, "%s\\%s", pSearchDir, pFile );
			CreateFileList( Directory, pRootDir );
		}
		// ファイル
		else
		{
			// サイズチェック
			if ( FindData.nFileSizeLow == 0 )
			{
				printf( "  サイズ 0Byte のファイル [%s]\n", pFile );
			}
			else
			{
				char Temp[MAX_PATH] = "";

				// 相対パス？
				if ( pFile[1] != ':' )
				{
					// 絶対パスに
					sprintf( Temp, "%s\\%s", pSearchDir, pFile );
					pFile = Temp;
				}

				// パスからファイル名を取得する
				size_t Len = strlen( pRootDir );

				// ファイル名
				strcpy( m_pFileData[m_FileCount].FileName, pFile + Len + 1 );
				// ファイルサイズ
				m_pFileData[m_FileCount].Size = FindData.nFileSizeLow;
				// ファイル数加算
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
		// ビットの立っている数を算出
		long Bit = 0;
		for ( long i = 0; i < 32; i++ )
		{
			if ( (Aligned & (1 << i)) != 0 )
			{
				Bit++;
			}
		}

		// ビットが立っている箇所が1つで無いとき
		if ( Bit != 1 )
		{
			// アライメントなし
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
	// ファイル名からCRC取得
	for ( unsigned long i = 0; i < m_FileCount; i++ )
	{
		// 全角ファイル名チェック
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

		// ファイルのCRC取得
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
	// パックファイル名
	//----------------------------------------------------------------------------------------
	sprintf( PackFile, "%s.bin", pSrcDirName );

	//----------------------------------------------------------------------------------------
	// 入力ディレクトリ
	//----------------------------------------------------------------------------------------
	strcpy( SrcDir, pSrcDirName );
	size_t Len = strlen( SrcDir );
	if ( SrcDir[Len-1] == '\\' )
	{
		SrcDir[Len-1] = '\0';
	}

	//----------------------------------------------------------------------------------------
	// アライメント値
	//----------------------------------------------------------------------------------------
	Aligned = ComputeAligned( Aligned );

	//----------------------------------------------------------------------------------------
	// ディレクトリ？
	//----------------------------------------------------------------------------------------
	if ( (::GetFileAttributes( SrcDir ) & FILE_ATTRIBUTE_DIRECTORY) != 0 )
	{
		printf( "Packing...... [%s] -> [%s]\n", SrcDir, PackFile );

		m_FileCount = 0;

		//----------------------------------------------------------------------------
		// ファイル管理用メモリ確保
		//----------------------------------------------------------------------------
		m_pFileData = (FILEPACK_DATA*)SAFE_ALLOC( sizeof(FILEPACK_DATA[FILE_MAX]) );
		if ( m_pFileData != NULL )
		{
			//-------------------------------------------------------
			// ファイルリスト生成
			//-------------------------------------------------------
			CreateFileList( SrcDir, pSrcDirName );
			printf( "Find : %d\n", m_FileCount );

			Bin.FileCount = m_FileCount;
			Address += sizeof(FILEPACK_DATA) * Bin.FileCount;

			//-------------------------------------------------------
			// ファイル名のCRCを算出
			//-------------------------------------------------------
			ComputeNameCRC();

			//-------------------------------------------------------
			// ファイルアクセス用アドレス設定
			//-------------------------------------------------------
			for ( unsigned long i = 0; i < m_FileCount; i++ )
			{
				// アドレスのアライメント
				Address = (Address + Aligned) & ~Aligned;
				// アドレス
				m_pFileData[i].Address = Address;
				// アドレス加算
				Address += m_pFileData[i].Size;
			}

			//-------------------------------------------------------
			// 書き込み用ファイルオープン
			//-------------------------------------------------------
			hWrite = FILE_OPEN_WRITE( PackFile );
			if ( hWrite != INVALID_HANDLE_VALUE )
			{
				// ファイルヘッダ書き出し
				FILE_WRITE( hWrite, &Bin, sizeof(FILEPACK_HEADER) );
				// ファイルデータテーブル書き出し
				FILE_WRITE( hWrite, m_pFileData, sizeof(FILEPACK_DATA) * m_FileCount );

				// ファイル書き出し
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
							// ファイル読み込み
							FILE_READ( hRead, pData, Size );
							// ファイルのCRC算出
							m_pFileData[i].DataCrc = GetCRC( (unsigned char *)pData, Size );
							// 該当アドレスまで０で埋める
							while ( FILE_SEEK( hWrite, 0, FILE_CURRENT ) != m_pFileData[i].Address )
							{
								unsigned char Data = 0x00;
								FILE_WRITE( hWrite, &Data, sizeof(unsigned char) );
							}
							// ファイル出力
							FILE_WRITE( hWrite, pData, Size );

							SAFE_FREE( pData );

							printf( "Packing... [0x%08X] [%9d byte] [%s]\n", m_pFileData[i].NameCrc, m_pFileData[i].Size, m_pFileData[i].FileName );
						}

						// ファイル閉じる
						FILE_CLOSE( hRead );
					}
				}

				// ファイル検索にバイナリサーチが使えるようにCRCでファイルリストをソート
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

				// ファイルデータテーブル書き出し直し
				FILE_SEEK( hWrite, sizeof(FILEPACK_HEADER), FILE_BEGIN );
				FILE_WRITE( hWrite, m_pFileData, sizeof(FILEPACK_DATA) * m_FileCount );

				// ファイル閉じる
				FILE_CLOSE( hWrite );
			}

			// ファイル管理用メモリ解放
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
	// ディレクトリ？
	//----------------------------------------------------------------------------------------
	if ( (::GetFileAttributes( pPackFileName ) & FILE_ATTRIBUTE_DIRECTORY) == 0 )
	{
		printf( "UnPacking...... [%s]\n", pPackFileName );

		//---------------------------------------------------------------------------------
		// ファイルオープン
		//---------------------------------------------------------------------------------
		HANDLE hPack = FILE_OPEN_READ( pPackFileName );
		if ( hPack != INVALID_HANDLE_VALUE )
		{
			//---------------------------------------------------------------------------
			// ファイルヘッダ
			//---------------------------------------------------------------------------
			FILE_READ( hPack, Guid, sizeof(char[4]) );
			if ( !strcmp( Guid, "PACK" ) )
			{
				//-------------------------------------------------------------------
				// ファイル数
				//-------------------------------------------------------------------
				FILE_READ( hPack, &FileCount, sizeof(unsigned long) );
				printf( "  File Count [%d]\n", FileCount );

				pFileData = (FILEPACK_DATA*)SAFE_ALLOC( sizeof(FILEPACK_DATA) * FileCount );
				if ( pFileData != NULL )
				{
					CutAfterStr( DirPath, pPackFileName, '.' );

					// ファイルデータテーブル書き出し
					FILE_READ( hPack, pFileData, sizeof(FILEPACK_DATA) * FileCount );

					// ファイル展開
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

							// ファイル書き出し
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

		// ヘッダ取得
		FILE_READ( hRead, &Guid, sizeof(char[4]) );
		if ( !strcmp( Guid, "PACK" ) )
		{
			// ファイル数取得
			FILE_READ( hRead, &FileCount, sizeof(unsigned long) );
			// ファイルデータ取得
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


