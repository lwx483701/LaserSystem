// SystemLogView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_SYSTEMLOGVIEW_H__B57EB5B1_873B_4622_BE28_4EC3377FE947__INCLUDED_)
#define AFX_SYSTEMLOGVIEW_H__B57EB5B1_873B_4622_BE28_4EC3377FE947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "ControlTool/SortListCtr/SortListCtrl.h"

typedef struct tagReportSanalyse
{
	CString m_FileName;
	CString m_LotID;
	CString  m_BeginDay;
	CString  m_BeginTime;
	CString  m_EndDay;
	CString  m_EndTime;
	CString  m_PitchTime;
	long  m_AllTimes;
	int  m_OKPanel;
	int  m_NGPanel;
	int  m_TotalPanel;
	int   m_SingleHoles;
	long  m_TotalHoles;
}isTagReportSanalyse;

typedef CArray<tagReportSanalyse,tagReportSanalyse &> CArraytagReportSanalyse;

class CSystemLogView : public TVisualFormView
{
protected:
	CSystemLogView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSystemLogView)

// Form Data
public:
	//{{AFX_DATA(CSystemLogView)
	enum { IDD = IDD_SYSTEMLOG };
	CComboBox	m_HisLogSelect;
	CTreeCtrl	m_treeLog;
	CSortListCtrl	m_datadisplay;
	CTransParentButton	m_logSave;
	CTransParentButton	m_logFilter;
	CComboBox	m_SetSelect;
	COleDateTime	m_tDataTimeBefor;
	COleDateTime	m_tDateTimeAfter;
	COleDateTime	m_tHistoryAfter;
	COleDateTime	m_tHistoryBefor;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemLogView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
private:
	void SetUI();
	void LoadHistoryLog();

	void SetCalcHead(int mode=0);
	void SetProHead();
	void SetPowerHead();
	void SetFilePropHead();

	BOOL LoadHistoryCalcDisplay(BOOL sift=0);
	BOOL LoadHistoryProDisplay(BOOL sift=0);
	BOOL LoadHistoryPowerDisplay();
	BOOL LoadHistoryPowerParaDisplay();

	void LoadCalcToDisplay(CString &TimeB,CString &TimeA);
	void LoadProToDisplay(CString &TimeB,CString &TimeA,BOOL sift=0);
	void LoadPowerToDisplay(CString &TimeB,CString &TimeA);
	void LoadPowerParaToDisplay(CString &TimeB,CString &TimeA);

	void LoadCalcAnalyse(CString &TimeB,CString &TimeA);
	
protected:
	virtual ~CSystemLogView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSystemLogView)
	afx_msg void OnBtFitter();
	afx_msg void OnBtLogsave();
	afx_msg void OnDblclkTreelog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtOpenhisdisplay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL ExportResult(const CString strFilName);
	CString  GetListFieldName(int FieldNumb);

	CString strValueB,strValueA;
    CArraytagReportSanalyse m_CArrayCountList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMLOGVIEW_H__B57EB5B1_873B_4622_BE28_4EC3377FE947__INCLUDED_)
