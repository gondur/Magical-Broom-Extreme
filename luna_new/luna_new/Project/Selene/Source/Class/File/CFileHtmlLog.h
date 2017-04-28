

#ifndef ___SELENE__FILEHTMLLOG___
#define ___SELENE__FILEHTMLLOG___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "File/CFileBase.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief HTML形式ログ操作作成クラス
		@author 葉迩倭
	*/
	class CFileHtmlLog : public CFileBase
	{
	public:
		CFileHtmlLog( const wchar_t *pFileName, const wchar_t *pTitle );
		virtual ~CFileHtmlLog();

		virtual Uint32 Print( Uint32 Color, const wchar_t *pStr,... );
		virtual Uint32 PrintStrong( Uint32 Color, const wchar_t *pStr,... );
		virtual Uint32 PrintLine( Uint32 Color, const wchar_t *pStr,... );
		virtual Uint32 PrintStrongLine( Uint32 Color, const wchar_t *pStr,... );

		virtual Uint32 TableBegin( void );
		virtual Uint32 TableEnd( void );
		virtual Uint32 TableLine( Uint32 Bold );

		virtual Uint32 CellBegin( Uint32 Width );
		virtual Uint32 CellEnd( void );
	};
}

#endif // ___SELENE__FILEHTMLLOG___

