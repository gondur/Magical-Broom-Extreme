

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Render/CRenderData.h"
#include "Render/CShader.h"
#include "Core/CDevice.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// FxFile
//-----------------------------------------------------------------------------------

//--------------------------------------------------------------
// P
//--------------------------------------------------------------
static const Uint8 g_HLSL_P[] = {
	#include "FxFile/HLSL_P.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PA[] = {
	#include "FxFile/HLSL_PA.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PS[] = {
	#include "FxFile/HLSL_PS.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PAS[] = {
	#include "FxFile/HLSL_PAS.inc"
};

//--------------------------------------------------------------
// PT
//--------------------------------------------------------------

static const Uint8 g_HLSL_PT[] = {
	#include "FxFile/HLSL_PT.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PTA[] = {
	#include "FxFile/HLSL_PTA.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PTS[] = {
	#include "FxFile/HLSL_PTS.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PTAS[] = {
	#include "FxFile/HLSL_PTAS.inc"
};

//--------------------------------------------------------------
// PL
//--------------------------------------------------------------
static const Uint8 g_HLSL_PL_0[] = {
	#include "FxFile/HLSL_PL_0.inc"
};
static const Uint8 g_HLSL_PL_1[] = {
	#include "FxFile/HLSL_PL_1.inc"
};
static const Uint8 g_HLSL_PL_2[] = {
	#include "FxFile/HLSL_PL_2.inc"
};
static const Uint8 g_HLSL_PL_3[] = {
	#include "FxFile/HLSL_PL_3.inc"
};
static const Uint8 g_HLSL_PL_4[] = {
	#include "FxFile/HLSL_PL_4.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PLA_0[] = {
	#include "FxFile/HLSL_PLA_0.inc"
};
static const Uint8 g_HLSL_PLA_1[] = {
	#include "FxFile/HLSL_PLA_1.inc"
};
static const Uint8 g_HLSL_PLA_2[] = {
	#include "FxFile/HLSL_PLA_2.inc"
};
static const Uint8 g_HLSL_PLA_3[] = {
	#include "FxFile/HLSL_PLA_3.inc"
};
static const Uint8 g_HLSL_PLA_4[] = {
	#include "FxFile/HLSL_PLA_4.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PLS_0[] = {
	#include "FxFile/HLSL_PLS_0.inc"
};
static const Uint8 g_HLSL_PLS_1[] = {
	#include "FxFile/HLSL_PLS_1.inc"
};
static const Uint8 g_HLSL_PLS_2[] = {
	#include "FxFile/HLSL_PLS_2.inc"
};
static const Uint8 g_HLSL_PLS_3[] = {
	#include "FxFile/HLSL_PLS_3.inc"
};
static const Uint8 g_HLSL_PLS_4[] = {
	#include "FxFile/HLSL_PLS_4.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PLAS_0[] = {
	#include "FxFile/HLSL_PLAS_0.inc"
};
static const Uint8 g_HLSL_PLAS_1[] = {
	#include "FxFile/HLSL_PLAS_1.inc"
};
static const Uint8 g_HLSL_PLAS_2[] = {
	#include "FxFile/HLSL_PLAS_2.inc"
};
static const Uint8 g_HLSL_PLAS_3[] = {
	#include "FxFile/HLSL_PLAS_3.inc"
};
static const Uint8 g_HLSL_PLAS_4[] = {
	#include "FxFile/HLSL_PLAS_4.inc"
};

//--------------------------------------------------------------
// PTL
//--------------------------------------------------------------
static const Uint8 g_HLSL_PTL_0[] = {
	#include "FxFile/HLSL_PTL_0.inc"
};
static const Uint8 g_HLSL_PTL_1[] = {
	#include "FxFile/HLSL_PTL_1.inc"
};
static const Uint8 g_HLSL_PTL_2[] = {
	#include "FxFile/HLSL_PTL_2.inc"
};
static const Uint8 g_HLSL_PTL_3[] = {
	#include "FxFile/HLSL_PTL_3.inc"
};
static const Uint8 g_HLSL_PTL_4[] = {
	#include "FxFile/HLSL_PTL_4.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PTLA_0[] = {
	#include "FxFile/HLSL_PTLA_0.inc"
};
static const Uint8 g_HLSL_PTLA_1[] = {
	#include "FxFile/HLSL_PTLA_1.inc"
};
static const Uint8 g_HLSL_PTLA_2[] = {
	#include "FxFile/HLSL_PTLA_2.inc"
};
static const Uint8 g_HLSL_PTLA_3[] = {
	#include "FxFile/HLSL_PTLA_3.inc"
};
static const Uint8 g_HLSL_PTLA_4[] = {
	#include "FxFile/HLSL_PTLA_4.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PTLS_0[] = {
	#include "FxFile/HLSL_PTLS_0.inc"
};
static const Uint8 g_HLSL_PTLS_1[] = {
	#include "FxFile/HLSL_PTLS_1.inc"
};
static const Uint8 g_HLSL_PTLS_2[] = {
	#include "FxFile/HLSL_PTLS_2.inc"
};
static const Uint8 g_HLSL_PTLS_3[] = {
	#include "FxFile/HLSL_PTLS_3.inc"
};
static const Uint8 g_HLSL_PTLS_4[] = {
	#include "FxFile/HLSL_PTLS_4.inc"
};

//--------------------------------------------------------------
static const Uint8 g_HLSL_PTLAS_0[] = {
	#include "FxFile/HLSL_PTLAS_0.inc"
};
static const Uint8 g_HLSL_PTLAS_1[] = {
	#include "FxFile/HLSL_PTLAS_1.inc"
};
static const Uint8 g_HLSL_PTLAS_2[] = {
	#include "FxFile/HLSL_PTLAS_2.inc"
};
static const Uint8 g_HLSL_PTLAS_3[] = {
	#include "FxFile/HLSL_PTLAS_3.inc"
};
static const Uint8 g_HLSL_PTLAS_4[] = {
	#include "FxFile/HLSL_PTLAS_4.inc"
};

//--------------------------------------------------------------
static const Uint8 *g_HLSL_Tbl[SHADOW_TYPE_MAX][POLYGON_TYPE_MAX][POINT_LIGHT_COUNT_TYPE_MAX] = {
	// SHADOW_TYPE_DISABLE
	{
		// P POLYGON_TYPE_TRANSFORM
		{
			g_HLSL_P, g_HLSL_P, g_HLSL_P, g_HLSL_P, g_HLSL_P,
		},
		// PT POLYGON_TYPE_TRANSFORM_TEXTURE
		{
			g_HLSL_PT, g_HLSL_PT, g_HLSL_PT, g_HLSL_PT, g_HLSL_PT,
		},
		// PL POLYGON_TYPE_TRANSFORM_LIGHTING
		{
			g_HLSL_PL_1, g_HLSL_PL_1, g_HLSL_PL_2, g_HLSL_PL_3, g_HLSL_PL_4,
		},
		// PTL POLYGON_TYPE_TRANSFORM_LIGHTING_TEXTURE
		{
			g_HLSL_PTL_0, g_HLSL_PTL_1, g_HLSL_PTL_2, g_HLSL_PTL_3, g_HLSL_PTL_4,
		},
		// PA POLYGON_TYPE_TRANSFORM_ANIMATION
		{
			g_HLSL_PA, g_HLSL_PA, g_HLSL_PA, g_HLSL_PA, g_HLSL_PA,
		},
		// PTA POLYGON_TYPE_TRANSFORM_ANIMATION_TEXTURE
		{
			g_HLSL_PTA, g_HLSL_PTA, g_HLSL_PTA, g_HLSL_PTA, g_HLSL_PTA,
		},
		// PLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING
		{
			g_HLSL_PLA_0, g_HLSL_PLA_1, g_HLSL_PLA_2, g_HLSL_PLA_3, g_HLSL_PLA_4,
		},
		// PTLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING_TEXTURE,
		{
			g_HLSL_PTLA_0, g_HLSL_PTLA_1, g_HLSL_PTLA_2, g_HLSL_PTLA_3, g_HLSL_PTLA_4,
		},
	},
	// SHADOW_TYPE_ENABLE
	{
		// P POLYGON_TYPE_TRANSFORM
		{
			g_HLSL_PS, g_HLSL_PS, g_HLSL_PS, g_HLSL_PS, g_HLSL_PS,
		},
		// PT POLYGON_TYPE_TRANSFORM_TEXTURE
		{
			g_HLSL_PTS, g_HLSL_PTS, g_HLSL_PTS, g_HLSL_PTS, g_HLSL_PTS,
		},
		// PL POLYGON_TYPE_TRANSFORM_LIGHTING
		{
			g_HLSL_PLS_1, g_HLSL_PLS_1, g_HLSL_PLS_2, g_HLSL_PLS_3, g_HLSL_PLS_4,
		},
		// PTL POLYGON_TYPE_TRANSFORM_LIGHTING_TEXTURE
		{
			g_HLSL_PTLS_0, g_HLSL_PTLS_1, g_HLSL_PTLS_2, g_HLSL_PTLS_3, g_HLSL_PTLS_4,
		},
		// PA POLYGON_TYPE_TRANSFORM_ANIMATION
		{
			g_HLSL_PAS, g_HLSL_PAS, g_HLSL_PAS, g_HLSL_PAS, g_HLSL_PAS,
		},
		// PTA POLYGON_TYPE_TRANSFORM_ANIMATION_TEXTURE
		{
			g_HLSL_PTAS, g_HLSL_PTAS, g_HLSL_PTAS, g_HLSL_PTAS, g_HLSL_PTAS,
		},
		// PLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING
		{
			g_HLSL_PLAS_0, g_HLSL_PLAS_1, g_HLSL_PLAS_2, g_HLSL_PLAS_3, g_HLSL_PLAS_4,
		},
		// PTLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING_TEXTURE,
		{
			g_HLSL_PTLAS_0, g_HLSL_PTLAS_1, g_HLSL_PTLAS_2, g_HLSL_PTLAS_3, g_HLSL_PTLAS_4,
		},
	}
};

static const Uint32 g_HLSL_SizeTbl[SHADOW_TYPE_MAX][POLYGON_TYPE_MAX][POINT_LIGHT_COUNT_TYPE_MAX] = {
	// SHADOW_TYPE_DISABLE
	{
		// P POLYGON_TYPE_TRANSFORM
		{
			sizeof(g_HLSL_P), sizeof(g_HLSL_P), sizeof(g_HLSL_P), sizeof(g_HLSL_P), sizeof(g_HLSL_P),
		},
		// PT POLYGON_TYPE_TRANSFORM_TEXTURE
		{
			sizeof(g_HLSL_PT), sizeof(g_HLSL_PT), sizeof(g_HLSL_PT), sizeof(g_HLSL_PT), sizeof(g_HLSL_PT),
		},
		// PL POLYGON_TYPE_TRANSFORM_LIGHTING
		{
			sizeof(g_HLSL_PL_1), sizeof(g_HLSL_PL_1), sizeof(g_HLSL_PL_2), sizeof(g_HLSL_PL_3), sizeof(g_HLSL_PL_4),
		},
		// PTL POLYGON_TYPE_TRANSFORM_LIGHTING_TEXTURE
		{
			sizeof(g_HLSL_PTL_0), sizeof(g_HLSL_PTL_1), sizeof(g_HLSL_PTL_2), sizeof(g_HLSL_PTL_3), sizeof(g_HLSL_PTL_4),
		},
		// PA POLYGON_TYPE_TRANSFORM_ANIMATION
		{
			sizeof(g_HLSL_PA), sizeof(g_HLSL_PA), sizeof(g_HLSL_PA), sizeof(g_HLSL_PA), sizeof(g_HLSL_PA),
		},
		// PTA POLYGON_TYPE_TRANSFORM_ANIMATION_TEXTURE
		{
			sizeof(g_HLSL_PTA), sizeof(g_HLSL_PTA), sizeof(g_HLSL_PTA), sizeof(g_HLSL_PTA), sizeof(g_HLSL_PTA),
		},
		// PLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING
		{
			sizeof(g_HLSL_PLA_0), sizeof(g_HLSL_PLA_1), sizeof(g_HLSL_PLA_2), sizeof(g_HLSL_PLA_3), sizeof(g_HLSL_PLA_4),
		},
		// PTLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING_TEXTURE,
		{
			sizeof(g_HLSL_PTLA_0), sizeof(g_HLSL_PTLA_1), sizeof(g_HLSL_PTLA_2), sizeof(g_HLSL_PTLA_3), sizeof(g_HLSL_PTLA_4),
		},
	},
	// SHADOW_TYPE_ENABLE
	{
		// P POLYGON_TYPE_TRANSFORM
		{
			sizeof(g_HLSL_PS), sizeof(g_HLSL_PS), sizeof(g_HLSL_PS), sizeof(g_HLSL_PS), sizeof(g_HLSL_PS),
		},
		// PT POLYGON_TYPE_TRANSFORM_TEXTURE
		{
			sizeof(g_HLSL_PTS), sizeof(g_HLSL_PTS), sizeof(g_HLSL_PTS), sizeof(g_HLSL_PTS), sizeof(g_HLSL_PTS),
		},
		// PL POLYGON_TYPE_TRANSFORM_LIGHTING
		{
			sizeof(g_HLSL_PLS_1), sizeof(g_HLSL_PLS_1), sizeof(g_HLSL_PLS_2), sizeof(g_HLSL_PLS_3), sizeof(g_HLSL_PLS_4),
		},
		// PTL POLYGON_TYPE_TRANSFORM_LIGHTING_TEXTURE
		{
			sizeof(g_HLSL_PTLS_0), sizeof(g_HLSL_PTLS_1), sizeof(g_HLSL_PTLS_2), sizeof(g_HLSL_PTLS_3), sizeof(g_HLSL_PTLS_4),
		},
		// PA POLYGON_TYPE_TRANSFORM_ANIMATION
		{
			sizeof(g_HLSL_PAS), sizeof(g_HLSL_PAS), sizeof(g_HLSL_PAS), sizeof(g_HLSL_PAS), sizeof(g_HLSL_PAS),
		},
		// PTA POLYGON_TYPE_TRANSFORM_ANIMATION_TEXTURE
		{
			sizeof(g_HLSL_PTAS), sizeof(g_HLSL_PTAS), sizeof(g_HLSL_PTAS), sizeof(g_HLSL_PTAS), sizeof(g_HLSL_PTAS),
		},
		// PLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING
		{
			sizeof(g_HLSL_PLAS_0), sizeof(g_HLSL_PLAS_1), sizeof(g_HLSL_PLAS_2), sizeof(g_HLSL_PLAS_3), sizeof(g_HLSL_PLAS_4),
		},
		// PTLA POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING_TEXTURE,
		{
			sizeof(g_HLSL_PTLAS_0), sizeof(g_HLSL_PTLAS_1), sizeof(g_HLSL_PTLAS_2), sizeof(g_HLSL_PTLAS_3), sizeof(g_HLSL_PTLAS_4),
		},
	},
};


//--------------------------------------------------------------
static Uint32 g_VertexFlagTbl[] = {
	VERTEX_ELEMENT_3DBASE,																						// POLYGON_TYPE_TRANSFORM,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DTEXTURE,															// POLYGON_TYPE_TRANSFORM_TEXTURE,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DLIGHT,																// POLYGON_TYPE_TRANSFORM_LIGHTING,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DLIGHT | VERTEX_ELEMENT_3DTEXTURE,									// POLYGON_TYPE_TRANSFORM_LIGHTING_TEXTURE,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DANIMATION,															// POLYGON_TYPE_TRANSFORM_ANIMATION,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DANIMATION | VERTEX_ELEMENT_3DTEXTURE,								// POLYGON_TYPE_TRANSFORM_ANIMATION_TEXTURE,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DANIMATION | VERTEX_ELEMENT_3DLIGHT,								// POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING,
	VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DANIMATION | VERTEX_ELEMENT_3DLIGHT | VERTEX_ELEMENT_3DTEXTURE,		// POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING_TEXTURE,
};

//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
SRenderShaderData CRenderData::m_Shader[POLYGON_TYPE_MAX][POINT_LIGHT_COUNT_TYPE_MAX][SHADOW_TYPE_MAX];


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRenderData::Initialize( CRender *pRender )
{
	for ( Uint32 i = 0; i < POLYGON_TYPE_MAX; i++ )
	{
		for ( Uint32 j = 0; j < POINT_LIGHT_COUNT_TYPE_MAX; j++ )
		{
			for ( Uint32 k = 0; k < SHADOW_TYPE_MAX; k++ )
			{
				// シェーダー生成
				CreateShader(
					m_Shader[i][j][k],
					i,
					j,
					k == SHADOW_TYPE_ENABLE,
					pRender );
				// ハンドル
				UpdateShaderHandle(
					m_Shader[i][j][k] );
			}
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRenderData::Finalize( void )
{
	for ( Uint32 i = 0; i < POLYGON_TYPE_MAX; i++ )
	{
		for ( Uint32 j = 0; j < POINT_LIGHT_COUNT_TYPE_MAX; j++ )
		{
			for ( Uint32 k = 0; k < SHADOW_TYPE_MAX; k++ )
			{
				SAFE_RELEASE( m_Shader[i][j][k].pShader );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
SRenderShaderData &CRenderData::GetShader( ePolygonType PolyType, Uint32 PointLightCount, Bool IsShadow )
{
	return m_Shader[PolyType][PointLightCount][IsShadow?1:0];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRenderData::CreateShader( SRenderShaderData &Shader, Uint32 PolygonType, Uint32 PointLightNum, Bool IsShadowEnable, CRender *pRender )
{
	//------------------------------------------------------------------------
	// シェーダー
	//------------------------------------------------------------------------
	const Uint8 *pShader = g_HLSL_Tbl[IsShadowEnable?1:0][PolygonType][PointLightNum];
	Uint32 ShaderSize = g_HLSL_SizeTbl[IsShadowEnable?1:0][PolygonType][PointLightNum];

	//------------------------------------------------------------------------
	// シェーダー生成
	//------------------------------------------------------------------------
	Shader.pShader = pRender->CreateShaderFromMemory( pShader, ShaderSize );
	if ( Shader.pShader == NULL )
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRenderData::UpdateShaderHandle( SRenderShaderData &Shader )
{
	if ( Shader.pShader == NULL ) return;

	const wchar_t *pTechniqueTbl[TECHNIQUE_TYPE_MAX][TECHNIQUE_BUMPMAP_MAX][TECHNIQUE_REFLEX_MAX][TECHNIQUE_FOG_MAX] = {
		// TECHNIQUE_TYPE_NORMAL
		{
			{
				{ L"Technique_Base",						L"Technique_Fog" },								// 
				{ L"Technique_Specular",					L"Technique_Fog_Specular" },					// Specular
			},
			{
				{ L"Technique_Bumpmap",						L"Technique_Fog_Bumpmap" },						// Bump
				{ L"Technique_Bumpmap_Specular",			L"Technique_Fog_Bumpmap_Specular" },			// Bump & Specular
			},
			{
				{ L"Technique_Parallax",					L"Technique_Fog_Parallax" },					// Parallax
				{ L"Technique_Parallax_Specular",			L"Technique_Fog_Parallax_Specular" },			// Parallax & Specular
			},
		},
		// TECHNIQUE_TYPE_DEPTH_OF_FIELD
		{
			{
				{ L"Technique_1PassDoF",					L"Technique_Fog_1PassDoF" },					// DoF
				{ L"Technique_1PassDoF_Specular",			L"Technique_Fog_1PassDoF_Specular" },			// DoF
			},
			{
				{ L"Technique_1PassDoF_Bumpmap",			L"Technique_Fog_1PassDoF_Bumpmap" },			// DoF & Bump
				{ L"Technique_1PassDoF_Bumpmap_Specular",	L"Technique_Fog_1PassDoF_Bumpmap_Specular" },	// DoF & Bump
			},
			{
				{ L"Technique_1PassDoF_Parallax",			L"Technique_Fog_1PassDoF_Parallax" },			// DoF & Parallax
				{ L"Technique_1PassDoF_Parallax_Specular",	L"Technique_Fog_1PassDoF_Parallax_Specular" },	// DoF & Parallax
			},
		},
		// TECHNIQUE_TYPE_NORMAL_AND_DEPTH
		{
			{
				{ L"TechniqueNormalDepth",					L"TechniqueNormalDepth" },				// Normal + Depth
				{ L"TechniqueNormalDepth",					L"TechniqueNormalDepth" },				// Normal + Depth
			},
			{
				{ L"TechniqueNormalDepth",					L"TechniqueNormalDepth" },				// Normal + Depth
				{ L"TechniqueNormalDepth",					L"TechniqueNormalDepth" },				// Normal + Depth
			},
			{
				{ L"TechniqueNormalDepth",					L"TechniqueNormalDepth" },				// Normal + Depth
				{ L"TechniqueNormalDepth",					L"TechniqueNormalDepth" },				// Normal + Depth
			},
		},
		// TECHNIQUE_TYPE_SHADOWMAP
		{
			{
				{ L"Technique_ShadowMap",					L"Technique_ShadowMap" },				// Depth
				{ L"Technique_ShadowMap",					L"Technique_ShadowMap" },				// Depth
			},
			{
				{ L"Technique_ShadowMap",					L"Technique_ShadowMap" },				// Depth
				{ L"Technique_ShadowMap",					L"Technique_ShadowMap" },				// Depth
			},
			{
				{ L"Technique_ShadowMap",					L"Technique_ShadowMap" },				// Depth
				{ L"Technique_ShadowMap",					L"Technique_ShadowMap" },				// Depth
			},
		},
	};

	for ( Uint32 i = 0; i < TECHNIQUE_TYPE_MAX; i++ )
	{
		for ( Uint32 j = 0; j < TECHNIQUE_BUMPMAP_MAX; j++ )
		{
			for ( Uint32 k = 0; k < TECHNIQUE_REFLEX_MAX; k++ )
			{
				for ( Uint32 l = 0; l < TECHNIQUE_FOG_MAX; l++ )
				{
					Shader.hTechnique[i][j][k][l] = Shader.pShader->GetTechnique( pTechniqueTbl[i][j][k][l] );
				}
			}
		}
	}

	Shader.hMaterialColor				= Shader.pShader->GetParameterBySemantic( L"MaterialColor" );
	Shader.hSpecularColor				= Shader.pShader->GetParameterBySemantic( L"SpecularColor" );

	Shader.hRefractive					= Shader.pShader->GetParameterBySemantic( L"Refractive" );
	Shader.hRoughly						= Shader.pShader->GetParameterBySemantic( L"Roughly" );

	Shader.hDirectionalLightDirection	= Shader.pShader->GetParameterBySemantic( L"DirectionalLightDirection" );
	Shader.hDirectionalLightColor		= Shader.pShader->GetParameterBySemantic( L"DirectionalLightColor" );
	Shader.hPointLightPosition			= Shader.pShader->GetParameterBySemantic( L"PointLightPosition" );
	Shader.hPointLightColor				= Shader.pShader->GetParameterBySemantic( L"PointLightColor" );
	Shader.hAmbientLightColorSky		= Shader.pShader->GetParameterBySemantic( L"AmbientLightColorSky" );
	Shader.hAmbientLightColorEarth		= Shader.pShader->GetParameterBySemantic( L"AmbientLightColorEarth" );
	Shader.hCameraPosition				= Shader.pShader->GetParameterBySemantic( L"CameraPosition" );

	Shader.hBoneMatrixArray				= Shader.pShader->GetParameterBySemantic( L"BoneMatrixArray" );

	Shader.hParallaxDepth				= Shader.pShader->GetParameterBySemantic( L"ParallaxDepth" );
	Shader.hFogColor					= Shader.pShader->GetParameterBySemantic( L"FogColor" );
	Shader.hFogParameter				= Shader.pShader->GetParameterBySemantic( L"FogParameter" );

	Shader.hShadowMapParameter			= Shader.pShader->GetParameterBySemantic( L"ShadowMapParameter" );
	Shader.hShadowMapTransform			= Shader.pShader->GetParameterBySemantic( L"ShadowMapTransform" );

	Shader.hDofParameter				= Shader.pShader->GetParameterBySemantic( L"DofParameter" );
	Shader.hDepthTransform				= Shader.pShader->GetParameterBySemantic( L"DepthTransform" );

	Shader.hShadowWorldViewProjection	= Shader.pShader->GetParameterBySemantic( L"ShadowWorldViewProjection" );

	Shader.hProjection					= Shader.pShader->GetParameterBySemantic( L"Projection" );
	Shader.hProjectionInverse			= Shader.pShader->GetParameterBySemantic( L"ProjectionInverse" );

	Shader.hView						= Shader.pShader->GetParameterBySemantic( L"View" );
	Shader.hViewInverse					= Shader.pShader->GetParameterBySemantic( L"ViewInverse" );
	Shader.hViewProjection				= Shader.pShader->GetParameterBySemantic( L"ViewProjection" );
	Shader.hViewProjectionInverse		= Shader.pShader->GetParameterBySemantic( L"ViewProjectionInverse" );

	Shader.hWorld						= Shader.pShader->GetParameterBySemantic( L"World" );
	Shader.hWorldInverse				= Shader.pShader->GetParameterBySemantic( L"WorldInverse" );
	Shader.hWorldView					= Shader.pShader->GetParameterBySemantic( L"WorldView" );
	Shader.hWorldViewInverse			= Shader.pShader->GetParameterBySemantic( L"WorldViewInverse" );
	Shader.hWorldViewProjection			= Shader.pShader->GetParameterBySemantic( L"WorldViewProjection" );
	Shader.hWorldViewProjectionInverse	= Shader.pShader->GetParameterBySemantic( L"WorldViewProjectionInverse" );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderData::CRenderData()
{
	MemoryClear( Material, sizeof(Material) );

	MaterialCount	= 0;
	BoneCount		= 0;

	mWorld.Identity();
	mWorldInverse.Identity();

	for ( Uint32 i = 0; i < SHADER_BONE_MAX; i++ )
	{
		CMatrix mTemp;
		mTemp.Identity();
		mBone[i] = mTemp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderData::~CRenderData()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderData& CRenderData::operator = ( CRenderData &Src )
{
	// ポリゴンタイプ
	Type = Src.Type;

	// カリング
	IsCullTest = Src.IsCullTest;
	CullBox = Src.CullBox;

	// トランスフォーム
	mWorld = Src.mWorld;
	mWorldInverse = Src.mWorldInverse;

	// モード
	BumpMode = Src.BumpMode;
	ReflexMode = Src.ReflexMode;

	// ボーン関連
	BoneCount = Src.BoneCount;
	if ( BoneCount > 0 )
	{
		MemoryCopy(
			mBone,
			Src.mBone,
			sizeof(SMatrix4x4) * BoneCount );
	}

	// マテリアル関連
	MaterialCount = Src.MaterialCount;
	if ( MaterialCount > 0 )
	{
		MemoryCopy(
			Material,
			Src.Material,
			sizeof(SRenderMaterialData) * MaterialCount );
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRenderData::SetPolygonType( Uint32 VertexFlag )
{
	// 不要フラグカット
	VertexFlag &= ~VERTEX_ELEMENT_PRIMITIVE;
	VertexFlag &= ~VERTEX_ELEMENT_SPRITE;
	VertexFlag &= ~VERTEX_ELEMENT_3DBUMP;

	// 該当フラグ検索
	for ( Uint32 i = 0; i < POLYGON_TYPE_MAX; i++ )
	{
		if ( g_VertexFlagTbl[i] == VertexFlag )
		{
			Type = (ePolygonType)i;
		}
	}
}

#endif // ENABLE_3D
