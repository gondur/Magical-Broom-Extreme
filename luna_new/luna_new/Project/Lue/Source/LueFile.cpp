

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueFile.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// ProtoType
//------------------------------------------------------------------------------------------------
extern ICore *Lue_GetCore( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���ǂݍ���
	@author �t���`

	@param pFile	[in] �ǂݍ��݃t�@�C����
	@param ppData	[out] �ǂݍ��݃f�[�^�i�[��
	@param pSize	[out] �ǂݍ��݃f�[�^�T�C�Y�i�[��

	@retval LTRUE	�ǂݍ��ݐ���
	@retval LFALSE	�ǂݍ��ݎ��s

	�t�@�C���̓ǂݍ��݂��s���܂��B<BR>
	�ǂݍ��݂���������Ɠ����Ń��������m�ۂ���A<BR>
	���̃A�h���X�� ppData �Ɋi�[����A�t�@�C���T�C�Y�� pSize �Ɋi�[����܂��B<BR>
	�ǂݍ��݌�A�s�v�ɂȂ����t�@�C���f�[�^�� File_Release �֐��Ń������ォ�������Ă��������B
*/
//------------------------------------------------------------------------------------------------
eLueBool LueFile_Load( const char *pFile, void **ppData, unsigned int *pSize )
{
	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFile, wTemp );
	return Lue_GetCore()->GetFileMgrPointer()->Load( wTemp, ppData, (Uint32*)pSize ) ? LTRUE : LFALSE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C�����
	@author �t���`

	@param pData	[in] �ǂݍ��݃f�[�^���

	File_Load �֐��œǂݍ��񂾃f�[�^��������܂��B<BR>
	���̊֐��ŉ�����s��Ȃ��ƃA�v���P�[�V�������I�����Ă�<BR>
	����������폜����܂���B
*/
//------------------------------------------------------------------------------------------------
void LueFile_Release( void *pData )
{
	MemGlobalFree( pData );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���̃I�[�v��
	@author �t���`

	@param pFile	[in] �t�@�C����

	@retval NULL		�t�@�C���I�[�v�����s
	@return NULL�ȊO	�t�@�C���̃t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̃N���[�Y���܂��B
*/
//------------------------------------------------------------------------------------------------
LUE_FILEPTR LueFile_FileOpen( const char *pFile )
{
	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFile, wTemp );
	return (LUE_FILEPTR)Lue_GetCore()->GetFileMgrPointer()->FileOpen( wTemp );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���̃N���[�Y
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̃N���[�Y���܂��B
*/
//------------------------------------------------------------------------------------------------
void LueFile_FileClose( LUE_FILEPTR FilePtr )
{
	((IResourceFile*)FilePtr)->Release();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���̃T�C�Y���擾
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̃t�@�C���T�C�Y���擾���܂��B
*/
//------------------------------------------------------------------------------------------------
unsigned int LueFile_FileGetSize( LUE_FILEPTR FilePtr )
{
	return ((IResourceFile*)FilePtr)->GetFileSize();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���|�C���^�̈ʒu���擾
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^

	�I�[�v�����̃t�@�C���̌��݂̃t�@�C���|�C���^��<BR>
	�ʒu���擾���܂��B
*/
//------------------------------------------------------------------------------------------------
unsigned int LueFile_FileGetPosition( LUE_FILEPTR FilePtr )
{
	return ((IResourceFile*)FilePtr)->GetFilePosition();
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���̓ǂݍ���
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^
	@param pData	[in/out] �f�[�^�i�[��
	@param Size		[in] �ǂݍ��݃T�C�Y

	���݂̃t�@�C���|�C���^�̈ʒu����w��f�[�^�T�C�Y����<BR>
	�f�[�^��ǂݍ��݂܂��B
*/
//------------------------------------------------------------------------------------------------
unsigned int LueFile_FileRead( LUE_FILEPTR FilePtr, void *pData, unsigned int Size )
{
	return ((IResourceFile*)FilePtr)->Read( pData, Size );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���|�C���^�̈ړ�
	@author �t���`

	@param FilePtr	[in] �t�@�C���|�C���^
	@param Offset	[in] �t�@�C���|�C���^�̈ړ���
	@param Flag		[in] �t�@�C���|�C���^��ʒu

	�I�[�v�����̃t�@�C���̃t�@�C���|�C���^��C�ӂ̈ʒu�Ɉړ����܂��B
*/
//------------------------------------------------------------------------------------------------
int LueFile_FileSeek( LUE_FILEPTR FilePtr, int Offset, eLueSeek Flag )
{
	switch ( Flag )
	{
	case LSEEK_FILE_CURRENT:		///< ���݈ʒu
		return ((IResourceFile*)FilePtr)->Seek( Offset );
	case LSEEK_FILE_START:			///< �擪�ʒu
		return ((IResourceFile*)FilePtr)->SeekStart( Offset );
	case LSEEK_FILE_END:			///< �I�[�ʒu
		return ((IResourceFile*)FilePtr)->SeekEnd( Offset );
	}

	return 0;
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���ǂݍ��݃J�����g�f�B���N�g���ݒ�
	@author �t���`

	@param pCurrentDir	[in] �����J�����g�f�B���N�g��

	�t�@�C������������ۂɎg����J�����g�f�B���N�g����ݒ肵�܂�<BR>
	LueFile_SetLoadPath �����[�g�̃p�X�Ƃ��āA����ȉ��̃f�B���N�g�����w�肵�܂�<BR>
	<BR>
	��jData/Texture/Chara00/Stand.bmp �̓ǂݍ���<BR>
	LueFile_SetLoadPath �� Data ���w�肵�A<BR>
	LueFile_SetCurrentDirectory �� Texture/Chara00 ���w�肵�܂��B<BR>
	���̌� LueFile_Load �� Stand.bmp �Ǝw�肷�邱�Ƃœǂݍ��܂�܂��B
*/
//------------------------------------------------------------------------------------------------
void LueFile_SetCurrentDirectory( char *pCurrentDir )
{
	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pCurrentDir, wTemp );
	Lue_GetCore()->GetFileMgrPointer()->SetCurrentDirectory( wTemp );
}


//------------------------------------------------------------------------------------------------
/**
	@brief �t�@�C���ǂݍ��݃p�X�ݒ�
	@author �t���`

	@param Priority		[in] �ǂݍ��ݗD��x
	@param pRootPath	[in] ���[�g�f�B���N�g��
	@param pPackFile	[in] �p�b�N�t�@�C����

	�t�@�C���ǂݍ��݂̍ۂɎg����p�X��ݒ肵�܂�<BR>
	pRootPath �� pPackFile �͓���Ɉ����A<BR>
	pRootPath ���̌������s��� pPackFile ���̌������s���悤�ɂȂ��Ă��܂��B
*/
//------------------------------------------------------------------------------------------------
void LueFile_SetLoadPath( unsigned int Priority, const char *pRootPath, const char *pPackFile )
{
	wchar_t wTemp0[MAX_PATH] = L"";
	wchar_t wTemp1[MAX_PATH] = L"";
	MBCStoWCS( pRootPath, wTemp0 );
	MBCStoWCS( pPackFile, wTemp1 );
	return Lue_GetCore()->GetFileMgrPointer()->SetLoadPath( Priority, wTemp0, wTemp1 );
}


} // extern "C"

