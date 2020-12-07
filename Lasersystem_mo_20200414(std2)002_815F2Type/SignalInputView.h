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

//�������IO�ڱ���
//1842 -1
#define INPUT0   "Ԥ��բ��N"
#define INPUT1   "Ԥ��բ��P"
#define INPUT2   "��༤�����N"
#define INPUT3   "��༤�����P"
#define INPUT4   "�Ҳ༤�����N"
#define INPUT5   "�Ҳ༤�����P"
#define INPUT6   "���N"
#define INPUT7   "���P"
//1842-2
#define INPUT8   "�������������N"
#define INPUT9   "�������������P"
#define INPUT10  "�����Ҳ�������N"
#define INPUT11  "�����Ҳ�������P"
#define INPUT12  "ȡ��λ���ź�"
#define INPUT13  "�ϲ������ź�"
#define INPUT14  "�����������ź�"
#define INPUT15  "�����Ҳ�����ź�"
//1842-3
#define INPUT16  "�����������ź�"
#define INPUT17  "�����Ҳ�����ź�"
#define INPUT18  "�������������N"
#define INPUT19  "�������������P"
#define INPUT20  "�����Ҳ�������N"
#define INPUT21  "�����Ҳ�������P"
#define INPUT22  "����λ���ź�"
#define INPUT23  "���ϳ���λ�ź�"
//7200-1
//#define INPUT24  ""
//#define INPUT25  ""
//#define INPUT26  ""
//#define INPUT27  ""
#define INPUT28  "�ϵ�"
//#define INPUT29  ""   
#define INPUT30  "��ͣ�ź�"
//#define INPUT31  ""
#define INPUT32  "����·���"
#define INPUT33  "�����Ƴ���λ�ź�"
#define INPUT34  "��ƽ̨���"
#define INPUT35  "��ƽ̨���"

#define INPUT36  "���ϳ�����"
#define INPUT37  "���ϳ�����"
#define INPUT38  "����С�����ź�"

//#define INPUT39  ""

#define INPUT40  "��λXP"
#define INPUT41  "��λXN"

#define INPUT42  "��λYP"
#define INPUT43  "��λYN"
#define INPUT44  "����N"
#define INPUT45  "����P"
#define INPUT46  "�����������ź�"
#define INPUT47  "�����Ҳ�����ź�"
#define INPUT48  "�����������ź�"
#define INPUT49  "�����������ź�"
#define INPUT50  "���N"
#define INPUT51  "���P"
#define INPUT52  "ת����N"
#define INPUT53  "ת����P"
#define INPUT54  "ת����N"
#define INPUT55  "ת����P"



//1842-1
#define OUTPUT0  "�������屣����"
#define OUTPUT1  "����Ԥ�ȷ�"
#define OUTPUT2  "���������"
#define OUTPUT3  "�����ҿ���"
#define OUTPUT4	 "��ͷ������"
#define OUTPUT5  "���N"
#define OUTPUT6  "���P"
#define OUTPUT7  "���ʲ������"
//1842-2
#define OUTPUT8  "������1����"
#define OUTPUT9  "������1�½�"
#define OUTPUT10 "������2����"
#define OUTPUT11 "������2�½�"
#define OUTPUT12 "���ϻ�е�ִ����"
#define OUTPUT13 "���ϻ�е�ִ���"
#define OUTPUT14 "������1����л�"
#define OUTPUT15 "������2����л�"
//1842-3
#define OUTPUT16 "������1����л�"
#define OUTPUT17 "������2����л�"
#define OUTPUT18 "������1����"
#define OUTPUT19 "������1�½�"
#define OUTPUT20 "������2����"
#define OUTPUT21 "������2�½�"
//#define OUTPUT22 ""
//#define OUTPUT23 ""

//7200-1

#define OUTPUT24 "������������ѡ��"
#define OUTPUT25 "����ƿ�������"
//#define OUTPUT26~ OUTPUT33"��������"

#define OUTPUT34 "��ƽ̨�����"
#define OUTPUT35 "��ƽ̨�����"
#define OUTPUT36 "����С����"
#define OUTPUT37 "����С����"
#define OUTPUT38 "�����ͨ������"
#define OUTPUT39 "�����ͨ������"
#define OUTPUT40 "X����λ"
#define OUTPUT41 "Y����λ"
#define OUTPUT42 "����"
//#define OUTPUT43 ""
//#define OUTPUT44 ""
//#define OUTPUT45 ""
//#define OUTPUT46 ""
//#define OUTPUT47 ""
//#define OUTPUT48 ""
//#define OUTPUT49 ""
#define OUTPUT50 "��ͬ�Ὺ��"
#define OUTPUT51 "��ͬ�Ὺ��"
#define OUTPUT52 "����"
#define OUTPUT53  "�Ҳ��"
#define OUTPUT54 "��·ת��"
//#define OUTPUT55 "CCD ����ͨ·ѡ��"







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
	BOOL isActivateView;//���ڼ���ý����ʱ�򣬰Ѷ�ʱ��������һֱ��ѯ�����ڶ��࣬�������Ӵ˱���
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
