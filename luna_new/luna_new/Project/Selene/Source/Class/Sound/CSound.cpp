

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Sound/CSound.h"
#include "File/CFileManager.h"
#include "File/CResourceFile.h"
#include "../Project/Lib/Ayame.h"


//-----------------------------------------------------------------------------------
// PROTOTPE
//-----------------------------------------------------------------------------------
CAyame *Ayame_CreateInstanceFromFileEx( const char *pFileName, unsigned long Start, unsigned long Size, bool IsGlobal );


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
CSound::CSound( CCore *pCore )
	: m_pDriver		( NULL )
{
	pCore->AddChild( this );
}


//-----------------------------------------------------------------------------------
/**
	@brief �f�X�g���N�^
	@author �t���`
*/
//-----------------------------------------------------------------------------------
CSound::~CSound( void )
{
	Log_PrintTable( 0xFF0000, 0x000000, L"���", L"�T�E���h", m_Name );
	Log_TableLine( 1 );

	SAFE_RELEASE( m_pDriver );
}

//-----------------------------------------------------------------------------------
/**
	@brief �T�E���h����
	@author �t���`

	@param pFileName		[in] �T�E���h�t�@�C����
	@param IsGlobalScope	[in] �E�B���h�E����A�N�e�B�u�����Ă��Đ����邩�ǂ���

	@retval false	���s
	@retval true	����
*/
//-----------------------------------------------------------------------------------
Bool CSound::CreateFromFile( const wchar_t *pFileName, Bool IsGlobalScope )
{
	CCore *pCore = dynamic_cast<CCore*>(m_pParent);
	CResourceFile *pFile = NULL;

	try
	{
		//--------------------------------------------------------------
		// �f�[�^�̓ǂݍ���
		//--------------------------------------------------------------
		pFile = dynamic_cast<CResourceFile*>(pCore->GetFileMgrPointer()->FileOpen( pFileName ));
		if ( pFile == NULL )
		{
			throw L"�t�@�C�����J���܂���ł���";
		}

		//--------------------------------------------------------------
		// �h���C�o�[�̎擾
		//--------------------------------------------------------------
		char Temp[MAX_PATH] = "";
		WCStoMBCS( pFile->GetNamePointer(), Temp );

		m_pDriver = Ayame_CreateInstanceFromFileEx( Temp, pFile->GetFileStart(), pFile->GetFileSize(), IsGlobalScope );
		if ( m_pDriver == NULL )
		{
			throw L"�h���C�o�[���擾�ł��܂���ł���";
		}
	}
	catch ( const wchar_t *pErr )
	{
		Log_PrintStrong( 0xFF0000, pErr );
		m_pDriver = NULL;
	}

	// �t�@�C���N���[�Y
	SAFE_RELEASE( pFile );

	return m_pDriver != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief �Đ�
	@author �t���`

	@param LoopCount		[in] ���[�v�J�E���g
	@param LoopInSample		[in] ���[�v��J�n�ʒu�T���v����

	�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
	���[�v���ƁA���[�v��Đ��J�n�ʒu���T���v���P�ʂŎw��ł��܂��B
*/
//-----------------------------------------------------------------------------------
void CSound::Play( Uint32 LoopCount, Uint32 LoopInSample )
{
	m_pDriver->Play( LoopCount, LoopInSample );
}

//-----------------------------------------------------------------------------------
/**
	@brief ��~
	@author �t���`

	�Đ����̃T�E���h���~���܂��B
*/
//-----------------------------------------------------------------------------------
void CSound::Stop( void )
{
	m_pDriver->Stop();
}

//-----------------------------------------------------------------------------------
/**
	@brief �ꎞ��~/����
	@author �t���`

	�Đ����̃T�E���h���ꎞ��~�A<BR>
	�ꎞ��~���̃T�E���h���Đ����܂��B
*/
//-----------------------------------------------------------------------------------
void CSound::Pause( void )
{
	m_pDriver->Pause();
}

//-----------------------------------------------------------------------------------
/**
	@brief �{�����[���ύX
	@author �t���`

	@param fVolume	[in] �{�����[���i0�`100�j

	�{�����[���̕ύX���s���܂��B
*/
//-----------------------------------------------------------------------------------
void CSound::SetVolume( Float fVolume )
{
	m_pDriver->SetVolume( fVolume );
}

//-----------------------------------------------------------------------------------
/**
	@brief �p���ړ�
	@author �t���`

	@param fVolume	[in] �p���i-100�`+100�j

	�p���̈ړ����s���܂��B
*/
//-----------------------------------------------------------------------------------
void CSound::SetPan( Float fPan )
{
	m_pDriver->SetPan( fPan );
}

//-----------------------------------------------------------------------------------
/**
	@brief �Đ��`�F�b�N
	@author �t���`

	@retval false	�Đ����Ă��Ȃ�
	@retval true	�Đ����Ă���

	���ݍĐ����̃T�E���h���ǂ������ׂ܂��B
*/
//-----------------------------------------------------------------------------------
Bool CSound::IsPlay( void )
{
	return m_pDriver->IsPlay();
}

