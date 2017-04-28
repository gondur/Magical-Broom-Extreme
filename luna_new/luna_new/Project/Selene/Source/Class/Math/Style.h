

#ifndef ___SELENE__STYLE___
#define ___SELENE__STYLE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief 姿勢制御クラス
	*/
	class SELENE_DLL_API CStyle
	{
	private:
		CMatrix m_mStyle;												///< 姿勢用行列
		CMatrix m_mStyleInverse;										///< 姿勢の逆行列
		CMatrix m_mTransform;											///< 変換行列
		CMatrix m_mTransformInverse;									///< 変換行列の逆行列
		CVector3D m_vUp;												///< 上方向ベクトル
		CVector3D m_vRight;												///< 右方向ベクトル
		CVector3D m_vFront;												///< 前方向ベクトル
		CVector3D m_vPosition;											///< 位置ベクトル
		CVector3D m_vScale;												///< 拡大縮小ベクトル

	public:
		CStyle();
		CStyle( const CStyle &Style );

		virtual void TransformReset( void );
		virtual void TransformUpdate( void );

		virtual void RotationX( Sint32 Rot );
		virtual void RotationY( Sint32 Rot );
		virtual void RotationZ( Sint32 Rot );
		virtual void Pitching( Sint32 Rot );
		virtual void Heading( Sint32 Rot );
		virtual void Rolling( Sint32 Rot );
		virtual void RotationQuaternion( CQuaternion &Quat );
		virtual void Translation( Float fPx, Float fPy, Float fPz );
		virtual void Scaling( Float fSx, Float fSy, Float fSz );
		virtual void LookAt( CVector3D &vEye, CVector3D &vAt, CVector3D &vUp );
		virtual void FromMatrix( CMatrix &Mat );
		virtual Sint32 GetAngleX( void );
		virtual Sint32 GetAngleY( void );
		virtual Sint32 GetAngleZ( void );
		virtual void SetPosition( CVector3D &Pos );
		virtual void SetFront( CVector3D &Vec );
		virtual void SetRight( CVector3D &Vec );
		virtual void SetUp( CVector3D &Vec );
		virtual void GetPosition( CVector3D &Pos );
		virtual void GetFront( CVector3D &Vec );
		virtual void GetRight( CVector3D &Vec );
		virtual void GetUp( CVector3D &Vec );
		virtual void GetStyle( CMatrix &Mat );
		virtual void GetStyleInverse( CMatrix &Mat );
		virtual void GetTransform( CMatrix &Mat );
		virtual void GetTransformInverse( CMatrix &Mat );

		virtual CStyle &operator = ( const CStyle &In );
	};
}


#endif // ___SELENE__STYLE___


