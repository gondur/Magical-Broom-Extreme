

#ifndef ___SELENE__EVENT___
#define ___SELENE__EVENT___


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
		@brief スレッド用イベントオブジェクト
		@author 葉迩倭
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];					///< イベントハンドル
		Uint32 m_HandleCount;										///< イベント数

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param IsSignal		[in] シグナル状態で初期化する場合はtrue
			@param Count		[in] イベントのカウント（MAXIMUM_WAIT_OBJECTS以下）
		*/
		CEvent( Bool IsSignal = false, Uint32 Count = 1 );

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CEvent();

		/**
			@brief 指定されたイベントをシグナル状態に設定
			@author 葉迩倭
			@param No	[in] シグナル状態するイベントの番号
		*/
		virtual void Set( Uint32 No = 0 );

		/**
			@brief 指定されたイベントを非シグナル状態に設定
			@author 葉迩倭
			@param No	[in] 非シグナル状態するイベントの番号
		*/
		virtual void Reset( Uint32 No = 0 );

		/**
			@brief 指定したイベントがシグナル状態かチェック
			@author 葉迩倭
			@param No	[in] チェックするイベントの番号
			@retval false	非シグナル状態
			@retval true	シグナル状態
		*/
		virtual Bool IsSignal( Uint32 No = 0 );

		/**
			@brief 全てのイベントがシグナル状態かチェック
			@author 葉迩倭
			@retval false	非シグナル状態
			@retval true	シグナル状態
		*/
		virtual Bool IsSignalAll( void );

		/**
			@brief シグナル状態になったイベントを取得
			@author 葉迩倭
			@param TimeOut		[in] タイムアウトms時間（-1で無限）
			@retval -1		タイムアウト
			@retval 0以上	シグナル状態になったイベント番号
		*/
		virtual Sint32 Wait( Uint32 TimeOut = -1 );
	};
}


#endif // ___SELENE__EVENT___


