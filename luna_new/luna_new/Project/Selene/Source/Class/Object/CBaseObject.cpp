

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH

#include "Object/CBaseObject.h"

using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief �R���X�g���N�^
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
	@brief �f�X�g���N�^
*/
//-----------------------------------------------------------------------------------
CBaseObject::~CBaseObject()
{
	// �������N���̎q���̎��̓��X�g����؂藣��
	if ( m_pParent != NULL )
	{
		// �e�̎q���̐����f�N�������g
		m_pParent->m_ChildCount--;

		// �e�̒����̎�
		if ( m_pParent->m_pChild == this )
		{
			// ���֘A��
			m_pParent->m_pChild = m_pSibling;
		}
		else
		{
			// ���X�g���玩��������
			CBaseObject *pObj = m_pParent->m_pChild;
			while ( pObj->m_pSibling != this )
			{
				pObj = pObj->m_pSibling;
			}

			// ���֘A��
			pObj->m_pSibling = m_pSibling;
		}

		// �e�ւ̎Q�Ƃ�j��
		SAFE_RELEASE( m_pParent );
	}

	// �q���폜
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
	@brief �Q�ƃJ�E���^�C���N�������g

	�Q�ƃJ�E���^�̃C���N�������g���s���܂��B
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::AddRef( void )
{
	m_RefCount++;
	return m_RefCount;
}


//-----------------------------------------------------------------------------------
/**
	@brief �Q�ƃJ�E���^�擾

	�Q�ƃJ�E���^�̃J�E���g�����擾���܂��B
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::GetRefCount( void )
{
	return m_RefCount;
}


//-----------------------------------------------------------------------------------
/**
	@brief �Q�ƃJ�E���^�f�N�������g

	�Q�ƃJ�E���^�̃f�N�������g���s���܂��B<BR>
	�Q�ƃJ�E���^���O�ɂȂ������_�Ń���������폜����܂��B<BR>
	�q���������Ԃł̍폜�̓��X�g�̏�Ԃ͕ۏႳ��܂���B

	@return �Q�ƃJ�E���^�l
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
	@brief �q���̐����擾

	�����ɂԂ牺�����Ă���q���̐����擾���܂��B

	@return �q���̐�
*/
//-----------------------------------------------------------------------------------
Uint32 CBaseObject::GetChildCount( void )
{
	return m_ChildCount;
}


//-----------------------------------------------------------------------------------
/**
	@brief �A�����X�g�̑O�̃I�u�W�F�N�g�̎擾

	�A�����X�g��Ŏ����̑O�̃I�u�W�F�N�g���擾���܂��B

	@return �O�̃I�u�W�F�N�g�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetPrev( void )
{
	return m_pPrev;
}


//-----------------------------------------------------------------------------------
/**
	@brief �A�����X�g�̎��̃I�u�W�F�N�g�̎擾

	�A�����X�g��Ŏ����̎��̃I�u�W�F�N�g���擾���܂��B

	@return ���̃I�u�W�F�N�g�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetNext( void )
{
	return m_pNext;
}


//-----------------------------------------------------------------------------------
/**
	@brief �e�I�u�W�F�N�g�̎擾

	�����̐e�̃I�u�W�F�N�g���擾���܂��B

	@return �e�I�u�W�F�N�g�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetParent( void )
{
	return m_pParent;
}


//-----------------------------------------------------------------------------------
/**
	@brief �e�I�u�W�F�N�g�̎擾

	�����̐e�̃I�u�W�F�N�g���擾���܂��B

	@return �e�I�u�W�F�N�g�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetChild( void )
{
	return m_pChild;
}


//-----------------------------------------------------------------------------------
/**
	@brief �Z��I�u�W�F�N�g�̎擾

	�����̌Z��̃I�u�W�F�N�g���擾���܂��B

	@return �q���I�u�W�F�N�g�̃|�C���^
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseObject::GetSibling( void )
{
	return m_pSibling;
}


//-----------------------------------------------------------------------------------
/**
	@brief �q���I�u�W�F�N�g�̓o�^

	�����̎q���Ƃ��ăI�u�W�F�N�g�̓o�^���s���܂��B

	@param pChild	[in] �q���f�[�^�̃|�C���^
*/
//-----------------------------------------------------------------------------------
void CBaseObject::AddChild( CBaseObject *pChild )
{
	// �q���̐����C���N�������g
	m_ChildCount++;

	// �q�������Ȃ���
	if ( m_pChild == NULL )
	{
		m_pChild = pChild;
	}
	else
	{
		// �q���̘A�����X�g�ɒǉ�
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
	@brief �I�u�W�F�N�g���ݒ�

	�I�u�W�F�N�g�̖��O��ݒ肵�܂��B

	@param pName	[out] ���O�i�[���|�C���^
*/
//-----------------------------------------------------------------------------------
void CBaseObject::SetName( const wchar_t *pName )
{
	::StringCbCopy( m_Name, sizeof(m_Name), pName );
}


//-----------------------------------------------------------------------------------
/**
	@brief �I�u�W�F�N�g���擾

	�I�u�W�F�N�g�̖��O���擾���܂��B

	@param pName	[out] ���O�i�[��|�C���^
*/
//-----------------------------------------------------------------------------------
void CBaseObject::GetName( wchar_t *pName, Uint32 NameSize )
{
	::StringCbCopy( pName, NameSize, m_Name );
}


//-----------------------------------------------------------------------------------
/**
	@brief �I�u�W�F�N�g���擾

	�I�u�W�F�N�g�̖��O���擾���܂��B

	@return		���O�i�[���|�C���^
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


