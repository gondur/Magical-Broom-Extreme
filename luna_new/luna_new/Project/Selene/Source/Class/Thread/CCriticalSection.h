

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
		@brief �N���e�B�J���Z�N�V�����Ǘ��N���X
		@author �t���`
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< �N���e�B�J���Z�N�V����

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CCriticalSection();

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CCriticalSection();

		/**
			@brief �N���e�B�J���Z�N�V�����ɓ���
			@author �t���`

			�N���e�B�J���Z�N�V�����ɓ���܂��B
		*/
		void Enter( void );

		/**
			@brief �N���e�B�J���Z�N�V�������甲����
			@author �t���`

			�N���e�B�J���Z�N�V�������甲���܂��B
		*/
		void Leave( void );
	};
}

#endif // ___SELENE__CRITICALSECTION___


