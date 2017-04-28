

#ifndef ___SELENE__ANIMATION_H___
#define ___SELENE__ANIMATION_H___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �A�j���[�V�����^�C�v��`
		@author �t���`
	*/
	enum eAnimationType
	{
		ANIM_TYPE_STEP,							///< �X�e�b�v���
		ANIM_TYPE_LINEAR,						///< ���`���
		ANIM_TYPE_TCB,							///< �s�b�a�X�v���C�����
	};

	/**
		@brief �L�[�t���[���f�[�^
		@author �t���`
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< �X�v���C������IN�W����萔�ɂ��邩�ǂ���
		Bool IsOut;								///< �X�v���C������OUT�W����萔�ɂ��邩�ǂ���
		Float fTime;							///< �L�[����
		Float fParam;							///< �L�[�l
		Float fIn;								///< IN�W���̒萔
		Float fOut;								///< OUT�W���̒萔

		SKeyFrame *pPrev;						///< �O���L�[�t���[���f�[�^�|�C���^
		SKeyFrame *pNext;						///< ����L�[�t���[���f�[�^�|�C���^
	};

	/**
		@brief �A�j���[�V�����N���X
		@author �t���`
	*/
	class CAnimation
	{
	private:
		Float m_fTimeFirst;						///< �J�n����
		Float m_fTimeLast;						///< �I������
		SKeyFrame *m_pKeys;						///< �L�[�t���[���f�[�^�|�C���^
		Uint32 m_KeyMax;						///< �L�[�t���[����

	private:
		/**
			@brief �w�莞�Ԃ���ł��߂��L�[�f�[�^���擾���܂�
			@author �t���`
			@param pKeys		[in] �L�[�t���[���f�[�^
			@param fTime		[in] ��������
			@param KeyMax		[in] �L�[�ő吔
			@return �L�[�t���[���f�[�^�|�C���^

			�w�莞�Ԃ�������Ƃ��߂��L�[�����A<BR>
			�o�C�i���T�[�`�Ō������܂��B
		*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

		/**
			@brief �G���~�[�g��Ԋ֐����������܂�
			@author �t���`
			@param fTime	[in] ����
			@param pH1		[out] �p�����[�^�[�i�[��P
			@param pH2		[out] �p�����[�^�[�i�[��Q
			@param pH3		[out] �p�����[�^�[�i�[��R
			@param pH4		[out] �p�����[�^�[�i�[��S

			�G���~�[�g��Ԋ֐����g���ė^����ꂽ�p�����[�^�[����<BR>
			���ʂ��Z�o���܂��B
		*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

		/**
			@brief �O���̃L�[�̏o�͐�̃p�����[�^�����߂܂�
			@author �t���`
			@param pKey0	[in] �O���L�[�f�[�^
			@param pKey1	[in] ����L�[�f�[�^
			@return �Z�o���ꂽ�p�����[�^�[

			�w�莞�Ԃɑ΂��Ă̒��O�̃L�[�̋������v�Z���܂��B
		*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

		/**
			@brief ����̃L�[�̏o�͐�̃p�����[�^�����߂܂�
			@author �t���`
			@param pKey0	[in] �O���L�[�f�[�^
			@param pKey1	[in] ����L�[�f�[�^
			@return �Z�o���ꂽ�p�����[�^�[

			�w�莞�Ԃɑ΂��Ă̒���̃L�[�̋������v�Z���܂��B
		*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param KeyMax		[in] �L�[�ő吔
		*/
		CAnimation( Uint32 KeyMax );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CAnimation();

		/**
			@brief �L�[�t���[���f�[�^�ɃL�[��ݒ肵�܂�
			@author �t���`
			@param KeyNo		[in] �ݒ��L�[�ԍ�
			@param fTime		[in] �ݒ莞��
			@param fParam		[in] �ݒ�p�����[�^
			@param IsIn			[in] ���̓p�����[�^�[�w��L��
			@param IsOut		[in] �o�̓p�����[�^�[�w��L��
			@param fIn			[in] ���̓p�����[�^�[
			@param fOut			[in] �o�̓p�����[�^�[
			@return ��������true

			�w��̃L�[�ɑ΂��āA��ԗp�̃p�����[�^�[��ݒ肵�܂��B
		*/
		virtual Bool SetKey( Uint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

		/**
			@brief �w��^�C�v�̃A�j���[�V�����Ŏw�莞�Ԃɂ�����l���擾���܂�
			@author �t���`
			@param fTime		[in] ����
			@param Type			[in] ��ԃ^�C�v
			@param fDefault		[in] �f�t�H���g�l
			@return		��Ԍ��ʒl

			�w�莞�Ԃɑ΂��Ďw��^�C�v�ŕ�Ԃ����ꍇ�̌��ʂ��擾���܂��B
		*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}


#endif // ___SELENE__ANIMATION_H___

