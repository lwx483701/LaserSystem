#if !defined(AFX_TESTFUNCTIONVIEW_H__518A3B6D_D63D_4F6E_AC99_87C28F219EF4__INCLUDED_)
#define AFX_TESTFUNCTIONVIEW_H__518A3B6D_D63D_4F6E_AC99_87C28F219EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestFunctionView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestFunctionView dialog
#include "stdafx.h"

class CTestFunctionView : public TVisualFormView
{
// Construction
	DECLARE_DYNCREATE(CTestFunctionView)
public:
	CTestFunctionView();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestFunctionView)
	enum { IDD = IDD_TESTFUNCTIONVIEW };
	CEdit	m_BaseDelay;
	CComboBox	m_LaserHead;
	CComboBox	m_MatrixHead;
	CTransParentButton	m_btnCycleDrillMatrix;
	CSmartEdit	m_edtTextTest;
	CSmartEdit	m_edtTestBoardThickness;
	CComboBox	m_cmbTestAperture;
//	CTransParentButton	m_btnRegionTest;
	CTransParentButton	m_btnBarCodePrint;
	CTransParentButton	m_btnResetParam;
	CTransParentButton	m_btnSetParam;
	CSmartEdit	m_edtLaserOnTime;
	CSmartEdit	m_edtJumpDelay;
	CSmartEdit	m_edtJumpSpeed;
	CSmartEdit	m_edtPlsPeriod;
	CSmartEdit	m_edtPlsRelease;
	CComboBox	m_cmbMDir;
	CTransParentButton	m_btnWarmUpLaser;
	CTransParentButton	m_btnTestLaserPower;
	CTransParentButton	m_btnDrillMatrix;
	int		m_iMatrix;
	UINT	m_ulJumpDelay;
	UINT	m_ulJumpSpeed;
	int 	m_ulLaserOnTime;
	UINT	m_ulPlsPeriod;
	UINT	m_ulPlsRelease;
	int		m_lMatrixHead;
	int		m_lLaserHead;
	float	m_dbLaserPower;
	CString	m_strBarcode;
	int		m_lDrillBarCodeHead;
	int		m_lDrillBarCodeType;
	int		m_iLaserTestInDex;
	CString	m_strTestThickness;
	CString	m_strPulseCount;
	long	m_ulTestThickness;
	CString	m_strTextTest;
	BOOL m_SysTestF;
	UINT	m_uWarmPlsRelease;
	int		m_BaseDelayInt;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestFunctionView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestFunctionView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrillMatrix();
	afx_msg void OnDestroy();
//	afx_msg void OnResetParam();
	afx_msg void OnSetParam();
	afx_msg void OnTestLaserPower();
	afx_msg void OnWarmupLaser();
	afx_msg void OnBarCodePreview();
	afx_msg void OnBarCodePrint();
	afx_msg void OnBtSwitch();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnZerotest();
	afx_msg void OnBtnTestthickness();
	afx_msg void OnBtTexttest();
	afx_msg void OnBtAptswitch();
	afx_msg void OnBtCycledrillmatrix();
	afx_msg void OnSelchangeCmbTestaperture();
	afx_msg void OnPrecisiontest();
	afx_msg void OnLaserfocustest1();
	afx_msg void OnLaserfocustest2();
	afx_msg void OnAperturetest();
	afx_msg void OnTabletest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetUI();//ly add 20110318

	bool m_bSwitch;
};

extern CTestFunctionView *pTestFunctionView;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTFUNCTIONVIEW_H__518A3B6D_D63D_4F6E_AC99_87C28F219EF4__INCLUDED_)
