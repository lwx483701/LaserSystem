// PrecisionSelect.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "PrecisionSelect.h"

#include "SysParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrecisionSelect dialog


CPrecisionSelect::CPrecisionSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CPrecisionSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrecisionSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrecisionSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrecisionSelect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrecisionSelect, CDialog)
	//{{AFX_MSG_MAP(CPrecisionSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrecisionSelect message handlers

void CPrecisionSelect::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	GetDoc().m_CArrayGetPrecisionSelect.RemoveAll();
    for (int i=0;i<16;i++)
	{
		if (((CButton *)GetDlgItem(IDC_CHECK_PRECISION1+i))->GetCheck()==1)
		{
		
			GetDoc().m_CArrayGetPrecisionSelect.Add(i);
		}	   
	}	
	CDialog::OnOK();
}

BOOL CPrecisionSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton *)GetDlgItem(IDC_CHECK_PRECISION1))->SetCheck(1);	
	for (int i=0;i<15;i++)
	{
	   ((CButton *)GetDlgItem(IDC_CHECK_PRECISION2+i))->SetCheck(0);	
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
