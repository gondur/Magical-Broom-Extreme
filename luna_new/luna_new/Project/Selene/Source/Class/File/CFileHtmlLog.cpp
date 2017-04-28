

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "File/CFileHtmlLog.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static const wchar_t g_HtmlHeadStart[] = {
	L"<HTML>\r\n"
	L"<HEAD>\r\n"
	L"<TITLE>%s</TITLE>\r\n"
	L"<META http-equiv=\"Content-Type\" content=\"text/html\">\r\n"
	L"<STYLE type=\"text/css\">\r\n"
	L"<!--\r\n"
	L"BODY{\r\n"
	L"  font-size : 15px;\r\n"
	L"  font-family : \"‚l‚r ƒSƒVƒbƒN\";\r\n"
	L"  font-weight : normal;\r\n"
	L"}\r\n"
	L"TABLE{\r\n"
	L"  font-size : 15px;\r\n"
	L"  font-family : \"‚l‚r ƒSƒVƒbƒN\";\r\n"
	L"  font-weight : normal;\r\n"
	L"}\r\n"
	L"-->\r\n"
	L"</STYLE>\r\n"
	L"</HEAD>\r\n"
	L"<BODY text=\"#000000\" bgcolor=\"#FFFFFF\">\r\n"
};

static const wchar_t g_HtmlHeadEnd[] = {
	L"</BODY>\r\n"
	L"</HTML>\r\n"
};


//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
CFileHtmlLog::CFileHtmlLog( const wchar_t *pFileName, const wchar_t *pTitle ) : CFileBase( pFileName, FILE_OPEN_TYPE_WRITE )
{
	wchar_t Buff[1024] = L"";
	size_t Len;

	::StringCbPrintf( Buff, sizeof(Buff), g_HtmlHeadStart, pTitle );
	Len = wcslen( Buff );

	Uint8 BOM[] = { 0xFF, 0xFE };
	Write( (Uint8*)BOM, sizeof(BOM) );
	Write( (Uint8*)Buff, (Uint32)Len * sizeof(wchar_t) );
}


//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
CFileHtmlLog::~CFileHtmlLog()
{
	Write( (Uint8*)g_HtmlHeadEnd, sizeof(g_HtmlHeadEnd) );
}

//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::Print( Uint32 Color, const wchar_t *pStr,... )
{
	wchar_t Buff[1024] = L"";
	wchar_t InBuff[64] = L"";

	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	wchar_t In[] = L"<FONT COLOR=\"#%06X\">";
	wchar_t Out[] = L"</FONT>";

	::StringCbPrintf( InBuff, sizeof(InBuff), In, Color );

	Uint32 WriteBytes = 0;
	if ( Color != 0x000000 )
	{
		WriteBytes += Write( (Uint8*)InBuff, (Uint32)wcslen(InBuff) * sizeof(wchar_t) );
		WriteBytes += Write( (Uint8*)Buff, (Uint32)wcslen(Buff) * sizeof(wchar_t) );
		WriteBytes += Write( (Uint8*)Out, (Uint32)wcslen(Out) * sizeof(wchar_t) );
	}
	else
	{
		WriteBytes += Write( (Uint8*)Buff, (Uint32)wcslen(Buff) * sizeof(wchar_t) );
	}
	return WriteBytes;
}


//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::PrintStrong( Uint32 Color, const wchar_t *pStr,... )
{
	wchar_t Buff[1024] = L"";
	wchar_t Str[1024] = L"";
	wchar_t InBuff[64] = L"";

	::StringCbPrintf( Str, sizeof(Str), L"<B>%s</B>", pStr );
	::StringCbVPrintf( Buff, sizeof(Buff), Str, (char*)(&pStr + 1) );

	wchar_t In[] = L"<FONT COLOR=\"#%06X\">";
	wchar_t Out[] = L"</FONT>\r\n";

	::StringCbPrintf( InBuff, sizeof(InBuff), In, Color );

	Uint32 WriteBytes = 0;
	if ( Color != 0x000000 )
	{
		WriteBytes += Write( (Uint8*)InBuff, (Uint32)wcslen(InBuff) * sizeof(wchar_t) );
		WriteBytes += Write( (Uint8*)Buff, (Uint32)wcslen(Buff) * sizeof(wchar_t) );
		WriteBytes += Write( (Uint8*)Out, (Uint32)wcslen(Out) * sizeof(wchar_t) );
	}
	else
	{
		WriteBytes += Write( (Uint8*)Buff, (Uint32)wcslen(Buff) * sizeof(wchar_t) );
	}
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::PrintLine( Uint32 Color, const wchar_t *pStr,... )
{
	wchar_t Buff[1024] = L"";

	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Uint32 WriteBytes = 0;
	WriteBytes += Print( Color, Buff );
	WriteBytes += Print( 0x000000, L"<BR>\r\n" );
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::PrintStrongLine( Uint32 Color, const wchar_t *pStr,... )
{
	wchar_t Buff[1024] = L"";

	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Uint32 WriteBytes = 0;
	WriteBytes += PrintStrong( Color, Buff );
	WriteBytes += Print( 0x000000, L"<BR>\r\n" );
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::TableBegin( void )
{
	const wchar_t Table[] = {
		L"<TABLE width=\"100%\">\r\n"
		L"  <TBODY>\r\n"
		L"    <TR>\r\n"
	};

	return Write( (Uint8*)Table, (Uint32)wcslen(Table) * sizeof(wchar_t) );
}

//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::TableEnd( void )
{
	const wchar_t Table[] = {
		L"    </TR>\r\n"
		L"  </TBODY>\r\n"
		L"</TABLE>\r\n"
	};

	return Write( (Uint8*)Table, (Uint32)wcslen(Table) * sizeof(wchar_t) );
}


//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::CellBegin( Uint32 Width )
{
	const wchar_t Table1[] = {
		L"<TD width=\"%d\" valign=\"top\">\r\n"
	};

	const wchar_t Table2[] = {
		L"<TD width=\"%d\" valign=\"top\">\r\n"
	};

	wchar_t Buff[64] = L"";
	::StringCbPrintf( Buff, sizeof(Buff), (Width == 0) ? Table2 : Table1, Width );

	return Write( (Uint8*)Buff, (Uint32)wcslen(Buff) * sizeof(wchar_t) );
}


//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::CellEnd( void )
{
	const wchar_t Table[] = {
		L"</TD>\r\n"
	};

	return Write( (Uint8*)Table, (Uint32)wcslen(Table) * sizeof(wchar_t) );
}

//-----------------------------------------------------------------------------------
/**
	@brief
	@author 
*/
//-----------------------------------------------------------------------------------
Uint32 CFileHtmlLog::TableLine( Uint32 Bold )
{
	const wchar_t Table[] = {
		L"<TABLE width=\"100%%\">\r\n"
		L"  <TR>\r\n"
		L"    <TD height=\"%d\" bgcolor=\"#000000\"></TD>\r\n"
		L"  </TR>\r\n"
		L"</TABLE>\r\n"
	};

	wchar_t Buff[1024] = L"";
	::StringCbPrintf( Buff, sizeof(Buff), Table, Bold );

	size_t Len = wcslen( Buff );
	return Write( (Uint8*)Buff, (Uint32)Len * sizeof(wchar_t) );
}

