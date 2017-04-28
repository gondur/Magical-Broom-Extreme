

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Core/CCore.h"
#include "Core/CDevice.h"
#include "Surface/CTexture.h"

#include "Render/CFont.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
static const Uint8 g_AlphaTbl[] = {
	0x00, 0x03, 0x07, 0x0B, 0x0F, 0x13, 0x17, 0x1B,
	0x1F, 0x23, 0x27, 0x2B, 0x2F, 0x33, 0x37, 0x3B,
	0x3F, 0x43, 0x47, 0x4B, 0x4F, 0x53, 0x57, 0x5B,
	0x5F, 0x63, 0x67, 0x6B, 0x6F, 0x73, 0x77, 0x7B,
	0x7F, 0x83, 0x87, 0x8B, 0x8F, 0x93, 0x97, 0x9B,
	0x9F, 0xA3, 0xA7, 0xAB, 0xAF, 0xB3, 0xB7, 0xBB,
	0xBF, 0xC3, 0xC7, 0xCB, 0xCF, 0xD3, 0xD7, 0xDB,
	0xDF, 0xE3, 0xE7, 0xEB, 0xEF, 0xF3, 0xF7, 0xFB,
	0xFF,
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFont::CFont( CBaseMgr *pMgr ) : CDeviceObject( pMgr )
{
	m_hDC			= NULL;
	m_hFont			= NULL;
	m_hFontOld		= NULL;
	m_pTarget		= NULL;
	m_pBuffer		= NULL;
	m_FontSize		= 0;
	m_IsBegin		= false;
	m_IsAlpha		= false;
	m_IsUpdate		= false;
	MemoryClear( &m_TextMetric, sizeof(m_TextMetric) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFont::~CFont()
{
	// �t�H���g������ꍇ�͉��
	if ( m_pBuffer != NULL )
	{
		::DeleteObject( m_hFont );
		SAFE_DELETE_ARRAY( m_pBuffer );
	}

	SAFE_RELEASE( m_pTarget );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::OnResetDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFont::Create( const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold )
{
	//--------------------------------------------------------------
	// �t�H���g�o�b�t�@
	//--------------------------------------------------------------
	SAFE_DELETE( m_pBuffer );
	m_pBuffer = new char [ (FontSize * 2) * (FontSize * 2) ];
	if ( m_pBuffer == NULL )
	{
		return false;
	}

	///CCore::Logout( " } " );

	//--------------------------------------------------------------
	// �t�H���g����
	//--------------------------------------------------------------
	m_hFont = ::CreateFont(
					FontSize,					// �t�H���g����
					0,							// ������
					0,							// �e�L�X�g�̊p�x	
					0,							// �x�[�X���C���Ƃ����Ƃ̊p�x
					((IsBold)?(1000):(0)),		// �t�H���g�̏d���i�����j
					IsItalic,					// �C�^���b�N��
					false,						// �A���_�[���C��
					false,						// �ł�������
					SHIFTJIS_CHARSET,			// �����Z�b�g
					OUT_TT_PRECIS,				// �o�͐��x
					CLIP_DEFAULT_PRECIS,		// �N���b�s���O���x
					PROOF_QUALITY,				// �o�͕i��
					FIXED_PITCH | FF_MODERN,	// �s�b�`�ƃt�@�~���[
					pFontFace );				// ���̖�

	//--------------------------------------------------------------
	// �f�[�^�ݒ�
	//--------------------------------------------------------------
	m_FontSize = FontSize;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::GetFontBuffer( HDC hDC, Uint16 Code, GLYPHMETRICS *pGM, char **ppData, Bool Alpha )
{
	//--------------------------------------------------------------
	// ��]�Ȃǂ��s��ŗ^����
	// | 1 0 |
	// | 0 1 |
	//--------------------------------------------------------------
    static Sint32 m11 = (Sint32)(1.0f * 65536.0f);
	static Sint32 m12 = (Sint32)(0.0f * 65536.0f);
    static Sint32 m21 = (Sint32)(0.0f * 65536.0f);
	static Sint32 m22 = (Sint32)(1.0f * 65536.0f);

	MAT2 Matrix;
	Matrix.eM11 = *((FIXED *)&m11);		Matrix.eM12 = *((FIXED *)&m12);
	Matrix.eM21 = *((FIXED *)&m21);		Matrix.eM22 = *((FIXED *)&m22);

	//--------------------------------------------------------------
	// �t�H���g�f�[�^�擾
	//--------------------------------------------------------------
	Uint32 Flag = (Alpha) ? (GGO_GRAY8_BITMAP) : (GGO_BITMAP);

	// �o�b�t�@�T�C�Y��M
	Sint32 Size = ::GetGlyphOutline( hDC, Code, Flag, pGM, 0, NULL, &Matrix );
	// �o�b�t�@�Ƀt�H���g��M
	::GetGlyphOutline( hDC, Code, Flag, pGM, Size, *ppData, &Matrix );

	return Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::GetFontSize( void )
{
	return m_FontSize;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::SetDestination( CTexture *pTarget )
{
	SAFE_RELEASE( m_pTarget );

	m_pTarget = pTarget;
	if ( m_pTarget != NULL ) m_pTarget->AddRef();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::Begin( Bool IsUpdate )
{
	m_IsBegin = true;

	// �f�o�C�X�R���e�L�X�g�A�Â��t�H���g���擾
	m_hDC      = ::GetDC( GetWindow() );
	m_hFontOld = (HFONT)::SelectObject( m_hDC, m_hFont );

	// �t�H���g�����擾
	::GetTextMetrics( m_hDC, &m_TextMetric );

	// �]����t�H�[�}�b�g�`�F�b�N
	m_IsUpdate = IsUpdate;
	m_IsAlpha = false;
	if ( m_pTarget != NULL )
	{
		switch ( m_pTarget->GetFormat() )
		{
		case D3DFMT_A4R4G4B4:
		case D3DFMT_X4R4G4B4:
		case D3DFMT_A8R8G8B8:
		case D3DFMT_X8R8G8B8:
			m_IsAlpha = true;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::End( void )
{
	if ( m_IsBegin )
	{
		m_IsBegin = false;

		::SelectObject( m_hDC, m_hFontOld );
		::ReleaseDC( GetWindow(), m_hDC );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFont::LockTarget( void **ppBits, Sint32 *pPitch, D3DFORMAT *pFormat, Sint32 *pWidth, Sint32 *pHeight )
{
	if ( m_pTarget->LockRect( NULL, ppBits, (Uint32*)pPitch, (Uint32*)pWidth, (Uint32*)pHeight, pFormat ) )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::UnlockTarget( void )
{
	m_pTarget->UnLockRect();
	if ( m_IsUpdate )
	{
		m_pTarget->UpdateTexture();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawChar( Sint32 Px, Sint32 Py, CColor Color, Uint16 Code )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	if ( LockTarget( &FontDrawRect[0].pBits, &FontDrawRect[0].Pitch, &TargetFormat, &TargetWidth, &TargetHeight ) )
	{
		//==================================================
		// �t�H���g�o�b�t�@�擾
		//==================================================
		GLYPHMETRICS GlyphMetrics;
		Uint32 DataSize = CFont::GetFontBuffer( m_hDC, Code, &GlyphMetrics, &m_pBuffer, false );

		//==================================================
		// �]�����f�[�^
		//==================================================
		FontDrawRect[1].x1		= 0;
		FontDrawRect[1].y1		= 0;
		FontDrawRect[1].x2		= (Sint32)GlyphMetrics.gmBlackBoxX;
		FontDrawRect[1].y2		= (Sint32)GlyphMetrics.gmBlackBoxY;
		FontDrawRect[1].Pitch	= (DataSize / GlyphMetrics.gmBlackBoxY) & ~0x03;
		FontDrawRect[1].pBits	= m_pBuffer;

		//==================================================
		// �]����f�[�^
		//==================================================
		FontDrawRect[0].x1 = Px;
		FontDrawRect[0].y1 = Py + m_TextMetric.tmAscent - GlyphMetrics.gmptGlyphOrigin.y;
		FontDrawRect[0].x2 = FontDrawRect[0].x1 + (Sint32)GlyphMetrics.gmBlackBoxX;
		FontDrawRect[0].y2 = FontDrawRect[0].y1 + (Sint32)GlyphMetrics.gmBlackBoxY;

		//==================================================
		// �N���b�s���O��ɕ`��\�Ȃ�`��
		//==================================================
		if ( Clip( &FontDrawRect[0], &FontDrawRect[1], TargetWidth, TargetHeight ) )
		{
			switch ( TargetFormat )
			{
			case D3DFMT_X1R5G5B5:
				DrawPixel1555( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_A1R5G5B5:
				DrawPixel1555( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_R5G6B5:
				DrawPixel565( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_X4R4G4B4:
				DrawPixel4444( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_A4R4G4B4:
				DrawPixel4444( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_X8R8G8B8:
				DrawPixel8888( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_A8R8G8B8:
				DrawPixel8888( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			}
		}

		UnlockTarget();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawCharAA( Sint32 Px, Sint32 Py, CColor Color, Uint16 Code )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	if ( !m_IsAlpha )
	{
		DrawChar( Px, Py, Color, Code );
		return;
	}

	if ( LockTarget( &FontDrawRect[0].pBits, &FontDrawRect[0].Pitch, &TargetFormat, &TargetWidth, &TargetHeight ) )
	{
		//==================================================
		// �t�H���g�o�b�t�@�擾
		//==================================================
		GLYPHMETRICS GlyphMetrics;
		Uint32 DataSize = GetFontBuffer( m_hDC, Code, &GlyphMetrics, &m_pBuffer, true );

		//==================================================
		// �]�����f�[�^
		//==================================================
		FontDrawRect[1].x1 = 0;
		FontDrawRect[1].y1 = 0;
		FontDrawRect[1].x2 = (Sint32)GlyphMetrics.gmBlackBoxX;
		FontDrawRect[1].y2 = (Sint32)GlyphMetrics.gmBlackBoxY;
		FontDrawRect[1].Pitch = (DataSize / GlyphMetrics.gmBlackBoxY) & ~0x03;
		FontDrawRect[1].pBits = m_pBuffer;

		//==================================================
		// �]����f�[�^
		//==================================================
		FontDrawRect[0].x1 = Px;
		FontDrawRect[0].y1 = Py + m_TextMetric.tmAscent - GlyphMetrics.gmptGlyphOrigin.y;
		FontDrawRect[0].x2 = FontDrawRect[0].x1 + (Sint32)GlyphMetrics.gmBlackBoxX;
		FontDrawRect[0].y2 = FontDrawRect[0].y1 + (Sint32)GlyphMetrics.gmBlackBoxY;

		//==================================================
		// �N���b�s���O��ɕ`��\�Ȃ�`��
		//==================================================
		if ( Clip( &FontDrawRect[0], &FontDrawRect[1], TargetWidth, TargetHeight ) )
		{
			switch ( TargetFormat )
			{
			case D3DFMT_X4R4G4B4:
				DrawPixel4444AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_A4R4G4B4:
				DrawPixel4444AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_X8R8G8B8:
				DrawPixel8888AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			case D3DFMT_A8R8G8B8:
				DrawPixel8888AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
				break;
			}
		}

		UnlockTarget();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::DrawText( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	Sint32 pos_x = Px;
	Sint32 pos_y = Py;

	if ( LockTarget( &FontDrawRect[0].pBits, &FontDrawRect[0].Pitch, &TargetFormat, &TargetWidth, &TargetHeight ) )
	{
		//----------------------------------------------------------------
		// �`�敶���񐶐�
		//----------------------------------------------------------------
		// ������
		size_t len = wcslen( pStr );

		//----------------------------------------------------------------
		// �����`��
		//----------------------------------------------------------------
		Uint32 i = 0;
		while ( i < len )
		{
			//----------------------------------------------------------------
			// �����R�[�h
			//----------------------------------------------------------------
			Uint16 Code = pStr[i++];

			// �t�H���g���擾
			ABC Abc;
			CFont::GetFontData( Code, &Abc );
			pos_x += Abc.abcA;

			//----------------------------------------------------------------
			// ���s
			//----------------------------------------------------------------
			if ( (Code == L'\n') || (Code == L'\r') )
			{
				pos_x = Px;
				pos_y += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �^�u
			//----------------------------------------------------------------
			if ( Code == L'\t' )
			{
				pos_x += m_TextMetric.tmHeight * 4;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L' ' )
			{
				pos_x += m_TextMetric.tmHeight / 2;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L'�@' )
			{
				pos_x += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �`�悷��
			//----------------------------------------------------------------
			else
			{
				Uint32 Width = (Code <= 0xFF) ? m_TextMetric.tmHeight/2 : m_TextMetric.tmHeight;

				//==================================================
				// �t�H���g�o�b�t�@�擾
				//==================================================
				GLYPHMETRICS GlyphMetrics;
				Uint32 DataSize = GetFontBuffer( m_hDC, Code, &GlyphMetrics, &m_pBuffer, false );

				//==================================================
				// �]�����f�[�^
				//==================================================
				FontDrawRect[1].x1 = 0;
				FontDrawRect[1].y1 = 0;
				FontDrawRect[1].x2 = (Sint32)GlyphMetrics.gmBlackBoxX;
				FontDrawRect[1].y2 = (Sint32)GlyphMetrics.gmBlackBoxY;
				FontDrawRect[1].Pitch = (DataSize / GlyphMetrics.gmBlackBoxY) & ~0x03;
				FontDrawRect[1].pBits = m_pBuffer;

				//==================================================
				// �]����f�[�^
				//==================================================
				FontDrawRect[0].x1 = pos_x;
				FontDrawRect[0].y1 = pos_y + m_TextMetric.tmAscent - GlyphMetrics.gmptGlyphOrigin.y;
				FontDrawRect[0].x2 = FontDrawRect[0].x1 + (Sint32)GlyphMetrics.gmBlackBoxX;
				FontDrawRect[0].y2 = FontDrawRect[0].y1 + (Sint32)GlyphMetrics.gmBlackBoxY;

				//==================================================
				// �N���b�s���O��ɕ`��\�Ȃ�`��
				//==================================================
				if ( Clip( &FontDrawRect[0], &FontDrawRect[1], TargetWidth, TargetHeight ) )
				{
					switch ( TargetFormat )
					{
					case D3DFMT_X1R5G5B5:
						DrawPixel1555( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A1R5G5B5:
						DrawPixel1555( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_R5G6B5:
						DrawPixel565( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_X4R4G4B4:
						DrawPixel4444( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A4R4G4B4:
						DrawPixel4444( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_X8R8G8B8:
						DrawPixel8888( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A8R8G8B8:
						DrawPixel8888( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					}
				}
				pos_x += Width - Abc.abcA;
			}
		}

		UnlockTarget();
	}

	return pos_x - Px;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::DrawTextAA( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	if ( !m_IsAlpha ) return DrawText( Px, Py, Color, pStr );

	Sint32 pos_x = Px;
	Sint32 pos_y = Py;

	if ( LockTarget( &FontDrawRect[0].pBits, &FontDrawRect[0].Pitch, &TargetFormat, &TargetWidth, &TargetHeight ) )
	{
		//----------------------------------------------------------------
		// �`�敶���񐶐�
		//----------------------------------------------------------------
		// ������
		size_t len = wcslen( pStr );

		//----------------------------------------------------------------
		// �����`��
		//----------------------------------------------------------------
		Uint32 i = 0;
		while ( i < len )
		{
			//----------------------------------------------------------------
			// �����R�[�h
			//----------------------------------------------------------------
			Uint16 Code = pStr[i++];

			// �t�H���g���擾
			ABC Abc;
			CFont::GetFontData( Code, &Abc );
			pos_x += Abc.abcA;

			//----------------------------------------------------------------
			// ���s
			//----------------------------------------------------------------
			if ( (Code == L'\n') || (Code == L'\r') )
			{
				pos_x = Px;
				pos_y += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �^�u
			//----------------------------------------------------------------
			if ( Code == L'\t' )
			{
				pos_x += m_TextMetric.tmHeight * 4;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L' ' )
			{
				pos_x += m_TextMetric.tmHeight / 2;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L'�@' )
			{
				pos_x += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �`�悷��
			//----------------------------------------------------------------
			else
			{
				Uint32 Width = (Code <= 0xFF) ? m_TextMetric.tmHeight/2 : m_TextMetric.tmHeight;

				//==================================================
				// �t�H���g�o�b�t�@�擾
				//==================================================
				GLYPHMETRICS GlyphMetrics;
				Uint32 DataSize = GetFontBuffer( m_hDC, Code, &GlyphMetrics, &m_pBuffer, true );

				//==================================================
				// �]�����f�[�^
				//==================================================
				FontDrawRect[1].x1 = 0;
				FontDrawRect[1].y1 = 0;
				FontDrawRect[1].x2 = (Sint32)GlyphMetrics.gmBlackBoxX;
				FontDrawRect[1].y2 = (Sint32)GlyphMetrics.gmBlackBoxY;
				FontDrawRect[1].Pitch = (DataSize / GlyphMetrics.gmBlackBoxY) & ~0x03;
				FontDrawRect[1].pBits = m_pBuffer;

				//==================================================
				// �]����f�[�^
				//==================================================
				FontDrawRect[0].x1 = pos_x;
				FontDrawRect[0].y1 = pos_y + m_TextMetric.tmAscent - GlyphMetrics.gmptGlyphOrigin.y;
				FontDrawRect[0].x2 = FontDrawRect[0].x1 + (Sint32)GlyphMetrics.gmBlackBoxX;
				FontDrawRect[0].y2 = FontDrawRect[0].y1 + (Sint32)GlyphMetrics.gmBlackBoxY;

				//==================================================
				// �N���b�s���O��ɕ`��\�Ȃ�`��
				//==================================================
				if ( Clip( &FontDrawRect[0], &FontDrawRect[1], TargetWidth, TargetHeight ) )
				{
					switch ( TargetFormat )
					{
					case D3DFMT_X4R4G4B4:
						DrawPixel4444AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A4R4G4B4:
						DrawPixel4444AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_X8R8G8B8:
						DrawPixel8888AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A8R8G8B8:
						DrawPixel8888AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					}
				}

				pos_x += Width - Abc.abcA;
			}
		}

		UnlockTarget();
	}

	return pos_x - Px;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::DrawPText( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	Sint32 pos_x = Px;
	Sint32 pos_y = Py;

	if ( LockTarget( &FontDrawRect[0].pBits, &FontDrawRect[0].Pitch, &TargetFormat, &TargetWidth, &TargetHeight ) )
	{
		//----------------------------------------------------------------
		// �`�敶���񐶐�
		//----------------------------------------------------------------
		// ������
		size_t len = wcslen( pStr );

		//----------------------------------------------------------------
		// �����`��
		//----------------------------------------------------------------
		Uint32 i = 0;
		while ( i < len )
		{
			//----------------------------------------------------------------
			// �����R�[�h
			//----------------------------------------------------------------
			Uint16 Code = pStr[i++];

			// �t�H���g���擾
			ABC Abc;
			CFont::GetFontData( Code, &Abc );

			//----------------------------------------------------------------
			// ���s
			//----------------------------------------------------------------
			if ( (Code == L'\n') || (Code == L'\r') )
			{
				pos_x = Px;
				pos_y += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �^�u
			//----------------------------------------------------------------
			if ( Code == L'\t' )
			{
				pos_x += m_TextMetric.tmHeight * 4;
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
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L' ' )
			{
				pos_x += m_TextMetric.tmHeight / 2;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L'�@' )
			{
				pos_x += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �`�悷��
			//----------------------------------------------------------------
			else
			{
				//==================================================
				// �t�H���g�o�b�t�@�擾
				//==================================================
				GLYPHMETRICS GlyphMetrics;
				Uint32 DataSize = GetFontBuffer( m_hDC, Code, &GlyphMetrics, &m_pBuffer, false );

				//==================================================
				// �]�����f�[�^
				//==================================================
				FontDrawRect[1].x1 = 0;
				FontDrawRect[1].y1 = 0;
				FontDrawRect[1].x2 = (Sint32)GlyphMetrics.gmBlackBoxX;
				FontDrawRect[1].y2 = (Sint32)GlyphMetrics.gmBlackBoxY;
				FontDrawRect[1].Pitch = (DataSize / GlyphMetrics.gmBlackBoxY) & ~0x03;
				FontDrawRect[1].pBits = m_pBuffer;

				//==================================================
				// �]����f�[�^
				//==================================================
				FontDrawRect[0].x1 = pos_x;
				FontDrawRect[0].y1 = pos_y + m_TextMetric.tmAscent - GlyphMetrics.gmptGlyphOrigin.y;
				FontDrawRect[0].x2 = FontDrawRect[0].x1 + (Sint32)GlyphMetrics.gmBlackBoxX;
				FontDrawRect[0].y2 = FontDrawRect[0].y1 + (Sint32)GlyphMetrics.gmBlackBoxY;

				//==================================================
				// �N���b�s���O��ɕ`��\�Ȃ�`��
				//==================================================
				if ( Clip( &FontDrawRect[0], &FontDrawRect[1], TargetWidth, TargetHeight ) )
				{
					switch ( TargetFormat )
					{
					case D3DFMT_X1R5G5B5:
						DrawPixel1555( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A1R5G5B5:
						DrawPixel1555( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_R5G6B5:
						DrawPixel565( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_X4R4G4B4:
						DrawPixel4444( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A4R4G4B4:
						DrawPixel4444( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_X8R8G8B8:
						DrawPixel8888( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					case D3DFMT_A8R8G8B8:
						DrawPixel8888( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
						break;
					}
				}
				pos_x += Abc.abcB;
			}
		}

		UnlockTarget();
	}

	return pos_x - Px;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::DrawPTextAA( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	if ( !m_IsAlpha ) return DrawPText( Px, Py, Color, pStr );

	Sint32 pos_x = Px;
	Sint32 pos_y = Py;

	if ( LockTarget( &FontDrawRect[0].pBits, &FontDrawRect[0].Pitch, &TargetFormat, &TargetWidth, &TargetHeight ) )
	{
		//----------------------------------------------------------------
		// �`�敶���񐶐�
		//----------------------------------------------------------------
		// ������
		size_t len = wcslen( pStr );

		//----------------------------------------------------------------
		// �����`��
		//----------------------------------------------------------------
		Uint32 i = 0;
		while ( i < len )
		{
			//----------------------------------------------------------------
			// �����R�[�h
			//----------------------------------------------------------------
			Uint16 Code = pStr[i++];

			// �t�H���g���擾
			ABC Abc;
			CFont::GetFontData( Code, &Abc );

			//----------------------------------------------------------------
			// ���s
			//----------------------------------------------------------------
			if ( (Code == L'\n') || (Code == L'\r') )
			{
				pos_x = Px;
				pos_y += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �^�u
			//----------------------------------------------------------------
			if ( Code == L'\t' )
			{
				pos_x += m_TextMetric.tmHeight * 4;
				continue;
			}
			//----------------------------------------------------------------
			// �o�b�N�X�y�[�X
			//----------------------------------------------------------------
			if ( Code == L'\b' )
			{
				pos_x -= m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L' ' )
			{
				pos_x += m_TextMetric.tmHeight / 2;
				continue;
			}
			//----------------------------------------------------------------
			// �X�y�[�X�Ȃ�`�悵�Ȃ�
			//----------------------------------------------------------------
			if ( Code == L'�@' )
			{
				pos_x += m_TextMetric.tmHeight;
				continue;
			}
			//----------------------------------------------------------------
			// �`�悷��
			//----------------------------------------------------------------

			//==================================================
			// �t�H���g�o�b�t�@�擾
			//==================================================
			GLYPHMETRICS GlyphMetrics;
			Uint32 DataSize = GetFontBuffer( m_hDC, Code, &GlyphMetrics, &m_pBuffer, true );

			//==================================================
			// �]�����f�[�^
			//==================================================
			FontDrawRect[1].x1 = 0;
			FontDrawRect[1].y1 = 0;
			FontDrawRect[1].x2 = (Sint32)GlyphMetrics.gmBlackBoxX;
			FontDrawRect[1].y2 = (Sint32)GlyphMetrics.gmBlackBoxY;
			FontDrawRect[1].Pitch = (DataSize / GlyphMetrics.gmBlackBoxY) & ~0x03;
			FontDrawRect[1].pBits = m_pBuffer;

			//==================================================
			// �]����f�[�^
			//==================================================
			FontDrawRect[0].x1 = pos_x;
			FontDrawRect[0].y1 = pos_y + m_TextMetric.tmAscent - GlyphMetrics.gmptGlyphOrigin.y;
			FontDrawRect[0].x2 = FontDrawRect[0].x1 + (Sint32)GlyphMetrics.gmBlackBoxX;
			FontDrawRect[0].y2 = FontDrawRect[0].y1 + (Sint32)GlyphMetrics.gmBlackBoxY;

			//==================================================
			// �N���b�s���O��ɕ`��\�Ȃ�`��
			//==================================================
			if ( Clip( &FontDrawRect[0], &FontDrawRect[1], TargetWidth, TargetHeight ) )
			{
				switch ( TargetFormat )
				{
				case D3DFMT_X4R4G4B4:
					DrawPixel4444AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
					break;
				case D3DFMT_A4R4G4B4:
					DrawPixel4444AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
					break;
				case D3DFMT_X8R8G8B8:
					DrawPixel8888AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
					break;
				case D3DFMT_A8R8G8B8:
					DrawPixel8888AA( (D3DCOLOR)Color, &FontDrawRect[0], &FontDrawRect[1] );
					break;
				}
			}

			pos_x += Abc.abcB;
		}

		UnlockTarget();
	}

	return pos_x - Px;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawPixel565( Sint32 Color, FontDrawRect *pDst, FontDrawRect *pSrc )
{
	//==================================================
	// �F�쐬
	//==================================================
	Uint8 r = (Uint8)(((Uint8)(Color>>16))>>3);
	Uint8 g = (Uint8)(((Uint8)(Color>> 8))>>2);
	Uint8 b = (Uint8)(((Uint8)(Color>> 0))>>3);
	Color = (r<<11) | (g<<5) | (b<<0);

	//==================================================
	// �T�[�t�F�C�X�ւ̃|�C���^
	//==================================================
	Uint16 *pd = (Uint16 *)pDst->pBits;
	Sint32 dp = pDst->Pitch >> 1;

	const Uint8 *ps = (const Uint8 *)pSrc->pBits;
	Sint32 sp = pSrc->Pitch;

	//==================================================
	// �]����̃T�[�t�F�C�X�̎n�_
	//==================================================
	pd += (pDst->x1) + (pDst->y1 * dp);

	//==================================================
	// �]��
	//==================================================
	for ( Sint32 Py = pSrc->y1; Py < pSrc->y2; Py++ )
	{
		Sint32 Px2 = 0;
		for ( Sint32 Px = pSrc->x1; Px < pSrc->x2; Px++ )
		{
			Sint32 shift = 7-(Px&7);
			Sint32 no = Px>>3;
			if ( (ps[no]>>shift)&0x01 ) pd[Px2] = (Uint16)Color;
			Px2++;
		}
		pd += dp;
		ps += sp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawPixel1555( Sint32 Color, FontDrawRect *pDst, FontDrawRect *pSrc )
{
	//==================================================
	// �F�쐬
	//==================================================
	Uint8 r = (Uint8)(((Uint8)(Color>>16))>>3);
	Uint8 g = (Uint8)(((Uint8)(Color>> 8))>>3);
	Uint8 b = (Uint8)(((Uint8)(Color>> 0))>>3);
	Color = (1<<15) | (r<<10) | (g<<5) | (b<<0);

	//==================================================
	// �T�[�t�F�C�X�ւ̃|�C���^
	//==================================================
	Uint16 *pd = (Uint16 *)pDst->pBits;
	Sint32 dp = pDst->Pitch >> 1;

	const Uint8 *ps = (const Uint8 *)pSrc->pBits;
	Sint32 sp = pSrc->Pitch;

	//==================================================
	// �]����̃T�[�t�F�C�X�̎n�_
	//==================================================
	pd += (pDst->x1) + (pDst->y1 * dp);

	//==================================================
	// �]��
	//==================================================
	for ( Sint32 Py = pSrc->y1; Py < pSrc->y2; Py++ )
	{
		Sint32 Px2 = 0;
		for ( Sint32 Px = pSrc->x1; Px < pSrc->x2; Px++ )
		{
			Sint32 shift = 7-(Px&7);
			Sint32 no = Px>>3;
			if ( (ps[no]>>shift)&0x01 ) pd[Px2] = (Uint16)Color;
			Px2++;
		}
		pd += dp;
		ps += sp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawPixel4444( Sint32 Color, FontDrawRect *pDst, FontDrawRect *pSrc )
{
	//==================================================
	// �F�쐬
	//==================================================
	Uint8 r = (Uint8)(((Uint8)(Color>>16))>>4);
	Uint8 g = (Uint8)(((Uint8)(Color>> 8))>>4);
	Uint8 b = (Uint8)(((Uint8)(Color>> 0))>>4);
	Color = (15<<12) | (r<<8) | (g<<4) | (b<<0);

	//==================================================
	// �T�[�t�F�C�X�ւ̃|�C���^
	//==================================================
	Uint16 *pd = (Uint16 *)pDst->pBits;
	Sint32 dp = pDst->Pitch >> 1;

	const Uint8 *ps = (const Uint8 *)pSrc->pBits;
	Sint32 sp = pSrc->Pitch;

	//==================================================
	// �]����̃T�[�t�F�C�X�̎n�_
	//==================================================
	pd += (pDst->x1) + (pDst->y1 * dp);

	//==================================================
	// �]��
	//==================================================
	for ( Sint32 Py = pSrc->y1; Py < pSrc->y2; Py++ )
	{
		Sint32 Px2 = 0;
		for ( Sint32 Px = pSrc->x1; Px < pSrc->x2; Px++ )
		{
			Sint32 shift = 7-(Px&7);
			Sint32 no = Px>>3;
			if ( ((ps[no] >> shift) & 0x01) != 0x00 )
			{
				pd[Px2] = (Uint16)Color;
			}
			Px2++;
		}
		pd += dp;
		ps += sp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawPixel8888( Sint32 Color, FontDrawRect *pDst, FontDrawRect *pSrc )
{
	//==================================================
	// �F�쐬
	//==================================================
	Color |= 0xFF000000;

	//==================================================
	// �T�[�t�F�C�X�ւ̃|�C���^
	//==================================================
	Uint32 *pd = (Uint32 *)pDst->pBits;
	Sint32 dp = pDst->Pitch >> 2;

	const Uint8 *ps = (const Uint8 *)pSrc->pBits;
	Sint32 sp = pSrc->Pitch;

	//==================================================
	// �]����̃T�[�t�F�C�X�̎n�_
	//==================================================
	pd += (pDst->x1) + (pDst->y1 * dp);

	//==================================================
	// �]��
	//==================================================
	for ( Sint32 Py = pSrc->y1; Py < pSrc->y2; Py++ )
	{
		Sint32 Px2 = 0;
		for ( Sint32 Px = pSrc->x1; Px < pSrc->x2; Px++ )
		{
			Sint32 shift = 7 - (Px & 7);
			Sint32 no = Px >> 3;
			if ( ((ps[no] >> shift) & 0x01) != 0x00 )
			{
				pd[Px2] = Color;
			}
			Px2++;
		}
		pd += dp;
		ps += sp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawPixel4444AA( Sint32 Color, FontDrawRect *pDst, FontDrawRect *pSrc )
{
	//==================================================
	// �F�쐬
	//==================================================
	Uint8 r = (Uint8)(((Uint8)(Color>>16))>>4);
	Uint8 g = (Uint8)(((Uint8)(Color>> 8))>>4);
	Uint8 b = (Uint8)(((Uint8)(Color>> 0))>>4);
	Color = (r<<8) | (g<<4) | (b<<0);

	//==================================================
	// �T�[�t�F�C�X�ւ̃|�C���^
	//==================================================
	Uint16 *pd = (Uint16 *)pDst->pBits;
	Sint32 dp = pDst->Pitch >> 1;

	const Uint8 *ps = (const Uint8 *)pSrc->pBits;
	Sint32 sp = pSrc->Pitch;

	//==================================================
	// �]����̃T�[�t�F�C�X�̎n�_
	//==================================================
	pd += (pDst->x1) + (pDst->y1 * dp);

	//==================================================
	// �]��
	//==================================================
	for ( Sint32 Py = pSrc->y1; Py < pSrc->y2; Py++ )
	{
		Sint32 Px2 = 0;
		for ( Sint32 Px = pSrc->x1; Px < pSrc->x2; Px++ )
		{
			pd[Px2++] = (Uint16)(Color | ((g_AlphaTbl[ps[Px]]>>4)<<12));
		}
		pd += dp;
		ps += sp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::DrawPixel8888AA( Sint32 Color, FontDrawRect *pDst, FontDrawRect *pSrc )
{
	//==================================================
	// �F�쐬
	//==================================================
	Color &= 0x00FFFFFF;

	//==================================================
	// �T�[�t�F�C�X�ւ̃|�C���^
	//==================================================
	Uint32 *pd = (Uint32 *)pDst->pBits;
	Sint32 dp = pDst->Pitch >> 2;

	const Uint8 *ps = (const Uint8 *)pSrc->pBits;
	Sint32 sp = pSrc->Pitch;

	//==================================================
	// �]����̃T�[�t�F�C�X�̎n�_
	//==================================================
	pd += (pDst->x1) + (pDst->y1 * dp);

	//==================================================
	// �]��
	//==================================================
	for ( Sint32 Py = pSrc->y1; Py < pSrc->y2; Py++ )
	{
		Sint32 Px2 = 0;
		for ( Sint32 Px = pSrc->x1; Px < pSrc->x2; Px++ )
		{
			pd[Px2++] = (Color | (g_AlphaTbl[ps[Px]]<<24));
		}
		pd += dp;
		ps += sp;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFont::Clip( FontDrawRect *pDst, FontDrawRect *pSrc, Sint32 Width, Sint32 Height )
{
	// ���[
	if ( pDst->x1 < 0 )
	{
		pSrc->x1 -= pDst->x1;
		pDst->x1 = 0;
	}
	// �E�[
	if ( pDst->x2 > Width )
	{
		pSrc->x2 -= (pDst->x2 - Width);
		pDst->x2 = Width;
	}
	// ��[
	if ( pDst->y1 < 0 )
	{
		pSrc->y1 -= pDst->y1;
		pDst->y1 = 0;
	}
	// ���[
	if ( pDst->y2 > Height )
	{
		pSrc->y2 -= (pDst->y2 - Height);
		pDst->y2 = Height;
	}

	// ��ʊO�Ȃ�`��s�v
	if ( pDst->x2 < pDst->x1 ) return false;
	if ( pDst->y2 < pDst->y1 ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFont::GetFontData( Uint16 Code, ABC *pABC )
{
	::GetCharABCWidths( m_hDC, Code, Code, pABC );

    static Sint32 m11 = (Sint32)(1.0 * 65536.0);
	static Sint32 m12 = (Sint32)(0.0 * 65536.0);
    static Sint32 m21 = (Sint32)(0.0 * 65536.0);
	static Sint32 m22 = (Sint32)(1.0 * 65536.0);

	MAT2 Matrix;
	Matrix.eM11 = *((FIXED *)&m11);	Matrix.eM12 = *((FIXED *)&m12);
	Matrix.eM21 = *((FIXED *)&m21);	Matrix.eM22 = *((FIXED *)&m22);

	GLYPHMETRICS GlyphMetrics;
	::GetGlyphOutline( m_hDC, Code, GGO_GRAY8_BITMAP, &GlyphMetrics, 0, NULL, &Matrix );

	if ( pABC->abcB < GlyphMetrics.gmBlackBoxX ) pABC->abcB = GlyphMetrics.gmBlackBoxX;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFont::GetTextWidth( const wchar_t *pStr )
{
	static FontDrawRect FontDrawRect[2];
	static D3DFORMAT TargetFormat;
	static Sint32 TargetWidth, TargetHeight;

	Sint32 pos_x = 0;
	Sint32 pos_y = 0;

	//----------------------------------------------------------------
	// �`�敶���񐶐�
	//----------------------------------------------------------------
	wchar_t Text[1024] = L"";
	::StringCbVPrintf( Text, sizeof(Text), pStr, (char *)(&pStr + 1) );

	// ������
	size_t Len = wcslen( Text );

	//----------------------------------------------------------------
	// �����`��
	//----------------------------------------------------------------
	Uint32 i = 0;
	while ( i < Len )
	{
		//----------------------------------------------------------------
		// �����R�[�h
		//----------------------------------------------------------------
		Uint16 Code = pStr[i++];

		// �t�H���g���擾
		ABC Abc;
		CFont::GetFontData( Code, &Abc );
		pos_x += Abc.abcA;

		//----------------------------------------------------------------
		// ���s
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			pos_x = 0;
			pos_y += m_TextMetric.tmHeight;
			continue;
		}
		//----------------------------------------------------------------
		// �^�u
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			pos_x += m_TextMetric.tmHeight * 4;
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
		// �X�y�[�X�Ȃ�`�悵�Ȃ�
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			pos_x += m_TextMetric.tmHeight / 2;
			continue;
		}
		//----------------------------------------------------------------
		// �X�y�[�X�Ȃ�`�悵�Ȃ�
		//----------------------------------------------------------------
		if ( Code == L'�@' )
		{
			pos_x += m_TextMetric.tmHeight;
			continue;
		}
		//----------------------------------------------------------------
		// �`�悷��
		//----------------------------------------------------------------
		else
		{
			pos_x += Abc.abcB + Abc.abcC;
		}
	}

	return pos_x;
}


