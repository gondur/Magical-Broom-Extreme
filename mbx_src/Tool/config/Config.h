// Config.h : CONFIG �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_CONFIG_H__18BBEEB7_6E30_4FFE_97A2_50BFE49B799C__INCLUDED_)
#define AFX_CONFIG_H__18BBEEB7_6E30_4FFE_97A2_50BFE49B799C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CConfigApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� Config.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CConfigApp : public CWinApp
{
public:
	CConfigApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CConfigApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CConfigApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CONFIG_H__18BBEEB7_6E30_4FFE_97A2_50BFE49B799C__INCLUDED_)
