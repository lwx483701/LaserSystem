#if !defined(AFX_FUNCTIONTESTVIEW_H__D8FBC08A_B816_4ADA_864E_239A7FE61307__INCLUDED_)
#define AFX_FUNCTIONTESTVIEW_H__D8FBC08A_B816_4ADA_864E_239A7FE61307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FunctionTestView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFunctionTestView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "stdafx.h"
class CFunctionTestView : public TVisualFormView
{
protected:
	CFunctionTestView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFunctionTestView)

// Form Data
public:
	//{{AFX_DATA(CFunctionTestView)
	enum { IDD = IDD_FUNCTIONTESTVIEW };
	CTransParentButton	m_btnDrillMatrix;
	CTransParentButton	m_btnLaserPowerTest;
	CTransParentButton	m_btnLaserWarmUp;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFunctionTestView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFunctionTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFunctionTestView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUNCTIONTESTVIEW_H__D8FBC08A_B816_4ADA_864E_239A7FE61307__INCLUDED_)
