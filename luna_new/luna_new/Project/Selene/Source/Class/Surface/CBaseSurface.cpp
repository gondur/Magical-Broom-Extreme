

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Surface/CBaseSurface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭

	@param pMgr		[in] オブジェクト管理クラス
*/
//-----------------------------------------------------------------------------------
CBaseSurface::CBaseSurface( CBaseMgr *pMgr ) : CDeviceObject( pMgr )
	, m_IsLock				( false )
	, m_Size				( 0, 0 )
	, m_SurfaceType			( SURFACE_TYPE_INVALID )
{
	MemoryClear( &m_ImageInfo, sizeof(m_ImageInfo) );
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CBaseSurface::~CBaseSurface()
{
}


//-----------------------------------------------------------------------------------
/**
	@brief ベースサーフェイスに画像イメージを展開
	@author 葉迩倭

	@param pSurface		[in/out] サーフェイス展開先
	@param pData		[in] 画像データ
	@param Size			[in] データサイズ
	@param Width		[in] 画像横サイズ
	@param Height		[in] 画像縦サイズ
	@param KeyColor		[in] カラーキー色

	@return 結果（HRESULT型

	指定のシステムメモリ上のサーフェイスに対して<BR>
	メモリ上の画像データを展開します。
*/
//-----------------------------------------------------------------------------------
HRESULT CBaseSurface::LoadImageToBaseSurface( IDirect3DSurface9 *pSurface, const void *pData, Uint32 Size, Uint32 Width, Uint32 Height, CColor KeyColor )
{
	HRESULT hr;
	RECT Dst = { 0, 0, Width, Height };
	RECT Src = { 0, 0, m_ImageInfo.Width, m_ImageInfo.Height };

	//------------------------------------------------------
	// オフスクリーンサーフェイスに画像データをロード
	//------------------------------------------------------
	hr = ::D3DXLoadSurfaceFromFileInMemory(
				pSurface,
				NULL,
				&Dst,
				pData,
				Size,
				&Src,
				D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER,
				(D3DCOLOR)KeyColor,
				NULL );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"データが開けません　[ %s ]", GetD3DError(hr) );
		return false;
	}

	return hr;
}

//-----------------------------------------------------------------------------------
/**
	@brief メモリ用の画像ファイルからイメージ情報を取得
	@author 葉迩倭

	@param pData	[in] 画像データ
	@param Size		[in] 画像データサイズ

	@retval true	成功
	@retval false	失敗

	メモリ上の画像ファイルからサイズやフォーマット等の<BR>
	イメージデータを取得します。
*/
//-----------------------------------------------------------------------------------
Bool CBaseSurface::GetImageInfoFromMemory( const void *pData, Uint32 Size )
{
	HRESULT hr;

	//--------------------------------------------------------------
	// ファイル情報取得
	//--------------------------------------------------------------
	hr = ::D3DXGetImageInfoFromFileInMemory( pData, Size, &m_ImageInfo );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"ファイルが開けません　[ %s ]", GetD3DError(hr) );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief 画像データの横サイズを取得
	@author 葉迩倭

	@return 横サイズ

	読み込んでいる画像データの横サイズを取得します。
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseSurface::GetImageWidth( void )
{
	return m_ImageInfo.Width;
}

//-----------------------------------------------------------------------------------
/**
	@brief 画像データの縦サイズを取得
	@author 葉迩倭

	@return 縦サイズ

	読み込んでいる画像データの縦サイズを取得します。
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseSurface::GetImageHeight( void )
{
	return m_ImageInfo.Height;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャサイズを取得
	@author 葉迩倭

	@return サイズ

	読み込んでいる画像データを展開してるテクスチャのサイズを取得します。
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CBaseSurface::GetSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャフォーマットを取得
	@author 葉迩倭

	@return フォーマット

	読み込んでいる画像データを展開してるテクスチャのフォーマットを取得します。
*/
//-----------------------------------------------------------------------------------
D3DFORMAT CBaseSurface::GetFormat( void )
{
	return m_Format;
}

