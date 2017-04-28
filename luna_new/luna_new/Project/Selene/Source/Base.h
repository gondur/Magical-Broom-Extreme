//------------------------------------------------------------------------------//
//                       DirectX9用ライブラリ Selene                            //
//------------------------------------------------------------------------------//
//                                                                              //
//  最新版の置いてあるURL                                                       //
//    TWINTAIL LOVERS.                                                          //
//      http://www.twin-tail.jp/                                                //
//                                                                              //
//  質問等発言場所                                                              //
//    BBS                                                                       //
//      TWINTAIL LOVERS.内の掲示板                                              //
//                                                                              //
//                                                  DirectX Library 'Selene'    //
//                                                  Copyright (C) 2006 葉迩倭   //
//                                                  All rights reserved.        //
//------------------------------------------------------------------------------//

#ifndef ___SELENE__BASE___
#define ___SELENE__BASE___


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#undef _UNICODE
#define _UNICODE
#undef UNICODE
#define UNICODE


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>

#include "DirectX9.h"


//-----------------------------------------------------------------------------------
// WARNING
//-----------------------------------------------------------------------------------
#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )

#pragma warning ( disable: 4819 )
#pragma warning ( disable: 4201 )


//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
typedef char					Sint8;								///< signed char 型の別定義
typedef short					Sint16;								///< signed short 型の別定義
typedef long					Sint32;								///< signed long 型の別定義
typedef __int64					Sint64;								///< signed __int64 型の別定義
typedef unsigned char			Uint8;								///< unsigned char 型の別定義
typedef unsigned short			Uint16;								///< unsigned short 型の別定義
typedef unsigned long			Uint32;								///< unsigned long 型の別定義
typedef unsigned __int64		Uint64;								///< unsigned __int64 型の別定義
typedef float					Float;								///< Float 型の別定義
typedef float					Float32;							///< Float 型の別定義
typedef double					Float64;							///< double 型の別定義
typedef long double				Float80;							///< long double 型の別定義
typedef bool					Bool;								///< Bool 型の別定義

typedef void					*FX_HANDLE;							///< エフェクトファイルのハンドル


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define ef									else if																		///< else if 簡略用マクロ

#define toF(val)							((Float)(val))																///< Float型へのキャストマクロ
#define toI(val)							((Sint32)(val))																///< Sint32型へのキャストマクロ

#define PI									(3.141592653589793238462643383279f)											///< π
#define PI2									(6.283185307179586476925286766559f)											///< 2π
#define REV(val)							toF(1.0f/toF(val))															///< 逆数算出マクロ

#define SHADER_BONE_MAX						(48)

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))													///< 最小値取得マクロ
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))													///< 最大値取得マクロ
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< 値交換マクロ

#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }							///< COM安全解放マクロ
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }								///< newメモリ安全解放
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }							///< new[]メモリ安全解放

#define ANGLE_TABLE_BIT						(16)																		///< サインテーブルのビット数
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)														///< サインテーブルのサイズ
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)																///< サインテーブルのアクセス用マスク
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)													///< 角度の正規化
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)													///< 度数法から専用角度
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)											///< 弧度法から専用角度
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))												///< 専用角度から弧度法

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)													///< メモリクリア
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))													///< メモリ塗りつぶし
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))													///< メモリ移動
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))													///< メモリコピー

#define MemGlobalAlloc(size)				(::VirtualAlloc( NULL, ((size)+4095)&~4095, MEM_COMMIT, PAGE_READWRITE ))					///< VirtuakAllocメモリ確保マクロ
#define MemGlobalFree(pointer)				if ( (pointer) != NULL ) { ::VirtualFree( pointer, 0, MEM_RELEASE ); (pointer) = NULL; }	///< VirtualAllocメモリ解放マクロ

#define MemLocalAlloc(size)					::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, size )										///< HeapAllocメモリ確保マクロ
#define MemLocalFree(pointer)				if ( (pointer) != NULL ) { ::HeapFree( ::GetProcessHeap(), 0, pointer ); (pointer) = NULL; }	///< HeapAllocメモリ解放マクロ


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#ifdef LIB_SELENE
#	define SELENE_DLL_API
#else // LIB_SELENE
#	ifdef DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllexport)
#	else // DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllimport)
#	endif // DLL_SELENE
#endif // LIB_SELENE


//-----------------------------------------------------------------------------------
// INTERFACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class ICore;
	class IGraphicCard;
	class IDevice;
	class IResourceFile;
	class IFileManager;
	class IMouse;
	class IKeyboard;
	class IRender;
	class IPostEffect;
	class IPointPrimitive2D;
	class ILinePrimitive2D;
	class IPrimitive2D;
	class ISprite2D;
	class IFontSprite2D;
	class IPointPrimitive3D;
	class ILinePrimitive3D;
	class IPrimitive3D;
	class IFrame;
	class IMesh;
	class IModel;
	class ISceneCamera;
	class ISceneManager;
	class ISound;
	class ISurface;
	class ITexture;

	class CVector2D;
	class CVector3D;
	class CVector4D;
	class CMatrix;
	class CStyle;
	class CQuaternion;
}

//-----------------------------------------------------------------------------------
// PROTOTYPE
//-----------------------------------------------------------------------------------
void SELENE_DLL_API GetVersioinInfo( wchar_t *pVersionStr, Uint32 Length );


#endif // ___SELENE__BASE___

