

#ifndef ___SELENE__IPOSTEFFECT___
#define ___SELENE__IPOSTEFFECT___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �|�X�g�G�t�F�N�g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IPostEffect
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																																			= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																																			= 0;

		/**
			@brief �e�N�X�`�����g������`�����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			�P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void SingleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																	= 0;

		/**
			@brief �}���`�e�N�X�`�����g������`�����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param SrcTbl		[in] �e�N�X�`��UV��`
			@param TypeTbl		[in] �X�e�[�W���̉��Z�^�C�v
			@param pTexTbl		[in] �e�N�X�`��
			@param StageCount	[in] ���p����X�e�[�W��

			�P���ȋ�`���}���`�e�N�X�`���Ή��Ń����_�����O���܂��B<BR>
			2D�`��ɂ�����}���`�e�N�X�`���p�r�͎�Ƀ|�X�g�G�t�F�N�g�Ȃ̂�<BR>
			���̕����ɓ��������@�\�Ƃ��Ď������Ă���܂��B
		*/
		virtual void MultipleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> SrcTbl[], eTextureOperationType TypeTbl[], ITexture *pTexTbl[], Uint32 StageCount )		= 0;

		/**
			@brief �O���C�X�P�[���������_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��
			@param fRate		[in] �K�p�x(0.0�`1.0)

			�J���[�摜���O���[�X�P�[�������܂��B<BR>
			fRate�����ɂ���āA�i�K�I�ɃO���[�X�P�[�������鎖���\�ł��B<BR>
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void Grayscale( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex, Float fRate )																= 0;

		/**
			@brief ���j�o�[�T���g�����W�V���������_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param fRate		[in] �������[�g(0.0�`1.0)
			@param SrcBase		[in] �x�[�X�e�N�X�`��UV��`
			@param pBaseTex		[in] �x�[�X�e�N�X�`���C���^�[�t�F�C�X
			@param SrcRule		[in] ���[���e�N�X�`��UV��`
			@param pRuleTex		[in] ���[���e�N�X�`���C���^�[�t�F�C�X

			�O���[�X�P�[���̃��[���摜��p���ă��j�o�[�T���g�����W�V�������s���܂��B<BR>
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void UniversalTransition( CRect2D<Sint32> &Dst, Float fRate, CRect2D<Sint32> &SrcBase, ITexture *pBaseTex, CRect2D<Sint32> &SrcRule, ITexture *pRuleTex )			= 0;

		/**
			@brief �摜���ڂ����ă����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			3x3�{�b�N�X�t�B���^�ŉ摜���ڂ����܂��B
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void Blur9Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief �摜���ڂ����ă����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			4x4�{�b�N�X�t�B���^�ŉ摜���ڂ����܂��B
			�s�N�Z���V�F�[�_�[1.1���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			SingleTexture()�ɒu���������܂��B
		*/
		virtual void Blur16Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief �摜���ڂ����ă����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F
			@param Src			[in] �e�N�X�`��UV��`
			@param pTex			[in] �e�N�X�`��

			8x8�{�b�N�X�t�B���^�ŉ摜���ڂ����܂��B<BR>
			�s�N�Z���V�F�[�_�[2.0���T�|�[�g���Ȃ��r�f�I�J�[�h�̏ꍇ<BR>
			Blur16Box()�ɒu���������܂��B
		*/
		virtual void Blur64Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;
	};
}

#endif // ___SELENE__IPOSTEFFECT___

