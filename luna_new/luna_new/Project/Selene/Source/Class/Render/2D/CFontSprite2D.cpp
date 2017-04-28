

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
	Log_PrintTable( 0xFF0000, 0x000000, L"解放", L"フォントスプライト", m_Name );
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
	フォントスプライトの生成を行います

	@param pBuffer		[in] 文字バッファ
	@param IsAlpha		[in] アルファチャンネル有無
	@param Num			[in] 最大スプライト頂点数
	@param lFont		[in] フォントハンドル
	@param IsSortZ		[in] スプライトにＺソートを使うか否か
	@param IsAntialias	[in] アンチエイリアスフォントを使うか否か

	@return			フォントスプライトハンドル
*/
//-----------------------------------------------------------------------------------
Bool CFontSprite2D::Create( const wchar_t *pBuffer, Uint32 Num, CFont *pFont, Bool IsAntialias )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"フォントスプライト" );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// シート生成
	//--------------------------------------------------------------
	if ( !CreateSheetTable( pBuffer, pFont, IsAntialias ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// スプライト生成
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pSprites[i] = (CSprite2D*)GetRenderPointer()->CreateSprite2D( Num * 2, m_pTextures[i] );
	}

	Log_PrintLine( 0x000000, L"フォント展開用テクスチャ数 %u", m_SheetCount );
	SetName( L"Create" );
	Log_PrintStrongLine( 0x008000, L"完了" );
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return true;
}


//-----------------------------------------------------------------------------------
/**
	フォントスプライトの生成を行います

	@param pBuffer		[in] 文字バッファ
	@param IsAlpha		[in] アルファチャンネル有無
	@param Num			[in] 最大スプライト頂点数
	@param lFont		[in] フォントハンドル
	@param IsSortZ		[in] スプライトにＺソートを使うか否か
	@param IsAntialias	[in] アンチエイリアスフォントを使うか否か

	@return			フォントスプライトハンドル
*/
//-----------------------------------------------------------------------------------
Bool CFontSprite2D::CreateFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 Num )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"フォントスプライト" );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// シート生成
	//--------------------------------------------------------------
	if ( !CreateSheetTableFromFile( pFileName, pExt ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// スプライト生成
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pSprites[i] = (CSprite2D*)GetRenderPointer()->CreateSprite2D( Num * 2, m_pTextures[i] );
	}

	Log_PrintLine( 0x000000, L"フォント展開用テクスチャ数 %u", m_SheetCount );
	SetName( pFileName );
	Log_PrintStrongLine( 0x008000, L"完了" );
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return true;
}


//-----------------------------------------------------------------------------------
/**
	描画用スプライトバッファの初期化をします

	@param lFontSpr		[in] フォントスプライトハンドル

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
	描画用スプライトバッファの更新をします

	@param lFontSpr		[in] フォントスプライトハンドル

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
	文字のレンダリング処理をします

	@param lFontSpr		[in] フォントスプライトハンドル

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
		// 文字コード
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// 改行
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.y;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// バックスペース
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}

		//-------------------------------------------------------
		// 文字データがある場合
		//-------------------------------------------------------
		Uint16 Index = m_IndexTbl[Code];
		if ( Index != 0xFFFF )
		{
			SFontSheetData Sheet = m_pSheetTbl[Index];
			if ( Sheet.SheetNo != -1 )
			{
				// 転送先
				Sint32 w = Sheet.x2 - Sheet.x1;
				Sint32 h = Sheet.y2 - Sheet.y1;
				Sint32 x = toI(PosX) + Sheet.abcA;
				CRect2D<Sint32> Dst( x, PosY, w, h );
				CRect2D<Sint32> Src( Sheet.x1, Sheet.y1, w, h );

				// 描画
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
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += m_FontSize;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
	プロポーショナルフォントの文字列の描画要求をします

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pStr			[in] 文字列の格納されたバッファ
	@param Px			[in] 描画開始X座標
	@param Py			[in] 描画開始Y座標
	@param Pz			[in] 描画Z値
	@param Color		[in] 描画色

*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// 文字コード
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// 改行
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.x;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// バックスペース
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}
		else
		{
			//-------------------------------------------------------
			// 文字データがある場合
			//-------------------------------------------------------
			Uint16 Index = m_IndexTbl[Code];
			if ( Index != 0xFFFF )
			{
				SFontSheetData Sheet = m_pSheetTbl[Index];
				if ( Sheet.SheetNo != -1 )
				{
					// 転送先
					Sint32 w = Sheet.x2 - Sheet.x1;
					Sint32 h = Sheet.y2 - Sheet.y1;
					Sint32 x = toI(PosX) + 1;
					CRect2D<Sint32> Dst( x, PosY, w, h );
					CRect2D<Sint32> Src( Sheet.x1, Sheet.y1, w, h );

					// 描画
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
			// 文字データが無い場合
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
	通常の文字の描画要求をします

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pStr			[in] 文字列の格納されたバッファ
	@param Dst			[in] 文字描画先矩形
	@param Pz			[in] 描画Z値
	@param Color		[in] 描画色

	@retval 0	描画されていない
	@retval 1	描画したのは半角文字
	@retval 2	描画したのは全角文字
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
	通常の文字の回転ありの描画要求をします

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pStr			[in] 文字列の格納されたバッファ
	@param Dst			[in] 文字描画先矩形
	@param Pz			[in] 描画Z値
	@param Color		[in] 描画色
	@param Angle		[in] 回転角度（1周65536度

	@retval 0	描画されていない
	@retval 1	描画したのは半角文字
	@retval 2	描画したのは全角文字
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
	文字列の幅を取得します

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pStr			[in] 文字列の格納されたバッファ
	@param Px			[in] 描画開始想定位置
	@param Py			[in] 描画開始想定位置

	@return 描画後の位置
*/
//-----------------------------------------------------------------------------------
CPoint2D<Sint32> CFontSprite2D::GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// 文字コード
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// 改行
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.x;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// バックスペース
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}
		else
		{
			//-------------------------------------------------------
			// 文字データがある場合
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
			// 文字データが無い場合
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
	文字列の幅を取得します

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pStr			[in] 文字列の格納されたバッファ
	@param Px			[in] 描画開始想定位置
	@param Py			[in] 描画開始想定位置

	@return 描画後の位置
*/
//-----------------------------------------------------------------------------------
CPoint2D<Sint32> CFontSprite2D::GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos )
{
	Sint32 PosX = Pos.x;
	Sint32 PosY = Pos.y;
	while ( *pStr != L'\0' )
	{
		//----------------------------------------------------------------
		// 文字コード
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// 改行
		//----------------------------------------------------------------
		if ( (Code == L'\n') || (Code == L'\r') )
		{
			PosX = Pos.x;
			PosY += m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == L'\t' )
		{
			PosX += m_FontSize * 4;
			continue;
		}
		//----------------------------------------------------------------
		// バックスペース
		//----------------------------------------------------------------
		if ( Code == L'\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == L' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}
		else
		{
			//-------------------------------------------------------
			// 文字データがある場合
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
			// 文字データが無い場合
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

