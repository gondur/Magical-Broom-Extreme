//==============================================================================//
//                         DirectX9�p�ėp���C�u���� Selene                        //
//==============================================================================//
//                                                                              //
//    �ŐV�ł̒u���Ă���URL                                                     //
//                                                                              //
//    TWINTAIL LOVERS.                                                          //
//      http://www.twin-tail.jp/                                                //
//                                                                              //
//    ���ⓙ�����ꏊ                                                            //
//      TWINTAIL LOVERS.���̌f����                                              //
//                                                                              //
//   DirectX Library 'Selene'                                                   //
//   Copyright (C) 2006 �t���`                                                  //
//   All rights reserved.                                                       //
//                                                                              //
//==============================================================================//


#ifndef ___SELENE_H___
#define ___SELENE_H___


#undef _UNICODE
#define _UNICODE
#undef UNICODE
#define UNICODE

#include <stdio.h>
#include <windows.h>

#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )

#pragma warning ( disable: 4819 )
#pragma warning ( disable: 4201 )

typedef char					Sint8;								///< signed char �^�̕ʒ�`
typedef short					Sint16;								///< signed short �^�̕ʒ�`
typedef long					Sint32;								///< signed long �^�̕ʒ�`
typedef __int64					Sint64;								///< signed __int64 �^�̕ʒ�`
typedef unsigned char			Uint8;								///< unsigned char �^�̕ʒ�`
typedef unsigned short			Uint16;								///< unsigned short �^�̕ʒ�`
typedef unsigned long			Uint32;								///< unsigned long �^�̕ʒ�`
typedef unsigned __int64		Uint64;								///< unsigned __int64 �^�̕ʒ�`
typedef float					Float;								///< Float �^�̕ʒ�`
typedef float					Float32;							///< Float �^�̕ʒ�`
typedef double					Float64;							///< double �^�̕ʒ�`
typedef long double				Float80;							///< long double �^�̕ʒ�`
typedef bool					Bool;								///< Bool �^�̕ʒ�`

typedef void					*FX_HANDLE;							///< �G�t�F�N�g�t�@�C���̃n���h��

#define ef									else if																		///< else if �ȗ��p�}�N��

#define toF(val)							((Float)(val))																///< Float�^�ւ̃L���X�g�}�N��
#define toI(val)							((Sint32)(val))																///< Sint32�^�ւ̃L���X�g�}�N��

#define PI									(3.141592653589793238462643383279f)											///< ��
#define PI2									(6.283185307179586476925286766559f)											///< 2��
#define REV(val)							toF(1.0f/toF(val))															///< �t���Z�o�}�N��

#define SHADER_BONE_MAX						(48)

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))													///< �ŏ��l�擾�}�N��
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))													///< �ő�l�擾�}�N��
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< �l�����}�N��

#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }							///< COM���S����}�N��
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }								///< new���������S���
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }							///< new[]���������S���

#define ANGLE_TABLE_BIT						(16)																		///< �T�C���e�[�u���̃r�b�g��
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)														///< �T�C���e�[�u���̃T�C�Y
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)																///< �T�C���e�[�u���̃A�N�Z�X�p�}�X�N
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)													///< �p�x�̐��K��
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)													///< �x���@�����p�p�x
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)											///< �ʓx�@�����p�p�x
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))												///< ��p�p�x����ʓx�@

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)													///< �������N���A
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))													///< �������h��Ԃ�
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))													///< �������ړ�
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))													///< �������R�s�[

#define MemGlobalAlloc(size)				(::VirtualAlloc( NULL, ((size)+4095)&~4095, MEM_COMMIT, PAGE_READWRITE ))					///< VirtuakAlloc�������m�ۃ}�N��
#define MemGlobalFree(pointer)				if ( (pointer) != NULL ) { ::VirtualFree( pointer, 0, MEM_RELEASE ); (pointer) = NULL; }	///< VirtualAlloc����������}�N��

#define MemLocalAlloc(size)					::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, size )										///< HeapAlloc�������m�ۃ}�N��
#define MemLocalFree(pointer)				if ( (pointer) != NULL ) { ::HeapFree( ::GetProcessHeap(), 0, pointer ); (pointer) = NULL; }	///< HeapAlloc����������}�N��

#ifdef LIB_SELENE
#	define SELENE_DLL_API
#else // LIB_SELENE
#	ifdef DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllexport)
#	else // DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllimport)
#	endif // DLL_SELENE
#endif // LIB_SELENE

namespace Selene
{
	class ICore;
	class IGraphicCard;
	class IDevice;
	class IResourceFile;
	class IFileManager;
	class IMouse;
	class IKeyboard;
	class IRender;
	class IPostEffect;
	class IPointPrimitive2D;
	class ILinePrimitive2D;
	class IPrimitive2D;
	class ISprite2D;
	class IFontSprite2D;
	class IPointPrimitive3D;
	class ILinePrimitive3D;
	class IPrimitive3D;
	class IFrame;
	class IMesh;
	class IModel;
	class ISceneCamera;
	class ISceneManager;
	class ISound;
	class ISurface;
	class ITexture;

	class CVector2D;
	class CVector3D;
	class CVector4D;
	class CMatrix;
	class CStyle;
	class CQuaternion;
}

void SELENE_DLL_API GetVersioinInfo( wchar_t *pVersionStr, Uint32 Length );



namespace Selene
{
	/**
		@brief �F���Ǘ��N���X
		@author �t���`

		�e��f�[�^�̐F���`���邽�߂̃N���X�ł��B<BR>
		���C�u�������ŐF���w�肷��ꍇ�͂��ׂĂ��̃N���X���g���܂��B
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< �F�̐���
				Uint8 g;		///< �F�̗ΐ���
				Uint8 r;		///< �F�̐Ԑ���
				Uint8 a;		///< �F�̓����x����
			};
			Uint32 Color;		///< �F��32Bit�����\�L
		};

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CColor()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param r		[in] �Ԑ����i�O�`�Q�T�T�j
			@param g		[in] �ΐ����i�O�`�Q�T�T�j
			@param b		[in] �����i�O�`�Q�T�T�j
			@param a		[in] �A���t�@�����i�O�`�Q�T�T�j
		*/
		CColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255 )
		{
			this->a = a;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param Color	[in] �F����
		*/
		CColor( Uint32 Color )
		{
			this->Color = Color;
		}

		/**
			@brief �I�y���[�^�[=���Z�q
			@author �t���`
		*/
		CColor operator = ( CColor &Color )
		{
			this->a = Color.a;
			this->r = Color.r;
			this->g = Color.g;
			this->b = Color.b;

			return *this;
		}

		/**
			@brief �I�y���[�^�[=���Z�q
			@author �t���`
		*/
		CColor operator = ( Uint32 Color )
		{
			this->Color = Color;

			return *this;
		}

		/**
			@brief �^�ϊ�
			@author �t���`
		*/
		operator Uint32 ()
		{
			return Color;
		}

		/**
			@brief �^�ϊ�
			@author �t���`
		*/
		operator const Uint32 () const
		{
			return Color;
		}
	};
}



namespace Selene
{
namespace System
{
	/**
		@brief �V�X�e��������
		@author �t���`
		@retval true	����
		@retval false	���s

		Selene�V�X�e���̏��������s���܂��B
	*/
	SELENE_DLL_API Bool Initialize( void );

	/**
		@brief �V�X�e���I��
		@author �t���`

		Selene�V�X�e���̏I�������܂��B
	*/
	SELENE_DLL_API void Finalize( void );

	/**
		@brief ���d�N���u���b�N
		@author �t���`
		@param pApplicationName	[in] �A�v���P�[�V������
		@retval false	���ɓ����̃A�v���P�[�V�������N�����Ă���
		@retval true	�����̃A�v���P�[�V�����͑��݂��Ȃ�

		�Ԃ�lfalse���ɃA�v���P�[�V�������I�������邱�Ƃ�<BR>
		���d�N����h�~���邱�Ƃ��ł��܂��B
	*/
	SELENE_DLL_API Bool BlockDualBoot( const wchar_t *pApplicationName );

	/**
		@brief SSE2�T�|�[�g�L��
		@author �t���`
		@retval false	SSE2���T�|�[�g���Ă��Ȃ�
		@retval true	SSE2���T�|�[�g���Ă���

		SSE2���T�|�[�g���Ă��邩�ǂ����𒲂ׂ܂��B
	*/
	SELENE_DLL_API Bool IsSuportSSE( void );

	/**
		@brief �J�����g�f�B���N�g�����Z�b�g
		@author �t���`

		�J�����g�f�B���N�g�����A�v���P�[�V�����̎��s�t�H���_�ɐݒ肵�܂��B
	*/
	SELENE_DLL_API void ResetCurrentDirectory( void );

	/**
		@brief �f�B���N�g������
		@author �t���`
		@param pPath	[in] �t�H���_�p�X

		�w��p�X�փf�B���N�g���𐶐����܂��B<BR>
		�r���̃t�H���_�����݂��Ȃ��ꍇ�A�S�Ă̊K�w�ɑ΂��ăt�H���_���쐬���Ă����܂��B
	*/
	SELENE_DLL_API void CreateDirectory( const wchar_t *pPath );

	/**
		@brief Core�̎擾
		@author �t���`
		@return ICore�C���^�[�t�F�C�X

		�E�B���h�E���Ǘ�����ICore�N���X�𐶐�/�擾���܂��B<BR>
		���݁A�P��ICore���������ł��܂���B
	*/
	SELENE_DLL_API ICore *CreateCore( void );
}
}



namespace Selene
{
	/**
		@brief �A�j���[�V�����^�C�v��`
		@author �t���`
	*/
	enum eAnimationType
	{
		ANIM_TYPE_STEP,							///< �X�e�b�v���
		ANIM_TYPE_LINEAR,						///< ���`���
		ANIM_TYPE_TCB,							///< �s�b�a�X�v���C�����
	};

	/**
		@brief �L�[�t���[���f�[�^
		@author �t���`
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< �X�v���C������IN�W����萔�ɂ��邩�ǂ���
		Bool IsOut;								///< �X�v���C������OUT�W����萔�ɂ��邩�ǂ���
		Float fTime;							///< �L�[����
		Float fParam;							///< �L�[�l
		Float fIn;								///< IN�W���̒萔
		Float fOut;								///< OUT�W���̒萔

		SKeyFrame *pPrev;						///< �O���L�[�t���[���f�[�^�|�C���^
		SKeyFrame *pNext;						///< ����L�[�t���[���f�[�^�|�C���^
	};

	/**
		@brief �A�j���[�V�����N���X
		@author �t���`
	*/
	class CAnimation
	{
	private:
		Float m_fTimeFirst;						///< �J�n����
		Float m_fTimeLast;						///< �I������
		SKeyFrame *m_pKeys;						///< �L�[�t���[���f�[�^�|�C���^
		Uint32 m_KeyMax;						///< �L�[�t���[����

	private:
		/**
			@brief �w�莞�Ԃ���ł��߂��L�[�f�[�^���擾���܂�
			@author �t���`
			@param pKeys		[in] �L�[�t���[���f�[�^
			@param fTime		[in] ��������
			@param KeyMax		[in] �L�[�ő吔
			@return �L�[�t���[���f�[�^�|�C���^

			�w�莞�Ԃ�������Ƃ��߂��L�[�����A<BR>
			�o�C�i���T�[�`�Ō������܂��B
		*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

		/**
			@brief �G���~�[�g��Ԋ֐����������܂�
			@author �t���`
			@param fTime	[in] ����
			@param pH1		[out] �p�����[�^�[�i�[��P
			@param pH2		[out] �p�����[�^�[�i�[��Q
			@param pH3		[out] �p�����[�^�[�i�[��R
			@param pH4		[out] �p�����[�^�[�i�[��S

			�G���~�[�g��Ԋ֐����g���ė^����ꂽ�p�����[�^�[����<BR>
			���ʂ��Z�o���܂��B
		*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

		/**
			@brief �O���̃L�[�̏o�͐�̃p�����[�^�����߂܂�
			@author �t���`
			@param pKey0	[in] �O���L�[�f�[�^
			@param pKey1	[in] ����L�[�f�[�^
			@return �Z�o���ꂽ�p�����[�^�[

			�w�莞�Ԃɑ΂��Ă̒��O�̃L�[�̋������v�Z���܂��B
		*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

		/**
			@brief ����̃L�[�̏o�͐�̃p�����[�^�����߂܂�
			@author �t���`
			@param pKey0	[in] �O���L�[�f�[�^
			@param pKey1	[in] ����L�[�f�[�^
			@return �Z�o���ꂽ�p�����[�^�[

			�w�莞�Ԃɑ΂��Ă̒���̃L�[�̋������v�Z���܂��B
		*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param KeyMax		[in] �L�[�ő吔
		*/
		CAnimation( Uint32 KeyMax );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CAnimation();

		/**
			@brief �L�[�t���[���f�[�^�ɃL�[��ݒ肵�܂�
			@author �t���`
			@param KeyNo		[in] �ݒ��L�[�ԍ�
			@param fTime		[in] �ݒ莞��
			@param fParam		[in] �ݒ�p�����[�^
			@param IsIn			[in] ���̓p�����[�^�[�w��L��
			@param IsOut		[in] �o�̓p�����[�^�[�w��L��
			@param fIn			[in] ���̓p�����[�^�[
			@param fOut			[in] �o�̓p�����[�^�[
			@return ��������true

			�w��̃L�[�ɑ΂��āA��ԗp�̃p�����[�^�[��ݒ肵�܂��B
		*/
		virtual Bool SetKey( Uint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

		/**
			@brief �w��^�C�v�̃A�j���[�V�����Ŏw�莞�Ԃɂ�����l���擾���܂�
			@author �t���`
			@param fTime		[in] ����
			@param Type			[in] ��ԃ^�C�v
			@param fDefault		[in] �f�t�H���g�l
			@return		��Ԍ��ʒl

			�w�莞�Ԃɑ΂��Ďw��^�C�v�ŕ�Ԃ����ꍇ�̌��ʂ��擾���܂��B
		*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}



namespace Selene
{
	/**
		@brief �N���e�B�J���Z�N�V�����Ǘ��N���X
		@author �t���`
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< �N���e�B�J���Z�N�V����

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CCriticalSection();

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CCriticalSection();

		/**
			@brief �N���e�B�J���Z�N�V�����ɓ���
			@author �t���`

			�N���e�B�J���Z�N�V�����ɓ���܂��B
		*/
		void Enter( void );

		/**
			@brief �N���e�B�J���Z�N�V�������甲����
			@author �t���`

			�N���e�B�J���Z�N�V�������甲���܂��B
		*/
		void Leave( void );
	};
}



namespace Selene
{
	/**
		@brief �X���b�h�p�C�x���g�I�u�W�F�N�g
		@author �t���`
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];					///< �C�x���g�n���h��
		Uint32 m_HandleCount;										///< �C�x���g��

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param IsSignal		[in] �V�O�i����Ԃŏ���������ꍇ��true
			@param Count		[in] �C�x���g�̃J�E���g�iMAXIMUM_WAIT_OBJECTS�ȉ��j
		*/
		CEvent( Bool IsSignal = false, Uint32 Count = 1 );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CEvent();

		/**
			@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
			@author �t���`
			@param No	[in] �V�O�i����Ԃ���C�x���g�̔ԍ�
		*/
		virtual void Set( Uint32 No = 0 );

		/**
			@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
			@author �t���`
			@param No	[in] ��V�O�i����Ԃ���C�x���g�̔ԍ�
		*/
		virtual void Reset( Uint32 No = 0 );

		/**
			@brief �w�肵���C�x���g���V�O�i����Ԃ��`�F�b�N
			@author �t���`
			@param No	[in] �`�F�b�N����C�x���g�̔ԍ�
			@retval false	��V�O�i�����
			@retval true	�V�O�i�����
		*/
		virtual Bool IsSignal( Uint32 No = 0 );

		/**
			@brief �S�ẴC�x���g���V�O�i����Ԃ��`�F�b�N
			@author �t���`
			@retval false	��V�O�i�����
			@retval true	�V�O�i�����
		*/
		virtual Bool IsSignalAll( void );

		/**
			@brief �V�O�i����ԂɂȂ����C�x���g���擾
			@author �t���`
			@param TimeOut		[in] �^�C���A�E�gms���ԁi-1�Ŗ����j
			@retval -1		�^�C���A�E�g
			@retval 0�ȏ�	�V�O�i����ԂɂȂ����C�x���g�ԍ�
		*/
		virtual Sint32 Wait( Uint32 TimeOut = -1 );
	};
}



namespace Selene
{
	/**
		@brief �X���b�h�Ǘ�����N���X
		@author �t���`

		�X���b�h�𑀍삷�邽�߂̃N���X�ł��B
	*/
	class SELENE_DLL_API CThread
	{
	private:
		/**
			@brief �X���b�h�p�֐�
			@author �t���`
			@param pArguments	[in] CThread�̃|�C���^

			�N���X�̊֐��𒼐ڂ͎w��ł��Ȃ��̂�<BR>
			static�Ȋ֐����o�R���ČĂяo���B
		*/
		static unsigned __stdcall ThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< �X���b�h�n���h��
		Uint32 m_ThreadId;					///< �X���b�hID
		void *m_pData;						///< �X���b�h�f�[�^�`�B�p�|�C���^
		void (*m_pMainProc)( void* );		///< �X���b�h�֐�

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CThread();

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CThread();

	public:
		/**
			@brief �X���b�h����
			@author �t���`
			@param pThreadFunc	[in] �X���b�h�֐�
			@param pData		[in] �X���b�h�Ɉ����n���f�[�^�|�C���^
			@retval false	�������sor���ɃX���b�h����������Ă���
			@retval true	��������
		*/
		virtual Bool Create( void (*pThreadFunc)( void* ), void *pData );

		/**
			@brief �X���b�h�I���҂�
			@author �t���`
			@param TimeOut		[in] �I���҂������鎞�Ԃ�ms�Őݒ肵�܂��B<BR>-1���w�肷��Ɩ����ɑ҂��܂��B

			�X���b�h���I������̂�҂��܂�
		*/
		virtual void WaitForExit( Sint32 TimeOut );

		/**
			@brief �X���b�h�̗D��x�ύX
			@author �t���`
			@param Priority		[in] �X���b�h�����̗D��x

			�X���b�h�̗D��x��ύX���܂��B<BR>
			�f�t�H���g�̗D��x��THREAD_PRIORITY_NORMAL�ł��B
		*/
		virtual Bool SetPriority( Sint32 Priority );

		/**
			@brief �X���b�h�̒��f������
			@author �t���`

			�X���b�h�̃T�X�y���h�J�E���g�� 1 ����܂��B<BR>
			�J�E���g�� 0 �ɂȂ������_�ŃX���b�h�̒��f����������܂��B
		*/
		virtual void Resume( void );

		/**
			@brief �X���b�h�̎��s�𒆒f
			@author �t���`

			�w�肳�ꂽ�X���b�h�̎��s�����f����A<BR>
			���̃X���b�h�̃T�X�y���h�J�E���g�� 1 �����܂��B
		*/
		virtual void Suspend( void );
	};
}



namespace Selene
{
	/**
		@brief �x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API CVector2D
	{
	public:
		Float x;
		Float y;

	public:
		CVector2D();
		CVector2D( const CVector2D &v );
		CVector2D( Float fPx, Float fPy );

		void Add( CVector2D &In1, CVector2D &In2 );
		void Sub( CVector2D &In1, CVector2D &In2 );
		void Set( Float fPx, Float fPy );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector2D &In );
		void Reflect( CVector2D &In1, CVector2D &In2 );

		void Normalize( void );
		Float Cross( CVector2D &In1, CVector2D &In2 );

		void Normalize( CVector2D &In );
		Float Cross( CVector2D &In );
		void Reflect( CVector2D &In );

		void Scaling( Float sx, Float sy );
		void Translation( Float px, Float py );

		CVector2D& operator += ( const CVector2D& );
		CVector2D& operator -= ( const CVector2D& );
		CVector2D& operator *= ( Float );
		CVector2D& operator /= ( Float );

		CVector2D operator + () const;
		CVector2D operator - () const;

		CVector2D operator + ( const CVector2D& ) const;
		CVector2D operator - ( const CVector2D& ) const;
		CVector2D operator * ( Float ) const;
		CVector2D operator / ( Float ) const;
	};
}



namespace Selene
{
	/**
		@brief �x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API CVector3D
	{
	public:
		Float x;
		Float y;
		Float z;

	public:
		CVector3D();
		CVector3D( const CVector3D &v );
		CVector3D( Float fPx, Float fPy, Float fPz );

		void Add( CVector3D &In1, CVector3D &In2 );
		void Sub( CVector3D &In1, CVector3D &In2 );
		void Set( Float fPx, Float fPy, Float fPz );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector3D &In );

		void Normalize( void );
		void Cross( CVector3D &In1, CVector3D &In2 );
		void Reflect( CVector3D &In1, CVector3D &In2 );
		void TransformNormal( CVector3D &In1, CMatrix &In2 );
		void TransformCoord( CVector3D &In1, CMatrix &In2 );
		void TransformProjection( CVector3D &In1, CMatrix &In2 );

		void Normalize( CVector3D &In );
		void Cross( CVector3D &In );
		void Reflect( CVector3D &In );
		void TransformNormal( CMatrix &In );
		void TransformCoord( CMatrix &In );
		void TransformProjection( CMatrix &In );

		void RotationX( Sint32 Angle );
		void RotationY( Sint32 Angle );
		void RotationZ( Sint32 Angle );
		void RotationAxis( Sint32 Angle, CVector3D &Axis );
		void Scaling( Float sx, Float sy, Float sz );
		void Translation( Float px, Float py, Float pz );

		CVector3D& operator += ( const CVector3D& );
		CVector3D& operator -= ( const CVector3D& );
		CVector3D& operator *= ( Float );
		CVector3D& operator /= ( Float );

		CVector3D operator + () const;
		CVector3D operator - () const;

		CVector3D operator + ( const CVector3D& ) const;
		CVector3D operator - ( const CVector3D& ) const;
		CVector3D operator * ( Float ) const;
		CVector3D operator / ( Float ) const;
	};
}



namespace Selene
{
	/**
		@brief �x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API CVector4D
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		CVector4D();
		CVector4D( const CVector3D &v );
		CVector4D( const CVector4D &v );
		CVector4D( Float fPx, Float fPy, Float fPz, Float fPw = 1.0f );

		void Add( CVector4D &In1, CVector4D &In2 );
		void Sub( CVector4D &In1, CVector4D &In2 );
		void Set( Float fPx, Float fPy, Float fPz );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector4D &In );

		void Normalize( void );
		void Cross( CVector4D &In1, CVector4D &In2 );
		void Reflect( CVector4D &In1, CVector4D &In2 );
		void TransformNormal( CVector4D &In1, CMatrix &In2 );
		void TransformCoord( CVector4D &In1, CMatrix &In2 );
		void TransformProjection( CVector4D &In1, CMatrix &In2 );

		void Normalize( CVector4D &In );
		void Cross( CVector4D &In );
		void Reflect( CVector4D &In );
		void TransformNormal( CMatrix &In );
		void TransformCoord( CMatrix &In );
		void TransformProjection( CMatrix &In );

		void RotationX( Sint32 Angle );
		void RotationY( Sint32 Angle );
		void RotationZ( Sint32 Angle );
		void RotationAxis( Sint32 Angle, CVector3D &Axis );
		void Scaling( Float sx, Float sy, Float sz );
		void Translation( Float px, Float py, Float pz );

		CVector4D& operator += ( const CVector4D& );
		CVector4D& operator -= ( const CVector4D& );
		CVector4D& operator *= ( Float );
		CVector4D& operator /= ( Float );

		CVector4D operator + () const;
		CVector4D operator - () const;

		CVector4D operator + ( const CVector4D& ) const;
		CVector4D operator - ( const CVector4D& ) const;
		CVector4D operator * ( Float ) const;
		CVector4D operator / ( Float ) const;
	};
}



namespace Selene
{
	struct SMatrix4x4
	{
		CVector4D x;
		CVector4D y;
		CVector4D z;
		CVector4D w;
	};

	/**
		@brief �s��N���X
	*/
	class SELENE_DLL_API CMatrix
	{
	private:
		Uint8 m_Data[sizeof(SMatrix4x4) + 16];
		SMatrix4x4 &Mtx;

	public:
		CVector4D &x;
		CVector4D &y;
		CVector4D &z;
		CVector4D &w;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix( CMatrix &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix( SMatrix4x4 &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix( CQuaternion &In );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CMatrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief �s��̒P�ʉ�
			@author �t���`
		*/
		void Identity( void );

		/**
			@brief �s��̓]�u��
			@author �t���`
			@param In	[in] �������s��
		*/
		void Transpose( CMatrix &In );

		/**
			@brief �s��̋t�s��
			@author �t���`
			@param In	[in] �������s��
		*/
		void Inverse( CMatrix &In );

		/**
			@brief �s��̍���
			@author �t���`
			@param In1		[in] �������s��P
			@param In2		[in] �������s��Q
		*/
		void Multiply( CMatrix &In1, CMatrix &In2 );

		/**
			@brief �s��̓]�u�s��
			@author �t���`
		*/
		void Transpose( void );

		/**
			@brief �s��̋t�s��
			@author �t���`
		*/
		void Inverse( void );

		/**
			@brief �s��̍���
			@author �t���`
			@param In	[in] �������s��
		*/
		void Multiply( CMatrix &In );

		/**
			@brief �w����]�p�x
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		void RotationX( Sint32 Angle );

		/**
			@brief �x����]�p�x
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		void RotationY( Sint32 Angle );

		/**
			@brief �y����]�p�x
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		void RotationZ( Sint32 Angle );

		/**
			@brief �y�w�x��]�s��𐶐�
			@author �t���`
			@param AngleX	[in] �w����]�p�x
			@param AngleY	[in] �x����]�p�x
			@param AngleZ	[in] �y����]�p�x
		*/
		void RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief �C�ӎ���]
			@author �t���`
			@param Angle	[in] �p�x
			@param Axis		[in] ��]��
		*/
		void RotationAxis( Sint32 Angle, CVector3D &Axis );

		/**
			@brief �g��k���s�񐶐�
			@author �t���`
			@param sx	[in] �w�����g�嗦
			@param sy	[in] �x�����g�嗦
			@param sz	[in] �y�����g�嗦
		*/
		void Scaling( Float sx, Float sy, Float sz );

		/**
			@brief �ړ��s�񐶐�
			@author �t���`
			@param px	[in] �w�ʒu
			@param py	[in] �x�ʒu
			@param pz	[in] �y�ʒu
		*/
		void Translation( Float px, Float py, Float pz );

		/**
			@brief �����ϊ��p�s�񐶐�
			@author �t���`
			@param Fov		[in] ��p
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
			@param Aspect	[in] �A�X�y�N�g��i���`��G���A�������`��G���A�c���j
		*/
		void Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief ���s���e�p�s�񐶐�
			@author �t���`
			@param Width	[in] ����
			@param Height	[in] �c��
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
		*/
		void Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief �C�ӓ_�����s��쐬
			@author �t���`
			@param Eye	[in] ���_
			@param At	[in] �����_
			@param Up	[in] �����
		*/
		void LookAt( CVector3D &Eye, CVector3D &At, CVector3D &Up );

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 & ();

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 & () const;

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 * ();

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		operator SMatrix4x4 * () const;

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix &operator = ( const CMatrix &In );	

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix &operator = ( const CQuaternion &In );

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix  operator * ( const CMatrix &In );	

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CMatrix &operator *= ( const CMatrix &In );	
	};
}


namespace Selene
{
	/**
		@brief �l�����N���X
	*/
	class SELENE_DLL_API CQuaternion
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		void Add( CQuaternion &In1, CQuaternion &In2 );
		void Sub( CQuaternion &In1, CQuaternion &In2 );
		void Mul( CQuaternion &In1, CQuaternion &In2 );
		void Lerp( CQuaternion &In0, CQuaternion &In1, Float fRate );
		void Slerp( CQuaternion &In0, CQuaternion &In1, Float fRate );

		void Add( CQuaternion &In );
		void Sub( CQuaternion &In );
		void Mul( CQuaternion &In );
		void Lerp( CQuaternion &In, Float fRate );
		void Slerp( CQuaternion &In, Float fRate );

		void Identity( void );
		Float LengthSq( void );
		Float Length( void );
		Float Dot( CQuaternion &In );
		void Conjugate( void );
	};
}



namespace Selene
{
	/**
		@brief �p������N���X
	*/
	class SELENE_DLL_API CStyle
	{
	private:
		CMatrix m_mStyle;												///< �p���p�s��
		CMatrix m_mStyleInverse;										///< �p���̋t�s��
		CMatrix m_mTransform;											///< �ϊ��s��
		CMatrix m_mTransformInverse;									///< �ϊ��s��̋t�s��
		CVector3D m_vUp;												///< ������x�N�g��
		CVector3D m_vRight;												///< �E�����x�N�g��
		CVector3D m_vFront;												///< �O�����x�N�g��
		CVector3D m_vPosition;											///< �ʒu�x�N�g��
		CVector3D m_vScale;												///< �g��k���x�N�g��

	public:
		CStyle();
		CStyle( const CStyle &Style );

		virtual void TransformReset( void );
		virtual void TransformUpdate( void );

		virtual void RotationX( Sint32 Rot );
		virtual void RotationY( Sint32 Rot );
		virtual void RotationZ( Sint32 Rot );
		virtual void Pitching( Sint32 Rot );
		virtual void Heading( Sint32 Rot );
		virtual void Rolling( Sint32 Rot );
		virtual void RotationQuaternion( CQuaternion &Quat );
		virtual void Translation( Float fPx, Float fPy, Float fPz );
		virtual void Scaling( Float fSx, Float fSy, Float fSz );
		virtual void LookAt( CVector3D &vEye, CVector3D &vAt, CVector3D &vUp );
		virtual void FromMatrix( CMatrix &Mat );
		virtual Sint32 GetAngleX( void );
		virtual Sint32 GetAngleY( void );
		virtual Sint32 GetAngleZ( void );
		virtual void SetPosition( CVector3D &Pos );
		virtual void SetFront( CVector3D &Vec );
		virtual void SetRight( CVector3D &Vec );
		virtual void SetUp( CVector3D &Vec );
		virtual void GetPosition( CVector3D &Pos );
		virtual void GetFront( CVector3D &Vec );
		virtual void GetRight( CVector3D &Vec );
		virtual void GetUp( CVector3D &Vec );
		virtual void GetStyle( CMatrix &Mat );
		virtual void GetStyleInverse( CMatrix &Mat );
		virtual void GetTransform( CMatrix &Mat );
		virtual void GetTransformInverse( CMatrix &Mat );

		virtual CStyle &operator = ( const CStyle &In );
	};
}



namespace Selene
{
namespace Math
{
	/**
		@brief sin�擾
		@author �t���`
		@param Angle	[in] 1��65536�Ƃ����p�x
		@return sin�l

		sin�l���擾���܂��B
	*/
	SELENE_DLL_API Float Sin( Sint32 Angle );

	/**
		@brief cos�擾
		@author �t���`
		@param Angle	[in] 1��65536�Ƃ����p�x
		@return cos�l

		cos�l���擾���܂��B
	*/
	SELENE_DLL_API Float Cos( Sint32 Angle );

	/**
		@brief atan2�擾
		@author �t���`
		@param Dx	[in] �w����
		@param Dy	[in] �x����
		@return X-Y�̐����p�x

		X,Y���狁�߂���atan2�̒l��Selene�̊p�x�P�ʂ�<BR>
		���킹���l�Ŏ擾���܂��B
	*/
	SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );
}

	/**
		@brief ��`�f�[�^
		@author �t���`
	*/
	template <typename Type>
	class CRect2D
	{
	public:
		Type x;					///< �w�n�_���W
		Type y;					///< �x�n�_���W
		Type w;					///< �w�T�C�Y
		Type h;					///< �x�T�C�Y

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRect2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w�n�_���W
			@param y		[in] �x�n�_���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
		*/
		CRect2D( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	/**
		@brief �Q�����̓_
		@author �t���`
	*/
	template <typename Type>
	class CPoint2D
	{
	public:
		Type x;					///< �w���W
		Type y;					///< �x���W

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPoint2D(){}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
		*/
		CPoint2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator + ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x + Pt.x, this->y + Py.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator - ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x - Pt.x, this->y - Py.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator * ( Type Mul )
		{
			return CPoint2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> operator / ( Type Div )
		{
			return CPoint2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator += ( CPoint2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator -= ( CPoint2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint2D<Type> Rotate( Sint32 Angle )
		{
			Float fSin = Math::Sin( Angle );
			Float fCos = Math::Cos( Angle );

			Float fPx = (fCos * toF(this->x)) - (fSin * toF(this->y));
			Float fPy = (fSin * toF(this->x)) + (fCos * toF(this->y));

			return CPoint2D<Type>( (Type)fPx, (Type)fPy );
		}
	};

	/**
		@brief �R�����̓_
	*/
	template <typename Type>
	struct CPoint3D
	{
		Type x;							///< �w�ʒu
		Type y;							///< �x�ʒu
		Type z;							///< �y�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPoint3D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
		*/
		CPoint3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator + ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x + Pt.x, this->y + Py.y, this->z + Py.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator - ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x - Pt.x, this->y - Py.y, this->z - Py.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator * ( Type Mul )
		{
			return CPoint3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> operator / ( Type Div )
		{
			return CPoint3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator += ( CPoint3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator -= ( CPoint3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		CPoint3D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			this->z /= Div;
			return *this;
		}
	};

	/**
		@brief �Q������̉~
		@author �t���`
	*/
	struct CCircle
	{
		CVector2D Center;				///< �~�̒��S
		Float Radius;					///< �~�̔��a

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CCircle()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param r		[in] ���a
		*/
		CCircle( Float x, Float y, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Radius = r;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CCircle( CVector2D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief �R������̋�
		@author �t���`
	*/
	struct CSphere
	{
		CVector3D Center;					///< ���̒��S
		Float Radius;							///< ���̔��a

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CSphere()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
			@param r		[in] ���a
		*/
		CSphere( Float x, Float y, Float z, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Center.z = z;
			this->Radius = r;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CSphere( CVector3D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief �Q�����̐���
		@author �t���`
	*/
	struct CLine2D
	{
		CVector2D Pt0;						///< �����n�_�ʒu
		CVector2D Pt1;						///< �����I�_�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0		[in] �����̒��_�P
			@param pt1		[in] �����̒��_�Q
		*/
		CLine2D( CVector2D &pt0, CVector2D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief �Q�����̑��p�`
		@author �t���`
	*/
	struct CPolygon2D
	{
		Uint32 Count;								///< �|�C���g�z��̃|�C���g��
		CVector2D *pPts;						///< �|���S����\�����߂̃|�C���g�z��̃|�C���^

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPolygon2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param Cnt		[in] ���_��
			@param pPt		[in] ���_�̔z��
		*/
		CPolygon2D( Uint32 Cnt, CVector2D *pPt )
		{
			this->Count = Cnt;
			this->pPts = pPt;
		}
	};

	/**
		@brief �R�����̐���
		@author �t���`
	*/
	struct CLine3D
	{
		CVector3D Pt0;						///< �����n�_�ʒu
		CVector3D Pt1;						///< �����I�_�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine3D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param z0		[in] �y���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
			@param z1		[in] �y���W
		*/
		CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt0.z = z0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
			this->Pt1.z = z1;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0	[in] �����̒��_�P
			@param pt1	[in] �����̒��_�Q
		*/
		CLine3D( CVector3D &pt0, CVector3D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief �R�����̕���
		@author �t���`
	*/
	struct CPlane
	{
		Float a;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W��
		Float b;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W��
		Float c;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W��
		Float d;							///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPlane()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param a	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W��
			@param b	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W��
			@param c	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W��
			@param d	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��
		*/
		CPlane( Float a, Float b, Float c, Float d )
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}

		/**
			@brief �@���f�[�^���琶��
			@author �t���`

			@param Pt		[in] ���ʏ��1�_
			@param vNormal	[in] ���ʂ̖@��
		*/
		void FromNormal( CVector3D &Pt, CVector3D &vNormal )
		{
			CVector3D vNrm;
			vNrm.Normalize( vNormal );
			a = vNrm.x;
			b = vNrm.y;
			c = vNrm.z;
			d = -Pt.Dot( vNrm );
		};

		/**
			@brief ���ʏ�̂R�_���琶��
			@author �t���`

			@param Pt0		[in] ���ʏ��1�_
			@param Pt1		[in] ���ʏ��1�_
			@param Pt2		[in] ���ʏ��1�_
		*/
		void FromPoint( CVector3D &vPt0, CVector3D &vPt1, CVector3D &vPt2 )
		{
			CVector3D vEdge0 = vPt1 - vPt0;
			CVector3D vEdge1 = vPt2 - vPt0;
			CVector3D vNormal;
			vNormal.Cross( vEdge0, vEdge1 );
			FromNormal( vPt0, vNormal );
		}

		/**
			@brief ����
			@author �t���`

			@param Pt	[in] �C�ӂ̓_

			���ʂƔC�ӂ̓_�̓��ς��Ƃ�܂��B
		*/
		Float Dot( CVector3D &Pt, Float w = 1.0f )
		{
			return (a * Pt.x) + (b * Pt.y) + (c * Pt.z) + (w * d);
		}
	};

	/**
		@brief �R������̔�
		@author �t���`
	*/
	struct CBox
	{
	public:
		CVector3D Points[8];	///< ���̊e�p��\�����_�f�[�^
		CPlane Planes[6];		///< ���̊e�ʂ�\���ʃf�[�^

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CBox()
		{
		}

		/**
			@brief ���_�f�[�^���畽�ʃf�[�^����
			@author �t���`
		*/
		void Update( void )
		{
			Planes[0].FromPoint( Points[0], Points[1], Points[2] );
			Planes[1].FromPoint( Points[6], Points[5], Points[4] );
			Planes[2].FromPoint( Points[5], Points[6], Points[2] );
			Planes[3].FromPoint( Points[7], Points[4], Points[0] );
			Planes[4].FromPoint( Points[3], Points[2], Points[6] );
			Planes[5].FromPoint( Points[4], Points[5], Points[1] );
		}
	};
}



namespace Selene
{
namespace Collision
{
	Bool Point_Point( CVector2D *pPt1, CVector2D *pPt2 );
	Bool Point_Line( CVector2D *pPt, CLine2D *pLine );
	Bool Point_Rect( CVector2D *pPt, CRect2D<Float> *pRect );
	Bool Point_Circle( CVector2D *pPt, CCircle *pCir );
	Bool Point_Polygon( CVector2D *pPt, CPolygon2D *pPoly );
	Bool Rect_Rect( CRect2D<Float> *pRect1, CRect2D<Float> *pRect2 );
	Bool Rect_Circle( CRect2D<Float> *pRect, CCircle *pCir );
	Bool Rect_Line( CRect2D<Float> *pRect, CLine2D *pLine );
	Bool Rect_Polygon( CRect2D<Float> *pRect, CPolygon2D *pPoly );
	Bool Circle_Circle( CCircle *pCir1, CCircle *pCir2 );
	Bool Circle_Line( CCircle *pCir, CLine2D *pLine );
	Bool Circle_Polygon( CCircle *pCir, CPolygon2D *pPoly );
	Bool Line_Line( CLine2D *pLine1, CLine2D *pLine2 );
	Bool Line_Polygon( CLine2D *pLine, CPolygon2D *pPoly );
	Bool Polygon_Polygon( CPolygon2D *pPoly1, CPolygon2D *pPoly2 );

	Bool Point_Point_3D( CVector3D *pPt1, CVector3D *pPt2 );
	Bool Point_Sphere_3D( CVector3D *pPt, CSphere *pSph );
	Bool Point_Line_3D( CVector3D *pPt, CLine3D *pLine );
	Bool Point_Plane_3D( CVector3D *pPt, CPlane *pPlane );
	Bool Point_Box_3D( CVector3D *pPt, CBox *pBox );
	Bool Sphere_Sphere_3D( CSphere *pSph1, CSphere *pSph2 );
	Bool Sphere_Line_3D( CSphere *pSph, CLine3D *pLine );
	Bool Sphere_Plane( CSphere *pSph, CPlane *pPlane );
	Bool Sphere_Box_3D( CSphere *pSph, CBox *pBox );
	Bool Line_Plane_3D( CLine3D *pLine, CPlane *pPlane, CVector3D *pPoints, CVector3D *pPos );
	Bool Line_Box_3D( CLine3D *pLine, CBox *pBox );
	Bool Line_Triangle_3D( CLine3D* pLine, CVector3D Points[], Float *pT, Float *pU, Float *pV );
	Bool Plane_Plane_3D( CPlane *pPlane1, CPlane *pPlane2, CVector3D Points1[], CVector3D Points2[] );
	Bool Box_Box_3D( CBox &Box1, CBox &Box2 );

	void CreateBox( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix );
	void CreateBoxProjection( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix );

	Bool EdgeIntersectsQuad( CVector3D* pEdges, CVector3D* pFacePoints, CPlane* pPlane, CVector3D *pHitPos );

	Bool LineIntersectPolygon( CVector3D *pPtTbl[], CPlane &Plane, CVector3D *pPlanePoints[], Uint32 Count );
	Bool LineIntersectPlane( CVector3D &vIntersection, CPlane &Plane, CVector3D &Pt0, CVector3D &Pt1 );
}
}



namespace Selene
{
	/**
		@brief ���������N���X
		@author �t���`
	*/
	class SELENE_DLL_API CRandom
	{
		enum { N = 624UL };

	private:
		Uint32 MersenneTwister[N];			///< ���������p���[�N
		Sint32 MersenneTwisterCount;		///< ���������p���[�N

	private:
		/**
			@brief �[����������
			@author �t���`
			@return �����l

			32Bit�����̋[�������𐶐����܂��B
		*/
		virtual Uint32 GenerateInt32( void );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRandom();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRandom( Uint32 Param );

		/**
			@brief �����p��ݒ�
			@author �t���`
			@param Param	[in] �V�[�h�l

			���������̎��ݒ肵�܂��B
		*/
		virtual void Seed( Uint32 Param );

		/**
			@brief 32Bit���������擾
			@author �t���`
			@return �����l

			32Bit�����̗����l���擾���܂��B
		*/
		virtual Uint32 GetInt32( void );

		/**
			@brief 64Bit���������擾
			@author �t���`
			@return �����l

			64Bit�����̗����l���擾���܂��B
		*/
		virtual Uint64 GetInt64( void );

		/**
			@brief 32Bit�������������擾
			@author �t���`
			@return �����l

			32Bit���������̗����l���擾���܂��B
		*/
		virtual Float GetFloat32( void );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l

			�w��͈͓��̐����������擾���܂��B
		*/
		virtual Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l

			�w��͈͓��̕��������������擾���܂��B
		*/
		virtual Float GetFloat( Float Min, Float Max );
	};
}



namespace Selene
{
	/**
		@brief �f�o�C�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IDevice
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
		virtual Uint32 Release( void )												= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)												= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�N���A
			@author �t���`
			@param Color	[in] �N���A�Ɏg���F
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�����_�����O�^�[�Q�b�g���w�肳�ꂽ�F�ŃN���A�[���܂��B
		*/
		virtual Bool Clear( CColor Color = 0x00000000 )								= 0;

		/**
			@brief �[�x�o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�[�x�o�b�t�@���N���A���܂��B<BR>
			�[�x�o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearDepth( void )												= 0;

		/**
			@brief �X�e���V���o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�X�e���V���o�b�t�@���N���A���܂��B<BR>
			�X�e���V���o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearStencil( void )											= 0;

		/**
			@brief �[�x�X�e���V���o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�[�x�X�e���V���o�b�t�@���N���A���܂��B<BR>
			�[�x�X�e���V���o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearDepthStencil( void )										= 0;

		/**
			@brief �[���R���\�[����ʂɕ������`��
			@author �t���`
			@param pStr	[in] �����t������(printf�Ɠ�������)

			�R���\�[����printf()�Ǝ���������`�揈���ł��B<BR>
			�f�o�b�O�p�ɉ�ʂɕ�����`�悵�Ă��������ꍇ���ɗ��p���Ă��������B
		*/
		virtual void Printf( const wchar_t *pStr, ... )								= 0;

		/**
			@brief �[���R���\�[����ʂ��N���A
			@author �t���`

			�[���R���\�[����ʂ��N���A���܂��B
		*/
		virtual void Cls( void )													= 0;

		/**
			@brief �`��̈�V�U�����O
			@author �t���`
			@param IsEnable		[in] �V�U�����O��L���ɂ��邩�ۂ�
			@param Rect			[in] �`��̈�

			�w�肵���`��̈���ɂ��������_�����O����Ȃ��悤�ɂȂ�܂��B<BR>
			�r���[�|�[�g�ɂ͉e����^���܂���B
		*/
		virtual void SetScissor( Bool IsEnable, CRect2D<Sint32> Rect )			= 0;

		/**
			@brief IRender�C���^�[�t�F�C�X�擾
			@author �t���`
			@return IRender�C���^�[�t�F�C�X

			IRender�C���^�[�t�F�C�X���擾���܂��B<BR>
			��ʂւ̃����_�����O�����̑S�Ă����̃C���^�[�t�F�C�X��<BR>
			��čs����悤�ɂȂ��Ă��܂��B<BR>
			���̃C���^�[�t�F�C�X��1��IDevice�ɑ΂���1�������݂��܂���B<BR>
			�܂��s�v�ɂȂ���IRender�C���^�[�t�F�C�X�͕K��Release()���ĉ������B
		*/
		virtual IRender *CreateRender( void )										= 0;
	};
}



namespace Selene
{
	#define GRAPHIC_CARD_DEFAULT_NO		(0x00000000)					///< �f�t�H���g�̃r�f�I�J�[�h
	#define GRAPHIC_CARD_NV_PERF_HUD	(0xFFFFFFFF)					///< NVPerfHUD��p�̃r�f�I�J�[�h

	/**
		@brief ���_�V�F�[�_�[�o�[�W����
		@author �t���`
	*/
	enum eVertexShaderVersion
	{
		VERTEXSHADER_VERSION_2_0,			///< Version 2.0
		VERTEXSHADER_VERSION_3_0,			///< Version 3.0
	};

	/**
		@brief �T�[�t�F�C�X�t�H�[�}�b�g��`
		@author �t���`
	*/
	enum eSurfaceFormat
	{
		FORMAT_INVALID,						///< ����

		FORMAT_FROM_FILE,					///< �t�@�C������擾

		FORMAT_DEPTH16,						///< 16Bit�[�x�o�b�t�@
		FORMAT_DEPTH32,						///< 32Bit�[�x�o�b�t�@
		FORMAT_DEPTHSTENCIL,				///< �X�e���V���[�x�o�b�t�@

		FORMAT_DXT1,						///< DXT1���k�t�H�[�}�b�g�e�N�X�`��
		FORMAT_DXT3,						///< DXT3���k�t�H�[�}�b�g�e�N�X�`��
		FORMAT_DXT5,						///< DXT5���k�t�H�[�}�b�g�e�N�X�`��

		FORMAT_BACKBUFFER,					///< �o�b�N�o�b�t�@�ɏ���
		FORMAT_TARGET16,					///< 16Bit�����_�����O�^�[�Q�b�g
		FORMAT_TARGET32,					///< 32Bit�����_�����O�^�[�Q�b�g
		FORMAT_TARGET_HDR,					///< HDR�p�����_�����O�^�[�Q�b�g
		FORMAT_TARGET_SHADOWMAP,			///< �V���h�E�}�b�v�p�����_�����O�^�[�Q�b�g

		FORMAT_ALPHAONLY,					///< �A���t�@�p�e�N�X�`��

		FORMAT_TEXTURE32,					///< 32Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		FORMAT_TEXTURE16,					///< 16Bit�e�N�X�`���t�H�[�}�b�g�ɏ���

		FORMAT_TEXTURE_2D,					///< 2D�p�ėp�e�N�X�`���t�H�[�}�b�g
		FORMAT_TEXTURE_3D,					///< 3D�p�ėp�e�N�X�`���t�H�[�}�b�g
	};

	/**
		@brief �r�f�I�J�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IGraphicCard
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
		virtual Uint32 Release( void )																	= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																	= 0;

		/**
			@brief 16Bit�J���[���[�h���g�p
			@author �t���`

			�t���X�N���[�����̉�ʃJ���[��32Bit�ł͂Ȃ�16Bit�ɂ��܂��B<BR>
			�t�B�����[�g�̌��������ő��x�̌��オ�]�߂܂����A<BR>
			�}�b�n�o���h�Ȃǂ̉掿�I�Ȗ����o�܂��B
		*/
		virtual void EnableHighlColorScreen( void )														= 0;

		/**
			@brief �s�N�Z���V�F�[�_�[���T�|�[�g����Ă��邩�擾
			@author �t���`
			@param Major	[in] ���W���[�o�[�W����
			@param Minor	[in] �}�C�i�[�o�[�W����

			���݂̃f�o�C�X�Ŏw�肵���s�N�Z���V�F�[�_�[���T�|�[�g<BR>
			���Ă��邩�ǂ������擾���܂��B
		*/
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor )								= 0;

		/**
			@brief ��ʉ𑜓x���擾
			@author �t���`
			@param IsFullColor	[in] �t���J���[(32Bit)�̉�ʉ𑜓x���ۂ�
			@return ��ʉ𑜓x��

			�g�p�\�ȉ�ʉ𑜓x�̐����擾�ł��܂��B<BR>
			IsFullColor�t���O�ɉ����āA16Bit/32Bit�J���[�̉�ʉ𑜓x�����擾�o���܂��B
		*/
		virtual Sint32 GetScreenTypeCount( Bool IsFullColor )											= 0;

		/**
			@brief ��ʉ𑜓x
			@author �t���`
			@param IsFullColor	[in] �t���J���[(32Bit)�̉�ʉ𑜓x���ۂ�
			@param No			[in] ��ʉ𑜓x�̃C���f�b�N�X�i�ő吔��GetScreenTypeCount()�Ŏ擾�j
			@param Width		[out] ��ʉ����i�[��
			@param Height		[out] ��ʏc���i�[��

			�g�p�\�ȉ�ʉ𑜓x���擾���܂��B
		*/
		virtual void GetScreenType( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height )		= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾
			@author �t���`
			@return �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y��

			�g�p�\�ȃ����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�̐����擾�ł��܂��B
		*/
		virtual Sint32 CreateRenderTargetTextureSizeCount( void )										= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y
			@author �t���`
			@param No			[in] �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�̃C���f�b�N�X�i�ő吔��CreateRenderTargetTextureSizeCount()�Ŏ擾�j
			@param pWidth		[out] ��ʉ����i�[��
			@param pHeight		[out] ��ʏc���i�[��

			�g�p�\�ȃ����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾���܂��B
		*/
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight )		= 0;

		/**
			@brief �O���t�B�b�N�J�[�h���̎擾
			@author �t���`
			@param pName		[out] ���̊i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̖��̂��擾���܂��B
		*/
		virtual void GetGraphicCardName( wchar_t *pName, Uint32 NameSize )									= 0;

		/**
			@brief �O���t�B�b�N�J�[�h�̃h���C�o�[�擾
			@author �t���`
			@param pName		[out] �h���C�o�[�i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̃h���C�o�[���擾���܂��B
		*/
		virtual void GetGraphicCardDriver( wchar_t *pName, Uint32 NameSize )								= 0;

		/**
			@brief �O���t�B�b�N�J�[�h�̃o�[�W�����擾
			@author �t���`
			@param pName		[out] �o�[�W�����i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̃o�[�W�������擾���܂��B
		*/
		virtual void GetGraphicCardVersion( wchar_t *pName, Uint32 NameSize )								= 0;

		/**
			@brief IDevice�C���^�[�t�F�C�X����
			@author �t���`
			@return IDevice�C���^�[�t�F�C�X

			�O���t�B�b�N�J�[�h��̃f�o�C�X����p��IDevice�C���^�[�t�F�C�X���擾���܂��B<BR>
			IDevice�C���^�[�t�F�C�X�͂P��IGraphicCard�ɑ΂��ĂP�������݂��܂���B
		*/
		virtual IDevice *CreateDevice( void )															= 0;
	};
}



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



namespace Selene
{
	/**
		@brief �V�[���J��������p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���̃J�����𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISceneCamera
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																					= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																					= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																					= 0;

		/**
			@brief ���[���h���X�N���[�����W�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���X�N���[�����W�ւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &WorldToScreen( void ) const																= 0;

		/**
			@brief ���[���h���r���[�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���J������Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &WorldToView( void ) const																= 0;

		/**
			@brief �X�N���[�������[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�X�N���[�����W���烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &ScreenToWorld( void ) const																= 0;

		/**
			@brief �r���[�����[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�J������Ԃ��烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const CMatrix &ViewToWorld( void ) const																= 0;

		/**
			@brief �j�A�N���b�v�l�擾
			@author �t���`

			@return �j�A�N���b�v�l

			�j�A�N���b�v�l���擾���܂��B
		*/
		virtual Float GetNearClip( void ) const																			= 0;

		/**
			@brief �t�@�[�N���b�v�l�擾
			@author �t���`

			@return �t�@�[�N���b�v�l

			�t�@�[�N���b�v�l���擾���܂��B
		*/
		virtual Float GetFarClip( void ) const																			= 0;

		/**
			@brief �v���W�F�N�V�����s��X�V
			@author �t���`

			@param fNearClip	[in] �j�A�N���b�v�l
			@param fFarClip		[in] �t�@�[�N���b�v�l
			@param FovAngle		[in] ��p�i1��65536�Ƃ����p�x�j
			@param Width		[in] �\������
			@param Height		[in] �\���c��

			�v���W�F�N�V�����s����X�V���܂��B<BR>
			�J�������g�p����ꍇ�ɂ͕K�����̊֐��Ńv���W�F�N�V�������쐬���ĉ������B<BR>
			�܂�FovAngle��0���w�肷��ƕ��s���e�ɂȂ�܂��B
		*/
		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )	= 0;

		/**
			@brief �J�����f�[�^������
			@author �t���`

			�J�����f�[�^�����������܂��B<BR>
			���W(0,0,0)����Z��+��������������ԂɂȂ�܂��B
		*/
		virtual void Reset( void )																						= 0;

		/**
			@brief �J�����f�[�^�X�V
			@author �t���`

			�J�����̃f�[�^���X�V���܂��B<BR>
			�e��s���o�E���f�B���O�{�b�N�X�Ȃǂ�<BR>
			���̊֐����Ăяo�����Ƃō쐬����܂��B
		*/
		virtual void Update( void )																						= 0;

		/**
			@brief �J������ϊ�
			@author �t���`

			@param Style	[in] �J�����ϊ��pCStyle

			Ctyle�f�[�^�Œ�`���ꂽ�ϊ�������<BR>
			�J�����ɓK�p���܂��B<BR>
			�J�����Ŏg�p�����͈̂ړ�/��]�ɂȂ�܂��B
		*/
		virtual void SetTransform( CStyle &Style )																		= 0;
	};
}



namespace Selene
{
	/**
		@brief �V�[�������_�����O���[�h
		@author �t���`
	*/
	enum eSceneMode
	{
		SCENE_MODE_NOT_MANAGED,			///< �����_�����O�����s��Ȃ�
		SCENE_MODE_MANAGED,				///< �����Ő[�x�o�b�t�@�⃌���_�����O�^�[�Q�b�g���Ǘ�����
		SCENE_MODE_1PASS_DOF,			///< 1PASS�Ŕ�ʊE�[�x�������s���i�A���t�@�u�����f�B���O�͂ł��Ȃ��Ȃ�܂�
		SCENE_MODE_2PASS_DOF,			///< 2PASS�Ŕ�ʊE�[�x�������s���i�A���t�@�u�����f�B���O���ł��܂�
		SCENE_MODE_1PASS_DOF_HIGH,		///< 1PASS�ō��掿��ʊE�[�x�������s���i�A���t�@�u�����f�B���O�͂ł��Ȃ��Ȃ�܂�
		SCENE_MODE_2PASS_DOF_HIGH,		///< 2PASS�ō��掿��ʊE�[�x�������s���i�A���t�@�u�����f�B���O���ł��܂�
	};

	/**
		@brief �V�[�������_�����O���[�h
		@author �t���`
	*/
	enum eSceneModeOption
	{
		SCENE_MODE_OPTION_NO,					///< �I�v�V�����Ȃ�
		SCENE_MODE_OPTION_HDR,					///< HDR�����_�����O���s���܂��i�A���t�@�u�����f�B���O�E�A���t�@�e�X�g�͂ł��Ȃ��Ȃ�܂�
		SCENE_MODE_OPTION_EDGE,					///< �G�b�W�����_�����O���s���܂�
		SCENE_MODE_OPTION_SHADOW,				///< �e�̃����_�����O���s���܂�
	};

	/**
		@brief �V�[���Ǘ��p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISceneManager
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																								= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																								= 0;

		/**
			@brief �V�[���J�����擾
			@author �t���`
			@return �J�����f�[�^

			�V�[���Ɋ֘A�t����ꂽ�J�������擾���܂��B
		*/
		virtual ISceneCamera *GetSceneCamera( void )																				= 0;

		/**
			@brief �V�[��������
			@author �t���`

			�V�[���̃��C�g��t�H�O�Ȃǂ̃f�[�^�����Z�b�g���܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void Reset( void )																									= 0;

		/**
			@brief �V�[���J�n
			@author �t���`
			@param IsSort	[in] �V�[�����̃I�u�W�F�N�g���\�[�g���邩�ǂ���

			�V�[���Ǘ����J�n���܂��B<BR>
			���̎��_�ŃJ�����̃f�[�^���m�肵�܂��̂�<BR>
			���̊֐����Ăяo�������Ƃ̃J�����̍X�V�͑S�Ė����ł��B
		*/
		virtual void Begin( Bool IsSort )																							= 0;

		/**
			@brief �V�[���I��
			@author �t���`

			�V�[���̊Ǘ����������܂��B
		*/
		virtual void End( void )																									= 0;

		/**
			@brief �V�[�������_�����O
			@author �t���`
			@param IsDrawBuffer	[in] �����p�o�b�t�@�̕\���i�f�o�b�O�p�j

			�V�[���̊Ǘ��ō\�z���ꂽ�V�[���������_�����O���܂��B<BR>
			���̊֐����R�[�������i�K�œ����ŕ`�揈�����J�n����܂��B<BR>
			�K��IRender::Begin()�`IRender::End()�ԂŌĂяo���Ă��������B
		*/
		virtual void Rendering( Bool IsDrawBuffer = false )																			= 0;

		/**
			@brief �V���h�E�p�J�����ݒ�
			@author �t���`
			@param vPosition	[in] �J�����ʒu
			@param vTarget		[in] �J���������_
			@param Fov			[in] ��p�i1��65536�Ƃ����p�x�j
			@param fNear		[in] �߃N���b�v��
			@param fFar			[in] ���N���b�v��

			�V���h�E�p�̃J�����f�[�^��ݒ肵�܂��B
		*/
		virtual void SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias )	= 0;

		/**
			@brief �t�H�OON/OFF
			@author �t���`
			@param Enable	[in] �t�H�O��K�p����ꍇON

			�V�[���ɓK�p�����t�H�O��ON/OFF���܂��B
		*/
		virtual void SetFogEnable( Bool Enable )																					= 0;

		/**
			@brief �t�H�O���ݒ�
			@author �t���`

			@param fNear	[in] �t�H�O�J�nZ�i����Z���O�̓t�H�O�ɉe������Ȃ��j
			@param fFar		[in] �t�H�O�I��Z�i����Z����͊��S��Color�̐F�ɂȂ�j
			@param Color	[in] �t�H�O�̐F

			�V�[���ɓK�p�����t�H�O�̃p�����[�^�[��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetFog( Float fNear, Float fFar, CColor Color )																= 0;

		/**
			@brief ��ʊE�[�x�p�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
			@author �t���`

			@param fForcusZ	[in] �t�H�[�J�X�̂y�i�J������j
			@param fPower	[in] ��ʊE�[�x���x

			��ʊE�[�x�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
		*/
		virtual void SetDepthOfFieldForcus( Float fForcusZ, Float fPower )															= 0;

		/**
			@brief �A���r�G���g���C�g�ݒ�
			@author �t���`
			@param vColorSky	[in] �V�[�����̓V���̊����̐F
			@param vColorEarth	[in] �V�[�����̒n�\�̊����̐F

			�V�[���̊�����ݒ肵�܂��B<BR>
			�������C�e�B���O���s�����߂ɁA�V���ƒn�\�̐F��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth )												= 0;

		/**
			@brief �f�B���N�V�������C�g�ݒ�
			@author �t���`
			@param vDirect	[in] �V�[�����̕��s�����̕���
			@param vColor	[in] �V�[�����̕��s�����̐F

			�V�[���ɑ債��1�������s���������蓖�Ă邱�Ƃ��ł��܂��B<BR>
			���z�̂悤�ɗy�������ɑ��݂��A�I�u�W�F�N�g�̈ʒu�ɂ����<BR>
			���̕������ς��Ȃ��悤�ȃ��C�g�Ɍ����Ă��܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetDirectionLight( CVector3D &vDirect, CVector3D &vColor )														= 0;

		/**
			@brief �|�C���g���C�g�ǉ�
			@author �t���`
			@param vPosition	[in] �V�[�����̓_�����̈ʒu
			@param vColor		[in] �V�[�����̓_�����̐F
			@param fDistance	[in] �V�[���̓_�����̉e������

			�V�[���ɑ΂��ē_������ǉ����܂�<BR>
			�ő��32�̃��C�g��ݒ�ł��A���̂����ł��I�u�W�F�N�g�ɋ߂�<BR>
			4�̃��C�g���I�u�W�F�N�g�ɓK�p����܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance )										= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̃T�C�Y��ݒ�
			@author �t���`
			@param Size		[in] �T�C�Y

			�V�[���̃����_�����O�^�[�Q�b�g�̃T�C�Y���w�肵�܂��B<BR>
			eSceneMode��SCENE_MODE_NORMAL�ȊO�̏ꍇ�Ɏg����e��<BR>
			�o�b�t�@�̃T�C�Y�Ɋ֌W���܂��B
		*/
		virtual CPoint2D<Uint32> SetRenderTargetSize( CPoint2D<Uint32> Size )														= 0;

		/**
			@brief �����_�����O���N�G�X�g���擾
			@author �t���`
			@return �����_�����O���N�G�X�g��

			�V�[���Ƀ��N�G�X�g�����_�����O�����擾���܂��B
		*/
		virtual Uint32 GetRenderingRequestCount( void )																				= 0;

		/**
			@brief �����_�����O���擾
			@author �t���`
			@return �����_�����O��

			�V�[���Ŏ��s���ꂽ�����_�����O�����擾���܂��B<BR>
			2Pass�n�̏��������J�E���g�����̂ŁA<BR>
			���N�G�X�g���ȏ�̒l�ɂȂ邱�Ƃ�����܂��B
		*/
		virtual Uint32 GetRenderingCount( void )																					= 0;

		/**
			@brief �����_�����O�s�N�Z�����擾
			@author �t���`
			@return �����_�����O�s�N�Z����

			�����_�����O�������f���̃����_�����O�s�N�Z�������擾���܂��B<BR>
			�T�|�[�g����Ă��Ȃ��r�f�I�J�[�h�̏ꍇ��0xFFFFFFFF���Ԃ�܂��B
		*/
		virtual Uint32 GetOcculusion( Uint32 Index )																				= 0;
	};
}



namespace Selene
{
	/**
		@brief �e�N�X�`���X�e�[�W��`
		@author �t���`

		�e�N�X�`���X�e�[�W�Ɋւ��Ă̒�`�ł��B<BR>
		3D�I�u�W�F�N�g�Ɋւ��Ă͊�{�I�ɃV�F�[�_�[����<BR>
		UV���v�Z����悤�ɂȂ��Ă���̂ŁA<BR>
		���_�f�[�^�Ƃ��ĕێ�����UV�̓J���[�}�b�v�ƃ��C�g�}�b�v�����ł��B
	*/
	enum
	{
		TEXTURE_STAGE_00			= 0,	///< �e�N�X�`���X�e�[�W�O
		TEXTURE_STAGE_01,					///< �e�N�X�`���X�e�[�W�P
		TEXTURE_STAGE_02,					///< �e�N�X�`���X�e�[�W�Q
		TEXTURE_STAGE_03,					///< �e�N�X�`���X�e�[�W�R
		TEXTURE_STAGE_04,					///< �e�N�X�`���X�e�[�W�S
		TEXTURE_STAGE_05,					///< �e�N�X�`���X�e�[�W�T
		TEXTURE_STAGE_06,					///< �e�N�X�`���X�e�[�W�U
		TEXTURE_STAGE_07,					///< �e�N�X�`���X�e�[�W�V
		TEXTURE_STAGE_MAX,					///< �e�N�X�`���X�e�[�W�ő吔

		MESH_TEXTURE_COLORMAP		= 0,	///< ���b�V���p�J���[�}�b�v
		MESH_TEXTURE_LIGHTMAP,				///< ���C�g�}�b�v�i���ݎg���Ă��܂���
		MESH_TEXTURE_NORMALMAP,				///< �o���vor�����}�b�v�p�@���}�b�v
		MESH_TEXTURE_SHADOWMAP,				///< �V���h�E�}�b�v
		MESH_TEXTURE_MAX,					///< 3D���f���pUV��
	};

	/**
		@brief �}���`�e�N�X�`�����Z�^�C�v
		@author �t���`

		�}���`�e�N�X�`���g�p���̃X�e�[�W���̉��Z���@���`���܂��B
	*/
	enum eTextureOperationType
	{
		TEXTURE_OP_NONE,				///< �ȉ��X�e�[�W����
		TEXTURE_OP_MUL,					///< Color = [���ʃX�e�[�W]�~[�e�N�X�`��]
		TEXTURE_OP_ADD,					///< Color = [���ʃX�e�[�W]�{[�e�N�X�`��]
		TEXTURE_OP_SUB,					///< Color = [���ʃX�e�[�W]�|[�e�N�X�`��]
	};

	/**
		@brief ���_��`
		@author �t���`

		���_��`�N���X�̍쐬���Ɏw�肷��t���O�ł��B<BR>
		�Ȃ� VERTEX_ELEMENT_PRIMITIVE�AVERTEX_ELEMENT_SPRITE�AVERTEX_ELEMENT_3DBASE ��<BR>
		�Ɨ����Ă���r���ł��B
	*/
	enum eVertexElement
	{
		VERTEX_ELEMENT_PRIMITIVE	= 1 << 0,			///< �ʒu�ƐF�������܂ލł��P����2D�p���_
		VERTEX_ELEMENT_SPRITE		= 1 << 1,			///< �ʒu�ƐF�ƃe�N�X�`��UV���܂�2D�p���_
		VERTEX_ELEMENT_3DBASE		= 1 << 2,			///< �ʒu�ƐF���܂ނ����Ƃ��P����3D���_
		VERTEX_ELEMENT_3DTEXTURE	= 1 << 3,			///< �e�N�X�`��UV���܂ފ�{�I��3D�p���_
		VERTEX_ELEMENT_3DLIGHT		= 1 << 4,			///< ���C�e�B���O�Ɋւ���@�����܂�3D���_
		VERTEX_ELEMENT_3DBUMP		= 1 << 5,			///< �o���v�}�b�v�Ɋւ���ڐ����܂�3D���_
		VERTEX_ELEMENT_3DANIMATION	= 1 << 6,			///< �X�L�j���O�Ɋւ���{�[���̃C���f�b�N�X���E�F�C�g���܂�3D���_
	};

	/**
		@brief �`��^�C�v��`
		@author �t���`

		�e��`��^�C�v�Ɋւ��Ă̒�`�ł��B
	*/
	enum eDrawType
	{
		DRAW_TYPE_NORMAL,					///< �ʏ�`��
		DRAW_TYPE_BLEND,					///< �������`��
		DRAW_TYPE_ADD,						///< ���Z�`��
		DRAW_TYPE_ADD_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB,						///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_MULTIPLE,					///< ��Z�`��
		DRAW_TYPE_SCREEN,					///< �X�N���[���`��
	};

	/**
		@brief �J�����O�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eCullType
	{
		CULL_FRONT,							///< �\�̏ꍇ�̂ݕ`��
		CULL_BACK,							///< ���̏ꍇ�̂ݕ`��
		CULL_NONE,							///< ���\���ʕ`��
	};

	/**
		@brief �J�����O�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eTextureFilterType
	{
		TEXTURE_FILTER_DISABLE,				///< �t�B���^�����O����
		TEXTURE_FILTER_BILINEAR,			///< �o�C���j�A�t�B���^�����O
		TEXTURE_FILTER_ANISOTROPY_LOW,		///< �ٕ����t�B���^�����O/��掿
		TEXTURE_FILTER_ANISOTROPY_HIGH,		///< �ٕ����t�B���^�����O/���掿
	};

	/**
		@brief �e�N�X�`���T���v�����O���@
		@author �t���`

		0.0�`1.0�ȊO�͈̔͂��w�肵���ꍇ�̋����Ɋւ��Ă̒�`�ł��B<BR>
		Selene�ł͂Q�̗ݏ�ȊO�̃T�C�Y�̃e�N�X�`�����h���C�o��<BR>
		�Ή����Ă���΍쐬�E���p���鎖���\�ł��B<BR>
		�������Q�̗ݏ�ȊO�̃T�C�Y�̃e�N�X�`���𗘗p����ꍇ�́A<BR>
		TEXTURE_ADDRESS_CLAMP ���w�肵�Ă��Ȃ���΂Ȃ�܂���B
	*/
	enum eTextureAddressType
	{
		TEXTURE_ADDRESS_REPEAT,				///< UV���e�N�X�`���͈̔͊O�̎��A�J��Ԃ��܂��B
		TEXTURE_ADDRESS_CLAMP,				///< UV���e�N�X�`���͈̔͊O�̎��A(0�A�e�N�X�`���T�C�Y�j�ɐ������܂��B
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̊�{���_�f�[�^�ł��B<BR>
		���IPointPrimitive2D/ILinePrimitive2D<BR>
		�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_PRIMITIVE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2D
	{
		CVector4D Pos;		///< �ʒu
		CColor Col;			///< ���_�F
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̃e�N�X�`��UV�t�����_�f�[�^�ł��B<BR>
		���IPrimitive2D/ISprite2D/IFontSprite2D<BR>
		�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_SPRITE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2DTex
	{
		CVector4D Pos;		///< �ʒu
		CColor Col;			///< ���_�F
		CVector2D Tex;		///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̊�{���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_BASE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂P�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DBase
	{
		CVector3D Pos;		///< �ʒu
		CColor Col;			///< ���_�F
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃e�N�X�`��UV�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DTEXTURE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂P�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DTexture
	{
		CVector2D TexColor;		///< �e�N�X�`��UV
		CVector2D TexLight;		///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃��C�e�B���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DLIGHT�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂Q�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DLight
	{
		CVector3D Norm;		///< �@��
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃o���v�}�b�s���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DBUMP�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂R�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DBump
	{
		CVector3D Tangent;	///< �ڐ�
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃X�L�j���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DANIMATION�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂S�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B<BR>
		�P�̒��_�ɂ��Q�̃{�[���̌v�Z���s���܂��B
	*/
	struct SVertex3DAnimation
	{
		Float Weight;		///< �E�F�C�g�i�P�Ԗڂ̃E�F�C�g�������w��A�Q�Ԗڂ̓V�F�[�_�[����1.0-Weight�ŎZ�o�j
		Uint8 Index[4];		///< �{�[���C���f�b�N�X
	};

	/**
		@brief �e�N�X�`�������p�R���t�B�O
		@author �t���`

		�e�N�X�`���������ɎQ�Ƃ����<BR>
		�쐬�p�p�����[�^�[����`�����N���X�ł��B
	*/
	class CTextureConfig
	{
	private:
		CColor m_KeyColor;			///< �J���[�L�[�̐F
		eSurfaceFormat m_Format;	///< �T�[�t�F�C�X�t�H�[�}�b�g

	public:
		/**
			@brief �J���[�L�[�i�����F�j�ݒ�
			@author �t���`
			@param Col	[in] �J���[�L�[�i�����F�j�Ɏg���F<BR>0x00000000�̎��J���[�L�[�i�����F�jOFF

			�e�N�X�`����ǂݍ��񂾍ۂɎw�肵���F�̃A���t�@��0�ɂ��A<BR>
			�J���[�L�[�������s�����悤�ɂ��̃s�N�Z����`��<BR>
			����Ȃ��悤�ɂ��܂��B
		*/
		void SetColorKey( CColor Col )
		{
			m_KeyColor = Col;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g�ݒ�
			@author �t���`
			@param Fmt	[in] �T�[�t�F�C�X�t�H�[�}�b�g

			�e�N�X�`���ǂݍ��ݎ��̃T�[�t�F�C�X�t�H�[�}�b�g��ݒ肵�܂��B<BR>
			�����ȃt�H�[�}�b�g���w�肵���ꍇ�A�쐬�͎��s���܂��B
		*/
		void SetFormat( eSurfaceFormat Fmt )
		{
			m_Format = Fmt;
		}

		/**
			@brief �J���[�L�[���擾
			@author �t���`
			@retval	0		�J���[�L�[�������s��Ȃ�
			@retval	0�ȊO	���̐F���J���[�L�[�Ƃ���
		*/
		CColor GetColorKey( void )
		{
			return m_KeyColor;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g���擾���܂�
			@author �t���`
			@return �T�[�t�F�C�X�t�H�[�}�b�g
		*/
		eSurfaceFormat GetFormat( void )
		{
			return m_Format;
		}
	};

	/**
		@brief �����_���[�C���^�[�t�F�C�X
		@author �t���`

		��ʂɑ΂���S�Ă̕`�揈�����Ǘ����܂��B<BR>
		�`��p�̊e��N���X���S�Ă��̃N���X����擾���܂�<BR>
		�܂����̃C���^�[�t�F�C�X��1��IDevice�C���^�[�t�F�C�X�ɑ΂���1�����쐬����܂���B
	*/
	class IRender
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
		virtual Uint32 Release( void )																																					= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																																					= 0;

		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param Stage	[in] �ݒ肷��X�e�[�W�i�O�`�V�j
			@param pTex		[in] �ݒ肷��e�N�X�`���iNULL�Ŗ������j
			@retval false	���s
			@retval true	����

			�e�N�X�`���������_���[�ɐݒ肵�܂��B<BR>
			��x�ݒ肳�ꂽ�e�N�X�`����NULL��ݒ肷��܂�<BR>
			�L���ɂȂ��Ă��܂��B
		*/
		virtual Bool SetTexture( Uint32 Stage, ITexture *pTex )																															= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂��܂��B
		*/
		virtual Bool ResetRenderTarget( void )																																			= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
			CreateRenderTarget()�Ő������ꂽ�e�N�X�`���ȊO�͎��s���܂��B
		*/
		virtual Bool SetRenderTarget( ITexture *pTexture )																																= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ɐݒ�
			@author �t���`
			@retval true	����
			@retval false	���s

			�T�[�t�F�C�X�������_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
			�����_�����O�^�[�Q�b�g�Ƃ��Đ������ꂽ�T�[�t�F�C�X�łȂ��ꍇ��<BR>
			���̊֐��͎��s���܂��B
		*/
		virtual Bool SetRenderTarget( ISurface *pSurface )																																= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�擾
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g���擾���܂��B
		*/
		virtual Bool GetRenderTarget( ITexture **ppTexture )																															= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�擾
			@author �t���`
			@retval true	����
			@retval false	���s

			�����_�����O�^�[�Q�b�g���擾���܂��B
		*/
		virtual Bool GetRenderTarget( ISurface **ppSurface )																															= 0;

		/**
			@brief �[�x�X�e���V���o�b�t�@�ɐݒ�
			@author �t���`
			@retval true	����
			@retval false	���s

			�T�[�t�F�C�X��[�x�X�e���V���T�[�t�F�C�X�Ƃ��Đݒ肵�܂��B<BR>
			�[�x�X�e���V���T�[�t�F�C�X�Ƃ��Đ������ꂽ�T�[�t�F�C�X�łȂ��ꍇ��<BR>
			���̊֐��͎��s���܂��B
		*/
		virtual Bool SetDepthStencil( ISurface *pSurface )																																= 0;

		/**
			@brief �����_�����O�����J�n�ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă��ꂩ�烌���_�����O������<BR>
			�J�n����Ƃ�������ʒm���܂��B
		*/
		virtual void Begin( void )																																						= 0;

		/**
			@brief �����_�����O�����I���ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă���Ń����_�����O������<BR>
			�I������Ƃ������Ƃ�ʒm���܂��B
		*/
		virtual void End( void )																																						= 0;

		/**
			@brief �|�X�g�G�t�F�N�g�Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@return �|�X�g�G�t�F�N�g�Ǘ��C���^�[�t�F�C�X

			�|�X�g�G�t�F�N�g�Ǘ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�e�N�X�`�����g�����|�X�g�G�t�F�N�g�Ɋւ��鏈���͑S�Ă��̃C���^�[�t�F�C�X����܂��B
		*/
		virtual IPostEffect *CreatePostEffect( void )																																	= 0;

		/**
			@brief �V�[���Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@return �V�[���Ǘ��C���^�[�t�F�C�X

			�V�[���Ǘ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			3D�Ɋւ��郌���_�����O�����͑S�Ă��̃C���^�[�t�F�C�X����܂��B
		*/
		virtual ISceneManager *CreateSceneManager( eSceneMode Mode = SCENE_MODE_MANAGED, eSceneModeOption Option = SCENE_MODE_OPTION_NO )												= 0;

		/**
			@brief 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PointMax	[in] �����o�b�t�@�i�[�\�|�C���g��
			@return 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɓ_��łꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual IPointPrimitive2D *CreatePointPrimitive2D( Uint32 PointMax )																											= 0;

		/**
			@brief 2D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param LineMax	[in] �����o�b�t�@�i�[�\���C����
			@return 2D���C���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɐ��������ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual ILinePrimitive2D *CreateLinePrimitive2D( Uint32 LineMax )																												= 0;

		/**
			@brief 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@return 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual IPrimitive2D *CreatePrimitive2D( Uint32 PrimitiveMax )																													= 0;

		/**
			@brief 2D�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@param pTexture		[in] �X�v���C�g�Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@return 2D�X�v���C�g�C���^�[�t�F�C�X

			2D�̃X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive2D���p�����Ă���A�����I�ɂ�IPrimitive2D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`�����g�����ł��ȒP�ȃX�v���C�g�`�悪�\�ȃC���^�[�t�F�C�X�ł��B
		*/
		virtual ISprite2D *CreateSprite2D( Uint32 PrimitiveMax, ITexture *pTexture )																									= 0;

		/**
			@brief 2D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pBuffer		[in] �`�旘�p������i�����Ŏw�肵���������摜�Ƃ��ēW�J���g����悤�ɂ��܂��j
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@param pFontFace	[in] �t�H���g����
			@param FontSize		[in] �t�H���g�T�C�Y
			@param IsItalic		[in] �Α̃t�H���gON/OFF
			@param IsBold		[in] �����t�H���gON/OFF
			@param IsAntialias	[in] �A���`�G�C���A�X�t�H���gON/OFF
			@return 2D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			2D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			ISprite2D�𗘗p���Ă���A�����I�ɂ�ISprite2D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`���Ɏ��O�ɕ������摜�Ƃ��ēW�J���Ă������ƂŁA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual IFontSprite2D *CreateFontSprite2D( const wchar_t *pBuffer, Uint32 FontMax, const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold, Bool IsAntialias )	= 0;

		/**
			@brief 2D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pFileName	[in] �t�H���g�X�v���C�g�p��`�t�@�C��
			@param pExt			[in] �t�H���g�X�v���C�g�p�摜�t�@�C���g���q
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@return 2D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			2D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			ISprite2D�𗘗p���Ă���A�����I�ɂ�ISprite2D�ł̕`����s���Ă��܂��B<BR>
			FontUtility�Ő���������`�t�@�C���ƃe�N�X�`�����g���āA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual IFontSprite2D *CreateFontSprite2DFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 FontMax )																= 0;

		/**
			@brief 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] �|�C���g�̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|�C���g�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual IPointPrimitive3D *CreatePointPrimitive3D( Uint32 VertexMax, Bool IsDynamic )																							= 0;

		/**
			@brief 3D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] ���C���̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D���C���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃��C���`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual ILinePrimitive3D *CreateLinePrimitive3D( Uint32 VertexMax, Bool IsDynamic )																								= 0;

		/**
			@brief 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] �������_�o�b�t�@�̍ő吔
			@param IndexMax		[in] �����C���f�b�N�X�o�b�t�@�̍ő吔
			@param VertexFlag	[in] ���_�f�[�^�t���O�ieVertexElement�̑g�ݍ��킹�j
			@param IsDynamic		[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B<BR>
			�܂��C���f�b�N�X���g�p���������I�ȕ`����T�|�[�g���܂��B<BR>
			VertexFlag�͒��_�̃t�H�[�}�b�g���w�肷����̂� eVertexElement �񋓌^�̒�����<BR>
			VERTEX_ELEMENT_PRIMITIVE �� VERTEX_ELEMENT_SPRITE �����������̂��w�肵�܂��B<BR>
			�����g�ݍ��킹��ꍇ�� | ���Z�q�Ŏw�肵�Ă��������B<BR>
			���p�����V�F�[�_�[�͓����ō쐬���ꂽ�Œ�V�F�[�_�[�����p����܂��B<BR>
			���݂̃o�[�W�����ł̓o���v�}�b�v�Ɋւ��鏈���͍s���܂���B<BR>
			<BR>
			�i��j�@�����������C�e�B���O�\�Ȓ��_ -> VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT
		*/
		virtual IPrimitive3D *CreatePrimitive3D( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic )																	= 0;

		/**
			@brief ���f�����t�@�C�����琶��
			@author �t���`
			@param pFileName	[in] ���f����

			SMF�`���̃��f���t�@�C����ǂݍ��݂܂��B<BR>
			SMF�t�@�C����ConvertX2SMF���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual IModel *CreateModelFromFile( const wchar_t *pFileName )																													= 0;

		/**
			@brief ���f�������������琶��
			@author �t���`
			@param pData	[in] ���f���f�[�^
			@param Size		[in] �f�[�^�T�C�Y

			SMF�`���̃��f���f�[�^��ǂݍ��݂܂��B<BR>
			SMF�t�@�C����ConvertX2SMF���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual IModel *CreateModelFromMemory( const Uint8 *pData, Uint32 Size )																										= 0;

		/**
			@brief �f�o�C�X����T�[�t�F�C�X�𐶐�
			@author �t���`
			@param Width	[in] �T�[�t�F�C�X�̉���
			@param Height	[in] �T�[�t�F�C�X�̏c��
			@param Format	[in] �T�[�t�F�C�X�̃t�H�[�}�b�g
			@return �T�[�t�F�C�X�C���^�[�t�F�C�X
		*/
		virtual ISurface *CreateDepthStencilSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format )																				= 0;

		/**
			@brief �f�o�C�X����T�[�t�F�C�X�𐶐�
			@author �t���`
			@param Width		[in] �T�[�t�F�C�X�̉���
			@param Height		[in] �T�[�t�F�C�X�̏c��
			@param Format		[in] �T�[�t�F�C�X�̃t�H�[�}�b�g
			@param pCopyTarget	[in] Copy�g�p���̃R�s�[��̃T�[�t�F�C�X�i�t�H�[�}�b�g�ϊ��@�\�̃`�F�b�N�p�j
			@return �T�[�t�F�C�X�C���^�[�t�F�C�X
		*/
		virtual ISurface *CreateRenderTargetSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format, ISurface *pCopyTarget )														= 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^���擾
			@author �t���`
			@return �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual CTextureConfig &GetTextureConfig( void )																																= 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^�ݒ�
			@author �t���`
			@param Conf		[in] �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual void SetTextureConfig( CTextureConfig &Conf )																															= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param Width	[in] �e�N�X�`���̉���
			@param Height	[in] �e�N�X�`���̏c��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTexture( Uint32 Width, Uint32 Height )																													= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromFile( const wchar_t *pFileName )																												= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromMemory( void *pData, Uint32 Size )																											= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param Width	[in] �e�N�X�`���̉���
			@param Height	[in] �e�N�X�`���̏c��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureRenderTarget( Uint32 Width, Uint32 Height )																										= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@param fHeight	[in] �@���}�b�v�̍����{��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )																					= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@param fHeight	[in] �@���}�b�v�̍����{��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )																			= 0;

		/**
			@brief �`��^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �`��^�C�v

			�|���S���̕`��^�C�v��ݒ肵�܂��B
		*/
		virtual void SetDrawType( eDrawType Type )																																		= 0;

		/**
			@brief �\������^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �\������^�C�v

			�|���S���̕\������^�C�v��ݒ肵�܂��B
		*/
		virtual void SetCullType( eCullType Type )																																		= 0;

		/**
			@brief �t�B���^�����O�^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �t�B���^�����O�^�C�v

			�e�N�X�`���X�e�[�W���̃t�B���^�����O�^�C�v��ݒ肵�܂��B<BR>
			TEXTURE_FILTER_ANISOTROPY�n �̃t�B���^���T�|�[�g����Ȃ��n�[�h�E�F�A�ł�<BR>
			TEXTURE_FILTER_BILINEAR ���g���܂��B
		*/
		virtual void SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )																													= 0;

		/**
			@brief �e�N�X�`���A�h���b�V���O�^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �A�h���b�V���O�^�C�v

			�e�N�X�`���X�e�[�W���̃e�N�X�`���A�h���b�V���O�^�C�v��ݒ肵�܂��B<BR>
			0.0�`1.0�͈̔͊O��UV���w�肵�����ɂǂ̗l�ȏ������s�������w�肵�܂��B
		*/
		virtual void SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )																									= 0;

		/**
			@brief �e�N�X�`���I�y���[�V�����^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �I�y���[�V�����^�C�v

			�e�N�X�`���X�e�[�W���̃e�N�X�`���J���[�I�y���[�V�����^�C�v��ݒ肵�܂��B<BR>
			���ʃX�e�[�W�Ƃ̍������@�̏������w�肵�܂��B
		*/
		virtual void SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )																								= 0;

		/**
			@brief �[�x�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�e�X�gON/OFF

			�[�x�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthTestEnable( Bool Flag )																																	= 0;

		/**
			@brief �[�x�o�b�t�@��������ON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�o�b�t�@��������ON/OFF

			�[�x�o�b�t�@�������݂�ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthWriteEnable( Bool Flag )																																	= 0;

		/**
			@brief �A���t�@�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �A���t�@�e�X�gON/OFF

			�A���t�@�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetAlphaTestEnable( Bool Flag )																																	= 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N�ɑޔ����܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ������܂��B<BR>
			���̊֐��ɂ���đޔ������X�e�[�g�͈ȉ��̊֐��Őݒ肵�����̂ł��B<BR>
			�Evoid SetDrawType( eDrawType Type )<BR>
			�Evoid SetCullType( eCullType Type )<BR>
			�Evoid SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )<BR>
			�Evoid SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )<BR>
			�Evoid SetFogEnable( Bool Flag )<BR>
			�Evoid SetFogColor( CColor Color )<BR>
			�Evoid SetDepthTestEnable( Bool Flag )<BR>
			�Evoid SetDepthWriteEnable( Bool Flag )<BR>
			�Evoid SetAlphaTestEnable( Bool Flag )<BR>
			�Evoid SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )<BR>
			�EBool SetTexture( Uint32 Stage, ITexture *pTex )
		*/
		virtual Bool StatePush( void )																																					= 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N���畜�A���܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B
		*/
		virtual Bool StatePop( void )																																					= 0;

		/**
			@brief �X�e�[�g�̐ݒ��������ԂɃ��Z�b�g���܂�
			@author �t���`

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B<BR>
			�ESetDrawType( DRAW_TYPE_NORMAL )<BR>
			�ESetDrawType( DRAW_TYPE_NORMAL )<BR>
			�ESetCullType( CULL_FRONT )<BR>
			�ESetFogEnable( false )<BR>
			�ESetFogColor( 0x00000000 )<BR>
			�ESetDepthTestEnable( false )<BR>
			�ESetDepthWriteEnable( false )<BR>
			�Evoid SetAlphaTestEnable( true )<BR>
			�ESetTextureFilterType( <Stage>, TEXTURE_FILTER_DISABLE )<BR>
			�ESetTextureAddressType( <Stage>, TEXTURE_ADDRESS_REPEAT )<BR>
			�ESetTextureOperationType( <Stage>, <Stage>==0?TEXTURE_OP_MUL:TEXTURE_OP_NONE )<BR>
			�ESetTexture( <Stage>, NULL )
		*/
		virtual void StateInit( void )																																					= 0;
	};
}



namespace Selene
{
	/**
		@brief �|�X�g�G�t�F�N�g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IPostEffect
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
		virtual Uint32 Release( void )																																			= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																																			= 0;

		/**
			@brief �e�N�X�`�����g������`�����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			�P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void SingleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																	= 0;

		/**
			@brief �}���`�e�N�X�`�����g������`�����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param SrcTbl		[in] �e�N�X�`��UV��`
			@param TypeTbl		[in] �X�e�[�W���̉��Z�^�C�v
			@param pTexTbl		[in] �e�N�X�`��
			@param StageCount	[in] ���p����X�e�[�W��

			�P���ȋ�`���}���`�e�N�X�`���Ή��Ń����_�����O���܂��B<BR>
			2D�`��ɂ�����}���`�e�N�X�`���p�r�͎�Ƀ|�X�g�G�t�F�N�g�Ȃ̂�<BR>
			���̕����ɓ��������@�\�Ƃ��Ď������Ă���܂��B
		*/
		virtual void MultipleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> SrcTbl[], eTextureOperationType TypeTbl[], ITexture *pTexTbl[], Uint32 StageCount )		= 0;

		/**
			@brief �O���C�X�P�[���������_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��
			@param fRate		[in] �K�p�x(0.0�`1.0)

			�J���[�摜���O���[�X�P�[�������܂��B<BR>
			fRate�����ɂ���āA�i�K�I�ɃO���[�X�P�[�������鎖���\�ł��B<BR>
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void Grayscale( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex, Float fRate )																= 0;

		/**
			@brief ���j�o�[�T���g�����W�V���������_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param fRate		[in] �������[�g(0.0�`1.0)
			@param SrcBase		[in] �x�[�X�e�N�X�`��UV��`
			@param pBaseTex		[in] �x�[�X�e�N�X�`���C���^�[�t�F�C�X
			@param SrcRule		[in] ���[���e�N�X�`��UV��`
			@param pRuleTex		[in] ���[���e�N�X�`���C���^�[�t�F�C�X

			�O���[�X�P�[���̃��[���摜��p���ă��j�o�[�T���g�����W�V�������s���܂��B<BR>
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void UniversalTransition( CRect2D<Sint32> &Dst, Float fRate, CRect2D<Sint32> &SrcBase, ITexture *pBaseTex, CRect2D<Sint32> &SrcRule, ITexture *pRuleTex )			= 0;

		/**
			@brief �摜���ڂ����ă����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			3x3�{�b�N�X�t�B���^�ŉ摜���ڂ����܂��B
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void Blur9Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief �摜���ڂ����ă����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			4x4�{�b�N�X�t�B���^�ŉ摜���ڂ����܂��B
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void Blur16Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief �摜���ڂ����ă����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			8x8�{�b�N�X�t�B���^�ŉ摜���ڂ����܂��B<BR>
			�s�N�Z���V�F�[�_�[2.0���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			Blur16Box()�ɒu���������܂��B
		*/
		virtual void Blur64Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;
	};
}



namespace Selene
{
	/**
		@brief 2D�|�C���g�v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IPointPrimitive2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )							= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )							= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )							= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )								= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )								= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPoint	[in] ���_�f�[�^
			@param Count	[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SVertex2D *pPoint, Uint32 Count )	= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )							= 0;
	};
}



namespace Selene
{
	/**
		@brief ���C���v���~�e�B�u�p���_�f�[�^
@author �t���`
	*/
	struct SLineVertex2D
	{
		SVertex2D v1;
		SVertex2D v2;
	};

	/**
		@brief 2D���C���v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class ILinePrimitive2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )								= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )									= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )									= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pLine	[in] ���C���f�[�^
			@param Count	[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SLineVertex2D *pLine, Uint32 Count )		= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )								= 0;
	};
}



namespace Selene
{
	/**
		@brief �v���~�e�B�u�p���_�f�[�^
		@author �t���`
	*/
	struct SPrimitiveVertex2D
	{
		SVertex2DTex v1;
		SVertex2DTex v2;
		SVertex2DTex v3;
	};

	/**
		@brief 2D�v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IPrimitive2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																													= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																														= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )																				= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief �l�p�`�`��
			@author �t���`
			@param DstRect	[in] �`���`�f�[�^
			@param Color	[in] �`��F

			�P���Ȏl�p�`��`�悵�܂��B
		*/
		virtual void Square( CRect2D<Sint32> &DstRect, CColor Color )																					= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`
			@param DstRect	[in] �`���`�f�[�^
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t���̎l�p�`��`�悵�܂��B
		*/
		virtual void SquareRotate( CRect2D<Sint32> &DstRect, CColor Color, Sint32 Angle )																= 0;

		/**
			@brief ���p�`�`��
			@author �t���`
			@param Pos		[in] ���S�ʒu
			@param fRadius	[in] �`�攼�a
			@param Color	[in] �`��F
			@param Num		[in] �p��

			�P���ȑ��p�`��`�悵�܂��B
		*/
		virtual void Polygon( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num )															= 0;

		/**
			@brief ��]�t�����p�`�`��
			@author �t���`
			@param Pos		[in] ���S�ʒu
			@param fRadius	[in] �`�攼�a
			@param Color	[in] �`��F
			@param Num		[in] �p��
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t�����p�`��`�悵�܂��B
		*/
		virtual void PolygonRotate( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )										= 0;

		/**
			@brief �����O��`��
			@author �t���`
			@param Pos			[in] ���S�ʒu
			@param fInRadius	[in] �������a
			@param fOutRadius	[in] �O�����a
			@param InColor		[in] �����`��F
			@param OutColor		[in] �O���`��F
			@param Num			[in] �p��

			�����O��|���S����`�悵�܂��B
		*/
		virtual void Ring( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )						= 0;

		/**
			@brief ��]�t�������O��`��
			@author �t���`
			@param Pos			[in] ���S�ʒu
			@param fInRadius	[in] �������a
			@param fOutRadius	[in] �O�����a
			@param InColor		[in] �����`��F
			@param OutColor		[in] �O���`��F
			@param Num			[in] �p��
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t�������O��|���S����`�悵�܂��B
		*/
		virtual void RingRotate( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )	= 0;
	};
}



namespace Selene
{
	/**
		@brief 2D�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class ISprite2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																													= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																														= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )																				= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief �l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F

			�ł��P���ȃX�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color )														= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F
			@param Angle		[in] 1��65536�Ƃ�����]�p�x

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle )									= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src )				= 0;

		/**
			@brief ���ˏ�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���S�Ɍ������ăt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )													= 0;

		/**
			@brief �~���]�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���v���Ƀt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )												= 0;
	};
}



namespace Selene
{
	/**
		@brief �t�H���g�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IFontSprite2D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																			= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																			= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																			= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																				= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																				= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																			= 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )						= 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )						= 0;

		/**
			@brief �����`��
			@author �t���`
			@param Chara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F

			�w��ʒu�ɕ�����`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawChara( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color )						= 0;

		/**
			@brief ��]�t�������`��
			@author �t���`
			@param Chara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			�w��ʒu�ɕ�������]�t���ŕ`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawCharaRotate( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color, Sint32 Angle )	= 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@return		�`�抮�����̍��W

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual CPoint2D<Sint32> GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos )					= 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@return		�`�抮�����̍��W

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual CPoint2D<Sint32> GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos )					= 0;
	};
}



namespace Selene
{
	/**
		@brief 3D�|�C���g�v���~�e�B�u�`��N���X
		@author �t���`
	*/
	class IPointPrimitive3D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`
			@return �V�[�����̎��ʔԍ�

			�����o�b�t�@�̓��e���V�[���}�l�[�W���[�ɑ΂��ă����_�����O���N�G�X�g�����܂��B<BR>
			���ۂ̃����_�����O�����̓V�[���}�l�[�W���[���ōs���܂��B<BR>
			���̂��߁A���̊֐��̓����_�����O������҂����ɖ߂��Ă��܂��B
		*/
		virtual Sint32 Rendering( void )									= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pPoint		[in] �|�C���g�f�[�^
			@param PointCount	[in] �|�C���g��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵�����_�t�H�[�}�b�g�ɓK���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DBase *pPoint, Uint32 PointCount )		= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )											= 0;

		/**
			@brief ���W�ϊ��p�p���f�[�^�ݒ�
			@author �t���`
			@param Style	[in] �p���f�[�^

			���W�ϊ��p�̎p���f�[�^��ݒ肵�܂��B
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief �}�e���A���F�ݒ�
			@author �t���`
			@param Color	[in] �}�e���A���̐F

			�}�e���A���̐F��ݒ肵�܂��B
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;
	};
}



namespace Selene
{
	/**
		@brief 3D�v���~�e�B�u��{�f�[�^
		@author �t���`

		ILinePrimitive3D�ŕ`����s���ۂɎg�p���钸�_�f�[�^�B
	*/
	struct SPrimitive3DVertexLine
	{
		SVertex3DBase v1;			///< �ʒu�E���_�F
		SVertex3DBase v2;			///< �ʒu�E���_�F
	};

	/**
		@brief 3D���C���v���~�e�B�u�`��N���X
		@author �t���`
	*/
	class ILinePrimitive3D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`
			@return �V�[�����̎��ʔԍ�

			�����o�b�t�@�̓��e���V�[���}�l�[�W���[�ɑ΂��ă����_�����O���N�G�X�g�����܂��B<BR>
			���ۂ̃����_�����O�����̓V�[���}�l�[�W���[���ōs���܂��B<BR>
			���̂��߁A���̊֐��̓����_�����O������҂����ɖ߂��Ă��܂��B
		*/
		virtual Sint32 Rendering( void )										= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pLine		[in] ���C���f�[�^
			@param LineCount	[in] ���C����
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵�����_�t�H�[�}�b�g�ɓK���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SPrimitive3DVertexLine *pLine, Uint32 LineCount )		= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )											= 0;

		/**
			@brief ���W�ϊ��p�p���f�[�^�ݒ�
			@author �t���`
			@param Style	[in] �p���f�[�^

			���W�ϊ��p�̎p���f�[�^��ݒ肵�܂��B
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief �}�e���A���F�ݒ�
			@author �t���`
			@param Color	[in] �}�e���A���̐F

			�}�e���A���̐F��ݒ肵�܂��B
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;
	};
}



namespace Selene
{
	/**
		@brief 3D�v���~�e�B�u�`��N���X
		@author �t���`

		�|���S���f�[�^�������ō��Ƃ��Ɏg�p���邽�߂̃N���X�ł��B<BR>
		�쐬���Ƀt���O�Ŏw�肵�����_�f�[�^�ƃC���f�b�N�X�f�[�^��<BR>
		�v���O�����Ńo�b�t�@�ɒǉ����Ă��������_�����O���܂��B<BR>
		���C�e�B���O��X�L�j���O�Ȃǂ̋@�\���T�|�[�g����Ă��܂����A<BR>
		�o���v�}�b�s���O�̓T�|�[�g����Ă��܂���B<BR>
	<BR>
		�܂����s�̃o�[�W�����ł͓����ŏ������Ă���V�F�[�_�[�ł���<BR>
		�����_�����O�����鎖���ł��܂���B<BR>
		���̐����͏C���\��ł��B
	*/
	class IPrimitive3D
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`
			@return �V�[�����̎��ʔԍ�

			�����o�b�t�@�̓��e���V�[���}�l�[�W���[�ɑ΂��ă����_�����O���N�G�X�g�����܂��B<BR>
			���ۂ̃����_�����O�����̓V�[���}�l�[�W���[���ōs���܂��B<BR>
			���̂��߁A���̊֐��̓����_�����O������҂����ɖ߂��Ă��܂��B
		*/
		virtual Sint32 Rendering( void )										= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count )		= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count )	= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count )		= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count )		= 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count )	= 0;

		/**
			@brief �C���f�b�N�X�f�[�^��ǉ�
			@author �t���`
			@param pIndex		[in] �C���f�b�N�X�f�[�^
			@param IndexCount	[in] �C���f�b�N�X��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�փC���f�b�N�X�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵���C���f�b�N�X�t�H�[�}�b�g�ɓK�������C���f�b�N�X�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DBase &Vtx, Uint32 Index )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DTexture &Vtx, Uint32 Index )		= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DLight &Vtx, Uint32 Index )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DBump &Vtx, Uint32 Index )			= 0;

		/**
			@brief ���_�f�[�^���擾
			@author �t���`
			@param Vtx		[in] �擾���钸�_�f�[�^
			@param Index	[in] �擾���钸�_�C���f�b�N�X
			@retval false	�擾�ł��Ȃ������i�C���f�b�N�X���͈͊O�j
			@retval true	�擾�ł���

			�����o�b�t�@�̒��_�f�[�^���擾���܂��B
		*/
		virtual Bool Get( SVertex3DAnimation &Vtx, Uint32 Index )		= 0;

		/**
			@brief ���_���擾
			@author �t���`
			@return �ǉ��v�����������_�̐�

			�ǉ��v�����s����SVertex3DBase���_�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Uint32 GetVertexCount( void )								= 0;

		/**
			@brief �C���f�b�N�X���擾
			@author �t���`
			@return �ǉ��v���������C���f�b�N�X�̐�

			�ǉ��v�����s�����C���f�b�N�X�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Uint32 GetIndexCount( void )								= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )											= 0;

		/**
			@brief �{�[�����ݒ�
			@author �t���`
			@param BoneCount	[in] �{�[����

			�����_�����O�Ɏg����{�[���̐���ݒ肵�܂��B
		*/
		virtual void SetBoneCount( Sint32 BoneCount )						= 0;

		/**
			@brief �I�t�Z�b�g�p�{�[���ݒ�
			@author �t���`
			@param No		[in] �{�[���ԍ�
			@param Matrix	[in] �I�t�Z�b�g�s��

			�w��ԍ��̃{�[���̐e����̃I�t�Z�b�g�p�̍s���ݒ肵�܂��B
		*/
		virtual void SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix )		= 0;

		/**
			@brief �g�����X�t�H�[���p�{�[���ݒ�
			@author �t���`
			@param No		[in] �{�[���ԍ�
			@param Matrix	[in] �g�����X�t�H�[���s��

			�w��ԍ��̃{�[���̃g�����X�t�H�[���p�̍s���ݒ肵�܂��B
		*/
		virtual void SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix )	= 0;

		/**
			@brief ���W�ϊ��p�p���f�[�^�ݒ�
			@author �t���`
			@param Style	[in] �p���f�[�^

			���W�ϊ��p�̎p���f�[�^��ݒ肵�܂��B
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief �}�e���A���F�ݒ�
			@author �t���`
			@param Color	[in] �}�e���A���̐F

			�}�e���A���̐F��ݒ肵�܂��B
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;

		/**
			@brief �X�y�L�����F�ݒ�
			@author �t���`
			@param Color	[in] �X�y�L�����̐F

			�X�y�L�����̐F��ݒ肵�܂��B
		*/
		virtual void SetSpecularColor( CColor Color )						= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param fRefractive		[in] �X�y�L�����̋��ܗ�(����20.0f)

			�}�e���A���̃X�y�L�����̋��ܗ���ݒ肵�܂�
		*/
		virtual void SetSpecularRefractive( Float fRefractive )				= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param fRoughly			[in] �X�y�L�����̑e��(����0.5f)

			�}�e���A���̃X�y�L�����̑e����ݒ肵�܂�
		*/
		virtual void SetSpecularRoughly( Float fRoughly )					= 0;
	};
}



namespace Selene
{
	class IMesh
	{
	public:
		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)													= 0;

		/**
			@brief ���ʔ��˗p���f���ɕϊ�
			@author �t���`

			���̊֐����Ăяo���Ǝ��ŋ��ʔ��˂�L�����o���܂��B<BR>
			���s�����ɑ΂��Ă̒P���ȃt�H�����ʔ��˂��K�p�����悤�ɂȂ�܂��B
		*/
		virtual void ConvertReflexMesh( void )											= 0;

		/**
			@brief �o���v�}�b�v�p���f���ɕϊ�
			@author �t���`
			@param pTexNormal	[in] �o���v�p�@���}�b�v

			���̊֐����Ăяo���Ǝ��Ńo���v�}�b�v��L�����o���܂��B<BR>
			�������ȉ��̏����𖞂����Ă���K�v������܂��B<BR>
			�E�e�N�X�`��UV�f�[�^�������Ă���<BR>
			�E�@���E�ڐ��f�[�^�������Ă���<BR>
			<BR>
			�ʏ�ConvertX2SMF�ō쐬�����ꍇ�͌���X�t�@�C���Ƀe�N�X�`�����܂܂�ē���΁A<BR>
			��L�̃f�[�^�͊܂܂�Ă��܂��B<BR>
			�܂����̂Ƃ��w�肷��e�N�X�`���͖@���}�b�v�ł���K�v������܂��B<BR>
			�@���}�b�v��IRender::CreateTextureFromFileForNormalMap()��
			IRender::CreateTextureFromMemoryForNormalMap()�֐��ō쐬�ł��܂��B
		*/
		virtual void ConvertBumpMesh( ITexture *pTexNormal )								= 0;

		/**
			@brief �����}�b�v�p���f���ɕϊ�
			@author �t���`
			@param pTexNormal		[in] �o���v�p�@���}�b�v
			@param fParallaxDepth	[in] �����[�x�i��������0.01�`0.05���x�j

			���̊֐����Ăяo���Ǝ��Ŏ����}�b�v��L�����o���܂��B<BR>
			�������ȉ��̏����𖞂����Ă���K�v������܂��B<BR>
			�E�e�N�X�`��UV�f�[�^�������Ă���<BR>
			�E�@���E�ڐ��f�[�^�������Ă���<BR>
			<BR>
			�ʏ�ConvertX2SMF�ō쐬�����ꍇ�͌���X�t�@�C���Ƀe�N�X�`�����܂܂�ē���΁A<BR>
			��L�̃f�[�^�͊܂܂�Ă��܂��B<BR>
			�@���}�b�v��IRender::CreateTextureFromFileForNormalMap()��
			IRender::CreateTextureFromMemoryForNormalMap()�֐��ō쐬�ł��܂��B
		*/
		virtual void ConvertParallaxMesh( ITexture *pTexNormal, Float fParallaxDepth )	= 0;

		/**
			@brief �}�e���A���̐����擾
			@author �t���`
			@return �}�e���A����

			���b�V������������}�e���A���̐����擾���܂�
		*/
		virtual Uint32 GetMaterialCount( void )											= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param Color			[in] �X�y�L�����̐F

			�}�e���A�����Ƃ̃X�y�L�����̐F��ݒ肵�܂�
		*/
		virtual void SetSpecularColor( Uint32 MaterialIndex, CColor Color )				= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fRefractive		[in] �X�y�L�����̋��ܗ�(����20.0f)

			�}�e���A�����Ƃ̃X�y�L�����̋��ܗ���ݒ肵�܂�
		*/
		virtual void SetSpecularRefractive( Uint32 MaterialIndex, Float fRefractive )	= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fRoughly			[in] �X�y�L�����̑e��(����0.5f)

			�}�e���A�����Ƃ̃X�y�L�����̑e����ݒ肵�܂�
		*/
		virtual void SetSpecularRoughly( Uint32 MaterialIndex, Float fRoughly )			= 0;

		/**
			@brief �@���f�[�^�̉��������܂�
			@author �t���`
			@param fLength	[in] ����

			���b�V���̖@���E�ڐ��E�]�@���f�[�^�����������邱�Ƃ��ł��܂��B
		*/
		virtual void NormalVisible( Float fLength )										= 0;

		/**
			@brief �o�E���f�B���O�f�[�^�̉��������܂�
			@author �t���`

			���b�V���̃o�E���f�B���O�{�b�N�X�����������邱�Ƃ��ł��܂��B
		*/
		virtual void BoundingVisible( void )											= 0;

		/**
			@brief �����_�����OID�擾
			@author �t���`

			�����_�����O���̃V�[��ID���擾���܂��B
		*/
		virtual Sint32 GetRenderID( void )												= 0;
	};
}



namespace Selene
{
	class IFrame
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)										= 0;
	};
}



namespace Selene
{
	class IModel
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief ���W�ϊ��p�p���f�[�^�ݒ�
			@author �t���`
			@param Style	[in] �p���f�[�^

			���W�ϊ��p�̎p���f�[�^��ݒ肵�܂��B
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief �����o�b�t�@�̃����_�����O
			@author �t���`

			�����o�b�t�@�̓��e���V�[���}�l�[�W���[�ɑ΂��ă����_�����O���N�G�X�g�����܂��B<BR>
			���ۂ̃����_�����O�����̓V�[���}�l�[�W���[���ōs���܂��B<BR>
			���̂��߁A���̊֐��̓����_�����O������҂����ɖ߂��Ă��܂��B
		*/
		virtual void Rendering( void )										= 0;

		/**
			@brief �t���[���f�[�^�擾
			@author �t���`
			@param FrameIndex	[in] �t���[���ԍ�
			@param pFrame		[in] �t���[���i�[��

			���f�����̃t���[���f�[�^���擾���܂��B<BR>
			�擾�����t���[���͕s�v�ɂȂ�����Release()���Ă��������B
		*/
		virtual Bool GetFrame( Uint32 FrameIndex, IFrame *&pFrame )			= 0;

		/**
			@brief �t���[�����擾
			@author �t���`
			@return �t���[����

			���f�����̃t���[�������擾���܂��B
		*/
		virtual Uint32 GetFrameCount( void )								= 0;

		/**
			@brief ���b�V���f�[�^�擾
			@author �t���`
			@param MeshIndex	[in] ���b�V���ԍ�
			@param pMesh		[in] ���b�V���i�[��

			���f�����̃��b�V���f�[�^���擾���܂��B<BR>
			�擾�������b�V���͕s�v�ɂȂ�����Release()���Ă��������B
		*/
		virtual Bool GetMesh( Uint32 MeshIndex, IMesh *&pMesh )				= 0;

		/**
			@brief ���b�V�����擾
			@author �t���`
			@return ���b�V����

			���f�����̃��b�V�������擾���܂��B
		*/
		virtual Uint32 GetMeshCount( void )									= 0;
	};
}



namespace Selene
{
	/**
		@brief �e�N�X�`���C���^�[�t�F�C�X
		@author �t���`

		�e�N�X�`���𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B<BR>
		IRender�C���^�[�t�F�C�X����擾�ł��܂��B
	*/
	class ITexture
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																		= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )																		= 0;

		/**
			@brief ��`�R�s�[
			@author �t���`
			@param pDstRect		[in] �]����e�N�X�`���̋�`
			@param pSrcTex		[in] �]�����e�N�X�`��
			@param pSrcRect		[in] �]�����e�N�X�`���̋�`
			@param IsUvToTexel	[in] �e�N�X�`���T�C�Y�ƃC���[�W�T�C�Y����v���Ȃ��ꍇ�̕␳�����邩�ۂ�
			@retval true	����
			@retval false	���s

			�e�N�X�`�����m�̊g��k���R�s�[���s���܂��B<BR>
			�e�N�X�`���ԂŃt�H�[�}�b�g���قȂ�ꍇ��<BR>
			�n�[�h�E�F�A�̃t�H�[�}�b�g�ϊ��̃T�|�[�g���Ȃ���<BR>
			���̊֐��͎��s���܂��B<BR>
			�܂����̃R�s�[�����ɂ͂������̐��������݂��܂��B<BR>
			�E�ʏ�e�N�X�`������ʏ�e�N�X�`���̊g��k���R�s�[�͂ł��܂���B<BR>
			�E�o�b�N�o�b�t�@����ʏ�e�N�X�`���ւ̃R�s�[�͂ł��܂���B
		*/
		virtual Bool Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel = false )	= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g���_�E�����[�h
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�T�[�t�F�C�X<BR>
			���݂̃����_�����O�^�[�Q�b�g�̓��e���R�s�[���܂��B
		*/
		virtual Bool DownloadRenderTarget( void )															= 0;

		/**
			@brief �e�N�X�`���X�V
			@author �t���`

			�o�b�N�A�b�v�p�V�X�e���������}�e���A���̓��e��<BR>
			VRAM��̃}�e���A���֓]�����܂��B
		*/
		virtual void UpdateTexture( void )																	= 0;

		/**
			@brief �摜�t�@�C���Ƃ��ĕۑ�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@retval false	���s
			@retval true	����

			�e�N�X�`���̓��e��TGA�摜�t�@�C���Ƃ��ĕۑ����܂��B
		*/
		virtual Bool SaveToTGA( const wchar_t *pFileName )													= 0;

		/**
			@brief ���e�N�X�`���T�C�Y�擾
			@author �t���`
			@return �e�N�X�`���̎��T�C�Y

			�e�N�X�`���̃T�C�Y���擾���܂��B<BR>
			�Q�̗ݏ�łȂ��e�N�X�`�����쐬�����ۂ�<BR>
			�f�o�C�X�����̃T�C�Y�����ہ[�Ƃ��Ă��Ȃ��Ƃ���<BR>
			����ł���傫���̂Q�̗ݏ�̃T�C�Y�ɂȂ��Ă��܂��B
		*/
		virtual CPoint2D<Uint32> GetSize( void )															= 0;
	};
}



namespace Selene
{
	/**
		@brief �}�e���A���C���^�[�t�F�C�X
		@author �t���`

		�T�[�t�F�C�X�t�F�C�X���삷�邽�߂̃C���^�[�t�F�C�X�ł��B<BR>
		IRender�C���^�[�t�F�C�X����擾�ł��܂��B
	*/
	class ISurface
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
		virtual Uint32 Release( void )											= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )											= 0;

		/**
			@brief �o�b�N�o�b�t�@�ɃR�s�[
			@author �t���`
			@retval true	����
			@retval false	���s

			�T�[�t�F�C�X�t�F�C�X�o�b�N�o�b�t�@�ɃR�s�[���܂��B<BR>
			�������[�x�X�e���V���}�e���A����t�H�[�}�b�g�ϊ��Ƀn�[�h�E�F�A��<BR>
			�Ή����Ă��Ȃ��t�H�[�}�b�g�̃}�e���A���ł͎��s���܂��B
		*/
		virtual Bool CopyToBackBuffer( void )									= 0;

		/**
			@brief �}�e���A���̃R�s�[
			@author �t���`
			@param pDstRect		[in] �]����}�e���A���̋�`
			@param pSrc			[in] �]�����}�e���A��
			@param pSrcRect		[in] �]�����}�e���A���̋�`
			@retval true	����
			@retval false	���s

			�}�e���A�����m�̊g��k���R�s�[���s���܂��B<BR>
			�}�e���A���ԂŃt�H�[�}�b�g���قȂ�ꍇ��<BR>
			�n�[�h�E�F�A�̃t�H�[�}�b�g�ϊ��̃T�|�[�g���Ȃ���<BR>
			���̊֐��͎��s���܂��B<BR>
			�܂����̃R�s�[�����ɂ͂������̐��������݂��܂��B<BR>
			�E�ʏ�}�e���A������ʏ�}�e���A���̊g��k���R�s�[�͂ł��܂���B<BR>
			�E�o�b�N�o�b�t�@����ʏ�}�e���A���ւ̃R�s�[�͂ł��܂���B
		*/
		virtual Bool Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )		= 0;
	};
}



namespace Selene
{
	/**
		@brief �t�@�C���V�[�N��`
		@author �t���`
	*/
	enum eSeekFlag
	{
		SEEK_FILE_CURRENT,					///< �J�����g�ʒu
		SEEK_FILE_START,					///< �擪�ʒu
		SEEK_FILE_END,						///< �I�[�ʒu
	};

	/**
		@brief �t�@�C���Ǘ��N���X
		@author �t���`
	*/
	class IFileManager
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
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																		= 0;

		/**
			@brief �t�@�C�����[�h�p�X�ݒ�
			@author �t���`
			@param Priority		[in] �����v���C�I���e�B
			@param pRootPath	[in] ���[�g�f�B���N�g��
			@param pPackFile	[in] �p�b�N�t�@�C����

			�t�@�C���̓ǂݍ��݂��s�����[�g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ�p�X����уp�b�N�t�@�C���͓���Ɉ����܂��B<BR>
			�܂�v���O�����̕ύX�Ȃ��o���ɂ܂����������悤�ɃA�N�Z�X�\�ł��B
		*/
		virtual void SetLoadPath( Uint32 Priority, const wchar_t *pRootPath, const wchar_t *pPackFile )		= 0;

		/**
			@brief �J�����g�f�B���N�g���ݒ�
			@author �t���`
			@param pCurrentDir	[in] �f�B���N�g����

			�t�@�C���������s���ۂ̃J�����g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ�f�B���N�g�������[�g�Ƃ��ăt�@�C���̌������s���܂��B
		*/
		virtual void SetCurrentDirectory( wchar_t *pCurrentDir )											= 0;

		/**
			@brief �t�@�C�����[�h
			@author �t���`
			@param pFile	[in] �t�@�C����
			@param ppData	[out] �t�@�C���f�[�^�i�[��
			@param pSize	[out] �t�@�C���T�C�Y�i�[��
			@retval true	����
			@retval false	���s

			�t�@�C�������[�h���܂��B<BR>
			SetLoadPath() �Ŏw�肳��Ă���[�t�H���_]��[�p�b�N�t�@�C��]��<BR>
			���Ƀt�@�C�����������܂��B
		*/
		virtual Bool Load( const wchar_t *pFile, void **ppData, Uint32 *pSize )								= 0;

		/**
			@brief �f�[�^���
			@author �t���`
			@param pData	[in] �f�[�^

			Load()�֐��Ŏ擾�����f�[�^�����������������܂��B<BR>
			���̊֐����g�������@�ȊO�ł̉���͊��ˑ����邽�߁A<BR>
			�������������Ȃ��\��������܂��B
		*/
		virtual void Free( void *pData )																	= 0;

		/**
			@brief �t�@�C���I�[�v��
			@author �t���`
			@param pFile		[in] �t�@�C����
			@retval NULL		���s
			@retval NULL�ȊO	�t�@�C���C���^�[�t�F�C�X

			���\�[�X�t�@�C�����I�[�v�����܂��B<BR>
			�����ł������\�[�X�t�@�C���̓Q�[���Ŏg����f�[�^�S�ʂ̎��ł��B<BR>
			�܂�p�b�N�t�@�C���̓��e�A����у��[�g�f�B���N�g���ȉ��̃f�[�^�ł��B<BR>
			SetLoadPath() �Ŏw�肳��Ă���[�t�H���_]��[�p�b�N�t�@�C��]��<BR>
			���Ƀt�@�C�����������܂��B<BR>
			�I�[�v�������t�@�C���̓p�b�N�t�@�C���ł����Ă��A<BR>
			�ʏ�̃t�@�C���Ɠ����悤�ɃA�N�Z�X���邱�Ƃ��o���܂��B<BR>
			�܂����̊֐�����擾����IFIle�C���^�[�t�F�C�X�͓ǂݎ���p�ł��B<BR>
			�g�p���I������IFile�C���^�[�t�F�C�X��Release()�ŉ�����Ă��������B
		*/
		virtual IResourceFile *FileOpen( const wchar_t *pFile )												= 0;
	};
}



namespace Selene
{
	/**
		@brief ���\�[�X�t�@�C������
		@author �t���`
	*/
	class IResourceFile
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
		virtual Uint32 Release( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)								= 0;

		/**
			@brief �t�@�C���ւ̓ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �ǂݍ��݃f�[�^�T�C�Y
			@return ���ۂɏ������񂾃o�C�g��

			�t�@�C���ւ̓ǂݍ��݂��s���܂��B<BR>
			�ǂݍ��݉\�ȃt�@�C���̓C���^�[�t�F�C�X��������<BR>
			FILE_OPEN_TYPE_READ��FILE_OPEN_TYPE_READ_WRITE�t���O��<BR>
			�w�肷��K�v������܂��B
		*/
		virtual Uint32 Read( void *pData, Uint32 Size )				= 0;

		/**
			@brief �t�@�C�����擾
			@author �t���`
			@return �t�@�C�����̐擪�A�h���X

			�t�@�C�����̐擪�A�h���X���擾���܂��B
		*/
		virtual const wchar_t *GetNamePointer( void )				= 0;

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y

			�t�@�C���̃T�C�Y���擾���܂��B
		*/
		virtual Uint32 GetFileSize( void )							= 0;

		/**
			@brief �t�@�C���|�C���^�[�ʒu�擾
			@author �t���`
			@return �t�@�C���|�C���^�[�̈ʒu

			���݂̃t�@�C���|�C���^�̈ʒu���擾���܂��B
		*/
		virtual Uint32 GetFilePosition( void )						= 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̐擪����Offset�o�C�g�ړ����܂��B
		*/
		virtual Uint32 SeekStart( Sint32 Offset )					= 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̏I�[����Offset�o�C�g�ړ����܂��B
		*/
		virtual Uint32 SeekEnd( Sint32 Offset )						= 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu�����݂̈ʒu����Offset�o�C�g�ړ����܂��B
		*/
		virtual Uint32 Seek( Sint32 Offset )						= 0;
	};
}



namespace Selene
{
	/**
		@brief �}�E�X�{�^����Ԓ�`
		@author �t���`
	*/
	enum eMouseState
	{
		MOUSE_FREE,							///< �}�E�X�{�^���͉�����Ă��Ȃ�
		MOUSE_PULL,							///< �}�E�X�{�^���͗����ꂽ
		MOUSE_PUSH,							///< �}�E�X�{�^���͉����ꂽ
		MOUSE_HOLD,							///< �}�E�X�{�^���͉�����Â��Ă���
	};

	/**
		@brief �}�E�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IMouse
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
		virtual Uint32 Release( void )					= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )					= 0;

		/**
			@brief �}�E�X��X���W�擾
			@author �t���`
			@return X���W

			�}�E�X�|�C���^�[�̃X�N���[�����W���X���W���擾���܂��B
		*/
		virtual Sint32 GetPosX( void ) const			= 0;

		/**
			@brief �}�E�X��Y���W�擾
			@author �t���`
			@return Y���W

			�}�E�X�|�C���^�[�̃X�N���[�����W���Y���W���擾���܂��B
		*/
		virtual Sint32 GetPosY( void ) const			= 0;

		/**
			@brief �}�E�X�̃z�C�[����]�ʎ擾
			@author �t���`
			@return �z�C�[����]��

			�}�E�X�z�C�[���̉�]�ʂ��擾���܂��B
		*/
		virtual Sint32 GetPosW( void ) const			= 0;

		/**
			@brief �}�E�X��X�ړ��ʎ擾
			@author �t���`
			@return X�ړ���

			�}�E�X�|�C���^�[�̃X�N���[���ړ��ʏ��X�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveX( void ) const			= 0;

		/**
			@brief �}�E�X��Y�ړ��ʎ擾
			@author �t���`
			@return Y�ړ���

			�}�E�X�|�C���^�[�̃X�N���[���ړ��ʏ��Y�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveY( void ) const			= 0;

		/**
			@brief �}�E�X�̍��N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���͉�����Ă��Ȃ�
			@retval true	���{�^���͉�����Ă���

			�}�E�X�̍��{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickL( void ) const			= 0;

		/**
			@brief �}�E�X�̉E�N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���͉�����Ă��Ȃ�
			@retval true	�E�{�^���͉�����Ă���

			�}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickR( void ) const			= 0;

		/**
			@brief �}�E�X�̃z�C�[���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���͉�����Ă��Ȃ�
			@retval true	�z�C�[���{�^���͉�����Ă���

			�}�E�X�̃z�C�[���{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickW( void ) const			= 0;

		/**
			@brief �}�E�X�̍��_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	���{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̍��{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickL( void ) const		= 0;

		/**
			@brief �}�E�X�̉E�_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	�E�{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̉E�{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickR( void ) const		= 0;

		/**
			@brief �}�E�X�̃z�C�[���_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	�z�C�[���{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̃z�C�[���{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickW( void ) const		= 0;

		/**
			@brief �}�E�X�̍��{�^����Ԏ擾
			@author �t���`
			@return		���{�^���̏��

			�}�E�X�̍��{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState GetStateL( void ) const		= 0;

		/**
			@brief �}�E�X�̉E�{�^����Ԏ擾
			@author �t���`
			@return		�E�{�^���̏��

			�}�E�X�̉E�{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState	GetStateR( void ) const		= 0;

		/**
			@brief �}�E�X�̃z�C�[���{�^����Ԏ擾
			@author �t���`
			@return		�z�C�[���{�^���̏��

			�}�E�X�̃z�C�[���{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState	GetStateW( void ) const		= 0;
	};
}



namespace Selene
{
	/**
		@brief ���z�L�[�R�[�h
		@author �t���`
	*/
	enum eVirtualKeyCode
	{
		SELENE_VK_ESCAPE          = 0x01,
		SELENE_VK_1               = 0x02,
		SELENE_VK_2               = 0x03,
		SELENE_VK_3               = 0x04,
		SELENE_VK_4               = 0x05,
		SELENE_VK_5               = 0x06,
		SELENE_VK_6               = 0x07,
		SELENE_VK_7               = 0x08,
		SELENE_VK_8               = 0x09,
		SELENE_VK_9               = 0x0A,
		SELENE_VK_0               = 0x0B,
		SELENE_VK_MINUS           = 0x0C,
		SELENE_VK_EQUALS          = 0x0D,
		SELENE_VK_BACK            = 0x0E,
		SELENE_VK_TAB             = 0x0F,
		SELENE_VK_Q               = 0x10,
		SELENE_VK_W               = 0x11,
		SELENE_VK_E               = 0x12,
		SELENE_VK_R               = 0x13,
		SELENE_VK_T               = 0x14,
		SELENE_VK_Y               = 0x15,
		SELENE_VK_U               = 0x16,
		SELENE_VK_I               = 0x17,
		SELENE_VK_O               = 0x18,
		SELENE_VK_P               = 0x19,
		SELENE_VK_LBRACKET        = 0x1A,
		SELENE_VK_RBRACKET        = 0x1B,
		SELENE_VK_RETURN          = 0x1C,
		SELENE_VK_LCONTROL        = 0x1D,
		SELENE_VK_A               = 0x1E,
		SELENE_VK_S               = 0x1F,
		SELENE_VK_D               = 0x20,
		SELENE_VK_F               = 0x21,
		SELENE_VK_G               = 0x22,
		SELENE_VK_H               = 0x23,
		SELENE_VK_J               = 0x24,
		SELENE_VK_K               = 0x25,
		SELENE_VK_L               = 0x26,
		SELENE_VK_SEMICOLON       = 0x27,
		SELENE_VK_APOSTROPHE      = 0x28,
		SELENE_VK_GRAVE           = 0x29,
		SELENE_VK_LSHIFT          = 0x2A,
		SELENE_VK_BACKSLASH       = 0x2B,
		SELENE_VK_Z               = 0x2C,
		SELENE_VK_X               = 0x2D,
		SELENE_VK_C               = 0x2E,
		SELENE_VK_V               = 0x2F,
		SELENE_VK_B               = 0x30,
		SELENE_VK_N               = 0x31,
		SELENE_VK_M               = 0x32,
		SELENE_VK_COMMA           = 0x33,
		SELENE_VK_PERIOD          = 0x34,
		SELENE_VK_SLASH           = 0x35,
		SELENE_VK_RSHIFT          = 0x36,
		SELENE_VK_MULTIPLY        = 0x37,
		SELENE_VK_LMENU           = 0x38,
		SELENE_VK_SPACE           = 0x39,
		SELENE_VK_CAPITAL         = 0x3A,
		SELENE_VK_F1              = 0x3B,
		SELENE_VK_F2              = 0x3C,
		SELENE_VK_F3              = 0x3D,
		SELENE_VK_F4              = 0x3E,
		SELENE_VK_F5              = 0x3F,
		SELENE_VK_F6              = 0x40,
		SELENE_VK_F7              = 0x41,
		SELENE_VK_F8              = 0x42,
		SELENE_VK_F9              = 0x43,
		SELENE_VK_F10             = 0x44,
		SELENE_VK_NUMLOCK         = 0x45,
		SELENE_VK_SCROLL          = 0x46,
		SELENE_VK_NUMPAD7         = 0x47,
		SELENE_VK_NUMPAD8         = 0x48,
		SELENE_VK_NUMPAD9         = 0x49,
		SELENE_VK_SUBTRACT        = 0x4A,
		SELENE_VK_NUMPAD4         = 0x4B,
		SELENE_VK_NUMPAD5         = 0x4C,
		SELENE_VK_NUMPAD6         = 0x4D,
		SELENE_VK_ADD             = 0x4E,
		SELENE_VK_NUMPAD1         = 0x4F,
		SELENE_VK_NUMPAD2         = 0x50,
		SELENE_VK_NUMPAD3         = 0x51,
		SELENE_VK_NUMPAD0         = 0x52,
		SELENE_VK_DECIMAL         = 0x53,
		SELENE_VK_OEM_102         = 0x56,
		SELENE_VK_F11             = 0x57,
		SELENE_VK_F12             = 0x58,
		SELENE_VK_KANA            = 0x70,
		SELENE_VK_ABNT_C1         = 0x73,
		SELENE_VK_CONVERT         = 0x79,
		SELENE_VK_NOCONVERT       = 0x7B,
		SELENE_VK_YEN             = 0x7D,
		SELENE_VK_ABNT_C2         = 0x7E,
		SELENE_VK_NUMPADEQUALS    = 0x8D,
		SELENE_VK_PREVTRACK       = 0x90,
		SELENE_VK_NUMPADENTER     = 0x9C,
		SELENE_VK_RCONTROL        = 0x9D,
		SELENE_VK_NUMPADCOMMA     = 0xB3,
		SELENE_VK_DIVIDE          = 0xB5,
		SELENE_VK_SYSRQ           = 0xB7,
		SELENE_VK_RMENU           = 0xB8,
		SELENE_VK_PAUSE           = 0xC5,
		SELENE_VK_HOME            = 0xC7,
		SELENE_VK_UP              = 0xC8,
		SELENE_VK_PRIOR           = 0xC9,
		SELENE_VK_LEFT            = 0xCB,
		SELENE_VK_RIGHT           = 0xCD,
		SELENE_VK_END             = 0xCF,
		SELENE_VK_DOWN            = 0xD0,
		SELENE_VK_NEXT            = 0xD1,
		SELENE_VK_INSERT          = 0xD2,
		SELENE_VK_DELETE          = 0xD3,
		SELENE_VK_LWIN            = 0xDB,
		SELENE_VK_RWIN            = 0xDC,

		SELENE_VK_NONE            = 0x00000000
	};

	/**
		@brief �L�[�{�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IKeyboard
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
		virtual Uint32 Release( void )						= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void )						= 0;

		/**
			@brief �L�[���̓o�b�t�@�t���b�V��
			@author �t���`

			�L�[���̓o�b�t�@�ɒ~�ς������̓o�b�t�@���N���A���܂��B
		*/
		virtual void ClearKeyBuffer( void )					= 0;

		/**
			@brief �L�[���̓o�b�t�@����f�[�^�擾
			@author �t���`
			@return ���͂��ꂽ�L�[�̃L�[�R�[�h

			�L�[���̓o�b�t�@�ɒ~�ς��ꂽ�f�[�^�����o���܂��B<BR>
			�����ꂽ�L�[��S�Ď��o������while()�����ŏ������Ă��������B
		*/
		virtual eVirtualKeyCode GetKeyBuffer( void )		= 0;

		/**
			@brief �L�[��������Ă��邩�`�F�b�N����
			@author �t���`
			@retval false	������Ă��Ȃ�
			@retval true	������Ă���

			�w�肳�ꂽ�L�[�����݉�����Ă��邩�`�F�b�N���܂��B<BR>
			�����ɃL�[��ON/OFF�̂ݎ擾�ł��܂��B
		*/
		virtual Bool GetKeyData( eVirtualKeyCode Key )		= 0;
	};
}



namespace Selene
{
	/**
		@brief �T�E���h�Ǘ��N���X
		@author �t���`

		�T�E���h�̏������s���N���X�ł��B<BR>
		WAV/���kWAVE/OGG�̍Đ��ɑΉ����Ă��܂��B
	*/
	class ISound
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƒl
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƒl
		*/
		virtual Uint32 AddRef( void )								= 0;

		/**
			@brief �Đ�
			@author �t���`
			@param LoopCount		[in] ���[�v�J�E���g
			@param LoopInSample		[in] ���[�v��J�n�ʒu�T���v����

			�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
			���[�v���ƁA���[�v��Đ��J�n�ʒu���T���v���P�ʂŎw��ł��܂��B
		*/
		virtual void Play( Uint32 LoopCount, Uint32 LoopInSample )	= 0;

		/**
			@brief ��~
			@author �t���`

			�Đ����̃T�E���h���~���܂��B
		*/
		virtual void Stop( void )									= 0;

		/**
			@brief �ꎞ��~/����
			@author �t���`

			�Đ����̃T�E���h���ꎞ��~�A<BR>
			�ꎞ��~���̃T�E���h���Đ����܂��B
		*/
		virtual void Pause( void )									= 0;

		/**
			@brief �{�����[���ύX
			@author �t���`
			@param fVolume	[in] �{�����[���i0�`100�j

			�{�����[���̕ύX���s���܂��B
		*/
		virtual void SetVolume( Float fVolume )						= 0;

		/**
			@brief �p���ړ�
			@author �t���`
			@param fPan	[in] �p���i-100�`+100�j

			�p���̈ړ����s���܂��B
		*/
		virtual void SetPan( Float fPan )							= 0;

		/**
			@brief �Đ��`�F�b�N
			@author �t���`
			@retval false	�Đ����Ă��Ȃ�
			@retval true	�Đ����Ă���

			���ݍĐ����̃T�E���h���ǂ������ׂ܂��B
		*/
		virtual Bool IsPlay( void )									= 0;
	};
}


#endif  // ___SELENE_H___


