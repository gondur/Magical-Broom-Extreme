

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
		@brief �`��v���~�e�B�u�t�H�[�}�b�g
		@author �t���`

		�|���S���̃����_�����O���Ɏw�肷��t���O�ł��B<BR>
		�����Ŏg�p������̂ł��B
	*/
	enum ePrimitiveType
	{
		PRIMITIVE_POINT,				///< �_�`��
		PRIMITIVE_LINE,					///< ���`��
		PRIMITIVE_LINE_STRIP,			///< �X�g���b�v���`��
		PRIMITIVE_TRIANGLE,				///< �Ɨ��O�p�`�`��
		PRIMITIVE_TRIANGLE_STRIP,		///< �X�g���b�v�O�p�`�`��
		PRIMITIVE_TRIANGLE_FAN,			///< �t�@���O�p�`�`��
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
		@brief �����_���[�N���X
		@author �t���`

		��ʂɑ΂���S�Ă̕`�揈�����Ǘ����܂��B<BR>
		�`��p�̊e��N���X���S�Ă��̃N���X����擾���܂�<BR>
		�܂����̃N���X��1��CDevice�ɑ΂���1�����쐬����܂���B
	*/
	class CRender : public CBaseObject, public IRender
	{
		enum { STATE_STACK_MAX = 16 };

	public:
		CDeviceObjectMgr	*m_pVertexStreamMgr;					///< ���_��`�Ǘ����X�g
		CDeviceObjectMgr	*m_pVertexBufferMgr;					///< ���_�o�b�t�@�Ǘ����X�g
		CDeviceObjectMgr	*m_pIndexBufferMgr;						///< �C���f�b�N�X�o�b�t�@�Ǘ����X�g
		CDeviceObjectMgr	*m_pShaderMgr;							///< �V�F�[�_�[�Ǘ����X�g
		CPrimitive2DBaseMgr	*m_pListPrimitive2DMgr;					///< 2D�n�`��I�u�W�F�N�g�Ǘ��N���X
		CPrimitive3DBaseMgr	*m_pListPrimitive3DMgr;					///< 3D�n�`��I�u�W�F�N�g�Ǘ��N���X
		CModelMgr			*m_pListModelMgr;						///< ���f���I�u�W�F�N�g�Ǘ��N���X
		CSurfaceMgr			*m_pSurfaceMgr;							///< �T�[�t�F�C�X�Ǘ����X�g
		CTextureMgr			*m_pTextureMgr;							///< �e�N�X�`���Ǘ����X�g
		CPostEffect			*m_pPostEffect;							///< �|�X�g�G�t�F�N�g
		CSceneManager		*m_pActiveScene;						///< ���݃A�N�e�B�u�ȃV�[��
		CBaseSurface		*m_pDepthStencil;						///< �[�x�X�e���V���o�b�t�@
		CBaseSurface		*m_pRenderTarget;						///< �����_�����O�^�[�Q�b�g
		CTextureConfig		m_TextureConfig;						///< �e�N�X�`���쐬�p�ݒ�f�[�^
		Float				m_fOffset[TEXTURE_STAGE_MAX];			///< �t�B���^�����O�pUV�I�t�Z�b�g
		SRenderState		m_RenderState[STATE_STACK_MAX];			///< �`��X�e�[�g
		Sint32				m_RenderStatePos;						///< �`��X�e�[�g�ʒu

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


