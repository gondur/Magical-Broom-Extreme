

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "File/CFileHtmlLog.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static CFileHtmlLog *g_pHtmlLogFile;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::MBCStoWCS( const char *pSrc, wchar_t *pDst )
{
	Sint32 Len = ::MultiByteToWideChar( CP_ACP, 0, pSrc, -1, NULL, 0 );
	::MultiByteToWideChar( CP_ACP, 0, pSrc, -1, pDst, Len );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::WCStoMBCS( const wchar_t *pSrc, char *pDst )
{
	Sint32 Len = ::WideCharToMultiByte( CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL );
	::WideCharToMultiByte( CP_ACP, 0, pSrc, -1, pDst, Len, NULL, NULL );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
wchar_t *Selene::GetSocketError( Sint32 ErrorCode, wchar_t *pErrStr, Uint32 ErrStrSize )
{
	static wchar_t String[256] = L"";

	switch ( ErrorCode )
	{
	case WSABASEERR:				::StringCbCopy( String, sizeof(String), L"エラーは発生していない" );								break;
	case WSAEINTR:					::StringCbCopy( String, sizeof(String), L"関数呼び出しが中断された" );								break;
	case WSAEBADF:					::StringCbCopy( String, sizeof(String), L"無効なファイルハンドル" );								break;
	case WSAEACCES:					::StringCbCopy( String, sizeof(String), L"アクセスが拒否された" );									break;
	case WSAEFAULT:					::StringCbCopy( String, sizeof(String), L"無効なバッファアドレス" );								break;
	case WSAEINVAL:					::StringCbCopy( String, sizeof(String), L"無効な引数が渡された" );									break;
	case WSAEMFILE:					::StringCbCopy( String, sizeof(String), L"使用中のソケットの数が多すぎる" );						break;
	case WSAEWOULDBLOCK:			::StringCbCopy( String, sizeof(String), L"操作はブロッキングされる" );								break;
	case WSAEINPROGRESS:			::StringCbCopy( String, sizeof(String), L"すでにブロッキング手続きが実行されている" );				break;
	case WSAEALREADY:				::StringCbCopy( String, sizeof(String), L"要求された操作は既に実行中、または実行済み" );			break;
	case WSAENOTSOCK:				::StringCbCopy( String, sizeof(String), L"指定されたソケットが無効である" );						break;
	case WSAEDESTADDRREQ:			::StringCbCopy( String, sizeof(String), L"操作の実行に送信先アドレスが必要" );						break;
	case WSAEMSGSIZE:				::StringCbCopy( String, sizeof(String), L"メッセージサイズが大きすぎる" );							break;
	case WSAEPROTOTYPE:				::StringCbCopy( String, sizeof(String), L"ソケットは要求されたプロトコルに適合していない" );		break;
	case WSAENOPROTOOPT:			::StringCbCopy( String, sizeof(String), L"不正なプロトコルオプション" );							break;
	case WSAEPROTONOSUPPORT:		::StringCbCopy( String, sizeof(String), L"プロトコルがサポートされていない" );						break;
	case WSAESOCKTNOSUPPORT:		::StringCbCopy( String, sizeof(String), L"指定されたソケットタイプはサポートされていない" );		break;
	case WSAEOPNOTSUPP:				::StringCbCopy( String, sizeof(String), L"要求された操作はサポートされていない" );					break;
	case WSAEPFNOSUPPORT:			::StringCbCopy( String, sizeof(String), L"プロトコルファミリがサポートされていない" );				break;
	case WSAEAFNOSUPPORT:			::StringCbCopy( String, sizeof(String), L"アドレスファミリがサポートされていない" );				break;
	case WSAEADDRINUSE:				::StringCbCopy( String, sizeof(String), L"アドレスは既に使用中である" );							break;
	case WSAEADDRNOTAVAIL:			::StringCbCopy( String, sizeof(String), L"無効なネットワークアドレス" );							break;
	case WSAENETDOWN:				::StringCbCopy( String, sizeof(String), L"ネットワークがダウンしている" );							break;
	case WSAENETUNREACH:			::StringCbCopy( String, sizeof(String), L"指定されたネットワークホストに到達できない" );			break;
	case WSAENETRESET:				::StringCbCopy( String, sizeof(String), L"ネットワーク接続が破棄された" );							break;
	case WSAECONNABORTED:			::StringCbCopy( String, sizeof(String), L"ネットワーク接続が破棄された" );							break;
	case WSAECONNRESET:				::StringCbCopy( String, sizeof(String), L"ネットワーク接続が相手によって破棄された" );				break;
	case WSAENOBUFS:				::StringCbCopy( String, sizeof(String), L"バッファが不足している" );								break;
	case WSAEISCONN:				::StringCbCopy( String, sizeof(String), L"ソケットは既に接続されている" );							break;
	case WSAENOTCONN:				::StringCbCopy( String, sizeof(String), L"ソケットは接続されていない" );							break;
	case WSAESHUTDOWN:				::StringCbCopy( String, sizeof(String), L"ソケットはシャットダウンされている" );					break;
	case WSAETOOMANYREFS:			::StringCbCopy( String, sizeof(String), L"参照の数が多すぎる" );									break;
	case WSAETIMEDOUT:				::StringCbCopy( String, sizeof(String), L"接続要求がタイムアウトした" );							break;
	case WSAECONNREFUSED:			::StringCbCopy( String, sizeof(String), L"接続が拒否された" );										break;
	case WSAELOOP:					::StringCbCopy( String, sizeof(String), L"ループ" );												break;
	case WSAENAMETOOLONG:			::StringCbCopy( String, sizeof(String), L"名前が長すぎる" );										break;
	case WSAEHOSTDOWN:				::StringCbCopy( String, sizeof(String), L"ホストがダウンしている" );								break;
	case WSAEHOSTUNREACH:			::StringCbCopy( String, sizeof(String), L"ホストへの経路がない" );									break;
	case WSAENOTEMPTY:				::StringCbCopy( String, sizeof(String), L"ディレクトリが空ではない" );								break;
	case WSAEPROCLIM:				::StringCbCopy( String, sizeof(String), L"プロセスの数が多すぎる" );								break;
	case WSAEUSERS:					::StringCbCopy( String, sizeof(String), L"ユーザの数が多すぎる" );									break;
	case WSAEDQUOT:					::StringCbCopy( String, sizeof(String), L"ディスククォータ" );										break;
	case WSAESTALE:					::StringCbCopy( String, sizeof(String), L"実行しようとした操作は廃止されている" );					break;
	case WSAEREMOTE:				::StringCbCopy( String, sizeof(String), L"リモート" );												break;
	case WSASYSNOTREADY:			::StringCbCopy( String, sizeof(String), L"ネットワークサブシステムが利用できない" );				break;
	case WSAVERNOTSUPPORTED:		::StringCbCopy( String, sizeof(String), L"Winsock.dllのバージョンが範囲外である" );					break;
	case WSANOTINITIALISED:			::StringCbCopy( String, sizeof(String), L"WinSockシステムが初期化されていない" );					break;
	case WSAEDISCON:				::StringCbCopy( String, sizeof(String), L"シャットダウン処理中" );									break;
	case WSAENOMORE:				::StringCbCopy( String, sizeof(String), L"データはこれ以上存在しない" );							break;
	case WSAECANCELLED:				::StringCbCopy( String, sizeof(String), L"操作は取り消された" );									break;
	case WSAEINVALIDPROCTABLE:		::StringCbCopy( String, sizeof(String), L"サービスプロバイダの関数テーブルが無効" );				break;
	case WSAEINVALIDPROVIDER:		::StringCbCopy( String, sizeof(String), L"サービスプロバイダが無効" );								break;
	case WSAEPROVIDERFAILEDINIT:	::StringCbCopy( String, sizeof(String), L"サービスプロバイダの初期化に失敗した" );					break;
	case WSASYSCALLFAILURE:			::StringCbCopy( String, sizeof(String), L"システムコールに失敗した" );								break;
	case WSASERVICE_NOT_FOUND:		::StringCbCopy( String, sizeof(String), L"サービスが見つからない" );								break;
	case WSATYPE_NOT_FOUND:			::StringCbCopy( String, sizeof(String), L"タイプが見つからない" );									break;
	case WSA_E_CANCELLED:			::StringCbCopy( String, sizeof(String), L"検索がキャンセルされた" );								break;
	case WSAEREFUSED:				::StringCbCopy( String, sizeof(String), L"操作は拒否された" );										break;
	case WSAHOST_NOT_FOUND:			::StringCbCopy( String, sizeof(String), L"ホストが見つからない" );									break;
	case WSATRY_AGAIN:				::StringCbCopy( String, sizeof(String), L"指定されたホストが見つからない、またはサービスの異常" );	break;
	case WSANO_RECOVERY:			::StringCbCopy( String, sizeof(String), L"回復不能なエラーが発生した" );							break;
	case WSANO_DATA:				::StringCbCopy( String, sizeof(String), L"要求されたタイプのデータレコードが見つからない" );		break;
	}

	if ( pErrStr != NULL ) ::StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
wchar_t *Selene::GetPixelFormat( D3DFORMAT Format, wchar_t *pErrStr, Uint32 ErrStrSize )
{
	static wchar_t String[256] = L"";

	switch ( Format )
	{
	case D3DFMT_UNKNOWN:			::StringCbCopy( String, sizeof(String), L"UNKNOWN" );		break;
	case D3DFMT_R8G8B8:				::StringCbCopy( String, sizeof(String), L"R8G8B8" );		break;
	case D3DFMT_A8R8G8B8:			::StringCbCopy( String, sizeof(String), L"A8R8G8B8" );		break;
	case D3DFMT_X8R8G8B8:			::StringCbCopy( String, sizeof(String), L"X8R8G8B8" );		break;
	case D3DFMT_R5G6B5:				::StringCbCopy( String, sizeof(String), L"R5G6B5" );		break;
	case D3DFMT_X1R5G5B5:			::StringCbCopy( String, sizeof(String), L"X1R5G5B5" );		break;
	case D3DFMT_A1R5G5B5:			::StringCbCopy( String, sizeof(String), L"A1R5G5B5" );		break;
	case D3DFMT_A4R4G4B4:			::StringCbCopy( String, sizeof(String), L"A4R4G4B4" );		break;
	case D3DFMT_R3G3B2:				::StringCbCopy( String, sizeof(String), L"R3G3B2" );		break;
	case D3DFMT_A8:					::StringCbCopy( String, sizeof(String), L"A8" );			break;
	case D3DFMT_A8R3G3B2:			::StringCbCopy( String, sizeof(String), L"A8R3G3B2" );		break;
	case D3DFMT_X4R4G4B4:			::StringCbCopy( String, sizeof(String), L"X4R4G4B4" );		break;
	case D3DFMT_A2B10G10R10:		::StringCbCopy( String, sizeof(String), L"A2B10G10R10" );	break;
	case D3DFMT_A8B8G8R8:			::StringCbCopy( String, sizeof(String), L"A8B8G8R8" );		break;
	case D3DFMT_X8B8G8R8:			::StringCbCopy( String, sizeof(String), L"X8B8G8R8" );		break;
	case D3DFMT_G16R16:				::StringCbCopy( String, sizeof(String), L"G16R16" );		break;
	case D3DFMT_A2R10G10B10:		::StringCbCopy( String, sizeof(String), L"A2R10G10B10" );	break;
	case D3DFMT_A16B16G16R16:		::StringCbCopy( String, sizeof(String), L"A16B16G16R16" );	break;
	case D3DFMT_A8P8:				::StringCbCopy( String, sizeof(String), L"A8P8" );			break;
	case D3DFMT_P8:					::StringCbCopy( String, sizeof(String), L"P8" );			break;
	case D3DFMT_L8:					::StringCbCopy( String, sizeof(String), L"L8" );			break;
	case D3DFMT_L16:				::StringCbCopy( String, sizeof(String), L"L16" );			break;
	case D3DFMT_A8L8:				::StringCbCopy( String, sizeof(String), L"A8L8" );			break;
	case D3DFMT_A4L4:				::StringCbCopy( String, sizeof(String), L"A4L4" );			break;
	case D3DFMT_V8U8:				::StringCbCopy( String, sizeof(String), L"V8U8" );			break;
	case D3DFMT_Q8W8V8U8:			::StringCbCopy( String, sizeof(String), L"Q8W8V8U8" );		break;
	case D3DFMT_V16U16:				::StringCbCopy( String, sizeof(String), L"V16U16" );		break;
	case D3DFMT_Q16W16V16U16:		::StringCbCopy( String, sizeof(String), L"Q16W16V16U16" );	break;
	case D3DFMT_CxV8U8:				::StringCbCopy( String, sizeof(String), L"CxV8U8" );		break;
	case D3DFMT_L6V5U5:				::StringCbCopy( String, sizeof(String), L"L6V5U5" );		break;
	case D3DFMT_X8L8V8U8:			::StringCbCopy( String, sizeof(String), L"X8L8V8U8" );		break;
	case D3DFMT_A2W10V10U10:		::StringCbCopy( String, sizeof(String), L"A2W10V10U10" );	break;
	case D3DFMT_G8R8_G8B8:			::StringCbCopy( String, sizeof(String), L"G8R8_G8B8" );		break;
	case D3DFMT_R8G8_B8G8:			::StringCbCopy( String, sizeof(String), L"R8G8_B8G8" );		break;
	case D3DFMT_DXT1:				::StringCbCopy( String, sizeof(String), L"DXT1" );			break;
	case D3DFMT_DXT2:				::StringCbCopy( String, sizeof(String), L"DXT2" );			break;
	case D3DFMT_DXT3:				::StringCbCopy( String, sizeof(String), L"DXT3" );			break;
	case D3DFMT_DXT4:				::StringCbCopy( String, sizeof(String), L"DXT4" );			break;
	case D3DFMT_DXT5:				::StringCbCopy( String, sizeof(String), L"DXT5" );			break;
	case D3DFMT_UYVY:				::StringCbCopy( String, sizeof(String), L"UYVY" );			break;
	case D3DFMT_YUY2:				::StringCbCopy( String, sizeof(String), L"YUY2" );			break;
	case D3DFMT_D16_LOCKABLE:		::StringCbCopy( String, sizeof(String), L"D16_LOCKABLE" );	break;
	case D3DFMT_D32:				::StringCbCopy( String, sizeof(String), L"D32" );			break;
	case D3DFMT_D15S1:				::StringCbCopy( String, sizeof(String), L"D15S1" );			break;
	case D3DFMT_D24S8:				::StringCbCopy( String, sizeof(String), L"D24S8" );			break;
	case D3DFMT_D24X8:				::StringCbCopy( String, sizeof(String), L"D24X8" );			break;
	case D3DFMT_D24X4S4:			::StringCbCopy( String, sizeof(String), L"D24X4S4" );		break;
	case D3DFMT_D32F_LOCKABLE:		::StringCbCopy( String, sizeof(String), L"D32F_LOCKABLE" );	break;
	case D3DFMT_D24FS8:				::StringCbCopy( String, sizeof(String), L"D24FS8" );		break;
	case D3DFMT_D16:				::StringCbCopy( String, sizeof(String), L"D16" );			break;
	case D3DFMT_VERTEXDATA:			::StringCbCopy( String, sizeof(String), L"VERTEXDATA" );	break;
	case D3DFMT_INDEX16:			::StringCbCopy( String, sizeof(String), L"INDEX16" );		break;
	case D3DFMT_INDEX32:			::StringCbCopy( String, sizeof(String), L"INDEX32" );		break;
	case D3DFMT_R16F:				::StringCbCopy( String, sizeof(String), L"R16F" );			break;
	case D3DFMT_G16R16F:			::StringCbCopy( String, sizeof(String), L"G16R16F" );		break;
	case D3DFMT_A16B16G16R16F:		::StringCbCopy( String, sizeof(String), L"A16B16G16R16F" );	break;
	case D3DFMT_R32F:				::StringCbCopy( String, sizeof(String), L"R32F" );			break;
	case D3DFMT_G32R32F:			::StringCbCopy( String, sizeof(String), L"G32R32F" );		break;
	case D3DFMT_A32B32G32R32F:		::StringCbCopy( String, sizeof(String), L"A32B32G32R32F" );	break;
	}

	if ( pErrStr != NULL ) ::StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
wchar_t *Selene::GetD3DError( HRESULT hr, wchar_t *pErrStr, Uint32 ErrStrSize )
{
	static wchar_t String[128] = L"";

	switch ( hr )
	{
	case D3D_OK:							::StringCbCopy( String, sizeof(String), L"エラーは発生していない。" );																																					break;
	case D3DERR_CONFLICTINGRENDERSTATE:		::StringCbCopy( String, sizeof(String), L"現在設定されているレンダリング ステートは一緒に使用できない。" );																												break;
	case D3DERR_CONFLICTINGTEXTUREFILTER:	::StringCbCopy( String, sizeof(String), L"現在のテクスチャ フィルタは一緒に使用できない。" );																															break;
	case D3DERR_CONFLICTINGTEXTUREPALETTE:	::StringCbCopy( String, sizeof(String), L"現在のテクスチャは同時に使用できない。一般にマルチテクスチャ デバイスにおいて、同時に有効にされたパレット化テクスチャで同じパレットを共有する必要がある場合に発生する。" );	break;
	case D3DERR_DEVICELOST:					::StringCbCopy( String, sizeof(String), L"デバイスが失われていて、現時点では復元できないため、レンダリングは不可能である。" );																							break;
	case D3DERR_DEVICENOTRESET:				::StringCbCopy( String, sizeof(String), L"デバイスはリセットできない。" );																																				break;
	case D3DERR_DRIVERINTERNALERROR:		::StringCbCopy( String, sizeof(String), L"内部ドライバ エラー。" );																																						break;
	case D3DERR_INVALIDCALL:				::StringCbCopy( String, sizeof(String), L"メソッドの呼び出しが無効である。たとえば、メソッドのパラメータに無効な値が設定されている場合など。" );																			break;
	case D3DERR_INVALIDDEVICE:				::StringCbCopy( String, sizeof(String), L"要求されたデバイスの種類が有効でない。" );																																		break;
	case D3DERR_MOREDATA:					::StringCbCopy( String, sizeof(String), L"指定されたバッファ サイズに保持できる以上のデータが存在する。" );																												break;
	case D3DERR_NOTAVAILABLE:				::StringCbCopy( String, sizeof(String), L"このデバイスは、照会されたテクニックをサポートしていない。" );																													break;
	case D3DERR_NOTFOUND:					::StringCbCopy( String, sizeof(String), L"要求された項目が見つからなかった。" );																																			break;
	case D3DERR_OUTOFVIDEOMEMORY:			::StringCbCopy( String, sizeof(String), L"Direct3D が処理を行うのに十分なディスプレイ メモリがない。" );																													break;
	case D3DERR_TOOMANYOPERATIONS:			::StringCbCopy( String, sizeof(String), L"デバイスがサポートしている以上のテクスチャ フィルタリング処理を、アプリケーションが要求している。" );																			break;
	case D3DERR_UNSUPPORTEDALPHAARG:		::StringCbCopy( String, sizeof(String), L"アルファ チャネルに対して指定されているテクスチャ ブレンディング引数を、デバイスがサポートしていない。" );																		break;
	case D3DERR_UNSUPPORTEDALPHAOPERATION:	::StringCbCopy( String, sizeof(String), L"アルファ チャネルに対して指定されているテクスチャ ブレンディング処理を、デバイスがサポートしていない。" );																		break;
	case D3DERR_UNSUPPORTEDCOLORARG:		::StringCbCopy( String, sizeof(String), L"カラー値に対して指定されているテクスチャ ブレンディング引数を、デバイスがサポートしていない。" );																				break;
	case D3DERR_UNSUPPORTEDCOLOROPERATION:	::StringCbCopy( String, sizeof(String), L"カラー値に対して指定されているテクスチャ ブレンディング処理を、デバイスがサポートしていない。" );																				break;
	case D3DERR_UNSUPPORTEDFACTORVALUE:		::StringCbCopy( String, sizeof(String), L"デバイスが指定されたテクスチャ係数値をサポートしていない。" );																													break;
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:	::StringCbCopy( String, sizeof(String), L"デバイスが指定されたテクスチャ フィルタをサポートしていない。" );																												break;
	case D3DERR_WRONGTEXTUREFORMAT:			::StringCbCopy( String, sizeof(String), L"テクスチャ サーフェスのピクセル フォーマットが有効でない。" );																													break;
	case E_FAIL:							::StringCbCopy( String, sizeof(String), L"Direct3D サブシステム内で原因不明のエラーが発生した。" );																														break;
	case E_INVALIDARG:						::StringCbCopy( String, sizeof(String), L"無効なパラメータが戻ってくる関数に渡された。" );																																break;
	case E_OUTOFMEMORY:						::StringCbCopy( String, sizeof(String), L"Direct3D が呼び出しを完了するための十分なメモリを割り当てることができなかった。" );																							break;
	case D3DXERR_CANNOTATTRSORT:			::StringCbCopy( String, sizeof(String), L"最適化テクニックとして属性のソート (::D3DXMESHOPT_ATTRSORT) はサポートされていない。 " );																						break;
	case D3DXERR_CANNOTMODIFYINDEXBUFFER:	::StringCbCopy( String, sizeof(String), L"インデックス バッファを変更できない。 " );																																		break;
	case D3DXERR_INVALIDMESH:				::StringCbCopy( String, sizeof(String), L"メッシュが無効である。 " );																																					break;
	case D3DXERR_SKINNINGNOTSUPPORTED:		::StringCbCopy( String, sizeof(String), L"スキニングはサポートされていない。 " );																																		break;
	case D3DXERR_TOOMANYINFLUENCES:			::StringCbCopy( String, sizeof(String), L"指定された影響が多すぎる。 " );																																				break;
	case D3DXERR_INVALIDDATA:				::StringCbCopy( String, sizeof(String), L"データが無効である。" );																																						break;
	default:								::StringCbCopy( String, sizeof(String), L"未知のエラー。" );																																								break;
	}

	if ( pErrStr != NULL ) ::StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Initialize( const wchar_t *pDir )
{
	wchar_t LogFile[MAX_PATH];
	::StringCbPrintf( LogFile, sizeof(LogFile), L"%sLog.html", pDir );

	wchar_t Version[MAX_PATH];
	GetVersioinInfo( Version, sizeof(Version) );
	g_pHtmlLogFile = new CFileHtmlLog( LogFile, Version );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Finalize( void )
{
	SAFE_DELETE( g_pHtmlLogFile );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Print( Uint32 Color, const wchar_t *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	wchar_t Buff[1024] = L"";
	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->Print( Color, Buff );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintStrong( Uint32 Color, const wchar_t *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	wchar_t Buff[1024] = L"";
	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintStrong( Color, Buff );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintLine( Uint32 Color, const wchar_t *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	wchar_t Buff[1024] = L"";
	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintLine( Color, Buff );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintStrongLine( Uint32 Color, const wchar_t *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	wchar_t Buff[1024] = L"";
	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintStrongLine( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintTable( Uint32 ColorTitle, Uint32 Color, const wchar_t *pTitle, const wchar_t *pKind, const wchar_t *pStr,... )
{
	wchar_t Buff[1024] = L"";
	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1 ) );

	Log_TableBegin();
	Log_PrintCellTitle( ColorTitle, pTitle );
	Log_PrintCellKind( pKind );
	Log_CellBegin( 0 );
	Log_Print( Color, Buff );
	Log_CellEnd();
	Log_TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintTable( Uint32 Width, const wchar_t *pTitle, const wchar_t *pStr,... )
{
	wchar_t Buff[1024] = L"";
	::StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1 ) );

	Log_TableBegin();
	Log_CellBegin( Width );
	Log_PrintLine( 0x000000, pTitle );
	Log_CellEnd();
	Log_CellBegin( 0 );
	Log_PrintLine( 0x000000, Buff );
	Log_CellEnd();
	Log_TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintCellTitle( Uint32 Color, const wchar_t *pTitle )
{
	Log_CellBegin( 64 );
	Log_PrintStrong( Color, pTitle );
	Log_CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintCellKind( const wchar_t *pKind,... )
{
	wchar_t Buff[1024] = L"";
	::StringCbPrintf( Buff, sizeof(Buff), pKind, (wchar_t *)(&pKind+ 1 ) );

	Log_CellBegin( 192 );
	Log_Print( 0x000000, Buff );
	Log_CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableBegin( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableBegin();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableEnd( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableLine( Uint32 Bold )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableLine( Bold );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_CellBegin( Uint32 Width )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->CellBegin( Width );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_CellEnd( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->CellEnd();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::SetWindowCenter( HWND hWnd, HWND hWndParent )
{
    RECT RectParent, Rect;

	::GetWindowRect( hWndParent, &RectParent );
	::GetWindowRect( hWnd, &Rect );

	Sint32 w = Rect.right-Rect.left;
	Sint32 h = Rect.bottom-Rect.top;
    Sint32 x = (RectParent.right - w) / 2;
    Sint32 y = (RectParent.bottom - h) / 2;

	::SetWindowPos( hWnd, HWND_TOP, x, y, w, h, SWP_SHOWWINDOW ); 
}



//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::GetDesktopDirectory( wchar_t *pPath, Uint32 PathSize )
{
	pPath[0] = L'\0';

	ITEMIDLIST *pidl = NULL;
	IMalloc *pMalloc = NULL;
	wchar_t Temp[MAX_PATH] = L"";

	if FAILED( ::SHGetMalloc( &pMalloc ) ) return false;

	::SHGetSpecialFolderLocation( ::GetDesktopWindow(), CSIDL_DESKTOP, &pidl );
	::SHGetPathFromIDList( pidl, Temp );

	pMalloc->Free( pidl );
	SAFE_RELEASE( pMalloc );

	::StringCbCopy( pPath, PathSize, Temp );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::GetLongFullPathName( const wchar_t *pSrcPath, wchar_t *pDstPath, Uint32 DstPathSize )
{
	pDstPath[0] = L'\0';

	Sint32 Len = (Sint32)wcslen( pSrcPath );
	while ( pSrcPath[Len] != L'\\' ) if ( --Len < 0 ) break;
	if ( Len < 0 )
	{
		::StringCbCat( pDstPath, DstPathSize, pSrcPath );
	}
	else
	{
		HANDLE hFind;
		WIN32_FIND_DATA FindData;
		wchar_t LongPath[MAX_PATH] = L"";
		wchar_t Temp[MAX_PATH] = L"";

		// 親ディレクトリを取得
		::StringCbCopy( Temp, sizeof(Temp), pSrcPath );
		Temp[Len] = L'\0';
		GetLongFullPathName( Temp, LongPath, sizeof(LongPath) );

		// ファイル名検索
		hFind = ::FindFirstFile( pSrcPath, &FindData );
		if ( hFind == INVALID_HANDLE_VALUE )
		{
			::StringCbCat( pDstPath, DstPathSize, LongPath );
		}
		else
		{
			::FindClose( hFind );

			::StringCbCat( pDstPath, DstPathSize, LongPath );
			::StringCbCat( pDstPath, DstPathSize, L"\\" );
			::StringCbCat( pDstPath, DstPathSize, FindData.cFileName );
		}
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::CopyToUpper( wchar_t *pDst, const wchar_t *pSrc )
{
	while ( *pSrc != L'\0' )
	{
		switch ( *pSrc )
		{
		case L'a': *pDst = L'A'; break;
		case L'b': *pDst = L'B'; break;
		case L'c': *pDst = L'C'; break;
		case L'd': *pDst = L'D'; break;
		case L'e': *pDst = L'E'; break;
		case L'f': *pDst = L'F'; break;
		case L'g': *pDst = L'G'; break;
		case L'h': *pDst = L'H'; break;
		case L'i': *pDst = L'I'; break;
		case L'j': *pDst = L'J'; break;
		case L'k': *pDst = L'K'; break;
		case L'l': *pDst = L'L'; break;
		case L'm': *pDst = L'M'; break;
		case L'n': *pDst = L'N'; break;
		case L'o': *pDst = L'O'; break;
		case L'p': *pDst = L'P'; break;
		case L'q': *pDst = L'Q'; break;
		case L'r': *pDst = L'R'; break;
		case L's': *pDst = L'S'; break;
		case L't': *pDst = L'T'; break;
		case L'u': *pDst = L'U'; break;
		case L'v': *pDst = L'V'; break;
		case L'w': *pDst = L'W'; break;
		case L'x': *pDst = L'X'; break;
		case L'y': *pDst = L'Y'; break;
		case L'z': *pDst = L'Z'; break;
		default: *pDst = *pSrc; break;
		}

		*pSrc++;
		*pDst++;
	}
}


