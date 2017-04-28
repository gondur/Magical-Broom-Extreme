

#ifndef ___SELENE__ISCENECAMERA___
#define ___SELENE__ISCENECAMERA___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �V�[���J��������p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���̃J�����𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISceneCamera
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																					= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																					= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																					= 0;

		/**
			@brief ���[���h���X�N���[�����W�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���X�N���[�����W�ւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &WorldToScreen( void ) const																= 0;

		/**
			@brief ���[���h���r���[�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���J������Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &WorldToView( void ) const																= 0;

		/**
			@brief �X�N���[�������[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�X�N���[�����W���烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &ScreenToWorld( void ) const																= 0;

		/**
			@brief �r���[�����[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�J������Ԃ��烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &ViewToWorld( void ) const																= 0;

		/**
			@brief �j�A�N���b�v�l�擾
			@author �t���`

			@return �j�A�N���b�v�l

			�j�A�N���b�v�l���擾���܂��B
		*/
		virtual Float GetNearClip( void ) const																			= 0;

		/**
			@brief �t�@�[�N���b�v�l�擾
			@author �t���`

			@return �t�@�[�N���b�v�l

			�t�@�[�N���b�v�l���擾���܂��B
		*/
		virtual Float GetFarClip( void ) const																			= 0;

		/**
			@brief �v���W�F�N�V�����s��X�V
			@author �t���`

			@param fNearClip	[in] �j�A�N���b�v�l
			@param fFarClip		[in] �t�@�[�N���b�v�l
			@param FovAngle		[in] ��p�i1��65536�Ƃ����p�x�j
			@param Width		[in] �\������
			@param Height		[in] �\���c��

			�v���W�F�N�V�����s����X�V���܂��B<BR>
			�J�������g�p����ꍇ�ɂ͕K�����̊֐��Ńv���W�F�N�V�������쐬���ĉ������B<BR>
			�܂�FovAngle��0���w�肷��ƕ��s���e�ɂȂ�܂��B
		*/
		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )	= 0;

		/**
			@brief �J�����f�[�^������
			@author �t���`

			�J�����f�[�^�����������܂��B<BR>
			���W(0,0,0)����Z��+��������������ԂɂȂ�܂��B
		*/
		virtual void Reset( void )																						= 0;

		/**
			@brief �J�����f�[�^�X�V
			@author �t���`

			�J�����̃f�[�^���X�V���܂��B<BR>
			�e��s���o�E���f�B���O�{�b�N�X�Ȃǂ�<BR>
			���̊֐����Ăяo�����Ƃō쐬����܂��B
		*/
		virtual void Update( void )																						= 0;

		/**
			@brief �J������ϊ�
			@author �t���`

			@param Style	[in] �J�����ϊ��pCStyle

			Ctyle�f�[�^�Œ�`���ꂽ�ϊ�������<BR>
			�J�����ɓK�p���܂��B<BR>
			�J�����Ŏg�p�����͈̂ړ�/��]�ɂȂ�܂��B
		*/
		virtual void SetTransform( CStyle &Style )																		= 0;
	};
}

#endif // ___SELENE__ISCENECAMERA___


