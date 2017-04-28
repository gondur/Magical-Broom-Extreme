

#ifndef ___SELENE__CSCENECAMERA___
#define ___SELENE__CSCENECAMERA___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Math.h"
#include "Math/Style.h"
#include "Object/CBaseObject.h"
#include "Interface/Scene/ISceneCamera.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief シーンカメラ
		@author 葉迩倭

		シーン管理に存在するカメラを操作するためのクラスです。
	*/
	class CSceneCamera : public CBaseObject, public ISceneCamera
	{
	protected:
		CMatrix m_mCamera;						///< ビューｘプロジェクション行列
		CMatrix m_mCameraInverse;				///< ビューｘプロジェクション逆行列
		CMatrix m_mProjection;					///< プロジェクション行列
		CMatrix m_mProjectionInverse;			///< プロジェクション逆行列
		CMatrix m_mView;						///< ビュー行列
		CMatrix m_mViewInverse;					///< ビュー逆行列
		CVector3D m_vPosition;					///< 位置

		Float m_fNearClip;						///< ニアクリップ
		Float m_fFarClip;						///< ファークリップ
		Sint32 m_FovAngle;						///< FOV角度

		CBox m_BoxOBB;							///< ビューフラスタム用バウンディングボックス

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CSceneCamera();
		virtual ~CSceneCamera();

		virtual const CMatrix &WorldToScreen( void ) const;
		virtual const CMatrix &WorldToView( void ) const;
		virtual const CMatrix &ScreenToWorld( void ) const;
		virtual const CMatrix &ViewToWorld( void ) const;
		virtual const CVector3D &Position( void ) const;

		virtual Float GetNearClip( void ) const;
		virtual Float GetFarClip( void ) const;

		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height );

		virtual void Reset( void );
		virtual void Update( void );

		virtual Bool ViewfrustumCulling( CBox &Box );

		virtual void SetTransform( CStyle &Style );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CSCENECAMERA___


