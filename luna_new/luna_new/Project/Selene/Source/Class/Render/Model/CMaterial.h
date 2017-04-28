

#ifndef ___SELENE__CMATERIAL___
#define ___SELENE__CMATERIAL___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/IRender.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CTexture;

	class CMaterial
	{
	private:
		CTexture *m_pTexture[MESH_TEXTURE_MAX];
		CVector4D m_vMaterialColor;
		CVector4D m_vSpecularColor;
		Float m_fRefractive;
		Float m_fRoughly;
		Uint32 m_VertexStart;
		Uint32 m_VertexCount;
		Uint32 m_IndexStart;
		Uint32 m_IndexCount;

	public:
		CMaterial();
		virtual ~CMaterial();

		virtual void SetTexture( Uint32 Stage, CTexture *pTexture );
		virtual CTexture *GetTexturePointer( Uint32 Stage ) const;

		virtual void SetColor( const CVector4D &Color );
		virtual const CVector4D &GetColor( void ) const;

		virtual void SetSpecularColor( const CVector4D &Color );
		virtual const CVector4D &GetSpecularColor( void ) const;

		virtual void SetSpecularRefractive( const Float fRefractive );
		virtual const Float &GetSpecularRefractive( void ) const;

		virtual void SetSpecularRoughly( const Float fRoughly );
		virtual const Float &GetSpecularRoughly( void ) const;

		virtual void SetVertexStart( Uint32 Start );
		virtual void SetVertexCount( Uint32 Count );
		virtual void SetIndexStart( Uint32 Start );
		virtual void SetIndexCount( Uint32 Count );

		virtual Uint32 GetVertexStart( void );
		virtual Uint32 GetVertexCount( void );
		virtual Uint32 GetIndexStart( void );
		virtual Uint32 GetIndexCount( void );

		CMaterial& operator = ( CMaterial &Src );
	};
}

#endif // ENABLE_3D

#endif // ___SELENE__CMATERIAL___


