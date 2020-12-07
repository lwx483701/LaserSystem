#if !defined(AFX_MARKMAKE_H__58485708_B92D_487E_A43A_37039C34661D__INCLUDED_)
#define AFX_MARKMAKE_H__58485708_B92D_487E_A43A_37039C34661D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkMake.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarkMake dialog

class CMarkMake : public CDialog
{
// Construction
public:
	CMarkMake(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMarkMake)
	enum { IDD = IDD_MARKMAKE };
	int		m_iMarkType;
	BOOL	m_chkWhiteInBlack;
	int		m_iMarkSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkMake)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMarkMake)
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChkWhiteinblack();
	afx_msg void OnChangeEdtMarksize();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	unsigned char* pImageBMP;
	int imageSize;

	void MakeBMP();

public:
	void OnSave2();
	friend CMarkMake& GetCMarkMake();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKMAKE_H__58485708_B92D_487E_A43A_37039C34661D__INCLUDED_)
