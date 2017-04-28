

#ifndef ___SELENE__ITEXTURE___
#define ___SELENE__ITEXTURE___


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
		@brief �e�N�X�`���C���^�[�t�F�C�X
		@author �t���`

		�e�N�X�`���𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B<BR>
		IRender�C���^�[�t�F�C�X����擾�ł��܂��B
	*/
	class ITexture
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																		= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																		= 0;

		/**
			@brief ��`�R�s�[
			@author �t���`
			@param pDstRect		[in] �]����e�N�X�`���̋�`
			@param pSrcTex		[in] �]�����e�N�X�`��
			@param pSrcRect		[in] �]�����e�N�X�`���̋�`
			@param IsUvToTexel	[in] �e�N�X�`���T�C�Y�ƃC���[�W�T�C�Y����v���Ȃ��ꍇ�̕␳�����邩�ۂ�
			@retval true	����
			@retval false	���s

			�e�N�X�`�����m�̊g��k���R�s�[���s���܂��B<BR>
			�e�N�X�`���ԂŃt�H�[�}�b�g���قȂ�ꍇ��<BR>
			�n�[�h�E�F�A�̃t�H�[�}�b�g�ϊ��̃T�|�[�g���Ȃ���<BR>
			���̊֐��͎��s���܂��B<BR>
			�܂����̃R�s�[�����ɂ͂������̐��������݂��܂��B<BR>
			�E�ʏ�e�N�X�`������ʏ�e�N�X�`���̊g��k���R�s�[�͂ł��܂���B<BR>
			�E�o�b�N�o�b�t�@����ʏ�e�N�X�`���ւ̃R�s�[�͂ł��܂���B
		*/
		virtual Bool Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel = false )	= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g���_�E�����[�h
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�T�[�t�F�C�X<BR>
			���݂̃����_�����O�^�[�Q�b�g�̓��e���R�s�[���܂��B
		*/
		virtual Bool DownloadRenderTarget( void )															= 0;

		/**
			@brief �e�N�X�`���X�V
			@author �t���`

			�o�b�N�A�b�v�p�V�X�e���������}�e���A���̓��e��<BR>
			VRAM��̃}�e���A���֓]�����܂��B
		*/
		virtual void UpdateTexture( void )																	= 0;

		/**
			@brief �摜�t�@�C���Ƃ��ĕۑ�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@retval false	���s
			@retval true	����

			�e�N�X�`���̓��e��TGA�摜�t�@�C���Ƃ��ĕۑ����܂��B
		*/
		virtual Bool SaveToTGA( const wchar_t *pFileName )													= 0;

		/**
			@brief ���e�N�X�`���T�C�Y�擾
			@author �t���`
			@return �e�N�X�`���̎��T�C�Y

			�e�N�X�`���̃T�C�Y���擾���܂��B<BR>
			�Q�̗ݏ�łȂ��e�N�X�`�����쐬�����ۂ�<BR>
			�f�o�C�X�����̃T�C�Y�����ہ[�Ƃ��Ă��Ȃ��Ƃ���<BR>
			����ł���傫���̂Q�̗ݏ�̃T�C�Y�ɂȂ��Ă��܂��B
		*/
		virtual CPoint2D<Uint32> GetSize( void )															= 0;
	};
}

#endif // ___SELENE__ITEXTURE___


