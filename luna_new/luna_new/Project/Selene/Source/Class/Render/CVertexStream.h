

#ifndef ___SELENE__VERTEXSTREAM___
#define ___SELENE__VERTEXSTREAM___


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
	class CVertexStream : public CDeviceObject
	{
	private:
		IDirect3DVertexDeclaration9 *m_pDeclaration;

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		CVertexStream( CBaseMgr *pMgr );
		virtual ~CVertexStream();

		virtual Bool Create( const D3DVERTEXELEMENT9 *pElements );
		virtual HRESULT SetDevice( void );
	};
}

#endif // ___SELENE__VERTEXSTREAM___


