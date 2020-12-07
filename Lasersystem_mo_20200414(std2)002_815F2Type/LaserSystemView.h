// LaserSystemView.h : interface of the CLaserSystemView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASERSYSTEMVIEW_H__FB5913C8_EAC1_4D8B_A0D7_E90433DB971F__INCLUDED_)
#define AFX_LASERSYSTEMVIEW_H__FB5913C8_EAC1_4D8B_A0D7_E90433DB971F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLaserSystemView : public CView
{
protected: // create from serialization only
	CLaserSystemView();
	DECLARE_DYNCREATE(CLaserSystemView)

// Attributes
public:
	CLaserSystemDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaserSystemView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLaserSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLaserSystemView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LaserSystemView.cpp
inline CLaserSystemDoc* CLaserSystemView::GetDocument()
   { return (CLaserSystemDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LASERSYSTEMVIEW_H__FB5913C8_EAC1_4D8B_A0D7_E90433DB971F__INCLUDED_)
