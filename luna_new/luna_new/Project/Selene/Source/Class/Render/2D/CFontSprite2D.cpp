

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Render/2D/CSprite2D.h"
#include "Render/2D/CFontSprite2D.h"
#include "Surface/CTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFontSprite2D::CFontSprite2D( CRender *pRender, CBaseMgr *pMgr ) : CBaseFontSheet( pRender, pMgr )
{
	MemoryClear( m_pSprites, sizeof(m_pSprites) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFontSprite2D::~CFontSprite2D()
{
	Log_PrintTable( 0xFF0000, 0x000000, L"���", L"�t�H���g�X�v���C�g", m_Name );
	Log_TableLine( 1 );

	for ( Sint32 i = 0; i < SHEET_MAX; i++ )
	{
		SAFE_RELEASE( m_pSprites[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::OnResetDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
	�t�H���g�X�v���C�g�̐������s���܂�

	@param pBuffer		[in] �����o�b�t�@
	@param IsAlpha		[in] �A���t�@�`�����l���L��
	@param Num			[in] �ő�X�v���C�g���_��
	@param lFont		[in] �t�H���g�n���h��
	@param IsSortZ		[in] �X�v���C�g�ɂy�\�[�g���g�����ۂ�
	@param IsAntialias	[in] �A���`�G�C���A�X�t�H���g���g�����ۂ�

	@return			�t�H���g�X�v���C�g�n���h��
*/
//-----------------------------------------------------------------------------------
Bool CFontSprite2D::Create( const wchar_t *pBuffer, Uint32 Num, CFont *pFont, Bool IsAntialias )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�t�H���g�X�v���C�g" );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// �V�[�g����
	//--------------------------------------------------------------
	if ( !CreateSheetTable( pBuffer, pFont, IsAntialias ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// �X�v���C�g����
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pSprites[i] = (CSprite2D*)GetRenderPointer()->CreateSprite2D( Num * 2, m_pTextures[i] );
	}

	Log_PrintLine( 0x000000, L"�t�H���g�W�J�p�e�N�X�`���� %u", m_SheetCount );
	SetName( L"Create" );
	Log_PrintStrongLine( 0x008000, L"����" );
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return true;
}


//-----------------------------------------------------------------------------------
/**
	�t�H���g�X�v���C�g�̐������s���܂�

	@param pBuffer		[in] �����o�b�t�@
	@param IsAlpha		[in] �A���t�@�`�����l���L��
	@param Num			[in] �ő�X�v���C�g���_��
	@param lFont		[in] �t�H���g�n���h��
	@param IsSortZ		[in] �X�v���C�g�ɂy�\�[�g���g�����ۂ�
	@param IsAntialias	[in] �A���`�G�C���A�X�t�H���g���g�����ۂ�

	@return			�t�H���g�X�v���C�g�n���h��
*/
//-----------------------------------------------------------------------------------
Bool CFontSprite2D::CreateFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 Num )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"����" );
	Log_PrintCellKind( L"�t�H���g�X�v���C�g" );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// �V�[�g����
	//--------------------------------------------------------------
	if ( !CreateSheetTableFromFile( pFileName, pExt ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// �X�v���C�g����
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pSprites[i] = (CSprite2D*)GetRenderPointer()->CreateSprite2D( Num * 2, m_pTextures[i] );
	}

	Log_PrintLine( 0x000000, L"�t�H���g�W�J�p�e�N�X�`���� %u", m_SheetCount );
	SetName( pFileName );
	Log_PrintStrongLine( 0x008000, L"����" );
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return true;
}


//-----------------------------------------------------------------------------------
/**
	�`��p�X�v���C�g�o�b�t�@�̏����������܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��

*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::Begin( void )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pSprites[i]->Begin();
	}
}

//-----------------------------------------------------------------------------------
/**
	�`��p�X�v���C�g�o�b�t�@�̍X�V�����܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��

*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::End( void )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pSprites[i]->End();
	}
}

//-----------------------------------------------------------------------------------
/**
	�����̃����_�����O���������܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��

*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::Rendering( void )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pSprites[i]->Rendering();
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawString( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// �����R�[�h
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// ���s
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.y;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// �^�u
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// �o�b�N�X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// �X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}

		//-------------------------------------------------------
		// �����f�[�^������ꍇ
		//-------------------------------------------------------
		Uint16 Index = m_IndexTbl[Code];
		if ( Index != 0xFFFF )
		{
			SFontSheetData Sheet = m_pSheetTbl[Index];
			if ( Sheet.SheetNo != -1 )
			{
				// �]����
				Sint32 w = Sheet.x2 - Sheet.x1;
				Sint32 h = Sheet.y2 - Sheet.y1;
				Sint32 x = toI(PosX) + Sheet.abcA;
				CRect2D<Sint32> Dst( x, PosY, w, h );
				CRect2D<Sint32> Src( Sheet.x1, Sheet.y1, w, h );

				// �`��
				m_pSprites[Sheet.SheetNo]->DrawSquare(
					Dst,
					Src,
					Color );

				if ( Code <= 0xFF )
				{
					PosX += m_FontSize / 2;
				}
				else
				{
					PosX += m_FontSize;
				}
			}
			else
			{
				PosX += m_FontSize;
			}
		}
		//-------------------------------------------------------
		// �����f�[�^�������ꍇ
		//-------------------------------------------------------
		else
		{
			PosX += m_FontSize;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	�v���|�[�V���i���t�H���g�̕�����̕`��v�������܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pStr			[in] ������̊i�[���ꂽ�o�b�t�@
	@param Px			[in] �`��J�nX���W
	@param Py			[in] �`��J�nY���W
	@param Pz			[in] �`��Z�l
	@param Color		[in] �`��F

*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// �����R�[�h
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// ���s
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.x;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// �^�u
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// �o�b�N�X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// �X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}
		else
		{
			//-------------------------------------------------------
			// �����f�[�^������ꍇ
			//-------------------------------------------------------
			Uint16 Index = m_IndexTbl[Code];
			if ( Index != 0xFFFF )
			{
				SFontSheetData Sheet = m_pSheetTbl[Index];
				if ( Sheet.SheetNo != -1 )
				{
					// �]����
					Sint32 w = Sheet.x2 - Sheet.x1;
					Sint32 h = Sheet.y2 - Sheet.y1;
					Sint32 x = toI(PosX) + 1;
					CRect2D<Sint32> Dst( x, PosY, w, h );
					CRect2D<Sint32> Src( Sheet.x1, Sheet.y1, w, h );

					// �`��
					m_pSprites[Sheet.SheetNo]->DrawSquare(
						Dst,
						Src,
						Color );

					PosX += Sheet.abcB + 1;
				}
				else
				{
					PosX += m_FontSize / 2;
				}
			}
			//-------------------------------------------------------
			// �����f�[�^�������ꍇ
			//-------------------------------------------------------
			else
			{
				PosX += m_FontSize / 2;
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	�ʏ�̕����̕`��v�������܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pStr			[in] ������̊i�[���ꂽ�o�b�t�@
	@param Dst			[in] �����`����`
	@param Pz			[in] �`��Z�l
	@param Color		[in] �`��F

	@retval 0	�`�悳��Ă��Ȃ�
	@retval 1	�`�悵���͔̂��p����
	@retval 2	�`�悵���̂͑S�p����
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::DrawChara( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color )
{
	Uint16 Index = m_IndexTbl[Chara];
	if ( Index != 0xFFFF )
	{
		SFontSheetData Sheet = m_pSheetTbl[Index];
		if ( Sheet.SheetNo != -1 )
		{
			Sint32 x = Sheet.x1;
			Sint32 y = Sheet.y1;
			Sint32 w = Sheet.x2 - Sheet.x1;
			Sint32 h = Sheet.y2 - Sheet.y1;
			CRect2D<Sint32> Src( x, y, w, h );
			m_pSprites[Sheet.SheetNo]->DrawSquare(
				Dst,
				Src,
				Color );
		}

		return ((Chara <= 0xFF) ? (1) : (2));
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
	�ʏ�̕����̉�]����̕`��v�������܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pStr			[in] ������̊i�[���ꂽ�o�b�t�@
	@param Dst			[in] �����`����`
	@param Pz			[in] �`��Z�l
	@param Color		[in] �`��F
	@param Angle		[in] ��]�p�x�i1��65536�x

	@retval 0	�`�悳��Ă��Ȃ�
	@retval 1	�`�悵���͔̂��p����
	@retval 2	�`�悵���̂͑S�p����
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::DrawCharaRotate( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color, Sint32 Angle )
{
	Uint16 Index = m_IndexTbl[Chara];
	if ( Index != 0xFFFF )
	{
		SFontSheetData Sheet = m_pSheetTbl[Index];
		if ( Sheet.SheetNo != -1 )
		{
			Sint32 x = Sheet.x1;
			Sint32 y = Sheet.y1;
			Sint32 w = Sheet.x2 - Sheet.x1;
			Sint32 h = Sheet.y2 - Sheet.y1;
			CRect2D<Sint32> Src( x, y, w, h );
			m_pSprites[Sheet.SheetNo]->DrawSquareRotate(
				Dst,
				Src,
				Color,
				Angle );
		}

		return ((Chara <= 0xFF) ? (1) : (2));
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
	������̕����擾���܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pStr			[in] ������̊i�[���ꂽ�o�b�t�@
	@param Px			[in] �`��J�n�z��ʒu
	@param Py			[in] �`��J�n�z��ʒu

	@return �`���̈ʒu
*/
//-----------------------------------------------------------------------------------
CPoint2D<Sint32> CFontSprite2D::GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// �����R�[�h
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// ���s
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.x;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// �^�u
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// �o�b�N�X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// �X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}
		else
		{
			//-------------------------------------------------------
			// �����f�[�^������ꍇ
			//-------------------------------------------------------
			Uint16 Index = m_IndexTbl[Code];
			if ( Index != 0xFFFF )
			{
				SFontSheetData Sheet = m_pSheetTbl[Index];
				if ( Sheet.SheetNo != -1 )
				{
					if ( Code <= 0xFF )
					{
						PosX += m_FontSize / 2;
					}
					else
					{
						PosX += m_FontSize;
					}
				}
				else
				{
					PosX += m_FontSize;
				}
			}
			//-------------------------------------------------------
			// �����f�[�^�������ꍇ
			//-------------------------------------------------------
			else
			{
				PosX += m_FontSize;
			}
		}
	}

	Pos.x = PosX;
	Pos.y = PosY;

	return Pos;
}


//-----------------------------------------------------------------------------------
/**
	������̕����擾���܂�

	@param lFontSpr		[in] �t�H���g�X�v���C�g�n���h��
	@param pStr			[in] ������̊i�[���ꂽ�o�b�t�@
	@param Px			[in] �`��J�n�z��ʒu
	@param Py			[in] �`��J�n�z��ʒu

	@return �`���̈ʒu
*/
//-----------------------------------------------------------------------------------
CPoint2D<Sint32> CFontSprite2D::GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// �����R�[�h
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// ���s
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.x;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// �^�u
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// �o�b�N�X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// �X�y�[�X
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}
		else
		{
			//-------------------------------------------------------
			// �����f�[�^������ꍇ
			//-------------------------------------------------------
			Uint16 Index = m_IndexTbl[Code];
			if ( Index != 0xFFFF )
			{
				SFontSheetData Sheet = m_pSheetTbl[Index];
				if ( Sheet.SheetNo != -1 )
				{
					PosX += Sheet.abcB + 1;
				}
				else
				{
					PosX += m_FontSize;
				}
			}
			//-------------------------------------------------------
			// �����f�[�^�������ꍇ
			//-------------------------------------------------------
			else
			{
				PosX += m_FontSize;
			}
		}
	}

	Pos.x = PosX;
	Pos.y = PosY;

	return Pos;
}

