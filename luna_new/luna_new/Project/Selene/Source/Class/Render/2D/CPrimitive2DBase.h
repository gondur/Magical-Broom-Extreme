

#ifndef ___SELENE__PRIMITIVE2DBASE___
#define ___SELENE__PRIMITIVE2DBASE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CRenderPrimitiveObject.h"
#include "Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CPrimitive2DBaseMgr;

	/**
		@brief �v���~�e�B�u�N���X

		�Q�c���ʏ�ɒP��̃|���S����`�悷�邽�߂̃N���X�ł��B
		���̃N���X���g�͒P���ȃ|���S����`�悷�邾���̂��̂ł����A
		SeleneEffect�N���X��SeleneSprite�N���X����舵���₷���悤��
		���b�p�[�ɂȂ��Ă���A���ڂ��̃N���X���g�p����̂�
		�Â����G�t�F�N�g���g�p�������Ƃ��Ȃǂ����ɂȂ�Ǝv���܂��B
	*/
	class CPrimitive2DBase : public CRenderPrimitiveObject
	{
		friend CPrimitive2DBaseMgr;

	protected:
		Bool m_IsScissoring;							///< �V�U�����O���s�����ۂ�
		Float m_ScissorX1;								///< �V�U�����O�����E
		Float m_ScissorY1;								///< �V�U�����O�㋫�E
		Float m_ScissorX2;								///< �V�U�����O�E���E
		Float m_ScissorY2;								///< �V�U�����O�����E

	protected:
		CPrimitive2DBase( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CPrimitive2DBase();

	protected:
		void SetVertexLinear( SVertex2D *pPtIn1, SVertex2D *pPtIn2, SVertex2D *pPtOut, Float Ave );
		void SetVertexLinear( SVertex2DTex *pPtIn1, SVertex2DTex *pPtIn2, SVertex2DTex *pPtOut, Float Ave );

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual void Begin( void )								= 0;
		virtual void End( void )								= 0;
		virtual void Rendering( void )							= 0;

	public:
		virtual void SetScissoring( RECT *pRect );
	};
}

#endif // ___SELENE__PRIMITIVE2DBASE___


