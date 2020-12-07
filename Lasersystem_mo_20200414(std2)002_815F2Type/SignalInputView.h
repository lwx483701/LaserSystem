#if !defined(AFX_SIGNALINPUTVIEW_H__7C41F9E6_437B_43DF_9578_BB55D2EC763D__INCLUDED_)
#define AFX_SIGNALINPUTVIEW_H__7C41F9E6_437B_43DF_9578_BB55D2EC763D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SignalInputView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSignalInputView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "VisualFx.h"
#include "Shared Classes/ListReport/ListReport.h"

//定义各个IO口别名
//1842 -1
#define INPUT0   "预热闸门N"
#define INPUT1   "预热闸门P"
#define INPUT2   "左侧激光快门N"
#define INPUT3   "左侧激光快门P"
#define INPUT4   "右侧激光快门N"
#define INPUT5   "右侧激光快门P"
#define INPUT6   "测厚N"
#define INPUT7   "测厚P"
//1842-2
#define INPUT8   "上料左侧手升降N"
#define INPUT9   "上料左侧手升降P"
#define INPUT10  "上料右侧手升降N"
#define INPUT11  "上料右侧手升降P"
#define INPUT12  "取料位置信号"
#define INPUT13  "料仓有料信号"
#define INPUT14  "上料左侧真空信号"
#define INPUT15  "上料右侧真空信号"
//1842-3
#define INPUT16  "下料左侧真空信号"
#define INPUT17  "下料右侧真空信号"
#define INPUT18  "下料左侧手升降N"
#define INPUT19  "下料左侧手升降P"
#define INPUT20  "下料右侧手升降N"
#define INPUT21  "下料右侧手升降P"
#define INPUT22  "放料位置信号"
#define INPUT23  "上料车到位信号"
//7200-1
//#define INPUT24  ""
//#define INPUT25  ""
//#define INPUT26  ""
//#define INPUT27  ""
#define INPUT28  "上电"
//#define INPUT29  ""   
#define INPUT30  "急停信号"
//#define INPUT31  ""
#define INPUT32  "总气路检查"
#define INPUT33  "上料推车到位信号"
#define INPUT34  "左平台真空"
#define INPUT35  "右平台真空"

#define INPUT36  "上料车锁定"
#define INPUT37  "下料车锁定"
#define INPUT38  "下料小车满信号"

//#define INPUT39  ""

#define INPUT40  "定位XP"
#define INPUT41  "定位XN"

#define INPUT42  "定位YP"
#define INPUT43  "定位YN"
#define INPUT44  "抖料N"
#define INPUT45  "抖料P"
#define INPUT46  "上料左侧真空信号"
#define INPUT47  "上料右侧真空信号"
#define INPUT48  "下料左侧真空信号"
#define INPUT49  "下料左侧真空信号"
#define INPUT50  "测厚N"
#define INPUT51  "测厚P"
#define INPUT52  "转换左N"
#define INPUT53  "转换左P"
#define INPUT54  "转换右N"
#define INPUT55  "转换右P"



//1842-1
#define OUTPUT0  "激光气体保护阀"
#define OUTPUT1  "激光预热阀"
#define OUTPUT2  "激光左快门"
#define OUTPUT3  "激光右快门"
#define OUTPUT4	 "镜头隔离气"
#define OUTPUT5  "测厚N"
#define OUTPUT6  "测厚P"
#define OUTPUT7  "功率测试清洁"
//1842-2
#define OUTPUT8  "上料手1上升"
#define OUTPUT9  "上料手1下降"
#define OUTPUT10 "上料手2上升"
#define OUTPUT11 "上料手2下降"
#define OUTPUT12 "上料机械手大真空"
#define OUTPUT13 "上料机械手吹气"
#define OUTPUT14 "上料手1真空切换"
#define OUTPUT15 "上料手2真空切换"
//1842-3
#define OUTPUT16 "下料手1真空切换"
#define OUTPUT17 "下料手2真空切换"
#define OUTPUT18 "下料手1上升"
#define OUTPUT19 "下料手1下降"
#define OUTPUT20 "下料手2上升"
#define OUTPUT21 "下料手2下降"
//#define OUTPUT22 ""
//#define OUTPUT23 ""

//7200-1

#define OUTPUT24 "背光灯内外控制选择"
#define OUTPUT25 "背光灯控制输入"
//#define OUTPUT26~ OUTPUT33"作调光用"

#define OUTPUT34 "左平台吸真空"
#define OUTPUT35 "右平台吸真空"
#define OUTPUT36 "上料小车锁"
#define OUTPUT37 "下料小车锁"
#define OUTPUT38 "背光灯通道开关"
#define OUTPUT39 "背光灯通道开关"
#define OUTPUT40 "X方向定位"
#define OUTPUT41 "Y方向定位"
#define OUTPUT42 "抖料"
//#define OUTPUT43 ""
//#define OUTPUT44 ""
//#define OUTPUT45 ""
//#define OUTPUT46 ""
//#define OUTPUT47 ""
//#define OUTPUT48 ""
//#define OUTPUT49 ""
#define OUTPUT50 "左同轴开关"
#define OUTPUT51 "右同轴开关"
#define OUTPUT52 "左测厚"
#define OUTPUT53  "右测厚"
#define OUTPUT54 "光路转换"
//#define OUTPUT55 "CCD 背光通路选择"







class CSignalInputView : public TVisualFormView
{
protected:
	CSignalInputView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSignalInputView)

// Form Data
public:
	//{{AFX_DATA(CSignalInputView)
	enum { IDD = IDD_SIGNALINPUTVIEW };
	CStatic	m_sThicknessHome2;
	CStatic	m_sThicknessHome1;
	CStatic	m_sTopHat2;
	CStatic	m_sTopHat1;
	CStatic	m_sRingLight2Error;
	CStatic	m_sRingLight1Error;
	CStatic	m_sTableClampP;
	CStatic	m_sTableClampN;
	CStatic	m_sLensWindow2Error;
	CStatic	m_sLensWindow1Error;
	CStatic	m_sGaussian2;
	CStatic	m_sGaussian1;
	CStatic	m_sDustPressure2;
	CStatic	m_sDustPressure1;
	CStatic	m_sDoorProtect;
	CStatic	m_sLaserError;
	CStatic	m_sUnloadOK;
	CStatic	m_sThicknessError2;
	CStatic	m_sThicknessError1;
	CStatic	m_sTableYError;
	CStatic	m_sTableXError;
	CStatic	m_sSWaterCoolFault;
	CStatic	m_sServoAlarmZR;
	CStatic	m_sServoAlarmZL;
	CStatic	m_sServoAlarmY;
	CStatic	m_sServoAlarmX;
	CStatic	m_sServoAlarmBETSUB;
	CStatic	m_sServoAlarmBETPRI;
	CStatic	m_sReadyToUnloadOK;
	CStatic	m_sReadyLoad;
	CStatic	m_sPutBoardOnTable;
	CStatic	m_sOverTimeAlarm;
	CStatic	m_sOnlyLeft;
	CStatic	m_sMotionStopReset;
	CStatic	m_sLoadOK;
	CStatic	m_sLaserGasFlux;
	CStatic	m_sHomeAllOK;
	CStatic	m_sDepotEmpty;
	CStatic	m_sAOMTemProtect;
	CStatic	m_sAlarm;
	CStatic	m_s1842_2Error;
	CStatic	m_s1842_1Error;
	CStatic	m_sDrillMatrixSwitch;
	CStatic	m_sLoadRTHandVPSec;
	CStatic	m_sLoadLTHandVPSec;
	CStatic	m_sUnloadLTHandVPSec;
	CStatic	m_sUnloadRTHandVPSec;
	CStatic	m_sThicknessNL;
	CStatic	m_sThicknessPR;
	CStatic	m_sThicknessPL;
	CStatic	m_sThickNessNR;
	CStatic	m_sUnloadRTVaccumBack;
	CStatic	m_sUnloadLTVaccumBack;
	CStatic	m_sTunePosXPBack;
	CStatic	m_sTunePosXNBack;
	CStatic	m_sLoadLTVaccumBack;
	CStatic	m_sLoadRTVaccumBack;
	CStatic	m_sUnLoaderPich;
	CStatic	m_sLoaderPich;
	CStatic	m_sUnloaderPushupTo;
	CStatic	m_sTunePosYP;
	CStatic	m_sLoadVibrateP;
	CStatic	m_sLoadVibrateN;
	CStatic	m_sTunePosYN;
	CStatic	m_sTunePosXP;
	CStatic	m_sTunePosXN;
	CListReport	m_ioOutput;
	CListReport	m_ioInput;
	CStatic	m_s;
	CStatic	m_sFtGateStatus;
	CStatic	m_sAirPressure;
	CStatic	m_sCCDLightError2;
	CStatic	m_sCCDLightError1;
	CStatic	m_sLoaderPushUpto;
	CStatic	m_sUnloaderFull;
	CStatic	m_sWaterTemperture;
	CStatic	m_sWaterPress;
	CStatic	m_sUnderVolt;
	CStatic	m_sOverVolt;
	CStatic	m_sLaserShutterLN;
	CStatic m_sLaserShutterLP;
	CStatic m_sLaserShutterRN;
	CStatic m_sLaserShutterRP;
	CStatic   m_sLaserWarmN;
	CStatic   m_sLaserWarmP;
	CStatic  m_sTabLTVacumm;
	CStatic  m_sTabRTVacumm;
	//}}AFX_DATA

// Attributes
public:
//	enum TTabPos { TP_TOP, TP_BOTTOM };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalInputView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetUI();//ly add 20110318
	virtual ~CSignalInputView();
#ifdef _DEBUG										
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
//	BOOL QueryInput();												//20160919
#endif
	BOOL QueryInput();

private:
	BOOL isActivateView;//由于激活该界面的时候，把定时器开启，一直查询，属于多余，所以增加此变量
	HICON m_hLedON;
	HICON m_hLedOFF;
	// Generated message map functions
	//{{AFX_MSG(CSignalInputView)
	afx_msg LONG OnCheckInputSignal(UINT  wParam, LONG lParam);
	afx_msg LONG OnUncheckInputSignal(UINT  wParam, LONG lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnFtgatestatus2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGNALINPUTVIEW_H__7C41F9E6_437B_43DF_9578_BB55D2EC763D__INCLUDED_)
