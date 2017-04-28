

#ifndef ___SELENE__FONT___
#define ___SELENE__FONT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CTexture;

	/**
		@brief フォント描画矩形
		@author 葉迩倭

		フォント描画用のクリッピング＆描画用矩形データ
	*/
	struct FontDrawRect
	{
		Sint32 x1;					///< Ｘ始点座標
		Sint32 y1;					///< Ｙ始点座標
		Sint32 x2;					///< Ｘ終点座標
		Sint32 y2;					///< Ｙ終点座標
		Sint32 Pitch;				///< フォント画像のピッチ
		void *pBits;				///< フォントのピクセルデータの先頭ポインタ
	};

	/**
		@brief フォント関連クラス
		@author 葉迩倭

		単純なフォント描画をサポートするクラスです。<BR>
		バックバッファ、テクスチャ、オフスクリーン<BR>
		サーフェイスへのフォント描画処理をサポートします。
	*/
	class CFont : public CDeviceObject
	{
	protected:
		HDC m_hDC;									///< デバイスコンテキストハンドル
		HFONT m_hFont;								///< フォントハンドル
		HFONT m_hFontOld;							///< 前のフォントハンドル
		TEXTMETRIC m_TextMetric;					///< フォントメトリック
		Uint32 m_FontSize;							///< フォントサイズ
		CTexture *m_pTarget;						///< ターゲットハンドル
		char *m_pBuffer;							///< バッファポインタ
		Bool m_IsBegin;								///< フォント描画可能状態かどうか
		Bool m_IsAlpha;								///< アルファチャンネル有無かどうか
		Bool m_IsUpdate;							///< 描画後にテクスチャを更新するかどうか

	protected:
		virtual Sint32 GetFontBuffer( HDC hDC, Uint16 Code, GLYPHMETRICS *pGM, char **ppData, Bool Alpha );
		virtual Bool LockTarget( void **ppBits, Sint32 *pPitch, D3DFORMAT *pFormat, Sint32 *pWidth, Sint32 *pHeight );
		virtual void UnlockTarget( void );
		virtual void DrawPixel1555( Sint32 Char, FontDrawRect *pDst, FontDrawRect *pSrc );
		virtual void DrawPixel565( Sint32 Char, FontDrawRect *pDst, FontDrawRect *pSrc );
		virtual void DrawPixel4444( Sint32 Char, FontDrawRect *pDst, FontDrawRect *pSrc );
		virtual void DrawPixel8888( Sint32 Char, FontDrawRect *pDst, FontDrawRect *pSrc );
		virtual void DrawPixel4444AA( Sint32 Char, FontDrawRect *pDst, FontDrawRect *pSrc );
		virtual void DrawPixel8888AA( Sint32 Char, FontDrawRect *pDst, FontDrawRect *pSrc );
		virtual Bool Clip( FontDrawRect *pDst, FontDrawRect *pSrc, Sint32 Width, Sint32 Height );

	public:
		CFont( CBaseMgr *pMgr );
		virtual ~CFont();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Bool Create( const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic = false, Bool IsBold = false );

		virtual void SetDestination( CTexture *pTarget );
		virtual void DrawChar( Sint32 Px, Sint32 Py, CColor Color, Uint16 Code );
		virtual void DrawCharAA( Sint32 Px, Sint32 Py, CColor Color, Uint16 Code );
		virtual Sint32 DrawText( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr );
		virtual Sint32 DrawTextAA( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr );
		virtual Sint32 DrawPText( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr );
		virtual Sint32 DrawPTextAA( Sint32 Px, Sint32 Py, CColor Color, const wchar_t *pStr );
		virtual void GetFontData( Uint16 Code, ABC *pABC );

		virtual void Begin( Bool IsUpdate = true );
		virtual void End( void );

		virtual Sint32 GetTextWidth( const wchar_t *pStr );
		virtual Sint32 GetFontSize( void );
	};
}

#endif // ___SELENE__FONT___

