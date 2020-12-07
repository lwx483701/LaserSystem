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
	"����·��ѹ��",					//0
	"��������������",               //1
	"С��ˮ������",					//2
	"AOM���󱨾�",					//3
	"����������",                   //4
	"�����δ�ϵ�",				//5
	"�Ҳ���δ�ϵ�",				//6
    "������¶ȵ�",				//7
    "�Ҳ����¶ȵ�",				//8
    "�˶���1���󱨾�",				//9
    "�˶���2���󱨾�",				//10
    "X�����ŷ�����",				//11
    "Y�����ŷ�����",				//12
    "Z1�����ŷ�����",				//13
    "Z2�����ŷ�����",				//14 
    "BET�������ŷ�����",			//15
    "BET�Ӷ����ŷ�����",			//16
	"���δ�ϵ籨��",               //17
    "X���դ�ߴ���",				//18 
    "Y���դ�ߴ���",				//19
    "�����դ�ߴ���",				//20
	"�Ҳ���դ�ߴ���",             //21  
	"��������ѹ����",				//22
	"��������ѹ����",				//23
	"������1����",					//24
	"������2����",					//25
	"�Ű�ȫ��������",				//26
};*/

CString plcSignalOutputMRV[24]=
{//����6+2��OUT 
	"00FFBW0M0408011",//0   �ϲ��ٴμ���
	"00FFBW0M0409011",//1   ƽ̨ȡ�����
	"00FFBW0M0410011",//2   ����׼��ȡ��
	"00FFBW0M0411011",//3   ��ʼ����
	"00FFBW0M0412011",//4   ���ӹ�ʧ��
	"00FFBW0M0413011",//5   �Ҳ�ӹ�ʧ��
	"00FFBW0M0414011",//6   ƽ̨��������
	"00FFBW0M0415011",//7   ���Ͽ���ȡ��
	"00FFBW0M0416011",//8   �������
	"00FFBW0M0417011",//9   ��������
	"00FFBW0M0418011",//10  ��ͣ(����Ļ)
	"00FFBW0M0419011",//11  ��ͣ��λ
	"00FFBW0M0420011",//12  ���ϵ�ѭ��
	"00FFBW0M0421011",//13  ���ϵ�ѭ�� //һ������
	"00FFBW0M0422011",//14  Z1��ӹ�ѭ�� 
	"00FFBW0M0423011",//15  Z2��ӹ�ѭ��
	"00FFBW0M0467011",//16  ����ѭ��                  //////////////
	"00FFBW0M0468011",//17  ����ѭ��
	"00FFBW0M0469011",//18  ����ƽ̨��������
	"00FFBW0M0470011",//19  ����ƽ̨ȡ�����
	"00FFBW0M0471011",//20  ��������׼��ȡ��
	"00FFBW0M0472011",//21  �������Ͽ���ȡ��
	"00FFBW0M0473011",//22  ����NG׼��ȡ��
	"00FFBW0M0474011",//23  ����NG����ȡ��
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
	ON_MESSAGE(WM_MSG_PREHOT,MachinePreHot)//����Ԥ��
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

	// �ֶ�/�Զ�
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
	sprintf(buf,"%d",GetDoc().GetNGSum());//"szRead( NG��: %d )\n"
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
//			if(nLevel==SystemDoc::PRIMARY)//����				
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
				if(nLevel==SystemDoc::ADMIN)//ϵͳ
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
			if(1==GetDoc().GetFZInnerMark())							//20160330 Ϊ���㷽�����η�ѡ����
				GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(FALSE);
			else
				GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(TRUE);
			
			GetDlgItem(IDC_CHECK_NULLDRILLHOLES)->ShowWindow(FALSE);		
		}
		else
		{
			GetDlgItem(IDC_CHECKSELECTOTHERS)->ShowWindow(FALSE);
			
			if(1==GetDoc().GetFZInnerMark())							//20160321 Ϊ���㷽�����ο��ܹ���
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
	GetImageCaptor().SelectChannel(GetImageCaptor().GetCurrentChannel());	//��AVT��ȶ�˲���

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
		m_btnLaserWarmup.SetWindowText(szRead);//"�������"
		m_btnLaserWarmup.SetIcon(IDI_LASERPOWEROFF,IDI_LASERPOWEROFF);
	}
	else
	{
		strncpy(szRead ,GetLang().GetWarningText(10016),20);
		m_btnLaserWarmup.SetWindowText(szRead);//"�����ϵ�"
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
	sprintf(buf,szRead,GetDoc().GetProcedPCBNum());//"%-4d Ƭ \n"
	m_strProcedNum = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());//ly add 20110903 ���������Ѽӹ�������ʾ��
	m_DrilledHoleCount = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());//ly add 20111008 �������ӵ�ǰ�ӹ�������ʾ��
	m_CurArea = buf;
	sprintf(buf,"%d",GetDoc().GetNGSum());//"szRead( NG��: %d )\n"
	m_strNGSum = buf;//ly add 20121127
	sprintf(buf,"%.4f",GetDoc().GetHolesSum());
	m_strHoleSum = buf;//ly add 20121127
/*
    BOOL bPcb1 = GetControl().GetFiducialMatchStatus(HeadLeft);
	BOOL bPcb2 = GetControl().GetFiducialMatchStatus(HeadRight);
	
	if(bPcb1&&bPcb2)
	{
		strncpy(szRead,GetLang().GetWarningText(10092),64);
		sprintf(buf,szRead);//"�б�ƥ�����"
	}
	else if(!bPcb1&&bPcb2)
	{
		strncpy(szRead,GetLang().GetWarningText(10093),64);
		sprintf(buf,szRead);//"���б�Ѱ��ʧ��"
	      
	}
	else if(!bPcb2&&bPcb1)
	{
		strncpy(szRead,GetLang().GetWarningText(10094),64);
	    sprintf(buf,szRead);//"�Ҳ�б�Ѱ��ʧ��"
	}
	else
	{
		strncpy(szRead,GetLang().GetWarningText(10095),64);
	    sprintf(buf,szRead);//"����б�Ѱ��ʧ��"
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
	sprintf(buf,szRead,GetDoc().GetProcedPCBNum());//"%-4d Ƭ"
	m_strProcedNum = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());//ly add 20110903 ���������Ѽӹ�������ʾ��
	m_DrilledHoleCount = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());//ly add 20111008 �������ӵ�ǰ�ӹ�������ʾ��
	m_CurArea = buf;
	sprintf(buf,"%d",GetDoc().GetNGSum());//"szRead( NG��: %d )\n"
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

//�����ӹ��߳� 20190125
//�ع��ӹ����̣�20161123
void CMainRunView::OnRunStart()
{
	if(bRunning)													//20190401
		return;

	GetDoc().SaveProcessParam();									//20200715 ���˳����������˴�

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
		int nSel = AfxMessageBox("��ȷ���Ƿ�Ҫ���³�ʼ��ʱ����Ƽ��ܹ�? ",MB_YESNO);		
		if(nSel == IDYES )
		{
			if(!GetDoc().InitSentinal())
			{
				AfxMessageBox("��ȷ��ʱ����Ƽ��ܹ��Ƿ���ȷ������߼���ʱ���Ƿ��ڣ�");

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
		AfxMessageBox("�ӹ��ļ�δ���Ż������޷��ӹ�����ȷ�ϣ�");

		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return 0;
	}

//	UpdateData();

//�жϻ�������״̬
	if(!GetDoc().GetMotorState())										
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);	//"����δ������㣬��������ز���!"

		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return 0;
	}

//�жϼ������ϵ�״̬
	if(!GetDoc().GetLaserPowerState())												//20181225
	{
		int nsel = AfxMessageBox("������δ�ϵ磬������ѡ���ǡ���ȡ����ѡ����!",MB_YESNO);
		if(nsel == IDNO)
		{
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//�ӹ����շ�ʽ�ж�
	if(m_bAutoProc==CControl::SELEPROC)									
	{
		if(GetDoc().GetFileMode()!=SystemDoc::NORMALPROC)							//20160819
		{
			AfxMessageBox("ָ���ӹ�ֻ���������ӹ���ʽ��ʹ��!");

			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//�����ļ��Ƿ�������
	if(!GetDoc().GetFileOpenState())									
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
		AfxMessageBox(ez);	//"���ȴ�Ҫ�ӹ��������ļ�!"
#ifdef USELOG
		GetLog().Append_pro(10057,20025);	//"���ȴ�Ҫ�ӹ��ļ�!"
#endif
		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return 0;
	}

//�Ƿ�������ж�λ
	if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)
	{
		if((!GetDoc().GetIsFiducialDo2(0))||(!GetDoc().GetIsFiducialDo2(1)))
		{
			strncpy(ez,GetLang().GetWarningText(21038),256);
			AfxMessageBox(ez);	//"���ȶ�PCB����б�ж�λ!"
#ifdef USELOG
			GetLog().Append_pro(10058,20025);	//"û��������ж�λ����ͼ�ӹ�!"
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
			AfxMessageBox(ez);	//"���ȶ�PCB����б�ж�λ!"
#ifdef USELOG
			GetLog().Append_pro(10058,20025);	//"û��������ж�λ����ͼ�ӹ�!"
#endif
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//��������������Ϣ��LOTID��Ϣ���Ӵ��ļ���ʼֻ��¼һ��
	if(GetDoc().GetIsRecordPowerPara())									
	{
		CString szLotid;
		GetDoc().SetIsRecordPowerPara(FALSE);
#ifdef USELOG
		szLotid= GetDoc().GetLOTIDFix();
		if (GetDoc().GetDrillInc())										//��ʿ�����ӵ�LotID���巽ʽ
			szLotid= GetDoc().GetLOTIDFix()+ GetDoc().GetNoProcessID();

		GetLog().Append_PowerPara(GetDoc().GetFileName(),GetControl().ReadPowerPara((LPCTSTR)GetDoc().GetToolFileName()),szLotid);
#endif
	}

//���м�����״̬��س���
#ifdef LASERMONITOR
	CString	laserLinkPath = GetDoc().GetAppPath()+"E400IXSocetLink";		
    ShellExecute(NULL, "open", laserLinkPath, "", NULL, SW_SHOWMINIMIZED);
#endif

//�ӹ�����������ȷ�ϣ��л��������趨�������ȷ��
	if(GetDoc().GetShowTool()==1)						
	{
		GetMainFrame().m_Framework.Get(15)->SetActivePane();

		int nsel = AfxMessageBox("��ȷ�ϼӹ����������'��'��ʼ�ӹ�  �������ֹͣ�ӹ�",MB_YESNO);

		GetMainFrame().m_Framework.Get(37)->SetActivePane();
		
		if(nsel == IDNO)
		{
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}

//�Զ������Ͽ�ʼ����ǰ���������ϵ�״̬����һ����ѯ 28����е�ִ��󱨾�
	if(!GetDoc().GetUse9112())
	{
		if(GetDoc().GetProcessState()==CControl::AUTOPROC)
			GetControl().QueryCOMInput(28);					
	}

//	GetControl().SetRunState(CControl::RUN);
//�ر���Ч������
	GetDoc().SetAxisIsRun(0,false);							//20180821
	GetDoc().SetAxisIsRun(1,false);

//	OnActivateView(true,this,this);
/*																//20200601 ȡ��
#ifndef PRELOADTEST
//���SMC���ɽ��мӹ�����Ԥ���ع���
#ifdef SMCPreLoad
//	if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
	if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData())&&(!(GetDoc().GetFlowPathMode()==AANDBDOUBLE)))	//20200107 ˫��ӹ�ʱ�˴������з�������Ԥ����
	{
		if(!GetControl().PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
		{		
			AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
			
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}
	else														//20191015
	{
		if(!GetControl().PreLoadCreate(false,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))
		{		
			AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
			
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return 0;
		}
	}
#endif
#endif
*/
	UpdateData();

	GetLog().Append_pro("��ʼ�ӹ�","���̿���");				//20200720 ����

//��ʼ�����������״̬
	m_DrilledHoleCount = "0";
	m_CurArea = "0";
	GetControl().SetLampStatus(CControl::ORDER);
	GetDoc().SetFault(false);							//�����Ĵ���״̬���л�����
	GetDoc().SetFaultRun(false);						//��������������״̬���ǻ��߷�
//	GetDoc().SetWarner(false);							//�����ľ���״̬���л�����
	GetDoc().SetErrorPCB(0);							//��¼�Զ������ϼӹ�����������ԭ����ֵ��쳣�����������ڵ���6�ź󱨾������򲻱���

//��ʼ���ӹ����õ�����������
//	GetControl().Calc75umControl();						//��ʿ��75un�жϼ���		//20180829
#ifdef LASERMONITOR
	GetDoc().ReadLaserConfig();							//��ѯ���������״̬
#endif

//ʱ�����
	GetDoc().SetTimeAnalyse(TRUE);
	GetDoc().SetBeginTimeAnalyse(COleDateTime::GetCurrentTime());
	GetDoc().SetCalculateBeginTime(GetTickCount());
	GetLog().AppendSNOtherStatusTable("����״̬",COleDateTime::GetCurrentTime());

#ifndef MACHINEHOTTEST
//�򿪷��
	GetControl().ChannelOutput(OFANPOWERON,IO_ON);
#endif

//��ʼ����PCB��ӹ�
/*
	if(m_bAutoProc==CControl::AUTOPROC)					//�Զ������ϼӹ�
	{
//		SetTimer(30,15000,NULL);						//20161212	ȡ���ӹ���ʱ��ع���
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
			GetControl().SetCOMOutput(14);				//����ӹ�ѭ�� o����14��	o����14
		}

		if(GetDoc().GetProcAxisMode()==2)
		{
			nHead=HeadRight;
			GetControl().SetCOMOutput(15);				//����ӹ�ѭ�� o����15��	o����15
		}

		if(!GetControl().AutoProcPCB(nHead))
		{
//�ر���Ч������
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
		
//		KillTimer(30);												//20161212	ȡ���ӹ���ʱ��ع���
	}
	else															//�ֶ������ϼӹ�����ָ���ӹ�
	{
		if(m_bAutoProc==CControl::MANUPROC)
			GetDoc().SetProcessState(SystemDoc::MANUPROC);

		if(m_bAutoProc==CControl::SELEPROC)		
			GetDoc().SetProcessState(SystemDoc::SELEPROC);
		
		strncpy(ez,GetLang().GetWarningText(31007),256);
		int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);	//"�ӹ�����PCB  ѡ��  '��'\n�ӹ�˫��PCB  ѡ��  '��'\nȡ������ ѡ��             'ȡ��'\n"
		
		if(nSel == IDYES)
		{
			strncpy(ez,GetLang().GetWarningText(31008),256);
			int nSel1 = AfxMessageBox(ez,MB_YESNOCANCEL);//"�ӹ����PCB  ѡ��  '��'\n�ӹ��Ҳ�PCB  ѡ��  '��'\nȡ������ ѡ��             'ȡ��'\n"
			
			if(nSel1 == IDYES)							//�ӹ�����
			{	
				if(!GetControl().ManuProcPCB(HeadLeft))
				{
//�ر���Ч������
					GetDoc().SetAxisIsRun(0,false);							//20180821
					GetDoc().SetAxisIsRun(1,false);	

					if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
						GetLog().Append_pro(10026,20014);//"������߽���ָ���ӹ�ʧ��","ָ���ӹ�"
					GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
				}
			}
			else if(nSel1 == IDNO)						//�ӹ�����
			{	
				if(!GetControl().ManuProcPCB(HeadRight))
				{
//�ر���Ч������
					GetDoc().SetAxisIsRun(0,false);							//20180821
					GetDoc().SetAxisIsRun(1,false);	

					if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
						GetLog().Append_pro(10027,20014);//"�����ұ߽���ָ���ӹ�ʧ��","ָ���ӹ�"
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
				if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
				{
					if(!GetControl().PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
					{		
						AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
						
						GetControl().SetRunState(CControl::END);
						OnActivateView(true,this,this);
						return 0;
					}
				}
#endif		
				if(!GetControl().ManuProcPCB(HeadBoth))
				{
//�ر���Ч������
					GetDoc().SetAxisIsRun(0,false);							//20180821
					GetDoc().SetAxisIsRun(1,false);	

					GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
					break;
				}
			}
#else
			if(!GetControl().ManuProcPCB(HeadBoth))
			{
//�ر���Ч������
				GetDoc().SetAxisIsRun(0,false);							//20180821
				GetDoc().SetAxisIsRun(1,false);	

				if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
					GetLog().Append_pro(10029,20014);	//"˫��ָ���ӹ�ʧ��","ָ���ӹ�"
				GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));//2010-9-28�ָ�
			}
#endif		
		}
		else
		{
			GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
			if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
				GetLog().Append_pro(10028,20014);		//"ѡ��ȡ���ӹ�","ָ���ӹ�"
		}
	}
*/
	int nHead=HeadBoth;									//20190902
	if(GetDoc().GetProcAxisMode()==1)
		nHead=HeadLeft;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=HeadRight;

	if(m_bAutoProc==CControl::AUTOPROC)					//�Զ������ϼӹ�
	{
//		SetTimer(30,15000,NULL);						//20161212	ȡ���ӹ���ʱ��ع���
		GetDoc().SetProcTime(0);
		GetDoc().SetProcessState(SystemDoc::AUTOPROC);

		if(GetDoc().GetProcAxisMode()==1)				//20190604
			GetControl().SetCOMOutput(14);				//����ӹ�ѭ�� o����14��	o����14

		if(GetDoc().GetProcAxisMode()==2)
			GetControl().SetCOMOutput(15);				//����ӹ�ѭ�� o����15��	o����15

		if(!GetControl().AutoProcPCB(nHead))
		{
//�ر���Ч������
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
		
//		KillTimer(30);												//20161212	ȡ���ӹ���ʱ��ع���
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
/*																//20200601 ȡ��
#ifdef SMCPreLoad
//			if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
			if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData())&&(!(GetDoc().GetFlowPathMode()==AANDBDOUBLE)))	//20200107 ˫��ӹ�ʱ�˴������з�������Ԥ����
			{
				if(!GetControl().PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
				{		
					AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
					
					GetControl().SetRunState(CControl::END);
					OnActivateView(true,this,this);
					return 0;
				}
			}
			else												//20191015
			{
				if(!GetControl().PreLoadCreate(false,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))
				{		
					AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
					
					GetControl().SetRunState(CControl::END);
					OnActivateView(true,this,this);
					return 0;
				}
			}
#endif
*/			
			if(!GetControl().ManuProcPCB(HeadBoth))
			{
//�ر���Ч������
				GetDoc().SetAxisIsRun(0,false);							//20180821
				GetDoc().SetAxisIsRun(1,false);	
				
				GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
				break;
			}
		}
#else
		if(!GetControl().ManuProcPCB(nHead))
		{
//�ر���Ч������
			GetDoc().SetAxisIsRun(0,false);							//20180821
			GetDoc().SetAxisIsRun(1,false);	
			
			if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
			{
				if(nHead==HeadBoth)
					GetLog().Append_pro(10029,20014);//"˫��ָ���ӹ�ʧ��","ָ���ӹ�"
				if(nHead==HeadLeft)
					GetLog().Append_pro(10026,20014);//"������߽���ָ���ӹ�ʧ��","ָ���ӹ�"
				if(nHead==HeadRight)
					GetLog().Append_pro(10027,20014);//"�����ұ߽���ָ���ӹ�ʧ��","ָ���ӹ�"
			}

			GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));//2010-9-28�ָ�
		}
#endif	
	}

//�ر���Ч������
	GetDoc().SetAxisIsRun(0,false);							//20180821
	GetDoc().SetAxisIsRun(1,false);	

//�ָ����������״̬
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
	GetControl().SetLampStatus(CControl::WARN);
	GetDoc().SetFault(false);
	GetDoc().SetFaultRun(false);
//	GetDoc().SetWarner(false);

	//�ӹ���ɺ���Ҫ�ϱ��Ƴ̽��
	if (GetDoc().GetProcedPCBNum()>0)
	{
		AfxBeginThread(ThreadProcWipTackReport,this,0,0,0,NULL);
	}
	GetLog().AppendSNOtherStatusTable("����״̬",COleDateTime::GetCurrentTime());				//20160901
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
				tips.Format("�Ƴ̽���ش���,����:%d,ʱ��:%s",times,currentTime);
				::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
				result = false;
				continue;
			}
		}
		if (result)
		{
			CString tips;
			tips.Format("�Ƴ̽���ϴ��ɹ�,ʱ��:%s",currentTime);
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
			tips.Format("��Ʒ�ϴ�ʧ��,ԭ��:%s,ʱ��:%s",reason,currentTime);
			GetLog().Append_pro(reason,"��Ʒ�ϴ�",GetDoc().GetSysProcLOTID());
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
	if((GetControl().GetRunState()!=CControl::END)&&(GetDoc().GetProcessState()==CControl::MANUPROC))	//20190329 �ӹ������в������ֶ�->�Զ�
		return;

	if(pImageParaSetView->pLampAdj->IsWindowVisible())				//20190403
		return;

	UpdateData();

//�ӹ����շ�ʽ�ж�
	if(m_bAutoProc==CControl::SELEPROC)									
	{
		if(GetDoc().GetFileMode()!=SystemDoc::NORMALPROC)
		{
			AfxMessageBox("ָ���ӹ�ֻ���������ӹ���ʽ��ʹ��!");
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
		if(1==GetDoc().GetFZInnerMark())							//20160330 Ϊ���㷽�����η�ѡ����
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
		
		if(1==GetDoc().GetFZInnerMark())							//20160321 Ϊ���㷽�����ο��ܹ���
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
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
	GetLog().Append_pro(10002,20002);//"����̨�Ƴ�","����̨����"
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
	GetLog().Append_pro(10030,20015);//"�û�Ҫ��ֹͣ�ӹ�","����"
	GetLog().AppendSNOtherStatusTable("ͣ��״̬",COleDateTime::GetCurrentTime());//ͣ��״̬
#endif
}

void CMainRunView::SetBlankColor(const COLORREF &color, int nSaIndex)
{
	if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)//ָ���ӹ�
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
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	strncpy(ez,GetLang().GetWarningText(31006),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"���������  ѡ�� '��'\n�����Ҳ��� ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
//	UpdateData();
	
	if(nSel==IDYES)
		nHead=0; 
	else if(nSel==IDNO) 
		nHead=1;
	else
		return;

//ƽ̨����������ж�
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
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	int nSel=AfxMessageBox("��ȷ���Ƿ����������������ѡ���ǡ���ȡ����ѡ���񡱣�",MB_YESNO);	//20190902
	if(nSel==IDNO)
		return;
	
	int nHead=2;
	if(GetDoc().GetProcAxisMode()==1)
		nHead=0;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=1;

/*
	strncpy(ez,GetLang().GetWarningText(31005),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"�����񾵲���  ѡ��  '��'\n˫���񾵲���  ѡ��  '��'\nȡ������ ѡ��             'ȡ��'\n"
	
	if(nSel==IDYES)
	{
		strncpy(ez,GetLang().GetWarningText(31006),256);
		nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"���������  ѡ�� '��'\n�����Ҳ��� ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
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
//ƽ̨����������ж�
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
		int iSel = AfxMessageBox(ez,MB_YESNO);////"ȷ���Ƿ񼤹��ϵ磿  �ϵ�  '��'\nȡ��  'ȡ��'\n"
		if(iSel==IDNO)
			return;

		if(GetControl().LaserComInital())
		{  		
		    GetDoc().SetLaserPowerState(true);			
			time(&CurTime);

			strncpy(szRead ,GetLang().GetWarningText(10015),20);
			m_btnLaserWarmup.SetWindowText(szRead);//"�������"
			m_btnLaserWarmup.SetIcon(IDI_LASERPOWEROFF,IDI_LASERPOWEROFF);

			GetLog().Append_pro(10001,20017,30002);//"�����ϵ�","�����϶ϵ�","�ϵ�ɹ�"
		}
		else
		{	
			GetLog().Append_pro(10001,20017,30003);//"�����ϵ�","�����϶ϵ�","�����ϵ�ʧ��"	
			return ;
		}
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(21107),256);//ly add 20120519
		int iSel = AfxMessageBox(ez,MB_YESNO);////"ȷ���Ƿ񼤹���磿  ����  '��'\nȡ��  'ȡ��'\n"
		if(iSel==IDNO)
			return;

		if(GetControl().LaserComRelease())
		{
		    GetDoc().SetLaserPowerState(FALSE);
			time(&CurTime);

			strncpy(szRead ,GetLang().GetWarningText(10016),20);
			m_btnLaserWarmup.SetWindowText(szRead);//"�����ϵ�"
	        m_btnLaserWarmup.SetIcon(IDI_LASERPOWERON,IDI_LASERPOWERON);

			GetLog().Append_pro(10033,20017,30004);//"����ϵ�","�����϶ϵ�","�ϵ����"
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
		if(AfxMessageBox(ez,MB_OKCANCEL)== IDOK)//"����û���ϵ磬���ϵ�!"
			return ;
	}
//	m_btnHomeAll.EnableWindow(FALSE);

#ifdef USELOG
	GetLog().AppendSNOtherStatusTable("��ʼ״̬",COleDateTime::GetCurrentTime());//��ʼ״̬
#endif

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);
/*														//20190723 ȡ��
	if(GetControl().GetRunState()==CControl::PAUSE)
	{
		if(GetDoc().GetUse9112())
			GetControl().ChannelOutput(STOPMOVE,MIO_OFF);
		else
			GetControl().SetCOMOutput(11);				//��е����ͣ��λ  o����11��	i����11
	}

	GetControl().SetHandPause(FALSE);					//�����Ƿ���ͣ�ֱ۵ı��
*/
	if(GetControl().HomeAll())
	{
#ifdef USELOG
		GetLog().Append_pro(10034,20018);//"��ϵͳ��ֱ�ӻ���","����"
		
#endif
		GetDoc().SetPos(AXISTABX,0);//ly add 20110928
		GetDoc().SetPos(AXISTABY,0);//ly add 20110928
	}
	else
	{
#ifdef USELOG
		GetLog().Append_pro(10035,20018);//"��ϵͳ�����ڵ������δ�ɹ�","����"
#endif
	}

//	m_btnHomeAll.EnableWindow(TRUE);

	GetControl().SetRunState(CControl::END);
#ifdef USELOG
	GetLog().AppendSNOtherStatusTable("ͣ��״̬",COleDateTime::GetCurrentTime());//����Ҫ���ʼ���Y������Ҫ��ͣ��״̬
#endif
	OnActivateView(true,this,this);
}

void CMainRunView::OnSetParameter()									//20191015
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	int nSel=AfxMessageBox("��ȷ���Ƿ����������������ѡ���ǡ���ȡ����ѡ���񡱣�",MB_YESNO);	//20190902
	if(nSel==IDNO)
		return;
	
	int nHead=2;
	if(GetDoc().GetProcAxisMode()==1)
		nHead=0;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=1;
/*
	strncpy(ez,GetLang().GetWarningText(31001),256);
	int nSel=AfxMessageBox(ez,MB_YESNOCANCEL);//"���Ṧ�ʲ���  ѡ��  '��'\n˫�Ṧ�ʲ���  ѡ��  '��'\nȡ������ ѡ��             'ȡ��'\n"
	
	if(nSel==IDYES)
	{
		strncpy(ez,GetLang().GetWarningText(31002),256);
		nSel=AfxMessageBox(ez,MB_YESNOCANCEL);//"�������Ṧ��  ѡ�� '��'\n�������Ṧ�� ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
		
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
		AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
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
			AfxMessageBox(ez);//"���ȴ�Ҫ�ӹ��ļ�!"
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return;
		}
		
		if(!GetControl().AutoFileLaserPower(nHead,0))					//20180829
		{
//			AfxMessageBox("���ʲ��Գ����쳣����ȷ��!");
			GetControl().SetRunState(CControl::END);
			OnActivateView(true,this,this);
			return;
		}
	}
	else
	{					
		if(!GetControl().AutoLaserPower(nHead,0))
		{
//			AfxMessageBox("���ʲ��Գ����쳣����ȷ��!");
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

////ָ���ӹ�ʱ����ѡ��ָ���Ŀ����к�ת���ɼӹ�������
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

//ָ���ӹ�ʱ����ѡ��ָ���Ŀ����к�ת���ɿ�������
//����ӹ�ʱ���ɼӹ�������������ת���ɿ�������
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
			m=nIndex/GetExcellonData().GetSubAreaRow();											//���е�����
			n=GetExcellonData().GetSubAreaRow()-nIndex%GetExcellonData().GetSubAreaRow();		//������ Ϊ������ʱ���������м���
			nrtn=(m%2==0)?nIndex:(m*GetExcellonData().GetSubAreaRow()+n-1);						//������ Ϊ������ʱ��ֱ��ȡ�������� Ϊż����ʱ��-1����Ϊ��0Ϊ���
		}
		else
		{
			m=nIndex/GetDoc().GetDisplayColCount();												//���е�����
			n=GetDoc().GetDisplayColCount()-nIndex%GetDoc().GetDisplayColCount();				//������ Ϊ������ʱ���������м���

			if(bIsEvenRow)
				nrtn=(m%2==0)?nIndex:(m*GetDoc().GetDisplayColCount()+n-1);						//������ Ϊ������ʱ��ֱ��ȡ�������� Ϊż����ʱ��-1����Ϊ��0Ϊ���
			else
				nrtn=(m%2==1)?nIndex:(m*GetDoc().GetDisplayColCount()+n-1);						//������ Ϊż����ʱ��ֱ��ȡ�������� Ϊ������ʱ��-1����Ϊ��0Ϊ���
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
	int nSel = AfxMessageBox("�����Ƿ�����?",MB_YESNO);		
	if(nSel == IDNO)
		return;	
    GetControl().SetProcedPCBNum(0);	
//  OnDisplayDrillInfo(0,0);
	char buf[16];
	char szRead[16]={""};
	strncpy(szRead,GetLang().GetWarningText(10091),16);
	sprintf(buf,szRead,GetDoc().GetProcedPCBNum());//"%-4d Ƭ"
	m_strProcedNum = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledHoleCount());//ly add 20110903 ���������Ѽӹ�������ʾ��
	m_DrilledHoleCount = buf;
	sprintf(buf,"%d",GetDoc().GetCurPCBDrilledArea());//ly add 20111008 �������ӵ�ǰ�ӹ�������ʾ��
	m_CurArea = buf;

#ifdef USELOG
	 GetLog().Append_pro(10037,20020);//"�����Ŀ����","�ֶ�Ѱ�ұ��"
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
			if(difftime(CurTime1, GetControl().GetCycleStartTime())>(GetDoc().GetProcTime()+30))		//����������ʱ�����
			{
				GetControl().SetLampStatus(CControl::ERR);
				GetControl().ChannelOutput(OCOMMONALARM ,IO_ON);
				MessageBox("�����쳣ֹͣ����ͣ״̬����ȷ��!");	
				
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

void CMainRunView::MachinePreHot(WPARAM w, LPARAM l)//����Ԥ��
{

}

void CMainRunView::OnClearNg() //ly add 20121127
{
	int nSel = AfxMessageBox("NG�����Ƿ�����?",MB_YESNO);		
	if(nSel == IDNO)
		return;	
	
	GetDoc().SetNGSum(0);
	
	char buf[16];
	sprintf(buf,"%d",GetDoc().GetNGSum());
	m_strNGSum = buf;
	
#ifdef USELOG
	GetLog().Append_pro("NG->0",20020);//"��Ŀ����","�ֶ�Ѱ�ұ��"
#endif
	UpdateData(FALSE);
}

void CMainRunView::OnClrHoles() //ly add 20121230
{
	int nSel = AfxMessageBox("�����Ƿ�����?",MB_YESNO);		
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
	 GetLog().Append_pro("Holes->0",20026);//"��Ŀ����","�������"
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
		int nSel = ::AfxMessageBox(ez,MB_YESNO);	//ly add 20131226"������ӹ����ܵ��¹���Ч���½���ȷ��Ҫ����ӹ���"						
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

//�ع��ӹ����̣�20161123
//����ģʽ
void CMainRunView::OnMenuonlyanoreverse() 
{
	// TODO: Add your command handler code here
	if(GetDoc().GetFlowPathMode()!=0)
	{
		if(GetDoc().GetFileOpenState())
		{
			int nSel = AfxMessageBox("�ı�ӹ�����ģʽ��Ҫ���µ���ӹ��ļ�����ȷ���Ƿ������������ѡ���ǡ���ȡ����ѡ���񡱡�",MB_YESNO);
			
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
			int nSel = AfxMessageBox("�ı�ӹ�����ģʽ��Ҫ���µ���ӹ��ļ�����ȷ���Ƿ������������ѡ���ǡ���ȡ����ѡ���񡱡�",MB_YESNO);
			
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

	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
		if(GetDoc().GetFunctionOverBorad())					//�з��幦��
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
			int nSel = AfxMessageBox("�ı�ӹ�����ģʽ��Ҫ���µ���ӹ��ļ�����ȷ���Ƿ������������ѡ���ǡ���ȡ����ѡ���񡱡�",MB_YESNO);
			
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

	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
		if(GetDoc().GetFunctionOverBorad())					//�з��幦��
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
			int nSel = AfxMessageBox("�ı�ӹ�����ģʽ��Ҫ���µ���ӹ��ļ�����ȷ���Ƿ������������ѡ���ǡ���ȡ����ѡ���񡱡�",MB_YESNO);
			
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

	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
	{
		if(GetDoc().GetFunctionOverBorad())					//�з��幦��
		{
			pCmdUI->Enable(true);
			pCmdUI->SetRadio(GetDoc().GetFlowPathMode()==3);
		}
	}
}
//��ģʽ
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
//	pCmdUI->SetRadio(GetDoc().GetProcAxisMode()==0);		//��ʼ��ʱ˫��ӹ�����ѡ��״̬	

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

	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
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

	if(!GetDoc().GetUse9112())								//���ڷ�ʽ������
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

	GetControl().GlobalMemoryStatusEx(&status);	//���ú���ȡ��ϵͳ���ڴ����

	//�ڴ�(��λ:MB)
	int nTotal=status.ullTotalPhys/1024/1024;	//���ڴ�
	int nAvail=status.ullAvailPhys/1024/1024;	//�����ڴ�
	int nUsed=(nTotal-nAvail);					//�����ڴ�

	str.Format("%d M",nUsed);
	GetLog().Append_pro(str,"��ǰ�����ڴ�ʹ����","");

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
//	CogSetShapePolarity((CogShapeExtractPolarityConstants)2);	//Cognex����Ŀ��ʶ���� cogShapeExtractPolarityDarkOnLight = 2
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
