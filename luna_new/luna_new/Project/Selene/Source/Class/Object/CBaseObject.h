

#ifndef ___SELENE__BASEOBJECT___
#define ___SELENE__BASEOBJECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CBaseList;

	class CBaseObject
	{
		friend CBaseList;

	protected:
		CBaseObject		*m_pPrev;
		CBaseObject		*m_pNext;
		CBaseObject		*m_pParent;
		CBaseObject		*m_pChild;
		CBaseObject		*m_pSibling;

		Uint32			m_RefCount;
		Uint32			m_ChildCount;

		wchar_t			m_Name[128];

	public:
		CBaseObject();
		virtual ~CBaseObject();

		Uint32 AddRef( void );
		Uint32 Release( void );

		Uint32 GetRefCount( void );
		Uint32 GetChildCount( void );

		CBaseObject *GetPrev( void );
		CBaseObject *GetNext( void );
		CBaseObject *GetChild( void );
		CBaseObject *GetParent( void );
		CBaseObject *GetSibling( void );

		void AddChild( CBaseObject *pChild );

		void SetName( const wchar_t *pName );
		void GetName( wchar_t *pName, Uint32 NameSize );
		const wchar_t *GetNamePointer( void ) const;

		Bool IsSame( const wchar_t *pName );
	};
}

#endif // ___SELENE__BASEOBJECT___


