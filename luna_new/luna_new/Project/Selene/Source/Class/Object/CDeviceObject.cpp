

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Object/CDeviceObject.h"
#include "Object/CBaseMgr.h"
#include "Core/CGraphicCard.h"
#include "Core/CDevice.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
*/
//-----------------------------------------------------------------------------------
CDeviceObject::CDeviceObject( CBaseMgr *pMgr )
{
	m_pManager = pMgr;
	m_pManager->InsertEnd( this );
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CDeviceObject::~CDeviceObject()
{
	if ( m_pManager != NULL )
	{
		m_pManager->Erase( this );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
wchar_t *CDeviceObject::GetError( HRESULT hr )
{
	static wchar_t String[128] = L"";

	switch ( hr )
	{
	case D3D_OK:
		::StringCbCopy( String, sizeof(String), L"エラーは発生していない。" );
		break;
	case D3DERR_CONFLICTINGRENDERSTATE:
		::StringCbCopy( String, sizeof(String), L"現在設定されているレンダリング ステートは一緒に使用できない。" );
		break;
	case D3DERR_CONFLICTINGTEXTUREFILTER:
		::StringCbCopy( String, sizeof(String), L"現在のテクスチャ フィルタは一緒に使用できない。" );
		break;
	case D3DERR_CONFLICTINGTEXTUREPALETTE:
		::StringCbCopy( String, sizeof(String), L"現在のテクスチャは同時に使用できない。一般にマルチテクスチャ デバイスにおいて、同時に有効にされたパレット化テクスチャで同じパレットを共有する必要がある場合に発生する。" );
		break;
	case D3DERR_DEVICELOST:
		::StringCbCopy( String, sizeof(String), L"デバイスが失われていて、現時点では復元できないため、レンダリングは不可能である。" );
		break;
	case D3DERR_DEVICENOTRESET:
		::StringCbCopy( String, sizeof(String), L"デバイスはリセットできない。" );
		break;
	case D3DERR_DRIVERINTERNALERROR:
		::StringCbCopy( String, sizeof(String), L"内部ドライバ エラー。" );
		break;
	case D3DERR_INVALIDCALL:
		::StringCbCopy( String, sizeof(String), L"メソッドの呼び出しが無効である。たとえば、メソッドのパラメータに無効な値が設定されている場合など。" );
		break;
	case D3DERR_INVALIDDEVICE:
		::StringCbCopy( String, sizeof(String), L"要求されたデバイスの種類が有効でない。" );
		break;
	case D3DERR_MOREDATA:
		::StringCbCopy( String, sizeof(String), L"指定されたバッファ サイズに保持できる以上のデータが存在する。" );
		break;
	case D3DERR_NOTAVAILABLE:
		::StringCbCopy( String, sizeof(String), L"このデバイスは、照会されたテクニックをサポートしていない。" );
		break;
	case D3DERR_NOTFOUND:
		::StringCbCopy( String, sizeof(String), L"要求された項目が見つからなかった。" );
		break;
	case D3DERR_OUTOFVIDEOMEMORY:
		::StringCbCopy( String, sizeof(String), L"Direct3D が処理を行うのに十分なディスプレイ メモリがない。" );
		break;
	case D3DERR_TOOMANYOPERATIONS:
		::StringCbCopy( String, sizeof(String), L"デバイスがサポートしている以上のテクスチャ フィルタリング処理を、アプリケーションが要求している。" );
		break;
	case D3DERR_UNSUPPORTEDALPHAARG:
		::StringCbCopy( String, sizeof(String), L"アルファ チャネルに対して指定されているテクスチャ ブレンディング引数を、デバイスがサポートしていない。" );
		break;
	case D3DERR_UNSUPPORTEDALPHAOPERATION:
		::StringCbCopy( String, sizeof(String), L"アルファ チャネルに対して指定されているテクスチャ ブレンディング処理を、デバイスがサポートしていない。" );
		break;
	case D3DERR_UNSUPPORTEDCOLORARG:
		::StringCbCopy( String, sizeof(String), L"カラー値に対して指定されているテクスチャ ブレンディング引数を、デバイスがサポートしていない。" );
		break;
	case D3DERR_UNSUPPORTEDCOLOROPERATION:
		::StringCbCopy( String, sizeof(String), L"カラー値に対して指定されているテクスチャ ブレンディング処理を、デバイスがサポートしていない。" );
		break;
	case D3DERR_UNSUPPORTEDFACTORVALUE:
		::StringCbCopy( String, sizeof(String), L"デバイスが指定されたテクスチャ係数値をサポートしていない。" );
		break;
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
		::StringCbCopy( String, sizeof(String), L"デバイスが指定されたテクスチャ フィルタをサポートしていない。" );
		break;
	case D3DERR_WRONGTEXTUREFORMAT:
		::StringCbCopy( String, sizeof(String), L"テクスチャ サーフェスのピクセル フォーマットが有効でない。" );
		break;
	case E_FAIL:
		::StringCbCopy( String, sizeof(String), L"Direct3D サブシステム内で原因不明のエラーが発生した。" );
		break;
	case E_INVALIDARG:
		::StringCbCopy( String, sizeof(String), L"無効なパラメータが戻ってくる関数に渡された。" );
		break;
	case E_OUTOFMEMORY:
		::StringCbCopy( String, sizeof(String), L"Direct3D が呼び出しを完了するための十分なメモリを割り当てることができなかった。" );
		break;
	case D3DXERR_CANNOTATTRSORT:
		::StringCbCopy( String, sizeof(String), L"最適化テクニックとして属性のソート (::D3DXMESHOPT_ATTRSORT) はサポートされていない。 " );
		break;
	case D3DXERR_CANNOTMODIFYINDEXBUFFER:
		::StringCbCopy( String, sizeof(String), L"インデックス バッファを変更できない。 " );
		break;
	case D3DXERR_INVALIDMESH:
		::StringCbCopy( String, sizeof(String), L"メッシュが無効である。 " );
		break;
	case D3DXERR_SKINNINGNOTSUPPORTED:
		::StringCbCopy( String, sizeof(String), L"スキニングはサポートされていない。 " );
		break;
	case D3DXERR_TOOMANYINFLUENCES:
		::StringCbCopy( String, sizeof(String), L"指定された影響が多すぎる。 " );
		break;
	case D3DXERR_INVALIDDATA:
		::StringCbCopy( String, sizeof(String), L"データが無効である。" );
		break;
	default:
		::StringCbCopy( String, sizeof(String), L"未知のエラー。" );
		break;
	}

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDevice *CDeviceObject::GetDevicePointer( void ) const
{
	return m_pManager->GetDevicePointer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CDeviceObject::GetGraphicCardPointer( void ) const
{
	return m_pManager->GetGraphicCardPointer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CDeviceObject::GetCorePointer( void ) const
{
	return m_pManager->GetCorePointer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CDeviceObject::GetTextureMaxSize( void )
{
	return GetGraphicCardPointer()->GetTextureMaxSize();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HWND CDeviceObject::GetWindow( void ) const
{
	return m_pManager->GetWindow();
}

