

#ifndef ___SELENE__CCORE___
#define ___SELENE__CCORE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Core/CGraphicCard.h"
#include "Object/CBaseObject.h"
#include "Interface/Core/ICore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CInput;
	class CKeyboard;
	class CMouse;
	class CFileHtmlLog;
	class CGraphicCard;
	class CDevice;
	class CSystem;
	class CFileManager;
	/**
		@brief アプリケーション管理クラス
		@author 葉迩倭

		Windows関連の基本部分を管理するクラスです。
		ウィンドウの生成から、メッセージ処理、
		タイマー処理、メッセージボックス表示などの
		ウィンドウアプリの基本部分を管理しています
	*/
	class CCore : public CBaseObject, public ICore
	{
		friend CGraphicCard;
		friend CDevice;

	private:
		static LRESULT CALLBACK CommonMsgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

	public:
		static ICore *CreateCore( void );

	protected:
		// アプリケーション情報
		HANDLE m_hMutex;							///< ミューテックスハンドル
		wchar_t m_ApplicationName[128];				///< アプリケーション名
		Uint64 m_NowTime;							///< 現在フレーム時間
		Uint64 m_OldTime;							///< 前フレーム時間
		Uint64 m_BeforeTime;						///< フレーム差分時間
		// ウィンドウ情報
		HWND m_hWindow;								///< ウィンドウハンドル
		Uint32 m_ScreenWidth;						///< 画面横幅
		Uint32 m_ScreenHeight;						///< 画面縦幅
		Bool m_IsWindowType;						///< ウィンドウモードか否か
		Bool m_IsActive;							///< アクティブか否か
		Bool m_IsActiveWindow;						///< ウィンドウがアクティブか否か
		Bool m_IsInitAyame;							///< AYAME初期化フラグ
		Uint32 m_VirtualScreenWidth;				///< 仮想画面横幅
		Uint32 m_VirtualScreenHeight;				///< 仮想画面縦幅
		Float m_fVirtual2RealX;						///< 仮想画面からスクリーン画面への変換
		Float m_fVirtual2RealY;						///< 仮想画面からスクリーン画面への変換
		Float m_fBackUpVirtual2RealX;				///< 仮想画面からスクリーン画面への変換パラメータバックアップ
		Float m_fBackUpVirtual2RealY;				///< 仮想画面からスクリーン画面への変換パラメータバックアップ
		// フレーム情報
		Uint32 m_SyncCount;							///< 総フレーム数
		eFrameRate m_FrameRate;						///< フレームレート
		Uint32 m_FPS;								///< 秒間フレーム数
		Uint32 m_OldFPS;							///< 秒間フレーム数バックアップ
		Uint32 m_PPS;								///< 秒間ポリゴン数
		Uint32 m_OldPPS;							///< 秒間ポリゴン数バックアップ
		Uint32 m_PPS3D;								///< 秒間３Ｄポリゴン数
		Uint32 m_OldPPS3D;							///< 秒間３Ｄポリゴン数バックアップ
		Uint32 m_PPF;								///< フレームポリゴン数
		Uint32 m_OldPPF;							///< フレームポリゴン数バックアップ
		Uint32 m_PPF3D;								///< フレーム３Ｄポリゴン数
		Uint32 m_OldPPF3D;							///< フレーム３Ｄポリゴン数バックアップ
		Float m_fFrameTime;							///< フレーム時間
		// 他
		CFileManager *m_pFileManager;				///< ファイルマネージャー
		CGraphicCard *m_pGraphicCard;				///< ビデオカード
		CDevice *m_pDevice;							///< デバイス
		CInput *m_pInput;							///< 入力管理
		CKeyboard *m_pKeyboard;						///< キーボード
		CMouse *m_pMouse;							///< マウス

	private:
		CCore( void );
		virtual ~CCore( void );

	protected:
		virtual Bool RegisterWindowClass( void );
		virtual Bool WindowCreate( void );
		virtual void UpdateWidow( void );
		virtual void Message( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
		virtual void SyncFrame( void );
		virtual void SetWindowCenter( HWND hWnd, HWND hWndParent );
		virtual void SetDevice( CDevice *pDevice );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool Initialize( const wchar_t *pAppName, eFrameRate FrameRate );
		virtual void Start( Uint32 ScreenWidth, Uint32 ScreenHeight, Bool IsWindowType );

		virtual void Exit( void );
		virtual Bool Run( Bool IsFullActive );

		// 初期設定関連
		virtual void SetVirtualScreenSize( Uint32 RealWidth, Uint32 RealHeight, Uint32 VirtualWidth, Uint32 VirtualHeight );
		// 取得系
		virtual HWND GetWindowHandle( void );
		virtual Sint32 GetFPS( void );
		virtual Sint32 GetPPS( void );
		virtual Sint32 GetPPF( void );
		virtual Sint32 GetPPS3D( void );
		virtual Sint32 GetPPF3D( void );
		virtual void GetApplicationName( wchar_t *pAppName, Uint32 AppNameSize );
		virtual void GetScreenData( Uint32 *pWidth, Uint32 *pHeight, Bool *pIsWindow );
		virtual void GetVirtualScreenSize( Sint32 *pWidth, Sint32 *pHeight );
		virtual Float Virtual2RealX( Float Pos );
		virtual Float Virtual2RealY( Float Pos );
		// その他各種
		virtual void DrawPolygon( Sint32 Cnt );
		virtual void DrawPolygon3D( Sint32 Cnt );
		virtual void ChangeScreenType( void );
		virtual void SetVirtualScreenEnable( Bool Flag );
		// タイマー系
		virtual Uint64 GetSystemTime( void );
		virtual Uint64 GetSystemOneSecondTime( void );
		virtual Float GetFrameTime( void );
		virtual Uint32 GetSyncCount( void );
		virtual eFrameRate GetFrameRate( void );
		// ダイアログ
		virtual void MsgBox( Uint32 Flag, const wchar_t *pTitle, const wchar_t *pStr,... );
		virtual Bool SelectBox( const wchar_t *pTitle, const wchar_t *pStr,... );
		virtual Bool FolderSelect( wchar_t *pDirPath, Uint32 DirPathSize );
		virtual Bool FileOpenDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter, const wchar_t *pExt );
		virtual Bool FileSaveDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter, const wchar_t *pExt );
		virtual Bool OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB );
		// ビデオカード
		virtual IGraphicCard *CreateGraphicCard( Uint32 GraphicCardNo, eVertexShaderVersion VsVer );
		// マウス
		virtual IMouse *GetMouse( void ) const;
		virtual IKeyboard *GetKeyboard( void ) const;
		// ファイル操作
		virtual IFileManager *CreateFileMgr( void );
		virtual IFileManager *GetFileMgrPointer( void ) const;
		virtual void SetFileManager( IFileManager *pMgr );
		// サウンド
		virtual ISound *CreateSoundFromFile( const wchar_t *pFileName, Bool IsGlobalScope );
	};
}


#endif // ___SELENE__CCORE___

