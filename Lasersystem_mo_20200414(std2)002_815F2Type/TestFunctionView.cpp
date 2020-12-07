// TestFunctionView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "TestFunctionView.h"
#include "operatecontrol.h"

#include "PrecisionSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestFunctionView dialog

#include "VisualFx.h"
CTestFunctionView *pTestFunctionView;

IMPLEMENT_DYNCREATE(CTestFunctionView, TVisualFormView)

CTestFunctionView::CTestFunctionView()
	: TVisualFormView(CTestFunctionView::IDD)
{
	//{{AFX_DATA_INIT(CTestFunctionView)
	m_iMatrix = 0;
	m_ulJumpDelay = 0;
	m_ulJumpSpeed = 0;
	m_ulLaserOnTime = 0;
	m_ulPlsPeriod = 1000;
	m_ulPlsRelease = 0;
	m_lMatrixHead = 0;
	m_lLaserHead = 0;
	m_dbLaserPower = 0.0;
	m_strBarcode = _T("");
	m_lDrillBarCodeHead = 0;
	m_lDrillBarCodeType = 0;
	m_iLaserTestInDex = 0;
	m_strTestThickness = _T("0");
	m_strPulseCount = _T("0");
	m_ulTestThickness = 0;
	m_strTextTest = _T("HANS");
	m_SysTestF = false;
	m_uWarmPlsRelease = 0;
	m_bSwitch = false;
	m_BaseDelayInt = 0;
	//}}AFX_DATA_INIT
}

void CTestFunctionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestFunctionView)
	DDX_Control(pDX, IDC_EDIT1_BASEDELAY, m_BaseDelay);
	DDX_Control(pDX, IDC_CMB_LASERHEAD, m_LaserHead);
	DDX_Control(pDX, IDC_CMB_MATRIXHEAD, m_MatrixHead);
	DDX_Control(pDX, IDC_BT_CYCLEDRILLMATRIX, m_btnCycleDrillMatrix);
	DDX_Control(pDX, IDC_EDT_TEXT, m_edtTextTest);
	DDX_Control(pDX, IDC_EDT_TESTBOARDTHICKNESS, m_edtTestBoardThickness);
	DDX_Control(pDX, IDC_CMB_TESTAPERTURE, m_cmbTestAperture);
//	DDX_Control(pDX, IDC_BT_SWITCH, m_btnRegionTest);
	DDX_Control(pDX, IDC_BARCPRINT, m_btnBarCodePrint);
	DDX_Control(pDX, IDC_BT_RESET, m_btnResetParam);
	DDX_Control(pDX, IDC_BT_SET, m_btnSetParam);
	DDX_Control(pDX, IDC_EDT_LASERONTIME, m_edtLaserOnTime);
	DDX_Control(pDX, IDC_EDT_JUMPDELAY, m_edtJumpDelay);
	DDX_Control(pDX, IDC_EDT_JUMPSPEED, m_edtJumpSpeed);
	DDX_Control(pDX, IDC_EDT_PLSPERIOD, m_edtPlsPeriod);
	DDX_Control(pDX, IDC_EDT_PLSRELEASE, m_edtPlsRelease);
	DDX_Control(pDX, IDC_COMBO2, m_cmbMDir);
	DDX_Control(pDX, IDC_BT_WARMUPLASER, m_btnWarmUpLaser);
	DDX_Control(pDX, IDC_BT_TESTLASERPOWER, m_btnTestLaserPower);
	DDX_Control(pDX, IDC_BT_DRILLMATRIX, m_btnDrillMatrix);
	DDX_Radio(pDX, IDC_RADIO1, m_iMatrix);
	DDX_Text(pDX, IDC_EDT_JUMPDELAY, m_ulJumpDelay);
	DDX_Text(pDX, IDC_EDT_JUMPSPEED, m_ulJumpSpeed);
	DDX_Text(pDX, IDC_EDT_LASERONTIME, m_ulLaserOnTime);
	DDX_Text(pDX, IDC_EDT_PLSPERIOD, m_ulPlsPeriod);
	DDX_Text(pDX, IDC_EDT_PLSRELEASE, m_ulPlsRelease);
	DDX_CBIndex(pDX, IDC_CMB_MATRIXHEAD, m_lMatrixHead);
	DDX_CBIndex(pDX, IDC_CMB_LASERHEAD, m_lLaserHead);
	DDX_Text(pDX, IDC_EDT_LASERPOWER, m_dbLaserPower);
	DDX_Text(pDX, IDC_BARCODESTR, m_strBarcode);
	DDX_CBIndex(pDX, IDC_CMB_DRILLBARCODEHEAD, m_lDrillBarCodeHead);
	DDX_CBIndex(pDX, IDC_CMB_DRILLBARCODETYPE, m_lDrillBarCodeType);
	DDX_Radio(pDX, IDC_RADIO7, m_iLaserTestInDex);
	DDX_Text(pDX, IDC_EDT_TESTTHICKNESS, m_strTestThickness);
	DDX_Text(pDX, IDC_EDT_PULSECOUNT, m_strPulseCount);
	DDX_Text(pDX, IDC_EDT_TESTBOARDTHICKNESS, m_ulTestThickness);
	DDX_Text(pDX, IDC_EDT_TEXT, m_strTextTest);
	DDX_Text(pDX, IDC_EDT_WARMPLSRELEASE, m_uWarmPlsRelease);
	DDX_Text(pDX, IDC_EDIT1_BASEDELAY, m_BaseDelayInt);
	DDV_MinMaxInt(pDX, m_BaseDelayInt, 0, 5000);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_ulPlsRelease, 1, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_uWarmPlsRelease, 0, LASERMAXWIDTH);//ly add 20111216
	
}


BEGIN_MESSAGE_MAP(CTestFunctionView, TVisualFormView)
	//{{AFX_MSG_MAP(CTestFunctionView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_DRILLMATRIX, OnDrillMatrix)
	ON_WM_DESTROY()
//	ON_BN_CLICKED(IDC_BT_RESET, OnResetParam)
	ON_BN_CLICKED(IDC_BT_SET, OnSetParam)
	ON_BN_CLICKED(IDC_BT_TESTLASERPOWER, OnTestLaserPower)
	ON_BN_CLICKED(IDC_BT_WARMUPLASER, OnWarmupLaser)
	ON_BN_CLICKED(IDC_BARCPREVIEW, OnBarCodePreview)
	ON_BN_CLICKED(IDC_BT_SWITCH, OnBtSwitch)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ZEROTEST, OnBtnZerotest)
	ON_BN_CLICKED(IDC_BTN_TESTTHICKNESS, OnBtnTestthickness)
	ON_BN_CLICKED(IDC_BT_TEXTTEST, OnBtTexttest)
	ON_BN_CLICKED(IDC_BT_APTSWITCH, OnBtAptswitch)
	ON_BN_CLICKED(IDC_BT_CYCLEDRILLMATRIX, OnBtCycledrillmatrix)
	ON_CBN_SELCHANGE(IDC_CMB_TESTAPERTURE, OnSelchangeCmbTestaperture)
	ON_COMMAND(ID_PRECISIONTEST, OnPrecisiontest)
	ON_COMMAND(ID_LASERFOCUSTEST1, OnLaserfocustest1)
	ON_COMMAND(ID_LASERFOCUSTEST2, OnLaserfocustest2)
	ON_COMMAND(ID_APERTURETEST, OnAperturetest)
//	ON_COMMAND(ID_TABLETEST, OnTabletest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestFunctionView message handlers

int CTestFunctionView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_btnWarmUpLaser.SubclassDlgItem(IDC_BT_WARMUPLASER,this);
	m_btnWarmUpLaser.SetIcon(IDI_WARMUP,IDI_WARMUP);

	m_btnTestLaserPower.SubclassDlgItem(IDC_BT_TESTLASERPOWER,this);
	m_btnTestLaserPower.SetIcon(IDI_LASER,IDI_LASER);

	m_btnDrillMatrix.SubclassDlgItem(IDC_BT_DRILLMATRIX,this);
	m_btnDrillMatrix.SetIcon(IDI_MATRIX,IDI_MATRIX);

	m_btnResetParam.SubclassDlgItem(IDC_BT_RESET,this);
	m_btnResetParam.SetIcon(IDI_RESET,IDI_RESET);
	m_btnSetParam.SubclassDlgItem(IDC_BT_SET,this);
	m_btnSetParam.SetIcon(IDI_SET,IDI_SET);
	m_edtJumpDelay.SetParseType ( SES_NUMBERS ); 
	m_edtJumpSpeed.SetParseType ( SES_NUMBERS ); 
	m_edtPlsPeriod.SetParseType ( SES_NUMBERS ); 
	m_edtPlsRelease.SetParseType( SES_NUMBERS ); 
	m_edtLaserOnTime.SetParseType(SES_NUMBERS ); 
	m_ulJumpDelay = GetDoc().GetTestJumpDelay();
	m_ulJumpSpeed = GetDoc().GetTestJumpSpeed();
	m_ulLaserOnTime = GetDoc().GetTestLaserOnTime();
	m_ulPlsPeriod	= GetDoc().GetTestPlsPeriod();
	m_ulPlsRelease  = GetDoc().GetTestPlsRelease();
    m_uWarmPlsRelease  = GetDoc().GetWarmUpPlsRelease();//����Ԥ��
	m_ulTestThickness=GetDoc().GetTestBoardThickness(); 
//	m_iRegionDim=GetDoc().GetRegionDim();

//	m_edtMotionCardSn3.SetParseType( SES_NUMBERS ); 
	pTestFunctionView=this;
	return 0;
}

/////////////////
//�������ƣ�OnBarCodePrint()
//�������ܣ��ڲ�����ͼ��ʵ������MARK
//��д�ˣ���͢ѫ
//��дʱ�䣺2006-05-29
/////////////////
/*
void CTestFunctionView::OnBarCodePrint()
{
	UpdateData (TRUE);
	CString binstr =GetBarCode().SetBarCodeValue(m_strBarcode);
	//	m_btnBarCodePrint.EnableWindow(FALSE);
	GetControl().MarkBarCode(binstr,m_lDrillBarCodeType,m_lDrillBarCodeHead);
}
*/
void CTestFunctionView::OnDrillMatrix() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	UpdateData(TRUE);	
	int iDir = m_cmbMDir.GetCurSel();

//	if(GetDoc().GetProcAxisMode()==1)												//20191015
//		m_lMatrixHead=0;
//	if(GetDoc().GetProcAxisMode()==2)
//		m_lMatrixHead=1;

	if(GetDoc().GetProcAxisMode()==1)												//20191210
	{
		if(m_lMatrixHead!=0)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

	if(GetDoc().GetProcAxisMode()==2)
	{
		if(m_lMatrixHead!=1)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

//	m_btnDrillMatrix.EnableWindow(FALSE);
//	double lSLScale=GetDoc().GetSLBitPerMM()/1000.0;
//	Coord offset;

//	m_strPulseCount = "";
//	UpdateData(FALSE);

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	GetControl().DrillMatrix(m_iMatrix,iDir,m_lMatrixHead);

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

//  m_btnDrillMatrix.EnableWindow(TRUE);

//	UpdateData (FALSE);	

#ifdef USELOG
    CString Tempstr;
	strncpy(ez,GetLang().GetWarningText(21098),256);
	Tempstr.Format(ez ,iDir,m_iMatrix);//"��ʽ��:%d �����:%d"
	GetLog().Append_pro(!m_lMatrixHead?10031:10032,20164,Tempstr);//"��":"��","�ӹ��������"
#endif
}

void CTestFunctionView::OnTestLaserPower() 
{
/*
	time_t Testtime;
	time(&Testtime);
	GetDoc().SetLaserTestCurTime(Testtime);
*/	
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	UpdateData(TRUE);

//	if(GetDoc().GetProcAxisMode()==1)												//20191015
//		m_lLaserHead=0;
//	if(GetDoc().GetProcAxisMode()==2)
//		m_lLaserHead=1;

	if(GetDoc().GetProcAxisMode()==1)												//20191210
	{
		if(m_lLaserHead!=0)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

	if(GetDoc().GetProcAxisMode()==2)
	{
		if(m_lLaserHead!=1)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

#ifdef SMCPreLoad																	//20180619
	if(!GetControl().PreLoadCreate(false,false,true,m_iLaserTestInDex))
	{
		AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
		return;
	}
#endif

//  m_btnTestLaserPower.EnableWindow(FALSE);

	float volt;
	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	if(!GetControl().GetLaserPowerTest(m_lLaserHead,m_ulLaserOnTime,volt,m_iLaserTestInDex))
	{
#ifdef USELOG
		GetLog().Append_pro(10106,20040);//"����ʧ��","������������"
#endif
//		m_btnTestLaserPower.EnableWindow(TRUE);
//		UpdateData(FALSE);
		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return;
	}

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

//	m_btnTestLaserPower.EnableWindow(TRUE);
	
	m_dbLaserPower=volt;
    if(m_dbLaserPower<0.2)
		m_dbLaserPower=0;	

	char buf[64];
	sprintf(buf,"%2.1f",m_dbLaserPower);
	m_dbLaserPower=atof(buf);	
	UpdateData(FALSE);
}

void CTestFunctionView::OnWarmupLaser() 
{
	UpdateData();
	char ez[256]={""};//ly 20110404
	m_btnWarmUpLaser.EnableWindow(FALSE);
	
	if(!GetDoc().GetLaserPowerState())
	{
		if(GetControl().LaserComInital())
		{
			GetDoc().SetLaserPowerState(true);
		}
		else
		{
			m_btnWarmUpLaser.EnableWindow(TRUE);
				return ;
		}
	}
	
	if(GetControl().LaserWarmup(m_ulLaserOnTime))
	{
		GetDoc().SetLaserWarmupState(true);
#ifdef USELOG
		CString StrTime;
		strncpy(ez,GetLang().GetWarningText(21099),256);
		StrTime.Format(ez,m_ulLaserOnTime);//"Ԥ��ʱ��:%d"
		GetLog().Append_pro(10108,20001,StrTime);//"����Ԥ�ȳɹ�","����Ԥ��"
#endif 
	}
	
	m_btnWarmUpLaser.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CTestFunctionView::OnBarCodePreview() 
{

}

void CTestFunctionView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("TestFunction","IDC_STATIC1",szRead,20);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC2",szRead,20);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC3",szRead,20);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC4",szRead,20);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC5",szRead,20);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC6",szRead,20);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC7",szRead,20);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC8",szRead,20);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC9",szRead,20);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_APTSWITCH",szRead,20);
	SetDlgItemText(IDC_BT_APTSWITCH,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_SET",szRead,20);
	SetDlgItemText(IDC_BT_SET,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC10",szRead,20);
	SetDlgItemText(IDC_STATIC10,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC11",szRead,20);
	SetDlgItemText(IDC_STATIC11,szRead);
	GetLang().GetUIText("FileInfoSetting","IDC_STATIC12",szRead,20);
	SetDlgItemText(IDC_STATIC12,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC13",szRead,20);
	SetDlgItemText(IDC_STATIC13,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_CYCLEDRILLMATRIX",szRead,20);
	SetDlgItemText(IDC_BT_CYCLEDRILLMATRIX,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_DRILLMATRIX",szRead,20);
	SetDlgItemText(IDC_BT_DRILLMATRIX,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC14",szRead,20);
	SetDlgItemText(IDC_STATIC14,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC15",szRead,20);
	SetDlgItemText(IDC_STATIC15,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC16",szRead,20);
	SetDlgItemText(IDC_STATIC16,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC17",szRead,20);
	SetDlgItemText(IDC_STATIC17,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC18",szRead,20);
	SetDlgItemText(IDC_STATIC18,szRead);
	GetLang().GetUIText("TestFunction","IDC_CHECK1",szRead,20);
	SetDlgItemText(IDC_CHECK1,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_TESTLASERPOWER",szRead,20);
	SetDlgItemText(IDC_BT_TESTLASERPOWER,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC19",szRead,20);
	SetDlgItemText(IDC_STATIC19,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC20",szRead,20);
	SetDlgItemText(IDC_STATIC20,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC21",szRead,20);
	SetDlgItemText(IDC_STATIC21,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_SWITCH",szRead,20);
	SetDlgItemText(IDC_BT_SWITCH,szRead);
	GetLang().GetUIText("TestFunction","IDC_BT_TEXTTEST",szRead,20);
	SetDlgItemText(IDC_BT_TEXTTEST,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC22",szRead,20);
	SetDlgItemText(IDC_STATIC22,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC23",szRead,20);
	SetDlgItemText(IDC_STATIC23,szRead);
	GetLang().GetUIText("TestFunction","IDC_STATIC24",szRead,20);//ly add 20120523
	SetDlgItemText(IDC_STATIC24,szRead);
	GetLang().GetUIText("TestFunction","IDC_BTN_ZEROTEST",szRead,20);
	SetDlgItemText(IDC_BTN_ZEROTEST,szRead);
	GetLang().GetUIText("TestFunction","IDC_BTN_TESTTHICKNESS",szRead,20);
	SetDlgItemText(IDC_BTN_TESTTHICKNESS,szRead);
}

void CTestFunctionView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	char szRead[20]={""};
	m_cmbMDir.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10107),20);
	m_cmbMDir.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10108),20);
	m_cmbMDir.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10109),20);
	m_cmbMDir.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10110),20);
	m_cmbMDir.AddString(szRead);

	m_cmbMDir.SetCurSel(0);

	m_MatrixHead.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10111),20);
	m_MatrixHead.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10112),20);
	m_MatrixHead.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10113),20);
	m_MatrixHead.AddString(szRead);
	m_MatrixHead.SetCurSel(m_lMatrixHead);

	m_LaserHead.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10111),20);
	m_LaserHead.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10112),20);
	m_LaserHead.AddString(szRead);
	m_LaserHead.SetCurSel(m_lLaserHead);
	m_cmbTestAperture.SetCurSel(GetDoc().GetTestAperture()-1);			//2009 12 24 liq
//	m_cmbTestAperture.SetCurSel(GetDoc().GetTestShowAperture()-1);		// 2009 12 24 liq
}

void CTestFunctionView::OnDestroy() 
{
	TVisualFormView::OnDestroy();
	UpdateData();
	GetDoc().SetTestJumpDelay(m_ulJumpDelay);
	GetDoc().SetTestJumpSpeed(m_ulJumpSpeed);
	GetDoc().SetTestLaserOnTime(m_ulLaserOnTime);
	GetDoc().SetTestPlsPeriod(m_ulPlsPeriod);
	GetDoc().SetTestPlsRelease(m_ulPlsRelease);
	GetDoc().SetWarmUpPlsRelease(m_uWarmPlsRelease);//����Ԥ��
	GetDoc().SetTestAperture( m_cmbTestAperture.GetCurSel()+1 );
}

void CTestFunctionView::OnSetParam() 
{
     UpdateData();

     GetDoc().SetBaseDelay(m_BaseDelayInt);
	if(!m_SysTestF)
	{
	m_SysTestF = true;
	UpdateData();
	GetDoc().SetTestJumpDelay(m_ulJumpDelay);
	GetDoc().SetTestJumpSpeed(m_ulJumpSpeed);
	GetDoc().SetTestLaserOnTime(m_ulLaserOnTime);
	GetDoc().SetTestPlsPeriod(m_ulPlsPeriod);
	GetDoc().SetTestPlsRelease(m_ulPlsRelease);
	GetDoc().SetWarmUpPlsRelease(m_uWarmPlsRelease);//
	GetDoc().SetTestAperture( m_cmbTestAperture.GetCurSel()+1 );
	GetDoc().SetTestBoardThickness(m_ulTestThickness);
	GetDoc().SetTextTest(m_strTextTest);
//	GetDoc().SetRegionDim(m_iRegionDim);
//	GetDoc().ReleaseSysDoc();
	GetDoc().SaveProcessParam();
	Delay(200);
	AfxMessageBox("�������趨�����棡");
		
#ifdef USELOG
	CString TempStr;
	/*TempStr.Format("D:%d ,S:%d ,T:%d ,P:%d,R:%d",
		m_ulJumpDelay,m_ulJumpSpeed,m_ulLaserOnTime,m_ulPlsPeriod,m_ulPlsRelease);*/
	TempStr.Format("D:%d ,S:%d ,T:%d ,P:%d,R:%d,WarmR:%d",//ly change 20110125 ����Ԥ��
		m_ulJumpDelay,m_ulJumpSpeed,m_ulLaserOnTime,m_ulPlsPeriod,m_ulPlsRelease,m_uWarmPlsRelease);
	GetLog().Append_pro(10049,20165,TempStr);//"��������","���Ի�������"
#endif
	m_SysTestF = false;
	}
}

void CTestFunctionView::OnBtSwitch() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	UpdateData (TRUE);

//	if(GetDoc().GetProcAxisMode()==1)												//20191015
//		m_lMatrixHead=0;
//	if(GetDoc().GetProcAxisMode()==2)
//		m_lMatrixHead=1;

	if(GetDoc().GetProcAxisMode()==1)												//20191210
	{
		if(m_lMatrixHead!=0)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

	if(GetDoc().GetProcAxisMode()==2)
	{
		if(m_lMatrixHead!=1)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

#ifdef SMCPreLoad																	//20180619
	if(!GetControl().PreLoadCreate(false,true,false))
	{
		AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
		return;
	}
#endif
	
//	m_btnRegionTest.EnableWindow(FALSE);

//	GetControl().DrillRegion(Coord(0,0),m_lMatrixHead);  

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	GetControl().DrillRegionTest(m_lMatrixHead);

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

//  m_btnRegionTest.EnableWindow(TRUE);

//	UpdateData (FALSE);		
}

void CTestFunctionView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*
	if (888==nIDEvent)
	{
		if (GetControl().GetRunState()==CControl::RUN)
		{
			GetDlgItem(IDC_BT_TESTLASERPOWER)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_TESTTHICKNESS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ZEROTEST)->EnableWindow(FALSE);			
		}
		else
		{
			GetDlgItem(IDC_BT_TESTLASERPOWER)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_TESTTHICKNESS)->EnableWindow(TRUE);			
			GetDlgItem(IDC_BTN_ZEROTEST)->EnableWindow(TRUE);	
		}
	}
*/	
	TVisualFormView::OnTimer(nIDEvent);
}

void CTestFunctionView::OnBtnZerotest() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	long lThickZero[2]={0,0};;

	UpdateData(TRUE);

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

//	if(!GetControl().TestThicknessAL(lThickZero,m_lLaserHead))
	if(!GetControl().TestThicknessAL(lThickZero,m_lLaserHead,Coord(GetDoc().GetThicknessX(),GetDoc().GetThicknessY())))		//20190725
	{
		strncpy(ez,GetLang().GetWarningText(21074),256);
		AfxMessageBox(ez);//"����׼У������������У��!�����ֶ���λ�˶����ƿ���"//ly add 20110316 ��λ��ʾ

		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return;
	}

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

	GetDoc().SetThicknessZero(lThickZero[m_lLaserHead],m_lLaserHead);	

	m_strTestThickness.Format("%d",0);
    UpdateData(FALSE);	
}

void CTestFunctionView::OnBtnTestthickness() 
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	long lThickTest[2]={0,0};;

	UpdateData(TRUE);

//	m_strTestThickness  = "";
//	UpdateData(FALSE);

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

//	if(!GetControl().TestThicknessAL(lThickTest,m_lLaserHead))
	if(!GetControl().TestThicknessAL(lThickTest,m_lLaserHead,Coord(GetDoc().GetThicknessX(),GetDoc().GetThicknessY())))		//20190725
	{
		strncpy(ez,GetLang().GetWarningText(21075),256);
		AfxMessageBox(ez);//"���������������²��!�����ֶ���λ�˶����ƿ���"

		GetControl().SetRunState(CControl::END);
		OnActivateView(true,this,this);
		return;
	}

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

	m_strTestThickness.Format("%d",GetDoc().GetThicknessZero(m_lLaserHead)-lThickTest[m_lLaserHead]+GetDoc().GetTestThicknessCompensation(m_lLaserHead));
	UpdateData(FALSE);
}

void CTestFunctionView::OnBtTexttest() 
{
// TODO: Add your control notification handler code here
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	UpdateData (TRUE);

//	if(GetDoc().GetProcAxisMode()==1)												//20191015
//		m_lMatrixHead=0;
//	if(GetDoc().GetProcAxisMode()==2)
//		m_lMatrixHead=1;

	if(GetDoc().GetProcAxisMode()==1)												//20191210
	{
		if(m_lMatrixHead!=0)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}

	if(GetDoc().GetProcAxisMode()==2)
	{
		if(m_lMatrixHead!=1)
		{
			AfxMessageBox("��ǰ�ǵ�����ģʽ����ѡ���޷�������");
			return;
		}
	}
	
//	m_btnRegionTest.EnableWindow(FALSE);

//	GetControl().DrillRegion(Coord(0,0),m_lMatrixHead); 
	
	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	GetControl().DrillStringTest(m_strTextTest,m_lMatrixHead);

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);

//  m_btnRegionTest.EnableWindow(TRUE);

//	UpdateData (FALSE);			
}

void CTestFunctionView::OnBtAptswitch() 
{
// TODO: Add your control notification handler code here
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	GetControl().MoveTo(GetDoc().GetTestAperture());

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

void CTestFunctionView::OnBtCycledrillmatrix() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	UpdateData (TRUE);
	
	int iDir = m_cmbMDir.GetCurSel();
	m_btnCycleDrillMatrix.EnableWindow(FALSE);

//	GetControl().CycleDrillMatrix(m_iMatrix,iDir,m_lMatrixHead);

	m_btnCycleDrillMatrix.EnableWindow(TRUE);
	UpdateData (FALSE);		
}

void CTestFunctionView::OnSelchangeCmbTestaperture() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8��Ȧ
	if(m_cmbTestAperture.GetCurSel()>7)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"��Ȧ�趨ֵ���������8#��Ȧ!"
		
		m_cmbTestAperture.SetCurSel(7);
		UpdateData(FALSE);
	}
	
#else//ly change 20110122 12��Ȧ
	if(m_cmbTestAperture.GetCurSel()>11)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"��Ȧ�趨ֵ���������12#��Ȧ!"
		
		m_cmbTestAperture.SetCurSel(11);
		UpdateData(FALSE);
	}
#endif
#else
//ly change 20110122 18��Ȧ
	if(m_cmbTestAperture.GetCurSel()>17)
	{
		strncpy(ez,GetLang().GetWarningText(21060),256);
		AfxMessageBox(ez);//"��Ȧ�趨ֵ���������18#��Ȧ!"

		m_cmbTestAperture.SetCurSel(17);
		UpdateData(FALSE);
	}
#endif
}

void CTestFunctionView::OnPrecisiontest() 
{
	char ez[256]={""};
	int nHead=0;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}
	
	strncpy(ez,GetLang().GetWarningText(31035),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"��������ӹ�����  ѡ�� '��'\n��������ӹ�����  ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
	
	if(nSel==IDYES)
		nHead=0; 
	else if(nSel==IDNO) 
		nHead=1;
	else
		return;

	CPrecisionSelect dlg;								//�ظ�ʹ�þ��Ȳ���λ�ã���4*4=16��λ�ÿ��ã�λ�ÿɶ�ѡ�����ж�β�����
	if (dlg.DoModal()!=IDOK)
		return;

//	BOOL isQuitTable=FALSE;
//	int processTime=GetDoc().m_CArrayGetPrecisionSelect.GetSize();

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

	for (int i=0;i<GetDoc().m_CArrayGetPrecisionSelect.GetSize();i++)
	{
		GetControl().DrillPrecisionTest(nHead,GetDoc().m_CArrayGetPrecisionSelect.GetAt(i));
		Delay(1000);
	}

	GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

void CTestFunctionView::OnLaserfocustest1() 
{
	// TODO: Add your command handler code here
	char ez[256]={""};
	int nHead=0;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}
		
	strncpy(ez,GetLang().GetWarningText(31036),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"��������ӹ�����  ѡ�� '��'\n��������ӹ�����  ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"

	if(nSel==IDYES)
		nHead=0; 
	else if(nSel==IDNO) 
		nHead=1;
	else
		return;

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);	
		
	GetControl().DrillFocusTest(nHead,false);
	
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

void CTestFunctionView::OnLaserfocustest2() 
{
	// TODO: Add your command handler code here
	char ez[256]={""};
	int nHead=0;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}

	strncpy(ez,GetLang().GetWarningText(31036),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"��������ӹ�����  ѡ�� '��'\n��������ӹ�����  ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
	
	if(nSel==IDYES)
		nHead=0; 
	else if(nSel==IDNO) 
		nHead=1;
	else
		return;

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);	
		
	GetControl().DrillFocusTest(nHead,true);
	
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);	
}

void CTestFunctionView::OnAperturetest() //ly add 20110312 ��Ȧ����
{
	// TODO: Add your command handler code here
	char ez[256]={""};
	int nHead=0;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}
	
	strncpy(ez,GetLang().GetWarningText(31037),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"���������Ȧ  ѡ�� '��'\n���������Ȧ  ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
	
	if(nSel==IDYES)
		nHead=0; 
	else if(nSel==IDNO) 
		nHead=1;
	else
		return;

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);	
		
	GetControl().DrillApertureTest(nHead);
	
	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);	
}

void CTestFunctionView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class	
	if(bActivate)
	{
//		SetTimer(888, 1000, NULL);

		if(GetControl().GetRunState()!=CControl::END)
		{
			GetDlgItem(IDC_EDT_TESTBOARDTHICKNESS)->EnableWindow(FALSE);
			GetDlgItem(IDC_CMB_TESTAPERTURE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_TEXT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT1_BASEDELAY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_PLSRELEASE)->EnableWindow(FALSE);		
			GetDlgItem(IDC_BT_APTSWITCH)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_SET)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
			GetDlgItem(IDC_CMB_MATRIXHEAD)->EnableWindow(FALSE);			
			GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);		
			GetDlgItem(IDC_BT_CYCLEDRILLMATRIX)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_DRILLMATRIX)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_BT_SWITCH)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_TEXTTEST)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_CMB_LASERHEAD)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_LASERONTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_TESTLASERPOWER)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_BTN_ZEROTEST)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_TESTTHICKNESS)->EnableWindow(FALSE);	
		}
		else
		{
			int nLevel = GetDoc().GetCurUserLevel();
			if(nLevel==SystemDoc::PRIMARY)//����
			{
				GetDlgItem(IDC_EDT_TESTBOARDTHICKNESS)->EnableWindow(FALSE);
				GetDlgItem(IDC_CMB_TESTAPERTURE)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDT_TEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDIT1_BASEDELAY)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDT_PLSRELEASE)->EnableWindow(FALSE);		
				GetDlgItem(IDC_BT_APTSWITCH)->EnableWindow(FALSE);
				GetDlgItem(IDC_BT_SET)->EnableWindow(FALSE);
				
				GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
				GetDlgItem(IDC_CMB_MATRIXHEAD)->EnableWindow(FALSE);			
				GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);		
				GetDlgItem(IDC_BT_CYCLEDRILLMATRIX)->EnableWindow(FALSE);
				GetDlgItem(IDC_BT_DRILLMATRIX)->EnableWindow(FALSE);
				
				GetDlgItem(IDC_BT_SWITCH)->EnableWindow(FALSE);
				GetDlgItem(IDC_BT_TEXTTEST)->EnableWindow(FALSE);

				GetDlgItem(IDC_CMB_LASERHEAD)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDT_LASERONTIME)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
				GetDlgItem(IDC_BT_TESTLASERPOWER)->EnableWindow(FALSE);

				GetDlgItem(IDC_BTN_ZEROTEST)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_TESTTHICKNESS)->EnableWindow(TRUE);
			}
			else //�߼�//ϵͳ
			{
				GetDlgItem(IDC_EDT_TESTBOARDTHICKNESS)->EnableWindow(TRUE);
				GetDlgItem(IDC_CMB_TESTAPERTURE)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_TEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT1_BASEDELAY)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_PLSRELEASE)->EnableWindow(TRUE);	
				GetDlgItem(IDC_BT_APTSWITCH)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_SET)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
				GetDlgItem(IDC_CMB_MATRIXHEAD)->EnableWindow(TRUE);	
				GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_CYCLEDRILLMATRIX)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_DRILLMATRIX)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_BT_SWITCH)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_TEXTTEST)->EnableWindow(TRUE);

				GetDlgItem(IDC_CMB_LASERHEAD)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_LASERONTIME)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO9)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO10)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO11)->EnableWindow(TRUE);
				GetDlgItem(IDC_BT_TESTLASERPOWER)->EnableWindow(TRUE);

				GetDlgItem(IDC_BTN_ZEROTEST)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_TESTTHICKNESS)->EnableWindow(TRUE);
			}
		}

		m_edtPlsPeriod.EnableWindow(FALSE);
		m_edtJumpSpeed.EnableWindow(FALSE);
		m_edtJumpDelay.EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_WARMPLSRELEASE)->EnableWindow(FALSE);
	}
//	else
//		KillTimer(888);

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
/*
void CTestFunctionView::OnTabletest() 
{
	char ez[256]={""};//ly 20110404
	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return;
	}
	
	strncpy(ez,GetLang().GetWarningText(31040),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"����Z1��ƽ̨����  ѡ�� '��'\n����Z2��ƽ̨����  ѡ�� '��'\nȡ������ ѡ��       'ȡ��'\n"
	
	GetDoc().SetPrecisionRowCount(0); 
	GetDoc().SetPrecisionLineCount(0); 		   
	if(nSel == IDYES)			//�ӹ�����
	{			
		if(!GetControl().DrillParamTableDelayTest(HeadLeft,GetDoc().GetBaseDelay()))
		{
			GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
		}
	}
	else if(nSel == IDNO)		//�ӹ�����
	{				
		if(!GetControl().DrillParamTableDelayTest(HeadRight,GetDoc().GetBaseDelay()))
		{
			GetControl().EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
		}				
	}
	
}
*/
