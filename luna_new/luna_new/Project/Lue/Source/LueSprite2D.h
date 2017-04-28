
#ifndef ___LUE_SPRITE2D_H___
#define ___LUE_SPRITE2D_H___


//=============================================================================
// INCLUDE
//=============================================================================
#include "LueBase.h"


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//=============================================================================
// PROTOTYPE
//=============================================================================
/**
	@brief スプライトの解放
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル

	スプライトの解放を行います。
*/
void LueSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief スプライト生成
	@author 葉迩倭

	@param PrimitiveMax		[in] プリミティブ最大数
	@param hTexture			[in] 接続するテクスチャのハンドル

	@return スプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	スプライトオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズであり、<BR>
	シザリング等を行うとリクエストした頂点数よりも多く消費されるので<BR>
	目安程度として溢れない十分な大きさを指定するようにしてください。<BR>
	また hTeture で指定したテクスチャを使って描画されます。
*/
LUE_HANDLE LueSprite2D_Create( unsigned int PrimitiveMax, LUE_HANDLE hTexture );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでリクエストされたプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LueSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LueSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LueSprite2D_End( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Dst		[in] 描画先矩形
	@param Src		[in] テクスチャUV矩形
	@param Color	[in] 頂点色

	スプライトを使った矩形の描画を行います。
*/
void LueSprite2D_DrawSquare( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Dst		[in] 描画先矩形
	@param Src		[in] テクスチャUV矩形
	@param Color	[in] 頂点色
	@param Angle	[in] 1周65536とした回転角度

	スプライトを使った矩形の回転描画を行います。
*/
void LueSprite2D_DrawSquareRotate( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, unsigned int Angle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Pos		[in] ポイントのX,Y値が格納された配列
	@param Width	[in] ポイントの幅が格納された配列
	@param Angle	[in] ポイントの1周65536とした回転角度が格納された配列
	@param Color	[in] 1周65536とした回転角度
	@param Count	[in] 各配列の要素数
	@param Src		[in] テクスチャUV矩形

	スプライトを使ったリスト状の描画を行います<BR>
	曲がるレーザーのような多関節系の表現するのに適しています。
*/
void LueSprite2D_DrawList( LUE_HANDLE Handle, LuePoint Pos[], float Width[], int Angle[], unsigned int Color[], int Count, LueRect Src );

/**
	@brief 円状フェード
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル
	@param SrcRect		[in] テクスチャの適応矩形
	@param Divide		[in] 回転部分分割数（１６程度推奨）
	@param Side			[in] 側面分割数（１６程度推奨）
	@param Alpha		[in] 半透明度（-255～+255)

	画面中心に向かってフェードイン／フェードアウトをします<BR>
	画面効果としてよく見かける効果ですが簡単に使える画面効果として実装してあります。
*/
void LueSprite2D_CircleFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha );

/**
	@brief 回転フェード
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル
	@param SrcRect		[in] テクスチャの適応矩形
	@param Divide		[in] 回転部分分割数（１６程度推奨）
	@param Side			[in] 側面分割数（１６程度推奨）
	@param Alpha		[in] 半透明度（-255～+255)

	時計回りに回転するようにフェードイン／フェードアウトをします<BR>
	画面効果としてよく見かける効果ですが簡単に使える画面効果として実装してあります。
*/
void LueSprite2D_CircleRoundFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_SPRITE2D_H___
