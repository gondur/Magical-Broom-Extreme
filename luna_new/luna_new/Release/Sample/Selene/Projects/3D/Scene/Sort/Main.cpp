

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

#define SPHERE_SIZE				(10)


//----------------------------------------------------------------------------------
// PROTOTYPE
//----------------------------------------------------------------------------------
static void CreateSphere( IPrimitive3D *pPrimitive, Float fSx, Float fSy, Float fSz, Uint32 Slices, Uint32 Stacks );


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
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IPrimitive3D *pPrimitive	= NULL;
	ISceneManager *pSceneMgr	= NULL;
	ISceneCamera *pCamera		= NULL;

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
		pSceneMgr = pRender->CreateSceneManager();
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
		pCamera->UpdateProjection( 1.0f, 1000.0f, DEG_TO_ANGLE(45), SCREEN_WIDTH, SCREEN_HEIGHT );

		//-----------------------------------------------------------------
		// 描画オブジェクト生成
		//-----------------------------------------------------------------
		// 3Dプリミティブを生成
		//   IPrimitive3Dは最も低レベルならインターフェイスです。
		//   自分で頂点データ、インデックスデータを設定しレンダリングを行います。
		//   VERTEX_ELEMENT_3DBASE       位置・色の含まれた必須フラグです。
		pPrimitive = pRender->CreatePrimitive3D( 1500, 6000, VERTEX_ELEMENT_3DBASE, false );

		// 球生成
		//   関数内で球のデータを作成しています。
		// データ追加開始
		pPrimitive->Begin();
		// 球生成
		CreateSphere( pPrimitive, SPHERE_SIZE, SPHERE_SIZE, SPHERE_SIZE, 24, 24 );
		// データ追加完了
		pPrimitive->End();

		// マテリアルの色を変更
		//   ここでは半透明に
		pPrimitive->SetMaterialColor( CColor(255,255,255,128) );

		//-----------------------------------------------------------------
		// 描画ステート
		//-----------------------------------------------------------------
		// 描画モード設定
		//   描画モードを設定しています。
		//   半透明ブレンドON
		pRender->SetDrawType( DRAW_TYPE_BLEND );

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
			////////////////////////////////////////////////////////////////////////////////////////////

			// 裏画面のクリア
			pDevice->Clear( 0x00303030 );

			////////////////////////////////////////////////////////////////////////////////////////////

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

			////////////////////////////////////////////////////////////////////////////////////////////

			// シーン情報リセット
			//   ISceneManagerインターフェイスを使ったシーン管理情報を初期化します。
			pSceneMgr->Reset();

			// カメラの移動・回転
			//   CStyleクラスで変換をかけたものを
			//   カメラに渡します。
			CVector3D vEye( Math::Cos(pCore->GetSyncCount()*64)*300.0f, 70.0f, Math::Sin(pCore->GetSyncCount()*64)*300.0f );
			CVector3D vAt( 0.0f, 1.0f, 0.0f );
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

			// シーン管理
			//   ISceneManagerインターフェイスを使ったシーン管理を開始します。
			//   半透明のモデルを描画するので正しく出るようにソートを行う。
			pSceneMgr->Begin( true );

			// フォグOFF
			//   シーンへのフォグの適用のOFF
			pSceneMgr->SetFogEnable( false );

			// レンダリング
			//   IPrimitive3Dインターフェイスの内容を描画します。
			//   この関数ではIRenderインターフェイスに関連付けられたISceneManagerインターフェイスに対して
			//   描画リクエストを発行するだけで、描画を待たずに帰ってきます。

			Sint32 Cnt = 4;
			for ( Sint32 i = -Cnt; i <= +Cnt; i++ )
			{
				for ( Sint32 j = -Cnt; j <= +Cnt; j++ )
				{
					// プリミティブの変換処理
					//   CStyleの変換をIPrimitive3Dに渡しています。
					Style.TransformReset();
					Style.Translation( toF(i*25), 0.0f, toF(j*25) );
					Style.TransformUpdate();

					pPrimitive->SetTransform( Style );
					pPrimitive->Rendering();
				}
			}

			// シーン管理を終了
			//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
			pSceneMgr->End();

			////////////////////////////////////////////////////////////////////////////////////////////
		}

EXIT:
		// プリミティブの解放
		SAFE_RELEASE( pPrimitive );

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

//----------------------------------------------------------------------------------
/**
*/
//----------------------------------------------------------------------------------
void CreateSphere( IPrimitive3D *pPrimitive, Float fSx, Float fSy, Float fSz, Uint32 Slices, Uint32 Stacks )
{
	SVertex3DBase v1;
	SVertex3DTexture v2;
	SVertex3DLight v3;

	CVector3D vTemp;
	CMatrix Mtx;

	pPrimitive->Begin();

	//=============================================================
	// 頂点データ生成
	//=============================================================
	{
		Float fHorz = PI2 / (Stacks);
		Float fVert = PI  / (Slices-1);

		Sint32 Num = 0;
		for ( Uint32 i = 0; i < Slices; i++ )
		{
			CVector3D Vertex( 0, 1, 0 );

			Mtx.RotationX( PI_TO_ANGLE(fVert * i) );
			vTemp.TransformNormal( Vertex, Mtx );

			for ( Uint32 j = 0; j < Stacks+1; j++ )
			{
				Mtx.RotationY( PI_TO_ANGLE( PI2 - fHorz * j ) );
				Vertex.TransformCoord( vTemp, Mtx );

				CVector3D vNorm;
				CVector3D vPos( Vertex.x * fSx, Vertex.y * fSy, Vertex.z * fSz );
				CVector2D vUV( 1.0f - toF(j)/toF(Stacks), (1.0f - Vertex.y) * 0.5f );
				vNorm.Normalize( vPos );

				v1.Pos = vPos;							// 頂点座標
				v1.Col = 0xFFFFFFFF;					// 頂点色
				v2.TexColor = vUV;						// テクスチャUV
				v2.TexLight = vUV;						// テクスチャUV
				v3.Norm = vNorm;						// 法線

				pPrimitive->Push( &v1, 1 );
				pPrimitive->Push( &v2, 1 );
				pPrimitive->Push( &v3, 1 );

				Num++;
			}
		}
	}

	//=============================================================
	// インデックス生成
	//=============================================================
	{
		Sint32 Num = 0;
		for ( Uint32 i = 1; i < Slices; i++ )
		{
			for ( Uint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks+1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pPrimitive->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}
	}

	pPrimitive->End();
}



