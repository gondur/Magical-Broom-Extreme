

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CCore.h"
#include "Math/Vector4D.h"
#include "Render/2D/CPrimitive2DBase.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive2DBase::CPrimitive2DBase( CRender *pRender, CBaseMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
{
	m_IsScissoring	= false;
	m_ScissorX1		= 0.0f;
	m_ScissorY1		= 0.0f;
	m_ScissorX2		= 0.0f;
	m_ScissorY2		= 0.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive2DBase::~CPrimitive2DBase()
{
	wchar_t Temp[64] = L"";
	::StringCbPrintf( Temp, sizeof(Temp), L"0x%08X", (Uint64)this );
	Log_PrintTable( 0xFF0000, 0x000000, L"���", m_Name, Temp );
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
	���Z�b�g���������܂��B
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
	���X�g�A���������܂��B
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::OnResetDevice( void )
{
}

//-----------------------------------------------------------------------------------
/*
	�|���S�����V�U�����O���邽�߂̗̈��ݒ肵�܂�

	@param IsUse		[in] �g�p����Ȃ� true �^ �g�p���Ȃ��Ȃ� false
	@param pRect		[in] �V�U�����O��`�̃|�C���^
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::SetScissoring( RECT *pRect )
{
	if ( pRect != NULL )
	{
		m_IsScissoring = true;
		m_ScissorX1 = toF(pRect->left);
		m_ScissorY1 = toF(pRect->top);
		m_ScissorX2 = toF(pRect->right);
		m_ScissorY2 = toF(pRect->bottom);
	}
	else
	{
		m_IsScissoring = false;
	}
}

//-----------------------------------------------------------------------------------
/**
	�V�U�����O���̒��_�f�[�^���Ԃ��܂�

	@param pPtIn1	[in] ���̓|�C���g�P�A�h���X
	@param pPtIn2	[in] ���̓|�C���g�Q�A�h���X
	@param pPtOut	[out] �o�̓|�C���g�A�h���X
	@param fAve		[in] ���d�l
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::SetVertexLinear( SVertex2D *pPtIn1, SVertex2D *pPtIn2, SVertex2D *pPtOut, Float fAve )
{
	pPtOut->Pos.x = pPtIn1->Pos.x + ((pPtIn2->Pos.x - pPtIn1->Pos.x) * fAve);
	pPtOut->Pos.y = pPtIn1->Pos.y + ((pPtIn2->Pos.y - pPtIn1->Pos.y) * fAve);
	pPtOut->Pos.z = pPtIn1->Pos.z + ((pPtIn2->Pos.z - pPtIn1->Pos.z) * fAve);
	pPtOut->Pos.w = pPtIn1->Pos.w + ((pPtIn2->Pos.w - pPtIn1->Pos.w) * fAve);

	pPtOut->Col.a = (Uint8)(toF(pPtIn1->Col.a) + (toF(pPtIn2->Col.a - pPtIn1->Col.a) * fAve));
	pPtOut->Col.r = (Uint8)(toF(pPtIn1->Col.r) + (toF(pPtIn2->Col.r - pPtIn1->Col.r) * fAve));
	pPtOut->Col.g = (Uint8)(toF(pPtIn1->Col.g) + (toF(pPtIn2->Col.g - pPtIn1->Col.g) * fAve));
	pPtOut->Col.b = (Uint8)(toF(pPtIn1->Col.b) + (toF(pPtIn2->Col.b - pPtIn1->Col.b) * fAve));
}

//-----------------------------------------------------------------------------------
/**
	�V�U�����O���̒��_�f�[�^���Ԃ��܂�

	@param pPtIn1	[in] ���̓|�C���g�P�A�h���X
	@param pPtIn2	[in] ���̓|�C���g�Q�A�h���X
	@param pPtOut	[out] �o�̓|�C���g�A�h���X
	@param fAve		[in] ���d�l
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::SetVertexLinear( SVertex2DTex *pPtIn1, SVertex2DTex *pPtIn2, SVertex2DTex *pPtOut, Float fAve )
{
	pPtOut->Pos.x = pPtIn1->Pos.x + ((pPtIn2->Pos.x - pPtIn1->Pos.x) * fAve);
	pPtOut->Pos.y = pPtIn1->Pos.y + ((pPtIn2->Pos.y - pPtIn1->Pos.y) * fAve);
	pPtOut->Pos.z = pPtIn1->Pos.z + ((pPtIn2->Pos.z - pPtIn1->Pos.z) * fAve);
	pPtOut->Pos.w = pPtIn1->Pos.w + ((pPtIn2->Pos.w - pPtIn1->Pos.w) * fAve);
	pPtOut->Tex.x = pPtIn1->Tex.x + ((pPtIn2->Tex.x - pPtIn1->Tex.x) * fAve);
	pPtOut->Tex.y = pPtIn1->Tex.y + ((pPtIn2->Tex.y - pPtIn1->Tex.y) * fAve);

	pPtOut->Col.a = (Uint8)(toF(pPtIn1->Col.a) + (toF(pPtIn2->Col.a - pPtIn1->Col.a) * fAve));
	pPtOut->Col.r = (Uint8)(toF(pPtIn1->Col.r) + (toF(pPtIn2->Col.r - pPtIn1->Col.r) * fAve));
	pPtOut->Col.g = (Uint8)(toF(pPtIn1->Col.g) + (toF(pPtIn2->Col.g - pPtIn1->Col.g) * fAve));
	pPtOut->Col.b = (Uint8)(toF(pPtIn1->Col.b) + (toF(pPtIn2->Col.b - pPtIn1->Col.b) * fAve));
}

