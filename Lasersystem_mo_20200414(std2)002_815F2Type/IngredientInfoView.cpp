// IngredientInfoView.cpp : implementation file
//

#include "stdafx.h"
#include <fstream>
#include "lasersystem.h"
#include "IngredientInfoView.h"
#include "operatecontrol.h"
#include "ImesSettingDialog.h"
#include "FileInfoSettingView.h"
#include "MainFrm.h"
#include "MarkMake.h"	
#include "MODESWITCHDIALOG.h"
#include "ToolUtil.h"
#include "ToolParaView.h"
#include "PointcontrlView.h"
#include <direct.h>
#include <algorithm>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFileInfoSettingView *pFileInfoSettingView;
/////////////////////////////////////////////////////////////////////////////
// CIngredientInfoView
#define CELLWIDTH	58
#define CELLHEIDTH	32
#define BK_GREENCOLOR	RGB(0, 255, 0)
#define BK_REDCOLOR		RGB(255, 0, 0)

IMPLEMENT_DYNCREATE(CIngredientInfoView, TVisualFormView)
CIngredientInfoView *pIngredientInfoView;

CIngredientInfoView::CIngredientInfoView()
	: TVisualFormView(CIngredientInfoView::IDD)
{
	//{{AFX_DATA_INIT(CIngredientInfoView)
	m_beginLabel = _T("");
	m_strCurUser = _T("");
	m_strSsemp = _T("");
	m_strLotID = _T("");
	m_strResponse = _T("");
	m_bModeSwitch = TRUE;
	m_lHeartbeatFreq = 0;
	m_bisLoading = FALSE;
	//}}AFX_DATA_INIT
}

CIngredientInfoView::~CIngredientInfoView()
{
	 DWORD code;                               
	 GetExitCodeThread(statusThread->m_hThread, &code);
	 if(code == STILL_ACTIVE)
     {  
		TRACE("statusThread线程需要释放资源\n");
     }
}

void CIngredientInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIngredientInfoView)

	DDX_Control(pDX, IDC_BTN_IMESSETTING, m_btnImesSetting);
	DDX_Control(pDX, IDC_EDIT_STAFFID, m_staCurUser);
	DDX_Text(pDX, IDC_EDIT_STAFFID, m_strCurUser);
	DDX_Control(pDX, IDC_STA_SSEMP, m_staSsemp);
	DDX_Text(pDX, IDC_STA_SSEMP, m_strSsemp);
	DDX_Control(pDX, IDC_EDT_LOTID, m_staLotID);
	DDX_Text(pDX, IDC_EDT_LOTID, m_strLotID);
	DDX_Control(pDX, IDC_EDIT_RESPONSE, m_staResponse);
	DDX_Text(pDX, IDC_EDIT_RESPONSE, m_strResponse);
	DDX_Control(pDX, IDC_BTN_PATTERNSWITCH, m_btnModeSwitch);
	DDX_Control(pDX, IDC_BTN_GETINGREDIENTS, m_btnGetIngredients);

	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_GRIDPROCPARA, m_GridProcPara);

}


BEGIN_MESSAGE_MAP(CIngredientInfoView, TVisualFormView)
	//{{AFX_MSG_MAP(CIngredientInfoView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_IMESSETTING, OnImesSetting)
	ON_BN_CLICKED(IDC_BTN_PATTERNSWITCH, OnModeSwitch)
	ON_BN_CLICKED(IDC_BTN_GETINGREDIENTS, OnGetIngredients)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRIDPROCPARA, SetEditDisabledBegin)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRIDPROCPARA, SetEditDisabledEnd)
	ON_MESSAGE(WM_USERUPDATERESPONSE,OnUpdateResponse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIngredientInfoView diagnostics

#ifdef _DEBUG
void CIngredientInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIngredientInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIngredientInfoView message handlers
int CIngredientInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	pIngredientInfoView=this;

	m_GridProcPara.SetEditable(TRUE);
	m_GridProcPara.SetListMode(TRUE);
	m_GridProcPara.SetHeaderSort(FALSE);
	m_GridProcPara.EnableDragAndDrop(TRUE);
	m_GridProcPara.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	TRY 
	{
		m_GridProcPara.SetRowCount(m_itemKeyValueV.size()+1);
		m_GridProcPara.SetColumnCount(3);
		m_GridProcPara.SetFixedRowCount(1);
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

	m_GridProcPara.SetRowResize(FALSE);
	m_GridProcPara.SetColumnResize(FALSE);

	return 0;
}

void CIngredientInfoView::FillGridWithText()
{
    char buf[32];
 
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
 	
	char szRead[100]={""};

	for (int row = 0; row < m_GridProcPara.GetRowCount(); row++)
	{
		m_GridProcPara.SetRowHeight(row, 30);
		
		for (int col = 0; col < m_GridProcPara.GetColumnCount(); col++)
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
					strncpy(szRead,GetLang().GetWarningText(10086),30);
					Item.szText =szRead ;//"配方名"
					break;
				case 2:
					strncpy(szRead,GetLang().GetWarningText(10087),30);
					Item.szText = szRead;//"配方值"
					break;
				}
			}
            else if (col < 1) 
            {
			    sprintf(buf,"%d",row);
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				Item.szText = buf;
				m_GridProcPara.SetItemState(row,col, m_GridProcPara.GetItemState(row,col) | GVIS_READONLY);
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				Item.szText = GetCurCellText(row,col);
			}
			m_GridProcPara.SetItem(&Item);
			if(col==0)											
			     m_GridProcPara.SetColumnWidth(col,60);
			else
				m_GridProcPara.SetColumnWidth(col,160);
			m_GridProcPara.RedrawCell(row,col);
		}
	}
}

CString CIngredientInfoView::GetCurCellText(UINT nRow, UINT nCol)
{
    CString str;

	KEYVALUEINFO kv;

	char szRead[100]={""};
	if(nRow<m_GridProcPara.GetRowCount())
	{
		kv = m_itemKeyValueV[nRow-1];
		switch(nCol) {
		case 1:
			str.Format("%s",kv.keyName.c_str());
			break;
		case 2:
			str.Format("%s",kv.keyValue.c_str());
			break;
		default:
			break;
		}
	}

	return str;
}


void CIngredientInfoView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if(bActivate)
	{
		if(GetControl().GetRunState()!=CControl::END)
		{
			GetDlgItem(IDC_BTN_GETINGREDIENTS)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BTN_GETINGREDIENTS)->EnableWindow(TRUE);
		}
		SetUI();
		/*if (GetDoc().GetSysModeSwitch())//在线模式
		{
			if (GetDoc().GetSysHeartbeatSwitch())//启用心跳
			{
				int heartbeatFreq = atoi(GetDoc().GetSysHeartbeatFreq());
				//long heartbeatFreqMs = heartbeatFreq*60*1000;
				//SetTimer(1111,heartbeatFreqMs,NULL);
				GetDlgItem(IDC_STA_SSEMP)->ShowWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_STA_SSEMP)->ShowWindow(TRUE);
			}
		
		}
		else
		{
			GetDlgItem(IDC_STA_SSEMP)->ShowWindow(FALSE);
			
		}*/
		
	
		char buf[32];
		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			GetDlgItem(IDC_BTN_IMESSETTING)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_PATTERNSWITCH)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_LOTID)->EnableWindow(TRUE);
			m_strCurUser = GetDoc().GetCurUserName();
		}
		else if(nLevel==SystemDoc::SUPEROR)//高级
		{
			GetDlgItem(IDC_BTN_IMESSETTING)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_PATTERNSWITCH)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_LOTID)->EnableWindow(FALSE);
			strncpy(buf,GetLang().GetWarningText(10082),32);
			m_strCurUser = buf;

		}
	    else //系统
		{
			GetDlgItem(IDC_BTN_IMESSETTING)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_PATTERNSWITCH)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_LOTID)->EnableWindow(FALSE);
			strncpy(buf,GetLang().GetWarningText(10083),32);
			m_strCurUser = buf;
		}
	}
	UpdateData(FALSE);

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CIngredientInfoView::SetUI() 
{
	if (m_bModeSwitch)
	{
		m_staSsemp.SetBkColor(BK_GREENCOLOR);
	}
	else
	{
		m_staSsemp.SetBkColor(BK_REDCOLOR);
	}
	m_strSsemp = GetDoc().GetSysHeartbeatContent();
	UpdateData(FALSE);
	//Invalidate();
}
UINT StatusChangeReportForText(LPVOID pParam);
UINT AlarmReportForText(LPVOID pParam);
UINT UtilityReportForText(LPVOID pParam);
UINT WIPTrackingReportForText(LPVOID pParam);

//UINT ThreadProcAutoUploadReport(LPVOID pParam);
UINT ThreadProcEQPInfoVerify(LPVOID pParam);
UINT IViewThreadProcStatusReport(LPVOID pParam);
UINT ThreadProcParamVerify(LPVOID pParam);

void CIngredientInfoView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class	
	TVisualFormView::OnInitialUpdate();
	AfxBeginThread(ThreadProcEQPInfoVerify,this,0,0,0,NULL);
	SetUI();
	//CIngViewThread=AfxBeginThread(ThreadProcAutoUploadReport,this,0,0,0,NULL);

	CString statusReportFile = GetDoc().GetAppPath()+"info\\"+"StatusChangeReport.txt";
	CString utilityReportFile = GetDoc().GetAppPath()+"info\\"+"UtilityReport.txt";
	CString wipTrackingReportFile = GetDoc().GetAppPath()+"info\\"+"WIPTrackingReport.txt";
	CString alarmReportFile = GetDoc().GetAppPath()+"info\\"+"AlarmReport.txt";
	
	statusThread = AfxBeginThread(StatusChangeReportForText,this,0,0,CREATE_SUSPENDED,NULL);
	alarmThread = AfxBeginThread(AlarmReportForText,this,0,0,CREATE_SUSPENDED,NULL);
	wipTrackThread = AfxBeginThread(WIPTrackingReportForText,this,0,0,CREATE_SUSPENDED,NULL);
	utilityThread = AfxBeginThread(UtilityReportForText,this,0,0,CREATE_SUSPENDED,NULL);

	int heartbeatFreq = atoi(GetDoc().GetSysHeartbeatFreq());
	m_lHeartbeatFreq = heartbeatFreq*60*1000;

	SetTimer(1111,m_lHeartbeatFreq,NULL);//心跳检测定时器
	SetTimer(2222,1000,NULL);//数据补报定时器

	m_bModeSwitch = GetDoc().GetSysModeSwitch();
	if (GetDoc().GetSysModeSwitch())
	{
		m_btnModeSwitch.SetWindowText("模式开关:ON");
	}
	else
	{
		m_btnModeSwitch.SetWindowText("模式开关:OFF");
	}
}	

UINT ThreadProcEQPInfoVerify(LPVOID pParam)
{
	CIngredientInfoView *pIngView = (CIngredientInfoView *)pParam;
	pIngView->EQPInfoVerify();
	return 0;
}

UINT ThreadProcParamVerify(LPVOID pParam)
{
	CIngredientInfoView *pIngView = (CIngredientInfoView *)pParam;
	pIngView->ParamVerify();
	pIngView->m_bisLoading = FALSE;
	return 0;
}

/*
//自动补报线程函数
UINT ThreadProcAutoUploadReport(LPVOID pParam)
{
	CString statusReportFile = GetDoc().GetAppPath()+"info\\"+"StatusChangeReport.txt";
	CString utilityReportFile = GetDoc().GetAppPath()+"info\\"+"UtilityReport.txt";
	CString wipTrackingReportFile = GetDoc().GetAppPath()+"info\\"+"WIPTrackingReport.txt";
	CString alarmReportFile = GetDoc().GetAppPath()+"info\\"+"AlarmReport.txt";
	
	CIngredientInfoView *pView = (CIngredientInfoView *)pParam;
	//pView->statusThread = AfxBeginThread(StatusChangeReportForText,pView,0,0,CREATE_SUSPENDED,NULL);
	//pView->alarmThread = AfxBeginThread(AlarmReportForText,pView,0,0,CREATE_SUSPENDED,NULL);
	//pView->wipTrackThread = AfxBeginThread(WIPTrackingReportForText,pView,0,0,CREATE_SUSPENDED,NULL);
	//pView->utilityThread = AfxBeginThread(UtilityReportForText,pView,0,0,CREATE_SUSPENDED,NULL);
  
	while (true)
	{	
		//if (GetDoc().GetSysNeedUpload() && GetDoc().GetSysModeSwitch())//有数据需要补报
		{
			//if (pView->m_bStaNeedUpload)
			{
				pView->statusThread->ResumeThread();
			}
			if (pView->m_bAlaNeedUpload)
			{
				pView->alarmThread->ResumeThread();
			}
			if (pView->m_bWipNeedUpload)
			{
				pView->wipTrackThread->ResumeThread();
			}

			if (pView->m_bUtiNeedUpload)
			{
				pView->utilityThread->ResumeThread();
			}
		}
		else
		{
			continue;
		}
	}
	return 0;
}*/

UINT IViewThreadProcStatusReport(LPVOID pParam)
{
	CMainFrame *mainFrame = (CMainFrame *)pParam;
	mainFrame->StatusReport();
	return 0;
}


void CIngredientInfoView::OnImesSetting()
{
	MODESWITCHDIALOG login;
	if(login.DoModal()==IDOK )
	{
		CImesSettingDialog imesSettingDlg;
		if (imesSettingDlg.DoModal() != IDOK)
		{
			return;
		}
		else
		{
			int heartbeatFreq = atoi(GetDoc().GetSysHeartbeatFreq());
			long  lElapse= heartbeatFreq*60*1000;
			if (m_lHeartbeatFreq != lElapse)
			{
				m_lHeartbeatFreq = lElapse;
				//修改定时器频率
				SetTimer(1111,m_lHeartbeatFreq,NULL);
			}
		}	
	}
	else
	{
		return;
	}
}

void CIngredientInfoView::OnModeSwitch()
{
	UpdateData();
	MODESWITCHDIALOG login;
	if(login.DoModal()==IDOK)
	{
		ClearAllContent();
		CString tempStr;
		m_btnModeSwitch.GetWindowText(tempStr);
		if (m_bModeSwitch)
		{
			m_bModeSwitch = FALSE;
			m_strLotID = "";
			AfxMessageBox("已切换为离线模式");
			m_btnModeSwitch.SetWindowText("模式开关:OFF");
			GetDoc().SetSysHeartbeatContent("OffLine");
			if(GetDoc().GetFileOpenState())
			{
				GetDoc().SetFileOpenState(false);
			}
		}
		else
		{
			m_bModeSwitch = TRUE;
			AfxMessageBox("已切换为在线模式");
			GetDoc().SetSysHeartbeatContent("OnLine");
			m_btnModeSwitch.SetWindowText("模式开关:ON");
		}
		if(GetDoc().GetSysModeSwitch()!=m_bModeSwitch)
		{
			CString	BeforeStr,AfterStr;
			char ez[256]={""};
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,GetDoc().GetSysModeSwitch());//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,m_bModeSwitch);//"后:%d"
			
			GetLog().Append_pro(AfterStr,"模式切换",BeforeStr);//"模式切换"
		}
		GetDoc().SetSysModeSwitch(m_bModeSwitch);
		GetDoc().SaveWebServiceParam();
		SetUI();
		UpdateData(FALSE);
		Sleep(50);
		//GetMainFrame().StatusReport();
		AfxBeginThread(IViewThreadProcStatusReport,GetMainFrame(),0,0,0,NULL);
	}
	else
	{
		return;
	}
}

void CIngredientInfoView::ClearAllContent()
{
	m_itemKeyValueV.clear();
	m_GridProcPara.DeleteNonFixedRows();
	FillGridWithText();
	m_GridProcPara.RedrawWindow();
	m_strResponse="";
	SetGlobalExcellonIndex(0);									//20161109	第一步：清空钻孔数据（钻孔文件数据和分区数据）		
	GetExcellonData().ClearAll();
	SetGlobalExcellonIndex(1);			
	GetExcellonData().ClearAll();
	GetDoc().ClearTools();										//清除“加工用”刀具参数
	GetToolView().ToolParaClear();								//清除“显示用”刀具参数
	GetPointcontrlView().ToolInforClear();

	CString	str="";
	GetDoc().SetFileName(str);
	::SendMessage(GetMainFrame().m_Framework.Get(MAINRUNVIEW)->GetWnd()->m_hWnd,WM_USERUPDATEFILANAME,0,0);
	GetDoc().SetToolFileName(str);	
	pFileInfoSettingView->SetDlgItemText(IDC_EDT_SELECTFILE,"");
}


UINT AlarmReportForText(LPVOID pParam)
{
	CIngredientInfoView *pView = (CIngredientInfoView *)pParam;
	CString fileName = GetDoc().GetAppPath()+"info\\"+"AlarmReport.txt";
	
	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));

	vector<string> reqV;
	GetMainFrame().cs_alarm.Lock();
	bool parseret = ToolUtil::ParseJsonFromFile(fileName, reqV);
	GetMainFrame().cs_alarm.Unlock();
	if(!parseret)
	{
		return 0;
	}

	Json::Value oneReq;
	Json::Reader reader;
	for (int i=0;i<reqV.size();i++)
	{
		if (reader.parse(reqV[i],oneReq))
		{
			Request req;
			Response rsp;
			Json::Value reqSetting;
			Json::Value reqHead;
			reqHead["eqp_id"] = Json::Value(oneReq["requestHead"]["eqp_id"].asString());
			reqHead["time_stamp"] = Json::Value(oneReq["requestHead"]["time_stamp"].asString());
			reqHead["trx_id"] = Json::Value(oneReq["requestHead"]["trx_id"].asString());
			req.setReqHead(reqHead);

			Json::Value reqBody;
			reqBody["report_dt"] = Json::Value(oneReq["requestBody"]["report_dt"].asString());
			reqBody["keep_reason"] = Json::Value(oneReq["requestBody"]["keep_reason"].asString());
			reqBody["alarm_type"] = Json::Value(oneReq["requestBody"]["alarm_type"].asString());
			reqBody["alarm_code"] = Json::Value(oneReq["requestBody"]["alarm_code"].asString());
			reqBody["alarm_id"] = Json::Value(oneReq["requestBody"]["alarm_id"].asString());
			reqBody["alarm_desc"] = Json::Value(oneReq["requestBody"]["alarm_desc"].asString());
			req.setReqBody(reqBody);

			int ret = STS_NG;
			do{
				Sleep(20);
				reqSetting["ImesURL"] = Json::Value(GetDoc().GetSysImesURL());
				reqSetting["Timeout"] = Json::Value(GetDoc().GetSysTimeout());
				
				req.setReqSetting(reqSetting);
				ret = GetWSInterfaceImplementor().AlarmReport(req, rsp);
				if (ret == STS_OK)
				{
					Sleep(20);
					break;
				}
			}while(ret != STS_OK);
		}
	}
	pView->alarmThread->SuspendThread();
	fstream file(fileName, ios::out);	
	file.close();
	return 0;
}

UINT StatusChangeReportForText(LPVOID pParam)
{
	CIngredientInfoView *pView = (CIngredientInfoView *)pParam;
	CString fileName = GetDoc().GetAppPath()+"info\\"+"StatusChangeReport.txt";

	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	
	vector<string> reqV;		
	GetMainFrame().cs_status.Lock();
	bool parseret = ToolUtil::ParseJsonFromFile(fileName, reqV);
	GetMainFrame().cs_status.Unlock();

	if(!parseret)
	{
		return 0;
	}

	Json::Value oneReq;
	Json::Reader reader;
	for (int i=0;i<reqV.size();i++)
	{
		if (reader.parse(reqV[i],oneReq))
		{
			Request req;
			Response rsp;
			Json::Value reqSetting;
			Json::Value reqHead;
			reqHead["eqp_id"] = Json::Value(oneReq["requestHead"]["eqp_id"].asString());
			reqHead["time_stamp"] = Json::Value(oneReq["requestHead"]["time_stamp"].asString());
			reqHead["trx_id"] = Json::Value(oneReq["requestHead"]["trx_id"].asString());
			req.setReqHead(reqHead);
			
			Json::Value reqBody;
			reqBody["report_dt"] = Json::Value(oneReq["requestBody"]["report_dt"].asString());
			reqBody["keep_reason"] = Json::Value(oneReq["requestBody"]["keep_reason"].asString());
			reqBody["cim_mode"] = Json::Value(oneReq["requestBody"]["cim_mode"].asString());
			reqBody["auto_mode"] = Json::Value(oneReq["requestBody"]["auto_mode"].asString());
			reqBody["status_id"] = Json::Value(oneReq["requestBody"]["status_id"].asString());
			reqBody["alarm_id"] = Json::Value(oneReq["requestBody"]["alarm_id"].asString());
			req.setReqBody(reqBody);
			
			int ret = STS_NG;
			do{
				Sleep(20);
				reqSetting["ImesURL"] = Json::Value(GetDoc().GetSysImesURL());
				reqSetting["Timeout"] = Json::Value(GetDoc().GetSysTimeout());
				
				req.setReqSetting(reqSetting);
				ret = GetWSInterfaceImplementor().StatusChangeReport(req, rsp);
				if (ret == STS_OK)
				{
					Sleep(20);
					break;
				}
			}while(ret != STS_OK);
		}
	}
	pView->statusThread->SuspendThread();
	fstream file(fileName, ios::out);
	file.close();
	return 0;
}

UINT UtilityReportForText(LPVOID pParam)
{
	CIngredientInfoView *pView = (CIngredientInfoView *)pParam;
	CString fileName = GetDoc().GetAppPath()+"info\\"+"UtilityReport.txt";

	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	
	vector<string> reqV;
	GetMainFrame().cs_utility.Lock();
	bool parseret = ToolUtil::ParseJsonFromFile(fileName, reqV);
	GetMainFrame().cs_utility.Unlock();
	if(!parseret)
	{
		return 0;
	}

	Json::Value oneReq;
	Json::Reader reader;
	for (int i=0;i<reqV.size();i++)
	{
		if (reader.parse(reqV[i],oneReq))
		{
			Request req;
			Response rsp;
			Json::Value reqSetting;
			Json::Value reqHead;
			reqHead["eqp_id"] = Json::Value(oneReq["requestHead"]["eqp_id"].asString());
			reqHead["time_stamp"] = Json::Value(oneReq["requestHead"]["time_stamp"].asString());
			reqHead["trx_id"] = Json::Value(oneReq["requestHead"]["trx_id"].asString());
			req.setReqHead(reqHead);

			Json::Value reqBody;
			Json::Value arr;
			
			reqBody["report_dt"] = Json::Value(oneReq["requestBody"]["report_dt"].asString());
			reqBody["keep_reason"] = Json::Value(oneReq["requestBody"]["keep_reason"].asString());
			reqBody["shift_id"] = Json::Value(oneReq["requestBody"]["shift_id"].asString());
			
			Json::Value arrayObj = oneReq["requestBody"]["utl_infos"]["utl"];
			for (int k = 0; k < arrayObj.size(); k++)
			{
				Json::Value item;
				item["item_id"] = Json::Value(arrayObj[k]["item_id"].asString());
				if(arrayObj[k]["item_value"].isNull() || arrayObj[k]["item_value"].empty())
				{
					item["item_value"] = Json::Value("0");
				}
				else if(arrayObj[k]["item_value"].isInt())
				{
					CString itostr;
					itostr.Format("%d",arrayObj[k]["item_value"].asInt());
					item["item_value"] = Json::Value(itostr);
				}
				else
				{
					item["item_value"] = Json::Value(arrayObj[k]["item_value"].asString());
				}
				arr["utl"].append(item);
			}
			reqBody["utl_infos"] = arr;
			req.setReqBody(reqBody);

			int ret = STS_NG;
			do{
				Sleep(20);
				reqSetting["ImesURL"] = Json::Value(GetDoc().GetSysImesURL());
				reqSetting["Timeout"] = Json::Value(GetDoc().GetSysTimeout());
				
				req.setReqSetting(reqSetting);
				ret = GetWSInterfaceImplementor().UtilityReport(req, rsp);
				if (ret == STS_OK)
				{
					Sleep(20);
					break;
				}
			}while(ret != STS_OK);
		}
	}
	pView->utilityThread->SuspendThread();
	fstream file(fileName, ios::out);
	file.close();
	return 0;
}

UINT WIPTrackingReportForText(LPVOID pParam)
{
	CIngredientInfoView *pView = (CIngredientInfoView *)pParam;
	CString fileName = GetDoc().GetAppPath()+"info\\"+"WIPTrackingReport.txt";

	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));

	vector<string> reqV;
	GetMainFrame().cs_wiptrack.Lock();
	bool parseret = ToolUtil::ParseJsonFromFile(fileName, reqV);
	GetMainFrame().cs_wiptrack.Unlock();
	if(!parseret)
	{
		return 0;
	}

	Json::Value oneReq;
	Json::Reader reader;
	for (int i=0;i<reqV.size();i++)
	{
		if (reader.parse(reqV[i],oneReq))
		{
			Request req;
			Response rsp;
			Json::Value reqSetting;
			Json::Value reqHead;
			reqHead["eqp_id"] = Json::Value(oneReq["requestHead"]["eqp_id"].asString());
			reqHead["time_stamp"] = Json::Value(oneReq["requestHead"]["time_stamp"].asString());
			reqHead["trx_id"] = Json::Value(oneReq["requestHead"]["trx_id"].asString());
			req.setReqHead(reqHead);

			Json::Value reqBody;
			Json::Value arr;
			
			reqBody["report_dt"] = Json::Value(oneReq["requestBody"]["report_dt"].asString());
			reqBody["keep_reason"] = Json::Value(oneReq["requestBody"]["keep_reason"].asString());
			reqBody["lot_id"] = Json::Value(oneReq["requestBody"]["lot_id"].asString());
			Json::Value arrayObj = oneReq["requestBody"]["edc_infos"]["edc"];

			for (int k = 0; k < arrayObj.size(); k++)
			{
				Json::Value item;
				item["item_id"] = Json::Value(arrayObj[k]["item_id"].asString());
				if(arrayObj[k]["item_value"].isNull() || arrayObj[k]["item_value"].empty())
				{
					item["item_value"] = Json::Value("0");
				}
				else if(arrayObj[k]["item_value"].isInt())
				{
					CString itostr;
					itostr.Format("%d",arrayObj[k]["item_value"].asInt());
					item["item_value"] = Json::Value(itostr);
				}
				else
				{
					item["item_value"] = Json::Value(arrayObj[k]["item_value"].asString());
				}
				arr["edc"].append(item);
			}
			reqBody["edc_infos"] = arr;
			req.setReqBody(reqBody);
			req.setReqBody(reqBody);

			int ret = STS_NG;
			do{
				Sleep(20);
				reqSetting["ImesURL"] = Json::Value(GetDoc().GetSysImesURL());
				reqSetting["Timeout"] = Json::Value(GetDoc().GetSysTimeout());
				
				req.setReqSetting(reqSetting);
				ret = GetWSInterfaceImplementor().WIPTrackingReport(req, rsp);
				if (ret == STS_OK)
				{
					Sleep(20);
					break;
				}
			}while(ret != STS_OK);
		}
	}
	pView->wipTrackThread->SuspendThread();
	fstream file(fileName, ios::out);
	file.close();
	return 0;
}

void CIngredientInfoView::OnGetIngredients()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!GetDoc().GetSysModeSwitch())//离线模式
	{
		AfxMessageBox("当前模式不支持配方下发,请打开模式开关为ON!");
		return;
	} 
	int nLevel = GetDoc().GetCurUserLevel();
	if(nLevel==SystemDoc::SUPEROR || nLevel==SystemDoc::ADMIN)//高级//管理员
	{
		AfxMessageBox("当前用户不支持配方在线获取,请切换登录普通用户再进行操作!");
		return;
	}
	if (m_strLotID == "")
	{
		AfxMessageBox("工单ID不能为空,请输入工单ID!");
		return;
	}
	if (m_bisLoading)
	{
		AfxMessageBox("请等待上一个工单加载完成后再操作!");
		return;
	}
	ClearAllContent();
	m_bisLoading = TRUE;
	UpdateData(FALSE);
	AfxBeginThread(ThreadProcParamVerify,this,0,0,0,NULL);
}

void CIngredientInfoView::ParamVerify()
{
	Request req;
	Response rsp;
	bool hasErrValue = false;
	bool allFileExist = false;
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
	reqBody["lot_id"] = Json::Value(m_strLotID);
	req.setReqBody(reqBody);
	
	int errCode;
	int times = 0;
	for (int i=0; i<3; i++)
	{
		errCode = GetWSInterfaceImplementor().ParamVerify(req, rsp);
		if (errCode == STS_OK)
		{
			break;	
		}
		else
		{
			times ++;
			CString tips;
			tips.Format("配方下发重试中,次数:%d,时间:%s",times,currentTime);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			continue;
		}
	}
	if (errCode == STS_OK)
	{
		times=0;
		CString pathname;
		KEYVALUEINFO itemStruct;
		itemStruct.keyName = "lot_id";
		itemStruct.keyValue = rsp.getRspBody()["lot_id"].asString();
		
		CString lotid = rsp.getRspBody()["lot_id"].asCString();
		GetDoc().SetSysProcLOTID(lotid);
		CString fix,inc;
		ToolUtil::SplitStringGenerateFixAndInc(lotid,fix,inc);
		GetDoc().SetLOTIDFix(lotid);
		GetDoc().SetLOTIDInc(inc);
		
		m_itemKeyValueV.push_back(itemStruct);
		Json::Value array = rsp.getRspBody()["lot_infos"]["lot"];
		CString saFileA,paramFileA,saFileB,paramFileB;
		CString	strProdId,strProdVer;
		
		for (unsigned int j = 0; j < array.size(); j++)
		{   
			CString key = array[j]["item_id"].asCString();
			CString item_value = array[j]["item_value"].asCString();
			itemStruct.keyName = key.GetBuffer(0);
			itemStruct.keyValue = item_value.GetBuffer(0);
			m_itemKeyValueV.push_back(itemStruct);
			pFileInfoSettingView->m_barcodeStructVet = m_itemKeyValueV;
			
			/*if (key == "LOT_QTY")
			{
				GetDoc().SetSysPCBCount(atoi(item_value));		
			}
			if (key == "PROD_ID")
			{
				GetDoc().SetSysProcPRODID(item_value);
				strProdId=item_value;
			}
			if (key == "PROD_VER")
			{
				strProdVer = item_value;
			}*/
			if (key == "S103")
			{
				saFileA = item_value;
			}
			if (key == "S104")
			{
				paramFileA = item_value;
			}
			if (key == "S105")
			{
				saFileB = item_value;
			}
			if (key == "S106")
			{
				paramFileB = item_value;
			}
			if (key == "S108")
			{
				if(item_value != "")
				{
					GetDoc().SetFlowPathMode(atoi(item_value));
				}
			}
			/*if (key == "S107")
			{
				GetDoc().SetProcMode(SystemDoc::PROCMODE(atoi(item_value)));
			}
			if (key == "S050")
			{
				GetDoc().SetPCBThickness(atof(item_value)*1000);	
				GetDoc().SetPCBThicknessStd(atof(item_value)*1000);
			}*/
		}
		
		char buf[30] = "";
		for (int k = 0; k<m_itemKeyValueV.size(); k++)
		{
			m_GridProcPara.InsertRow(buf);
		}
		
		//拷贝程序文件和参数文件到本地LotPath文件夹下
		CIniFile file;
		CString desPath  =  GetDoc().GetAppPath()+"ProcPath";
		bool desPathisExist = false;
		if (!file.VerifyPathExist(desPath))
		{
			int flag = _mkdir(desPath);//不存在则创建（后续需要优化，循环判断各级目录，不存在则分级创建）
		}
		else
		{
			ToolUtil::DelDirFiles(desPath);
		}
		
		//校验程序AP路径，参数AP路径是否存在并且具有可读属性
		bool saFileExist;
		bool paramFileExist;

		//根据相应的flow_mode 取相应的文件 ONLYANOREVERSE,ONLYAREVERSE,AANDBDOUBLE,ONLYB
		if (GetDoc().GetFlowPathMode() == ONLYB)//S105,S106
		{
			saFileExist = file.VerifyPathExist(saFileB);
			paramFileExist= file.VerifyPathExist(paramFileB);
		}
		else if (GetDoc().GetFlowPathMode() == AANDBDOUBLE)//S103,S104,S105,S106 
		{
			saFileExist = file.VerifyPathExist(saFileA)|file.VerifyPathExist(saFileB);
			paramFileExist= file.VerifyPathExist(paramFileA)|file.VerifyPathExist(paramFileB);
		}
		else //S103,S104
		{
			saFileExist = file.VerifyPathExist(saFileA);
			paramFileExist= file.VerifyPathExist(paramFileA);
		}
		
		CString newSaFileA,newParamFileA,newSaFileB,newParamFileB;
		if (saFileExist && paramFileExist)
		{
			CString tips;
			tips.Format("配方正在加载中,请稍后...");
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			
			CString temp;
			temp = saFileA.Left(saFileA.ReverseFind('.'));
			temp = temp.Mid(temp.ReverseFind('\\')+1);
			newSaFileA.Format("%s\\%s.sa",desPath,temp);
			newParamFileA.Format("%s\\%s.tpm",desPath,temp);

			temp = saFileB.Left(saFileB.ReverseFind('.'));
			temp = temp.Mid(temp.ReverseFind('\\')+1);
			newSaFileB.Format("%s\\%s.sa",desPath,temp);
			newParamFileB.Format("%s\\%s.tpm",desPath,temp);
			
			if (GetDoc().GetFlowPathMode() == ONLYB)//S104,S106 Reverse
			{
				CopyFile(saFileB,newSaFileB,false);
				CopyFile(paramFileB,newParamFileB,false);
			}
			else if(GetDoc().GetFlowPathMode() == AANDBDOUBLE)
			{	
				CopyFile(saFileA,newSaFileA,false);
				CopyFile(paramFileA,newParamFileA,false);
				CopyFile(saFileB,newSaFileB,false);
				CopyFile(paramFileB,newParamFileB,false);
			}
			else
			{
				CopyFile(saFileA,newSaFileA,false);
				CopyFile(paramFileA,newParamFileA,false);
			}
			tips.Format("配方加载完成,时间:%s",currentTime);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			
			::SendMessage(GetMainFrame().m_Framework.Get(FILEINFOSETTINGVIEW)->GetWnd()->m_hWnd,\
			WM_USERUPDATESELECTFILE,(WPARAM)(LPSTR)(LPCTSTR)newSaFileA,(LPARAM)(LPSTR)(LPCTSTR)newSaFileB);
		}
		else
		{
			CString tips;
			tips.Format("配方下发失败,文件不存在或者文件为空,请检查服务器上的程序、参数文件");
			GetLog().Append_pro("文件错误","配方下发",m_strLotID);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			AfxMessageBox(tips);
		}
	}
	else
	{
		times=0;
		CString tips;
		CString reason;
		if(!rsp.getRspHead()["rtn_msg"].isNull())
				reason = rsp.getRspHead()["rtn_msg"].asCString();
			else
				reason = StringOfBaseStatus[errCode].pString;
		tips.Format("配方下发失败,原因:%s,时间:%s!",reason,currentTime);
		GetLog().Append_pro(reason,"配方下发",m_strLotID);
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
		AfxMessageBox("配方下发失败!");
	}
	
	Json::FastWriter fast_writer;
	m_strResponse.Format("%s\r\n%s %s",currentTime,fast_writer.write(rsp.getRspHead()).c_str(),\
		fast_writer.write(rsp.getRspBody()).c_str());
	::SendMessage(GetMainFrame().m_Framework.Get(INGREDIENTINFOVIEW)->GetWnd()->m_hWnd, WM_USERUPDATERESPONSE,0,0);
}


//必须要带NMHDR和LRESULT这两个参数，否则会报错
void CIngredientInfoView::SetEditDisabledBegin(NMHDR *pNotifyStruct, LRESULT* pResult) 
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    int row = (pItem->iRow);        
    int col = (pItem->iColumn);    
 
	//根据行号列号获取单元格内容
	m_beginLabel = m_GridProcPara.GetItemText(row,col);
}


//必须要带NMHDR和LRESULT这两个参数，否则会报错
void CIngredientInfoView::SetEditDisabledEnd(NMHDR *pNotifyStruct, LRESULT* pResult) 
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    int row = (pItem->iRow);        
    int col = (pItem->iColumn);    
 
	//根据行号列号获取单元格内容
	CString  endLabel = m_GridProcPara.GetItemText(row,col);
	if (endLabel != m_beginLabel)
	{
		AfxMessageBox("不可修改!");
		FillGridWithText();
		Invalidate();
	}
}
	
void CIngredientInfoView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//UpdateData(FALSE);
	fstream file1,file2,file3,file4;
	CString statusReportFile = GetDoc().GetAppPath()+"info\\"+"StatusChangeReport.txt";
	CString utilityReportFile = GetDoc().GetAppPath()+"info\\"+"UtilityReport.txt";
	CString wipTrackingReportFile = GetDoc().GetAppPath()+"info\\"+"WIPTrackingReport.txt";
	CString alarmReportFile = GetDoc().GetAppPath()+"info\\"+"AlarmReport.txt";

	switch(nIDEvent)
	{
	case 1111:
		AfxBeginThread(ThreadProcEQPInfoVerify,this,0,0,0,NULL);
		SetUI();
		break;
	case 2222:
		if (GetDoc().GetSysModeSwitch())//在线模式
		{
			//StatusChangeReport
			file1.open(statusReportFile,ios::in);
			if (file1.is_open()) //文件打开OK
			{
				file1.seekg(0,ios::end);
				streampos fp = file1.tellg();
				if (int(fp) != 0 && m_bModeSwitch)
				{
					DWORD code = 0; 
					if (statusThread)
					{
						statusThread->ResumeThread();                              
						GetExitCodeThread(statusThread->m_hThread, &code);
					}
					if(code != STILL_ACTIVE)
					{  
						statusThread = AfxBeginThread(StatusChangeReportForText,this,0,0,0,NULL);
					}	
				}
				file1.close();
			}
			
			//AlarmReport
			file2.open(alarmReportFile,ios::in);
			if (file2.is_open())
			{
				file2.seekg(0,ios::end);
				streampos fp = file2.tellg();
				if (int(fp) != 0 && m_bModeSwitch)
				{	
					DWORD code = 0; 
					if (alarmThread)
					{
						alarmThread->ResumeThread();
						GetExitCodeThread(alarmThread->m_hThread, &code);
					}
					if(code != STILL_ACTIVE)
					{  
						alarmThread = AfxBeginThread(AlarmReportForText,this,0,0,0,NULL);
					}
				}	
				file2.close();
			}
			
			//WIPTrackingReport
			file3.open(wipTrackingReportFile,ios::in);
			if (file3.is_open())
			{
				file3.seekg(0,ios::end);
				streampos fp = file3.tellg();
				if (int(fp) != 0 && m_bModeSwitch)
				{	
					DWORD code = 0; 
					if (wipTrackThread)
					{
						wipTrackThread->ResumeThread();                              
						GetExitCodeThread(wipTrackThread->m_hThread, &code);
					}                             
					if(code != STILL_ACTIVE)
					{  
						wipTrackThread = AfxBeginThread(WIPTrackingReportForText,this,0,0,0,NULL);
					}
				}
				file3.close();
			}
			
			//UtilityReport
			file4.open(utilityReportFile,ios::in);
			if (file4.is_open())
			{
				file4.seekg(0,ios::end);
				streampos fp = file4.tellg();
				if (int(fp) != 0 && m_bModeSwitch)
				{	
					DWORD code = 0; 
					if (utilityThread)
					{
						utilityThread->ResumeThread();                              
						GetExitCodeThread(utilityThread->m_hThread, &code);
					}
					if(code != STILL_ACTIVE)
					{  
						utilityThread = AfxBeginThread(UtilityReportForText,this,0,0,0,NULL);
					}
				}
				file4.close();
			}
		}
		break;
	}
	TVisualFormView::OnTimer(nIDEvent);
}

void CIngredientInfoView::EQPInfoVerify()
{
	bool result = false;
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
	
	int errCode = GetWSInterfaceImplementor().EQPInfoVerify(req, rsp);
	if (errCode == STS_OK)
	{
		result = true;
		//rsp.getRspBody()["cim_msg"].asCString()
		//GetDoc().SetSysHeartbeatContent("online");
		
		//修改系统时间
		CString serviceDt = rsp.getRspBody()["now"].asCString();
		
		COleDateTime tm;
		COleDateTimeSpan ts;
		tm.ParseDateTime(serviceDt);
		//ts.SetDateTimeSpan(0,0,0,0);
		tm+=ts;
		SYSTEMTIME st;
		tm.GetAsSystemTime(st);
		SetLocalTime(&st);
		//CIngViewThread->ResumeThread();
	}
	else
	{
		//GetDoc().SetSysHeartbeatContent("OffLine");
		result = false;
	}
}

void CIngredientInfoView::OnUpdateResponse(WPARAM wParam, LPARAM lParam)
{
	FillGridWithText();
	m_GridProcPara.RedrawWindow();
	m_GridProcPara.AutoSizeRows();
	UpdateData(FALSE);
}