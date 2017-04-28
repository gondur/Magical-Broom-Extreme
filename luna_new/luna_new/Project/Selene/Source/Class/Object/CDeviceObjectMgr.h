

#ifndef ___SELENE__DEVICEOBJECTMGR___
#define ___SELENE__DEVICEOBJECTMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CDevice;
	class CDeviceObject;

	/**
		@brief オブジェクト管理クラス

		ゲーム内の各種オブジェクトと管理するためのクラスです。
	*/
	class CDeviceObjectMgr : public CBaseMgr
	{
	public:
		CDeviceObjectMgr( CDevice *pDevice );
		virtual ~CDeviceObjectMgr();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );
	};
}

#endif // ___SELENE__DEVICEOBJECTMGR___

