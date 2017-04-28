

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
//		フォント展開
//
//==========================================================================
void DrawFont( HWND hWnd, CSurface *pDst, FONTDATA *pFont, char *pStr )
{
	GLYPHMETRICS GlyphMetric[2];

	// 文字コード
	unsigned short Code = GetCharCode( (unsigned char*)pStr );

	// デバイスコンテキスト取得
	pFont->hDC = ::GetDC( hWnd );

	// フォントオブジェクト生成
	CreateFontObject( hWnd, pFont );

	// 文字幅
	GetCharABCWidths( pFont->hDC, Code, Code, &pFont->abc );

	// 文字データ取得
	char *pBuffer = NULL;
	long DataSize = GetFontBuffer( Code, GlyphMetric, &pBuffer, pFont->hDC, pFont );
	if ( pBuffer == NULL ) { ::MessageBox( hWnd, "ERROR Failed GetFontBuffer", "Error", MB_ICONERROR ); return; }

	pFont->abc.abcA = (long)((float)pFont->abc.abcA / pFont->fAspectX);
	pFont->abc.abcB = (long)((float)pFont->abc.abcB * pFont->fAspectX);
	pFont->abc.abcC = (long)((float)pFont->abc.abcC / pFont->fAspectX);

	long pitch = (DataSize / GlyphMetric[0].gmBlackBoxY) & ~0x03;
	long w = GlyphMetric[0].gmBlackBoxX;
	long h = GlyphMetric[0].gmBlackBoxY;

	// サーフェイスに文字バッファ展開
	DrawFontBuffer( pDst, pBuffer, w, h, pitch, pFont );

	// 文字バッファ解放
	SAFE_FREE( pBuffer );

	// 文字描画開始Ｙ座標
	pFont->PosY = pFont->TextMetric.tmAscent - GlyphMetric[1].gmptGlyphOrigin.y;

	// デバイスコンテキスト解放
	::SelectObject( pFont->hDC, pFont->hFontOld );
	::DeleteObject( pFont->hFont );
	::ReleaseDC( hWnd, pFont->hDC );

	// エッジ処理
	FilterEdge( pDst, pFont );
	// 影処理
	FilterBevel( pDst, pFont );
	// アンチエイリアス処理
//	FilterAntialias( pDst, pFont );
}

//==========================================================================
//
//		縁
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
//		影
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
//		アンチエイリアス
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
//		フォントデータ取得
//
//==========================================================================
long GetFontBuffer( long Code, GLYPHMETRICS GryphMetrics[], char **ppData, HDC hdc, FONTDATA *pFont )
{
	float fSize, fSizeX, fSizeY;
	long Size = 0;

	//======================================================================
	// 最終的なサイズの矩形
	//======================================================================
	{
		fSizeX = pFont->fAspectX;
		fSizeY = pFont->fAspectY;

		//=============================================================
		// 回転などを行列で与える
		//=============================================================
		long m11 = (long)(fSizeX * 65536.0f), m12 = (long)(  0.0f * 65536.0f);
		long m21 = (long)(  0.0f * 65536.0f), m22 = (long)(fSizeY * 65536.0f);

		MAT2 Matrix;
		Matrix.eM11 = *((FIXED*)&m11);	Matrix.eM12 = *((FIXED*)&m12);
		Matrix.eM21 = *((FIXED*)&m21);	Matrix.eM22 = *((FIXED*)&m22);

		//=============================================================
		// フォントデータ取得
		//=============================================================
		// バッファサイズ受信
		GetGlyphOutline( hdc, Code, GGO_BITMAP, &GryphMetrics[1], 0, NULL, &Matrix );
	}

	//======================================================================
	// 実データ
	//======================================================================
	{
		//=============================================================
		// フォントサイズ算出
		//=============================================================
		long SpaceSize = 0;

		if ( pFont->IsEdge  ) SpaceSize += pFont->EdgeSize * 2;		// 縁
		if ( pFont->IsBevel ) SpaceSize += pFont->BevelSize;		// 影

		fSize = (float)(pFont->FontSize - SpaceSize) / (float)pFont->FontSize;

		fSizeX = fSize * pFont->fAspectX;
		fSizeY = fSize * pFont->fAspectY;

		//=============================================================
		// 回転などを行列で与える
		//=============================================================
		long m11 = (long)(fSizeX * 65536.0f), m12 = (long)(  0.0f * 65536.0f);
		long m21 = (long)(  0.0f * 65536.0f), m22 = (long)(fSizeY * 65536.0f);

		MAT2 Matrix;
		Matrix.eM11 = *((FIXED*)&m11);	Matrix.eM12 = *((FIXED*)&m12);
		Matrix.eM21 = *((FIXED*)&m21);	Matrix.eM22 = *((FIXED*)&m22);

		//=============================================================
		// フォントデータ取得
		//=============================================================
		// バッファサイズ受信
		Size = GetGlyphOutline( hdc, Code, GGO_BITMAP, &GryphMetrics[0], 0, NULL, &Matrix );

		*ppData = (char*)SAFE_ALLOC( Size );

		// バッファにフォント受信
		GetGlyphOutline( hdc, Code, GGO_BITMAP, &GryphMetrics[0], Size, *ppData, &Matrix );
	}

	return Size;
}


//==========================================================================
//
//		フォントオブジェクト生成
//
//==========================================================================
void CreateFontObject( HWND hWnd, FONTDATA *pFont )
{
	long SizeY = pFont->FontSize * pFont->SamplingCount;

	//--------------------------------------------------------------
	//		フォント生成
	//--------------------------------------------------------------
	pFont->hFont = ::CreateFont(
						SizeY,										// フォント高さ
						0,											// 文字幅
						0,											// テキストの角度
						0,											// ベースラインとｘ軸との角度
						pFont->IsBold ? FW_BLACK : FW_DONTCARE,		// フォントの重さ（太さ）
						pFont->IsItalic,							// イタリック体
						FALSE,										// アンダーライン
						FALSE,										// 打ち消し線
						SHIFTJIS_CHARSET,							// 文字セット
						OUT_TT_PRECIS,								// 出力精度
						CLIP_DEFAULT_PRECIS,						// クリッピング精度
						PROOF_QUALITY,								// 出力品質
						FIXED_PITCH | FF_MODERN,					// ピッチとファミリー
						pFont->Face );								// 書体名

	pFont->hDC = ::GetDC( hWnd );

	pFont->hFontOld = (HFONT)SelectObject( pFont->hDC, pFont->hFont );
	GetTextMetrics( pFont->hDC, &pFont->TextMetric );
}

//==========================================================================
//
//		フォント展開
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
	// サーフェイス生成
	//------------------------------------------------
	pDstBuff->Create( Width, Height );

	//------------------------------------------------
	// サーフェイスへのポインタ
	//------------------------------------------------
	unsigned long *pDst;
	long DstPitch;

	unsigned char *pSrc = (unsigned char *)pBuffer;
	long SrcPitch = Pitch;

	//------------------------------------------------
	// 転送
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

