

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
		@brief �X���b�h�Ǘ�����N���X
		@author �t���`

		�X���b�h�𑀍삷�邽�߂̃N���X�ł��B
	*/
	class SELENE_DLL_API CThread
	{
	private:
		/**
			@brief �X���b�h�p�֐�
			@author �t���`
			@param pArguments	[in] CThread�̃|�C���^

			�N���X�̊֐��𒼐ڂ͎w��ł��Ȃ��̂�<BR>
			static�Ȋ֐����o�R���ČĂяo���B
		*/
		static unsigned __stdcall ThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< �X���b�h�n���h��
		Uint32 m_ThreadId;					///< �X���b�hID
		void *m_pData;						///< �X���b�h�f�[�^�`�B�p�|�C���^
		void (*m_pMainProc)( void* );		///< �X���b�h�֐�

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CThread();

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CThread();

	public:
		/**
			@brief �X���b�h����
			@author �t���`
			@param pThreadFunc	[in] �X���b�h�֐�
			@param pData		[in] �X���b�h�Ɉ����n���f�[�^�|�C���^
			@retval false	�������sor���ɃX���b�h����������Ă���
			@retval true	��������
		*/
		virtual Bool Create( void (*pThreadFunc)( void* ), void *pData );

		/**
			@brief �X���b�h�I���҂�
			@author �t���`
			@param TimeOut		[in] �I���҂������鎞�Ԃ�ms�Őݒ肵�܂��B<BR>-1���w�肷��Ɩ����ɑ҂��܂��B

			�X���b�h���I������̂�҂��܂�
		*/
		virtual void WaitForExit( Sint32 TimeOut );

		/**
			@brief �X���b�h�̗D��x�ύX
			@author �t���`
			@param Priority		[in] �X���b�h�����̗D��x

			�X���b�h�̗D��x��ύX���܂��B<BR>
			�f�t�H���g�̗D��x��THREAD_PRIORITY_NORMAL�ł��B
		*/
		virtual Bool SetPriority( Sint32 Priority );

		/**
			@brief �X���b�h�̒��f������
			@author �t���`

			�X���b�h�̃T�X�y���h�J�E���g�� 1 ����܂��B<BR>
			�J�E���g�� 0 �ɂȂ������_�ŃX���b�h�̒��f����������܂��B
		*/
		virtual void Resume( void );

		/**
			@brief �X���b�h�̎��s�𒆒f
			@author �t���`

			�w�肳�ꂽ�X���b�h�̎��s�����f����A<BR>
			���̃X���b�h�̃T�X�y���h�J�E���g�� 1 �����܂��B
		*/
		virtual void Suspend( void );
	};
}


#endif // ___SELENE__CTHREAD___

