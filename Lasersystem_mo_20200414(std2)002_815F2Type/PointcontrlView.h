#if !defined(AFX_POINTCONTRLVIEW_H__ADFE1D9C_41A2_4AA2_91A1_E78EA76D3473__INCLUDED_)
#define AFX_POINTCONTRLVIEW_H__ADFE1D9C_41A2_4AA2_91A1_E78EA76D3473__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointcontrlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointcontrlView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ControlTool/CJColorPicker/CJColorPicker.h"
#include "ControlTool/ColorComBox/BSColorComboBox.h"
#include "ControlTool/SortListCtr/SortListCtrl.h"

class CPointcontrlView : public TVisualFormView
{
protected:
	CPointcontrlView();           // protected constructor used by dynamic creation  	static	CSortListCtrl	m_tInfor;
	DECLARE_DYNCREATE(CPointcontrlView)

// Form Data
public:
	//{{AFX_DATA(CPointcontrlView)
	enum { IDD = IDD_POINTCONTRLVIEW };
	CCJColorPicker	m_btnToolColor;
	CTransParentButton	m_cBtZoomFrame;
	CTransParentButton	m_cBtZoomReset;
	CTransParentButton	m_cBtZoomOut;
	CTransParentButton	m_cBtZoomIn;
	CBSColorComboBox	m_ColorSel;
	static	CSortListCtrl	m_tInfor;
	//}}AFX_DATA

// Attributes

// Operations
private:
	int m_TempiIten;

public:
	static CDWordArray ColorToolPoint;
	static COLORREF  ColorToolFid;
	static COLORREF  ColorToolTxt;
	static COLORREF  ColorToolRect;

	void ToolInforClear();
	void LoadToolInfor();
	void SaveToolColorToFile();			//存储刀具颜色信息到TXT文件里
	void SaveAssisCrInfo();				//从INI文件里取得辅助信息颜色信息

	friend  CPointcontrlView& GetPointcontrlView();

private:	
	void SetUI();
	void LoadToolColorFormFile();		//从TXT文件里取得刀具颜色信息
	void LoadAssisCrInfo();				//从INI文件里取得辅助信息颜色信息

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointcontrlView)
	public:
	virtual void OnInitialUpdate();

	protected:
		afx_msg void OnClickLstTool(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg LRESULT OnComboSelection(WPARAM, LPARAM);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:	
	virtual ~CPointcontrlView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPointcontrlView)
	afx_msg void OnBtZoomin();
	afx_msg void OnBtZoomout();
	afx_msg void OnBtZoomreset();
	afx_msg void OnBtZoomframe();
	afx_msg void OnBtnToolcolor();
	afx_msg void OnBtPathShow();
	afx_msg void OnBtColorSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTCONTRLVIEW_H__ADFE1D9C_41A2_4AA2_91A1_E78EA76D3473__INCLUDED_)
