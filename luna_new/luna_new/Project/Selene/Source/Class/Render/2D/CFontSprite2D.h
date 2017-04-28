

#ifndef ___SELENE__CFONTSPRITE2D___
#define ___SELENE__CFONTSPRITE2D___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Object/CBaseFontSheet.h"
#include "Interface/Render/2D/IFontSprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CSprite2D;

	/**
		@brief �t�H���g�X�v���C�g�Ǘ��N���X

		�X�v���C�g�`���̃t�H���g�`��N���X�ł��B
		���O�Ƀe�N�X�`���Ƀt�H���g��~���l�߁A
		UV�e�[�u�����쐬���Ă����A�e�[�u���A�N�Z�X����A
		�C�ӂ̕������e�N�X�`������؂�o���ĕ`��
		����悤�ȍ\���ɂȂ��Ă��܂��B
		������A�P���ȕ����`����������ɏ����ł��A
		�G�t�F�N�g�Ȃǂ��e�Ղɂ����܂����A
		�S�Ă̕������e�N�X�`���ɓW�J���Ă������߁A
		�g�p�������͑����Ă��܂��܂��B
	*/
	class CFontSprite2D : public CBaseFontSheet, public IFontSprite2D
	{
	protected:
		CSprite2D *m_pSprites[SHEET_MAX];

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CFontSprite2D( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CFontSprite2D();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Bool Create( const wchar_t *pBuffer, Uint32 Num, CFont *pFont , Bool IsAntialias );
		virtual Bool CreateFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 Num );

		virtual void Begin( void );
		virtual void End( void );
		virtual void Rendering( void );

		virtual void DrawString( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color );
		virtual void DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color );
		virtual Sint32 DrawChara( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color );
		virtual Sint32 DrawCharaRotate( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color, Sint32 Angle );

		virtual CPoint2D<Sint32> GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos );
		virtual CPoint2D<Sint32> GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos );
	};
}

#endif // ___SELENE__CFONTSPRITE2D___

