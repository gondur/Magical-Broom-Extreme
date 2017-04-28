

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Render/CIndexBuffer.h"
#include "Core/CDevice.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CIndexBuffer::CIndexBuffer( CBaseMgr *pMgr ) : CDeviceObject( pMgr )
	, m_pBuffer			( NULL )
	, m_pIndex			( NULL )
	, m_MaxCount		( 0 )
	, m_Offset			( 0 )
	, m_RequestedCount	( 0 )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CIndexBuffer::~CIndexBuffer()
{
	SAFE_RELEASE( m_pBuffer	);
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::OnLostDevice( void )
{
	SAFE_RELEASE( m_pBuffer	);
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::OnResetDevice( void )
{
	// 再生成
	GetDevicePointer()->CreateIndexBuffer( sizeof(Uint16) * m_MaxCount, &m_pBuffer, m_IsDynamic );
	// 再構築
	Update();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::Update( void )
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
			MemoryCopy( pData, m_pIndex, sizeof(Uint16) * m_Offset );
			m_pBuffer->Unlock();
		}
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::Flush( void )
{
	m_Offset = 0;
	m_RequestedCount = 0;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CIndexBuffer::Push( Uint16 *pIdx, Uint32 Count )
{
	m_RequestedCount += Count;

	if ( m_Offset + Count <= m_MaxCount )
	{
		MemoryCopy( m_pIndex + m_Offset, pIdx, sizeof(Uint16) * Count );
		m_Offset += Count;

		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CIndexBuffer::Create( Uint32 Count, Bool IsDynamic )
{
	m_IsDynamic	= IsDynamic;
	m_MaxCount	= Count;
	m_Offset	= 0;

	HRESULT hr = GetDevicePointer()->CreateIndexBuffer( sizeof(Uint16) * Count, &m_pBuffer, IsDynamic );
	if SUCCEEDED( hr )
	{
		m_pIndex = (Uint16*)MemGlobalAlloc( sizeof(Uint16) * Count );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CIndexBuffer::SetDevice( void )
{
	return GetDevicePointer()->SetIndices( m_pBuffer );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CIndexBuffer::GetCount( void ) const
{
	return m_Offset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CIndexBuffer::GetRequestedCount( void ) const
{
	return m_RequestedCount;
}

