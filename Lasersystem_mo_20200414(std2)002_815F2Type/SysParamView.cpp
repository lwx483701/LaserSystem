// SysParamView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "SysParamView.h"
#include "operatecontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSysParamView dialog

IMPLEMENT_DYNCREATE(CSysParamView, TVisualFormView)

CSysParamView::CSysParamView()
: TVisualFormView(CSysParamView::IDD)
{
	//{{AFX_DATA_INIT(CSysParamView)
	m_ulMotionCardSn1 = 0;
	m_ulMotionCardSn2 = 0;
	m_ulMotionCardSn3 = 0;
	m_ulJmpSpeed = 0;
	m_ulJmpDelay = 0;
	m_nGlvCCDOffsetHead = 0;
	m_lOffsetAxisX = 0;
	m_lOffsetAxisY = 0;
	m_lOffsetAxisZAbs = 0;
	m_lCCDFocusRT = 0;
	m_lCCDFocusLT = 0;
	m_lLaserFocusLT = 0;
	m_lLaserFocusRT = 0;
	m_lCCDDistanceY = 0;
	m_lCCDDistanceX = 0;
	m_ulSLBitPermm = 0;
	m_ulProcThreshold = 0;
	m_ulProcInnerThreshold = 0;
	m_ulAdjThreshold = 0;
	m_ulAdjTestTime = 120;
	m_ulLaserPowerTime = 120;
	m_lLongLaserPathFocusRT = 0;
	m_lLongPathLaserFocusLT = 0;
	m_strXDiff = _T("");
	m_strYDiff = _T("");
	m_iGlvThreshold = 0;
	m_fScaleThreshold = 0.0001;
	m_ulAutoThickError = 50;
	m_fLaserPowerSt = 0.0f;
	m_SysParamUsed  = false;
	m_ulJmpLenth = 0;
	m_ulJmpDelay0 = 0;
	m_ScaleType = -1;
	m_fLaserPowerMax = 0.0;
	m_iScaleThrd = 500;
	m_lNGThred = 0;
	m_fInnerScaleThrd = 0.001;
	m_IntDistanceCentre = 76;
	m_tDataTimeUpload.ParseDateTime(CString("20:00:00"));
	m_tDataTimeUploadNight.ParseDateTime(CString("8:00:00"));
	//}}AFX_DATA_INIT
}


void CSysParamView::DoDataExchange(CDataExchange* pDX)
{
	TVisualFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysParamView)
	DDX_Control(pDX, IDC_EDT_INNERSCALETHRESHOLD, m_edtInnerScaleThrd);
	DDX_Control(pDX, IDC_EDT_NGTHRESHOLD, m_edtNgThred);
	DDX_Control(pDX, IDC_EDT_SCALETHRESHOLD2, m_edtScaleThrd);
	DDX_Control(pDX, IDC_EDT_LASERPOWERMAX, m_edtLaserPowerMax);
	DDX_Control(pDX, IDC_EDT_Z_JUMPDELAY, m_edtJmpDelay0);
	DDX_Control(pDX, IDC_EDT_JUMPLENTH, m_edtJmpLenth);
	DDX_Control(pDX, IDC_EDT_LASERPOWERST, m_edtLaserPowerSt);
	DDX_Control(pDX, IDC_EDT_AUTOTHICKERROR, m_edtAutoThickError);
	DDX_Control(pDX, IDC_EDT_SCALETHRESHOLD, m_edtScaleThreshold);
	DDX_Control(pDX, IDC_EDT_GLVTHRESHOLD, m_edtGlvThreshold);
	DDX_Control(pDX, IDC_EDT_LASERPOWERTIME, m_edtLaserPowerTime);
	DDX_Control(pDX, IDC_EDT_ADJTESTTIME, m_edtAdjTestTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEUPLOAD, m_tDataTimeUpload);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEUPLOADNIGHT, m_tDataTimeUploadNight);
	DDX_Control(pDX, C_BT_LONGPATH_TESTLASERFOCUS, m_btnLongPathLaserTest);
	DDX_Control(pDX, IDC_EDT_LONGPATH_LASERFOCUSRT, m_edtLongPathLaserFocusRT);
	DDX_Control(pDX, IDC_EDT_LONHPATH_LASERFOCUSLT, m_edtLongPathLaserFocusLT);
	DDX_Control(pDX, IDC_BT_GLVCCDSYSOFFSET, m_glvCCDSysOffset);
	DDX_Control(pDX, IDC_BT_TESTCCDDISTANCE, m_testCCDDistance);
	DDX_Control(pDX, IDC_BT_TESTLASERFOCUS, m_testLaserFocus);
	DDX_Control(pDX, IDC_BT_TESTCCDFOCUS, m_testCCDFocus);
	DDX_Control(pDX, IDC_EDT_ADJTHRESHOLD, m_edtAdjThreshold);
	DDX_Control(pDX, IDC_EDT_PROCTHRESHOLD, m_edtProcThreshold);
	DDX_Control(pDX, IDC_EDT_PROCINNERTHRESHOLD, m_edtProcInnerThreshold);
	DDX_Control(pDX, IDC_BT_GLVCCDPSET, m_btnSet);
	DDX_Control(pDX, IDC_BT_GLVCCDPRESET, m_btnReset);
	DDX_Control(pDX, IDC_BT_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_EDT_BITPERMM, m_edtSLBitPermm);
	DDX_Control(pDX, IDC_EDT_CCDDISTANCEY, m_edtCCDDistanceY);
	DDX_Control(pDX, IDC_EDT_CCDDISTANCEX, m_edtCCDDistanceX);
	DDX_Control(pDX, IDC_EDT_OFFAXISZA, m_edtGlvCCDOffsetZAbs);
	DDX_Control(pDX, IDC_EDT_LASERFOCUSRT, m_edtLaserFocusRT);
	DDX_Control(pDX, IDC_EDT_LASERFOCUSLT, m_edtLaserFocusLT);
	DDX_Control(pDX, IDC_EDT_CCDFOCUSRT, m_edtCCDFocusRT);
	DDX_Control(pDX, IDC_EDT_CCDFOCUSLT, m_edtCCDFocusLT);
	DDX_Control(pDX, IDC_EDT_OFFAXISY, m_edtGlvCCDOffsetY);
	DDX_Control(pDX, IDC_EDT_OFFAXISX, m_edtGlvCCDOffsetX);
	DDX_Control(pDX, IDC_EDT_JUMPSPEED, m_edtJmpSpeed);
	DDX_Control(pDX, IDC_EDT_JUMPDELAY, m_edtJmpDelay);
	DDX_Control(pDX, IDC_EDT_MOTIONCARDSN3, m_edtMotionCardSn3);
	DDX_Control(pDX, IDC_EDT_MOTIONCARDSN2, m_edtMotionCardSn2);
	DDX_Control(pDX, IDC_EDT_MOTIONCARDSN1, m_edtMotionCardSn1);
	DDX_Text(pDX, IDC_EDT_MOTIONCARDSN1, m_ulMotionCardSn1);
	DDX_Text(pDX, IDC_EDT_MOTIONCARDSN2, m_ulMotionCardSn2);
	DDX_Text(pDX, IDC_EDT_MOTIONCARDSN3, m_ulMotionCardSn3);
	DDX_Text(pDX, IDC_EDT_JUMPSPEED, m_ulJmpSpeed);
	DDX_Text(pDX, IDC_EDT_JUMPDELAY, m_ulJmpDelay);
	DDX_Radio(pDX, IDC_RADGLVCCDOFFSET, m_nGlvCCDOffsetHead);
	DDX_Text(pDX, IDC_EDT_OFFAXISX, m_lOffsetAxisX);
	DDX_Text(pDX, IDC_EDT_OFFAXISY, m_lOffsetAxisY);
	DDX_Text(pDX, IDC_EDT_OFFAXISZA, m_lOffsetAxisZAbs);
	DDX_Text(pDX, IDC_EDT_CCDFOCUSRT, m_lCCDFocusRT);
	DDX_Text(pDX, IDC_EDT_CCDFOCUSLT, m_lCCDFocusLT);
	DDX_Text(pDX, IDC_EDT_LASERFOCUSLT, m_lLaserFocusLT);
	DDX_Text(pDX, IDC_EDT_LASERFOCUSRT, m_lLaserFocusRT);
	DDX_Text(pDX, IDC_EDT_CCDDISTANCEY, m_lCCDDistanceY);
	DDX_Text(pDX, IDC_EDT_CCDDISTANCEX, m_lCCDDistanceX);
	DDX_Text(pDX, IDC_EDT_BITPERMM, m_ulSLBitPermm);
	DDX_Text(pDX, IDC_EDT_PROCTHRESHOLD, m_ulProcThreshold);
	DDX_Text(pDX, IDC_EDT_PROCINNERTHRESHOLD, m_ulProcInnerThreshold);
	DDX_Text(pDX, IDC_EDT_ADJTHRESHOLD, m_ulAdjThreshold);
	DDX_Text(pDX, IDC_EDT_ADJTESTTIME, m_ulAdjTestTime);
	DDX_Text(pDX, IDC_EDT_LASERPOWERTIME, m_ulLaserPowerTime);
	DDX_Text(pDX, IDC_EDT_LONGPATH_LASERFOCUSRT, m_lLongLaserPathFocusRT);
	DDX_Text(pDX, IDC_EDT_LONHPATH_LASERFOCUSLT, m_lLongPathLaserFocusLT);
	DDX_Text(pDX, IDC_XDIFF, m_strXDiff);
	DDX_Text(pDX, IDC_YDIFF, m_strYDiff);
	DDX_Text(pDX, IDC_EDT_GLVTHRESHOLD, m_iGlvThreshold);
	DDX_Text(pDX, IDC_EDT_SCALETHRESHOLD, m_fScaleThreshold);
	DDX_Text(pDX, IDC_EDT_AUTOTHICKERROR, m_ulAutoThickError);
	DDX_Text(pDX, IDC_EDT_LASERPOWERST, m_fLaserPowerSt);
	DDX_Text(pDX, IDC_EDT_JUMPLENTH, m_ulJmpLenth);
	DDX_Text(pDX, IDC_EDT_Z_JUMPDELAY, m_ulJmpDelay0);
	DDX_Radio(pDX, IDC_RADIO_SCALETHRESHOLD, m_ScaleType);
	DDX_Text(pDX, IDC_EDT_LASERPOWERMAX, m_fLaserPowerMax);
	DDX_Text(pDX, IDC_EDT_SCALETHRESHOLD2, m_iScaleThrd);
	DDX_Text(pDX, IDC_EDT_NGTHRESHOLD, m_lNGThred);
	DDX_Text(pDX, IDC_EDT_INNERSCALETHRESHOLD, m_fInnerScaleThrd);
	DDX_Text(pDX, IDC_EDIT_DISTANCEVALUE, m_IntDistanceCentre);
	DDV_MinMaxInt(pDX, m_IntDistanceCentre, -1, 10000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSysParamView, TVisualFormView)
//{{AFX_MSG_MAP(CSysParamView)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_RADGLVCCDOFFSET, OnRadGlvCCDOffset)
ON_BN_CLICKED(IDC_BT_GLVCCDPRESET, OnGlvCcdPReset)
ON_BN_CLICKED(IDC_BT_GLVCCDPSET, OnGlvCcdPSet)
ON_BN_CLICKED(IDC_BT_TESTCCDFOCUS, OnTestCCDFocus)
ON_BN_CLICKED(IDC_BT_TESTLASERFOCUS, OnTestLaserFocus)
ON_BN_CLICKED(IDC_BT_TESTCCDDISTANCE, OnTestCCDDistance)
ON_BN_CLICKED(IDC_BT_SAVE, OnSave)
ON_BN_CLICKED(C_BT_LONGPATH_TESTLASERFOCUS, OnBtLongpathTestlaserfocus)
ON_BN_CLICKED(IDC_RADIO_SCALETHRESHOLD, OnRadioScalethreshold)
ON_BN_CLICKED(IDC_RADIO_SCALETHRESHOLD2, OnRadioScalethreshold2)
ON_BN_CLICKED(IDC_RADGLVCCDOFFSETR, OnRadGlvCCDOffset)
ON_EN_KILLFOCUS(IDC_EDT_INNERSCALETHRESHOLD, OnKillfocusEdtInnerScaleThred)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysParamView message handlers

int CSysParamView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ScaleType = GetDoc().GetScaleType();//ly add 20120919
	
	
	m_edtMotionCardSn3.SetParseType( SES_NUMBERS ); 
	m_edtMotionCardSn2.SetParseType( SES_NUMBERS );
	m_edtMotionCardSn1.SetParseType( SES_NUMBERS );
	
	m_ulMotionCardSn3 = GetDoc().GetMotionCardSn(2);
	m_ulMotionCardSn2 = GetDoc().GetMotionCardSn(1);
	m_ulMotionCardSn1 = GetDoc().GetMotionCardSn(0);
	
	
	
	//m_glvCCDSysOffset.SubclassDlgItem(IDC_BT_GLVCCDSYSOFFSET,this);
	m_glvCCDSysOffset.SetIcon(IDI_TEST,IDI_TEST);
	//	m_testCCDDistance.SubclassDlgItem(IDC_BT_TESTCCDDISTANCE,this);
	m_testCCDDistance.SetIcon(IDI_TEST,IDI_TEST);
	//	m_testCCDFocus.SubclassDlgItem(IDC_BT_TESTCCDFOCUS,this);
	m_testCCDFocus.SetIcon(IDI_TEST,IDI_TEST);
	//	m_testLaserFocus.SubclassDlgItem(IDC_BT_TESTLASERFOCUS,this);
	m_testLaserFocus.SetIcon(IDI_TEST,IDI_TEST);
	
	m_btnLongPathLaserTest.SetIcon(IDI_TEST,IDI_TEST);
	
	//	m_btnSet.SubclassDlgItem(IDC_BT_GLVCCDPSET,this);
	m_btnSet.SetIcon(IDI_SET,IDI_SET);	
	//	m_btnSave.SubclassDlgItem(IDC_BT_SAVE,this);
	m_btnSave.SetIcon(IDI_SAVEP,IDI_SAVEP);	
	//	m_btnReset.SubclassDlgItem(IDC_BT_GLVCCDPRESET,this);
	m_btnReset.SetIcon(IDI_RESET,IDI_RESET);
	
	m_ulJmpDelay = GetDoc().GetProcJumpDelay();
	m_ulJmpSpeed = GetDoc().GetProcJumpSpeed();
	m_ulJmpDelay0 = GetDoc().GetProcJumpDelay0();//ly add 20111123
	m_ulJmpLenth = GetDoc().GetProcJumpLenth();
	
	m_edtGlvCCDOffsetX.SetParseType( SES_NUMBERS|SES_SIGNED ); 
	m_edtGlvCCDOffsetX.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_edtGlvCCDOffsetZAbs.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_lOffsetAxisX = GetDoc().GetCCDToGlvSysOffset(0).x;
	m_lOffsetAxisY = GetDoc().GetCCDToGlvSysOffset(0).y;
	m_lOffsetAxisZAbs = GetDoc().GetCCDToGlvSysOffset(0).z;
	
	
	m_edtCCDFocusLT.SetParseType( SES_NUMBERS|SES_SIGNED ); 
	m_edtCCDFocusRT.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_lCCDFocusLT=GetDoc().GetCCDFocus(0);
	m_lCCDFocusRT=GetDoc().GetCCDFocus(1);
	m_edtLongPathLaserFocusLT.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_edtLongPathLaserFocusRT.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_edtLaserFocusLT.SetParseType( SES_NUMBERS|SES_SIGNED ); 
	m_edtLaserFocusRT.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_lLaserFocusLT = GetDoc().GetLaserProcFocus(0);
	m_lLaserFocusRT = GetDoc().GetLaserProcFocus(1);
	
	m_lLongPathLaserFocusLT = GetDoc().GetLongPathLaserProcFocus(0);
	m_lLongLaserPathFocusRT = GetDoc().GetLongPathLaserProcFocus(1);
	
	m_edtCCDDistanceX.SetParseType( SES_NUMBERS|SES_SIGNED ); 
	m_edtCCDDistanceY.SetParseType( SES_NUMBERS|SES_SIGNED );
	m_lCCDDistanceX = GetDoc().GetCCDDistance().x;
	m_lCCDDistanceY = GetDoc().GetCCDDistance().y;
	
    m_edtSLBitPermm.SetParseType(SES_NUMBERS);
	m_ulSLBitPermm  = GetDoc().GetSLBitPerMM();  
	
	
	m_edtAdjThreshold.SetParseType(SES_NUMBERS);
	m_ulAdjThreshold = GetDoc().GetCCDAdjThreshold();
    m_edtProcThreshold.SetParseType(SES_NUMBERS);
	m_edtProcInnerThreshold.SetParseType(SES_NUMBERS);
	
	m_ulProcThreshold = GetDoc().GetCCDProcThreshold();
	m_ulProcInnerThreshold = GetDoc().GetCCDProcInnerThreshold();
	m_iGlvThreshold=GetDoc().GetGlvAdjustThreshold();

		m_IntDistanceCentre=GetDoc().GetDistanceCenterThreshold();

	m_fScaleThreshold=GetDoc().GetPCBScaleThreshold();
	m_iScaleThrd=GetDoc().GetPCBScaleThrd();//ly add 20120919
	m_fInnerScaleThrd=GetDoc().GetFZInnerScale();//ly add 20130821
	m_ulAutoThickError=GetDoc().GetAutoThickError();
	
	m_fLaserPowerSt=GetDoc().GetLaserPowerTestSt();
	m_fLaserPowerMax=GetDoc().GetLaserPowerTestMax();//ly add 20120924
	m_lNGThred = GetDoc().GetNGThred();//ly add 20121127
	
    m_ulLaserPowerTime = GetDoc().GetLaserTestTime();
	m_ulAdjTestTime = GetDoc().GetAdjTime();
	m_tDataTimeUpload.ParseDateTime(GetDoc().GetOperationRateTime());
	m_tDataTimeUploadNight.ParseDateTime(GetDoc().GetOperationRateTimeNight());

	return 0;
}

void CSysParamView::OnDestroy() 
{
	TVisualFormView::OnDestroy();
	
	UpdateData (TRUE);	
	//ccd
	GetDoc().SetCCDToGlvSysOffset(Coord3D(m_lOffsetAxisX,m_lOffsetAxisY,m_lOffsetAxisZAbs),m_nGlvCCDOffsetHead);
	
	GetDoc().SetMotionCardSn(0,m_ulMotionCardSn1);
	GetDoc().SetMotionCardSn(1,m_ulMotionCardSn2);
	GetDoc().SetMotionCardSn(2,m_ulMotionCardSn3);
	//
	GetDoc().SetLaserProcFocus(m_lLaserFocusLT,0);
	GetDoc().SetLaserProcFocus(m_lLaserFocusRT,1);
	GetDoc().SetCCDFocus(m_lCCDFocusLT,0);
	GetDoc().SetCCDFocus(m_lCCDFocusRT,1);
	
	//CCD相对距离
	GetDoc().SetCCDDistance(Coord(m_lCCDDistanceX,m_lCCDDistanceY));
	GetDoc().SetProcJumpDelay(m_ulJmpDelay);
	GetDoc().SetProcJumpSpeed(m_ulJmpSpeed);
	GetDoc().SetSLBitPerMM(m_ulSLBitPermm);  
	GetDoc().SetProcJumpDelay0(m_ulJmpDelay0);//ly add 20111123
	GetDoc().SetProcJumpLenth(m_ulJmpLenth);
	
	GetDoc().SetCCDAdjThreshold(m_ulAdjThreshold);
    GetDoc().SetCCDProcThreshold(m_ulProcThreshold);
    GetDoc().SetCCDProcInnerThreshold(m_ulProcInnerThreshold);
	
	GetDoc().SetGlvAdjustThreshold(m_iGlvThreshold);


	GetDoc().SetDistanceCenterThreshold(m_IntDistanceCentre);

	GetDoc().SetPCBScaleThreshold(m_fScaleThreshold);
	GetDoc().SetFZInnerScale(m_fInnerScaleThrd);//ly add 20130821
	GetDoc().SetPCBScaleThrd(m_iScaleThrd);//ly add 20120919
	GetDoc().SetAutoThickError(m_ulAutoThickError);
	GetDoc().SetLaserPowerTestSt(m_fLaserPowerSt);
	GetDoc().SetLaserPowerTestMax(m_fLaserPowerMax);//ly add 20120924
	GetDoc().SetNGThred(m_lNGThred);//ly add 20121127
}

void CSysParamView::OnGlvCcdPReset() 
{
	if(!m_SysParamUsed)
	{
		m_SysParamUsed = true;
		GetDoc().InitializeSysDoc();
		//  ccd
		m_lOffsetAxisX    = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).x;
		m_lOffsetAxisY    = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).y;
		m_lOffsetAxisZAbs = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).z;
		//  laser & ccd Proc focus
		m_lLongPathLaserFocusLT = GetDoc().GetLongPathLaserProcFocus(0);
		m_lLongLaserPathFocusRT = GetDoc().GetLongPathLaserProcFocus(1);
		m_lLaserFocusLT   = GetDoc().GetLaserProcFocus(0);
		m_lLaserFocusRT   = GetDoc().GetLaserProcFocus(1);
		m_lCCDFocusLT     = GetDoc().GetCCDFocus(0);
		m_lCCDFocusRT     = GetDoc().GetCCDFocus(1);
		
		//  cardSN
		m_ulMotionCardSn3 = GetDoc().GetMotionCardSn(2);
		m_ulMotionCardSn2 = GetDoc().GetMotionCardSn(1);
		m_ulMotionCardSn1 = GetDoc().GetMotionCardSn(0);
		// SL Test Param
		m_ulJmpDelay    = GetDoc().GetProcJumpDelay();
		m_ulJmpSpeed    = GetDoc().GetProcJumpSpeed();
		m_ulSLBitPermm  = GetDoc().GetSLBitPerMM();  
		m_ulJmpDelay0	= GetDoc().GetProcJumpDelay0();//ly add 20111123
		m_ulJmpLenth	= GetDoc().GetProcJumpLenth();
		//CCD相对距离
		m_lCCDDistanceX = GetDoc().GetCCDDistance().x;
		m_lCCDDistanceY = GetDoc().GetCCDDistance().y;
		
		m_ulAdjThreshold = GetDoc().GetCCDAdjThreshold();
		m_ulProcThreshold = GetDoc().GetCCDProcThreshold();
		m_ulProcInnerThreshold = GetDoc().GetCCDProcInnerThreshold();
		
		m_iGlvThreshold=GetDoc().GetGlvAdjustThreshold();
		m_IntDistanceCentre=GetDoc().GetDistanceCenterThreshold();
		m_fScaleThreshold=GetDoc().GetPCBScaleThreshold();
		m_fInnerScaleThrd=GetDoc().GetFZInnerScale();//ly add 20130821
		m_iScaleThrd=GetDoc().GetPCBScaleThrd();//ly add 20120919
		m_ulAutoThickError=GetDoc().GetAutoThickError();
		
		m_fLaserPowerSt=GetDoc().GetLaserPowerTestSt();
		m_fLaserPowerMax=GetDoc().GetLaserPowerTestMax();//ly add 20120924
		m_lNGThred = GetDoc().GetNGThred();//ly add 20121127
		
		//Warning Time
		
		this->m_ulAdjTestTime = GetDoc().GetAdjTime();
		this->m_ulLaserPowerTime= GetDoc().GetLaserTestTime();
		this->m_tDataTimeUpload.ParseDateTime(GetDoc().GetOperationRateTime());
		this->m_tDataTimeUploadNight.ParseDateTime(GetDoc().GetOperationRateTimeNight());
		UpdateData(FALSE);
#ifdef USELOG
		
		GetLog().Append_pro(10051,20051);//"系统参数恢复","系统参数测试"
#endif
		m_SysParamUsed = false;
	}
}

void CSysParamView::OnGlvCcdPSet() 
{
	if(!m_SysParamUsed)
	{
		m_SysParamUsed  = true;
		UpdateData();
		//ccd
		GetDoc().SetCCDToGlvSysOffset(Coord3D(m_lOffsetAxisX,m_lOffsetAxisY,m_lOffsetAxisZAbs),m_nGlvCCDOffsetHead);
		//laser
		GetDoc().SetLaserProcFocus(m_lLaserFocusLT,0);
		GetDoc().SetLaserProcFocus(m_lLaserFocusRT,1);
		
		GetDoc().SetLongPathLaserProcFocus(m_lLongPathLaserFocusLT,0);
		GetDoc().SetLongPathLaserProcFocus(m_lLongLaserPathFocusRT,1);
		
		GetDoc().SetCCDFocus(m_lCCDFocusLT,0);
		GetDoc().SetCCDFocus(m_lCCDFocusRT,1);
		//  cardSn
		GetDoc().SetMotionCardSn(0,m_ulMotionCardSn1);
		GetDoc().SetMotionCardSn(1,m_ulMotionCardSn2);
		GetDoc().SetMotionCardSn(2,m_ulMotionCardSn3);
		// SL Test Param
		GetDoc().SetProcJumpDelay(m_ulJmpDelay);
		GetDoc().SetProcJumpSpeed(m_ulJmpSpeed);
		GetDoc().SetSLBitPerMM(m_ulSLBitPermm);  
		GetDoc().SetProcJumpDelay0(m_ulJmpDelay0);//ly add 20111123
		GetDoc().SetProcJumpLenth(m_ulJmpLenth);
		//CCD相对距离
		GetDoc().SetCCDDistance(Coord(m_lCCDDistanceX,m_lCCDDistanceY));
		//CCD阀值
		GetDoc().SetCCDAdjThreshold(m_ulAdjThreshold);
		GetDoc().SetCCDProcThreshold(m_ulProcThreshold);
		GetDoc().SetCCDProcInnerThreshold(m_ulProcInnerThreshold);
		//
		GetDoc().SetGlvAdjustThreshold(m_iGlvThreshold);
		GetDoc().SetDistanceCenterThreshold(m_IntDistanceCentre);
		GetDoc().SetPCBScaleThreshold(m_fScaleThreshold);
		GetDoc().SetFZInnerScale(m_fInnerScaleThrd);//ly add 20130821
		GetDoc().SetPCBScaleThrd(m_iScaleThrd);//ly add 20120919
		GetDoc().SetAutoThickError(m_ulAutoThickError);
		GetDoc().SetLaserPowerTestSt(m_fLaserPowerSt);
		GetDoc().SetLaserPowerTestMax(m_fLaserPowerMax);//ly add 20120924
		GetDoc().SetNGThred(m_lNGThred);//ly add 20121127
		//激光能量测试时间段和振镜校正时间
		GetDoc().SetAdjTime(m_ulAdjTestTime);
		GetDoc().SetLaserTestTime(m_ulLaserPowerTime);
		GetDoc().SetOperationRateTime(m_tDataTimeUpload.Format("%H:%M:%S"));
		GetDoc().SetOperationRateTimeNight(m_tDataTimeUploadNight.Format("%H:%M:%S"));
		//cognex 模板极性
		GetDoc().SetMainFiduPolarity(((CComboBox*)GetDlgItem(IDC_COMBO_MAIN_POLARITY))->GetCurSel());
		GetDoc().SetInnerFiduPolarity(((CComboBox*)GetDlgItem(IDC_COMBO_INN_POLARITY))->GetCurSel());
		
#ifdef USELOG
		GetLog().Append_pro(10049,20051);//"系统参数设定","系统参数测试"
#endif
		m_SysParamUsed  =false;
	}
	
}
void CSysParamView::OnSave() 
{
//	if(!m_SysParamUsed)
//	{
//		m_SysParamUsed = true;

		OnGlvCcdPSet();
//		GetDoc().ReleaseSysDoc();
		GetDoc().SaveProcessParam();
		Delay(200);
		AfxMessageBox("参数已设定并保存！");

#ifdef USELOG
		GetLog().Append_pro(10050,20051);//"系统参数保存","系统参数测试"
#endif
//		m_SysParamUsed = false;
//	}
}

void CSysParamView::OnRadGlvCCDOffset() 
{
	
	int nHead = m_nGlvCCDOffsetHead;
	
	UpdateData();
	GetDoc().SetCCDToGlvSysOffset(Coord3D(m_lOffsetAxisX,m_lOffsetAxisY,m_lOffsetAxisZAbs),nHead);
	m_lOffsetAxisX    = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).x;
	m_lOffsetAxisY    = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).y;
	m_lOffsetAxisZAbs = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).z;
	UpdateData(FALSE);
}

void CSysParamView::OnTestCCDFocus() 
{
	char ez[256]={""};
	strncpy(ez,GetLang().GetWarningText(31032),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"测试左侧 CCD 选择 '是'\n测试右侧 CCD 选择 '否'\n取消操作 选择       '取消'\n"
	
	//   Coord crd = GetControl().GetTablePos();
	
	UpdateData();
	if(nSel == IDYES)
	{
		GetControl().MoveTo(AXISLEFTZ,m_lCCDFocusLT);
		GetControl().WaitAxisStop(AXISLEFTZ);
#ifdef USELOG
		CString TempStrZ;
		TempStrZ.Format( "CCDFocus= %d  ", m_lCCDFocusLT );
		GetLog().Append_pro(10093,20052,TempStrZ);//"左侧测试","CCD测试"
#endif
	}
	else if(nSel == IDNO)
	{
		GetControl().WaitAxisStop(AXISTAB);
		GetControl().MoveTo(AXISRIGHTZ,m_lCCDFocusRT);
		GetControl().WaitAxisStop(AXISRIGHTZ);
		
#ifdef USELOG
		CString TempStrZ;
		TempStrZ.Format( "CCDFocus= %d  ", m_lCCDFocusRT );
		GetLog().Append_pro(10094,20052,TempStrZ);//"右侧测试","CCD测试"
#endif
	}
	else
	{
		return ;
	}
	
}

void CSysParamView::OnTestLaserFocus() 
{
	char ez[256]={""};
	strncpy(ez,GetLang().GetWarningText(31033),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"测试左侧振镜  选择 '是'\n测试右侧振镜  选择 '否'\n取消操作 选择       '取消'\n"
	//加工点阵 	
	UpdateData();
	if(nSel == IDYES)  //左侧
	{
		GetControl().MoveTo(AXISLEFTZ,m_lLaserFocusLT);
		GetControl().WaitAxisStop(AXISLEFTZ);
		GetControl().DrillMatrix(5,0,0);      // 61*61
		
#ifdef USELOG
		
		CString TempStrZ;
		TempStrZ.Format( "LeftFocus= %d  ", m_lLaserFocusLT );
		GetLog().Append_pro(10093,20053,TempStrZ);//"左侧测试","激光加工焦距测试"
#endif
	}
	else if(nSel == IDNO) //右侧
	{
		GetControl().MoveTo(AXISRIGHTZ,m_lLaserFocusRT);
		GetControl().WaitAxisStop(AXISRIGHTZ);
		GetControl().DrillMatrix(5,0,1);      //61*61
#ifdef USELOG
		CString TempStrZ;
		TempStrZ.Format( "RightFocus= %d  ", m_lLaserFocusRT );
		GetLog().Append_pro(10094,20053,TempStrZ);//"右侧测试","激光加工焦距测试"
#endif
	}
	else
	{
		return ;
	}
}

void CSysParamView::OnTestCCDDistance() 
{
	return;
}

void CSysParamView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if(bActivate)
	{
		UpdateData();
		if(GetDoc().GetDrillInc())
		{
			GetDlgItem(IDC_STATIC_DISTANCEVALUE)->ShowWindow(TRUE);	
			GetDlgItem(IDC_EDIT_DISTANCEVALUE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_DISTANCEVALUEUM)->ShowWindow(TRUE);	
		}
		else
		{
			GetDlgItem(IDC_STATIC_DISTANCEVALUE)->ShowWindow(FALSE);	
			GetDlgItem(IDC_EDIT_DISTANCEVALUE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_DISTANCEVALUEUM)->ShowWindow(FALSE);
		}
		
		if (GetDoc().GetTechnicType()==0)
		{
			GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);	
			GetDlgItem(IDC_STATIC4)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC5)->ShowWindow(TRUE);	
			GetDlgItem(IDC_EDT_LASERFOCUSLT)->ShowWindow(TRUE);
			GetDlgItem(IDC_EDT_LASERFOCUSRT)->ShowWindow(TRUE);	
			GetDlgItem(IDC_STATICLSHORT)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATICRSHORT)->ShowWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);	
			GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC5)->ShowWindow(FALSE);	
			GetDlgItem(IDC_EDT_LASERFOCUSLT)->ShowWindow(FALSE);
			GetDlgItem(IDC_EDT_LASERFOCUSRT)->ShowWindow(FALSE);	
			GetDlgItem(IDC_STATICLSHORT)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATICRSHORT)->ShowWindow(FALSE);
		}
		
		m_lOffsetAxisX = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).x;
		m_lOffsetAxisY = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).y;
//	    m_lOffsetAxisZAbs = GetDoc().GetCCDToGlvSysOffset(m_nGlvCCDOffsetHead).z;
		
		m_lCCDDistanceX = GetDoc().GetCCDDistance().x;
		m_lCCDDistanceY = GetDoc().GetCCDDistance().y;
		
		Coord crd =  GetDoc().GetCCDDistance() - GetDoc().GetGlvDistance();
		m_strXDiff.Format("%d",crd.x);
		m_strYDiff.Format("%d",crd.y);
		
		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			m_edtCCDFocusLT.EnableWindow(FALSE);//CCD成像焦距
			m_edtCCDFocusRT.EnableWindow(FALSE);
			
			m_edtLaserFocusLT.EnableWindow(FALSE);//短光路激光加工焦距
			m_edtLaserFocusRT.EnableWindow(FALSE);
			
			m_edtLongPathLaserFocusLT.EnableWindow(FALSE);//长光路激光加工焦距
			m_edtLongPathLaserFocusRT.EnableWindow(FALSE);
			
			m_edtGlvCCDOffsetX.EnableWindow(FALSE);//振镜与CCD相对位置
			m_edtGlvCCDOffsetY.EnableWindow(FALSE);
			
			m_edtCCDDistanceX.EnableWindow(FALSE);//两CCD间相对位置
			m_edtCCDDistanceY.EnableWindow(FALSE);
			
			m_edtAdjThreshold. EnableWindow(FALSE);//相关阈值设定
			m_edtProcThreshold.EnableWindow(FALSE);
			m_edtProcInnerThreshold.EnableWindow(FALSE);
			m_edtGlvThreshold.EnableWindow(FALSE);

			if(GetDoc().GetScaleType()==0)
			{
				m_edtScaleThreshold.EnableWindow(TRUE);
				m_edtScaleThrd.EnableWindow(FALSE);
			}
			else if(GetDoc().GetScaleType()==1)
			{
				m_edtScaleThreshold.EnableWindow(FALSE);
				m_edtScaleThrd.EnableWindow(TRUE);
			}

//			m_edtScaleThreshold.EnableWindow(FALSE);				//20181106
//			m_edtScaleThrd.EnableWindow(FALSE);

			m_edtAutoThickError.EnableWindow(FALSE);
			m_edtLaserPowerSt.EnableWindow(FALSE);
			m_edtLaserPowerMax.EnableWindow(FALSE);
			m_edtNgThred.EnableWindow(FALSE);

			m_edtAdjTestTime.EnableWindow(FALSE);//相关周期设定
			m_edtLaserPowerTime.EnableWindow(FALSE);	
			
			m_edtJmpSpeed.EnableWindow(FALSE);//加工时振镜参数
			m_edtJmpDelay.EnableWindow(FALSE);
			m_edtSLBitPermm.EnableWindow(FALSE);
			m_edtJmpDelay0.EnableWindow(FALSE);
			m_edtJmpLenth.EnableWindow(FALSE);
		}
        else if(nLevel==SystemDoc::SUPEROR)  //高级
		{
//#ifdef CHONGDA
			if(GetDoc().GetCustomerSpecial()==1)
			{
				m_edtCCDFocusLT.EnableWindow(FALSE);//CCD成像焦距
				m_edtCCDFocusRT.EnableWindow(FALSE);
				
				m_edtLaserFocusRT.EnableWindow (FALSE);//短光路激光加工焦距
				m_edtLaserFocusLT.EnableWindow (FALSE);
				
				m_edtLongPathLaserFocusLT.EnableWindow(FALSE);//长光路激光加工焦距
				m_edtLongPathLaserFocusRT.EnableWindow(FALSE);
				
				m_edtGlvCCDOffsetX.EnableWindow(FALSE);//振镜与CCD相对位置
				m_edtGlvCCDOffsetY.EnableWindow(FALSE);
				
				m_edtCCDDistanceX.EnableWindow(FALSE);//两CCD间相对位置
				m_edtCCDDistanceY.EnableWindow(FALSE);
				
				m_edtAdjThreshold. EnableWindow(FALSE);//相关阈值设定
				m_edtProcThreshold.EnableWindow(FALSE);
				m_edtProcInnerThreshold.EnableWindow(FALSE);
				m_edtGlvThreshold.EnableWindow(FALSE);//ly add 20111028
				
				m_edtScaleThreshold.EnableWindow(FALSE);//ly add 20111028
				m_edtScaleThrd.EnableWindow(FALSE);//ly add 20120919
				
				m_edtAutoThickError.EnableWindow(FALSE);//ly add 20111028
				m_edtLaserPowerSt.EnableWindow(FALSE);//ly add 20111028
				m_edtLaserPowerMax.EnableWindow(FALSE);//ly add 20120924
				m_edtNgThred.EnableWindow(FALSE);//ly add 20121127
				
				m_edtAdjTestTime.EnableWindow(FALSE);//相关周期设定
				m_edtLaserPowerTime.EnableWindow(FALSE);//ly add 20111028
			}
//#else
			else
			{
				if(GetDoc().GetShenLan3Fid()!=0)								//20180515 按照厂家要求将高级与初级一致
				{
					m_edtCCDFocusLT.EnableWindow(FALSE);//CCD成像焦距
					m_edtCCDFocusRT.EnableWindow(FALSE);
					
					m_edtLaserFocusLT.EnableWindow(FALSE);//短光路激光加工焦距
					m_edtLaserFocusRT.EnableWindow(FALSE);
					
					m_edtLongPathLaserFocusLT.EnableWindow(FALSE);//长光路激光加工焦距
					m_edtLongPathLaserFocusRT.EnableWindow(FALSE);
					
					m_edtGlvCCDOffsetX.EnableWindow(FALSE);//振镜与CCD相对位置
					m_edtGlvCCDOffsetY.EnableWindow(FALSE);
					
					m_edtCCDDistanceX.EnableWindow(FALSE);//两CCD间相对位置
					m_edtCCDDistanceY.EnableWindow(FALSE);
					
					m_edtAdjThreshold. EnableWindow(FALSE);//相关阈值设定
					m_edtProcThreshold.EnableWindow(FALSE);
					m_edtProcInnerThreshold.EnableWindow(FALSE);
					m_edtGlvThreshold.EnableWindow(FALSE);
					
					if(GetDoc().GetScaleType()==0)
					{
						m_edtScaleThreshold.EnableWindow(TRUE);//ly add 20111028
						m_edtScaleThrd.EnableWindow(FALSE);//ly add 20120919
					}
					else if(GetDoc().GetScaleType()==1)
					{
						m_edtScaleThreshold.EnableWindow(FALSE);//ly add 20120919
						m_edtScaleThrd.EnableWindow(TRUE);//ly add 20120919
					}

//					m_edtScaleThreshold.EnableWindow(FALSE);					//20181106
//					m_edtScaleThrd.EnableWindow(FALSE);
				
					m_edtAutoThickError.EnableWindow(FALSE);
					m_edtLaserPowerSt.EnableWindow(FALSE);
					m_edtLaserPowerMax.EnableWindow(FALSE);
					m_edtNgThred.EnableWindow(FALSE);
					
					m_edtAdjTestTime.EnableWindow(FALSE);//相关周期设定
					m_edtLaserPowerTime.EnableWindow(FALSE);
				}
				else
				{
					m_edtCCDFocusLT.  EnableWindow(TRUE);//CCD成像焦距
					m_edtCCDFocusRT.  EnableWindow(TRUE);
					
					if(LSPATH_CHECKING==0)//ly add 20110201 仅有长光路
					{
						m_edtLaserFocusRT.EnableWindow (FALSE);//短光路激光加工焦距
						m_edtLaserFocusLT.EnableWindow (FALSE);
					}
					else
					{
						m_edtLaserFocusLT.EnableWindow(TRUE);//短光路激光加工焦距
						m_edtLaserFocusRT.EnableWindow(TRUE);
					}
					
					m_edtLongPathLaserFocusLT.EnableWindow(TRUE);//长光路激光加工焦距
					m_edtLongPathLaserFocusRT.EnableWindow(TRUE);
					
					m_edtGlvCCDOffsetX.EnableWindow(TRUE);//振镜与CCD相对位置
					m_edtGlvCCDOffsetY.EnableWindow(TRUE);
					
					m_edtCCDDistanceX.EnableWindow(TRUE);//两CCD间相对位置
					m_edtCCDDistanceY.EnableWindow(TRUE);
					
					m_edtAdjThreshold. EnableWindow(TRUE);//相关阈值设定
					m_edtProcThreshold.EnableWindow(TRUE);
					m_edtProcInnerThreshold.EnableWindow(TRUE);
					m_edtGlvThreshold.EnableWindow(TRUE);//ly add 20111028
					
					if(GetDoc().GetScaleType()==0)
					{
						m_edtScaleThreshold.EnableWindow(TRUE);//ly add 20111028
						m_edtScaleThrd.EnableWindow(FALSE);//ly add 20120919
					}
					else if(GetDoc().GetScaleType()==1)
					{
						m_edtScaleThreshold.EnableWindow(FALSE);//ly add 20120919
						m_edtScaleThrd.EnableWindow(TRUE);//ly add 20120919
					}
					
					m_edtAutoThickError.EnableWindow(TRUE);//ly add 20111028
					m_edtLaserPowerSt.EnableWindow(TRUE);//ly add 20111028
					m_edtLaserPowerMax.EnableWindow(TRUE);//ly add 20120924
					m_edtNgThred.EnableWindow(TRUE);//ly add 20121127
					
					m_edtAdjTestTime.EnableWindow(TRUE);//相关周期设定
					m_edtLaserPowerTime.EnableWindow(TRUE);//ly add 20111028
				}
			}
//#endif
			m_edtJmpSpeed.EnableWindow(FALSE);//加工时振镜参数
			m_edtJmpDelay.EnableWindow(FALSE);
			m_edtSLBitPermm.EnableWindow(FALSE);
			m_edtJmpDelay0.EnableWindow(FALSE);//ly add 20111123
			m_edtJmpLenth.EnableWindow(FALSE);		
		}
		else if(nLevel==SystemDoc::ADMIN)//系统
		{
			m_edtCCDFocusLT.  EnableWindow(TRUE);//CCD成像焦距
			m_edtCCDFocusRT.  EnableWindow(TRUE);
			
			if(LSPATH_CHECKING==0)//ly add 20110201 仅有长光路
			{
				m_edtLaserFocusRT.EnableWindow (FALSE);//短光路激光加工焦距
				m_edtLaserFocusLT.EnableWindow (FALSE);
			}
			else
			{
				m_edtLaserFocusLT.EnableWindow(TRUE);//短光路激光加工焦距
				m_edtLaserFocusRT.EnableWindow(TRUE);
			}
			
			m_edtLongPathLaserFocusLT.EnableWindow(TRUE);//长光路激光加工焦距
			m_edtLongPathLaserFocusRT.EnableWindow(TRUE);
			
			m_edtGlvCCDOffsetX.EnableWindow(TRUE);//振镜与CCD相对位置
			m_edtGlvCCDOffsetY.EnableWindow(TRUE);
			
			m_edtCCDDistanceX.EnableWindow(TRUE);//两CCD间相对位置
			m_edtCCDDistanceY.EnableWindow(TRUE);
			
			m_edtAdjThreshold. EnableWindow(TRUE);//相关阈值设定
			m_edtProcThreshold.EnableWindow(TRUE);
			m_edtProcInnerThreshold.EnableWindow(TRUE);
			m_edtGlvThreshold.EnableWindow(TRUE);//ly add 20111028

			if(GetDoc().GetScaleType()==0)
			{
				m_edtScaleThreshold.EnableWindow(TRUE);//ly add 20111028
				m_edtScaleThrd.EnableWindow(FALSE);//ly add 20120919
			}
			else if(GetDoc().GetScaleType()==1)
			{
				m_edtScaleThreshold.EnableWindow(FALSE);//ly add 20120919
				m_edtScaleThrd.EnableWindow(TRUE);//ly add 20120919
			}

			m_edtAutoThickError.EnableWindow(TRUE);//ly add 20111028
			m_edtLaserPowerSt.EnableWindow(TRUE);//ly add 20111028
			m_edtLaserPowerMax.EnableWindow(TRUE);//ly add 20120924
			m_edtNgThred.EnableWindow(TRUE);//ly add 20121127

			m_edtAdjTestTime.EnableWindow(TRUE);//相关周期设定
			m_edtLaserPowerTime.EnableWindow(TRUE);//ly add 20111028
			
			m_edtJmpSpeed.EnableWindow(TRUE);//加工时振镜参数
			m_edtJmpDelay.EnableWindow(TRUE);
			m_edtSLBitPermm.EnableWindow(TRUE);
			m_edtJmpDelay0.EnableWindow(TRUE);//ly add 20111123
			m_edtJmpLenth.EnableWindow(TRUE);
		}
	}
	
	if(LSPATH_CHECKING==0)//ly add 20110201 仅有长光路
	{		
		m_edtLaserFocusRT.EnableWindow (FALSE);
		m_edtLaserFocusLT.EnableWindow (FALSE);
	}
	
	UpdateData(FALSE);
	if(GetDoc().GetScaleType()==0)//ly add 20120919
	{
		if (m_fScaleThreshold < 0.0001) //ignore 1.2e-10
		{
			CString str;
			str.Format("%0.10f",m_fScaleThreshold);
			str.TrimRight('0');
			m_edtScaleThreshold.SetWindowText(str);
		}
	}
	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CSysParamView::OnBtLongpathTestlaserfocus() 
{
	char ez[256]={""};
	strncpy(ez,GetLang().GetWarningText(31033),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"测试左侧振镜  选择 '是'\n测试右侧振镜  选择 '否'\n取消操作 选择       '取消'\n"
	//加工点阵 	
	UpdateData();
	if(nSel == IDYES)  //左侧
	{
		GetControl().MoveTo(AXISLEFTZ,m_lLongPathLaserFocusLT);
		GetControl().WaitAxisStop(AXISLEFTZ);
		GetControl().DrillMatrix(5,0,0);      // 61*61
		
#ifdef USELOG
		
		CString TempStrZ;
		TempStrZ.Format( "LeftFocus= %d  ", m_lLongPathLaserFocusLT );
		GetLog().Append_pro(10093,20053,TempStrZ);//"左侧测试","激光加工焦距测试"
#endif
	}
	else if(nSel == IDNO) //右侧
	{
		GetControl().MoveTo(AXISRIGHTZ,m_lLongLaserPathFocusRT);
		GetControl().WaitAxisStop(AXISRIGHTZ);
		GetControl().DrillMatrix(5,0,1);      //61*61
#ifdef USELOG
		CString TempStrZ;
		TempStrZ.Format( "RightFocus= %d  ", m_lLongLaserPathFocusRT );
		GetLog().Append_pro(10094,20053,TempStrZ);//"右侧测试","激光加工焦距测试"
#endif
	}
	else
	{
		return ;
	}	
}

void CSysParamView::SetUI()//ly add 20110318
{
	char szRead[30] = {""};
	GetLang().GetUIText("SysParam","IDC_STATIC33",szRead,30);
	SetDlgItemText(IDC_STATIC33,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC1",szRead,30);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC2",szRead,30);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC3",szRead,30);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC4",szRead,30);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC5",szRead,30);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC6",szRead,30);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC7",szRead,30);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC8",szRead,30);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC9",szRead,30);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("SysParam","IDC_RADGLVCCDOFFSET",szRead,30);
	SetDlgItemText(IDC_RADGLVCCDOFFSET,szRead);
	GetLang().GetUIText("SysParam","IDC_RADGLVCCDOFFSETR",szRead,30);
	SetDlgItemText(IDC_RADGLVCCDOFFSETR,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC10",szRead,30);
	SetDlgItemText(IDC_STATIC10,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC11",szRead,30);
	SetDlgItemText(IDC_STATIC11,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC12",szRead,30);
	SetDlgItemText(IDC_STATIC12,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC13",szRead,30);
	SetDlgItemText(IDC_STATIC13,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC14",szRead,30);
	SetDlgItemText(IDC_STATIC14,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC15",szRead,30);
	SetDlgItemText(IDC_STATIC15,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC16",szRead,30);
	SetDlgItemText(IDC_STATIC16,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC17",szRead,30);
	SetDlgItemText(IDC_STATIC17,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC18",szRead,30);
	SetDlgItemText(IDC_STATIC18,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC19",szRead,30);
	SetDlgItemText(IDC_STATIC19,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC20",szRead,30);
	SetDlgItemText(IDC_STATIC20,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC21",szRead,30);
	SetDlgItemText(IDC_STATIC21,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC22",szRead,30);
	SetDlgItemText(IDC_STATIC22,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC23",szRead,30);
	SetDlgItemText(IDC_STATIC23,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC24",szRead,30);
	SetDlgItemText(IDC_STATIC24,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC25",szRead,30);
	SetDlgItemText(IDC_STATIC25,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC26",szRead,30);
	SetDlgItemText(IDC_STATIC26,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC27",szRead,30);
	SetDlgItemText(IDC_STATIC27,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC28",szRead,30);
	SetDlgItemText(IDC_STATIC28,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC29",szRead,30);
	SetDlgItemText(IDC_STATIC29,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC30",szRead,30);
	SetDlgItemText(IDC_STATIC30,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC31",szRead,30);
	SetDlgItemText(IDC_STATIC31,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC32",szRead,30);
	SetDlgItemText(IDC_STATIC32,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC34",szRead,30);//ly add 20111122
	SetDlgItemText(IDC_STATIC34,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC35",szRead,30);//ly add 20111122
	SetDlgItemText(IDC_STATIC35,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC36",szRead,30);//ly add 20130821
	SetDlgItemText(IDC_STATIC36,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC_POLARITY",szRead,30);
	SetDlgItemText(IDC_STATIC_POLARITY,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC_MFPOL",szRead,30);
	SetDlgItemText(IDC_STATIC_MFPOL,szRead);
	GetLang().GetUIText("SysParam","IDC_STATIC_INFPOL",szRead,30);
	SetDlgItemText(IDC_STATIC_INFPOL,szRead);
	GetLang().GetUIText("SysParam","IDC_BT_GLVCCDPRESET",szRead,30);
	SetDlgItemText(IDC_BT_GLVCCDPRESET,szRead);
	GetLang().GetUIText("SysParam","IDC_BT_GLVCCDPSET",szRead,30);
	SetDlgItemText(IDC_BT_GLVCCDPSET,szRead);
	GetLang().GetUIText("SysParam","IDC_BT_SAVE",szRead,30);
	SetDlgItemText(IDC_BT_SAVE,szRead);
}

void CSysParamView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();
	
	if(!GetDoc().GetScaleUnit())//ly add 20130625
	{
		((CButton*)GetDlgItem(IDC_RADIO_SCALETHRESHOLD))->ShowWindow(SW_HIDE);
		((CButton*)GetDlgItem(IDC_RADIO_SCALETHRESHOLD2))->ShowWindow(SW_HIDE);
		((CEdit*)GetDlgItem(IDC_EDT_SCALETHRESHOLD2))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_SCALEBEF))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_SCALEAFT))->ShowWindow(SW_HIDE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_SCALETHRESHOLD))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_RADIO_SCALETHRESHOLD2))->ShowWindow(SW_SHOW);
		((CEdit*)GetDlgItem(IDC_EDT_SCALETHRESHOLD2))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_SCALEBEF))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_SCALEAFT))->ShowWindow(SW_SHOW);
	}
	if(!GetDoc().GetPowerMax())//ly add 20130625
	{
		((CEdit*)GetDlgItem(IDC_EDT_LASERPOWERMAX))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_PWMAXBEF))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_PWMAXAFT))->ShowWindow(SW_HIDE);
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDT_LASERPOWERMAX))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_PWMAXBEF))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_PWMAXAFT))->ShowWindow(SW_SHOW);
	}
	if(!GetDoc().GetFZInnerMark())//ly add 20130821
	{
		GetDlgItem(IDC_STATIC22)->SetWindowText("加工时涨缩阈值：");							//20200326

		((CEdit*)GetDlgItem(IDC_EDT_INNERSCALETHRESHOLD))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_INNERSCALE))->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC36))->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC22)->SetWindowText("外标靶涨缩阈值：");							//20200326

		((CEdit*)GetDlgItem(IDC_EDT_INNERSCALETHRESHOLD))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_INNERSCALE))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC36))->ShowWindow(SW_SHOW);
	}
	// TODO: Add your specialized code here and/or call the base class
	
#ifdef USERCOGNEX
	int iSelMain = 0;
	int iSelInn = 0;
	if(GetDoc().GetMainFiduPolarity()== cogShapeExtractPolarityDarkOnLight)
		iSelMain = 0;
	else
		iSelMain = 1;

	if(GetDoc().GetInnerFiduPolarity()== cogShapeExtractPolarityDarkOnLight)
		iSelInn = 0;
	else
		iSelInn = 1;

	char szRead[20]={""};
	strncpy(szRead ,GetLang().GetWarningText(10050),20);
	((CComboBox*)GetDlgItem(IDC_COMBO_MAIN_POLARITY))->InsertString(0,szRead);//"白中黑"
	strncpy(szRead ,GetLang().GetWarningText(10051),20);
	((CComboBox*)GetDlgItem(IDC_COMBO_MAIN_POLARITY))->InsertString(1,szRead);//"黑中白"
	((CComboBox*)GetDlgItem(IDC_COMBO_MAIN_POLARITY))->SetCurSel(iSelMain);
	
	strncpy(szRead ,GetLang().GetWarningText(10050),20);
	((CComboBox*)GetDlgItem(IDC_COMBO_INN_POLARITY))->InsertString(0,szRead);//"白中黑"
	strncpy(szRead ,GetLang().GetWarningText(10051),20);
	((CComboBox*)GetDlgItem(IDC_COMBO_INN_POLARITY))->InsertString(1,szRead);//"黑中白"
	((CComboBox*)GetDlgItem(IDC_COMBO_INN_POLARITY))->SetCurSel(iSelInn);
#else
	((CComboBox*)GetDlgItem(IDC_COMBO_MAIN_POLARITY))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_COMBO_INN_POLARITY))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_STATIC_MFPOL))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_STATIC_INFPOL))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_STATIC_POLARITY))->ShowWindow(SW_HIDE);
#endif	
	
}

void CSysParamView::OnRadioScalethreshold() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetScaleType(m_ScaleType);
	
	m_edtScaleThreshold.EnableWindow(TRUE);//ly add 20111028
	m_edtScaleThrd.EnableWindow(FALSE);//ly add 20120919
				
	//GetDlgItem(IDC_RADIO_SCALETHRESHOLD)->EnableWindow(TRUE);
	//GetDlgItem(IDC_RADIO_SCALETHRESHOLD2)->EnableWindow(TRUE);
	
	//	Invalidate();
	UpdateWindow();
}

void CSysParamView::OnRadioScalethreshold2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDoc().SetScaleType(m_ScaleType);
	
	m_edtScaleThreshold.EnableWindow(FALSE);//ly add 20120919
	m_edtScaleThrd.EnableWindow(TRUE);//ly add 20120919
				
	//GetDlgItem(IDC_RADIO_SCALETHRESHOLD)->EnableWindow(FALSE);
	//GetDlgItem(IDC_RADIO_SCALETHRESHOLD2)->EnableWindow(TRUE);	
	
	//Invalidate();
	UpdateWindow();
}

void CSysParamView::OnKillfocusEdtInnerScaleThred() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	char ez[256]={""};
	if((m_fInnerScaleThrd<0.0001)||(m_fInnerScaleThrd>0.002))
	{
		strncpy(ez,GetLang().GetWarningText(21108),256);
		AfxMessageBox(ez);//"内层涨缩阈值请输入0.0001-0.002之间的数值！"
	}
}
