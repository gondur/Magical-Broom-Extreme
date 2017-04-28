

#ifndef ___SELENE__IPOINTPRIMITIVE3D___
#define ___SELENE__IPOINTPRIMITIVE3D___


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
		@brief 3D�|�C���g�v���~�e�B�u�`��N���X
		@author �t���`
	*/
	class IPointPrimitive3D
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
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`
			@return �V�[�����̎��ʔԍ�

			�����o�b�t�@�̓��e���V�[���}�l�[�W���[�ɑ΂��ă����_�����O���N�G�X�g�����܂��B<BR>
			���ۂ̃����_�����O�����̓V�[���}�l�[�W���[���ōs���܂��B<BR>
			���̂��߁A���̊֐��̓����_�����O������҂����ɖ߂��Ă��܂��B
		*/
		virtual Sint32 Rendering( void )									= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pPoint		[in] �|�C���g�f�[�^
			@param PointCount	[in] �|�C���g��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵�����_�t�H�[�}�b�g�ɓK���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DBase *pPoint, Uint32 PointCount )		= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )											= 0;

		/**
			@brief ���W�ϊ��p�p���f�[�^�ݒ�
			@author �t���`
			@param Style	[in] �p���f�[�^

			���W�ϊ��p�̎p���f�[�^��ݒ肵�܂��B
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief �}�e���A���F�ݒ�
			@author �t���`
			@param Color	[in] �}�e���A���̐F

			�}�e���A���̐F��ݒ肵�܂��B
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;
	};
}


#endif // ___SELENE__IPOINTPRIMITIVE3D___


