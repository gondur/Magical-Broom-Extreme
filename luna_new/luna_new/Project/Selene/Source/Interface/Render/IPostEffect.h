

#ifndef ___SELENE__IPOSTEFFECT___
#define ___SELENE__IPOSTEFFECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief ポストエフェクトインターフェイス
		@author 葉迩倭
	*/
	class IPostEffect
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																																			= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																																			= 0;

		/**
			@brief テクスチャを使った矩形レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			単純な矩形をテクスチャ対応でレンダリングします。
		*/
		virtual void SingleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																	= 0;

		/**
			@brief マルチテクスチャを使った矩形レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param SrcTbl		[in] テクスチャUV矩形
			@param TypeTbl		[in] ステージ毎の演算タイプ
			@param pTexTbl		[in] テクスチャ
			@param StageCount	[in] 利用するステージ数

			単純な矩形をマルチテクスチャ対応でレンダリングします。<BR>
			2D描画におけるマルチテクスチャ用途は主にポストエフェクトなので<BR>
			その部分に特化した機能として実装してあります。
		*/
		virtual void MultipleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> SrcTbl[], eTextureOperationType TypeTbl[], ITexture *pTexTbl[], Uint32 StageCount )		= 0;

		/**
			@brief グレイスケール化レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ
			@param fRate		[in] 適用度(0.0～1.0)

			カラー画像をグレースケール化します。<BR>
			fRate引数によって、段階的にグレースケール化する事が可能です。<BR>
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void Grayscale( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex, Float fRate )																= 0;

		/**
			@brief ユニバーサルトランジションレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param fRate		[in] 合成レート(0.0～1.0)
			@param SrcBase		[in] ベーステクスチャUV矩形
			@param pBaseTex		[in] ベーステクスチャインターフェイス
			@param SrcRule		[in] ルールテクスチャUV矩形
			@param pRuleTex		[in] ルールテクスチャインターフェイス

			グレースケールのルール画像を用いてユニバーサルトランジションを行います。<BR>
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void UniversalTransition( CRect2D<Sint32> &Dst, Float fRate, CRect2D<Sint32> &SrcBase, ITexture *pBaseTex, CRect2D<Sint32> &SrcRule, ITexture *pRuleTex )			= 0;

		/**
			@brief 画像をぼかしてレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			3x3ボックスフィルタで画像をぼかします。
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void Blur9Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief 画像をぼかしてレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			4x4ボックスフィルタで画像をぼかします。
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void Blur16Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief 画像をぼかしてレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			8x8ボックスフィルタで画像をぼかします。<BR>
			ピクセルシェーダー2.0をサポートしないビデオカードの場合<BR>
			Blur16Box()に置き換えられます。
		*/
		virtual void Blur64Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;
	};
}

#endif // ___SELENE__IPOSTEFFECT___

