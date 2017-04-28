

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
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief ���W�ϊ��p�p���f�[�^�ݒ�
			@author �t���`
			@param Style	[in] �p���f�[�^

			���W�ϊ��p�̎p���f�[�^��ݒ肵�܂��B
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e���V�[���}�l�[�W���[�ɑ΂��ă����_�����O���N�G�X�g�����܂��B<BR>
			���ۂ̃����_�����O�����̓V�[���}�l�[�W���[���ōs���܂��B<BR>
			���̂��߁A���̊֐��̓����_�����O������҂����ɖ߂��Ă��܂��B
		*/
		virtual void Rendering( void )										= 0;

		/**
			@brief �t���[���f�[�^�擾
			@author �t���`
			@param FrameIndex	[in] �t���[���ԍ�
			@param pFrame		[in] �t���[���i�[��

			���f�����̃t���[���f�[�^���擾���܂��B<BR>
			�擾�����t���[���͕s�v�ɂȂ�����Release()���Ă��������B
		*/
		virtual Bool GetFrame( Uint32 FrameIndex, IFrame *&pFrame )			= 0;

		/**
			@brief �t���[�����擾
			@author �t���`
			@return �t���[����

			���f�����̃t���[�������擾���܂��B
		*/
		virtual Uint32 GetFrameCount( void )								= 0;

		/**
			@brief ���b�V���f�[�^�擾
			@author �t���`
			@param MeshIndex	[in] ���b�V���ԍ�
			@param pMesh		[in] ���b�V���i�[��

			���f�����̃��b�V���f�[�^���擾���܂��B<BR>
			�擾�������b�V���͕s�v�ɂȂ�����Release()���Ă��������B
		*/
		virtual Bool GetMesh( Uint32 MeshIndex, IMesh *&pMesh )				= 0;

		/**
			@brief ���b�V�����擾
			@author �t���`
			@return ���b�V����

			���f�����̃��b�V�������擾���܂��B
		*/
		virtual Uint32 GetMeshCount( void )									= 0;
	};
}


#endif // ___SELENE__IMODEL___

