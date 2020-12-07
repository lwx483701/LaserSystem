#if !defined(AFX_PROCLOGIN_FZ_H__4B72B304_0C2B_4A06_B24E_B734FA4C34D3__INCLUDED_)
#define AFX_PROCLOGIN_FZ_H__4B72B304_0C2B_4A06_B24E_B734FA4C34D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcLogin_FZ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcLogin_FZ dialog

class CProcLogin_FZ : public CDialog
{
// Construction
public:
	CProcLogin_FZ(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcLogin_FZ)
	enum { IDD = IDD_DLG_PROCLOGIN_FZ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcLogin_FZ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcLogin_FZ)
	virtual void OnOK();
	afx_msg void OnBtnFzStartup();
	afx_msg void OnBtnFzVerify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCLOGIN_FZ_H__4B72B304_0C2B_4A06_B24E_B734FA4C34D3__INCLUDED_)
