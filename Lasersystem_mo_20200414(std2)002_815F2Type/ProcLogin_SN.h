#if !defined(AFX_PROCLOGIN_SN_H__0DE48DC1_2A33_489E_93E8_EE7484D5E3D4__INCLUDED_)
#define AFX_PROCLOGIN_SN_H__0DE48DC1_2A33_489E_93E8_EE7484D5E3D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcLogin_SN.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcLogin_SN dialog

class CProcLogin_SN : public CDialog
{
// Construction
public:
	CProcLogin_SN(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcLogin_SN)
	enum { IDD = IDD_DLG_PROCLOGIN_SN };
	CString	m_strAmployeeID_SN;
	CString	m_strLOTID_SN;
	CString	m_strPRODID_SN;
	CString	m_strDEPTID_SN;
	CString	m_strProgram_SN;
	UINT	m_nPCBCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcLogin_SN)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcLogin_SN)
	afx_msg void OnSave();
	afx_msg void OnSNOpenFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCLOGIN_SN_H__0DE48DC1_2A33_489E_93E8_EE7484D5E3D4__INCLUDED_)
