

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
		@brief �p������N���X
	*/
	class SELENE_DLL_API CStyle
	{
	private:
		CMatrix m_mStyle;												///< �p���p�s��
		CMatrix m_mStyleInverse;										///< �p���̋t�s��
		CMatrix m_mTransform;											///< �ϊ��s��
		CMatrix m_mTransformInverse;									///< �ϊ��s��̋t�s��
		CVector3D m_vUp;												///< ������x�N�g��
		CVector3D m_vRight;												///< �E�����x�N�g��
		CVector3D m_vFront;												///< �O�����x�N�g��
		CVector3D m_vPosition;											///< �ʒu�x�N�g��
		CVector3D m_vScale;												///< �g��k���x�N�g��

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


