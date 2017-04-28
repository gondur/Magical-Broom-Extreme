

#ifndef ___SELENE__CRESOURCEFILE___
#define ___SELENE__CRESOURCEFILE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/File/CFileBase.h"
#include "Interface/File/IResourceFile.h"


namespace Selene
{
	/**
		@brief ファイル操作
		@author 葉迩倭
	*/
	class CResourceFile : public CFileBase, public IResourceFile
	{
	private:
		Bool m_IsPack;						///< パックファイルか否か
		Uint32 m_Start;						///< ファイル開始位置
		Uint32 m_Size;						///< ファイル終了位置
		wchar_t m_FileName[MAX_PATH];		///< ファイル名

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CResourceFile( const wchar_t *pFileName );
		virtual ~CResourceFile();

		virtual Uint32 Write( const void *pData, Uint32 Size );
		virtual Uint32 Read( void *pData, Uint32 Size );

		virtual void SetStart( Uint32 Pos ) { m_Start = Pos; }
		virtual void SetSize( Uint32 Size ) { m_Size = Size; }
		virtual const wchar_t *GetNamePointer( void ) { return m_FileName; }
		
		virtual Uint32 GetFileStart( void );
		virtual Uint32 GetFileSize( void );
		virtual Uint32 GetFilePosition( void );
		virtual Uint32 SeekStart( Sint32 Offset );
		virtual Uint32 SeekEnd( Sint32 Offset );
		virtual Uint32 Seek( Sint32 Offset );
	};
}

#endif // ___SELENE__CRESOURCEFILE___

