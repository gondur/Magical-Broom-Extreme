

#ifndef ___SELENE__COLOR___
#define ___SELENE__COLOR___


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
		@brief �F���Ǘ��N���X
		@author �t���`

		�e��f�[�^�̐F���`���邽�߂̃N���X�ł��B<BR>
		���C�u�������ŐF���w�肷��ꍇ�͂��ׂĂ��̃N���X���g���܂��B
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< �F�̐���
				Uint8 g;		///< �F�̗ΐ���
				Uint8 r;		///< �F�̐Ԑ���
				Uint8 a;		///< �F�̓����x����
			};
			Uint32 Color;		///< �F��32Bit�����\�L
		};

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CColor()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param r		[in] �Ԑ����i�O�`�Q�T�T�j
			@param g		[in] �ΐ����i�O�`�Q�T�T�j
			@param b		[in] �����i�O�`�Q�T�T�j
			@param a		[in] �A���t�@�����i�O�`�Q�T�T�j
		*/
		CColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255 )
		{
			this->a = a;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param Color	[in] �F����
		*/
		CColor( Uint32 Color )
		{
			this->Color = Color;
		}

		/**
			@brief �I�y���[�^�[=���Z�q
			@author �t���`
		*/
		CColor operator = ( CColor &Color )
		{
			this->a = Color.a;
			this->r = Color.r;
			this->g = Color.g;
			this->b = Color.b;

			return *this;
		}

		/**
			@brief �I�y���[�^�[=���Z�q
			@author �t���`
		*/
		CColor operator = ( Uint32 Color )
		{
			this->Color = Color;

			return *this;
		}

		/**
			@brief �^�ϊ�
			@author �t���`
		*/
		operator Uint32 ()
		{
			return Color;
		}

		/**
			@brief �^�ϊ�
			@author �t���`
		*/
		operator const Uint32 () const
		{
			return Color;
		}
	};
}


#endif // ___SELENE__COLOR___


