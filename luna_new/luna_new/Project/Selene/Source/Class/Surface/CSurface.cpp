

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Surface/CSurface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭

	@param pMgr		[in] クラス管理用マネージャー
*/
//-----------------------------------------------------------------------------------
CSurface::CSurface( CBaseMgr *pMgr ) : CBaseSurface( pMgr )
	, m_pSurface	( NULL )
	, m_BaseFormat	( FORMAT_INVALID )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CSurface::~CSurface()
{
	Log_PrintTable( 0xFF0000, 0x000000, L"解放", L"サーフェイス", m_Name );
	Log_TableLine( 1 );

	SAFE_RELEASE( m_pSurface );
}

//-----------------------------------------------------------------------------------
/**
	@brief デバイスリセット時の処理
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CSurface::OnLostDevice( void )
{
	SAFE_RELEASE( m_pSurface );
}


//-----------------------------------------------------------------------------------
/**
	@brief デバイスリストア時の処理
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CSurface::OnResetDevice( void )
{
	HRESULT hr = S_OK;

	switch ( m_SurfaceType )
	{
	case SURFACE_TYPE_RENDERTARGET:
		hr = GetDevicePointer()->CreateRenderTarget( m_Size.x, m_Size.y, m_Format, &m_pSurface );
		break;
	case SURFACE_TYPE_DEPTHSTENCIL:
		hr = GetDevicePointer()->CreateDepthStencilSurface( m_Size.x, m_Size.y, m_Format, &m_pSurface );
		break;
	}

	if FAILED( hr )
	{
		Log_PrintTable( 0xFF0000, 0x000000, L"エラー", L"サーフェイスのリストアに失敗 [ %s ]", GetD3DError(hr) );
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲットに設定
	@author 葉迩倭

	@retval true	成功
	@retval false	失敗

	サーフェイスをレンダリングターゲットとして設定します。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::SetRenderTarget( void )
{
	return SUCCEEDED( GetDevicePointer()->SetRenderTarget( m_pSurface ) );
}


//-----------------------------------------------------------------------------------
/**
	@brief 深度ステンシルバッファに設定
	@author 葉迩倭

	@retval true	成功
	@retval false	失敗

	サーフェイスを深度ステンシルサーフェイスとして設定します。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::SetDepthStencil( void )
{
	return SUCCEEDED( GetDevicePointer()->SetDepthStencilSurface( m_pSurface ) );
}

//-----------------------------------------------------------------------------------
/**
	@brief バックバッファにコピー
	@author 葉迩倭

	@retval true	成功
	@retval false	失敗

	サーフェイスをバックバッファにコピーします。<BR>
	ただし深度ステンシルサーフェイスやフォーマット変換に<BR>
	ハードウェアが対応していないフォーマットのサーフェイスでは<BR>
	失敗します。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::CopyToBackBuffer( void )
{
	HRESULT hr = GetDevicePointer()->CopyToBackBuffer( m_pSurface );
	return SUCCEEDED( hr );
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

	深度ステンシル用のサーフェイスを生成します。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;
	D3DFORMAT SurfFormat;

	//--------------------------------------------------------------
	// サーフェイス情報の生成
	//--------------------------------------------------------------
	SurfFormat = GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );

	//--------------------------------------------------------------
	// サーフェイス生成
	//--------------------------------------------------------------
	hr = GetDevicePointer()->CreateDepthStencilSurface(
									Width,
									Height,
									SurfFormat,
									&m_pSurface );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"サーフェイスの生成に失敗 [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );
		return false;
	}

	//--------------------------------------------------------------
	// データ設定
	//--------------------------------------------------------------
	m_BaseFormat	= Format;
	m_Format		= SurfFormat;
	m_Size.x			= Width;
	m_Size.y		= Height;
	m_SurfaceType	= SURFACE_TYPE_DEPTHSTENCIL;

	// ログ
	Log_PrintLine( 0x0000000, L"サイズ [%dx%d] フォーマット [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲットバッファを生成
	@author 葉迩倭

	@param Width		[in] 横幅
	@param Height		[in] 縦幅
	@param Format		[in] フォーマット
	@param pCopyTarget	[in] コピーを行う場合のコピー先のサーフェイス

	@retval true	成功
	@retval false	失敗

	レンダリングターゲット用のサーフェイスを生成します。<BR>
	pCopyTargetがNULLではない時、自動的にCopy()メソッドによる<BR>
	ハードウェアフォーマット変換に対応しているフォーマットで生成されます。
	またサーフェイスフォーマットが出来ない場合はこの関数は失敗します。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format, CSurface *pCopyTarget )
{
	HRESULT hr;
	D3DFORMAT SurfFormat;

	//--------------------------------------------------------------
	// サーフェイス情報の生成
	//--------------------------------------------------------------
	SurfFormat = GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN, pCopyTarget == NULL ? D3DFMT_UNKNOWN : pCopyTarget->GetFormat() );
	if ( SurfFormat == D3DFMT_UNKNOWN )
	{
		Log_PrintLine( 0xFF00000, L"有効なサーフェイスフォーマットが見つかりませんでした" );
		return false;
	}

	//--------------------------------------------------------------
	// サーフェイス生成
	//--------------------------------------------------------------
	hr = GetDevicePointer()->CreateRenderTarget(
									Width,
									Height,
									SurfFormat,
									&m_pSurface );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"サーフェイスの生成に失敗 [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );
		return false;
	}

	//--------------------------------------------------------------
	// データ設定
	//--------------------------------------------------------------
	m_BaseFormat	= Format;
	m_Format		= SurfFormat;
	m_Size.x			= Width;
	m_Size.y		= Height;
	m_SurfaceType	= SURFACE_TYPE_RENDERTARGET;

	// ログ
	Log_PrintLine( 0x0000000, L"サイズ [%dx%d] フォーマット [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief サーフェイスのコピー
	@author 葉迩倭

	@param pDstRect		[in] 転送先サーフェイスの矩形
	@param pSrc			[in] 転送元サーフェイス
	@param pSrcRect		[in] 転送元サーフェイスの矩形

	@retval true	成功
	@retval false	失敗

	サーフェイス同士の拡大縮小コピーを行います。<BR>
	サーフェイス間でフォーマットが異なる場合は<BR>
	ハードウェアのフォーマット変換のサポートがないと<BR>
	この関数は失敗します。<BR>
	またこのコピー処理にはいくつかの制限が存在します。<BR>
	・通常サーフェイスから通常サーフェイスの拡大縮小コピーはできません。<BR>
	・バックバッファから通常サーフェイスへのコピーはできません。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )
{
	RECT Dst = { 0, 0, m_Size.x, m_Size.y };
	RECT Src = { 0, 0, ((CSurface*)pSrc)->m_Size.x, ((CSurface*)pSrc)->m_Size.y };

	if ( pDstRect != NULL ) Dst = *pDstRect;
	if ( pSrcRect != NULL ) Src = *pSrcRect;

	if ( GetDevicePointer()->Clip( &Dst, &Src ) )
	{
		HRESULT hr = GetDevicePointer()->StretchRect(
							((CSurface*)pSrc)->m_pSurface,
							&Src,
							m_pSurface,
							&Dst,
							D3DTEXF_LINEAR );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief サーフェイス取得
	@author 葉迩倭

	@param ppSurface	[in] サーフェイス格納先

	サーフェイスインターフェイスを取得します。<BR>
	この関数で取得したサーフェイスは参照カウンタが<BR>
	インクリメントされるのでRelease()関数で解放する必要があります。
*/
//-----------------------------------------------------------------------------------
Bool CSurface::GetSurface( IDirect3DSurface9 **ppSurface )
{
	if ( m_pSurface != NULL )
	{
		m_pSurface->AddRef();
		*ppSurface = m_pSurface;
	}

	return *ppSurface != NULL;
}


