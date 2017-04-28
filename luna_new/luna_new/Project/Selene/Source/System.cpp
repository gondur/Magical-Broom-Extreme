

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "System.h"
#include "Core/CCore.h"
#include "File/CFileHtmlLog.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static Bool g_IsInitialize					= false;
static Bool g_IsSuportSSE					= false;
static HANDLE g_hMutex						= NULL;
static ICore *g_pCore						= NULL;
static wchar_t g_CurrentDirectry[MAX_PATH]	= L"";



//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::System::Initialize( void )
{
	if ( !g_IsInitialize )
	{
		size_t Len;
		Sint32 Flag = 0;

		//------------------------------------------------------
		// SSE2
		//------------------------------------------------------
		_asm
		{
			push	eax
			push	edx

			mov		eax,	0x00000001
			_emit	0x0F
			_emit	0xA2
			mov		Flag,	edx

			pop		edx
			pop		eax
		}

		g_IsSuportSSE = (Flag & 0x04000000) != 0;

		//------------------------------------------------------
		// COM�̏�����
		//------------------------------------------------------
		::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

		//------------------------------------------------------
		// �J�����g�f�B���N�g��
		//------------------------------------------------------
		::GetModuleFileName( ::GetModuleHandle( NULL ), g_CurrentDirectry, MAX_PATH );
		Len = wcslen( g_CurrentDirectry );
		while ( g_CurrentDirectry[Len] != L'\\' )
		{
			g_CurrentDirectry[Len] = L'\0';
			if ( --Len < 0 ) break;
		}
		::SetCurrentDirectory( g_CurrentDirectry );

		//------------------------------------------------------
		// ���O�t�@�C��
		//------------------------------------------------------
		Log_Initialize( g_CurrentDirectry );

		//------------------------------------------------------
		// �^�C�}�[���x�ݒ�
		//------------------------------------------------------
		::timeBeginPeriod( 1 );

		g_IsInitialize = true;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::Finalize( void )
{
	if ( g_IsInitialize )
	{
		g_IsInitialize = false;

		//------------------------------------------------------
		// �R�A���
		//------------------------------------------------------
		SAFE_RELEASE( g_pCore );

		//------------------------------------------------------
		// �~���[�e�b�N�X
		//------------------------------------------------------
		if ( g_hMutex != NULL )
		{
			::CloseHandle( g_hMutex );
		}

		//------------------------------------------------------
		// ���O�p
		//------------------------------------------------------
		Log_Finalize();

		//------------------------------------------------------
		// �^�C�}�[���x����
		//------------------------------------------------------
		::timeEndPeriod( 1 );

		//------------------------------------------------------
		// COM�̉��
		//------------------------------------------------------
		::CoUninitialize();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::System::BlockDualBoot( const wchar_t *pApplicationName )
{
	if ( g_hMutex == NULL )
	{
		// ��d�N���m�F
		g_hMutex = ::CreateMutex( NULL, false, pApplicationName );
		if ( ::WaitForSingleObject( g_hMutex, 0 ) != WAIT_OBJECT_0 )
		{
			// ���łɂ���
			::CloseHandle( g_hMutex );
			g_hMutex = NULL;

			return false;
		}
	}

	return true;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::System::IsSuportSSE( void )
{
	return g_IsSuportSSE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICore *Selene::System::CreateCore( void )
{
	if ( g_pCore == NULL )
	{
		g_pCore = CCore::CreateCore();
	}
	else
	{
		g_pCore->AddRef();
	}

	return g_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::ResetCurrentDirectory( void )
{
	::SetCurrentDirectory( g_CurrentDirectry );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::CreateDirectory( const wchar_t *pPath )
{
	SECURITY_ATTRIBUTES Attr = { sizeof(SECURITY_ATTRIBUTES) };
	wchar_t Work[MAX_PATH] = L"";
	Uint32 pos = 0;
	Uint32 len = (Sint32)wcslen(pPath);
	WIN32_FIND_DATA FindData;

	while ( pos < len )
	{
		// �t�H���_���擾
		while ( (pos < len) && ((pPath[pos] != L'/') && (pPath[pos] != L'\\')) )
		{
			Work[pos] = pPath[pos];
			pos++;
		}

		Work[pos] = L'\0';

		// �t�H���_���Ȃ����͍��
		HANDLE hFind = ::FindFirstFile( Work, &FindData );
		if ( hFind != INVALID_HANDLE_VALUE )
		{
			::CreateDirectory( Work, &Attr );
			::CloseHandle( hFind );
		}

		Work[pos] = L'\\';
		pos++;
	}
}

