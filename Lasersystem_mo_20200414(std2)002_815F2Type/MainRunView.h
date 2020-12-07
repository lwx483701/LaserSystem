#if !defined(AFX_MAINRUNVIEW_H__7C531555_8636_4D72_8904_F123E0B50D54__INCLUDED_)
#define AFX_MAINRUNVIEW_H__7C531555_8636_4D72_8904_F123E0B50D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainRunView.h : header file

/////////////////////////////////////////////////////////////////////////////
// CMainRunView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "checkerctrl.h"
#include "ColorStaticST.h"
#include "ColorProgressCtrl.h"
#include "ProgressCheckCtrl.h"

#define WM_MSG_PREHOT  WM_USER+1//机器预热

class CMainRunView : public TVisualFormView
{
//建立加工线程 20190125
	friend DWORD WINAPI RunStart(LPVOID pM);
public:
	DWORD Process();							//原有的OnRunStart(),return->return 0
//重构加工流程：20161123
public:
//	void OnRunStartOld();

public:
	int GetBlockIndex(int nIndex,BOOL bIsSelectProc=true,BOOL bIsEvenRow=true);									//20161109
	void SetBlockColor(const COLORREF &color, int nIndex);

protected:
	CMainRunView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainRunView)

// Form Data
public:
	//{{AFX_DATA(CMainRunView)
	enum { IDD = IDD_MAINFORMVIEW };
	CButton	m_CheckNullHoles;
	CButton	m_CheckSelectOthers;
	CStatic	m_sMatch;
	CStatic	m_stHoleSum;
	CStatic	m_stNGSum;
	CButton	m_chkManuFid;
	CColorStaticST	m_stCurarea;
	CColorStaticST	m_stCurArea;
	CColorStaticST	m_stPCBDrilledHolecount;
	CColorStaticST	m_pcbdrilledholenum;
	CColorStaticST	m_cAdjustWar;
	CColorStaticST	m_cLaserpowerWar;
	CColorProgressCtrl	m_proLaserPowerWar;
	CColorProgressCtrl	m_proGalvoAdjWar;
	CColorStaticST	m_pcbholenum;
	CTransParentButton	m_btnTopoint;
	CTransParentButton	m_btnClean;
	CColorStaticST	m_ProcInfo;
	CColorStaticST	m_stPCBHoleCount;
	CColorStaticST	m_stProcInfo;
	CCheckSK	m_btnShowFileInfo;
	CColorStaticST	m_ProcedNum;
	CColorStaticST	m_FileName;
	CColorStaticST	m_stProcedNum;
	CColorStaticST	m_stFileName;
	CTransParentButton	m_btnRunStart;
	CTransParentButton	m_btnRunPause;
	CTransParentButton	m_btnHomeAll;
	CTransParentButton	m_btnSetParameter;
	CTransParentButton	m_btnScanAdjust;
	CTransParentButton	m_btnRunEnd;
	CTransParentButton	m_btnLaserWarmup;
	CTransParentButton	m_btnExit;
	int		m_bAutoProc;
	CString	m_strFileName;
	CString	m_strProcedNum;
	CString	m_strProcInfo;
	int		m_nAutoMatch;
	CString	m_strPCBHoleCount;
	BOOL	m_bAutoAdjust;
	BOOL	m_bAutoPower;
	CString	m_DrilledHoleCount;
	CString	m_CurArea;
	BOOL	m_bFidRetry;
	BOOL	m_bManuFid;
	CString	m_strHoleSum;
	CString	m_strNGSum;
	CString	m_strMatchScore;
	CString	m_strLRScale;
	BOOL	m_bOneAxis;
	BOOL	m_bCheckNullHoles;
	CString	m_strFileNameNew;
	//}}AFX_DATA

// Attributes
public:
	virtual ~CMainRunView();
// Operations
public:
	
	void ShowLaserRelease();
//	void ShowBlockView();
	void ResetSelectBlankColor();
	void SetScanSize(UINT ulSize);
//	long GetSelectBlockIndex(int nIndex)const;
	long GetSelectBlockIndex(int nIndex,BOOL bIsEvenRow=true)const;					//20161216
	long GetSelectBlockNum();
	void ResetBlankColor();
	
	void SetBlankColor(const COLORREF&color, int nSaIndex);
	void WIPTrackingReport();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainRunView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL
// Implementation


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	void SetUI();

	void SetCheckerBlockParam(UINT ulRow,UINT ulCol);
	void SetCheckerBlockParam();

	friend CMainRunView& GetRunView();
	void   OnDisplayFileInfo();
	static CCheckerCtrl m_ctrlChecker;
	static CProgressCheckCtrl m_ctrlChecker1;
	
	BOOL   m_bIsDisplay;
	long   m_lRunState;
	long   m_lDrillingSubareaNo;
    long   m_lPitchHeadNo;

    static UINT m_ulLastBlockSize;
    int   m_bStatusScale;
	int      m_bStatusX;
	int      m_bStatusY;

	HICON m_hLedON;//ly add 20130724
	HICON m_hLedOFF;//ly add 20130724
// Generated message map functions
//{{AFX_MSG(CMainRunView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRunCont();
	afx_msg void OnRunPause();
	afx_msg void OnDestroy();
	afx_msg void OnRunStart();
	afx_msg void OnRadAutoproc();
	afx_msg void OnExit();
	afx_msg void OnRunEnd();
	afx_msg void OnScanAdjust();
	afx_msg void OnLaserWarmup();
	afx_msg void OnHomeall();
	afx_msg void OnSetParameter();
	afx_msg void OnClearProcNum();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LONG OnDisplayImage(UINT wParam, LONG lParam);
	afx_msg LONG OnUnDisplayImage(UINT wParam, LONG lParam);
	afx_msg LONG OnDisplayDrillInfo(UINT wParam, LONG lParam);
//	afx_msg LONG OnDisplayProcInfo(UINT wParam,  LONG lParam);
	afx_msg LONG OnDisplayMatchInfo(UINT wParam,  LONG lParam);//ly add 20130724
//	afx_msg void OnBtTopoint();
	afx_msg void OnRadauto();
	afx_msg void OnRadmanu();
	afx_msg void OnChkEnableautoadjust();
	afx_msg void OnChkEnableautopower();
	afx_msg void MachinePreHot(WPARAM w, LPARAM l);
	afx_msg void OnFidRetry();
	afx_msg void OnClearNg();
	afx_msg void OnClrHoles();
	afx_msg void OnChkManufid();
	afx_msg void OnOneaxis();
	afx_msg void OnCheckselectothers();
	afx_msg void OnCheckNulldrillholes();
	afx_msg void OnMenuonlyanoreverse();
	afx_msg void OnUpdateMenuonlyanoreverse(CCmdUI* pCmdUI);
	afx_msg void OnMenuonlyareverse();
	afx_msg void OnUpdateMenuonlyareverse(CCmdUI* pCmdUI);
	afx_msg void OnMenuaandbdouble();
	afx_msg void OnUpdateMenuaandbdouble(CCmdUI* pCmdUI);
	afx_msg void OnMenuonlyb();
	afx_msg void OnUpdateMenuonlyb(CCmdUI* pCmdUI);
	afx_msg void OnMenudoubleaxis();
	afx_msg void OnUpdateMenudoubleaxis(CCmdUI* pCmdUI);
	afx_msg void OnMenuonlyleft();
	afx_msg void OnUpdateMenuonlyleft(CCmdUI* pCmdUI);
	afx_msg void OnMenuonlyright();
	afx_msg void OnUpdateMenuonlyright(CCmdUI* pCmdUI);
	afx_msg void OnButton6();
	afx_msg void OnRecognizeTest();
	afx_msg void OnUpdateFileName(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINRUNVIEW_H__7C531555_8636_4D72_8904_F123E0B50D54__INCLUDED_)
