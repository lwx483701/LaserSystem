#if !defined(AFX_TREECTRLEX_H__9BF19864_5616_41CA_87D9_751302716DE3__INCLUDED_)
#define AFX_TREECTRLEX_H__9BF19864_5616_41CA_87D9_751302716DE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx window

class CTreeCtrlEx : public CTreeCtrl
{
// Construction
public:
	CTreeCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetBkImage(LPCTSTR lpszResourceName);
	BOOL SetBkImage(UINT nIDResource);
	BOOL Sort(HTREEITEM hItem,BOOL bSortA=TRUE);
	void SaveToolToFile(const char* filename);
	BOOL LoadToolFromFile(const char* filename);
	long GetIndentLevel(HTREEITEM hItem )const;
	void Serialize(CArchive& ar);
	HTREEITEM FindData(HTREEITEM hti, DWORD dwData);
	HTREEITEM FindItemData(DWORD lparam, BOOL bDownDir,HTREEITEM hItem);
	HTREEITEM FindItem(CString& str,BOOL bCaseSensitive, BOOL bDownDir,BOOL bWholeWord,HTREEITEM hItem);
	HTREEITEM GetPrevItem(HTREEITEM hItem);
	HTREEITEM GetLastItem(HTREEITEM hItem);
	HTREEITEM GetNextItem(HTREEITEM hItem);
    static int CALLBACK CompareNoCase(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	virtual ~CTreeCtrlEx();

	// Generated message map functions
protected:
	BOOL IsFindValid(HTREEITEM);
	//{{AFX_MSG(CTreeCtrlEx)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
protected:
	CPalette m_pal;
	CBitmap m_bitmap;
	int m_cxBitmap, m_cyBitmap;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLEX_H__9BF19864_5616_41CA_87D9_751302716DE3__INCLUDED_)
