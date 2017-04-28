

#ifndef ___SELENE__VERTEXBUFFER___
#define ___SELENE__VERTEXBUFFER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CVertexBuffer : public CDeviceObject
	{
	public:
		IDirect3DVertexBuffer9 *m_pBuffer;
		void *m_pVertex;
		Uint32 m_VertexSize;
		Uint32 m_MaxCount;
		Uint32 m_Offset;
		Uint32 m_RequestedCount;
		Bool m_IsDynamic;

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		CVertexBuffer( CBaseMgr *pMgr );
		virtual ~CVertexBuffer();

		virtual void Update( void );
		virtual void Flush( void );
		virtual Bool Push( void *pVtx, Uint32 Count );
		virtual Bool Get( void *pVtx, Uint32 Index );

		virtual Uint32 GetCount( void ) const;
		virtual Uint32 GetRequestedCount( void ) const;

		virtual Bool Create( Uint32 Count, Uint32 VertexSize, Bool IsDynamic );
		virtual HRESULT SetDevice( Uint32 StreamNo );
	};
}

#endif // ___SELENE__VERTEXBUFFER___


