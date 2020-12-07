// ImageParaSetView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "ImageParaSetView.h"
#include "Excellon.h"
#include "operatecontrol.h"

#include "MarkMake.h"									//20190814

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageParaSetView
IMPLEMENT_DYNCREATE(CImageParaSetView, TVisualFormView)

CImageParaSetView *pImageParaSetView;

CImageParaSetView::CImageParaSetView()
	: TVisualFormView(CImageParaSetView::IDD)
{
	//{{AFX_DATA_INIT(CImageParaSetView)
	m_ulStepLength = "1000";
	m_lLightness = 0;
	m_bPlaneLAdsorb = FALSE;
	m_bPlaneRAdsorb = FALSE;
	m_X = _T("");
	m_Y = _T("");
	m_ZL = _T("");
	m_ZR = _T("");
	m_bStatusScale=-1;
	m_chkManuMove = FALSE;
	m_Edit_StringTableDelay = _T("50");
	m_bStatusX=-1;
	m_bStatusY=-1;
	FirstRun  = false;
	m_dbTestTemperature = 22.0;
	//}}AFX_DATA_INIT
	m_bManuMarkIsOK=false;
	m_bManuMarkIsEnd=false;
}

CImageParaSetView::~CImageParaSetView()
{
	delete pLampAdj;
}

void CImageParaSetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageParaSetView)
	DDX_Control(pDX, IDC_BT_FIRSTFIDUPOS, m_btnFirstFiduPoint);
	DDX_Control(pDX, IDC_EDT_STEPLEN, m_edtStepLength);
	DDX_Control(pDX, IDC_BT_LANMP, m_btnLampAjust);
	DDX_Control(pDX, IDC_BT_CLEANZR, m_coordCleanZR);
	DDX_Control(pDX, IDC_BT_CLEANY, m_coordCleanY);
	DDX_Control(pDX, IDC_BT_CLEANZL, m_coordCleanZL);
	DDX_Control(pDX, IDC_BT_CLEANX, m_coordCleanX);
	DDX_Control(pDX, IDC_CHK_OUT_PLANEL, m_chkPlaneLAdsorb);
	DDX_Control(pDX, IDC_CHK_OUT_PLANER, m_chkPlaneRAdsorb);
	DDX_Control(pDX, IDC_BT_STEP_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BT_STEP_UP, m_btnTabUP);
	DDX_Control(pDX, IDC_BT_STEP_RIGHT, m_btnTabRT);
	DDX_Control(pDX, IDC_BT_STEP_DOWN, m_btnTabDN);
	DDX_Control(pDX, IDC_BT_STEP_LEFT, m_btnTabLT);
	DDX_Control(pDX, IDC_BT_ZUP, m_btnZUp);
	DDX_Control(pDX, IDC_BT_ZDOWN, m_btnZDown);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_BT_FIDUCIALPOS, m_btnSetFiducialPos);
	DDX_Control(pDX, IDC_BT_CHANGECHAN, m_btnChannelChange);
	DDX_Control(pDX, IDC_BT_ADJUSTPATTERN, m_btnAdjustPattern);
	DDX_Control(pDX, IDC_BT_LEARNPATTERN, m_btnLearningPattern);
	DDX_Text(pDX, IDC_EDT_STEPLEN, m_ulStepLength);
	DDX_Text(pDX, IDC_EDIT1, m_lLightness);
	DDX_Check(pDX, IDC_CHK_OUT_PLANEL, m_bPlaneLAdsorb);
	DDX_Check(pDX, IDC_CHK_OUT_PLANER, m_bPlaneRAdsorb);
	DDX_Text(pDX, IDC_STATICX, m_X);
	DDX_Text(pDX, IDC_STATICY, m_Y);
	DDX_Text(pDX, IDC_STATICZL, m_ZL);
	DDX_Text(pDX, IDC_STATICZR, m_ZR);
	DDX_Check(pDX, IDC_CHK_ENABLEMANUMOVE, m_chkManuMove);
	DDX_Text(pDX, IDC_EDIT_TABLEDELAY, m_Edit_StringTableDelay);
	DDX_Text(pDX, IDC_EDT_TEMPERATURE, m_dbTestTemperature);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageParaSetView, TVisualFormView)
	//{{AFX_MSG_MAP(CImageParaSetView)
	ON_MESSAGE(WM_DISPLAY,OnDisplayImage)
	ON_MESSAGE(WM_UNDISPLAY,OnUndisplayImage)
	ON_BN_CLICKED(IDC_BT_CHANGECHAN, OnChangChannel)
	ON_BN_CLICKED(IDC_BT_LEARNPATTERN, OnLearnPattern)
	ON_BN_CLICKED(IDC_BT_STEP_DOWN, OnStepDown)
	ON_BN_CLICKED(IDC_BT_STEP_LEFT, OnStepLeft)
	ON_BN_CLICKED(IDC_BT_STEP_RIGHT, OnStepRight)
	ON_BN_CLICKED(IDC_BT_STEP_UP, OnStepUp)
	ON_BN_CLICKED(IDC_BT_STEP_STOP, OnStepStop)
	ON_BN_CLICKED(IDC_BT_FIDUCIALPOS, OnFiducialPosSet)
	ON_BN_CLICKED(IDC_BT_ADJUSTPATTERN, OnAdjustPattern)
	ON_WM_CREATE()
//	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_ZDOWN, OnBtZdown)
	ON_BN_CLICKED(IDC_BT_ZUP, OnBtZup)
	ON_BN_CLICKED(IDC_CHK_OUT_PLANEL, OnChkOutPlanel)
	ON_BN_CLICKED(IDC_CHK_OUT_PLANER, OnChkOutPlaner)
	ON_BN_CLICKED(IDC_BT_LANMP, OnBtLamp)
	ON_BN_CLICKED(IDC_BT_FIRSTFIDUPOS, OnBtFirstfidupos)
	ON_BN_CLICKED(IDC_CHK_ENABLEMANUMOVE, OnChkEnablemanumove)
	ON_BN_CLICKED(IDC_BUTTON_ACCURACYADJUST, OnButtonCorrectionGalvo)
	ON_BN_CLICKED(IDC_BUTTON_ACCURACYTEST, OnButtonAccuracyGalvo)
	ON_BN_CLICKED(IDC_BUTTON_DATATESTREPEATABILITY, OnButtonRepeatabilityTable)
	ON_BN_CLICKED(IDC_BUTTON_ACCURACYTABLE, OnButtonAccuracyTable)
	ON_BN_CLICKED(IDC_BUTTON_CORRECTIONTABLE, OnButtonCorrectionTable)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BT_MARKTEST, OnBtMarktest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageParaSetView diagnostics

//#ifdef _DEBUG//ly delete 20111217
void CImageParaSetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CImageParaSetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

LONG CImageParaSetView::OnDisplayImage(UINT wParam,LONG LParam)
{	
#ifdef USEIMAGE
#ifdef AVT													//20170531
	CRect rect;
	CSize size;		
	GetDlgItem(IDC_DISPLAY)->GetClientRect(rect);
	size.cx=rect.Width();
	size.cy=rect.Height();
	
	GetImageCaptor().Display(::GetDlgItem(m_hWnd,IDC_DISPLAY),size);
#endif
	
#ifdef PICOLO												//此AVT操作相同
	CRect rect;
	CSize size;		
	GetDlgItem(IDC_DISPLAY)->GetClientRect(rect);
	size.cx=rect.Width();
	size.cy=rect.Height();
	
	GetImageCaptor().Display(::GetDlgItem(m_hWnd,IDC_DISPLAY),size);
#endif
#endif	

	m_chkManuMove=false;
	GetDlgItem(IDC_CHK_ENABLEMANUMOVE)->EnableWindow(true);
	UpdateData(false);

	SetTimer(10,200,NULL);
	
	return 0;
}

LONG CImageParaSetView::OnUndisplayImage(UINT wParam,LONG lParam)
{
#ifdef USEIMAGE
	GetImageCaptor().UnDisplay();
#endif

    KillTimer(1);
	KillTimer(10);

#ifdef USEMOTION
#ifdef USEDMSYSTEM													//20200414
	GetXYMotion().SetTableManuMove(AXISTABX,1,FALSE);
    GetXYMotion().SetTableManuMove(AXISTABY,1,FALSE);
#else
	GetMotion().SetTableManuMove(AXISTABX,1,FALSE);
    GetMotion().SetTableManuMove(AXISTABY,1,FALSE);
#endif
#endif
//	m_chkManuMove=false; 
//	GetDlgItem(IDC_CHK_ENABLEMANUMOVE)->EnableWindow(true);

//  pLampAdj->ShowWindow(SW_HIDE);					//20200107 取消
	return 0;
}
/*
void CImageParaSetView::OnChangChannel() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	static long lCurChan=0 ;

	UpdateData();
	
	if(lCurChan==0)
	   lCurChan =1;
	else
	   lCurChan =0;

	if(lCurChan==0)
	{
#ifdef USEIMAGE
		if (!GetImageCaptor().SelectChannel(1))
			AfxMessageBox("图像通道1图像获取失败");
#endif  
	    m_btnChannelChange.SetIcon(IDI_CHANGER,IDI_CHANGEL);

		GetControl().MoveTo(AXISRIGHTZ,GetDoc().GetCCDFocus(1)-GetDoc().GetPCBThickness());
		GetControl().WaitAxisStop(AXISRIGHTZ);
	}
	else
	{
#ifdef USEIMAGE
		if (!GetImageCaptor().SelectChannel(0))
			AfxMessageBox("图像通道0图像获取失败");
#endif   
		m_btnChannelChange.SetIcon(IDI_CHANGEL,IDI_CHANGER);

		GetControl().MoveTo(AXISLEFTZ,GetDoc().GetCCDFocus(0)-GetDoc().GetPCBThickness());
		GetControl().WaitAxisStop(AXISLEFTZ);
	}

	Invalidate(FALSE);
	UpdateData(FALSE);
}
*/
void CImageParaSetView::OnChangChannel()								//20191015 改写
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	long lCurChan = GetImageCaptor().GetCurrentChannel();

	if(lCurChan==0)
	{
#ifdef USEIMAGE
		if (!GetImageCaptor().SelectChannel(1))
			AfxMessageBox("图像通道1图像获取失败");
#endif  
	    m_btnChannelChange.SetIcon(IDI_CHANGER,IDI_CHANGEL);

		GetControl().MoveTo(AXISRIGHTZ,GetDoc().GetCCDFocus(1)-GetDoc().GetPCBThickness());
		GetControl().WaitAxisStop(AXISRIGHTZ);
	}
	else
	{
#ifdef USEIMAGE
		if (!GetImageCaptor().SelectChannel(0))
			AfxMessageBox("图像通道0图像获取失败");
#endif   
		m_btnChannelChange.SetIcon(IDI_CHANGEL,IDI_CHANGER);

		GetControl().MoveTo(AXISLEFTZ,GetDoc().GetCCDFocus(0)-GetDoc().GetPCBThickness());
		GetControl().WaitAxisStop(AXISLEFTZ);
	}

//	Invalidate(FALSE);
	UpdateData(FALSE);
}

void CImageParaSetView::OnLearnPattern()						//20170524
{
	CString path = GetDoc().GetAppPath()+"bmp";

	int nSel = AfxMessageBox("请选择标靶模板制作方式:\n\n手工输入制作	选择“是”\n图像抓取制作	选择“否”\n取消此次操作	选择“取消”\n",MB_YESNOCANCEL);
	
	if(nSel==IDYES)
	{
//		ShellExecute(NULL, "open", "HansDraw", "", path, SW_SHOWNORMAL);
		CMarkMake markMake;										//20190814
		markMake.DoModal();
	}
	else if(nSel==IDNO)
	{
		CString destName = path + "\\ROI.bmp";
		GetImageCaptor().CaptROIImage((LPCSTR)destName,570,570);
		ShellExecute(NULL, "open", "mspaint", "ROI.bmp", path, SW_SHOWNORMAL);		
	}
	else
		return;

//	CString destName = GetDoc().GetAppPath()+"ROI.bmp";
//	GetImageCaptor().CaptROIImage((LPCSTR)destName,570,570);

//	CString path = GetDoc().GetAppPath()+"bmp";
//	ShellExecute(NULL, "open", "mspaint", "ROI.bmp", path, SW_SHOWNORMAL);
}

void CImageParaSetView::OnAdjustPattern() 
{
	SHORT  keyCtr = GetKeyState(VK_CONTROL);
	SHORT  keyRBtn = GetKeyState(VK_RBUTTON);
	SHORT  keyShift = GetKeyState(VK_SHIFT);

	if((keyCtr & 0x0080) && (keyRBtn & 0x0080) && (keyShift & 0x0080))
	{
       	GetDlgItem(IDC_BUTTON_ACCURACYADJUST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_ACCURACYTEST)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BT_MARKTEST)->ShowWindow(SW_SHOW);							//20190412

		GetDlgItem(IDC_STATIC_TABLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDT_TEMPERATURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TEMPERATURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_GALVO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_DATATESTREPEATABILITY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_ACCURACYTABLE)->ShowWindow(SW_SHOW);

#ifdef TABLE2DCALI
		GetDlgItem(IDC_BUTTON_CORRECTIONTABLE)->ShowWindow(SW_SHOW);
#endif
		UpdateData(FALSE);
		return;
	}

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

//#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageParaSetView message handlers

void CImageParaSetView::OnStepDown() 
{
	UpdateData();

	m_btnTabUP.EnableWindow(FALSE);					//20191210
	m_btnTabDN.EnableWindow(FALSE);
    
	GetControl().WaitAxisStop(AXISTABY);			//20191120 增加
    GetControl().MoveTo(AXISTABY,GetControl().GetPos(AXISTABY)-atol(m_ulStepLength));
    GetControl().WaitAxisStop(AXISTABY);

	Delay(500);

	m_btnTabUP.EnableWindow(true);
	m_btnTabDN.EnableWindow(true);
}

void CImageParaSetView::OnStepLeft() 
{
	UpdateData();

	m_btnTabRT.EnableWindow(FALSE);
	m_btnTabLT.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABX);			//20191120 增加
	GetControl().MoveTo(AXISTABX,GetControl().GetPos(AXISTABX)-atol(m_ulStepLength));
    GetControl().WaitAxisStop(AXISTABX);

	Delay(500);

	m_btnTabRT.EnableWindow(true);
	m_btnTabLT.EnableWindow(true);
}

void CImageParaSetView::OnStepRight() 
{
	UpdateData();

	m_btnTabRT.EnableWindow(FALSE);
	m_btnTabLT.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABX);			//20191120 增加
	GetControl().MoveTo(AXISTABX,GetControl().GetPos(AXISTABX)+atol(m_ulStepLength));
    GetControl().WaitAxisStop(AXISTABX);

	Delay(500);

	m_btnTabRT.EnableWindow(true);
	m_btnTabLT.EnableWindow(true);
}

void CImageParaSetView::OnBtZdown() 
{
	UpdateData();
	long lCurChan = GetImageCaptor().GetCurrentChannel();
    long AxisNo = lCurChan?AXISRIGHTZ:AXISLEFTZ;

    GetControl().WaitAxisStop(AxisNo);				//20191120 增加
	GetControl().MoveTo(AxisNo,GetControl().GetPos(AxisNo)+atol(m_ulStepLength));
    GetControl().WaitAxisStop(AxisNo);
}

void CImageParaSetView::OnBtZup() 
{
	UpdateData();
	long lCurChan = GetImageCaptor().GetCurrentChannel();
    long AxisNo = lCurChan?AXISRIGHTZ:AXISLEFTZ;

    GetControl().WaitAxisStop(AxisNo);				//20191120 增加
	GetControl().MoveTo(AxisNo,GetControl().GetPos(AxisNo)-atol(m_ulStepLength));
    GetControl().WaitAxisStop(AxisNo);
}

void CImageParaSetView::OnStepUp() 
{
	UpdateData();	

	m_btnTabUP.EnableWindow(FALSE);
	m_btnTabDN.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABY);			//20191120 增加
    GetControl().MoveTo(AXISTABY,GetControl().GetPos(AXISTABY)+atol(m_ulStepLength));
    GetControl().WaitAxisStop(AXISTABY);

	Delay(500);

	m_btnTabUP.EnableWindow(true);
	m_btnTabDN.EnableWindow(true);
}

void CImageParaSetView::OnStepStop() 
{
	GetMotion().Stop(AXISTABX);
	GetMotion().Stop(AXISTABY);
}

void CImageParaSetView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("ImageParaSet","IDC_STATIC3",szRead,20);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_STATIC1",szRead,20);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BT_ADJUSTPATTERN",szRead,20);
	SetDlgItemText(IDC_BT_ADJUSTPATTERN,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BT_LANMP",szRead,20);
	SetDlgItemText(IDC_BT_LANMP,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BT_LEARNPATTERN",szRead,20);
	SetDlgItemText(IDC_BT_LEARNPATTERN,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BT_CHANGECHAN",szRead,20);
	SetDlgItemText(IDC_BT_CHANGECHAN,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BT_FIDUCIALPOS",szRead,20);
	SetDlgItemText(IDC_BT_FIDUCIALPOS,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BT_FIRSTFIDUPOS",szRead,20);
	SetDlgItemText(IDC_BT_FIRSTFIDUPOS,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_CHK_OUT_PLANEL",szRead,20);
	SetDlgItemText(IDC_CHK_OUT_PLANEL,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_CHK_OUT_PLANER",szRead,20);
	SetDlgItemText(IDC_CHK_OUT_PLANER,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_CHK_ENABLEMANUMOVE",szRead,20);
	SetDlgItemText(IDC_CHK_ENABLEMANUMOVE,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_STATIC2",szRead,20);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_STATIC_TABLEDELAY",szRead,48);//ly add 20130326
	SetDlgItemText(IDC_STATIC_TABLEDELAY,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BUTTON_LOCATIONREPEATABILITY",szRead,20);//ly add 20130326
	SetDlgItemText(IDC_BUTTON_LOCATIONREPEATABILITY,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BUTTON_DATATESTREPEATABILITY",szRead,20);
	SetDlgItemText(IDC_BUTTON_DATATESTREPEATABILITY,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BUTTON_ACCURACYADJUST",szRead,20);
	SetDlgItemText(IDC_BUTTON_ACCURACYADJUST,szRead);
	GetLang().GetUIText("ImageParaSet","IDC_BUTTON_ACCURACYTEST",szRead,20);
	SetDlgItemText(IDC_BUTTON_ACCURACYTEST,szRead);
}

void CImageParaSetView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	pLampAdj = new CLampAdjDlgView;
	pLampAdj->Create(IDD_LAMPSADJUST,this);

	m_edit1.SetSlideLink( this, IDC_SLIDER1 );
	m_edit1.SetParams( 1,255 , 1 );//ly change 0,255-->1,255 20110617
	m_edit1.SetValue(m_lLightness);
    m_Slider1.SetSlidePos(m_lLightness);

	m_edtStepLength.SetParseType( SES_NUMBERS|SES_SIGNED ); 
	m_edtStepLength.SetRange(1,100000);

	GetDlgItem(IDC_BUTTON_ACCURACYADJUST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ACCURACYTEST)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BT_MARKTEST)->ShowWindow(SW_HIDE);								//20190412

	GetDlgItem(IDC_STATIC_TABLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDT_TEMPERATURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TEMPERATURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GALVO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_DATATESTREPEATABILITY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ACCURACYTABLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CORRECTIONTABLE)->ShowWindow(SW_HIDE);
}

int CImageParaSetView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
//	m_coordCleanX.SetIcon(IDI_ZERO,IDI_ZERO);
//	m_coordCleanY.SetIcon(IDI_ZERO,IDI_ZERO);
//	m_coordCleanZL.SetIcon(IDI_ZERO,IDI_ZERO);
//	m_coordCleanZR.SetIcon(IDI_ZERO,IDI_ZERO);
	
    m_lLightness = GetDoc().GetCCDLightness();
	pImageParaSetView=this;	
   
  // m_btnFirstFiduPoint.SubclassDlgItem(IDC_BT_FIRSTFIDUPOS,this);
	m_btnFirstFiduPoint.SetIcon(IDI_FIDU,IDI_FIDU);
   //m_btnLampAjust.SubclassDlgItem(IDC_BT_LANMP,this);
	m_btnLampAjust.SetIcon(IDI_LAMP,IDI_LAMP);
	
//	m_chkPlaneLAdsorb.SubclassDlgItem(IDC_CHK_OUT_PLANEL,this);
	m_chkPlaneLAdsorb.SetIcon(IDI_LEDON,IDI_LEDOFF);
	
//	m_chkPlaneRAdsorb.SubclassDlgItem(IDC_CHK_OUT_PLANER,this);
	m_chkPlaneRAdsorb.SetIcon(IDI_LEDON,IDI_LEDOFF);
	
//	m_btnLearningPattern.SubclassDlgItem(IDC_BT_LEARNPATTERN,this);
	m_btnLearningPattern.SetIcon(IDI_MPATTERN,IDI_MPATTERN);
	
//	m_btnSetFiducialPos.SubclassDlgItem(IDC_BT_FIDUCIALPOS,this);
	m_btnSetFiducialPos.SetIcon(IDI_FIDUPOS,IDI_FIDUPOS);
	
//	m_btnChannelChange.SubclassDlgItem(IDC_BT_CHANGECHAN,this);
	m_btnChannelChange.SetIcon(IDI_CHANGEL,IDI_CHANGER);
	
  // 	m_btnZUp.SubclassDlgItem(IDC_BT_ZUP,this);
	m_btnZUp.SetIcon(IDI_ZUP,IDI_ZUP);
	
   //	m_btnZDown.SubclassDlgItem(IDC_BT_ZDOWN,this);
	m_btnZDown.SetIcon(IDI_ZDOWN,IDI_ZDOWN);
    
   // m_btnTabDN.SubclassDlgItem(IDC_BT_STEP_DOWN,this);
	m_btnTabDN.SetIcon(IDI_ARROWDOWN,IDI_ARROWDOWN);
	
//	m_btnTabUP.SubclassDlgItem(IDC_BT_STEP_UP,this);
    m_btnTabUP.SetIcon(IDI_ARROWUP,IDI_ARROWUP);
	
//	m_btnTabRT.SubclassDlgItem(IDC_BT_STEP_RIGHT,this);
    m_btnTabRT.SetIcon(IDI_ARROWRIGHT,IDI_ARROWRIGHT);
	
//	m_btnTabLT.SubclassDlgItem(IDC_BT_STEP_LEFT,this);
    m_btnTabLT.SetIcon(IDI_ARROWLEFT,IDI_ARROWLEFT);
	
   // m_btnStop.SubclassDlgItem(IDC_BT_STEP_STOP,this);
	m_btnStop.SetIcon(IDI_STOP,IDI_STOP);

	m_btnAdjustPattern.SetIcon(IDI_MATRIX,IDI_MATRIX);
	return 0;
}
/*
void CImageParaSetView::OnChangeEdit1() 
{
    UpdateData();
 
	long lCurChan = GetImageCaptor().GetCurrentChannel();

	GetControl().SetCCDLuminance(m_lLightness,lCurChan);
}
*/
void CImageParaSetView::OnDestroy() 
{
	TVisualFormView::OnDestroy();

#ifdef USEIMAGE																//20200617
	long lCurChan = GetImageCaptor().GetCurrentChannel();
   
	UpdateData();
	GetDoc().SetCCDLightness(m_lLightness,lCurChan);
#endif
}

void CImageParaSetView::OnTimer(UINT nIDEvent)								//20180202
{
	char ez[256]={""};//ly 20110404

	if(nIDEvent == 1)
	{
		if(((GetControl().GetRunState()==CControl::END)||(GetControl().GetRunState()==CControl::MANU))&&GetDoc().GetMotorState())
		{
			if(m_chkManuMove)
			{
#ifdef USEIOCARD	
//				int nStatusX,nStatusY;
//				int nScale,nScale1,nScale5,nScale50;
				int nStatusX=1;
				int nStatusY=1;
				int nScale=1;
				int nScale1=1;
				int nScale5=1;
				int nScale50=1;
			
				nStatusX = GetControl().QueryIOBit(IMANUXBTN);				//0为有效，1为无效
				nStatusY = GetControl().QueryIOBit(IMANUYBTN);
				
				nScale1  = GetControl().QueryIOBit(IMANUX1BTN);				//0为有效，1为无效
				nScale5  = GetControl().QueryIOBit(IMANUX2BTN);
				nScale50 = GetControl().QueryIOBit(IMANUX3BTN);
				
				if(nStatusX==0&&nStatusY==0)
				{
					strncpy(ez,GetLang().GetWarningText(21011),256);
					AfxMessageBox(ez);//"请检查XY选择档相关线路！"
#ifdef USELOG
					GetLog().Append_pro(10010,20010,30001);//"请检查XY选择档相关线路!","手轮功能","大图窗口"
#endif
					return ;
				}
				
				if((nScale1+nScale5+nScale50)<2)
				{
					strncpy(ez,GetLang().GetWarningText(21012),256);
					AfxMessageBox(ez);//"请检查倍率选择档相关线路！"
#ifdef USELOG
					GetLog().Append_pro(10011,20010,30001);//"请检查倍率选择档相关线路!","手轮功能","大图窗口"
#endif
					return ;
				}

#ifdef USEDMSYSTEM																//20200506			
				if(nScale1==0)
					nScale = 4;
				else if(nScale5==0)
					nScale = 10;
				else if(nScale50==0)
					nScale = 16;
				else
					nScale = 1;
#else
				if(nScale1==0)
					nScale = 1;
				else if(nScale5==0)
					nScale = 10;
				else if(nScale50==0)
					nScale = 16;
				else
					nScale = 1;
#endif
				
				if ((nStatusX!=m_bStatusX) )	//定时判断X轴选择输入状态是否变化
				{
#ifdef USEDMSYSTEM
					GetXYMotion().SetTableManuMove(AXISTABX,nScale,!nStatusX);
#else
					GetMotion().SetTableManuMove(AXISTABX,nScale,!nStatusX);						//20190305 待修改
#endif
					m_bStatusX = nStatusX;	
				}
				
				if((nStatusY!=m_bStatusY))		//定时判断Y轴选择输入状态是否变化
				{
#ifdef USEDMSYSTEM
					GetXYMotion().SetTableManuMove(AXISTABY,nScale,!nStatusY);
#else
					GetMotion().SetTableManuMove(AXISTABY,nScale,!nStatusY);
#endif
					m_bStatusY = nStatusY;
				}
				
				if (nScale!=m_bStatusScale)		//定时判断倍率输入状态是否变化
				{
#ifdef USEDMSYSTEM
					GetXYMotion().SetTableManuMove(AXISTABY,nScale,!nStatusY);
					GetXYMotion().SetTableManuMove(AXISTABX,nScale,!nStatusX);
#else
					GetMotion().SetTableManuMove(AXISTABY,nScale,!nStatusY);
					GetMotion().SetTableManuMove(AXISTABX,nScale,!nStatusX);
#endif					
					m_bStatusScale=nScale;
				}
#endif	
			}
		}		
	}

	if(nIDEvent == 2)
	{
		if((GetControl().GetRunState()==CControl::MANU)&&GetDoc().GetMotorState())
		{
			if(m_chkManuMove)
			{
#ifdef USEIOCARD	
				int nStatusRun;
				nStatusRun = GetControl().QueryIOBit(IMANURUNBTN);
				
				if(nStatusRun!=m_bManuRun)
				{
					CString InforStr;
					InforStr.Format("确认标靶中心位置  请选择		'是'\n重新选择新的位置  请选择		'否'\n放弃手工对靶识别  请选择		'取消'\n");
					
					int nSel = ::AfxMessageBox(InforStr,MB_YESNOCANCEL);
					if(nSel==IDYES)
					{
						m_bManuMarkIsOK=true;
						EndManuMark();

					}
					else if(nSel==IDCANCEL)
						EndManuMark();
				}
#endif	
			}
		}
	}

	if(nIDEvent == 10)
	{
#ifdef USEMOTION
//		m_X.Format("%d",GetDoc().GetPos(AXISTABX));
//		m_Y.Format("%d",GetDoc().GetPos(AXISTABY));
//		m_ZL.Format("%d",GetMotion().GetPos(AXISLEFTZ));
//		m_ZR.Format("%d",GetMotion().GetPos(AXISRIGHTZ));

		m_X.Format("%d",GetControl().GetPos(AXISTABX));
		m_Y.Format("%d",GetControl().GetPos(AXISTABY));
		m_ZL.Format("%d",GetControl().GetPos(AXISLEFTZ));
		m_ZR.Format("%d",GetControl().GetPos(AXISRIGHTZ));
#endif
		GetDlgItem(IDC_STATICX)->SetWindowText(m_X);
		GetDlgItem(IDC_STATICY)->SetWindowText(m_Y);
		GetDlgItem(IDC_STATICZL)->SetWindowText(m_ZL);
		GetDlgItem(IDC_STATICZR)->SetWindowText(m_ZR);
	}

//	UpdateData(FALSE);
	
	TVisualFormView::OnTimer(nIDEvent);
}

void CImageParaSetView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)		//20180528
{
	m_bStatusX=-1;
	m_bStatusY=-1;
	m_bStatusScale=-1;

	if(bActivate)
	{
		int nLevel = GetDoc().GetCurUserLevel();

		if(GetControl().GetRunState()!=CControl::END)
		{
			m_btnAdjustPattern.EnableWindow(FALSE);
			m_btnChannelChange.EnableWindow(FALSE);
			m_btnSetFiducialPos.EnableWindow(FALSE);
			m_btnFirstFiduPoint.EnableWindow(FALSE);
			
			m_btnStop.EnableWindow(FALSE);
			m_btnTabUP.EnableWindow(FALSE);
			m_btnTabRT.EnableWindow(FALSE);
			m_btnTabDN.EnableWindow(FALSE);
			m_btnTabLT.EnableWindow(FALSE);
			m_btnZUp.EnableWindow(FALSE);
			m_btnZDown.EnableWindow(FALSE);
			
			GetDlgItem(IDC_CHK_OUT_PLANEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_PLANER)->EnableWindow(FALSE);
		}
		else
		{
			m_btnAdjustPattern.EnableWindow(TRUE);
			m_btnChannelChange.EnableWindow(TRUE);
			m_btnSetFiducialPos.EnableWindow(TRUE);
			m_btnFirstFiduPoint.EnableWindow(TRUE);	
			
			m_btnStop.EnableWindow(TRUE);
			m_btnTabUP.EnableWindow(TRUE);
			m_btnTabRT.EnableWindow(TRUE);
			m_btnTabDN.EnableWindow(TRUE);
			m_btnTabLT.EnableWindow(TRUE);
//			m_btnZUp.EnableWindow(TRUE);
//			m_btnZDown.EnableWindow(TRUE);

			if(nLevel==SystemDoc::PRIMARY)//初级						//20181225
			{
				m_btnZUp.EnableWindow(FALSE);
				m_btnZDown.EnableWindow(FALSE);
			}
			else
			{
				m_btnZUp.EnableWindow(TRUE);
				m_btnZDown.EnableWindow(TRUE);
			}
			
			GetDlgItem(IDC_CHK_OUT_PLANEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_PLANER)->EnableWindow(TRUE);	
		}
		
		/*if(nLevel==SystemDoc::PRIMARY)//初级
			GetDlgItem(IDC_BT_LEARNPATTERN)->EnableWindow(FALSE);
		else
			GetDlgItem(IDC_BT_LEARNPATTERN)->EnableWindow(TRUE);*/
		
//		UpdateData(FALSE);
	}

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CImageParaSetView::OnChkOutPlanel() 
{
	UpdateData();

	if(m_chkPlaneLAdsorb.GetCheck())
	{
		GetControl().ChannelOutput(OFANPOWERON, m_chkPlaneLAdsorb.GetCheck()); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
	}
	else
	{
		if(!m_chkPlaneRAdsorb.GetCheck())
			GetControl().ChannelOutput(OFANPOWERON, m_chkPlaneLAdsorb.GetCheck()); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	}
}

void CImageParaSetView::OnChkOutPlaner() 
{
	UpdateData();

	if(m_chkPlaneRAdsorb.GetCheck())   
		GetControl().ChannelOutput(OFANPOWERON, m_chkPlaneRAdsorb.GetCheck()); 
	else
	{
		if(!m_chkPlaneLAdsorb.GetCheck())
		   GetControl().ChannelOutput(OFANPOWERON, m_chkPlaneRAdsorb.GetCheck());   
	}

	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,m_chkPlaneRAdsorb.GetCheck());	
}

void CImageParaSetView::OnBtLamp() 
{
	pLampAdj->ShowWindow(SW_SHOW);
}

void CImageParaSetView::WriteFiducialPosToFile(int mode)
{
	CIniFile IniFile;
	Coord crd,crdA,crdB;
	char buf[MaxPathLen];
	CString strName = GetDoc().GetFileName();

	crd.x = GetControl().GetPos(AXISTABX);
	crd.y = GetControl().GetPos(AXISTABY);

	crdA = ReadFiducialPosFromFile(1);
	Delay(200);
	crdB = ReadFiducialPosFromFile(0);
	Delay(200);

	strName =strName.Left(strName.ReverseFind('.'));
	sprintf(buf,"%s",strName);
	IniFile.SetName(buf);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		if(mode==1)
		{
			IniFile.WriteSection("FistFiducialPosA");
			IniFile.WriteItemInt("Crd_x", crd.x);
			IniFile.WriteItemInt("Crd_y", crd.y);
			IniFile.WriteString("\n");

			IniFile.WriteSection("FistFiducialPosB");
			IniFile.WriteItemInt("Crd_x", crdB.x);
			IniFile.WriteItemInt("Crd_y", crdB.y);
			IniFile.WriteString("\n");
		}
		else
		{
			IniFile.WriteSection("FistFiducialPosA");
			IniFile.WriteItemInt("Crd_x", crdA.x);
			IniFile.WriteItemInt("Crd_y", crdA.y);
			IniFile.WriteString("\n");

			IniFile.WriteSection("FistFiducialPosB");
			IniFile.WriteItemInt("Crd_x", crd.x);
			IniFile.WriteItemInt("Crd_y", crd.y);
			IniFile.WriteString("\n");
		}

		IniFile.WriteSection("PCBThickness");
		IniFile.WriteItemInt("Thickness", GetDoc().GetPCBThicknessStd());

		IniFile.CloseIniFile();
	}
}

Coord CImageParaSetView::ReadFiducialPosFromFile(int mode)
{
  	CIniFile IniFile;
    Coord crd;
	char buf[MaxPathLen];
	CString strName = GetDoc().GetFileName();

	strName =strName.Left(strName.ReverseFind('.'));
	sprintf(buf,"%s",strName);
	IniFile.SetName(buf);

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		if(mode==1)
		{
			if(!IniFile.GetItemInt("FistFiducialPosA","Crd_x", crd.x))
				crd.x=245000;
			if(!IniFile.GetItemInt("FistFiducialPosA","Crd_y", crd.y))
				crd.y=245000;
		}
		else
		{
			if(!IniFile.GetItemInt("FistFiducialPosB","Crd_x", crd.x))
				crd.x=245000;
			if(!IniFile.GetItemInt("FistFiducialPosB","Crd_y", crd.y))
				crd.y=245000;
		}

		IniFile.CloseIniFile();	

		return crd;
	}
	else
		return Coord(245000,245000);
}

void CImageParaSetView::OnChkEnablemanumove() 
{
	m_chkManuMove=true;	
	GetDlgItem(IDC_CHK_ENABLEMANUMOVE)->EnableWindow(false);
	UpdateData(false);

#ifdef ACSDMSYSTEM														//20200414
	GetXYMotion().InitalTableManuMove(2,0.001);							//手轮轴号：2
#endif

	SetTimer(1,500,NULL);
}

void CImageParaSetView::OnBtFirstfidupos()
{	
	DWORD dwThreadId;
	//FirstMark();
	CloseHandle(CreateThread(NULL,0,RunFirstMark,(LPVOID)this,0,&dwThreadId));
}

DWORD WINAPI RunFirstMark(LPVOID pM)
{
	((CImageParaSetView*)pM)->FirstMark();

	return 0;
}

DWORD CImageParaSetView::FirstMark()							//20190723
//void CImageParaSetView::OnBtFirstfidupos()
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);						//"机器未整体回零，不允许相关操作!"
		return 0;
	}

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
		AfxMessageBox(ez);						//"请先打开要加工文件!"
		return 0;
	}

//Z轴下移到CCD工作位置，并打开相应的图像通道
	if(GetDoc().GetProcAxisMode()==0)
	{
		GetControl().MoveTo(AXISLEFTZ,GetDoc().GetCCDFocus(HeadLeft)-GetDoc().GetPCBThickness());		
		GetControl().MoveTo(AXISRIGHTZ,GetDoc().GetCCDFocus(HeadRight)-GetDoc().GetPCBThickness());

		GetControl().WaitAxisStop(AXISLEFTZ);
		GetControl().WaitAxisStop(AXISRIGHTZ);
		
		if (!GetImageCaptor().SelectChannel(0))					//打开相应的图像通道
		{
			AfxMessageBox("CCD图像通道0有异常，请确认！");
			return 0;
		}
	}
	else if(GetDoc().GetProcAxisMode()==1)
	{
		GetControl().MoveTo(AXISLEFTZ,GetDoc().GetCCDFocus(HeadLeft)-GetDoc().GetPCBThickness());

		GetControl().WaitAxisStop(AXISLEFTZ);

		if (!GetImageCaptor().SelectChannel(0))					//打开相应的图像通道
		{
			AfxMessageBox("CCD图像通道0有异常，请确认！");
			return 0;
		}
	}
	else if(GetDoc().GetProcAxisMode()==2)
	{
		GetControl().MoveTo(AXISRIGHTZ,GetDoc().GetCCDFocus(HeadRight)-GetDoc().GetPCBThickness());

		GetControl().WaitAxisStop(AXISRIGHTZ);

		if (!GetImageCaptor().SelectChannel(1))					//打开相应的图像通道
		{
			AfxMessageBox("CCD图像通道1有异常，请确认！");
			return 0;
		}
	}

	if(GetDoc().GetProcessState()==CControl::AUTOPROC)			//自动上板	//20190723
		GetControl().SetRunState(CControl::OPERATEWITHHAND);
	else
		GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);
	
	GetDoc().SetFault(false);

//手工上板或者自动上板
	int pathMode=1;
	if(!GetControl().PutPCBToTable(pathMode))
	{
		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);

		GetDoc().SetFault(false);
		return 0;
	}
/*																//20190604
	if(GetDoc().GetProcessState()==CControl::AUTOPROC)			//自动上板
	{
		Delay(6000);
		if(GetDoc().GetUse9112())
		{
			GetControl().ChannelOutput(OPROCEXIT,MIO_ON);
			Delay(500);
			GetControl().ChannelOutput(OPROCEXIT,MIO_OFF);
		}
		else
			GetControl().SetCOMOutput(9);						//机械手结束运行  o正向：9，	i逆向：9
	}
*/
//上板后平台移动到保存的位置
//	Coord FisrtFiduPos = ReadFiducialPosFromFile();	
	Coord FisrtFiduPos = ReadFiducialPosFromFile(pathMode);	
/*		
    if((FisrtFiduPos.x>0)&&(FisrtFiduPos.x<300000)&&(FisrtFiduPos.y>0)&&(FisrtFiduPos.y<300000))
	{
		GetControl().MoveTo(FisrtFiduPos);
		GetControl().WaitAxisStop(AXISTAB);
		
#ifdef USELOG
		GetLog().Append_pro(10012,20011);		//"成功到第一靶位置","第一靶位"
#endif 			
	}
	else
	{
	    strncpy(ez,GetLang().GetWarningText(22016),256);
		MessageBox(ez);							//"标靶位置超出范围！"	

#ifdef USELOG
		GetLog().Append_pro(10013,20011);		//"标靶位置超出范围","第一靶位"
#endif
	}
*/
	GetControl().MoveTo(FisrtFiduPos);							//20181113
	GetControl().WaitAxisStop(AXISTAB);
/*
	Delay(6000);
	if(GetDoc().GetUse9112())
	{
		GetControl().ChannelOutput(OPROCEXIT,MIO_ON);
		Delay(500);
		GetControl().ChannelOutput(OPROCEXIT,MIO_OFF);
	}
	else
		GetControl().SetCOMOutput(9);			//机械手结束运行  o正向：9，	i逆向：9
*/
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

	GetDoc().SetFault(false);
	return 0;
}

void CImageParaSetView::OnFiducialPosSet()
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);			//"机器未整体回零，不允许相关操作!"
		return;
	}

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
		AfxMessageBox(ez);			//"请先打开要加工文件!"
		return;
	}

    if(GetExcellonData().GetFiducialNum()>0)
	{
		Coord crd;
		HoleCoordV crdV;
		double dbDevX,dbDevY;

		dbDevX=0.0;
		dbDevY=0.0;

		crd.x = GetControl().GetPos(AXISTABX);
		crd.y = GetControl().GetPos(AXISTABY);

		crdV.push_back(crd);
		crdV.push_back(crd);											//20190412 增加

		int nHead=HeadBoth;	
		if(GetDoc().GetProcAxisMode()==1)
			nHead=HeadLeft;
		if(GetDoc().GetProcAxisMode()==2)
			nHead=HeadRight;

//		if(GetControl().TargetFindInProc(HeadLeft,1,crdV,FIRSTMARKPOS,dbDevX,dbDevY)==-1)
		if(GetControl().TargetFindInProc(nHead,1,crdV,FIRSTMARKPOS,dbDevX,dbDevY)==-1)
		{
			strncpy(ez,GetLang().GetWarningText(21009),256);
			AfxMessageBox(ez);									//"靶标定位失败!"

			GetLog().Append_pro(10008,20009);					//"靶标定位失败!","模板定位"

//			GetControl().LightTurnOff();
			return ;
		}
/*	
		if(!GetControl().FindFiducialRealPos(0,crd,3,dbDevX,dbDevY))
		{
			GetControl().ChannelOutput(OCOMMONALARM,IO_ON);
			strncpy(ez,GetLang().GetWarningText(21009),256);
			AfxMessageBox(ez);									//"靶标定位失败!"
			GetControl().ChannelOutput(OCOMMONALARM,IO_OFF);
			GetLog().Append_pro(10008,20009);					//"靶标定位失败!","模板定位"

			GetControl().LightTurnOff();
			return ;
		}
*/
		Delay(500);
		
		if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)
		{
			int nSel = AfxMessageBox("请选择此次标靶定位的流程方向，A面请选“是”，B面请选“否”!",MB_YESNO);
			
			if(nSel==IDYES)
			{
				crd.x = GetControl().GetPos(AXISTABX)+GetDoc().GetFirstMarkPos(true).x+dbDevX;		//A面第一个标靶
				crd.y = GetControl().GetPos(AXISTABY)+GetDoc().GetFirstMarkPos(true).y+dbDevY;

				GetDoc().SetFileToRealRelative2(crd,0);
				GetDoc().SetIsFiducialDo2(TRUE,0);

				WriteFiducialPosToFile(1);
			}
			else
			{
				crd.x = GetControl().GetPos(AXISTABX)+GetDoc().GetFirstMarkPos(false).x+dbDevX;		//B面第一个标靶
				crd.y = GetControl().GetPos(AXISTABY)+GetDoc().GetFirstMarkPos(false).y+dbDevY;

				GetDoc().SetFileToRealRelative2(crd,1);
				GetDoc().SetIsFiducialDo2(TRUE,1);

				WriteFiducialPosToFile(0);
			}

//			if(GetDoc().GetIsFiducialDo2(0)&&GetDoc().GetIsFiducialDo2(1))
//				GetDoc().SetIsFiducialDo(TRUE);
		}
		else
		{
			crd.x = GetControl().GetPos(AXISTABX)+GetExcellonData().GetFiducialPos().x+dbDevX;		//第一个标靶
			crd.y = GetControl().GetPos(AXISTABY)+GetExcellonData().GetFiducialPos().y+dbDevY;

			GetDoc().SetFileToRealRelative(crd);

			GetDoc().SetIsFiducialDo(TRUE);

			if(GetDoc().GetFlowPathMode()==ONLYB)
				WriteFiducialPosToFile(0);
			else
				WriteFiducialPosToFile(1);
		}

//		WriteFiducialPosToFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(21010),256);
		AfxMessageBox(ez);						//"请先选择加工文件并确定其包含靶标位置信息！"

#ifdef USELOG
		GetLog().Append_pro(10009,20009);		//"请先选择加工文件并确定其包含靶标位置信息!","模板定位"
#endif
	}
}

void CImageParaSetView::OnButtonCorrectionGalvo()
{
	char ez[256]={""};
	int nHead=2;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

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

	if(!GetControl().AutoAdjustPattern(nHead,true))
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

void CImageParaSetView::OnButtonAccuracyGalvo()
{
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

	CTime timeAccuracy;
	timeAccuracy=CTime::GetCurrentTime();
	CString str="";
	str=timeAccuracy.Format("%Y%m%d-");
    CString timeFormat="";
	timeFormat.Format("%s%d%d%d-speed%d-jumpDelay%d-minJumpDelay%d-jumpLengthLimit%d-Bit%d",str,timeAccuracy.GetHour(),timeAccuracy.GetMinute(),timeAccuracy.GetSecond(),
		GetDoc().GetProcJumpSpeed(),GetDoc().GetProcJumpDelay(),GetDoc().GetProcJumpDelay0(),GetDoc().GetProcJumpLenth(),GetDoc().GetSLBitPerMM());
   	CString gavloAccuracySavePath=GetDoc().GetAppPath()+"info\\"+timeFormat+".txt";
	
	GetInfo().SaveToFile(gavloAccuracySavePath,"ProcJumpSpeed %d    ,ProcJumpDelay %d    ,ProcJumpDelay0 %d    ,ProcJumpLenth %d    , SLBitPerMM %d\n",	
		GetDoc().GetProcJumpSpeed(),GetDoc().GetProcJumpDelay(),GetDoc().GetProcJumpDelay0(),GetDoc().GetProcJumpLenth(),GetDoc().GetSLBitPerMM());
	GetInfo().SaveToFile(gavloAccuracySavePath,"AdjustJumpSpeed %d    ,AdjustJumpDelay %d    ,AdjustPulsePeriod %d    ,AdjustPulseRelease %d     ,Aperture %d\n",	
		GetDoc().GetAdjustJumpSpeed(),GetDoc().GetAdjustJumpDelay(),GetDoc().GetAdjustPulsePeriod(),GetDoc().GetGlvAdjPlsRelease(),GetDoc().GetLongPathAdjustAperture());
	
	bool bMatrixOk,bTestOK;
	Coord3D crd3d,CCDToGlvOffSet;
	int calibTimes=50;
	
	crd3d.x = GetDoc().GetCCDToGlvSysOffset(nHead).x;
	crd3d.y = GetDoc().GetCCDToGlvSysOffset(nHead).y;
	crd3d.z = GetDoc().GetCCDFocus(nHead)-GetDoc().GetGalvoBoardThick();
	
	CCDToGlvOffSet.x = GetDoc().GetGlvAdjPosX();
	CCDToGlvOffSet.y = GetDoc().GetGlvAdjPosY();
	
	if((nHead==HeadRight)&&(GetDoc().GetLargeTable()==1))//大台面机型的振镜校正板放置在两台面的中间，并且左台面的在中间偏上，右台机的在中间偏下
	{
		CCDToGlvOffSet.x+=TABADJRTLX;
		CCDToGlvOffSet.y+=TABADJRTLY;
	}
	
	if(GetDoc().GetTechnicType())
		CCDToGlvOffSet.z = GetDoc().GetLongPathLaserProcFocus(nHead)-GetDoc().GetGalvoBoardThick();
	else
		CCDToGlvOffSet.z = GetDoc().GetLaserProcFocus(nHead)-GetDoc().GetGalvoBoardThick();	


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

//打开CCD光源
	GetControl().LightTurnOn(GALNOMATRIX);

//开始振镜精度测试
	int testStart=0;

#ifdef GALVOTEST
	testStart=2;
#endif

	bTestOK=true;

	for (int accuracyTimes=testStart;accuracyTimes<calibTimes;accuracyTimes++)
	{ 
		if (accuracyTimes==testStart)	
			GetDoc().AccuracyTestChangeRow(nHead);
		
//		if(((accuracyTimes>9)&&(accuracyTimes<26))||(accuracyTimes>33))				//20171129 新测试，跳过一些步距测试
//			continue;
		
		for(int j=0;j<6;j++)
		{			
			bMatrixOk=TRUE;
			
			if(GetControl().GlovaAccuracyAutoCalibrateTest(CCDToGlvOffSet,crd3d,nHead,bMatrixOk,j,accuracyTimes,gavloAccuracySavePath))
			{	
				if(bMatrixOk)
					break;					
			}
			else
			{
				if(nHead==HeadLeft)
					GetDoc().SetLastWarningNo(79);	//"左轴振镜点阵校正出现错误"

				if(nHead==HeadRight)
					GetDoc().SetLastWarningNo(80);	//"右轴振镜点阵校正出现错误"
		
				bTestOK=false;
				break;
			}

			if(j==5)
			{
				GetDoc().SetLastWarningNo(95);		//"校正区域有异常点"
				bTestOK=false;
			}
		}

		if(!bTestOK)
			break;
	}

	GetDoc().WriteCaliTimes();
	GetControl().LightTurnOff();

	GetControl().TableClampOperate(true,GetDoc().GetTableClamp());
	GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

void CImageParaSetView::InsertSort(int a[],int count)//jpc add 20130322
{//升序
	int i,j,temp;
	for(i=1;i<count;i++)   
	{
		temp=a[i];
		j=i-1;
		while(a[j]>temp && j>=0)
		{
			a[j+1]=a[j];
			j--;
		}
		if(j!=(i-1))     
			a[j+1]=temp;
	}
}

void CImageParaSetView::OnButtonRepeatabilityTable()				//随机重复测试激光标记的225个点
{//使用自制的严克力板测试平台的重复性
	char ez[256]={""};
	int nHead;
	const int pointCount=225;										//9*5*5=225

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	UpdateData();

//设定加工轴
	int nSelect = AfxMessageBox("左侧平台  选择 '是'\n 右侧平台 选择 '否'\n取消操作 选择 '取消'\n",MB_YESNOCANCEL);
	if (nSelect == IDYES)
		nHead=0;
	else if (nSelect == IDNO)
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

//打开CCD光源
	GetControl().LightTurnOn(GALNOOFFSET);	

	nSelect = AfxMessageBox("请确认已将测试原点移至CCD视场中，继续请选择  '是'，取消请选择  '否'\n",MB_YESNO);
	if (nSelect == IDNO)
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

//识别定位原点和水平点
	CArray<Coord, Coord> Dev;
	HoleCoordV crdTestV;

	Dev.RemoveAll();	
	crdTestV.clear();

	crdTestV.push_back(GetControl().GetTablePos());

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,4))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

	Delay(500);

	Coord crd0;
	crd0.x=GetControl().GetPos(AXISTABX);
	crd0.y=GetControl().GetPos(AXISTABY);
	crd0.x+=Dev.GetAt(0).x;
	crd0.y+=Dev.GetAt(0).y;

	Dev.RemoveAll();
	crdTestV.clear();

	crdTestV.push_back(Coord(crd0.x-470000,crd0.y));

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,4))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

	Delay(500);

	Coord crd1;
	crd1.x=GetControl().GetPos(AXISTABX);
	crd1.y=GetControl().GetPos(AXISTABY);
	crd1.x+=Dev.GetAt(0).x;
	crd1.y+=Dev.GetAt(0).y;

//生成规则的测试点数据
	Coord crdCCDPos;
	Coord crdBig,crdSmall,posCrd;
    double rotateRadian=atan((double)(crd1.y-crd0.y)/(double)(crd1.x-crd0.x));	//亚克力板放置旋转弧度

	crdTestV.clear();

	for(int j=0;j<9;j++)							//9个大区域，十字
    {
        crdBig.x=crd0.x-235000*(j%3);
		crdBig.y=crd0.y-330000*(j/3);

		for(int i=0;i<5;i++)						//5个中区域，十字
		{			
			if (i==0)
			{
				crdSmall.x=crdBig.x+30000;
				crdSmall.y=crdBig.y+30000;
			}
			else if (i==1)
			{
				crdSmall.x=crdBig.x-30000;
				crdSmall.y=crdBig.y+30000;
			}
			else if (i==2)
			{
				crdSmall.x=crdBig.x;
				crdSmall.y=crdBig.y;
			}
			else if (i==3)
			{
				crdSmall.x=crdBig.x+30000;
				crdSmall.y=crdBig.y-30000;
			}
			else
			{
				crdSmall.x=crdBig.x-30000;
				crdSmall.y=crdBig.y-30000;
			}
			
			for(int mark=0;mark<5;mark++)			//5个小区域，十字
			{
               	if (mark==0)
				{
					posCrd.x=crdSmall.x+5000;
					posCrd.y=crdSmall.y+5000;
				}
				else if (mark==1)
				{
					posCrd.x=crdSmall.x-5000;
					posCrd.y=crdSmall.y+5000;
				}
				else if (mark==2)
				{
					posCrd.x=crdSmall.x;
					posCrd.y=crdSmall.y;
				}
				else if (mark==3)
				{
					posCrd.x=crdSmall.x+5000;
					posCrd.y=crdSmall.y-5000;
				}
				else
				{
					posCrd.x=crdSmall.x-5000;
					posCrd.y=crdSmall.y-5000;
				}

				crdCCDPos=ToRotateTable(crd0,rotateRadian,posCrd);

				crdTestV.push_back(crdCCDPos);
			}
		}
	}

//进行3次随机数据采集并记录
	int arrayErrorResultX1[pointCount];
	int arrayErrorResultY1[pointCount];
	int arrayErrorResultX2[pointCount];
	int arrayErrorResultY2[pointCount];
	int arrayErrorResultX3[pointCount];
	int arrayErrorResultY3[pointCount];
	
	int tableDelaytime=0;									//0是动态延时
	if(!GetDoc().GetNewDelay())
		tableDelaytime=GetDoc().GetTableDelay();

	for(int times=0;times<3;times++)
	{
		int arrayInt[pointCount];
		int randint=0;
		int tempCount=0;
		bool controlInsert=FALSE;
		HoleCoordV crdRandomV;

//生成随机索引序列
		srand(time(NULL));

		while(true)
		{
			randint = rand() % pointCount; 

			if (tempCount==0)
			{
				arrayInt[tempCount]=randint;
				tempCount++;
				continue;
			}

			controlInsert=true;

			for (int m=0;m<tempCount;m++)
			{
				if (arrayInt[m]==randint)
				{
					controlInsert=FALSE;
					continue;
				}
			}

			if (controlInsert)
			{
				arrayInt[tempCount]=randint;
				tempCount++;
			}

			if (tempCount==pointCount)
				break;
		}
		
//检测随机生成的索引序列是否有效
		int arrayCheck[pointCount];
		for (int checkNumber=0;checkNumber<pointCount;checkNumber++)
		{
			arrayCheck[checkNumber]=arrayInt[checkNumber];
		}

		InsertSort(arrayCheck,pointCount);

		for (int judge=0;judge<pointCount;judge++)
		{
			if (arrayCheck[judge]!=judge)
			{
				AfxMessageBox("随机序列生成错误，请确认!");
				return;
			}
		}		
	
//生成随机的测试点数据，并采集测试数据
		Dev.RemoveAll();
		crdRandomV.clear();

		for(int rand=0;rand<pointCount;rand++)
		{
			crdRandomV.push_back(crdTestV[arrayInt[rand]]);
		}

		if(!GetControl().TargetFindInCali(nHead,crdRandomV.size(),crdRandomV,Dev,5))
		{
			GetControl().LightTurnOff();		
			GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
			GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
			GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
			GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
			GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
			return;
		}

//保存测试数据
		CFileFind fileFind;
		BOOL isFind=FALSE;
		CString strOut;
		strOut.Format("info\\TableRepeatData%d.txt",times);
		CString outpointstr=GetDoc().GetAppPath()+strOut;

		isFind=fileFind.FindFile(outpointstr);
		fileFind.Close();
		if (isFind)
			DeleteFile(outpointstr);

		GetInfo().SaveToFile(outpointstr,"(CommandX,CommandY):(PosErrX,PosErrY)\n");

		for(int error=0;error<pointCount;error++)
		{
			if (times==0)
			{
				arrayErrorResultX1[arrayInt[error]]=Dev.GetAt(error).x;
				arrayErrorResultY1[arrayInt[error]]=Dev.GetAt(error).y;
			}
			else if (times==1)
			{
				arrayErrorResultX2[arrayInt[error]]=Dev.GetAt(error).x;
				arrayErrorResultY2[arrayInt[error]]=Dev.GetAt(error).y;
			}
			else
			{
				arrayErrorResultX3[arrayInt[error]]=Dev.GetAt(error).x;
				arrayErrorResultY3[arrayInt[error]]=Dev.GetAt(error).y;
			}
		}
		
		for(int n=0; n<pointCount;n++)
		{
			if (times==0)
				GetInfo().SaveToFile(outpointstr,"(%d,%d):(%d,%d)\n",crdTestV[n].x,crdTestV[n].y,arrayErrorResultX1[n],arrayErrorResultY1[n]);
			else if (times==1)
				GetInfo().SaveToFile(outpointstr,"(%d,%d):(%d,%d)\n",crdTestV[n].x,crdTestV[n].y,arrayErrorResultX2[n],arrayErrorResultY2[n]);
			else
				GetInfo().SaveToFile(outpointstr,"(%d,%d):(%d,%d)\n",crdTestV[n].x,crdTestV[n].y,arrayErrorResultX3[n],arrayErrorResultY3[n]);
		}		
	}

//关闭CCD光源
	GetControl().LightTurnOff();
	
	GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
	
//数据分析并保存
	int compareOneX[pointCount],compareTwoX[pointCount],compareResultX[pointCount],compareResultY[pointCount];

	CString resultData=GetDoc().GetAppPath()+"info\\TableRepeatResult.txt";

	for (int compareTimes=0;compareTimes<3;compareTimes++)
	{
		for (int calculateRepeatability=0;calculateRepeatability<pointCount;calculateRepeatability++)
		{//两次测量数据之差
			if (compareTimes==0)
			{
				compareResultX[calculateRepeatability]=arrayErrorResultX1[calculateRepeatability]-arrayErrorResultX2[calculateRepeatability];
				compareResultY[calculateRepeatability]=arrayErrorResultY1[calculateRepeatability]-arrayErrorResultY2[calculateRepeatability];
			}
			else if(compareTimes==1)
			{
				compareResultX[calculateRepeatability]=arrayErrorResultX2[calculateRepeatability]-arrayErrorResultX3[calculateRepeatability];
				compareResultY[calculateRepeatability]=arrayErrorResultY2[calculateRepeatability]-arrayErrorResultY3[calculateRepeatability];	
			}
			else
			{
				compareResultX[calculateRepeatability]=arrayErrorResultX3[calculateRepeatability]-arrayErrorResultX1[calculateRepeatability];
				compareResultY[calculateRepeatability]=arrayErrorResultY3[calculateRepeatability]-arrayErrorResultY1[calculateRepeatability];	
			}
		}

		InsertSort(compareResultX,pointCount);
		InsertSort(compareResultY,pointCount);

		if (compareTimes==0)
			strncpy(ez,GetLang().GetWarningText(32005),256);//"第一次与第二次之差:   平台重复精度范围X轴:[%d,%d]um,Y轴:[%d,%d]um. 平台延时:%d us\n"
		else if(compareTimes==1)
			strncpy(ez,GetLang().GetWarningText(32006),256);//"第二次与第三次之差:   平台重复精度范围X轴:[%d,%d]um,Y轴:[%d,%d]um. 平台延时:%d us\n"
		else
			strncpy(ez,GetLang().GetWarningText(32007),256);//"第三次与第一次之差:   平台重复精度范围X轴:[%d,%d]um,Y轴:[%d,%d]um. 平台延时:%d us\n"
		
		GetInfo().SaveToFile(resultData,ez,compareResultX[0],compareResultX[pointCount-1],compareResultY[0],compareResultY[pointCount-1],tableDelaytime);
	}
	
//输出各组误差值范围
	InsertSort(arrayErrorResultX1,pointCount);
	InsertSort(arrayErrorResultY1,pointCount);
	InsertSort(arrayErrorResultX2,pointCount);
	InsertSort(arrayErrorResultY2,pointCount);
	InsertSort(arrayErrorResultX3,pointCount);
	InsertSort(arrayErrorResultY3,pointCount);

	strncpy(ez,GetLang().GetWarningText(32008),256);//"平台测试数据1精度范围:---X轴:[%d,%d]um,Y轴:[%d,%d]um. 平台延时:%d us\n"
	GetInfo().SaveToFile(resultData,ez,arrayErrorResultX1[0],arrayErrorResultX1[pointCount-1],arrayErrorResultY1[0],arrayErrorResultY1[pointCount-1],tableDelaytime);
	strncpy(ez,GetLang().GetWarningText(32009),256);//"平台测试数据2精度范围:---X轴:[%d,%d]um,Y轴:[%d,%d]um. 平台延时:%d us\n"
	GetInfo().SaveToFile(resultData,ez,arrayErrorResultX2[0],arrayErrorResultX2[pointCount-1],arrayErrorResultY2[0],arrayErrorResultY2[pointCount-1],tableDelaytime);
	strncpy(ez,GetLang().GetWarningText(32010),256);//"平台测试数据3精度范围:---X轴:[%d,%d]um,Y轴:[%d,%d]um. 平台延时:%d us\n"
	GetInfo().SaveToFile(resultData,ez,arrayErrorResultX3[0],arrayErrorResultX3[pointCount-1],arrayErrorResultY3[0],arrayErrorResultY3[pointCount-1],tableDelaytime);

	AfxMessageBox("亚克力板平台重复精度测试完成!");
}

Coord CImageParaSetView::ToRotateTable(const Coord& cenCrd, double angle, const Coord& crd)
{//旋转算法
    return Coord( (long)(cenCrd.x + (crd.x - cenCrd.x) * cos(angle) - (crd.y - cenCrd.y) * sin(angle)),
		(long)(cenCrd.y + (crd.x - cenCrd.x) * sin(angle) + (crd.y - cenCrd.y) * cos(angle)) );	
}

void CImageParaSetView::OnButtonAccuracyTable()						//20180417
{//使用玻璃尺测试平台的精度
	char ez[256]={""};
	int nHead;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	UpdateData();

//设定加工轴
	int nSelect = AfxMessageBox("左侧平台  选择 '是'\n 右侧平台 选择 '否'\n取消操作 选择 '取消'\n",MB_YESNOCANCEL);
	if (nSelect == IDYES)
		nHead=0;
	else if (nSelect == IDNO)
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

//打开CCD光源
	GetControl().LightTurnOn(OUTERMAINPATTERN);	

	nSelect = AfxMessageBox("请确认已将测试原点移至CCD视场中，继续请选择  '是'，取消请选择  '否'\n",MB_YESNO);
	if (nSelect == IDNO)
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

//识别玻璃尺原点和水平点
	CArray<Coord, Coord> Dev;
	HoleCoordV crdTestV;

	Dev.RemoveAll();	
	crdTestV.clear();

	crdTestV.push_back(GetControl().GetTablePos());

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,2))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

	Delay(500);

	Coord crd0;
	crd0.x=GetControl().GetPos(AXISTABX);
	crd0.y=GetControl().GetPos(AXISTABY);
	crd0.x+=Dev.GetAt(0).x;
	crd0.y+=Dev.GetAt(0).y;

	Dev.RemoveAll();
	crdTestV.clear();

	crdTestV.push_back(Coord(crd0.x-585000,crd0.y));							//20200414
//	crdTestV.push_back(Coord(crd0.x-580000,crd0.y));							//20180525

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,2))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

	Delay(500);

	Coord crd1;
	crd1.x=GetControl().GetPos(AXISTABX);
	crd1.y=GetControl().GetPos(AXISTABY);
	crd1.x+=Dev.GetAt(0).x;
	crd1.y+=Dev.GetAt(0).y;

//采集玻璃尺测试数据
//	HoleCoordV crdCommandV;
	Coord crdCCDPos;

 	int tempXPoints=14;															//20200414
 	int tempYPoints=18;															//18
	int interval=45000;
// 	int tempXPoints=30;															//20180525
//	int tempYPoints=30;
//	int interval=20000;

	double temperature=m_dbTestTemperature;										//玻璃尺放置环境温度
	double scaleTemperature=8.1/1000000.0;										//玻璃尺线膨胀系数 8.067/1000000.0
	double scaleGlass=1+(temperature-22.0)*scaleTemperature;					//玻璃尺使用标准温度为22度
    double rotateRadian=atan((double)(crd1.y-crd0.y)/(double)(crd1.x-crd0.x));	//玻璃尺放置旋转弧度

	Dev.RemoveAll();
	crdTestV.clear();
//	crdCommandV.clear();

	for(int i=0;i<tempYPoints;i++)		
	{
		for(int j=0;j<tempXPoints;j++)			
		{
			crdCCDPos.x=crd0.x-j*interval*scaleGlass;
			crdCCDPos.y=crd0.y-i*interval*scaleGlass;

//			crdCommandV.push_back(crdCCDPos);

			crdCCDPos=ToRotateTable(crd0,rotateRadian,crdCCDPos);

			crdTestV.push_back(crdCCDPos);
		}
	}

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,3))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

//关闭CCD光源
	GetControl().LightTurnOff();
	
	GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);

//保存玻璃尺测试数据
	CFileFind fileFind;
	BOOL isFind=FALSE;
	CString outpointstr=GetDoc().GetAppPath()+"info\\TableTestData.txt";
	
	isFind=fileFind.FindFile(outpointstr);
	fileFind.Close();
	if (isFind)
		DeleteFile(outpointstr);	
	
	GetInfo().SaveToFile(outpointstr,"(CommandX,CommandY):(PosErrX,PosErrY)\n");

	for(int n=0; n<tempYPoints*tempXPoints;n++)
	{
		GetInfo().SaveToFile(outpointstr,"(%d,%d):(%d,%d)\n",crdTestV[n].x,crdTestV[n].y,Dev.GetAt(n).x,Dev.GetAt(n).y);
	}

	AfxMessageBox("玻璃尺测试数据采集完成!");
}

void CImageParaSetView::BeginManuMark()
{
	m_chkManuMove=true;	
	GetDlgItem(IDC_CHK_ENABLEMANUMOVE)->EnableWindow(false);
	UpdateData(false);

	m_bManuMarkIsOK=false;
	m_bManuMarkIsEnd=false;
	m_bManuRun = GetControl().QueryIOBit(IMANURUNBTN);

	SetTimer(1,500,NULL);
	SetTimer(2,500,NULL);
}

void CImageParaSetView::EndManuMark()
{
	KillTimer(1);
	KillTimer(2);
	
	m_bManuMarkIsEnd=true;
}

void CImageParaSetView::OnButtonCorrectionTable()			//20180417
{
	char ez[256]={""};
	int nHead,label;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

	UpdateData();

//设定加工轴
	int nSelect = AfxMessageBox("左侧平台  选择 '是'\n 右侧平台 选择 '否'\n取消操作 选择 '取消'\n",MB_YESNOCANCEL);
	if (nSelect == IDYES)
		nHead=0;
	else if (nSelect == IDNO)
		nHead=1;	
	else
		return;

	Delay(500);

//设定上下区域
/*
	nSelect = AfxMessageBox("上面区域  选择 '是'\n 下面区域 选择 '否'\n取消操作 选择 '取消'\n",MB_YESNOCANCEL);
	if (nSelect == IDYES)
		label=0;
	else if (nSelect == IDNO)
		label=1;	
	else
		return;
*/
	label=0;																//20200414

//平台真空吸附并判断
	GetControl().ChannelOutput(OFANPOWERON,IO_ON); 
	Delay(500);

	if(!GetControl().TableAdsorbInProc(nHead))
	{
		GetControl().ResetTableStatus();
		return;
	}

//打开CCD光源
	GetControl().LightTurnOn(OUTERMAINPATTERN);	

	nSelect = AfxMessageBox("请确认已将校正原点移至CCD视场中，继续请选择  '是'，取消请选择  '否'\n",MB_YESNO);
	if (nSelect == IDNO)
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

//设定平台校正状态
	GetDoc().SetTableIsCali(nHead,label,true);

//识别玻璃尺原点和水平点
	CArray<Coord, Coord> Dev;
	HoleCoordV crdTestV;

	Dev.RemoveAll();	
	crdTestV.clear();

//	crdTestV.push_back(Coord(290000,DIVIDINGLINE));						
	crdTestV.push_back(GetControl().GetTablePos());								//20180525

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,2))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

	Delay(500);

	Coord crd0;
	crd0.x=GetControl().GetPos(AXISTABX);
	crd0.y=GetControl().GetPos(AXISTABY);
	crd0.x+=Dev.GetAt(0).x;
	crd0.y+=Dev.GetAt(0).y;

	Dev.RemoveAll();
	crdTestV.clear();

	crdTestV.push_back(Coord(crd0.x-585000,crd0.y));							//20200414
//	crdTestV.push_back(Coord(crd0.x-580000,crd0.y));							//20180525

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,2))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

	Delay(500);

	Coord crd1;
	crd1.x=GetControl().GetPos(AXISTABX);
	crd1.y=GetControl().GetPos(AXISTABY);
	crd1.x+=Dev.GetAt(0).x;
	crd1.y+=Dev.GetAt(0).y;

	CString strMessage;
	strMessage.Format("玻璃尺定位完成，Y向误差为%d，继续请选择  '是'，取消请选择  '否'\n",crd1.y-crd0.y);

	nSelect = AfxMessageBox(strMessage,MB_YESNO);
	if (nSelect == IDNO)
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

//采集玻璃尺校正数据
	HoleCoordV crdCommandV;
	Coord crdCCDPos;

// 	int tempXPoints=14;
// 	int tempYPoints=11;
//	int interval=45000;
//	int offset=0;
// 	int tempXPoints=30;															//20180525
// 	int tempYPoints=24;
//	int interval=20000;
//	int offset=20000;
 	int tempXPoints=14;															//20200414
 	int tempYPoints=18;
	int interval=45000;
	int offset=0;

	double temperature=m_dbTestTemperature;										//玻璃尺放置环境温度
	double scaleTemperature=8.1/1000000.0;										//玻璃尺线膨胀系数 8.067/1000000.0
	double scaleGlass=1+(temperature-22.0)*scaleTemperature;					//玻璃尺使用标准温度为22度
    double rotateRadian=atan((double)(crd1.y-crd0.y)/(double)(crd1.x-crd0.x));	//玻璃尺放置旋转弧度

	Dev.RemoveAll();
	crdTestV.clear();
	crdCommandV.clear();

	for(int i=0;i<tempYPoints;i++)		
	{
		for(int j=0;j<tempXPoints;j++)			
		{
			crdCCDPos.x=crd0.x-j*interval*scaleGlass;
/*
			if(label==0)
				crdCCDPos.y=crd0.y-offset+i*interval*scaleGlass;
			else
				crdCCDPos.y=crd0.y+offset-i*interval*scaleGlass;
*/
			crdCCDPos.y=crd0.y+offset-i*interval*scaleGlass;						//20200414

			crdCommandV.push_back(crdCCDPos);

			crdCCDPos=ToRotateTable(crd0,rotateRadian,crdCCDPos);

			crdTestV.push_back(crdCCDPos);
		}
	}

	if(!GetControl().TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,3))
	{
		GetControl().LightTurnOff();		
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		return;
	}

//关闭CCD光源
	GetControl().LightTurnOff();
	
	GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);

//生成平台校正参数
	HoleCoordV crdActualV;

	for(int m=0; m<tempYPoints*tempXPoints;m++)
	{
		crdCCDPos.x=crdTestV[m].x+Dev.GetAt(m).x;
		crdCCDPos.y=crdTestV[m].y+Dev.GetAt(m).y;

		crdCCDPos=ToRotateTable(crd0,-rotateRadian,crdCCDPos);		//------------|

		crdActualV.push_back(crdCCDPos);
	}

	CogSetNPointToNPointDOFConstants(cogNPointToNPointDOFScalingAspectRotationSkewAndTranslation);

//	if(!CogTableTransform(nHead,label,crdCommandV,crdActualV))		//------------|
	if(!CogTableTransform(0,label,crdCommandV,crdActualV))			//20200414
//	if(!CogTableTransform(nHead,label,crdTestV,crdActualV))
	{
		AfxMessageBox("平台2D变换参数计算错误，请确认！");
		return;
	}

//保存玻璃尺校正数据 (crdCommandV : crdActualV)
	CIniFile IniFile;
	CString str,path,strName;
	char buf[24];

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
//	strName.Format("param\\TableCorData%d%d",nHead,label);
	strName.Format("param\\TableCorData0%d",label);					//20200414
	IniFile.SetName(strName);
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		char timebuf[128],daybuf[128]; 
		tzset();
		_strtime(timebuf);
		_strdate(daybuf);

		sprintf(buf,"%s-%s\0",daybuf,timebuf);

		IniFile.WriteSection("TablePosErr");
		IniFile.WriteItemString("TestTime",buf);
		IniFile.WriteItemInt("ParallelErr",crd1.y-crd0.y);
 		IniFile.WriteString("\n");
       
	    for(int n=0; n<tempYPoints*tempXPoints;n++)
		{

			sprintf(buf,"Pos%dCX\0",n);
			IniFile.WriteItemInt(buf,crdCommandV[n].x);
			sprintf(buf,"Pos%dCY\0",n);
			IniFile.WriteItemInt(buf,crdCommandV[n].y);
			sprintf(buf,"Pos%dAX\0",n);
			IniFile.WriteItemInt(buf,crdActualV[n].x);
			sprintf(buf,"Pos%dAY\0",n);
			IniFile.WriteItemInt(buf,crdActualV[n].y);
/*
			sprintf(buf,"Pos%dCX\0",n);
			IniFile.WriteItemInt(buf,crdTestV[n].x);
			sprintf(buf,"Pos%dCY\0",n);
			IniFile.WriteItemInt(buf,crdTestV[n].y);
			sprintf(buf,"Pos%dAX\0",n);
			IniFile.WriteItemInt(buf,crdActualV[n].x);
			sprintf(buf,"Pos%dAY\0",n);
			IniFile.WriteItemInt(buf,crdActualV[n].y);
*/
 			IniFile.WriteString("\n");
		}

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13012),256);
		AfxMessageBox(ez,MB_OK);//"无法保存 运动参数！"
#ifdef USELOG
		GetLog().Append_pro(10100,"SaveMotionParam");//"无法保存 运动参数"
#endif
	}

//复位平台校正状态	
	GetDoc().SetTableIsCali(nHead,label,false);

	if(label==0)
		AfxMessageBox("玻璃尺校正数据采集完成，请将玻璃尺放至安全位置！");
	else
		AfxMessageBox("玻璃尺校正数据采集完成！");	
}

void CImageParaSetView::OnBtMarktest()									//20190412
{
	// TODO: Add your control notification handler code here
	CString str;
	Coord crd;
	HoleCoordV crdV;
	double dbDevX,dbDevY;
	Coord crd0=GetControl().GetTablePos();
	int offsetX[9]={0,1,1,0,-1,-1,-1,0,1};
	int offsetY[9]={0,0,1,1,1,0,-1,-1,-1};

	UpdateData();

	for(int j=0;j<9;j++)
	{
		dbDevX=0.0;
		dbDevY=0.0;
		crdV.clear();

		crd.x = offsetX[j]*atol(m_ulStepLength);
		crd.y = offsetY[j]*atol(m_ulStepLength);

//		str.Format("crd0.x=%d,crd0.y=%d\ncrd.x=%d,crd.y=%d",crd0.x,crd0.y,crd.x,crd.y);
//		AfxMessageBox(str);

		crdV.push_back(crd0+crd);

//		str.Format("crdV[0].x=%d,crdV[0].y=%d",crdV[0].x,crdV[0].y);
//		AfxMessageBox(str);

		if(GetControl().TargetFindInProc(0,1,crdV,FIRSTMARKPOS,dbDevX,dbDevY)==0)
		{
			str.Format("平台指令：crd.x=%d,crd.y=%d\n测量结果：devX=%6.1f,devY=%6.1f",crd.x,crd.y,dbDevX,dbDevY);
			AfxMessageBox(str);
		}
		else
			return;
	}
}
