#if !defined(AFX_PROCPARAVIEW_H__1455678C_DA70_493E_9774_28415DDE1E0D__INCLUDED_)
#define AFX_PROCPARAVIEW_H__1455678C_DA70_493E_9774_28415DDE1E0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PROCPARAVIEW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcParaView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CProcParaView : public TVisualFormView
{
protected:
	void SetUI();//ly add 20110318
	CProcParaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProcParaView)

// Form Data
public:
	//{{AFX_DATA(CProcParaView)
	enum { IDD = IDD_PROCPARAVIEW };
	CButton	m_CheckDrillRegion;
	CEdit	m_edtPluseTimes;
	CSmartEdit	m_edtTextHeigth;
	CSmartEdit	m_edtRegionDim;
	CSmartEdit	m_edtGlvAdjPlsRelease;
	CComboBox	m_cmbLongPathAdjAperture;
	CComboBox	m_cmbAdjAperture;
	CComboBox	m_cmbTxtAperture;
	CSmartEdit	m_edtTxtJumpDelay;
	CSmartEdit	m_edtTxtJumpSpeed;
	CSmartEdit	m_edtTxtPlsPeriod;
	CSmartEdit	m_edtTxtPlsRelease;
	CComboBox	m_cmbTxtPlsNum;
	CSmartEdit	m_edtAdjJmpSpeed;
	CSmartEdit	m_edtAdjPlsRelease;
	CSmartEdit	m_edtAdjPlsPeriod;
	CSmartEdit	m_edtAdjJmpDelay;
	CSmartEdit	m_edtPlsPeriod;
	CSmartEdit	m_edtJumpDelay;
	CTransParentButton	m_btnSetPara;
	CTransParentButton	m_btnSavePara;
	CTransParentButton	m_btnResetPara;
	CSmartEdit	m_edtPlsRelease;
	CSmartEdit	m_edtPls2Release;
	CSmartEdit	m_edtPls3Release;
	CSmartEdit	m_edtPls4Release;
	CSmartEdit	m_edtPls5Release;
	CSmartEdit	m_edtJumpSpeed;
	CComboBox	m_cmbAperture;
	CComboBox	m_cmbPlsNum;
	long	m_lJumpDelay;
	long	m_lJumpSpeed;
	UINT	m_ulPlsPeriod;
	UINT	m_ulPlsRelease;
	UINT	m_ulPls2Release;
	UINT	m_ulPls3Release;
	UINT	m_ulPls4Release;
	UINT	m_ulPls5Release;
	UINT	m_ulAdjJmpDelay;
	UINT	m_ulAdjJmpSpeed;
	UINT	m_ulAdjPlsPeriod;
	UINT	m_ulAdjPlsRelease;
	UINT	m_ulTxtPlsRelease;
	UINT	m_ulTxtPlsPeriod;
	long	m_lTxtJumpSpeed;
	long	m_lTxtJumpDelay;
	UINT	m_ulGlvAdjPlsRelease;
	long	m_iRegionDim;
	double	m_fTextHeigth;
	BOOL	m_SysProc;
	int		m_RegionPointDis;
	int		m_iPluseTimes;
	BOOL	m_chkDrillCoil;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcParaView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProcParaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProcParaView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnResetProcPara();
	afx_msg void OnSetProcPara();
	afx_msg void OnSaveProcPara();
	afx_msg void OnSelchangeCmbAperture();
	afx_msg void OnSelchangeCmbAdjaperture();
	afx_msg void OnSelchangeCmbLongpathAdjaperture();
	afx_msg void OnSelchangeCmbTxtperture();
	afx_msg void OnCountClear();
	afx_msg void OnButtonAccuray();
	afx_msg void OnCheckDrillregion();
	afx_msg void OnCheckDrillcoil();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCPARAVIEW_H__1455678C_DA70_493E_9774_28415DDE1E0D__INCLUDED_)
