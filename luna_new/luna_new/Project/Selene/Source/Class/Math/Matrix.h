

#ifndef ___SELENE__MATRIX___
#define ___SELENE__MATRIX___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Vector4D.h"
#include "Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	struct SMatrix4x4
	{
		CVector4D x;
		CVector4D y;
		CVector4D z;
		CVector4D w;
	};

	/**
		@brief �s��N���X
	*/
	class SELENE_DLL_API CMatrix
	{
	private:
		Uint8 m_Data[sizeof(SMatrix4x4) + 16];
		SMatrix4x4 &Mtx;

	public:
		CVector4D &x;
		CVector4D &y;
		CVector4D &z;
		CVector4D &w;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix( CMatrix &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix( SMatrix4x4 &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix( CQuaternion &In );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief �s��̒P�ʉ�
			@author �t���`
		*/
		void Identity( void );

		/**
			@brief �s��̓]�u��
			@author �t���`
			@param In	[in] �������s��
		*/
		void Transpose( CMatrix &In );

		/**
			@brief �s��̋t�s��
			@author �t���`
			@param In	[in] �������s��
		*/
		void Inverse( CMatrix &In );

		/**
			@brief �s��̍���
			@author �t���`
			@param In1		[in] �������s��P
			@param In2		[in] �������s��Q
		*/
		void Multiply( CMatrix &In1, CMatrix &In2 );

		/**
			@brief �s��̓]�u�s��
			@author �t���`
		*/
		void Transpose( void );

		/**
			@brief �s��̋t�s��
			@author �t���`
		*/
		void Inverse( void );

		/**
			@brief �s��̍���
			@author �t���`
			@param In	[in] �������s��
		*/
		void Multiply( CMatrix &In );

		/**
			@brief �w����]�p�x
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		void RotationX( Sint32 Angle );

		/**
			@brief �x����]�p�x
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		void RotationY( Sint32 Angle );

		/**
			@brief �y����]�p�x
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		void RotationZ( Sint32 Angle );

		/**
			@brief �y�w�x��]�s��𐶐�
			@author �t���`
			@param AngleX	[in] �w����]�p�x
			@param AngleY	[in] �x����]�p�x
			@param AngleZ	[in] �y����]�p�x
		*/
		void RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief �C�ӎ���]
			@author �t���`
			@param Angle	[in] �p�x
			@param Axis		[in] ��]��
		*/
		void RotationAxis( Sint32 Angle, CVector3D &Axis );

		/**
			@brief �g��k���s�񐶐�
			@author �t���`
			@param sx	[in] �w�����g�嗦
			@param sy	[in] �x�����g�嗦
			@param sz	[in] �y�����g�嗦
		*/
		void Scaling( Float sx, Float sy, Float sz );

		/**
			@brief �ړ��s�񐶐�
			@author �t���`
			@param px	[in] �w�ʒu
			@param py	[in] �x�ʒu
			@param pz	[in] �y�ʒu
		*/
		void Translation( Float px, Float py, Float pz );

		/**
			@brief �����ϊ��p�s�񐶐�
			@author �t���`
			@param Fov		[in] ��p
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
			@param Aspect	[in] �A�X�y�N�g��i���`��G���A�������`��G���A�c���j
		*/
		void Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief ���s���e�p�s�񐶐�
			@author �t���`
			@param Width	[in] ����
			@param Height	[in] �c��
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
		*/
		void Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief �C�ӓ_�����s��쐬
			@author �t���`
			@param Eye	[in] ���_
			@param At	[in] �����_
			@param Up	[in] �����
		*/
		void LookAt( CVector3D &Eye, CVector3D &At, CVector3D &Up );

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 & ();

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 & () const;

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 * ();

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 * () const;

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix &operator = ( const CMatrix &In );	

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix &operator = ( const CQuaternion &In );

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix  operator * ( const CMatrix &In );	

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix &operator *= ( const CMatrix &In );	
	};
}

#endif // ___SELENE__MATRIX___

