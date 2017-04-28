

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Lue.h"


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// 画面横幅
#define SCREEN_HEIGHT	(480)		// 画面縦幅

#define BALL_MAX		(256)		// ボールの数
#define BALL_SIZE		(32)		// ボールの画像サイズ
#define BALL_TYPE_MAX	(9)			// ボールの種類


//=============================================================================
// STRUCT
//=============================================================================
typedef struct SBallData
{
	float Px;
	float Py;
	float Mx;
	float My;
}
SBallData;


//=============================================================================
// VARIABLE
//=============================================================================
static SBallData g_BallData[BALL_MAX];


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
	LUE_HANDLE hTex = INVALID_LUE_HANDLE;	// テクスチャハンドル
	LUE_HANDLE lSpr = INVALID_LUE_HANDLE;	// スプライトハンドル
	LueRect Src, Dst;
	long i, Type, Angle;

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
	LueFile_SetCurrentDirectory( "2D\\Sprite" );

	//--------------------------------------------------------
	// テクスチャの読み込み
	//--------------------------------------------------------
	// テクスチャ生成用のオプション設定
	//  0,255,0 の色をカラーキーに設定
	LueTexture_SetConfig( LUE_RGB(0,255,0) );

	// 画像ファイルからテクスチャ読み込み
	//  DirectXで扱うテクスチャのサイズは２の階乗である必要があります。
	//  １辺のピクセル数が 1、2、4、8、16、32、64、128、256、512、1024、2048 である必要があります。
	hTex = LueTexture_CreateFromFile( "Ball.bmp" );

	// スプライト用バッファを生成
	//  三角形2枚で四角形を作るので、四角形1つに大して6個の頂点が必要です。
	//  また作成時に使用するテクスチャを渡します。
	lSpr = LueSprite2D_Create( BALL_MAX * 6, hTex );

	//--------------------------------------------------------
	// ボール情報初期化
	//--------------------------------------------------------
	for ( i = 0; i < BALL_MAX; i++ )
	{
		Angle = rand() % LUE_ANGLE_MAX;
		g_BallData[i].Px = (float)(rand() % (SCREEN_WIDTH  - BALL_SIZE));	// 初期位置
		g_BallData[i].Py = (float)(rand() % (SCREEN_HEIGHT - BALL_SIZE));	// 初期位置
		g_BallData[i].Mx = LueMath_Cos( Angle ) * 2.0f;						// 移動方向
		g_BallData[i].My = LueMath_Sin( Angle ) * 2.0f;						// 移動方向
	}

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
		///////////////////////////////////////////////////////////////// ボールのデータ更新
		// ボールの位置情報を更新
		for ( i = 0; i < BALL_MAX; i++ )
		{
			g_BallData[i].Px += g_BallData[i].Mx;
			g_BallData[i].Py += g_BallData[i].My;

			// 左移動時、画面端まで言った反転
			if ( (g_BallData[i].Mx < 0) && (g_BallData[i].Px <= 0) )
			{
				g_BallData[i].Mx = -g_BallData[i].Mx;
			}
			// 右移動時、画面端まで言った反転
			if ( (g_BallData[i].Mx > 0) && (g_BallData[i].Px + BALL_SIZE >= SCREEN_WIDTH) )
			{
				g_BallData[i].Mx = -g_BallData[i].Mx;
			}
			// 上移動時、画面端まで言った反転
			if ( (g_BallData[i].My < 0) && (g_BallData[i].Py <= 0) )
			{
				g_BallData[i].My = -g_BallData[i].My;
			}
			// 下移動時、画面端まで言った反転
			if ( (g_BallData[i].My > 0) && (g_BallData[i].Py + BALL_SIZE >= SCREEN_HEIGHT) )
			{
				g_BallData[i].My = -g_BallData[i].My;
			}
		}

		///////////////////////////////////////////////////////////////// スプライトへの描画リクエスト

		// スプライトへの描画開始を通知
		LueSprite2D_Begin( lSpr );

		// スプライトに対してボールを描画
		for ( i = 0; i < BALL_MAX; i++ )
		{
			// 描画位置
			Dst.x = (int)g_BallData[i].Px;
			Dst.y = (int)g_BallData[i].Py;
			Dst.w = BALL_SIZE;
			Dst.h = BALL_SIZE;
			// テクスチャ位置
			Type = i % BALL_TYPE_MAX;
			Src.x = (Type % 3) * BALL_SIZE;
			Src.y = (Type / 3) * BALL_SIZE;
			Src.w = BALL_SIZE;
			Src.h = BALL_SIZE;
			// スプライトに描画をリクエスト
			LueSprite2D_DrawSquare( lSpr, Dst, Src, LUE_RGB(255,255,255) ); 
		}

		// スプライトへの描画完了を通知
		LueSprite2D_End( lSpr );

		///////////////////////////////////////////////////////////////// レンダラーへの描画処理

		// 描画開始宣言
		LueRender_SceneStart();

		// スプライトバッファの内容を画面に描画
		LueSprite2D_Rendering( lSpr );

		// 描画終了宣言
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// 終了処理
	//--------------------------------------------------------
	// 作成したスプライトを解放
	LueSprite2D_Release( lSpr );
	// 読み込んだテクスチャを解放
	LueTexture_Release( hTex );

	//--------------------------------------------------------
	// Lue終了
    //   Lueで使用している全データを解放します。
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


