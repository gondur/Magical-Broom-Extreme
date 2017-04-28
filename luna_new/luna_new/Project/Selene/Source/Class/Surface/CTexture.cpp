

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Render/CRender.h"
#include "File/CFileManager.h"
#include "Surface/CTexture.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
	@author �t���`

	@param pMgr		[in] �Ǘ��p�}�l�[�W���[
*/
//-----------------------------------------------------------------------------------
CTexture::CTexture( CBaseMgr *pMgr ) : CBaseSurface( pMgr )
	, m_Pool					( D3DPOOL_DEFAULT )
	, m_pTexture				( NULL )
	, m_pBaseTexture			( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CTexture::~CTexture()
{
	Log_PrintTable( 0xFF0000, 0x000000, L"���", L"�e�N�X�`��", m_Name );
	Log_TableLine( 1 );

	SAFE_RELEASE( m_pBaseTexture );
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
	@brief �摜��񂩂�e�N�X�`������
	@author �t���`

	@param pData		[in] �f�[�^�̃|�C���^
	@param Size			[in] pData�̃f�[�^�T�C�Y
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval false		���s
	@retval true		����

	��������̃e�N�X�`����񂩂�e�N�X�`���𐶐����܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateTextureFromImageInfo( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	HRESULT hr;
	IDirect3DSurface9 *pSurface;
	D3DSURFACE_DESC Desc;

	//------------------------------------------------------------
	// �e�N�X�`��
	//------------------------------------------------------------
	m_Size			= GetGraphicCardPointer()->GetTextureSize( CPoint2D<Uint32>( m_ImageInfo.Width, m_ImageInfo.Height ) );
	m_Format		= GetGraphicCardPointer()->GetFormat( Format, m_ImageInfo.Format );
	m_Pool			= D3DPOOL_MANAGED;
	m_SurfaceType	= SURFACE_TYPE_OFFSCREEN;

	//------------------------------------------------------------
	// �e�N�X�`���̐���
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					3,
					0,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�e�N�X�`���̐����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	//------------------------------------------------------------
	// �T�[�t�F�C�X�ɉ摜�ǂݍ���
	//------------------------------------------------------------
	Uint32 Max = m_pTexture->GetLevelCount();
	for ( Uint32 i = 0; i < Max; i++ )
	{
		// �T�[�t�F�C�X�擾
		hr = m_pTexture->GetSurfaceLevel( i, &pSurface );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, L"�T�[�t�F�C�X�̎擾�Ɏ��s���܂��� [ %s ]", GetD3DError(hr) );
			SAFE_RELEASE( m_pTexture );
			return false;
		}

		// �T�[�t�F�C�X���擾
		pSurface->GetDesc( &Desc );

		// �T�[�t�F�C�X�ɉ摜�f�[�^�ǂݍ���
		hr = LoadImageToBaseSurface( pSurface, pData, Size, Desc.Width, Desc.Height, KeyColor );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, L"�摜�̓ǂݍ��݂Ɏ��s���܂��� [ %s ]", GetD3DError(hr) );
			SAFE_RELEASE( pSurface );
			SAFE_RELEASE( m_pTexture );
			return false;
		}

		SAFE_RELEASE( pSurface );
	}

	// ���O
	Log_PrintLine( 0x0000000, L"�T�C�Y [%dx%d] �t�H�[�}�b�g [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���ǂݍ���
	@author �t���`

	@param pData		[in] �f�[�^�̃|�C���^
	@param Size			[in] pData�̃f�[�^�T�C�Y
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval false		���s
	@retval true		����

	��������̃e�N�X�`���t�@�C������e�N�X�`����ǂݍ��݂܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::LoadImageFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	SAFE_RELEASE( m_pTexture );

	//--------------------------------------------------------
	// �摜�f�[�^���I�t�X�N���[���T�[�t�F�C�X�ɓǂݍ���
	//--------------------------------------------------------
	if ( !GetImageInfoFromMemory( pData, Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	//--------------------------------------------------------
	// �e�N�X�`���𐶐�
	//--------------------------------------------------------
	if ( !CreateTextureFromImageInfo( pData, Size, Format, KeyColor ) )
	{
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���ǂݍ���
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval false		���s
	@retval true		����

	�e�N�X�`���t�@�C������e�N�X�`����ǂݍ��݂܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::LoadImageFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor )
{
	void *pData = NULL;
	Uint32 Size;

	SAFE_RELEASE( m_pTexture );

	//--------------------------------------------------------
	// �t�@�C������ǂݍ���
	//--------------------------------------------------------
	if ( !GetCorePointer()->GetFileMgrPointer()->Load( pFileName, &pData, &Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		GetCorePointer()->GetFileMgrPointer()->Free( pData );
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, L"�t�@�C�����J���܂���" );

		return false;
	}

	//--------------------------------------------------------
	// �摜�f�[�^���I�t�X�N���[���T�[�t�F�C�X�ɓǂݍ���
	//--------------------------------------------------------
	if ( !GetImageInfoFromMemory( pData, Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		GetCorePointer()->GetFileMgrPointer()->Free( pData );
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, L"�摜�f�[�^�̓W�J�Ɏ��s" );

		return false;
	}

	//--------------------------------------------------------
	// �e�N�X�`���𐶐�
	//--------------------------------------------------------
	if ( !CreateTextureFromImageInfo( pData, Size, Format, KeyColor ) )
	{
		GetCorePointer()->GetFileMgrPointer()->Free( pData );
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, L"�e�N�X�`���̐����Ɏ��s" );

		return false;
	}

	GetCorePointer()->GetFileMgrPointer()->Free( pData );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`������
	@author �t���`

	@param Width	[in] �e�N�X�`������
	@param Height	[in] �e�N�X�`���c��
	@param Format	[in] �e�N�X�`���t�H�[�}�b�g

	@retval false		���s
	@retval true		����

	��̃e�N�X�`���𐶐����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;

	//------------------------------------------------------------
	// �C���[�W���
	//------------------------------------------------------------
	m_ImageInfo.Format		= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_ImageInfo.Width		= Width;
	m_ImageInfo.Height		= Height;
	m_Format				= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_Pool					= D3DPOOL_MANAGED;
	m_SurfaceType			= SURFACE_TYPE_OFFSCREEN;
	m_Size					= GetGraphicCardPointer()->GetTextureSize( CPoint2D<Uint32>( m_ImageInfo.Width, m_ImageInfo.Height ) );

	//------------------------------------------------------------
	// �e�N�X�`���̐���
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					0,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L" �e�N�X�`���̐����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );

		return false;
	}

	// ���O
	Log_PrintLine( 0x0000000, L"�T�C�Y [%dx%d] �t�H�[�}�b�g [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g�e�N�X�`������
	@author �t���`

	@param Width	[in] �e�N�X�`������
	@param Height	[in] �e�N�X�`���c��
	@param Format	[in] �e�N�X�`���t�H�[�}�b�g

	@retval false		���s
	@retval true		����

	�����_�����O�^�[�Q�b�g�p�̃e�N�X�`���𐶐����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;

	//------------------------------------------------------------
	// �C���[�W���
	//------------------------------------------------------------
	m_ImageInfo.Format		= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_ImageInfo.Width		= Width;
	m_ImageInfo.Height		= Height;
	m_Format				= GetGraphicCardPointer()->GetFormat( Format, D3DFMT_UNKNOWN );
	m_SurfaceType			= SURFACE_TYPE_RENDERTARGET;
	m_Pool					= D3DPOOL_DEFAULT;
	m_Size					= GetGraphicCardPointer()->GetTextureSize( CPoint2D<Uint32>( m_ImageInfo.Width, m_ImageInfo.Height ) );

	//------------------------------------------------------------
	// �x�[�X�e�N�X�`������
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					0,
					m_Format,
					D3DPOOL_SYSTEMMEM,
					&m_pBaseTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�x�[�X�e�N�X�`���̐����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );

		return false;
	}

	//------------------------------------------------------------
	// �e�N�X�`���̐���
	//------------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�e�N�X�`���̐����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, GetD3DError(hr) );

		return false;
	}

	// ���O
	Log_PrintLine( 0x0000000, L"�T�C�Y [%dx%d] �t�H�[�}�b�g [%s]", m_Size.x, m_Size.y, GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`������
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval false		���s
	@retval true		����

	�e�N�X�`���t�@�C������e�N�X�`���𐶐����܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor )
{
	//--------------------------------------------------------------
	// �t�@�C����ǂݍ��݁A��������f�[�^���擾����
	//--------------------------------------------------------------
	if ( LoadImageFromFile( pFileName, Format, KeyColor ) )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`������
	@author �t���`

	@param pData		[in] �f�[�^�̃|�C���^
	@param Size			[in] pData�̃f�[�^�T�C�Y
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval false		���s
	@retval true		����

	��������̃e�N�X�`���t�@�C������e�N�X�`���𐶐����܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	//--------------------------------------------------------------
	// �e�N�X�`���ǂݍ���
	//--------------------------------------------------------------
	if ( LoadImageFromMemory( pData, Size, Format, KeyColor ) )
	{
		return true;
	}

	return false;
}

Bool CTexture::ConvertNormalMap( Float fHeight )
{
	Bool IsRet = false;
	IDirect3DTexture9 *pTexNew;
	HRESULT hr;

	struct PIXEL32 {
		Uint8 b, g, r, a;
	};

	//--------------------------------------------------------
	// �t�H�[�}�b�g�`�F�b�N
	//--------------------------------------------------------
	if ( (m_Format != D3DFMT_X8R8G8B8) && (m_Format != D3DFMT_A8R8G8B8) )
	{
		return false;
	}

	//--------------------------------------------------------
	// �e�N�X�`������
	//--------------------------------------------------------
	hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					3,
					0,
					m_Format,
					m_Pool,
					&pTexNew );
	if FAILED( hr )
	{
		goto EXIT;
	}

	//--------------------------------------------------------
	// �@���}�b�v����
	//--------------------------------------------------------
	hr = D3DXComputeNormalMap(
					pTexNew,
					m_pTexture,
					NULL,
					0,
					D3DX_CHANNEL_LUMINANCE,
					fHeight );
	if FAILED( hr ) 
	{
		goto EXIT;
	}

	//--------------------------------------------------------
	// �A���t�@�����ɍ����f�[�^�����Ă���
	//--------------------------------------------------------
	// �]�������b�N
	D3DLOCKED_RECT SrcRc;
	hr = m_pTexture->LockRect( 0, &SrcRc, NULL, 0 );
	if SUCCEEDED( hr )
	{
		// �]���惍�b�N
		D3DLOCKED_RECT DstRc;
		hr = pTexNew->LockRect( 0, &DstRc, NULL, 0 );
		if SUCCEEDED( hr )
		{
			Uint32 w = m_Size.x;
			Uint32 h = m_Size.y;
			PIXEL32 *pSrc = (PIXEL32*)SrcRc.pBits;
			PIXEL32 *pDst = (PIXEL32*)DstRc.pBits;
			// �A���t�@�����ɍ����f�[�^�����Ă���
			for ( Uint32 y = 0; y < h; y++ )
			{
				for ( Uint32 x = 0; x < w; x++ )
				{
					Uint32 r = pSrc[x].r;
					Uint32 g = pSrc[x].g;
					Uint32 b = pSrc[x].b;
					pDst[x].a = (Uint8)((r + g + b) / 3);
				}
				pDst += w;
				pSrc += w;
			}
			pTexNew->UnlockRect( 0 );
		}
		m_pTexture->UnlockRect( 0 );
	}

	IsRet = true;

EXIT:
	//--------------------------------------------------------
	// �V�����e�N�X�`�����R�s�[
	//--------------------------------------------------------
	if ( IsRet )
	{
		SAFE_RELEASE( m_pTexture );
		m_pTexture = pTexNew;
	}
	else
	{
		SAFE_RELEASE( pTexNew );
	}

	return IsRet;
}

Bool CTexture::CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )
{
	//--------------------------------------------------------------
	// �t�@�C����ǂݍ��݁A��������f�[�^���擾����
	//--------------------------------------------------------------
	if ( LoadImageFromFile( pFileName, FORMAT_TEXTURE32, 0x00000000 ) )
	{
		return ConvertNormalMap( fHeight );
	}

	return false;
}

Bool CTexture::CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )
{
	//--------------------------------------------------------------
	// �e�N�X�`���ǂݍ���
	//--------------------------------------------------------------
	if ( LoadImageFromMemory( pData, Size, FORMAT_TEXTURE32, 0x00000000 ) )
	{
		return ConvertNormalMap( fHeight );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�o�C�X���Z�b�g������
	@author �t���`

	�f�o�C�X�����X�g�����ꍇ�̏������s���܂��B
*/
//-----------------------------------------------------------------------------------
void CTexture::OnLostDevice( void )
{
	if ( m_Pool == D3DPOOL_DEFAULT )
	{
		SAFE_RELEASE( m_pTexture );
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�o�C�X���X�g�A������
	@author �t���`

	�f�o�C�X�����X�g���畜�������ꍇ�̏������s���܂��B
*/
//-----------------------------------------------------------------------------------
void CTexture::OnResetDevice( void )
{
	HRESULT hr = S_OK;

	switch ( m_SurfaceType )
	{
	case SURFACE_TYPE_RENDERTARGET:
		hr = GetDevicePointer()->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					D3DPOOL_DEFAULT,
					&m_pTexture );
		break;
	case SURFACE_TYPE_OFFSCREEN:
		if ( m_Pool == D3DPOOL_DEFAULT )
		{
			hr = GetDevicePointer()->CreateTexture(
						m_Size.x,
						m_Size.y,
						1,
						0,
						m_Format,
						D3DPOOL_DEFAULT,
						&m_pTexture );

			UpdateTexture();
		}
		break;
	}

	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�e�N�X�`���̐����Ɏ��s���܂��� [ %s ]", GetD3DError(hr) );
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`�����b�N
	@author �t���`

	@param pRect	[in] ���b�N�Ώۂ̋�`
	@param ppBits	[out] ���b�N��̃e�N�X�`���̃|�C���^
	@param pPitch	[out] �e�N�X�`���̃s�b�`�i���̃o�C�g���j
	@param pWidth	[out] �e�N�X�`���̉���
	@param pHeight	[out] �e�N�X�`���̏c��
	@param pFormat	[out] �e�N�X�`���̃t�H�[�}�b�g

	�o�b�N�A�b�v�p�V�X�e���������̃e�N�X�`�������b�N���A<BR>
	���ڃs�N�Z���f�[�^���������悤�ɂ��܂��B��BR>
	���b�N����Ă���Ԃ͎��R�ɂ����鎖���o���܂����A<BR>
	���b�N���͈�؂̕`�悪�s���܂���B<BR>
	�܂�Unlock()���UpdateTexture()���邱�ƂŔ��f����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::LockRect( RECT *pRect, void **ppBites, Uint32 *pPitch, Uint32 *pWidth, Uint32 *pHeight, D3DFORMAT *pFormat )
{
	HRESULT hr;

	if ( m_pTexture != NULL )
	{
		if ( m_IsLock )
		{
			Log_PrintLine( 0xFF00000, L"�e�N�X�`���͊��Ƀ��b�N����Ă��܂�" );
		}
		else
		{
			// �����_�����O�^�[�Q�b�g�̏ꍇ�̓V�X�e���ɃR�s�|
			DownloadRenderTarget();

			// ���b�N
			D3DLOCKED_RECT LockRect;
			if ( m_pBaseTexture == NULL )
			{
				hr = m_pTexture->LockRect( 0, &LockRect, pRect, 0 );
			}
			else
			{
				hr = m_pBaseTexture->LockRect( 0, &LockRect, pRect, 0 );
			}

			if SUCCEEDED( hr )
			{
				m_IsLock = true;

				if ( pRect == NULL )
				{
					if ( pFormat != NULL ) *pFormat = m_Format;
					if ( pWidth  != NULL ) *pWidth  = m_Size.x;
					if ( pHeight != NULL ) *pHeight = m_Size.y;
					if ( ppBites != NULL ) *ppBites = LockRect.pBits;
					if ( pPitch  != NULL ) *pPitch  = LockRect.Pitch;
				}
				else
				{
					if ( pFormat != NULL ) *pFormat = m_Format;
					if ( pWidth  != NULL ) *pWidth  = pRect->right - pRect->left;
					if ( pHeight != NULL ) *pHeight = pRect->bottom - pRect->top;
					if ( ppBites != NULL ) *ppBites = LockRect.pBits;
					if ( pPitch  != NULL ) *pPitch  = LockRect.Pitch;
				}
			}
			else
			{
				Log_PrintLine( 0xFF00000, L"�e�N�X�`���̃��b�N�Ɏ��s���܂��� [ %s ]", GetD3DError(hr) );
			}
		}
	}

	return m_IsLock;
}


//-----------------------------------------------------------------------------------
/**
	@brief ���b�N����
	@author �t���`

	���b�N���̃e�N�X�`���̃��b�N���������܂��B
*/
//-----------------------------------------------------------------------------------
void CTexture::UnLockRect( void )
{
	if ( m_IsLock )
	{
		if ( m_pBaseTexture == NULL )
		{
			m_pTexture->UnlockRect( 0 );
		}
		else
		{
			m_pBaseTexture->UnlockRect( 0 );
		}
		m_IsLock = false;
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���̃R�s�[
	@author �t���`

	@param pDstRect		[in] �]����e�N�X�`���̋�`
	@param pSrcTex		[in] �]�����e�N�X�`��
	@param pSrcRect		[in] �]�����e�N�X�`���̋�`
	@param IsUvToTexel	[in] �e�N�X�`���T�C�Y�ƃC���[�W�T�C�Y����v���Ȃ��ꍇ�̕␳�����邩�ۂ�

	@retval true	����
	@retval false	���s

	�e�N�X�`�����m�̊g��k���R�s�[���s���܂��B<BR>
	�e�N�X�`���ԂŃt�H�[�}�b�g���قȂ�ꍇ��<BR>
	�n�[�h�E�F�A�̃t�H�[�}�b�g�ϊ��̃T�|�[�g���Ȃ���<BR>
	���̊֐��͎��s���܂��B<BR>
	�܂����̃R�s�[�����ɂ͂������̐��������݂��܂��B<BR>
	�E�ʏ�e�N�X�`������ʏ�e�N�X�`���̊g��k���R�s�[�͂ł��܂���B<BR>
	�E�o�b�N�o�b�t�@����ʏ�e�N�X�`���ւ̃R�s�[�͂ł��܂���B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel )
{
	HRESULT hr;
	RECT Dst, Src;
	IDirect3DSurface9 *pSrcSurf = NULL;
	IDirect3DSurface9 *pDstSurf = NULL;

	GetSurface( &pDstSurf );
	((CTexture*)pSrcTex)->GetSurface( &pSrcSurf );

	if ( IsUvToTexel )
	{
		Dst.left   = pDstRect->left   * m_Size.x  / m_ImageInfo.Width;
		Dst.top    = pDstRect->top    * m_Size.y / m_ImageInfo.Height;
		Dst.right  = pDstRect->right  * m_Size.x  / m_ImageInfo.Width;
		Dst.bottom = pDstRect->bottom * m_Size.y / m_ImageInfo.Height;

		Src.left   = pSrcRect->left   * ((CTexture*)pSrcTex)->m_Size.x  / ((CTexture*)pSrcTex)->m_ImageInfo.Width;
		Src.top    = pSrcRect->top    * ((CTexture*)pSrcTex)->m_Size.y / ((CTexture*)pSrcTex)->m_ImageInfo.Height;
		Src.right  = pSrcRect->right  * ((CTexture*)pSrcTex)->m_Size.x  / ((CTexture*)pSrcTex)->m_ImageInfo.Width;
		Src.bottom = pSrcRect->bottom * ((CTexture*)pSrcTex)->m_Size.y / ((CTexture*)pSrcTex)->m_ImageInfo.Height;
	}
	else
	{
		Dst = *pDstRect;
		Src = *pSrcRect;
	}

	hr = GetDevicePointer()->StretchRect( pSrcSurf, &Src, pDstSurf, &Dst, D3DTEXF_LINEAR );
	if FAILED( hr )
	{
		hr = GetDevicePointer()->StretchRect( pSrcSurf, &Src, pDstSurf, &Dst, D3DTEXF_POINT );
		if FAILED( hr )
		{
			hr = GetDevicePointer()->StretchRect( pSrcSurf, &Src, pDstSurf, &Dst, D3DTEXF_NONE );
		}
	}

	SAFE_RELEASE( pDstSurf );
	SAFE_RELEASE( pSrcSurf );

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���X�V
	@author �t���`

	�o�b�N�A�b�v�p�V�X�e���������T�[�t�F�C�X�̓��e��<BR>
	VRAM��̃T�[�t�F�C�X�֓]�����܂��B
*/
//-----------------------------------------------------------------------------------
void CTexture::UpdateTexture( void )
{
	if ( m_pTexture != NULL )
	{
		if ( m_pBaseTexture != NULL )
		{
			HRESULT hr;
			m_pTexture->AddDirtyRect( NULL );
			m_pBaseTexture->AddDirtyRect( NULL );
			hr = GetDevicePointer()->UpdateTexture( m_pBaseTexture, m_pTexture );
			if FAILED( hr )
			{
				Log_PrintLine( 0xFF00000, L"UpdateTexture() �Ɏ��s���܂��� [ %s ]", GetD3DError(hr) );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`���擾
	@author �t���`

	@retval false	���s
	@retval true	����

	�����_�����O�p��VRAM��̃e�N�X�`�����擾���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetTexture( IDirect3DTexture9 **ppTexture )
{
	if ( m_pTexture != NULL )
	{
		*ppTexture = m_pTexture;
		m_pTexture->AddRef();
	}
	else
	{
		*ppTexture = NULL;
	}

	return *ppTexture != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief �o�b�N�A�b�v�p�e�N�X�`���擾
	@author �t���`

	@retval false	���s
	@retval true	����

	�o�b�N�A�b�v�p�̃V�X�e���������e�N�X�`�����擾���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetBaseTexture( IDirect3DTexture9 **ppTexture )
{
	if ( m_pBaseTexture != NULL )
	{
		*ppTexture = m_pBaseTexture;
		m_pBaseTexture->AddRef();
	}
	else
	{
		*ppTexture = NULL;
	}

	return *ppTexture != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief �T�[�t�F�C�X�擾
	@author �t���`

	@retval false	���s
	@retval true	����

	�����_�����O�p��VRAM��̃T�[�t�F�C�X���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetSurface( IDirect3DSurface9 **ppSurface )
{
	if ( m_pTexture != NULL )
	{
		m_pTexture->GetSurfaceLevel( 0, ppSurface );
	}
	else
	{
		*ppSurface = NULL;
	}

	return *ppSurface != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief �o�b�N�A�b�v�p�T�[�t�F�C�X�擾
	@author �t���`

	@retval false	���s
	@retval true	����

	�o�b�N�A�b�v�p�̃V�X�e���������T�[�t�F�C�X���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetBaseSurface( IDirect3DSurface9 **ppSurface )
{
	if ( m_pBaseTexture != NULL )
	{
		m_pBaseTexture->GetSurfaceLevel( 0, ppSurface );
	}
	else
	{
		*ppSurface = NULL;
	}

	return *ppSurface != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief U�擾

	@param fParam	�e�N�X�`����X���W

	@return U�l

	�e�N�X�`���̃s�N�Z�����W����<BR>
	���_�f�[�^�Ɏg��UV�l���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Float CTexture::PixelToTexelU( Float fParam )
{
	return fParam / toF(m_ImageInfo.Width);
}

//-----------------------------------------------------------------------------------
/**
	@brief V�擾

	@param fParam	�e�N�X�`����Y���W

	@return V�l

	�e�N�X�`���̃s�N�Z�����W����<BR>
	���_�f�[�^�Ɏg��UV�l���擾���܂��B
*/
//-----------------------------------------------------------------------------------
Float CTexture::PixelToTexelV( Float fParam )
{
	return fParam / toF(m_ImageInfo.Height);
}

//-----------------------------------------------------------------------------------
/**
	@brief �摜�t�@�C���Ƃ��ĕۑ�
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����

	@retval false	���s
	@retval true	����

	�e�N�X�`���̓��e��TGA�摜�t�@�C���Ƃ��ĕۑ����܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SaveToTGA( const wchar_t *pFileName )
{
	if ( m_pTexture != NULL )
	{
		// �����_�����O�^�[�Q�b�g�̏ꍇ�̓V�X�e���ɃR�s�|
		DownloadRenderTarget();

		// �ۑ�
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_TGA,
					m_pBaseTexture != NULL ? m_pBaseTexture : m_pTexture,
					NULL );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g���_�E�����[�h
	@author �t���`

	@retval false	���s
	@retval true	����

	�����_�����O�^�[�T�[�t�F�C�X<BR>
	���݂̃����_�����O�^�[�Q�b�g�̓��e���R�s�[���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::DownloadRenderTarget( void )
{
	HRESULT hr;
	IDirect3DSurface9 *pSrcSurf;
	IDirect3DSurface9 *pDstSurf;

	if ( m_pBaseTexture == NULL ) return false;
	if ( m_pTexture == NULL ) return false;
	if ( m_SurfaceType != SURFACE_TYPE_RENDERTARGET ) return false;

	hr = m_pTexture->GetSurfaceLevel( 0, &pSrcSurf );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, L"�T�[�t�F�C�X�̎擾�Ɏ��s [%s]", GetD3DError(hr) );
		return false;
	}
	else
	{
		hr = m_pBaseTexture->GetSurfaceLevel( 0, &pDstSurf );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, L"�T�[�t�F�C�X�̎擾�Ɏ��s [%s]", GetD3DError(hr) );
			SAFE_RELEASE( pSrcSurf );
			return false;
		}
		else
		{
			hr = GetDevicePointer()->GetRenderTargetData( pSrcSurf, pDstSurf );
			if FAILED( hr )
			{
				Log_PrintLine( 0xFF00000, L"�e�N�X�`���̃R�s�[�����Ɏ��s [%s]", GetD3DError(hr) );
				SAFE_RELEASE( pSrcSurf );
				SAFE_RELEASE( pDstSurf );
				return false;
			}

			SAFE_RELEASE( pDstSurf );
		}

		SAFE_RELEASE( pSrcSurf );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g�ݒ�
	@author �t���`

	@retval false	���s
	@retval true	����

	�����_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
	CreateRenderTarget()�Ő������ꂽ�e�N�X�`���ȊO�͎��s���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SetRenderTarget( void )
{
	Bool bRet = false;

	// �T�[�t�F�C�X�擾
	IDirect3DSurface9 *pSurface;
	if ( GetSurface( &pSurface ) )
	{
		// �����_�����O�^�[�Q�b�g�ݒ�
		if SUCCEEDED( GetDevicePointer()->SetRenderTarget( pSurface ) )
		{
			bRet = true;
		}

		SAFE_RELEASE( pSurface );
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
	@brief �[�x�X�e���V���o�b�t�@�֐ݒ�
	@author �t���`

	@retval false	���s
	@retval true	����

	�[�x�X�e���V���T�[�t�F�C�X�Ƃ��Đݒ肵�܂��B<BR>
	���̊֐���100%���s���܂��B
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SetDepthStencil( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CTexture::GetSize( void )
{
	return m_Size;
}

