
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
	@brief LFDファイルヘッダ

	LFDファイル用のファイルヘッダ構造体。
*/
struct LFDHEADER
{
	char Guid[4];						///< ファイル識別情報（常に 'L' 'F' 'D' '\0'
	Uint8 FontSize;						///< フォントサイズ
	Uint8 SheetMax;						///< シート最大数
	Uint16 SheetWidth;					///< シート横幅
	Uint16 SheetHeight;					///< シート縦幅
	Uint16 FontMax;						///< フォント最大数
	Uint16 IndexTbl[CHARA_CODE_MAX];	///< インデックステーブル
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
	フォントスプライトの再生成を行います

	@param pBuffer		[in] 文字バッファ

	@return			成功か否か
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
	// テクスチャ設定
	//--------------------------------------------------------------
	Conf = GetRenderPointer()->GetTextureConfig();
	ConfOrg = Conf;
	Conf.SetFormat( FORMAT_TEXTURE_2D );
	Conf.SetColorKey( 0x00000000 );
	GetRenderPointer()->SetTextureConfig( Conf );

	//--------------------------------------------------------------
	// データコピー
	//--------------------------------------------------------------
	m_IsAntialias = IsAntialias;
	m_pFont = pFont;
	m_pFont->AddRef();

	//--------------------------------------------------------------
	// シート用バッファ
	//--------------------------------------------------------------
	m_pSheetTbl = (SFontSheetData*)MemGlobalAlloc( sizeof(SFontSheetData[CHARA_CODE_MAX]) );
	for ( Sint32 i = 0; i < CHARA_CODE_MAX; i++ )
	{
		m_pSheetTbl[i].SheetNo = 0xFF;
		m_IndexTbl[i] = 0xFFFF;
	}

	//--------------------------------------------------------------
	// 文字数からテクスチャサイズ算出
	//--------------------------------------------------------------
	FontSize	= m_pFont->GetFontSize();
	FontHeight	= FontSize + 2;
	Len			= wcslen( pBuffer );
	Size		= FontHeight * FontHeight * Len;

	// テクスチャサイズ算出
	TexArea = 1;
	while ( Size > (TexArea * TexArea) ) TexArea <<= 1;

	// 使用可能な最大サイズ取得
	CPoint2D<Uint32> MaxTextureSize = GetTextureMaxSize();

	// テクスチャサイズ制限
	MaxTextureSize.x = (MaxTextureSize.x > TexArea) ? (TexArea) : (MaxTextureSize.x);
	MaxTextureSize.y = (MaxTextureSize.y > TexArea) ? (TexArea) : (MaxTextureSize.y);

	m_SheetWidth	= MaxTextureSize.x;
	m_SheetHeight	= MaxTextureSize.y;
	m_FontSize		= FontSize;

	SheetLineNum	= m_SheetWidth / FontHeight;

	//--------------------------------------------------------------
	// １枚目のシートをこさえておく
	//--------------------------------------------------------------
	///Logout( "　" );
	m_pTextures[0] = (CTexture*)GetRenderPointer()->CreateTexture( m_SheetWidth, m_SheetHeight );
	m_SheetCount++;

	//--------------------------------------------------------------
	// シート作成
	//--------------------------------------------------------------
	Pos = 0;
	while ( Pos < Len )
	{
		//-----------------------------------------
		// Shift-JISコード
		//-----------------------------------------
		Code = pBuffer[Pos++];

		//-----------------------------------------
		// 挿入可能なシート場所検索
		//-----------------------------------------
		LineNum = 0;
		IsWrite = false;
		while ( !IsWrite )
		{
			// 最終シート番号
			LastSheet = m_SheetCount - 1;

			// 描画先テクスチャ設定
			m_pFont->SetDestination( m_pTextures[LastSheet] );

			// フォント描画処理開始
			m_pFont->Begin( false );

			// フォント幅
			m_pFont->GetFontData( Code, &Abc );
			FontWidth = Abc.abcB + 2;

			// 文字追記可能？
			if ( LineWidthTbl[LineNum] + FontWidth < m_SheetWidth )
			{
				// 一回書いた文字？
				if ( m_IndexTbl[Code] == 0xFFFF )
				{
					m_IndexTbl[Code] = (Uint16)m_FontMax;

					// 描画位置算出
					Px = LineWidthTbl[LineNum];
					Py = LineNum * FontHeight;

					// 描画
					if ( m_IsAntialias )
						m_pFont->DrawCharAA( Px + 1, Py + 1, CColor(255,255,255,255), Code );
					else
						m_pFont->DrawChar( Px + 1, Py + 1, CColor(255,255,255,255), Code );

					// アクセス用テーブルを作る
					m_pSheetTbl[m_FontMax].SheetNo	= (Uint8)(LastSheet);
					m_pSheetTbl[m_FontMax].abcA		= (Uint8)(Abc.abcA);
					m_pSheetTbl[m_FontMax].abcB		= (Uint8)(FontWidth);
					m_pSheetTbl[m_FontMax].abcC		= (Uint8)(Abc.abcC);
					m_pSheetTbl[m_FontMax].x1		= (Uint16)(Px);
					m_pSheetTbl[m_FontMax].y1		= (Uint16)(Py);
					m_pSheetTbl[m_FontMax].x2		= (Uint16)(Px + FontWidth);
					m_pSheetTbl[m_FontMax].y2		= (Uint16)(Py + FontHeight);
					m_FontMax++;

					// フォント描画シート位置加算
					LineWidthTbl[LineNum] += FontWidth;
				}

				// 描画しますた
				IsWrite = true;
			}
			else
			{
				// 描画できんかったので次の行に移る
				LineNum++;

				// シートがいっぱいなので次のシートを作成する
				if ( LineNum == SheetLineNum )
				{
					LineNum = 0;
					MemoryClear( LineWidthTbl, sizeof(LineWidthTbl) );

					// 新規シート作成
					///Logout( "　" );
					m_pTextures[m_SheetCount] = (CTexture*)GetRenderPointer()->CreateTexture( m_SheetWidth, m_SheetHeight );
					m_SheetCount++;
					if ( m_SheetCount == SHEET_MAX )
					{
						goto EXIT;
					}
				}
			}

			// フォント描画終了
			m_pFont->End();
		}
	}

	//--------------------------------------------------------------
	// テクスチャの更新
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pTextures[i]->UpdateTexture();
	}

	bRet = true;

EXIT:
	// テクスチャ設定戻す
	GetRenderPointer()->SetTextureConfig( ConfOrg );

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
	フォントスプライトをメモリから生成をします。

	@param pData		[in] LFDデータメモリのアドレス
	@param pExt			[in] 画像の格納されたLAGファイル名

	@return		フォントスプライトインターフェイス
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTableFromMemory( void *pData, const wchar_t *pExt )
{
	LFDHEADER *pLfdHead;

	//--------------------------------------------------------------
	// ヘッダ
	//--------------------------------------------------------------
	pLfdHead = (LFDHEADER*)pData;
	pData = ((char*)pData) + sizeof(LFDHEADER);
	if ( strcmp( pLfdHead->Guid, "LFD" ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// データ
	//--------------------------------------------------------------
	m_FontSize		= pLfdHead->FontSize;		// フォントサイズ
	m_FontMax		= pLfdHead->FontMax;		// フォント数
	m_SheetCount	= pLfdHead->SheetMax;		// シート数
	m_SheetWidth	= pLfdHead->SheetWidth;		// シート横幅
	m_SheetHeight	= pLfdHead->SheetHeight;	// シート縦幅

	//--------------------------------------------------------------
	// シート名
	//--------------------------------------------------------------
	for ( Uint32 i = 0; i < m_SheetCount; i++ )
	{
		// シート名取得
		char Name[64] = "";
		MemoryCopy( Name, pData, 32 );
		pData = ((char*)pData) + 32;

		// テクスチャ生成
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
	// インデックス
	//--------------------------------------------------------------
	MemoryCopy( m_IndexTbl, pLfdHead->IndexTbl, sizeof(Uint16) * CHARA_CODE_MAX );

	//--------------------------------------------------------------
	// データ
	//--------------------------------------------------------------
	m_pSheetTbl = (SFontSheetData*)MemGlobalAlloc( sizeof(SFontSheetData) * pLfdHead->FontMax );
	MemoryCopy( m_pSheetTbl, pData, sizeof(SFontSheetData) * pLfdHead->FontMax );
	pData = ((char*)pData) + sizeof(SFontSheetData) * pLfdHead->FontMax;

	return true;
}


//-----------------------------------------------------------------------------------
/**
	フォントスプライトをLFDファイルから生成をします。

	@param pFileName	[in] フォントデータが格納されたLFDファイル名
	@param pExt		[in] 画像の格納されたLAGファイル名
	@param IsAlpha		[in] アルファテクスチャを使うか？
	@param Num			[in] スプライト数
	@param IsSortZ		[in] スプライトにＺソートを使うか否か

	@return		フォントスプライトインターフェイス
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTableFromFile( const wchar_t *pFileName, const wchar_t *pExt )
{
	//--------------------------------------------------------------
	// ファイルから
	//--------------------------------------------------------------
	Uint32 Size;
	void *pData;

	//--------------------------------------------------------------
	// ファイル読み込み
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
		Log_PrintStrong( 0xFF0000, L"ファイルが見つかりません" );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	文字の詳細な横幅を取得します

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pStr			[in] 幅を取得したい文字
	@param pLeft		[in] 左幅を格納するための変数へのポインタ
	@param pCenter		[in] 文字幅を格納するための変数へのポインタ
	@param pRight		[in] 右幅を格納するための変数へのポインタ

	@retval true	成功
	@retval false	失敗
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
	文字の縦幅を取得します

	@param lFontSpr		[in] フォントスプライトハンドル
	@param pHeight		[in] 縦幅を格納するための変数へのポインタ
*/
//-----------------------------------------------------------------------------------
void CBaseFontSheet::GetHeight( Sint32 *pHeight )
{
	*pHeight = m_FontSize;
}
