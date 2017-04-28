
#ifndef ___LUE_INPUT_H___
#define ___LUE_INPUT_H___

#include "LueBase.h"

//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//=============================================================================
// PROTOTYPE
//=============================================================================
/**
	@brief �L�[�{�b�h�̓��̓o�b�t�@���N���A
	@author �t���`

	�L�[�{�[�h�̏�񂪊i�[����Ă�����̓o�b�t�@���N���A���܂��B
*/
void LueInput_ClearKeyBuffer( void );

/**
	@brief �L�[�{�[�h���̓o�b�t�@�̎擾
	@author �t���`

	@retval 0		���͂Ȃ�
	@return 0�ȊO	�����ꂽ�L�[�̃L�[�R�[�h

	�L�[�{�[�h���̓o�b�t�@���̃f�[�^���P�Â��o���܂��B<BR>
	�o�b�t�@����ɂȂ������_�� LUE_VK_NONE ���Ԃ�܂��B
*/
eLueVirtualKey LueInput_GetKeyBuffer( void );

/**
	@brief �L�[�{�[�h���擾
	@author �t���`

	@param Key	[in] ���ׂ����L�[�̃L�[�R�[�h

	@retval LTRUE	������Ă���
	@retval LFALSE	������Ă��Ȃ�
*/
eLueBool LueInput_GetKeyData( eLueVirtualKey Key );

/**
	@brief �}�E�X���擾
	@author �t���`

	@return �}�E�X�f�[�^

	�}�E�X�̏����擾���܂��B
*/
LueMouseData LueInput_GetMouseData( void );

/**
	@brief �W���C�X�e�B�b�N���擾
	@author �t���`

	@param No	[in] �W���C�X�e�B�b�N�ԍ�

	@return �W���C�X�e�B�b�N�f�[�^

	�w��ڑ��ԍ��̃W���C�X�e�B�b�N�̃f�[�^���擾���܂��B<BR>
	�w��ڑ��ԍ��̃W���C�X�e�B�b�N���ڑ�����Ă��Ȃ��ꍇ��<BR>
	IsActive �����o�ϐ��� LFALSE ���ݒ肳��܂��B
*/
LueJoyStickData LueInput_GetJoystickData( int No );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_INPUT_H___
