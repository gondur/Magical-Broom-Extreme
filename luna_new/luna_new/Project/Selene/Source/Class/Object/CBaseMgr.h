

#ifndef ___SELENE__BASEMGR___
#define ___SELENE__BASEMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"
#include "Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CDevice;
	class CGraphicCard;
	class CCore;

	/**
		@brief オブジェクト管理クラス

		ゲーム内の各種オブジェクトと管理するためのクラスです。
	*/
	class CBaseMgr : public CBaseList
	{
	protected:
		CDevice *m_pDevice;

	public:
		CBaseMgr( CDevice *pDevice );
		virtual ~CBaseMgr();

		virtual CDevice *GetDevicePointer( void ) const;
		virtual CGraphicCard *GetGraphicCardPointer( void ) const;
		virtual CCore *GetCorePointer( void ) const;
		virtual HWND GetWindow( void ) const;

	public:
		virtual void OnLostDevice( void ){}
		virtual void OnResetDevice( void ){}
	};
}

#endif // ___SELENE__BASEMGR___

