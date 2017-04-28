

#ifndef ___SELENE__TEXTUREMGR___
#define ___SELENE__TEXTUREMGR___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Core/CDevice.h"
#include "Object/CDeviceObjectMgr.h"
#include "Surface/CTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief テクスチャ管理クラス
		@author 葉迩倭
	*/
	class CTextureMgr : public CDeviceObjectMgr
	{
	protected:

	public:
		CTextureMgr( CDevice *pDevice );
		virtual ~CTextureMgr();

		CTexture *SearchInstance( const wchar_t *pFileName );

		virtual CTexture *Create( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual CTexture *CreateRenderTarget( Uint32 Width, Uint32 Height, eSurfaceFormat Format );
		virtual CTexture *CreateFromFile( const wchar_t *pFileName, eSurfaceFormat Format, CColor KeyColor );
		virtual CTexture *CreateFromMemory( const void *pData, Uint32 Size, eSurfaceFormat Format, CColor KeyColor );
		virtual CTexture *CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight );
		virtual CTexture *CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight );
	};
}

#endif // ___SELENE__TEXTUREMGR___

