#if !defined(AFX_SCALESETDLGVIEW_H__D4428B39_250C_465E_AB35_2B5ACABC48BB__INCLUDED_)
#define AFX_SCALESETDLGVIEW_H__D4428B39_250C_465E_AB35_2B5ACABC48BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScaleSetDlgView.h : header file
//
#include "ControlTool/SmartEdit/gridctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CScaleSetDlgView dialog

class CScaleSetDlgView : public CDialog
{
// Construction
public:
	void FillGridWithText();
	CScaleSetDlgView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScaleSetDlgView)
	enum { IDD = IDD_DLG_SCALESET };
	double	m_dbDownLimit;
	double	m_dbUpLimit;
	CString	m_strChar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleSetDlgView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScaleSetDlgView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnScaleSetAdd();
	afx_msg void OnScaleSetDelete();
	afx_msg void OnScaleSetModify();
	afx_msg void OnScaleSetSet();
	afx_msg void OnScaleSetSave();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool m_ScaleSetSaved;
	CGridCtrl m_GridScaleSet;
	CString GetCurCellText(UINT nRow, UINT nCol);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCALESETDLGVIEW_H__D4428B39_250C_465E_AB35_2B5ACABC48BB__INCLUDED_)
