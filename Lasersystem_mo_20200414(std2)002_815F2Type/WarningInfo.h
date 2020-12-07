// WarningInfo.h : header file
//
#if !defined(AFX_WARNINGINFO_H__28A459B4_CF3E_4363_9C30_535AF4C9406C__INCLUDED_)
#define AFX_WARNINGINFO_H__28A459B4_CF3E_4363_9C30_535AF4C9406C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWarningInfo dialog

extern void IsWarning();
extern void SaveWarningInfo(int nIndex,BOOL bStatus);

struct AlarmInfo 
{ 
    int alarmId; 
    CString alarmType; 
};

class CWarningInfo : public CDialog
{
// Construction
public:
	CWarningInfo(CWnd* pParent = NULL);   // standard constructor
	void AlarmReport(int alarmIndex,CString &alarmType);
// Dialog Data
	//{{AFX_DATA(CWarningInfo)
	enum { IDD = IDD_WARNINGINFO };
	CListBox	m_listWarning;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarningInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:
	BOOL PreTranslateMessage(MSG* pMsg) ;//重载函数，响应键盘动作。//ly 20110403
	// Generated message map functions
	//{{AFX_MSG(CWarningInfo)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//双语控制
class CLangControl
{
public:
	CLangControl();
	~CLangControl();

	BOOL LoadLogText();
	BOOL LoadWarningText();

	int Init();
	int GetCurLanguage();

	int GetUIText(LPCTSTR lpApp,LPCTSTR lpKey,LPTSTR lpBuf,DWORD dwSize);
//	int GetUIText(LPCSTR lpApp,LPCTSTR lpKey,LPSTR lpBuf,DWORD dwSize,int nLanguage);
	char* GetWarningText(int ErrNo);
	char* GetLogText(LPCTSTR lpApp,int ErrNo);

	friend CLangControl& GetLang();

private:
	int m_nIDLan;					//0:简体中文;1:英文
	TCHAR m_tszUiTxtPath[260];		//界面文本路径
	TCHAR m_tszErrTxtPath[260];		//报警文本路径
	TCHAR m_tszLogTxtPath[260];		//日志文本路径

	CString m_strLogText10[120];
	CString m_strLogText20[180];
	CString m_strLogText30[10];

	CString m_strWarningText10[200];
	CString m_strWarningText11[40];
	CString m_strWarningText12[20];
	CString m_strWarningText13[40];
	CString m_strWarningText14[125];
	CString m_strWarningText21[120];
	CString m_strWarningText22[60];
	CString m_strWarningText23[20];
	CString m_strWarningText31[50];
	CString m_strWarningText32[20];
	CString m_strWarningText41[50];
	CString m_strWarningText42[20];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNINGINFO_H__28A459B4_CF3E_4363_9C30_535AF4C9406C__INCLUDED_)
