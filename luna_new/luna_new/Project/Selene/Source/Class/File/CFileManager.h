

#ifndef ___SELENE__FILEMANAGER___
#define ___SELENE__FILEMANAGER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"
#include "Interface/File/IFileManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CFileBase;
	class CResourceFile;
	class CCore;

	#define FILE_SEARCH_MAX		(16)		///< �t�@�C�������e�[�u���T�C�Y

	/**
		@brief �t�@�C�������e�[�u��
		@author �t���`
	*/
	struct SFileSearchTable
	{
		wchar_t FileRootPath[MAX_PATH];		///< ���[�g�f�B���N�g��
		wchar_t FilePackName[MAX_PATH];		///< �p�b�N�t�@�C����
	};

	/**
		@brief �t�@�C���Ǘ��N���X
		@author �t���`
	*/
	class CFileManager : public CBaseObject, public IFileManager
	{
		friend CCore;

	protected:
		wchar_t m_CurrentDirectory[MAX_PATH];								///< ���݂̃J�����g�f�B���N�g��
		SFileSearchTable m_FileSearchTbl[FILE_SEARCH_MAX];					///< �t�@�C�������e�[�u��

	protected:
		CFileManager();

		virtual Bool GetFileAddress( CFileBase &File, const wchar_t *pFile, Uint32 *pAddress, Uint32 *pSize, Uint32 *pCrc );
		virtual Uint32 GetCRC( Uint8 Data[], Sint32 Size );
		virtual Bool LoadFromFile( const wchar_t *pFile, void **ppData, Uint32 *pSize );
		virtual Bool LoadFromPack( const wchar_t *pFile, const wchar_t *pPack, void **ppData, Uint32 *pSize );
		virtual Bool LoadFromResource( const wchar_t *pFile, const wchar_t *pResource, void **ppData, Uint32 *pSize );
		virtual CResourceFile *FileOpenFromFile( const wchar_t *pFile );
		virtual CResourceFile *FileOpenFromPack( const wchar_t *pFile, const wchar_t *pPack );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void SetCurrentDirectory( wchar_t *pCurrentDir );
		virtual void SetLoadPath( Uint32 Priority, const wchar_t *pRootPath, const wchar_t *pPackFile );

		virtual Bool GetFilePath( wchar_t *pFilePath, Uint32 FilePathSize, const wchar_t *pSrcFile );

		virtual Bool IsFileExistInPack( const wchar_t *pFile );
		virtual Bool Load( const wchar_t *pFile, void **ppData, Uint32 *pSize );
		virtual void Free( void *pData );
		virtual IResourceFile *FileOpen( const wchar_t *pFile );
	};
}

#endif // ___SELENE__FILEMANAGER___

