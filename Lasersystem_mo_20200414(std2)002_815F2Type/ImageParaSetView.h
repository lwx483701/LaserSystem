#if !defined(AFX_IMAGEPARASETVIEW_H__BF13D93A_71EC_497E_B65E_9E3DAE5C6DD9__INCLUDED_)
#define AFX_IMAGEPARASETVIEW_H__BF13D93A_71EC_497E_B65E_9E3DAE5C6DD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImageParaSetView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "stdafx.h"
#include "LampAdjDlgView.h"

class CImageParaSetView : public TVisualFormView
{
	friend DWORD WINAPI RunFirstMark(LPVOID pM);				//20190723 增加
public:
	DWORD FirstMark();

public:															//20180202
	BOOL m_bManuMarkIsOK;
	BOOL m_bManuMarkIsEnd;

	void BeginManuMark();
	void EndManuMark();

public:
	void InsertSort(int a[],int count);//jpc add 20130322

protected:
	CImageParaSetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CImageParaSetView)

// Form Data
public:
	//{{AFX_DATA(CImageParaSetView)
	enum { IDD = IDD_IMAGEPARASETVIEW };
	CTransParentButton	m_btnFirstFiduPoint;
	CSmartEdit	m_edtStepLength;
	CTransParentButton	m_btnLampAjust;
	CTransParentButton	m_coordCleanZR;
	CTransParentButton	m_coordCleanY;
	CTransParentButton	m_coordCleanZL;
	CTransParentButton	m_coordCleanX;
	CCheckSK	m_chkPlaneLAdsorb;
	CCheckSK	m_chkPlaneRAdsorb;
	CTransParentButton	m_btnStop;
	CTransParentButton	m_btnTabUP;
	CTransParentButton	m_btnTabRT;
	CTransParentButton	m_btnTabDN;
	CTransParentButton	m_btnTabLT;
	CTransParentButton	m_btnZUp;
	CTransParentButton	m_btnZDown;
	CLinkSlider	m_Slider1;
	CSmartEdit	m_edit1;
	CTransParentButton	m_btnSetFiducialPos;
	CTransParentButton	m_btnChannelChange;
	CTransParentButton	m_btnAdjustPattern;
	CTransParentButton	m_btnLearningPattern;
	CString	m_ulStepLength;
	long	m_lLightness;
	BOOL	m_bPlaneLAdsorb;
	BOOL	m_bPlaneRAdsorb;
	CString	m_X;
	CString	m_Y;
	CString	m_ZL;
	CString	m_ZR;
	 long m_bStatusScale;
	BOOL	m_chkManuMove;
	CString	m_Edit_StringTableDelay;
	double	m_dbTestTemperature;
	//}}AFX_DATA

// Attributes
public:
	CLampAdjDlgView* pLampAdj;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageParaSetView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL
	virtual ~CImageParaSetView();

// Implementation
protected:

//#ifdef _DEBUG											//20160919
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
//#endif
private:
	int selectHeadNumber;
	BOOL FirstPosFind;
	double FirstPosX;
	double FirstPosY;
	
	BOOL     FirstRun;

	int      m_bStatusX;
	int      m_bStatusY;
	int		 m_bManuRun;

	void WriteFiducialPosToFile(int mode);					//mode：1 A向；0 B向
	Coord ReadFiducialPosFromFile(int mode);				//mode：1 A向；0 B向
	void SetUI();	
	Coord ToRotateTable(const Coord& cenCrd, double angle, const Coord& crd);

	// Generated message map functions
	//{{AFX_MSG(CImageParaSetView)
    afx_msg LONG OnDisplayImage(UINT wParam,LONG lParam); 
	afx_msg LONG OnUndisplayImage(UINT wParam,LONG lParam);
	afx_msg void OnChangChannel();
	afx_msg void OnLearnPattern();
	afx_msg void OnStepDown();
	afx_msg void OnStepLeft();
	afx_msg void OnStepRight();
	afx_msg void OnStepUp();
	afx_msg void OnStepStop();
	afx_msg void OnFiducialPosSet();
	afx_msg void OnAdjustPattern();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChangeEdit1();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtZdown();
	afx_msg void OnBtZup();
	afx_msg void OnChkOutPlanel();
	afx_msg void OnChkOutPlaner();
	afx_msg void OnBtLamp();
	afx_msg void OnBtCleanX();
	afx_msg void OnBtCleanY();
	afx_msg void OnBtCleanZL();
	afx_msg void OnBtCleanZR();
	afx_msg void OnBtFirstfidupos();
	afx_msg void OnChkEnablemanumove();
	afx_msg void OnButtonCorrectionGalvo();
	afx_msg void OnButtonAccuracyGalvo();
	afx_msg void OnButtonRepeatabilityTable();
	afx_msg void OnButtonAccuracyTable();
	afx_msg void OnButtonCorrectionTable();
	afx_msg void OnBtMarktest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPARASETVIEW_H__BF13D93A_71EC_497E_B65E_9E3DAE5C6DD9__INCLUDED_)
