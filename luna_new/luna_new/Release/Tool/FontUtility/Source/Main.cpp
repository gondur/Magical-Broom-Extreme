

//==========================================================================
// INCLUDE
//==========================================================================
#include "../resource.h"
#include "Surface.h"
#include "StrBuffer.h"
#include "Font.h"
#include "DirectX.h"

#include <process.h>


//==========================================================================
// DEFINE
//==========================================================================
#define PRODUCT_VERSION						"1.1.0"
#define CHARA_CODE_MAX						(65536)
#define FONT_MAX							(65536)
#define SHEET_MAX							(256)
#define LINE_MAX							(4096)


//==========================================================================
// STRUCT
//==========================================================================
struct SHEETDATA
{
	long LineCount;
	long LineWidth[LINE_MAX];
	long LineUseHeight;
	CSurface Texture;
};

struct FONTUVDATA
{
	char SheetNo;
	char abcA;
	char abcB;
	char abcC;
	short x1;
	short y1;
	short x2;
	short y2;
};

struct LFDHEADER
{
	char Guid[4];								///< �t�@�C�����ʏ��i��� 'L' 'F' 'D' '\0'
	unsigned char FontSize;						///< �t�H���g�T�C�Y
	unsigned char SheetMax;						///< �V�[�g�ő吔
	unsigned short SheetWidth;					///< �V�[�g����
	unsigned short SheetHeight;					///< �V�[�g�c��
	unsigned short FontMax;						///< �t�H���g�ő吔
	unsigned short IndexTbl[CHARA_CODE_MAX];	///< �C���f�b�N�X�e�[�u��
};


//==========================================================================
// PROTOTYPE
//==========================================================================
LRESULT CALLBACK ProgressProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
static LRESULT CALLBACK DlgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
static int CALLBACK EnumFontFamExProc( LOGFONT* Lf, LPNEWTEXTMETRIC* Tm, DWORD Type, LPARAM Data );
static BOOL FileOpenDialog( char *pPath, HWND hWnd, char *pTitle, char *pFilter, char *pExt );
static BOOL FileSaveDialog( char *pPath, HWND hWnd, char *pTitle, char *pFilter, char *pExt );
static void UpdatePreview( HWND hWnd );
static void RefreshWindow( HWND hWnd );
static void CreateFontTexture( HWND hWnd );
static void DrawBox( HDC hdc, long x1, long y1, long x2, long y2, COLORREF Color );
static void OpenColorDialog( HWND hWnd, COLORREF *pColor );
static void AnalyzeBatch( int nArgc, char* pArgv[] );
static void BatchMode( void );
static void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//==========================================================================
// VARIABLE
//==========================================================================
static char szFontList[FONT_MAX][64];
static long FontCount;
static long SheetCount;
static CSurface PreviewSurf;
static FONTUVDATA *pFontUV;
static SHEETDATA *pSheet;
static HINSTANCE hInstance;

static FONTDATA FontData;

static long TexWidthNo		= 1;
static long TexHeightNo		= 1;
static long TexExtNo		= 2;

static char FolderPath[_MAX_PATH]	= "";
static char FileText[_MAX_PATH]	= "";
static char FileName[_MAX_PATH]	= "font";


//==========================================================================
// CONST
//==========================================================================
static const long TexSizeTbl[] = { 128, 256, 512, 1024, 2048 };


//==========================================================================
// CONSTANT
//==========================================================================
static const long BevelTbl[] = { 7, 9, 1, 3, 8, 2, 4, 6 };


//==========================================================================
//
//		WinMain
//
//==========================================================================
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow )
{
	hInstance = hInst;

	// �f�t�H���g�ݒ�
	ZeroMemory(&FontData, sizeof(FontData));
	strcpy(FontData.Face, "�l�r �S�V�b�N");
	FontData.FontSize = 26;
	FontData.FontColor = 0xFFFFFFFF;
	FontData.SamplingCount = 1;
	FontData.fAspectX = 1.0f;
	FontData.fAspectY = 1.0f;

	// �o�b�t�@�m��
	pSheet = (SHEETDATA*)SAFE_ALLOC( sizeof(SHEETDATA[SHEET_MAX]) );
	pFontUV = (FONTUVDATA*)SAFE_ALLOC( sizeof(FONTUVDATA[FONT_MAX]) );

	if ( __argc > 1 )
	{
		BatchMode();
	}
	else
	{
		// �_�C�A���O�{�b�N�X�I�[�v��
		::DialogBox( hInst, "IDD_DIALOG_MAIN", NULL, (DLGPROC)DlgProc );
	}

	// �o�b�t�@���
	SAFE_FREE( pSheet );
	SAFE_FREE( pFontUV );

	return 0L;
}


//==========================================================================
//
//		���b�Z�[�W�֐�
//
//==========================================================================
LRESULT CALLBACK DlgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	char StrBuff[256] = "";
	RECT Rect;
	LOGFONT lf;
	HDC hdc;
	long i;

	switch ( msg )
	{
	//------------------------------------------------------ �_�C�A���O��������
	case WM_INITDIALOG:
		{
			// DirectDraw������
			if ( !DxInitialize( ::GetDlgItem(hWnd, IDC_PICTURE) ) )
			{
				::EndDialog( hWnd, IDCANCEL );
				break;
			}
			// �v���r���[�p�T�[�t�F�C�X
			::GetWindowRect( ::GetDlgItem(hWnd, IDC_PICTURE), &Rect );
			PreviewSurf.Create( Rect.right-Rect.left, Rect.bottom-Rect.top );
			// �t�H���g����
			FontCount = 0;
			ZeroMemory( &lf, sizeof(LOGFONT) );
			lf.lfCharSet = SHIFTJIS_CHARSET;
			hdc = GetDC( hWnd );
			EnumFontFamiliesEx( hdc, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)NULL, 0 );
			ReleaseDC( hWnd, hdc );
			// �E�B���h�E����ʒ�����
			::SetWindowText( hWnd, "�t�H���g���[�e�B���e�B Version "PRODUCT_VERSION );
			::GetWindowRect( hWnd, &Rect );
			::SetWindowPos(
					hWnd,
					HWND_TOP,
					(GetSystemMetrics(SM_CXSCREEN)-(Rect.right-Rect.left))/2,
					(GetSystemMetrics(SM_CYSCREEN)-(Rect.bottom-Rect.top))/2,
					(Rect.right-Rect.left),
					(Rect.bottom-Rect.top),
					SWP_SHOWWINDOW );
			// �f�[�^��
			::SetDlgItemText( hWnd, IDC_EDIT_DATANAME, (LPCTSTR)FileName );
			// �t�H���g�T�C�Y
			sprintf( StrBuff, "%d", FontData.FontSize );
			::SetDlgItemText( hWnd, IDC_EDIT_FONTSIZE, (LPCTSTR)StrBuff );
			// �T���v�����O��
			sprintf( StrBuff, "%d", FontData.SamplingCount );
			::SetDlgItemText( hWnd, IDC_EDIT_SAMPLING, (LPCTSTR)StrBuff );
			// �A�X�y�N�g��
			sprintf( StrBuff, "%.2lf", FontData.fAspectX );
			::SetDlgItemText( hWnd, IDC_EDIT_ASPECT_X, (LPCTSTR)StrBuff );
			sprintf( StrBuff, "%.2lf", FontData.fAspectY );
			::SetDlgItemText( hWnd, IDC_EDIT_ASPECT_Y, (LPCTSTR)StrBuff );
			// ���T�C�Y
			sprintf( StrBuff, "%d", FontData.EdgeSize );
			::SetDlgItemText( hWnd, IDC_EDIT_EDGESIZE, (LPCTSTR)StrBuff );
			// �V���h�E�T�C�Y
			sprintf( StrBuff, "%d", FontData.BevelSize );
			::SetDlgItemText( hWnd, IDC_EDIT_BEVELSIZE, (LPCTSTR)StrBuff );
			// �t�H���g�t�F�[�X
			for ( i = 0; i < FontCount; i++ )
			{
				::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_INSERTSTRING, i, (LPARAM)szFontList[i] );
			}
			// �f�t�H���g�̃t�H���g�́h�l�r �S�V�b�N�h
			for ( i = 0; i < FontCount; i++ )
			{
				if ( !strcmp( "�l�r �S�V�b�N", szFontList[i] ) )
				{
					::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_SETCURSEL, i, 0L );
				}
			}
			// �V���h�E����
			for ( i = 0; i < 8; i++ )
			{
				char *pStr[] = { "����", "�E��", "����", "�E��", "��", "��", "��", "�E" };
				::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
			}
			::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_SETCURSEL, 0, 0L );
			FontData.BevelDir = BevelTbl[FontData.BevelDir];
			// �e�N�X�`���T�C�Y
			for ( i = 0; i < 5; i++ )
			{
				char *pStr[] = { "128", "256", "512", "1024", "2048" };
				::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
				::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
			}
			::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_SETCURSEL, TexWidthNo, 0L );
			::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_SETCURSEL, TexHeightNo, 0L );
			// �g���q
			for ( i = 0; i < 3; i++ )
			{
				char *pStr[] = { "bmp(4bit)", "bmp(8bit)", "tga(32bit)" };
				::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_EXT, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
			}
			::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_EXT, CB_SETCURSEL, TexExtNo, 0L );

			// ��ʍX�V
			UpdatePreview( hWnd );
		}
		return FALSE;

	//------------------------------------------------------ �R�}���h������
	case WM_COMMAND:
		switch ( LOWORD( wParam ) )
		{
		//----------------------------- �t�H���g�쐬
		case ID_CREATE:
			{
				if ( FileName[0] == '\0' )
				{
					::MessageBox( hWnd, "�f�[�^�������͂���Ă��܂���", "Error", MB_ICONERROR );
				}
				else
				if ( strlen( FileName ) >= 16 )
				{
					::MessageBox( hWnd, "�f�[�^�����������܂�\n���p16�����܂łł�", "Error", MB_ICONERROR );
				}
				else
				if ( FileText[0] == '\0' )
				{
					::MessageBox( hWnd, "���̓t�@�C�������w�肳��Ă��܂���", "Error", MB_ICONERROR );
				}
				else
				{
					// ����
					::DialogBox(
							hInstance,
							"IDD_DIALOG_PROGRESS",
							hWnd,
							(DLGPROC)ProgressProc );
				}
			}
			return TRUE;

		//----------------------------- �o�b�`�ۑ�
		case ID_SAVE_BATCH:
			if ( FileSaveDialog( StrBuff, hWnd, "�o�b�`�t�@�C���ۑ�", "BAT�t�@�C��(*.bat)\0*.bat\0", "BAT" ) )
			{
				FILE *fp = fopen( StrBuff, "wt" );
				if ( fp != NULL )
				{
					char File[256] = "";
					long len = (long)strlen( FileText );
					while ( FileText[len] != '\\' ) if ( --len < 0 ) break;
					strcpy( File, &FileText[len+1] );
					fprintf( fp, "FontUtility %s ", File );

					fprintf( fp, "/out,\"%s\" ", FileName );

					fprintf( fp, "/format,%d ", TexExtNo );

					fprintf( fp, "/width,%d /height,%d ", TexWidthNo, TexHeightNo );

					fprintf( fp, "/sample,%d ", FontData.SamplingCount );

					fprintf( fp, "/aspect,%.1lf,%.1lf ", FontData.fAspectX, FontData.fAspectY );

					fprintf( fp, "/face,\"%s\" /size,%d ", FontData.Face, FontData.FontSize );

					fprintf( fp, "/color,%d,%d,%d ", (FontData.FontColor>>0)&0xFF, (FontData.FontColor>>8)&0xFF, (FontData.FontColor>>16)&0xFF );

					if ( FontData.IsEdge )
						fprintf( fp, "/edge,%d,%d,%d,%d ", FontData.EdgeSize, (FontData.EdgeColor>>0)&0xFF, (FontData.EdgeColor>>8)&0xFF, (FontData.EdgeColor>>16)&0xFF );

					if ( FontData.IsBevel )
						fprintf( fp, "/bevel,%d,%d,%d,%d,%d ", FontData.BevelSize, FontData.BevelDir, (FontData.BevelColor>>0)&0xFF, (FontData.BevelColor>>8)&0xFF, (FontData.BevelColor>>16)&0xFF );

					if ( FontData.IsBold )
						fprintf( fp, "/bold " );

					if ( FontData.IsItalic )
						fprintf( fp, "/italic " );

					if ( FontData.IsFixPitch )
						fprintf( fp, "/fixpitch " );

					fclose( fp );
				}
			}
			return TRUE;

		//----------------------------- �o�b�`�Ǎ�
		case ID_LOAD_BATCH:
			if ( FileOpenDialog( StrBuff, hWnd, "�o�b�`�t�@�C���Ǎ�", "BAT�t�@�C��(*.bat)\0*.bat\0", "BAT" ) )
			{
				FILE *fp = fopen( StrBuff, "rt" );
				if ( fp != NULL )
				{
					char	 szData[2048];
					char	 szBuff[2048];
					int		nArgc = 0;
					char*	pArgv[256];
					char*	pText  = szData;
					char*	pWrite = szBuff;
					int		iSkip = 0;

					ZeroMemory(szData, sizeof(szData));
					ZeroMemory(szBuff, sizeof(szBuff));
					if (fread(szData, 1, 2047, fp) > 0) {
						ZeroMemory(&FontData, sizeof(FontData));

						pArgv[0] = pWrite;
						while(*pText != '\0')
						{
							if (iSkip == 0)
							{
								if (*pText == '\"')
								{
									iSkip = 1;
									pText++;
									continue;
								}
								else if (*pText == ' ')
								{
									*pWrite++ = '\0';
									nArgc++;
									if (nArgc < 255)
									{
										pArgv[nArgc] = pWrite;
									}
									pText++;
									continue;
								}
							}
							else
							{
								if (*pText == '\"')
								{
									iSkip = 0;
									pText++;
									continue;
								}
							}
							*pWrite++ = *pText++;
						}
						AnalyzeBatch( nArgc, pArgv );

						// �R���o�[�g�t�@�C���p�X
						::SetDlgItemText( hWnd, IDC_EDIT_FILE_TEXT, (LPCTSTR)FileText );
						// �o�̓f�[�^��
						::SetDlgItemText( hWnd, IDC_EDIT_DATANAME, (LPCTSTR)FileName );

						// ����
						for ( i = 0; i < FontCount; i++ )
						{
							if ( !strcmp( FontData.Face, szFontList[i] ) )
							{
								::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_SETCURSEL, i, 0L );
							}
						}
						// �t�H���g�T�C�Y
						sprintf( StrBuff, "%d", FontData.FontSize );
						::SetDlgItemText( hWnd, IDC_EDIT_FONTSIZE, (LPCTSTR)StrBuff );

						// �T���v�����O��
						sprintf( StrBuff, "%d", FontData.SamplingCount );
						::SetDlgItemText( hWnd, IDC_EDIT_SAMPLING, (LPCTSTR)StrBuff );
						// �A�X�y�N�g��
						sprintf( StrBuff, "%.1lf", FontData.fAspectX );
						::SetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_X), StrBuff );
						sprintf( StrBuff, "%.1lf", FontData.fAspectY );
						::SetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_Y), StrBuff );
						// ���T�C�Y
						sprintf( StrBuff, "%d", FontData.EdgeSize );
						::SetDlgItemText( hWnd, IDC_EDIT_EDGESIZE, (LPCTSTR)StrBuff );
						::SendDlgItemMessage( hWnd, IDC_CHECK_EDGE, BM_SETCHECK, FontData.IsEdge, 0L );
						// ����
						::SendDlgItemMessage( hWnd, IDC_CHECK_BOLD, BM_SETCHECK, FontData.IsBold, 0L );
						// �Α�
						::SendDlgItemMessage( hWnd, IDC_CHECK_ITALIC, BM_SETCHECK, FontData.IsItalic, 0L );
						// �V���h�E�T�C�Y
						sprintf( StrBuff, "%d", FontData.BevelSize );
						::SetDlgItemText( hWnd, IDC_EDIT_BEVELSIZE, (LPCTSTR)StrBuff );
						for(int i = 0; i < (sizeof(BevelTbl) / sizeof(long)); i++) {
							if (BevelTbl[i] == FontData.BevelDir)
							{
								::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_SETCURSEL, i, 0L );
							}
						}
						::SendDlgItemMessage( hWnd, IDC_CHECK_BEVEL, BM_SETCHECK, FontData.IsBevel, 0L );
						// �e�N�X�`���T�C�Y
						::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_SETCURSEL, TexWidthNo, 0L );
						::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_SETCURSEL, TexHeightNo, 0L );
						// �g���q
						::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_EXT, CB_SETCURSEL, TexExtNo, 0L );
						// �s�b�`�Œ�
						::SendDlgItemMessage( hWnd, IDC_CHECK_FIXPITCH, BM_SETCHECK, FontData.IsFixPitch, 0L );

						// ��ʍX�V
						UpdatePreview( hWnd );
					}
					fclose( fp );
				}
			}
			return TRUE;

		//----------------------------- �t�@�C���I��
		case IDC_FILE_SELECT_TEXT:
			if ( FileOpenDialog( StrBuff, hWnd, "�e�L�X�g�t�@�C���ǂݍ���", "TEXT�t�@�C��(*.txt)\0*.txt\0", "TXT" ) )
			{
				strcpy( FileText, StrBuff );
				::SetDlgItemText( hWnd, IDC_EDIT_FILE_TEXT, (LPCTSTR)FileText );
			}
			return TRUE;

		//----------------------------- �t�@�C����
		case IDC_EDIT_FILE_TEXT:
			::GetDlgItemText( hWnd, IDC_EDIT_FILE_TEXT, FileText, sizeof(FileText) );
			return TRUE;

		//----------------------------- �f�[�^��
		case IDC_EDIT_DATANAME:
			::GetDlgItemText( hWnd, IDC_EDIT_DATANAME, FileName, sizeof(FileName) );
			break;

		//----------------------------- �t�H���g�t�F�[�X
		case IDC_COMBO_FONTFACE:
			i = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_GETCURSEL, 0L, 0L );
			strcpy( FontData.Face, szFontList[i] );
			return TRUE;

		//----------------------------- �t�H���g�T�C�Y
		case IDC_EDIT_FONTSIZE:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_FONTSIZE), StrBuff, sizeof(StrBuff) );
			FontData.FontSize = atoi( StrBuff );
			return TRUE;

		//----------------------------- �t�H���g�F
		case IDC_COLOR_FONT:
			OpenColorDialog( hWnd, &FontData.FontColor );
			return TRUE;

		//----------------------------- �T���v�����O��
		case IDC_EDIT_SAMPLING:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_SAMPLING), StrBuff, 256 );
			FontData.SamplingCount = atoi( StrBuff );
			if ( FontData.SamplingCount < 1 )
			{
				FontData.SamplingCount = 1;
				sprintf( StrBuff, "%d", FontData.SamplingCount );
				::SetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_SAMPLING), StrBuff );
			}
			return TRUE;

		//----------------------------- �A�X�y�N�g��
		case IDC_EDIT_ASPECT_X:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_X), StrBuff, 256 );
			FontData.fAspectX = (float)atof( StrBuff );
			return TRUE;

		//----------------------------- �A�X�y�N�g��
		case IDC_EDIT_ASPECT_Y:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_Y), StrBuff, 256 );
			FontData.fAspectY = (float)atof( StrBuff );
			return TRUE;

		//----------------------------- �Α̃`�F�b�N
		case IDC_CHECK_ITALIC:
			FontData.IsItalic = (::IsDlgButtonChecked(hWnd, IDC_CHECK_ITALIC) == BST_CHECKED);
			return TRUE;

		//----------------------------- �����`�F�b�N
		case IDC_CHECK_BOLD:
			FontData.IsBold = (::IsDlgButtonChecked(hWnd, IDC_CHECK_BOLD) == BST_CHECKED);
			return TRUE;

		//----------------------------- ���`�F�b�N
		case IDC_CHECK_EDGE:
			FontData.IsEdge = (::IsDlgButtonChecked(hWnd, IDC_CHECK_EDGE) == BST_CHECKED);
			return TRUE;

		//----------------------------- ���T�C�Y
		case IDC_EDIT_EDGESIZE:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_EDGESIZE), StrBuff, sizeof(StrBuff) );
			FontData.EdgeSize = atoi( StrBuff );
			return TRUE;

		//----------------------------- ���F
		case IDC_COLOR_EDGE:
			OpenColorDialog( hWnd, &FontData.EdgeColor );
			return TRUE;

		//----------------------------- �����o���`�F�b�N
		case IDC_CHECK_BEVEL:
			FontData.IsBevel = (::IsDlgButtonChecked(hWnd, IDC_CHECK_BEVEL) == BST_CHECKED);
			return TRUE;

		//----------------------------- �����o������
		case IDC_COMBO_BEVELDIR:
			FontData.BevelDir = (long)(DWORD)::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_GETCURSEL, 0L, 0L );
			FontData.BevelDir = BevelTbl[FontData.BevelDir];
			return TRUE;

		//----------------------------- �����o���T�C�Y
		case IDC_EDIT_BEVELSIZE:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_BEVELSIZE), StrBuff, sizeof(StrBuff) );
			FontData.BevelSize = atoi( StrBuff );
			return TRUE;

		//----------------------------- �����o���F
		case IDC_COLOR_BEVEL:
			OpenColorDialog( hWnd, &FontData.BevelColor );
			return TRUE;

		//----------------------------- �e�N�X�`������
		case IDC_COMBO_TEX_W:
			TexWidthNo = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_GETCURSEL, 0L, 0L );
			return TRUE;

		//----------------------------- �e�N�X�`���c��
		case IDC_COMBO_TEX_H:
			TexHeightNo = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_GETCURSEL, 0L, 0L );
			return TRUE;

		//----------------------------- �e�N�X�`���g���q
		case IDC_COMBO_EXT:
			TexExtNo = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_EXT, CB_GETCURSEL, 0L, 0L );
			return TRUE;

		//----------------------------- �s�b�`�Œ�`�F�b�N
		case IDC_CHECK_FIXPITCH:
			FontData.IsFixPitch = (::IsDlgButtonChecked(hWnd, IDC_CHECK_FIXPITCH) == BST_CHECKED);
			return TRUE;

		//----------------------------- �v���r���[�E�B���h�E�X�V
		case IDC_PREVIEW:
			UpdatePreview( hWnd );
			return TRUE;
		}
		return TRUE;

	//------------------------------------------------------ �_�C�A���O�I����
	case WM_CLOSE:
		PreviewSurf.Release();
		DxFinalize();
		::EndDialog( hWnd, IDCANCEL );
		return TRUE;

	//------------------------------------------------------ �E�B���h�E�ĕ`��
	case WM_PAINT:
		RefreshWindow( hWnd );
		return FALSE;
	}

	return FALSE;
}

//==========================================================================
//
//			�t�H���g����
//
//==========================================================================
int CALLBACK EnumFontFamExProc( LOGFONT* Lf, LPNEWTEXTMETRIC* Tm, DWORD Type, LPARAM Data )
{
	// ������
	if ( FontCount == FONT_MAX ) return 0;

	// �c�����s�v
	if ( Lf->lfFaceName[0] == '@' ) return 1;

	// �t�H���g���̎擾
	strcpy( szFontList[FontCount++], Lf->lfFaceName );

	return 1;
}


//==========================================================================
//
//			�t�H���_�I���_�C�A���O
//
//==========================================================================
BOOL FolderSelect( char *pDir, HWND hWnd )
{
	pDir[0] = '\0';

    HRESULT hr;
    BROWSEINFO bi;
    ITEMIDLIST *lpid = NULL;
    LPMALLOC pMalloc = NULL;

	ZeroMemory( &bi, sizeof(BROWSEINFO) );

	bi.hwndOwner	= hWnd;;
	bi.ulFlags		= BIF_EDITBOX;
	bi.lpszTitle	= "�f�B���N�g���w��";

	lpid = ::SHBrowseForFolder( &bi );

	if ( lpid == NULL )
	{
		return FALSE;
	}
	else
	{
		hr = ::SHGetMalloc( &pMalloc );
		if ( hr == E_FAIL ) return FALSE;

		::SHGetPathFromIDList( lpid, pDir );
		if ( pDir[strlen(pDir) - 1] == '\\' ) pDir[strlen(pDir) - 1] = '\0';

		pMalloc->Free( lpid );
		pMalloc->Release();
	}

	return TRUE;
}

//==========================================================================
//
//		�t�@�C���I�[�v���t�@�C�A���O
//
//==========================================================================
BOOL FileOpenDialog( char *pPath, HWND hWnd, char *pTitle, char *pFilter, char *pExt )
{
	pPath[0] = '\0';

	//=======================================================
	// �t�@�C���I�[�v��
	//=======================================================
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };

	ofn.hwndOwner		= hWnd;
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= 256;
	ofn.lpstrDefExt		= pExt;
	ofn.lpstrInitialDir	= NULL;
	ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	return ::GetOpenFileName( &ofn ) != FALSE;
}

//==========================================================================
//
//		�t�@�C���I�[�v���t�@�C�A���O
//
//==========================================================================
BOOL FileSaveDialog( char *pPath, HWND hWnd, char *pTitle, char *pFilter, char *pExt )
{
	pPath[0] = '\0';

	//=======================================================
	// �t�@�C���I�[�v��
	//=======================================================
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };

	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= hWnd;
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= 256;
	ofn.lpstrDefExt		= pExt;
	ofn.lpstrInitialDir	= NULL;
	ofn.Flags			= OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

	return ::GetSaveFileName( &ofn ) != FALSE;
}

//==========================================================================
//
//			�v���r���[�E�B���h�E�X�V
//
//==========================================================================
void UpdatePreview( HWND hWnd )
{
	CSurface TempSurf;

	// �T�[�t�F�C�X�Ƀt�H���g�`��
	DrawFont( hWnd, &TempSurf, &FontData, "��" );
	FilterAntialias( &TempSurf, &FontData );

	// �v���r���[��ʂɕ\��
	long src_w = TempSurf.GetWidth();
	long src_h = TempSurf.GetHeight();
	long dst_w = PreviewSurf.GetWidth();
	long dst_h = PreviewSurf.GetHeight();

	long x = (dst_w - src_w) / 2;
	long y = (dst_h - src_h) / 2;

	PreviewSurf.Clear();
	PreviewSurf.DirectDraw( x, y, &TempSurf, 0, 0, src_w, src_h );
	DxUpdateBackBuffer( &PreviewSurf );

	TempSurf.Release();

	// �E�B���h�E�X�V
	RefreshWindow( hWnd );
}

//==========================================================================
//
//			�v���r���[�E�B���h�E�X�V
//
//==========================================================================
void RefreshWindow( HWND hWnd )
{
	HWND hDstWnd = ::GetDlgItem(hWnd, IDC_PICTURE);

	DxRefreshBackBuffer( hDstWnd );

	// ��ʍX�V
	::InvalidateRect( hDstWnd, NULL, FALSE );
}

//==========================================================================
//
//			�e�N�X�`���쐬
//
//==========================================================================
void CreateFontTexture( HWND hWnd )
{
	long i, j;
	RECT Rect;
	HANDLE hFile;
	char Temp[256]	= "";
	char File[256]	= "";
	long WinWidth	= -1;
	long WinHeight	= -1;
	LFDHEADER Lfd	= { "LFD" };
	unsigned short Index = 0;

	::GetClientRect( hWnd, &Rect );
	WinWidth  = Rect.right - Rect.left;
	WinHeight = Rect.bottom - Rect.top;

	//------------------------------------------------------------
	// ������
	//------------------------------------------------------------
	SheetCount = 0;
	::ZeroMemory( pSheet, sizeof(SHEETDATA[SHEET_MAX]) );
	::ZeroMemory( pFontUV, sizeof(FONTUVDATA) );
	for ( i = 0; i < FONT_MAX; i++ )
	{
		pFontUV[i].SheetNo = -1;
	}

	for ( i = 0; i < CHARA_CODE_MAX; i++ )
	{
		Lfd.IndexTbl[i] = 0xFFFF;
	}

	long LineHeight	= (FontData.FontSize + 2) * FontData.SamplingCount;
	long TexWidth	= TexSizeTbl[TexWidthNo]  * FontData.SamplingCount;
	long TexHeight	= TexSizeTbl[TexHeightNo] * FontData.SamplingCount;
	long Space[]	= { FontData.SamplingCount, FontData.SamplingCount * 2 };

	//------------------------------------------------------------
	// �����f�[�^��������
	//------------------------------------------------------------
	STRING *pStr = GetStringBuffer();
	long StringCount = GetStringCount();

	//------------------------------------------------------------
	// ��ڂ̃V�[�g
	//------------------------------------------------------------
	pSheet[0].Texture.Create( TexWidth, TexHeight );
	pSheet[0].LineCount = TexHeight / LineHeight;

	//------------------------------------------------------------
	// �S��������
	//------------------------------------------------------------
	::SendDlgItemMessage( hWnd, IDC_PROGRESS, PBM_SETRANGE, 0, MAKELPARAM(0, StringCount) );
	::SendDlgItemMessage( hWnd, IDC_PROGRESS, PBM_SETSTEP, 1, 0 );
	for ( i = 0; i < StringCount; i++ )
	{
		//----------------------------------------------
		// �i���o�[
		//----------------------------------------------
		::SendDlgItemMessage( hWnd, IDC_PROGRESS, PBM_STEPIT, 0, 0 );

		//----------------------------------------------
		// �t�H���g�쐬����
		//----------------------------------------------
		// �T�[�t�F�C�X�Ƀt�H���g�`��
		CSurface TempSurf;
		DrawFont( hWnd, &TempSurf, &FontData, pStr[i].Buff );

		//----------------------------------------------
		// �t�H���g�W�J����
		//----------------------------------------------
		// �V�[�g�ɓW�J
		long w = TempSurf.GetWidth();
		long h = TempSurf.GetHeight();

		for ( ; ; )
		{
			// �W�J��̗������
			for ( j = 0; j < pSheet[SheetCount].LineCount; j++ )
			{
				// �Œ�s�b�`��
				long nTmpW = FontData.IsFixPitch ? FontData.FontSize * FontData.SamplingCount : w;

				// �W�J�\���`�F�b�N
				if ( TexWidth - pSheet[SheetCount].LineWidth[j] >= nTmpW + Space[1] )
				{
					long x = pSheet[SheetCount].LineWidth[j];
					long y = LineHeight * j;
					long add_y = FontData.PosY;
					long tmp_x;

					// �`��
					tmp_x = FontData.IsFixPitch ? (x + ((FontData.FontSize * FontData.SamplingCount + Space[1] - w) / 2)) : (x + Space[0]);

					if ( add_y > LineHeight - h - Space[1] )
					{
						add_y = LineHeight - h - Space[1];
					}
					pSheet[SheetCount].Texture.DirectDraw( tmp_x, y + Space[0] + add_y, &TempSurf, 0, 0, w, h );

					if ( pSheet[SheetCount].LineUseHeight < y + Space[0] + add_y + h )
					{
						pSheet[SheetCount].LineUseHeight = y + Space[0] + add_y + h;
					}

					// SJIS����UTF-16��
					wchar_t wChar[2] = L"";
					MBCStoWCS( pStr[i].Buff, wChar );

					// �����R�[�h
					unsigned short Code = wChar[0];

					// �e�[�u��
					Lfd.IndexTbl[Code] = Index;

					// �f�[�^�ݒ�
					pFontUV[Index].SheetNo	= (char)SheetCount;
					pFontUV[Index].abcA		= (char)((FontData.abc.abcA) / FontData.SamplingCount);
					pFontUV[Index].abcB		= (char)((w + Space[1]     ) / FontData.SamplingCount);
					pFontUV[Index].abcC		= (char)((FontData.abc.abcC) / FontData.SamplingCount);
					pFontUV[Index].x1		= (short)((x               ) / FontData.SamplingCount);
					pFontUV[Index].y1		= (short)((y               ) / FontData.SamplingCount);
					pFontUV[Index].x2		= (short)((x + w + Space[1]) / FontData.SamplingCount);
					pFontUV[Index].y2		= (short)((y + LineHeight  ) / FontData.SamplingCount);
					Index++;

					// ���𖄂߂�
					pSheet[SheetCount].LineWidth[j] += nTmpW + Space[1];

					break;
				}
			}
			// �W�J�ł��Ȃ������Ƃ�
			if ( j == pSheet[SheetCount].LineCount )
			{
				SheetCount++;
				pSheet[SheetCount].Texture.Create( TexWidth, TexHeight );
				pSheet[SheetCount].LineCount = TexHeight / LineHeight;
			}
			else
			{
				break;
			}
		}

		TempSurf.Release();
	}

	SheetCount++;

	//------------------------------------------------------------
	// �J�����g�f�B���N�g���ݒ�
	//------------------------------------------------------------
	strcpy( FolderPath, FileText );
	long len = (long)strlen( FolderPath );
	while ( FolderPath[len] != '\\' ) len--;
	FolderPath[len] = '\0';
	::SetCurrentDirectory( FolderPath );

	//------------------------------------------------------------
	// �V�[�g�e�N�X�`�����a�l�o�ŕۑ�
	//------------------------------------------------------------
	for ( i = 0; i < SheetCount; i++ )
	{
		PIXELDATA32 *pDst;
		long Pitch;

		FilterAntialias( &pSheet[i].Texture, &FontData );

		if ( pSheet[i].Texture.GetData( &pDst, &Pitch ) )
		{
			long Size = Pitch * pSheet[i].Texture.GetHeight();

			while ( Size-- != 0 )
			{
				if ( pDst[Size].a == 0x00 )
				{
					pDst[Size].r = 0x00;
					pDst[Size].g = 0x00;
					pDst[Size].b = 0x00;
				}
			}
		}

		switch ( TexExtNo )
		{
		case FF_BMP_16:
			sprintf( Temp, "%s_%02d.bmp", FileName, i );
			pSheet[i].Texture.SaveBMP16( Temp, pSheet[i].LineUseHeight / FontData.SamplingCount );
			break;
		case FF_BMP_256:
			sprintf( Temp, "%s_%02d.bmp", FileName, i );
			pSheet[i].Texture.SaveBMP256( Temp, pSheet[i].LineUseHeight / FontData.SamplingCount );
			break;
		case FF_TGA:
			sprintf( Temp, "%s_%02d.tga", FileName, i );
			pSheet[i].Texture.SaveTGA( Temp, pSheet[i].LineUseHeight / FontData.SamplingCount );
			break;
		}
	}

	//------------------------------------------------------------
	// �t�u�f�[�^�ۑ�
	//------------------------------------------------------------
	{
		Lfd.FontSize	= (unsigned char)(FontData.FontSize);
		Lfd.SheetMax	= (unsigned char)(SheetCount);
		Lfd.FontMax		= (unsigned short)(Index);
		Lfd.SheetWidth	= (unsigned short)(TexSizeTbl[TexWidthNo]);
		Lfd.SheetHeight	= (unsigned short)(TexSizeTbl[TexHeightNo]);

		sprintf( File, "%s.lfd", FileName );
		hFile = FILE_OPEN_WRITE( File );
		if ( hFile != INVALID_HANDLE_VALUE )
		{
			// �w�b�_
			FILE_WRITE( hFile, &Lfd, sizeof(LFDHEADER) );

			// �V�[�g��
			for ( i = 0; i < SheetCount; i++ )
			{
				sprintf( File, "%s_%02d", FileName, i );
				long Len = (long)strlen(File);
				while ( File[Len] != '\\' ) if ( --Len < 0 ) break;
				FILE_WRITE( hFile, File + Len + 1, sizeof(char) * 32 );
			}

			// �f�[�^
			FILE_WRITE( hFile, pFontUV, sizeof(FONTUVDATA) * Lfd.FontMax );

			FILE_CLOSE( hFile );
		}
	}
	//------------------------------------------------------------
	// �V�[�g�f�[�^���
	//------------------------------------------------------------
	for ( i = 0; i < SHEET_MAX; i++ )
	{
		pSheet[i].Texture.Release();
	}
}

//==========================================================================
//
//			�t�H���g�쐬�X���b�h
//
//==========================================================================
void FontCreateThreadProc( void *pData )
{
	// �����񐶐�
	CutString( FileText );

	// �e�N�X�`���쐬
	CreateFontTexture( (HWND)pData );

	// �I��
	::EndDialog( (HWND)pData, IDCANCEL );

	// �I��
	::_endthread();
}

//==========================================================================
//
//			���b�Z�[�W
//
//==========================================================================
LRESULT CALLBACK ProgressProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	//------------------------------------------------------ �_�C�A���O��������
	case WM_INITDIALOG:
		// �X���b�h����
		::_beginthread( FontCreateThreadProc, 0, hWnd );

		return TRUE;
	}

	return FALSE;
}

//==========================================================================
//
//			���`��
//
//==========================================================================
void DrawBox( HDC hdc, long x1, long y1, long x2, long y2, COLORREF Color )
{
	static LOGBRUSH LogBrush;
	static HBRUSH NowBrush,OldBrush;

	LogBrush.lbStyle = BS_SOLID;
	LogBrush.lbColor = Color;

	NowBrush = CreateBrushIndirect( &LogBrush );
	OldBrush = (HBRUSH)SelectObject( hdc, NowBrush );

	Rectangle( hdc, x1, y1, x2, y2 );

	SelectObject( hdc, OldBrush );
	DeleteObject( NowBrush );
}

//=============================================================================
//
//			�J���[�I���_�C�A���O
//
//=============================================================================
void OpenColorDialog( HWND hWnd, COLORREF *pColor )
{
	CHOOSECOLOR cc = {
		sizeof(CHOOSECOLOR),
		hWnd,
		NULL,
		*pColor,
		pColor,
		CC_FULLOPEN | CC_RGBINIT,
	};

	if ( !::ChooseColor( &cc ) ) return;

	*pColor = cc.rgbResult;
}

//=============================================================================
//
//		�g�[�N����
//
//==========================================================================
long GetToken( char *pDst, char *pSrc )
{
	long n = 0;

	while ( *pSrc != '\0' )
	{
		n++;
		*pDst++ = *pSrc++;
		if ( *pSrc == ',' )
		{
			break;
		}
	}

	*pDst = '\0';

	return n+1;
}

//=============================================================================
//
//			�o�b�`����
//
//=============================================================================
void AnalyzeBatch( int nArgc, char* pArgv[] )
{
	//-----------------------------------------
	// �������
	//-----------------------------------------
	for ( long i = 1; i < nArgc; i++ )
	{
		if ( pArgv[i][0] == '/' )
		{
			char Temp[256] = "";
			char buff[256] = "";
			long n = GetToken( buff, pArgv[i] + 1 ) + 1;
			// �R�[�h�����킯
			if ( !strcmp( buff, "width" ) )
			{
				char Temp[256] = "";
				n += GetToken( Temp, pArgv[i] + n );
				TexWidthNo = atoi( Temp );
			}
			else
			if ( !strcmp( buff, "height" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				TexHeightNo = atoi( Temp );
			}
			else
			if ( !strcmp( buff, "format" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				TexExtNo = atoi( Temp );
			}
			else
			if ( !strcmp( buff, "size" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				FontData.FontSize = atoi( Temp );
			}
			else
			if ( !strcmp( buff, "sample" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				FontData.SamplingCount = atoi( Temp );
			}
			else
			if ( !strcmp( buff, "aspect" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				FontData.fAspectX = (float)atof( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				FontData.fAspectY = (float)atof( Temp );
			}
			else
			if ( !strcmp( buff, "color" ) )
			{
				long r, g, b;
				n += GetToken( Temp, pArgv[i] + n );
				r = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				g = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				b = atoi( Temp );

				FontData.FontColor = 0xFF000000 | RGB(r,g,b);
			}
			else
			if ( !strcmp( buff, "edge" ) )
			{
				FontData.IsEdge = TRUE;
				n += GetToken( Temp, pArgv[i] + n );
				FontData.EdgeSize = atoi( Temp );

				long r, g, b;
				n += GetToken( Temp, pArgv[i] + n );
				r = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				g = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				b = atoi( Temp );

				FontData.EdgeColor = 0xFF000000 | RGB(r,g,b);
			}
			else
			if ( !strcmp( buff, "bevel" ) )
			{
				FontData.IsBevel = TRUE;
				n += GetToken( Temp, pArgv[i] + n );
				FontData.BevelSize = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				FontData.BevelDir = atoi( Temp );

				long r, g, b;
				n += GetToken( Temp, pArgv[i] + n );
				r = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				g = atoi( Temp );
				n += GetToken( Temp, pArgv[i] + n );
				b = atoi( Temp );

				FontData.BevelColor = 0xFF000000 | RGB(r,g,b);
			}
			else
			if ( !strcmp( buff, "bold" ) )
			{
				FontData.IsBold = TRUE;
			}
			else
			if ( !strcmp( buff, "italic" ) )
			{
				FontData.IsItalic = TRUE;
			}
			else
			if ( !strcmp( buff, "face" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				strcpy( FontData.Face, Temp );
			}
			else
			if ( !strcmp( buff, "out" ) )
			{
				n += GetToken( Temp, pArgv[i] + n );
				strcpy( FileName, Temp );
			}
			else
			if ( !strcmp( buff, "fixpitch" ) )
			{
				FontData.IsFixPitch = TRUE;
			}
		}
		else
		{
			// ���̓t�@�C����
			::GetCurrentDirectory( 512, FolderPath );
			sprintf( FileText, "%s\\%s", FolderPath, pArgv[i] );
		}
	}
}

//=============================================================================
/**
*/
//=============================================================================
void BatchMode( void )
{
	//-------------------------------------------------------------
	// DirectX������
	//-------------------------------------------------------------
	if ( DxInitialize( ::GetDesktopWindow() ) )
	{
		AnalyzeBatch( __argc, __argv );

		//-----------------------------------------
		// �v���O���X�o�[
		//-----------------------------------------
		::DialogBox( hInstance, "IDD_DIALOG_PROGRESS", NULL, (DLGPROC)ProgressProc );

		//-----------------------------------------
		// DirectX���
		//-----------------------------------------
		DxFinalize();
	}
}

//=============================================================================
/**
*/
//=============================================================================
void MBCStoWCS( const char *pSrc, wchar_t *pDst )
{
	int Len = ::MultiByteToWideChar( CP_ACP, 0, pSrc, -1, NULL, 0 );
	::MultiByteToWideChar( CP_ACP, 0, pSrc, -1, pDst, Len );
}
