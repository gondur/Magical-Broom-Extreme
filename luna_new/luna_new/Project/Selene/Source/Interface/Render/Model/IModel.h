

#ifndef ___SELENE__IMODEL___
#define ___SELENE__IMODEL___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class IModel
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
			@brief 座標変換用姿勢データ設定
			@author 葉迩倭
			@param Style	[in] 姿勢データ

			座標変換用の姿勢データを設定します。
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容をシーンマネージャーに対してレンダリングリクエストをします。<BR>
			実際のレンダリング処理はシーンマネージャー内で行われます。<BR>
			そのため、この関数はレンダリング処理を待たずに戻ってきます。
		*/
		virtual void Rendering( void )										= 0;

		/**
			@brief フレームデータ取得
			@author 葉迩倭
			@param FrameIndex	[in] フレーム番号
			@param pFrame		[in] フレーム格納先

			モデル内のフレームデータを取得します。<BR>
			取得したフレームは不要になったらRelease()してください。
		*/
		virtual Bool GetFrame( Uint32 FrameIndex, IFrame *&pFrame )			= 0;

		/**
			@brief フレーム数取得
			@author 葉迩倭
			@return フレーム数

			モデル内のフレーム数を取得します。
		*/
		virtual Uint32 GetFrameCount( void )								= 0;

		/**
			@brief メッシュデータ取得
			@author 葉迩倭
			@param MeshIndex	[in] メッシュ番号
			@param pMesh		[in] メッシュ格納先

			モデル内のメッシュデータを取得します。<BR>
			取得したメッシュは不要になったらRelease()してください。
		*/
		virtual Bool GetMesh( Uint32 MeshIndex, IMesh *&pMesh )				= 0;

		/**
			@brief メッシュ数取得
			@author 葉迩倭
			@return メッシュ数

			モデル内のメッシュ数を取得します。
		*/
		virtual Uint32 GetMeshCount( void )									= 0;
	};
}


#endif // ___SELENE__IMODEL___

