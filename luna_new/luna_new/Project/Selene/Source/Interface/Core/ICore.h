

#ifndef ___SELENE__ICORE___
#define ___SELENE__ICORE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �t���[�����[�g��`
		@author �t���`
	*/
	enum eFrameRate
	{
		FRAME_RATE_60,
		FRAME_RATE_30,
		FRAME_RATE_20,
		FRAME_RATE_15,
		FRAME_RATE_VSYNC,
	};

	/**
		@brief �E�B���h�E�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class ICore
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																							= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																							= 0;

		/**
			@brief �R�A�̏�����
			@author �t���`
			@param pAppName		[in] �A�v���P�[�V������
			@param FrameRate	[in] �t���[�����[�g
			@retval false	���s
			@retval true	����

			�A�v���P�[�V�����Ɋւ��鏉�������s���܂��B
		*/
		virtual Bool Initialize( const wchar_t *pAppName, eFrameRate FrameRate )														= 0;

		/**
			@brief �R�A�̊J�n
			@author �t���`
			@param ScreenWidth	[in] ��ʉ���
			@param ScreenHeight	[in] ��ʏc��
			@param IsWindowType	[in] �E�B���h�E���[�h�t���O

			�E�B���h�E���쐬���A�A�v���P�[�V�������N�����܂��B<BR>
			�����ł̐ݒ�ŋN����ύX�\�Ȃ��͉̂�ʃ��[�h�����ł��B
		*/
		virtual void Start( Uint32 ScreenWidth, Uint32 ScreenHeight, Bool IsWindowType )										= 0;

		/**
			@brief �R�A�̏I��
			@author �t���`

			�E�B���h�E����̂��A�A�v���P�[�V�������I�����܂��B<BR>
			���̊֐��͏I����ʒm���邾���ŁA���ۂɂ̓��C�����[�v���<BR>
			�I���������s���܂��B<BR>
		*/
		virtual void Exit( void )																								= 0;

		/**
			@brief �A�v���P�[�V�������C������
			@author �t���`
			@param IsFullActive	[in] �펞����t���O
			@retval false	�A�v���P�[�V�����͏I������
			@retval true	�A�v���P�[�V�����͉ғ���

			IsFullActive��true���w�肷��ƁA<BR>
			�E�B���h�E���t�H�[�J�X�������Ă����Ԃł����삵�����܂��B
		*/
		virtual Bool Run( Bool IsFullActive = false )																			= 0;

		/**
			@brief �E�B���h�E�n���h���擾
			@author �t���`
			@return �E�B���h�E�̃E�B���h�E�n���h��

			ICore�̏��L����E�B���h�E�̃E�B���h�E�n���h�����擾���܂��B
		*/
		virtual HWND GetWindowHandle( void )																					= 0;

		/**
			@brief �E�B���h�E�n���h���擾
			@author �t���`
			@return �E�B���h�E�̃E�B���h�E�n���h��

			ICore�̏��L����E�B���h�E�̃E�B���h�E�n���h�����擾���܂��B
		*/
		virtual void SetVirtualScreenEnable( Bool Flag )																		= 0;

		/**
			@brief ���z��ʐݒ�
			@author �t���`
			@param RealWidth		[in] ����ʂ̉���
			@param RealHeight		[in] ����ʂ̏c��
			@param VirtualWidth		[in] ���z��ʂ̉���
			@param VirtualHeight	[in] ���z��ʂ̏c��

			�ω�ʃT�C�Y�p�̐ݒ���s���܂��B<BR>
			3D�p�ɉ�ʂ̃T�C�Y�����R�ɕς�����悤�ɍ���Ă���ꍇ�ł�<BR>
			2D�̕`��͉��z��ʂɐݒ肳�ꂽ��ʃT�C�Y�ƌ����Ăĕ`����s���܂��B<BR>
			�܂艼�z��ʂ�(640x480)�̎���(0,0)-(640,480)�ւ̑S��ʂ�2D�`����s�����ꍇ�A<BR>
			���ۂ̉�ʂ̃T�C�Y��(320x240)��(1280x960)���̃T�C�Y�ł����Ă�<BR>
			�S��ʂɎ����I�Ɋg��k�����ĕ`�悳���Ƃ������Ƃł��B
		*/
		virtual void SetVirtualScreenSize( Uint32 RealWidth, Uint32 RealHeight, Uint32 VirtualWidth, Uint32 VirtualHeight )		= 0;

		/**
			@brief �t���[�����Ԃ��擾���܂��B
			@author �t���`
			@return �t���[������

			�O�t���[���̏����ɂ����������Ԃ��擾���܂��B<BR>
			���̃t���[�����Ԃ�1�b��1.0�ɂȂ�悤�ɂȂ��Ă��܂��B<BR>
			�σt���[�����[�g�n�̃Q�[�������ꍇ�ɗ��p���Ă��������B
		*/
		virtual Float GetFrameTime( void )																						= 0;

		/**
			@brief �t���[���J�E���g���擾���܂��B
			@author �t���`
			@return �t���[����

			�N��������̑��t���[�������擾���܂��B
		*/
		virtual Uint32 GetSyncCount( void )																						= 0;

		/**
			@brief �t���[�����[�g���擾���܂��B
			@author �t���`
			@return �t���[�����[�g

			���݂̃t���[�����[�g���擾���܂��B
		*/
		virtual eFrameRate GetFrameRate( void )																						= 0;

		/**
			@brief �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X���擾
			@author �t���`
			@param GraphicCardNo	[in] �O���t�B�b�N�J�[�h�ԍ�
			@param VsVer			[in] �g�p���钸�_�V�F�[�_�[�̃o�[�W����
			@return �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X

			�O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���A<BR>
			���̃C���^�[�t�F�C�X���擾���܂��B<BR>
			�ʏ�GraphicCardNo�ɂ�GRAPHIC_CARD_DEFAULT_NO���w�肵�܂��B<BR>
			�uNV PerfHUD�v�̃C���X�g�[�����ꂽ���ł́A<BR>
			GRAPHIC_CARD_NV_PERF_HUD���w�肷�邱�Ƃł����L���ɏo���܂��B
		*/
		virtual IGraphicCard *CreateGraphicCard( Uint32 GraphicCardNo, eVertexShaderVersion VsVer )								= 0;

		/**
			@brief �}�E�X�C���^�[�t�F�C�X���擾
			@author �t���`
			@return �}�E�X�C���^�[�t�F�C�X

			ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�}�E�X�̏��������s���A<BR>
			���̃C���^�[�t�F�C�X���擾���܂��B<BR>
			�}�E�X�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B
		*/
		virtual IMouse *GetMouse( void ) const																					= 0;

		/**
			@brief �L�[�{�[�h�C���^�[�t�F�C�X���擾
			@author �t���`
			@return �L�[�{�[�h�C���^�[�t�F�C�X

			ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�L�[�{�[�h�̏��������s���A<BR>
			���̃C���^�[�t�F�C�X���擾���܂��B<BR>
			�L�[�{�[�h�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B
		*/
		virtual IKeyboard *GetKeyboard( void ) const																			= 0;

		/**
			@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X����
			@author �t���`
			@return �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

			�V�K�̃t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�t�@�C���̃p�X�Ȃǂ̐ݒ�͑S��IFileManager���o�R���čs���܂��B
			�擾�����t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�͎g�p�I����ɂ͕K��Release()���ĉ������B�B
		*/
		virtual IFileManager *CreateFileMgr( void )																				= 0;

		/**
			@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�擾
			@author �t���`
			@return �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

			���ݐݒ肳��Ă���t�@�C���}�l�[�W���[�C���^�[�t�F�C�X���擾���܂��B<BR>
			�ݒ�ς݂̃t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�ւ̃A�N�Z�X���s���ꍇ�Ɏg�p���Ă��������B
		*/
		virtual IFileManager *GetFileMgrPointer( void ) const																	= 0;

		/**
			@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�ݒ�
			@author �t���`
			@param pMgr	[in] �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

			�t�@�C���̓ǂݍ��݂Ɏg����t�@�C���}�l�[�W���[�C���^�[�t�F�C�X��ݒ肵�܂��B<BR>
			�t�@�C���̓ǂݍ��݂͂��̃}�l�[�W���[���o�R���čs���̂ŁA<BR>
			�t�@�C���̓ǂݍ��݂��s���ꍇ�͕K���ݒ肵�Ă��������B<BR>
			���ɐݒ肳��Ă���}�l�[�W���[�͓����ŉ������܂��B
		*/
		virtual void SetFileManager( IFileManager *pMgr )																		= 0;

		/**
			@brief �T�E���h�t�@�C���ǂݍ���
			@author �t���`
			@param pFileName		[in] �T�E���h�t�@�C����(wav/ogg)
			@param IsGlobalScope	[in] �T�E���h�̃X�R�[�v
			@retval NULL		�t�@�C���ǂݍ��݃G���[
			@retval NULL�ȊO	�T�E���h�C���^�[�t�F�C�X�̃|�C���^

			ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�T�E���h���擾���܂��B<BR>
			IsGlobalScope��true��n���ƁA�E�B���h�E�̃t�H�[�J�X�Ɋ֌W�Ȃ�<BR>
			�Đ�����܂��B<BR>
			�g�p�̏I�������T�E���h�͕K��Release()���ĉ������B
		*/
		virtual ISound *CreateSoundFromFile( const wchar_t *pFileName, Bool IsGlobalScope )										= 0;
	};
}


#endif // ___SELENE__ICORE___

