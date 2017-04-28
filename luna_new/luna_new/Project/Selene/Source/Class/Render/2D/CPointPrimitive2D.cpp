

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Render/CVertexBuffer.h"
#include "Render/2D/CPointPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPointPrimitive2D::CPointPrimitive2D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( L"2Dポイントプリミティブ" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPointPrimitive2D::~CPointPrimitive2D()
{
}

//-----------------------------------------------------------------------------------
/**
	空のラインを生成します。

	@param VertexMax	[in] 最大頂点数

	@return		ラインハンドル
*/
//-----------------------------------------------------------------------------------
Bool CPointPrimitive2D::Create( Uint32 PointMax )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, L"生成" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	Bool bRet = true;

	try
	{
		//--------------------------------------------------------------
		// 頂点バッファ
		//--------------------------------------------------------------
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( PointMax, GetRenderPointer()->GetSize(VERTEX_ELEMENT_PRIMITIVE), true );
		if ( m_pVB_Base == NULL )
		{
			throw L"頂点バッファの生成に失敗";
		}

		//--------------------------------------------------------------
		// 頂点ストリーム
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VERTEX_ELEMENT_PRIMITIVE );
		if ( m_pVS == NULL )
		{
			throw L"頂点ストリームの生成に失敗";
		}

		wchar_t Temp[64] = L"";
		::StringCbPrintf( Temp, sizeof(Temp), L"0x%08X", (Uint64)this );
		Log_PrintLine( 0x0000000, Temp );
	}
	catch ( const wchar_t *pErrMsg )
	{
		Log_PrintStrong( 0xFF0000, pErrMsg );
		bRet = false;
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
	ポリゴンを描画バッファに追加します

	@param lPoint		[in] ラインハンドル
	@param pPoint		[in] ポイントデータ３点で１ポリゴン
	@param Count		[in] ポリゴン数（ポイント数／３）

	@retval true		成功
	@retval false		失敗
*/
//-----------------------------------------------------------------------------------
Bool CPointPrimitive2D::Push( SVertex2D *pPoint, Uint32 Count )
{
	SVertex2D PointTemp;

	//-------------------------------------------------------------------------------------
	// ポリゴン処理
	//-------------------------------------------------------------------------------------
	for ( Uint32 i = 0; i < Count; i++ )
	{
		//--------------------------------------------------
		// 特殊効果
		//--------------------------------------------------
		PointTemp.Pos.x = GetCorePointer()->Virtual2RealX( pPoint[i].Pos.x ) - 0.5f;
		PointTemp.Pos.y = GetCorePointer()->Virtual2RealY( pPoint[i].Pos.y ) - 0.5f;
		PointTemp.Pos.z = pPoint[i].Pos.z;
		PointTemp.Pos.w = pPoint[i].Pos.w;
		PointTemp.Col = pPoint[i].Col;

		//--------------------------------------------------
		// シザリング
		//--------------------------------------------------
		if ( m_IsScissoring )
		{
			if ( PointTemp.Pos.x < m_ScissorX1 ) continue;
			if ( PointTemp.Pos.x > m_ScissorX2 ) continue;
			if ( PointTemp.Pos.y < m_ScissorY1 ) continue;
			if ( PointTemp.Pos.y > m_ScissorY2 ) continue;
		}

		//--------------------------------------------------
		// データコピー
		//--------------------------------------------------
		if ( !m_pVB_Base->Push( &PointTemp, 1 ) )
		{
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファを更新します

	@param lPoint	[in] ラインハンドル
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive2D::Begin( void )
{
	// 各情報初期化
	m_pVB_Base->Flush();
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファを更新します

	@param lPoint	[in] ラインハンドル
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive2D::End( void )
{
	m_pVB_Base->Update();
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファをレンダリングします

	@param lPoint	[in] ラインハンドル
*/
//-----------------------------------------------------------------------------------
void CPointPrimitive2D::Rendering( void )
{
	Uint32 PrimitiveCount = m_pVB_Base->GetCount();

	//-------------------------------------------------------------------------------------
	// レンダリング
	//-------------------------------------------------------------------------------------
	if ( PrimitiveCount > 0 )
	{
		// ステート
		GetRenderPointer()->StatePush();
		GetRenderPointer()->SetTextureOperationType( 1, TEXTURE_OP_NONE );
		GetRenderPointer()->SetTexture( 0, NULL );
		GetRenderPointer()->SetTexture( 1, NULL );

		// 描画
		GetRenderPointer()->SetStream( m_pVS );
		GetRenderPointer()->SetVertex( 0, m_pVB_Base );
		GetRenderPointer()->DrawPrimitive( PRIMITIVE_POINT, PrimitiveCount );

		// ステート
		GetRenderPointer()->StatePop();

		// 描画ポリゴン数追加
		GetCorePointer()->DrawPolygon( PrimitiveCount );
	}
}

