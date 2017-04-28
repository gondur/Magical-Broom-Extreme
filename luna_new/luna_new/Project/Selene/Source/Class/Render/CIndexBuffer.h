

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
		@brief �C���f�b�N�X�o�b�t�@�Ǘ��N���X
		@author �t���`

		�C���f�b�N�X�o�b�t�@���Ǘ����邽�߂̃N���X�ł��B<BR>
		Selene���Ŏg�p�����S�C���f�b�N�X�o�b�t�@��<BR>
		���̃N���X���g���ăC���f�b�N�X�o�b�t�@�ɃA�N�Z�X���Ă��܂��B<BR>
	*/
	class CIndexBuffer : public CDeviceObject
	{
	public:
		IDirect3DIndexBuffer9 *m_pBuffer;			///< �C���f�b�N�X�o�b�t�@
		Uint16 *m_pIndex;							///< �C���f�b�N�X�f�[�^
		Uint32 m_MaxCount;							///< �ő�C���f�b�N�X��
		Uint32 m_Offset;							///< �g�p���ɃC���f�b�N�X��
		Uint32 m_RequestedCount;					///< ���N�G�X�g���ꂽ���_��
		Bool m_IsDynamic;							///< �p�ɂɏ���������邩�ۂ�

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


