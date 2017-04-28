

#ifndef ___SELENE__CFRAME___
#define ___SELENE__CFRAME___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Object/CBaseObject.h"
#include "Object/CBaseList.h"
#include "Scene/CSceneManager.h"
#include "Math/Style.h"
#include "Interface/Render/Model/IFrame.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CMesh;

	class CFrame : public CStyle, public IFrame, public CBaseObject
	{
	private:
		CMatrix m_mParent;
		CBaseList m_Child;
		CMesh *m_pMesh;
		CMatrix m_mWorld;

	public:
		CFrame();
		virtual ~CFrame();

		virtual void ConnectChildFrame( CFrame *pFrame );
		virtual void ConnectMesh( CMesh *pMesh );

		virtual void SetParentMatrix( CMatrix &mParent );

		virtual void GetTransform( CMatrix &Mtx );
		virtual void GetTransformInverse( CMatrix &Mtx );

		virtual void UpdateTransform( CMatrix &mWorld );

		virtual void Rendering( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CFRAME___


