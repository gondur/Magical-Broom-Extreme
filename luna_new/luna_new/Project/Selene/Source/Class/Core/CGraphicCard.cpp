

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Core/CGraphicCard.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Local.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// CONSTANT
//-----------------------------------------------------------------------------------

//---------------------------------------------------------------
// バックバッファフォーマット
//---------------------------------------------------------------
static const D3DFORMAT g_BackBufferFormats[] = {
	D3DFMT_A8R8G8B8,
	D3DFMT_X8R8G8B8,
	D3DFMT_A1R5G5B5,
	D3DFMT_X1R5G5B5,
	D3DFMT_R5G6B5,
	D3DFMT_UNKNOWN,
};


//---------------------------------------------------------------
// テクスチャフォーマット
//---------------------------------------------------------------
static D3DFORMAT g_TextureFormats[] = {
	D3DFMT_R5G6B5,			D3DFMT_X1R5G5B5,		D3DFMT_A1R5G5B5,
	D3DFMT_A4R4G4B4,		D3DFMT_R8G8B8,			D3DFMT_A8R8G8B8,
	D3DFMT_X8R8G8B8,		D3DFMT_R3G3B2,			D3DFMT_A8,
	D3DFMT_A8R3G3B2,		D3DFMT_X4R4G4B4,		D3DFMT_A2B10G10R10,
	D3DFMT_A2R10G10B10,		D3DFMT_A16B16G16R16,	D3DFMT_A8P8,
	D3DFMT_P8,				D3DFMT_L8,				D3DFMT_L16,
	D3DFMT_A8L8,			D3DFMT_A4L4,			D3DFMT_V8U8,
	D3DFMT_Q8W8V8U8,		D3DFMT_V16U16,			D3DFMT_Q16W16V16U16,
	D3DFMT_CxV8U8,			D3DFMT_L6V5U5,			D3DFMT_X8L8V8U8,
	D3DFMT_A2W10V10U10,		D3DFMT_G8R8_G8B8,		D3DFMT_R8G8_B8G8,
	D3DFMT_DXT5,			D3DFMT_DXT4,			D3DFMT_DXT3,
	D3DFMT_DXT2,			D3DFMT_DXT1,			D3DFMT_UYVY,
	D3DFMT_YUY2,			D3DFMT_D16_LOCKABLE,	D3DFMT_D32,
	D3DFMT_D15S1,			D3DFMT_D24S8,			D3DFMT_D24X8,
	D3DFMT_D24X4S4,			D3DFMT_D32F_LOCKABLE,	D3DFMT_D24FS8,
	D3DFMT_D16,				D3DFMT_VERTEXDATA,		D3DFMT_INDEX16,
	D3DFMT_INDEX32,			D3DFMT_R16F,			D3DFMT_G16R16F,
	D3DFMT_A16B16G16R16F,	D3DFMT_R32F,			D3DFMT_G32R32F,
	D3DFMT_A32B32G32R32F,	D3DFMT_G16R16,			D3DFMT_UNKNOWN,
};


//---------------------------------------------------------------
// 深度バッファフォーマット
//---------------------------------------------------------------
static D3DFORMAT g_DepthFormats[] = {
	D3DFMT_D16,				D3DFMT_D32,				D3DFMT_D24S8,
	D3DFMT_D24X8,			D3DFMT_D24X4S4,			D3DFMT_D24FS8,
	D3DFMT_D15S1,			D3DFMT_UNKNOWN,
};

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard::CGraphicCard( void )
{
	m_GraphicCardNo	= 0;
	m_MaxUseVertexShaderVersion = 0;

	m_hDllD3D9	= NULL;
	m_pDirect3D	= NULL;
	m_pDevice	= NULL;

	m_IsHighColor	= false;
	m_IsWaitBlank	= false;
	m_IsHVPerfHUD	= false;

	MemoryClear( m_SurfaceFormatTbl, sizeof(m_SurfaceFormatTbl) );
	MemoryClear( m_SurfaceFormatCount, sizeof(m_SurfaceFormatCount) );
	MemoryClear( m_GraphicCardName, sizeof(m_GraphicCardName) );
	MemoryClear( m_GraphicCardDriver, sizeof(m_GraphicCardDriver) );
	MemoryClear( m_GraphicCardVersion, sizeof(m_GraphicCardVersion ) );
	MemoryClear( m_FullScreenType, sizeof(m_FullScreenType) );
	MemoryClear( m_PresentParams, sizeof(m_PresentParams) );
	MemoryClear( &m_DeviceInfo, sizeof(m_DeviceInfo) );
	MemoryClear( &m_WindowType, sizeof(m_WindowType) );

	m_ScreenTypeCount	= 0;
	m_DepthCount		= 0;
	m_TextureCount		= 0;
	m_TargetCount		= 0;

	MemoryClear( m_ScreenType, sizeof(m_ScreenType) );
	MemoryClear( m_DepthFormats, sizeof(m_DepthFormats) );
	MemoryClear( m_TextureFormats, sizeof(m_TextureFormats) );
	MemoryClear( m_TargetFormats, sizeof(m_TargetFormats) );

	eSurfaceFormat Fmt2D[] = { FORMAT_TEXTURE32, FORMAT_TEXTURE16, FORMAT_DXT5, FORMAT_DXT3 };
	SetSurfaceFormatTblFor2D( Fmt2D, sizeof(Fmt2D) / sizeof(eSurfaceFormat) );

	eSurfaceFormat Fmt3D[] = { FORMAT_DXT5, FORMAT_DXT3, FORMAT_TEXTURE32, FORMAT_TEXTURE16 };
	SetSurfaceFormatTblFor3D( Fmt3D, sizeof(Fmt3D) / sizeof(eSurfaceFormat) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard::~CGraphicCard()
{
	// グラフィックカード解放
	if ( m_pDirect3D != NULL )
	{
		Uint32 Num = m_pDirect3D->Release();
		m_pDirect3D = NULL;

		Log_TableBegin();
		Log_PrintCellTitle( 0x008000, L"解放" );
		Log_PrintCellKind( L"IDirect3DObject" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, L"参照数 %d", Num );
		Log_CellEnd();
		Log_TableEnd();
		Log_TableLine( 2 );
	}

	if ( m_hDllD3D9 != NULL )
	{
		::FreeLibrary( m_hDllD3D9 );
		m_hDllD3D9 = NULL;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::Initialize( Uint32 GraphicCardNo, eVertexShaderVersion VsVer )
{
	const Uint32 VsVerTbl[] = {
		D3DVS_VERSION(2,0), D3DVS_VERSION(3,0),
	};

	//---------------------------------------------------------------
	// ビデオカード番号
	//---------------------------------------------------------------
	m_GraphicCardNo = GraphicCardNo;

	//---------------------------------------------------------------
	// シェーダーバージョン
	//---------------------------------------------------------------
	m_MaxUseVertexShaderVersion = VsVerTbl[VsVer];

	//---------------------------------------------------------------
	// Direct3Dオブジェクトの生成
	//---------------------------------------------------------------
	if ( !CreateDirect3DObject() )
	{
		return false;
	}

	//---------------------------------------------------------------
	// "NVPerfHUD"チェック
	//---------------------------------------------------------------
	if ( m_GraphicCardNo == GRAPHIC_CARD_NV_PERF_HUD )
	{
		Uint32 MaxGraphicCard = m_pDirect3D->GetAdapterCount();
		for ( Uint32 i= 0; i< MaxGraphicCard; i++ )
		{
			D3DADAPTER_IDENTIFIER9 Identifier;
			m_pDirect3D->GetAdapterIdentifier( i, 0, &Identifier );

			wchar_t Temp[128] = L"";
			MBCStoWCS( Identifier.Description, Temp );
			Uint32 Compare = ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, Temp, -1, L"NVIDIA NVPerfHUD", -1 );
			if ( Compare == CSTR_EQUAL )
			{
				m_IsHVPerfHUD = true;
				m_GraphicCardNo = i;
				break;
			}
		}
	}

	//---------------------------------------------------------------
	// ビデオカード情報のチェック
	//---------------------------------------------------------------
	if ( !CheckGraphicCardInfo() )
	{
		return false;
	}

	//---------------------------------------------------------------
	// デバイス情報のチェック
	//---------------------------------------------------------------
	if ( !CheckGraphicCardCaps() )
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CreateDirect3DObject( void )
{
	PDIRECT3DCREATE9 pProcDirect3DCreate9 = NULL;

	try
	{
		//---------------------------------------------------------------
		// Load DLL
		//---------------------------------------------------------------
		m_hDllD3D9 = ::LoadLibrary( L"d3d9.dll" );
		if ( m_hDllD3D9 == NULL )
		{
			throw L"DLLの読み込みに失敗\nDirectX9.0cが正しくインストールされているか\n確認して下さい";
		}

		//---------------------------------------------------------------
		// Load Direct3DCreate from DLL
		//---------------------------------------------------------------
		pProcDirect3DCreate9 = (PDIRECT3DCREATE9)::GetProcAddress( m_hDllD3D9, "Direct3DCreate9" );
		if ( pProcDirect3DCreate9 == NULL )
		{
			throw L"DLLからの関数呼び出しに失敗\nDirectX9.0cが正しくインストールされているか\n確認して下さい";
		}

		//---------------------------------------------------------------
		// Create Direct3D Object
		//---------------------------------------------------------------
		m_pDirect3D = pProcDirect3DCreate9( D3D_SDK_VERSION );
		if ( m_pDirect3D == NULL )
		{
			throw L"Direct3Dオブジェクトの生成に失敗\nDirectX9.0cが正しくインストールされているか\n確認して下さい";
		}
	}
	catch ( const wchar_t *pErrMsg )
	{
		(dynamic_cast<CCore*>(GetParent()))->MsgBox( MB_ICONERROR, L"Error", pErrMsg );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckGraphicCardInfo( void )
{
	D3DADAPTER_IDENTIFIER9 Identifier;
	HRESULT hr;

	//---------------------------------------------------------------
	// ビデオカード情報
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"ビデオカード情報" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->GetAdapterIdentifier( m_GraphicCardNo, 0, &Identifier );
	if SUCCEEDED( hr )
	{
		MBCStoWCS( Identifier.Description, m_GraphicCardName );

		MBCStoWCS( Identifier.Driver, m_GraphicCardDriver );

		::StringCbPrintf(
			m_GraphicCardVersion, sizeof(m_GraphicCardVersion),
			L"%u.%u.%u.%u",
			HIWORD(Identifier.DriverVersion.HighPart),
			LOWORD(Identifier.DriverVersion.HighPart),
			HIWORD(Identifier.DriverVersion.LowPart),
			LOWORD(Identifier.DriverVersion.LowPart) );

		Log_PrintTable( 96, L"Name", L"%s", m_GraphicCardName );
		Log_PrintTable( 96, L"Driver", L"%s", m_GraphicCardDriver );
		Log_PrintTable( 96, L"Product", L"%u", HIWORD(Identifier.DriverVersion.HighPart) );
		Log_PrintTable( 96, L"Version", L"%u.%u.%u", LOWORD(Identifier.DriverVersion.HighPart), HIWORD(Identifier.DriverVersion.LowPart), LOWORD(Identifier.DriverVersion.LowPart) );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// 現在の画面モード取得
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"現在の画面情報" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->GetAdapterDisplayMode( m_GraphicCardNo, &m_WindowType );
	if SUCCEEDED( hr )
	{
		Log_PrintTable( 128, L"Width", L"%u", m_WindowType.Width );
		Log_PrintTable( 128, L"Height", L"%u", m_WindowType.Height );
		Log_PrintTable( 128, L"RefreshRate", L"%uHz", m_WindowType.RefreshRate );
		Log_PrintTable( 128, L"Format", L"%s", GetPixelFormat(m_WindowType.Format) );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// フルスクリーン時に使用可能な画面モードを列挙する
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"使用可能な画面モード" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_BackBufferFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		// ディスプレイモード数の取得
		D3DDISPLAYMODE DisplayType;
		Uint32 TypeCount = m_pDirect3D->GetAdapterModeCount( m_GraphicCardNo, g_BackBufferFormats[i] );

		if ( TypeCount > 0 )
		{
			Log_PrintStrongLine( 0x000000, L"BackBuffer Format %s", GetPixelFormat(g_BackBufferFormats[i]) );

			// モードを列挙
			for ( Uint32 j = 0; j < TypeCount; j++ )
			{
				hr = m_pDirect3D->EnumAdapterModes( m_GraphicCardNo, g_BackBufferFormats[i], j, &DisplayType );
				if SUCCEEDED( hr )
				{
					Bool IsNew = true;

					// 同一画面サイズの検索
					for ( Sint32 k = 0; k < m_ScreenTypeCount; k++ )
					{
						if ( m_ScreenType[k].Width == DisplayType.Width )
						{
							if ( m_ScreenType[k].Height == DisplayType.Height )
							{
								if ( m_ScreenType[k].Format == DisplayType.Format )
								{
									IsNew = false;
								}
							}
						}
					}

					// 同一画面サイズが見つからなかった場合は新しく入れておく
					if ( IsNew )
					{
						m_ScreenType[m_ScreenTypeCount++] = DisplayType;
						Log_PrintLine( 0x000000, L"%4u x %4u : %uHz", DisplayType.Width, DisplayType.Height, DisplayType.RefreshRate );
					}
				}
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// フルスクリーンモード用のディスプレイモード設定
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"フルスクリーン用<BR>ディスプレイモード" );
	Log_CellBegin( 0 );

	Uint32 Width, Height;
	(dynamic_cast<CCore*>(GetParent()))->GetScreenData( &Width, &Height, NULL );

	// クリア
	m_FullScreenType[0].Format = D3DFMT_UNKNOWN;
	m_FullScreenType[1].Format = D3DFMT_UNKNOWN;

	// 検索
	for ( Sint32 j = 0; j < m_ScreenTypeCount; j++ )
	{
		switch ( m_ScreenType[j].Format )
		{
		// 16Bit
		case D3DFMT_X1R5G5B5:
		case D3DFMT_R5G6B5:
			m_FullScreenType[0] = m_ScreenType[j];
			break;
		// 32Bit
		case D3DFMT_X8R8G8B8:
			m_FullScreenType[1] = m_ScreenType[j];
			break;
		}
	}

	// ログ
	Log_PrintLine( 0x000000, L"16BitColor %s", GetPixelFormat(m_FullScreenType[0].Format) );
	Log_PrintLine( 0x000000, L"32BitColor %s", GetPixelFormat(m_FullScreenType[1].Format) );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// テクスチャフォーマットから使用可能なものを検索
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"使用可能な<BR>テクスチャフォーマット" );
	Log_CellBegin( 0 );

	D3DFORMAT BaseFormat = m_FullScreenType[1].Format == D3DFMT_UNKNOWN ? m_WindowType.Format : m_FullScreenType[1].Format;

	for ( Sint32 i = 0; g_TextureFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
						m_GraphicCardNo,
						D3DDEVTYPE_HAL,
						BaseFormat,
						0,
						D3DRTYPE_TEXTURE,
						g_TextureFormats[i] );
		if SUCCEEDED( hr )
		{
			m_TextureFormats[ m_TextureCount ] = g_TextureFormats[i];
			m_TextureCount++;

			Log_PrintLine( 0x000000, L"%s", GetPixelFormat(g_TextureFormats[i]) );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// レンダリングターゲットテクスチャフォーマットから使用可能なものを検索
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"使用可能な<BR>レンダリングターゲット<BR>フォーマット" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_TextureFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
						m_GraphicCardNo,
						D3DDEVTYPE_HAL,
						BaseFormat,
						D3DUSAGE_RENDERTARGET,
						D3DRTYPE_TEXTURE,
						g_TextureFormats[i] );
		if SUCCEEDED( hr )
		{
			m_TargetFormats[ m_TargetCount++ ] = g_TextureFormats[i];

			Log_PrintLine( 0x000000, L"%s", GetPixelFormat(g_TextureFormats[i]) );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// 深度バッファフォーマットから使用可能なものを検索
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"使用可能な<BR>デプスステンシル<BR>フォーマット" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
								m_GraphicCardNo,
								D3DDEVTYPE_HAL,
								BaseFormat,
								D3DUSAGE_DEPTHSTENCIL,
								D3DRTYPE_SURFACE,
								g_DepthFormats[i] );
		if SUCCEEDED( hr )
		{
			m_DepthFormats[ m_DepthCount++ ] = g_DepthFormats[i];

			Log_PrintLine( 0x000000, L"%s", GetPixelFormat(g_DepthFormats[i]) );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// サーフェイス間転送をチェック
	//---------------------------------------------------------------
	D3DFORMAT g_CopySurface[] = {
		D3DFMT_X1R5G5B5,
		D3DFMT_A1R5G5B5,
		D3DFMT_R5G6B5,
		D3DFMT_R8G8B8,
		D3DFMT_X8R8G8B8,
		D3DFMT_A8R8G8B8,
		D3DFMT_A2R10G10B10,
		D3DFMT_A16B16G16R16,
		D3DFMT_A2B10G10R10,
		D3DFMT_A8B8G8R8,
		D3DFMT_X8B8G8R8,
		D3DFMT_A16B16G16R16F,
		D3DFMT_A32B32G32R32F,
		D3DFMT_UNKNOWN,
	};

	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"使用可能な<BR>サーフェイス間転送" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_CopySurface[i] != D3DFMT_UNKNOWN; i++ )
	{
		for ( Sint32 j = 0; j < m_TargetCount; j++ )
		{
			if ( g_CopySurface[i] == m_TargetFormats[j] )
			{
				for ( Sint32 k = 0; g_CopySurface[k] != D3DFMT_UNKNOWN; k++ )
				{
					for ( Sint32 l = 0; l < m_TargetCount; l++ )
					{
						if ( g_CopySurface[k] == m_TargetFormats[l] )
						{
							hr = m_pDirect3D->CheckDeviceFormatConversion(
													m_GraphicCardNo,
													D3DDEVTYPE_HAL,
													g_CopySurface[i],
													g_CopySurface[k] );
							wchar_t Temp[256];
							wchar_t Src[64], Dst[64];
							GetPixelFormat( g_CopySurface[i], Src, sizeof(Src) );
							GetPixelFormat( g_CopySurface[k], Dst, sizeof(Dst) );
							::StringCbPrintf( Temp, sizeof(Temp), L"%s -> %s", Src, Dst );
							Log_PrintTable( 24, SUCCEEDED( hr ) ? L"○" : L"×", Temp );
						}
					}
				}
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckGraphicCardCaps( void )
{
	D3DCAPS9 Caps;

	//-----------------------------------------------------------
	// ハードウェアデバイスの性能を取得
	//-----------------------------------------------------------
	m_pDirect3D->GetDeviceCaps( m_GraphicCardNo, D3DDEVTYPE_HAL, &Caps );
	GetDeviceCaps( &Caps, &m_DeviceInfo );

	//-----------------------------------------------------------
	// ハードウェアデバイスの性能を列挙
	//-----------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, L"調査" );
	Log_PrintCellKind( L"ビデオカード性能" );
	Log_CellBegin( 0 );

	Log_PrintTable( 384, L"ピュアデバイス", L"[ %s ]", m_DeviceInfo.IsPureDevice ? L"○" : L"×" );
	Log_PrintTable( 384, L"ハードウェアＴｎＬ", L"[ %s ]", m_DeviceInfo.IsHardwareTnL ? L"○" : L"×" );
	Log_PrintTable( 384, L"ハードウェアラスタライズ", L"[ %s ]", m_DeviceInfo.IsHardwareRasterize ? L"○" : L"×" );
	Log_PrintTable( 384, L"ミップマップ自動生成", L"[ %s ]", m_DeviceInfo.IsAutoMipMap ? L"○" : L"×" );
	Log_PrintTable( 384, L"両面ステンシル", L"[ %s ]", m_DeviceInfo.IsStencilTwoSided ? L"○" : L"×" );
	Log_PrintTable( 384, L"キューブマップ", L"[ %s ]", m_DeviceInfo.IsCubeTexture ? L"○" : L"×" );
	Log_PrintTable( 384, L"異方性フィルタ：拡大", L"[ %s ]", m_DeviceInfo.IsMagAnisotropy ? L"○" : L"×" );
	Log_PrintTable( 384, L"異方性フィルタ：縮小", L"[ %s ]", m_DeviceInfo.IsMinAnisotropy ? L"○" : L"×" );

	Log_PrintTable( 384, L"テクスチャ最大横幅", L"[ %u ]", m_DeviceInfo.MaxTextureWidth );
	Log_PrintTable( 384, L"テクスチャ最大縦幅", L"[ %u ]", m_DeviceInfo.MaxTextureHeight );
	Log_PrintTable( 384, L"テクスチャ異方性の次数", L"[ %u ]", m_DeviceInfo.MaxAnisotropy );

	Log_PrintTable( 384, L"ガードバンド 左", L"[ %.3lf ]", m_DeviceInfo.GuardBandLeft );
	Log_PrintTable( 384, L"ガードバンド 上", L"[ %.3lf ]", m_DeviceInfo.GuardBandTop );
	Log_PrintTable( 384, L"ガードバンド 右", L"[ %.3lf ]", m_DeviceInfo.GuardBandRight );
	Log_PrintTable( 384, L"ガードバンド 下", L"[ %.3lf ]", m_DeviceInfo.GuardBandBottom );
	Log_PrintTable( 384, L"最大プリミティブ数", L"[ %u ]", m_DeviceInfo.MaxPrimitiveCount );
	Log_PrintTable( 384, L"最大インデックス数", L"[ %u ]", m_DeviceInfo.MaxVertexIndex );
	Log_PrintTable( 384, L"最大テクスチャステージ数", L"[ %u ]", m_DeviceInfo.MaxTextureBlendStages );
	Log_PrintTable( 384, L"最大マルチテクスチャ数", L"[ %u ]", m_DeviceInfo.MaxSimultaneousTextures );
	Log_PrintTable( 384, L"頂点シェーダーバージョン", L"[ %u.%u ]", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.VertexShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.VertexShaderVersion) );
	Log_PrintTable( 384, L"ピクセルシェーダーバージョン", L"[ %u.%u ]", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.PixelShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.PixelShaderVersion) );
	Log_PrintTable( 384, L"動的フロー制御命令のネスティング", L"[ %u ]", m_DeviceInfo.DynamicFlowControlDepth );
	Log_PrintTable( 384, L"静的フロー制御命令のネスティング", L"[ %u ]", m_DeviceInfo.StaticFlowControlDepth );

	Log_PrintTable( 384, L"マルチレンダリングターゲット数", L"[ %u ]", m_DeviceInfo.MultiRenderTargetCount );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo )
{
	// デバイスタイプ
	pDevInfo->DeviceType				= pCaps->DeviceType;
	// ピュアデバイス
	pDevInfo->IsPureDevice				= (pCaps->DevCaps & D3DDEVCAPS_PUREDEVICE) != 0;
	// ハードウェアTnL
	pDevInfo->IsHardwareTnL				= (pCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) != 0;
	// ハードウェアRaster
	pDevInfo->IsHardwareRasterize		= (pCaps->DevCaps & D3DDEVCAPS_HWRASTERIZATION) != 0;
	// テクスチャ
	pDevInfo->IsCubeTexture				= (pCaps->TextureCaps & D3DPTEXTURECAPS_CUBEMAP) != 0;
	// ステンシル
	pDevInfo->IsStencilTwoSided			= (pCaps->StencilCaps & D3DSTENCILCAPS_TWOSIDED) != 0;
	// テクスチャ情報
	pDevInfo->MaxTextureWidth			= pCaps->MaxTextureWidth;
	pDevInfo->MaxTextureHeight			= pCaps->MaxTextureHeight;
	pDevInfo->MaxAnisotropy				= pCaps->MaxAnisotropy;
	pDevInfo->IsMagAnisotropy			= (pCaps->TextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) != 0;
	pDevInfo->IsMinAnisotropy			= (pCaps->TextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) != 0;

	// 2 の累乗
	pDevInfo->IsSupportPow2Texture		= (pCaps->TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL) != 0;

	// 他
	pDevInfo->GuardBandLeft				= pCaps->GuardBandLeft;
	pDevInfo->GuardBandTop				= pCaps->GuardBandTop;
	pDevInfo->GuardBandRight			= pCaps->GuardBandRight;
	pDevInfo->GuardBandBottom			= pCaps->GuardBandBottom;
	pDevInfo->MaxPrimitiveCount			= pCaps->MaxPrimitiveCount;
	pDevInfo->MaxVertexIndex			= pCaps->MaxVertexIndex;
	// テクスチャ
	pDevInfo->MaxTextureBlendStages		= pCaps->MaxTextureBlendStages;
	pDevInfo->MaxSimultaneousTextures	= pCaps->MaxSimultaneousTextures;
	// シェーダー
	pDevInfo->MaxVertexShaderConst		= pCaps->MaxVertexShaderConst;
	pDevInfo->DynamicFlowControlDepth	= pCaps->VS20Caps.DynamicFlowControlDepth;
	pDevInfo->StaticFlowControlDepth	= pCaps->VS20Caps.StaticFlowControlDepth;
	pDevInfo->VertexShaderVersion		= pCaps->VertexShaderVersion;
	pDevInfo->PixelShaderVersion		= pCaps->PixelShaderVersion;
	// マルチレンダリングターゲット
	pDevInfo->MultiRenderTargetCount	= pCaps->NumSimultaneousRTs;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetAnisotropyFilterSupport( Bool &IsMin, Bool &IsMag, Uint32 &Max )
{
	IsMag = m_DeviceInfo.IsMagAnisotropy;
	IsMin = m_DeviceInfo.IsMinAnisotropy;
	Max = m_DeviceInfo.MaxAnisotropy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::EnableHighlColorScreen( void )
{
	m_IsHighColor = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetHDRRenderTargetSupport( void )
{
	return GetFormat( FORMAT_TARGET_HDR, D3DFMT_UNKNOWN ) != D3DFMT_UNKNOWN;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetPixelShaderSupport( Uint16 Major, Uint16 Minor )
{
	return m_DeviceInfo.PixelShaderVersion >= D3DPS_VERSION( Major, Minor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNoPow2TextureSupport( void )
{
	return m_DeviceInfo.IsSupportPow2Texture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetHightColorType( void )
{
	return m_IsHighColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNVPerfHUD( void )
{
	return m_IsHVPerfHUD;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::GetDeviceTypeNo( void )
{
	Sint32 No = 4;		// REF Device

	// ソフトウェアＴｎＬサポート？
	if ( !m_DeviceInfo.IsHardwareRasterize ) return No;

	No--;

	// ハードウェアＴｎＬサポート？
	if ( !m_DeviceInfo.IsHardwareTnL ) return No;

	No--;

	// 指定バーテックスシェーダーを完全にサポート？
	if ( m_DeviceInfo.VertexShaderVersion < m_MaxUseVertexShaderVersion ) return No;

	No--;

	// ピュアデバイスをサポート？
	if ( !m_DeviceInfo.IsPureDevice ) return No;

	No--;

	return No;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DPRESENT_PARAMETERS CGraphicCard::MakePresentParameters( Bool IsWindow, Bool IsHightColor )
{
	Uint32 RefreshRate;
	Uint32 Width, Height;
	D3DPRESENT_PARAMETERS PresentParam;
	D3DFORMAT ScreenFormat, DepthFormat;

	//-----------------------------------------------------------
	// モード
	//-----------------------------------------------------------
	if ( !IsWindow )
	{
		if ( IsHightColor )
		{
			ScreenFormat = m_FullScreenType[0].Format;
			RefreshRate = m_FullScreenType[0].RefreshRate;
		}
		else
		{
			ScreenFormat = m_FullScreenType[1].Format;
			RefreshRate = m_FullScreenType[1].RefreshRate;
		}
	}
	else
	{
		ScreenFormat = m_WindowType.Format;
		RefreshRate = 0;
	}


	//-----------------------------------------------------------
	// 画面サイズ取得
	//-----------------------------------------------------------
	(dynamic_cast<CCore*>(GetParent()))->GetScreenData( &Width, &Height, NULL );

	//-----------------------------------------------------------
	// 有効なフォーマット取得
	//-----------------------------------------------------------
	DepthFormat = D3DFMT_UNKNOWN;
	for ( Sint32 i = 0; i < 8; i++ )
	{
		if ( g_BackBufferFormats[i] == ScreenFormat )
		{
			DepthFormat = m_DepthFormats[0];
		}
	}

	//-----------------------------------------------------------
	// パラメーター生成
	//-----------------------------------------------------------
	PresentParam.BackBufferWidth			= Width;
	PresentParam.BackBufferHeight			= Height;
	PresentParam.BackBufferFormat			= ScreenFormat;
	PresentParam.BackBufferCount			= 1;
	PresentParam.MultiSampleType			= D3DMULTISAMPLE_NONE;
	PresentParam.MultiSampleQuality			= 0;
	PresentParam.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	PresentParam.hDeviceWindow				= GetCorePointer()->GetWindowHandle();
	PresentParam.Windowed					= IsWindow;
	PresentParam.EnableAutoDepthStencil		= false;
	PresentParam.AutoDepthStencilFormat		= DepthFormat;
	PresentParam.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	PresentParam.FullScreen_RefreshRateInHz	= RefreshRate;
	PresentParam.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;

	return PresentParam;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckSupportVertexProccessing( void )
{
	if ( m_DeviceInfo.IsHardwareTnL )
	{
		if ( m_DeviceInfo.VertexShaderVersion < m_MaxUseVertexShaderVersion )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DFORMAT CGraphicCard::GetFormat( eSurfaceFormat Format, D3DFORMAT OrgFmt, D3DFORMAT FmtTarget )
{
	Bool IsWindow;
	D3DFORMAT ScreenFormat;

	//------------------------------------------------------------
	// ウィンドウ情報取得
	//------------------------------------------------------------
	(dynamic_cast<CCore*>(GetParent()))->GetScreenData( NULL, NULL, &IsWindow );
	ScreenFormat = IsWindow ? m_WindowType.Format : m_FullScreenType[m_IsHighColor ? 0 : 1].Format;

	//------------------------------------------------------------
	// フォーマット情報検索
	//------------------------------------------------------------
	switch ( Format )
	{
		// ファイルから
	case FORMAT_FROM_FILE:
		return OrgFmt;

		// 16Bit深度バッファ
	case FORMAT_DEPTH16:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_D16_LOCKABLE, D3DFMT_D16, D3DFMT_D15S1, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_DepthCount; j++ )
				{
					if ( FmtTbl[i] == m_DepthFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// 32Bit深度バッファ
	case FORMAT_DEPTH32:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_D32, D3DFMT_D24S8, D3DFMT_D24X8, D3DFMT_D24X4S4, D3DFMT_D24FS8, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_DepthCount; j++ )
				{
					if ( FmtTbl[i] == m_DepthFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// ステンシル深度バッファ
	case FORMAT_DEPTHSTENCIL:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_D24S8, D3DFMT_D24X4S4, D3DFMT_D24FS8, D3DFMT_D15S1, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_DepthCount; j++ )
				{
					if ( FmtTbl[i] == m_DepthFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// バックバッファに準拠
	case FORMAT_BACKBUFFER:
		{
			return ScreenFormat;
		}
		break;

		// 16Bitレンダリングターゲット
	case FORMAT_TARGET16:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_A4R4G4B4, D3DFMT_A1R5G5B5, D3DFMT_X1R5G5B5, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TargetCount; j++ )
				{
					if ( FmtTbl[i] == m_TargetFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// 32Bitレンダリングターゲット
	case FORMAT_TARGET32:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TargetCount; j++ )
				{
					if ( FmtTbl[i] == m_TargetFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// HDR用レンダリングターゲット
	case FORMAT_TARGET_HDR:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_A16B16G16R16F, D3DFMT_A16B16G16R16, D3DFMT_A32B32G32R32F, D3DFMT_A2R10G10B10, D3DFMT_A2B10G10R10, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TargetCount; j++ )
				{
					if ( FmtTbl[i] == m_TargetFormats[j] )
					{
						HRESULT hr = D3D_OK;
						if ( FmtTarget != D3DFMT_UNKNOWN )
						{
							hr = m_pDirect3D->CheckDeviceFormatConversion(
												m_GraphicCardNo,
												D3DDEVTYPE_HAL,
												FmtTbl[i],
												FmtTarget );
						}
						if SUCCEEDED( hr ) return FmtTbl[i];
					}
				}
			}
		}
		break;

		// シャドウマップ用
	case FORMAT_TARGET_SHADOWMAP:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_R32F, D3DFMT_R16F, D3DFMT_G32R32F, D3DFMT_G16R16F, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TargetCount; j++ )
				{
					if ( FmtTbl[i] == m_TargetFormats[j] )
					{
						HRESULT hr = D3D_OK;
						if ( FmtTarget != D3DFMT_UNKNOWN )
						{
							hr = m_pDirect3D->CheckDeviceFormatConversion(
												m_GraphicCardNo,
												D3DDEVTYPE_HAL,
												FmtTbl[i],
												FmtTarget );
						}
						if SUCCEEDED( hr ) return FmtTbl[i];
					}
				}
			}
		}
		break;

		// アルファ用テクスチャ
	case FORMAT_ALPHAONLY:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_A8, D3DFMT_A8R3G3B2, D3DFMT_A8R8G8B8, D3DFMT_A4R4G4B4, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TextureCount; j++ )
				{
					if ( FmtTbl[i] == m_TextureFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// 32Bitテクスチャフォーマットに準拠
	case FORMAT_TEXTURE32:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TextureCount; j++ )
				{
					if ( FmtTbl[i] == m_TextureFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// 16Bitテクスチャフォーマットに準拠
	case FORMAT_TEXTURE16:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_A4R4G4B4, D3DFMT_A1R5G5B5, D3DFMT_A8R3G3B2, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TextureCount; j++ )
				{
					if ( FmtTbl[i] == m_TextureFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// DXT1圧縮フォーマットテクスチャ
	case FORMAT_DXT1:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_DXT1, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TextureCount; j++ )
				{
					if ( FmtTbl[i] == m_TextureFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// DXT3圧縮フォーマットテクスチャ
	case FORMAT_DXT3:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_DXT3, D3DFMT_DXT1, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TextureCount; j++ )
				{
					if ( FmtTbl[i] == m_TextureFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// DXT5圧縮フォーマットテクスチャ
	case FORMAT_DXT5:
		{
			D3DFORMAT FmtTbl[] = {
				D3DFMT_DXT5, D3DFMT_DXT3, D3DFMT_DXT1, D3DFMT_UNKNOWN,
			};

			for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
			{
				for ( Sint32 j = 0; j < m_TextureCount; j++ )
				{
					if ( FmtTbl[i] == m_TextureFormats[j] )
					{
						return FmtTbl[i];
					}
				}
			}
		}
		break;

		// ユーザー定義2Dテクスチャ
	case FORMAT_TEXTURE_2D:
		{
			for ( Uint32 i = 0; i < m_SurfaceFormatCount[0]; i++ )
			{
				D3DFORMAT Fmt = GetFormat( m_SurfaceFormatTbl[0][i], D3DFMT_UNKNOWN );
				if ( Fmt != D3DFMT_UNKNOWN )
				{
					return Fmt;
				}
			}
		}
		break;

		// ユーザー定義3Dテクスチャ
	case FORMAT_TEXTURE_3D:
		{
			for ( Uint32 i = 0; i < m_SurfaceFormatCount[1]; i++ )
			{
				D3DFORMAT Fmt = GetFormat( m_SurfaceFormatTbl[1][i], D3DFMT_UNKNOWN );
				if ( Fmt != D3DFMT_UNKNOWN )
				{
					return Fmt;
				}
			}
		}
		break;
	}

	return D3DFMT_UNKNOWN;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::GetScreenTypeCount( Bool IsFullColor )
{
	Sint32 Count = 0;

	if ( IsFullColor )
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreenType[1].Format )
			{
				Count++;
			}
		}
	}
	else
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreenType[0].Format )
			{
				Count++;
			}
		}
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetScreenType( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height )
{
	if ( IsFullColor )
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreenType[1].Format )
			{
				if ( No-- == 0 )
				{
					Width = m_ScreenType[i].Width;
					Height = m_ScreenType[i].Height;
					return;
				}
			}
		}
	}
	else
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreenType[0].Format )
			{
				if ( No-- == 0 )
				{
					Width = m_ScreenType[i].Width;
					Height = m_ScreenType[i].Height;
					return;
				}
			}
		}
	}

	Width = 0;
	Height = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::CreateRenderTargetTextureSizeCount( void )
{
	Sint32 Count = 0;

	if ( m_DeviceInfo.MaxTextureWidth <  m_DeviceInfo.MaxTextureHeight )
	{
		for ( Uint32 i = 32; i <= m_DeviceInfo.MaxTextureWidth; i <<= 1 ) Count++;
	}
	else
	{
		for ( Uint32 i = 32; i <= m_DeviceInfo.MaxTextureHeight; i <<= 1 ) Count++;
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight )
{
	Sint32 Count = 0;

	if ( m_DeviceInfo.MaxTextureWidth <  m_DeviceInfo.MaxTextureHeight )
	{
		for ( Uint32 i = 32; i <= m_DeviceInfo.MaxTextureWidth; i <<= 1 )
		{
			if ( Count++ == No )
			{
				*pWidth = *pHeight = i;
				return;
			}
		}
	}
	else
	{
		for ( Uint32 i = 32; i <= m_DeviceInfo.MaxTextureHeight; i <<= 1 )
		{
			if ( Count++ == No )
			{
				*pWidth = *pHeight = i;
				return;
			}
		}
	}

	*pWidth = *pHeight = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetGraphicCardName( wchar_t *pName, Uint32 NameSize )
{
	::StringCbCopy( pName, NameSize, m_GraphicCardName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetGraphicCardDriver( wchar_t *pName, Uint32 NameSize )
{
	::StringCbCopy( pName, NameSize, m_GraphicCardDriver );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetGraphicCardVersion( wchar_t *pName, Uint32 NameSize )
{
	::StringCbCopy( pName, NameSize, m_GraphicCardVersion );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::SetSurfaceFormatTblFor2D( eSurfaceFormat FmtTbl[], Uint32 Count )
{
	MemoryCopy( m_SurfaceFormatTbl[0], FmtTbl, sizeof(eSurfaceFormat) * Count );
	m_SurfaceFormatCount[0] = Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::SetSurfaceFormatTblFor3D( eSurfaceFormat FmtTbl[], Uint32 Count )
{
	MemoryCopy( m_SurfaceFormatTbl[1], FmtTbl, sizeof(eSurfaceFormat) * Count );
	m_SurfaceFormatCount[1] = Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IDevice *CGraphicCard::CreateDevice( void )
{
	if ( m_pDevice == NULL )
	{
		m_pDevice = new CDevice;
		AddChild( m_pDevice );

		// ウィンドウに対して所有デバイスを設定
		GetCorePointer()->SetDevice( m_pDevice );

		Bool IsWindow;
		GetCorePointer()->GetScreenData( NULL, NULL, &IsWindow );
		if ( !m_pDevice->Initialize( IsWindow ) )
		{
			SAFE_RELEASE( m_pDevice );
			return NULL;
		}
	}
	else
	{
		m_pDevice->AddRef();
	}

	return m_pDevice;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CGraphicCard::GetTextureMaxSize( void )
{
	return CPoint2D<Uint32>( m_DeviceInfo.MaxTextureWidth, m_DeviceInfo.MaxTextureHeight );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CGraphicCard::GetTextureSize( CPoint2D<Uint32> Size )
{
	CPoint2D<Uint32> SizeMax = GetTextureMaxSize();
	CPoint2D<Uint32> SizeNew;

	if ( GetNoPow2TextureSupport() )
	{
		SizeNew = Size;
		if ( SizeNew.x > SizeMax.x ) SizeNew.x = SizeMax.x;
		if ( SizeNew.y > SizeMax.y ) SizeNew.y = SizeMax.y;
	}
	else
	{
		for ( SizeNew.x = 1; SizeNew.x < Size.x; SizeNew.x <<= 1 );
		for ( SizeNew.y = 1; SizeNew.y < Size.y; SizeNew.y <<= 1 );
		while ( SizeNew.x > SizeMax.x ) SizeNew.x >>= 1;
		while ( SizeNew.y > SizeMax.y ) SizeNew.y >>= 1;
	}

	return SizeNew;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CGraphicCard::GetCorePointer( void )
{
	return dynamic_cast<CCore*>(GetParent());
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CGraphicCard::CreateDeviceObject( D3DDEVTYPE DeviceType, Uint32 CreateFlag, D3DPRESENT_PARAMETERS &Param, IDirect3DDevice9 **ppDevice )
{
	HRESULT hr = m_pDirect3D->CreateDevice(
					m_GraphicCardNo,
					DeviceType,
					GetCorePointer()->GetWindowHandle(),
					CreateFlag,
					&Param,
					ppDevice );
	return hr;
}


