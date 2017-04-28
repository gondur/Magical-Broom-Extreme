

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Surface/CSurface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
	@author �t���`

	@param pMgr		[in] �N���X�Ǘ��p�}�l�[�W���[
*/
//-----------------------------------------------------------------------------------
CSurface::CSurface( CBaseMgr *pMgr ) : CBaseSurface( pMgr )
	, m_pSurface	( NULL )
	, m_BaseFormat	( FORMAT_INVALID )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CSurface::~CSurface()
{
	Log_PrintTable( 0xFF0000, 0x000000, L"���", L"�T�[�t�F�C�X", m_Name );
	Log_TableLine( 1 );

	SAFE_RELEASE( m_pSurface );
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�o�C�X���Z�b�g���̏���
	@author �t���`
*/
//-----------------------------------------------------------------------------------
void CSurface::OnLostDevice( void )
{
	SAFE_RELEASE( m_pSurface );
}


//-----------------------------------------------------------------------------------
/**
	@brief �f�o�C�X���X�g�A���̏���
	@author �t���`
*/
//-----------------------------------------------------------------------------------
void CSurface::OnResetDevice( void )
{
	HRESULT hr = S_OK;

	switch ( m_SurfaceType )
	{
	case SURFACE_TYPE_RENDERTARGET:
		hr = GetDevicePointer()->CreateRenderTarget( m_Size.x, m_Size.y, m_Format, &m_pSurface );
		break;
	case SURFACE_TYPE_DEPTHSTENCIL:
		hr = GetDevicePointer()->CreateDepthStencilSurface( m_Size.x, m_Size.y, m_Format, &m_pSurface );
		break;
	}

	if FAILED( hr )
	{
		Log_PrintTable( 0xFF0000, 0x000000, L"�G���[", L"�T�[�t�F�C�X�̃��X�g�A�Ɏ��s [ %s ]", GetD3DError(hr) );
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g�ɐݒ�
	@author �t���`

	@retval true	����
	@retval false	���s

	�T�[�t�F�C�X�������_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::SetRenderTarget( void )
{
	return SUCCEEDED( GetDevicePointer()->SetRenderTarget( m_pSurface ) );
}


//-----------------------------------------------------------------------------------
/**
	@brief �[�x�X�e���V���o�b�t�@�ɐݒ�
	@author �t���`

	@retval true	����
	@retval false	���s

	�T�[�t�F�C�X��[�x�X�e���V���T�[�t�F�C�X�Ƃ��Đݒ肵�܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::SetDepthStencil( void )
{
	return SUCCEEDED( GetDevicePointer()->SetDepthStencilSurface( m_pSurface ) );
}

//-----------------------------------------------------------------------------------
/**
	@brief �o�b�N�o�b�t�@�ɃR�s�[
	@author �t���`

	@retval true	����
	@retval false	���s

	�T�[�t�F�C�X���o�b�N�o�b�t�@�ɃR�s�[���܂��B<BR>
	�������[�x�X�e���V���T�[�t�F�C�X��t�H�[�}�b�g�ϊ���<BR>
	�n�[�h�E�F�A���Ή����Ă��Ȃ��t�H�[�}�b�g�̃T�[�t�F�C�X�ł�<BR>
	���s���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::CopyToBackBuffer( void )
{
	HRESULT hr = GetDevicePointer()->CopyToBackBuffer( m_pSurface );
	return SUCCEEDED( hr );
}


//-----------------------------------------------------------------------------------
/**
	@brief �[�x�X�e���V���o�b�t�@�𐶐�
	@author �t���`

	@param Width	[in] ����
	@param Height	[in] �c��
	@param Format	[in] �t�H�[�}�b�g

	@retval true	����
	@retval false	���s

	�[�x�X�e���V���p�̃T�[�t�F�C�X�𐶐����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;
	D3DFORMAT SurfFormat;

	//--------------------------------------------------------------
	// �T�[�t�F�C�X���̐���
	//--------------------------------------------------------------
	SurfFormat = GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );

	//--------------------------------------------------------------
	// �T�[�t�F�C�X����
	//--------------------------------------------------------------
	hr = GetDevicePointer()->CreateDepthStencilSurface(
									Width,
									Height,
									SurfFormat,
									&m_pSurface );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�T�[�t�F�C�X�̐����Ɏ��s [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );
		return false;
	}

	//--------------------------------------------------------------
	// �f�[�^�ݒ�
	//--------------------------------------------------------------
	m_BaseFormat	= Format;
	m_Format		= SurfFormat;
	m_Size.x			= Width;
	m_Size.y		= Height;
	m_SurfaceType	= SURFACE_TYPE_DEPTHSTENCIL;

	// ���O
	Log_PrintLine( 0x0000000, L"�T�C�Y [%dx%d] �t�H�[�}�b�g [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g�o�b�t�@�𐶐�
	@author �t���`

	@param Width		[in] ����
	@param Height		[in] �c��
	@param Format		[in] �t�H�[�}�b�g
	@param pCopyTarget	[in] �R�s�[���s���ꍇ�̃R�s�[��̃T�[�t�F�C�X

	@retval true	����
	@retval false	���s

	�����_�����O�^�[�Q�b�g�p�̃T�[�t�F�C�X�𐶐����܂��B<BR>
	pCopyTarget��NULL�ł͂Ȃ����A�����I��Copy()���\�b�h�ɂ��<BR>
	�n�[�h�E�F�A�t�H�[�}�b�g�ϊ��ɑΉ����Ă���t�H�[�}�b�g�Ő�������܂��B
	�܂��T�[�t�F�C�X�t�H�[�}�b�g���o���Ȃ��ꍇ�͂��̊֐��͎��s���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format, CSurface *pCopyTarget )
{
	HRESULT hr;
	D3DFORMAT SurfFormat;

	//--------------------------------------------------------------
	// �T�[�t�F�C�X���̐���
	//--------------------------------------------------------------
	SurfFormat = GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN, pCopyTarget == NULL ? D3DFMT_UNKNOWN : pCopyTarget->GetFormat() );
	if ( SurfFormat == D3DFMT_UNKNOWN )
	{
		Log_PrintLine( 0xFF00000, L"�L���ȃT�[�t�F�C�X�t�H�[�}�b�g��������܂���ł���" );
		return false;
	}

	//--------------------------------------------------------------
	// �T�[�t�F�C�X����
	//--------------------------------------------------------------
	hr = GetDevicePointer()->CreateRenderTarget(
									Width,
									Height,
									SurfFormat,
									&m_pSurface );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�T�[�t�F�C�X�̐����Ɏ��s [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );
		return false;
	}

	//--------------------------------------------------------------
	// �f�[�^�ݒ�
	//--------------------------------------------------------------
	m_BaseFormat	= Format;
	m_Format		= SurfFormat;
	m_Size.x			= Width;
	m_Size.y		= Height;
	m_SurfaceType	= SURFACE_TYPE_RENDERTARGET;

	// ���O
	Log_PrintLine( 0x0000000, L"�T�C�Y [%dx%d] �t�H�[�}�b�g [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �T�[�t�F�C�X�̃R�s�[
	@author �t���`

	@param pDstRect		[in] �]����T�[�t�F�C�X�̋�`
	@param pSrc			[in] �]�����T�[�t�F�C�X
	@param pSrcRect		[in] �]�����T�[�t�F�C�X�̋�`

	@retval true	����
	@retval false	���s

	�T�[�t�F�C�X���m�̊g��k���R�s�[���s���܂��B<BR>
	�T�[�t�F�C�X�ԂŃt�H�[�}�b�g���قȂ�ꍇ��<BR>
	�n�[�h�E�F�A�̃t�H�[�}�b�g�ϊ��̃T�|�[�g���Ȃ���<BR>
	���̊֐��͎��s���܂��B<BR>
	�܂����̃R�s�[�����ɂ͂������̐��������݂��܂��B<BR>
	�E�ʏ�T�[�t�F�C�X����ʏ�T�[�t�F�C�X�̊g��k���R�s�[�͂ł��܂���B<BR>
	�E�o�b�N�o�b�t�@����ʏ�T�[�t�F�C�X�ւ̃R�s�[�͂ł��܂���B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )
{
	RECT Dst = { 0, 0, m_Size.x, m_Size.y };
	RECT Src = { 0, 0, ((CSurface*)pSrc)->m_Size.x, ((CSurface*)pSrc)->m_Size.y };

	if ( pDstRect != NULL ) Dst = *pDstRect;
	if ( pSrcRect != NULL ) Src = *pSrcRect;

	if ( GetDevicePointer()->Clip( &Dst, &Src ) )
	{
		HRESULT hr = GetDevicePointer()->StretchRect(
							((CSurface*)pSrc)->m_pSurface,
							&Src,
							m_pSurface,
							&Dst,
							D3DTEXF_LINEAR );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief �T�[�t�F�C�X�擾
	@author �t���`

	@param ppSurface	[in] �T�[�t�F�C�X�i�[��

	�T�[�t�F�C�X�C���^�[�t�F�C�X���擾���܂��B<BR>
	���̊֐��Ŏ擾�����T�[�t�F�C�X�͎Q�ƃJ�E���^��<BR>
	�C���N�������g�����̂�Release()�֐��ŉ������K�v������܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSurface::GetSurface( IDirect3DSurface9 **ppSurface )
{
	if ( m_pSurface != NULL )
	{
		m_pSurface->AddRef();
		*ppSurface = m_pSurface;
	}

	return *ppSurface != NULL;
}


