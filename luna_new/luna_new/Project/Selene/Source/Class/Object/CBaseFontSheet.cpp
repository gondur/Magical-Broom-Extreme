
//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Surface/CTexture.h"
#include "Render/CRender.h"
#include "Render/CFont.h"
#include "File/CFileManager.h"
#include "Object/CBaseFontSheet.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// STRUCT
//-----------------------------------------------------------------------------------
/**
	@brief LFD�t�@�C���w�b�_

	LFD�t�@�C���p�̃t�@�C���w�b�_�\���́B
*/
struct LFDHEADER
{
	char Guid[4];						///< �t�@�C�����ʏ��i��� 'L' 'F' 'D' '\0'
	Uint8 FontSize;						///< �t�H���g�T�C�Y
	Uint8 SheetMax;						///< �V�[�g�ő吔
	Uint16 SheetWidth;					///< �V�[�g����
	Uint16 SheetHeight;					///< �V�[�g�c��
	Uint16 FontMax;						///< �t�H���g�ő吔
	Uint16 IndexTbl[CHARA_CODE_MAX];	///< �C���f�b�N�X�e�[�u��
};

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseFontSheet::CBaseFontSheet( CRender *pRender, CBaseMgr *pMgr ) : CRenderObject( pRender, pMgr )
{
	MemoryClear( m_pTextures, sizeof(m_pTextures) );
	MemoryClear( m_IndexTbl, sizeof(m_IndexTbl) );

	m_pFont			= NULL;
	m_pSheetTbl		= NULL;

	m_SheetWidth	= 0;
	m_SheetHeight	= 0;
	m_SheetCount	= 0;
	m_FontSize		= 0;
	m_FontMax		= 0;

	m_IsAlpha		= false;
	m_IsAntialias	= false;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseFontSheet::~CBaseFontSheet()
{
	MemGlobalFree( m_pSheetTbl );
	SAFE_RELEASE( m_pFont );
	for ( Sint32 i = 0; i < SHEET_MAX; i++ )
	{
		SAFE_RELEASE( m_pTextures[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
	�t�H���g�X�v���C�g�̍Đ������s���܂�

	@param pBuffer		[in] �����o�b�t�@

	@return			�������ۂ�
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTable( const wchar_t *pBuffer, CFont *pFont, Bool IsAntialias )
{
	static Uint32 LineWidthTbl[512];
	size_t Len;
	Uint32 Size, TexArea, SheetLineNum, LineNum, LastSheet;
	Uint32 FontSize, FontHeight, FontWidth, Pos;
	Sint32 Px, Py;
	Uint16 Code;
	Bool IsWrite;
	ABC Abc;
	CTextureConfig ConfOrg;
	CTextureConfig Conf;

	Bool bRet = false;

	MemoryClear( LineWidthTbl, sizeof(LineWidthTbl) );

	//--------------------------------------------------------------
	// �e�N�X�`���ݒ�
	//--------------------------------------------------------------
	Conf = GetRenderPointer()->GetTextureConfig();
	ConfOrg = Conf;
	Conf.SetFormat( FORMAT_TEXTURE_2D );
	Conf.SetColorKey( 0x00000000 );
	GetRenderPointer()->SetTextureConfig( Conf );

	//--------------------------------------------------------------
	// �f�[�^�R�s�[
	//--------------------------------------------------------------
	m_IsAntialias = IsAntialias;
	m_pFont = pFont;
	m_pFont->AddRef();

	//--------------------------------------------------------------
	// �V�[�g�p�o�b�t�@
	//--------------------------------------------------------------
	m_pSheetTbl = (SFontSheetData*)MemGlobalAlloc( sizeof(SFontSheetData[CHARA_CODE_MAX]) );
	for ( Sint32 i = 0; i < CHARA_CODE_MAX; i++ )
	{
		m_pSheetTbl[i].SheetNo = 0xFF;
		m_IndexTbl[i] = 0xFFFF;
	}

	//--------------------------------------------------------------
	// ����������e�N�X�`���T�C�Y�Z�o
	//--------------------------------------------------------------
	FontSize	= m_pFont->GetFontSize();
	FontHeight	= FontSize + 2;
	Len			= wcslen( pBuffer );
	Size		= FontHeight * FontHeight * Len;

	// �e�N�X�`���T�C�Y�Z�o
	TexArea = 1;
	while ( Size > (TexArea * TexArea) ) TexArea <<= 1;

	// �g�p�\�ȍő�T�C�Y�擾
	CPoint2D<Uint32> MaxTextureSize = GetTextureMaxSize();

	// �e�N�X�`���T�C�Y����
	MaxTextureSize.x = (MaxTextureSize.x > TexArea) ? (TexArea) : (MaxTextureSize.x);
	MaxTextureSize.y = (MaxTextureSize.y > TexArea) ? (TexArea) : (MaxTextureSize.y);

	m_SheetWidth	= MaxTextureSize.x;
	m_SheetHeight	= MaxTextureSize.y;
	m_FontSize		= FontSize;

	SheetLineNum	= m_SheetWidth / FontHeight;

	//--------------------------------------------------------------
	// �P���ڂ̃V�[�g���������Ă���
	//--------------------------------------------------------------
	///Logout( "�@" );
	m_pTextures[0] = (CTexture*)GetRenderPointer()->CreateTexture( m_SheetWidth, m_SheetHeight );
	m_SheetCount++;

	//--------------------------------------------------------------
	// �V�[�g�쐬
	//--------------------------------------------------------------
	Pos = 0;
	while ( Pos < Len )
	{
		//-----------------------------------------
		// Shift-JIS�R�[�h
		//-----------------------------------------
		Code = pBuffer[Pos++];

		//-----------------------------------------
		// �}���\�ȃV�[�g�ꏊ����
		//-----------------------------------------
		LineNum = 0;
		IsWrite = false;
		while ( !IsWrite )
		{
			// �ŏI�V�[�g�ԍ�
			LastSheet = m_SheetCount - 1;

			// �`���e�N�X�`���ݒ�
			m_pFont->SetDestination( m_pTextures[LastSheet] );

			// �t�H���g�`�揈���J�n
			m_pFont->Begin( false );

			// �t�H���g��
			m_pFont->GetFontData( Code, &Abc );
			FontWidth = Abc.abcB + 2;

			// �����ǋL�\�H
			if ( LineWidthTbl[LineNum] + FontWidth < m_SheetWidth )
			{
				// ��񏑂��������H
				if ( m_IndexTbl[Code] == 0xFFFF )
				{
					m_IndexTbl[Code] = (Uint16)m_FontMax;

					// �`��ʒu�Z�o
					Px = LineWidthTbl[LineNum];
					Py = LineNum * FontHeight;

					// �`��
					if ( m_IsAntialias )
						m_pFont->DrawCharAA( Px + 1, Py + 1, CColor(255,255,255,255), Code );
					else
						m_pFont->DrawChar( Px + 1, Py + 1, CColor(255,255,255,255), Code );

					// �A�N�Z�X�p�e�[�u�������
					m_pSheetTbl[m_FontMax].SheetNo	= (Uint8)(LastSheet);
					m_pSheetTbl[m_FontMax].abcA		= (Uint8)(Abc.abcA);
					m_pSheetTbl[m_FontMax].abcB		= (Uint8)(FontWidth);
					m_pSheetTbl[m_FontMax].abcC		= (Uint8)(Abc.abcC);
					m_pSheetTbl[m_FontMax].x1		= (Uint16)(Px);
					m_pSheetTbl[m_FontMax].y1		= (Uint16)(Py);
					m_pSheetTbl[m_FontMax].x2		= (Uint16)(Px + FontWidth);
					m_pSheetTbl[m_FontMax].y2		= (Uint16)(Py + FontHeight);
					m_FontMax++;

					// �t�H���g�`��V�[�g�ʒu���Z
					LineWidthTbl[LineNum] += FontWidth;
				}

				// �`�悵�܂���
				IsWrite = true;
			}
			else
			{
				// �`��ł��񂩂����̂Ŏ��̍s�Ɉڂ�
				LineNum++;

				// �V�[�g�������ς��Ȃ̂Ŏ��̃V�[�g���쐬����
				if ( LineNum == SheetLineNum )
				{
					LineNum = 0;
					MemoryClear( LineWidthTbl, sizeof(LineWidthTbl) );

					// �V�K�V�[�g�쐬
					///Logout( "�@" );
					m_pTextures[m_SheetCount] = (CTexture*)GetRenderPointer()->CreateTexture( m_SheetWidth, m_SheetHeight );
					m_SheetCount++;
					if ( m_SheetCount == SHEET_MAX )
					{
						goto EXIT;
					}
				}
			}

			// �t�H���g�`��I��
			m_pFont->End();
		}
	}

	//--------------------------------------------------------------
	// �e�N�X�`���̍X�V
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pTextures[i]->UpdateTexture();
	}

	bRet = true;

EXIT:
	// �e�N�X�`���ݒ�߂�
	GetRenderPointer()->SetTextureConfig( ConfOrg );

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
	�t�H���g�X�v���C�g�����������琶�������܂��B

	@param pData		[in] LFD�f�[�^�������̃A�h���X
	@param pExt			[in] �摜�̊i�[���ꂽLAG�t�@�C����

	@return		�t�H���g�X�v���C�g�C���^�[�t�F�C�X
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTableFromMemory( void *pData, const wchar_t *pExt )
{
	LFDHEADER *pLfdHead;

	//--------------------------------------------------------------
	// �w�b�_
	//--------------------------------------------------------------
	pLfdHead = (LFDHEADER*)pData;
	pData = ((char*)pData) + sizeof(LFDHEADER);
	if ( strcmp( pLfdHead->Guid, "LFD" ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// �f�[�^
	//--------------------------------------------------------------
	m_FontSize		= pLfdHead->FontSize;		// �t�H���g�T�C�Y
	m_FontMax		= pLfdHead->FontMax;		// �t�H���g��
	m_SheetCount	= pLfdHead->SheetMax;		// �V�[�g��
	m_SheetWidth	= pLfdHead->SheetWidth;		// �V�[�g����
	m_SheetHeight	= pLfdHead->SheetHeight;	// �V�[�g�c��

	//--------------------------------------------------------------
	// �V�[�g��
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		// �V�[�g���擾
		char Name[64] = "";
		MemoryCopy( Name, pData, 32 );
		pData = ((char*)pData) + 32;

		// �e�N�X�`������
		if ( (pExt != NULL) )
		{
			wchar_t TexName[128] = L"";
			MBCStoWCS( Name, TexName );

			::StringCbCat( TexName, sizeof(TexName), L"." );
			::StringCbCat( TexName, sizeof(TexName), pExt );
			m_pTextures[i] = (CTexture*)GetRenderPointer()->CreateTextureFromFile( TexName );
		}
	}

	//--------------------------------------------------------------
	// �C���f�b�N�X
	//--------------------------------------------------------------
	MemoryCopy( m_IndexTbl, pLfdHead->IndexTbl, sizeof(Uint16) * CHARA_CODE_MAX );

	//--------------------------------------------------------------
	// �f�[�^
	//--------------------------------------------------------------
	m_pSheetTbl = (SFontSheetData*)MemGlobalAlloc( sizeof(SFontSheetData) * pLfdHead->FontMax );
	MemoryCopy( m_pSheetTbl, pData, sizeof(SFontSheetData) * pLfdHead->FontMax );
	pData = ((char*)pData) + sizeof(SFontSheetData) * pLfdHead->FontMax;

	return true;
}


//-----------------------------------------------------------------------------------
/**
	�t�H���g�X�v���C�g��LFD�t�@�C�����琶�������܂��B

	@param pFileName	[in] �t�H���g�f�[�^���i�[���ꂽLFD�t�@�C����
	@param pExt		[in] �摜�̊i�[���ꂽLAG�t�@�C����
	@param IsAlpha		[in] �A���t�@�e�N�X�`�����g�����H
	@param Num			[in] �X�v���C�g��
	@param IsSortZ		[in] �X�v���C�g�ɂy�\�[�g���g�����ۂ�

	@return		�t�H���g�X�v���C�g�C���^�[�t�F�C�X
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTableFromFile( const wchar_t *pFileName, const wchar_t *pExt )
{
	//--------------------------------------------------------------
	// �t�@�C������
	//--------------------------------------------------------------
	Uint32 Size;
	void *pData;

	//--------------------------------------------------------------
	// �t�@�C���ǂݍ���
	//--------------------------------------------------------------
	if ( GetCorePointer()->GetFileMgrPointer()->Load( pFileName, &pData, &Size ) )
	{
		if ( !CreateSheetTableFromMemory( pData, pExt ) )
		{
			GetCorePointer()->GetFileMgrPointer()->Free( pData );
			return false;
		}

		GetCorePointer()->GetFileMgrPointer()->Free( pData );
	}
	else
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"�t�@�C����������܂���" );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�����̏ڍׂȉ������擾���܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pStr			[in] �����擾����������
	@param pLeft		[in] �������i�[���邽�߂̕ϐ��ւ̃|�C���^
	@param pCenter		[in] ���������i�[���邽�߂̕ϐ��ւ̃|�C���^
	@param pRight		[in] �E�����i�[���邽�߂̕ϐ��ւ̃|�C���^

	@retval true	����
	@retval false	���s
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::GetWidth( const wchar_t Chara, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight )
{
	if ( pLeft   != NULL ) *pLeft	= m_pSheetTbl[Chara].abcA;
	if ( pCenter != NULL ) *pCenter	= m_pSheetTbl[Chara].abcB;
	if ( pRight  != NULL ) *pRight	= m_pSheetTbl[Chara].abcC;

	return true;
}

//-----------------------------------------------------------------------------------
/**
	�����̏c�����擾���܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pHeight		[in] �c�����i�[���邽�߂̕ϐ��ւ̃|�C���^
*/
//-----------------------------------------------------------------------------------
void CBaseFontSheet::GetHeight( Sint32 *pHeight )
{
	*pHeight = m_FontSize;
}
