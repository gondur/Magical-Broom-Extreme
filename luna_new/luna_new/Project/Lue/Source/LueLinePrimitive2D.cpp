
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueLinePrimitive2D.h"

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
const unsigned int LINEPRIMITIVE2D_MAX = 1024;


//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static ILinePrimitive2D *g_pPrim2DTbl[LINEPRIMITIVE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );


//------------------------------------------------------------------------------------------------
/**
	@brief ���C���v���~�e�B�u�Ǘ��N���X�̏�����
	@author �t���`

	���C���v���~�e�B�u�Ǘ��N���X�̏��������s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Initialize( void )
{
	for ( Uint32 i = 0; i < LINEPRIMITIVE2D_MAX; i++ )
	{
		g_pPrim2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ���C���v���~�e�B�u�Ǘ��N���X�̉��
	@author �t���`

	���C���v���~�e�B�u�Ǘ��N���X�̉�����s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Finalize( void )
{
	for ( Uint32 i = 0; i < LINEPRIMITIVE2D_MAX; i++ )
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
	@brief ���g�p���C���v���~�e�B�u�̌���
	@author �t���`

	@return ���g�p�̃��C���v���~�e�B�u�n���h��

	���g�p�̃��C���v���~�e�B�u�I�u�W�F�N�g�̌��������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueLinePrimitive2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < LINEPRIMITIVE2D_MAX; i++ )
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
	@brief ���C���v���~�e�B�u�̉��
	@author �t���`

	@param Handle	[in] ���C���v���~�e�B�u�n���h��

	���C���v���~�e�B�u�̉�����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;

	if ( g_pPrim2DTbl[Handle] != NULL )
	{
		g_pPrim2DTbl[Handle]->Release();
		g_pPrim2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief ���C���v���~�e�B�u����
	@author �t���`

	@param PrimitiveMax		[in] ���C���v���~�e�B�u�ő吔

	@return ���C���v���~�e�B�u�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	���C���v���~�e�B�u�I�u�W�F�N�g�̐������s���܂��B<BR>
	PrimitiveMax �͓����Ŋm�ۂ����o�b�t�@�̃T�C�Y�ł��B
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueLinePrimitive2D_Create( unsigned int PrimitiveMax )
{
	LUE_HANDLE Handle = LueLinePrimitive2D_SearchFreeHandle();
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return INVALID_LUE_HANDLE;

	g_pPrim2DTbl[Handle] = Lue_GetRenderer()->CreateLinePrimitive2D( PrimitiveMax );
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

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ���C���v���~�e�B�u�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��C���v���~�e�B�u�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��

	���̊֐����Ăяo�����ƂŃ��C���v���~�e�B�u�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LueLinePrimitive2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return;
	if ( g_pPrim2DTbl[Handle] == NULL ) return;

	g_pPrim2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g
	@author �t���`

	@param Handle		[in] ���C���v���~�e�B�u�n���h��
	@param pPrimitive	[in] ���C���v���~�e�B�u���_�f�[�^
	@param Count		[in] pPrimitive�̐�

	@retval LTRUE	����ɒǉ��ł���
	@retval LFALSE	�ǉ��ł��Ȃ������i�o�b�t�@�I�[�o�[�t���[

	�`�惉�C���v���~�e�B�u���_��ǉ����܂��B<BR>
	�K�� Begin() �� End() �̊ԂŌĂ�ł��������B<BR>
	���̊֐��͎��ۂɕ`����s���܂���<BR>
	�o�b�t�@�ɒǉ����邾���Ŏ��ۂ̕`��� Render() ���ɍs���܂��B
*/
//------------------------------------------------------------------------------------------------
eLueBool LueLinePrimitive2D_Push( LUE_HANDLE Handle, LueLinePrimitiveVertex2D *pPrimitive, unsigned int Count )
{
	if ( Handle >= LINEPRIMITIVE2D_MAX ) return LFALSE;
	if ( g_pPrim2DTbl[Handle] == NULL ) return LFALSE;

	return g_pPrim2DTbl[Handle]->Push( (SLineVertex2D*)pPrimitive, Count ) ? LTRUE : LFALSE;
}


} // extern "C"

