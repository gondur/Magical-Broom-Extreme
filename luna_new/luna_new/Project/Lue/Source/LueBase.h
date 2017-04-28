
#ifndef ___LUE_BASE_H___
#define ___LUE_BASE_H___

#include "../../../Release/Include/Selene.h"
#include <strsafe.h>


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//=============================================================================
// DEFINE
//=============================================================================
#define LPAD_BUTTON_MAX			16						///< �p�b�h�Ŏg�p�\�ȃ{�^����
#define INVALID_LUE_HANDLE		0xFFFFFFFF				///< �����ȃn���h��
#define SOUND_LOOP_INFINITY		0xFFFFFFFF				///< �T�E���h�������[�v�w��
#define LUE_ANGLE_MAX			(1 << 16)				///< Lue�Ŏg�p�����p�x�̍ő�l
#define LUE_ANGLE_MASK			(LUE_ANGLE_MAX - 1)		///< �p�x�ɑ΂��Ẵ}�X�N�l


//=============================================================================
// MACRO
//=============================================================================
#define LUE_COLOR(a,r,g,b)	(	(((unsigned int)(a))<<24) |\
								(((unsigned int)(r))<<16) |\
								(((unsigned int)(g))<< 8) |\
								(((unsigned int)(b))<< 0)	)		///< �F�쐬

#define LUE_RGB(r,g,b)			LUE_COLOR(255,r,g,b)				///< �F�쐬
#define LUE_ARGB(a,r,g,b)		LUE_COLOR(a,r,g,b)					///< �F�쐬
#define LUE_A(a)				LUE_COLOR(a,255,255,255)			///< �F�쐬
#define LUE_BRIGHT(c)			LUE_COLOR(255,c,c,c)				///< �F�쐬


//=============================================================================
// TYPEDEF
//=============================================================================
typedef void			*LUE_FILEPTR;		///< �t�@�C���|�C���^
typedef unsigned int	LUE_HANDLE;			///< �n���h��


//=============================================================================
// ENUM
//=============================================================================
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


//=============================================================================
// VIRTUAL KEY CODE
//=============================================================================
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


//=============================================================================
// STRUCT
//=============================================================================
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


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_BASE_H___
