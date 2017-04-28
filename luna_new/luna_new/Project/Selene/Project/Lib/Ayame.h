
/**
*/

#ifndef ___AYAME_H___
#define ___AYAME_H___


//====================================================================
// INCLUDE
//====================================================================
#include <windows.h>


//====================================================================
// DEFINE
//====================================================================
#define LOOP_INFINITY	(0xFFFFFFFF)


//====================================================================
// TYPEDEF
//====================================================================
// ----�݊����̂��ߎc���Ă��܂����A�g�p����Ă��܂���B
typedef void *(*AYAME_MEMORY_ALLOC_PROC)( unsigned long Size, const char *pFileName, unsigned long Line );										///< �������m�ۗp�R�[���o�b�N�֐�
typedef void (*AYAME_MEMORY_FREE_PROC)( void *pData );																							///< ����������p�R�[���o�b�N�֐�
// ----

typedef bool (*AYAME_INITIALIZE_PROC)( HWND hWnd, void **ppDirectSound, AYAME_MEMORY_ALLOC_PROC pAllocProc, AYAME_MEMORY_FREE_PROC pFreeProc );	///< �h���C�o�[������
typedef void (*AYAME_UNINITIALIZE_PROC)( void );																								///< �h���C�o�[���
typedef bool (*AYAME_GETERROR_PROC)( char *pErrStr );
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_PROC)( const char *pFileName, bool IsGlobal );													///< �h���C�o�[����I�u�W�F�N�g�擾
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_EX_PROC)( const char *pFileName, unsigned long Start, unsigned long Size, bool IsGlobal );		///< �h���C�o�[����I�u�W�F�N�g�擾
typedef class CAyame *(*AYAME_CREATE_FROM_MEMORY_PROC)( void *pData, unsigned long Size, bool IsGlobal );										///< �h���C�o�[����I�u�W�F�N�g�擾


//====================================================================
/**
	@brief	OggVorbis�Đ��p�N���X

	DLL�p�ɏ������z�֐������̒��g�̂Ȃ��N���X�ł�
*/
//====================================================================
typedef class CAyame
{
public:
	virtual bool __stdcall IsPlay( void )					= 0;	///< �Đ��`�F�b�N
	virtual bool __stdcall Play( unsigned long nLoopCount = 0, unsigned long nLoopInSample = 0 )	= 0;	///< �Đ�
	virtual bool __stdcall Loop( unsigned long nLoopCount = LOOP_INFINITY, unsigned long nLoopInSample = 0 )	= 0;	///< ���[�v�Đ�
	virtual bool __stdcall Stop( void )						= 0;	///< ��~
	virtual bool __stdcall Pause( void )					= 0;	///< �ꎞ��~
	virtual bool __stdcall SetVolume( float fParam )		= 0;	///< �{�����[���ݒ�
	virtual bool __stdcall SetPan( float fParam )			= 0;	///< �p���ݒ�
	virtual bool __stdcall Release( void )					= 0;	///< ���
	virtual bool __stdcall AddRef( void )					= 0;	///< �Q�ƃJ�E���g�C���N�������g
	virtual void __stdcall WaitEvent( void )				= 0;	///< �C�x���g�I���҂�
}
COggVorbis, *PCOggVorbis;


#endif // ___AYAME_H___


