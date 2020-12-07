// LampAdjDlgView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "LampAdjDlgView.h"

#include "SysParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLampAdjDlgView dialog

CLampAdjDlgView::CLampAdjDlgView(CWnd* pParent /*=NULL*/)
: CDialog(CLampAdjDlgView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLampAdjDlgView)
	m_vaEditLC = 0;
	m_vaEditLR = 0;
	m_vaEditRC = 0;
	m_vaEditRR = 0;
	m_radExt = 0;
	m_radPriChannel = 0;
	m_SysLamps = false;
	m_LongLeftInfared = 0;
	m_LongRightInfared = 0;
	//}}AFX_DATA_INIT
}

void CLampAdjDlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLampAdjDlgView)
	DDX_Control(pDX, IDC_EDIT_RINFRARED, m_Edit_RightInfrared);
	DDX_Control(pDX, IDC_EDIT_LINFRARED, m_Edit_LeftInfrared);
	DDX_Control(pDX, IDC_SDER_RINFRARED, m_Slider_RightInfrared);
	DDX_Control(pDX, IDC_SDER_LINFRARED, m_Slider_LeftInfrared);
	DDX_Control(pDX, IDC_CHECKRINFRARED, m_Check_RightInfrared);
	DDX_Control(pDX, IDC_CHECKLINFRARED, m_Check_LeftInfrared);
	DDX_Control(pDX, IDC_CCDLUMINSET, m_btnLuminSet);
	DDX_Control(pDX, IDC_SELECTMANUALHECK, m_chkSelectManual);
	DDX_Control(pDX, IDC_RESETCCDLUMINPARA, m_btnResetCCDLumPara);
	DDX_Control(pDX, IDC_RIGHTROPENCHECK, m_chkRightROpen);
	DDX_Control(pDX, IDC_RIGHTCOPENCHECK, m_chkRightCOpen);
	DDX_Control(pDX, IDC_LEFTROPENCHECK, m_chkLeftROpen);
	DDX_Control(pDX, IDC_LEFTCOPENCHECK, m_chkLeftCOpen);
	DDX_Control(pDX, IDOK, m_LightParaOk);
	DDX_Control(pDX, IDC_BT_SAVELIGHT, m_LightParaSave);
	DDX_Control(pDX, IDC_SDER_RR, m_sliderRR);
	DDX_Control(pDX, IDC_SDER_RC, m_sliderRC);
	DDX_Control(pDX, IDC_SDER_LR, m_sliderLR);
	DDX_Control(pDX, IDC_SDER_LC, m_sliderLC);
	DDX_Control(pDX, IDC_EDIT_RR, m_conEditRR);
	DDX_Control(pDX, IDC_EDIT_RC, m_conEditRC);
	DDX_Control(pDX, IDC_EDIT_LR, m_conEditLR);
	DDX_Control(pDX, IDC_EDIT_LC, m_conEditLC);
	DDX_Text(pDX, IDC_EDIT_LC, m_vaEditLC);
	DDX_Text(pDX, IDC_EDIT_LR, m_vaEditLR);
	DDX_Text(pDX, IDC_EDIT_RC, m_vaEditRC);
	DDX_Text(pDX, IDC_EDIT_RR, m_vaEditRR);
	DDX_Radio(pDX, IDC_RAD_EXT, m_radExt);
	DDX_Radio(pDX, IDC_RADIO2, m_radPriChannel);
	DDX_Text(pDX, IDC_EDIT_LINFRARED, m_LongLeftInfared);
	DDX_Text(pDX, IDC_EDIT_RINFRARED, m_LongRightInfared);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLampAdjDlgView, CDialog)
//{{AFX_MSG_MAP(CLampAdjDlgView)
ON_BN_CLICKED(IDC_BT_SAVELIGHT, OnBtSavelight)
ON_BN_CLICKED(IDC_RESETCCDLUMINPARA, OnResetccdluminpara)
ON_BN_CLICKED(IDC_RAD_EXT, OnLightSelect)
ON_BN_CLICKED(IDC_LEFTCOPENCHECK, OnLeftcopencheck)
ON_BN_CLICKED(IDC_LEFTROPENCHECK, OnLeftropencheck)
ON_BN_CLICKED(IDC_RIGHTCOPENCHECK, OnRightcopencheck)
ON_BN_CLICKED(IDC_RIGHTROPENCHECK, OnRightropencheck)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDER_LC, OnCustomdrawSderLc)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDER_LR, OnCustomdrawSderLr)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDER_RC, OnCustomdrawSderRc)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDER_RR, OnCustomdrawSderRr)
ON_BN_CLICKED(IDC_CCDLUMINSET, OnCcdluminset)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO2, OnPriChannelSelect)
	ON_BN_CLICKED(IDC_RADIO3, OnSubChannelSelect)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDER_LINFRARED, OnOutofmemorySderLinfrared)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SDER_RINFRARED, OnOutofmemorySderRinfrared)
	ON_BN_CLICKED(IDC_CHECKLINFRARED, OnChecklinfrared)
	ON_BN_CLICKED(IDC_RADIO5, OnLightSelect)
	ON_BN_CLICKED(IDC_RADIO6, OnLightSelect)
	ON_BN_CLICKED(IDC_RADIO7, OnLightSelect)
	ON_BN_CLICKED(IDC_RADIO8, OnLightSelect)
	ON_BN_CLICKED(IDC_RADIO1, OnLightSelect)
	ON_BN_CLICKED(IDC_CHECKRINFRARED, OnCheckrinfrared)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLampAdjDlgView message handlers
void CLampAdjDlgView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("LampAdj","IDC_STATIC8",szRead,20);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("LampAdj","IDC_RAD_EXT",szRead,20);
	SetDlgItemText(IDC_RAD_EXT,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO5",szRead,20);
	SetDlgItemText(IDC_RADIO5,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO6",szRead,20);
	SetDlgItemText(IDC_RADIO6,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO7",szRead,20);
	SetDlgItemText(IDC_RADIO7,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO8",szRead,20);
	SetDlgItemText(IDC_RADIO8,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO1",szRead,20);
	SetDlgItemText(IDC_RADIO1,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC1",szRead,20);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO2",szRead,20);
	SetDlgItemText(IDC_RADIO2,szRead);
	GetLang().GetUIText("LampAdj","IDC_RADIO3",szRead,20);
	SetDlgItemText(IDC_RADIO3,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC2",szRead,20);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC3",szRead,20);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC4",szRead,20);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("LampAdj","IDC_LEFTCOPENCHECK",szRead,20);
	SetDlgItemText(IDC_LEFTCOPENCHECK,szRead);
	GetLang().GetUIText("LampAdj","IDC_LEFTROPENCHECK",szRead,20);
	SetDlgItemText(IDC_LEFTROPENCHECK,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC5",szRead,20);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC6",szRead,20);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("LampAdj","IDC_STATIC7",szRead,20);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("LampAdj","IDC_RIGHTCOPENCHECK",szRead,20);
	SetDlgItemText(IDC_RIGHTCOPENCHECK,szRead);
	GetLang().GetUIText("LampAdj","IDC_RIGHTROPENCHECK",szRead,20);
	SetDlgItemText(IDC_RIGHTROPENCHECK,szRead);
	GetLang().GetUIText("LampAdj","IDC_RESETCCDLUMINPARA",szRead,20);
	SetDlgItemText(IDC_RESETCCDLUMINPARA,szRead);
	GetLang().GetUIText("LampAdj","IDC_CCDLUMINSET",szRead,20);
	SetDlgItemText(IDC_CCDLUMINSET,szRead);
	GetLang().GetUIText("LampAdj","IDC_BT_SAVELIGHT",szRead,20);
	SetDlgItemText(IDC_BT_SAVELIGHT,szRead);
	GetLang().GetUIText("LampAdj","IDOK",szRead,20);
	SetDlgItemText(IDOK,szRead);
}

BOOL CLampAdjDlgView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	m_btnResetCCDLumPara.SetIcon(IDI_RESET,IDI_RESET);
	
	m_LightParaSave.SetIcon(IDI_SAVEP,IDI_SAVEP);
	m_LightParaOk.SetIcon(IDI_CLOSE,IDI_CLOSE);
	m_conEditLC.SetSlideLink(this,IDC_SDER_LC);
	m_conEditLC.SetParams( 1,100 , 1 );//ly change 0,100--->1,100 20110617
	m_conEditLC.SetValue(m_vaEditLC);
	m_sliderLC.SetSlidePos(m_vaEditLC);
	m_sliderLC.SetSlideRange(1,100);
	
	m_conEditLR.SetSlideLink(this,IDC_SDER_LR);
	m_conEditLR.SetParams( 1,255 , 1 );//ly change 0,255--->1,255 20110617
	m_conEditLR.SetValue(m_vaEditLR);
	
	m_sliderLR.SetSlidePos(m_vaEditLR);
	m_sliderLR.SetSlideRange(1,255);	

	//红外
	m_Edit_LeftInfrared.SetSlideLink(this,IDC_SDER_LINFRARED);
	m_Edit_LeftInfrared.SetParams( 1,255 , 1 );
	m_Edit_LeftInfrared.SetValue(m_LongLeftInfared);
	m_Slider_LeftInfrared.SetSlidePos(m_LongLeftInfared);
	m_Slider_LeftInfrared.SetSlideRange(1,255);
	
	m_Edit_RightInfrared.SetSlideLink(this,IDC_SDER_RINFRARED);
	m_Edit_RightInfrared.SetParams( 1,255 , 1 );
	m_Edit_RightInfrared.SetValue(m_LongRightInfared);
	m_Slider_RightInfrared.SetSlidePos(m_LongRightInfared);
	m_Slider_RightInfrared.SetSlideRange(1,255);	

	m_btnLuminSet.SetIcon(IDI_SET,IDI_SET);
		
	m_conEditRC.SetSlideLink(this,IDC_SDER_RC);
	m_conEditRC.SetParams( 1,100 , 1 );//ly change 0,100--->1,100 20110617
	m_conEditRC.SetValue(m_vaEditRC); 
	m_sliderRC.SetSlidePos(m_vaEditRC);
	m_sliderRC.SetSlideRange(1,100);
		
	m_conEditRR.SetSlideLink(this,IDC_SDER_RR);
	m_conEditRR.SetParams( 1,255 , 1 );//ly change 0,255--->1,255 20110617
	m_conEditRR.SetValue(m_vaEditRR);
	m_sliderRR.SetSlidePos(m_vaEditRR);
	m_sliderRR.SetSlideRange(1,255);
	//	this->m_raExt.SetCheck(1);
#ifdef CCSRING
	GetControl().ChannelOutput(OCCDLIGHTTUNEBITLCEN , IO_OFF);	//同轴光低电平打开(CCS)
	GetControl().ChannelOutput(OCCDLIGHTTUNEBITRCEN , IO_OFF);
	GetControl().ChannelOutput(OCCDLIGHTSOURCELEFT , IO_OFF);	//环形光低电平打开(CCS)
	GetControl().ChannelOutput(OCCDLIGHTSOURCERIGHT , IO_OFF);
#else
	GetControl().ChannelOutput(OCCDLIGHTONL,IO_ON);			//环形光高电平打开(Moritex)
	GetControl().ChannelOutput(OCCDLIGHTONR,IO_ON);	
	#ifdef IO_C//ly add 20110127
	GetControl().ChannelOutput(OCCDLIGHTONCOL,IO_ON);		//同轴光高电平打开
	GetControl().ChannelOutput(OCCDLIGHTONCOR,IO_ON);
	#else
	GetControl().ChannelOutput(OCCDLIGHTONCOL,IO_OFF);		//同轴光低电平打开(CCS)
	GetControl().ChannelOutput(OCCDLIGHTONCOR,IO_OFF);
	#endif

	if (1==GetDoc().GetInfrared())
	{//红外
		GetControl().ChannelOutput(OCCDLIGHTONCOL1,IO_ON);
		GetControl().ChannelOutput(OCCDLIGHTONCOR1,IO_ON);
	}

#endif

	m_chkRightROpen.SetCheck(true);
	m_chkRightCOpen.SetCheck(true);
	m_chkLeftROpen.SetCheck(true);
	m_chkLeftCOpen.SetCheck(true);
	m_Check_LeftInfrared.SetCheck(true);
    m_Check_RightInfrared.SetCheck(true);

	m_vaEditLC = GetDoc().GetCCDLightness(0,0);
	m_vaEditLR = GetDoc().GetCCDLightness(0,1);
	m_vaEditRC = GetDoc().GetCCDLightness(1,0);
	m_vaEditRR = GetDoc().GetCCDLightness(1,1);	
	//infared
	m_LongLeftInfared=GetDoc().GetCCDInfrared(0,0);
	m_LongRightInfared=GetDoc().GetCCDInfrared(1,0);

	m_sliderLC.SetSlidePos(m_vaEditLC);
	m_sliderLR.SetSlidePos(m_vaEditLR);
	m_sliderRC.SetSlidePos(m_vaEditRC);
	m_sliderRR.SetSlidePos(m_vaEditRR);
	//infared
	m_Slider_LeftInfrared.SetSlidePos(m_LongLeftInfared);
	m_Slider_RightInfrared.SetSlidePos(m_LongRightInfared);
    
	UpdateData(false);	//ly mark 20110603
	
	GetControl().SetCCDCaxLuminance(m_vaEditLC,LEFTCHAN);
	GetControl().SetCCDCaxLuminance(m_vaEditRC,RIGHTCHAN);
	GetControl().SetCCDLuminance(m_vaEditLR,LEFTCHAN);
	GetControl().SetCCDLuminance(m_vaEditRR,RIGHTCHAN);	
	
	GetControl().SetCCDInFrared(m_LongLeftInfared,LEFTCHAN);	
	GetControl().SetCCDInFrared(m_LongRightInfared,RIGHTCHAN);
	if (1!=GetDoc().GetInfrared())
	{//不开启不显示
		GetDlgItem(IDC_STATICLINFRARED)->ShowWindow(FALSE);
		GetDlgItem(IDC_SDER_LINFRARED)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_LINFRARED)->ShowWindow(FALSE);
		GetDlgItem(IDC_CHECKLINFRARED)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC10)->ShowWindow(FALSE);
		GetDlgItem(IDC_SDER_RINFRARED)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RINFRARED)->ShowWindow(FALSE);
		GetDlgItem(IDC_CHECKRINFRARED)->ShowWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLampAdjDlgView::OnBtSavelight() 
{
//	if(!m_SysLamps)
//	{
//		m_SysLamps = true;
		OnCcdluminset() ;
		GetDoc().SaveCCDLuminancePara();
//		m_SysLamps = false;
//	}
}

void CLampAdjDlgView::OnResetccdluminpara() 
{
	if(!m_SysLamps)
	{
		m_SysLamps = true;
		GetDoc().LoadCCDLuminancePara();
		OnLightSelect();
		m_SysLamps = false;
	}
}

void CLampAdjDlgView::OnLightSelect() 
{
	UpdateData();
	m_vaEditLC = GetDoc().GetCCDLightness(LEFTCHAN,COAXIAL,m_radExt);
	m_vaEditLR = GetDoc().GetCCDLightness(LEFTCHAN,RINGED,m_radExt);
	m_vaEditRC = GetDoc().GetCCDLightness(RIGHTCHAN,COAXIAL,m_radExt);
	m_vaEditRR = GetDoc().GetCCDLightness(RIGHTCHAN,RINGED,m_radExt);
	
	m_LongLeftInfared = GetDoc().GetCCDInfrared(LEFTCHAN,m_radExt);
	m_LongRightInfared = GetDoc().GetCCDInfrared(RIGHTCHAN,m_radExt);

	UpdateData(FALSE);
	m_sliderLC.SetSlidePos(m_vaEditLC);
	m_sliderLR.SetSlidePos(m_vaEditLR);
	m_sliderRC.SetSlidePos(m_vaEditRC);
	m_sliderRR.SetSlidePos(m_vaEditRR);

	m_Slider_LeftInfrared.SetSlidePos(m_LongLeftInfared);
	m_Slider_RightInfrared.SetSlidePos(m_LongRightInfared);

	UpdateData(FALSE);
	
	GetControl().SetCCDCaxLuminance(m_vaEditLC,LEFTCHAN);
	GetControl().SetCCDCaxLuminance(m_vaEditRC,RIGHTCHAN);
	GetControl().SetCCDLuminance(m_vaEditLR,LEFTCHAN);
	GetControl().SetCCDLuminance(m_vaEditRR,RIGHTCHAN);	

	GetControl().SetCCDInFrared(m_LongLeftInfared,LEFTCHAN);
	GetControl().SetCCDInFrared(m_LongRightInfared,RIGHTCHAN);	
}

void CLampAdjDlgView::OnLeftcopencheck() 
{
#ifdef CCSRING
	GetControl().ChannelOutput(OCCDLIGHTTUNEBITLCEN, m_chkLeftCOpen.GetCheck()==IO_OFF);
#else	
	#ifdef IO_C
	GetControl().ChannelOutput(OCCDLIGHTONCOL, m_chkLeftCOpen.GetCheck()==IO_ON);
	#else
	GetControl().ChannelOutput(OCCDLIGHTONCOL, m_chkLeftCOpen.GetCheck()==IO_OFF);
	#endif
#endif
}

void CLampAdjDlgView::OnLeftropencheck() 
{
#ifdef CCSRING
	GetControl().ChannelOutput(OCCDLIGHTSOURCELEFT,m_chkLeftROpen.GetCheck()==IO_OFF);
#else
	GetControl().ChannelOutput(OCCDLIGHTONL,m_chkLeftROpen.GetCheck()==IO_ON);	
#endif
}

void CLampAdjDlgView::OnRightcopencheck() 
{
#ifdef CCSRING
	GetControl().ChannelOutput(OCCDLIGHTTUNEBITRCEN,m_chkRightCOpen.GetCheck()==IO_OFF);
#else
	#ifdef IO_C
	GetControl().ChannelOutput(OCCDLIGHTONCOR,m_chkRightCOpen.GetCheck()==IO_ON);
	#else
	GetControl().ChannelOutput(OCCDLIGHTONCOR,m_chkRightCOpen.GetCheck()==IO_OFF);	
	#endif	
#endif
}

void CLampAdjDlgView::OnRightropencheck() 
{
#ifdef CCSRING
	GetControl().ChannelOutput(OCCDLIGHTSOURCERIGHT, m_chkRightROpen.GetCheck()==IO_OFF);
#else
	GetControl().ChannelOutput(OCCDLIGHTONR, m_chkRightROpen.GetCheck()==IO_ON);	
#endif
}

void CLampAdjDlgView::OnCustomdrawSderLc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	GetControl().SetCCDCaxLuminance(m_vaEditLC,0);	
	*pResult = 0;
}

void CLampAdjDlgView::OnCustomdrawSderLr(NMHDR* pNMHDR, LRESULT* pResult) 
{
    UpdateData();
	GetControl().SetCCDLuminance(m_vaEditLR,0);
	
	*pResult = 0;
}

void CLampAdjDlgView::OnCustomdrawSderRc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	GetControl().SetCCDCaxLuminance(m_vaEditRC,1);	
	*pResult = 0;
}

void CLampAdjDlgView::OnCustomdrawSderRr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	GetControl().SetCCDLuminance(m_vaEditRR,1);	
	*pResult = 0;
}

void CLampAdjDlgView::OnCcdluminset() 
{
	if(!m_SysLamps)
	{
		m_SysLamps = true;
		UpdateData();
		GetDoc().SetCCDLightness(m_vaEditLC,LEFTCHAN,COAXIAL,m_radExt);
		GetDoc().SetCCDLightness(m_vaEditLR,LEFTCHAN,RINGED,m_radExt);
		GetDoc().SetCCDLightness(m_vaEditRC,RIGHTCHAN,COAXIAL,m_radExt);
		GetDoc().SetCCDLightness(m_vaEditRR,RIGHTCHAN,RINGED,m_radExt);	
		//Infrared
		GetDoc().SetCCDInfrared(m_LongLeftInfared,LEFTCHAN,m_radExt);	
		GetDoc().SetCCDInfrared(m_LongRightInfared,RIGHTCHAN,m_radExt);

		m_SysLamps = false;
	}
}

void CLampAdjDlgView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//MessageBox("");	
}

void CLampAdjDlgView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
	{
#ifdef CCSRING
		GetControl().ChannelOutput(OCCDLIGHTTUNEBITLCEN , IO_OFF);	//同轴光低电平打开(CCS)
		GetControl().ChannelOutput(OCCDLIGHTTUNEBITRCEN , IO_OFF);
		GetControl().ChannelOutput(OCCDLIGHTSOURCELEFT , IO_OFF);	//环形光低电平打开(CCS)
		GetControl().ChannelOutput(OCCDLIGHTSOURCERIGHT , IO_OFF);
#else
		GetControl().ChannelOutput(OCCDLIGHTONL,IO_ON);			//环形光高电平打开(Moritex)
		GetControl().ChannelOutput(OCCDLIGHTONR,IO_ON);		
		#ifdef IO_C//ly add 20110127
		GetControl().ChannelOutput(OCCDLIGHTONCOL,IO_ON);		//同轴光高电平打开
		GetControl().ChannelOutput(OCCDLIGHTONCOR,IO_ON);
		#else
		GetControl().ChannelOutput(OCCDLIGHTONCOL,IO_OFF);		//同轴光低电平打开(CCS)
		GetControl().ChannelOutput(OCCDLIGHTONCOR,IO_OFF);
		#endif
#endif
	}

	CDialog::OnShowWindow(bShow, nStatus);
}

void CLampAdjDlgView::OnPriChannelSelect() 
{
	// TODO: Add your control notification handler code here
	GetControl().ChannelOutput(OLCHANNELSELECT,MIO_OFF);	
	GetControl().ChannelOutput(ORCHANNELSELECT,MIO_OFF);
}

void CLampAdjDlgView::OnSubChannelSelect() 
{
	// TODO: Add your control notification handler code here
	GetControl().ChannelOutput(OLCHANNELSELECT,MIO_ON);	
	GetControl().ChannelOutput(ORCHANNELSELECT,MIO_ON);	
}

void CLampAdjDlgView::OnOutofmemorySderLinfrared(NMHDR* pNMHDR, LRESULT* pResult) 
{//
	UpdateData();
	GetControl().SetCCDInFrared(m_LongLeftInfared,0);	
	*pResult = 0;
}

void CLampAdjDlgView::OnOutofmemorySderRinfrared(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	GetControl().SetCCDInFrared(m_LongRightInfared,1);
	*pResult = 0;
}

void CLampAdjDlgView::OnChecklinfrared() 
{//左轴红外线光源开关
	GetControl().ChannelOutput(OCCDLIGHTONCOL1,m_Check_LeftInfrared.GetCheck()==IO_ON);	
	return;
}

void CLampAdjDlgView::OnCheckrinfrared() 
{//右轴红外线光源开关
	GetControl().ChannelOutput(OCCDLIGHTONCOR1,m_Check_RightInfrared.GetCheck()==IO_ON);
	return;
}
