
#ifndef ___LUE_SOUND_H___
#define ___LUE_SOUND_H___


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
	@brief �t�@�C������T�E���h��ǂݍ��݁A<BR>
	���̃T�E���h�̃n���h�����擾���܂��B
	@author �t���`

	@param pFileName	[in] �t�@�C����
	@param IsAllActive	[in] LTRUE �ɂ���ƃE�B���h�E����A�N�e�B�u�ł���~���Ȃ�

	@return ���g�p�̃T�E���h�n���h��

	�T�E���h�t�@�C����ǂݍ��݁A���̃T�E���h�̑���p�̃n���h�����擾���܂��B<BR>
	�擾�����T�E���h�͕s�v�ɂȂ����������ĉ������B
*/
LUE_HANDLE LueSound_CreateFromFile( const char *pFileName, eLueBool IsAllActive );

/**
	@brief �T�E���h��������܂��B
	@author �t���`

	@param Handle	[in] �T�E���h�n���h��

	�ǂݍ��񂾃T�E���h�����������������܂��B
*/
void LueSound_Release( LUE_HANDLE Handle );

/**
	@brief �T�E���h���Đ��J�n
	@author �t���`

	@param Handle	[in] �T�E���h�n���h��

	�ǂݍ��񂾃T�E���h�����������������܂��B
*/
void LueSound_Play( LUE_HANDLE Handle );

/**
	@brief �T�E���h�����[�v�Đ��J�n
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��
	@param LoopCount	[in] ���[�v��<BR>�������[�v�̏ꍇ�� SOUND_LOOP_INFINITY ���w��B
	@param LoopSample	[in] ���[�v�J�n�ʒu�i�T���v�����O���Ŏw��j

	�T�E���h�̃��[�v�Đ����s���܂��B
*/
void LueSound_Loop( LUE_HANDLE Handle, unsigned int LoopCount, unsigned int LoopSample );

/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��

	�Đ����̃T�E���h���~���܂��B
*/
void LueSound_Stop( LUE_HANDLE Handle );

/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��

	�Đ����̃T�E���h���~���܂��B
*/
void LueSound_Pause( LUE_HANDLE Handle );

/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��
	@param fParam		[in] �{�����[���l(+0�`+100)

	�Đ����̃T�E���h���~���܂��B
*/
void LueSound_SetVolume( LUE_HANDLE Handle, float fParam );

/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��
	@param fParam		[in] �p���l(-100�`+100)

	�Đ����̃T�E���h���~���܂��B
*/
void LueSound_SetPan( LUE_HANDLE Handle, float fParam );

/**
	@brief �T�E���h���Đ����ł��邩�`�F�b�N
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��

	@retval true		�Đ����i�ꎞ��~�܂ށj
	@retval false		��~��

	�Đ����̃T�E���h�ł��邩�ǂ����𒲂ׂ܂��B
*/
eLueBool LueSound_IsPlay( LUE_HANDLE Handle );


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_SOUND_H___
