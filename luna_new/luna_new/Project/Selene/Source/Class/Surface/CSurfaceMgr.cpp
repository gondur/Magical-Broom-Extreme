

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Surface/CSurface.h"
#include "Surface/CSurfaceMgr.h"


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
CSurfaceMgr::CSurfaceMgr( CDevice *pDevice ) : CDeviceObjectMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CSurfaceMgr::~CSurfaceMgr()
{
}

//-----------------------------------------------------------------------------------
/**
	@brief 深度ステンシルバッファを生成
	@author 葉迩倭

	@param Width	[in] 横幅
	@param Height	[in] 縦幅
	@param Format	[in] フォーマット

	@retval true	成功
	@retval false	失敗

	深度ステンシル用のサーフェイス生成します。
*/
//-----------------------------------------------------------------------------------
CSurface *CSurfaceMgr::CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"マテリアル" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"深度ステンシルバッファを生成" );

	CSurface *pSurf = new CSurface( this );

	if ( !pSurf->CreateDepthStencil( Width, Height, Format ) )
	{
		SAFE_RELEASE( pSurf );
		return NULL;
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CeateDepthStencil [%dx%d] %s", pSurf->GetSize().x, pSurf->GetSize().y, GetPixelFormat(pSurf->GetFormat()) );
		pSurf->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSurf;
}

//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲットバッファを生成
	@author 葉迩倭

	@param Width		[in] 横幅
	@param Height		[in] 縦幅
	@param Format		[in] フォーマット
	@param pCopyTarget	[in] コピーを行う場合のコピー先のマテリアル

	@retval true	成功
	@retval false	失敗

	レンダリングターゲット用のサーフェイス生成します。<BR>
	pCopyTargetがNULLではない時、自動的にCopy()メソッドによる<BR>
	ハードウェアフォーマット変換に対応しているフォーマットで生成されます。
	またマテリアルフォーマットが出来ない場合はこの関数は失敗します。
*/
//-----------------------------------------------------------------------------------
CSurface *CSurfaceMgr::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format, CSurface *pCopyTarget )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"マテリアル" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"レンダリング用バッファを生成" );

	CSurface *pSurf = new CSurface( this );

	if ( pSurf->CreateRenderTarget( Width, Height, Format, pCopyTarget ) )
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateRenderTarget [%dx%d] %s", pSurf->GetSize().x, pSurf->GetSize().y, GetPixelFormat(pSurf->GetFormat()) );
		pSurf->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"完了" );
	}
	else
	{
		SAFE_RELEASE( pSurf );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSurf;
}

