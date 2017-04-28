

//======================================================================
// INCLUDE
//======================================================================
#include "StrBuffer.h"


//==========================================================================
// CONST
//==========================================================================
static const long STRING_MAX = 65536;


//==========================================================================
// PROTOTYPE
//==========================================================================
static void SetString( char *pStr );


//==========================================================================
// GLOBAL
//==========================================================================
static STRING String[STRING_MAX];
static long StrCount;


//==========================================================================
//
//		�t�@�C������S�p������擾
//
//==========================================================================
void CutString( char *pFileName )
{
	memset( String, 0x00, sizeof(String) );
	StrCount = 0;

	//-------------------------------------------------------
	// �t�@�C����
	//-------------------------------------------------------
	FILE *fp = fopen( pFileName, "rt" );
	if ( fp != NULL )
	{
		for ( ; ; )
		{
			char Chara = fgetc( fp );
			if ( feof( fp ) ) break;

			if ( IsKanji( Chara ) )
			{
				char Str[4] = { Chara, fgetc( fp ) };
				SetString( Str );
			}
			else
			{
				if ( (unsigned char)Chara >= 0x20 )
				{
					char Str[4] = { Chara };
					SetString( Str );
				}
			}
		}

		fclose( fp );
	}

	//-------------------------------------------------------
	// �����R�[�h���ƂɃ\�[�g
	//-------------------------------------------------------
	for ( long i = 0; i < StrCount; i++ )
	{
		for ( long j = 0; j < StrCount; j++ )
		{
			if ( String[i].Code < String[j].Code )
			{
				STRING Temp = String[i];
				String[i] = String[j];
				String[j] = Temp;
			}
		}
	}
}


//==========================================================================
//
//		�S�p�����Z�b�g
//
//==========================================================================
void SetString( char *pStr )
{
	if ( StrCount == STRING_MAX ) return;

	long i = 0;
	char buff[3] = { pStr[0], pStr[1] };
	unsigned short code = GetCharCode( (unsigned char *)buff );

	if ( code == '�@' ) return;
	if ( code == '\r' ) return;
	if ( code == '\n' ) return;
	if ( code == '\t' ) return;
	if ( code == '\b' ) return;
	if ( code == ' '  ) return;

	// ���ꕶ������
	while ( i < StrCount )
	{
		if ( String[i++].Code == code ) return;
	}

	// �V�K����
	strcpy( (char *)String[i].Buff, buff );
	String[i].Code = code;
	StrCount++;
}

//==========================================================================
//
//		�S�p�`�F�b�N
//
//==========================================================================
bool IsKanji( unsigned char c )
{
	if ( c < 0x81 ) return false;
	if ( c < 0xA0 ) return true;
	if ( c < 0xE0 ) return false;
	if ( c < 0xFF ) return true;

	return false;
}

//==========================================================================
//
//		�����R�[�h�擾
//
//==========================================================================
unsigned short GetCharCode( unsigned char *pStr )
{
	if ( IsKanji( pStr[0] ) )
	{
		unsigned char Temp[2] =  { pStr[1], pStr[0] };
		return (*((unsigned short *)Temp));
	}
	else
	{
		return pStr[0];
	}
}

//==========================================================================
//
//		�����R�[�h�擾
//
//==========================================================================
STRING *GetStringBuffer( void )
{
	return String;
}

//==========================================================================
//
//		�����R�[�h�擾
//
//==========================================================================
long GetStringCount( void )
{
	return StrCount;
}