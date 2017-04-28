


#ifndef ___SELENE__CPOSTEFFECT___
#define ___SELENE__CPOSTEFFECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObject.h"
#include "Interface/Render/IRender.h"
#include "Interface/Render/IPostEffect.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CVertexStream;
	class CVertexBuffer;
	class CShader;

	/**
		@brief ポストエフェクトインターフェイス
		@author 葉迩倭
	*/
	class CPostEffect : public CBaseObject, public IPostEffect
	{
	private:
		CRender				*m_pRender;								///< 関連レンダラー
		CShader				*m_pShader;								///< ポストエフェクト用シェーダー
		CVertexBuffer		*m_pVertexBuffer_PostEffect;			///< マルチテクスチャ用頂点バッファ
		CVertexStream		*m_pVertexStream_PostEffect;			///< マルチテクスチャ用頂点定義

		FX_HANDLE			m_hTech_Grayscale;
		FX_HANDLE			m_hTech_UniversalTransition;
		FX_HANDLE			m_hTech_Blur9;
		FX_HANDLE			m_hTech_Blur16;
		FX_HANDLE			m_hTech_Blur64;
		FX_HANDLE			m_hTech_DepthOfField1;
		FX_HANDLE			m_hTech_DepthOfField2;
		FX_HANDLE			m_hTech_HDRDownSample;
		FX_HANDLE			m_hTech_Gaussian;
		FX_HANDLE			m_hTech_Edge;
		FX_HANDLE			m_hOFFSET;
		FX_HANDLE			m_hBLEND_RATE;
		FX_HANDLE			m_hTEXTURE0;
		FX_HANDLE			m_hTEXTURE1;
		FX_HANDLE			m_hTEXTURE2;
		FX_HANDLE			m_hTEXTURE3;

	private:
		Float ToPixelX( Sint32 Val );
		Float ToPixelY( Sint32 Val );
		Float ComputeGaussianValue( Float fRate, Float fMean, Float fStdDev );

	public:
		CPostEffect( CRender *pRender );
		virtual ~CPostEffect();

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void SingleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
		virtual void MultipleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> SrcTbl[], eTextureOperationType TypeTbl[], ITexture *pTexTbl[], Uint32 StageCount );
		virtual void Grayscale( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex, Float fRate );
		virtual void UniversalTransition( CRect2D<Sint32> &Dst, Float fRate, CRect2D<Sint32> &SrcBase, ITexture *pBaseTex, CRect2D<Sint32> &SrcRule, ITexture *pRuleTex );
		virtual void Blur9Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
		virtual void Blur16Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
		virtual void Blur64Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );

		virtual void DepthOfField( CRect2D<Sint32> &Dst, ITexture *pTexBlur, ITexture *pTexBase );
		virtual void DepthOfField( CRect2D<Sint32> &Dst, ITexture *pTexBlur, ITexture *pTexBase, ITexture *pTexBlend );
		virtual void HDR_DownSample( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
		virtual void GaussianH( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
		virtual void GaussianV( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
		virtual void DrawEdge( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex );
	};
}

#endif // ___SELENE__CPOSTEFFECT___

