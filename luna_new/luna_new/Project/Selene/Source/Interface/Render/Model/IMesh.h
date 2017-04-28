

#ifndef ___SELENE__IMESH___
#define ___SELENE__IMESH___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class IMesh
	{
	public:
		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )													= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)													= 0;

		/**
			@brief 鏡面反射用モデルに変換
			@author 葉迩倭

			この関数を呼び出すと事で鏡面反射を有効化出来ます。<BR>
			平行光源に対しての単純なフォン鏡面反射が適用されるようになります。
		*/
		virtual void ConvertReflexMesh( void )											= 0;

		/**
			@brief バンプマップ用モデルに変換
			@author 葉迩倭
			@param pTexNormal	[in] バンプ用法線マップ

			この関数を呼び出すと事でバンプマップを有効化出来ます。<BR>
			ただし以下の条件を満たしている必要があります。<BR>
			・テクスチャUVデータを持っている<BR>
			・法線・接線データを持っている<BR>
			<BR>
			通常ConvertX2SMFで作成した場合は元のXファイルにテクスチャが含まれて入れば、<BR>
			上記のデータは含まれています。<BR>
			またこのとき指定するテクスチャは法線マップである必要があります。<BR>
			法線マップはIRender::CreateTextureFromFileForNormalMap()か
			IRender::CreateTextureFromMemoryForNormalMap()関数で作成できます。
		*/
		virtual void ConvertBumpMesh( ITexture *pTexNormal )								= 0;

		/**
			@brief 視差マップ用モデルに変換
			@author 葉迩倭
			@param pTexNormal		[in] バンプ用法線マップ
			@param fParallaxDepth	[in] 視差深度（だいたい0.01～0.05程度）

			この関数を呼び出すと事で視差マップを有効化出来ます。<BR>
			ただし以下の条件を満たしている必要があります。<BR>
			・テクスチャUVデータを持っている<BR>
			・法線・接線データを持っている<BR>
			<BR>
			通常ConvertX2SMFで作成した場合は元のXファイルにテクスチャが含まれて入れば、<BR>
			上記のデータは含まれています。<BR>
			法線マップはIRender::CreateTextureFromFileForNormalMap()か
			IRender::CreateTextureFromMemoryForNormalMap()関数で作成できます。
		*/
		virtual void ConvertParallaxMesh( ITexture *pTexNormal, Float fParallaxDepth )	= 0;

		/**
			@brief マテリアルの数を取得
			@author 葉迩倭
			@return マテリアル数

			メッシュが所持するマテリアルの数を取得します
		*/
		virtual Uint32 GetMaterialCount( void )											= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param MaterialIndex	[in] マテリアル番号
			@param Color			[in] スペキュラの色

			マテリアルごとのスペキュラの色を設定します
		*/
		virtual void SetSpecularColor( Uint32 MaterialIndex, CColor Color )				= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param MaterialIndex	[in] マテリアル番号
			@param fRefractive		[in] スペキュラの屈折率(初期20.0f)

			マテリアルごとのスペキュラの屈折率を設定します
		*/
		virtual void SetSpecularRefractive( Uint32 MaterialIndex, Float fRefractive )	= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param MaterialIndex	[in] マテリアル番号
			@param fRoughly			[in] スペキュラの粗さ(初期0.5f)

			マテリアルごとのスペキュラの粗さを設定します
		*/
		virtual void SetSpecularRoughly( Uint32 MaterialIndex, Float fRoughly )			= 0;

		/**
			@brief 法線データの可視化をします
			@author 葉迩倭
			@param fLength	[in] 長さ

			メッシュの法線・接線・従法線データを可視化させることができます。
		*/
		virtual void NormalVisible( Float fLength )										= 0;

		/**
			@brief バウンディングデータの可視化をします
			@author 葉迩倭

			メッシュのバウンディングボックスを可視化させることができます。
		*/
		virtual void BoundingVisible( void )											= 0;

		/**
			@brief レンダリングID取得
			@author 葉迩倭

			レンダリング時のシーンIDを取得します。
		*/
		virtual Sint32 GetRenderID( void )												= 0;
	};
}


#endif // ___SELENE__IMESH___

