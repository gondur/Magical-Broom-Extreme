
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueTexture.h"

//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;

//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {

//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const Uint32 TEXTURE_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ITexture *g_pTextureTbl[TEXTURE_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャ管理クラス初期化
	@author 葉迩倭

	テクスチャ関連の処理を初期化します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueTexture_Initialize( void )
{
	for ( Sint32 i = 0; i < TEXTURE_MAX; i++ )
	{
		g_pTextureTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャ管理クラス終了
	@author 葉迩倭

	テクスチャ関連の処理を終了します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueTexture_Finalize( void )
{
	for ( Uint32 i = 0; i < TEXTURE_MAX; i++ )
	{
		if ( g_pTextureTbl[i] != NULL )
		{
			g_pTextureTbl[i]->Release();
			g_pTextureTbl[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief 未使用テクスチャの検索
	@author 葉迩倭

	@return 未使用のテクスチャハンドル

	未使用のテクスチャオブジェクトの検索をします。<BR>
	※この関数は公開されていません。
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < TEXTURE_MAX; i++ )
	{
		if ( g_pTextureTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャクラスのインターフェースを取得
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル

	@return テクスチャクラスのインターフェース

	指定したテクスチャハンドルが所有するテクスチャインターフェースクラスを取得します。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
ITexture *LueTexture_Get( LUE_HANDLE Handle )
{
	if ( Handle >= TEXTURE_MAX ) return NULL;
	return g_pTextureTbl[Handle];
}



//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャ生成用コンフィグ設定
	@author 葉迩倭

	@param IsMipmap	[in] ミップマップの有無
	@param Color	[in] カラーキーの色（0で抜け設定なし

	テクスチャ生成用の設定を行います。
*/
//------------------------------------------------------------------------------------------------
void LueTexture_SetConfig( unsigned int Color )
{
	CTextureConfig Conf;
	Conf.SetColorKey( Color );
	Conf.SetFormat( FORMAT_TEXTURE_2D );

	Lue_GetRenderer()->SetTextureConfig( Conf );
}


//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャの解放
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル

	テクスチャの解放を行います。
*/
//------------------------------------------------------------------------------------------------
void LueTexture_Release( LUE_HANDLE Handle )
{
	if ( Handle >= TEXTURE_MAX ) return;

	if ( g_pTextureTbl[Handle] != NULL )
	{
		g_pTextureTbl[Handle]->Release();
		g_pTextureTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param Width	[in] テクスチャの横幅
	@param Height	[in] テクスチャの縦幅

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	指定したサイズのテクスチャの生成を行います。<BR>
	サイズは２の階乗である必要があります。　
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_Create( unsigned int Width, unsigned int Height )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTexture( Width, Height );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// 完了
		return Handle;
	}

	// 失敗なので解放
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	画像ファイルからテクスチャの生成を行います。<BR>
	サポートしている画像フォーマットは TGA/PNG/JPG/DDS/BMP です。<BR>
	サイズは２の階乗である必要があります。　
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_CreateFromFile( const char *pFileName )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFileName, wTemp );

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTextureFromFile( wTemp );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// 完了
		return Handle;
	}

	// 失敗なので解放
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param pData	[in] テクスチャファイルの格納されたメモリのアドレス
	@param Size		[in] pDataのデータサイズ

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	メモリ内の画像ファイルからテクスチャの生成を行います。<BR>
	サポートしている画像フォーマットは TGA/PNG/JPG/DDS/BMP です。<BR>
	サイズは２の階乗である必要があります。　
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_CreateFromMemory( void *pData, unsigned int Size )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTextureFromMemory( pData, Size );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// 完了
		return Handle;
	}

	// 失敗なので解放
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param Width	[in] テクスチャの横幅
	@param Height	[in] テクスチャの縦幅

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	レンダリングターゲットとしてテクスチャを生成します。<BR>
	レンダリングターゲットとして生成されたテクスチャに対しては<BR>
	直接レンダリングする事が可能です。<BR>
	サイズは２の階乗である必要があります。　
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueTexture_CreateRenderTarget( unsigned int Width, unsigned int Height )
{
	LUE_HANDLE Handle = LueTexture_SearchFreeHandle();
	if ( Handle >= TEXTURE_MAX ) return INVALID_LUE_HANDLE;

	g_pTextureTbl[Handle] = Lue_GetRenderer()->CreateTextureRenderTarget( Width, Height );
	if ( g_pTextureTbl[Handle] != NULL )
	{
		// 完了
		return Handle;
	}

	// 失敗なので解放
	LueTexture_Release( Handle );

	return INVALID_LUE_HANDLE;
}

//------------------------------------------------------------------------------------------------
/**
	@brief テクスチャの設定
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル

	レンダラーに対して描画に使用するテクスチャを設定します。<BR>
	INVALID_LUE_HANDLE を指定するとテクスチャを使わないようになります。<BR>
	また逆に INVALID_LUE_HANDLE を指定するまで設定したテクスチャが<BR>
	使われる続ける事になります。
	さらに LueSprite2D や LueFontSprite2D のように内部でテクスチャを<BR>
	自動的に切り替える関数を呼び出した後は変更されたままになっていますので<BR>
	アプリケーション側で使用する際には再度設定するようにして下さい。<BR>
	※この関数は公開されていません。
*/
//------------------------------------------------------------------------------------------------
void LueTexture_SetRender( LUE_HANDLE Handle )
{
	if ( (Handle >= TEXTURE_MAX) )
	{
		Lue_GetRenderer()->SetTexture( 0, NULL );
	}
	else
	{
		Lue_GetRenderer()->SetTexture( 0, g_pTextureTbl[Handle] );
	}
}


} // extern "C"

