/**********************************************************************
 *  Windows Aplication Library
 *     StdioFile.cpp		STDIOファイルクラス
 *
 *                           Programed by Sazanta
 *********************************************************************/
#ifndef __STDIOFILE_H__
#define	__STDIOFILE_H__


#include <stdio.h>
#include <string.h>

typedef	unsigned int	u_int;


class CStdioFile
{
  private:
			FILE*			m_pFile;

  public:
							CStdioFile(void){
								m_pFile = NULL;
							}
							~CStdioFile(void){
								CloseFile();
							}

	const	FILE*			GetFilePointer(void)	const	{
								return m_pFile;
							}

			int				OpenFile(const char* pszFileName, const char* pszFileMode){
								CloseFile();
								m_pFile = fopen(pszFileName, pszFileMode);
								if (m_pFile == NULL)			return -1;

								return 0;
							}
			void			CloseFile(void){
								if (m_pFile != NULL) {
									fclose(m_pFile);
									m_pFile = NULL;
								}
							}

			size_t			ReadFile(char* pData, size_t uiReadSize){
								if (pData == NULL)				return 0;
								if (uiReadSize == 0)			return 0;
								if (m_pFile == NULL)			return 0;

								uiReadSize = fread(pData, 1, uiReadSize, m_pFile);

								return uiReadSize;
							}
			int				ReadString(char* pBuffer, u_int uiBuffSize){
								if (m_pFile == NULL)			return -1;
								if (fgets(pBuffer, uiBuffSize, m_pFile) == NULL)	return -2;

								return 0;
							}
			size_t			WriteFile(const void* pData, size_t uiWriteSize){
								if (pData == NULL)				return 0;
								if (uiWriteSize == 0)			return 0;
								if (m_pFile == NULL)			return 0;

								uiWriteSize = fwrite(pData, 1, uiWriteSize, m_pFile);

								return uiWriteSize;
							}
			size_t			WriteString(const char* pText){
								if (pText == NULL)				return 0;
								if (m_pFile == NULL)			return 0;

								size_t	uiWriteSize = strlen(pText);
								if (uiWriteSize == 0)			return 0;

								uiWriteSize = fwrite(pText, 1, uiWriteSize, m_pFile);

								return uiWriteSize;
							}

			int				Rewind(void){
								if (m_pFile == NULL)			return -1;
								rewind(m_pFile);

								return 0;
							}
			int				Seek(long lPoint = 0){
								if (m_pFile == NULL)			return -1;
								fseek(m_pFile, lPoint, SEEK_SET);
								return 0;
							}
			long			Tell(void){
								if (m_pFile == NULL)			return -1;
								return ftell(m_pFile);
							}
			int				Eof(void){
								if (m_pFile == NULL)			return -1;

								return feof(m_pFile);
							}
			long			GetFileSize(void){
								if (m_pFile == NULL)			return 0;

								long	lSize, lSave;
								lSave = ftell(m_pFile);
								fseek(m_pFile, 0, SEEK_END);
								lSize = ftell(m_pFile);
								fseek(m_pFile, lSave, SEEK_SET);

								return lSize;
							}
			int				GetFileNumber(void)	const	{
								if (m_pFile == NULL)			return -1;

								return _fileno(m_pFile);
							}
};


#endif
/*  Bottom of StdioFile.h  */
