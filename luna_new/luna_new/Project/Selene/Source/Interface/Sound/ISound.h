

#ifndef ___SELENE__ISOUND___
#define ___SELENE__ISOUND___


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
		@brief サウンド管理クラス
		@author 葉迩倭

		サウンドの処理を行うクラスです。<BR>
		WAV/圧縮WAVE/OGGの再生に対応しています。
	*/
	class ISound
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )								= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照値
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照値
		*/
		virtual Uint32 AddRef( void )								= 0;

		/**
			@brief 再生
			@author 葉迩倭
			@param LoopCount		[in] ループカウント
			@param LoopInSample		[in] ループ後開始位置サンプル数

			読み込んだサウンドデータの再生を開始します。<BR>
			ループ数と、ループ後再生開始位置をサンプル単位で指定できます。
		*/
		virtual void Play( Uint32 LoopCount, Uint32 LoopInSample )	= 0;

		/**
			@brief 停止
			@author 葉迩倭

			再生中のサウンドを停止します。
		*/
		virtual void Stop( void )									= 0;

		/**
			@brief 一時停止/解除
			@author 葉迩倭

			再生中のサウンドを一時停止、<BR>
			一時停止中のサウンドを再生します。
		*/
		virtual void Pause( void )									= 0;

		/**
			@brief ボリューム変更
			@author 葉迩倭
			@param fVolume	[in] ボリューム（0～100）

			ボリュームの変更を行います。
		*/
		virtual void SetVolume( Float fVolume )						= 0;

		/**
			@brief パン移動
			@author 葉迩倭
			@param fPan	[in] パン（-100～+100）

			パンの移動を行います。
		*/
		virtual void SetPan( Float fPan )							= 0;

		/**
			@brief 再生チェック
			@author 葉迩倭
			@retval false	再生していない
			@retval true	再生している

			現在再生中のサウンドかどうか調べます。
		*/
		virtual Bool IsPlay( void )									= 0;
	};
}

#endif // ___SELENE__ISOUND___

