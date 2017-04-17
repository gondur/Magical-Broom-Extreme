//======================================================================================
//======================================================================================
//
//
//			���̓f�o�C�X�Ǘ�
//
//
//
//======================================================================================
//======================================================================================


//======================================================================================
// INCLUDE
//======================================================================================
#include "Io.h"


//======================================================================================
//	class menber
//======================================================================================
unsigned char IO::State[3];


//======================================================================================
//
//	�L�[���X�V
//
//
//======================================================================================
void IO::RefreshKeyState( void )
{
	static unsigned char OldWork, NewWork;

	OldWork = NewWork;
	NewWork = 0x00;

	//-------------------------------------------------
	// �L�[�{�[�h
	//-------------------------------------------------
	// �J�[�\���L�[
	if ( LunaInput::GetKeyData( DIK_UP      ) ) NewWork |= KEY_UP;
	if ( LunaInput::GetKeyData( DIK_DOWN    ) ) NewWork |= KEY_DOWN;
	if ( LunaInput::GetKeyData( DIK_LEFT    ) ) NewWork |= KEY_LEFT;
	if ( LunaInput::GetKeyData( DIK_RIGHT   ) ) NewWork |= KEY_RIGHT;
	// �e���L�[
	if ( LunaInput::GetKeyData( DIK_NUMPAD8 ) ) NewWork |= KEY_UP;
	if ( LunaInput::GetKeyData( DIK_NUMPAD2 ) ) NewWork |= KEY_DOWN;
	if ( LunaInput::GetKeyData( DIK_NUMPAD4 ) ) NewWork |= KEY_LEFT;
	if ( LunaInput::GetKeyData( DIK_NUMPAD6 ) ) NewWork |= KEY_RIGHT;
	// �{�^��
	if ( LunaInput::GetKeyData( DIK_Z       ) ) NewWork |= KEY_01;
	if ( LunaInput::GetKeyData( DIK_X       ) ) NewWork |= KEY_02;
	if ( LunaInput::GetKeyData( DIK_C       ) ) NewWork |= KEY_03;
	if ( LunaInput::GetKeyData( DIK_V       ) ) NewWork |= KEY_04;

	//-------------------------------------------------
	// �W���C�X�e�B�b�N
	//-------------------------------------------------
	// �W���C�X�e�B�b�N�o�b�t�@��M
	LPJOYSTICKDATA joy = LunaInput::GetJoystickData( 0 );

	// �ڑ����̂Ƃ�
	if ( joy != NULL )
	{
		if ( joy->Px > +1<<15 ) NewWork |= KEY_RIGHT;
		if ( joy->Px < -1<<15 ) NewWork |= KEY_LEFT;
		if ( joy->Py > +1<<15 ) NewWork |= KEY_DOWN;
		if ( joy->Py < -1<<15 ) NewWork |= KEY_UP;
		if ( joy->Button[0]  ) NewWork |= KEY_01;
		if ( joy->Button[1]  ) NewWork |= KEY_02;
		if ( joy->Button[2]  ) NewWork |= KEY_03;
		if ( joy->Button[3]  ) NewWork |= KEY_04;
	}

	//-------------------------------------------------
	// ��Ԏ擾
	//-------------------------------------------------
	State[KEYSTATE_PULL] = (unsigned char)( ( OldWork ) & (~NewWork ) );
	State[KEYSTATE_PUSH] = (unsigned char)( (~OldWork ) & ( NewWork ) );
	State[KEYSTATE_HOLD] = (unsigned char)( ( OldWork ) & ( NewWork ) );
}

//======================================================================================
//
//	�L�[���擾
//
//
//======================================================================================
bool IO::GetKey( eKeyState state, long key )
{
	return ( State[state] & key ) == key;
}