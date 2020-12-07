#if !defined(AFX_CHECKERCTRL_H__AD4BC4E3_7750_11D4_8718_008048CA4A77__INCLUDED_)
#define AFX_CHECKERCTRL_H__AD4BC4E3_7750_11D4_8718_008048CA4A77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckerCtrl.h : header file
//

#include "afxtempl.h" 
/////////////////////////////////////////////////////////////////////////////
// CCheckerCtrl window

#define WM_CHECKERCTRL_RBUTTONDOWN	WM_USER + 100

#define BLANKED_BLOCKS_COLOR	  RGB(0,  0,   252)
#define BLANKED_BLOCKS_UNSELCOLOR RGB(255,100, 0  )
#define BLANKED_BLOCKS_SELCOLOR	  RGB(55, 155, 100)
#define BLANKED_BLOCKS_DIRLLCOLOR RGB(155,155, 100)
#define CHECKERCTRLBACKGROUND     RGB(255,128, 64)

#define TEXT_COLOR	  RGB(100, 10, 252)

#define BLANKED_BLOCKS_WIDTH	26
#define BLANKED_BLOCKS_HEIGHT	30

class CCheckerCtrl : public CWnd
{
// Construction
public:
	CCheckerCtrl();

	struct BlockPos
	{
		unsigned int nCol;
		unsigned int nRow;
		BlockPos()
		{
			nCol = 0;
			nRow = 0;
		}
		BlockPos(unsigned int nC,unsigned int nR):nCol(nC),nRow(nR){}
	};

// Attributes
public:
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckerCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBlockWidth(UINT nWidth,UINT nR,UINT nC);
	BlockPos GetSelectBlockPos(unsigned int unIndex);
//	BlockPos GetSelectBlockPos(int nIndex);
	int  GetSelectBlockNum()const;
	void CreateSafeTooltipRect(int iIndex,LPCTSTR lpszText);
	void SetTotalBlocks(const UINT nRows, const UINT nCols,const UINT nStartIndex);
	void SetTotalBlocks(const UINT nNumberofBlocks, const UINT nStartIndex = 0);
	void Update(const UINT nBlockNumber);
	void Reset();
	void Refresh();
	void SetBlock(const UINT nBlockNumber, const COLORREF crColor);
	COLORREF GetBlock(const UINT nBlockNumber) const;
	void SelectOthers();
		void SelectOthers2();
	BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID);
	virtual ~CCheckerCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckerCtrl)
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsVisible(const UINT nBlockNumber);
	CRect GetRect(const UINT nRow, const UINT nColumn);
	COLORREF GetColor(int iIndex) const;

	void CreateSafeTooltipRect(int x, int y, LPCTSTR lpszText);
	void SetBlock(int nRow, int nColumn, CBrush &brush, CDC &dc);

	CWnd	*m_pParentWnd;
	UINT	m_nID;
	UINT	m_nStartIndex;            //the starting index of blocks
	BOOL	m_bShouldUpdated;
	CRect	tooltipRect;
	UINT	m_nTotalVisibleBlocks;
	UINT	m_nBlockStartPos;
	int		m_nyPos; 
	int		m_nOffset;
	CRect	m_rcClient;
	CRect   m_rcScreen;
	UINT	m_nBlocksPerRow;
	UINT	m_nBlocksPerColumn;
	UINT	m_nNumberofBlocks;

	UINT    m_ulBlockWidth;
	UINT    m_ulBlockHeight;

	CBrush	m_backgroundBrush;
	CArray	<COLORREF, COLORREF> m_crColor;
	CArray	<COLORREF, COLORREF> m_crBKColor;
	CArray	<UINT, UINT> m_iSelectFlag;
	std::vector<BlockPos> m_lSelIndexv;
public:
    std::vector<BlockPos> m_lSelIndexvCopy;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKERCTRL_H__AD4BC4E3_7750_11D4_8718_008048CA4A77__INCLUDED_)
