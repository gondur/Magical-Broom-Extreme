

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "File/CFileManager.h"
#include "Render/Model/CModel.h"
#include "Render/Model/CModelLoader.h"
#include "Render/Model/CFrame.h"
#include "Render/Model/CMesh.h"
#include "Render/Model/CMaterial.h"
#include "Surface/CTexture.h"
#include "Common/SMF.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModelLoader::CModelLoader( CModel *pModel )
{
	m_pModel = pModel;
	m_pModel->AddRef();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModelLoader::~CModelLoader()
{
	SAFE_RELEASE( m_pModel );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelLoader::LoadFromMemory( const Uint8 *pData, Uint32 Size )
{
	Uint32 Pos			= 0;
	Uint32 FrameNo		= 0;
	Uint32 MeshNo		= 0;
	Uint32 MaterialNo	= 0;
	CMesh *pLastMesh	= NULL;

	//--------------------------------------------------------------------
	// データ取得ループ
	//--------------------------------------------------------------------
	while ( Pos < Size )
	{
		// チャンク取得
		SMF_CHUNK *pChunk = (SMF_CHUNK*)pData;
		pData += sizeof(SMF_CHUNK);
		Pos += sizeof(SMF_CHUNK);

		// チャンク解析
		switch ( pChunk->Chunk )
		{
		case 'SMF':  //------------------------------------ ファイルヘッダ
			Load_SMF( pData, pChunk->Size );
			break;
		case 'FRM':  //------------------------------------ フレーム
			Load_FRM( pData, pChunk->Size, FrameNo++ );
			break;
		case 'MESH': //------------------------------------ メッシュ
			pLastMesh = Load_MESH( pData, pChunk->Size, MeshNo++ );
			MaterialNo = 0;
			break;
		case 'BONE': //------------------------------------ ボーン
			//Load_BONE( pData, pChunk->Size, pLastMesh );
			break;
		case 'V_PC': //------------------------------------ 頂点：位置＋色
			Load_V_PC( pData, pChunk->Size, pLastMesh );
			break;
		case 'V_N':  //------------------------------------ 頂点：法線
			Load_V_N( pData, pChunk->Size, pLastMesh );
			break;
		case 'V_B':  //------------------------------------ 頂点：接線
			Load_V_B( pData, pChunk->Size, pLastMesh );
			break;
		case 'V_A':  //------------------------------------ 頂点：ウェイト＋インデックス
			Load_V_A( pData, pChunk->Size, pLastMesh );
			break;
		case 'V_UV': //------------------------------------ 頂点：テクスチャUV
			Load_V_UV( pData, pChunk->Size, pLastMesh );
			break;
		case 'INDX': //------------------------------------ インデックス
			Load_INDX( pData, pChunk->Size, pLastMesh );
			break;
		case 'MTRL': //------------------------------------ マテリアル
			Load_MTRL( pData, pChunk->Size, pLastMesh, MaterialNo++ );
			break;
		}

		// チャンクサイズ分進める
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}

	//--------------------------------------------------------------------
	// メッシュのアップデート
	//--------------------------------------------------------------------
	m_pModel->UpdateMesh();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_SMF( const Uint8 *pData, Uint32 Size )
{
	SMF_FILEHEAD Head;
	MemoryCopy( &Head, pData, sizeof(SMF_FILEHEAD) );

	// メッシュとフレームを生成
	m_pModel->CreateFrameList( Head.FrameCount );
	m_pModel->CreateMeshList( Head.MeshCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_FRM( const Uint8 *pData, Uint32 Size, Uint32 FrameNo )
{
	SMF_FRAMEDATA Frame;
	MemoryCopy( &Frame, pData, sizeof(SMF_FRAMEDATA) );

	CFrame *pFrame = m_pModel->GetFramePointer( FrameNo );
	// 名称
	wchar_t Temp[256];
	MBCStoWCS( Frame.Name, Temp );
	pFrame->SetName( Temp );
	// トランスフォームマトリックス
	CMatrix mTemp(
				Frame.mTransform.x.x, Frame.mTransform.x.y, Frame.mTransform.x.z, Frame.mTransform.x.w,
				Frame.mTransform.y.x, Frame.mTransform.y.y, Frame.mTransform.y.z, Frame.mTransform.y.w,
				Frame.mTransform.z.x, Frame.mTransform.z.y, Frame.mTransform.z.z, Frame.mTransform.z.w,
				Frame.mTransform.w.x, Frame.mTransform.w.y, Frame.mTransform.w.z, Frame.mTransform.w.w );
	pFrame->SetParentMatrix( mTemp );
	// メッシュ
	if ( Frame.MeshNo != -1 )
	{
		pFrame->ConnectMesh( m_pModel->GetMeshPointer( Frame.MeshNo ) );
		m_pModel->GetMeshPointer( Frame.MeshNo )->SetParentFrame( pFrame );
	}
	// フレーム
	if ( Frame.ParentFrameNo != -1 )
	{
		m_pModel->GetFramePointer( Frame.ParentFrameNo )->ConnectChildFrame( pFrame );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh *CModelLoader::Load_MESH( const Uint8 *pData, Uint32 Size, Uint32 MeshNo )
{
	SMF_MESHDATA Mesh;
	MemoryCopy( &Mesh, pData, sizeof(SMF_MESHDATA) );

	CMesh *pMesh = m_pModel->GetMeshPointer( MeshNo );
	// 名称
	wchar_t Temp[256];
	MBCStoWCS( Mesh.Name, Temp );
	pMesh->SetName( Temp );
	// マテリアル
	pMesh->CreateMaterialList( Mesh.MaterialCount );
	// バウンディング
	CSceneBounding OBB;
	CVector3D vCenter( Mesh.OBB.vCenter.x, Mesh.OBB.vCenter.y, Mesh.OBB.vCenter.z );
	CVector3D vAxis[] = {
		CVector3D( Mesh.OBB.vAxis[0].x, Mesh.OBB.vAxis[0].y, Mesh.OBB.vAxis[0].z ),
		CVector3D( Mesh.OBB.vAxis[1].x, Mesh.OBB.vAxis[1].y, Mesh.OBB.vAxis[1].z ),
		CVector3D( Mesh.OBB.vAxis[2].x, Mesh.OBB.vAxis[2].y, Mesh.OBB.vAxis[2].z ),
	};
	OBB.SetAxis( vCenter, vAxis[0], vAxis[1], vAxis[2] );
	OBB.SetLength( Mesh.OBB.fLength[0], Mesh.OBB.fLength[1], Mesh.OBB.fLength[2] );
	OBB.UpdateMatrix();
	OBB.UpdatePoints();
	OBB.UpdateRadius();
	pMesh->SetBouding( OBB );

	return pMesh;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_PC( const Uint8 *pData, Uint32 Size, CMesh *pMesh )
{
	Uint32 Count = Size / sizeof(SVertex3DBase);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DBASE, Count );
	pMesh->Push( (SVertex3DBase*)pData, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_N( const Uint8 *pData, Uint32 Size, CMesh *pMesh )
{
	Uint32 Count = Size / sizeof(SVertex3DLight);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DLIGHT, Count );
	pMesh->Push( (SVertex3DLight*)pData, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_B( const Uint8 *pData, Uint32 Size, CMesh *pMesh )
{
	Uint32 Count = Size / sizeof(SVertex3DBump);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DBUMP, Count );
	pMesh->Push( (SVertex3DBump*)pData, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_A( const Uint8 *pData, Uint32 Size, CMesh *pMesh )
{
	Uint32 Count = Size / sizeof(SVertex3DAnimation);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DANIMATION, Count );
	pMesh->Push( (SVertex3DAnimation*)pData, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_UV( const Uint8 *pData, Uint32 Size, CMesh *pMesh )
{
	Uint32 Count = Size / sizeof(SVertex3DTexture);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DTEXTURE, Count );
	pMesh->Push( (SVertex3DTexture*)pData, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_INDX( const Uint8 *pData, Uint32 Size, CMesh *pMesh )
{
	Uint32 Count = Size / sizeof(Uint16);

	pMesh->CreateIndex( Count );
	pMesh->Push( (Uint16*)pData, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_MTRL( const Uint8 *pData, Uint32 Size, CMesh *pMesh, Uint32 MaterialNo )
{
	SMF_MATERIAL Mtrl;
	MemoryCopy( &Mtrl, pData, sizeof(SMF_MATERIAL) );

	CMaterial Material;
	// テクスチャ
	for ( Uint32 i = 0; i < 2; i++ )
	{
		if ( pMesh->GetSupportTexture() && (Mtrl.TextureFileName[i][0] != '\0') )
		{
			wchar_t Temp[64];
			MBCStoWCS( Mtrl.TextureFileName[i], Temp );
			ITexture *pTexture = m_pModel->GetRenderPointer()->CreateTextureFromFile( Temp );
			Material.SetTexture( i, dynamic_cast<CTexture*>(pTexture) );
		}
	}
	// 色
	Material.SetColor( CVector4D(Mtrl.vDiffuse.x, Mtrl.vDiffuse.y, Mtrl.vDiffuse.z, Mtrl.vDiffuse.w) );
	// インデックス
	Material.SetIndexStart( Mtrl.FaceStart * 3 );
	Material.SetIndexCount( Mtrl.FaceCount * 3 );
	// バーテックス
	Material.SetVertexStart( Mtrl.VertexStart );
	Material.SetVertexCount( Mtrl.VertexCount );
	// 設定
	pMesh->SetMaterial( MaterialNo, Material );
}

#endif // ENABLE_3D
