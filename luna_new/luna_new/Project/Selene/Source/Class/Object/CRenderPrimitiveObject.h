

#ifndef ___SELENE__RENDERPRIMITIVEOBJECT___
#define ___SELENE__RENDERPRIMITIVEOBJECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CRenderObject.h"
#include "Object/CBaseMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CRender;
	class CVertexStream;
	class CVertexBuffer;
	class CIndexBuffer;

	class CRenderPrimitiveObject : public CRenderObject
	{
	protected:
		CIndexBuffer *m_pIB;
		CVertexStream *m_pVS;
		CVertexBuffer *m_pVB_Base;
		CVertexBuffer *m_pVB_Tex;
		CVertexBuffer *m_pVB_Light;
		CVertexBuffer *m_pVB_Bump;
		CVertexBuffer *m_pVB_Animation;

	public:
		CRenderPrimitiveObject( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CRenderPrimitiveObject();

	public:
		virtual void OnLostDevice( void )		= 0;
		virtual void OnResetDevice( void )		= 0;

	public:
		virtual Uint32 GetCount( void ) const;
		virtual Uint32 GetRequestedCount( void ) const;
	};
}

#endif // ___SELENE__RENDERPRIMITIVEOBJECT___


