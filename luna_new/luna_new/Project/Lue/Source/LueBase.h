
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
#define LPAD_BUTTON_MAX			16						///< パッドで使用可能なボタン数
#define INVALID_LUE_HANDLE		0xFFFFFFFF				///< 無効なハンドル
#define SOUND_LOOP_INFINITY		0xFFFFFFFF				///< サウンド無限ループ指定
#define LUE_ANGLE_MAX			(1 << 16)				///< Lueで使用される角度の最大値
#define LUE_ANGLE_MASK			(LUE_ANGLE_MAX - 1)		///< 角度に対してのマスク値


//=============================================================================
// MACRO
//=============================================================================
#define LUE_COLOR(a,r,g,b)	(	(((unsigned int)(a))<<24) |\
								(((unsigned int)(r))<<16) |\
								(((unsigned int)(g))<< 8) |\
								(((unsigned int)(b))<< 0)	)		///< 色作成

#define LUE_RGB(r,g,b)			LUE_COLOR(255,r,g,b)				///< 色作成
#define LUE_ARGB(a,r,g,b)		LUE_COLOR(a,r,g,b)					///< 色作成
#define LUE_A(a)				LUE_COLOR(a,255,255,255)			///< 色作成
#define LUE_BRIGHT(c)			LUE_COLOR(255,c,c,c)				///< 色作成


//=============================================================================
// TYPEDEF
//=============================================================================
typedef void			*LUE_FILEPTR;		///< ファイルポインタ
typedef unsigned int	LUE_HANDLE;			///< ハンドル


//=============================================================================
// ENUM
//=============================================================================
/**
	@brief フレームレート定義
	@author 葉迩倭
*/
typedef enum eLueFrameRata
{
	LFRAME_RATE_60,					///< 1/60秒毎
	LFRAME_RATE_30,					///< 1/30秒毎
	LFRAME_RATE_20,					///< 1/20秒毎
	LFRAME_RATE_15,					///< 1/15秒毎
	LFRAME_RATE_VSYNC,				///< Vsync依存
}
eLueFrameRata;

/**
	@brief 結果フラグ
	@author 葉迩倭
*/
typedef enum eLueBool
{
	LFALSE,				///< ON  or TRUE
	LTRUE,				///< OFF or FALSE
}
eLueBool;

/**
	@brief 描画モード
	@author 葉迩倭
*/
typedef enum eLueDrawMode
{
	LDRAW_MODE_NORMAL,					///< 通常描画
	LDRAW_MODE_BLEND,					///< 半透明描画
	LDRAW_MODE_ADD,						///< 加算描画
	LDRAW_MODE_ADD_NOALPHA,				///< 加算描画（アルファ値無効）
	LDRAW_MODE_SUB,						///< 減算描画（アルファ値無効）
	LDRAW_MODE_SUB_NOALPHA,				///< 減算描画（アルファ値無効）
	LDRAW_MODE_MULTIPLE,				///< 乗算描画
	LDRAW_MODE_SCREEN,					///< スクリーン描画
}
eLueDrawMode;

/**
	@brief ファイルシーク基準位置
	@author 葉迩倭
*/
typedef enum eLueSeek
{
	LSEEK_FILE_CURRENT,			///< 現在位置
	LSEEK_FILE_START,			///< 先頭位置
	LSEEK_FILE_END,				///< 終端位置
}
eLueSeek;

/**
	@brief ジョイスティックボタン状態
	@author 葉迩倭
*/
typedef enum eLueKeyState
{
	LKEY_STATE_FREE,			///< 押されていない
	LKEY_STATE_PULL,			///< 離した瞬間
	LKEY_STATE_PUSH,			///< 押した瞬間
	LKEY_STATE_HOLD,			///< 押し続けている状態
}
eLueKeyState;

/**
	@brief マウスボタン状態
	@author 葉迩倭
*/
typedef enum eLueMouseState
{
	LMOUSE_FREE,				///< 押されていない
	LMOUSE_PULL,				///< 離した瞬間
	LMOUSE_PUSH,				///< 押した瞬間
	LMOUSE_HOLD,				///< 押し続けている状態
}
eLueMouseState;

/**
	@brief 使用API種類
	@author 葉迩倭
*/
typedef enum eLueAPIType
{
	LAPI_TYPE_DIRECTX9,			///< DirectX9を使う
}
eLueAPIType;


//=============================================================================
// VIRTUAL KEY CODE
//=============================================================================
/**
	@brief キーコード
	@author 葉迩倭
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
	@brief 2Dベクトル
	@author 葉迩倭
*/
typedef struct LueVector2D
{
	float x;					///< X成分
	float y;					///< Y成分
}
LueVector2D;

/**
	@brief 3Dベクトル
	@author 葉迩倭
*/
typedef struct LueVector3D
{
	float x;					///< X成分
	float y;					///< Y成分
	float z;					///< Z成分
}
LueVector3D;

/**
	@brief 4Dベクトル
	@author 葉迩倭
*/
typedef struct LueVector4D
{
	float x;					///< X成分
	float y;					///< Y成分
	float z;					///< Z成分
	float w;					///< W成分
}
LueVector4D;

/**
	@brief 4x4マトリックス
	@author 葉迩倭
*/
typedef struct LueMatrix4x4
{
	LueVector4D x;					///< 第１行
	LueVector4D y;					///< 第２行
	LueVector4D z;					///< 第３行
	LueVector4D w;					///< 第４行
}
LueMatrix4x4;

/**
	@brief マウスデータ
	@author 葉迩倭
*/
typedef struct LueMouseData
{
	int Px;					///< X座標
	int Py;					///< Y座標
	int Pw;					///< ホイール座標

	int Mx;					///< X座標移動量
	int My;					///< Y座標移動量

	int ClickL;				///< 左クリックON/OFF
	int ClickR;				///< 右クリックON/OFF
	int ClickW;				///< ホイールクリックON/OFF

	int DoubleClickL;			///< 左ダブルクリックON/OFF
	int DoubleClickR;			///< 右ダブルクリックON/OFF
	int DoubleClickW;			///< ホイールダブルクリックON/OFF

	eLueMouseState StateL;		///< 左クリックボタン状態
	eLueMouseState StateR;		///< 右クリックボタン状態
	eLueMouseState StateW;		///< ホイールクリックボタン状態
}
LueMouseData;

/**
	@brief ジョイスティックデータ
	@author 葉迩倭
*/
typedef struct LueJoyStickData
{
	eLueBool IsActive;				///< パッドの有効フラグON/OFF
	int Px, Py, Pz;				///< 軸
	int Rx, Ry, Rz;				///< 回転軸
	int Vx, Vy, Vz;				///< 軸の速度
	int VRx, VRy, VRz;				///< 軸の角速度
	int Ax, Ay, Az;				///< 軸の加速度
	int ARx, ARy, ARz;				///< 軸の角加速度
	int Fx, Fy, Fz;				///< 軸のフォース
	int FRx, FRy, FRz;				///< 軸のトルク
	int Slider[2];					///< スライダー軸
	int Pov[4];					///< POV軸
	char Button[LPAD_BUTTON_MAX];	///< パッドのボタン
}
LueJoyStickData;

/**
	@brief 2Dポイント
	@author 葉迩倭
*/
typedef struct LuePoint
{
	int x;					///< X座標
	int y;					///< Y座標
}
LuePoint;

/**
	@brief 2Dレクト
	@author 葉迩倭
*/
typedef struct LueRect
{
	int x;					///< 左上X座標
	int y;					///< 左上Y座標
	int w;					///< Xサイズ
	int h;					///< Yサイズ
}
LueRect;

/**
	@brief 2D描画用頂点データ
	@author 葉迩倭
*/
typedef struct LueVertex2D
{
	LueVector4D Pos;			///< 頂点位置
	unsigned int Col;			///< 頂点色
}
LueVertex2D;

/**
	@brief 2D描画用頂点データ
	@author 葉迩倭
*/
typedef struct LueVertex2DTex
{
	LueVector4D Pos;			///< 頂点位置
	unsigned int Col;			///< 頂点色
	LueVector2D Tex;			///< テクスチャUV
}
LueVertex2DTex;

/**
	@brief 2Dラインプリミティブ描画用
	@author 葉迩倭
*/
typedef struct LueLinePrimitiveVertex2D
{
	LueVertex2D v[2];			///< 線分を作る頂点
}
LueLinePrimitiveVertex2D;

/**
	@brief 2Dプリミティブ描画用
	@author 葉迩倭
*/
typedef struct LuePrimitiveVertex2D
{
	LueVertex2DTex v[3];			///< 三角形を作る頂点
}
LuePrimitiveVertex2D;


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_BASE_H___
