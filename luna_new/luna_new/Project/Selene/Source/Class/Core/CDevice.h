

#ifndef ___SELENE__CDEVICE___
#define ___SELENE__CDEVICE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Object/CBaseObject.h"
#include "Core/CGraphicCard.h"
#include "Math/Vector4D.h"
#include "Math/Vector2D.h"
#include "Interface/Core/IDevice.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CCore;
	class CGraphicCard;
	class CRender;
	class CSurface;
	class CTexture;
	class CDeviceObjectMgr;
	class CShader;
	class CVertexStream;
	class CVertexBuffer;
	class CIndexBuffer;
	class CSurface;
	class CTexture;
	class COcclusion;

	enum eDeviceCreateType
	{
		DEVICE_CREATE_PUREDEVICE,
		DEVICE_CREATE_HARDWARE_TNL,
		DEVICE_CREATE_MIXED_TNL,
		DEVICE_CREATE_SOFTWARE_TNL,
		DEVICE_CREATE_REF,
	};

	class CDevice : public CBaseObject, public IDevice
	{
		friend CCore;
		friend CGraphicCard;
		friend CShader;
		friend CRender;
		friend CVertexStream;
		friend CVertexBuffer;
		friend CIndexBuffer;
		friend CSurface;
		friend CTexture;

	protected:
		IDirect3DDevice9 *m_pDevice;							///< �f�o�C�X�I�u�W�F�N�g
		IDirect3DSurface9 *m_pRenderTarget;						///< �����_�����O�^�[�Q�b�g
		IDirect3DQuery9 *m_pQuery;								///< �B���₢���킹�p

		D3DCAPS9 m_Caps;										///< �f�o�C�X���\
		D3DVIEWPORT9 m_Viewport;								///< �r���[�|�[�g
		Uint32 m_MaxUseVertexShaderVersion;						///< �g�p����ő�V�F�[�_�[�o�[�W����

		D3DDISPLAYMODE m_WindowType;							///< �E�B���h�E���[�h�̃f�B�X�v���C���[�h
		D3DDISPLAYMODE m_FullScreenType[2];						///< �t���N���[�����[�h�̃f�B�X�v���C���[�h
		D3DPRESENT_PARAMETERS m_PresentParams[2];				///< �v���[���e�[�V�����p�����[�^�[

		HFONT m_hFont;											///< �t�H���g�n���h��
		HFONT m_hOldFont;										///< �O�̃t�H���g�n���h��
		HDC m_hDC;												///< �f�o�C�X�R���e�L�X�g�n���h��

		CRender *m_pRender;

		void (*m_pCallbackReset)( void );						///< ���Z�b�g���R�[���o�b�N�֐�
		void (*m_pCallbackRestore)( void );						///< ���X�g�A���R�[���o�b�N�֐�

		wchar_t m_PrintfBuffer[4096];							///< ��ʊȈՕ`��p�����o�b�t�@
		Uint32 m_PrintfBufferPos;								///< ��ʊȈՕ`��p�����o�b�t�@�ǋL�ʒu

	protected:
		virtual Bool CreateDeviceByNVPerfHUD( D3DPRESENT_PARAMETERS &PresentParam );
		virtual Bool FontBegin( const wchar_t *pFontFace, Uint32 FontSize );
		virtual void FontDraw( Sint32 Px, Sint32 Py, const wchar_t *pStr, Uint32 Len );
		virtual void FontEnd( void );
		virtual void Refresh( HWND hWnd = NULL );
		virtual void ResetDevice( Bool IsChange );
		virtual void SetVertexProccessingType( void );
		virtual void SetDialogBoxType( Bool IsType );

	protected:
		CDevice();
		virtual ~CDevice();

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:

		virtual HWND GetCreationWindow( void );

		virtual Bool Initialize( Bool IsWindow );

		virtual CGraphicCard *GetGraphicCardPointer( void );

		virtual Uint32 GetRestVRAM( void );

		virtual CRect2D<Sint32> GetViewport( void );

		virtual Bool IsSupportedPS( Uint32 Major, Uint32 Minor );

		virtual Bool Clear( CColor Color = 0x00000000 );
		virtual Bool ClearDepth( void );
		virtual Bool ClearStencil( void );
		virtual Bool ClearDepthStencil( void );

		virtual Bool Clip( RECT *pDst, RECT *pSrc );

		virtual void Printf( const wchar_t *pStr, ... );
		virtual void Cls( void );

		virtual void SetCallbackDeviceReset( void (*pCallback)( void ) );
		virtual void SetCallbackDeviceRestore( void (*pCallback)( void ) );

		virtual void ResetRenderState( void );
		virtual void ResetSamplerState( void );
		virtual void ResetTextureStageState( void );

		virtual void SetScissor( Bool IsEnable, CRect2D<Sint32> Rect );
		virtual IRender *CreateRender( void );

		virtual COcclusion *CeateOcclusion( void );

		//--------------------------------------------------------------------------------------------------------------------
		// D3D�f�o�C�X�A�N�Z�X�n
		virtual void BeginScene( void );
		virtual void EndScene( void );
		virtual HRESULT SetRenderState( D3DRENDERSTATETYPE State, Uint32 Value );
		virtual HRESULT SetSamplerState( Uint32 Sampler, D3DSAMPLERSTATETYPE Type, Uint32 Value );
		virtual HRESULT SetTextureStageState( Uint32 Stage, D3DTEXTURESTAGESTATETYPE Type, Uint32 Value );
		virtual HRESULT CreateDepthStencilSurface( Uint32 Width, Uint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface );
		virtual HRESULT CreateOffscreenPlainSurface( Uint32 Width, Uint32 Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface );
		virtual HRESULT CreateTexture( Uint32 Width, Uint32 Height, Uint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture );
		virtual HRESULT CreateRenderTarget( Uint32 Width, Uint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface );
		virtual HRESULT GetRenderTargetData( IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface );
 		virtual HRESULT StretchRect( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter );
		virtual HRESULT UpdateTexture( IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture );
		virtual HRESULT SetDepthStencilSurface( IDirect3DSurface9 *pZStencil );
		virtual HRESULT SetRenderTarget( IDirect3DSurface9 *pRenderTarget );
		virtual HRESULT CopyToBackBuffer( IDirect3DSurface9 *pRenderTarget );
		virtual HRESULT SetSoftwareVertexProcessing( BOOL bSoftware );
		virtual HRESULT SetTexture( Uint32 Stage, IDirect3DTexture9 *pTex );
		virtual HRESULT CreateVertexBuffer( Uint32 Length, IDirect3DVertexBuffer9** ppVertexBuffer, Bool IsDynamic );
		virtual HRESULT CreateIndexBuffer( Uint32 Length, IDirect3DIndexBuffer9** ppIndexBuffer, Bool IsDynamic );
		virtual HRESULT CreateVertexDeclaration( const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl );
		virtual HRESULT SetStreamSource( Uint32 StreamNumber, IDirect3DVertexBuffer9 *pStreamData, Uint32 Stride );
		virtual HRESULT SetIndices( IDirect3DIndexBuffer9 *pIndexData );
		virtual HRESULT SetVertexDeclaration( IDirect3DVertexDeclaration9 *pDecl );
		virtual HRESULT CreateEffect( LPCVOID pSrcData, UINT SrcDataLen, LPD3DXEFFECT *ppEffect, LPD3DXBUFFER *ppCompilationErrors );
		virtual HRESULT DrawPrimitive( D3DPRIMITIVETYPE PrimitiveType, Uint32 PrimitiveCount );
		virtual HRESULT DrawIndexedPrimitive( D3DPRIMITIVETYPE PrimitiveType, Uint32 VertexCount, Uint32 PrimitiveCount );
		virtual HRESULT DrawMesh( Uint32 VertexStart, Uint32 VertexCount, Uint32 IndexStart, Uint32 PrimitiveCount );
		virtual HRESULT CreateOcclusionQuery( IDirect3DQuery9 **ppQuery );
	};
}


#endif // ___SELENE__CDEVICE___

