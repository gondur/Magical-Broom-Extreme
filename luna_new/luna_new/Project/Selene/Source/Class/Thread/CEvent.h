

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
		@brief �X���b�h�p�C�x���g�I�u�W�F�N�g
		@author �t���`
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];					///< �C�x���g�n���h��
		Uint32 m_HandleCount;										///< �C�x���g��

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param IsSignal		[in] �V�O�i����Ԃŏ���������ꍇ��true
			@param Count		[in] �C�x���g�̃J�E���g�iMAXIMUM_WAIT_OBJECTS�ȉ��j
		*/
		CEvent( Bool IsSignal = false, Uint32 Count = 1 );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CEvent();

		/**
			@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
			@author �t���`
			@param No	[in] �V�O�i����Ԃ���C�x���g�̔ԍ�
		*/
		virtual void Set( Uint32 No = 0 );

		/**
			@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
			@author �t���`
			@param No	[in] ��V�O�i����Ԃ���C�x���g�̔ԍ�
		*/
		virtual void Reset( Uint32 No = 0 );

		/**
			@brief �w�肵���C�x���g���V�O�i����Ԃ��`�F�b�N
			@author �t���`
			@param No	[in] �`�F�b�N����C�x���g�̔ԍ�
			@retval false	��V�O�i�����
			@retval true	�V�O�i�����
		*/
		virtual Bool IsSignal( Uint32 No = 0 );

		/**
			@brief �S�ẴC�x���g���V�O�i����Ԃ��`�F�b�N
			@author �t���`
			@retval false	��V�O�i�����
			@retval true	�V�O�i�����
		*/
		virtual Bool IsSignalAll( void );

		/**
			@brief �V�O�i����ԂɂȂ����C�x���g���擾
			@author �t���`
			@param TimeOut		[in] �^�C���A�E�gms���ԁi-1�Ŗ����j
			@retval -1		�^�C���A�E�g
			@retval 0�ȏ�	�V�O�i����ԂɂȂ����C�x���g�ԍ�
		*/
		virtual Sint32 Wait( Uint32 TimeOut = -1 );
	};
}


#endif // ___SELENE__EVENT___


