

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Render/CVertexBuffer.h"
#include "Core/CDevice.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CVertexBuffer::CVertexBuffer( CBaseMgr *pMgr ) : CDeviceObject( pMgr )
	, m_pBuffer			( NULL )
	, m_pVertex			( NULL )
	, m_RequestedCount	( 0 )
	, m_MaxCount		( 0 )
	, m_Offset			( 0 )
	, m_VertexSize		( 0 )
	, m_IsDynamic		( false )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CVertexBuffer::~CVertexBuffer()
{
	SAFE_RELEASE( m_pBuffer	);
	MemGlobalFree( m_pVertex );
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::OnLostDevice( void )
{
	SAFE_RELEASE( m_pBuffer	);
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::OnResetDevice( void )
{
	// 再生成
	GetDevicePointer()->CreateVertexBuffer( m_VertexSize * m_MaxCount, &m_pBuffer, m_IsDynamic );
	// 再構築
	Update();
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::Update( void )
{
	// 書き込みされている場合
	if ( m_Offset > 0 )
	{
		// バッファをロック
		void *pData;
		HRESULT hr = m_pBuffer->Lock( 0, 0, &pData, m_IsDynamic ? D3DLOCK_DISCARD : 0 );
		if SUCCEEDED( hr )
		{
			// バッファに書き込み
			MemoryCopy( pData, m_pVertex, m_VertexSize * m_Offset );
			m_pBuffer->Unlock();
		}
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::Flush( void )
{
	m_Offset			= 0;
	m_RequestedCount	= 0;
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Push( void *pVtx, Uint32 Count )
{
	m_RequestedCount += Count;
	// 追加
	if ( m_Offset + Count <= m_MaxCount )
	{
		Uint8 *pDst = (Uint8*)m_pVertex + (m_VertexSize * m_Offset);
		Uint8 *pSrc = (Uint8*)pVtx;
		for ( Uint32 i = 0; i < Count; i++ )
		{
			MemoryCopy( pDst, pSrc, m_VertexSize );
			pDst += m_VertexSize;
			pSrc += m_VertexSize;
		}
		m_Offset += Count;

		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Get( void *pVtx, Uint32 Index )
{
	if ( Index < m_Offset )
	{
		Uint8 *pSrc = (Uint8*)m_pVertex + (m_VertexSize * Index);
		Uint8 *pDst = (Uint8*)pVtx;

		MemoryCopy( pDst, pSrc, m_VertexSize );

		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Create( Uint32 Count, Uint32 VertexSize, Bool IsDynamic )
{
	m_VertexSize		= VertexSize;
	m_MaxCount			= Count;
	m_RequestedCount	= 0;
	m_Offset			= 0;
	m_IsDynamic			= IsDynamic;

	HRESULT hr = GetDevicePointer()->CreateVertexBuffer( VertexSize * Count, &m_pBuffer, IsDynamic );
	if SUCCEEDED( hr )
	{
		m_pVertex = MemGlobalAlloc( m_VertexSize * m_MaxCount );
		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
HRESULT CVertexBuffer::SetDevice( Uint32 StreamNo )
{
	return GetDevicePointer()->SetStreamSource( StreamNo, m_pBuffer, m_VertexSize );
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
Uint32 CVertexBuffer::GetCount( void ) const
{
	return m_Offset;
}


//-----------------------------------------------------------------------------------
/**
	@brief リクエストのあった頂点数を取得します
	@author 葉迩倭

	@return			リクエスト頂点数
*/
//-----------------------------------------------------------------------------------
Uint32 CVertexBuffer::GetRequestedCount( void ) const
{
	return m_RequestedCount;
}


