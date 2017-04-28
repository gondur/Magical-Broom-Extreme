

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
	char Guid[4];								///< ファイル識別情報（常に 'L' 'F' 'D' '\0'
	unsigned char FontSize;						///< フォントサイズ
	unsigned char SheetMax;						///< シート最大数
	unsigned short SheetWidth;					///< シート横幅
	unsigned short SheetHeight;					///< シート縦幅
	unsigned short FontMax;						///< フォント最大数
	unsigned short IndexTbl[CHARA_CODE_MAX];	///< インデックステーブル
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

	// デフォルト設定
	ZeroMemory(&FontData, sizeof(FontData));
	strcpy(FontData.Face, "ＭＳ ゴシック");
	FontData.FontSize = 26;
	FontData.FontColor = 0xFFFFFFFF;
	FontData.SamplingCount = 1;
	FontData.fAspectX = 1.0f;
	FontData.fAspectY = 1.0f;

	// バッファ確保
	pSheet = (SHEETDATA*)SAFE_ALLOC( sizeof(SHEETDATA[SHEET_MAX]) );
	pFontUV = (FONTUVDATA*)SAFE_ALLOC( sizeof(FONTUVDATA[FONT_MAX]) );

	if ( __argc > 1 )
	{
		BatchMode();
	}
	else
	{
		// ダイアログボックスオープン
		::DialogBox( hInst, "IDD_DIALOG_MAIN", NULL, (DLGPROC)DlgProc );
	}

	// バッファ解放
	SAFE_FREE( pSheet );
	SAFE_FREE( pFontUV );

	return 0L;
}


//==========================================================================
//
//		メッセージ関数
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
	//------------------------------------------------------ ダイアログ初期化時
	case WM_INITDIALOG:
		{
			// DirectDraw初期化
			if ( !DxInitialize( ::GetDlgItem(hWnd, IDC_PICTURE) ) )
			{
				::EndDialog( hWnd, IDCANCEL );
				break;
			}
			// プレビュー用サーフェイス
			::GetWindowRect( ::GetDlgItem(hWnd, IDC_PICTURE), &Rect );
			PreviewSurf.Create( Rect.right-Rect.left, Rect.bottom-Rect.top );
			// フォント検索
			FontCount = 0;
			ZeroMemory( &lf, sizeof(LOGFONT) );
			lf.lfCharSet = SHIFTJIS_CHARSET;
			hdc = GetDC( hWnd );
			EnumFontFamiliesEx( hdc, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)NULL, 0 );
			ReleaseDC( hWnd, hdc );
			// ウィンドウを画面中央に
			::SetWindowText( hWnd, "フォントユーティリティ Version "PRODUCT_VERSION );
			::GetWindowRect( hWnd, &Rect );
			::SetWindowPos(
					hWnd,
					HWND_TOP,
					(GetSystemMetrics(SM_CXSCREEN)-(Rect.right-Rect.left))/2,
					(GetSystemMetrics(SM_CYSCREEN)-(Rect.bottom-Rect.top))/2,
					(Rect.right-Rect.left),
					(Rect.bottom-Rect.top),
					SWP_SHOWWINDOW );
			// データ名
			::SetDlgItemText( hWnd, IDC_EDIT_DATANAME, (LPCTSTR)FileName );
			// フォントサイズ
			sprintf( StrBuff, "%d", FontData.FontSize );
			::SetDlgItemText( hWnd, IDC_EDIT_FONTSIZE, (LPCTSTR)StrBuff );
			// サンプリング数
			sprintf( StrBuff, "%d", FontData.SamplingCount );
			::SetDlgItemText( hWnd, IDC_EDIT_SAMPLING, (LPCTSTR)StrBuff );
			// アスペクト比
			sprintf( StrBuff, "%.2lf", FontData.fAspectX );
			::SetDlgItemText( hWnd, IDC_EDIT_ASPECT_X, (LPCTSTR)StrBuff );
			sprintf( StrBuff, "%.2lf", FontData.fAspectY );
			::SetDlgItemText( hWnd, IDC_EDIT_ASPECT_Y, (LPCTSTR)StrBuff );
			// 縁サイズ
			sprintf( StrBuff, "%d", FontData.EdgeSize );
			::SetDlgItemText( hWnd, IDC_EDIT_EDGESIZE, (LPCTSTR)StrBuff );
			// シャドウサイズ
			sprintf( StrBuff, "%d", FontData.BevelSize );
			::SetDlgItemText( hWnd, IDC_EDIT_BEVELSIZE, (LPCTSTR)StrBuff );
			// フォントフェース
			for ( i = 0; i < FontCount; i++ )
			{
				::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_INSERTSTRING, i, (LPARAM)szFontList[i] );
			}
			// デフォルトのフォントは”ＭＳ ゴシック”
			for ( i = 0; i < FontCount; i++ )
			{
				if ( !strcmp( "ＭＳ ゴシック", szFontList[i] ) )
				{
					::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_SETCURSEL, i, 0L );
				}
			}
			// シャドウ方向
			for ( i = 0; i < 8; i++ )
			{
				char *pStr[] = { "左上", "右上", "左下", "右下", "上", "下", "左", "右" };
				::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
			}
			::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_SETCURSEL, 0, 0L );
			FontData.BevelDir = BevelTbl[FontData.BevelDir];
			// テクスチャサイズ
			for ( i = 0; i < 5; i++ )
			{
				char *pStr[] = { "128", "256", "512", "1024", "2048" };
				::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
				::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
			}
			::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_SETCURSEL, TexWidthNo, 0L );
			::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_SETCURSEL, TexHeightNo, 0L );
			// 拡張子
			for ( i = 0; i < 3; i++ )
			{
				char *pStr[] = { "bmp(4bit)", "bmp(8bit)", "tga(32bit)" };
				::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_EXT, CB_INSERTSTRING, i, (LPARAM)pStr[i] );
			}
			::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_EXT, CB_SETCURSEL, TexExtNo, 0L );

			// 画面更新
			UpdatePreview( hWnd );
		}
		return FALSE;

	//------------------------------------------------------ コマンド処理時
	case WM_COMMAND:
		switch ( LOWORD( wParam ) )
		{
		//----------------------------- フォント作成
		case ID_CREATE:
			{
				if ( FileName[0] == '\0' )
				{
					::MessageBox( hWnd, "データ名が入力されていません", "Error", MB_ICONERROR );
				}
				else
				if ( strlen( FileName ) >= 16 )
				{
					::MessageBox( hWnd, "データ名が長すぎます\n半角16文字までです", "Error", MB_ICONERROR );
				}
				else
				if ( FileText[0] == '\0' )
				{
					::MessageBox( hWnd, "入力ファイル名が指定されていません", "Error", MB_ICONERROR );
				}
				else
				{
					// 生成
					::DialogBox(
							hInstance,
							"IDD_DIALOG_PROGRESS",
							hWnd,
							(DLGPROC)ProgressProc );
				}
			}
			return TRUE;

		//----------------------------- バッチ保存
		case ID_SAVE_BATCH:
			if ( FileSaveDialog( StrBuff, hWnd, "バッチファイル保存", "BATファイル(*.bat)\0*.bat\0", "BAT" ) )
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

		//----------------------------- バッチ読込
		case ID_LOAD_BATCH:
			if ( FileOpenDialog( StrBuff, hWnd, "バッチファイル読込", "BATファイル(*.bat)\0*.bat\0", "BAT" ) )
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

						// コンバートファイルパス
						::SetDlgItemText( hWnd, IDC_EDIT_FILE_TEXT, (LPCTSTR)FileText );
						// 出力データ名
						::SetDlgItemText( hWnd, IDC_EDIT_DATANAME, (LPCTSTR)FileName );

						// 書体
						for ( i = 0; i < FontCount; i++ )
						{
							if ( !strcmp( FontData.Face, szFontList[i] ) )
							{
								::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_SETCURSEL, i, 0L );
							}
						}
						// フォントサイズ
						sprintf( StrBuff, "%d", FontData.FontSize );
						::SetDlgItemText( hWnd, IDC_EDIT_FONTSIZE, (LPCTSTR)StrBuff );

						// サンプリング数
						sprintf( StrBuff, "%d", FontData.SamplingCount );
						::SetDlgItemText( hWnd, IDC_EDIT_SAMPLING, (LPCTSTR)StrBuff );
						// アスペクト比
						sprintf( StrBuff, "%.1lf", FontData.fAspectX );
						::SetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_X), StrBuff );
						sprintf( StrBuff, "%.1lf", FontData.fAspectY );
						::SetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_Y), StrBuff );
						// 縁サイズ
						sprintf( StrBuff, "%d", FontData.EdgeSize );
						::SetDlgItemText( hWnd, IDC_EDIT_EDGESIZE, (LPCTSTR)StrBuff );
						::SendDlgItemMessage( hWnd, IDC_CHECK_EDGE, BM_SETCHECK, FontData.IsEdge, 0L );
						// 太字
						::SendDlgItemMessage( hWnd, IDC_CHECK_BOLD, BM_SETCHECK, FontData.IsBold, 0L );
						// 斜体
						::SendDlgItemMessage( hWnd, IDC_CHECK_ITALIC, BM_SETCHECK, FontData.IsItalic, 0L );
						// シャドウサイズ
						sprintf( StrBuff, "%d", FontData.BevelSize );
						::SetDlgItemText( hWnd, IDC_EDIT_BEVELSIZE, (LPCTSTR)StrBuff );
						for(int i = 0; i < (sizeof(BevelTbl) / sizeof(long)); i++) {
							if (BevelTbl[i] == FontData.BevelDir)
							{
								::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_SETCURSEL, i, 0L );
							}
						}
						::SendDlgItemMessage( hWnd, IDC_CHECK_BEVEL, BM_SETCHECK, FontData.IsBevel, 0L );
						// テクスチャサイズ
						::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_SETCURSEL, TexWidthNo, 0L );
						::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_SETCURSEL, TexHeightNo, 0L );
						// 拡張子
						::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_EXT, CB_SETCURSEL, TexExtNo, 0L );
						// ピッチ固定
						::SendDlgItemMessage( hWnd, IDC_CHECK_FIXPITCH, BM_SETCHECK, FontData.IsFixPitch, 0L );

						// 画面更新
						UpdatePreview( hWnd );
					}
					fclose( fp );
				}
			}
			return TRUE;

		//----------------------------- ファイル選択
		case IDC_FILE_SELECT_TEXT:
			if ( FileOpenDialog( StrBuff, hWnd, "テキストファイル読み込み", "TEXTファイル(*.txt)\0*.txt\0", "TXT" ) )
			{
				strcpy( FileText, StrBuff );
				::SetDlgItemText( hWnd, IDC_EDIT_FILE_TEXT, (LPCTSTR)FileText );
			}
			return TRUE;

		//----------------------------- ファイル名
		case IDC_EDIT_FILE_TEXT:
			::GetDlgItemText( hWnd, IDC_EDIT_FILE_TEXT, FileText, sizeof(FileText) );
			return TRUE;

		//----------------------------- データ名
		case IDC_EDIT_DATANAME:
			::GetDlgItemText( hWnd, IDC_EDIT_DATANAME, FileName, sizeof(FileName) );
			break;

		//----------------------------- フォントフェース
		case IDC_COMBO_FONTFACE:
			i = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_FONTFACE, CB_GETCURSEL, 0L, 0L );
			strcpy( FontData.Face, szFontList[i] );
			return TRUE;

		//----------------------------- フォントサイズ
		case IDC_EDIT_FONTSIZE:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_FONTSIZE), StrBuff, sizeof(StrBuff) );
			FontData.FontSize = atoi( StrBuff );
			return TRUE;

		//----------------------------- フォント色
		case IDC_COLOR_FONT:
			OpenColorDialog( hWnd, &FontData.FontColor );
			return TRUE;

		//----------------------------- サンプリング数
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

		//----------------------------- アスペクト比
		case IDC_EDIT_ASPECT_X:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_X), StrBuff, 256 );
			FontData.fAspectX = (float)atof( StrBuff );
			return TRUE;

		//----------------------------- アスペクト比
		case IDC_EDIT_ASPECT_Y:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_ASPECT_Y), StrBuff, 256 );
			FontData.fAspectY = (float)atof( StrBuff );
			return TRUE;

		//----------------------------- 斜体チェック
		case IDC_CHECK_ITALIC:
			FontData.IsItalic = (::IsDlgButtonChecked(hWnd, IDC_CHECK_ITALIC) == BST_CHECKED);
			return TRUE;

		//----------------------------- 太字チェック
		case IDC_CHECK_BOLD:
			FontData.IsBold = (::IsDlgButtonChecked(hWnd, IDC_CHECK_BOLD) == BST_CHECKED);
			return TRUE;

		//----------------------------- 縁チェック
		case IDC_CHECK_EDGE:
			FontData.IsEdge = (::IsDlgButtonChecked(hWnd, IDC_CHECK_EDGE) == BST_CHECKED);
			return TRUE;

		//----------------------------- 縁サイズ
		case IDC_EDIT_EDGESIZE:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_EDGESIZE), StrBuff, sizeof(StrBuff) );
			FontData.EdgeSize = atoi( StrBuff );
			return TRUE;

		//----------------------------- 縁色
		case IDC_COLOR_EDGE:
			OpenColorDialog( hWnd, &FontData.EdgeColor );
			return TRUE;

		//----------------------------- 押し出しチェック
		case IDC_CHECK_BEVEL:
			FontData.IsBevel = (::IsDlgButtonChecked(hWnd, IDC_CHECK_BEVEL) == BST_CHECKED);
			return TRUE;

		//----------------------------- 押し出し方向
		case IDC_COMBO_BEVELDIR:
			FontData.BevelDir = (long)(DWORD)::SendDlgItemMessage( hWnd, IDC_COMBO_BEVELDIR, CB_GETCURSEL, 0L, 0L );
			FontData.BevelDir = BevelTbl[FontData.BevelDir];
			return TRUE;

		//----------------------------- 押し出しサイズ
		case IDC_EDIT_BEVELSIZE:
			::GetWindowText( ::GetDlgItem(hWnd, IDC_EDIT_BEVELSIZE), StrBuff, sizeof(StrBuff) );
			FontData.BevelSize = atoi( StrBuff );
			return TRUE;

		//----------------------------- 押し出し色
		case IDC_COLOR_BEVEL:
			OpenColorDialog( hWnd, &FontData.BevelColor );
			return TRUE;

		//----------------------------- テクスチャ横幅
		case IDC_COMBO_TEX_W:
			TexWidthNo = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_W, CB_GETCURSEL, 0L, 0L );
			return TRUE;

		//----------------------------- テクスチャ縦幅
		case IDC_COMBO_TEX_H:
			TexHeightNo = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_TEX_H, CB_GETCURSEL, 0L, 0L );
			return TRUE;

		//----------------------------- テクスチャ拡張子
		case IDC_COMBO_EXT:
			TexExtNo = (long)::SendDlgItemMessage( hWnd, IDC_COMBO_EXT, CB_GETCURSEL, 0L, 0L );
			return TRUE;

		//----------------------------- ピッチ固定チェック
		case IDC_CHECK_FIXPITCH:
			FontData.IsFixPitch = (::IsDlgButtonChecked(hWnd, IDC_CHECK_FIXPITCH) == BST_CHECKED);
			return TRUE;

		//----------------------------- プレビューウィンドウ更新
		case IDC_PREVIEW:
			UpdatePreview( hWnd );
			return TRUE;
		}
		return TRUE;

	//------------------------------------------------------ ダイアログ終了時
	case WM_CLOSE:
		PreviewSurf.Release();
		DxFinalize();
		::EndDialog( hWnd, IDCANCEL );
		return TRUE;

	//------------------------------------------------------ ウィンドウ再描画
	case WM_PAINT:
		RefreshWindow( hWnd );
		return FALSE;
	}

	return FALSE;
}

//==========================================================================
//
//			フォント検索
//
//==========================================================================
int CALLBACK EnumFontFamExProc( LOGFONT* Lf, LPNEWTEXTMETRIC* Tm, DWORD Type, LPARAM Data )
{
	// 多すぎ
	if ( FontCount == FONT_MAX ) return 0;

	// 縦書き不要
	if ( Lf->lfFaceName[0] == '@' ) return 1;

	// フォント名の取得
	strcpy( szFontList[FontCount++], Lf->lfFaceName );

	return 1;
}


//==========================================================================
//
//			フォルダ選択ダイアログ
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
	bi.lpszTitle	= "ディレクトリ指定";

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
//		ファイルオープンファイアログ
//
//==========================================================================
BOOL FileOpenDialog( char *pPath, HWND hWnd, char *pTitle, char *pFilter, char *pExt )
{
	pPath[0] = '\0';

	//=======================================================
	// ファイルオープン
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
//		ファイルオープンファイアログ
//
//==========================================================================
BOOL FileSaveDialog( char *pPath, HWND hWnd, char *pTitle, char *pFilter, char *pExt )
{
	pPath[0] = '\0';

	//=======================================================
	// ファイルオープン
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
//			プレビューウィンドウ更新
//
//==========================================================================
void UpdatePreview( HWND hWnd )
{
	CSurface TempSurf;

	// サーフェイスにフォント描画
	DrawFont( hWnd, &TempSurf, &FontData, "あ" );
	FilterAntialias( &TempSurf, &FontData );

	// プレビュー画面に表示
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

	// ウィンドウ更新
	RefreshWindow( hWnd );
}

//==========================================================================
//
//			プレビューウィンドウ更新
//
//==========================================================================
void RefreshWindow( HWND hWnd )
{
	HWND hDstWnd = ::GetDlgItem(hWnd, IDC_PICTURE);

	DxRefreshBackBuffer( hDstWnd );

	// 画面更新
	::InvalidateRect( hDstWnd, NULL, FALSE );
}

//==========================================================================
//
//			テクスチャ作成
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
	// 初期化
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
	// 文字データ＆文字数
	//------------------------------------------------------------
	STRING *pStr = GetStringBuffer();
	long StringCount = GetStringCount();

	//------------------------------------------------------------
	// 一つ目のシート
	//------------------------------------------------------------
	pSheet[0].Texture.Create( TexWidth, TexHeight );
	pSheet[0].LineCount = TexHeight / LineHeight;

	//------------------------------------------------------------
	// 全文字処理
	//------------------------------------------------------------
	::SendDlgItemMessage( hWnd, IDC_PROGRESS, PBM_SETRANGE, 0, MAKELPARAM(0, StringCount) );
	::SendDlgItemMessage( hWnd, IDC_PROGRESS, PBM_SETSTEP, 1, 0 );
	for ( i = 0; i < StringCount; i++ )
	{
		//----------------------------------------------
		// 進捗バー
		//----------------------------------------------
		::SendDlgItemMessage( hWnd, IDC_PROGRESS, PBM_STEPIT, 0, 0 );

		//----------------------------------------------
		// フォント作成処理
		//----------------------------------------------
		// サーフェイスにフォント描画
		CSurface TempSurf;
		DrawFont( hWnd, &TempSurf, &FontData, pStr[i].Buff );

		//----------------------------------------------
		// フォント展開処理
		//----------------------------------------------
		// シートに展開
		long w = TempSurf.GetWidth();
		long h = TempSurf.GetHeight();

		for ( ; ; )
		{
			// 展開先の列を検索
			for ( j = 0; j < pSheet[SheetCount].LineCount; j++ )
			{
				// 固定ピッチ時
				long nTmpW = FontData.IsFixPitch ? FontData.FontSize * FontData.SamplingCount : w;

				// 展開可能かチェック
				if ( TexWidth - pSheet[SheetCount].LineWidth[j] >= nTmpW + Space[1] )
				{
					long x = pSheet[SheetCount].LineWidth[j];
					long y = LineHeight * j;
					long add_y = FontData.PosY;
					long tmp_x;

					// 描画
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

					// SJISからUTF-16に
					wchar_t wChar[2] = L"";
					MBCStoWCS( pStr[i].Buff, wChar );

					// 文字コード
					unsigned short Code = wChar[0];

					// テーブル
					Lfd.IndexTbl[Code] = Index;

					// データ設定
					pFontUV[Index].SheetNo	= (char)SheetCount;
					pFontUV[Index].abcA		= (char)((FontData.abc.abcA) / FontData.SamplingCount);
					pFontUV[Index].abcB		= (char)((w + Space[1]     ) / FontData.SamplingCount);
					pFontUV[Index].abcC		= (char)((FontData.abc.abcC) / FontData.SamplingCount);
					pFontUV[Index].x1		= (short)((x               ) / FontData.SamplingCount);
					pFontUV[Index].y1		= (short)((y               ) / FontData.SamplingCount);
					pFontUV[Index].x2		= (short)((x + w + Space[1]) / FontData.SamplingCount);
					pFontUV[Index].y2		= (short)((y + LineHeight  ) / FontData.SamplingCount);
					Index++;

					// 幅を埋める
					pSheet[SheetCount].LineWidth[j] += nTmpW + Space[1];

					break;
				}
			}
			// 展開できなかったとき
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
	// カレントディレクトリ設定
	//------------------------------------------------------------
	strcpy( FolderPath, FileText );
	long len = (long)strlen( FolderPath );
	while ( FolderPath[len] != '\\' ) len--;
	FolderPath[len] = '\0';
	::SetCurrentDirectory( FolderPath );

	//------------------------------------------------------------
	// シートテクスチャをＢＭＰで保存
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
	// ＵＶデータ保存
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
			// ヘッダ
			FILE_WRITE( hFile, &Lfd, sizeof(LFDHEADER) );

			// シート名
			for ( i = 0; i < SheetCount; i++ )
			{
				sprintf( File, "%s_%02d", FileName, i );
				long Len = (long)strlen(File);
				while ( File[Len] != '\\' ) if ( --Len < 0 ) break;
				FILE_WRITE( hFile, File + Len + 1, sizeof(char) * 32 );
			}

			// データ
			FILE_WRITE( hFile, pFontUV, sizeof(FONTUVDATA) * Lfd.FontMax );

			FILE_CLOSE( hFile );
		}
	}
	//------------------------------------------------------------
	// シートデータ解放
	//------------------------------------------------------------
	for ( i = 0; i < SHEET_MAX; i++ )
	{
		pSheet[i].Texture.Release();
	}
}

//==========================================================================
//
//			フォント作成スレッド
//
//==========================================================================
void FontCreateThreadProc( void *pData )
{
	// 文字列生成
	CutString( FileText );

	// テクスチャ作成
	CreateFontTexture( (HWND)pData );

	// 終了
	::EndDialog( (HWND)pData, IDCANCEL );

	// 終了
	::_endthread();
}

//==========================================================================
//
//			メッセージ
//
//==========================================================================
LRESULT CALLBACK ProgressProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	//------------------------------------------------------ ダイアログ初期化時
	case WM_INITDIALOG:
		// スレッド生成
		::_beginthread( FontCreateThreadProc, 0, hWnd );

		return TRUE;
	}

	return FALSE;
}

//==========================================================================
//
//			箱描画
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
//			カラー選択ダイアログ
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
//		トークン切
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
//			バッチ処理
//
//=============================================================================
void AnalyzeBatch( int nArgc, char* pArgv[] )
{
	//-----------------------------------------
	// 引数解析
	//-----------------------------------------
	for ( long i = 1; i < nArgc; i++ )
	{
		if ( pArgv[i][0] == '/' )
		{
			char Temp[256] = "";
			char buff[256] = "";
			long n = GetToken( buff, pArgv[i] + 1 ) + 1;
			// コード処理わけ
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
			// 入力ファイル名
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
	// DirectX初期化
	//-------------------------------------------------------------
	if ( DxInitialize( ::GetDesktopWindow() ) )
	{
		AnalyzeBatch( __argc, __argv );

		//-----------------------------------------
		// プログレスバー
		//-----------------------------------------
		::DialogBox( hInstance, "IDD_DIALOG_PROGRESS", NULL, (DLGPROC)ProgressProc );

		//-----------------------------------------
		// DirectX解放
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
