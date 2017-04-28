

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
		@brief 行列クラス
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
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix();

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix( CMatrix &Mat );

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix( SMatrix4x4 &Mat );

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix( CQuaternion &In );

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief 行列の単位化
			@author 葉迩倭
		*/
		void Identity( void );

		/**
			@brief 行列の転置化
			@author 葉迩倭
			@param In	[in] 処理元行列
		*/
		void Transpose( CMatrix &In );

		/**
			@brief 行列の逆行列化
			@author 葉迩倭
			@param In	[in] 処理元行列
		*/
		void Inverse( CMatrix &In );

		/**
			@brief 行列の合成
			@author 葉迩倭
			@param In1		[in] 合成元行列１
			@param In2		[in] 合成元行列２
		*/
		void Multiply( CMatrix &In1, CMatrix &In2 );

		/**
			@brief 行列の転置行列化
			@author 葉迩倭
		*/
		void Transpose( void );

		/**
			@brief 行列の逆行列化
			@author 葉迩倭
		*/
		void Inverse( void );

		/**
			@brief 行列の合成
			@author 葉迩倭
			@param In	[in] 合成元行列
		*/
		void Multiply( CMatrix &In );

		/**
			@brief Ｘ軸回転角度
			@author 葉迩倭
			@param Angle	[in] 回転角度
		*/
		void RotationX( Sint32 Angle );

		/**
			@brief Ｙ軸回転角度
			@author 葉迩倭
			@param Angle	[in] 回転角度
		*/
		void RotationY( Sint32 Angle );

		/**
			@brief Ｚ軸回転角度
			@author 葉迩倭
			@param Angle	[in] 回転角度
		*/
		void RotationZ( Sint32 Angle );

		/**
			@brief ＺＸＹ回転行列を生成
			@author 葉迩倭
			@param AngleX	[in] Ｘ軸回転角度
			@param AngleY	[in] Ｙ軸回転角度
			@param AngleZ	[in] Ｚ軸回転角度
		*/
		void RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief 任意軸回転
			@author 葉迩倭
			@param Angle	[in] 角度
			@param Axis		[in] 回転軸
		*/
		void RotationAxis( Sint32 Angle, CVector3D &Axis );

		/**
			@brief 拡大縮小行列生成
			@author 葉迩倭
			@param sx	[in] Ｘ方向拡大率
			@param sy	[in] Ｙ方向拡大率
			@param sz	[in] Ｚ方向拡大率
		*/
		void Scaling( Float sx, Float sy, Float sz );

		/**
			@brief 移動行列生成
			@author 葉迩倭
			@param px	[in] Ｘ位置
			@param py	[in] Ｙ位置
			@param pz	[in] Ｚ位置
		*/
		void Translation( Float px, Float py, Float pz );

		/**
			@brief 透視変換用行列生成
			@author 葉迩倭
			@param Fov		[in] 画角
			@param NearZ	[in] 近接クリップ面
			@param FarZ		[in] 遠方クリップ面
			@param Aspect	[in] アスペクト比（＝描画エリア横幅÷描画エリア縦幅）
		*/
		void Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief 並行投影用行列生成
			@author 葉迩倭
			@param Width	[in] 横幅
			@param Height	[in] 縦幅
			@param NearZ	[in] 近接クリップ面
			@param FarZ		[in] 遠方クリップ面
		*/
		void Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief 任意点注視行列作成
			@author 葉迩倭
			@param Eye	[in] 視点
			@param At	[in] 注視点
			@param Up	[in] 上方向
		*/
		void LookAt( CVector3D &Eye, CVector3D &At, CVector3D &Up );

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 & ();

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 & () const;

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 * ();

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 * () const;

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix &operator = ( const CMatrix &In );	

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix &operator = ( const CQuaternion &In );

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix  operator * ( const CMatrix &In );	

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix &operator *= ( const CMatrix &In );	
	};
}

#endif // ___SELENE__MATRIX___

