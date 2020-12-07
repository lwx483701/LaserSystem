#if !defined(AFX_POSITIONERRVALUEVIEW_H__33F15E09_FDCF_44E5_9236_3F321989D173__INCLUDED_)
#define AFX_POSITIONERRVALUEVIEW_H__33F15E09_FDCF_44E5_9236_3F321989D173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PositionErrValueView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPositionErrValueView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ControlTool/SmartEdit/gridctrl.h"

class CPositionErrValueView : public TVisualFormView
{
protected:
	CPositionErrValueView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPositionErrValueView)

// Form Data
public:
	//{{AFX_DATA(CPositionErrValueView)
	enum { IDD = IDD_POSITIONERRVALUEVIEW };
	CComboBox	m_BetFactor;
	CTransParentButton	m_mationpause;
	CTransParentButton	m_btnSet;
	CTransParentButton	m_btnSave;
	CTransParentButton	m_btnReset;
	int		m_mationdelay;
	long	m_mationend;
	long	m_mationstar;
	int		m_chooseXY;
	int		m_MationTime;
	BOOL    m_mationpuls;
	BOOL    m_SysPosition;
	//}}AFX_DATA
	CGridCtrl m_GridErr;

	CGridCtrl m_GridBET;


// Attributes
public:

// Operations
public:
	void FillGridWithText();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPositionErrValueView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPositionErrValueView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPositionErrValueView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSave();
	afx_msg void OnSet();
	afx_msg void OnReset();
	afx_msg void OnMationRun();
	afx_msg void OnMoveStar();
	afx_msg void OnPusl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPusle();
	afx_msg void OnBUTTONpause();
	afx_msg void OnRADIOChooseX();
	afx_msg void OnRADIOChooseY();
//	afx_msg void OnSelchangeBetfactor();
//	afx_msg void OnFitBET();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetUI();//ly add 20110318
	CString GetBETOffsetText(UINT nRow,UINT nCol);
	CString GetCurCellText(UINT nRow, UINT nCol);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSITIONERRVALUEVIEW_H__33F15E09_FDCF_44E5_9236_3F321989D173__INCLUDED_)
