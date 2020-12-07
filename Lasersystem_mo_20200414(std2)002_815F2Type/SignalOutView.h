#if !defined(AFX_SIGNALOUTVIEW_H__B0440CDA_9CDD_4376_8F98_6842EFD517C1__INCLUDED_)
#define AFX_SIGNALOUTVIEW_H__B0440CDA_9CDD_4376_8F98_6842EFD517C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SignalOutView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSignalOutView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "VisualFx.h"
#include "cchecksk.h"
class CSignalOutView : public TVisualFormView
{
protected:
	void SetUI();//ly add 20110318
	CSignalOutView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSignalOutView)

// Form Data
public:
	//{{AFX_DATA(CSignalOutView)
	enum { IDD = IDD_SINGLEOUTPUTVIEW };
	CCheckSK	m_chkOut50;
	CCheckSK	m_chkOut14;
	CCheckSK	m_chkOut13;
	CCheckSK	m_chkOut9;
	CCheckSK	m_chkOut8;
	CCheckSK	m_chkOut7;
	CCheckSK	m_chkOut6;
	CCheckSK	m_chkOut5;
	CCheckSK	m_chkOut4;
	CCheckSK	m_chkOut3;
	CCheckSK	m_chkOut2;
	CCheckSK	m_chkOut1;
	CCheckSK	m_chkOut12;
	CCheckSK	m_chkOut11;
	CCheckSK	m_chkOut10;
	CCheckSK	m_chkOut28;
	CCheckSK	m_chkOut27;
	CCheckSK	m_chkOut26;
	CCheckSK	m_chkOut25;
	CCheckSK	m_chkOut24;
	CCheckSK	m_chkOut23;
	CCheckSK	m_chkOut22;
	CCheckSK	m_chkOut21;
	CCheckSK	m_chkOut20;
	CCheckSK	m_chkOut49;
	CCheckSK	m_chkOut48;
	CCheckSK	m_chkOut47;
	CCheckSK	m_chkOut46;
	CCheckSK	m_chkOut45;
	CCheckSK	m_chkOut44;
	CCheckSK	m_chkOut43;
	CCheckSK	m_chkOut42;
	CCheckSK	m_chkOut41;
	CCheckSK	m_chkOut40;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalOutView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSignalOutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSignalOutView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOutput1Click();
	afx_msg void OnOutput2Click();
	afx_msg void OnOutput3Click();
	afx_msg void OnOutput4Click();
	afx_msg void OnOutput5Click();
	afx_msg void OnOutput6Click();
	afx_msg void OnOutput7Click();
	afx_msg void OnOutput8Click();
	afx_msg void OnOutput9Click();
	afx_msg void OnOutput10Click();
	afx_msg void OnOutput11Click();
	afx_msg void OnOutput12Click();
	afx_msg void OnOutput20Click();
	afx_msg void OnOutput21Click();
	afx_msg void OnOutput24Click();
	afx_msg void OnOutput25Click();
	afx_msg void OnOutput26Click();
	afx_msg void OnOutput27Click();
	afx_msg void OnOutput28Click();
	afx_msg void OnChkOut22();
	afx_msg void OnChkOut23();
	afx_msg void OnChkOut22Click();
	afx_msg void OnChkOut23Click();
	afx_msg void OnChkOut40Click();
	afx_msg void OnChkOut41Click();
	afx_msg void OnChkOut42Click();
	afx_msg void OnChkOut43Click();
	afx_msg void OnChkOut44Click();
	afx_msg void OnChkOut45Click();
	afx_msg void OnChkOut46Click();
	afx_msg void OnChkOut47Click();
	afx_msg void OnChkOut48Click();
	afx_msg void OnChkOut49Click();
	afx_msg void OnChkOut13();
	afx_msg void OnChkOut13Click();
	afx_msg void OnChkOut14Click();
	afx_msg void OnChkOut50();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGNALOUTVIEW_H__B0440CDA_9CDD_4376_8F98_6842EFD517C1__INCLUDED_)
