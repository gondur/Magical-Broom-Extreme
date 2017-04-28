

#ifndef ___SELENE__ICORE___
#define ___SELENE__ICORE___


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
		@brief フレームレート定義
		@author 葉迩倭
	*/
	enum eFrameRate
	{
		FRAME_RATE_60,
		FRAME_RATE_30,
		FRAME_RATE_20,
		FRAME_RATE_15,
		FRAME_RATE_VSYNC,
	};

	/**
		@brief ウィンドウ管理インターフェイス
		@author 葉迩倭
	*/
	class ICore
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
		virtual Uint32 Release( void )																							= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																							= 0;

		/**
			@brief コアの初期化
			@author 葉迩倭
			@param pAppName		[in] アプリケーション名
			@param FrameRate	[in] フレームレート
			@retval false	失敗
			@retval true	成功

			アプリケーションに関する初期化を行います。
		*/
		virtual Bool Initialize( const wchar_t *pAppName, eFrameRate FrameRate )														= 0;

		/**
			@brief コアの開始
			@author 葉迩倭
			@param ScreenWidth	[in] 画面横幅
			@param ScreenHeight	[in] 画面縦幅
			@param IsWindowType	[in] ウィンドウモードフラグ

			ウィンドウを作成し、アプリケーションを起動します。<BR>
			ここでの設定で起動後変更可能なものは画面モードだけです。
		*/
		virtual void Start( Uint32 ScreenWidth, Uint32 ScreenHeight, Bool IsWindowType )										= 0;

		/**
			@brief コアの終了
			@author 葉迩倭

			ウィンドウを解体し、アプリケーションを終了します。<BR>
			この関数は終了を通知するだけで、実際にはメインループ後に<BR>
			終了処理が行われます。<BR>
		*/
		virtual void Exit( void )																								= 0;

		/**
			@brief アプリケーションメイン処理
			@author 葉迩倭
			@param IsFullActive	[in] 常時動作フラグ
			@retval false	アプリケーションは終了した
			@retval true	アプリケーションは稼働中

			IsFullActiveにtrueを指定すると、<BR>
			ウィンドウがフォーカスを失っている状態でも動作し続けます。
		*/
		virtual Bool Run( Bool IsFullActive = false )																			= 0;

		/**
			@brief ウィンドウハンドル取得
			@author 葉迩倭
			@return ウィンドウのウィンドウハンドル

			ICoreの所有するウィンドウのウィンドウハンドルを取得します。
		*/
		virtual HWND GetWindowHandle( void )																					= 0;

		/**
			@brief ウィンドウハンドル取得
			@author 葉迩倭
			@return ウィンドウのウィンドウハンドル

			ICoreの所有するウィンドウのウィンドウハンドルを取得します。
		*/
		virtual void SetVirtualScreenEnable( Bool Flag )																		= 0;

		/**
			@brief 仮想画面設定
			@author 葉迩倭
			@param RealWidth		[in] 実画面の横幅
			@param RealHeight		[in] 実画面の縦幅
			@param VirtualWidth		[in] 仮想画面の横幅
			@param VirtualHeight	[in] 仮想画面の縦幅

			可変画面サイズ用の設定を行います。<BR>
			3D用に画面のサイズを自由に変えられるように作られている場合でも<BR>
			2Dの描画は仮想画面に設定された画面サイズと見立てて描画を行います。<BR>
			つまり仮想画面が(640x480)の時に(0,0)-(640,480)への全画面の2D描画を行った場合、<BR>
			実際の画面のサイズが(320x240)や(1280x960)等のサイズであっても<BR>
			全画面に自動的に拡大縮小して描画されるということです。
		*/
		virtual void SetVirtualScreenSize( Uint32 RealWidth, Uint32 RealHeight, Uint32 VirtualWidth, Uint32 VirtualHeight )		= 0;

		/**
			@brief フレーム時間を取得します。
			@author 葉迩倭
			@return フレーム時間

			前フレームの処理にかかった時間を取得します。<BR>
			このフレーム時間は1秒で1.0になるようになっています。<BR>
			可変フレームレート系のゲームを作る場合に利用してください。
		*/
		virtual Float GetFrameTime( void )																						= 0;

		/**
			@brief フレームカウントを取得します。
			@author 葉迩倭
			@return フレーム数

			起動時からの総フレーム数を取得します。
		*/
		virtual Uint32 GetSyncCount( void )																						= 0;

		/**
			@brief フレームレートを取得します。
			@author 葉迩倭
			@return フレームレート

			現在のフレームレートを取得します。
		*/
		virtual eFrameRate GetFrameRate( void )																						= 0;

		/**
			@brief グラフィックカードインターフェイスを取得
			@author 葉迩倭
			@param GraphicCardNo	[in] グラフィックカード番号
			@param VsVer			[in] 使用する頂点シェーダーのバージョン
			@return グラフィックカードインターフェイス

			グラフィックカードに関しての初期化を行い、<BR>
			そのインターフェイスを取得します。<BR>
			通常GraphicCardNoにはGRAPHIC_CARD_DEFAULT_NOを指定します。<BR>
			「NV PerfHUD」のインストールされた環境では、<BR>
			GRAPHIC_CARD_NV_PERF_HUDを指定することでそれを有効に出来ます。
		*/
		virtual IGraphicCard *CreateGraphicCard( Uint32 GraphicCardNo, eVertexShaderVersion VsVer )								= 0;

		/**
			@brief マウスインターフェイスを取得
			@author 葉迩倭
			@return マウスインターフェイス

			ICoreの所有するウィンドウに関連付けられたマウスの初期化を行い、<BR>
			そのインターフェイスを取得します。<BR>
			マウスに関しての情報はこのインターフェイス経由で取得して下さい。
		*/
		virtual IMouse *GetMouse( void ) const																					= 0;

		/**
			@brief キーボードインターフェイスを取得
			@author 葉迩倭
			@return キーボードインターフェイス

			ICoreの所有するウィンドウに関連付けられたキーボードの初期化を行い、<BR>
			そのインターフェイスを取得します。<BR>
			キーボードに関しての情報はこのインターフェイス経由で取得して下さい。
		*/
		virtual IKeyboard *GetKeyboard( void ) const																			= 0;

		/**
			@brief ファイルマネージャーインターフェイス生成
			@author 葉迩倭
			@return ファイルマネージャーインターフェイス

			新規のファイルマネージャーインターフェイスを生成します。<BR>
			ファイルのパスなどの設定は全てIFileManagerを経由して行います。
			取得したファイルマネージャーインターフェイスは使用終了後には必ずRelease()して下さい。。
		*/
		virtual IFileManager *CreateFileMgr( void )																				= 0;

		/**
			@brief ファイルマネージャーインターフェイス取得
			@author 葉迩倭
			@return ファイルマネージャーインターフェイス

			現在設定されているファイルマネージャーインターフェイスを取得します。<BR>
			設定済みのファイルマネージャーインターフェイスへのアクセスを行う場合に使用してください。
		*/
		virtual IFileManager *GetFileMgrPointer( void ) const																	= 0;

		/**
			@brief ファイルマネージャーインターフェイス設定
			@author 葉迩倭
			@param pMgr	[in] ファイルマネージャーインターフェイス

			ファイルの読み込みに使われるファイルマネージャーインターフェイスを設定します。<BR>
			ファイルの読み込みはこのマネージャーを経由して行うので、<BR>
			ファイルの読み込みを行う場合は必ず設定してください。<BR>
			既に設定されているマネージャーは内部で解放されます。
		*/
		virtual void SetFileManager( IFileManager *pMgr )																		= 0;

		/**
			@brief サウンドファイル読み込み
			@author 葉迩倭
			@param pFileName		[in] サウンドファイル名(wav/ogg)
			@param IsGlobalScope	[in] サウンドのスコープ
			@retval NULL		ファイル読み込みエラー
			@retval NULL以外	サウンドインターフェイスのポインタ

			ICoreの所有するウィンドウに関連付けられたサウンドを取得します。<BR>
			IsGlobalScopeにtrueを渡すと、ウィンドウのフォーカスに関係なく<BR>
			再生されます。<BR>
			使用の終了したサウンドは必ずRelease()して下さい。
		*/
		virtual ISound *CreateSoundFromFile( const wchar_t *pFileName, Bool IsGlobalScope )										= 0;
	};
}


#endif // ___SELENE__ICORE___

