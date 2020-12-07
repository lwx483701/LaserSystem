#if !defined(AFX_MOTIONPARAMETERVIEW_H__C6C48655_7DF5_45E0_A66B_F0B6BEF42F74__INCLUDED_)
#define AFX_MOTIONPARAMETERVIEW_H__C6C48655_7DF5_45E0_A66B_F0B6BEF42F74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotionParameterView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotionParameterView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "stdafx.h"
#include "ControlTool/SmartEdit/gridctrl.h"

class CMotionParameterView : public TVisualFormView
{
protected:
	CMotionParameterView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMotionParameterView)

// Form Data
public:
	//{{AFX_DATA(CMotionParameterView)
	enum { IDD = IDD_MOTIONPARAMETER };
	CTransParentButton	m_btnSet;
	CTransParentButton	m_btnSave;
	CTransParentButton	m_btnReset;
	//}}AFX_DATA
	CGridCtrl m_Grid;
	CSize m_OldSize;

// Attributes
public:

// Operations
public:
	void FillGridWithText();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionParameterView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMotionParameterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMotionParameterView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetParam();
	afx_msg void OnResetParam();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetUI();
	UINT GetAxisEncode(int nIndex) const;
	CString GetCurCellText(UINT nRow,UINT nCol);

	BOOL m_SysMotion;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONPARAMETERVIEW_H__C6C48655_7DF5_45E0_A66B_F0B6BEF42F74__INCLUDED_)
