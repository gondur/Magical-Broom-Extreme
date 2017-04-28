

//=============================================================================
// INCLUDE
//=============================================================================
#include "../../../../../Include/Selene.h"


//=============================================================================
// NAMESPACE
//=============================================================================
using namespace Selene;


//=============================================================================
// DEFINE
//=============================================================================
#define SCREEN_WIDTH	(640)		// 画面横幅
#define SCREEN_HEIGHT	(480)		// 画面縦幅
#define FRAME_RATE		(60)		// フレームレート

#define TEX_W			(256)		// テクスチャ横幅
#define TEX_H			(256)		// テクスチャ縦幅


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
	ICore *pCore				= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IFileManager *pFileMgr		= NULL;
	IMouse *pMouse				= NULL;

	CColor Color;

	//----------------------------------------------------------------------------
	// システムの初期化
	//----------------------------------------------------------------------------
	// Seleneのシステムを初期化しています。
	// 起動時に必ず呼び出してください。
	CSystem::Initialize();

	//----------------------------------------------------------------------------
	// コアの生成
	//----------------------------------------------------------------------------
	// システムからICoreインターフェイスを取得しています。
	// 要するにアプリケーションウィンドウです。
	// スレッド毎に複数作成することでウィンドウも複数作られます。
	pCore = CSystem::CreateCore();

	//----------------------------------------------------------------------------
	// 初期化
	//----------------------------------------------------------------------------
	// ICoreインターフェイスの初期化を行います。
	// アプリケーションウィンドウに関しての各種初期化が行われます。
	if ( pCore->Initialize( "Selene Sample Program", FRAME_RATE ) )
	{
		//-----------------------------------------------------------------
		// グラフィックカードを取得
		//-----------------------------------------------------------------
		// グラフィックカードに関しての初期化を行います。
		// IGraphicCardインターフェイスからは接続された
		// グラフィックカードの能力を取得する事が可能です。
		// IGraphicCardインターフェイスは1つのICoreインターフェイスに対して1つしか存在しません。
		pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO, VERTEXSHADER_VERSION_2_0 );
		if ( pGraphicCard == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// ウィンドウ作成
		//-----------------------------------------------------------------
		// ICoreインターフェイス内の情報に従ってアプリケーション
		// ウィンドウを生成します。
		// IGraphicCardからの情報を元に画面解像度などを変更する場合は、
		// ICore::Start()を呼び出す前に行ってください。
		pCore->Start( SCREEN_WIDTH, SCREEN_HEIGHT, true );

		//-----------------------------------------------------------------
		// デバイスを取得
		//-----------------------------------------------------------------
		// IGraphicCardで接続されているグラフィックカードから
		// 描画用のデバイスを作成します。
		// IDeviceインターフェイスは1つのIGraphicCardインターフェイスに対して1つしか存在しません。
		pDevice = pGraphicCard->CreateDevice();
		if ( pDevice == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// レンダラーを取得
		//-----------------------------------------------------------------
		// 作成したデバイスから画面描画用のレンダラーを取得します。
		// IRenderインターフェイスは1つのIDeviceインターフェイスに対して1つしか存在しません。
		pRender = pDevice->CreateRender();
		if ( pRender == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// マウス取得
		//-----------------------------------------------------------------
		pMouse = pCore->GetMouse();
		if ( pMouse == NULL ) goto EXIT;

		//-----------------------------------------------------------------
		// ファイル登録
		//-----------------------------------------------------------------
		// ファイルマネージャーを生成
		pFileMgr = pCore->CreateFileMgr();
		// コアに設定
		pCore->SetFileManager( pFileMgr );
		// ルートのディレクトリを設定
		pFileMgr->SetLoadPath( 0, "Data", "Data.bin" );
		pFileMgr->SetCurrentDirectory( "2D\\DrawTexture" );

		//-----------------------------------------------------------------
		// 描画ステート
		//-----------------------------------------------------------------
		// 両面レンダリングOFF
		//   裏面をレンダリングするかどうかです。
		pRender->SetDoubleSide( false );
		// カラーキー処理OFF
		//   テクスチャカラーキー処理をするかどうかです。
		pRender->SetColorkeyEnable( false );
		// 描画モード設定
		//   描画モードを設定しています。
		//   ここではそのままの状態で描画します。
		pRender->SetDrawMode( DRAW_MODE_NORMAL );

		//-----------------------------------------------------------------
		// メインループ
		//-----------------------------------------------------------------
		// アプリケーションウィンドウのウィンドウメッセージの処理と、
		// ICoreインターフェイス経由で設定されたフレーム制御を行います。
		// またキー入力の更新や画面の更新もこの関数内で行われます。
		// この関数はウィンドウが終了されるとfalseを返します。
		// その場合、ただちにアプリケーションを終了するようにして下さい。
		while ( pCore->Run() )
		{
			/////////////////////////////////////////////////////////////// マウス入力処理

			// マウスの位置に絵を表示
			Px = Mouse.Px - (TEX_W / 2);
			Py = Mouse.Py - (TEX_H / 2);

			// 左クリックで赤
			if ( Mouse.ClickL )
			{
				Color = CColor(255,128,128);
			}
			// 右クリックで緑
			else if ( Mouse.ClickR )
			{
				Color = CColor(128,255,128);
			}
			//ホイールクリックで青

			else if ( Mouse.ClickW )
			{
				Color = CColor(128,128,255);
			}
			// 押されていない時はそのまま
			else
			{
				Color = CColor(255,255,255);
			}

			//////////////////////////////////////////////////////////////// 画面クリア

			// 裏画面のクリア
			pDevice->Clear( 0x00303030 );

			//////////////////////////////////////////////////////////////// 画面描画

			// 画面への描画を開始
			//   IRenderインターフェイスへ画面への描画を開始することを通知します。
			//   この関数を呼ばないと画面への描画が正しく行われません。
			pRender->Begin();

			// 画面への描画を完了
			//  IRenderインターフェイスに対して、
			//  画面への描画が完了したことを通知します。
			pRender->End();

			/////////////////////////////////////////////////////////////// 終わり
		}

EXIT:
		// ファイルマネージャー解放
		SAFE_RELEASE( pFileMgr );

		// マウス解放
		SAFE_RELEASE( pMouse );

		// レンダラーの解放
		SAFE_RELEASE( pRender );

		// デバイスの解放
		SAFE_RELEASE( pDevice );

		// グラフィックカードの解放
		SAFE_RELEASE( pGraphicCard );
	}

	// コアの解放
	SAFE_RELEASE( pCore );

	//--------------------------------------------------------
	// システムの解放
	//--------------------------------------------------------
	// アプリケーションの終了時に必ず呼び出して下さい。
	// またこの関数を呼び出す前に取得した全ての
	// インターフェイスを解放してください。
	CSystem::Finalize();

	return 0;
/*
	LUE_HANDLE hTex = INVALID_LUE_HANDLE;		// テクスチャハンドル
	LueRect Dst, Src;							// 描画用矩形
	long Px = (SCREEN_WIDTH  - TEX_W) / 2;		// 初期位置
	long Py = (SCREEN_HEIGHT - TEX_H) / 2;		// 初期位置
	LueMouseData Mouse;							// マウス用構造体
	unsigned long Color;						// 絵の色

	//--------------------------------------------------------
	// Lue初期化
	//--------------------------------------------------------
	if ( !Lue_Initialize(
			"Lue Sample Program",		// アプリケーション名
			SCREEN_WIDTH,				// ウィンドウ横幅
			SCREEN_HEIGHT,				// ウィンドウ縦幅
			FRAME_RATE,					// フレームレート（1秒間のフレーム数）
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
	LueFile_SetCurrentDirectory( "2D\\DrawTexture" );

	//--------------------------------------------------------
	// テクスチャの読み込み
	//--------------------------------------------------------
	// テクスチャ生成用のオプション設定
	LueTexture_SetConfig( LFALSE, LUE_ARGB(0,0,0,0) );

	// 画像ファイルからテクスチャ読み込み
	//  DirectXで扱うテクスチャのサイズは２の階乗である必要があります。
	//  １辺のピクセル数が 1、2、4、8、16、32、64、128、256、512、1024、2048 である必要があります。
	hTex = LueTexture_CreateFromFile( "Sample.bmp" );

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
		/////////////////////////////////////////////////////////////// マウス入力処理

		// マウス情報を取得
		Mouse = LueInput_GetMouseData();

		// マウスの位置に絵を表示
		Px = Mouse.Px - (TEX_W / 2);
		Py = Mouse.Py - (TEX_H / 2);

		// 左クリックで赤
		if ( Mouse.ClickL )
		{
			Color = CColor(255,128,128);
		}
		// 右クリックで緑
		else if ( Mouse.ClickR )
		{
			Color = CColor(128,255,128);
		}
		//ホイールクリックで青

		else if ( Mouse.ClickW )
		{
			Color = CColor(128,128,255);
		}
		// 押されていない時はそのまま
		else
		{
			Color = CColor(255,255,255);
		}

		/////////////////////////////////////////////////////////////// 描画処理

		// 描画開始宣言
		LueRender_SceneStart( LSCENE_2D_FOREGROUND );	// 2D前景でシーン開始

		// 描画位置
		Dst.Px = Px;
		Dst.Py = Py;
		Dst.Sx = TEX_W;
		Dst.Sy = TEX_H;
		// テクスチャ参照位置
		Src.Px = 0;
		Src.Py = 0;
		Src.Sx = TEX_W;
		Src.Sy = TEX_H;
		// 読み込んだテクスチャを画面に描画
		LueTexture_Draw( hTex, Dst, Src, Color );

		// 描画終了宣言
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// 終了処理
	//--------------------------------------------------------
	// 読み込んだテクスチャを解放
	LueTexture_Release( hTex );

	//--------------------------------------------------------
	// Lue終了
    //   Lueで使用している全データを解放します。
	//--------------------------------------------------------
	Lue_Finalize();
*/
	return 0;
}


