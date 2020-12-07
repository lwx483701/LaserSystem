#if !defined(AFX_LISTTREECTRL_H__41D75506_D558_41BB_A7B8_506DCF2FB2AA__INCLUDED_)
#define AFX_LISTTREECTRL_H__41D75506_D558_41BB_A7B8_506DCF2FB2AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListTreeCtrl window
#include "SuperGridCtrl.h"
class CListTreeCtrl : public CSuperGridCtrl
{
// Construction
public:
	CListTreeCtrl();

// Attributes
public:

// Operations
public:
CComboBox* ShowList(int nItem, int nCol, CStringList *lstItems);
void OnControlLButtonDown(UINT nFlags, CPoint point, LVHITTESTINFO& ht);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
protected:
		CImageList m_image;//Must provide an imagelist
			int CalcHorzExtent(CWnd* pWnd, CStringList *pList);
public:
	bool InitializeGrid();
	virtual ~CListTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListTreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTREECTRL_H__41D75506_D558_41BB_A7B8_506DCF2FB2AA__INCLUDED_)
