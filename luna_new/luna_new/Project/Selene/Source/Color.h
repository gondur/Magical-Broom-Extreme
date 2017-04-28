

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
		@brief 色情報管理クラス
		@author 葉迩倭

		各種データの色を定義するためのクラスです。<BR>
		ライブラリ内で色を指定する場合はすべてこのクラスを使います。
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< 色の青成分
				Uint8 g;		///< 色の緑成分
				Uint8 r;		///< 色の赤成分
				Uint8 a;		///< 色の透明度成分
			};
			Uint32 Color;		///< 色の32Bit整数表記
		};

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CColor()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param r		[in] 赤成分（０～２５５）
			@param g		[in] 緑成分（０～２５５）
			@param b		[in] 青成分（０～２５５）
			@param a		[in] アルファ成分（０～２５５）
		*/
		CColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255 )
		{
			this->a = a;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param Color	[in] 色成分
		*/
		CColor( Uint32 Color )
		{
			this->Color = Color;
		}

		/**
			@brief オペレーター=演算子
			@author 葉迩倭
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
			@brief オペレーター=演算子
			@author 葉迩倭
		*/
		CColor operator = ( Uint32 Color )
		{
			this->Color = Color;

			return *this;
		}

		/**
			@brief 型変換
			@author 葉迩倭
		*/
		operator Uint32 ()
		{
			return Color;
		}

		/**
			@brief 型変換
			@author 葉迩倭
		*/
		operator const Uint32 () const
		{
			return Color;
		}
	};
}


#endif // ___SELENE__COLOR___


