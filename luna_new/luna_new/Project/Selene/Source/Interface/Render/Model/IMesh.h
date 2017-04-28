

#ifndef ___SELENE__IMESH___
#define ___SELENE__IMESH___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class IMesh
	{
	public:
		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)													= 0;

		/**
			@brief ���ʔ��˗p���f���ɕϊ�
			@author �t���`

			���̊֐����Ăяo���Ǝ��ŋ��ʔ��˂�L�����o���܂��B<BR>
			���s�����ɑ΂��Ă̒P���ȃt�H�����ʔ��˂��K�p�����悤�ɂȂ�܂��B
		*/
		virtual void ConvertReflexMesh( void )											= 0;

		/**
			@brief �o���v�}�b�v�p���f���ɕϊ�
			@author �t���`
			@param pTexNormal	[in] �o���v�p�@���}�b�v

			���̊֐����Ăяo���Ǝ��Ńo���v�}�b�v��L�����o���܂��B<BR>
			�������ȉ��̏����𖞂����Ă���K�v������܂��B<BR>
			�E�e�N�X�`��UV�f�[�^�������Ă���<BR>
			�E�@���E�ڐ��f�[�^�������Ă���<BR>
			<BR>
			�ʏ�ConvertX2SMF�ō쐬�����ꍇ�͌���X�t�@�C���Ƀe�N�X�`�����܂܂�ē���΁A<BR>
			��L�̃f�[�^�͊܂܂�Ă��܂��B<BR>
			�܂����̂Ƃ��w�肷��e�N�X�`���͖@���}�b�v�ł���K�v������܂��B<BR>
			�@���}�b�v��IRender::CreateTextureFromFileForNormalMap()��
			IRender::CreateTextureFromMemoryForNormalMap()�֐��ō쐬�ł��܂��B
		*/
		virtual void ConvertBumpMesh( ITexture *pTexNormal )								= 0;

		/**
			@brief �����}�b�v�p���f���ɕϊ�
			@author �t���`
			@param pTexNormal		[in] �o���v�p�@���}�b�v
			@param fParallaxDepth	[in] �����[�x�i��������0.01�`0.05���x�j

			���̊֐����Ăяo���Ǝ��Ŏ����}�b�v��L�����o���܂��B<BR>
			�������ȉ��̏����𖞂����Ă���K�v������܂��B<BR>
			�E�e�N�X�`��UV�f�[�^�������Ă���<BR>
			�E�@���E�ڐ��f�[�^�������Ă���<BR>
			<BR>
			�ʏ�ConvertX2SMF�ō쐬�����ꍇ�͌���X�t�@�C���Ƀe�N�X�`�����܂܂�ē���΁A<BR>
			��L�̃f�[�^�͊܂܂�Ă��܂��B<BR>
			�@���}�b�v��IRender::CreateTextureFromFileForNormalMap()��
			IRender::CreateTextureFromMemoryForNormalMap()�֐��ō쐬�ł��܂��B
		*/
		virtual void ConvertParallaxMesh( ITexture *pTexNormal, Float fParallaxDepth )	= 0;

		/**
			@brief �}�e���A���̐����擾
			@author �t���`
			@return �}�e���A����

			���b�V������������}�e���A���̐����擾���܂�
		*/
		virtual Uint32 GetMaterialCount( void )											= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param Color			[in] �X�y�L�����̐F

			�}�e���A�����Ƃ̃X�y�L�����̐F��ݒ肵�܂�
		*/
		virtual void SetSpecularColor( Uint32 MaterialIndex, CColor Color )				= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fRefractive		[in] �X�y�L�����̋��ܗ�(����20.0f)

			�}�e���A�����Ƃ̃X�y�L�����̋��ܗ���ݒ肵�܂�
		*/
		virtual void SetSpecularRefractive( Uint32 MaterialIndex, Float fRefractive )	= 0;

		/**
			@brief �X�y�L�����ݒ�
			@author �t���`
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fRoughly			[in] �X�y�L�����̑e��(����0.5f)

			�}�e���A�����Ƃ̃X�y�L�����̑e����ݒ肵�܂�
		*/
		virtual void SetSpecularRoughly( Uint32 MaterialIndex, Float fRoughly )			= 0;

		/**
			@brief �@���f�[�^�̉��������܂�
			@author �t���`
			@param fLength	[in] ����

			���b�V���̖@���E�ڐ��E�]�@���f�[�^�����������邱�Ƃ��ł��܂��B
		*/
		virtual void NormalVisible( Float fLength )										= 0;

		/**
			@brief �o�E���f�B���O�f�[�^�̉��������܂�
			@author �t���`

			���b�V���̃o�E���f�B���O�{�b�N�X�����������邱�Ƃ��ł��܂��B
		*/
		virtual void BoundingVisible( void )											= 0;

		/**
			@brief �����_�����OID�擾
			@author �t���`

			�����_�����O���̃V�[��ID���擾���܂��B
		*/
		virtual Sint32 GetRenderID( void )												= 0;
	};
}


#endif // ___SELENE__IMESH___

