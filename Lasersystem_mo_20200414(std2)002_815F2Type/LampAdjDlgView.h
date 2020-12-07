#if !defined(AFX_LAMPADJDLGVIEW_H__E81124AB_5234_4250_9AE7_8CDF43FBDFAA__INCLUDED_)
#define AFX_LAMPADJDLGVIEW_H__E81124AB_5234_4250_9AE7_8CDF43FBDFAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LampAdjDlgView.h : header file
//
#include "OperateControl.h"
#include "ControlTool/SmartEdit/SmartEdit.h"
#include "cchecksk.h"
/////////////////////////////////////////////////////////////////////////////
// CLampAdjDlgView dialog

class CLampAdjDlgView : public CDialog
{
// Construction
public:
	CLampAdjDlgView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLampAdjDlgView)
	enum { IDD = IDD_LAMPSADJUST };
	CSmartEdit	m_Edit_RightInfrared;
	CSmartEdit	m_Edit_LeftInfrared;
	CLinkSlider	m_Slider_RightInfrared;
	CLinkSlider	m_Slider_LeftInfrared;
	CCheckSK	m_Check_RightInfrared;
	CCheckSK	m_Check_LeftInfrared;
	CTransParentButton	m_btnLuminSet;
	CCheckSK	m_chkSelectManual;
	CTransParentButton	m_btnResetCCDLumPara;
	CCheckSK	m_chkRightROpen;
	CCheckSK	m_chkRightCOpen;
	CCheckSK	m_chkLeftROpen;
	CCheckSK	m_chkLeftCOpen;
	CTransParentButton	m_LightParaOk;
	CTransParentButton	m_LightParaSave;
	CLinkSlider	m_sliderRR;
	CLinkSlider	m_sliderRC;
	CLinkSlider	m_sliderLR;
	CLinkSlider	m_sliderLC;
	CSmartEdit	m_conEditRR;
	CSmartEdit	m_conEditRC;
	CSmartEdit	m_conEditLR;
	CSmartEdit	m_conEditLC;
	long	m_vaEditLC;
	long	m_vaEditLR;
	long	m_vaEditRC;
	long	m_vaEditRR;
	int		m_radExt;
	int		m_radPriChannel;
	BOOL    m_SysLamps;
	long	m_LongLeftInfared;
	long	m_LongRightInfared;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLampAdjDlgView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetUI();//ly add 20110318
	// Generated message map functions
	//{{AFX_MSG(CLampAdjDlgView)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtSavelight();
	afx_msg void OnResetccdluminpara();
	afx_msg void OnLightSelect();
	afx_msg void OnLeftcopencheck();
	afx_msg void OnLeftropencheck();
	afx_msg void OnRightcopencheck();
	afx_msg void OnRightropencheck();
	afx_msg void OnCustomdrawSderLc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSderLr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSderRc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSderRr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCcdluminset();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPriChannelSelect();
	afx_msg void OnSubChannelSelect();
	afx_msg void OnOutofmemorySderLinfrared(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySderRinfrared(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChecklinfrared();
	afx_msg void OnCheckrinfrared();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAMPADJDLGVIEW_H__E81124AB_5234_4250_9AE7_8CDF43FBDFAA__INCLUDED_)
