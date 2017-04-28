

#ifndef ___SELENE__MATH___
#define ___SELENE__MATH___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief sin�擾
		@author �t���`
		@param Angle	[in] 1��65536�Ƃ����p�x
		@return sin�l

		sin�l���擾���܂��B
	*/
	SELENE_DLL_API Float Sin( Sint32 Angle );

	/**
		@brief cos�擾
		@author �t���`
		@param Angle	[in] 1��65536�Ƃ����p�x
		@return cos�l

		cos�l���擾���܂��B
	*/
	SELENE_DLL_API Float Cos( Sint32 Angle );

	/**
		@brief atan2�擾
		@author �t���`
		@param Dx	[in] �w����
		@param Dy	[in] �x����
		@return X-Y�̐����p�x

		X,Y���狁�߂���atan2�̒l��Selene�̊p�x�P�ʂ�<BR>
		���킹���l�Ŏ擾���܂��B
	*/
	SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );
}

	/**
		@brief ��`�f�[�^
		@author �t���`
	*/
	template <typename Type>
	class CRect2D
	{
	public:
		Type x;					///< �w�n�_���W
		Type y;					///< �x�n�_���W
		Type w;					///< �w�T�C�Y
		Type h;					///< �x�T�C�Y

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRect2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w�n�_���W
			@param y		[in] �x�n�_���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
		*/
		CRect2D( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	/**
		@brief �Q�����̓_
		@author �t���`
	*/
	template <typename Type>
	class CPoint2D
	{
	public:
		Type x;					///< �w���W
		Type y;					///< �x���W

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPoint2D(){}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
		*/
		CPoint2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator + ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x + Pt.x, this->y + Py.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator - ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x - Pt.x, this->y - Py.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator * ( Type Mul )
		{
			return CPoint2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator / ( Type Div )
		{
			return CPoint2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator += ( CPoint2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator -= ( CPoint2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> Rotate( Sint32 Angle )
		{
			Float fSin = Math::Sin( Angle );
			Float fCos = Math::Cos( Angle );

			Float fPx = (fCos * toF(this->x)) - (fSin * toF(this->y));
			Float fPy = (fSin * toF(this->x)) + (fCos * toF(this->y));

			return CPoint2D<Type>( (Type)fPx, (Type)fPy );
		}
	};

	/**
		@brief �R�����̓_
	*/
	template <typename Type>
	struct CPoint3D
	{
		Type x;							///< �w�ʒu
		Type y;							///< �x�ʒu
		Type z;							///< �y�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPoint3D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
		*/
		CPoint3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator + ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x + Pt.x, this->y + Py.y, this->z + Py.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator - ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x - Pt.x, this->y - Py.y, this->z - Py.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator * ( Type Mul )
		{
			return CPoint3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator / ( Type Div )
		{
			return CPoint3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator += ( CPoint3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator -= ( CPoint3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			this->z /= Div;
			return *this;
		}
	};

	/**
		@brief �Q������̉~
		@author �t���`
	*/
	struct CCircle
	{
		CVector2D Center;				///< �~�̒��S
		Float Radius;					///< �~�̔��a

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CCircle()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param r		[in] ���a
		*/
		CCircle( Float x, Float y, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Radius = r;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CCircle( CVector2D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief �R������̋�
		@author �t���`
	*/
	struct CSphere
	{
		CVector3D Center;					///< ���̒��S
		Float Radius;							///< ���̔��a

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CSphere()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
			@param r		[in] ���a
		*/
		CSphere( Float x, Float y, Float z, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Center.z = z;
			this->Radius = r;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CSphere( CVector3D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief �Q�����̐���
		@author �t���`
	*/
	struct CLine2D
	{
		CVector2D Pt0;						///< �����n�_�ʒu
		CVector2D Pt1;						///< �����I�_�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0		[in] �����̒��_�P
			@param pt1		[in] �����̒��_�Q
		*/
		CLine2D( CVector2D &pt0, CVector2D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief �Q�����̑��p�`
		@author �t���`
	*/
	struct CPolygon2D
	{
		Uint32 Count;								///< �|�C���g�z��̃|�C���g��
		CVector2D *pPts;						///< �|���S����\�����߂̃|�C���g�z��̃|�C���^

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPolygon2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param Cnt		[in] ���_��
			@param pPt		[in] ���_�̔z��
		*/
		CPolygon2D( Uint32 Cnt, CVector2D *pPt )
		{
			this->Count = Cnt;
			this->pPts = pPt;
		}
	};

	/**
		@brief �R�����̐���
		@author �t���`
	*/
	struct CLine3D
	{
		CVector3D Pt0;						///< �����n�_�ʒu
		CVector3D Pt1;						///< �����I�_�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine3D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param z0		[in] �y���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
			@param z1		[in] �y���W
		*/
		CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt0.z = z0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
			this->Pt1.z = z1;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0	[in] �����̒��_�P
			@param pt1	[in] �����̒��_�Q
		*/
		CLine3D( CVector3D &pt0, CVector3D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief �R�����̕���
		@author �t���`
	*/
	struct CPlane
	{
		Float a;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W��
		Float b;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W��
		Float c;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W��
		Float d;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPlane()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param a	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W��
			@param b	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W��
			@param c	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W��
			@param d	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��
		*/
		CPlane( Float a, Float b, Float c, Float d )
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}

		/**
			@brief �@���f�[�^���琶��
			@author �t���`

			@param Pt		[in] ���ʏ��1�_
			@param vNormal	[in] ���ʂ̖@��
		*/
		void FromNormal( CVector3D &Pt, CVector3D &vNormal )
		{
			CVector3D vNrm;
			vNrm.Normalize( vNormal );
			a = vNrm.x;
			b = vNrm.y;
			c = vNrm.z;
			d = -Pt.Dot( vNrm );
		};

		/**
			@brief ���ʏ�̂R�_���琶��
			@author �t���`

			@param Pt0		[in] ���ʏ��1�_
			@param Pt1		[in] ���ʏ��1�_
			@param Pt2		[in] ���ʏ��1�_
		*/
		void FromPoint( CVector3D &vPt0, CVector3D &vPt1, CVector3D &vPt2 )
		{
			CVector3D vEdge0 = vPt1 - vPt0;
			CVector3D vEdge1 = vPt2 - vPt0;
			CVector3D vNormal;
			vNormal.Cross( vEdge0, vEdge1 );
			FromNormal( vPt0, vNormal );
		}

		/**
			@brief ����
			@author �t���`

			@param Pt	[in] �C�ӂ̓_

			���ʂƔC�ӂ̓_�̓��ς��Ƃ�܂��B
		*/
		Float Dot( CVector3D &Pt, Float w = 1.0f )
		{
			return (a * Pt.x) + (b * Pt.y) + (c * Pt.z) + (w * d);
		}
	};

	/**
		@brief �R������̔�
		@author �t���`
	*/
	struct CBox
	{
	public:
		CVector3D Points[8];	///< ���̊e�p��\�����_�f�[�^
		CPlane Planes[6];		///< ���̊e�ʂ�\���ʃf�[�^

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CBox()
		{
		}

		/**
			@brief ���_�f�[�^���畽�ʃf�[�^����
			@author �t���`
		*/
		void Update( void )
		{
			Planes[0].FromPoint( Points[0], Points[1], Points[2] );
			Planes[1].FromPoint( Points[6], Points[5], Points[4] );
			Planes[2].FromPoint( Points[5], Points[6], Points[2] );
			Planes[3].FromPoint( Points[7], Points[4], Points[0] );
			Planes[4].FromPoint( Points[3], Points[2], Points[6] );
			Planes[5].FromPoint( Points[4], Points[5], Points[1] );
		}
	};
}


#endif // ___SELENE__MATH___

