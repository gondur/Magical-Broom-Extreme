

#ifndef ___SELENE__ISCENEMANAGER___
#define ___SELENE__ISCENEMANAGER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �V�[�������_�����O���[�h
		@author �t���`
	*/
	enum eSceneMode
	{
		SCENE_MODE_NOT_MANAGED,			///< �����_�����O�����s��Ȃ�
		SCENE_MODE_MANAGED,				///< �����Ő[�x�o�b�t�@�⃌���_�����O�^�[�Q�b�g���Ǘ�����
		SCENE_MODE_1PASS_DOF,			///< 1PASS�Ŕ�ʊE�[�x�������s���i�A���t�@�u�����f�B���O�͂ł��Ȃ��Ȃ�܂�
		SCENE_MODE_2PASS_DOF,			///< 2PASS�Ŕ�ʊE�[�x�������s���i�A���t�@�u�����f�B���O���ł��܂�
		SCENE_MODE_1PASS_DOF_HIGH,		///< 1PASS�ō��掿��ʊE�[�x�������s���i�A���t�@�u�����f�B���O�͂ł��Ȃ��Ȃ�܂�
		SCENE_MODE_2PASS_DOF_HIGH,		///< 2PASS�ō��掿��ʊE�[�x�������s���i�A���t�@�u�����f�B���O���ł��܂�
	};

	/**
		@brief �V�[�������_�����O���[�h
		@author �t���`
	*/
	enum eSceneModeOption
	{
		SCENE_MODE_OPTION_NO,					///< �I�v�V�����Ȃ�
		SCENE_MODE_OPTION_HDR,					///< HDR�����_�����O���s���܂��i�A���t�@�u�����f�B���O�E�A���t�@�e�X�g�͂ł��Ȃ��Ȃ�܂�
		SCENE_MODE_OPTION_EDGE,					///< �G�b�W�����_�����O���s���܂�
		SCENE_MODE_OPTION_SHADOW,				///< �e�̃����_�����O���s���܂�
	};

	/**
		@brief �V�[���Ǘ��p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISceneManager
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																								= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Uint32 Release( void )																								= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Uint32 AddRef( void	)																								= 0;

		/**
			@brief �V�[���J�����擾
			@author �t���`
			@return �J�����f�[�^

			�V�[���Ɋ֘A�t����ꂽ�J�������擾���܂��B
		*/
		virtual ISceneCamera *GetSceneCamera( void )																				= 0;

		/**
			@brief �V�[��������
			@author �t���`

			�V�[���̃��C�g��t�H�O�Ȃǂ̃f�[�^�����Z�b�g���܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void Reset( void )																									= 0;

		/**
			@brief �V�[���J�n
			@author �t���`
			@param IsSort	[in] �V�[�����̃I�u�W�F�N�g���\�[�g���邩�ǂ���

			�V�[���Ǘ����J�n���܂��B<BR>
			���̎��_�ŃJ�����̃f�[�^���m�肵�܂��̂�<BR>
			���̊֐����Ăяo�������Ƃ̃J�����̍X�V�͑S�Ė����ł��B
		*/
		virtual void Begin( Bool IsSort )																							= 0;

		/**
			@brief �V�[���I��
			@author �t���`

			�V�[���̊Ǘ����������܂��B
		*/
		virtual void End( void )																									= 0;

		/**
			@brief �V�[�������_�����O
			@author �t���`
			@param IsDrawBuffer	[in] �����p�o�b�t�@�̕\���i�f�o�b�O�p�j

			�V�[���̊Ǘ��ō\�z���ꂽ�V�[���������_�����O���܂��B<BR>
			���̊֐����R�[�������i�K�œ����ŕ`�揈�����J�n����܂��B<BR>
			�K��IRender::Begin()�`IRender::End()�ԂŌĂяo���Ă��������B
		*/
		virtual void Rendering( Bool IsDrawBuffer = false )																			= 0;

		/**
			@brief �V���h�E�p�J�����ݒ�
			@author �t���`
			@param vPosition	[in] �J�����ʒu
			@param vTarget		[in] �J���������_
			@param Fov			[in] ��p�i1��65536�Ƃ����p�x�j
			@param fNear		[in] �߃N���b�v��
			@param fFar			[in] ���N���b�v��

			�V���h�E�p�̃J�����f�[�^��ݒ肵�܂��B
		*/
		virtual void SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias )	= 0;

		/**
			@brief �t�H�OON/OFF
			@author �t���`
			@param Enable	[in] �t�H�O��K�p����ꍇON

			�V�[���ɓK�p�����t�H�O��ON/OFF���܂��B
		*/
		virtual void SetFogEnable( Bool Enable )																					= 0;

		/**
			@brief �t�H�O���ݒ�
			@author �t���`

			@param fNear	[in] �t�H�O�J�nZ�i����Z���O�̓t�H�O�ɉe������Ȃ��j
			@param fFar		[in] �t�H�O�I��Z�i����Z����͊��S��Color�̐F�ɂȂ�j
			@param Color	[in] �t�H�O�̐F

			�V�[���ɓK�p�����t�H�O�̃p�����[�^�[��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetFog( Float fNear, Float fFar, CColor Color )																= 0;

		/**
			@brief ��ʊE�[�x�p�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
			@author �t���`

			@param fForcusZ	[in] �t�H�[�J�X�̂y�i�J������j
			@param fPower	[in] ��ʊE�[�x���x

			��ʊE�[�x�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
		*/
		virtual void SetDepthOfFieldForcus( Float fForcusZ, Float fPower )															= 0;

		/**
			@brief �A���r�G���g���C�g�ݒ�
			@author �t���`
			@param vColorSky	[in] �V�[�����̓V���̊����̐F
			@param vColorEarth	[in] �V�[�����̒n�\�̊����̐F

			�V�[���̊�����ݒ肵�܂��B<BR>
			�������C�e�B���O���s�����߂ɁA�V���ƒn�\�̐F��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth )												= 0;

		/**
			@brief �f�B���N�V�������C�g�ݒ�
			@author �t���`
			@param vDirect	[in] �V�[�����̕��s�����̕���
			@param vColor	[in] �V�[�����̕��s�����̐F

			�V�[���ɑ債��1�������s���������蓖�Ă邱�Ƃ��ł��܂��B<BR>
			���z�̂悤�ɗy�������ɑ��݂��A�I�u�W�F�N�g�̈ʒu�ɂ����<BR>
			���̕������ς��Ȃ��悤�ȃ��C�g�Ɍ����Ă��܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetDirectionLight( CVector3D &vDirect, CVector3D &vColor )														= 0;

		/**
			@brief �|�C���g���C�g�ǉ�
			@author �t���`
			@param vPosition	[in] �V�[�����̓_�����̈ʒu
			@param vColor		[in] �V�[�����̓_�����̐F
			@param fDistance	[in] �V�[���̓_�����̉e������

			�V�[���ɑ΂��ē_������ǉ����܂�<BR>
			�ő��32�̃��C�g��ݒ�ł��A���̂����ł��I�u�W�F�N�g�ɋ߂�<BR>
			4�̃��C�g���I�u�W�F�N�g�ɓK�p����܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance )										= 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̃T�C�Y��ݒ�
			@author �t���`
			@param Size		[in] �T�C�Y

			�V�[���̃����_�����O�^�[�Q�b�g�̃T�C�Y���w�肵�܂��B<BR>
			eSceneMode��SCENE_MODE_NORMAL�ȊO�̏ꍇ�Ɏg����e��<BR>
			�o�b�t�@�̃T�C�Y�Ɋ֌W���܂��B
		*/
		virtual CPoint2D<Uint32> SetRenderTargetSize( CPoint2D<Uint32> Size )														= 0;

		/**
			@brief �����_�����O���N�G�X�g���擾
			@author �t���`
			@return �����_�����O���N�G�X�g��

			�V�[���Ƀ��N�G�X�g�����_�����O�����擾���܂��B
		*/
		virtual Uint32 GetRenderingRequestCount( void )																				= 0;

		/**
			@brief �����_�����O���擾
			@author �t���`
			@return �����_�����O��

			�V�[���Ŏ��s���ꂽ�����_�����O�����擾���܂��B<BR>
			2Pass�n�̏��������J�E���g�����̂ŁA<BR>
			���N�G�X�g���ȏ�̒l�ɂȂ邱�Ƃ�����܂��B
		*/
		virtual Uint32 GetRenderingCount( void )																					= 0;

		/**
			@brief �����_�����O�s�N�Z�����擾
			@author �t���`
			@return �����_�����O�s�N�Z����

			�����_�����O�������f���̃����_�����O�s�N�Z�������擾���܂��B<BR>
			�T�|�[�g����Ă��Ȃ��r�f�I�J�[�h�̏ꍇ��0xFFFFFFFF���Ԃ�܂��B
		*/
		virtual Uint32 GetOcculusion( Uint32 Index )																				= 0;
	};
}

#endif // ___SELENE__ISCENEMANAGER___


