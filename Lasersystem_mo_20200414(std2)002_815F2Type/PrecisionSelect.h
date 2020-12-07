#if !defined(AFX_PRECISIONSELECT_H__821D6687_9EA9_4DC6_A79A_EC6FB698DC27__INCLUDED_)
#define AFX_PRECISIONSELECT_H__821D6687_9EA9_4DC6_A79A_EC6FB698DC27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrecisionSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrecisionSelect dialog

class CPrecisionSelect : public CDialog
{
// Construction
public:
	CPrecisionSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrecisionSelect)
	enum { IDD = IDD_DIALOG_PRECISION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrecisionSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrecisionSelect)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRECISIONSELECT_H__821D6687_9EA9_4DC6_A79A_EC6FB698DC27__INCLUDED_)
