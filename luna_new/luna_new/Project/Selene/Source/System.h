

#ifndef ___SELENE__SYSTEM___
#define ___SELENE__SYSTEM___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Core/CCore.h"
#include "Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace System
{
	/**
		@brief システム初期化
		@author 葉迩倭
		@retval true	成功
		@retval false	失敗

		Seleneシステムの初期化を行います。
	*/
	SELENE_DLL_API Bool Initialize( void );

	/**
		@brief システム終了
		@author 葉迩倭

		Seleneシステムの終了をします。
	*/
	SELENE_DLL_API void Finalize( void );

	/**
		@brief 多重起動ブロック
		@author 葉迩倭
		@param pApplicationName	[in] アプリケーション名
		@retval false	既に同名のアプリケーションが起動している
		@retval true	同名のアプリケーションは存在しない

		返り値false時にアプリケーションを終了させることで<BR>
		多重起動を防止することができます。
	*/
	SELENE_DLL_API Bool BlockDualBoot( const wchar_t *pApplicationName );

	/**
		@brief SSE2サポート有無
		@author 葉迩倭
		@retval false	SSE2をサポートしていない
		@retval true	SSE2をサポートしている

		SSE2をサポートしているかどうかを調べます。
	*/
	SELENE_DLL_API Bool IsSuportSSE( void );

	/**
		@brief カレントディレクトリリセット
		@author 葉迩倭

		カレントディレクトリをアプリケーションの実行フォルダに設定します。
	*/
	SELENE_DLL_API void ResetCurrentDirectory( void );

	/**
		@brief ディレクトリ生成
		@author 葉迩倭
		@param pPath	[in] フォルダパス

		指定パスへディレクトリを生成します。<BR>
		途中のフォルダが存在しない場合、全ての階層に対してフォルダを作成していきます。
	*/
	SELENE_DLL_API void CreateDirectory( const wchar_t *pPath );

	/**
		@brief Coreの取得
		@author 葉迩倭
		@return ICoreインターフェイス

		ウィンドウを管理するICoreクラスを生成/取得します。<BR>
		現在、１つのICoreしか生成できません。
	*/
	SELENE_DLL_API ICore *CreateCore( void );
}
}


#endif // ___SELENE__SYSTEM___

