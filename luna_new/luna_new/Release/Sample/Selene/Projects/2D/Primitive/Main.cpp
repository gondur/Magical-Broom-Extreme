

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

#define PRIMITIVE_MAX	(64)		// プリミティブ数


//=============================================================================
/**
	@brief メイン関数

	@param hInstance		[in] 現在のインスタンスのハンドル
	@param hPrevInstance	[in] 以前のインスタンスのハンドル
	@param lpCmdPoint		[in] コマンドプリミティブ
	@param nCmdShow			[in] 表示状態

	コンソールアプリケーションでいう所の main() 関数です。
	ウィンドウズアプリケーションでは以下の関数が main() になります。
*/
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdPoint, int nCmdShow )
{
	unsigned long ColTbl[] = {
		LUE_RGB(255,128,128), LUE_RGB(128,255,128), LUE_RGB(128,128,255),
	};

	LUE_HANDLE hPrimitive;
	LuePrimitiveVertex2D Prim[2];
	unsigned long Time;
	long i, Angle;

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
	// プリミティブ用描画オブジェクト生成
	//--------------------------------------------------------
	hPrimitive = LuePrimitive2D_Create( PRIMITIVE_MAX );

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
		Time = Lue_GetTime() * 8;

		///////////////////////////////////////////////////////////////// プリミティブへの描画リクエスト

		// プリミティブへの描画開始を通知
		LuePrimitive2D_Begin( hPrimitive );

		// 背景（右上）
		Prim[0].v[0].Pos.x = 0.0f;
		Prim[0].v[0].Pos.y = 0.0f;
		Prim[0].v[0].Pos.z = 0.0f;
		Prim[0].v[0].Pos.w = 1.0f;
		Prim[0].v[0].Col = LUE_RGB(255,64,64);
		Prim[0].v[1].Pos.x = (float)SCREEN_WIDTH;
		Prim[0].v[1].Pos.y = 0.0f;
		Prim[0].v[1].Pos.z = 0.0f;
		Prim[0].v[1].Pos.w = 1.0f;
		Prim[0].v[1].Col = LUE_RGB(64,255,64);
		Prim[0].v[2].Pos.x = (float)SCREEN_WIDTH;
		Prim[0].v[2].Pos.y = (float)SCREEN_HEIGHT;
		Prim[0].v[2].Pos.z = 0.0f;
		Prim[0].v[2].Pos.w = 1.0f;
		Prim[0].v[2].Col = LUE_RGB(64,64,255);
		// 背景（左下）
		Prim[1].v[0].Pos.x = 0.0f;
		Prim[1].v[0].Pos.y = 0.0f;
		Prim[1].v[0].Pos.z = 0.0f;
		Prim[1].v[0].Pos.w = 1.0f;
		Prim[1].v[0].Col = LUE_RGB(64,64,255);
		Prim[1].v[1].Pos.x = 0.0f;
		Prim[1].v[1].Pos.y = (float)SCREEN_HEIGHT;
		Prim[1].v[1].Pos.z = 0.0f;
		Prim[1].v[1].Pos.w = 1.0f;
		Prim[1].v[1].Col = LUE_RGB(64,255,64);
		Prim[1].v[2].Pos.x = (float)SCREEN_WIDTH;
		Prim[1].v[2].Pos.y = (float)SCREEN_HEIGHT;
		Prim[1].v[2].Pos.z = 0.0f;
		Prim[1].v[2].Pos.w = 1.0f;
		Prim[1].v[2].Col = LUE_RGB(255,64,64);
		// バッファに追加
		LuePrimitive2D_Push( hPrimitive, Prim, 2 );

		// 左で回転
		for ( i = 0; i < 3; i++ )
		{
			Angle = Time + (i * LUE_ANGLE_MAX / 3);
			Prim[0].v[i].Pos.x = (LueMath_Cos( Angle ) * 150.0f) + 160.0f;
			Prim[0].v[i].Pos.y = (LueMath_Sin( Angle ) * 200.0f) + 240.0f;
			Prim[0].v[i].Pos.z = 0.0f;
			Prim[0].v[i].Pos.w = 1.0f;
			Prim[0].v[i].Col = ColTbl[i];
		}
		// バッファに追加
		LuePrimitive2D_Push( hPrimitive, Prim, 1 );

		// プリミティブへの描画完了を通知
		LuePrimitive2D_End( hPrimitive );

		///////////////////////////////////////////////////////////////// レンダラーへの描画処理

		// 描画開始宣言
		LueRender_SceneStart( LSCENE_2D_BACKGROUND );	// 2D背景でシーン開始

		// テクスチャ設定無し
		LueRender_SetTexture( INVALID_LUE_HANDLE );

		// プリミティブバッファの内容を画面に描画
		LuePrimitive2D_Render( hPrimitive );

		// 描画終了宣言
		LueRender_SceneExit();

		///////////////////////////////////////////////////////////////// プリミティブへの描画リクエスト

		// プリミティブへの描画開始を通知
		LuePrimitive2D_Begin( hPrimitive );

		// 右で半透明回転
		for ( i = 0; i < 3; i++ )
		{
			Angle = Time + (i * LUE_ANGLE_MAX / 3);
			Prim[0].v[i].Pos.x = (LueMath_Cos( Angle ) * 150.0f) + 480.0f;
			Prim[0].v[i].Pos.y = (LueMath_Sin( Angle ) * 200.0f) + 240.0f;
			Prim[0].v[i].Pos.z = 0.0f;
			Prim[0].v[i].Pos.w = 1.0f;
			Prim[0].v[i].Col = (ColTbl[i] & 0x00FFFFFF) | (0x80000000);
		}
		// バッファに追加
		LuePrimitive2D_Push( hPrimitive, Prim, 1 );

		// プリミティブへの描画完了を通知
		LuePrimitive2D_End( hPrimitive );

		///////////////////////////////////////////////////////////////// レンダラーへの描画処理

		// 描画開始宣言
		LueRender_SceneStart( LSCENE_2D_FOREGROUND );	// 2D前景でシーン開始

		// 半透明ON
		LueRender_SetDrawMode( LDRAW_MODE_BLEND );

		// テクスチャ設定無し
		LueRender_SetTexture( INVALID_LUE_HANDLE );

		// プリミティブバッファの内容を画面に描画
		LuePrimitive2D_Render( hPrimitive );

		// 描画終了宣言
		LueRender_SceneExit();
	}

	//--------------------------------------------------------
	// プリミティブオブジェクト解放
	//--------------------------------------------------------
	LuePrimitive2D_Release( hPrimitive );

	//--------------------------------------------------------
	// Lue終了
    //   Lueで使用している全データを解放します。
	//--------------------------------------------------------
	Lue_Finalize();

	return 0;
}


