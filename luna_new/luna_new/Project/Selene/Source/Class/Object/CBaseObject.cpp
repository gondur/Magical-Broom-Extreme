

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Object/CBaseObject.h"

using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
*/
//-----------------------------------------------------------------------------------
CBaseObject::CBaseObject()
{
	m_RefCount		= 1;
	m_ChildCount	= 0;
	m_pPrev			= NULL;
	m_pNext			= NULL;
	m_pParent		= NULL;
	m_pChild		= NULL;
	m_pSibling		= NULL;
	m_Name[0]		= L'\0';
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
*/
//-----------------------------------------------------------------------------------
CBaseObject::~CBaseObject()
{
	// 自分が誰かの子供の時はリストから切り離す
	if ( m_pParent != NULL )
	{
		// 親の子供の数をデクリメント
		m_pParent->m_ChildCount--;

		// 親の直下の時
		if ( m_pParent->m_pChild == this )
		{
			// 後ろへ連結
			m_pParent->m_pChild = m_pSibling;
		}
		else
		{
			// リストから自分を検索
			CBaseObject *pObj = m_pParent->m_pChild;
			while ( pObj->m_pSibling != this )
			{
				pObj = pObj->m_pSibling;
			}

			// 後ろへ連結
			pObj->m_pSibling = m_pSibling;
		}

		// 親への参照を破棄
		SAFE_RELEASE( m_pParent );
	}

	// 子供削除
	CBaseObject *pChild = m_pChild;
	while ( pChild != NULL )
	{
		pChild->m_pParent = NULL;
		pChild = pChild->m_pSibling;
	}

	m_ChildCount	= 0;
	m_pPrev			= NULL;
	m_pNext			= NULL;
	m_pParent		= NULL;
	m_pChild		= NULL;
	m_pSibling		= NULL;
}


//-----------------------------------------------------------------------------------
/**
	@brief 参照カウンタインクリメント

	参照カウンタのインクリメントを行います。
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::AddRef( void )
{
	m_RefCount++;
	return m_RefCount;
}


//-----------------------------------------------------------------------------------
/**
	@brief 参照カウンタ取得

	参照カウンタのカウント数を取得します。
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::GetRefCount( void )
{
	return m_RefCount;
}


//-----------------------------------------------------------------------------------
/**
	@brief 参照カウンタデクリメント

	参照カウンタのデクリメントを行います。<BR>
	参照カウンタが０になった時点でメモリから削除されます。<BR>
	子供が居る状態での削除はリストの状態は保障されません。

	@return 参照カウンタ値
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::Release( void )
{
	Uint32 Cnt = --m_RefCount;
	if ( Cnt == 0 )
	{
		delete this;
	}

	return Cnt;
}


//-----------------------------------------------------------------------------------
/**
	@brief 子供の数を取得

	自分にぶら下がっている子供の数を取得します。

	@return 子供の数
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::GetChildCount( void )
{
	return m_ChildCount;
}


//-----------------------------------------------------------------------------------
/**
	@brief 連結リストの前のオブジェクトの取得

	連結リスト上で自分の前のオブジェクトを取得します。

	@return 前のオブジェクトのポインタ
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetPrev( void )
{
	return m_pPrev;
}


//-----------------------------------------------------------------------------------
/**
	@brief 連結リストの次のオブジェクトの取得

	連結リスト上で自分の次のオブジェクトを取得します。

	@return 次のオブジェクトのポインタ
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetNext( void )
{
	return m_pNext;
}


//-----------------------------------------------------------------------------------
/**
	@brief 親オブジェクトの取得

	自分の親のオブジェクトを取得します。

	@return 親オブジェクトのポインタ
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetParent( void )
{
	return m_pParent;
}


//-----------------------------------------------------------------------------------
/**
	@brief 親オブジェクトの取得

	自分の親のオブジェクトを取得します。

	@return 親オブジェクトのポインタ
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetChild( void )
{
	return m_pChild;
}


//-----------------------------------------------------------------------------------
/**
	@brief 兄弟オブジェクトの取得

	自分の兄弟のオブジェクトを取得します。

	@return 子供オブジェクトのポインタ
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetSibling( void )
{
	return m_pSibling;
}


//-----------------------------------------------------------------------------------
/**
	@brief 子供オブジェクトの登録

	自分の子供としてオブジェクトの登録を行います。

	@param pChild	[in] 子供データのポインタ
*/
//-----------------------------------------------------------------------------------
void CBaseObject::AddChild( CBaseObject *pChild )
{
	// 子供の数をインクリメント
	m_ChildCount++;

	// 子供がいない時
	if ( m_pChild == NULL )
	{
		m_pChild = pChild;
	}
	else
	{
		// 子供の連結リストに追加
		CBaseObject *pObj = m_pChild;
		while ( pObj->m_pSibling != NULL )
		{
			pObj = pObj->m_pSibling;
		}

		pObj->m_pSibling = pChild;
	}

	pChild->m_pParent = this;
	AddRef();
}


//-----------------------------------------------------------------------------------
/**
	@brief オブジェクト名設定

	オブジェクトの名前を設定します。

	@param pName	[out] 名前格納元ポインタ
*/
//-----------------------------------------------------------------------------------
void CBaseObject::SetName( const wchar_t *pName )
{
	::StringCbCopy( m_Name, sizeof(m_Name), pName );
}


//-----------------------------------------------------------------------------------
/**
	@brief オブジェクト名取得

	オブジェクトの名前を取得します。

	@param pName	[out] 名前格納先ポインタ
*/
//-----------------------------------------------------------------------------------
void CBaseObject::GetName( wchar_t *pName, Uint32 NameSize )
{
	::StringCbCopy( pName, NameSize, m_Name );
}


//-----------------------------------------------------------------------------------
/**
	@brief オブジェクト名取得

	オブジェクトの名前を取得します。

	@return		名前格納元ポインタ
*/
//-----------------------------------------------------------------------------------
const wchar_t *CBaseObject::GetNamePointer( void ) const
{
	return m_Name;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CBaseObject::IsSame( const wchar_t *pName )
{
	return ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, m_Name, -1, pName, -1 ) == CSTR_EQUAL;
}


