

#ifndef ___SELENE__CSCENEMANAGER___
#define ___SELENE__CSCENEMANAGER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Render/CRender.h"
#include "Render/CRenderData.h"
#include "Scene/CSceneObject.h"
#include "Scene/CSceneCamera.h"
#include "Object/CBaseObject.h"
#include "Thread/CThread.h"
#include "Thread/CEvent.h"
#include "Thread/CCriticalSection.h"
#include "Interface/Scene/ISceneManager.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class COcclusion;

	/**
		@brief �o�E���f�B���O�f�[�^
		@author �t���`
	*/
	class CSceneBounding
	{
	public:
		CMatrix Matrix;

		CVector3D vCenter;
		CVector3D vAxis[3];
		Float fLength[3];

		Float fRadius;

		CVector3D vPoint[8];

	public:
		CSceneBounding() {
			Matrix.Identity();
			vCenter		= CVector3D( 0.0f, 0.0f, 0.0f );
			vAxis[0]	= CVector3D( 0.0f, 0.0f, 1.0f );
			vAxis[1]	= CVector3D( 0.0f, 1.0f, 0.0f );
			vAxis[2]	= CVector3D( 1.0f, 0.0f, 0.0f );
			fLength[0]	= 0.001f;
			fLength[1]	= 0.001f;
			fLength[2]	= 0.001f;

			UpdatePoints();
			UpdateRadius();
		}

		void SetAxis( CVector3D &vCenter, CVector3D &Axis0, CVector3D &Axis1, CVector3D &Axis2 )
		{
			this->vCenter  = vCenter;
			this->vAxis[0] = Axis0;
			this->vAxis[1] = Axis1;
			this->vAxis[2] = Axis2;
		}

		void SetLength( Float fLength0, Float fLength1, Float fLength2 )
		{
			fLength[0] = fLength0;
			fLength[1] = fLength1;
			fLength[2] = fLength2;
		}

		void UpdateMatrix( void )
		{
			CVector3D Axis[3] = {
				vAxis[0] * fLength[0] * 0.5f,
				vAxis[1] * fLength[1] * 0.5f,
				vAxis[2] * fLength[2] * 0.5f,
			};

			// ���ʓ��e�p
			CVector3D G = vCenter - Axis[0] - Axis[1] - Axis[2];
			Matrix = CMatrix(
						vAxis[0].x, vAxis[0].y, vAxis[0].z, -vAxis[0].Dot( G ),
						vAxis[1].x, vAxis[1].y, vAxis[1].z, -vAxis[1].Dot( G ),
						vAxis[2].x, vAxis[2].y, vAxis[2].z, -vAxis[2].Dot( G ),
						0.0f, 0.0f, 0.0f, 1.0f );
		}

		void UpdatePoints( void )
		{
			CVector3D Axis[3] = {
				vAxis[0] * fLength[0] * 0.5f,
				vAxis[1] * fLength[1] * 0.5f,
				vAxis[2] * fLength[2] * 0.5f,
			};
			// �{�b�N�X���\�����钸�_�f�[�^
			vPoint[0] = vCenter - Axis[0] - Axis[1] - Axis[2];
			vPoint[1] = vCenter - Axis[0] + Axis[1] - Axis[2];
			vPoint[2] = vCenter - Axis[0] + Axis[1] + Axis[2];
			vPoint[3] = vCenter - Axis[0] - Axis[1] + Axis[2];
			vPoint[4] = vCenter + Axis[0] - Axis[1] - Axis[2];
			vPoint[5] = vCenter + Axis[0] + Axis[1] - Axis[2];
			vPoint[6] = vCenter + Axis[0] + Axis[1] + Axis[2];
			vPoint[7] = vCenter + Axis[0] - Axis[1] + Axis[2];
		}

		void UpdateRadius( void )
		{
			fRadius = 0.0f;

			for ( Uint32 i = 0; i < 8; i++ )
			{
				CVector3D vTemp = vPoint[0] - vCenter;
				Float fLen2 = vTemp.LengthSq();
				if ( fRadius < fLen2 )
				{
					fRadius = fLen2;
				}
			}

			fRadius = sqrtf( fRadius );
		}
	};

	/**
		@brief �V�[�������_�����O�p�I�u�W�F�N�g
		@author �t���`
	*/
	struct SSceneRenderObject
	{
		CRenderData RenderData;					///< �����_�����O�p�V�F�[�_�[�f�[�^
		CSceneObject *pObject;					///< �V�[���p�I�u�W�F�N�g
		COcclusion *pOcclusion;					///< �I�N���[�W�����p
		CVector3D vCenter;						///< ���S�ʒu
		Float fKey;								///< �\�[�g�L�[
		Bool IsFog;								///< �t�H�O�̗L��

		SSceneRenderObject *pNext;				///< ���X�g�p�|�C���^

		CMatrix mWorldView;						///< �V�F�[�_�[�ɓ]������ϊ��s��
		CMatrix mWorldViewProjection;			///< �V�F�[�_�[�ɓ]������ϊ��s��
		CMatrix mShadowWorldViewProjection;		///< �V�F�[�_�[�ɓ]������ϊ��s��

		CVector4D vShadowMapTransform;			///< �V�F�[�_�[�ɓ]������[�x�擾�x�N�g��
		CVector4D vDepthTransform;				///< �V�F�[�_�[�ɓ]������[�x�擾�x�N�g��
		CVector4D vLightDiection;				///< �V�F�[�_�[�ɓ]������f�B���N�V���i�����C�g�F���C�g����
		CVector4D vPointLightPositionTbl[4];	///< �V�F�[�_�[�ɓ]������|�C���g���C�g�ʒu�e�[�u��
		CVector4D vPointLightColorTbl[4];		///< �V�F�[�_�[�ɓ]������|�C���g���C�g�F�e�[�u��
		Sint32 PointLightCount;					///< �V�F�[�_�[�ɓ]������|�C���g���C�g��
	};

	/**
		@brief �V�[���Ǘ��N���X
		@author �t���`

		3D��Ԃ��Ǘ����邽�߂̃N���X�ł��B
	*/
	class CSceneManager : public CBaseObject, public ISceneManager
	{
		enum {
			SCENE_MANAGER_EVENT_MAX = 2,
			SCENE_MANAGER_QUE_MAX = 1024,
			LIGHT_POINT_MAX = 64,
			LIGHT_DIRECTION,
			LIGHT_AMBIENT_SKY,
			LIGHT_AMBIENT_EARTH,
			LIGHT_MAX,
			POINT_LIGHT_VALID_MAX = 4,
		};

		enum {
			EVENT_NO_EXIT,
			EVENT_NO_QUEEND,
		};

		friend CRender;

	protected:
		Bool m_IsBegin;											///< �V�[���J�n�����ۂ�
		Bool m_IsFog;											///< �t�H�O�̗L��
		CSceneCamera *m_pCameraBackup;							///< �J�����F�o�b�N�A�b�v
		CSceneCamera m_Camera;									///< �J����
		CMatrix m_View;											///< �r���[�s��
		CMatrix m_Projection;									///< �v���W�F�N�V�����s��
		CMatrix m_ViewProjection;								///< �r���[���v���W�F�N�V�����s��

		CVector3D m_vLightColor[LIGHT_MAX];						///< �e�탉�C�g�F
		CVector3D m_vLightPosition[LIGHT_POINT_MAX];			///< �|�C���g���C�g�ʒu
		Float m_fLightDistance[LIGHT_POINT_MAX];				///< �|�C���g���C�g�e������
		Float m_fLightAttenuation[LIGHT_POINT_MAX];				///< �|�C���g���C�g������
		CVector3D m_vLightDirection;							///< �f�B���N�V���i�����C�g����
		Sint32 m_PointLightCount;								///< �|�C���g���C�g��

		Float m_fShadowMapNear;									///< �V���h�E�}�b�v�p�̃J�����̋߃N���b�v
		Float m_fShadowMapFar;									///< �V���h�E�}�b�v�p�̃J�����̉��N���b�v									
		Float m_fShadowMapBias;									///< �V���h�E�}�b�v�p�o�C�A�X
		CMatrix m_mShadowView;									///< �V���h�E�}�b�v�p�r���[�s��
		CMatrix m_mShadowViewProj;								///< �V���h�E�}�b�v�p�r���[���v���W�F�N�V�����s��

		Float m_fFogNear;										///< �t�H�O�J�n�X
		Float m_fFogFar;										///< �t�H�O�I���_
		CColor m_FogColor;										///< �t�H�O�F

		SSceneRenderObject *m_pObjectListTop;					///< �I�u�W�F�N�g���X�g
		CRender *m_pRender;										///< �֘A�t����ꂽ�����_���[

		CThread m_Thread;										///< �V�[���\�z�p�X���b�h
		CEvent m_Event;											///< �L���[�Ǘ��p�C�x���g
		CEvent m_EventEndConstruct;										///< �L���[�Ǘ��p�C�x���g
		CCriticalSection m_CriticalSection;						///< �N���e�B�J���Z�N�V����

		SSceneRenderObject m_QueTbl[SCENE_MANAGER_QUE_MAX];		///< �C�x���g�p�L���[
		Sint32 m_QuePos;										///< �L���[�������݈ʒu
		Bool m_IsEndSceneConstruct;
		Bool m_IsEndManage;

		Bool m_IsSort;											///< �\�[�g���邩�ۂ�

		eSceneMode m_SceneMode;									///< �V�[�����[�h
		eSceneModeOption m_SceneOption;							///< �V�[�����[�h�I�v�V����

		CPoint2D<Uint32> m_TargetSize;							///< �^�[�Q�b�g�̃T�C�Y
		CPostEffect *m_pPostEffect;								///< �|�X�g�G�t�F�N�g�p
		ISurface *m_pDepthStencil;								///< �[�x�X�e���V���o�b�t�@
		ISurface *m_pDepthStencilShadow;						///< �[�x�X�e���V���o�b�t�@
		ITexture *m_pTextureTarget;								///< �����_�����O�^�[�Q�b�g
		ITexture *m_pTextureEffect;								///< �G�t�F�N�g�p�����_�����O�^�[�Q�b�g
		ITexture *m_pTextureBlurLow;							///< �ڂ����摜�i�[�p
		ITexture *m_pTextureBlurHigh;							///< �ڂ����摜�i�[�p
		ITexture *m_pTextureHDR_GaussH;							///< ���������K�E�X
		ITexture *m_pTextureHDR_GaussV;							///< ���������K�E�X
		ITexture *m_pTextureHDR_GaussH2;						///< ���������K�E�X
		ITexture *m_pTextureHDR_GaussV2;						///< ���������K�E�X
		ITexture *m_pTextureHDR_GaussH4;						///< ���������K�E�X
		ITexture *m_pTextureHDR_GaussV4;						///< ���������K�E�X
		ITexture *m_pTextureShadow;								///< �e�e�N�X�`��
		Float m_fFocusDepth;									///< �[�x�t�H�[�J�X�ʒu
		Float m_fFocusPower;									///< ��ʊE�[�x���x
		Uint32 m_RenderRequestCount;							///< �����_�����O���N�G�X�g��
		Uint32 m_RenderCount;									///< �����_�����O��

	protected:
		static void SceneConstructionFunc( void *pData );

	protected:
		CSceneManager( CRender *pRender, eSceneMode Mode, eSceneModeOption Option );
		virtual ~CSceneManager();

		virtual void SceneConstruction( void );
		virtual Sint32 SearchPointLight( Sint32 NoTbl[], CVector3D vPosition );
		virtual void InsertList( SSceneRenderObject &Obj );
		virtual void ComputeRenderData( SSceneRenderObject &Obj );

		virtual void Rendering( eTechniqueType Type );

		virtual void Rendering_MANAGED( Bool IsDrawBuffer );
		virtual void Rendering_1PASS_DOF( Bool IsDrawBuffer );
		virtual void Rendering_2PASS_DOF( Bool IsDrawBuffer );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Sint32 AddObject( CSceneObject *pObject, CRenderData &RenderData, CVector3D &vCenter );

		virtual ISceneCamera *GetSceneCamera( void );

		virtual void Reset( void );
		virtual void Begin( Bool IsSort );
		virtual void End( void );
		virtual void Rendering( Bool IsDrawBuffer );

		virtual Bool IsEndSceneConstruct( void );

		virtual void SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias );
		virtual void SetFogEnable( Bool Enable );
		virtual void SetFog( Float fNear, Float fFar, CColor Color );
		virtual void SetDepthOfFieldForcus( Float fForcusZ, Float fPower );
		virtual void SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth );
		virtual void SetDirectionLight( CVector3D &vDirect, CVector3D &vColor );
		virtual void AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance );
		virtual CPoint2D<Uint32> SetRenderTargetSize( CPoint2D<Uint32> Size );

		virtual Uint32 GetRenderingRequestCount( void );
		virtual Uint32 GetRenderingCount( void );

		virtual Uint32 GetOcculusion( Uint32 Index );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CSCENEMANAGER___


