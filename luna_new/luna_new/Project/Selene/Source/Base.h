//------------------------------------------------------------------------------//
//                       DirectX9�p���C�u���� Selene                            //
//------------------------------------------------------------------------------//
//                                                                              //
//  �ŐV�ł̒u���Ă���URL                                                       //
//    TWINTAIL LOVERS.                                                          //
//      http://www.twin-tail.jp/                                                //
//                                                                              //
//  ���ⓙ�����ꏊ                                                              //
//    BBS                                                                       //
//      TWINTAIL LOVERS.���̌f����                                              //
//                                                                              //
//                                                  DirectX Library 'Selene'    //
//                                                  Copyright (C) 2006 �t���`   //
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
typedef char					Sint8;								///< signed char �^�̕ʒ�`
typedef short					Sint16;								///< signed short �^�̕ʒ�`
typedef long					Sint32;								///< signed long �^�̕ʒ�`
typedef __int64					Sint64;								///< signed __int64 �^�̕ʒ�`
typedef unsigned char			Uint8;								///< unsigned char �^�̕ʒ�`
typedef unsigned short			Uint16;								///< unsigned short �^�̕ʒ�`
typedef unsigned long			Uint32;								///< unsigned long �^�̕ʒ�`
typedef unsigned __int64		Uint64;								///< unsigned __int64 �^�̕ʒ�`
typedef float					Float;								///< Float �^�̕ʒ�`
typedef float					Float32;							///< Float �^�̕ʒ�`
typedef double					Float64;							///< double �^�̕ʒ�`
typedef long double				Float80;							///< long double �^�̕ʒ�`
typedef bool					Bool;								///< Bool �^�̕ʒ�`

typedef void					*FX_HANDLE;							///< �G�t�F�N�g�t�@�C���̃n���h��


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define ef									else if																		///< else if �ȗ��p�}�N��

#define toF(val)							((Float)(val))																///< Float�^�ւ̃L���X�g�}�N��
#define toI(val)							((Sint32)(val))																///< Sint32�^�ւ̃L���X�g�}�N��

#define PI									(3.141592653589793238462643383279f)											///< ��
#define PI2									(6.283185307179586476925286766559f)											///< 2��
#define REV(val)							toF(1.0f/toF(val))															///< �t���Z�o�}�N��

#define SHADER_BONE_MAX						(48)

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))													///< �ŏ��l�擾�}�N��
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))													///< �ő�l�擾�}�N��
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< �l�����}�N��

#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }							///< COM���S����}�N��
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }								///< new���������S���
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }							///< new[]���������S���

#define ANGLE_TABLE_BIT						(16)																		///< �T�C���e�[�u���̃r�b�g��
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)														///< �T�C���e�[�u���̃T�C�Y
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)																///< �T�C���e�[�u���̃A�N�Z�X�p�}�X�N
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)													///< �p�x�̐��K��
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)													///< �x���@�����p�p�x
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)											///< �ʓx�@�����p�p�x
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))												///< ��p�p�x����ʓx�@

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)													///< �������N���A
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))													///< �������h��Ԃ�
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))													///< �������ړ�
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))													///< �������R�s�[

#define MemGlobalAlloc(size)				(::VirtualAlloc( NULL, ((size)+4095)&~4095, MEM_COMMIT, PAGE_READWRITE ))					///< VirtuakAlloc�������m�ۃ}�N��
#define MemGlobalFree(pointer)				if ( (pointer) != NULL ) { ::VirtualFree( pointer, 0, MEM_RELEASE ); (pointer) = NULL; }	///< VirtualAlloc����������}�N��

#define MemLocalAlloc(size)					::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, size )										///< HeapAlloc�������m�ۃ}�N��
#define MemLocalFree(pointer)				if ( (pointer) != NULL ) { ::HeapFree( ::GetProcessHeap(), 0, pointer ); (pointer) = NULL; }	///< HeapAlloc����������}�N��


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

