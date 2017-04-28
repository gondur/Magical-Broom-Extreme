

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
		@brief �T�E���h�Ǘ��N���X
		@author �t���`

		�T�E���h�̏������s���N���X�ł��B<BR>
		WAV/���kWAVE/OGG�̍Đ��ɑΉ����Ă��܂��B
	*/
	class ISound
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƒl
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƒl
		*/
		virtual Uint32 AddRef( void )								= 0;

		/**
			@brief �Đ�
			@author �t���`
			@param LoopCount		[in] ���[�v�J�E���g
			@param LoopInSample		[in] ���[�v��J�n�ʒu�T���v����

			�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
			���[�v���ƁA���[�v��Đ��J�n�ʒu���T���v���P�ʂŎw��ł��܂��B
		*/
		virtual void Play( Uint32 LoopCount, Uint32 LoopInSample )	= 0;

		/**
			@brief ��~
			@author �t���`

			�Đ����̃T�E���h���~���܂��B
		*/
		virtual void Stop( void )									= 0;

		/**
			@brief �ꎞ��~/����
			@author �t���`

			�Đ����̃T�E���h���ꎞ��~�A<BR>
			�ꎞ��~���̃T�E���h���Đ����܂��B
		*/
		virtual void Pause( void )									= 0;

		/**
			@brief �{�����[���ύX
			@author �t���`
			@param fVolume	[in] �{�����[���i0�`100�j

			�{�����[���̕ύX���s���܂��B
		*/
		virtual void SetVolume( Float fVolume )						= 0;

		/**
			@brief �p���ړ�
			@author �t���`
			@param fPan	[in] �p���i-100�`+100�j

			�p���̈ړ����s���܂��B
		*/
		virtual void SetPan( Float fPan )							= 0;

		/**
			@brief �Đ��`�F�b�N
			@author �t���`
			@retval false	�Đ����Ă��Ȃ�
			@retval true	�Đ����Ă���

			���ݍĐ����̃T�E���h���ǂ������ׂ܂��B
		*/
		virtual Bool IsPlay( void )									= 0;
	};
}

#endif // ___SELENE__ISOUND___

