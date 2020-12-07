#if !defined(AFX_TOOLPARAVIEW_H__ED8FF191_6B41_4705_93A7_022E58BF450A__INCLUDED_)
#define AFX_TOOLPARAVIEW_H__ED8FF191_6B41_4705_93A7_022E58BF450A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolParaView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "stdafx.h"
#include "ColorStaticST.h"

class CToolParaView : public TVisualFormView
{
public:
	void ParamTest(int testType);
protected:	
	CToolParaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CToolParaView)

// Form Data
public:
	//{{AFX_DATA(CToolParaView)
	enum { IDD = IDD_TOOLSPARAVIEW };
	CSmartEdit	m_edtLaserRelease;
	CSmartEdit	m_edtLaserPeriod;
	long	m_lLaserPeriod;
	long	m_lLaserRelease;
	float	m_dbToolDiameter;
	CTransParentButton	 m_btnToolDel;
	CTransParentButton	 m_btnToolAdd;
	CTransParentButton	 m_btnToolSave;
	CTransParentButton	 m_btnToolModi;
	CString	m_strLaserWorkTime;
	CString	m_strDataState;
	BOOL	m_bTwoCycleMode;
	BOOL	m_checkPeriod;
	BOOL	m_bCircleProcMode;
	long	m_lBeamDia;
	long	m_lBeamStep;
	CString	m_sToolIndex;
	double	m_dbStepScale;
	//}}AFX_DATA
	static CComboBox	m_cmbToolSubApt;
	static CComboBox	m_cmbToolMode;
	static CComboBox	m_cmbToolIndex;
	static CComboBox	m_cmbToolApt;
	static CTreeCtrlEx	m_ToolParaTree;
	static BOOL m_bDataModified;
// Attributes

// Operations
public:
	afx_msg void OnToolParaSave();
	void SetBigHole(int nHoleDia,int nBeamDia,int nStepLength,int nIndex);				//20160809
	void SetBigHoleNew(int nHoleDia,int nBeamDia,int nStepLength,int nIndex);			//20160831
	void SetBigHoleNewNew(int nHoleDia,int nBeamDia,int nStepLength,double dbStepScale,int nIndex);			//20180824
	void ToolParaClear();
	void RestorePara();
	void LoadToolParaTree();
	void SetToolPara();
	virtual ~CToolParaView();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolParaView)
public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//	void GetToolInfo(const char* buf, long& iToolNo, float& iDiameter, long& iAperture);
	void GetToolInfo(const char *buf, long &iToolNo, float &dbDiameter, long &iAperture,long &iSubAperture);
	long GetDrillModel(const  char* pchFirst, const char* pchLast)const;
	void ShowEnergyInfo(const char* buf);
	void ShowUToolInfo(const char* buf);

	friend  CToolParaView& GetToolView();
	// Generated message map functions
	//{{AFX_MSG(CToolParaView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnDisplayToolTree(UINT wParam, LONG lParam);
	afx_msg void OnToolParaAdd();
	afx_msg void OnToolModify();
	afx_msg void OnToolParaDel();
	afx_msg void OnSelChangedToolTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCmbToolapt();
	afx_msg void OnSelchangeCmbToolSubapt();
	afx_msg void OnChkTwocyclemode();
	afx_msg void OnParamTest();
	afx_msg void OnParamTest2();
	afx_msg void OnParamTest3();
	afx_msg void OnParamTest4();
	afx_msg void OnButtonLaserFocus();
	afx_msg void OnButtonAperture();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnChkCircleprocmode();
	afx_msg void OnButton1();
	afx_msg void On5mmTable();
	afx_msg void OnTableAccuracy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetUI();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLPARAVIEW_H__ED8FF191_6B41_4705_93A7_022E58BF450A__INCLUDED_)
