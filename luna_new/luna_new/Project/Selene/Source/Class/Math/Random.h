

#ifndef ___SELENE_RAND_H___
#define ___SELENE_RAND_H___


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
		@brief ���������N���X
		@author �t���`
	*/
	class SELENE_DLL_API CRandom
	{
		enum { N = 624UL };

	private:
		Uint32 MersenneTwister[N];			///< ���������p���[�N
		Sint32 MersenneTwisterCount;		///< ���������p���[�N

	private:
		/**
			@brief �[����������
			@author �t���`
			@return �����l

			32Bit�����̋[�������𐶐����܂��B
		*/
		virtual Uint32 GenerateInt32( void );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRandom();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRandom( Uint32 Param );

		/**
			@brief �����p��ݒ�
			@author �t���`
			@param Param	[in] �V�[�h�l

			���������̎��ݒ肵�܂��B
		*/
		virtual void Seed( Uint32 Param );

		/**
			@brief 32Bit���������擾
			@author �t���`
			@return �����l

			32Bit�����̗����l���擾���܂��B
		*/
		virtual Uint32 GetInt32( void );

		/**
			@brief 64Bit���������擾
			@author �t���`
			@return �����l

			64Bit�����̗����l���擾���܂��B
		*/
		virtual Uint64 GetInt64( void );

		/**
			@brief 32Bit�������������擾
			@author �t���`
			@return �����l

			32Bit���������̗����l���擾���܂��B
		*/
		virtual Float GetFloat32( void );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l

			�w��͈͓��̐����������擾���܂��B
		*/
		virtual Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l

			�w��͈͓��̕��������������擾���܂��B
		*/
		virtual Float GetFloat( Float Min, Float Max );
	};
}

#endif // ___SELENE_RAND_H___

