// MODESWITCHDIALOG.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "MODESWITCHDIALOG.h"
#include "SysParameter.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MODESWITCHDIALOG dialog


MODESWITCHDIALOG::MODESWITCHDIALOG(CWnd* pParent /*=NULL*/)
	: CDialog(MODESWITCHDIALOG::IDD, pParent)
{
	//{{AFX_DATA_INIT(MODESWITCHDIALOG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strPassword = _T("");
}


void MODESWITCHDIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MODESWITCHDIALOG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_MOTHPASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(MODESWITCHDIALOG, CDialog)
	//{{AFX_MSG_MAP(MODESWITCHDIALOG)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MODESWITCHDIALOG message handlers


void MODESWITCHDIALOG::OnOK() 
{
	UpdateData();
	char ez[256]={""};
    CString strName;
    int nLevel = GetDoc().GetCurUserLevel();
	if (m_strPassword == "")
	{
		AfxMessageBox("���벻��Ϊ��");//"��ѡ���û�!"
		return;
	}
	//if(nLevel==SystemDoc::PRIMARY || nLevel==SystemDoc::SUPEROR)//����/�߼�
	//{
		//ѭ�����������û����е�½����Ƚ�
		for(int n=0; n<GetDoc().GetLoginUserNum();++n)
		{	
			//�͹���Ա������бȽ�
			if (GetDoc().GetLoginUserInfo(n).strUserName == "Administrator")
			{
				if(m_strPassword != GetDoc().GetLoginUserInfo(n).strPassword)
				{
					strncpy(ez,GetLang().GetWarningText(12002),256);
					AfxMessageBox(ez);//"�����ȷ!"
					return;
				}
			}
		}	
	//}
	CDialog::OnOK();
}


int MODESWITCHDIALOG::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

/*BOOL MODESWITCHDIALOG::OnInitDialog() 
{
	CDialog::OnInitDialog();

#ifdef SENTINAL															//20180126
    GetDoc().LoadUserInfoInSentinal();	
#else
    GetDoc().LoadUserInfo();
#endif

	if(GetDoc().GetLoginUserNum()==0)//ע�����û���û���¼ʱ��Ĭ���û�ΪAdministrator������Ĭ��123.ly add 20111028
		GetDoc().AddUserInfo(UserInfo(2,"Administrator","123"));

	BOOL UAdmin = false;//ly add 20111028
    for(int n=0; n<GetDoc().GetLoginUserNum();++n)
	{
	   m_cmbUserName.AddString(GetDoc().GetLoginUserInfo(n).strUserName);
	   if(GetDoc().GetLoginUserInfo(n).strUserName=="Administrator")
		   UAdmin=true;
	}

	if(UAdmin==false)//ly add 20111028
	{
		GetDoc().AddUserInfo(UserInfo(2,"Administrator","123"));
		m_cmbUserName.AddString("Administrator");
	}
//	
//	m_cmbUserName.SetCurSel(0);
	return TRUE;  
}
*/
