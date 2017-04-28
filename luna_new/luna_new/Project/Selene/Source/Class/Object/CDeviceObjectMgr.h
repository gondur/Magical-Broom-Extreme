

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
		@brief �I�u�W�F�N�g�Ǘ��N���X

		�Q�[�����̊e��I�u�W�F�N�g�ƊǗ����邽�߂̃N���X�ł��B
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

