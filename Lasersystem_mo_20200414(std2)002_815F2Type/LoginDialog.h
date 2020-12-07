#if !defined(AFX_LOGINDIALOG_H__4DBE1704_EB19_4B6D_B333_81E018642B21__INCLUDED_)
#define AFX_LOGINDIALOG_H__4DBE1704_EB19_4B6D_B333_81E018642B21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

class CLoginDialog : public CDialog
{
// Construction
public:
	CLoginDialog(CWnd* pParent = NULL);   // standard constructor
	enum USER{ALLUSER,SUPERORUSER,ADMINUSER};//所有用户，高级用户，系统用户

// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = IDD_DLG_LOGIN };
	CComboBox	m_cmbUserRight;
	CComboBox	m_cmbUserName;
	CButton	m_btnOK;
	CString	m_strPassword;
	CString m_strUserCard;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	bool UserVerify(CString &userId);
protected:

	void SetUI();//ly add 20120210
	void AddUserByLevel(int level);
	// Generated message map functions
	//{{AFX_MSG(CLoginDialog)
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboUserright();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDIALOG_H__4DBE1704_EB19_4B6D_B333_81E018642B21__INCLUDED_)
