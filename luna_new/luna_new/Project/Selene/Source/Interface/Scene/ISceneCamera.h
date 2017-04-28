

#ifndef ___SELENE__ISCENECAMERA___
#define ___SELENE__ISCENECAMERA___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief シーンカメラ操作用インターフェイス
		@author 葉迩倭

		シーンのカメラを操作するためのインターフェイスです。
	*/
	class ISceneCamera
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																					= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																					= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																					= 0;

		/**
			@brief ワールド→スクリーン座標変換行列取得
			@author 葉迩倭
			@return 変換行列

			ワールド空間からスクリーン座標への逆変換行列を取得します。
		*/
		virtual const CMatrix &WorldToScreen( void ) const																= 0;

		/**
			@brief ワールド→ビュー変換行列取得
			@author 葉迩倭
			@return 変換行列

			ワールド空間からカメラ空間への逆変換行列を取得します。
		*/
		virtual const CMatrix &WorldToView( void ) const																= 0;

		/**
			@brief スクリーン→ワールド変換行列取得
			@author 葉迩倭
			@return 変換行列

			スクリーン座標からワールド空間への逆変換行列を取得します。
		*/
		virtual const CMatrix &ScreenToWorld( void ) const																= 0;

		/**
			@brief ビュー→ワールド変換行列取得
			@author 葉迩倭
			@return 変換行列

			カメラ空間からワールド空間への逆変換行列を取得します。
		*/
		virtual const CMatrix &ViewToWorld( void ) const																= 0;

		/**
			@brief ニアクリップ値取得
			@author 葉迩倭

			@return ニアクリップ値

			ニアクリップ値を取得します。
		*/
		virtual Float GetNearClip( void ) const																			= 0;

		/**
			@brief ファークリップ値取得
			@author 葉迩倭

			@return ファークリップ値

			ファークリップ値を取得します。
		*/
		virtual Float GetFarClip( void ) const																			= 0;

		/**
			@brief プロジェクション行列更新
			@author 葉迩倭

			@param fNearClip	[in] ニアクリップ値
			@param fFarClip		[in] ファークリップ値
			@param FovAngle		[in] 画角（1周65536とした角度）
			@param Width		[in] 表示横幅
			@param Height		[in] 表示縦幅

			プロジェクション行列を更新します。<BR>
			カメラを使用する場合には必ずこの関数でプロジェクションを作成して下さい。<BR>
			またFovAngleに0を指定すると平行投影になります。
		*/
		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )	= 0;

		/**
			@brief カメラデータ初期化
			@author 葉迩倭

			カメラデータを初期化します。<BR>
			座標(0,0,0)からZ軸+方向を向いた状態になります。
		*/
		virtual void Reset( void )																						= 0;

		/**
			@brief カメラデータ更新
			@author 葉迩倭

			カメラのデータを更新します。<BR>
			各種行列やバウンディングボックスなどは<BR>
			この関数を呼び出すことで作成されます。
		*/
		virtual void Update( void )																						= 0;

		/**
			@brief カメラを変換
			@author 葉迩倭

			@param Style	[in] カメラ変換用CStyle

			Ctyleデータで定義された変換処理を<BR>
			カメラに適用します。<BR>
			カメラで使用されるのは移動/回転になります。
		*/
		virtual void SetTransform( CStyle &Style )																		= 0;
	};
}

#endif // ___SELENE__ISCENECAMERA___


