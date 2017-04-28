

#ifndef ___FILEPACK_H___
#define ___FILEPACK_H___


//=============================================================================
// DEFINE
//=============================================================================
#define ALIGNED(N1,N2)	(((N1)+((N2)-1))&(~((N2)-1)))												///< �A���C�����g�}�N��
#define SAFE_ALLOC(S)	(::VirtualAlloc( NULL, ALIGNED(S,4096), MEM_COMMIT, PAGE_READWRITE ))		///< VirtuakAlloc�������m�ۃ}�N��
#define SAFE_FREE(P)	if ( (P) != NULL ) { ::VirtualFree( (P), 0, MEM_RELEASE ); (P) = NULL; }	///< VirtualAlloc����������}�N��


//=============================================================================
// STRUCT
//=============================================================================
typedef struct
{
	char FileName[64];			// �t�@�C����
	unsigned long NameCrc;		// �t�@�C����CRC
	unsigned long DataCrc;		// �t�@�C����CRC
	unsigned long Address;		// �t�@�C���J�n�ʒu
	unsigned long Size;			// �t�@�C���T�C�Y
}
FILEPACK_DATA;

typedef struct
{
	char Guid[4];				// 'P' 'A' 'C' 'K'
	unsigned long FileCount;	// �t�@�C����
}
FILEPACK_HEADER;


//=============================================================================
// CLASS
//=============================================================================
class CFilePack
{
private:
	FILEPACK_DATA *m_pFileData;
	unsigned long m_FileCount;

private:
	bool CutAfterStr( char *pDst, const char *pSrc, char c );
	void ComputeNameCRC( void );
	bool IsKanji( unsigned char Chara );
	bool CreateDirectory( const char *pPath );
	unsigned long GetCRC( unsigned char Data[], unsigned long Size );
	void CreateFileList( const char *pSearchDir, const char *pRootDir );
	unsigned long ComputeAligned( unsigned long Aligned );

public:
	CFilePack();
	~CFilePack();

public:
	bool Encode( const char *pSrcDirName, unsigned long Aligned = 0 );
	bool Decode( const char *pPackFileName );

	bool Load( const char *pPackFile, const char *pDataName, void **ppData, unsigned long *pSize );
};


#endif // ___FILEPACK_H___

