

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Core/CCore.h"
#include "Core/CGraphicCard.h"
#include "Render/CPostEffect.h"
#include "Render/CVertexBuffer.h"
#include "Render/CVertexStream.h"
#include "Render/CShader.h"
#include "Render/CRender.h"
#include "Surface/CTexture.h"

Float fGaussMean		= 0.0f;
Float fGaussStdDev		= 0.8f;


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// STRUCT
//-----------------------------------------------------------------------------------
struct SVertexPostEffect
{
	CVector4D vPos;
	CColor Color;
	CVector2D vTex[8];
};


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
// Multi Texture用
static const D3DVERTEXELEMENT9 g_VertexElementPostEffect[] = {
    { 0,  0, D3DDECLTYPE_FLOAT4,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT,	0 },
	{ 0, 16, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
	{ 0, 20, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
	{ 0, 28, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	1 },
	{ 0, 36, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	2 },
	{ 0, 44, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	3 },
	{ 0, 52, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	4 },
	{ 0, 60, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	5 },
	{ 0, 68, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	6 },
	{ 0, 76, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	7 },
	D3DDECL_END(),
};

//-----------------------------------------------------------------------------------
// SHADER
//-----------------------------------------------------------------------------------
static const Uint8 EffectShader[] = {
#include "FxFile/PostEffect.inc"
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPostEffect::CPostEffect( CRender *pRender )
{
	m_pRender = pRender;
	m_pRender->AddRef();

	//------------------------------------------------------------------
	// エフェクト用シェーダー
	//------------------------------------------------------------------
	m_pShader = pRender->CreateShaderFromMemory( EffectShader, sizeof(EffectShader) );

	m_hTech_Grayscale			= m_pShader->GetTechnique( L"TECH_Grayscale" );
	m_hTech_UniversalTransition	= m_pShader->GetTechnique( L"TECH_UniversalTransition" );
	m_hTech_Blur9				= m_pShader->GetTechnique( L"TECH_Blur9" );
	m_hTech_Blur16				= m_pShader->GetTechnique( L"TECH_Blur16" );
	m_hTech_Blur64				= m_pShader->GetTechnique( L"TECH_Blur64" );
	m_hTech_DepthOfField1		= m_pShader->GetTechnique( L"TECH_DOF1" );
	m_hTech_DepthOfField2		= m_pShader->GetTechnique( L"TECH_DOF2" );
	m_hTech_HDRDownSample		= m_pShader->GetTechnique( L"TECH_HDR" );
	m_hTech_Gaussian			= m_pShader->GetTechnique( L"TECH_GAUSSIAN" );
	m_hTech_Edge				= m_pShader->GetTechnique( L"TECH_EDGE" );

	m_hBLEND_RATE				= m_pShader->GetParameterBySemantic( L"BLEND_RATE" );
	m_hOFFSET					= m_pShader->GetParameterBySemantic( L"OFFSET" );
	m_hTEXTURE0					= m_pShader->GetParameterBySemantic( L"TEXTURE0" );
	m_hTEXTURE1					= m_pShader->GetParameterBySemantic( L"TEXTURE1" );
	m_hTEXTURE2					= m_pShader->GetParameterBySemantic( L"TEXTURE2" );
	m_hTEXTURE3					= m_pShader->GetParameterBySemantic( L"TEXTURE3" );

	//------------------------------------------------------------------
	// マルチテクスチャ用
	//------------------------------------------------------------------
	m_pVertexStream_PostEffect = pRender->CreateVertexStreamDirect();
	m_pVertexStream_PostEffect->Create( g_VertexElementPostEffect );
	m_pVertexBuffer_PostEffect = pRender->CreateVertexBuffer( 4, sizeof(SVertexPostEffect), true );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPostEffect::~CPostEffect()
{
	// 所有オブジェクトの解体
	SAFE_RELEASE( m_pVertexBuffer_PostEffect );
	SAFE_RELEASE( m_pVertexStream_PostEffect );

	SAFE_RELEASE( m_pVertexBuffer_PostEffect );
	SAFE_RELEASE( m_pVertexStream_PostEffect );

	SAFE_RELEASE( m_pShader );
	SAFE_RELEASE( m_pRender );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::SingleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		Float fOffsetX = Src.w == Dst.w ? 0.0f : m_pRender->GetTextureOffset( 0 );
		Float fOffsetY = Src.h == Dst.h ? 0.0f : m_pRender->GetTextureOffset( 0 );

		Vtx[0].vTex[0] = CVector2D( toF(Src.x      )+fOffsetX, toF(Src.y      )+fOffsetY );
		Vtx[1].vTex[0] = CVector2D( toF(Src.x+Src.w)-fOffsetX, toF(Src.y      )+fOffsetY );
		Vtx[2].vTex[0] = CVector2D( toF(Src.x      )+fOffsetX, toF(Src.y+Src.h)-fOffsetY );
		Vtx[3].vTex[0] = CVector2D( toF(Src.x+Src.w)-fOffsetX, toF(Src.y+Src.h)-fOffsetY );

		CTexture *pTexture = dynamic_cast<CTexture*>(pTex);
		for ( Uint32 i = 0; i < 4; i++ )
		{
			Vtx[i].vTex[0].x = pTexture->PixelToTexelU( Vtx[i].vTex[0].x );
			Vtx[i].vTex[0].y = pTexture->PixelToTexelV( Vtx[i].vTex[0].y );
		}
	}

	// テクスチャ
	m_pRender->SetTextureOperationType( 0, TEXTURE_OP_MUL );
	m_pRender->SetTextureOperationType( 1, TEXTURE_OP_NONE );
	m_pRender->SetTexture( 0, pTex );
	m_pRender->SetTexture( 1, NULL );

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// レンダリング
	m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

	// ステート復帰
	m_pRender->StatePop();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::MultipleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> SrcTbl[], eTextureOperationType TypeTbl[], ITexture *pTexTbl[], Uint32 StageCount )
{
	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	for ( Uint32 i = 0; i < StageCount; i++ )
	{
		Float fOffsetX = SrcTbl[i].w == Dst.w ? 0.0f : m_pRender->GetTextureOffset( i );
		Float fOffsetY = SrcTbl[i].h == Dst.h ? 0.0f : m_pRender->GetTextureOffset( i );

		m_pRender->SetTextureOperationType( i, TypeTbl[i] );
		m_pRender->SetTexture( i, pTexTbl[i] );

		CTexture *pTex = m_pRender->GetTexture( i );
		if ( pTex != NULL )
		{
			Vtx[0].vTex[i] = CVector2D( toF(SrcTbl[i].x            )+fOffsetX, toF(SrcTbl[i].y            )+fOffsetY );
			Vtx[1].vTex[i] = CVector2D( toF(SrcTbl[i].x+SrcTbl[i].w)-fOffsetX, toF(SrcTbl[i].y            )+fOffsetY );
			Vtx[2].vTex[i] = CVector2D( toF(SrcTbl[i].x            )+fOffsetX, toF(SrcTbl[i].y+SrcTbl[i].h)-fOffsetY );
			Vtx[3].vTex[i] = CVector2D( toF(SrcTbl[i].x+SrcTbl[i].w)-fOffsetX, toF(SrcTbl[i].y+SrcTbl[i].h)-fOffsetY );

			for ( Uint32 j = 0; j < 4; j++ )
			{
				Vtx[j].vTex[i].x = pTex->PixelToTexelU( Vtx[j].vTex[i].x );
				Vtx[j].vTex[i].y = pTex->PixelToTexelV( Vtx[j].vTex[i].y );
			}
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// レンダリング
	m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Grayscale( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex, Float fRate )
{
	// レート
	if ( fRate > 1.0f ) fRate = 1.0f;
	if ( fRate < 0.0f ) fRate = 0.0f;

	// ピクセルシェーダー1.0サポート？
	if ( !m_pRender->GetDevicePointer()->IsSupportedPS( 1, 0 ) )
	{
		// ただの描画に置き換え
		SingleTexture( Dst, Color, Src, pTex );
		return;
	}

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		Float fOffsetX = Src.w == Dst.w ? 0.0f : m_pRender->GetTextureOffset( 0 );
		Float fOffsetY = Src.h == Dst.h ? 0.0f : m_pRender->GetTextureOffset( 0 );

		Vtx[0].vTex[0] = CVector2D( toF(Src.x      )+fOffsetX, toF(Src.y      )+fOffsetY );
		Vtx[1].vTex[0] = CVector2D( toF(Src.x+Src.w)-fOffsetX, toF(Src.y      )+fOffsetY );
		Vtx[2].vTex[0] = CVector2D( toF(Src.x      )+fOffsetX, toF(Src.y+Src.h)-fOffsetY );
		Vtx[3].vTex[0] = CVector2D( toF(Src.x+Src.w)-fOffsetX, toF(Src.y+Src.h)-fOffsetY );

		CTexture *pTexture = dynamic_cast<CTexture*>(pTex);
		for ( Uint32 i = 0; i < 4; i++ )
		{
			Vtx[i].vTex[0].x = pTexture->PixelToTexelU( Vtx[i].vTex[0].x );
			Vtx[i].vTex[0].y = pTexture->PixelToTexelV( Vtx[i].vTex[0].y );
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクスチャ
	m_pShader->SetFloat( m_hBLEND_RATE, fRate );
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// テクニック
	m_pShader->SetTechnique( m_hTech_Grayscale );

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::UniversalTransition( CRect2D<Sint32> &Dst, Float fRate, CRect2D<Sint32> &SrcBase, ITexture *pBaseTex, CRect2D<Sint32> &SrcRule, ITexture *pRuleTex )
{
	// レート
	if ( fRate > 1.0f ) fRate = 1.0f;
	if ( fRate < 0.0f ) fRate = 0.0f;

	// ピクセルシェーダー1.0サポート？
	if ( !m_pRender->GetDevicePointer()->IsSupportedPS( 1, 0 ) )
	{
		// ただの描画に置き換え
		CColor Color( 255, 255, 255, (Uint8)(fRate * 255.0f) );
		SingleTexture( Dst, Color, SrcBase, pBaseTex );
		return;
	}

	// ステート保存
	m_pRender->StatePush();

	// フィルタ
	m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
	m_pRender->SetTextureFilterType( 1, TEXTURE_FILTER_BILINEAR );

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), 0xFFFFFFFF },
	};

	// テクスチャUV更新
	CTexture *pTex[] = {
		dynamic_cast<CTexture*>(pBaseTex),
		dynamic_cast<CTexture*>(pRuleTex),
	};
	CRect2D<Sint32> *pSrc[] = {
		&SrcBase,
		&SrcRule,
	};

	for ( Uint32 i = 0; i < 2; i++ )
	{
		if ( pTex[i] == NULL ) return;

		Float fOffsetX = pSrc[i]->w == Dst.w ? 0.0f : m_pRender->GetTextureOffset( i );
		Float fOffsetY = pSrc[i]->h == Dst.h ? 0.0f : m_pRender->GetTextureOffset( i );

		Vtx[0].vTex[i] = CVector2D( toF(pSrc[i]->x           )+fOffsetX, toF(pSrc[i]->y           )+fOffsetY );
		Vtx[1].vTex[i] = CVector2D( toF(pSrc[i]->x+pSrc[i]->w)-fOffsetX, toF(pSrc[i]->y           )+fOffsetY );
		Vtx[2].vTex[i] = CVector2D( toF(pSrc[i]->x           )+fOffsetX, toF(pSrc[i]->y+pSrc[i]->h)-fOffsetY );
		Vtx[3].vTex[i] = CVector2D( toF(pSrc[i]->x+pSrc[i]->w)-fOffsetX, toF(pSrc[i]->y+pSrc[i]->h)-fOffsetY );
		for ( Uint32 j = 0; j < 4; j++ )
		{
			Vtx[j].vTex[i].x = pTex[i]->PixelToTexelU( Vtx[j].vTex[i].x );
			Vtx[j].vTex[i].y = pTex[i]->PixelToTexelV( Vtx[j].vTex[i].y );
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_UniversalTransition );

	// テクスチャ
	m_pShader->SetFloat( m_hBLEND_RATE, (fRate * 2.0f) - 1.0f );
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pBaseTex) );
	m_pShader->SetTexture( m_hTEXTURE1, dynamic_cast<CTexture*>(pRuleTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Blur9Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ピクセルシェーダー1.0サポート？
	if ( !m_pRender->GetDevicePointer()->IsSupportedPS( 1, 0 ) )
	{
		// ただの描画に置き換え
		SingleTexture( Dst, Color, Src, pTex );
		return;
	}

	CTexture *pTexture = dynamic_cast<CTexture*>(pTex);

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		CVector2D uv[] = {
			CVector2D( toF(Src.x         ), toF(Src.y         ) ),
			CVector2D( toF(Src.x + Src.w), toF(Src.y         ) ),
			CVector2D( toF(Src.x         ), toF(Src.y + Src.h) ),
			CVector2D( toF(Src.x + Src.w), toF(Src.y + Src.h) ),
		};

		Float x_tbl[] = { -1.0f,  0.0f, -1.0f, 0.0f };
		Float y_tbl[] = { -1.0f, -1.0f,  0.0f, 0.0f };

		for ( Uint32 i = 0; i < 4; i++ )
		{
			for ( Uint32 j = 0; j < 4; j++ )
			{
				Vtx[i].vTex[j].x = pTexture->PixelToTexelU( uv[i].x + x_tbl[j] + 0.5f );
				Vtx[i].vTex[j].y = pTexture->PixelToTexelV( uv[i].y + y_tbl[j] + 0.5f );
			}
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_Blur9 );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Blur16Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ピクセルシェーダー1.0サポート？
	if ( !m_pRender->GetDevicePointer()->IsSupportedPS( 1, 0 ) )
	{
		// ただの描画に置き換え
		SingleTexture( Dst, Color, Src, pTex );
		return;
	}

	CTexture *pTexture = dynamic_cast<CTexture*>(pTex);

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		CVector2D uv[] = {
			CVector2D( toF(Src.x         ), toF(Src.y         ) ),
			CVector2D( toF(Src.x + Src.w), toF(Src.y         ) ),
			CVector2D( toF(Src.x         ), toF(Src.y + Src.h) ),
			CVector2D( toF(Src.x + Src.w), toF(Src.y + Src.h) ),
		};

		Float x_tbl[] = { -1.0f, +1.0f, -1.0f, +1.0f };
		Float y_tbl[] = { -1.0f, -1.0f, +1.0f, +1.0f };

		for ( Uint32 i = 0; i < 4; i++ )
		{
			for ( Uint32 j = 0; j < 4; j++ )
			{
				Vtx[i].vTex[j].x = pTexture->PixelToTexelU( uv[i].x + x_tbl[j] + 0.5f );
				Vtx[i].vTex[j].y = pTexture->PixelToTexelV( uv[i].y + y_tbl[j] + 0.5f );
			}
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_Blur16 );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Blur64Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ピクセルシェーダー2.0サポート？
	if ( !m_pRender->GetDevicePointer()->IsSupportedPS( 2, 0 ) )
	{
		// ただの描画に置き換え
		Blur16Box( Dst, Color, Src, pTex );
		return;
	}

	CTexture *pTexture = dynamic_cast<CTexture*>(pTex);

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		CVector2D uv[] = {
			CVector2D( toF(Src.x         ), toF(Src.y         ) ),
			CVector2D( toF(Src.x + Src.w), toF(Src.y         ) ),
			CVector2D( toF(Src.x         ), toF(Src.y + Src.h) ),
			CVector2D( toF(Src.x + Src.w), toF(Src.y + Src.h) ),
		};

		Float x_tbl[] = { +3.0f, +3.0f, +3.0f, +3.0f, +1.0f, +1.0f, +1.0f, +1.0f };
		Float y_tbl[] = { -3.0f, -1.0f, +1.0f, +3.0f, -3.0f, -1.0f, +1.0f, +3.0f };

		for ( Uint32 i = 0; i < 4; i++ )
		{
			for ( Uint32 j = 0; j < 8; j++ )
			{
				Vtx[i].vTex[j].x = pTexture->PixelToTexelU( uv[i].x + x_tbl[j] + 0.5f );
				Vtx[i].vTex[j].y = pTexture->PixelToTexelV( uv[i].y + y_tbl[j] + 0.5f );
			}
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_Blur64 );

	// テクスチャサイズ
	m_pShader->SetFloat( m_hBLEND_RATE, -4.0f / toF(pTexture->GetSize().x) );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::DepthOfField( CRect2D<Sint32> &Dst, ITexture *pTexBlur, ITexture *pTexBase )
{
	if ( pTexBase == NULL ) return;

	CTexture *pTextureBase = dynamic_cast<CTexture*>(pTexBase);
	CTexture *pTextureBlur = dynamic_cast<CTexture*>(pTexBlur);

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), 0xFFFFFFFF },
	};

	Vtx[0].vTex[0] = CVector2D( 0.0f, 0.0f );
	Vtx[1].vTex[0] = CVector2D( 1.0f, 0.0f );
	Vtx[2].vTex[0] = CVector2D( 0.0f, 1.0f );
	Vtx[3].vTex[0] = CVector2D( 1.0f, 1.0f );

	Float fOffX = 0.5f / toF(pTextureBlur->GetSize().x);
	Float fOffY = 0.5f / toF(pTextureBlur->GetSize().y);
	Vtx[0].vTex[1] = CVector2D( 0.0f-fOffX, 0.0f-fOffY );
	Vtx[1].vTex[1] = CVector2D( 1.0f-fOffX, 0.0f-fOffY );
	Vtx[2].vTex[1] = CVector2D( 0.0f-fOffX, 1.0f-fOffY );
	Vtx[3].vTex[1] = CVector2D( 1.0f-fOffX, 1.0f-fOffY );

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_DepthOfField1 );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, pTextureBase );
	m_pShader->SetTexture( m_hTEXTURE1, pTextureBlur );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::DepthOfField( CRect2D<Sint32> &Dst, ITexture *pTexBlur, ITexture *pTexBase, ITexture *pTexBlend )
{
	if ( pTexBase == NULL ) return;

	CTexture *pTextureBase = dynamic_cast<CTexture*>(pTexBase);
	CTexture *pTextureBlur = dynamic_cast<CTexture*>(pTexBlur);
	CTexture *pTextureBlend = dynamic_cast<CTexture*>(pTexBlend);

	Float fOffX, fOffY;

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), 0xFFFFFFFF },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), 0xFFFFFFFF },
	};

	Vtx[0].vTex[0] = CVector2D( 0.0f, 0.0f );
	Vtx[1].vTex[0] = CVector2D( 1.0f, 0.0f );
	Vtx[2].vTex[0] = CVector2D( 0.0f, 1.0f );
	Vtx[3].vTex[0] = CVector2D( 1.0f, 1.0f );

	fOffX = 0.5f / toF(pTextureBlur->GetSize().x);
	fOffY = 0.5f / toF(pTextureBlur->GetSize().y);
	Vtx[0].vTex[1] = CVector2D( 0.0f-fOffX, 0.0f-fOffY );
	Vtx[1].vTex[1] = CVector2D( 1.0f-fOffX, 0.0f-fOffY );
	Vtx[2].vTex[1] = CVector2D( 0.0f-fOffX, 1.0f-fOffY );
	Vtx[3].vTex[1] = CVector2D( 1.0f-fOffX, 1.0f-fOffY );

	fOffX = 0.5f / toF(pTextureBlend->GetSize().x);
	fOffY = 0.5f / toF(pTextureBlend->GetSize().y);
	Vtx[0].vTex[2] = CVector2D( 0.0f-fOffX, 0.0f-fOffY );
	Vtx[1].vTex[2] = CVector2D( 1.0f-fOffX, 0.0f-fOffY );
	Vtx[2].vTex[2] = CVector2D( 0.0f-fOffX, 1.0f-fOffY );
	Vtx[3].vTex[2] = CVector2D( 1.0f-fOffX, 1.0f-fOffY );

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_DepthOfField2 );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, pTextureBase );
	m_pShader->SetTexture( m_hTEXTURE1, pTextureBlur );
	m_pShader->SetTexture( m_hTEXTURE2, pTextureBlend );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::HDR_DownSample( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		Float fOffsetX = m_pRender->GetTextureOffset( 0 );
		Float fOffsetY = m_pRender->GetTextureOffset( 0 );

		Vtx[0].vTex[0] = CVector2D( toF(Src.x      )+fOffsetX, toF(Src.y      )+fOffsetY );
		Vtx[1].vTex[0] = CVector2D( toF(Src.x+Src.w)-fOffsetX, toF(Src.y      )+fOffsetY );
		Vtx[2].vTex[0] = CVector2D( toF(Src.x      )+fOffsetX, toF(Src.y+Src.h)-fOffsetY );
		Vtx[3].vTex[0] = CVector2D( toF(Src.x+Src.w)-fOffsetX, toF(Src.y+Src.h)-fOffsetY );

		CTexture *pTexture = dynamic_cast<CTexture*>(pTex);
		for ( Uint32 i = 0; i < 4; i++ )
		{
			Vtx[i].vTex[0].x = pTexture->PixelToTexelU( Vtx[i].vTex[0].x );
			Vtx[i].vTex[0].y = pTexture->PixelToTexelV( Vtx[i].vTex[0].y );
		}
	}

	static CVector4D vOffset[16];

	Sint32 Idx = 0;
    for ( Sint32 i = -2; i < 2; i++ )
    {
        for( Sint32 j = -2; j < 2; j++ )
        {
            vOffset[Idx].x = (static_cast<Float>(i) + 0.5f) * (1.0f / static_cast<Float>(pTex->GetSize().x)), 
            vOffset[Idx].y = (static_cast<Float>(j) + 0.5f) * (1.0f / static_cast<Float>(pTex->GetSize().y)),
			Idx++;
        }
    }

	m_pShader->SetVectorArray( m_hOFFSET, vOffset, 16 );

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_HDRDownSample );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::GaussianH( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		Vtx[0].vTex[0] = CVector2D( toF(Src.x      ), toF(Src.y      ) );
		Vtx[1].vTex[0] = CVector2D( toF(Src.x+Src.w), toF(Src.y      ) );
		Vtx[2].vTex[0] = CVector2D( toF(Src.x      ), toF(Src.y+Src.h) );
		Vtx[3].vTex[0] = CVector2D( toF(Src.x+Src.w), toF(Src.y+Src.h) );

		CTexture *pTexture = dynamic_cast<CTexture*>(pTex);
		for ( Uint32 i = 0; i < 4; i++ )
		{
			Vtx[i].vTex[0].x = pTexture->PixelToTexelU( Vtx[i].vTex[0].x );
			Vtx[i].vTex[0].y = pTexture->PixelToTexelV( Vtx[i].vTex[0].y );
		}
	}

	static CVector4D vOffset[16];
	Float fAll = 0.0f;
    for ( Sint32 i = 0; i < 16; i++ )
    {
        vOffset[i].x = (static_cast<Float>(i) - 7.5f) * (1.0f / static_cast<float>(pTex->GetSize().x));
        Float fRate = (static_cast<Float>(i) - 7.5f) / 16.0f;
		vOffset[i].z = ComputeGaussianValue( fRate, fGaussMean, fGaussStdDev );
		fAll += vOffset[i].z;
    }

	fAll = 1.0f / fAll;
    for ( Sint32 i = 0; i < 16; i++ )
    {
		vOffset[i].z *= fAll;
    }

	m_pShader->SetVectorArray( m_hOFFSET, vOffset, 16 );

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_Gaussian );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::GaussianV( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		Vtx[0].vTex[0] = CVector2D( toF(Src.x      ), toF(Src.y      ) );
		Vtx[1].vTex[0] = CVector2D( toF(Src.x+Src.w), toF(Src.y      ) );
		Vtx[2].vTex[0] = CVector2D( toF(Src.x      ), toF(Src.y+Src.h) );
		Vtx[3].vTex[0] = CVector2D( toF(Src.x+Src.w), toF(Src.y+Src.h) );

		CTexture *pTexture = dynamic_cast<CTexture*>(pTex);
		for ( Uint32 i = 0; i < 4; i++ )
		{
			Vtx[i].vTex[0].x = pTexture->PixelToTexelU( Vtx[i].vTex[0].x );
			Vtx[i].vTex[0].y = pTexture->PixelToTexelV( Vtx[i].vTex[0].y );
		}
	}

	static CVector4D vOffset[16];
	Float fAll = 0.0f;
    for ( Sint32 i = 0; i < 16; i++ )
    {
        vOffset[i].y = (static_cast<Float>(i) - 7.5f) * (1.0f / static_cast<float>(pTex->GetSize().y));
        Float fRate = (static_cast<Float>(i) - 7.5f) / 16.0f;
		vOffset[i].z = ComputeGaussianValue( fRate, fGaussMean, fGaussStdDev );
		fAll += vOffset[i].z;
    }

	fAll = 1.0f / fAll;
    for ( Sint32 i = 0; i < 16; i++ )
    {
		vOffset[i].z *= fAll;
    }

	m_pShader->SetVectorArray( m_hOFFSET, vOffset, 16 );

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_Gaussian );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::DrawEdge( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )
{
	if ( pTex == NULL ) return;

	// ステート保存
	m_pRender->StatePush();

	// 頂点更新
	SVertexPostEffect Vtx[4] = {
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
		{ CVector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h), 0.0f, 1.0f ), Color },
	};

	// テクスチャUV更新
	if ( pTex != NULL )
	{
		CVector2D vUV[] = {
			CVector2D( toF(Src.x      ), toF(Src.y      ) ),
			CVector2D( toF(Src.x+Src.w), toF(Src.y      ) ),
			CVector2D( toF(Src.x      ), toF(Src.y+Src.h) ),
			CVector2D( toF(Src.x+Src.w), toF(Src.y+Src.h) ),
		};

		Float u_tbl[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		Float v_tbl[] = { 0.0f, 1.0f, 1.0f, 0.0f };

		CTexture *pTexture = dynamic_cast<CTexture*>(pTex);
		for ( Uint32 i = 0; i < 4; i++ )
		{
			for ( Uint32 j = 0; j < 4; j++ )
			{
				Vtx[i].vTex[j].x = pTexture->PixelToTexelU( vUV[i].x + u_tbl[j] );
				Vtx[i].vTex[j].y = pTexture->PixelToTexelV( vUV[i].y + v_tbl[j] );
			}
		}
	}

	// 頂点データ
	m_pVertexBuffer_PostEffect->Flush();
	m_pVertexBuffer_PostEffect->Push( Vtx, 4 );
	m_pVertexBuffer_PostEffect->Update();

	// 頂点定義
	m_pVertexStream_PostEffect->SetDevice();

	// 頂点バッファ
	m_pVertexBuffer_PostEffect->SetDevice( 0 );

	// テクニック
	m_pShader->SetTechnique( m_hTech_Edge );

	// テクスチャ
	m_pShader->SetTexture( m_hTEXTURE0, dynamic_cast<CTexture*>(pTex) );
	m_pShader->SetTexture( m_hTEXTURE1, dynamic_cast<CTexture*>(pTex) );
	m_pShader->SetTexture( m_hTEXTURE2, dynamic_cast<CTexture*>(pTex) );
	m_pShader->SetTexture( m_hTEXTURE3, dynamic_cast<CTexture*>(pTex) );

	// シェーダーパラメーター更新
	m_pShader->UpdateParameter();

	// シェーダー
	if ( m_pShader->Begin( NULL ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();

		// シェーダー
		m_pShader->End();
	}

	// ステート復帰
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CPostEffect::ComputeGaussianValue( Float fRate, Float fMean, Float fStdDev )
{
    // The gaussian equation is defined as such:
    /*    
                                                     -(x - fMean)^2
                                                     -------------
                                    1.0               2*std_dev^2
        f(x,fMean,std_dev) = -------------------- * e^
                            sqrt(2*pi*std_dev^2)

    */

	Float fStdDev2 = fStdDev * fStdDev;
	Float fTemp1 = 1.0f / sqrtf( PI2 * fStdDev2 );
	Float fTemp2 = expf( (-((fRate - fMean) * (fRate - fMean))) / (2.0f * fStdDev2) );

	return fTemp1 * fTemp2;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CPostEffect::ToPixelX( Sint32 Val )
{
	CDevice			*pDevice		= m_pRender->GetDevicePointer();
	CGraphicCard	*pGraphicCard	= pDevice->GetGraphicCardPointer();
	CCore			*pCore			= pGraphicCard->GetCorePointer();
	
	return pCore->Virtual2RealX( toF(Val) ) - 0.5f;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CPostEffect::ToPixelY( Sint32 Val )
{
	CDevice			*pDevice		= m_pRender->GetDevicePointer();
	CGraphicCard	*pGraphicCard	= pDevice->GetGraphicCardPointer();
	CCore			*pCore			= pGraphicCard->GetCorePointer();
	
	return pCore->Virtual2RealY( toF(Val) ) - 0.5f;
}

