

#ifndef ___SELENE__SYSTEM___
#define ___SELENE__SYSTEM___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Core/CCore.h"
#include "Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace System
{
	/**
		@brief �V�X�e��������
		@author �t���`
		@retval true	����
		@retval false	���s

		Selene�V�X�e���̏��������s���܂��B
	*/
	SELENE_DLL_API Bool Initialize( void );

	/**
		@brief �V�X�e���I��
		@author �t���`

		Selene�V�X�e���̏I�������܂��B
	*/
	SELENE_DLL_API void Finalize( void );

	/**
		@brief ���d�N���u���b�N
		@author �t���`
		@param pApplicationName	[in] �A�v���P�[�V������
		@retval false	���ɓ����̃A�v���P�[�V�������N�����Ă���
		@retval true	�����̃A�v���P�[�V�����͑��݂��Ȃ�

		�Ԃ�lfalse���ɃA�v���P�[�V�������I�������邱�Ƃ�<BR>
		���d�N����h�~���邱�Ƃ��ł��܂��B
	*/
	SELENE_DLL_API Bool BlockDualBoot( const wchar_t *pApplicationName );

	/**
		@brief SSE2�T�|�[�g�L��
		@author �t���`
		@retval false	SSE2���T�|�[�g���Ă��Ȃ�
		@retval true	SSE2���T�|�[�g���Ă���

		SSE2���T�|�[�g���Ă��邩�ǂ����𒲂ׂ܂��B
	*/
	SELENE_DLL_API Bool IsSuportSSE( void );

	/**
		@brief �J�����g�f�B���N�g�����Z�b�g
		@author �t���`

		�J�����g�f�B���N�g�����A�v���P�[�V�����̎��s�t�H���_�ɐݒ肵�܂��B
	*/
	SELENE_DLL_API void ResetCurrentDirectory( void );

	/**
		@brief �f�B���N�g������
		@author �t���`
		@param pPath	[in] �t�H���_�p�X

		�w��p�X�փf�B���N�g���𐶐����܂��B<BR>
		�r���̃t�H���_�����݂��Ȃ��ꍇ�A�S�Ă̊K�w�ɑ΂��ăt�H���_���쐬���Ă����܂��B
	*/
	SELENE_DLL_API void CreateDirectory( const wchar_t *pPath );

	/**
		@brief Core�̎擾
		@author �t���`
		@return ICore�C���^�[�t�F�C�X

		�E�B���h�E���Ǘ�����ICore�N���X�𐶐�/�擾���܂��B<BR>
		���݁A�P��ICore���������ł��܂���B
	*/
	SELENE_DLL_API ICore *CreateCore( void );
}
}


#endif // ___SELENE__SYSTEM___

