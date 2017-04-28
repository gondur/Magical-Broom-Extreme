

#ifndef ___SELENE__NULLPRIMITIVE3D___
#define ___SELENE__NULLPRIMITIVE3D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/3D/IPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class NullPrimitive3D : public IPrimitive3D
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

		virtual Sint32 Rendering( void )
		{
			return -1;
		}

		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count )
		{
			return false;
		}

		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count )
		{
			return false;
		}

		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count )
		{
			return false;
		}

		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count )
		{
			return false;
		}

		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count )
		{
			return false;
		}

		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount )
		{
			return false;
		}

		virtual Bool Get( SVertex3DBase &Vtx, Uint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DTexture &Vtx, Uint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DLight &Vtx, Uint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DBump &Vtx, Uint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DAnimation &Vtx, Uint32 Index )
		{
			return false;
		}

		virtual Uint32 GetVertexCount( void )
		{
			return 0;
		}

		virtual Uint32 GetIndexCount( void )
		{
			return 0;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void SetBoneCount( Sint32 BoneCount )
		{
		}

		virtual void SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix )
		{
		}

		virtual void SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix )
		{
		}

		virtual void SetTransform( CStyle &Style )
		{
		}

		virtual void SetMaterialColor( CColor Color )
		{
		}

		virtual void SetSpecularColor( CColor Color )
		{
		}

		virtual void SetSpecularRefractive( Float fRefractive )
		{
		}

		virtual void SetSpecularRoughly( Float fRoughly )
		{
		}
	};
}


#endif // ___SELENE__NULLPRIMITIVE3D___


