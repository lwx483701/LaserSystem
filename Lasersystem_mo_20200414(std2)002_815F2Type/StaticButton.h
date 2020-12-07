#if !defined(AFX_STATICBUTTON_H__4A73442D_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
#define AFX_STATICBUTTON_H__4A73442D_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticButton window

class CStaticButton : public CStatic
{
// Construction
public:
	CStaticButton();
	HBITMAP Up;
	HBITMAP Down;
	HCURSOR Select;
	HCURSOR No;
	BOOL bActive;
	BOOL Enable;
	CRgn* Region;
	static CRect rect;
	CToolTipCtrl* cTool;

// Attributes
public:
	void wSetBitmap(HBITMAP hBitmapUP, HBITMAP hBitmapDOWN, BOOL bAct = FALSE, CRgn* rgn = NULL);
	BOOL ChangeCursor(CPoint point);

	HBITMAP GetBitmapUp();
	HBITMAP GetBitmapDown();

	void SetEnable(BOOL B);
	BOOL GetEnable() { return Enable; };

	void SetRegion(CRgn* rgn);
	CRgn* GetRegion();

	void SetToolTip(LPSTR lpToolTip);
	CToolTipCtrl* GetToolTip() { return cTool; };

	void SetCursor(BOOL bSel, HCURSOR hCur);
	HCURSOR GetCursor(BOOL bSel);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICBUTTON_H__4A73442D_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
