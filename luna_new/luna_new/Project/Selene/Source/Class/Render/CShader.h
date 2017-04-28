

#ifndef ___SELENE__SHADER___
#define ___SELENE__SHADER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObject.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class ITexture;

	class CShader : public CDeviceObject
	{
	protected:
		ID3DXEffect *m_pEffect;

	public:
		CShader( CBaseMgr *pMgr );
		virtual ~CShader();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Bool CreateFromFile( const wchar_t *pFileName );
		virtual Bool CreateFromMemory( const Uint8 *pShader, Uint32 Size );

		virtual Bool Begin( Uint32 *pPassMax );
		virtual void End( void );
		virtual void BeginPass( Uint32 Pass );
		virtual void EndPass( void );
		virtual void UpdateParameter( void );

		virtual FX_HANDLE GetParameterByName( const wchar_t *pName );
		virtual FX_HANDLE GetParameterBySemantic( const wchar_t *pSemantic );

		virtual FX_HANDLE GetTechnique( const wchar_t *pName );
		virtual void SetTechnique( FX_HANDLE Handle );

		virtual void SetFloat( FX_HANDLE Handle, Float Param );
		virtual void SetFloatArray( FX_HANDLE Handle, Float *pParam, Sint32 Num );
		virtual void SetInt( FX_HANDLE Handle, Sint32 Param );
		virtual void SetIntArray( FX_HANDLE Handle, Sint32 *pParam, Sint32 Num );
		virtual void SetMatrix( FX_HANDLE Handle, SMatrix4x4 *pMatrix );
		virtual void SetMatrixArray( FX_HANDLE Handle, SMatrix4x4 *pMatrix, Sint32 Num );
		virtual void SetMatrixPointerArray( FX_HANDLE Handle, const SMatrix4x4 **ppMatrix, Sint32 Num );
		virtual void SetMatrixTranspose( FX_HANDLE Handle, SMatrix4x4 *pMatrix );
		virtual void SetMatrixTransposeArray( FX_HANDLE Handle, SMatrix4x4 *pMatrix, Sint32 Num );
		virtual void SetString( FX_HANDLE Handle, const wchar_t *pStr );
		virtual void SetTexture( FX_HANDLE Handle, ITexture *pTex );
		virtual void SetVector( FX_HANDLE Handle, CVector4D *pVec );
		virtual void SetVectorArray( FX_HANDLE Handle, CVector4D *pVec, Sint32 Num );
	};
}

#endif // ___SELENE__SHADER___

