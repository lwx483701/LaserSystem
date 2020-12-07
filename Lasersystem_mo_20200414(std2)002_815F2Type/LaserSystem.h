// LaserSystem.h : main header file for the LASERSYSTEM application
//

#if !defined(AFX_LASERSYSTEM_H__3C1A3160_8E14_4319_B186_CA87150FBC29__INCLUDED_)
#define AFX_LASERSYSTEM_H__3C1A3160_8E14_4319_B186_CA87150FBC29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "WarningInfo.h"


/////////////////////////////////////////////////////////////////////////////
// CLaserSystemApp:
// See LaserSystem.cpp for the implementation of this class
//

class CLaserSystemApp : public CWinApp
{
public:
	CLaserSystemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaserSystemApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLaserSystemApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

 
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LASERSYSTEM_H__3C1A3160_8E14_4319_B186_CA87150FBC29__INCLUDED_)
