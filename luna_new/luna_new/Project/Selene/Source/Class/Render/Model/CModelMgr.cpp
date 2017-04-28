

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CCore.h"
#include "File/CFileManager.h"
#include "Render/Model/CModel.h"
#include "Render/Model/CModelMgr.h"
#include "Render/Model/CModelLoader.h"

#if ENABLE_3D

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
CModelMgr::CModelMgr( CDevice *pDevice ) : CDeviceObjectMgr( pDevice )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CModelMgr::~CModelMgr()
{
}

//-----------------------------------------------------------------------------------
/**
	�w�肵�����O�����e�N�X�`���̌��������܂�

	@param pFileName		[in] ���f����

	@retval NULL		�����̃e�N�X�`���͑��݂��Ȃ�
	@retval NULL�ȊO	�����̃e�N�X�`���I�u�W�F�N�g

	�w�肵�����O�����e�N�X�`�����������܂��B<BR>
	�{�̖̂��O������ł��t�@�C���p�X���Ⴄ�ꍇ��<BR>
	�Ⴄ�t�@�C���Ƃ��Ď��ʂ���܂��B
*/
//-----------------------------------------------------------------------------------
CModel *CModelMgr::SearchInstance( const wchar_t *pFileName )
{
	return (CModel*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
	@brief ���f������
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
CModel *CModelMgr::CreateFromFile( const wchar_t *pFileName, CRender *pRender )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());
	CModel *pModel = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"���f��" );
	Log_CellBegin( 0 );

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"�t�@�C����������܂���" );
	}
	else
	{
		pModel = SearchInstance( FilePath );
		if ( pModel != NULL )
		{
			Log_Print( 0x000000, L"����t�@�C��[%s]���擾", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, L"%s", FilePath );

			void *pData = NULL;
			Uint32 Size;

			pModel = new CModel( pRender, this );
			CModelLoader Loader( pModel );
			if ( !pFileMgr->Load( pFileName, &pData, &Size ) )
			{
				SAFE_RELEASE( pModel );
			}
			ef( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
			{
				SAFE_RELEASE( pModel );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, L"����" );
				pModel->SetName( FilePath );
			}

			pFileMgr->Free( pData );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}

//-----------------------------------------------------------------------------------
/**
	@brief ���f������
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
CModel *CModelMgr::CreateFromMemory( const void *pData, Uint32 Size, CRender *pRender )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"���f��" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, L"��������̉摜���琶��" );

	CModel *pModel = new CModel( pRender, this );
	CModelLoader Loader( pModel );
	if( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
	{
		SAFE_RELEASE( pModel );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}

#endif // ENABLE_3D
