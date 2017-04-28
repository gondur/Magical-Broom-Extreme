

#ifndef ___SELENE__CMODELLOADER___
#define ___SELENE__CMODELLOADER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CModel;

	class CModelLoader
	{
	private:
		CModel *m_pModel;

	private:
		void Load_SMF( const Uint8 *pData, Uint32 Size );
		void Load_FRM( const Uint8 *pData, Uint32 Size, Uint32 FrameNo );
		CMesh *Load_MESH( const Uint8 *pData, Uint32 Size, Uint32 MeshNo );
		void Load_V_PC( const Uint8 *pData, Uint32 Size, CMesh *pMesh );
		void Load_V_N( const Uint8 *pData, Uint32 Size, CMesh *pMesh );
		void Load_V_B( const Uint8 *pData, Uint32 Size, CMesh *pMesh );
		void Load_V_A( const Uint8 *pData, Uint32 Size, CMesh *pMesh );
		void Load_V_UV( const Uint8 *pData, Uint32 Size, CMesh *pMesh );
		void Load_INDX( const Uint8 *pData, Uint32 Size, CMesh *pMesh );
		void Load_MTRL( const Uint8 *pData, Uint32 Size, CMesh *pMesh, Uint32 MaterialNo );

	public:
		CModelLoader( CModel *pModel );
		~CModelLoader();

		Bool LoadFromMemory( const Uint8 *pData, Uint32 Size );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CMODELLOADER___


