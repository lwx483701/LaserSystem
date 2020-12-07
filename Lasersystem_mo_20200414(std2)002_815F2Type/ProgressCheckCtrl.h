#if !defined(AFX_PROGRESSCHECKCTRL_H__B963F23C_46EF_400E_BB0D_CB420B3120A1__INCLUDED_)
#define AFX_PROGRESSCHECKCTRL_H__B963F23C_46EF_400E_BB0D_CB420B3120A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressCheckCtrl.h : header file
//
#include <afxtempl.h>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CProgressCheckCtrl window
//#define BLANKED_BLOCKS_COLOR	  RGB(0,  0,   252)//蓝色
//#define BLANKED_BLOCKS_UNSELCOLOR RGB(255,100, 0  )//黄色
//#define BLANKED_BLOCKS_SELCOLOR	  RGB(55, 155, 100)//绿色
//#define BLANKED_BLOCKS_DIRLLCOLOR RGB(155,155, 100)//橄榄绿
//#define CHECKERCTRLBACKGROUND     RGB(255,128, 64)//黄色

#define BLANKED_BLOCKS_COLOR	  RGB(0,  0,   252)//蓝色
#define BLANKED_BLOCKS_UNSELCOLOR RGB(255,100, 0  )//黄色
#define BLANKED_BLOCKS_SELCOLOR	  RGB(0, 255, 0)//亮绿色
#define BLANKED_BLOCKS_DIRLLCOLOR RGB(155,155, 100)//橄榄绿//无用
#define CHECKERCTRLBACKGROUND     RGB(255,128, 64)//黄色//无用

class CProgressCheckCtrl : public CWnd
{
	// Construction
public:
	CProgressCheckCtrl();
	BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID);
		// Attributes
public:
struct Block
{
	Coord point;
	long   width;
	long   high;
	COLORREF ColorBlock;
	Block(const Coord pt = Coord(0,0),const long lWidth = 0,const long lHigh = 0,const COLORREF crColorBlock=0)
	{
		this->point = pt;
		this->width  =lWidth;
		this->high = lHigh;
		this->ColorBlock = crColorBlock;
	}
	
};


// Operations
public:
void SetBlockWidth(UINT nWidth,UINT nR,UINT nC);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressCheckCtrl)
	public:
	  
	//}}AFX_VIRTUAL

		// Implementation
	public:
		void RemoveAllData();
		void SetBlockColor(int nIndex,COLORREF crColor);
		void Update(CPoint ptCenter,long width,long high);
		void Update(CRect lrect,const COLORREF crColor);
		void Refresh();
		void SetBlock(int nIndex,const Coord iPoint,const long lWidth,const long lHigh,const COLORREF crColor);
		virtual ~CProgressCheckCtrl();
		void DrawBlock(int iBlocknum,const Coord crd,const long lWidth,const long lHigh, CBrush &brush, CDC &dc);

	// Generated message map functions
protected:
	//{{AFX_MSG(CProgressCheckCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
//变量
	CUIntArray m_lSelIndexv;
	CArray <Block,Block&> m_Array;
	CArray <CRect,CRect&> m_RectArray;
	CArray	<COLORREF, COLORREF> m_crColor;
	CRect m_rcClient;
//	CBrush	m_BlockColorBrush;
	CBrush m_backgroundBrush;
	COLORREF m_BlockColor;
	CPoint m_CenterPos;
	long m_BlockWidth;
	long m_BlockHigh;
    long m_ulBlockWidth;
	long m_ulBlockHeight;
	CRect   m_rcScreen;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSCHECKCTRL_H__B963F23C_46EF_400E_BB0D_CB420B3120A1__INCLUDED_)
