

#ifndef ___SELENE__CRENDER___
#define ___SELENE__CRENDER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Scene/CSceneCamera.h"
#include "Core/CDevice.h"
#include "Object/CDeviceObject.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CPostEffect;
	class CDevice;
	class CDeviceObjectMgr;
	class CTextureMgr;
	class CSurfaceMgr;
	class CPrimitive2DBaseMgr;
	class CPrimitive3DBaseMgr;
	class CModelMgr;
	class CVertexStream;
	class CVertexBuffer;
	class CIndexBuffer;
	class CShader;
	class CSceneManager;
	class CFont;
	class CBaseSurface;

	static const Uint32 MATERIAL_MAX = 32;

	/**
		@brief 描画プリミティブフォーマット
		@author 葉迩倭

		ポリゴンのレンダリング時に指定するフラグです。<BR>
		内部で使用するものです。
	*/
	enum ePrimitiveType
	{
		PRIMITIVE_POINT,				///< 点描画
		PRIMITIVE_LINE,					///< 線描画
		PRIMITIVE_LINE_STRIP,			///< ストリップ線描画
		PRIMITIVE_TRIANGLE,				///< 独立三角形描画
		PRIMITIVE_TRIANGLE_STRIP,		///< ストリップ三角形描画
		PRIMITIVE_TRIANGLE_FAN,			///< ファン三角形描画
	};

	struct SRenderState
	{
		ITexture *pTextureTbl[TEXTURE_STAGE_MAX];
		eTextureFilterType FilterType[TEXTURE_STAGE_MAX];
		eTextureAddressType AddressType[TEXTURE_STAGE_MAX];
		eTextureOperationType OperationType[TEXTURE_STAGE_MAX];
		eDrawType DrawType;
		eCullType CullType;
		CColor FogColor;
		Bool IsDepthTestEnable;
		Bool IsDepthWriteEnable;
		Bool IsAlphaTestEnable;
	};

	/**
		@brief レンダラークラス
		@author 葉迩倭

		画面に対する全ての描画処理を管理します。<BR>
		描画用の各種クラスも全てこのクラスから取得します<BR>
		またこのクラスは1つのCDeviceに対して1つしか作成されません。
	*/
	class CRender : public CBaseObject, public IRender
	{
		enum { STATE_STACK_MAX = 16 };

	public:
		CDeviceObjectMgr	*m_pVertexStreamMgr;					///< 頂点定義管理リスト
		CDeviceObjectMgr	*m_pVertexBufferMgr;					///< 頂点バッファ管理リスト
		CDeviceObjectMgr	*m_pIndexBufferMgr;						///< インデックスバッファ管理リスト
		CDeviceObjectMgr	*m_pShaderMgr;							///< シェーダー管理リスト
		CPrimitive2DBaseMgr	*m_pListPrimitive2DMgr;					///< 2D系描画オブジェクト管理クラス
		CPrimitive3DBaseMgr	*m_pListPrimitive3DMgr;					///< 3D系描画オブジェクト管理クラス
		CModelMgr			*m_pListModelMgr;						///< モデルオブジェクト管理クラス
		CSurfaceMgr			*m_pSurfaceMgr;							///< サーフェイス管理リスト
		CTextureMgr			*m_pTextureMgr;							///< テクスチャ管理リスト
		CPostEffect			*m_pPostEffect;							///< ポストエフェクト
		CSceneManager		*m_pActiveScene;						///< 現在アクティブなシーン
		CBaseSurface		*m_pDepthStencil;						///< 深度ステンシルバッファ
		CBaseSurface		*m_pRenderTarget;						///< レンダリングターゲット
		CTextureConfig		m_TextureConfig;						///< テクスチャ作成用設定データ
		Float				m_fOffset[TEXTURE_STAGE_MAX];			///< フィルタリング用UVオフセット
		SRenderState		m_RenderState[STATE_STACK_MAX];			///< 描画ステート
		Sint32				m_RenderStatePos;						///< 描画ステート位置

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CRender( CDevice *pDevice );
		virtual ~CRender();

		virtual void Initialize( void );

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual CDevice *GetDevicePointer( void );

		virtual Float GetTextureOffset( Uint32 Stage );
		virtual Uint32 GetSize( Uint32 Flag );

		virtual IPostEffect *CreatePostEffect( void );

		virtual CTexture *GetTexture( Uint32 Stage );

		virtual Bool SetTexture( Uint32 Stage, ITexture *pTex );
		virtual Bool SetStream( CVertexStream *pStream );
		virtual Bool SetVertex( Uint32 StreamNo, CVertexBuffer *pVertex );
		virtual Bool SetIndex( CIndexBuffer *pIndex );
		virtual Bool DrawPrimitive( ePrimitiveType PrimitiveType, Uint32 PrimitiveCount );
		virtual Bool DrawIndexedPrimitive( ePrimitiveType PrimitiveType, Uint32 VertexCount, Uint32 PrimitiveCount );
		virtual Bool DrawMesh( Uint32 VertexStart, Uint32 VertexCount, Uint32 IndexStart, Uint32 IndexCount );

		virtual Bool ResetRenderTarget( void );

		virtual Bool SetDepthStencil( ISurface *pSurface );

		virtual Bool SetRenderTarget( ITexture *pTexture );
		virtual Bool SetRenderTarget( ISurface *pSurface );

		virtual Bool GetRenderTarget( ITexture **ppTexture );
		virtual Bool GetRenderTarget( ISurface **ppSurface );

		virtual ISceneManager *CreateSceneManager( eSceneMode Mode, eSceneModeOption Option );
#if ENABLE_3D
		virtual CSceneManager *GetSceneManagerPointer( void );
		virtual Bool ActivateScene( CSceneManager *pScene );
		virtual Bool DeActivateScene( CSceneManager *pScene );
#endif // ENABLE_3D

		virtual void Begin( void );
		virtual void End( void );

		virtual CVertexStream *CreateVertexStreamDirect( void );
		virtual CVertexStream *CreateVertexStream( Uint32 Flag );
		virtual CVertexBuffer *CreateVertexBuffer( Uint32 Count, Uint32 VertexSize, Bool IsDynamic );
		virtual CIndexBuffer *CreateIndexBuffer( Uint32 Count, Bool IsDynamic );
		virtual CShader *CreateShaderFromFile( const wchar_t *pFileName );
		virtual CShader *CreateShaderFromMemory( const Uint8 *pShader, Uint32 Size );

		virtual void SetScissoring( RECT *pRect );

		virtual IPointPrimitive2D *CreatePointPrimitive2D( Uint32 PointMax );
		virtual ILinePrimitive2D *CreateLinePrimitive2D( Uint32 LineMax );
		virtual IPrimitive2D *CreatePrimitive2D( Uint32 PrimitiveMax );
		virtual ISprite2D *CreateSprite2D( Uint32 PrimitiveMax, ITexture *pTexture );
		virtual IFontSprite2D *CreateFontSprite2D( const wchar_t *pBuffer, Uint32 FontMax, const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold, Bool IsAntialias );
		virtual IFontSprite2D *CreateFontSprite2DFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 FontMax );
		virtual CFont *CreateFont( const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold );

		virtual IPointPrimitive3D *CreatePointPrimitive3D( Uint32 VertexMax, Bool IsDynamic );
		virtual ILinePrimitive3D *CreateLinePrimitive3D( Uint32 VertexMax, Bool IsDynamic );
		virtual IPrimitive3D *CreatePrimitive3D( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic );

		virtual IModel *CreateModelFromFile( const wchar_t *pFileName );
		virtual IModel *CreateModelFromMemory( const Uint8 *pData, Uint32 Size );

		virtual ISurface *CreateDepthStencilSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual ISurface *CreateRenderTargetSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format, ISurface *pCopyTarget );

		virtual CTextureConfig &GetTextureConfig( void );
		virtual void SetTextureConfig( CTextureConfig &Conf );
		virtual ITexture *CreateTexture( Uint32 Width, Uint32 Height );
		virtual ITexture *CreateTextureFromFile( const wchar_t *pFileName );
		virtual ITexture *CreateTextureFromMemory( void *pData, Uint32 Size );
		virtual ITexture *CreateTextureRenderTarget( Uint32 Width, Uint32 Height );
		virtual ITexture *CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight );
		virtual ITexture *CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight );

		virtual void SetDrawType( eDrawType Type );
		virtual void SetCullType( eCullType Type );
		virtual void SetTextureFilterType( Uint32 Stage, eTextureFilterType Type );
		virtual void SetTextureAddressType( Uint32 Stage, eTextureAddressType Type );
		virtual void SetTextureOperationType( Uint32 Stage, eTextureOperationType Type );
		virtual void SetFogColor( CColor Color );
		virtual void SetDepthTestEnable( Bool Flag );
		virtual void SetDepthWriteEnable( Bool Flag );
		virtual void SetAlphaTestEnable( Bool Flag );
		virtual Bool StatePush( void );
		virtual Bool StatePop( void );
		virtual void StateInit( void );
	};
}

#endif // ___SELENE__CRENDER___


