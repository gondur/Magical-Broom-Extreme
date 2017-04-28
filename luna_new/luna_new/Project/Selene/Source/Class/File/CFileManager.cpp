

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
	@brief �t�@�C���f�[�^�w�b�_

	�t�@�C�����e�Ɋւ���f�[�^���i�[���Ă���w�b�_
*/
struct FILE_DATA
{
	char FileName[64];			// �t�@�C����
	Uint32 NameCrc;				// �t�@�C����CRC
	Uint32 DataCrc;				// �t�@�C����CRC
	Uint32 Address;				// �t�@�C���J�n�ʒu
	Uint32 Size;				// �t�@�C���T�C�Y
};

/**
	@brief �o�C�i���f�[�^�w�b�_

	�o�C�i���f�[�^�Ɋւ���f�[�^���i�[���Ă���w�b�_
*/
struct BINARY_HEADER
{
	char Guid[4];				///< 'P' 'A' 'C' 'K'
	Uint32 FileCount;			///< �t�@�C����
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
	�w�肵���t�@�C���̓ǂݍ��݂����܂��B<BR>
	LZSS�ň��k����Ă���ꍇ�͉𓀌�̃f�[�^���擾����܂��B

	@param pFile	[in] �t�@�C����
	@param ppData	[out] �J�����f�[�^���i�[���邽�߂̃|�C���^�̃A�h���X
	@param pSize	[out] �J�����t�@�C���̃t�@�C���T�C�Y

	@retval true	����
	@retval false	���s
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::Load( const wchar_t *pFile, void **ppData, Uint32 *pSize )
{
	wchar_t DataPath[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// �v���C�I���e�B���Ƃ̏���
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//----------------------------------------------------
		// �f�B���N�g������ǂݍ���
		//----------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath),L"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pFile );
		// �f�B���N�g������
		if ( CFileManager::LoadFromFile( DataPath, ppData, pSize ) )
		{
			return true;
		}

		//----------------------------------------------------
		// �p�b�N�t�@�C������
		//----------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s", m_CurrentDirectory, pFile );
		if ( CFileManager::LoadFromPack( DataPath, m_FileSearchTbl[i].FilePackName, ppData, pSize ) )
		{
			return true;
		}
	}

	//-----------------------------------------------------------
	// ���ړǂݍ���
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
	�w�肵���t�@�C���̓ǂݍ��݂����܂��B<BR>
	LZSS�ň��k����Ă���ꍇ�͉𓀌�̃f�[�^���擾����܂��B

	@param pFile	[in] �t�@�C����
	@param ppData	[out] �J�����f�[�^���i�[���邽�߂̃|�C���^�̃A�h���X
	@param pSize	[out] �J�����t�@�C���̃t�@�C���T�C�Y

	@retval true	����
	@retval false	���s
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromFile( const wchar_t *pFile, void **ppData, Uint32 *pSize )
{
	//---------------------------------------------------
	// �t�@�C���I�[�v��
	//---------------------------------------------------
	CFileBase File( pFile, FILE_OPEN_TYPE_READ );
	if ( !File.IsOpened() ) return false;

	//---------------------------------------------------
	// �f�[�^�W�J�̈�`�F�b�N
	//---------------------------------------------------
	if ( ppData == NULL ) return true;

	//---------------------------------------------------
	// �t�@�C���T�C�Y�擾
	//---------------------------------------------------
	(*pSize) = File.GetFileSize();

	//---------------------------------------------------
	// �������m��
	//---------------------------------------------------
	(*ppData) = MemGlobalAlloc( (*pSize) );

	//---------------------------------------------------
	// �t�@�C���ǂݍ���
	//---------------------------------------------------
	File.Read( *ppData, *pSize );

	return true;
}


//-----------------------------------------------------------------------------------
/**
	�p�b�N�t�@�C������w��t�@�C����ǂݍ��݂܂��B<BR>
	LZSS�ň��k����Ă���ꍇ�͉𓀌�̃f�[�^���擾����܂��B

	@param pFile	[in] �f�[�^��
	@param pPack	[in] �p�b�N�t�@�C����
	@param ppData	[out] �J�����f�[�^���i�[���邽�߂̃|�C���^�̃A�h���X
	@param pSize	[out] �J�����t�@�C���̃t�@�C���T�C�Y

	@retval true	����
	@retval false	���s
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromPack( const wchar_t *pFile, const wchar_t *pPack, void **ppData, Uint32 *pSize )
{
	Uint32 Address;
	Uint32 Size;
	Uint32 Crc;
	wchar_t FileName[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// �������͑啶���ɂ��R�s�[
	//-----------------------------------------------------------
	CopyToUpper( FileName, pFile );

	//-----------------------------------------------------------
	// �t�@�C���I�[�v��
	//-----------------------------------------------------------
	CFileBase File( pPack, FILE_OPEN_TYPE_READ );
	if ( !File.IsOpened() ) return false;

	try
	{
		//-----------------------------------------------------------
		// �Y���t�@�C������
		//-----------------------------------------------------------
		if ( !GetFileAddress( File, FileName, &Address, &Size, &Crc ) ) throw false;

		//-----------------------------------------------------------
		// �f�[�^�W�J�̈�`�F�b�N
		//-----------------------------------------------------------
		if ( ppData == NULL ) throw true;

		//-----------------------------------------------------------
		// �Y���A�h���X�܂ňړ�
		//-----------------------------------------------------------
		File.SeekStart( Address );

		//-----------------------------------------------------------
		// �T�C�Y�R�s�[
		//-----------------------------------------------------------
		(*pSize) = Size;

		//-----------------------------------------------------------
		// �T�C�Y���̃������m��
		//-----------------------------------------------------------
		(*ppData) = MemGlobalAlloc( (*pSize) );

		//-----------------------------------------------------------
		// �ǂݍ���
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
	���\�[�X����w��t�@�C����ǂݍ��݂܂��B<BR>
	LZSS�ň��k����Ă���ꍇ�͉𓀌�̃f�[�^���擾����܂��B

	@param pFile		[in] �f�[�^��
	@param pResource	[in] ���\�[�X��
	@param ppData		[out] �J�����f�[�^���i�[���邽�߂̃|�C���^�̃A�h���X
	@param pSize		[out] �J�����t�@�C���̃t�@�C���T�C�Y

	@retval true	����
	@retval false	���s
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromResource( const wchar_t *pFile, const wchar_t *pResource, void **ppData, Uint32 *pSize )
{
	HRSRC hFound = NULL;
	HGLOBAL hRes = NULL;

	//--------------------------------------------------------------------
	// ���\�[�X�̌���
	//--------------------------------------------------------------------
	hFound = ::FindResource( ::GetModuleHandle( NULL ), pFile, pResource );
	if ( hFound == NULL )
	{
		// RCDATA���\�[�X�̌���
		hFound = ::FindResource( ::GetModuleHandle( NULL ), pFile, RT_RCDATA );
		if ( hFound == NULL )
		{
			return false;
		}
	}

	//--------------------------------------------------------------------
	// ���\�[�X���Ƀt�@�C�������݂��Ă���ꍇ
	//--------------------------------------------------------------------
	hRes = ::LoadResource( ::GetModuleHandle( NULL ), hFound );
	if ( hRes == NULL ) return false;

	try
	{
		//----------------------------------------------
		// �W�J��`�F�b�N
		//----------------------------------------------
		if ( ppData == NULL ) throw true;

		//----------------------------------------------
		// �T�C�Y�R�s�[
		//----------------------------------------------
		(*pSize) = ::SizeofResource( ::GetModuleHandle( NULL ), hFound );

		//----------------------------------------------
		// �T�C�Y���̃������m��
		//----------------------------------------------
		(*ppData) = MemGlobalAlloc( (*pSize) );

		//----------------------------------------------
		// �ǂݍ���
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
	�w��t�@�C���̃t�@�C���n���h�����擾���܂��B<BR>
	�擾�����t�@�C���n���h���͓ǂݍ��݁E�������݂��ł��܂��B<BR>

	@param pFile	[in] �t�@�C����

	@return			�t�@�C���f�[�^�̃|�C���^
*/
//-----------------------------------------------------------------------------------
IResourceFile *CFileManager::FileOpen( const wchar_t *pFile )
{
	CResourceFile *pFileData = NULL;
	wchar_t DataPath[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// �v���C�I���e�B����
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//---------------------------------------------------
		// �f�B���N�g������ǂݍ���
		//---------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pFile );
		// �f�B���N�g������
		pFileData = CFileManager::FileOpenFromFile( DataPath );
		if ( pFileData != NULL ) return pFileData;

		//---------------------------------------------------
		// �p�b�N�t�@�C������
		//---------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s", m_CurrentDirectory, pFile );
		pFileData = CFileManager::FileOpenFromPack( DataPath, m_FileSearchTbl[i].FilePackName );
		if ( pFileData != NULL ) return pFileData;
	}

	//---------------------------------------------------
	// ���ړǂݍ���
	//---------------------------------------------------
	pFileData = CFileManager::FileOpenFromFile( pFile );
	if ( pFileData != NULL ) return pFileData;

	return NULL;
}


//-----------------------------------------------------------------------------------
/**
	�w��t�@�C���̃t�@�C���n���h�����擾���܂��B<BR>

	@param pFile	[in] �t�@�C����

	@return			�t�@�C���f�[�^�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CResourceFile *CFileManager::FileOpenFromFile( const wchar_t *pFile )
{
	CResourceFile *pFD = NULL;

	//--------------------------------------------------------
	// �t�@�C���I�[�v��
	//--------------------------------------------------------
	pFD = new CResourceFile( pFile );
	if ( !pFD->IsOpened() )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	//--------------------------------------------------------
	// �t�@�C���T�C�Y�擾
	//--------------------------------------------------------
	pFD->SetSize( pFD->GetFileSize() );

	return pFD;
}

//-----------------------------------------------------------------------------------
/**
	�p�b�N�t�@�C�����̂��ăt�@�C���̃t�@�C���n���h�����擾���܂��B<BR>

	@param pFile	[in] �t�@�C����
	@param pPack	[in] �p�b�N�t�@�C����
	@param IsReadOnly	[in] �ǂݍ��ݐ�p�ŊJ���ꍇ��true

	@return			�t�@�C���f�[�^�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CResourceFile *CFileManager::FileOpenFromPack( const wchar_t *pFile, const wchar_t *pPack )
{
	CResourceFile *pFD = NULL;
	wchar_t FileName[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// �������͑啶���ɂ��R�s�[
	//-----------------------------------------------------------
	CopyToUpper( FileName, pFile );

	//-----------------------------------------------------------
	// �t�@�C���I�[�v��
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
	// �w�b�_�ǂݍ���
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
	// �擪�ʒu�ɃV�[�N
	//-----------------------------------------------------------
	pFD->SeekStart( 0 );

	return pFD;
}


//-----------------------------------------------------------------------------------
/**
	�t�@�C����CRC32���擾���܂��B

	@param Data		[in] �Z�o����f�[�^�̔z��
	@param Size		[in] �f�[�^�T�C�Y

	@return		�Z�o���ꂽCRC
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
	�p�b�N�t�@�C�����̃f�[�^�̃A�h���X���擾���܂�

	@param hFile	[in] �p�b�N�t�@�C���̃t�@�C���n���h��
	@param pFile	[in] �f�[�^��
	@param pAddress	[out] �f�[�^�A�h���X�i�[��
	@param pSize	[out] �f�[�^�T�C�Y�i�[��
	@param pCrc		[out] �f�[�^CRC�i�[��

	@retval true	�f�[�^�����݂���
	@retval false	�f�[�^�����݂��Ȃ�
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
	// �t�@�C�����ϊ�
	//------------------------------------------------------
	WCStoMBCS( pFile, FileName );

	//------------------------------------------------------
	// �t�@�C���w�b�_�`�F�b�N
	//------------------------------------------------------
	File.Read( &BinHead, sizeof(BINARY_HEADER) );

	try
	{
		//----------------------------------------------
		// �w�b�_�`�F�b�N
		//----------------------------------------------
		if ( BinHead.Guid[0] != 'P' ) throw false;
		if ( BinHead.Guid[1] != 'A' ) throw false;
		if ( BinHead.Guid[2] != 'C' ) throw false;
		if ( BinHead.Guid[3] != 'K' ) throw false;

		//----------------------------------------------
		// �t�@�C���f�[�^�e�[�u���擾
		//----------------------------------------------
		pFileData = (FILE_DATA*)MemGlobalAlloc( sizeof(FILE_DATA) * BinHead.FileCount );
		if ( pFileData == NULL ) throw false;

		for ( Sint32 i = 0; i < (Sint32)BinHead.FileCount; i++ )
		{
			File.Read( &pFileData[i], sizeof(FILE_DATA) );
		}

		//----------------------------------------------
		// �t�@�C������CRC���擾
		//----------------------------------------------
		Crc = GetCRC( (unsigned char*)FileName, (Sint32)strlen(FileName) );

		//----------------------------------------------
		// �t�@�C������
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
	�t�@�C���̑��݃`�F�b�N�����܂�

	@param Type		[in] �f�B���N�g���^�C�v
	@param pFile	[in] �t�@�C����

	@retval true	���݂���
	@retval false	���݂��Ȃ�
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::IsFileExistInPack( const wchar_t *pFile )
{
	wchar_t DataFile[MAX_PATH] = L"";
	wchar_t FileName[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// �f�[�^�t�@�C�����𐶐����Ă݂�
	//-----------------------------------------------------------
	::StringCbPrintf( DataFile, sizeof(DataFile), L"%s%s", m_CurrentDirectory, pFile );

	//-----------------------------------------------------------
	// �������͑啶���ɂ��R�s�[
	//-----------------------------------------------------------
//*	CChara::CopyUpper( (unsigned char *)FileName, (unsigned char *)DataFile );

	//-----------------------------------------------------------
	// �v���C�I���e�B���Ƃ̏���
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//------------------------------------------------
		// �`�F�b�N
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
	�Ǎ���̃J�����g�f�B���N�g����ݒ肵�܂�

	@param pCurrentDir	[in] �f�B���N�g����
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
	�Ǎ���̃��[�g�f�B���N�g����ݒ肵�܂�

	@param pRootPath	[in] �f�B���N�g����
	@param pPackFile	[in] �p�b�N�t�@�C����
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
	�Ǎ���̃f�[�^�f�B���N�g�����擾���܂�

	@param Type			[in] �f�B���N�g���^�C�v
	@param pFilePath	[in] �Ǎ���t�@�C����
	@param pSrcFile		[in] �t�@�C����
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::GetFilePath( wchar_t *pFilePath, Uint32 FilePathSize, const wchar_t *pSrcFile )
{
	wchar_t DataPath[MAX_PATH] = L"";

	//-----------------------------------------------------------
	// �v���C�I���e�B���Ƃ̏���
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//------------------------------------------------
		// �f�B���N�g������ǂݍ���
		//------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pSrcFile );
		// �f�B���N�g������
		if ( CFileManager::LoadFromFile( DataPath, NULL, NULL ) )
		{
			::StringCbCopy( pFilePath, FilePathSize, DataPath );
			return true;
		}

		//------------------------------------------------
		// �p�b�N�t�@�C������
		//------------------------------------------------
		::StringCbPrintf( DataPath, sizeof(DataPath), L"%s%s", m_CurrentDirectory, pSrcFile );
		if ( CFileManager::LoadFromPack( DataPath, m_FileSearchTbl[i].FilePackName, NULL, NULL ) )
		{
			::StringCbCopy( pFilePath, FilePathSize, DataPath );
			return true;
		}
	}

	//-----------------------------------------------------------
	// ���ړǂݍ���
	//-----------------------------------------------------------
	::StringCbPrintf( DataPath, sizeof(DataPath), L"%s", pSrcFile );
	if ( CFileManager::LoadFromFile( DataPath, NULL, NULL ) )
	{
		::StringCbCopy( pFilePath, FilePathSize, DataPath );
		return true;
	}

	return false;
}


