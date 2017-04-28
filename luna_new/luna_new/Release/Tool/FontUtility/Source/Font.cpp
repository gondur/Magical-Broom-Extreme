

//==========================================================================
// INCLUDE
//==========================================================================
#include "Font.h"


//==========================================================================
// PROTOTYPE
//==========================================================================
static long GetFontBuffer( long Code, GLYPHMETRICS GryphMetrics[], char **ppData, HDC hdc, FONTDATA *pFont );
static void CreateFontObject( HWND hWnd, FONTDATA *pFont );
static void DrawFontBuffer( CSurface *pDst, char *pBuffer, long w, long h, long pitch, FONTDATA *pFont );

static void FilterEdge( CSurface *pDst, FONTDATA *pFont );
static void FilterBevel( CSurface *pDst, FONTDATA *pFont );


//==========================================================================
//
//		�t�H���g�W�J
//
//==========================================================================
void DrawFont( HWND hWnd, CSurface *pDst, FONTDATA *pFont, char *pStr )
{
	GLYPHMETRICS GlyphMetric[2];

	// �����R�[�h
	unsigned short Code = GetCharCode( (unsigned char*)pStr );

	// �f�o�C�X�R���e�L�X�g�擾
	pFont->hDC = ::GetDC( hWnd );

	// �t�H���g�I�u�W�F�N�g����
	CreateFontObject( hWnd, pFont );

	// ������
	GetCharABCWidths( pFont->hDC, Code, Code, &pFont->abc );

	// �����f�[�^�擾
	char *pBuffer = NULL;
	long DataSize = GetFontBuffer( Code, GlyphMetric, &pBuffer, pFont->hDC, pFont );
	if ( pBuffer == NULL ) { ::MessageBox( hWnd, "ERROR Failed GetFontBuffer", "Error", MB_ICONERROR ); return; }

	pFont->abc.abcA = (long)((float)pFont->abc.abcA / pFont->fAspectX);
	pFont->abc.abcB = (long)((float)pFont->abc.abcB * pFont->fAspectX);
	pFont->abc.abcC = (long)((float)pFont->abc.abcC / pFont->fAspectX);

	long pitch = (DataSize / GlyphMetric[0].gmBlackBoxY) & ~0x03;
	long w = GlyphMetric[0].gmBlackBoxX;
	long h = GlyphMetric[0].gmBlackBoxY;

	// �T�[�t�F�C�X�ɕ����o�b�t�@�W�J
	DrawFontBuffer( pDst, pBuffer, w, h, pitch, pFont );

	// �����o�b�t�@���
	SAFE_FREE( pBuffer );

	// �����`��J�n�x���W
	pFont->PosY = pFont->TextMetric.tmAscent - GlyphMetric[1].gmptGlyphOrigin.y;

	// �f�o�C�X�R���e�L�X�g���
	::SelectObject( pFont->hDC, pFont->hFontOld );
	::DeleteObject( pFont->hFont );
	::ReleaseDC( hWnd, pFont->hDC );

	// �G�b�W����
	FilterEdge( pDst, pFont );
	// �e����
	FilterBevel( pDst, pFont );
	// �A���`�G�C���A�X����
//	FilterAntialias( pDst, pFont );
}

//==========================================================================
//
//		��
//
//==========================================================================
void FilterEdge( CSurface *pDst, FONTDATA *pFont )
{
	if ( pFont->IsEdge )
	{
		PIXELDATA32 Color;
		Color.a = 0;
		Color.b = (unsigned char)((pFont->EdgeColor >> 16) & 0xFF);
		Color.g = (unsigned char)((pFont->EdgeColor >>  8) & 0xFF);
		Color.r = (unsigned char)((pFont->EdgeColor >>  0) & 0xFF);

		CSurface org_surf;
		org_surf.Create( pDst );

		long size = pFont->EdgeSize * pFont->SamplingCount;
		for ( long i = 0; i < size; i++ )
		{
			if ( (size >= 2) && (i == (size - 1)) )
			{
				CSurface temp_surf;
				temp_surf.Create( pDst );
				pDst->Release();
				pDst->Create( temp_surf.GetWidth()+2, temp_surf.GetHeight()+2 );
				long w = temp_surf.GetWidth();
				long h = temp_surf.GetHeight();
				for ( long j = 0; j < 4; j++ )
				{
					const long x_tbl[] = { 0, 1, 1, 2 };
					const long y_tbl[] = { 1, 0, 2, 1 };
					pDst->ColorDrawNoAlpha( x_tbl[j], y_tbl[j], &temp_surf, 0, 0, w, h, Color );
				}
				temp_surf.Release();
			}
			else
			{
				CSurface temp_surf;
				temp_surf.Create( pDst );
				pDst->Release();
				pDst->Create( temp_surf.GetWidth()+2, temp_surf.GetHeight()+2 );
				long w = temp_surf.GetWidth();
				long h = temp_surf.GetHeight();
				for ( long j = 0; j < 9; j++ )
				{
					const long x_tbl[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };
					const long y_tbl[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };
					pDst->ColorDrawNoAlpha( x_tbl[j], y_tbl[j], &temp_surf, 0, 0, w, h, Color );
				}
				temp_surf.Release();
			}
		}

		pDst->Draw( size, size, &org_surf, 0, 0, org_surf.GetWidth(), org_surf.GetHeight() );

		org_surf.Release();
	}
}

//==========================================================================
//
//		�e
//
//==========================================================================
void FilterBevel( CSurface *pDst, FONTDATA *pFont )
{
	if ( pFont->IsBevel )
	{
		PIXELDATA32 Color;
		Color.a = 0;
		Color.b = (unsigned char)((pFont->BevelColor >> 16) & 0xFF);
		Color.g = (unsigned char)((pFont->BevelColor >>  8) & 0xFF);
		Color.r = (unsigned char)((pFont->BevelColor >>  0) & 0xFF);

		long size = pFont->BevelSize * pFont->SamplingCount;

		//                         0,      1,      2,       3,     4, 5,      6,     7,     8,      9
		const long sx_tbl[]    = { 0,      0,      0,  size-1,     0, 0, size-1,     0,     0, size-1 };
		const long sy_tbl[]    = { 0, size-1, size-1,  size-1,     0, 0,      0,     0,     0,      0 };
		const long w_tbl[]     = { 0,   size,      0,    size,  size, 0,   size,  size,     0,   size };
		const long h_tbl[]     = { 0,   size,   size,    size,     0, 0,      0,  size,  size,   size };
		const long add_x_tbl[] = { 0,     +1,      0,      -1,    +1, 0,     -1,    +1,     0,     -1 };
		const long add_y_tbl[] = { 0,     -1,     -1,      -1,     0, 0,      0,    +1,    +1,     +1 };

		CSurface temp_surf;
		temp_surf.Create( pDst );

		long w = temp_surf.GetWidth()  + w_tbl[pFont->BevelDir];
		long h = temp_surf.GetHeight() + h_tbl[pFont->BevelDir];

		pDst->Release();
		pDst->Create( w, h );

		w = temp_surf.GetWidth();
		h = temp_surf.GetHeight();

		long sx		= sx_tbl[pFont->BevelDir];
		long sy		= sy_tbl[pFont->BevelDir];
		long x		= sx;
		long y		= sy;
		long add_x	= add_x_tbl[pFont->BevelDir];
		long add_y	= add_y_tbl[pFont->BevelDir];

		for ( long i = 0; i <= size; i++ )
		{
			pDst->ColorDrawNoAlpha( x, y, &temp_surf, 0, 0, w, h, Color );
			x += add_x;
			y += add_y;
		}
		pDst->Draw( sx, sy, &temp_surf, 0, 0, w, h );

		temp_surf.Release();
	}
}

//==========================================================================
//
//		�A���`�G�C���A�X
//
//==========================================================================
void FilterAntialias( CSurface *pDst, FONTDATA *pFont )
{
	if ( pFont->SamplingCount == 1 ) return;

	CSurface temp_surf;
	temp_surf.Create( pDst );

	long src_w = (temp_surf.GetWidth() +(pFont->SamplingCount-1)) / pFont->SamplingCount;
	long src_h = (temp_surf.GetHeight()+(pFont->SamplingCount-1)) / pFont->SamplingCount;

	pDst->Release();
	pDst->Create( src_w, src_h );

	long w = pDst->GetWidth();
	long h = pDst->GetHeight();

	for ( long y = 0; y < h; y++ )
	{
		for ( long x = 0; x < w; x++ )
		{
			long count[2] = { 0, 0 };
			long a = 0, r = 0, g = 0, b = 0;
			for ( long dy = 0; dy < pFont->SamplingCount; dy++ )
			{
				for ( long dx = 0; dx < pFont->SamplingCount; dx++ )
				{
					PIXELDATA32 pixel;
					temp_surf.GetColor( x * pFont->SamplingCount + dx, y * pFont->SamplingCount + dy, &pixel );
					if ( pixel.a == 0 )
					{
						count[1]++;
					}
					else
					{
						a += pixel.a;
						r += pixel.r;
						g += pixel.g;
						b += pixel.b;
						count[0]++;
						count[1]++;
					}
				}
			}

			if ( count[0] == 0 )
			{
				PIXELDATA32 pixel = { 0, 0, 0, 0 };
				pDst->SetColor( x, y, &pixel );
			}
			else
			{
				PIXELDATA32 pixel = {
					(unsigned char)(b/count[0]),
					(unsigned char)(g/count[0]),
					(unsigned char)(r/count[0]),
					(unsigned char)(a/count[1]),
				};
				pDst->SetColor( x, y, &pixel );
			}
		}
	}
}

//==========================================================================
//
//		�t�H���g�f�[�^�擾
//
//==========================================================================
long GetFontBuffer( long Code, GLYPHMETRICS GryphMetrics[], char **ppData, HDC hdc, FONTDATA *pFont )
{
	float fSize, fSizeX, fSizeY;
	long Size = 0;

	//======================================================================
	// �ŏI�I�ȃT�C�Y�̋�`
	//======================================================================
	{
		fSizeX = pFont->fAspectX;
		fSizeY = pFont->fAspectY;

		//=============================================================
		// ��]�Ȃǂ��s��ŗ^����
		//=============================================================
		long m11 = (long)(fSizeX * 65536.0f), m12 = (long)(  0.0f * 65536.0f);
		long m21 = (long)(  0.0f * 65536.0f), m22 = (long)(fSizeY * 65536.0f);

		MAT2 Matrix;
		Matrix.eM11 = *((FIXED*)&m11);	Matrix.eM12 = *((FIXED*)&m12);
		Matrix.eM21 = *((FIXED*)&m21);	Matrix.eM22 = *((FIXED*)&m22);

		//=============================================================
		// �t�H���g�f�[�^�擾
		//=============================================================
		// �o�b�t�@�T�C�Y��M
		GetGlyphOutline( hdc, Code, GGO_BITMAP, &GryphMetrics[1], 0, NULL, &Matrix );
	}

	//======================================================================
	// ���f�[�^
	//======================================================================
	{
		//=============================================================
		// �t�H���g�T�C�Y�Z�o
		//=============================================================
		long SpaceSize = 0;

		if ( pFont->IsEdge  ) SpaceSize += pFont->EdgeSize * 2;		// ��
		if ( pFont->IsBevel ) SpaceSize += pFont->BevelSize;		// �e

		fSize = (float)(pFont->FontSize - SpaceSize) / (float)pFont->FontSize;

		fSizeX = fSize * pFont->fAspectX;
		fSizeY = fSize * pFont->fAspectY;

		//=============================================================
		// ��]�Ȃǂ��s��ŗ^����
		//=============================================================
		long m11 = (long)(fSizeX * 65536.0f), m12 = (long)(  0.0f * 65536.0f);
		long m21 = (long)(  0.0f * 65536.0f), m22 = (long)(fSizeY * 65536.0f);

		MAT2 Matrix;
		Matrix.eM11 = *((FIXED*)&m11);	Matrix.eM12 = *((FIXED*)&m12);
		Matrix.eM21 = *((FIXED*)&m21);	Matrix.eM22 = *((FIXED*)&m22);

		//=============================================================
		// �t�H���g�f�[�^�擾
		//=============================================================
		// �o�b�t�@�T�C�Y��M
		Size = GetGlyphOutline( hdc, Code, GGO_BITMAP, &GryphMetrics[0], 0, NULL, &Matrix );

		*ppData = (char*)SAFE_ALLOC( Size );

		// �o�b�t�@�Ƀt�H���g��M
		GetGlyphOutline( hdc, Code, GGO_BITMAP, &GryphMetrics[0], Size, *ppData, &Matrix );
	}

	return Size;
}


//==========================================================================
//
//		�t�H���g�I�u�W�F�N�g����
//
//==========================================================================
void CreateFontObject( HWND hWnd, FONTDATA *pFont )
{
	long SizeY = pFont->FontSize * pFont->SamplingCount;

	//--------------------------------------------------------------
	//		�t�H���g����
	//--------------------------------------------------------------
	pFont->hFont = ::CreateFont(
						SizeY,										// �t�H���g����
						0,											// ������
						0,											// �e�L�X�g�̊p�x
						0,											// �x�[�X���C���Ƃ����Ƃ̊p�x
						pFont->IsBold ? FW_BLACK : FW_DONTCARE,		// �t�H���g�̏d���i�����j
						pFont->IsItalic,							// �C�^���b�N��
						FALSE,										// �A���_�[���C��
						FALSE,										// �ł�������
						SHIFTJIS_CHARSET,							// �����Z�b�g
						OUT_TT_PRECIS,								// �o�͐��x
						CLIP_DEFAULT_PRECIS,						// �N���b�s���O���x
						PROOF_QUALITY,								// �o�͕i��
						FIXED_PITCH | FF_MODERN,					// �s�b�`�ƃt�@�~���[
						pFont->Face );								// ���̖�

	pFont->hDC = ::GetDC( hWnd );

	pFont->hFontOld = (HFONT)SelectObject( pFont->hDC, pFont->hFont );
	GetTextMetrics( pFont->hDC, &pFont->TextMetric );
}

//==========================================================================
//
//		�t�H���g�W�J
//
//==========================================================================
void DrawFontBuffer( CSurface *pDstBuff, char *pBuffer, long Width, long Height, long Pitch, FONTDATA *pFont )
{
	PIXELDATA32 Color;
	Color.a = 0xFF;
	Color.b = (unsigned char)((pFont->FontColor >> 16) & 0xFF);
	Color.g = (unsigned char)((pFont->FontColor >>  8) & 0xFF);
	Color.r = (unsigned char)((pFont->FontColor >>  0) & 0xFF);

	//------------------------------------------------
	// �T�[�t�F�C�X����
	//------------------------------------------------
	pDstBuff->Create( Width, Height );

	//------------------------------------------------
	// �T�[�t�F�C�X�ւ̃|�C���^
	//------------------------------------------------
	unsigned long *pDst;
	long DstPitch;

	unsigned char *pSrc = (unsigned char *)pBuffer;
	long SrcPitch = Pitch;

	//------------------------------------------------
	// �]��
	//------------------------------------------------
	if ( pDstBuff->GetData( (PIXELDATA32**)&pDst, &DstPitch ) )
	{
		for ( long y = 0; y < Height; y++ )
		{
			long xx = 0;
			for ( long x = 0; x < Width; x++ )
			{
				long shift = 7 - (x & 7);
				long no = x >> 3;
				pDst[xx] = (((pSrc[no] >> shift) & 0x01) ? *((unsigned long*)&Color) : 0x00000000);
				xx++;
			}
			pDst += DstPitch;
			pSrc += SrcPitch;
		}
	}
}

