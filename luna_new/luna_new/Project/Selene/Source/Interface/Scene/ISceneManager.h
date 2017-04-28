

#ifndef ___SELENE__ISCENEMANAGER___
#define ___SELENE__ISCENEMANAGER___


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
		@brief シーンレンダリングモード
		@author 葉迩倭
	*/
	enum eSceneMode
	{
		SCENE_MODE_NOT_MANAGED,			///< レンダリングしか行わない
		SCENE_MODE_MANAGED,				///< 内部で深度バッファやレンダリングターゲットを管理する
		SCENE_MODE_1PASS_DOF,			///< 1PASSで被写界深度処理を行う（アルファブレンディングはできなくなります
		SCENE_MODE_2PASS_DOF,			///< 2PASSで被写界深度処理を行う（アルファブレンディングができます
		SCENE_MODE_1PASS_DOF_HIGH,		///< 1PASSで高画質被写界深度処理を行う（アルファブレンディングはできなくなります
		SCENE_MODE_2PASS_DOF_HIGH,		///< 2PASSで高画質被写界深度処理を行う（アルファブレンディングができます
	};

	/**
		@brief シーンレンダリングモード
		@author 葉迩倭
	*/
	enum eSceneModeOption
	{
		SCENE_MODE_OPTION_NO,					///< オプションなし
		SCENE_MODE_OPTION_HDR,					///< HDRレンダリングを行います（アルファブレンディング・アルファテストはできなくなります
		SCENE_MODE_OPTION_EDGE,					///< エッジレンダリングを行います
		SCENE_MODE_OPTION_SHADOW,				///< 影のレンダリングを行います
	};

	/**
		@brief シーン管理用インターフェイス
		@author 葉迩倭

		シーン管理を行うためのインターフェイスです。
	*/
	class ISceneManager
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																								= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																								= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																								= 0;

		/**
			@brief シーンカメラ取得
			@author 葉迩倭
			@return カメラデータ

			シーンに関連付けられたカメラを取得します。
		*/
		virtual ISceneCamera *GetSceneCamera( void )																				= 0;

		/**
			@brief シーン初期化
			@author 葉迩倭

			シーンのライトやフォグなどのデータをリセットします。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void Reset( void )																									= 0;

		/**
			@brief シーン開始
			@author 葉迩倭
			@param IsSort	[in] シーン内のオブジェクトをソートするかどうか

			シーン管理を開始します。<BR>
			この時点でカメラのデータが確定しますので<BR>
			この関数を呼び出したあとのカメラの更新は全て無効です。
		*/
		virtual void Begin( Bool IsSort )																							= 0;

		/**
			@brief シーン終了
			@author 葉迩倭

			シーンの管理を完了します。
		*/
		virtual void End( void )																									= 0;

		/**
			@brief シーンレンダリング
			@author 葉迩倭
			@param IsDrawBuffer	[in] 内部用バッファの表示（デバッグ用）

			シーンの管理で構築されたシーンをレンダリングします。<BR>
			この関数をコールした段階で内部で描画処理が開始されます。<BR>
			必ずIRender::Begin()～IRender::End()間で呼び出してください。
		*/
		virtual void Rendering( Bool IsDrawBuffer = false )																			= 0;

		/**
			@brief シャドウ用カメラ設定
			@author 葉迩倭
			@param vPosition	[in] カメラ位置
			@param vTarget		[in] カメラ注視点
			@param Fov			[in] 画角（1周65536とした角度）
			@param fNear		[in] 近クリップ面
			@param fFar			[in] 遠クリップ面

			シャドウ用のカメラデータを設定します。
		*/
		virtual void SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias )	= 0;

		/**
			@brief フォグON/OFF
			@author 葉迩倭
			@param Enable	[in] フォグを適用する場合ON

			シーンに適用されるフォグをON/OFFします。
		*/
		virtual void SetFogEnable( Bool Enable )																					= 0;

		/**
			@brief フォグ情報設定
			@author 葉迩倭

			@param fNear	[in] フォグ開始Z（このZより前はフォグに影響されない）
			@param fFar		[in] フォグ終了Z（このZより後は完全にColorの色になる）
			@param Color	[in] フォグの色

			シーンに適用されるフォグのパラメーターを設定します。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetFog( Float fNear, Float fFar, CColor Color )																= 0;

		/**
			@brief 被写界深度用のフォーカス位置を設定します。
			@author 葉迩倭

			@param fForcusZ	[in] フォーカスのＺ（カメラ基準）
			@param fPower	[in] 被写界深度強度

			被写界深度のフォーカス位置を設定します。
		*/
		virtual void SetDepthOfFieldForcus( Float fForcusZ, Float fPower )															= 0;

		/**
			@brief アンビエントライト設定
			@author 葉迩倭
			@param vColorSky	[in] シーン内の天球の環境光の色
			@param vColorEarth	[in] シーン内の地表の環境光の色

			シーンの環境光を設定します。<BR>
			半球ライティングを行うために、天球と地表の色を設定します。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth )												= 0;

		/**
			@brief ディレクションライト設定
			@author 葉迩倭
			@param vDirect	[in] シーン内の平行光源の方向
			@param vColor	[in] シーン内の平行光源の色

			シーンに大して1つだけ平行光源を割り当てることができます。<BR>
			太陽のように遥か遠方に存在し、オブジェクトの位置によって<BR>
			光の方向が変わらないようなライトに向いています。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetDirectionLight( CVector3D &vDirect, CVector3D &vColor )														= 0;

		/**
			@brief ポイントライト追加
			@author 葉迩倭
			@param vPosition	[in] シーン内の点光源の位置
			@param vColor		[in] シーン内の点光源の色
			@param fDistance	[in] シー内の点光源の影響距離

			シーンに対して点光源を追加します<BR>
			最大で32個のライトを設定でき、そのうち最もオブジェクトに近い<BR>
			4つのライトがオブジェクトに適用されます。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance )										= 0;

		/**
			@brief レンダリングターゲットのサイズを設定
			@author 葉迩倭
			@param Size		[in] サイズ

			シーンのレンダリングターゲットのサイズを指定します。<BR>
			eSceneModeがSCENE_MODE_NORMAL以外の場合に使われる各種<BR>
			バッファのサイズに関係します。
		*/
		virtual CPoint2D<Uint32> SetRenderTargetSize( CPoint2D<Uint32> Size )														= 0;

		/**
			@brief レンダリングリクエスト数取得
			@author 葉迩倭
			@return レンダリングリクエスト数

			シーンにリクエストレンダリング数を取得します。
		*/
		virtual Uint32 GetRenderingRequestCount( void )																				= 0;

		/**
			@brief レンダリング数取得
			@author 葉迩倭
			@return レンダリング数

			シーンで実行されたレンダリング数を取得します。<BR>
			2Pass系の処理等もカウントされるので、<BR>
			リクエスト数以上の値になることもあります。
		*/
		virtual Uint32 GetRenderingCount( void )																					= 0;

		/**
			@brief レンダリングピクセル数取得
			@author 葉迩倭
			@return レンダリングピクセル数

			レンダリングしたモデルのレンダリングピクセル数を取得します。<BR>
			サポートされていないビデオカードの場合は0xFFFFFFFFが返ります。
		*/
		virtual Uint32 GetOcculusion( Uint32 Index )																				= 0;
	};
}

#endif // ___SELENE__ISCENEMANAGER___


