

#ifndef ___SELENE__CRITICALSECTION___
#define ___SELENE__CRITICALSECTION___


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
		@brief クリティカルセクション管理クラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< クリティカルセクション

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CCriticalSection();

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CCriticalSection();

		/**
			@brief クリティカルセクションに入る
			@author 葉迩倭

			クリティカルセクションに入ります。
		*/
		void Enter( void );

		/**
			@brief クリティカルセクションから抜ける
			@author 葉迩倭

			クリティカルセクションから抜けます。
		*/
		void Leave( void );
	};
}

#endif // ___SELENE__CRITICALSECTION___


