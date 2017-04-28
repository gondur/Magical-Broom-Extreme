
#ifndef ___LUE_CORE_H___
#define ___LUE_CORE_H___


//=============================================================================
// INCLUDE
//=============================================================================
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
	@brief Lue�V�X�e���̏��������s���܂�
	@author �t���`

	@param pAppName		[in] �A�v���P�[�V������
	@param ScreenW		[in] ��ʉ���
	@param ScreenH		[in] ��ʏc��
	@param FrameRate	[in] �t���[�����[�g
	@param IsWindowMode	[in] �E�B���h�E���[�h�ŋN�����邩�ǂ���
	@param Type			[in] �g�p����API�i���݂� LAPI_TYPE_DIRECTX9 �Œ�j

	@retval LTRUE	����������
	@retval LFALSE	���������s

	Lue�V�X�e���̏������������s���܂��B<BR>
	���̊֐������������i�K�ł��ׂĂ�Lue�n�̊֐����g�����Ƃ��\�ɂȂ�܂��B
*/
eLueBool Lue_Initialize( const char *pAppName, unsigned int ScreenW, unsigned int ScreenH, eLueFrameRata FrameRate, eLueBool IsWindowMode, eLueAPIType Type );

/**
	@brief Lue�V�X�e���̏I��
	@author �t���`

	Lue�V�X�e�������ׂĉ�����܂��B<BR>
	���̊֐����Ă΂ꂽ���Lue�n�̊֐����Ăяo�����Ƃ͋֎~����Ă��܂��B
*/
void Lue_Finalize( void );

/**
	@brief Lue�V�X�e���̃��C������
	@author �t���`

	@param IsActive	[in] LTRUE �̎��A�t�H�[�J�X�������Ă����삵������B

	@retval LTRUE	�A�v���P�[�V�������쒆
	@retval LFALSE	�A�v���P�[�V������~

	Lue�V�X�e���̃��C���������s���܂��B<BR>
	���t���[���Ăяo���悤�ɂ��Ă��������B<BR>
	�܂��Ԃ�l��LFALSE�̂Ƃ��͒����Ƀ��C�����[�v���甲���ĉ������B
*/
eLueBool Lue_Run( eLueBool IsActive );

/**
	@brief �o�[�W����������擾
	@author �t���`

	@param pStr		[out] �o�[�W����������i�[��
	@param Size		[in] pStr�̃o�b�t�@�T�C�Y

	Lue�̃o�[�W�����𕶎���Ŏ擾���܂��B<BR>
	���̊֐����Ăяo�����Ƃ� DLL �̃o�[�W�������擾���邱�Ƃ��\�ł��B
*/
void Lue_GetVersionString( char *pStr, unsigned int Size );

/**
	@brief �o�[�W�����ԍ��擾
	@author �t���`

	@return �o�[�W�����ԍ�

	Lue�̃o�[�W�����𐔒l�Ŏ擾���܂��B<BR>
	���16Bit�Ƀ��W���[�o�[�W�����A����16Bit�Ƀ}�C�i�[�o�[�W�������i�[����Ă��܂��B
*/
unsigned int Lue_GetVersionNumber( void );

/**
	@brief OS�N������̎��Ԏ擾
	@author �t���`

	@return 1/1000�b�P�ʂ̎���

	OS���N�����Ă���̎��Ԃ��擾���܂��B<BR>
	32Bit�ϐ��Ȃ̂Ŗ�48����1������0�ɖ߂��Ă��܂��܂��B
*/
unsigned int Lue_GetTime( void );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_CORE_H___
