// SignalInputView.cpp : implementation file
//

#include "stdafx.h"
#include "OperateControl.h"
#include "LaserSystem.h"
#include "SignalInputView.h"
#include "Shared Classes/ListReport/ListItem.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSignalInputView

IMPLEMENT_DYNCREATE(CSignalInputView, TVisualFormView)

CSignalInputView::CSignalInputView()
	: TVisualFormView(CSignalInputView::IDD)
{
	//{{AFX_DATA_INIT(CSignalInputView)
	//}}AFX_DATA_INIT
	isActivateView=FALSE;
}

CSignalInputView::~CSignalInputView()
{

}

void CSignalInputView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSignalInputView)
	DDX_Control(pDX, IDC_RTHICKNESS, m_sThicknessHome2);
	DDX_Control(pDX, IDC_LTHICKNESS, m_sThicknessHome1);
	DDX_Control(pDX, IDC_TOPHAT2, m_sTopHat2);
	DDX_Control(pDX, IDC_TOPHAT1, m_sTopHat1);
	DDX_Control(pDX, IDC_RINGLIGHT2ERROR, m_sRingLight2Error);
	DDX_Control(pDX, IDC_RINGLIGHT1ERROR, m_sRingLight1Error);
	DDX_Control(pDX, IDC_TABLECLAMPP, m_sTableClampP);
	DDX_Control(pDX, IDC_TABLECLAMPN, m_sTableClampN);
	DDX_Control(pDX, IDC_LENSWINDOW2ERROR, m_sLensWindow2Error);
	DDX_Control(pDX, IDC_LENSWINDOW1ERROR, m_sLensWindow1Error);
	DDX_Control(pDX, IDC_GAUSSIAN2, m_sGaussian2);
	DDX_Control(pDX, IDC_GAUSSIAN1, m_sGaussian1);
	DDX_Control(pDX, IDC_DUSTPRESSURE2, m_sDustPressure2);
	DDX_Control(pDX, IDC_DUSTPRESSURE1, m_sDustPressure1);
	DDX_Control(pDX, IDC_DOORPROTECT, m_sDoorProtect);
	DDX_Control(pDX, IDC_LASERERROR, m_sLaserError);
	DDX_Control(pDX, IDC_UNLOADOK, m_sUnloadOK);
	DDX_Control(pDX, IDC_THICKNESSERROR2, m_sThicknessError2);
	DDX_Control(pDX, IDC_THICKNESSERROR1, m_sThicknessError1);
	DDX_Control(pDX, IDC_TABYERROR, m_sTableYError);
	DDX_Control(pDX, IDC_TABXERROR, m_sTableXError);
	DDX_Control(pDX, IDC_SWATERCOOLFAULT, m_sSWaterCoolFault);
	DDX_Control(pDX, IDC_SERVOALARMZRIGHT, m_sServoAlarmZR);
	DDX_Control(pDX, IDC_SERVOALARMZLEFT, m_sServoAlarmZL);
	DDX_Control(pDX, IDC_SERVOALARMY, m_sServoAlarmY);
	DDX_Control(pDX, IDC_SERVOALARMX, m_sServoAlarmX);
	DDX_Control(pDX, IDC_SERVOALARMBETSUB, m_sServoAlarmBETSUB);
	DDX_Control(pDX, IDC_SERVOALARMBETPRI, m_sServoAlarmBETPRI);
	DDX_Control(pDX, IDC_READYTOUNLOADOK, m_sReadyToUnloadOK);
	DDX_Control(pDX, IDC_READYLOAD, m_sReadyLoad);
	DDX_Control(pDX, IDC_PUTBOARDONTABABLE, m_sPutBoardOnTable);
	DDX_Control(pDX, IDC_OVERTIMEALARM, m_sOverTimeAlarm);
	DDX_Control(pDX, IDC_ONLYLEFT, m_sOnlyLeft);
	DDX_Control(pDX, IDC_MOTIONSTOPRESET, m_sMotionStopReset);
	DDX_Control(pDX, IDC_LOADOK, m_sLoadOK);
	DDX_Control(pDX, IDC_LASERGASFLUX, m_sLaserGasFlux);
	DDX_Control(pDX, IDC_HOMEALLOK, m_sHomeAllOK);
	DDX_Control(pDX, IDC_DEPOTEMPTY, m_sDepotEmpty);
	DDX_Control(pDX, IDC_AOMTEMPROTECT, m_sAOMTemProtect);
	DDX_Control(pDX, IDC_ALARM, m_sAlarm);
	DDX_Control(pDX, IDC_1842_2ERROR, m_s1842_2Error);
	DDX_Control(pDX, IDC_1842_1ERROR, m_s1842_1Error);
	DDX_Control(pDX, IDC_DRILLMATRIXSWITCH, m_sDrillMatrixSwitch);
	DDX_Control(pDX, IDC_LOADRTHANDVPSEC, m_sLoadRTHandVPSec);
	DDX_Control(pDX, IDC_LOADLTHANDVPSEC, m_sLoadLTHandVPSec);
	DDX_Control(pDX, IDC_UNLOADLTHANDVPSEC, m_sUnloadLTHandVPSec);
	DDX_Control(pDX, IDC_UNLOADRTHANDVPSEC, m_sUnloadRTHandVPSec);
	DDX_Control(pDX, IDC_THICKNESSNL, m_sThicknessNL);
	DDX_Control(pDX, IDC_THICKNESSPR, m_sThicknessPR);
	DDX_Control(pDX, IDC_THICKNESSPL, m_sThicknessPL);
	DDX_Control(pDX, IDC_THICKNESSNR, m_sThickNessNR);
	DDX_Control(pDX, IDC_UNLOADRTVACCUMBACK, m_sUnloadRTVaccumBack);
	DDX_Control(pDX, IDC_UNLOADLTVACCUMBACK, m_sUnloadLTVaccumBack);
	DDX_Control(pDX, IDC_TUNEPOSXPBACK, m_sTunePosXPBack);
	DDX_Control(pDX, IDC_TUNEPOSXNBACK, m_sTunePosXNBack);
	DDX_Control(pDX, IDC_LOADLTVACCUMBACK, m_sLoadLTVaccumBack);
	DDX_Control(pDX, IDC_LOADRTVACCUMBACK, m_sLoadRTVaccumBack);
	DDX_Control(pDX, IDC_UNLOADERPITCH, m_sUnLoaderPich);
	DDX_Control(pDX, IDC_LOADERPITCH, m_sLoaderPich);
	DDX_Control(pDX, IDC_UNLOADERPUSHUPTO, m_sUnloaderPushupTo);
	DDX_Control(pDX, IDC_TUNEPOSYP, m_sTunePosYP);
	DDX_Control(pDX, IDC_LOADVIBRATEP, m_sLoadVibrateP);
	DDX_Control(pDX, IDC_LOADVIBRATEN, m_sLoadVibrateN);
	DDX_Control(pDX, IDC_TUNEPOSYN, m_sTunePosYN);
	DDX_Control(pDX, IDC_TUNEPOSXP, m_sTunePosXP);
	DDX_Control(pDX, IDC_TUNEPOSXN, m_sTunePosXN);
	DDX_Control(pDX, IDC_LIST_IOOUTPUT, m_ioOutput);
	DDX_Control(pDX, IDC_LIST_IOINPUT, m_ioInput);
	DDX_Control(pDX, IDC_FTGATESTATUS2, m_s);
	DDX_Control(pDX, IDC_FTGATESTATUS, m_sFtGateStatus);
	DDX_Control(pDX, IDC_AIRPRESSURE, m_sAirPressure);
	DDX_Control(pDX, IDC_CCDLIGHTERROR2, m_sCCDLightError2);
	DDX_Control(pDX, IDC_CCDLIGHTERROR1, m_sCCDLightError1);
	DDX_Control(pDX, IDC_LOADERPUSHUPTO, m_sLoaderPushUpto);
	DDX_Control(pDX, IDC_UNLOADERFULL, m_sUnloaderFull);
	DDX_Control(pDX, IDC_WATERTEMPERTURE, m_sWaterTemperture);
	DDX_Control(pDX, IDC_WATERPRESS, m_sWaterPress);
	DDX_Control(pDX, IDC_UNDERVOLT, m_sUnderVolt);
	DDX_Control(pDX, IDC_OVERVOLT, m_sOverVolt);
	DDX_Control(pDX, IDC_LASERSHUTTERLN, m_sLaserShutterLN);
	DDX_Control(pDX, IDC_LASERSHUTTERLP, m_sLaserShutterLP);
	DDX_Control(pDX, IDC_LASERSHUTTERRN, m_sLaserShutterRN);
	DDX_Control(pDX, IDC_LASERSHUTTERRP, m_sLaserShutterRP);
	DDX_Control(pDX, IDC_LASERWARMN,     m_sLaserWarmN);
	DDX_Control(pDX, IDC_LASERWARMP,     m_sLaserWarmP);
	DDX_Control(pDX, IDC_TABLTVACUMM,    m_sTabLTVacumm);
	DDX_Control(pDX, IDC_TABRTVACUMM,    m_sTabRTVacumm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSignalInputView, TVisualFormView)
	//{{AFX_MSG_MAP(CSignalInputView)
	ON_MESSAGE(WM_INPUTCHECK,OnCheckInputSignal)
	ON_MESSAGE(WM_INPUTUNCHECK,OnUncheckInputSignal)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_FTGATESTATUS2, OnFtgatestatus2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignalInputView diagnostics

#ifdef _DEBUG
void CSignalInputView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSignalInputView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSignalInputView message handlers



LONG CSignalInputView::OnCheckInputSignal(UINT  wParam, LONG lParam)
{
#ifdef USEIOCARD
	QueryInput();
#endif
	return SetTimer(1,400,NULL);
}
LONG CSignalInputView::OnUncheckInputSignal(UINT  wParam, LONG lParam)
{
	
	KillTimer(1);
	return 0;
}
void CSignalInputView::OnTimer(UINT nIDEvent) 
{
#ifdef USEIOCARD
	QueryInput();
#endif
	TVisualFormView::OnTimer(nIDEvent);
}

BOOL CSignalInputView::QueryInput()
{
//	return 0;

	if (!isActivateView)
		return 0;

	UpdateData();
#ifdef USEIOCARD
//主机气路信号
//	m_sLaserWarmN.SetIcon( GetControl().QueryIOBit(ILASERWARMUPN)?m_hLedOFF:m_hLedON );
	m_sLaserWarmP.SetIcon( GetControl().QueryIOBit(ILASERWARMUPP)?m_hLedOFF:m_hLedON );
	m_sLaserShutterLN.SetIcon( GetControl().QueryIOBit(ILASERSHUTTERLTN)?m_hLedOFF:m_hLedON );
	m_sLaserShutterLP.SetIcon( GetControl().QueryIOBit(ILASERSHUTTERLTP)?m_hLedOFF:m_hLedON );
	m_sLaserShutterRN.SetIcon( GetControl().QueryIOBit(ILASERSHUTTERRTN)?m_hLedOFF:m_hLedON );
	m_sLaserShutterRP.SetIcon( GetControl().QueryIOBit(ILASERSHUTTERRTP)?m_hLedOFF:m_hLedON );
 	
	m_sThicknessNL.SetIcon( GetControl().QueryIOBit(ITHICKNESS1N)?m_hLedOFF:m_hLedON );
	m_sThicknessPL.SetIcon( GetControl().QueryIOBit(ITHICKNESS1P)?m_hLedOFF:m_hLedON );
	m_sThickNessNR.SetIcon( GetControl().QueryIOBit(ITHICKNESS2N)?m_hLedOFF:m_hLedON );
	m_sThicknessPR.SetIcon( GetControl().QueryIOBit(ITHICKNESS2P)?m_hLedOFF:m_hLedON );
	m_sTableClampN.SetIcon( GetControl().QueryIOBit(ITABLECLAMPN)?m_hLedOFF:m_hLedON );
	m_sTableClampP.SetIcon( GetControl().QueryIOBit(ITABLECLAMPP)?m_hLedOFF:m_hLedON );
	m_sTopHat1.SetIcon( GetControl().QueryIOBit(ITOPHAT1N)?m_hLedOFF:m_hLedON );
	m_sGaussian1.SetIcon( GetControl().QueryIOBit(ITOPHAT1P)?m_hLedOFF:m_hLedON );
	m_sTopHat2.SetIcon( GetControl().QueryIOBit(ITOPHAT2N)?m_hLedOFF:m_hLedON );
	m_sGaussian2.SetIcon( GetControl().QueryIOBit(ITOPHAT2P)?m_hLedOFF:m_hLedON );
	m_sDustPressure1.SetIcon( GetControl().QueryIOBit(IDUSTOUT1PRESSURE)?m_hLedOFF:m_hLedON );
	m_sDustPressure2.SetIcon( GetControl().QueryIOBit(IDUSTOUT2PRESSURE)?m_hLedOFF:m_hLedON );

//主机调光路用信号
	m_sDrillMatrixSwitch.SetIcon( GetControl().QueryIOBit(DRILLMATRIXSWITCH)?m_hLedOFF:m_hLedON );
//主机报警信号	
	m_s1842_1Error.SetIcon( GetControl().QueryIOBit(I1842_1ERROR)?m_hLedOFF:m_hLedON );
	m_s1842_2Error.SetIcon( GetControl().QueryIOBit(I1842_2ERROR)?m_hLedOFF:m_hLedON );
	m_sServoAlarmX.SetIcon( GetControl().QueryIOBit(ISERVOALARMX)?m_hLedOFF:m_hLedON );
	m_sServoAlarmY.SetIcon( GetControl().QueryIOBit(ISERVOALARMY)?m_hLedOFF:m_hLedON );
	m_sServoAlarmBETSUB.SetIcon( GetControl().QueryIOBit(ISERVOALARMUNBETSUB)?m_hLedOFF:m_hLedON );
 	m_sServoAlarmBETPRI.SetIcon( GetControl().QueryIOBit(ISERVOALARMUNBETHOST)?m_hLedOFF:m_hLedON );
	m_sServoAlarmZL.SetIcon( GetControl().QueryIOBit(ISERVOALARMZLEFT)?m_hLedOFF:m_hLedON );
	m_sServoAlarmZR.SetIcon( GetControl().QueryIOBit(ISERVOALARMZRIGHT)?m_hLedOFF:m_hLedON );
	m_sMotionStopReset.SetIcon( GetControl().QueryIOBit(MOTIONSTOPRESET)?m_hLedON:m_hLedOFF );
	m_sTabLTVacumm.SetIcon( GetControl().QueryIOBit(ITABLTVACUMM )?m_hLedON:m_hLedOFF );
	m_sTabRTVacumm.SetIcon( GetControl().QueryIOBit(ITABRTVACUMM)?m_hLedON:m_hLedOFF );
	m_sAirPressure.SetIcon( GetControl().QueryIOBit(IAIRPRESSURE)?m_hLedON:m_hLedOFF );
#ifdef IO_C
	m_sWaterTemperture.SetIcon( GetControl().QueryIOBit(ITEMPERATUREFAULT)?m_hLedOFF:m_hLedON );
	m_sWaterPress.SetIcon( GetControl().QueryIOBit(IWATERFLOWPROTECT )?m_hLedOFF:m_hLedON );
	m_sCCDLightError1.SetIcon( GetControl().QueryIOBit(ICOLIGHT1ERROR)?m_hLedOFF:m_hLedON);//同轴光源
 	m_sCCDLightError2.SetIcon( GetControl().QueryIOBit(ICOLIGHT2ERROR)?m_hLedOFF:m_hLedON );
	m_sLaserGasFlux.SetIcon( (!GetControl().QueryIOBit(ILASERGASFLUX))?m_hLedON:m_hLedOFF );//ly delete 20110316 &&(GetDoc().GetLaserPowerState())
	m_sSWaterCoolFault.SetIcon( GetControl().QueryIOBit(ISWATERCOOLFAULT)?m_hLedOFF:m_hLedON );//ly change 20110915	
	if(GetDoc().GetWaterYBJ())
	{
	m_sLaserWarmN.SetIcon( !GetControl().QueryIOBit(ISWATERFAULT)?m_hLedOFF:m_hLedON );//ly add 20110915 YBJ
	}
	m_sAOMTemProtect.SetIcon( GetControl().QueryIOBit(IAOMTEMPROTECT)?m_hLedOFF:m_hLedON );
	m_sThicknessHome1.SetIcon( GetControl().QueryIOBit(ITHICKNESSHOME1)?m_hLedOFF:m_hLedON );
	m_sThicknessHome2.SetIcon( GetControl().QueryIOBit(ITHICKNESSHOME2)?m_hLedOFF:m_hLedON );
#else	
	m_sLaserGasFlux.SetIcon( (!GetControl().QueryIOBit(ILASERGASFLUX)&&(GetDoc().GetLaserPowerState()))?m_hLedON:m_hLedOFF );
	m_sSWaterCoolFault.SetIcon( !GetControl().QueryIOBit(ISWATERCOOLFAULT)?m_hLedOFF:m_hLedON );
	m_sAOMTemProtect.SetIcon( !GetControl().QueryIOBit(IAOMTEMPROTECT)?m_hLedOFF:m_hLedON );
#endif

#ifdef PPLASER
	m_sLaserError.SetIcon( (!GetControl().QueryIOBit(ILASERALERT)&&(GetDoc().GetLaserPowerState()))?m_hLedON:m_hLedOFF);
#else
	#ifdef IO_LASERONOK_HIGH     //高电平有效
		m_sLaserError.SetIcon( (!GetControl().QueryIOBit(ILASERONOK)&&(GetDoc().GetLaserPowerState()))?m_hLedON:m_hLedOFF);
	#else
		m_sLaserError.SetIcon( (GetControl().QueryIOBit(ILASERONOK)&&(GetDoc().GetLaserPowerState()))?m_hLedON:m_hLedOFF);
	#endif
#endif
	m_sTableXError.SetIcon( GetControl().QueryIOBit(ITABXERROR)?m_hLedOFF:m_hLedON );
	m_sTableYError.SetIcon( GetControl().QueryIOBit(ITABYERROR)?m_hLedOFF:m_hLedON );
#ifdef IO_C
	m_sThicknessError1.SetIcon( m_hLedOFF);
	m_sThicknessError2.SetIcon( m_hLedOFF);
#else
	m_sThicknessError1.SetIcon( GetControl().QueryIOBit(ITHICKNESSERROR1)?m_hLedOFF:m_hLedON );
	m_sThicknessError2.SetIcon( GetControl().QueryIOBit(ITHICKNESSERROR2)?m_hLedOFF:m_hLedON );
#endif
//	m_sLensWindow1Error.SetIcon( GetControl().QueryIOBit(ILENSWINDOW1ERROR)?m_hLedOFF:m_hLedON );
//	m_sLensWindow2Error.SetIcon( GetControl().QueryIOBit(ILENSWINDOW2ERROR)?m_hLedOFF:m_hLedON );

#ifdef IO_C
	m_sLensWindow1Error.SetIcon( !GetControl().QueryIOBit(ILENSWINDOW1ERROR)?m_hLedON:m_hLedOFF );
	m_sLensWindow2Error.SetIcon( !GetControl().QueryIOBit(ILENSWINDOW2ERROR)?m_hLedON:m_hLedOFF );
#else
	m_sLensWindow1Error.SetIcon( GetControl().QueryIOBit(ILENSWINDOW1ERROR)?m_hLedON:m_hLedOFF );
	m_sLensWindow2Error.SetIcon( GetControl().QueryIOBit(ILENSWINDOW2ERROR)?m_hLedON:m_hLedOFF );
#endif

	m_sRingLight1Error.SetIcon( GetControl().QueryIOBit(IRINGLIGHT1ERROR)?m_hLedOFF:m_hLedON );
	m_sRingLight2Error.SetIcon( GetControl().QueryIOBit(IRINGLIGHT2ERROR)?m_hLedOFF:m_hLedON );

/*#ifdef DoorPrt_HighLevel
	//c# TTL convert
	m_sDoorProtect.SetIcon( (!GetControl().QueryIOBit(IDOORPROTECT))?m_hLedOFF:m_hLedON );
#else
	m_sDoorProtect.SetIcon( GetControl().QueryIOBit(IDOORPROTECT)?m_hLedOFF:m_hLedON );
#endif*/
	m_sDoorProtect.SetIcon( GetControl().GetDoorWarning()?m_hLedON:m_hLedOFF );	//ly change 20140418
	
	//上下料信号
//	m_sHomeAllOK.SetIcon( GetControl().QueryIOBit(IHOMEALLOK)?m_hLedOFF:m_hLedON );
//	m_sReadyLoad.SetIcon( GetControl().QueryIOBit(IREADYLOAD,1)?m_hLedOFF:m_hLedON );//jpc change 20130912
//	m_sLoadOK.SetIcon( GetControl().QueryIOBit(ILOADOK,1)?m_hLedOFF:m_hLedON );
//	m_sOnlyLeft.SetIcon( GetControl().QueryIOBit(IONLYLEFT,1)?m_hLedOFF:m_hLedON );
//	m_sUnloadOK.SetIcon( GetControl().QueryIOBit(IUNLOADOK,1)?m_hLedOFF:m_hLedON );
//	m_sAlarm.SetIcon( GetControl().QueryIOBit(IALARM,1)?m_hLedOFF:m_hLedON );
//	m_sDepotEmpty.SetIcon( GetControl().QueryIOBit(IDEPOTEMPTY,1)?m_hLedOFF:m_hLedON );
//	m_sPutBoardOnTable.SetIcon( GetControl().QueryIOBit(IPUTBOARDONTABABLE,1)?m_hLedOFF:m_hLedON );
//	m_sReadyToUnloadOK.SetIcon( GetControl().QueryIOBit(IREADYTOUNLOADOK,1)?m_hLedOFF:m_hLedON );
//	m_sOverTimeAlarm.SetIcon( GetControl().QueryIOBit(IOVERTIMEALARM,1)?m_hLedOFF:m_hLedON );

//	m_sThichnessP.SetIcon( GetControl().QueryIOBit(ITHICKNESS1P)?m_hLedOFF:m_hLedON );
//	m_sThichnessN.SetIcon( GetControl().QueryIOBit(ITHICKNESS1N)?m_hLedOFF:m_hLedON );
//	m_sLoadRTHandVN.SetIcon( GetControl().QueryIOBit(ILOADERRTHANDVN)?m_hLedOFF:m_hLedON );//上料右侧手N
//	m_sLoadRTHandVP.SetIcon( GetControl().QueryIOBit(ILOADERRTHANDVP)?m_hLedOFF:m_hLedON );//上料右侧手P
//	m_sLoadLTHandVN.SetIcon( GetControl().QueryIOBit(ILOADERLTHANDVN)?m_hLedOFF:m_hLedON );//上料左侧手N
//	m_sLoadLTHandVP.SetIcon( GetControl().QueryIOBit(ILOADERLTHANDVP)?m_hLedOFF:m_hLedON );//上料左侧手P

//	m_sLoadRTHandVN.SetIcon( GetControl().QueryIOBit(ILOADOK)?m_hLedOFF:m_hLedON );//上料右侧手N
//	m_sLoadRTHandVP.SetIcon( GetControl().QueryIOBit(IREADYLOAD)?m_hLedOFF:m_hLedON );//上料右侧手P
//	m_sLoadLTHandVN.SetIcon( GetControl().QueryIOBit(IHOMEALLOK)?m_hLedOFF:m_hLedON );//上料左侧手N
//	m_sLoadLTHandVP.SetIcon( GetControl().QueryIOBit(IONLYLEFT)?m_hLedOFF:m_hLedON );//上料左侧手P

//	m_sLoadRTVaccum.SetIcon( GetControl().QueryIOBit(ILOADERRSUCKOK1)?m_hLedOFF:m_hLedON );
//	m_sLoadLTVaccum.SetIcon( GetControl().QueryIOBit(ILOADERLSUCKOK1)?m_hLedOFF:m_hLedON );
//	m_sLoadRTVaccumBack.SetIcon( GetControl().QueryIOBit(ILOADERRSUCKOK2)?m_hLedOFF:m_hLedON );
//	m_sLoadLTVaccumBack.SetIcon( GetControl().QueryIOBit(ILOADERLSUCKOK2)?m_hLedOFF:m_hLedON );

//	m_sLoadRTVaccum.SetIcon( GetControl().QueryIOBit(IOVERTIMEALARM)?m_hLedOFF:m_hLedON );
//	m_sLoadLTVaccum.SetIcon( GetControl().QueryIOBit(IDEPOTEMPTY)?m_hLedOFF:m_hLedON );
//	m_sLoadRTVaccumBack.SetIcon( GetControl().QueryIOBit(IPUTBOARDONTABABLE)?m_hLedOFF:m_hLedON );
//	m_sLoadLTVaccumBack.SetIcon( GetControl().QueryIOBit(IREADYTOUNLOADOK)?m_hLedOFF:m_hLedON );

//	m_sLoadPitchPos.SetIcon( GetControl().QueryIOBit(ILOADERDOLLYISRISEARRIVE)?m_hLedOFF:m_hLedON );
//	m_sLoadEmpty.SetIcon( GetControl().QueryIOBit(ILOADEREMPTY)?m_hLedOFF:m_hLedON );
//	m_sLoadPitchPos.SetIcon( GetControl().QueryIOBit(IPROCOK)?m_hLedOFF:m_hLedON );
//	m_sLoadEmpty.SetIcon( GetControl().QueryIOBit(IOVERTIMEALARM)?m_hLedOFF:m_hLedON );

//	m_sUnloadRTHandVN.SetIcon( GetControl().QueryIOBit(IUNLOADERRTHANDVN)?m_hLedOFF:m_hLedON );
//	m_sUnloadRTHandVP.SetIcon( GetControl().QueryIOBit(IUNLOADERRTHANDVP)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTHandVN.SetIcon( GetControl().QueryIOBit(IUNLOADERLTHANDVN)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTHandVP.SetIcon( GetControl().QueryIOBit(IUNLOADERLTHANDVP)?m_hLedOFF:m_hLedON );
//	m_sLoadRTHandVPSec.SetIcon( GetControl().QueryIOBit(ILOADERRTHANDVPSEC)?m_hLedOFF:m_hLedON );
//	m_sLoadLTHandVPSec.SetIcon( GetControl().QueryIOBit(ILOADERLTHANDVPSEC)?m_hLedOFF:m_hLedON );

//	m_sLoadRTHandVPSec.SetIcon( GetControl().QueryIOBit(IALARM)?m_hLedOFF:m_hLedON );
//	m_sLoadLTHandVPSec.SetIcon( GetControl().QueryIOBit(IUNLOADOK)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTHandVPSec.SetIcon( GetControl().QueryIOBit(IUNLOADERLTHANDVPSEC)?m_hLedOFF:m_hLedON );
//	m_sUnloadRTHandVPSec.SetIcon( GetControl().QueryIOBit(IUNLOADERRTHANDVPSEC)?m_hLedOFF:m_hLedON );

//	m_sUnloadRTVaccum.SetIcon( GetControl().QueryIOBit(IUNLOADERRSUCKOK1)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTVaccum.SetIcon( GetControl().QueryIOBit(IUNLOADERLSUCKOK1)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTVaccumBack.SetIcon( GetControl().QueryIOBit(IUNLOADERLSUCKOK2)?m_hLedOFF:m_hLedON );
//	m_sUnloadRTVaccumBack.SetIcon( GetControl().QueryIOBit(IUNLOADERRSUCKOK2)?m_hLedOFF:m_hLedON );
//	m_sUnloadRTVaccum.SetIcon( GetControl().QueryIOBit(IUNLOADERRSUCKOK1)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTVaccum.SetIcon( GetControl().QueryIOBit(IUNLOADERLSUCKOK1)?m_hLedOFF:m_hLedON );
//	m_sUnloadLTVaccumBack.SetIcon( GetControl().QueryIOBit(IUNLOADERLSUCKOK2)?m_hLedOFF:m_hLedON );
//	m_sUnloadRTVaccumBack.SetIcon( GetControl().QueryIOBit(IUNLOADERRSUCKOK2)?m_hLedOFF:m_hLedON );
//	m_sUnloadPutPos.SetIcon  ( GetControl().QueryIOBit(IUNLOADERDOLLYARRIVE)?m_hLedOFF:m_hLedON );

//	m_sOverVolt.SetIcon  ( GetControl().QueryIOBit(IOVERVOLT)?m_hLedOFF:m_hLedON );
//	m_sUnderVolt.SetIcon ( GetControl().QueryIOBit(IUNDERVOLT)?m_hLedOFF:m_hLedON );
//	m_sWaterPress.SetIcon( GetControl().QueryIOBit(IWATERPRESS )?m_hLedOFF:m_hLedON );
//	m_sWaterTemperture.SetIcon ( GetControl().QueryIOBit(IWATERTEMPERTURE)?m_hLedOFF:m_hLedON );
//	m_sLoaderPitchN.SetIcon ( GetControl().QueryIOBit(ILOADERPITCHN)?m_hLedOFF:m_hLedON );
//	m_sLoaderPitchP.SetIcon ( GetControl().QueryIOBit(ILOADERPITCHP)?m_hLedOFF:m_hLedON );
//	m_sLoaderPich.SetIcon ( GetControl().QueryIOBit(ILOADERDOLLYISLOCK)?m_hLedOFF:m_hLedON );
//	m_sUnLoaderPich.SetIcon ( GetControl().QueryIOBit(IUNLOADERDOLLYISLOCK)?m_hLedOFF:m_hLedON );

//	m_sCCDLightError1.SetIcon( GetControl().QueryIOBit(ICCDLIGHTSOURCE_ERROR1)?m_hLedOFF:m_hLedON );
//	m_sCCDLightError2.SetIcon( GetControl().QueryIOBit(ICCDLIGHTSOURCE_ERROR2)?m_hLedOFF:m_hLedON );
//	m_sLoaderPushUpto.SetIcon( GetControl().QueryIOBit(ILOADERDOLLYARRIVE )?m_hLedOFF:m_hLedON );
//	m_sUnloaderFull.SetIcon  ( GetControl().QueryIOBit(IUNLOADERFULL)?m_hLedOFF:m_hLedON );
//	m_sFtGateStatus.SetIcon  ( GetControl().QueryIOBit(IFRONTGATESTATUS)?m_hLedOFF:m_hLedON );
//	m_s.SetIcon  ( GetControl().QueryIOBit(IWATERPRESS1)?m_hLedOFF:m_hLedON );

	UpdateData(FALSE);

#endif
	
	return 0;
}

int CSignalInputView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_hLedOFF = AfxGetApp()->LoadIcon(IDI_LEDOFF);	
	m_hLedON =  AfxGetApp()->LoadIcon(IDI_LEDON);	

	return 0;
}

void CSignalInputView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("SignalInput","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC7",szRead,40);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC9",szRead,40);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC10",szRead,40);
	SetDlgItemText(IDC_STATIC10,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC11",szRead,40);
	SetDlgItemText(IDC_STATIC11,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC12",szRead,40);
	SetDlgItemText(IDC_STATIC12,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC13",szRead,40);
	SetDlgItemText(IDC_STATIC13,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC14",szRead,40);
	SetDlgItemText(IDC_STATIC14,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC15",szRead,40);
	SetDlgItemText(IDC_STATIC15,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC16",szRead,40);
	SetDlgItemText(IDC_STATIC16,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC17",szRead,40);
	SetDlgItemText(IDC_STATIC17,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC18",szRead,40);
	SetDlgItemText(IDC_STATIC18,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC19",szRead,40);
	SetDlgItemText(IDC_STATIC19,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC20",szRead,40);
	SetDlgItemText(IDC_STATIC20,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC21",szRead,40);
	SetDlgItemText(IDC_STATIC21,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC22",szRead,40);
	SetDlgItemText(IDC_STATIC22,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC23",szRead,40);
	SetDlgItemText(IDC_STATIC23,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC24",szRead,40);
	SetDlgItemText(IDC_STATIC24,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC25",szRead,40);
	SetDlgItemText(IDC_STATIC25,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC26",szRead,40);
	SetDlgItemText(IDC_STATIC26,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC27",szRead,40);
	SetDlgItemText(IDC_STATIC27,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC28",szRead,40);
	SetDlgItemText(IDC_STATIC28,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC29",szRead,40);
	SetDlgItemText(IDC_STATIC29,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC30",szRead,40);
	SetDlgItemText(IDC_STATIC30,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC31",szRead,40);
	SetDlgItemText(IDC_STATIC31,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC32",szRead,40);
	SetDlgItemText(IDC_STATIC32,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC33",szRead,40);
	SetDlgItemText(IDC_STATIC33,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC34",szRead,40);
	SetDlgItemText(IDC_STATIC34,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC35",szRead,40);
	SetDlgItemText(IDC_STATIC35,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC36",szRead,40);
	SetDlgItemText(IDC_STATIC36,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC37",szRead,40);
	SetDlgItemText(IDC_STATIC37,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC38",szRead,40);
	SetDlgItemText(IDC_STATIC38,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC39",szRead,40);
	SetDlgItemText(IDC_STATIC39,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC40",szRead,40);
	SetDlgItemText(IDC_STATIC40,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC41",szRead,40);
	SetDlgItemText(IDC_STATIC41,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC42",szRead,40);
	SetDlgItemText(IDC_STATIC42,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC43",szRead,40);
	SetDlgItemText(IDC_STATIC43,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC44",szRead,40);
	SetDlgItemText(IDC_STATIC44,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC45",szRead,40);
	SetDlgItemText(IDC_STATIC45,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC46",szRead,40);
	SetDlgItemText(IDC_STATIC46,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC47",szRead,40);
	SetDlgItemText(IDC_STATIC47,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC48",szRead,40);
	SetDlgItemText(IDC_STATIC48,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC49",szRead,40);
	SetDlgItemText(IDC_STATIC49,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC50",szRead,40);
	SetDlgItemText(IDC_STATIC50,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC51",szRead,40);
	SetDlgItemText(IDC_STATIC51,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC52",szRead,40);
	SetDlgItemText(IDC_STATIC52,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC53",szRead,40);
	SetDlgItemText(IDC_STATIC53,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC54",szRead,40);
	SetDlgItemText(IDC_STATIC54,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC55",szRead,40);
	SetDlgItemText(IDC_STATIC55,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC56",szRead,40);
	SetDlgItemText(IDC_STATIC56,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC57",szRead,40);
	SetDlgItemText(IDC_STATIC57,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC58",szRead,40);
	SetDlgItemText(IDC_STATIC58,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC59",szRead,40);
	SetDlgItemText(IDC_STATIC59,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC60",szRead,40);
	SetDlgItemText(IDC_STATIC60,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC61",szRead,40);
	SetDlgItemText(IDC_STATIC61,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC62",szRead,40);
	SetDlgItemText(IDC_STATIC62,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC63",szRead,40);
	SetDlgItemText(IDC_STATIC63,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC64",szRead,40);
	SetDlgItemText(IDC_STATIC64,szRead);
	GetLang().GetUIText("SignalInput","IDC_STATIC65",szRead,40);
	SetDlgItemText(IDC_STATIC65,szRead);
}

void CSignalInputView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	char ez[256]={""};//ly 20110405
//IO   的初始化
	m_ioInput.SetExtendedStyle(LVS_EX_GRIDLINES);
	strncpy(ez,GetLang().GetWarningText(10170),256);
	m_ioInput.AddColumn(ez, 0, 150);//"输入端口名称"
	strncpy(ez,GetLang().GetWarningText(10171),256);
	m_ioInput.AddColumn(ez, 1,20);//"状态"

	m_ioInput.AddItem(0, 0, INPUT0);m_ioInput.AddItem(0, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(1, 0, INPUT1);m_ioInput.AddItem(1, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(2, 0, INPUT2);m_ioInput.AddItem(2, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(3, 0, INPUT3);m_ioInput.AddItem(3, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(4, 0, INPUT4);m_ioInput.AddItem(4, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(5, 0, INPUT5);m_ioInput.AddItem(5, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(6, 0, INPUT6);m_ioInput.AddItem(6, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(7, 0, INPUT7);m_ioInput.AddItem(7, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(8, 0, INPUT8);m_ioInput.AddItem(8, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(9, 0, INPUT9);m_ioInput.AddItem(9, 1, "0", CListItemCheckBox::GenerateProperty());
	
	m_ioInput.AddItem(10, 0, INPUT10,CListItemText::GenerateProperty(TRUE,234));m_ioInput.AddItem(10, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(11, 0, INPUT11);m_ioInput.AddItem(11, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(12, 0, INPUT12);m_ioInput.AddItem(12, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(13, 0, INPUT13);m_ioInput.AddItem(13, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(14, 0, INPUT14);m_ioInput.AddItem(14, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(15, 0, INPUT15);m_ioInput.AddItem(15, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(16, 0, INPUT16);m_ioInput.AddItem(16, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(17, 0, INPUT17);m_ioInput.AddItem(17, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(18, 0, INPUT18);m_ioInput.AddItem(18, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(19, 0, INPUT19);m_ioInput.AddItem(19, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(20, 0, INPUT20);m_ioInput.AddItem(20, 1, "0", CListItemCheckBox::GenerateProperty());	
	m_ioInput.AddItem(21, 0, INPUT21);m_ioInput.AddItem(21, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(22, 0, INPUT22);m_ioInput.AddItem(22, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(23, 0, INPUT23);m_ioInput.AddItem(23, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(24, 0, INPUT24);m_ioInput.AddItem(24, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(25, 0, INPUT25);m_ioInput.AddItem(25, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(26, 0, INPUT26);m_ioInput.AddItem(26, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(27, 0, INPUT27);m_ioInput.AddItem(27, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(24, 0, INPUT28);m_ioInput.AddItem(24, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(29, 0, INPUT29);m_ioInput.AddItem(29, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(25, 0, INPUT30);m_ioInput.AddItem(25, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(31, 0, INPUT31);m_ioInput.AddItem(31, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(26, 0, INPUT32);m_ioInput.AddItem(26, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(27, 0, INPUT33);m_ioInput.AddItem(27, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(28, 0, INPUT34);m_ioInput.AddItem(28, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(29, 0, INPUT35);m_ioInput.AddItem(29, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(30, 0, INPUT36);m_ioInput.AddItem(30, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(31, 0, INPUT37);m_ioInput.AddItem(31, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(32, 0, INPUT38);m_ioInput.AddItem(32, 1, "0", CListItemCheckBox::GenerateProperty());
//	m_ioInput.AddItem(39, 0, INPUT39);m_ioInput.AddItem(39, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(33, 0, INPUT40);m_ioInput.AddItem(33, 1, "0", CListItemCheckBox::GenerateProperty());	
	m_ioInput.AddItem(34, 0, INPUT41);m_ioInput.AddItem(34, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(35, 0, INPUT42);m_ioInput.AddItem(35, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(36, 0, INPUT43);m_ioInput.AddItem(36, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(37, 0, INPUT44);m_ioInput.AddItem(37, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(38, 0, INPUT45);m_ioInput.AddItem(38, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(39, 0, INPUT46);m_ioInput.AddItem(39, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioInput.AddItem(40, 0, INPUT47);m_ioInput.AddItem(40, 1, "0", CListItemCheckBox::GenerateProperty());

	///输出信号
	m_ioOutput.SetExtendedStyle(LVS_EX_GRIDLINES);
	strncpy(ez,GetLang().GetWarningText(10170),256);
	m_ioOutput.AddColumn(ez, 0, 150);//"输出端口名称"
	strncpy(ez,GetLang().GetWarningText(10171),256);
	m_ioOutput.AddColumn(ez, 1,20);//"状态"
	m_ioOutput.AddItem(0, 0, OUTPUT0);m_ioOutput.AddItem(0, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(1, 0, OUTPUT1);m_ioOutput.AddItem(1, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(2, 0, OUTPUT2);m_ioOutput.AddItem(2, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(3, 0, OUTPUT3);m_ioOutput.AddItem(3, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(4, 0, OUTPUT4);m_ioOutput.AddItem(4, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(5, 0, OUTPUT5);m_ioOutput.AddItem(5, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(6, 0, OUTPUT6);m_ioOutput.AddItem(6, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(7, 0, OUTPUT7);m_ioOutput.AddItem(7, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(8, 0, OUTPUT8);m_ioOutput.AddItem(8, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(9, 0, OUTPUT9);m_ioOutput.AddItem(9, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(10, 0, OUTPUT10);m_ioOutput.AddItem(10, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(11, 0, OUTPUT11);m_ioOutput.AddItem(11, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(12, 0, OUTPUT12);m_ioOutput.AddItem(12, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(13, 0, OUTPUT13);m_ioOutput.AddItem(13, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(14, 0, OUTPUT14);m_ioOutput.AddItem(14, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(15, 0, OUTPUT15);m_ioOutput.AddItem(15, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(16, 0, OUTPUT16);m_ioOutput.AddItem(16, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(17, 0, OUTPUT17);m_ioOutput.AddItem(17, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(18, 0, OUTPUT18);m_ioOutput.AddItem(18, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(19, 0, OUTPUT19);m_ioOutput.AddItem(19, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(20, 0, OUTPUT20);m_ioOutput.AddItem(20, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(21, 0, OUTPUT21);m_ioOutput.AddItem(21, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(22, 0, OUTPUT24);m_ioOutput.AddItem(22, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(23, 0, OUTPUT25);m_ioOutput.AddItem(23, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(24, 0, OUTPUT34);m_ioOutput.AddItem(24, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(25, 0, OUTPUT35);m_ioOutput.AddItem(25, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(26, 0, OUTPUT36);m_ioOutput.AddItem(26, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(27, 0, OUTPUT37);m_ioOutput.AddItem(27, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(28, 0, OUTPUT38);m_ioOutput.AddItem(28, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(29, 0, OUTPUT39);m_ioOutput.AddItem(29, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(30, 0, OUTPUT40);m_ioOutput.AddItem(30, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(31, 0, OUTPUT41);m_ioOutput.AddItem(31, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(32, 0, OUTPUT42);m_ioOutput.AddItem(32, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(33, 0, OUTPUT50);m_ioOutput.AddItem(33, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(34, 0, OUTPUT51);m_ioOutput.AddItem(34, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(35, 0, OUTPUT52);m_ioOutput.AddItem(35, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(36, 0, OUTPUT53);m_ioOutput.AddItem(36, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(37, 0, OUTPUT54);m_ioOutput.AddItem(37, 1, "0", CListItemCheckBox::GenerateProperty());
/*	m_ioOutput.AddItem(38, 0, OUTPUT0);m_ioOutput.AddItem(38, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(39, 0, OUTPUT0);m_ioOutput.AddItem(39, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(40, 0, OUTPUT0);m_ioOutput.AddItem(40, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(41, 0, OUTPUT0);m_ioOutput.AddItem(41, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(42, 0, OUTPUT0);m_ioOutput.AddItem(42, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(43, 0, OUTPUT0);m_ioOutput.AddItem(43, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(44, 0, OUTPUT0);m_ioOutput.AddItem(44, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(45, 0, OUTPUT0);m_ioOutput.AddItem(45, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(46, 0, OUTPUT0);m_ioOutput.AddItem(46, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(47, 0, OUTPUT0);m_ioOutput.AddItem(47, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(47, 0, OUTPUT0);m_ioOutput.AddItem(48, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(49, 0, OUTPUT0);m_ioOutput.AddItem(49, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(50, 0, OUTPUT0);m_ioOutput.AddItem(50, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(51, 0, OUTPUT0);m_ioOutput.AddItem(51, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(52, 0, OUTPUT0);m_ioOutput.AddItem(52, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(53, 0, OUTPUT0);m_ioOutput.AddItem(53, 1, "0", CListItemCheckBox::GenerateProperty());
	m_ioOutput.AddItem(54, 0, OUTPUT0);m_ioOutput.AddItem(54, 1, "0", CListItemCheckBox::GenerateProperty());
*/
}

void CSignalInputView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if((nIDCtl == IDC_LIST_IOINPUT)|(nIDCtl == IDC_LIST_IOOUTPUT))//IDC_MY_LIST为List的ID
{
lpMeasureItemStruct->itemHeight =20;
}	
	TVisualFormView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSignalInputView::OnFtgatestatus2() 
{
	// TODO: Add your control notification handler code here
	
}

void CSignalInputView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(!bActivate)
		isActivateView=FALSE;
	else
		isActivateView=TRUE;

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
