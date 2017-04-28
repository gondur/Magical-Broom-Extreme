

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Render/CRender.h"
#include "File/CFileManager.h"
#include "Surface/CTexture.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭

	@param pMgr		[in] 管理用マネージャー
*/
//-----------------------------------------------------------------------------------
CTexture::CTexture( CBaseMgr *pMgr ) : CBaseSurface( pMgr )
	, m_Pool					( D3DPOOL_DEFAULT )
	, m_pTexture				( NULL )
	, m_pBaseTexture			( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CTexture::~CTexture()
{
	Log_PrintTable( 0xFF0000, 0x000000, L"解放", L"テクスチャ", m_Name );
	Log_TableLine( 1 );

	SAFE_RELEASE( m_pBaseTexture );
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
	@brief 画像情報からテクスチャ生成
	@author 葉迩倭

	@param pData		[in] データのポインタ
	@param Size			[in] pDataのデータサイズ
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval false		失敗
	@retval true		成功

	メモリ上のテクスチャ情報からテクスチャを生成します。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateTextureFromImageInfo( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	HRESULT hr;
	IDirect3DSurface9 *pSurface;
	D3DSURFACE_DESC Desc;

	//------------------------------------------------------------
	// テクスチャ
	//------------------------------------------------------------
	m_Size			= GetGraphicCardPointer()->GetTextureSize( CPoint2D<Uint32>( m_ImageInfo.Width, m_ImageInfo.Height ) );
	m_Format		= GetGraphicCardPointer()->GetFormat( Format, m_ImageInfo.Format );
	m_Pool			= D3DPOOL_MANAGED;
	m_SurfaceType	= SURFACE_TYPE_OFFSCREEN;

	//------------------------------------------------------------
	// テクスチャの生成
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					3,
					0,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"テクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	//------------------------------------------------------------
	// サーフェイスに画像読み込み
	//------------------------------------------------------------
	Uint32 Max = m_pTexture->GetLevelCount();
	for ( Uint32 i = 0; i < Max; i++ )
	{
		// サーフェイス取得
		hr = m_pTexture->GetSurfaceLevel( i, &pSurface );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, L"サーフェイスの取得に失敗しました [ %s ]", GetD3DError(hr) );
			SAFE_RELEASE( m_pTexture );
			return false;
		}

		// サーフェイス情報取得
		pSurface->GetDesc( &Desc );

		// サーフェイスに画像データ読み込み
		hr = LoadImageToBaseSurface( pSurface, pData, Size, Desc.Width, Desc.Height, KeyColor );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, L"画像の読み込みに失敗しました [ %s ]", GetD3DError(hr) );
			SAFE_RELEASE( pSurface );
			SAFE_RELEASE( m_pTexture );
			return false;
		}

		SAFE_RELEASE( pSurface );
	}

	// ログ
	Log_PrintLine( 0x0000000, L"サイズ [%dx%d] フォーマット [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ読み込み
	@author 葉迩倭

	@param pData		[in] データのポインタ
	@param Size			[in] pDataのデータサイズ
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval false		失敗
	@retval true		成功

	メモリ上のテクスチャファイルからテクスチャを読み込みます。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::LoadImageFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	SAFE_RELEASE( m_pTexture );

	//--------------------------------------------------------
	// 画像データをオフスクリーンサーフェイスに読み込み
	//--------------------------------------------------------
	if ( !GetImageInfoFromMemory( pData, Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	//--------------------------------------------------------
	// テクスチャを生成
	//--------------------------------------------------------
	if ( !CreateTextureFromImageInfo( pData, Size, Format, KeyColor ) )
	{
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ読み込み
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval false		失敗
	@retval true		成功

	テクスチャファイルからテクスチャを読み込みます。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::LoadImageFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor )
{
	void *pData = NULL;
	Uint32 Size;

	SAFE_RELEASE( m_pTexture );

	//--------------------------------------------------------
	// ファイルから読み込み
	//--------------------------------------------------------
	if ( !GetCorePointer()->GetFileMgrPointer()->Load( pFileName, &pData, &Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		GetCorePointer()->GetFileMgrPointer()->Free( pData );
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, L"ファイルが開けません" );

		return false;
	}

	//--------------------------------------------------------
	// 画像データをオフスクリーンサーフェイスに読み込み
	//--------------------------------------------------------
	if ( !GetImageInfoFromMemory( pData, Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		GetCorePointer()->GetFileMgrPointer()->Free( pData );
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, L"画像データの展開に失敗" );

		return false;
	}

	//--------------------------------------------------------
	// テクスチャを生成
	//--------------------------------------------------------
	if ( !CreateTextureFromImageInfo( pData, Size, Format, KeyColor ) )
	{
		GetCorePointer()->GetFileMgrPointer()->Free( pData );
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, L"テクスチャの生成に失敗" );

		return false;
	}

	GetCorePointer()->GetFileMgrPointer()->Free( pData );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ生成
	@author 葉迩倭

	@param Width	[in] テクスチャ横幅
	@param Height	[in] テクスチャ縦幅
	@param Format	[in] テクスチャフォーマット

	@retval false		失敗
	@retval true		成功

	空のテクスチャを生成します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;

	//------------------------------------------------------------
	// イメージ情報
	//------------------------------------------------------------
	m_ImageInfo.Format		= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_ImageInfo.Width		= Width;
	m_ImageInfo.Height		= Height;
	m_Format				= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_Pool					= D3DPOOL_MANAGED;
	m_SurfaceType			= SURFACE_TYPE_OFFSCREEN;
	m_Size					= GetGraphicCardPointer()->GetTextureSize( CPoint2D<Uint32>( m_ImageInfo.Width, m_ImageInfo.Height ) );

	//------------------------------------------------------------
	// テクスチャの生成
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					0,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L" テクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );

		return false;
	}

	// ログ
	Log_PrintLine( 0x0000000, L"サイズ [%dx%d] フォーマット [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲットテクスチャ生成
	@author 葉迩倭

	@param Width	[in] テクスチャ横幅
	@param Height	[in] テクスチャ縦幅
	@param Format	[in] テクスチャフォーマット

	@retval false		失敗
	@retval true		成功

	レンダリングターゲット用のテクスチャを生成します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;

	//------------------------------------------------------------
	// イメージ情報
	//------------------------------------------------------------
	m_ImageInfo.Format		= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_ImageInfo.Width		= Width;
	m_ImageInfo.Height		= Height;
	m_Format				= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_SurfaceType			= SURFACE_TYPE_RENDERTARGET;
	m_Pool					= D3DPOOL_DEFAULT;
	m_Size					= GetGraphicCardPointer()->GetTextureSize( CPoint2D<Uint32>( m_ImageInfo.Width, m_ImageInfo.Height ) );

	//------------------------------------------------------------
	// ベーステクスチャ生成
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					0,
					m_Format,
					D3DPOOL_SYSTEMMEM,
					&m_pBaseTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"ベーステクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );

		return false;
	}

	//------------------------------------------------------------
	// テクスチャの生成
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"テクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );

		return false;
	}

	// ログ
	Log_PrintLine( 0x0000000, L"サイズ [%dx%d] フォーマット [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval false		失敗
	@retval true		成功

	テクスチャファイルからテクスチャを生成します。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor )
{
	//--------------------------------------------------------------
	// ファイルを読み込み、そこからデータを取得する
	//--------------------------------------------------------------
	if ( LoadImageFromFile( pFileName, Format, KeyColor ) )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ生成
	@author 葉迩倭

	@param pData		[in] データのポインタ
	@param Size			[in] pDataのデータサイズ
	@param Format		[in] テクスチャフォーマット
	@param KeyColor		[in] カラーキーとして使う色（0で無効）

	@retval false		失敗
	@retval true		成功

	メモリ上のテクスチャファイルからテクスチャを生成します。<BR>
	対応しているテクスチャファイルはTGA/BMP/DDS/PNG/JPGです。<BR>
	またテクスチャサイズは2のべき乗の必要があり、<BR>
	これに当てはまらないサイズの場合は、内部でリサイズされて管理されます。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	//--------------------------------------------------------------
	// テクスチャ読み込み
	//--------------------------------------------------------------
	if ( LoadImageFromMemory( pData, Size, Format, KeyColor ) )
	{
		return true;
	}

	return false;
}

Bool CTexture::ConvertNormalMap( Float fHeight )
{
	Bool IsRet = false;
	IDirect3DTexture9 *pTexNew;
	HRESULT hr;

	struct PIXEL32 {
		Uint8 b, g, r, a;
	};

	//--------------------------------------------------------
	// フォーマットチェック
	//--------------------------------------------------------
	if ( (m_Format != D3DFMT_X8R8G8B8) && (m_Format != D3DFMT_A8R8G8B8) )
	{
		return false;
	}

	//--------------------------------------------------------
	// テクスチャ生成
	//--------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					3,
					0,
					m_Format,
					m_Pool,
					&pTexNew );
	if FAILED( hr )
	{
		goto EXIT;
	}

	//--------------------------------------------------------
	// 法線マップ生成
	//--------------------------------------------------------
	hr = D3DXComputeNormalMap(
					pTexNew,
					m_pTexture,
					NULL,
					0,
					D3DX_CHANNEL_LUMINANCE,
					fHeight );
	if FAILED( hr ) 
	{
		goto EXIT;
	}

	//--------------------------------------------------------
	// アルファ成分に高さデータを入れておく
	//--------------------------------------------------------
	// 転送元ロック
	D3DLOCKED_RECT SrcRc;
	hr = m_pTexture->LockRect( 0, &SrcRc, NULL, 0 );
	if SUCCEEDED( hr )
	{
		// 転送先ロック
		D3DLOCKED_RECT DstRc;
		hr = pTexNew->LockRect( 0, &DstRc, NULL, 0 );
		if SUCCEEDED( hr )
		{
			Uint32 w = m_Size.x;
			Uint32 h = m_Size.y;
			PIXEL32 *pSrc = (PIXEL32*)SrcRc.pBits;
			PIXEL32 *pDst = (PIXEL32*)DstRc.pBits;
			// アルファ部分に高さデータを入れておく
			for ( Uint32 y = 0; y < h; y++ )
			{
				for ( Uint32 x = 0; x < w; x++ )
				{
					Uint32 r = pSrc[x].r;
					Uint32 g = pSrc[x].g;
					Uint32 b = pSrc[x].b;
					pDst[x].a = (Uint8)((r + g + b) / 3);
				}
				pDst += w;
				pSrc += w;
			}
			pTexNew->UnlockRect( 0 );
		}
		m_pTexture->UnlockRect( 0 );
	}

	IsRet = true;

EXIT:
	//--------------------------------------------------------
	// 新しいテクスチャをコピー
	//--------------------------------------------------------
	if ( IsRet )
	{
		SAFE_RELEASE( m_pTexture );
		m_pTexture = pTexNew;
	}
	else
	{
		SAFE_RELEASE( pTexNew );
	}

	return IsRet;
}

Bool CTexture::CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )
{
	//--------------------------------------------------------------
	// ファイルを読み込み、そこからデータを取得する
	//--------------------------------------------------------------
	if ( LoadImageFromFile( pFileName, FORMAT_TEXTURE32, 0x00000000 ) )
	{
		return ConvertNormalMap( fHeight );
	}

	return false;
}

Bool CTexture::CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )
{
	//--------------------------------------------------------------
	// テクスチャ読み込み
	//--------------------------------------------------------------
	if ( LoadImageFromMemory( pData, Size, FORMAT_TEXTURE32, 0x00000000 ) )
	{
		return ConvertNormalMap( fHeight );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief デバイスリセット時処理
	@author 葉迩倭

	デバイスがロストした場合の処理を行います。
*/
//-----------------------------------------------------------------------------------
void CTexture::OnLostDevice( void )
{
	if ( m_Pool == D3DPOOL_DEFAULT )
	{
		SAFE_RELEASE( m_pTexture );
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief デバイスリストア時処理
	@author 葉迩倭

	デバイスがロストから復旧した場合の処理を行います。
*/
//-----------------------------------------------------------------------------------
void CTexture::OnResetDevice( void )
{
	HRESULT hr = S_OK;

	switch ( m_SurfaceType )
	{
	case SURFACE_TYPE_RENDERTARGET:
		hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					D3DPOOL_DEFAULT,
					&m_pTexture );
		break;
	case SURFACE_TYPE_OFFSCREEN:
		if ( m_Pool == D3DPOOL_DEFAULT )
		{
			hr = GetDevicePointer()->CreateTexture(
						m_Size.x,
						m_Size.y,
						1,
						0,
						m_Format,
						D3DPOOL_DEFAULT,
						&m_pTexture );

			UpdateTexture();
		}
		break;
	}

	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"テクスチャの生成に失敗しました [ %s ]", GetD3DError(hr) );
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャロック
	@author 葉迩倭

	@param pRect	[in] ロック対象の矩形
	@param ppBits	[out] ロック後のテクスチャのポインタ
	@param pPitch	[out] テクスチャのピッチ（横のバイト数）
	@param pWidth	[out] テクスチャの横幅
	@param pHeight	[out] テクスチャの縦幅
	@param pFormat	[out] テクスチャのフォーマット

	バックアップ用システムメモリのテクスチャをロックし、<BR>
	直接ピクセルデータをいじれるようにします。＜BR>
	ロックされている間は自由にいじる事が出来ますが、<BR>
	ロック中は一切の描画が行えません。<BR>
	またUnlock()後にUpdateTexture()することで反映されます。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::LockRect( RECT *pRect, void **ppBites, Uint32 *pPitch, Uint32 *pWidth, Uint32 *pHeight, D3DFORMAT *pFormat )
{
	HRESULT hr;

	if ( m_pTexture != NULL )
	{
		if ( m_IsLock )
		{
			Log_PrintLine( 0xFF00000, L"テクスチャは既にロックされています" );
		}
		else
		{
			// レンダリングターゲットの場合はシステムにコピ－
			DownloadRenderTarget();

			// ロック
			D3DLOCKED_RECT LockRect;
			if ( m_pBaseTexture == NULL )
			{
				hr = m_pTexture->LockRect( 0, &LockRect, pRect, 0 );
			}
			else
			{
				hr = m_pBaseTexture->LockRect( 0, &LockRect, pRect, 0 );
			}

			if SUCCEEDED( hr )
			{
				m_IsLock = true;

				if ( pRect == NULL )
				{
					if ( pFormat != NULL ) *pFormat = m_Format;
					if ( pWidth  != NULL ) *pWidth  = m_Size.x;
					if ( pHeight != NULL ) *pHeight = m_Size.y;
					if ( ppBites != NULL ) *ppBites = LockRect.pBits;
					if ( pPitch  != NULL ) *pPitch  = LockRect.Pitch;
				}
				else
				{
					if ( pFormat != NULL ) *pFormat = m_Format;
					if ( pWidth  != NULL ) *pWidth  = pRect->right - pRect->left;
					if ( pHeight != NULL ) *pHeight = pRect->bottom - pRect->top;
					if ( ppBites != NULL ) *ppBites = LockRect.pBits;
					if ( pPitch  != NULL ) *pPitch  = LockRect.Pitch;
				}
			}
			else
			{
				Log_PrintLine( 0xFF00000, L"テクスチャのロックに失敗しました [ %s ]", GetD3DError(hr) );
			}
		}
	}

	return m_IsLock;
}


//-----------------------------------------------------------------------------------
/**
	@brief ロック解除
	@author 葉迩倭

	ロック中のテクスチャのロックを解除します。
*/
//-----------------------------------------------------------------------------------
void CTexture::UnLockRect( void )
{
	if ( m_IsLock )
	{
		if ( m_pBaseTexture == NULL )
		{
			m_pTexture->UnlockRect( 0 );
		}
		else
		{
			m_pBaseTexture->UnlockRect( 0 );
		}
		m_IsLock = false;
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief テクスチャのコピー
	@author 葉迩倭

	@param pDstRect		[in] 転送先テクスチャの矩形
	@param pSrcTex		[in] 転送元テクスチャ
	@param pSrcRect		[in] 転送元テクスチャの矩形
	@param IsUvToTexel	[in] テクスチャサイズとイメージサイズが一致しない場合の補正をするか否か

	@retval true	成功
	@retval false	失敗

	テクスチャ同士の拡大縮小コピーを行います。<BR>
	テクスチャ間でフォーマットが異なる場合は<BR>
	ハードウェアのフォーマット変換のサポートがないと<BR>
	この関数は失敗します。<BR>
	またこのコピー処理にはいくつかの制限が存在します。<BR>
	・通常テクスチャから通常テクスチャの拡大縮小コピーはできません。<BR>
	・バックバッファから通常テクスチャへのコピーはできません。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel )
{
	HRESULT hr;
	RECT Dst, Src;
	IDirect3DSurface9 *pSrcSurf = NULL;
	IDirect3DSurface9 *pDstSurf = NULL;

	GetSurface( &pDstSurf );
	((CTexture*)pSrcTex)->GetSurface( &pSrcSurf );

	if ( IsUvToTexel )
	{
		Dst.left   = pDstRect->left   * m_Size.x  / m_ImageInfo.Width;
		Dst.top    = pDstRect->top    * m_Size.y / m_ImageInfo.Height;
		Dst.right  = pDstRect->right  * m_Size.x  / m_ImageInfo.Width;
		Dst.bottom = pDstRect->bottom * m_Size.y / m_ImageInfo.Height;

		Src.left   = pSrcRect->left   * ((CTexture*)pSrcTex)->m_Size.x  / ((CTexture*)pSrcTex)->m_ImageInfo.Width;
		Src.top    = pSrcRect->top    * ((CTexture*)pSrcTex)->m_Size.y / ((CTexture*)pSrcTex)->m_ImageInfo.Height;
		Src.right  = pSrcRect->right  * ((CTexture*)pSrcTex)->m_Size.x  / ((CTexture*)pSrcTex)->m_ImageInfo.Width;
		Src.bottom = pSrcRect->bottom * ((CTexture*)pSrcTex)->m_Size.y / ((CTexture*)pSrcTex)->m_ImageInfo.Height;
	}
	else
	{
		Dst = *pDstRect;
		Src = *pSrcRect;
	}

	hr = GetDevicePointer()->StretchRect( pSrcSurf, &Src, pDstSurf, &Dst, D3DTEXF_LINEAR );
	if FAILED( hr )
	{
		hr = GetDevicePointer()->StretchRect( pSrcSurf, &Src, pDstSurf, &Dst, D3DTEXF_POINT );
		if FAILED( hr )
		{
			hr = GetDevicePointer()->StretchRect( pSrcSurf, &Src, pDstSurf, &Dst, D3DTEXF_NONE );
		}
	}

	SAFE_RELEASE( pDstSurf );
	SAFE_RELEASE( pSrcSurf );

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ更新
	@author 葉迩倭

	バックアップ用システムメモリサーフェイスの内容を<BR>
	VRAM上のサーフェイスへ転送します。
*/
//-----------------------------------------------------------------------------------
void CTexture::UpdateTexture( void )
{
	if ( m_pTexture != NULL )
	{
		if ( m_pBaseTexture != NULL )
		{
			HRESULT hr;
			m_pTexture->AddDirtyRect( NULL );
			m_pBaseTexture->AddDirtyRect( NULL );
			hr = GetDevicePointer()->UpdateTexture( m_pBaseTexture, m_pTexture );
			if FAILED( hr )
			{
				Log_PrintLine( 0xFF00000, L"UpdateTexture() に失敗しました [ %s ]", GetD3DError(hr) );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief テクスチャ取得
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	レンダリング用のVRAM上のテクスチャを取得します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetTexture( IDirect3DTexture9 **ppTexture )
{
	if ( m_pTexture != NULL )
	{
		*ppTexture = m_pTexture;
		m_pTexture->AddRef();
	}
	else
	{
		*ppTexture = NULL;
	}

	return *ppTexture != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief バックアップ用テクスチャ取得
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	バックアップ用のシステムメモリテクスチャを取得します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetBaseTexture( IDirect3DTexture9 **ppTexture )
{
	if ( m_pBaseTexture != NULL )
	{
		*ppTexture = m_pBaseTexture;
		m_pBaseTexture->AddRef();
	}
	else
	{
		*ppTexture = NULL;
	}

	return *ppTexture != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief サーフェイス取得
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	レンダリング用のVRAM上のサーフェイスを取得します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetSurface( IDirect3DSurface9 **ppSurface )
{
	if ( m_pTexture != NULL )
	{
		m_pTexture->GetSurfaceLevel( 0, ppSurface );
	}
	else
	{
		*ppSurface = NULL;
	}

	return *ppSurface != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief バックアップ用サーフェイス取得
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	バックアップ用のシステムメモリサーフェイスを取得します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetBaseSurface( IDirect3DSurface9 **ppSurface )
{
	if ( m_pBaseTexture != NULL )
	{
		m_pBaseTexture->GetSurfaceLevel( 0, ppSurface );
	}
	else
	{
		*ppSurface = NULL;
	}

	return *ppSurface != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief U取得

	@param fParam	テクスチャのX座標

	@return U値

	テクスチャのピクセル座標から<BR>
	頂点データに使うUV値を取得します。
*/
//-----------------------------------------------------------------------------------
Float CTexture::PixelToTexelU( Float fParam )
{
	return fParam / toF(m_ImageInfo.Width);
}

//-----------------------------------------------------------------------------------
/**
	@brief V取得

	@param fParam	テクスチャのY座標

	@return V値

	テクスチャのピクセル座標から<BR>
	頂点データに使うUV値を取得します。
*/
//-----------------------------------------------------------------------------------
Float CTexture::PixelToTexelV( Float fParam )
{
	return fParam / toF(m_ImageInfo.Height);
}

//-----------------------------------------------------------------------------------
/**
	@brief 画像ファイルとして保存
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名

	@retval false	失敗
	@retval true	成功

	テクスチャの内容をTGA画像ファイルとして保存します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SaveToTGA( const wchar_t *pFileName )
{
	if ( m_pTexture != NULL )
	{
		// レンダリングターゲットの場合はシステムにコピ－
		DownloadRenderTarget();

		// 保存
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_TGA,
					m_pBaseTexture != NULL ? m_pBaseTexture : m_pTexture,
					NULL );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲットをダウンロード
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	レンダリングターサーフェイス<BR>
	現在のレンダリングターゲットの内容をコピーします。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::DownloadRenderTarget( void )
{
	HRESULT hr;
	IDirect3DSurface9 *pSrcSurf;
	IDirect3DSurface9 *pDstSurf;

	if ( m_pBaseTexture == NULL ) return false;
	if ( m_pTexture == NULL ) return false;
	if ( m_SurfaceType != SURFACE_TYPE_RENDERTARGET ) return false;

	hr = m_pTexture->GetSurfaceLevel( 0, &pSrcSurf );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"サーフェイスの取得に失敗 [%s]", GetD3DError(hr) );
		return false;
	}
	else
	{
		hr = m_pBaseTexture->GetSurfaceLevel( 0, &pDstSurf );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, L"サーフェイスの取得に失敗 [%s]", GetD3DError(hr) );
			SAFE_RELEASE( pSrcSurf );
			return false;
		}
		else
		{
			hr = GetDevicePointer()->GetRenderTargetData( pSrcSurf, pDstSurf );
			if FAILED( hr )
			{
				Log_PrintLine( 0xFF00000, L"テクスチャのコピー処理に失敗 [%s]", GetD3DError(hr) );
				SAFE_RELEASE( pSrcSurf );
				SAFE_RELEASE( pDstSurf );
				return false;
			}

			SAFE_RELEASE( pDstSurf );
		}

		SAFE_RELEASE( pSrcSurf );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief レンダリングターゲット設定
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	レンダリングターゲットとして設定します。<BR>
	CreateRenderTarget()で生成されたテクスチャ以外は失敗します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SetRenderTarget( void )
{
	Bool bRet = false;

	// サーフェイス取得
	IDirect3DSurface9 *pSurface;
	if ( GetSurface( &pSurface ) )
	{
		// レンダリングターゲット設定
		if SUCCEEDED( GetDevicePointer()->SetRenderTarget( pSurface ) )
		{
			bRet = true;
		}

		SAFE_RELEASE( pSurface );
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
	@brief 深度ステンシルバッファへ設定
	@author 葉迩倭

	@retval false	失敗
	@retval true	成功

	深度ステンシルサーフェイスとして設定します。<BR>
	この関数は100%失敗します。
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SetDepthStencil( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CTexture::GetSize( void )
{
	return m_Size;
}

