

//=================================================================
// INCLUDE
//=================================================================
#include "stdio.h"
#include "windows.h"

//=================================================================
// LINK
//=================================================================
#pragma comment ( lib, "winmm.lib" )

//=================================================================
// GLOBAL
//=================================================================
char DataName[32];

//=================================================================
//
//		Wave�t�@�C���ǂݍ���
//
//=================================================================
void ConvertWave( char *file, FILE *fp )
{
	FILE *rfp = NULL;
	bool result = false;
	long RiffDataSize;
	long fmtDataSize;
	long DataSize;
	long FormatSize;
	// fmt �T�u�`�����N
	WAVEFORMATEX wf;

	//--------------------------------------------------------
	// �t�@�C���I�[�v��
	//--------------------------------------------------------
	rfp = fopen( file, "rb" );
	if ( rfp == NULL )
	{
		puts( "Can't open file" );
		return;
	}

	//--------------------------------------------------------
	// "RIFF"�̕�����
	//--------------------------------------------------------
	if ( fgetc( rfp ) != 'R' || fgetc( rfp ) != 'I' || fgetc( rfp ) != 'F' || fgetc( rfp ) != 'F' )
	{
		puts( "This file isn't wavefile" );
		fclose( rfp );
		return;
	}

	//--------------------------------------------------------
	// RIFF�f�[�^�T�C�Y
	//--------------------------------------------------------
	fread( &RiffDataSize, sizeof(long), 1, rfp );

	//--------------------------------------------------------
	// "WAVE"�̕�����
	//--------------------------------------------------------
	if ( fgetc( rfp ) != 'W' || fgetc( rfp ) != 'A' || fgetc( rfp ) != 'V' || fgetc( rfp ) != 'E' )
	{
		puts( "This file isn't wavefile" );
		fclose( rfp );
		return;
	}

	//========================================================
	// Foramt �`�����N
	//========================================================
	// "fmt "�̕�����
	if ( fgetc( rfp ) != 'f' || fgetc( rfp ) != 'm' || fgetc( rfp ) != 't' || fgetc( rfp ) != ' ' )
	{
		puts( "This file isn't wavefile" );
		fclose( rfp );
		return;
	}

	//--------------------------------------------------------
	// fmt�f�[�^�T�C�Y
	//--------------------------------------------------------
	fread( &fmtDataSize, sizeof(long), 1, rfp );

	//--------------------------------------------------------
	// �t�H�[�}�b�g���擾
	//--------------------------------------------------------
	FormatSize = sizeof(WAVEFORMATEX)-sizeof(WORD);
	fread( &wf, FormatSize, 1, rfp );

	// �t�H�[�}�b�g
	if ( wf.wFormatTag != 1 )
	{
		// ���k�t�@�C���͊��فiT-T
		puts( "Not sopport compressed file" );
		fclose( rfp );
		return;
	}

	// �g���f�[�^�͎g�p���܂����`
    wf.cbSize = 0;

	// ���O
	printf( "  Channel  => %d\n", wf.nChannels );
	printf( "  Sample   => %d\n", wf.nSamplesPerSec );
	printf( "  Byte     => %d\n", wf.nAvgBytesPerSec );
	printf( "  Block    => %d\n", wf.nBlockAlign ); 
	printf( "  Bit      => %d\n", wf.wBitsPerSample );

	// �����ɂ�`
	fseek( rfp, fmtDataSize-(sizeof(WAVEFORMATEX)-sizeof(WORD)), SEEK_CUR );

	//========================================================
	// Data�`�����N����
	//========================================================
	while ( true )
	{
		// �Ȃ�̃`�����N���ȁ`
		char guid[5] = "";
		fread( guid, sizeof(char), 4, rfp );
		printf( "Chunk => %s\n", guid );
		// ������Ƃ܂ā`
		if ( feof( rfp ) )
		{
			puts( "Can't find Wave Data" );
			fclose( rfp );
			return;
		}
		// �������ł����H
		if ( strcmp( "data", guid ) == 0 )
		{
			// �r�o
			break;
		}
		else
		{
			// �Ȃ�ł��Ⴄ�񂩂�
			DWORD size;
			fread( &size, sizeof(DWORD), 1, rfp );
			// ��������
			fseek( rfp, size, SEEK_CUR );
		}
	}

	//--------------------------------------------------------
	// �f�[�^�T�C�Y
	//--------------------------------------------------------
	fread( &DataSize, sizeof(long), 1, rfp );

	// �f�[�^�擾
	LPBYTE lpSoundData = new BYTE [ DataSize ];
	fread( lpSoundData, sizeof(BYTE), DataSize, rfp );

	printf( "  DataSize => %.3lf Kbyte\n", DataSize/1024.0 );

	//--------------------------------------------------------
	// �f�[�^��������
	//--------------------------------------------------------
	fwrite( DataName, sizeof(char), 32, fp );
	fwrite( &DataSize, sizeof(long), 1, fp );
	fwrite( &wf, sizeof(WAVEFORMATEX), 1, fp );
	fwrite( lpSoundData, sizeof(BYTE), DataSize, fp );

	// �f�[�^�J��
	delete [] lpSoundData;
}

//=================================================================
//
//		�t�@�C���I�[�v���_�C�A���O
//
//=================================================================
bool SaveDialog( char *path )
{
	ZeroMemory( path, 256 );
	
	OPENFILENAME ofn;
	ZeroMemory( &ofn, sizeof(OPENFILENAME) );
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrTitle = "�p�b�N�t�@�C���̕ۑ�";
	ofn.lpstrFilter = "lsd�t�@�C��(*.lwd)\0*.lsd\0";
	ofn.lpstrDefExt = "lsd";
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = path;
	ofn.nMaxFile = 256;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
	
	if ( !GetOpenFileName( &ofn ) ) return false;

	return true;
}

//=================================================================
//
//	���C��
//
//=================================================================
void main( int arg, char *args[] )
{
	char FilePath[256];
	char SavePath[256];
	char *AbsPath;
	HANDLE hFile;
	FILE *fp;
	WIN32_FIND_DATA FindData;

	AbsPath = args[0];

	//---------------------------------------------------
	// �t�H���_�̃p�X�擾
	//---------------------------------------------------
	for ( long i = (long)strlen(AbsPath); AbsPath[i] != '\\'; i-- ) AbsPath[i] = '\0';

	//---------------------------------------------------
	// �t�@�C���̃��C���h�J�[�h�ݒ�
	//---------------------------------------------------
	sprintf( FilePath, "%s*.wav", AbsPath );

	//---------------------------------------------------
	// ��ڂ̃t�@�C��
	//---------------------------------------------------
	hFile = FindFirstFile( FilePath, &FindData );
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		puts( "Can't find WaveFile in this folder..." );
		return;
	}

	//---------------------------------------------------
	// �������݃t�@�C���p�_�C�A���O
	//---------------------------------------------------
	if ( SaveDialog( SavePath ) )
	{
		//------------------------------------
		// �w�b�_��������
		//------------------------------------
		fp = fopen( SavePath, "wb" );
		if ( fp == NULL )
		{
			puts( "Can't Open WriteFile" );
			return;
		}

		// �w�b�_
		struct RWFFILEHEADER
		{
			char guid[4];
		}
		rwh = { 'L', 'S', 'D' };

		// �t�@�C���w�b�_��������
		fwrite( &rwh, sizeof(RWFFILEHEADER), 1, fp );

		//------------------------------------
		// �t�@�C����
		//------------------------------------
		while ( true )
		{
			// �ǂݍ��݃t�@�C��
			char buff[256];
			sprintf( buff, "%s%s", AbsPath, FindData.cFileName );
			char *p = FindData.cFileName;

			ZeroMemory( DataName, sizeof(char)*32 );

			// �f�[�^��
			for ( long i = 0; p[i] != '.'; i++ )
			{
				if ( 'A' <= p[i] && p[i] <= 'Z' )
				{
					p[i] += 'a' - 'A';
				}
				DataName[i] = p[i];
			}
			puts( DataName );

			// Wave�f�[�^����
			ConvertWave( buff, fp );

			// ���̃t�@�C��
			if ( FindNextFile( hFile, &FindData ) == FALSE ) break;
		}

		// �t�@�C���N���[�Y
		fclose( fp );
	}

	puts( "Press any key" );
	getchar();
}