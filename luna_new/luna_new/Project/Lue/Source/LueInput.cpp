

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueInput.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IMouse *Lue_GetMouse( void );
extern IKeyboard *Lue_GetKeyboard( void );


//------------------------------------------------------------------------------------------------
/**
	@brief �L�[�{�b�h�̓��̓o�b�t�@���N���A
	@author �t���`

	�L�[�{�[�h�̏�񂪊i�[����Ă�����̓o�b�t�@���N���A���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueInput_ClearKeyBuffer( void )
{
	IKeyboard *pKeyboard = Lue_GetKeyboard();

	pKeyboard->ClearKeyBuffer();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �L�[�{�[�h���̓o�b�t�@�̎擾
	@author �t���`

	@retval 0		���͂Ȃ�
	@return 0�ȊO	�����ꂽ�L�[�̃L�[�R�[�h

	�L�[�{�[�h���̓o�b�t�@���̃f�[�^���P�Â��o���܂��B<BR>
	�o�b�t�@����ɂȂ������_�� LUE_VK_NONE ���Ԃ�܂��B
*/
//------------------------------------------------------------------------------------------------
eLueVirtualKey LueInput_GetKeyBuffer( void )
{
	IKeyboard *pKeyboard = Lue_GetKeyboard();

	return (eLueVirtualKey)pKeyboard->GetKeyBuffer();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �L�[�{�[�h���擾
	@author �t���`

	@param Key	[in] ���ׂ����L�[�̃L�[�R�[�h

	@retval LTRUE	������Ă���
	@retval LFALSE	������Ă��Ȃ�
*/
//------------------------------------------------------------------------------------------------
eLueBool LueInput_GetKeyData( eLueVirtualKey Key )
{
	IKeyboard *pKeyboard = Lue_GetKeyboard();

	return pKeyboard->GetKeyData( (eVirtualKeyCode)Key ) ? LTRUE : LFALSE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �}�E�X���擾
	@author �t���`

	@return �}�E�X�f�[�^

	�}�E�X�̏����擾���܂��B
*/
//------------------------------------------------------------------------------------------------
LueMouseData LueInput_GetMouseData( void )
{
	IMouse *pMouse = Lue_GetMouse();

	LueMouseData Mouse = {
		pMouse->GetPosX(),
		pMouse->GetPosY(),
		pMouse->GetPosW(),
		pMouse->GetMoveX(),
		pMouse->GetMoveY(),
		pMouse->GetClickL(),
		pMouse->GetClickR(),
		pMouse->GetClickW(),
		pMouse->GetDoubleClickL(),
		pMouse->GetDoubleClickR(),
		pMouse->GetDoubleClickW(),
		(eLueMouseState)pMouse->GetStateL(),
		(eLueMouseState)pMouse->GetStateR(),
		(eLueMouseState)pMouse->GetStateW(),
	};

	return Mouse;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �W���C�X�e�B�b�N���擾
	@author �t���`

	@param No	[in] �W���C�X�e�B�b�N�ԍ�

	@return �W���C�X�e�B�b�N�f�[�^

	�w��ڑ��ԍ��̃W���C�X�e�B�b�N�̃f�[�^���擾���܂��B<BR>
	�w��ڑ��ԍ��̃W���C�X�e�B�b�N���ڑ�����Ă��Ȃ��ꍇ��<BR>
	IsActive �����o�ϐ��� LFALSE ���ݒ肳��܂��B
*/
//------------------------------------------------------------------------------------------------
LueJoyStickData LueInput_GetJoystickData( int No )
{
	LueJoyStickData DstJoy = { LFALSE };
/*
	SJoystickData SrcJoy;
	if ( CInput::GetJoystickData( No, &SrcJoy ) )
	{
		DstJoy.IsActive		= LTRUE;
		DstJoy.Px			= SrcJoy.Px;
		DstJoy.Py			= SrcJoy.Py;
		DstJoy.Pz			= SrcJoy.Pz;
		DstJoy.Rx			= SrcJoy.Rx;
		DstJoy.Ry			= SrcJoy.Ry;
		DstJoy.Rz			= SrcJoy.Rz;
		DstJoy.Vx			= SrcJoy.Vx;
		DstJoy.Vy			= SrcJoy.Vy;
		DstJoy.Vz			= SrcJoy.Vz;
		DstJoy.VRx			= SrcJoy.VRx;
		DstJoy.VRy			= SrcJoy.VRy;
		DstJoy.VRz			= SrcJoy.VRz;
		DstJoy.Ax			= SrcJoy.Ax;
		DstJoy.Ay			= SrcJoy.Ay;
		DstJoy.Az			= SrcJoy.Az;
		DstJoy.ARx			= SrcJoy.ARx;
		DstJoy.ARy			= SrcJoy.ARy;
		DstJoy.ARz			= SrcJoy.ARz;
		DstJoy.Fx			= SrcJoy.Fx;
		DstJoy.Fy			= SrcJoy.Fy;
		DstJoy.Fz			= SrcJoy.Fz;
		DstJoy.FRx			= SrcJoy.FRx;
		DstJoy.FRy			= SrcJoy.FRy;
		DstJoy.FRz			= SrcJoy.FRz;
		DstJoy.Slider[0]	= SrcJoy.Slider[0];
		DstJoy.Slider[1]	= SrcJoy.Slider[1];
		DstJoy.Pov[0]		= SrcJoy.Pov[0];
		DstJoy.Pov[1]		= SrcJoy.Pov[1];
		DstJoy.Pov[2]		= SrcJoy.Pov[2];
		DstJoy.Pov[3]		= SrcJoy.Pov[3];
		for ( Sint32 i = 0; i < LPAD_BUTTON_MAX; i++ )
		{
			DstJoy.Button[i] = SrcJoy.Button[i];
		}
	}
*/
	return DstJoy;
}


} // extern "C"

