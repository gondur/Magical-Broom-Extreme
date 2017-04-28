

#ifndef ___SELENE__ITEXTURE___
#define ___SELENE__ITEXTURE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief テクスチャインターフェイス
		@author 葉迩倭

		テクスチャを操作するためのインターフェイスです。<BR>
		IRenderインターフェイスから取得できます。
	*/
	class ITexture
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																		= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )																		= 0;

		/**
			@brief 矩形コピー
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
		virtual Bool Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel = false )	= 0;

		/**
			@brief レンダリングターゲットをダウンロード
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターサーフェイス<BR>
			現在のレンダリングターゲットの内容をコピーします。
		*/
		virtual Bool DownloadRenderTarget( void )															= 0;

		/**
			@brief テクスチャ更新
			@author 葉迩倭

			バックアップ用システムメモリマテリアルの内容を<BR>
			VRAM上のマテリアルへ転送します。
		*/
		virtual void UpdateTexture( void )																	= 0;

		/**
			@brief 画像ファイルとして保存
			@author 葉迩倭
			@param pFileName	[in] テクスチャファイル名
			@retval false	失敗
			@retval true	成功

			テクスチャの内容をTGA画像ファイルとして保存します。
		*/
		virtual Bool SaveToTGA( const wchar_t *pFileName )													= 0;

		/**
			@brief 実テクスチャサイズ取得
			@author 葉迩倭
			@return テクスチャの実サイズ

			テクスチャのサイズを取得します。<BR>
			２の累乗でないテクスチャを作成した際に<BR>
			デバイスがそのサイズをさぽーとしていないときは<BR>
			内包できる大きさの２の累乗のサイズになっています。
		*/
		virtual CPoint2D<Uint32> GetSize( void )															= 0;
	};
}

#endif // ___SELENE__ITEXTURE___


