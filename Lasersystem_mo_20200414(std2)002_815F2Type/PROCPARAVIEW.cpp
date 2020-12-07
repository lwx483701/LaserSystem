// PROCPARAVIEW.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "PROCPARAVIEW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcParaView

IMPLEMENT_DYNCREATE(CProcParaView, TVisualFormView)

CProcParaView::CProcParaView()
	: TVisualFormView(CProcParaView::IDD)
{
	//{{AFX_DATA_INIT(CProcParaView)
	m_lJumpDelay = 0;
	m_lJumpSpeed = 0;
	m_ulPlsPeriod = 0;
	m_ulPlsRelease = 0;
	m_ulPls2Release = 0;
	m_ulPls3Release = 0;
	m_ulPls4Release = 0;
	m_ulPls5Release = 0;
	m_ulAdjJmpDelay = 0;
	m_ulAdjJmpSpeed = 0;
	m_ulAdjPlsPeriod = 0;
	m_ulAdjPlsRelease = 0;
	m_ulTxtPlsRelease = 0;
	m_ulTxtPlsPeriod = 0;
	m_lTxtJumpSpeed = 0;
	m_lTxtJumpDelay = 0;
	m_ulGlvAdjPlsRelease = 0;
	m_iRegionDim = 1000;
	m_fTextHeigth = 2.4;
	m_SysProc =  false;
	m_RegionPointDis = 100;
	m_iPluseTimes = 0;
	m_chkDrillCoil = FALSE;
	//}}AFX_DATA_INIT
}

CProcParaView::~CProcParaView()
{
}

void CProcParaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcParaView)
	DDX_Control(pDX, IDC_CHECK_DRILLREGION, m_CheckDrillRegion);
	DDX_Control(pDX, IDC_EDIT_PLUSETIMES, m_edtPluseTimes);
	DDX_Control(pDX, IDC_EDT_TEXTHEIGTH, m_edtTextHeigth);
	DDX_Control(pDX, IDC_EDT_REGIONDIM, m_edtRegionDim);
	DDX_Control(pDX, IDC_EDT_GLVADJPLSRELEASE, m_edtGlvAdjPlsRelease);
	DDX_Control(pDX, IDC_CMB_LONGPATH_ADJAPERTURE, m_cmbLongPathAdjAperture);
	DDX_Control(pDX, IDC_CMB_ADJAPERTURE, m_cmbAdjAperture);
	DDX_Control(pDX, IDC_CMB_TXTPERTURE, m_cmbTxtAperture);
	DDX_Control(pDX, IDC_EDT_TXTJUMPDELAY, m_edtTxtJumpDelay);
	DDX_Control(pDX, IDC_EDT_TXTJUMPSPEED, m_edtTxtJumpSpeed);
	DDX_Control(pDX, IDC_EDT_TXTPLSPERIOD, m_edtTxtPlsPeriod);
	DDX_Control(pDX, IDC_EDT_TXTPLSRELEASE, m_edtTxtPlsRelease);
	DDX_Control(pDX, IDC_CMB_TXTPULSENUM, m_cmbTxtPlsNum);
	DDX_Control(pDX, IDC_EDT_ADJJUMPSPEED, m_edtAdjJmpSpeed);
	DDX_Control(pDX, IDC_EDT_ADJPLSRELEASE, m_edtAdjPlsRelease);
	DDX_Control(pDX, IDC_EDT_ADJPLSPERIOD, m_edtAdjPlsPeriod);
	DDX_Control(pDX, IDC_EDT_ADJJUMPDELAY, m_edtAdjJmpDelay);
	DDX_Control(pDX, IDC_EDT_PLSPERIOD, m_edtPlsPeriod);
	DDX_Control(pDX, IDC_EDT_JUMPDELAY, m_edtJumpDelay);
	DDX_Control(pDX, IDC_BT_SETPROCPARA, m_btnSetPara);
	DDX_Control(pDX, IDC_BT_SAVEPROCPARA, m_btnSavePara);
	DDX_Control(pDX, IDC_BT_RESETPROCPARA, m_btnResetPara);
	DDX_Control(pDX, IDC_EDT_PLSRELEASE, m_edtPlsRelease);
	DDX_Control(pDX, IDC_EDT_PLS2RELEASE, m_edtPls2Release);
	DDX_Control(pDX, IDC_EDT_PLS3RELEASE, m_edtPls3Release);
	DDX_Control(pDX, IDC_EDT_PLS4RELEASE, m_edtPls4Release);
	DDX_Control(pDX, IDC_EDT_PLS5RELEASE, m_edtPls5Release);
	DDX_Control(pDX, IDC_EDT_JUMPSPEED, m_edtJumpSpeed);
	DDX_Control(pDX, IDC_CMB_APERTURE, m_cmbAperture);
	DDX_Control(pDX, IDC_CMB_PULSENUM, m_cmbPlsNum);
	DDX_Text(pDX, IDC_EDT_JUMPDELAY, m_lJumpDelay);
	DDX_Text(pDX, IDC_EDT_JUMPSPEED, m_lJumpSpeed);
	DDX_Text(pDX, IDC_EDT_PLSPERIOD, m_ulPlsPeriod);
	DDX_Text(pDX, IDC_EDT_PLSRELEASE, m_ulPlsRelease);
	DDX_Text(pDX, IDC_EDT_PLS2RELEASE, m_ulPls2Release);
	DDX_Text(pDX, IDC_EDT_PLS3RELEASE, m_ulPls3Release);
	DDX_Text(pDX, IDC_EDT_PLS4RELEASE, m_ulPls4Release);
	DDX_Text(pDX, IDC_EDT_PLS5RELEASE, m_ulPls5Release);
	DDX_Text(pDX, IDC_EDT_ADJJUMPDELAY, m_ulAdjJmpDelay);
	DDX_Text(pDX, IDC_EDT_ADJJUMPSPEED, m_ulAdjJmpSpeed);
	DDX_Text(pDX, IDC_EDT_ADJPLSPERIOD, m_ulAdjPlsPeriod);
	DDX_Text(pDX, IDC_EDT_ADJPLSRELEASE, m_ulAdjPlsRelease);
	DDX_Text(pDX, IDC_EDT_TXTPLSRELEASE, m_ulTxtPlsRelease);
	DDX_Text(pDX, IDC_EDT_TXTPLSPERIOD, m_ulTxtPlsPeriod);
	DDX_Text(pDX, IDC_EDT_TXTJUMPSPEED, m_lTxtJumpSpeed);
	DDX_Text(pDX, IDC_EDT_TXTJUMPDELAY, m_lTxtJumpDelay);
	DDX_Text(pDX, IDC_EDT_GLVADJPLSRELEASE, m_ulGlvAdjPlsRelease);
	DDX_Text(pDX, IDC_EDT_REGIONDIM, m_iRegionDim);
	DDX_Text(pDX, IDC_EDT_TEXTHEIGTH, m_fTextHeigth);
	DDX_Text(pDX, IDC_EDT_REGIONPOINTDIS, m_RegionPointDis);
	DDV_MinMaxInt(pDX, m_RegionPointDis, 50, 150);										//20160919
	DDX_Text(pDX, IDC_EDIT_PLUSETIMES, m_iPluseTimes);
	DDX_Check(pDX, IDC_CHECK_DRILLCOIL, m_chkDrillCoil);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_ulPlsRelease, 0, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulPls2Release, 0, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulPls3Release, 0, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulPls4Release, 0, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulPls5Release, 0, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulAdjPlsRelease, 1, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulTxtPlsRelease, 1, LASERMAXWIDTH);//ly add 20111216
	DDV_MinMaxUInt(pDX, m_ulGlvAdjPlsRelease, 1, LASERMAXWIDTH);//ly add 20111216
}


BEGIN_MESSAGE_MAP(CProcParaView, TVisualFormView)
	//{{AFX_MSG_MAP(CProcParaView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_RESETPROCPARA, OnResetProcPara)
	ON_BN_CLICKED(IDC_BT_SETPROCPARA, OnSetProcPara)
	ON_BN_CLICKED(IDC_BT_SAVEPROCPARA, OnSaveProcPara)
	ON_CBN_SELCHANGE(IDC_CMB_APERTURE, OnSelchangeCmbAperture)
	ON_CBN_SELCHANGE(IDC_CMB_ADJAPERTURE, OnSelchangeCmbAdjaperture)
	ON_CBN_SELCHANGE(IDC_CMB_LONGPATH_ADJAPERTURE, OnSelchangeCmbLongpathAdjaperture)
	ON_CBN_SELCHANGE(IDC_CMB_TXTPERTURE, OnSelchangeCmbTxtperture)
	ON_BN_CLICKED(IDC_BUTTON1, OnCountClear)
	ON_BN_CLICKED(IDC_BUTTON_ACCURAY, OnButtonAccuray)
	ON_BN_CLICKED(IDC_CHECK_DRILLREGION, OnCheckDrillregion)
	ON_BN_CLICKED(IDC_CHECK_DRILLCOIL, OnCheckDrillcoil)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcParaView diagnostics

#ifdef _DEBUG
void CProcParaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProcParaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProcParaView message handlers
void CProcParaView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("ProcPara","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC7",szRead,40);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC9",szRead,40);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC10",szRead,40);
	SetDlgItemText(IDC_STATIC10,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC11",szRead,40);
	SetDlgItemText(IDC_STATIC11,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC12",szRead,40);
	SetDlgItemText(IDC_STATIC12,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC13",szRead,40);
	SetDlgItemText(IDC_STATIC13,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC14",szRead,40);
	SetDlgItemText(IDC_STATIC14,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC15",szRead,40);
	SetDlgItemText(IDC_STATIC15,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC16",szRead,40);
	SetDlgItemText(IDC_STATIC16,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC17",szRead,40);
	SetDlgItemText(IDC_STATIC17,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC18",szRead,40);
	SetDlgItemText(IDC_STATIC18,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC19",szRead,40);
	SetDlgItemText(IDC_STATIC19,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC20",szRead,40);
	SetDlgItemText(IDC_STATIC20,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC21",szRead,40);
	SetDlgItemText(IDC_STATIC21,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC22",szRead,40);
	SetDlgItemText(IDC_STATIC22,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC23",szRead,40);
	SetDlgItemText(IDC_STATIC23,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC24",szRead,40);
	SetDlgItemText(IDC_STATIC24,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC25",szRead,40);
	SetDlgItemText(IDC_STATIC25,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC26",szRead,40);
	SetDlgItemText(IDC_STATIC26,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC27",szRead,40);
	SetDlgItemText(IDC_STATIC27,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC28",szRead,40);
	SetDlgItemText(IDC_STATIC28,szRead);
	GetLang().GetUIText("ProcPara","IDC_STATIC29",szRead,40);//ly add 20121029 脉冲发数
	SetDlgItemText(IDC_STATIC29,szRead);
	GetLang().GetUIText("ProcPara","IDC_BUTTON1",szRead,40);
	SetDlgItemText(IDC_BUTTON1,szRead);
	GetLang().GetUIText("ProcPara","IDC_BT_RESETPROCPARA",szRead,40);
	SetDlgItemText(IDC_BT_RESETPROCPARA,szRead);
	GetLang().GetUIText("ProcPara","IDC_BT_SETPROCPARA",szRead,40);
	SetDlgItemText(IDC_BT_SETPROCPARA,szRead);
	GetLang().GetUIText("ProcPara","IDC_BT_SAVEPROCPARA",szRead,40);
	SetDlgItemText(IDC_BT_SAVEPROCPARA,szRead);
	GetLang().GetUIText("ProcPara","IDC_BUTTON_ACCURAY",szRead,40);//ly add 20130326
	SetDlgItemText(IDC_BUTTON_ACCURAY,szRead);
}

void CProcParaView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	m_cmbAperture.SetCurSel(GetDoc().GetDrlRegAperture()-1);      //2009 12 24 liq
//	m_cmbAperture.SetCurSel(GetDoc().GetDrlRegShowAperture()-1);      //2009 12 24 liq
	m_cmbPlsNum.SetCurSel(GetDoc().GetDrlRegPlsNum()-1);

	//yutingxun 7-20   
	m_cmbTxtAperture.SetCurSel(GetDoc().GetDrlTxtAperture()-1);		//2009 12 24 liq
//	m_cmbTxtAperture.SetCurSel(GetDoc().GetDrlTxtShowAperture()-1);		//2009 12 24 liq
	m_cmbTxtPlsNum.SetCurSel(GetDoc().GetDrlTxtPlsNum()-1);
	m_lTxtJumpDelay = GetDoc().GetDrlTxtJumpDelay();
	m_lTxtJumpSpeed = GetDoc().GetDrlTxtJumpSpeed();
	m_ulTxtPlsPeriod = GetDoc().GetDrlTxtPulsePeriod();
	m_ulTxtPlsRelease = GetDoc().GetDrlTxtPulseRelease();
	m_cmbAdjAperture.SetCurSel(GetDoc().GetAdjustAperture()-1);		//2009 12 24 liq
//	m_cmbAdjAperture.SetCurSel(GetDoc().GetAdjustShowAperture()-1);		//2009 12 24 liq
	m_cmbLongPathAdjAperture.SetCurSel(GetDoc().GetLongPathAdjustAperture()-1);   //2009 12 24 
//	m_cmbLongPathAdjAperture.SetCurSel(GetDoc().GetLongPathAdjustShowAperture()-1);	//2009 12 24 

	m_edtJumpSpeed.SetParseType (SES_NUMBERS);
	m_edtJumpSpeed.SetRange(0,7000);
    m_edtJumpDelay.SetParseType (SES_NUMBERS);
	m_edtPlsRelease.SetParseType(SES_NUMBERS);
	m_edtPls2Release.SetParseType(SES_NUMBERS);
	m_edtPls3Release.SetParseType(SES_NUMBERS);
	m_edtPls4Release.SetParseType(SES_NUMBERS);
	m_edtPls5Release.SetParseType(SES_NUMBERS);
    m_edtPlsRelease.SetRange(0,LASERMAXWIDTH);
	m_edtPls2Release.SetRange(0,LASERMAXWIDTH);
	m_edtPls3Release.SetRange(0,LASERMAXWIDTH);
	m_edtPls4Release.SetRange(0,LASERMAXWIDTH);
	m_edtPls5Release.SetRange(0,LASERMAXWIDTH);

	m_edtPlsPeriod.SetParseType (SES_NUMBERS);
	m_edtAdjJmpSpeed.SetParseType (SES_NUMBERS);
	m_edtAdjJmpSpeed.SetRange(0,7000);
	m_edtAdjPlsRelease.SetParseType (SES_NUMBERS);
    m_edtAdjPlsRelease.SetRange(0,LASERMAXWIDTH);
	m_edtAdjPlsPeriod.SetParseType (SES_NUMBERS);
	m_edtAdjJmpDelay.SetParseType (SES_NUMBERS);
	UpdateData(FALSE);

}

int CProcParaView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_lJumpDelay = GetDoc().GetDrlRegJumpDelay();
	m_lJumpSpeed = GetDoc().GetDrlRegJumpSpeed();

	m_iPluseTimes = GetDoc().GetDrlRegPulseTimes();
	m_ulPlsPeriod = GetDoc().GetDrlRegPulsePeriod();
	m_ulPlsRelease = GetDoc().GetDrlRegPulseRelease();
	m_ulPls2Release = GetDoc().GetDrlRegPulse2Release();
	m_ulPls3Release = GetDoc().GetDrlRegPulse3Release();
	m_ulPls4Release = GetDoc().GetDrlRegPulse4Release();
	m_ulPls5Release = GetDoc().GetDrlRegPulse5Release();
	m_RegionPointDis = GetDoc().GetDrlRegionPointDis();

	m_ulAdjJmpDelay = GetDoc().GetAdjustJumpDelay();
	m_ulAdjJmpSpeed = GetDoc().GetAdjustJumpSpeed();
	m_ulAdjPlsPeriod = GetDoc().GetAdjustPulsePeriod();
	m_ulAdjPlsRelease = GetDoc().GetAdjustPulseRelease();

	m_ulGlvAdjPlsRelease = GetDoc().GetGlvAdjPlsRelease();
//	m_lGlvAdjPosX = GetDoc().GetGlvAdjPosX();
//	m_lGlvAdjPosY = GetDoc().GetGlvAdjPosY();
	
//	m_btnResetPara.SubclassDlgItem(IDC_BT_RESETPROCPARA,this);
	m_btnResetPara.SetIcon(IDI_RESET,IDI_RESET);
//	m_btnSetPara.SubclassDlgItem(IDC_BT_SETPROCPARA,this);
	m_btnSetPara.SetIcon(IDI_SET,IDI_SET);
//	m_btnSavePara.SubclassDlgItem(IDC_BT_SAVEPROCPARA,this);
	m_btnSavePara.SetIcon(IDI_SAVEP,IDI_SAVEP);
	m_iRegionDim=GetDoc().GetRegionDim();
	m_fTextHeigth=GetDoc().GetTextHeigth();
	m_chkDrillCoil=GetDoc().GetDrillCoil();							//20170224

	return 0;
}

void CProcParaView::OnResetProcPara() 
{
   	GetDoc().InitializeSysDoc();
    
	m_lJumpDelay = GetDoc().GetDrlRegJumpDelay();
	m_lJumpSpeed = GetDoc().GetDrlRegJumpSpeed();
	m_ulPlsPeriod = GetDoc().GetDrlRegPulsePeriod();
	m_ulPlsRelease = GetDoc().GetDrlRegPulseRelease();

	m_iPluseTimes = GetDoc().GetDrlRegPulseTimes();//ly add 20121030

    m_cmbAperture.SetCurSel(GetDoc().GetDrlRegAperture()-1);		//2009 12 24 
//  m_cmbAperture.SetCurSel(GetDoc().GetDrlRegShowAperture()-1);		//2009 12 24 
	m_cmbPlsNum.SetCurSel(GetDoc().GetDrlRegPlsNum()-1);

//yutingxun 7-5 06
	m_lTxtJumpDelay = GetDoc().GetDrlTxtJumpDelay();
	m_lTxtJumpSpeed = GetDoc().GetDrlTxtJumpSpeed();
	m_ulTxtPlsPeriod = GetDoc().GetDrlTxtPulsePeriod();
	m_ulTxtPlsRelease = GetDoc().GetDrlTxtPulseRelease();

    m_cmbTxtAperture.SetCurSel(GetDoc().GetDrlTxtAperture()-1);         // 2009 12 24 liq
//  m_cmbTxtAperture.SetCurSel(GetDoc().GetDrlTxtShowAperture()-1);         // 2009 12 24 liq
	m_cmbTxtPlsNum.SetCurSel(GetDoc().GetDrlTxtPlsNum()-1);
//
	m_cmbAdjAperture.SetCurSel(GetDoc().GetAdjustAperture()-1);				//2009 12 24 liq
//	m_cmbAdjAperture.SetCurSel(GetDoc().GetAdjustShowAperture()-1);				//2009 12 24 liq
	m_cmbLongPathAdjAperture.SetCurSel(GetDoc().GetLongPathAdjustAperture()-1);		//2009 12 24 liq
//	m_cmbLongPathAdjAperture.SetCurSel(GetDoc().GetLongPathAdjustShowAperture()-1);		//2009 12 24 liq
    m_ulAdjJmpDelay = GetDoc().GetAdjustJumpDelay();
	m_ulAdjJmpSpeed = GetDoc().GetAdjustJumpSpeed();
	m_ulAdjPlsPeriod = GetDoc().GetAdjustPulsePeriod();
	m_ulAdjPlsRelease = GetDoc().GetAdjustPulseRelease();
//
	m_ulGlvAdjPlsRelease = GetDoc().GetGlvAdjPlsRelease();
	m_iRegionDim=GetDoc().GetRegionDim();
	m_fTextHeigth=GetDoc().GetTextHeigth();

//	m_lGlvAdjPosX = GetDoc().GetGlvAdjPosX();
//	m_lGlvAdjPosY = GetDoc().GetGlvAdjPosY();

#ifdef USELOG
	GetLog().Append_pro(10051,20049);//"恢复参数","加工参数"
#endif
	UpdateData(FALSE);
}

void CProcParaView::OnSetProcPara() 
{
	UpdateData();

	GetDoc().SetDrlRegionPointDis(m_RegionPointDis);

    GetDoc().SetDrlRegJumpDelay(m_lJumpDelay);
	GetDoc().SetDrlRegJumpSpeed(m_lJumpSpeed);
	
	GetDoc().SetDrlRegPulsePeriod(m_ulPlsPeriod);
	GetDoc().SetDrlRegPulseTimes(m_iPluseTimes);
	GetDoc().SetDrlRegPulseRelease(m_ulPlsRelease);
    GetDoc().SetDrlRegPulse2Release(m_ulPls2Release);
	GetDoc().SetDrlRegPulse3Release(m_ulPls3Release);
	GetDoc().SetDrlRegPulse4Release(m_ulPls4Release);
	GetDoc().SetDrlRegPulse5Release(m_ulPls5Release);

    GetDoc().SetGlvAdjPlsRelease(m_ulGlvAdjPlsRelease);
//	GetDoc().SetGlvAdjPosX(m_lGlvAdjPosX);
//	GetDoc().SetGlvAdjPosY(m_lGlvAdjPosY);

	GetDoc().SetAdjustJumpDelay(m_ulAdjJmpDelay);
	GetDoc().SetAdjustJumpSpeed(m_ulAdjJmpSpeed);
	GetDoc().SetAdjustPulsePeriod(m_ulAdjPlsPeriod);
	GetDoc().SetAdjustPulseRelease(m_ulAdjPlsRelease);
	GetDoc().SetAdjustAperture(m_cmbAdjAperture.GetCurSel()+1);
	GetDoc().SetLongPathAdjustAperture(m_cmbLongPathAdjAperture.GetCurSel()+1);
	GetDoc().SetDrlRegPlsNum(m_cmbPlsNum.GetCurSel()+1);
    GetDoc().SetDrlRegAperture(m_cmbAperture.GetCurSel()+1);

	GetDoc().SetDrlTxtJumpDelay(m_lTxtJumpDelay);
	GetDoc().SetDrlTxtJumpSpeed(m_lTxtJumpSpeed);
	GetDoc().SetDrlTxtPulsePeriod(m_ulTxtPlsPeriod);
	GetDoc().SetDrlTxtPulseRelease(m_ulTxtPlsRelease);
	GetDoc().SetDrlTxtPlsNum(m_cmbTxtPlsNum.GetCurSel()+1);
	GetDoc().SetDrlTxtAperture(m_cmbTxtAperture.GetCurSel()+1);
	GetDoc().SetRegionDim(m_iRegionDim);
	GetDoc().SetTextHeigth(m_fTextHeigth);

#ifdef USELOG
	GetLog().Append_pro(10049,20049);//"设置参数","加工参数"
#endif
}

void CProcParaView::OnSaveProcPara() 
{
	OnSetProcPara();
//	GetDoc().ReleaseSysDoc();
	GetDoc().SaveProcessParam();
	Delay(200);
	AfxMessageBox("参数已设定并保存！");

#ifdef USELOG
	GetLog().Append_pro(10050,20049);//"保存参数","加工参数"
#endif
}

void CProcParaView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if(bActivate)
	{
		
		if (GetDoc().GetTechnicType()==0)
		{
			m_cmbAdjAperture.ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC13)->ShowWindow(TRUE);
		}
		else
		{
			m_cmbAdjAperture.ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC13)->ShowWindow(FALSE);
		}

		if (GetDoc().GetIsDrillRegion())
			m_CheckDrillRegion.SetCheck(TRUE);
		else
			m_CheckDrillRegion.SetCheck(FALSE);
			
		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			m_edtRegionDim.EnableWindow(TRUE);//内层标靶开窗参数
			m_cmbAperture.EnableWindow(TRUE);
			m_edtPluseTimes.EnableWindow(TRUE);//ly add 20121030
			m_edtPlsRelease.EnableWindow(TRUE);
			m_edtPls2Release.EnableWindow(TRUE);
			m_edtPls3Release.EnableWindow(TRUE);
			m_edtPls4Release.EnableWindow(TRUE);
			m_edtPls5Release.EnableWindow(TRUE);
			m_edtPlsPeriod.EnableWindow(FALSE);
			m_edtJumpSpeed.EnableWindow(FALSE);
			m_edtJumpDelay.EnableWindow(FALSE);

			m_cmbAdjAperture.EnableWindow(FALSE);//振镜校正参数
			m_cmbLongPathAdjAperture.EnableWindow(FALSE);
			m_edtGlvAdjPlsRelease.EnableWindow(FALSE);
			m_edtAdjPlsRelease.EnableWindow(FALSE);
			m_edtAdjPlsPeriod.EnableWindow(FALSE);
			m_edtAdjJmpSpeed.EnableWindow(FALSE);
			m_edtAdjJmpDelay.EnableWindow(FALSE);

			m_edtTextHeigth.EnableWindow(FALSE);//字符加工参数
			m_cmbTxtPlsNum.EnableWindow(FALSE);
			m_cmbTxtAperture.EnableWindow(FALSE);
			m_edtTxtPlsRelease.EnableWindow(FALSE);
			m_edtTxtPlsPeriod.EnableWindow(FALSE);
			m_edtTxtJumpSpeed.EnableWindow(FALSE);
			m_edtTxtJumpDelay.EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ACCURAY)->EnableWindow(FALSE);
		}
		else if(nLevel==SystemDoc::SUPEROR)//高级
		{
			m_edtRegionDim.EnableWindow(TRUE);//内层标靶开窗参数
			m_cmbAperture.EnableWindow(TRUE);
			m_edtPluseTimes.EnableWindow(TRUE);//ly add 20121030
			m_edtPlsRelease.EnableWindow(TRUE);
			m_edtPls2Release.EnableWindow(TRUE);
			m_edtPls3Release.EnableWindow(TRUE);
			m_edtPls4Release.EnableWindow(TRUE);
			m_edtPls5Release.EnableWindow(TRUE);
			m_edtPlsPeriod.EnableWindow(FALSE);
			m_edtJumpSpeed.EnableWindow(FALSE);
			m_edtJumpDelay.EnableWindow(FALSE);

			m_cmbAdjAperture.EnableWindow(TRUE);//振镜校正参数
			m_cmbLongPathAdjAperture.EnableWindow(TRUE);
			m_edtGlvAdjPlsRelease.EnableWindow(TRUE);
			m_edtAdjPlsRelease.EnableWindow(TRUE);
			m_edtAdjPlsPeriod.EnableWindow(FALSE);
			m_edtAdjJmpSpeed.EnableWindow(FALSE);
			m_edtAdjJmpDelay.EnableWindow(FALSE);

			m_edtTextHeigth.EnableWindow(TRUE);//字符加工参数
			m_cmbTxtPlsNum.EnableWindow(TRUE);
			m_cmbTxtAperture.EnableWindow(TRUE);
			m_edtTxtPlsRelease.EnableWindow(TRUE);
			m_edtTxtPlsPeriod.EnableWindow(FALSE);
			m_edtTxtJumpSpeed.EnableWindow(FALSE);
			m_edtTxtJumpDelay.EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ACCURAY)->EnableWindow(FALSE);
		}
	    else if(nLevel==SystemDoc::ADMIN)//系统
		{
			m_edtRegionDim.EnableWindow(TRUE);//内层标靶开窗参数
			m_cmbAperture.EnableWindow(TRUE);
			m_edtPluseTimes.EnableWindow(TRUE);//ly add 20121030
			m_edtPlsRelease.EnableWindow(TRUE);
			m_edtPls2Release.EnableWindow(TRUE);
			m_edtPls3Release.EnableWindow(TRUE);
			m_edtPls4Release.EnableWindow(TRUE);
			m_edtPls5Release.EnableWindow(TRUE);
			m_edtPlsPeriod.EnableWindow(TRUE);
			m_edtJumpSpeed.EnableWindow(TRUE);
			m_edtJumpDelay.EnableWindow(TRUE);

			m_cmbAdjAperture.EnableWindow(TRUE);//振镜校正参数
			m_cmbLongPathAdjAperture.EnableWindow(TRUE);
			m_edtGlvAdjPlsRelease.EnableWindow(TRUE);
			m_edtAdjPlsRelease.EnableWindow(TRUE);
			m_edtAdjPlsPeriod.EnableWindow(TRUE);
			m_edtAdjJmpSpeed.EnableWindow(TRUE);
			m_edtAdjJmpDelay.EnableWindow(TRUE);

			m_edtTextHeigth.EnableWindow(TRUE);//字符加工参数
			m_cmbTxtPlsNum.EnableWindow(TRUE);
			m_cmbTxtAperture.EnableWindow(TRUE);
			m_edtTxtPlsRelease.EnableWindow(TRUE);
			m_edtTxtPlsPeriod.EnableWindow(TRUE);
			m_edtTxtJumpSpeed.EnableWindow(TRUE);
			m_edtTxtJumpDelay.EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_ACCURAY)->EnableWindow(true);
		}
	}

	m_edtPlsPeriod.EnableWindow(FALSE);//ly add 20111208---------------
	m_edtJumpSpeed.EnableWindow(FALSE);
	m_edtJumpDelay.EnableWindow(FALSE);
	
	m_edtAdjPlsPeriod.EnableWindow(FALSE);
	m_edtAdjJmpSpeed.EnableWindow(FALSE);
	m_edtAdjJmpDelay.EnableWindow(FALSE);
	
	m_edtTxtPlsPeriod.EnableWindow(FALSE);
	m_edtTxtJumpSpeed.EnableWindow(FALSE);
	m_edtTxtJumpDelay.EnableWindow(FALSE);//ly add 20111208---------------

			

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CProcParaView::OnSelchangeCmbAperture() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
	if(m_cmbAperture.GetCurSel()>7)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于8#光圈!"
		
		m_cmbAperture.SetCurSel(7);
		UpdateData(FALSE);
	}
	
#else//ly change 20110122 12光圈
	if(m_cmbAperture.GetCurSel()>11)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于12#光圈!"
		
		m_cmbAperture.SetCurSel(11);
		UpdateData(FALSE);
	}
#endif
#else
//ly change 20110122 18光圈
	if(m_cmbAperture.GetCurSel()>17)
	{
		strncpy(ez,GetLang().GetWarningText(21060),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于18#光圈!"

		m_cmbAperture.SetCurSel(17);
		UpdateData(FALSE);
	}
#endif
}

void CProcParaView::OnSelchangeCmbAdjaperture() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
	if(m_cmbAdjAperture.GetCurSel()>7)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于8#光圈!"
		
		m_cmbAdjAperture.SetCurSel(7);
		UpdateData(FALSE);
	}
	
#else//ly change 20110122 12光圈
	if(m_cmbAdjAperture.GetCurSel()>11)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于12#光圈!"
		
		m_cmbAdjAperture.SetCurSel(11);
		UpdateData(FALSE);
	}
#endif
#else
//ly change 20110122 18光圈
	if(m_cmbAdjAperture.GetCurSel()>17)
	{
		strncpy(ez,GetLang().GetWarningText(21060),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于18#光圈!"

		m_cmbAdjAperture.SetCurSel(17);
		UpdateData(FALSE);
	}
#endif
}

void CProcParaView::OnSelchangeCmbLongpathAdjaperture() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
	if(m_cmbLongPathAdjAperture.GetCurSel()>7)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于8#光圈!"
		
		m_cmbLongPathAdjAperture.SetCurSel(7);
		UpdateData(FALSE);
	}
	
#else//ly change 20110122 12光圈
	if(m_cmbLongPathAdjAperture.GetCurSel()>11)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于12#光圈!"
		
		m_cmbLongPathAdjAperture.SetCurSel(11);
		UpdateData(FALSE);
	}
#endif
#else
//ly change 20110122 18光圈
	if(m_cmbLongPathAdjAperture.GetCurSel()>17)
	{
		strncpy(ez,GetLang().GetWarningText(21060),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于18#光圈!"

		m_cmbLongPathAdjAperture.SetCurSel(17);
		UpdateData(FALSE);
	}
#endif
}

void CProcParaView::OnSelchangeCmbTxtperture() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
	if(m_cmbTxtAperture.GetCurSel()>7)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于8#光圈!"
		
		m_cmbTxtAperture.SetCurSel(7);
		UpdateData(FALSE);
	}
	
#else//ly change 20110122 12光圈
	if(m_cmbTxtAperture.GetCurSel()>11)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于12#光圈!"
		
		m_cmbTxtAperture.SetCurSel(11);
		UpdateData(FALSE);
	}
#endif
#else
//ly change 20110122 18光圈
	if(m_cmbTxtAperture.GetCurSel()>17)
	{
		strncpy(ez,GetLang().GetWarningText(21060),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于18#光圈!"

		m_cmbTxtAperture.SetCurSel(17);
		UpdateData(FALSE);
	}
#endif
}

void CProcParaView::OnCountClear() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};//ly 20110404
	strncpy(ez,GetLang().GetWarningText(21061),256);
	if(AfxMessageBox(ez,MB_OKCANCEL) == IDCANCEL)//"确定要将校正次数清零吗?"
		return;

	GetDoc().SetOrgTimes(HeadLeft,0);
	GetDoc().SetOrgTimes(HeadRight,0);
	GetDoc().SetPatternTimes(HeadLeft,0);
	GetDoc().SetPatternTimes(HeadRight,0);
	GetDoc().WriteCaliTimes();	
}

void CProcParaView::OnButtonAccuray() //jpc add 20130307
{
	GetDoc().m_PatternXTimes[0]=0;
	GetDoc().m_PatternXTimes[1]=0;	
	GetDoc().m_PatternYTimes[0]=0;
	GetDoc().m_PatternYTimes[1]=0;
	GetDoc().WriteCaliTimes();	
}

void CProcParaView::OnCheckDrillregion() 
{
	if (1==m_CheckDrillRegion.GetCheck())
		GetDoc().SetIsDrillRegion(TRUE);
	else
		GetDoc().SetIsDrillRegion(FALSE);
}

void CProcParaView::OnCheckDrillcoil()									//20170224
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	GetDoc().SetDrillCoil(m_chkDrillCoil);	
}
