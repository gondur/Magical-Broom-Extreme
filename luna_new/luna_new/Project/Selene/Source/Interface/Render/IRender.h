

#ifndef ___SELENE__IRENDER___
#define ___SELENE__IRENDER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Class/Math/Math.h"
#include "Class/Math/Vector2D.h"
#include "Class/Math/Vector3D.h"
#include "Class/Math/Vector4D.h"
#include "Interface/Scene/ISceneManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �e�N�X�`���X�e�[�W��`
		@author �t���`

		�e�N�X�`���X�e�[�W�Ɋւ��Ă̒�`�ł��B<BR>
		3D�I�u�W�F�N�g�Ɋւ��Ă͊�{�I�ɃV�F�[�_�[����<BR>
		UV���v�Z����悤�ɂȂ��Ă���̂ŁA<BR>
		���_�f�[�^�Ƃ��ĕێ�����UV�̓J���[�}�b�v�ƃ��C�g�}�b�v�����ł��B
	*/
	enum
	{
		TEXTURE_STAGE_00			= 0,	///< �e�N�X�`���X�e�[�W�O
		TEXTURE_STAGE_01,					///< �e�N�X�`���X�e�[�W�P
		TEXTURE_STAGE_02,					///< �e�N�X�`���X�e�[�W�Q
		TEXTURE_STAGE_03,					///< �e�N�X�`���X�e�[�W�R
		TEXTURE_STAGE_04,					///< �e�N�X�`���X�e�[�W�S
		TEXTURE_STAGE_05,					///< �e�N�X�`���X�e�[�W�T
		TEXTURE_STAGE_06,					///< �e�N�X�`���X�e�[�W�U
		TEXTURE_STAGE_07,					///< �e�N�X�`���X�e�[�W�V
		TEXTURE_STAGE_MAX,					///< �e�N�X�`���X�e�[�W�ő吔

		MESH_TEXTURE_COLORMAP		= 0,	///< ���b�V���p�J���[�}�b�v
		MESH_TEXTURE_LIGHTMAP,				///< ���C�g�}�b�v�i���ݎg���Ă��܂���
		MESH_TEXTURE_NORMALMAP,				///< �o���vor�����}�b�v�p�@���}�b�v
		MESH_TEXTURE_SHADOWMAP,				///< �V���h�E�}�b�v
		MESH_TEXTURE_MAX,					///< 3D���f���pUV��
	};

	/**
		@brief �}���`�e�N�X�`�����Z�^�C�v
		@author �t���`

		�}���`�e�N�X�`���g�p���̃X�e�[�W���̉��Z���@���`���܂��B
	*/
	enum eTextureOperationType
	{
		TEXTURE_OP_NONE,				///< �ȉ��X�e�[�W����
		TEXTURE_OP_MUL,					///< Color = [���ʃX�e�[�W]�~[�e�N�X�`��]
		TEXTURE_OP_ADD,					///< Color = [���ʃX�e�[�W]�{[�e�N�X�`��]
		TEXTURE_OP_SUB,					///< Color = [���ʃX�e�[�W]�|[�e�N�X�`��]
	};

	/**
		@brief ���_��`
		@author �t���`

		���_��`�N���X�̍쐬���Ɏw�肷��t���O�ł��B<BR>
		�Ȃ� VERTEX_ELEMENT_PRIMITIVE�AVERTEX_ELEMENT_SPRITE�AVERTEX_ELEMENT_3DBASE ��<BR>
		�Ɨ����Ă���r���ł��B
	*/
	enum eVertexElement
	{
		VERTEX_ELEMENT_PRIMITIVE	= 1 << 0,			///< �ʒu�ƐF�������܂ލł��P����2D�p���_
		VERTEX_ELEMENT_SPRITE		= 1 << 1,			///< �ʒu�ƐF�ƃe�N�X�`��UV���܂�2D�p���_
		VERTEX_ELEMENT_3DBASE		= 1 << 2,			///< �ʒu�ƐF���܂ނ����Ƃ��P����3D���_
		VERTEX_ELEMENT_3DTEXTURE	= 1 << 3,			///< �e�N�X�`��UV���܂ފ�{�I��3D�p���_
		VERTEX_ELEMENT_3DLIGHT		= 1 << 4,			///< ���C�e�B���O�Ɋւ���@�����܂�3D���_
		VERTEX_ELEMENT_3DBUMP		= 1 << 5,			///< �o���v�}�b�v�Ɋւ���ڐ����܂�3D���_
		VERTEX_ELEMENT_3DANIMATION	= 1 << 6,			///< �X�L�j���O�Ɋւ���{�[���̃C���f�b�N�X���E�F�C�g���܂�3D���_
	};

	/**
		@brief �`��^�C�v��`
		@author �t���`

		�e��`��^�C�v�Ɋւ��Ă̒�`�ł��B
	*/
	enum eDrawType
	{
		DRAW_TYPE_NORMAL,					///< �ʏ�`��
		DRAW_TYPE_BLEND,					///< �������`��
		DRAW_TYPE_ADD,						///< ���Z�`��
		DRAW_TYPE_ADD_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB,						///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_MULTIPLE,					///< ��Z�`��
		DRAW_TYPE_SCREEN,					///< �X�N���[���`��
	};

	/**
		@brief �J�����O�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eCullType
	{
		CULL_FRONT,							///< �\�̏ꍇ�̂ݕ`��
		CULL_BACK,							///< ���̏ꍇ�̂ݕ`��
		CULL_NONE,							///< ���\���ʕ`��
	};

	/**
		@brief �J�����O�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eTextureFilterType
	{
		TEXTURE_FILTER_DISABLE,				///< �t�B���^�����O����
		TEXTURE_FILTER_BILINEAR,			///< �o�C���j�A�t�B���^�����O
		TEXTURE_FILTER_ANISOTROPY_LOW,		///< �ٕ����t�B���^�����O/��掿
		TEXTURE_FILTER_ANISOTROPY_HIGH,		///< �ٕ����t�B���^�����O/���掿
	};

	/**
		@brief �e�N�X�`���T���v�����O���@
		@author �t���`

		0.0�`1.0�ȊO�͈̔͂��w�肵���ꍇ�̋����Ɋւ��Ă̒�`�ł��B<BR>
		Selene�ł͂Q�̗ݏ�ȊO�̃T�C�Y�̃e�N�X�`�����h���C�o��<BR>
		�Ή����Ă���΍쐬�E���p���鎖���\�ł��B<BR>
		�������Q�̗ݏ�ȊO�̃T�C�Y�̃e�N�X�`���𗘗p����ꍇ�́A<BR>
		TEXTURE_ADDRESS_CLAMP ���w�肵�Ă��Ȃ���΂Ȃ�܂���B
	*/
	enum eTextureAddressType
	{
		TEXTURE_ADDRESS_REPEAT,				///< UV���e�N�X�`���͈̔͊O�̎��A�J��Ԃ��܂��B
		TEXTURE_ADDRESS_CLAMP,				///< UV���e�N�X�`���͈̔͊O�̎��A(0�A�e�N�X�`���T�C�Y�j�ɐ������܂��B
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̊�{���_�f�[�^�ł��B<BR>
		���IPointPrimitive2D/ILinePrimitive2D<BR>
		�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_PRIMITIVE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2D
	{
		CVector4D Pos;		///< �ʒu
		CColor Col;			///< ���_�F
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̃e�N�X�`��UV�t�����_�f�[�^�ł��B<BR>
		���IPrimitive2D/ISprite2D/IFontSprite2D<BR>
		�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_SPRITE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2DTex
	{
		CVector4D Pos;		///< �ʒu
		CColor Col;			///< ���_�F
		CVector2D Tex;		///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̊�{���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_BASE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂P�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DBase
	{
		CVector3D Pos;		///< �ʒu
		CColor Col;			///< ���_�F
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃e�N�X�`��UV�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DTEXTURE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂P�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DTexture
	{
		CVector2D TexColor;		///< �e�N�X�`��UV
		CVector2D TexLight;		///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃��C�e�B���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DLIGHT�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂Q�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DLight
	{
		CVector3D Norm;		///< �@��
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃o���v�}�b�s���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DBUMP�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂R�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B
	*/
	struct SVertex3DBump
	{
		CVector3D Tangent;	///< �ڐ�
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃X�L�j���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DANIMATION�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ă͂S�ڂ̍\���̂Ƃ��Ă��̍\���̂�<BR>
		��`����܂��B<BR>
		�P�̒��_�ɂ��Q�̃{�[���̌v�Z���s���܂��B
	*/
	struct SVertex3DAnimation
	{
		Float Weight;		///< �E�F�C�g�i�P�Ԗڂ̃E�F�C�g�������w��A�Q�Ԗڂ̓V�F�[�_�[����1.0-Weight�ŎZ�o�j
		Uint8 Index[4];		///< �{�[���C���f�b�N�X
	};

	/**
		@brief �e�N�X�`�������p�R���t�B�O
		@author �t���`

		�e�N�X�`���������ɎQ�Ƃ����<BR>
		�쐬�p�p�����[�^�[����`�����N���X�ł��B
	*/
	class CTextureConfig
	{
	private:
		CColor m_KeyColor;			///< �J���[�L�[�̐F
		eSurfaceFormat m_Format;	///< �T�[�t�F�C�X�t�H�[�}�b�g

	public:
		/**
			@brief �J���[�L�[�i�����F�j�ݒ�
			@author �t���`
			@param Col	[in] �J���[�L�[�i�����F�j�Ɏg���F<BR>0x00000000�̎��J���[�L�[�i�����F�jOFF

			�e�N�X�`����ǂݍ��񂾍ۂɎw�肵���F�̃A���t�@��0�ɂ��A<BR>
			�J���[�L�[�������s�����悤�ɂ��̃s�N�Z����`��<BR>
			����Ȃ��悤�ɂ��܂��B
		*/
		void SetColorKey( CColor Col )
		{
			m_KeyColor = Col;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g�ݒ�
			@author �t���`
			@param Fmt	[in] �T�[�t�F�C�X�t�H�[�}�b�g

			�e�N�X�`���ǂݍ��ݎ��̃T�[�t�F�C�X�t�H�[�}�b�g��ݒ肵�܂��B<BR>
			�����ȃt�H�[�}�b�g���w�肵���ꍇ�A�쐬�͎��s���܂��B
		*/
		void SetFormat( eSurfaceFormat Fmt )
		{
			m_Format = Fmt;
		}

		/**
			@brief �J���[�L�[���擾
			@author �t���`
			@retval	0		�J���[�L�[�������s��Ȃ�
			@retval	0�ȊO	���̐F���J���[�L�[�Ƃ���
		*/
		CColor GetColorKey( void )
		{
			return m_KeyColor;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g���擾���܂�
			@author �t���`
			@return �T�[�t�F�C�X�t�H�[�}�b�g
		*/
		eSurfaceFormat GetFormat( void )
		{
			return m_Format;
		}
	};

	/**
		@brief �����_���[�C���^�[�t�F�C�X
		@author �t���`

		��ʂɑ΂���S�Ă̕`�揈�����Ǘ����܂��B<BR>
		�`��p�̊e��N���X���S�Ă��̃N���X����擾���܂�<BR>
		�܂����̃C���^�[�t�F�C�X��1��IDevice�C���^�[�t�F�C�X�ɑ΂���1�����쐬����܂���B
	*/
	class IRender
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
		virtual Uint32 Release( void )																																					= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																																					= 0;

		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param Stage	[in] �ݒ肷��X�e�[�W�i�O�`�V�j
			@param pTex		[in] �ݒ肷��e�N�X�`���iNULL�Ŗ������j
			@retval false	���s
			@retval true	����

			�e�N�X�`���������_���[�ɐݒ肵�܂��B<BR>
			��x�ݒ肳�ꂽ�e�N�X�`����NULL��ݒ肷��܂�<BR>
			�L���ɂȂ��Ă��܂��B
		*/
		virtual Bool SetTexture( Uint32 Stage, ITexture *pTex )																															= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂��܂��B
		*/
		virtual Bool ResetRenderTarget( void )																																			= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
			CreateRenderTarget()�Ő������ꂽ�e�N�X�`���ȊO�͎��s���܂��B
		*/
		virtual Bool SetRenderTarget( ITexture *pTexture )																																= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ɐݒ�
			@author �t���`
			@retval true	����
			@retval false	���s

			�T�[�t�F�C�X�������_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
			�����_�����O�^�[�Q�b�g�Ƃ��Đ������ꂽ�T�[�t�F�C�X�łȂ��ꍇ��<BR>
			���̊֐��͎��s���܂��B
		*/
		virtual Bool SetRenderTarget( ISurface *pSurface )																																= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�擾
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g���擾���܂��B
		*/
		virtual Bool GetRenderTarget( ITexture **ppTexture )																															= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�擾
			@author �t���`
			@retval true	����
			@retval false	���s

			�����_�����O�^�[�Q�b�g���擾���܂��B
		*/
		virtual Bool GetRenderTarget( ISurface **ppSurface )																															= 0;

		/**
			@brief �[�x�X�e���V���o�b�t�@�ɐݒ�
			@author �t���`
			@retval true	����
			@retval false	���s

			�T�[�t�F�C�X��[�x�X�e���V���T�[�t�F�C�X�Ƃ��Đݒ肵�܂��B<BR>
			�[�x�X�e���V���T�[�t�F�C�X�Ƃ��Đ������ꂽ�T�[�t�F�C�X�łȂ��ꍇ��<BR>
			���̊֐��͎��s���܂��B
		*/
		virtual Bool SetDepthStencil( ISurface *pSurface )																																= 0;

		/**
			@brief �����_�����O�����J�n�ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă��ꂩ�烌���_�����O������<BR>
			�J�n����Ƃ�������ʒm���܂��B
		*/
		virtual void Begin( void )																																						= 0;

		/**
			@brief �����_�����O�����I���ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă���Ń����_�����O������<BR>
			�I������Ƃ������Ƃ�ʒm���܂��B
		*/
		virtual void End( void )																																						= 0;

		/**
			@brief �|�X�g�G�t�F�N�g�Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@return �|�X�g�G�t�F�N�g�Ǘ��C���^�[�t�F�C�X

			�|�X�g�G�t�F�N�g�Ǘ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�e�N�X�`�����g�����|�X�g�G�t�F�N�g�Ɋւ��鏈���͑S�Ă��̃C���^�[�t�F�C�X����܂��B
		*/
		virtual IPostEffect *CreatePostEffect( void )																																	= 0;

		/**
			@brief �V�[���Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@return �V�[���Ǘ��C���^�[�t�F�C�X

			�V�[���Ǘ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			3D�Ɋւ��郌���_�����O�����͑S�Ă��̃C���^�[�t�F�C�X����܂��B
		*/
		virtual ISceneManager *CreateSceneManager( eSceneMode Mode = SCENE_MODE_MANAGED, eSceneModeOption Option = SCENE_MODE_OPTION_NO )												= 0;

		/**
			@brief 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PointMax	[in] �����o�b�t�@�i�[�\�|�C���g��
			@return 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɓ_��łꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual IPointPrimitive2D *CreatePointPrimitive2D( Uint32 PointMax )																											= 0;

		/**
			@brief 2D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param LineMax	[in] �����o�b�t�@�i�[�\���C����
			@return 2D���C���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɐ��������ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual ILinePrimitive2D *CreateLinePrimitive2D( Uint32 LineMax )																												= 0;

		/**
			@brief 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@return 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual IPrimitive2D *CreatePrimitive2D( Uint32 PrimitiveMax )																													= 0;

		/**
			@brief 2D�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@param pTexture		[in] �X�v���C�g�Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@return 2D�X�v���C�g�C���^�[�t�F�C�X

			2D�̃X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive2D���p�����Ă���A�����I�ɂ�IPrimitive2D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`�����g�����ł��ȒP�ȃX�v���C�g�`�悪�\�ȃC���^�[�t�F�C�X�ł��B
		*/
		virtual ISprite2D *CreateSprite2D( Uint32 PrimitiveMax, ITexture *pTexture )																									= 0;

		/**
			@brief 2D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pBuffer		[in] �`�旘�p������i�����Ŏw�肵���������摜�Ƃ��ēW�J���g����悤�ɂ��܂��j
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@param pFontFace	[in] �t�H���g����
			@param FontSize		[in] �t�H���g�T�C�Y
			@param IsItalic		[in] �Α̃t�H���gON/OFF
			@param IsBold		[in] �����t�H���gON/OFF
			@param IsAntialias	[in] �A���`�G�C���A�X�t�H���gON/OFF
			@return 2D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			2D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			ISprite2D�𗘗p���Ă���A�����I�ɂ�ISprite2D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`���Ɏ��O�ɕ������摜�Ƃ��ēW�J���Ă������ƂŁA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual IFontSprite2D *CreateFontSprite2D( const wchar_t *pBuffer, Uint32 FontMax, const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold, Bool IsAntialias )	= 0;

		/**
			@brief 2D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pFileName	[in] �t�H���g�X�v���C�g�p��`�t�@�C��
			@param pExt			[in] �t�H���g�X�v���C�g�p�摜�t�@�C���g���q
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@return 2D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			2D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			ISprite2D�𗘗p���Ă���A�����I�ɂ�ISprite2D�ł̕`����s���Ă��܂��B<BR>
			FontUtility�Ő���������`�t�@�C���ƃe�N�X�`�����g���āA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual IFontSprite2D *CreateFontSprite2DFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 FontMax )																= 0;

		/**
			@brief 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] �|�C���g�̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|�C���g�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual IPointPrimitive3D *CreatePointPrimitive3D( Uint32 VertexMax, Bool IsDynamic )																							= 0;

		/**
			@brief 3D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] ���C���̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D���C���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃��C���`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual ILinePrimitive3D *CreateLinePrimitive3D( Uint32 VertexMax, Bool IsDynamic )																								= 0;

		/**
			@brief 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] �������_�o�b�t�@�̍ő吔
			@param IndexMax		[in] �����C���f�b�N�X�o�b�t�@�̍ő吔
			@param VertexFlag	[in] ���_�f�[�^�t���O�ieVertexElement�̑g�ݍ��킹�j
			@param IsDynamic		[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B<BR>
			�܂��C���f�b�N�X���g�p���������I�ȕ`����T�|�[�g���܂��B<BR>
			VertexFlag�͒��_�̃t�H�[�}�b�g���w�肷����̂� eVertexElement �񋓌^�̒�����<BR>
			VERTEX_ELEMENT_PRIMITIVE �� VERTEX_ELEMENT_SPRITE �����������̂��w�肵�܂��B<BR>
			�����g�ݍ��킹��ꍇ�� | ���Z�q�Ŏw�肵�Ă��������B<BR>
			���p�����V�F�[�_�[�͓����ō쐬���ꂽ�Œ�V�F�[�_�[�����p����܂��B<BR>
			���݂̃o�[�W�����ł̓o���v�}�b�v�Ɋւ��鏈���͍s���܂���B<BR>
			<BR>
			�i��j�@�����������C�e�B���O�\�Ȓ��_ -> VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT
		*/
		virtual IPrimitive3D *CreatePrimitive3D( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic )																	= 0;

		/**
			@brief ���f�����t�@�C�����琶��
			@author �t���`
			@param pFileName	[in] ���f����

			SMF�`���̃��f���t�@�C����ǂݍ��݂܂��B<BR>
			SMF�t�@�C����ConvertX2SMF���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual IModel *CreateModelFromFile( const wchar_t *pFileName )																													= 0;

		/**
			@brief ���f�������������琶��
			@author �t���`
			@param pData	[in] ���f���f�[�^
			@param Size		[in] �f�[�^�T�C�Y

			SMF�`���̃��f���f�[�^��ǂݍ��݂܂��B<BR>
			SMF�t�@�C����ConvertX2SMF���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual IModel *CreateModelFromMemory( const Uint8 *pData, Uint32 Size )																										= 0;

		/**
			@brief �f�o�C�X����T�[�t�F�C�X�𐶐�
			@author �t���`
			@param Width	[in] �T�[�t�F�C�X�̉���
			@param Height	[in] �T�[�t�F�C�X�̏c��
			@param Format	[in] �T�[�t�F�C�X�̃t�H�[�}�b�g
			@return �T�[�t�F�C�X�C���^�[�t�F�C�X
		*/
		virtual ISurface *CreateDepthStencilSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format )																				= 0;

		/**
			@brief �f�o�C�X����T�[�t�F�C�X�𐶐�
			@author �t���`
			@param Width		[in] �T�[�t�F�C�X�̉���
			@param Height		[in] �T�[�t�F�C�X�̏c��
			@param Format		[in] �T�[�t�F�C�X�̃t�H�[�}�b�g
			@param pCopyTarget	[in] Copy�g�p���̃R�s�[��̃T�[�t�F�C�X�i�t�H�[�}�b�g�ϊ��@�\�̃`�F�b�N�p�j
			@return �T�[�t�F�C�X�C���^�[�t�F�C�X
		*/
		virtual ISurface *CreateRenderTargetSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format, ISurface *pCopyTarget )														= 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^���擾
			@author �t���`
			@return �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual CTextureConfig &GetTextureConfig( void )																																= 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^�ݒ�
			@author �t���`
			@param Conf		[in] �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual void SetTextureConfig( CTextureConfig &Conf )																															= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param Width	[in] �e�N�X�`���̉���
			@param Height	[in] �e�N�X�`���̏c��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTexture( Uint32 Width, Uint32 Height )																													= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromFile( const wchar_t *pFileName )																												= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromMemory( void *pData, Uint32 Size )																											= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param Width	[in] �e�N�X�`���̉���
			@param Height	[in] �e�N�X�`���̏c��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureRenderTarget( Uint32 Width, Uint32 Height )																										= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@param fHeight	[in] �@���}�b�v�̍����{��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )																					= 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@param fHeight	[in] �@���}�b�v�̍����{��
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )																			= 0;

		/**
			@brief �`��^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �`��^�C�v

			�|���S���̕`��^�C�v��ݒ肵�܂��B
		*/
		virtual void SetDrawType( eDrawType Type )																																		= 0;

		/**
			@brief �\������^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �\������^�C�v

			�|���S���̕\������^�C�v��ݒ肵�܂��B
		*/
		virtual void SetCullType( eCullType Type )																																		= 0;

		/**
			@brief �t�B���^�����O�^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �t�B���^�����O�^�C�v

			�e�N�X�`���X�e�[�W���̃t�B���^�����O�^�C�v��ݒ肵�܂��B<BR>
			TEXTURE_FILTER_ANISOTROPY�n �̃t�B���^���T�|�[�g����Ȃ��n�[�h�E�F�A�ł�<BR>
			TEXTURE_FILTER_BILINEAR ���g���܂��B
		*/
		virtual void SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )																													= 0;

		/**
			@brief �e�N�X�`���A�h���b�V���O�^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �A�h���b�V���O�^�C�v

			�e�N�X�`���X�e�[�W���̃e�N�X�`���A�h���b�V���O�^�C�v��ݒ肵�܂��B<BR>
			0.0�`1.0�͈̔͊O��UV���w�肵�����ɂǂ̗l�ȏ������s�������w�肵�܂��B
		*/
		virtual void SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )																									= 0;

		/**
			@brief �e�N�X�`���I�y���[�V�����^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �I�y���[�V�����^�C�v

			�e�N�X�`���X�e�[�W���̃e�N�X�`���J���[�I�y���[�V�����^�C�v��ݒ肵�܂��B<BR>
			���ʃX�e�[�W�Ƃ̍������@�̏������w�肵�܂��B
		*/
		virtual void SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )																								= 0;

		/**
			@brief �[�x�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�e�X�gON/OFF

			�[�x�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthTestEnable( Bool Flag )																																	= 0;

		/**
			@brief �[�x�o�b�t�@��������ON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�o�b�t�@��������ON/OFF

			�[�x�o�b�t�@�������݂�ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthWriteEnable( Bool Flag )																																	= 0;

		/**
			@brief �A���t�@�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �A���t�@�e�X�gON/OFF

			�A���t�@�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetAlphaTestEnable( Bool Flag )																																	= 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N�ɑޔ����܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ������܂��B<BR>
			���̊֐��ɂ���đޔ������X�e�[�g�͈ȉ��̊֐��Őݒ肵�����̂ł��B<BR>
			�Evoid SetDrawType( eDrawType Type )<BR>
			�Evoid SetCullType( eCullType Type )<BR>
			�Evoid SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )<BR>
			�Evoid SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )<BR>
			�Evoid SetFogEnable( Bool Flag )<BR>
			�Evoid SetFogColor( CColor Color )<BR>
			�Evoid SetDepthTestEnable( Bool Flag )<BR>
			�Evoid SetDepthWriteEnable( Bool Flag )<BR>
			�Evoid SetAlphaTestEnable( Bool Flag )<BR>
			�Evoid SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )<BR>
			�EBool SetTexture( Uint32 Stage, ITexture *pTex )
		*/
		virtual Bool StatePush( void )																																					= 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N���畜�A���܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B
		*/
		virtual Bool StatePop( void )																																					= 0;

		/**
			@brief �X�e�[�g�̐ݒ��������ԂɃ��Z�b�g���܂�
			@author �t���`

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B<BR>
			�ESetDrawType( DRAW_TYPE_NORMAL )<BR>
			�ESetDrawType( DRAW_TYPE_NORMAL )<BR>
			�ESetCullType( CULL_FRONT )<BR>
			�ESetFogEnable( false )<BR>
			�ESetFogColor( 0x00000000 )<BR>
			�ESetDepthTestEnable( false )<BR>
			�ESetDepthWriteEnable( false )<BR>
			�Evoid SetAlphaTestEnable( true )<BR>
			�ESetTextureFilterType( <Stage>, TEXTURE_FILTER_DISABLE )<BR>
			�ESetTextureAddressType( <Stage>, TEXTURE_ADDRESS_REPEAT )<BR>
			�ESetTextureOperationType( <Stage>, <Stage>==0?TEXTURE_OP_MUL:TEXTURE_OP_NONE )<BR>
			�ESetTexture( <Stage>, NULL )
		*/
		virtual void StateInit( void )																																					= 0;
	};
}

#endif // ___SELENE__IRENDER___

