
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LuePointPrimitive2D.h"

//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;

//------------------------------------------------------------------------------------------------
// for C Compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------------------
const unsigned int POINTPRIMITIVE2D_MAX = 1024;


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static IPointPrimitive2D *g_pPrim2DTbl[POINTPRIMITIVE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );


//------------------------------------------------------------------------------------------------
/**
	@brief �|�C���g�v���~�e�B�u�Ǘ��N���X�̏�����
	@author �t���`

	�|�C���g�v���~�e�B�u�Ǘ��N���X�̏��������s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Initialize( void )
{
	for ( Uint32 i = 0; i < POINTPRIMITIVE2D_MAX; i++ )
	{
		g_pPrim2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �|�C���g�v���~�e�B�u�Ǘ��N���X�̉��
	@author �t���`

	�|�C���g�v���~�e�B�u�Ǘ��N���X�̉�����s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Finalize( void )
{
	for ( Uint32 i = 0; i < POINTPRIMITIVE2D_MAX; i++ )
	{
		if ( g_pPrim2DTbl[i] != NULL )
		{
			g_pPrim2DTbl[i]->Release();
			g_pPrim2DTbl[i] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ���g�p�|�C���g�v���~�e�B�u�̌���
	@author �t���`

	@return ���g�p�̃|�C���g�v���~�e�B�u�n���h��

	���g�p�̃|�C���g�v���~�e�B�u�I�u�W�F�N�g�̌��������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LuePointPrimitive2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < POINTPRIMITIVE2D_MAX; i++ )
	{
		if ( g_pPrim2DTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �|�C���g�v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] �|�C���g�v���~�e�B�u�n���h��

	�|�C���g�v���~�e�B�u�̉�����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;

	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		g_pPrim2DTbl[Handle]->Release();
		g_pPrim2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �|�C���g�v���~�e�B�u����
	@author �t���`

	@param PrimitiveMax		[in] �|�C���g�v���~�e�B�u�ő吔

	@return �|�C���g�v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�|�C���g�v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł��B
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LuePointPrimitive2D_Create( unsigned int PrimitiveMax )
{
	LUE_HANDLE Handle = LuePointPrimitive2D_SearchFreeHandle();
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pPrim2DTbl[Handle] = Lue_GetRenderer()->CreatePointPrimitive2D( PrimitiveMax );
	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�|�C���g�v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ|�C���g�v���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ|�C���g�v���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LuePointPrimitive2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] �|�C���g�v���~�e�B�u�n���h��
	@param pPrimitive	[in] �|�C���g�v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`��|�C���g�v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
//------------------------------------------------------------------------------------------------
eLueBool LuePointPrimitive2D_Push( LUE_HANDLE Handle, LueVertex2D *pPrimitive, unsigned int Count )
{
	if ( Handle >= POINTPRIMITIVE2D_MAX ) return LFALSE;
	if ( g_pPrim2DTbl[Handle] == NULL ) return LFALSE;

	return g_pPrim2DTbl[Handle]->Push( (SVertex2D*)pPrimitive, Count ) ? LTRUE : LFALSE;
}


} // extern "C"

