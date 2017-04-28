

#ifndef ___SELENE__BASEFONTSPRITE___
#define ___SELENE__BASEFONTSPRITE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CRenderObject.h"
#include "Object/CBaseMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CFont;
	class CTexture;

	/**
		@brief キャラコード最大数
	*/
	static const Uint32 CHARA_CODE_MAX	= 65536;

	/**
		@brief 文字用シート数
	*/
	static const Uint32 SHEET_MAX		= 32;

	/**
		@brief フォントシートデータ

		フォントシートの各フォントのデータを格納する構造体です
	*/
	struct SFontSheetData
	{
		Uint8 SheetNo;		///< シート番号
		Uint8 abcA;			///< ABC幅
		Uint8 abcB;			///< ABC幅
		Uint8 abcC;			///< ABC幅
		Uint16 x1;			///< UVデータ
		Uint16 y1;			///< UVデータ
		Uint16 x2;			///< UVデータ
		Uint16 y2;			///< UVデータ
	};

	/**
		@brief フォントスプライト管理クラス

		スプライト形式のフォント描画クラスです。
		事前にテクスチャにフォントを敷き詰め、
		UVテーブルを作成しておき、テーブルアクセスから、
		任意の文字をテクスチャから切り出して描画
		するような構造になっています。
		性質上、単純な文字描画よりも高速に処理でき、
		エフェクトなども容易につけられますが、
		全ての文字をテクスチャに展開しておくため、
		使用メモリは増えてしまいます。
	*/
	class CBaseFontSheet : public CRenderObject
	{
	protected:
		CFont *m_pFont;
		SFontSheetData *m_pSheetTbl;					///< フォントシートデータポインタ
		CTexture *m_pTextures[SHEET_MAX];				///< テクスチャハンドル
		Uint16 m_IndexTbl[CHARA_CODE_MAX];				///< インデックステーブル

		Uint32 m_SheetWidth;							///< シート横幅
		Uint32 m_SheetHeight;							///< シート縦幅
		Uint32 m_SheetCount;							///< シート数
		Uint32 m_FontSize;								///< フォントサイズ
		Uint32 m_FontMax;								///< フォント数

		Bool m_IsAlpha;									///< αチャンネルを使うか否か
		Bool m_IsAntialias;								///< アンチエイリアスを使うか否か

	protected:
		CBaseFontSheet( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CBaseFontSheet();

	public:
		virtual Bool CreateSheetTable( const wchar_t *pBuffer, CFont *pFont, Bool IsAntialias );					///< フォントオブジェクト生成
		virtual Bool CreateSheetTableFromFile( const wchar_t *pFileName, const wchar_t *pExt );						///< フォントオブジェクトをLFDから生成
		virtual Bool CreateSheetTableFromMemory( void *pData, const wchar_t *pExt );								///< フォントオブジェクトをLFDから生成

		virtual Bool GetWidth( const wchar_t Chara, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );
		virtual void GetHeight( Sint32 *pHeight );
	};
}

#endif // ___SELENE__BASEFONTSPRITE___

