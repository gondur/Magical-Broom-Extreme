

#ifndef ___SELENE__FILEBASE___
#define ___SELENE__FILEBASE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief ファイルオープンモード
		@author 葉迩倭
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< 書き込み専用
		FILE_OPEN_TYPE_READ,			///< 読み込み専用
		FILE_OPEN_TYPE_READ_WRITE,		///< 読み書き用

		FILE_OPEN_TYPE_INVALID,			///< 無効
	};

	/**
		@brief ファイル操作
		@author 葉迩倭
	*/
	class CFileBase : public CBaseObject
	{
	private:
		HANDLE m_hFile;				///< ファイルハンドル
		eFileOpenType m_Type;		///< ファイルオープンモード
		FILETIME m_TimeCreate;		///< ファイル作成時間
		FILETIME m_TimeAccess;		///< ファイルアクセス時間
		FILETIME m_TimeLastWrite;	///< ファイル書き込み時間

	public:
		CFileBase( const wchar_t *pFileName, eFileOpenType Type );
		virtual ~CFileBase();

		virtual Bool IsOpened( void );

		virtual Uint32 Write( const void *pData, Uint32 Size );
		virtual Uint32 Read( void *pData, Uint32 Size );

		virtual Uint32 GetFileSize( void );
		virtual Uint32 GetFilePosition( void );
		virtual Uint32 SeekStart( Sint32 Offset );
		virtual Uint32 SeekEnd( Sint32 Offset );
		virtual Uint32 Seek( Sint32 Offset );
	};
}

#endif // ___SELENE__FILEBASE___

