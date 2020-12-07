// ProcLogin_FZ.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "ProcLogin_FZ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcLogin_FZ dialog


CProcLogin_FZ::CProcLogin_FZ(CWnd* pParent /*=NULL*/)
	: CDialog(CProcLogin_FZ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcLogin_FZ)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProcLogin_FZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcLogin_FZ)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcLogin_FZ, CDialog)
	//{{AFX_MSG_MAP(CProcLogin_FZ)
	ON_BN_CLICKED(IDC_BTN_FZ_STARTUP, OnBtnFzStartup)
	ON_BN_CLICKED(IDC_BTN_FZ_VERIFY, OnBtnFzVerify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcLogin_FZ message handlers

void CProcLogin_FZ::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CProcLogin_FZ::OnBtnFzStartup() 
{
	// TODO: Add your control notification handler code here
	
}

void CProcLogin_FZ::OnBtnFzVerify() 
{
	// TODO: Add your control notification handler code here
	
}
