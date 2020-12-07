#if !defined(AFX_FILEINFOSETTINGVIEW_H__F89AA71B_44A6_45F3_8468_53D7E43270BC__INCLUDED_)
#define AFX_FILEINFOSETTINGVIEW_H__F89AA71B_44A6_45F3_8468_53D7E43270BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileInfoSettingView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "stdafx.h"
#include "ColorStaticST.h"
#include "ScaleSetDlgView.h"
#include "ProcLogin_SN.h"

class CFileInfoSettingView : public TVisualFormView
{
public:
	BOOL m_bFileInfoDataModified;
//重构加工流程：20161123
public:
	void SelectFile(CString& strFileName);
	BOOL OpenDataFile(CString& strFileName,BOOL bIsOnlySA=false);
	BOOL SwitchDataFile(int side);
	void OnBtnRotate(int angle);
	void DealLotIdFixAndInc();

//public:
//	CProcLogin_SN* pProcLogin_SN;			//20160901
public:
	CScaleSetDlgView* pScaleSetView;		//20160812

protected:
	CFileInfoSettingView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFileInfoSettingView)

// Form Data
public:
	//{{AFX_DATA(CFileInfoSettingView)
	enum { IDD = IDD_FILEINFOSETTINGVIEW };
	CButton	m_Check_OverBorad;
	CButton	m_Check_ManuScale;
	CButton	m_chk3Fid;
	CButton	m_chkAxisNo;
	CButton	m_chkLotIdScale;
	CButton	m_chkLotIdFix;
	CButton	m_chkLotIdInc;
	CTransParentButton	m_btnRotate;
	CColorStaticST	m_stState;
	CColorStaticST	m_stFileInfo;
	CCheckSK	m_chkDrillStringInfo;
	CTransParentButton	m_btnTransSave;
	CSmartEdit	m_edtStrZoom;
	CSmartEdit	m_edtPCBThickness;
	CTransParentButton	m_btnMirror;
	CTransParentButton	m_btnTxtZoomEnter;
	CTransParentButton	m_btnOptimizePath;
	CComboBox	m_cIntegernum;
	CComboBox	m_cDecimalnum;
	CTransParentButton	m_btnSetFidOffset;
	CSmartEdit	m_edtFidOffY4;
	CSmartEdit	m_edtFidOffY3;
	CSmartEdit	m_edtFidOffY2;
	CSmartEdit	m_edtFidOffY1;
	CSmartEdit	m_edtFidOffX4;
	CSmartEdit	m_edtFidOffX3;
	CSmartEdit	m_edtFidOffX2;
	CSmartEdit	m_edtFidOffX1;
	CSmartEdit	m_edtScanSize;
	CSmartEdit	m_edtMachineSn;
	CTransParentButton	m_btnSelectFile;
	CCheckSK	m_chkDrillTimeInfo;
	CCheckSK	m_chkDrillMachInfo;
	CCheckSK	m_chkDrillLotInfo;
	CCheckSK	m_chkDrillDayInfo;
	BOOL	m_bDrillTimeInfo;
	BOOL    m_bDrillStrInfo;
	BOOL	m_bDrillMachInfo;
	BOOL	m_bDrillLotInfo;
	BOOL	m_bDrillDayInfo;
	CString	m_strMachineSn;
	long	m_lScanSize;
	int		m_iProcMode;
	int		m_iCrdAbsolute;
	int		m_iUnitInch;
	int		m_iDateFormat;
	int		m_iDecimalNum;
	int		m_iIntegerNum;
	long	m_lFidOffX1;
	long	m_lFidOffX2;
	long	m_lFidOffX3;
	long	m_lFidOffX4;
	long	m_lFidOffY2;
	long	m_lFidOffY3;
	long	m_lFidOffY4;
	long	m_lFidOffY1;
	CString	m_staticState;
	double	m_fStrZoom;
	int		m_iOpticalPathMode;
	int		m_iAutoThicking;
	long	m_ulPCBThickness;
	int		m_iFileMode;
	BOOL	m_bLotIDFix;
	BOOL	m_bLotIDInc;
	BOOL	m_bLotIDScale;
	CString	m_strLotIdFix;
	CString	m_strLotIdInc;
	BOOL	m_bAxisNo;
	BOOL	m_b3Fid;
	BOOL	m_bCheckManulScaleRange;
	CString	m_EditNoProcess;
	int m_Combo_OverPCB;
	CString	m_DoubleManScaleX;
	CString	m_DoubleManScaleY;
	CProgressCtrl m_prog;
	CTransParentButton	m_btnRise;
	CTransParentButton	m_btnDown;
	//}}AFX_DATA

// Attributes
public:
	vector<KEYVALUEINFO>m_barcodeStructVet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileInfoSettingView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileInfoSettingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFileInfoSettingView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectFile();
	afx_msg void OnDestroy();
//	afx_msg void OnRadProcessdir();
//	afx_msg void OnRadProcessdirN();
	afx_msg void OnOptimizePath();
	afx_msg void OnRadUnitinch();
	afx_msg void OnRadUnitmetric();
//	afx_msg void OnChkDrillmachinfo();
//	afx_msg void OnChkDrilldayinfo();
//	afx_msg void OnChkDrilltimeinfo();
	afx_msg void OnChkDrilllotinfo();
	afx_msg void OnBtEnter();
	afx_msg void OnBtnMirror();
	afx_msg void OnRadioShortpath();
	afx_msg void OnRadioLongpath();
	afx_msg void OnRadioManthickness();
	afx_msg void OnRadioAutothickness();
	afx_msg void OnBtnSetThickness();
	afx_msg void OnRadioNormalproc();
	afx_msg void OnRadioInnermark();
	afx_msg void OnRadioLocalmark();
	afx_msg void OnBtnTranssave();
	afx_msg void OnRadioSalocalmark();
//	afx_msg void OnChkDrillstringinfo();
//	afx_msg void OnChkEnfiducial1();
//	afx_msg void OnChkEnfiducial2();
//	afx_msg void OnChkEnfiducial3();
//	afx_msg void OnChkEnfiducial4();
	afx_msg void OnMachPrehot();
	afx_msg void OnKillfocusEdtScansize();
//	afx_msg void OnRadAbsolute();
//	afx_msg void OnRadIncremental();
//	afx_msg void OnRadDataformat();
//	afx_msg void OnRadio7();
//	afx_msg void OnRadio8();
//	afx_msg void OnSelchangeCmbIntegernum();
//	afx_msg void OnSelchangeCmbDecimalnum();
	afx_msg void OnBtnRotate();
//	afx_msg void OnFixing();
//	afx_msg void OnIncreasing();
	afx_msg void OnDrillscale();
//	afx_msg void OnChkDrillAxisNo();
	afx_msg void OnChk3fid();
//	afx_msg void OnRadioManscale();
//	afx_msg void OnRadioRefscale();
	afx_msg void OnLoadavgscale();
	afx_msg void OnCheckscalethrd();
	afx_msg void OnCheckmanscale();
//	afx_msg void OnButton1();
	afx_msg void OnMenuonlyanoreverse();
	afx_msg void OnMenuasidedisplay();
	afx_msg void OnUpdateMenuasidedisplay(CCmdUI* pCmdUI);
	afx_msg void OnMenubsidedisplay();
	afx_msg void OnUpdateMenubsidedisplay(CCmdUI* pCmdUI);
	afx_msg void OnChangeData();
	afx_msg void OnRadProcMode();
	afx_msg void OnUpdateSeleteFileName(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnAgvRise();
	afx_msg void OnBtnAgvDown();
	//afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetUI();
	void ReadPCBThickness();

	CString twoFilePath[2];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEINFOSETTINGVIEW_H__F89AA71B_44A6_45F3_8468_53D7E43270BC__INCLUDED_)
