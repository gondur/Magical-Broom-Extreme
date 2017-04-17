
//==========================================================================
//
//
//		Application �t�@�C���֘A
//
//
//==========================================================================


//==========================================================================
// INCLUDE
//==========================================================================
#include <windows.h>
#include <stdio.h>
#include <shlobj.h>

#include "Resource.h"
#include "LagUtil.h"
#include "Lag.h"
#include "DirectDraw.h"


//==========================================================================
// DEFINE
//==========================================================================
#define AppName "LagUtility"


//==========================================================================
// GLOBAL
//==========================================================================
static char DataName[128];
static LAGPIXELFORMAT Format = LAGFMT_A8R8G8B8;


//==========================================================================
// PROTOTYPE
//==========================================================================
LRESULT CALLBACK WindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK DlgNameProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
bool InitWindow( HINSTANCE hInst );
bool SetWinCenter( HWND hWnd, long w, long h );
bool FileOpenDialog( HWND hWnd, char *path, char *title, long mode );
bool FileSaveDialog( HWND hWnd, char *path, char *title, long mode );
bool GetFolderPath( char *path );
bool BatchProcess( char *dir, HWND hWnd, long *num );
void ConvertName( char *file );
bool CheckAlphaName( char *file );
void ConvertAlphaName( char *file );
void SetFormat( LAGPIXELFORMAT fmt, HWND hWnd );
bool SaveBitmap32( char *file, long w, long h, long pitch, PIXELDATA32 *pData );


//==========================================================================
//
//
//		WinMain
//
//
//==========================================================================
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow )
{
	//===================================================
	// COM������
	//===================================================
	CoInitialize( NULL );

	//===================================================
	// �E�B���h�E������
	//===================================================
	if ( InitWindow( hInst ) == false ) return false;

	//===================================================
	// ���b�Z�[�W���[�v
	//===================================================
	MSG msg;
	while ( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	//===================================================
	// COM�J��
	//===================================================
	CoUninitialize();

	return msg.wParam;
}


//==========================================================================
//
//
//		�E�B���h�E������
//
//
//==========================================================================
bool InitWindow( HINSTANCE hInst )
{
	//=================================================
	// �E�B���h�E�N���X�o�^
	//=================================================
	WNDCLASS wc;
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc      = WindowProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInst;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( GRAY_BRUSH );
	wc.lpszMenuName		= "IDR_MENU";
	wc.lpszClassName	= AppName;
	
	if ( RegisterClass( &wc ) == NULL ) return false;

	//=================================================
	// �E�B���h�E����
	//=================================================
	HWND hWnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			AppName,
			AppName,
			WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInst,
			NULL
		);
	if ( hWnd == NULL ) return false;

	// �E�B���h�E��
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );

	return true;
}

//==========================================================================
//
//
//		���b�Z�[�W����
//
//
//==========================================================================
LRESULT CALLBACK WindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static const long BAR_DIV = 8;
	static long DrawX, DrawY;
	static long DispNoV, DispNoH;
	static long BarPosV, BarPosH;
	static SCROLLINFO ScrollInfoV, ScrollInfoH;

	switch ( msg )
	{
		//====================================================
		// ���j���[�R�}���h
		//====================================================
	case WM_COMMAND:
		{
			char path[512] = "";

			switch ( wParam )
			{
			/////////////////////////////////////////// �摜�t�@�C���I�[�v��
			case ID_OPENBMP:
				if ( FileOpenDialog( hWnd, path, "BMP�t�@�C��", 1 ) )
				{
					if ( LoadBMP( path, FMT_GRAPHIC ) )
					{
						long w, h;
						GetGraphicSize( &w, &h );
						SetWinCenter( hWnd, w, h );
						// �f�[�^���擾
						ConvertName( path );
						// �A���t�@�`�����l���f�[�^�����ǂݍ���
						ConvertAlphaName( path );
						if ( LoadBMP( path, FMT_ALPHA ) )
						{
						}
						DataName[15] = '\0';
						sprintf( path, "%s < %s >", AppName, DataName );
						SetWindowText( hWnd, path ); 
					}
				}
				break;
			/////////////////////////////////////////// �A���t�@�p�摜�t�@�C���I�[�v��
			case ID_OPENALPHA:
				if ( FileOpenDialog( hWnd, path, "�A���t�@�`�����l���pBMP�t�@�C��", 1 ) )
				{
					if ( LoadBMP( path, FMT_ALPHA ) )
					{
					}
				}
				break;
			/////////////////////////////////////////// LAG�t�@�C���V�K�ۑ�
			case ID_SAVE:
				{
					bool ret = false; 
					long w, h;
					GetGraphicSize( &w, &h );
					if ( w < 0 || h < 0 )
					{
						MsgBox( "Error", "�������ރf�[�^������܂���" );
					}
					else
					{
						if ( FileSaveDialog( hWnd, path, "LAG�t�@�C��", 0 ) )
						{
							// �w�b�_��������
							if ( SaveLAGHeader( path, 0 ) )
							{
								// �f�[�^�擾����������
								long pitch;
								PIXELDATA32 *pData = LockSurface( &pitch );
								if ( pData != NULL )
								{
									if ( SaveLAG( path, DataName, w, h, pitch, pData, Format, 0 ) )
									{
										ret = true;
									}
									UnlockSurface();
								}
							}

							if ( ret == false ) MsgBox( "Error", "LAG�t�@�C���̏������݂Ɏ��s" );
						}
					}
				}
				break;
			/////////////////////////////////////////// LAG�t�@�C���ǋL�ۑ�
			case ID_SAVEADD:
				{
					bool ret = false; 
					long w, h;
					GetGraphicSize( &w, &h );
					if ( w < 0 || h < 0 )
					{
						MsgBox( "Error", "�������ރf�[�^������܂���" );
					}
					else
					{
						if ( FileOpenDialog( hWnd, path, "LAG�t�@�C��", 0 ) )
						{
							// �f�[�^�擾����������
							long pitch;
							PIXELDATA32 *pData = LockSurface( &pitch );
							if ( pData != NULL )
							{
								if ( SaveLAG( path, DataName, w, h, pitch, pData, Format, 0 ) )
								{
									ret = true;
								}
								UnlockSurface();
							}

							if ( ret == false ) MsgBox( "Error", "LAG�t�@�C���̏������݂Ɏ��s" );
						}
					}
				}
				break;
			/////////////////////////////////////////// 32BitBMP�t�@�C���ǋL�ۑ�
			case ID_SAVE32BMP:
				{
					bool ret = false; 
					long w, h;
					GetGraphicSize( &w, &h );
					if ( w < 0 || h < 0 )
					{
						MsgBox( "Error", "�������ރf�[�^������܂���" );
					}
					else
					{
						if ( FileSaveDialog( hWnd, path, "32Bit�A���t�@�t��BMP�t�@�C��", 1 ) )
						{
							// �f�[�^�擾����������
							long pitch;
							PIXELDATA32 *pData = LockSurface( &pitch );
							if ( pData != NULL )
							{
								if ( SaveBitmap32( path, w, h, pitch, pData ) )
								{
									ret = true;
								}
								UnlockSurface();
							}

							if ( ret == false ) MsgBox( "Error", "BMP�t�@�C���̏������݂Ɏ��s" );
						}
					}
				}
				break;
			/////////////////////////////////////////// �J���[�L�[
			case ID_COLORKEY:
				RestoreColorKey();
				break;
			/////////////////////////////////////////// �o�b�`����
			case ID_BATCH:
				if ( GetFolderPath( path ) )
				{
					long num;
					if ( BatchProcess( path, hWnd, &num ) )
					{
						sprintf( path, "�o�b�`��������\n%d���̉摜���p�b�N�����܂���", num );
						MsgBox( "Information", path );
					}
				}
				break;
			/////////////////////////////////////////// ���E���]
			case IR_CHANGE_LR:
				GraphciLeftRight();
				break;
			/////////////////////////////////////////// �㉺���]
			case ID_CHANGE_UD:
				GraphciUpDown();
				break;
			/////////////////////////////////////////// �摜���]
			case ID_REVERSE:
				GraphciReverse();
			/////////////////////////////////////////// ARGB 16Bit�J���[
			case ID_PIXEL_A4R4G4B4:
				SetFormat( LAGFMT_A4R4G4B4, hWnd );
				break;
			/////////////////////////////////////////// ARGB 32Bit�J���[
			case ID_PIXEL_A8R8G8B8:
				SetFormat( LAGFMT_A8R8G8B8, hWnd );
				break;
			/////////////////////////////////////////// ARGB 64Bit�J���[
			case ID_PIXEL_A16R16G16B16:
				SetFormat( LAGFMT_A16R16G16B16, hWnd );
				break;
			/////////////////////////////////////////// ARGB float�^�J���[
			case ID_PIXEL_FLOAT:
				SetFormat( LAGFMT_FLOAT, hWnd );
				break;
			/////////////////////////////////////////// ���O�ύX
			case ID_RENAME:
				long w, h;
				GetGraphicSize( &w, &h );
				if ( w > 0 && h > 0 )
				{
					DialogBox( GetModuleHandle(NULL), "IDD_DLG_NAME", hWnd, (DLGPROC)DlgNameProc);
					sprintf( path, "%s < %s >", AppName, DataName );
					SetWindowText( hWnd, path );
				}
                break;
			/////////////////////////////////////////// �I��
			case ID_CLOSE:
				SendMessage( hWnd, WM_CLOSE, 0, 0 );
				break;
			}
		}
		break;
		//====================================================
		// �}�E�X�N���b�N��
		//====================================================
	case WM_LBUTTONDOWN:
		{
			long r, g, b;
			char str[256] = "";
			// �}�E�X�ʒu
			POINT pt;
			GetCursorPos( &pt );
			ScreenToClient( hWnd, &pt );
			// �摜�T�C�Y�`�F�b�N
			long w, h;
			GetGraphicSize( &w, &h );
			if ( 0 < pt.x && pt.x < w && 0 < pt.y && pt.y < h )
			{
				// �}�E�X�ʒu�̐F�擾
				GetColor( &r, &g, &b, pt.x, pt.y );
				sprintf( str, "RGB(%d,%d,%d)���J���[�L�[�ɂ��܂����H", r, g, b );
				if ( MessageBox( hWnd, str, "�J���[�L�[�t��", MB_YESNO | MB_ICONQUESTION ) == IDYES)
				{
					SetColorKey( r, g, b );
				}
			}
		}
		break;
		//====================================================
		// �E�B���h�E�X�V��
		//====================================================
	case WM_PAINT:
		{
			Refresh( hWnd, DrawX, DrawY );
		}
		break;
		//====================================================
		// �E�B���h�E������
		//====================================================
	case WM_CREATE:
		{
			if ( InitDirectX( hWnd ) == false )
			{
				PostMessage( hWnd, WM_CLOSE, 0, 0 );
			}
		}
		break;
		//====================================================
		// �E�B���h�E�j��
		//====================================================
	case WM_DESTROY:
		{
			UninitDirectX();
			// �I��
			PostQuitMessage( 0 );
		}
		break;
		//====================================================
		// �E�B���h�E�T�C�Y�ύX
		//====================================================
	case WM_SIZE:
		{
			RECT rect;
			GetClientRect( hWnd, &rect );
			DispNoV = (rect.bottom - rect.top) / BAR_DIV;
			DispNoH = (rect.right - rect.left) / BAR_DIV;

			long w, h;
			GetGraphicSize( &w, &h );

			long LineMaxV = w / BAR_DIV;
			long LineMaxH = h / BAR_DIV;

			ScrollInfoV.cbSize = sizeof(SCROLLINFO);
			ScrollInfoV.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;
			ScrollInfoV.nMin = 0;
			ScrollInfoV.nMax = LineMaxV;
			ScrollInfoV.nPage = DispNoV;
			ScrollInfoV.nPos = BarPosV;
			SetScrollInfo( hWnd, SB_VERT, &ScrollInfoV, TRUE );

			ScrollInfoH.cbSize = sizeof(SCROLLINFO);
			ScrollInfoH.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;
			ScrollInfoH.nMin = 0;
			ScrollInfoH.nMax = LineMaxH;
			ScrollInfoH.nPage = DispNoH;
			ScrollInfoH.nPos = BarPosH;

			SetScrollInfo( hWnd, SB_HORZ, &ScrollInfoH, TRUE );
		}
		break;
		//====================================================
		// �����X�N���[���o�[
		//====================================================
	case WM_VSCROLL:
		{
			long dy = 0;
			switch ( LOWORD(wParam) )
			{
			case SB_LINEUP:
				dy = -1;
				break;
			case SB_LINEDOWN:
				dy = +1;
				break;
			case SB_PAGEUP:
				dy = -(long)ScrollInfoV.nPage;
				break;
			case SB_PAGEDOWN:
				dy = +(long)ScrollInfoV.nPage;
				break;
			case SB_THUMBTRACK:
				dy = HIWORD(wParam) - ScrollInfoV.nPos;
				break;
			}
			dy = max( -1 * ScrollInfoV.nPos, min(dy, ScrollInfoV.nMax - ScrollInfoV.nPos) );
			ScrollInfoV.nPos += dy;
			DispNoV = ScrollInfoV.nPos;
			SetScrollInfo( hWnd, SB_VERT, &ScrollInfoV, TRUE );
			DrawY = -(long)(ScrollInfoV.nPos * BAR_DIV);
			InvalidateRect( hWnd, NULL, TRUE );
		}
		break;
		//====================================================
		// �����X�N���[���o�[
		//====================================================
	case WM_HSCROLL:
		{
			long dy = 0;
			switch ( LOWORD(wParam) )
			{
			case SB_LINEUP:
				dy = -1;
				break;
			case SB_LINEDOWN:
				dy = 1;
				break;
			case SB_PAGEUP:
				dy = -(long)ScrollInfoH.nPage;
				break;
			case SB_PAGEDOWN:
				dy = +(long)ScrollInfoH.nPage;
				break;
			case SB_THUMBTRACK:
				dy = HIWORD(wParam) - ScrollInfoH.nPos;
				break;
			}
			dy = max( -1 * ScrollInfoH.nPos, min(dy, ScrollInfoH.nMax - ScrollInfoH.nPos) );
			ScrollInfoH.nPos += dy ;
			DispNoH = ScrollInfoH.nPos;
			SetScrollInfo( hWnd, SB_HORZ, &ScrollInfoH, TRUE );
			DrawX = -(long)(ScrollInfoH.nPos * BAR_DIV);
			InvalidateRect( hWnd, NULL, TRUE );
		}
		break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

//==========================================================================
//
//
//		���O�ύX�_�C�A���O�p���b�Z�[�W�����֐�
//
//
//==========================================================================
LRESULT CALLBACK DlgNameProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	char path[256] = "";

	switch ( msg )
	{
	case WM_INITDIALOG:
		{
            SetDlgItemText( hWnd, IDC_EDIT_RENAME, (LPCTSTR)DataName );
		}
		break;
	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDOK:
                GetDlgItemText( hWnd, IDC_EDIT_RENAME, (LPTSTR)DataName, 128 );
				DataName[15] = '\0';
				EndDialog( hWnd, IDOK );
				return true;
			case IDCANCEL:
				EndDialog( hWnd, IDCANCEL );
				return true;
			}
		}
		break;
	}

	return false;
}

//==========================================================================
//
//
//		�E�B���h�E����ʒ����ɐݒ�
//
//
//==========================================================================
bool SetWinCenter( HWND hWnd, long w, long h )
{
	// �E�B���h�E�T�C�Y�`�F�b�N
	if ( w < 0 || h < 0 ) GetWindowSize( hWnd, &w, &h );

	if ( w < 128 ) w = 128;
	if ( h < 128 ) h = 128;

	// ���j���[��^�C�g���o�[���܂ރE�B���h�E�̃T�C�Y�擾
	long window_w = w + GetSystemMetrics(SM_CXEDGE) + GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXDLGFRAME);
	long window_h = h + GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);

	// ��ʂ̒����ɂ���悤�ɂ���
	long x = GetSystemMetrics(SM_CXSCREEN)/2 - window_w/2;
	long y = GetSystemMetrics(SM_CYSCREEN)/2 - window_h/2;

	// ���オ�͂ݏo���ꍇ (0,0) �ɂ���悤�ɂ���
	if ( x < 0 ) x = 0;
	if ( y < 0 ) y = 0;

	// �E�B���h�E�ʒu�X�V
	SetWindowPos(
			hWnd,
			HWND_TOP,
			x,
			y,
			window_w, window_h,
			SWP_SHOWWINDOW
		);

	return true;
}

//==========================================================================
//
//
//		�E�B���h�E�T�C�Y�擾
//
//
//==========================================================================
void GetWindowSize( HWND hWnd, long *w, long *h )
{
	RECT rect = { 0, 0, 0, 0 };
	GetClientRect( hWnd, &rect );

	if ( w != NULL ) *w = rect.right - rect.left;
	if ( h != NULL ) *h = rect.bottom - rect.top;
}

//==========================================================================
//
//
//		�t�@�C���I�[�v���t�@�C�A���O
//
//
//==========================================================================
bool FileOpenDialog( HWND hWnd, char *path, char *title, long mode )
{
	char temp[512] = "";

	OPENFILENAME ofn;
	ZeroMemory( &ofn, sizeof(OPENFILENAME) );
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrTitle = title;
	ofn.lpstrFilter = ((mode)?("BMP�t�@�C��(*.bmp)\0*.bmp\0"):("LAG�t�@�C��(*.lag)\0*.lag\0"));
	ofn.lpstrDefExt = ((mode)?("BMP"):("LAG"));
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = temp;
	ofn.nMaxFile = 512;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if ( GetOpenFileName( &ofn ) != 0 )
	{
		if ( strlen( temp ) > 0 )
		{
			strcpy( path, temp );
			return true;
		}
	}

	return false;
}

//==========================================================================
//
//
//		�t�@�C���Z�[�u�_�C�A���O
//
//
//==========================================================================
bool FileSaveDialog( HWND hWnd, char *path, char *title, long mode )
{
	char temp[512] = "";
	
	OPENFILENAME ofn;
	ZeroMemory( &ofn, sizeof(OPENFILENAME) );
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrTitle = title;
	ofn.lpstrFilter = ((mode)?("BMP�t�@�C��(*.bmp)\0*.bmp\0"):("LAG�t�@�C��(*.lag)\0*.lag\0"));
	ofn.lpstrDefExt = ((mode)?("BMP"):("LAG"));
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = temp;
	ofn.nMaxFile = 512;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

	if ( GetOpenFileName( &ofn ) != 0 )
	{
		if ( strlen( temp ) > 0 )
		{
			strcpy( path, temp );
			return true;
		}
	}

	return false;
}

//==========================================================================
//
//
//		�t�H���_�I��
//
//
//==========================================================================
bool GetFolderPath( char *path )
{
	//============================================
	// �t�H���_�I��
	//============================================
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	LPMALLOC pMalloc;
	bool result = false;

	if SUCCEEDED( SHGetMalloc( &pMalloc ) )
	{
		ZeroMemory( &bi, sizeof(BROWSEINFO) );

		bi.lpszTitle		= "�t�H���_�I��";
		bi.ulFlags			= BIF_RETURNONLYFSDIRS;

		pidl = SHBrowseForFolder( &bi );

		if ( pidl != NULL )
		{
			if ( SHGetPathFromIDList( pidl, path ) == TRUE )
			{
				result = true;
			}
			pMalloc->Free( pidl );
		}
		pMalloc->Release();
	}

	return result;
}

//==========================================================================
//
//
//		���O�ϊ�
//
//
//==========================================================================
void ConvertName( char *file )
{
	char temp[256];
	strcpy( temp, file );

	long num = -1;

	// �t�@�C���������ׂď�������
	num = 0;
	while ( temp[num] != '\0' )
	{
		if ( 'A' <= temp[num] && temp[num] <= 'Z' )
		{
			temp[num] += ('a' - 'A');
		}
		num++;
	}

	// ��΃p�X����t�@�C�������o��
	num = strlen( temp );
	while ( temp[num] != '\\' ) if ( --num < 0 ) break;
	char *p = temp + num + 1;

	// �g���q�폜
	num = strlen( p );
	while ( true )
	{
		char c = p[num];
		p[num] = '\0';
		num--;
		if ( c == '.' ) break;
	}

	// �f�[�^���N���A
	memset( DataName, 0x00, 128 );

	// �f�[�^���R�s�[
	strcpy( DataName, p );
}

//==========================================================================
//
//
//		���O�`�F�b�N
//
//
//==========================================================================
bool CheckAlphaName( char *file )
{
	char temp[256];
	strcpy( temp, file );

	long num = -1;

	// �g���q�폜
	num = strlen( temp );
	while ( true )
	{
		char c = temp[num];
		temp[num] = '\0';
		num--;
		if ( c == '.' ) break;
	}

	// �A���t�@�p�t�@�C�����`�F�b�N
	num = strlen( temp );

	return ( temp[num-2] == '_' && (temp[num-1] == 'a' || temp[num-1] == 'A') );
}

//==========================================================================
//
//
//		�A���t�@�`�����l�����ɕύX
//
//
//==========================================================================
void ConvertAlphaName( char *file )
{
	long num = -1;
	char flt[16] = "";

	// �g���q�ۑ�
	num = strlen( file );
	while ( true )
	{
		if ( file[num--] == '.' ) break;
	}
	strcpy( flt, &file[num+1] );
	file[num+1] = '\0';

	// �A���t�@���t��
	strcat( file, "_a" );
	strcat( file, flt );
}


//==========================================================================
//
//
//		�o�b�`����
//
//
//==========================================================================
bool BatchProcess( char *dir, HWND hWnd, long *num )
{
	WIN32_FIND_DATA FindData;
	char SavePath[256] = "";
	char FilePath[256] = "";

	//====================================================
	// �t�@�C���̃��C���h�J�[�h�ݒ�
	//====================================================
	sprintf( FilePath, "%s\\*.bmp", dir );

	//====================================================
	// ��ڂ̃t�@�C��
	//====================================================
	HANDLE hFile = FindFirstFile( FilePath, &FindData );
	if ( hFile == INVALID_HANDLE_VALUE ) return false;

	//====================================================
	// �������݃t�@�C���p�_�C�A���O
	//====================================================
	if ( FileSaveDialog( hWnd, SavePath, "LAG�t�@�C���ۑ�", 0 ) == false ) return false;

	//====================================================
	// �t�@�C���w�b�_��������
	//====================================================
	if ( SaveLAGHeader( SavePath, 0 ) == false ) return false;

	//====================================================
	// �t�@�C����
	//====================================================
	(*num) = 0;
	while ( true )
	{
		char *p = FindData.cFileName;
		if ( p[1] != ':' )
		{
			char temp[256] = "";
			sprintf( temp, "%s\\%s", dir, p );
			p = temp;
		}
		// �A���t�@�`�����l���p�t�@�C�����`�F�b�N
		if ( !CheckAlphaName( p ) )
		{
			(*num)++;
			// �摜�ǂݍ���
			if ( LoadBMP( p, FMT_GRAPHIC ) )
			{
				long w, h;
				GetGraphicSize( &w, &h );
				SetWinCenter( hWnd, w, h );
				// �f�[�^���擾
				ConvertName( p );
				// �A���t�@�`�����l���f�[�^�����ǂݍ���
				ConvertAlphaName( p );
				LoadBMP( p, FMT_ALPHA );
				// �f�[�^�擾����������
				long pitch;
				PIXELDATA32 *pData = LockSurface( &pitch );
				if ( pData != NULL )
				{
					if ( SaveLAG( SavePath, DataName, w, h, pitch, pData, Format, 0 ) == false )
					{
						MsgBox( "Error", "�f�[�^�������݂Ɏ��s" );
						UnlockSurface();
						return false;
					}
					UnlockSurface();
				}
			}
		}
		// ���̃t�@�C��
		if ( FindNextFile( hFile, &FindData ) == FALSE ) break;
	}

	return true;
}

//==========================================================================
//
//
//		�s�N�Z���t�H�[�}�b�g�ݒ�
//
//
//==========================================================================
void SetFormat( LAGPIXELFORMAT fmt, HWND hWnd )
{
	long no = -1;

	switch ( fmt )
	{
	case LAGFMT_A4R4G4B4:
		no = 0;
		break;
	case LAGFMT_A8R8G8B8:
		no = 1;
		break;
	case LAGFMT_A16R16G16B16:
		no = 2;
		break;
	case LAGFMT_FLOAT:
		no = 3;
		break;
	}

	const long id[] = { ID_PIXEL_A4R4G4B4, ID_PIXEL_A8R8G8B8, ID_PIXEL_A16R16G16B16, ID_PIXEL_FLOAT };

	MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
	mii.fMask = MIIM_STATE;

	for ( int i = 0; i < 4; i++ )
	{
		mii.fState = MFS_UNCHECKED;
		SetMenuItemInfo( GetMenu( hWnd ), id[i], false, &mii );
	}

	mii.fState = MFS_CHECKED;
	SetMenuItemInfo( GetMenu( hWnd ), id[no], false, &mii );

	Format = fmt;
}


//==========================================================================
//
//
//		32Bit Bitmap �t�@�C���ۑ�
//
//
//==========================================================================
bool SaveBitmap32( char *file, long w, long h, long pitch, PIXELDATA32 *pData )
{
	//================================================
	// �r�b�g�}�b�v�\���̊m��
	//================================================
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpih;

	bmpfh.bfType			= ('B' << 0) | ('M' << 8);
	bmpfh.bfSize			= (w*h*4) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpfh.bfReserved1		= 0;
	bmpfh.bfReserved2		= 0;
	bmpfh.bfOffBits			= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmpih.biSize			= sizeof(BITMAPINFOHEADER);
	bmpih.biWidth			= w;
	bmpih.biHeight			= h;
	bmpih.biPlanes			= 1;
	bmpih.biBitCount		= 32;
	bmpih.biCompression		= 0;
	bmpih.biSizeImage		= 0;
	bmpih.biXPelsPerMeter	= 0;
	bmpih.biYPelsPerMeter	= 0;
	bmpih.biClrUsed			= 0;
	bmpih.biClrImportant	= 0;

	//================================================
	// �f�[�^�����o��
	//================================================
	FILE *fp = fopen( file, "wb" );
	if ( fp == NULL ) return false;

	// �w�b�_
	fwrite( &bmpfh, sizeof(BITMAPFILEHEADER), 1, fp );
	fwrite( &bmpih, sizeof(BITMAPINFOHEADER), 1, fp );

	// �f�[�^;
	pData += (h-1) * pitch;
	for ( int y = 0; y < h; y++ )
	{
		for ( long x = 0; x < w; x++ )
		{
			fwrite( &pData[x], sizeof(PIXELDATA32), 1, fp );
		}
		pData -= pitch;
	}

	return true;
}