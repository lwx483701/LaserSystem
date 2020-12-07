#if !defined(AFX_SYSPARAMVIEW_H__94939005_9043_4D2E_BD77_511B5A6F4CD0__INCLUDED_)
#define AFX_SYSPARAMVIEW_H__94939005_9043_4D2E_BD77_511B5A6F4CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysParamView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysParamView dialog
#include "stdafx.h"

class CSysParamView : public TVisualFormView
{
// Construction
public:
	CSysParamView();   // standard constructor
	DECLARE_DYNCREATE(CSysParamView)

// Dialog Data
	//{{AFX_DATA(CSysParamView)
	enum { IDD = IDD_SYSPARAMVIEW };
	CEdit	m_edtInnerScaleThrd;
	CEdit	m_edtNgThred;
	CEdit	m_edtScaleThrd;
	CEdit	m_edtLaserPowerMax;
	CEdit	m_edtJmpDelay0;
	CEdit	m_edtJmpLenth;
	CSmartEdit	m_edtLaserPowerSt;
	CSmartEdit	m_edtAutoThickError;
	CSmartEdit	m_edtScaleThreshold;
	CSmartEdit	m_edtGlvThreshold;
	COleDateTime  m_tDataTimeUpload;
	COleDateTime  m_tDataTimeUploadNight;
	CSmartEdit  m_edtAdjTestTime;
	CSmartEdit	m_edtLaserPowerTime;
	CTransParentButton	m_btnLongPathLaserTest;
	CSmartEdit	m_edtLongPathLaserFocusRT;
	CSmartEdit	m_edtLongPathLaserFocusLT;
	CTransParentButton	m_glvCCDSysOffset;
	CTransParentButton	m_testCCDDistance;
	CTransParentButton	m_testLaserFocus;
	CTransParentButton	m_testCCDFocus;
	CSmartEdit	m_edtAdjThreshold;
	CSmartEdit	m_edtProcThreshold;
	CSmartEdit	m_edtProcInnerThreshold;
	CTransParentButton	m_btnSet;
	CTransParentButton	m_btnReset;
	CTransParentButton	m_btnSave;
	CSmartEdit	m_edtSLBitPermm;
	CSmartEdit	m_edtCCDDistanceY;
	CSmartEdit	m_edtCCDDistanceX;
	CSmartEdit	m_edtGlvCCDOffsetZAbs;
	CSmartEdit	m_edtLaserFocusRT;
	CSmartEdit	m_edtLaserFocusLT;
	CSmartEdit	m_edtCCDFocusRT;
	CSmartEdit	m_edtCCDFocusLT;
	CSmartEdit	m_edtGlvCCDOffsetY;
	CSmartEdit	m_edtGlvCCDOffsetX;
	CSmartEdit	m_edtJmpSpeed;
	CSmartEdit	m_edtJmpDelay;
	CSmartEdit	m_edtMotionCardSn3;
	CSmartEdit	m_edtMotionCardSn2;
	CSmartEdit	m_edtMotionCardSn1;
	UINT	m_ulMotionCardSn1;
	UINT	m_ulMotionCardSn2;
	UINT	m_ulMotionCardSn3;
	UINT	m_ulJmpSpeed;
	int		m_ulJmpDelay;
	int		m_nGlvCCDOffsetHead;
	long	m_lOffsetAxisX;
	long	m_lOffsetAxisY;
	long	m_lOffsetAxisZAbs;
	long	m_lCCDFocusRT;
	long	m_lCCDFocusLT;
	long	m_lLaserFocusLT;
	long	m_lLaserFocusRT;
	long	m_lCCDDistanceY;
	long	m_lCCDDistanceX;
	UINT	m_ulSLBitPermm;
	UINT	m_ulProcThreshold;
	UINT	m_ulProcInnerThreshold;
	UINT	m_ulAdjThreshold;
	long	m_ulAdjTestTime;
	long	m_ulLaserPowerTime;
	long	m_lLongLaserPathFocusRT;
	long	m_lLongPathLaserFocusLT;
	CString	m_strXDiff;
	CString	m_strYDiff;
	long	m_iGlvThreshold;
	double	m_fScaleThreshold;
	UINT	m_ulAutoThickError;
	double	m_fLaserPowerSt;
	BOOL m_SysParamUsed;
	long	m_ulJmpLenth;
	int		m_ulJmpDelay0;
	int		m_ScaleType;
	double	m_fLaserPowerMax;
	int		m_iScaleThrd;
	long	m_lNGThred;
	double	m_fInnerScaleThrd;
	int		m_IntDistanceCentre;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysParamView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetUI();//ly add 20110318
	// Generated message map functions
	//{{AFX_MSG(CSysParamView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnRadGlvCCDOffset();
	afx_msg void OnGlvCcdPReset();
	afx_msg void OnGlvCcdPSet();
	afx_msg void OnTestCCDFocus();
	afx_msg void OnTestLaserFocus();
	afx_msg void OnTestCCDDistance();
	afx_msg void OnSave();
	afx_msg void OnBtLongpathTestlaserfocus();
	afx_msg void OnRadioScalethreshold();
	afx_msg void OnRadioScalethreshold2();
	afx_msg void OnKillfocusEdtInnerScaleThred();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSPARAMVIEW_H__94939005_9043_4D2E_BD77_511B5A6F4CD0__INCLUDED_)
