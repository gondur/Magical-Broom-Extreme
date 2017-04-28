

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
		@brief �t�H���g�`���`
		@author �t���`

		�t�H���g�`��p�̃N���b�s���O���`��p��`�f�[�^
	*/
	struct FontDrawRect
	{
		Sint32 x1;					///< �w�n�_���W
		Sint32 y1;					///< �x�n�_���W
		Sint32 x2;					///< �w�I�_���W
		Sint32 y2;					///< �x�I�_���W
		Sint32 Pitch;				///< �t�H���g�摜�̃s�b�`
		void *pBits;				///< �t�H���g�̃s�N�Z���f�[�^�̐擪�|�C���^
	};

	/**
		@brief �t�H���g�֘A�N���X
		@author �t���`

		�P���ȃt�H���g�`����T�|�[�g����N���X�ł��B<BR>
		�o�b�N�o�b�t�@�A�e�N�X�`���A�I�t�X�N���[��<BR>
		�T�[�t�F�C�X�ւ̃t�H���g�`�揈�����T�|�[�g���܂��B
	*/
	class CFont : public CDeviceObject
	{
	protected:
		HDC m_hDC;									///< �f�o�C�X�R���e�L�X�g�n���h��
		HFONT m_hFont;								///< �t�H���g�n���h��
		HFONT m_hFontOld;							///< �O�̃t�H���g�n���h��
		TEXTMETRIC m_TextMetric;					///< �t�H���g���g���b�N
		Uint32 m_FontSize;							///< �t�H���g�T�C�Y
		CTexture *m_pTarget;						///< �^�[�Q�b�g�n���h��
		char *m_pBuffer;							///< �o�b�t�@�|�C���^
		Bool m_IsBegin;								///< �t�H���g�`��\��Ԃ��ǂ���
		Bool m_IsAlpha;								///< �A���t�@�`�����l���L�����ǂ���
		Bool m_IsUpdate;							///< �`���Ƀe�N�X�`�����X�V���邩�ǂ���

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

