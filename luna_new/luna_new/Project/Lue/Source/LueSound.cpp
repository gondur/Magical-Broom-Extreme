

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueSound.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// PROTOTYPE
//------------------------------------------------------------------------------------------------
extern ICore *Lue_GetCore( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const Uint32 SOUND_MAX = 1024;


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ISound *g_pSound[SOUND_MAX];


//------------------------------------------------------------------------------------------------
/**
	@brief �T�E���h�����̏�����
	@author �t���`

	@param hWnd		[in] ���C���E�B���h�E�̃E�B���h�E�n���h��

	�T�E���h�����̏����������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Initialize( void )
{
	for ( Sint32 i = 0; i < SOUND_MAX; i++ )
	{
		g_pSound[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �T�E���h�����̉��
	@author �t���`

	�T�E���h�����̉�������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Finalize( void )
{
	for ( Sint32 i = 0; i < SOUND_MAX; i++ )
	{
		if ( g_pSound[i] != NULL )
		{
			g_pSound[i]->Release();
			g_pSound[i] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ���g�p�T�E���h�̌���
	@author �t���`

	@return ���g�p�̃T�E���h�n���h��

	���g�p�̃T�E���h�I�u�W�F�N�g�̌��������܂��B
	�����̊֐��͌��J����Ă��܂���B
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueSound_SearchFreeHandle( void )
{
	for ( Sint32 i = 0; i < SOUND_MAX; i++ )
	{
		if ( g_pSound[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C������T�E���h��ǂݍ��݁A<BR>
	���̃T�E���h�̃n���h�����擾���܂��B
	@author �t���`

	@param pFileName	[in] �t�@�C����
	@param IsAllActive	[in] LTRUE �ɂ���ƃE�B���h�E����A�N�e�B�u�ł���~���Ȃ�

	@return ���g�p�̃T�E���h�n���h��

	�T�E���h�t�@�C����ǂݍ��݁A���̃T�E���h�̑���p�̃n���h�����擾���܂��B<BR>
	�擾�����T�E���h�͕s�v�ɂȂ����������ĉ������B
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueSound_CreateFromFile( const char *pFileName, eLueBool IsAllActive )
{
	LUE_HANDLE Handle = LueSound_SearchFreeHandle();
	if ( Handle >= SOUND_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFileName, wTemp );
	g_pSound[Handle] = Lue_GetCore()->CreateSoundFromFile( wTemp, IsAllActive != LFALSE );
	if ( g_pSound[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �T�E���h��������܂��B
	@author �t���`

	@param Handle	[in] �T�E���h�n���h��

	�ǂݍ��񂾃T�E���h�����������������܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Release( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Release();
	g_pSound[Handle] = NULL;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �T�E���h���Đ��J�n
	@author �t���`

	@param Handle	[in] �T�E���h�n���h��

	�ǂݍ��񂾃T�E���h�����������������܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Play( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Play( 0, 0 );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �T�E���h�����[�v�Đ��J�n
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��
	@param LoopCount	[in] ���[�v��<BR>�������[�v�̏ꍇ�� SOUND_LOOP_INFINITY ���w��B
	@param LoopSample	[in] ���[�v�J�n�ʒu�i�T���v�����O���Ŏw��j

	�T�E���h�̃��[�v�Đ����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Loop( LUE_HANDLE Handle, unsigned int LoopCount, unsigned int LoopSample )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Play( LoopCount, LoopSample );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��

	�Đ����̃T�E���h���~���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Stop( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Stop();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��

	�Đ����̃T�E���h���~���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_Pause( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->Pause();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��
	@param fParam		[in] �{�����[���l(+0�`+100)

	�Đ����̃T�E���h���~���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_SetVolume( LUE_HANDLE Handle, float fParam )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->SetVolume( fParam );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �Đ����̃T�E���h���~
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��
	@param fParam		[in] �p���l(-100�`+100)

	�Đ����̃T�E���h���~���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueSound_SetPan( LUE_HANDLE Handle, float fParam )
{
	if ( Handle >= SOUND_MAX ) return;
	if ( g_pSound[Handle] == NULL ) return;

	g_pSound[Handle]->SetPan( fParam );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �T�E���h���Đ����ł��邩�`�F�b�N
	@author �t���`

	@param Handle		[in] �T�E���h�n���h��

	@retval true		�Đ����i�ꎞ��~�܂ށj
	@retval false		��~��

	�Đ����̃T�E���h�ł��邩�ǂ����𒲂ׂ܂��B
*/
//------------------------------------------------------------------------------------------------
eLueBool LueSound_IsPlay( LUE_HANDLE Handle )
{
	if ( Handle >= SOUND_MAX ) return LFALSE;
	if ( g_pSound[Handle] == NULL ) return LFALSE;

	return g_pSound[Handle]->IsPlay() ? LTRUE : LFALSE;
}


} // extern "C"

