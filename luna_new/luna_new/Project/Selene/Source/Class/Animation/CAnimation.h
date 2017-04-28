

#ifndef ___SELENE__ANIMATION_H___
#define ___SELENE__ANIMATION_H___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief アニメーションタイプ定義
		@author 葉迩倭
	*/
	enum eAnimationType
	{
		ANIM_TYPE_STEP,							///< ステップ補間
		ANIM_TYPE_LINEAR,						///< 線形補間
		ANIM_TYPE_TCB,							///< ＴＣＢスプライン補間
	};

	/**
		@brief キーフレームデータ
		@author 葉迩倭
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< スプライン時のIN係数を定数にするかどうか
		Bool IsOut;								///< スプライン時のOUT係数を定数にするかどうか
		Float fTime;							///< キー時間
		Float fParam;							///< キー値
		Float fIn;								///< IN係数の定数
		Float fOut;								///< OUT係数の定数

		SKeyFrame *pPrev;						///< 前方キーフレームデータポインタ
		SKeyFrame *pNext;						///< 後方キーフレームデータポインタ
	};

	/**
		@brief アニメーションクラス
		@author 葉迩倭
	*/
	class CAnimation
	{
	private:
		Float m_fTimeFirst;						///< 開始時間
		Float m_fTimeLast;						///< 終了時間
		SKeyFrame *m_pKeys;						///< キーフレームデータポインタ
		Uint32 m_KeyMax;						///< キーフレーム数

	private:
		/**
			@brief 指定時間から最も近いキーデータを取得します
			@author 葉迩倭
			@param pKeys		[in] キーフレームデータ
			@param fTime		[in] 検索時間
			@param KeyMax		[in] キー最大数
			@return キーフレームデータポインタ

			指定時間からもっとも近いキー情報を、<BR>
			バイナリサーチで検索します。
		*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

		/**
			@brief エルミート補間関数を処理します
			@author 葉迩倭
			@param fTime	[in] 時間
			@param pH1		[out] パラメーター格納先１
			@param pH2		[out] パラメーター格納先２
			@param pH3		[out] パラメーター格納先３
			@param pH4		[out] パラメーター格納先４

			エルミート補間関数を使って与えられたパラメーターから<BR>
			結果を算出します。
		*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

		/**
			@brief 前方のキーの出力先のパラメータを求めます
			@author 葉迩倭
			@param pKey0	[in] 前方キーデータ
			@param pKey1	[in] 後方キーデータ
			@return 算出されたパラメーター

			指定時間に対しての直前のキーの挙動を計算します。
		*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

		/**
			@brief 後方のキーの出力先のパラメータを求めます
			@author 葉迩倭
			@param pKey0	[in] 前方キーデータ
			@param pKey1	[in] 後方キーデータ
			@return 算出されたパラメーター

			指定時間に対しての直後のキーの挙動を計算します。
		*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param KeyMax		[in] キー最大数
		*/
		CAnimation( Uint32 KeyMax );

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CAnimation();

		/**
			@brief キーフレームデータにキーを設定します
			@author 葉迩倭
			@param KeyNo		[in] 設定先キー番号
			@param fTime		[in] 設定時間
			@param fParam		[in] 設定パラメータ
			@param IsIn			[in] 入力パラメーター指定有無
			@param IsOut		[in] 出力パラメーター指定有無
			@param fIn			[in] 入力パラメーター
			@param fOut			[in] 出力パラメーター
			@return 成功時はtrue

			指定のキーに対して、補間用のパラメーターを設定します。
		*/
		virtual Bool SetKey( Uint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

		/**
			@brief 指定タイプのアニメーションで指定時間における値を取得します
			@author 葉迩倭
			@param fTime		[in] 時間
			@param Type			[in] 補間タイプ
			@param fDefault		[in] デフォルト値
			@return		補間結果値

			指定時間に対して指定タイプで補間した場合の結果を取得します。
		*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}


#endif // ___SELENE__ANIMATION_H___

