

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "File/CFileManager.h"
#include "Surface/CTextureMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭

	@param pDevice	[in] 関連付けられたデバイス
*/
//-----------------------------------------------------------------------------------
CTextureMgr::CTextureMgr( CDevice *pDevice ) : CDeviceObjectMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CTextureMgr::~CTextureMgr()
{
}

//-----------------------------------------------------------------------------------
/**
	指定した名前をもつテクスチャの検索をします

	@param pFileName		[in] テクスチャ名

	@retval NULL		同名のテクスチャは存在しない
	@retval NULL以外	同名のテクスチャオブジェクト

	指定した名前を持つテクスチャを検索します。<BR>
	本体の名前が同一でもファイルパスが違う場合は<BR>
	違うファイルとして識別されます。
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::SearchInstance( const wchar_t *pFileName )
{
	return (CTexture*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ生成
	@author 葉迩倭

	@param Width	[in] テクスチャ横幅
	@param Height	[in] テクスチャ縦幅
	@param Format	[in] テクスチャフォーマット

	@retval NULL		失敗
	@retval NULL以外	テクスチャオブジェクト

	空のテクスチャを生成します。
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"空のテクスチャを生成" );

	CTexture *pTex = new CTexture( this );
	if ( !pTex->Create( Width, Height, Format ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"Create [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲットテクスチャ生成
	@author 葉迩倭

	@param Width	[in] テクスチャ横幅
	@param Height	[in] テクスチャ縦幅
	@param Format	[in] テクスチャフォーマット

	@retval NULL		失敗
	@retval NULL以外	テクスチャオブジェクト

	レンダリングターゲット用のテクスチャを生成します。
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"レンダリングターゲットを生成" );

	CTexture *pTex = new CTexture( this );
	if ( !pTex->CreateRenderTarget( Width, Height, Format ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateRenderTarget [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval NULL		失敗
	@retval NULL以外	テクスチャオブジェクト

	テクスチャファイルからテクスチャを生成します。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());
	CTexture *pTex = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"テクスチャ" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"ファイルが見つかりません" );
	}
	else
	{
		pTex = SearchInstance( FilePath );
		if ( pTex != NULL )
		{
			Log_Print( 0x000000, L"同一ファイル[%s]を取得", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, L"%s", FilePath );

			pTex = new CTexture( this );

			if ( !pTex->CreateFromFile( pFileName, Format, KeyColor ) )
			{
				SAFE_RELEASE( pTex );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, L"完了" );
				pTex->SetName( FilePath );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ生成
	@author 葉迩倭

	@param pData		[in] データのポインタ
	@param Size			[in] pDataのデータサイズ
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval NULL		失敗
	@retval NULL以外	テクスチャオブジェクト

	メモリ上のテクスチャファイルからテクスチャを生成します。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"メモリ上の画像から生成" );

	CTexture *pTex = new CTexture( this );

	if ( !pTex->CreateFromMemory( pData, Size, Format, KeyColor ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateFromMemory [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

CTexture *CTextureMgr::CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());
	CTexture *pTex = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"テクスチャ" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"ファイルが見つかりません" );
	}
	else
	{
		pTex = SearchInstance( FilePath );
		if ( pTex != NULL )
		{
			Log_Print( 0x000000, L"同一ファイル[%s]を取得", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, L"%s", FilePath );

			pTex = new CTexture( this );

			if ( !pTex->CreateTextureFromFileForNormalMap( pFileName, fHeight ) )
			{
				SAFE_RELEASE( pTex );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, L"完了" );
				pTex->SetName( FilePath );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

CTexture *CTextureMgr::CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"メモリ上の画像から生成" );

	CTexture *pTex = new CTexture( this );

	if ( !pTex->CreateTextureFromMemoryForNormalMap( pData, Size, fHeight ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateFromMemory [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}
