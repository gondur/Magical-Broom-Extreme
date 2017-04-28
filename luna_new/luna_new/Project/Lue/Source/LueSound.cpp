

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueSound.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// PROTOTYPE
//------------------------------------------------------------------------------------------------
extern ICore *Lue_GetCore( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const Uint32 SOUND_MAX = 1024;


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ISound *g_pSound[SOUND_MAX];


//------------------------------------------------------------------------------------------------
/**
	@brief サウンド処理の初期化
	@author 葉迩倭

	@param hWnd		[in] メインウィンドウのウィンドウハンドル

	サウンド処理の初期化をします。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Initialize( void )
{
	for ( Sint32 i = 0; i < SOUND_MAX; i++ )
	{
		g_pSound[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief サウンド処理の解放
	@author 葉迩倭

	サウンド処理の解放をします。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Finalize( void )
{
	for ( Sint32 i = 0; i < SOUND_MAX; i++ )
	{
		if ( g_pSound[i] != NULL )
		{
			g_pSound[i]->Release();
			g_pSound[i] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief 未使用サウンドの検索
	@author 葉迩倭

	@return 未使用のサウンドハンドル

	未使用のサウンドオブジェクトの検索をします。
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueSound_SearchFreeHandle( void )
{
	for ( Sint32 i = 0; i < SOUND_MAX; i++ )
	{
		if ( g_pSound[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルからサウンドを読み込み、<BR>
	そのサウンドのハンドルを取得します。
	@author 葉迩倭

	@param pFileName	[in] ファイル名
	@param IsAllActive	[in] LTRUE にするとウィンドウが非アクティブでも停止しない

	@return 未使用のサウンドハンドル

	サウンドファイルを読み込み、そのサウンドの操作用のハンドルを取得します。<BR>
	取得したサウンドは不要になったら解放して下さい。
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueSound_CreateFromFile( const char *pFileName, eLueBool IsAllActive )
{
	LUE_HANDLE Handle = LueSound_SearchFreeHandle();
	if ( Handle >= SOUND_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFileName, wTemp );
	g_pSound[Handle] = Lue_GetCore()->CreateSoundFromFile( wTemp, IsAllActive != LFALSE );
	if ( g_pSound[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief サウンドを解放します。
	@author 葉迩倭

	@param Handle	[in] サウンドハンドル

	読み込んだサウンドをメモリから解放します。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Release( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Release();
	g_pSound[Handle] = NULL;
}


//------------------------------------------------------------------------------------------------
/**
	@brief サウンドを再生開始
	@author 葉迩倭

	@param Handle	[in] サウンドハンドル

	読み込んだサウンドをメモリから解放します。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Play( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Play( 0, 0 );
}


//------------------------------------------------------------------------------------------------
/**
	@brief サウンドをループ再生開始
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param LoopCount	[in] ループ回数<BR>無限ループの場合は SOUND_LOOP_INFINITY を指定。
	@param LoopSample	[in] ループ開始位置（サンプリング数で指定）

	サウンドのループ再生を行います。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Loop( LUE_HANDLE Handle, unsigned int LoopCount, unsigned int LoopSample )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Play( LoopCount, LoopSample );
}


//------------------------------------------------------------------------------------------------
/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	再生中のサウンドを停止します。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Stop( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Stop();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	再生中のサウンドを停止します。
*/
//------------------------------------------------------------------------------------------------
void LueSound_Pause( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Pause();
}


//------------------------------------------------------------------------------------------------
/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param fParam		[in] ボリューム値(+0～+100)

	再生中のサウンドを停止します。
*/
//------------------------------------------------------------------------------------------------
void LueSound_SetVolume( LUE_HANDLE Handle, float fParam )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->SetVolume( fParam );
}


//------------------------------------------------------------------------------------------------
/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param fParam		[in] パン値(-100～+100)

	再生中のサウンドを停止します。
*/
//------------------------------------------------------------------------------------------------
void LueSound_SetPan( LUE_HANDLE Handle, float fParam )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->SetPan( fParam );
}


//------------------------------------------------------------------------------------------------
/**
	@brief サウンドが再生中であるかチェック
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	@retval true		再生中（一時停止含む）
	@retval false		停止中

	再生中のサウンドであるかどうかを調べます。
*/
//------------------------------------------------------------------------------------------------
eLueBool LueSound_IsPlay( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return LFALSE;
	if ( g_pSound[Handle] == NULL ) return LFALSE;

	return g_pSound[Handle]->IsPlay() ? LTRUE : LFALSE;
}


} // extern "C"

