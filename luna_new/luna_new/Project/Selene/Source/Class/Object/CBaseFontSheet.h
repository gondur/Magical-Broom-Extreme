

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
		@brief �L�����R�[�h�ő吔
	*/
	static const Uint32 CHARA_CODE_MAX	= 65536;

	/**
		@brief �����p�V�[�g��
	*/
	static const Uint32 SHEET_MAX		= 32;

	/**
		@brief �t�H���g�V�[�g�f�[�^

		�t�H���g�V�[�g�̊e�t�H���g�̃f�[�^���i�[����\���̂ł�
	*/
	struct SFontSheetData
	{
		Uint8 SheetNo;		///< �V�[�g�ԍ�
		Uint8 abcA;			///< ABC��
		Uint8 abcB;			///< ABC��
		Uint8 abcC;			///< ABC��
		Uint16 x1;			///< UV�f�[�^
		Uint16 y1;			///< UV�f�[�^
		Uint16 x2;			///< UV�f�[�^
		Uint16 y2;			///< UV�f�[�^
	};

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
	class CBaseFontSheet : public CRenderObject
	{
	protected:
		CFont *m_pFont;
		SFontSheetData *m_pSheetTbl;					///< �t�H���g�V�[�g�f�[�^�|�C���^
		CTexture *m_pTextures[SHEET_MAX];				///< �e�N�X�`���n���h��
		Uint16 m_IndexTbl[CHARA_CODE_MAX];				///< �C���f�b�N�X�e�[�u��

		Uint32 m_SheetWidth;							///< �V�[�g����
		Uint32 m_SheetHeight;							///< �V�[�g�c��
		Uint32 m_SheetCount;							///< �V�[�g��
		Uint32 m_FontSize;								///< �t�H���g�T�C�Y
		Uint32 m_FontMax;								///< �t�H���g��

		Bool m_IsAlpha;									///< ���`�����l�����g�����ۂ�
		Bool m_IsAntialias;								///< �A���`�G�C���A�X���g�����ۂ�

	protected:
		CBaseFontSheet( CRender *pRender, CBaseMgr *pMgr );
		virtual ~CBaseFontSheet();

	public:
		virtual Bool CreateSheetTable( const wchar_t *pBuffer, CFont *pFont, Bool IsAntialias );					///< �t�H���g�I�u�W�F�N�g����
		virtual Bool CreateSheetTableFromFile( const wchar_t *pFileName, const wchar_t *pExt );						///< �t�H���g�I�u�W�F�N�g��LFD���琶��
		virtual Bool CreateSheetTableFromMemory( void *pData, const wchar_t *pExt );								///< �t�H���g�I�u�W�F�N�g��LFD���琶��

		virtual Bool GetWidth( const wchar_t Chara, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );
		virtual void GetHeight( Sint32 *pHeight );
	};
}

#endif // ___SELENE__BASEFONTSPRITE___

