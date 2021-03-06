

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Object/CRenderObject.h"
#include "Render/CIndexBuffer.h"
#include "Render/CVertexBuffer.h"
#include "Render/CVertexStream.h"
#include "Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
*/
//-----------------------------------------------------------------------------------
CRenderObject::CRenderObject( CRender *pRender, CBaseMgr *pMgr ) : CDeviceObject( pMgr )
{
	m_pRender = pRender;
	m_pRender->AddRef();
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CRenderObject::~CRenderObject()
{
	SAFE_RELEASE( m_pRender );
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CRender *CRenderObject::GetRenderPointer( void ) const
{
	return m_pRender;
}
