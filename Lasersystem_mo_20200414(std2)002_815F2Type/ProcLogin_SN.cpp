// ProcLogin_SN.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "SysParameter.h"
#include "ProcLogin_SN.h"
#include "FileInfoSettingView.h"
#include "ToolUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFileInfoSettingView *pFileInfoSettingView;
/////////////////////////////////////////////////////////////////////////////
// CProcLogin_SN dialog


CProcLogin_SN::CProcLogin_SN(CWnd* pParent /*=NULL*/)
	: CDialog(CProcLogin_SN::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcLogin_SN)
	m_strAmployeeID_SN = _T("");
	m_strLOTID_SN = _T("");
	m_strPRODID_SN = _T("");
	m_strDEPTID_SN = _T("");
	m_strProgram_SN = _T("");
	m_nPCBCount = 0;
	//}}AFX_DATA_INIT
}


void CProcLogin_SN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcLogin_SN)
	DDX_Text(pDX, IDC_EDT_SN_AMPLOYEEID, m_strAmployeeID_SN);
	DDX_Text(pDX, IDC_EDT_SN_AMPLOYEEDEPT, m_strDEPTID_SN);
	DDX_Text(pDX, IDC_EDT_SN_LOTID, m_strLOTID_SN);
	DDX_Text(pDX, IDC_EDT_SN_PRODID, m_strPRODID_SN);
	DDX_Text(pDX, IDC_EDT_SN_PROGRAM, m_strProgram_SN);
	DDX_Text(pDX, IDC_EDT_SN_PCBCOUNT, m_nPCBCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcLogin_SN, CDialog)
	//{{AFX_MSG_MAP(CProcLogin_SN)
	ON_BN_CLICKED(IDOK, OnSave)
	ON_BN_CLICKED(IDC_BTN_SN_OPENFILE, OnSNOpenFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcLogin_SN message handlers

void CProcLogin_SN::OnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if((m_strProgram_SN=="")||(m_strLOTID_SN=="")||(m_strPRODID_SN=="")||(m_strDEPTID_SN=="")||(m_strAmployeeID_SN==""))			//20180118 取消
	{
		AfxMessageBox("资料输入不完整，请重新输入!");
		return;
	}
	CString fix,inc;
	ToolUtil::SplitStringGenerateFixAndInc(m_strLOTID_SN,fix,inc);
	
	GetDoc().SetLOTIDFix(m_strLOTID_SN);
	GetDoc().SetLOTIDInc(inc);

//	int nSel = AfxMessageBox("请确认是否保存输入资料？",MB_YESNO);		
//	if(nSel == IDNO )
//		return;

//	GetDoc().SetSysProcFileName(m_strProgram_SN);

	GetDoc().SetSysProcLOTID(m_strLOTID_SN);
	GetDoc().SetSysPCBCount(m_nPCBCount);							//20180118
	GetDoc().SetSysProcPRODID(m_strPRODID_SN);
	GetDoc().SetSysUserDEPTID(m_strDEPTID_SN);

	GetDoc().AddUserInfo(UserInfo(0,m_strAmployeeID_SN,m_strAmployeeID_SN));
	GetDoc().SetCurUserLevel(0);
	GetDoc().SetCurUserName(m_strAmployeeID_SN);
	GetDoc().SetCurUserDepartment(m_strDEPTID_SN);

	struct tm *local;
	time_t long_time;
	time( &long_time );
	local = localtime( &long_time );
	int h = local->tm_hour;
	int m = local->tm_min;

	if(h>=8&&h<20)
	{
		GetDoc().SetCurUserShift("1");
	}
	else 
	{
		GetDoc().SetCurUserShift("2");
	}
	

	if(GetDoc().GetSysInfoDBMode()==1)								//20181212
	{
#ifdef USELOG
		CString setQty;																	
		setQty.Format("%d",GetDoc().GetSysPCBCount());
		GetLog().AppendSNWorkTable(m_strLOTID_SN,m_strAmployeeID_SN,m_strProgram_SN,setQty,COleDateTime::GetCurrentTime());
#endif
	}

	CDialog::OnOK();
}

BOOL CProcLogin_SN::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//	if((GetDoc().GetCurUserLevel()==SystemDoc::PRIMARY)&&((pMsg->message==WM_KEYDOWN)||(pMsg->message==WM_RBUTTONDOWN)))	//20180118 取消
//		return true;

	return CDialog::PreTranslateMessage(pMsg);
}


void CProcLogin_SN::OnSNOpenFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
/*																//20161129 如果字符串为空，则打开文件选择对话框
	if(m_strProgram_SN=="")
	{
		AfxMessageBox("文件名不能为空!");
		return;
	}
*/
	//GetDoc().SetSysProcFileName(m_strProgram_SN);

	if(GetDoc().GetSysInfoDBMode()==2)							//20181212
		m_strProgram_SN="";
	pFileInfoSettingView->SetDlgItemText(IDC_EDT_SELECTFILE,"");
	GetDoc().SetFileIsOptimized(false);							//20181225

	pFileInfoSettingView->SelectFile(m_strProgram_SN);

	GetDoc().SetSysSNProcedPCBNum(0);

	m_strProgram_SN = GetDoc().GetFileName();
	m_nPCBCount=0;												//20180118
	m_strLOTID_SN="";
	GetDoc().SetSysPCBCount(m_nPCBCount);
	GetDoc().SetSysProcLOTID(m_strLOTID_SN);

	UpdateData(false);
}

