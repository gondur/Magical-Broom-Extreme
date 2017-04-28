

#ifndef ___SELENE__IFILEMANAGER___
#define ___SELENE__IFILEMANAGER___


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
		@brief �t�@�C���V�[�N��`
		@author �t���`
	*/
	enum eSeekFlag
	{
		SEEK_FILE_CURRENT,					///< �J�����g�ʒu
		SEEK_FILE_START,					///< �擪�ʒu
		SEEK_FILE_END,						///< �I�[�ʒu
	};

	/**
		@brief �t�@�C���Ǘ��N���X
		@author �t���`
	*/
	class IFileManager
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
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																		= 0;

		/**
			@brief �t�@�C�����[�h�p�X�ݒ�
			@author �t���`
			@param Priority		[in] �����v���C�I���e�B
			@param pRootPath	[in] ���[�g�f�B���N�g��
			@param pPackFile	[in] �p�b�N�t�@�C����

			�t�@�C���̓ǂݍ��݂��s�����[�g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ�p�X����уp�b�N�t�@�C���͓���Ɉ����܂��B<BR>
			�܂�v���O�����̕ύX�Ȃ��o���ɂ܂����������悤�ɃA�N�Z�X�\�ł��B
		*/
		virtual void SetLoadPath( Uint32 Priority, const wchar_t *pRootPath, const wchar_t *pPackFile )		= 0;

		/**
			@brief �J�����g�f�B���N�g���ݒ�
			@author �t���`
			@param pCurrentDir	[in] �f�B���N�g����

			�t�@�C���������s���ۂ̃J�����g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ�f�B���N�g�������[�g�Ƃ��ăt�@�C���̌������s���܂��B
		*/
		virtual void SetCurrentDirectory( wchar_t *pCurrentDir )											= 0;

		/**
			@brief �t�@�C�����[�h
			@author �t���`
			@param pFile	[in] �t�@�C����
			@param ppData	[out] �t�@�C���f�[�^�i�[��
			@param pSize	[out] �t�@�C���T�C�Y�i�[��
			@retval true	����
			@retval false	���s

			�t�@�C�������[�h���܂��B<BR>
			SetLoadPath() �Ŏw�肳��Ă���[�t�H���_]��[�p�b�N�t�@�C��]��<BR>
			���Ƀt�@�C�����������܂��B
		*/
		virtual Bool Load( const wchar_t *pFile, void **ppData, Uint32 *pSize )								= 0;

		/**
			@brief �f�[�^���
			@author �t���`
			@param pData	[in] �f�[�^

			Load()�֐��Ŏ擾�����f�[�^�����������������܂��B<BR>
			���̊֐����g�������@�ȊO�ł̉���͊��ˑ����邽�߁A<BR>
			�������������Ȃ��\��������܂��B
		*/
		virtual void Free( void *pData )																	= 0;

		/**
			@brief �t�@�C���I�[�v��
			@author �t���`
			@param pFile		[in] �t�@�C����
			@retval NULL		���s
			@retval NULL�ȊO	�t�@�C���C���^�[�t�F�C�X

			���\�[�X�t�@�C�����I�[�v�����܂��B<BR>
			�����ł������\�[�X�t�@�C���̓Q�[���Ŏg����f�[�^�S�ʂ̎��ł��B<BR>
			�܂�p�b�N�t�@�C���̓��e�A����у��[�g�f�B���N�g���ȉ��̃f�[�^�ł��B<BR>
			SetLoadPath() �Ŏw�肳��Ă���[�t�H���_]��[�p�b�N�t�@�C��]��<BR>
			���Ƀt�@�C�����������܂��B<BR>
			�I�[�v�������t�@�C���̓p�b�N�t�@�C���ł����Ă��A<BR>
			�ʏ�̃t�@�C���Ɠ����悤�ɃA�N�Z�X���邱�Ƃ��o���܂��B<BR>
			�܂����̊֐�����擾����IFIle�C���^�[�t�F�C�X�͓ǂݎ���p�ł��B<BR>
			�g�p���I������IFile�C���^�[�t�F�C�X��Release()�ŉ�����Ă��������B
		*/
		virtual IResourceFile *FileOpen( const wchar_t *pFile )												= 0;
	};
}

#endif // ___SELENE__IFILEMANAGER___

