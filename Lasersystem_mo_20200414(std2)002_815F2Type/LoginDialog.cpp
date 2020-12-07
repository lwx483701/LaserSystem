// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "LoginDialog.h"
#include "SysParameter.h"
#include "Registry.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDialog)
	m_strPassword = _T("");
	m_strUserCard = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Control(pDX, IDC_COMBO_USERRIGHT, m_cmbUserRight);
	DDX_Control(pDX, IDC_COMBO1, m_cmbUserName);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_AMPLOYEEID, m_strUserCard);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_USERRIGHT, OnSelchangeComboUserright)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

void CLoginDialog::OnOK() 
{
	
	UpdateData();
	char ez[256]={""};//ly 20110404
    static int n=0;
    CString strName;
	bool result = false;
	int times = 0;
	int errCode = 0;
	
	int userRightIndex = m_cmbUserRight.GetCurSel();
	int nLoginIndex = m_cmbUserName.GetCurSel();
	CString combUserName;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(combUserName);
	if(userRightIndex < 0)
	{
		strncpy(ez,"��ѡ���ɫ!",256);
		AfxMessageBox(ez);
		GetLog().Append_pro("��ѡ���ɫ��½!","��½","");
		return;
	}

	if(userRightIndex == SystemDoc::PRIMARY)//����Ա
	{
		//��ȡ��Ա���ʹܿؿ���
		if (!GetDoc().GetSysUserControlSwitch())
		{
			AfxMessageBox("���豸δ������Ա���ʹܿ���,����Ա�޷���½,����ϵ����Ա��½����Ա���ʹܿؿ��غ���!");
			return;
		}
		if (combUserName == "" && m_strUserCard == "")
		{
			strncpy(ez,"���Ų���Ϊ��!",256);
			AfxMessageBox(ez);
			return;
		}
		CString userCardId = combUserName.IsEmpty()? m_strUserCard:combUserName;
		result = this->UserVerify(userCardId);
		if(!result)
		{
			AfxMessageBox("�û���֤ʧ�ܣ������µ�½!");
			GetLog().Append_pro("�û���֤ʧ��","��Ա��¼",userCardId);
			combUserName = _T("");
			m_strUserCard = _T("");
			UpdateData(FALSE);
			return;
		}
		else//��ͨ�û���֤�ɹ���������m_UserInfo��ʾ
		{
			if (combUserName.IsEmpty())
			{
				GetDoc().AddUserInfo(UserInfo(m_cmbUserRight.GetCurSel(),userCardId,userCardId));
			}
			GetDoc().SetCurUserLevel(userRightIndex);
			GetDoc().SetCurUserName(userCardId);
		}
	}
	else
	{
		if(nLoginIndex <GetDoc().GetLoginUserNum()&&nLoginIndex>=0)
		{	
			//ѭ�����������û����е�½����Ƚ�
			for(int n=0; n<GetDoc().GetLoginUserNum();++n)
			{	
				if (GetDoc().GetLoginUserInfo(n).strUserName == combUserName)
				{
					if(m_strPassword != GetDoc().GetLoginUserInfo(n).strPassword)
					{
						strncpy(ez,GetLang().GetWarningText(12002),256);
						AfxMessageBox(ez);//"�����ȷ!"
						GetLog().Append_pro(10014,20012);//"�����ȷ!","��½"
						return;
					}
					GetDoc().SetCurUserLevel(GetDoc().GetLoginUserInfo(n).nLevel);
					GetDoc().SetCurUserName(GetDoc().GetLoginUserInfo(n).strUserName);
				}
			}
		}
		else if(nLoginIndex == GetDoc().GetLoginUserNum())
		{
			if(m_strPassword != "")
			{
				strncpy(ez,GetLang().GetWarningText(12002),256);
				AfxMessageBox(ez);//"�����ȷ!"
				GetLog().Append_pro(10014,20012);//"�����ȷ!","��½"
				return;
			}
			GetDoc().SetCurUserLevel(2);
			GetDoc().SetCurUserName("Administrator");
			n=0;
		}
		else if(nLoginIndex<0)
		{
			//strncpy(ez,GetLang().GetWarningText(12008),256);
			AfxMessageBox("��ѡ���û�!");//"��ѡ���û�!"
			GetLog().Append_pro(10020,20012);//"��ѡ���û�!","��½"
			return;
		}
	}
	CDialog::OnOK();
}

int CLoginDialog::DoModal() 
{
	return CDialog::DoModal();
}

int CLoginDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CLoginDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(GetLang().GetCurLanguage()==1)
		SetUI();	

	GetDlgItem(IDC_STATIC67)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_AMPLOYEEID)->ShowWindow(FALSE);
	char szRead[20]={""};
	m_cmbUserRight.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10054),20);
	m_cmbUserRight.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10055),20);
	m_cmbUserRight.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10056),20);
	m_cmbUserRight.AddString(szRead);
	

#ifdef SENTINAL															//20180126
    GetDoc().LoadUserInfoInSentinal();	
#else
    GetDoc().LoadUserInfo();
#endif

	m_cmbUserName.ResetContent();

	{
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
	}
//	
//	m_cmbUserName.SetCurSel(0);
	return TRUE;  
}

void CLoginDialog::SetUI()//ly add 20120210
{
	char szRead[40] = {""};
	GetLang().GetUIText("LogIn","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("LogIn","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("LogIn","IDOK",szRead,40);
	SetDlgItemText(IDOK,szRead);
	GetLang().GetUIText("LogIn","IDCANCEL",szRead,40);
	SetDlgItemText(IDCANCEL,szRead);
}

void CLoginDialog::AddUserByLevel(int level)
{
	if(GetDoc().GetLoginUserNum()==0)//ע�����û���û���¼ʱ��Ĭ���û�ΪAdministrator������Ĭ��123.ly add 20111028
		GetDoc().AddUserInfo(UserInfo(2,"Administrator","123"));
	
	BOOL UAdmin = false;//ly add 20111028
    for(int n=0; n<GetDoc().GetLoginUserNum();++n)
	{
		switch(level) {
		case 0:
			if (GetDoc().GetLoginUserInfo(n).nLevel == SystemDoc::PRIMARY)
			{
				m_cmbUserName.AddString(GetDoc().GetLoginUserInfo(n).strUserName);
			}
			break;
		case 1:
			if (GetDoc().GetLoginUserInfo(n).nLevel == SystemDoc::SUPEROR)
			{
				m_cmbUserName.AddString(GetDoc().GetLoginUserInfo(n).strUserName);
			}
			break;
			
		case 2:
			if (GetDoc().GetLoginUserInfo(n).nLevel == SystemDoc::ADMIN)
			{
				m_cmbUserName.AddString(GetDoc().GetLoginUserInfo(n).strUserName);
			}
			break;
		default:
			break;	
		}
		if(GetDoc().GetLoginUserInfo(n).strUserName=="Administrator")
			UAdmin=true;
	}
	
	if(UAdmin==false)//ly add 20111028
	{
		GetDoc().AddUserInfo(UserInfo(2,"Administrator","123"));
		m_cmbUserName.AddString("Administrator");
	}
}

void CLoginDialog::OnSelchangeComboUserright() 
{
	// TODO: Add your control notification handler code here
	int userRightIndex = m_cmbUserRight.GetCurSel();
	if(userRightIndex < 0)
	{
		return;
	}
	//���ݽ�ɫɸѡ�û��������б�
	m_cmbUserName.ResetContent();
	if (userRightIndex == SystemDoc::SUPEROR)
	{
		AddUserByLevel(SUPERORUSER);
	}
	else if (userRightIndex == SystemDoc::ADMIN)
	{
		AddUserByLevel(ADMINUSER);
	}
	else
	{
		AddUserByLevel(ALLUSER);
	}
	
	if(userRightIndex == 0)//����Ա
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC67)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_AMPLOYEEID)->ShowWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC67)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_AMPLOYEEID)->ShowWindow(FALSE);
	}	
}


bool CLoginDialog::UserVerify(CString &userId)
{
	bool result = false;
	bool errCode = 0;
	Request req;
	Response rsp;
	CString uuid  = req.UuidGenerator();
	
	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y/%m/%d %H:%M:%S", localtime(&timep));
	
	CString machineSn = GetDoc().GetSysMachineSn();
	CString imesURL = GetDoc().GetSysImesURL();
	int timeout = GetDoc().GetSysTimeout();
	
	Json::Value reqSetting;
	reqSetting["ImesURL"] = Json::Value(imesURL);
	reqSetting["Timeout"] = Json::Value(timeout);
	req.setReqSetting(reqSetting);
	
	Json::Value reqHead;
	reqHead["eqp_id"] = Json::Value(machineSn);
	reqHead["time_stamp"] = Json::Value(currentTime);
	reqHead["trx_id"] = Json::Value(uuid);
	req.setReqHead(reqHead);
	
	Json::Value reqBody;
	reqBody["user_id"] = Json::Value(userId);
	req.setReqBody(reqBody);
	for (int i=0; i<3; i++)
	{
		errCode = GetWSInterfaceImplementor().UserVerify(req, rsp);
		if (errCode == STS_OK)
		{
			result = true;
			if (!rsp.getRspBody()["dept_id"].isNull())
			{
				GetDoc().SetCurUserDepartment(rsp.getRspBody()["dept_id"].asCString());
			}
			if (!rsp.getRspBody()["shift_id"].isNull())
			{
				GetDoc().SetCurUserShift(rsp.getRspBody()["shift_id"].asCString());
			}	
			break;
		}
		continue;
	}
	return result;
}