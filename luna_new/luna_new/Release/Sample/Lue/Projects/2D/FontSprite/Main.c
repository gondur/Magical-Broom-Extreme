

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// 画面横幅
#define SCREEN_HEIGHT	(480)		// 画面縦幅

#define FONT_MAX		(1024)		// フォントスプライト数


//=============================================================================
/**
	@brief メイン関数

	@param hInstance		[in] 現在のインスタンスのハンドル
	@param hPrevInstance	[in] 以前のインスタンスのハンドル
	@param lpCmdPoint		[in] コマンドフォントスプライト
	@param nCmdShow			[in] 表示状態

	コンソールアプリケーションでいう所の main() 関数です。
	ウィンドウズアプリケーションでは以下の関数が main() になります。
*/
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdPoint, int nCmdShow )
{
	LUE_HANDLE hFontSpr;

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
	// ファイル読み込み場所の設定
	//--------------------------------------------------------
	// ファイル読み込みのルートディレクトリ設定
	LueFile_SetLoadPath( 0, "Data", "Data.bin" );

	// ファイル読み込みの基準ディレクトリ設定
	LueFile_SetCurrentDirectory( "2D\\FontSprite" );

	//--------------------------------------------------------
	// フォントスプライト用描画オブジェクト生成
	//   専用ツールであるFontUtilityを使って文字で作成した
	//   文字定義データを読み込みます。
	//   ツール上で生成した文字なら全て高速に描画することができます。
	//
	//   またLueFontSprite2Dは低レベル部分にLueFontSpriteを
	//   使用しているので、1文字描画する場合に3角形x2で6頂点
	//   使用します。
	//--------------------------------------------------------
	hFontSpr = LueFontSprite2D_CreateFromFile( "Font.lfd", "tga", FONT_MAX * 6 );

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
		///////////////////////////////////////////////////////////////// フォントスプライトへの描画リクエスト

		// フォントスプライトへの描画開始を通知
		LueFontSprite2D_Begin( hFontSpr );

		// フォントスプライトに対して描画
		LueFontSprite2D_DrawString( hFontSpr, "さんぷるテキスト", 100, 100, LUE_RGB(255,255,255) );
		LueFontSprite2D_DrawString( hFontSpr, "ﾊﾝｶｸもかけます", 100, 130, LUE_RGB(255,255,255) );
		LueFontSprite2D_DrawString( hFontSpr, "ABCabcＡＢＣａｂｃ012０１２", 100, 160, LUE_RGB(255,255,255) );

		// フォントスプライトへの描画完了を通知
		LueFontSprite2D_End( hFontSpr );

		///////////////////////////////////////////////////////////////// レンダラーへの描画処理

		// 描画開始宣言
		LueRender_SceneStart();

		// フォントスプライトバッファの内容を画面に描画
		LueFontSprite2D_Rendering( hFontSpr );

		// 描画終了宣言
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// フォントスプライトオブジェクト解放
	//--------------------------------------------------------
	LueFontSprite2D_Release( hFontSpr );

	//--------------------------------------------------------
	// Lue終了
    //   Lueで使用している全データを解放します。
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}

