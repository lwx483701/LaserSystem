// MainFrm.cpp : implementation of the CMainFrame class
//
#include "stdafx.h"
#include "LaserSystem.h"
#include "inifile.h"
#include "MainFrm.h"
#include "WarningInfo.h"
#include "MainFrm.h"
#include "ToolParaView.h"
#include "ImageParaSetView.h"
#include "IngredientInfoView.h"
#include "SignalInputview.h"
#include "motioncontroltestview.h"
#include "signaloutview.h"
#include "operateRefCoord.h"
#include "testfunctionview.h"
#include "fileinfosettingview.h"
#include "mainrunview.h"
#include "motionparameterview.h"
#include "PositionErrValueView.h"
#include "SysParameter.h"
#include "SysParamView.h"
#include "LoginDialog.h"
#include "OperateControl.h"
#include "FilePointView.h"
#include "SystemLogView.h"
#include "PointcontrlView.h"
#include "LoginView.h"
#include "PROCPARAVIEW.h"
#include "OperateControl.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString strDataBase[6];
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_SHOWWINDOW()
ON_COMMAND(ID_RUN_PANE, OnRunPane)
ON_COMMAND(ID_FUNCTIONTEST_PANE, OnFunctiontestPane)
ON_COMMAND(ID_FILESET_PANE, OnFilesetPane)
ON_COMMAND(ID_PORW_PANE, OnPorwPane)
ON_COMMAND(ID_IMAGE_PANE, OnImagePane)
ON_COMMAND(ID_SHOWPOINT_PANE, OnShowpointPane)
ON_COMMAND(ID_SYSTEMPARA_PANE, OnSystemparaPane)
ON_COMMAND(ID_OPRATECOORD_PANE, OnOpratecoordPane)
ON_COMMAND(ID_WORKPARA_PANE, OnWorkparaPane)
ON_COMMAND(ID_SINGALINPUT_PANE, OnSingalinputPane)
ON_COMMAND(ID_SINGALOUTPUT_PANE, OnSingaloutputPane)
ON_COMMAND(ID_MOTORTEST_PANE, OnMotortestPane)
ON_WM_CLOSE()
ON_WM_TIMER()
ON_WM_ACTIVATE()
ON_MESSAGE(WM_USERUPDATESTATUSBAR,OnUpdateStatusBar)
	//}}AFX_MSG_MAP
ON_UPDATE_COMMAND_UI(IDS_PROCAXISMODE,OnUpdateProcAxisMode)		//�ع��ӹ����̣�20161123
ON_UPDATE_COMMAND_UI(IDS_FLOWPATHMODE,OnUpdateFlowPathMode)
ON_UPDATE_COMMAND_UI(IDS_CURRENTFILEDISPLAY,OnUpdateCurFileDisplay)
ON_UPDATE_COMMAND_UI(IDS_CURRENTFLOWSTATUS,OnUpdateCurFlowStatus)

ON_UPDATE_COMMAND_UI(IDS_GALVOLEFTTEST,OnUpdateGalvoLeft)
ON_UPDATE_COMMAND_UI(IDS_GALVORIGHTTEST,OnUpdateGalvoRight)
ON_UPDATE_COMMAND_UI(IDS_POWERLEFTTEST,OnUpdatePowerLeft)
ON_UPDATE_COMMAND_UI(IDS_POWERRIGHTTEST,OnUpdatePowerRight)
//ON_UPDATE_COMMAND_UI(IDS_PROCSTATUS,OnUpdateProcStatus)
ON_UPDATE_COMMAND_UI(IDS_APTNO,OnUpdateAptNo)
ON_UPDATE_COMMAND_UI(IDS_OPTICALPATHMODE,OnUpdateOptPathMode)
ON_UPDATE_COMMAND_UI(IDS_BEAMMODE,OnUpdateBeamMode)
ON_UPDATE_COMMAND_UI(IDS_CURRENTMACHINESTATUS,OnUpdateMachineStatus)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_CURRENTFILEDISPLAY,	//�ع��ӹ����̣�20161123
	IDS_CURRENTFLOWSTATUS,
	IDS_PROCAXISMODE,									
	IDS_FLOWPATHMODE,
	IDS_GALVOLEFTTEST,
	IDS_GALVORIGHTTEST,
	IDS_POWERLEFTTEST,
	IDS_POWERRIGHTTEST,
//	IDS_PROCSTATUS,
	IDS_APTNO,
	IDS_OPTICALPATHMODE,
	IDS_CURRENTMACHINESTATUS,
//	IDS_BEAMMODE
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame& GetMainFrame()
{
	static CMainFrame mainframe;
	return mainframe;
}

TVisualFramework CMainFrame::m_Framework;

CMainFrame::CMainFrame()
{
	m_StaRSCurPods = -1;
	m_Status = _T("");
	m_Operation_Rate = 0;
	m_shift = 1;
	m_bAutoMenuEnable=FALSE;
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
//		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	NONCLIENTMETRICS metrics;
	metrics.cbSize = sizeof(metrics);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &metrics, 0);
	CWindowDC wdc(NULL);
	int nLPixY = GetDeviceCaps(wdc.m_hDC, LOGPIXELSY);
	_tcscpy(metrics.lfStatusFont.lfFaceName, _T("Verdana"));
	metrics.lfStatusFont.lfItalic = 1;
	m_Font.CreateFontIndirect(&metrics.lfStatusFont);

	SetTimer(1, 1000, NULL); 
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
//extern int nWarningCount[100];
extern VOID CALLBACK TimerProc(  HWND hwnd,   UINT uMsg,    UINT idEvent,  DWORD dwTime);
extern VOID CALLBACK TimerProc1(  HWND hwnd,   UINT uMsg,    UINT idEvent,  DWORD dwTime);
VOID CALLBACK TimeProcUploadStatusReport(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTimer);
UINT unTimer;
UINT unTimer1;
UINT unTimer2;


void CMainFrame::SetUI(CMenu* mmenu)
{
	if(mmenu)//ly add 20110319
	{
		char szRead[20] = {""};
		
		//TopMenu,����û��ID���ã�ֻ��ͨ��MF_MYPOSITION������
		GetLang().GetUIText("Menu","0",szRead,20);
		mmenu->ModifyMenu(0,MF_STRING |MF_BYPOSITION,0,szRead);//"&F(�ļ�)""&F(File)"
//		GetLang().GetUIText("Menu","1",szRead,20);
//		mmenu->ModifyMenu(1,MF_STRING |MF_BYPOSITION,0,szRead);//"&L(��־)"
		GetLang().GetUIText("Menu","2",szRead,20);
		mmenu->ModifyMenu(2,MF_STRING |MF_BYPOSITION,0,szRead);//"&T(����)"
		GetLang().GetUIText("Menu","3",szRead,20);
		mmenu->ModifyMenu(3,MF_STRING |MF_BYPOSITION,0,szRead);//"&H(����)"
/*
		//SubMenu1-
		GetLang().GetUIText("Menu","10",szRead,20);
		mmenu->GetSubMenu(1)->ModifyMenu(0,MF_STRING |MF_BYPOSITION,0,szRead);//
		GetLang().GetUIText("Menu","11",szRead,20);
		mmenu->GetSubMenu(1)->ModifyMenu(1,MF_STRING |MF_BYPOSITION,0,szRead);//
		GetLang().GetUIText("Menu","12",szRead,20);
		mmenu->GetSubMenu(1)->ModifyMenu(2,MF_STRING |MF_BYPOSITION,0,szRead);//
		GetLang().GetUIText("Menu","13",szRead,20);
		mmenu->GetSubMenu(1)->ModifyMenu(3,MF_STRING |MF_BYPOSITION,0,szRead);//
		
		//SubMenu1-1-
		GetLang().GetUIText("Menu","ID_MENUPCBDATA1",szRead,20);
		mmenu->ModifyMenu(ID_MENUPCBDATA1,MF_STRING | MF_BYCOMMAND , ID_MENUPCBDATA1,szRead);
		GetLang().GetUIText("Menu","ID_MENUPCBDATA2",szRead,20);
		mmenu->ModifyMenu(ID_MENUPCBDATA2,MF_STRING | MF_BYCOMMAND , ID_MENUPCBDATA2,szRead);
		GetLang().GetUIText("Menu","ID_MENUPCBDATA5",szRead,20);
		mmenu->ModifyMenu(ID_MENUPCBDATA5,MF_STRING | MF_BYCOMMAND , ID_MENUPCBDATA5,szRead);
		GetLang().GetUIText("Menu","ID_MENUPCBDATA6",szRead,20);
		mmenu->ModifyMenu(ID_MENUPCBDATA6,MF_STRING | MF_BYCOMMAND , ID_MENUPCBDATA6,szRead);
		
		//SubMenu1-2-
		GetLang().GetUIText("Menu","ID_MENUOPRATOR1",szRead,20);
		mmenu->ModifyMenu(ID_MENUOPRATOR1,MF_STRING | MF_BYCOMMAND , ID_MENUOPRATOR1,szRead);
		GetLang().GetUIText("Menu","ID_MENUOPRATOR2",szRead,20);
		mmenu->ModifyMenu(ID_MENUOPRATOR2,MF_STRING | MF_BYCOMMAND , ID_MENUOPRATOR2,szRead);
		GetLang().GetUIText("Menu","ID_MENUOPRATOR3",szRead,20);
		mmenu->ModifyMenu(ID_MENUOPRATOR3,MF_STRING | MF_BYCOMMAND , ID_MENUOPRATOR3,szRead);
		GetLang().GetUIText("Menu","ID_MENUOPRATOR4",szRead,20);
		mmenu->ModifyMenu(ID_MENUOPRATOR4,MF_STRING | MF_BYCOMMAND , ID_MENUOPRATOR4,szRead);
		
		//SubMenu1-3-
		GetLang().GetUIText("Menu","ID_MENUPOWER1",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER1,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER1,szRead);
		GetLang().GetUIText("Menu","ID_MENUPOWER2",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER2,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER2,szRead);
		GetLang().GetUIText("Menu","ID_MENUPOWER3",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER3,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER3,szRead);
		GetLang().GetUIText("Menu","ID_MENUPOWER4",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER4,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER4,szRead);
		GetLang().GetUIText("Menu","ID_MENUPOWER5",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER5,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER5,szRead);
		GetLang().GetUIText("Menu","ID_MENUPOWER6",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER6,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER6,szRead);
		GetLang().GetUIText("Menu","ID_MENUPOWER7",szRead,20);
		mmenu->ModifyMenu(ID_MENUPOWER7,MF_STRING | MF_BYCOMMAND , ID_MENUPOWER7,szRead);
		
		//SubMenu1-4-
		GetLang().GetUIText("Menu","ID_MENUFILEPRO1",szRead,20);
		mmenu->ModifyMenu(ID_MENUFILEPRO1,MF_STRING | MF_BYCOMMAND , ID_MENUFILEPRO1,szRead);
		GetLang().GetUIText("Menu","ID_MENUFILEPRO2",szRead,20);
		mmenu->ModifyMenu(ID_MENUFILEPRO2,MF_STRING | MF_BYCOMMAND , ID_MENUFILEPRO2,szRead);
		GetLang().GetUIText("Menu","ID_MENUFILEPRO4",szRead,20);
		mmenu->ModifyMenu(ID_MENUFILEPRO4,MF_STRING | MF_BYCOMMAND , ID_MENUFILEPRO4,szRead);
*/	
		//SubMenu2-
		GetLang().GetUIText("Menu","ID_PRECISIONTEST",szRead,20);
		mmenu->ModifyMenu(ID_PRECISIONTEST,MF_STRING | MF_BYCOMMAND , ID_PRECISIONTEST,szRead);
		GetLang().GetUIText("Menu","ID_LASERFOCUSTEST1",szRead,20);
		mmenu->ModifyMenu(ID_LASERFOCUSTEST1,MF_STRING | MF_BYCOMMAND , ID_LASERFOCUSTEST1,szRead);
		GetLang().GetUIText("Menu","ID_LASERFOCUSTEST2",szRead,20);
		mmenu->ModifyMenu(ID_LASERFOCUSTEST2,MF_STRING | MF_BYCOMMAND , ID_LASERFOCUSTEST2,szRead);
		GetLang().GetUIText("Menu","ID_APERTURETEST",szRead,20);
		mmenu->ModifyMenu(ID_APERTURETEST,MF_STRING | MF_BYCOMMAND , ID_APERTURETEST,szRead);
		GetLang().GetUIText("Menu","ID_TABLETEST",szRead,20);
		mmenu->ModifyMenu(ID_TABLETEST,MF_STRING | MF_BYCOMMAND , ID_APERTURETEST,szRead);
		
		DrawMenuBar();//ˢ��Menu
	}
}

UINT ThreadProcStatusReport(LPVOID pParam);
UINT ThreadProcUtilityReport(LPVOID pParam);

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	char ez[256]={""};
	char szRead[20] = {""};

//��ʼ������
	if(GetLang().Init()==0)
		return false;

	m_hMutex = CreateMutex( NULL, FALSE, AfxGetApp()->m_pszExeName );

	if ( GetLastError() == ERROR_ALREADY_EXISTS ) 
	{
		m_hMutex = NULL;
		strncpy(ez,GetLang().GetWarningText(21015),256);
		AfxMessageBox(ez);//"�Ѿ��������ϵͳ��"
		return false;
	}

//��ʼ��ϵͳ��ز���
	if(!GetDoc().InitializeSysDoc())
		return false;

	GetDoc().SetProcAxisMode(GetDoc().GetProcAxisSelected());			//20191015 ����

//��ʼ��������ݿ�
#ifdef USELOG
//	if(!(GetLog().InitLog()))
//	{
//		strncpy(ez,GetLang().GetWarningText(14007),256);
//		MessageBox(ez);//"�������ݿ��ļ�"	
//	}

	if(!GetLog().InitLog())
		return false;

//	GetLog().BackupAllLogData(this);

	if(!GetLog().BackupAllLogData(this))							//20190102
		return false;
#endif

//��ʼ����½״̬
	if (!GetLog().isStatusTableEOF())
	{
		CString seqNum,status,strTime;
		GetLog().LoadStatusTable(seqNum,status,strTime);
		TRACE("INFO: init value %ld, %s, %s, %s\n",seqNum,status,strTime);
		GetMainFrame().m_StaRSCurPods = GetLog().GetStatusTableAbsolutePosition();
		GetMainFrame().m_Status = status;
	}
	else
	{
		GetMainFrame().m_StaRSCurPods = 1;
		GetMainFrame().m_Status = "ͣ��״̬";
	}

//��ʼ��ʱ����Ƽ��ܹ�
#ifdef SENTINAL
	if(!GetDoc().InitSentinal())
		return false;
#endif

//�򿪵�¼����
#ifdef LOGIN
	CLoginDialog login;	
	if(login.DoModal()==IDCANCEL )
		exit(1);
#endif

//��ʼ��Ӳ���忨
	if(!GetControl().InitalControl())
		return false;

//��ʼ���ӹ������趨
	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
		if(GetDoc().GetFunctionOverBorad())					//�з��幦��ʱ����ģʽ�趨Ϊ ��A�棨���壩
			GetDoc().SetFlowPathMode(1);
		else												//�޷��幦��ʱ����ģʽ�趨Ϊ ��A�棨�����壩
			GetDoc().SetFlowPathMode(0);
	}
	else													//IO��ʽ�����ϣ���A�棨�����壩
		GetDoc().SetFlowPathMode(0);

	GetDoc().SetASideIsProcessing(true);

//���ó������
	CMenu* mmenu = GetMenu();
	if(GetLang().GetCurLanguage()==1)
		SetUI(mmenu);		

#ifdef ONLYFILE
	TVisualObject *pTab0 = new TVisualObject(VIEWBASE,"",pContext,RUNTIME_CLASS(TTabWnd),TVisualObject::TOS_TABTOP);	
	strncpy(szRead ,GetLang().GetWarningText(10021),20);//"�ļ��趨"
	TVisualObject *pTabView11 = new TVisualObject(FILEINFOSETTINGVIEW,szRead, pContext, RUNTIME_CLASS(CFileInfoSettingView));
	strncpy(szRead ,GetLang().GetWarningText(10027),20);//"ϵͳ����"
	TVisualObject *pTabView21 = new TVisualObject(SYSPARAMVIEW,szRead, pContext, RUNTIME_CLASS(CSysParamView));
	strncpy(szRead ,GetLang().GetWarningText(10038),20);//"�ļ���ͼ"
	TVisualObject *pSplitter = new TVisualObject(4,szRead, 1,2,pContext);
	TVisualObject *pTabView46 = new TVisualObject(0,0,0, pContext, RUNTIME_CLASS(CFilePointView), CSize(770,300));							//20160907
	TVisualObject *pTabView47 = new TVisualObject(IDD_POINTCONTRLVIEW,0,1,pContext, RUNTIME_CLASS(CPointcontrlView), CSize(1024-770,300));

	m_Framework.Add(pTab0);	
	m_Framework.Add(pTab0, pTabView11);   
	m_Framework.Add(pTab0, pTabView21); 	
	m_Framework.Add(pTab0, pSplitter);	
	m_Framework.Add(pSplitter, pTabView47);
	m_Framework.Add(pSplitter, pTabView46);
	
	m_Framework.Create(this);
#else
	TVisualObject *pTab0 = new TVisualObject(VIEWBASE,"",pContext,RUNTIME_CLASS(TTabWnd),TVisualObject::TOS_TABTOP);

	strncpy(szRead ,GetLang().GetWarningText(10021),20);//"�ļ��趨"
	TVisualObject *pTab1 = new TVisualObject(FILEINFOSETBASE,szRead, pContext, RUNTIME_CLASS(TTabWnd));
	strncpy(szRead ,GetLang().GetWarningText(10022),20);//"�����趨"
	TVisualObject *pTab2 = new TVisualObject(PARAMETERBASE,szRead, pContext,RUNTIME_CLASS(TTabWnd));
	strncpy(szRead ,GetLang().GetWarningText(10023),20);//"��������"
	TVisualObject *pTab3 = new TVisualObject(MAINRUNVIEW,szRead, pContext,RUNTIME_CLASS(CMainRunView));
	strncpy(szRead ,GetLang().GetWarningText(10024),20);//"����ά��"
	TVisualObject *pTab4 = new TVisualObject(MAINTAINBASE,szRead, pContext, RUNTIME_CLASS(TTabWnd));
	
	strncpy(szRead ,GetLang().GetWarningText(10021),20);//"�ļ��趨"
	TVisualObject *pTabView11 = new TVisualObject(FILEINFOSETTINGVIEW,szRead, pContext, RUNTIME_CLASS(CFileInfoSettingView));
	strncpy(szRead ,GetLang().GetWarningText(10025),20);//"�����趨"
	TVisualObject *pTabView12 = new TVisualObject(TOOLPARAVIEW,szRead, pContext, RUNTIME_CLASS(CToolParaView));
	strncpy(szRead ,GetLang().GetWarningText(10026),20);//"Ӱ�����"
	TVisualObject *pTabView13 = new TVisualObject(IMAGEPARASETVIEW,szRead, pContext, RUNTIME_CLASS(CImageParaSetView));
	strncpy(szRead ,GetLang().GetWarningText(10039),20);//"�䷽����"
	TVisualObject *pTabView14 = new TVisualObject(INGREDIENTINFOVIEW,szRead, pContext, RUNTIME_CLASS(CIngredientInfoView));
	
	strncpy(szRead ,GetLang().GetWarningText(10027),20);//"ϵͳ����"
	TVisualObject *pTabView21 = new TVisualObject(SYSPARAMVIEW,szRead, pContext, RUNTIME_CLASS(CSysParamView));
	strncpy(szRead ,GetLang().GetWarningText(10028),20);//"��������"
	TVisualObject *pTabView22 = new TVisualObject(OPERATEREFCOORDVIEW,szRead, pContext, RUNTIME_CLASS(COperateRefCoord));
	strncpy(szRead ,GetLang().GetWarningText(10029),20);//"�ӹ�����"
	TVisualObject *pTabView23 = new TVisualObject(PROCPARAVIEW,szRead, pContext, RUNTIME_CLASS(CProcParaView));
	strncpy(szRead ,GetLang().GetWarningText(10030),20);//"�˶�����"
	TVisualObject *pTabView24 = new TVisualObject(MOTIONPARAMETERVIEW,szRead, pContext, RUNTIME_CLASS(CMotionParameterView));
	strncpy(szRead ,GetLang().GetWarningText(10031),20);//"����"
	TVisualObject *pTabView25 = new TVisualObject(MOTIONPOSITIONERRVIEW,szRead, pContext, RUNTIME_CLASS(CPositionErrValueView));
	strncpy(szRead ,GetLang().GetWarningText(10032),20);//"�û��趨"
	TVisualObject *pTabView26 = new TVisualObject(USERINFOVIEW,szRead, pContext, RUNTIME_CLASS(CLoginView));
	
	strncpy(szRead ,GetLang().GetWarningText(10033),20);//"�����ź�"
	TVisualObject *pTabView41 = new TVisualObject(SIGNALINPUTVIEW,szRead, pContext, RUNTIME_CLASS(CSignalInputView));
	strncpy(szRead ,GetLang().GetWarningText(10034),20);//"����ź�"
	TVisualObject *pTabView42 = new TVisualObject(SIGNALOUTPUTVIEW,szRead, pContext, RUNTIME_CLASS(CSignalOutView));
	strncpy(szRead ,GetLang().GetWarningText(10035),20);//"�������"
	TVisualObject *pTabView43 = new TVisualObject(MOTIONCONTROLTESTVIEW,szRead, pContext, RUNTIME_CLASS(CMotionControlTestView));
	strncpy(szRead ,GetLang().GetWarningText(10036),20);//"���ܲ���"
	TVisualObject *pTabView44 = new TVisualObject(TESTFUCTIONVIEW,szRead, pContext, RUNTIME_CLASS(CTestFunctionView));
	strncpy(szRead ,GetLang().GetWarningText(10037),20);//"ϵͳ��־"
	TVisualObject *pTabView45 = new TVisualObject(IDD_SYSTEMLOG,szRead, pContext, RUNTIME_CLASS(CSystemLogView));

	strncpy(szRead ,GetLang().GetWarningText(10038),20);//"�ļ���ͼ"
	TVisualObject *pSplitter = new TVisualObject(4,szRead,1,2,pContext);
//	TVisualObject *pTabView46 = new TVisualObject(0,0,0, pContext, RUNTIME_CLASS(CFilePointView), CSize(770,300));							//20160907
//	TVisualObject *pTabView47 = new TVisualObject(IDD_POINTCONTRLVIEW,0,1,pContext, RUNTIME_CLASS(CPointcontrlView), CSize(1024-770,300));
	TVisualObject *pTabView46 = new TVisualObject(0,0,0, pContext, RUNTIME_CLASS(CFilePointView), CSize(1024-241,500));
	TVisualObject *pTabView47 = new TVisualObject(IDD_POINTCONTRLVIEW,0,1,pContext, RUNTIME_CLASS(CPointcontrlView), CSize(241,500));
	
	pTabView11->SetHotKey('1');
	pTabView12->SetHotKey('2');
	pTabView13->SetHotKey('3');
	pTabView46->SetHotKey('4');
	pTab3->SetHotKey('5');
	pTabView21->SetHotKey('6');
	pTabView22->SetHotKey('7');
	pTabView23->SetHotKey('8');
	pTabView41->SetHotKey('9');
	pTabView42->SetHotKey('a');
	pTabView43->SetHotKey('b');
	pTabView45->SetHotKey('c');
	pTabView14->SetHotKey('d');


	m_Framework.Add(pTab0);
	m_Framework.Add(pTab0, pTab1);     
	m_Framework.Add(pTab0, pTab2);     
	m_Framework.Add(pTab0, pTab3);     
	m_Framework.Add(pTab0, pTab4);     
	
	m_Framework.Add(pTab1, pTabView11);   
	m_Framework.Add(pTab1, pTabView12);   
	m_Framework.Add(pTab1, pTabView13);
	m_Framework.Add(pTab1, pTabView14);

	m_Framework.Add(pTab1, pSplitter);	
	m_Framework.Add(pSplitter, pTabView47);
	m_Framework.Add(pSplitter, pTabView46);	
	
	m_Framework.Add(pTab2, pTabView21);   
	m_Framework.Add(pTab2, pTabView22);
	m_Framework.Add(pTab2, pTabView23); 
	m_Framework.Add(pTab2, pTabView24); 
	m_Framework.Add(pTab2, pTabView25); 
	m_Framework.Add(pTab2, pTabView26); 

	m_Framework.Add(pTab4, pTabView41); 
	m_Framework.Add(pTab4, pTabView42); 
	m_Framework.Add(pTab4, pTabView43); 
	m_Framework.Add(pTab4, pTabView44); 
	m_Framework.Add(pTab4, pTabView45);
//	m_Framework.Add(pTab4, pTabView48);

	m_Framework.Create(this);

//	pTabView11->SetActivePane();

	//PostMessage(WM_SYSKEYDOWN,'d',0);			//��ʾ�䷽��������

	PostMessage(WM_SYSKEYDOWN,'5',0);			//��ʾ�������н���

	
#endif
//	TVisualFrameworkIterator it(m_Framework);
//	while (!it.End()) 
//	{
//		TVisualObject *pObject = it.Get();
//		it++;
//	}

//��ʼ���������״̬���ϵ�״̬��˫��·״̬
#ifdef USEIOCARD
	while(GetControl().QueryIOBit(MOTIONSTOPRESET))
	{
		GetDoc().SetMachinePowerState(FALSE);
		
		strncpy(ez,GetLang().GetWarningText(41003),256);
		if(AfxMessageBox(ez,MB_OKCANCEL)== IDCANCEL)//"����û���ϵ磬���ϵ�!"
			return true;
		
		Delay(500);
	}
	
	GetDoc().SetMachinePowerState(TRUE);
	
	if(LSPATH_CHECKING==1)	//˫��·
	{
		time_t start_time, end_time;

		if(GetDoc().GetTechnicType())
		{
			GetControl().ChannelOutput(OLASERSHUTTER1,MIO_ON);

			start_time = time( NULL );
			while(GetControl().QueryIOBit(ILASERSHUTTERLTP)||GetControl().QueryIOBit(ILASERSHUTTERRTP))
			{	
				end_time = time( NULL );
				if( difftime(end_time, start_time)>5 )
				{
#ifndef LESSWARN
					strncpy(ez,GetLang().GetWarningText(41002),256);
					AfxMessageBox(ez);//"δ���л�������·������!"
#endif
#ifdef USELOG
					GetLog().Append_pro(10007,20008);//"δ���л�������·!","��·�л�"
#endif
				}
			}
		}
		else
		{
			GetControl().ChannelOutput(OLASERSHUTTER1,MIO_OFF);

			start_time = time( NULL );
			while(GetControl().QueryIOBit(ILASERSHUTTERLTN)||GetControl().QueryIOBit(ILASERSHUTTERRTN))
			{	
				end_time = time( NULL );
				if( difftime(end_time, start_time)>5 )
				{
#ifndef LESSWARN
					strncpy(ez,GetLang().GetWarningText(41001),256);
					AfxMessageBox(ez);//"δ���л����̹�·������!"
#endif
#ifdef USELOG
					GetLog().Append_pro(10006,20008);//"δ���л����̹�·!","��·�л�"
#endif
				}
			}
		}
	}
#endif

	unTimer = ::SetTimer(NULL,NULL,1000,TimerProc);
	unTimer1 = ::SetTimer(NULL,NULL,10000,TimerProc1);
	//StartThread();
	//unTimer2 = ::SetTimer(NULL, 0, 1000, TimeProcUploadStatusReport);

#ifdef USELOG
	GetLog().Append_pro(10023,20013);	//"�ɹ�����ϵͳ","��ϵͳ"

	//GetLog().AppendSNOtherStatusTable("����״̬",COleDateTime::GetCurrentTime());				//20160901
#endif

//	GetDoc().SetCurAptNo(0);
//	GetDoc().SetFault(false);
//	GetDoc().SetFaultRun(false);
//	GetDoc().SetWarner(false);

//	CFileFind ffFlild;
//	if (!ffFlild.FindFile("C:\\log"))
//		CreateDirectory("C:\\log",NULL);

	startMachineTime = COleDateTime::GetCurrentTime();
	return true;
}

UINT ThreadProcStatusReport(LPVOID pParam)
{
	CMainFrame *mainFrame = (CMainFrame *)pParam;
	mainFrame->StatusReport();
	return 0;
}

UINT ThreadProcUtilityReport(LPVOID pParam)
{
	CMainFrame *mainFrame = (CMainFrame *)pParam;
	mainFrame->UtilityReport();
	return 0;
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	GetDoc().SaveWebServiceParam();
	m_Framework.Destroy();
	
    if(m_hMutex != NULL)
		ReleaseMutex(m_hMutex);

    ::KillTimer(NULL,unTimer);
    ::KillTimer(NULL,unTimer1);
	//::KillTimer(NULL,unTimer2);

//	GetControl().ReleaseControl();							//20180822ȡ��

#ifdef USERCOGNEX
	CogRelease();
#endif
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
}

void CMainFrame::OnRunPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'5',0);
}

void CMainFrame::OnFunctiontestPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'c',0);
}

void CMainFrame::OnFilesetPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'1',0);	
}

void CMainFrame::OnPorwPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'2',0);	
}

void CMainFrame::OnImagePane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'3',0);	
}

void CMainFrame::OnShowpointPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'4',0);	
}

void CMainFrame::OnSystemparaPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'6',0);	
}

void CMainFrame::OnOpratecoordPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'7',0);	
}

void CMainFrame::OnWorkparaPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'8',0)	;
}

void CMainFrame::OnSingalinputPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'9',0);	
}

void CMainFrame::OnSingaloutputPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'a',0)	;
}

void CMainFrame::OnMotortestPane() 
{
	CWnd * hWnd = AfxGetMainWnd();
	hWnd->PostMessage(WM_SYSKEYDOWN,'b',0);	
}

LRESULT CMainFrame::OnUpdateStatusBar(WPARAM wParam, LPARAM lParam)
{
	CString lpszText = _T("");  
    lpszText.Format("%s",(char *)wParam);
    SetMessageText(lpszText);
    return 0;
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	char ez[256]={""};

//	GetDoc().ReleaseSysDoc();											//20180703 20170719�Ļ� 20180822ȡ��
//	GetDoc().SaveProcessParam();										//20190902 ����	//20200715 ȡ��
/*
	if(m_Framework.Get(TOOLPARAVIEW)->GetFocusFlag())
	{
		if(GetToolView().m_bDataModified)
		{
			strncpy(ez,GetLang().GetWarningText(21081),256);
			int nSel = AfxMessageBox(ez,MB_YESNO);//"�ӹ������Ѿ��ı䣬�����Ƿ񱣴�?"

			if(nSel == IDYES )
				GetToolView().OnToolParaSave();

			GetToolView().m_bDataModified=false;
		}
	}

	strncpy(ez,GetLang().GetWarningText(21016),256);
	if(AfxMessageBox(ez,MB_OKCANCEL) == IDCANCEL)//"ȷ���˳�Lasersystem?"
		return;
*/
	if(AfxMessageBox("ȷ���˳�LaserSystem?",MB_OKCANCEL) == IDCANCEL)
		return;

#ifdef USEIOCARD
	int ionum=0;

#ifdef NEWE2
	ionum=3;
#else
	if(GetDoc().GetUse9112())
		ionum=3;		
	else
		ionum=2;
#endif

	for(int i=0; i<ionum; ++i)
	{
		GetIO(IOMODE).Release(i);								//20190102
	}
#endif

#ifdef USEMOTION
	GetMotion().Release();										//20181214
#endif

#ifdef USELOG
	GetLog().AppendSNOtherStatusTable("ͣ��״̬",COleDateTime::GetCurrentTime());				
#endif	

	CFrameWnd::OnClose();
}

void CMainFrame::OnUpdateAptNo(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str;

	char szRead[20]={""};
	if(GetDoc().GetCurAptNo()==0)
	{
		strncpy(szRead,GetLang().GetWarningText(21017),20);
		str.Format("  %s",szRead);;//"δ����";
	}
	else
	{
		str.Format( "  %d#",GetDoc().GetCurAptNo());  
	}
    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateOptPathMode(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str;

	char szRead[20]={""};
	if(GetDoc().GetTechnicType())
	{
		strncpy(szRead,GetLang().GetWarningText(21018),20);
		str.Format("  %s",szRead);;//"����·";
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(21019),20);
		str.Format("  %s",szRead);;//"�̹�·";
	}
    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateBeamMode(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
}

void CMainFrame::OnUpdateGalvoLeft(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str;
	char szRead[20]={""};

	if(GetDoc().GetAutoAdjustPattern(HeadLeft))
	{
		strncpy(szRead,GetLang().GetWarningText(21020),20);
		str.Format("  %s",szRead);//"���񾵣�NG";
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(21021),20);
		str.Format("  %s",szRead);//"���񾵣�OK";  
	}
    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateGalvoRight(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str;

	char szRead[20]={""};
	if(GetDoc().GetAutoAdjustPattern(HeadRight))
	{
		strncpy(szRead,GetLang().GetWarningText(21022),20);
		str.Format("  %s",szRead);//"���񾵣�NG";
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(21023),20);
		str.Format("  %s",szRead);;//"���񾵣�OK";  
	}
    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdatePowerLeft(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str;

	char szRead[20]={""};
	if(GetDoc().GetAutoLaserPowerTest(HeadLeft))
	{
		strncpy(szRead,GetLang().GetWarningText(21024),20);
		str.Format("  %s",szRead);;//"���ʣ�NG";
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(21025),20);
		str.Format("  %s",szRead);;//"���ʣ�OK";  
	}
    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdatePowerRight(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str;

	char szRead[20]={""};
	if(GetDoc().GetAutoLaserPowerTest(HeadRight))
	{
		strncpy(szRead,GetLang().GetWarningText(21026),20);
		str.Format("  %s",szRead);;//"�ҹ��ʣ�NG";
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(21027),20);
		str.Format("  %s",szRead);;//"�ҹ��ʣ�OK";  
	}
    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateProcAxisMode(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str="   ˫  ��";
	
	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
//		if(!GetDoc().GetFunctionOverBorad())	//20190612	ȡ��	//�޷��幦��ʱ��֧�ֵ����˫��ӹ����з��幦��ʱĿǰֻ֧��˫��ӹ�������ӹ���֧��
//		{
			if(GetDoc().GetProcAxisMode()==0)
				str="   ˫  ��";
			else if(GetDoc().GetProcAxisMode()==1)
				str="   ������";
			else
				str="   ������";
//		}
	}

    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateFlowPathMode(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str="��A��(������)";

	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
		if(GetDoc().GetFunctionOverBorad())					//�з��幦��
		{
			if(GetDoc().GetFlowPathMode()==0)
				str="��A��(������)";
			else if(GetDoc().GetFlowPathMode()==1)
				str=" ��A��(����)";
			else if(GetDoc().GetFlowPathMode()==2)
				str="   A&B˫��";
			else
				str="    ��B��";
		}
	}

    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateCurFileDisplay(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str="";
	
	if((GetDoc().GetFlowPathMode()==2)&&GetDoc().GetFileOpenState())
	{
		if(GetDoc().GetASideIsDisplay())
			str="  ��ʾ:A��";
		else
			str="  ��ʾ:B��";
	}

    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateCurFlowStatus(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str="";

	if((GetDoc().GetFlowPathMode()==2)&&GetDoc().GetFileOpenState())
	{
		if(GetDoc().GetASideIsProcessing())
			str="  �ӹ�:A��";
		else
			str="  �ӹ�:B��";
	}

    pCmdUI->SetText( str );
}

void CMainFrame::OnUpdateMachineStatus(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(); 
    CString str="";
	long seconds  = LoadLightStatusTableToCalcRunRate();

	CString dayDt;
	CString nightDt;
	
	time_t timep;
	time(&timep);
	char currentDate[64];
	strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localtime(&timep));

	//��ǰ�豸�ڶ���ʵʱ��ʾ
	if (seconds != 0)
	{
		m_Operation_Rate = ((double)(seconds)/(60*60*12))*100;
	}
	else
	{
		m_Operation_Rate = 0;
	}
	str.Format("%.4f%%",m_Operation_Rate);
}

/*
void CMainFrame::StartThread()
{
	try
	{
		m_hThread = (HANDLE)::CreateThread(NULL, 0, StatusReportUploadProc, NULL, 0, NULL);
		HANDLE hArray[1] = {m_hThread};
		WaitForMultipleObjects(1, hArray, TRUE, INFINITE);
		CloseHandle(m_hThread);
	}
	catch (...)
	{
		TRACE("error:StartThread error...");
	}
}*/

/*
//ÿ5��ִ��ִ��һ��
DWORD WINAPI StatusReportUploadProc(LPVOID args)
{
     BOOL bRet = FALSE;
     MSG msg = { 0 };
     //����һ:������ʱ��
     //���hWndΪNULL������ֵΪ�½�����timer��ID
     //UINT timerid = SetTimer(NULL, 0, 5000, (TIMERPROC)TimeProcUploadStatusReport);

     while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
     {
         if (bRet == -1)
         {
             // handle the error and possibly exit  
         }
         else
         {
             //����ʱ����Ϣ���ݸ�so��Ϣ����,�������ܴ���Timerprocִ��
             TranslateMessage(&msg);
             DispatchMessage(&msg);
         }
     }
     //�����������ٶ�ʱ��
	 KillTimer(NULL, timerid);
     
     return 0;
}*/

VOID CALLBACK TimeProcUploadStatusReport(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	// TODO: Add your message handler code here and/or call default

	CString seqNum,finalStatus,finalTime;
	if (!GetLog().isStatusTableEOF())
	{
		GetLog().LoadStatusTable(seqNum,finalStatus,finalTime);
	}	
	if (finalStatus.Compare(GetMainFrame().m_Status) != 0 && GetMainFrame().m_Status !="")
	{
		GetMainFrame().m_Status = finalStatus;
		//GetMainFrame().m_wndStatusBar.SetPaneText(11,finalStatus,TRUE);
		//AfxBeginThread(ThreadProcStatusReport,GetMainFrame(),0,0,0,NULL);
	}
}

void CMainFrame::StatusReport()
{
	BOOL result = false;
	int times = 0;
	int errCode = 0;
	
	Request req;
	Response rsp;
	CString uuid  = req.UuidGenerator();
	
	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	CString failedDataBackup = GetDoc().GetAppPath()+"info\\"+"StatusChangeReport.txt";

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
	reqBody["report_dt"] = Json::Value(currentTime);
	reqBody["keep_reason"] = Json::Value("0");
	if (GetDoc().GetSysModeSwitch())//����ģʽ
	{
		reqBody["cim_mode"] = Json::Value("Remote");
	}
	else
	{
		reqBody["cim_mode"] = Json::Value("Local");
	}

	if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
	{
		reqBody["auto_mode"] = Json::Value("Auto");
	}
	else
	{
		reqBody["auto_mode"] = Json::Value("Manual");	
	}

	if (GetMainFrame().m_Status == "����״̬")
	{
		reqBody["status_id"] = Json::Value("Idle");//Idle, Run, Stop, Initial and Down
	}
	if(GetMainFrame().m_Status == "����״̬")
	{
		reqBody["status_id"] = Json::Value("Run");
	}
	if(GetMainFrame().m_Status == "����״̬")
	{
		reqBody["status_id"] = Json::Value("Down");
	}
	if(GetMainFrame().m_Status == "ͣ��״̬")
	{
		reqBody["status_id"] = Json::Value("Stop");
	}
	if(GetMainFrame().m_Status == "��ʼ״̬")
	{
		reqBody["status_id"] = Json::Value("Initial");
	}
	int index = GetDoc().GetLastAlarmId();
	CString alarmid;
	alarmid.Format("%0.4d",index);
	if (GetMainFrame().m_Status == "����״̬")
	{
		if(index<0)
			reqBody["alarm_id"] = Json::Value("0000");
		else
			reqBody["alarm_id"] = Json::Value(alarmid);	
	}
	else
	{
		reqBody["alarm_id"] = Json::Value("0000");
	}
	req.setReqBody(reqBody);
	fstream file;
	streampos fp;
	file.open(failedDataBackup,ios::in);
	if (file.is_open())
	{
		file.seekg(0,ios::end);
		fp = file.tellg();
	}
	file.close();
	if (!GetDoc().GetSysModeSwitch() || (int(fp) != 0))//����ģʽ
	{
		if((int(fp) != 0) && GetDoc().GetSysModeSwitch())
		{
			reqBody["cim_mode"] = Json::Value("Remote");
			reqBody["keep_reason"] = Json::Value("0");
		}
		else
		{
			reqBody["cim_mode"] = Json::Value("Local");
			reqBody["keep_reason"] = Json::Value("1");
		}
		
		req.setReqBody(reqBody);
		CString reqAndRsp;
		Json::FastWriter fast_writer;
		reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
			fast_writer.write(req.getReqHead()).c_str(),\
			fast_writer.write(req.getReqBody()).c_str());
		GetMainFrame().cs_status.Lock();
		GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
		GetMainFrame().cs_status.Unlock();
	}
	else
	{
		for (int i=0; i<3; i++)
		{
			errCode = GetWSInterfaceImplementor().StatusChangeReport(req, rsp);
			if (errCode == STS_OK)
			{
				result = true;
				times = 0;
				break;
			}
			else
			{
				times ++;
				CString tips;
				tips.Format("״̬�仯�ش���,����:%d,ʱ��:%s",times,currentTime);
				::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
				result = false;
				continue;
			}
		}
		if (result)
		{
			CString tips;
			tips.Format("״̬�仯�ϴ��ɹ�,ʱ��:%s",currentTime);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
		}
		else
		{
			CString tips;
			CString reason;
			CString remarks;
			if(!rsp.getRspHead()["rtn_msg"].isNull())
				reason = rsp.getRspHead()["rtn_msg"].asCString();
			else
				reason = StringOfBaseStatus[errCode].pString;
			remarks = req.getReqBody()["status_id"].asCString();
			tips.Format("״̬�仯�ϴ�ʧ��,ԭ��:%s,ʱ��:%s",reason,currentTime);
			GetLog().Append_pro(reason,"״̬�ϴ�",remarks);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			
			reqBody["keep_reason"] = Json::Value("2");
			req.setReqBody(reqBody);
			CString reqAndRsp;
			Json::FastWriter fast_writer;
			reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
				fast_writer.write(req.getReqHead()).c_str(),\
				fast_writer.write(req.getReqBody()).c_str());
			GetMainFrame().cs_status.Lock();
			GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
			GetMainFrame().cs_status.Unlock();
		}
	}

	//RealStatusReport
	times = 0;
	reqBody["tower_red"] = Json::Value("OFF");
	reqBody["tower_yellow"] = Json::Value("OFF");
	reqBody["tower_green"] = Json::Value("OFF");
	reqBody["tower_blue"] = Json::Value("OFF");
	
	if (GetControl().GetLampStatus() == 0)
	{
		reqBody["tower_green"] = Json::Value("ON");
	}
	else if(GetControl().GetLampStatus() == 1)
	{
		reqBody["tower_red"] = Json::Value("ON");
	}
	else
	{
		reqBody["tower_yellow"] = Json::Value("ON");
	}
	
	req.setReqBody(reqBody);
	if (!GetDoc().GetSysModeSwitch())//����ģʽ
	{
		reqBody["cim_mode"] = Json::Value("Local");
		reqBody["keep_reason"] = Json::Value("1");
		req.setReqBody(reqBody);
	}
	else
	{
		reqBody["cim_mode"] = Json::Value("Remote");
		reqBody["keep_reason"] = Json::Value("0");
		req.setReqBody(reqBody);
	}
	
	for (int j=0; j<3; j++)
	{
		errCode = GetWSInterfaceImplementor().RealStatusReport(req, rsp);
		if (errCode == STS_OK)
		{
			result = true;
			times = 0;
			break;
		}
		else
		{
			times ++;
			CString tips;
			tips.Format("��ʱ״̬�ش���,����:%d,ʱ��:%s",times,currentTime);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			result = false;
			continue;
		}
	}
	if (result)
	{
		CString tips;
		tips.Format("��ʱ״̬�ϴ��ɹ�,ʱ��:%s",currentTime);
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
	}
	else
	{
		CString tips;
		CString reason;
		CString remarks;
		if(!rsp.getRspHead()["rtn_msg"].isNull())
			reason = rsp.getRspHead()["rtn_msg"].asCString();
		else
			reason = StringOfBaseStatus[errCode].pString;
		remarks = req.getReqBody()["status_id"].asCString();
		tips.Format("��ʱ״̬�ϴ�ʧ��,ԭ��:%s,ʱ��:%s",reason,currentTime);
		GetLog().Append_pro(reason,"��ʱ״̬�ϴ�",remarks);
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
	}
}


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default 
    CString strTime; 
	int shiftFlag;
    COleDateTime curTime = COleDateTime::GetCurrentTime();  
	if (8<=curTime.GetHour() && curTime.GetHour()<20)
	{
		shiftFlag = 1;
	}
	else
	{
		shiftFlag = 2;
	}
	
	if (shiftFlag != m_shift)
	{
		m_shift = shiftFlag;
	}

    strTime = curTime.Format(_T("%H:%M:%S"));  
	
	if (strTime.Compare(GetDoc().GetOperationRateTime()) == 0 \
		|| (strTime.Compare(GetDoc().GetOperationRateTimeNight()) == 0))
	{
		AfxBeginThread(ThreadProcUtilityReport,this,0,0,0,NULL);
	}

	long lastlpods=-1;
	vector<CString> csv_Status;
	if (!GetLog().isStatusTableEOF())
	{
		lastlpods = GetLog().GetStatusTableAbsolutePosition();
		if (GetMainFrame().m_StaRSCurPods != lastlpods)
		{
			GetLog().LoadStatusTableV(GetMainFrame().m_StaRSCurPods,lastlpods,csv_Status);
			GetMainFrame().m_StaRSCurPods = lastlpods;
		}
	}

	for (int i=0;i<csv_Status.size();i++)
	{
		if (GetMainFrame().m_Status.Compare(csv_Status[i]) != 0)
		{
			GetMainFrame().m_Status = csv_Status[i];
			CString enstatus;
			if (GetMainFrame().m_Status == "����״̬") //Idle, Run, Stop, Initial and Down
			{
				enstatus = "Idle";
			}
			if(GetMainFrame().m_Status == "����״̬")
			{
				enstatus = "Run";
			}
			if(GetMainFrame().m_Status == "����״̬")
			{
				enstatus = "Down";
			}
			if(GetMainFrame().m_Status == "ͣ��״̬")
			{
				enstatus = "Stop";
			}
			if(GetMainFrame().m_Status == "��ʼ״̬")
			{
				enstatus = "Initial";
			}

			this->m_wndStatusBar.SetPaneText(11,enstatus,TRUE);
			AfxBeginThread(ThreadProcStatusReport,GetMainFrame(),0,0,0,NULL);
			Sleep(100);
		}
	}
	
	if(GetControl().QueryIOBit(MOTIONSTOPRESET))
	{
		GetLog().AppendSNOtherStatusTable("ͣ��״̬",COleDateTime::GetCurrentTime());
	}

	CString str="��A��(������)";
	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
		if(GetDoc().GetFunctionOverBorad())					//�з��幦��
		{
			if(GetDoc().GetFlowPathMode()==0)
				str="��A��(������)";
			else if(GetDoc().GetFlowPathMode()==1)
				str=" ��A��(����)";
			else if(GetDoc().GetFlowPathMode()==2)
				str="   A&B˫��";
			else
				str="    ��B��";
		}
	}
	this->m_wndStatusBar.SetPaneText(4,str,TRUE);

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::UtilityReport() 
{	
	BOOL ret = false;
	int times = 0;
	int errCode;
	
	Request req;
	Response rsp;
	CString uuid  = req.UuidGenerator();
	
	time_t timep;
	time(&timep);
	char currentDate[64];
	char currentTime[64];
	strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localtime(&timep));
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	CString failedDataBackup = GetDoc().GetAppPath()+"info\\"+"UtilityReport.txt";
	
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
	Json::Value	arr,reportDateitem,opRateitem,energyPreitemL,energyPreitemR,cameraitemL,cameraitemR;
	reqBody["report_dt"] = Json::Value(currentTime);
	reqBody["keep_reason"] = Json::Value("0");
	//reqBody["shift_id"] = Json::Value(GetDoc().GetCurUserShift());
	
	//�ڶ���
	CString operationRate;
	operationRate.Format("%.4f%%",m_Operation_Rate);
	opRateitem["item_id"] =Json::Value("U001");
	opRateitem["item_value"] =Json::Value(operationRate);
	
	CString reportdate;
	reportDateitem["item_id"] =Json::Value("report_date");

	COleDateTime curTime = COleDateTime::GetCurrentTime();  
    CString strTime = curTime.Format(_T("%H:%M:%S")); 
	
	if (strTime.Compare(GetDoc().GetOperationRateTimeNight()) == 0)//���
	{
		COleDateTime dateTime,eTime;
		eTime = COleDateTime::GetCurrentTime();
		COleDateTimeSpan TimeSpan(1,0,0,0);
		dateTime = eTime - TimeSpan; 
		reportdate.Format("%d-%d-%d",dateTime.GetYear(),dateTime.GetMonth(),dateTime.GetDay());
		reportDateitem["item_value"] =Json::Value(reportdate);
		reqBody["shift_id"] = Json::Value("2");
	}
	else //�װ�
	{
		reportDateitem["item_value"] =Json::Value(currentDate);
		reqBody["shift_id"] = Json::Value("1");
	}
	
	//��������
	CString strPowerL,strPowerR;
	GetLog().LoadPowerForUpload(strPowerL,strPowerR);
	if (strPowerL=="")
	{
		energyPreitemL["item_id"] =Json::Value("U002");
		energyPreitemL["item_value"] =Json::Value("0");
	}
	else
	{
		energyPreitemL["item_id"] =Json::Value("U002");
		energyPreitemL["item_value"] =Json::Value(strPowerL);
	}
	if (strPowerR=="")
	{
		energyPreitemR["item_id"] =Json::Value("U003");
		energyPreitemR["item_value"] =Json::Value("0");
	}
	else
	{
		energyPreitemR["item_id"] =Json::Value("U003");
		energyPreitemR["item_value"] =Json::Value(strPowerR);
	}
	
	//�񾵾���
	CString strGlvAdjPreL;
	CString strGlvAdjPreR;
	GetLog().LoadProForUpload(strGlvAdjPreL,strGlvAdjPreR);
	if(strGlvAdjPreL == "")
	{
		cameraitemL["item_id"] =Json::Value("U004");
		cameraitemL["item_value"] =Json::Value("0");
	}
	else
	{
		cameraitemL["item_id"] =Json::Value("U004");
		cameraitemL["item_value"] =Json::Value(strGlvAdjPreL);
	}
	if(strGlvAdjPreR == "")
	{
		cameraitemR["item_id"] =Json::Value("U005");
		cameraitemR["item_value"] =Json::Value("0");
	}
	else
	{
		cameraitemR["item_id"] =Json::Value("U005");
		cameraitemR["item_value"] =Json::Value(strGlvAdjPreR);
	}
	//if(isFourHours.GetTotalSeconds() == 14400)
	//{
	arr["utl"].append(reportDateitem);
	arr["utl"].append(opRateitem);
	arr["utl"].append(energyPreitemL);
	arr["utl"].append(energyPreitemR);
	arr["utl"].append(cameraitemL);
	arr["utl"].append(cameraitemR);
	//}
	reqBody["utl_infos"] = arr;
	req.setReqBody(reqBody);

	fstream file;
	streampos fp;
	file.open(failedDataBackup,ios::in);
	if (file.is_open())
	{
		file.seekg(0,ios::end);
		fp = file.tellg();
	}
	file.close();

	if (!GetDoc().GetSysModeSwitch() || (int(fp) != 0))//����ģʽ
	{
		if((int(fp) != 0) && GetDoc().GetSysModeSwitch())
		{
			reqBody["keep_reason"] = Json::Value("0");
		}
		else
		{
			reqBody["keep_reason"] = Json::Value("1");
		}
		req.setReqBody(reqBody);
		CString reqAndRsp;
		Json::FastWriter fast_writer;
		reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
			fast_writer.write(req.getReqHead()).c_str(),\
			fast_writer.write(req.getReqBody()).c_str());
		GetMainFrame().cs_utility.Lock();
		GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
		GetMainFrame().cs_utility.Unlock();
	}
	else
	{
		for (int i=0; i<3; i++)
		{
			errCode = GetWSInterfaceImplementor().UtilityReport(req, rsp);
			if (errCode == STS_OK)
			{
				ret = true;
				times = 0;
				break;
			}
			else
			{
				times ++;
				CString tips;
				tips.Format("�ڶ����ش���,����:%d,ʱ��:%s",times,currentTime);
				::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
				ret = false;
				continue;
			}
		}
		
		if (ret)
		{
			CString tips;
			tips.Format("�ڶ����ϴ��ɹ�,ʱ��:%s",currentTime);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
		}
		else
		{
			CString tips;
			CString reason;
			if(!rsp.getRspHead()["rtn_msg"].isNull())
				reason = rsp.getRspHead()["rtn_msg"].asCString();
			else
				reason = StringOfBaseStatus[errCode].pString;
			tips.Format("�ڶ����ϴ�ʧ��,ԭ��:%s,ʱ��:%s",reason,currentTime);
			GetLog().Append_pro(reason,"�ڶ����ϴ�",operationRate);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			
			reqBody["keep_reason"] = Json::Value("2");
			req.setReqBody(reqBody);
			CString reqAndRsp;
			Json::FastWriter fast_writer;
			reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
				fast_writer.write(req.getReqHead()).c_str(),\
				fast_writer.write(req.getReqBody()).c_str());
			GetMainFrame().cs_utility.Lock();
			GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
			GetMainFrame().cs_utility.Unlock();
		}
	}	
}

long CMainFrame::LoadLightStatusTableToCalcRunRate()
{
	CString currUserName = GetDoc().GetCurUserName();
	COleDateTime firstDateTime,nextDateTime;
	COleDateTimeSpan timeSpan;
	long seconds = 0;

	CString strTimeA,strTimeB;
	COleDateTime startDt,endDt;
	if (m_shift ==1)
	{
		endDt = COleDateTime::GetCurrentTime();
		startDt	= endDt; 
		strTimeB.Format("%d/%d/%d %s",startDt.GetYear(),startDt.GetMonth(),startDt.GetDay(),GetDoc().GetOperationRateTime());
		strTimeA.Format("%d/%d/%d %s",endDt.GetYear(),endDt.GetMonth(),endDt.GetDay(),GetDoc().GetOperationRateTimeNight());
	}
	else
	{
		startDt = COleDateTime::GetCurrentTime();
		COleDateTimeSpan TimeSpan(1,0,0,0);
		endDt = startDt - TimeSpan; 
		strTimeA.Format("%d/%d/%d %s",endDt.GetYear(),endDt.GetMonth(),endDt.GetDay(),GetDoc().GetOperationRateTime());
		strTimeB.Format("%d/%d/%d %s",startDt.GetYear(),startDt.GetMonth(),startDt.GetDay(),GetDoc().GetOperationRateTimeNight());
	}
	
	bool isfirst = false;
	GetLog().LightStatusTableMoveFirst();
	while (!GetLog().isLightStatusTableEOF())
	{
		CString lampStatus,strTime;
		COleDateTime dateTime;
		GetLog().LoadLightStatusTable(lampStatus,dateTime);
		strTime.Format("%d/%d/%d %d:%d:%d",dateTime.GetYear(),dateTime.GetMonth(),dateTime.GetDay(),dateTime.GetHour(),dateTime.GetMinute(),dateTime.GetSecond());
		if(strTimeA.Compare(strTime)<=0 && strTime.Compare(strTimeB)<=0)
		{	
			if (lampStatus == "��" && isfirst == false)
			{
				GetLog().LightStatusTableMoveNext();
				continue;
			}
			if (lampStatus == "��" && isfirst == false)
			{
				firstDateTime = dateTime;
				isfirst = true;
				GetLog().LightStatusTableMoveNext();
				continue;
			}
			if (lampStatus == "��" && isfirst == true)
			{
				long interval = 0;
				nextDateTime = dateTime;
				timeSpan = nextDateTime-firstDateTime;
				interval = timeSpan.GetHours()*60*60+timeSpan.GetMinutes()*60+timeSpan.GetSeconds();
				seconds += interval;
				isfirst = false;
				GetLog().LightStatusTableMoveNext();
				continue;
			}
		}
		GetLog().LightStatusTableMoveNext();
	}
	return seconds;
}
