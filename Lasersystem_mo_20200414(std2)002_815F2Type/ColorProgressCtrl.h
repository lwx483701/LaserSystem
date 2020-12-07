#if !defined(AFX_COLORPROGRESSCTRL_H__9CCAF7DA_D6E5_4898_8584_957537738597__INCLUDED_)
#define AFX_COLORPROGRESSCTRL_H__9CCAF7DA_D6E5_4898_8584_957537738597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorProgressCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorProgressCtrl window

class CColorProgressCtrl : public CProgressCtrl
{
// Construction
public:
	CColorProgressCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorProgressCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRange(long iLow =0,long iUpper = 120);
	void SetTextColor(COLORREF color)	{m_clrText=color;}
	void SetBkColor(COLORREF color)		{m_clrBkGround=color;}
	void SetStartColor(COLORREF color)	{m_clrStart=color;}
	void SetEndColor(COLORREF color)	{m_clrEnd=color;}
	int SetPos(long iPos);
	virtual ~CColorProgressCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorProgressCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG
void DrawGradient(CPaintDC *pDC,const RECT& rectClient,const int & nMaxWidth);
	DECLARE_MESSAGE_MAP()
private:
	long m_iLower;
	long	m_iUpper;
	long m_iCurrentPosition;
	COLORREF m_clrText;
	COLORREF m_clrBkGround;
	COLORREF m_clrStart;
	COLORREF m_clrEnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPROGRESSCTRL_H__9CCAF7DA_D6E5_4898_8584_957537738597__INCLUDED_)
