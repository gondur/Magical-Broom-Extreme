

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Core/COcclusion.h"
#include "Math/Matrix.h"
#include "Math/Vector3D.h"
#include "Surface/CSurface.h"
#include "Surface/CTexture.h"
#include "Render/CRender.h"
#include "Object/CDeviceObjectMgr.h"


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
static const D3DFORMAT BackBufferFormats[] = {
	D3DFMT_X8R8G8B8,
	D3DFMT_X1R5G5B5,
	D3DFMT_R5G6B5,
	D3DFMT_UNKNOWN,
};


//---------------------------------------------------------------
// テクスチャフォーマット
//---------------------------------------------------------------
static D3DFORMAT TextureFormats[] = {
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
static D3DFORMAT DepthFormats[] = {
	D3DFMT_D16,				D3DFMT_D32,				D3DFMT_D24S8,
	D3DFMT_D24X8,			D3DFMT_D24X4S4,			D3DFMT_D24FS8,
	D3DFMT_D15S1,			D3DFMT_UNKNOWN,
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDevice::CDevice()
	: m_pDevice				( NULL )
	, m_pRenderTarget		( NULL )
	, m_pQuery				( NULL )
	, m_hFont				( NULL )
	, m_hOldFont			( NULL )
	, m_hDC					( NULL )
	, m_pCallbackReset		( NULL )
	, m_pCallbackRestore	( NULL )
	, m_pRender				( NULL )
	, m_PrintfBufferPos		( 0 )
{

	MemoryClear( m_PrintfBuffer, sizeof(m_PrintfBuffer) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDevice::~CDevice()
{
	// ウィンドウに対して所有デバイスを設定
	GetGraphicCardPointer()->GetCorePointer()->SetDevice( NULL );

	// 所有オブジェクトの解体
	SAFE_RELEASE( m_pQuery );
	SAFE_RELEASE( m_pRenderTarget );

	// デバイス解放
	if ( m_pDevice != NULL )
	{
		Uint32 Num = m_pDevice->Release();
		m_pDevice = NULL;

		Log_TableBegin();
		Log_PrintCellTitle( 0x008000, L"解放" );
		Log_PrintCellKind( L"IDirect3DDevice" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, L"参照数 %d", Num );
		Log_CellEnd();
		Log_TableEnd();
		Log_TableLine( 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::Initialize( Bool IsWindow )
{
	HRESULT hr = E_FAIL;

	//------------------------------------------------------------------
	// デバイス生成用パラメーターの設定
	//------------------------------------------------------------------
	m_PresentParams[0] = GetGraphicCardPointer()->MakePresentParameters( true, false );
	m_PresentParams[1] = GetGraphicCardPointer()->MakePresentParameters( false, GetGraphicCardPointer()->GetHightColorType() );

	D3DPRESENT_PARAMETERS PresentParam = m_PresentParams[IsWindow ? 0 : 1];

	//------------------------------------------------------------------
	// ３Ｄデバイスの生成
	//------------------------------------------------------------------
	// デバイスタイプ
	const D3DDEVTYPE DeviceType[] = {
		D3DDEVTYPE_HAL,				// DEVICE_CREATE_PUREDEVICE
		D3DDEVTYPE_HAL,				// DEVICE_CREATE_HARDWARE_TNL
		D3DDEVTYPE_HAL,				// DEVICE_CREATE_MIXED_TNL
		D3DDEVTYPE_HAL,				// DEVICE_CREATE_SOFTWARE_TNL
		D3DDEVTYPE_REF,				// DEVICE_CREATE_REF
	};

	//------------------------------------------------------------------
	// 頂点処理
	//------------------------------------------------------------------
	const Uint32 CreateFlag[] = {
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,	// DEVICE_CREATE_PUREDEVICE
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// DEVICE_CREATE_HARDWARE_TNL
		D3DCREATE_MIXED_VERTEXPROCESSING,							// DEVICE_CREATE_MIXED_TNL
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,						// DEVICE_CREATE_SOFTWARE_TNL
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,						// DEVICE_CREATE_REF
	};

	Sint32 DeviceNo = GetGraphicCardPointer()->GetDeviceTypeNo();

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"Direct3Dデバイス" );
	Log_CellBegin( 0 );

	//------------------------------------------------------------------
	// NVPerfHUDでデバイスの作成を試みる
	//------------------------------------------------------------------
	if ( !CreateDeviceByNVPerfHUD( PresentParam ) )
	{
		// 通常のデバイス作成
		do
		{
			// デバイス生成
			hr = GetGraphicCardPointer()->CreateDeviceObject( DeviceType[DeviceNo], CreateFlag[DeviceNo], PresentParam, &m_pDevice );
			if SUCCEEDED( hr ) break;
		}
		while ( ++DeviceNo < 5 );

		// デバイス生成終了
		switch ( DeviceNo )
		{
		case 0:
			Log_PrintStrongLine( 0x000000, L"ピュアデバイスを生成" );
			Log_PrintLine( 0x000000, L"D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, L"D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE" );
			m_pDevice->SetSoftwareVertexProcessing( false );
			break;
		case 1:
			Log_PrintStrongLine( 0x000000, L"ハードウェアTnLデバイスを生成" );
			Log_PrintLine( 0x000000, L"D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, L"D3DCREATE_HARDWARE_VERTEXPROCESSING" );
			m_pDevice->SetSoftwareVertexProcessing( false );
			break;
		case 2:
			Log_PrintStrongLine( 0x000000, L"ソフト＆ハードウェアTnLデバイスを生成" );
			Log_PrintLine( 0x000000, L"D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, L"D3DCREATE_MIXED_VERTEXPROCESSING" );
			m_pDevice->SetSoftwareVertexProcessing( false );
			break;
		case 3:
			Log_PrintStrongLine( 0x000000, L"ソフトウェアTnLデバイスを生成" );
			Log_PrintLine( 0x000000, L"D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, L"D3DCREATE_SOFTWARE_VERTEXPROCESSING" );
			m_pDevice->SetSoftwareVertexProcessing( true );
			break;
		case 4:
		default:
			Log_PrintStrongLine( 0xFF0000, L"デバイス生成エラー" );
			Log_PrintLine( 0xFF0000, GetD3DError(hr) );
			Log_CellEnd();
			Log_TableEnd();
			Log_TableLine( 2 );
			return false;
		}
	}

	Log_PrintLine( 0x000000, L"使用可能テクスチャメモリ容量 %4dMB", GetRestVRAM() );
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//------------------------------------------------------------------
	// デバイス性能
	//------------------------------------------------------------------
	m_pDevice->GetDeviceCaps( &m_Caps );

	//------------------------------------------------------------------
	// 隠蔽問い合わせ
	//------------------------------------------------------------------
	m_pDevice->CreateQuery( D3DQUERYTYPE_OCCLUSION, &m_pQuery );

	//------------------------------------------------------------------
	// レンダリングターゲット取得
	//------------------------------------------------------------------
	m_pDevice->GetRenderTarget( 0, &m_pRenderTarget );
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0 );
	m_pDevice->Present( NULL, NULL, NULL, NULL );
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0 );

	//------------------------------------------------------------------
	// ビューポート初期化
	//------------------------------------------------------------------
	Uint32 Width, Height;
	GetGraphicCardPointer()->GetCorePointer()->GetScreenData( &Width, &Height, NULL );
	m_Viewport.X		= 0;
	m_Viewport.Y		= 0;
	m_Viewport.Width	= Width;
	m_Viewport.Height	= Height;
    m_Viewport.MinZ		= 0.0f;
	m_Viewport.MaxZ		= 1.0f;
	m_pDevice->SetViewport( &m_Viewport );

	//------------------------------------------------------------------
	// 変換行列
	//------------------------------------------------------------------
	D3DXMATRIX Mtx;
	D3DXMatrixIdentity( &Mtx );
    m_pDevice->SetTransform( D3DTS_WORLD,		&Mtx );
    m_pDevice->SetTransform( D3DTS_VIEW,		&Mtx );
    m_pDevice->SetTransform( D3DTS_PROJECTION,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE0,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE1,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE2,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE3,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE4,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE5,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE6,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE7,	&Mtx );

	//------------------------------------------------------------------
	// シェーダー
	//------------------------------------------------------------------
	m_pDevice->SetVertexShader( NULL );
	m_pDevice->SetPixelShader( NULL );

	//------------------------------------------------------------------
	// テクスチャ
	//------------------------------------------------------------------
	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pDevice->SetTexture( i, NULL );
	}

	//------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------
	ResetRenderState();
	ResetSamplerState();
	ResetTextureStageState();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CDevice::GetGraphicCardPointer( void )
{
	return dynamic_cast<CGraphicCard*>(GetParent());
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::CreateDeviceByNVPerfHUD( D3DPRESENT_PARAMETERS &PresentParam )
{
	if ( GetGraphicCardPointer()->GetNVPerfHUD() )
	{
		HRESULT hr = GetGraphicCardPointer()->CreateDeviceObject(
							D3DDEVTYPE_REF,
							D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
							PresentParam,
							&m_pDevice );
		if SUCCEEDED( hr )
		{
			Log_PrintStrongLine( 0x000000, L"NVPerfHUDデバイスを生成" );
			Log_PrintLine( 0x000000, L"D3DDEVTYPE_REF" );
			Log_PrintLine( 0x000000, L"D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE" );
			m_pDevice->SetSoftwareVertexProcessing( false );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::ResetRenderState( void )
{
	Float fPointSize	= 64.0f;
	Float fZero			= 0.0f;
	Float fOne			= 1.0f;
	Uint32 PointSize	= *((Uint32*)&fPointSize);
	Uint32 Zero			= *((Uint32*)&fZero);
	Uint32 One			= *((Uint32*)&fOne);

	m_pDevice->SetRenderState( D3DRS_COLORWRITEENABLE,				D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );
	m_pDevice->SetRenderState( D3DRS_ZENABLE,						D3DZB_FALSE );
	m_pDevice->SetRenderState( D3DRS_FILLMODE,						D3DFILL_SOLID );
	m_pDevice->SetRenderState( D3DRS_SHADEMODE,						D3DSHADE_GOURAUD );
	m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE,					FALSE );
	m_pDevice->SetRenderState( D3DRS_LASTPIXEL,						TRUE );
	m_pDevice->SetRenderState( D3DRS_SRCBLEND,						D3DBLEND_ONE );
	m_pDevice->SetRenderState( D3DRS_DESTBLEND,						D3DBLEND_ZERO );
	m_pDevice->SetRenderState( D3DRS_CULLMODE,						D3DCULL_CCW );
	m_pDevice->SetRenderState( D3DRS_ZFUNC,							D3DCMP_LESSEQUAL );
	m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,				TRUE );
	m_pDevice->SetRenderState( D3DRS_ALPHATESTENABLE,				TRUE );
	m_pDevice->SetRenderState( D3DRS_ALPHAREF,						0x00000000 );
	m_pDevice->SetRenderState( D3DRS_ALPHAFUNC,						D3DCMP_GREATER );
	m_pDevice->SetRenderState( D3DRS_DITHERENABLE,					FALSE );
	m_pDevice->SetRenderState( D3DRS_FOGENABLE,						FALSE );
	m_pDevice->SetRenderState( D3DRS_SPECULARENABLE,				FALSE );
	m_pDevice->SetRenderState( D3DRS_FOGCOLOR,						0x00000000 );
	m_pDevice->SetRenderState( D3DRS_FOGTABLEMODE,					D3DFOG_NONE );
	m_pDevice->SetRenderState( D3DRS_FOGSTART,						Zero );
	m_pDevice->SetRenderState( D3DRS_FOGEND,						One );
	m_pDevice->SetRenderState( D3DRS_FOGDENSITY,					One );
	m_pDevice->SetRenderState( D3DRS_RANGEFOGENABLE,				FALSE );
	m_pDevice->SetRenderState( D3DRS_STENCILENABLE,					FALSE );
	m_pDevice->SetRenderState( D3DRS_STENCILFAIL,					D3DSTENCILOP_KEEP );
	m_pDevice->SetRenderState( D3DRS_STENCILZFAIL,					D3DSTENCILOP_KEEP );
	m_pDevice->SetRenderState( D3DRS_STENCILPASS,					D3DSTENCILOP_KEEP );
	m_pDevice->SetRenderState( D3DRS_STENCILFUNC,					D3DCMP_ALWAYS );
	m_pDevice->SetRenderState( D3DRS_STENCILREF,					0x00000000 );
	m_pDevice->SetRenderState( D3DRS_STENCILMASK,					0xFFFFFFFF );
	m_pDevice->SetRenderState( D3DRS_STENCILWRITEMASK,				0xFFFFFFFF );
	m_pDevice->SetRenderState( D3DRS_TEXTUREFACTOR,					0xFFFFFFFF );
	m_pDevice->SetRenderState( D3DRS_CLIPPING,						TRUE );
	m_pDevice->SetRenderState( D3DRS_LIGHTING,						FALSE );
	m_pDevice->SetRenderState( D3DRS_AMBIENT,						0x00000000 );
	m_pDevice->SetRenderState( D3DRS_FOGVERTEXMODE,					D3DFOG_NONE );
	m_pDevice->SetRenderState( D3DRS_COLORVERTEX,					TRUE );
	m_pDevice->SetRenderState( D3DRS_LOCALVIEWER,					TRUE );
	m_pDevice->SetRenderState( D3DRS_NORMALIZENORMALS,				FALSE );
	m_pDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE,			D3DMCS_COLOR1 );
	m_pDevice->SetRenderState( D3DRS_SPECULARMATERIALSOURCE,		D3DMCS_COLOR2 );
	m_pDevice->SetRenderState( D3DRS_AMBIENTMATERIALSOURCE,			D3DMCS_MATERIAL );
	m_pDevice->SetRenderState( D3DRS_EMISSIVEMATERIALSOURCE,		D3DMCS_MATERIAL );
	m_pDevice->SetRenderState( D3DRS_VERTEXBLEND,					D3DVBF_DISABLE );
	m_pDevice->SetRenderState( D3DRS_CLIPPLANEENABLE,				0x00000000 );
	m_pDevice->SetRenderState( D3DRS_POINTSIZE,						0 );
	m_pDevice->SetRenderState( D3DRS_POINTSIZE_MIN,					One );
	m_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE,				FALSE );
	m_pDevice->SetRenderState( D3DRS_POINTSCALEENABLE,				FALSE );
	m_pDevice->SetRenderState( D3DRS_POINTSCALE_A,					One );
	m_pDevice->SetRenderState( D3DRS_POINTSCALE_B,					Zero );
	m_pDevice->SetRenderState( D3DRS_POINTSCALE_C,					Zero );
	m_pDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS,			FALSE );
	m_pDevice->SetRenderState( D3DRS_MULTISAMPLEMASK,				0xFFFFFFFF );
	m_pDevice->SetRenderState( D3DRS_PATCHEDGESTYLE,				D3DPATCHEDGE_DISCRETE );
	m_pDevice->SetRenderState( D3DRS_DEBUGMONITORTOKEN,				D3DDMT_ENABLE );
	m_pDevice->SetRenderState( D3DRS_POINTSIZE_MAX,					PointSize );
	m_pDevice->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE,		FALSE );
	m_pDevice->SetRenderState( D3DRS_TWEENFACTOR,					Zero );
	m_pDevice->SetRenderState( D3DRS_BLENDOP,						D3DBLENDOP_ADD );
	m_pDevice->SetRenderState( D3DRS_POSITIONDEGREE,				D3DDEGREE_CUBIC );
	m_pDevice->SetRenderState( D3DRS_NORMALDEGREE,					D3DDEGREE_LINEAR );
	m_pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE,				FALSE );
	m_pDevice->SetRenderState( D3DRS_SLOPESCALEDEPTHBIAS,			0 );
	m_pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE,			FALSE );
	m_pDevice->SetRenderState( D3DRS_MINTESSELLATIONLEVEL,			One );
	m_pDevice->SetRenderState( D3DRS_MAXTESSELLATIONLEVEL,			One );
	m_pDevice->SetRenderState( D3DRS_ADAPTIVETESS_X,				Zero );
	m_pDevice->SetRenderState( D3DRS_ADAPTIVETESS_Y,				Zero );
	m_pDevice->SetRenderState( D3DRS_ADAPTIVETESS_Z,				One );
	m_pDevice->SetRenderState( D3DRS_ADAPTIVETESS_W,				Zero );
	m_pDevice->SetRenderState( D3DRS_ENABLEADAPTIVETESSELLATION,	FALSE );
	m_pDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE,			FALSE );
	m_pDevice->SetRenderState( D3DRS_CCW_STENCILFAIL,				D3DSTENCILOP_KEEP );
	m_pDevice->SetRenderState( D3DRS_CCW_STENCILZFAIL,				D3DSTENCILOP_KEEP );
	m_pDevice->SetRenderState( D3DRS_CCW_STENCILPASS,				D3DSTENCILOP_KEEP );
	m_pDevice->SetRenderState( D3DRS_CCW_STENCILFUNC,				D3DCMP_ALWAYS );
	m_pDevice->SetRenderState( D3DRS_COLORWRITEENABLE1,				0x0000000F );
	m_pDevice->SetRenderState( D3DRS_COLORWRITEENABLE2,				0x0000000F );
	m_pDevice->SetRenderState( D3DRS_COLORWRITEENABLE3,				0x0000000F );
	m_pDevice->SetRenderState( D3DRS_BLENDFACTOR,					0xFFFFFFFF );
	m_pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE,				0 );
	m_pDevice->SetRenderState( D3DRS_DEPTHBIAS,						0 );
	m_pDevice->SetRenderState( D3DRS_WRAP0,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP1,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP2,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP3,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP4,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP5,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP6,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP7,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP8,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP9,							0 );
	m_pDevice->SetRenderState( D3DRS_WRAP10,						0 );
	m_pDevice->SetRenderState( D3DRS_WRAP11,						0 );
	m_pDevice->SetRenderState( D3DRS_WRAP12,						0 );
	m_pDevice->SetRenderState( D3DRS_WRAP13,						0 );
	m_pDevice->SetRenderState( D3DRS_WRAP14,						0 );
	m_pDevice->SetRenderState( D3DRS_WRAP15,						0 );
	m_pDevice->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE,		FALSE );
	m_pDevice->SetRenderState( D3DRS_SRCBLENDALPHA,					D3DBLEND_ONE );
	m_pDevice->SetRenderState( D3DRS_DESTBLENDALPHA,				D3DBLEND_ZERO );
	m_pDevice->SetRenderState( D3DRS_BLENDOPALPHA,					D3DBLENDOP_ADD );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::ResetSamplerState( void )
{
	Bool IsMin, IsMag;
	Uint32 Max;
	GetGraphicCardPointer()->GetAnisotropyFilterSupport( IsMin, IsMag, Max );

	for ( Uint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pDevice->SetSamplerState( i, D3DSAMP_ADDRESSU,		D3DTADDRESS_WRAP );
		m_pDevice->SetSamplerState( i, D3DSAMP_ADDRESSV,		D3DTADDRESS_WRAP );
		m_pDevice->SetSamplerState( i, D3DSAMP_ADDRESSW,		D3DTADDRESS_WRAP );
		m_pDevice->SetSamplerState( i, D3DSAMP_BORDERCOLOR,		0x00000000 );
		m_pDevice->SetSamplerState( i, D3DSAMP_MAGFILTER,		D3DTEXF_POINT );
		m_pDevice->SetSamplerState( i, D3DSAMP_MINFILTER,		D3DTEXF_POINT );
		m_pDevice->SetSamplerState( i, D3DSAMP_MIPFILTER,		D3DTEXF_NONE );
		m_pDevice->SetSamplerState( i, D3DSAMP_MIPMAPLODBIAS,	0 );
		m_pDevice->SetSamplerState( i, D3DSAMP_MAXMIPLEVEL,		0 );
		m_pDevice->SetSamplerState( i, D3DSAMP_SRGBTEXTURE,		0 );
		m_pDevice->SetSamplerState( i, D3DSAMP_ELEMENTINDEX,	0 );
		m_pDevice->SetSamplerState( i, D3DSAMP_DMAPOFFSET,		0 );
		m_pDevice->SetSamplerState( i, D3DSAMP_MAXANISOTROPY,	Max );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::ResetTextureStageState( void )
{
	Float fZero		= 0.0f;
	Uint32 Zero		= *((Uint32*)&fZero);

	for ( Uint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pDevice->SetTextureStageState( i, D3DTSS_COLOROP,					(i == 0) ? D3DTOP_MODULATE : D3DTOP_DISABLE );
		m_pDevice->SetTextureStageState( i, D3DTSS_COLORARG1,				D3DTA_TEXTURE );
		m_pDevice->SetTextureStageState( i, D3DTSS_COLORARG2,				D3DTA_CURRENT );
		m_pDevice->SetTextureStageState( i, D3DTSS_ALPHAOP,					(i == 0) ? D3DTOP_MODULATE : D3DTOP_DISABLE );
		m_pDevice->SetTextureStageState( i, D3DTSS_ALPHAARG1,				D3DTA_TEXTURE );
		m_pDevice->SetTextureStageState( i, D3DTSS_ALPHAARG2,				D3DTA_CURRENT );
		m_pDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT00,			Zero );
		m_pDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT01,			Zero );
		m_pDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT10,			Zero );
		m_pDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT11,			Zero );
		m_pDevice->SetTextureStageState( i, D3DTSS_BUMPENVLSCALE,			Zero );
		m_pDevice->SetTextureStageState( i, D3DTSS_BUMPENVLOFFSET,			Zero );
		m_pDevice->SetTextureStageState( i, D3DTSS_TEXCOORDINDEX,			i );
		m_pDevice->SetTextureStageState( i, D3DTSS_TEXTURETRANSFORMFLAGS,	D3DTTFF_DISABLE );
		m_pDevice->SetTextureStageState( i, D3DTSS_COLORARG0,				D3DTA_CURRENT );
		m_pDevice->SetTextureStageState( i, D3DTSS_ALPHAARG0,				D3DTA_CURRENT );
		m_pDevice->SetTextureStageState( i, D3DTSS_RESULTARG,				D3DTA_CURRENT );
		m_pDevice->SetTextureStageState( i, D3DTSS_CONSTANT,				0x00000000 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::ResetDevice( Bool IsChange )
{
	//-------------------------------------------------------
	// デバイスがまだ生成されていない場合は終了
	//-------------------------------------------------------
	if ( m_pDevice == NULL ) return;

	//-------------------------------------------------------
	// スクリーンモードの変更でない時、デバイスが問題ないなら終了
	//-------------------------------------------------------
	if ( !IsChange && (m_pDevice->TestCooperativeLevel() == D3D_OK) ) return;

	//-------------------------------------------------------
	// プレゼンテーションパラメータ取得
	//-------------------------------------------------------
	Uint32 Width, Height;
	Bool IsWindow;
	GetGraphicCardPointer()->GetCorePointer()->GetScreenData( &Width, &Height, &IsWindow );
	m_PresentParams[0].BackBufferWidth	= Width;
	m_PresentParams[0].BackBufferHeight	= Height;
	m_PresentParams[1].BackBufferWidth	= Width;
	m_PresentParams[1].BackBufferHeight	= Height;

	D3DPRESENT_PARAMETERS PresentParam = m_PresentParams[IsWindow ? 0 : 1];

	//-------------------------------------------------------
	// ビデオメモリ内のリソース全解放
	//-------------------------------------------------------
	// ユーザー指定コールバック
	if ( m_pCallbackReset != NULL )
	{
		m_pCallbackReset();
	}

	// レンダラー
	if ( m_pRender != NULL )
	{
		m_pRender->OnLostDevice();
	}

	// レンダリングターゲット
	SAFE_RELEASE( m_pRenderTarget );
	// 隠蔽問い合わせ
	SAFE_RELEASE( m_pQuery );

	//-------------------------------------------------------
	// デバイスのリセット
	//-------------------------------------------------------
	if FAILED( m_pDevice->Reset( &PresentParam ) )
	{
		GetGraphicCardPointer()->GetCorePointer()->MsgBox( MB_ICONERROR, L"ERROR", L"デバイスの復帰に失敗" );
		return;
	}

	//-------------------------------------------------------
	// ステート
	//-------------------------------------------------------
	ResetRenderState();
	ResetSamplerState();
	ResetTextureStageState();

	//-------------------------------------------------------
	// 変換行列
	//-------------------------------------------------------
	D3DXMATRIX Mtx;
	D3DXMatrixIdentity( &Mtx );
    m_pDevice->SetTransform( D3DTS_WORLD,		&Mtx );
    m_pDevice->SetTransform( D3DTS_VIEW,		&Mtx );
    m_pDevice->SetTransform( D3DTS_PROJECTION,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE0,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE1,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE2,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE3,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE4,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE5,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE6,	&Mtx );
    m_pDevice->SetTransform( D3DTS_TEXTURE7,	&Mtx );

	//-------------------------------------------------------
	// ビデオメモリ内のリソース全復旧
	//-------------------------------------------------------
	// レンダリングターゲット
	m_pDevice->GetRenderTarget( 0, &m_pRenderTarget );

	// 隠蔽問い合わせ
	m_pDevice->CreateQuery( D3DQUERYTYPE_OCCLUSION, &m_pQuery );

	// レンダラー
	if ( m_pRender != NULL )
	{
		m_pRender->OnResetDevice();
	}

	// ユーザー指定コールバック
	if ( m_pCallbackRestore != NULL )
	{
		m_pCallbackRestore();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::SetCallbackDeviceReset( void (*pCallback)( void ) )
{
	m_pCallbackReset = pCallback;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::SetCallbackDeviceRestore( void (*pCallback)( void ) )
{
	m_pCallbackRestore = pCallback;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::SetVertexProccessingType( void )
{
	if ( GetGraphicCardPointer()->CheckSupportVertexProccessing() )
	{
		m_pDevice->SetSoftwareVertexProcessing( true );
	}
	else
	{
		m_pDevice->SetSoftwareVertexProcessing( false );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::Clear( CColor Color )
{
	return SUCCEEDED( m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, (D3DCOLOR)Color, 1.0f, 0 ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::ClearDepth( void )
{
	return SUCCEEDED( m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0 ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::ClearStencil( void )
{
	return SUCCEEDED( m_pDevice->Clear( 0, NULL, D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0 ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::ClearDepthStencil( void )
{
	return SUCCEEDED( m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0 ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::Refresh( HWND hWnd )
{
	//----------------------------------------------------------
	// 画面描画文字
	//----------------------------------------------------------
	if ( m_PrintfBufferPos > 0 )
	{
		if ( FontBegin( L"ＭＳ ゴシック", 12 ) )
		{
			Sint32 Px = 5;
			Sint32 Py = 5;
			wchar_t *pStr = m_PrintfBuffer;
			while ( *pStr != L'\0' )
			{
				Uint32 Len = 0;
				wchar_t Temp[1024] = L"";
				while ( (*pStr != L'\n') && (*pStr != L'\0') )
				{
					Temp[Len++] = *pStr++;
				}
				FontDraw( Px, Py, Temp, Len );
				Py += 14;
				pStr++;
			}

			FontEnd();
		}
	}

	//----------------------------------------------------------
	// 画面更新
	//----------------------------------------------------------
	switch ( m_pDevice->Present( NULL, NULL, hWnd, NULL ) )
	{
		// ドライバ内部の意味不明なエラー
	case D3DERR_DRIVERINTERNALERROR:
		GetGraphicCardPointer()->GetCorePointer()->Exit();
		break;
		// デバイスロスト
	case D3DERR_DEVICELOST:
		switch ( m_pDevice->TestCooperativeLevel() )
		{
			// デバイスロスト
		case D3DERR_DEVICELOST:
			::SleepEx( 10, true );
			break;
			// デバイスロスト：リセット可能状態
		case D3DERR_DEVICENOTRESET:
			ResetDevice( false );
			break;
		}
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::FontBegin( const wchar_t *pFontFace, Uint32 FontSize )
{
	HRESULT hr;

	//----------------------------------------------
	// ＤＣ取得
	//----------------------------------------------
	hr = m_pRenderTarget->GetDC( &m_hDC );
	if FAILED( hr )
	{
		return false;
	}

	//----------------------------------------------
	// フォント生成
	//----------------------------------------------
	m_hFont = ::CreateFont(
						FontSize,					// フォント高さ
						0,							// 文字幅
						0,							// テキストの角度	
						0,							// ベースラインとｘ軸との角度
						0,							// フォントの重さ（太さ）
						false,						// イタリック体
						false,						// アンダーライン
						false,						// 打ち消し線
						SHIFTJIS_CHARSET,			// 文字セット
						OUT_TT_PRECIS,				// 出力精度
						CLIP_DEFAULT_PRECIS,		// クリッピング精度
						PROOF_QUALITY,				// 出力品質
						FIXED_PITCH | FF_MODERN,	// ピッチとファミリー
						pFontFace );				// 書体名

	// フォント設定
	m_hOldFont = (HFONT)::SelectObject( m_hDC, m_hFont );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::FontDraw( Sint32 Px, Sint32 Py, const wchar_t *pStr, Uint32 Len )
{
	// 拝啓色
	::SetBkColor( m_hDC, RGB(0,0,0) );
	::SetBkMode( m_hDC, TRANSPARENT );

	// フォント色
	::SetTextColor( m_hDC, RGB(0,0,0) );
	::TextOut( m_hDC, Px+1, Py+1, pStr, Len );

	// フォント色
	::SetTextColor( m_hDC, RGB(255,255,255) );
	::TextOut( m_hDC, Px, Py, pStr, Len );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::FontEnd( void )
{
	::SelectObject( m_hDC, m_hOldFont );
	::DeleteObject( m_hFont );

	m_pRenderTarget->ReleaseDC( m_hDC );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::Clip( RECT *pDst, RECT *pSrc )
{
	// ビューポート
	Sint32 x1 = m_Viewport.X;
	Sint32 y1 = m_Viewport.Y;
	Sint32 x2 = x1 + m_Viewport.Width;
	Sint32 y2 = y1 + m_Viewport.Height;

	// 転送先矩形
	Sint32 dx1 = pDst->left;
	Sint32 dy1 = pDst->top;
	Sint32 dx2 = pDst->right;
	Sint32 dy2 = pDst->bottom;

	// 転送元矩形
	Sint32 sx1 = pSrc->left;
	Sint32 sy1 = pSrc->top;
	Sint32 sx2 = pSrc->right;
	Sint32 sy2 = pSrc->bottom;

	// サイズ比率
	Float fx = toF(sx2 - sx1) / toF(dx2 - dx1);
	Float fy = toF(sy2 - sy1) / toF(dy2 - dy1);

	// 左チェック
	if ( dx1 < x1 )
	{
		sx1 = sx1 + toI(toF(x1 - dx1) * fx);
		dx1 = x1;
	}
	// 上チェック
	if ( dy1 < y1 )
	{
		sy1 = sy1 + toI(toF(y1 - dy1) * fy);
		dy1 = y1;
	}
	// 右チェック
	if ( dx2 > x2 )
	{
		sx2 = sx2 - toI(toF(dx2 - x2) * fx);
		dx2 = x2;
	}
	// 下チェック
	if ( dy2 > y2 )
	{
		sy2 = sy2 - toI(toF(dy2 - y2) * fy);
		dy2 = y2;
	}

	// 転送先矩形
	pDst->left		= dx1;
	pDst->top		= dy1;
	pDst->right		= dx2;
	pDst->bottom	= dy2;

	// 転送元矩形
	pSrc->left		= sx1;
	pSrc->top		= sy1;
	pSrc->right		= sx2;
	pSrc->bottom	= sy2;

	return ((dx1 < dx2) && (dy1 < dy2));
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CDevice::GetRestVRAM( void )
{
	return m_pDevice->GetAvailableTextureMem() / 1024 / 1024;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDevice::IsSupportedPS( Uint32 Major, Uint32 Minor )
{
	return m_Caps.PixelShaderVersion >= D3DPS_VERSION( Major, Minor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRect2D<Sint32> CDevice::GetViewport( void )
{
	return CRect2D<Sint32>( m_Viewport.X, m_Viewport.Y, m_Viewport.Width, m_Viewport.Height );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::SetDialogBoxType( Bool IsType )
{
	if ( m_pDevice != NULL )
	{
		m_pDevice->SetDialogBoxMode( IsType );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HWND CDevice::GetCreationWindow( void )
{
	D3DDEVICE_CREATION_PARAMETERS Param;
	m_pDevice->GetCreationParameters( &Param );
	return Param.hFocusWindow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::Printf( const wchar_t *pStr, ... )
{
	wchar_t *pBuff = m_PrintfBuffer + m_PrintfBufferPos;
	Uint32 Size = sizeof(m_PrintfBuffer) - m_PrintfBufferPos;

	::StringCbVPrintf( pBuff, Size, pStr, (char*)(&pStr + 1) );

	size_t Len = wcslen( pBuff );

	m_PrintfBufferPos += (Uint32)Len;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::Cls( void )
{
	m_PrintfBufferPos = 0;
	MemoryClear( m_PrintfBuffer, sizeof(m_PrintfBuffer) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::SetScissor( Bool IsEnable, CRect2D<Sint32> Rect )
{
	m_pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, IsEnable );
	if ( IsEnable )
	{
		RECT Scissor = { Rect.x, Rect.y, Rect.x + Rect.w, Rect.y + Rect.h };
		m_pDevice->SetScissorRect( &Scissor );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IRender *CDevice::CreateRender( void )
{
	if ( m_pRender == NULL )
	{
		m_pRender = new CRender( this );
		AddChild( m_pRender );
		m_pRender->Initialize();
	}
	else
	{
		m_pRender->AddRef();
	}

	return m_pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
COcclusion *CDevice::CeateOcclusion( void )
{
	return new COcclusion( this );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::BeginScene( void )
{
	m_pDevice->BeginScene();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDevice::EndScene( void )
{
	m_pDevice->EndScene();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetRenderState( D3DRENDERSTATETYPE State, Uint32 Value )
{
	return m_pDevice->SetRenderState( State, Value );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetSamplerState( Uint32 Sampler, D3DSAMPLERSTATETYPE Type, Uint32 Value )
{
	return m_pDevice->SetSamplerState( Sampler, Type, Value );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetTextureStageState( Uint32 Stage, D3DTEXTURESTAGESTATETYPE Type, Uint32 Value )
{
	return m_pDevice->SetTextureStageState( Stage, Type, Value );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateDepthStencilSurface( Uint32 Width, Uint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface )
{
	return m_pDevice->CreateDepthStencilSurface( Width, Height, Format, D3DMULTISAMPLE_NONE, D3DMULTISAMPLE_NONE, true, ppSurface, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateOffscreenPlainSurface( Uint32 Width, Uint32 Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface )
{
	return m_pDevice->CreateOffscreenPlainSurface( Width, Height, Format, Pool, ppSurface, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateTexture( Uint32 Width, Uint32 Height, Uint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture )
{
	return m_pDevice->CreateTexture( Width, Height, Levels, Usage, Format, Pool, ppTexture, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateRenderTarget( Uint32 Width, Uint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface )
{
	return m_pDevice->CreateRenderTarget( Width, Height, Format, D3DMULTISAMPLE_NONE, D3DMULTISAMPLE_NONE, true, ppSurface, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::GetRenderTargetData( IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface )
{
	return m_pDevice->GetRenderTargetData( pRenderTarget, pDestSurface );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::StretchRect( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter )
{
	return m_pDevice->StretchRect( pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::UpdateTexture( IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture )
{
	return m_pDevice->UpdateTexture( pSourceTexture, pDestinationTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetDepthStencilSurface( IDirect3DSurface9 *pZStencil )
{
	return m_pDevice->SetDepthStencilSurface( pZStencil );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetRenderTarget( IDirect3DSurface9 *pRenderTarget )
{
	// NULLの時はバックバッファに
	if ( pRenderTarget == NULL )
	{
		pRenderTarget = m_pRenderTarget;
	}

	// レンダリングターゲット設定
	HRESULT hr = m_pDevice->SetRenderTarget( 0, pRenderTarget );
	if SUCCEEDED( hr )
	{
		// ビューポートをサーフェイスに合わせる
		D3DSURFACE_DESC Desc;
		pRenderTarget->GetDesc( &Desc );
		m_Viewport.X      = 0;
		m_Viewport.Y      = 0;
		m_Viewport.Width  = Desc.Width;
		m_Viewport.Height = Desc.Height;
		m_pDevice->SetViewport( &m_Viewport );
	}
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CopyToBackBuffer( IDirect3DSurface9 *pRenderTarget )
{
	return m_pDevice->StretchRect( pRenderTarget, NULL, m_pRenderTarget, NULL, D3DTEXF_LINEAR );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetSoftwareVertexProcessing( BOOL bSoftware )
{
	return m_pDevice->SetSoftwareVertexProcessing( bSoftware );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetTexture( Uint32 Stage, IDirect3DTexture9 *pTex )
{
	return m_pDevice->SetTexture( Stage, pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateVertexBuffer( Uint32 Length, IDirect3DVertexBuffer9** ppVertexBuffer, Bool IsDynamic )
{
	Uint32 Usage = IsDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
	return m_pDevice->CreateVertexBuffer( Length, Usage, 0, D3DPOOL_DEFAULT, ppVertexBuffer, NULL );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateIndexBuffer( Uint32 Length, IDirect3DIndexBuffer9** ppIndexBuffer, Bool IsDynamic )
{
	Uint32 Usage = IsDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
	return m_pDevice->CreateIndexBuffer( Length, Usage, D3DFMT_INDEX16, D3DPOOL_DEFAULT, ppIndexBuffer, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateVertexDeclaration( const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl )
{
	return m_pDevice->CreateVertexDeclaration( pVertexElements, ppDecl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetStreamSource( Uint32 StreamNumber, IDirect3DVertexBuffer9 *pStreamData, Uint32 Stride )
{
	return m_pDevice->SetStreamSource( StreamNumber, pStreamData, 0, Stride );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetIndices( IDirect3DIndexBuffer9 *pIndexData )
{
	return m_pDevice->SetIndices( pIndexData );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::SetVertexDeclaration( IDirect3DVertexDeclaration9 *pDecl )
{
	return m_pDevice->SetVertexDeclaration( pDecl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::DrawPrimitive( D3DPRIMITIVETYPE PrimitiveType, Uint32 PrimitiveCount )
{
	return m_pDevice->DrawPrimitive( PrimitiveType, 0, PrimitiveCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::DrawIndexedPrimitive( D3DPRIMITIVETYPE PrimitiveType, Uint32 VertexCount, Uint32 PrimitiveCount )
{
	return m_pDevice->DrawIndexedPrimitive( PrimitiveType, 0, 0, VertexCount, 0, PrimitiveCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::DrawMesh( Uint32 VertexStart, Uint32 VertexCount, Uint32 IndexStart, Uint32 PrimitiveCount )
{
	return m_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, VertexStart, VertexCount, IndexStart, PrimitiveCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateOcclusionQuery( IDirect3DQuery9 **ppQuery )
{
	return m_pDevice->CreateQuery( D3DQUERYTYPE_OCCLUSION, ppQuery );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CDevice::CreateEffect( LPCVOID pSrcData, UINT SrcDataLen, LPD3DXEFFECT *ppEffect, LPD3DXBUFFER *ppCompilationErrors )
{
	return ::D3DXCreateEffect(
					m_pDevice,
					pSrcData,
					SrcDataLen,
					NULL,
					NULL,
					0,
					NULL,
					ppEffect,
					ppCompilationErrors );
}


