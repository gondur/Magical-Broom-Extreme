

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Scene/CSceneManager.h"
#include "Scene/CSceneObject.h"
#include "Render/CShader.h"
#include "Render/CPostEffect.h"
#include "Surface/CTexture.h"
#include "Surface/CSurface.h"
#include "Core/CCore.h"
#include "Core/COcclusion.h"


#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SceneConstructionFunc( void *pData )
{
	CSceneManager *pSceneMgr = (CSceneManager*)pData;

	pSceneMgr->SceneConstruction();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager::CSceneManager( CRender *pRender, eSceneMode Mode, eSceneModeOption Option )
	: m_vLightDirection			(0.0f,0.0f,0.0f)
	, m_PointLightCount			( 0 )
	, m_pObjectListTop			( NULL )
	, m_fFogNear				( 1000000000000000000.0f )
	, m_fFogFar					( 2000000000000000000.0f )
	, m_FogColor				( 0x00000000 )
	, m_IsBegin					( false )
	, m_IsFog					( false )
	, m_IsSort					( false )
	, m_Event					( false, SCENE_MANAGER_EVENT_MAX )
	, m_EventEndConstruct		( false, 1 )
	, m_QuePos					( 0 )
	, m_IsEndManage				( false )
	, m_SceneMode				( Mode )
	, m_SceneOption				( Option )
	, m_fFocusDepth				( 0.0f )
	, m_fFocusPower				( 0.0f )
	, m_RenderRequestCount		( 0 )
	, m_RenderCount				( 0 )
	, m_pDepthStencil			( NULL )
	, m_pDepthStencilShadow		( NULL )
	, m_pTextureTarget			( NULL )
	, m_pTextureEffect			( NULL )
	, m_pTextureBlurLow			( NULL )
	, m_pTextureBlurHigh		( NULL )
	, m_pTextureHDR_GaussH		( NULL )
	, m_pTextureHDR_GaussV		( NULL )
	, m_pTextureHDR_GaussH2		( NULL )
	, m_pTextureHDR_GaussV2		( NULL )
	, m_pTextureHDR_GaussH4		( NULL )
	, m_pTextureHDR_GaussV4		( NULL )
	, m_pTextureShadow			( NULL )
{
	m_pRender = pRender;
	pRender->AddRef();

	for ( Sint32 i = 0; i < LIGHT_MAX; i++ )
	{
		m_vLightColor[i] = CVector3D(0.0f,0.0f,0.0f);
	}

	for ( Sint32 i = 0; i < LIGHT_POINT_MAX; i++ )
	{
		m_vLightPosition[i] = CVector3D(0.0f,0.0f,0.0f);
	}

	for ( Sint32 i = 0; i < SCENE_MANAGER_QUE_MAX; i++ )
	{
		m_QueTbl[i].pOcclusion = m_pRender->GetDevicePointer()->CeateOcclusion();
	}

	m_pCameraBackup = new CSceneCamera;
	m_Camera.Reset();

	m_mShadowView.Identity();

	m_View.Identity();
	m_Projection.Identity();
	m_ViewProjection.Identity();

	m_pPostEffect = dynamic_cast<CPostEffect*>(m_pRender->CreatePostEffect());

	m_TargetSize = CPoint2D<Uint32>( 0, 0 );

	m_Thread.Create( SceneConstructionFunc, this );

	// シーンモードチェック
	switch ( m_SceneMode )
	{
	case SCENE_MODE_NOT_MANAGED:
		break;
	case SCENE_MODE_MANAGED:
		break;
	case SCENE_MODE_1PASS_DOF:
	case SCENE_MODE_2PASS_DOF:
	case SCENE_MODE_1PASS_DOF_HIGH:
	case SCENE_MODE_2PASS_DOF_HIGH:
		if ( !m_pRender->GetDevicePointer()->GetGraphicCardPointer()->GetPixelShaderSupport( 1, 1 ) )
		{
			m_SceneMode = SCENE_MODE_MANAGED;
		}
		break;
	}

	// シーンオプションチェック
	switch ( m_SceneOption )
	{
	case SCENE_MODE_OPTION_NO:
		break;
	case SCENE_MODE_OPTION_HDR:
	case SCENE_MODE_OPTION_EDGE:
		if ( !m_pRender->GetDevicePointer()->GetGraphicCardPointer()->GetPixelShaderSupport( 2, 0 ) )
		{
			m_SceneOption = SCENE_MODE_OPTION_NO;
		}
		if ( !m_pRender->GetDevicePointer()->GetGraphicCardPointer()->GetHDRRenderTargetSupport() )
		{
			m_SceneOption = SCENE_MODE_OPTION_NO;
		}
		break;
	case SCENE_MODE_OPTION_SHADOW:
		if ( !m_pRender->GetDevicePointer()->GetGraphicCardPointer()->GetPixelShaderSupport( 2, 0 ) )
		{
			m_SceneOption = SCENE_MODE_OPTION_NO;
		}
		break;
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager::~CSceneManager()
{
	// キュー処理スレッド終了
	m_IsEndManage = true;
	m_Event.Set( EVENT_NO_EXIT );
	m_Thread.WaitForExit( -1 );

	// オクリュージョン
	for ( Sint32 i = 0; i < SCENE_MANAGER_QUE_MAX; i++ )
	{
		SAFE_RELEASE( m_QueTbl[i].pOcclusion );
	}

	// 所有オブジェクト解放
	SAFE_RELEASE( m_pRender );
	SAFE_RELEASE( m_pCameraBackup );

	SAFE_RELEASE( m_pDepthStencil );
	SAFE_RELEASE( m_pDepthStencilShadow );
	SAFE_RELEASE( m_pTextureTarget );
	SAFE_RELEASE( m_pTextureEffect );
	SAFE_RELEASE( m_pTextureBlurLow );
	SAFE_RELEASE( m_pTextureBlurHigh );
	SAFE_RELEASE( m_pTextureHDR_GaussH );
	SAFE_RELEASE( m_pTextureHDR_GaussV );
	SAFE_RELEASE( m_pTextureHDR_GaussH2 );
	SAFE_RELEASE( m_pTextureHDR_GaussV2 );
	SAFE_RELEASE( m_pTextureHDR_GaussH4 );
	SAFE_RELEASE( m_pTextureHDR_GaussV4 );
	SAFE_RELEASE( m_pTextureShadow );
	SAFE_RELEASE( m_pPostEffect );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISceneCamera *CSceneManager::GetSceneCamera( void )
{
	m_pCameraBackup->AddRef();
	return m_pCameraBackup;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Reset( void )
{
	if ( m_IsBegin ) return;

	m_PointLightCount = 0;
	m_pObjectListTop = NULL;

	m_vLightDirection = CVector3D( 0.0f, 0.0f, 0.0f );
	MemoryClear( m_vLightColor, sizeof(m_vLightColor) );

	m_fFogNear	= m_Camera.GetFarClip() + 100.0f;
	m_fFogFar	= m_Camera.GetFarClip() + 200.0f;

	m_fFocusDepth = m_fFogNear;
	m_fFocusPower = 0.0f;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Begin( Bool IsSort )
{
	if ( !m_pRender->ActivateScene( this ) ) return;
	if ( m_pObjectListTop != NULL ) return;
	if ( m_IsBegin ) return;

	m_IsBegin				= true;
	m_IsSort				= IsSort;
	m_IsFog					= false;
	m_QuePos				= 0;
	m_Camera				= *m_pCameraBackup;
	m_View					= m_Camera.WorldToView();
	m_ViewProjection		= m_Camera.WorldToScreen();

	m_RenderRequestCount	= 0;
	m_RenderCount			= 0;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::End( void )
{
	if ( !m_pRender->DeActivateScene( this ) ) return;
	if ( !m_IsBegin ) return;

	// キューにデータがあるとき
	if ( m_QuePos > 0 )
	{
		// 描画完了イベント
		m_EventEndConstruct.Reset();

		// キュー追加イベント発行
		if ( !m_Event.IsSignal( EVENT_NO_QUEEND ) )
		{
			m_Event.Set( EVENT_NO_QUEEND );
		}
	}

	m_RenderRequestCount	= m_QuePos;
	m_RenderCount			= 0;

	m_IsBegin = false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Rendering( eTechniqueType Type )
{
	CVector4D vPositionTbl[4];
	CVector4D vColorTbl[4];
	CMatrix mTemp;

	Bool IsShadow = m_SceneOption == SCENE_MODE_OPTION_SHADOW;

	Float fFogParam[] = {
		-1.0f     / (m_fFogFar - m_fFogNear),
		m_fFogFar / (m_fFogFar - m_fFogNear),
	};

	Float fDofParam[] = {
		-1.0f                 / (m_Camera.GetFarClip() - m_Camera.GetNearClip()),
		m_Camera.GetFarClip() / (m_Camera.GetFarClip() - m_Camera.GetNearClip()),
		m_fFocusDepth,
		m_fFocusPower,
	};

	Float fShadowParam[] = {
		-1.0f           / (m_fShadowMapFar - m_fShadowMapNear),
		m_fShadowMapFar / (m_fShadowMapFar - m_fShadowMapNear),
		0.0f,
		m_fShadowMapBias,
	};

	SSceneRenderObject *pObj = m_pObjectListTop;
	while ( pObj != NULL )
	{
		CRenderData &RD = pObj->RenderData;
		SRenderShaderData &SD = CRenderData::GetShader( RD.Type, pObj->PointLightCount, IsShadow );

		pObj->pOcclusion->Begin();

		// テクニック
		SD.pShader->SetTechnique( SD.hTechnique[Type][RD.BumpMode][RD.ReflexMode][pObj->IsFog] );

		// ShadowMapParameter
		if ( SD.hShadowMapParameter != NULL )
		{
			SD.pShader->SetFloatArray( SD.hShadowMapParameter, fShadowParam, 4 );
		}
		// ShadowMapTransform
		if ( SD.hShadowMapTransform != NULL )
		{
			SD.pShader->SetVector( SD.hShadowMapTransform, &pObj->vShadowMapTransform );
		}
		// DepthTransform
		if ( ((Type != TECHNIQUE_TYPE_NORMAL) || pObj->IsFog) && (SD.hDepthTransform != NULL) )
		{
			SD.pShader->SetVector( SD.hDepthTransform, &pObj->vDepthTransform );
		}
		// DofParameter
		if ( (Type != TECHNIQUE_TYPE_NORMAL) && (SD.hDofParameter != NULL) )
		{
			SD.pShader->SetFloatArray( SD.hDofParameter, fDofParam, 4 );
		}
		// FogParameter
		if ( pObj->IsFog && (SD.hFogParameter != NULL) )
		{
			CVector4D vTemp( toF(m_FogColor.r) / 255.0f, toF(m_FogColor.g) / 255.0f, toF(m_FogColor.b) / 255.0f, 1.0f );
			SD.pShader->SetVector( SD.hFogColor, &vTemp );
			SD.pShader->SetFloatArray( SD.hFogParameter, fFogParam, 2 );
		}
		// ShadowWorldViewProjection
		if ( SD.hShadowWorldViewProjection != NULL )
		{
			SD.pShader->SetMatrix( SD.hShadowWorldViewProjection, (SMatrix4x4*)pObj->mShadowWorldViewProjection );
		}
		// WorldViewProjection
		if ( SD.hWorldViewProjection != NULL )
		{
			SD.pShader->SetMatrix( SD.hWorldViewProjection, (SMatrix4x4*)pObj->mWorldViewProjection );
		}
		// WorldView
		if ( SD.hWorldView != NULL )
		{
			SD.pShader->SetMatrix( SD.hWorldView, (SMatrix4x4*)pObj->mWorldView );
		}
		// World
		if ( SD.hWorld != NULL )
		{
			SD.pShader->SetMatrix( SD.hWorld, (SMatrix4x4*)RD.mWorld );
		}
		// CameraPosition
		if ( SD.hCameraPosition != NULL )
		{
			CVector3D vPos = m_Camera.Position();
			vPos.TransformCoord( RD.mWorldInverse );
			CVector4D vTemp( vPos.x, vPos.y, vPos.z, 1.0f );
			SD.pShader->SetVector( SD.hCameraPosition, &vTemp );
		}
		// AmbientLightColorSky
		if ( SD.hAmbientLightColorSky != NULL )
		{
			CVector4D vCol(
				m_vLightColor[LIGHT_AMBIENT_SKY].x,
				m_vLightColor[LIGHT_AMBIENT_SKY].y,
				m_vLightColor[LIGHT_AMBIENT_SKY].z,
				0.0f );
			SD.pShader->SetVector( SD.hAmbientLightColorSky, &vCol );
		}
		// AmbientLightColorEarth
		if ( SD.hAmbientLightColorEarth != NULL )
		{
			CVector4D vCol(
				m_vLightColor[LIGHT_AMBIENT_EARTH].x,
				m_vLightColor[LIGHT_AMBIENT_EARTH].y,
				m_vLightColor[LIGHT_AMBIENT_EARTH].z,
				0.0f );
			SD.pShader->SetVector( SD.hAmbientLightColorEarth, &vCol );
		}
		// DirectionalLightColor
		if ( SD.hDirectionalLightColor != NULL )
		{
			CVector4D vCol(
				m_vLightColor[LIGHT_DIRECTION].x,
				m_vLightColor[LIGHT_DIRECTION].y,
				m_vLightColor[LIGHT_DIRECTION].z,
				1.0f );
			SD.pShader->SetVector( SD.hDirectionalLightColor, &vCol );
		}
		// DirectionalLightDirection
		if ( SD.hDirectionalLightDirection != NULL )
		{
			SD.pShader->SetVector( SD.hDirectionalLightDirection, &pObj->vLightDiection );
		}
		// PointLightPosition & PointLightColor
		if ( (SD.hPointLightPosition != NULL) && (SD.hPointLightColor != NULL) )
		{
			SD.pShader->SetVectorArray( SD.hPointLightPosition, pObj->vPointLightPositionTbl, pObj->PointLightCount );
			SD.pShader->SetVectorArray( SD.hPointLightColor, pObj->vPointLightColorTbl, pObj->PointLightCount );
		}
		// BoneMatrixArray
		if ( SD.hBoneMatrixArray != NULL )
		{
			SD.pShader->SetMatrixArray( SD.hBoneMatrixArray, RD.mBone, RD.BoneCount );
		}
		// マテリアル単位で
		for ( Uint32 i = 0; i < RD.MaterialCount; i++ )
		{
			if ( (Type == TECHNIQUE_TYPE_NORMAL_AND_DEPTH) || (Type == TECHNIQUE_TYPE_SHADOWMAP) )
			{
				// テクスチャ
				for ( Uint32 j = MESH_TEXTURE_COLORMAP; j <= MESH_TEXTURE_NORMALMAP; j++ )
				{
					m_pRender->SetTexture( j, NULL );
				}
			}
			else
			{
				// テクスチャ
				for ( Uint32 j = MESH_TEXTURE_COLORMAP; j <= MESH_TEXTURE_NORMALMAP; j++ )
				{
					m_pRender->SetTexture( j, RD.Material[i].pTexture[j] );
				}

				// MaterialColor
				if ( SD.hMaterialColor != NULL )
				{
					SD.pShader->SetVector( SD.hMaterialColor, &RD.Material[i].vMaterialColor );
				}
				// SpecularColor
				if ( SD.hSpecularColor != NULL )
				{
					SD.pShader->SetVector( SD.hSpecularColor, &RD.Material[i].vSpecularColor );
				}
				// Specular Refractive
				if ( SD.hRefractive != NULL )
				{
					SD.pShader->SetFloat( SD.hRefractive, RD.Material[i].fRefractive );
				}
				// Specular Roughly
				if ( SD.hRoughly != NULL )
				{
					SD.pShader->SetFloat( SD.hRoughly, RD.Material[i].fRoughly );
				}
			}
			// レンダリング
			pObj->pObject->RenderSubstance( i, SD );
		}

		pObj->pOcclusion->End();

		// 次
		pObj = pObj->pNext;

		// レンダリング数＋１
		m_RenderCount++;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Rendering( Bool IsDrawBuffer )
{
	if ( m_IsBegin ) return;
	if ( m_QuePos == 0 ) return;

	CRect2D<Sint32> Dst, Src;

	//==============================================================
	// シーン構築が終わるまでブロック
	//==============================================================
	m_EventEndConstruct.Wait();

	//==============================================================
	// モードごとにレンダリング
	//==============================================================
	switch ( m_SceneMode )
	{
	//----------------------------------------------
	// 通常レンダリング
	//----------------------------------------------
	case SCENE_MODE_NOT_MANAGED:
		// 普通にレンダリング
		Rendering( TECHNIQUE_TYPE_NORMAL );
		break;

	//----------------------------------------------
	// 内部管理レンダリング
	//----------------------------------------------
	case SCENE_MODE_MANAGED:
		Rendering_MANAGED( IsDrawBuffer );
		break;

	//----------------------------------------------
	// 1-Pass被写界深度
	//----------------------------------------------
	case SCENE_MODE_1PASS_DOF:
	case SCENE_MODE_1PASS_DOF_HIGH:
		Rendering_1PASS_DOF( IsDrawBuffer );
		break;

	//--------------------------------------------------------------------------------------------
	// 2-Pass被写界深度
	//--------------------------------------------------------------------------------------------
	case SCENE_MODE_2PASS_DOF:
	case SCENE_MODE_2PASS_DOF_HIGH:
		Rendering_2PASS_DOF( IsDrawBuffer );
		break;
	}

	//===============================================================================================
	// シーンオブジェクト解放
	//===============================================================================================
	m_pObjectListTop = NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Rendering_MANAGED( Bool IsDrawBuffer )
{
	CRect2D<Sint32> Dst, Src;

	//------------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------------
	m_pRender->StatePush();
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );
	m_pRender->SetAlphaTestEnable( false );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// シャドウマップレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_SHADOW:
		// レンダリングターゲット
		m_pRender->SetRenderTarget( m_pTextureShadow );
		m_pRender->SetDepthStencil( m_pDepthStencilShadow );
		// バッファクリア
		m_pRender->GetDevicePointer()->Clear( 0x00000000 );
		m_pRender->GetDevicePointer()->ClearDepth();
		// シザリング
		m_pRender->GetDevicePointer()->SetScissor(
			true,
			CRect2D<Sint32>( 1, 1, m_pTextureShadow->GetSize().x - 2, m_pTextureShadow->GetSize().y - 2 ) );
		// レンダリング
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetDepthTestEnable( true );
		m_pRender->SetCullType( CULL_BACK );
		Rendering( TECHNIQUE_TYPE_SHADOWMAP );
		m_pRender->SetCullType( CULL_FRONT );
		// シャドウマップ
		m_pRender->SetTexture( MESH_TEXTURE_SHADOWMAP, m_pTextureShadow );
		m_pRender->SetTextureAddressType( MESH_TEXTURE_SHADOWMAP, TEXTURE_ADDRESS_CLAMP );
		m_pRender->SetTextureFilterType( MESH_TEXTURE_SHADOWMAP, TEXTURE_FILTER_DISABLE );
		// シザリング
		m_pRender->GetDevicePointer()->SetScissor( false, CRect2D<Sint32>( 0, 0, 0, 0 ) );
		break;
	}

	//------------------------------------------------------------------------
	// レンダリングターゲット
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureTarget );
	m_pRender->SetDepthStencil( m_pDepthStencil );

	//------------------------------------------------------------------------
	// バッファクリア
	//------------------------------------------------------------------------
	m_pRender->GetDevicePointer()->Clear( 0x00000000 );
	m_pRender->GetDevicePointer()->ClearDepth();

	//------------------------------------------------------------------------
	// 普通にレンダリング
	//------------------------------------------------------------------------
	Rendering( TECHNIQUE_TYPE_NORMAL );

	//------------------------------------------------------------------------
	// ターゲットに描画
	//------------------------------------------------------------------------
	m_pRender->SetTextureAddressType( 0, TEXTURE_ADDRESS_CLAMP );
	m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	m_pRender->ResetRenderTarget();
	m_pRender->SetDepthStencil( NULL );
	Dst = m_pRender->GetDevicePointer()->GetViewport();
	Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
	m_pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// オプションなし
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_NO:
		break;
	//-------------------------------------------------------
	// HDRレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_HDR:
		{
			eTextureOperationType OperateTbl[] = {
				TEXTURE_OP_MUL,
				TEXTURE_OP_ADD,
				TEXTURE_OP_ADD,
			};

			ITexture *pTexTbl[] = {
				m_pTextureHDR_GaussV,
				m_pTextureHDR_GaussV2,
				m_pTextureHDR_GaussV4,
			};

			CRect2D<Sint32> SrcTbl[] = {
				CRect2D<Sint32>( 0, 0, pTexTbl[0]->GetSize().x, pTexTbl[0]->GetSize().y ),
				CRect2D<Sint32>( 0, 0, pTexTbl[1]->GetSize().x, pTexTbl[1]->GetSize().y ),
				CRect2D<Sint32>( 0, 0, pTexTbl[2]->GetSize().x, pTexTbl[2]->GetSize().y ),
			};

			m_pRender->SetDepthStencil( NULL );
			// 高輝度部分抽出
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
			m_pPostEffect->HDR_DownSample( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV->GetSize().x, m_pTextureHDR_GaussV->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH->GetSize().x, m_pTextureHDR_GaussH->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH );
			// 縮小バッファに
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV->GetSize().x, m_pTextureHDR_GaussV->GetSize().y );
			m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV2->GetSize().x, m_pTextureHDR_GaussV2->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV2 );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH2->GetSize().x, m_pTextureHDR_GaussH2->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH2 );
			// 縮小バッファに
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV2->GetSize().x, m_pTextureHDR_GaussV2->GetSize().y );
			m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV2 );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV4->GetSize().x, m_pTextureHDR_GaussV4->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV4 );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH4->GetSize().x, m_pTextureHDR_GaussH4->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH4 );
			// ターゲットに描画
			m_pRender->ResetRenderTarget();
			m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetTextureFilterType( 1, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetTextureFilterType( 2, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetDrawType( DRAW_TYPE_ADD_NOALPHA );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			m_pPostEffect->MultipleTexture( Dst, 0xFFFFFFFF, SrcTbl, OperateTbl, pTexTbl, 3 );
		}
		break;
	//-------------------------------------------------------
	// エッジレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_EDGE:
		// レンダリングターゲット
		m_pRender->SetRenderTarget( m_pTextureEffect );
		m_pRender->SetDepthStencil( m_pDepthStencil );
		// バッファクリア
		m_pRender->GetDevicePointer()->Clear( 0x00000000 );
		m_pRender->GetDevicePointer()->ClearDepth();
		// レンダリング
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetDepthTestEnable( true );
		Rendering( TECHNIQUE_TYPE_NORMAL_AND_DEPTH );
		// エッジレンダリング
		m_pRender->ResetRenderTarget();
		m_pRender->SetDepthStencil( NULL );
		// エッジのエフェクト
		m_pRender->SetDrawType( DRAW_TYPE_MULTIPLE );
		Dst = m_pRender->GetDevicePointer()->GetViewport();
		Src = CRect2D<Sint32>( 0, 0, m_pTextureEffect->GetSize().x, m_pTextureEffect->GetSize().y );
		m_pPostEffect->DrawEdge( Dst, 0xFFFFFFFF, Src, m_pTextureEffect );
		break;
	//-------------------------------------------------------
	// シャドウマップレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_SHADOW:
		// バッファレインダリンg
		if ( IsDrawBuffer )
		{
			Dst.x = 0;
			Dst.y = 0;
			Dst.w = 256;
			Dst.h = 256;
			Src = CRect2D<Sint32>( 0, 0, m_pTextureShadow->GetSize().x, m_pTextureShadow->GetSize().y );
			m_pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, m_pTextureShadow );
		}
		break;
	}

	//------------------------------------------------------------------------
	// ステータス戻す
	//------------------------------------------------------------------------
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Rendering_1PASS_DOF( Bool IsDrawBuffer )
{
	CRect2D<Sint32> Dst, Src;

	//------------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------------
	m_pRender->StatePush();
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );
	m_pRender->SetAlphaTestEnable( false );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// シャドウマップレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_SHADOW:
		// レンダリングターゲット
		m_pRender->SetRenderTarget( m_pTextureShadow );
		m_pRender->SetDepthStencil( m_pDepthStencilShadow );
		// バッファクリア
		m_pRender->GetDevicePointer()->Clear( 0x00000000 );
		m_pRender->GetDevicePointer()->ClearDepth();
		// シザリング
		m_pRender->GetDevicePointer()->SetScissor(
			true,
			CRect2D<Sint32>( 1, 1, m_pTextureShadow->GetSize().x - 2, m_pTextureShadow->GetSize().y - 2 ) );
		// レンダリング
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetDepthTestEnable( true );
		m_pRender->SetCullType( CULL_BACK );
		Rendering( TECHNIQUE_TYPE_SHADOWMAP );
		m_pRender->SetCullType( CULL_FRONT );
		// シャドウマップ
		m_pRender->SetTexture( MESH_TEXTURE_SHADOWMAP, m_pTextureShadow );
		m_pRender->SetTextureAddressType( MESH_TEXTURE_SHADOWMAP, TEXTURE_ADDRESS_CLAMP );
		m_pRender->SetTextureFilterType( MESH_TEXTURE_SHADOWMAP, TEXTURE_FILTER_DISABLE );
		// シザリング
		m_pRender->GetDevicePointer()->SetScissor( false, CRect2D<Sint32>( 0, 0, 0, 0 ) );
		break;
	//-------------------------------------------------------
	// エッジレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_EDGE:
		// レンダリングターゲット
		m_pRender->SetRenderTarget( m_pTextureEffect );
		m_pRender->SetDepthStencil( m_pDepthStencil );
		// バッファクリア
		m_pRender->GetDevicePointer()->Clear( 0x00000000 );
		m_pRender->GetDevicePointer()->ClearDepth();
		// レンダリング
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetDepthTestEnable( true );
		Rendering( TECHNIQUE_TYPE_NORMAL_AND_DEPTH );
		break;
	}

	//------------------------------------------------------------------------
	// 1-PASS目
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureTarget );
	m_pRender->SetDepthStencil( m_pDepthStencil );

	//------------------------------------------------------------------------
	// バッファクリア
	//------------------------------------------------------------------------
	m_pRender->GetDevicePointer()->Clear( 0xFF000000 );
	m_pRender->GetDevicePointer()->ClearDepth();

	//------------------------------------------------------------------------
	// アルファに深度値を格納しつつレンダリング
	//------------------------------------------------------------------------
	Rendering( TECHNIQUE_TYPE_DEPTH_OF_FIELD );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// HDRレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_HDR:
		{
			m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
			m_pRender->SetDepthStencil( NULL );
			// 高輝度部分抽出
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
			m_pPostEffect->HDR_DownSample( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV->GetSize().x, m_pTextureHDR_GaussV->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH->GetSize().x, m_pTextureHDR_GaussH->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH );
			// 縮小バッファに
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV->GetSize().x, m_pTextureHDR_GaussV->GetSize().y );
			m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV2->GetSize().x, m_pTextureHDR_GaussV2->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV2 );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH2->GetSize().x, m_pTextureHDR_GaussH2->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH2 );
			// 縮小バッファに
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV2->GetSize().x, m_pTextureHDR_GaussV2->GetSize().y );
			m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV2 );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV4->GetSize().x, m_pTextureHDR_GaussV4->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV4 );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH4->GetSize().x, m_pTextureHDR_GaussH4->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH4 );
		}
		break;
	}

	//------------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------------
	m_pRender->SetDepthWriteEnable( false );
	m_pRender->SetDepthTestEnable( false );

	//------------------------------------------------------------------------
	// 縮小画像生成
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureBlurLow );
	m_pRender->SetDepthStencil( NULL );

	Dst = m_pRender->GetDevicePointer()->GetViewport();
	Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
	switch ( m_SceneMode )
	{
	case SCENE_MODE_1PASS_DOF:
		m_pPostEffect->Blur16Box( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
		break;
	case SCENE_MODE_1PASS_DOF_HIGH:
		m_pPostEffect->Blur64Box( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
		break;
	}

	//------------------------------------------------------------------------
	// 16Boxフィルタ画像生成
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureBlurHigh );
	m_pRender->SetDepthStencil( NULL );

	Dst = m_pRender->GetDevicePointer()->GetViewport();
	Src = CRect2D<Sint32>( 0, 0, m_pTextureBlurLow->GetSize().x, m_pTextureBlurLow->GetSize().y );
	switch ( m_SceneMode )
	{
	case SCENE_MODE_1PASS_DOF:
		m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureBlurLow );
		break;
	case SCENE_MODE_1PASS_DOF_HIGH:
		m_pPostEffect->Blur16Box( Dst, 0xFFFFFFFF, Src, m_pTextureBlurLow );
		break;
	}

	//------------------------------------------------------------------------
	// ターゲットに描画
	//------------------------------------------------------------------------
	m_pRender->SetTextureAddressType( 0, TEXTURE_ADDRESS_CLAMP );
	m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	m_pRender->ResetRenderTarget();
	m_pRender->SetDepthStencil( NULL );
	Dst = m_pRender->GetDevicePointer()->GetViewport();
	Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
	m_pPostEffect->DepthOfField( Dst, m_pTextureBlurHigh, m_pTextureTarget );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// HDRレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_HDR:
		{
			eTextureOperationType OperateTbl[] = {
				TEXTURE_OP_MUL,
				TEXTURE_OP_ADD,
				TEXTURE_OP_ADD,
			};

			ITexture *pTexTbl[] = {
				m_pTextureHDR_GaussV,
				m_pTextureHDR_GaussV2,
				m_pTextureHDR_GaussV4,
			};

			CRect2D<Sint32> SrcTbl[] = {
				CRect2D<Sint32>( 0, 0, pTexTbl[0]->GetSize().x, pTexTbl[0]->GetSize().y ),
				CRect2D<Sint32>( 0, 0, pTexTbl[1]->GetSize().x, pTexTbl[1]->GetSize().y ),
				CRect2D<Sint32>( 0, 0, pTexTbl[2]->GetSize().x, pTexTbl[2]->GetSize().y ),
			};
			// ターゲットに描画
			m_pRender->ResetRenderTarget();
			m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetTextureFilterType( 1, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetTextureFilterType( 2, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetDrawType( DRAW_TYPE_ADD_NOALPHA );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			m_pPostEffect->MultipleTexture( Dst, 0xFFFFFFFF, SrcTbl, OperateTbl, pTexTbl, 3 );
		}
		break;
	//-------------------------------------------------------
	// エッジレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_EDGE:
		// レンダリングターゲット
		m_pRender->ResetRenderTarget();
		m_pRender->SetDepthStencil( NULL );
		// エッジのエフェクト
		m_pRender->SetDrawType( DRAW_TYPE_MULTIPLE );
		Dst = m_pRender->GetDevicePointer()->GetViewport();
		Src = CRect2D<Sint32>( 0, 0, m_pTextureEffect->GetSize().x, m_pTextureEffect->GetSize().y );
		m_pPostEffect->DrawEdge( Dst, 0xFFFFFFFF, Src, m_pTextureEffect );
		// バッファレンダリング
		if ( IsDrawBuffer )
		{
			Dst.x = 0;
			Dst.y = 0;
			Dst.w = 256;
			Dst.h = 256;
			Src = CRect2D<Sint32>( 0, 0, m_pTextureEffect->GetSize().x, m_pTextureEffect->GetSize().y );
			m_pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, m_pTextureEffect );
		}
		break;
	//-------------------------------------------------------
	// シャドウマップレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_SHADOW:
		// バッファレンダリング
		if ( IsDrawBuffer )
		{
			Dst.x = 0;
			Dst.y = 0;
			Dst.w = 256;
			Dst.h = 256;
			Src = CRect2D<Sint32>( 0, 0, m_pTextureShadow->GetSize().x, m_pTextureShadow->GetSize().y );
			m_pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, m_pTextureShadow );
		}
		break;
	}

	//------------------------------------------------------------------------
	// ステータス戻す
	//------------------------------------------------------------------------
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::Rendering_2PASS_DOF( Bool IsDrawBuffer )
{
	CRect2D<Sint32> Dst, Src;

	//------------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------------
	m_pRender->StatePush();
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );
	m_pRender->SetAlphaTestEnable( false );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// シャドウマップレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_SHADOW:
		// レンダリングターゲット
		m_pRender->SetRenderTarget( m_pTextureShadow );
		m_pRender->SetDepthStencil( m_pDepthStencilShadow );
		// バッファクリア
		m_pRender->GetDevicePointer()->Clear( 0x00000000 );
		m_pRender->GetDevicePointer()->ClearDepth();
		// シザリング
		m_pRender->GetDevicePointer()->SetScissor(
			true,
			CRect2D<Sint32>( 1, 1, m_pTextureShadow->GetSize().x - 2, m_pTextureShadow->GetSize().y - 2 ) );
		// レンダリング
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetDepthTestEnable( true );
		m_pRender->SetCullType( CULL_BACK );
		Rendering( TECHNIQUE_TYPE_SHADOWMAP );
		m_pRender->SetCullType( CULL_FRONT );
		// シャドウマップ
		m_pRender->SetTexture( MESH_TEXTURE_SHADOWMAP, m_pTextureShadow );
		m_pRender->SetTextureAddressType( MESH_TEXTURE_SHADOWMAP, TEXTURE_ADDRESS_CLAMP );
		m_pRender->SetTextureFilterType( MESH_TEXTURE_SHADOWMAP, TEXTURE_FILTER_DISABLE );
		// シザリング
		m_pRender->GetDevicePointer()->SetScissor( false, CRect2D<Sint32>( 0, 0, 0, 0 ) );
		break;
	}

	//------------------------------------------------------------------------
	// 1-PASS目
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureTarget );
	m_pRender->SetDepthStencil( m_pDepthStencil );
	// バッファクリア
	m_pRender->GetDevicePointer()->Clear( 0x00000000 );
	m_pRender->GetDevicePointer()->ClearDepth();
	// 普通にレンダリング
	Rendering( TECHNIQUE_TYPE_NORMAL );

	//------------------------------------------------------------------------
	// 2-PASS目
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureEffect );
	m_pRender->SetDepthStencil( m_pDepthStencil );
	// バッファクリア
	m_pRender->GetDevicePointer()->Clear( 0xFF000000 );
	m_pRender->GetDevicePointer()->ClearDepth();
	// アルファに深度値を格納しつつレンダリング
	Rendering( TECHNIQUE_TYPE_NORMAL_AND_DEPTH );

	//------------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------------
	m_pRender->SetDepthWriteEnable( false );
	m_pRender->SetDepthTestEnable( false );

	//------------------------------------------------------------------------
	// 縮小画像生成
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureBlurLow );
	m_pRender->SetDepthStencil( NULL );

	Dst = m_pRender->GetDevicePointer()->GetViewport();
	Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
	switch ( m_SceneMode )
	{
	case SCENE_MODE_2PASS_DOF:
		m_pPostEffect->Blur16Box( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
		break;
	case SCENE_MODE_2PASS_DOF_HIGH:
		m_pPostEffect->Blur64Box( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
		break;
	}

	//------------------------------------------------------------------------
	// 16Boxフィルタ画像生成
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pTextureBlurHigh );
	m_pRender->SetDepthStencil( NULL );

	Dst = m_pRender->GetDevicePointer()->GetViewport();
	Src = CRect2D<Sint32>( 0, 0, m_pTextureBlurLow->GetSize().x, m_pTextureBlurLow->GetSize().y );
	switch ( m_SceneMode )
	{
	case SCENE_MODE_2PASS_DOF:
		m_pPostEffect->Blur16Box( Dst, 0xFFFFFFFF, Src, m_pTextureBlurLow );
		break;
	case SCENE_MODE_2PASS_DOF_HIGH:
		m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureBlurLow );
		break;
	}

	//------------------------------------------------------------------------
	// ターゲットに描画
	//------------------------------------------------------------------------
	m_pRender->SetTextureAddressType( 0, TEXTURE_ADDRESS_CLAMP );
	m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	m_pRender->ResetRenderTarget();
	m_pRender->SetDepthStencil( NULL );
	Dst = m_pRender->GetDevicePointer()->GetViewport();
	m_pPostEffect->DepthOfField( Dst, m_pTextureBlurHigh, m_pTextureTarget, m_pTextureEffect );

	//------------------------------------------------------------------------
	// オプションごとの処理
	//------------------------------------------------------------------------
	switch ( m_SceneOption )
	{
	//-------------------------------------------------------
	// オプションなし
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_NO:
		break;
	//-------------------------------------------------------
	// HDRレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_HDR:
		{
			eTextureOperationType OperateTbl[] = {
				TEXTURE_OP_MUL,
				TEXTURE_OP_ADD,
				TEXTURE_OP_ADD,
			};

			ITexture *pTexTbl[] = {
				m_pTextureHDR_GaussV,
				m_pTextureHDR_GaussV2,
				m_pTextureHDR_GaussV4,
			};

			CRect2D<Sint32> SrcTbl[] = {
				CRect2D<Sint32>( 0, 0, pTexTbl[0]->GetSize().x, pTexTbl[0]->GetSize().y ),
				CRect2D<Sint32>( 0, 0, pTexTbl[1]->GetSize().x, pTexTbl[1]->GetSize().y ),
				CRect2D<Sint32>( 0, 0, pTexTbl[2]->GetSize().x, pTexTbl[2]->GetSize().y ),
			};

			m_pRender->SetDepthStencil( NULL );
			// 高輝度部分抽出
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureTarget->GetSize().x, m_pTextureTarget->GetSize().y );
			m_pPostEffect->HDR_DownSample( Dst, 0xFFFFFFFF, Src, m_pTextureTarget );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV->GetSize().x, m_pTextureHDR_GaussV->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH->GetSize().x, m_pTextureHDR_GaussH->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH );
			// 縮小バッファに
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV->GetSize().x, m_pTextureHDR_GaussV->GetSize().y );
			m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV2->GetSize().x, m_pTextureHDR_GaussV2->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV2 );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV2 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH2->GetSize().x, m_pTextureHDR_GaussH2->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH2 );
			// 縮小バッファに
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV2->GetSize().x, m_pTextureHDR_GaussV2->GetSize().y );
			m_pPostEffect->Blur9Box( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV2 );
			// 水平方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussH4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussV4->GetSize().x, m_pTextureHDR_GaussV4->GetSize().y );
			m_pPostEffect->GaussianH( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussV4 );
			// 垂直方向ガウス
			m_pRender->SetRenderTarget( m_pTextureHDR_GaussV4 );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			Src = CRect2D<Sint32>( 0, 0, m_pTextureHDR_GaussH4->GetSize().x, m_pTextureHDR_GaussH4->GetSize().y );
			m_pPostEffect->GaussianV( Dst, 0xFFFFFFFF, Src, m_pTextureHDR_GaussH4 );
			// ターゲットに描画
			m_pRender->ResetRenderTarget();
			m_pRender->SetTextureFilterType( 0, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetTextureFilterType( 1, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetTextureFilterType( 2, TEXTURE_FILTER_BILINEAR );
			m_pRender->SetDrawType( DRAW_TYPE_ADD_NOALPHA );
			Dst = m_pRender->GetDevicePointer()->GetViewport();
			m_pPostEffect->MultipleTexture( Dst, 0xFFFFFFFF, SrcTbl, OperateTbl, pTexTbl, 3 );
		}
		break;
	//-------------------------------------------------------
	// エッジレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_EDGE:
		// エッジのエフェクト
		m_pRender->SetDrawType( DRAW_TYPE_MULTIPLE );
		Dst = m_pRender->GetDevicePointer()->GetViewport();
		Src = CRect2D<Sint32>( 0, 0, m_pTextureEffect->GetSize().x, m_pTextureEffect->GetSize().y );
		m_pPostEffect->DrawEdge( Dst, 0xFFFFFFFF, Src, m_pTextureEffect );
		// バッファレンダリング
		if ( IsDrawBuffer )
		{
			Dst.x = 0;
			Dst.y = 0;
			Dst.w = 256;
			Dst.h = 256;
			Src = CRect2D<Sint32>( 0, 0, m_pTextureEffect->GetSize().x, m_pTextureEffect->GetSize().y );
			m_pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, m_pTextureEffect );
		}
		break;
	//-------------------------------------------------------
	// シャドウマップレンダリング
	//-------------------------------------------------------
	case SCENE_MODE_OPTION_SHADOW:
		// バッファレンダリング
		if ( IsDrawBuffer )
		{
			Dst.x = 0;
			Dst.y = 0;
			Dst.w = 256;
			Dst.h = 256;
			Src = CRect2D<Sint32>( 0, 0, m_pTextureShadow->GetSize().x, m_pTextureShadow->GetSize().y );
			m_pPostEffect->SingleTexture( Dst, 0xFFFFFFFF, Src, m_pTextureShadow );
		}
		break;
	}

	//------------------------------------------------------------------------
	// ステータス戻す
	//------------------------------------------------------------------------
	m_pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth )
{
	if ( m_IsBegin ) return;

	m_vLightColor[LIGHT_AMBIENT_SKY]   = vColorSky;
	m_vLightColor[LIGHT_AMBIENT_EARTH] = vColorEarth;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SetDirectionLight( CVector3D &vDirect, CVector3D &vColor )
{
	if ( m_IsBegin ) return;

	if ( vDirect.LengthSq() <= 0.001f )
	{
		m_vLightDirection.Set( 0.0f, 0.0f, 0.0f );
	}
	else
	{
		m_vLightDirection.Normalize( vDirect );
	}
	m_vLightColor[LIGHT_DIRECTION] = vColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance )
{
	if ( m_IsBegin ) return;

	if ( m_PointLightCount < LIGHT_POINT_MAX )
	{
		m_vLightPosition[m_PointLightCount]		= vPosition;
		m_vLightColor[m_PointLightCount]		= vColor;
		m_fLightDistance[m_PointLightCount]		= fDistance;

		m_PointLightCount++;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CSceneManager::SetRenderTargetSize( CPoint2D<Uint32> Size )
{
	//--------------------------------------------------------------------------------------
	// 古いの解放
	//--------------------------------------------------------------------------------------
	SAFE_RELEASE( m_pDepthStencil );
	SAFE_RELEASE( m_pDepthStencilShadow );
	SAFE_RELEASE( m_pTextureEffect );
	SAFE_RELEASE( m_pTextureTarget );
	SAFE_RELEASE( m_pTextureBlurLow );
	SAFE_RELEASE( m_pTextureBlurHigh );
	SAFE_RELEASE( m_pTextureHDR_GaussH );
	SAFE_RELEASE( m_pTextureHDR_GaussV );
	SAFE_RELEASE( m_pTextureHDR_GaussH2 );
	SAFE_RELEASE( m_pTextureHDR_GaussV2 );
	SAFE_RELEASE( m_pTextureHDR_GaussH4 );
	SAFE_RELEASE( m_pTextureHDR_GaussV4 );
	SAFE_RELEASE( m_pTextureShadow );

	//--------------------------------------------------------------------------------------
	// サイズチェック
	//--------------------------------------------------------------------------------------
	m_TargetSize = m_pRender->GetDevicePointer()->GetGraphicCardPointer()->GetTextureSize( Size );

	//--------------------------------------------------------------------------------------
	// テクスチャフォーマット
	//--------------------------------------------------------------------------------------
	CTextureConfig ConfBackup = m_pRender->GetTextureConfig();
	CTextureConfig Conf = ConfBackup;
	Conf.SetColorKey( 0x00000000 );

	switch ( m_SceneOption )
	{
	// オプションなし
	case SCENE_MODE_OPTION_NO:
		Conf.SetFormat( FORMAT_TARGET32 );
		break;
	// HDRレンダリング
	case SCENE_MODE_OPTION_HDR:
		// ターゲット生成
		Conf.SetFormat( FORMAT_TARGET32 );
		m_pRender->SetTextureConfig( Conf );
		m_pTextureHDR_GaussH	 = m_pRender->CreateTextureRenderTarget( m_TargetSize.x/ 4, m_TargetSize.y/ 4 );
		m_pTextureHDR_GaussV	 = m_pRender->CreateTextureRenderTarget( m_TargetSize.x/ 4, m_TargetSize.y/ 4 );
		m_pTextureHDR_GaussH2	 = m_pRender->CreateTextureRenderTarget( m_TargetSize.x/ 8, m_TargetSize.y/ 8 );
		m_pTextureHDR_GaussV2	 = m_pRender->CreateTextureRenderTarget( m_TargetSize.x/ 8, m_TargetSize.y/ 8 );
		m_pTextureHDR_GaussH4	 = m_pRender->CreateTextureRenderTarget( m_TargetSize.x/16, m_TargetSize.y/16 );
		m_pTextureHDR_GaussV4	 = m_pRender->CreateTextureRenderTarget( m_TargetSize.x/16, m_TargetSize.y/16 );
		Conf.SetFormat( FORMAT_TARGET_HDR );
		// 失敗？
		if ( m_pTextureHDR_GaussH->IsInvalid() ||
			m_pTextureHDR_GaussV->IsInvalid() ||
			m_pTextureHDR_GaussH2->IsInvalid() ||
			m_pTextureHDR_GaussV2->IsInvalid() ||
			m_pTextureHDR_GaussH4->IsInvalid() ||
			m_pTextureHDR_GaussV4->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneOption = SCENE_MODE_OPTION_NO;
			return SetRenderTargetSize( Size );
		}
		break;
	// エッジレンダリング
	case SCENE_MODE_OPTION_EDGE:
		Conf.SetFormat( FORMAT_TARGET32 );
		m_pRender->SetTextureConfig( Conf );
		m_pTextureEffect = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		// 失敗？
		if ( m_pTextureEffect->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneOption = SCENE_MODE_OPTION_NO;
			return SetRenderTargetSize( Size );
		}
		break;
	// 影レンダリング
	case SCENE_MODE_OPTION_SHADOW:
		m_pDepthStencilShadow = m_pRender->CreateDepthStencilSurface( 2048, 2048, FORMAT_DEPTH16 );
		Conf.SetFormat( FORMAT_TARGET_SHADOWMAP );
		m_pRender->SetTextureConfig( Conf );
		m_pTextureShadow = m_pRender->CreateTextureRenderTarget( 2048, 2048 );
		// 失敗？
		if ( m_pTextureShadow->IsInvalid() || m_pDepthStencilShadow->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneOption = SCENE_MODE_OPTION_NO;
			return SetRenderTargetSize( Size );
		}
		Conf.SetFormat( FORMAT_TARGET32 );
		break;
	}

	m_pRender->SetTextureConfig( Conf );

	//--------------------------------------------------------------------------------------
	// シーンモードごとに設定
	//--------------------------------------------------------------------------------------
	switch ( m_SceneMode )
	{
	// 通常レンダリング
	case SCENE_MODE_NOT_MANAGED:
		break;
	// 管理レンダリング
	case SCENE_MODE_MANAGED:
		m_pDepthStencil		= m_pRender->CreateDepthStencilSurface( m_TargetSize.x, m_TargetSize.y, FORMAT_DEPTH16 );
		m_pTextureTarget	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		// 失敗？
		if ( m_pDepthStencil->IsInvalid() ||
			m_pTextureTarget->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneMode = SCENE_MODE_NOT_MANAGED;
			return SetRenderTargetSize( Size );
		}
		break;
	// 1-Pass被写界深度
	case SCENE_MODE_1PASS_DOF:
		m_pDepthStencil		= m_pRender->CreateDepthStencilSurface( m_TargetSize.x, m_TargetSize.y, FORMAT_DEPTH16 );
		m_pTextureTarget	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		m_pTextureBlurLow	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 2, m_TargetSize.y / 2 );
		m_pTextureBlurHigh	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 2, m_TargetSize.y / 2 );
		// 失敗？
		if ( m_pDepthStencil->IsInvalid() ||
			m_pTextureTarget->IsInvalid() ||
			m_pTextureBlurLow->IsInvalid() ||
			m_pTextureBlurHigh->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneMode = SCENE_MODE_MANAGED;
			return SetRenderTargetSize( Size );
		}
		break;
	// 2-Pass被写界深度
	case SCENE_MODE_2PASS_DOF:
		m_pDepthStencil		= m_pRender->CreateDepthStencilSurface( m_TargetSize.x, m_TargetSize.y, FORMAT_DEPTH16 );
		m_pTextureTarget	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		m_pTextureBlurLow	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 2, m_TargetSize.y / 2 );
		m_pTextureBlurHigh	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 2, m_TargetSize.y / 2 );
		if ( m_pTextureEffect == NULL )
		{
			m_pTextureEffect = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		}
		// 失敗？
		if ( m_pDepthStencil->IsInvalid() ||
			m_pTextureTarget->IsInvalid() ||
			m_pTextureBlurLow->IsInvalid() ||
			m_pTextureBlurHigh->IsInvalid() ||
			m_pTextureEffect->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneMode = SCENE_MODE_MANAGED;
			return SetRenderTargetSize( Size );
		}
		break;
	// 1-Pass被写界深度
	case SCENE_MODE_1PASS_DOF_HIGH:
		m_pDepthStencil		= m_pRender->CreateDepthStencilSurface( m_TargetSize.x, m_TargetSize.y, FORMAT_DEPTH16 );
		m_pTextureTarget	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		m_pTextureBlurLow	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		m_pTextureBlurHigh	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		// 失敗？
		if ( m_pDepthStencil->IsInvalid() ||
			m_pTextureTarget->IsInvalid() ||
			m_pTextureBlurLow->IsInvalid() ||
			m_pTextureBlurHigh->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneMode = SCENE_MODE_MANAGED;
			return SetRenderTargetSize( Size );
		}
		break;
	// 2-Pass被写界深度
	case SCENE_MODE_2PASS_DOF_HIGH:
		m_pDepthStencil		= m_pRender->CreateDepthStencilSurface( m_TargetSize.x, m_TargetSize.y, FORMAT_DEPTH16 );
		m_pTextureTarget	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		m_pTextureBlurLow	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		m_pTextureBlurHigh	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		if ( m_pTextureEffect == NULL )
		{
			m_pTextureEffect = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y );
		}
		// 失敗？
		if ( m_pDepthStencil->IsInvalid() ||
			m_pTextureTarget->IsInvalid() ||
			m_pTextureBlurLow->IsInvalid() ||
			m_pTextureBlurHigh->IsInvalid() ||
			m_pTextureEffect->IsInvalid() )
		{
			m_pRender->SetTextureConfig( ConfBackup );
			m_SceneMode = SCENE_MODE_MANAGED;
			return SetRenderTargetSize( Size );
		}
		break;
	}

	m_pRender->SetTextureConfig( ConfBackup );

	// 使用されるターゲットのサイズ
	return m_TargetSize;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias )
{
	if ( m_IsBegin ) return;

	CVector3D vEye = vPosition;
	CVector3D vAt = vTarget;
	CVector3D vUp( 0.0f, 1.0f, 0.0f );

	// 真上or真下を見ている時
	CVector3D vDir = vTarget - vPosition;
	if ( (vDir.x == 0.0f) && (vDir.z == 0.0f) )
	{
		if ( vDir.y > 0.0f )
		{
			vUp = CVector3D( 0.0f, 0.0f, -1.0f );
		}
		else
		{
			vUp = CVector3D( 0.0f, 0.0f, +1.0f );
		}
	}

	// プロジェクション行列
	CMatrix mProject;
	mProject.Ortho( fSize, fSize, fNear, fFar );

	// ビュー行列
	m_mShadowView.LookAt( vEye, vAt, vUp );

	// ビューｘプロジェクション
	m_mShadowViewProj = m_mShadowView * mProject;

	// バイアス
	m_fShadowMapNear	= fNear;
	m_fShadowMapFar		= fFar;
	m_fShadowMapBias	= fBias;

	// 平行光源
	CVector3D vDirect = vAt - vEye;
	if ( vDirect.LengthSq() <= 0.001f )
	{
		m_vLightDirection.Set( 0.0f, 0.0f, 0.0f );
	}
	else
	{
		m_vLightDirection.Normalize( vDirect );
	}

}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SetFogEnable( Bool Enable )
{
	m_IsFog = Enable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SetFog( Float fNear, Float fFar, CColor Color )
{
	if ( m_IsBegin ) return;

	m_fFogNear	= fNear;
	m_fFogFar	= fFar;
	m_FogColor	= Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SetDepthOfFieldForcus( Float fForcusZ, Float fPower )
{
	m_fFocusDepth = (fForcusZ - m_Camera.GetNearClip()) / (m_Camera.GetFarClip() - m_Camera.GetNearClip());
	m_fFocusDepth = 1.0f - m_fFocusDepth;
	m_fFocusPower = fPower;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManager::IsEndSceneConstruct( void )
{
	return m_EventEndConstruct.IsSignal( 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManager::AddObject( CSceneObject *pObject, CRenderData &RenderData, CVector3D &vCenter )
{
	if ( !m_IsBegin ) return -1;

	// 書き込み可能？
	if ( m_QuePos < SCENE_MANAGER_QUE_MAX )
	{
		Sint32 No = m_QuePos++;
		SSceneRenderObject &Que = m_QueTbl[No];
		// キューに追加
		Que.IsFog		= m_IsFog;
		Que.pObject		= pObject;
		Que.vCenter		= vCenter;
		Que.RenderData	= RenderData;
		Que.fKey		= 0.0f;
		Que.pNext		= NULL;

		return No;
	}

	return -1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::InsertList( SSceneRenderObject &Obj )
{
	//----------------------------------------------------------------------------------------
	// オブジェクトの中心位置をカメラ空間に変換
	//----------------------------------------------------------------------------------------
	CMatrix Mtx;
	Mtx.Multiply( Obj.RenderData.mWorld, m_View );
	Obj.vCenter.TransformCoord( Obj.vCenter, Mtx );
	Obj.fKey = Obj.vCenter.LengthSq();

	//----------------------------------------------------------------------------------------
	// リストに追加
	//----------------------------------------------------------------------------------------
	// １つ目orソートなし
	if ( (m_pObjectListTop == NULL) || !m_IsSort )
	{
		Obj.pNext = m_pObjectListTop;
		m_pObjectListTop = &Obj;
	}
	// ２つ目以降でソートする
	ef ( m_IsSort )
	{
		// 先頭？
		if ( Obj.fKey >= m_pObjectListTop->fKey )
		{
			Obj.pNext = m_pObjectListTop;
			m_pObjectListTop = &Obj;
		}
		// 該当箇所へ挿入
		else
		{
			// 該当箇所へ挿入
			SSceneRenderObject *pSrc = m_pObjectListTop;
			while ( (pSrc->pNext != NULL) && (Obj.fKey < pSrc->pNext->fKey) )
			{
				pSrc = pSrc->pNext;
			}
			Obj.pNext = pSrc->pNext;
			pSrc->pNext = &Obj;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManager::SearchPointLight( Sint32 NoTbl[], CVector3D vPosition )
{
	static Float fRangeInTbl[LIGHT_POINT_MAX];
	static Sint32 NoInTbl[LIGHT_POINT_MAX];
	Sint32 NoInMax = 0;
	Sint32 Num;
	Float fRangeMax = 0.0f;

	Sint32 Max = 0;

	//--------------------------------------------------------
	// もともとライト数が規定数に収まってる？
	//--------------------------------------------------------
	Num = m_PointLightCount;
	if ( Num <= POINT_LIGHT_VALID_MAX )
	{
		for ( Sint32 i = 0; i < Num; i++ )
		{
			NoTbl[i] = i;
		}
		return Num;
	}

	//--------------------------------------------------------
	// 適用範囲内のポイントライトを検索
	//--------------------------------------------------------
	Num = m_PointLightCount;
	for ( Sint32 i = 0; i < Num; i++ )
	{
		CVector3D vDistance = vPosition - m_vLightPosition[i];
		fRangeInTbl[i] = vDistance.LengthSq();
		if ( fRangeInTbl[i] < m_fLightDistance[i] * m_fLightDistance[i] )
		{
			if ( fRangeMax < fRangeInTbl[i] )
			{
				fRangeMax = fRangeInTbl[i];
			}
			NoInTbl[NoInMax++] = i;
		}
	}

	//--------------------------------------------------------
	// この時点でライト数が規定数に収まってる？
	//--------------------------------------------------------
	if ( NoInMax <= POINT_LIGHT_VALID_MAX )
	{
		for ( Sint32 i = 0; i < Num; i++ )
		{
			NoTbl[i] = NoInTbl[i];
		}
		return NoInMax;
	}

	//--------------------------------------------------------
	// ライトの中から距離の近い順にソート
	//--------------------------------------------------------
	Float fRangeTbl[] = { fRangeMax, fRangeMax, fRangeMax, fRangeMax };
	for ( Sint32 i = 0; i < NoInMax; i++ )
	{
		// ４つのリストから最も距離の遠いライトを検索
		Sint32 FarNo = 0;
		for ( Sint32 j = 1; j < POINT_LIGHT_VALID_MAX; j++ )
		{
			// より遠いものが見つかったら更新
			if ( fRangeTbl[FarNo] < fRangeTbl[j] )
			{
				FarNo = j;
			}
		}

		// リスト中の最も遠いものが現在のライトより遠ければ入れ替える
		if ( fRangeTbl[FarNo] > fRangeInTbl[i] )
		{
			fRangeTbl[FarNo] = fRangeInTbl[i];
			NoTbl[FarNo] = NoInTbl[i];
		}
	}

	return Max;
}

//-----------------------------------------------------------------------------------
/**。
*/
//-----------------------------------------------------------------------------------
void CSceneManager::ComputeRenderData( SSceneRenderObject &Obj )
{
	CVector4D vPositionTbl[4];
	CVector4D vColorTbl[4];

	CRenderData &RD = Obj.RenderData;

	// PointLightPosition & PointLightColor
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Obj.vPointLightPositionTbl[i] = CVector4D( 0.0f, 0.0f, 0.0f, 0.0f );
		Obj.vPointLightColorTbl[i]    = CVector4D( 0.0f, 0.0f, 0.0f, 0.0f );
	}

	Sint32 NoTbl[4];
	Sint32 NoMax = SearchPointLight( NoTbl, Obj.vCenter );
	if ( NoMax > 0 )
	{
		for ( Sint32 i = 0; i < NoMax; i++ )
		{
			CVector4D vPos = m_vLightPosition[NoTbl[i]];
			Obj.vPointLightPositionTbl[i].TransformCoord( vPos, RD.mWorldInverse );
			Obj.vPointLightPositionTbl[i].w = m_fLightDistance[NoTbl[i]];
			Obj.vPointLightColorTbl[i].x = m_vLightColor[NoTbl[i]].x;
			Obj.vPointLightColorTbl[i].y = m_vLightColor[NoTbl[i]].y;
			Obj.vPointLightColorTbl[i].z = m_vLightColor[NoTbl[i]].z;
		}
	}
	Obj.PointLightCount = NoMax;

	// シェーダー
	Bool IsShadow = m_SceneOption == SCENE_MODE_OPTION_SHADOW;
	SRenderShaderData &SD = CRenderData::GetShader( RD.Type, Obj.PointLightCount, IsShadow );

	// WorldView
	Obj.mWorldView.Multiply( RD.mWorld, m_View );

	// WorldViewProjection
	if ( SD.hWorldViewProjection != NULL )
	{
		Obj.mWorldViewProjection.Multiply( RD.mWorld, m_ViewProjection );
	}

	// DirectionalLightDirection
	if ( SD.hDirectionalLightDirection != NULL )
	{
		CVector4D vDir = -m_vLightDirection;
		Obj.vLightDiection.TransformNormal( vDir, RD.mWorldInverse );
	}

	// 影あり
	if ( SD.hShadowWorldViewProjection != NULL )
	{
		if ( m_SceneOption == SCENE_MODE_OPTION_SHADOW )
		{
			Obj.mShadowWorldViewProjection.Multiply( RD.mWorld, m_mShadowViewProj );

			// ShadowMapTransform
			if ( SD.hShadowMapTransform != NULL )
			{
				CMatrix mTemp;
				mTemp.Multiply( RD.mWorld, m_mShadowView );
				Obj.vShadowMapTransform = CVector4D( mTemp.x.z, mTemp.y.z, mTemp.z.z, mTemp.w.z );
			}
		}
	}

	// DepthTransform
	if ( SD.hDepthTransform != NULL )
	{
		Obj.vDepthTransform = CVector4D( Obj.mWorldView.x.z, Obj.mWorldView.y.z, Obj.mWorldView.z.z, Obj.mWorldView.w.z );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CSceneManager::GetRenderingRequestCount( void )
{
	return m_RenderRequestCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CSceneManager::GetRenderingCount( void )
{
	return m_RenderCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CSceneManager::GetOcculusion( Uint32 Index )
{
	if ( Index < SCENE_MANAGER_QUE_MAX )
	{
		return m_QueTbl[Index].pOcclusion->GetPixels();
	}

	return 0xFFFFFFFF;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager::SceneConstruction( void )
{
	// イベントループ
	for ( ; ; )
	{
		// イベント待ち
		Sint32 Ret = m_Event.Wait();
		if ( m_IsEndManage ) break;
		if ( Ret == -1 ) continue;

		m_Event.Reset( Ret );

		// キューからデータを取り出す
		Uint32 Max = m_QuePos;
		for ( Uint32 i = 0; i < Max; i++ )
		{
			Bool IsDraw = true;

			// ビューフラスタムカリングする？
			if ( m_QueTbl[i].RenderData.IsCullTest )
			{
				// カリング
				if ( !m_Camera.ViewfrustumCulling( m_QueTbl[i].RenderData.CullBox ) )
				{
					// 画面外
					IsDraw = false;
				}
			}

			// 描画する？
			if ( IsDraw )
			{
				// リストに追加
				InsertList( m_QueTbl[i] );

				// 各種レンダリング用データの事前生成
				ComputeRenderData( m_QueTbl[i] );
			}
		}

		// シーン構築終わった
		m_EventEndConstruct.Set();
	}
}

#endif // ENABLE_3D
