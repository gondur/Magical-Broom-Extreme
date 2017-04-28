

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
		@brief �A�v���P�[�V�����Ǘ��N���X
		@author �t���`

		Windows�֘A�̊�{�������Ǘ�����N���X�ł��B
		�E�B���h�E�̐�������A���b�Z�[�W�����A
		�^�C�}�[�����A���b�Z�[�W�{�b�N�X�\���Ȃǂ�
		�E�B���h�E�A�v���̊�{�������Ǘ����Ă��܂�
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
		// �A�v���P�[�V�������
		HANDLE m_hMutex;							///< �~���[�e�b�N�X�n���h��
		wchar_t m_ApplicationName[128];				///< �A�v���P�[�V������
		Uint64 m_NowTime;							///< ���݃t���[������
		Uint64 m_OldTime;							///< �O�t���[������
		Uint64 m_BeforeTime;						///< �t���[����������
		// �E�B���h�E���
		HWND m_hWindow;								///< �E�B���h�E�n���h��
		Uint32 m_ScreenWidth;						///< ��ʉ���
		Uint32 m_ScreenHeight;						///< ��ʏc��
		Bool m_IsWindowType;						///< �E�B���h�E���[�h���ۂ�
		Bool m_IsActive;							///< �A�N�e�B�u���ۂ�
		Bool m_IsActiveWindow;						///< �E�B���h�E���A�N�e�B�u���ۂ�
		Bool m_IsInitAyame;							///< AYAME�������t���O
		Uint32 m_VirtualScreenWidth;				///< ���z��ʉ���
		Uint32 m_VirtualScreenHeight;				///< ���z��ʏc��
		Float m_fVirtual2RealX;						///< ���z��ʂ���X�N���[����ʂւ̕ϊ�
		Float m_fVirtual2RealY;						///< ���z��ʂ���X�N���[����ʂւ̕ϊ�
		Float m_fBackUpVirtual2RealX;				///< ���z��ʂ���X�N���[����ʂւ̕ϊ��p�����[�^�o�b�N�A�b�v
		Float m_fBackUpVirtual2RealY;				///< ���z��ʂ���X�N���[����ʂւ̕ϊ��p�����[�^�o�b�N�A�b�v
		// �t���[�����
		Uint32 m_SyncCount;							///< ���t���[����
		eFrameRate m_FrameRate;						///< �t���[�����[�g
		Uint32 m_FPS;								///< �b�ԃt���[����
		Uint32 m_OldFPS;							///< �b�ԃt���[�����o�b�N�A�b�v
		Uint32 m_PPS;								///< �b�ԃ|���S����
		Uint32 m_OldPPS;							///< �b�ԃ|���S�����o�b�N�A�b�v
		Uint32 m_PPS3D;								///< �b�ԂR�c�|���S����
		Uint32 m_OldPPS3D;							///< �b�ԂR�c�|���S�����o�b�N�A�b�v
		Uint32 m_PPF;								///< �t���[���|���S����
		Uint32 m_OldPPF;							///< �t���[���|���S�����o�b�N�A�b�v
		Uint32 m_PPF3D;								///< �t���[���R�c�|���S����
		Uint32 m_OldPPF3D;							///< �t���[���R�c�|���S�����o�b�N�A�b�v
		Float m_fFrameTime;							///< �t���[������
		// ��
		CFileManager *m_pFileManager;				///< �t�@�C���}�l�[�W���[
		CGraphicCard *m_pGraphicCard;				///< �r�f�I�J�[�h
		CDevice *m_pDevice;							///< �f�o�C�X
		CInput *m_pInput;							///< ���͊Ǘ�
		CKeyboard *m_pKeyboard;						///< �L�[�{�[�h
		CMouse *m_pMouse;							///< �}�E�X

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

		// �����ݒ�֘A
		virtual void SetVirtualScreenSize( Uint32 RealWidth, Uint32 RealHeight, Uint32 VirtualWidth, Uint32 VirtualHeight );
		// �擾�n
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
		// ���̑��e��
		virtual void DrawPolygon( Sint32 Cnt );
		virtual void DrawPolygon3D( Sint32 Cnt );
		virtual void ChangeScreenType( void );
		virtual void SetVirtualScreenEnable( Bool Flag );
		// �^�C�}�[�n
		virtual Uint64 GetSystemTime( void );
		virtual Uint64 GetSystemOneSecondTime( void );
		virtual Float GetFrameTime( void );
		virtual Uint32 GetSyncCount( void );
		virtual eFrameRate GetFrameRate( void );
		// �_�C�A���O
		virtual void MsgBox( Uint32 Flag, const wchar_t *pTitle, const wchar_t *pStr,... );
		virtual Bool SelectBox( const wchar_t *pTitle, const wchar_t *pStr,... );
		virtual Bool FolderSelect( wchar_t *pDirPath, Uint32 DirPathSize );
		virtual Bool FileOpenDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter, const wchar_t *pExt );
		virtual Bool FileSaveDialog( wchar_t *pPath, const wchar_t *pTitle, const wchar_t *pFilter, const wchar_t *pExt );
		virtual Bool OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB );
		// �r�f�I�J�[�h
		virtual IGraphicCard *CreateGraphicCard( Uint32 GraphicCardNo, eVertexShaderVersion VsVer );
		// �}�E�X
		virtual IMouse *GetMouse( void ) const;
		virtual IKeyboard *GetKeyboard( void ) const;
		// �t�@�C������
		virtual IFileManager *CreateFileMgr( void );
		virtual IFileManager *GetFileMgrPointer( void ) const;
		virtual void SetFileManager( IFileManager *pMgr );
		// �T�E���h
		virtual ISound *CreateSoundFromFile( const wchar_t *pFileName, Bool IsGlobalScope );
	};
}


#endif // ___SELENE__CCORE___

