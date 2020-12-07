// DlgRotate.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "DlgRotate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRotate dialog


CDlgRotate::CDlgRotate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRotate)
	m_Rotate = -1;
	//}}AFX_DATA_INIT
}


void CDlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRotate)
	DDX_Radio(pDX, IDC_ROTATE90, m_Rotate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRotate, CDialog)
	//{{AFX_MSG_MAP(CDlgRotate)
	ON_BN_CLICKED(IDC_ROTATE90, OnRotate90)
	ON_BN_CLICKED(IDC_ROTATE180, OnRotate180)
	ON_BN_CLICKED(IDC_ROTATE270, OnRotate270)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRotate message handlers

void CDlgRotate::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


void CDlgRotate::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlgRotate::OnRotate90() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetRotateFlag(m_Rotate);
}

void CDlgRotate::OnRotate180() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetRotateFlag(m_Rotate);
}

void CDlgRotate::OnRotate270() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetRotateFlag(m_Rotate);
}
