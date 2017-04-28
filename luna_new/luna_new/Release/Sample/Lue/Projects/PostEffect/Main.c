

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(256 * 2)		// 画面横幅
#define SCREEN_HEIGHT	(256 * 2)		// 画面縦幅


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
	LUE_HANDLE hTexBase = INVALID_LUE_HANDLE;		// テクスチャハンドル
	LUE_HANDLE hTexRule = INVALID_LUE_HANDLE;		// テクスチャハンドル
	float fRate;

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
	LueFile_SetCurrentDirectory( "PostEffect" );

	//--------------------------------------------------------
	// テクスチャの読み込み
	//--------------------------------------------------------
	// テクスチャ生成用のオプション設定
	LueTexture_SetConfig( LUE_ARGB(0,0,0,0) );

	// 画像ファイルからテクスチャ読み込み
	//  DirectXで扱うテクスチャのサイズは２の階乗である必要があります。
	//  １辺のピクセル数が 1、2、4、8、16、32、64、128、256、512、1024、2048 である必要があります。
	hTexBase = LueTexture_CreateFromFile( "Base.bmp" );
	hTexRule = LueTexture_CreateFromFile( "Rule.bmp" );

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
		// 0～1
		fRate = (LueMath_Sin( Lue_GetTime() * 16 ) + 1.0f) / 2.0f;

		// 描画開始宣言
		LueRender_SceneStart();

		// 単純な描画
		{
			LueRect Dst = { 0, 0, 256, 256 };	// 描画位置
			LueRect Src = { 0, 0, 256, 256 };	// テクスチャ参照位置
			// 描画
			LueRender_DrawSingleTexture( hTexBase, Dst, Src, LUE_RGB(255,255,255) );
		}
		// グレースケール
		{
			LueRect Dst = { 256, 0, 256, 256 };	// 描画位置
			LueRect Src = {     0, 0, 256, 256 };	// テクスチャ参照位置
			// 描画
			LueRender_DrawGrayscale( hTexBase, Dst, Src, LUE_RGB(255,255,255), fRate );
		}
		// ユニバーサルトランジション
		{
			LueRect Dst = { 0, 256, 256, 256 };	// 描画位置
			LueRect SrcBase = { 0,     0, 256, 256 };	// テクスチャ参照位置
			LueRect SrcRule = { 0,     0, 128, 128};	// テクスチャ参照位置
			// 描画
			LueRender_DrawUniversalTransition( hTexBase, hTexRule, Dst, SrcBase, SrcRule, fRate );
		}
		// ぼかし
		{
			LueRect Dst = { 256, 256, 256, 256 };	// 描画位置
			LueRect Src = {   0,   0, 256, 256 };	// テクスチャ参照位置
			// 描画
			LueRender_DrawBlur16Box( hTexBase, Dst, Src, LUE_RGB(255,255,255) );
		}

		// 描画終了宣言
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// 終了処理
	//--------------------------------------------------------
	// 読み込んだテクスチャを解放
	LueTexture_Release( hTexRule );
	LueTexture_Release( hTexBase );

	//--------------------------------------------------------
	// Lue終了
    //   Lueで使用している全データを解放します。
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


