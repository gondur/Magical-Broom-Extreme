//==============================================================================//
//                         DirectX9用簡易ライブラリ Lue                         //
//==============================================================================//
//                                                                              //
//    最新版の置いてあるURL                                                     //
//                                                                              //
//    TWINTAIL LOVERS.                                                          //
//      http://www.twin-tail.jp/                                                //
//                                                                              //
//    質問等発言場所                                                            //
//      TWINTAIL LOVERS.内の掲示板                                              //
//                                                                              //
//   DirectX Library 'Lue'                                                      //
//   Copyright (C) 2006 葉迩倭                                                  //
//   All rights reserved.                                                       //
//                                                                              //
//==============================================================================//


#ifndef ___LUE_H___
#define ___LUE_H___

#include <windows.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LPAD_BUTTON_MAX			16						///< パッドで使用可能なボタン数
#define INVALID_LUE_HANDLE		0xFFFFFFFF				///< 無効なハンドル
#define SOUND_LOOP_INFINITY		0xFFFFFFFF				///< サウンド無限ループ指定
#define LUE_ANGLE_MAX			(1 << 16)				///< Lueで使用される角度の最大値
#define LUE_ANGLE_MASK			(LUE_ANGLE_MAX - 1)		///< 角度に対してのマスク値

#define LUE_COLOR(a,r,g,b)	(	(((unsigned int)(a))<<24) |\
								(((unsigned int)(r))<<16) |\
								(((unsigned int)(g))<< 8) |\
								(((unsigned int)(b))<< 0)	)		///< 色作成

#define LUE_RGB(r,g,b)			LUE_COLOR(255,r,g,b)				///< 色作成
#define LUE_ARGB(a,r,g,b)		LUE_COLOR(a,r,g,b)					///< 色作成
#define LUE_A(a)				LUE_COLOR(a,255,255,255)			///< 色作成
#define LUE_BRIGHT(c)			LUE_COLOR(255,c,c,c)				///< 色作成

typedef void			*LUE_FILEPTR;		///< ファイルポインタ
typedef unsigned int	LUE_HANDLE;			///< ハンドル

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

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief sin値を取得する
	@author 葉迩倭

	@param Angle	[in] 1周65536とした角度

	@return sin値

	sinの値を取得します。
*/
float LueMath_Sin( int Angle );

/**
	@brief cos値を取得する
	@author 葉迩倭

	@param Angle	[in] 1周65536とした角度

	@return cos値

	cosの値を取得します。
*/
float LueMath_Cos( int Angle );

/**
	@brief atan2値を取得する
	@author 葉迩倭

	@param fPx	[in] arc tangent 計算用のx値
	@param fPy	[in] arc tangent 計算用のy値

	@return sin値

	arc tangent の値を取得します。
*/
int LueMath_ATan2( float fPx, float fPy );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ベクトルに値を設定
	@author 葉迩倭

	@param fPx	[in] x値
	@param fPy	[in] y値

	@return 値設定後のベクトル

	値をベクトルに設定し、そのベクトルを取得します。
*/
LueVector2D LueVector2D_Set( float fPx, float fPy );

/**
	@brief ベクトル同士の加算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を加算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector2D LueVector2D_Add( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトル同士の減算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を減算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector2D LueVector2D_Sub( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトルの長さの二乗を取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さの二乗

	指定ベクトルの長さの二乗を取得します。
*/
float LueVector2D_LengthSq( LueVector2D In );

/**
	@brief ベクトルの長さを取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さ

	指定ベクトルの長さを取得します。
*/
float LueVector2D_Length( LueVector2D In );

/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。
*/
LueVector2D LueVector2D_Normalize( LueVector2D In );

/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。
*/
float LueVector2D_DotProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。
*/
float LueVector2D_CrossProduct( LueVector2D In1, LueVector2D In2 );

/**
	@brief ベクトルの反射を取得
	@author 葉迩倭

	@param In1	[in] 入射ベクトル
	@param In2	[in] 反射軸ベクトル

	@return 反射後のベクトル

	入射ベクトルを反射軸ベクトルを法泉とする平面で反射した時の<BR>
	反射後のベクトルを取得します。
*/
LueVector2D LueVector2D_Reflect( LueVector2D In1, LueVector2D In2 );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ベクトルに値を設定
	@author 葉迩倭

	@param fPx	[in] x値
	@param fPy	[in] y値
	@param fPz	[in] z値

	@return 値設定後のベクトル

	値をベクトルに設定し、そのベクトルを取得します。
*/
LueVector3D LueVector3D_Set( float fPx, float fPy, float fPz );

/**
	@brief ベクトル同士の加算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を加算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector3D LueVector3D_Add( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトル同士の減算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を減算し、<BR>
	その結果のベクトルを取得します。
*/
LueVector3D LueVector3D_Sub( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの長さの二乗を取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さの二乗

	指定ベクトルの長さの二乗を取得します。
*/
float LueVector3D_LengthSq( LueVector3D In );

/**
	@brief ベクトルの長さを取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さ

	指定ベクトルの長さを取得します。
*/
float LueVector3D_Length( LueVector3D In );

/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。
*/
LueVector3D LueVector3D_Normalize( LueVector3D In );

/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。
*/
float LueVector3D_DotProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。
*/
LueVector3D LueVector3D_CrossProduct( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの反射を取得
	@author 葉迩倭

	@param In1	[in] 入射ベクトル
	@param In2	[in] 反射軸ベクトル

	@return 反射後のベクトル

	入射ベクトルを反射軸ベクトルを法泉とする平面で反射した時の<BR>
	反射後のベクトルを取得します。
*/
LueVector3D LueVector3D_Reflect( LueVector3D In1, LueVector3D In2 );

/**
	@brief ベクトルの回転拡縮変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小変換を行います。
*/
LueVector3D LueVector3D_TransformNormal( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルの回転拡縮移動変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動変換を行います。
*/
LueVector3D LueVector3D_TransformCoord( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルの回転拡縮移動透視変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動・透視変換を行います。<BR>
	演算後のw値がほしい場合は LueVector4D_TransformProjection 使ってください。
*/
LueVector3D LueVector3D_TransformProjection( LueVector3D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルのX軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをX軸で回転します。
*/
LueVector3D LueVector3D_RotationX( LueVector3D In, int Angle );

/**
	@brief ベクトルのY軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをY軸で回転します。
*/
LueVector3D LueVector3D_RotationY( LueVector3D In, int Angle );

/**
	@brief ベクトルのZ軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをZ軸で回転します。
*/
LueVector3D LueVector3D_RotationZ( LueVector3D In, int Angle );

/**
	@brief ベクトルの任意軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度
	@param Axis		[in] 回転の基準軸

	@return 変換後のベクトル

	ベクトルを任意の軸で回転します。
*/
LueVector3D LueVector3D_RotationAxis( LueVector3D In, int Angle, LueVector3D Axis );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ベクトルに値を設定
	@author 葉迩倭

	@param fPx	[in] x値
	@param fPy	[in] y値
	@param fPz	[in] z値

	@return 値設定後のベクトル

	値をベクトルに設定し、そのベクトルを取得します。<BR>
	w値は1.0fで初期化されています。
*/
LueVector4D LueVector4D_Set( float fPx, float fPy, float fPz );

/**
	@brief ベクトル同士の加算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を加算し、<BR>
	その結果のベクトルを取得します。<BR>
	ただしw値は1.0fが設定されています。
*/
LueVector4D LueVector4D_Add( LueVector4D In1, LueVector4D In2 );

/**
	@brief ベクトル同士の減算
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 演算後のベクトル

	２つのベクトルの各成分を減算し、<BR>
	その結果のベクトルを取得します。<BR>
	ただしw値は1.0fが設定されています。
*/
LueVector4D LueVector4D_Sub( LueVector4D In1, LueVector4D In2 );

/**
	@brief ベクトルの長さの二乗を取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さの二乗

	指定ベクトルの長さの二乗を取得します。
*/
float LueVector4D_LengthSq( LueVector4D In );

/**
	@brief ベクトルの長さを取得
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 長さ

	指定ベクトルの長さを取得します。
*/
float LueVector4D_Length( LueVector4D In );

/**
	@brief ベクトルの正規化
	@author 葉迩倭

	@param In	[in] 演算元ベクトル

	@return 正規化後のベクトル

	指定ベクトルの正規化を行います。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_Normalize( LueVector4D In );

/**
	@brief ベクトルの内積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 内積値

	指定ベクトルの内積を取得します。<BR>
	w値は1.0fで初期化されます。
*/
float LueVector4D_DotProduct( LueVector4D In1, LueVector4D In2 );

/**
	@brief ベクトルの外積を取得
	@author 葉迩倭

	@param In1	[in] 演算元ベクトル
	@param In2	[in] 演算元ベクトル

	@return 外積値

	指定ベクトルの外積を取得します。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_CrossProduct( LueVector4D In1, LueVector4D In2 );

/**
	@brief ベクトルの反射を取得
	@author 葉迩倭

	@param In1	[in] 入射ベクトル
	@param In2	[in] 反射軸ベクトル

	@return 反射後のベクトル

	入射ベクトルを反射軸ベクトルを法泉とする平面で反射した時の<BR>
	反射後のベクトルを取得します。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_Reflect( LueVector4D In1, LueVector4D In2 );

/**
	@brief ベクトルの回転拡縮変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小変換を行います。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_TransformNormal( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルの回転拡縮移動変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動変換を行います。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_TransformCoord( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルの回転拡縮移動透視変換
	@author 葉迩倭

	@param In1	[in] ベクトル
	@param In2	[in] 変換用マトリックス

	@return 変換後のベクトル

	ベクトルを与えられたマトリックスを使って回転・拡大縮小・移動・透視変換を行います。
*/
LueVector4D LueVector4D_TransformProjection( LueVector4D In1, LueMatrix4x4 In2 );

/**
	@brief ベクトルのX軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをX軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_RotationX( LueVector4D In, int Angle );

/**
	@brief ベクトルのY軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをY軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_RotationY( LueVector4D In, int Angle );

/**
	@brief ベクトルのZ軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度

	@return 変換後のベクトル

	ベクトルをZ軸で回転します。<BR>
	w値は1.0fで初期化されます。
*/
LueVector4D LueVector4D_RotationZ( LueVector4D In, int Angle );

/**
	@brief ベクトルの任意軸回転
	@author 葉迩倭

	@param In		[in] ベクトル
	@param Angle	[in] 1周を65536とした回転角度
	@param Axis		[in] 回転の基準軸

	@return 変換後のベクトル

	ベクトルを任意の軸で回転します。<BR>
	w値は1.0fで初期化されます。
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
	@brief ファイルからサウンドを読み込み、<BR>
	そのサウンドのハンドルを取得します。
	@author 葉迩倭

	@param pFileName	[in] ファイル名
	@param IsAllActive	[in] LTRUE にするとウィンドウが非アクティブでも停止しない

	@return 未使用のサウンドハンドル

	サウンドファイルを読み込み、そのサウンドの操作用のハンドルを取得します。<BR>
	取得したサウンドは不要になったら解放して下さい。
*/
LUE_HANDLE LueSound_CreateFromFile( const char *pFileName, eLueBool IsAllActive );

/**
	@brief サウンドを解放します。
	@author 葉迩倭

	@param Handle	[in] サウンドハンドル

	読み込んだサウンドをメモリから解放します。
*/
void LueSound_Release( LUE_HANDLE Handle );

/**
	@brief サウンドを再生開始
	@author 葉迩倭

	@param Handle	[in] サウンドハンドル

	読み込んだサウンドをメモリから解放します。
*/
void LueSound_Play( LUE_HANDLE Handle );

/**
	@brief サウンドをループ再生開始
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param LoopCount	[in] ループ回数<BR>無限ループの場合は SOUND_LOOP_INFINITY を指定。
	@param LoopSample	[in] ループ開始位置（サンプリング数で指定）

	サウンドのループ再生を行います。
*/
void LueSound_Loop( LUE_HANDLE Handle, unsigned int LoopCount, unsigned int LoopSample );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	再生中のサウンドを停止します。
*/
void LueSound_Stop( LUE_HANDLE Handle );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	再生中のサウンドを停止します。
*/
void LueSound_Pause( LUE_HANDLE Handle );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param fParam		[in] ボリューム値(+0～+100)

	再生中のサウンドを停止します。
*/
void LueSound_SetVolume( LUE_HANDLE Handle, float fParam );

/**
	@brief 再生中のサウンドを停止
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル
	@param fParam		[in] パン値(-100～+100)

	再生中のサウンドを停止します。
*/
void LueSound_SetPan( LUE_HANDLE Handle, float fParam );

/**
	@brief サウンドが再生中であるかチェック
	@author 葉迩倭

	@param Handle		[in] サウンドハンドル

	@retval true		再生中（一時停止含む）
	@retval false		停止中

	再生中のサウンドであるかどうかを調べます。
*/
eLueBool LueSound_IsPlay( LUE_HANDLE Handle );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ファイル読み込み
	@author 葉迩倭

	@param pFile	[in] 読み込みファイル名
	@param ppData	[out] 読み込みデータ格納先
	@param pSize	[out] 読み込みデータサイズ格納先

	@retval LTRUE	読み込み成功
	@retval LFALSE	読み込み失敗

	ファイルの読み込みを行います。<BR>
	読み込みが成功すると内部でメモリが確保され、<BR>
	そのアドレスが ppData に格納され、ファイルサイズが pSize に格納されます。<BR>
	読み込み後、不要になったファイルデータは File_Release 関数でメモリ上から解放してください。
*/
eLueBool LueFile_Load( const char *pFile, void **ppData, unsigned int *pSize );

/**
	@brief ファイル解放
	@author 葉迩倭

	@param pData	[in] 読み込みデータ解放

	File_Load 関数で読み込んだデータを解放します。<BR>
	この関数で解放を行わないとアプリケーションが終了しても<BR>
	メモリから削除されません。
*/
void LueFile_Release( void *pData );

/**
	@brief ファイルのオープン
	@author 葉迩倭

	@param pFile	[in] ファイル名

	@retval NULL		ファイルオープン失敗
	@return NULL以外	ファイルのファイルポインタ

	オープン中のファイルのクローズします。
*/
LUE_FILEPTR LueFile_FileOpen( const char *pFile );

/**
	@brief ファイルのクローズ
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ

	オープン中のファイルのクローズします。
*/
void LueFile_FileClose( LUE_FILEPTR FilePtr );

/**
	@brief ファイルのサイズを取得
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ

	オープン中のファイルのファイルサイズを取得します。
*/
unsigned int LueFile_FileGetSize( LUE_FILEPTR FilePtr );

/**
	@brief ファイルポインタの位置を取得
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ

	オープン中のファイルの現在のファイルポインタの<BR>
	位置を取得します。
*/
unsigned int LueFile_FileGetPosition( LUE_FILEPTR FilePtr );

/**
	@brief ファイルの読み込み
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ
	@param pData	[in/out] データ格納先
	@param Size		[in] 読み込みサイズ

	現在のファイルポインタの位置から指定データサイズ分の<BR>
	データを読み込みます。
*/
unsigned int LueFile_FileRead( LUE_FILEPTR FilePtr, void *pData, unsigned int Size );

/**
	@brief ファイルポインタの移動
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ
	@param Offset	[in] ファイルポインタの移動量
	@param Flag		[in] ファイルポインタ基準位置

	オープン中のファイルのファイルポインタを任意の位置に移動します。
*/
int LueFile_FileSeek( LUE_FILEPTR FilePtr, int Offset, eLueSeek Flag );

/**
	@brief ファイル読み込みカレントディレクトリ設定
	@author 葉迩倭

	@param pCurrentDir	[in] 検索カレントディレクトリ

	ファイルを検索する際に使われるカレントディレクトリを設定します<BR>
	LueFile_SetLoadPath をルートのパスとして、それ以下のディレクトリを指定します<BR>
	<BR>
	例）Data/Texture/Chara00/Stand.bmp の読み込み<BR>
	LueFile_SetLoadPath で Data を指定し、<BR>
	LueFile_SetCurrentDirectory で Texture/Chara00 を指定します。<BR>
	その後 LueFile_Load で Stand.bmp と指定することで読み込まれます。
*/
void LueFile_SetCurrentDirectory( char *pCurrentDir );

/**
	@brief ファイル読み込みパス設定
	@author 葉迩倭

	@param Priority		[in] 読み込み優先度
	@param pRootPath	[in] ルートディレクトリ
	@param pPackFile	[in] パックファイル名

	ファイル読み込みの際に使われるパスを設定します<BR>
	pRootPath と pPackFile は同列に扱われ、<BR>
	pRootPath 内の検索実行後に pPackFile 内の検索を行うようになっています。
*/
void LueFile_SetLoadPath( unsigned int Priority, const char *pRootPath, const char *pPackFile );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief Lueシステムの初期化を行います
	@author 葉迩倭

	@param pAppName		[in] アプリケーション名
	@param ScreenW		[in] 画面横幅
	@param ScreenH		[in] 画面縦幅
	@param FrameRate	[in] フレームレート
	@param IsWindowMode	[in] ウィンドウモードで起動するかどうか
	@param Type			[in] 使用するAPI（現在は LAPI_TYPE_DIRECTX9 固定）

	@retval LTRUE	初期化成功
	@retval LFALSE	初期化失敗

	Lueシステムの初期化処理を行います。<BR>
	この関数が完了した段階ですべてのLue系の関数を使うことが可能になります。
*/
eLueBool Lue_Initialize( const char *pAppName, unsigned int ScreenW, unsigned int ScreenH, eLueFrameRata FrameRate, eLueBool IsWindowMode, eLueAPIType Type );

/**
	@brief Lueシステムの終了
	@author 葉迩倭

	Lueシステムをすべて解放します。<BR>
	この関数が呼ばれた後にLue系の関数を呼び出すことは禁止されています。
*/
void Lue_Finalize( void );

/**
	@brief Lueシステムのメイン処理
	@author 葉迩倭

	@param IsActive	[in] LTRUE の時、フォーカスを失っても動作し続ける。

	@retval LTRUE	アプリケーション動作中
	@retval LFALSE	アプリケーション停止

	Lueシステムのメイン処理を行います。<BR>
	毎フレーム呼び出すようにしてください。<BR>
	また返り値がLFALSEのときは直ちにメインループから抜けて下さい。
*/
eLueBool Lue_Run( eLueBool IsActive );

/**
	@brief バージョン文字列取得
	@author 葉迩倭

	@param pStr		[out] バージョン文字列格納先
	@param Size		[in] pStrのバッファサイズ

	Lueのバージョンを文字列で取得します。<BR>
	この関数を呼び出すことで DLL のバージョンを取得することが可能です。
*/
void Lue_GetVersionString( char *pStr, unsigned int Size );

/**
	@brief バージョン番号取得
	@author 葉迩倭

	@return バージョン番号

	Lueのバージョンを数値で取得します。<BR>
	上位16Bitにメジャーバージョン、下位16Bitにマイナーバージョンが格納されています。
*/
unsigned int Lue_GetVersionNumber( void );

/**
	@brief OS起動からの時間取得
	@author 葉迩倭

	@return 1/1000秒単位の時間

	OSが起動してからの時間を取得します。<BR>
	32Bit変数なので約48日で1周して0に戻ってしまいます。
*/
unsigned int Lue_GetTime( void );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief キーボッドの入力バッファをクリア
	@author 葉迩倭

	キーボードの情報が格納されている入力バッファをクリアします。
*/
void LueInput_ClearKeyBuffer( void );

/**
	@brief キーボード入力バッファの取得
	@author 葉迩倭

	@retval 0		入力なし
	@return 0以外	押されたキーのキーコード

	キーボード入力バッファ内のデータを１つづつ取り出します。<BR>
	バッファが空になった時点で LUE_VK_NONE が返ります。
*/
eLueVirtualKey LueInput_GetKeyBuffer( void );

/**
	@brief キーボード情報取得
	@author 葉迩倭

	@param Key	[in] 調べたいキーのキーコード

	@retval LTRUE	押されている
	@retval LFALSE	押されていない
*/
eLueBool LueInput_GetKeyData( eLueVirtualKey Key );

/**
	@brief マウス情報取得
	@author 葉迩倭

	@return マウスデータ

	マウスの情報を取得します。
*/
LueMouseData LueInput_GetMouseData( void );

/**
	@brief ジョイスティック情報取得
	@author 葉迩倭

	@param No	[in] ジョイスティック番号

	@return ジョイスティックデータ

	指定接続番号のジョイスティックのデータを取得します。<BR>
	指定接続番号のジョイスティックが接続されていない場合は<BR>
	IsActive メンバ変数に LFALSE が設定されます。
*/
LueJoyStickData LueInput_GetJoystickData( int No );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief シーン開始宣言
	@author 葉迩倭

	@retval LTRUE	シーン開始成功
	@retval LFALSE	シーン開始失敗（シーンを完了してない場合や、上位のシーンから下位のシーンへ入ろうとした場合等）

	画面の描画処理を開始することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出した後<BR>
	でなければなりません。
*/
eLueBool LueRender_SceneStart( void );

/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を<BR>
	呼び出す前でなければなりません。
*/
void LueRender_SceneExit( void );

/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出す前<BR>
	でなければなりません。
*/
void LueRender_Printf( const char *pStr, ... );

/**
	@brief シーン終了宣言
	@author 葉迩倭

	画面の描画処理を終了することを宣言します。<BR>
	画面へなんらかの描画を行うときはこの関数を呼び出す前<BR>
	でなければなりません。
*/
void LueRender_ClsPrintf( void );

/**
	@brief 描画モード設定
	@author 葉迩倭

	@param DrawMode		[in] 描画モード

	画面への描画を行う際の描画方法を指定します<BR>
	不透明/半透明/加算/乗算などが指定可能です。
*/
void LueRender_SetDrawMode( eLueDrawMode DrawMode );

/**
	@brief テクスチャの設定
	@author 葉迩倭

	@param hTexture	[in] テクスチャハンドル

	レンダラーに対して描画に使用するテクスチャを設定します。<BR>
	INVALID_LUE_HANDLE を指定するとテクスチャを使わないようになります。<BR>
	また逆に INVALID_LUE_HANDLE を指定するまで設定したテクスチャが<BR>
	使われる続ける事になります。
	さらに LueSprite2D や LueFontSprite2D のように内部でテクスチャを<BR>
	自動的に切り替える関数を呼び出した後は変更されたままになっていますので<BR>
	アプリケーション側で使用する際には再度設定するようにして下さい。
*/
void LueRender_SetTexture( LUE_HANDLE hTexture );

/**
	@brief テクスチャの直接描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを直接画面にレンダリングします。<BR>
	簡易的に画面への描画を可能にするための関数ですので、<BR>
	大量に描画したい場合等、速度を優先する場合は LueSprite2D を<BR>
	使ってまとめて描画するようにして下さい。
*/
void LueRender_DrawSingleTexture( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief テクスチャのグレースケール描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成
	@param Src		[in] テクスチャの描画元矩形
	@param fRate	[in] グレースケール適用度(0.0～1.0)

	テクスチャをグレースケール化してレンダリングします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawGrayscale( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, float fRate );

/**
	@brief テクスチャのユニバーサルトランジション描画
	@author 葉迩倭

	@param HandleBase	[in] カラーテクスチャハンドル
	@param HandleRule	[in] ルールテクスチャハンドル
	@param Dst			[in] 描画先の矩形
	@param SrcBase		[in] カラーテクスチャの描画元矩形
	@param SrcRule		[in] ルールテクスチャの描画元矩形
	@param fRate		[in] 半透明適用度(0.0～1.0)

	ルール画像を用いてユニバーサルトランジションレンダリングします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawUniversalTransition( LUE_HANDLE HandleBase, LUE_HANDLE HandleRule, LueRect Dst, LueRect SrcBase, LueRect SrcRule, float fRate );

/**
	@brief テクスチャのぼかし描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを3x3ボックスフィルタリングをかけてぼかします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawBlur9Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief テクスチャのぼかし描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを4x4ボックスフィルタリングをかけてぼかします。<BR>
	ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
	LueRender_DrawSingleTexture()に置き換えられます。
*/
void LueRender_DrawBlur16Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief テクスチャのぼかし描画
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル
	@param Dst		[in] 描画先の矩形
	@param Src		[in] テクスチャの描画元矩形
	@param Color	[in] 頂点色（LUE_COLORマクロで色を生成

	テクスチャを8x8ボックスフィルタリングをかけてぼかします。<BR>
	ピクセルシェーダー2.0をサポートしないビデオカードの場合<BR>
	LueRender_DrawBlur16Box()に置き換えられます。
*/
void LueRender_DrawBlur64Box( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief サーフェイスの解放
	@author 葉迩倭

	@param Handle	[in] サーフェイスハンドル

	サーフェイスの解放を行います。
*/
void LueSurface_Release( LUE_HANDLE Handle );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief テクスチャ生成用コンフィグ設定
	@author 葉迩倭

	@param Color	[in] カラーキーの色（0で抜け設定なし

	テクスチャ生成用の設定を行います。
*/
void LueTexture_SetConfig( unsigned int Color );

/**
	@brief テクスチャの解放
	@author 葉迩倭

	@param Handle	[in] テクスチャハンドル

	テクスチャの解放を行います。
*/
void LueTexture_Release( LUE_HANDLE Handle );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param Width	[in] テクスチャの横幅
	@param Height	[in] テクスチャの縦幅

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	指定したサイズのテクスチャの生成を行います。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_Create( unsigned int Width, unsigned int Height );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャファイル名

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	画像ファイルからテクスチャの生成を行います。<BR>
	サポートしている画像フォーマットは TGA/PNG/JPG/DDS/BMP です。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_CreateFromFile( const char *pFileName );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param pData	[in] テクスチャファイルの格納されたメモリのアドレス
	@param Size		[in] pDataのデータサイズ

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	メモリ内の画像ファイルからテクスチャの生成を行います。<BR>
	サポートしている画像フォーマットは TGA/PNG/JPG/DDS/BMP です。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_CreateFromMemory( void *pData, unsigned int Size );

/**
	@brief テクスチャの生成
	@author 葉迩倭

	@param Width	[in] テクスチャの横幅
	@param Height	[in] テクスチャの縦幅

	@return テクスチャハンドル（失敗時はINVALID_LUE_HANDLE）

	レンダリングターゲットとしてテクスチャを生成します。<BR>
	レンダリングターゲットとして生成されたテクスチャに対しては<BR>
	直接レンダリングする事が可能です。<BR>
	サイズは２の階乗である必要があります。　
*/
LUE_HANDLE LueTexture_CreateRenderTarget( unsigned int Width, unsigned int Height );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ポイントプリミティブの解放
	@author 葉迩倭

	@param Handle	[in] ポイントプリミティブハンドル

	ポイントプリミティブの解放を行います。
*/
void LuePointPrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief ポイントプリミティブ生成
	@author 葉迩倭

	@param PointPrimitiveMax		[in] ポイントプリミティブ最大数

	@return ポイントプリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	ポイントプリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズです。
*/
LUE_HANDLE LuePointPrimitive2D_Create( unsigned int PointPrimitiveMax );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル

	この関数を呼び出すことでリクエストされたポイントプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LuePointPrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル

	この関数を呼び出すことでポイントプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LuePointPrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル

	この関数を呼び出すことでポイントプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LuePointPrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle		[in] ポイントプリミティブハンドル
	@param pPrimitive	[in] ポイントプリミティブ頂点データ
	@param Count		[in] pPrimitiveの数

	@retval LTRUE	正常に追加できた
	@retval LFALSE	追加できなかった（バッファオーバーフロー

	描画ポイントプリミティブ頂点を追加します。<BR>
	必ず Begin() と End() の間で呼んでください。<BR>
	この関数は実際に描画を行いません<BR>
	バッファに追加するだけで実際の描画は Render() 時に行われます。
*/
eLueBool LuePointPrimitive2D_Push( LUE_HANDLE Handle, LueVertex2D *pPrimitive, unsigned int Count );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief ラインプリミティブの解放
	@author 葉迩倭

	@param Handle	[in] ラインプリミティブハンドル

	ラインプリミティブの解放を行います。
*/
void LueLinePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief ラインプリミティブ生成
	@author 葉迩倭

	@param LinePrimitiveMax		[in] ラインプリミティブ最大数

	@return ラインプリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	ラインプリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズです。
*/
LUE_HANDLE LueLinePrimitive2D_Create( unsigned int LinePrimitiveMax );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでリクエストされたラインプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LueLinePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでラインプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LueLinePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル

	この関数を呼び出すことでラインプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LueLinePrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle		[in] ラインプリミティブハンドル
	@param pPrimitive	[in] ラインプリミティブ頂点データ
	@param Count		[in] pPrimitiveの数

	@retval LTRUE	正常に追加できた
	@retval LFALSE	追加できなかった（バッファオーバーフロー

	描画ラインプリミティブ頂点を追加します。<BR>
	必ず Begin() と End() の間で呼んでください。<BR>
	この関数は実際に描画を行いません<BR>
	バッファに追加するだけで実際の描画は Render() 時に行われます。
*/
eLueBool LueLinePrimitive2D_Push( LUE_HANDLE Handle, LueLinePrimitiveVertex2D *pPrimitive, unsigned int Count );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief プリミティブの解放
	@author 葉迩倭

	@param Handle	[in] プリミティブハンドル

	プリミティブの解放を行います。
*/
void LuePrimitive2D_Release( LUE_HANDLE Handle );

/**
	@brief プリミティブ生成
	@author 葉迩倭

	@param PrimitiveMax		[in] プリミティブ最大数

	@return プリミティブハンドル（失敗した場合はINVALID_LUE_HANDLE）

	プリミティブオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズであり、<BR>
	シザリング等を行うとリクエストした頂点数よりも多く消費されるので<BR>
	目安程度として溢れない十分な大きさを指定するようにしてください。
*/
LUE_HANDLE LuePrimitive2D_Create( unsigned int PrimitiveMax );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでリクエストされたプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LuePrimitive2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LuePrimitive2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LuePrimitive2D_End( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param pPrimitive	[in] プリミティブ頂点データ
	@param Count		[in] pPrimitiveの数

	@retval LTRUE	正常に追加できた
	@retval LFALSE	追加できなかった（バッファオーバーフロー

	描画プリミティブ頂点を追加します。<BR>
	必ず Begin() と End() の間で呼んでください。<BR>
	この関数は実際に描画を行いません<BR>
	バッファに追加するだけで実際の描画は Render() 時に行われます。
*/
eLueBool LuePrimitive2D_Push( LUE_HANDLE Handle, LuePrimitiveVertex2D *pPrimitive, unsigned int Count );

/**
	@brief 四角形描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param DstRect		[in] 描画矩形
	@param Color		[in] 描画色

	四角形の描画を行います。
*/
void LuePrimitive2D_Square( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color );

/**
	@brief 回転四角形描画
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param DstRect		[in] 描画矩形
	@param Color		[in] 描画色
	@param Angle		[in] 回転角度

	四角形の描画を行います。
*/
void LuePrimitive2D_SquareRotate( LUE_HANDLE Handle, LueRect DstRect, unsigned int Color, int Angle );

/**
	@brief 正多角形
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] 多角形中心位置
	@param fRadius		[in] 多角形半径
	@param Color		[in] 多角形色
	@param Num			[in] 画数（３～

	正多角形を描画します。
*/
void LuePrimitive2D_Polygon( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num );

/**
	@brief 回転正多角形
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] 多角形中心位置
	@param fRadius		[in] 多角形半径
	@param Color		[in] 多角形色
	@param Num			[in] 画数（３～
	@param Angle		[in] 回転角度

	正多角形を描画します。
*/
void LuePrimitive2D_PolygonRotate( LUE_HANDLE Handle, LuePoint Pos, float fRadius, unsigned int Color, int Num, int Angle );

/**
	@brief リング状ポリゴン
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] リングの中心位置
	@param fInRadius	[in] リングの内径
	@param fOutRadius	[in] リングの外形
	@param InColor		[in] リングの内色
	@param OutColor		[in] リングの外色
    @param Num			[in] リングを構成する頂点数

	リング状のポリゴンを描画します。<BR>
	内径外径で別々の色が指定できるので衝撃波のようなエフェクトが作れます。
*/
void LuePrimitive2D_Ring( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num );

/**
	@brief 回転リング状ポリゴン
	@author 葉迩倭

	@param Handle		[in] プリミティブハンドル
	@param Pos			[in] リングの中心位置
	@param fInRadius	[in] リングの内径
	@param fOutRadius	[in] リングの外形
	@param InColor		[in] リングの内色
	@param OutColor		[in] リングの外色
    @param Num			[in] リングを構成する頂点数
	@param Angle		[in] 回転角度

	リング状のポリゴンを描画します。<BR>
	内径外径で別々の色が指定できるので衝撃波のようなエフェクトが作れます。
*/
void LuePrimitive2D_RingRotate( LUE_HANDLE Handle, LuePoint Pos, float fInRadius, float fOutRadius, unsigned int InColor, unsigned int OutColor, int Num, int Angle );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief スプライトの解放
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル

	スプライトの解放を行います。
*/
void LueSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief スプライト生成
	@author 葉迩倭

	@param PrimitiveMax		[in] プリミティブ最大数
	@param hTexture			[in] 接続するテクスチャのハンドル

	@return スプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	スプライトオブジェクトの生成を行います。<BR>
	PrimitiveMax は内部で確保されるバッファのサイズであり、<BR>
	シザリング等を行うとリクエストした頂点数よりも多く消費されるので<BR>
	目安程度として溢れない十分な大きさを指定するようにしてください。<BR>
	また hTeture で指定したテクスチャを使って描画されます。
*/
LUE_HANDLE LueSprite2D_Create( unsigned int PrimitiveMax, LUE_HANDLE hTexture );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでリクエストされたプリミティブデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LueSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LueSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル

	この関数を呼び出すことでプリミティブの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LueSprite2D_End( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Dst		[in] 描画先矩形
	@param Src		[in] テクスチャUV矩形
	@param Color	[in] 頂点色

	スプライトを使った矩形の描画を行います。
*/
void LueSprite2D_DrawSquare( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Dst		[in] 描画先矩形
	@param Src		[in] テクスチャUV矩形
	@param Color	[in] 頂点色
	@param Angle	[in] 1周65536とした回転角度

	スプライトを使った矩形の回転描画を行います。
*/
void LueSprite2D_DrawSquareRotate( LUE_HANDLE Handle, LueRect Dst, LueRect Src, unsigned int Color, unsigned int Angle );

/**
	@brief 描画リクエスト
	@author 葉迩倭

	@param Handle	[in] スプライトハンドル
	@param Pos		[in] ポイントのX,Y値が格納された配列
	@param Width	[in] ポイントの幅が格納された配列
	@param Angle	[in] ポイントの1周65536とした回転角度が格納された配列
	@param Color	[in] 1周65536とした回転角度
	@param Count	[in] 各配列の要素数
	@param Src		[in] テクスチャUV矩形

	スプライトを使ったリスト状の描画を行います<BR>
	曲がるレーザーのような多関節系の表現するのに適しています。
*/
void LueSprite2D_DrawList( LUE_HANDLE Handle, LuePoint Pos[], float Width[], int Angle[], unsigned int Color[], int Count, LueRect Src );

/**
	@brief 円状フェード
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル
	@param SrcRect		[in] テクスチャの適応矩形
	@param Divide		[in] 回転部分分割数（１６程度推奨）
	@param Side			[in] 側面分割数（１６程度推奨）
	@param Alpha		[in] 半透明度（-255～+255)

	画面中心に向かってフェードイン／フェードアウトをします<BR>
	画面効果としてよく見かける効果ですが簡単に使える画面効果として実装してあります。
*/
void LueSprite2D_CircleFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha );

/**
	@brief 回転フェード
	@author 葉迩倭

	@param Handle		[in] スプライトハンドル
	@param SrcRect		[in] テクスチャの適応矩形
	@param Divide		[in] 回転部分分割数（１６程度推奨）
	@param Side			[in] 側面分割数（１６程度推奨）
	@param Alpha		[in] 半透明度（-255～+255)

	時計回りに回転するようにフェードイン／フェードアウトをします<BR>
	画面効果としてよく見かける効果ですが簡単に使える画面効果として実装してあります。
*/
void LueSprite2D_CircleRoundFade( LUE_HANDLE Handle, LueRect SrcRect, int Divide, int Side, int Alpha );

#ifdef __cplusplus
}
#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
	@brief フォントスプライトの解放
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル

	フォントスプライトの解放を行います。
*/
void LueFontSprite2D_Release( LUE_HANDLE Handle );

/**
	@brief フォントスプライト生成
	@author 葉迩倭

	@param pBuffer		[in] テクスチャ作成用文字列
	@param FontMax		[in] フォントスプライト数
	@param pFontFace	[in] フォント書体
	@param FontSize		[in] フォントサイズ（ピクセル
	@param IsItalic		[in] 斜体のON/OFF
	@param IsBold		[in] 太字のON/OFF
	@param IsAntialias	[in] アンチエイリアスのON/OFF

	@return フォントスプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	文字列からフォントスプライトを生成します。<BR>
	pBuffer で指定された文字列をその他引数に応じてテクスチャに展開します。<BR>
	FontMaxは最大描画可能個数であり、シザリングなどで内部バッファが<BR>
	リクエストより多く使われることもありますので、溢れない十分な大きさを指定してください。
*/
LUE_HANDLE LueFontSprite2D_Create( const char *pBuffer, unsigned int FontMax, const char *pFontFace, unsigned int FontSize, eLueBool IsItalic, eLueBool IsBold, eLueBool IsAntialias );

/**
	@brief フォントスプライト生成
	@author 葉迩倭

	@param pFileName	[in] テクスチャ作成用文字列
	@param pExt			[in] テクスチャ拡張子（Font_00.tgaの場合は"tga"）
	@param FontMax		[in] フォントスプライト数

	@return フォントスプライトハンドル（失敗した場合はINVALID_LUE_HANDLE）

	事前に作成されたフォントデータからフォントスプライトを生成します。<BR>
	FontMaxは最大描画可能個数であり、シザリングなどで内部バッファが<BR>
	リクエストより多く使われることもありますので、溢れない十分な大きさを指定してください。
*/
LUE_HANDLE LueFontSprite2D_CreateFromFile( const char *pFileName, const char *pExt, unsigned int FontMax );

/**
	@brief 描画リクエスト開始
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでフォントスプライトの描画リクエストが開始します。<BR>
	これ以降は描画リクエストを行うことは出来ます。<BR>
	描画リクエストをする前には必ずこの関数でリクエスト状態を開始して下さい。
*/
void LueFontSprite2D_Begin( LUE_HANDLE Handle );

/**
	@brief 描画リクエスト終了
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでフォントスプライトの描画リクエストが完了します。<BR>
	これ以降は描画リクエストを行うことはできません。<BR>
	Render() を呼び出す前には必ずこの関数でリクエスト状態を終了して下さい。
*/
void LueFontSprite2D_End( LUE_HANDLE Handle );

/**
	@brief 描画
	@author 葉迩倭

	@param Handle		[in] フォントスプライトハンドル

	この関数を呼び出すことでリクエストされたフォントスプライトデータが描画されます。<BR>
	デバイスへの描画キューの追加を行うだけですのでこの関数自体はすぐに終了しますが、<BR>
	実際の描画が完了しているわけではありません。<BR>
*/
void LueFontSprite2D_Rendering( LUE_HANDLE Handle );

/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値
	@param Color	[in] 頂点色

	フォントスプライトを使った等幅フォントでの文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
void LueFontSprite2D_DrawString( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値
	@param Color	[in] 頂点色

	フォントスプライトを使ったプロポーショナルフォントでの文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
void LueFontSprite2D_DrawStringP( LUE_HANDLE Handle, const char *pStr, int Px, int Py, unsigned int Color );

/**
	@brief 文字描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字
	@param Dst		[in] 描画矩形
	@param Color	[in] 頂点色

	フォントスプライトを使った文字描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
int LueFontSprite2D_DrawChara( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color );

/**
	@brief 文字列描画リクエスト
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Dst		[in] 描画矩形
	@param Color	[in] 頂点色
	@param Angle	[in] 1周65536とした回転角度

	フォントスプライトを使った回転付き文字列描画処理を行います。<BR>
	この関数は描画用のバッファにデータを追加するだけで<BR>
	実際の描画処理は Render() を呼び出すことで行われます。<BR>
	また必ず Begin() と End() の間で呼び出すようにしてください。
*/
int LueFontSprite2D_DrawCharaRotate( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color, int Angle );

/**
	@brief 文字列描画位置取得
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値

	フォントスプライトを使った等幅フォントでの文字列描画を行った後の。<BR>
	最終的な位置を取得します。<BR>
	続けて文字列を描画する場合や、文字列の高さや幅を取得するのに有効です。
*/
LuePoint LueFontSprite2D_GetStringLastPos( LUE_HANDLE Handle, const char *pStr, int Px, int Py );

/**
	@brief 文字列描画位置取得
	@author 葉迩倭

	@param Handle	[in] フォントスプライトハンドル
	@param pStr		[in] 描画文字列
	@param Px		[in] 描画X値
	@param Py		[in] 描画Y値

	フォントスプライトを使ったプロポーショナルフォントでの文字列描画を行った後の。<BR>
	最終的な位置を取得します。<BR>
	続けて文字列を描画する場合や、文字列の高さや幅を取得するのに有効です。
*/
LuePoint LueFontSprite2D_GetStringLastPosP( LUE_HANDLE Handle, const char *pStr, int Px, int Py );

#ifdef __cplusplus
}
#endif // __cplusplus


#endif  // ___LUE_H___


