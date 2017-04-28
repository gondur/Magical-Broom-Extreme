

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

	typedef IDirect3D9 * (WINAPI *PDIRECT3DCREATE9)( unsigned int );	///< Direct3Dオブジェクト生成関数

	/**
		@brief 3Dデバイス情報
		@author 葉迩倭
	*/
	struct DEVICEINFORMATION
	{
		Bool IsPureDevice;							///< ピュアデバイスをサポートしてるかどうか
		Bool IsHardwareTnL;							///< ハードウェアＴｎＬをサポートしてるかどうか
		Bool IsHardwareRasterize;					///< ハードウェアラスタライズをサポートしてるかどうか

		D3DDEVTYPE DeviceType;						///< デバイスタイプ

		Bool IsAutoMipMap;							///< ミップマップ自動生成をサポートしているか否か
		Bool IsCubeTexture;							///< キューブテークスチャをサポートしているか否か
		Bool IsStencilTwoSided;						///< 両面ステンシル処理が可能かどうか
		Bool IsMagAnisotropy;						///< 両面ステンシル処理が可能かどうか
		Bool IsMinAnisotropy;						///< 両面ステンシル処理が可能かどうか
		Bool IsSupportPow2Texture;					///< 2^n以外のテクスチャサイズが使えるかどうか

		Uint32 MaxAnisotropy;						///< 異方性フィルタ次数
		Uint32 MaxTextureWidth;						///< 最大テクスチャ横幅
		Uint32 MaxTextureHeight;					///< 最大テクスチャ縦幅

		Float GuardBandLeft;						///< ガードバンドクリッピング左位置
		Float GuardBandTop;							///< ガードバンドクリッピング上位置
		Float GuardBandRight;						///< ガードバンドクリッピング右位置
		Float GuardBandBottom;						///< ガードバンドクリッピング下位置

		Uint32 MaxPrimitiveCount;					///< 最大描画可能ポリゴン数
		Uint32 MaxVertexIndex;						///< 最大描画可能頂点インデックス数

		Uint32 MaxTextureBlendStages;				///< 最大テクスチャブレンディングステージ数
		Uint32 MaxSimultaneousTextures;				///< 最大テクスチャステージ数

		Uint32 VertexShaderVersion;					///< 頂点シェーダーバージョン
		Uint32 PixelShaderVersion;					///< ピクセルシェーダーバージョン
		Uint32 MaxVertexShaderConst;				///< 最大頂点シェーダー定数レジスタ数

		Uint32 DynamicFlowControlDepth;				///< 頂点シェーダーでの動的フロー制御最大ネスト数
		Uint32 StaticFlowControlDepth;				///< 頂点シェーダーでの静的フロー制御最大ネスト数

		Uint32 MultiRenderTargetCount;				///< マルチレンダリングターゲット数
	};

	/**
		@brief ビデオカード情報管理クラス
		@author 葉迩倭
	*/
	class CGraphicCard : public CBaseObject, public IGraphicCard
	{
		friend CCore;
		friend CRender;
		friend CDevice;
		friend CTexture;
		friend CSurface;

	protected:
		eSurfaceFormat m_SurfaceFormatTbl[2][16];				///< サーフェイスフォーマット検索テーブル
		Uint32 m_SurfaceFormatCount[2];							///< サーフェイスフォーマット数

		HINSTANCE m_hDllD3D9;									///< DLLハンドル
		IDirect3D9 *m_pDirect3D;								///< Direct3Dオブジェクト

		Uint32 m_GraphicCardNo;									///< ビデオカード番号
		wchar_t m_GraphicCardName[128];							///< ビデオカード名
		wchar_t m_GraphicCardDriver[128];						///< ビデオカードドライバー名
		wchar_t m_GraphicCardVersion[128];						///< ビデオカードバージョン名

		Uint32 m_MaxUseVertexShaderVersion;						///< 使用する頂点シェーダーの最大バージョン
		DEVICEINFORMATION m_DeviceInfo;							///< デバイス情報

		D3DDISPLAYMODE m_WindowType;							///< ウィンドウモードのディスプレイモード
		D3DDISPLAYMODE m_FullScreenType[2];						///< フルクリーンモードのディスプレイモード
		D3DPRESENT_PARAMETERS m_PresentParams[2];				///< プレゼンテーションパラメーター

		Bool m_IsHighColor;										///< 16Bit画面モードかどうか
		Bool m_IsWaitBlank;										///< VSYNC待ちをするかどうか
		Bool m_IsHVPerfHUD;										///< NVPerfHUDを使うかどうか

		Sint32 m_ScreenTypeCount;								///< 画面モード数
		D3DDISPLAYMODE m_ScreenType[64];						///< 画面モード

		Sint32 m_DepthCount;									///< 深度フォーマット数
		D3DFORMAT m_DepthFormats[16];							///< 深度フォーマット

		Sint32 m_TextureCount;									///< テクスチャフォーマット数
		D3DFORMAT m_TextureFormats[64];							///< テクスチャフォーマット

		Sint32 m_TargetCount;									///< レンダリングターゲットフォーマット数
		D3DFORMAT m_TargetFormats[32];							///< レンダリングターゲットフォーマット

		CDevice *m_pDevice;										///< デバイス

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

