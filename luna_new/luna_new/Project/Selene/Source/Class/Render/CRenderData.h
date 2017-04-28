

#ifndef ___SELENE__RENDERDATA___
#define ___SELENE__RENDERDATA___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Render/CRender.h"
#include "Math/Vector4D.h"
#include "Math/Matrix.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CShader;
	class CTexture;

	enum ePolygonType
	{
		POLYGON_TYPE_TRANSFORM,
		POLYGON_TYPE_TRANSFORM_TEXTURE,
		POLYGON_TYPE_TRANSFORM_LIGHTING,
		POLYGON_TYPE_TRANSFORM_LIGHTING_TEXTURE,
		POLYGON_TYPE_TRANSFORM_ANIMATION,
		POLYGON_TYPE_TRANSFORM_ANIMATION_TEXTURE,
		POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING,
		POLYGON_TYPE_TRANSFORM_ANIMATION_LIGHTING_TEXTURE,
		POLYGON_TYPE_MAX,
	};

	enum eShadowType
	{
		SHADOW_TYPE_DISABLE,
		SHADOW_TYPE_ENABLE,
		SHADOW_TYPE_MAX,
	};

	enum ePointLigjhtCountType
	{
		POINT_LIGHT_COUNT_TYPE_0,
		POINT_LIGHT_COUNT_TYPE_1,
		POINT_LIGHT_COUNT_TYPE_2,
		POINT_LIGHT_COUNT_TYPE_3,
		POINT_LIGHT_COUNT_TYPE_4,
		POINT_LIGHT_COUNT_TYPE_MAX,
	};

	enum eTechniqueFog
	{
		TECHNIQUE_FOG_DISABLE,
		TECHNIQUE_FOG_ENABLE,
		TECHNIQUE_FOG_MAX,
	};

	enum eTechniqueReflex
	{
		TECHNIQUE_REFLEX_DISABLE,
		TECHNIQUE_REFLEX_ENABLE,
		TECHNIQUE_REFLEX_MAX,
	};

	enum eTechniqueBumpmap
	{
		TECHNIQUE_BUMPMAP_DISABLE,
		TECHNIQUE_BUMPMAP_ENABLE,
		TECHNIQUE_BUMPMAP_PARALLAX,
		TECHNIQUE_BUMPMAP_MAX,
	};

	enum eTechniqueType
	{
		TECHNIQUE_TYPE_NORMAL,
		TECHNIQUE_TYPE_DEPTH_OF_FIELD,
		TECHNIQUE_TYPE_NORMAL_AND_DEPTH,
		TECHNIQUE_TYPE_SHADOWMAP,
		TECHNIQUE_TYPE_MAX,
	};

	/**
		@brief レンダリング用シェーダーデータ
		@author 葉迩倭

		レンダリングを行う際のシェーダーデータを格納し、<BR>
		このデータを元にしてレンダリング処理が行われます。
	*/
	struct SRenderShaderData
	{
		CShader *pShader;								///< シェーダー

		FX_HANDLE hTechnique[TECHNIQUE_TYPE_MAX][TECHNIQUE_BUMPMAP_MAX][TECHNIQUE_REFLEX_MAX][TECHNIQUE_FOG_MAX];	///< テクニック

		FX_HANDLE hMaterialColor;						///< float4 マテリアル色
		FX_HANDLE hSpecularColor;						///< float4 スペキュラ色

		FX_HANDLE hRefractive;							///< スペキュラ屈折率
		FX_HANDLE hRoughly;							///< スペキュラ粗さ

		FX_HANDLE hDirectionalLightDirection;			///< float4 平行光源：方向
		FX_HANDLE hDirectionalLightColor;				///< float4 平行光源：色
		FX_HANDLE hPointLightPosition;					///< float4[] 点光源：位置
		FX_HANDLE hPointLightColor;					///< float4[] 点光源：色
		FX_HANDLE hAmbientLightColorSky;				///< float4 環境光：色
		FX_HANDLE hAmbientLightColorEarth;				///< float4 環境光：色
		FX_HANDLE hCameraPosition;						///< float3 カメラ位置
		FX_HANDLE hParallaxDepth;						///< float 視差深度

		FX_HANDLE hBoneMatrixArray;					///< float4x4 ボーン行列

		FX_HANDLE hFogColor;							///< float4 フォグの色
		FX_HANDLE hFogParameter;						///< float[] フォグのパラメーター

		FX_HANDLE hDofParameter;						///< float[] 被写界深度用のパラメーター
		FX_HANDLE hDepthTransform;						///< float4 Ｚ変換ベクトル

		FX_HANDLE hShadowMapParameter;					///< シャドウマップ用バイアス
		FX_HANDLE hShadowMapTransform;					///< float4 Ｚ変換ベクトル

		FX_HANDLE hProjection;							///< float4x4 射影行列
		FX_HANDLE hProjectionInverse;					///< float4x4 射影行列の逆行列

		FX_HANDLE hView;								///< float4x4 ビュー行列
		FX_HANDLE hViewInverse;						///< float4x4 ビュー行列の逆行列
		FX_HANDLE hViewProjection;						///< float4x4 ビュー射影行列
		FX_HANDLE hViewProjectionInverse;				///< float4x4 ビュー射影行列の逆行列

		FX_HANDLE hWorld;								///< float4x4 ワールド行列
		FX_HANDLE hWorldInverse;						///< float4x4 ワールド行列の逆行列
		FX_HANDLE hWorldView;							///< float4x4 ワールド ビュー行列
		FX_HANDLE hWorldViewInverse;					///< float4x4 ワールド ビュー行列の逆行列
		FX_HANDLE hWorldViewProjection;				///< float4x4 ワールド ビュー射影行列
		FX_HANDLE hWorldViewProjectionInverse;			///< float4x4 ワールド ビュー射影行列の逆行列

		FX_HANDLE hShadowWorldViewProjection;			///< float4x4 シャドウマップ用 ワールド ビュー射影行列の逆行列
	};

	/**
		@brief レンダリング用マテリアルデータ
		@author 葉迩倭

		レンダリングを行う際のマテリアルデータを格納し、<BR>
		このデータを元にしてレンダリング処理が行われます。
	*/
	struct SRenderMaterialData
	{
		Float fRefractive;
		Float fRoughly;
		CVector4D vMaterialColor;							///< マテリアル色
		CVector4D vSpecularColor;							///< スペキュラ色
		CTexture *pTexture[MESH_TEXTURE_MAX];				///< テクスチャ
	};

	/**
		@brief レンダリング用データ
		@author 葉迩倭

		レンダリングを行う際のデータを全て格納し、<BR>
		このデータを元にしてレンダリング処理が行われます。<BR>
		この構造体を使って描画されるのは3Dオブジェクトのみで、<BR>
		3Dオブジェクトは全てISceneManagerを経由してレンダリングされます。<BR>
		また2D描画には関係ありません。
	*/
	class CRenderData
	{
	public:
		static SRenderShaderData m_Shader[POLYGON_TYPE_MAX][POINT_LIGHT_COUNT_TYPE_MAX][SHADOW_TYPE_MAX];

	private:
		static Bool CreateShader( SRenderShaderData &Shader, Uint32 PolygonType, Uint32 PointLightNum, Bool IsShadowEnable, CRender *pRender );
		static void UpdateShaderHandle( SRenderShaderData &Shader );

	public:
		static Bool Initialize( CRender *pRender );
		static void Finalize( void );

		static SRenderShaderData &GetShader( ePolygonType PolyType, Uint32 PointLightCount, Bool IsShadow );

	public:
		ePolygonType Type;										///< ポリゴンタイプ

		Bool IsCullTest;										///< カリングテスト有無
		CBox CullBox;											///< カリング用データ

		CMatrix mWorld;											///< ワールド行列
		CMatrix mWorldInverse;									///< 逆ワールド行列

		eTechniqueReflex ReflexMode;
		eTechniqueBumpmap BumpMode;

		Uint32 BoneCount;										///< ボーン行列数
		SMatrix4x4 mBone[SHADER_BONE_MAX];						///< ボーン行列

		Uint32 MaterialCount;									///< マテリアル数
		SRenderMaterialData Material[MATERIAL_MAX];				///< マテリアル

	public:
		CRenderData();
		~CRenderData();

		CRenderData& operator = ( CRenderData &Src );

		void SetPolygonType( Uint32 VertexFlag );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__RENDERDATA___


