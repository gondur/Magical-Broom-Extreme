

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "File/CFileManager.h"
#include "File/CResourceFile.h"

#include "Local.h"
#include "System.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// STRUCT
//-----------------------------------------------------------------------------------

/**
	@brief ファイルデータヘッダ

	ファイル内容に関するデータを格納しているヘッダ
*/
struct FILE_DATA
{
	char FileName[64];			// ファイル名
	Uint32 NameCrc;				// ファイルのCRC
	Uint32 DataCrc;				// ファイルのCRC
	Uint32 Address;				// ファイル開始位置
	Uint32 Size;				// ファイルサイズ
};

/**
	@brief バイナリデータヘッダ

	バイナリデータに関するデータを格納しているヘッダ
*/
struct BINARY_HEADER
{
	char Guid[4];				///< 'P' 'A' 'C' 'K'
	Uint32 FileCount;			///< ファイル数
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFileManager::CFileManager()
{
	::StringCbCopy( m_CurrentDirectory, sizeof(m_CurrentDirectory), L".\\" );
	MemoryClear( m_FileSearchTbl, sizeof(m_FileSearchTbl) );
}

//-----------------------------------------------------------------------------------
/**
	指定したファイルの読み込みをします。<BR>
	LZSSで圧縮されている場合は解凍後のデータが取得されます。

	@param pFile	[in] ファイル名
	@param ppData	[out] 開いたデータを格納するためのポインタのアドレス
	@param pSize	[out] 開いたファイルのファイルサイズ

	@retval true	成功
	@retval false	失敗
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::Load( const wchar_t *pFile, void **ppData, Uint32 *pSize )
{
	wchar_t DataPath[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// プライオリティごとの処理
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//----------------------------------------------------
		// ディレクトリから読み込み
		//----------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath),L"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pFile );
		// ディレクトリから
		if ( CFileManager::LoadFromFile( DataPath, ppData, pSize ) )
		{
			return true;
		}

		//----------------------------------------------------
		// パックファイルから
		//----------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s", m_CurrentDirectory, pFile );
		if ( CFileManager::LoadFromPack( DataPath, m_FileSearchTbl[i].FilePackName, ppData, pSize ) )
		{
			return true;
		}
	}

	//-----------------------------------------------------------
	// 直接読み込み
	//-----------------------------------------------------------
	if ( CFileManager::LoadFromFile( pFile, ppData, pSize ) )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFileManager::Free( void *pData )
{
	MemGlobalFree( pData );
}

//-----------------------------------------------------------------------------------
/**
	指定したファイルの読み込みをします。<BR>
	LZSSで圧縮されている場合は解凍後のデータが取得されます。

	@param pFile	[in] ファイル名
	@param ppData	[out] 開いたデータを格納するためのポインタのアドレス
	@param pSize	[out] 開いたファイルのファイルサイズ

	@retval true	成功
	@retval false	失敗
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromFile( const wchar_t *pFile, void **ppData, Uint32 *pSize )
{
	//---------------------------------------------------
	// ファイルオープン
	//---------------------------------------------------
	CFileBase File( pFile, FILE_OPEN_TYPE_READ );
	if ( !File.IsOpened() ) return false;

	//---------------------------------------------------
	// データ展開領域チェック
	//---------------------------------------------------
	if ( ppData == NULL ) return true;

	//---------------------------------------------------
	// ファイルサイズ取得
	//---------------------------------------------------
	(*pSize) = File.GetFileSize();

	//---------------------------------------------------
	// メモリ確保
	//---------------------------------------------------
	(*ppData) = MemGlobalAlloc( (*pSize) );

	//---------------------------------------------------
	// ファイル読み込み
	//---------------------------------------------------
	File.Read( *ppData, *pSize );

	return true;
}


//-----------------------------------------------------------------------------------
/**
	パックファイルから指定ファイルを読み込みます。<BR>
	LZSSで圧縮されている場合は解凍後のデータが取得されます。

	@param pFile	[in] データ名
	@param pPack	[in] パックファイル名
	@param ppData	[out] 開いたデータを格納するためのポインタのアドレス
	@param pSize	[out] 開いたファイルのファイルサイズ

	@retval true	成功
	@retval false	失敗
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromPack( const wchar_t *pFile, const wchar_t *pPack, void **ppData, Uint32 *pSize )
{
	Uint32 Address;
	Uint32 Size;
	Uint32 Crc;
	wchar_t FileName[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// 小文字は大文字にしつつコピー
	//-----------------------------------------------------------
	CopyToUpper( FileName, pFile );

	//-----------------------------------------------------------
	// ファイルオープン
	//-----------------------------------------------------------
	CFileBase File( pPack, FILE_OPEN_TYPE_READ );
	if ( !File.IsOpened() ) return false;

	try
	{
		//-----------------------------------------------------------
		// 該当ファイル検索
		//-----------------------------------------------------------
		if ( !GetFileAddress( File, FileName, &Address, &Size, &Crc ) ) throw false;

		//-----------------------------------------------------------
		// データ展開領域チェック
		//-----------------------------------------------------------
		if ( ppData == NULL ) throw true;

		//-----------------------------------------------------------
		// 該当アドレスまで移動
		//-----------------------------------------------------------
		File.SeekStart( Address );

		//-----------------------------------------------------------
		// サイズコピー
		//-----------------------------------------------------------
		(*pSize) = Size;

		//-----------------------------------------------------------
		// サイズ分のメモリ確保
		//-----------------------------------------------------------
		(*ppData) = MemGlobalAlloc( (*pSize) );

		//-----------------------------------------------------------
		// 読み込み
		//-----------------------------------------------------------
		File.Read( *ppData, *pSize );

		throw true;
	}
	catch ( Bool bRet )
	{
		return bRet;
	}
}


//-----------------------------------------------------------------------------------
/**
	リソースから指定ファイルを読み込みます。<BR>
	LZSSで圧縮されている場合は解凍後のデータが取得されます。

	@param pFile		[in] データ名
	@param pResource	[in] リソース名
	@param ppData		[out] 開いたデータを格納するためのポインタのアドレス
	@param pSize		[out] 開いたファイルのファイルサイズ

	@retval true	成功
	@retval false	失敗
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromResource( const wchar_t *pFile, const wchar_t *pResource, void **ppData, Uint32 *pSize )
{
	HRSRC hFound = NULL;
	HGLOBAL hRes = NULL;

	//--------------------------------------------------------------------
	// リソースの検索
	//--------------------------------------------------------------------
	hFound = ::FindResource( ::GetModuleHandle( NULL ), pFile, pResource );
	if ( hFound == NULL )
	{
		// RCDATAリソースの検索
		hFound = ::FindResource( ::GetModuleHandle( NULL ), pFile, RT_RCDATA );
		if ( hFound == NULL )
		{
			return false;
		}
	}

	//--------------------------------------------------------------------
	// リソース内にファイルが存在している場合
	//--------------------------------------------------------------------
	hRes = ::LoadResource( ::GetModuleHandle( NULL ), hFound );
	if ( hRes == NULL ) return false;

	try
	{
		//----------------------------------------------
		// 展開先チェック
		//----------------------------------------------
		if ( ppData == NULL ) throw true;

		//----------------------------------------------
		// サイズコピー
		//----------------------------------------------
		(*pSize) = ::SizeofResource( ::GetModuleHandle( NULL ), hFound );

		//----------------------------------------------
		// サイズ分のメモリ確保
		//----------------------------------------------
		(*ppData) = MemGlobalAlloc( (*pSize) );

		//----------------------------------------------
		// 読み込み
		//----------------------------------------------
		MemoryCopy( (*ppData), ::LockResource( hRes ), (*pSize) );

		throw true;
	}
	catch ( Bool bRet )
	{
		::FreeResource( hRes );

		return bRet;
	}
}

//-----------------------------------------------------------------------------------
/**
	指定ファイルのファイルハンドルを取得します。<BR>
	取得したファイルハンドルは読み込み・書き込みができます。<BR>

	@param pFile	[in] ファイル名

	@return			ファイルデータのポインタ
*/
//-----------------------------------------------------------------------------------
IResourceFile *CFileManager::FileOpen( const wchar_t *pFile )
{
	CResourceFile *pFileData = NULL;
	wchar_t DataPath[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// プライオリティごと
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//---------------------------------------------------
		// ディレクトリから読み込み
		//---------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pFile );
		// ディレクトリから
		pFileData = CFileManager::FileOpenFromFile( DataPath );
		if ( pFileData != NULL ) return pFileData;

		//---------------------------------------------------
		// パックファイルから
		//---------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s", m_CurrentDirectory, pFile );
		pFileData = CFileManager::FileOpenFromPack( DataPath, m_FileSearchTbl[i].FilePackName );
		if ( pFileData != NULL ) return pFileData;
	}

	//---------------------------------------------------
	// 直接読み込み
	//---------------------------------------------------
	pFileData = CFileManager::FileOpenFromFile( pFile );
	if ( pFileData != NULL ) return pFileData;

	return NULL;
}


//-----------------------------------------------------------------------------------
/**
	指定ファイルのファイルハンドルを取得します。<BR>

	@param pFile	[in] ファイル名

	@return			ファイルデータのポインタ
*/
//-----------------------------------------------------------------------------------
CResourceFile *CFileManager::FileOpenFromFile( const wchar_t *pFile )
{
	CResourceFile *pFD = NULL;

	//--------------------------------------------------------
	// ファイルオープン
	//--------------------------------------------------------
	pFD = new CResourceFile( pFile );
	if ( !pFD->IsOpened() )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	//--------------------------------------------------------
	// ファイルサイズ取得
	//--------------------------------------------------------
	pFD->SetSize( pFD->GetFileSize() );

	return pFD;
}

//-----------------------------------------------------------------------------------
/**
	パックファイル内のしてファイルのファイルハンドルを取得します。<BR>

	@param pFile	[in] ファイル名
	@param pPack	[in] パックファイル名
	@param IsReadOnly	[in] 読み込み専用で開く場合はtrue

	@return			ファイルデータのポインタ
*/
//-----------------------------------------------------------------------------------
CResourceFile *CFileManager::FileOpenFromPack( const wchar_t *pFile, const wchar_t *pPack )
{
	CResourceFile *pFD = NULL;
	wchar_t FileName[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// 小文字は大文字にしつつコピー
	//-----------------------------------------------------------
	CopyToUpper( FileName, pFile );

	//-----------------------------------------------------------
	// ファイルオープン
	//-----------------------------------------------------------
	pFD = new CResourceFile( pPack );
	if ( !pFD->IsOpened() )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	CFileBase File( pPack, FILE_OPEN_TYPE_READ );
	if ( !File.IsOpened() )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	//-----------------------------------------------------------
	// ヘッダ読み込み
	//-----------------------------------------------------------
	Uint32 Start, Size;
	if ( !GetFileAddress( File, FileName, &Start, &Size, NULL ) )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	pFD->SetStart( Start );
	pFD->SetSize( Size );

	//-----------------------------------------------------------
	// 先頭位置にシーク
	//-----------------------------------------------------------
	pFD->SeekStart( 0 );

	return pFD;
}


//-----------------------------------------------------------------------------------
/**
	ファイルのCRC32を取得します。

	@param Data		[in] 算出するデータの配列
	@param Size		[in] データサイズ

	@return		算出されたCRC
*/
//-----------------------------------------------------------------------------------
Uint32 CFileManager::GetCRC( Uint8 Data[], Sint32 Size )
{
	Uint32 r = 0xFFFFFFFF;

	for ( Sint32 i = 0; i < Size; i++ )
	{
		r ^= (Uint32)Data[i];
		for ( Sint32 j = 0; j < 8; j++ )
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

//-----------------------------------------------------------------------------------
/**
	パックファイル内のデータのアドレスを取得します

	@param hFile	[in] パックファイルのファイルハンドル
	@param pFile	[in] データ名
	@param pAddress	[out] データアドレス格納先
	@param pSize	[out] データサイズ格納先
	@param pCrc		[out] データCRC格納先

	@retval true	データが存在する
	@retval false	データが存在しない
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::GetFileAddress( CFileBase &File, const wchar_t *pFile, Uint32 *pAddress, Uint32 *pSize, Uint32 *pCrc )
{
	FILE_DATA *pFileData = NULL;
	BINARY_HEADER BinHead;
	Uint32 Crc;
	char FileName[MAX_PATH] = "";

	File.SeekStart( 0 );

	//------------------------------------------------------
	// ファイル名変換
	//------------------------------------------------------
	WCStoMBCS( pFile, FileName );

	//------------------------------------------------------
	// ファイルヘッダチェック
	//------------------------------------------------------
	File.Read( &BinHead, sizeof(BINARY_HEADER) );

	try
	{
		//----------------------------------------------
		// ヘッダチェック
		//----------------------------------------------
		if ( BinHead.Guid[0] != 'P' ) throw false;
		if ( BinHead.Guid[1] != 'A' ) throw false;
		if ( BinHead.Guid[2] != 'C' ) throw false;
		if ( BinHead.Guid[3] != 'K' ) throw false;

		//----------------------------------------------
		// ファイルデータテーブル取得
		//----------------------------------------------
		pFileData = (FILE_DATA*)MemGlobalAlloc( sizeof(FILE_DATA) * BinHead.FileCount );
		if ( pFileData == NULL ) throw false;

		for ( Sint32 i = 0; i < (Sint32)BinHead.FileCount; i++ )
		{
			File.Read( &pFileData[i], sizeof(FILE_DATA) );
		}

		//----------------------------------------------
		// ファイル名のCRCを取得
		//----------------------------------------------
		Crc = GetCRC( (unsigned char*)FileName, (Sint32)strlen(FileName) );

		//----------------------------------------------
		// ファイル検索
		//----------------------------------------------
		for ( Sint32 i = 0; i < (Sint32)BinHead.FileCount; i++ )
		{
			if ( Crc == pFileData[i].NameCrc )
			{
				if ( pAddress != NULL ) *pAddress = pFileData[i].Address;
				if ( pSize    != NULL ) *pSize    = pFileData[i].Size;
				if ( pCrc     != NULL ) *pCrc     = pFileData[i].DataCrc;

				throw true;
			}
		}

		throw false;
	}
	catch ( Bool bRet )
	{
		MemGlobalFree( pFileData );
		File.SeekStart( 0 );
	
		return bRet;
	}
}

//-----------------------------------------------------------------------------------
/**
	ファイルの存在チェックをします

	@param Type		[in] ディレクトリタイプ
	@param pFile	[in] ファイル名

	@retval true	存在する
	@retval false	存在しない
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::IsFileExistInPack( const wchar_t *pFile )
{
	wchar_t DataFile[MAX_PATH] = L"";
	wchar_t FileName[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// データファイル名を生成してみる
	//-----------------------------------------------------------
	::StringCbPrintf( DataFile, sizeof(DataFile), L"%s%s", m_CurrentDirectory, pFile );

	//-----------------------------------------------------------
	// 小文字は大文字にしつつコピー
	//-----------------------------------------------------------
//*	CChara::CopyUpper( (unsigned char *)FileName, (unsigned char *)DataFile );

	//-----------------------------------------------------------
	// プライオリティごとの処理
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//------------------------------------------------
		// チェック
		//------------------------------------------------
		CFileBase File( m_FileSearchTbl[i].FilePackName, FILE_OPEN_TYPE_READ );
		if ( File.IsOpened() )
		{
			if ( GetFileAddress( File, FileName, NULL, NULL, NULL ) )
			{
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	読込先のカレントディレクトリを設定します

	@param pCurrentDir	[in] ディレクトリ名
*/
//-----------------------------------------------------------------------------------
void CFileManager::SetCurrentDirectory( wchar_t *pCurrentDir )
{
	MemoryClear( m_CurrentDirectory, sizeof(m_CurrentDirectory) );
	if ( pCurrentDir != NULL )
	{
		::StringCbCopy( m_CurrentDirectory, sizeof(m_CurrentDirectory), pCurrentDir );
		Sint32 Len = (Sint32)wcslen( m_CurrentDirectory );
		if ( Len > 0 )
		{
			if ( m_CurrentDirectory[Len-1] != L'\\' )
			{
				m_CurrentDirectory[Len] = L'\\';
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	読込先のルートディレクトリを設定します

	@param pRootPath	[in] ディレクトリ名
	@param pPackFile	[in] パックファイル名
*/
//-----------------------------------------------------------------------------------
void CFileManager::SetLoadPath( Uint32 Priority, const wchar_t *pRootPath, const wchar_t *pPackFile )
{
	MemoryClear( m_FileSearchTbl[Priority].FileRootPath, sizeof(m_FileSearchTbl[Priority].FileRootPath) );
	::StringCbCopy( m_FileSearchTbl[Priority].FileRootPath, sizeof(m_FileSearchTbl[Priority].FileRootPath), pRootPath );

	Sint32 Len = (Sint32)wcslen( m_FileSearchTbl[Priority].FileRootPath );
	if ( Len > 0 )
	{
		if ( m_FileSearchTbl[Priority].FileRootPath[Len-1] != L'\\' )
		{
			m_FileSearchTbl[Priority].FileRootPath[Len] = L'\\';
		}
	}

	MemoryClear( m_FileSearchTbl[Priority].FilePackName, sizeof(m_FileSearchTbl[Priority].FilePackName) );
	::StringCbCopy( m_FileSearchTbl[Priority].FilePackName, sizeof(m_FileSearchTbl[Priority].FilePackName), pPackFile );
}

//-----------------------------------------------------------------------------------
/**
	読込先のデータディレクトリを取得します

	@param Type			[in] ディレクトリタイプ
	@param pFilePath	[in] 読込先ファイル名
	@param pSrcFile		[in] ファイル名
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::GetFilePath( wchar_t *pFilePath, Uint32 FilePathSize, const wchar_t *pSrcFile )
{
	wchar_t DataPath[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// プライオリティごとの処理
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//------------------------------------------------
		// ディレクトリから読み込み
		//------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pSrcFile );
		// ディレクトリから
		if ( CFileManager::LoadFromFile( DataPath, NULL, NULL ) )
		{
			::StringCbCopy( pFilePath, FilePathSize, DataPath );
			return true;
		}

		//------------------------------------------------
		// パックファイルから
		//------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s", m_CurrentDirectory, pSrcFile );
		if ( CFileManager::LoadFromPack( DataPath, m_FileSearchTbl[i].FilePackName, NULL, NULL ) )
		{
			::StringCbCopy( pFilePath, FilePathSize, DataPath );
			return true;
		}
	}

	//-----------------------------------------------------------
	// 直接読み込み
	//-----------------------------------------------------------
	::StringCbPrintf( DataPath, sizeof(DataPath), L"%s", pSrcFile );
	if ( CFileManager::LoadFromFile( DataPath, NULL, NULL ) )
	{
		::StringCbCopy( pFilePath, FilePathSize, DataPath );
		return true;
	}

	return false;
}


