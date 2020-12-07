#if !defined(AFX_LISTREPORT_H__2A49DBDB_C0FE_4669_B1CF_F2825FEEEADD__INCLUDED_)
#define AFX_LISTREPORT_H__2A49DBDB_C0FE_4669_B1CF_F2825FEEEADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListReport.h : header file
//
#pragma warning(disable:4786)
#include <string>
#include <vector>
using namespace std;

namespace ListReportDefinition
{
	enum ItemType
	{
		ItemTypeText = 0,
		ItemTypeCheckBox
	};

	// list of style
	const int intCellSelect = 1;
	// end of list of style
}

// user messages
#define WM_LISTREPORT_LBUTTONDOWN	WM_USER+1201
#define WM_LISTREPORT_LBUTTONDBLCLK	WM_USER+1202

const int intBorder = 2;

class CListItem;

/////////////////////////////////////////////////////////////////////////////
// CListReport window
class CListReport : public CListCtrl
{
// Construction
public:
	CListReport(int intStyle = 0);

// Attributes
public:

// Operations
public:
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	BOOL AddItem(int nItem, int nSubItem,LPCTSTR strItem, string sProperty = "");
	BOOL AddColumn(LPCTSTR strItem,int nItem, int intColumnWidth = -1,
		int nSubItem = -1,	int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
		int nFmt = LVCFMT_LEFT);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListReport)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListReport();
	static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	virtual BOOL DeleteItem( int nItem );
	virtual BOOL DeleteAllItems();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListReport)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CListItem * FindSelectedItem(CPoint point, int &intRow, int &intColumn);
	CPoint m_point;
	typedef vector<string> vecPropertyItem;
	vector <vecPropertyItem> m_vecProperty;
	int m_intStyle;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTREPORT_H__2A49DBDB_C0FE_4669_B1CF_F2825FEEEADD__INCLUDED_)
