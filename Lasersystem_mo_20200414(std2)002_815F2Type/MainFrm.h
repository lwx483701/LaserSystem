// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D2A800D7_252F_4E64_9770_3268FA1FD51F__INCLUDED_)
#define AFX_MAINFRM_H__D2A800D7_252F_4E64_9770_3268FA1FD51F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VisualFx.h"
#include "afxmt.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	long m_StaRSCurPods;
	CString m_Status;
	double m_Operation_Rate;
	COleDateTime startMachineTime;
	int m_shift;

	CCriticalSection cs_alarm;
	CCriticalSection cs_status;
	CCriticalSection cs_utility;
	CCriticalSection cs_wiptrack;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void SetUI(CMenu* mmenu);

    HANDLE		m_hMutex;
	HANDLE		m_hThread;
    CFont		m_Font;
//  CDummySplitter Splitter;
//	CGfxOutBarCtrl	wndBar;
//	CToolBar    m_wndToolBar;
//	CImageList	imaLarge, imaSmall;
//	CTreeCtrl	wndTree;

public:
	CStatusBar  m_wndStatusBar;
	static TVisualFramework m_Framework;
	
	friend CMainFrame& GetMainFrame();
	void StartThread();
	friend DWORD WINAPI StatusReportUploadProc(LPVOID pParam);
	long LoadLightStatusTableToCalcRunRate();
	void UtilityReport();
	void StatusReport();
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRunPane();
	afx_msg void OnFunctiontestPane();
	afx_msg void OnFilesetPane();
	afx_msg void OnPorwPane();
	afx_msg void OnImagePane();
	afx_msg void OnShowpointPane();
	afx_msg void OnSystemparaPane();
	afx_msg void OnOpratecoordPane();
	afx_msg void OnWorkparaPane();
	afx_msg void OnSingalinputPane();
	afx_msg void OnSingaloutputPane();
	afx_msg void OnMotortestPane();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnUpdateStatusBar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateProcAxisMode(CCmdUI *pCmdUI);		//重构加工流程：20161123
	afx_msg void OnUpdateFlowPathMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCurFileDisplay(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCurFlowStatus(CCmdUI *pCmdUI);

	afx_msg void OnUpdateGalvoLeft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGalvoRight(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePowerLeft(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePowerRight(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateProcStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAptNo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOptPathMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBeamMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMachineStatus(CCmdUI *pCmdUI);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D2A800D7_252F_4E64_9770_3268FA1FD51F__INCLUDED_)
