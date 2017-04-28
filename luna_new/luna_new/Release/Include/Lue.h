//==============================================================================//
//                         DirectX9�p�ȈՃ��C�u���� Lue                         //
//==============================================================================//
//                                                                              //
//    �ŐV�ł̒u���Ă���URL                                                     //
//                                                                              //
//    TWINTAIL LOVERS.                                                          //
//      http://www.twin-tail.jp/                                                //
//                                                                              //
//    ���ⓙ�����ꏊ                                                            //
//      TWINTAIL LOVERS.���̌f����                                              //
//                                                                              //
//   DirectX Library 'Lue'                                                      //
//   Copyright (C) 2006 �t���`                                                  //
//   All rights reserved.                                                       //
//                                                                              //
//==============================================================================//


#ifndef ___LUE_H___
#define ___LUE_H___

#include <windows.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LPAD_BUTTON_MAX			16						///< �p�b�h�Ŏg�p�\�ȃ{�^����
#define INVALID_LUE_HANDLE		0xFFFFFFFF				///< �����ȃn���h��
#define SOUND_LOOP_INFINITY		0xFFFFFFFF				///< �T�E���h�������[�v�w��
#define LUE_ANGLE_MAX			(1 << 16)				///< Lue�Ŏg�p�����p�x�̍ő�l
#define LUE_ANGLE_MASK			(LUE_ANGLE_MAX - 1)		///< �p�x�ɑ΂��Ẵ}�X�N�l

#define LUE_COLOR(a,r,g,b)	(	(((unsigned int)(a))<<24) |\
								(((unsigned int)(r))<<16) |\
								(((unsigned int)(g))<< 8) |\
								(((unsigned int)(b))<< 0)	)		///< �F�쐬

#define LUE_RGB(r,g,b)			LUE_COLOR(255,r,g,b)				///< �F�쐬
#define LUE_ARGB(a,r,g,b)		LUE_COLOR(a,r,g,b)					///< �F�쐬
#define LUE_A(a)				LUE_COLOR(a,255,255,255)			///< �F�쐬
#define LUE_BRIGHT(c)			LUE_COLOR(255,c,c,c)				///< �F�쐬

typedef void			*LUE_FILEPTR;		///< �t�@�C���|�C���^
typedef unsigned int	LUE_HANDLE;			///< �n���h��

/**
	@brief �t���[�����[�g��`
	@author �t���`
*/
typedef enum eLueFrameRata
{
	LFRAME_RATE_60,					///< 1/60�b��
	LFRAME_RATE_30,					///< 1/30�b��
	LFRAME_RATE_20,					///< 1/20�b��
	LFRAME_RATE_15,					///< 1/15�b��
	LFRAME_RATE_VSYNC,				///< Vsync�ˑ�
}
eLueFrameRata;

/**
	@brief ���ʃt���O
	@author �t���`
*/
typedef enum eLueBool
{
	LFALSE,				///< ON  or TRUE
	LTRUE,				///< OFF or FALSE
}
eLueBool;

/**
	@brief �`�惂�[�h
	@author �t���`
*/
typedef enum eLueDrawMode
{
	LDRAW_MODE_NORMAL,					///< �ʏ�`��
	LDRAW_MODE_BLEND,					///< �������`��
	LDRAW_MODE_ADD,						///< ���Z�`��
	LDRAW_MODE_ADD_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
	LDRAW_MODE_SUB,						///< ���Z�`��i�A���t�@�l�����j
	LDRAW_MODE_SUB_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
	LDRAW_MODE_MULTIPLE,				///< ��Z�`��
	LDRAW_MODE_SCREEN,					///< �X�N���[���`��
}
eLueDrawMode;

/**
	@brief �t�@�C���V�[�N��ʒu
	@author �t���`
*/
typedef enum eLueSeek
{
	LSEEK_FILE_CURRENT,			///< ���݈ʒu
	LSEEK_FILE_START,			///< �擪�ʒu
	LSEEK_FILE_END,				///< �I�[�ʒu
}
eLueSeek;

/**
	@brief �W���C�X�e�B�b�N�{�^�����
	@author �t���`
*/
typedef enum eLueKeyState
{
	LKEY_STATE_FREE,			///< ������Ă��Ȃ�
	LKEY_STATE_PULL,			///< �������u��
	LKEY_STATE_PUSH,			///< �������u��
	LKEY_STATE_HOLD,			///< ���������Ă�����
}
eLueKeyState;

/**
	@brief �}�E�X�{�^�����
	@author �t���`
*/
typedef enum eLueMouseState
{
	LMOUSE_FREE,				///< ������Ă��Ȃ�
	LMOUSE_PULL,				///< �������u��
	LMOUSE_PUSH,				///< �������u��
	LMOUSE_HOLD,				///< ���������Ă�����
}
eLueMouseState;

/**
	@brief �g�pAPI���
	@author �t���`
*/
typedef enum eLueAPIType
{
	LAPI_TYPE_DIRECTX9,			///< DirectX9���g��
}
eLueAPIType;

/**
	@brief �L�[�R�[�h
	@author �t���`
*/
typedef enum eLueVirtualKey
{
	LUE_VK_ESCAPE          = 0x01,
	LUE_VK_1               = 0x02,
	LUE_VK_2               = 0x03,
	LUE_VK_3               = 0x04,
	LUE_VK_4               = 0x05,
	LUE_VK_5               = 0x06,
	LUE_VK_6               = 0x07,
	LUE_VK_7               = 0x08,
	LUE_VK_8               = 0x09,
	LUE_VK_9               = 0x0A,
	LUE_VK_0               = 0x0B,
	LUE_VK_MINUS           = 0x0C,
	LUE_VK_EQUALS          = 0x0D,
	LUE_VK_BACK            = 0x0E,
	LUE_VK_TAB             = 0x0F,
	LUE_VK_Q               = 0x10,
	LUE_VK_W               = 0x11,
	LUE_VK_E               = 0x12,
	LUE_VK_R               = 0x13,
	LUE_VK_T               = 0x14,
	LUE_VK_Y               = 0x15,
	LUE_VK_U               = 0x16,
	LUE_VK_I               = 0x17,
	LUE_VK_O               = 0x18,
	LUE_VK_P               = 0x19,
	LUE_VK_LBRACKET        = 0x1A,
	LUE_VK_RBRACKET        = 0x1B,
	LUE_VK_RETURN          = 0x1C,
	LUE_VK_LCONTROL        = 0x1D,
	LUE_VK_A               = 0x1E,
	LUE_VK_S               = 0x1F,
	LUE_VK_D               = 0x20,
	LUE_VK_F               = 0x21,
	LUE_VK_G               = 0x22,
	LUE_VK_H               = 0x23,
	LUE_VK_J               = 0x24,
	LUE_VK_K               = 0x25,
	LUE_VK_L               = 0x26,
	LUE_VK_SEMICOLON       = 0x27,
	LUE_VK_APOSTROPHE      = 0x28,
	LUE_VK_GRAVE           = 0x29,
	LUE_VK_LSHIFT          = 0x2A,
	LUE_VK_BACKSLASH       = 0x2B,
	LUE_VK_Z               = 0x2C,
	LUE_VK_X               = 0x2D,
	LUE_VK_C               = 0x2E,
	LUE_VK_V               = 0x2F,
	LUE_VK_B               = 0x30,
	LUE_VK_N               = 0x31,
	LUE_VK_M               = 0x32,
	LUE_VK_COMMA           = 0x33,
	LUE_VK_PERIOD          = 0x34,
	LUE_VK_SLASH           = 0x35,
	LUE_VK_RSHIFT          = 0x36,
	LUE_VK_MULTIPLY        = 0x37,
	LUE_VK_LMENU           = 0x38,
	LUE_VK_SPACE           = 0x39,
	LUE_VK_CAPITAL         = 0x3A,
	LUE_VK_F1              = 0x3B,
	LUE_VK_F2              = 0x3C,
	LUE_VK_F3              = 0x3D,
	LUE_VK_F4              = 0x3E,
	LUE_VK_F5              = 0x3F,
	LUE_VK_F6              = 0x40,
	LUE_VK_F7              = 0x41,
	LUE_VK_F8              = 0x42,
	LUE_VK_F9              = 0x43,
	LUE_VK_F10             = 0x44,
	LUE_VK_NUMLOCK         = 0x45,
	LUE_VK_SCROLL          = 0x46,
	LUE_VK_NUMPAD7         = 0x47,
	LUE_VK_NUMPAD8         = 0x48,
	LUE_VK_NUMPAD9         = 0x49,
	LUE_VK_SUBTRACT        = 0x4A,
	LUE_VK_NUMPAD4         = 0x4B,
	LUE_VK_NUMPAD5         = 0x4C,
	LUE_VK_NUMPAD6         = 0x4D,
	LUE_VK_ADD             = 0x4E,
	LUE_VK_NUMPAD1         = 0x4F,
	LUE_VK_NUMPAD2         = 0x50,
	LUE_VK_NUMPAD3         = 0x51,
	LUE_VK_NUMPAD0         = 0x52,
	LUE_VK_DECIMAL         = 0x53,
	LUE_VK_OEM_102         = 0x56,
	LUE_VK_F11             = 0x57,
	LUE_VK_F12             = 0x58,
	LUE_VK_KANA            = 0x70,
	LUE_VK_ABNT_C1         = 0x73,
	LUE_VK_CONVERT         = 0x79,
	LUE_VK_NOCONVERT       = 0x7B,
	LUE_VK_YEN             = 0x7D,
	LUE_VK_ABNT_C2         = 0x7E,
	LUE_VK_NUMPADEQUALS    = 0x8D,
	LUE_VK_PREVTRACK       = 0x90,
	LUE_VK_NUMPADENTER     = 0x9C,
	LUE_VK_RCONTROL        = 0x9D,
	LUE_VK_NUMPADCOMMA     = 0xB3,
	LUE_VK_DIVIDE          = 0xB5,
	LUE_VK_SYSRQ           = 0xB7,
	LUE_VK_RMENU           = 0xB8,
	LUE_VK_PAUSE           = 0xC5,
	LUE_VK_HOME            = 0xC7,
	LUE_VK_UP              = 0xC8,
	LUE_VK_PRIOR           = 0xC9,
	LUE_VK_LEFT            = 0xCB,
	LUE_VK_RIGHT           = 0xCD,
	LUE_VK_END             = 0xCF,
	LUE_VK_DOWN            = 0xD0,
	LUE_VK_NEXT            = 0xD1,
	LUE_VK_INSERT          = 0xD2,
	LUE_VK_DELETE          = 0xD3,
	LUE_VK_LWIN            = 0xDB,
	LUE_VK_RWIN            = 0xDC,

	LUE_VK_NONE            = 0x00000000
}
eLueVirtualKey;

/**
	@brief 2D�x�N�g��
	@author �t���`
*/
typedef struct LueVector2D
{
	float x;					///< X����
	float y;					///< Y����
}
LueVector2D;

/**
	@brief 3D�x�N�g��
	@author �t���`
*/
typedef struct LueVector3D
{
	float x;					///< X����
	float y;					///< Y����
	float z;					///< Z����
}
LueVector3D;

/**
	@brief 4D�x�N�g��
	@author �t���`
*/
typedef struct LueVector4D
{
	float x;					///< X����
	float y;					///< Y����
	float z;					///< Z����
	float w;					///< W����
}
LueVector4D;

/**
	@brief 4x4�}�g���b�N�X
	@author �t���`
*/
typedef struct LueMatrix4x4
{
	LueVector4D x;					///< ��P�s
	LueVector4D y;					///< ��Q�s
	LueVector4D z;					///< ��R�s
	LueVector4D w;					///< ��S�s
}
LueMatrix4x4;

/**
	@brief �}�E�X�f�[�^
	@author �t���`
*/
typedef struct LueMouseData
{
	int Px;					///< X���W
	int Py;					///< Y���W
	int Pw;					///< �z�C�[�����W

	int Mx;					///< X���W�ړ���
	int My;					///< Y���W�ړ���

	int ClickL;				///< ���N���b�NON/OFF
	int ClickR;				///< �E�N���b�NON/OFF
	int ClickW;				///< �z�C�[���N���b�NON/OFF

	int DoubleClickL;			///< ���_�u���N���b�NON/OFF
	int DoubleClickR;			///< �E�_�u���N���b�NON/OFF
	int DoubleClickW;			///< �z�C�[���_�u���N���b�NON/OFF

	eLueMouseState StateL;		///< ���N���b�N�{�^�����
	eLueMouseState StateR;		///< �E�N���b�N�{�^�����
	eLueMouseState StateW;		///< �z�C�[���N���b�N�{�^�����
}
LueMouseData;

/**
	@brief �W���C�X�e�B�b�N�f�[�^
	@author �t���`
*/
typedef struct LueJoyStickData
{
	eLueBool IsActive;				///< �p�b�h�̗L���t���OON/OFF
	int Px, Py, Pz;				///< ��
	int Rx, Ry, Rz;				///< ��]��
	int Vx, Vy, Vz;				///< ���̑��x
	int VRx, VRy, VRz;				///< ���̊p���x
	int Ax, Ay, Az;				///< ���̉����x
	int ARx, ARy, ARz;				///< ���̊p�����x
	int Fx, Fy, Fz;				///< ���̃t�H�[�X
	int FRx, FRy, FRz;				///< ���̃g���N
	int Slider[2];					///< �X���C�_�[��
	int Pov[4];					///< POV��
	char Button[LPAD_BUTTON_MAX];	///< �p�b�h�̃{�^��
}
LueJoyStickData;

/**
	@brief 2D�|�C���g
	@author �t���`
*/
typedef struct LuePoint
{
	int x;					///< X���W
	int y;					///< Y���W
}
LuePoint;

/**
	@brief 2D���N�g
	@author �t���`
*/
typedef struct LueRect
{
	int x;					///< ����X���W
	int y;					///< ����Y���W
	int w;					///< X�T�C�Y
	int h;					///< Y�T�C�Y
}
LueRect;

/**
	@brief 2D�`��p���_�f�[�^
	@author �t���`
*/
typedef struct LueVertex2D
{
	LueVector4D Pos;			///< ���_�ʒu
	unsigned int Col;			///< ���_�F
}
LueVertex2D;

/**
	@brief 2D�`��p���_�f�[�^
	@author �t���`
*/
typedef struct LueVertex2DTex
{
	LueVector4D Pos;			///< ���_�ʒu
	unsigned int Col;			///< ���_�F
	LueVector2D Tex;			///< �e�N�X�`��UV
}
LueVertex2DTex;

/**
	@brief 2D���C���v���~�e�B�u�`��p
	@author �t���`
*/
typedef struct LueLinePrimitiveVertex2D
{
	LueVertex2D v[2];			///< ��������钸�_
}
LueLinePrimitiveVertex2D;

/**
	@brief 2D�v���~�e�B�u�`��p
	@author �t���`
*/
typedef struct LuePrimitiveVertex2D
{
	LueVertex2DTex v[3];			///< �O�p�`����钸�_
}
LuePrimitiveVertex2D;

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief sin�l���擾����
	@author �t���`

	@param Angle	[in] 1��65536�Ƃ����p�x

	@return sin�l

	sin�̒l���擾���܂��B
*/
float LueMath_Sin( int Angle );

/**
	@brief cos�l���擾����
	@author �t���`

	@param Angle	[in] 1��65536�Ƃ����p�x

	@return cos�l

	cos�̒l���擾���܂��B
*/
float LueMath_Cos( int Angle );

/**
	@brief atan2�l���擾����
	@author �t���`

	@param fPx	[in] arc tangent �v�Z�p��x�l
	@param fPy	[in] arc tangent �v�Z�p��y�l

	@return sin�l

	arc tangent �̒l���擾���܂��B
*/
int LueMath_ATan2( float fPx, float fPy );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �x�N�g���ɒl��ݒ�
	@author �t���`

	@param fPx	[in] x�l
	@param fPy	[in] y�l

	@return �l�ݒ��̃x�N�g��

	�l���x�N�g���ɐݒ肵�A���̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Set( float fPx, float fPy );

/**
	@brief �x�N�g�����m�̉��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Add( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g�����m�̌��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Sub( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
float LueVector2D_LengthSq( LueVector2D In );

/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
float LueVector2D_Length( LueVector2D In );

/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B
*/
LueVector2D LueVector2D_Normalize( LueVector2D In );

/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B
*/
float LueVector2D_DotProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B
*/
float LueVector2D_CrossProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief �x�N�g���̔��˂��擾
	@author �t���`

	@param In1	[in] ���˃x�N�g��
	@param In2	[in] ���ˎ��x�N�g��

	@return ���ˌ�̃x�N�g��

	���˃x�N�g���𔽎ˎ��x�N�g����@��Ƃ��镽�ʂŔ��˂�������<BR>
	���ˌ�̃x�N�g�����擾���܂��B
*/
LueVector2D LueVector2D_Reflect( LueVector2D In1, LueVector2D In2 );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �x�N�g���ɒl��ݒ�
	@author �t���`

	@param fPx	[in] x�l
	@param fPy	[in] y�l
	@param fPz	[in] z�l

	@return �l�ݒ��̃x�N�g��

	�l���x�N�g���ɐݒ肵�A���̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Set( float fPx, float fPy, float fPz );

/**
	@brief �x�N�g�����m�̉��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Add( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g�����m�̌��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Sub( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
float LueVector3D_LengthSq( LueVector3D In );

/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
float LueVector3D_Length( LueVector3D In );

/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B
*/
LueVector3D LueVector3D_Normalize( LueVector3D In );

/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B
*/
float LueVector3D_DotProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B
*/
LueVector3D LueVector3D_CrossProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̔��˂��擾
	@author �t���`

	@param In1	[in] ���˃x�N�g��
	@param In2	[in] ���ˎ��x�N�g��

	@return ���ˌ�̃x�N�g��

	���˃x�N�g���𔽎ˎ��x�N�g����@��Ƃ��镽�ʂŔ��˂�������<BR>
	���ˌ�̃x�N�g�����擾���܂��B
*/
LueVector3D LueVector3D_Reflect( LueVector3D In1, LueVector3D In2 );

/**
	@brief �x�N�g���̉�]�g�k�ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���ϊ����s���܂��B
*/
LueVector3D LueVector3D_TransformNormal( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ��ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��ϊ����s���܂��B
*/
LueVector3D LueVector3D_TransformCoord( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ������ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��E�����ϊ����s���܂��B<BR>
	���Z���w�l���ق����ꍇ�� LueVector4D_TransformProjection �g���Ă��������B
*/
LueVector3D LueVector3D_TransformProjection( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g����X����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����X���ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationX( LueVector3D In, int Angle );

/**
	@brief �x�N�g����Y����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Y���ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationY( LueVector3D In, int Angle );

/**
	@brief �x�N�g����Z����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Z���ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationZ( LueVector3D In, int Angle );

/**
	@brief �x�N�g���̔C�ӎ���]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x
	@param Axis		[in] ��]�̊��

	@return �ϊ���̃x�N�g��

	�x�N�g����C�ӂ̎��ŉ�]���܂��B
*/
LueVector3D LueVector3D_RotationAxis( LueVector3D In, int Angle, LueVector3D Axis );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �x�N�g���ɒl��ݒ�
	@author �t���`

	@param fPx	[in] x�l
	@param fPy	[in] y�l
	@param fPz	[in] z�l

	@return �l�ݒ��̃x�N�g��

	�l���x�N�g���ɐݒ肵�A���̃x�N�g�����擾���܂��B<BR>
	w�l��1.0f�ŏ���������Ă��܂��B
*/
LueVector4D LueVector4D_Set( float fPx, float fPy, float fPz );

/**
	@brief �x�N�g�����m�̉��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B<BR>
	������w�l��1.0f���ݒ肳��Ă��܂��B
*/
LueVector4D LueVector4D_Add( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g�����m�̌��Z
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���Z��̃x�N�g��

	�Q�̃x�N�g���̊e���������Z���A<BR>
	���̌��ʂ̃x�N�g�����擾���܂��B<BR>
	������w�l��1.0f���ݒ肳��Ă��܂��B
*/
LueVector4D LueVector4D_Sub( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̒����̓����擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return �����̓��

	�w��x�N�g���̒����̓����擾���܂��B
*/
float LueVector4D_LengthSq( LueVector4D In );

/**
	@brief �x�N�g���̒������擾
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ����

	�w��x�N�g���̒������擾���܂��B
*/
float LueVector4D_Length( LueVector4D In );

/**
	@brief �x�N�g���̐��K��
	@author �t���`

	@param In	[in] ���Z���x�N�g��

	@return ���K����̃x�N�g��

	�w��x�N�g���̐��K�����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_Normalize( LueVector4D In );

/**
	@brief �x�N�g���̓��ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return ���ϒl

	�w��x�N�g���̓��ς��擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
float LueVector4D_DotProduct( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̊O�ς��擾
	@author �t���`

	@param In1	[in] ���Z���x�N�g��
	@param In2	[in] ���Z���x�N�g��

	@return �O�ϒl

	�w��x�N�g���̊O�ς��擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_CrossProduct( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̔��˂��擾
	@author �t���`

	@param In1	[in] ���˃x�N�g��
	@param In2	[in] ���ˎ��x�N�g��

	@return ���ˌ�̃x�N�g��

	���˃x�N�g���𔽎ˎ��x�N�g����@��Ƃ��镽�ʂŔ��˂�������<BR>
	���ˌ�̃x�N�g�����擾���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_Reflect( LueVector4D In1, LueVector4D In2 );

/**
	@brief �x�N�g���̉�]�g�k�ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���ϊ����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_TransformNormal( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ��ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��ϊ����s���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_TransformCoord( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g���̉�]�g�k�ړ������ϊ�
	@author �t���`

	@param In1	[in] �x�N�g��
	@param In2	[in] �ϊ��p�}�g���b�N�X

	@return �ϊ���̃x�N�g��

	�x�N�g����^����ꂽ�}�g���b�N�X���g���ĉ�]�E�g��k���E�ړ��E�����ϊ����s���܂��B
*/
LueVector4D LueVector4D_TransformProjection( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief �x�N�g����X����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����X���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationX( LueVector4D In, int Angle );

/**
	@brief �x�N�g����Y����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Y���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationY( LueVector4D In, int Angle );

/**
	@brief �x�N�g����Z����]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x

	@return �ϊ���̃x�N�g��

	�x�N�g����Z���ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationZ( LueVector4D In, int Angle );

/**
	@brief �x�N�g���̔C�ӎ���]
	@author �t���`

	@param In		[in] �x�N�g��
	@param Angle	[in] 1����65536�Ƃ�����]�p�x
	@param Axis		[in] ��]�̊��

	@return �ϊ���̃x�N�g��

	�x�N�g����C�ӂ̎��ŉ�]���܂��B<BR>
	w�l��1.0f�ŏ���������܂��B
*/
LueVector4D LueVector4D_RotationAxis( LueVector4D In, int Angle, LueVector3D Axis );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

LueMatrix4x4 LueMatrix_Identity( void );
LueMatrix4x4 LueMatrix_Transpose( LueMatrix4x4 In );
LueMatrix4x4 LueMatrix_Inverse( LueMatrix4x4 In );
LueMatrix4x4 LueMatrix_Multiply( LueMatrix4x4 In1, LueMatrix4x4 In2 );

LueMatrix4x4 LueMatrix_RotationX( int Angle );
LueMatrix4x4 LueMatrix_RotationY( int Angle );
LueMatrix4x4 LueMatrix_RotationZ( int Angle );
LueMatrix4x4 LueMatrix_RotationZXY( int AngleX, int AngleY, int AngleZ );
LueMatrix4x4 LueMatrix_RotationAxis( int Angle, LueVector3D Axis );
LueMatrix4x4 LueMatrix_Scaling( float sx, float sy, float sz );
LueMatrix4x4 LueMatrix_Translation( float px, float py, float pz );

LueMatrix4x4 LueMatrix_Perspective( int fov, float near_z, float far_z, float aspect );
LueMatrix4x4 LueMatrix_Ortho( float w, float h, float near_z, float far_z );

LueMatrix4x4 LueMatrix_LookAt( LueVector3D Eye, LueVector3D At, LueVector3D Up );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �t�@�C���ǂݍ���
	@author �t���`

	@param pFile	[in] �ǂݍ��݃t�@�C����
	@param ppData	[out] �ǂݍ��݃f�[�^�i�[��
	@param pSize	[out] �ǂݍ��݃f�[�^�T�C�Y�i�[��

	@retval LTRUE	�ǂݍ��ݐ���
	@retval LFALSE	�ǂݍ��ݎ��s

	�t�@�C���̓ǂݍ��݂��s���܂��B<BR>
	�ǂݍ��݂���������Ɠ����Ń��������m�ۂ���A<BR>
	���̃A�h���X�� ppData �Ɋi�[����A�t�@�C���T�C�Y�� pSize �Ɋi�[����܂��B<BR>
	�ǂݍ��݌�A�s�v�ɂȂ����t�@�C���f�[�^�� File_Release �֐��Ń������ォ�������Ă��������B
*/
eLueBool LueFile_Load( const char *pFile, void **ppData, unsigned int *pSize );

/**
	@brief �t�@�C�����
	@author �t���`

	@param pData	[in] �ǂݍ��݃f�[�^���

	File_Load �֐��œǂݍ��񂾃f�[�^��������܂��B<BR>
	���̊֐��ŉ�����s��Ȃ��ƃA�v���P�[�V�������I�����Ă�<BR>
	����������폜����܂���B
*/
void LueFile_Release( void *pData );

/**
	@brief �t�@�C���̃I�[�v��
	@author �t���`

	@param pFile	[in] �t�@�C����

	@retval NULL		�t�@�C���I�[�v�����s
	@return NULL�ȊO	�t�@�C���̃t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̃N���[�Y���܂��B
*/
LUE_FILEPTR LueFile_FileOpen( const char *pFile );

/**
	@brief �t�@�C���̃N���[�Y
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̃N���[�Y���܂��B
*/
void LueFile_FileClose( LUE_FILEPTR FilePtr );

/**
	@brief �t�@�C���̃T�C�Y���擾
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̃t�@�C���T�C�Y���擾���܂��B
*/
unsigned int LueFile_FileGetSize( LUE_FILEPTR FilePtr );

/**
	@brief �t�@�C���|�C���^�̈ʒu���擾
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̌��݂̃t�@�C���|�C���^��<BR>
	�ʒu���擾���܂��B
*/
unsigned int LueFile_FileGetPosition( LUE_FILEPTR FilePtr );

/**
	@brief �t�@�C���̓ǂݍ���
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^
	@param pData	[in/out] �f�[�^�i�[��
	@param Size		[in] �ǂݍ��݃T�C�Y

	���݂̃t�@�C���|�C���^�̈ʒu����w��f�[�^�T�C�Y����<BR>
	�f�[�^��ǂݍ��݂܂��B
*/
unsigned int LueFile_FileRead( LUE_FILEPTR FilePtr, void *pData, unsigned int Size );

/**
	@brief �t�@�C���|�C���^�̈ړ�
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^
	@param Offset	[in] �t�@�C���|�C���^�̈ړ���
	@param Flag		[in] �t�@�C���|�C���^��ʒu

	�I�[�v�����̃t�@�C���̃t�@�C���|�C���^��C�ӂ̈ʒu�Ɉړ����܂��B
*/
int LueFile_FileSeek( LUE_FILEPTR FilePtr, int Offset, eLueSeek Flag );

/**
	@brief �t�@�C���ǂݍ��݃J�����g�f�B���N�g���ݒ�
	@author �t���`

	@param pCurrentDir	[in] �����J�����g�f�B���N�g��

	�t�@�C������������ۂɎg����J�����g�f�B���N�g����ݒ肵�܂�<BR>
	LueFile_SetLoadPath �����[�g�̃p�X�Ƃ��āA����ȉ��̃f�B���N�g�����w�肵�܂�<BR>
	<BR>
	��jData/Texture/Chara00/Stand.bmp �̓ǂݍ���<BR>
	LueFile_SetLoadPath �� Data ���w�肵�A<BR>
	LueFile_SetCurrentDirectory �� Texture/Chara00 ���w�肵�܂��B<BR>
	���̌� LueFile_Load �� Stand.bmp �Ǝw�肷�邱�Ƃœǂݍ��܂�܂��B
*/
void LueFile_SetCurrentDirectory( char *pCurrentDir );

/**
	@brief �t�@�C���ǂݍ��݃p�X�ݒ�
	@author �t���`

	@param Priority		[in] �ǂݍ��ݗD��x
	@param pRootPath	[in] ���[�g�f�B���N�g��
	@param pPackFile	[in] �p�b�N�t�@�C����

	�t�@�C���ǂݍ��݂̍ۂɎg����p�X��ݒ肵�܂�<BR>
	pRootPath �� pPackFile �͓���Ɉ����A<BR>
	pRootPath ���̌������s��� pPackFile ���̌������s���悤�ɂȂ��Ă��܂��B
*/
void LueFile_SetLoadPath( unsigned int Priority, const char *pRootPath, const char *pPackFile );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �V�[���J�n�錾
	@author �t���`

	@retval LTRUE	�V�[���J�n����
	@retval LFALSE	�V�[���J�n���s�i�V�[�����������ĂȂ��ꍇ��A��ʂ̃V�[�����牺�ʂ̃V�[���֓��낤�Ƃ����ꍇ���j

	��ʂ̕`�揈�����J�n���邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo������<BR>
	�łȂ���΂Ȃ�܂���B
*/
eLueBool LueRender_SceneStart( void );

/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐���<BR>
	�Ăяo���O�łȂ���΂Ȃ�܂���B
*/
void LueRender_SceneExit( void );

/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo���O<BR>
	�łȂ���΂Ȃ�܂���B
*/
void LueRender_Printf( const char *pStr, ... );

/**
	@brief �V�[���I���錾
	@author �t���`

	��ʂ̕`�揈�����I�����邱�Ƃ�錾���܂��B<BR>
	��ʂւȂ�炩�̕`����s���Ƃ��͂��̊֐����Ăяo���O<BR>
	�łȂ���΂Ȃ�܂���B
*/
void LueRender_ClsPrintf( void );

/**
	@brief �`�惂�[�h�ݒ�
	@author �t���`

	@param DrawMode		[in] �`�惂�[�h

	��ʂւ̕`����s���ۂ̕`����@���w�肵�܂�<BR>
	�s����/������/���Z/��Z�Ȃǂ��w��\�ł��B
*/
void LueRender_SetDrawMode( eLueDrawMode DrawMode );

/**
	@brief �e�N�X�`���̐ݒ�
	@author �t���`

	@param hTexture	[in] �e�N�X�`���n���h��

	�����_���[�ɑ΂��ĕ`��Ɏg�p����e�N�X�`����ݒ肵�܂��B<BR>
	INVALID_LUE_HANDLE ���w�肷��ƃe�N�X�`�����g��Ȃ��悤�ɂȂ�܂��B<BR>
	�܂��t�� INVALID_LUE_HANDLE ���w�肷��܂Őݒ肵���e�N�X�`����<BR>
	�g���鑱���鎖�ɂȂ�܂��B
	����� LueSprite2D �� LueFontSprite2D �̂悤�ɓ����Ńe�N�X�`����<BR>
	�����I�ɐ؂�ւ���֐����Ăяo������͕ύX���ꂽ�܂܂ɂȂ��Ă��܂��̂�<BR>
	�A�v���P�[�V�������Ŏg�p����ۂɂ͍ēx�ݒ肷��悤�ɂ��ĉ������B
*/
void LueRender_SetTexture( LUE_HANDLE hTexture );

/**
	@brief �e�N�X�`���̒��ڕ`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`���𒼐ډ�ʂɃ����_�����O���܂��B<BR>
	�ȈՓI�ɉ�ʂւ̕`����\�ɂ��邽�߂̊֐��ł��̂ŁA<BR>
	��ʂɕ`�悵�����ꍇ���A���x��D�悷��ꍇ�� LueSprite2D ��<BR>
	�g���Ă܂Ƃ߂ĕ`�悷��悤�ɂ��ĉ������B
*/
void LueRender_DrawSingleTexture( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �e�N�X�`���̃O���[�X�P�[���`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param fRate	[in] �O���[�X�P�[���K�p�x(0.0�`1.0)

	�e�N�X�`�����O���[�X�P�[�������ă����_�����O���܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawGrayscale( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, float fRate );

/**
	@brief �e�N�X�`���̃��j�o�[�T���g�����W�V�����`��
	@author �t���`

	@param HandleBase	[in] �J���[�e�N�X�`���n���h��
	@param HandleRule	[in] ���[���e�N�X�`���n���h��
	@param Dst			[in] �`���̋�`
	@param SrcBase		[in] �J���[�e�N�X�`���̕`�挳��`
	@param SrcRule		[in] ���[���e�N�X�`���̕`�挳��`
	@param fRate		[in] �������K�p�x(0.0�`1.0)

	���[���摜��p���ă��j�o�[�T���g�����W�V���������_�����O���܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawUniversalTransition( LUE_HANDLE HandleBase, LUE_HANDLE HandleRule, LueRect Dst, LueRect SrcBase, LueRect SrcRule, float fRate );

/**
	@brief �e�N�X�`���̂ڂ����`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`����3x3�{�b�N�X�t�B���^�����O�������Ăڂ����܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawBlur9Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �e�N�X�`���̂ڂ����`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`����4x4�{�b�N�X�t�B���^�����O�������Ăڂ����܂��B<BR>
	�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawSingleTexture()�ɒu���������܂��B
*/
void LueRender_DrawBlur16Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �e�N�X�`���̂ڂ����`��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��
	@param Dst		[in] �`���̋�`
	@param Src		[in] �e�N�X�`���̕`�挳��`
	@param Color	[in] ���_�F�iLUE_COLOR�}�N���ŐF�𐶐�

	�e�N�X�`����8x8�{�b�N�X�t�B���^�����O�������Ăڂ����܂��B<BR>
	�s�N�Z���V�F�[�_�[2.0���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
	LueRender_DrawBlur16Box()�ɒu���������܂��B
*/
void LueRender_DrawBlur64Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �T�[�t�F�C�X�̉��
	@author �t���`

	@param Handle	[in] �T�[�t�F�C�X�n���h��

	�T�[�t�F�C�X�̉�����s���܂��B
*/
void LueSurface_Release( LUE_HANDLE Handle );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �e�N�X�`�������p�R���t�B�O�ݒ�
	@author �t���`

	@param Color	[in] �J���[�L�[�̐F�i0�Ŕ����ݒ�Ȃ�

	�e�N�X�`�������p�̐ݒ���s���܂��B
*/
void LueTexture_SetConfig( unsigned int Color );

/**
	@brief �e�N�X�`���̉��
	@author �t���`

	@param Handle	[in] �e�N�X�`���n���h��

	�e�N�X�`���̉�����s���܂��B
*/
void LueTexture_Release( LUE_HANDLE Handle );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param Width	[in] �e�N�X�`���̉���
	@param Height	[in] �e�N�X�`���̏c��

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�w�肵���T�C�Y�̃e�N�X�`���̐������s���܂��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_Create( unsigned int Width, unsigned int Height );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�摜�t�@�C������e�N�X�`���̐������s���܂��B<BR>
	�T�|�[�g���Ă���摜�t�H�[�}�b�g�� TGA/PNG/JPG/DDS/BMP �ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_CreateFromFile( const char *pFileName );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param pData	[in] �e�N�X�`���t�@�C���̊i�[���ꂽ�������̃A�h���X
	@param Size		[in] pData�̃f�[�^�T�C�Y

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	���������̉摜�t�@�C������e�N�X�`���̐������s���܂��B<BR>
	�T�|�[�g���Ă���摜�t�H�[�}�b�g�� TGA/PNG/JPG/DDS/BMP �ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_CreateFromMemory( void *pData, unsigned int Size );

/**
	@brief �e�N�X�`���̐���
	@author �t���`

	@param Width	[in] �e�N�X�`���̉���
	@param Height	[in] �e�N�X�`���̏c��

	@return �e�N�X�`���n���h���i���s����INVALID_LUE_HANDLE�j

	�����_�����O�^�[�Q�b�g�Ƃ��ăe�N�X�`���𐶐����܂��B<BR>
	�����_�����O�^�[�Q�b�g�Ƃ��Đ������ꂽ�e�N�X�`���ɑ΂��Ă�<BR>
	���ڃ����_�����O���鎖���\�ł��B<BR>
	�T�C�Y�͂Q�̊K��ł���K�v������܂��B�@
*/
LUE_HANDLE LueTexture_CreateRenderTarget( unsigned int Width, unsigned int Height );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �|�C���g�v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] �|�C���g�v���~�e�B�u�n���h��

	�|�C���g�v���~�e�B�u�̉�����s���܂��B
*/
void LuePointPrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief �|�C���g�v���~�e�B�u����
	@author �t���`

	@param PointPrimitiveMax		[in] �|�C���g�v���~�e�B�u�ő吔

	@return �|�C���g�v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�|�C���g�v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł��B
*/
LUE_HANDLE LuePointPrimitive2D_Create( unsigned int PointPrimitiveMax );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�|�C���g�v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LuePointPrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ|�C���g�v���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LuePointPrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ|�C���g�v���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LuePointPrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��
	@param pPrimitive	[in] �|�C���g�v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`��|�C���g�v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
eLueBool LuePointPrimitive2D_Push( LUE_HANDLE Handle, LueVertex2D *pPrimitive, unsigned int Count );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ���C���v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] ���C���v���~�e�B�u�n���h��

	���C���v���~�e�B�u�̉�����s���܂��B
*/
void LueLinePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief ���C���v���~�e�B�u����
	@author �t���`

	@param LinePrimitiveMax		[in] ���C���v���~�e�B�u�ő吔

	@return ���C���v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	���C���v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł��B
*/
LUE_HANDLE LueLinePrimitive2D_Create( unsigned int LinePrimitiveMax );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ���C���v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LueLinePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��C���v���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LueLinePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��C���v���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LueLinePrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��
	@param pPrimitive	[in] ���C���v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`�惉�C���v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
eLueBool LueLinePrimitive2D_Push( LUE_HANDLE Handle, LueLinePrimitiveVertex2D *pPrimitive, unsigned int Count );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] �v���~�e�B�u�n���h��

	�v���~�e�B�u�̉�����s���܂��B
*/
void LuePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief �v���~�e�B�u����
	@author �t���`

	@param PrimitiveMax		[in] �v���~�e�B�u�ő吔

	@return �v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł���A<BR>
	�V�U�����O�����s���ƃ��N�G�X�g�������_����������������̂�<BR>
	�ڈ����x�Ƃ��Ĉ��Ȃ��\���ȑ傫�����w�肷��悤�ɂ��Ă��������B
*/
LUE_HANDLE LuePrimitive2D_Create( unsigned int PrimitiveMax );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LuePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LuePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LuePrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param pPrimitive	[in] �v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`��v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
eLueBool LuePrimitive2D_Push( LUE_HANDLE Handle, LuePrimitiveVertex2D *pPrimitive, unsigned int Count );

/**
	@brief �l�p�`�`��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param DstRect		[in] �`���`
	@param Color		[in] �`��F

	�l�p�`�̕`����s���܂��B
*/
void LuePrimitive2D_Square( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color );

/**
	@brief ��]�l�p�`�`��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param DstRect		[in] �`���`
	@param Color		[in] �`��F
	@param Angle		[in] ��]�p�x

	�l�p�`�̕`����s���܂��B
*/
void LuePrimitive2D_SquareRotate( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color, int Angle );

/**
	@brief �����p�`
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] ���p�`���S�ʒu
	@param fRadius		[in] ���p�`���a
	@param Color		[in] ���p�`�F
	@param Num			[in] �搔�i�R�`

	�����p�`��`�悵�܂��B
*/
void LuePrimitive2D_Polygon( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num );

/**
	@brief ��]�����p�`
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] ���p�`���S�ʒu
	@param fRadius		[in] ���p�`���a
	@param Color		[in] ���p�`�F
	@param Num			[in] �搔�i�R�`
	@param Angle		[in] ��]�p�x

	�����p�`��`�悵�܂��B
*/
void LuePrimitive2D_PolygonRotate( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num, int Angle );

/**
	@brief �����O��|���S��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] �����O�̒��S�ʒu
	@param fInRadius	[in] �����O�̓��a
	@param fOutRadius	[in] �����O�̊O�`
	@param InColor		[in] �����O�̓��F
	@param OutColor		[in] �����O�̊O�F
    @param Num			[in] �����O���\�����钸�_��

	�����O��̃|���S����`�悵�܂��B<BR>
	���a�O�a�ŕʁX�̐F���w��ł���̂ŏՌ��g�̂悤�ȃG�t�F�N�g�����܂��B
*/
void LuePrimitive2D_Ring( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num );

/**
	@brief ��]�����O��|���S��
	@author �t���`

	@param Handle		[in] �v���~�e�B�u�n���h��
	@param Pos			[in] �����O�̒��S�ʒu
	@param fInRadius	[in] �����O�̓��a
	@param fOutRadius	[in] �����O�̊O�`
	@param InColor		[in] �����O�̓��F
	@param OutColor		[in] �����O�̊O�F
    @param Num			[in] �����O���\�����钸�_��
	@param Angle		[in] ��]�p�x

	�����O��̃|���S����`�悵�܂��B<BR>
	���a�O�a�ŕʁX�̐F���w��ł���̂ŏՌ��g�̂悤�ȃG�t�F�N�g�����܂��B
*/
void LuePrimitive2D_RingRotate( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num, int Angle );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �X�v���C�g�̉��
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��

	�X�v���C�g�̉�����s���܂��B
*/
void LueSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief �X�v���C�g����
	@author �t���`

	@param PrimitiveMax		[in] �v���~�e�B�u�ő吔
	@param hTexture			[in] �ڑ�����e�N�X�`���̃n���h��

	@return �X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�X�v���C�g�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł���A<BR>
	�V�U�����O�����s���ƃ��N�G�X�g�������_����������������̂�<BR>
	�ڈ����x�Ƃ��Ĉ��Ȃ��\���ȑ傫�����w�肷��悤�ɂ��Ă��������B<BR>
	�܂� hTeture �Ŏw�肵���e�N�X�`�����g���ĕ`�悳��܂��B
*/
LUE_HANDLE LueSprite2D_Create( unsigned int PrimitiveMax, LUE_HANDLE hTexture );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LueSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LueSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃv���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LueSprite2D_End( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��
	@param Dst		[in] �`����`
	@param Src		[in] �e�N�X�`��UV��`
	@param Color	[in] ���_�F

	�X�v���C�g���g������`�̕`����s���܂��B
*/
void LueSprite2D_DrawSquare( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��
	@param Dst		[in] �`����`
	@param Src		[in] �e�N�X�`��UV��`
	@param Color	[in] ���_�F
	@param Angle	[in] 1��65536�Ƃ�����]�p�x

	�X�v���C�g���g������`�̉�]�`����s���܂��B
*/
void LueSprite2D_DrawSquareRotate( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, unsigned int Angle );

/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �X�v���C�g�n���h��
	@param Pos		[in] �|�C���g��X,Y�l���i�[���ꂽ�z��
	@param Width	[in] �|�C���g�̕����i�[���ꂽ�z��
	@param Angle	[in] �|�C���g��1��65536�Ƃ�����]�p�x���i�[���ꂽ�z��
	@param Color	[in] 1��65536�Ƃ�����]�p�x
	@param Count	[in] �e�z��̗v�f��
	@param Src		[in] �e�N�X�`��UV��`

	�X�v���C�g���g�������X�g��̕`����s���܂�<BR>
	�Ȃ��郌�[�U�[�̂悤�ȑ��֐ߌn�̕\������̂ɓK���Ă��܂��B
*/
void LueSprite2D_DrawList( LUE_HANDLE Handle, LuePoint Pos[], float Width[], int Angle[], unsigned int Color[], int Count, LueRect Src );

/**
	@brief �~��t�F�[�h
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��
	@param SrcRect		[in] �e�N�X�`���̓K����`
	@param Divide		[in] ��]�����������i�P�U���x�����j
	@param Side			[in] ���ʕ������i�P�U���x�����j
	@param Alpha		[in] �������x�i-255�`+255)

	��ʒ��S�Ɍ������ăt�F�[�h�C���^�t�F�[�h�A�E�g�����܂�<BR>
	��ʌ��ʂƂ��Ă悭����������ʂł����ȒP�Ɏg�����ʌ��ʂƂ��Ď������Ă���܂��B
*/
void LueSprite2D_CircleFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha );

/**
	@brief ��]�t�F�[�h
	@author �t���`

	@param Handle		[in] �X�v���C�g�n���h��
	@param SrcRect		[in] �e�N�X�`���̓K����`
	@param Divide		[in] ��]�����������i�P�U���x�����j
	@param Side			[in] ���ʕ������i�P�U���x�����j
	@param Alpha		[in] �������x�i-255�`+255)

	���v���ɉ�]����悤�Ƀt�F�[�h�C���^�t�F�[�h�A�E�g�����܂�<BR>
	��ʌ��ʂƂ��Ă悭����������ʂł����ȒP�Ɏg�����ʌ��ʂƂ��Ď������Ă���܂��B
*/
void LueSprite2D_CircleRoundFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief �t�H���g�X�v���C�g�̉��
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��

	�t�H���g�X�v���C�g�̉�����s���܂��B
*/
void LueFontSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief �t�H���g�X�v���C�g����
	@author �t���`

	@param pBuffer		[in] �e�N�X�`���쐬�p������
	@param FontMax		[in] �t�H���g�X�v���C�g��
	@param pFontFace	[in] �t�H���g����
	@param FontSize		[in] �t�H���g�T�C�Y�i�s�N�Z��
	@param IsItalic		[in] �Α̂�ON/OFF
	@param IsBold		[in] ������ON/OFF
	@param IsAntialias	[in] �A���`�G�C���A�X��ON/OFF

	@return �t�H���g�X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�����񂩂�t�H���g�X�v���C�g�𐶐����܂��B<BR>
	pBuffer �Ŏw�肳�ꂽ����������̑������ɉ����ăe�N�X�`���ɓW�J���܂��B<BR>
	FontMax�͍ő�`��\���ł���A�V�U�����O�Ȃǂœ����o�b�t�@��<BR>
	���N�G�X�g��葽���g���邱�Ƃ�����܂��̂ŁA���Ȃ��\���ȑ傫�����w�肵�Ă��������B
*/
LUE_HANDLE LueFontSprite2D_Create( const char *pBuffer, unsigned int FontMax, const char *pFontFace, unsigned int FontSize, eLueBool IsItalic, eLueBool IsBold, eLueBool IsAntialias );

/**
	@brief �t�H���g�X�v���C�g����
	@author �t���`

	@param pFileName	[in] �e�N�X�`���쐬�p������
	@param pExt			[in] �e�N�X�`���g���q�iFont_00.tga�̏ꍇ��"tga"�j
	@param FontMax		[in] �t�H���g�X�v���C�g��

	@return �t�H���g�X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	���O�ɍ쐬���ꂽ�t�H���g�f�[�^����t�H���g�X�v���C�g�𐶐����܂��B<BR>
	FontMax�͍ő�`��\���ł���A�V�U�����O�Ȃǂœ����o�b�t�@��<BR>
	���N�G�X�g��葽���g���邱�Ƃ�����܂��̂ŁA���Ȃ��\���ȑ傫�����w�肵�Ă��������B
*/
LUE_HANDLE LueFontSprite2D_CreateFromFile( const char *pFileName, const char *pExt, unsigned int FontMax );

/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃt�H���g�X�v���C�g�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
void LueFontSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃt�H���g�X�v���C�g�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
void LueFontSprite2D_End( LUE_HANDLE Handle );

/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�t�H���g�X�v���C�g�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
void LueFontSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g���������t�H���g�ł̕�����`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
void LueFontSprite2D_DrawString( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g�����v���|�[�V���i���t�H���g�ł̕�����`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
void LueFontSprite2D_DrawStringP( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief �����`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶��
	@param Dst		[in] �`���`
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g���������`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
int LueFontSprite2D_DrawChara( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color );

/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Dst		[in] �`���`
	@param Color	[in] ���_�F
	@param Angle	[in] 1��65536�Ƃ�����]�p�x

	�t�H���g�X�v���C�g���g������]�t��������`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
int LueFontSprite2D_DrawCharaRotate( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color, int Angle );

/**
	@brief ������`��ʒu�擾
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l

	�t�H���g�X�v���C�g���g���������t�H���g�ł̕�����`����s������́B<BR>
	�ŏI�I�Ȉʒu���擾���܂��B<BR>
	�����ĕ������`�悷��ꍇ��A������̍����╝���擾����̂ɗL���ł��B
*/
LuePoint LueFontSprite2D_GetStringLastPos( LUE_HANDLE Handle, const char *pStr, int Px, int Py );

/**
	@brief ������`��ʒu�擾
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Px		[in] �`��X�l
	@param Py		[in] �`��Y�l

	�t�H���g�X�v���C�g���g�����v���|�[�V���i���t�H���g�ł̕�����`����s������́B<BR>
	�ŏI�I�Ȉʒu���擾���܂��B<BR>
	�����ĕ������`�悷��ꍇ��A������̍����╝���擾����̂ɗL���ł��B
*/
LuePoint LueFontSprite2D_GetStringLastPosP( LUE_HANDLE Handle, const char *pStr, int Px, int Py );

#ifdef __cplusplus
}
#endif // __cplusplus


#endif  // ___LUE_H___


