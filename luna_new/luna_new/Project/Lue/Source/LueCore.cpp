

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueCore.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
#define VERSION_NO_HIGH		0
#define VERSION_NO_LOW		1


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern HINSTANCE GetDLLInstance( void );
extern void LueTexture_Initialize( void );
extern void LueTexture_Finalize( void );
extern void LueSurface_Initialize( void );
extern void LueSurface_Finalize( void );
extern void LueFontSprite2D_Initialize( void );
extern void LueFontSprite2D_Finalize( void );
extern void LueSprite2D_Initialize( void );
extern void LueSprite2D_Finalize( void );
extern void LuePrimitive2D_Initialize( void );
extern void LuePrimitive2D_Finalize( void );
extern void LueLinePrimitive2D_Initialize( void );
extern void LueLinePrimitive2D_Finalize( void );
extern void LuePointPrimitive2D_Initialize( void );
extern void LuePointPrimitive2D_Finalize( void );
extern void LueSound_Initialize( void );
extern void LueSound_Finalize( void );
extern void LueRender_Initialize( void );
extern void LueRender_Finalize( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ICore *g_pCore				= NULL;
static IGraphicCard *g_pGraphicCard	= NULL;
static IDevice *g_pDevice			= NULL;
static IRender *g_pRender			= NULL;
static IFileManager *g_pFileMgr		= NULL;
static IMouse *g_pMouse				= NULL;
static IKeyboard *g_pKeyboard		= NULL;


//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムの初期化を行います
	@author 葉迩倭

	@param pAppName		[in] アプリケーション名
	@param ScreenW		[in] 画面横幅
	@param ScreenH		[in] 画面縦幅
	@param FrameRate	[in] フレームレート
	@param IsWindowMode	[in] ウィンドウモードで起動するかどうか
	@param Type			[in] 使用するAPI（現在は LAPI_TYPE_DIRECTX9 固定）

	@retval LTRUE	初期化成功
	@retval LFALSE	初期化失敗

	Lueシステムの初期化処理を行います。<BR>
	この関数が完了した段階ですべてのLue系の関数を使うことが可能になります。
*/
//------------------------------------------------------------------------------------------------
eLueBool Lue_Initialize( const char *pAppName, unsigned int ScreenW, unsigned int ScreenH, eLueFrameRata FrameRate, eLueBool IsWindowMode, eLueAPIType Type )
{
	HICON hIcon;
	wchar_t wTemp[128] = L"";
	MBCStoWCS( pAppName, wTemp );

	// 多重起動は許可しない
	if ( !System::BlockDualBoot( wTemp ) )
	{
		::MessageBox( ::GetDesktopWindow(), L"既に同名のアプリケーションが起動しています。", L"エラー", MB_ICONERROR );
		return LFALSE;
	}

	// システム初期化
	if ( !System::Initialize() ) goto EXIT;

	// コアの生成
	g_pCore = System::CreateCore();
	if ( g_pCore == NULL ) goto EXIT;

	// コアの初期化
	if ( !g_pCore->Initialize( wTemp, (eFrameRate)FrameRate ) )
	{
		goto EXIT;
	}

	// グラフィックカードを取得
	g_pGraphicCard = g_pCore->CreateGraphicCard( 0, VERTEXSHADER_VERSION_2_0 );
	if ( g_pGraphicCard == NULL ) goto EXIT;

	// アイコン
	hIcon = (HICON)::LoadImage( GetDLLInstance(), L"ICON_SMALL", IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( g_pCore->GetWindowHandle(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon );
	hIcon = (HICON)::LoadImage( GetDLLInstance(), L"ICON_BIG", IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( g_pCore->GetWindowHandle(), WM_SETICON, ICON_BIG, (LPARAM)hIcon );

	g_pCore->Start( ScreenW, ScreenH, IsWindowMode != LFALSE );

	g_pDevice = g_pGraphicCard->CreateDevice();
	if ( g_pDevice == NULL ) goto EXIT;

	// レンダラーを取得
	g_pRender = g_pDevice->CreateRender();
	if ( g_pRender == NULL ) goto EXIT;

	// 各オブジェクト初期化
	LueSurface_Initialize();
	LueTexture_Initialize();
	LueLinePrimitive2D_Initialize();
	LuePointPrimitive2D_Initialize();
	LuePrimitive2D_Initialize();
	LueSprite2D_Initialize();
	LueFontSprite2D_Initialize();
	LueSound_Initialize();

	// レンダラー初期化
	LueRender_Initialize();

	// ファイル登録
	g_pFileMgr = g_pCore->CreateFileMgr();
	g_pCore->SetFileManager( g_pFileMgr );

	// マウス取得
	g_pMouse = g_pCore->GetMouse();

	// キーボード取得
	g_pKeyboard = g_pCore->GetKeyboard();

	return LTRUE;

EXIT:
	Lue_Finalize();

	return LFALSE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムの終了
	@author 葉迩倭

	Lueシステムをすべて解放します。<BR>
	この関数が呼ばれた後にLue系の関数を呼び出すことは禁止されています。
*/
//------------------------------------------------------------------------------------------------
void Lue_Finalize( void )
{
	LueRender_Finalize();

	LueFontSprite2D_Finalize();
	LueSprite2D_Finalize();
	LuePrimitive2D_Finalize();
	LueLinePrimitive2D_Finalize();
	LuePointPrimitive2D_Finalize();
	LueTexture_Finalize();
	LueSurface_Finalize();
	LueSound_Finalize();

	// キーボード解放
	SAFE_RELEASE( g_pKeyboard );

	// マウス解放
	SAFE_RELEASE( g_pMouse );

	// ファイル解放
	SAFE_RELEASE( g_pFileMgr );

	// レンダラー解放
	SAFE_RELEASE( g_pRender );

	// デバイス解放
	SAFE_RELEASE( g_pDevice );

	// ビデオカード
	SAFE_RELEASE( g_pGraphicCard );

	// コア解放
	SAFE_RELEASE( g_pCore );

	// システム終了
	System::Finalize();
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムで使用しているコアオブジェクト取得
	@author 葉迩倭

	@return Lueコアインターフェース

	システム内部で使用しているLueのコアを取得します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
ICore *Lue_GetCore( void )
{
	return g_pCore;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムで使用しているデバイス取得
	@author 葉迩倭

	@return Lueデバイスインターフェース

	システム内部で使用しているLueのデバイスを取得します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
IDevice *Lue_GetDevice( void )
{
	return g_pDevice;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムで使用しているレンダラー取得
	@author 葉迩倭

	@return Lueレンダラーインターフェース

	システム内部で使用しているLueのレンダラーを取得します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
IRender *Lue_GetRenderer( void )
{
	return g_pRender;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムで使用しているマウス取得
	@author 葉迩倭

	@return Lueマウスインターフェース

	システム内部で使用しているLueのマウスを取得します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
IMouse *Lue_GetMouse( void )
{
	return g_pMouse;
}


//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムで使用しているキーボード取得
	@author 葉迩倭

	@return Lueキーボードインターフェース

	システム内部で使用しているLueのキーボードを取得します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
IKeyboard *Lue_GetKeyboard( void )
{
	return g_pKeyboard;
}

//------------------------------------------------------------------------------------------------
/**
	@brief Lueシステムのメイン処理
	@author 葉迩倭

	@param IsActive	[in] LTRUE の時、フォーカスを失っても動作し続ける。

	@retval LTRUE	アプリケーション動作中
	@retval LFALSE	アプリケーション停止

	Lueシステムのメイン処理を行います。<BR>
	毎フレーム呼び出すようにしてください。<BR>
	また返り値がLFALSEのときは直ちにメインループから抜けて下さい。
*/
//------------------------------------------------------------------------------------------------
eLueBool Lue_Run( eLueBool IsActive )
{
	// メッセージ処理
	if ( !Lue_GetCore()->Run( IsActive != LFALSE ) )
	{
		return LFALSE;
	}

	g_pDevice->Clear();

	return LTRUE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief バージョン文字列取得
	@author 葉迩倭

	@param pStr		[out] バージョン文字列格納先
	@param Size		[in] pStrのバッファサイズ

	Lueのバージョンを文字列で取得します。<BR>
	この関数を呼び出すことで DLL のバージョンを取得することが可能です。
*/
//------------------------------------------------------------------------------------------------
void Lue_GetVersionString( char *pStr, unsigned int Size )
{
	sprintf_s( pStr, Size, "\"Lue for DirectX9.0c\" Phase %02d.%02d", VERSION_NO_HIGH, VERSION_NO_LOW );
}

//------------------------------------------------------------------------------------------------
/**
	@brief バージョン番号取得
	@author 葉迩倭

	@return バージョン番号

	Lueのバージョンを数値で取得します。<BR>
	上位16Bitにメジャーバージョン、下位16Bitにマイナーバージョンが格納されています。
*/
//------------------------------------------------------------------------------------------------
unsigned int Lue_GetVersionNumber( void )
{
	return (VERSION_NO_HIGH << 16) | (VERSION_NO_LOW << 0);
}

//------------------------------------------------------------------------------------------------
/**
	@brief OS起動からの時間取得
	@author 葉迩倭

	@return 1/1000秒単位の時間

	OSが起動してからの時間を取得します。<BR>
	32Bit変数なので約48日で1周して0に戻ってしまいます。
*/
//------------------------------------------------------------------------------------------------
unsigned int Lue_GetTime( void )
{
	return ::timeGetTime();
}


} // extern "C"

