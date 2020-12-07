#if !defined(AFX_MOTIONCONTROLTESTVIEW_H__E95C0A9C_D868_401C_A586_8C81EF517138__INCLUDED_)
#define AFX_MOTIONCONTROLTESTVIEW_H__E95C0A9C_D868_401C_A586_8C81EF517138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotionControlTestView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotionControlTestView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "stdafx.h"
#include "Shared Classes/ListReport/ListReport.h"
class CMotionControlTestView : public TVisualFormView
{
	friend DWORD WINAPI RunLoadOnce(LPVOID pM);				//20190723 Ôö¼Ó
	friend DWORD WINAPI RunUnloadOnce(LPVOID pM);
public:
	DWORD LoadOnce();
	DWORD UnloadOnce();

protected:
	CMotionControlTestView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMotionControlTestView)

// Form Data

private:
	bool m_bLoadRUpDown;
    bool m_bLoadLUpDown;
	bool m_bUnLoadLUpDown;
	bool m_bUnLoadRUpDown;
	bool m_bLoadRVac;
	bool m_bLoadLVac;
	bool m_bUnLoadRVac;
	bool m_bUnLoadLVac;
public:
	//{{AFX_DATA(CMotionControlTestView)
	enum { IDD = IDD_MOTIONCONTESTVIEW };
	CSmartEdit	m_edtStepLength;
	CSmartEdit	m_edtMoveToPos2;
	CSmartEdit	m_edtMoveToPos1;
//	CTransParentButton	m_btnLeftHandD;
//	CTransParentButton	m_btnRightHandD;
//	CTransParentButton	m_btnUnRightHandD;
//	CTransParentButton	m_btnUnLeftHandD;
//	CTransParentButton	m_btnUnLoadTest;
	CTransParentButton	m_btnTableUnLoadPos;
//	CTransParentButton	m_btnUnRightSorb;
//	CTransParentButton	m_btnUnRightHandUD;
//	CTransParentButton	m_btnUnPutBoadPos;
//	CTransParentButton	m_btnUnLoadStHUp;
//	CTransParentButton	m_btnUnLoadStHDown;
//	CTransParentButton	m_btnUnLeftSorb;
//	CTransParentButton	m_btnLeftHand_Ud;
//	CTransParentButton	m_btnUnTunePos;
//	CTransParentButton	m_btnUnTransPos;
//	CTransParentButton	m_btnUnGetBoadPos;
//	CTransParentButton	m_btnLoadTest;
//	CTransParentButton	m_btnPutBoadPos;
//	CTransParentButton	m_btnLoadStHUp;
//	CTransParentButton	m_btnLoadStHDown;
	CTransParentButton	m_btnTableLoadPos;
//	CTransParentButton	m_btnLeftSorb;
//	CTransParentButton	m_btnLeftHandUD;
//	CTransParentButton	m_btnGetTunePos;
//	CTransParentButton	m_btnTransPos;
//	CTransParentButton	m_btnGetBoadPos;
//	CTransParentButton	m_btnSnapIm;
//	CTransParentButton	m_btnSnapEx;
//	CTransParentButton	m_btnRightSorb;
//	CTransParentButton	m_btnRightHandUD;
	CStatic	m_sPLimit;
	CStatic	m_sNLimit;
	CStatic	m_sHome;
	CString	m_strMoveToPos1;
	CString	m_strMoveToPos2;
	UINT	m_ulStepLength;
	int		m_IntLoadTime;
	int		m_IntUnLoadTime;
	//}}AFX_DATA
	HICON m_hLedON;
	HICON m_hLedOFF;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionControlTestView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMotionControlTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMotionControlTestView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void On_AxisW_Home();
	afx_msg void On_AxisY_Home();
	afx_msg void On_AxisZ_Home();
	afx_msg void On_AxisX_Home();
	afx_msg void On_AxisLF_Home();
	afx_msg void On_AxisRF_Home();
	afx_msg void OnMoveToP1();
	afx_msg void OnMoveToP2();
	afx_msg void OnManuStop2();
	afx_msg void OnManuStop();
	afx_msg void OnManuUp();
	afx_msg void OnManuDown();
	afx_msg void OnManuLeft();
	afx_msg void OnManuRight();
	afx_msg void OnBtStopexcCard1();
	afx_msg void OnBtStopexcCard2();
	afx_msg void OnResetCard1();
	afx_msg void OnResetCard2();
	afx_msg void OnResetCard3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg long OnCheckLimit(UINT wParam,LONG lParam);
	afx_msg long OnUncheckLimit(UINT wParam,LONG lParam);;
	afx_msg void OnBtLoadpos();
	afx_msg void OnBtUnloadpos();
	afx_msg void OnButtonSet();
	afx_msg void OnBtnAgvl();
	afx_msg void OnBtnAgvul();
	afx_msg void OnBtnAgvulandl();
	//}}AFX_MSG
private:
	void SetUI();//ly add 20110318
	UINT GetCurOperateAxis();

	CTransParentButton	m_btnHomeX;
	CTransParentButton	m_btnHomeY;
	CTransParentButton	m_btnHomeZ;
	CTransParentButton	m_btnHomeW;

//	CTransParentButton	m_btnHomeX1;
//	CTransParentButton	m_btnHomeY1;
	CTransParentButton	m_btnHomeZ1;
	CTransParentButton	m_btnHomeW1;
//	CTransParentButton	m_btnHomeX2;
//	CTransParentButton	m_btnHomeY2;

	CTransParentButton	m_btnResetCard3;
	CTransParentButton	m_btnResetCard2;
	CTransParentButton	m_btnResetCard1;
//	CSmartEdit	m_edtStepLength;
//	CSmartEdit	m_edtMoveToPos1;
//	CSmartEdit	m_edtMoveToPos2;
	CComboBox	m_cmbSelectAxis;
	CTransParentButton	m_btnManuStop2;
	CTransParentButton	m_btnManuStop;
	CTransParentButton	m_btnManuUp;
	CTransParentButton	m_btnManuRight;
	CTransParentButton	m_btnManuLeft;
	CTransParentButton	m_btnManuDown;
	CTransParentButton	m_btnMoveToP2;
	CTransParentButton	m_btnMoveToP1;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONCONTROLTESTVIEW_H__E95C0A9C_D868_401C_A586_8C81EF517138__INCLUDED_)
