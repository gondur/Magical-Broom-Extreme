

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
#define SCREEN_WIDTH			(512)
#define SCREEN_HEIGHT			(512)

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
	IFileManager *pFileMgr		= NULL;
	IGraphicCard *pGraphicCard	= NULL;
	IDevice *pDevice			= NULL;
	IRender *pRender			= NULL;
	IPrimitive3D *pPrimitive	= NULL;
	ISceneManager *pSceneMgr	= NULL;
	ISceneCamera *pCamera		= NULL;
	ITexture *pTexture			= NULL;

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
		pFileMgr->SetCurrentDirectory( L"3D\\Primitive" );

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
		//   VERTEX_ELEMENT_3DTEXTURE    ２つのテクスチャUVの含まれたオプションフラグです。
		//   VERTEX_ELEMENT_3DLIGHT      ライティングをするための法線を含むオプションフラグです。
		//   VERTEX_ELEMENT_3DANIMATION  フラグはアニメーションを行うためのボーンウェイト及びインデックスを含むオプションフラグです。
		pPrimitive = pRender->CreatePrimitive3D( 1500, 6000, VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT | VERTEX_ELEMENT_3DANIMATION, false );

		// 球生成
		//   関数内で球のデータを作成しています。
		// データ追加開始
		pPrimitive->Begin();
		// 球生成
		CreateSphere( pPrimitive, SPHERE_SIZE, SPHERE_SIZE, SPHERE_SIZE, 24, 24 );
		// データ追加完了
		pPrimitive->End();

		//-----------------------------------------------------------------
		// テクスチャ読み込み
		//-----------------------------------------------------------------
		pTexture = pRender->CreateTextureFromFile( L"Sample.bmp" );

		//-----------------------------------------------------------------
		// 描画ステート
		//-----------------------------------------------------------------
		// フィルタリング
		//   3D用のそこそこ高画質なフィルタを使用します。
		pRender->SetTextureFilterType( 0, TEXTURE_FILTER_ANISOTROPY_LOW );

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
			pDevice->Clear( 0x00303030 );

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
			CVector3D vEye( 0.0f, 10.0f, -40.0f );
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

			// 平行光源
			//   シーンに対して平行光源を設定します。
			CVector3D vDir( 1.0f, -1.0f, 1.0f );
			CVector3D vCol( 0.7f, 0.7f, 0.7f );
			pSceneMgr->SetDirectionLight( vDir, vCol );
			// アンビエント
			// 半球ライティングを行っているので、天球と地表の照り返しの色を設定します。
			CVector3D vColSky( 0.3f, 0.3f, 0.7f );
			CVector3D vColEarth( 0.7f, 0.3f, 0.3f );
			pSceneMgr->SetAmbientLight( vColSky, vColEarth );

			/////////////////////////////////////////////////////////////////////////////////////////////
			// シーンへのレンダリングリクエスト
			/////////////////////////////////////////////////////////////////////////////////////////////

			// シーン管理
			//   ISceneManagerインターフェイスを使ったシーン管理を開始します。
			pSceneMgr->Begin( false );

			// ボーン設定
			//   IPrimitive3Dインターフェイスに対してボーンの情報を設定します。
			CMatrix mOff, mBone[2];
			mOff.Identity();
			mBone[0].Identity();
			mBone[1].RotationY( toI(Math::Sin( pCore->GetSyncCount() * 256 ) * toF(DEG_TO_ANGLE(180))) );
			pPrimitive->SetBoneCount( 2 );
			pPrimitive->SetBoneOffsetMatrix( 0, mOff );
			pPrimitive->SetBoneTransformMatrix( 0, mBone[0] );
			pPrimitive->SetBoneOffsetMatrix( 1, mOff );
			pPrimitive->SetBoneTransformMatrix( 1, mBone[1] );

			// テクスチャ設定
			//   レンダラーに対して使用するテクスチャを設定します。
			pRender->SetTexture( 0, pTexture );

			// レンダリング
			//   IPrimitive3Dインターフェイスの内容を描画します。
			//   この関数ではIRenderインターフェイスに関連付けられたISceneManagerインターフェイスに対して
			//   描画リクエストを発行するだけで、描画を待たずに帰ってきます。
			pPrimitive->Rendering();

			// シーン管理を終了
			//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
			pSceneMgr->End();

			/////////////////////////////////////////////////////////////////////////////////////////////
		}

EXIT:
		// テクスチャの解放
		SAFE_RELEASE( pTexture );

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

//----------------------------------------------------------------------------------
/**
*/
//----------------------------------------------------------------------------------
void CreateSphere( IPrimitive3D *pPrimitive, Float fSx, Float fSy, Float fSz, Uint32 Slices, Uint32 Stacks )
{
	SVertex3DBase v1;
	SVertex3DTexture v2;
	SVertex3DLight v3;
	SVertex3DAnimation v4;

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

				// 高さに応じてウェイト設定
				v4.Index[0] = 0;
				v4.Index[1] = 1;
				v4.Weight = ((vPos.y + SPHERE_SIZE) / 2.0f) / SPHERE_SIZE;

				v1.Pos = vPos;							// 頂点座標
				v1.Col = 0xFFFFFFFF;					// 頂点色
				v2.TexColor = vUV;						// テクスチャUV
				v2.TexLight = vUV;						// テクスチャUV
				v3.Norm = vNorm;						// 法線

				pPrimitive->Push( &v1, 1 );
				pPrimitive->Push( &v2, 1 );
				pPrimitive->Push( &v3, 1 );
				pPrimitive->Push( &v4, 1 );

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
