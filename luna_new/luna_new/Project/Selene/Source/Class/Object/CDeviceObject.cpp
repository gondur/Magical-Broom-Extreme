

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Object/CDeviceObject.h"
#include "Object/CBaseMgr.h"
#include "Core/CGraphicCard.h"
#include "Core/CDevice.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
*/
//-----------------------------------------------------------------------------------
CDeviceObject::CDeviceObject( CBaseMgr *pMgr )
{
	m_pManager = pMgr;
	m_pManager->InsertEnd( this );
}

//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
*/
//-----------------------------------------------------------------------------------
CDeviceObject::~CDeviceObject()
{
	if ( m_pManager != NULL )
	{
		m_pManager->Erase( this );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
wchar_t *CDeviceObject::GetError( HRESULT hr )
{
	static wchar_t String[128] = L"";

	switch ( hr )
	{
	case D3D_OK:
		::StringCbCopy( String, sizeof(String), L"�G���[�͔������Ă��Ȃ��B" );
		break;
	case D3DERR_CONFLICTINGRENDERSTATE:
		::StringCbCopy( String, sizeof(String), L"���ݐݒ肳��Ă��郌���_�����O �X�e�[�g�͈ꏏ�Ɏg�p�ł��Ȃ��B" );
		break;
	case D3DERR_CONFLICTINGTEXTUREFILTER:
		::StringCbCopy( String, sizeof(String), L"���݂̃e�N�X�`�� �t�B���^�͈ꏏ�Ɏg�p�ł��Ȃ��B" );
		break;
	case D3DERR_CONFLICTINGTEXTUREPALETTE:
		::StringCbCopy( String, sizeof(String), L"���݂̃e�N�X�`���͓����Ɏg�p�ł��Ȃ��B��ʂɃ}���`�e�N�X�`�� �f�o�C�X�ɂ����āA�����ɗL���ɂ��ꂽ�p���b�g���e�N�X�`���œ����p���b�g�����L����K�v������ꍇ�ɔ�������B" );
		break;
	case D3DERR_DEVICELOST:
		::StringCbCopy( String, sizeof(String), L"�f�o�C�X�������Ă��āA�����_�ł͕����ł��Ȃ����߁A�����_�����O�͕s�\�ł���B" );
		break;
	case D3DERR_DEVICENOTRESET:
		::StringCbCopy( String, sizeof(String), L"�f�o�C�X�̓��Z�b�g�ł��Ȃ��B" );
		break;
	case D3DERR_DRIVERINTERNALERROR:
		::StringCbCopy( String, sizeof(String), L"�����h���C�o �G���[�B" );
		break;
	case D3DERR_INVALIDCALL:
		::StringCbCopy( String, sizeof(String), L"���\�b�h�̌Ăяo���������ł���B���Ƃ��΁A���\�b�h�̃p�����[�^�ɖ����Ȓl���ݒ肳��Ă���ꍇ�ȂǁB" );
		break;
	case D3DERR_INVALIDDEVICE:
		::StringCbCopy( String, sizeof(String), L"�v�����ꂽ�f�o�C�X�̎�ނ��L���łȂ��B" );
		break;
	case D3DERR_MOREDATA:
		::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�o�b�t�@ �T�C�Y�ɕێ��ł���ȏ�̃f�[�^�����݂���B" );
		break;
	case D3DERR_NOTAVAILABLE:
		::StringCbCopy( String, sizeof(String), L"���̃f�o�C�X�́A�Ɖ�ꂽ�e�N�j�b�N���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_NOTFOUND:
		::StringCbCopy( String, sizeof(String), L"�v�����ꂽ���ڂ�������Ȃ������B" );
		break;
	case D3DERR_OUTOFVIDEOMEMORY:
		::StringCbCopy( String, sizeof(String), L"Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ���������Ȃ��B" );
		break;
	case D3DERR_TOOMANYOPERATIONS:
		::StringCbCopy( String, sizeof(String), L"�f�o�C�X���T�|�[�g���Ă���ȏ�̃e�N�X�`�� �t�B���^�����O�������A�A�v���P�[�V�������v�����Ă���B" );
		break;
	case D3DERR_UNSUPPORTEDALPHAARG:
		::StringCbCopy( String, sizeof(String), L"�A���t�@ �`���l���ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_UNSUPPORTEDALPHAOPERATION:
		::StringCbCopy( String, sizeof(String), L"�A���t�@ �`���l���ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_UNSUPPORTEDCOLORARG:
		::StringCbCopy( String, sizeof(String), L"�J���[�l�ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_UNSUPPORTEDCOLOROPERATION:
		::StringCbCopy( String, sizeof(String), L"�J���[�l�ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_UNSUPPORTEDFACTORVALUE:
		::StringCbCopy( String, sizeof(String), L"�f�o�C�X���w�肳�ꂽ�e�N�X�`���W���l���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
		::StringCbCopy( String, sizeof(String), L"�f�o�C�X���w�肳�ꂽ�e�N�X�`�� �t�B���^���T�|�[�g���Ă��Ȃ��B" );
		break;
	case D3DERR_WRONGTEXTUREFORMAT:
		::StringCbCopy( String, sizeof(String), L"�e�N�X�`�� �T�[�t�F�X�̃s�N�Z�� �t�H�[�}�b�g���L���łȂ��B" );
		break;
	case E_FAIL:
		::StringCbCopy( String, sizeof(String), L"Direct3D �T�u�V�X�e�����Ō����s���̃G���[�����������B" );
		break;
	case E_INVALIDARG:
		::StringCbCopy( String, sizeof(String), L"�����ȃp�����[�^���߂��Ă���֐��ɓn���ꂽ�B" );
		break;
	case E_OUTOFMEMORY:
		::StringCbCopy( String, sizeof(String), L"Direct3D ���Ăяo�����������邽�߂̏\���ȃ����������蓖�Ă邱�Ƃ��ł��Ȃ������B" );
		break;
	case D3DXERR_CANNOTATTRSORT:
		::StringCbCopy( String, sizeof(String), L"�œK���e�N�j�b�N�Ƃ��đ����̃\�[�g (::D3DXMESHOPT_ATTRSORT) �̓T�|�[�g����Ă��Ȃ��B " );
		break;
	case D3DXERR_CANNOTMODIFYINDEXBUFFER:
		::StringCbCopy( String, sizeof(String), L"�C���f�b�N�X �o�b�t�@��ύX�ł��Ȃ��B " );
		break;
	case D3DXERR_INVALIDMESH:
		::StringCbCopy( String, sizeof(String), L"���b�V���������ł���B " );
		break;
	case D3DXERR_SKINNINGNOTSUPPORTED:
		::StringCbCopy( String, sizeof(String), L"�X�L�j���O�̓T�|�[�g����Ă��Ȃ��B " );
		break;
	case D3DXERR_TOOMANYINFLUENCES:
		::StringCbCopy( String, sizeof(String), L"�w�肳�ꂽ�e������������B " );
		break;
	case D3DXERR_INVALIDDATA:
		::StringCbCopy( String, sizeof(String), L"�f�[�^�������ł���B" );
		break;
	default:
		::StringCbCopy( String, sizeof(String), L"���m�̃G���[�B" );
		break;
	}

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDevice *CDeviceObject::GetDevicePointer( void ) const
{
	return m_pManager->GetDevicePointer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CDeviceObject::GetGraphicCardPointer( void ) const
{
	return m_pManager->GetGraphicCardPointer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CDeviceObject::GetCorePointer( void ) const
{
	return m_pManager->GetCorePointer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D<Uint32> CDeviceObject::GetTextureMaxSize( void )
{
	return GetGraphicCardPointer()->GetTextureMaxSize();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HWND CDeviceObject::GetWindow( void ) const
{
	return m_pManager->GetWindow();
}

