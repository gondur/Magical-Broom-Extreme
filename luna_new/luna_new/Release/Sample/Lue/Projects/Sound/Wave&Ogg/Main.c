

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// PROTOTYPE
//=============================================================================
static BOOL FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter );


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// 画面横幅
#define SCREEN_HEIGHT	(480)		// 画面縦幅


//=============================================================================
/**
	@brief メイン関数

	@param hInstance		[in] 現在のインスタンスのハンドル
	@param hPrevInstance	[in] 以前のインスタンスのハンドル
	@param lpCmdLine		[in] コマンドライン
	@param nCmdShow			[in] 表示状態

	コンソールアプリケーションでいう所の main() 関数です。
	ウィンドウズアプリケーションでは以下の関数が main() になります。
*/
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	LUE_HANDLE hSound;			// サウンドハンドル
	char FilePath[MAX_PATH];

	//--------------------------------------------------------
	// Lue初期化
	//--------------------------------------------------------
	if ( !Lue_Initialize(
			"Lue Sample Program",		// アプリケーション名
			SCREEN_WIDTH,				// ウィンドウ横幅
			SCREEN_HEIGHT,				// ウィンドウ縦幅
			LFRAME_RATE_60,				// フレームレート（1秒間のフレーム数）
			LTRUE,						// ウィンドウモードで起動するかどうか
			LAPI_TYPE_DIRECTX9 ) )		// 固定
	{
		return 1;
	}

	//--------------------------------------------------------
	// サウンドファイルの読み込み
	//--------------------------------------------------------
	if ( !FileOpenDialog( FilePath, "サウンド選択", "サウンドファイル(*.wav *.ogg)\0*.wav;*.ogg\0\0" ) )
	{
		// ファイルが読み込めなかった
		Lue_Finalize();
		return 1;
	}

	//--------------------------------------------------------
	// サウンドファイルを読み込みます。
	//   LueではサウンドのドライバにAyameを採用しているので、
	//   Ayameで対応しているサウンドフォーマットが使えます。
	//   具体的に 無圧縮wave、圧縮wave、OggVorbis の3種類です。
	//--------------------------------------------------------
	hSound = LueSound_CreateFromFile( FilePath, LFALSE );

	// サウンドの再生
	LueSound_Loop(
		hSound,					// サウンドハンドル
		SOUND_LOOP_INFINITY,	// ループ回数（無限
		0 );					// ループ後の先頭位置（サンプリング指定

	//--------------------------------------------------------
	// メインループ
	//   ALT+F4でアプリケーションの終了。
	//   ALT+ENTERで画面モードの切り替え
	//
	// Lue_Run()はウィンドウを使ったゲームで必須の処理が
	// 内部に組み込まれています。
	// ウィンドウを正常に終了させた場合は LFASE が返りますので
	// その時はループから抜けるような作りにして下さい。
	//--------------------------------------------------------
	while ( Lue_Run( LFALSE ) )
	{
	}

	//--------------------------------------------------------
	// サウンドファイルの解放
	//--------------------------------------------------------
	LueSound_Release( hSound );

	//--------------------------------------------------------
	// Lue終了
    //   Lueで使用している全データを解放します。
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}

//=============================================================================
/**
	@brief ファイル選択用ダイアログをだします。

	@param pPath	[out] ファイルが格納されるパス（MAX_PATHバイトのchar配列）
	@param pTitle	[in] ダイアログのタイトル
	@param pFilter	[in] 拡張子の指定
	@param pExt		[in] 拡張子

	@retval true	成功
	@retval false	失敗
*/
//=============================================================================
BOOL FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter )
{
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };
	ofn.hwndOwner		= GetActiveWindow();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= MAX_PATH;
	ofn.lpstrDefExt		= ".";
	ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	pPath[0] = '\0';

	return GetOpenFileName( &ofn );
}


