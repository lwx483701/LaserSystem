// FileInfoSettingView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "FileInfoSettingView.h"
#include "SysParameter.h"
#include "Decode.h"
#include "ToolParaView.h"
#include "PointcontrlView.h"
#include "MainFrm.h"
#include "MainRunView.h"
#include "FilePointView.h"
#include "DlgRotate.h"
#include "OperateControl.h"
#include "ScaleSetDlgView.h"
#include <time.h>
#include <direct.h>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ToolUtil.h"
#include "MarkMake.h"
using namespace ToolUtil;
using namespace std;
#pragma comment(lib, "shell32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileInfoSettingView

IMPLEMENT_DYNCREATE(CFileInfoSettingView, TVisualFormView)

CFileInfoSettingView *pFileInfoSettingView;

CFileInfoSettingView::CFileInfoSettingView()
	: TVisualFormView(CFileInfoSettingView::IDD)
{
	//{{AFX_DATA_INIT(CFileInfoSettingView)
	m_bDrillTimeInfo = FALSE;
	m_bDrillStrInfo=FALSE;
	m_bDrillMachInfo = FALSE;
	m_bDrillLotInfo  = FALSE;
	m_bDrillDayInfo  = FALSE;
	m_strMachineSn   = _T("HANS");
	m_lScanSize   = 65;
	m_iProcMode = 0;
	m_iCrdAbsolute= 1;
	m_iUnitInch	  = 1;
	m_iDateFormat = 1;
	m_iDecimalNum = 3;
	m_iIntegerNum = 2;
	m_lFidOffX1 = 0;
	m_lFidOffX2 = 0;
	m_lFidOffX3 = 0;
	m_lFidOffX4 = 0;
	m_lFidOffY2 = 0;
	m_lFidOffY3 = 0;
	m_lFidOffY4 = 0;
	m_lFidOffY1 = 0;
	m_staticState = _T("无导入文件！");//"未打开数据文件！"
	m_fStrZoom = 2.4;
	m_iOpticalPathMode = 0;
	m_iAutoThicking = 0;
	m_ulPCBThickness = 1000;
	m_iFileMode = 0;
	m_bLotIDFix = FALSE;
	m_bLotIDInc = FALSE;
	m_bLotIDScale = FALSE;
	m_strLotIdFix = _T("");
	m_strLotIdInc = _T("");
	m_bAxisNo = FALSE;
	m_b3Fid = FALSE;
	m_bCheckManulScaleRange = FALSE;
	m_EditNoProcess = _T("");
	m_Combo_OverPCB=0;
	m_DoubleManScaleX = _T("");
	m_DoubleManScaleY = _T("");
	m_bFileInfoDataModified=false;
	//}}AFX_DATA_INIT
}

CFileInfoSettingView::~CFileInfoSettingView()
{
	delete pScaleSetView;					//20160812
//	delete pProcLogin_SN;					//20160901
}

void CFileInfoSettingView::DoDataExchange(CDataExchange* pDX)
{
	TVisualFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileInfoSettingView)
	DDX_Control(pDX, IDC_CHECK_OVERBORAD, m_Check_OverBorad);
	DDX_Control(pDX, IDC_CHECKMANSCALE, m_Check_ManuScale);
	DDX_Control(pDX, IDC_CHK_3FID, m_chk3Fid);
	DDX_Control(pDX, IDC_CHK_DRILLAXISNO, m_chkAxisNo);
	DDX_Control(pDX, IDC_DRILLSCALE, m_chkLotIdScale);
	DDX_Control(pDX, IDC_FIXING, m_chkLotIdFix);
	DDX_Control(pDX, IDC_INCREASING, m_chkLotIdInc);
	DDX_Control(pDX, IDC_BTN_ROTATE, m_btnRotate);
	DDX_Control(pDX, IDC_STASTATE, m_stState);
	DDX_Control(pDX, IDC_STATIC_FILEINFO, m_stFileInfo);
	DDX_Control(pDX, IDC_CHK_DRILLSTRINGINFO, m_chkDrillStringInfo);
	DDX_Control(pDX, IDC_BTN_TRANSSAVE, m_btnTransSave);
	DDX_Control(pDX, IDC_EDT_STRZOOM, m_edtStrZoom);
	DDX_Control(pDX, IDC_EDT_PCBTHICKNESS, m_edtPCBThickness);
	DDX_Control(pDX, IDC_BTN_MIRROR, m_btnMirror);
	DDX_Control(pDX, IDC_BT_ENTER, m_btnTxtZoomEnter);
	DDX_Control(pDX, IDC_BTN_OPTIMIZEPATH, m_btnOptimizePath);
	DDX_Control(pDX, IDC_CMB_INTEGERNUM, m_cIntegernum);
	DDX_Control(pDX, IDC_CMB_DECIMALNUM, m_cDecimalnum);
	DDX_Control(pDX, IDC_BTN_SETFIDOFFSET, m_btnSetFidOffset);
	DDX_Control(pDX, IDC_EDT_FIDY4, m_edtFidOffY4);
	DDX_Control(pDX, IDC_EDT_FIDY3, m_edtFidOffY3);
	DDX_Control(pDX, IDC_EDT_FIDY2, m_edtFidOffY2);
	DDX_Control(pDX, IDC_EDT_FIDY1, m_edtFidOffY1);
	DDX_Control(pDX, IDC_EDT_FIDX4, m_edtFidOffX4);
	DDX_Control(pDX, IDC_EDT_FIDX3, m_edtFidOffX3);
	DDX_Control(pDX, IDC_EDT_FIDX2, m_edtFidOffX2);
	DDX_Control(pDX, IDC_EDT_FIDX1, m_edtFidOffX1);
	DDX_Control(pDX, IDC_EDT_SCANSIZE, m_edtScanSize);
	DDX_Control(pDX, IDC_EDT_MACHINESN, m_edtMachineSn);
	DDX_Control(pDX, IDC_BT_SELECTFILE, m_btnSelectFile);
	DDX_Control(pDX, IDC_CHK_DRILLTIMEINFO, m_chkDrillTimeInfo);
	DDX_Control(pDX, IDC_CHK_DRILLMACHINFO, m_chkDrillMachInfo);
	DDX_Control(pDX, IDC_CHK_DRILLLOTINFO, m_chkDrillLotInfo);
	DDX_Control(pDX, IDC_CHK_DRILLDAYINFO, m_chkDrillDayInfo);
	DDX_Check(pDX, IDC_CHK_DRILLTIMEINFO, m_bDrillTimeInfo);
	DDX_Check(pDX, IDC_CHK_DRILLSTRINGINFO, m_bDrillStrInfo);
	DDX_Check(pDX, IDC_CHK_DRILLMACHINFO, m_bDrillMachInfo);
	DDX_Check(pDX, IDC_CHK_DRILLLOTINFO, m_bDrillLotInfo);
	DDX_Check(pDX, IDC_CHK_DRILLDAYINFO, m_bDrillDayInfo);
	DDX_Text(pDX, IDC_EDT_MACHINESN, m_strMachineSn);
	DDV_MaxChars(pDX, m_strMachineSn, 30);
	DDX_Text(pDX, IDC_EDT_SCANSIZE, m_lScanSize);
	DDX_Radio(pDX, IDC_RAD_PROCESSDIR, m_iProcMode);
	DDX_Radio(pDX, IDC_RAD_ABSOLUTE, m_iCrdAbsolute);
	DDX_Radio(pDX, IDC_RAD_UNITINCH, m_iUnitInch);
	DDX_Radio(pDX, IDC_RAD_DATAFORMAT, m_iDateFormat);
	DDX_CBIndex(pDX, IDC_CMB_DECIMALNUM, m_iDecimalNum);
	DDX_CBIndex(pDX, IDC_CMB_INTEGERNUM, m_iIntegerNum);
	DDX_Text(pDX, IDC_EDT_FIDX1, m_lFidOffX1);
	DDX_Text(pDX, IDC_EDT_FIDX2, m_lFidOffX2);
	DDX_Text(pDX, IDC_EDT_FIDX3, m_lFidOffX3);
	DDX_Text(pDX, IDC_EDT_FIDX4, m_lFidOffX4);
	DDX_Text(pDX, IDC_EDT_FIDY2, m_lFidOffY2);
	DDX_Text(pDX, IDC_EDT_FIDY3, m_lFidOffY3);
	DDX_Text(pDX, IDC_EDT_FIDY4, m_lFidOffY4);
	DDX_Text(pDX, IDC_EDT_FIDY1, m_lFidOffY1);
	DDX_Text(pDX, IDC_STASTATE, m_staticState);
	DDX_Text(pDX, IDC_EDT_STRZOOM, m_fStrZoom);
	DDX_Radio(pDX, IDC_RADIO_SHORTPATH, m_iOpticalPathMode);
	DDX_Radio(pDX, IDC_RADIO_MANTHICKNESS, m_iAutoThicking);
	DDX_Text(pDX, IDC_EDT_PCBTHICKNESS, m_ulPCBThickness);
	DDX_Radio(pDX, IDC_RADIO_NORMALPROC, m_iFileMode);
	DDX_Check(pDX, IDC_FIXING, m_bLotIDFix);
	DDX_Check(pDX, IDC_INCREASING, m_bLotIDInc);
	DDX_Check(pDX, IDC_DRILLSCALE, m_bLotIDScale);
	DDX_Text(pDX, IDC_EDT_LOTIDFIX, m_strLotIdFix);
	DDV_MaxChars(pDX, m_strLotIdFix, 30);
	DDX_Text(pDX, IDC_EDT_LOTIDINC, m_strLotIdInc);
	DDV_MaxChars(pDX, m_strLotIdInc, 30);
	DDX_Check(pDX, IDC_CHK_DRILLAXISNO, m_bAxisNo);
	DDX_Check(pDX, IDC_CHK_3FID, m_b3Fid);
	DDX_Check(pDX, IDC_CHECKSCALETHRD, m_bCheckManulScaleRange);
	DDX_Text(pDX, IDC_EDIT_NOPROCESSID, m_EditNoProcess);
	DDX_CBIndex(pDX, IDC_COMBO_OVERPCB, m_Combo_OverPCB);
	DDX_Text(pDX, IDC_EDIT_MANSCALEX, m_DoubleManScaleX);
	DDX_Text(pDX, IDC_EDIT_MANSCALEY, m_DoubleManScaleY);
	//DDX_Control(pDX,IDC_PROGRESS1, m_prog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileInfoSettingView, TVisualFormView)
	//{{AFX_MSG_MAP(CFileInfoSettingView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_SELECTFILE, OnSelectFile)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RAD_PROCESSDIR, OnRadProcMode)
	ON_BN_CLICKED(IDC_RAD_PROCESSDIRN, OnRadProcMode)
	ON_BN_CLICKED(IDC_BTN_OPTIMIZEPATH, OnOptimizePath)
	ON_BN_CLICKED(IDC_RAD_UNITINCH, OnRadUnitinch)
	ON_BN_CLICKED(IDC_RAD_UNITMETRIC, OnRadUnitmetric)
	ON_BN_CLICKED(IDC_CHK_DRILLMACHINFO, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_DRILLDAYINFO, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_DRILLTIMEINFO, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_DRILLLOTINFO, OnChkDrilllotinfo)
	ON_BN_CLICKED(IDC_BT_ENTER, OnBtEnter)
	ON_BN_CLICKED(IDC_BTN_MIRROR, OnBtnMirror)
	ON_BN_CLICKED(IDC_RADIO_SHORTPATH, OnRadioShortpath)
	ON_BN_CLICKED(IDC_RADIO_LONGPATH, OnRadioLongpath)
	ON_BN_CLICKED(IDC_RADIO_MANTHICKNESS, OnRadioManthickness)
	ON_BN_CLICKED(IDC_RADIO_AUTOTHICKNESS, OnRadioAutothickness)
	ON_BN_CLICKED(IDC_BTN_THICKNESS, OnBtnSetThickness)
	ON_BN_CLICKED(IDC_RADIO_NORMALPROC, OnRadioNormalproc)
	ON_BN_CLICKED(IDC_RADIO_INNERMARK, OnRadioInnermark)
	ON_BN_CLICKED(IDC_RADIO_LOCALMARK, OnRadioLocalmark)
	ON_BN_CLICKED(IDC_BTN_TRANSSAVE, OnBtnTranssave)
	ON_BN_CLICKED(IDC_RADIO_SALOCALMARK, OnRadioSalocalmark)
	ON_BN_CLICKED(IDC_CHK_DRILLSTRINGINFO, OnChangeData)
	ON_EN_KILLFOCUS(IDC_EDT_SCANSIZE, OnKillfocusEdtScansize)
//	ON_BN_CLICKED(IDC_RAD_ABSOLUTE, OnChangeData)
//	ON_BN_CLICKED(IDC_RAD_INCREMENTAL, OnChangeData)
//	ON_BN_CLICKED(IDC_RAD_DATAFORMAT, OnChangeData)
//	ON_BN_CLICKED(IDC_RADIO7, OnChangeData)
//	ON_BN_CLICKED(IDC_RADIO8, OnChangeData)
//	ON_CBN_SELCHANGE(IDC_CMB_INTEGERNUM, OnChangeData)
//	ON_CBN_SELCHANGE(IDC_CMB_DECIMALNUM, OnChangeData)
	ON_BN_CLICKED(IDC_BTN_ROTATE, OnBtnRotate)
	ON_BN_CLICKED(IDC_FIXING, OnChangeData)
	ON_BN_CLICKED(IDC_INCREASING, OnChangeData)
	ON_BN_CLICKED(IDC_DRILLSCALE, OnDrillscale)
	ON_BN_CLICKED(IDC_CHK_DRILLAXISNO, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_3FID, OnChk3fid)
//	ON_BN_CLICKED(IDC_RADIO_MANSCALE, OnRadioManscale)
//	ON_BN_CLICKED(IDC_RADIO_REFSCALE, OnRadioRefscale)
	ON_BN_CLICKED(IDC_LOADAVGSCALE, OnLoadavgscale)
	ON_BN_CLICKED(IDC_CHECKSCALETHRD, OnCheckscalethrd)
	ON_BN_CLICKED(IDC_CHECKMANSCALE, OnCheckmanscale)
//	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_COMMAND(ID_MENUASIDEDISPLAY, OnMenuasidedisplay)
	ON_UPDATE_COMMAND_UI(ID_MENUASIDEDISPLAY, OnUpdateMenuasidedisplay)
	ON_COMMAND(ID_MENUBSIDEDISPLAY, OnMenubsidedisplay)
	ON_UPDATE_COMMAND_UI(ID_MENUBSIDEDISPLAY, OnUpdateMenubsidedisplay)
	ON_BN_CLICKED(IDC_CHK_DRILLMACHINFO, OnChangeData)
	ON_BN_CLICKED(IDC_RAD_PROCESSDIR, OnRadProcMode)
	ON_MESSAGE(WM_USERUPDATESELECTFILE,OnUpdateSeleteFileName)
	ON_BN_CLICKED(IDC_RAD_PROCESSDIRN, OnRadProcMode)
	ON_BN_CLICKED(IDC_CHK_DRILLDAYINFO, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_DRILLTIMEINFO, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_DRILLSTRINGINFO, OnChangeData)
	ON_BN_CLICKED(IDC_FIXING, OnChangeData)
	ON_BN_CLICKED(IDC_INCREASING, OnChangeData)
	ON_BN_CLICKED(IDC_CHK_DRILLAXISNO, OnChangeData)
	ON_EN_CHANGE(IDC_EDT_MACHINESN, OnChangeData)
	ON_EN_CHANGE(IDC_EDT_LOTIDFIX, OnChangeData)
	ON_EN_CHANGE(IDC_EDT_LOTIDINC, OnChangeData)
	ON_EN_CHANGE(IDC_EDT_STRZOOM, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_NOPROCESSID, OnChangeData)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileInfoSettingView diagnostics

#ifdef _DEBUG
void CFileInfoSettingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFileInfoSettingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileInfoSettingView message handlers
int CFileInfoSettingView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	pFileInfoSettingView=this;

//	m_chkDrillDayInfo.SubclassDlgItem(IDC_CHK_DRILLDAYINFO,this);
	m_chkDrillDayInfo.SetIcon(IDI_CHECKED,IDI_UNCHECKED);

//	m_chkDrillTimeInfo.SubclassDlgItem(IDC_CHK_DRILLTIMEINFO,this);
	m_chkDrillTimeInfo.SetIcon(IDI_CHECKED,IDI_UNCHECKED);

	m_chkDrillStringInfo.SetIcon(IDI_CHECKED,IDI_UNCHECKED);

//	m_chkDrillMachInfo.SubclassDlgItem(IDC_CHK_DRILLMACHINFO,this);
	m_chkDrillMachInfo.SetIcon(IDI_CHECKED,IDI_UNCHECKED);

//	m_chkDrillLotInfo.SubclassDlgItem(IDC_CHK_DRILLLOTINFO,this);
	m_chkDrillLotInfo.SetIcon(IDI_CHECKED,IDI_UNCHECKED);

//	m_btnSelectFile.SubclassDlgItem(IDC_BT_SELECTFILE,this);
	m_btnSelectFile.SetIcon(IDI_OPENFILE,IDI_OPENFILE);

//	m_btnOptimizePath.SubclassDlgItem(IDC_BTN_OPTIMIZEPATH,this);
//  m_btnOptimizePath.SetIcon(IDI_OPTIM,IDI_OPTIM);

//	m_stFileInfo.SubclassDlgItem(IDC_STATIC3,this);
//	m_stState.SubclassDlgItem(IDC_ST_PROCINFO,this);

 	return 0;
}

void CFileInfoSettingView::OnDestroy()
{
	TVisualFormView::OnDestroy();	
}

void CFileInfoSettingView::OnRadProcMode() 
{
	UpdateData();

	if(GetDoc().GetProcMode()!=SystemDoc::PROCMODE(m_iProcMode))
	{
		GetDoc().SetProcMode(SystemDoc::PROCMODE(m_iProcMode));

		m_bFileInfoDataModified=true;

		if(GetDoc().GetFileOpenState())
		{			
			CString	str="";
			SetDlgItemText(IDC_EDT_SELECTFILE,str);
			GetDoc().SetFileOpenState(false);

			char ez[100]={""};
			strncpy(ez,GetLang().GetWarningText(11025),100);//"数据文件须重新导入!"
			m_staticState = _T(ez);	
//			AfxMessageBox("主标靶工艺方式发生改变，须重新打开数据文件!");
		}

		OnRadioNormalproc();
	}
}

void CFileInfoSettingView::OnUpdateSeleteFileName(WPARAM wParam, LPARAM lParam)
{
	int retCode = lParam;
	CString fileNameA = _T("");  
    fileNameA.Format("%s",(char *)wParam);

	CString fileNameB = _T("");  
    fileNameB.Format("%s",(char *)lParam);

	twoFilePath[0]=fileNameA;
	twoFilePath[1]=fileNameB;

	if (GetDoc().GetFlowPathMode()== ONLYB)
	{
		SelectFile(fileNameB);
	}
	else
	{
		SelectFile(fileNameA);
	}
	
	
	/*if (-1 == fileName.Find(_T(".sa")))
	{
		MessageBox(_T("检测到不是sa文件"));
		OnBtnTranssave();
	}*/

	/*else//失败需要创建CProcLogin_SN窗口
	{
		CProcLogin_SN  procLoginDlg;								//20190815
		procLoginDlg.m_strLOTID_SN = fileName;
		procLoginDlg.DoModal();
	}*/
}

void CFileInfoSettingView::OnSelectFile()
{
//	GetDoc().SetFileIsOptimized(false);								//20180116

	if(GetDoc().GetSysInfoDBMode()==0)								//20181212
	{
		SetDlgItemText(IDC_EDT_SELECTFILE,"");
		GetDoc().SetFileIsOptimized(false);							//20181225

		CString strFileName="";
		SelectFile(strFileName);
	}
	else
	{
//		pProcLogin_SN->ShowWindow(SW_SHOW);
		CProcLogin_SN  procLoginDlg;								//20190815
		if (GetDoc().GetCurUserLevel() == SystemDoc::PRIMARY)//当前用户为操作员
		{
			procLoginDlg.m_strAmployeeID_SN = GetDoc().GetCurUserName();
			procLoginDlg.m_strDEPTID_SN = GetDoc().GetCurUserDepartment();
		}
		procLoginDlg.DoModal();
		DealLotIdFixAndInc();
	}
	
#ifdef HIKAGV
	if((GetDoc().GetFlowPathMode()==AANDBDOUBLE)&&(!GetDoc().GetPCBBoardIsReady()))
	{
		int nSel=AfxMessageBox("请选择是否需要AGV小车送料过来？",MB_YESNO);
		
		if(nSel==IDNO)
			return;

		if(!GetControl().AGVTransport(0))
			AfxMessageBox("AGV小车送料过程出现异常，请确认！");
	}
#endif
}

void CFileInfoSettingView::SelectFile(CString& strFileName)
{
	if (GetDoc().GetFlowPathMode()==AANDBDOUBLE)				//此模式下不支持文件旋转和镜像
	{
		if(GetDoc().GetSysModeSwitch())
		{
			Delay(200);
			
			if (!OpenDataFile(twoFilePath[0],true))
			{  
				AfxMessageBox("A面数据文件打开失败!");
				return;
			}
			GetDoc().SetFirstMarkPos(GetExcellonData().GetFiducialPos(),true);		//保存A面第一个标靶
			
			if (!OpenDataFile(twoFilePath[1],true))
			{  
				AfxMessageBox("B面数据文件打开失败!");
				return;
			}
			GetDoc().SetFirstMarkPos(GetExcellonData().GetFiducialPos(),false);		//保存B面第一个标靶	
			
			GetDoc().SetIsFiducialDo2(FALSE,0);
			GetDoc().SetIsFiducialDo2(FALSE,1);
			
			GetDoc().SetASideIsDisplay(false);										//设定B面显示状态
			
			CMainFrame* pMainFrame;
			pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
			pMainFrame->m_wndStatusBar.SetPaneText(1,"  显示:B面");
		}
		else
		{
			
			twoFilePath[0]="";
			twoFilePath[1]="";
			
			int nSel=AfxMessageBox("A&B双面加工流程模式下只支持SA数据文件格式 ！\n\n     继续请选“是”，取消请选“否”。",MB_YESNO);
			
			if(nSel==IDNO)
				return;
			
			Delay(200);
			
			strFileName="";		
			AfxMessageBox("请选择A面数据文件!");
			
			if (!OpenDataFile(strFileName,true))
			{  
				AfxMessageBox("A面数据文件打开失败!");
				return;
			}
			
			twoFilePath[0]=strFileName;	
			GetDoc().SetFirstMarkPos(GetExcellonData().GetFiducialPos(),true);		//保存A面第一个标靶
			
			strFileName="";
			AfxMessageBox("请选择B面数据文件!");
			
			if (!OpenDataFile(strFileName,true))
			{  
				AfxMessageBox("B面数据文件打开失败!");
				return;
			}
			
			twoFilePath[1]=strFileName;	
			GetDoc().SetFirstMarkPos(GetExcellonData().GetFiducialPos(),false);		//保存B面第一个标靶	
			
			GetDoc().SetIsFiducialDo2(FALSE,0);
			GetDoc().SetIsFiducialDo2(FALSE,1);
			
			GetDoc().SetASideIsDisplay(false);										//设定B面显示状态
			
			//		(CMainFrame*)AfxGetMainWnd()->m_wndStatusBar.SetPaneText(1,"  显示:B面");
			
			CMainFrame* pMainFrame;
			pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
			pMainFrame->m_wndStatusBar.SetPaneText(1,"  显示:B面");
			
			//		OnBtnSetThickness();
		}
	}
	else
	{
		if(GetDoc().GetSysModeSwitch())
		{
			if (!OpenDataFile(strFileName,true))
			return;
		}
		else
		{
			if (!OpenDataFile(strFileName))
			return;
		}
		
		GetDoc().SetIsFiducialDo(false);
		
		if(GetDoc().GetIsDoubleFileData())						//20161109 不支持双区域6/8内标靶文件的转存和旋转
		{
			GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(FALSE);	
		}
	}
}


void CFileInfoSettingView::OnKillfocusEdtScansize() //ly change 20111221
{
	CString sc;
	GetDlgItemText(IDC_EDT_SCANSIZE,sc);
	long scsize = atol(sc);
	if(scsize>GetDoc().GetScanSizeMax() || scsize<SCANSIZEMIN)
	{
		CString txt;
		txt.Format("请确认扫描区域大小设定范围是%d-%dmm!",SCANSIZEMIN,GetDoc().GetScanSizeMax());
		AfxMessageBox(txt);

		txt.Format("%d",GetDoc().GetScanSize());
		m_edtScanSize.SetWindowText(txt);
	}
	
	UpdateData();

	GetDoc().SetScanSize(m_lScanSize);

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{	
	if(!bActivate)
	{
		if(m_bFileInfoDataModified)
		{
			GetDoc().SaveProcessParam();
			m_bFileInfoDataModified=false;
		}
	}
	else
	{
/*		
		if (GetDoc().GetDrillInc())
		{
			GetDlgItem(IDC_STATIC_NOPROCESSID)->ShowWindow(TRUE);
			GetDlgItem(IDC_EDIT_NOPROCESSID)->ShowWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_STATIC_NOPROCESSID)->ShowWindow(FALSE);
			GetDlgItem(IDC_EDIT_NOPROCESSID)->ShowWindow(FALSE);
		}
*/		
		if(GetControl().GetRunState()!=CControl::END)
		{
			GetDlgItem(IDC_BT_SELECTFILE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_MIRROR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(FALSE);
		
			GetDlgItem(IDC_RAD_UNITINCH)->EnableWindow(FALSE);//单位
			GetDlgItem(IDC_RAD_UNITMETRIC)->EnableWindow(FALSE);		
			GetDlgItem(IDC_RAD_ABSOLUTE)->EnableWindow(FALSE);//坐标
			GetDlgItem(IDC_RAD_INCREMENTAL)->EnableWindow(FALSE);	
			GetDlgItem(IDC_RAD_DATAFORMAT)->EnableWindow(FALSE);//数据形式
			GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);	
			GetDlgItem(IDC_CMB_INTEGERNUM)->EnableWindow(FALSE);//数据格式
			GetDlgItem(IDC_CMB_DECIMALNUM)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_RAD_PROCESSDIR)->EnableWindow(FALSE);
			GetDlgItem(IDC_RAD_PROCESSDIRN)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_3FID)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_CHK_DRILLDAYINFO)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_DRILLTIMEINFO)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_DRILLMACHINFO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_MACHINESN)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_DRILLLOTINFO)->EnableWindow(FALSE);
			GetDlgItem(IDC_DRILLSCALE)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_DRILLAXISNO)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_DRILLSTRINGINFO)->EnableWindow(FALSE);
			GetDlgItem(IDC_FIXING)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(FALSE);
			GetDlgItem(IDC_INCREASING)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_STRZOOM)->EnableWindow(FALSE);					
			GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(FALSE);						//富士康ID
			GetDlgItem(IDC_BT_ENTER)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_EDT_SCANSIZE)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_NORMALPROC)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_INNERMARK)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_LOCALMARK)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_SALOCALMARK)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_LONGPATH)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_SHORTPATH)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_EDT_PCBTHICKNESS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_THICKNESS)->EnableWindow(FALSE);
			
			if(GetDoc().GetUIManSetScale())
			{
				GetDlgItem(IDC_CHECKMANSCALE)->EnableWindow(FALSE);				
				GetDlgItem(IDC_STATIC29)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC31)->EnableWindow(FALSE);

//				GetDlgItem(IDC_RADIO_MANSCALE)->EnableWindow(FALSE);
//				GetDlgItem(IDC_RADIO_REFSCALE)->EnableWindow(FALSE);				
//				GetDlgItem(IDC_STATIC_SCALE)->EnableWindow(FALSE);
//				GetDlgItem(IDC_STATIC_SCALE2)->EnableWindow(FALSE);

				GetDlgItem(IDC_EDIT_MANSCALEX)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDIT_MANSCALEY)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECKSCALETHRD)->EnableWindow(FALSE);
				GetDlgItem(IDC_LOADAVGSCALE)->EnableWindow(FALSE);
			}
		}
		else
		{
			if (GetDoc().GetSysModeSwitch())//在线模式不支持本地加载
			{
				GetDlgItem(IDC_BT_SELECTFILE)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_BT_SELECTFILE)->EnableWindow(TRUE);
			}
			

			GetDlgItem(IDC_RAD_PROCESSDIR)->EnableWindow(TRUE);
			GetDlgItem(IDC_RAD_PROCESSDIRN)->EnableWindow(TRUE);

			GetDlgItem(IDC_BTN_THICKNESS)->EnableWindow(TRUE);

			if(GetDoc().GetUIManSetScale())
			{				
				GetDlgItem(IDC_CHECKMANSCALE)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC29)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC31)->EnableWindow(TRUE);
				
//				GetDlgItem(IDC_RADIO_MANSCALE)->EnableWindow(TRUE);
//				GetDlgItem(IDC_RADIO_REFSCALE)->EnableWindow(TRUE);						
//				GetDlgItem(IDC_STATIC_SCALE)->EnableWindow(TRUE);
//				GetDlgItem(IDC_STATIC_SCALE2)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_EDIT_MANSCALEX)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_MANSCALEY)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHECKSCALETHRD)->EnableWindow(TRUE);
				GetDlgItem(IDC_LOADAVGSCALE)->EnableWindow(TRUE);
			}

			int nLevel = GetDoc().GetCurUserLevel();
			if(nLevel==SystemDoc::PRIMARY)//初级
			{
//#ifdef ZHIHAO	
				if(GetDoc().GetCustomerSpecial()==2 || !GetDoc().GetSysModeSwitch())
				{
					GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(TRUE);
					GetDlgItem(IDC_BTN_MIRROR)->EnableWindow(TRUE);
					GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(TRUE);
				}
//#else
				else
				{
					GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(FALSE);
					GetDlgItem(IDC_BTN_MIRROR)->EnableWindow(FALSE);
					GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(FALSE);
				}
//#endif
				GetDlgItem(IDC_RAD_UNITINCH)->EnableWindow(FALSE);//单位
				GetDlgItem(IDC_RAD_UNITMETRIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_RAD_ABSOLUTE)->EnableWindow(FALSE);//坐标
				GetDlgItem(IDC_RAD_INCREMENTAL)->EnableWindow(FALSE);
				GetDlgItem(IDC_RAD_DATAFORMAT)->EnableWindow(FALSE);//数据形式
				GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
				GetDlgItem(IDC_CMB_INTEGERNUM)->EnableWindow(FALSE);//数据格式
				GetDlgItem(IDC_CMB_DECIMALNUM)->EnableWindow(FALSE);
				
				GetDlgItem(IDC_CHK_3FID)->EnableWindow(FALSE);
				
				if(1==GetDoc().GetFZInnerMark())							//方正
				{
					GetDlgItem(IDC_CHK_DRILLDAYINFO)->EnableWindow(TRUE);
					GetDlgItem(IDC_CHK_DRILLTIMEINFO)->EnableWindow(TRUE);
					GetDlgItem(IDC_CHK_DRILLMACHINFO)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_MACHINESN)->EnableWindow(TRUE);
					GetDlgItem(IDC_CHK_DRILLLOTINFO)->EnableWindow(TRUE);
					GetDlgItem(IDC_DRILLSCALE)->EnableWindow(TRUE);
					GetDlgItem(IDC_CHK_DRILLAXISNO)->EnableWindow(TRUE);
					GetDlgItem(IDC_CHK_DRILLSTRINGINFO)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_STRZOOM)->EnableWindow(TRUE);
//					GetDlgItem(IDC_BT_ENTER)->EnableWindow(TRUE);
				}
				else
				{							
					GetDlgItem(IDC_CHK_DRILLDAYINFO)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHK_DRILLTIMEINFO)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHK_DRILLMACHINFO)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_MACHINESN)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHK_DRILLLOTINFO)->EnableWindow(FALSE);
					GetDlgItem(IDC_DRILLSCALE)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHK_DRILLAXISNO)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHK_DRILLSTRINGINFO)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_STRZOOM)->EnableWindow(FALSE);
//					GetDlgItem(IDC_BT_ENTER)->EnableWindow(FALSE);
				}

//				GetDlgItem(IDC_FIXING)->EnableWindow(FALSE);
//				GetDlgItem(IDC_INCREASING)->EnableWindow(FALSE);
//				GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(FALSE);
//				GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(FALSE);

				if(GetDoc().GetEnLOTSn()==1)											//20181225
				{
					GetDlgItem(IDC_FIXING)->EnableWindow(TRUE);
					GetDlgItem(IDC_INCREASING)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(TRUE);				//富士康ID	//20181225
				}
				else
				{
					GetDlgItem(IDC_FIXING)->EnableWindow(FALSE);
					GetDlgItem(IDC_INCREASING)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(FALSE);
				}

				GetDlgItem(IDC_BT_ENTER)->EnableWindow(TRUE);							//20190108
				
				GetDlgItem(IDC_EDT_SCANSIZE)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_NORMALPROC)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_INNERMARK)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_LOCALMARK)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_SALOCALMARK)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_LONGPATH)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_SHORTPATH)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->EnableWindow(FALSE);
				
				GetDlgItem(IDC_EDT_PCBTHICKNESS)->EnableWindow(TRUE);					
			}
			else if(nLevel==SystemDoc::SUPEROR)  //高级
			{
				GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_MIRROR)->EnableWindow(TRUE);		
				GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(TRUE);
//#ifdef CHONGDA
				if(GetDoc().GetCustomerSpecial()==1)
				{
					GetDlgItem(IDC_RAD_UNITINCH)->EnableWindow(FALSE);//单位
					GetDlgItem(IDC_RAD_UNITMETRIC)->EnableWindow(FALSE);	
					GetDlgItem(IDC_RAD_ABSOLUTE)->EnableWindow(FALSE);//坐标
					GetDlgItem(IDC_RAD_INCREMENTAL)->EnableWindow(FALSE);	
					GetDlgItem(IDC_RAD_DATAFORMAT)->EnableWindow(FALSE);//数据形式
					GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
					GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);		
					GetDlgItem(IDC_CMB_INTEGERNUM)->EnableWindow(FALSE);//数据格式
					GetDlgItem(IDC_CMB_DECIMALNUM)->EnableWindow(FALSE);
				}
//#else
				else
				{
					GetDlgItem(IDC_RAD_UNITINCH)->EnableWindow(TRUE);//单位
					GetDlgItem(IDC_RAD_UNITMETRIC)->EnableWindow(TRUE);	
					GetDlgItem(IDC_RAD_ABSOLUTE)->EnableWindow(TRUE);//坐标
					GetDlgItem(IDC_RAD_INCREMENTAL)->EnableWindow(TRUE);	
					GetDlgItem(IDC_RAD_DATAFORMAT)->EnableWindow(TRUE);//数据形式
					GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
					GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);		
					GetDlgItem(IDC_CMB_INTEGERNUM)->EnableWindow(TRUE);//数据格式
					GetDlgItem(IDC_CMB_DECIMALNUM)->EnableWindow(TRUE);	
				}
//#endif
				if (GetDoc().GetShenLan3Fid()!=0)
					GetDlgItem(IDC_CHK_3FID)->EnableWindow(FALSE);
				else
					GetDlgItem(IDC_CHK_3FID)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_CHK_DRILLDAYINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLTIMEINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLMACHINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_MACHINESN)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLLOTINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_DRILLSCALE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLAXISNO)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLSTRINGINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_STRZOOM)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_ENTER)->EnableWindow(TRUE);
				
				if(GetDoc().GetEnLOTSn()==1)
				{
					GetDlgItem(IDC_FIXING)->EnableWindow(TRUE);
					GetDlgItem(IDC_INCREASING)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_FIXING)->EnableWindow(FALSE);
					GetDlgItem(IDC_INCREASING)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(FALSE);
				}
				
				GetDlgItem(IDC_EDT_SCANSIZE)->EnableWindow(TRUE);	
				GetDlgItem(IDC_RADIO_NORMALPROC)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_INNERMARK)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_LOCALMARK)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_SALOCALMARK)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_LONGPATH)->EnableWindow(TRUE);
				if(LSPATH_CHECKING==0)
					GetDlgItem(IDC_RADIO_SHORTPATH)->EnableWindow(FALSE);
				else
					GetDlgItem(IDC_RADIO_SHORTPATH)->EnableWindow(TRUE);
				if(GetDoc().GetFZInnerMark())											//方正
					GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(FALSE);
				else
					GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->EnableWindow(TRUE);

				if(GetDoc().GetFZInnerMark())											//方正
					GetDlgItem(IDC_EDT_PCBTHICKNESS)->EnableWindow(FALSE);
				else
					GetDlgItem(IDC_EDT_PCBTHICKNESS)->EnableWindow(TRUE);
			}
			else if(nLevel==SystemDoc::ADMIN)//系统
			{
				GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_MIRROR)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_RAD_UNITINCH)->EnableWindow(TRUE);//单位
				GetDlgItem(IDC_RAD_UNITMETRIC)->EnableWindow(TRUE);		
				GetDlgItem(IDC_RAD_ABSOLUTE)->EnableWindow(TRUE);//坐标
				GetDlgItem(IDC_RAD_INCREMENTAL)->EnableWindow(TRUE);		
				GetDlgItem(IDC_RAD_DATAFORMAT)->EnableWindow(TRUE);//数据形式
				GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);		
				GetDlgItem(IDC_CMB_INTEGERNUM)->EnableWindow(TRUE);//数据格式
				GetDlgItem(IDC_CMB_DECIMALNUM)->EnableWindow(TRUE);
			
				GetDlgItem(IDC_CHK_3FID)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_CHK_DRILLDAYINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLTIMEINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLMACHINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_MACHINESN)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLLOTINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_DRILLSCALE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLAXISNO)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHK_DRILLSTRINGINFO)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_STRZOOM)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_ENTER)->EnableWindow(TRUE);
				
				if(GetDoc().GetEnLOTSn()==1)
				{
					GetDlgItem(IDC_FIXING)->EnableWindow(TRUE);
					GetDlgItem(IDC_INCREASING)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_FIXING)->EnableWindow(FALSE);
					GetDlgItem(IDC_INCREASING)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(FALSE);
				}
				
				GetDlgItem(IDC_EDT_SCANSIZE)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_NORMALPROC)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_INNERMARK)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_LOCALMARK)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_SALOCALMARK)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_LONGPATH)->EnableWindow(TRUE);
				if(LSPATH_CHECKING==0)
					GetDlgItem(IDC_RADIO_SHORTPATH)->EnableWindow(FALSE);
				else
					GetDlgItem(IDC_RADIO_SHORTPATH)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_EDT_PCBTHICKNESS)->EnableWindow(TRUE);
			}
		}

		if (GetDoc().GetFlowPathMode()==AANDBDOUBLE)				//此模式下不支持文件转存、镜像和旋转
		{
			GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_MIRROR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(FALSE);	
		}
		else
		{
			if(GetDoc().GetIsDoubleFileData())						//20161109 不支持双区域6/8内标靶文件的转存和旋转
			{
				GetDlgItem(IDC_BTN_TRANSSAVE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_ROTATE)->EnableWindow(FALSE);	
			}
		}
	}
	
//	UpdateData(FALSE);
	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CFileInfoSettingView::OnOptimizePath() 
{
	int index;
	char ez[100] = {""};

	strncpy(ez,GetLang().GetWarningText(11014),100);//"正在优化当前文件..."
	m_staticState = _T(ez);
	UpdateData(FALSE);

//	m_btnOptimizePath.EnableWindow(FALSE);								//20180116

	if(!GetDoc().GetIsDoubleFileData())
	{
		GetExcellonData().OptimizePath(GetExcellonData().GetSubArea());
		
		if(GetExcellonData().GetLocalMarkDataCount()>0)
		{
			for(index=0;index<GetExcellonData().GetLocalMarkDataCount();index++)
			{
				GetExcellonData().OptimizePath(GetExcellonData().GetLocalMarkSubArea(index));
			}
			
			GetExcellonData().OptimizePath(GetExcellonData().GetOtherSubArea());
		}
	}
	else//-----------------------------------------------------20161109
	{
		for(int index=0;index<2;index++)
		{
			SetGlobalExcellonIndex(index);
			GetExcellonData().OptimizePath(GetExcellonData().GetSubArea());
			
			if(GetExcellonData().GetLocalMarkDataCount()>0)
			{
				for(index=0;index<GetExcellonData().GetLocalMarkDataCount();index++)
				{
					GetExcellonData().OptimizePath(GetExcellonData().GetLocalMarkSubArea(index));
				}
				
				GetExcellonData().OptimizePath(GetExcellonData().GetOtherSubArea());
			}
		}				
	}
//--------------------------------------------------------------------------

//	m_btnOptimizePath.EnableWindow(TRUE);								//20180116

#ifdef USELOG
	CString strName = GetDoc().GetFileName();
	GetLog().Append_pro(strName,20006);//"路径优化"
#endif

	m_staticState =  "";
	UpdateData(FALSE);
}

void CFileInfoSettingView::OnRadUnitinch() 
{
	this->m_cIntegernum.SetCurSel(1);
	this->m_cDecimalnum.SetCurSel(4);

//	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnRadUnitmetric() 
{
	this->m_cIntegernum.SetCurSel(2);
	this->m_cDecimalnum.SetCurSel(3);

//	m_bFileInfoDataModified=true;	
}

void CFileInfoSettingView::OnChkDrilllotinfo() 
{
	UpdateData();
	
	if(m_chkDrillLotInfo.GetCheck()==1)//LotID加工方式
	{
		GetDlgItem(IDC_FIXING)->EnableWindow(TRUE);
		GetDlgItem(IDC_INCREASING)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(TRUE);						//20181225
	}
	else
	{
		GetDlgItem(IDC_FIXING)->EnableWindow(FALSE);
		GetDlgItem(IDC_INCREASING)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_LOTIDINC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_LOTIDFIX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NOPROCESSID)->EnableWindow(FALSE);
	}

	UpdateWindow();

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC30",szRead,40);//ly add 20111008
	SetDlgItemText(IDC_STATIC30,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_BTN_OPTIMIZEPATH",szRead,40);
	SetDlgItemText(IDC_BTN_OPTIMIZEPATH,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_BTN_TRANSSAVE",szRead,40);
	SetDlgItemText(IDC_BTN_TRANSSAVE,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_BTN_MIRROR",szRead,40);
	SetDlgItemText(IDC_BTN_MIRROR,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_BTN_ROTATE",szRead,40);//ly add 20120831
	SetDlgItemText(IDC_BTN_ROTATE,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_UNITINCH",szRead,40);
	SetDlgItemText(IDC_RAD_UNITINCH,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_UNITMETRIC",szRead,40);
	SetDlgItemText(IDC_RAD_UNITMETRIC,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_ABSOLUTE",szRead,40);
	SetDlgItemText(IDC_RAD_ABSOLUTE,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_INCREMENTAL",szRead,40);
	SetDlgItemText(IDC_RAD_INCREMENTAL,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_DATAFORMAT",szRead,40);
	SetDlgItemText(IDC_RAD_DATAFORMAT,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO7",szRead,40);
	SetDlgItemText(IDC_RADIO7,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO8",szRead,40);
	SetDlgItemText(IDC_RADIO8,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC7",szRead,40);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC9",szRead,40);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC10",szRead,40);
	SetDlgItemText(IDC_STATIC10,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC11",szRead,40);
	SetDlgItemText(IDC_STATIC11,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC12",szRead,40);
	SetDlgItemText(IDC_STATIC12,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC13",szRead,40);
	SetDlgItemText(IDC_STATIC13,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC14",szRead,40);
	SetDlgItemText(IDC_STATIC14,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC15",szRead,40);
	SetDlgItemText(IDC_STATIC15,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_FIXING",szRead,40);//ly change 20121127
	SetDlgItemText(IDC_FIXING,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_INCREASING",szRead,40);//ly change 20121127
	SetDlgItemText(IDC_INCREASING,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_DRILLSCALE",szRead,40);//ly add 20121127
	SetDlgItemText(IDC_DRILLSCALE,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC16",szRead,40);
	SetDlgItemText(IDC_STATIC16,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_BT_ENTER",szRead,40);
	SetDlgItemText(IDC_BT_ENTER,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC17",szRead,40);
	SetDlgItemText(IDC_STATIC17,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC18",szRead,40);
	SetDlgItemText(IDC_STATIC18,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC19",szRead,40);
	SetDlgItemText(IDC_STATIC19,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_NORMALPROC",szRead,40);
	SetDlgItemText(IDC_RADIO_NORMALPROC,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_INNERMARK",szRead,40);
	SetDlgItemText(IDC_RADIO_INNERMARK,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_LOCALMARK",szRead,40);
	SetDlgItemText(IDC_RADIO_LOCALMARK,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_SALOCALMARK",szRead,40);
	SetDlgItemText(IDC_RADIO_SALOCALMARK,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC20",szRead,40);
	SetDlgItemText(IDC_STATIC20,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_SHORTPATH",szRead,40);
	SetDlgItemText(IDC_RADIO_SHORTPATH,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_LONGPATH",szRead,40);
	SetDlgItemText(IDC_RADIO_LONGPATH,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC21",szRead,40);
	SetDlgItemText(IDC_STATIC21,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_MANTHICKNESS",szRead,40);
	SetDlgItemText(IDC_RADIO_MANTHICKNESS,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_AUTOTHICKNESS",szRead,40);
	SetDlgItemText(IDC_RADIO_AUTOTHICKNESS,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC22",szRead,40);
	SetDlgItemText(IDC_STATIC22,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_PROCESSDIR",szRead,40);
	SetDlgItemText(IDC_RAD_PROCESSDIR,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_RAD_PROCESSDIRN",szRead,40);
	SetDlgItemText(IDC_RAD_PROCESSDIRN,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC23",szRead,40);
	SetDlgItemText(IDC_STATIC23,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC24",szRead,40);
	SetDlgItemText(IDC_STATIC24,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC25",szRead,40);
	SetDlgItemText(IDC_STATIC25,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC26",szRead,40);
	SetDlgItemText(IDC_STATIC26,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC27",szRead,40);
	SetDlgItemText(IDC_STATIC27,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC28",szRead,40);
	SetDlgItemText(IDC_STATIC28,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC29",szRead,40);
	SetDlgItemText(IDC_STATIC29,szRead);    
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC31",szRead,40);
	SetDlgItemText(IDC_STATIC31,szRead);
//	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_MANSCALE",szRead,40);
//	SetDlgItemText(IDC_RADIO_MANSCALE,szRead);
//	GetLang().GetUIText("FileInfoSetting","IDC_RADIO_REFSCALE",szRead,40);//ly add 20140504
//	SetDlgItemText(IDC_RADIO_REFSCALE,szRead);

	GetLang().GetUIText("FileInfoSetting","IDC_LOADAVGSCALE",szRead,40);//ly add 20140504
	SetDlgItemText(IDC_LOADAVGSCALE,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_CHECKSCALETHRD",szRead,40);//ly add 20140504
	SetDlgItemText(IDC_CHECKSCALETHRD,szRead);	

	GetLang().GetUIText("FileInfoSetting","IDC_STATIC_SCALE",szRead,40);
	SetDlgItemText(IDC_STATIC_SCALE,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC_SCALE2",szRead,40);
	SetDlgItemText(IDC_STATIC_SCALE2,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_BTN_THICKNESS",szRead,40);
	SetDlgItemText(IDC_BTN_THICKNESS,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC_FILEINFO",szRead,40);
	SetDlgItemText(IDC_STATIC_FILEINFO,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_CHK_3FID",szRead,40);//ly add 20130422
	SetDlgItemText(IDC_CHK_3FID,szRead);	
}

void CFileInfoSettingView::OnInitialUpdate() 
{
//	CRect rect;
//	this->GetWindowRect(rect);

	TVisualFormView::OnInitialUpdate();

//	m_edtLotId.SetParseType(SES_LETTERS | SES_NUMBERS | SES_UNDERSCORE);
	m_edtMachineSn.SetParseType(SES_LETTERS | SES_NUMBERS | SES_UNDERSCORE);
	m_edtScanSize.SetParseType(SES_NUMBERS);
//	m_edtScanSize.SetRange(SCANSIZEMIN,SCANSIZEMAX);

	m_iUnitInch    = GetDoc().GetDataUnit();
	m_iCrdAbsolute = GetDoc().GetCrdMode();
	m_iDateFormat  = GetDoc().GetDataFormat();
	m_iDecimalNum  = GetDoc().GetDecimalNum();
	m_iIntegerNum  = GetDoc().GetIntegerNum()-1;

	m_bDrillMachInfo = GetDoc().GetEnMachSn();
	m_bAxisNo = GetDoc().GetEnAxisNo();
	m_bDrillDayInfo  = GetDoc().GetEnManuDay();
	m_bDrillTimeInfo = GetDoc().GetEnManuTime();
	m_bDrillStrInfo=GetDoc().GetEnManuString();
	m_bDrillLotInfo  = GetDoc().GetEnLOTSn();
	m_bLotIDScale=GetDoc().GetEnLOTScale();
	m_bLotIDFix = GetDoc().GetEnLOTFix();
	m_bLotIDInc = GetDoc().GetEnLOTInc();

	m_strMachineSn = GetDoc().GetMachSn();
	m_strLotIdFix = GetDoc().GetLOTIDFix();
	m_strLotIdInc = GetDoc().GetLOTIDInc();
	m_fStrZoom=GetDoc().GetStrZoomSn();

	m_lScanSize = GetDoc().GetScanSize();

	m_iProcMode=GetDoc().GetProcMode();
    m_iAutoThicking=GetDoc().GetThickingType();
	if(LSPATH_CHECKING==0)
	{
		m_iOpticalPathMode=1;
		GetDoc().SetTechnicType(TRUE);	
	}
	else
		m_iOpticalPathMode=GetDoc().GetTechnicType();

	if(GetDoc().GetSysInfoDBMode()==0)						//20160901
		SetDlgItemText(IDC_BT_SELECTFILE,"打开");
	else
		SetDlgItemText(IDC_BT_SELECTFILE,"载入");

	if(GetLang().GetCurLanguage()==1)
		SetUI();

	m_stState.SetTextColor(TEXT_COLOR);
	m_stFileInfo.SetTextColor(TEXT_COLOR);

	pScaleSetView=new CScaleSetDlgView;						//20160812
	pScaleSetView->Create(IDD_DLG_SCALESET,this);

//	pProcLogin_SN=new CProcLogin_SN;						//20160901
//	pProcLogin_SN->Create(IDD_DLG_PROCLOGIN_SN,this);			

//	if(m_iProcMode)
//	{
//		GetDlgItem(IDC_RADIO_LOCALMARK)->EnableWindow(FALSE);
//		GetDlgItem(IDC_RADIO_SALOCALMARK)->EnableWindow(FALSE);
//	}	

	if (GetDoc().GetUIManSetScale())
	{
		CString str;
		double fScaleX=1.0,fScaleY=1.0;
		GetDoc().GetManSetScaleVal(fScaleX,fScaleY);

		str.Format("%0.6f",fScaleX);
		m_DoubleManScaleX=str;
		str.Format("%0.6f",fScaleY);
		m_DoubleManScaleY=str;

		((CButton*)GetDlgItem(IDC_CHECKMANSCALE))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC29))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC31))->ShowWindow(SW_SHOW);

//		((CButton*)GetDlgItem(IDC_RADIO_MANSCALE))->ShowWindow(SW_SHOW);
//		((CButton*)GetDlgItem(IDC_RADIO_REFSCALE))->ShowWindow(SW_SHOW);
//		((CButton*)GetDlgItem(IDC_RADIO_MANSCALE))->SetCheck(BST_UNCHECKED);
//		((CButton*)GetDlgItem(IDC_RADIO_REFSCALE))->SetCheck(BST_UNCHECKED);

		((CStatic*)GetDlgItem(IDC_STATIC_SCALE))->ShowWindow(SW_SHOW);
		((CEdit*)GetDlgItem(IDC_EDIT_MANSCALEX))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_SCALE2))->ShowWindow(SW_SHOW);
		((CEdit*)GetDlgItem(IDC_EDIT_MANSCALEY))->ShowWindow(SW_SHOW);

		((CButton*)GetDlgItem(IDC_CHECKSCALETHRD))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_LOADAVGSCALE))->ShowWindow(SW_SHOW);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECKMANSCALE))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC29))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC31))->ShowWindow(SW_HIDE);

//		((CButton*)GetDlgItem(IDC_RADIO_MANSCALE))->ShowWindow(SW_HIDE);
//		((CButton*)GetDlgItem(IDC_RADIO_REFSCALE))->ShowWindow(SW_HIDE);

		((CStatic*)GetDlgItem(IDC_STATIC_SCALE))->ShowWindow(SW_HIDE);
		((CEdit*)GetDlgItem(IDC_EDIT_MANSCALEX))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_SCALE2))->ShowWindow(SW_HIDE);
		((CEdit*)GetDlgItem(IDC_EDIT_MANSCALEY))->ShowWindow(SW_HIDE);

		((CButton*)GetDlgItem(IDC_CHECKSCALETHRD))->ShowWindow(SW_HIDE);
		((CButton*)GetDlgItem(IDC_LOADAVGSCALE))->ShowWindow(SW_HIDE);
	}

	UpdateData(false);
}

void CFileInfoSettingView::OnBtEnter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	GetDoc().SetEnMachSn(m_chkDrillMachInfo.GetCheck());
	GetDoc().SetEnManuTime( m_chkDrillTimeInfo.GetCheck() );
	GetDoc().SetEnManuDay( m_chkDrillDayInfo.GetCheck());
	GetDoc().SetEnLOTSn( m_chkDrillLotInfo.GetCheck());
	GetDoc().SetEnManuString( m_chkDrillStringInfo.GetCheck() );
	GetDoc().SetEnLOTFix( m_chkLotIdFix.GetCheck());
	GetDoc().SetEnLOTInc( m_chkLotIdInc.GetCheck());
	GetDoc().SetEnLOTScale( m_chkLotIdScale.GetCheck());
	GetDoc().SetEnAxisNo( m_chkAxisNo.GetCheck());

	GetDoc().SetMachSn(m_strMachineSn);	
	GetDoc().SetLOTIDFix(m_strLotIdFix);
	GetDoc().SetLOTIDInc(m_strLotIdInc);
	GetDoc().SetStrZoomSn(m_fStrZoom);
	GetDoc().SetNoProcessID(m_EditNoProcess);
	
	GetDoc().SetIsRecordPowerPara(1);
}

void CFileInfoSettingView::OnBtnMirror() 
{
	char ez[256]={""};

	if(GetExcellonData().GetSubAreaCnt()>0)
	{		
		if(!GetDoc().GetMirrorFlag())
		{
			CRD length=-1;	
			CRD Min=0;

			Coord crdDest;
			CRD MinX = 99999999,MinY = 99999999;
			
			if(!GetDoc().GetIsDoubleFileData())
			{
				GetExcellonData().MirrorY(length,Min);
				
				for(int k=0; k<GetExcellonData().GetSubAreaCnt(); k++)
				{
					if(!GetExcellonData().GetSubAreaIsEmpty(k)) 
					{
						crdDest = GetExcellonData().GetSubAreaCenter(k);
						
						if(MinX > crdDest.x)
							MinX = crdDest.x;
						if(MinY > crdDest.y)
							MinY = crdDest.y;
					}
				}
			}
			else//-----------------------------------------------------20161109
			{
				for(int index=0;index<2;index++)
				{
					SetGlobalExcellonIndex(index);
					GetExcellonData().MirrorY(length,Min);
					
					for(int l=0; l<GetExcellonData().GetSubAreaCnt(); l++)
					{
						if(!GetExcellonData().GetSubAreaIsEmpty(l)) 
						{
							crdDest = GetExcellonData().GetSubAreaCenter(l);
							
							if(MinX > crdDest.x)
								MinX = crdDest.x;
							if(MinY > crdDest.y)
								MinY = crdDest.y;
						}
					}
				}				
			}
//--------------------------------------------------------------------------
			MinX-=GetDoc().GetScanSize()*1000;
			MinY-=GetDoc().GetScanSize()*1000;
			GetDoc().SetLBRefPoint(Coord(MinX,MinY));

			GetDoc().SetMirrorFlag(true);
			GetDoc().SetIsFiducialDo(false);

			strncpy(ez ,GetLang().GetWarningText(10006),20);
			m_btnMirror.SetWindowText(ez);//"已镜像"
		}
		else
		{
			strncpy(ez,GetLang().GetWarningText(11015),256);
			MessageBox(ez);//"文件已镜像!"
		}		
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(11016),256);
		MessageBox(ez);//"请先导入数据!"
	}	
}

void CFileInfoSettingView::OnBtnRotate()
{
	char ez[256]={""};

	if(GetExcellonData().GetSubAreaCnt()>0)
	{		
		if(GetDoc().GetRotateFlag()<0)
		{				
			CDlgRotate RotateDlg;
			if(RotateDlg.DoModal()!=IDOK )	
				return;

			if(GetDoc().GetRotateFlag()==0)
				GetExcellonData().Rotate90();
			else if(GetDoc().GetRotateFlag()==1)
				GetExcellonData().Rotate180();
			else if(GetDoc().GetRotateFlag()==2)
				GetExcellonData().Rotate270();

			Coord crdDest;
			CRD MinX = 99999999,MinY = 99999999;
			
			for(int k=0; k<GetExcellonData().GetSubAreaCnt(); k++)
			{
				if(!GetExcellonData().GetSubAreaIsEmpty(k)) 
				{
					crdDest = GetExcellonData().GetSubAreaCenter(k);
					
					if(MinX > crdDest.x)
						MinX = crdDest.x;
					if(MinY > crdDest.y)
						MinY = crdDest.y;
				}
			}

			MinX-=GetDoc().GetScanSize()*1000;
			MinY-=GetDoc().GetScanSize()*1000;
			GetDoc().SetLBRefPoint(Coord(MinX,MinY));

			GetDoc().SetIsFiducialDo(false);
				
			strncpy(ez ,GetLang().GetWarningText(10018),20);
			m_btnRotate.SetWindowText(ez);//"已旋转"
		}
		else
		{
			strncpy(ez,GetLang().GetWarningText(10018),256);
			MessageBox(ez);//"文件已旋转!"
		}		
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(11016),256);
		MessageBox(ez);//"请先导入数据!"
	}
}


void CFileInfoSettingView::OnBtnRotate(int angle)
{
	char ez[256]={""};

	if(GetExcellonData().GetSubAreaCnt()>0)
	{		
		if(GetDoc().GetRotateFlag()<0)
		{				

			if(angle == 0)
				GetExcellonData().Rotate90();
			else if(angle == 1)
				GetExcellonData().Rotate180();
			else if(angle == 2)
				GetExcellonData().Rotate270();

			Coord crdDest;
			CRD MinX = 99999999,MinY = 99999999;
			
			for(int k=0; k<GetExcellonData().GetSubAreaCnt(); k++)
			{
				if(!GetExcellonData().GetSubAreaIsEmpty(k)) 
				{
					crdDest = GetExcellonData().GetSubAreaCenter(k);
					
					if(MinX > crdDest.x)
						MinX = crdDest.x;
					if(MinY > crdDest.y)
						MinY = crdDest.y;
				}
			}

			MinX-=GetDoc().GetScanSize()*1000;
			MinY-=GetDoc().GetScanSize()*1000;
			GetDoc().SetLBRefPoint(Coord(MinX,MinY));

			GetDoc().SetIsFiducialDo(false);
				
			strncpy(ez ,GetLang().GetWarningText(10018),20);
			m_btnRotate.SetWindowText(ez);//"已旋转"
		
		}
		else
		{
			strncpy(ez,GetLang().GetWarningText(10018),256);
			//MessageBox(ez);//"文件已旋转!"
		}		
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(11016),256);
		MessageBox(ez);//"请先导入数据!"
	}
}

void CFileInfoSettingView::DealLotIdFixAndInc()
{
	//处理固定号流水号
	CString lotIdFixStr = GetDoc().GetLOTIDFix();
	CString	lotIdIncStr = GetDoc().GetLOTIDInc();
	if (lotIdFixStr != "" && lotIdIncStr != "")
	{
		m_chkDrillLotInfo.SetCheck(1);
		m_chkLotIdFix.SetCheck(1);
		m_chkLotIdInc.SetCheck(1);
		GetDoc().SetEnLOTSn(TRUE);
	}
	else if (lotIdFixStr != "" && lotIdIncStr == "")
	{
		m_chkDrillLotInfo.SetCheck(1);
		m_chkLotIdFix.SetCheck(1);
		m_chkLotIdInc.SetCheck(0);
		GetDoc().SetEnLOTSn(TRUE);
	}
	else if (lotIdFixStr == "" && lotIdIncStr != "")
	{
		m_chkDrillLotInfo.SetCheck(1);
		m_chkLotIdFix.SetCheck(0);
		m_chkLotIdInc.SetCheck(1);
		GetDoc().SetEnLOTSn(TRUE);
	}
	else
	{
		m_chkDrillLotInfo.SetCheck(0);
		m_chkLotIdFix.SetCheck(0);
		m_chkLotIdInc.SetCheck(0);
		GetDoc().SetEnLOTSn(FALSE);
	}
	OnChkDrilllotinfo();
	m_strLotIdFix = lotIdFixStr;
	m_strLotIdInc = lotIdIncStr;
	UpdateData(FALSE);
}

void CFileInfoSettingView::OnRadioShortpath() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};
	time_t start_time, end_time;

	m_iOpticalPathMode=0;
	
	GetControl().ChannelOutput(OLASERSHUTTER1,MIO_OFF);
	
	start_time = time( NULL );
	while(LSPATH_CHECKING &&( GetControl().QueryIOBit(ILASERSHUTTERLTN)||GetControl().QueryIOBit(ILASERSHUTTERRTN)))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
#ifndef LESSWARN
			strncpy(ez,GetLang().GetWarningText(41001),256);
			AfxMessageBox(ez);//"未能切换到短光路，请检查!"
#endif
#ifdef USELOG
			GetLog().Append_pro(10006,20008);//"未能切换到短光路!","光路切换"
#endif
			return ;
		}
	}

	GetDoc().SetTechnicType(FALSE);

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnRadioLongpath() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};
	time_t start_time, end_time;

	m_iOpticalPathMode=1;
	
	GetControl().ChannelOutput(OLASERSHUTTER1,MIO_ON);
	
	start_time = time( NULL );
	while(LSPATH_CHECKING &&( GetControl().QueryIOBit(ILASERSHUTTERLTP)||GetControl().QueryIOBit(ILASERSHUTTERRTP)))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
#ifndef LESSWARN
			strncpy(ez,GetLang().GetWarningText(41002),256);
			AfxMessageBox(ez);//"未能切换到长光路，请检查!"
#endif
#ifdef USELOG
			GetLog().Append_pro(10007,20008);//"未能切换到长光路!","光路切换"
#endif
			return ;
		}
	}

	GetDoc().SetTechnicType(TRUE);

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnRadioManthickness() 
{
	if (!GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->IsWindowEnabled() && m_iAutoThicking==1 )
	{
		GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->EnableWindow(TRUE);
		UpdateData(FALSE);
		m_iAutoThicking = 0;
		GetDoc().SetThickingType(FALSE);
		GetDlgItem(IDC_RADIO_AUTOTHICKNESS)->EnableWindow(FALSE);
		UpdateData(FALSE);
	}
	else
	{
		m_iAutoThicking = 0;
		GetDoc().SetThickingType(FALSE);	
	}

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnRadioAutothickness() 
{
	if (!GetDlgItem(IDC_RADIO_MANTHICKNESS)->IsWindowEnabled() && m_iAutoThicking==0 )
	{
		GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(TRUE);
		UpdateData(FALSE);
		m_iAutoThicking = 1;
		GetDoc().SetThickingType(TRUE);	
		GetDlgItem(IDC_RADIO_MANTHICKNESS)->EnableWindow(FALSE);
		UpdateData(FALSE);
	}
	else
	{		
		m_iAutoThicking = 1;
		GetDoc().SetThickingType(TRUE);	
	}

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnBtnSetThickness() 
{
	char ez[256]={""};

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
		AfxMessageBox(ez);
		return;		
	}

	UpdateData();

//设定板厚值
	GetDoc().SetPCBThickness(m_ulPCBThickness);	
	GetDoc().SetPCBThicknessStd(m_ulPCBThickness);

//保存板厚信息到文件中
	CIniFile IniFile;
	char buf[MaxPathLen];
	CString strName = GetDoc().GetFileName();

	strName =strName.Left(strName.ReverseFind('.'));
	sprintf(buf,"%s",strName);
	IniFile.SetName(buf);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		IniFile.WriteSection("PCBThickness");
		IniFile.WriteItemInt("Thickness", m_ulPCBThickness);

		IniFile.CloseIniFile();
	}

	Delay(200);

//设定手工涨缩值
	if(GetDoc().GetUIManSetScale())
	{
		CString str;

		double fScaleX = atof(m_DoubleManScaleX);
		if (GetDoc().GetDrillInc())
			fScaleX = fScaleX/10000.0+1;

		double fScaleY = atof(m_DoubleManScaleY);		
		if (GetDoc().GetDrillInc())
			fScaleY = fScaleY/10000.0+1;		

		if(!GetDoc().InputManSetScaleVal(fScaleX,fScaleY))		//设定手工涨缩值，如果设定值超出，则恢复为原有值
		{
			strncpy(ez,GetLang().GetWarningText(13001),256);
			AfxMessageBox(ez);//"涨缩值范围0.92 - 1.08"

			GetDoc().GetManSetScaleVal(fScaleX,fScaleY);

			str.Format("%0.6f",fScaleX);
			m_DoubleManScaleX=str;
			str.Format("%0.6f",fScaleY);
			m_DoubleManScaleY=str;

			UpdateData(false);

			return;
		}

#ifdef USELOG
		GetLog().Append_pro("ManualScaleX","PCBScale",m_DoubleManScaleX);
		GetLog().Append_pro("ManualScaleY","PCBScale",m_DoubleManScaleY);
#endif 
	}
	if (GetDoc().GetSysModeSwitch())//在线模式
	{
		return;
	}
	AfxMessageBox("参数已设定并保存！");
}

void CFileInfoSettingView::ReadPCBThickness()
{
	char buf[MaxPathLen];
	char ez[256]={""};
	CString strName = GetDoc().GetFileName();
	m_ulPCBThickness = GetDoc().GetPCBThickness();

	UpdateData(false);
}

void CFileInfoSettingView::OnRadioNormalproc() 
{
	// TODO: Add your control notification handler code here
//	m_iFileMode = 0;
//	GetDoc().SetFileMode(SystemDoc::NORMALPROC);

	if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)			//20160818
	{
		m_iFileMode = 0;
		GetDoc().SetFileMode(SystemDoc::NORMALPROC);
	}

	if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(GetExcellonData().GetInnerFiducialNum()==4))
	{
		m_iFileMode = 0;
		GetDoc().SetFileMode(SystemDoc::NORMALPROC);
	}

	UpdateData(false);
}

void CFileInfoSettingView::OnRadioInnermark() 
{
	// TODO: Add your control notification handler code here
	if(GetExcellonData().GetInnerFiducialNum()==2&&(GetExcellonData().GetInnerFiducialPos(0)!=GetExcellonData().GetInnerFiducialPos(1)))
	{
		m_iFileMode = 1;
		GetDoc().SetFileMode(SystemDoc::INNERMARK);
	}
	else
		m_iFileMode = 0;

	UpdateData(false);
}

void CFileInfoSettingView::OnRadioLocalmark() 
{
	// TODO: Add your control notification handler code here
	if(GetExcellonData().GetLocalMarkNum()>0)
	{
		m_iFileMode = 2;
		GetDoc().SetFileMode(SystemDoc::LOCALMARKM02);	
	}
	else
		m_iFileMode = 0;

	UpdateData(false);
}

void CFileInfoSettingView::OnRadioSalocalmark() 
{
	// TODO: Add your control notification handler code here
	if(GetExcellonData().GetSALocalMarkDataCount()>0)
	{
		m_iFileMode = 3;
		GetDoc().SetFileMode(SystemDoc::LOCALMARKSA);	
	}
	else
		m_iFileMode = 0;

	UpdateData(false);	
}

void CFileInfoSettingView::OnBtnTranssave() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11017),256);
		MessageBox(ez);//"未打开数据文件，无法转存！"
		return;
	}

	strncpy(ez,GetLang().GetWarningText(11018),256);									//20180116
	int nSel = AfxMessageBox(ez,MB_YESNO);//"请确认是否进行了优化!\n是否继续进行转存?"
	if(nSel == IDYES )
	{
		if(!GetDoc().GetFileIsOptimized())
		{
			OnOptimizePath();
			Delay(500);
			
			strncpy(ez,GetLang().GetWarningText(11019),256);// "正在转存当前文件..."
			m_staticState = _T(ez);
			m_btnTransSave.EnableWindow(FALSE);
			
			UpdateData(FALSE);
			
			char buf[MaxPathLen];
			CString strName;
			FILE* fp;
			
			strName = GetDoc().GetFileName();
			strName =strName.Left(strName.ReverseFind('.'));
			sprintf(buf,"%s.sa",strName);
			
			DeleteFile(buf);
			
			if(!(fp= fopen(buf,"a+")))
			{
				strncpy(ez,GetLang().GetWarningText(11020),256);
				MessageBox(ez);//"文件操作失败！"
				return;
			}
			
			GetExcellonData().SADataTransSave(fp,GetDoc().GetScanSize(),GetDoc().GetSLBitPerMM());
			
			fclose(fp);
			
			char szRead[20] = {""};
			strncpy(szRead ,GetLang().GetWarningText(10005),20);
			m_btnTransSave.SetWindowText(szRead);//"已转存"
			m_staticState =  "";
			m_btnTransSave.EnableWindow(TRUE);
			
			UpdateData(FALSE);
			
			GetDoc().SetFileIsOptimized(true);								//20180116
		}
	}
}

void CFileInfoSettingView::OnDrillscale() //ly add 20121127
{
	if((!GetDoc().GetEnLOTScale())&&(2==GetDoc().GetShenLan3Fid()))			//20160812
		pScaleSetView->ShowWindow(SW_SHOW);

	m_bFileInfoDataModified=true;
}

void CFileInfoSettingView::OnChk3fid()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetEn3Fid(m_b3Fid);
}
/*
void CFileInfoSettingView::OnLoadavgscale() //ly add 20140702
{
	// TODO: Add your control notification handler code here
	CString str;
	double showScale=0;

	if (GetDoc().GetDrillInc())
	{//为了与日志记录中的现实一致 20150415
		showScale=((GetDoc().GetLAvgScaleX()+GetDoc().GetRAvgScaleX())/2.0-1.0)*10000;
		str.Format("%0.6f",showScale);

		if (abs(showScale)<10000)
          m_DoubleManScaleX=str;

        showScale=((GetDoc().GetLAvgScaleY()+GetDoc().GetRAvgScaleY())/2.0-1.0)*10000;
		str.Format("%0.6f",showScale);

	    if (abs(showScale)<10000)
		 m_DoubleManScaleY=str;
	}
	else
	{
		showScale=(GetDoc().GetLAvgScaleX()+GetDoc().GetRAvgScaleX())/2.0;
		str.Format("%0.6f",showScale);

		if (abs(showScale)<2)
		m_DoubleManScaleX=str;

		showScale=(GetDoc().GetLAvgScaleY()+GetDoc().GetRAvgScaleY())/2.0;
		str.Format("%0.6f",showScale);

		if (abs(showScale)<2)
		 m_DoubleManScaleY=str;
	}

	UpdateData(false);

	OnBtnSetThickness();
}
*/
void CFileInfoSettingView::OnLoadavgscale()					//20191219 修改
{
	// TODO: Add your control notification handler code here
	CString str;
	double showScale=0;

	double dbLAvgScaleX=GetDoc().GetLAvgScaleX();
	double dbLAvgScaleY=GetDoc().GetLAvgScaleY();
	double dbRAvgScaleX=GetDoc().GetRAvgScaleX();
	double dbRAvgScaleY=GetDoc().GetRAvgScaleY();

	if(GetDoc().GetProcAxisMode()==1)
	{
		dbRAvgScaleX=dbLAvgScaleX;
		dbRAvgScaleY=dbLAvgScaleY;
	}

	if(GetDoc().GetProcAxisMode()==2)
	{
		dbLAvgScaleX=dbRAvgScaleX;
		dbLAvgScaleY=dbRAvgScaleY;
	}

	if (GetDoc().GetDrillInc())								//为了与日志记录中的现实一致
	{
		showScale=((dbLAvgScaleX+dbRAvgScaleX)/2.0-1.0)*10000;
		str.Format("%0.6f",showScale);

		if (abs(showScale)<10000)
          m_DoubleManScaleX=str;

        showScale=((dbLAvgScaleY+dbRAvgScaleY)/2.0-1.0)*10000;
		str.Format("%0.6f",showScale);

	    if (abs(showScale)<10000)
		 m_DoubleManScaleY=str;
	}
	else
	{
		showScale=(dbLAvgScaleX+dbRAvgScaleX)/2.0;
		str.Format("%0.6f",showScale);

		if (abs(showScale)<2)
		m_DoubleManScaleX=str;

		showScale=(dbLAvgScaleY+dbRAvgScaleY)/2.0;
		str.Format("%0.6f",showScale);

		if (abs(showScale)<2)
		 m_DoubleManScaleY=str;
	}

	UpdateData(false);

	OnBtnSetThickness();
}

void CFileInfoSettingView::OnCheckscalethrd() //ly add 20140702
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetCheckManulScaleRange(m_bCheckManulScaleRange);
}

void CFileInfoSettingView::OnCheckmanscale() 
{
	UpdateData();
	GetDoc().SetCheckManScale(m_Check_ManuScale.GetCheck());	
}

BOOL CFileInfoSettingView::OpenDataFile(CString& strFileName,BOOL bIsOnlySA)
{
	static char szFilter[] = "Drill Files (*.*)|*.*||";
    CFileDialog FileDlg(true,NULL,NULL,OFN_HIDEREADONLY,szFilter,NULL);	
	char ez[256]={""};
//初始化
	m_btnOptimizePath.EnableWindow(TRUE);	
	m_btnTransSave.EnableWindow(TRUE);

	m_edtScanSize.EnableWindow(TRUE);

	char szRead[20] = {""};
	strncpy(szRead ,GetLang().GetWarningText(10001),20);
	m_btnOptimizePath.SetWindowText(szRead);//"优化"
	strncpy(szRead ,GetLang().GetWarningText(10003),20);
	m_btnMirror.SetWindowText(szRead);//"镜像"
	strncpy(szRead ,GetLang().GetWarningText(10002),20);
	m_btnTransSave.SetWindowText(szRead);//"转存"
	strncpy(szRead ,GetLang().GetWarningText(10017),20);//ly add 20120831
	m_btnRotate.SetWindowText(szRead);//"旋转"

	SetGlobalExcellonIndex(0);									//20161109	第一步：清空钻孔数据（钻孔文件数据和分区数据）		
	GetExcellonData().ClearAll();
	SetGlobalExcellonIndex(1);			
	GetExcellonData().ClearAll();
	GetDoc().ClearTools();										//清除“加工用”刀具参数
	GetToolView().ToolParaClear();								//清除“显示用”刀具参数
	GetPointcontrlView().ToolInforClear();
	
	CString	str="";
	GetDoc().SetFileName(str);
	GetDoc().SetToolFileName(str);

	GetDoc().SetMirrorFlag(false);
	GetDoc().SetRotateFlag(-1);
	GetDoc().SetFileOpenState(false);
//	GetDoc().SetIsFiducialDo(false);

	GetDoc().SetCurPCBHoleCount(0);
//	GetDoc().SetCurPCBDrilledHoleCount(0);
//	GetDoc().SetCurPCBDrilledArea(0);
	GetDoc().SetProcedPCBNum(0);								//20170628 20180613追加
	GetDoc().SetLNum(0);										//20181207
	GetDoc().SetRNum(0);

	m_ulPCBThickness=1000;
//	GetDoc().SetPCBThickness(m_ulPCBThickness);
//	GetDoc().SetPCBThicknessStd(m_ulPCBThickness);
	
	UpdateData();
/////////////////////////////////////////////////////////////	
	bool rtn=false;								//20160901
	bool bSilent=false;

	if(strFileName=="")												//20161123
	{
		rtn=FileDlg.DoModal();
		if(rtn)
			str = FileDlg.GetPathName();
	}
	else
	{
		rtn=true;
		str = strFileName;

		if (GetDoc().GetFlowPathMode()==AANDBDOUBLE)
			bSilent=true;
	}


/////////////////////////////////////////////////////////////
//	if(FileDlg.DoModal())
	if(rtn)
	{
//		str = FileDlg.GetPathName();	
		if(str!="")
		{
			CString strName =str.Mid(str.ReverseFind('.')+1);

			SetDlgItemText(IDC_EDT_SELECTFILE,str);

			if(bIsOnlySA&&(strName!="sa"))								//20161123
			{
				AfxMessageBox("数据文件不是SA格式，无法导入!");
				return false;
			}
			
			if(strName=="sa") 
			{
				if (GetDoc().GetSysModeSwitch())//在线模式
				{
					CString key,item_value;
					for(int k=0;k<m_barcodeStructVet.size();k++)
					{
						key.Format("%s",m_barcodeStructVet[k].keyName.c_str());
						item_value.Format("%s",m_barcodeStructVet[k].keyValue.c_str());
						if (key == "LOT_QTY")
						{
							GetDoc().SetSysPCBCount(atoi(item_value));		
						}
						if (key == "PROD_ID")
						{
							GetDoc().SetSysProcPRODID(item_value);
						}
						if (key == "S107")
						{
							GetDoc().SetProcMode(SystemDoc::PROCMODE(atoi(item_value)));
						}
						if (key == "S050")
						{
							GetDoc().SetPCBThickness(atof(item_value)*1000);	
							GetDoc().SetPCBThicknessStd(atof(item_value)*1000);
						}
					}
				}

				strncpy(ez,GetLang().GetWarningText(11005),256);//"正在导入转存文件..."
				m_staticState = _T(ez);
				UpdateData(FALSE);
				
				
				GetDoc().SetIsDoubleFileData(false);								//20161122
				
				if(GetDecodeSA().DecodeSAFile(str))
				{
					SetGlobalExcellonIndex(0);													
					GetExcellonData().ClearAll();
					SetGlobalExcellonIndex(1);			
					GetExcellonData().ClearAll();
					
					strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
					m_staticState = _T(ez);
					UpdateData(FALSE);
					strncpy(ez,GetLang().GetWarningText(11004),256);
					AfxMessageBox(ez);//"文件格式不正确!"
					return false;
				}
				
				if(GetGlobalExcellonIndex()==1)										//20161122
					GetDoc().SetIsDoubleFileData(true);
					/*																					//20180911
					if(GetDoc().GetFitBit()&&(GetExcellonData().GetGlvScanBit()!=GetDoc().GetSLBitPerMM()))
					{
					if(GetExcellonData().GetGlvScanBit()==0)
					{
					strncpy(ez,GetLang().GetWarningText(11026),256);//"sa文件没有比特率数据，请确定是否与机器当前比特率一致？"
					int nSel = AfxMessageBox(ez,MB_YESNO);
					if(nSel== IDYES)
					{
					char buf[MaxPathLen];
					FILE* fp;
					sprintf(buf,"%s",str);
					
					  DeleteFile(buf);
					  
						if(!(fp= fopen(buf,"a+")))
						{
						GetExcellonData().ClearAll();
						UpdateData(FALSE);
						strncpy(ez,GetLang().GetWarningText(11020),256);
						MessageBox(ez);//"文件操作失败！"
						return false;
						}
						
						  GetExcellonData().SADataTransSave(fp,GetExcellonData().GetGlvScanSize(),GetDoc().GetSLBitPerMM());
						  
							fclose(fp);
							}
							else
							{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(11027),256);//"文件比特率和设备不符，请导入原始文件重新转化！"
							AfxMessageBox(ez);
							return false;
							}	
							}
							else
							{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(11027),256);//"文件比特率和设备不符，请导入原始文件重新转化！"
							AfxMessageBox(ez);
							return false;
							}
							}
				*/				
				if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
				{
					if(GetExcellonData().GetFiducialNum()<3||GetExcellonData().GetFiducialNum()>4)
					{
						GetExcellonData().ClearAll();
						strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						strncpy(ez,GetLang().GetWarningText(22006),256);
						AfxMessageBox(ez);//"在内层主标靶工艺方式下外层标靶数量不正确!"
						return false;
					}
					//					if(GetExcellonData().GetInnerFiducialNum()!=4)
					if((GetExcellonData().GetInnerFiducialNum()!=4)&&(GetExcellonData().GetInnerFiducialNum()!=6))
					{
						GetExcellonData().ClearAll();
						strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						strncpy(ez,GetLang().GetWarningText(22007),256);
						AfxMessageBox(ez);//"在内层主标靶工艺方式下内层标靶数量不正确!"
						return false;
					}
				}
				
				if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
				{
					if(GetExcellonData().GetFiducialNum()!=4)
					{
						GetExcellonData().ClearAll();
						strncpy(ez,GetLang().GetWarningText(11006),256);// "导入转存文件失败！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						strncpy(ez,GetLang().GetWarningText(22008),256);
						AfxMessageBox(ez);//"在外层主标靶工艺方式下外层标靶数量不正确!"
						return false;
					}
					
					if(GetExcellonData().GetInnerFiducialNum()>0)
					{
						if(GetExcellonData().GetInnerFiducialNum()!=2)
						{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22009),256);
							AfxMessageBox(ez);//"在外层主标靶工艺方式下内部标靶数量不正确!"
							return false;
						}
					}
					
					if(GetExcellonData().GetLocalMarkNum()>0)
					{
						if(GetExcellonData().GetLocalMarkNum()!=4)
						{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11006),256);//"导入转存文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22010),256);
							AfxMessageBox(ez);//"在M02内部标靶工艺方式下局部标靶数量不正确!"
							return false;
						}
					}
					if(GetExcellonData().GetSALocalMarkDataCount()>0)
					{
						if(!GetExcellonData().SortSALocalMarkData())
						{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11006),256);// "导入转存文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22011),256);
							AfxMessageBox(ez);//"在分区内部标靶工艺方式下局部标靶数量不正确!"
							return false;
						}
					}
				}
				
				long StartX,StartY,EndX,EndY;				
				StartX=GetExcellonData().GetLayerStartX();
				StartY=GetExcellonData().GetLayerStartY();
				EndX=GetExcellonData().GetLayerEndX();
				EndY=GetExcellonData().GetLayerEndY();
				for(int n=0;n<GetExcellonData().GetSubAreaCnt();n++)
				{
					Coord crd;
					crd= GetExcellonData().GetSubAreaCenter(n);
					
					if(crd.x<StartX)
						StartX = crd.x;
					if(crd.y<StartY)
						StartY = crd.y;
					
					if(crd.x>EndX)
						EndX = crd.x;
					if(crd.y>EndY)
						EndY = crd.y;
				}
				GetExcellonData().SetLayerStartX(StartX-GetDoc().GetScanSize()*500+1);
				GetExcellonData().SetLayerStartY(StartY-GetDoc().GetScanSize()*500+1);
				GetExcellonData().SetLayerEndX(EndX+GetDoc().GetScanSize()*500-1);
				GetExcellonData().SetLayerEndY(EndY+GetDoc().GetScanSize()*500-1);//ly add 20140318
				
				strncpy(ez,GetLang().GetWarningText(11007),256);//"导入转存文件完成！"
				m_staticState = _T(ez);
				
				m_lScanSize =GetExcellonData().GetGlvScanSize();
				GetDoc().SetScanSize(m_lScanSize);
				
				m_edtScanSize.EnableWindow(FALSE);
				m_btnOptimizePath.EnableWindow(FALSE);	
				m_btnTransSave.EnableWindow(FALSE);
				char szRead[20] = {""};
				strncpy(szRead ,GetLang().GetWarningText(10001),20);
				m_btnOptimizePath.SetWindowText(szRead);//"优化"
				strncpy(szRead ,GetLang().GetWarningText(10003),20);
				m_btnMirror.SetWindowText(szRead);//"镜像"
				strncpy(szRead ,GetLang().GetWarningText(10002),20);
				m_btnTransSave.SetWindowText(szRead);//"转存"
				strncpy(szRead ,GetLang().GetWarningText(10017),20);//ly add 20120831
				m_btnRotate.SetWindowText(szRead);//"旋转"
				UpdateData(FALSE);	
				
				strFileName=str;
				
				GetDoc().SetFileIsOptimized(true);								//20180116
			}
			else
			{
				strncpy(ez,GetLang().GetWarningText(11008),256);//"正在导入原始文件..."
				m_staticState = _T(ez);
				UpdateData(FALSE);
				
				//				UpdateData();
				
				GetDoc().SetDataUnit(m_iUnitInch);
				GetDoc().SetCrdMode(m_iCrdAbsolute);
				GetDoc().SetDataFormat((DecodeExcellon::XYDateFormat)m_iDateFormat);
				GetDoc().SetDecimalNum(m_iDecimalNum);
				GetDoc().SetIntegerNum(m_iIntegerNum+1);
				
				GetDoc().SaveProcessParam();										//20180822增加
				
				GetDecodeExcellon().SetDataUnit(m_iUnitInch);
				GetDecodeExcellon().SetCrdMode(m_iCrdAbsolute);
				GetDecodeExcellon().SetDataFormat((DecodeExcellon::XYDateFormat)m_iDateFormat);
				GetDecodeExcellon().SetDecimalNum(m_iDecimalNum);
				GetDecodeExcellon().SetIntegerNum(m_iIntegerNum+1);
				
				GetDoc().SetIsDoubleFileData(false);								//20161109
				
				if(GetDecodeExcellon().DecodeFile(str))								//20161109	第二步：解析钻孔数据
				{
					SetGlobalExcellonIndex(0);													
					GetExcellonData().ClearAll();
					SetGlobalExcellonIndex(1);			
					GetExcellonData().ClearAll();
					
					strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
					m_staticState = _T(ez);
					UpdateData(FALSE);
					strncpy(ez,GetLang().GetWarningText(11004),256);
					AfxMessageBox(ez);//"文件格式不正确!"
					return false;
				}
				
				if(GetGlobalExcellonIndex()==1)										//20161109
					GetDoc().SetIsDoubleFileData(true);
				
				if(!GetDoc().GetIsDoubleFileData())
				{
					if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)			//内层主标靶方式下，外靶允许3或4个，内靶允许4个
					{
						if(GetExcellonData().GetFiducialNum()<3||GetExcellonData().GetFiducialNum()>4)
						{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22006),256);
							AfxMessageBox(ez);//"在内层主标靶工艺方式下外层标靶数量不正确!"
							return false;
						}
						
						if(GetExcellonData().GetInnerFiducialNum()!=4)
						{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22007),256);
							AfxMessageBox(ez);//"在内层主标靶工艺方式下内层标靶数量不正确!"
							return false;
						}
					}
					
					if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)			//外层主标靶方式下，外靶允许4个，内靶允许2个
					{
						if(GetExcellonData().GetFiducialNum()!=4)
						{
							GetExcellonData().ClearAll();
							strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22008),256);
							AfxMessageBox(ez);//"在外层主标靶工艺方式下外层标靶数量不正确!"
							return false; 
						}
						
						if(GetExcellonData().GetInnerFiducialNum()>0)
						{
							if(GetExcellonData().GetInnerFiducialNum()!=2)
							{
								GetExcellonData().ClearAll();
								strncpy(ez,GetLang().GetWarningText(11009),256);// "导入原始文件失败！"
								m_staticState = _T(ez);
								UpdateData(FALSE);
								strncpy(ez,GetLang().GetWarningText(22009),256);
								AfxMessageBox(ez);//"在6标靶工艺方式下内层标靶数量不正确!"
								return false;
							}
						}
						
						if(GetExcellonData().GetLocalMarkNum()>0)
						{
							if(GetExcellonData().GetLocalMarkNum()!=4)
							{
								GetExcellonData().ClearAll();
								strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
								m_staticState = _T(ez);
								UpdateData(FALSE);
								strncpy(ez,GetLang().GetWarningText(22010),256);
								AfxMessageBox(ez);//"在M02内部标靶工艺方式下局部标靶数量不正确!"
								return false;
							}
						}
					}
					
					if(!GetExcellonData().MakeAssistantData())
					{
						GetExcellonData().ClearAll();
						strncpy(ez,GetLang().GetWarningText(11011),256);//"数据生成失败！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						return false;				
					}
					
					GetExcellonData().CheckFileRange();//ly add 20131225
					
					if(!GetDoc().DistributeSubarea())
					{				
						GetExcellonData().ClearAll();
						strncpy(ez,GetLang().GetWarningText(11012),256);//"数据宽度或高度超出范围！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						return false;
					}
				}
				else//--------------------------------------------------------------------------//20161109
				{
					if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
					{
						SetGlobalExcellonIndex(0);
						GetExcellonData().ClearAll();
						SetGlobalExcellonIndex(1);
						GetExcellonData().ClearAll();
						
						AfxMessageBox("双区域加工文件不支持外层主标靶工艺方式，请重新选择标靶方式!");
						return false;
					}
					
					SetGlobalExcellonIndex(0);
					if(GetExcellonData().GetFiducialNum()<3||GetExcellonData().GetFiducialNum()>4)	//双区域加工文件+内层主标靶方式下，外靶允许3或4个
					{
						SetGlobalExcellonIndex(0);
						GetExcellonData().ClearAll();
						SetGlobalExcellonIndex(1);
						GetExcellonData().ClearAll();
						
						strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						strncpy(ez,GetLang().GetWarningText(22006),256);
						AfxMessageBox(ez);//"在内层主标靶工艺方式下外层标靶数量不正确!"
						return false;
					}
				
					for(int index=0;index<2;index++)
					{
						SetGlobalExcellonIndex(index);
						if(GetExcellonData().GetInnerFiducialNum()!=4)								//双区域加工文件+内层主标靶方式下，内靶允许4个
						{
							SetGlobalExcellonIndex(0);
							GetExcellonData().ClearAll();
							SetGlobalExcellonIndex(1);
							GetExcellonData().ClearAll();

							strncpy(ez,GetLang().GetWarningText(11009),256);//"导入原始文件失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							strncpy(ez,GetLang().GetWarningText(22007),256);
							AfxMessageBox(ez);//"在内层主标靶工艺方式下内层标靶数量不正确!"
							return false;
						}
					}

					for(index=0;index<2;index++)
					{
						SetGlobalExcellonIndex(index);
						if(!GetExcellonData().MakeAssistantData())
						{
							SetGlobalExcellonIndex(0);
							GetExcellonData().ClearAll();
							SetGlobalExcellonIndex(1);
							GetExcellonData().ClearAll();
							
							strncpy(ez,GetLang().GetWarningText(11011),256);//"数据生成失败！"
							m_staticState = _T(ez);
							UpdateData(FALSE);
							return false;				
						}
					}

					for(index=0;index<2;index++)
					{
						SetGlobalExcellonIndex(index);
						GetExcellonData().CheckFileRange();
					}

					if(!GetDoc().DistributeSubarea())
					{
						SetGlobalExcellonIndex(0);
						GetExcellonData().ClearAll();
						SetGlobalExcellonIndex(1);
						GetExcellonData().ClearAll();

						strncpy(ez,GetLang().GetWarningText(11012),256);//"数据宽度或高度超出范围！"
						m_staticState = _T(ez);
						UpdateData(FALSE);
						return false;
					}
				}
//--------------------------------------------------------------------------------------------------
				strncpy(ez,GetLang().GetWarningText(11010),256);//"导入原始文件完成！"
				m_staticState = _T(ez);
				UpdateData(FALSE);
			}
			
			GetDoc().SetFileOpenState(TRUE);
			GetDoc().SetFileName(str);
			
			str = str.Left(str.ReverseFind('.'));
			str +=TOOLPARAEXT;
			GetDoc().SetToolFileName(str);				
			GetToolView().LoadToolParaTree();

			if(GetDoc().GetToolCycleMode())
			{
//				GetDlgItem(IDC_RADIO_INNERMARK)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_LOCALMARK)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_SALOCALMARK)->EnableWindow(FALSE);				
			}

			GetPointcontrlView().LoadToolInfor();
/*			
			if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)			//20160818
			{
				m_iFileMode = 0;
				GetDoc().SetFileMode(SystemDoc::NORMALPROC);
			}

			if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
			{
				if(GetExcellonData().GetInnerFiducialNum()==4)
				{
					m_iFileMode = 0;
					GetDoc().SetFileMode(SystemDoc::NORMALPROC);
				}
				if(GetExcellonData().GetInnerFiducialNum()==6)
				{
					m_iFileMode = 1;
					GetDoc().SetFileMode(SystemDoc::INNERMARK);
				}
			}

			UpdateData(FALSE);
*/	
			long sum =0 ;
			Coord crdDest;
			CRD MinX = 99999999,MinY = 99999999;

			if(!GetDoc().GetIsDoubleFileData())
			{			
				for(int i=0; i<GetExcellonData().GetSubAreaCnt(); i++)
				{
					sum +=GetExcellonData().GetSubAreaHoleCount(i);

					if(!GetExcellonData().GetSubAreaIsEmpty(i)) 
					{
						crdDest = GetExcellonData().GetSubAreaCenter(i);
						
						if(MinX > crdDest.x)
							MinX = crdDest.x;
						if(MinY > crdDest.y)
							MinY = crdDest.y;
					}
				}
			}
			else//----------------------------------------------------------------20161109
			{
				for(int ii=0;ii<2;ii++)
				{	
					SetGlobalExcellonIndex(ii);
					for(int iii=0; iii<GetExcellonData().GetSubAreaCnt(); iii++)
					{
						sum +=GetExcellonData().GetSubAreaHoleCount(iii);

						if(!GetExcellonData().GetSubAreaIsEmpty(iii)) 
						{
							crdDest = GetExcellonData().GetSubAreaCenter(iii);
							
							if(MinX > crdDest.x)
								MinX = crdDest.x;
							if(MinY > crdDest.y)
								MinY = crdDest.y;
						}
					}					
				}
			}
//--------------------------------------------------------------------------------
			GetDoc().SetCurPCBHoleCount(sum);
//			GetDoc().SetIsRecordPowerPara(TRUE);

			MinX-=GetDoc().GetScanSize()*1000;
			MinY-=GetDoc().GetScanSize()*1000;
			GetDoc().SetLBRefPoint(Coord(MinX,MinY));

			if(!bSilent)														//20161123
			{
				if (!GetDoc().GetSysModeSwitch())//离线模式
				{
					ReadPCBThickness();
				}
				char bufnum[32];
				strncpy(ez,GetLang().GetWarningText(11013),256);
				sprintf(bufnum,ez,sum);//"孔数：%d\n"
				
				AfxMessageBox(bufnum);
			}
		}
		else
			return false;
	}

	if (GetDoc().GetSysModeSwitch())//在线模式
	{
		//处理固定号流水号
		DealLotIdFixAndInc();

		//处理内外标靶
		m_iProcMode = GetDoc().GetProcMode();
		UpdateData(FALSE);
		
		//处理板厚
		m_ulPCBThickness = GetDoc().GetPCBThickness()? GetDoc().GetPCBThickness():1000;
		UpdateData(FALSE);

		//生成标靶图像文件
		if (GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
		{
			//生成外标靶文件
			GetCMarkMake().m_iMarkType = 0;
			GetCMarkMake().OnSave2();
			//生成内标靶文件
			GetCMarkMake().m_iMarkType = 1;
			GetCMarkMake().OnSave2();
		}
		else
		{
			//生成外标靶文件
			GetCMarkMake().m_iMarkType = 0;
			GetCMarkMake().OnSave2();
		}
	}
	return true;
}

BOOL CFileInfoSettingView::SwitchDataFile(int side)
{
	ASSERT(side==0||side==1);
	CString strFileName=twoFilePath[side];
	
	if (!OpenDataFile(strFileName,true))
	{
		if(side==0)
			AfxMessageBox("A面数据文件打开失败!");
		else
			AfxMessageBox("B面数据文件打开失败!");
		return false;
	}

	return true;
}
/*
void CFileInfoSettingView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	SetGlobalExcellonIndex(0);

	int rowCount0=GetExcellonData().GetSubAreaCol();
	CString str;
	str.Format("rowCount0 = %d",rowCount0);
	AfxMessageBox(str);
}
*/
void CFileInfoSettingView::OnMenuasidedisplay() 
{
	// TODO: Add your command handler code here
	GetDoc().SetASideIsDisplay(true);
	CString strFileName=twoFilePath[0];
	
	if (!OpenDataFile(strFileName,true))
		AfxMessageBox("A面数据文件打开失败!");

//	GetMainFrame().m_wndStatusBar.SetPaneText(1,"  显示:A面");

	CMainFrame* pMainFrame;
	pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText(1,"  显示:A面");
}

void CFileInfoSettingView::OnUpdateMenuasidedisplay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if((GetDoc().GetFlowPathMode()==2)&&GetDoc().GetFileOpenState()&&(GetControl().GetRunState()==CControl::END))
	{
		pCmdUI->Enable(true);
		pCmdUI->SetRadio(GetDoc().GetASideIsDisplay()==true);
	}
	else
		pCmdUI->Enable(false);
}

void CFileInfoSettingView::OnMenubsidedisplay() 
{
	// TODO: Add your command handler code here
	GetDoc().SetASideIsDisplay(false);
	CString strFileName=twoFilePath[1];
	
	if (!OpenDataFile(strFileName,true))
		AfxMessageBox("B面数据文件打开失败!");	

//	GetMainFrame().m_wndStatusBar.SetPaneText(1,"  显示:B面");

	CMainFrame* pMainFrame;
	pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText(1,"  显示:B面");
}

void CFileInfoSettingView::OnUpdateMenubsidedisplay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if((GetDoc().GetFlowPathMode()==2)&&GetDoc().GetFileOpenState()&&(GetControl().GetRunState()==CControl::END))
	{
		pCmdUI->Enable(true);
		pCmdUI->SetRadio(GetDoc().GetASideIsDisplay()==false);
	}
	else
		pCmdUI->Enable(false);
}

void CFileInfoSettingView::OnChangeData() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the TVisualFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bFileInfoDataModified=true;	
}
/*
void CFileInfoSettingView::OnBtnAgvRise() 
{
	// TODO: Add your control notification handler code here
	//访问地址方法1 ip+port
	std::string domainIp = GetDoc().GetSysWebserviceIP().GetBuffer(0);
	std::string domainPort = GetDoc().GetSysWebservicePort().GetBuffer(0);
	//访问地址方法2 url
	std::string imeUrl = GetDoc().GetSysImesURL().GetBuffer(0);
	//设置超时时间(单位:秒)
	int timeOut = GetDoc().GetSysTimeout();

	//调用方法名
	std::string methodInvoke = "CallAgv";
	
	char prefixChar[256];
	std::string machineSn = GetDoc().GetSysMachineSn().GetBuffer(0);
	std::string inMaterialCode = GetDoc().GetSysInMaterialCode().GetBuffer(0);
	//进料时工单ID为空
	std::string wipEntity = "";
	sprintf(prefixChar,"macCode=\"%s\" berthCode=\"%s\" wipEntity=\"%s\"", machineSn.c_str(),inMaterialCode.c_str(),wipEntity.c_str());
	std::string prefixStr = prefixChar;
	
	//拼接需要上报的xml
	std::string inputxmlstring,responseStr;	
	bool result = false;
	//bool result = GetWSObejctImplementor().CallAgv(domainIp, domainPort, imeUrl, timeOut, prefixStr, methodInvoke, inputxmlstring, responseStr);
	if(!result)
	{
		AfxMessageBox("呼叫AGV进料失败!");
		//需要记日志
	}	
	else
	{
		m_staticState = _T("呼叫AGV进料成功!");
		UpdateData(FALSE);
	}

	// 动态加载dll
	HINSTANCE hInst;
	hInst = LoadLibrary("Dynamic.dll");
	//根据函数名获取dll地址
	typedef int(*SUBPROC)();
	SUBPROC func = (SUBPROC)GetProcAddress(hInst, "MyParamVerify");
	//调用dll的导出函数
	func();
	FreeLibrary(hInst);       //LoadLibrary后要记得FreeLibrary

	



}

void CFileInfoSettingView::OnBtnAgvDown() 
{
	// TODO: Add your control notification handler code here
	//访问地址方法1 ip+port
	std::string domainIp = GetDoc().GetSysWebserviceIP().GetBuffer(0);
	std::string domainPort = GetDoc().GetSysWebservicePort().GetBuffer(0);
	//访问地址方法2 url
	std::string imeUrl = GetDoc().GetSysImesURL().GetBuffer(0);
	//设置超时时间(单位:秒)
	int timeOut = GetDoc().GetSysTimeout();
	//调用方法名
	std::string methodInvoke = "CallAgv";
	
	char prefixChar[256];
	std::string machineSn = GetDoc().GetSysMachineSn().GetBuffer(0);
	std::string outMaterialCode = GetDoc().GetSysOutMaterialCode().GetBuffer(0);
	std::string wipEntity = "";
	sprintf(prefixChar,"macCode=\"%s\" berthCode=\"%s\" wipEntity=\"%s\"", machineSn.c_str(),outMaterialCode.c_str(),wipEntity.c_str());
	std::string prefixStr = prefixChar;
	
	//拼接需要上报的xml
	std::string inputxmlstring,responseStr;	
	bool result = false;
	//result = GetWSObejctImplementor().CallAgv(domainIp, domainPort, imeUrl, timeOut, prefixStr, methodInvoke, inputxmlstring, responseStr);
	if(!result)
	{
		AfxMessageBox("呼叫AGV出料失败!");
		//需要记日志
	}
	else
	{
		m_staticState = _T("呼叫AGV出料成功!");
		UpdateData(FALSE);
	}
	
}*/
