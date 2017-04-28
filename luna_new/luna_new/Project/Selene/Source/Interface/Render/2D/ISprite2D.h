

#ifndef ___SELENE_ISPRITE2D___
#define ___SELENE_ISPRITE2D___


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
		@brief 2Dスプライト管理インターフェイス
		@author 葉迩倭
	*/
	class ISprite2D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																													= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )																													= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )																														= 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pPrimitive	[in] プリミティブデータ
			@param Count		[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )																				= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief 四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色

			最も単純なスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color )														= 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色
			@param Angle		[in] 1周65536とした回転角度

			回転付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle )									= 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭

			@param Pos		[in] 描画位置の配列
			@param Width	[in] 頂点ごとの幅の配列
			@param Angle	[in] 1周65536とした回転角度の配列
			@param Color	[in] 描画色の配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			回転付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src )				= 0;

		/**
			@brief 放射状フェード
			@author 葉迩倭

			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Divide		[in] 円周のポリゴンの分割数
			@param Side			[in] １辺あたりのポリゴンの分割数
			@param Alpha		[in] 透明度

			中心に向かってフェードするエフェクトです。<BR>
			画面の切り替え時などに利用できると思います。
		*/
		virtual void CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )													= 0;

		/**
			@brief 円状回転フェード
			@author 葉迩倭

			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Divide		[in] 円周のポリゴンの分割数
			@param Side			[in] １辺あたりのポリゴンの分割数
			@param Alpha		[in] 透明度

			時計回りにフェードするエフェクトです。<BR>
			画面の切り替え時などに利用できると思います。
		*/
		virtual void CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )												= 0;
	};
}


#endif // ___SELENE_ISPRITE2D___

