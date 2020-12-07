// LoginView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "LoginView.h"
#include "LoginDialog.h"
#include "MainFrm.h"
#include "IngredientInfoView.h"
#include "OperateControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

extern CIngredientInfoView *pIngredientInfoView;
IMPLEMENT_DYNCREATE(CLoginView, TVisualFormView)

CLoginView::CLoginView()
:TVisualFormView(CLoginView::IDD)
{
	//{{AFX_DATA_INIT(CLoginView)
	
	m_strUserName = _T("");
	m_strPasswordC = _T("");
	m_strPassword = _T("");
	m_CurUser = _T("");
	m_UserIdCard = _T("");
	//}}AFX_DATA_INIT
}

CLoginView::~CLoginView()
{

}

void CLoginView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginView)
	DDX_Control(pDX, IDC_ST_CURUSER, m_stCurUser);
	DDX_Control(pDX, IDC_EDT_USERNAME, m_edtUserName);
	DDX_Control(pDX, IDC_EDT_PASSWORDC, m_edtPasswordC);
	DDX_Control(pDX, IDC_EDT_PASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_CMB_USERLEVEL, m_cmbUserLevel);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDT_PASSWORDC, m_strPasswordC);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_ST_CURUSER, m_CurUser);
	DDX_Text(pDX, IDC_EDIT_USERIDCARD, m_UserIdCard);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_LOGINGRID, m_GridLogin);
}

BEGIN_MESSAGE_MAP(CLoginView, TVisualFormView)
	//{{AFX_MSG_MAP(CLoginView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ADD, OnAddUser)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_BTN_DEL, OnDeleteUserInfo)
	ON_BN_CLICKED(IDC_BTN_MODI, OnModiPassword)
	ON_CBN_SELCHANGE(IDC_CMB_USERLEVEL, OnSelchangeComboUserright)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginView diagnostics

#ifdef _DEBUG
void CLoginView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLoginView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoginView message handlers
int CLoginView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_GridLogin.SetEditable(FALSE);
	m_GridLogin.SetListMode(TRUE);
	m_GridLogin.SetHeaderSort(FALSE);
	m_GridLogin.EnableDragAndDrop(TRUE);

	TRY 
	{
		m_GridLogin.SetRowCount(GetDoc().GetLoginUserNum()+1);   //m_nRows
		m_GridLogin.SetColumnCount(3);  //m_nCols
		m_GridLogin.SetFixedRowCount(1);//m_nFixRows;
		//m_GridLogin.SetFixedColumnCount(1);//m_nFixCols;
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
    END_CATCH

    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
    dwTextStyle |= DT_END_ELLIPSIS;
#endif

	FillGridWithText();

	m_GridLogin.SetRowResize(FALSE);
	m_GridLogin.SetColumnResize(FALSE);

	m_stCurUser.SubclassDlgItem(IDC_ST_CURUSER, this);
	return 0;
}

void CLoginView::FillGridWithText()
{
    char buf[32];
 
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
 	
	char szRead[30]={""};

	for (int row = 0; row < m_GridLogin.GetRowCount(); row++)
	{
		m_GridLogin.SetRowHeight(row, 30);
		
		for (int col = 0; col < m_GridLogin.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			if (row < 1)//m_nFixRows
            {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				switch(col)
				{
				case 1:
					strncpy(szRead,GetLang().GetWarningText(10079),30);
					Item.szText =szRead ;//"用户"
					break;
				case 2:
					strncpy(szRead,GetLang().GetWarningText(10080),30);
					Item.szText = szRead;//"权限"
					break;
				}
			}
            else if (col < 1) //m_nFixCols
            {
			    sprintf(buf,"%d",row);
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				Item.szText = buf;
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				Item.szText = GetCurCellText(row,col);
			}
			m_GridLogin.SetItem(&Item);
//          m_GridLogin.SetColumnWidth(col,120);
			if(col==0)												//20160907
			     m_GridLogin.SetColumnWidth(col,60);
			else
				m_GridLogin.SetColumnWidth(col,192);
			m_GridLogin.RedrawCell(row,col);
		}
	}
}

CString CLoginView::GetCurCellText(UINT nRow, UINT nCol)
{
    CString str,strName,strLevel;

	UserInfo ui;

	char szRead[30]={""};
	if(nRow<m_GridLogin.GetRowCount())
	{
		ui = GetDoc().GetLoginUserInfo(nRow-1);
		if(nCol==1)
		{
		   str = ui.strUserName;
		}
		else if(nCol == 2)
		{
			switch(ui.nLevel)
			{
			case 0:
				strncpy(szRead,GetLang().GetWarningText(10081),30);
				str = szRead;//"普通用户"
				break;
			case 1:
				strncpy(szRead,GetLang().GetWarningText(10082),30);
				str = szRead;//"高级用户"
				break;
			case 2:
				strncpy(szRead,GetLang().GetWarningText(10083),30);
				str = szRead;//"系统用户"
				break;
			default:
				strncpy(szRead,GetLang().GetWarningText(10084),30);
				str = szRead;//"未知用户"
				break;
			}
		}
	}

	return str;
}

void CLoginView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if(bActivate)
	   SetTimer(2,500,NULL);
	else
		KillTimer(2);

	int nLevel = GetDoc().GetCurUserLevel();
	m_CurUser = GetDoc().GetCurUserName();
	if(GetControl().GetRunState()!=CControl::END)
	{
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_MODI)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			GetDlgItem(IDC_EDT_USERNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_PASSWORD)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_PASSWORDC)->EnableWindow(FALSE);
			GetDlgItem(IDC_CMB_USERLEVEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_MODI)->EnableWindow(FALSE);
		}	
		else if(nLevel==SystemDoc::SUPEROR)  //高级
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_EDT_USERNAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_PASSWORD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_PASSWORDC)->EnableWindow(TRUE);
			GetDlgItem(IDC_CMB_USERLEVEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_MODI)->EnableWindow(TRUE);
		}
	}

	UpdateData(FALSE);
	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CLoginView::OnTimer(UINT nIDEvent) 
{
    static int oldrow =-1;
	int row = m_GridLogin.GetFocusCell().row;
	if((oldrow!=row)&&(row>0))
	{
	    if(row<m_GridLogin.GetRowCount())
		{
			m_UserIdCard = GetDoc().GetLoginUserInfo(row-1).strUserName;
	        m_strUserName = GetDoc().GetLoginUserInfo(row-1).strUserName;
            m_strPassword = GetDoc().GetLoginUserInfo(row-1).strPassword;
			m_strPasswordC = GetDoc().GetLoginUserInfo(row-1).strPassword;
			m_cmbUserLevel.SetCurSel(GetDoc().GetLoginUserInfo(row-1).nLevel);	
			if (GetDoc().GetLoginUserInfo(row-1).nLevel == SystemDoc::PRIMARY)
			{
				GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(TRUE);
				GetDlgItem(IDC_EDIT_USERIDCARD)->ShowWindow(TRUE);

				GetDlgItem(IDC_EDT_USERNAME)->ShowWindow(FALSE);
				GetDlgItem(IDC_EDT_PASSWORD)->ShowWindow(FALSE);
				GetDlgItem(IDC_EDT_PASSWORDC)->ShowWindow(FALSE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
				GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
				GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_EDT_USERNAME)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_PASSWORD)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_PASSWORDC)->EnableWindow(TRUE);
				GetDlgItem(IDC_CMB_USERLEVEL)->EnableWindow(TRUE);
			}
		}

		oldrow = row;
		UpdateData(FALSE);
//		Invalidate();
	}

	TVisualFormView::OnTimer(nIDEvent);
}

void CLoginView::OnAddUser() 
{
    UpdateData();
	char buf[32];
	char ez[256]={""};//ly 20110404
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;

	int userRightIndex = m_cmbUserLevel.GetCurSel();
	if(userRightIndex < 0)
	{
		strncpy(ez,"请选择新增角色!",256);
		AfxMessageBox(ez);
		return;
	}
	
	if((m_cmbUserLevel.GetCurSel()>=GetDoc().GetCurUserLevel()) || (m_cmbUserLevel.GetCurSel()<0))
	{
		strncpy(ez,GetLang().GetWarningText(12006),256);
		AfxMessageBox(ez);//"请修改用户权限"//,不能创建
		GetLog().Append_pro(10018,20012);//"请修改用户权限"," 登陆"
		return ;
	}
	if(userRightIndex == SystemDoc::PRIMARY)//操作员
	{
		if (m_UserIdCard == "")
		{
			strncpy(ez,"请输入员工卡号!",256);
			AfxMessageBox(ez);
			return;
		}
		
		for(int n=0;n<GetDoc().GetLoginUserNum();++n)
		{
			if(m_strUserName == GetDoc().GetLoginUserInfo(n).strUserName)
			{
				strncpy(ez,"员工卡号已经存在!",256);
				AfxMessageBox(ez);
				GetLog().Append_pro(10019,20012);//"员工卡号已经存在"," 登陆"
				return ;
			}
		}
		CLoginDialog login;
		bool result = login.UserVerify(m_UserIdCard);
		if(!result)
		{
			AfxMessageBox("新增用户验证失败，请重新添加!");
			GetLog().Append_pro("新增用户失败","人员新增",m_UserIdCard);
			m_UserIdCard = _T("");
			UpdateData(FALSE);
			return;
		}
		else
		{
			GetDoc().AddUserInfo(UserInfo(m_cmbUserLevel.GetCurSel(),m_UserIdCard,m_UserIdCard));
			//m_GridLogin.InsertRow(ltoa(m_GridLogin.GetRowCount()-2,buf,10),m_GridLogin.GetRowCount()-2);
			m_GridLogin.InsertRow(buf);
			FillGridWithText();
			m_GridLogin.SetSelectedRange(m_GridLogin.GetRowCount()-1,0,m_GridLogin.GetRowCount()-1,2);
		}
	}
	else
	{
		if(m_strUserName =="")
		{
			strncpy(ez,GetLang().GetWarningText(12003),256);
			AfxMessageBox(ez);//"请输入用户名"
			GetLog().Append_pro(10015,20012);//"请输入用户名"," 登陆"
			return ;
		}
		if(m_strPassword != m_strPasswordC)
		{
			strncpy(ez,GetLang().GetWarningText(12004),256);
			AfxMessageBox(ez);//"两次密码不一致"
			GetLog().Append_pro(10016,20012);//"两次密码不一致"," 登陆"
			return ;
		}
		if(m_strPassword =="")
		{
			strncpy(ez,GetLang().GetWarningText(12005),256);
			AfxMessageBox(ez);//"请输入密码"
			GetLog().Append_pro(10017,20012);//"请输入密码"," 登陆"
			return ;
		}
		for(int n=0;n<GetDoc().GetLoginUserNum();++n)
		{
			if(m_strUserName == GetDoc().GetLoginUserInfo(n).strUserName)
			{
				strncpy(ez,GetLang().GetWarningText(12007),256);
				AfxMessageBox(ez);//"用户名已经存在"
				GetLog().Append_pro(10019,20012);//"用户名已经存在"," 登陆"
				return ;
			}
		}
		GetDoc().AddUserInfo(UserInfo(m_cmbUserLevel.GetCurSel(),m_strUserName,m_strPassword));
		//m_GridLogin.InsertRow(ltoa(m_GridLogin.GetRowCount()-2,buf,10),m_GridLogin.GetRowCount()-2);
		m_GridLogin.InsertRow(buf);
		FillGridWithText();
		m_GridLogin.SetSelectedRange(m_GridLogin.GetRowCount()-1,0,m_GridLogin.GetRowCount()-1,2);
	}

#ifdef SENTINAL															//20180126
    GetDoc().SaveUserInfoInSentinal();	
#else
    GetDoc().SaveUserInfo();
#endif

	m_UserIdCard="";
	m_strUserName="";//ly add 20111101
	m_strPassword="";
	m_strPasswordC="";
	m_cmbUserLevel.SetCurSel(-1);

	UpdateData(FALSE);
}

void CLoginView::OnLogin() 
{
	CLoginDialog login;
	if(login.DoModal()==IDOK )
	{
		m_CurUser=GetDoc().GetCurUserName();
		long curLevel=GetDoc().GetCurUserLevel();
		
		bool hasExit = false;
		//循环遍历所有用户进行比较
		for(int n=0; n<GetDoc().GetLoginUserNum();++n)
		{	
			if (GetDoc().GetLoginUserInfo(n).strUserName == m_CurUser)
			{
				hasExit = true;
				break;
			}
			else
			{
				continue;
			}	
		}
		char buf[30] = "";
		int row = m_GridLogin.GetRowCount()-1;//末尾行
		//切换系统不存在的普通用户，此时需要在末尾新增一行
		if (curLevel == SystemDoc::PRIMARY)		
		{
			if (!hasExit)
			{
				GetDoc().AddUserInfo(UserInfo(curLevel,m_CurUser,m_CurUser));
				m_GridLogin.InsertRow(ltoa(m_GridLogin.GetRowCount()-2,buf,10),m_GridLogin.GetRowCount()-2);
				//m_GridLogin.InsertRow(buf);
				FillGridWithText();
				m_GridLogin.SetSelectedRange(m_GridLogin.GetRowCount()-1,0,m_GridLogin.GetRowCount()-1,m_GridLogin.GetColumnCount()-1);                                                                                                                                                                
			}
		}
		//切换成功后需要清空工单信息
		//pIngredientInfoView->m_strLotID = "";
		//pIngredientInfoView->ClearAllContent();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      		pIngredientInfoView->m_strResponse.Format("");	
	}
	else
	{    
		return ;
	}
	
    UpdateData(FALSE);
}

void CLoginView::OnDeleteUserInfo() 
{
	char ez[256]={""};//ly 20110404
	int row = m_GridLogin.GetFocusCell().row;
	if(row<1||row>m_GridLogin.GetRowCount()-1)
	{
		strncpy(ez,GetLang().GetWarningText(12008),256);
	   AfxMessageBox(ez);//"请先选择用户再删除"
	   GetLog().Append_pro(10020,20012);//"请先选择用户再删除"," 登陆"
	   return ;
	}

	UpdateData();

	if(m_strUserName==GetDoc().GetCurUserName())
	{
		strncpy(ez,GetLang().GetWarningText(12009),256);
	    AfxMessageBox(ez);//"不能删除登入用户"
		GetLog().Append_pro(10021,20012);//"不能删除登入用户"," 登陆"
		return ;
	}
    
	if((GetDoc().GetLoginUserInfo(row-1).nLevel>=GetDoc().GetCurUserLevel())&&GetDoc().GetCurUserName()!="Administrator")
	{
		strncpy(ez,GetLang().GetWarningText(12010),256);
	    AfxMessageBox(ez);//"没有权限删除选定用户"
		GetLog().Append_pro(10022,20012);//"没有权限删除选定用户"," 登陆"
		return ;
	}

	if(row<m_GridLogin.GetRowCount())
	{
		GetDoc().DeleteUserInfo(row-1);

#ifdef SENTINAL															//20180126
		GetDoc().SaveUserInfoInSentinal();	
#else
		GetDoc().SaveUserInfo();
#endif
		    
		m_GridLogin.DeleteRow(row);
		//m_GridLogin.SetSelectedRange(row,0,row,2);

		FillGridWithText();
		m_GridLogin.RedrawWindow();//ly add 20111028
	}
}

void CLoginView::OnModiPassword() 
{
	char ez[256]={""};//ly 20110404
    int row = m_GridLogin.GetFocusCell().row;
	if(row>0&&row<m_GridLogin.GetRowCount())
	{
		UpdateData();
		if(GetDoc().GetLoginUserInfo(row-1).strUserName!=m_strUserName)
		{
			strncpy(ez,GetLang().GetWarningText(12013),256);
			AfxMessageBox(ez);//"不可修改用户名"
			GetLog().Append_pro(10117,20012);//"不可修改用户名"," 登陆"
			return ;
		}

		if((GetDoc().GetLoginUserInfo(row-1).nLevel>=GetDoc().GetCurUserLevel())&&GetDoc().GetCurUserName()!="Administrator")
		{
			if(GetDoc().GetLoginUserInfo(row-1).strUserName!=GetDoc().GetCurUserName())
			{
			strncpy(ez,GetLang().GetWarningText(12011),256);
			AfxMessageBox(ez);//"没有权限修改选定用户密码"
			GetLog().Append_pro(10115,20012);//"没有权限修改选定用户密码"," 登陆"
			return ;
			}
		}

		if (GetDoc().GetLoginUserInfo(row-1).nLevel == SystemDoc::PRIMARY)
		{
			//strncpy(ez,GetLang().GetWarningText(12004),256);
			AfxMessageBox("普通用户不支持修改密码");//"普通不支持修改密码"
			//GetLog().Append_pro(10016,20012);//"两次密码不一致"," 登陆"
			return ;
		}

		if(m_strPassword != m_strPasswordC)
		{
			strncpy(ez,GetLang().GetWarningText(12004),256);
			AfxMessageBox(ez);//"两次密码不一致"
			GetLog().Append_pro(10016,20012);//"两次密码不一致"," 登陆"
			return ;
		}

		if(m_strPassword =="")
		{
			strncpy(ez,GetLang().GetWarningText(12005),256);
			AfxMessageBox(ez);//"请输入密码"
			GetLog().Append_pro(10017,20012);//"请输入密码"," 登陆"
			return ;
		}

		if(GetDoc().GetLoginUserInfo(row-1).nLevel!=m_cmbUserLevel.GetCurSel())
		{			
			strncpy(ez,GetLang().GetWarningText(12006),256);
			AfxMessageBox(ez);//"请修改用户权限"//,不能创建
			GetLog().Append_pro(10018,20012);//"请修改用户权限"," 登陆"
			return ;
		}
		
		GetDoc().SetUserPassword(row-1,m_strPassword);
#ifdef SENTINAL															//20180126
		GetDoc().SaveUserInfoInSentinal();	
#else
		GetDoc().SaveUserInfo();
#endif
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(12012),256);
		AfxMessageBox(ez);//"请先选择用户再修改"
		GetLog().Append_pro(10020,20012);//"请先选择用户再修改"," 登陆"
		return ;
	}
}

void CLoginView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("Loginview","IDC_STATIC1",szRead,20);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("Loginview","IDC_STATIC2",szRead,20);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("Loginview","IDC_STATIC3",szRead,20);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("Loginview","IDC_STATIC4",szRead,20);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("Loginview","IDC_STATIC5",szRead,20);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("Loginview","IDC_STATIC6",szRead,20);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("Loginview","IDC_BTN_ADD",szRead,20);
	SetDlgItemText(IDC_BTN_ADD,szRead);
	GetLang().GetUIText("Loginview","IDC_BTN_DEL",szRead,20);
	SetDlgItemText(IDC_BTN_DEL,szRead);
	GetLang().GetUIText("Loginview","IDC_BTN_MODI",szRead,20);
	SetDlgItemText(IDC_BTN_MODI,szRead);
	GetLang().GetUIText("Loginview","IDC_BTN_LOGIN",szRead,20);
	SetDlgItemText(IDC_BTN_LOGIN,szRead);
}

void CLoginView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();

	if(GetLang().GetCurLanguage()==1)
		SetUI();

	char szRead[20]={""};
	m_cmbUserLevel.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10054),20);
	m_cmbUserLevel.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10055),20);
	m_cmbUserLevel.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10056),20);
	m_cmbUserLevel.AddString(szRead);

	char buf[32];
	sprintf(buf,"%s",GetDoc().GetCurUserName());
	m_CurUser = buf;

	GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_USERIDCARD)->ShowWindow(FALSE);
    
	UpdateData(FALSE);
	// TODO: Add your specialized code here and/or call the base class
}

void CLoginView::OnSelchangeComboUserright()
{
	int userRightIndex = m_cmbUserLevel.GetCurSel();
	if(userRightIndex < 0)
	{
		return;
	}
	if(userRightIndex == 0)//操作员
	{

		GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_USERIDCARD)->ShowWindow(TRUE);

		GetDlgItem(IDC_EDT_USERNAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDT_PASSWORD)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDT_PASSWORDC)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERIDCARD)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDT_PASSWORD)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDT_PASSWORDC)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDT_USERNAME)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDT_PASSWORD)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDT_PASSWORDC)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(TRUE);

		m_strUserName = "";
        m_strPassword = "";
		m_strPasswordC = "";
	}
	UpdateData(FALSE);
}