

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
		@brief �����_�����O�p�V�F�[�_�[�f�[�^
		@author �t���`

		�����_�����O���s���ۂ̃V�F�[�_�[�f�[�^���i�[���A<BR>
		���̃f�[�^�����ɂ��ă����_�����O�������s���܂��B
	*/
	struct SRenderShaderData
	{
		CShader *pShader;								///< �V�F�[�_�[

		FX_HANDLE hTechnique[TECHNIQUE_TYPE_MAX][TECHNIQUE_BUMPMAP_MAX][TECHNIQUE_REFLEX_MAX][TECHNIQUE_FOG_MAX];	///< �e�N�j�b�N

		FX_HANDLE hMaterialColor;						///< float4 �}�e���A���F
		FX_HANDLE hSpecularColor;						///< float4 �X�y�L�����F

		FX_HANDLE hRefractive;							///< �X�y�L�������ܗ�
		FX_HANDLE hRoughly;							///< �X�y�L�����e��

		FX_HANDLE hDirectionalLightDirection;			///< float4 ���s�����F����
		FX_HANDLE hDirectionalLightColor;				///< float4 ���s�����F�F
		FX_HANDLE hPointLightPosition;					///< float4[] �_�����F�ʒu
		FX_HANDLE hPointLightColor;					///< float4[] �_�����F�F
		FX_HANDLE hAmbientLightColorSky;				///< float4 �����F�F
		FX_HANDLE hAmbientLightColorEarth;				///< float4 �����F�F
		FX_HANDLE hCameraPosition;						///< float3 �J�����ʒu
		FX_HANDLE hParallaxDepth;						///< float �����[�x

		FX_HANDLE hBoneMatrixArray;					///< float4x4 �{�[���s��

		FX_HANDLE hFogColor;							///< float4 �t�H�O�̐F
		FX_HANDLE hFogParameter;						///< float[] �t�H�O�̃p�����[�^�[

		FX_HANDLE hDofParameter;						///< float[] ��ʊE�[�x�p�̃p�����[�^�[
		FX_HANDLE hDepthTransform;						///< float4 �y�ϊ��x�N�g��

		FX_HANDLE hShadowMapParameter;					///< �V���h�E�}�b�v�p�o�C�A�X
		FX_HANDLE hShadowMapTransform;					///< float4 �y�ϊ��x�N�g��

		FX_HANDLE hProjection;							///< float4x4 �ˉe�s��
		FX_HANDLE hProjectionInverse;					///< float4x4 �ˉe�s��̋t�s��

		FX_HANDLE hView;								///< float4x4 �r���[�s��
		FX_HANDLE hViewInverse;						///< float4x4 �r���[�s��̋t�s��
		FX_HANDLE hViewProjection;						///< float4x4 �r���[�ˉe�s��
		FX_HANDLE hViewProjectionInverse;				///< float4x4 �r���[�ˉe�s��̋t�s��

		FX_HANDLE hWorld;								///< float4x4 ���[���h�s��
		FX_HANDLE hWorldInverse;						///< float4x4 ���[���h�s��̋t�s��
		FX_HANDLE hWorldView;							///< float4x4 ���[���h �r���[�s��
		FX_HANDLE hWorldViewInverse;					///< float4x4 ���[���h �r���[�s��̋t�s��
		FX_HANDLE hWorldViewProjection;				///< float4x4 ���[���h �r���[�ˉe�s��
		FX_HANDLE hWorldViewProjectionInverse;			///< float4x4 ���[���h �r���[�ˉe�s��̋t�s��

		FX_HANDLE hShadowWorldViewProjection;			///< float4x4 �V���h�E�}�b�v�p ���[���h �r���[�ˉe�s��̋t�s��
	};

	/**
		@brief �����_�����O�p�}�e���A���f�[�^
		@author �t���`

		�����_�����O���s���ۂ̃}�e���A���f�[�^���i�[���A<BR>
		���̃f�[�^�����ɂ��ă����_�����O�������s���܂��B
	*/
	struct SRenderMaterialData
	{
		Float fRefractive;
		Float fRoughly;
		CVector4D vMaterialColor;							///< �}�e���A���F
		CVector4D vSpecularColor;							///< �X�y�L�����F
		CTexture *pTexture[MESH_TEXTURE_MAX];				///< �e�N�X�`��
	};

	/**
		@brief �����_�����O�p�f�[�^
		@author �t���`

		�����_�����O���s���ۂ̃f�[�^��S�Ċi�[���A<BR>
		���̃f�[�^�����ɂ��ă����_�����O�������s���܂��B<BR>
		���̍\���̂��g���ĕ`�悳���̂�3D�I�u�W�F�N�g�݂̂ŁA<BR>
		3D�I�u�W�F�N�g�͑S��ISceneManager���o�R���ă����_�����O����܂��B<BR>
		�܂�2D�`��ɂ͊֌W����܂���B
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
		ePolygonType Type;										///< �|���S���^�C�v

		Bool IsCullTest;										///< �J�����O�e�X�g�L��
		CBox CullBox;											///< �J�����O�p�f�[�^

		CMatrix mWorld;											///< ���[���h�s��
		CMatrix mWorldInverse;									///< �t���[���h�s��

		eTechniqueReflex ReflexMode;
		eTechniqueBumpmap BumpMode;

		Uint32 BoneCount;										///< �{�[���s��
		SMatrix4x4 mBone[SHADER_BONE_MAX];						///< �{�[���s��

		Uint32 MaterialCount;									///< �}�e���A����
		SRenderMaterialData Material[MATERIAL_MAX];				///< �}�e���A��

	public:
		CRenderData();
		~CRenderData();

		CRenderData& operator = ( CRenderData &Src );

		void SetPolygonType( Uint32 VertexFlag );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__RENDERDATA___


