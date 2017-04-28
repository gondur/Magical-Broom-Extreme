

#ifndef ___SELENE__COCCLUSION___
#define ___SELENE__COCCLUSION___


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
	class CDevice;

	class COcclusion : public CBaseObject
	{
		friend CDevice;

	protected:
		IDirect3DQuery9 *m_pQuery;

	private:
		COcclusion( CDevice *pDevice );
		virtual ~COcclusion();

	public:
		virtual void Begin( void );
		virtual void End( void );
		virtual Uint32 GetPixels( void );
	};
}


#endif // ___SELENE__COCCLUSION___

