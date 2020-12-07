// LaserSystemDoc.h : interface of the CLaserSystemDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASERSYSTEMDOC_H__8DA0C945_2DF9_48C6_9001_FB451E4832B4__INCLUDED_)
#define AFX_LASERSYSTEMDOC_H__8DA0C945_2DF9_48C6_9001_FB451E4832B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLaserSystemDoc : public CDocument
{
protected: // create from serialization only
	CLaserSystemDoc();
	DECLARE_DYNCREATE(CLaserSystemDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaserSystemDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLaserSystemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLaserSystemDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LASERSYSTEMDOC_H__8DA0C945_2DF9_48C6_9001_FB451E4832B4__INCLUDED_)
