// MainRunView.cpp : implementation file
//

#include "stdafx.h"
//#include "lasersystem.h"
#include "MainRunView.h"
#include "Excellon.h"
#include "OperateControl.h"
#include "mainfrm.h"
#include "CBmpMenu.h"
#include "WarningInfo.h"
#include "ImageParaSetView.h"
#include "IngredientInfoView.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "hasp_api.h"			//SENTINAL
//#include "hasp_vcode.h"       /* contains HASP DEMOMA vendor code */

/////////////////////////////////////////////////////////////////////////////
// CMainRunView
CMainRunView* pCMainRunView;								//20190215
extern CImageParaSetView *pImageParaSetView;				//20190403
extern CIngredientInfoView *pIngredientInfoView;
////////////////////////////////
BOOL LeftPareSt;
BOOL RightPareSt;
BOOL bInDelay=false;										//20190329
BOOL bRunning=false;										//20190401
bool bInPowerTest=false;									//20190626
///////////////////////////////
CCheckerCtrl CMainRunView::m_ctrlChecker;
CProgressCheckCtrl CMainRunView::m_ctrlChecker1;
UINT CMainRunView::m_ulLastBlockSize=0;
IMPLEMENT_DYNCREATE(CMainRunView, TVisualFormView)

/*CString strProcInfo[]=
{
	"总气路气压低",					//0
	"保护气流量报警",               //1
	"小冷水机报警",					//2
	"AOM错误报警",					//3
	"激光器报警",                   //4
	"左侧振镜未上电",				//5
	"右侧振镜未上电",				//6
    "左侧振镜温度低",				//7
    "右侧振镜温度低",				//8
    "运动卡1错误报警",				//9
    "运动卡2错误报警",				//10
    "X轴电机伺服报警",				//11
    "Y轴电机伺服报警",				//12
    "Z1轴电机伺服报警",				//13
    "Z2轴电机伺服报警",				//14 
    "BET主动轴伺服报警",			//15
    "BET从动轴伺服报警",			//16
	"电机未上电报警",               //17
    "X轴光栅尺错误",				//18 
    "Y轴光栅尺错误",				//19
    "左测厚光栅尺错误",				//20
	"右测厚光栅尺错误",             //21  
	"左吸尘静压报警",				//22
	"右吸尘静压报警",				//23
	"保护窗1报警",					//24
	"保护窗2报警",					//25
	"门安全保护报警",				//26
};*/

CString plcSignalOutputMRV[24]=
{//增加6+2个OUT 
	"00FFBW0M0408011",//0   料仓再次加料
	"00FFBW0M0409011",//1   平台取了完成
	"00FFBW0M0410011",//2   下料准备取料
	"00FFBW0M0411011",//3   开始运行
	"00FFBW0M0412011",//4   左侧加工失败
	"00FFBW0M0413011",//5   右侧加工失败
	"00FFBW0M0414011",//6   平台可以上料
	"00FFBW0M0415011",//7   下料可以取料
	"00FFBW0M0416011",//8   整体回零
	"00FFBW0M0417011",//9   结束运行
	"00FFBW0M0418011",//10  暂停(含光幕)
	"00FFBW0M0419011",//11  暂停复位
	"00FFBW0M0420011",//12  上料单循环
	"00FFBW0M0421011",//13  下料单循环 //一键下料
	"00FFBW0M0422011",//14  Z1轴加工循环 
	"00FFBW0M0423011",//15  Z2轴加工循环
	"00FFBW0M0467011",//16  翻板循环                  //////////////
	"00FFBW0M0468011",//17  逆向循环
	"00FFBW0M0469011",//18  逆向平台可以上料
	"00FFBW0M0470011",//19  逆向平台取料完成
	"00FFBW0M0471011",//20  逆向下料准备取料
	"00FFBW0M0472011",//21  逆向下料可以取料
	"00FFBW0M0473011",//22  逆向NG准备取料
	"00FFBW0M0474011",//23  逆向NG可以取料
};

CMainRunView& GetRunView()
{
	static CMainRunView view;
	return view;
}

CMainRunView::CMainRunView()
	: TVisualFormView(CMainRunView::IDD)
{
	//{{AFX_DATA_INIT(CMainRunView)
	m_bAutoProc = 0;
	m_strFileName = _T("");
	m_strProcedNum = _T("");
	m_strProcInfo = _T("");
	m_nAutoMatch = 0;
	m_strPCBHoleCount = _T("");
	m_bAutoAdjust = FALSE;
	m_bAutoPower = FALSE;
	m_DrilledHoleCount = _T("");
	m_CurArea = _T("");
	m_bFidRetry = FALSE;
	m_bManuFid = FALSE;
	m_strHoleSum = _T("");
	m_strNGSum = _T("");
	m_strMatchScore = _T("");
	m_strLRScale = _T("");
	m_bOneAxis = FALSE;
	m_bCheckNullHoles = FALSE;
	m_lRunState = -1;
	m_lPitchHeadNo =0;
	m_strFileNameNew = _T("");
	//}}AFX_DATA_INIT
	m_bIsDisplay = FALSE;
}

CMainRunView::~CMainRunView()
{
}

void CMainRunView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainRunView)
	DDX_Control(pDX, IDC_CHECK_NULLDRILLHOLES, m_CheckNullHoles);
	DDX_Control(pDX, IDC_CHECKSELECTOTHERS, m_CheckSelectOthers);
	DDX_Control(pDX, IDC_MATCH, m_sMatch);
	DDX_Control(pDX, IDC_HOLES_SUM, m_stHoleSum);
	DDX_Control(pDX, IDC_NG_SUM, m_stNGSum);
	DDX_Control(pDX, IDC_CHK_MANUFID, m_chkManuFid);
	DDX_Control(pDX, IDC_CURAREA, m_stCurarea);
	DDX_Control(pDX, IDC_ST_CURAREA, m_stCurArea);
	DDX_Control(pDX, IDC_ST_DRILLEDHOLES, m_stPCBDrilledHolecount);
	DDX_Control(pDX, IDC_PCBDRILLEDHOLENUM, m_pcbdrilledholenum);
	DDX_Control(pDX, IDC_ADJUSTWAR, m_cAdjustWar);
	DDX_Control(pDX, IDC_LASERPOWERWAR, m_cLaserpowerWar);
	DDX_Control(pDX, IDC_PRO_LASERPOWAR, m_proLaserPowerWar);
	DDX_Control(pDX, IDC_PRO_GALVOADJWAR, m_proGalvoAdjWar);
	DDX_Control(pDX, IDC_PCBHOLENUM, m_pcbholenum);
	DDX_Control(pDX, IDC_BT_CLEAR, m_btnClean);
	DDX_Control(pDX, IDC_STATIC3, m_ProcInfo);
	DDX_Control(pDX, IDC_ST_PCBHOLE, m_stPCBHoleCount);
	DDX_Control(pDX, IDC_ST_PROCINFO, m_stProcInfo);
	DDX_Control(pDX, IDC_STATIC2, m_ProcedNum);
	DDX_Control(pDX, IDC_STATIC1, m_FileName);
	DDX_Control(pDX, IDC_ST_PROCEDNUM, m_stProcedNum);
	DDX_Control(pDX, IDC_FILENAME, m_stFileName);
	DDX_Control(pDX, IDC_BT_RUN_START, m_btnRunStart);
	DDX_Control(pDX, IDC_BT_RUN_PAUSE, m_btnRunPause);
	DDX_Control(pDX, IDC_BT_HOMEALL, m_btnHomeAll);
	DDX_Control(pDX, IDC_BT_SETPARAMETER, m_btnSetParameter);
	DDX_Control(pDX, IDC_BT_SCANADJUST, m_btnScanAdjust);
	DDX_Control(pDX, IDC_BT_RUN_END, m_btnRunEnd);
	DDX_Control(pDX, IDC_BT_LASERWARMUP, m_btnLaserWarmup);
	DDX_Control(pDX, IDC_BT_EXIT, m_btnExit);
	DDX_Radio(pDX, IDC_RAD_AUTOPROC, m_bAutoProc);
	DDX_Text(pDX, IDC_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_ST_PROCEDNUM, m_strProcedNum);
	DDX_Text(pDX, IDC_ST_PROCINFO, m_strProcInfo);
	DDX_Radio(pDX, IDC_RADAUTO, m_nAutoMatch);
	DDX_Text(pDX, IDC_ST_PCBHOLE, m_strPCBHoleCount);
	DDX_Check(pDX, IDC_CHK_ENABLEAUTOADJUST, m_bAutoAdjust);
	DDX_Check(pDX, IDC_CHK_ENABLEAUTOPOWER, m_bAutoPower);
	DDX_Text(pDX, IDC_ST_DRILLEDHOLES, m_DrilledHoleCount);
	DDX_Text(pDX, IDC_ST_CURAREA, m_CurArea);
	DDX_Check(pDX, IDC_FIDRETRY, m_bFidRetry);
	DDX_Check(pDX, IDC_CHK_MANUFID, m_bManuFid);
	DDX_Text(pDX, IDC_HOLES_SUM, m_strHoleSum);
	DDX_Text(pDX, IDC_NG_SUM, m_strNGSum);
	DDX_Text(pDX, IDC_MATCHSCORE, m_strMatchScore);
	DDV_MaxChars(pDX, m_strMatchScore, 10);
	DDX_Text(pDX, IDC_STATIC_LRSCALE, m_strLRScale);
	DDX_Check(pDX, IDC_ONEAXIS, m_bOneAxis);
	DDX_Check(pDX, IDC_CHECK_NULLDRILLHOLES, m_bCheckNullHoles);
	DDX_Text(pDX, IDC_EDT_FILENAMENEW, m_strFileNameNew);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainRunView, TVisualFormView)
	//{{AFX_MSG_MAP(CMainRunView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_RUN_CONT, OnRunCont)
	ON_BN_CLICKED(IDC_BT_RUN_PAUSE, OnRunPause)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_RUN_START, OnRunStart)
	ON_BN_CLICKED(IDC_RAD_AUTOPROC, OnRadAutoproc)
	ON_BN_CLICKED(IDC_BT_EXIT, OnExit)
	ON_BN_CLICKED(IDC_BT_RUN_END, OnRunEnd)
	ON_BN_CLICKED(IDC_BT_SCANADJUST, OnScanAdjust)
	ON_BN_CLICKED(IDC_BT_LASERWARMUP, OnLaserWarmup)
	ON_BN_CLICKED(IDC_BT_HOMEALL, OnHomeall)
	ON_BN_CLICKED(IDC_BT_SETPARAMETER, OnSetParameter)
	ON_BN_CLICKED(IDC_BT_CLEAR, OnClearProcNum)
	ON_WM_TIMER()
//	ON_BN_CLICKED(IDC_BT_TOPOINT, OnBtTopoint)
	ON_BN_CLICKED(IDC_RADAUTO, OnRadauto)
	ON_BN_CLICKED(IDC_RADMANU, OnRadmanu)
	ON_BN_CLICKED(IDC_CHK_ENABLEAUTOADJUST, OnChkEnableautoadjust)
	ON_BN_CLICKED(IDC_CHK_ENABLEAUTOPOWER, OnChkEnableautopower)
	ON_MESSAGE(WM_MSG_PREHOT,MachinePreHot)//机器预热
	ON_BN_CLICKED(IDC_FIDRETRY, OnFidRetry)
	ON_BN_CLICKED(IDC_CLEAR_NG, OnClearNg)
	ON_BN_CLICKED(IDC_CLR_HOLES, OnClrHoles)
	ON_BN_CLICKED(IDC_CHK_MANUFID, OnChkManufid)
	ON_BN_CLICKED(IDC_ONEAXIS, OnOneaxis)
	ON_BN_CLICKED(IDC_CHECKSELECTOTHERS, OnCheckselectothers)
	ON_BN_CLICKED(IDC_CHECK_NULLDRILLHOLES, OnCheckNulldrillholes)
	ON_COMMAND(ID_MENUONLYANOREVERSE, OnMenuonlyanoreverse)
	ON_UPDATE_COMMAND_UI(ID_MENUONLYANOREVERSE, OnUpdateMenuonlyanoreverse)
	ON_COMMAND(ID_MENUONLYAREVERSE, OnMenuonlyareverse)
	ON_UPDATE_COMMAND_UI(ID_MENUONLYAREVERSE, OnUpdateMenuonlyareverse)
	ON_COMMAND(ID_MENUAANDBDOUBLE, OnMenuaandbdouble)
	ON_UPDATE_COMMAND_UI(ID_MENUAANDBDOUBLE, OnUpdateMenuaandbdouble)
	ON_COMMAND(ID_MENUONLYB, OnMenuonlyb)
	ON_UPDATE_COMMAND_UI(ID_MENUONLYB, OnUpdateMenuonlyb)
	ON_COMMAND(ID_MENUDOUBLEAXIS, OnMenudoubleaxis)
	ON_UPDATE_COMMAND_UI(ID_MENUDOUBLEAXIS, OnUpdateMenudoubleaxis)
	ON_COMMAND(ID_MENUONLYLEFT, OnMenuonlyleft)
	ON_UPDATE_COMMAND_UI(ID_MENUONLYLEFT, OnUpdateMenuonlyleft)
	ON_COMMAND(ID_MENUONLYRIGHT, OnMenuonlyright)
	ON_UPDATE_COMMAND_UI(ID_MENUONLYRIGHT, OnUpdateMenuonlyright)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_RAD_MANUPROC, OnRadAutoproc)
	ON_BN_CLICKED(IDC_RAD_SELECT, OnRadAutoproc)
	ON_BN_CLICKED(IDC_BUTTON1, OnRecognizeTest)
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_DISPLAY,OnDisplayImage)
	ON_MESSAGE(WM_UNDISPLAY,OnUnDisplayImage)
	ON_MESSAGE(WM_DISPDRILLINFO,OnDisplayDrillInfo)
//	ON_MESSAGE(WM_DISPPROCINFO,OnDisplayProcInfo)
	ON_MESSAGE(WM_DISPMATCHINFO,OnDisplayMatchInfo)   //ly add 20130724
	ON_MESSAGE(WM_USERUPDATEFILANAME,OnUpdateFileName)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainRunView diagnostics

#ifdef _DEBUG
void CMainRunView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMainRunView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainRunView message handlers

int CMainRunView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	pCMainRunView=this;

	// TODO: Add your specialized creation code here
	m_hLedOFF = AfxGetApp()->LoadIcon(IDI_LEDGREEN);	//ly add 20130724
	m_hLedON =  AfxGetApp()->LoadIcon(IDI_LEDON);//ly add 20130724
//	m_sMatch.SetIcon(m_hLedON);

//	m_btnTopoint.SubclassDlgItem(IDC_BT_TOPOINT,this);
	m_btnTopoint.SetIcon(IDI_FILEPOINT,IDI_FILEPOINT);
	m_btnTopoint.SetAlign(AL_TOP);
	m_btnTopoint.SetIconYPos(10);

	/*m_btnPass.SubclassDlgItem(IDC_BT_PITCHPOINT,this);
	m_btnPass.SetIcon(IDI_PASS,IDI_PASS);
	m_btnPass.SetAlign(AL_LEFT);
	m_btnPass.SetIconYPos(10);

	m_btnPitch.SubclassDlgItem(IDC_BT_PITCHPOINT,this);
	m_btnPitch.SetIcon(IDI_ADD,IDI_ADD);
	m_btnPitch.SetAlign(AL_LEFT);
	m_btnPitch.SetIconYPos(10);*///ly delete 20121127

	m_btnClean.SubclassDlgItem(IDC_BT_CLEAR,this);
	m_btnClean.SetIcon(IDI_CLEAN,IDI_CLEAN);
	m_btnClean.SetAlign(AL_LEFT);
	m_btnClean.SetIconYPos(10);
	
	m_btnRunStart.SubclassDlgItem(IDC_BT_RUN_START,this);
	m_btnRunStart.SetIcon(IDI_START,IDI_START);
	m_btnRunStart.SetAlign(AL_TOP);
	m_btnRunStart.SetIconYPos(10);

	m_btnRunPause.SubclassDlgItem(IDC_BT_RUN_PAUSE,this);
	m_btnRunPause.SetIcon(IDI_PAUSE,IDI_PAUSE);
	m_btnRunPause.SetAlign(AL_TOP);
	m_btnRunPause.SetIconYPos(10);

	m_btnExit.SubclassDlgItem(IDC_BT_EXIT,this);
	m_btnExit.SetIcon(IDI_EXIT,IDI_EXIT);
	m_btnExit.SetAlign(AL_TOP);
	m_btnExit.SetIconYPos(10);
	
	m_btnHomeAll.SubclassDlgItem(IDC_BT_HOMEALL,this);
	m_btnHomeAll.SetIcon(IDI_HOME,IDI_HOME);
	m_btnHomeAll.SetAlign(AL_TOP);
	m_btnHomeAll.SetIconYPos(10);

	m_btnSetParameter.SubclassDlgItem(IDC_BT_SETPARAMETER,this);
	m_btnSetParameter.SetIcon(IDI_PARAMETER,IDI_PARAMETER);
	m_btnSetParameter.SetAlign(AL_TOP);
	m_btnSetParameter.SetIconYPos(10);

	m_btnScanAdjust.SubclassDlgItem(IDC_BT_SCANADJUST,this);
	m_btnScanAdjust.SetIcon(IDI_ADJUST,IDI_ADJUST);
	m_btnScanAdjust.SetAlign(AL_TOP);
	m_btnScanAdjust.SetIconYPos(10);

	m_btnRunEnd.SubclassDlgItem(IDC_BT_RUN_END,this);
	m_btnRunEnd.SetIcon(IDI_END,IDI_END);
	m_btnRunEnd.SetAlign(AL_TOP);
	m_btnRunEnd.SetIconYPos(10);

	m_btnLaserWarmup.SubclassDlgItem(IDC_BT_LASERWARMUP,this);
	m_btnLaserWarmup.SetIcon(IDI_LASERPOWERON,IDI_LASERPOWERON);
	m_btnLaserWarmup.SetAlign(AL_TOP);
	m_btnLaserWarmup.SetIconYPos(10);
	
//	m_btnShowFileInfo.SubclassDlgItem(IDC_BT_SHOWFILEINFO,this);
//	m_btnShowFileInfo.SetIcon(IDI_SHOWPART,IDI_SHOWWHOLE);
//	m_stFileName.SubclassDlgItem(IDC_FILENAME,this);					//20191223
//	m_FileName.SubclassDlgItem(IDC_STATIC1,this);

	m_stProcedNum.SubclassDlgItem(IDC_ST_PROCEDNUM,this);
	m_stPCBDrilledHolecount.SubclassDlgItem(IDC_ST_DRILLEDHOLES,this);
	m_stCurArea.SubclassDlgItem(IDC_ST_CURAREA,this);

	m_stProcInfo.SubclassDlgItem(IDC_ST_PROCINFO,this);
	m_ProcInfo.SubclassDlgItem(IDC_STATIC3,this);
	m_ProcedNum.SubclassDlgItem(IDC_STATIC2,this);
    m_stPCBHoleCount.SubclassDlgItem(IDC_ST_PCBHOLE,this);

	// 手动/自动
//	m_bAutoProc = GetDoc().GetProcessState();
	if(!GetDoc().GetLAndULSystem())										//20200422
	{
		m_bAutoProc=0;
		GetDoc().SetProcessState(m_bAutoProc);
	}
	else
		m_bAutoProc=GetDoc().GetProcessState();

	time_t Dotime;
	time(&Dotime);
	GetDoc().SetLaserTestCurTime(Dotime);
	GetDoc().SetAdjustTime(Dotime);

	if(GetDoc().GetShenLan3Fid()!=0)									//20170518
	{
		m_bAutoAdjust=true;
		m_bAutoPower=true;		

		GetDoc().SetEnAutoAdjust(true);
		GetDoc().SetEnAutoPower(true);
	}
	else
	{
		m_bAutoAdjust=GetDoc().GetEnAutoAdjust();
		m_bAutoPower=GetDoc().GetEnAutoPower();
	}

//	m_bAutoAdjust=GetDoc().GetEnAutoAdjust();
//	m_bAutoPower=GetDoc().GetEnAutoPower();
	m_bFidRetry = GetDoc().GetEnFidRetry();

	char buf[64];
	sprintf(buf,"%d",GetDoc().GetNGSum());//"szRead( NG数: %d )\n"
	m_strNGSum = buf;//ly add 20121127
	sprintf(buf,"%.4f",GetDoc().GetHolesSum());
	m_strHoleSum = buf;//ly add 20121127

	return 0;
}

void CMainRunView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	char buf[64];
	char szRead[30]={""};

	if(bActivate)
	{
		sprintf(buf,"%d",GetDoc().GetCurPCBHoleCount());
		m_strPCBHoleCount = buf;

		strncpy(szRead,GetLang().GetWarningText(10091),64);
		sprintf(buf,szRead,GetDoc().GetProcedPCBNum());
		m_strProcedNum = buf;

		sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());
		m_DrilledHoleCount = buf;

		sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());
		m_CurArea = buf;

		if(GetDoc().GetSysInfoDBMode()==2)								//20181212
			m_strProcInfo = GetDoc().GetSysProcLOTID();
/*
		if(GetDoc().GetUse9112()==0)//ly add 20140108
			GetDlgItem(IDC_ONEAXIS)->ShowWindow(SW_SHOW);	
		else
			GetDlgItem(IDC_ONEAXIS)->ShowWindow(SW_HIDE);
*/	
		if(GetControl().GetRunState()!=CControl::END)
		{
			GetDlgItem(IDC_BT_RUN_START)->EnableWindow(FALSE);
//			GetDlgItem(IDC_BT_SCANADJUST)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_LASERWARMUP)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_HOMEALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_EXIT)->EnableWindow(FALSE);

			GetDlgItem(IDC_RADAUTO)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_MANUFID)->EnableWindow(FALSE);
//			GetDlgItem(IDC_RAD_MANUPROC)->EnableWindow(FALSE);				//20181106
//			GetDlgItem(IDC_RAD_AUTOPROC)->EnableWindow(FALSE);
			GetDlgItem(IDC_RAD_SELECT)->EnableWindow(FALSE);

			GetDlgItem(IDC_BT_SCANADJUST)->EnableWindow(FALSE);				//20191015
			GetDlgItem(IDC_BT_SETPARAMETER)->EnableWindow(FALSE);
		}
		else
		{
			int nLevel = GetDoc().GetCurUserLevel();

			GetDlgItem(IDC_BT_RUN_START)->EnableWindow(TRUE);
//			if(nLevel==SystemDoc::PRIMARY)//初级				
//				GetDlgItem(IDC_BT_SCANADJUST)->EnableWindow(FALSE);
//			else
//				GetDlgItem(IDC_BT_SCANADJUST)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_LASERWARMUP)->EnableWindow(TRUE);				
			GetDlgItem(IDC_BT_HOMEALL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_EXIT)->EnableWindow(TRUE);

			GetDlgItem(IDC_RADAUTO)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_MANUFID)->EnableWindow(TRUE);
//			GetDlgItem(IDC_RAD_MANUPROC)->EnableWindow(TRUE);				//20181106
//			GetDlgItem(IDC_RAD_AUTOPROC)->EnableWindow(TRUE);
			GetDlgItem(IDC_RAD_SELECT)->EnableWindow(TRUE);

			GetDlgItem(IDC_BT_SCANADJUST)->EnableWindow(TRUE);				//20191015
			GetDlgItem(IDC_BT_SETPARAMETER)->EnableWindow(TRUE);

			if(GetDoc().GetShenLan3Fid()!=0)								//20170518
			{
				if(nLevel==SystemDoc::ADMIN)//系统
				{
					GetDlgItem(IDC_CHK_ENABLEAUTOADJUST)->EnableWindow(TRUE);
					GetDlgItem(IDC_STATIC4)->EnableWindow(TRUE);
					GetDlgItem(IDC_CHK_ENABLEAUTOPOWER)->EnableWindow(TRUE);
					GetDlgItem(IDC_STATIC5)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_CHK_ENABLEAUTOADJUST)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC4)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHK_ENABLEAUTOPOWER)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC5)->EnableWindow(FALSE);			
				}
			}
		}
		
		if (m_bAutoProc==CControl::SELEPROC)
		{
			if(1==GetDoc().GetFZInnerMark())							//20160330 为满足方正屏蔽反选功能
				GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(FALSE);
			else
				GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(TRUE);
			
			GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(FALSE);		
		}
		else
		{
			GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(FALSE);
			
			if(1==GetDoc().GetFZInnerMark())							//20160321 为满足方正屏蔽空跑功能
				GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(FALSE);
			else
				GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(TRUE);

			if(GetControl().GetRunState()!=CControl::END)				//20190531
				GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->EnableWindow(FALSE);
			else
				GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->EnableWindow(true);
		}

		m_btnRunPause.EnableWindow(FALSE);
//		m_btnSetParameter.EnableWindow(FALSE);							//20191015
//		m_btnScanAdjust.EnableWindow(FALSE);

//#ifdef NOLANDULSYSTEM
	if(!GetDoc().GetLAndULSystem())
		GetDlgItem(IDC_RAD_MANUPROC)->EnableWindow(false);
//#endif
	}

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CMainRunView::OnRunCont() 
{

}

void CMainRunView::OnRunPause() 
{

}

LONG CMainRunView::OnDisplayImage(UINT wParam, LONG lParam)
{
#ifdef USEIMAGE
#ifdef AVT														//20170531
	CRect rect;	
	CSize size;
	GetDlgItem(IDC_DISPLAY)->GetClientRect(rect);
	size.cx=rect.Width();
	size.cy=rect.Height();	

	GetImageCaptor().Display(::GetDlgItem(m_hWnd,IDC_DISPLAY),size);
#endif
	
#ifdef PICOLO
	GetImageCaptor().SelectChannel(GetImageCaptor().GetCurrentChannel());	//与AVT相比多此操作

	CRect rect;	
	CSize size;
	GetDlgItem(IDC_DISPLAY)->GetClientRect(rect);
	size.cx=rect.Width();
	size.cy=rect.Height();	

	GetImageCaptor().Display(::GetDlgItem(m_hWnd,IDC_DISPLAY),size);
#endif
#endif
	
//	m_strFileName = GetDoc().GetFileName();
	m_strFileNameNew = GetDoc().GetFileName();					//20191223

	OnDisplayFileInfo();	
	
	char szRead[20] = {""};
	if(GetDoc().GetLaserPowerState())
	{
		strncpy(szRead ,GetLang().GetWarningText(10015),20);
		m_btnLaserWarmup.SetWindowText(szRead);//"激光掉电"
		m_btnLaserWarmup.SetIcon(IDI_LASERPOWEROFF,IDI_LASERPOWEROFF);
	}
	else
	{
		strncpy(szRead ,GetLang().GetWarningText(10016),20);
		m_btnLaserWarmup.SetWindowText(szRead);//"激光上电"
		m_btnLaserWarmup.SetIcon(IDI_LASERPOWERON,IDI_LASERPOWERON);
	}
	
	UpdateData(FALSE);
	
	return 0;
}

LONG CMainRunView::OnUnDisplayImage(UINT wParam, LONG lParam)
{
#ifdef USEIMAGE
	GetImageCaptor().UnDisplay();
#endif	
	return 0;
}

LONG CMainRunView::OnDisplayDrillInfo(UINT wParam, LONG lParam)
{
//	m_lDrillingSubareaNo = wParam;
	char buf[64];

	char szRead[64]={""};
	strncpy(szRead,GetLang().GetWarningText(10091),64);
	sprintf(buf,szRead,GetDoc().GetProcedPCBNum());//"%-4d 片 \n"
	m_strProcedNum = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());//ly add 20110903 界面增加已加工孔数显示。
	m_DrilledHoleCount = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());//ly add 20111008 界面增加当前加工区域显示。
	m_CurArea = buf;
	sprintf(buf,"%d",GetDoc().GetNGSum());//"szRead( NG数: %d )\n"
	m_strNGSum = buf;//ly add 20121127
	sprintf(buf,"%.4f",GetDoc().GetHolesSum());
	m_strHoleSum = buf;//ly add 20121127
/*
    BOOL bPcb1 = GetControl().GetFiducialMatchStatus(HeadLeft);
	BOOL bPcb2 = GetControl().GetFiducialMatchStatus(HeadRight);
	
	if(bPcb1&&bPcb2)
	{
		strncpy(szRead,GetLang().GetWarningText(10092),64);
		sprintf(buf,szRead);//"靶标匹配完成"
	}
	else if(!bPcb1&&bPcb2)
	{
		strncpy(szRead,GetLang().GetWarningText(10093),64);
		sprintf(buf,szRead);//"左侧靶标寻找失败"
	      
	}
	else if(!bPcb2&&bPcb1)
	{
		strncpy(szRead,GetLang().GetWarningText(10094),64);
	    sprintf(buf,szRead);//"右侧靶标寻找失败"
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(10095),64);
	    sprintf(buf,szRead);//"两侧靶标寻找失败"
	}

	m_strProcInfo = buf;
*/
	sprintf(buf,"LX:%.6f  LY:%.6f  RX:%.6f  RY:%.6f",GetDoc().GetLAvgScaleX(),GetDoc().GetLAvgScaleY(),GetDoc().GetRAvgScaleX(),GetDoc().GetRAvgScaleY());//ly add 20131021
	m_strLRScale = buf;//ly add 20121127
	
	UpdateData(FALSE);	
	OnPaint();	
	return 0;
}

LONG CMainRunView::OnDisplayMatchInfo(UINT wParam, LONG lParam)//ly add 20130724
{
	char buf[64];

	m_sMatch.SetIcon(GetDoc().GetMatch()?m_hLedOFF:m_hLedON);

	double a  = GetDoc().GetMatchScore();
	sprintf(buf,"%.4f",GetDoc().GetMatchScore());
	m_strMatchScore = buf;//ly add 20121127

	UpdateData(FALSE);	
	OnPaint();	
	return 0;
}

void CMainRunView::OnUpdateFileName(WPARAM wParam, LPARAM lParam)
{
	char buf[64];
	sprintf(buf,"%d",GetDoc().GetCurPCBHoleCount());
	m_strPCBHoleCount = buf;
	m_strFileNameNew = GetDoc().GetFileName();
	UpdateData(FALSE);
}

void CMainRunView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("MainRun","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC7",szRead,40);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("MainRun","IDC_PCBHOLENUM",szRead,40);
	SetDlgItemText(IDC_PCBHOLENUM,szRead);
	GetLang().GetUIText("MainRun","IDC_PCBDRILLEDHOLENUM",szRead,40);//ly add 20110903
	SetDlgItemText(IDC_PCBDRILLEDHOLENUM,szRead);
	GetLang().GetUIText("MainRun","IDC_CURAREA",szRead,40);//ly add 20110903
	SetDlgItemText(IDC_CURAREA,szRead);
	GetLang().GetUIText("MainRun","IDC_ADJUSTWAR",szRead,40);
	SetDlgItemText(IDC_ADJUSTWAR,szRead);
	GetLang().GetUIText("MainRun","IDC_LASERPOWERWAR",szRead,40);
	SetDlgItemText(IDC_LASERPOWERWAR,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_CLEAR",szRead,40);
	SetDlgItemText(IDC_BT_CLEAR,szRead);
//	GetLang().GetUIText("MainRun","IDC_BT_PITCHPOINT",szRead,40);
//	SetDlgItemText(IDC_BT_PITCHPOINT,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_PASS",szRead,40);
	SetDlgItemText(IDC_BT_PASS,szRead);
	GetLang().GetUIText("MainRun","IDC_RADAUTO",szRead,40);
	SetDlgItemText(IDC_RADAUTO,szRead);
	GetLang().GetUIText("MainRun","IDC_RADMANU",szRead,40);
	SetDlgItemText(IDC_RADMANU,szRead);
	GetLang().GetUIText("MainRun","IDC_RAD_MANUPROC",szRead,40);
	SetDlgItemText(IDC_RAD_MANUPROC,szRead);
	GetLang().GetUIText("MainRun","IDC_RAD_AUTOPROC",szRead,40);
	SetDlgItemText(IDC_RAD_AUTOPROC,szRead);
	GetLang().GetUIText("MainRun","IDC_RAD_SELECT",szRead,40);
	SetDlgItemText(IDC_RAD_SELECT,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_RUN_START",szRead,40);
	SetDlgItemText(IDC_BT_RUN_START,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_RUN_PAUSE",szRead,40);
	SetDlgItemText(IDC_BT_RUN_PAUSE,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_RUN_END",szRead,40);
	SetDlgItemText(IDC_BT_RUN_END,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_HOMEALL",szRead,40);
	SetDlgItemText(IDC_BT_HOMEALL,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_SCANADJUST",szRead,40);
	SetDlgItemText(IDC_BT_SCANADJUST,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_SETPARAMETER",szRead,40);
	SetDlgItemText(IDC_BT_SETPARAMETER,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_LASERWARMUP",szRead,40);
	SetDlgItemText(IDC_BT_LASERWARMUP,szRead);
	GetLang().GetUIText("MainRun","IDC_BT_EXIT",szRead,40);
	SetDlgItemText(IDC_BT_EXIT,szRead);
	GetLang().GetUIText("MainRun","IDC_FIDRETRY",szRead,40);//ly add 20120210
	SetDlgItemText(IDC_FIDRETRY,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("MainRun","IDC_STATIC9",szRead,40);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("MainRun","IDC_CLR_HOLES",szRead,40);
	SetDlgItemText(IDC_CLR_HOLES,szRead);
	GetLang().GetUIText("MainRun","IDC_CLEAR_NG",szRead,40);
	SetDlgItemText(IDC_CLEAR_NG,szRead);
	GetLang().GetUIText("MainRun","IDC_CHK_MANUFID",szRead,40);
	SetDlgItemText(IDC_CHK_MANUFID,szRead);
}


UINT ThreadProcWipTackReport(LPVOID pParam);
UINT MViewThreadProcStatusReport(LPVOID pParam);
void CMainRunView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	m_bManuFid=GetDoc().GetEnManuFid();//ly add 20131226

//	m_stFileName.SetTextColor(TEXT_COLOR);										//20191223
//	m_FileName.SetTextColor(TEXT_COLOR);

	m_ProcedNum.SetTextColor(TEXT_COLOR);
	m_stProcedNum.SetTextColor(TEXT_COLOR);
	m_stPCBDrilledHolecount.SetTextColor(TEXT_COLOR);
	m_stCurArea.SetTextColor(TEXT_COLOR);
    m_stPCBHoleCount.SetTextColor(TEXT_COLOR);
	m_cLaserpowerWar.SetTextColor(TEXT_COLOR);
	m_cAdjustWar.SetTextColor(TEXT_COLOR);
	m_stProcInfo.SetTextColor(TEXT_COLOR);
	m_ProcInfo.SetTextColor(TEXT_COLOR);
	
	m_pcbholenum.SetTextColor(TEXT_COLOR);
	m_pcbdrilledholenum.SetTextColor(TEXT_COLOR);//ly add 20110903
	m_stCurarea.SetTextColor(TEXT_COLOR);//ly add 20111008
	
	char buf[16];
	char szRead[16]={""};
	strncpy(szRead,GetLang().GetWarningText(10091),16);
	sprintf(buf,szRead,GetDoc().GetProcedPCBNum());//"%-4d 片"
	m_strProcedNum = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());//ly add 20110903 界面增加已加工孔数显示。
	m_DrilledHoleCount = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());//ly add 20111008 界面增加当前加工区域显示。
	m_CurArea = buf;
	sprintf(buf,"%d",GetDoc().GetNGSum());//"szRead( NG数: %d )\n"
	m_strNGSum = buf;//ly add 20121127
	sprintf(buf,"%.4f",GetDoc().GetHolesSum());
	m_strHoleSum = buf;//ly add 20121127
	
	CRect rect;
	GetDlgItem(IDC_STATIC_DISPLAYBLOCK)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_ctrlChecker.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP, rect, this, IDC_STATIC_DISPLAYBLOCK);
   	SetCheckerBlockParam();
/*
	if(GetDoc().GetUse9112()==0)
		GetDlgItem(IDC_ONEAXIS)->ShowWindow(SW_SHOW);	
	else
		GetDlgItem(IDC_ONEAXIS)->ShowWindow(SW_HIDE);
*/
	GetControl().SetRunState(CControl::END);

	SetTimer(20,10000,NULL);
}

UINT ThreadProcWipTackReport(LPVOID pParam)
{
	CMainRunView *mainRunView = (CMainRunView *)pParam;
	mainRunView->WIPTrackingReport();
	return 0;
}

UINT MViewThreadProcStatusReport(LPVOID pParam)
{
	CMainFrame *mainFrame = (CMainFrame *)pParam;
	mainFrame->StatusReport();
	return 0;
}

void CMainRunView::SetScanSize(UINT ulSize)
{
	m_ulLastBlockSize = ulSize;
}

void CMainRunView::SetCheckerBlockParam(UINT ulRow, UINT ulCol)
{	
	m_ctrlChecker.SetBlockWidth(GetDoc().GetScanSize(),ulCol,ulRow);
}

void CMainRunView::SetCheckerBlockParam()
{
	int l=(int)(GetDoc().GetTableHeight()/GetDoc().GetScanSize()  + (GetDoc().GetTableHeight()%GetDoc().GetScanSize()==0?0:1));
    int w=(int)(GetDoc().GetTableWidth()/GetDoc().GetScanSize() + (GetDoc().GetTableWidth()%GetDoc().GetScanSize()==0?0:1));
	
	int nNum = l*w;

	m_ctrlChecker.SetBlockWidth(GetDoc().GetScanSize(),l,w);

	m_ctrlChecker.SetTotalBlocks(nNum,0); 
 
 	for( int i = 0; i < nNum; i++)
 		m_ctrlChecker.SetBlock(i,BLANKED_BLOCKS_COLOR );	
}

void CMainRunView::OnDestroy() 
{
	TVisualFormView::OnDestroy();
	UpdateData(TRUE);
	GetDoc().SetProcessState(m_bAutoProc);

	KillTimer(20);	
}

void CMainRunView::OnDisplayFileInfo()
{
	if(!GetDoc().GetIsDoubleFileData())
	{
		if(GetExcellonData().GetSubAreaRow()==0&&GetExcellonData().GetSubAreaCol()==0)
		{
			SetCheckerBlockParam();
			return ;
		}
		
		int l=GetDoc().GetTableHeight()/GetDoc().GetScanSize()  + (GetDoc().GetTableHeight()%GetDoc().GetScanSize()==0?0:1);
		int w=GetDoc().GetTableWidth()/GetDoc().GetScanSize() + (GetDoc().GetTableWidth()%GetDoc().GetScanSize()==0?0:1);
		
		if(GetExcellonData().GetSubAreaRow()>w||GetExcellonData().GetSubAreaCol()>l)
		{
			SetCheckerBlockParam();
			return ;
		}
		
		SetCheckerBlockParam(GetExcellonData().GetSubAreaRow(),GetExcellonData().GetSubAreaCol());
		m_ctrlChecker.SetTotalBlocks(GetExcellonData().GetSubAreaRow(),GetExcellonData().GetSubAreaCol(),0); 
		
		for( int i=0; i<GetExcellonData().GetSubAreaCol(); i++)
			for(int j=0; j<GetExcellonData().GetSubAreaRow(); j++)
			{
				if((i*GetExcellonData().GetSubAreaRow()+j)>=GetExcellonData().GetSubAreaCnt())
				{
					m_ctrlChecker.SetBlock(i*GetExcellonData().GetSubAreaRow()+(i%2==0?j:GetExcellonData().GetSubAreaRow()-j-1),
						BLANKED_BLOCKS_COLOR);				
					continue;
				}
				
				if(GetExcellonData().GetSubAreaHoleCount(i*GetExcellonData().GetSubAreaRow()+j))
				{
					m_ctrlChecker.SetBlock(i*GetExcellonData().GetSubAreaRow()+(i%2==0?j:GetExcellonData().GetSubAreaRow()-j-1),
						BLANKED_BLOCKS_UNSELCOLOR );
				}
			}
			
		if(GetDoc().GetProcessState()==SystemDoc::SELEPROC&&m_ctrlChecker.GetSelectBlockNum()>0)
		{
			for(int n=0; n<m_ctrlChecker.GetSelectBlockNum();++n)
			{
				CCheckerCtrl::BlockPos blkpos = m_ctrlChecker.GetSelectBlockPos(n);
				m_ctrlChecker.SetBlock(blkpos.nRow*GetExcellonData().GetSubAreaRow()+blkpos.nCol,
					BLANKED_BLOCKS_SELCOLOR);//BLANKED_BLOCKS_COLOR 
			}
		}
	}
	else//----------------------------------------------------------------20161109
	{
		int rowCount=GetDoc().GetDisplayRowCount();
		int colCount=GetDoc().GetDisplayColCount();
		SetCheckerBlockParam(colCount,rowCount);
		m_ctrlChecker.SetTotalBlocks(colCount,rowCount,0); 

		int oldGlobalExcellonIndex=GetGlobalExcellonIndex();
		
		if(GetDoc().GetExcellonData0IsUp())
			SetGlobalExcellonIndex(1);
		else
			SetGlobalExcellonIndex(0);

		int iStart=0;
		int iEnd=0;
		int offset=0;
		int rowCount0=GetExcellonData().GetSubAreaCol();

		for(int times=0;times<2;times++)
		{
			if(times==0)
			{
				iStart=0;
				iEnd=rowCount0;
				offset=0;
			}
			else
			{
				iStart=rowCount0;
				iEnd=rowCount;
				offset=colCount*rowCount0;
				
				if(GetDoc().GetExcellonData0IsUp())
					SetGlobalExcellonIndex(0);
				else
					SetGlobalExcellonIndex(1);
			}

			for( int i=iStart; i<iEnd; i++)
				for(int j=0; j<colCount; j++)
				{
					if(((i*colCount+j-offset)>=GetExcellonData().GetSubAreaCnt())&&((i*colCount+j)<iEnd*colCount))
					{
						m_ctrlChecker.SetBlock(i*colCount+(i%2==0?j:colCount-j-1),BLANKED_BLOCKS_COLOR);				
						continue;
					}
					
					if(GetExcellonData().GetSubAreaHoleCount(i*colCount+j-offset))
					{
						m_ctrlChecker.SetBlock(i*colCount+(i%2==0?j:colCount-j-1),BLANKED_BLOCKS_UNSELCOLOR );
					}
				}
		}
		
		if(GetDoc().GetProcessState()==SystemDoc::SELEPROC&&m_ctrlChecker.GetSelectBlockNum()>0)
		{
			for(int n=0; n<m_ctrlChecker.GetSelectBlockNum();++n)
			{
				CCheckerCtrl::BlockPos blkpos = m_ctrlChecker.GetSelectBlockPos(n);
				m_ctrlChecker.SetBlock(blkpos.nRow*colCount+blkpos.nCol,BLANKED_BLOCKS_SELCOLOR);	 
			}
		}

		SetGlobalExcellonIndex(oldGlobalExcellonIndex);
	}
//---------------------------------------------------------------------------------
	m_ctrlChecker.Refresh();
}

void CMainRunView::ResetBlankColor()
{
	OnDisplayFileInfo();
}

void CMainRunView::ResetSelectBlankColor()
{
	//	OnDisplayFileInfo();
    for(int n=0; n<m_ctrlChecker.GetSelectBlockNum();++n)
	{
		CCheckerCtrl::BlockPos blkpos = m_ctrlChecker.GetSelectBlockPos(n);
		m_ctrlChecker.SetBlock(blkpos.nRow*GetExcellonData().GetSubAreaRow()+blkpos.nCol,
			BLANKED_BLOCKS_SELCOLOR );//BLANKED_BLOCKS_COLOR
		
	}
	m_ctrlChecker.Refresh();

}

//建立加工线程 20190125
//重构加工流程：20161123
void CMainRunView::OnRunStart()
{
	if(bRunning)													//20190401
		return;

	GetDoc().SaveProcessParam();									//20200715 由退出程序处移至此处

	bRunning=true;
	//Process();
	//bRunning=false;


//	UpdateData(true);
	
	DWORD dwThreadId;
	CloseHandle(CreateThread(NULL,0,RunStart,(LPVOID)this,0,&dwThreadId));
}

DWORD WINAPI RunStart(LPVOID pM)
{
//	return ((CMainRunView*)pM)->Process();

	((CMainRunView*)pM)->Process();									//20190401
	bRunning=false;

	return 0;
}

DWORD CMainRunView::Process()
{
	GetControl().SetRunState(CControl::RUN);						//20190329
	OnActivateView(true,this,this);

//	UpdateData(true);

	char ez[256]={""};
	//int nHead=HeadBoth;	
	//goto Label;
	

#ifdef SENTINAL
#ifdef DOUBLEPROTECT
	hasp_time_t timeForUse=0;
	if(!GetDoc().TimeController(timeForUse))
	{
		int nSel = AfxMessageBox("请确定是否要重新初始化时间控制加密狗? ",MB_YESNO);		
		if(nSel == IDYES )
		{
			if(!GetDoc().InitSentinal())
			{
				AfxMessageBox("请确认时间控制加密狗是否正确插入或者加密时间是否到期！");

				GetControl().SetRunState(CControl::END);
				OnActivateView(true,this,this);
				return 0;
			}
		}
		else
		{
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}
#endif
#endif

	if(!GetDoc().GetFileIsOptimized())									//20180116
	{
		AfxMessageBox("加工文件未做优化处理，无法加工，请确认！");

		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return 0;
	}

//	UpdateData();

//判断机器回零状态
	if(!GetDoc().GetMotorState())										
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);	//"机器未整体回零，不允许相关操作!"

		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return 0;
	}

//判断激光器上电状态
	if(!GetDoc().GetLaserPowerState())												//20181225
	{
		int nsel = AfxMessageBox("激光器未上电，继续请选“是”，取消请选“否”!",MB_YESNO);
		if(nsel == IDNO)
		{
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//加工工艺方式判断
	if(m_bAutoProc==CControl::SELEPROC)									
	{
		if(GetDoc().GetFileMode()!=SystemDoc::NORMALPROC)							//20160819
		{
			AfxMessageBox("指定加工只能在正常加工方式下使用!");

			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//数据文件是否正常打开
	if(!GetDoc().GetFileOpenState())									
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
		AfxMessageBox(ez);	//"请先打开要加工的数据文件!"
#ifdef USELOG
		GetLog().Append_pro(10057,20025);	//"请先打开要加工文件!"
#endif
		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return 0;
	}

//是否做过标靶定位
	if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)
	{
		if((!GetDoc().GetIsFiducialDo2(0))||(!GetDoc().GetIsFiducialDo2(1)))
		{
			strncpy(ez,GetLang().GetWarningText(21038),256);
			AfxMessageBox(ez);	//"请先对PCB板进行标靶定位!"
#ifdef USELOG
			GetLog().Append_pro(10058,20025);	//"没有做过标靶定位而试图加工!"
#endif
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0; 
		}
	}
	else
	{
		if(!GetDoc().GetIsFiducialDo())										
		{
			strncpy(ez,GetLang().GetWarningText(21038),256);
			AfxMessageBox(ez);	//"请先对PCB板进行标靶定位!"
#ifdef USELOG
			GetLog().Append_pro(10058,20025);	//"没有做过标靶定位而试图加工!"
#endif
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//储存能量参数信息和LOTID信息，从打开文件开始只记录一次
	if(GetDoc().GetIsRecordPowerPara())									
	{
		CString szLotid;
		GetDoc().SetIsRecordPowerPara(FALSE);
#ifdef USELOG
		szLotid= GetDoc().GetLOTIDFix();
		if (GetDoc().GetDrillInc())										//富士康增加的LotID定义方式
			szLotid= GetDoc().GetLOTIDFix()+ GetDoc().GetNoProcessID();

		GetLog().Append_PowerPara(GetDoc().GetFileName(),GetControl().ReadPowerPara((LPCTSTR)GetDoc().GetToolFileName()),szLotid);
#endif
	}

//运行激光器状态监控程序
#ifdef LASERMONITOR
	CString	laserLinkPath = GetDoc().GetAppPath()+"E400IXSocetLink";		
    ShellExecute(NULL, "open", laserLinkPath, "", NULL, SW_SHOWMINIMIZED);
#endif

//加工用能量参数确认：切换至能量设定界面进行确认
	if(GetDoc().GetShowTool()==1)						
	{
		GetMainFrame().m_Framework.Get(15)->SetActivePane();

		int nsel = AfxMessageBox("请确认加工参数！点击'是'开始加工  点击‘否’停止加工",MB_YESNO);

		GetMainFrame().m_Framework.Get(37)->SetActivePane();
		
		if(nsel == IDNO)
		{
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//自动上下料开始运行前，对上下料的状态进行一次轮询 28：机械手错误报警
	if(!GetDoc().GetUse9112())
	{
		if(GetDoc().GetProcessState()==CControl::AUTOPROC)
			GetControl().QueryCOMInput(28);					
	}

//	GetControl().SetRunState(CControl::RUN);
//关闭有效吸附轴
	GetDoc().SetAxisIsRun(0,false);							//20180821
	GetDoc().SetAxisIsRun(1,false);

//	OnActivateView(true,this,this);
/*																//20200601 取消
#ifndef PRELOADTEST
//针对SMC，可进行加工数据预加载工作
#ifdef SMCPreLoad
//	if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//预加载功能不支持大孔绕烧和双区域6/8内层主标靶方式
	if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData())&&(!(GetDoc().GetFlowPathMode()==AANDBDOUBLE)))	//20200107 双面加工时此处不进行分区数据预加载
	{
		if(!GetControl().PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
		{		
			AfxMessageBox("加工数据预加载过程出现错误，请确认！");
			
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}
	else														//20191015
	{
		if(!GetControl().PreLoadCreate(false,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))
		{		
			AfxMessageBox("加工数据预加载过程出现错误，请确认！");
			
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}
#endif
#endif
*/
	UpdateData();

	GetLog().Append_pro("开始加工","流程控制");				//20200720 增加

//初始化界面和运行状态
	m_DrilledHoleCount = "0";
	m_CurArea = "0";
	GetControl().SetLampStatus(CControl::ORDER);
	GetDoc().SetFault(false);							//机器的错误状态：有或者无
	GetDoc().SetFaultRun(false);						//机器带错误运行状态：是或者否
//	GetDoc().SetWarner(false);							//机器的警告状态：有或者无
	GetDoc().SetErrorPCB(0);							//记录自动上下料加工中由于涨缩原因出现的异常板数量，大于等于6张后报警，否则不报警

//初始化加工中用到的其他数据
//	GetControl().Calc75umControl();						//富士康75un判断计算		//20180829
#ifdef LASERMONITOR
	GetDoc().ReadLaserConfig();							//查询激光器监控状态
#endif

//时间分析
	GetDoc().SetTimeAnalyse(TRUE);
	GetDoc().SetBeginTimeAnalyse(COleDateTime::GetCurrentTime());
	GetDoc().SetCalculateBeginTime(GetTickCount());
	GetLog().AppendSNOtherStatusTable("生产状态",COleDateTime::GetCurrentTime());

#ifndef MACHINEHOTTEST
//打开风机
	GetControl().ChannelOutput(OFANPOWERON,IO_ON);
#endif

//开始进行PCB板加工
/*
	if(m_bAutoProc==CControl::AUTOPROC)					//自动上下料加工
	{
//		SetTimer(30,15000,NULL);						//20161212	取消加工用时监控功能
		GetDoc().SetProcTime(0);
		GetDoc().SetProcessState(SystemDoc::AUTOPROC);
		
		int nHead=HeadBoth;	
//		if(GetDoc().GetProcAxisMode()==1)
//			nHead=HeadLeft;
//		if(GetDoc().GetProcAxisMode()==2)
//			nHead=HeadRight;

		if(GetDoc().GetProcAxisMode()==1)				//20190604
		{
			nHead=HeadLeft;
			GetControl().SetCOMOutput(14);				//左轴加工循环 o正向：14，	o逆向：14
		}

		if(GetDoc().GetProcAxisMode()==2)
		{
			nHead=HeadRight;
			GetControl().SetCOMOutput(15);				//右轴加工循环 o正向：15，	o逆向：15
		}

		if(!GetControl().AutoProcPCB(nHead))
		{
//关闭有效吸附轴
			GetDoc().SetAxisIsRun(0,false);							//20180821
			GetDoc().SetAxisIsRun(1,false);	

			GetControl().ResetProcStatus();	

			if(GetDoc().GetSysInfoDBMode()==1)
			{
#ifdef USELOG
				CString strCount;																	//20160901
				strCount.Format("%d",GetDoc().GetSysSNProcedPCBNum());
				GetLog().AppendSNWorkTable(GetDoc().GetSysProcLOTID(),"","",strCount,COleDateTime::GetCurrentTime());
#endif
				GetDoc().SetSysSNProcedPCBNum(0);
			}
		}
		
//		KillTimer(30);												//20161212	取消加工用时监控功能
	}
	else															//手动上下料加工或者指定加工
	{
		if(m_bAutoProc==CControl::MANUPROC)
			GetDoc().SetProcessState(SystemDoc::MANUPROC);

		if(m_bAutoProc==CControl::SELEPROC)		
			GetDoc().SetProcessState(SystemDoc::SELEPROC);
		
		strncpy(ez,GetLang().GetWarningText(31007),256);
		int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);	//"加工单轴PCB  选择  '是'\n加工双轴PCB  选择  '否'\n取消操作 选择             '取消'\n"
		
		if(nSel == IDYES)
		{
			strncpy(ez,GetLang().GetWarningText(31008),256);
			int nSel1 = AfxMessageBox(ez,MB_YESNOCANCEL);//"加工左侧PCB  选择  '是'\n加工右侧PCB  选择  '否'\n取消操作 选择             '取消'\n"
			
			if(nSel1 == IDYES)							//加工左轴
			{	
				if(!GetControl().ManuProcPCB(HeadLeft))
				{
//关闭有效吸附轴
					GetDoc().SetAxisIsRun(0,false);							//20180821
					GetDoc().SetAxisIsRun(1,false);	

					if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
						GetLog().Append_pro(10026,20014);//"利用左边进行指定加工失败","指定加工"
					GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
				}
			}
			else if(nSel1 == IDNO)						//加工右轴
			{	
				if(!GetControl().ManuProcPCB(HeadRight))
				{
//关闭有效吸附轴
					GetDoc().SetAxisIsRun(0,false);							//20180821
					GetDoc().SetAxisIsRun(1,false);	

					if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
						GetLog().Append_pro(10027,20014);//"利用右边进行指定加工失败","指定加工"
					GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
				}				
			}
			else
				GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
		}
		else if(nSel == IDNO)
		{
#ifdef	PRELOADTEST		
			for(int times=0;times<100;times++)
			{	
#ifdef SMCPreLoad
				if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//预加载功能不支持大孔绕烧和双区域6/8内层主标靶方式
				{
					if(!GetControl().PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
					{		
						AfxMessageBox("加工数据预加载过程出现错误，请确认！");
						
						GetControl().SetRunState(CControl::END);
						OnActivateView(true,this,this);
						return 0;
					}
				}
#endif		
				if(!GetControl().ManuProcPCB(HeadBoth))
				{
//关闭有效吸附轴
					GetDoc().SetAxisIsRun(0,false);							//20180821
					GetDoc().SetAxisIsRun(1,false);	

					GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
					break;
				}
			}
#else
			if(!GetControl().ManuProcPCB(HeadBoth))
			{
//关闭有效吸附轴
				GetDoc().SetAxisIsRun(0,false);							//20180821
				GetDoc().SetAxisIsRun(1,false);	

				if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
					GetLog().Append_pro(10029,20014);	//"双轴指定加工失败","指定加工"
				GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));//2010-9-28恢复
			}
#endif		
		}
		else
		{
			GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
			if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
				GetLog().Append_pro(10028,20014);		//"选择取消加工","指定加工"
		}
	}
*/
	int nHead=HeadBoth;									//20190902
	if(GetDoc().GetProcAxisMode()==1)
		nHead=HeadLeft;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=HeadRight;

	if(m_bAutoProc==CControl::AUTOPROC)					//自动上下料加工
	{
//		SetTimer(30,15000,NULL);						//20161212	取消加工用时监控功能
		GetDoc().SetProcTime(0);
		GetDoc().SetProcessState(SystemDoc::AUTOPROC);

		if(GetDoc().GetProcAxisMode()==1)				//20190604
			GetControl().SetCOMOutput(14);				//左轴加工循环 o正向：14，	o逆向：14

		if(GetDoc().GetProcAxisMode()==2)
			GetControl().SetCOMOutput(15);				//右轴加工循环 o正向：15，	o逆向：15

		if(!GetControl().AutoProcPCB(nHead))
		{
//关闭有效吸附轴
			GetDoc().SetAxisIsRun(0,false);							//20180821
			GetDoc().SetAxisIsRun(1,false);	

			GetControl().ResetProcStatus();	

			if(GetDoc().GetSysInfoDBMode()==1)
			{
#ifdef USELOG
				CString strCount;																	//20160901
				strCount.Format("%d",GetDoc().GetProcedPCBNum());
				GetLog().AppendSNWorkTable(GetDoc().GetSysProcLOTID(),GetDoc().GetCurUserName(),GetDoc().GetFileName(),strCount,COleDateTime::GetCurrentTime());
#endif
				GetDoc().SetSysSNProcedPCBNum(0);
			}
		}
		
//		KillTimer(30);												//20161212	取消加工用时监控功能
	}
	else
	{
		if(m_bAutoProc==CControl::MANUPROC)
			GetDoc().SetProcessState(SystemDoc::MANUPROC);

		if(m_bAutoProc==CControl::SELEPROC)		
			GetDoc().SetProcessState(SystemDoc::SELEPROC);

#ifdef	PRELOADTEST		
		for(int times=0;times<100;times++)
		{
/*																//20200601 取消
#ifdef SMCPreLoad
//			if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//预加载功能不支持大孔绕烧和双区域6/8内层主标靶方式
			if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData())&&(!(GetDoc().GetFlowPathMode()==AANDBDOUBLE)))	//20200107 双面加工时此处不进行分区数据预加载
			{
				if(!GetControl().PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
				{		
					AfxMessageBox("加工数据预加载过程出现错误，请确认！");
					
					GetControl().SetRunState(CControl::END);
					OnActivateView(true,this,this);
					return 0;
				}
			}
			else												//20191015
			{
				if(!GetControl().PreLoadCreate(false,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))
				{		
					AfxMessageBox("加工数据预加载过程出现错误，请确认！");
					
					GetControl().SetRunState(CControl::END);
					OnActivateView(true,this,this);
					return 0;
				}
			}
#endif
*/			
			if(!GetControl().ManuProcPCB(HeadBoth))
			{
//关闭有效吸附轴
				GetDoc().SetAxisIsRun(0,false);							//20180821
				GetDoc().SetAxisIsRun(1,false);	
				
				GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
				break;
			}
		}
#else
		if(!GetControl().ManuProcPCB(nHead))
		{
//关闭有效吸附轴
			GetDoc().SetAxisIsRun(0,false);							//20180821
			GetDoc().SetAxisIsRun(1,false);	
			
			if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
			{
				if(nHead==HeadBoth)
					GetLog().Append_pro(10029,20014);//"双轴指定加工失败","指定加工"
				if(nHead==HeadLeft)
					GetLog().Append_pro(10026,20014);//"利用左边进行指定加工失败","指定加工"
				if(nHead==HeadRight)
					GetLog().Append_pro(10027,20014);//"利用右边进行指定加工失败","指定加工"
			}

			GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));//2010-9-28恢复
		}
#endif	
	}

//关闭有效吸附轴
	GetDoc().SetAxisIsRun(0,false);							//20180821
	GetDoc().SetAxisIsRun(1,false);	

//恢复界面和运行状态
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
	GetControl().SetLampStatus(CControl::WARN);
	GetDoc().SetFault(false);
	GetDoc().SetFaultRun(false);
//	GetDoc().SetWarner(false);

	//加工完成后需要上报制程结果
	if (GetDoc().GetProcedPCBNum()>0)
	{
		AfxBeginThread(ThreadProcWipTackReport,this,0,0,0,NULL);
	}
	GetLog().AppendSNOtherStatusTable("待机状态",COleDateTime::GetCurrentTime());				//20160901
	return 0;
}

void CMainRunView::WIPTrackingReport() 
{
	BOOL result = false;
	int times = 0;
	int errCode;
	
	Request req;
	Response rsp;
	CString uuid  = req.UuidGenerator();
	
	time_t timep;
	time(&timep);
	char currentTime[64];
	char currentDate[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localtime(&timep));
	CString failedDataBackup = GetDoc().GetAppPath()+"info\\"+"WIPTrackingReport.txt";
	
	Json::Value reqSetting;
	reqSetting["ImesURL"] = Json::Value(GetDoc().GetSysImesURL());
	reqSetting["Timeout"] = Json::Value(GetDoc().GetSysTimeout());
	req.setReqSetting(reqSetting);
	
	Json::Value reqHead;
	reqHead["eqp_id"] = Json::Value(GetDoc().GetSysMachineSn());
	reqHead["time_stamp"] = Json::Value(currentTime);
	reqHead["trx_id"] = Json::Value(uuid);
	req.setReqHead(reqHead);
	
	Json::Value reqBody;
	Json::Value	arr,item1,item2,item3,item4,item5,item6,item7,item8,item9,item10,item11;
	reqBody["report_dt"] = Json::Value(currentTime);
	reqBody["keep_reason"] = Json::Value("0");
	reqBody["lot_id"] = Json::Value(GetDoc().GetSysProcLOTID());
	
	item1["item_id"] =Json::Value("EQP_ID");
	item1["item_value"] =Json::Value(GetDoc().GetSysMachineSn());
	
	item2["item_id"] =Json::Value("USER_ID");
	item2["item_value"] =Json::Value(GetDoc().GetCurUserName());
	
	item3["item_id"] =Json::Value("DEPT_ID");
	item3["item_value"] =Json::Value(GetDoc().GetCurUserDepartment());
	
	item4["item_id"] =Json::Value("SHIFT_ID");
	item4["item_value"] =Json::Value(GetDoc().GetCurUserShift());
	
	item5["item_id"] =Json::Value("REPORT_DATE");
	item5["item_value"] =Json::Value(currentDate);
	
	COleDateTime beginDt = GetDoc().GetBeginTimeAnalyse(); 
	CString startProcTime = beginDt.Format("%Y-%m-%d %H:%M:%S");
	
	item6["item_id"] =Json::Value("START_DT");
	item6["item_value"] =Json::Value(startProcTime);
	
	item7["item_id"] =Json::Value("END_DT");
	item7["item_value"] =Json::Value(currentTime);
	
	item8["item_id"] =Json::Value("PROD_ID");
	item8["item_value"] =Json::Value(GetDoc().GetSysProcPRODID());
	
	item9["item_id"] =Json::Value("LOT_ID");
	item9["item_value"] =Json::Value(GetDoc().GetSysProcLOTID());
	
	item10["item_id"] =Json::Value("OUTPUT_QTY");
	CString outputQty;																	
	outputQty.Format("%d",GetDoc().GetProcedPCBNum());
	item10["item_value"] =Json::Value(outputQty);
	
	CString setQty;																	
	setQty.Format("%d",GetDoc().GetSysPCBCount());
	item11["item_id"] =Json::Value("T001");
	item11["item_value"] =Json::Value(setQty);
	
	arr["edc"].append(item1);
	arr["edc"].append(item2);
	arr["edc"].append(item3);
	arr["edc"].append(item4);
	arr["edc"].append(item5);
	arr["edc"].append(item6);
	
	arr["edc"].append(item7);
	arr["edc"].append(item8);
	arr["edc"].append(item9);
	arr["edc"].append(item10);
	arr["edc"].append(item11);
	
	reqBody["edc_infos"] = arr;
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
	if (!GetDoc().GetSysModeSwitch() || (int(fp) != 0))//离线模式
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
		GetMainFrame().cs_wiptrack.Lock();
		GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
		GetMainFrame().cs_wiptrack.Unlock();
	}
	else
	{
		for (int i=0; i<3; i++)
		{	
			errCode = GetWSInterfaceImplementor().WIPTrackingReport(req, rsp);
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
				tips.Format("制程结果重传中,次数:%d,时间:%s",times,currentTime);
				::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
				result = false;
				continue;
			}
		}
		if (result)
		{
			CString tips;
			tips.Format("制程结果上传成功,时间:%s",currentTime);
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
			tips.Format("制品上传失败,原因:%s,时间:%s",reason,currentTime);
			GetLog().Append_pro(reason,"制品上传",GetDoc().GetSysProcLOTID());
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			
			reqBody["keep_reason"] = Json::Value("2");
			req.setReqBody(reqBody);
			CString reqAndRsp;
			Json::FastWriter fast_writer;
			reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
				fast_writer.write(req.getReqHead()).c_str(),\
				fast_writer.write(req.getReqBody()).c_str());
			GetMainFrame().cs_wiptrack.Lock();
			GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
			GetMainFrame().cs_wiptrack.Unlock();
		}
	}
}


void CMainRunView::OnRadAutoproc() 									//20160819
{
	if((GetControl().GetRunState()!=CControl::END)&&(GetDoc().GetProcessState()==CControl::MANUPROC))	//20190329 加工过程中不允许手动->自动
		return;

	if(pImageParaSetView->pLampAdj->IsWindowVisible())				//20190403
		return;

	UpdateData();

//加工工艺方式判断
	if(m_bAutoProc==CControl::SELEPROC)									
	{
		if(GetDoc().GetFileMode()!=SystemDoc::NORMALPROC)
		{
			AfxMessageBox("指定加工只能在正常加工方式下使用!");
			return;
		}
	}
	
	m_ctrlChecker.Reset();
	OnDisplayFileInfo();

	if (GetDoc().SetProcessState(m_bAutoProc))
	{
		AfxBeginThread(MViewThreadProcStatusReport,GetMainFrame(),0,0,0,NULL);
	}

	if (m_bAutoProc==CControl::SELEPROC)
	{
		if(1==GetDoc().GetFZInnerMark())							//20160330 为满足方正屏蔽反选功能
			GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(FALSE);
		else
			GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(TRUE);
		
		GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(FALSE);
		
		m_CheckSelectOthers.SetCheck(FALSE);
		m_CheckNullHoles.SetCheck(FALSE);
        GetDoc().SetIsNullPrecessHoles(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(FALSE);
		
		if(1==GetDoc().GetFZInnerMark())							//20160321 为满足方正屏蔽空跑功能
			GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(FALSE);
		else
			GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(TRUE);

		if(GetControl().GetRunState()!=CControl::END)				//20190531
			GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->EnableWindow(FALSE);
		else
			GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->EnableWindow(true);
	}
}

void CMainRunView::OnExit()											//20191015
{
/*
 	UpdateData();
	CBmpMenu oMenu(0, 0, 0, FALSE);
	oMenu.LoadMenu(IDR_SUBFUN);

	if(GetLang().GetCurLanguage()==1)
	{
		char szRead[20] = {""};
		GetLang().GetUIText("SubFun","ID_TABLESUCTIONON",szRead,20);
		oMenu.ModifyMenu(ID_TABLESUCTIONON,MF_STRING | MF_BYCOMMAND , ID_TABLESUCTIONON,szRead);
		GetLang().GetUIText("SubFun","ID_TABLESUCTIONOFF",szRead,20);
		oMenu.ModifyMenu(ID_TABLESUCTIONOFF,MF_STRING | MF_BYCOMMAND , ID_TABLESUCTIONOFF,szRead);
		GetLang().GetUIText("SubFun","ID_FUN_LASERWARNUP",szRead,20);
		oMenu.ModifyMenu(ID_FUN_LASERWARNUP,MF_STRING | MF_BYCOMMAND | MF_GRAYED, ID_FUN_LASERWARNUP,szRead);
		GetLang().GetUIText("SubFun","ID_POWER_TEST",szRead,20);
		oMenu.ModifyMenu(ID_POWER_TEST,MF_STRING | MF_BYCOMMAND , ID_POWER_TEST,szRead);
		GetLang().GetUIText("SubFun","ID_FUN_TABLEOUT",szRead,20);
		oMenu.ModifyMenu(ID_FUN_TABLEOUT,MF_STRING | MF_BYCOMMAND , ID_FUN_TABLEOUT,szRead);
	}

	CPoint pt;
	GetCursorPos(&pt);
	oMenu.TrackPopupMenu(0, pt.x, pt.y, this);
*/
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
	GetLog().Append_pro(10002,20002);//"工作台移出","工作台控制"
}

void CMainRunView::OnRunEnd() 
{
//#ifndef UNLOADISOK
	if(!GetDoc().GetUnloadIsOK())
	{
		if(bInDelay)											//20190329
			return;
	}
//#endif

	if(bInPowerTest)											//20190626
		return;

	if(pImageParaSetView->pLampAdj->IsWindowVisible())			//20190403
		return;

//	GetControl().SetHandPause(FALSE);
	GetControl().SetRunState(CControl::END);
//	m_btnRunPause.EnableWindow(TRUE);	

#ifdef USELOG
	GetLog().Append_pro(10030,20015);//"用户要求停止加工","结束"
	GetLog().AppendSNOtherStatusTable("停机状态",COleDateTime::GetCurrentTime());//停机状态
#endif
}

void CMainRunView::SetBlankColor(const COLORREF &color, int nSaIndex)
{
	if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)//指定加工
	{
		int n = nSaIndex/GetExcellonData().GetSubAreaRow();
		int ncol1 = GetExcellonData().GetSubAreaRow()-nSaIndex%GetExcellonData().GetSubAreaRow()-1;

		int nindex= n%2==0 ? nSaIndex:(n*GetExcellonData().GetSubAreaRow()+ncol1);

		m_ctrlChecker.SetBlock(nindex,color );	

		m_ctrlChecker.Update(nindex);
	}
    else
	{
		for(int j=0; j<=nSaIndex;j++)
		{
			int n = j/GetExcellonData().GetSubAreaRow();
			int ncol1 = GetExcellonData().GetSubAreaRow()-j%GetExcellonData().GetSubAreaRow()-1;

			int nindex= n%2==0 ? j:(n*GetExcellonData().GetSubAreaRow()+ncol1);

			if(!GetExcellonData().GetSubAreaIsEmpty(j))
			{
				m_ctrlChecker.SetBlock(nindex,color );	
				m_ctrlChecker.Refresh();
			}
		}
	}

}

void CMainRunView::OnScanAdjust()									//20191015
{
/*
	char ez[256]={""};
	int nHead=0;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	strncpy(ez,GetLang().GetWarningText(31006),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"测试左侧振镜  选择 '是'\n测试右侧振镜 选择 '否'\n取消操作 选择       '取消'\n"
//	UpdateData();
	
	if(nSel==IDYES)
		nHead=0; 
	else if(nSel==IDNO) 
		nHead=1;
	else
		return;

//平台真空吸附并判断
	GetControl().ChannelOutput(OFANPOWERON,IO_ON); 
	Delay(500);

	if(!GetControl().TableAdsorbInProc(nHead))
	{
		GetControl().ResetTableStatus();
		return;
	}

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	if(!GetControl().AutoAdjustPattern(nHead,false,true))
	{
		GetDoc().WriteCaliTimes();
		GetControl().LightTurnOff();
	}

	GetControl().TableClampOperate(true,GetDoc().GetTableClamp());
	GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
*/
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	int nSel=AfxMessageBox("请确认是否继续操作，继续请选“是”，取消请选“否”！",MB_YESNO);	//20190902
	if(nSel==IDNO)
		return;
	
	int nHead=2;
	if(GetDoc().GetProcAxisMode()==1)
		nHead=0;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=1;

/*
	strncpy(ez,GetLang().GetWarningText(31005),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"单轴振镜测试  选择  '是'\n双轴振镜测试  选择  '否'\n取消操作 选择             '取消'\n"
	
	if(nSel==IDYES)
	{
		strncpy(ez,GetLang().GetWarningText(31006),256);
		nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"测试左侧振镜  选择 '是'\n测试右侧振镜 选择 '否'\n取消操作 选择       '取消'\n"
//		UpdateData();

		if(nSel==IDYES)
			nHead=0; 
		else if(nSel==IDNO) 
			nHead=1;
		else
			return;

	}
	else if(nSel==IDNO)
		nHead=2;
	else
		return;
*/
//平台真空吸附并判断
	GetControl().ChannelOutput(OFANPOWERON,IO_ON); 
	Delay(500);

	if(!GetControl().TableAdsorbInProc(nHead))
	{
		GetControl().ResetTableStatus();
		return;
	}

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	if(!GetControl().AutoAdjustPattern(nHead))
	{
		GetDoc().WriteCaliTimes();
		GetControl().LightTurnOff();
	}

	GetControl().TableClampOperate(true,GetDoc().GetTableClamp());
	GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

void CMainRunView::OnLaserWarmup() 
{
	char szRead[20] = {""};
	char ez[256]={""};
	time_t CurTime;

	if(!GetDoc().GetLaserPowerState())
	{
		strncpy(ez,GetLang().GetWarningText(21106),256);
		int iSel = AfxMessageBox(ez,MB_YESNO);////"确认是否激光上电？  上电  '是'\n取消  '取消'\n"
		if(iSel==IDNO)
			return;

		if(GetControl().LaserComInital())
		{  		
		    GetDoc().SetLaserPowerState(true);			
			time(&CurTime);

			strncpy(szRead ,GetLang().GetWarningText(10015),20);
			m_btnLaserWarmup.SetWindowText(szRead);//"激光掉电"
			m_btnLaserWarmup.SetIcon(IDI_LASERPOWEROFF,IDI_LASERPOWEROFF);

			GetLog().Append_pro(10001,20017,30002);//"激光上电","激光上断电","上电成功"
		}
		else
		{	
			GetLog().Append_pro(10001,20017,30003);//"激光上电","激光上断电","激光上电失败"	
			return ;
		}
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(21107),256);//ly add 20120519
		int iSel = AfxMessageBox(ez,MB_YESNO);////"确认是否激光掉电？  掉电  '是'\n取消  '取消'\n"
		if(iSel==IDNO)
			return;

		if(GetControl().LaserComRelease())
		{
		    GetDoc().SetLaserPowerState(FALSE);
			time(&CurTime);

			strncpy(szRead ,GetLang().GetWarningText(10016),20);
			m_btnLaserWarmup.SetWindowText(szRead);//"激光上电"
	        m_btnLaserWarmup.SetIcon(IDI_LASERPOWERON,IDI_LASERPOWERON);

			GetLog().Append_pro(10033,20017,30004);//"激光断电","激光上断电","断电完成"
		}
	}

	Invalidate(FALSE);
}

void CMainRunView::OnHomeall() 
{
	char ez[256]={""};

	if(GetControl().QueryIOBit(MOTIONSTOPRESET))
	{
		GetDoc().SetMachinePowerState(FALSE);
		strncpy(ez,GetLang().GetWarningText(41003),256);
		if(AfxMessageBox(ez,MB_OKCANCEL)== IDOK)//"机器没有上电，请上电!"
			return ;
	}
//	m_btnHomeAll.EnableWindow(FALSE);

#ifdef USELOG
	GetLog().AppendSNOtherStatusTable("初始状态",COleDateTime::GetCurrentTime());//初始状态
#endif

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);
/*														//20190723 取消
	if(GetControl().GetRunState()==CControl::PAUSE)
	{
		if(GetDoc().GetUse9112())
			GetControl().ChannelOutput(STOPMOVE,MIO_OFF);
		else
			GetControl().SetCOMOutput(11);				//机械手暂停复位  o正向：11，	i逆向：11
	}

	GetControl().SetHandPause(FALSE);					//设置是否暂停手臂的标记
*/
	if(GetControl().HomeAll())
	{
#ifdef USELOG
		GetLog().Append_pro(10034,20018);//"打开系统后，直接回零","回零"
		
#endif
		GetDoc().SetPos(AXISTABX,0);//ly add 20110928
		GetDoc().SetPos(AXISTABY,0);//ly add 20110928
	}
	else
	{
#ifdef USELOG
		GetLog().Append_pro(10035,20018);//"打开系统后，由于电机报警未成功","回零"
#endif
	}

//	m_btnHomeAll.EnableWindow(TRUE);

	GetControl().SetRunState(CControl::END);
#ifdef USELOG
	GetLog().AppendSNOtherStatusTable("停机状态",COleDateTime::GetCurrentTime());//厂商要求初始化結束后需要报停机状态
#endif
	OnActivateView(true,this,this);
}

void CMainRunView::OnSetParameter()									//20191015
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	int nSel=AfxMessageBox("请确认是否继续操作，继续请选“是”，取消请选“否”！",MB_YESNO);	//20190902
	if(nSel==IDNO)
		return;
	
	int nHead=2;
	if(GetDoc().GetProcAxisMode()==1)
		nHead=0;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=1;
/*
	strncpy(ez,GetLang().GetWarningText(31001),256);
	int nSel=AfxMessageBox(ez,MB_YESNOCANCEL);//"单轴功率测试  选择  '是'\n双轴功率测试  选择  '否'\n取消操作 选择             '取消'\n"
	
	if(nSel==IDYES)
	{
		strncpy(ez,GetLang().GetWarningText(31002),256);
		nSel=AfxMessageBox(ez,MB_YESNOCANCEL);//"测试左轴功率  选择 '是'\n测试右轴功率 选择 '否'\n取消操作 选择       '取消'\n"
		
		if(nSel==IDYES)
			nHead=0; 
		else if(nSel==IDNO) 
			nHead=1;
		else
			return;
		
	}
	else if(nSel==IDNO)
		nHead=2;
	else
		return;
*/
#ifdef SMCPreLoad																	//20180619
	if(!GetControl().PreLoadCreate(false,false,true))
	{
		AfxMessageBox("加工数据预加载过程出现错误，请确认！");
		return;
	}
#endif
	
	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);
	
	if(GetDoc().GetFileLPTest())
	{
		if(!GetDoc().GetFileOpenState())
		{
			strncpy(ez,GetLang().GetWarningText(11021),256);
			AfxMessageBox(ez);//"请先打开要加工文件!"
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return;
		}
		
		if(!GetControl().AutoFileLaserPower(nHead,0))					//20180829
		{
//			AfxMessageBox("功率测试出现异常，请确认!");
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return;
		}
	}
	else
	{					
		if(!GetControl().AutoLaserPower(nHead,0))
		{
//			AfxMessageBox("功率测试出现异常，请确认!");
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return;				
		}
	}
	
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

long CMainRunView::GetSelectBlockNum()
{
	return m_ctrlChecker.GetSelectBlockNum();
}
/*
long CMainRunView::GetSelectBlockIndex(int nIndex)const
{
    int nrtn;	

	CCheckerCtrl::BlockPos blkpos = m_ctrlChecker.GetSelectBlockPos(nIndex);
	
	if(!GetDoc().GetIsDoubleFileData())
	{
		if(blkpos.nRow%2==0)
		{
			nrtn = blkpos.nRow*GetExcellonData().GetSubAreaRow()+blkpos.nCol;
		}
		else
		{
			nrtn = blkpos.nRow*GetExcellonData().GetSubAreaRow()+GetExcellonData().GetSubAreaRow()-blkpos.nCol-1;
		}
	}
	else//-------------------------------------------------------------------------------//20161109
	{
		if(blkpos.nRow%2==0)
		{
			nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+blkpos.nCol;
		}
		else
		{
			nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+GetDoc().GetDisplayColCount()-blkpos.nCol-1;
		}		
	}
//---------------------------------------------------------------------------------------
	return nrtn;
}
*/

////指定加工时：由选择指定的块行列号转换成加工分区号
long CMainRunView::GetSelectBlockIndex(int nIndex,BOOL bIsEvenRow)const							//20161216
{
    int nrtn;	

	CCheckerCtrl::BlockPos blkpos = m_ctrlChecker.GetSelectBlockPos(nIndex);
	
	if(!GetDoc().GetIsDoubleFileData())
	{
		if(blkpos.nRow%2==0)
		{
			nrtn = blkpos.nRow*GetExcellonData().GetSubAreaRow()+blkpos.nCol;
		}
		else
		{
			nrtn = blkpos.nRow*GetExcellonData().GetSubAreaRow()+GetExcellonData().GetSubAreaRow()-blkpos.nCol-1;
		}
	}
	else//-------------------------------------------------------------------------------//20161109
	{
		if(bIsEvenRow)
		{
			if(blkpos.nRow%2==0)
			{
				nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+blkpos.nCol;
			}
			else
			{
				nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+GetDoc().GetDisplayColCount()-blkpos.nCol-1;
			}
		}
		else
		{
			if(blkpos.nRow%2==1)
			{
				nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+blkpos.nCol;
			}
			else
			{
				nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+GetDoc().GetDisplayColCount()-blkpos.nCol-1;
			}
		}	
	}
//---------------------------------------------------------------------------------------
	return nrtn;
}

//指定加工时：由选择指定的块行列号转换成块索引号
//整板加工时：由加工分区的索引号转换成块索引号
int CMainRunView::GetBlockIndex(int nIndex,BOOL bIsSelectProc,BOOL bIsEvenRow)
{
    int nrtn;	

	if(bIsSelectProc)
	{
		CCheckerCtrl::BlockPos blkpos = m_ctrlChecker.GetSelectBlockPos(nIndex);
		
		if(!GetDoc().GetIsDoubleFileData())
			nrtn = blkpos.nRow*GetExcellonData().GetSubAreaRow()+blkpos.nCol;
		else
			nrtn = blkpos.nRow*GetDoc().GetDisplayColCount()+blkpos.nCol;
	}
	else
	{
		int m,n;

		if(!GetDoc().GetIsDoubleFileData())
		{
			m=nIndex/GetExcellonData().GetSubAreaRow();											//整行的行数
			n=GetExcellonData().GetSubAreaRow()-nIndex%GetExcellonData().GetSubAreaRow();		//非整行 为奇数行时，左手起有几列
			nrtn=(m%2==0)?nIndex:(m*GetExcellonData().GetSubAreaRow()+n-1);						//非整行 为奇数行时，直接取；非整行 为偶数行时，-1，因为以0为起点
		}
		else
		{
			m=nIndex/GetDoc().GetDisplayColCount();												//整行的行数
			n=GetDoc().GetDisplayColCount()-nIndex%GetDoc().GetDisplayColCount();				//非整行 为奇数行时，左手起有几列

			if(bIsEvenRow)
				nrtn=(m%2==0)?nIndex:(m*GetDoc().GetDisplayColCount()+n-1);						//非整行 为奇数行时，直接取；非整行 为偶数行时，-1，因为以0为起点
			else
				nrtn=(m%2==1)?nIndex:(m*GetDoc().GetDisplayColCount()+n-1);						//非整行 为偶数行时，直接取；非整行 为奇数行时，-1，因为以0为起点
		}
	}

	return nrtn;
}

void CMainRunView::SetBlockColor(const COLORREF &color, int nIndex)
{
	m_ctrlChecker.SetBlock(nIndex,color);	
	m_ctrlChecker.Refresh();	
}

void CMainRunView::OnClearProcNum() 
{
	int nSel = AfxMessageBox("板数是否清零?",MB_YESNO);		
	if(nSel == IDNO)
		return;	
    GetControl().SetProcedPCBNum(0);	
//  OnDisplayDrillInfo(0,0);
	char buf[16];
	char szRead[16]={""};
	strncpy(szRead,GetLang().GetWarningText(10091),16);
	sprintf(buf,szRead,GetDoc().GetProcedPCBNum());//"%-4d 片"
	m_strProcedNum = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());//ly add 20110903 界面增加已加工孔数显示。
	m_DrilledHoleCount = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());//ly add 20111008 界面增加当前加工区域显示。
	m_CurArea = buf;

#ifdef USELOG
	 GetLog().Append_pro(10037,20020);//"标靶数目清零","手动寻找标靶"
#endif

	UpdateData(FALSE);
}

void CMainRunView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char ez[256]={""};
	
	if(nIDEvent == 20)
	{
		time_t CurTime;
		time(&CurTime);
		time_t lastLaserTestTime,GalVoAdjTime;

		m_proLaserPowerWar.SetRange(0,GetDoc().GetLaserTestTime()*60);
		m_proGalvoAdjWar.SetRange(0,GetDoc().GetAdjTime()*60);

//		if(GetDoc().GetAutoLaserPowerTest(HeadLeft)&&GetDoc().GetAutoLaserPowerTest(HeadRight))
//		if(GetDoc().GetAutoLaserPowerTest(HeadLeft)||GetDoc().GetAutoLaserPowerTest(HeadRight))	//20180925
		if(GetDoc().GetAutoLaserTestIsTimed())													//20190711
			lastLaserTestTime=GetDoc().GetLaserTestTime()*60-1;
		else
			lastLaserTestTime=difftime(CurTime, GetDoc().GetLaserTestCurTime());

		m_proLaserPowerWar.SetPos(lastLaserTestTime);

//		if(GetDoc().GetAutoAdjustPattern(HeadLeft)&&GetDoc().GetAutoAdjustPattern(HeadRight))
//		if(GetDoc().GetAutoAdjustPattern(HeadLeft)||GetDoc().GetAutoAdjustPattern(HeadRight))	//20180925
		if(GetDoc().GetAutoGalvoAdjustIsTimed())												//20190711
			GalVoAdjTime=GetDoc().GetAdjTime()*60-1;
		else
			GalVoAdjTime=difftime(CurTime, GetDoc().GetAdjustTime());

		m_proGalvoAdjWar.SetPos(GalVoAdjTime);

		if(lastLaserTestTime>=(GetDoc().GetLaserTestTime()*60))
		{
//			GetDoc().SetAutoLaserPowerTest(true,HeadLeft);
//			GetDoc().SetAutoLaserPowerTest(true,HeadRight);
			GetDoc().SetAutoLaserTestIsTimed(true);												//20190711
		}

		if(GalVoAdjTime>=(GetDoc().GetAdjTime()*60))
		{
//			GetDoc().SetAutoAdjustPattern(true,HeadLeft);
//			GetDoc().SetAutoAdjustPattern(true,HeadRight);
			GetDoc().SetAutoGalvoAdjustIsTimed(true);											//20190711
		}
	}

	if (nIDEvent == 30)											//20161212
	{
		if(GetDoc().GetProcTime()>0)
		{
			time_t CurTime1;
			time(&CurTime1);

//			if(difftime(CurTime1, GetControl().GetCycleStartTime())>900)
			if(difftime(CurTime1, GetControl().GetCycleStartTime())>(GetDoc().GetProcTime()+30))		//超过正常用时半分钟
			{
				GetControl().SetLampStatus(CControl::ERR);
				GetControl().ChannelOutput(OCOMMONALARM ,IO_ON);
				MessageBox("机器异常停止在暂停状态，请确认!");	
				
				GetControl().SetLampStatus(CControl::ORDER);
				GetControl().ChannelOutput(OCOMMONALARM ,IO_OFF);
				
				time(&CurTime1);
				GetControl().SetCycleStartTime(CurTime1);
			}
		}
	}
		
	TVisualFormView::OnTimer(nIDEvent);
}

void CMainRunView::OnRadauto() 
{
/*															//20181106
	UpdateData();
	//m_btnPass.EnableWindow(false);//ly delete 20121127	
	//m_btnPitch.EnableWindow(false);//ly delete 20121127
	GetDlgItem(IDC_RAD_MANUPROC)->EnableWindow(true);
    GetDlgItem(IDC_RAD_SELECT)->EnableWindow(true);
*/
}

void CMainRunView::OnRadmanu() 
{
/*															//20181106
	UpdateData();
	//m_btnPass.EnableWindow(true);	//ly delete 20121127
	//m_btnPitch.EnableWindow(true);//ly delete 20121127	
	GetDlgItem(IDC_RAD_MANUPROC)->EnableWindow(false);
    GetDlgItem(IDC_RAD_SELECT)->EnableWindow(false);

	m_bAutoProc=CControl::MANUPROC;
	UpdateData(false);
*/
}

void CMainRunView::OnChkEnableautoadjust() 
{
	UpdateData(true);
	GetDoc().SetEnAutoAdjust(m_bAutoAdjust);
}

void CMainRunView::OnChkEnableautopower() 
{
	UpdateData(true);
	GetDoc().SetEnAutoPower(m_bAutoPower);	
}

void CMainRunView::OnFidRetry() //ly add 20120202
{
	UpdateData(true);
	GetDoc().SetEnFidRetry(m_bFidRetry);
}

void CMainRunView::MachinePreHot(WPARAM w, LPARAM l)//机器预热
{

}

void CMainRunView::OnClearNg() //ly add 20121127
{
	int nSel = AfxMessageBox("NG板数是否清零?",MB_YESNO);		
	if(nSel == IDNO)
		return;	
	
	GetDoc().SetNGSum(0);
	
	char buf[16];
	sprintf(buf,"%d",GetDoc().GetNGSum());
	m_strNGSum = buf;
	
#ifdef USELOG
	GetLog().Append_pro("NG->0",20020);//"数目清零","手动寻找标靶"
#endif
	UpdateData(FALSE);
}

void CMainRunView::OnClrHoles() //ly add 20121230
{
	int nSel = AfxMessageBox("孔数是否清零?",MB_YESNO);		
	if(nSel == IDNO)
		return;	

	// TODO: Add your control notification handler code here
	CString strinfo,strName;
	strinfo = GetDoc().GetAppPath()+"info\\holes.txt";
	strName = GetDoc().GetFileName();	
		
	char timebuf[128],daybuf[128];       
		
	tzset();
	_strtime(timebuf);
	_strdate(daybuf);
		
	GetInfo().SaveToFile(strinfo,"%s, %s, %.4f\n",daybuf,timebuf,GetDoc().GetHolesSum());

	GetDoc().SetHolesSum(0);
	char buf[64];
	sprintf(buf,"%.4f",GetDoc().GetHolesSum());
	m_strHoleSum = buf;
#ifdef USELOG
	 GetLog().Append_pro("Holes->0",20026);//"数目清零","激光控制"
#endif
	UpdateData(FALSE);
}

void CMainRunView::OnChkManufid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	GetDoc().SetEnManuFid(m_bManuFid);
}

void CMainRunView::OnOneaxis() 
{
	// TODO: Add your control notification handler code here
	if(m_bOneAxis==0)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(23011),256);
		int nSel = ::AfxMessageBox(ez,MB_YESNO);	//ly add 20131226"允许单轴加工可能导致工作效率下降，确定要单轴加工？"						
		if(nSel==IDNO)
		{		
			UpdateData(false);
			return;
		}
		else
		{
			m_bOneAxis=1;
			UpdateData(false);
			GetDoc().SetOneAxis(m_bOneAxis);
		}
	}
	else
	{
		m_bOneAxis=0;
		UpdateData(false);
		GetDoc().SetOneAxis(m_bOneAxis);
		GetDoc().SetCurOneAxis(-1);
	}	
}

void CMainRunView::OnCheckselectothers() 
{	
	if (m_bAutoProc==CControl::SELEPROC)
		m_ctrlChecker.SelectOthers(); 		
	return;
	
}

void CMainRunView::OnCheckNulldrillholes() 
{
	UpdateData();
	GetDoc().SetIsNullPrecessHoles(!m_bCheckNullHoles);
}

//重构加工流程：20161123
//流程模式
void CMainRunView::OnMenuonlyanoreverse() 
{
	// TODO: Add your command handler code here
	if(GetDoc().GetFlowPathMode()!=0)
	{
		if(GetDoc().GetFileOpenState())
		{
			int nSel = AfxMessageBox("改变加工流程模式需要重新导入加工文件，请确认是否继续，继续请选“是”，取消请选“否”。",MB_YESNO);
			
			if(nSel==IDYES)
			{
				GetDoc().SetFlowPathMode(0);
				GetDoc().SetFileOpenState(false);
				GetDoc().SetASideIsProcessing(true);
			}
		}
		else
		{
			GetDoc().SetFlowPathMode(0);
			GetDoc().SetASideIsProcessing(true);
		}
	}
}

void CMainRunView::OnUpdateMenuonlyanoreverse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);
	pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==0);
}

void CMainRunView::OnMenuonlyareverse() 
{
	// TODO: Add your command handler code here
	if(GetDoc().GetFlowPathMode()!=1)
	{
		if(GetDoc().GetFileOpenState())
		{
			int nSel = AfxMessageBox("改变加工流程模式需要重新导入加工文件，请确认是否继续，继续请选“是”，取消请选“否”。",MB_YESNO);
			
			if(nSel==IDYES)
			{
				GetDoc().SetFlowPathMode(1);
				GetDoc().SetFileOpenState(false);
				GetDoc().SetASideIsProcessing(true);
			}
		}
		else
		{
			GetDoc().SetFlowPathMode(1);
			GetDoc().SetASideIsProcessing(true);
		}
	}
}

void CMainRunView::OnUpdateMenuonlyareverse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==1);	
	pCmdUI->Enable(false);

	if(!GetDoc().GetUse9112())								//串口方式上下料
	{
		if(GetDoc().GetFunctionOverBorad())					//有翻板功能
		{
			pCmdUI->Enable(true);
			pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==1);
		}
	}
}

void CMainRunView::OnMenuaandbdouble() 
{
	// TODO: Add your command handler code here
	if(GetDoc().GetFlowPathMode()!=2)
	{
		if(GetDoc().GetFileOpenState())
		{
			int nSel = AfxMessageBox("改变加工流程模式需要重新导入加工文件，请确认是否继续，继续请选“是”，取消请选“否”。",MB_YESNO);
			
			if(nSel==IDYES)
			{
				GetDoc().SetFlowPathMode(2);
				GetDoc().SetFileOpenState(false);
				GetDoc().SetASideIsProcessing(true);
			}
		}
		else
		{
			GetDoc().SetFlowPathMode(2);
			GetDoc().SetASideIsProcessing(true);
		}
	}
}

void CMainRunView::OnUpdateMenuaandbdouble(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==2);	
	pCmdUI->Enable(false);

	if(!GetDoc().GetUse9112())								//串口方式上下料
	{
		if(GetDoc().GetFunctionOverBorad())					//有翻板功能
		{
			pCmdUI->Enable(true);
			pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==2);
		}
	}
}

void CMainRunView::OnMenuonlyb() 
{
	// TODO: Add your command handler code here
	if(GetDoc().GetFlowPathMode()!=3)
	{
		if(GetDoc().GetFileOpenState())
		{
			int nSel = AfxMessageBox("改变加工流程模式需要重新导入加工文件，请确认是否继续，继续请选“是”，取消请选“否”。",MB_YESNO);
			
			if(nSel==IDYES)
			{
				GetDoc().SetFlowPathMode(3);
				GetDoc().SetFileOpenState(false);
				GetDoc().SetASideIsProcessing(false);
			}
		}
		else
		{
			GetDoc().SetFlowPathMode(3);
			GetDoc().SetASideIsProcessing(false);
		}
	}	
}

void CMainRunView::OnUpdateMenuonlyb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==3);	
	pCmdUI->Enable(false);

	if(!GetDoc().GetUse9112())								//串口方式上下料
	{
		if(GetDoc().GetFunctionOverBorad())					//有翻板功能
		{
			pCmdUI->Enable(true);
			pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==3);
		}
	}
}
//轴模式
void CMainRunView::OnMenudoubleaxis()							
{
	// TODO: Add your command handler code here
//	GetDoc().SetProcAxisMode(0);

	if(GetDoc().GetProcAxisMode()!=0)						//20190711
	{
		GetDoc().SetProcAxisMode(0);
		GetDoc().SetAutoGalvoAdjustIsTimed(true);
		GetDoc().SetAutoLaserTestIsTimed(true);
	}	
}

void CMainRunView::OnUpdateMenudoubleaxis(CCmdUI* pCmdUI)				
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==0);		//初始化时双轴加工处于选中状态	

	if(GetDoc().GetProcAxisSelected()==0)					//20191015
		pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==0);
	else
	{
		pCmdUI->Enable(false);
		pCmdUI->SetRadio(false);
	}
}

void CMainRunView::OnMenuonlyleft() 
{
	// TODO: Add your command handler code here
//	GetDoc().SetProcAxisMode(1);

	if(GetDoc().GetProcAxisMode()!=1)						//20190711
	{
		GetDoc().SetProcAxisMode(1);
		GetDoc().SetAutoGalvoAdjustIsTimed(true);
		GetDoc().SetAutoLaserTestIsTimed(true);
	}
}

void CMainRunView::OnUpdateMenuonlyleft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);

	if(!GetDoc().GetUse9112())								//串口方式上下料
	{
//		pCmdUI->Enable(true);
//		pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==1);

		if(GetDoc().GetProcAxisSelected()==0)				//20191015
		{
			pCmdUI->Enable(true);
			pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==1);
		}
		else
		{
			pCmdUI->Enable(GetDoc().GetProcAxisSelected()==1);
			pCmdUI->SetRadio(GetDoc().GetProcAxisSelected()==1);
		}
	}
}

void CMainRunView::OnMenuonlyright() 
{
	// TODO: Add your command handler code here
//	GetDoc().SetProcAxisMode(2);
	
	if(GetDoc().GetProcAxisMode()!=2)						//20190711
	{
		GetDoc().SetProcAxisMode(2);
		GetDoc().SetAutoGalvoAdjustIsTimed(true);
		GetDoc().SetAutoLaserTestIsTimed(true);
	}
}

void CMainRunView::OnUpdateMenuonlyright(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);

	if(!GetDoc().GetUse9112())								//串口方式上下料
	{
//		pCmdUI->Enable(true);
//		pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==2);

		if(GetDoc().GetProcAxisSelected()==0)				//20191015
		{
			pCmdUI->Enable(true);
			pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==2);
		}
		else
		{
			pCmdUI->Enable(GetDoc().GetProcAxisSelected()==2);
			pCmdUI->SetRadio(GetDoc().GetProcAxisSelected()==2);
		}
	}	
}

void CMainRunView::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CString str;
/*
	for(int i=0;i<24;i++)
	{
		str=GetControlManipulator().AddHex(plcSignalOutputMRV[i]);
		AfxMessageBox(str);
	}
*/
/*
	str="00FFBW0M0479011";
	str=GetControlManipulator().AddHex(str);
	AfxMessageBox(str);
*/
	str="00FFBR0M04084C";
	str=GetControlManipulator().AddHex(str);
	AfxMessageBox(str);
/*
	str="00FFBR0M040832";
	str=GetControlManipulator().AddHex(str);
	AfxMessageBox(str);
*/
	str="00FFBW0M04084C0000000000000000000000000000000000000000000000000000000000000000000000000000";
	str=GetControlManipulator().AddHex(str);
	AfxMessageBox(str);
/*
	str="00FFBW0M04083200000000000000000000000000000000000000000000000000";
	str=GetControlManipulator().AddHex(str);
	AfxMessageBox(str);
*/
//	GetDoc().CalculateCalibratePosOffset();

//	GetControl().GetPulsePmr(0,200,1000,true);

#ifdef MEMORYSTATUSMONITOR

	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);

	GetControl().GlobalMemoryStatusEx(&status);	//调用函数取得系统的内存情况

	//内存(单位:MB)
	int nTotal=status.ullTotalPhys/1024/1024;	//总内存
	int nAvail=status.ullAvailPhys/1024/1024;	//可用内存
	int nUsed=(nTotal-nAvail);					//已用内存

	str.Format("%d M",nUsed);
	GetLog().Append_pro(str,"当前物理内存使用量","");

	str.Format("nTotal=%dM, nAvail=%dM, nUsed=%dM" ,nTotal,nAvail,nUsed);
	AfxMessageBox(str);

#endif

	long posX=-92000;
	long posY=389000;

	double errX=GetDoc().GetAxisXErrVaule(posX);
	double errY=GetDoc().GetAxisYErrVaule(posY);
	str.Format("errX(%d)=%f um;errY(%d)=%f um",posX,errX,posY,errY);
	AfxMessageBox(str);
}

void CMainRunView::OnRecognizeTest() 
{
	// TODO: Add your control notification handler code here
//	CString ScrName = GetDoc().GetAppPath()+BMPFILEDIR+"Mark.bmp";
	CString ScrName = GetDoc().GetAppPath()+BMPFILEDIR+"OKnew.bmp";					//20200214

#ifdef USERCOGNEX
//	CogSetShapePolarity((CogShapeExtractPolarityConstants)2);	//Cognex设置目标识别极性 cogShapeExtractPolarityDarkOnLight = 2
	CogSetShapePolarity((CogShapeExtractPolarityConstants)1);
	CogSetTrainParam(0,2.0,1.0);
	if(!CogTrain((LPSTR)(LPCSTR)ScrName,false))
		return;
#endif
/*
	CFileDialog dlg(TRUE, "bmp", "*.bmp");
    if (dlg.DoModal() != IDOK) {
        return;
    }

	CString strPathName=dlg.GetPathName();							//....\bmp.bmp
	strPathName =strPathName.Left(strPathName.ReverseFind('.'));

	double offsetx=0.0,offsety=0.0;	
	double score=0.0;
	CString strDestName,strScore;

	for(int i=0;i<10;i++)
	{
		Delay(500);
		strDestName.Format("%s%d.bmp",strPathName,i);
#ifdef USERCOGNEX		
		CogFind((LPSTR)(LPCSTR)strDestName,offsetx,offsety,0.9,score,0.1,GetDoc().GetCCDContrastThrd());
		strScore.Format("Score=%.3f",score);
		AfxMessageBox(strScore);
#endif
	}
*/
//	CString strDestName = GetDoc().GetAppPath()+BMPFILEDIR+"OKnew.bmp";
	CString strDestName = GetDoc().GetAppPath()+BMPFILEDIR+"ExtTest.bmp";
	double offsetx=0.0,offsety=0.0;	
	double score=0.0;
	CString strScore;

#ifdef USERCOGNEX		
	CogFind((LPSTR)(LPCSTR)strDestName,offsetx,offsety,0.9,score,0.1,GetDoc().GetCCDContrastThrd());
	strScore.Format("Score=%.3f,OffsetX=%.2f,OffsetY=%.2f",score,offsetx,offsety);
	AfxMessageBox(strScore);
#endif

}
