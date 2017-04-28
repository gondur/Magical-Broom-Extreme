

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Surface/CSurface.h"
#include "Surface/CSurfaceMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
	@author �t���`

	@param pDevice	[in] �֘A�t����ꂽ�f�o�C�X
*/
//-----------------------------------------------------------------------------------
CSurfaceMgr::CSurfaceMgr( CDevice *pDevice ) : CDeviceObjectMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CSurfaceMgr::~CSurfaceMgr()
{
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

	�[�x�X�e���V���p�̃T�[�t�F�C�X�������܂��B
*/
//-----------------------------------------------------------------------------------
CSurface *CSurfaceMgr::CreateDepthStencil( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�}�e���A��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"�[�x�X�e���V���o�b�t�@�𐶐�" );

	CSurface *pSurf = new CSurface( this );

	if ( !pSurf->CreateDepthStencil( Width, Height, Format ) )
	{
		SAFE_RELEASE( pSurf );
		return NULL;
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CeateDepthStencil [%dx%d] %s", pSurf->GetSize().x, pSurf->GetSize().y, GetPixelFormat(pSurf->GetFormat()) );
		pSurf->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"����" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSurf;
}

//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g�o�b�t�@�𐶐�
	@author �t���`

	@param Width		[in] ����
	@param Height		[in] �c��
	@param Format		[in] �t�H�[�}�b�g
	@param pCopyTarget	[in] �R�s�[���s���ꍇ�̃R�s�[��̃}�e���A��

	@retval true	����
	@retval false	���s

	�����_�����O�^�[�Q�b�g�p�̃T�[�t�F�C�X�������܂��B<BR>
	pCopyTarget��NULL�ł͂Ȃ����A�����I��Copy()���\�b�h�ɂ��<BR>
	�n�[�h�E�F�A�t�H�[�}�b�g�ϊ��ɑΉ����Ă���t�H�[�}�b�g�Ő�������܂��B
	�܂��}�e���A���t�H�[�}�b�g���o���Ȃ��ꍇ�͂��̊֐��͎��s���܂��B
*/
//-----------------------------------------------------------------------------------
CSurface *CSurfaceMgr::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format, CSurface *pCopyTarget )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�}�e���A��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"�����_�����O�p�o�b�t�@�𐶐�" );

	CSurface *pSurf = new CSurface( this );

	if ( pSurf->CreateRenderTarget( Width, Height, Format, pCopyTarget ) )
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateRenderTarget [%dx%d] %s", pSurf->GetSize().x, pSurf->GetSize().y, GetPixelFormat(pSurf->GetFormat()) );
		pSurf->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"����" );
	}
	else
	{
		SAFE_RELEASE( pSurf );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSurf;
}

