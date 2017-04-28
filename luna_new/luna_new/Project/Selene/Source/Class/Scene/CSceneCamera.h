

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
		@brief �V�[���J����
		@author �t���`

		�V�[���Ǘ��ɑ��݂���J�����𑀍삷�邽�߂̃N���X�ł��B
	*/
	class CSceneCamera : public CBaseObject, public ISceneCamera
	{
	protected:
		CMatrix m_mCamera;						///< �r���[���v���W�F�N�V�����s��
		CMatrix m_mCameraInverse;				///< �r���[���v���W�F�N�V�����t�s��
		CMatrix m_mProjection;					///< �v���W�F�N�V�����s��
		CMatrix m_mProjectionInverse;			///< �v���W�F�N�V�����t�s��
		CMatrix m_mView;						///< �r���[�s��
		CMatrix m_mViewInverse;					///< �r���[�t�s��
		CVector3D m_vPosition;					///< �ʒu

		Float m_fNearClip;						///< �j�A�N���b�v
		Float m_fFarClip;						///< �t�@�[�N���b�v
		Sint32 m_FovAngle;						///< FOV�p�x

		CBox m_BoxOBB;							///< �r���[�t���X�^���p�o�E���f�B���O�{�b�N�X

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


