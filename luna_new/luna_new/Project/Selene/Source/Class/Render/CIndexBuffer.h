

#ifndef ___SELENE__INDEXBUFFER___
#define ___SELENE__INDEXBUFFER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Object/CDeviceObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief インデックスバッファ管理クラス
		@author 葉迩倭

		インデックスバッファを管理するためのクラスです。<BR>
		Selene内で使用される全インデックスバッファが<BR>
		このクラスを使ってインデックスバッファにアクセスしています。<BR>
	*/
	class CIndexBuffer : public CDeviceObject
	{
	public:
		IDirect3DIndexBuffer9 *m_pBuffer;			///< インデックスバッファ
		Uint16 *m_pIndex;							///< インデックスデータ
		Uint32 m_MaxCount;							///< 最大インデックス数
		Uint32 m_Offset;							///< 使用中にインデックス数
		Uint32 m_RequestedCount;					///< リクエストされた頂点数
		Bool m_IsDynamic;							///< 頻繁に書き換えらるか否か

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		CIndexBuffer( CBaseMgr *pMgr );
		virtual ~CIndexBuffer();

		virtual void Update( void );
		virtual void Flush( void );
		virtual Bool Push( Uint16 *pIdx, Uint32 Count );

		virtual Uint32 GetCount( void ) const;
		virtual Uint32 GetRequestedCount( void ) const;

		virtual Bool Create( Uint32 Count, Bool IsDynamic );
		virtual HRESULT SetDevice( void );
	};
}

#endif // ___SELENE__INDEXBUFFER___


