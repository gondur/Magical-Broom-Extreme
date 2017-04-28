
//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "CAnimation.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimation::CAnimation( Uint32 KeyMax )
{
	// メモリ確保
	m_KeyMax = KeyMax;
	m_pKeys  = new SKeyFrame [ KeyMax ];

	// リストクリア
	for ( Uint32 i = 0; i < KeyMax - 1; i++ )
	{
		m_pKeys[i].pPrev = NULL;
		m_pKeys[i].pNext = NULL;
	}

	// 後にリンクリストを接続
	for ( Uint32 i = 0; i < KeyMax - 1; i++ )
	{
		m_pKeys[i].pNext = &m_pKeys[i+1];
	}

	// 前にリンクリストを接続
	for ( Uint32 i = KeyMax - 1; i >= 1; i-- )
	{
		m_pKeys[i].pPrev = &m_pKeys[i-1];
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimation::~CAnimation()
{
	SAFE_DELETE_ARRAY( m_pKeys );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
SKeyFrame *CAnimation::GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax )
{
	Sint32 Left	= 0;
	Sint32 Right	= KeyMax - 1;

	if ( fTime <= pKeys[Left ].fTime ) return &pKeys[Left ];
	if ( fTime >= pKeys[Right].fTime ) return &pKeys[Right];

	while ( Left <= Right )
	{
		Sint32 Middle = Left + (Right - Left) / 2;

		if ( fTime < pKeys[Middle+0].fTime )
		{
			Right = Middle - 1;
		}
		ef ( fTime > pKeys[Middle+1].fTime )
		{
			Left = Middle + 1;
		}
		else
		{
			return &pKeys[Middle];
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CAnimation::SetKey( Uint32 KeyNo, Float fTime, Float fParam, Bool IsIn, Bool IsOut, Float fIn, Float fOut )
{
	if ( KeyNo < m_KeyMax )
	{
		// キー設定
		m_pKeys[KeyNo].fTime  = fTime;
		m_pKeys[KeyNo].fParam = fParam;
		m_pKeys[KeyNo].IsIn   = IsIn;
		m_pKeys[KeyNo].IsOut  = IsOut;
		m_pKeys[KeyNo].fIn    = fIn;
		m_pKeys[KeyNo].fOut   = fOut;

		// 開始－終了時間
		m_fTimeFirst = m_pKeys[0].fTime;
		m_fTimeLast  = m_pKeys[m_KeyMax-1].fTime;

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimation::Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 )
{
   Float fTime2 = fTime * fTime;
   Float fTime3 = fTime * fTime2;

   *pH2 = (3.0f * fTime2) - fTime3 - fTime3;
   *pH1 = 1.0f - *pH2;
   *pH4 = fTime3 - fTime2;
   *pH3 = *pH4 - fTime2 + fTime;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CAnimation::InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 )
{
	Float fParam = pKey1->fParam - pKey0->fParam;

	if ( pKey1->pNext != NULL )
	{
		Float fTime = (pKey1->fTime - pKey0->fTime) / (pKey1->pNext->fTime - pKey0->fTime);
		return (fTime * ((pKey1->pNext->fParam - pKey1->fParam) + fParam));
	}
	else
	{
		return fParam;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CAnimation::OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 )
{
	Float fParam = pKey1->fParam - pKey0->fParam;

	if ( pKey0->pPrev != NULL )
	{
		Float fTime = (pKey1->fTime - pKey0->fTime) / (pKey1->fTime - pKey0->pPrev->fTime);
		return (fTime * ((pKey0->fParam - pKey0->pPrev->fParam) + fParam));
	}
	else
	{
		return fParam;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CAnimation::GetParameter( Float fTime, eAnimationType Type, Float fDefault )
{
	//--------------------------------------------------
	// 時間はクランプ処理
	//--------------------------------------------------
	if ( fTime < 0.0f )
	{
		fTime = 0.0f;
	}
	ef ( fTime > m_fTimeLast )
	{
		fTime = m_fTimeLast;
	}

	//--------------------------------------------------
	// 指定時間のキー取得
	//--------------------------------------------------
	SKeyFrame *pKey0 = GetKeyData( m_pKeys, fTime, m_KeyMax );
	SKeyFrame *pKey1 = pKey0->pNext;

	if ( pKey1 == NULL ) return pKey0->fParam;

	//--------------------------------------------------
	// 補間割合取得
	//--------------------------------------------------
	Float fLerpValue = 0;
	if ( pKey0->fParam != pKey1->fParam )
	{
		fLerpValue = (fTime - pKey0->fTime) / (pKey1->fTime - pKey0->fTime);
	}

	//--------------------------------------------------
	// キー補間
	//--------------------------------------------------
	switch ( Type )
	{
	// Step
	case ANIM_TYPE_STEP:
		{
			return pKey0->fParam;
		}
		break;
	// Linear
	case ANIM_TYPE_LINEAR:
		{
			return (pKey0->fParam + ((pKey1->fParam - pKey0->fParam) * fLerpValue));
		}
		break;
	// TCB (Kochanek-Bartels) 
	case ANIM_TYPE_TCB:
		{
			Float fIn, fOut;
			Float h1, h2, h3, h4;

			// ポイント算出
			fOut = pKey0->IsOut ? pKey0->fOut : OutGoing( pKey0, pKey1 );
			fIn  = pKey1->IsIn  ? pKey1->fIn  : InComing( pKey0, pKey1 );

			// エルミート
			Hermite( fLerpValue, &h1, &h2, &h3, &h4 );

			return ((h1 * pKey0->fParam) + (h2 * pKey1->fParam) + (h3 * fOut) + (h4 * fIn));
		}
		break;
	}

	return fDefault;
}

