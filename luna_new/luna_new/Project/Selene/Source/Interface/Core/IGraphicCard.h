

#ifndef ___SELENE__IGRAPHICCARD___
#define ___SELENE__IGRAPHICCARD___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	#define GRAPHIC_CARD_DEFAULT_NO		(0x00000000)					///< デフォルトのビデオカード
	#define GRAPHIC_CARD_NV_PERF_HUD	(0xFFFFFFFF)					///< NVPerfHUD専用のビデオカード

	/**
		@brief 頂点シェーダーバージョン
		@author 葉迩倭
	*/
	enum eVertexShaderVersion
	{
		VERTEXSHADER_VERSION_2_0,			///< Version 2.0
		VERTEXSHADER_VERSION_3_0,			///< Version 3.0
	};

	/**
		@brief サーフェイスフォーマット定義
		@author 葉迩倭
	*/
	enum eSurfaceFormat
	{
		FORMAT_INVALID,						///< 無効

		FORMAT_FROM_FILE,					///< ファイルから取得

		FORMAT_DEPTH16,						///< 16Bit深度バッファ
		FORMAT_DEPTH32,						///< 32Bit深度バッファ
		FORMAT_DEPTHSTENCIL,				///< ステンシル深度バッファ

		FORMAT_DXT1,						///< DXT1圧縮フォーマットテクスチャ
		FORMAT_DXT3,						///< DXT3圧縮フォーマットテクスチャ
		FORMAT_DXT5,						///< DXT5圧縮フォーマットテクスチャ

		FORMAT_BACKBUFFER,					///< バックバッファに準拠
		FORMAT_TARGET16,					///< 16Bitレンダリングターゲット
		FORMAT_TARGET32,					///< 32Bitレンダリングターゲット
		FORMAT_TARGET_HDR,					///< HDR用レンダリングターゲット
		FORMAT_TARGET_SHADOWMAP,			///< シャドウマップ用レンダリングターゲット

		FORMAT_ALPHAONLY,					///< アルファ用テクスチャ

		FORMAT_TEXTURE32,					///< 32Bitテクスチャフォーマットに準拠
		FORMAT_TEXTURE16,					///< 16Bitテクスチャフォーマットに準拠

		FORMAT_TEXTURE_2D,					///< 2D用汎用テクスチャフォーマット
		FORMAT_TEXTURE_3D,					///< 3D用汎用テクスチャフォーマット
	};

	/**
		@brief ビデオカード管理インターフェイス
		@author 葉迩倭
	*/
	class IGraphicCard
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
		virtual Uint32 Release( void )																	= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																	= 0;

		/**
			@brief 16Bitカラーモードを使用
			@author 葉迩倭

			フルスクリーン時の画面カラーを32Bitではなく16Bitにします。<BR>
			フィルレートの厳しい環境で速度の向上が望めますが、<BR>
			マッハバンドなどの画質的な問題も出ます。
		*/
		virtual void EnableHighlColorScreen( void )														= 0;

		/**
			@brief ピクセルシェーダーがサポートされているか取得
			@author 葉迩倭
			@param Major	[in] メジャーバージョン
			@param Minor	[in] マイナーバージョン

			現在のデバイスで指定したピクセルシェーダーをサポート<BR>
			しているかどうかを取得します。
		*/
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor )								= 0;

		/**
			@brief 画面解像度数取得
			@author 葉迩倭
			@param IsFullColor	[in] フルカラー(32Bit)の画面解像度か否か
			@return 画面解像度数

			使用可能な画面解像度の数を取得できます。<BR>
			IsFullColorフラグに応じて、16Bit/32Bitカラーの画面解像度数が取得出来ます。
		*/
		virtual Sint32 GetScreenTypeCount( Bool IsFullColor )											= 0;

		/**
			@brief 画面解像度
			@author 葉迩倭
			@param IsFullColor	[in] フルカラー(32Bit)の画面解像度か否か
			@param No			[in] 画面解像度のインデックス（最大数はGetScreenTypeCount()で取得）
			@param Width		[out] 画面横幅格納先
			@param Height		[out] 画面縦幅格納先

			使用可能な画面解像度を取得します。
		*/
		virtual void GetScreenType( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height )		= 0;

		/**
			@brief レンダリングターゲットテクスチャサイズ数取得
			@author 葉迩倭
			@return レンダリングターゲットテクスチャサイズ数

			使用可能なレンダリングターゲットテクスチャサイズの数を取得できます。
		*/
		virtual Sint32 CreateRenderTargetTextureSizeCount( void )										= 0;

		/**
			@brief レンダリングターゲットテクスチャサイズ
			@author 葉迩倭
			@param No			[in] レンダリングターゲットテクスチャサイズのインデックス（最大数はCreateRenderTargetTextureSizeCount()で取得）
			@param pWidth		[out] 画面横幅格納先
			@param pHeight		[out] 画面縦幅格納先

			使用可能なレンダリングターゲットテクスチャサイズを取得します。
		*/
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight )		= 0;

		/**
			@brief グラフィックカード名称取得
			@author 葉迩倭
			@param pName		[out] 名称格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードの名称を取得します。
		*/
		virtual void GetGraphicCardName( wchar_t *pName, Uint32 NameSize )									= 0;

		/**
			@brief グラフィックカードのドライバー取得
			@author 葉迩倭
			@param pName		[out] ドライバー格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードのドライバーを取得します。
		*/
		virtual void GetGraphicCardDriver( wchar_t *pName, Uint32 NameSize )								= 0;

		/**
			@brief グラフィックカードのバージョン取得
			@author 葉迩倭
			@param pName		[out] バージョン格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードのバージョンを取得します。
		*/
		virtual void GetGraphicCardVersion( wchar_t *pName, Uint32 NameSize )								= 0;

		/**
			@brief IDeviceインターフェイス生成
			@author 葉迩倭
			@return IDeviceインターフェイス

			グラフィックカード上のデバイス制御用のIDeviceインターフェイスを取得します。<BR>
			IDeviceインターフェイスは１つのIGraphicCardに対して１つしか存在しません。
		*/
		virtual IDevice *CreateDevice( void )															= 0;
	};
}


#endif // ___SELENE__IGRAPHICCARD___

