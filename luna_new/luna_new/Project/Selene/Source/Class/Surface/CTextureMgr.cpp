

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "File/CFileManager.h"
#include "Surface/CTextureMgr.h"


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
CTextureMgr::CTextureMgr( CDevice *pDevice ) : CDeviceObjectMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CTextureMgr::~CTextureMgr()
{
}

//-----------------------------------------------------------------------------------
/**
	�w�肵�����O�����e�N�X�`���̌��������܂�

	@param pFileName		[in] �e�N�X�`����

	@retval NULL		�����̃e�N�X�`���͑��݂��Ȃ�
	@retval NULL�ȊO	�����̃e�N�X�`���I�u�W�F�N�g

	�w�肵�����O�����e�N�X�`�����������܂��B<BR>
	�{�̖̂��O������ł��t�@�C���p�X���Ⴄ�ꍇ��<BR>
	�Ⴄ�t�@�C���Ƃ��Ď��ʂ���܂��B
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::SearchInstance( const wchar_t *pFileName )
{
	return (CTexture*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`������
	@author �t���`

	@param Width	[in] �e�N�X�`������
	@param Height	[in] �e�N�X�`���c��
	@param Format	[in] �e�N�X�`���t�H�[�}�b�g

	@retval NULL		���s
	@retval NULL�ȊO	�e�N�X�`���I�u�W�F�N�g

	��̃e�N�X�`���𐶐����܂��B
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�e�N�X�`��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"��̃e�N�X�`���𐶐�" );

	CTexture *pTex = new CTexture( this );
	if ( !pTex->Create( Width, Height, Format ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"Create [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"����" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
	@brief �����_�����O�^�[�Q�b�g�e�N�X�`������
	@author �t���`

	@param Width	[in] �e�N�X�`������
	@param Height	[in] �e�N�X�`���c��
	@param Format	[in] �e�N�X�`���t�H�[�}�b�g

	@retval NULL		���s
	@retval NULL�ȊO	�e�N�X�`���I�u�W�F�N�g

	�����_�����O�^�[�Q�b�g�p�̃e�N�X�`���𐶐����܂��B
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�e�N�X�`��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"�����_�����O�^�[�Q�b�g�𐶐�" );

	CTexture *pTex = new CTexture( this );
	if ( !pTex->CreateRenderTarget( Width, Height, Format ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateRenderTarget [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"����" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`������
	@author �t���`

	@param pFileName	[in] �e�N�X�`���t�@�C����
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval NULL		���s
	@retval NULL�ȊO	�e�N�X�`���I�u�W�F�N�g

	�e�N�X�`���t�@�C������e�N�X�`���𐶐����܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());
	CTexture *pTex = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�e�N�X�`��" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"�t�@�C����������܂���" );
	}
	else
	{
		pTex = SearchInstance( FilePath );
		if ( pTex != NULL )
		{
			Log_Print( 0x000000, L"����t�@�C��[%s]���擾", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, L"%s", FilePath );

			pTex = new CTexture( this );

			if ( !pTex->CreateFromFile( pFileName, Format, KeyColor ) )
			{
				SAFE_RELEASE( pTex );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, L"����" );
				pTex->SetName( FilePath );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
	@brief �e�N�X�`������
	@author �t���`

	@param pData		[in] �f�[�^�̃|�C���^
	@param Size			[in] pData�̃f�[�^�T�C�Y
	@param Format		[in] �e�N�X�`���t�H�[�}�b�g
	@param KeyColor		[in] �J���[�L�[�Ƃ��Ďg���F�i0�Ŗ����j

	@retval NULL		���s
	@retval NULL�ȊO	�e�N�X�`���I�u�W�F�N�g

	��������̃e�N�X�`���t�@�C������e�N�X�`���𐶐����܂��B<BR>
	�Ή����Ă���e�N�X�`���t�@�C����TGA/BMP/DDS/PNG/JPG�ł��B<BR>
	�܂��e�N�X�`���T�C�Y��2�ׂ̂���̕K�v������A<BR>
	����ɓ��Ă͂܂�Ȃ��T�C�Y�̏ꍇ�́A�����Ń��T�C�Y����ĊǗ�����܂��B
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�e�N�X�`��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"��������̉摜���琶��" );

	CTexture *pTex = new CTexture( this );

	if ( !pTex->CreateFromMemory( pData, Size, Format, KeyColor ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateFromMemory [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"����" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

CTexture *CTextureMgr::CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());
	CTexture *pTex = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�e�N�X�`��" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"�t�@�C����������܂���" );
	}
	else
	{
		pTex = SearchInstance( FilePath );
		if ( pTex != NULL )
		{
			Log_Print( 0x000000, L"����t�@�C��[%s]���擾", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, L"%s", FilePath );

			pTex = new CTexture( this );

			if ( !pTex->CreateTextureFromFileForNormalMap( pFileName, fHeight ) )
			{
				SAFE_RELEASE( pTex );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, L"����" );
				pTex->SetName( FilePath );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

CTexture *CTextureMgr::CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�e�N�X�`��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"��������̉摜���琶��" );

	CTexture *pTex = new CTexture( this );

	if ( !pTex->CreateTextureFromMemoryForNormalMap( pData, Size, fHeight ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"CreateFromMemory [%dx%d] %s", pTex->GetSize().x, pTex->GetSize().y, GetPixelFormat(pTex->GetFormat()) );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, L"����" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}
