
// OperateControl.cpp: implementation of the CControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include <math.h>
#include <algorithm>
#include "calc.h"
#include "info.h"
#include "MainFrm.h"
#include "ToolParameter.h"
#include "WarningInfo.h"
#include "SysParameter.h"
#include "OperateControl.h"
#include "FileInfoSettingView.h"
#include "ImageParaSetView.h"
#include "MainRunView.h"
#include "TestFunctionView.h"

#include "HttpClient.h"
#include "json/json.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CFileInfoSettingView *pFileInfoSettingView;
extern CImageParaSetView *pImageParaSetView;
extern BOOL bInDelay;												//20190329
extern bool bInPowerTest;											//20190626

bool bPowerOn=false;
float fLaserPower=0.0;

void Delay(int milliseconds)
{
	bInDelay=true;													//20190329

	DWORD dwStart;
	dwStart = GetTickCount();
	MSG s_msg;
	while(GetTickCount()-milliseconds<dwStart)
	{
//		DoEvent();
		if(PeekMessage(&s_msg, NULL, 0, 0,PM_NOREMOVE))//
		{
			if (GetMessage(&s_msg, NULL, 0, 0))
			{
				TranslateMessage(&s_msg);
				DispatchMessage(&s_msg);
			}
		}
		else
		   Sleep(1);
	}

	bInDelay=false;													//20190329
} 
	
void DoEvent()
{	
	MSG s_msg;
	if(PeekMessage(&s_msg, NULL, 0, 0,PM_NOREMOVE))//
	{
		if (GetMessage(&s_msg, NULL, 0, 0))
		{
			TranslateMessage(&s_msg);
			DispatchMessage(&s_msg);
		}
	}
//	else
//		Sleep(1);
}

CControl::CControl()
{
	riseReqCode="";
	downReqCode="";

	m_bSADataIsPreLoad=false;

	m_bSAProcMode=false;

	m_bUseOldScale=false;

	m_PauseTimeInSec=0.0;

	m_dbAutoScaleLX=1.0;
	m_dbAutoScaleLY=1.0;
	m_dbAutoScaleRX=1.0;
	m_dbAutoScaleRY=1.0;

	m_dbScaleLX[0]=1.0;
	m_dbScaleLX[1]=1.0;
	m_dbScaleLY[0]=1.0;
	m_dbScaleLY[1]=1.0;
	m_dbScaleRX[0]=1.0;
	m_dbScaleRX[1]=1.0;
	m_dbScaleRY[0]=1.0;
	m_dbScaleRY[1]=1.0;

	m_panelProcessTime=0;
	m_bLoadIsReady=false;
	m_bUnloadIsReady=false;

	m_rsCurRunState=END;
//	bFaultRun=FALSE;
	m_bOnlyOne=FALSE;				//˫��ӹ�

    m_bPitchPcbToProc = TRUE;
	m_bAbsorbedPCBLT  = TRUE;
	m_bAbsorbedPCBRT  = TRUE;
    m_uProcedPCBNum = 0;
	m_lCurDrillHoleNo = 0;
	
	m_bToManuPitchPointR = FALSE;
	m_bToManuPitchPointL = FALSE;
    m_lLoadLeft =2;	

    m_OldpostBetOne =GetDoc().GetBET1TOBET2();
    m_OldpostBetTwo=GetDoc().GetBET2TOBET3();
	TestTotolTime = 0;

	cycleno=0;											//20181203
   	m_bMatchTheFirstFid = false;
	iControlThicking=false;

	m_handfail= false;
	m_handPauseL = false;
	m_handPauseUnL = false;

	m_LIncreasingStr="NO";
	m_RIncreasingStr="NO";

	scaleLXInfo=scaleLYInfo=scaleRXInfo=scaleRYInfo=0;

	isUseTimeLoadOpt=FALSE;
	isControlLoadCommand=TRUE;
	isControlUdLoadCommand=TRUE;
	m_processAllTime=0;

	leftFiducialMoveCrd.x=0;
	rightFiducialMoveCrd.x=0;
	leftFiducialMoveCrd.y=0;
	rightFiducialMoveCrd.y=0;

	m_LampStatus=ORDER;
	m_bLeftAxisStatus=true;			//20160901
	m_bRightAxisStatus=true;

	distanceDentreDiagonal02=0;
	distanceDentreDiagonal13=0;

	m_lTablePosX=0;	
	m_lTablePosY=0;
}

CControl::~CControl()
{
 	
}

CControl& GetControl()
{
	static CControl oc;
	return oc;
}	

BOOL CControl::ChannelOutput(U32 ulData, char bState) const
{
	switch(GetCardNo(ulData))
	{
#ifdef USEMOTION
	case 0:
	case 1:
	case 2:	
		return GetMotion().ChannelOutput(GetIOBit(ulData),bState,GetCardNo(ulData));
#endif
#ifdef USEIOCARD
#ifdef NEWE2
	case 3:
		return GetIO(IOMODE).DigitalOutput(1,GetIOBit(ulData),bState);
	case 4:	
		if (ulData==OLASERON)
			return GetIO(IOMODE).DigitalOutput(2,GetIOBit(ulData),bState);
		else
			return GetIO(IOMODE).DigitalOutput(2,GetIOBit(ulData),!bState);
	case 5:
		return GetIO(IOMODE).DigitalOutput(2,GetIOBit(ulData),bState);
#else
	case 3:
		return GetIO(IOMODE).DigitalOutput(0,GetIOBit(ulData),bState);
	case 4:
		return GetIO(IOMODE).DigitalOutput(1,GetIOBit(ulData),bState);
	case 5:
		return GetIO(IOMODE).DigitalOutput(2,GetIOBit(ulData),bState);
#endif
#endif		
	}

	return FALSE;
}

int CControl::QueryIOBit(U32 ulData,int queryCOMIO) const
{
	switch(GetCardNo(ulData))
	{
#ifdef USEMOTION
	case 0:
	case 1:
	case 2:
		return GetMotion().QueryIOBit(GetIOBit(ulData),GetCardNo(ulData));
#endif
#ifdef USEIOCARD
#ifdef NEWE2
	case 3:
		if(ulData==IDOORPROTECT || ulData==ILENSWINDOW1ERROR || ulData==ILENSWINDOW2ERROR || ulData==ISWATERCOOLFAULT || ulData==ILASERGASFLUX)
			return !GetIO(IOMODE).DigitalInput(0,GetIOBit(ulData));
		else
			return GetIO(IOMODE).DigitalInput(0,GetIOBit(ulData));
	case 4:
		if (ulData==ILASERONOK)
	    	return !GetIO(IOMODE).DigitalInput(2,GetIOBit(ulData));
		else
			return GetIO(IOMODE).DigitalInput(2,GetIOBit(ulData));
	case 5:
        return GetIO(IOMODE).DigitalInput(2,GetIOBit(ulData));
#else
	case 3:
		return GetIO(IOMODE).DigitalInput(0,GetIOBit(ulData));
	case 4:
		return GetIO(IOMODE).DigitalInput(1,GetIOBit(ulData));
	case 5:
        return GetIO(IOMODE).DigitalInput(2,GetIOBit(ulData));
#endif
#endif	
	}

	return TRUE;
}

BOOL CControl::GetDoorWarning(int isCheck)
{
    BOOL hostDoor=0;
	BOOL handDoor=0;

	if(GetDoc().GetDoorOpenWarning()==0)
	{
#ifdef DoorPrt_HighLevel
		hostDoor=QueryIOBit(IDOORPROTECT);
#else
		hostDoor=!QueryIOBit(IDOORPROTECT);
#endif
	}
	else
		hostDoor=QueryIOBit(IDOOROPENPROTECT);

//	if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC) && (!GetDoc().GetUse9112()))
//		handDoor=(!QueryCOMInput(45,isCheck))||(!QueryCOMInput(46,isCheck));

	if(!GetDoc().GetUse9112())										//20190723 �޸�
	{
		if(GetDoc().GetProcessState()==CControl::AUTOPROC)
		{
			if(isCheck==0)											//�������ϵ�״̬����һ����ѯ 28����е�ִ��󱨾�
				QueryCOMInput(28);
			
			handDoor=(!QueryCOMInput(45,1))||(!QueryCOMInput(46,1));
		}				
	}

	return hostDoor||handDoor;
}

BOOL CControl::InitalControl()
{
	char ez[256] = {""};

#ifdef MEMORYSTATUSMONITOR

	m_hModule = LoadLibrary("kernel32.dll");				//���붯̬���ӿ�kernel32.dll���������ľ��
	if(NULL==m_hModule)										//�ж�����dll�Ƿ�ɹ�
		AfxMessageBox("���붯̬���ӿ�kernel32.dllʧ�ܣ�");

	GlobalMemoryStatusEx = (FunctionGlobalMemoryStatusEx)GetProcAddress(m_hModule,"GlobalMemoryStatusEx");	//��kernel32.dll��������GlobalMemoryStatusEx���������ظĺ�����ָ��
	if(NULL==GlobalMemoryStatusEx)							//�жϺ����Ƿ��ҵ�
		AfxMessageBox("��������ʧ�ܣ�");

#endif

//��ʼ�����������״̬
#ifdef LASERMONITOR
	GetDoc().SaveConfig(0);
#endif

//��ʼ��IO��
#ifdef USEIOCARD
	int ionum=0;

#ifdef NEWE2
	ionum=3;
#else
	if(GetDoc().GetUse9112())
		ionum=3;		
	else
		ionum=2;
#endif

	for(int i=0; i<ionum; ++i)
	{
		if(!GetIO(IOMODE).Inital(i))
		{
			strncpy(ez,GetLang().GetWarningText(41004),256);
			AfxMessageBox(ez);//"IO����ʼ��ʧ��!"
			return false;
		}
	}
#endif

//��ʼ������
#ifdef USECOM
	if (GetDoc().GetLaserPowerPattern()==1)
	{			
		HANDLE powerHandle=InitPowerCOM();							//���ʲ����ô���

		if (INVALID_HANDLE_VALUE==powerHandle)
		{
			GetDoc().SetLastWarningNo(98);//"�򿪴���ʧ��"
			return false;
		}
	}

//#ifndef L2TYPE													//20191203
//#ifndef NOLANDULSYSTEM
	if(GetDoc().GetLAndULSystem())
	{
#ifndef LESSWARN													//20161102 20180613׷��
		if(!GetDoc().GetUse9112())
		{
			HANDLE plcHandle=GetControlManipulator().InitPLCCOM();	//�������ô���
			
			if (INVALID_HANDLE_VALUE==plcHandle)
			{
				GetDoc().SetLastWarningNo(98);//"�򿪴���ʧ��"
				return false;
			}
		}
#endif
	}
//#endif
#endif

//��ʼ���˶���	
#ifdef USEMOTION
	BOOL rtn;
	long lCardSN[3]={0};
	int nMode=0;

#ifdef DOUBLEBET
	nMode=1;
#endif

#ifdef NEWE2
	nMode=2;
#endif

#ifdef USEDMSYSTEM													//20190507
	nMode=3;
#endif

	lCardSN[0]=GetDoc().GetMotionCardSn(0);
	lCardSN[1]=GetDoc().GetMotionCardSn(1);
	lCardSN[2]=GetDoc().GetMotionCardSn(2);

	if(lCardSN[0]==lCardSN[1] || lCardSN[0]== lCardSN[2] || lCardSN[1]==lCardSN[2])
		return FALSE;

	rtn=GetMotion().Inital(nMode,lCardSN);
	
	if(rtn<0)
	{
		if(rtn == DMCUSERCARDSNERROR)
		{
			strncpy(ez,GetLang().GetWarningText(41005),256);
			AfxMessageBox(ez);//"�˶����������!"
#ifdef USELOG
			GetLog().Append_pro(10052,20024);//"�˶����������!","����ϵͳ��ʼ��"
#endif
			return FALSE;
		}

		strncpy(ez,GetLang().GetWarningText(41006),256);
		AfxMessageBox(ez);//"�˶�����ʼ��ʧ��!"
#ifdef USELOG
		GetLog().Append_pro(10053,20024);//"�˶�����ʼ��ʧ��!","����ϵͳ��ʼ��"
#endif
		return FALSE;
	}

#ifdef USEDMSYSTEM													//20190507
	if(!GetXYMotion().Inital())
		return false;
#endif
#endif

#ifndef LESSWARN													//20171010 20180613׷��
//��ʼ��ͼ���豸 
#ifdef USEIMAGE
#ifdef AVT
	UINT32HL cameraSN[2];

	for(int index=0;index<2;index++)
	{
		cameraSN[index].High=GetDoc().GetCameraSNHigh(index);
		cameraSN[index].Low=GetDoc().GetCameraSNLow(index);
	}

	GetImageCaptor().InitImageCaptor(cameraSN);	
#endif

#ifdef PICOLO
	GetImageCaptor().InitImageCaptor(2);								//20170531	
#endif
#endif

//��ʼ���񾵿�
#ifdef USESCANLAB
	CString FileAppPath = GetDoc().GetAppPath();
	CStringV csV;

	LaserPmr lp;
	lp.deadTime=GetDoc().GetHdSysDeadTime();
	lp.laserTriggerAdjust=GetDoc().GetHdSysLaserTriggerAdjust();
	lp.laserSyncWidth=39;												//20190626	//0
	lp.laserSyncPeriod=500;

	PulseMode pm=(PulseMode)GetDoc().GetHdSysPulseMode();
	if((pm==AOMMODE)||(pm==LASERSYNCMODE))
	{
//		if(GetDoc().GetHdSysAOMOnDelay()<10)
//		{
//			AfxMessageBox("ϵͳAOMOnDelay��������������ȷ��");
//			return false;
//		}
	}

	SettleMode sm=FULLOPENLOOP;

//#ifdef SMCDLL
#if (defined SMCDLL)||(defined SMCDMDLL)
#ifdef SMCCaliDLL
	CString LCorrectionPath=FileAppPath+LPATHADJDIR+"CorL.xml\0";
	CString RCorrectionPath=FileAppPath+LPATHADJDIR+"CorR.xml\0";
#else
	CString LCorrectionPath=FileAppPath+LPATHADJDIR+"CorL.ctb\0";
	CString RCorrectionPath=FileAppPath+LPATHADJDIR+"CorR.ctb\0";
#endif
	
	if(GetDoc().GetProcAxisSelected()==1)				//20191015
		RCorrectionPath="";
	if(GetDoc().GetProcAxisSelected()==2)
		LCorrectionPath="";

	csV.push_back(LCorrectionPath);
	csV.push_back(RCorrectionPath);
#endif

#ifdef RTC3DLL
	CString LCorrectionPath=FileAppPath+LPATHADJDIR+"CorL.ctb\0";
	CString RCorrectionPath=FileAppPath+LPATHADJDIR+"CorR.ctb\0";
	CString DSPPath=FileAppPath+"RTC3D2.hex\0";

	csV.push_back(LCorrectionPath);
	csV.push_back(RCorrectionPath);
	csV.push_back(DSPPath);
#endif

#ifdef RTC4DLL
	CString LCorrectionPath=FileAppPath+LPATHADJDIR+"CorL.ctb\0";
	CString RCorrectionPath=FileAppPath+LPATHADJDIR+"CorR.ctb\0";
	CString DSPPath=FileAppPath+"RTC4D2.hex\0";

	csV.push_back(LCorrectionPath);
	csV.push_back(RCorrectionPath);
	csV.push_back(DSPPath);
#endif

#ifdef RTC5DLL
	CString LCorrectionPath=FileAppPath+LPATHADJDIR+"CorL.ct5\0";
	CString RCorrectionPath=FileAppPath+LPATHADJDIR+"CorR.ct5\0";

	csV.push_back(LCorrectionPath);
	csV.push_back(RCorrectionPath);
#endif

	if(!GalvoInit(lp,pm,sm,csV))
	{
		GalvoRelease();
		return false;
	}
#endif
#endif

//��ʼ��Cognex
#ifdef USERCOGNEX
	if(!CogInit())
		return false;

#ifdef TABLE2DCALI
	if(!GetDoc().LoadTableCorParam())
		return false;
#endif
#endif

//��ʼ������״̬
#ifdef USEIOCARD 
//��ʼ������Ԥ�ȷ���
//	ChannelOutput(OLASERWARNUP,MIO_OFF);

//��ʼ����·״̬


//��ʼ��CCD��Դ״̬
#ifdef CCSRING
	ChannelOutput(OCCDLIGHTTUNEBITLCEN , IO_ON);	//ͬ���͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTTUNEBITRCEN , IO_ON);
	ChannelOutput(OCCDLIGHTSOURCELEFT , IO_ON);		//���ι�͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTSOURCERIGHT , IO_ON);
#else
	ChannelOutput(OCCDLIGHTONL,IO_OFF);				//���ι�ߵ�ƽ��(Moritex)
	ChannelOutput(OCCDLIGHTONR,IO_OFF);	
#ifdef IO_C
	ChannelOutput(OCCDLIGHTONCOL,IO_OFF);			//ͬ���ߵ�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTONCOR,IO_OFF);
#else
	ChannelOutput(OCCDLIGHTONCOL,IO_ON);			//ͬ���͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTONCOR,IO_ON);
#endif
#endif
//��ʼ������״̬
	SetLampStatus(CControl::ORDER);
	Delay(200);
	SetLampStatus(CControl::WARN);
#endif

//��ʼ���������ϵ�״̬
	GetDoc().SetLaserPowerState(FALSE);

	return TRUE;
}

BOOL CControl::ReleaseControl()
{
#ifdef MEMORYSTATUSMONITOR
	FreeLibrary(m_hModule);										//�ͷ����ӿ���
#endif

#ifdef USESCANLAB	
//	GetSLControl().ScanLabRelease();							//20160919
	GalvoRelease();
//	Delay(100);													//20180703 ������7�� 20180720 ȡ��
#endif

#ifdef USEIOCARD
	int ionum=0;

#ifdef NEWE2
	ionum=3;
#else
	if(GetDoc().GetUse9112())
		ionum=3;		
	else
		ionum=2;
#endif

	for(int i=0; i<ionum; ++i)
	{
		GetIO(IOMODE).Release(i);
	}

//	Delay(100);
#endif

#ifdef USECOM
	if (GetDoc().GetLaserPowerPattern()==1)						//20180720 ȡ�����ڵ��ͷ�
		ReleasePowerCOM();

//#ifndef L2TYPE												//20191203
//#ifndef NOLANDULSYSTEM
	if(GetDoc().GetLAndULSystem())
	{
#ifndef LESSWARN												//20161102 20180613׷��
		if(!GetDoc().GetUse9112())
			GetControlManipulator().ReleasePLCCOM();
#endif
	}
//#endif
//	Delay(100);
#endif

#ifdef USEMOTION
	GetMotion().Release();
//	Delay(100);
#ifdef USEDMSYSTEM
	GetXYMotion().Release();
#endif
#endif

#ifdef USEIMAGE
	GetImageCaptor().ReleaseImageCaptor();
//	Delay(100);
#endif

#ifdef USERCOGNEX
	CogRelease();
//	Delay(100);
#endif

#ifdef SENTINAL
	GetDoc().ReleaseSentinal();
//	Delay(100);
#endif

	return TRUE;
}
/*
BOOL CControl::MatrixProcess(int nHead,unsigned int energy,unsigned int interval,PATHMODE pm,long lProcRangeBit,int iPointCount,POINTTYPE pt,int iToolNo,bool bPoint9)	//20160919 ����
{
//����У���ļ�
	SetHeadCorParam(0,0,0,0,1.0,1.0);
	SetHeadCorParam(1,0,0,0,1.0,1.0);
	Delay(500);																//20161216 ����

#ifdef RTC5DLL
	GalvoCorrectionSetup(0,1.0,1.0,0,0,0);
	GalvoCorrectionSetup(1,1.0,1.0,0,0,0);
#endif

//�趨�ӹ�ͷ
	ScanHead sh=SH_HeadBoth;
	if (nHead==HeadBoth)
		sh=SH_HeadBoth;
	else if (nHead==HeadLeft)
		sh=SH_Head1;
	else if (nHead==HeadRight)
		sh=SH_Head2;
	else
		return FALSE;

//�趨����ת����
	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=GetDoc().GetProcJumpLenth();
	if(interval==0)
	{
		gp.jumpSpeed=GetDoc().GetProcJumpSpeed()/5;
		gp.jumpDelay=GetDoc().GetProcJumpDelay()*10;
		gp.jumpZeroLengthDelay=gp.jumpDelay;
		gp.jumpLengthLimit=0;
	}

//�趨��ز��β���
	PulsePmr pp;
	PulsePmrV ppV;
	pp=GetPulsePmr(energy,interval,0);
	pp.xOffset=0;
	pp.yOffset=0;

	if((pm==NTYPE)||(pm==STYPE)||(pm==RANDOM))
		pp.allLaserOn=true;
	else
		pp.allLaserOn=false;

	if(bPoint9)
		pp.allLaserOn=false;

	ppV.push_back(pp);

//���ɼӹ����������������������
	XYDataV xyV,xySubV;
	GetMatrixData(xyV,pm,lProcRangeBit,iPointCount,bPoint9);
	GetSubData(xySubV,pt,iToolNo);

//�趨�ӹ��ÿ�����
	BlockData bd;

//�ӹ�
	if(!GalvoJobExecute(sh,gp,ppV,xyV,xySubV,bd,DRILLMODE))
	{
		AfxMessageBox("����ӹ������г��ִ�����ȷ�Ϲ���!");
		return FALSE;
	}

	return true;
}
*/
BOOL CControl::MatrixProcess(int nHead,unsigned int energy,unsigned int interval,PATHMODE pm,long lProcRangeBit,
							 int iPointCount,POINTTYPE pt,int iToolNo,bool bPoint9,bool bFirstPulse)				//20160919 ����	//20181229
{
//����У���ļ�
	SetHeadCorParam(0,0,0,0,1.0,1.0);
	Delay(500);																//20190221 ����
	SetHeadCorParam(1,0,0,0,1.0,1.0);
	Delay(500);																//20161216 ����

#ifdef RTC5DLL
	GalvoCorrectionSetup(0,1.0,1.0,0,0,0);
	GalvoCorrectionSetup(1,1.0,1.0,0,0,0);
#endif

//�趨�ӹ�ͷ
	ScanHead sh=SH_HeadBoth;
	if (nHead==HeadBoth)
		sh=SH_HeadBoth;
	else if (nHead==HeadLeft)
		sh=SH_Head1;
	else if (nHead==HeadRight)
		sh=SH_Head2;
	else
		return FALSE;

//�趨����ת����
	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=GetDoc().GetProcJumpLenth();
	if(interval==0)
	{
		gp.jumpSpeed=GetDoc().GetProcJumpSpeed()/5;
		gp.jumpDelay=GetDoc().GetProcJumpDelay()*10;
		gp.jumpZeroLengthDelay=gp.jumpDelay;
		gp.jumpLengthLimit=0;
	}

//�趨��ز��β���
	PulsePmr pp;
	PulsePmrV ppV;
	pp=GetPulsePmr(energy,interval,0,bFirstPulse);
	pp.xOffset=0;
	pp.yOffset=0;

	if((pm==NTYPE)||(pm==STYPE)||(pm==RANDOM))
		pp.allLaserOn=true;
	else
		pp.allLaserOn=false;

	if(bPoint9)
		pp.allLaserOn=false;

	ppV.push_back(pp);

//���ɼӹ����������������������
	XYDataV xyV,xySubV;
	GetMatrixData(xyV,pm,lProcRangeBit,iPointCount,bPoint9);
	GetSubData(xySubV,pt,iToolNo);

//�趨�ӹ��ÿ�����
	BlockData bd;

//�ӹ�
	if(!GalvoJobExecute(sh,gp,ppV,xyV,xySubV,bd,DRILLMODE))
	{
		AfxMessageBox("����ӹ������г��ִ�����ȷ�Ϲ���!");
		return FALSE;
	}

	return true;
}

BOOL CControl::DrillMatrix(int nSize,int nType, int nHead) 
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

//�л���Ȧ
	MoveTo(GetDoc().GetTestAperture());

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetTestBoardThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

	int iCount=1;
	PATHMODE pm;
	POINTTYPE pt=ONLYHOLE;

	switch(nSize)
	{
	case 0:
		iCount=1;
		break;
	case 1:
		iCount=11;
		break;
	case 2:
		iCount=17;
		break;
	case 3:
		iCount=21;
		break;
	case 4:
		iCount=33;
		break;
	case 5:
		iCount=61;
		break;
	default:
		AfxMessageBox("�����趨��Ч����ȷ��!");
		return false;
	}

	switch(nType)
	{
	case 0:
		pm=NTYPE;
		break;
	case 1:
		pm=STYPE;
		break;
	case 2:
		AfxMessageBox("�˹�����ʱδʵ��!");
		return false;
	case 3:
		pm=NTYPE;
		pt=CROSS;
		break;
	default:
		AfxMessageBox("�����趨��Ч����ȷ��!");
		return false;
	}

	MatrixProcess(nHead,GetDoc().GetTestPlsRelease(),GetDoc().GetTestPlsPeriod(),pm,GetDoc().GetDefineMatrixRange(),iCount,pt);

//��ͷ���������ر�	
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

	return true;
}

BOOL CControl::DrillParamTest(int nHead,int iToolNo,double iTsize) 
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetPCBThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);	
	Delay(500);
	
	POINTTYPE pt=ONLYHOLE;
	int iCount;
	long lProcRangeBit;
	
	if(iTsize==0)
	{
		iCount=11;
		lProcRangeBit=10*GetDoc().GetSLBitPerMM();
	}
	else
	{
		iCount=GetDoc().GetScanSize()/iTsize+1;
		lProcRangeBit=GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM();
	}

	if(GetDoc().GetSysCircleProcMode())	
	{
		pt=CIRCLEWINDOW;
		
		if(iTsize==0)
			iCount=3;
		else
		{
			iCount=GetDoc().GetScanSize()/(iTsize*10)+1;
			if((iCount%2)==0)
				++iCount;
		}
	}

	int nApt;	
	int nToolCycNum = GetDoc().GetToolPara(iToolNo,0).GetCycleNum();

	for(int k=0; k<nToolCycNum; ++k)
	{
		Energy eng;
		int minJump=0;	
		
		if(GetDoc().GetToolSubApertureNo(iToolNo)!=0)
//		if(GetDoc().GetToolSubShowApertureNo(iToolNo)!=0)
		{
			if(k==0)
				nApt = GetDoc().GetToolApertureNo(iToolNo);
			else
				nApt = GetDoc().GetToolSubApertureNo(iToolNo);
		}
		else
			nApt = GetDoc().GetToolApertureNo(iToolNo);
			
		MoveTo(nApt);
		
		eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);

		if (k==0)
		{
			if(GetDoc().GetFitApt())
				minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
			else
				minJump=GetDoc().GetFirstDelayPeriod(); 
		}
		else
			minJump=GetDoc().GetOtherDelayPeriod();	
		
//		MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,lProcRangeBit,iCount,pt,iToolNo);
		MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,lProcRangeBit,iCount,pt,iToolNo,false,k==0);			//20181229
	}
	
//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
	
	return true;
}

BOOL CControl::LaserPowerMeasure(int nHead,short posx,short posy,unsigned int energy,unsigned int interval,long time,float *volt)
{
//��ʼ������ֵ
	fLaserPower=0.0;

//����У���ļ�
	SetHeadCorParam(0,0,0,0,1.0,1.0);
	Delay(500);																//20190221 ����
	SetHeadCorParam(1,0,0,0,1.0,1.0);
	Delay(500);																//20161216 ����

#ifdef RTC5DLL
	GalvoCorrectionSetup(0,1.0,1.0,0,0,0);
	GalvoCorrectionSetup(1,1.0,1.0,0,0,0);
#endif

//�趨�ӹ�ͷ
	ScanHead sh=SH_HeadBoth;
	if (nHead==HeadLeft)
		sh=SH_Head1;
	else if (nHead==HeadRight)
		sh=SH_Head2;
	else
		return FALSE;

//�趨����ת����
	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=0;

//�趨��ز��β���
	PulsePmr pp;
	PulsePmrV ppV;
//	pp=GetPulsePmr(energy,interval,time*1000000/interval);
	pp=GetPulsePmr(energy,interval,time*1000000/interval,true,true);		//20200515
	pp.xOffset=0;
	pp.yOffset=0;
	pp.allLaserOn=true;
	ppV.push_back(pp);

//���ɼӹ����������������������
	XYData xyd;
	XYDataV xyV,xySubV;
	xyd.coordX=-posy*GetDoc().GetSLBitPerMM()/1000.0;
	xyd.coordY=posx*GetDoc().GetSLBitPerMM()/1000.0;
	xyd.laserON=true;
	xyV.push_back(xyd);

//�趨�ӹ��ÿ�����
	BlockData bd;

//�ӹ�������
	DWORD dwExitCode=1;
	HANDLE handle=CreateThread(NULL,0,GetPowerData,NULL,0,NULL);
	Delay(500);

	bPowerOn=true;

#ifdef SMCPreLoad
	if(!GalvoJobExecute(sh,gp,ppV,xyV,xySubV,bd,POWERBLOCKMODE))
	{
		AfxMessageBox("���ʼӹ������г��ִ�����ȷ�Ϲ���!");
		bPowerOn=false;
		WaitForSingleObject(handle,INFINITE);
		CloseHandle(handle);
		return FALSE;
	}
#else
	if(!GalvoJobExecute(sh,gp,ppV,xyV,xySubV,bd,POWERMODE))
	{
		AfxMessageBox("���ʼӹ������г��ִ�����ȷ�Ϲ���!");
		bPowerOn=false;
		WaitForSingleObject(handle,INFINITE);
		CloseHandle(handle);
		return FALSE;
	}
#endif

	bPowerOn=false;
	WaitForSingleObject(handle,INFINITE);

	GetExitCodeThread(handle,&dwExitCode);
	if(dwExitCode==0)
	{
		AfxMessageBox("���������г��ִ�����ȷ�Ϲ���!");
		CloseHandle(handle);
		return FALSE;
	}

	CloseHandle(handle);

	*volt=fLaserPower;

	return TRUE;
}

DWORD WINAPI GetPowerData(LPVOID pM)
{
	int num=0;
	float total=0.0;
	double volt1=0.0;
	float volt2=0.0;
//	HANDLE powerHandle=GetDoc().GetPowerComHandle();
	std::vector<float> LaserPowerDataV;

	Delay(6000);
	while(bPowerOn)
	{
		if (0==GetDoc().GetLaserPowerPattern())					//��ѹ���ʽ���⹦��̽ͷ
		{	
//			GetIO(2).GetAnalogInput(0,AD_B_5_V,&volt1); 
			volt1=GetIO(IOMODE).AnalogInput(2,0); 			

			volt2 = float(GetDoc().GetPowerScale()*volt1);		//volt2 = float(volt1)
			total += volt2; 
			LaserPowerDataV.push_back(volt2*10);				//10����ϵ
			num++;

//			CString strinfo = GetDoc().GetAppPath()+POWERDIR;
//			GetInfo().SaveToFile(strinfo,"POWER:%f\n",volt2*10);
		}
		
		if (1==GetDoc().GetLaserPowerPattern())					//�������ʽ���⹦��̽ͷ
		{
//			if (powerHandle!=INVALID_HANDLE_VALUE)
//			{
				char buf[128]="pw? \r";
				if (0==GetCOM(0).WriteDataToCom(buf,strlen(buf)))
					return false;

				memset(buf,0,128);

				if (GetCOM(0).ReadDataFromCom(buf,128) > 0)
				{
					CString source=buf;
					source.TrimRight();			
					volt1=atof(source);				                
				}
				else
					return false;
//			}
//			else
//				return false;
			
			volt2 = float(GetDoc().GetPowerScale()*volt1);		//volt2 = float(volt1)
			total += volt2; 
			LaserPowerDataV.push_back(volt2);					//1����ϵ
			num++;

//			CString strinfo = GetDoc().GetAppPath()+POWERDIR;
//			GetInfo().SaveToFile(strinfo,"POWER:%f\n",volt2);
		}
		
		Delay(1000);
	}

//	*volt = total/num; 
	if(LaserPowerDataV.size()>16)
	{
		std::sort(LaserPowerDataV.begin(),LaserPowerDataV.end());

		if(GetDoc().GetLaserPowerMode()==1)							//20180313
		{
			GetDoc().ResetLaserPw();

			int middle=LaserPowerDataV.size()/2+1;					//ȡ���м�λ��			
			for(int j=0,k=middle-2;j<5;j++,k++)
			{
				GetDoc().SetLaserPw(j,LaserPowerDataV[k]);
			}
			
			fLaserPower=GetDoc().GetLaserPwAvg()/10.0;
		}
		else
		{
			total=0;
			for (int i=3;i<LaserPowerDataV.size()-3;i++)			//ȥ��3�����ֵ��ȥ��3����Сֵ
			{
				total+=LaserPowerDataV[i];
			}
			
			fLaserPower=total/10.0/((float)(LaserPowerDataV.size()-6));
		}
	}
	else
		fLaserPower=0;

	return true;
}

BOOL CControl::GetLaserPowerTest(int nHead,long time,float &power,int nIndex)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);
	ASSERT(nIndex>=0&&nIndex<5);

	char ez[256]={""};
	Coord crdCleanRef;
	Coord3D crd3d;
	float volt;

	Coord crdXY;
	long  lLZPos;
	long  lRZPos;
	short lDPosH;
	short lDPosV;

//����λ��ƫ��λ��
	switch(nIndex)
	{
		case 0:
			lDPosH= 0;lDPosV= 0;
			break;
		case 1:
			lDPosH= -25000;lDPosV= 25000;
			break;
		case 2:
			lDPosH= 25000;lDPosV= 25000;
			break;
		case 3:
			lDPosH= -25000;lDPosV=-25000;
			break;
		case 4:
			lDPosH= 25000;lDPosV= -25000;
			break;
		default:
			strncpy(ez,GetLang().GetWarningText(21035),256);
			AfxMessageBox(ez);//"����ƫ����ʱ��������"
			return false;
	}

	bInPowerTest=true;												//20190626

//��ȡ��ǰλ��	
	crdXY.x = GetPos(AXISTABX);
	crdXY.y = GetPos(AXISTABY);
	lLZPos = GetPos(AXISLEFTZ);
	lRZPos = GetPos(AXISRIGHTZ);

//�л���Ȧ
	MoveTo(GetDoc().GetTestAperture());	

//����
	crdCleanRef = GetDoc().GetLaserTestCleanRefPos();
	MoveTo(crdCleanRef);
	WaitAxisStop(AXISTAB);
	
	ChannelOutput( OLASERPOWERCLEANER,MIO_ON);
	Delay(1500);
	ChannelOutput( OLASERPOWERCLEANER,MIO_OFF);
	
//ƽ̨�ƶ�������λ��
	crd3d= GetDoc().GetLaserPowerTestCrd(nHead);
	MoveTo(Coord(crd3d.x+lDPosH,crd3d.y+lDPosV));
	WaitAxisStop(AXISTAB);

//Z���ƶ��������߶�	
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,crd3d.z);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,crd3d.z);
		WaitAxisStop(AXISRIGHTZ);
	}

//��ʼ����
	if(!LaserPowerMeasure(nHead,lDPosH,lDPosV,GetDoc().GetTestPlsRelease(),GetDoc().GetTestPlsPeriod(),time,&volt))
	{
		bInPowerTest=false;												//20190626
		return false;
	}

	power=volt*10;

//��¼�������
#ifdef USELOG	
	GetLog().Append_pro(10107,20040);//"�����ɹ�","������������"

	CString tempTime;
    tempTime.Format("%d",time);

	char ez1[20]={""};
	char ez2[20]={""};
	strncpy(ez1 ,GetLang().GetLogText("operation",10031),20);
	strncpy(ez2 ,GetLang().GetLogText("operation",10032),20);

	float laserPower=volt*10;
    if(laserPower<0.2)
		laserPower=0;	

	char buf[64];
	sprintf(buf,"%2.1f",laserPower);
	laserPower=atof(buf);

	GetLog().Append_Power((nHead==0)? ez1:ez2,laserPower,tempTime,
		(int)GetDoc().GetTestPlsRelease(),(int)GetDoc().GetTestPlsPeriod(),(int)GetDoc().GetTestAperture());//"��":"��"
#endif

//����ԭʼλ��
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,lLZPos);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,lRZPos);
		WaitAxisStop(AXISRIGHTZ);
	}

	MoveTo(crdXY);
	WaitAxisStop(AXISTAB);

	bInPowerTest=false;												//20190626

	return true;
}

BOOL CControl::LaserWarmup(int nTime)
{
	char ez[256]={""};
	
	ChannelOutput(OLASERWARNUP,MIO_OFF);

	DWORD dwStart,dwStop;
	dwStart = GetTickCount();

	while(QueryIOBit(ILASERWARMUPP))
	{		
		dwStop = GetTickCount();
		if(dwStop-1000*3>dwStart)
		{
			strncpy(ez,GetLang().GetWarningText(41007),256);
			AfxMessageBox(ez);//" ����Ԥ������δ�ܵ�λ������! "
#ifdef USELOG
			GetLog().Append_pro(10055,20001);//"����Ԥ������δ�ܵ�λ������!","����Ԥ��"
#endif
			return FALSE;
		}
	}

//����У���ļ�
	SetHeadCorParam(0,0,0,0,1.0,1.0);
	Delay(500);																//20190221 ����
	SetHeadCorParam(1,0,0,0,1.0,1.0);
	Delay(500);																//20161216 ����

#ifdef RTC5DLL
	GalvoCorrectionSetup(0,1.0,1.0,0,0,0);
	GalvoCorrectionSetup(1,1.0,1.0,0,0,0);
#endif

//�趨����ת����
	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=0;

//�趨��ز��β���
	PulsePmr pp;
	PulsePmrV ppV;
	pp=GetPulsePmr(5,2000,nTime*1000000/2000);
	pp.xOffset=0;
	pp.yOffset=0;
	pp.allLaserOn=true;
	ppV.push_back(pp);

//���ɼӹ����������������������
	XYData xyd;
	XYDataV xyV,xySubV;
	xyd.coordX=0;
	xyd.coordY=0;
	xyd.laserON=true;
	xyV.push_back(xyd);

//�趨�ӹ��ÿ�����
	BlockData bd;

//�ӹ�
	if(!GalvoJobExecute(SH_HeadBoth,gp,ppV,xyV,xySubV,bd,POWERMODE))
	{
		AfxMessageBox("Ԥ�ȼӹ������г��ִ�����ȷ�Ϲ���!");
		return FALSE;
	}

	ChannelOutput(OLASERWARNUP,MIO_ON);
	
	dwStart = GetTickCount();
	while(QueryIOBit(ILASERWARMUPN))
	{
		dwStop = GetTickCount();
		if(dwStop-1000*3>dwStart)
		{
			strncpy(ez,GetLang().GetWarningText(41008),256);
			AfxMessageBox(ez);//" ����Ԥ������δ�ָܻ���λ������! "
#ifdef USELOG
			GetLog().Append_pro(10056,20001);//"����Ԥ������δ�ָܻ���λ������!","����Ԥ��"
#endif
			return FALSE;
		}
	}

	return true;
}
/*
BOOL CControl::LaserComInital()
{
	char ez[256]={""};	
	time_t start_time, end_time;

//������1�ϵ�
	ChannelOutput(OLASERON,IO_ON);
	Delay(1000);
	ChannelOutput(OLASERSHUTTERON,IO_ON);
	Delay(1000);

	start_time = time( NULL );
	
#ifdef IO_LASERONOK_HIGH     
	while(!QueryIOBit(ILASERONOK))			//�ߵ�ƽ��Ч
#else
	while(QueryIOBit(ILASERONOK))
#endif
	{
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
			strncpy(ez,GetLang().GetWarningText(41014),256);
			AfxMessageBox(ez);//"�ϵ�ʧ��!"
#ifdef  USELOG
			GetLog().Append_pro(10064,20026);//"�ϵ�ʧ��!","�������"
#endif
			ChannelOutput(OLASERON,IO_OFF);
			ChannelOutput(OLASERSHUTTERON,IO_OFF);

			return FALSE;
		}
	}

	Delay(1000);

#ifdef DOUBLELASER
//������2�ϵ�
	ChannelOutput(OLASERON2,IO_ON);
	Delay(1000);
	
	start_time = time( NULL ); 
	while(!QueryIOBit(LASEROK2))			//�ߵ�ƽ��Ч		
	{
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
			strncpy(ez,GetLang().GetWarningText(41014),256);
			AfxMessageBox(ez);//"�ϵ�ʧ��!"
			ChannelOutput(OLASERON2,IO_OFF);
			return FALSE;
		}
	}

	Delay(1000);

#endif

#ifndef IO_C
	ChannelOutput(OLASERPROTECTGAS,MIO_ON);
	ChannelOutput(OLASERWARNUP,MIO_ON); 

	start_time = time( NULL );
	while(GetControl().QueryIOBit(ILASERWARMUPN))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
#ifndef LESSWARN
			strncpy(ez,GetLang().GetWarningText(41015),256);
			AfxMessageBox(ez);//"����Ԥ�ȿ���δ�ܴ򿪣�����!"
#endif
			ChannelOutput(OLASERPROTECTGAS,MIO_OFF);
			ChannelOutput(OLASERWARNUP,MIO_OFF);
			return false;
		}
	}
#endif

	GetDoc().SetLaserPowerState(TRUE);
	return TRUE;
}

BOOL CControl::LaserComRelease()
{
	char ez[256]={""};
	time_t start_time, end_time;

//������1����
	ChannelOutput(OLASERSHUTTERON,IO_OFF);
	Delay(1000);
	ChannelOutput(OLASERON,IO_OFF);

#ifdef DOUBLELASER
//������2����
	ChannelOutput(OLASERON2,IO_OFF);
#endif

#ifndef IO_C
	ChannelOutput(OLASERPROTECTGAS,MIO_OFF);
	ChannelOutput(OLASERWARNUP,MIO_OFF); 

	start_time = time( NULL );
	while(GetControl().QueryIOBit(ILASERWARMUPP))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
#ifndef LESSWARN
			strncpy(ez,GetLang().GetWarningText(41016),256);
			AfxMessageBox(ez);//"����Ԥ�ȿ���δ�ܹرգ�����!"
#endif
		}
	}
#endif

	GetDoc().SetLaserPowerState(FALSE);
	return TRUE;
}
*/
BOOL CControl::LaserComInital()												//20191015
{
	char ez[256]={""};	
	time_t start_time, end_time;

#ifdef DOUBLELASER

	int axisMode=GetDoc().GetProcAxisMode();
	if((axisMode==0)||(axisMode==1))
	{
		ChannelOutput(OLASERON,IO_ON);			//������1�ϵ�
		Delay(1000);
		
		start_time = time( NULL ); 
		while(!QueryIOBit(ILASERONOK))			//�ߵ�ƽ��Ч		
		{
			end_time = time( NULL );
			if( difftime(end_time, start_time)>5 )
			{
				strncpy(ez,GetLang().GetWarningText(41014),256);
				AfxMessageBox(ez);//"�ϵ�ʧ��!"
				ChannelOutput(OLASERON,IO_OFF);
				return FALSE;
			}
		}
		Delay(1000);
	}

	if((axisMode==0)||(axisMode==2))
	{
		ChannelOutput(OLASERON2,IO_ON);			//������2�ϵ�
		Delay(1000);
		
		start_time = time( NULL ); 
		while(!QueryIOBit(LASEROK2))			//�ߵ�ƽ��Ч		
		{
			end_time = time( NULL );
			if( difftime(end_time, start_time)>5 )
			{
				strncpy(ez,GetLang().GetWarningText(41014),256);
				AfxMessageBox(ez);//"�ϵ�ʧ��!"
				ChannelOutput(OLASERON2,IO_OFF);
				return FALSE;
			}
		}
		Delay(1000);
	}

#else

	ChannelOutput(OLASERON,IO_ON);				//�������ϵ�
	Delay(1000);
	ChannelOutput(OLASERSHUTTERON,IO_ON);
	Delay(1000);

	start_time = time( NULL );
	
#ifdef IO_LASERONOK_HIGH     
	while(!QueryIOBit(ILASERONOK))				//�ߵ�ƽ��Ч
#else
	while(QueryIOBit(ILASERONOK))				//�͵�ƽ��Ч
#endif
	{
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
			strncpy(ez,GetLang().GetWarningText(41014),256);
			AfxMessageBox(ez);//"�ϵ�ʧ��!"
#ifdef  USELOG
			GetLog().Append_pro(10064,20026);//"�ϵ�ʧ��!","�������"
#endif
			ChannelOutput(OLASERON,IO_OFF);
			ChannelOutput(OLASERSHUTTERON,IO_OFF);

			return FALSE;
		}
	}
	Delay(1000);

#endif

#ifndef IO_C
	ChannelOutput(OLASERPROTECTGAS,MIO_ON);
	ChannelOutput(OLASERWARNUP,MIO_ON); 

	start_time = time( NULL );
	while(GetControl().QueryIOBit(ILASERWARMUPN))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
#ifndef LESSWARN
			strncpy(ez,GetLang().GetWarningText(41015),256);
			AfxMessageBox(ez);//"����Ԥ�ȿ���δ�ܴ򿪣�����!"
#endif
			ChannelOutput(OLASERPROTECTGAS,MIO_OFF);
			ChannelOutput(OLASERWARNUP,MIO_OFF);
			return false;
		}
	}
#endif

	GetDoc().SetLaserPowerState(TRUE);
	return TRUE;
}

BOOL CControl::LaserComRelease()											//20191015
{
	char ez[256]={""};
	time_t start_time, end_time;

#ifdef DOUBLELASER

	int axisMode=GetDoc().GetProcAxisMode();
	if((axisMode==0)||(axisMode==1))
		ChannelOutput(OLASERON,IO_OFF);			//������1����
	if((axisMode==0)||(axisMode==2))
		ChannelOutput(OLASERON2,IO_OFF);		//������2����
#else

	ChannelOutput(OLASERSHUTTERON,IO_OFF);
	Delay(1000);
	ChannelOutput(OLASERON,IO_OFF);				//����������

#endif

#ifndef IO_C
	ChannelOutput(OLASERPROTECTGAS,MIO_OFF);
	ChannelOutput(OLASERWARNUP,MIO_OFF); 

	start_time = time( NULL );
	while(GetControl().QueryIOBit(ILASERWARMUPP))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>5 )
		{
#ifndef LESSWARN
			strncpy(ez,GetLang().GetWarningText(41016),256);
			AfxMessageBox(ez);//"����Ԥ�ȿ���δ�ܹرգ�����!"
#endif
		}
	}
#endif

	GetDoc().SetLaserPowerState(FALSE);
	return TRUE;
}

void CControl::UnloadPcbAndNG()							//ԭ�е�ʹ��9112ʱʹ�õ�����
{
	if(!m_bFoundLocalMarkPCB1)
	{
		ChannelOutput(OLEFTERRO,MIO_ON);
		Delay(500);
		ChannelOutput(OLEFTERRO,MIO_OFF); 
		
		int m_iNGSum = GetDoc().GetNGSum();
		m_iNGSum++;
		GetDoc().SetNGSum(m_iNGSum);
		
		if(m_iNGSum>GetDoc().GetNGThred())
			GetDoc().SetLastWarningNo(37);//NG����
	}

	if(!m_bFoundLocalMarkPCB2&&!m_bOnlyOne)
	{
		ChannelOutput(ORIGHTERRO,MIO_ON);
		Delay(500);
		ChannelOutput(ORIGHTERRO,MIO_OFF);    

		int m_iNGSum = GetDoc().GetNGSum();
		m_iNGSum++;
		GetDoc().SetNGSum(m_iNGSum);
		
		if(m_iNGSum>GetDoc().GetNGThred())
			GetDoc().SetLastWarningNo(37);//NG����
	}
}

BOOL CControl::UnloadPcb()									//ԭ�е�ʹ��9112ʱʹ�õ�����
{
	if(GetDoc().GetProcessState()!=SystemDoc::AUTOPROC)
       return FALSE;

    int outTime=25;
	if (1==GetDoc().GetFunctionOverBorad())//ʹ�÷�����Ĺ��� ���ڷ����ʱ����Ҫ�ȴ�ʱ��ܳ�
       outTime=150;

	time_t start_time, end_time;

	start_time = time( NULL );
    while(QueryIOBit(IREADYTOUNLOADOK))
	{	
		if(!PeekRunState())
			return FALSE;

		if(m_handPauseUnL)//ly change 20130905//ly add 20110816 !QueryIOBit(STOPMOVE)
		{
			start_time = time( NULL );
		}		
		end_time = time( NULL );		
		if( difftime(end_time, start_time)>outTime )
		{
#ifdef USELOG
			GetLog().Append_pro(10065,20027);//"�����ֵ�������λ�ó�ʱ��","�ȴ�����"
#endif
			GetDoc().SetLastWarningNo(76);
			return FALSE;
		}
		Delay(1);//20150505
	}

	UnloadPcbAndNG();//20150505

	if(m_handPauseUnL)//ly add 20130905
	{
		while(1)
		{
			
			if(!m_handPauseUnL)
				break;
			Delay(1);//20150505
		}
	}

	ChannelOutput(OUNLAORDBORD,MIO_ON);
	Delay(500);
	if(m_handPauseUnL)//ly add 20110816
	{
		while(1)//ly add 20130905
		{
			if(!m_handPauseUnL)
				break;
			Delay(1);//20150505
		}
		Delay(500);
	}
	ChannelOutput(OUNLAORDBORD,MIO_OFF);

	start_time = time( NULL );
    while(QueryIOBit(IUNLOADOK))
	{	
		if(!PeekRunState())
			return FALSE;

		if(m_handPauseUnL)//ly change 20130905//ly add 20110816 !QueryIOBit(STOPMOVE)
		{
			start_time = time( NULL );
		}
		end_time = time( NULL );		
		if( difftime(end_time, start_time)>outTime)
		{
#ifdef USELOG
			GetLog().Append_pro(10066,20027);//"���ϳ�ʱ��","�ȴ�����"
#endif
			GetDoc().SetLastWarningNo(77);
			return FALSE;
		}
		Delay(1);//20150505
	}
	
	return TRUE;
}

long CControl::HomeAPT()
{
	char ez[256]={""};

#ifdef DOUBLEBET
	GetMotion().Home(AXISAPT);
	GetMotion().Home(AXISAPT2);
	Delay(500);	
    GetMotion().WaitStopWhenProgramming(AXISAPT);
	GetMotion().WaitStopWhenProgramming(AXISAPT2);
	Delay(2000);

	if(GetMotion().GetMationSH(AXISAPT))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if(GetMotion().GetMationSH(AXISAPT2))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if (GetMotion().MoveTo(AXISAPT,GetDoc().GetAptBenchmark(),
		GetDoc().GetMoveAcc(AXISAPT),GetDoc().GetMoveDec(AXISAPT),
		GetDoc().GetMoveMaxSpeed(AXISAPT))!=DMCNOERROR)
	{
		AfxMessageBox("AXISAPT Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISAPT2,GetDoc().GetAptBenchmark2(),
		GetDoc().GetMoveAcc(AXISAPT),GetDoc().GetMoveDec(AXISAPT),
		GetDoc().GetMoveMaxSpeed(AXISAPT))!=DMCNOERROR)
	{
		AfxMessageBox("AXISAPT2 Motion Fault!");
		return 4;
	}

	WaitAxisStop(AXISAPT);
	WaitAxisStop(AXISAPT2);	
	Delay(300);

	GetMotion().SetPos(AXISAPT,0);
	GetMotion().SetPos(AXISAPT2,0);
#else
	GetMotion().Home(AXISAPT); 
	Delay(500);
    GetMotion().WaitStopWhenProgramming(AXISAPT);
	Delay(2000);	

	if(GetMotion().GetMationSH(AXISAPT))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if (GetMotion().MoveTo(AXISAPT,GetDoc().GetAptBenchmark(),
		GetDoc().GetMoveAcc(AXISAPT),GetDoc().GetMoveDec(AXISAPT),
		GetDoc().GetMoveMaxSpeed(AXISAPT))!=DMCNOERROR)
	{
		AfxMessageBox("AXISAPT Motion Fault!");
		return 4;
	}

	WaitAxisStop(AXISAPT);
	Delay(300);

	GetMotion().SetPos(AXISAPT,0);
#endif

	GetDoc().SetCurAptNo(1);
	return 0;
}

long CControl::HomeBET()
{
	char ez[256]={""};

#ifdef DOUBLEBET
	GetMotion().Home(AXISBETPRI);	 
	GetMotion().Home(AXISBETSUB);
	GetMotion().Home(AXISBETPRI2);	 
	GetMotion().Home(AXISBETSUB2);
	Delay(500);	
	GetMotion().WaitStopWhenProgramming( AXISBETPRI);	
	GetMotion().WaitStopWhenProgramming( AXISBETSUB);
	GetMotion().WaitStopWhenProgramming( AXISBETPRI2);	
	GetMotion().WaitStopWhenProgramming( AXISBETSUB2);
	Delay(500);	

	if(GetMotion().GetMationSH(AXISBETPRI))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if(GetMotion().GetMationSH(AXISBETSUB))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}

	if(GetMotion().GetMationSH(AXISBETPRI2))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if(GetMotion().GetMationSH(AXISBETSUB2))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}

	if (GetMotion().MoveTo(AXISBETPRI,GetDoc().GetBETPriOffset(),
		GetDoc().GetMoveAcc(AXISBETPRI),GetDoc().GetMoveDec(AXISBETPRI),
		GetDoc().GetMoveMaxSpeed(AXISBETPRI))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETPRI Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISBETSUB,GetDoc().GetBETBenchmark(),
		GetDoc().GetMoveAcc(AXISBETSUB),GetDoc().GetMoveDec(AXISBETSUB),
		GetDoc().GetMoveMaxSpeed(AXISBETSUB))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETSUB Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISBETPRI2,GetDoc().GetBETPriOffset2(),
		GetDoc().GetMoveAcc(AXISBETPRI),GetDoc().GetMoveDec(AXISBETPRI),
		GetDoc().GetMoveMaxSpeed(AXISBETPRI))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETPRI2 Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISBETSUB2,GetDoc().GetBETSubOffset2(),
		GetDoc().GetMoveAcc(AXISBETSUB),GetDoc().GetMoveDec(AXISBETSUB),
		GetDoc().GetMoveMaxSpeed(AXISBETSUB))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETSUB2 Motion Fault!");
		return 4;
	}
	
	WaitAxisStop(AXISBETPRI);
	WaitAxisStop(AXISBETSUB);
	WaitAxisStop(AXISBETPRI2);
	WaitAxisStop(AXISBETSUB2);
	Delay(300);

	GetMotion().SetPos(AXISBETPRI,0);
	GetMotion().SetPos(AXISBETSUB,0);
	GetMotion().SetPos(AXISBETPRI2,0);
	GetMotion().SetPos(AXISBETSUB2,0);
#else
	GetMotion().Home(AXISBETPRI);	 
	GetMotion().Home(AXISBETSUB);
	Delay(500);	
	GetMotion().WaitStopWhenProgramming( AXISBETPRI);	
	GetMotion().WaitStopWhenProgramming( AXISBETSUB);
	Delay(500);

	if(GetMotion().GetMationSH(AXISBETPRI))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if(GetMotion().GetMationSH(AXISBETSUB))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
		
	if (GetMotion().MoveTo(AXISBETPRI,GetDoc().GetBETPriOffset(),
		GetDoc().GetMoveAcc(AXISBETPRI),GetDoc().GetMoveDec(AXISBETPRI),
		GetDoc().GetMoveMaxSpeed(AXISBETPRI))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETPRI Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISBETSUB,GetDoc().GetBETBenchmark(),
		GetDoc().GetMoveAcc(AXISBETSUB),GetDoc().GetMoveDec(AXISBETSUB),
		GetDoc().GetMoveMaxSpeed(AXISBETSUB))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETSUB Motion Fault!");
		return 4;
	}

	WaitAxisStop(AXISBETPRI);
	WaitAxisStop(AXISBETSUB);
	Delay(300);
	
	GetMotion().SetPos(AXISBETPRI,0);
	GetMotion().SetPos(AXISBETSUB,0);
#endif

	return 0;
}

//�й�MoveTo
//0:OK
//1:δ����
//2:������Ч�г�
//3:���ʹ�ܴ���
//4:������ָ����ɴ���
//5:���о��Ȳ���

long CControl::MoveTo(U32 ulAxis, long pos)
{
	Coord crd=Coord(m_lTablePosX,m_lTablePosY);
	char ez[256]={""};
	CString str="";

//�жϻ�������״̬
	if(!GetDoc().GetMotorState())										
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return 1;
	}
/*
	if(GetMotion().GetMationSH(ulAxis))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}	
*/
//#ifndef NOLANDULSYSTEM
	if(GetDoc().GetLAndULSystem())
	{
		if((ulAxis==AXISTABX)||(ulAxis==AXISTABY))							//20190627
		{
			if(!GetDoc().GetUse9112())
			{
//#ifdef UNLOADISOK
				if(GetDoc().GetUnloadIsOK())
				{
					if(!QueryCOMInput(68))				//����������Ƿ��ڰ�ȫλ�ã�ͬʱˢ��������״̬	68�������ϰ�ȫλ�ñ���
					{
						AfxMessageBox("������λ�ò���ȫ���޷��ƶ�ƽ̨����ȷ��!");
						return 3;
					}
				}
//#else
				else
				{
					if((GetDoc().GetProcessState()==CControl::AUTOPROC)&&(GetControl().GetRunState()==CControl::RUN))
						QueryCOMInput(28);				//�Զ������ϼӹ�ʱ��ÿ��ƽ̨�ƶ����������ϵ�״̬����һ����ѯ 28����е�ִ��󱨾�
				}
//#endif
			}
			
//			PeekRunState();								//20190723 ��������ͣ ������
		}
	}
//#endif

#ifndef NO_SOFT_LIMIT
	if((ulAxis==AXISLEFTZ)||(ulAxis==AXISRIGHTZ))						//20180912
	{
		if(pos>GetDoc().GetFORWARDZ()||pos<0)
		{
			AfxMessageBox("Z�ᳬ����Ч�˶���Χ����ȷ�ϣ�");
			return 2;
		}
	}
#endif

#ifdef TABLE2DCALI
	int label=0;

	if(ulAxis==AXISTABX)
	{
#ifndef NO_SOFT_LIMIT
		if(pos>GetDoc().GetFORWARDX()||pos<GetDoc().GetREVERSEX())
		{
			strncpy(ez,GetLang().GetWarningText(41017),256);
			AfxMessageBox(ez);//"ƽ̨������Ч�˶���Χ����ȷ������!"
			return 2;
		}
#endif
//		if(m_lTablePosY<(DIVIDINGLINE))									//20200414
//			label=1;

		if(!GetDoc().GetTableIsCali())
		{
			if(!CogTableMapPoint(0,label,Coord(pos,m_lTablePosY),crd))
			{
				SetLampStatus(CControl::ERR);
				ChannelOutput(OCOMMONALARM ,TRUE);
				
				AfxMessageBox("ƽ̨�ƶ�����ӳ����������ȷ�ϣ�");
				
				SetLampStatus(CControl::ORDER);
				ChannelOutput(OCOMMONALARM ,FALSE);
				return 4;
			}			
		}
	}
	
	if(ulAxis==AXISTABY)
	{
#ifndef NO_SOFT_LIMIT
		if(pos>GetDoc().GetFORWARDY()||pos<GetDoc().GetREVERSEY())
		{
			strncpy(ez,GetLang().GetWarningText(41017),256);
			AfxMessageBox(ez);//"ƽ̨������Ч�˶���Χ����ȷ������!"
			return 2;
		}
#endif
//		if(pos<(DIVIDINGLINE))											//20200414
//			label=1;

		if(!GetDoc().GetTableIsCali())
		{
			if(!CogTableMapPoint(0,label,Coord(m_lTablePosX,pos),crd))
			{
				SetLampStatus(CControl::ERR);
				ChannelOutput(OCOMMONALARM ,TRUE);
				
				AfxMessageBox("ƽ̨�ƶ�����ӳ����������ȷ�ϣ�");
				
				SetLampStatus(CControl::ORDER);
				ChannelOutput(OCOMMONALARM ,FALSE);
				return 4;
			}			
		}
	}

	if((ulAxis==AXISTABX)||(ulAxis==AXISTABY))
	{
		if(!GetDoc().GetTableIsCali())
		{
#ifdef USEDMSYSTEM																//20200414
			if (!GetXYMotion().MoveTo(crd.x,crd.y))
			{
				AfxMessageBox("AXISTAB Motion Fault!");
				return 4;
			}
#else
			if (GetMotion().MoveTo(AXISTABX,crd.x,
				GetDoc().GetMoveAcc(AXISTABX),GetDoc().GetMoveDec(AXISTABX),
				GetDoc().GetMoveMaxSpeed(AXISTABX))!=DMCNOERROR)
			{
				AfxMessageBox("AXISTABX Motion Fault!");
				return 4;
			}
			
			if (GetMotion().MoveTo(AXISTABY,crd.y,
				GetDoc().GetMoveAcc(AXISTABY),GetDoc().GetMoveDec(AXISTABY),
				GetDoc().GetMoveMaxSpeed(AXISTABY))!=DMCNOERROR)
			{
				AfxMessageBox("AXISTABY Motion Fault!");
				return 4;
			}
#endif
		}
		else
		{
#ifdef USEDMSYSTEM																//20200414
			if (!GetXYMotion().MoveTo(ulAxis,pos,
				GetDoc().GetMoveAcc(ulAxis),GetDoc().GetMoveDec(ulAxis),
				GetDoc().GetMoveMaxSpeed(ulAxis)))
			{
				str.Format("Axis %d Motion Fault!",ulAxis);
				AfxMessageBox(str);
				return 4;
			}
#else
			if (GetMotion().MoveTo(ulAxis,pos,
				GetDoc().GetMoveAcc(ulAxis),GetDoc().GetMoveDec(ulAxis),
				GetDoc().GetMoveMaxSpeed(ulAxis))!=DMCNOERROR)
			{
				str.Format("Axis %d Motion Fault!",ulAxis);
				AfxMessageBox(str);
				return 4;
			}
#endif
		}
	}
	else
	{
		if (GetMotion().MoveTo(ulAxis,pos,
			GetDoc().GetMoveAcc(ulAxis),GetDoc().GetMoveDec(ulAxis),
			GetDoc().GetMoveMaxSpeed(ulAxis))!=DMCNOERROR)
		{
			str.Format("Axis %d Motion Fault!",ulAxis);
			AfxMessageBox(str);
			return 4;
		}
	}

	if(ulAxis==AXISTABX)
		m_lTablePosX=pos;
	if(ulAxis==AXISTABY)
		m_lTablePosY=pos;

#else	//TABLE2DCALI

	if(ulAxis==AXISTABX)
	{
#ifndef NO_SOFT_LIMIT
		if(pos>GetDoc().GetFORWARDX()||pos<GetDoc().GetREVERSEX())
		{
			strncpy(ez,GetLang().GetWarningText(41017),256);
			AfxMessageBox(ez);//"ƽ̨������Ч�˶���Χ����ȷ������!"
			return 2;
		}
#endif
		GetDoc().SetPos(AXISTABX,pos);
		pos+=AxisCompensate(AXISTABX,pos,0);
	}
	
	if(ulAxis==AXISTABY)
	{
#ifndef NO_SOFT_LIMIT
		if(pos>GetDoc().GetFORWARDY()||pos<GetDoc().GetREVERSEY())
		{
			strncpy(ez,GetLang().GetWarningText(41017),256);
			AfxMessageBox(ez);//"ƽ̨������Ч�˶���Χ����ȷ������!"
			return 2;
		}
#endif	
		GetDoc().SetPos(AXISTABY,pos);		
		pos+=AxisCompensate(AXISTABY,pos,0);
	}

	if((ulAxis==AXISTABX)||(ulAxis==AXISTABY))
	{
#ifdef USEDMSYSTEM
#ifdef ACSDMSYSTEM
		if (!GetXYMotion().MoveTo(ulAxis,pos,										//20190507 ����
			GetDoc().GetMoveAcc(ulAxis),GetDoc().GetMoveDec(ulAxis),
			GetDoc().GetMoveMaxSpeed(ulAxis)))
#endif
#ifdef AEROTECHDMSYSTEM
		if (!GetXYMotion().MoveTo(ulAxis,(double)pos,(double)GetDoc().GetMoveAcc(ulAxis),	//20200818
			(double)GetDoc().GetMoveDec(ulAxis),(double)GetDoc().GetMoveMaxSpeed(ulAxis)))
#endif
		{
			str.Format("Axis %d Motion Fault!",ulAxis);
			AfxMessageBox(str);
			return 4;
		}
#else
		if (GetMotion().MoveTo(ulAxis,pos,
			GetDoc().GetMoveAcc(ulAxis),GetDoc().GetMoveDec(ulAxis),
			GetDoc().GetMoveMaxSpeed(ulAxis))!=DMCNOERROR)
		{
			str.Format("Axis %d Motion Fault!",ulAxis);
			AfxMessageBox(str);
			return 4;
		}
#endif
	}
	else
	{
		if (GetMotion().MoveTo(ulAxis,pos,
			GetDoc().GetMoveAcc(ulAxis),GetDoc().GetMoveDec(ulAxis),
			GetDoc().GetMoveMaxSpeed(ulAxis))!=DMCNOERROR)
		{
			str.Format("Axis %d Motion Fault!",ulAxis);
			AfxMessageBox(str);
			return 4;
		}
	}

#endif
	
	return 0;
}

long CControl::MoveTo(const Coord &crd)
{
	Coord actualPos;
	char ez[256]={""};
	CString str="";															//20200417
	long result;

//�жϻ�������״̬
	if(!GetDoc().GetMotorState())										
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬��������ز���!"
		return 1;
	}
/*	
	if(GetMotion().GetMationSH(AXISTABX))
	{
		strncpy(ez,GetLang().GetWarningText(41019),256);
		AfxMessageBox(ez);//"X����ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	if(GetMotion().GetMationSH(AXISTABY))
	{
		strncpy(ez,GetLang().GetWarningText(41020),256);
		AfxMessageBox(ez);//"Y����ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
*/
//#ifndef NOLANDULSYSTEM
	if(GetDoc().GetLAndULSystem())
	{	
		if(!GetDoc().GetUse9112())
		{
//#ifdef UNLOADISOK
			if(GetDoc().GetUnloadIsOK())
			{
				if(!QueryCOMInput(68))				//����������Ƿ��ڰ�ȫλ�ã�ͬʱˢ��������״̬	68�������ϰ�ȫλ�ñ���
				{
					AfxMessageBox("������λ�ò���ȫ���޷��ƶ�ƽ̨����ȷ��!");
					return 3;
				}
			}
//#else
			else
			{
				if((GetDoc().GetProcessState()==CControl::AUTOPROC)&&(GetControl().GetRunState()==CControl::RUN))		//����������ʱ
					QueryCOMInput(28);				//�Զ������ϼӹ�ʱ��ÿ��ƽ̨�ƶ����������ϵ�״̬����һ����ѯ 28����е�ִ��󱨾�
			}
//#endif
			
//			PeekRunState();							//20190723 ��������ͣ ������
		}
	}
//#endif

#ifndef NO_SOFT_LIMIT
	if(crd.x>GetDoc().GetFORWARDX()||crd.x<GetDoc().GetREVERSEX()||crd.y>GetDoc().GetFORWARDY()||crd.y<GetDoc().GetREVERSEY())
	{
		strncpy(ez,GetLang().GetWarningText(41017),256);
		AfxMessageBox(ez);//"ƽ̨������Ч�˶���Χ����ȷ������!"
		return 2;
	}
#endif
	
#ifdef TABLE2DCALI
	int label=0;
//	if(crd.y<(DIVIDINGLINE))												//20200414
//		label=1;

	if(!GetDoc().GetTableIsCali())
	{
		if(!CogTableMapPoint(0,label,crd,actualPos))
		{
			SetLampStatus(CControl::ERR);
			ChannelOutput(OCOMMONALARM ,TRUE);
			
			AfxMessageBox("ƽ̨�ƶ�����ӳ����������ȷ�ϣ�");
			
			SetLampStatus(CControl::ORDER);
			ChannelOutput(OCOMMONALARM ,FALSE);
			return 4;
		}
	}
	else
		actualPos=crd;

#ifdef USEDMSYSTEM																//20200414
	if (!GetXYMotion().MoveTo(actualPos.x,actualPos.y))
	{
		AfxMessageBox("AXISTAB Motion Fault!");
		return 4;
	}
#else
/*																				//20200417
	if (GetMotion().MoveTo(AXISTABX,actualPos.x,
		GetDoc().GetMoveAcc(AXISTABX),GetDoc().GetMoveDec(AXISTABX),
		GetDoc().GetMoveMaxSpeed(AXISTABX))!=DMCNOERROR)
	{
		AfxMessageBox("AXISTABX Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISTABY,actualPos.y,
		GetDoc().GetMoveAcc(AXISTABY),GetDoc().GetMoveDec(AXISTABY),
		GetDoc().GetMoveMaxSpeed(AXISTABY))!=DMCNOERROR)
	{
		AfxMessageBox("AXISTABY Motion Fault!");
		return 4;
	}
*/
	result=GetMotion().MoveTo(AXISTABX,actualPos.x,GetDoc().GetMoveAcc(AXISTABX),GetDoc().GetMoveDec(AXISTABX),GetDoc().GetMoveMaxSpeed(AXISTABX));
	if (result!=DMCNOERROR)
	{
		str.Format("AXISTABX Motion Fault! Error code: %d",result);
		AfxMessageBox(str);
		return 4;
	}
	
	result=GetMotion().MoveTo(AXISTABY,actualPos.y,GetDoc().GetMoveAcc(AXISTABY),GetDoc().GetMoveDec(AXISTABY),GetDoc().GetMoveMaxSpeed(AXISTABY));
	if (result!=DMCNOERROR)
	{
		str.Format("AXISTABY Motion Fault! Error code: %d",result);
		AfxMessageBox(str);
		return 4;
	}
#endif

	m_lTablePosX=crd.x;
	m_lTablePosY=crd.y;

#else	//TABLE2DCALI

	GetDoc().SetPos(AXISTABX,crd.x);
	GetDoc().SetPos(AXISTABY,crd.y);

#ifdef USEDMSYSTEM
	double acc[2],dec[2],speed[2];
	acc[0]=(double)GetDoc().GetMoveAcc(AXISTABX);
	acc[1]=(double)GetDoc().GetMoveAcc(AXISTABY);
	dec[0]=(double)GetDoc().GetMoveDec(AXISTABX);
	dec[1]=(double)GetDoc().GetMoveDec(AXISTABY);
	speed[0]=(double)GetDoc().GetMoveMaxSpeed(AXISTABX);
	speed[1]=(double)GetDoc().GetMoveMaxSpeed(AXISTABY);

#ifdef ACSDMSYSTEM
	if (!GetXYMotion().MoveTo(crd.x+AxisCompensate(AXISTABX,crd.x,0),crd.y+AxisCompensate(AXISTABY,crd.y,0)))	//20190507 ����
#endif
#ifdef AEROTECHDMSYSTEM
	if (!GetXYMotion().MoveTo((double)(crd.x+AxisCompensate(AXISTABX,crd.x,0)),(double)(crd.y+AxisCompensate(AXISTABY,crd.y,0)),acc,dec,speed))	//20200818
#endif
	{
		AfxMessageBox("AXISTAB Motion Fault!");
		return 4;
	}
#else
/*																				//20200417
	if (GetMotion().MoveTo(AXISTABX,crd.x+AxisCompensate(AXISTABX,crd.x,0),
		GetDoc().GetMoveAcc(AXISTABX),GetDoc().GetMoveDec(AXISTABX),
		GetDoc().GetMoveMaxSpeed(AXISTABX))!=DMCNOERROR)
	{
		AfxMessageBox("AXISTABX Motion Fault!");
		return 4;
	}

	if (GetMotion().MoveTo(AXISTABY,crd.y+AxisCompensate(AXISTABY,crd.y,0),
		GetDoc().GetMoveAcc(AXISTABY),GetDoc().GetMoveDec(AXISTABY),
		GetDoc().GetMoveMaxSpeed(AXISTABY))!=DMCNOERROR)
	{
		AfxMessageBox("AXISTABY Motion Fault!");
		return 4;
	}
*/
	result=GetMotion().MoveTo(AXISTABX,crd.x+AxisCompensate(AXISTABX,crd.x,0),GetDoc().GetMoveAcc(AXISTABX),GetDoc().GetMoveDec(AXISTABX),GetDoc().GetMoveMaxSpeed(AXISTABX));
	if (result!=DMCNOERROR)
	{
		str.Format("AXISTABX Motion Fault! Error code: %d",result);
		AfxMessageBox(str);
		return 4;
	}
	
	result=GetMotion().MoveTo(AXISTABY,crd.y+AxisCompensate(AXISTABY,crd.y,0),GetDoc().GetMoveAcc(AXISTABY),GetDoc().GetMoveDec(AXISTABY),GetDoc().GetMoveMaxSpeed(AXISTABY));
	if (result!=DMCNOERROR)
	{
		str.Format("AXISTABY Motion Fault! Error code: %d",result);
		AfxMessageBox(str);
		return 4;
	}
#endif

#endif
	
	return  0;	
}

long CControl::MoveTo(long aptNo)
{
	char ez[256]={""};
	CString str="";
	long error=0;
    long posBET1=0,posBET2=0;

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"����δ������㣬������������!"
		return 1;
	}

	if(GetMotion().GetMationSH(AXISAPT))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}

	if(GetMotion().GetMationSH(AXISBETPRI))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if(GetMotion().GetMationSH(AXISBETSUB))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}

#ifdef DOUBLEBET
	if(GetMotion().GetMationSH(AXISAPT2))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}

	if(GetMotion().GetMationSH(AXISBETPRI2))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}
	
	if(GetMotion().GetMationSH(AXISBETSUB2))
	{
		strncpy(ez,GetLang().GetWarningText(41018),256);
		AfxMessageBox(ez);//"���ʹ�ܴ�������ȷ�Ϻ����»���"
		GetDoc().SetFault(true);
		return 3;
	}

	if (GetMotion().MoveTo(AXISBETPRI,GetDoc().GetBETOffset(GetDoc().GetFactualAperture(aptNo)-1),
		GetDoc().GetMoveAcc(AXISBETPRI),GetDoc().GetMoveDec(AXISBETPRI),
		GetDoc().GetMoveMaxSpeed(AXISBETPRI))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETPRI Motion Fault!");
		return 4;
	}
		
	if (GetMotion().MoveTo(AXISBETSUB,GetControl().GetBetTwoPos(GetDoc().GetBETOffset(GetDoc().GetFactualAperture(aptNo)-1)),
		GetDoc().GetMoveAcc(AXISBETSUB),GetDoc().GetMoveDec(AXISBETSUB),
		GetDoc().GetMoveMaxSpeed(AXISBETSUB))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETSUB Motion Fault!");
		return 4;
	}
		
	if (GetMotion().MoveTo(AXISBETPRI2,GetDoc().GetBETOffset2(GetDoc().GetFactualAperture2(aptNo)-1),
		GetDoc().GetMoveAcc(AXISBETPRI),GetDoc().GetMoveDec(AXISBETPRI),
		GetDoc().GetMoveMaxSpeed(AXISBETPRI))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETPRI2 Motion Fault!");
		return 4;
	}
		
	if (GetMotion().MoveTo(AXISBETSUB2,GetControl().GetBetTwoPos(GetDoc().GetBETOffset2(GetDoc().GetFactualAperture2(aptNo)-1)),
		GetDoc().GetMoveAcc(AXISBETSUB),GetDoc().GetMoveDec(AXISBETSUB),
		GetDoc().GetMoveMaxSpeed(AXISBETSUB))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETSUB2 Motion Fault!");
		return 4;
	}

 	if (GetDoc().GetCurAptNo()==aptNo)					//�����Ȧ��һ������������Ȧ�˶�������жϺ͵�ǰ��Ȧ���趨
	{
		WaitAxisStop(AXISBETPRI);
		WaitAxisStop(AXISBETSUB);
		WaitAxisStop(AXISBETPRI2);
	    WaitAxisStop(AXISBETSUB2);
		return 0;
	}

	posBET1=-(GetDoc().GetFactualAperture(aptNo)-1)*APTCIRCLEPLS;
	if (GetMotion().MoveTo(AXISAPT,posBET1,
		GetDoc().GetMoveAcc(AXISAPT),GetDoc().GetMoveDec(AXISAPT),
		GetDoc().GetMoveMaxSpeed(AXISAPT))!=DMCNOERROR)
	{
		AfxMessageBox("AXISAPT Motion Fault!");
		return 4;
	}

	posBET2=-(GetDoc().GetFactualAperture2(aptNo)-1)*APTCIRCLEPLS;
	if (GetMotion().MoveTo(AXISAPT2,posBET2,
		GetDoc().GetMoveAcc(AXISAPT),GetDoc().GetMoveDec(AXISAPT),
		GetDoc().GetMoveMaxSpeed(AXISAPT))!=DMCNOERROR)
	{
		AfxMessageBox("AXISAPT2 Motion Fault!");
		return 4;
	}
	
	WaitAxisStop(AXISAPT);
	WaitAxisStop(AXISBETPRI);
	WaitAxisStop(AXISBETSUB);
	WaitAxisStop(AXISAPT2);
	WaitAxisStop(AXISBETPRI2);
	WaitAxisStop(AXISBETSUB2);

	if (abs(posBET1-GetPos(AXISAPT))>3)				//+/-3pulse (+/-3*2*PI*55000/50000=21um)	//20160823
	{
		error=posBET1-GetPos(AXISAPT);
		str.Format("AXISAPT Move error %d is large!",error);
		AfxMessageBox(str);
//		return  5;
	}

	if (abs(posBET2-GetPos(AXISAPT2))>3)
	{
		error=posBET2-GetPos(AXISAPT2);
		str.Format("AXISAPT2 Move error %d is large!",error);
		AfxMessageBox(str);
//		return  5;
	}

#else//ʹ�õ�BET
	if (GetMotion().MoveTo(AXISBETPRI,GetDoc().GetBETOffset(GetDoc().GetFactualAperture(aptNo)-1),
		GetDoc().GetMoveAcc(AXISBETPRI),GetDoc().GetMoveDec(AXISBETPRI),
		GetDoc().GetMoveMaxSpeed(AXISBETPRI))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETPRI Motion Fault!");
		return 4;
	}
		
	if (GetMotion().MoveTo(AXISBETSUB,GetControl().GetBetTwoPos(GetDoc().GetBETOffset(GetDoc().GetFactualAperture(aptNo)-1)),
		GetDoc().GetMoveAcc(AXISBETSUB),GetDoc().GetMoveDec(AXISBETSUB),
		GetDoc().GetMoveMaxSpeed(AXISBETSUB))!=DMCNOERROR)
	{
		AfxMessageBox("AXISBETSUB Motion Fault!");
		return 4;
	}

	if (GetDoc().GetCurAptNo()==aptNo)					//�����Ȧ��һ������������Ȧ�˶�������жϺ͵�ǰ��Ȧ���趨
	{
		WaitAxisStop(AXISBETPRI);
		WaitAxisStop(AXISBETSUB);
		return 0;
	}

	posBET1=-(GetDoc().GetFactualAperture(aptNo)-1)*APTCIRCLEPLS;
	if (GetMotion().MoveTo(AXISAPT,posBET1,
		GetDoc().GetMoveAcc(AXISAPT),GetDoc().GetMoveDec(AXISAPT),
		GetDoc().GetMoveMaxSpeed(AXISAPT))!=DMCNOERROR)
	{
		AfxMessageBox("AXISAPT Motion Fault!");
		return 4;
	}
	
	WaitAxisStop(AXISAPT);
	WaitAxisStop(AXISBETPRI);
	WaitAxisStop(AXISBETSUB);

	if (abs(posBET1-GetPos(AXISAPT))>3)
	{
		error=posBET1-GetPos(AXISAPT);
		str.Format("AXISAPT Move error %d is large!",error);
		AfxMessageBox(str);
//		return  5;
	}

#endif
	
	GetDoc().SetCurAptNo(aptNo);
	return 0;
}

BOOL CControl::WaitAxisStop(U32 ulAxis) const
{
	if (ulAxis==AXISTAB)
	{
#ifdef USEDMSYSTEM
		if(!GetXYMotion().WaitStop(AXISTABX))
			return false;

		if(!GetXYMotion().WaitStop(AXISTABY))
			return false;

		if(!GetDoc().GetNewDelay())
			Delay(GetDoc().GetTableDelay());
#else
		if(!GetMotion().WaitStop(AXISTABX))
			return false;

		if(!GetMotion().WaitStop(AXISTABY))
			return false;

		if(GetDoc().GetNewDelay())
			return GetMotion().WaitXYStop(32,25);		//32�Σ�25��
		else
			Delay(GetDoc().GetTableDelay());
#endif
	}
	else
	{
		if(!GetMotion().WaitStop(ulAxis))
			return false;
	}

	return true;
}

long CControl::GetPos(U32 ulAxisNo) const
{
#ifdef TABLE2DCALI
	if(ulAxisNo==AXISTABX)
		return m_lTablePosX;
	else if(ulAxisNo==AXISTABY)		
		return m_lTablePosY;		
	else
		return GetMotion().GetPos(ulAxisNo);
#else
	long pos;

	if(ulAxisNo==AXISTABX)
	{
#ifdef USEDMSYSTEM													//20190507
//		pos=GetXYMotion().GetPos(AXISTABX);
#ifdef AEROTECHDMSYSTEM												//20200818
		pos=GetXYMotion().GetRPos(AXISTABX);
#else
		pos=GetXYMotion().GetPos(AXISTABX);
#endif
#else
		pos=GetMotion().GetPos(AXISTABX);
#endif
		return pos-AxisCompensate(AXISTABX,pos,0);
	}
	else if(ulAxisNo==AXISTABY)
	{
#ifdef USEDMSYSTEM													//20190507
//		pos=GetXYMotion().GetPos(AXISTABY);
#ifdef AEROTECHDMSYSTEM												//20200818
		pos=GetXYMotion().GetRPos(AXISTABY);
#else
		pos=GetXYMotion().GetPos(AXISTABY);
#endif
#else
		pos=GetMotion().GetPos(AXISTABY);
#endif
		return pos-AxisCompensate(AXISTABY,pos,0);		
	}
	else
		return GetMotion().GetPos(ulAxisNo);
#endif
}

long CControl::GetCurDrillSubAreaNo()const
{
	return m_lCurDrillSubAreaNo;
}

void CControl::SetRunState(RUNSTATUS rs)
{
	m_rsCurRunState = rs;
}

long CControl::GetRunState()const
{
	return (long)m_rsCurRunState ;
}

long CControl::HomeAll()
{
	char ez[256]={""};
	time_t start_time, end_time;

	GetDoc().SetMotorState(false);
	GetDoc().SetMachinePowerState(false);

//�Զ����ʱ������У����׼�������ȷ��̨�����ް�					//20190725
	if(GetDoc().GetThickingType())
	{
		ChannelOutput(OFANPOWERON,IO_ON);							//�򿪷��

		if(!QueryTableStatus(HeadBoth,1))							//�ж�̨�����Ƿ��ް�
		{
			ResetTableStatus();
			return false;
		}

		ChannelOutput(OFANPOWERON,IO_OFF);							//�رշ��
	}

#ifndef USEDMSYSTEM													//20190507 ����
	if(!GetControl().QueryIOBit(ISERVOALARMX))
	{
		strncpy(ez,GetLang().GetWarningText(41026),256);
		AfxMessageBox(ez);//"ƽ̨X����ŷ�������������ٻ���"
		return FALSE;
	}
	if(!GetControl().QueryIOBit(ISERVOALARMY))
	{
		strncpy(ez,GetLang().GetWarningText(41027),256);
		AfxMessageBox(ez);//"ƽ̨Y����ŷ�������������ٻ���"
		return FALSE;
	}
#endif

	if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)		//�Զ�
	{
		if(GetDoc().GetUse9112())
		{
			GetControl().ChannelOutput(OHOMEALL , IO_ON);
			Delay(500);
			GetControl().ChannelOutput(OHOMEALL , IO_OFF);
			
			start_time = time( NULL );
			
			while(QueryIOBit(IHOMEALLOK))
			{
				end_time = time( NULL );
				if( difftime(end_time, start_time)>20 )
				{
					strncpy(ez,GetLang().GetWarningText(42010),256);
					AfxMessageBox(ez);//"�����ϻ���ʧ��!"
					return FALSE;
				}
			}
		}
		else
		{
			SetCOMOutput(8);									//��е�ֻ���  o����8��	i����8
			
			start_time = time( NULL );
			
			while(QueryCOMInput(16))							//��е�ֻ�����ɣ� i����16��	i����16
			{
				end_time = time( NULL );
				if( difftime(end_time, start_time)>20 )
				{
					strncpy(ez,GetLang().GetWarningText(42010),256);
					AfxMessageBox(ez);//"�����ϻ���ʧ��!"
					return FALSE;
				}
			}	
		}	
	}

	GetMotion().Home( AXISLEFTZ	);	
	GetMotion().Home( AXISRIGHTZ);
	Delay(500);
	
	if (!GetMotion().WaitStopWhenProgramming( AXISLEFTZ))
		return FALSE;	
	if (!GetMotion().WaitStopWhenProgramming( AXISRIGHTZ))
		return FALSE;	

#ifdef USEDMSYSTEM
	GetXYMotion().Home(AXISTABY);
	GetDoc().SetPos(AXISTABY,0);//ly add 20110928
	Delay(500); 		
	GetXYMotion().Home(AXISTABX);
	GetDoc().SetPos(AXISTABX,0);//ly add 20110928
	Delay(500); 

	GetXYMotion().WaitStopWhenProgramming( AXISTABY);
	GetXYMotion().WaitStopWhenProgramming( AXISTABX);
#else
	GetMotion().Home(AXISTABY);
	GetDoc().SetPos(AXISTABY,0);//ly add 20110928
	Delay(500); 		
	GetMotion().Home(AXISTABX);
	GetDoc().SetPos(AXISTABX,0);//ly add 20110928
	Delay(500); 

	GetMotion().WaitStopWhenProgramming( AXISTABY);
	GetMotion().WaitStopWhenProgramming( AXISTABX);
#endif	
	
	m_lTablePosX=0;					//20180417
	m_lTablePosY=0;

	GetControl().HomeAPT();
	GetControl().HomeBET();

	GetDoc().SetMotorState(true);
	GetDoc().SetMachinePowerState(true);

//�Զ����ʱ�������������һ�λ�׼У��							//20190725
	if(GetDoc().GetThickingType())
	{
		long lThickZero[2]={0,0};;
		
		if(!TestThicknessAL(lThickZero,HeadBoth,Coord(0,0)))
		{
			AfxMessageBox("��׼���������쳣���������������ȷ�ϣ�");

			GetDoc().SetMotorState(false);
			GetDoc().SetMachinePowerState(false);
			return false;
		}
		
		GetDoc().SetThicknessZero(lThickZero[0],HeadLeft);
		GetDoc().SetThicknessZero(lThickZero[1],HeadRight);	
	}

	return TRUE;
}
/*
BOOL CControl::PeekRunState(BOOL onlyOne)
{
	DoEvent();
	while(1)
	{
		DoEvent();
		if(!GetDoc().GetMotorState())
		{
			return DealFault();
		}
		if(m_rsCurRunState == PAUSE)
		{
			Sleep(50);
		}
		else if(m_rsCurRunState == MANU)
		{
			Sleep(50);
		}
		else if(m_rsCurRunState == END )
		{
			return FALSE;
		}
		else if(GetDoc().GetFault())
		{
			return DealFault();
		}
		else if(!GetDoc().GetFaultRun()&&(GetDoc().GetWarner()))
		{
//			if(onlyOne)
//				return DealFault();
//			else
//				return DealWarner();

			return DealWarner();
		}
		else
			return TRUE;
	}
}

BOOL CControl::PeekRunState()									//20190604
{
	m_PauseTimeInSec=0.0;										//20190612

	while(1)
	{
		if(m_rsCurRunState == PAUSE)
//			Sleep(50);											//20190612
		{
			Sleep(50);
			m_PauseTimeInSec+=0.05;
		}
		else if(m_rsCurRunState == OPERATEPAUSE)				//20190722 ����
		{
			Sleep(50);
			m_PauseTimeInSec+=0.05;
		}
		else if(m_rsCurRunState == MANU)
			Sleep(50);
		else if(m_rsCurRunState == END )
			return FALSE;
		else if(GetDoc().GetFault())
			return DealFault();
//		else if(!GetDoc().GetFaultRun()&&(GetDoc().GetWarner()))	//20190718 �޸�
//			return DealWarner();
		else if((GetDoc().GetProcessState()==CControl::AUTOPROC)&&(!GetDoc().GetFaultRun()))
		{
			if(!GetDoc().GetUse9112())
			{
				if((QueryCOMInput(24,1)==1)||(QueryCOMInput(28,1)==1))
				{
					GetDoc().SetLastWarningNo(27);					// "�����ϻ�е�ֱ���"
					return DealWarner();
				}
				
				if(QueryCOMInput(26,1)==1)
				{
					GetDoc().SetLastWarningNo(37);					// "NG�ϲ������������"
					return DealWarner();
				}
			}
			
			return TRUE;
		}
		else
			return TRUE;
	}
}
*/
BOOL CControl::PeekRunState()									//20190604		//20190723 �޸�
{
	m_PauseTimeInSec=0.0;										//20190612

	while(1)
	{
		if((m_rsCurRunState==PAUSE)||(m_rsCurRunState==OPERATEPAUSE)||(m_rsCurRunState==OPERATEWITHHANDPAUSE))	//20190722 ����
		{
			Sleep(50);
			m_PauseTimeInSec+=0.05;
		}
		else if(m_rsCurRunState==MANU)
			Sleep(50);
		else if(m_rsCurRunState==END)
			return false;
		else if(GetDoc().GetFault())
			return DealFault();
		else if(m_rsCurRunState==OPERATE)
			return true;
		else if(m_rsCurRunState==OPERATEWITHHAND)
			return PeekHandState();
		else if((GetDoc().GetProcessState()==CControl::AUTOPROC)&&(!GetDoc().GetFaultRun()))	//RUN: �Զ�������
		{
			if(!PeekHandState())
				return DealWarner();
			else
				return true;
		}
		else																					//RUN:�ֹ�������
			return true;
	}
}

BOOL CControl::PeekHandState()										//20190723 ����
{
	if(GetDoc().GetUse9112())
	{
		if(QueryIOBit(IALARM)==0)
		{
			GetDoc().SetLastWarningNo(27);					// "�����ϻ�е�ֱ���"
			return false;
		}
		
		if(QueryIOBit(IONGFULLALARM)==0)
		{
			GetDoc().SetLastWarningNo(37);					// "NG�ϲ������������"
			return false;
		}
	}
	else
	{
		if((QueryCOMInput(24,1)==1)||(QueryCOMInput(28,1)==1))
		{
			GetDoc().SetLastWarningNo(27);					// "�����ϻ�е�ֱ���"
			return false;
		}
		
		if(QueryCOMInput(26,1)==1)
		{
			GetDoc().SetLastWarningNo(37);					// "NG�ϲ������������"
			return false;
		}
	}
	
	return true;
}

BOOL CControl::GlovaCalibrateOffset(const Coord3D &crdLaserPos, Coord3D &CCDOffset,int nHead,bool &bTestOk,int ftime)
{	
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	char ez[256]={""};
	static Coord crdOff(0,0);

//��ȡУ�����ƽ̨��ʼλ��
	if(!GetDoc().GetAutoCalibrateOrgPosOffset(crdOff, nHead))
	{
		if(HeadLeft==nHead)
			GetDoc().SetLastWarningNo(87);						//"����У������������������µ�У����!"

		if(HeadRight==nHead)
			GetDoc().SetLastWarningNo(88);						//"����У������������������µ�У����!"

		return false;
	}

	crdOff.x-=5000;

//����У����У������
//	long lTimes=GetDoc().GetOrgTimes(nHead);
//	GetDoc().SetOrgTimes(nHead,lTimes++);

//��ȡĿ��ʶ��ʱ��ƽ̨��������
	HoleCoordV crdV;
	CArray<Coord, Coord> dev;
	Coord crdCCDPos=Coord(0,0);
	Coord crdLASERPos=Coord(0,0);
	Coord CCDOffsetNow;
	Coord tempCrd[3];
//	Coord sumCrd=Coord(0,0);

	CCDOffsetNow.x=CCDOffset.x;
	CCDOffsetNow.y=CCDOffset.y;

	if(GetDoc().GetTechnicType())
		MoveTo(GetDoc().GetLongPathAdjustAperture());	
	else
		MoveTo(GetDoc().GetAdjustAperture());

	for(int TestTime=0;TestTime<3;TestTime++)
	{
		crdV.clear();

		crdOff.x+=5000;
		crdCCDPos.x=crdLaserPos.x-crdOff.x+CCDOffsetNow.x;
		crdCCDPos.y=crdLaserPos.y-crdOff.y+CCDOffsetNow.y;
		crdLASERPos.x=crdLaserPos.x-crdOff.x;
		crdLASERPos.y=crdLaserPos.y-crdOff.y;

		crdV.push_back(crdCCDPos);

		if(TargetFindInCali(nHead,1,crdV,dev,0))
		{
			if(ftime>=3)
			{
				GetDoc().SetLastWarningNo(95);	//"У���������쳣��"
//				strncpy(ez,GetLang().GetWarningText(21044),256);
//				AfxMessageBox(ez);					//"У���������쳣�㣬�޷�����У���������!"
//				GetDoc().WriteCaliTimes();
			}

			bTestOk = false;
			return true;
		}
		
		MoveTo(crdLASERPos);

		if(nHead==HeadLeft)
		{
			MoveTo(AXISLEFTZ,crdLaserPos.z);
			WaitAxisStop(AXISLEFTZ);
		}
		else
		{
			MoveTo(AXISRIGHTZ,crdLaserPos.z);
			WaitAxisStop(AXISRIGHTZ);
		}
		
		WaitAxisStop(AXISTAB);
		Delay(500);

//#ifdef SMCDLL
#if (defined SMCDLL)||(defined SMCDMDLL)
		if(TestTime==0)															//20171106
		{
			MatrixProcess(nHead,0,0,STYPE,GetDoc().GetDefineMatrixRange(),1);		
			Delay(500);
		}
#endif
		MatrixProcess(nHead,GetDoc().GetGlvAdjPlsRelease(),0,STYPE,GetDoc().GetDefineMatrixRange(),1);

		dev.RemoveAll();

		if(!TargetFindInCali(nHead,1,crdV,dev,1))
			return false;

		tempCrd[TestTime]=dev.GetAt(0);
//		sumCrd+=tempCrd[TestTime];
//		sumCrd=tempCrd[TestTime];

//������õľ���ƫ��ֵ
		CCDOffsetNow.x+=dev.GetAt(0).x;
		CCDOffsetNow.y+=dev.GetAt(0).y;

//ȡ����õ�������ƫ��ֵ
		if(TestTime>0)
		{
			Coord crd;
			long dis1=sqrt(pow(tempCrd[TestTime-1].x,2)+pow(tempCrd[TestTime-1].y,2));
			long dis2=sqrt(pow(tempCrd[TestTime].x,2)+pow(tempCrd[TestTime].y,2));

			if(dis1>dis2)
			{
				crd=tempCrd[TestTime];
				tempCrd[TestTime]=tempCrd[TestTime-1];
				tempCrd[TestTime-1]=crd;
			}
		}
	}
	
//	GetDoc().WriteCaliTimes();
//	LightTurnOff(); 
	
//	CCDOffset.x+=int(sumCrd.x/3);
//	CCDOffset.y+=int(sumCrd.y/3);

//������õ�������ƫ��ֵ
	CCDOffset.x+=tempCrd[2].x;
	CCDOffset.y+=tempCrd[2].y;

	if(!IsPassCrd(tempCrd,3)) 
		bTestOk = false;
	
	return true;
}

void CControl::SetLampStatus(LAMPSTATUS lamp) //const
{
	ASSERT(lamp==ORDER||lamp==ERR||lamp==WARN);
	if(lamp==ORDER)
	{
		ChannelOutput(OLAMPGREENON,IO_ON);
		ChannelOutput(OLAMPREDON,IO_OFF);
	}
	else if(lamp==ERR)
	{
		ChannelOutput(OLAMPREDON,IO_ON);
		ChannelOutput(OLAMPGREENON,IO_OFF);
	}
	else
	{
		ChannelOutput(OLAMPREDON,IO_OFF);
		ChannelOutput(OLAMPGREENON,IO_OFF);
	}

#ifdef USELOG
	if ((m_LampStatus!=lamp)&&(GetDoc().GetSysInfoDBMode()==1))						//20160901
	{
		if (lamp==WARN)
			GetLog().AppendSNLightStatusTable(1,COleDateTime::GetCurrentTime());
		else if (lamp==ORDER)
			GetLog().AppendSNLightStatusTable(2,COleDateTime::GetCurrentTime());
		else if (lamp==ERR)
			GetLog().AppendSNLightStatusTable(3,COleDateTime::GetCurrentTime());
		
		m_LampStatus=lamp;
	}
#endif
}

int CControl::GetLampStatus()const
{
	return (int)m_LampStatus;
}

BOOL CControl::GlovaAutoCalibrate(const Coord3D &crdLaserPos, Coord3D &CCDOffset,int nHead,bool &bTestOk,int ftime,bool isForTest)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	char ez[256]={""};
	static Coord crdOff(0,0);
	bool result=false;

//��ȡУ�����ƽ̨��ʼλ��
	if(isForTest)
		result=GetDoc().GetAutoCalibrateFieldPosOffsetForAccuracyTest(GetDoc().GetSLBitPerMM(),crdOff, nHead,0);
	else
		result=GetDoc().GetAutoCalibrateFieldPosOffset(crdOff, nHead);

	if(!result)
	{
		if(HeadLeft==nHead)
			GetDoc().SetLastWarningNo(87);						//"����У������������������µ�У����!"

		if(HeadRight==nHead)
			GetDoc().SetLastWarningNo(88);						//"����У������������������µ�У����!"

		return false;
	}

//����У����У������
//	long lTimes=GetDoc().GetPatternTimes(nHead);
//	GetDoc().SetPatternTimes(nHead,lTimes++);

//��У�������
	double iUseCalibrate=(double)(GetDoc().GetSLBitPerMM()/1000.0);
	CString correXionPath ="";
	CString CorDatPath="";
	CString DevDatPath="";
	CString CurPath="";

	if(GetDoc().GetTechnicType())
		CurPath= "LPathC\\";
	else
		CurPath= "SPathC\\";

//��ȡĿ��ʶ��ʱ��ƽ̨��������
	HoleCoordV crdTestV,crdCaliV;
	CArray<Coord, Coord> Dev;
	Coord crdCCDPos=Coord(0,0);
	Coord crdLASERPos=Coord(0,0);
	
	crdTestV.clear();
	crdCaliV.clear();

	if(GetDoc().GetTechnicType())
		MoveTo(GetDoc().GetLongPathAdjustAperture());	
	else
		MoveTo(GetDoc().GetAdjustAperture());

	const long MaxdataU=(long)(GetDoc().GetDefineMatrixRange()/2/iUseCalibrate);
	const int  PToPDtanceU = (int)(GetDoc().GetDefineMatrixRange()/(PATTERNDOTNUM-1)/iUseCalibrate);
	const int MatrixPNumU = PATTERNDOTNUM;
	for(int jj=0;jj<MatrixPNumU;jj++)
	{
		for(int ii=0;ii<MatrixPNumU;ii++)
		{
//			crdCCDPos=Coord(crdLaserPos.x,crdLaserPos.y)-crdOff+Coord(CCDOffset.x,CCDOffset.y)+Coord(MaxdataU-ii*PToPDtanceU,MaxdataU-jj*PToPDtanceU);
			crdCCDPos.x=crdLaserPos.x-crdOff.x+CCDOffset.x+MaxdataU-ii*PToPDtanceU;
			crdCCDPos.y=crdLaserPos.y-crdOff.y+CCDOffset.y+MaxdataU-jj*PToPDtanceU;

			crdCaliV.push_back(crdCCDPos);

			if(((jj==0)&&(ii==0))||((jj==MatrixPNumU-1)&&(ii==MatrixPNumU-1))||((jj==0)&&(ii==MatrixPNumU-1))||((jj==MatrixPNumU-1)&&(ii==0))||((jj==MatrixPNumU/2)&&(ii==MatrixPNumU/2)))
				crdTestV.push_back(crdCCDPos);	
		}
	}
	
	crdLASERPos.x=crdLaserPos.x-crdOff.x;
	crdLASERPos.y=crdLaserPos.y-crdOff.y;
	
	if(TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,0))
	{
		if(ftime>=3)
		{
			GetDoc().SetLastWarningNo(95);	//"У���������쳣��"
//			strncpy(ez,GetLang().GetWarningText(21044),256);
//			AfxMessageBox(ez);									//"У���������쳣�㣬�޷�����У���������!"
//			GetDoc().WriteCaliTimes();
		}
		
		bTestOk = false;
		return true;
	}
	
	MoveTo(crdLASERPos);
	
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,crdLaserPos.z);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,crdLaserPos.z);
		WaitAxisStop(AXISRIGHTZ);
	}	

	WaitAxisStop(AXISTAB);	
	Delay(500);
	
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

#ifdef SMCDMDLL
	MatrixProcess(nHead,GetDoc().GetGlvAdjPlsRelease(),0,STYPE,GetDoc().GetDefineMatrixRange(),PATTERNDOTNUM);
#else
	MatrixProcess(nHead,GetDoc().GetGlvAdjPlsRelease(),0,SOPPOSITE,GetDoc().GetDefineMatrixRange(),PATTERNDOTNUM);
#endif

	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

//	GetDoc().WriteCaliTimes();
	
	Dev.RemoveAll();
	
	if(!TargetFindInCali(nHead,crdCaliV.size(),crdCaliV,Dev,1))
		return false;

//	LightTurnOff(); 

//У�������ļ����������µ�У���ļ�������
#ifdef RTC5DLL										//ִ��RTC5��У��
	CArray	<Coord, Coord> ArrayRTC5;
	CArray	<Coord, Coord> ArrayRTC5Tran;
	long max=0,min=0;
	const int MatrixPNum=PATTERNDOTNUM;
	int index=0,center=(MatrixPNum*MatrixPNum-1)/2;
	long interval=GetDoc().GetDefineMatrixRange()/(PATTERNDOTNUM-1);
	long FirstColData=0,SecondColData=0;
	float ThirdColData=0.0,FourColData=0.0;
	long Maxdata=(long)(GetDoc().GetDefineMatrixRange()/2);
    CString saveNewCal="";
	double changeType=0;
	double dbCenterX=0.0,dbCenterY=0.0;	

	correXionPath = GetDoc().GetAppPath()+CurPath+"correXion5";

	if(nHead==HeadLeft)
	{
		CorDatPath=GetDoc().GetAppPath()+CurPath+"Cor_auto5L.dat";
		DeleteFile(CorDatPath);
		changeType=iUseCalibrate*1000.0;	
		GetInfo().SaveToFile(CorDatPath,"[INPUT]        =CorL; input table filename\n");
		GetInfo().SaveToFile(CorDatPath,"[OUTPUT]       =CorL; output table filename\n");
	}
	else
	{
		CorDatPath=GetDoc().GetAppPath()+CurPath+"Cor_auto5R.dat";	
		DeleteFile(CorDatPath);
		changeType=iUseCalibrate*1000.0;	
		GetInfo().SaveToFile(CorDatPath,"[INPUT]        =CorR; input table filename\n");
		GetInfo().SaveToFile(CorDatPath,"[OUTPUT]       =CorR; output table filename\n");
	}

	GetInfo().SaveToFile(CorDatPath,"[CALIBRATION]  = %d; calibration in bits\/mm\n",(long)changeType);
	GetInfo().SaveToFile(CorDatPath,"[RTC4]         = 0; RTC4-compatibility mode\n");
	GetInfo().SaveToFile(CorDatPath,"[FITORDER]     = 1; degree of overall polynomial fit\n");
	GetInfo().SaveToFile(CorDatPath,"[SMOOTHING]    = -1; smoothing parameter for overall spline fit\n");
	GetInfo().SaveToFile(CorDatPath,"[AUTO_FIT]     = 1; adjust parameters for fitting\n");
	GetInfo().SaveToFile(CorDatPath,"[TOLERANCE]    = 0.01; tolerance value\n\n");
	GetInfo().SaveToFile(CorDatPath,"[Limit(Bits)]  = 524288; control value limits\n");		
	GetInfo().SaveToFile(CorDatPath,"[Limit(mm)]    = %3.4f; field size limits\n",(float)(16*Maxdata/changeType));
	GetInfo().SaveToFile(CorDatPath,"[OffsetX]      = 0; offset X\n");
	GetInfo().SaveToFile(CorDatPath,"[OffsetY]      = 0; offset Y\n");
	GetInfo().SaveToFile(CorDatPath,"[Deviation]    = 0; max. deviation\n\n");
	GetInfo().SaveToFile(CorDatPath,"[GRIDNUMBERS]  = 5  5; grid X, grid Y; points: 11 per line, 11 per column, total 121\n");
	
	float arrayx[11], arrayy[11];
	for (int num=0;num<11;num++)
	{
		arrayx[num]=16*(-Maxdata+float(num*interval))/(double)GetDoc().GetSLBitPerMM();
		arrayy[num]=16*(-(Maxdata-float(num*interval)))/(double)GetDoc().GetSLBitPerMM();
	}
	
	GetInfo().SaveToFile(CorDatPath,"[GRIDVALUES_X] =    %11.3f    %11.3f    %11.6f    %11.6f\n",arrayx[0],arrayx[1],arrayx[2],arrayx[3]);
	GetInfo().SaveToFile(CorDatPath,"[GRIDVALUES_X] =    %11.6f    %11.3f    %11.6f    %11.6f\n",arrayx[4],arrayx[5],arrayx[6],arrayx[7]);
	GetInfo().SaveToFile(CorDatPath,"[GRIDVALUES_X] =    %11.6f    %11.6f    %11.6f    %11.6f\n\n",arrayx[8],arrayx[9],arrayx[10],0);
	//GetInfo().SaveToFile(CorDatPath,"\n");
	GetInfo().SaveToFile(CorDatPath,"[GRIDVALUES_Y] =    %11.6f    %11.6f    %11.6f    %11.6f\n",arrayy[0],arrayy[1],arrayy[2],arrayy[3]);
	GetInfo().SaveToFile(CorDatPath,"[GRIDVALUES_Y] =    %11.6f    %11.6f    %11.6f    %11.6f\n",arrayy[4],arrayy[5],arrayy[6],arrayy[7]);
	GetInfo().SaveToFile(CorDatPath,"[GRIDVALUES_Y] =    %11.6f    %11.6f    %11.6f    %11.6f\n\n",arrayy[8],arrayy[9],arrayy[10],0);
	
	GetInfo().SaveToFile(CorDatPath,"    Xn     Yn         X mm           Y mm\n\n");		
	ArrayRTC5.RemoveAll();
	ArrayRTC5Tran.RemoveAll();
	for(int iDevnumx=0;iDevnumx<MatrixPNum;iDevnumx++)
	{
		for(int iDevnumy=0;iDevnumy<MatrixPNum;iDevnumy++)
		{//���ļ���д��У������
			FirstColData = Maxdata-int(iDevnumx*interval);
			SecondColData = -(Maxdata-int(iDevnumy*interval));
			ThirdColData = (float)FirstColData/1000/iUseCalibrate-(float)(-Dev.GetAt(index).y)/1000;
			FourColData = (float)SecondColData/1000/iUseCalibrate-(float)(Dev.GetAt(index).x)/1000;
			
			Coord forRTC5(0,0);
			forRTC5.x=ThirdColData*1000;
			forRTC5.y=FourColData*1000;
			ArrayRTC5.Add(forRTC5);
			
			dbCenterX+=Dev.GetAt(index).x;
			dbCenterY+=Dev.GetAt(index).y;				
			//	GetInfo().SaveToFile(CorDatPath,"    %2.1d    %2.1d      %11.6f    %11.6f\n",row,line,ThirdColData,FourColData);
			
			if((-Dev.GetAt(index).y)>max)
				max=-Dev.GetAt(index).y;

			if((-Dev.GetAt(index).y)<min)
				min=-Dev.GetAt(index).y;
				
			if((Dev.GetAt(index).x)>max)
				max=Dev.GetAt(index).x;

			if((Dev.GetAt(index).x)<min)
				min=Dev.GetAt(index).x;
				
			if((abs(-Dev.GetAt(index).y)>GetDoc().GetGlvAdjustThreshold())||(abs(Dev.GetAt(index).x)>GetDoc().GetGlvAdjustThreshold()))
				bTestOk = false;					

			index++;
		}
	}

	int line=0,row=0;
	int pointPos=0;
	for(int iDevnumxSave=0;iDevnumxSave<MatrixPNum;iDevnumxSave++)
	{
		for(int iDevnumySave=0;iDevnumySave<MatrixPNum;iDevnumySave++)
		{
			pointPos=(MatrixPNum-iDevnumxSave-1)*MatrixPNum+iDevnumySave;
			ArrayRTC5Tran.Add(ArrayRTC5.GetAt(pointPos));
		}
	}

	for(iDevnumxSave=0;iDevnumxSave<MatrixPNum;iDevnumxSave++)
	{
		line=iDevnumxSave-5;
		for(int iDevnumySave=0;iDevnumySave<MatrixPNum;iDevnumySave++)
		{
			row=iDevnumySave-5;
			pointPos=iDevnumySave*MatrixPNum+iDevnumxSave;
			GetInfo().SaveToFile(CorDatPath,"    %2.1d    %2.1d      %11.6f    %11.6f\n",row,line,
				16*ArrayRTC5Tran.GetAt(pointPos).x/1000.0,	16*ArrayRTC5Tran.GetAt(pointPos).y/1000.0);				
		}
	}	
#else												//ִ��RTC4��У��
#ifdef SMCCaliDLL									//20191230
	long max=0,min=0;
	const int MatrixPNum=PATTERNDOTNUM;
	int index=0,center=(MatrixPNum*MatrixPNum-1)/2;
//	float interval=GetDoc().GetDefineMatrixRange()/(PATTERNDOTNUM-1);
	float interval=(float)(GetDoc().GetDefineMatrixRange()/(PATTERNDOTNUM-1));
//	long FirstColData=0,SecondColData=0;
	float FirstColData=0.0,SecondColData=0.0;
	float ThirdColData=0.0,FourColData=0.0;
	long Maxdata=GetDoc().GetDefineMatrixRange()/2;
//  CString saveNewCal="";
//	long changeType=0;
	double changeType=0.0;
	double dbCenterX=0.0,dbCenterY=0.0;

	correXionPath = GetDoc().GetAppPath()+CurPath+"correXion";
	
	if(nHead==HeadLeft)
	{
		CorDatPath=GetDoc().GetAppPath()+CurPath+"Cor_autoL.dat";
	    DeleteFile(CorDatPath);

		changeType=iUseCalibrate*1000.0;

		DevDatPath=GetDoc().GetAppPath()+CurPath+"DevL.csv";
		DeleteFile(DevDatPath);
		GetInfo().SaveToFile(DevDatPath,"DevX,DevY\n");
	}
	else
	{
		CorDatPath = GetDoc().GetAppPath()+CurPath+"Cor_autoR.dat";
		DeleteFile(CorDatPath);

		changeType=iUseCalibrate*1000.0;

		DevDatPath=GetDoc().GetAppPath()+CurPath+"DevR.csv";
		DeleteFile(DevDatPath);
		GetInfo().SaveToFile(DevDatPath,"DevX,DevY\n");
	}

	for(int iDevnumx=0;iDevnumx<MatrixPNum;iDevnumx++)
	{
		for(int iDevnumy=0;iDevnumy<MatrixPNum;iDevnumy++)
		{
//			FirstColData = Maxdata-int(iDevnumx*interval);
//			SecondColData = -(Maxdata-int(iDevnumy*interval));
			FirstColData = (float)Maxdata-(float)(iDevnumx*interval);
			SecondColData = -((float)Maxdata-(float)(iDevnumy*interval));
//			ThirdColData = (float)FirstColData/1000/iUseCalibrate-(float)(-Dev.GetAt(index).y)/1000;
//			FourColData = (float)SecondColData/1000/iUseCalibrate-(float)(Dev.GetAt(index).x)/1000;

//			ThirdColData = FirstColData/1000.0/iUseCalibrate-(float)(-(Dev.GetAt(index).y-Dev.GetAt(center).y))/1000.0;
//			FourColData = SecondColData/1000.0/iUseCalibrate-(float)(Dev.GetAt(index).x-Dev.GetAt(center).x)/1000.0;
			ThirdColData = FirstColData/1000.0/iUseCalibrate-(float)(-Dev.GetAt(index).y)/1000.0;						//20200225
			FourColData = SecondColData/1000.0/iUseCalibrate-(float)(Dev.GetAt(index).x)/1000.0;
			
			dbCenterX+=Dev.GetAt(index).x;
			dbCenterY+=Dev.GetAt(index).y;
			
//			GetInfo().SaveToFile(CorDatPath,"%d %d  %2.3f %2.3f\n",FirstColData,SecondColData,ThirdColData,FourColData);
//			GetInfo().SaveToFile(CorDatPath,"%2.3f %2.3f %2.3f %2.3f\n",(double)FirstColData/changeType,(double)SecondColData/changeType,ThirdColData,FourColData);
//			ctiX=-Y;ctiY=X;

//			GetInfo().SaveToFile(CorDatPath,"%2.3f %2.3f %2.3f %2.3f\n",(double)-SecondColData/changeType,(double)FirstColData/changeType,-FourColData,ThirdColData);
//			GetInfo().SaveToFile(CorDatPath,"%2.3f %2.3f %2.3f %2.3f\n",-SecondColData/changeType,FirstColData/changeType,-FourColData,ThirdColData);
			GetInfo().SaveToFile(CorDatPath,"%2.3f %2.3f %2.3f %2.3f\n",FirstColData/changeType,SecondColData/changeType,ThirdColData,FourColData);
			
//			GetInfo().SaveToFile(DevDatPath,"%d,%d\n",Dev.GetAt(index).x-Dev.GetAt(center).x,
//				Dev.GetAt(index).y-Dev.GetAt(center).y);
			GetInfo().SaveToFile(DevDatPath,"%d,%d\n",Dev.GetAt(index).x,Dev.GetAt(index).y);							//20200225
				
			if((-Dev.GetAt(index).y)>max)
				max=-Dev.GetAt(index).y;

			if((-Dev.GetAt(index).y)<min)
				min=-Dev.GetAt(index).y;
			
			if((Dev.GetAt(index).x)>max)
				max=Dev.GetAt(index).x;

			if((Dev.GetAt(index).x)<min)
				min=Dev.GetAt(index).x;
			
			if((abs(-Dev.GetAt(index).y)>GetDoc().GetGlvAdjustThreshold())||(abs(Dev.GetAt(index).x)>GetDoc().GetGlvAdjustThreshold()))
				bTestOk = false;					
			
			index++;
		}
		
		GetInfo().SaveToFile(CorDatPath,"\n");
	}
#else
	long max=0,min=0;
	const int MatrixPNum=PATTERNDOTNUM;
	int index=0,center=(MatrixPNum*MatrixPNum-1)/2;
	float interval=GetDoc().GetDefineMatrixRange()/(PATTERNDOTNUM-1);
	long FirstColData=0,SecondColData=0;
	float ThirdColData=0.0,FourColData=0.0;
	long Maxdata=(long)(GetDoc().GetDefineMatrixRange()/2);
    CString saveNewCal="";
	long changeType=0;
	double dbCenterX=0.0,dbCenterY=0.0;

	correXionPath = GetDoc().GetAppPath()+CurPath+"correXion";
	
	if(nHead==HeadLeft)
	{
		CorDatPath=GetDoc().GetAppPath()+CurPath+"Cor_autoL.dat";
	    DeleteFile(CorDatPath);

		changeType=iUseCalibrate*1000.0;
		saveNewCal.Format("%d",changeType);
        saveNewCal+=".0";
		GetInfo().SaveToFile(CorDatPath,"NewCal = %s\nOldCTBFile =CorL.ctb\nNewCTBFile =CorL.ctb\n",saveNewCal);

		DevDatPath=GetDoc().GetAppPath()+CurPath+"DevL.csv";
		DeleteFile(DevDatPath);
		GetInfo().SaveToFile(DevDatPath,"DevX,DevY\n");
	}
	else
	{
		CorDatPath = GetDoc().GetAppPath()+CurPath+"Cor_autoR.dat";
		DeleteFile(CorDatPath);

		changeType=iUseCalibrate*1000.0;
		saveNewCal.Format("%d",changeType);
        saveNewCal+=".0";
		GetInfo().SaveToFile(CorDatPath,"NewCal = %s\nOldCTBFile =CorR.ctb\nNewCTBFile =CorR.ctb\n",saveNewCal);

		DevDatPath=GetDoc().GetAppPath()+CurPath+"DevR.csv";
		DeleteFile(DevDatPath);
		GetInfo().SaveToFile(DevDatPath,"DevX,DevY\n");
	}

	for(int iDevnumx=0;iDevnumx<MatrixPNum;iDevnumx++)
	{
		for(int iDevnumy=0;iDevnumy<MatrixPNum;iDevnumy++)
		{
			FirstColData = Maxdata-int(iDevnumx*interval);
			SecondColData = -(Maxdata-int(iDevnumy*interval));
			ThirdColData = (float)FirstColData/1000/iUseCalibrate-(float)(-Dev.GetAt(index).y)/1000;
			FourColData = (float)SecondColData/1000/iUseCalibrate-(float)(Dev.GetAt(index).x)/1000;
			
			dbCenterX+=Dev.GetAt(index).x;
			dbCenterY+=Dev.GetAt(index).y;
			
			GetInfo().SaveToFile(CorDatPath,"%d %d  %2.3f %2.3f\n",FirstColData,SecondColData,ThirdColData,FourColData);
			
			GetInfo().SaveToFile(DevDatPath,"%d,%d\n",Dev.GetAt(index).x-Dev.GetAt(center).x,
				Dev.GetAt(index).y-Dev.GetAt(center).y);
				
			if((-Dev.GetAt(index).y)>max)
				max=-Dev.GetAt(index).y;

			if((-Dev.GetAt(index).y)<min)
				min=-Dev.GetAt(index).y;
			
			if((Dev.GetAt(index).x)>max)
				max=Dev.GetAt(index).x;

			if((Dev.GetAt(index).x)<min)
				min=Dev.GetAt(index).x;
			
			if((abs(-Dev.GetAt(index).y)>GetDoc().GetGlvAdjustThreshold())||(abs(Dev.GetAt(index).x)>GetDoc().GetGlvAdjustThreshold()))
				bTestOk = false;					
			
			index++;
		}
		
		GetInfo().SaveToFile(CorDatPath,"\n");
	}
#endif
#endif		//RTC5DLL
	if(abs(max)<abs(min))
		max=min;

	CString InforStr;

	if(GetDoc().GetDrillInc())	//20160801	
	{
		if(ftime<3)		
		{
			if(bTestOk)
			{
				if(nHead==HeadLeft)
				{
					InforStr.Format("%d um",max);	
#ifdef USELOG
					GetLog().Append_pro(10073,20171,InforStr);//"����񾵲�����ƫ��","�񾵵��󾫶�У����"
#endif
				}
				else
				{	
					InforStr.Format("%d um",max);
#ifdef USELOG
					GetLog().Append_pro(10074,20171,InforStr);//"�Ҳ��񾵲�����ƫ��","�񾵵��󾫶�У����"
#endif
				}
			}
			else
			{
				if(nHead==HeadLeft)
				{
					InforStr.Format("%d um",max);	
#ifdef USELOG
					GetLog().Append_pro(10073,20170,InforStr);//"����񾵲�����ƫ��","�񾵵��󾫶�У��ǰ"
#endif
				}
				else
				{	
					InforStr.Format("%d um",max);
#ifdef USELOG
					GetLog().Append_pro(10074,20170,InforStr);//"�Ҳ��񾵲�����ƫ��","�񾵵��󾫶�У��ǰ"
#endif
				}
			}
		}
		else
		{
			if(nHead==HeadLeft)
			{
				InforStr.Format("%d um",max);	
#ifdef USELOG
				GetLog().Append_pro(10073,20171,InforStr);//"����񾵲�����ƫ��","�񾵵��󾫶�У����"
#endif
			}
			else
			{	
				InforStr.Format("%d um",max);
#ifdef USELOG
				GetLog().Append_pro(10074,20171,InforStr);//"�Ҳ��񾵲�����ƫ��","�񾵵��󾫶�У����"
#endif
			}
			
		}
	}
	else
	{
		if(nHead==HeadLeft)
		{
			InforStr.Format("%d um",max);	
#ifdef USELOG
			GetLog().Append_pro(10073,20033,InforStr);//"����񾵲�����ƫ��","�񾵵��󾫶�У��"
#endif
		}
		else
		{
			InforStr.Format("%d um",max);
#ifdef USELOG
			GetLog().Append_pro(10074,20033,InforStr);//"�Ҳ��񾵲�����ƫ��","�񾵵��󾫶�У��"
#endif
		}
	}
//	AfxMessageBox(InforStr);
	
	if(bTestOk)
	{
		CCDOffset.x+=(dbCenterX/(MatrixPNum*MatrixPNum));					//20200226 ȡ�� 20200227�ָĻ�
		CCDOffset.y+=(dbCenterY/(MatrixPNum*MatrixPNum));
	}
	else
//	if(!bTestOk)
	{
//-----------------------------------------------------------------------//20190311
		char oldCTB[MaxPathLen];										
		char ctbBackup[MaxPathLen];
		char dataBackup[MaxPathLen];

		CString strOldCTB;
		CString strCTBBackup;
		CString strDataBackup;
		
#ifdef RTC5DLL
		if(nHead==HeadLeft)
		{
			strOldCTB=GetDoc().GetAppPath()+CurPath+"CorL.ct5";
			strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorL";
			strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_auto5L";
		}
		else
		{
			strOldCTB=GetDoc().GetAppPath()+CurPath+"CorR.ct5";
			strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorR";
			strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_auto5R";
		}

		sprintf(oldCTB,"%s",strOldCTB);
		sprintf(ctbBackup,"%s%d.ct5",strCTBBackup,ftime);
		sprintf(dataBackup,"%s%d.dat",strDataBackup,ftime);
#else
		if(nHead==HeadLeft)
		{
			strOldCTB=GetDoc().GetAppPath()+CurPath+"CorL.ctb";
			strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorL";
			strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_autoL";
		}
		else
		{
			strOldCTB=GetDoc().GetAppPath()+CurPath+"CorR.ctb";
			strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorR";
			strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_autoR";			
		}

		sprintf(oldCTB,"%s",strOldCTB);
		sprintf(ctbBackup,"%s%d.ctb",strCTBBackup,ftime);
		sprintf(dataBackup,"%s%d.dat",strDataBackup,ftime);
#endif
		CopyFile(oldCTB,ctbBackup,false);
		CopyFile(CorDatPath,dataBackup,false);
		Delay(500);
//----------------------------------------------------------------------
#ifdef SMCCaliDLL
		char corControl[MaxPathLen];										
		CString strcorControl;
		
		if(nHead==HeadLeft)
			strcorControl=GetDoc().GetAppPath()+CurPath+"CorLcontrol.xml";
		else
			strcorControl=GetDoc().GetAppPath()+CurPath+"CorRcontrol.xml";

		sprintf(corControl,"%s",strcorControl);

		GalvoCorrectionCreate(corControl);
#else
		ShellExecute(NULL, "open", correXionPath, CorDatPath, NULL, SW_SHOWNORMAL);
#endif
		Delay(5000);
	}	

	return true;
}

BOOL CControl::GlovaAccuracyAutoCalibrateTest(const Coord3D& crdLaserPos,Coord3D& CCDOffset,int nHead,bool &bTestOk,int ftime,int times,CString outAccuracyDataPath)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	char ez[256]={""};
	static Coord crdOff(0,0);

	CString headShowStr=""; 
	CString showXYMAXStr=""; 

//��ȡУ�����ƽ̨��ʼλ��
	if(!GetDoc().GetAutoCalibrateFieldPosOffsetForAccuracyTest(GetDoc().GetSLBitPerMM(),crdOff, nHead,0))
	{
		if(HeadLeft==nHead)
			GetDoc().SetLastWarningNo(87);						//"����У������������������µ�У����!"

		if(HeadRight==nHead)
			GetDoc().SetLastWarningNo(88);						//"����У������������������µ�У����!"

		return false;
	}

//����У����У������
//	long lTimes=GetDoc().GetPatternTimes(nHead);
//	GetDoc().SetPatternTimes(nHead,lTimes++);

//��ȡĿ��ʶ��ʱ��ƽ̨��������
	HoleCoordV crdTestV,crdCaliV;
	CArray<Coord, Coord> Dev;
	Coord crdCCDPos=Coord(0,0);
	Coord crdLASERPos=Coord(0,0);
	
	crdTestV.clear();
	crdCaliV.clear();

	if(GetDoc().GetTechnicType())
		MoveTo(GetDoc().GetLongPathAdjustAperture());	
	else
		MoveTo(GetDoc().GetAdjustAperture());

	int MatrixPNumU;
	if(times<2)
		MatrixPNumU=PATTERNDOTNUM;
	else
		MatrixPNumU=3;

	double iUseCalibrate=(double)(GetDoc().GetSLBitPerMM()/1000.0);
	const long MaxdataU=(long)(GetDoc().GetDefineMatrixRange()/2/iUseCalibrate);
	const int  PToPDtanceU = (int)(GetDoc().GetDefineMatrixRange()/(MatrixPNumU-1)/iUseCalibrate);

	for(int jj=0;jj<MatrixPNumU;jj++)
	{
		for(int ii=0;ii<MatrixPNumU;ii++)
		{
//			crdCCDPos=Coord(crdLaserPos.x,crdLaserPos.y)-crdOff+Coord(CCDOffset.x,CCDOffset.y)+Coord(MaxdataU-ii*PToPDtanceU,MaxdataU-jj*PToPDtanceU);
			crdCCDPos.x=crdLaserPos.x-crdOff.x+CCDOffset.x+MaxdataU-ii*PToPDtanceU;
			crdCCDPos.y=crdLaserPos.y-crdOff.y+CCDOffset.y+MaxdataU-jj*PToPDtanceU;

			crdCaliV.push_back(crdCCDPos);

			if(((jj==0)&&(ii==0))||((jj==MatrixPNumU-1)&&(ii==MatrixPNumU-1))||((jj==0)&&(ii==MatrixPNumU-1))||((jj==MatrixPNumU-1)&&(ii==0))||((jj==MatrixPNumU/2)&&(ii==MatrixPNumU/2)))
				crdTestV.push_back(crdCCDPos);	
		}
	}
	
	crdLASERPos.x=crdLaserPos.x-crdOff.x;
	crdLASERPos.y=crdLaserPos.y-crdOff.y;
	
	if(TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,0))
	{
		bTestOk = false;
		return true;
	}
	
	MoveTo(crdLASERPos);

	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,crdLaserPos.z);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,crdLaserPos.z);
		WaitAxisStop(AXISRIGHTZ);
	}	

	WaitAxisStop(AXISTAB);	
	Delay(500);
	
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

	long lPoint=1;	
	 
	switch(times)
	{
	case 2:
		lPoint =3;
		break;
	case 3:
		lPoint =5;
		break;
	case 4:
		lPoint =9;
		break;
	case 5:
		lPoint =15;
		break;
	case 6:
		lPoint =29;
		break;
	case 7:
		lPoint =31;
		break;
	case 8:
		lPoint =33;
		break;
	case 9:
		lPoint =35;
		break;
	case 10:
		lPoint =37;
		break;
	case 11:
		lPoint =39;
		break;
	case 12:
		lPoint =41;
		break;
	case 13:
		lPoint =45;
		break;
	case 14:
		lPoint =49;
		break;
	case 15:
		lPoint =53;
		break;
	case 16:
		lPoint =59;
		break;
	case 17:
		lPoint =65;
		break;
	case 18:
		lPoint =73;
		break;
	case 19:
		lPoint =83;
		break;
	case 20:
		lPoint =95;
		break;
	case 21:
		lPoint =115;
		break;
	case 22:
		lPoint =143;
		break;
	case 23:
		lPoint =191;
		break;
	case 24:
		lPoint =285;
		break;
	case 25:
		lPoint =375;
		break;

	case 26:
		lPoint =3;
		break;
	case 27:
		lPoint =5;
		break;
	case 28:
		lPoint =9;
		break;
	case 29:
		lPoint =15;
		break;
	case 30:
		lPoint =29;
		break;
	case 31:
		lPoint =31;
		break;
	case 32:
		lPoint =33;
		break;
	case 33:
		lPoint =35;
		break;
	case 34:
		lPoint =37;
		break;
	case 35:
		lPoint =39;
		break;
	case 36:
		lPoint =41;
		break;
	case 37:
		lPoint =45;
		break;
	case 38:
		lPoint =49;
		break;
	case 39:
		lPoint =53;
		break;
	case 40:
		lPoint =59;
		break;
	case 41:
		lPoint =65;
		break;
	case 42:
		lPoint =73;
		break;
	case 43:
		lPoint =83;
		break;
	case 44:
		lPoint =95;
		break;
	case 45:
		lPoint =115;
		break;
	case 46:
		lPoint =143;
		break;
	case 47:
		lPoint =191;
		break;
	case 48:
		lPoint =285;
		break;
	case 49:
		lPoint =375;
		break;
	default:
		lPoint =1;
		break;
	}

	if(times<2)
		MatrixProcess(nHead,GetDoc().GetGlvAdjPlsRelease(),50,RANDOM,GetDoc().GetDefineMatrixRange(),MatrixPNumU);
	else if(times<26)
	{
		MatrixProcess(nHead,GetDoc().GetGlvAdjPlsRelease(),50,STYPE,GetDoc().GetDefineMatrixRange(),lPoint,ONLYHOLE,0,true);//20161216 �޸�
		headShowStr.Format("S��%dbit, ",GetDoc().GetDefineMatrixRange()/(lPoint-1));
	}
	else
	{
		MatrixProcess(nHead,GetDoc().GetGlvAdjPlsRelease(),50,NTYPE,GetDoc().GetDefineMatrixRange(),lPoint,ONLYHOLE,0,true);//20161216 �޸�
		headShowStr.Format("N��%dbit, ",GetDoc().GetDefineMatrixRange()/(lPoint-1));
	}

	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

//	GetDoc().WriteCaliTimes();
	
	Dev.RemoveAll();
	
	if(!TargetFindInCali(nHead,crdCaliV.size(),crdCaliV,Dev,1))
		return false;

//	LightTurnOff(); 

	CString InforStr;
	CString InforStroutputx;
	CString InforStroutputy;

	int index=0;
	long max=0;
	long maxx=-100000,maxy=-100000;
	long minx=100000,miny=100000;
	long errorX=0,errorY=0;

	GetInfo().SaveToFile(outAccuracyDataPath,headShowStr);	
	
	for(int iDevnumx=0;iDevnumx<MatrixPNumU;iDevnumx++)
	{
		for(int iDevnumy=0;iDevnumy<MatrixPNumU;iDevnumy++)
		{
			errorX=-Dev.GetAt(index).y;
			errorY=-Dev.GetAt(index).x;

#ifdef GALVOTEST
			InforStr.Format("point%d,%d,%d, ",index+1,errorX,errorY);
			GetInfo().SaveToFile(outAccuracyDataPath,InforStr);	
#endif	
			if(errorX>maxx)
				maxx=errorX;
			
			if(errorX<minx)
				minx=errorX;
			
			if(errorY>maxy)
				maxy=errorY;
			
			if(errorY<miny)
				miny=errorY;
			
			index++;
		}	
	}
	
	if(labs(maxx)<labs(minx))
		maxx=minx;
	
	if(labs(maxy)<labs(miny))
		maxy=miny;

	if(labs(maxx)<labs(maxy))
		max=maxy;
	else
		max=maxx;

	InforStr.Format("%dum",max);
	
	if(nHead==HeadLeft)
	{
		InforStroutputx.Format("����񾵲��Xƫ��%dum, ",maxx);
		InforStroutputy.Format("����񾵲��Yƫ��%dum, ",maxy);
		if(times<2)
			strncpy(ez,GetLang().GetWarningText(32012),256);//"�����������Ծ������ƫ��%s\n"
		else
//			strncpy(ez,GetLang().GetWarningText(32015),256);//"%s    %s    ����񾵲��Ծ������ƫ��%s\n"
			strncpy(ez,"%s����񾵲��Ծ������ƫ��%s\n",256);
	}
	else
	{
		InforStroutputx.Format("�Ҳ��񾵲��Xƫ��%dum, ",maxx);
		InforStroutputy.Format("�Ҳ��񾵲��Yƫ��%dum, ",maxy);
		if(times<2)
			strncpy(ez,GetLang().GetWarningText(32014),256);//"�Ҳ���������Ծ������ƫ��%s\n"
		else
//			strncpy(ez,GetLang().GetWarningText(32016),256);//"%s    %s    �Ҳ��񾵲��Ծ������ƫ��%s\n"
			strncpy(ez,"%s�Ҳ��񾵲��Ծ������ƫ��%s\n",256);
	}
	
	if(times<2)
		GetInfo().SaveToFile(outAccuracyDataPath,ez,InforStr);
	else
	{
		showXYMAXStr=InforStroutputx+InforStroutputy;	
		GetInfo().SaveToFile(outAccuracyDataPath,ez,showXYMAXStr,InforStr);	
	}

	return TRUE;
}

/*
BOOL CControl::SetHeadCorParam(int nHead, double nBitX, double nBitY,double dbAngle,double dbScalX,double dbScalY)
{
	if (!GetDoc().GetIsNullPrecessHoles())
		return TRUE;

	ASSERT(nHead==HeadLeft||nHead==HeadRight);
	if(nHead==HeadLeft)
	{
		CString tempstr = GetDoc().GetCorPathName(0);
//		return 	GetSLControl().SetCorFile((LPCTSTR)GetDoc().GetCorPathName(0), 1,
//			dbScalY+0.0001754, dbScalX+0.0001754, dbAngle, nBitX, nBitY);//�����ž��Ƚ����˲�����ͬʱ��dbScalX��dbScalY�Ի���20070704��  yu
		return 	GetSLControl().SetCorFile((LPCTSTR)GetDoc().GetCorPathName(0), 1,
			dbScalY, dbScalX, dbAngle, nBitX, nBitY);//�����ž��Ƚ����˲�����ͬʱ��dbScalX��dbScalY�Ի���20070704��  yu
	}
	else if(nHead==HeadRight)
	{
//		return GetSLControl().SetCorFile((LPCTSTR)GetDoc().GetCorPathName(1), 2, 
//			dbScalY+0.0001754, dbScalX+0.0001754, dbAngle, nBitX, nBitY);//�����ž��Ƚ����˲�����ͬʱ��dbScalX��dbScalY�Ի���20070704��
		return GetSLControl().SetCorFile((LPCTSTR)GetDoc().GetCorPathName(1), 2, 
			dbScalY, dbScalX, dbAngle, nBitX, nBitY);//�����ž��Ƚ����˲�����ͬʱ��dbScalX��dbScalY�Ի���20070704��
	}
	return FALSE;
}
*/
BOOL CControl::SetHeadCorParam(int nHead, double nBitX, double nBitY,double dbAngle,double dbScalX,double dbScalY)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);
//	if (!GetDoc().GetIsNullPrecessHoles())										//20200714 ɾ��
//		return TRUE;
//--------------------------------------------------------------------------------------------------------------//20160919 �滻
	CString corFile;
	short corTable;
	if(nHead==HeadLeft)
	{
		corFile = GetDoc().GetCorPathName(0);
		corTable=1;
	}
	else if(nHead==HeadRight)
	{
		corFile = GetDoc().GetCorPathName(1);
		corTable=2;
	}

	return GalvoCorrectionLoad((LPCTSTR)corFile, corTable, dbScalY, dbScalX,dbAngle, nBitX, nBitY);//�����ž��Ƚ����˲�����ͬʱ��dbScalX��dbScalY�Ի���20070704��
}

void CControl::SetCCDCaxLuminance(UINT ulData, UINT ulChan) //ͬ���
{
	ASSERT(ulData>=0||ulData<100);
	ASSERT(ulChan==0||ulChan==1);

	if(ulData==0)//ly add 20110617
		ulData=1;
#ifdef IO_C//ly add 20110127
   if(ulChan==0)
   {//��ͬ�ᣬCH1��0��0
	   ChannelOutput(OLCHANNELSELECT,IO_ON);
	   ChannelOutput(ORCHANNELSELECT,IO_ON);
   }
   else if(ulChan==1)
   {//�ң�ͬ�ᣬCH2��1��0
	   ChannelOutput(OLCHANNELSELECT,IO_OFF);
	   ChannelOutput(ORCHANNELSELECT,IO_ON);
   }
   for(int n=0; n<8;++n)
   {
		ChannelOutput(OCCDLIGHTTUNELBIT0+n,((ulData&(0x1<<n))!=0));		
   }   
   Sleep(20);
   ChannelOutput(OCCDLIGHTSOURCEENABLE,IO_OFF);
   Sleep(30);//ly 20110601 change 30->600 �ȷ�8λ��Դֵ����д���źţ�һ����д��󣬹ر�д���źš�
   ChannelOutput(OCCDLIGHTSOURCEENABLE,IO_ON);
#else
	if(ulChan == 0)
		GetIO(IOMODE).SetAnalogOutput(2,0,float(ulData)/400);
	else if(ulChan==1)
		GetIO(IOMODE).SetAnalogOutput(2,1,float(ulData)/400);
#endif
}

void CControl::SetCCDInFrared(UINT ulData, UINT ulChan)
{//����
	if (1!=GetDoc().GetInfrared())
		return;
	ASSERT(ulData>=0||ulData<256);
	ASSERT(ulChan==0||ulChan==1);//��ͨ����0����ͨ��1
	if(ulChan==0)//��
		ChannelOutput(OCCDLIGHTTUNEHEADSEL1,IO_ON);
	else if(ulChan==1)
		ChannelOutput(OCCDLIGHTTUNEHEADSEL1,IO_OFF);	
	for(int n=0; n<8;++n)
	{
		ChannelOutput(OCCDLIGHTTUNERBIT0+n,((ulData&(0x1<<n))!=0));	
	}
	Sleep(20);
	ChannelOutput(OCCD1,IO_OFF);
	Sleep(30);
	ChannelOutput(OCCD1,IO_ON);	
	return;
}

void CControl::SetCCDLuminance(UINT ulData, UINT ulChan)//���ڻ��ι� 
{
   ASSERT(ulData>=0||ulData<256);
   ASSERT(ulChan==0||ulChan==1);//��ͨ����0����ͨ��1

   if(ulData==0)//ly add 20110617
		ulData=1;

#ifdef IO_C//ly add 20110127
   if(ulChan==0)
   {//�󣬻��Σ�CH3��0��1
	   ChannelOutput(OLCHANNELSELECT,IO_ON);
	   ChannelOutput(ORCHANNELSELECT,IO_OFF);
   }
   else if(ulChan==1)
   {//�ң����Σ�CH4��1��1
	   ChannelOutput(OLCHANNELSELECT,IO_OFF);
	   ChannelOutput(ORCHANNELSELECT,IO_OFF);
   }
   for(int n=0; n<8;++n)
   {
		ChannelOutput(OCCDLIGHTTUNELBIT0+n,((ulData&(0x1<<n))!=0));	
   }
   Sleep(20);
   ChannelOutput(OCCDLIGHTSOURCEENABLE,IO_OFF);
   Sleep(30);
   ChannelOutput(OCCDLIGHTSOURCEENABLE,IO_ON);
#else
#ifdef CCSRING	
	if(ulChan==0)
	{
		ChannelOutput(OCCDLIGHTTUNEHEADSEL,0);
	}
	else if(ulChan==1)
	{
		ChannelOutput(OCCDLIGHTTUNEHEADSEL,1);
	}	
	for(int n=0; n<8;++n)
	{
		if(ulChan==0)
		{		
			ChannelOutput(OCCDLIGHTTUNEBIT11+n,((ulData&(0x1<<n))==0));	
		}
		else if(ulChan==1)
		{		
			ChannelOutput(OCCDLIGHTTUNEBIT11+n,((ulData&(0x1<<n))==0));	
		}
	}
	Sleep(30);
	ChannelOutput(OCCDLIGHTSOURCEENABLE,IO_OFF);
	Sleep(30);
	ChannelOutput(OCCDLIGHTSOURCEENABLE,IO_ON);
#else
	for(int n=0; n<8;++n)
	{
		if(ulChan==0)
		{
			ChannelOutput(OCCDLIGHTTUNELBIT0+n,((ulData&(0x1<<n))!=0));		
		}
		else if(ulChan==1)
		{
			ChannelOutput(OCCDLIGHTTUNERBIT0+n,((ulData&(0x1<<n))!=0));	
		}
	}
#endif
#endif
}

Coord CControl::GetTablePos() const
{
    return Coord(GetPos(AXISTABX),GetPos(AXISTABY));
}

void CControl::ResetProcStatus()		//�����Զ�������ʱ�ĸ�λ
{
//	LeftPareSt = false;
//	RightPareSt = false;

    ChannelOutput(OTHETALENSPROTECT,  MIO_OFF);
	TableClampOperate(true,GetDoc().GetTableClamp());
	ChannelOutput(OFANPOWERON,IO_OFF); 
	ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);	

//	if(!GetDoc().GetFaultRun())									//20190326
//	{
		if(GetDoc().GetUse9112())
		{
			ChannelOutput(OPROCEXIT,MIO_ON);
			Delay(500);
			ChannelOutput(OPROCEXIT,MIO_OFF);
		}
		else
			SetCOMOutput(9);									//��е�ֽ�������  o����9��	i����9
//	}
}
/*
long CControl::AxisCompensate(int Axis, long lDestPos,long lCurPos) const
{
	
	ASSERT(Axis==AXISTABX||Axis==AXISTABY);
    if(Axis==AXISTABX)
	{
		return (long)( GetDoc().GetAxisXErrVaule(lDestPos)
			-GetDoc().GetAxisXErrVaule(lCurPos));
	}
	else if(Axis==AXISTABY)
	{
		return (long)(GetDoc().GetAxisYErrVaule(lDestPos)
			-GetDoc().GetAxisYErrVaule(lCurPos));
	}
	return 0;
}
*/
long CControl::AxisCompensate(int Axis, long lDestPos,long lCurPos) const
{
	
	ASSERT(Axis==AXISTABX||Axis==AXISTABY);
    if(Axis==AXISTABX)
	{
		return (long)(-GetDoc().GetAxisXErrVaule(lDestPos));
	}
	else if(Axis==AXISTABY)
	{
		return (long)(-GetDoc().GetAxisYErrVaule(lDestPos));
	}
	return 0;
}

BOOL CControl::DrillRegion(const Coord &crdPos,PROCTAB pb)										//20160919 �滻	//20170118 �޸�
{
//	Coord crdDest;	
//	crdDest=GetGlvProcTablePos(crdPos,(int)pb);
//	MoveTo(crdDest);
	
//	if(!SetCorParam(crdPos,0,pb))
//		return FALSE;

	if(!TableAndGalvoTransform((int)pb,crdPos))
		return false;

	WaitAxisStop(AXISTAB);

	if(!DrillRegion((int)pb))
		return false;
	
	return true;
}

PulsePmrV CControl::GetRegionPmr()
{
	PulsePmr pp;
	PulsePmrV ppV;
	int minJump=0;
	int times=0;
	int disRegion=GetDoc().GetDrlRegionPointDis()*GetDoc().GetSLBitPerMM()/1000.0;
	
	
//	if(GetDoc().GetFitApt())
//		minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
//	else
//		minJump=GetDoc().GetFirstDelayPeriod(); 
#ifdef AOMTYPE
	minJump=800;															//20170103��������ʱ
#else
	minJump=600;
#endif
	
	if(GetDoc().GetDrlRegPulseRelease()!=0)
	{			
		pp=GetPulsePmr(GetDoc().GetDrlRegPulseRelease(),minJump,times);
		pp.xOffset=0;
		pp.yOffset=0;
		pp.allLaserOn=true;
		ppV.push_back(pp);
	}
	if(GetDoc().GetDrlRegPulse2Release()!=0)
	{			
		pp=GetPulsePmr(GetDoc().GetDrlRegPulse2Release(),minJump,++times);
		pp.xOffset=disRegion*1.732/2.0/3.0;
		pp.yOffset=disRegion/2.0;
		pp.allLaserOn=true;
		ppV.push_back(pp);
		
		pp=GetPulsePmr(GetDoc().GetDrlRegPulse2Release(),minJump,++times);
		pp.xOffset=2*disRegion*1.732/2.0/3.0;
		pp.yOffset=2*disRegion/2.0;
		pp.allLaserOn=true;
		ppV.push_back(pp);
	}
	
#ifdef AOMTYPE
	minJump=330;																//20170103������ʱ
#else
	minJump=GetDoc().GetOtherDelayPeriod();	
#endif
	
	if(GetDoc().GetDrlRegPulse3Release()!=0)
	{
		for(int counts=0;counts<GetDoc().GetDrlRegPulse4Release();counts++)
		{
			for(int ii=0;ii<3;ii++)
			{
				pp=GetPulsePmr(GetDoc().GetDrlRegPulse3Release(),minJump,++times);
				pp.xOffset=ii*disRegion*1.732/2.0/3.0;
				pp.yOffset=ii*disRegion/2.0;
				pp.allLaserOn=true;
				ppV.push_back(pp);
			}
		}
	}
	if(GetDoc().GetDrlRegPulse5Release()!=0)
	{	
		for(int j=0;j<3;j++)
		{	
			for (int i=0;i<3;i++)
			{
				pp=GetPulsePmr(GetDoc().GetDrlRegPulse5Release(),minJump,++times);
				pp.xOffset=i*disRegion*1.732/2.0/3.0;
				pp.yOffset=j*disRegion/3.0+i*disRegion/2.0;
				pp.allLaserOn=true;
				ppV.push_back(pp);
			}
		}
	}
	
	return ppV;
}

BOOL CControl::DrillRegion(int nHead)															//20160919 ����
{
	ScanHead headNumber=SH_HeadBoth;
	if (nHead==HeadBoth)
		headNumber=SH_HeadBoth;
	else if (nHead==HeadLeft)
		headNumber=SH_Head1;
	else if (nHead==HeadRight)
		headNumber=SH_Head2;
	else
		return false;
	
	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=0;
	
//	if (GetDoc().GetIsDrillRegion())
//	{
/*
//----------------------------------------------------
		PulsePmr pp;
		PulsePmrV ppV;
		int minJump=0;
		int times=0;
		int disRegion=GetDoc().GetDrlRegionPointDis()*GetDoc().GetSLBitPerMM()/1000.0;

//		if(GetDoc().GetFitApt())
//			minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
//		else
//			minJump=GetDoc().GetFirstDelayPeriod(); 
		minJump=800;															//20170103��������ʱ
			
		if(GetDoc().GetDrlRegPulseRelease()!=0)
		{			
			pp=GetPulsePmr(GetDoc().GetDrlRegPulseRelease(),minJump,times);
			pp.xOffset=0;
			pp.yOffset=0;
			pp.allLaserOn=true;
			ppV.push_back(pp);
		}
		if(GetDoc().GetDrlRegPulse2Release()!=0)
		{			
			pp=GetPulsePmr(GetDoc().GetDrlRegPulse2Release(),minJump,++times);
			pp.xOffset=disRegion*1.732/2.0/3.0;
			pp.yOffset=disRegion/2.0;
			pp.allLaserOn=true;
			ppV.push_back(pp);
			
			pp=GetPulsePmr(GetDoc().GetDrlRegPulse2Release(),minJump,++times);
			pp.xOffset=2*disRegion*1.732/2.0/3.0;
			pp.yOffset=2*disRegion/2.0;
			pp.allLaserOn=true;
			ppV.push_back(pp);
		}
		
//		minJump=GetDoc().GetOtherDelayPeriod();	
		minJump=330;																//20170103������ʱ
			
		if(GetDoc().GetDrlRegPulse3Release()!=0)
		{
			for(int counts=0;counts<GetDoc().GetDrlRegPulse4Release();counts++)
			{
				for(int ii=0;ii<3;ii++)
				{
					pp=GetPulsePmr(GetDoc().GetDrlRegPulse3Release(),minJump,++times);
					pp.xOffset=ii*disRegion*1.732/2.0/3.0;
					pp.yOffset=ii*disRegion/2.0;
					pp.allLaserOn=true;
					ppV.push_back(pp);
				}
			}
		}
		if(GetDoc().GetDrlRegPulse5Release()!=0)
		{	
			for(int j=0;j<3;j++)
			{	
				for (int i=0;i<3;i++)
				{
					pp=GetPulsePmr(GetDoc().GetDrlRegPulse5Release(),minJump,++times);
					pp.xOffset=i*disRegion*1.732/2.0/3.0;
					pp.yOffset=j*disRegion/3.0+i*disRegion/2.0;
					pp.allLaserOn=true;
					ppV.push_back(pp);
				}
			}
		}
//------------------------------------------------------------
*/
		PulsePmrV ppV;
		ppV=GetRegionPmr();

#ifdef SMCPreLoad
		XYDataV xyV,xySubV;		
		GetSubData(xySubV,RECTWINDOW,0);
		
		BlockData bd;
		bd.holeCount=xySubV.size();

		if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,WINDOWBLOCKMODE))
		{
			AfxMessageBox("�����ӹ������г��ִ�����ȷ�Ϲ���!");
			return false;
		}
#else
		XYData holeData;
		XYDataV xyV,xySubV;
		holeData.coordX=0;
		holeData.coordY=0;
		holeData.laserON=true;
		xyV.push_back(holeData);		
		GetSubData(xySubV,RECTWINDOW,0);
		
		BlockData bd;

		if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,DRILLMODE))
		{
			AfxMessageBox("�����ӹ������г��ִ�����ȷ�Ϲ���!");
			return false;
		}
#endif
//	}

	return true;
}

BOOL CControl::DrillString(const CString& str,const Coord& crd, TextDir td,TextPosition tp,PROCTAB pb)		//20170118�滻 20180907�޸�
{
	Coord StringPos;
	int nTextHeigth=GetDoc().GetStrZoomSn()*1000;
	int nTextWidth=nTextHeigth*FONTRATIO;

//�ļ���������ݴ���1�����ļ������ԭʼ����㻻�����ַ��������½ǣ�2�������������½������������ɨ������
	if(HorizontalText==td)
	{
		switch(tp)
		{
		case 0:
			StringPos.x = crd.x;
			StringPos.y = crd.y;	
			break;
		case 1:
			StringPos.x = crd.x;
			StringPos.y = crd.y-nTextHeigth;
			break;
		case 2:
			StringPos.x = crd.x-(str.GetLength())*nTextWidth;
			StringPos.y = crd.y-nTextHeigth;
			break;
		case 3:
			StringPos.x = crd.x-(str.GetLength())*nTextWidth;
			StringPos.y = crd.y;	
			break;
		default:
			StringPos.x = crd.x;
			StringPos.y = crd.y;	
			break;
		}

		StringPos.x+=GetDoc().GetScanSize()*1000/2;
	}
	else if(VerticalText==td)
	{
		switch(tp)
		{
		case 0:
			StringPos.x = crd.x;
			StringPos.y = crd.y;
			break;
		case 1:
			StringPos.x = crd.x+nTextHeigth;
			StringPos.y = crd.y;
			break;
		case 2:
			StringPos.x = crd.x+nTextHeigth;
			StringPos.y = crd.y-(str.GetLength())*nTextWidth;
			break;
		case 3:
			StringPos.x = crd.x;
			StringPos.y = crd.y-(str.GetLength())*nTextWidth;
			break;
		default:
			StringPos.x = crd.x;
			StringPos.y = crd.y;	
			break;
		}

		StringPos.y+=GetDoc().GetScanSize()*1000/2;
	}

//	crdDest=GetGlvProcTablePos(StringPos,(int)pb);
//	MoveTo(crdDest);
	
//	if(!SetCorParam(StringPos,0,pb))
//		return FALSE;

	if(!TableAndGalvoTransform((int)pb,StringPos))
		return false;

	WaitAxisStop(AXISTAB);

//-----------------------------------------------------------------------------------------------------//20160919 �޸�
	if(!DrillString((int)pb,str,td))
		return false;
//--------------------------------------------------------------------------------------------------------
	if(!PeekRunState())
		return FALSE;	

	return true;
}

BOOL CControl::DrillString(int nHead,const CString& str,TextDir td)										//20160919 ����
{
	ScanHead headNumber=SH_HeadBoth;
	if (nHead==HeadBoth)
		headNumber=SH_HeadBoth;
	else if (nHead==HeadLeft)
		headNumber=SH_Head1;
	else if (nHead==HeadRight)
		headNumber=SH_Head2;
	else
		return FALSE;

	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=0;

	PulsePmr pp;
	PulsePmrV ppV;

	for(int k=0; k<GetDoc().GetDrlTxtPlsNum(); ++k)
	{
		int minJump=0;

		if (k==0)
        {
			if(GetDoc().GetFitApt())
				minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
			else
				minJump=GetDoc().GetFirstDelayPeriod(); 
		}
		else
			minJump=GetDoc().GetOtherDelayPeriod();	
		
		pp=GetPulsePmr(GetDoc().GetDrlTxtPulseRelease(),minJump,k);
		pp.xOffset=0;
		pp.yOffset=0;
		pp.allLaserOn=true;
		ppV.push_back(pp);
	}
	
	XYData holeData;
	XYDataV xyV,xySubV;
	holeData.coordX=0;
	holeData.coordY=0;
	holeData.laserON=true;
	xyV.push_back(holeData);
	GetSubData(xySubV,STRING,0,str,td);
	
	BlockData bd;

	if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,DRILLMODE))
	{
		AfxMessageBox("�ַ��ӹ������г��ִ�����ȷ�Ϲ���!");
		return FALSE;
	}

	return true;
}

BOOL CControl::GetFiducialMatchStatus(int nHead) const
{
    ASSERT(nHead==HeadLeft||nHead==HeadRight);
	
	if(nHead==HeadLeft)
	{
		return m_bFoundFiducialPCB1;
	}
	else //if(nHead==HeadRight)
	{
		return m_bFoundFiducialPCB2;
	}
}

void CControl::SetFiducialMatchStatus(int nHead, BOOL bStatus)
{
    ASSERT(nHead==HeadLeft||nHead==HeadRight);
	
	if(nHead==HeadLeft)
	{
		m_bFoundFiducialPCB1 = bStatus;
	}
	else  if(nHead==HeadRight)
	{
		m_bFoundFiducialPCB2 = bStatus;
	}
}

void CControl::EndProc(const Coord& crd,bool bXYMove)		//�����ֶ���ָ���ӹ�ʱ�ĸ�λ
{
//	LeftPareSt = false;
//	RightPareSt = false;
	
	if(bXYMove)
	{
		MoveTo(crd);
		WaitAxisStop(AXISTAB);
	}

	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
	TableClampOperate(true,GetDoc().GetTableClamp());
	ChannelOutput(OFANPOWERON,IO_OFF);   
	ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
}

void CControl::SetProcedPCBNum(UINT ulNum)
{
	m_uProcedPCBNum = ulNum;
	GetDoc().SetProcedPCBNum(ulNum);
}

void CControl::SetMatchMode(MATCHMODE mm)
{
	m_MatchMode = mm;
}

CControl::MATCHMODE CControl::GetMatchMode() const
{
    return m_MatchMode;
}

void CControl::SetManuPitchPointStatus(BOOL bStatus, int nHead)
{
	ASSERT(nHead == HeadLeft||nHead == HeadRight);
    if(nHead == HeadLeft)	
	{
		m_bToManuPitchPointL = bStatus;
		
	}
	//�ڶ��� 
    else if(nHead == HeadRight)
	{
		m_bToManuPitchPointR = bStatus;
	}
	
}

//BOOL CControl::DrillText(int nHead)											//20170118 �滻
BOOL CControl::DrillText()											//20190124
{
	int n;
	PROCTAB pb;

	if(m_bEnableProcPCB1&&m_bEnableProcPCB2)								//��ȫ�ֱ���������ӹ��������
		pb=PROCBOTH;
	else if(m_bEnableProcPCB1)
		pb=PROCLEFT;
	else if(m_bEnableProcPCB2)
		pb=PROCRIGHT;
/*
	if(nHead==HeadBoth)
		pb=PROCBOTH;	
	else if(nHead==HeadLeft)
		pb=PROCLEFT;
	else if(nHead==HeadRight)
		pb=PROCRIGHT;
	else
		return false;
*/
	MoveTo(GetDoc().GetDrlTxtAperture());

//�豸���
	if(GetDoc().GetEnMachSn())
	{
		for(n = 0; n<GetExcellonData().GetMachineSignCount(); ++n)
		{
#ifdef USESCANLAB
		if(!DrillString(GetDoc().GetMachSn(),GetExcellonData().GetMachineSignPos(n),GetExcellonData().GetMachineSignDir(n),
			GetExcellonData().GetMachineTextPosition(n),pb))
			return false;			
#endif
		}
	}
//�������ں�����ʱ��
	char daybuf[32],timebuf[32];   
	struct tm *NowTime;	
    time_t ltime;

	if(GetDoc().GetEnManuDay())
	{
		time(&ltime);
		NowTime= localtime( &ltime );

//#ifdef ZHIHAO
		if(GetDoc().GetCustomerSpecial()==2)
			strftime( daybuf, 32,"%m:%d", NowTime );
//#else
		else
			strftime( daybuf, 32,"%Y:%m:%d", NowTime );
//#endif

		for(n = 0; n<GetExcellonData().GetDaySignCount(); ++n)
		{
#ifdef USESCANLAB		
		if(!DrillString(daybuf,GetExcellonData().GetDaySignPos(n),GetExcellonData().GetDaySignDir(n),
			GetExcellonData().GetDayTextPosition(n),pb))
			return false;
#endif
		}
	}

	if(GetDoc().GetEnManuTime())
	{
		time(&ltime);
		NowTime= localtime( &ltime );
		strftime( timebuf, 32,"%H:%M:%S", NowTime );

		for(n = 0; n<GetExcellonData().GetTimeSignCount(); ++n)
		{
#ifdef USESCANLAB		
		if(!DrillString(timebuf,GetExcellonData().GetTimeSignPos(n),GetExcellonData().GetTimeSignDir(n),
			GetExcellonData().GetTimeTextPosition(n),pb))
			return false;
#endif
		}
	}
//�ӹ����
	if(GetDoc().GetEnAxisNo())
	{
		for(n = 0; n<GetExcellonData().GetAxisNoSignCount(); ++n)
		{			
#ifdef USESCANLAB	
			if(m_bEnableProcPCB1)
			{
				if(!DrillString("L",GetExcellonData().GetAxisNoSignPos(n),GetExcellonData().GetAxisNoSignDir(n),
					GetExcellonData().GetAxisNoTextPosition(n),PROCLEFT))
					return false;
			}
			if(m_bEnableProcPCB2)
			{
				if(!DrillString("R",GetExcellonData().GetAxisNoSignPos(n),GetExcellonData().GetAxisNoSignDir(n),
					GetExcellonData().GetAxisNoTextPosition(n),PROCRIGHT))
					return false;
			}
#endif
		}
	}
//LotID�ţ������ּӹ�ģʽ����ʿ��ר�á�����ר�á���׼ģʽ
	if(GetDoc().GetEnLOTSn())
	{
		int count,count0;
		CString MarkLID="";
		CString MarkRID="";

		m_LIncreasingStr="NO";
		m_RIncreasingStr="NO";

		if(GetDoc().GetDrillInc())				//��ʿ��ר�ã���ʽΪ����ˮ��+�ո�+�̶���
		{
			if(GetDoc().GetEnLOTInc())			//��ѡ����ˮ�ţ���ʿ��ר�ã���������ˮ��һ��
			{
				CString info = GetDoc().GetLOTIDInc();
				count0=atoi(info);
				
				MarkLID = info;
				MarkRID = info;
				
				m_LIncreasingStr=info;
				m_RIncreasingStr=info;
				
				count=count0+1;
				info.Format("%d",count);
				GetDoc().SetLOTIDInc(info);	
			}

			if(GetDoc().GetEnLOTFix())			//��ѡ���̶���
			{
				MarkLID = MarkLID+" "+GetDoc().GetLOTIDFix();
				MarkRID = MarkRID+" "+GetDoc().GetLOTIDFix();
			}			
		}
		else									//��ʽΪ���̶���+�ո�+��ˮ��
		{
			if(GetDoc().GetEnLOTFix())			//��ѡ���̶���
			{
				if(GetDoc().GetDrillH01H02())	//���������µ�H1,H2����ʽΪ�����᣺�̶���+" H1-"+��ˮ�ţ����᣺�̶���+" H2-"+��ˮ�ţ�
				{
					MarkLID = GetDoc().GetLOTIDFix()+" H1-";
					MarkRID = GetDoc().GetLOTIDFix()+" H2-";
				}	
				else							//��׼ģʽ����ʽΪ���̶���+�ո�+��ˮ��
				{
					MarkLID = GetDoc().GetLOTIDFix()+" ";
					MarkRID = GetDoc().GetLOTIDFix()+" ";
				}			
			}
		
			if(GetDoc().GetEnLOTInc())			//��ѡ����ˮ�ţ���������ˮ�Ų�һ��
			{
				CString info = GetDoc().GetLOTIDInc();
				count0=atoi(info);

				if(m_bEnableProcPCB1&&m_bEnableProcPCB2)
				{
					MarkLID = MarkLID+info;
					m_LIncreasingStr=info;  
					
					count=count0+1;
					info.Format("%d",count);
					MarkRID = MarkRID+info; 
					m_RIncreasingStr=info;
					
					count=count0+2;
					info.Format("%d",count);
					GetDoc().SetLOTIDInc(info);
				}
				else if(m_bEnableProcPCB1)
				{
					MarkLID = MarkLID+info;
					m_LIncreasingStr=info;  
					
					count=count0+1;
					info.Format("%d",count);
					GetDoc().SetLOTIDInc(info);
				}
				else if(m_bEnableProcPCB2)
				{
					MarkRID = MarkRID+info; 
					m_RIncreasingStr=info;
					
					count=count0+1;
					info.Format("%d",count);
					GetDoc().SetLOTIDInc(info);
				}
			}    
		}	
					
		for(n = 0; n<GetExcellonData().GetLotIDSignCount(); ++n)
		{		
#ifdef USESCANLAB
			if(GetDoc().GetDrillInc())
			{
				if(!DrillString(MarkLID,GetExcellonData().GetLotIDSignPos(n),GetExcellonData().GetLotIDSignDir(n),
					GetExcellonData().GetLotIDTextPosition(n),pb))
					return false;
			}
			else
			{
				if(GetDoc().GetEnLOTInc())
				{
					if(m_bEnableProcPCB1)
					{
						if(!DrillString(MarkLID,GetExcellonData().GetLotIDSignPos(n),GetExcellonData().GetLotIDSignDir(n),
							GetExcellonData().GetLotIDTextPosition(n),PROCLEFT))
							return false;
					}
					if(m_bEnableProcPCB2)
					{
						if(!DrillString(MarkRID,GetExcellonData().GetLotIDSignPos(n),GetExcellonData().GetLotIDSignDir(n),
							GetExcellonData().GetLotIDTextPosition(n),PROCRIGHT))
							return false;
					}
				}
				else
				{
					if(!DrillString(MarkLID,GetExcellonData().GetLotIDSignPos(n),GetExcellonData().GetLotIDSignDir(n),
						GetExcellonData().GetLotIDTextPosition(n),pb))
						return false;					
				}
			}
#endif	
	   }
	}
//����ֵ
	if(GetDoc().GetEnLOTScale())
	{
		CString str="";
		CString MarkLID="";
		CString MarkRID="";

		double dbSX1=1.0;
		double dbSY1=1.0;
		double dbSX2=1.0;
		double dbSY2=1.0;

		if (GetDoc().IsManSetScale())
		{
			GetDoc().GetManSetScaleVal(dbSX1,dbSY1);
			GetDoc().GetManSetScaleVal(dbSX2,dbSY2);
		}
		else
		{
			dbSX1=(m_dbScaleLX1+m_dbScaleLX2)/2.0;
			dbSY1=(m_dbScaleLY1+m_dbScaleLY2)/2.0;
			dbSX2=(m_dbScaleRX1+m_dbScaleRX2)/2.0;
			dbSY2=(m_dbScaleRY1+m_dbScaleRY2)/2.0;
		}
		
		if(2==GetDoc().GetShenLan3Fid())				//20160812
		{
			str.Format("LX:%.6f %s",dbSX1,IsWhatString(dbSX1));
			MarkLID = str;
			
			str.Format("LY:%.6f %s",dbSY1,IsWhatString(dbSY1));
			MarkLID = MarkLID+" "+str;
			
			str.Format("RX:%.6f %s",dbSX2,IsWhatString(dbSX2));
			MarkRID = str;
			
			str.Format("RY:%.6f %s",dbSY2,IsWhatString(dbSY2));
			MarkRID = MarkRID+" "+str;
		}
		else
		{
//#ifdef ZHIHAO
//			if(GetDoc().GetCustomerSpecial()==2)
			if((GetDoc().GetCustomerSpecial()==2)||(GetDoc().GetCustomerSpecial()==3))			//20200326
			{
				str.Format("LY:%.6f",dbSY1);
				MarkLID = str;
				
				str.Format("LX:%.6f",dbSX1);	
				MarkLID = MarkLID+" "+str;
				
				str.Format("RY:%.6f",dbSY2);
				MarkRID = str;
				
				str.Format("RX:%.6f",dbSX2);
				MarkRID = MarkRID+" "+str;
			}
//#else
			else
			{
				str.Format("LX:%.6f",dbSX1);
				MarkLID = str;
				
				str.Format("LY:%.6f",dbSY1);
				MarkLID = MarkLID+" "+str;
				
				str.Format("RX:%.6f",dbSX2);
				MarkRID = str;
				
				str.Format("RY:%.6f",dbSY2);
				MarkRID = MarkRID+" "+str;
			}
//#endif
		}
					
		for(n = 0; n<GetExcellonData().GetScaleSignCount(); ++n)
		{		
#ifdef USESCANLAB	
			if(m_bEnableProcPCB1)
			{
				if(!DrillString(MarkLID,GetExcellonData().GetScaleSignPos(n),GetExcellonData().GetScaleSignDir(n),
					GetExcellonData().GetScaleTextPosition(n),PROCLEFT))
					return false;
			}
			if(m_bEnableProcPCB2)
			{
				if(!DrillString(MarkRID,GetExcellonData().GetScaleSignPos(n),GetExcellonData().GetScaleSignDir(n),
					GetExcellonData().GetScaleTextPosition(n),PROCRIGHT))
					return false;
			}			
#endif	
	   }
	}
//�ַ���
	if(GetDoc().GetEnManuString()) 
	{
		for(n = 0; n<GetExcellonData().GetStrTextSignCount(); ++n)
		{
#ifdef USESCANLAB
			if(!DrillString(GetExcellonData().GetStrText(n),GetExcellonData().GetStrTextSignPos(n),GetExcellonData().GetStrTextSignDir(n),
				GetExcellonData().GetStrTextPosition(n),pb))
				return false;
#endif	
	   }
	}

    return TRUE;
}

//BOOL CControl::DrillFiducial(int nHead)														//20161109	//20170118 �޸�
BOOL CControl::DrillFiducial()												//20190124
{
	PROCTAB pb;

	if(m_bEnableProcPCB1&&m_bEnableProcPCB2)								//��ȫ�ֱ���������ӹ��������
		pb=PROCBOTH;
	else if(m_bEnableProcPCB1)
		pb=PROCLEFT;
	else if(m_bEnableProcPCB2)
		pb=PROCRIGHT;

//Z��Lens�۽�
	ZAxisLensFocus((int)pb,GetDoc().GetPCBThickness(),false);
/*
	if(nHead==HeadBoth)
		pb=PROCBOTH;	
	else if(nHead==HeadLeft)
		pb=PROCLEFT;
	else if(nHead==HeadRight)
		pb=PROCRIGHT;
	else
		return false;
*/	
	MoveTo(GetDoc().GetDrlRegAperture());	
	
   	WaitAxisStop(AXISLEFTZ);
    WaitAxisStop(AXISRIGHTZ);

	if(!PeekRunState())
		return FALSE;

	Coord innerFiducialPos[8];
	int innerFiducialNum=0;

	if(!GetDoc().GetIsDoubleFileData())
	{
		innerFiducialNum=GetExcellonData().GetInnerFiducialNum();
		for(int m=0;m<innerFiducialNum;m++)
			innerFiducialPos[m]=GetExcellonData().GetInnerFiducialPos(m);
	}
	else
	{
		int oldGlobalExcellonIndex=GetGlobalExcellonIndex();

		int order[2]={0,1};
		if(GetDoc().GetExcellonData0IsUp())
		{
			order[0]=1;
			order[1]=0;
		}

		SetGlobalExcellonIndex(order[0]);
		innerFiducialPos[0]=GetExcellonData().GetInnerFiducialPos(0);
		innerFiducialPos[1]=GetExcellonData().GetInnerFiducialPos(1);
		innerFiducialPos[6]=GetExcellonData().GetInnerFiducialPos(2);
		innerFiducialPos[7]=GetExcellonData().GetInnerFiducialPos(3);

		SetGlobalExcellonIndex(order[1]);
		innerFiducialPos[2]=GetExcellonData().GetInnerFiducialPos(0);
		innerFiducialPos[3]=GetExcellonData().GetInnerFiducialPos(1);
		innerFiducialPos[4]=GetExcellonData().GetInnerFiducialPos(2);
		innerFiducialPos[5]=GetExcellonData().GetInnerFiducialPos(3);

		SetGlobalExcellonIndex(oldGlobalExcellonIndex);

		if((innerFiducialPos[1]==innerFiducialPos[2])&&(innerFiducialPos[5]==innerFiducialPos[6]))
		{
			innerFiducialNum=6;
			innerFiducialPos[2]=innerFiducialPos[3];
			innerFiducialPos[3]=innerFiducialPos[4];
			innerFiducialPos[4]=innerFiducialPos[6];
			innerFiducialPos[5]=innerFiducialPos[7];
		}
		else
			innerFiducialNum=8;
	}

//	for(int n = 0; n<GetExcellonData().GetInnerFiducialNum(); ++n)
	for(int n = 0; n<innerFiducialNum; ++n)
	{
#ifdef USESCANLAB
		DrillRegion(innerFiducialPos[n],pb);
#endif
		if(!PeekRunState())
			return FALSE;
	}
	return TRUE;
}

BOOL CControl::OnDealDataC(const SubArea &subarea, int iToolNo)	
{
//------------------------------------------------------------------------------------//20160919 �滻
	ScanHead headNumber=SH_HeadBoth;

	if (m_bEnableProcPCB1&&m_bEnableProcPCB2)								//��ȫ�ֱ���������ӹ��������
		headNumber=SH_HeadBoth;
	else if (m_bEnableProcPCB1)
		headNumber=SH_Head1;
	else if (m_bEnableProcPCB2)
		headNumber=SH_Head2;
	else
		return FALSE;

	int nToolIndex  = GetDoc().GetToolNo(iToolNo);
	int nSubToolIndex = subarea.GetSameToolIndex(nToolIndex);
	if(nSubToolIndex==-1)
		return FALSE;
	long holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();

	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=GetDoc().GetProcJumpLenth();

	PulsePmr pp;
	PulsePmrV ppV;
	for(int k=0; k<GetDoc().GetToolPara(iToolNo,0).GetCycleNum(); ++k)
	{
        Energy eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);
		int minJump=0;

		if (k==0)
        {
			if(GetDoc().GetFitApt())
				minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
			else
				minJump=GetDoc().GetFirstDelayPeriod(); 

			pp=GetPulsePmr(eng.m_iRelease,minJump,k);
		}
		else
		{
			minJump=GetDoc().GetOtherDelayPeriod();	

			pp=GetPulsePmr(eng.m_iRelease,minJump,k,false);									//20181229
		}

//		pp=GetPulsePmr(eng.m_iRelease,minJump,k);
//		pp=GetPulsePmr(eng.m_iRelease+GetDoc().GetLaserComp(),minJump,k);					//20171011
		pp.xOffset=0;
		pp.yOffset=0;
		pp.allLaserOn=true;
		ppV.push_back(pp);
	}

#ifdef SMCPreLoad											//20191015

	XYDataV xyV,xySubV;
	BlockData bd;

	if(m_bSADataIsPreLoad)
	{
		bd.subAreaNo=m_lCurDrillSubAreaNo;
		bd.toolNo=iToolNo;
		bd.holeCount=holecnt;
		
		if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,DRILLBLOCKMODE))
		{
			AfxMessageBox("�����ӹ������г��ִ�����ȷ�Ϲ���!");
			return FALSE;
		}
	}
	else
	{
		long holeNum=0;	
		std::vector<HoleClass>::iterator hcv;
		std::vector<Coord>::iterator Holecrd;
		XYData holeData;
		
		hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
		
		while( holeNum < holecnt )
		{
			Holecrd = hcv->hcvHolePos.begin()+holeNum;		
			
			holeData.coordX=Holecrd->x;
			holeData.coordY=Holecrd->y;
			holeData.laserON=true;
			xyV.push_back(holeData);
			
			holeNum++;
		}
		
		if(GetDoc().GetSysCircleProcMode())
			GetCircleWindowSubData(xySubV,iToolNo);
		
		if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,DRILLMODE))
		{
			AfxMessageBox("�����ӹ������г��ִ�����ȷ�Ϲ���!");
			return FALSE;
		}
	}

#else

	long holeNum=0;	
	std::vector<HoleClass>::iterator hcv;
	std::vector<Coord>::iterator Holecrd;
	XYData holeData;
	XYDataV xyV,xySubV;
	
	hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
	
	while( holeNum < holecnt )
	{
		Holecrd = hcv->hcvHolePos.begin()+holeNum;		
		
		holeData.coordX=Holecrd->x;
		holeData.coordY=Holecrd->y;
		holeData.laserON=true;
		xyV.push_back(holeData);
		
		holeNum++;
	}
	
	if(GetDoc().GetSysCircleProcMode())
		GetCircleWindowSubData(xySubV,iToolNo);
	
	BlockData bd;
	
	if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,DRILLMODE))
	{
		AfxMessageBox("�����ӹ������г��ִ�����ȷ�Ϲ���!");
		return FALSE;
	}

#endif
//---------------------------------------------------------------------------------------------------    
	double CurDldHole=GetDoc().GetHolesSum();	
	if(m_bEnableProcPCB1)
		CurDldHole+=(double)(holecnt/10000.0);
	if(m_bEnableProcPCB2)
		CurDldHole+=(double)(holecnt/10000.0);
	GetDoc().SetHolesSum(CurDldHole);

	m_lCurDrillHoleNo+=holecnt;
	GetDoc().SetCurPCBDrilledHoleCount(m_lCurDrillHoleNo);

	SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);	

	if(GetDoc().GetCTIHWWarning())//ly add 20130708
	{
		GetDoc().SetLastWarningNo(109);
		return FALSE;
	}

//	if(!PeekRunState())
//		return FALSE;

	return TRUE;
}
/*
PulsePmr CControl::GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number)		//20160919 ����
{
	int AOMOnDelay=GetDoc().GetHdSysAOMOnDelay();
	int AOMOffAhead=GetDoc().GetHdSysAOMOffAhead();
	float LaserMAXDutyCycle=GetDoc().GetHdSysLaserMAXDutyCycle();
	PulseMode pm=(PulseMode)GetDoc().GetHdSysPulseMode();

	PulsePmr pp;
	pp.laserOnTime=0;
	pp.laser1=0;
	pp.laser2=0;
	pp.laserOnDelay=0;
	pp.laserOffDelay=0;
	pp.laserPulsePeriod=300;
	pp.laserPulseCount=number;

	switch(pm)
	{
	case 0:					//AOMMODE
	case 1:					//LASERSYNCMODE
		pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead;
		pp.laser1=AOMOnDelay+energy;
		pp.laser2=energy;
		break;
	case 2:					//DOUBLELASERMODE
		pp.laserOnTime=10+energy;
		pp.laser1=energy;
		pp.laser2=energy;
		break;
	case 3:					//SINGLELASERMODE:ĿǰΨһ��һ̨E2��laseron�źſ��Ƽ������������ʱ���֣������º���DOUBLELASERMODEһ��
		pp.laserOnTime=energy;
		pp.laser1=energy;
		pp.laser2=energy;
		break;
	default:
		AfxMessageBox("����ģʽ������Ч����ȷ��!");
		break;
	}
	if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
			interval=pp.laserOnTime/LaserMAXDutyCycle;
	pp.laserPulsePeriod=interval;

	return pp;
}

PulsePmr CControl::GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number)		//20161216 �޸�
{
	int AOMOnDelay=GetDoc().GetHdSysAOMOnDelay();
	int AOMOffAhead=GetDoc().GetHdSysAOMOffAhead();
	float LaserMAXDutyCycle=GetDoc().GetHdSysLaserMAXDutyCycle();
	PulseMode pm=(PulseMode)GetDoc().GetHdSysPulseMode();

	PulsePmr pp;
	pp.laserOnTime=0;
	pp.laser1=0;
	pp.laser2=0;
	pp.laserOnDelay=0;
	pp.laserOffDelay=0;
	pp.laserPulsePeriod=300;
	pp.laserPulseCount=number;

	switch(pm)
	{
	case 0:					//AOMMODE
	case 1:					//LASERSYNCMODE
//		pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead;
//		pp.laser1=AOMOnDelay+energy;
//		pp.laser2=energy;
		pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead+GetDoc().GetLaserTestComp()+GetDoc().GetLaserComp();	//20171124
		pp.laser1=AOMOnDelay+energy+GetDoc().GetLaserTestComp();				
		pp.laser2=energy+GetDoc().GetLaserComp();
		if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
			interval=pp.laserOnTime/LaserMAXDutyCycle;
		break;
	case 2:					//DOUBLELASERMODE
	case 3:					//SINGLELASERMODE
		pp.laserOnTime=10+energy;
//		pp.laser1=energy;
//		pp.laser2=energy;
		pp.laser1=energy+GetDoc().GetLaserTestComp();															//20171124
		pp.laser2=energy+GetDoc().GetLaserComp();
		if (interval<(energy/LaserMAXDutyCycle))
			interval=energy/LaserMAXDutyCycle;
		break;
//	case 3:					//SINGLELASERMODE:ĿǰΨһ��һ̨E2��laseron�źſ��Ƽ������������ʱ���֣������º���DOUBLELASERMODEһ��
//		pp.laserOnTime=energy;
//		pp.laser1=energy;
//		pp.laser2=energy;
//		if (interval<(energy/LaserMAXDutyCycle))
//			interval=energy/LaserMAXDutyCycle;
//		break;
	default:
		AfxMessageBox("����ģʽ������Ч����ȷ��!");
		break;
	}
//	if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
//			interval=pp.laserOnTime/LaserMAXDutyCycle;

	pp.laserPulsePeriod=interval;

	return pp;
}
*/
/*
PulsePmr CControl::GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number,bool bFirstPulse)		//20181229 �޸�
{
	int AOMOnDelay=GetDoc().GetHdSysAOMOnDelay();
	int AOMOffAhead=GetDoc().GetHdSysAOMOffAhead();
	float LaserMAXDutyCycle=GetDoc().GetHdSysLaserMAXDutyCycle();
	PulseMode pm=(PulseMode)GetDoc().GetHdSysPulseMode();
	int pulseWidth=0;

	PulsePmr pp;
	pp.laserOnTime=0;
	pp.laser1=0;
	pp.laser2=0;
	pp.laserOnDelay=0;
	pp.laserOffDelay=0;
	pp.laserPulsePeriod=300;
	pp.laserPulseCount=number;

	switch(pm)
	{
	case 0:					//AOMMODE
	case 1:					//LASERSYNCMODE
//		pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead;
//		pp.laser1=AOMOnDelay+energy;
//		pp.laser2=energy;
		if(bFirstPulse)
		{
			pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead+GetDoc().GetLaserTestComp()+GetDoc().GetLaserComp();	//20171124
			pp.laser1=AOMOnDelay+energy+GetDoc().GetLaserTestComp();				
			pp.laser2=energy+GetDoc().GetLaserComp();
		}
		else
		{
			pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead+GetDoc().GetFirstJumpDelay()+GetDoc().GetOtherJumpDelay();
			pp.laser1=AOMOnDelay+energy+GetDoc().GetFirstJumpDelay();				
			pp.laser2=energy+GetDoc().GetOtherJumpDelay();
		}

		if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
			interval=pp.laserOnTime/LaserMAXDutyCycle;
		break;
	case 2:					//DOUBLELASERMODE
	case 3:					//SINGLELASERMODE
		pp.laserOnTime=10+energy;
//		pp.laser1=energy;
//		pp.laser2=energy;
		if(bFirstPulse)
		{
			pp.laser1=energy+GetDoc().GetLaserTestComp();															//20171124
			pp.laser2=energy+GetDoc().GetLaserComp();
		}
		else
		{
			pp.laser1=energy+GetDoc().GetFirstJumpDelay();
			pp.laser2=energy+GetDoc().GetOtherJumpDelay();
		}

		pulseWidth=pp.laser1;
		if(pp.laser2>pp.laser1)
			pulseWidth=pp.laser2;

		if (interval<(pulseWidth/LaserMAXDutyCycle))
			interval=pulseWidth/LaserMAXDutyCycle;
		break;
//	case 3:					//SINGLELASERMODE:ĿǰΨһ��һ̨E2��laseron�źſ��Ƽ������������ʱ���֣������º���DOUBLELASERMODEһ��
//		pp.laserOnTime=energy;
//		pp.laser1=energy;
//		pp.laser2=energy;
//		if (interval<(energy/LaserMAXDutyCycle))
//			interval=energy/LaserMAXDutyCycle;
//		break;
	default:
		AfxMessageBox("����ģʽ������Ч����ȷ��!");
		break;
	}
//	if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
//			interval=pp.laserOnTime/LaserMAXDutyCycle;

	pp.laserPulsePeriod=interval;

	return pp;
}
*/
//PulsePmr CControl::GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number,bool bFirstPulse)			//20190822 �޸�
PulsePmr CControl::GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number,bool bFirstPulse,bool bPower)	//20200515 �޸�
{
	int AOMOnDelay=GetDoc().GetHdSysAOMOnDelay();
	int AOMOffAhead=GetDoc().GetHdSysAOMOffAhead();
	float LaserMAXDutyCycle=GetDoc().GetHdSysLaserMAXDutyCycle();
	PulseMode pm=(PulseMode)GetDoc().GetHdSysPulseMode();
	int pulseWidth=0;
	int actual=0;

	PulsePmr pp;
	pp.laserOnTime=0;
	pp.laser1=0;
	pp.laser2=0;
	pp.laserOnDelay=0;
	pp.laserOffDelay=0;
	pp.laserPulsePeriod=300;
	pp.laserPulseCount=number;

	switch(pm)
	{
	case 0:					//AOMMODE
	case 1:					//LASERSYNCMODE
//		pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead;
//		pp.laser1=AOMOnDelay+energy;
//		pp.laser2=energy;
		if(bFirstPulse)
		{
			if(bPower)		//20200515
			{
				pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead+GetDoc().GetLaserTestComp()+GetDoc().GetLaserComp()+GetDoc().GetLaserComp1()+GetDoc().GetLaserComp2();
				pp.laser1=AOMOnDelay+energy+GetDoc().GetLaserTestComp()+GetDoc().GetLaserComp2();
				actual=energy+GetDoc().GetLaserComp()+GetDoc().GetLaserComp1();
			}
			else
			{
				pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead+GetDoc().GetLaserTestComp()+GetDoc().GetLaserComp();	//20171124
				pp.laser1=AOMOnDelay+energy+GetDoc().GetLaserTestComp();
				actual=energy+GetDoc().GetLaserComp();
			}

			if(energy==0)
				pp.laser2=0;
			else
			{
				if(actual<0)
					pp.laser2=0;
				else
					pp.laser2=actual;
			}
		}
		else
		{
			pp.laserOnTime=AOMOnDelay+2*energy+1+AOMOffAhead+GetDoc().GetFirstJumpDelay()+GetDoc().GetOtherJumpDelay();
			pp.laser1=AOMOnDelay+energy+GetDoc().GetFirstJumpDelay();				
//			pp.laser2=energy+GetDoc().GetOtherJumpDelay();

			actual=energy+GetDoc().GetOtherJumpDelay();
			if(energy==0)
				pp.laser2=0;
			else
			{
				if(actual<0)
					pp.laser2=0;
				else
					pp.laser2=actual;
			}
		}

		if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
			interval=pp.laserOnTime/LaserMAXDutyCycle;
		break;
	case 2:					//DOUBLELASERMODE
	case 3:					//SINGLELASERMODE
		pp.laserOnTime=10+energy;
//		pp.laser1=energy;
//		pp.laser2=energy;
		if(bFirstPulse)
		{
//			pp.laser1=energy+GetDoc().GetLaserTestComp();															//20171124
//			pp.laser2=energy+GetDoc().GetLaserComp();

			if(bPower)		//20200515
				actual=energy+GetDoc().GetLaserTestComp()+GetDoc().GetLaserComp2();
			else
				actual=energy+GetDoc().GetLaserTestComp();

			if(energy==0)
				pp.laser1=0;
			else
			{
				if(actual<0)
					pp.laser1=0;
				else
					pp.laser1=actual;
			}

			if(bPower)		//20200515
				actual=energy+GetDoc().GetLaserComp()+GetDoc().GetLaserComp1();
			else
				actual=energy+GetDoc().GetLaserComp();

			if(energy==0)
				pp.laser2=0;
			else
			{
				if(actual<0)
					pp.laser2=0;
				else
					pp.laser2=actual;
			}
		}
		else
		{
//			pp.laser1=energy+GetDoc().GetFirstJumpDelay();
//			pp.laser2=energy+GetDoc().GetOtherJumpDelay();

			actual=energy+GetDoc().GetFirstJumpDelay();
			if(energy==0)
				pp.laser1=0;
			else
			{
				if(actual<0)
					pp.laser1=0;
				else
					pp.laser1=actual;
			}

			actual=energy+GetDoc().GetOtherJumpDelay();
			if(energy==0)
				pp.laser2=0;
			else
			{
				if(actual<0)
					pp.laser2=0;
				else
					pp.laser2=actual;
			}
		}

		pulseWidth=pp.laser1;
		if(pp.laser2>pp.laser1)
			pulseWidth=pp.laser2;

		if (interval<(pulseWidth/LaserMAXDutyCycle))
			interval=pulseWidth/LaserMAXDutyCycle;
		break;
//	case 3:					//SINGLELASERMODE:ĿǰΨһ��һ̨E2��laseron�źſ��Ƽ������������ʱ���֣������º���DOUBLELASERMODEһ��
//		pp.laserOnTime=energy;
//		pp.laser1=energy;
//		pp.laser2=energy;
//		if (interval<(energy/LaserMAXDutyCycle))
//			interval=energy/LaserMAXDutyCycle;
//		break;
	default:
		AfxMessageBox("����ģʽ������Ч����ȷ��!");
		break;
	}
//	if (interval<(pp.laserOnTime/LaserMAXDutyCycle))
//			interval=pp.laserOnTime/LaserMAXDutyCycle;

//	if (interval<MINLASERPERIOD)							//20191216
//		interval=MINLASERPERIOD;
	if (interval<GetDoc().GetMINlaserPeriod())
		interval=GetDoc().GetMINlaserPeriod();

	pp.laserPulsePeriod=interval;

	return pp;
}

BOOL CControl::LightTurnOn(UINT LayerSel)
{
#ifdef CCSRING
	ChannelOutput(OCCDLIGHTTUNEBITLCEN , IO_OFF);	//ͬ���͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTTUNEBITRCEN , IO_OFF);
	ChannelOutput(OCCDLIGHTSOURCELEFT , IO_OFF);	//���ι�͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTSOURCERIGHT , IO_OFF);
#else
	GetControl().ChannelOutput(OCCDLIGHTONL,IO_ON);			//���ι�ߵ�ƽ��(Moritex)
	GetControl().ChannelOutput(OCCDLIGHTONR,IO_ON);	
	#ifdef IO_C//ly add 20110127
	GetControl().ChannelOutput(OCCDLIGHTONCOL,IO_ON);		//ͬ���ߵ�ƽ��
	GetControl().ChannelOutput(OCCDLIGHTONCOR,IO_ON);
	#else
	GetControl().ChannelOutput(OCCDLIGHTONCOL,IO_OFF);		//ͬ���͵�ƽ��(CCS)
	GetControl().ChannelOutput(OCCDLIGHTONCOR,IO_OFF);
	#endif
	if (1==GetDoc().GetInfrared())
	{//����
		GetControl().ChannelOutput(OCCDLIGHTONCOL1,IO_ON);
		GetControl().ChannelOutput(OCCDLIGHTONCOR1,IO_ON);
	}

#endif
	Sleep(30);//ly add 20110616
	long m_vaEditLC = GetDoc().GetCCDLightness(0,0,LayerSel);//��һ�������������ң��ڶ���������ʾͬ����ͣ�������Ϊ���У��
	long m_vaEditLR = GetDoc().GetCCDLightness(0,1,LayerSel);
    //SetCCDLuminance(m_vaEditLR,0);
    //SetCCDCaxLuminance(m_vaEditLC, 0);	
	long m_vaEditRC = GetDoc().GetCCDLightness(1,0,LayerSel);
	long m_vaEditRR = GetDoc().GetCCDLightness(1,1,LayerSel);
	//SetCCDLuminance(m_vaEditRR,1);
	//SetCCDCaxLuminance(m_vaEditRC,1);
	long longLeftInfared=GetDoc().GetCCDInfrared(0,LayerSel);
	long longRightInfared=GetDoc().GetCCDInfrared(1,LayerSel);

	SetCCDCaxLuminance(m_vaEditLC,LEFTCHAN);
	SetCCDCaxLuminance(m_vaEditRC,RIGHTCHAN);
	SetCCDLuminance(m_vaEditLR,LEFTCHAN);
	SetCCDLuminance(m_vaEditRR,RIGHTCHAN);	
	SetCCDInFrared(longLeftInfared,LEFTCHAN);	
    SetCCDInFrared(longRightInfared,RIGHTCHAN);
	return TRUE;						
}

BOOL CControl::LightTurnOff()
{
#ifdef CCSRING
	ChannelOutput(OCCDLIGHTTUNEBITLCEN , IO_ON);	//ͬ���͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTTUNEBITRCEN , IO_ON);
	ChannelOutput(OCCDLIGHTSOURCELEFT , IO_ON);		//���ι�͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTSOURCERIGHT , IO_ON);
#else
	ChannelOutput(OCCDLIGHTONL,IO_OFF);			//���ι�ߵ�ƽ��(Moritex)
	ChannelOutput(OCCDLIGHTONR,IO_OFF);	
	#ifdef IO_C//ly add 20110127
	ChannelOutput(OCCDLIGHTONCOL,IO_OFF);		//ͬ���ߵ�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTONCOR,IO_OFF);
	#else
	ChannelOutput(OCCDLIGHTONCOL,IO_ON);		//ͬ���͵�ƽ��(CCS)
	ChannelOutput(OCCDLIGHTONCOR,IO_ON);
	#endif
	if (1==GetDoc().GetInfrared())
	{//����
		GetControl().ChannelOutput(OCCDLIGHTONCOL1,IO_OFF);
		GetControl().ChannelOutput(OCCDLIGHTONCOR1,IO_OFF);
	}

#endif
	return TRUE;
}

CString CControl::ReadPowerPara(const char *filename)
{
	CString rtn = "";
	CStdioFile fpp;
	CString buf;
	
	if(!fpp.Open(filename,CFile::modeRead))
	{
		return "";
	}
	fpp.ReadString(buf);
	buf = buf.Left(buf.GetLength()-1);
	while(buf!="")
	{
		rtn+= buf;
		fpp.ReadString(buf);
		buf = buf.Left(buf.GetLength()-1);
	}
	fpp.Close();
	if(rtn.GetLength()>255)
		rtn = rtn.Mid(0,255);
	return rtn;
}

BOOL CControl::IsPassCrd( Coord* TempCrd,int const Cordsize)
{
	long Max;
	
	for(int i=0;i<Cordsize-1;i++)
	{
		for(int j=i+1;j<Cordsize;j++)
		{	
			if(TempCrd[j].x<TempCrd[i].x)
			{
				Max=TempCrd[i].x;
				TempCrd[i].x=TempCrd[j].x;		
				TempCrd[j].x=Max;
			}
		}
	}

	if(abs(TempCrd[Cordsize-1].x-TempCrd[0].x)>6)
		return FALSE;
	
	for(int ii=0;ii<Cordsize-1;ii++)
	{
		for(int jj=ii+1;jj<Cordsize;jj++)
		{	
			if(TempCrd[jj].y<TempCrd[ii].y)
			{
				Max=TempCrd[ii].y;
				TempCrd[ii].y=TempCrd[jj].y;		
				TempCrd[jj].y=Max;
			}
		}
	}

	if(abs(TempCrd[Cordsize-1].y-TempCrd[0].y)>6)
		return FALSE;
	
	return TRUE;
}

BOOL CControl::TunePos()
{
	char ez[256]={""};//ly 20110404
	if(ChannelOutput(OLOADSNAPX,IO_OFF))
	{
		strncpy(ez,GetLang().GetWarningText(21051),256);
		AfxMessageBox(ez);//"����X����Ķ�λ��·"
		return FALSE;
	}
		if(ChannelOutput(OLOADSNAPY,IO_OFF))
	{
			strncpy(ez,GetLang().GetWarningText(21051),256);
		AfxMessageBox(ez);//"����X����Ķ�λ��·"
		return FALSE;
	}
		return TRUE;
}

BOOL CControl::TunePosIm()
{
	char ez[256]={""};//ly 20110404
	if(ChannelOutput(OLOADSNAPX,IO_ON))
	{
		strncpy(ez,GetLang().GetWarningText(21051),256);
		AfxMessageBox(ez);//"����X����Ķ�λ��·"
		return FALSE;
	}
		if(ChannelOutput(OLOADSNAPY,IO_ON))
	{
			strncpy(ez,GetLang().GetWarningText(21051),256);
		AfxMessageBox(ez);//"����X����Ķ�λ��·"
		return FALSE;
	}
		return TRUE;
}

long CControl::GetBetTwoPos(long posBetOne)
{
	m_OldpostBetOne =GetDoc().GetBET1TOBET2();
    m_OldpostBetTwo=GetDoc().GetBET2TOBET3();//ly add 20130626
	float x=(float)(posBetOne/1000)+m_OldpostBetOne;
	float y=(float)(GetDoc().GetBET2F()*x-GetDoc().GetBET2F()*GetDoc().GetBET3F())/(x-GetDoc().GetBET2F()-GetDoc().GetBET3F())+GetDoc().GetBET1F();
    float Subpos=y- m_OldpostBetTwo+x-m_OldpostBetOne;
	return (long)(Subpos*1000);
}

void CControl::SetHandPause(BOOL stop)//ly add 20110815
{
	m_handPauseL = stop;
	m_handPauseUnL = stop;
}

BOOL CControl::LoadPcb()							//ԭ�е�ʹ��9112ʱʹ�õ�����
{
	time_t start_time, end_time;
	end_time = start_time = time( NULL );
	
	while(QueryIOBit(IREADYLOAD))		//����׼����ɣ�
	{
		if(!PeekRunState())//ly delete 20110816
			return FALSE;
		
		if(m_handPauseL)//ly change 20130905 !QueryIOBit(STOPMOVE)
		{
			start_time = time( NULL );
		}
		end_time = time( NULL );
		if(difftime( end_time, start_time )>120)
		{		
			GetDoc().SetLastWarningNo(69);
			return FALSE;
			
		}
		Delay(1);
	}
	
	if(!QueryIOBit(IONLYLEFT))			//�Ƿ������һ�Ű壿
		m_bOnlyOne=TRUE;
	
	if(m_handPauseL)//ly add 20130905
	{
		while(1)
		{
			if(!m_handPauseL)
				break;
			Delay(1);//20150505
		}
	}		
	ChannelOutput(OLOARDBORD,IO_ON);	//��ƽ̨�Ϸ���
	Delay(500);
	if(m_handPauseL==true)//ly add 20110816
	{
		while(1)//ly add 20130905
		{
			if(!m_handPauseL)
				break;
			Delay(1);//20150505
		}
	}
	ChannelOutput(OLOARDBORD,IO_OFF);
	
	end_time = start_time = time( NULL );
	while(QueryIOBit(IPUTBOARDONTABABLE))	//�����ϵ�ƽ̨��
	{
		if(!PeekRunState())
			return FALSE;
		
		if(m_handPauseL)//ly change 20130905 !QueryIOBit(STOPMOVE)
		{
			start_time = time( NULL );
		}
		end_time = time( NULL );
		if(difftime( end_time, start_time )>40)
		{
			GetDoc().SetLastWarningNo(70);
			return FALSE;
		}
		Delay(1);
	}	
	
	ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
	ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	
	if(!m_bOnlyOne)
	{
		ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
	}
	
	if(GetDoc().GetTableClamp())//ly change 20120523
	{
		if(QueryIOBit(ITABLECLAMPP))
		{
			TableClampOn(false);//ChannelOutput(OTABLECLAMP,IO_ON);		//ƽ̨��ǯ�ر�
			
			end_time = start_time = time( NULL );
			while(QueryIOBit(ITABLECLAMPP))			//ƽ̨��ǯ�ѹرգ�
			{
				end_time = time( NULL );
				if(difftime( end_time, start_time )>15)
				{
					GetDoc().SetLastWarningNo(44);
					return FALSE;
				}
			}
		}
	}
	
	Delay(200);
	
	if(m_handPauseL)//ly add 20130905
	{
		while(1)
		{
			if(!m_handPauseL)
				break;
			Delay(1);//20150505
		}
	}
	
	ChannelOutput(OSORBOK,IO_ON);		//��е�ֳ���
	Delay(500);
	if(m_handPauseL)//ly add 20110816
	{
		while(1)//ly add 20130905
		{
			if(!m_handPauseL)
				break;
			Delay(1);//20150505
		}
	}
	ChannelOutput(OSORBOK,IO_OFF);
	
	end_time = start_time = time( NULL );
	while(QueryIOBit(ILOADOK))			//�ѳ�����е�֣�
	{
		if(!PeekRunState())
			return FALSE;
		
		if(m_handPauseL)//ly change 20130905//ly add 20110816 !QueryIOBit(STOPMOVE)
		{
			start_time = time( NULL );
		}
		end_time = time( NULL );
		if(difftime( end_time, start_time )>40)
		{
			GetDoc().SetLastWarningNo(71);
			return FALSE;
		}
	}
		
	return TRUE;
}

//BOOL CControl::TestThicknessAL(long thick[2],int nHead)
BOOL CControl::TestThicknessAL(long thick[2],int nHead,Coord crd)		//20190725
{
	BOOL bHeadBothOrLeft=(HeadBoth==nHead||HeadLeft==nHead);
	BOOL bHeadBothOrRight=(HeadBoth==nHead||HeadRight==nHead);
	time_t start_time, end_time;
	int iZ1Flag = 0;							//��֤Z�ڰ�ȫλ��
	int iZ2Flag = 0;
	long lZSafePos = GetDoc().GetTestThicknessZSafePos();

//��ʼ��Z��״̬��Z��������ȫλ�á�ȷ���������׶�ͣ���϶�
	if(bHeadBothOrLeft)
	{
		if(GetControl().GetPos(AXISLEFTZ)>lZSafePos) 
		{
			GetControl().MoveTo(AXISLEFTZ,lZSafePos);
			iZ1Flag = 1;
		}
	}

	if(bHeadBothOrRight)
	{
		if(GetControl().GetPos(AXISRIGHTZ)>lZSafePos)
		{
			GetControl().MoveTo(AXISRIGHTZ,lZSafePos);
			iZ2Flag = 1;
		}
	}
	
	if (iZ1Flag)
		WaitAxisStop(AXISLEFTZ);

	if (iZ2Flag)
		WaitAxisStop(AXISRIGHTZ);
	
	BOOL bUpThick=TRUE;
	start_time = time( NULL );
	while(QueryIOBit(ITHICKNESS2N)||QueryIOBit(ITHICKNESS1N))
	{	
		end_time = time( NULL );
		if( difftime(end_time, start_time)>6 )
		{
//			AfxMessageBox("�������δ�ڰ�ȫλ�ã�����!");
			GetDoc().SetLastWarningNo(68);
			return false;
		}

		if (bUpThick)
		{
			bUpThick = FALSE;
			ChannelOutput(OTESTTHICKNESSN1,MIO_OFF);
			ChannelOutput(OTESTTHICKNESSN2,MIO_OFF);
		}
	}
	
//XY�Ƶ����λ��
//	MoveTo(Coord(GetDoc().GetThicknessX(),GetDoc().GetThicknessY()));
	MoveTo(crd);														//20190725
	WaitAxisStop(AXISTAB);

//�������Ʋ�ȷ����λ
	if(bHeadBothOrLeft)
		ChannelOutput(OTESTTHICKNESSN1,MIO_ON);

	if(bHeadBothOrRight)
		ChannelOutput(OTESTTHICKNESSN2,MIO_ON);

	start_time = time( NULL );

	if(bHeadBothOrLeft)
	{
		while(QueryIOBit(ITHICKNESS1P))
		{	
			end_time = time( NULL );
			if( difftime(end_time, start_time)>6 )
			{
//				AfxMessageBox("����������½�δ��λ������!");
				GetDoc().SetLastWarningNo(64);
				return false;
			}
		}
	}

	if(bHeadBothOrRight)
	{
		while(QueryIOBit(ITHICKNESS2P))
		{	
			end_time = time( NULL );
			if( difftime(end_time, start_time)>6 )
			{
//				AfxMessageBox("�Ҳ��������½�δ��λ������!");
				GetDoc().SetLastWarningNo(66);
				return false;
			}
		}
	}

	long lResult[2]={0,0};

#ifdef USEDMSYSTEM														//20190510
	if(bHeadBothOrLeft)
	{
		if(!GetMotion().Thick(HeadLeft,AXISLEFTZ))
			return false;
	}

	if(bHeadBothOrRight)
	{
		if(!GetMotion().Thick(HeadRight,AXISRIGHTZ))
			return false;
	}

	if(bHeadBothOrLeft)
	{
//		if (!GetMotion().WaitStopWhenProgramming( AXISLEFTZ))			//20190626
		if (!GetMotion().WaitStopWhenProgramming( AXISLEFTZTHICK))
			return FALSE;
	}

	if(bHeadBothOrRight)
	{
//		if (!GetMotion().WaitStopWhenProgramming( AXISRIGHTZ))			//20190626
		if (!GetMotion().WaitStopWhenProgramming( AXISRIGHTZTHICK))
			return FALSE;
	}

	if(bHeadBothOrLeft)
	{
		if(!GetMotion().GetThickness(HeadLeft,AXISLEFTZ,lResult))
			return false;
	}

	if(bHeadBothOrRight)
	{
		if(!GetMotion().GetThickness(HeadRight,AXISRIGHTZ,lResult))
			return false;
	}
#else
//����Z�������Z������������ƣ�����翪�ش���Z��λ�ø��������ź�ʱ��Z��ֹͣ
	if(!GetMotion().Thick(nHead,AXISLEFTZ))												//20180202
		return false;

	if (!GetMotion().WaitStopWhenProgramming( AXISLEFTZ))
		return FALSE;	

//��ȡ���
	if(!GetMotion().GetThickness(nHead,AXISLEFTZ,lResult))
		return false;
#endif

	if(lResult[0]<-300000||lResult[0]>60000||lResult[1]<-300000||lResult[1]>60000) //���������쳣
		return false;

	thick[0]=-lResult[0]*2000.0/2048.0/4;	//??????2000->5000 ly 20110514
	thick[1]=-lResult[1]*2000.0/2048.0/4;	//ly mark 20110510 2000->5000 ly 20110514

//��������ȷ����λ
	if(bHeadBothOrLeft)
		ChannelOutput(OTESTTHICKNESSN1,MIO_OFF);

	if(bHeadBothOrRight)
		ChannelOutput(OTESTTHICKNESSN2,MIO_OFF);

	start_time = time( NULL );

	if(bHeadBothOrLeft)
	{
		while(QueryIOBit(ITHICKNESS1N))
		{	
			end_time = time( NULL );
			if( difftime(end_time, start_time)>6 )
			{
//				AfxMessageBox("�������δ�ڰ�ȫλ�ã�����!");
				GetDoc().SetLastWarningNo(68);
				return false;
			}
		}
	}

	if(bHeadBothOrRight)
	{
		while(QueryIOBit(ITHICKNESS2N))
		{	
			end_time = time( NULL );
			if( difftime(end_time, start_time)>6 )
			{
//				AfxMessageBox("�������δ�ڰ�ȫλ�ã�����!");
				GetDoc().SetLastWarningNo(68);
				return false;
			}
		}
	}

//Z�᷵�ذ�ȫλ��
	if(bHeadBothOrLeft)
		GetControl().MoveTo(AXISLEFTZ,lZSafePos);

	if(bHeadBothOrRight)
		GetControl().MoveTo(AXISRIGHTZ,lZSafePos);
	
	WaitAxisStop(AXISLEFTZ);
	WaitAxisStop(AXISRIGHTZ);

	return true;
}

BOOL CControl::DrillStringTest(CString string,int nHead)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	Coord crdXYOriginal,crdXY;
	crdXYOriginal.x = GetPos(AXISTABX);
	crdXYOriginal.y = GetPos(AXISTABY);

	crdXY.x = crdXYOriginal.x-GetDoc().GetCCDToGlvSysOffset(nHead).x;
	crdXY.y = crdXYOriginal.y-GetDoc().GetCCDToGlvSysOffset(nHead).y;

	MoveTo(crdXY);
	WaitAxisStop(AXISTAB);

//�л���Ȧ
	MoveTo(GetDoc().GetDrlTxtAperture());	

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetTestBoardThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

//����У���ļ�
	SetHeadCorParam(0,0,0,0,1.0,1.0);
	Delay(500);																//20190221 ����
	SetHeadCorParam(1,0,0,0,1.0,1.0);
	Delay(500);																//20161216 ����

#ifdef RTC5DLL
	GalvoCorrectionSetup(0,1.0,1.0,0,0,0);
	GalvoCorrectionSetup(1,1.0,1.0,0,0,0);
#endif

	if(!DrillString(nHead,string,HorizontalText))
	{
		ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
		return false;
	}

//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

//Z��CCD�۽�
	ZAxisCCDFocus(nHead,GetDoc().GetTestBoardThickness());

//XYƽ̨�ص�֮ǰ��λ��
	MoveTo(crdXYOriginal);
	WaitAxisStop(AXISTAB);

	return TRUE;
}

BOOL CControl::DrillRegionTest(int nHead)															//20160919 �滻
{	    
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth); 
	
	Coord crdXYOriginal,crdXY;
	crdXYOriginal.x = GetPos(AXISTABX);
	crdXYOriginal.y = GetPos(AXISTABY);

	crdXY.x = crdXYOriginal.x-GetDoc().GetCCDToGlvSysOffset(nHead).x;
	crdXY.y = crdXYOriginal.y-GetDoc().GetCCDToGlvSysOffset(nHead).y;

	MoveTo(crdXY);
	WaitAxisStop(AXISTAB);

//�л���Ȧ
	MoveTo(GetDoc().GetDrlRegAperture());	

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetTestBoardThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

	if (GetDoc().GetIsDrillRegion())
	{
//����У���ļ�
		SetHeadCorParam(0,0,0,0,1.0,1.0);
		Delay(500);																//20190221 ����
		SetHeadCorParam(1,0,0,0,1.0,1.0);
		Delay(500);																//20161216 ����

#ifdef RTC5DLL
		GalvoCorrectionSetup(0,1.0,1.0,0,0,0);
		GalvoCorrectionSetup(1,1.0,1.0,0,0,0);
#endif

		if(!DrillRegion(nHead))
		{
			ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
			return false;
		}
	}

//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

//Z��CCD�۽�
	ZAxisCCDFocus(nHead,GetDoc().GetTestBoardThickness());

//XYƽ̨�ص�֮ǰ��λ��
	MoveTo(crdXYOriginal);
	WaitAxisStop(AXISTAB);

	return TRUE;
}

BOOL CControl::DealFault()
{
	char ez[256]={""};

	ChannelOutput(OCOMMONALARM,MIO_ON);
	SetLampStatus(CControl::ERR);

	strncpy(ez,GetLang().GetWarningText(41031),256);
	AfxMessageBox(ez);//"���������ش��󱨾�����Ҫֹͣ�ӹ�!"

	ChannelOutput(OCOMMONALARM,MIO_OFF); 
	SetLampStatus(CControl::WARN);

	return FALSE;
}

BOOL CControl::DealWarner()
{
	char ez[256]={""};	

	ChannelOutput(OCOMMONALARM,MIO_ON);
	SetLampStatus(CControl::ERR);

	strncpy(ez,GetLang().GetWarningText(42015),256);
	int nSel = AfxMessageBox(ez,MB_YESNO);//"�����ϻ�е�ֱ�������ȷ���Ƿ������ɵ�ǰ�����ļӹ�?"

	ChannelOutput(OCOMMONALARM,MIO_OFF); 

	if(nSel==IDYES)
	{
		GetDoc().SetFaultRun(true);
		SetLampStatus(CControl::ORDER);
		return TRUE;						
	}
	else
	{
		SetLampStatus(CControl::WARN);
		return FALSE;
	}
}

BOOL CControl::GlvSubAreaProc(const SubArea &subarea,int Aptno)//ly waitmark
{
//	if (!GetDoc().GetIsNullPrecessHoles())										//20200714 ɾ��
//		return TRUE;

	GetDoc().SetCurPCBDrilledArea(m_lCurDrillSubAreaNo+1);//ly add 20111008
	SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);	

	for(int it=0;it<GetDoc().GetToolsCnt();++it)
	{
//�жϹ�Ȧ�Ų���ͬ�Ĳ��ӹ�
		if(Aptno!=GetDoc().GetToolApertureNo(it))  //2009 12 24 
//		if(Aptno!=GetDoc().GetToolShowApertureNo(it))  //2009 12 24 
			continue;
		
	    int nToolNo = GetDoc().GetToolNo(it);
		int nSubToolIndex = subarea.GetSameToolIndex(nToolNo);
	    if(nSubToolIndex==-1)
			continue;

		int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
		if (holecnt<=0) 
			continue ;
				
		int nApt = GetDoc().GetToolApertureNo(it);

		MoveTo(nApt);	

		WaitAxisStop(AXISTAB);	
			
		switch(GetDoc().GetToolPara(it).GetDrillMode())   // �ӹ���ʽ
		{
		case 0:
//			if(!OnDealDataB(subarea,it))
//				return FALSE;
//			break;
		case 1:
//			if(!OnDealDataC(subarea,it))
//				return FALSE;
//			break;
		case 2:
		case 3:
			if(!OnDealDataC(subarea,it))
				return FALSE;
			break;
		}
	} 	

	if(!PeekRunState())
		return FALSE;

	return true;
}

BOOL CControl::GlvSubAreaProc(const SubArea &subarea,int Aptno,BOOL bToolCycleMode)//ly waitmark
{
//	if (!GetDoc().GetIsNullPrecessHoles())										//20200714 ɾ��
//		return TRUE;

	GetDoc().SetCurPCBDrilledArea(m_lCurDrillSubAreaNo+1);//ly add 20111008
	SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);	

	for(int it=0;it<GetDoc().GetToolsCnt();++it)
	{
//�жϹ�Ȧ�Ų���ͬ�Ĳ��ӹ�
		if(bToolCycleMode)
		{
			if(Aptno!=GetDoc().GetToolSubApertureNo(it))     //2009 12 24 
//			if(Aptno!=GetDoc().GetToolSubShowApertureNo(it))     //2009 12 24 
				continue;
		}
		else
		{
			if(Aptno!=GetDoc().GetToolApertureNo(it))       //2009 12 24 
//			if(Aptno!=GetDoc().GetToolShowApertureNo(it))       //2009 12 24 
				continue;
		}
		
	    int nToolNo = GetDoc().GetToolNo(it);
		int nSubToolIndex = subarea.GetSameToolIndex(nToolNo);
	    if(nSubToolIndex==-1)
			continue;
		int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
		if (holecnt<=0) 
			continue ;
				
		int nApt;
		if(bToolCycleMode)
			nApt = GetDoc().GetToolSubApertureNo(it);
		else
			nApt = GetDoc().GetToolApertureNo(it);
					
		MoveTo(nApt);

		WaitAxisStop(AXISTAB);
		
		switch(GetDoc().GetToolPara(it).GetDrillMode())   // �ӹ���ʽ
		{
		case 0:
		case 1:
		case 2:
		case 3:
 			if(!OnDealDataC(subarea,it,bToolCycleMode))//1
 				return FALSE;
			break;
		}
	} 	

	if(!PeekRunState())
		return FALSE;

	return true;
}

BOOL CControl::OnDealDataC(const SubArea &subarea, int iToolNo,BOOL bToolCycleMode)	
{
//------------------------------------------------------------------------------------//20160919 �滻
	ScanHead headNumber=SH_HeadBoth;

	if (m_bEnableProcPCB1&&m_bEnableProcPCB2)								//��ȫ�ֱ���������ӹ��������
		headNumber=SH_HeadBoth;
	else if (m_bEnableProcPCB1)
		headNumber=SH_Head1;
	else if (m_bEnableProcPCB2)
		headNumber=SH_Head2;
	else
		return FALSE;

	int nToolIndex  = GetDoc().GetToolNo(iToolNo);
	int nSubToolIndex = subarea.GetSameToolIndex(nToolIndex);
	if(nSubToolIndex==-1)
		return FALSE;
	long holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();

	GalvoPmr gp;
	gp.jumpSpeed=GetDoc().GetProcJumpSpeed();
	gp.jumpDelay=GetDoc().GetProcJumpDelay();
	gp.jumpZeroLengthDelay=GetDoc().GetProcJumpDelay0();
	gp.jumpLengthLimit=GetDoc().GetProcJumpLenth();

	PulsePmr pp;
	PulsePmrV ppV;
	for(int k=0; k<GetDoc().GetToolPara(iToolNo,0).GetCycleNum(); ++k)
	{
        Energy eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);
		int minJump=0;

		if(bToolCycleMode)
		{
			if(k==0)
				continue;
		}
		else
		{
			if(GetDoc().GetToolSubApertureNo(iToolNo)!=0)
			{
				if(k!=0)
					continue;
			}
		}

		if (k==0)
        {
			if(GetDoc().GetFitApt())
				minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
			else
				minJump=GetDoc().GetFirstDelayPeriod(); 

			pp=GetPulsePmr(eng.m_iRelease,minJump,k);
		}
		else
		{
			minJump=GetDoc().GetOtherDelayPeriod();	

			pp=GetPulsePmr(eng.m_iRelease,minJump,k,false);									//20181229
		}
	
//		pp=GetPulsePmr(eng.m_iRelease,minJump,k);
//		pp=GetPulsePmr(eng.m_iRelease+GetDoc().GetLaserComp(),minJump,k);					//20171011
		pp.xOffset=0;
		pp.yOffset=0;
		pp.allLaserOn=true;
		ppV.push_back(pp);
	}

	long holeNum = 0;	
	std::vector<HoleClass>::iterator hcv;
	hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
	std::vector<Coord>::iterator Holecrd;
	XYData holeData;
	XYDataV xyV,xySubV;
	
	while( holeNum < holecnt )
	{
		Holecrd = hcv->hcvHolePos.begin()+holeNum;		
		
		holeData.coordX=Holecrd->x;
		holeData.coordY=Holecrd->y;
		holeData.laserON=true;
		xyV.push_back(holeData);
		
		holeNum++;
	}

	if(GetDoc().GetSysCircleProcMode())
		GetCircleWindowSubData(xySubV,iToolNo);

	BlockData bd;

	if(!GalvoJobExecute(headNumber,gp,ppV,xyV,xySubV,bd,DRILLMODE))
	{
		AfxMessageBox("�����ӹ������г��ִ�����ȷ�Ϲ���!");
		return FALSE;
	}
//---------------------------------------------------------------------------------------------------  
	double CurDldHole=GetDoc().GetHolesSum();	
	if(m_bEnableProcPCB1)
		CurDldHole+=(double)(holecnt/10000.0);
	if(m_bEnableProcPCB2)
		CurDldHole+=(double)(holecnt/10000.0);
	GetDoc().SetHolesSum(CurDldHole);

	m_lCurDrillHoleNo+=holecnt;
	GetDoc().SetCurPCBDrilledHoleCount(m_lCurDrillHoleNo);	

	SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);	

	if(GetDoc().GetCTIHWWarning())//ly add 20130708
	{
		GetDoc().SetLastWarningNo(109);
		return FALSE;
	}

//	if(!PeekRunState())
//		return FALSE;

	return TRUE;
}

BOOL CControl::GetLaserPower(int nHead,float &power,bool &bTestOk,int nIndex)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);
	ASSERT(nIndex>=0&&nIndex<5);

	char ez[256]={""};
	long testtime=30;							//����ʱ��30s
	unsigned short laserperiod=1000;			//��������1000us
	Coord crdCleanRef;
	Coord3D crd3d;	
	float volt;

	long  lLZPos;
	long  lRZPos;
	short lDPosH;
	short lDPosV;

//����λ��ƫ��λ��
	switch(nIndex)
	{
		case 0:
			lDPosH= 0;lDPosV= 0;
			break;
		case 1:
			lDPosH= -25000;lDPosV= 25000;
			break;
		case 2:
			lDPosH= 25000;lDPosV= 25000;
			break;
		case 3:
			lDPosH= -25000;lDPosV=-25000;
			break;
		case 4:
			lDPosH= 25000;lDPosV= -25000;
			break;
		default:
			strncpy(ez,GetLang().GetWarningText(21035),256);
			AfxMessageBox(ez);//"����ƫ����ʱ��������"
			return false;
	}

	bInPowerTest=true;												//20190626
	
//��ȡ��ǰλ��	
	lLZPos  = GetPos(AXISLEFTZ);
	lRZPos = GetPos(AXISRIGHTZ);

//�л���Ȧ
	MoveTo(GetDoc().GetTestAperture());	
	
//����
	crdCleanRef = GetDoc().GetLaserTestCleanRefPos();
	MoveTo(crdCleanRef);
	WaitAxisStop(AXISTAB);
	
	ChannelOutput( OLASERPOWERCLEANER,MIO_ON);
	Delay(1500);
	ChannelOutput( OLASERPOWERCLEANER,MIO_OFF);
	
//ƽ̨�ƶ�������λ��
	crd3d= GetDoc().GetLaserPowerTestCrd(nHead);
	MoveTo(Coord(crd3d.x+lDPosH,crd3d.y+lDPosV));
	WaitAxisStop(AXISTAB);

//Z���ƶ��������߶�	
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,crd3d.z);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,crd3d.z);
		WaitAxisStop(AXISRIGHTZ);
	}
	
//	if(nHead==HeadLeft)
//		Delay(1000*GetDoc().GetLaserPowerDelayTime());		

//��ʼ����
	for (int times=0;times<GetDoc().GetLaserPowerTimes();times++)
	{
		bTestOk=true;

		if(!LaserPowerMeasure(nHead,lDPosH,lDPosV,GetDoc().GetTestPlsRelease(),laserperiod,testtime,&volt))
		{
			bInPowerTest=false;												//20190626
			return false;
		}

		power=volt*10;
		if(power<0.2)
			power=0;
		
		char buf[64];
		sprintf(buf,"%2.1f",power);
		power=atof(buf);

		if((power>(GetDoc().GetLaserPowerTestSt()*0.9))&&(power<(GetDoc().GetLaserPowerTestMax()*1.1)))
			break;
		else
			bTestOk=false;

		Delay(500);
	}

//	if (GetDoc().GetLaserPowerShow()&&(power>=(GetDoc().GetLaserPowerTestSt()*0.8) && power<=(GetDoc().GetLaserPowerTestSt()*0.9)))
//		power=GetDoc().GetLaserPowerTestSt()*(0.9+(rand()+1)%50/1000.0);

//��¼�������
#ifdef USELOG	
	GetLog().Append_pro(10082,20040);//"�����ɹ�","������������"

	CString tempTime;
    tempTime.Format("%d",testtime);

	char ez1[20]={""};
	char ez2[20]={""};
	strncpy(ez1 ,GetLang().GetLogText("operation",10031),20);
	strncpy(ez2 ,GetLang().GetLogText("operation",10032),20);

	GetLog().Append_Power((nHead==0)?ez1:ez2,power,tempTime,
		(int)GetDoc().GetTestPlsRelease(),(int)laserperiod,(int)GetDoc().GetTestAperture());//"��":"��"
#endif	

//����ԭʼλ��
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,lLZPos);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,lRZPos);
		WaitAxisStop(AXISRIGHTZ);
	}

	bInPowerTest=false;												//20190626

	return TRUE;
}

BOOL CControl::GetFileLaserPower(int nHead,float &power,bool &bTestOk,int nIndex)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);
	ASSERT(nIndex>=0&&nIndex<5);

	char ez[256]={""};
	long testtime=30;							//����ʱ��30s
	unsigned short laserperiod=1000;			//��������1000us
	Coord crdCleanRef;
	Coord3D crd3d;
	float volt;

	long  lLZPos;
	long  lRZPos;
	short lDPosH;
	short lDPosV;

//����λ��ƫ��λ��
	switch(nIndex)
	{
		case 0:
			lDPosH= 0;lDPosV= 0;
			break;
		case 1:
			lDPosH= -25000;lDPosV= 25000;
			break;
		case 2:
			lDPosH= 25000;lDPosV= 25000;
			break;
		case 3:
			lDPosH= -25000;lDPosV=-25000;
			break;
		case 4:
			lDPosH= 25000;lDPosV= -25000;
			break;
		default:
			strncpy(ez,GetLang().GetWarningText(21035),256);
			AfxMessageBox(ez);//"����ƫ����ʱ��������"
			return false;
	}

	bInPowerTest=true;												//20190626
	
//��ȡ��ǰλ��	
	lLZPos  = GetPos(AXISLEFTZ);
	lRZPos = GetPos(AXISRIGHTZ);

//����
	crdCleanRef = GetDoc().GetLaserTestCleanRefPos();
	MoveTo(crdCleanRef);
	WaitAxisStop(AXISTAB);
	
	ChannelOutput( OLASERPOWERCLEANER,MIO_ON);
	Delay(1500);
	ChannelOutput( OLASERPOWERCLEANER,MIO_OFF);
	
//ƽ̨�ƶ�������λ��
	crd3d= GetDoc().GetLaserPowerTestCrd(nHead);
	MoveTo(Coord(crd3d.x+lDPosH,crd3d.y+lDPosV));
	WaitAxisStop(AXISTAB);

//Z���ƶ��������߶�	
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,crd3d.z);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,crd3d.z);
		WaitAxisStop(AXISRIGHTZ);
	}

	for(int it=0;it<GetDoc().GetToolsCnt();++it)
	{
//�л���Ȧ
		int nApt;
		nApt=GetDoc().GetToolApertureNo(it);		
		MoveTo(nApt);

		Delay(500);
		
//���ò������� 
		Energy eng = GetDoc().GetToolPara(it,0).GetCycEnergy(0);
		
//		if(nHead==HeadLeft)
//			Delay(1000*GetDoc().GetLaserPowerDelayTime());
		
//��ʼ����
		for (int times=0;times<GetDoc().GetLaserPowerTimes();times++)
		{
			bTestOk=true;

			if(!LaserPowerMeasure(nHead,lDPosH,lDPosV,eng.m_iRelease,laserperiod,testtime,&volt))
			{
				bInPowerTest=false;												//20190626
				return false;
			}
			
			power=volt*10;
			if(power<0.2)
				power=0;
			
			char buf[64];
			sprintf(buf,"%2.1f",power);
			power=atof(buf);
		
			if((power>(GetDoc().GetAptPower(nApt,eng.m_iRelease)*0.9))&&(power<(GetDoc().GetAptPower(nApt,eng.m_iRelease)*1.1)))
				break;
			else
				bTestOk=false;
			
			Delay(500);
		}
		
//		if (GetDoc().GetLaserPowerShow()&&(power>=(GetDoc().GetLaserPowerTestSt()*0.8) && power<=(GetDoc().GetLaserPowerTestSt()*0.9)))
//			power=GetDoc().GetLaserPowerTestSt()*(0.9+(rand()+1)%50/1000.0);
		
//��¼�������
#ifdef USELOG	
		GetLog().Append_pro(10082,20040);//"�����ɹ�","������������"
		
		CString tempTime;
		tempTime.Format("%d",testtime);
		
		char ez1[20]={""};
		char ez2[20]={""};
		strncpy(ez1 ,GetLang().GetLogText("operation",10031),20);
		strncpy(ez2 ,GetLang().GetLogText("operation",10032),20);
		
		GetLog().Append_Power((nHead==0)?ez1:ez2,power,tempTime,
			(int)eng.m_iRelease,(int)laserperiod,(int)GetDoc().GetToolApertureNo(it));//"��":"��"
#endif
		
		if(!bTestOk)
			break;
	}

//����ԭʼλ��
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,lLZPos);
		WaitAxisStop(AXISLEFTZ);
	}
	else
	{
		MoveTo(AXISRIGHTZ,lRZPos);
		WaitAxisStop(AXISRIGHTZ);
	}

	bInPowerTest=false;												//20190626

	return TRUE;
}

bool CControl::IsBoardVacOKNew(int nHead)
{
    ASSERT(nHead==HeadLeft||nHead==HeadRight);
	char ez[256]={""};//ly 20110404

	if (nHead==HeadLeft)
	{
		while(!QueryIOBit(ITABLTVACUMM))
		{
			GetDoc().SetLastWarningNo(42);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
			
			strncpy(ez,GetLang().GetWarningText(31016),256);
			int nSel = ::AfxMessageBox(ez,MB_YESNO);//"��ƽ̨�����������!\n����(��) �˳��ӹ�(��)"
			
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
			Delay(1000);
			
			if(nSel == IDNO)
				return false;
		}
	}

	if (nHead==HeadRight)
	{
		while(!QueryIOBit(ITABRTVACUMM))
		{
			GetDoc().SetLastWarningNo(43);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
			
			strncpy(ez,GetLang().GetWarningText(31017),256);
			int nSel = ::AfxMessageBox(ez,MB_YESNO);//"��ƽ̨�����������!\n����(��) �˳��ӹ�(��)"
			
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
			Delay(1000);
			
			if(nSel == IDNO)
				return false;
		}
	}

	return true;
}

BOOL CControl::Calc75umControl()//����75us  ƴ�ճ�����һ���㷨
{
//	if(GetDoc().GetDrillInc()&&GetDoc().GetUseRefScale()==1||(GetDoc().IsManSetScale()&&GetDoc().GetCheckManulScaleRange()))
//	{	
		double midScaleX=1.0,midScaleY=1.0;
		if(GetDoc().IsManSetScale()&&GetDoc().GetCheckManulScaleRange())
			GetDoc().GetManSetScaleVal(midScaleX,midScaleY);
		
//		if(!(GetDoc().IsManSetScale()&&(!GetDoc().GetCheckManulScaleRange())))
//		{
			if ((!GetDoc().GetEn3Fid()) && (GetExcellonData().GetFiducialNum()==4))
			{//�Խ������ľ����ж�	
				distanceDentreDiagonal02=0;
				distanceDentreDiagonal13=0;
				Coord  crdCenterFile11,crdCenterFile12;
				double distanceDentreDiagonalX=0,distanceDentreDiagonalY=0;

				crdCenterFile11.x=(GetExcellonData().GetFiducial().at(0).x+GetExcellonData().GetFiducial().at(2).x)/2;
				crdCenterFile11.y=(GetExcellonData().GetFiducial().at(0).y+GetExcellonData().GetFiducial().at(2).y)/2;			
				distanceDentreDiagonalX=abs(crdCenterFile11.x-GetExcellonData().GetFiducial().at(0).x);
				distanceDentreDiagonalY=abs(crdCenterFile11.y-GetExcellonData().GetFiducial().at(0).y);
				distanceDentreDiagonal02=sqrt(pow(distanceDentreDiagonalX*midScaleX,2)+pow(distanceDentreDiagonalY*midScaleY,2));
				
				crdCenterFile12.x=(GetExcellonData().GetFiducial().at(1).x+GetExcellonData().GetFiducial().at(3).x)/2;
				crdCenterFile12.y=(GetExcellonData().GetFiducial().at(1).y+GetExcellonData().GetFiducial().at(3).y)/2;
				distanceDentreDiagonalX=abs(crdCenterFile12.x-GetExcellonData().GetFiducial().at(1).x);
				distanceDentreDiagonalY=abs(crdCenterFile12.y-GetExcellonData().GetFiducial().at(1).y);
				distanceDentreDiagonal13=sqrt(pow(distanceDentreDiagonalX*midScaleX,2)+pow(distanceDentreDiagonalY*midScaleY,2));			
			}
//		}
//	}

	return TRUE;
}

double CControl::CalcLinearLevel(int head)							//20180829
{
	Coord crd1Level = Coord (0,0);
	Coord centerLevel = Coord (0,0);
	Coord distLevel= Coord (0,0);
	Coord crdRealOffsetLLevel= Coord (0,0);	
	double maxLinearLevel=0,tempLinearLevel=0;
	Coord crdArrayFileLevel[4],crdArrayRealLevel[4];
/*
	for (int i=0;i<4;i++)
	{
//		crdArrayFileLevel[i]=GetExcellonData().GetFiducial().at(i);		
//		crdArrayRealLevel[i]=GetDoc().GetFiducial(head).at(i);
		crdArrayFileLevel[i]=GetSource(head).at(i);	
		crdArrayRealLevel[i]=GetTarget(head).at(i);
	}
*/
/*
	if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
	{
		crdArrayFileLevel[0]=GetSource(head).at(0);	
		crdArrayFileLevel[1]=GetSource(head).at(3);	
		crdArrayFileLevel[2]=GetSource(head).at(2);	
		crdArrayFileLevel[3]=GetSource(head).at(1);	

		crdArrayRealLevel[0]=GetTarget(head).at(0);
		crdArrayRealLevel[1]=GetTarget(head).at(3);
		crdArrayRealLevel[2]=GetTarget(head).at(2);
		crdArrayRealLevel[3]=GetTarget(head).at(1);
	}

	if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
	{
		crdArrayFileLevel[0]=GetSource(head).at(0);	
		crdArrayFileLevel[1]=GetSource(head).at(1);	
		crdArrayFileLevel[2]=GetSource(head).at(2);	
		crdArrayFileLevel[3]=GetSource(head).at(3);	

		crdArrayRealLevel[0]=GetTarget(head).at(0);
		crdArrayRealLevel[1]=GetTarget(head).at(1);
		crdArrayRealLevel[2]=GetTarget(head).at(2);
		crdArrayRealLevel[3]=GetTarget(head).at(3);
	}
*/
	crdArrayFileLevel[0]=GetSource(head).at(0);								//20191210
	crdArrayFileLevel[1]=GetSource(head).at(1);	
	crdArrayFileLevel[2]=GetSource(head).at(2);	
	crdArrayFileLevel[3]=GetSource(head).at(3);	
	
	crdArrayRealLevel[0]=GetTarget(head).at(0);
	crdArrayRealLevel[1]=GetTarget(head).at(1);
	crdArrayRealLevel[2]=GetTarget(head).at(2);
	crdArrayRealLevel[3]=GetTarget(head).at(3);
	
	double dbScaleLX1Level = calc::distance(crdArrayRealLevel[0],crdArrayRealLevel[3])/calc::distance(crdArrayFileLevel[0],crdArrayFileLevel[3]);
	double dbScaleLY1Level = calc::distance(crdArrayRealLevel[0],crdArrayRealLevel[1])/calc::distance(crdArrayFileLevel[0],crdArrayFileLevel[1]);		
	double dbScaleLX2Level = calc::distance(crdArrayRealLevel[1],crdArrayRealLevel[2])/calc::distance(crdArrayFileLevel[1],crdArrayFileLevel[2]);
	double dbScaleLY2Level = calc::distance(crdArrayRealLevel[2],crdArrayRealLevel[3])/calc::distance(crdArrayFileLevel[2],crdArrayFileLevel[3]);
	
	double angle1Level=calc::angle(crdArrayFileLevel[0],crdArrayFileLevel[2],crdArrayRealLevel[0],crdArrayRealLevel[2],1.0,1.0);
	double angle2Level=calc::angle(crdArrayFileLevel[3],crdArrayFileLevel[1],crdArrayRealLevel[3],crdArrayRealLevel[1],1.0,1.0);   
	
    crdRealOffsetLLevel = (crdArrayRealLevel[0]-crdArrayFileLevel[0] + crdArrayRealLevel[1]-crdArrayFileLevel[1] + crdArrayRealLevel[2]-crdArrayFileLevel[2]+crdArrayRealLevel[3]-crdArrayFileLevel[3] )/4;
	centerLevel=(crdArrayFileLevel[0]+crdArrayFileLevel[1]+crdArrayFileLevel[2]+crdArrayFileLevel[3])/4+crdRealOffsetLLevel;	
	for (int i=0;i<4;i++)
	{	
		Coord  crdTmp1= crdArrayFileLevel[i]+crdRealOffsetLLevel;
		crd1Level.x =crdArrayFileLevel[i].x+ (crdTmp1.x-centerLevel.x)*((dbScaleLX1Level+dbScaleLX2Level)/2.0-1);
		crd1Level.y =crdArrayFileLevel[i].y+ (crdTmp1.y-centerLevel.y)*((dbScaleLY1Level+dbScaleLY2Level)/2.0-1);		
		crd1Level = calc::ToRotate((crdArrayFileLevel[0]+crdArrayFileLevel[1]+crdArrayFileLevel[2]+crdArrayFileLevel[3])/4,(angle1Level+angle2Level)/2.0,crd1Level);		
		distLevel=crdArrayRealLevel[i]-crd1Level-crdRealOffsetLLevel;
		
		tempLinearLevel=sqrt(pow(distLevel.x,2)+pow(distLevel.y,2));
		if (tempLinearLevel>maxLinearLevel)
			maxLinearLevel=tempLinearLevel;
	}
	
	return maxLinearLevel;
}

BOOL CControl::DrillPrecisionTest(int nHead,int serialNumber,BOOL quitTable) 
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	Coord crd=Coord();
	long offX=0,offY=0;

	long widthX=500000,widthY=600000;
	long count=3,MatrixPoint=3,MatrixWidth=50000;

	long lengthX=widthX-MatrixWidth-20000;
	long lengthY=widthY-MatrixWidth-20000;
	long intervalX=lengthX/(count-1);//����֮���� X��215000
	long intervalY=lengthY/(count-1);//����֮���� Y��265000

	if (!(GetDoc().GetScanSize()>GetDoc().GetScanSizeMax() || GetDoc().GetScanSize()<SCANSIZEMIN))
		MatrixWidth=GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM();					//bit

	//long crdX0=240500,crdY0=373500;
	long crdX0=218500,crdY0=362500;//�����½ǵĵ�

    crdX0=crdX0-2000*(serialNumber%4);
    crdY0=crdY0-2000*(serialNumber/4);

	char ez[256]={""};

//�л���Ȧ
	MoveTo(GetDoc().GetTestAperture());	

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetTestBoardThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);	
	Delay(500);
	
	for(int j=0;j<count;j++)
    {
		for(int i=0;i<count;i++)
		{
			offX=(j%2?lengthX:0)+(j%2?-i:i)*intervalX;
			offY=j*intervalY;
			
			crd.x=crdX0-offX;
			crd.y=crdY0-offY;
			
			MoveTo(crd);
			WaitAxisStop(AXISTAB);	

			MatrixProcess(nHead,GetDoc().GetTestPlsRelease(),50,STYPE,MatrixWidth,MatrixPoint);	 
		}
	}

//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

//	if (quitTable)
//		EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));

	return true;
}
/*
BOOL CControl::DrillParamTableDelayTest(int nHead,int ntime)//jpc add 20120207
{//��ײ�����ƽ̨��ʱ����
	ASSERT(nHead==HeadLeft||nHead==HeadRight);
	Coord crd=Coord();
	long offX=0,offY=0;
	char ez[256]={""};//ly 20110404
	//��ʼ��
	m_bAbsorbedPCBLT =TRUE;
	m_bAbsorbedPCBRT =TRUE;
	
	if(nHead==HeadLeft)
	{
		m_bAbsorbedPCBRT =false;
	}
	else if(nHead==HeadRight)
	{
		m_bAbsorbedPCBLT =false;
	}	
	GetSLControl().SetLaserParam(GetDoc().GetTestPlsPeriod(),GetDoc().GetTestPlsRelease());
	GetSLControl().SetProcSpeed(GetDoc().GetProcJumpSpeed(),GetDoc().GetProcJumpDelay());
//	SetHeadCorParam(nHead,0,0,0,1.0,1.0);
	MoveToAPTAndBET(GetDoc().GetTestAperture(),GetDoc().GetTestShowAperture());		
	if(nHead==HeadLeft) //�ڹ�
	{
		// Z���½������⽹�� ׼���ӹ���
		if(GetDoc().GetTechnicType())
		{
			MoveTo(AXISLEFTZ,GetDoc().GetLongPathLaserProcFocus(0)-GetDoc().GetTestBoardThickness());
		}
		else 
		{
			MoveTo(AXISLEFTZ,GetDoc().GetLaserProcFocus(0)-GetDoc().GetTestBoardThickness());
		}
	}
	
	if(nHead == HeadRight)
	{
		// Z���½������⽹�� ׼���ӹ���		
		if(GetDoc().GetTechnicType())
		{
			MoveTo(AXISRIGHTZ,GetDoc().GetLongPathLaserProcFocus(1)-GetDoc().GetTestBoardThickness());
		}
		else
		{
			MoveTo(AXISRIGHTZ,GetDoc().GetLaserProcFocus(1)-GetDoc().GetTestBoardThickness());
		}
	}
	
	//ƽ̨��ǯ�ر�
//#ifdef TABLECLAMP
	if(GetDoc().GetTableClamp())//ly change 20120523
	{
		if(QueryIOBit(ITABLECLAMPP))
		{
			TableClampOn(false);//ChannelOutput(OTABLECLAMP,IO_ON);	
			
			time_t start_time, end_time;
			start_time = time( NULL );
			while(QueryIOBit(ITABLECLAMPP))	
			{
				end_time = time( NULL );
				if(difftime( end_time, start_time )>5)
				{
					GetDoc().SetLastWarningNo(44);
					strncpy(ez,GetLang().GetWarningText(41025),256);
					AfxMessageBox(ez);//"ƽ̨��ǯ�����쳣���޷������ӹ���������ӹ�!"
					return FALSE;
				}
			}
		}
	}
//#endif
	
	//����ϵ�
	ChannelOutput(OFANPOWERON,IO_ON); 
	
	if (nHead==HeadLeft)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
		Delay(1000);
		
		IsBoardVacOKNew(HeadLeft);
	}
	
	if (nHead==HeadRight)
	{
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		Delay(1000);
		
		IsBoardVacOKNew(HeadRight);
	}
	
	if(!(m_bAbsorbedPCBLT||m_bAbsorbedPCBRT))
	{
		strncpy(ez,GetLang().GetWarningText(41021),256);
		AfxMessageBox(ez);//"ƽ̨������������쳣���޷������ӹ���������ӹ�!"
		return false;
	}
	
	WaitAxisStop(AXISLEFTZ);
	WaitAxisStop(AXISRIGHTZ);
	Delay(300);
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	int row1=57,row2=57,range1=57000/2,range2=57000/2;
	int step=range2/(row2-1)/4;
	for (int p=0;p<4;p++)
	{
		long crdX0Move=240500,crdY0Move=373500;//373500;
		switch(p)
		{
		case 0:
			crdX0Move=245500;
			crdY0Move=393500-40000;
			break;
		case 1:
			crdX0Move=245500-40000;
			crdY0Move=393500-40000;
			break;
		case 2:
			crdX0Move=245500-40000;
			crdY0Move=393500;
			break;
		case 3:
			crdX0Move=245500;
			crdY0Move=393500;
			break;
		default:
			crdX0Move=245500;
			crdY0Move=393500;
			break;
		}
		long crdX0,crdY0;
		for (int markTimes=0;markTimes<8;markTimes++)
		{
			if (markTimes<4)
			{
				crdX0=crdX0Move-step*markTimes,crdY0=crdY0Move;//373500;
			}
			else
			{
				crdX0=crdX0Move-step*(markTimes-4),crdY0=crdY0Move+2*step;//373500;
			}
			long widthX=470000,widthY=600000;
			Coord crd0(0,0);
			switch(p)
			{
			case 0:
				crd0.x=crdX0-500;
				crd0.y=crdY0-500;
				break;
			case 1:
				crd0.x=crdX0-100000;
				crd0.y=crdY0-100000;
				break;
			case 2:
				crd0.x=crdX0-250000;
				crd0.y=crdY0-250000;
				break;
			case 3:
				crd0.x=crdX0-widthX;
				crd0.y=crdY0-widthY;
				break;
			default:
				crd0.x=crdX0-500;
				crd0.y=crdY0-500;
				break;
			}
			MoveTo(crd0);
			WaitAxisStop(AXISTAB);
			crd0.x=crdX0;
			crd0.y=crdY0;
			MoveTo(crd0);
			WaitAxisStop(AXISTAB);
			Delay(ntime+markTimes*10);
//			GetSLControl().DrillTableTest(nHead);
			
		}
	}
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
	
	EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
	return 0;
}
*/
BOOL CControl::DrillFocusTest(int nHead,BOOL bTest) 
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	Coord crd=Coord();
	long offX=0,offY=0,offZ=0;
	long intervalXY=400,intervalZ=0;
	if(bTest)
		intervalZ=100;
	else
		intervalZ=200;
	long countX=4,countY=3;
	long lengthX=intervalXY*(countX-1);
	long crdX0=-3*intervalXY/2;
	long crdY0=-intervalXY;	
	long crdZ0=intervalZ*5;	

//�л���Ȧ	
	MoveTo(GetDoc().GetTestAperture());	

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

	int k =0;
	for(int j=0;j<countY;j++)
    {
		for(int i=0;i<countX;i++)
		{
			k++;
//Z��Lens�۽�
			ZAxisLensFocus(nHead,GetDoc().GetTestBoardThickness()+crdZ0-offZ);	
					
			offX=(j%2?lengthX:0)+(j%2?-i:i)*intervalXY;
			offY=j*intervalXY;
			offZ+=intervalZ;	
			crd.x=crdX0+offX;
			crd.y=crdY0+offY;
			
			MoveTo(crd);
			WaitAxisStop(AXISTAB);	
			
			MatrixProcess(nHead,GetDoc().GetTestPlsRelease(),GetDoc().GetTestPlsPeriod(),STYPE,GetDoc().GetDefineMatrixRange(),33);

			if(k==11)
				break;
		}

		if(k==11)
			break;
	}
	
//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

//	MoveTo(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
//	WaitAxisStop(AXISTAB);
	
	return true;
}

BOOL CControl::DrillApertureTest(int nHead)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);
	
	Coord crd=Coord();
	long offX=0,offY=0;
	long intervalXY=400;
	long countX=5,countY=4;
	long lengthX=intervalXY*(countX-1);
	long crdX0=-3*intervalXY/2;
	long crdY0=-intervalXY;	
	int apnum =8;
	
#ifdef APERTURE18
	apnum =18;
#endif
	
#ifdef APERTURE12
	apnum = 12;
#endif
	
//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetTestBoardThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

	int k =0;
	for(int j=0;j<countY;j++)
    {
		for(int i=0;i<countX;i++)
		{
			k++;//���ù�Ȧ(����1-18��Ȧ�������)
			
			GetDoc().SetTestAperture(k);		
			MoveTo(GetDoc().GetTestAperture());	
			
			offX=(j%2?lengthX:0)+(j%2?-i:i)*intervalXY;
			offY=j*intervalXY;			
			crd.x=crdX0+offX;
			crd.y=crdY0+offY;
			
			MoveTo(crd);
			WaitAxisStop(AXISTAB);	
			
			MatrixProcess(nHead,GetDoc().GetTestPlsRelease(),GetDoc().GetTestPlsPeriod(),STYPE,GetDoc().GetDefineMatrixRange(),21); 	
			
			if(k==apnum)
				break;
		}
		
		if(k==apnum)
			break;
	}

//��ͷ���������ر�	
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
	
//	MoveTo(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
//	WaitAxisStop(AXISTAB);
	
	return true;
}

HANDLE CControl::InitPowerCOM()
{
	char szCOM[20]={0};
	sprintf(szCOM,"COM%d",GetDoc().GetPowerCOMNum());

	HANDLE hCom = INVALID_HANDLE_VALUE;
	hCom = GetCOM(0).OpenCOM(szCOM,9600);

	if (hCom != INVALID_HANDLE_VALUE)
	{
		char buf[1024]="msn? \r";								//Queries the serial number.
		if (0 == GetCOM(0).WriteDataToCom(buf,strlen(buf)))
		{
			GetCOM(0).CloseCOM();
			return INVALID_HANDLE_VALUE;
		}

		memset(buf,0,1024);
		if (GetCOM(0).ReadDataFromCom(buf,1024) > 0)
		{
			CString scoure=buf;
			scoure.TrimRight();
			if (scoure.GetLength()<4)
			{
				GetCOM(0).CloseCOM();
				return INVALID_HANDLE_VALUE;
			}		  
		}
		else
		{			
			GetCOM(0).CloseCOM();
			return INVALID_HANDLE_VALUE;
		}

		return hCom;
	}

	return INVALID_HANDLE_VALUE;
}

void CControl::ReleasePowerCOM()
{
	GetCOM(0).CloseCOM();
}

BOOL CControl::DrillParamFocusTest(int nHead,int iToolNo,double iTsize)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);
			
	int nApt;
	int nToolCycNum = GetDoc().GetToolPara(iToolNo,0).GetCycleNum();

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);
	Delay(500);

	for (int times=0;times<9;times++)
	{	
		if (times<4)
		{
			if (times>0)
				MoveTo(AXISTABX,GetPos(AXISTABX)+200);
		}
		else if (times<8)
		{
			if (times==4)	
				MoveTo(AXISTABY,GetPos(AXISTABY)+200);
			else
				MoveTo(AXISTABX,GetPos(AXISTABX)-200);
		}
		else
			MoveTo(AXISTABY,GetPos(AXISTABY)+200);

		WaitAxisStop(AXISTAB);	

//Z��Lens�۽�
		ZAxisLensFocus(nHead,GetDoc().GetPCBThickness()-(times-4)*100);	
		
		for(int k=0; k<nToolCycNum; ++k)
		{
			Energy eng;
			int minJump=0;	
			
			if(GetDoc().GetToolSubApertureNo(iToolNo)!=0)
			{
				if(k==0)
					nApt = GetDoc().GetToolApertureNo(iToolNo);
				else
					nApt = GetDoc().GetToolSubApertureNo(iToolNo);
			}
			else
				nApt = GetDoc().GetToolApertureNo(iToolNo);
									
			MoveTo(nApt);	

			eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);

			if (k==0)
			{
				if(GetDoc().GetFitApt())
					minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
				else
					minJump=GetDoc().GetFirstDelayPeriod(); 
			}
			else
				minJump=GetDoc().GetOtherDelayPeriod();	
			
//			MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM(),GetDoc().GetScanSize()/iTsize+1);
			MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM(),GetDoc().GetScanSize()/iTsize+1,ONLYHOLE,0,false,k==0); //20181229
		}

		Delay(1000);
	}

//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF); 

	return true;
}

BOOL CControl::DrillParamApertureTest(int nHead,int iToolNo,double iTsize)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetPCBThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);	
	Delay(500);
	
	int nApt,nAptTest;
	int nToolCycNum = GetDoc().GetToolPara(iToolNo,0).GetCycleNum();

	for (int times=0;times<5;times++)
	{
		if (times<3)
		{
			if (times>0)
				MoveTo(AXISTABX,GetPos(AXISTABX)+200);
		}
		else if (times==3)
			MoveTo(AXISTABY,GetPos(AXISTABY)+200);
		else	
			MoveTo(AXISTABX,GetPos(AXISTABX)-200);
		
		WaitAxisStop(AXISTAB);	
	
		for(int k=0; k<nToolCycNum; ++k)
		{
			Energy eng;	
			int minJump=0;
			
			if(GetDoc().GetToolSubApertureNo(iToolNo)!=0)
			{
				if(k==0)
					nApt = GetDoc().GetToolApertureNo(iToolNo);
				else
					nApt = GetDoc().GetToolSubApertureNo(iToolNo);
			}
			else
				nApt = GetDoc().GetToolApertureNo(iToolNo);				
			
			nAptTest=nApt+times-2;
			if(nAptTest<1)
				nAptTest=1;
					
			MoveTo(nAptTest);	
			
			eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);

			if (k==0)
			{
				if(GetDoc().GetFitApt())
					minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
				else
					minJump=GetDoc().GetFirstDelayPeriod(); 
			}
			else
				minJump=GetDoc().GetOtherDelayPeriod();	
			
//			MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM(),GetDoc().GetScanSize()/iTsize+1);
			MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM(),GetDoc().GetScanSize()/iTsize+1,ONLYHOLE,0,false,k==0); //20181229
		}

		Delay(1000);				
	}

//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

	return true;
}

void CControl::TableClampOn(BOOL onoff) 
{
#ifdef IO_C
	GetControl().ChannelOutput(OTABLECLAMP , onoff);
#else
	GetControl().ChannelOutput(OTABLECLAMP ,(!onoff));
#endif
}

CString CControl::IsWhatString(double scale)			//20160812
{
	std::vector<ScaleSet>::iterator ssv;
	for(int nn=0; nn<GetDoc().GetSysScaleSetSize();nn++)
	{
		ssv=GetDoc().GetSysScaleSet(nn);
		if((scale>ssv->dbDownLimit)&&(scale<=ssv->dbUpLimit))
			return ssv->strChar;
	}
	
	return "";
}
//----------------------------------------------------------------------------------------//20160919 ����
BOOL CControl::GetMatrixData(XYDataV& xyV,PATHMODE pm,long lProcRangeBit,int iPointCount,bool bPoint9)
{
	Coord point;
	XYData xyd;
/*
	int lPoint=1;

	long range=GetDoc().GetDefineMatrixRange();

	switch(mz)
	{
	case 0:
		lPoint =1;
		break;
	case 1:
		lPoint =11;
		break;
	case 2:
		lPoint =17;
		break;
	case 3:
		lPoint =21;
		break;
	case 4:
		lPoint =33;
		break;
	case 5:
		lPoint =61;
		break;
	case 6:
		lPoint=iPointCount;
		if(!bPoint9)
			range=GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM();
		break;
	default:
		lPoint =1;
		break;
	}
*/
	int arrayInt[121];			//11*11�����������	
	Coord drillpoint[121];
	if(pm==RANDOM)
	{
		iPointCount =11;
		int tempCount=0;
		bool controlInsert=FALSE;
		int randint=0;

		srand(time(NULL));
		while(true)
		{
			randint = rand() % 121; 
			if (tempCount==0)
			{
				arrayInt[tempCount]=randint;
				tempCount++;
				continue;
			}

			controlInsert=true;
			for (int i=0;i<tempCount;i++)
			{
				if (arrayInt[i]==randint)
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

			if (tempCount>(121-1))
				break;
		}
		
		int arrayCheck[121];		//������ɵ���������Ƿ���ȷ

		for (int checkNumber=0;checkNumber<121;checkNumber++)
		{
			arrayCheck[checkNumber]=arrayInt[checkNumber];
		}

		InsertSort(arrayCheck,121);

		for (int judge=0;judge<121;judge++)
		{
			if (arrayCheck[judge]!=judge)
			{
				AfxMessageBox("����������ɴ������ٴγ���!");
				return false;
			}
		}	
	}
	
	if(iPointCount==1)
	{
		xyd.coordX=0;
		xyd.coordY=0;
		xyd.laserON=true;
		xyV.push_back(xyd);
	}
	else
	{
		for(int j=0;j<iPointCount;j++)
		{
			for(int i=0;i<iPointCount;i++)
			{
				if((j!=(iPointCount-1)/2) || (i !=(iPointCount-1)/2))
				{
//					point.x=(short)((j%2?-lProcRangeBit:lProcRangeBit)/2 + (j%2?i:-i)*lProcRangeBit/(iPointCount-1));
//					point.y=(short)(-lProcRangeBit/2 + j*lProcRangeBit/(iPointCount-1));
					point.x=(long)((j%2?-lProcRangeBit:lProcRangeBit)/2 + (j%2?i:-i)*lProcRangeBit/(iPointCount-1));	//20200119
					point.y=(long)(-lProcRangeBit/2 + j*lProcRangeBit/(iPointCount-1));
					
					if(pm==NTYPE)
					{
						xyd.coordX=point.x;
						xyd.coordY=point.y;
						xyd.laserON=true;
						xyV.push_back(xyd);
					}
					else if(pm==STYPE)
					{     
						xyd.coordX=point.y;
						xyd.coordY=point.x;
						xyd.laserON=true;
						xyV.push_back(xyd);					
					}
					else if(pm==RANDOM)
					{
						drillpoint[j*iPointCount+i]=point;
					}
					else if(pm==NOPPOSITE)
					{
						xyd.coordX=-point.x;
						xyd.coordY=-point.y;
						xyd.laserON=false;
						xyV.push_back(xyd);
						
						xyd.coordX=point.x;
						xyd.coordY=point.y;
						xyd.laserON=true;
						xyV.push_back(xyd);
					}
					else if(pm==SOPPOSITE)
					{
						xyd.coordX=-point.y;
						xyd.coordY=-point.x;
						xyd.laserON=false;
						xyV.push_back(xyd);
						
						xyd.coordX=point.y;
						xyd.coordY=point.x;
						xyd.laserON=true;
						xyV.push_back(xyd);
					}
					else
					{
						AfxMessageBox("��·�������趨��Ч����ȷ��!");
						return false;
					}
				}
				else
				{
					xyd.coordX=0;
					xyd.coordY=0;
					xyd.laserON=true;
					xyV.push_back(xyd);
				}
			}
		}
		
		if(pm==RANDOM)
		{
			for (int index=0;index<121;index++)
			{
//				xyd.coordX=-drillpoint[arrayInt[index]].x;
//				xyd.coordY=-drillpoint[arrayInt[index]].y;
//				xyd.laserON=false;
//				xyV.push_back(xyd);
				
				xyd.coordX=drillpoint[arrayInt[index]].x;
				xyd.coordY=drillpoint[arrayInt[index]].y;
				xyd.laserON=true;
				xyV.push_back(xyd);
			}
		}

		if(bPoint9)
		{
//			Coord point;										//20200119 ȡ��
			std::vector<XYData>::iterator xyVit;
			
			for(int m=0;m<xyV.size();m++)
			{
				xyVit=xyV.begin()+m;
				point.x=xyVit->coordX;
				point.y=xyVit->coordY;	
				
				if(IsPoint3(point,lProcRangeBit))
					xyVit->laserON=true;
				else
					xyVit->laserON=false;
			}
		}
	}

	return true;
}

BOOL CControl::GetSubData(XYDataV& xySubV,POINTTYPE pt,int iToolNo,CString str,TextDir Dir)
{
	switch(pt)
	{
	case 0:
		break;
	case 1:
		GetCrossSubData(xySubV);
		break;
	case 2:
		GetCircleRingSubData(xySubV);
		break;
	case 3:
		GetCircleWindowSubData(xySubV,iToolNo);
		break;
	case 4:
		GetRectWindowSubData(xySubV);
		break;
	case 5:
		GetStringSubData(xySubV,str,Dir);
		break;
	default:
		AfxMessageBox("����״�����趨��Ч����ȷ��!");
		return false;
	}
	return true;
}

void CControl::InsertSort(int a[],int count)
{//����
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

void CControl::GetCrossSubData(XYDataV& xySubV)
{
	int interval=GetDoc().GetDrlRegionPointDis()*GetDoc().GetSLBitPerMM()/1000.0;
	XYData xyd;
	
	for(int n=-15;n<16;++n)
	{
		xyd.coordX=n*interval;
		xyd.coordY=0;
		xyd.laserON=true;
		xySubV.push_back(xyd);			
	}
	
	for(int m=-15;m<16;++m) 
	{
		if(m!=0)
		{
			xyd.coordX=0;
			xyd.coordY=m*interval;
			xyd.laserON=true;
			xySubV.push_back(xyd);	
		}
	}
}

void CControl::GetCircleRingSubData(XYDataV& xySubV)
{

}

void CControl::GetCircleWindowSubData(XYDataV& xySubV,int iToolNo)
{
	XYData xyd;

	if (GetDoc().arrayBigHoleCPoint[iToolNo].GetSize()>0)
	{
		Coord  codArray(0,0);	
		for (int ii=0;ii<GetDoc().arrayBigHoleCPoint[iToolNo].GetSize();ii++)
		{
			codArray=GetDoc().arrayBigHoleCPoint[iToolNo].GetAt(ii);
			xyd.coordX=codArray.x;
			xyd.coordY=codArray.y;
			xyd.laserON=true;
			xySubV.push_back(xyd);	
		}			
	}
}

void CControl::GetRectWindowSubData(XYDataV& xySubV)
{
	XYData xyd;
	Coord point;
	int range=GetDoc().GetRegionDim()*GetDoc().GetSLBitPerMM()/2000.0;
	int disRegion=GetDoc().GetDrlRegionPointDis()*GetDoc().GetSLBitPerMM()/1000.0;
//	bool noSort=true;																	//20170103	20170224
//	int disRegionHeight=times*disRegion*1.732/2.0/3.0;
//	int disRegionWidth=movePoint*disRegion/3.0+times*disRegion/2.0;	
	int controlLine=0;
	int sortMark=0;
	
	int row=0;
	int line=0;
//	for(int n=-range+disRegionHeight; n<=(int)(range+disRegionHeight); n+=(int)(disRegion*1.732/2.0))
	for(int n=-range; n<=range; n+=(int)(disRegion*1.732/2.0))
	{ 
		line++;
	}
	
	row=0;
	for(int m=-range; m<=range; m+=disRegion)
	{  	
		row++;	
	}
	
	Coord *coilsSortPoint=new Coord[row*line];
	controlLine=0;
	sortMark=0;	
	
	for( int nn=-range; nn<=range; nn+=(int)(disRegion*1.732/2.0))
	{ 
		controlLine++;	
		
		for(int mm=-range; mm<=range; mm+=disRegion)
		{  	
			if (controlLine%2==0)
			{
				coilsSortPoint[sortMark].x=nn;

				if(GetDoc().GetDrillCoil())
					coilsSortPoint[sortMark].y=mm+disRegion/2;		//20170103	20170224
				else
					coilsSortPoint[sortMark].y=-mm+disRegion/2;		//mm+disRegion/2		//20170103
			}
			else
			{
				coilsSortPoint[sortMark].x=nn;
				coilsSortPoint[sortMark].y=mm;
			}	
			sortMark++;
		}
	}
	
//	if (noSort)
	if(!GetDoc().GetDrillCoil())										//20170224
	{
		for (int i=0;i<line;i++)
		{
			for (int j=0;j<row;j++)
			{
//				JumpLaserOnInListFirst(coilsSortPoint[i*row+j].x,coilsSortPoint[i*row+j].y);
				xyd.coordX=coilsSortPoint[i*row+j].x;
				xyd.coordY=coilsSortPoint[i*row+j].y;
				xyd.laserON=true;
				xySubV.push_back(xyd);
				
			}
		}
		
		delete coilsSortPoint;
	}
	else
	{
		Coord *sortArray=ArrayCoilsNew(row,line,coilsSortPoint);
		for (int i=0;i<line;i++)
		{
			for (int j=0;j<row;j++)
			{
//				JumpLaserOnInListFirst(sortArray[i*row+j].x,sortArray[i*row+j].y);
				xyd.coordX=sortArray[i*row+j].x;
				xyd.coordY=sortArray[i*row+j].y;
				xyd.laserON=true;
				xySubV.push_back(xyd);
				
			}
		}
		
		delete coilsSortPoint;
		delete sortArray;
	}
}

void CControl::GetStringSubData(XYDataV& xySubV,CString str,TextDir Dir)
{
	XYData xyd;
	Coord point;

	int fontHeight=GetDoc().GetStrZoomSn()*GetDoc().GetSLBitPerMM();				//20180907 �޸�
//	int fontWidth=fontHeight*3/4;

//	int fontHeight=GetDoc().GetTextHeigth()*GetDoc().GetSLBitPerMM();				//20170118 �޸�				
	int fontWidth=fontHeight*FONTRATIO;

	int offset=GetDoc().GetScanSize()*GetDoc().GetSLBitPerMM()/2;

	const char buf[41]="1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ-/:.";	
	
	FILE* fp;	
//  CString strScr = GetDoc().GetAppPath()+"\\string.fnt";						//8*8�ַ�
    CString strScr = GetDoc().GetAppPath()+"\\string_7x7.fnt";					//7*7�ַ�

	int fontMatrixSize=7;														//�����ʽ��������е�����
	int fontRowSize=fontMatrixSize+1;											//��������ÿ�е��ַ�����˵���ڼ��·�
	int fontColumnSize=fontMatrixSize;											//��������ÿ�е��ַ���
	int fontStreamSize=fontRowSize*fontColumnSize;								//�������е��ַ�����

	if(!(fp=fopen(strScr,"r")))
	{
		GetDoc().SetLastWarningNo(63);			//"�ַ������ļ�δ�����򿪣���ȷ��!"
		return;
	}
	
//	char chbuf[72];
	char chbuf[56];																
	char* pch;
	int chPos;	
	for(int i=0; i < str.GetLength(); ++i)
	{
		pch = strchr(buf,toupper(str.GetAt(i)));
		if(pch==NULL) continue;
		chPos = pch - buf ;
//		fseek(fp,80*chPos,SEEK_SET);									//����LF��CR���ַ��������ļ���ÿ��10���ַ�
		fseek(fp,(fontMatrixSize+2)*fontMatrixSize*chPos,SEEK_SET);		//����LF��CR���ַ��������ļ���ÿ�ж������ַ�
		fread(&chbuf,sizeof(char),fontStreamSize,fp);					//If the given stream is opened in text mode, carriage return�Clinefeed pairs 
																		//are replaced with single linefeed characters.
		for(int j=0; j<fontStreamSize; ++j)
		{
			if(chbuf[j]=='1')
			{
				if(HorizontalText == Dir)
				{
//					point.y = i*fontWidth+fontWidth*(j%9+1)/9;
					point.y = i*fontWidth+fontWidth*(j%fontRowSize+1)/fontRowSize-offset;					//20170118 �޸�
					point.x = - (fontHeight-fontHeight*(j/fontRowSize)/fontColumnSize);
				}
				else if(VerticalText==Dir)
				{
					point.y = - (fontHeight-fontHeight*(j/fontRowSize)/fontColumnSize);
//					point.x = -(i*fontWidth+fontWidth*(j%9+1)/9);
					point.x = -(i*fontWidth+fontWidth*(j%fontRowSize+1)/fontRowSize)+offset;				//20170118 �޸�					
				}
				
				xyd.coordX=point.x;
				xyd.coordY=point.y;
				xyd.laserON=true;
				xySubV.push_back(xyd);
			}
		}
	}

	fclose(fp);	
}

Coord * CControl::ArrayCoilsNew(int row,int line,Coord *sortPoint)
{//����
	int **a;  
	a=new int *[line];
	for (int aCount=0;aCount<line;aCount++)
	{
		a[aCount]=new int[row];
	}	
	int   i=0,j=0;  
	int   m=1;   
	bool   bRight=true;  
	int   x1=row,y1=line-1;
	while(m<=row*line)  
	{  
		int   k=0;  
		if(bRight)  
		{  
			for(k=0;k<x1;++k)//r  
			{  
				a[i][j]=m++;  
				j++; 
			}  
			i++;j--;  
			for(k=0;k<y1;++k)//b  
			{  
				a[i][j]=m++;  
				i++;  
			}   
			i--;j--;  
			bRight=!bRight; 
			x1--;y1--;  
		}  
		else  
		{  
			for(k=0;k<x1;++k)//l  
			{  
				a[i][j]=m++;  
				j--;  
			}  
			i--;j++;  
			for(k=0;k<y1;++k)//t  
			{  
				a[i][j]=m++;  
				i--;  
			}  
			i++;j++;  
			bRight=!bRight; 
			x1--;y1--;  
		}  
	}  
	Coord  *resultPoint;
	resultPoint=new Coord[line*row];
	for (i=0;i<line;i++)
	{
		for (int j=0;j<row;j++)
		{
            resultPoint[a[i][j]-1]=sortPoint[i*row+j];
		}
	}
	
	delete []a;
	return resultPoint;
}

BOOL CControl::IsPoint3(Coord point,long width)//jpc add 20130304
{
	Coord point3;	
    for(int j=0;j<3;j++)
    {
		for(int i=0;i<3;i++)
		{
//			point3.x=(short)((j%2?-width:width)/2 + (j%2?i:-i)*width/(3-1));
//			point3.y=(short)(-width/2 + j*width/(3-1));
			point3.x=(long)((j%2?-width:width)/2 + (j%2?i:-i)*width/(3-1));		//20200119
			point3.y=(long)(-width/2 + j*width/(3-1));
			
			if(point.x==point3.x&&point.y==point3.y)
				return true;
		}
	}	
	return false;
}

//�ع��ӹ����̣�20161123
BOOL CControl::TableClampOperate(BOOL onoff,BOOL bHasTableClamp) 
{
	if(bHasTableClamp)
	{
		char ez[256]={""};
		time_t start_time, end_time;

		if(onoff)
		{
			if(QueryIOBit(ITABLECLAMPN))
			{
#ifdef IO_C
				ChannelOutput(OTABLECLAMP,IO_ON);				//ƽ̨��ǯ��
#else
				ChannelOutput(OTABLECLAMP,IO_OFF);
#endif
				
				start_time = time( NULL );
				while(QueryIOBit(ITABLECLAMPN))					//ƽ̨��ǯ�򿪣�
				{
					end_time = time( NULL );
					if(difftime( end_time, start_time )>5)
					{
						GetDoc().SetLastWarningNo(75);
						strncpy(ez,GetLang().GetWarningText(41025),256);
						AfxMessageBox(ez);						//"ƽ̨��ǯ�����쳣���޷������ӹ���������ӹ�!"
						return false;
					}
				}
			}
		}
		else
		{
			if(QueryIOBit(ITABLECLAMPP))
			{
#ifdef IO_C
				ChannelOutput(OTABLECLAMP,IO_OFF);				//ƽ̨��ǯ�ر�
#else
				ChannelOutput(OTABLECLAMP,IO_ON);
#endif						
				
				end_time = start_time = time( NULL );
				while(QueryIOBit(ITABLECLAMPP))					//ƽ̨��ǯ�ѹرգ�
				{
					end_time = time( NULL );
					if(difftime( end_time, start_time )>5)
					{
						GetDoc().SetLastWarningNo(75);
						strncpy(ez,GetLang().GetWarningText(41025),256);
						AfxMessageBox(ez);						//"ƽ̨��ǯ�����쳣���޷������ӹ���������ӹ�!"
						return false;
					}
				}
			}
		}
	}

	return true;
}

BOOL CControl::TableAdsorbInProc(int nHead)
{
	char ez[256]={""};
	
	if(!TableClampOperate(false,GetDoc().GetTableClamp()))	//�رռ�ǯ
		return false;

	if(nHead==HeadBoth)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		Delay(1000);
		
		if(!IsBoardVacOKNew(HeadLeft))
			return false;
		
		if(!IsBoardVacOKNew(HeadRight))
			return false;
	}
	
	if (nHead==HeadLeft)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
		Delay(1000);
		
		if(!IsBoardVacOKNew(HeadLeft))
			return false;
	}
	
	if (nHead==HeadRight)
	{
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		Delay(1000);
		
		if(!IsBoardVacOKNew(HeadRight))
			return false;
	}
}
/*
BOOL CControl::ThicknessMeasureInProc(int nHead,BOOL bUseAlarm)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	long boardThickness=0;
	long lThickTest[2]={0,0};
	char ez[256]={""};

	if(!TestThicknessAL(lThickTest,nHead))
	{
		strncpy(ez,GetLang().GetWarningText(41024),256);
		AfxMessageBox(ez);										//"�����������쳣���޷������ӹ���������ӹ�!"
		return false;
	}
		
	if(bUseAlarm)
	{
		BOOL bIsLeftThicknessNG=false;
		BOOL bIsRightThicknessNG=false;
		
		if(nHead==HeadBoth)
		{
			if(abs(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				bIsLeftThicknessNG=true;
				GetDoc().SetLastWarningNo(73);					//"���������ƫ�����"					
//				return false;
			}
			
			if(abs(GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				bIsRightThicknessNG=true;
				GetDoc().SetLastWarningNo(74);					//"���������ƫ�����"					
//				return false;
			}

			if(bIsLeftThicknessNG||bIsRightThicknessNG)
				return false;
		}
		else if(nHead==HeadLeft)
		{
			if(abs(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				GetDoc().SetLastWarningNo(73);					//"���������ƫ�����"					
				return false;
			}
		}
		else if(nHead==HeadRight)
		{
			if(abs(GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				GetDoc().SetLastWarningNo(74);					//"���������ƫ�����"					
				return false;
			}
		}
	}
	
	if(nHead==HeadBoth)
		boardThickness=(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft)+GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight))/2;
	else if(nHead==HeadLeft)
		boardThickness=GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft);
	else if(nHead==HeadRight)
		boardThickness=GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight);
	
	GetDoc().SetPCBThickness(boardThickness);
	
#ifdef USELOG
	CString str;
				
	if(nHead==HeadBoth)
		str.Format("ZL%d,ZR%d",GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft),GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight));
	else if(nHead==HeadLeft)
		str.Format("ZL%d,ZR%d",GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft),0);
	else if(nHead==HeadRight)
		str.Format("ZL%d,ZR%d",0,GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight));
				
	GetLog().Append_pro(str,20028);								//"���"
#endif

	return true;
}
*/
BOOL CControl::ThicknessMeasureInCali(int nHead)				//20190725
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	long boardThickness=0;
	long lThickTest[2]={0,0};
	char ez[256]={""};

	if(!TestThicknessAL(lThickTest,nHead,Coord(-90000,-440000)))
	{
		strncpy(ez,GetLang().GetWarningText(41024),256);
		AfxMessageBox(ez);										//"�����������쳣���޷������ӹ���������ӹ�!"
		return false;
	}

	BOOL bIsLeftThicknessNG=false;
	BOOL bIsRightThicknessNG=false;
	
	if(nHead==HeadBoth)
	{
		if(abs(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]-GetDoc().GetGalvoBoardThick())>2*GetDoc().GetAutoThickError())
		{
			bIsLeftThicknessNG=true;
			GetDoc().SetLastWarningNo(73);					//"���������ƫ�����"					
//			return false;
		}
		
		if(abs(GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]-GetDoc().GetGalvoBoardThick())>2*GetDoc().GetAutoThickError())
		{
			bIsRightThicknessNG=true;
			GetDoc().SetLastWarningNo(74);					//"���������ƫ�����"					
//			return false;
		}
	}
	else if(nHead==HeadLeft)
	{
		if(abs(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]-GetDoc().GetGalvoBoardThick())>2*GetDoc().GetAutoThickError())
		{
			bIsLeftThicknessNG=true;
			GetDoc().SetLastWarningNo(73);					//"���������ƫ�����"					
//			return false;
		}
	}
	else if(nHead==HeadRight)
	{
		if(abs(GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]-GetDoc().GetGalvoBoardThick())>2*GetDoc().GetAutoThickError())
		{
			bIsRightThicknessNG=true;
			GetDoc().SetLastWarningNo(74);					//"���������ƫ�����"					
//			return false;
		}
	}

	if(bIsLeftThicknessNG||bIsRightThicknessNG)
		return false;

	return true;
}

BOOL CControl::ThicknessMeasureInProc(int nHead,BOOL bUseAlarm)											//20190109 �޸�
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	long boardThickness=0;
	long lThickTest[2]={0,0};
	char ez[256]={""};

//	if(!TestThicknessAL(lThickTest,nHead))
	if(!TestThicknessAL(lThickTest,nHead,Coord(GetDoc().GetThicknessX(),GetDoc().GetThicknessY())))		//20190725
	{
		strncpy(ez,GetLang().GetWarningText(41024),256);
		AfxMessageBox(ez);										//"�����������쳣���޷������ӹ���������ӹ�!"
		return false;
	}

	BOOL bIsLeftThicknessNG=false;
	BOOL bIsRightThicknessNG=false;
		
	if(bUseAlarm)
	{	
		if(nHead==HeadBoth)
		{
			if(abs(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				bIsLeftThicknessNG=true;
				GetDoc().SetLastWarningNo(73);					//"���������ƫ�����"					
//				return false;
			}
			
			if(abs(GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				bIsRightThicknessNG=true;
				GetDoc().SetLastWarningNo(74);					//"���������ƫ�����"					
//				return false;
			}
		}
		else if(nHead==HeadLeft)
		{
			if(abs(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				bIsLeftThicknessNG=true;
				GetDoc().SetLastWarningNo(73);					//"���������ƫ�����"					
//				return false;
			}
		}
		else if(nHead==HeadRight)
		{
			if(abs(GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight)-GetDoc().GetPCBThicknessStd())>GetDoc().GetAutoThickError())
			{
				bIsRightThicknessNG=true;
				GetDoc().SetLastWarningNo(74);					//"���������ƫ�����"					
//				return false;
			}
		}
	}

#ifdef USELOG
	CString str;
				
	if(nHead==HeadBoth)
		str.Format("ZL%d,ZR%d",GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft),GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight));
	else if(nHead==HeadLeft)
		str.Format("ZL%d,ZR%d",GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft),0);
	else if(nHead==HeadRight)
		str.Format("ZL%d,ZR%d",0,GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight));
				
	GetLog().Append_pro(str,20028);								//"���"
#endif

	if(bIsLeftThicknessNG||bIsRightThicknessNG)
		return false;
	
	if(nHead==HeadBoth)
		boardThickness=(GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft)+GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight))/2;
	else if(nHead==HeadLeft)
		boardThickness=GetDoc().GetThicknessZero(HeadLeft)-lThickTest[HeadLeft]+GetDoc().GetTestThicknessCompensation(HeadLeft);
	else if(nHead==HeadRight)
		boardThickness=GetDoc().GetThicknessZero(HeadRight)-lThickTest[HeadRight]+GetDoc().GetTestThicknessCompensation(HeadRight);
	
	GetDoc().SetPCBThickness(boardThickness);

	return true;
}

BOOL CControl::CalibrationInProc(int nHead)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	char ez[256]={""};
//	BOOL autoAdjustStatus=false;
//	BOOL autoPowerStatus=false;
//------------------------------------------------
	if(GetDoc().GetEnAutoAdjust())
	{
//		if(nHead==HeadBoth)
//			autoAdjustStatus=GetDoc().GetAutoAdjustPattern(HeadLeft)||GetDoc().GetAutoAdjustPattern(HeadRight);
//		else
//			autoAdjustStatus=GetDoc().GetAutoAdjustPattern(nHead);
		
//		if(autoAdjustStatus)
		if(GetDoc().GetAutoGalvoAdjustIsTimed())								//20190711
		{
			if(!AutoAdjustPattern(nHead))
			{
				strncpy(ez,GetLang().GetWarningText(41022),256);
				AfxMessageBox(ez);							//"�Զ���У�������쳣���޷������ӹ���������ӹ�!"

				GetDoc().WriteCaliTimes();
				LightTurnOff();

				return false;
			}
		}
	}
	else
	{
/*
		if(nHead==HeadBoth)	//˫��ӹ�ģʽ
		{
			BOOL bIsLeftGalvoNG=false;
			BOOL bIsRightGalvoNG=false;

			if(GetDoc().GetAutoAdjustPattern(HeadLeft))
			{
				bIsLeftGalvoNG=true;
//				GetDoc().SetLastWarningNo(49);				//"����δ������У�������᲻���мӹ�!";
			}			
			
			if(GetDoc().GetAutoAdjustPattern(HeadRight))
			{
				bIsRightGalvoNG=true;
//				GetDoc().SetLastWarningNo(50);				//"����δ������У�������᲻���мӹ�!";
			}
			
			if(bIsLeftGalvoNG||bIsRightGalvoNG)				//20170411 ����ӹ�ģʽ�£�����һ�������δУ��״̬���ܾ��ӹ�
			{
				strncpy(ez,GetLang().GetWarningText(21053),256);
				AfxMessageBox(ez);							//"��δ����У�����޷������ӹ���������ӹ�!"
				return false;
			}
		}
		else				//����ӹ�ģʽ
		{
			if(GetDoc().GetAutoAdjustPattern(nHead))
			{
				strncpy(ez,GetLang().GetWarningText(21053),256);
				AfxMessageBox(ez);							//"��δ����У�����޷������ӹ���������ӹ�!"
				return false;
			}			
		}
*/
		if(GetDoc().GetAutoGalvoAdjustIsTimed())								//20190711
		{
			strncpy(ez,GetLang().GetWarningText(21053),256);
			AfxMessageBox(ez);								//"��δ����У�����޷������ӹ���������ӹ�!"
			return false;
		}
	}

	if(!PeekRunState())
		return FALSE;
//--------------------------------------------------
	if(GetDoc().GetEnAutoPower())
	{
//		if(nHead==HeadBoth)
//			autoPowerStatus=GetDoc().GetAutoLaserPowerTest(HeadLeft)||GetDoc().GetAutoLaserPowerTest(HeadRight);
//		else
//			autoPowerStatus=GetDoc().GetAutoLaserPowerTest(nHead);
		
//		if(autoPowerStatus)
		if(GetDoc().GetAutoLaserTestIsTimed())									//20190711
		{
			if(GetDoc().GetFileLPTest())
			{
				if(!AutoFileLaserPower(nHead,0))
				{
					strncpy(ez,GetLang().GetWarningText(41023),256);
					AfxMessageBox(ez);									//"�Զ����ʲ��������쳣���޷������ӹ���������ӹ�!"
					return false;
				}
			}
			else
			{
				if(!AutoLaserPower(nHead,0))
				{
					strncpy(ez,GetLang().GetWarningText(41023),256);
					AfxMessageBox(ez);									//"�Զ����ʲ��������쳣���޷������ӹ���������ӹ�!"
					return false;
				}
			}
		}
	}
	else
	{
/*
		if(nHead==HeadBoth)	//˫��ӹ�ģʽ
		{
			BOOL bIsLeftPowerNG=false;
			BOOL bIsRightPowerNG=false;

			if(GetDoc().GetAutoLaserPowerTest(HeadLeft))
			{
				bIsLeftPowerNG=true;
				GetDoc().SetLastWarningNo(51);				//"����δ���м��⹦�ʲ���!";
			}			
			
			if(GetDoc().GetAutoLaserPowerTest(HeadRight))
			{
				bIsRightPowerNG=true;
				GetDoc().SetLastWarningNo(52);				//"����δ���м��⹦�ʲ���!";
			}
			
			if(bIsLeftPowerNG||bIsRightPowerNG)				//20170411 ����ӹ�ģʽ�£�����һ����ֹ���δ����״̬���ܾ��ӹ�
			{
				strncpy(ez,GetLang().GetWarningText(21054),256);
				AfxMessageBox(ez);							//"���⹦��δ���в��ԣ��޷������ӹ���������ӹ�!"
				return false;
			}
		}
		else				//����ӹ�ģʽ
		{
			if(GetDoc().GetAutoLaserPowerTest(nHead))
			{
				strncpy(ez,GetLang().GetWarningText(21054),256);
				AfxMessageBox(ez);							//"���⹦��δ���в��ԣ��޷������ӹ���������ӹ�!"
				return false;
			}			
		}
*/
		if(GetDoc().GetAutoLaserTestIsTimed())									//20190711
		{
			strncpy(ez,GetLang().GetWarningText(21054),256);
			AfxMessageBox(ez);								//"���⹦��δ���в��ԣ��޷������ӹ���������ӹ�!"
			return false;
		}
	}

	return true;
}

BOOL CControl::AutoAdjustPattern(int nHead,bool isForTest,bool isOnlyOffset)							//20170411
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	bool bCenterOk,bMatrixOk;
	Coord3D crd3d,CCDToGlvOffSet;

//�Զ���У��ǰ����һ�ι�Ȧ����
//	GetControl().HomeAPT();
//	Delay(500);

//�Զ����
	if(GetDoc().GetThickingType())						//˫��ӹ�ʱ���������һ��δͨ����false			//20190725 ����
	{
		if(!ThicknessMeasureInCali(nHead))
			return false;
		
		if(!PeekRunState())
			return false;
	}

#ifdef SMCAdjust
	CString galvoPath="";
	CString strOldCTB;
	CString strNewCTB;
	
	char oldCTB[MaxPathLen];
	char newCTB[MaxPathLen];
	
	CFileFind fileFind;
	BOOL isFind=false;
	
	if(GetDoc().GetTechnicType())
		galvoPath= GetDoc().GetAppPath()+"LPathC\\";
	else
		galvoPath= GetDoc().GetAppPath()+"SPathC\\";

//��ɾ���ɵģ��ٸ����µ�
	isFind=false;
	strOldCTB=galvoPath+"CorL.ctb";
	sprintf(oldCTB,"%s",strOldCTB);
	isFind=fileFind.FindFile(oldCTB);
	if (isFind)
		DeleteFile(oldCTB);
	
	strNewCTB=galvoPath+"Backup\\CorL.ctb";
	sprintf(newCTB,"%s",strNewCTB);
	CopyFile(newCTB,oldCTB,false);

	isFind=false;
	strOldCTB=galvoPath+"CorR.ctb";
	sprintf(oldCTB,"%s",strOldCTB);
	isFind=fileFind.FindFile(oldCTB);
	if (isFind)
		DeleteFile(oldCTB);
	
	strNewCTB=galvoPath+"Backup\\CorR.ctb";
	sprintf(newCTB,"%s",strNewCTB);
	CopyFile(newCTB,oldCTB,false);
	
	fileFind.Close();
#endif

//�ӹ���ģʽ�趨
	int start=0;
	int end=2;
	int mTimes=2;
	GetDoc().SetAutoAdjustPattern(true,HeadLeft);				//true:��ҪУ������ʱ��NG��false:����У������ʱ��OK
	GetDoc().SetAutoAdjustPattern(true,HeadRight);

	if(nHead==HeadLeft)
	{
		start=0;
		end=1;
	}
	
	if(nHead==HeadRight)
	{
		start=1;
		end=2;
	}

//��CCD��Դ
	LightTurnOn(GALNOMATRIX);

//��ʼ���Զ�У��
	if (isForTest)	
		GetDoc().AccuracyTestChangeRow(nHead);

	if(isOnlyOffset)
		mTimes=1;

	bool bOK[2];
	bOK[HeadLeft]=false;
	bOK[HeadRight]=false;

	for(int i=start;i<end;i++)
	{
		crd3d.x = GetDoc().GetCCDToGlvSysOffset(i).x;
		crd3d.y = GetDoc().GetCCDToGlvSysOffset(i).y;
		crd3d.z = GetDoc().GetCCDFocus(i)-GetDoc().GetGalvoBoardThick();

		CCDToGlvOffSet.x = GetDoc().GetGlvAdjPosX();
		CCDToGlvOffSet.y = GetDoc().GetGlvAdjPosY();

		if((i==1)&&(GetDoc().GetLargeTable()==1))	//��̨����͵���У�����������̨����м䣬������̨������м�ƫ�ϣ���̨�������м�ƫ��
		{
			CCDToGlvOffSet.x+=TABADJRTLX;
			CCDToGlvOffSet.y+=TABADJRTLY;
		}
		
		if(GetDoc().GetTechnicType())
			CCDToGlvOffSet.z = GetDoc().GetLongPathLaserProcFocus(i)-GetDoc().GetGalvoBoardThick();
		else
			CCDToGlvOffSet.z = GetDoc().GetLaserProcFocus(i)-GetDoc().GetGalvoBoardThick();	

#ifdef RTC5DLL										//20191216
	BOOL bOnceAgain=false;							//20191106
#else
	BOOL bOnceAgain=true;
#endif

	for(int n=0;n<2;n++)
	{
		for(int m=0;m<mTimes;m++)
		{
			if(m==0)
			{
				for(int k=0;k<4;k++)				//��Ч��λ���+У������ѭ������4��
				{
					bCenterOk = true;
					
					if(GetControl().GlovaCalibrateOffset(CCDToGlvOffSet,crd3d,i,bCenterOk,k))	//true��У��ͨ������У���������쳣��
					{						
						if(bCenterOk)				//true��У��ͨ����false��У���������쳣�����У�������ظ���δ���
						{
							if (!GetDoc().IsGlovCalibOffstOutofTol(crd3d,i))	//У��ͨ���󣬴˴�ԭ��У��������ϴ�ƫ����󣬱��������ѭ��
							{
								if(i==0)
									GetDoc().SetLastWarningNo(96);				//"��������������ԭ��У��ƫ�����"

								if(i==1)
									GetDoc().SetLastWarningNo(97);				//"��������������ԭ��У��ƫ�����"
								
								int nSel=AfxMessageBox("��ѡ���Ƿ��������У����������ѡ���ǡ����˳���ѡ���񡱣�",MB_YESNO);	//20190828
								
								if(nSel==IDNO)
									return false;
							}

							GetDoc().SetCCDToGlvSysOffset(crd3d,i);
							break;	
						}
					}
					else							//false��У���������������������У����ͼ��ʶ��ʧ�ܣ����������ѭ��
					{						
//						if(i==0)
//							GetDoc().SetLastWarningNo(91);						//"������ԭ��У�����ִ���"

//						if(i==1)
//							GetDoc().SetLastWarningNo(92);						//"������ԭ��У�����ִ���"
						
						return false;
					}
				}

				if(!bCenterOk)			//break��true��У��ͨ������Ч��λ���+У��4�κ�false��У���������쳣�����У�������ظ���δ��꣬���������ѭ��
				{
					if(i==0)
						GetDoc().SetLastWarningNo(93);							//"������ԭ��У�����������Ҫ��"

					if(i==1)
						GetDoc().SetLastWarningNo(94);							//"������ԭ��У�����������Ҫ��"

					return false;
				}
			}
			else if(m==1)
			{
//-----------------------------------------------------------------------//���ԭ�е� //20190311
				char ctbBackup[MaxPathLen];										
				char dataBackup[MaxPathLen];
				
				CString strCTBBackup;
				CString strDataBackup;
				
				CString CurPath="";
				
				if(GetDoc().GetTechnicType())
					CurPath= "LPathC\\";
				else
					CurPath= "SPathC\\";
				
#ifdef RTC5DLL
				if(i==0)
				{
					strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorL";
					strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_auto5L";
				}

				if(i==1)
				{
					strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorR";
					strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_auto5R";
				}
#else
				if(i==0)
				{
					strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorL";
					strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_autoL";
				}

				if(i==1)
				{
					strCTBBackup=GetDoc().GetAppPath()+CurPath+"CorR";
					strDataBackup=GetDoc().GetAppPath()+CurPath+"Cor_autoR";			
				}
#endif		
				for(int nn=0; nn<4; ++nn)
				{
#ifdef RTC5DLL
					sprintf(ctbBackup,"%s%d.ct5",strCTBBackup,nn);
#else
					sprintf(ctbBackup,"%s%d.ctb",strCTBBackup,nn);
#endif
					sprintf(dataBackup,"%s%d.dat",strDataBackup,nn);

					DeleteFile(ctbBackup);
					DeleteFile(dataBackup);
				}
//----------------------------------------------------------------------
				for(int j=0;j<4;j++)				//��Ч��λ���+У������ѭ������4��
				{
					bMatrixOk = true;
					
					if(GetControl().GlovaAutoCalibrate(CCDToGlvOffSet,crd3d,i,bMatrixOk,j,isForTest))	//true��У��ͨ������У���������쳣��
					{					
//						if(bCenterOk&&bMatrixOk)
						if(bMatrixOk)				//true��У��ͨ����false��У���������쳣�����У������δ���
						{
							GetDoc().SetCCDToGlvSysOffset(crd3d,i);					//20200226 ȡ�� 20200227�ָĻ�

							bOK[i]=true;
							break;	
						}
					}
					else							//false��У���������������������У����ͼ��ʶ��ʧ�ܣ����������ѭ��
					{
						if(i==0)
							GetDoc().SetLastWarningNo(79);							//"�����񾵵���У�����ִ���"

						if(i==1)
							GetDoc().SetLastWarningNo(80);							//"�����񾵵���У�����ִ���"
						
						return false;
					}
				}

				if(!bMatrixOk)			//break��true��У��ͨ������Ч��λ���+У��4�κ�false��У���������쳣�����У������δ��꣬���������ѭ��
				{
					if(bOnceAgain)
					{
						if(i==0)
							GetDoc().SetLastWarningNo(81);							//"�����񾵵���У�����������Ҫ��"
						
						if(i==1)
							GetDoc().SetLastWarningNo(82);							//"�����񾵵���У�����������Ҫ��"	
						
						return false;
					}
					else
						bOnceAgain=true;
				}
				else										//20191216
					bOnceAgain=false;
			}
		}

		if(!bOnceAgain)
			break;
		}
	}

	if(bOK[HeadLeft])
		GetDoc().SetAutoAdjustPattern(false,HeadLeft);

	if(bOK[HeadRight])
		GetDoc().SetAutoAdjustPattern(false,HeadRight);

	if(!isOnlyOffset)
	{
		BOOL autoAdjustStatus=false;	

		if(nHead==HeadBoth)
			autoAdjustStatus=(bOK[HeadLeft]&&bOK[HeadRight]);
		else
			autoAdjustStatus=bOK[nHead];
		
		if(autoAdjustStatus)
//		if(bOK[HeadLeft]&&bOK[HeadRight])							//˫��ӹ�ģʽ�� 20180925 20190709�Ļ�
		{
			time_t Dotime;
			time(&Dotime);
			GetDoc().SetAdjustTime(Dotime);
			GetDoc().SetAutoGalvoAdjustIsTimed(false);											//20190711
		}
		else
			return false;
	}
	
	GetDoc().WriteCaliTimes();
	LightTurnOff();		
	
	return true;
}

BOOL CControl::AutoLaserPower(int nHead,int nIndex)					//20180829
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);
	ASSERT(nIndex>=0&&nIndex<5);

	bool bTestOk;
	float power;
	BOOL autoPowerStatus=false;

//�ӹ���ģʽ�趨
	int start=0;
	int end=2;
	GetDoc().SetAutoLaserPowerTest(true,HeadLeft);					//true:��Ҫ���ԣ���ʱ����NG��false:���ò��ԣ���ʱ����OK
	GetDoc().SetAutoLaserPowerTest(true,HeadRight);

	if(nHead==HeadLeft)
	{
		start=0;
		end=1;
	}
	
	if(nHead==HeadRight)
	{
		start=1;
		end=2;
	}

//��ʼ�����Զ�����
	bool bOK[2];
	bOK[HeadLeft]=false;
	bOK[HeadRight]=false;

	for(int i=start;i<end;i++)
	{
		bTestOk=true;
		power=0.0;

		if(GetLaserPower(i,power,bTestOk,nIndex))
		{
			if(bTestOk)
				bOK[i]=true;
		}
		else
		{
			if(0==i)
				GetDoc().SetLastWarningNo(83);					//"���Ṧ�ʲ��Գ��ִ���"

			if(1==i)
				GetDoc().SetLastWarningNo(84);					//"���Ṧ�ʲ��Գ��ִ���"

			return false;
		}
	}

	if(bOK[HeadLeft])
		GetDoc().SetAutoLaserPowerTest(false,HeadLeft);

	if(bOK[HeadRight])
		GetDoc().SetAutoLaserPowerTest(false,HeadRight);

	if(nHead==HeadBoth)
	{
		if(!bOK[HeadLeft])
			GetDoc().SetLastWarningNo(85);						//"���Ṧ�ʲ��Խ��������Ҫ��"
		
		if(!bOK[HeadRight])
			GetDoc().SetLastWarningNo(86);						//"���Ṧ�ʲ��Խ��������Ҫ��"
		
		autoPowerStatus=(bOK[HeadLeft]&&bOK[HeadRight]);
	}
	else
	{
		if((nHead==HeadLeft)&&(!bOK[HeadLeft]))
			GetDoc().SetLastWarningNo(85);						//"���Ṧ�ʲ��Խ��������Ҫ��"

		if((nHead==HeadRight)&&(!bOK[HeadRight]))
			GetDoc().SetLastWarningNo(86);						//"���Ṧ�ʲ��Խ��������Ҫ��"

		autoPowerStatus=bOK[nHead];
	}

	if(autoPowerStatus)	
//	if(bOK[HeadLeft]&&bOK[HeadRight])							//˫��ӹ�ģʽ�� 20180925	20190709�Ļ�
	{
		time_t Dotime;
		time(&Dotime);
		GetDoc().SetLaserTestCurTime(Dotime);
		GetDoc().SetAutoLaserTestIsTimed(false);											//20190711
	}
	else
		return false;

	return true;
}

BOOL CControl::AutoFileLaserPower(int nHead,int nIndex)					//20180829
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);
	ASSERT(nIndex>=0&&nIndex<5);

	bool bTestOk;
	float power;
	BOOL autoPowerStatus=false;

//�ӹ���ģʽ�趨
	int start=0;
	int end=2;
	GetDoc().SetAutoLaserPowerTest(true,HeadLeft);
	GetDoc().SetAutoLaserPowerTest(true,HeadRight);

	if(nHead==HeadLeft)
	{
		start=0;
		end=1;
	}
	
	if(nHead==HeadRight)
	{
		start=1;
		end=2;
	}

//��ʼ�����Զ�����
	bool bOK[2];
	bOK[HeadLeft]=false;
	bOK[HeadRight]=false;

	for(int i=start;i<end;i++)
	{
		bTestOk=true;
		power=0.0;

		if(GetFileLaserPower(i,power,bTestOk,nIndex))
		{
			if(bTestOk)
				bOK[i]=true;
		}
		else
		{
			if(0==i)
				GetDoc().SetLastWarningNo(83);					//"���Ṧ�ʲ��Գ��ִ���"

			if(1==i)
				GetDoc().SetLastWarningNo(84);					//"���Ṧ�ʲ��Գ��ִ���"

			return false;
		}
	}

	if(bOK[HeadLeft])
		GetDoc().SetAutoLaserPowerTest(false,HeadLeft);

	if(bOK[HeadRight])
		GetDoc().SetAutoLaserPowerTest(false,HeadRight);

	if(nHead==HeadBoth)
	{
		if(!bOK[HeadLeft])
			GetDoc().SetLastWarningNo(85);						//"���Ṧ�ʲ��Խ��������Ҫ��"
		
		if(!bOK[HeadRight])
			GetDoc().SetLastWarningNo(86);						//"���Ṧ�ʲ��Խ��������Ҫ��"
		
		autoPowerStatus=(bOK[HeadLeft]&&bOK[HeadRight]);
	}
	else
	{
		if((nHead==HeadLeft)&&(!bOK[HeadLeft]))
			GetDoc().SetLastWarningNo(85);						//"���Ṧ�ʲ��Խ��������Ҫ��"

		if((nHead==HeadRight)&&(!bOK[HeadRight]))
			GetDoc().SetLastWarningNo(86);						//"���Ṧ�ʲ��Խ��������Ҫ��"

		autoPowerStatus=bOK[nHead];
	}

	if(autoPowerStatus)	
//	if(bOK[HeadLeft]&&bOK[HeadRight])							//˫��ӹ�ģʽ�� 20180925	20190709�Ļ�
	{
		time_t Dotime;
		time(&Dotime);
		GetDoc().SetLaserTestCurTime(Dotime);
		GetDoc().SetAutoLaserTestIsTimed(false);											//20190711
	}
	else
		return false;

	return true;
}
/*
BOOL CControl::PreTargetFind(int nHead,TARGETMODE tm)
{
	switch(tm)
	{
	case 0:															//����	
		LightTurnOn(OUTERMAINPATTERN);
		GetDoc().ClearFiducailRealPos(nHead);
		break;
	case 1:															//�ڱ��
		LightTurnOn(INNERPATTERN);
		GetDoc().ClearInnerFiducailRealPos();
		break;
	case 2:															//��׼�ֲ����
	case 3:															//SA�ֲ����
		LightTurnOn(LOCALMARKPATTERN);
		GetDoc().ClearLocalMarkDataRealPos();
		break;
	case 4:															//�����������
		LightTurnOn(OUTERMAINPATTERN);
		break;
	default:
		AfxMessageBox("Ŀ��ʶ��ģʽ�趨����!");
		return false;
	}

	return true;
}
*/
void CControl::ClearSourceAndTarget(int nHead)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

	if(nHead==HeadBoth)
	{
		m_SourceCrdVL.clear();
		m_TargetCrdVL.clear();
		m_SourceCrdVR.clear();
		m_TargetCrdVR.clear();
	}

	if(nHead==HeadLeft)
	{
		m_SourceCrdVL.clear();
		m_TargetCrdVL.clear();
	}

	if(nHead==HeadRight)
	{
		m_SourceCrdVR.clear();
		m_TargetCrdVR.clear();
	}
}

void CControl::AddSource(int nHead,Coord crd)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	if(nHead==HeadLeft)
		m_SourceCrdVL.push_back(crd);

	if(nHead==HeadRight)
		m_SourceCrdVR.push_back(crd);
}

void CControl::AddTarget(int nHead,Coord crd)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	if(nHead==HeadLeft)
		m_TargetCrdVL.push_back(crd);

	if(nHead==HeadRight)
		m_TargetCrdVR.push_back(crd);
}

HoleCoordV CControl::GetSource(int nHead)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	if(nHead==HeadLeft)
		return m_SourceCrdVL;

	if(nHead==HeadRight)
		return m_SourceCrdVR;
}

HoleCoordV CControl::GetTarget(int nHead)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight);

	if(nHead==HeadLeft)
		return m_TargetCrdVL;

	if(nHead==HeadRight)
		return m_TargetCrdVR;
}

void CControl::InitalTransform()
{
	m_dbScaleLX1 = 1;
	m_dbScaleLY1 = 1;
	m_dbScaleLX2 = 1;
	m_dbScaleLY2 = 1;
	m_dbAngleL   = 0;
	m_crdRealOffsetL = Coord();

	m_dbScaleRX1 = 1;
	m_dbScaleRY1 = 1;
	m_dbScaleRX2 = 1;
	m_dbScaleRY2 = 1;
	m_dbAngleR  = 0;
	m_crdRealOffsetR = Coord();

	m_crdGlvMidPos=(GetDoc().GetCCDToGlvSysOffset(HeadLeft)+GetDoc().GetCCDToGlvSysOffset(HeadRight))/2;	//20190731
}
/*
BOOL CControl::AddFindedTarget(int nHead,Coord crd,TARGETMODE tm,int index)
{
	switch(tm)
	{
	case 0:															//����	
		GetDoc().AddFiducialPos(crd,nHead);
		break;
	case 1:															//�ڱ��
		GetDoc().AddInnerFiducialPos(crd,nHead);
		break;
	case 2:															//��׼�ֲ����
	case 3:															//SA�ֲ����
		GetDoc().AddLocalMarkDataRealPos(crd,index,nHead);
		break;
	case 4:															//�����������
		break;
	default:
		AfxMessageBox("Ŀ��ʶ��ģʽ�趨����!");
		return false;
	}

	return true;
}
*/
//�ƶ���Ŀ��λ��->ץͼ->Ŀ��ʶ��
BOOL CControl::PatternMatch(const Coord& crdTarget,char* strScrName,char* strDestName,int iWidth,int iHeight,int iTimes,float fMinScore,double& dbDevX,double& dbDevY,int maxError,double dbOutsideThredHold)
{
	double score=0.0;									//ly add 20130724 �õ���ǰƥ��ֵ�����沢��ʾ
	dbDevX=0;
	dbDevY=0;

	int searchTimes=5;
	int offsetX[5]={0,1,-1,-1,1};
	int offsetY[5]={0,1,1,-1,-1};
	long iCurX,iCurY;

//	if(iTimes==1)
//		searchTimes=1;
	if(iTimes<3)											//20190328
		searchTimes=1;

	for(int j=0;j<searchTimes;j++)
	{
		MoveTo(crdTarget+Coord(offsetX[j]*SEARCHSTEP,offsetY[j]*SEARCHSTEP));

		iCurX=crdTarget.x+offsetX[j]*SEARCHSTEP;			//20200819
		iCurY=crdTarget.y+offsetY[j]*SEARCHSTEP;
		
		for (int k=0;k<2;k++)								//Ϊ��һ��Ŀ��ʶ������һ��ʶ�����
		{
			BOOL onceAgain=false;
			double dbOutsideThredHoldtemp=dbOutsideThredHold;
			double offsetx=0,offsety=0;	
//			long iCurX,iCurY;	
			
			for(int i=0; i<iTimes; i++)
			{
//				if(((iWidth==0)||(iHeight==0))&&(iTimes>1)&&(i==0))
				if(((iWidth==0)||(iHeight==0))&&(iTimes>2)&&(i==0))					//20190328
					dbOutsideThredHoldtemp=0.5;				//��ץȡȫͼ����ʶ������趨����2��ʱ���ڵ�һ��Ŀ��ʶ��ʱ��Ŀ��������ֵ��Ϊ0.5
//ƽ̨��Ŀ���ƶ�
				if(i>0)
				{
					dbOutsideThredHoldtemp=dbOutsideThredHold;	
/*																					//20200819					
					iCurX = GetPos(AXISTABX);
					iCurY = GetPos(AXISTABY);
												
#ifdef AEROTECHDMSYSTEM																//20200818
					iCurX = GetXYMotion().GetFPos(AXISTABX);
					iCurY = GetXYMotion().GetFPos(AXISTABY);
#else
					iCurX = GetPos(AXISTABX);
					iCurY = GetPos(AXISTABY);
#endif
*/
					MoveTo(Coord(iCurX+dbDevX,iCurY+dbDevY));

					iCurX+=dbDevX;													//20200819
					iCurY+=dbDevY;
				}
				
				WaitAxisStop(AXISTAB);		

#ifdef AEROTECHDMSYSTEM																//20200818
				Delay(200);
#endif
//#ifdef AVT
//				Delay(200);
//#endif				
//ץȡͼ��				
#ifdef USEIMAGE
				if((iWidth==0)||(iHeight==0))
				{
					GetImageCaptor().CaptFullImage(strDestName);
				}
				else
				{
//					GetImageCaptor().CaptROIImage(strDestName,iWidth,iHeight,true);
					GetImageCaptor().CaptROIImage(strDestName,iWidth,iHeight);			//20170524
				}
#endif
				
//Ŀ��ʶ��			 
#ifdef USERCOGNEX
					if(CogFind(strDestName,offsetx,offsety,fMinScore,score,dbOutsideThredHoldtemp,GetDoc().GetCCDContrastThrd()))
#endif
					{
						GetDoc().SetMatch(true);
						GetDoc().SetMatchScore(score);
						SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPMATCHINFO,0,0);
						
						dbDevX = offsetx*IMAGEPIXELX;	
						dbDevY = offsety*IMAGEPIXELY;
						
						if((maxError>0)&&(i==0))		//�жϵ�һ��ץ��λ��ƫ���Ƿ���� um
						{
//							CString strMessage;														//20190328
//							strMessage.Format("DevX=%f,DevY=%f,maxError=%d",fabs(dbDevX),fabs(dbDevY),maxError);
//							AfxMessageBox(strMessage);

							if((fabs(dbDevX)>maxError)||(fabs(dbDevY)>maxError))			
							{
								AfxMessageBox("�˱�е�ʶ��λ��ƫ����󣬿����Ǳ�����ݴ��󡢰���ֲ����ι�����߰�����ô�����ɵģ���ȷ��!");
								return false;
							}
						}
					}
					else
					{
						GetDoc().SetMatch(false);
						GetDoc().SetMatchScore(score);
						SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPMATCHINFO,0,0);
						
						if ((k==0)&&(i==0))				//��һ�λ���ʱ���״�ʶ��ʧ�ܣ��������еڶ��λ��ᣬ�������Խ��еڶ����״�ʶ��֮��ĵڶ��͵�����ʶ��ֻ��һ�λ���
							onceAgain=true;
						
						break;
					}
					
//					if(GetDoc().GetMatch() && abs(dbDevX)<50 && abs(dbDevY)<50 && i<iTimes-1)		//Ŀ��ʶ��ɹ���������ƫ��С��50X50um������	//20190327 ȡ��
//						break;
			}
			
			if (!onceAgain)
				break;
		}

		if(GetDoc().GetMatch())
			break;
	}

	if(GetDoc().GetMatch())
		return true;
	else
		return false;
}

int CControl::TargetFindInProc(int nHead,int count,HoleCoordV& crdV,TARGETMODE tm,double& dbDevX,double& dbDevY)
{
//����Ŀ��ģʽ������Ӧ��ʶ����
//----------------------------------------------------------
//����ͼ��ʶ����ز���
	char scrName[MaxPathLen]; 
	char destName[MaxPathLen];
	CString strMode;
	CString message;

	TransformParam tfParam;

	int width=GetDoc().GetCCDProcInnerRange();
	int height=GetDoc().GetCCDProcInnerRange();
//	int times=1;
	int times[2];
	times[0]=1;
	times[1]=1;
	float minScore=GetDoc().GetCCDProcInnerThreshold()/100.0;
//	int maxError=GetDoc().GetFZInnerOffset();
	int maxError[2];
	maxError[0]=GetDoc().GetFZInnerOffset();
	maxError[1]=GetDoc().GetFZInnerOffset();
	long markPolarity=GetDoc().GetInnerFiduPolarity();
	int iGrainLimitAutoSelect=1;
	bool isHighSensitivityUsed=false;

	switch(tm)
	{
	case 0:															//����
	case 5:															//��ж�λ
		strMode="Ext";
#ifdef GREENOILBOARD
		iGrainLimitAutoSelect=0;
		isHighSensitivityUsed=true;
#endif
		width=0;
		height=0;
//		times=3;
		if(crdV.size()>1)											//20190412 �޸�
		{
			times[0]=3;
			times[1]=3;
		}
		minScore=GetDoc().GetCCDProcThreshold()/100.0;
//		maxError=0;
		maxError[0]=0;
		maxError[1]=0;
		markPolarity=GetDoc().GetMainFiduPolarity();
		LightTurnOn(OUTERMAINPATTERN);
		break;
	case 1:															//�ڱ��
		strMode="Inn";
		times[0]=2;													//20190418	�޸�
		times[1]=2;
		iGrainLimitAutoSelect=0;
		isHighSensitivityUsed=true;									//20180806
		LightTurnOn(INNERPATTERN);
		break;
	case 2:															//��׼�ֲ����
	case 3:															//SA�ֲ����
		strMode="Int";
		LightTurnOn(LOCALMARKPATTERN);
		break;
	case 4:															//�����������
		strMode="Gander";
		width=0;
		height=0;
		minScore=GetDoc().GetCCDProcThreshold()/100.0;
//		maxError=500;
		maxError[0]=500;
		maxError[1]=500;
		markPolarity=GetDoc().GetMainFiduPolarity();
		LightTurnOn(OUTERMAINPATTERN);
		break;
	default:
		AfxMessageBox("Ŀ��ʶ��ģʽ�趨�������˳��ӹ�����ȷ��!");
		return -1;
	}

//Z��CCD�۽�
	ZAxisCCDFocus(nHead,GetDoc().GetPCBThickness());

	CString strpath = GetDoc().GetAppPath()+BMPFILEDIR;
	CString strName = GetDoc().GetFileName();
	strName =strName.Left(strName.ReverseFind('.'));
	sprintf(scrName,"%s%s.bmp",strName,strMode);

//Cognexģ��ѧϰ
#ifdef USERCOGNEX
	CogSetShapePolarity((CogShapeExtractPolarityConstants)markPolarity);	//Cognex����Ŀ��ʶ����
	CogSetTrainParam(iGrainLimitAutoSelect,2.0,1.0);
	if(!CogTrain(scrName,isHighSensitivityUsed))
		return -1;
#endif

//��ʼĿ��ʶ��
	char ez[256]={""};
	CString InforStr;

	Coord crd;
//	bool channelOK[2];
	bool findOK[2];						//��¼��ʶ��ͨ���Ƿ�ʶ��ʧ�ܣ�false��ʶ��ʧ��
	bool markAllOK[2];					//��¼��ʶ��ͨ���Ƿ��Ѻ���1����У�false���Ѻ���1�����
	bool hasIgnored[2];					//��¼��ǰ����Ƿ�Ϊ����״̬
	bool bALLNG=false;
	bool bDirectFind[2];				//OUTERģʽ�¼�¼��ǰ����Ƿ���ֱ�Ӷ�λץȡ��false������ֱ�Ӷ�λ�����Ƕ��Ѱ��ץȡ
//	double dbDevX,dbDevY;

//	channelOK[0]=true;
//	channelOK[1]=true;
	findOK[0]=true;
	findOK[1]=true;
	markAllOK[0]=true;
	markAllOK[1]=true;
	bDirectFind[0]=false;
	bDirectFind[1]=false;

	dbDevX=0.0;
	dbDevY=0.0;

	if(tm<4)							//�������ʶ��ͱ�ж�λ����������Ϣ���
		ClearSourceAndTarget(nHead);

//�ӹ���ģʽ�趨
	int start=0;
	int end=2;

	if(tm==FIRSTMARKPOS)
	{ 
		if(nHead==HeadRight)
		{
			start=1;
			end=2;
		}
		else
		{
			start=0;
			end=1;
		}
	}
	else
	{
		if(m_bEnableProcPCB1&&m_bEnableProcPCB2)							//��ȫ�ֱ���������ӹ��������
		{
			start=0;
			end=2;
		}
		else if(m_bEnableProcPCB1)
		{
			start=0;
			end=1;
		}
		else if(m_bEnableProcPCB2)
		{
			start=1;
			end=2;
		}
	}

//���ձ������˳���������л�ʶ����
	for(int n=0; n<count; ++n)
	{
		for(int i=start;i<end;i++)
		{
			if(tm==FIRSTMARKPOS)															//��ȡĿ�������λ��
				crd=crdV[n];
			else if((tm==OUTER)&&(!bDirectFind[i]))
				crd=GetDoc().GetFileToRealRelative()-crdV[n];
			else
			{
				if(!CogSetMapPoint(i,crdV[n],crd))
				{
					SetLampStatus(CControl::ERR);
					ChannelOutput(OCOMMONALARM ,TRUE);
					
					message.Format("�ӹ���%d����ӳ�����������˳��ӹ�����ȷ��!",i);
					AfxMessageBox(message);
					
					SetLampStatus(CControl::ORDER);
					ChannelOutput(OCOMMONALARM ,FALSE);
					return -1;
				}

				crd=GetDoc().GetFileToRealRelative()-crd;
			}

#ifdef AVT
//			if(findOK[i])																//20190418 ȡ��
//			{
//				MoveTo(crd);
//				WaitAxisStop(AXISTAB);
//			}
#endif

#ifdef USEIMAGE			
//			if (findOK[i]&&channelOK[i]&&(!GetImageCaptor().SelectChannel(i)))
			if (findOK[i]&&(!GetImageCaptor().SelectChannel(i)))						//����Ӧ��ͼ��ͨ��
			{
				SetLampStatus(CControl::ERR);
				ChannelOutput(OCOMMONALARM ,TRUE);

				message.Format("CCDͨ��%dͼ���ȡʧ�ܣ����˳��ӹ�����ȷ��!",i);
				AfxMessageBox(message);

				SetLampStatus(CControl::ORDER);
				ChannelOutput(OCOMMONALARM ,FALSE);
				return -1;

//				channelOK[i]=false;
/*				
				if(i==0)
					m_bEnableProcPCB1=false;
				else
					m_bEnableProcPCB2=false;

				if(!(m_bEnableProcPCB1||m_bEnableProcPCB2))
				{
					AfxMessageBox("CCDͼ��ϵͳ���ֹ��ϣ��޷������ӹ�����ȷ��!");
					return -1;
				}
*/
			}
#endif
			Delay(100);										//20190129 L2-001#�� ��ʱ����ͨ���л� //20190130 ������̬��

			if(i==0)
				sprintf(destName,"%s%sL%d.bmp",strpath,strMode,n+1);
			else
				sprintf(destName,"%s%sR%d.bmp",strpath,strMode,n+1);
			
//			isDelayInnerFidu=FALSE;

			hasIgnored[i]=false;

			while(findOK[i]&&(!PatternMatch(crd,scrName,destName,width,height,times[i],minScore,dbDevX,dbDevY,maxError[i],OUTSIZETHRED)))
			{
//----------------------------------------------------------------------------//20170103
#ifdef BMPFILETEST
				char buf[MaxPathLen];
				CTime timeAccuracy;
				timeAccuracy=CTime::GetCurrentTime();
				CString str="";
				str=timeAccuracy.Format("%Y%m%d-");
				CString timeFormat="";
				timeFormat.Format("%s%d%d%d-",str,timeAccuracy.GetHour(),timeAccuracy.GetMinute(),timeAccuracy.GetSecond());
				char bufCopyFile[MaxPathLen];
				sprintf(bufCopyFile,"%s%sInnL%d_%.1f.bmp",strpath,timeFormat,n+1,100*GetDoc().GetMatchScore());
				CopyFile(buf,bufCopyFile,false);
#endif
//----------------------------------------------------------------------------
				if(tm>=4)														//�������ʶ����߱�ж�λʧ�ܺ󷵻�-1
					return -1;

				if(GetDoc().GetEnFidRetry())									//�������Ա�У���ʱ�豨����ʾ���˹��������������Է�ʽ���ֹ��԰к��Զ�����ʶ��
				{
					SetLampStatus(CControl::ERR);
					ChannelOutput(OCOMMONALARM ,TRUE);

					int nSel=0;

					if(GetDoc().GetEnManuFid())									//�����ֹ��԰�
					{
						if(i==0)
							InforStr.Format("����%d�����ƥ��ʧ��!��ȷ���Ƿ���Ҫ�����ֹ��԰У�",n+1);
						else
							InforStr.Format("�Ҳ��%d�����ƥ��ʧ��!��ȷ���Ƿ���Ҫ�����ֹ��԰У�",n+1);						

						nSel = AfxMessageBox(InforStr,MB_YESNO);
						if(nSel==IDYES)
						{
							SetLampStatus(CControl::ORDER);
							ChannelOutput(OCOMMONALARM ,FALSE);
//�ֹ��԰У������˳�ʶ�𣬵������Ժ���
							SetRunState(CControl::MANU);							//�ֶ��԰�״̬ 
							GetMainFrame().m_Framework.Get(16)->SetActivePane();	//�л���ͼ��ʶ�����
							Delay(500);
							pImageParaSetView->BeginManuMark();						//��ʼ�����ֹ���

							while(!pImageParaSetView->m_bManuMarkIsEnd)
							{
								DoEvent();
								Sleep(50);
							}

							GetMainFrame().m_Framework.Get(37)->SetActivePane();	//�л���������
							SetRunState(CControl::RUN);								//�ӹ�״̬ 

							if(pImageParaSetView->m_bManuMarkIsOK)
							{
								dbDevX=0.0;
								dbDevY=0.0;
							}
							else
								findOK[i]=false;
							
							bALLNG=false;
							if(!findOK[i])
							{
								if(i==0)
								{
									m_bEnableProcPCB1=false;
									if(nHead==HeadLeft)
										bALLNG=true;
									if((nHead==HeadBoth)&&(!m_bEnableProcPCB2))
										bALLNG=true;
								}
								else
								{
									m_bEnableProcPCB2=false;
									if(nHead==HeadRight)
										bALLNG=true;
									if((nHead==HeadBoth)&&(!m_bEnableProcPCB1))
										bALLNG=true;
								}
								
								if(bALLNG)
								{
//									AfxMessageBox("���ʶ��ʧ�ܣ��޷����з����ӹ�������������!");
									return 1;
								}
							}

							break;
						}
					}

					if((count>=4)&&GetDoc().GetEn3Fid()&&markAllOK[i])			//ֻ�б������������4��ʱ���������1�����
					{
//						GetDoc().SetLastWarningNo(53);

						if(i==0)
							InforStr.Format("����%d�����ƥ��ʧ��!\n\n�˳�ʶ��  ��ѡ��'�˳�'\n����ʶ��  ��ѡ��'����'\n����ʶ��  ��ѡ��'����'\n",n+1);
						else
							InforStr.Format("�Ҳ��%d�����ƥ��ʧ��!\n\n�˳�ʶ��  ��ѡ��'�˳�'\n����ʶ��  ��ѡ��'����'\n����ʶ��  ��ѡ��'����'\n",n+1);
						
						nSel = AfxMessageBox(InforStr,MB_ABORTRETRYIGNORE);								
						if(nSel==IDABORT)										//�˳�ʶ��
							findOK[i]=false;
						else if(nSel==IDIGNORE)									//���Դ˱��
						{
							markAllOK[i]=false;
							hasIgnored[i]=true;
						}
					}
					else
					{
//						GetDoc().SetLastWarningNo(53);
						if(i==0)
							InforStr.Format("����%d�����ƥ��ʧ��!��ȷ���Ƿ���Ҫ�Զ�����ʶ��",n+1);
						else
							InforStr.Format("�Ҳ��%d�����ƥ��ʧ��!��ȷ���Ƿ���Ҫ�Զ�����ʶ��",n+1);						

						nSel = AfxMessageBox(InforStr,MB_YESNO);	
						if(nSel==IDNO)											//�˳�ʶ��
							findOK[i]=false;
					}

//					SetLampStatus(CControl::ORDER);
//					ChannelOutput(OCOMMONALARM ,FALSE);

//					isDelayInnerFidu=TRUE;

					if(nSel==IDYES||nSel==IDRETRY)
					{
//						strncpy(ez,GetLang().GetWarningText(21046),256);		//20190711 ȡ��
//						AfxMessageBox(ez);										//"�����µ���CCD��Դ���Ȼ�����������!"
						
						pImageParaSetView->pLampAdj->ShowWindow(SW_SHOW);
						
						while(1)
						{
							for(int m=0;m<12;m++)
								DoEvent();
							
							if(pImageParaSetView->pLampAdj->IsWindowVisible())
								Sleep(50);
							else
								break;
						}
					}

					SetLampStatus(CControl::ORDER);								//20190711 ������������
					ChannelOutput(OCOMMONALARM ,FALSE);
				}
				else															//���������Ա�У���ʱ���豨���������Զ�����
				{
					if((count>=4)&&GetDoc().GetEn3Fid()&&markAllOK[i])			//ֻ�б������������4��ʱ���������1�����
					{
						markAllOK[i]=false;
						hasIgnored[i]=true;
					}
					else
						findOK[i]=false;
				}

				bALLNG=false;
				if(!findOK[i])
				{
//----------------------------------------------------------------------	//20190403
//					if(GetDoc().GetEnFidRetry())

//					if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC)&&GetDoc().GetEnFidRetry())
//					{
//						int nSel=AfxMessageBox("��ѡ���Ƿ�����ӹ��������ӹ���ѡ���ǡ����˳��ӹ���ѡ����!",MB_YESNO);	
//						if(nSel==IDNO)
//							return -1;
//					}
//----------------------------------------------------------------------
					if(i==0)
					{
						m_bEnableProcPCB1=false;
						if(nHead==HeadLeft)
							bALLNG=true;
						if((nHead==HeadBoth)&&(!m_bEnableProcPCB2))
							bALLNG=true;
					}
					else
					{
						m_bEnableProcPCB2=false;
						if(nHead==HeadRight)
							bALLNG=true;
						if((nHead==HeadBoth)&&(!m_bEnableProcPCB1))
							bALLNG=true;
					}

					if(bALLNG)
					{
//						AfxMessageBox("���ʶ��ʧ�ܣ��޷����з����ӹ�������������!");
						return 1;
					}
				}

				if(hasIgnored[i])
					break;
			}
			
			if((tm<4)&&findOK[i]&&(!hasIgnored[i]))				//�������ʶ����߱�ж�λ����������Ϣ����
			{
//				if(!AddFindedTarget(i,GetDoc().GetFileToRealRelative()-GetTablePos()-Coord(dbDevX,dbDevY),tm,index))
//					return false;
//				AddSource(i,crd);
//				Coord sre=crdV[n];
//				Coord tgt=GetDoc().GetFileToRealRelative()-GetTablePos()-Coord(dbDevX,dbDevY);
				AddSource(i,crdV[n]);
				AddTarget(i,GetDoc().GetFileToRealRelative()-GetTablePos()-Coord(dbDevX,dbDevY));

				if((tm==OUTER)&&(count>2)&&(GetSource(i).size()==2))		//��������������2ʱ���д˹���:��1��2�����ó�3��4���λ�ã����ڿ���ץȡ3��4��
				{
					times[i]=2;												//20190328 //times[i]=1
					maxError[i]=GetDoc().GetFZInnerOffset();
					bDirectFind[i]=true;

					CogSetNPointToNPointDOFConstants(cogNPointToNPointDOFScalingRotationAndTranslation);		//XY����һ��
					
					if(!CogGetTransform(i,GetSource(i),GetTarget(i),tfParam))
					{
						SetLampStatus(CControl::ERR);
						ChannelOutput(OCOMMONALARM ,TRUE);
						
						message.Format("�ӹ���%d�任������ȡ�������˳��ӹ�����ȷ��!",i);
						AfxMessageBox(message);
						
						SetLampStatus(CControl::ORDER);
						ChannelOutput(OCOMMONALARM ,FALSE);
						return -1;
					}
				}
			}

			if(tm<=4)											//��ж�λʱ��������״̬��ѯ
			{
				if(!PeekRunState())
					return -1;
			}
//			else
//				continue;
		}
	}

	if(tm<=4)													//��ж�λʱ�����ع�Դ
		LightTurnOff();

	if(tm>=4)													//�������ʶ����߱�ж�λOK�󷵻�0
		return 0;

//�����任����ı�������趨
	CogSetNPointToNPointDOFConstants(cogNPointToNPointDOFScalingAspectRotationAndTranslation);		//XY������һ��
	if((tm==OUTER)&&(count==2))
		CogSetNPointToNPointDOFConstants(cogNPointToNPointDOFScalingRotationAndTranslation);		//XY����һ��

//��������У���ò��������ü�¼�������йܿ�
//	TransformParam tfParam;

	double dbScaleX=0.0, dbScaleY=0.0;
	double scaleThreshold=0.0;
	double midScaleX=1.0,midScaleY=1.0;

//	if(GetDoc().GetUseRefScale()==1||(GetDoc().IsManSetScale()&&GetDoc().GetCheckManulScaleRange()))
//	if(GetDoc().GetUseRefScale()==1)
	if(GetDoc().IsManSetScale()||GetDoc().GetCheckManulScaleRange())	//20181204 //&&	//�����ܿ���ֵ�趨��0����ֵΪ1.0��1����ֵΪ�趨ֵ
		GetDoc().GetManSetScaleVal(midScaleX,midScaleY);	

	if(GetDoc().GetScaleType()==1)													//�����ܿ���ֵ��λ�趨��0������ֵ��1������ֵum��ͳһ����Ϊ����ֵ
	{
		long length=GetExcellonData().GetLayerWidth()>GetExcellonData().GetLayerHeight()?GetExcellonData().GetLayerWidth():GetExcellonData().GetLayerHeight();
		scaleThreshold=(double)GetDoc().GetPCBScaleThrd()/(length*1000.0);
	}
	else
		scaleThreshold=GetDoc().GetPCBScaleThreshold();
/*	
	if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(tm==OUTER))	
		scaleThreshold=0.5;

	if(GetDoc().GetFZInnerMark())													
		scaleThreshold+=0.00006;
*/
	if(!GetDoc().GetFZInnerMark())													//20200326
	{
		if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(tm==OUTER))			//�ڲ�����мӹ���ʽ�£������������ֵ���ܿ�
			scaleThreshold=0.5;
	}
	else
	{
		scaleThreshold+=0.00006;													//�����������йܿ���ֵ+0.00006

		if(tm==INNER)
			scaleThreshold=GetDoc().GetFZInnerScale();								//���������ڱ�йܿ���ֵ
	}

	CString strinfo,strAxis;
	strinfo = GetDoc().GetAppPath()+SCALEDIR;
	strName = GetDoc().GetFileName();	
	
	char timebuf[128],daybuf[128];       	
	_tzset();
	_strtime(timebuf);
	_strdate(daybuf);

	InitalTransform();

	BOOL bUseOldScale[2];													//20190731
	bUseOldScale[0]=false;
	bUseOldScale[1]=false;
	m_bUseOldScale=false;

	if(m_bEnableProcPCB1&&m_bEnableProcPCB2)								//��ȫ�ֱ���������ӹ��������
	{
		start=0;
		end=2;
	}
	else if(m_bEnableProcPCB1)
	{
		start=0;
		end=1;
		bUseOldScale[1]=true;
	}
	else if(m_bEnableProcPCB2)
	{
		start=1;
		end=2;
		bUseOldScale[0]=true;
	}

//#ifdef TRANSFORMTEST
//	if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
/*
	if(!GetDoc().GetEn3Fid())												//20191106
	{
		for(int jjj=start;jjj<end;jjj++)
		{
			if((GetSource(jjj).size()==4)&&(GetTarget(jjj).size()==4))
				bUseOldScale[jjj]=true;
		}

		m_bUseOldScale=bUseOldScale[0]&&bUseOldScale[1];
	}
*/
//#endif

//	if(!GetDoc().GetEn3Fid())	//����ѡ����3��в����������з�ʽ�����ڲ�����з�ʽ�µ��ڲ���ʶ��ʱ 20191210
	if(GetDoc().IsManSetScale()||(!GetDoc().GetEn3Fid()))	//20191219 �޸�
	{
		if((GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)||((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(tm==INNER)))
		{
			for(int jjj=start;jjj<end;jjj++)
			{
				if((GetSource(jjj).size()==4)&&(GetTarget(jjj).size()==4))
					bUseOldScale[jjj]=true;
			}
			
			m_bUseOldScale=bUseOldScale[0]&&bUseOldScale[1];
		}
	}

	for(int j=start;j<end;j++)
	{
		bool autoSetScale=true;

		if(!CogGetTransform(j,GetSource(j),GetTarget(j),tfParam))
		{
			SetLampStatus(CControl::ERR);
			ChannelOutput(OCOMMONALARM ,TRUE);
			
			message.Format("�ӹ���%d�任������ȡ�������˳��ӹ�����ȷ��!",j);
			AfxMessageBox(message);
			
			SetLampStatus(CControl::ORDER);
			ChannelOutput(OCOMMONALARM ,FALSE);
			return -1;
		}
		else
		{
//1�����ñ任ϵ��
//#ifdef TRANSFORMTEST
			if(m_bUseOldScale)
			{
				Coord crdArrayFileLevel[4],crdArrayRealLevel[4];

//				crdArrayFileLevel[0]=GetSource(j).at(0);	
//				crdArrayFileLevel[1]=GetSource(j).at(3);	
//				crdArrayFileLevel[2]=GetSource(j).at(2);	
//				crdArrayFileLevel[3]=GetSource(j).at(1);	
				
//				crdArrayRealLevel[0]=GetTarget(j).at(0);
//				crdArrayRealLevel[1]=GetTarget(j).at(3);
//				crdArrayRealLevel[2]=GetTarget(j).at(2);
//				crdArrayRealLevel[3]=GetTarget(j).at(1);

				crdArrayFileLevel[0]=GetSource(j).at(0);						//20191210	
				crdArrayFileLevel[1]=GetSource(j).at(1);	
				crdArrayFileLevel[2]=GetSource(j).at(2);	
				crdArrayFileLevel[3]=GetSource(j).at(3);	
				
				crdArrayRealLevel[0]=GetTarget(j).at(0);
				crdArrayRealLevel[1]=GetTarget(j).at(1);
				crdArrayRealLevel[2]=GetTarget(j).at(2);
				crdArrayRealLevel[3]=GetTarget(j).at(3);

				double dbScaleX1Level = calc::distance(crdArrayRealLevel[0],crdArrayRealLevel[3])/calc::distance(crdArrayFileLevel[0],crdArrayFileLevel[3]);
				double dbScaleY1Level = calc::distance(crdArrayRealLevel[0],crdArrayRealLevel[1])/calc::distance(crdArrayFileLevel[0],crdArrayFileLevel[1]);		
				double dbScaleX2Level = calc::distance(crdArrayRealLevel[1],crdArrayRealLevel[2])/calc::distance(crdArrayFileLevel[1],crdArrayFileLevel[2]);
				double dbScaleY2Level = calc::distance(crdArrayRealLevel[2],crdArrayRealLevel[3])/calc::distance(crdArrayFileLevel[2],crdArrayFileLevel[3]);
				
				double angle1Level=calc::angle(crdArrayFileLevel[0],crdArrayFileLevel[2],crdArrayRealLevel[0],crdArrayRealLevel[2],1.0,1.0);
				double angle2Level=calc::angle(crdArrayFileLevel[3],crdArrayFileLevel[1],crdArrayRealLevel[3],crdArrayRealLevel[1],1.0,1.0);   
				
				Coord  offsetLevel = (crdArrayRealLevel[0]-crdArrayFileLevel[0] + crdArrayRealLevel[1]-crdArrayFileLevel[1] 
									+ crdArrayRealLevel[2]-crdArrayFileLevel[2] + crdArrayRealLevel[3]-crdArrayFileLevel[3])/4;

				GetInfo().SaveToFile(strinfo,"C: %1.8f, %1.8f, %1.8f, %6.3f, %6.3f\n",tfParam.ScalingX,tfParam.ScalingY,tfParam.Rotation,tfParam.TranslationX,tfParam.TranslationY);
				GetInfo().SaveToFile(strinfo,"S: %1.8f, %1.8f, %1.8f, %6.3f, %6.3f\n",(dbScaleX1Level+dbScaleX2Level)/2,(dbScaleY1Level+dbScaleY2Level)/2,
									(angle1Level+angle2Level)/2,(double)offsetLevel.x,(double)offsetLevel.y);

				tfParam.ScalingX=(dbScaleX1Level+dbScaleX2Level)/2.0;
				tfParam.ScalingY=(dbScaleY1Level+dbScaleY2Level)/2.0;
				tfParam.Rotation=(angle1Level+angle2Level)/2.0;
				tfParam.TranslationX=(double)offsetLevel.x;
				tfParam.TranslationY=(double)offsetLevel.y;
			}
//#endif
			if(j==0)
			{
				m_dbScaleLX1 = tfParam.ScalingX;
				m_dbScaleLY1 = tfParam.ScalingY;
				m_dbScaleLX2 = tfParam.ScalingX;
				m_dbScaleLY2 = tfParam.ScalingY;
				m_dbAngleL   = tfParam.Rotation;

#ifdef SETPROCOFFSET
				m_crdRealOffsetL = Coord(tfParam.TranslationX+GetDoc().GetLoadPCBTime(),tfParam.TranslationY+GetDoc().GetUnLoadPCBTime());		
#else
				m_crdRealOffsetL = Coord(tfParam.TranslationX,tfParam.TranslationY);
#endif

				strAxis="L";

				m_dbAutoScaleLX=tfParam.ScalingX;				//20180905
				m_dbAutoScaleLY=tfParam.ScalingY;
			}
			else
			{
				m_dbScaleRX1 = tfParam.ScalingX;
				m_dbScaleRY1 = tfParam.ScalingY;
				m_dbScaleRX2 = tfParam.ScalingX;
				m_dbScaleRY2 = tfParam.ScalingY;
				m_dbAngleR   = tfParam.Rotation;

#ifdef SETPROCOFFSET
				m_crdRealOffsetR = Coord(tfParam.TranslationX+GetDoc().GetLoadPCBTime(),tfParam.TranslationY+GetDoc().GetUnLoadPCBTime());
#else
				m_crdRealOffsetR = Coord(tfParam.TranslationX,tfParam.TranslationY);
#endif
				
				strAxis="R";
				
				m_dbAutoScaleRX=tfParam.ScalingX;
				m_dbAutoScaleRY=tfParam.ScalingY;
			}

//2����¼����ϵ��
			dbScaleX=tfParam.ScalingX;
			dbScaleY=tfParam.ScalingY;

			if (GetDoc().GetShunluoScale())		//˳��������ǣ������������Ͱ�����������ӹ���20150330 ��¼��ʱ������������
			{
				double tempRecordScaleX,tempRecordScaleY;
				tempRecordScaleX=dbScaleX;
				tempRecordScaleY=dbScaleY;
				
				if ((dbScaleX-1.0)>scaleThreshold)
				{
					dbScaleX=1.0+scaleThreshold;
					autoSetScale=false;
				}

				if ((dbScaleX-1.0)<-scaleThreshold)
				{
					dbScaleX=1.0-scaleThreshold;
					autoSetScale=false;
				}
	
				if ((dbScaleY-1.0)>scaleThreshold)
				{
					dbScaleY=1.0+scaleThreshold;
					autoSetScale=false;
				}

				if ((dbScaleY-1.0)<-scaleThreshold)
				{
					dbScaleY=1.0-scaleThreshold;
					autoSetScale=false;
				}
			
//				GetInfo().SaveToFile(strinfo,"%s: %s, %s, theoryX=%1.6f, theoryY=%1.6f, %1.6f, %1.6f, %s\n",strAxis,daybuf,timebuf,tempRecordScaleX,tempRecordScaleY,
//					dbScaleX,dbScaleY,strName);
			}
//			else								//����ԭ�еļ�¼
//				GetInfo().SaveToFile(strinfo,"%s: %s, %s, %1.6f, %1.6f, %s\n",strAxis,daybuf,timebuf,dbScaleX,dbScaleY,strName);
//3�������ܿ�
			dbScaleX=tfParam.ScalingX;
			dbScaleY=tfParam.ScalingY;

			if(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)		//�ڡ����������ռӹ���ʽ�²Ŷ��������л��ڲ�����н��������ܿ�
			{
				bALLNG=false;

				if((fabs(dbScaleX-midScaleX)>scaleThreshold)||(fabs(dbScaleY-midScaleY)>scaleThreshold))
				{					
#ifdef USELOG																								//20190109 ����
					CString str1;

					if(j==0)
						str1.Format("LX:%f,LY:%f",dbScaleX,dbScaleY);
					else
						str1.Format("RX:%f,RY:%f",dbScaleX,dbScaleY);

					GetLog().Append_pro("����ֵ����","�����ܿ�",str1);
#endif
					if(GetDoc().GetProcessState()==CControl::AUTOPROC)
					{
						GetDoc().SetErrorPCB(GetDoc().GetErrorPCB()+1);
						
						if(GetDoc().GetErrorPCB()>=6)
						{
							SetLampStatus(CControl::ERR);
							ChannelOutput(OCOMMONALARM ,TRUE);
							
							AfxMessageBox("����ֵ��������ѳ���6Ƭ�����˳��ӹ�����ȷ��!");
							
							SetLampStatus(CControl::ORDER);
							ChannelOutput(OCOMMONALARM ,FALSE);
							
							return -1;
						}
					}

					if(j==0)
					{
						m_bEnableProcPCB1=false;
						if(nHead==HeadLeft)
							bALLNG=true;
						if((nHead==HeadBoth)&&(!m_bEnableProcPCB2))					//20190709 ����
							bALLNG=true;

						if(GetDoc().GetProcessState()!=CControl::AUTOPROC)
							GetDoc().SetLastWarningNo(47);
					}
					else
					{
						m_bEnableProcPCB2=false;
						if(nHead==HeadRight)
							bALLNG=true;
						if((nHead==HeadBoth)&&(!m_bEnableProcPCB1))
							bALLNG=true;

						if(GetDoc().GetProcessState()!=CControl::AUTOPROC)
							GetDoc().SetLastWarningNo(48);
					}
					
					if(bALLNG)
					{
//						AfxMessageBox("XY����ֵ����޷����з����ӹ�������������!");
						return 1;
					}
				}
				else
				{	
					if (GetDoc().GetDrillInc()&&(!GetDoc().GetEn3Fid())&&(count==4))			//��ʿ���������������ڲ�4����������Ч
					{			
						if(CalcLinearLevel(j)>=GetDoc().GetDistanceCenterThreshold())	
						{
							if(GetDoc().GetProcessState()==CControl::AUTOPROC)
							{
								GetDoc().SetErrorPCB(GetDoc().GetErrorPCB()+1);
								
								if(GetDoc().GetErrorPCB()>=6)
								{
									SetLampStatus(CControl::ERR);
									ChannelOutput(OCOMMONALARM ,TRUE);
									
									AfxMessageBox("����ֵ��������ѳ���6Ƭ�����˳��ӹ�����ȷ��!");
									
									SetLampStatus(CControl::ORDER);
									ChannelOutput(OCOMMONALARM ,FALSE);
									
									return -1;
								}
							}
							
							if(j==0)
							{
								m_bEnableProcPCB1=false;
								if(nHead==HeadLeft)
									bALLNG=true;
								if((nHead==HeadBoth)&&(!m_bEnableProcPCB2))			//20190709 ����
									bALLNG=true;

								if(GetDoc().GetProcessState()!=CControl::AUTOPROC)
									GetDoc().SetLastWarningNo(38);
							}
							else
							{
								m_bEnableProcPCB2=false;
								if(nHead==HeadRight)
									bALLNG=true;
								if((nHead==HeadBoth)&&(!m_bEnableProcPCB1))
									bALLNG=true;

								if(GetDoc().GetProcessState()!=CControl::AUTOPROC)
									GetDoc().SetLastWarningNo(39);
							}
							
							if(bALLNG)
							{
//								AfxMessageBox("��������ֵ����޷����з����ӹ�������������!");
								return 1;
							}
						}
					}
				}
			}

//4�����Զ�����ʱ�����趨����ֵ			
			if (GetDoc().GetShunluoScale()&&(!autoSetScale))		//��ʽһ��˳������󣺳���������ֵ���Ͱ�������ʼ�����ֵ�ӹ�
			{
				if(j==0)
				{
					if ((dbScaleX-1.0)>scaleThreshold)
					{
						m_dbScaleLX1 = 1.0+scaleThreshold;
						m_dbScaleLX2 = 1.0+scaleThreshold;
					}
					
					if ((dbScaleX-1.0)<-scaleThreshold)
					{
						m_dbScaleLX1 = 1.0-scaleThreshold;
						m_dbScaleLX2 = 1.0-scaleThreshold;
					}
					
					if ((dbScaleY-1.0)>scaleThreshold)
					{
						m_dbScaleLY1 = 1.0+scaleThreshold;
						m_dbScaleLY2 = 1.0+scaleThreshold;
					}
					
					if ((dbScaleY-1.0)<-scaleThreshold)
					{
						m_dbScaleLY1 = 1.0-scaleThreshold;
						m_dbScaleLY2 = 1.0-scaleThreshold;
					}
				}
				else
				{
					if ((dbScaleX-1.0)>scaleThreshold)
					{
						m_dbScaleRX1 = 1.0+scaleThreshold;
						m_dbScaleRX2 = 1.0+scaleThreshold;
					}
					
					if ((dbScaleX-1.0)<-scaleThreshold)
					{
						m_dbScaleRX1 = 1.0-scaleThreshold;
						m_dbScaleRX2 = 1.0-scaleThreshold;
					}
					
					if ((dbScaleY-1.0)>scaleThreshold)
					{
						m_dbScaleRY1 = 1.0+scaleThreshold;
						m_dbScaleRY2 = 1.0+scaleThreshold;
					}
					
					if ((dbScaleY-1.0)<-scaleThreshold)
					{
						m_dbScaleRY1 = 1.0-scaleThreshold;
						m_dbScaleRY2 = 1.0-scaleThreshold;
					}
				}
			}
			
			if (GetDoc().IsManSetScale()&&GetDoc().GetIsNullPrecessHoles())	//��ʽ���������ֹ��趨����ֵ 20180905
			{
				double dbSX=1.0;
				double dbSY=1.0;
				GetDoc().GetManSetScaleVal(dbSX,dbSY);
				
				if(j==0)
				{
					m_dbScaleLX1 = dbSX;
					m_dbScaleLY1 = dbSY;
					m_dbScaleLX2 = dbSX;
					m_dbScaleLY2 = dbSY;
				}
				else
				{
					m_dbScaleRX1 = dbSX;
					m_dbScaleRY1 = dbSY;
					m_dbScaleRX2 = dbSX;
					m_dbScaleRY2 = dbSY;
				}
			}
//�������յı任����
			if(j==0)
			{
				if(!CogSetTransform(HeadLeft,m_dbScaleLX1,m_dbScaleLY1,m_dbAngleL,m_dbAngleL,m_crdRealOffsetL.x,m_crdRealOffsetL.y))
				{
					SetLampStatus(CControl::ERR);
					ChannelOutput(OCOMMONALARM ,TRUE);

					AfxMessageBox("����任�������ô������˳��ӹ�����ȷ��!");
					
					SetLampStatus(CControl::ORDER);
					ChannelOutput(OCOMMONALARM ,FALSE);
					return -1;	
				}
				
//				m_dbAngleL=m_dbAngleL*180/M_PI;					//����->��
			}
			else
			{
				if(!CogSetTransform(HeadRight,m_dbScaleRX1,m_dbScaleRY1,m_dbAngleR,m_dbAngleR,m_crdRealOffsetR.x,m_crdRealOffsetR.y))
				{
					SetLampStatus(CControl::ERR);
					ChannelOutput(OCOMMONALARM ,TRUE);
					
					AfxMessageBox("����任�������ô������˳��ӹ�����ȷ��!");
					
					SetLampStatus(CControl::ORDER);
					ChannelOutput(OCOMMONALARM ,FALSE);
					return -1;
				}

//				m_dbAngleR=m_dbAngleR*180/M_PI;					//����->��
			}
		}
	}
//----------------------------------------------------------
	return 0;
}

int CControl::TargetDealInProc(int nHead,int count,HoleCoordV& crdV,TARGETMODE tm)
{
	double dbDevX,dbDevY;
	
	dbDevX=0.0;
	dbDevY=0.0;

//�����ʶ��
	int rtn=0;				//ʶ�����Խ��з����ӹ�����ʱֱ�ӽ��з����ӹ����߽�NG�����NG�ֺ���з����ӹ�
	bool bAllNG=false;

/*
//�������ʶ��˳����������������й��շ�ʽʱ����ʱ4��У���������-����-����-���ϵ�˳��
//							  �ڲ�����й��շ�ʽʱ����ʱ3����4��У�3���ʱ��˳��ʶ��3����У�4���ʱ��������-���ϵ�˳��ʶ��2�����
	if(tm==OUTER)
	{
		SortFiducial(count,crdV);

//		if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(count==4))				//20181108
//			count=2;
		if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(count==4))
		{
			if(!GetDoc().GetLoadAfterPitch())											//20190828
				count=2;
		}
	}
*/

//�ڲ�����й��շ�ʽʱ�������ʶ��˳��������򣬴�ʱ3����4��У�3���ʱ��˳��ʶ��3����У�4���ʱ��˳��ʶ��4����л��߲�������-���ϵ�˳��ʶ��2�����	//20191210
	if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(tm==OUTER))
	{
		SortFiducial(count,crdV);

		if(count==4)
		{
			if(!GetDoc().GetLoadAfterPitch())
				count=2;
		}
	}

	rtn=TargetFindInProc(nHead,count,crdV,tm,dbDevX,dbDevY);

	if(rtn==-1)				//ʶ�������쳣�������趨���󡢲����������ͼ��ͨ�����󡢰��½�����ť�ȣ���ʱ��Ҫ�˳��ӹ�����
	{
		LightTurnOff();
		return -1;
	}

	if(rtn==1)				//ʶ�����д�������������Ŀ��ʶ��ʧ�ܻ��������ܿس�����޷����з����ӹ�����ʱ������Զ����������У���Ҫ�����Ϻ���������
	{
		LightTurnOff();
		bAllNG=true;					
		
#ifdef USELOG
		if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
			GetLog().Append_pro(10069,20030);	//"Ѱ�ұ��ʧ�ܣ�","�Զ��ӹ�"
		
		if(GetDoc().GetProcessState()==SystemDoc::MANUPROC)
			GetLog().Append_pro(10069,20031);	//"Ѱ�ұ��ʧ�ܣ�","�ֶ��ӹ�"
		
		if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
			GetLog().Append_pro(10069,20014);	//"Ѱ�ұ��ʧ�ܣ�","ָ���ӹ�"
#endif
		SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);	
	}

//��д���(NG)����ʶ��������������

//��ʱ����NG������������迼��:
//1����ǰѭ���Ĺ�����NG����ֱ�ӽ��������Ͻ׶Σ�
//2����˫��ӹ�ģʽ�£���ǰѭ���Ĺ�������NG���ڽ���ӹ��׶�ǰ��A�����̺�B�����̶�NG��Ĵ���ʽ��ͬ��
	if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
	{	
#ifndef MACHINEHOTTEST
		if(bAllNG)	//���1
		{
			m_bFoundLocalMarkPCB1=false;
			m_bFoundLocalMarkPCB2=false;

//			if(!PeekRunState())											//20190506 ����
//				return -1;
															
			if(!UnLoadPCBBoardToNG(nHead))								//��NG�����NG�֣�A�����̺�B����������ʱ������
				return -1;
																		//20190528
//			if(!GetDoc().GetASideIsProcessing())						
//			{
//				Delay(30000);						//20181204 //10000	//B������ʱ����ʱ���ڷ��������NG�ϣ�����ʱ
//				SetCOMOutput(17);										//����ѭ��
//			}
												
			if(!m_bLoadIsReady)
			{
				if(!GetDoc().GetASideIsProcessing())
					SetCOMOutput(17);									//����ѭ��

				if(GetDoc().GetUse9112())
				{
					ChannelOutput(OAOTUBIGN,MIO_ON);					//��ʼ���У��������ϣ�		
					Delay(500);
					ChannelOutput(OAOTUBIGN,MIO_OFF);
				}
				else
					SetCOMOutput(3);									//��ʼ���У��������ϣ� o����3��	o����3

				Delay(DELAYTIMEFORNOBOARD);
			}
			
			return 1;
		}

		if((!GetDoc().GetASideIsProcessing())&&(nHead==HeadBoth))		//˫��B����������ʱ���д˴���
		{
			BOOL bIsHaveNG=false;
			
			if(!m_bEnableProcPCB1)
			{				
				m_bFoundLocalMarkPCB1=false;
				bIsHaveNG=true;	
			}
			
			if(!m_bEnableProcPCB2)
			{				
				m_bFoundLocalMarkPCB2=false;
				bIsHaveNG=true;	
			}
			
			if(bIsHaveNG)	//���2
			{				
				if((GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)&&(tm==OUTER))	//�������з�ʽ�£�����ʧ��ʱ����
				{
					if(!UnLoadPCBBoardToNG(nHead))						//��NG�����NG��
						return -1;

//					Delay(5000);										//��ʱ���ڷŵ���NG�ϣ�����ʱ��
//					SetCOMOutput(17);									//����ѭ��
				}
				
				if((GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)&&(tm==INNER))		//�ڲ�����з�ʽ�£��ڱ��ʧ��ʱ��������ʧ��ʱ������
				{
					if(!UnLoadPCBBoardToNG(nHead))						//��NG�����NG��
						return -1;	

//					Delay(5000);										//��ʱ���ڷŵ���NG�ϣ�����ʱ��
//					SetCOMOutput(17);									//����ѭ��
				}		
			}
		}
#endif
	}
	else
	{
		if(bAllNG)	
			return -1;
	}

	return 0;
}

BOOL CControl::ManuProcPCB(int nHead)
{
	if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)					//20190912
	{
		m_bSAProcMode=false;
		int nsel=AfxMessageBox("��ѡ��ָ���ӹ�ģʽ������ģʽ��ѡ���ǡ�������ģʽ��ѡ���񡱣�",MB_YESNO);	
		if(nsel==IDYES)
			m_bSAProcMode=true;
	}

	int proccount,apt0,apt1,apt2,jj,Aptno[20],apt[20];
	int subproccount,SubAptno[20];
	char ez[256]={""};

//�ӹ�״̬��ʼ��	
	GetDoc().SetCurPCBDrilledHoleCount(0);			//��ʼ���Ѽӹ�����
	GetDoc().SetCurPCBDrilledArea(0);				//��ʼ���Ѽӹ�������
	m_lCurDrillHoleNo = 0;
//	SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);

	m_bOnlyOne=false;								//�ֶ��ӹ�ģʽ��һֱ��false

	m_bEnableProcPCB1=true;
	m_bEnableProcPCB2=true;
	if(nHead==HeadLeft)
		m_bEnableProcPCB2 =false;
	if(nHead==HeadRight)
		m_bEnableProcPCB1 =false;

//��ʼ���ӹ�����									//20191225 ����
	if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)	//�����A&B˫������ģʽ������Ҫ���ݵ�ǰ��A�滹��B��ӹ�״̬������Ӧ�������ļ��������˫��ģʽ��������������ļ�
	{
		CMainFrame* pMainFrame;
		pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
		
		int nSel = AfxMessageBox("A&B˫��ӹ�����ģʽ�£���ѡ�����̷���A����ѡ���ǡ���B����ѡ���񡱣�",MB_YESNO);
		
		if(nSel==IDYES)
		{
			GetDoc().SetASideIsProcessing(true);

			if(!pFileInfoSettingView->SwitchDataFile(0))
				return false;
			
			GetDoc().SetFileToRealRelative(GetDoc().GetFileToRealRelative2(0));
			
			GetDoc().SetASideIsDisplay(true);
			
			pMainFrame->m_wndStatusBar.SetPaneText(2,"  �ӹ�:A��");
			pMainFrame->m_wndStatusBar.SetPaneText(1,"  ��ʾ:A��");
		}
		else
		{
			GetDoc().SetASideIsProcessing(false);

			if(!pFileInfoSettingView->SwitchDataFile(1))
				return false;
			
			GetDoc().SetFileToRealRelative(GetDoc().GetFileToRealRelative2(1));
			
			GetDoc().SetASideIsDisplay(false);
			
			pMainFrame->m_wndStatusBar.SetPaneText(2,"  �ӹ�:B��");
			pMainFrame->m_wndStatusBar.SetPaneText(1,"  ��ʾ:B��");
		}
		::SendMessage(GetMainFrame().m_Framework.Get(MAINRUNVIEW)->GetWnd()->m_hWnd,WM_USERUPDATEFILANAME,0,0);
/*																				//20200601 ȡ��
#ifdef SMCPreLoad
		if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//20200107 ��������Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
		{
			if(!PreLoadCreate(true,false,false))
			{		
				AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
				return false;
			}
		}
#endif
*/
	}

#ifdef SMCPreLoad																//20200601 �������˴�
	if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
	{
		if(!PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
		{		
			AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
			return false;
		}
	}
	else																		//20191015
	{
		if(!PreLoadCreate(false,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))
		{		
			AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
			return false;
		}
	}
#endif

//����ӹ�ѭ�������Ͱ���Ȧ�����еļӹ�˳��
	for(int n=0;n<20;n++)
	{
		apt[n]=0;
		Aptno[n]=0;
		SubAptno[n]=0;
	}

	proccount=GetDoc().GetToolsCnt();				//������ѭ���ӹ�����

	if(proccount==1)
	{
		Aptno[0]=GetDoc().GetToolApertureNo(0);		//Aptno[]�б�����Ч����Ȧ����
//		Aptno[0]=GetDoc().GetToolShowApertureNo(0);	
	}
	if(proccount>1)
	{
		for(int m=0;m<GetDoc().GetToolsCnt();m++)
		{
			apt[m]=GetDoc().GetToolApertureNo(m);
//			apt[m]=GetDoc().GetToolShowApertureNo(m);
		}

		for(int i=0;i<GetDoc().GetToolsCnt()-1;i++)
		{
			for(int j=i+1;j<GetDoc().GetToolsCnt();j++)
			{	
				if(apt[j]<apt[i])					//����Ȧ�Ű��մ�С����Ĵ�������
				{
					apt0=apt[i];
					apt[i]=apt[j];		
					apt[j]=apt0;
				}
			}
		}

		Aptno[0]=apt[0];

		jj=0;
		for(int ii=1;ii<GetDoc().GetToolsCnt();ii++)
		{
			apt1=apt[ii-1];
			apt2=apt[ii];

			if(apt2==apt1)
			{
				proccount--;
			}
			else
			{
				jj++;
				Aptno[jj]=apt[ii];
			}
		}
	}

	if(GetDoc().GetToolCycleMode())							//���㸱ѭ���ӹ�����
	{
		subproccount=GetDoc().GetToolsCnt();

		if(subproccount==1)
		{
			SubAptno[0]=GetDoc().GetToolSubApertureNo(0);	//SubAptno[]�б�����Ч����Ȧ����
//			SubAptno[0]=GetDoc().GetToolSubShowApertureNo(0);
		}
		if(subproccount>1)
		{
			for(int m=0;m<GetDoc().GetToolsCnt();m++)
			{
				apt[m]=GetDoc().GetToolSubApertureNo(m); 
//				apt[m]=GetDoc().GetToolSubShowApertureNo(m);
			}

			for(int i=0;i<GetDoc().GetToolsCnt()-1;i++)
			{
				for(int j=i+1;j<GetDoc().GetToolsCnt();j++)
				{	
					if(apt[j]<apt[i])						//����Ȧ�Ű��մ�С����Ĵ�������
					{
						apt0=apt[i];
						apt[i]=apt[j];		
						apt[j]=apt0;
					}
				}
			}

			SubAptno[0]=apt[0];

			jj=0;
			for(int ii=1;ii<GetDoc().GetToolsCnt();ii++)
			{
				apt1=apt[ii-1];
				apt2=apt[ii];

				if(apt2==apt1)
				{
					subproccount--;
				}
				else
				{
					jj++;
					SubAptno[jj]=apt[ii];
				}
			}
		}
	}

//ƽ̨����
	if(!TableAdsorbInProc(nHead))							//ƽ̨����ʧ��ʱ�˳��ӹ�
		return false;

	if(!PeekRunState())
		return FALSE;

//����Ч������
	GetDoc().SetAxisIsRun(0,m_bEnableProcPCB1);							//20180821
	GetDoc().SetAxisIsRun(1,m_bEnableProcPCB2);

//�����ӹ�ǰ�񾵾���У���ͼ��⹦�ʲ���
	if(!GetDoc().GetTestMode())								//����ģʽ������У�������
	{
		if(!CalibrationInProc(nHead))						//У��ʧ��ʱ�˳��ӹ�
			return false;

		if(!PeekRunState())
			return FALSE;
	}

#ifdef MEMORYSTATUSMONITOR

	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	
	GlobalMemoryStatusEx(&status);				//���ú���ȡ��ϵͳ���ڴ����
	
	//�ڴ�(��λ:MB)
	int nTotal=status.ullTotalPhys/1024/1024;	//���ڴ�
	int nAvail=status.ullAvailPhys/1024/1024;	//�����ڴ�
	int nUsed=(nTotal-nAvail);					//�����ڴ�
	CString str;
	
	str.Format("%d M",nUsed);
	GetLog().Append_pro(str,"��ǰ�����ڴ�ʹ����","");

#endif
	
//��ʼ��¼�ӹ�ʱ��
	time(&m_StartTime);
	
//�����Ŀ��ʶ����ش���Ѱ���������У����й��ռӹ���ʽ����Ҫ
	int rtn;

//	for(int iii=0;iii<200;iii++)
//	{
	rtn=TargetDealInProc(nHead,GetExcellonData().GetFiducial().size(),GetExcellonData().GetFiducial(),OUTER);	//���Ű�ʶ��ɹ�����˫��ʶ��ɹ�

	if(rtn==-1)
		return false;
//	}
//������Ŀ��ʶ����ش���Ѱ����������У��ڡ����������ռӹ���ʽ�µ��������з�ʽʱ���д˹���
	if((GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)&&(GetExcellonData().GetInnerFiducialNum()>0))
	{
		double dbDevX,dbDevY;
		
		dbDevX=0.0;
		dbDevY=0.0;

		if(TargetFindInProc(nHead,1,GetExcellonData().GetInnerFiducial(),ASSISTANT,dbDevX,dbDevY)==-1)
		{
			strncpy(ez,GetLang().GetWarningText(22028),256);
			AfxMessageBox(ez);			//"Ѱ�ҷ����е�ʧ�ܣ��޷������ӹ���������ӹ�!"			
			return false;
		}
	}

//�ڲ���Ŀ��ʶ����ش����ȿ�������Ѱ���ڲ�����У��ڡ����������ռӹ���ʽ�µ��ڲ�����з�ʽʱ���д˹���
	if((GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC))
	{
		if(GetDoc().GetIsDrillRegion()&&(!DrillFiducial()))				//�ü�����б�п��� 
		{
			strncpy(ez,GetLang().GetWarningText(22029),256);
			AfxMessageBox(ez);			//"�ӹ��ڲ���ʧ�ܣ��޷������ӹ���������ӹ�!"			
			return false;
		}
		
		if(!GetDoc().GetIsDoubleFileData())								//�ڵ�����4�ڲ�����з�ʽ�²�Ѱ���ڲ������							
		{
//			for(int iii=0;iii<50;iii++)
			rtn=TargetDealInProc(nHead,GetExcellonData().GetInnerFiducial().size(),GetExcellonData().GetInnerFiducial(),INNER);	//���ֶ��ӹ���ʽ�£�����ֵֻ��-1��0
			
			if(rtn==-1)
				return false;
		}
	}

//�ӹ��������ַ�
	rtn=PanelProcessNew(nHead,proccount,Aptno,subproccount,SubAptno);	//Ŀǰ����ֵֻ��-1��0

//�ر���Ч������
	GetDoc().SetAxisIsRun(0,false);							//20180821
	GetDoc().SetAxisIsRun(1,false);	

	if(rtn==-1)
		return false;

//������¼�ӹ�ʱ��
	time(&m_EndTime);
	GetDoc().SetProcTime(difftime(m_EndTime, m_StartTime));				//20161212

//��¼�ӹ���Ϣ
	InfoRecordInProc(nHead);

	if(!PeekRunState())
		return FALSE;

#ifndef PRELOADTEST
//�ӹ����������״̬��λ
	EndProc(Coord(GetDoc().GetTableResetPosX(GetDoc().GetLargeTable()),TABLERESETPOS));
#endif

	return TRUE;
}
/*
BOOL CControl::QueryTableStatus(int nHead,int caseNo)
{
//	ChannelOutput(OFANPOWERON,IO_ON);

	if(!TableClampOperate(false,GetDoc().GetTableClamp()))			//�رռ�ǯ
		return false;

	if(nHead==HeadBoth)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);					//����
		ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
	}
	else if(nHead==HeadLeft)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);					//������
		ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	}
	else if(nHead==HeadRight)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);					//������
		ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
	}
	else
		return false;
	
	Delay(2000);

	BOOL bLeft=false;
	BOOL bRight=false;
	int warningTimes=0;
	
	while(1)
	{
		bLeft=QueryIOBit(ITABLTVACUMM);						//1Ϊ�а壬0Ϊ�ް�
		bRight=QueryIOBit(ITABRTVACUMM);

		if(nHead==HeadBoth)
		{
			m_bMatchTheFirstFid=bLeft&&bRight;
			m_bNoBoard=(!(bLeft||bRight));
			m_bOnlyLeftBoard=bLeft&&(!bRight);
			m_bOnlyRightBoard=(!bLeft)&&bRight;
		}
		else if(nHead==HeadLeft)
		{
			m_bMatchTheFirstFid=bLeft;
			m_bNoBoard=(!bLeft);
			m_bOnlyLeftBoard=bLeft;
			m_bOnlyRightBoard=false;
		}
		else if(nHead==HeadRight)
		{
			m_bMatchTheFirstFid=bRight;
			m_bNoBoard=(!bRight);
			m_bOnlyLeftBoard=false;
			m_bOnlyRightBoard=bRight;
		}
		else
			return false;

		if(caseNo==0)
		{
			if(m_bMatchTheFirstFid)							//��壺���ڱ�ж�λ
				break;
		}
		else if(caseNo==1)
		{
			if(m_bNoBoard)									//�ް壺�����в��ʱ�ӹ�
				break;
		}
		else if(caseNo==2)
		{
			if(m_bMatchTheFirstFid||m_bNoBoard)				//�����ް壺�����޲��ʱ�ӹ�
				break;
		}
		else if(caseNo==3)									//����״̬��ѯ
		{
			break;
		}
		
		warningTimes++;
		if(warningTimes==2)
		{
			AfxMessageBox("ƽ̨�����쳣���޷������ӹ�����ֹͣ�ӹ�!");
			return false;
		}
		
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);		//�ͷ�
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		
		AfxMessageBox("̨���ϰ��������⣬��ȷ�Ϻ���ȷ��!");
		
		if(nHead==HeadBoth)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);					//����
			ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		}
		else if(nHead==HeadLeft)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);					//������
			ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
		}
		else if(nHead==HeadRight)
		{
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);					//������
			ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		}
		else
			return false;

		Delay(1000);
	}

	if(m_bNoBoard)											//���ƽ̨���ް壬��λ�����������״̬
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);			
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	}

	return true;
}
*/
BOOL CControl::QueryTableStatus(int nHead,int caseNo)					//20190725 ��д
{
	BOOL bLeft=false;
	BOOL bRight=false;
	int warningTimes=0;
	
	while(1)
	{
		if(!TableClampOperate(false,GetDoc().GetTableClamp()))			//�رռ�ǯ
			return false;
		
		if(nHead==HeadBoth)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);					//����
			ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		}
		else if(nHead==HeadLeft)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);					//������
			ChannelOutput(OTABLEVACUUMVALVE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		}
		else if(nHead==HeadRight)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);					//������
			ChannelOutput(OTABLEVACUUMVALVE2,IO_ON);
		}
		else
			return false;
		
		Delay(2000);

		bLeft=QueryIOBit(ITABLTVACUMM);						//1Ϊ�а壬0Ϊ�ް�
		bRight=QueryIOBit(ITABRTVACUMM);

		if(nHead==HeadBoth)
		{
			m_bMatchTheFirstFid=bLeft&&bRight;
			m_bNoBoard=(!(bLeft||bRight));
			m_bOnlyLeftBoard=bLeft&&(!bRight);
			m_bOnlyRightBoard=(!bLeft)&&bRight;
		}
		else if(nHead==HeadLeft)
		{
			m_bMatchTheFirstFid=bLeft;
			m_bNoBoard=(!bLeft);
			m_bOnlyLeftBoard=bLeft;
			m_bOnlyRightBoard=false;
		}
		else if(nHead==HeadRight)
		{
			m_bMatchTheFirstFid=bRight;
			m_bNoBoard=(!bRight);
			m_bOnlyLeftBoard=false;
			m_bOnlyRightBoard=bRight;
		}
		else
			return false;

		if(caseNo==0)
		{
			if(m_bMatchTheFirstFid)							//��壺���ڱ�ж�λ
				break;
		}
		else if(caseNo==1)
		{
			if(m_bNoBoard)									//�ް壺�����в��ʱ�ӹ�
				break;
		}
		else if(caseNo==2)
		{
			if(m_bMatchTheFirstFid||m_bNoBoard)				//�����ް壺�����޲��ʱ�ӹ�
				break;
		}
		else if(caseNo==3)									//����״̬��ѯ
		{
			break;
		}
		
		warningTimes++;
		if(warningTimes==2)
		{
			AfxMessageBox("ƽ̨�����쳣���޷������ӹ�����ֹͣ�ӹ�!");
			return false;
		}
		
		if(!TableClampOperate(true,GetDoc().GetTableClamp()))			//�򿪼�ǯ
			return false;

		ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);						//�ͷ�
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		
		AfxMessageBox("̨���ϰ��������⣬��ȷ�Ϻ���ȷ��!");
	}

	if(m_bNoBoard)											//���ƽ̨���ް壬��λ�����������״̬
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);			
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	}

	return true;
}

void CControl::ResetTableStatus()
{
	TableClampOperate(true,GetDoc().GetTableClamp());
	ChannelOutput(OFANPOWERON,IO_OFF); 
	ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
}

void CControl::ResetHandStatus()
{
	if(GetDoc().GetUse9112())
	{
		ChannelOutput(OPROCEXIT,MIO_ON);
		Delay(500);
		ChannelOutput(OPROCEXIT,MIO_OFF);
	}
	else
		SetCOMOutput(9);								//��е�ֽ�������  o����9��	i����9
}

BOOL CControl::WaitUnloadFinish()
{
	if(GetDoc().GetUse9112())
		Delay(20000);									//�ȴ����һ������ѭ�����
	{			
//#ifdef UNLOADISOK
		if(GetDoc().GetUnloadIsOK())
		{
			time_t start_time, end_time;
			end_time = start_time = time( NULL );
			
			while(QueryCOMInput(67))					//��������ɣ�	i����67��	i����67
			{
				end_time = time( NULL );
				
				if(!PeekRunState())
					return false;
				
				if((difftime(end_time, start_time)-m_PauseTimeInSec)>150)
				{				
					GetDoc().SetLastWarningNo(72);		//"���Ϲ��̳��ֹ���"
					return false;				
				}
				
				Delay(LOADANDUNLOADDELAY);
			}
		}
//#else
		else
		{
			if(GetDoc().GetASideIsProcessing())			//�ȴ�A�����һ������ѭ�����
			{
				if(GetDoc().GetFlowPathMode()==0)		//������ʱ
					Delay(24000);
				else
					Delay(120000);						//����ʱ
			}
			else
				Delay(24000);							//�ȴ�B�����һ������ѭ�����
		}
//#endif
	}
	
	return true;
}

int CControl::QueryCOMInput(int bitNo,int refresh)
{
	if((bitNo==16)||(bitNo==24)||(bitNo==26)||(bitNo==28))					//16���������?, 24���������, 26��NG����, 28����е�ִ��󱨾�
		return !GetControlManipulator().GetPLCBitStatus(bitNo,refresh);
	else
		return GetControlManipulator().GetPLCBitStatus(bitNo,refresh);
}

BOOL CControl::SetCOMOutput(int commandNo)
{
/*																
	if(GetDoc().GetProcAxisMode()==0)												//20190307
		return GetControlManipulator().OperatorManipulator(commandNo);
	else
	{
		bool rtn=GetControlManipulator().OperatorManipulator(commandNo);

		if(commandNo==3)
		{
			if(GetDoc().GetProcAxisMode()==1)
				return GetControlManipulator().OperatorManipulator(14);				//����ӹ�ѭ�� o����14��	o����14
			if(GetDoc().GetProcAxisMode()==2)
				return GetControlManipulator().OperatorManipulator(15);				//����ӹ�ѭ�� o����15��	o����15
		}

		return rtn;
	}
*/
/*																					//20190528 �޸�
	bool rtn=GetControlManipulator().OperatorManipulator(commandNo);

	if(commandNo==3)			//��ʼ����
	{
		if(GetDoc().GetProcAxisMode()==1)
			rtn=GetControlManipulator().OperatorManipulator(14);					//����ӹ�ѭ�� o����14��	o����14

		if(GetDoc().GetProcAxisMode()==2)
			rtn=GetControlManipulator().OperatorManipulator(15);					//����ӹ�ѭ�� o����15��	o����15
	}

	return rtn;
*/
	return GetControlManipulator().OperatorManipulator(commandNo);					//20190604
}

BOOL CControl::LoadPCBBoardToTable(int nHead,bool bMode)							//20190604
{
	int iLoadIsReady;				//����׼����ɣ�		i����17��	i����55
	int iOnlyOne;					//�Ƿ������һ�Ű壿	i����19��	i����19
	int oPutBoardOnTable;			//��ƽ̨�Ϸ���			o����6��	o����18
	int iPutOnIsOK;					//�����ϵ�ƽ̨��		i����21��	i����54
	int oLeaveFromTable;			//��е�ֳ���			o����1��	o����19
	int iLeaveIsOK;					//�����ѳ�����е�֣�	i����18��	i����56

	if(!TableClampOperate(true,GetDoc().GetTableClamp()))	//�򿪼�ǯ	//20190725
		return false;

	if(GetDoc().GetUse9112())
	{
		if(!LoadPcb())
			return false;

		return true;
	}
	else
	{
		if(bMode)
		{
			iLoadIsReady=17;
			iOnlyOne=19;
			oPutBoardOnTable=6;
			iPutOnIsOK=21;	
			oLeaveFromTable=1;
			iLeaveIsOK=18;
		}
		else
		{
			iLoadIsReady=55;
			iOnlyOne=19;
			oPutBoardOnTable=18;
			iPutOnIsOK=54;	
			oLeaveFromTable=19;
			iLeaveIsOK=56;
		}
	}

	time_t start_time, end_time;
	end_time = start_time = time( NULL );
	
	while(QueryCOMInput(iLoadIsReady))					//����׼����ɣ�
	{
		end_time = time( NULL );

		if(!PeekRunState())
			return false;

		if((difftime(end_time, start_time)-m_PauseTimeInSec)>90)
		{				
			GetDoc().SetLastWarningNo(69);				//"���ϵ��Ϲ��̳��ֹ���"
			return false;				
		}

		Delay(LOADANDUNLOADDELAY);
	}
	
	if((nHead==HeadBoth)&&(!QueryCOMInput(iOnlyOne)))	//�Ƿ������һ�Ű壿
		m_bOnlyOne=true;

	SetCOMOutput(oPutBoardOnTable);						//��ƽ̨�Ϸ���
	
	end_time = start_time = time( NULL );
	
	while(QueryCOMInput(iPutOnIsOK))					//�����ϵ�ƽ̨��
	{
		end_time = time( NULL );

		if(!PeekRunState())
			return false;
		
		if((difftime(end_time, start_time)-m_PauseTimeInSec)>90)
		{
			GetDoc().SetLastWarningNo(70);				//"���Ϸ��Ϲ��̳��ֹ���"
			return FALSE;
		}

		Delay(LOADANDUNLOADDELAY);
	}

//#ifdef TABLEADSORBFIRST
	if(GetDoc().GetTableAbsorbFirst()==1)
	{
		if((nHead==HeadBoth)&&m_bOnlyOne)				//�ϲ�ֻ�����һ�ŵ���
		{
			if(bMode)
				nHead=HeadLeft;
			else
				nHead=HeadRight;
		}
		
		if(!TableAdsorbInProc(nHead))					//ƽ̨����������ж�
			return false;
	}
//#endif
	
	SetCOMOutput(oLeaveFromTable);						//��е�ֳ���
	
	end_time = start_time = time( NULL );

	while(QueryCOMInput(iLeaveIsOK))					//�ѳ�����е�֣�
	{
		end_time = time( NULL );

		if(!PeekRunState())
			return false;

		if((difftime(end_time, start_time)-m_PauseTimeInSec)>90)
		{
			GetDoc().SetLastWarningNo(71);				//"���ϳ������̳��ֹ���"
			return FALSE;
		}

		Delay(LOADANDUNLOADDELAY);
	}
	
//#ifdef HANDADSORBFIRST
	if(GetDoc().GetTableAbsorbFirst()==0)
	{
		if((nHead==HeadBoth)&&m_bOnlyOne)				//�ϲ�ֻ�����һ�ŵ���
		{
			if(bMode)
				nHead=HeadLeft;
			else
				nHead=HeadRight;
		}
		
		if(!TableAdsorbInProc(nHead))					//ƽ̨����������ж�
			return false;
	}
//#endif
				
	return true;
}

BOOL CControl::UnLoadPCBBoard(int nHead,bool bMode)								//20190604
{
	if(GetDoc().GetProcessState()!=SystemDoc::AUTOPROC)							//20181116
       return false;

	int iUnloadIsReady;				//����׼����ɣ�		i����22��	i����57
	int oGetBoardFromTable;			//��ƽ̨��ȡ��			o����7��	o����21
	int iLeaveIsOK;					//�����ѳ�����е�֣�	i����20��	i����58

	if(GetDoc().GetUse9112())
	{	
		if(!UnloadPcb())
			return false;

		return true;
	}
	else
	{
		if(bMode)
		{
			iUnloadIsReady=22;
			oGetBoardFromTable=7;
			iLeaveIsOK=20;
/*		
			int nNGSum = GetDoc().GetNGSum();

			if(nHead==HeadBoth)
			{
				if(!m_bEnableProcPCB1)
				{
					nNGSum++;
					SetCOMOutput(4);						//���ӹ�ʧ��  o����4��	o����4			
				}
				
				if(!m_bEnableProcPCB2)
				{
					nNGSum++;
					SetCOMOutput(5);						//�Ҳ�ӹ�ʧ��  o����5��	o����5	
				}
			}
			else if(nHead==HeadLeft)
			{
				if(!m_bEnableProcPCB1)
				{
					nNGSum++;
					SetCOMOutput(4);
				}	
			}
			else if(nHead==HeadRight)
			{
				if(!m_bEnableProcPCB2)
				{
					nNGSum++;
					SetCOMOutput(5);
				}	
			}
			
			GetDoc().SetNGSum(nNGSum);
			
			if(nNGSum>GetDoc().GetNGThred())
				GetDoc().SetLastWarningNo(37);				//"NG����"
*/
		}
		else
		{
			iUnloadIsReady=57;
			oGetBoardFromTable=21;
			iLeaveIsOK=58;
		}
	}

	time_t start_time, end_time;
	end_time = start_time = time( NULL );

	while(QueryCOMInput(iUnloadIsReady))					//����׼����ɣ�
	{
		end_time = time( NULL );		

		if(!PeekRunState())
			return false;
		
		if((difftime(end_time, start_time)-m_PauseTimeInSec)>120 )			//20181129 //90
		{
#ifdef USELOG
			GetLog().Append_pro(10065,20027);				//"�����ֵ�������λ�ó�ʱ��","�ȴ�����"
#endif
			GetDoc().SetLastWarningNo(76);					//"����׼�����̳��ֹ���"
			return false;
		}

		Delay(LOADANDUNLOADDELAY);
	}

	if((!GetDoc().GetUse9112())&&bMode)						//20181129
	{	
		int nNGSum = GetDoc().GetNGSum();
		
		if(nHead==HeadBoth)
		{
			if(!m_bEnableProcPCB1)
			{
				nNGSum++;
				SetCOMOutput(4);						//���ӹ�ʧ��  o����4��	o����4			
			}
			
			if(!m_bEnableProcPCB2)
			{
				nNGSum++;
				SetCOMOutput(5);						//�Ҳ�ӹ�ʧ��  o����5��	o����5	
			}
		}
		else if(nHead==HeadLeft)
		{
			if(!m_bEnableProcPCB1)
			{
				nNGSum++;
				SetCOMOutput(4);
			}	
		}
		else if(nHead==HeadRight)
		{
			if(!m_bEnableProcPCB2)
			{
				nNGSum++;
				SetCOMOutput(5);
			}	
		}
		
		GetDoc().SetNGSum(nNGSum);
		
		if(nNGSum>GetDoc().GetNGThred())
			GetDoc().SetLastWarningNo(37);				//"NG����"
	}
	
	SetCOMOutput(oGetBoardFromTable);					//��ƽ̨��ȡ��
	
	end_time = start_time = time( NULL );

	while(QueryCOMInput(iLeaveIsOK))						//�ѳ�����е�֣�
	{
		end_time = time( NULL );		

		if(!PeekRunState())
			return false;

		if((difftime(end_time, start_time)-m_PauseTimeInSec)>90 )
		{
#ifdef USELOG
			GetLog().Append_pro(10066,20027);				//"���ϳ�ʱ��","�ȴ�����"
#endif
			GetDoc().SetLastWarningNo(77);					//"����ȡ�Ϲ��̳��ֹ���"
			return false;
		}

		Delay(LOADANDUNLOADDELAY);
	}

	return true;
}

BOOL CControl::ReLoadPCBBoard()
{
	char ez[256]={""};
	
	strncpy(ez,GetLang().GetWarningText(42008),256);
	int nSel = AfxMessageBox(ez,MB_YESNO);					//"���������ϣ���Ҫ�ٴ����ϼӹ���?"
	
	if(nSel==IDYES)
	{
//		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
//		ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
//		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
//		ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);

		if(GetDoc().GetUse9112())
		{
			ChannelOutput(RELOADBOARD,MIO_ON);				//�ϲ��ٴμ��ϣ��ϲ��а��½�		
			Delay(500);
			ChannelOutput(RELOADBOARD,MIO_OFF);

			Delay(10000);									//�ȴ��ϲ��а��½���λ
		}				
		else
		{
//A&B˫��ģʽ�µ�B->Aת��
			if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)		//20190604
				SetCOMOutput(16);							//����ѭ��������ѭ����

			SetCOMOutput(0);								//�ϲ��ٴμ��ϣ��ϲ��а��½� o����0��	i����0

			Delay(10000);									//�ȴ��ϲ��а��½���λ

#ifdef HIKAGV
			if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)
			{
				if(!AGVTransport(2))
				{
					AfxMessageBox("AGVС�����Ϻ����Ϲ��̳����쳣����ȷ�ϣ�");
					return false;
				}
			}
#endif
		}

		strncpy(ez,GetLang().GetWarningText(42009),256);
		nSel = AfxMessageBox(ez,MB_YESNO);					//"��ȷ�����ϲ������ϣ����ϲ���գ����ڼӹ���ʼ��?"

		if(nSel==IDYES)
		{
//			m_bOnlyOne=FALSE;
//����ָ��
			if(!BeginLoad(GetDoc().GetASideIsProcessing()))	//20190528
				return false;
		}
		else
			return false;

		SetLampStatus(CControl::ORDER);
	}
	else
	{
#ifdef HIKAGV
		if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)
		{
			if(!AGVTransport(1))
				AfxMessageBox("AGVС�����Ϲ��̳����쳣����ȷ�ϣ�");
		}
#endif
		return false;
	}

	return true;
}

BOOL CControl::LoadPCB(int nHead,bool bMode)
{
	m_bOnlyOne=false;
	m_bMatchTheFirstFid=false;							//20190819 ����

//����ָ��
	if(!BeginLoad(bMode))								//20190604
		return false;

//ƽ̨��������λ
	if(GetDoc().GetUse9112())
		MoveTo(GetDoc().GetTabLoadPos());
	else
	{
		if(bMode)
			MoveTo(GetDoc().GetTabLoadPos());
		else
			MoveTo(GetDoc().GetOverTabLoadPos());		
	}

	WaitAxisStop(AXISTAB);

	if(!PeekRunState())									//20190723
		return false;

//��е��������ƽ̨
	if(!LoadPCBBoardToTable(nHead,bMode))				//���ݴ��ϲֵ�ȡ������ı�m_bOnlyOne��״̬���˽׶��м�ǯ�رն�����ƽ̨����������ж�
		return false;

	if((nHead==HeadBoth)&&m_bOnlyOne)
	{
		AfxMessageBox("�ϲ���ֻ��һ�Ű壬�޷�������Ч����!");
		return false;
	}

	return true;
}

BOOL CControl::UnloadPCB(int nHead,bool bMode)
{
	m_bEnableProcPCB1=true;
	m_bEnableProcPCB2=true;
	if(nHead==HeadLeft)
		m_bEnableProcPCB2 =false;
	if(nHead==HeadRight)
		m_bEnableProcPCB1 =false;

//����׼��
	if(GetDoc().GetUse9112())
	{
		ChannelOutput(OUNLOARDMOVETOTABLE,MIO_ON);				//���ϻ�е�ִ���
		Delay(500);
		ChannelOutput(OUNLOARDMOVETOTABLE,MIO_OFF);				
	}
	else
	{
		if(bMode)
		{
			if(GetDoc().GetFlowPathMode()!=0)
				SetCOMOutput(16);								//����ѭ��������ѭ����
/*
			if(GetDoc().GetProcAxisMode()==1)					//20190307	//20190604
			{
				SetCOMOutput(14);								//����ӹ�ѭ�� o����14��	o����14
				Delay(500);
			}

			if(GetDoc().GetProcAxisMode()==2)
			{
				SetCOMOutput(15);								//����ӹ�ѭ�� o����15��	o����15
				Delay(500);
			}
*/			
			SetCOMOutput(13);									//���ϵ�ѭ��	  o����13������13
			Delay(1500);

			SetCOMOutput(2);									//���ϻ�е�ִ���  o����2������20
		}
		else
		{
			SetCOMOutput(17);									//����ѭ��
/*
			if(GetDoc().GetProcAxisMode()==1)					//20190307	//20190604
			{
				SetCOMOutput(14);
				Delay(500);
			}

			if(GetDoc().GetProcAxisMode()==2)
			{
				SetCOMOutput(15);
				Delay(500);
			}
*/
			SetCOMOutput(13);									//���ϵ�ѭ��	  o����13������13
			Delay(1500);

			SetCOMOutput(20);									//���ϻ�е�ִ���  o����2������20
		}

		if(!QueryCOMInput(27))				//�����Ͽ�ʼ���к��ж϶�λ���������Ƿ��а壬ͬʱ�������ϵ�״̬����һ����ѯ 27���������а屨��
		{
			AfxMessageBox("���������ж���İ�,��������");	
			return false;
		}
	}

	if(!PeekRunState())
		return false;

//ƽ̨��������λ��׼������
	if(GetDoc().GetUse9112())
		MoveTo(GetDoc().GetTabUnloadPos());			
	else
	{
		if(bMode)
			MoveTo(GetDoc().GetTabUnloadPos());
		else
			MoveTo(GetDoc().GetOverTabUnloadPos());
	}
	
	WaitAxisStop(AXISTAB);	

//�򿪼�ǯ
	if(!TableClampOperate(true,GetDoc().GetTableClamp()))
		return false;

//ƽ̨�ͷ����
	if(nHead==HeadBoth)											
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	}
	
	if (nHead==HeadLeft)
	{
		ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
	}
	
	if (nHead==HeadRight)
	{
		ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
		ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
	}
	
	if(!PeekRunState())
		return false;

	Delay(1000);
//����
	if(!UnLoadPCBBoard(nHead,bMode))
		return false;

	if(!WaitUnloadFinish())
		return false;

	return true;
}

BOOL CControl::PutPCBToTable(int& mode)
{
	int nHead=HeadBoth;
	int flowPathMode= GetDoc().GetFlowPathMode();
	BOOL bPathMode=true;
	int nSel;
	
	switch(flowPathMode)
	{
	case 0:
	case 1:
		bPathMode=true;
		break;
	case 2:
		nSel = AfxMessageBox("A&B˫��ӹ�����ģʽ�£���ѡ�����̷���A����ѡ���ǡ���B����ѡ���񡱣�",MB_YESNO);

		if(nSel==IDYES)
			bPathMode=true;
		else
			bPathMode=false;
		break;
	case 3:
		bPathMode=false;
		break;
	default:
		AfxMessageBox("�ӹ������趨����!");
		return false;
	}

	if(bPathMode)
		mode=1;
	else
		mode=0;
	
	if(GetDoc().GetProcAxisMode()==1)						//20190604
		nHead=HeadLeft;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=HeadRight;

#ifndef MACHINEHOTTEST
	if(GetDoc().GetProcessState()==CControl::AUTOPROC)		//�Զ��ϰ�	//20190723
	{
		if(!GetDoc().GetUse9112())							//�������ϵ�״̬����һ����ѯ 28����е�ִ��󱨾�
			QueryCOMInput(28);													

		if(!PeekRunState())									//��ͣ������
			return false;
	}

//�򿪷��
	ChannelOutput(OFANPOWERON,IO_ON);

	if(GetDoc().GetProcessState()==CControl::AUTOPROC)		//�Զ��ϰ�
	{
//�ж�̨�����Ƿ��ް�
		if(!QueryTableStatus(nHead,1))						//20190604
		{
			ResetTableStatus();
			return false;
		}

		nSel = AfxMessageBox("��ȷ�����ϲ������������Ű壬������ѡ���ǡ���ȡ����ѡ����!",MB_YESNO);

		if(nSel==IDNO)
		{
			ResetTableStatus();
			return false;
		}

//�Զ����ʱ���Զ��ϰ���̨��֮ǰ���л�׼У��
		if(GetDoc().GetThickingType())
		{
			long lThickZero[2]={0,0};;

//			if(!TestThicknessAL(lThickZero,nHead))							//20190604
			if(!TestThicknessAL(lThickZero,nHead,Coord(GetDoc().GetThicknessX(),GetDoc().GetThicknessY())))		//20190725
			{
				AfxMessageBox("��׼���������쳣���������������ȷ�ϣ�");

				ResetTableStatus();
				return false;
			}
			
			GetDoc().SetThicknessZero(lThickZero[0],HeadLeft);
			GetDoc().SetThicknessZero(lThickZero[1],HeadRight);	
		}

//		int nHead=HeadBoth;												//20190307

//		if(GetDoc().GetProcAxisMode()==1)
//			nHead=HeadLeft;
//		if(GetDoc().GetProcAxisMode()==2)
//			nHead=HeadRight;

		if(GetDoc().GetProcAxisMode()==1)				//20190604
			GetControl().SetCOMOutput(14);				//����ӹ�ѭ�� o����14��	o����14
		if(GetDoc().GetProcAxisMode()==2)
			GetControl().SetCOMOutput(15);				//����ӹ�ѭ�� o����15��	o����15

		if(!PeekRunState())								//20190723 ��ͣ������
		{
			ResetTableStatus();
			return false;
		}
		
		if(!LoadPCB(nHead,bPathMode))
		{	
//			if(GetDoc().GetUse9112())
//			{
//				ChannelOutput(OPROCEXIT,MIO_ON);
//				Delay(500);
//				ChannelOutput(OPROCEXIT,MIO_OFF);
//			}
//			else
//				SetCOMOutput(9);						//��е�ֽ�������  o����9��	i����9
			
//			ChannelOutput(OFANPOWERON,IO_OFF);

			ResetProcStatus();
			return false;
		}

		Delay(6000);									//20190604
//		if(GetDoc().GetUse9112())
//		{
//			ChannelOutput(OPROCEXIT,MIO_ON);
//			Delay(500);
//			ChannelOutput(OPROCEXIT,MIO_OFF);
//		}
//		else
//			SetCOMOutput(9);							//��е�ֽ�������  o����9��	i����9

		ResetHandStatus();

		if(!PeekRunState())								//20190723 ��ͣ������
		{
			ResetTableStatus();
			return false;
		}
	}
	else												//�ֶ��ϰ�
	{
//�ж�̨�����Ƿ����
		if(!QueryTableStatus(nHead,0))					//20190604
		{
			ResetTableStatus();
			return false;
		}	
	}
#endif

	return true;
}

BOOL CControl::GetPCBFromTable()
{
	int flowPathMode= GetDoc().GetFlowPathMode();
	BOOL bPathMode=true;
	int nSel;
	
	switch(flowPathMode)
	{
	case 0:
	case 1:
		bPathMode=true;
		break;
	case 2:
		nSel = AfxMessageBox("A&B˫��ӹ�����ģʽ�£���ѡ�����̷���A����ѡ���ǡ���B����ѡ���񡱣�",MB_YESNO);

		if(nSel==IDYES)
			bPathMode=true;
		else
			bPathMode=false;
		break;
	case 3:
		bPathMode=false;
		break;
	default:
		AfxMessageBox("�ӹ������趨����!");
		return false;
	}

	int nHead=HeadBoth;
//	m_bMatchTheFirstFid=false;
	m_bNoBoard=false;
	m_bOnlyLeftBoard=false;
	m_bOnlyRightBoard=false;
	
	if(GetDoc().GetProcAxisMode()==1)				//20190307
		nHead=HeadLeft;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=HeadRight;

	if(!GetDoc().GetUse9112())						//�������ϵ�״̬����һ����ѯ 28����е�ִ��󱨾�	//20190723
		QueryCOMInput(28);

	if(!PeekRunState())								//��ͣ������
		return false;	

//�򿪷��
	ChannelOutput(OFANPOWERON,IO_ON);
	
//��ѯ̨��״̬
	if(!QueryTableStatus(nHead,3))
	{
		ResetTableStatus();
		return false;
	}
	
	if(m_bNoBoard)
	{
		AfxMessageBox("ƽ̨��û�а壬�޷����ϣ�");
		
		ResetTableStatus();
		return false;
	}
	
	if(nHead==HeadBoth)
	{
		if(m_bOnlyLeftBoard||m_bOnlyRightBoard)
		{
			AfxMessageBox("ƽ̨�ϰ������ԣ��޷����ϣ�");
			
			ResetTableStatus();
			return false;
		}
	}

	if(GetDoc().GetProcAxisMode()==1)				//20190604
		GetControl().SetCOMOutput(14);				//����ӹ�ѭ�� o����14��	o����14
	if(GetDoc().GetProcAxisMode()==2)
		GetControl().SetCOMOutput(15);				//����ӹ�ѭ�� o����15��	o����15

	if(!PeekRunState())								//��ͣ������
	{
		ResetTableStatus();
		return false;
	}	

	if(!UnloadPCB(nHead,bPathMode))
	{	
//		if(GetDoc().GetUse9112())
//		{
//			ChannelOutput(OPROCEXIT,MIO_ON);
//			Delay(500);
//			ChannelOutput(OPROCEXIT,MIO_OFF);
//		}
//		else
//			SetCOMOutput(9);						//��е�ֽ�������  o����9��	i����9

//		ChannelOutput(OFANPOWERON,IO_OFF);

		ResetProcStatus();
		return false;
	}

	ResetProcStatus();

	return true;
}

BOOL CControl::UnLoadPCBBoardToNG(int nHead)					//UnLoadPCBBoard��ͬ����ʱ��ƽ̨����ͷ�����ѡ���	//20190604
{
	if(!PeekRunState())
		return false;

	if(GetDoc().GetUse9112())
	{
		ChannelOutput(OUNLOARDMOVETOTABLE,MIO_ON);				//���ϻ�е�ִ���
		Delay(500);
		ChannelOutput(OUNLOARDMOVETOTABLE,MIO_OFF);	
		
		MoveTo(GetDoc().GetTabUnloadPos());						//ƽ̨��������λ				
	}
	else
	{
		if (GetDoc().GetASideIsProcessing())
		{
//			if(cycleno==0)						//20181204		//20190528
//				SetCOMOutput(3);								//��ʼ���� o����3��	o����3

			SetCOMOutput(2);									//���ϻ�е�ִ���  o����2������20
			
			MoveTo(GetDoc().GetTabUnloadPos());					//ƽ̨������������λ			
		}
		else
		{
//			if(cycleno==0)						//20181203		//20190528
//			{
//				Delay(30000);									//�����е�������ϣ�����ȴ���е�ֽ��Ϸ����ϲֺ��ٷ�������ָ��

//				SetCOMOutput(17);								//����ѭ��
//				SetCOMOutput(3);								//��ʼ���� o����3��	o����3
//			}

			if(cycleno==0)										//20191225
			{
				SetCOMOutput(17);								//����ѭ��
				SetCOMOutput(3);								//��ʼ���� o����3��	o����3
			}

			SetCOMOutput(22);									//����NGȡ��׼��  o�����ޣ�����22

			MoveTo(GetDoc().GetOverTabLoadPos());				//ƽ̨������������λ		
		}
	}

	WaitAxisStop(AXISTAB);
	
	if(!TableClampOperate(true,GetDoc().GetTableClamp()))		//�򿪼�ǯ
		return false;

//�ر���Ч������
	GetDoc().SetAxisIsRun(0,false);								//20180821
	GetDoc().SetAxisIsRun(1,false);

	if(nHead==HeadBoth)											//ƽ̨�ͷ����
	{
		if(!m_bEnableProcPCB1)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		}
		
		if(!m_bEnableProcPCB2)
		{
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		}
	}
	
	if (nHead==HeadLeft)
	{
		if(!m_bEnableProcPCB1)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		}
	}
	
	if (nHead==HeadRight)
	{
		if(!m_bEnableProcPCB2)
		{
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		}
	}

	if(!PeekRunState())
		return false;

	Delay(1000);

	if (GetDoc().GetASideIsProcessing())
	{
		if(!UnLoadPCBBoard(nHead,true))					//��NG�����NG�֣�����������������
			return false;
	}
	else
	{		
		int nNGSum = GetDoc().GetNGSum();
		
		if(nHead==HeadBoth)
		{
			if(!m_bEnableProcPCB1)
			{
				nNGSum++;
				SetCOMOutput(4);						//���ӹ�ʧ��  o����4��	o����4			
			}
			
			if(!m_bEnableProcPCB2)
			{
				nNGSum++;
				SetCOMOutput(5);						//�Ҳ�ӹ�ʧ��  o����5��	o����5	
			}
		}
		else if(nHead==HeadLeft)
		{
			if(!m_bEnableProcPCB1)
			{
				nNGSum++;
				SetCOMOutput(4);
			}	
		}
		else if(nHead==HeadRight)
		{
			if(!m_bEnableProcPCB2)
			{
				nNGSum++;
				SetCOMOutput(5);
			}	
		}
		
		GetDoc().SetNGSum(nNGSum);
		
		if(nNGSum>GetDoc().GetNGThred())
			GetDoc().SetLastWarningNo(37);					//"NG����"
		
//����NG����
//		SetCOMOutput(22);									//����NGȡ��׼��		o�����ޣ�	����22	//20181122

		int iUnloadIsReady=52;								//����׼����ɣ�		i�����ޣ�	i����52
		int oGetBoardFromTable=23;							//��ƽ̨��ȡ��			o�����ޣ�	o����23
		int iLeaveIsOK=53;									//�����ѳ�����е�֣�	i�����ޣ�	i����53
		
		time_t start_time, end_time;	
		end_time = start_time = time( NULL );
		
		while(QueryCOMInput(iUnloadIsReady))				//����׼����ɣ�
		{
			end_time = time( NULL );			

			if(!PeekRunState())
				return false;
			
			if((difftime(end_time, start_time)-m_PauseTimeInSec)>120 )		//20181129 //90
			{
#ifdef USELOG
				GetLog().Append_pro(10065,20027);			//"�����ֵ�������λ�ó�ʱ��","�ȴ�����"
#endif
				GetDoc().SetLastWarningNo(76);				//"����׼�����̳��ֹ���"
				return false;
			}
			
			Delay(LOADANDUNLOADDELAY);
		}
		
		SetCOMOutput(oGetBoardFromTable);					//��ƽ̨��ȡ��
		
		end_time = start_time = time( NULL );
		
		while(QueryCOMInput(iLeaveIsOK))					//�ѳ�����е�֣�
		{
			end_time = time( NULL );			

			if(!PeekRunState())
				return false;

			if((difftime(end_time, start_time)-m_PauseTimeInSec)>90 )
			{
#ifdef USELOG
				GetLog().Append_pro(10066,20027);				//"���ϳ�ʱ��","�ȴ�����"
#endif
				GetDoc().SetLastWarningNo(77);					//"����ȡ�Ϲ��̳��ֹ���"
				return false;
			}

			Delay(LOADANDUNLOADDELAY);
		}
	}
	
	return true;
}

BOOL CControl::BeginLoad(bool bMode)
{
	if(GetDoc().GetUse9112())							//���Use9112����˵�����ģʽ�е�4��ѡ��ȫΪ��ɫ����ѡ������4��ѡ��ͬʱ��Ч������4��ѡ���е�ѡ�����趨A����B״̬
	{
		ChannelOutput(OAOTUBIGN,MIO_ON);				//��ʼ���У�����4����ѭ��ǰ��ȫNG�ٴ����ϡ����ʶ��󣨷����ӹ�ǰ���ͷ����ӹ�ʱ	
		Delay(500);
		ChannelOutput(OAOTUBIGN,MIO_OFF);

		if(!PeekRunState())
			return FALSE;

		if(!m_bMatchTheFirstFid)							//20190819 ����
		{
			Delay(DELAYTIMEFORNOBOARD);						//��ʱ�������ϲֶ��������ϼ��
			
			if(!QueryIOBit(IDEPOTEMPTY))					//������ϲ��Ƿ��ް�				
			{
				GetDoc().SetLastWarningNo(78);				//"���ϲ��ް�"
				return false;			
			}
		}
	}
	else												
	{
		if(bMode)
		{
#ifdef HIKAGV
			if((GetDoc().GetFlowPathMode()==AANDBDOUBLE)&&(!GetDoc().GetPCBBoardIsReady()))
			{
				if(!AGVTransport(0))
				{
					AfxMessageBox("AGVС�����Ϲ��̳����쳣����ȷ�ϣ�");
					return false;
				}
			}
#endif
			if(GetDoc().GetFlowPathMode()!=0)
				SetCOMOutput(16);						//��A�棨���壩��A&B˫��A��ʱ������ѭ��������ѭ����
		}
		else
			SetCOMOutput(17);							//��B���A&B˫��B��ʱ������ѭ��
		
		SetCOMOutput(3);								//��ʼ���� o����3��	o����3
		
		if(!QueryCOMInput(27))							//�����Ͽ�ʼ���к��ж϶�λ���������Ƿ��а壬ͬʱ�������ϵ�״̬����һ����ѯ 27���������а屨��
		{
			SetLampStatus(CControl::ERR);
			ChannelOutput(OCOMMONALARM ,TRUE);
			
			AfxMessageBox("���϶˹��������ж���İ�,��������");
			
			SetLampStatus(CControl::ORDER);
			ChannelOutput(OCOMMONALARM ,FALSE);
			
			return false;
		}

		if(!PeekRunState())
			return FALSE;

		if(!m_bMatchTheFirstFid)							//20190819 ����
		{
			Delay(DELAYTIMEFORNOBOARD);						//��ʱ�������ϲֶ��������ϼ��
			
			if(!QueryCOMInput(25))							//������ϲ��Ƿ��ް� i����25��	i����25
			{
				GetDoc().SetLastWarningNo(78);				//"���ϲ��ް�"
				return false;
			}
		}
	}

	if(!PeekRunState())
		return FALSE;

	return true;
}

BOOL CControl::AutoProcPCB(int nHead)
{
	char ez[256]={""};
	int headMode=nHead;

//���ڼ���ӹ�ѭ�������Ͱ���Ȧ�����еļӹ�˳��
	int proccount,apt0,apt1,apt2,jj,Aptno[20],apt[20];
	int subproccount,SubAptno[20];

//���ڸ�������ļ���Ϣ����״̬
	BOOL bDataIsSwitched=false;

//��ʼ���ӹ�����
	if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)
	{
		int nSel = AfxMessageBox("A&B˫��ӹ�����ģʽ�£���ѡ�����̷���A����ѡ���ǡ���B����ѡ���񡱣�",MB_YESNO);

		CMainFrame* pMainFrame;										//20190604
		pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
		if(nSel==IDYES)
		{
			GetDoc().SetASideIsProcessing(true);

			pMainFrame->m_wndStatusBar.SetPaneText(2,"  �ӹ�:A��");
			GetDoc().SetASideIsDisplay(true);
			pMainFrame->m_wndStatusBar.SetPaneText(1,"  ��ʾ:A��");
		}
		else
		{
			GetDoc().SetASideIsProcessing(false);

			pMainFrame->m_wndStatusBar.SetPaneText(2,"  �ӹ�:B��");
			GetDoc().SetASideIsDisplay(false);
			pMainFrame->m_wndStatusBar.SetPaneText(1,"  ��ʾ:B��");
		}
	}

//��ʼ��̨��״̬��������׼��״̬
	m_bMatchTheFirstFid=false;
//	BOOL bFirstIsLoaded=false;

#ifndef MACHINEHOTTEST
//�ж�̨�����Ƿ��ް�������
	if(!QueryTableStatus(nHead,2))
		return false;

	if(!PeekRunState())
		return false;

//����ָ��
//	if(!BeginLoad(GetDoc().GetASideIsProcessing()))					//20190528
//		return false;
	if(GetDoc().GetASideIsProcessing()||(!m_bMatchTheFirstFid))		//20191218	B��̨���а�ʱ��ȥ�ϲ�ץ��
	{
		if(!BeginLoad(GetDoc().GetASideIsProcessing()))
			return false;
	}
#endif

//��ʼ�ӹ�ѭ��
	cycleno=0;												//����ȷ�Ϻ�ʱ��Ҫ���в���׼У�������ڼ�¼A�����B��ļӹ�ѭ�����������һѭ��̨���а壬��ѭ������
	int cycle=1;
	long procTime1=0;
	long procTime2=0;

	m_panelProcessTime=0;

	while(1)
	{
//�ر���Ч������
		GetDoc().SetAxisIsRun(0,false);						//20180821
		GetDoc().SetAxisIsRun(1,false);	

		time(&m_StartTime);									//20161212 ����׼���������Զ�У���������Զ�����

		if(!bDataIsSwitched)	//����״������Ч��1������whileʱ��2����while��A->B�л���3����while��B->A�л����ٴ����ϣ�					
		{
			bDataIsSwitched=true;

			if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)	//�����A&B˫������ģʽ������Ҫ���ݵ�ǰ��A�滹��B��ӹ�״̬������Ӧ�������ļ��������˫��ģʽ��������������ļ�
			{
				cycleno=0;
				cycle=1;
				procTime1=0;
				procTime2=0;

				m_panelProcessTime=0;

				CMainFrame* pMainFrame;										//20190604
				pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();

				if(GetDoc().GetASideIsProcessing())
				{
					if(!pFileInfoSettingView->SwitchDataFile(0))
						return false;

					GetDoc().SetFileToRealRelative(GetDoc().GetFileToRealRelative2(0));

					GetDoc().SetASideIsDisplay(true);

					pMainFrame->m_wndStatusBar.SetPaneText(2,"  �ӹ�:A��");
					pMainFrame->m_wndStatusBar.SetPaneText(1,"  ��ʾ:A��");
				}
				else
				{
					if(!pFileInfoSettingView->SwitchDataFile(1))
						return false;

					GetDoc().SetFileToRealRelative(GetDoc().GetFileToRealRelative2(1));

					GetDoc().SetASideIsDisplay(false);

					pMainFrame->m_wndStatusBar.SetPaneText(2,"  �ӹ�:B��");
					pMainFrame->m_wndStatusBar.SetPaneText(1,"  ��ʾ:B��");
				}
				::SendMessage(GetMainFrame().m_Framework.Get(MAINRUNVIEW)->GetWnd()->m_hWnd,WM_USERUPDATEFILANAME,0,0);
/*																						//20200601 ȡ��
#ifdef SMCPreLoad				
				if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//20200107 ��������Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
				{
					if(!PreLoadCreate(true,false,false))
					{		
						AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
						return false;
					}
				}
#endif
*/
			}

#ifdef SMCPreLoad																		//20200601 �������˴�
			if((!GetDoc().GetSysCircleProcMode())&&(!GetDoc().GetIsDoubleFileData()))	//Ԥ���ع��ܲ�֧�ִ�����պ�˫����6/8�ڲ�����з�ʽ
			{
				if(!PreLoadCreate(true,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))	//20180619
				{		
					AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
					return false;
				}
			}
			else																		//20191015
			{
				if(!PreLoadCreate(false,(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC),true))
				{		
					AfxMessageBox("�ӹ�����Ԥ���ع��̳��ִ�����ȷ�ϣ�");
					return false;
				}
			}
#endif
			
//����ӹ�ѭ�������Ͱ���Ȧ�����еļӹ�˳��Ϊ�����AB�����ļ����л������ѭ�����ݼ�������while��	
			for(int n=0;n<20;n++)
			{
				apt[n]=0;
				Aptno[n]=0;
				SubAptno[n]=0;
			}
			
			proccount=GetDoc().GetToolsCnt();				//������ѭ���ӹ�����
			
			if(proccount==1)
			{
				Aptno[0]=GetDoc().GetToolApertureNo(0);		//Aptno[]�б�����Ч����Ȧ����
//				Aptno[0]=GetDoc().GetToolShowApertureNo(0);	
			}
			if(proccount>1)
			{
				for(int m=0;m<GetDoc().GetToolsCnt();m++)
				{
					apt[m]=GetDoc().GetToolApertureNo(m);
//					apt[m]=GetDoc().GetToolShowApertureNo(m);
				}
				
				for(int i=0;i<GetDoc().GetToolsCnt()-1;i++)
				{
					for(int j=i+1;j<GetDoc().GetToolsCnt();j++)
					{	
						if(apt[j]<apt[i])					//����Ȧ�Ű��մ�С����Ĵ�������
						{
							apt0=apt[i];
							apt[i]=apt[j];		
							apt[j]=apt0;
						}
					}
				}
				
				Aptno[0]=apt[0];
				
				jj=0;
				for(int ii=1;ii<GetDoc().GetToolsCnt();ii++)
				{
					apt1=apt[ii-1];
					apt2=apt[ii];
					
					if(apt2==apt1)
					{
						proccount--;
					}
					else
					{
						jj++;
						Aptno[jj]=apt[ii];
					}
				}
			}
			
			if(GetDoc().GetToolCycleMode())							//���㸱ѭ���ӹ�����
			{
				subproccount=GetDoc().GetToolsCnt();
				
				if(subproccount==1)
				{
					SubAptno[0]=GetDoc().GetToolSubApertureNo(0);	//SubAptno[]�б�����Ч����Ȧ����
//					SubAptno[0]=GetDoc().GetToolSubShowApertureNo(0);
				}
				if(subproccount>1)
				{
					for(int m=0;m<GetDoc().GetToolsCnt();m++)
					{
						apt[m]=GetDoc().GetToolSubApertureNo(m); 
//						apt[m]=GetDoc().GetToolSubShowApertureNo(m);
					}
					
					for(int i=0;i<GetDoc().GetToolsCnt()-1;i++)
					{
						for(int j=i+1;j<GetDoc().GetToolsCnt();j++)
						{	
							if(apt[j]<apt[i])						//����Ȧ�Ű��մ�С����Ĵ�������
							{
								apt0=apt[i];
								apt[i]=apt[j];		
								apt[j]=apt0;
							}
						}
					}
					
					SubAptno[0]=apt[0];
					
					jj=0;
					for(int ii=1;ii<GetDoc().GetToolsCnt();ii++)
					{
						apt1=apt[ii-1];
						apt2=apt[ii];
						
						if(apt2==apt1)
						{
							subproccount--;
						}
						else
						{
							jj++;
							SubAptno[jj]=apt[ii];
						}
					}
				}
			}
		}

//ѭ���ӹ�״̬��ʼ��
		GetDoc().SetCurPCBDrilledHoleCount(0);
		GetDoc().SetCurPCBDrilledArea(0);
		m_lCurDrillHoleNo = 0;
		SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);

		m_bOnlyOne=false;								//�Զ�������˫��ӹ�ģʽ�£��ϲ�ֻ�����һ�ŵ��壬����е����ֻ��һ�Ű�
		nHead=headMode;

		m_bLoadIsReady=false;
		m_bUnloadIsReady=false;

//		if(m_bMatchTheFirstFid)											//20190528
		if(m_bMatchTheFirstFid&&GetDoc().GetASideIsProcessing())		//20191218
			m_bLoadIsReady=true;
		
		m_bEnableProcPCB1=true;
		m_bEnableProcPCB2=true;
		if(nHead==HeadLeft)
			m_bEnableProcPCB2 =false;
		if(nHead==HeadRight)
			m_bEnableProcPCB1 =false;
		
		if(!m_bMatchTheFirstFid)		//�״�ѭ����̨�������б�ж�λ��(true)ʱ���Զ�����׼У���޷����У�ֻ������һ������ǰ���У������״�Z�����ƺ����Ϲ���Ҳ������
		{
#ifndef MACHINEHOTTEST
//ÿ��ѭ����ʼʱ���ȼ�����ϲ��Ƿ��ް�
			int binStatus=1;
			
			if(GetDoc().GetUse9112())
				binStatus=QueryIOBit(IDEPOTEMPTY);				//������ϲ��Ƿ��ް�				
			else
				binStatus=QueryCOMInput(25);					//������ϲ��Ƿ��ް� i����25��	i����25

			if(!binStatus)										//�Ƿ��ް�			
			{
				if(!WaitUnloadFinish())							//20190725
					return false;

//A&B˫��A��ʱ�ް����Զ�����A->Bת��
				if((GetDoc().GetFlowPathMode()==AANDBDOUBLE)&&GetDoc().GetASideIsProcessing())
				{
					bDataIsSwitched=false;
					GetDoc().SetASideIsProcessing(false);
					
					SetCOMOutput(17);							//�л�������ѭ��
					SetCOMOutput(3);							//��ʼ���� o����3��	o����3
					
					continue;
				}
				
//����������ģʽ�£���A�桢��B�桢A&B˫��B��ʱ�ް�����ʾ����ش���				
				GetDoc().SetErrorPCB(0);						//��¼�Զ������ϼӹ�����������ԭ����ֵ��쳣�����������ڵ���6�ź󱨾������򲻱���
				GetDoc().SetLastWarningNo(78);					//"���ϲ��ް�"
				
//A&B˫��ģʽ�µ�B->Aת��
				if(GetDoc().GetFlowPathMode()==AANDBDOUBLE)		//20190604
				{
					bDataIsSwitched=false;
					GetDoc().SetASideIsProcessing(true);
				}
				
				if(ReLoadPCBBoard())							//20190604
					continue;
				else
					break;
			}
#endif
			cycleno++;

//�Զ����ʱ���Զ��ϰ���̨��֮ǰ���л�׼У����50��ѭ����һ��
			if(GetDoc().GetThickingType()&&((cycleno%50)==1))
			{
				long lThickZero[2]={0,0};;

//				if(!TestThicknessAL(lThickZero,headMode))
				if(!TestThicknessAL(lThickZero,headMode,Coord(GetDoc().GetThicknessX(),GetDoc().GetThicknessY())))		//20190725
				{
					strncpy(ez,GetLang().GetWarningText(21040),256);
					AfxMessageBox(ez);//"��׼���������쳣���޷������ӹ���������ӹ�!"
					return false;
				}

				GetDoc().SetThicknessZero(lThickZero[HeadLeft],HeadLeft);
				GetDoc().SetThicknessZero(lThickZero[HeadRight],HeadRight);
				
				if(!PeekRunState())
					return FALSE;
			}

//ѭ���ӹ�ʱZ�����Ƶ�CCD����λ��(�������Ч��)
			ZAxisCCDFocus(nHead,GetDoc().GetPCBThickness(),false);

			if(!PeekRunState())
				return FALSE;

#ifndef MACHINEHOTTEST
//ƽ̨��������λ
			if(GetDoc().GetUse9112())
				MoveTo(GetDoc().GetTabLoadPos());
			else
			{
				if(GetDoc().GetASideIsProcessing())
					MoveTo(GetDoc().GetTabLoadPos());
				else
					MoveTo(GetDoc().GetOverTabLoadPos());		
			}

			WaitAxisStop(AXISTAB);

//��е��������ƽ̨
			if(!LoadPCBBoardToTable(nHead,GetDoc().GetASideIsProcessing()))	//���ݴ��ϲֵ�ȡ������ı�m_bOnlyOne��״̬���˽׶��м�ǯ�رն�����ƽ̨����������ж�
				return false;

			if((nHead==HeadBoth)&&m_bOnlyOne)				//˫��ӹ�ģʽ���ϲ�ֻ�����һ�ŵ���
			{
				if (GetDoc().GetASideIsProcessing())
				{
					nHead=HeadLeft;
					m_bEnableProcPCB2 =false;
				}
				else
				{
					nHead=HeadRight;
					m_bEnableProcPCB1 =false;
				}
			}
#endif
		}
		else
			m_bMatchTheFirstFid = false;

//����Ч������
		GetDoc().SetAxisIsRun(0,m_bEnableProcPCB1);							//20180821
		GetDoc().SetAxisIsRun(1,m_bEnableProcPCB2);

		WaitAxisStop(AXISLEFTZ);
		WaitAxisStop(AXISRIGHTZ);

		if(!PeekRunState())
			return FALSE;

//�����ӹ�ǰ�񾵾���У���ͼ��⹦�ʲ���
		if(!GetDoc().GetTestMode())							//����ģʽ������У�������
		{
			if(!CalibrationInProc(headMode))				//˫��ӹ�ʱ��У�����������һ��δͨ����false
				return false;

			if(!PeekRunState())
				return FALSE;
		}

#ifdef MEMORYSTATUSMONITOR

		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		
		GlobalMemoryStatusEx(&status);				//���ú���ȡ��ϵͳ���ڴ����
		
		//�ڴ�(��λ:MB)
		int nTotal=status.ullTotalPhys/1024/1024;	//���ڴ�
		int nAvail=status.ullAvailPhys/1024/1024;	//�����ڴ�
		int nUsed=(nTotal-nAvail);					//�����ڴ�
		CString str;

		str.Format("%d M",nUsed);
		GetLog().Append_pro(str,"��ǰ�����ڴ�ʹ����","");

#endif

//��ʼ��¼�ӹ�ʱ�䣬ʱ����������ʱ�����ʶ������+�ڱ�У���ʱ�������ӹ���ʱ���ַ��ӹ���ʱ����B��ӹ�ʱ��������ʶ����ִ��󣬻�������NG������ʱ
		time(&m_StartTime);

//�Զ����
		if(GetDoc().GetThickingType())						//˫��ӹ�ʱ���������һ��δͨ����false
		{
			BOOL bUseAlarm=false;
#ifdef USEAUTOTHICKERROR
			bUseAlarm=true;
#endif
			if(!ThicknessMeasureInProc(nHead,bUseAlarm))
				return false;

			if(!PeekRunState())
				return false;
		} 

//�����Ŀ��ʶ����ش���Ѱ���������У����й��ռӹ���ʽ����Ҫ
		int rtn=TargetDealInProc(nHead,GetExcellonData().GetFiducial().size(),GetExcellonData().GetFiducial(),OUTER);

		if(rtn==-1)
			return false;

		if(rtn==1)
		{
			cycle++;
/*
			if(!m_bLoadIsReady)											//20190528
			{
				if(GetDoc().GetUse9112())
				{
					ChannelOutput(OAOTUBIGN,MIO_ON);					//��ʼ���У��������ϣ�		
					Delay(500);
					ChannelOutput(OAOTUBIGN,MIO_OFF);
				}
				else
					SetCOMOutput(3);									//��ʼ���У��������ϣ� o����3��	o����3
			}
*/
			continue;
		}

//������Ŀ��ʶ����ش���Ѱ����������У��ڡ����������ռӹ���ʽ�µ��������з�ʽʱ���д˹���
		if((GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)&&(GetExcellonData().GetInnerFiducialNum()>0))
		{
			double dbDevX,dbDevY;
			
			dbDevX=0.0;
			dbDevY=0.0;
			
			if(TargetFindInProc(nHead,1,GetExcellonData().GetInnerFiducial(),ASSISTANT,dbDevX,dbDevY)==-1)
			{
				strncpy(ez,GetLang().GetWarningText(22028),256);
				AfxMessageBox(ez);				//"Ѱ�ҷ����е�ʧ�ܣ��޷������ӹ���������ӹ�!"			
				return false;
			}
		}

//�ڲ���Ŀ��ʶ����ش����ȿ�������Ѱ���ڲ�����У��ڡ����������ռӹ���ʽ�µ��ڲ�����з�ʽʱ���д˹���
		if((GetDoc().GetFileMode()==SystemDoc::NORMALPROC)&&(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC))
		{
			if(GetDoc().GetIsDrillRegion()&&(!DrillFiducial()))			//�ü�����б�п��� 
			{
				strncpy(ez,GetLang().GetWarningText(22029),256);
				AfxMessageBox(ez);				//"�ӹ��ڲ���ʧ�ܣ��޷������ӹ���������ӹ�!"			
				return false;
			}

			if(!GetDoc().GetIsDoubleFileData())							//�ڵ�����4�ڲ�����з�ʽ�²�Ѱ���ڲ������								
			{
				rtn=TargetDealInProc(nHead,GetExcellonData().GetInnerFiducial().size(),GetExcellonData().GetInnerFiducial(),INNER);
				
				if(rtn==-1)
					return false;
				
				if(rtn==1)
				{
					cycle++;
/*
					if(!m_bLoadIsReady)									//20190528
					{
						if(GetDoc().GetUse9112())
						{
							ChannelOutput(OAOTUBIGN,MIO_ON);			//��ʼ���У��������ϣ�		
							Delay(500);
							ChannelOutput(OAOTUBIGN,MIO_OFF);
						}
						else
							SetCOMOutput(3);							//��ʼ���У��������ϣ� o����3��	o����3
					}
*/
					continue;
				}
			}
		}

#ifndef MACHINEHOTTEST
//Ŀ��ʶ��󣨷����ӹ�ǰ��ִ����������ָ��	
		if(!m_bLoadIsReady)												//20190528
		{
			if(m_panelProcessTime<=GetDoc().GetLoadOptimize())
			{
				m_bLoadIsReady=true;

				if(!GetDoc().GetASideIsProcessing())
					SetCOMOutput(17);									//����ѭ��				
				
				if(GetDoc().GetUse9112())
				{
					ChannelOutput(OAOTUBIGN,MIO_ON);					//��ʼ���У��������ϣ�		
					Delay(500);
					ChannelOutput(OAOTUBIGN,MIO_OFF);
				}
				else
					SetCOMOutput(3);									//��ʼ���У��������ϣ� o����3��	o����3				
			}
		}
#endif

//�ӹ��������ַ�
		rtn=PanelProcessNew(nHead,proccount,Aptno,subproccount,SubAptno);	//Ŀǰ����ֵֻ��-1��0
		
		if(rtn==-1)
			return false;

//������¼�ӹ�ʱ��
		time(&m_EndTime);
		GetDoc().SetProcTime(difftime(m_EndTime, m_StartTime));			//20161212

//��¼�ӹ���Ϣ
		InfoRecordInProc(nHead);

//����������б�����ѡ��ӹ��굱ǰ��ʱ�������ӹ�
		if(GetDoc().GetFaultRun())
			return false;

//��ȡ��׼ȷ�ļӹ���ʱ
		if(m_panelProcessTime==0)
		{
			if(cycleno==cycle)
				procTime1=GetDoc().GetProcTime();
			
			if(cycleno==(cycle+1))
			{
				procTime2=GetDoc().GetProcTime();
				
				if(labs(procTime1-procTime2)<10)						//�������β�õļӹ���ʱ����С��10sʱ��ȡƽ��ֵΪ���յļӹ���ʱ
					m_panelProcessTime=(procTime1+procTime2)/2;
				else													//��������ȡֵ
					cycle+=2;
			}
		}

#ifndef MACHINEHOTTEST
//���ӹ���ʱ�϶�ʱ�������ӹ���ɺ�ִ������׼��ָ��
//		if((!m_bUnloadIsReady)&&(m_panelProcessTime<=UNLOADREADYTIME))
//		if(!m_bUnloadIsReady)
		if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC)&&(!m_bUnloadIsReady))	//20200619
		{
			if(GetDoc().GetUse9112())
			{
				ChannelOutput(OUNLOARDMOVETOTABLE,MIO_ON);				//���ϻ�е�ִ���
				Delay(500);
				ChannelOutput(OUNLOARDMOVETOTABLE,MIO_OFF);				
			}
			else
			{
				if (GetDoc().GetASideIsProcessing())	
					SetCOMOutput(2);									//���ϻ�е�ִ���  o����2������20
				else
					SetCOMOutput(20);
			}
		}
#endif

		if(!PeekRunState())
			return false;

		time(&m_StartTime);												//20161212

//��ѯ���д���״̬
//		if(GetDoc().GetFault())
//			return false;		
//		if(GetDoc().GetWarner())
//			return false;
		
//�����ӹ����񾵾���У���ͼ��⹦�ʲ���
		if(!GetDoc().GetTestMode())							//����ģʽ������У�������
		{
			if(!CalibrationInProc(headMode))
				return false;

			if(!PeekRunState())
				return FALSE;
		}

#ifndef MACHINEHOTTEST
//ƽ̨��������λ��׼������
		if(GetDoc().GetUse9112())
			MoveTo(GetDoc().GetTabUnloadPos());			
		else
		{
			if(GetDoc().GetASideIsProcessing())
				MoveTo(GetDoc().GetTabUnloadPos());
			else
				MoveTo(GetDoc().GetOverTabUnloadPos());
		}

		WaitAxisStop(AXISTAB);	

//�򿪼�ǯ
		if(!TableClampOperate(true,GetDoc().GetTableClamp()))
			return false;

//�ر���Ч������
		GetDoc().SetAxisIsRun(0,false);							//20180821
		GetDoc().SetAxisIsRun(1,false);	

//ƽ̨�ͷ����
		if(nHead==HeadBoth)											
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		}
		
		if (nHead==HeadLeft)
		{
			ChannelOutput(OTABLEVACUUMVALVERE1,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		}
		
		if (nHead==HeadRight)
		{
			ChannelOutput(OTABLEVACUUMVALVERE2,IO_ON);
			ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);	
		}

		if(!PeekRunState())
			return FALSE;
		
		Delay(1000);
//����
		if(!UnLoadPCBBoard(nHead,GetDoc().GetASideIsProcessing()))
			return false;
#endif
	}

//ѭ���ӹ����������״̬��λ
	ResetProcStatus();
	
	if(GetDoc().GetSysInfoDBMode()==1)									
	{
		if(GetDoc().GetProcedPCBNum()!=GetDoc().GetSysPCBCount())						//20180118
			AfxMessageBox("�Ѽӹ��������趨������һ�£���ȷ�ϣ�");

#ifdef USELOG
		CString strCount;																	//20160901
		strCount.Format("%d",GetDoc().GetProcedPCBNum());
		GetLog().AppendSNWorkTable(GetDoc().GetSysProcLOTID(),GetDoc().GetCurUserName(),GetDoc().GetFileName(),strCount,COleDateTime::GetCurrentTime());
#endif
		GetDoc().SetSysSNProcedPCBNum(0);
	}

	return true;
}

void DoEventAndSleep(unsigned long time)
{
	MSG s_msg;
	if(PeekMessage(&s_msg, NULL, 0, 0,PM_NOREMOVE))
	{
		if (GetMessage(&s_msg, NULL, 0, 0))
		{
			TranslateMessage(&s_msg);
			DispatchMessage(&s_msg);
		}
	}
	else
		Sleep(time);
}

BOOL CControl::TableAndGalvoTransform(int nHead,Coord crd)
{
	Coord crdDest,crdOffsetL,crdOffsetR;
	char ez[256]=_T("");
	double lSLScale=GetDoc().GetSLBitPerMM()/1000.0;
	Coord Lcenter=Coord();
	Coord Rcenter=Coord();

//	m_crdGlvMidPos=(GetDoc().GetCCDToGlvSysOffset(HeadLeft)+GetDoc().GetCCDToGlvSysOffset(HeadRight))/2;	//20190731

	if(nHead==HeadBoth)
	{
		if(!CogSetMapPoint(HeadLeft,crd,Lcenter))
			return false;

		if(!CogSetMapPoint(HeadRight,crd,Rcenter))
			return false;

//		m_crdRealOffsetL=Lcenter-crd;					//�������ĵ�ƫ����
//		m_crdRealOffsetR=Rcenter-crd;					//�������ĵ�ƫ����

//		crdDest = GetDoc().GetFileToRealRelative()-crd-m_crdGlvMidPos-(m_crdRealOffsetL+m_crdRealOffsetR)/2;
//		crdOffsetL=GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdGlvMidPos+(m_crdRealOffsetL-m_crdRealOffsetR)/2;
//		crdOffsetR=GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdGlvMidPos+(m_crdRealOffsetR-m_crdRealOffsetL)/2;

		crdDest = GetDoc().GetFileToRealRelative()-m_crdGlvMidPos-(Lcenter+Rcenter)/2;								//20181127
		crdOffsetL=GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdGlvMidPos+(Lcenter-Rcenter)/2;
		crdOffsetR=GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdGlvMidPos+(Rcenter-Lcenter)/2;

//#ifdef TRANSFORMTEST
		if(m_bUseOldScale)
		{
			crdDest = GetDoc().GetFileToRealRelative()-crd-m_crdGlvMidPos-(m_crdRealOffsetL+m_crdRealOffsetR)/2;
			
//			crdOffsetL=GetGlvProcGlvOffset(0,crd,HeadLeft);															//20200317
			crdOffsetL=GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crd,HeadLeft);
			crdOffsetL+=GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdGlvMidPos+(m_crdRealOffsetL-m_crdRealOffsetR)/2;
			
			crdOffsetR=GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crd,HeadRight);
			crdOffsetR+=GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdGlvMidPos+(m_crdRealOffsetR-m_crdRealOffsetL)/2;
		}
//#endif
	}

	if(nHead==HeadLeft)
	{
		if(!CogSetMapPoint(HeadLeft,crd,Lcenter))
			return false;

//		if(!CogSetMapPoint(HeadRight,crd,Rcenter))
//			return false;

//		m_crdRealOffsetL=Lcenter-crd;					//�������ĵ�ƫ����
//		m_crdRealOffsetR=Rcenter-crd;					//�������ĵ�ƫ����

//		crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdRealOffsetL;
		crdDest = GetDoc().GetFileToRealRelative()-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-Lcenter;
		crdOffsetL=Coord();
		crdOffsetR=Coord();

//#ifdef TRANSFORMTEST
		if(m_bUseOldScale)
		{
			crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdRealOffsetL;
			
			crdOffsetL=GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crd,HeadLeft);
			crdOffsetR=Coord();
		}
//#endif
	}

	if(nHead==HeadRight)
	{
//		if(!CogSetMapPoint(HeadLeft,crd,Lcenter))
//			return false;

		if(!CogSetMapPoint(HeadRight,crd,Rcenter))
			return false;

//		m_crdRealOffsetL=Lcenter-crd;					//�������ĵ�ƫ����
//		m_crdRealOffsetR=Rcenter-crd;					//�������ĵ�ƫ����

//		crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdRealOffsetR;
		crdDest = GetDoc().GetFileToRealRelative()-GetDoc().GetCCDToGlvSysOffset(HeadRight)-Rcenter;
		crdOffsetL=Coord();
		crdOffsetR=Coord();

//#ifdef TRANSFORMTEST
		if(m_bUseOldScale)
		{
			crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdRealOffsetR;
			
			crdOffsetL=Coord();
			crdOffsetR=GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crd,HeadRight);
		}
//#endif
	}

#ifdef CPKTEST
//	crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(nHead);
	if(nHead==HeadBoth)
		crdDest = GetDoc().GetFileToRealRelative()-m_crdGlvMidPos-crd;
	else
		crdDest = GetDoc().GetFileToRealRelative()-GetDoc().GetCCDToGlvSysOffset(nHead)-crd;

	crdOffsetL=Coord();
	crdOffsetR=Coord();
#endif

//	if (GetDoc().GetIsNullPrecessHoles())										//20200714 ɾ��
		MoveTo(crdDest);									//WaitAxisStop(AXISTAB)��������GlvSubAreaProc()��

#ifdef RTC5DLL
	GalvoCorrectionSetup(HeadLeft,m_dbScaleLY1,m_dbScaleLX1,m_dbAngleL,-crdOffsetL.y*lSLScale,crdOffsetL.x*lSLScale);
	GalvoCorrectionSetup(HeadRight,m_dbScaleRY1,m_dbScaleRX1,m_dbAngleR,-crdOffsetR.y*lSLScale,crdOffsetR.x*lSLScale);
#else
#ifdef SMCNewCorType
	GalvoCorrectionSetup(SH_Head1,m_dbScaleLY1,m_dbScaleLX1,m_dbAngleL,-crdOffsetL.y*lSLScale,crdOffsetL.x*lSLScale);
	GalvoCorrectionSetup(SH_Head2,m_dbScaleRY1,m_dbScaleRX1,m_dbAngleR,-crdOffsetR.y*lSLScale,crdOffsetR.x*lSLScale);
#else
	double angleL=m_dbAngleL*180/M_PI;
	double angleR=m_dbAngleR*180/M_PI;

	if(!SetHeadCorParam(HeadLeft,-crdOffsetL.y*lSLScale,crdOffsetL.x*lSLScale,angleL,m_dbScaleLX1,m_dbScaleLY1))
	{
		GetDoc().SetLastWarningNo(58);
		strncpy(ez,GetLang().GetWarningText(21050),256);
		AfxMessageBox(ez);									//"��У�������趨�쳣���޷������ӹ���������ӹ�!"
		return false;
	}
//	Delay(20);																	//20161216 ����	
	if(!SetHeadCorParam(HeadRight,-crdOffsetR.y*lSLScale,crdOffsetR.x*lSLScale,angleR,m_dbScaleRX1,m_dbScaleRY1))
	{
		GetDoc().SetLastWarningNo(59);
		strncpy(ez,GetLang().GetWarningText(21050),256);
		AfxMessageBox(ez);									//"��У�������趨�쳣���޷������ӹ���������ӹ�!"
		return false;
	}
#endif
#endif

	return true;
}
/*
Coord CControl::GetGlvProcGlvOffset(int type,Coord crd,int nHead)
{
	ASSERT(nHead == HeadLeft || nHead==HeadRight );

	Coord center=Coord();
	Coord crdTmp,crd1=Coord();

	switch(type)
	{
	case 0:
		center=GetExcellonData().GetLayerCenter();
		break;
	case 1:
		center=GetExcellonData().GetInnerLayerCenter();
		break;
	default:
		center=GetExcellonData().GetLayerCenter();
		break;
	}

	if(nHead == HeadLeft)
	{
		crd1 = calc::ToRotate(center,m_dbAngleL,crd);

		crdTmp = crd1-center;
		crd1.x += crdTmp.x*(m_dbScaleLX1-1);
		crd1.y += crdTmp.y*(m_dbScaleLY1-1);

		crd1 -= crd;
	}

	if(nHead == HeadRight)
	{
		crd1 = calc::ToRotate(center,m_dbAngleR,crd);

		crdTmp = crd1-center;
		crd1.x += crdTmp.x*(m_dbScaleRX1-1);
		crd1.y += crdTmp.y*(m_dbScaleRY1-1);

		crd1 -= crd;
	}

	return crd1;
}
*/
Coord CControl::GetGlvProcGlvOffset(int type,Coord crd,int nHead)		//20191219 �޸�
{
	ASSERT(nHead == HeadLeft || nHead==HeadRight );

	Coord center=Coord();
	Coord crd1=Coord();
	Coord crd2=Coord();
	Coord crdOffset=Coord();

	switch(type)
	{
	case 0:
		center=GetExcellonData().GetLayerCenter();
		break;
	case 1:
		center=GetExcellonData().GetInnerLayerCenter();
		break;
	default:
		center=GetExcellonData().GetLayerCenter();
		break;
	}

	if(nHead == HeadLeft)
	{
		crd1.x=(crd.x-center.x)*m_dbScaleLX1;
		crd1.y=(crd.y-center.y)*m_dbScaleLY1;
		crd2=calc::ToRotate(center,m_dbAngleL,(crd1+center));
		crdOffset=crd2-crd;
	}

	if(nHead == HeadRight)
	{
		crd1.x=(crd.x-center.x)*m_dbScaleRX1;
		crd1.y=(crd.y-center.y)*m_dbScaleRY1;
		crd2=calc::ToRotate(center,m_dbAngleR,(crd1+center));
		crdOffset=crd2-crd;
	}

	return crdOffset;
}

int CControl::PanelProcessNew(int nHead,int proccount,int Aptno[20],int subproccount,int SubAptno[20])
{
//ȡ�������������

//�����ڱ�з��������ֲ������n����6/8�ڱ����2������׼��ʽ��1����ȷ�������ѭ������
//�ڴ�ѭ���жԷ����н��мӹ���ʶ����ʶ��õ��ı���������XY���űȡ���ת�ǶȺ�XYλ������5��������������ֻ�ԡ����������ռӹ���ʽ���������ܿ��жϣ������м�¼����Ӧ�Ĵ���
//��������ѭ��ģʽ�����м��ѭ��������1�λ���2�Σ�
//����ɵ��������������ڲ�ѭ��������ȡ���ڵ����趨���ж����ֹ�Ȧ�ţ�

//������ѭ����Ƕ�н��з���ѭ���ӹ�
//��ѭ����Ƕ������ַ��ӹ�

	char ez[256]={""};

	int fileMode=GetDoc().GetFileMode();								//���ռӹ���ʽ
	int groupCount=1;													//�����ڱ�з�����
	int timeStart=0;													//�ڱ�з���ѭ��ʱ����ʼѭ��ֵ,-1ֵѭ��ʱ�ӹ���M02��
	int order[2]={0,1};

	TARGETMODE tm;
	HoleCoordV innerMarkCrdV;

	SubArea subarea;
//	Coord crd=Coord(),crdDest=Coord();
	Coord crd=Coord();
	int ToolNo,SubToolIndex;
	long hole,holenum;

	int rowCount0=0;
	int subAreaCount0=0;

//	m_crdGlvMidPos.x=(GetDoc().GetCCDToGlvSysOffset(HeadLeft).x+GetDoc().GetCCDToGlvSysOffset(HeadRight).x)/2;
//	m_crdGlvMidPos.y=(GetDoc().GetCCDToGlvSysOffset(HeadLeft).y+GetDoc().GetCCDToGlvSysOffset(HeadRight).y)/2;

	switch(fileMode)
	{
	case 0:							//�����������ռӹ���ʽ֧���������з�ʽ���ڲ�����з�ʽ�����ڲ�����з�ʽ�ַ�Ϊ������4�ڲ�����к�˫����6/8�ڲ�����з�ʽ
		tm=OUTER;
		groupCount=1;				//�ڵ�����4�ڲ�����з�ʽ�£�������Ϊ1
//		timeStart=0;
		if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
		{
			tm=INNER;
			if(GetDoc().GetIsDoubleFileData())							
			{
				groupCount=2;		//��˫����6/8�ڲ�����з�ʽ�£�������Ϊ2	
				if(GetDoc().GetExcellonData0IsUp())
				{
					order[0]=1;
					order[1]=0;
				}
			}
		}
		break;
	case 1:																//��6��С����ռӹ���ʽ��֧���������з�ʽ
		tm=INNER;
		groupCount=2;
//		timeStart=0;
		break;
	case 2:																//��M02�ڲ���С����ռӹ���ʽ��֧���������з�ʽ
		tm=STDLOCAL;
		groupCount=GetExcellonData().GetLocalMarkDataCount();
		timeStart=-1;				//-1ֵѭ��ʱ�ӹ���M02��
		break;
	case 3:																//�������ڲ���С����ռӹ���ʽ��֧���������з�ʽ
		tm=SALOCAL;
		groupCount=GetExcellonData().GetSALocalMarkDataCount();
//		timeStart=0;
		break;
	default:
		AfxMessageBox("���ռӹ���ʽ�趨����!");
		return -1;
	}

	int toolcyclecount=1;												//�����м��ѭ��������ȱʡʱ������ѭ����ֵΪ1

	if(GetDoc().GetToolCycleMode())
		toolcyclecount=2;												//����ѭ���ӹ���ʽʱ��������ѭ����ֵΪ2

	ChannelOutput(OTHETALENSPROTECT,MIO_ON);							//ɨ�辵�������ϴ�

	for(int times=timeStart;times<groupCount;times++)	//�����ڱ�з��������е���
	{
		if(fileMode==SystemDoc::NORMALPROC)				//�ڡ����������ռӹ���ʽ�²�����Ҫ����˫�����л�
		{
			SetGlobalExcellonIndex(order[times]);						//˫�����л�
			
			if(times==0)
			{
				rowCount0=GetExcellonData().GetSubAreaCol();
				subAreaCount0=GetExcellonData().GetSubAreaCnt();
			}
		}

		long nSubareaStartIndex=0;
		long nSubareaEndIndex=0;

		innerMarkCrdV.clear();

		switch(fileMode)
		{
		case 0:															//�����������ռӹ���ʽ
			if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
				innerMarkCrdV=GetExcellonData().GetInnerFiducial();
			nSubareaStartIndex=0;
			nSubareaEndIndex=GetExcellonData().GetSubAreaCnt();
			break;
		case 1:															//��6��С����ռӹ���ʽ��������Ϊ2
			innerMarkCrdV=GetProcFiducialForSix(times);
			if(times==0)
			{
				nSubareaStartIndex=0;
				nSubareaEndIndex=GetExcellonData().GetSubAreaCnt()/2;
			}
			else if(times==1)
			{
				nSubareaStartIndex=GetExcellonData().GetSubAreaCnt()/2;
				nSubareaEndIndex=GetExcellonData().GetSubAreaCnt();
			}
			break;
		case 2:															//��M02�ڲ���С����ռӹ���ʽ
			innerMarkCrdV=GetExcellonData().GetLocalMark(times);
			nSubareaStartIndex=0;
			if(times==-1)												//-1ֵѭ��ʱ�ӹ���M02��
				nSubareaEndIndex=GetExcellonData().GetOtherSubAreaCnt();			
			else
				nSubareaEndIndex=GetExcellonData().GetLocalMarkSubAreaCnt(times);
			break;
		case 3:															//�������ڲ���С����ռӹ���ʽ
			innerMarkCrdV=GetExcellonData().GetSALocalMark(times);
			nSubareaStartIndex=GetExcellonData().GetSALocalMarkProcStartIndex(times);		
			if(times<groupCount-1)
				nSubareaEndIndex=GetExcellonData().GetSALocalMarkProcStartIndex(times+1);			
			else
				nSubareaEndIndex=GetExcellonData().GetSubAreaCnt();
			break;
		default:
			AfxMessageBox("�ļ�ģʽ�趨����!");
			return -1;
		}

//�ڲ㣨���ڲ���Ŀ��ʶ����ش���
		if(!((tm==OUTER)||(groupCount==1)))					//�����������ռӹ���ʽ���������з�ʽ�͵�����4�ڲ�����з�ʽʱ������ʶ�����
		{
			if(!((fileMode==SystemDoc::LOCALMARKM02)&&(times==-1)))	//�ڡ�M02�ڲ���С����ռӹ���ʽ�µĵ�һ��ѭ��������ʶ���������ѭ�����ڼӹ���M02��
			{
				int rtn=TargetDealInProc(nHead,innerMarkCrdV.size(),innerMarkCrdV,tm);

				if(rtn!=0)
					return -1;

				if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC)&&(!GetDoc().GetASideIsProcessing()))
				{
					if(nHead==HeadBoth)						//˫��ģʽ�£�����B���Զ�������ʱ�޷���NG�壬����κ�һ�����Ŀ��ʶ��ʧ��ʱ���˳��ӹ�����		
					{
						if(!(m_bEnableProcPCB1&&m_bEnableProcPCB2))
						{
							AfxMessageBox("B��ӹ�ʱ�ڲ����ʶ��ʧ�ܣ����˳��ӹ�����ȷ�ϣ�");
							return -1;
						}
					}
				}
			}
		}

//		if (!GetDoc().GetIsNullPrecessHoles())									//20200714 ����
//			continue;

/////////////////////////////////////////////////////////////////////////////////20160901
//���Զ�����ֵ����ר�ŵĴ洢����������ӹ���ɺ�ļӹ���Ϣ��¼
		if((fileMode==SystemDoc::NORMALPROC)||(fileMode==SystemDoc::INNERMARK))
		{
//			m_dbScaleLX[times]=(m_dbScaleLX1+m_dbScaleLX2)/2.0;
//			m_dbScaleLY[times]=(m_dbScaleLY1+m_dbScaleLY2)/2.0;
//			m_dbScaleRX[times]=(m_dbScaleRX1+m_dbScaleRX2)/2.0;
//			m_dbScaleRY[times]=(m_dbScaleRY1+m_dbScaleRY2)/2.0;

			m_dbScaleLX[times]=m_dbAutoScaleLX;							//20180905
			m_dbScaleLY[times]=m_dbAutoScaleLY;
			m_dbScaleRX[times]=m_dbAutoScaleRX;
			m_dbScaleRY[times]=m_dbAutoScaleRY;
		}

		if (!GetDoc().GetIsNullPrecessHoles())									//20200714 ����
			continue;

#ifdef USELOG
		if((GetDoc().GetSysInfoDBMode()==1))
		{
			if((m_bEnableProcPCB1!=m_bLeftAxisStatus)||(m_bEnableProcPCB2!=m_bRightAxisStatus))
			{
				CString leftStatus="��";
				CString rightStatus="��";

				if(m_bEnableProcPCB1)
					leftStatus="��";
				if(m_bEnableProcPCB2)
					rightStatus="��";

				GetLog().AppendSNAxisStatusTable(leftStatus,rightStatus,COleDateTime::GetCurrentTime());

				m_bLeftAxisStatus=m_bEnableProcPCB1;
				m_bRightAxisStatus=m_bEnableProcPCB2;
			}			
		}
#endif

//Z���ƶ������λ��
#ifndef MACHINEHOTTEST
		if(m_bEnableProcPCB1)
		{ 
			if(GetDoc().GetTechnicType())
				MoveTo(AXISLEFTZ,GetDoc().GetLongPathLaserProcFocus(0)-GetDoc().GetPCBThickness());
			else
				MoveTo(AXISLEFTZ,GetDoc().GetLaserProcFocus(0)-GetDoc().GetPCBThickness());
//			LeftPareSt = true;
		}
		
		if(m_bEnableProcPCB2)
		{ 
			if(GetDoc().GetTechnicType())
				MoveTo(AXISRIGHTZ,GetDoc().GetLongPathLaserProcFocus(1)-GetDoc().GetPCBThickness());
			else
				MoveTo(AXISRIGHTZ,GetDoc().GetLaserProcFocus(1)-GetDoc().GetPCBThickness());
//			RightPareSt = true;
		}
#else
		if(m_bEnableProcPCB1)
				MoveTo(AXISLEFTZ,45000);
		
		if(m_bEnableProcPCB2)
				MoveTo(AXISRIGHTZ,45000);
#endif

		WaitAxisStop(AXISLEFTZ);
		WaitAxisStop(AXISRIGHTZ);

#ifdef CPKTEST
		InitalTransform();
#endif

#ifdef SMCNewCorType
		double angleL=m_dbAngleL*180/M_PI;
		double angleR=m_dbAngleR*180/M_PI;
		
		if(!SetHeadCorParam(HeadLeft,0,0,angleL,m_dbScaleLX1,m_dbScaleLY1))
		{
			GetDoc().SetLastWarningNo(58);
			strncpy(ez,GetLang().GetWarningText(21050),256);
			AfxMessageBox(ez);									//"��У�������趨�쳣���޷������ӹ���������ӹ�!"
			return -1;
		}
//		Delay(20);																	//20161216 ����	
		if(!SetHeadCorParam(HeadRight,0,0,angleR,m_dbScaleRX1,m_dbScaleRY1))
		{
			GetDoc().SetLastWarningNo(59);
			strncpy(ez,GetLang().GetWarningText(21050),256);
			AfxMessageBox(ez);									//"��У�������趨�쳣���޷������ӹ���������ӹ�!"
			return -1;
		}
#endif

//���мӹ�
		for(int toolcycle=0;toolcycle<toolcyclecount;toolcycle++)		//��������ѭ�������е���
		{
			BOOL bToolCycleMode=FALSE;
			int count=proccount;
			
			if(GetDoc().GetToolCycleMode()&&toolcycle==1)
			{
				bToolCycleMode=TRUE;
				count=subproccount;
			}
			
			for(int proccycle=0;proccycle<count;proccycle++)			//���յ����������е���
			{
				if(GetDoc().GetToolCycleMode()&&toolcycle==1)
				{
					if(SubAptno[proccycle]==0)
						continue;
				}
		
				if(fileMode==SystemDoc::NORMALPROC)						//�ڡ����������ռӹ���ʽ�²���ָ���ӹ�����
				{
					if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)
					{
						GetRunView().ResetSelectBlankColor();			//�ӹ�������ʾ���ã�ָ���ӹ���������ӹ���ÿ������ѭ������һ��

//						if(proccycle==0)								//20180412
						if(m_bSAProcMode||(proccycle==0))				//20190912
						{
							if(!GetDoc().GetIsDoubleFileData())							
							{
								nSubareaEndIndex=GetRunView().GetSelectBlockNum();
							}
							else
							{
								int nSubAreaCount=0;
								
								for(int ii=0;ii<GetRunView().GetSelectBlockNum();ii++)
								{
									if(times==0)
									{
										if(GetRunView().GetSelectBlockIndex(ii)<GetDoc().GetDisplayColCount()*rowCount0)
											nSubAreaCount++;
									}
									else
									{
										if((GetRunView().GetSelectBlockIndex(ii)>=GetDoc().GetDisplayColCount()*rowCount0)
											&&(GetRunView().GetSelectBlockIndex(ii)<(GetDoc().GetDisplayColCount()*GetDoc().GetDisplayRowCount())))
											nSubAreaCount++;
									}	
								}
								
								nSubareaEndIndex=nSubAreaCount;
							}
						}
						else
							nSubareaEndIndex=GetExcellonData().GetSubAreaCnt();
					}
					else
						GetRunView().ResetBlankColor();
				}
				else
					GetRunView().ResetBlankColor();

#ifdef SMCDMDLL
				SetHeadCorParam(0,0,0,0,1.0,1.0);
				SetHeadCorParam(1,0,0,0,1.0,1.0);
				XYDataV xyVL,xyVR;
#endif

//���շ����������е���				
				for(long n=nSubareaStartIndex; n<nSubareaEndIndex;n++)	
				{
#ifdef SMCDMDLL
					xyVL.clear();
					xyVR.clear();
#endif
					if(fileMode==SystemDoc::NORMALPROC)					//�ڡ����������ռӹ���ʽ�²���ָ���ӹ�����
					{
						if(GetDoc().GetProcessState()==SystemDoc::SELEPROC)		//�ӹ�������ʾˢ�£�ָ���ӹ���������ӹ���ÿ�������ӹ�ѭ��ˢ��һ��
						{
							if(!GetDoc().GetIsDoubleFileData())							
							{						
//								m_lCurDrillSubAreaNo=GetRunView().GetSelectBlockIndex(n);							
//								GetRunView().SetBlankColor(BLANKED_BLOCKS_COLOR,m_lCurDrillSubAreaNo);
//---------------------------------------------------------------------------------------------------------20161109
//								if(proccycle==0)																			//20180412
								if(m_bSAProcMode||(proccycle==0))															//20190912
								{
									int nIndexCount=-1;
									
									for(int jjj=0;jjj<GetRunView().GetSelectBlockNum();jjj++)
									{							
										nIndexCount++;
										GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex(jjj));	//�����кż������ʾ�������ţ���������ɫ
										
										if(nIndexCount==n)
										{
											m_lCurDrillSubAreaNo=GetRunView().GetSelectBlockIndex(jjj);						//�����кż����S�ͼӹ������ţ������мӹ�
											break;
										}							
									}
								}
								else
								{
									GetRunView().SetBlankColor(BLANKED_BLOCKS_COLOR,m_lCurDrillSubAreaNo);	
									m_lCurDrillSubAreaNo=n;
								}
							}
							else
							{
								int iSubAreaCount=-1;
								
								if(times==0)
								{
									for(int iii=0;iii<GetRunView().GetSelectBlockNum();iii++)
									{						
										if(GetRunView().GetSelectBlockIndex(iii)<GetDoc().GetDisplayColCount()*rowCount0)	//�����кż����S�ͼӹ������ţ������ܷ������Ƚ�
										{
											iSubAreaCount++;
											GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex(iii));
											
											if(iSubAreaCount==n)
											{
												m_lCurDrillSubAreaNo=GetRunView().GetSelectBlockIndex(iii);
												break;
											}
										}
									}
								}
								else
								{
									for(int n1=0;n1<GetRunView().GetSelectBlockNum();n1++)
									{
										if(GetRunView().GetSelectBlockIndex(n1)<GetDoc().GetDisplayColCount()*rowCount0)	//�����кż����S�ͼӹ������ţ������ܷ������Ƚ�
											GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex(n1));
									}
									
									for(int n2=0;n2<GetRunView().GetSelectBlockNum();n2++)
									{
										if((GetRunView().GetSelectBlockIndex(n2)>=GetDoc().GetDisplayColCount()*rowCount0)	//�����кż����S�ͼӹ������ţ������ܷ������Ƚ�
											&&(GetRunView().GetSelectBlockIndex(n2)<(GetDoc().GetDisplayColCount()*GetDoc().GetDisplayRowCount())))
										{
											iSubAreaCount++;
											GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex(n2));
											
											if(iSubAreaCount==n)
											{
//												m_lCurDrillSubAreaNo=GetRunView().GetSelectBlockIndex(n2)-GetDoc().GetDisplayColCount()*rowCount0;//???
												if(rowCount0%2==0)
													m_lCurDrillSubAreaNo=GetRunView().GetSelectBlockIndex(n2)-GetDoc().GetDisplayColCount()*rowCount0;
												else
													m_lCurDrillSubAreaNo=GetRunView().GetSelectBlockIndex(n2,false)-GetDoc().GetDisplayColCount()*rowCount0;
												break;
											}
										}
									}
								}												
							}
//--------------------------------------------------------------------------------------------------------------
						}
						else											//����ӹ�
						{
							m_lCurDrillSubAreaNo=n;						//�趨�ӹ�������
							
							if(!GetDoc().GetIsDoubleFileData())													
								GetRunView().SetBlankColor(BLANKED_BLOCKS_COLOR,m_lCurDrillSubAreaNo);	
							else//------------------------------------------------------------------------20161109
							{							
								if(times==0)
								{
									for(int ii=0;ii<=m_lCurDrillSubAreaNo;ii++)
									{							
										GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex(ii,false));									
									}
								}
								else
								{
									for(int m1=0;m1<subAreaCount0;m1++)
									{							
										GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex(m1,false));									
									}
									
									for(int m2=0;m2<=m_lCurDrillSubAreaNo;m2++)
									{
										if(rowCount0%2==0)
											GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex((m2+GetDoc().GetDisplayColCount()*rowCount0),false,true));
										else
											GetRunView().SetBlockColor(BLANKED_BLOCKS_COLOR,GetRunView().GetBlockIndex((m2+GetDoc().GetDisplayColCount()*rowCount0),false,false));
									}
								}							
							}
//-------------------------------------------------------------------------------------------------------------------------
						}
					}
					else
					{
						m_lCurDrillSubAreaNo=n;
						GetRunView().SetBlankColor(BLANKED_BLOCKS_COLOR,m_lCurDrillSubAreaNo);
					}

					if(fileMode==SystemDoc::LOCALMARKM02)						//��M02�ڲ���С����ռӹ���ʽ
					{
						if(times==-1)
							subarea=GetExcellonData().GetOtherSubAreaData(m_lCurDrillSubAreaNo);
						else
							subarea=GetExcellonData().GetLocalMarkSubAreaData(times,m_lCurDrillSubAreaNo);
					}
					else
						subarea=GetExcellonData().GetSubAreaData(m_lCurDrillSubAreaNo);
//���������ӹ�
					if(!subarea.hcvHoleData.empty())
					{
						holenum=0;	
						crd=subarea.crdCenter;
						
						for(int tc=0;tc<GetDoc().GetToolsCnt();tc++)				//��ȡ��Ӧ���ߵļӹ�����
						{
							if(GetDoc().GetToolCycleMode()&&bToolCycleMode)
							{
								if(SubAptno[proccycle]==GetDoc().GetToolSubApertureNo(tc))
//								if(SubAptno[proccycle]==GetDoc().GetToolSubShowApertureNo(tc)) 
								{
									ToolNo = GetDoc().GetToolNo(tc);
									SubToolIndex = subarea.GetSameToolIndex(ToolNo);

									if(SubToolIndex!=-1)
									{
										hole = subarea.hcvHoleData[SubToolIndex].hcvHolePos.size();
										holenum+=hole;
									}

//									GetRunView().SetBlankColor(BLANKED_BLOCKS_COLOR,m_lCurDrillSubAreaNo);
								}
							}
							else
							{
								if(Aptno[proccycle]==GetDoc().GetToolApertureNo(tc))
//								if(Aptno[proccycle]==GetDoc().GetToolShowApertureNo(tc))
								{
									ToolNo = GetDoc().GetToolNo(tc);
									SubToolIndex = subarea.GetSameToolIndex(ToolNo);

									if(SubToolIndex!=-1)
									{
										hole = subarea.hcvHoleData[SubToolIndex].hcvHolePos.size();
										holenum+=hole;
									}

//									if(bToolCycleMode)
//										GetRunView().SetBlankColor(BLANKED_BLOCKS_DIRLLCOLOR,m_lCurDrillSubAreaNo);
//									else
//										GetRunView().SetBlankColor(BLANKED_BLOCKS_COLOR,m_lCurDrillSubAreaNo);
								}
								
							}
						}
						
						if(holenum>0)
						{
							if(m_bEnableProcPCB1&&m_bEnableProcPCB2)		//��ȫ�ֱ���������ӹ��������
							{
#ifdef SMCDMDLL
								if(!TableAndGalvoTransformNew(HeadBoth,subarea,xyVL,xyVR,Aptno[proccycle]))
									return -1;
#else
								if(!TableAndGalvoTransform(HeadBoth,crd))
									return -1;
#endif
							}
							else if(m_bEnableProcPCB1)
							{
#ifdef ONEAXISDATATRANSFORMTEST
#ifdef ONEAXISDATATRANSFORMANDPROC
								if(!OneAxisSubAreaDataTransform(HeadLeft,subarea,Aptno[proccycle]))
									return -1;

								if(!OneAxisTableAndGalvoTransform(HeadLeft,crd))
									return -1;
#endif
#ifdef ONEAXISDATATRANSFORMANDFIND
								if(!OneAxisSubAreaDataTransformAndFind(HeadLeft,subarea,Aptno[proccycle]))
									return -1;
								else
									continue;
#endif
#ifdef ONEAXISDATATRANSFORMANDDRILL
								if(!OneAxisSubAreaDataTransformAndDrill(HeadLeft,subarea,Aptno[proccycle]))
									return -1;
								else
									continue;
#endif
#else
#ifdef SMCDMDLL
								if(!TableAndGalvoTransformNew(HeadLeft,subarea,xyVL,xyVR,Aptno[proccycle]))
									return -1;
#else
								if(!TableAndGalvoTransform(HeadLeft,crd))
									return -1;
#endif
#endif
							}
							else if(m_bEnableProcPCB2)
							{
#ifdef ONEAXISDATATRANSFORMTEST
#ifdef ONEAXISDATATRANSFORMANDPROC
								if(!OneAxisSubAreaDataTransform(HeadRight,subarea,Aptno[proccycle]))
									return -1;

								if(!OneAxisTableAndGalvoTransform(HeadRight,crd))
									return -1;
#endif
#ifdef ONEAXISDATATRANSFORMANDFIND
								if(!OneAxisSubAreaDataTransformAndFind(HeadRight,subarea,Aptno[proccycle]))
									return -1;
								else
									continue;
#endif
#ifdef ONEAXISDATATRANSFORMANDDRILL
								if(!OneAxisSubAreaDataTransformAndDrill(HeadRight,subarea,Aptno[proccycle]))
									return -1;
								else
									continue;
#endif
#else
#ifdef SMCDMDLL
								if(!TableAndGalvoTransformNew(HeadRight,subarea,xyVL,xyVR,Aptno[proccycle]))
									return -1;
#else
								if(!TableAndGalvoTransform(HeadRight,crd))
									return -1;
#endif
#endif
							}
#ifdef LASERMONITOR
                            GetDoc().ReadLaserConfig();							//��ѯ���������״̬
#endif
//ȡ�����������ع���
//��ʼ�����ӹ�
							if(GetDoc().GetToolCycleMode())
							{
								if(bToolCycleMode)
								{
									if(!GlvSubAreaProc(subarea,SubAptno[proccycle],true))
										return -1;
								}
								else
								{
									if(!GlvSubAreaProc(subarea,Aptno[proccycle],false))
										return -1;
								}
							}
							else
							{
#ifdef SMCDMDLL
								if(!GlvSubAreaProcNew(subarea,xyVL,xyVR,Aptno[proccycle]))
									return -1;
#else
								if(!GlvSubAreaProc(subarea,Aptno[proccycle]))
									return -1;
#endif
							}
//ȡ�����������ع���

//�ӹ���һ���������ж��Ƿ���Ҫ����׼����������׼��
							if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC)&&(!GetDoc().GetFaultRun()))	//����������б�����ѡ��ӹ��굱ǰ��ʱ�������Ͻ�ֹ׼������
							{
#ifndef MACHINEHOTTEST
								time_t nowTime;
								long leftTime=0;

//								if((!m_bLoadIsReady)&&(m_panelProcessTime>LOADREADYTIME))		//20190222
								if((!m_bLoadIsReady)&&(m_panelProcessTime>GetDoc().GetLoadOptimize()))
								{	
									time(&nowTime);
									leftTime=m_panelProcessTime-difftime(nowTime,m_StartTime);	//������ʶ��ʱ���˹����Բ���������ӹ�ʱ��NG��������֮ǰ����ͣʱ����ֵ����Ϊ��ֵ

//									if(leftTime<=LOADREADYTIME)									//20190222
									if(leftTime<=GetDoc().GetLoadOptimize())
									{
										m_bLoadIsReady=true;
										
										if(!GetDoc().GetASideIsProcessing())
											SetCOMOutput(17);									//����ѭ��	//20190528
										
										if(GetDoc().GetUse9112())
										{
											ChannelOutput(OAOTUBIGN,MIO_ON);					//��ʼ���У��������ϣ�		
											Delay(500);
											ChannelOutput(OAOTUBIGN,MIO_OFF);
										}
										else
											SetCOMOutput(3);									//��ʼ���У��������ϣ� o����3��	o����3
									}
								}
								
								if((!m_bUnloadIsReady)&&(m_panelProcessTime>UNLOADREADYTIME))	//20200715 �Ļ�
								{
									time(&nowTime);
									leftTime=m_panelProcessTime-difftime(nowTime,m_StartTime);	//������ʶ��ʱ���˹����Բ���������ӹ�ʱ��NG��������֮ǰ����ͣʱ����ֵ����Ϊ��ֵ
									
									if(leftTime<=UNLOADREADYTIME)
									{
										m_bUnloadIsReady=true;
										
										if(GetDoc().GetUse9112())
										{
											ChannelOutput(OUNLOARDMOVETOTABLE,MIO_ON);			//���ϻ�е�ִ���
											Delay(500);
											ChannelOutput(OUNLOARDMOVETOTABLE,MIO_OFF);				
										}
										else
										{
											if (GetDoc().GetASideIsProcessing())	
												SetCOMOutput(2);								//���ϻ�е�ִ���  o����2������20
											else
												SetCOMOutput(20);
										}
									}
								}
/*																						//20200730 ȡ��
						if(n==nSubareaEndIndex-1)										//20200715 ����
						{
							if(!m_bLoadIsReady)
							{
								m_bLoadIsReady=true;
								
								if(!GetDoc().GetASideIsProcessing())
									SetCOMOutput(17);									//����ѭ��
								
								if(GetDoc().GetUse9112())
								{
									ChannelOutput(OAOTUBIGN,MIO_ON);					//��ʼ���У��������ϣ�		
									Delay(500);
									ChannelOutput(OAOTUBIGN,MIO_OFF);
								}
								else
									SetCOMOutput(3);									//��ʼ���У��������ϣ� o����3��	o����3
							}
							
							if(!m_bUnloadIsReady)
							{
								m_bUnloadIsReady=true;
								
								if(GetDoc().GetUse9112())
								{
									ChannelOutput(OUNLOARDMOVETOTABLE,MIO_ON);			//���ϻ�е�ִ���
									Delay(500);
									ChannelOutput(OUNLOARDMOVETOTABLE,MIO_OFF);				
								}
								else
								{
									if (GetDoc().GetASideIsProcessing())	
										SetCOMOutput(2);								//���ϻ�е�ִ���  o����2������20
									else
										SetCOMOutput(20);
								}
							}
						}
*/
#endif
							}
						}																//20200730 �޸�
					}
				}
			}
		}
	}

//�ӹ��ַ�
	if (GetDoc().GetIsNullPrecessHoles())
	{		
		if(!DrillText())
		{
			strncpy(ez,GetLang().GetWarningText(21056),256);
			AfxMessageBox(ez);										//"�ַ��ӹ������쳣���޷������ӹ���������ӹ�!"
			return -1;
		}	
	}

	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);

	return 0;
}

void CControl::InfoRecordInProc(int nHead)
{
//��¼�Ѽӹ���������������ƽ��ֵ
	if(m_bEnableProcPCB1)
	{
		if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC)&&(GetDoc().GetSysInfoDBMode()==1))		//20160901
		{
			UINT ulCountL=GetDoc().GetSysSNProcedPCBNum();
			ulCountL++;
			GetDoc().SetSysSNProcedPCBNum(ulCountL);
		}

		m_uProcedPCBNum = GetDoc().GetProcedPCBNum();

//#ifdef CHONGDA
		if(GetDoc().GetCustomerSpecial()==1)
		{
			if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
				m_uProcedPCBNum++;
		}
//#else
		else
			m_uProcedPCBNum++;
//#endif
		GetDoc().SetProcedPCBNum(m_uProcedPCBNum);

		double lscalex = GetDoc().GetLAvgScaleX();
		double lscaley = GetDoc().GetLAvgScaleY();	
		long lnum=GetDoc().GetLNum();

//		lscalex = (lnum*lscalex+(m_dbScaleLX1+m_dbScaleLX2)/2.0)/(lnum+1);
//		lscaley = (lnum*lscaley+(m_dbScaleLY1+m_dbScaleLY2)/2.0)/(lnum+1);

		lscalex = (lnum*lscalex+m_dbAutoScaleLX)/(lnum+1);					//20191219 �޸�
		lscaley = (lnum*lscaley+m_dbAutoScaleLY)/(lnum+1);

		lnum++;

		GetDoc().SetLAvgScaleX(lscalex);
		GetDoc().SetLAvgScaleY(lscaley);
		GetDoc().SetLNum(lnum);
	}

	if(m_bEnableProcPCB2)
	{
		if((GetDoc().GetProcessState()==SystemDoc::AUTOPROC)&&(GetDoc().GetSysInfoDBMode()==1))		//20160901
		{
			UINT ulCountR=GetDoc().GetSysSNProcedPCBNum();
			ulCountR++;
			GetDoc().SetSysSNProcedPCBNum(ulCountR);
		}

		m_uProcedPCBNum = GetDoc().GetProcedPCBNum();

//#ifdef CHONGDA
		if(GetDoc().GetCustomerSpecial()==1)
		{
			if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
				m_uProcedPCBNum++;
		}
//#else
		else
			m_uProcedPCBNum++;
//#endif
		GetDoc().SetProcedPCBNum(m_uProcedPCBNum);

		double rscalex = GetDoc().GetRAvgScaleX();
		double rscaley = GetDoc().GetRAvgScaleY();
		long rnum=GetDoc().GetRNum();

//		rscalex = (rnum*rscalex+(m_dbScaleRX1+m_dbScaleRX2)/2.0)/(rnum+1);
//		rscaley = (rnum*rscaley+(m_dbScaleRY1+m_dbScaleRY2)/2.0)/(rnum+1);

		rscalex = (rnum*rscalex+m_dbAutoScaleRX)/(rnum+1);					//20191219 �޸�
		rscaley = (rnum*rscaley+m_dbAutoScaleRY)/(rnum+1);

		rnum++;

		GetDoc().SetRAvgScaleX(rscalex);
		GetDoc().SetRAvgScaleY(rscaley);
		GetDoc().SetRNum(rnum);
	}

	CString strinfo,strName; 
	char timebuf[128],daybuf[128];       		
	tzset();
	_strtime(timebuf);
	_strdate(daybuf);

//��¼�Ѽӹ�����
	strinfo = GetDoc().GetAppPath()+"info\\holes.txt";					//info\holes.txt	
	GetInfo().SaveToFile(strinfo,"%s, %s, %d\n",daybuf,timebuf,GetDoc().GetHolesSum());

//����ˢ����ʾ
	SendMessage(GetMainFrame().m_Framework.Get(37)->GetWnd()->m_hWnd,WM_DISPDRILLINFO,0,0);	
	
//��¼�ӹ���Ϣ
	CString strAxis;
	double  dbScaleX=0.0, dbScaleY=0.0;
	BOOL bRecord=false;

	strinfo = GetDoc().GetAppPath()+INFODIR;							//info\info.txt
	strName = GetDoc().GetFileName();

	CString stra =strName.Mid(strName.ReverseFind('\\')+1);				//�ӹ������ļ���.��չ��
	CString strb =stra.Left(stra.ReverseFind('.'));						//�ӹ������ļ���
	if(GetDoc().GetSysProcLOTID()!="")									//20181212
		strb=strb+"("+GetDoc().GetSysProcLOTID()+")";

	CString strrp=ReadPowerPara((LPCTSTR)GetDoc().GetToolFileName());	//�ַ�����ʽ��ʾ�ļӹ���������	
	
	if(m_MatchMode == AUTOMATCH)		//�Զ�Ѱ��ʱ�Ż��¼�ӹ���Ϣ
	{
		CString Lotidfix = GetDoc().GetLOTIDFix();
		CString temp="";
		CString saveData=""; 
		CString strIncreasing="";
		int count0=0;
		CString info="";

//		char timebuf[128],daybuf[128];       	
//		_tzset();
//		_strtime(timebuf);
//		_strdate(daybuf);

//�ӹ���ģʽ�趨
		int start=0;
		int end=2;
/*		
		if(nHead==HeadLeft)
		{
			start=0;
			end=1;
		}
		
		if(nHead==HeadRight)
		{
			start=1;
			end=2;
		}
*/
		if(m_bEnableProcPCB1&&m_bEnableProcPCB2)							//��ȫ�ֱ���������ӹ��������
		{
			start=0;
			end=2;
		}
		else if(m_bEnableProcPCB1)
		{
			start=0;
			end=1;
		}
		else if(m_bEnableProcPCB2)
		{
			start=1;
			end=2;
		}

		int recordTimes=1;
		if((GetDoc().GetFileMode()==SystemDoc::INNERMARK)||GetDoc().GetIsDoubleFileData())
			recordTimes=2;
	
		for(int i=start;i<end;i++)
		{
			bRecord=false;

			if((i==0)&&m_bEnableProcPCB1)
			{
				if(GetDoc().GetEnLOTSn()&&(1==GetDoc().GetEnLOTInc()))		//����ӹ�LOTSn���Ҽӹ���ˮ�ţ���ʱ���¼��ˮ��
				{
					info = GetDoc().GetLOTIDInc();							//���ַ�����ʽ��ʾ����ˮ��
					
					if(m_bEnableProcPCB2)
						count0=atoi(info)-2;								//���ڼӹ���ˮ���ַ�ʱ��ˮ��ֵ�������ۼӣ���˼�¼ʱҪ��ȥ
					else
						count0=atoi(info)-1;
				}
				
				bRecord=true;				
			}

			if((i==1)&&m_bEnableProcPCB2)
			{
				if(GetDoc().GetEnLOTSn()&&(1==GetDoc().GetEnLOTInc()))		//����ӹ�LOTSn���Ҽӹ���ˮ�ţ���ʱ���¼��ˮ��
				{
					info = GetDoc().GetLOTIDInc();							//���ַ�����ʽ��ʾ����ˮ��

					count0=atoi(info)-1;									//���ڼӹ���ˮ���ַ�ʱ��ˮ��ֵ�������ۼӣ���˼�¼ʱҪ��ȥ
				}
				
				bRecord=true;				
			}

			if(bRecord)
			{ 			
				for(int j=0;j<recordTimes;j++)
				{			
					if(recordTimes==2)
					{
						if(i==0)
						{
							if(j==0)
								strAxis="L_Dn";
							else
								strAxis="L_Up";
						}
						
						if(i==1)
						{
							if(j==0)
								strAxis="R_Dn";
							else
								strAxis="R_Up";
						}	
					}
					else
					{
						if(i==0)
							strAxis="L";
						
						if(i==1)
							strAxis="R";
					}
	
					if (GetDoc().GetDrillInc())
					{
						if(i==0)
						{
							dbScaleX=(m_dbScaleLX[j]-1.0)*10000.0;
							dbScaleY=(m_dbScaleLY[j]-1.0)*10000.0;
						}
						
						if(i==1)
						{
							dbScaleX=(m_dbScaleRX[j]-1.0)*10000.0;
							dbScaleY=(m_dbScaleRY[j]-1.0)*10000.0;
						}
					}
					else
					{
						if(i==0)
						{
							dbScaleX=m_dbScaleLX[j];
							dbScaleY=m_dbScaleLY[j];
						}
						
						if(i==1)
						{
							dbScaleX=m_dbScaleRX[j];
							dbScaleY=m_dbScaleRY[j];
						}					
					}

					if(GetDoc().GetEnLOTSn()&&(1==GetDoc().GetEnLOTInc()))		//����ӹ�LOTSn���Ҽӹ���ˮ�ţ���ʱ���¼��ˮ��
					{
						GetInfo().SaveToFile(strinfo,"%s, %s, %s, %1.6f, %1.6f,%s, %s, %.0fs,%d,%s\n",strAxis,
							daybuf,timebuf,dbScaleX,dbScaleY,strrp,strName,difftime( m_EndTime, m_StartTime ),count0,strb);
					}
					else
					{
						GetInfo().SaveToFile(strinfo,"%s, %s, %s, %1.6f, %1.6f,%s, %s, %.0fs,%s\n",strAxis,
							daybuf,timebuf,dbScaleX,dbScaleY,strrp,strName,difftime( m_EndTime, m_StartTime ),strb);
					}

#ifdef USELOG
					temp="";
					saveData=""; 
					strIncreasing="";

//20150415 ԭ����GetDoc().GetLOTIDFix()�޸�ΪGetDoc().GetLOTIDFix()+ GetDoc().GetNoProcessID();��ʵ�ʰ���ֹ��趨������¼��ӵ�"�̶���"����
					if (GetDoc().GetDrillInc())
					{
						temp=GetDoc().GetNoProcessID();

						if (GetDoc().IsManSetScale())
						{
							double dbSX11=1.0;
							double dbSY11=1.0;
							GetDoc().GetManSetScaleVal(dbSX11,dbSY11);
							
//							scaleLXInfo=scaleRXInfo=dbSX11;
//							scaleLYInfo=scaleRYInfo=dbSY11;

							temp.Format("%s@%5.6f@%5.6f",GetDoc().GetNoProcessID(),(dbSX11-1.0)*10000.0,(dbSY11-1.0)*10000.0);
						}
						
//						if (GetDoc().IsManSetScale())
//							temp.Format("%s@%5.6f@%5.6f",GetDoc().GetNoProcessID(),(scaleLXInfo-1.0)*10000.0,(scaleLYInfo-1.0)*10000.0);
					}	
					
					if(GetDoc().GetEnLOTSn())
					{
						saveData=Lotidfix+temp;
						
						if(i==0)
							strIncreasing=m_LIncreasingStr;
						
						if(i==1)
							strIncreasing=m_RIncreasingStr;
					}
					else
					{
						saveData="NO"+temp;
						strIncreasing="NO";
					}	

					GetLog().Append_calc(strAxis,strName,dbScaleX,dbScaleY,difftime( m_EndTime, m_StartTime ),"OK",GetDoc().GetCurPCBHoleCount(),strb,saveData,strIncreasing);	
#endif
				}
			}
		}
	}
}

HoleCoordV CControl::GetProcFiducialForSix(int index)
{
	HoleCoordV crdV;

	if(index==0)
	{
		crdV.push_back(GetExcellonData().GetFiducialPos(0));
		crdV.push_back(GetExcellonData().GetInnerFiducialPos(0));
		crdV.push_back(GetExcellonData().GetInnerFiducialPos(1));
		crdV.push_back(GetExcellonData().GetFiducialPos(3));
	}
	else
	{
		crdV.push_back(GetExcellonData().GetInnerFiducialPos(0));
		crdV.push_back(GetExcellonData().GetFiducialPos(1));
		crdV.push_back(GetExcellonData().GetFiducialPos(2));
		crdV.push_back(GetExcellonData().GetInnerFiducialPos(1));
	}

	return crdV;
}
/*
void CControl::SortFiducial(int count,HoleCoordV& crdV)
{
	ASSERT(count<=4);

	Coord crd=Coord();
	int where[4];
//	char ez[256]={""};
	
	for(int p=0; p<count; ++p)
		crd+=crdV[p];
	
	crd=crd/count;
	
	for(int m=0; m<count; ++m)
	{
		if(crdV[m].x>=crd.x)
		{
			if(crdV[m].y>=crd.y)
			{
				if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
					where[m]=2;
				else
					where[m]=1;
			}
			else
			{
				if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)				
					where[m]=1;
				else
					where[m]=2;
			}
		}
		else
		{
			if(crdV[m].y>=crd.y)
			{
				where[m]=3;
			}
			else
			{
				where[m]=0;
			}		      
		}
	}
	
	for(int i=0;i<count-1;i++)
	{
		for(int j=i+1;j<count;j++)
		{	
			if(where[j]<where[i])
			{
				std::swap(where[j],where[i]);
				std::swap(crdV[j],crdV[i]);
			}
		}
	}
}
*/
/*
void CControl::SortFiducial(int count,HoleCoordV& crdV)						//20190328
{
	ASSERT(count<=4);

	Coord crd=Coord();
	int where[4];
	bool bSet[4]={false,false,false,false};
	
	for(int p=0; p<count; ++p)
		crd+=crdV[p];
	
	crd=crd/count;
	
	for(int m=0; m<count; ++m)
	{
		if(count==3)
		{
			if(crdV[m].x>=crd.x)
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=1;
					bSet[1]=true;
				}
				else
				{
					where[m]=2;
					bSet[2]=true;
				}
			}
			else
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=3;
					bSet[3]=true;
				}
				else
				{
					where[m]=0;
					bSet[0]=true;
				}		      
			}
		}

		if(count==4)
		{
			if(crdV[m].x>=crd.x)
			{
				if(crdV[m].y>=crd.y)
				{
					if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
						where[m]=2;
					else
						where[m]=1;
				}
				else
				{
					if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)				
						where[m]=1;
					else
						where[m]=2;
				}
			}
			else
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=3;
				}
				else
				{
					where[m]=0;
				}		      
			}
		}
	}
	
	for(int i=0;i<count-1;i++)
	{
		for(int j=i+1;j<count;j++)
		{	
			if(where[j]<where[i])
			{
				std::swap(where[j],where[i]);
				std::swap(crdV[j],crdV[i]);
			}
		}
	}

	if(count==3)
	{
		for(int n=0; n<4; ++n)
		{
			if(!bSet[n])
			{
				if((n==0)||(n==1))
					std::swap(crdV[0],crdV[2]);
			}
		}
	}
}
*/
/*
void CControl::SortFiducial(int count,HoleCoordV& crdV)						//20190828
{
	ASSERT(count<=4);

	Coord crd=Coord();
	int where[4];
	bool bSet[4]={false,false,false,false};
	
	for(int p=0; p<count; ++p)
		crd+=crdV[p];
	
	crd=crd/count;
	
	for(int m=0; m<count; ++m)
	{
		if(count==3)
		{
			if(crdV[m].x>=crd.x)
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=1;
					bSet[1]=true;
				}
				else
				{
					where[m]=2;
					bSet[2]=true;
				}
			}
			else
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=3;
					bSet[3]=true;
				}
				else
				{
					where[m]=0;
					bSet[0]=true;
				}		      
			}
		}

		if(count==4)
		{
			if(crdV[m].x>=crd.x)
			{
				if(crdV[m].y>=crd.y)
				{
					if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)
						where[m]=2;
					else
					{
						if(GetDoc().GetLoadAfterPitch())
							where[m]=2;
						else
							where[m]=1;
					}
				}
				else
				{
					if(GetDoc().GetProcMode()==SystemDoc::EXTERNALMARKPROC)				
						where[m]=1;
					else
					{
						if(GetDoc().GetLoadAfterPitch())
							where[m]=1;
						else
							where[m]=2;
					}
				}
			}
			else
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=3;
				}
				else
				{
					where[m]=0;
				}		      
			}
		}
	}
	
	for(int i=0;i<count-1;i++)
	{
		for(int j=i+1;j<count;j++)
		{	
			if(where[j]<where[i])
			{
				std::swap(where[j],where[i]);
				std::swap(crdV[j],crdV[i]);
			}
		}
	}

	if(count==3)
	{
		for(int n=0; n<4; ++n)
		{
			if(!bSet[n])
			{
				if((n==0)||(n==1))
					std::swap(crdV[0],crdV[2]);
			}
		}
	}
}
*/
void CControl::SortFiducial(int count,HoleCoordV& crdV)						//20191210
{
	ASSERT(count<=4);

	Coord crd=Coord();
	int where[4];
	bool bSet[4]={false,false,false,false};
	
	for(int p=0; p<count; ++p)
		crd+=crdV[p];
	
	crd=crd/count;
	
	for(int m=0; m<count; ++m)
	{
		if(count==3)
		{
			if(crdV[m].x>=crd.x)
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=1;
					bSet[1]=true;
				}
				else
				{
					where[m]=2;
					bSet[2]=true;
				}
			}
			else
			{
				if(crdV[m].y>=crd.y)
				{
					where[m]=3;
					bSet[3]=true;
				}
				else
				{
					where[m]=0;
					bSet[0]=true;
				}		      
			}
		}

		if(count==4)
		{
			if(crdV[m].x>=crd.x)
			{
				if(crdV[m].y>=crd.y)
				{
					if(GetDoc().GetLoadAfterPitch())
						where[m]=2;
					else
						where[m]=1;
				}
				else
				{
					if(GetDoc().GetLoadAfterPitch())
						where[m]=3;
					else
						where[m]=2;
				}
			}
			else
			{
				if(crdV[m].y>=crd.y)
				{
					if(GetDoc().GetLoadAfterPitch())
						where[m]=1;
					else
						where[m]=3;
				}
				else
				{
					where[m]=0;
				}		      
			}
		}
	}
	
	for(int i=0;i<count-1;i++)
	{
		for(int j=i+1;j<count;j++)
		{	
			if(where[j]<where[i])
			{
				std::swap(where[j],where[i]);
				std::swap(crdV[j],crdV[i]);
			}
		}
	}

	if(count==3)
	{
		for(int n=0; n<4; ++n)
		{
			if(!bSet[n])
			{
				if((n==0)||(n==1))
					std::swap(crdV[0],crdV[2]);
			}
		}
	}
}

//ѭ���ӹ���ʱ���											//20161212
time_t CControl::GetCycleStartTime()
{
	return m_StartTime;
}

void CControl::SetCycleStartTime(time_t time)
{
	m_StartTime=time;
}

BOOL CControl::TargetFindInCali(int nHead,int count,HoleCoordV& crdV,CArray<Coord, Coord> &dev,int testType)	//20180417 �޸�
{
//����ͼ��ʶ����ز���
	char scrName[MaxPathLen]; 
	char destName[MaxPathLen];
	char ez[256]={""};
	CString message;

	int width=GetDoc().GetCCDProcInnerRange();
	int height=GetDoc().GetCCDProcInnerRange();
	float minScore=GetDoc().GetCCDAdjThreshold()/100.0;
	int thickness=0;
	int times=1;

	if((testType==2)||(testType==4))
		times=3;

	double dbDevX=0.0;
	double dbDevY=0.0;

	CString strName;
	if(testType<2)
	{
		if(GetDoc().GetTechnicType())
			strName = GetDoc().GetAppPath()+TESTPATTERNNAMELP;
		else
			strName = GetDoc().GetAppPath()+TESTPATTERNNAMESP;
		thickness=GetDoc().GetGalvoBoardThick();
	}
	else if(testType<4)
	{
		strName=GetDoc().GetAppPath()+GLASSPATTERN;
//		thickness=4800;
		thickness=GetDoc().GetPCBThickness();								//20200402
	}
	else
	{
		strName=GetDoc().GetAppPath()+REPEATPATTERN;
		thickness=GetDoc().GetTestBoardThickness();
	}

	CString strDest = GetDoc().GetAppPath()+TESTTARGETNAME;

	sprintf(scrName,"%s",strName);
	sprintf(destName,"%s",strDest);

//��CCD��Դ
//	LightTurnOn(GALNOMATRIX);

//Z��CCD�۽�
	ZAxisCCDFocus(nHead,thickness);

//Cognexģ��ѧϰ
#ifdef USERCOGNEX
	CogSetShapePolarity((CogShapeExtractPolarityConstants)2);	//Cognex����Ŀ��ʶ���� cogShapeExtractPolarityDarkOnLight = 2
	CogSetTrainParam(1,2.0,1.0);
	if(!CogTrain(scrName,false))
		return false;
#endif

//����Ӧ��ͼ��ͨ��
#ifdef USEIMAGE			
	if (!GetImageCaptor().SelectChannel(nHead))
	{
		SetLampStatus(CControl::ERR);
		ChannelOutput(OCOMMONALARM ,TRUE);
		
		message.Format("CCDͨ��%dͼ���ȡʧ�ܣ����˳��ӹ�����ȷ��!",nHead);
		AfxMessageBox(message);
		
		SetLampStatus(CControl::ORDER);
		ChannelOutput(OCOMMONALARM ,FALSE);
		return false;
	}
#endif
//----------------------------------------------------------------------//���ԭ�е� //20190311
	char destBackup[MaxPathLen];										
	CString strBackup=GetDoc().GetAppPath()+"bmp\\cali";

	for(int nn=0; nn<count; ++nn)
	{
		sprintf(destBackup,"%s%d.bmp",strBackup,nn+1);
		DeleteFile(destBackup);
	}

	memset(destBackup,'\0',MaxPathLen);
//----------------------------------------------------------------------
//Ŀ��ʶ��
	for(int n=0; n<count; ++n)
	{
		if(testType==0)
		{
			if(PatternMatch(crdV[n],scrName,destName,width,height,times,0.5,dbDevX,dbDevY))
				return true;
			else
			{
				if(n==count-1)
					return false;
			}
		}
		else 
		{
			while(!PatternMatch(crdV[n],scrName,destName,width,height,times,minScore,dbDevX,dbDevY))
			{
				SetLampStatus(CControl::ERR);							//20190711 ����
				ChannelOutput(OCOMMONALARM ,TRUE);

				int nSel=0;
				
				if(nHead==HeadLeft)
					strncpy(ez,GetLang().GetWarningText(22021),256);	//"����%d�����ƥ��ʧ��!\n��Ҫ������?"
				else
					strncpy(ez,GetLang().GetWarningText(22022),256);	//"�Ҳ��%d�����ƥ��ʧ��!\n��Ҫ������?"
				message.Format(ez,n+1);
				
				nSel = ::AfxMessageBox(message,MB_YESNO);								
				
				if(nSel==IDYES)
				{
//					strncpy(ez,GetLang().GetWarningText(21046),256);	//20190711 ȡ��
//					AfxMessageBox(ez);									//"�����µ���CCD��Դ���Ȼ�����������!"
					
					pImageParaSetView->pLampAdj->ShowWindow(SW_SHOW);
					
					while(1)
					{
						for(int m=0;m<12;m++)
							DoEvent();
						
						if(pImageParaSetView->pLampAdj->IsWindowVisible())
							Sleep(50);
						else
							break;
					}

					if(GetControl().GetRunState()==CControl::RUN)		//20190711 ����
						SetLampStatus(CControl::ORDER);						
					else
						SetLampStatus(CControl::WARN);

					ChannelOutput(OCOMMONALARM ,FALSE);
				}
				else
				{
					SetLampStatus(CControl::WARN);						//20190711 ����
					ChannelOutput(OCOMMONALARM ,FALSE);

					return false;
				}
			}
			
			dev.Add(Coord(dbDevX,dbDevY));
//----------------------------------------------------------------------//20190311
			sprintf(destBackup,"%s%d.bmp",strBackup,n+1);				
			CopyFile(destName,destBackup,false);
//----------------------------------------------------------------------
		}
	}

//�ر�CCD��Դ
//	LightTurnOff();

	return true;
}

#ifdef SMCPreLoad
BOOL CControl::PreLoadCreate(bool bIsSubarea,bool bIsRegion,bool bIsPower,int nIndex)			//20180619
{
	char SegName[20];
	long nHoleCnt=0;										//int->long 20190917
	long holecnt=0;											//int->long 20190917
	JumpAndFirePoint2D *points;
	
	if(!GalvoJobLoadInit())
		return false;

//��������
	if(bIsRegion)
	{
		PulsePmrV ppV;
		ppV=GetRegionPmr();
		
		XYData windowData;
		XYDataV xySubV;
		unsigned int offsetX=0,offsetY=0;
		GetSubData(xySubV,RECTWINDOW,0);
		holecnt = xySubV.size();
		
		for(int nWindowTimes=0;nWindowTimes<ppV.size();nWindowTimes++)
		{  
			points = (JumpAndFirePoint2D *)malloc(sizeof(JumpAndFirePoint2D) * holecnt);
			nHoleCnt = 0;
			
			offsetX=ppV[nWindowTimes].xOffset;
			offsetY=ppV[nWindowTimes].yOffset;
			
			while(nHoleCnt<holecnt)
			{
				windowData=xySubV[nHoleCnt];
				
				points[nHoleCnt].x=windowData.coordX+offsetX;
				points[nHoleCnt].y=windowData.coordY+offsetY;
				points[nHoleCnt].laserData=0;
				
				nHoleCnt++;
			}
	
			sprintf(SegName,"Region_%d",nWindowTimes);					//Region_ѭ����
			
			if(!GalvoJobLoad(SegName,holecnt,points,10))				//laserOnTime=10us
			{
				free(points);
				return false;
			}
			
			free(points);
		}
	}

//���ʲ�������	
	if(bIsPower)
	{
		short lDPosH=0;				//mm
		short lDPosV=0;				//mm
		
		switch(nIndex)
		{
		case 0:
			lDPosH= 0;
			lDPosV= 0;
			break;
		case 1:
			lDPosH= -25;
			lDPosV= 25;
			break;
		case 2:
			lDPosH= 25;
			lDPosV= 25;
			break;
		case 3:
			lDPosH= -25;
			lDPosV=-25;
			break;
		case 4:
			lDPosH= 25;
			lDPosV= -25;
			break;
		default: 
			return false;
		}

		int count=1000;
		int bitPerMM=GetDoc().GetSLBitPerMM();
		points = (JumpAndFirePoint2D *)malloc(sizeof(JumpAndFirePoint2D)*count); 
		
		for(int k=0;k<count;k++)
		{
			points[k].x=-lDPosV*bitPerMM;
			points[k].y=lDPosH*bitPerMM;
			points[k].laserData=0;
		}
			
		sprintf(SegName,"Power");											//Power
		
		if(!GalvoJobLoad(SegName,count,points,10))							//laserOnTime=10us
		{
			free(points);
			return false;
		}

		free(points);
	}

//�������
	m_bSADataIsPreLoad=true;								//20191015

	if(bIsSubarea)
	{
		for(int nSubAreaNo=0;nSubAreaNo<GetExcellonData().GetSubAreaCnt();nSubAreaNo++)
		{
			SubArea& subarea = GetExcellonData().GetSubAreaData(nSubAreaNo);
		
			for(int it=0;it<GetDoc().GetToolsCnt();it++)	//����
			{
				int nToolNo = GetDoc().GetToolNo(it);
				
				int nSubToolIndex = subarea.GetSameToolIndex(nToolNo);
				if(nSubToolIndex==-1)
					continue;
				
				holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
				if (holecnt<=0) 
					continue;

				if(holecnt>50000)							//20191015
				{
					if(!GalvoJobLoadInit())
						return false;

					m_bSADataIsPreLoad=false;
					return true;
				}
				
				std::vector<Coord>::iterator Holecrd;
				std::vector<HoleClass>::iterator hcv;
				hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
				
				points = (JumpAndFirePoint2D *)malloc(sizeof(JumpAndFirePoint2D) * holecnt);  
				nHoleCnt = 0;
				
				while(nHoleCnt<holecnt)
				{
					Holecrd = hcv->hcvHolePos.begin()+nHoleCnt;
					
					points[nHoleCnt].x=Holecrd->x;
					points[nHoleCnt].y=Holecrd->y;
					points[nHoleCnt].laserData=0;
					
					nHoleCnt++;
				}
			
				sprintf(SegName,"Data_%d_%d",it,nSubAreaNo);				//Data_���ߺ�_������
				
				if(!GalvoJobLoad(SegName,holecnt,points,10))				//laserOnTime=10us
				{
					free(points);
					return false;
				}

				free(points);	
			}
		}
	}
	else
		m_bSADataIsPreLoad=false;

	return true;
}
#endif
											
void CControl::SetTablePosX(long pos)
{
	m_lTablePosX=pos;
}

void CControl::SetTablePosY(long pos)
{
	m_lTablePosY=pos;
}

void CControl::ZAxisCCDFocus(int nHead,long thickness,bool bWaitStop)
{
	if(nHead==HeadLeft)
	{
		MoveTo(AXISLEFTZ,GetDoc().GetCCDFocus(0)-thickness);

		if(bWaitStop)
			WaitAxisStop(AXISLEFTZ);
	}
	else if(nHead == HeadRight)
	{	
		MoveTo(AXISRIGHTZ,GetDoc().GetCCDFocus(1)-thickness);

		if(bWaitStop)
			WaitAxisStop(AXISRIGHTZ);
	}
	else if(nHead == HeadBoth)
	{
		MoveTo(AXISLEFTZ,GetDoc().GetCCDFocus(0)-thickness);
		MoveTo(AXISRIGHTZ,GetDoc().GetCCDFocus(1)-thickness);

		if(bWaitStop)
		{
			WaitAxisStop(AXISLEFTZ);
			WaitAxisStop(AXISRIGHTZ);
		}
	}
}

void CControl::ZAxisLensFocus(int nHead,long thickness,bool bWaitStop)
{
	if(nHead==HeadLeft)
	{
		if(GetDoc().GetTechnicType())
			MoveTo(AXISLEFTZ,GetDoc().GetLongPathLaserProcFocus(0)-thickness);
		else 
			MoveTo(AXISLEFTZ,GetDoc().GetLaserProcFocus(0)-thickness);

		if(bWaitStop)
			WaitAxisStop(AXISLEFTZ);
	}
	else if(nHead == HeadRight)
	{	
		if(GetDoc().GetTechnicType())
			MoveTo(AXISRIGHTZ,GetDoc().GetLongPathLaserProcFocus(1)-thickness);
		else
			MoveTo(AXISRIGHTZ,GetDoc().GetLaserProcFocus(1)-thickness);

		if(bWaitStop)
			WaitAxisStop(AXISRIGHTZ);
	}
	else if(nHead == HeadBoth)
	{
		if(GetDoc().GetTechnicType())
		{
			MoveTo(AXISLEFTZ,GetDoc().GetLongPathLaserProcFocus(0)-thickness);
			MoveTo(AXISRIGHTZ,GetDoc().GetLongPathLaserProcFocus(1)-thickness);
		}
		else
		{
			MoveTo(AXISLEFTZ,GetDoc().GetLaserProcFocus(0)-thickness);
			MoveTo(AXISRIGHTZ,GetDoc().GetLaserProcFocus(1)-thickness);
		}

		if(bWaitStop)
		{
			WaitAxisStop(AXISLEFTZ);
			WaitAxisStop(AXISRIGHTZ);
		}
	}
}

BOOL CControl::DrillTableTest(int nHead,int iToolNo)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetPCBThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);	
	Delay(500);
	
	POINTTYPE pt=ONLYHOLE;
	int iCount=11;
	long lProcRangeBit=10*GetDoc().GetSLBitPerMM();

	int nApt;	
	int nToolCycNum = GetDoc().GetToolPara(iToolNo,0).GetCycleNum();

	int times=9;
	int step=11000;
	Coord crd=Coord(GetPos(AXISTABX),GetPos(AXISTABY));
	int offsetX[9]={-1,0,1,1,0,-1,-1,0,1};
	int offsetY[9]={-1,-1,-1,0,0,0,1,1,1};

	for(int j=0;j<times;j++)
	{
		MoveTo(crd+Coord(offsetX[j]*step,offsetY[j]*step));

		WaitAxisStop(AXISTAB);

		for(int k=0; k<nToolCycNum; ++k)
		{
			Energy eng;
			int minJump=0;	
			
			if(GetDoc().GetToolSubApertureNo(iToolNo)!=0)
//			if(GetDoc().GetToolSubShowApertureNo(iToolNo)!=0)
			{
				if(k==0)
					nApt = GetDoc().GetToolApertureNo(iToolNo);
				else
					nApt = GetDoc().GetToolSubApertureNo(iToolNo);
			}
			else
				nApt = GetDoc().GetToolApertureNo(iToolNo);
			
			MoveTo(nApt);
			
			eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);
			
			if (k==0)
			{
				if(GetDoc().GetFitApt())
					minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
				else
					minJump=GetDoc().GetFirstDelayPeriod(); 
			}
			else
				minJump=GetDoc().GetOtherDelayPeriod();	
			
//			MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,lProcRangeBit,iCount,pt,iToolNo);
			MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,lProcRangeBit,iCount,pt,iToolNo,false,k==0);			//20181229
		}
	}
	
//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
	
	return true;
}

BOOL CControl::DrillTableAccuracy(int nHead,int iToolNo)
{
	ASSERT(nHead==HeadLeft||nHead==HeadRight||nHead==HeadBoth);

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetPCBThickness());

//��ͷ����������
	ChannelOutput(OTHETALENSPROTECT,MIO_ON);	
	Delay(500);
	
	POINTTYPE pt=ONLYHOLE;
	int iCount=1;
	long lProcRangeBit=10*GetDoc().GetSLBitPerMM();

	int nApt;	
	int nToolCycNum = GetDoc().GetToolPara(iToolNo,0).GetCycleNum();

	Coord crd0;
	crd0.x=250000;
	crd0.y=400000;									//394000

 	int tempXPoints=25;
 	int tempYPoints=29;
	int interval=20000;

	for(int i=0;i<tempYPoints;i++)		
	{
		for(int j=0;j<tempXPoints;j++)			
		{
			MoveTo(Coord(crd0.x-j*interval,crd0.y-i*interval));
			
			WaitAxisStop(AXISTAB);
			
			for(int k=0; k<nToolCycNum; ++k)
			{
				Energy eng;
				int minJump=0;	
				
				if(GetDoc().GetToolSubApertureNo(iToolNo)!=0)
//				if(GetDoc().GetToolSubShowApertureNo(iToolNo)!=0)
				{
					if(k==0)
						nApt = GetDoc().GetToolApertureNo(iToolNo);
					else
						nApt = GetDoc().GetToolSubApertureNo(iToolNo);
				}
				else
					nApt = GetDoc().GetToolApertureNo(iToolNo);
				
				MoveTo(nApt);
				
				eng = GetDoc().GetToolPara(iToolNo,0).GetCycEnergy(k);
				
				if (k==0)
				{
					if(GetDoc().GetFitApt())
						minJump=GetDoc().GetAptDelay(GetDoc().GetCurAptNo());
					else
						minJump=GetDoc().GetFirstDelayPeriod(); 
				}
				else
					minJump=GetDoc().GetOtherDelayPeriod();	
				
//				MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,lProcRangeBit,iCount,pt,iToolNo);
				MatrixProcess(nHead,eng.m_iRelease,minJump,STYPE,lProcRangeBit,iCount,pt,iToolNo,false,k==0);			//20181229
			}
		}
	}
	
//��ͷ���������ر�
	Delay(500);
	ChannelOutput(OTHETALENSPROTECT,MIO_OFF);
	
	return true;
}

#ifdef HIKAGV
BOOL CControl::SetAGVOutput(CString strTaskTypeCode,CString strStaPositionCode,CString strEndPositionCode,CString& strReqCode)
{
	CHttpClient   conn;
	CString postResponse = "";
	CString ip = GetDoc().GetSysRCSIP();
	CString port = GetDoc().GetSysRCSPort();
	CString methodName = "genAgvSchedulingTask";
	char url[256] = "";
	sprintf(url,"http://%s:%s/cms/services/rest/hikRpcService/%s",ip,port,methodName);

	strReqCode = conn.generate();
	CTime time;							//ʵ��һ��ʱ�����
    CString currentTime;				//��ʾʱ��
	time = CTime::GetCurrentTime();		//��ȡϵͳ��ǰʱ��
	currentTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));//��time�����е�ʱ����Ϣ(��,��,��,ʱ,��,��)�洢��CString�����н�����ʾ

	RequsetParam postParam;				//�����������
	postParam.reqCode = strReqCode;
	postParam.reqTime = currentTime;
	postParam.interfaceName = methodName;
	postParam.taskTyp = strTaskTypeCode;
	postParam.riseStaPositionCode = strStaPositionCode;
	postParam.riseEndPositionCode = strEndPositionCode;
	postParam.priority = "2";
	postParam.taskCode = strReqCode;

	CString postData = postParam.writeParamInfoJson();
	int result = conn.HttpPost(url,postData,postResponse);
//	TRACE("result = %d\n",result);
//	TRACE("postResponse = %s\n",postResponse);
	if (result != 0)
	{
		AfxMessageBox("С�����������·�ʱ���緢���쳣��");
		return false;
	}
	else
	{
		string strValue = postResponse.GetBuffer(0);
		Json::Reader reader;		//json����
		Json::Value value;			//��ʾһ��json��ʽ�Ķ���
		
		if(reader.parse(strValue,value))//������json�ŵ�json����
		{
			string errCode=value["code"].asString();
//			TRACE("code = %s\n",errCode.c_str());
			string errMessage = value["message"].asString();
//			TRACE("message = %s\n",errMessage.c_str());
			if ((errCode != "0")||(errMessage != "�ɹ�"))
			{
				AfxMessageBox("С����������ִ��ʱ�����쳣��");
				return false;
			}
		}
		else
		{
			AfxMessageBox("С�����������·�ʱ���練���쳣��");
			return false;
		}
	}

	return true;
}

int CControl::QueryAGVInput(CString strInput)
{
	CHttpClient   conn;
	CString postResponse = "";
	CString ip = GetDoc().GetSysRCSIP();
	CString port = GetDoc().GetSysRCSPort();
	CString methodName = "queryTaskStatus";
	char url[256] = "";
	sprintf(url,"http://%s:%s/cms/services/rest/hikRpcService/%s",ip,port,methodName);
	
	CString reqCode = conn.generate();
	CTime time;					//ʵ��һ��ʱ�����
    CString currentTime;		//��ʾʱ��
	time = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
	currentTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));//��time�����е�ʱ����Ϣ(��,��,��,ʱ,��,��)�洢��CString�����н�����ʾ
	
	//�����������
	RequsetParam postParam;
	postParam.reqCode = reqCode;
	postParam.reqTime = currentTime;
	postParam.interfaceName = methodName;
	postParam.taskCodes = strInput;

	CString postData = postParam.writeParamInfoJson();
	int result = conn.HttpPost(url,postData,postResponse);
//	TRACE("result = %d\n",result);
//	TRACE("postResponse = %s\n",postResponse);
	if (result != 0)
	{
		AfxMessageBox("С����ѯ�����·�ʱ���緢���쳣��");
		return 2;
	}
	else
	{
		string strValue = postResponse.GetBuffer(0);
		Json::Reader reader;	//json����
		Json::Value value;		//��ʾһ��json��ʽ�Ķ���

		if(reader.parse(strValue,value))//������json�ŵ�json����
		{
			string errCode=value["code"].asString();
//			TRACE("code = %s\n",errCode.c_str());
			string errMessage = value["message"].asString();
//			TRACE("message = %s\n",errMessage.c_str());

			if ((errCode != "0")||(errMessage != "�ɹ�"))
			{
				AfxMessageBox("С����ѯ����ִ��ʱ�����쳣��");
				return 2;
			}
			
			std::string taskStatus;
			const Json::Value arrayObj = value["data"];//������
			for (int i = 0; i < arrayObj.size(); i++)
			{
				taskStatus = arrayObj[i]["taskStatus"].asString();
			}
			
			return ((taskStatus == "�ѽ���")?1:0);
		}
		else
		{
			AfxMessageBox("С����ѯ�����·�ʱ���練���쳣��");
			return 2;
		}
	}
}

BOOL CControl::AGVTransport(int status)
{
//�жϻ�̨�Ƿ�׼����							//20191120
	if(!QueryCOMInput(74))						//AGV���Ѱ��£�
	{
		AfxMessageBox("���ϻ�����ϵ���ɫ��ť�谴�£���ȷ�ϣ�");
		return false;
	}

	time_t start_time, end_time;
	BOOL rtn;

//����С������
	if(!SetAGVOutput(GetDoc().GetSysTaskTypeRise(),GetDoc().GetSysRiseStaPositionCode(),GetDoc().GetSysRiseEndPositionCode(),riseReqCode))
		return false;

//ȷ��С����λ
	end_time = start_time = time( NULL );
	rtn=false;

	while(!rtn)
	{
		rtn=QueryAGVInput(riseReqCode);

		if(2==rtn)
			return false;

		end_time = time( NULL );

		if((difftime(end_time, start_time))>360)
		{				
			AfxMessageBox("С����������ʱ��ʱ����ȷ�ϣ�");
			return false;				
		}

		Delay(2000);
	}

//AGV���Ϻ�����									//20191120
	SetCOMOutput(26);							//AGV��λ
	Delay(500);

	if((1==status)||(2==status))
	{
		SetCOMOutput(24);						//AGV����
		
		end_time = start_time = time( NULL );
		
		while(QueryCOMInput(70))				//AGV������ɣ�
		{
			end_time = time( NULL );
			
//			if(!PeekRunState())
//				return false;
			
//			if((difftime(end_time, start_time)-m_PauseTimeInSec)>90)
			if(difftime(end_time, start_time)>60)
			{				
				AfxMessageBox("AGV���Ϲ��̳�ʱ����ȷ�ϣ�");
				return false;				
			}
			
			Delay(LOADANDUNLOADDELAY);
		}
	}

	if((0==status)||(2==status))
	{
		SetCOMOutput(25);						//AGV����
		
		end_time = start_time = time( NULL );
		
		while(QueryCOMInput(69))				//AGV������ɣ�
		{
			end_time = time( NULL );
			
//			if(!PeekRunState())
//				return false;
			
//			if((difftime(end_time, start_time)-m_PauseTimeInSec)>90)
			if(difftime(end_time, start_time)>60)
			{				
				AfxMessageBox("AGV���Ϲ��̳�ʱ����ȷ�ϣ�");
				return false;				
			}
			
			Delay(LOADANDUNLOADDELAY);
		}
	}

	if(1==status)								//��ȡ��
		GetDoc().SetPCBBoardIsReady(false);
	else
		GetDoc().SetPCBBoardIsReady(true);

//����С����ȥ
	if(!SetAGVOutput(GetDoc().GetSysTaskTypeDown(),GetDoc().GetSysDownStaPositionCode(),GetDoc().GetSysDownEndPositionCode(),downReqCode))
		return false;

//ȷ��С���뿪
	end_time = start_time = time( NULL );
	rtn=false;

	while(!rtn)
	{
		rtn=QueryAGVInput(downReqCode);

		if(2==rtn)
			return false;

		end_time = time( NULL );

		if((difftime(end_time, start_time))>360)
		{				
			AfxMessageBox("С����������ʱ��ʱ����ȷ�ϣ�");
			return false;				
		}

		Delay(2000);
	}

	return true;
}
#endif

#ifdef ONEAXISDATATRANSFORMTEST
bool CControl::OneAxisSubAreaDataTransform(int nHead,SubArea &subarea,int Aptno)
{
	Coord crdBefore,crdAfter;
	Coord crdCenterBefore,crdCenterAfter;
	double factor1=1000.0/(double)GetDoc().GetSLBitPerMM();
	double factor2=(double)GetDoc().GetSLBitPerMM()/1000.0;

	crdCenterBefore=subarea.crdCenter;
//	if(!CogSetMapPoint(nHead,crdCenterBefore,crdCenterAfter))
//		return false;
	if(m_bUseOldScale)
	{
		crdCenterAfter=crdCenterBefore+GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crdCenterBefore,nHead);
	}
	else
	{
		if(!CogSetMapPoint(nHead,crdCenterBefore,crdCenterAfter))
			return false;
	}


	for(int it=0;it<GetDoc().GetToolsCnt();++it)
	{
//�жϹ�Ȧ�Ų���ͬ�Ĳ��ӹ�
		if(Aptno!=GetDoc().GetToolApertureNo(it))  //2009 12 24 
//		if(Aptno!=GetDoc().GetToolShowApertureNo(it))  //2009 12 24 
			continue;
		
	    int nToolNo = GetDoc().GetToolNo(it);
		int nSubToolIndex = subarea.GetSameToolIndex(nToolNo);
	    if(nSubToolIndex==-1)
			continue;

		int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
		if (holecnt<=0) 
			continue ;
		
		long holeNum=0;	
		std::vector<HoleClass>::iterator hcv;
		std::vector<Coord>::iterator Holecrd;
		
		hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
		
		while( holeNum < holecnt )
		{
			Holecrd = hcv->hcvHolePos.begin()+holeNum;		
			
			crdBefore.x=Holecrd->y*factor1+crdCenterBefore.x;				//bit->um
			crdBefore.y=-Holecrd->x*factor1+crdCenterBefore.y;

//			if(!CogSetMapPoint(nHead,crdBefore,crdAfter))
//				return false;
			if(m_bUseOldScale)
			{
				crdAfter=crdBefore+GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crdBefore,nHead);	
			}
			else
			{
				if(!CogSetMapPoint(nHead,crdBefore,crdAfter))
					return false;
			}

			Holecrd->x=-(crdAfter.y-crdCenterAfter.y)*factor2;				//um->bit
			Holecrd->y=(crdAfter.x-crdCenterAfter.x)*factor2;

			holeNum++;
		}
	}

	return true;
}

bool CControl::OneAxisTableAndGalvoTransform(int nHead,Coord crd)
{
	Coord crdDest,crdOffsetL,crdOffsetR;
	char ez[256]=_T("");
	double lSLScale=GetDoc().GetSLBitPerMM()/1000.0;
	Coord Lcenter=Coord();
	Coord Rcenter=Coord();

//	m_crdGlvMidPos=(GetDoc().GetCCDToGlvSysOffset(HeadLeft)+GetDoc().GetCCDToGlvSysOffset(HeadRight))/2;	//20190731

	if(nHead==HeadLeft)
	{
		if(!CogSetMapPoint(HeadLeft,crd,Lcenter))
			return false;

//		if(!CogSetMapPoint(HeadRight,crd,Rcenter))
//			return false;

//		m_crdRealOffsetL=Lcenter-crd;					//�������ĵ�ƫ����
//		m_crdRealOffsetR=Rcenter-crd;					//�������ĵ�ƫ����

//		crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdRealOffsetL;
		crdDest = GetDoc().GetFileToRealRelative()-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-Lcenter;
		crdOffsetL=Coord();
		crdOffsetR=Coord();

//#ifdef TRANSFORMTEST
		if(m_bUseOldScale)
		{
//			crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdRealOffsetL;
			crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadLeft)-m_crdRealOffsetL-GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crd,HeadLeft);
			
//			crdOffsetL=GetGlvProcGlvOffset(0,crd,HeadLeft);
			crdOffsetL=Coord();
			crdOffsetR=Coord();
		}
//#endif
	}

	if(nHead==HeadRight)
	{
//		if(!CogSetMapPoint(HeadLeft,crd,Lcenter))
//			return false;

		if(!CogSetMapPoint(HeadRight,crd,Rcenter))
			return false;

//		m_crdRealOffsetL=Lcenter-crd;					//�������ĵ�ƫ����
//		m_crdRealOffsetR=Rcenter-crd;					//�������ĵ�ƫ����

//		crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdRealOffsetR;
		crdDest = GetDoc().GetFileToRealRelative()-GetDoc().GetCCDToGlvSysOffset(HeadRight)-Rcenter;
		crdOffsetL=Coord();
		crdOffsetR=Coord();

//#ifdef TRANSFORMTEST
		if(m_bUseOldScale)
		{
//			crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdRealOffsetR;
			crdDest = GetDoc().GetFileToRealRelative()-crd-GetDoc().GetCCDToGlvSysOffset(HeadRight)-m_crdRealOffsetR-GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crd,HeadRight);
			
			crdOffsetL=Coord();
//			crdOffsetR=GetGlvProcGlvOffset(0,crd,HeadRight);
			crdOffsetR=Coord();
		}
//#endif
	}

//	if (GetDoc().GetIsNullPrecessHoles())										//20200714 ɾ��
		MoveTo(crdDest);									//WaitAxisStop(AXISTAB)��������GlvSubAreaProc()��

#ifdef RTC5DLL
	GalvoCorrectionSetup(HeadLeft,1,1,0,-crdOffsetL.y*lSLScale,crdOffsetL.x*lSLScale);
	GalvoCorrectionSetup(HeadRight,1,1,0,-crdOffsetR.y*lSLScale,crdOffsetR.x*lSLScale);
#else
#ifdef SMCNewCorType
	GalvoCorrectionSetup(SH_Head1,1,1,0,-crdOffsetL.y*lSLScale,crdOffsetL.x*lSLScale);
	GalvoCorrectionSetup(SH_Head2,1,1,0,-crdOffsetR.y*lSLScale,crdOffsetR.x*lSLScale);
#else
//	double angleL=m_dbAngleL*180/M_PI;
//	double angleR=m_dbAngleR*180/M_PI;

	if(!SetHeadCorParam(HeadLeft,-crdOffsetL.y*lSLScale,crdOffsetL.x*lSLScale,0,1,1))
	{
		GetDoc().SetLastWarningNo(58);
		strncpy(ez,GetLang().GetWarningText(21050),256);
		AfxMessageBox(ez);									//"��У�������趨�쳣���޷������ӹ���������ӹ�!"
		return false;
	}
//	Delay(20);																	//20161216 ����	
	if(!SetHeadCorParam(HeadRight,-crdOffsetR.y*lSLScale,crdOffsetR.x*lSLScale,0,1,1))
	{
		GetDoc().SetLastWarningNo(59);
		strncpy(ez,GetLang().GetWarningText(21050),256);
		AfxMessageBox(ez);									//"��У�������趨�쳣���޷������ӹ���������ӹ�!"
		return false;
	}
#endif
#endif

	return true;
}

bool CControl::OneAxisSubAreaDataTransformAndFind(int nHead,SubArea &subarea,int Aptno)
{
	Coord crdBefore,crdAfter;
	Coord crdCenterBefore,crdCenterAfter;
	double factor1=1000.0/(double)GetDoc().GetSLBitPerMM();
	double factor2=(double)GetDoc().GetSLBitPerMM()/1000.0;

	Coord offset=Coord();
	if(nHead==HeadLeft)
		offset=m_crdRealOffsetL;
	if(nHead==HeadRight)
		offset=m_crdRealOffsetR;	

	crdCenterBefore=subarea.crdCenter;
//	if(!CogSetMapPoint(nHead,crdCenterBefore,crdCenterAfter))
//		return false;
	if(m_bUseOldScale)
	{
		crdCenterAfter=crdCenterBefore+GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crdCenterBefore,nHead);
	}
	else
	{
		if(!CogSetMapPoint(nHead,crdCenterBefore,crdCenterAfter))
			return false;
	}

	CArray<Coord, Coord> Dev;
	HoleCoordV crdTestV;
	
	Dev.RemoveAll();	
	crdTestV.clear();

	for(int it=0;it<GetDoc().GetToolsCnt();++it)
	{
//�жϹ�Ȧ�Ų���ͬ�Ĳ��ӹ�
		if(Aptno!=GetDoc().GetToolApertureNo(it))  //2009 12 24 
//		if(Aptno!=GetDoc().GetToolShowApertureNo(it))  //2009 12 24 
			continue;
		
	    int nToolNo = GetDoc().GetToolNo(it);
		int nSubToolIndex = subarea.GetSameToolIndex(nToolNo);
	    if(nSubToolIndex==-1)
			continue;

		int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
		if (holecnt<=0) 
			continue ;
		
		long holeNum=0;	
		std::vector<HoleClass>::iterator hcv;
		std::vector<Coord>::iterator Holecrd;
		
		hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
		
		while( holeNum < holecnt )
		{
			Holecrd = hcv->hcvHolePos.begin()+holeNum;		
			
			crdBefore.x=Holecrd->y*factor1+crdCenterBefore.x;				//bit->um
			crdBefore.y=-Holecrd->x*factor1+crdCenterBefore.y;

//			if(!CogSetMapPoint(nHead,crdBefore,crdAfter))
//				return false;
			if(m_bUseOldScale)
			{
				crdAfter=crdBefore+offset+GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crdBefore,nHead);	
			}
			else
			{
				if(!CogSetMapPoint(nHead,crdBefore,crdAfter))
					return false;
			}

//			Holecrd->x=-(crdAfter.y-crdCenterAfter.y)*factor2;				//um->bit
//			Holecrd->y=(crdAfter.x-crdCenterAfter.x)*factor2;
			crdTestV.push_back(GetDoc().GetFileToRealRelative()-crdAfter);

			holeNum++;
		}
	}

//��CCD��Դ
	GetControl().LightTurnOn(OUTERMAINPATTERN);	

	if(!TargetFindInCali(nHead,crdTestV.size(),crdTestV,Dev,3))
	{
		GetControl().LightTurnOff();
		return false;
	}

//�ر�CCD��Դ
	GetControl().LightTurnOff();

//���沣���߲�������
	CString outpointstr=GetDoc().GetAppPath()+"info\\GlassRulerTestData.txt";
	GetInfo().SaveToFile(outpointstr,"(CommandX,CommandY):(PosErrX,PosErrY)\n");

	for(int n=0; n<crdTestV.size();n++)
	{
		GetInfo().SaveToFile(outpointstr,"(%d,%d):(%d,%d)\n",crdTestV[n].x,crdTestV[n].y,Dev.GetAt(n).x,Dev.GetAt(n).y);
	}

	if(!PeekRunState())
		return false;

	return true;
}

bool CControl::OneAxisSubAreaDataTransformAndDrill(int nHead,SubArea &subarea,int Aptno)
{
	Coord crdBefore,crdAfter;
	Coord crdCenterBefore,crdCenterAfter;
	double factor1=1000.0/(double)GetDoc().GetSLBitPerMM();
	double factor2=(double)GetDoc().GetSLBitPerMM()/1000.0;

	Coord offset=Coord();
	if(nHead==HeadLeft)
		offset=m_crdRealOffsetL;
	if(nHead==HeadRight)
		offset=m_crdRealOffsetR;	

	crdCenterBefore=subarea.crdCenter;
//	if(!CogSetMapPoint(nHead,crdCenterBefore,crdCenterAfter))
//		return false;
	if(m_bUseOldScale)
	{
		crdCenterAfter=crdCenterBefore+GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crdCenterBefore,nHead);
	}
	else
	{
		if(!CogSetMapPoint(nHead,crdCenterBefore,crdCenterAfter))
			return false;
	}

	HoleCoordV crdTestV;	
	crdTestV.clear();

	for(int it=0;it<GetDoc().GetToolsCnt();++it)
	{
//�жϹ�Ȧ�Ų���ͬ�Ĳ��ӹ�
		if(Aptno!=GetDoc().GetToolApertureNo(it))  //2009 12 24 
//		if(Aptno!=GetDoc().GetToolShowApertureNo(it))  //2009 12 24 
			continue;
		
	    int nToolNo = GetDoc().GetToolNo(it);
		int nSubToolIndex = subarea.GetSameToolIndex(nToolNo);
	    if(nSubToolIndex==-1)
			continue;

		int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
		if (holecnt<=0) 
			continue ;
		
		long holeNum=0;	
		std::vector<HoleClass>::iterator hcv;
		std::vector<Coord>::iterator Holecrd;
		
		hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
		
		while( holeNum < holecnt )
		{
			Holecrd = hcv->hcvHolePos.begin()+holeNum;		
			
			crdBefore.x=Holecrd->y*factor1+crdCenterBefore.x;				//bit->um
			crdBefore.y=-Holecrd->x*factor1+crdCenterBefore.y;

//			if(!CogSetMapPoint(nHead,crdBefore,crdAfter))
//				return false;
			if(m_bUseOldScale)
			{
				crdAfter=crdBefore+offset+GetGlvProcGlvOffset((int)GetDoc().GetProcMode(),crdBefore,nHead);	
			}
			else
			{
				if(!CogSetMapPoint(nHead,crdBefore,crdAfter))
					return false;
			}

//			Holecrd->x=-(crdAfter.y-crdCenterAfter.y)*factor2;				//um->bit
//			Holecrd->y=(crdAfter.x-crdCenterAfter.x)*factor2;
			crdTestV.push_back(GetDoc().GetFileToRealRelative()-crdAfter-GetDoc().GetCCDToGlvSysOffset(nHead));

			holeNum++;
		}
	}

//�л���Ȧ
	MoveTo(GetDoc().GetTestAperture());

//Z��Lens�۽�
	ZAxisLensFocus(nHead,GetDoc().GetPCBThickness());

	for(int n=0; n<crdTestV.size();n++)
	{
		MoveTo(crdTestV[n]);	
		WaitAxisStop(AXISTAB);	

		MatrixProcess(nHead,GetDoc().GetTestPlsRelease(),GetDoc().GetTestPlsPeriod(),STYPE,GetDoc().GetDefineMatrixRange(),1);
	}

	if(!PeekRunState())
		return false;

	return true;
}
#endif
