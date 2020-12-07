// MotionControlTestView.cpp : implementation file
//

#include "stdafx.h"
#include "LaserSystem.h"
#include "MotionControlTestView.h"
#include "operatecontrol.h"
#include "Shared Classes/ListReport/ListItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotionControlTestView

IMPLEMENT_DYNCREATE(CMotionControlTestView, TVisualFormView)

CMotionControlTestView::CMotionControlTestView()
	: TVisualFormView(CMotionControlTestView::IDD)

{
	//{{AFX_DATA_INIT(CMotionControlTestView)
	m_strMoveToPos1 = "-20000";
	m_strMoveToPos2 =  "20000";
	m_ulStepLength = 10000;
	m_IntLoadTime = 60;
	m_IntUnLoadTime = 10;
	//}}AFX_DATA_INIT
}

CMotionControlTestView::~CMotionControlTestView()
{
}

void CMotionControlTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotionControlTestView)
	DDX_Control(pDX, IDC_EDT_STEPLENGTH, m_edtStepLength);
	DDX_Control(pDX, IDC_EDT_POS2, m_edtMoveToPos2);
	DDX_Control(pDX, IDC_EDT_POS1, m_edtMoveToPos1);
//	DDX_Control(pDX, IDC_BT_LEFTHAND_D, m_btnLeftHandD);
//	DDX_Control(pDX, IDC_BT_RIGHTHAND_D, m_btnRightHandD);
//	DDX_Control(pDX, IDC_BT_UN_RIGHTHAND_D, m_btnUnRightHandD);
//	DDX_Control(pDX, IDC_BT_UN_LEFTHAND_D, m_btnUnLeftHandD);
//	DDX_Control(pDX, IDC_BT_UNLOADTEST, m_btnUnLoadTest);
	DDX_Control(pDX, IDC_BT_UNLOADPOS, m_btnTableUnLoadPos);
//	DDX_Control(pDX, IDC_BT_UN_RIGHTSORB, m_btnUnRightSorb);
//	DDX_Control(pDX, IDC_BT_UN_RIGHTHAND_UD, m_btnUnRightHandUD);
//	DDX_Control(pDX, IDC_BT_UN_PUTBOADPOS, m_btnUnPutBoadPos);
//	DDX_Control(pDX, IDC_BT_UN_LOADSTH_UP, m_btnUnLoadStHUp);
//	DDX_Control(pDX, IDC_BT_UN_LOADSTH_DOWN, m_btnUnLoadStHDown);
//	DDX_Control(pDX, IDC_BT_UN_LEFTSORB, m_btnUnLeftSorb);
//	DDX_Control(pDX, IDC_BT_UN_LEFTHAND_UD, m_btnLeftHand_Ud);
//	DDX_Control(pDX, IDC_BT_UN_GETTUNESPOS, m_btnUnTunePos);
//	DDX_Control(pDX, IDC_BT_UN_GETTRANSPOS, m_btnUnTransPos);
//	DDX_Control(pDX, IDC_BT_UN_GETBOADPOS, m_btnUnGetBoadPos);
//	DDX_Control(pDX, IDC_BT_LOADTEST, m_btnLoadTest);
//	DDX_Control(pDX, IDC_BT_PUTBOADPOS, m_btnPutBoadPos);
//	DDX_Control(pDX, IDC_BT_LOADSTH_UP, m_btnLoadStHUp);
//	DDX_Control(pDX, IDC_BT_LOADSTH_DOWN, m_btnLoadStHDown);
	DDX_Control(pDX, IDC_BT_LOADPOS, m_btnTableLoadPos);
//	DDX_Control(pDX, IDC_BT_LEFTSORB, m_btnLeftSorb);
//	DDX_Control(pDX, IDC_BT_LEFTHAND_UD, m_btnLeftHandUD);
//	DDX_Control(pDX, IDC_BT_GETTUNESPOS, m_btnGetTunePos);
//	DDX_Control(pDX, IDC_BT_GETTRANSPOS, m_btnTransPos);
//	DDX_Control(pDX, IDC_BT_GETBOADPOS, m_btnGetBoadPos);
//	DDX_Control(pDX, IDC_BT_SNAPIM, m_btnSnapIm);
//	DDX_Control(pDX, IDC_BT_SNAPEX, m_btnSnapEx);
//	DDX_Control(pDX, IDC_BT_RIGHTSORB, m_btnRightSorb);
//	DDX_Control(pDX, IDC_BT_RIGHTHAND_UD, m_btnRightHandUD);
	DDX_Control(pDX, IDC_ST_PLIMIT, m_sPLimit);
	DDX_Control(pDX, IDC_ST_NLIMIT, m_sNLimit);
	DDX_Control(pDX, IDC_ST_HOME, m_sHome);
	DDX_Text(pDX, IDC_EDT_POS1, m_strMoveToPos1);
	DDX_Text(pDX, IDC_EDT_POS2, m_strMoveToPos2);
	DDX_Text(pDX, IDC_EDT_STEPLENGTH, m_ulStepLength);
	DDX_Control(pDX, IDC_BT_RESETCARD3, m_btnResetCard3);
	DDX_Control(pDX, IDC_BT_RESETCARD2, m_btnResetCard2);
	DDX_Control(pDX, IDC_BT_RESETCARD1, m_btnResetCard1);
	DDX_Control(pDX, IDC_CMB_SELECTAXIS, m_cmbSelectAxis);
	DDX_Control(pDX, IDC_BT_MANU_STOP2, m_btnManuStop2);
	DDX_Control(pDX, IDC_BT_MANU_STOP, m_btnManuStop);
	DDX_Control(pDX, IDC_BT_MANU_UP, m_btnManuUp);
	DDX_Control(pDX, IDC_BT_MANU_RIGHT, m_btnManuRight);
	DDX_Control(pDX, IDC_BT_MANU_LEFT, m_btnManuLeft);
	DDX_Control(pDX, IDC_BT_MANU_DOWN, m_btnManuDown);
	DDX_Control(pDX, IDC_BT_MOVETO_P2, m_btnMoveToP2);
	DDX_Control(pDX, IDC_BT_MOVETO_P1, m_btnMoveToP1);
	DDX_Control(pDX, IDC_BT_AXISW_HOME, m_btnHomeW);
	DDX_Control(pDX, IDC_BT_AXISZ_HOME, m_btnHomeZ);
	DDX_Control(pDX, IDC_BT_AXISY_HOME, m_btnHomeY);
	DDX_Control(pDX, IDC_BT_AXISX_HOME, m_btnHomeX);
	DDX_Control(pDX, IDC_BT_AXISW_HOME_1, m_btnHomeW1);
	DDX_Control(pDX, IDC_BT_AXISZ_HOME_1, m_btnHomeZ1);
//	DDX_Control(pDX, IDC_BT_AXISY_HOME_1, m_btnHomeY1);
//	DDX_Control(pDX, IDC_BT_AXISX_HOME_1, m_btnHomeX1);
//	DDX_Control(pDX, IDC_BT_AXISY_HOME_2, m_btnHomeY2);
//	DDX_Control(pDX, IDC_BT_AXISX_HOME_2, m_btnHomeX2);
	DDX_Text(pDX, IDC_EDIT_LOADTIME, m_IntLoadTime);
	DDV_MinMaxInt(pDX, m_IntLoadTime, 40, 1000);
	DDX_Text(pDX, IDC_EDIT_UNLOADTIME, m_IntUnLoadTime);
	DDV_MinMaxInt(pDX, m_IntUnLoadTime, 5, 30);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CMotionControlTestView, TVisualFormView)
	//{{AFX_MSG_MAP(CMotionControlTestView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_AXISW_HOME, On_AxisW_Home)
	ON_BN_CLICKED(IDC_BT_AXISY_HOME, On_AxisY_Home)
	ON_BN_CLICKED(IDC_BT_AXISZ_HOME, On_AxisZ_Home)
	ON_BN_CLICKED(IDC_BT_AXISX_HOME, On_AxisX_Home)
	ON_BN_CLICKED(IDC_BT_AXISZ_HOME_1, On_AxisLF_Home)
	ON_BN_CLICKED(IDC_BT_AXISW_HOME_1, On_AxisRF_Home)
	ON_BN_CLICKED(IDC_BT_MOVETO_P1, OnMoveToP1)
	ON_BN_CLICKED(IDC_BT_MOVETO_P2, OnMoveToP2)
	ON_BN_CLICKED(IDC_BT_MANU_STOP2, OnManuStop2)
	ON_BN_CLICKED(IDC_BT_MANU_STOP, OnManuStop)
	ON_BN_CLICKED(IDC_BT_MANU_UP, OnManuUp)
	ON_BN_CLICKED(IDC_BT_MANU_DOWN, OnManuDown)
	ON_BN_CLICKED(IDC_BT_MANU_LEFT, OnManuLeft)
	ON_BN_CLICKED(IDC_BT_MANU_RIGHT, OnManuRight)
	ON_BN_CLICKED(IDC_BT_STOPEXCCARD1, OnBtStopexcCard1)
	ON_BN_CLICKED(IDC_BT_STOPEXCCARD2, OnBtStopexcCard2)
	ON_BN_CLICKED(IDC_BT_RESETCARD1, OnResetCard1)
	ON_BN_CLICKED(IDC_BT_RESETCARD2, OnResetCard2)
	ON_BN_CLICKED(IDC_BT_RESETCARD3, OnResetCard3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_LOADPOS, OnBtLoadpos)
	ON_BN_CLICKED(IDC_BT_UNLOADPOS, OnBtUnloadpos)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BTN_AGVL, OnBtnAgvl)
	ON_BN_CLICKED(IDC_BTN_AGVUL, OnBtnAgvul)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BTN_AGVULANDL, OnBtnAgvulandl)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INPUTCHECK,OnCheckLimit)
	ON_MESSAGE(WM_INPUTUNCHECK,OnUncheckLimit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotionControlTestView diagnostics

#ifdef _DEBUG
void CMotionControlTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMotionControlTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMotionControlTestView message handlers

int CMotionControlTestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    m_hLedON = AfxGetApp()->LoadIcon(IDI_LEDON);
    m_hLedOFF = AfxGetApp()->LoadIcon(IDI_LEDOFF);
	
	HICON m_hIcon1 = AfxGetApp()->LoadIcon(IDI_HOME);
	
	m_btnHomeX.SetIcon(m_hIcon1,m_hIcon1);
	m_btnHomeY.SetIcon(m_hIcon1,m_hIcon1);
	m_btnHomeZ.SetIcon(m_hIcon1,m_hIcon1);
	m_btnHomeW.SetIcon(m_hIcon1,m_hIcon1);
//	m_btnHomeX1.SetIcon(m_hIcon1,m_hIcon1);
//	m_btnHomeY1.SetIcon(m_hIcon1,m_hIcon1);
	m_btnHomeZ1.SetIcon(m_hIcon1,m_hIcon1);
	m_btnHomeW1.SetIcon(m_hIcon1,m_hIcon1);
//	m_btnHomeX2.SetIcon(m_hIcon1,m_hIcon1);
//	m_btnHomeY2.SetIcon(m_hIcon1,m_hIcon1);
	
	m_hIcon1 = AfxGetApp()->LoadIcon(IDI_RESETCARD);
	m_btnResetCard1.SetIcon(m_hIcon1,m_hIcon1);
	m_btnResetCard2.SetIcon(m_hIcon1,m_hIcon1);
	m_btnResetCard3.SetIcon(m_hIcon1,m_hIcon1);
	
	m_btnMoveToP1.SubclassDlgItem(IDC_BT_MOVETO_P1,this);
	m_btnMoveToP1.SetIcon(IDI_MOVELEFT,IDI_MOVELEFT);
	
	m_btnMoveToP2.SubclassDlgItem(IDC_BT_MOVETO_P2,this);
	m_btnMoveToP2.SetIcon(IDI_MOVERIGHT,IDI_MOVERIGHT);
	
    m_btnManuUp.SubclassDlgItem(IDC_BT_MANU_UP,this);
	m_btnManuUp.SetIcon(IDI_ARROWUP,IDI_ARROWUP);
	
    m_btnManuDown.SubclassDlgItem(IDC_BT_MANU_DOWN,this);
	m_btnManuDown.SetIcon(IDI_ARROWDOWN,IDI_ARROWDOWN);
	
    m_btnManuLeft.SubclassDlgItem(IDC_BT_MANU_LEFT,this);
	m_btnManuLeft.SetIcon(IDI_ARROWLEFT,IDI_ARROWLEFT);
	
    m_btnManuRight.SubclassDlgItem(IDC_BT_MANU_RIGHT,this);
	m_btnManuRight.SetIcon(IDI_ARROWRIGHT,IDI_ARROWRIGHT);
	
    m_btnManuStop.SubclassDlgItem(IDC_BT_MANU_STOP,this);
	m_btnManuStop.SetIcon(IDI_STOP,IDI_STOP);
	
    m_btnManuStop2.SubclassDlgItem(IDC_BT_MANU_STOP2,this);
	m_btnManuStop2.SetIcon(IDI_STOP,IDI_STOP);
/*	
	m_btnGetBoadPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnGetTunePos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnPutBoadPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnTransPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnUnGetBoadPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnUnPutBoadPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnUnTransPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnUnTunePos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnUnLeftSorb.SetIcon(IDI_SORB,IDI_SORB);
	m_btnUnRightSorb.SetIcon(IDI_SORB,IDI_SORB);
	m_btnRightSorb.SetIcon(IDI_SORB,IDI_SORB);
	m_btnLeftSorb.SetIcon(IDI_SORB,IDI_SORB);	
	
	m_btnLeftHand_Ud.SetIcon(IDI_UP,IDI_UP);
	m_btnUnRightHandUD.SetIcon(IDI_UP,IDI_UP);
	m_btnLeftHandUD.SetIcon(IDI_UP,IDI_UP);
	m_btnRightHandUD.SetIcon(IDI_UP,IDI_UP);
	
	m_btnLeftHandD.SetIcon(IDI_DOWN,IDI_DOWN);
	m_btnRightHandD.SetIcon(IDI_DOWN,IDI_DOWN);
	m_btnUnRightHandD.SetIcon(IDI_DOWN,IDI_DOWN);
	m_btnUnLeftHandD.SetIcon(IDI_DOWN,IDI_DOWN);
	
	m_btnUnLoadStHUp.SetIcon(IDI_UP,IDI_UP);
	m_btnUnLoadStHDown.SetIcon(IDI_DOWN,IDI_DOWN);
	m_btnLoadStHUp.SetIcon(IDI_UP,IDI_UP);
	m_btnLoadStHDown.SetIcon(IDI_DOWN,IDI_DOWN);
	m_btnSnapIm.SetIcon(IDI_SNAP,IDI_SNAP);
	m_btnSnapEx.SetIcon(IDI_SNAP,IDI_SNAP);
*/
	m_btnTableLoadPos.SetIcon(IDI_MOVE,IDI_MOVE);
	m_btnTableUnLoadPos.SetIcon(IDI_MOVE,IDI_MOVE);

//	m_btnUnLoadTest.SetIcon(IDI_TEST,IDI_TEST);
//	m_btnLoadTest.SetIcon(IDI_TEST,IDI_TEST);

	return 0;
}

void CMotionControlTestView::On_AxisW_Home() 
{
	m_btnHomeW.EnableWindow(FALSE);
	GetControl().HomeAPT();
#ifdef USELOG
	GetLog().Append_pro(10040,20018);//"光圈选择","回零"
#endif
    m_btnHomeW.EnableWindow(TRUE);
}

void CMotionControlTestView::On_AxisZ_Home() 
{
	 m_btnHomeZ.EnableWindow(FALSE);
	 GetControl().HomeBET();
#ifdef USELOG
	GetLog().Append_pro(10041,20018);//"光束调节","回零"
#endif
    m_btnHomeZ.EnableWindow(TRUE);
}

void CMotionControlTestView::On_AxisY_Home() 
{
	char ez[256]={""};//ly 20110404
	if(GetControl().QueryIOBit(MOTIONSTOPRESET))
	{
		GetDoc().SetMachinePowerState(FALSE);
		strncpy(ez,GetLang().GetWarningText(41003),256);
		if(AfxMessageBox(ez,MB_OKCANCEL)== IDCANCEL)//"机器没有上电，请上电!"
			return ;
	}

    m_btnHomeY.EnableWindow(FALSE);

#ifdef USEDMSYSTEM
	GetXYMotion().Home(AXISTABY);
#else
	GetMotion().Home(AXISTABY);
#endif

	GetDoc().SetPos(AXISTABY,0);//ly add 20110928
#ifdef USELOG
	 GetLog().Append_pro(10042,20018);//"Y轴回零","回零"
#endif

#ifdef USEDMSYSTEM
	GetXYMotion().WaitStopWhenProgramming(AXISTABY);
#else
	GetMotion().WaitStopWhenProgramming(AXISTABY);
#endif

	GetControl().SetTablePosY(0);						//20180417
    m_btnHomeY.EnableWindow(TRUE);	
}

void CMotionControlTestView::On_AxisX_Home() 
{
	char ez[256]={""};//ly 20110404
	if(GetControl().QueryIOBit(MOTIONSTOPRESET))
	{
		GetDoc().SetMachinePowerState(FALSE);
		strncpy(ez,GetLang().GetWarningText(41003),256);
		if(AfxMessageBox(ez,MB_OKCANCEL)== IDCANCEL)//"机器没有上电，请上电!"
			return ;
	}
  
	m_btnHomeX.EnableWindow(FALSE);

#ifdef USEDMSYSTEM
	GetXYMotion().Home(AXISTABX);
#else
	GetMotion().Home(AXISTABX);
#endif

	GetDoc().SetPos(AXISTABX,0);//ly add 20110928
#ifdef USELOG
	GetLog().Append_pro(10043,20018);//"X轴回零","回零"
#endif

#ifdef USEDMSYSTEM
	GetXYMotion().WaitStopWhenProgramming(AXISTABX);
#else
	GetMotion().WaitStopWhenProgramming(AXISTABX);
#endif

	GetControl().SetTablePosX(0);						//20180417
    m_btnHomeX.EnableWindow(TRUE);	
}

void CMotionControlTestView::On_AxisLF_Home() 
{    
	m_btnHomeZ1.EnableWindow(FALSE);
	GetMotion().Home(AXISLEFTZ);
#ifdef USELOG
	GetLog().Append_pro(10044,20018);//"左侧调焦","回零"
#endif
	GetMotion().WaitStopWhenProgramming(AXISLEFTZ);
    m_btnHomeZ1.EnableWindow(TRUE);
}

void CMotionControlTestView::On_AxisRF_Home() 
{ 
	m_btnHomeW1.EnableWindow(FALSE);
	GetMotion().Home(AXISRIGHTZ);
#ifdef USELOG
	 GetLog().Append_pro(10045,20018);//"右侧调焦","回零"
#endif  
	GetMotion().WaitStopWhenProgramming(AXISRIGHTZ);
    m_btnHomeW1.EnableWindow(TRUE);
}

void CMotionControlTestView::OnMoveToP1() 
{
	UpdateData();
	char ez[256]={""};//ly 20110404
	long lMoveToPos1 = atol(m_strMoveToPos1);
	if(abs(lMoveToPos1)>MAXTESTPOS)
	{		
		strncpy(ez,GetLang().GetWarningText(21033),256);
		AfxMessageBox(ez);//"设定的测试位置过大!"
		GetLog().Append_pro(10046,20021,30006);//"设定的测试位置过大！","电机测试","负方向"
		return ;
	}

	UINT ulAxis = GetCurOperateAxis();

	GetControl().MoveTo(ulAxis,lMoveToPos1);

#ifdef USELOG
	int iAxis = m_cmbSelectAxis.GetCurSel();
	CString str;
	strncpy(ez,GetLang().GetWarningText(31010),256);
	str.Format(ez,iAxis);//"第%d轴"
	GetLog().Append_pro(str,20021,30006);//"电机测试","负方向"
#endif
}

void CMotionControlTestView::OnMoveToP2() 
{
	UpdateData();
	char ez[256]={""};//ly 20110404
long lMoveToPos2 = atol(m_strMoveToPos2);
	if(abs(lMoveToPos2)>MAXTESTPOS)
	{		
		strncpy(ez,GetLang().GetWarningText(21033),256);
		AfxMessageBox(ez);//"设定的测试位置过大!"
		GetLog().Append_pro(10046,20021,30007);//"设定的测试位置过大！","电机测试","正方向"
		return ;
	}

	UINT ulAxis = GetCurOperateAxis();

	GetControl().MoveTo(ulAxis,lMoveToPos2);
#ifdef USELOG
	int iAxis = m_cmbSelectAxis.GetCurSel();
	CString str;
	strncpy(ez,GetLang().GetWarningText(31010),256);
	str.Format(ez,iAxis);//"第%d轴"
		GetLog().Append_pro(str,20021,30007);//"电机测试","正方向"
#endif
}

void CMotionControlTestView::OnManuStop2() 
{
	UINT ulAxis = GetCurOperateAxis();
	char ez[256] = {""};
	GetMotion().Stop(ulAxis);
#ifdef USELOG
	int iAxis = m_cmbSelectAxis.GetCurSel();
	CString str;
	strncpy(ez,GetLang().GetWarningText(31010),256);
	str.Format(ez,iAxis);//"第%d轴"
	GetLog().Append_pro(10047,20021,str);//"停止电机移动","电机测试"
#endif
}

void CMotionControlTestView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("MotionControlTest","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_AXISX_HOME",szRead,40);
	SetDlgItemText(IDC_BT_AXISX_HOME,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_AXISY_HOME",szRead,40);
	SetDlgItemText(IDC_BT_AXISY_HOME,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_AXISZ_HOME_1",szRead,40);
	SetDlgItemText(IDC_BT_AXISZ_HOME_1,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_AXISW_HOME_1",szRead,40);
	SetDlgItemText(IDC_BT_AXISW_HOME_1,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_AXISZ_HOME",szRead,40);
	SetDlgItemText(IDC_BT_AXISZ_HOME,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_AXISW_HOME",szRead,40);
	SetDlgItemText(IDC_BT_AXISW_HOME,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_MOVETO_P1",szRead,40);
	SetDlgItemText(IDC_BT_MOVETO_P1,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_MOVETO_P2",szRead,40);
	SetDlgItemText(IDC_BT_MOVETO_P2,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC7",szRead,40);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_RESETCARD1",szRead,40);
	SetDlgItemText(IDC_BT_RESETCARD1,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_RESETCARD2",szRead,40);
	SetDlgItemText(IDC_BT_RESETCARD2,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_STATIC9",szRead,40);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_UNLOADPOS",szRead,40);
	SetDlgItemText(IDC_BT_UNLOADPOS,szRead);
	GetLang().GetUIText("MotionControlTest","IDC_BT_LOADPOS",szRead,40);
	SetDlgItemText(IDC_BT_LOADPOS,szRead);
}

void CMotionControlTestView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	char szRead[20]={""};
	m_cmbSelectAxis.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10101),20);
	m_cmbSelectAxis.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10102),20);
	m_cmbSelectAxis.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10103),20);
	m_cmbSelectAxis.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10104),20);
	m_cmbSelectAxis.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10105),20);
	m_cmbSelectAxis.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10106),20);
	m_cmbSelectAxis.AddString(szRead);
	
	m_edtMoveToPos1.SetParseType ( SES_NUMBERS | SES_SIGNED ); 
    m_edtMoveToPos1.SetRange(-MAXTESTPOS,MAXTESTPOS);
	m_edtMoveToPos2.SetParseType ( SES_NUMBERS | SES_SIGNED );
    m_edtMoveToPos2.SetRange(-MAXTESTPOS,MAXTESTPOS);
	m_edtStepLength.SetParseType ( SES_NUMBERS );
	m_cmbSelectAxis.SetCurSel(0);

//	if (2==GetDoc().GetLoadOptimize())
//	{
//		m_IntLoadTime=GetDoc().GetLoadPCBTime();
//		m_IntUnLoadTime=GetDoc().GetUnLoadPCBTime();
//	}

	if(!GetDoc().GetLAndULSystem())										//20200506
	{
		GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BT_STOPEXCCARD1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BT_STOPEXCCARD2)->ShowWindow(SW_HIDE);
	}
	else
	{
#ifdef NOONEKEY
		GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BT_STOPEXCCARD1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BT_STOPEXCCARD2)->ShowWindow(SW_HIDE);
#else
		GetDlgItem(IDC_STATIC10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BT_STOPEXCCARD1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BT_STOPEXCCARD2)->ShowWindow(SW_SHOW);
#endif
	}

#ifdef HIKAGV
	GetDlgItem(IDC_BTN_AGVL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_AGVUL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_AGVULANDL)->ShowWindow(SW_SHOW);
#else
	GetDlgItem(IDC_BTN_AGVL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_AGVUL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_AGVULANDL)->ShowWindow(SW_HIDE);
#endif
}

void CMotionControlTestView::OnManuStop() 
{
	GetMotion().Stop(AXISTABX);
	GetMotion().Stop(AXISTABY);
}

void CMotionControlTestView::OnManuUp() 
{
	UpdateData();

	m_btnManuUp.EnableWindow(FALSE);
	m_btnManuDown.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABY);
	GetControl().MoveTo(AXISTABY,GetControl().GetPos(AXISTABY)+m_ulStepLength);
    GetControl().WaitAxisStop(AXISTABY);

	Delay(500);

	m_btnManuUp.EnableWindow(true);
	m_btnManuDown.EnableWindow(true);
}

void CMotionControlTestView::OnManuDown() 
{
	UpdateData();

	m_btnManuUp.EnableWindow(FALSE);
	m_btnManuDown.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABY);
    GetControl().MoveTo(AXISTABY,GetControl().GetPos(AXISTABY)-m_ulStepLength);
    GetControl().WaitAxisStop(AXISTABY);

	Delay(500);
	
	m_btnManuUp.EnableWindow(true);
	m_btnManuDown.EnableWindow(true);
}

void CMotionControlTestView::OnManuLeft() 
{
	UpdateData();

	m_btnManuRight.EnableWindow(FALSE);
	m_btnManuLeft.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABX);
    GetControl().MoveTo(AXISTABX,GetControl().GetPos(AXISTABX)-m_ulStepLength);
    GetControl().WaitAxisStop(AXISTABX);

	Delay(500);

	m_btnManuRight.EnableWindow(true);
	m_btnManuLeft.EnableWindow(true);
}

void CMotionControlTestView::OnManuRight() 
{
	UpdateData();

	m_btnManuRight.EnableWindow(FALSE);
	m_btnManuLeft.EnableWindow(FALSE);

    GetControl().WaitAxisStop(AXISTABX);
    GetControl().MoveTo(AXISTABX,GetControl().GetPos(AXISTABX)+m_ulStepLength);
    GetControl().WaitAxisStop(AXISTABX);

	Delay(500);

	m_btnManuRight.EnableWindow(true);
	m_btnManuLeft.EnableWindow(true);
}

UINT CMotionControlTestView::GetCurOperateAxis()
{
	UINT nrtnAxis;
	UpdateData();

	int iAxis = m_cmbSelectAxis.GetCurSel();
	switch(iAxis)
	{
	case 0:
		nrtnAxis = AXISTABX;
		break;
	case 1:
		nrtnAxis = AXISTABY;
		break;
	case 2:
		nrtnAxis = AXISBETPRI;
		break;
	case 3:
		nrtnAxis = AXISBETSUB;
		break;
	case 4: //升降
		nrtnAxis = AXISLEFTZ;
		break;		
	case 5: //平移
		nrtnAxis = AXISRIGHTZ;
		break;
	case 6:
		nrtnAxis = AXISAPT;
		break;
//	case 7:
//		nrtnAxis = AXISRIGHTZ;
//		break;
//	case 8://升降
//		nrtnAxis = AXISUNLOADX;
//		break;
//	case 9://平移
//		nrtnAxis = AXISUNLOADY;
//		break;
//	case 10://平移
//		nrtnAxis = AXISBETSUB;
//		break;
	}
	return nrtnAxis;
}

void CMotionControlTestView::OnBtStopexcCard1()
{	
	DWORD dwThreadId;
	CloseHandle(CreateThread(NULL,0,RunLoadOnce,(LPVOID)this,0,&dwThreadId));
}

DWORD WINAPI RunLoadOnce(LPVOID pM)
{
	((CMotionControlTestView*)pM)->LoadOnce();

	return 0;
}

DWORD CMotionControlTestView::LoadOnce()									//20190723
//void CMotionControlTestView::OnBtStopexcCard1() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return 0;
	}

	if(GetDoc().GetProcessState()!=CControl::AUTOPROC)
	{
		AfxMessageBox("请先选择自动上下料方式!");
		return 0;
	}

	GetControl().SetRunState(CControl::OPERATEWITHHAND);						//20190723
	OnActivateView(true,this,this);
	
	GetLog().Append_pro("一键上料","流程控制");					//20200720 增加

	GetDoc().SetFault(false);

	int pathMode=1;
	if(!GetControl().PutPCBToTable(pathMode))
	{
		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);

		GetDoc().SetFault(false);
		return 0;
	}

	AfxMessageBox("上料放料已完成!");

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

	GetDoc().SetFault(false);
	return 0;
}

void CMotionControlTestView::OnBtStopexcCard2()
{	
	DWORD dwThreadId;
	CloseHandle(CreateThread(NULL,0,RunUnloadOnce,(LPVOID)this,0,&dwThreadId));
}

DWORD WINAPI RunUnloadOnce(LPVOID pM)
{
	((CMotionControlTestView*)pM)->UnloadOnce();

	return 0;
}

DWORD CMotionControlTestView::UnloadOnce()									//20190723
//void CMotionControlTestView::OnBtStopexcCard2() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return 0;
	}

	if(GetDoc().GetProcessState()!=CControl::AUTOPROC)
	{
		AfxMessageBox("请先选择自动上下料方式!");
		return 0;
	}

	GetControl().SetRunState(CControl::OPERATEWITHHAND);					//20190723
	OnActivateView(true,this,this);

	GetLog().Append_pro("一键下料","流程控制");					//20200720 增加

	GetDoc().SetFault(false);

	if(!GetControl().GetPCBFromTable())
	{
		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);

		GetDoc().SetFault(false);
		return 0;
	}

//	GetControl().ResetProcStatus();

	AfxMessageBox("下料取料已完成!");

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

	GetDoc().SetFault(false);
	return 0;
}

void CMotionControlTestView::OnResetCard1() 
{
	GetMotion().ResetCard(0);
	GetMotion().ResetCard(1);
//#ifdef DOUBLEBET
//	GetMotion().ResetCard(2);
//#endif
#ifndef USEDMSYSTEM													//20190507
#ifdef DOUBLEBET
	GetMotion().ResetCard(2);
#endif
#endif

	GetDoc().SetMotorState(FALSE);
	GetDoc().SetCurAptNo(0);
}

void CMotionControlTestView::OnResetCard2() 
{

}

void CMotionControlTestView::OnResetCard3() 
{

}

LONG CMotionControlTestView::OnCheckLimit(UINT wParam,LONG lParam)
{
    SetTimer(9,500,NULL);
	return 0;
}

LONG CMotionControlTestView::OnUncheckLimit(UINT wParam,LONG lParam)
{
	KillTimer(9);
	return 0;
}

void CMotionControlTestView::OnTimer(UINT nIDEvent) 
{
    UpdateData();

#ifdef USEIOCARD

 	int nLimit;  
	UINT ulAxis = GetCurOperateAxis();

#ifdef USEDMSYSTEM													//20190507
	if((ulAxis==AXISTABX)||(ulAxis==AXISTABY))
		nLimit = GetXYMotion().QueryLimit(ulAxis);
	else
		nLimit = GetMotion().QueryLimit(ulAxis);
#else
    nLimit = GetMotion().QueryLimit(ulAxis);
#endif

	if( nLimit>=0 )
	{
		m_sHome.SetIcon((nLimit&0x2)!=0  ? m_hLedOFF:m_hLedON);
		m_sNLimit.SetIcon((nLimit&0x4)!=0? m_hLedOFF:m_hLedON);
		m_sPLimit.SetIcon((nLimit&0x8)!=0? m_hLedOFF:m_hLedON);
	}

#endif
	UpdateData(FALSE);

//	TVisualFormView::OnTimer(nIDEvent);
}

void CMotionControlTestView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if(bActivate)
	{
		if(GetControl().GetRunState()!=CControl::END)
		{
			GetDlgItem(IDC_BT_STOPEXCCARD1)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_STOPEXCCARD2)->EnableWindow(FALSE);	
			
			m_btnHomeX.EnableWindow(FALSE);
			m_btnHomeY.EnableWindow(FALSE);
			m_btnHomeZ.EnableWindow(FALSE);
			m_btnHomeZ1.EnableWindow(FALSE);
			m_btnHomeW.EnableWindow(FALSE);
			m_btnHomeW1.EnableWindow(FALSE);			
			
			m_btnResetCard1.EnableWindow(FALSE);
			
			m_cmbSelectAxis.EnableWindow(FALSE);
			m_edtMoveToPos1.EnableWindow(FALSE);
			m_edtMoveToPos2.EnableWindow(FALSE);
			m_btnMoveToP1.EnableWindow(FALSE);
			m_btnMoveToP2.EnableWindow(FALSE);
			m_btnManuStop2.EnableWindow(FALSE);
			
			m_edtStepLength.EnableWindow(FALSE);
			m_btnManuUp.EnableWindow(FALSE);
			m_btnManuRight.EnableWindow(FALSE);
			m_btnManuLeft.EnableWindow(FALSE);
			m_btnManuDown.EnableWindow(FALSE);
			m_btnManuStop.EnableWindow(FALSE);

			m_btnTableUnLoadPos.EnableWindow(FALSE);
			m_btnTableLoadPos.EnableWindow(FALSE);
		}
		else
		{
			if (!GetDoc().GetUse9112()/* && GetDoc().GetDrillInc()*/)			//20181212
			{
				GetDlgItem(IDC_BT_STOPEXCCARD1)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_STOPEXCCARD2)->EnableWindow(TRUE);		
			}
			else
			{
				GetDlgItem(IDC_BT_STOPEXCCARD1)->EnableWindow(FALSE);
				GetDlgItem(IDC_BT_STOPEXCCARD2)->EnableWindow(FALSE);
			}
			
			int nLevel = GetDoc().GetCurUserLevel();
			if(nLevel==SystemDoc::PRIMARY)//初级
			{	  
				m_btnHomeX.EnableWindow(FALSE);
				m_btnHomeY.EnableWindow(FALSE);
				m_btnHomeZ.EnableWindow(FALSE);
				m_btnHomeZ1.EnableWindow(FALSE);
				m_btnHomeW.EnableWindow(FALSE);
				m_btnHomeW1.EnableWindow(FALSE);			
				
				m_btnResetCard1.EnableWindow(FALSE);
				
				m_cmbSelectAxis.EnableWindow(FALSE);
				m_edtMoveToPos1.EnableWindow(FALSE);
				m_edtMoveToPos2.EnableWindow(FALSE);
				m_btnMoveToP1.EnableWindow(FALSE);
				m_btnMoveToP2.EnableWindow(FALSE);
				m_btnManuStop2.EnableWindow(FALSE);
				
				m_edtStepLength.EnableWindow(FALSE);
				m_btnManuUp.EnableWindow(FALSE);
				m_btnManuRight.EnableWindow(FALSE);
				m_btnManuLeft.EnableWindow(FALSE);
				m_btnManuDown.EnableWindow(FALSE);
				m_btnManuStop.EnableWindow(FALSE);

				m_btnTableUnLoadPos.EnableWindow(FALSE);
				m_btnTableLoadPos.EnableWindow(FALSE);
			}
			else
			{
				m_btnHomeX.EnableWindow(TRUE);
				m_btnHomeY.EnableWindow(TRUE);
				m_btnHomeZ.EnableWindow(TRUE);
				m_btnHomeZ1.EnableWindow(TRUE);
				m_btnHomeW.EnableWindow(TRUE);
				m_btnHomeW1.EnableWindow(TRUE);			
				
				m_btnResetCard1.EnableWindow(TRUE);
				
				m_cmbSelectAxis.EnableWindow(TRUE);
				m_edtMoveToPos1.EnableWindow(TRUE);
				m_edtMoveToPos2.EnableWindow(TRUE);
				m_btnMoveToP1.EnableWindow(TRUE);
				m_btnMoveToP2.EnableWindow(TRUE);
				m_btnManuStop2.EnableWindow(TRUE);
				
				m_edtStepLength.EnableWindow(TRUE);
				m_btnManuUp.EnableWindow(TRUE);
				m_btnManuRight.EnableWindow(TRUE);
				m_btnManuLeft.EnableWindow(TRUE);
				m_btnManuDown.EnableWindow(TRUE);
				m_btnManuStop.EnableWindow(TRUE);

				m_btnTableUnLoadPos.EnableWindow(TRUE);
				m_btnTableLoadPos.EnableWindow(TRUE);
			}
		}
	}

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CMotionControlTestView::OnBtLoadpos() 
{
	char ez[256] = {""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

//	GetControl().MoveTo(GetDoc().GetTabLoadPos());
//	GetControl().WaitAxisStop(AXISTAB);	

//平台移至上料位
	if(GetDoc().GetUse9112())
		GetControl().MoveTo(GetDoc().GetTabLoadPos());
	else
	{
		if(GetDoc().GetASideIsProcessing())
			GetControl().MoveTo(GetDoc().GetTabLoadPos());
		else
			GetControl().MoveTo(GetDoc().GetOverTabLoadPos());		
	}
	
	GetControl().WaitAxisStop(AXISTAB);
}

void CMotionControlTestView::OnBtUnloadpos() 
{
	char ez[256] = {""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

//	GetControl().MoveTo(GetDoc().GetTabUnloadPos());
//	GetControl().WaitAxisStop(AXISTAB);	
	
//平台移至下料位
	if(GetDoc().GetUse9112())
		GetControl().MoveTo(GetDoc().GetTabUnloadPos());			
	else
	{
		if(GetDoc().GetASideIsProcessing())
			GetControl().MoveTo(GetDoc().GetTabUnloadPos());
		else
			GetControl().MoveTo(GetDoc().GetOverTabUnloadPos());
	}
	
	GetControl().WaitAxisStop(AXISTAB);
}

void CMotionControlTestView::OnButtonSet() 
{//20151110
	UpdateData();
//	if (2==GetDoc().GetLoadOptimize())
//	{
//		GetDoc().SetLoadPCBTime(m_IntLoadTime);
//		GetDoc().SetUnLoadPCBTime(m_IntUnLoadTime);
//	}
}

void CMotionControlTestView::OnBtnAgvl() 
{
	// TODO: Add your control notification handler code here
#ifdef HIKAGV
	int nsel = AfxMessageBox("请确认AGV小车送料仓有料，继续请选“是”，取消请选“否”!",MB_YESNO);
	if(nsel == IDNO)
		return;

	if(!GetDoc().GetPCBBoardIsReady())
	{
		if(!GetControl().AGVTransport(0))
			AfxMessageBox("AGV小车送料过程出现异常，请确认！");
	}
	else
		AfxMessageBox("机器内有料，无需AGV送料，请确认！");
#endif
}

void CMotionControlTestView::OnBtnAgvul() 
{
	// TODO: Add your control notification handler code here
#ifdef HIKAGV
	int nsel = AfxMessageBox("请确认AGV小车收料仓无料，继续请选“是”，取消请选“否”!",MB_YESNO);
	if(nsel == IDNO)
		return;

	if(GetDoc().GetPCBBoardIsReady())
	{
		if(!GetControl().AGVTransport(1))
			AfxMessageBox("AGV小车收料过程出现异常，请确认！");
	}
	else
		AfxMessageBox("机器内无料，无需AGV收料，请确认！");
#endif
}

void CMotionControlTestView::OnBtnAgvulandl() 
{
	// TODO: Add your control notification handler code here
#ifdef HIKAGV
	int nsel = AfxMessageBox("请确认AGV小车送料仓有料，收料仓无料，继续请选“是”，取消请选“否”!",MB_YESNO);
	if(nsel == IDNO)
		return;

	if(GetDoc().GetPCBBoardIsReady())
	{
		if(!GetControl().AGVTransport(2))
			AfxMessageBox("AGV小车收料和送料过程出现异常，请确认！");
	}
	else
		AfxMessageBox("机器内无料，无需AGV收料，请确认！");
#endif
}
