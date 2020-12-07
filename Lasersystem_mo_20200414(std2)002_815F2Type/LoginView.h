#if !defined(AFX_LOGINVIEW_H__F4203745_3277_4C94_96B1_ECD98BCAFE70__INCLUDED_)
#define AFX_LOGINVIEW_H__F4203745_3277_4C94_96B1_ECD98BCAFE70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ControlTool/SmartEdit/gridctrl.h"

class CLoginView : public TVisualFormView
{
protected:
	CLoginView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLoginView)

// Form Data
public:
	//{{AFX_DATA(CLoginView)
	enum { IDD = IDD_LOGINVIEW };
	CStatic	m_stCurUser;
	CEdit	m_edtUserName;
	CEdit	m_edtPasswordC;
	CEdit	m_edtPassword;
	CComboBox	m_cmbUserLevel;
	CString	m_strUserName;
	CString	m_strPasswordC;
	CString	m_strPassword;
	CString	m_CurUser;
	CString m_UserIdCard;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLoginView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLoginView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAddUser();
	afx_msg void OnLogin();
	afx_msg void OnDeleteUserInfo();
	afx_msg void OnModiPassword();
	afx_msg void OnSelchangeComboUserright();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetUI();
	CString GetCurCellText(UINT nRow, UINT nCol);
	void FillGridWithText();

	CGridCtrl m_GridLogin;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINVIEW_H__F4203745_3277_4C94_96B1_ECD98BCAFE70__INCLUDED_)
