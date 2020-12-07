#if !defined(AFX_FILEPOINTVIEW_H__738E5AB3_90D9_4B8F_8562_3410026BB56C__INCLUDED_)
#define AFX_FILEPOINTVIEW_H__738E5AB3_90D9_4B8F_8562_3410026BB56C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFilePointView view

#include "Excellon.h"

class CFilePointView : public CScrollView
{
protected:
	CFilePointView() ;         // protected constructor used by dynamic creation
	virtual ~CFilePointView();

	DECLARE_DYNCREATE(CFilePointView)

// Attributes
public:
	enum CZoomDrag {NONE, ZOOMIN, RECTZOOMIN, ZOOMOUT, DRAG};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilePointView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawDocFrame(CDC *pDC);
	void DrawStringText(CDC *pDC);
	void DrawFid(CDC *pDC);
	void DrawInnerFid(CDC *pDC);
	void DrawPoint(CDC *pDC);

	void DrawLocalMark(CDC *pDC,int index);
	void DrawLocalMarkSubArea(CDC *pDC,int index);
	void DrawOtherSubArea(CDC *pDC);
	void DrawSALocalMark(CDC *pDC,int index);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFilePointView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnReflashPoint(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void ZoomReset();
	void ZoomOut();
	void ZoomIn();
	void GetDrawTextRect(TextDir td,TextPosition tp,Coord TxtPos,RECT &rect,float tempScal);

	CRD m_xoff;
	CRD m_yoff;
	float m_Scal;
	BOOL isShowPathAndBE;

	double m_ScalDraw;

	long  m_Zoom;
	BOOL LButtomDown;
    CPoint m_ptdownInView,m_ptlastInView,m_ptZoomInFirst,m_ptZoomInLast;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEPOINTVIEW_H__738E5AB3_90D9_4B8F_8562_3410026BB56C__INCLUDED_)
