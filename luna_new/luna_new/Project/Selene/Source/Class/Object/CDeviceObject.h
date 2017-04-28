

#ifndef ___SELENE__DEVICEOBJECT___
#define ___SELENE__DEVICEOBJECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"
#include "Object/CBaseMgr.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CDevice;
	class CGraphicCard;
	class CCore;

	/**
		@brief �I�u�W�F�N�g�Ǘ��N���X

		�Q�[�����̊e��I�u�W�F�N�g�ƊǗ����邽�߂̃N���X�ł��B

	*/
	class CDeviceObject : public CBaseObject
	{
	protected:
		CBaseMgr *m_pManager;

	public:
		CDeviceObject( CBaseMgr *pMgr );
		virtual ~CDeviceObject();

	public:
		virtual void OnLostDevice( void )	= 0;
		virtual void OnResetDevice( void )	= 0;

	public:
		virtual wchar_t *GetError( HRESULT hr );
		virtual CDevice *GetDevicePointer( void ) const;
		virtual CGraphicCard *GetGraphicCardPointer( void ) const;
		virtual CCore *GetCorePointer( void ) const;
		virtual HWND GetWindow( void ) const;
		virtual CPoint2D<Uint32> GetTextureMaxSize( void );
	};
}

#endif // ___SELENE__DEVICEOBJECT___


