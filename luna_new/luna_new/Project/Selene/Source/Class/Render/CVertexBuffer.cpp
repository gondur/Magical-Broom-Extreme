

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
	@brief �R���X�g���N�^
	@author �t���`
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
	@brief �f�X�g���N�^
	@author �t���`
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
	@author �t���`
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::OnLostDevice( void )
{
	SAFE_RELEASE( m_pBuffer	);
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author �t���`
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::OnResetDevice( void )
{
	// �Đ���
	GetDevicePointer()->CreateVertexBuffer( m_VertexSize * m_MaxCount, &m_pBuffer, m_IsDynamic );
	// �č\�z
	Update();
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author �t���`
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::Update( void )
{
	// �������݂���Ă���ꍇ
	if ( m_Offset > 0 )
	{
		// �o�b�t�@�����b�N
		void *pData;
		HRESULT hr = m_pBuffer->Lock( 0, 0, &pData, m_IsDynamic ? D3DLOCK_DISCARD : 0 );
		if SUCCEEDED( hr )
		{
			// �o�b�t�@�ɏ�������
			MemoryCopy( pData, m_pVertex, m_VertexSize * m_Offset );
			m_pBuffer->Unlock();
		}
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author �t���`
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
	@author �t���`
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Push( void *pVtx, Uint32 Count )
{
	m_RequestedCount += Count;
	// �ǉ�
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
	@author �t���`
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
	@author �t���`
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
	@author �t���`
*/
//-----------------------------------------------------------------------------------
HRESULT CVertexBuffer::SetDevice( Uint32 StreamNo )
{
	return GetDevicePointer()->SetStreamSource( StreamNo, m_pBuffer, m_VertexSize );
}


//-----------------------------------------------------------------------------------
/**
	@brief 
	@author �t���`
*/
//-----------------------------------------------------------------------------------
Uint32 CVertexBuffer::GetCount( void ) const
{
	return m_Offset;
}


//-----------------------------------------------------------------------------------
/**
	@brief ���N�G�X�g�̂��������_�����擾���܂�
	@author �t���`

	@return			���N�G�X�g���_��
*/
//-----------------------------------------------------------------------------------
Uint32 CVertexBuffer::GetRequestedCount( void ) const
{
	return m_RequestedCount;
}


