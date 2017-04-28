

#ifndef ___SELENE__IPOINTPRIMITIVE3D___
#define ___SELENE__IPOINTPRIMITIVE3D___


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
		@brief 3Dポイントプリミティブ描画クラス
		@author 葉迩倭
	*/
	class IPointPrimitive3D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭
			@return シーン内の識別番号

			内部バッファの内容をシーンマネージャーに対してレンダリングリクエストをします。<BR>
			実際のレンダリング処理はシーンマネージャー内で行われます。<BR>
			そのため、この関数はレンダリング処理を待たずに戻ってきます。
		*/
		virtual Sint32 Rendering( void )									= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pPoint		[in] ポイントデータ
			@param PointCount	[in] ポイント数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			生成時に指定した頂点フォーマットに適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DBase *pPoint, Uint32 PointCount )		= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )											= 0;

		/**
			@brief 座標変換用姿勢データ設定
			@author 葉迩倭
			@param Style	[in] 姿勢データ

			座標変換用の姿勢データを設定します。
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief マテリアル色設定
			@author 葉迩倭
			@param Color	[in] マテリアルの色

			マテリアルの色を設定します。
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;
	};
}


#endif // ___SELENE__IPOINTPRIMITIVE3D___


