

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
		@brief プリミティブクラス

		２Ｄ平面状に単一のポリゴンを描画するためのクラスです。
		このクラス自身は単純なポリゴンを描画するだけのものですが、
		SeleneEffectクラスやSeleneSpriteクラスがより扱いやすいような
		ラッパーになっており、直接このクラスを使用するのは
		凝ったエフェクトを使用したいときなどだけになると思います。
	*/
	class CPrimitive2DBase : public CRenderPrimitiveObject
	{
		friend CPrimitive2DBaseMgr;

	protected:
		Bool m_IsScissoring;							///< シザリングを行うか否か
		Float m_ScissorX1;								///< シザリング左境界
		Float m_ScissorY1;								///< シザリング上境界
		Float m_ScissorX2;								///< シザリング右境界
		Float m_ScissorY2;								///< シザリング下境界

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


