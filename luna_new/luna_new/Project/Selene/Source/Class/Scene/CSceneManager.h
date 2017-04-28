

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
		@brief バウンディングデータ
		@author 葉迩倭
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

			// 平面投影用
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
			// ボックスを構成する頂点データ
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
		@brief シーンレンダリング用オブジェクト
		@author 葉迩倭
	*/
	struct SSceneRenderObject
	{
		CRenderData RenderData;					///< レンダリング用シェーダーデータ
		CSceneObject *pObject;					///< シーン用オブジェクト
		COcclusion *pOcclusion;					///< オクルージョン用
		CVector3D vCenter;						///< 中心位置
		Float fKey;								///< ソートキー
		Bool IsFog;								///< フォグの有無

		SSceneRenderObject *pNext;				///< リスト用ポインタ

		CMatrix mWorldView;						///< シェーダーに転送する変換行列
		CMatrix mWorldViewProjection;			///< シェーダーに転送する変換行列
		CMatrix mShadowWorldViewProjection;		///< シェーダーに転送する変換行列

		CVector4D vShadowMapTransform;			///< シェーダーに転送する深度取得ベクトル
		CVector4D vDepthTransform;				///< シェーダーに転送する深度取得ベクトル
		CVector4D vLightDiection;				///< シェーダーに転送するディレクショナルライト：ライト方向
		CVector4D vPointLightPositionTbl[4];	///< シェーダーに転送するポイントライト位置テーブル
		CVector4D vPointLightColorTbl[4];		///< シェーダーに転送するポイントライト色テーブル
		Sint32 PointLightCount;					///< シェーダーに転送するポイントライト数
	};

	/**
		@brief シーン管理クラス
		@author 葉迩倭

		3D空間を管理するためのクラスです。
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
		Bool m_IsBegin;											///< シーン開始中か否か
		Bool m_IsFog;											///< フォグの有無
		CSceneCamera *m_pCameraBackup;							///< カメラ：バックアップ
		CSceneCamera m_Camera;									///< カメラ
		CMatrix m_View;											///< ビュー行列
		CMatrix m_Projection;									///< プロジェクション行列
		CMatrix m_ViewProjection;								///< ビューｘプロジェクション行列

		CVector3D m_vLightColor[LIGHT_MAX];						///< 各種ライト色
		CVector3D m_vLightPosition[LIGHT_POINT_MAX];			///< ポイントライト位置
		Float m_fLightDistance[LIGHT_POINT_MAX];				///< ポイントライト影響距離
		Float m_fLightAttenuation[LIGHT_POINT_MAX];				///< ポイントライト減衰率
		CVector3D m_vLightDirection;							///< ディレクショナルライト方向
		Sint32 m_PointLightCount;								///< ポイントライト数

		Float m_fShadowMapNear;									///< シャドウマップ用のカメラの近クリップ
		Float m_fShadowMapFar;									///< シャドウマップ用のカメラの遠クリップ									
		Float m_fShadowMapBias;									///< シャドウマップ用バイアス
		CMatrix m_mShadowView;									///< シャドウマップ用ビュー行列
		CMatrix m_mShadowViewProj;								///< シャドウマップ用ビューｘプロジェクション行列

		Float m_fFogNear;										///< フォグ開始店
		Float m_fFogFar;										///< フォグ終了点
		CColor m_FogColor;										///< フォグ色

		SSceneRenderObject *m_pObjectListTop;					///< オブジェクトリスト
		CRender *m_pRender;										///< 関連付けられたレンダラー

		CThread m_Thread;										///< シーン構築用スレッド
		CEvent m_Event;											///< キュー管理用イベント
		CEvent m_EventEndConstruct;										///< キュー管理用イベント
		CCriticalSection m_CriticalSection;						///< クリティカルセクション

		SSceneRenderObject m_QueTbl[SCENE_MANAGER_QUE_MAX];		///< イベント用キュー
		Sint32 m_QuePos;										///< キュー書き込み位置
		Bool m_IsEndSceneConstruct;
		Bool m_IsEndManage;

		Bool m_IsSort;											///< ソートするか否か

		eSceneMode m_SceneMode;									///< シーンモード
		eSceneModeOption m_SceneOption;							///< シーンモードオプション

		CPoint2D<Uint32> m_TargetSize;							///< ターゲットのサイズ
		CPostEffect *m_pPostEffect;								///< ポストエフェクト用
		ISurface *m_pDepthStencil;								///< 深度ステンシルバッファ
		ISurface *m_pDepthStencilShadow;						///< 深度ステンシルバッファ
		ITexture *m_pTextureTarget;								///< レンダリングターゲット
		ITexture *m_pTextureEffect;								///< エフェクト用レンダリングターゲット
		ITexture *m_pTextureBlurLow;							///< ぼかし画像格納用
		ITexture *m_pTextureBlurHigh;							///< ぼかし画像格納用
		ITexture *m_pTextureHDR_GaussH;							///< 水平方向ガウス
		ITexture *m_pTextureHDR_GaussV;							///< 垂直方向ガウス
		ITexture *m_pTextureHDR_GaussH2;						///< 水平方向ガウス
		ITexture *m_pTextureHDR_GaussV2;						///< 垂直方向ガウス
		ITexture *m_pTextureHDR_GaussH4;						///< 水平方向ガウス
		ITexture *m_pTextureHDR_GaussV4;						///< 垂直方向ガウス
		ITexture *m_pTextureShadow;								///< 影テクスチャ
		Float m_fFocusDepth;									///< 深度フォーカス位置
		Float m_fFocusPower;									///< 被写界深度強度
		Uint32 m_RenderRequestCount;							///< レンダリングリクエスト数
		Uint32 m_RenderCount;									///< レンダリング数

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


