

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Scene/CSceneCamera.h"
#include "Math/Collision.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CSceneCamera::CSceneCamera()
	: m_fNearClip ( 0.0f )
	, m_fFarClip  ( 0.0f )
	, m_FovAngle  ( 0 )
{
	m_mCamera.Identity();
	m_mProjection.Identity();
	m_mView.Identity();
	m_mCameraInverse.Identity();
	m_mProjectionInverse.Identity();
	m_mViewInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CSceneCamera::~CSceneCamera()
{
}

//-----------------------------------------------------------------------------------
/**
	@brief ���[���h���X�N���[�����W�ϊ��s��擾
	@author �t���`

	@return �ϊ��s��

	���[���h��Ԃ���X�N���[�����W�ւ̋t�ϊ��s����擾���܂��B
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::WorldToScreen( void ) const
{
	return m_mCamera;
}

//-----------------------------------------------------------------------------------
/**
	@brief ���[���h���r���[�ϊ��s��擾
	@author �t���`

	@return �ϊ��s��

	���[���h��Ԃ���J������Ԃւ̋t�ϊ��s����擾���܂��B
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::WorldToView( void ) const
{
	return m_mView;
}

//-----------------------------------------------------------------------------------
/**
	@brief �X�N���[�������[���h�ϊ��s��擾
	@author �t���`

	@return �ϊ��s��

	�X�N���[�����W���烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::ScreenToWorld( void ) const
{
	return m_mCameraInverse;
}

//-----------------------------------------------------------------------------------
/**
	@brief �r���[�����[���h�ϊ��s��擾
	@author �t���`

	@return �ϊ��s��

	�J������Ԃ��烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::ViewToWorld( void ) const
{
	return m_mViewInverse;
}

const CVector3D &CSceneCamera::Position( void ) const
{
	return m_vPosition;
}

//-----------------------------------------------------------------------------------
/**
	@brief �j�A�N���b�v�l�擾
	@author �t���`

	@return �j�A�N���b�v�l

	�j�A�N���b�v�l���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Float CSceneCamera::GetNearClip( void ) const
{
	return m_fNearClip;
}

//-----------------------------------------------------------------------------------
/**
	@brief �t�@�[�N���b�v�l�擾
	@author �t���`

	@return �t�@�[�N���b�v�l

	�t�@�[�N���b�v�l���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Float CSceneCamera::GetFarClip( void ) const
{
	return m_fFarClip;
}

//-----------------------------------------------------------------------------------
/**
	@brief �v���W�F�N�V�����s��X�V
	@author �t���`

	@param fNearClip	[in] �j�A�N���b�v�l
	@param fFarClip		[in] �t�@�[�N���b�v�l
	@param FovAngle		[in] ��p�i1��65536�Ƃ����p�x�j
	@param Width		[in] �\������
	@param Height		[in] �\���c��

	�v���W�F�N�V�����s����X�V���܂��B<BR>
	�J�������g�p����ꍇ�ɂ͕K�����̊֐��Ńv���W�F�N�V�������쐬���ĉ������B<BR>
	�܂�FovAngle��0���w�肷��ƕ��s���e�ɂȂ�܂��B
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )
{
	m_fNearClip = fNearClip;
	m_fFarClip  = fFarClip;
	m_FovAngle  = FovAngle;

	// ���s���e
	if ( FovAngle == 0 )
	{
		m_mProjection.Ortho( toF(Width), toF(Height), fNearClip, fFarClip );
	}
	// �������e
	else
	{
		m_mProjection.Perspective( FovAngle, fNearClip, fFarClip, toF(Width) / toF(Height) );
	}

	// �t�s��
	m_mProjectionInverse.Inverse( m_mProjection );
}

//-----------------------------------------------------------------------------------
/**
	@brief �J�����f�[�^������
	@author �t���`

	�J�����f�[�^�����������܂��B<BR>
	���W(0,0,0)����Z��+��������������ԂɂȂ�܂��B
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::Reset( void )
{
	// Matrix
	m_mCamera.Identity();
	m_mCameraInverse.Identity();
	m_mView.Identity();
	m_mViewInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
	@brief �J�����f�[�^�X�V
	@author �t���`

	�J�����̃f�[�^���X�V���܂��B<BR>
	�e��s���o�E���f�B���O�{�b�N�X�Ȃǂ�<BR>
	���̊֐����Ăяo�����Ƃō쐬����܂��B
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::Update( void )
{
	// Matrix
	m_mCamera.Multiply( m_mView, m_mProjection );
	m_mCameraInverse.Multiply( m_mProjectionInverse, m_mViewInverse );

	// Update Bounding
	CVector3D vMin( -1.0f, -1.0f,  0.0f );
	CVector3D vMax( +1.0f, +1.0f, +1.0f );
	Collision::CreateBoxProjection( m_BoxOBB, vMin, vMax, m_mCameraInverse );
}

//-----------------------------------------------------------------------------------
/**
	@brief �J������ϊ�
	@author �t���`

	@param Style	[in] �J�����ϊ��pCStyle

	Ctyle�f�[�^�Œ�`���ꂽ�ϊ�������<BR>
	�J�����ɓK�p���܂��B<BR>
	�J�����Ŏg�p�����͈̂ړ�/��]�ɂȂ�܂��B
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::SetTransform( CStyle &Style )
{
	Style.GetTransformInverse( m_mView );
	Style.GetTransform( m_mViewInverse );

	Style.GetPosition( m_vPosition );
}

//-----------------------------------------------------------------------------------
/**
	@brief �r���[�t���X�^���J�����O�J�����O
	@author �t���`

	@param Style	[in] �J�����ϊ��pCStyle

	Ctyle�f�[�^�Œ�`���ꂽ�ϊ�������<BR>
	�J�����ɓK�p���܂��B<BR>
	�J�����Ŏg�p�����͈̂ړ�/��]�ɂȂ�܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSceneCamera::ViewfrustumCulling( CBox &Box )
{
	return Collision::Box_Box_3D( m_BoxOBB, Box );
}

#endif // ENABLE_3D
