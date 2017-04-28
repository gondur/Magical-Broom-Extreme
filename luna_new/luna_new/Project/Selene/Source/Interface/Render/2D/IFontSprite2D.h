

#ifndef ___SELENE__IFONTSPRITE2D___
#define ___SELENE__IFONTSPRITE2D___


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
		@brief �t�H���g�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IFontSprite2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																			= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																			= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																			= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																				= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																				= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																			= 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )						= 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )						= 0;

		/**
			@brief �����`��
			@author �t���`
			@param Chara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F

			�w��ʒu�ɕ�����`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawChara( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color )						= 0;

		/**
			@brief ��]�t�������`��
			@author �t���`
			@param Chara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			�w��ʒu�ɕ�������]�t���ŕ`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawCharaRotate( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color, Sint32 Angle )	= 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@return		�`�抮�����̍��W

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual CPoint2D<Sint32> GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos )					= 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@return		�`�抮�����̍��W

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual CPoint2D<Sint32> GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos )					= 0;
	};
}

#endif // ___SELENE__IFONTSPRITE2D___

