#if !defined(AFX_DLGROTATE_H__D0A8F8EB_280A_4DFE_B265_A3F89D4F63F4__INCLUDED_)
#define AFX_DLGROTATE_H__D0A8F8EB_280A_4DFE_B265_A3F89D4F63F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRotate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRotate dialog

class CDlgRotate : public CDialog
{
// Construction
public:
	CDlgRotate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRotate)
	enum { IDD = IDD_DLG_ROTATE };
	int		m_Rotate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRotate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRotate)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnRotate90();
	afx_msg void OnRotate180();
	afx_msg void OnRotate270();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROTATE_H__D0A8F8EB_280A_4DFE_B265_A3F89D4F63F4__INCLUDED_)
