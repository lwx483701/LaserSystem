#if !defined(AFX_IMESSETTINGDIALOG_H__496F891C_DC50_4B55_9759_675E4AB75025__INCLUDED_)
#define AFX_IMESSETTINGDIALOG_H__496F891C_DC50_4B55_9759_675E4AB75025__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImesSettingDialog.h : header file
//
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "stdafx.h"
#include "ControlTool/SmartEdit/gridctrl.h"


/////////////////////////////////////////////////////////////////////////////
// CImesSettingDialog dialog

class CImesSettingDialog : public CDialog
{
// Construction
public:
	CImesSettingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImesSettingDialog)
	enum { IDD = IDD_DLG_IMESSETTING };
	CStatic m_staMachineNum;
	CString m_strMachineNum;
	CStatic m_staImesURL;
	CString m_strImesURL;
	CStatic m_staTimeout;
	CStatic m_staIdtTime;
	long m_lTimeout;
	long m_lIdtTime;
	CCheckSK m_chkUserControlSwitch;
	BOOL m_bUserControlSwitch;
	CStatic m_staHeartbeatContent;
	CString m_strHeartbeatContent;
	CStatic m_staHeartbeatFreq;
	CString m_strHeartbeatFreq;

	CGridCtrl m_GridLabel;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	void FillGridWithText();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImesSettingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImesSettingDialog)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void SetEditDisabledBegin(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void SetEditDisabledEnd(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg BOOL OnSetParam();
	afx_msg void OnCheckHeartbeat();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//UINT GetAxisEncode(int nIndex) const;
	CString m_beforLabel;
	CString GetCurCellText(UINT nRow,UINT nCol);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMESSETTINGDIALOG_H__496F891C_DC50_4B55_9759_675E4AB75025__INCLUDED_)
