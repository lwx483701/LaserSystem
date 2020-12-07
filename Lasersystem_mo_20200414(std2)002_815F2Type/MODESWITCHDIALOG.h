#if !defined(AFX_MODESWITCHDIALOG_H__68FEE920_A2E6_4374_942F_366CC98605C4__INCLUDED_)
#define AFX_MODESWITCHDIALOG_H__68FEE920_A2E6_4374_942F_366CC98605C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MODESWITCHDIALOG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MODESWITCHDIALOG dialog

class MODESWITCHDIALOG : public CDialog
{
// Construction
public:
	MODESWITCHDIALOG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MODESWITCHDIALOG)
	enum { IDD = IDD_DLG_MODESWITCHLOGIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CString	m_strPassword;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MODESWITCHDIALOG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MODESWITCHDIALOG)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG

	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODESWITCHDIALOG_H__68FEE920_A2E6_4374_942F_366CC98605C4__INCLUDED_)
