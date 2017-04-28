

#ifndef ___SELENE__CGRAPHICCARD___
#define ___SELENE__CGRAPHICCARD___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"
#include "Math/Math.h"
#include "Interface/Core/IGraphicCard.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CCore;
	class CDevice;
	class CRender;
	class CTexture;
	class CSurface;

	typedef IDirect3D9 * (WINAPI *PDIRECT3DCREATE9)( unsigned int );	///< Direct3D�I�u�W�F�N�g�����֐�

	/**
		@brief 3D�f�o�C�X���
		@author �t���`
	*/
	struct DEVICEINFORMATION
	{
		Bool IsPureDevice;							///< �s���A�f�o�C�X���T�|�[�g���Ă邩�ǂ���
		Bool IsHardwareTnL;							///< �n�[�h�E�F�A�s���k���T�|�[�g���Ă邩�ǂ���
		Bool IsHardwareRasterize;					///< �n�[�h�E�F�A���X�^���C�Y���T�|�[�g���Ă邩�ǂ���

		D3DDEVTYPE DeviceType;						///< �f�o�C�X�^�C�v

		Bool IsAutoMipMap;							///< �~�b�v�}�b�v�����������T�|�[�g���Ă��邩�ۂ�
		Bool IsCubeTexture;							///< �L���[�u�e�[�N�X�`�����T�|�[�g���Ă��邩�ۂ�
		Bool IsStencilTwoSided;						///< ���ʃX�e���V���������\���ǂ���
		Bool IsMagAnisotropy;						///< ���ʃX�e���V���������\���ǂ���
		Bool IsMinAnisotropy;						///< ���ʃX�e���V���������\���ǂ���
		Bool IsSupportPow2Texture;					///< 2^n�ȊO�̃e�N�X�`���T�C�Y���g���邩�ǂ���

		Uint32 MaxAnisotropy;						///< �ٕ����t�B���^����
		Uint32 MaxTextureWidth;						///< �ő�e�N�X�`������
		Uint32 MaxTextureHeight;					///< �ő�e�N�X�`���c��

		Float GuardBandLeft;						///< �K�[�h�o���h�N���b�s���O���ʒu
		Float GuardBandTop;							///< �K�[�h�o���h�N���b�s���O��ʒu
		Float GuardBandRight;						///< �K�[�h�o���h�N���b�s���O�E�ʒu
		Float GuardBandBottom;						///< �K�[�h�o���h�N���b�s���O���ʒu

		Uint32 MaxPrimitiveCount;					///< �ő�`��\�|���S����
		Uint32 MaxVertexIndex;						///< �ő�`��\���_�C���f�b�N�X��

		Uint32 MaxTextureBlendStages;				///< �ő�e�N�X�`���u�����f�B���O�X�e�[�W��
		Uint32 MaxSimultaneousTextures;				///< �ő�e�N�X�`���X�e�[�W��

		Uint32 VertexShaderVersion;					///< ���_�V�F�[�_�[�o�[�W����
		Uint32 PixelShaderVersion;					///< �s�N�Z���V�F�[�_�[�o�[�W����
		Uint32 MaxVertexShaderConst;				///< �ő咸�_�V�F�[�_�[�萔���W�X�^��

		Uint32 DynamicFlowControlDepth;				///< ���_�V�F�[�_�[�ł̓��I�t���[����ő�l�X�g��
		Uint32 StaticFlowControlDepth;				///< ���_�V�F�[�_�[�ł̐ÓI�t���[����ő�l�X�g��

		Uint32 MultiRenderTargetCount;				///< �}���`�����_�����O�^�[�Q�b�g��
	};

	/**
		@brief �r�f�I�J�[�h���Ǘ��N���X
		@author �t���`
	*/
	class CGraphicCard : public CBaseObject, public IGraphicCard
	{
		friend CCore;
		friend CRender;
		friend CDevice;
		friend CTexture;
		friend CSurface;

	protected:
		eSurfaceFormat m_SurfaceFormatTbl[2][16];				///< �T�[�t�F�C�X�t�H�[�}�b�g�����e�[�u��
		Uint32 m_SurfaceFormatCount[2];							///< �T�[�t�F�C�X�t�H�[�}�b�g��

		HINSTANCE m_hDllD3D9;									///< DLL�n���h��
		IDirect3D9 *m_pDirect3D;								///< Direct3D�I�u�W�F�N�g

		Uint32 m_GraphicCardNo;									///< �r�f�I�J�[�h�ԍ�
		wchar_t m_GraphicCardName[128];							///< �r�f�I�J�[�h��
		wchar_t m_GraphicCardDriver[128];						///< �r�f�I�J�[�h�h���C�o�[��
		wchar_t m_GraphicCardVersion[128];						///< �r�f�I�J�[�h�o�[�W������

		Uint32 m_MaxUseVertexShaderVersion;						///< �g�p���钸�_�V�F�[�_�[�̍ő�o�[�W����
		DEVICEINFORMATION m_DeviceInfo;							///< �f�o�C�X���

		D3DDISPLAYMODE m_WindowType;							///< �E�B���h�E���[�h�̃f�B�X�v���C���[�h
		D3DDISPLAYMODE m_FullScreenType[2];						///< �t���N���[�����[�h�̃f�B�X�v���C���[�h
		D3DPRESENT_PARAMETERS m_PresentParams[2];				///< �v���[���e�[�V�����p�����[�^�[

		Bool m_IsHighColor;										///< 16Bit��ʃ��[�h���ǂ���
		Bool m_IsWaitBlank;										///< VSYNC�҂������邩�ǂ���
		Bool m_IsHVPerfHUD;										///< NVPerfHUD���g�����ǂ���

		Sint32 m_ScreenTypeCount;								///< ��ʃ��[�h��
		D3DDISPLAYMODE m_ScreenType[64];						///< ��ʃ��[�h

		Sint32 m_DepthCount;									///< �[�x�t�H�[�}�b�g��
		D3DFORMAT m_DepthFormats[16];							///< �[�x�t�H�[�}�b�g

		Sint32 m_TextureCount;									///< �e�N�X�`���t�H�[�}�b�g��
		D3DFORMAT m_TextureFormats[64];							///< �e�N�X�`���t�H�[�}�b�g

		Sint32 m_TargetCount;									///< �����_�����O�^�[�Q�b�g�t�H�[�}�b�g��
		D3DFORMAT m_TargetFormats[32];							///< �����_�����O�^�[�Q�b�g�t�H�[�}�b�g

		CDevice *m_pDevice;										///< �f�o�C�X

	protected:
		virtual Bool CreateDirect3DObject( void );
		virtual Bool CheckGraphicCardInfo( void );
		virtual Bool CheckGraphicCardCaps( void );
		virtual void GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo );
		virtual D3DPRESENT_PARAMETERS MakePresentParameters( Bool IsWindow, Bool IsHightColor );
		virtual Sint32 GetDeviceTypeNo( void );
		virtual Bool GetHightColorType( void );
		virtual Bool GetNVPerfHUD( void );
		virtual Bool CheckSupportVertexProccessing( void );
		virtual D3DFORMAT GetFormat( eSurfaceFormat Format, D3DFORMAT OrgFmt, D3DFORMAT FmtTarget = D3DFMT_UNKNOWN );
		virtual HRESULT CreateDeviceObject( D3DDEVTYPE DeviceType, Uint32 CreateFlag, D3DPRESENT_PARAMETERS &Param, IDirect3DDevice9 **ppDevice );
		virtual void GetAnisotropyFilterSupport( Bool &IsMin, Bool &IsMag, Uint32 &Max );

	protected:
		CGraphicCard();
		virtual ~CGraphicCard();

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool Initialize( Uint32 GraphicCardNo, eVertexShaderVersion VsVer );

		virtual void EnableHighlColorScreen( void );

		virtual Bool GetHDRRenderTargetSupport( void );
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor );
		virtual Bool GetNoPow2TextureSupport( void );

		virtual Sint32 GetScreenTypeCount( Bool IsFullColor );
		virtual void GetScreenType( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height );

		virtual Sint32 CreateRenderTargetTextureSizeCount( void );
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight );

		virtual void GetGraphicCardName( wchar_t *pName, Uint32 NameSize );
		virtual void GetGraphicCardDriver( wchar_t *pName, Uint32 NameSize );
		virtual void GetGraphicCardVersion( wchar_t *pName, Uint32 NameSize );

		virtual void SetSurfaceFormatTblFor2D( eSurfaceFormat FmtTbl[], Uint32 Count );
		virtual void SetSurfaceFormatTblFor3D( eSurfaceFormat FmtTbl[], Uint32 Count );

		virtual CPoint2D<Uint32> GetTextureMaxSize( void );
		virtual CPoint2D<Uint32> GetTextureSize( CPoint2D<Uint32> Size );

		virtual CCore *GetCorePointer( void );

		virtual IDevice *CreateDevice( void );
	};
}


#endif // ___SELENE__CGRAPHICCARD___

