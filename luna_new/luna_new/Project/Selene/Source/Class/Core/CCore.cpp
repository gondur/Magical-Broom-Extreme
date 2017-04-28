

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "System.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Peripheral/CInput.h"
#include "Peripheral/CKeyboard.h"
#include "Peripheral/CMouse.h"
#include "Math/Random.h"
#include "File/CFileHtmlLog.h"
#include "File/CFileManager.h"
#include "Surface/CTexture.h"
#include "Surface/CSurface.h"
#include "Sound/CSound.h"
#include "NullDevice/Sound/NullSound.h"
#include "../Project/Lib/Ayame.h"


//-----------------------------------------------------------------------------------
// PROTOTYPE
//-----------------------------------------------------------------------------------
bool Ayame_Initialize( HWND hWnd, void **ppDirectSound, AYAME_MEMORY_ALLOC_PROC pAllocProc, AYAME_MEMORY_FREE_PROC pFreeProc );
void Ayame_Uninitialize( void );


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
static const wchar_t g_VersionInfo[] = L"Selene for \"DirectX 9.0c Update (October 2004)\" Phase 2006.09.26.0";


//-----------------------------------------------------------------------------------
// DEFINEE
//-----------------------------------------------------------------------------------
static const Uint32 TIMER_SCALE_SHIFT		= 32;
static const Uint64 TIMER_MAX_COUNT			= (Uint64)0xFFFFFFFF << TIMER_SCALE_SHIFT;


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace System;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore::CCore( void )
	: m_pFileManager			( NULL )
	, m_pGraphicCard			( NULL )
	, m_pDevice					( NULL )
	, m_hWindow					( NULL )
	, m_hMutex					( NULL )
	, m_pInput					( NULL )
	, m_pKeyboard				( NULL )
	, m_pMouse					( NULL )
	, m_IsWindowType			( false )
	, m_IsActive				( false )
	, m_IsActiveWindow			( false )
	, m_IsInitAyame				( false )
	, m_NowTime					( 0 )
	, m_OldTime					( 0 )
	, m_BeforeTime				( 0 )
	, m_ScreenWidth				( 0 )
	, m_ScreenHeight			( 0 )
	, m_SyncCount				( 0 )
	, m_FrameRate				( FRAME_RATE_60 )
	, m_FPS						( 0 )
	, m_OldFPS					( 0 )
	, m_PPS						( 0 )
	, m_OldPPS					( 0 )
	, m_PPS3D					( 0 )
	, m_OldPPS3D				( 0 )
	, m_PPF						( 0 )
	, m_OldPPF					( 0 )
	, m_PPF3D					( 0 )
	, m_OldPPF3D				( 0 )
	, m_VirtualScreenWidth		( 0 )
	, m_VirtualScreenHeight		( 0 )
	, m_fVirtual2RealX			( 0.0f )
	, m_fVirtual2RealY			( 0.0f )
	, m_fBackUpVirtual2RealX	( 0.0f )
	, m_fBackUpVirtual2RealY	( 0.0f )
	, m_fFrameTime				( 0.0f )
{
	MemoryClear( m_ApplicationName, sizeof(m_ApplicationName) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore::~CCore( void )
{
	// ���L�I�u�W�F�N�g�̉��
	SAFE_RELEASE( m_pMouse );
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pInput );
	SAFE_RELEASE( m_pDevice );
	SAFE_RELEASE( m_pFileManager );

	//---------------------------------------------------------
	// AYAME���
	//---------------------------------------------------------
	if ( m_IsInitAyame )
	{
		Ayame_Uninitialize();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::RegisterWindowClass( void )
{
	WNDCLASS WindowClass;

	//---------------------------------------------------------
	//	�E�B���h�E�N���X�o�^
	//---------------------------------------------------------
	WindowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WindowClass.lpfnWndProc		= CommonMsgProc;
	WindowClass.cbClsExtra		= 0;
	WindowClass.cbWndExtra		= 0;
	WindowClass.hInstance		= ::GetModuleHandle( NULL );
	WindowClass.hIcon			= NULL;
	WindowClass.hCursor			= ::LoadCursor( NULL, IDC_ARROW );
	WindowClass.hbrBackground	= (HBRUSH)::GetStockObject( BLACK_BRUSH );
	WindowClass.lpszMenuName	= NULL;
	WindowClass.lpszClassName	= m_ApplicationName;

	// �E�B���h�E�N���X�o�^
	return ::RegisterClass( &WindowClass ) != 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::WindowCreate( void )
{
	char Temp[MAX_PATH] = "";
	WCStoMBCS( m_ApplicationName, Temp );

	//---------------------------------------------------------
	// �E�B���h�E����
	//---------------------------------------------------------
	m_hWindow = ::CreateWindowExA(
							0,
							Temp,
							Temp,
							WS_POPUP,
							CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT,
							NULL,
							NULL,
							::GetModuleHandle( NULL ),
							NULL );

	if ( m_hWindow == NULL ) return false;

	//---------------------------------------------------------
	// �f�[�^
	//---------------------------------------------------------
	::SetWindowLong( m_hWindow, GWL_USERDATA, (LONG)this );

	//---------------------------------------------------------
	// �A�C�R���ݒ�
	//---------------------------------------------------------
	HICON hIcon;
	hIcon = (HICON)::LoadImage( ::GetModuleHandle( NULL ), L"ICON_SMALL", IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( m_hWindow, WM_SETICON, ICON_SMALL, (LPARAM)hIcon );
	hIcon = (HICON)::LoadImage( ::GetModuleHandle( NULL ), L"ICON_BIG", IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( m_hWindow, WM_SETICON, ICON_BIG, (LPARAM)hIcon );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::Initialize( const wchar_t *pAppName, eFrameRate FrameRate )
{
	//=========================================================
	// �ϐ�������
	//=========================================================
	::StringCbCopy( m_ApplicationName, sizeof(m_ApplicationName), pAppName );
	m_FrameRate = FrameRate;

	//=========================================================
	// �E�B���h�E�N���X�̓o�^
	//=========================================================
	if ( !RegisterWindowClass() )
	{
		MsgBox( MB_ICONERROR, L"ERROR", L"�E�B���h�E�N���X�̓o�^�Ɏ��s" );
		return false;
	}

	//=========================================================
	// �E�B���h�E����
	//=========================================================
	if ( !WindowCreate() )
	{
		MsgBox( MB_ICONERROR, L"ERROR", L"�E�B���h�E�����Ɏ��s" );
		return false;
	}

	//=========================================================
	// ���̓f�o�C�X�N���X�̏�����
	//=========================================================
	m_pInput = new CInput( ::GetModuleHandle( NULL ) );
	AddChild( m_pInput );
	m_pInput->GetKeyboard( &m_pKeyboard );
	m_pInput->GetMouse( &m_pMouse );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::Start( Uint32 ScreenWidth, Uint32 ScreenHeight, Bool IsWindowType )
{
	//----------------------------------------------------
	// �E�B���h�E�T�C�Y
	//----------------------------------------------------
	m_IsWindowType = IsWindowType;
	m_ScreenWidth  = ScreenWidth;
	m_ScreenHeight = ScreenHeight;
	SetVirtualScreenSize( m_ScreenWidth, m_ScreenHeight, m_ScreenWidth, m_ScreenHeight );

	//----------------------------------------------------
	// �E�B���h�E�ό`
	//----------------------------------------------------
	UpdateWidow();

	//----------------------------------------------------
	// AYAME������
	//----------------------------------------------------
	Ayame_Initialize( m_hWindow, NULL, NULL, NULL );
	m_IsInitAyame = true;

	//----------------------------------------------------
	// ���ԕۑ�
	//----------------------------------------------------
	m_OldTime = GetSystemTime();
	m_BeforeTime = GetSystemTime();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::Message( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	//======================================================================
	// ���b�Z�[�W����
	//======================================================================
	switch ( Msg )
	{
	//--------------------------------------------------------- �}�E�X�z�C�[��
	case WM_MOUSEWHEEL:
		if ( m_pMouse != NULL )
		{
			m_pMouse->SetMouseWheel( (Sint16)HIWORD(wParam) );
		}
		break;

	//--------------------------------------------------------- ���_�u���N���b�N
	case WM_LBUTTONDBLCLK:
		if ( m_pMouse != NULL )
		{
			m_pMouse->SetDoubleClickL();
		}
		break;

	//--------------------------------------------------------- �E�_�u���N���b�N
	case WM_RBUTTONDBLCLK:
		if ( m_pMouse )
		{
			m_pMouse->SetDoubleClickR();
		}
		break;

	//--------------------------------------------------------- �z�C�[���_�u���N���b�N
	case WM_MBUTTONDBLCLK:
		if ( m_pMouse != NULL )
		{
			m_pMouse->SetDoubleClickM();
		}
		break;

	//--------------------------------------------------------- �V�X�e���L�[
	case WM_SYSKEYUP:
		// ALT+ENTER�Ńt���X�N���[���؂�ւ�
		if ( wParam == VK_RETURN )
		{
			// ��ʐ؂�ւ�
			ChangeScreenType();
		}
		break;

	//--------------------------------------------------------- �t�H�[�J�X�ړ���
	case WM_ACTIVATEAPP:
		m_IsActiveWindow = (wParam != 0);
		break;

	//--------------------------------------------------------- �I����
	case WM_CLOSE:
		// �����E�B���h�E�n���h���������
		m_hWindow = NULL;
		// �I��
		::SendMessage( hWnd, WM_DESTROY, 0, 0 );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetDevice( CDevice *pDevice )
{
	m_pDevice = pDevice;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::MsgBox( Uint32 Flag, const wchar_t *pTitle, const wchar_t *pStr,... )
{
	wchar_t Temp[1024] = L"";

	::StringCbVPrintf( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

	if ( m_pDevice != NULL ) m_pDevice->SetDialogBoxType( true );
	::MessageBox( m_hWindow, Temp, pTitle, Flag );
	if ( m_pDevice != NULL ) m_pDevice->SetDialogBoxType( false );

	// FEP����
	::SendMessage( ::ImmGetDefaultIMEWnd( m_hWindow ), WM_CLOSE, 0, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::SelectBox( const wchar_t *pTitle, const wchar_t *pStr,... )
{
	wchar_t Temp[1024] = L"";
	Uint32 Ret;

	::StringCbVPrintf( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

	if ( m_pDevice != NULL ) m_pDevice->SetDialogBoxType( true );
	Ret = ::MessageBox( m_hWindow, Temp, pTitle, MB_YESNO | MB_ICONQUESTION );
	if ( m_pDevice != NULL ) m_pDevice->SetDialogBoxType( false );
	
	// FEP����
	::SendMessage( ::ImmGetDefaultIMEWnd( m_hWindow ), WM_CLOSE, 0, 0 );

	return Ret == IDYES;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::Run( Bool IsFullActive )
{
	MSG Msg;

	//--------------------------------------------------
	// ���b�Z�[�W���[�v
	//--------------------------------------------------
	for ( ; ; )
	{
		// ���b�Z�[�W����
		while ( ::PeekMessage( &Msg, 0, 0, 0, PM_REMOVE ) )
		{
			// �I���H
			if ( Msg.message == WM_QUIT )
			{
				m_IsActiveWindow	= true;
				m_IsActive			= false;

				return false;
			}

			// ���b�Z�[�W�̖|��
			::TranslateMessage( &Msg );
			::DispatchMessage( &Msg );
		}

		// �A�N�e�B�u�łȂ��Ƃ��̓X���[�v
		if ( IsFullActive || m_IsActiveWindow )
		{
			break;
		}
		else
		{
			::SleepEx( 100, true );
		}
	}

	//--------------------------------------------------
	// �t���[�������ݒ�
	//--------------------------------------------------

	// �t���[�����[�g����
	SyncFrame();

	// ���̓f�o�C�X�X�V
	m_pInput->Refresh();

	// �p�b�h�X�V

	// �f�o�C�X����
	if ( m_pDevice != NULL )
	{
		// ��ʂ����t���b�V��
		m_pDevice->Refresh( m_hWindow );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SyncFrame( void )
{
	static const Uint32 Tbl[] = { 60, 30, 20, 15 };

	//--------------------------------------------
	// ���݂̎��Ԏ擾
	//--------------------------------------------
	m_NowTime = GetSystemTime();

	//--------------------------------------------
	// ����
	//--------------------------------------------
	Uint64 DifferenceTime = m_NowTime - m_OldTime;
	if ( m_NowTime < m_OldTime )
	{  
		DifferenceTime = TIMER_MAX_COUNT - (m_OldTime - m_NowTime);
	}

	//--------------------------------------------
	// FrameRate��VSYN�ˑ��łȂ���
	//--------------------------------------------
	if ( m_FrameRate != FRAME_RATE_VSYNC )
	{
		Uint64 WaitTime = GetSystemOneSecondTime() / Tbl[m_FrameRate];

		//----------------------------------
		// ���Ԍo�߂�҂�
		//----------------------------------
		if ( DifferenceTime < WaitTime )
		{
			Uint32 SleepTime = (Uint32)((WaitTime - DifferenceTime) >> TIMER_SCALE_SHIFT);
			if ( SleepTime >= 3 ) ::SleepEx( SleepTime - 1, TRUE );

			// �󃋁[�v�Ō����ɏ���������
			do 
			{
				m_NowTime = GetSystemTime();
				DifferenceTime = m_NowTime - m_OldTime;
			}
			while ( DifferenceTime < WaitTime );
		}
	}
	else
	{
		::SleepEx( 1, TRUE );
		m_NowTime = GetSystemTime();
	}

	//--------------------------------------------
	// �I��
	//--------------------------------------------
	m_OldTime = m_NowTime;

	//--------------------------------------------
	// �t���[�������Z
	//--------------------------------------------
	m_SyncCount++;
	m_FPS++;

	//--------------------------------------------
	// FPS�Z�o
	//--------------------------------------------
	if ( (m_NowTime - m_BeforeTime) >= GetSystemOneSecondTime() )
	{
		m_BeforeTime = m_NowTime;

		// FPS�ۑ�
		m_OldFPS = m_FPS;
		m_OldPPS = m_PPS;
		m_OldPPF = m_PPS / m_FPS;
		m_OldPPF3D = m_PPS3D / m_FPS;
		m_FPS = 0;
		m_PPS = 0;
		m_PPF = 0;
		m_PPS3D = 0;
		m_PPF3D = 0;

		// �`��n�m�Ȃ�^�C�g�����ɕ\��
//		if ( m_IsDrawTitleInfo )
		{
			wchar_t Temp[256] = L"";
			::StringCbPrintf(
				Temp, sizeof(Temp),
				L"%s FPS[%d] PPS[%d] PPF[%d] PPF3D[%d]",
				m_ApplicationName,
				m_OldFPS,
				m_OldPPS,
				m_OldPPF,
				m_OldPPF3D );
			::SetWindowText( m_hWindow, Temp );
		}
	}

	m_fFrameTime = toF(toI(DifferenceTime >> TIMER_SCALE_SHIFT)) * 0.001f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetVirtualScreenSize( Uint32 RealWidth, Uint32 RealHeight, Uint32 VirtualWidth, Uint32 VirtualHeight )
{
	m_VirtualScreenWidth  = VirtualWidth;
	m_VirtualScreenHeight = VirtualHeight;

	m_fVirtual2RealX = toF(RealWidth)  / toF(VirtualWidth);
	m_fVirtual2RealY = toF(RealHeight) / toF(VirtualHeight);

	m_fBackUpVirtual2RealX = m_fVirtual2RealX;
	m_fBackUpVirtual2RealY = m_fVirtual2RealY;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetVirtualScreenEnable( Bool Flag )
{
	if ( Flag )
	{
		m_fVirtual2RealX = m_fBackUpVirtual2RealX;
		m_fVirtual2RealY = m_fBackUpVirtual2RealY;
	}
	else
	{
		m_fBackUpVirtual2RealX = m_fVirtual2RealX;
		m_fBackUpVirtual2RealY = m_fVirtual2RealY;
		m_fVirtual2RealX = 1.0f;
		m_fVirtual2RealY = 1.0f;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::Virtual2RealX( Float Pos )
{
	return Pos * m_fVirtual2RealX;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::Virtual2RealY( Float Pos )
{
	return Pos * m_fVirtual2RealY;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::DrawPolygon( Sint32 Cnt )
{
	m_PPS += Cnt;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::DrawPolygon3D( Sint32 Cnt )
{
	m_PPS3D += Cnt;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetWindowCenter( HWND hWnd, HWND hWndParent )
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
HWND CCore::GetWindowHandle( void )
{
	return m_hWindow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetFPS( void )
{
	return m_OldFPS;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetPPS( void )
{
	return m_OldPPS;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetPPF( void )
{
	return m_OldPPF;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetPPS3D( void )
{
	return m_OldPPS3D;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetPPF3D( void )
{
	return m_OldPPF3D;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::GetApplicationName( wchar_t *pAppName, Uint32 AppNameSize )
{
	::StringCbCopy( pAppName, AppNameSize, m_ApplicationName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::GetScreenData( Uint32 *pWidth, Uint32 *pHeight, Bool *pIsWindow )
{
	if ( pWidth != NULL ) *pWidth = m_ScreenWidth;
	if ( pHeight != NULL ) *pHeight = m_ScreenHeight;
	if ( pIsWindow != NULL ) *pIsWindow = m_IsWindowType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::GetVirtualScreenSize( Sint32 *pWidth, Sint32 *pHeight )
{
	*pWidth = m_VirtualScreenWidth;
	*pHeight = m_VirtualScreenHeight;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::ChangeScreenType( void )
{
	if ( m_IsWindowType )
	{
		// ���[�h�X���b�v
		m_IsWindowType = !m_IsWindowType;
		// �E�B���h�E���Z�b�g
		UpdateWidow();
		// Direct3D�f�o�C�X���Z�b�g
		m_pDevice->ResetDevice( true );
	}
	else
	{
		// ���[�h�X���b�v
		m_IsWindowType = !m_IsWindowType;
		// Direct3D�f�o�C�X���Z�b�g
		m_pDevice->ResetDevice( true );
		// �E�B���h�E���Z�b�g
		UpdateWidow();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::UpdateWidow( void )
{
	//---------------------------------------------------------
	// ���j���[
	//---------------------------------------------------------
	HMENU hMenu = ::LoadMenu( ::GetModuleHandle( NULL ), L"MAIN_MENU" );
	::SetMenu( m_hWindow, hMenu );

	//---------------------------------------------------------
	//	�E�B���h�E�������̍쐬
	//---------------------------------------------------------
	Uint32 x = 0;
	Uint32 y = 0;
	Uint32 w = m_ScreenWidth;
	Uint32 h = m_ScreenHeight;
	Uint32 Flag = WS_POPUP | WS_VISIBLE;

	if ( m_IsWindowType )
	{
		Flag |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		w +=
			::GetSystemMetrics(SM_CXBORDER)		+
			::GetSystemMetrics(SM_CXEDGE)		+
			::GetSystemMetrics(SM_CXDLGFRAME);

		h +=
			::GetSystemMetrics(SM_CYBORDER)		+
			::GetSystemMetrics(SM_CYEDGE)		+
			::GetSystemMetrics(SM_CYDLGFRAME)	+
			::GetSystemMetrics(SM_CYCAPTION);

		// ���j���[����H
		if ( hMenu != NULL )
		{
			h += ::GetSystemMetrics(SM_CYMENU);
		}

		x = ::GetSystemMetrics(SM_CXSCREEN)/2 - w/2;
		y = ::GetSystemMetrics(SM_CYSCREEN)/2 - h/2;
	}

	//---------------------------------------------------------
	// �E�C���h�E���[�h�ɂ������E�C���h�E�ɍĒ�`����
	//---------------------------------------------------------
	::SetWindowLong( m_hWindow, GWL_STYLE, Flag );

	//---------------------------------------------------------
	// �E�C���h�E�\�����W���Z�b�g
	//---------------------------------------------------------
	::SetWindowPos( m_hWindow, HWND_TOP, x, y, w, h, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::Exit( void )
{
	::PostMessage( m_hWindow, WM_CLOSE, 0, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint64 CCore::GetSystemTime( void )
{
	return (Uint64)::timeGetTime() << TIMER_SCALE_SHIFT;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint64 CCore::GetSystemOneSecondTime( void )
{
	return (Uint64)1000 << TIMER_SCALE_SHIFT;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CCore::GetSyncCount( void )
{
	return m_SyncCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::GetFrameTime( void )
{
	return m_fFrameTime;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eFrameRate CCore::GetFrameRate( void )
{
	return m_FrameRate;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::FolderSelect( wchar_t *pDirPath, Uint32 DirPathSize )
{
	pDirPath[0] = L'\0';

    HRESULT hr;
    BROWSEINFO bi;
    ITEMIDLIST *lpid = NULL;
    LPMALLOC pMalloc = NULL;

	MemoryClear( &bi, sizeof(BROWSEINFO) );

	bi.hwndOwner	= GetWindowHandle();
	bi.ulFlags		= BIF_EDITBOX;
	bi.lpszTitle	= L"�f�B���N�g���w��";

	lpid = ::SHBrowseForFolder( &bi );

	if ( lpid == NULL )
	{
		return false;
	}
	else
	{
		hr = ::SHGetMalloc( &pMalloc );
		if ( hr == E_FAIL )
		{
			return false;
		}

		::SHGetPathFromIDList( lpid, pDirPath );
		size_t Len = wcslen( pDirPath );
		if ( pDirPath[Len - 1] != L'\\' ) ::StringCbCat( pDirPath, DirPathSize, L"\\" );

		pMalloc->Free( lpid );
		SAFE_RELEASE( pMalloc );
	}

	ResetCurrentDirectory();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::FileOpenDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter, const wchar_t *pExt )
{
	pPath[0] = L'\0';

	//=======================================================
	// �t�@�C���I�[�v��
	//=======================================================
	OPENFILENAME ofn;
	MemoryClear( &ofn, sizeof(OPENFILENAME) );

	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= GetWindowHandle();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= 256;
	ofn.lpstrDefExt		= pExt;
	ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	Bool result = (::GetOpenFileName( &ofn ) != false);

	ResetCurrentDirectory();

	return result;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::FileSaveDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter, const wchar_t *pExt )
{
	pPath[0] = L'\0';
	
	OPENFILENAME ofn;
	MemoryClear( &ofn, sizeof(OPENFILENAME) );
	
	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= GetWindowHandle();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= 256;
	ofn.lpstrDefExt		= pExt;
	ofn.lpstrInitialDir	= NULL;
	ofn.Flags			= OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

	Bool result = (::GetSaveFileName( &ofn ) != false);

	ResetCurrentDirectory();

	return result;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB )
{
	COLORREF color = RGB(*pR,*pG,*pB);

	CHOOSECOLOR cc = {
		sizeof(CHOOSECOLOR),
		GetWindowHandle(),
		NULL,
		color,
		&color,
		CC_FULLOPEN | CC_RGBINIT,
	};

	if ( !::ChooseColor( &cc ) ) return false;

	*pR = (cc.rgbResult>>16) & 0xFF;
	*pG = (cc.rgbResult>> 8) & 0xFF;
	*pB = (cc.rgbResult>> 0) & 0xFF;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IGraphicCard *CCore::CreateGraphicCard( Uint32 GraphicCardNo, eVertexShaderVersion VsVer )
{
	if ( m_pGraphicCard == NULL )
	{
		m_pGraphicCard = new CGraphicCard;
		AddChild( m_pGraphicCard );

		if ( !m_pGraphicCard->Initialize( GraphicCardNo, VsVer ) )
		{
			SAFE_RELEASE( m_pGraphicCard );
			return NULL;
		}
	}
	else
	{
		m_pGraphicCard->AddRef();
	}

	return m_pGraphicCard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IMouse *CCore::GetMouse( void ) const
{
	m_pMouse->AddRef();
	return m_pMouse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IKeyboard *CCore::GetKeyboard( void ) const
{
	m_pKeyboard->AddRef();
	return m_pKeyboard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IFileManager *CCore::CreateFileMgr( void )
{
	return new CFileManager;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IFileManager *CCore::GetFileMgrPointer( void ) const
{
	return m_pFileManager;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetFileManager( IFileManager *pMgr )
{
	CFileManager *pNewMgr = dynamic_cast<CFileManager*>(pMgr);
	if ( pNewMgr != NULL )
	{
		SAFE_RELEASE( m_pFileManager );
		m_pFileManager = pNewMgr;
		m_pFileManager->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISound *CCore::CreateSoundFromFile( const wchar_t *pFileName, Bool IsGlobalScope )
{
	static NullSound Dummy;
	ISound *pSnd;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�T�E���h" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH] = L"";
	if ( !m_pFileManager->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"�t�@�C����������܂���" );
		pSnd = &Dummy;
	}
	else
	{
		Log_PrintLine( 0x000000, L"%s", FilePath );

		CSound *pData = new CSound( this );
		if ( !pData->CreateFromFile( pFileName, IsGlobalScope ) )
		{
			SAFE_RELEASE( pData );
			pSnd = &Dummy;
		}
		else
		{
			Log_PrintStrongLine( 0x008000, L"����" );
			pData->SetName( FilePath );
			pSnd = pData;
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSnd;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICore *CCore::CreateCore( void )
{
	return new CCore();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
LRESULT CALLBACK CCore::CommonMsgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	//======================================================================
	// ���b�Z�[�W����
	//======================================================================
	switch ( Msg )
	{
	//--------------------------------------------------------- �V�X�e���R�}���h
	case WM_SYSCOMMAND:
		// �X�N���[���Z�[�o�[�֌W�̏�����}��
		if ( wParam == SC_SCREENSAVE   ) return 0;
		if ( wParam == SC_MONITORPOWER ) return 0;
		break;

	//--------------------------------------------------------- �E�B���h�E��̎�
	case WM_DESTROY:
		// �I��
		::PostQuitMessage( 0 );
		break;
	}

	//======================================================================
	// �ΏۃR�A�ɓ]��
	//======================================================================
	CCore *pCore = (CCore*)::GetWindowLong( hWnd, GWL_USERDATA );
	if ( pCore != NULL )
	{
		// ���b�Z�[�W����
		pCore->Message( hWnd, Msg, wParam, lParam );
	}

	return ::DefWindowProc( hWnd, Msg, wParam, lParam );
}

