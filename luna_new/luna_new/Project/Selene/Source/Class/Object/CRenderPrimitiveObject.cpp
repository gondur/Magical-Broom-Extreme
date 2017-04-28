

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Object/CRenderPrimitiveObject.h"
#include "Render/CIndexBuffer.h"
#include "Render/CVertexBuffer.h"
#include "Render/CVertexStream.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
*/
//-----------------------------------------------------------------------------------
CRenderPrimitiveObject::CRenderPrimitiveObject( CRender *pRender, CBaseMgr *pMgr ) : CRenderObject( pRender, pMgr )
	, m_pIB				( NULL )
	, m_pVS				( NULL )
	, m_pVB_Base		( NULL )
	, m_pVB_Tex			( NULL )
	, m_pVB_Light		( NULL )
	, m_pVB_Bump		( NULL )
	, m_pVB_Animation	( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CRenderPrimitiveObject::~CRenderPrimitiveObject()
{
	SAFE_RELEASE( m_pIB );
	SAFE_RELEASE( m_pVS );
	SAFE_RELEASE( m_pVB_Base );
	SAFE_RELEASE( m_pVB_Tex );
	SAFE_RELEASE( m_pVB_Light );
	SAFE_RELEASE( m_pVB_Bump );
	SAFE_RELEASE( m_pVB_Animation );
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
Uint32 CRenderPrimitiveObject::GetCount( void ) const
{
	return m_pVB_Base->GetCount();
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
Uint32 CRenderPrimitiveObject::GetRequestedCount( void ) const
{
	return m_pVB_Base->GetRequestedCount();
}

