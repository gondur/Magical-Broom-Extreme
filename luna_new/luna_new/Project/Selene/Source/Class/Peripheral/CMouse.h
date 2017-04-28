

#ifndef ___SELENE__CMOUSE___
#define ___SELENE__CMOUSE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Object/CBaseObject.h"
#include "Interface/Peripheral/IMouse.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CInput;

	/**
		@brief �}�E�X�Ǘ��N���X
		@author �t���`
	*/
	class CMouse : public CBaseObject, public IMouse
	{
		friend class CInput;

	protected:
		HWND			m_hWindow;			///< �E�B���h�E�n���h��

		Sint32			m_PosX;				///< �w�ʒu
		Sint32			m_PosY;				///< �x�ʒu
		Sint32			m_PosW;				///< �y�ʒu

		Sint32			m_MoveX;			///< �w�ړ���
		Sint32			m_MoveY;			///< �x�ړ���

		eMouseState		m_StateL;			///< ���{�^�����
		eMouseState		m_StateR;			///< �E�{�^�����
		eMouseState		m_StateW;			///< �z�C�[���{�^�����

		Bool			m_ClickL;			///< ���N���b�N
		Bool			m_ClickR;			///< �E�N���b�N
		Bool			m_ClickW;			///< �z�C�[���N���b�N

		Bool			m_DoubleClickL;		///< �E�_�u���N���b�N
		Bool			m_DoubleClickR;		///< ���_�u���N���b�N
		Bool			m_DoubleClickW;		///< �z�C�[���_�u���N���b�N

	protected:
		CMouse( HWND hWnd );
		virtual ~CMouse();

	protected:
		virtual void Refresh( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Uint32 Release( void ) { return CBaseObject::Release(); }
		virtual Uint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void SetCursorPos( POINT Pt );
		virtual void SetMouseWheel( Sint16 w );
		virtual void SetDoubleClickL( void );
		virtual void SetDoubleClickR( void );
		virtual void SetDoubleClickM( void );

		virtual Sint32 GetPosX( void ) const { return m_PosX; }
		virtual Sint32 GetPosY( void ) const { return m_PosY; }
		virtual Sint32 GetPosW( void ) const { return m_PosW; }

		virtual Sint32 GetMoveX( void ) const { return m_MoveX; }
		virtual Sint32 GetMoveY( void ) const { return m_MoveY; }

		virtual Bool GetClickL( void ) const { return m_ClickL; }
		virtual Bool GetClickR( void ) const { return m_ClickR; }
		virtual Bool GetClickW( void ) const { return m_ClickW; }

		virtual Bool GetDoubleClickL( void ) const { return m_DoubleClickL; }
		virtual Bool GetDoubleClickR( void ) const { return m_DoubleClickR; }
		virtual Bool GetDoubleClickW( void ) const { return m_DoubleClickW; }

		virtual eMouseState GetStateL( void ) const { return m_StateL; }
		virtual eMouseState	GetStateR( void ) const { return m_StateR; }
		virtual eMouseState	GetStateW( void ) const { return m_StateW; }
	};
}

#endif // ___SELENE__CMOUSE___

