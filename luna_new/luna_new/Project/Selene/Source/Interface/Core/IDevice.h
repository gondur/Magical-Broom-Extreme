

#ifndef ___SELENE__IDEVICE___
#define ___SELENE__IDEVICE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �f�o�C�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IDevice
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )												= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)												= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�N���A
			@author �t���`
			@param Color	[in] �N���A�Ɏg���F
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�����_�����O�^�[�Q�b�g���w�肳�ꂽ�F�ŃN���A�[���܂��B
		*/
		virtual Bool Clear( CColor Color = 0x00000000 )								= 0;

		/**
			@brief �[�x�o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�[�x�o�b�t�@���N���A���܂��B<BR>
			�[�x�o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearDepth( void )												= 0;

		/**
			@brief �X�e���V���o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�X�e���V���o�b�t�@���N���A���܂��B<BR>
			�X�e���V���o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearStencil( void )											= 0;

		/**
			@brief �[�x�X�e���V���o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�[�x�X�e���V���o�b�t�@���N���A���܂��B<BR>
			�[�x�X�e���V���o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearDepthStencil( void )										= 0;

		/**
			@brief �[���R���\�[����ʂɕ������`��
			@author �t���`
			@param pStr	[in] �����t������(printf�Ɠ�������)

			�R���\�[����printf()�Ǝ���������`�揈���ł��B<BR>
			�f�o�b�O�p�ɉ�ʂɕ�����`�悵�Ă��������ꍇ���ɗ��p���Ă��������B
		*/
		virtual void Printf( const wchar_t *pStr, ... )								= 0;

		/**
			@brief �[���R���\�[����ʂ��N���A
			@author �t���`

			�[���R���\�[����ʂ��N���A���܂��B
		*/
		virtual void Cls( void )													= 0;

		/**
			@brief �`��̈�V�U�����O
			@author �t���`
			@param IsEnable		[in] �V�U�����O��L���ɂ��邩�ۂ�
			@param Rect			[in] �`��̈�

			�w�肵���`��̈���ɂ��������_�����O����Ȃ��悤�ɂȂ�܂��B<BR>
			�r���[�|�[�g�ɂ͉e����^���܂���B
		*/
		virtual void SetScissor( Bool IsEnable, CRect2D<Sint32> Rect )			= 0;

		/**
			@brief IRender�C���^�[�t�F�C�X�擾
			@author �t���`
			@return IRender�C���^�[�t�F�C�X

			IRender�C���^�[�t�F�C�X���擾���܂��B<BR>
			��ʂւ̃����_�����O�����̑S�Ă����̃C���^�[�t�F�C�X��<BR>
			��čs����悤�ɂȂ��Ă��܂��B<BR>
			���̃C���^�[�t�F�C�X��1��IDevice�ɑ΂���1�������݂��܂���B<BR>
			�܂��s�v�ɂȂ���IRender�C���^�[�t�F�C�X�͕K��Release()���ĉ������B
		*/
		virtual IRender *CreateRender( void )										= 0;
	};
}


#endif // ___SELENE__IDEVICE___

