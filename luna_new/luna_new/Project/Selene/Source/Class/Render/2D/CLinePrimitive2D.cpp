

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Local.h"
#include "Core/CDevice.h"
#include "Core/CCore.h"
#include "Render/CVertexBuffer.h"
#include "Render/2D/CLinePrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLinePrimitive2D::CLinePrimitive2D( CRender *pRender, CBaseMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( L"2Dラインプリミティブ" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLinePrimitive2D::~CLinePrimitive2D()
{
}

//-----------------------------------------------------------------------------------
/**
	空のラインを生成します。

	@param VertexMax	[in] 最大頂点数

	@return		ラインハンドル
*/
//-----------------------------------------------------------------------------------
Bool CLinePrimitive2D::Create( Uint32 LineMax )
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
		m_pVB_Base = GetRenderPointer()->CreateVertexBuffer( LineMax, GetRenderPointer()->GetSize(VERTEX_ELEMENT_PRIMITIVE), true );
		if ( m_pVB_Base == NULL )
		{
			throw L"頂点バッファの生成に失敗";
		}

		//--------------------------------------------------------------
		// 頂点ストリーム
		//--------------------------------------------------------------
		m_pVS = GetRenderPointer()->CreateVertexStream( VERTEX_ELEMENT_PRIMITIVE);
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

	@param lLine		[in] ラインハンドル
	@param pPoint		[in] ポイントデータ３点で１ポリゴン
	@param Count		[in] ポリゴン数（ポイント数／３）

	@retval true		成功
	@retval false		失敗
*/
//-----------------------------------------------------------------------------------
Bool CLinePrimitive2D::Push( SLineVertex2D *pLine, Uint32 Count )
{
	static SVertex2D ScissorPoint[2];
	static SLineVertex2D LineTemp;

	//-------------------------------------------------------------------------------------
	// ポリゴン処理
	//-------------------------------------------------------------------------------------
	for ( Uint32 i = 0; i < Count; i++ )
	{
		//--------------------------------------------------
		// 特殊効果
		//--------------------------------------------------
		LineTemp.v1.Pos.x = GetCorePointer()->Virtual2RealX( pLine[i].v1.Pos.x ) - 0.5f;
		LineTemp.v1.Pos.y = GetCorePointer()->Virtual2RealY( pLine[i].v1.Pos.y ) - 0.5f;
		LineTemp.v2.Pos.x = GetCorePointer()->Virtual2RealX( pLine[i].v2.Pos.x ) - 0.5f;
		LineTemp.v2.Pos.y = GetCorePointer()->Virtual2RealY( pLine[i].v2.Pos.y ) - 0.5f;
	
		LineTemp.v1.Pos.z = pLine[i].v1.Pos.z;
		LineTemp.v1.Pos.w = pLine[i].v1.Pos.w;
		LineTemp.v1.Col = pLine[i].v1.Col;

		LineTemp.v2.Pos.z = pLine[i].v2.Pos.z;
		LineTemp.v2.Pos.w = pLine[i].v2.Pos.w;
		LineTemp.v2.Col = pLine[i].v2.Col;

		//--------------------------------------------------
		// シザリング
		//--------------------------------------------------
		Uint32 AddVertexCount = ScissorPolygon( ScissorPoint, (SVertex2D*)&LineTemp );
		if ( AddVertexCount == 0 ) continue;

		//--------------------------------------------------
		// データコピー
		//--------------------------------------------------
		m_pVB_Base->Push( ScissorPoint, AddVertexCount );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファを更新します

	@param lLine	[in] ラインハンドル
*/
//-----------------------------------------------------------------------------------
void CLinePrimitive2D::Begin( void )
{
	// 各情報初期化
	m_pVB_Base->Flush();
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファを更新します

	@param lLine	[in] ラインハンドル
*/
//-----------------------------------------------------------------------------------
void CLinePrimitive2D::End( void )
{
	m_pVB_Base->Update();
}

//-----------------------------------------------------------------------------------
/**
	描画用頂点バッファをレンダリングします

	@param lLine	[in] ラインハンドル
*/
//-----------------------------------------------------------------------------------
void CLinePrimitive2D::Rendering( void )
{
	Uint32 PrimitiveCount = m_pVB_Base->GetCount() / LINE_POINT_COUNT;

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
		GetRenderPointer()->DrawPrimitive( PRIMITIVE_LINE, PrimitiveCount );

		// ステート
		GetRenderPointer()->StatePop();

		// 描画ポリゴン数追加
		GetCorePointer()->DrawPolygon( PrimitiveCount );
	}
}

//-----------------------------------------------------------------------------------
/**
	ポリゴンをシザリングします

	@param pDst		[out] 出力ポイントアドレス
	@param pSrc		[in] 入力ポイントアドレス
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygon( SVertex2D *pDst, SVertex2D *pSrc )
{
	if ( m_IsScissoring )
	{
		if ( (pSrc[0].Pos.x < m_ScissorX1) && (pSrc[1].Pos.x < m_ScissorX1) && (pSrc[2].Pos.x < m_ScissorX1) ) return 0;
		if ( (pSrc[0].Pos.x > m_ScissorX2) && (pSrc[1].Pos.x > m_ScissorX2) && (pSrc[2].Pos.x > m_ScissorX2) ) return 0;
		if ( (pSrc[0].Pos.y < m_ScissorY1) && (pSrc[1].Pos.y < m_ScissorY1) && (pSrc[2].Pos.y < m_ScissorY1) ) return 0;
		if ( (pSrc[0].Pos.y > m_ScissorY2) && (pSrc[1].Pos.y > m_ScissorY2) && (pSrc[2].Pos.y > m_ScissorY2) ) return 0;

		static SVertex2D VxResult[4][16];
		Uint32 VertexCount = LINE_POINT_COUNT;
		Uint32 VertexNum = 0;

		// 左
		VertexCount = ScissorPolygonLeft( pSrc, VxResult[0], VertexCount );

		// 右
		VertexCount = ScissorPolygonRight( VxResult[0], VxResult[1], VertexCount );

		// 上
		VertexCount = ScissorPolygonTop( VxResult[1], VxResult[2], VertexCount );

		// 下
		VertexCount = ScissorPolygonBottom( VxResult[2], VxResult[3], VertexCount );

		if ( VertexCount == 0 ) return 0;

		// リストに展開
		pDst[VertexNum++] = VxResult[3][0];
		pDst[VertexNum++] = VxResult[3][1];

		return VertexNum;
	}
	else
	{
		for ( Sint32 i = 0; i < LINE_POINT_COUNT; i++ )
		{
			pDst[i] = pSrc[i];
		}

		return 2;
	}
}

//-----------------------------------------------------------------------------------
/**
	左側のシザリングをします

	@param pPtIn	[in] 入力ポイントアドレス
	@param pPtOut	[out] 出力ポイントアドレス
	@param VxNum	[in] 頂点数

	@return		シザリング後の頂点数
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonLeft( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// クリッピング
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.x < m_ScissorX1);
	}

	//--------------------------------------------------------
	// シザリング
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// 次の頂点をクリップ
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
	右側のシザリングをします

	@param pPtIn	[in] 入力ポイントアドレス
	@param pPtOut	[out] 出力ポイントアドレス
	@param VxNum	[in] 頂点数

	@return		シザリング後の頂点数
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonRight( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// クリッピング
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.x > m_ScissorX2);
	}

	//--------------------------------------------------------
	// シザリング
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// 次の頂点をクリップ
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
	上側のシザリングをします

	@param pPtIn	[in] 入力ポイントアドレス
	@param pPtOut	[out] 出力ポイントアドレス
	@param VxNum	[in] 頂点数

	@return		シザリング後の頂点数
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonTop( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// クリッピング
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.y < m_ScissorY1);
	}

	//--------------------------------------------------------
	// シザリング
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// 次の頂点をクリップ
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
	下側のシザリングをします

	@param pPtIn	[in] 入力ポイントアドレス
	@param pPtOut	[out] 出力ポイントアドレス
	@param VxNum	[in] 頂点数

	@return		シザリング後の頂点数
*/
//-----------------------------------------------------------------------------------
Uint32 CLinePrimitive2D::ScissorPolygonBottom( SVertex2D *pPtIn, SVertex2D *pPtOut, Uint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

	//--------------------------------------------------------
	// クリッピング
	//--------------------------------------------------------
	for ( Uint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.y > m_ScissorY2);
	}

	//--------------------------------------------------------
	// シザリング
	//--------------------------------------------------------
	if ( IsClip[0] && IsClip[1] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// 次の頂点をクリップ
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// 次の頂点をクリップ
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// 位置割合
		Ave = (m_ScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// 頂点追加
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

