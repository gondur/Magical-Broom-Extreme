

#ifndef ___SELENE__ISURFACE___
#define ___SELENE__ISURFACE___


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
		@brief マテリアルインターフェイス
		@author 葉迩倭

		サーフェイスフェイス操作するためのインターフェイスです。<BR>
		IRenderインターフェイスから取得できます。
	*/
	class ISurface
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
		virtual Uint32 Release( void )											= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )											= 0;

		/**
			@brief バックバッファにコピー
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗

			サーフェイスフェイスバックバッファにコピーします。<BR>
			ただし深度ステンシルマテリアルやフォーマット変換にハードウェアが<BR>
			対応していないフォーマットのマテリアルでは失敗します。
		*/
		virtual Bool CopyToBackBuffer( void )									= 0;

		/**
			@brief マテリアルのコピー
			@author 葉迩倭
			@param pDstRect		[in] 転送先マテリアルの矩形
			@param pSrc			[in] 転送元マテリアル
			@param pSrcRect		[in] 転送元マテリアルの矩形
			@retval true	成功
			@retval false	失敗

			マテリアル同士の拡大縮小コピーを行います。<BR>
			マテリアル間でフォーマットが異なる場合は<BR>
			ハードウェアのフォーマット変換のサポートがないと<BR>
			この関数は失敗します。<BR>
			またこのコピー処理にはいくつかの制限が存在します。<BR>
			・通常マテリアルから通常マテリアルの拡大縮小コピーはできません。<BR>
			・バックバッファから通常マテリアルへのコピーはできません。
		*/
		virtual Bool Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )		= 0;
	};
}

#endif // ___SELENE__ISURFACE___


