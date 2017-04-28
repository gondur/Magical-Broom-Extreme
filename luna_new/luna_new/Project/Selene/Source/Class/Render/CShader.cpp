

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Render/CShader.h"
#include "Local.h"
#include "File/CFileManager.h"
#include "Surface/CTexture.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
*/
//-----------------------------------------------------------------------------------
CShader::CShader( CBaseMgr *pMgr ) : CDeviceObject( pMgr )
{
	m_pEffect = NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CShader::~CShader()
{
//	Log_PrintTable( 0xFF0000, 0x000000, L"解放", L"シェーダー", m_Name );
//	Log_TableLine( 1 );

	SAFE_RELEASE( m_pEffect );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::OnLostDevice( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->OnLostDevice();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::OnResetDevice( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->OnResetDevice();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CShader::CreateFromFile( const wchar_t *pFileName )
{
	CFileManager *pFileMgr = dynamic_cast<CFileManager*>(GetCorePointer()->GetFileMgrPointer());

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( L"シェーダー" );
	Log_CellBegin( 0 );

	Bool Result = false;

	wchar_t FilePath[MAX_PATH];
	if ( !pFileMgr->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, L"ファイルが見つかりません" );
	}
	else
	{
		void *pData;
		Uint32 Size;

		if ( GetCorePointer()->GetFileMgrPointer()->Load( pFileName, &pData, &Size ) )
		{
			if ( CreateFromMemory( (Uint8*)pData, Size ) )
			{
				Log_PrintLine( 0x000000, FilePath );
				Log_PrintStrongLine( 0x008000, L"完了" );
				SetName( FilePath );
				Result = true;
			}

			GetCorePointer()->GetFileMgrPointer()->Free( pData );
		}
	}

	SetName( pFileName );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return Result;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CShader::CreateFromMemory( const Uint8 *pShader, Uint32 Size )
{
	ID3DXBuffer *pError = NULL;

	// ファイルからエフェクト読み出し
	HRESULT hr = GetDevicePointer()->CreateEffect( pShader, Size, &m_pEffect, &pError );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, L"エフェクトの読み込みに失敗しました。[%s]", GetD3DError( hr ) );
		if ( pError != NULL )
		{
			char *pBuff = (char*)MemLocalAlloc( pError->GetBufferSize() + 1 );
			if ( pBuff != NULL )
			{
				MemoryCopy( pBuff, pError->GetBufferPointer(), pError->GetBufferSize() + 1 );
				Log_PrintStrong( 0xFF0000, L"  -> Shader Compile Error [ %s ]", pBuff );
				MemLocalFree( pBuff );
			}
			SAFE_RELEASE( pError );
		}

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CShader::Begin( Uint32 *pPassMax )
{
	if ( m_pEffect != NULL )
	{
		unsigned int Pass;
		if SUCCEEDED( m_pEffect->Begin( &Pass, 0 ) )
		{
			if ( pPassMax != NULL )
			{
				*pPassMax = Pass;
			}
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::End( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::BeginPass( Uint32 Pass )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->BeginPass( Pass );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::EndPass( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->EndPass();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::UpdateParameter( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->CommitChanges();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
FX_HANDLE CShader::GetParameterByName( const wchar_t *pName )
{
	if ( m_pEffect != NULL )
	{
		char Temp[64] = "";
		WCStoMBCS( pName, Temp );
		return (FX_HANDLE)m_pEffect->GetParameterByName( NULL, Temp );
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
FX_HANDLE CShader::GetParameterBySemantic( const wchar_t *pSemantic )
{
	if ( m_pEffect != NULL )
	{
		char Temp[64] = "";
		WCStoMBCS( pSemantic, Temp );
		return (FX_HANDLE)m_pEffect->GetParameterBySemantic( NULL, Temp );
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
FX_HANDLE CShader::GetTechnique( const wchar_t *pTechnique )
{
	if ( m_pEffect != NULL )
	{
		char Temp[64] = "";
		WCStoMBCS( pTechnique, Temp );
		return (FX_HANDLE)m_pEffect->GetTechniqueByName( Temp );
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetTechnique( FX_HANDLE Handle )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetTechnique( (D3DXHANDLE)Handle );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetFloat( FX_HANDLE Handle, Float Param )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetFloat( (D3DXHANDLE)Handle, Param );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetFloatArray( FX_HANDLE Handle, Float *pParam, Sint32 Num )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetFloatArray( (D3DXHANDLE)Handle, pParam, Num );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetInt( FX_HANDLE Handle, Sint32 Param )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetInt( (D3DXHANDLE)Handle, Param );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetIntArray( FX_HANDLE Handle, Sint32 *pParam, Sint32 Num )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetIntArray( (D3DXHANDLE)Handle, (const int*)pParam, Num );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrix( FX_HANDLE Handle, SMatrix4x4 *pMatrix )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetMatrix( (D3DXHANDLE)Handle, (D3DXMATRIX*)pMatrix );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixArray( FX_HANDLE Handle, SMatrix4x4 *pMatrix, Sint32 Num )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetMatrixArray( (D3DXHANDLE)Handle, (D3DXMATRIX*)pMatrix, Num );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixPointerArray( FX_HANDLE Handle, const SMatrix4x4 **ppMatrix, Sint32 Num )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetMatrixPointerArray( (D3DXHANDLE)Handle, (const D3DXMATRIX**)ppMatrix, Num );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixTranspose( FX_HANDLE Handle, SMatrix4x4 *pMatrix )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetMatrixTranspose( (D3DXHANDLE)Handle, (D3DXMATRIX*)pMatrix );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixTransposeArray( FX_HANDLE Handle, SMatrix4x4 *pMatrix, Sint32 Num )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetMatrixTransposeArray( (D3DXHANDLE)Handle, (D3DXMATRIX*)pMatrix, Num );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetString( FX_HANDLE Handle, const wchar_t *pStr )
{
	if ( m_pEffect != NULL )
	{
		char Temp[64] = "";
		WCStoMBCS( pStr, Temp );
		m_pEffect->SetString( (D3DXHANDLE)Handle, Temp );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetTexture( FX_HANDLE Handle, ITexture *pTex )
{
	if ( m_pEffect != NULL )
	{
		CTexture *pTexData = dynamic_cast<CTexture*>(pTex);
		if ( pTexData == NULL )
		{
			m_pEffect->SetTexture( (D3DXHANDLE)Handle, NULL );
		}
		else
		{
			IDirect3DTexture9 *pTexture;
			pTexData->GetTexture( &pTexture );
			m_pEffect->SetTexture( (D3DXHANDLE)Handle, pTexture );
			SAFE_RELEASE( pTexture );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetVector( FX_HANDLE Handle, CVector4D *pVec )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetVector( (D3DXHANDLE)Handle, (D3DXVECTOR4*)pVec );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetVectorArray( FX_HANDLE Handle, CVector4D *pVec, Sint32 Num )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->SetVectorArray( (D3DXHANDLE)Handle, (D3DXVECTOR4*)pVec, Num );
	}
}

