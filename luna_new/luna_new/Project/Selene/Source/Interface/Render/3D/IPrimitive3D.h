

#ifndef ___SELENE__IPRIMITIVE3D___
#define ___SELENE__IPRIMITIVE3D___


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
		@brief 3D�v���~�e�B�u�`��N���X
		@author �t���`

		�|���S���f�[�^�������ō��Ƃ��Ɏg�p���邽�߂̃N���X�ł��B<BR>
		�쐬���Ƀt���O�Ŏw�肵�����_�f�[�^�ƃC���f�b�N�X�f�[�^��<BR>
		�v���O�����Ńo�b�t�@�ɒǉ����Ă��������_�����O���܂��B<BR>
		���C�e�B���O��X�L�j���O�Ȃǂ̋@�\���T�|�[�g����Ă��܂����A<BR>
		�o���v�}�b�s���O�̓T�|�[�g����Ă��܂���B<BR>
	<BR>
		�܂����s�̃o�[�W�����ł͓����ŏ������Ă���V�F�[�_�[�ł���<BR>
		�����_�����O�����鎖���ł��܂���B<BR>
		���̐����͏C���\��ł��B
	*/
	class IPrimitive3D
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
		virtual Sint32 Rendering( void )										= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count )		= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count )	= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count )		= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count )		= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count )	= 0;

		/**
			@brief �C���f�b�N�X�f�[�^��ǉ�
			@author �t���`
			@param pIndex		[in] �C���f�b�N�X�f�[�^
			@param IndexCount	[in] �C���f�b�N�X��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�փC���f�b�N�X�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵���C���f�b�N�X�t�H�[�}�b�g�ɓK�������C���f�b�N�X�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DBase &Vtx, Uint32 Index )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DTexture &Vtx, Uint32 Index )		= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DLight &Vtx, Uint32 Index )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DBump &Vtx, Uint32 Index )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DAnimation &Vtx, Uint32 Index )		= 0;

		/**
			@brief ���_���擾
			@author �t���`
			@return �ǉ��v�����������_�̐�

			�ǉ��v�����s����SVertex3DBase���_�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Uint32 GetVertexCount( void )								= 0;

		/**
			@brief �C���f�b�N�X���擾
			@author �t���`
			@return �ǉ��v���������C���f�b�N�X�̐�

			�ǉ��v�����s�����C���f�b�N�X�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Uint32 GetIndexCount( void )								= 0;

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
			@brief �{�[�����ݒ�
			@author �t���`
			@param BoneCount	[in] �{�[����

			�����_�����O�Ɏg����{�[���̐���ݒ肵�܂��B
		*/
		virtual void SetBoneCount( Sint32 BoneCount )						= 0;

		/**
			@brief �I�t�Z�b�g�p�{�[���ݒ�
			@author �t���`
			@param No		[in] �{�[���ԍ�
			@param Matrix	[in] �I�t�Z�b�g�s��

			�w��ԍ��̃{�[���̐e����̃I�t�Z�b�g�p�̍s���ݒ肵�܂��B
		*/
		virtual void SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix )		= 0;

		/**
			@brief �g�����X�t�H�[���p�{�[���ݒ�
			@author �t���`
			@param No		[in] �{�[���ԍ�
			@param Matrix	[in] �g�����X�t�H�[���s��

			�w��ԍ��̃{�[���̃g�����X�t�H�[���p�̍s���ݒ肵�܂��B
		*/
		virtual void SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix )	= 0;

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

		/**
			@brief �X�y�L�����F�ݒ�
			@author �t���`
			@param Color	[in] �X�y�L�����̐F

			�X�y�L�����̐F��ݒ肵�܂��B
		*/
		virtual void SetSpecularColor( CColor Color )						= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param fRefractive		[in] �X�y�L�����̋��ܗ�(����20.0f)

			�}�e���A���̃X�y�L�����̋��ܗ���ݒ肵�܂�
		*/
		virtual void SetSpecularRefractive( Float fRefractive )				= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param fRoughly			[in] �X�y�L�����̑e��(����0.5f)

			�}�e���A���̃X�y�L�����̑e����ݒ肵�܂�
		*/
		virtual void SetSpecularRoughly( Float fRoughly )					= 0;
	};
}


#endif // ___SELENE__IPRIMITIVE3D___


