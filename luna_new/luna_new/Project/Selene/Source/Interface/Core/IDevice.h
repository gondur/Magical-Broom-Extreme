

#ifndef ___SELENE__IDEVICE___
#define ___SELENE__IDEVICE___


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
		@brief デバイス管理インターフェイス
		@author 葉迩倭
	*/
	class IDevice
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
		virtual Uint32 Release( void )												= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)												= 0;

		/**
			@brief レンダリングターゲットクリア
			@author 葉迩倭
			@param Color	[in] クリアに使う色
			@retval false	失敗
			@retval true	成功

			設定されたレンダリングターゲットを指定された色でクリアーします。
		*/
		virtual Bool Clear( CColor Color = 0x00000000 )								= 0;

		/**
			@brief 深度バッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定された深度バッファをクリアします。<BR>
			深度バッファが存在しない場合失敗します。
		*/
		virtual Bool ClearDepth( void )												= 0;

		/**
			@brief ステンシルバッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定されたステンシルバッファをクリアします。<BR>
			ステンシルバッファが存在しない場合失敗します。
		*/
		virtual Bool ClearStencil( void )											= 0;

		/**
			@brief 深度ステンシルバッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定された深度ステンシルバッファをクリアします。<BR>
			深度ステンシルバッファが存在しない場合失敗します。
		*/
		virtual Bool ClearDepthStencil( void )										= 0;

		/**
			@brief 擬似コンソール画面に文字列を描画
			@author 葉迩倭
			@param pStr	[in] 書式付文字列(printfと同じ書式)

			コンソールのprintf()と似た文字列描画処理です。<BR>
			デバッグ用に画面に文字を描画しておきたい場合等に利用してください。
		*/
		virtual void Printf( const wchar_t *pStr, ... )								= 0;

		/**
			@brief 擬似コンソール画面をクリア
			@author 葉迩倭

			擬似コンソール画面をクリアします。
		*/
		virtual void Cls( void )													= 0;

		/**
			@brief 描画領域シザリング
			@author 葉迩倭
			@param IsEnable		[in] シザリングを有効にするか否か
			@param Rect			[in] 描画領域

			指定した描画領域内にしかレンダリングされないようになります。<BR>
			ビューポートには影響を与えません。
		*/
		virtual void SetScissor( Bool IsEnable, CRect2D<Sint32> Rect )			= 0;

		/**
			@brief IRenderインターフェイス取得
			@author 葉迩倭
			@return IRenderインターフェイス

			IRenderインターフェイスを取得します。<BR>
			画面へのレンダリング処理の全てがこのインターフェイスを<BR>
			介して行われるようになっています。<BR>
			このインターフェイスは1つのIDeviceに対して1つしか存在しません。<BR>
			また不要になったIRenderインターフェイスは必ずRelease()して下さい。
		*/
		virtual IRender *CreateRender( void )										= 0;
	};
}


#endif // ___SELENE__IDEVICE___

