
//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueFontSprite2D.h"

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
const Uint32 FONTSPRITE2D_MAX = 1024;

//------------------------------------------------------------------------------------------------
// VARIABLE
//------------------------------------------------------------------------------------------------
static IFontSprite2D *g_pFontSpr2DTbl[FONTSPRITE2D_MAX];


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IDevice *Lue_GetDevice( void );
extern IRender *Lue_GetRenderer( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
/**
	@brief �t�H���g�X�v���C�g�Ǘ��N���X�̏�����
	@author �t���`

	�t�H���g�X�v���C�g�Ǘ��N���X�̏��������s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Initialize( void )
{
	for ( Uint32 i = 0; i < FONTSPRITE2D_MAX; i++ )
	{
		g_pFontSpr2DTbl[i] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�H���g�X�v���C�g�Ǘ��N���X�̉��
	@author �t���`

	�t�H���g�X�v���C�g�Ǘ��N���X�̉�����s���܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Finalize( void )
{
	for ( Uint32 i = 0; i < FONTSPRITE2D_MAX; i++ )
	{
		if ( g_pFontSpr2DTbl[i] != NULL )
		{
			g_pFontSpr2DTbl[i]->Release();
			g_pFontSpr2DTbl[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------------------------
/**
	@brief ���g�p�t�H���g�X�v���C�g�̌���
	@author �t���`

	@return ���g�p�̃t�H���g�X�v���C�g�n���h��

	���g�p�̃t�H���g�X�v���C�g�I�u�W�F�N�g�̌��������܂��B<BR>
	�����̊֐��͌��J����Ă��܂���B
*/
//-----------------------------------------------------------------------------------------------
LUE_HANDLE LueFontSprite2D_SearchFreeHandle( void )
{
	for ( Uint32 i = 0; i < FONTSPRITE2D_MAX; i++ )
	{
		if ( g_pFontSpr2DTbl[i] == NULL )
		{
			return i;
		}
	}

	return INVALID_LUE_HANDLE;
}



//------------------------------------------------------------------------------------------------
/**
	@brief �t�H���g�X�v���C�g�̉��
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��

	�t�H���g�X�v���C�g�̉�����s���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Release( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;

	if ( g_pFontSpr2DTbl[Handle] != NULL )
	{
		g_pFontSpr2DTbl[Handle]->Release();
		g_pFontSpr2DTbl[Handle] = NULL;
	}
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�H���g�X�v���C�g����
	@author �t���`

	@param pBuffer		[in] �e�N�X�`���쐬�p������
	@param FontMax		[in] �t�H���g�X�v���C�g��
	@param pFontFace	[in] �t�H���g����
	@param FontSize		[in] �t�H���g�T�C�Y�i�s�N�Z��
	@param IsItalic		[in] �Α̂�ON/OFF
	@param IsBold		[in] ������ON/OFF
	@param IsAntialias	[in] �A���`�G�C���A�X��ON/OFF

	@return �t�H���g�X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	�����񂩂�t�H���g�X�v���C�g�𐶐����܂��B<BR>
	pBuffer �Ŏw�肳�ꂽ����������̑������ɉ����ăe�N�X�`���ɓW�J���܂��B<BR>
	FontMax�͍ő�`��\���ł���A�V�U�����O�Ȃǂœ����o�b�t�@��<BR>
	���N�G�X�g��葽���g���邱�Ƃ�����܂��̂ŁA���Ȃ��\���ȑ傫�����w�肵�Ă��������B
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueFontSprite2D_Create( const char *pBuffer, unsigned int FontMax, const char *pFontFace, unsigned int FontSize, eLueBool IsItalic, eLueBool IsBold, eLueBool IsAntialias )
{
	LUE_HANDLE Handle = LueFontSprite2D_SearchFreeHandle();
	if ( Handle >= FONTSPRITE2D_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp[64] = L"";
	MBCStoWCS( pFontFace, wTemp );
	wchar_t wBuffer[4096] = L"";
	MBCStoWCS( pBuffer, wBuffer );

	g_pFontSpr2DTbl[Handle] = Lue_GetRenderer()->CreateFontSprite2D( wBuffer, FontMax, wTemp, FontSize, IsItalic != LFALSE, IsBold != LFALSE, IsAntialias != LFALSE );
	if ( g_pFontSpr2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�H���g�X�v���C�g����
	@author �t���`

	@param pFileName	[in] �e�N�X�`���쐬�p������
	@param pExt			[in] �e�N�X�`���g���q�iFont_00.tga�̏ꍇ��"tga"�j
	@param FontMax		[in] �t�H���g�X�v���C�g��

	@return �t�H���g�X�v���C�g�n���h���i���s�����ꍇ��INVALID_LUE_HANDLE�j

	���O�ɍ쐬���ꂽ�t�H���g�f�[�^����t�H���g�X�v���C�g�𐶐����܂��B<BR>
	FontMax�͍ő�`��\���ł���A�V�U�����O�Ȃǂœ����o�b�t�@��<BR>
	���N�G�X�g��葽���g���邱�Ƃ�����܂��̂ŁA���Ȃ��\���ȑ傫�����w�肵�Ă��������B
*/
//------------------------------------------------------------------------------------------------
LUE_HANDLE LueFontSprite2D_CreateFromFile( const char *pFileName, const char *pExt, unsigned int FontMax )
{
	LUE_HANDLE Handle = LueFontSprite2D_SearchFreeHandle();
	if ( Handle >= FONTSPRITE2D_MAX ) return INVALID_LUE_HANDLE;

	wchar_t wTemp0[MAX_PATH] = L"";
	wchar_t wTemp1[32] = L"";
	MBCStoWCS( pFileName, wTemp0 );
	MBCStoWCS( pExt, wTemp1 );
	g_pFontSpr2DTbl[Handle] = Lue_GetRenderer()->CreateFontSprite2DFromFile( wTemp0, wTemp1, FontMax );
	if ( g_pFontSpr2DTbl[Handle] != NULL )
	{
		return Handle;
	}

	return INVALID_LUE_HANDLE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�J�n
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃt�H���g�X�v���C�g�̕`�惊�N�G�X�g���J�n���܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͏o���܂��B<BR>
	�`�惊�N�G�X�g������O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��J�n���ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Begin( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	g_pFontSpr2DTbl[Handle]->Begin();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`�惊�N�G�X�g�I��
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃt�H���g�X�v���C�g�̕`�惊�N�G�X�g���������܂��B<BR>
	����ȍ~�͕`�惊�N�G�X�g���s�����Ƃ͂ł��܂���B<BR>
	Render() ���Ăяo���O�ɂ͕K�����̊֐��Ń��N�G�X�g��Ԃ��I�����ĉ������B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_End( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	g_pFontSpr2DTbl[Handle]->End();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �`��
	@author �t���`

	@param Handle		[in] �t�H���g�X�v���C�g�n���h��

	���̊֐����Ăяo�����ƂŃ��N�G�X�g���ꂽ�t�H���g�X�v���C�g�f�[�^���`�悳��܂��B<BR>
	�f�o�C�X�ւ̕`��L���[�̒ǉ����s�������ł��̂ł��̊֐����̂͂����ɏI�����܂����A<BR>
	���ۂ̕`�悪�������Ă���킯�ł͂���܂���B<BR>
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_Rendering( LUE_HANDLE Handle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	g_pFontSpr2DTbl[Handle]->Rendering();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param x		[in] �`��X�l
	@param y		[in] �`��Y�l
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g���������t�H���g�ł̕�����`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_DrawString( LUE_HANDLE Handle, const char *pStr, int x, int y, unsigned int Color )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	g_pFontSpr2DTbl[Handle]->DrawString( Temp, CPoint2D<Sint32>(x, y), Color );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param x		[in] �`��X�l
	@param y		[in] �`��Y�l
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g�����v���|�[�V���i���t�H���g�ł̕�����`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
//------------------------------------------------------------------------------------------------
void LueFontSprite2D_DrawStringP( LUE_HANDLE Handle, const char *pStr, int x, int y, unsigned int Color )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	g_pFontSpr2DTbl[Handle]->DrawStringP( Temp, CPoint2D<Sint32>(x, y), Color );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �����`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶��
	@param Dst		[in] �`���`
	@param Color	[in] ���_�F

	�t�H���g�X�v���C�g���g���������`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
//------------------------------------------------------------------------------------------------
int LueFontSprite2D_DrawChara( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return 0;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return 0;

	wchar_t Temp[8] = L"";
	MBCStoWCS( pStr, Temp );
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	return g_pFontSpr2DTbl[Handle]->DrawChara( Temp[0], DstRc, Color );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ������`�惊�N�G�X�g
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param Dst		[in] �`���`
	@param Color	[in] ���_�F
	@param Angle	[in] 1��65536�Ƃ�����]�p�x

	�t�H���g�X�v���C�g���g������]�t��������`�揈�����s���܂��B<BR>
	���̊֐��͕`��p�̃o�b�t�@�Ƀf�[�^��ǉ����邾����<BR>
	���ۂ̕`�揈���� Render() ���Ăяo�����Ƃōs���܂��B<BR>
	�܂��K�� Begin() �� End() �̊ԂŌĂяo���悤�ɂ��Ă��������B
*/
//------------------------------------------------------------------------------------------------
int LueFontSprite2D_DrawCharaRotate( LUE_HANDLE Handle, const char *pStr, LueRect Dst, unsigned int Color, int Angle )
{
	if ( Handle >= FONTSPRITE2D_MAX ) return 0;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return 0;

	wchar_t Temp[8] = L"";
	MBCStoWCS( pStr, Temp );
	CRect2D<Sint32> DstRc( Dst.x, Dst.y, Dst.w, Dst.h );
	return g_pFontSpr2DTbl[Handle]->DrawCharaRotate( Temp[0], DstRc, Color, Angle );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ������`��ʒu�擾
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param x		[in] �`��X�l
	@param y		[in] �`��Y�l

	�t�H���g�X�v���C�g���g���������t�H���g�ł̕�����`����s������́B<BR>
	�ŏI�I�Ȉʒu���擾���܂��B<BR>
	�����ĕ������`�悷��ꍇ��A������̍����╝���擾����̂ɗL���ł��B
*/
//------------------------------------------------------------------------------------------------
LuePoint LueFontSprite2D_GetStringLastPos( LUE_HANDLE Handle, const char *pStr, int x, int y )
{
	LuePoint Pt = { 0, 0 };
	if ( Handle >= FONTSPRITE2D_MAX ) return Pt;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return Pt;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	CPoint2D<Sint32> Ret = g_pFontSpr2DTbl[Handle]->GetStringLastPos( Temp, CPoint2D<Sint32>(x, y) );
	Pt.x = Ret.x;
	Pt.y = Ret.y;

	return Pt;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ������`��ʒu�擾
	@author �t���`

	@param Handle	[in] �t�H���g�X�v���C�g�n���h��
	@param pStr		[in] �`�敶����
	@param x		[in] �`��X�l
	@param y		[in] �`��Y�l

	�t�H���g�X�v���C�g���g�����v���|�[�V���i���t�H���g�ł̕�����`����s������́B<BR>
	�ŏI�I�Ȉʒu���擾���܂��B<BR>
	�����ĕ������`�悷��ꍇ��A������̍����╝���擾����̂ɗL���ł��B
*/
//------------------------------------------------------------------------------------------------
LuePoint LueFontSprite2D_GetStringLastPosP( LUE_HANDLE Handle, const char *pStr, int x, int y )
{
	LuePoint Pt = { 0, 0 };
	if ( Handle >= FONTSPRITE2D_MAX ) return Pt;
	if ( g_pFontSpr2DTbl[Handle] == NULL ) return Pt;

	wchar_t Temp[1024] = L"";
	MBCStoWCS( pStr, Temp );
	CPoint2D<Sint32> Ret = g_pFontSpr2DTbl[Handle]->GetStringLastPosP( Temp, CPoint2D<Sint32>(x, y) );
	Pt.x = Ret.x;
	Pt.y = Ret.y;

	return Pt;
}


} // extern "C"

