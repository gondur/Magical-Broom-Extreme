

//----------------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------------
#include "../../../../../../Include/Selene.h"


//----------------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------------
using namespace Selene;


//----------------------------------------------------------------------------------
// DEFINE
//----------------------------------------------------------------------------------
#define SCREEN_WIDTH			(640)
#define SCREEN_HEIGHT			(480)


//----------------------------------------------------------------------------------
/**
	一般的なウィンドウズアプリケーションでのmain()関数に相当するものです。

	@param hInstance		[in] インスタンスのハンドル
	@param hPrevInstance	[in] Win3.1時代の名残（NULL)
	@param lpCmdLine		[in] コマンドラインが格納された文字列へのポインタ
	@param nCmdShow			[in] ウィンドウをどのように表示するかの指定

	@return		終了コード
*/
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ICore *pCore				= NULL;
	IFileManager *pFileMgr		= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	ISceneManager *pSceneMgr	= NULL;
	ISceneCamera *pCamera		= NULL;
	IModel *pModel				= NULL;
	IModel *pModelEarth			= NULL;

	CStyle Style;

	//----------------------------------------------------------------------------
	// システムの初期化
	//----------------------------------------------------------------------------
	// Seleneのシステムを初期化しています。
	// 起動時に必ず呼び出してください。
	System::Initialize();

	//----------------------------------------------------------------------------
	// コアの生成
	//----------------------------------------------------------------------------
	// システムからICoreインターフェイスを取得しています。
	// アプリケーションウィンドウに関するインターフェイスであり、
	// システム内に１つだけ存在します。
	pCore = System::CreateCore();

	//----------------------------------------------------------------------------
	// 初期化
	//----------------------------------------------------------------------------
	// ICoreインターフェイスの初期化を行います。
	// アプリケーションウィンドウに関しての各種初期化が行われます。
	if ( pCore->Initialize( L"Selene Sample Program", FRAME_RATE_60 ) )
	{
		//-----------------------------------------------------------------
		// ファイル登録
		//-----------------------------------------------------------------
		// ファイルマネージャーを生成
		pFileMgr = pCore->CreateFileMgr();
		// コアに設定
		pCore->SetFileManager( pFileMgr );
		// 読み込み先ルートディレクトリ設定
		pFileMgr->SetLoadPath( 0, L"Data", L"Data.bin" );
		// ルートディレクトリに対して読み込むカレントディレクトリ設定
		pFileMgr->SetCurrentDirectory( L"3D\\Scene" );

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
		// シーン
		//-----------------------------------------------------------------
		// シーンマネージャーを取得
		//   レンダラーに関連付けられたシーン管理用のインターフェイスを取得します。
		//   3D空間そのものを管理しているので、モデルなどのレンダリングに必要とします。
		pSceneMgr = pRender->CreateSceneManager( SCENE_MODE_MANAGED, SCENE_MODE_OPTION_EDGE );
		pSceneMgr->SetRenderTargetSize( CPoint2D<Uint32>( SCREEN_WIDTH, SCREEN_HEIGHT ) );

		//-----------------------------------------------------------------
		// カメラ
		//-----------------------------------------------------------------
		// シーンからカメラを取得
		//   シーン1つに対して、1つのカメラを所持しています。
		//   シーンのカメラを操作するために、カメラのインターフェイスを
		//   シーンから取得します。
		pCamera = pSceneMgr->GetSceneCamera();
		// カメラのプロジェクションを設定
		//   カメラの見える範囲と見え方を設定します。
		//   見える範囲が広いほどＺバッファの精度の問題で
		//   ちらつき易くなるので注意して設定してください。
		pCamera->UpdateProjection( 1.0f, 150.0f, DEG_TO_ANGLE(45), SCREEN_WIDTH, SCREEN_HEIGHT );

		//-----------------------------------------------------------------
		// 描画オブジェクト生成
		//-----------------------------------------------------------------
		// モデルデータの読み込み
		//   Seleneでは専用のモデルフォーマットを採用しています。
		//   これは読み込み速度の高速化や各種付加情報を得るためです。
		//   ConvertX2SMFを使うことで、Xファイルからコンバートする事が可能です。
		pModel = pRender->CreateModelFromFile( L"cube.smf" );

		// 地形モデル
		pModelEarth = pRender->CreateModelFromFile( L"earth.smf" );

		//-----------------------------------------------------------------
		// 描画ステート
		//-----------------------------------------------------------------
		// フィルタリング
		//   3D用のそこそこ高画質なフィルタを使用します。
		pRender->SetTextureFilterType( MESH_TEXTURE_COLORMAP, TEXTURE_FILTER_ANISOTROPY_LOW );
		pRender->SetTextureFilterType( MESH_TEXTURE_NORMALMAP, TEXTURE_FILTER_ANISOTROPY_LOW );

		// 深度処理のステート設定
		//   深度バッファに関しての設定を行います。
		//   深度バッファへの書き込みを有効にし、
		//   深度バッファのテストを有効にしています。
		pRender->SetDepthTestEnable( true );
		pRender->SetDepthWriteEnable( true );

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
			/////////////////////////////////////////////////////////////////////////////////////////////
			// 画面クリア
			/////////////////////////////////////////////////////////////////////////////////////////////

			// 裏画面のクリア
			pDevice->Clear( 0x00000000 );

			/////////////////////////////////////////////////////////////////////////////////////////////
			// シーンマネージャーの内容を実際にレンダリング
			/////////////////////////////////////////////////////////////////////////////////////////////

			// 画面への描画を開始
			//   IRenderインターフェイスへ画面への描画を開始することを通知します。
			//   この関数を呼ばないと画面への描画が正しく行われません。
			pRender->Begin();

			// シーンの内容をレンダリング
			//   ここまでで構築されたシーン情報を元に実際に描画処理を行います。
			//   この関数はIRender::End()を呼び出す前でなければ失敗します。
			pSceneMgr->Rendering();

			// 画面への描画を完了
			//  IRenderインターフェイスに対して、
			//  画面への描画が完了したことを通知します。
			pRender->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
			// シーン情報構築
			/////////////////////////////////////////////////////////////////////////////////////////////

			// シーン情報リセット
			//   ISceneManagerインターフェイスを使ったシーン管理情報を初期化します。
			pSceneMgr->Reset();

			// カメラの移動・回転
			//   CStyleクラスで変換をかけたものを
			//   カメラに渡します。
			CVector3D vEye( 0.0f, 60.0f, -30.0f );
			CVector3D vAt( 0.0f, 0.0f, 0.0f );
			CVector3D vUp( 0.0f, 1.0f, 0.0f );
			Style.TransformReset();
			Style.LookAt( vEye, vAt, vUp );
			Style.TransformUpdate();
			// カメラの状態を初期化
			pCamera->Reset();
			// CStyleの変換を適用
			pCamera->SetTransform( Style );
			// カメラの内部データを利用可能な状態に更新
			//   この関数を呼ぶことで実際にこのカメラでのレンダリング可能になります。
			pCamera->Update();

			// 平行光源
			//   シーンに対して平行光源を設定します。
			CVector3D vDir( 1.0f, -1.0f, 1.0f );
			CVector3D vCol( 0.7f, 0.7f, 0.7f );
			pSceneMgr->SetDirectionLight( vDir, vCol );
			// アンビエント
			// 半球ライティングを行っているので、天球と地表の照り返しの色を設定します。
			CVector3D vColSky( 0.3f, 0.3f, 0.7f );
			CVector3D vColEarth( 0.2f, 0.1f, 0.1f );
			pSceneMgr->SetAmbientLight( vColSky, vColEarth );

			/////////////////////////////////////////////////////////////////////////////////////////////
			// シーンへのレンダリングリクエスト
			/////////////////////////////////////////////////////////////////////////////////////////////

			// シーン管理
			//   ISceneManagerインターフェイスを使ったシーン管理を開始します。
			pSceneMgr->Begin( false );

			// 地形レンダリング
			//   IModelインターフェイスの内容を描画します。
			//   この関数ではIRenderインターフェイスに関連付けられたISceneManagerインターフェイスに対して
			//   描画リクエストを発行するだけで、描画を待たずに帰ってきます。
			Style.TransformReset();
			Style.TransformUpdate();
			pModelEarth->SetTransform( Style );
			pModelEarth->Rendering();

			// レンダリング
			//   IModelインターフェイスの内容を描画します。
			//   この関数ではIRenderインターフェイスに関連付けられたISceneManagerインターフェイスに対して
			//   描画リクエストを発行するだけで、描画を待たずに帰ってきます。
			Sint32 Cnt = 3;
			Sint32 Angle = 0;
			for ( Sint32 i = -Cnt; i <= +Cnt; i++ )
			{
				for ( Sint32 j = -Cnt; j <= +Cnt; j++ )
				{
					CPoint2D<Float> Pos( toF(i*10), toF(j*10) );
					Pos = Pos.Rotate( pCore->GetSyncCount() * 32 );

					// プリミティブの変換処理
					//   CStyleの変換をIPrimitive3Dに渡しています。
					Style.TransformReset();
					Style.Translation( Pos.x, 10.0f, Pos.y );
					Style.RotationX( Angle + (pCore->GetSyncCount() * 128) );
					Style.RotationY( Angle + (pCore->GetSyncCount() *  64) );
					Style.TransformUpdate();

					pModel->SetTransform( Style );
					pModel->Rendering();

					Angle += 4096;
				}
			}

			// シーン管理を終了
			//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
			pSceneMgr->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
		}

EXIT:
		// モデルの解放
		SAFE_RELEASE( pModelEarth );
		SAFE_RELEASE( pModel );

		// カメラの解放
		SAFE_RELEASE( pCamera );

		// シーンマネージャー解放
		SAFE_RELEASE( pSceneMgr );

		// レンダラーの解放
		SAFE_RELEASE( pRender );

		// デバイスの解放
		SAFE_RELEASE( pDevice );

		// グラフィックカードの解放
		SAFE_RELEASE( pGraphicCard );

		// ファイルマネージャー解放
		SAFE_RELEASE( pFileMgr );
	}

	// コアの解放
	SAFE_RELEASE( pCore );

	//--------------------------------------------------------
	// システムの解放
	//--------------------------------------------------------
	// アプリケーションの終了時に必ず呼び出して下さい。
	// またこの関数を呼び出す前に取得した全ての
	// インターフェイスを解放してください。
	System::Finalize();

	return 0;
}

