

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
	case WSABASEERR:				::StringCbCopy( String, sizeof(String), L"�G���[�͔������Ă��Ȃ�" );								break;
	case WSAEINTR:					::StringCbCopy( String, sizeof(String), L"�֐��Ăяo�������f���ꂽ" );								break;
	case WSAEBADF:					::StringCbCopy( String, sizeof(String), L"�����ȃt�@�C���n���h��" );								break;
	case WSAEACCES:					::StringCbCopy( String, sizeof(String), L"�A�N�Z�X�����ۂ��ꂽ" );									break;
	case WSAEFAULT:					::StringCbCopy( String, sizeof(String), L"�����ȃo�b�t�@�A�h���X" );								break;
	case WSAEINVAL:					::StringCbCopy( String, sizeof(String), L"�����Ȉ������n���ꂽ" );									break;
	case WSAEMFILE:					::StringCbCopy( String, sizeof(String), L"�g�p���̃\�P�b�g�̐�����������" );						break;
	case WSAEWOULDBLOCK:			::StringCbCopy( String, sizeof(String), L"����̓u���b�L���O�����" );								break;
	case WSAEINPROGRESS:			::StringCbCopy( String, sizeof(String), L"���łɃu���b�L���O�葱�������s����Ă���" );				break;
	case WSAEALREADY:				::StringCbCopy( String, sizeof(String), L"�v�����ꂽ����͊��Ɏ��s���A�܂��͎��s�ς�" );			break;
	case WSAENOTSOCK:				::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�\�P�b�g�������ł���" );						break;
	case WSAEDESTADDRREQ:			::StringCbCopy( String, sizeof(String), L"����̎��s�ɑ��M��A�h���X���K�v" );						break;
	case WSAEMSGSIZE:				::StringCbCopy( String, sizeof(String), L"���b�Z�[�W�T�C�Y���傫������" );							break;
	case WSAEPROTOTYPE:				::StringCbCopy( String, sizeof(String), L"�\�P�b�g�͗v�����ꂽ�v���g�R���ɓK�����Ă��Ȃ�" );		break;
	case WSAENOPROTOOPT:			::StringCbCopy( String, sizeof(String), L"�s���ȃv���g�R���I�v�V����" );							break;
	case WSAEPROTONOSUPPORT:		::StringCbCopy( String, sizeof(String), L"�v���g�R�����T�|�[�g����Ă��Ȃ�" );						break;
	case WSAESOCKTNOSUPPORT:		::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�\�P�b�g�^�C�v�̓T�|�[�g����Ă��Ȃ�" );		break;
	case WSAEOPNOTSUPP:				::StringCbCopy( String, sizeof(String), L"�v�����ꂽ����̓T�|�[�g����Ă��Ȃ�" );					break;
	case WSAEPFNOSUPPORT:			::StringCbCopy( String, sizeof(String), L"�v���g�R���t�@�~�����T�|�[�g����Ă��Ȃ�" );				break;
	case WSAEAFNOSUPPORT:			::StringCbCopy( String, sizeof(String), L"�A�h���X�t�@�~�����T�|�[�g����Ă��Ȃ�" );				break;
	case WSAEADDRINUSE:				::StringCbCopy( String, sizeof(String), L"�A�h���X�͊��Ɏg�p���ł���" );							break;
	case WSAEADDRNOTAVAIL:			::StringCbCopy( String, sizeof(String), L"�����ȃl�b�g���[�N�A�h���X" );							break;
	case WSAENETDOWN:				::StringCbCopy( String, sizeof(String), L"�l�b�g���[�N���_�E�����Ă���" );							break;
	case WSAENETUNREACH:			::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�l�b�g���[�N�z�X�g�ɓ��B�ł��Ȃ�" );			break;
	case WSAENETRESET:				::StringCbCopy( String, sizeof(String), L"�l�b�g���[�N�ڑ����j�����ꂽ" );							break;
	case WSAECONNABORTED:			::StringCbCopy( String, sizeof(String), L"�l�b�g���[�N�ڑ����j�����ꂽ" );							break;
	case WSAECONNRESET:				::StringCbCopy( String, sizeof(String), L"�l�b�g���[�N�ڑ�������ɂ���Ĕj�����ꂽ" );				break;
	case WSAENOBUFS:				::StringCbCopy( String, sizeof(String), L"�o�b�t�@���s�����Ă���" );								break;
	case WSAEISCONN:				::StringCbCopy( String, sizeof(String), L"�\�P�b�g�͊��ɐڑ�����Ă���" );							break;
	case WSAENOTCONN:				::StringCbCopy( String, sizeof(String), L"�\�P�b�g�͐ڑ�����Ă��Ȃ�" );							break;
	case WSAESHUTDOWN:				::StringCbCopy( String, sizeof(String), L"�\�P�b�g�̓V���b�g�_�E������Ă���" );					break;
	case WSAETOOMANYREFS:			::StringCbCopy( String, sizeof(String), L"�Q�Ƃ̐�����������" );									break;
	case WSAETIMEDOUT:				::StringCbCopy( String, sizeof(String), L"�ڑ��v�����^�C���A�E�g����" );							break;
	case WSAECONNREFUSED:			::StringCbCopy( String, sizeof(String), L"�ڑ������ۂ��ꂽ" );										break;
	case WSAELOOP:					::StringCbCopy( String, sizeof(String), L"���[�v" );												break;
	case WSAENAMETOOLONG:			::StringCbCopy( String, sizeof(String), L"���O����������" );										break;
	case WSAEHOSTDOWN:				::StringCbCopy( String, sizeof(String), L"�z�X�g���_�E�����Ă���" );								break;
	case WSAEHOSTUNREACH:			::StringCbCopy( String, sizeof(String), L"�z�X�g�ւ̌o�H���Ȃ�" );									break;
	case WSAENOTEMPTY:				::StringCbCopy( String, sizeof(String), L"�f�B���N�g������ł͂Ȃ�" );								break;
	case WSAEPROCLIM:				::StringCbCopy( String, sizeof(String), L"�v���Z�X�̐�����������" );								break;
	case WSAEUSERS:					::StringCbCopy( String, sizeof(String), L"���[�U�̐�����������" );									break;
	case WSAEDQUOT:					::StringCbCopy( String, sizeof(String), L"�f�B�X�N�N�H�[�^" );										break;
	case WSAESTALE:					::StringCbCopy( String, sizeof(String), L"���s���悤�Ƃ�������͔p�~����Ă���" );					break;
	case WSAEREMOTE:				::StringCbCopy( String, sizeof(String), L"�����[�g" );												break;
	case WSASYSNOTREADY:			::StringCbCopy( String, sizeof(String), L"�l�b�g���[�N�T�u�V�X�e�������p�ł��Ȃ�" );				break;
	case WSAVERNOTSUPPORTED:		::StringCbCopy( String, sizeof(String), L"Winsock.dll�̃o�[�W�������͈͊O�ł���" );					break;
	case WSANOTINITIALISED:			::StringCbCopy( String, sizeof(String), L"WinSock�V�X�e��������������Ă��Ȃ�" );					break;
	case WSAEDISCON:				::StringCbCopy( String, sizeof(String), L"�V���b�g�_�E��������" );									break;
	case WSAENOMORE:				::StringCbCopy( String, sizeof(String), L"�f�[�^�͂���ȏ㑶�݂��Ȃ�" );							break;
	case WSAECANCELLED:				::StringCbCopy( String, sizeof(String), L"����͎������ꂽ" );									break;
	case WSAEINVALIDPROCTABLE:		::StringCbCopy( String, sizeof(String), L"�T�[�r�X�v���o�C�_�̊֐��e�[�u��������" );				break;
	case WSAEINVALIDPROVIDER:		::StringCbCopy( String, sizeof(String), L"�T�[�r�X�v���o�C�_������" );								break;
	case WSAEPROVIDERFAILEDINIT:	::StringCbCopy( String, sizeof(String), L"�T�[�r�X�v���o�C�_�̏������Ɏ��s����" );					break;
	case WSASYSCALLFAILURE:			::StringCbCopy( String, sizeof(String), L"�V�X�e���R�[���Ɏ��s����" );								break;
	case WSASERVICE_NOT_FOUND:		::StringCbCopy( String, sizeof(String), L"�T�[�r�X��������Ȃ�" );								break;
	case WSATYPE_NOT_FOUND:			::StringCbCopy( String, sizeof(String), L"�^�C�v��������Ȃ�" );									break;
	case WSA_E_CANCELLED:			::StringCbCopy( String, sizeof(String), L"�������L�����Z�����ꂽ" );								break;
	case WSAEREFUSED:				::StringCbCopy( String, sizeof(String), L"����͋��ۂ��ꂽ" );										break;
	case WSAHOST_NOT_FOUND:			::StringCbCopy( String, sizeof(String), L"�z�X�g��������Ȃ�" );									break;
	case WSATRY_AGAIN:				::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�z�X�g��������Ȃ��A�܂��̓T�[�r�X�ُ̈�" );	break;
	case WSANO_RECOVERY:			::StringCbCopy( String, sizeof(String), L"�񕜕s�\�ȃG���[����������" );							break;
	case WSANO_DATA:				::StringCbCopy( String, sizeof(String), L"�v�����ꂽ�^�C�v�̃f�[�^���R�[�h��������Ȃ�" );		break;
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
	case D3D_OK:							::StringCbCopy( String, sizeof(String), L"�G���[�͔������Ă��Ȃ��B" );																																					break;
	case D3DERR_CONFLICTINGRENDERSTATE:		::StringCbCopy( String, sizeof(String), L"���ݐݒ肳��Ă��郌���_�����O �X�e�[�g�͈ꏏ�Ɏg�p�ł��Ȃ��B" );																												break;
	case D3DERR_CONFLICTINGTEXTUREFILTER:	::StringCbCopy( String, sizeof(String), L"���݂̃e�N�X�`�� �t�B���^�͈ꏏ�Ɏg�p�ł��Ȃ��B" );																															break;
	case D3DERR_CONFLICTINGTEXTUREPALETTE:	::StringCbCopy( String, sizeof(String), L"���݂̃e�N�X�`���͓����Ɏg�p�ł��Ȃ��B��ʂɃ}���`�e�N�X�`�� �f�o�C�X�ɂ����āA�����ɗL���ɂ��ꂽ�p���b�g���e�N�X�`���œ����p���b�g�����L����K�v������ꍇ�ɔ�������B" );	break;
	case D3DERR_DEVICELOST:					::StringCbCopy( String, sizeof(String), L"�f�o�C�X�������Ă��āA�����_�ł͕����ł��Ȃ����߁A�����_�����O�͕s�\�ł���B" );																							break;
	case D3DERR_DEVICENOTRESET:				::StringCbCopy( String, sizeof(String), L"�f�o�C�X�̓��Z�b�g�ł��Ȃ��B" );																																				break;
	case D3DERR_DRIVERINTERNALERROR:		::StringCbCopy( String, sizeof(String), L"�����h���C�o �G���[�B" );																																						break;
	case D3DERR_INVALIDCALL:				::StringCbCopy( String, sizeof(String), L"���\�b�h�̌Ăяo���������ł���B���Ƃ��΁A���\�b�h�̃p�����[�^�ɖ����Ȓl���ݒ肳��Ă���ꍇ�ȂǁB" );																			break;
	case D3DERR_INVALIDDEVICE:				::StringCbCopy( String, sizeof(String), L"�v�����ꂽ�f�o�C�X�̎�ނ��L���łȂ��B" );																																		break;
	case D3DERR_MOREDATA:					::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�o�b�t�@ �T�C�Y�ɕێ��ł���ȏ�̃f�[�^�����݂���B" );																												break;
	case D3DERR_NOTAVAILABLE:				::StringCbCopy( String, sizeof(String), L"���̃f�o�C�X�́A�Ɖ�ꂽ�e�N�j�b�N���T�|�[�g���Ă��Ȃ��B" );																													break;
	case D3DERR_NOTFOUND:					::StringCbCopy( String, sizeof(String), L"�v�����ꂽ���ڂ�������Ȃ������B" );																																			break;
	case D3DERR_OUTOFVIDEOMEMORY:			::StringCbCopy( String, sizeof(String), L"Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ���������Ȃ��B" );																													break;
	case D3DERR_TOOMANYOPERATIONS:			::StringCbCopy( String, sizeof(String), L"�f�o�C�X���T�|�[�g���Ă���ȏ�̃e�N�X�`�� �t�B���^�����O�������A�A�v���P�[�V�������v�����Ă���B" );																			break;
	case D3DERR_UNSUPPORTEDALPHAARG:		::StringCbCopy( String, sizeof(String), L"�A���t�@ �`���l���ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																		break;
	case D3DERR_UNSUPPORTEDALPHAOPERATION:	::StringCbCopy( String, sizeof(String), L"�A���t�@ �`���l���ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																		break;
	case D3DERR_UNSUPPORTEDCOLORARG:		::StringCbCopy( String, sizeof(String), L"�J���[�l�ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																				break;
	case D3DERR_UNSUPPORTEDCOLOROPERATION:	::StringCbCopy( String, sizeof(String), L"�J���[�l�ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																				break;
	case D3DERR_UNSUPPORTEDFACTORVALUE:		::StringCbCopy( String, sizeof(String), L"�f�o�C�X���w�肳�ꂽ�e�N�X�`���W���l���T�|�[�g���Ă��Ȃ��B" );																													break;
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:	::StringCbCopy( String, sizeof(String), L"�f�o�C�X���w�肳�ꂽ�e�N�X�`�� �t�B���^���T�|�[�g���Ă��Ȃ��B" );																												break;
	case D3DERR_WRONGTEXTUREFORMAT:			::StringCbCopy( String, sizeof(String), L"�e�N�X�`�� �T�[�t�F�X�̃s�N�Z�� �t�H�[�}�b�g���L���łȂ��B" );																													break;
	case E_FAIL:							::StringCbCopy( String, sizeof(String), L"Direct3D �T�u�V�X�e�����Ō����s���̃G���[�����������B" );																														break;
	case E_INVALIDARG:						::StringCbCopy( String, sizeof(String), L"�����ȃp�����[�^���߂��Ă���֐��ɓn���ꂽ�B" );																																break;
	case E_OUTOFMEMORY:						::StringCbCopy( String, sizeof(String), L"Direct3D ���Ăяo�����������邽�߂̏\���ȃ����������蓖�Ă邱�Ƃ��ł��Ȃ������B" );																							break;
	case D3DXERR_CANNOTATTRSORT:			::StringCbCopy( String, sizeof(String), L"�œK���e�N�j�b�N�Ƃ��đ����̃\�[�g (::D3DXMESHOPT_ATTRSORT) �̓T�|�[�g����Ă��Ȃ��B " );																						break;
	case D3DXERR_CANNOTMODIFYINDEXBUFFER:	::StringCbCopy( String, sizeof(String), L"�C���f�b�N�X �o�b�t�@��ύX�ł��Ȃ��B " );																																		break;
	case D3DXERR_INVALIDMESH:				::StringCbCopy( String, sizeof(String), L"���b�V���������ł���B " );																																					break;
	case D3DXERR_SKINNINGNOTSUPPORTED:		::StringCbCopy( String, sizeof(String), L"�X�L�j���O�̓T�|�[�g����Ă��Ȃ��B " );																																		break;
	case D3DXERR_TOOMANYINFLUENCES:			::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�e������������B " );																																				break;
	case D3DXERR_INVALIDDATA:				::StringCbCopy( String, sizeof(String), L"�f�[�^�������ł���B" );																																						break;
	default:								::StringCbCopy( String, sizeof(String), L"���m�̃G���[�B" );																																								break;
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

		// �e�f�B���N�g�����擾
		::StringCbCopy( Temp, sizeof(Temp), pSrcPath );
		Temp[Len] = L'\0';
		GetLongFullPathName( Temp, LongPath, sizeof(LongPath) );

		// �t�@�C��������
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


