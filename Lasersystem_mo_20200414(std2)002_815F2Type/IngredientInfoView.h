#if !defined(AFX_INGREDIENTINFOVIEW_H__33F15E09_FDCF_44E5_9236_3F321989D173__INCLUDED_)
#define AFX_INGREDIENTINFOVIEW_H__33F15E09_FDCF_44E5_9236_3F321989D173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IngredientInfoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIngredientInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <vector>
#include <string>
#include "ColorStaticST.h"
#include "ControlTool/SmartEdit/gridctrl.h"
using namespace std;

class CIngredientInfoView : public TVisualFormView
{
protected:
	CIngredientInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIngredientInfoView)

// Form Data
public:
	//{{AFX_DATA(CIngredientInfoView)
	enum { IDD = IDD_INGREDIENTINFOVIEW };
	CTransParentButton	m_btnImesSetting;
	CStatic	m_staCurUser;
	CString	m_strCurUser;
	CColorStaticST	m_staSsemp;
	CString	m_strSsemp;
	CStatic	m_staLotID;
	CString	m_strLotID;
	CStatic	m_staResponse;
	CString	m_strResponse;
	CTransParentButton m_btnModeSwitch;
	BOOL m_bModeSwitch;
	CTransParentButton m_btnGetIngredients;

	CGridCtrl m_GridProcPara;
	std::vector<KEYVALUEINFO> m_itemKeyValueV;

	//}}AFX_DATA
	CWinThread* statusThread;
	CWinThread* alarmThread;
	CWinThread* wipTrackThread;
	CWinThread* utilityThread;
	


// Attributes
public:
	long m_lHeartbeatFreq;
	BOOL m_bisLoading;

// Operations
public:
	void FillGridWithText();
	void ParamVerify();
	void EQPInfoVerify();
	void ClearAllContent();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIngredientInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIngredientInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIngredientInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnImesSetting();
	afx_msg void OnModeSwitch();
	afx_msg void OnGetIngredients();
	afx_msg void SetEditDisabledBegin(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void SetEditDisabledEnd(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateResponse(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnSelchangeBetfactor();
//	afx_msg void OnFitBET();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//CString GetBETOffsetText(UINT nRow,UINT nCol);
	void SetUI();
	CString GetCurCellText(UINT nRow, UINT nCol);
	CString m_beginLabel;
	CWinThread* CIngViewThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSITIONERRVALUEVIEW_H__33F15E09_FDCF_44E5_9236_3F321989D173__INCLUDED_)
