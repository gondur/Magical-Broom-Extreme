//
// SeleneAll.hからSelene.hを作る
//
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"stdiofile.h"


void ConvertSub(const char* pszFileName, CStdioFile* pWrite);


char	gszInputPath[_MAX_PATH];
int		Ret = 0;

int main(int argc, char* argv[])
{
	CStdioFile	cInFile, cInFile2, cOutFile;
	char		szFileName[_MAX_PATH];

	if (argc != 3) {
		printf("\n>mkSeleneh.exe <input file> <outputfile>\n");
		return 0;
	}

	strcpy(gszInputPath, argv[1]);
	if (gszInputPath[strlen(gszInputPath) - 1] != '\\' && gszInputPath[strlen(gszInputPath) - 1] != '/') {
		strcat(gszInputPath, "\\");
	}

	sprintf(szFileName, "%sLueAll.h", gszInputPath);
	if (cInFile.OpenFile(szFileName, "rt") < 0) {
		printf("SeleneAll.hが見つかりません。\n");
		return -1;
	} else {
		char	szBuff[8192];
		char*	pText;

		if (cOutFile.OpenFile(argv[2], "wt") < 0) {
			printf("Lue.hが作成できません。\n");
			return -1;
		}

		cOutFile.WriteString("//==============================================================================//\n");
		cOutFile.WriteString("//                         DirectX9用簡易ライブラリ Lue                         //\n");
		cOutFile.WriteString("//==============================================================================//\n");
		cOutFile.WriteString("//                                                                              //\n");
		cOutFile.WriteString("//    最新版の置いてあるURL                                                     //\n");
		cOutFile.WriteString("//                                                                              //\n");
		cOutFile.WriteString("//    TWINTAIL LOVERS.                                                          //\n");
		cOutFile.WriteString("//      http://www.twin-tail.jp/                                                //\n");
		cOutFile.WriteString("//                                                                              //\n");
		cOutFile.WriteString("//    質問等発言場所                                                            //\n");
		cOutFile.WriteString("//      TWINTAIL LOVERS.内の掲示板                                              //\n");
		cOutFile.WriteString("//                                                                              //\n");
		cOutFile.WriteString("//   DirectX Library 'Lue'                                                      //\n");
		cOutFile.WriteString("//   Copyright (C) 2006 葉迩倭                                                  //\n");
		cOutFile.WriteString("//   All rights reserved.                                                       //\n");
		cOutFile.WriteString("//                                                                              //\n");
		cOutFile.WriteString("//==============================================================================//\n");
		cOutFile.WriteString("\n");
		cOutFile.WriteString("\n");
		cOutFile.WriteString("#ifndef ___LUE_H___\n");
		cOutFile.WriteString("#define ___LUE_H___\n");
		cOutFile.WriteString("\n");
		cOutFile.WriteString("#include <windows.h>\n");

		// 解析開始
		memset(szBuff, 0, sizeof(szBuff));
		while (cInFile.ReadString(szBuff, sizeof(szBuff) - 1) >= 0) {
			pText = szBuff;

			while(*pText == ' ' || *pText == '\t')	pText++;
					if (strncmp(pText, "//", 2) == 0) { 
						pText[0] = '\n';
						pText[1] = '\0';
					}

			if(*pText == '\n') {
				Ret++;
				if ( Ret < 2 ) {
					;
				} else {
					continue;
				}
			} else {
				Ret = 0;
			}

			if (strnicmp(pText, "#include", 8) == 0) {
				pText += 8;
				while(*pText == ' ' || *pText == '\t')	pText++;
				if (*pText == '\"')						pText++;

				char*	pEnd = strchr(pText, '\"');
				if (pEnd != NULL) {
					*pEnd = '\0';
					sprintf(szFileName, "%s%s", gszInputPath, pText);
					printf(szFileName);
					printf("\n");

					ConvertSub(szFileName, &cOutFile);
				}
			}
		}
		cOutFile.WriteString("\n");
		cOutFile.WriteString("#endif  // ___LUE_H___\n");
		cOutFile.WriteString("\n");
		cOutFile.WriteString("\n");
	}

	return 0;
}


void ConvertSub(const char* pszFileName, CStdioFile* pWrite)
{
	char		szBuff[8192];
	char*		pText;
	CStdioFile	cInFile2;

	if (cInFile2.OpenFile(pszFileName, "rt") >= 0) {
		char		szDefine[8192];
		bool		bFlag = false;
		bool		bFirstDefine;

		while (cInFile2.ReadString(szBuff, sizeof(szBuff) - 1) >= 0) {
			pText = szBuff;

				while(*pText == ' ' || *pText == '\t')	pText++;
					if (strncmp(pText, "//", 2) == 0) { 
						pText[0] = '\n';
						pText[1] = '\0';
					}

				if(*pText == '\n') {
					Ret++;
					if ( Ret < 2 ) {
						;
					} else {
						continue;
					}
				} else {
					Ret = 0;
				}

			if (bFlag == false) {
				if (strnicmp(pText, "#ifndef", 7) == 0) {
					pText += 7;
					while(*pText == ' ' || *pText == '\t')	pText++;
					strcpy(szDefine, pText);
					if (szDefine[strlen(szDefine) - 1] == '\n') {
						szDefine[strlen(szDefine) - 1] = '\0';
					}
					bFlag = true;
					bFirstDefine = true;
				}
			} else {
				if (strnicmp(pText, "#endif", 6) == 0) 
				{
					pText += 6;
					if (strstr(pText, szDefine) != NULL)
					{
						bFlag = false;
					}
				}
				else if (strnicmp(pText, "#include", 8) == 0)
				{
					continue;
				}
				else if (bFirstDefine == true && strnicmp(pText, "#define", 7) == 0)
				{
					bFirstDefine = false;
					continue;
				}

				if (bFlag == true) {
					pWrite->WriteString(szBuff);
				}
			}
		}
		cInFile2.CloseFile();
	} else {
		printf("%sが見つかりません。", pszFileName);
	}
}


/*  Bottom of MakeSeleneh.cpp  */