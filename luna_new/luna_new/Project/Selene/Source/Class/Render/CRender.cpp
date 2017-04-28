

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Core/CCore.h"
#include "Render/CShader.h"
#include "Render/CRender.h"
#include "Render/CPostEffect.h"
#include "Render/CIndexBuffer.h"
#include "Render/CVertexBuffer.h"
#include "Render/CVertexStream.h"
#include "Render/CFont.h"
#include "Render/2D/CPrimitive2DBaseMgr.h"
#include "Render/2D/CFontSprite2D.h"
#include "Render/2D/CSprite2D.h"
#include "Render/2D/CPointPrimitive2D.h"
#include "Render/2D/CLinePrimitive2D.h"
#include "Render/3D/CPrimitive3DBaseMgr.h"
#include "Render/2D/CPrimitive2D.h"
#include "Render/3D/CPointPrimitive3D.h"
#include "Render/3D/CLinePrimitive3D.h"
#include "Render/3D/CPrimitive3D.h"
#include "Render/Model/CModel.h"
#include "Render/Model/CModelMgr.h"
#include "Object/CDeviceObjectMgr.h"
#include "Surface/CSurfaceMgr.h"
#include "Surface/CTextureMgr.h"
#include "Surface/CSurface.h"
#include "Surface/CTexture.h"
#include "Scene/CSceneManager.h"
#include "File/CFileManager.h"

#include "NullDevice/Surface/NullSurface.h"
#include "NullDevice/Surface/NullTexture.h"
#include "NullDevice/Render/2D/NullPointPrimitive2D.h"
#include "NullDevice/Render/2D/NullLinePrimitive2D.h"
#include "NullDevice/Render/2D/NullPrimitive2D.h"
#include "NullDevice/Render/2D/NullSprite2D.h"
#include "NullDevice/Render/2D/NullFontSprite2D.h"
#include "NullDevice/Render/3D/NullPointPrimitive3D.h"
#include "NullDevice/Render/3D/NullLinePrimitive3D.h"
#include "NullDevice/Render/3D/NullPrimitive3D.h"
#include "NullDevice/Render/Model/NullModel.h"
#include "NullDevice/Scene/NullSceneManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
static const D3DPRIMITIVETYPE g_PrimitiveTypeTbl[] = {
	D3DPT_POINTLIST,		// PRIMITIVE_POINT
	D3DPT_LINELIST,			// PRIMITIVE_LINE
	D3DPT_LINESTRIP,		// PRIMITIVE_LINE_STRIP
	D3DPT_TRIANGLELIST,		// PRIMITIVE_TRIANGLE
	D3DPT_TRIANGLESTRIP,	// PRIMITIVE_TRIANGLE_STRIP
	D3DPT_TRIANGLEFAN,		// PRIMITIVE_TRIANGLE_FAN
};

// ２Ｄ用
static const D3DVERTEXELEMENT9 g_VertexElement2D[] = {
    { 0,  0, D3DDECLTYPE_FLOAT4,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT,	0 },
	{ 0, 16, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
};

// ２Ｄ＋テクスチャ用
static const D3DVERTEXELEMENT9 g_VertexElementTex2D[] = {
    { 0,  0, D3DDECLTYPE_FLOAT4,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT,	0 },
	{ 0, 16, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
	{ 0, 20, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
};

// トランスフォーム用
static const D3DVERTEXELEMENT9 g_VertexElement3DBase[] = {
    { 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
	{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
};

// テクスチャ用
static const D3DVERTEXELEMENT9 g_VertexElement3DTexture[] = {
	{ 1,  0, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
	{ 1,  8, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	1 },
};

// ライティング用
static const D3DVERTEXELEMENT9 g_VertexElement3DLight[] = {
    { 2, 0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0 },
};

// バンプ用
static const D3DVERTEXELEMENT9 g_VertexElement3DBump[] = {
    { 3, 0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,	0 },
};

// アニメーション用
static const D3DVERTEXELEMENT9 g_VertexElement3DAnimation[] = {
    { 4,  0, D3DDECLTYPE_FLOAT1,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,	0 },
    { 4,  4, D3DDECLTYPE_UBYTE4,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES,	0 },
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender::CRender( CDevice *pDevice )
{
	m_pListPrimitive2DMgr	= new CPrimitive2DBaseMgr( pDevice );
	m_pVertexStreamMgr		= new CDeviceObjectMgr( pDevice );
	m_pVertexBufferMgr		= new CDeviceObjectMgr( pDevice );
	m_pIndexBufferMgr		= new CDeviceObjectMgr( pDevice );
	m_pShaderMgr			= new CDeviceObjectMgr( pDevice );
	m_pSurfaceMgr			= new CSurfaceMgr( pDevice );
	m_pTextureMgr			= new CTextureMgr( pDevice );

#if ENABLE_3D
	m_pListPrimitive3DMgr	= new CPrimitive3DBaseMgr( pDevice );
	m_pListModelMgr			= new CModelMgr( pDevice );

	// シェーダー
	CRenderData::Initialize( this );
#endif // ENABLE_3D

	//------------------------------------------------------------------
	// 変数初期化
	//------------------------------------------------------------------
	m_pActiveScene	= NULL;
	m_pDepthStencil	= NULL;
	m_pRenderTarget	= NULL;
	m_pPostEffect	= NULL;

	for ( Uint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_fOffset[i] = 0.0f;
	}

	m_RenderStatePos = 0;
	for ( Uint32 i = 0; i < STATE_STACK_MAX; i++ )
	{
		m_RenderState[i].DrawType			= DRAW_TYPE_NORMAL;
		m_RenderState[i].CullType			= CULL_FRONT;
		m_RenderState[i].FogColor			= 0x00000000;
		m_RenderState[i].IsDepthTestEnable	= false;
		m_RenderState[i].IsDepthWriteEnable	= false;
		for ( Uint32 j = 0; j < TEXTURE_STAGE_MAX; j++ )
		{
			m_RenderState[i].FilterType[j]	  = TEXTURE_FILTER_DISABLE;
			m_RenderState[i].AddressType[j]	  = TEXTURE_ADDRESS_REPEAT;
			m_RenderState[i].OperationType[j] = (j == 0) ? TEXTURE_OP_MUL : TEXTURE_OP_NONE;
			m_RenderState[i].pTextureTbl[j]   = NULL;
		}
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender::~CRender()
{
#if ENABLE_3D
	// シェーダー
	CRenderData::Finalize();

	SAFE_DELETE( m_pListModelMgr );
	SAFE_DELETE( m_pListPrimitive3DMgr );
#endif // ENABLE_3D

	SAFE_DELETE( m_pTextureMgr );
	SAFE_DELETE( m_pSurfaceMgr );
	SAFE_DELETE( m_pListPrimitive2DMgr );
	SAFE_DELETE( m_pVertexStreamMgr );
	SAFE_DELETE( m_pVertexBufferMgr );
	SAFE_DELETE( m_pIndexBufferMgr );
	SAFE_DELETE( m_pShaderMgr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::Initialize( void )
{
	m_TextureConfig.SetFormat( FORMAT_TEXTURE_2D );
	m_TextureConfig.SetColorKey( 0x00000000 );

	//------------------------------------------------------------------
	// デフォルトステート
	//------------------------------------------------------------------
	StateInit();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::OnLostDevice( void )
{
	m_pTextureMgr->OnLostDevice();
	m_pSurfaceMgr->OnLostDevice();

	m_pShaderMgr->OnLostDevice();
	m_pVertexStreamMgr->OnLostDevice();
	m_pVertexBufferMgr->OnLostDevice();
	m_pIndexBufferMgr->OnLostDevice();

	m_pListPrimitive2DMgr->OnLostDevice();

#if ENABLE_3D
	m_pListPrimitive3DMgr->OnLostDevice();
#endif // ENABLE_3D
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::OnResetDevice( void )
{
	m_pTextureMgr->OnResetDevice();
	m_pSurfaceMgr->OnResetDevice();

	m_pShaderMgr->OnResetDevice();
	m_pVertexStreamMgr->OnResetDevice();
	m_pVertexBufferMgr->OnResetDevice();
	m_pIndexBufferMgr->OnResetDevice();

	m_pListPrimitive2DMgr->OnResetDevice();

#if ENABLE_3D
	m_pListPrimitive3DMgr->OnResetDevice();
#endif // ENABLE_3D

	if ( m_pDepthStencil != NULL )
	{
		m_pDepthStencil->SetDepthStencil();
	}

	if ( m_pRenderTarget != NULL )
	{
		m_pRenderTarget->SetRenderTarget();
	}

	// ステート
	SRenderState Temp = m_RenderState[m_RenderStatePos];
	// デフォルト値上書き
	StateInit();
	// 前回のステートで再設定
	SetDrawType( Temp.DrawType );
	SetCullType( Temp.CullType );
	SetFogColor( Temp.FogColor );
	SetDepthTestEnable( Temp.IsDepthTestEnable );
	SetDepthWriteEnable( Temp.IsDepthWriteEnable );
	SetAlphaTestEnable( Temp.IsAlphaTestEnable );
	for ( Uint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTextureFilterType( i, Temp.FilterType[i] );
		SetTextureAddressType( i, Temp.AddressType[i] );
		SetTextureOperationType( i, Temp.OperationType[i] );
		SetTexture( i, Temp.pTextureTbl[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDevice *CRender::GetDevicePointer( void )
{
	return dynamic_cast<CDevice*>(GetParent());
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRender::GetTextureOffset( Uint32 Stage )
{
	return m_fOffset[Stage];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CRender::GetSize( Uint32 Flag )
{
	Uint32 Size = 0;

	if ( Flag & VERTEX_ELEMENT_PRIMITIVE   ) Size += sizeof(SVertex2D);
	if ( Flag & VERTEX_ELEMENT_SPRITE      ) Size += sizeof(SVertex2DTex);
	if ( Flag & VERTEX_ELEMENT_3DBASE      ) Size += sizeof(SVertex3DBase);
	if ( Flag & VERTEX_ELEMENT_3DTEXTURE   ) Size += sizeof(SVertex3DTexture);
	if ( Flag & VERTEX_ELEMENT_3DLIGHT     ) Size += sizeof(SVertex3DLight);
	if ( Flag & VERTEX_ELEMENT_3DBUMP      ) Size += sizeof(SVertex3DBump);
	if ( Flag & VERTEX_ELEMENT_3DANIMATION ) Size += sizeof(SVertex3DAnimation);

	return Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPostEffect *CRender::CreatePostEffect( void )
{
	if ( m_pPostEffect != NULL )
	{
		m_pPostEffect->AddRef();
	}
	else
	{
		m_pPostEffect = new CPostEffect( this );
	}

	return m_pPostEffect;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture *CRender::GetTexture( Uint32 Stage )
{
	return dynamic_cast<CTexture*>(m_RenderState[m_RenderStatePos].pTextureTbl[Stage]);
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetStream( CVertexStream *pStream )
{
	if ( pStream == NULL ) return false;

	return SUCCEEDED( pStream->SetDevice() );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetVertex( Uint32 StreamNo, CVertexBuffer *pVertex )
{
	if ( pVertex == NULL ) return false;

	return SUCCEEDED( pVertex->SetDevice( StreamNo ) );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetIndex( CIndexBuffer *pIndex )
{
	if ( pIndex == NULL ) return false;

	return SUCCEEDED( pIndex->SetDevice() );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DrawPrimitive( ePrimitiveType PrimitiveType, Uint32 PrimitiveCount )
{
	if ( PrimitiveCount == 0 ) return false;

	HRESULT hr = GetDevicePointer()->DrawPrimitive( g_PrimitiveTypeTbl[PrimitiveType], PrimitiveCount );
	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DrawIndexedPrimitive( ePrimitiveType PrimitiveType, Uint32 VertexCount, Uint32 PrimitiveCount )
{
	if ( PrimitiveCount == 0 ) return false;

	HRESULT hr = GetDevicePointer()->DrawIndexedPrimitive( g_PrimitiveTypeTbl[PrimitiveType], VertexCount, PrimitiveCount );
	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DrawMesh( Uint32 VertexStart, Uint32 VertexCount, Uint32 IndexStart, Uint32 IndexCount )
{
	if ( IndexCount == 0 ) return false;

	HRESULT hr = GetDevicePointer()->DrawMesh( VertexStart, VertexCount, IndexStart, IndexCount );
	return SUCCEEDED( hr );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::ResetRenderTarget( void )
{
	m_pRenderTarget = NULL;
	GetDevicePointer()->SetRenderTarget( NULL );
	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetRenderTarget( ITexture *pTexture )
{
	m_pRenderTarget = dynamic_cast<CBaseSurface*>(pTexture);
	if ( m_pRenderTarget == NULL )
	{
		GetDevicePointer()->SetRenderTarget( NULL );
		return true;
	}
	else
	{
		return m_pRenderTarget->SetRenderTarget();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetRenderTarget( ISurface *pSurface )
{
	m_pRenderTarget = dynamic_cast<CBaseSurface*>(pSurface);
	if ( m_pRenderTarget == NULL )
	{
		GetDevicePointer()->SetRenderTarget( NULL );
		return true;
	}
	else
	{
		return m_pRenderTarget->SetRenderTarget();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::GetRenderTarget( ITexture **ppTexture )
{
	*ppTexture = dynamic_cast<ITexture*>(m_pRenderTarget);
	if ( *ppTexture != NULL )
	{
		(*ppTexture)->AddRef();
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::GetRenderTarget( ISurface **ppSurface )
{
	*ppSurface = dynamic_cast<ISurface*>(m_pRenderTarget);
	if ( *ppSurface != NULL )
	{
		(*ppSurface)->AddRef();
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetDepthStencil( ISurface *pSurface )
{
	m_pDepthStencil	= dynamic_cast<CBaseSurface*>(pSurface);
	if ( m_pDepthStencil == NULL )
	{
		GetDevicePointer()->SetDepthStencilSurface( NULL );
		return true;
	}
	else
	{
		return m_pDepthStencil->SetDepthStencil();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISceneManager *CRender::CreateSceneManager( eSceneMode Mode, eSceneModeOption Option )
{
#if ENABLE_3D
	ISceneManager *pScene = new CSceneManager( this, Mode, Option );
	if ( pScene != NULL )
	{
		return pScene;
	}
#endif // ENABLE_3D

	static NullSceneManager Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
#if ENABLE_3D
Bool CRender::ActivateScene( CSceneManager *pScene )
{
	if ( m_pActiveScene == NULL )
	{
		if ( pScene->IsInvalid() )
		{
			return false;
		}
		else
		{
			m_pActiveScene = pScene;
		}
		return true;
	}
	else
	{
		return false;
	}
}
#endif // ENABLE_3D

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
#if ENABLE_3D
Bool CRender::DeActivateScene( CSceneManager *pScene )
{
	if ( m_pActiveScene == pScene )
	{
		m_pActiveScene = NULL;
		return true;
	}
	else
	{
		return false;
	}
}
#endif // ENABLE_3D

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
#if ENABLE_3D
CSceneManager *CRender::GetSceneManagerPointer( void )
{
	return m_pActiveScene;
}
#endif // ENABLE_3D

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::Begin( void )
{
	GetDevicePointer()->BeginScene();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::End( void )
{
	GetDevicePointer()->EndScene();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexStream *CRender::CreateVertexStreamDirect( void )
{
	return new CVertexStream( m_pVertexStreamMgr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexStream *CRender::CreateVertexStream( Uint32 Flag )
{
	D3DVERTEXELEMENT9 ElementEnd = D3DDECL_END();
	D3DVERTEXELEMENT9 VertexElement[32];
	Uint32 Offset = 0;

	// ２Ｄ
	if ( (Flag & VERTEX_ELEMENT_PRIMITIVE) != 0 )
	{
		Uint32 Cnt = sizeof(g_VertexElement2D) / sizeof(D3DVERTEXELEMENT9);
		for ( Uint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElement2D[i];
			Offset++;
		}
	}
	// ２Ｄ
	ef ( (Flag & VERTEX_ELEMENT_SPRITE) != 0 )
	{
		Uint32 Cnt = sizeof(g_VertexElementTex2D) / sizeof(D3DVERTEXELEMENT9);
		for ( Uint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElementTex2D[i];
			Offset++;
		}
	}
	// ３Ｄ座標
	ef ( (Flag & VERTEX_ELEMENT_3DBASE) != 0 )
	{
		Uint32 Cnt = sizeof(g_VertexElement3DBase) / sizeof(D3DVERTEXELEMENT9);
		for ( Uint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElement3DBase[i];
			Offset++;
		}

		// テクスチャ
		if ( (Flag & VERTEX_ELEMENT_3DTEXTURE) != 0 )
		{
			Uint32 Cnt = sizeof(g_VertexElement3DTexture) / sizeof(D3DVERTEXELEMENT9);
			for ( Uint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DTexture[i];
				Offset++;
			}
		}

		// ライト
		if ( (Flag & VERTEX_ELEMENT_3DLIGHT) != 0 )
		{
			Uint32 Cnt = sizeof(g_VertexElement3DLight) / sizeof(D3DVERTEXELEMENT9);
			for ( Uint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DLight[i];
				Offset++;
			}
		}

		// ３Ｄバンプ
		if ( (Flag & VERTEX_ELEMENT_3DBUMP) != 0 )
		{
			Uint32 Cnt = sizeof(g_VertexElement3DBump) / sizeof(D3DVERTEXELEMENT9);
			for ( Uint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DBump[i];
				Offset++;
			}
		}

		// ３Ｄアニメーション
		if ( (Flag & VERTEX_ELEMENT_3DANIMATION) != 0 )
		{
			Uint32 Cnt = sizeof(g_VertexElement3DAnimation) / sizeof(D3DVERTEXELEMENT9);
			for ( Uint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DAnimation[i];
				Offset++;
			}
		}
	}

	// 終端
	VertexElement[Offset] = ElementEnd;
	Offset++;

	// ストリーム定義生成
	CVertexStream *pData = new CVertexStream( m_pVertexStreamMgr );
	if ( !pData->Create( VertexElement ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexBuffer *CRender::CreateVertexBuffer( Uint32 Count, Uint32 VertexSize, Bool IsDynamic )
{
	CVertexBuffer *pData = new CVertexBuffer( m_pVertexBufferMgr );
	if ( !pData->Create( Count, VertexSize, IsDynamic ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CIndexBuffer *CRender::CreateIndexBuffer( Uint32 Count, Bool IsDynamic )
{
	CIndexBuffer *pData = new CIndexBuffer( m_pIndexBufferMgr );
	if ( !pData->Create( Count, IsDynamic ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CShader *CRender::CreateShaderFromFile( const wchar_t *pFileName )
{
	CShader *pData = new CShader( m_pShaderMgr );
	if ( !pData->CreateFromFile( pFileName ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CShader *CRender::CreateShaderFromMemory( const Uint8 *pShader, Uint32 Size )
{
	CShader *pData = new CShader( m_pShaderMgr );
	if ( !pData->CreateFromMemory( pShader, Size ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPointPrimitive2D *CRender::CreatePointPrimitive2D( Uint32 PointMax )
{
	CPointPrimitive2D *pData = new CPointPrimitive2D( this, m_pListPrimitive2DMgr );
	if ( !pData->Create( PointMax ) )
	{
		SAFE_RELEASE( pData );
		static NullPointPrimitive2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ILinePrimitive2D *CRender::CreateLinePrimitive2D( Uint32 LineMax )
{
	CLinePrimitive2D *pData = new CLinePrimitive2D( this, m_pListPrimitive2DMgr );
	if ( !pData->Create( LineMax ) )
	{
		SAFE_RELEASE( pData );
		static NullLinePrimitive2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPrimitive2D *CRender::CreatePrimitive2D( Uint32 PrimitiveMax )
{
	CPrimitive2D *pData = new CPrimitive2D( this, m_pListPrimitive2DMgr );
	if ( !pData->Create( PrimitiveMax ) )
	{
		SAFE_RELEASE( pData );
		static NullPrimitive2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISprite2D *CRender::CreateSprite2D( Uint32 PrimitiveMax, ITexture *pTexture )
{
	CSprite2D *pData = new CSprite2D( this, m_pListPrimitive2DMgr, dynamic_cast<CTexture*>(pTexture) );
	if ( !pData->Create( PrimitiveMax ) )
	{
		SAFE_RELEASE( pData );
		static NullSprite2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IFontSprite2D *CRender::CreateFontSprite2D( const wchar_t *pBuffer, Uint32 FontMax, const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold, Bool IsAntialias )
{
	CFont *pFont = CreateFont( pFontFace, FontSize, IsItalic, IsBold );
	if ( pFont != NULL )
	{
		CFontSprite2D *pData = new CFontSprite2D( this, m_pListPrimitive2DMgr );
		if ( pData->Create( pBuffer, FontMax, pFont, IsAntialias ) )
		{
			SAFE_RELEASE( pFont );
			return pData;
		}

		SAFE_RELEASE( pFont );
		SAFE_RELEASE( pData );
	}

	static NullFontSprite2D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IFontSprite2D *CRender::CreateFontSprite2DFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 FontMax )
{
	CFontSprite2D *pData = new CFontSprite2D( this, m_pListPrimitive2DMgr );
	if ( pData->CreateFromFile( pFileName, pExt, FontMax ) )
	{
		return pData;
	}

	SAFE_RELEASE( pData );

	static NullFontSprite2D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPointPrimitive3D *CRender::CreatePointPrimitive3D( Uint32 VertexMax, Bool IsDynamic )
{
#if ENABLE_3D
	CPointPrimitive3D *pData = new CPointPrimitive3D( this, m_pListPrimitive3DMgr );
	if ( pData != NULL )
	{
		if ( pData->Create( VertexMax, IsDynamic) )
		{
			return pData;
		}

		SAFE_RELEASE( pData );
	}
#endif // ENABLE_3D

	static NullPointPrimitive3D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ILinePrimitive3D *CRender::CreateLinePrimitive3D( Uint32 VertexMax, Bool IsDynamic )
{
#if ENABLE_3D
	CLinePrimitive3D *pData = new CLinePrimitive3D( this, m_pListPrimitive3DMgr );
	if ( pData != NULL )
	{
		if ( pData->Create( VertexMax, IsDynamic) )
		{
			return pData;
		}

		SAFE_RELEASE( pData );
	}
#endif // ENABLE_3D

	static NullLinePrimitive3D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPrimitive3D *CRender::CreatePrimitive3D( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic )
{
#if ENABLE_3D
	CPrimitive3D *pData = new CPrimitive3D( this, m_pListPrimitive3DMgr );
	if ( pData != NULL )
	{
		if ( pData->Create( VertexMax, IndexMax, VertexFlag, IsDynamic ) )
		{
			return pData;
		}

		SAFE_RELEASE( pData );
	}
#endif // ENABLE_3D

	static NullPrimitive3D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IModel *CRender::CreateModelFromFile( const wchar_t *pFileName )
{
#if ENABLE_3D
	IModel *pModel = m_pListModelMgr->CreateFromFile( pFileName, this );
	if ( pModel != NULL )
	{
		return pModel;
	}
#endif // ENABLE_3D

	static NullModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IModel *CRender::CreateModelFromMemory( const Uint8 *pData, Uint32 Size )
{
#if ENABLE_3D
	IModel *pModel = m_pListModelMgr->CreateFromMemory( pData, Size, this );
	if ( pModel != NULL )
	{
		return pModel;
	}
#endif // ENABLE_3D

	static NullModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFont *CRender::CreateFont( const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold )
{
	CFont *pData = new CFont( m_pListPrimitive2DMgr );
	if ( !pData->Create( pFontFace, FontSize, IsItalic, IsBold ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetScissoring( RECT *pRect )
{
	CGraphicCard *pGraphicCard = GetDevicePointer()->GetGraphicCardPointer();
	CCore *pCore = pGraphicCard->GetCorePointer();

	//------------------------------------------------
	// 仮想画面から実画面へ
	//------------------------------------------------
	if ( pRect != NULL )
	{
		pRect->left   = toI(pCore->Virtual2RealX( toF(pRect->left)   ));
		pRect->right  = toI(pCore->Virtual2RealX( toF(pRect->right)  ));
		pRect->top    = toI(pCore->Virtual2RealY( toF(pRect->top)    ));
		pRect->bottom = toI(pCore->Virtual2RealY( toF(pRect->bottom) ));
	}

	m_pListPrimitive2DMgr->SetScissoring( pRect );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISurface *CRender::CreateDepthStencilSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	ISurface *pSurf = m_pSurfaceMgr->CreateDepthStencil( Width, Height, Format );
	if ( pSurf == NULL )
	{
		static NullSurface Dummy;
		return &Dummy;
	}
	return pSurf;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISurface *CRender::CreateRenderTargetSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format, ISurface *pCopyTarget )
{
	ISurface *pSurf = m_pSurfaceMgr->CreateRenderTarget( Width, Height, Format, dynamic_cast<CSurface*>(pCopyTarget) );
	if ( pSurf == NULL )
	{
		static NullSurface Dummy;
		return &Dummy;
	}
	return pSurf;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTextureConfig &CRender::GetTextureConfig( void )
{
	return m_TextureConfig;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetTextureConfig( CTextureConfig &Conf )
{
	m_TextureConfig = Conf;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTexture( Uint32 Width, Uint32 Height )
{
	ITexture *pTex = m_pTextureMgr->Create( Width, Height, m_TextureConfig.GetFormat() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureFromFile( const wchar_t *pFileName )
{
	ITexture *pTex = m_pTextureMgr->CreateFromFile( pFileName, m_TextureConfig.GetFormat(), m_TextureConfig.GetColorKey() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureFromMemory( void *pData, Uint32 Size )
{
	ITexture *pTex = m_pTextureMgr->CreateFromMemory( pData, Size, m_TextureConfig.GetFormat(), m_TextureConfig.GetColorKey() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureRenderTarget( Uint32 Width, Uint32 Height )
{
	ITexture *pTex = m_pTextureMgr->CreateRenderTarget( Width, Height, m_TextureConfig.GetFormat() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )
{
	ITexture *pTex = m_pTextureMgr->CreateTextureFromFileForNormalMap( pFileName, fHeight );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )
{
	ITexture *pTex = m_pTextureMgr->CreateTextureFromMemoryForNormalMap( pData, Size, fHeight );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDrawType( eDrawType Type )
{
	if ( m_RenderState[m_RenderStatePos].DrawType == Type )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].DrawType = Type;

	switch ( Type )
	{
	case DRAW_TYPE_NORMAL:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO );
		break;

	case DRAW_TYPE_BLEND:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		break;

	case DRAW_TYPE_ADD:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_ADD_NOALPHA:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_SUB:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_REVSUBTRACT );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_SUB_NOALPHA:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_REVSUBTRACT );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_MULTIPLE:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ZERO );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR );
		break;

	case DRAW_TYPE_SCREEN:
		GetDevicePointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		GetDevicePointer()->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		GetDevicePointer()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		GetDevicePointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR );
		GetDevicePointer()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		GetDevicePointer()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT );
		GetDevicePointer()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_TEXTURE );
		GetDevicePointer()->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_MODULATE );
		GetDevicePointer()->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_CURRENT | D3DTA_ALPHAREPLICATE );
		GetDevicePointer()->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetCullType( eCullType Type )
{
	if ( m_RenderState[m_RenderStatePos].CullType == Type )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].CullType = Type;

	switch ( Type )
	{
	case CULL_FRONT:
		GetDevicePointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		break;
	case CULL_BACK:
		GetDevicePointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		break;
	case CULL_NONE:
		GetDevicePointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )
{
	Bool IsMin, IsMag;
	Uint32 Max;

	if ( m_RenderState[m_RenderStatePos].FilterType[Stage] == Type )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].FilterType[Stage] = Type;

	switch ( Type )
	{
	case TEXTURE_FILTER_DISABLE:
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		m_fOffset[Stage] = 0.0f;
		break;
	case TEXTURE_FILTER_BILINEAR:
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		m_fOffset[Stage] = 0.5f;
		break;
	case TEXTURE_FILTER_ANISOTROPY_LOW:
		GetDevicePointer()->GetGraphicCardPointer()->GetAnisotropyFilterSupport( IsMin, IsMag, Max );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MAXANISOTROPY, (Max + 3) / 4 );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MAGFILTER, IsMag ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MINFILTER, IsMin ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		m_fOffset[Stage] = 0.5f;
		break;
	case TEXTURE_FILTER_ANISOTROPY_HIGH:
		GetDevicePointer()->GetGraphicCardPointer()->GetAnisotropyFilterSupport( IsMin, IsMag, Max );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MAXANISOTROPY, Max );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MAGFILTER, IsMag ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MINFILTER, IsMin ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		m_fOffset[Stage] = 0.5f;
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )
{
	if ( m_RenderState[m_RenderStatePos].AddressType[Stage] == Type )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].AddressType[Stage] = Type;

	switch ( Type )
	{
	case TEXTURE_ADDRESS_REPEAT:
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
		break;
	case TEXTURE_ADDRESS_CLAMP:
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		GetDevicePointer()->SetSamplerState( Stage, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )
{
	if ( m_RenderState[m_RenderStatePos].OperationType[Stage] == Type )
	{
		return;
	}

	D3DTEXTUREOP TexOp[] = {
		D3DTOP_DISABLE,
		D3DTOP_MODULATE,
		D3DTOP_ADD,
		D3DTOP_SUBTRACT,
	};

	m_RenderState[m_RenderStatePos].OperationType[Stage] = Type;

	GetDevicePointer()->SetTextureStageState( Stage, D3DTSS_COLOROP, TexOp[Type] );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetFogColor( CColor Color )
{
	Color.a = 0x00;
	if ( m_RenderState[m_RenderStatePos].FogColor == Color )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].FogColor = Color;

	GetDevicePointer()->SetRenderState( D3DRS_FOGCOLOR, (Uint32)Color );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDepthTestEnable( Bool Flag )
{
	if ( m_RenderState[m_RenderStatePos].IsDepthTestEnable == Flag )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].IsDepthTestEnable = Flag;

	GetDevicePointer()->SetRenderState( D3DRS_ZENABLE, Flag ? D3DZB_TRUE : D3DZB_FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDepthWriteEnable( Bool Flag )
{
	if ( m_RenderState[m_RenderStatePos].IsDepthWriteEnable == Flag )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].IsDepthWriteEnable = Flag;

	GetDevicePointer()->SetRenderState( D3DRS_ZWRITEENABLE, Flag ? TRUE : FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetAlphaTestEnable( Bool Flag )
{
	if ( m_RenderState[m_RenderStatePos].IsAlphaTestEnable == Flag )
	{
		return;
	}

	m_RenderState[m_RenderStatePos].IsAlphaTestEnable = Flag;

	GetDevicePointer()->SetRenderState( D3DRS_ALPHATESTENABLE, Flag ? TRUE : FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetTexture( Uint32 Stage, ITexture *pTex )
{
	if ( m_RenderState[m_RenderStatePos].pTextureTbl[Stage] == pTex )
	{
		return true;
	}

	IDirect3DTexture9 *pTexture = NULL;
	HRESULT hr = E_FAIL;

	m_RenderState[m_RenderStatePos].pTextureTbl[Stage] = pTex;

	if ( pTex != NULL )
	{
		// テクスチャ取得
		(dynamic_cast<CTexture*>(pTex))->GetTexture( &pTexture );
		// デバイスに設定
		hr = GetDevicePointer()->SetTexture( Stage, pTexture );
		// テクスチャ解放
		SAFE_RELEASE( pTexture );
	}
	else
	{
		// デバイスに設定
		hr = GetDevicePointer()->SetTexture( Stage, NULL );
	}

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::StatePush( void )
{
	if ( m_RenderStatePos == STATE_STACK_MAX - 1 )
	{
		return false;
	}

	m_RenderStatePos++;

	m_RenderState[m_RenderStatePos] = m_RenderState[m_RenderStatePos-1];

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::StatePop( void )
{
	if ( m_RenderStatePos == 0 )
	{
		return false;
	}

	Uint32 Pos = m_RenderStatePos - 1;

	SetDrawType( m_RenderState[Pos].DrawType );
	SetCullType( m_RenderState[Pos].CullType );
	SetFogColor( m_RenderState[Pos].FogColor );
	SetDepthTestEnable( m_RenderState[Pos].IsDepthTestEnable );
	SetDepthWriteEnable( m_RenderState[Pos].IsDepthWriteEnable );
	SetAlphaTestEnable( m_RenderState[Pos].IsAlphaTestEnable );

	for ( Uint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTextureFilterType( i, m_RenderState[Pos].FilterType[i] );
		SetTextureAddressType( i, m_RenderState[Pos].AddressType[i] );
		SetTextureOperationType( i, m_RenderState[Pos].OperationType[i] );
		SetTexture( i, m_RenderState[Pos].pTextureTbl[i] );
	}

	m_RenderStatePos--;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::StateInit( void )
{
	SetDrawType( DRAW_TYPE_NORMAL );
	SetCullType( CULL_FRONT );
	SetFogColor( 0x00000000 );
	SetDepthTestEnable( false );
	SetDepthWriteEnable( false );
	SetAlphaTestEnable( true );

	for ( Uint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTextureFilterType( i, TEXTURE_FILTER_DISABLE );
		SetTextureAddressType( i, TEXTURE_ADDRESS_REPEAT );
		SetTextureOperationType( i, (i == 0) ? TEXTURE_OP_MUL : TEXTURE_OP_NONE );
		SetTexture( i, NULL );
	}
}


