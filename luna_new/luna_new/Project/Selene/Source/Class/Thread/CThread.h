

#ifndef ___SELENE__CTHREAD___
#define ___SELENE__CTHREAD___


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
		@brief スレッド管理操作クラス
		@author 葉迩倭

		スレッドを操作するためのクラスです。
	*/
	class SELENE_DLL_API CThread
	{
	private:
		/**
			@brief スレッド用関数
			@author 葉迩倭
			@param pArguments	[in] CThreadのポインタ

			クラスの関数を直接は指定できないので<BR>
			staticな関数を経由して呼び出す。
		*/
		static unsigned __stdcall ThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< スレッドハンドル
		Uint32 m_ThreadId;					///< スレッドID
		void *m_pData;						///< スレッドデータ伝達用ポインタ
		void (*m_pMainProc)( void* );		///< スレッド関数

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CThread();

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CThread();

	public:
		/**
			@brief スレッド生成
			@author 葉迩倭
			@param pThreadFunc	[in] スレッド関数
			@param pData		[in] スレッドに引き渡すデータポインタ
			@retval false	生成失敗or既にスレッドが生成されている
			@retval true	生成完了
		*/
		virtual Bool Create( void (*pThreadFunc)( void* ), void *pData );

		/**
			@brief スレッド終了待ち
			@author 葉迩倭
			@param TimeOut		[in] 終了待ちをする時間をmsで設定します。<BR>-1を指定すると無限に待ちます。

			スレッドが終了するのを待ちます
		*/
		virtual void WaitForExit( Sint32 TimeOut );

		/**
			@brief スレッドの優先度変更
			@author 葉迩倭
			@param Priority		[in] スレッド処理の優先度

			スレッドの優先度を変更します。<BR>
			デフォルトの優先度はTHREAD_PRIORITY_NORMALです。
		*/
		virtual Bool SetPriority( Sint32 Priority );

		/**
			@brief スレッドの中断を解除
			@author 葉迩倭

			スレッドのサスペンドカウントが 1 減ります。<BR>
			カウントが 0 になった時点でスレッドの中断が解除されます。
		*/
		virtual void Resume( void );

		/**
			@brief スレッドの実行を中断
			@author 葉迩倭

			指定されたスレッドの実行が中断され、<BR>
			そのスレッドのサスペンドカウントが 1 増えます。
		*/
		virtual void Suspend( void );
	};
}


#endif // ___SELENE__CTHREAD___

