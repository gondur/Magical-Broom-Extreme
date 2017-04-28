

#ifndef ___SELENE__ISURFACE___
#define ___SELENE__ISURFACE___


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
		@brief �}�e���A���C���^�[�t�F�C�X
		@author �t���`

		�T�[�t�F�C�X�t�F�C�X���삷�邽�߂̃C���^�[�t�F�C�X�ł��B<BR>
		IRender�C���^�[�t�F�C�X����擾�ł��܂��B
	*/
	class ISurface
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
		virtual Uint32 Release( void )											= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )											= 0;

		/**
			@brief �o�b�N�o�b�t�@�ɃR�s�[
			@author �t���`
			@retval true	����
			@retval false	���s

			�T�[�t�F�C�X�t�F�C�X�o�b�N�o�b�t�@�ɃR�s�[���܂��B<BR>
			�������[�x�X�e���V���}�e���A����t�H�[�}�b�g�ϊ��Ƀn�[�h�E�F�A��<BR>
			�Ή����Ă��Ȃ��t�H�[�}�b�g�̃}�e���A���ł͎��s���܂��B
		*/
		virtual Bool CopyToBackBuffer( void )									= 0;

		/**
			@brief �}�e���A���̃R�s�[
			@author �t���`
			@param pDstRect		[in] �]����}�e���A���̋�`
			@param pSrc			[in] �]�����}�e���A��
			@param pSrcRect		[in] �]�����}�e���A���̋�`
			@retval true	����
			@retval false	���s

			�}�e���A�����m�̊g��k���R�s�[���s���܂��B<BR>
			�}�e���A���ԂŃt�H�[�}�b�g���قȂ�ꍇ��<BR>
			�n�[�h�E�F�A�̃t�H�[�}�b�g�ϊ��̃T�|�[�g���Ȃ���<BR>
			���̊֐��͎��s���܂��B<BR>
			�܂����̃R�s�[�����ɂ͂������̐��������݂��܂��B<BR>
			�E�ʏ�}�e���A������ʏ�}�e���A���̊g��k���R�s�[�͂ł��܂���B<BR>
			�E�o�b�N�o�b�t�@����ʏ�}�e���A���ւ̃R�s�[�͂ł��܂���B
		*/
		virtual Bool Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )		= 0;
	};
}

#endif // ___SELENE__ISURFACE___


