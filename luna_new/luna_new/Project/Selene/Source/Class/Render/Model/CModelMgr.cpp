

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CCore.h"
#include "File/CFileManager.h"
#include "Render/Model/CModel.h"
#include "Render/Model/CModelMgr.h"
#include "Render/Model/CModelLoader.h"

#if ENABLE_3D

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
CModelMgr::CModelMgr( CDevice *pDevice ) : CDeviceObjectMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CModelMgr::~CModelMgr()
{
}

//-----------------------------------------------------------------------------------
/**
	指定した名前をもつテクスチャの検索をします

	@param pFileName		[in] モデル名

	@retval NULL		同名のテクスチャは存在しない
	@retval NULL以外	同名のテクスチャオブジェクト

	指定した名前を持つテクスチャを検索します。<BR>
	本体の名前が同一でもファイルパスが違う場合は<BR>
	違うファイルとして識別されます。
*/
//-----------------------------------------------------------------------------------
CModel *CModelMgr::SearchInstance( const wchar_t *pFileName )
{
	return (CModel*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
	@brief モデル生成
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
CModel *CModelMgr::CreateFromFile( const wchar_t *pFileName, CRender *pRender )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());
	CModel *pModel = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"モデル" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"ファイルが見つかりません" );
	}
	else
	{
		pModel = SearchInstance( FilePath );
		if ( pModel != NULL )
		{
			Log_Print( 0x000000, L"同一ファイル[%s]を取得", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, L"%s", FilePath );

			void *pData = NULL;
			Uint32 Size;

			pModel = new CModel( pRender, this );
			CModelLoader Loader( pModel );
			if ( !pFileMgr->Load( pFileName, &pData, &Size ) )
			{
				SAFE_RELEASE( pModel );
			}
			ef( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
			{
				SAFE_RELEASE( pModel );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, L"完了" );
				pModel->SetName( FilePath );
			}

			pFileMgr->Free( pData );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}

//-----------------------------------------------------------------------------------
/**
	@brief モデル生成
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
CModel *CModelMgr::CreateFromMemory( const void *pData, Uint32 Size, CRender *pRender )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"モデル" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"メモリ上の画像から生成" );

	CModel *pModel = new CModel( pRender, this );
	CModelLoader Loader( pModel );
	if( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
	{
		SAFE_RELEASE( pModel );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}

#endif // ENABLE_3D
