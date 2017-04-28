

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Surface/CBaseSurface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
	@author �t���`

	@param pMgr		[in] �I�u�W�F�N�g�Ǘ��N���X
*/
//-----------------------------------------------------------------------------------
CBaseSurface::CBaseSurface( CBaseMgr *pMgr ) : CDeviceObject( pMgr )
	, m_IsLock				( false )
	, m_Size				( 0, 0 )
	, m_SurfaceType			( SURFACE_TYPE_INVALID )
{
	MemoryClear( &m_ImageInfo, sizeof(m_ImageInfo) );
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CBaseSurface::~CBaseSurface()
{
}


//-----------------------------------------------------------------------------------
/**
	@brief �x�[�X�T�[�t�F�C�X�ɉ摜�C���[�W��W�J
	@author �t���`

	@param pSurface		[in/out] �T�[�t�F�C�X�W�J��
	@param pData		[in] �摜�f�[�^
	@param Size			[in] �f�[�^�T�C�Y
	@param Width		[in] �摜���T�C�Y
	@param Height		[in] �摜�c�T�C�Y
	@param KeyColor		[in] �J���[�L�[�F

	@return ���ʁiHRESULT�^

	�w��̃V�X�e����������̃T�[�t�F�C�X�ɑ΂���<BR>
	��������̉摜�f�[�^��W�J���܂��B
*/
//-----------------------------------------------------------------------------------
HRESULT CBaseSurface::LoadImageToBaseSurface( IDirect3DSurface9 *pSurface, const void *pData, Uint32 Size, Uint32 Width, Uint32 Height, CColor KeyColor )
{
	HRESULT hr;
	RECT Dst = { 0, 0, Width, Height };
	RECT Src = { 0, 0, m_ImageInfo.Width, m_ImageInfo.Height };

	//------------------------------------------------------
	// �I�t�X�N���[���T�[�t�F�C�X�ɉ摜�f�[�^�����[�h
	//------------------------------------------------------
	hr = ::D3DXLoadSurfaceFromFileInMemory(
				pSurface,
				NULL,
				&Dst,
				pData,
				Size,
				&Src,
				D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER,
				(D3DCOLOR)KeyColor,
				NULL );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�f�[�^���J���܂���@[ %s ]", GetD3DError(hr) );
		return false;
	}

	return hr;
}

//-----------------------------------------------------------------------------------
/**
	@brief �������p�̉摜�t�@�C������C���[�W�����擾
	@author �t���`

	@param pData	[in] �摜�f�[�^
	@param Size		[in] �摜�f�[�^�T�C�Y

	@retval true	����
	@retval false	���s

	��������̉摜�t�@�C������T�C�Y��t�H�[�}�b�g����<BR>
	�C���[�W�f�[�^���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CBaseSurface::GetImageInfoFromMemory( const void *pData, Uint32 Size )
{
	HRESULT hr;

	//--------------------------------------------------------------
	// �t�@�C�����擾
	//--------------------------------------------------------------
	hr = ::D3DXGetImageInfoFromFileInMemory( pData, Size, &m_ImageInfo );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�t�@�C�����J���܂���@[ %s ]", GetD3DError(hr) );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �摜�f�[�^�̉��T�C�Y���擾
	@author �t���`

	@return ���T�C�Y

	�ǂݍ���ł���摜�f�[�^�̉��T�C�Y���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseSurface::GetImageWidth( void )
{
	return m_ImageInfo.Width;
}

//-----------------------------------------------------------------------------------
/**
	@brief �摜�f�[�^�̏c�T�C�Y���擾
	@author �t���`

	@return �c�T�C�Y

	�ǂݍ���ł���摜�f�[�^�̏c�T�C�Y���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseSurface::GetImageHeight( void )
{
	return m_ImageInfo.Height;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���T�C�Y���擾
	@author �t���`

	@return �T�C�Y

	�ǂݍ���ł���摜�f�[�^��W�J���Ă�e�N�X�`���̃T�C�Y���擾���܂��B
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CBaseSurface::GetSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���t�H�[�}�b�g���擾
	@author �t���`

	@return �t�H�[�}�b�g

	�ǂݍ���ł���摜�f�[�^��W�J���Ă�e�N�X�`���̃t�H�[�}�b�g���擾���܂��B
*/
//-----------------------------------------------------------------------------------
D3DFORMAT CBaseSurface::GetFormat( void )
{
	return m_Format;
}

