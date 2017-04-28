

#ifndef ___SELENE__FILEBASE___
#define ___SELENE__FILEBASE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �t�@�C���I�[�v�����[�h
		@author �t���`
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< �������ݐ�p
		FILE_OPEN_TYPE_READ,			///< �ǂݍ��ݐ�p
		FILE_OPEN_TYPE_READ_WRITE,		///< �ǂݏ����p

		FILE_OPEN_TYPE_INVALID,			///< ����
	};

	/**
		@brief �t�@�C������
		@author �t���`
	*/
	class CFileBase : public CBaseObject
	{
	private:
		HANDLE m_hFile;				///< �t�@�C���n���h��
		eFileOpenType m_Type;		///< �t�@�C���I�[�v�����[�h
		FILETIME m_TimeCreate;		///< �t�@�C���쐬����
		FILETIME m_TimeAccess;		///< �t�@�C���A�N�Z�X����
		FILETIME m_TimeLastWrite;	///< �t�@�C���������ݎ���

	public:
		CFileBase( const wchar_t *pFileName, eFileOpenType Type );
		virtual ~CFileBase();

		virtual Bool IsOpened( void );

		virtual Uint32 Write( const void *pData, Uint32 Size );
		virtual Uint32 Read( void *pData, Uint32 Size );

		virtual Uint32 GetFileSize( void );
		virtual Uint32 GetFilePosition( void );
		virtual Uint32 SeekStart( Sint32 Offset );
		virtual Uint32 SeekEnd( Sint32 Offset );
		virtual Uint32 Seek( Sint32 Offset );
	};
}

#endif // ___SELENE__FILEBASE___

