

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Object/CDeviceObjectMgr.h"
#include "Object/CDeviceObject.h"

using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDeviceObjectMgr::CDeviceObjectMgr( CDevice *pDevice ) : CBaseMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CDeviceObjectMgr::~CDeviceObjectMgr()
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDeviceObjectMgr::OnLostDevice( void )
{
	CBaseObject *pObj = GetTop();
	while ( pObj != NULL )
	{
		((CDeviceObject*)pObj)->OnLostDevice();

		pObj = GetNext( pObj );
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDeviceObjectMgr::OnResetDevice( void )
{
	CBaseObject *pObj = GetTop();
	while ( pObj != NULL )
	{
		((CDeviceObject*)pObj)->OnResetDevice();

		pObj = GetNext( pObj );
	}
}

