

#ifndef ___SELENE__NULLMODEL___
#define ___SELENE__NULLMODEL___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/Model/IModel.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullModel : public IModel
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Uint32 Release( void ) 
		{
			return 0;
		}
	
		virtual Uint32 AddRef( void	)
		{
			return 0;
		}

		virtual void SetTransform( CStyle &Style )
		{
		}

		virtual void Rendering( void )
		{
		}

		virtual Bool GetFrame( Uint32 FrameIndex, IFrame *&pFrame )
		{
			pFrame = NULL;
			return false;
		}

		virtual Uint32 GetFrameCount( void )
		{
			return 0;
		}

		virtual Bool GetMesh( Uint32 MeshIndex, IMesh *&pMesh )
		{
			pMesh = NULL;
			return false;
		}

		virtual Uint32 GetMeshCount( void )
		{
			return 0;
		}
	};
}


#endif // ___SELENE__NULLMODEL___

