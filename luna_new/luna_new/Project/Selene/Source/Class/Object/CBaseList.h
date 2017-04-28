

#ifndef ___SELENE__BASELIST___
#define ___SELENE__BASELIST___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �I�u�W�F�N�g�Ǘ��N���X

		�Q�[�����̊e��I�u�W�F�N�g�ƊǗ����邽�߂̃N���X�ł��B

		@todo	------------------------
		@bug	------------------------
	*/
	class CBaseList : public CBaseObject
	{
	protected:
		CBaseObject	*m_pTop;
		CBaseObject	*m_pEnd;
		Uint32		m_Count;

	public:
		CBaseList();
		virtual ~CBaseList();

		void Init( void );
		void InsertTop( CBaseObject *pObj );
		void InsertEnd( CBaseObject *pObj );
		void Erase( CBaseObject *pObj );
		CBaseObject *GetTop( void );
		CBaseObject *GetEnd( void );
		CBaseObject *GetPrev( CBaseObject *pObj );
		CBaseObject *GetNext( CBaseObject *pObj );
		CBaseObject *GetByIndex( Uint32 Index );
		Uint32 GetCount( void );
		CBaseObject *SearchFromName( const wchar_t *pName );
	};
}

#endif // ___SELENE__BASELIST___


