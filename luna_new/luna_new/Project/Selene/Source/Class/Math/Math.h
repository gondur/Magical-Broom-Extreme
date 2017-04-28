

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
		@brief sin取得
		@author 葉迩倭
		@param Angle	[in] 1周65536とした角度
		@return sin値

		sin値を取得します。
	*/
	SELENE_DLL_API Float Sin( Sint32 Angle );

	/**
		@brief cos取得
		@author 葉迩倭
		@param Angle	[in] 1周65536とした角度
		@return cos値

		cos値を取得します。
	*/
	SELENE_DLL_API Float Cos( Sint32 Angle );

	/**
		@brief atan2取得
		@author 葉迩倭
		@param Dx	[in] Ｘ距離
		@param Dy	[in] Ｙ距離
		@return X-Yの成す角度

		X,Yから求められるatan2の値をSeleneの角度単位に<BR>
		あわせた値で取得します。
	*/
	SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );
}

	/**
		@brief 矩形データ
		@author 葉迩倭
	*/
	template <typename Type>
	class CRect2D
	{
	public:
		Type x;					///< Ｘ始点座標
		Type y;					///< Ｙ始点座標
		Type w;					///< Ｘサイズ
		Type h;					///< Ｙサイズ

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CRect2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ始点座標
			@param y		[in] Ｙ始点座標
			@param w		[in] Ｘサイズ
			@param h		[in] Ｙサイズ
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
		@brief ２次元の点
		@author 葉迩倭
	*/
	template <typename Type>
	class CPoint2D
	{
	public:
		Type x;					///< Ｘ座標
		Type y;					///< Ｙ座標

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPoint2D(){}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
		*/
		CPoint2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator + ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x + Pt.x, this->y + Py.y );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator - ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x - Pt.x, this->y - Py.y );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator * ( Type Mul )
		{
			return CPoint2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator / ( Type Div )
		{
			return CPoint2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator += ( CPoint2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator -= ( CPoint2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
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
		@brief ３次元の点
	*/
	template <typename Type>
	struct CPoint3D
	{
		Type x;							///< Ｘ位置
		Type y;							///< Ｙ位置
		Type z;							///< Ｚ位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPoint3D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param z		[in] Ｚ座標
		*/
		CPoint3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator + ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x + Pt.x, this->y + Py.y, this->z + Py.z );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator - ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x - Pt.x, this->y - Py.y, this->z - Py.z );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator * ( Type Mul )
		{
			return CPoint3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator / ( Type Div )
		{
			return CPoint3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator += ( CPoint3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator -= ( CPoint3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
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
		@brief ２次元上の円
		@author 葉迩倭
	*/
	struct CCircle
	{
		CVector2D Center;				///< 円の中心
		Float Radius;					///< 円の半径

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CCircle()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param r		[in] 半径
		*/
		CCircle( Float x, Float y, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Radius = r;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param c		[in] 中心座標
			@param r		[in] 半径
		*/
		CCircle( CVector2D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief ３次元上の球
		@author 葉迩倭
	*/
	struct CSphere
	{
		CVector3D Center;					///< 球の中心
		Float Radius;							///< 球の半径

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CSphere()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param z		[in] Ｚ座標
			@param r		[in] 半径
		*/
		CSphere( Float x, Float y, Float z, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Center.z = z;
			this->Radius = r;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param c		[in] 中心座標
			@param r		[in] 半径
		*/
		CSphere( CVector3D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief ２次元の線分
		@author 葉迩倭
	*/
	struct CLine2D
	{
		CVector2D Pt0;						///< 線分始点位置
		CVector2D Pt1;						///< 線分終点位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CLine2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x0		[in] Ｘ座標
			@param y0		[in] Ｙ座標
			@param x1		[in] Ｘ座標
			@param y1		[in] Ｙ座標
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param pt0		[in] 線分の頂点１
			@param pt1		[in] 線分の頂点２
		*/
		CLine2D( CVector2D &pt0, CVector2D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief ２次元の多角形
		@author 葉迩倭
	*/
	struct CPolygon2D
	{
		Uint32 Count;								///< ポイント配列のポイント数
		CVector2D *pPts;						///< ポリゴンを表すためのポイント配列のポインタ

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPolygon2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param Cnt		[in] 頂点数
			@param pPt		[in] 頂点の配列
		*/
		CPolygon2D( Uint32 Cnt, CVector2D *pPt )
		{
			this->Count = Cnt;
			this->pPts = pPt;
		}
	};

	/**
		@brief ３次元の線分
		@author 葉迩倭
	*/
	struct CLine3D
	{
		CVector3D Pt0;						///< 線分始点位置
		CVector3D Pt1;						///< 線分終点位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CLine3D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x0		[in] Ｘ座標
			@param y0		[in] Ｙ座標
			@param z0		[in] Ｚ座標
			@param x1		[in] Ｘ座標
			@param y1		[in] Ｙ座標
			@param z1		[in] Ｚ座標
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
			@brief コンストラクタ
			@author 葉迩倭

			@param pt0	[in] 線分の頂点１
			@param pt1	[in] 線分の頂点２
		*/
		CLine3D( CVector3D &pt0, CVector3D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief ３次元の平面
		@author 葉迩倭
	*/
	struct CPlane
	{
		Float a;							///< 一般平面方程式におけるクリップ面の a 係数
		Float b;							///< 一般平面方程式におけるクリップ面の b 係数
		Float c;							///< 一般平面方程式におけるクリップ面の c 係数
		Float d;							///< 一般平面方程式におけるクリップ面の d 係数

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPlane()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param a	[in] 一般平面方程式におけるクリップ面の a 係数
			@param b	[in] 一般平面方程式におけるクリップ面の b 係数
			@param c	[in] 一般平面方程式におけるクリップ面の c 係数
			@param d	[in] 一般平面方程式におけるクリップ面の d 係数
		*/
		CPlane( Float a, Float b, Float c, Float d )
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}

		/**
			@brief 法線データから生成
			@author 葉迩倭

			@param Pt		[in] 平面上の1点
			@param vNormal	[in] 平面の法線
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
			@brief 平面上の３点から生成
			@author 葉迩倭

			@param Pt0		[in] 平面上の1点
			@param Pt1		[in] 平面上の1点
			@param Pt2		[in] 平面上の1点
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
			@brief 内積
			@author 葉迩倭

			@param Pt	[in] 任意の点

			平面と任意の点の内積をとります。
		*/
		Float Dot( CVector3D &Pt, Float w = 1.0f )
		{
			return (a * Pt.x) + (b * Pt.y) + (c * Pt.z) + (w * d);
		}
	};

	/**
		@brief ３次元上の箱
		@author 葉迩倭
	*/
	struct CBox
	{
	public:
		CVector3D Points[8];	///< 箱の各角を表す頂点データ
		CPlane Planes[6];		///< 箱の各面を表す面データ

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CBox()
		{
		}

		/**
			@brief 頂点データから平面データ生成
			@author 葉迩倭
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

