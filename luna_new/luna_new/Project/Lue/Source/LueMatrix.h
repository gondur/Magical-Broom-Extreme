
#ifndef ___LUE_MATRIX_H___
#define ___LUE_MATRIX_H___


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


//=============================================================================
// for C++
//=============================================================================
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ___LUE_MATRIX_H___

