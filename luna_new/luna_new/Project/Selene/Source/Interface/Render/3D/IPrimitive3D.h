

#ifndef ___SELENE__IPRIMITIVE3D___
#define ___SELENE__IPRIMITIVE3D___


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
		@brief 3Dプリミティブ描画クラス
		@author 葉迩倭

		ポリゴンデータを自分で作るときに使用するためのクラスです。<BR>
		作成時にフラグで指定した頂点データとインデックスデータを<BR>
		プログラムでバッファに追加していきレンダリングします。<BR>
		ライティングやスキニングなどの機能がサポートされていますが、<BR>
		バンプマッピングはサポートされていません。<BR>
	<BR>
		また現行のバージョンでは内部で所持しているシェーダーでしか<BR>
		レンダリングをする事ができません。<BR>
		この制限は修正予定です。
	*/
	class IPrimitive3D
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
		virtual Sint32 Rendering( void )										= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count )		= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count )	= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count )		= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count )		= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count )	= 0;

		/**
			@brief インデックスデータを追加
			@author 葉迩倭
			@param pIndex		[in] インデックスデータ
			@param IndexCount	[in] インデックス数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへインデックスデータを追加します。<BR>
			生成時に指定したインデックスフォーマットに適合したインデックスデータを設定してください。
		*/
		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DBase &Vtx, Uint32 Index )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DTexture &Vtx, Uint32 Index )		= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DLight &Vtx, Uint32 Index )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DBump &Vtx, Uint32 Index )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DAnimation &Vtx, Uint32 Index )		= 0;

		/**
			@brief 頂点数取得
			@author 葉迩倭
			@return 追加要求をした頂点の数

			追加要求を行ったSVertex3DBase頂点の数を取得します。<BR>
			この値は実際に追加された数ではなく、Pushを行って追加された数を<BR>
			取得するので、実際に持てる最大数以上の数を返す場合があります。
		*/
		virtual Uint32 GetVertexCount( void )								= 0;

		/**
			@brief インデックス数取得
			@author 葉迩倭
			@return 追加要求をしたインデックスの数

			追加要求を行ったインデックスの数を取得します。<BR>
			この値は実際に追加された数ではなく、Pushを行って追加された数を<BR>
			取得するので、実際に持てる最大数以上の数を返す場合があります。
		*/
		virtual Uint32 GetIndexCount( void )								= 0;

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
			@brief ボーン数設定
			@author 葉迩倭
			@param BoneCount	[in] ボーン数

			レンダリングに使われるボーンの数を設定します。
		*/
		virtual void SetBoneCount( Sint32 BoneCount )						= 0;

		/**
			@brief オフセット用ボーン設定
			@author 葉迩倭
			@param No		[in] ボーン番号
			@param Matrix	[in] オフセット行列

			指定番号のボーンの親からのオフセット用の行列を設定します。
		*/
		virtual void SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix )		= 0;

		/**
			@brief トランスフォーム用ボーン設定
			@author 葉迩倭
			@param No		[in] ボーン番号
			@param Matrix	[in] トランスフォーム行列

			指定番号のボーンのトランスフォーム用の行列を設定します。
		*/
		virtual void SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix )	= 0;

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

		/**
			@brief スペキュラ色設定
			@author 葉迩倭
			@param Color	[in] スペキュラの色

			スペキュラの色を設定します。
		*/
		virtual void SetSpecularColor( CColor Color )						= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param fRefractive		[in] スペキュラの屈折率(初期20.0f)

			マテリアルのスペキュラの屈折率を設定します
		*/
		virtual void SetSpecularRefractive( Float fRefractive )				= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param fRoughly			[in] スペキュラの粗さ(初期0.5f)

			マテリアルのスペキュラの粗さを設定します
		*/
		virtual void SetSpecularRoughly( Float fRoughly )					= 0;
	};
}


#endif // ___SELENE__IPRIMITIVE3D___


