

#ifndef ___SELENE__IRESOURCEFILE___
#define ___SELENE__IRESOURCEFILE___


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
		@brief ���\�[�X�t�@�C������
		@author �t���`
	*/
	class IResourceFile
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
		virtual Uint32 Release( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)								= 0;

		/**
			@brief �t�@�C���ւ̓ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �ǂݍ��݃f�[�^�T�C�Y
			@return ���ۂɏ������񂾃o�C�g��

			�t�@�C���ւ̓ǂݍ��݂��s���܂��B<BR>
			�ǂݍ��݉\�ȃt�@�C���̓C���^�[�t�F�C�X��������<BR>
			FILE_OPEN_TYPE_READ��FILE_OPEN_TYPE_READ_WRITE�t���O��<BR>
			�w�肷��K�v������܂��B
		*/
		virtual Uint32 Read( void *pData, Uint32 Size )				= 0;

		/**
			@brief �t�@�C�����擾
			@author �t���`
			@return �t�@�C�����̐擪�A�h���X

			�t�@�C�����̐擪�A�h���X���擾���܂��B
		*/
		virtual const wchar_t *GetNamePointer( void )				= 0;

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y

			�t�@�C���̃T�C�Y���擾���܂��B
		*/
		virtual Uint32 GetFileSize( void )							= 0;

		/**
			@brief �t�@�C���|�C���^�[�ʒu�擾
			@author �t���`
			@return �t�@�C���|�C���^�[�̈ʒu

			���݂̃t�@�C���|�C���^�̈ʒu���擾���܂��B
		*/
		virtual Uint32 GetFilePosition( void )						= 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̐擪����Offset�o�C�g�ړ����܂��B
		*/
		virtual Uint32 SeekStart( Sint32 Offset )					= 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̏I�[����Offset�o�C�g�ړ����܂��B
		*/
		virtual Uint32 SeekEnd( Sint32 Offset )						= 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu�����݂̈ʒu����Offset�o�C�g�ړ����܂��B
		*/
		virtual Uint32 Seek( Sint32 Offset )						= 0;
	};
}

#endif // ___SELENE__IRESOURCEFILE___

