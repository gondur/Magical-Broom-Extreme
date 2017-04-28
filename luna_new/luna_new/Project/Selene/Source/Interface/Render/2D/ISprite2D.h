

#ifndef ___SELENE_ISPRITE2D___
#define ___SELENE_ISPRITE2D___


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
		@brief 2D�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class ISprite2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																													= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																														= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )																				= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief �l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F

			�ł��P���ȃX�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color )														= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F
			@param Angle		[in] 1��65536�Ƃ�����]�p�x

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle )									= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src )				= 0;

		/**
			@brief ���ˏ�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���S�Ɍ������ăt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )													= 0;

		/**
			@brief �~���]�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���v���Ƀt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )												= 0;
	};
}


#endif // ___SELENE_ISPRITE2D___

