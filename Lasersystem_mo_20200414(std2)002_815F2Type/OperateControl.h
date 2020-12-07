// OperateControl.h: interface for the COperateControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATECONTROL_H__0CEC0F62_036E_45B4_94B0_A661FD58D4CB__INCLUDED_)
#define AFX_OPERATECONTROL_H__0CEC0F62_036E_45B4_94B0_A661FD58D4CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include "StdAfx.h"	
#include "calc.h"	
#include "Excellon.h"
#include "ControlManipulator.h"

#define SEEKLENGTH	1500
#define FONTRATIO	6/7
//#define LOADREADYTIME	65						//55 20190108	//20190222
#define UNLOADREADYTIME	10
#define DELAYTIMEFORNOBOARD 6000
#define SEARCHSTEP 1000							//20191009 500->1000

enum AXISMODE{BOTHAXIS,LEFTONLY,RIGHTONLY};
//enum LOADANDUNLOADMODE{ONLYASIDENOTTURNOVER,ONLYASIDETURNOVER,ONLYBSIDE,DOUBLESIDE};
enum LOADANDUNLOADMODE{ONLYANOREVERSE,ONLYAREVERSE,AANDBDOUBLE,ONLYB};
enum TARGETMODE{OUTER,INNER,STDLOCAL,SALOCAL,ASSISTANT,FIRSTMARKPOS};

void DoEventAndSleep(unsigned long time=1);					//�ع��ӹ����̣�20161123

#ifdef MEMORYSTATUSMONITOR
typedef struct _MEMORYSTATUSEX {
  DWORD     dwLength;
  DWORD     dwMemoryLoad;
  DWORDLONG ullTotalPhys;
  DWORDLONG ullAvailPhys;
  DWORDLONG ullTotalPageFile;
  DWORDLONG ullAvailPageFile;
  DWORDLONG ullTotalVirtual;
  DWORDLONG ullAvailVirtual;
  DWORDLONG ullAvailExtendedVirtual;
} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;

typedef   void(WINAPI*   FunctionGlobalMemoryStatusEx)(LPMEMORYSTATUSEX);		//��������ԭ��ָ��
#endif

class CControl  
{
#ifdef SMCDMDLL
public:
	BOOL TableAndGalvoTransformNew(int nHead,const SubArea &subarea,XYDataV& xyVL,XYDataV& xyVR,int Aptno);
	BOOL GlvSubAreaProcNew(const SubArea &subarea,XYDataV& xyVL,XYDataV& xyVR,int Aptno);
	BOOL OnDealDataCNew(const SubArea &subarea,XYDataV& xyVL,XYDataV& xyVR,int iToolNo);
#endif

#ifdef ONEAXISDATATRANSFORMTEST
public:														//20200402
	bool OneAxisSubAreaDataTransformAndDrill(int nHead,SubArea &subarea,int Aptno);
	bool OneAxisSubAreaDataTransformAndFind(int nHead,SubArea &subarea,int Aptno);
	bool OneAxisSubAreaDataTransform(int nHead,SubArea &subarea,int Aptno);
	bool OneAxisTableAndGalvoTransform(int nHead,Coord crd);
#endif

#ifdef MEMORYSTATUSMONITOR
public:
	FunctionGlobalMemoryStatusEx GlobalMemoryStatusEx;
private:
	HMODULE m_hModule;
#endif

private:													//20191107
	CString riseReqCode;
	CString downReqCode;

#ifdef HIKAGV
public:
	BOOL SetAGVOutput(CString strTaskTypeCode,CString strStaPositionCode,CString strEndPositionCode,CString& strReqCode);
	int QueryAGVInput(CString strInput);
	BOOL AGVTransport(int status);		//0��AGV�����ϣ�1��AGV�����ϣ�2��AGV�����ϣ�������
#endif

private:													//20191015
	BOOL m_bSADataIsPreLoad;
private:													//20190912
	BOOL m_bSAProcMode;
private:													//20190731
	BOOL m_bUseOldScale;
	Coord GetGlvProcGlvOffset(int type,Coord crd,int nHead);
public:														//20190725
	BOOL WaitUnloadFinish();
	void ResetTableStatus();
	void ResetHandStatus();
	BOOL ThicknessMeasureInCali(int nHead);								
private:
	BOOL PeekHandState();									//20190723
public:
	BOOL BeginLoad(bool bMode);								//20190528
public:
	BOOL QueryTableStatus(int nHead,int caseNo);			//20180830
public:
	BOOL DrillTableAccuracy(int nHead,int iToolNo);			//20180627
	BOOL DrillTableTest(int nHead,int iToolNo);				//20180605

public:
	void ZAxisCCDFocus(int nHead,long thickness,bool bWaitStop=true);
	void ZAxisLensFocus(int nHead,long thickness,bool bWaitStop=true);
//ƽ̨������2DУ��											//20180417
public:	
	long m_lTablePosX,m_lTablePosY;
	void SetTablePosX(long pos);
	void SetTablePosY(long pos);

public:
	HANDLE InitPowerCOM();
	void ReleasePowerCOM();
//�й�������Ԥ����
#ifdef SMCPreLoad
public:
	BOOL PreLoadCreate(bool bIsSubarea,bool bIsRegion,bool bIsPower,int nIndex=0);		//20180619
#endif
//�й��˶�
public:
	long MoveTo(long aptNo);
//У��ʶ��													//20170918
public:
//	BOOL TargetFindInCali(int nHead,int count,HoleCoordV& crdV,CArray<Coord, Coord> &dev,bool isTesting=false);
	BOOL TargetFindInCali(int nHead,int count,HoleCoordV& crdV,CArray<Coord, Coord> &dev,int testType);		//testType:0 �������쳣�㣻1 ����У���㣻2 �ⲣ���߶�λ�㣻3 �ⲣ����У���㣻4 ��ʮ�ֶ�λ�㣻5 ��ʮ�ֲ��Ե�
	BOOL GlovaAutoCalibrate(const Coord3D& crdLaserPos,Coord3D& CCDOffset,int nHead,bool &bTestOk,int ftime,bool isForTest=false);
	BOOL GlovaCalibrateOffset(const Coord3D &crdLaserPos, Coord3D &CCDOffset,int nHead,bool &bTestOk,int ftime);
	BOOL GlovaAccuracyAutoCalibrateTest(const Coord3D& crdLaserPos,Coord3D& CCDOffset,int nHead,bool &bTestOk,int ftime,int times,CString outAccuracyDataPath);

//�ַ��ӹ�													//20170118
public:
	enum PROCTAB{PROCLEFT,PROCRIGHT,PROCBOTH};				//�ɺ����Ƶ��˴�
//	BOOL DrillText(int nHead);
	BOOL DrillText();										//20190124
	BOOL DrillString(const CString& str,const Coord& crd, TextDir td,TextPosition tp,PROCTAB pb);

//ѭ���ӹ���ʱ���											//20161212
public:
	time_t GetCycleStartTime();
	void SetCycleStartTime(time_t time);

//�ع��ӹ����̣�20161123
public:
	double  m_dbAutoScaleLX,m_dbAutoScaleLY,m_dbAutoScaleRX,m_dbAutoScaleRY;	//�Զ�������Ϣ��¼�� 20180905
	double  m_dbScaleLX[2],m_dbScaleLY[2],m_dbScaleRX[2],m_dbScaleRY[2];		//������Ϣ��¼��	//20191219 �����С������!!!
	long m_panelProcessTime;							//����ӹ���ʱ��0����ʵ�ʵ���Чֵ
	BOOL m_bLoadIsReady;								//����׼��ָ����ִ��
	BOOL m_bUnloadIsReady;								//����׼��ָ����ִ��

	void SortFiducial(int count,HoleCoordV& crdV);
	HoleCoordV GetProcFiducialForSix(int index);
	void InfoRecordInProc(int nHead);
	BOOL TableAndGalvoTransform(int nHead,Coord crd);
	int PanelProcessNew(int nHead,int proccount,int Aptno[20],int subproccount,int SubAptno[20]);//����ֵ��-1-->�����˳��ܼӹ����̣�0-->OK��

	BOOL PatternMatch(const Coord& crdTarget,char* strScrName,char* strDestName,int iWidth,int iHeight,int iTimes,float fMinScore,
					double& dbDevX,double& dbDevY,int maxError=0,double dbOutsideThredHold=0.0);
//	BOOL PreTargetFind(int nHead,TARGETMODE tm);
//	BOOL AddFindedTarget(int nHead,Coord crd,TARGETMODE tm,int index);
	void ClearSourceAndTarget(int nHead);
	void AddSource(int nHead,Coord crd);
	void AddTarget(int nHead,Coord crd);
	HoleCoordV GetSource(int nHead);
	HoleCoordV GetTarget(int nHead);
	void InitalTransform();
	int TargetFindInProc(int nHead,int count,HoleCoordV& crdV,TARGETMODE tm,double& dbDevX,double& dbDevY);	//����ֵͬTargetDealInProc(,,,)
	int TargetDealInProc(int nHead,int count,HoleCoordV& crdV,TARGETMODE tm);	//����ֵ��-1-->�����˳��ܼӹ����̣�0-->OK����������ӹ����̣�
																				//1-->continue�����������ӹ����̣������ϰ������ʶ��
	BOOL TableClampOperate(BOOL onoff,BOOL bHasTableClamp=false);
	BOOL TableAdsorbInProc(int nHead);
	BOOL ThicknessMeasureInProc(int nHead,BOOL bUseAlarm=true);
	BOOL CalibrationInProc(int nHead);
	BOOL AutoAdjustPattern(int nHead,bool isForTest=false,bool isOnlyOffset=false);
	BOOL AutoLaserPower(int nHead,int nIndex);
	BOOL AutoFileLaserPower(int nHead,int nIndex);

	int QueryCOMInput(int bitNo,int refresh=0);				//��COM�ڲ�ѯ�����ϵĵ�ǰ״̬
	BOOL SetCOMOutput(int commandNo);						//��COM�ڷ���������Ӧִ�е�����

	BOOL LoadPCBBoardToTable(int nHead,bool bMode);			//bMode��true A��false B��
	BOOL UnLoadPCBBoard(int nHead,bool bMode);				//A����������ʱOK���NG��ͬʱ���У�B����������ʱֻ��OK�壬bMode��true A��false B��
	BOOL UnLoadPCBBoardToNG(int nHead);						//ר�ŵ�NG����������//BOOL bIsAllNG
	BOOL ReLoadPCBBoard();									//

	BOOL LoadPCB(int nHead,bool bMode);						//bMode��true A��false B��
	BOOL UnloadPCB(int nHead,bool bMode);					//bMode��true A��false B��
	BOOL PutPCBToTable(int& mode);							//mode��1 A��0 B��
	BOOL GetPCBFromTable();

	BOOL AutoProcPCB(int nHead);
	BOOL ManuProcPCB(int nHead);
	CString ReadPowerPara(const char *filename);			//��˽�иĳɹ���

	bool IsBoardVacOKNew(int nHead);

private:
	AXISMODE m_axisMode;
	LOADANDUNLOADMODE m_loadAndUnloadMode;
	HoleCoordV m_SourceCrdVL,m_TargetCrdVL,m_SourceCrdVR,m_TargetCrdVR;

public:																			//20160919 ����
	enum PATHMODE{NTYPE,STYPE,RANDOM,NOPPOSITE,SOPPOSITE};
	enum POINTTYPE{ONLYHOLE,CROSS,CIRCLERING,CIRCLEWINDOW,RECTWINDOW,STRING};
	BOOL GetMatrixData(XYDataV& xyV,PATHMODE pm,long lProcRangeBit,int iPointCount=33,bool bPoint9=false);
	BOOL GetSubData(XYDataV& xySubV,POINTTYPE pt,int iToolNo,CString str="",TextDir Dir=HorizontalText);
	void InsertSort(int a[],int count);
	void GetCrossSubData(XYDataV& xySubV);
	void GetCircleRingSubData(XYDataV& xySubV);
	void GetCircleWindowSubData(XYDataV& xySubV,int iToolNo);
	void GetRectWindowSubData(XYDataV& xySubV);
	void GetStringSubData(XYDataV& xySubV,CString str,TextDir Dir);
	Coord* ArrayCoilsNew(int row,int line,Coord *sortPoint);
//	PulsePmr GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number);
//	PulsePmr GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number,bool bFirstPulse=true);				//20181229
	PulsePmr GetPulsePmr(unsigned int energy,unsigned int interval,unsigned long number,bool bFirstPulse=true,bool bPower=false);	//20200515
	BOOL LaserPowerMeasure(int nHead,short posx,short posy,unsigned int energy,unsigned int interval,long time,float *volt) ;
//	BOOL MatrixProcess(int nHead,unsigned int energy,unsigned int interval,PATHMODE pm,long lProcRangeBit,int iPointCount,POINTTYPE pt=ONLYHOLE,int iToolNo=0,bool bPoint9=false);
	BOOL MatrixProcess(int nHead,unsigned int energy,unsigned int interval,PATHMODE pm,long lProcRangeBit,
						int iPointCount,POINTTYPE pt=ONLYHOLE,int iToolNo=0,bool bPoint9=false,bool bFirstPulse=true);		//20181229
	BOOL DrillString(int nHead,const CString& str,TextDir td);
	PulsePmrV GetRegionPmr();
	BOOL DrillRegion(int nHead);
	BOOL IsPoint3(Coord point,long width);
	friend DWORD WINAPI GetPowerData(LPVOID pM);
public:
	bool m_bLeftAxisStatus,m_bRightAxisStatus;		//20160901	
public:	
	CString IsWhatString(double scale);				//20160812
//	enum PROCTAB{PROCLEFT,PROCRIGHT,PROCBOTH};
public:

//	BOOL SMCPrepareLoad(int proccount,int Aptno[20],int subproccount,int SubAptno[20]);//PanelProcess

	BOOL Calc75umControl();//��ʿ������75us  ƴ�ճ�����һ���㷨
	double CalcLinearLevel(int head);

	int  m_MF_nHead;
	int  m_MF_n;
	int  m_MF_type;//ly add 20130225
//	void PauseForManuMarkFid(int nHead,int n,int type);//ly add 20130121
//	void ContForManuMarkFid(bool GetFid,Coord FidPos);//ly add 20130121

	BOOL m_bMatchTheFirstFid;		//���
	BOOL m_bNoBoard;				//�ް�				//20180830
	BOOL m_bOnlyLeftBoard;			//�����
	BOOL m_bOnlyRightBoard;			//���Ұ�

	int cycleno;										//20181203

	void TableClampOn(BOOL onoff);//ly add 20120810
//	void ManuMarkFid(int nHead,int n,int type);//�ֶ������ֶ�λ���λ��ly add 20130121

//	BOOL GetGlassPlaneMarkCoordFitPart(int nHead,const Coord &crdFiducial,double &dbDevPosX,double &dbDevPosY,int n,int times,int delayTime,int isPrecision=0);//jpc add 20130322
//	BOOL PatternMatchTablePart(int useGlass,int delaytime, int nHead, const Coord &crdTarget, int iCaptFocus,char* ScrName, char* strDestName, int iTimes,float fMinScore,int iTop, int iLeft, int iWidth, int iHeight, double &dbDevX, double &dbDevY,double dbOutsideThredHold =0.0);//jpc add 20130322

	BOOL DrillParamFocusTest(int nHead,int iToolNo,double iTsize);//jpc add 20120207
	BOOL DrillParamApertureTest(int nHead,int iToolNo,double iTsize);//jpc add 20120207
//	BOOL DrillParamTableDelayTest(int nHead,int ntime);//time->ntime ly change 20120523

//	BOOL GlovaAutoCalibrateForAccuracyTest(const Coord3D &triCrdProc, Coord3D &triCrdCali,long lHeadNo,bool &bTestOk,int ftime);
//	BOOL GlovaAutoCalibrateForAccuracyTestRandOld(const Coord3D &triCrdProc, Coord3D &triCrdCali,long lHeadNo,CString outAccuracyDataPath);
//	BOOL GlovaAccuracyAutoCalibrateTestOld(const Coord3D &triCrdProc, Coord3D &triCrdCali,long lHeadNo,bool &bTestOk,int ftime,int times,CString outAccuracyDataPath);
//	BOOL GlovaAutoCalibrateForAccuracyTestRand(const Coord3D& crdLaserPos,Coord3D& CCDOffset,int nHead,CString outAccuracyDataPath);

	//int  iContorlSwitch;//��ֹ�ӹ���ʽ�붨λ��ʽ���л�
//	int  iContorlFirstfiduSwitch;//��ֹ�ӹ���ʽ���һ��λ��ʽ���л�
	BOOL iControlThicking;//�ж��Ƿ��Ѿ����׼


	BOOL DrillFocusTest(int nHead,BOOL bTest);
	BOOL DrillApertureTest(int nHead);
	BOOL DrillPrecisionTest(int nHead,int serialNumber=0,BOOL quitTable=TRUE);
//	bool IsBoardVacOK(int nHead);
//	bool CalculateforAFFINE();//ly add 20110802
//	bool PanelProcess(int proccount,int Aptno[20],int subproccount,int SubAptno[20]);
	BOOL GetLaserPower(int nHead,float &power,bool &bTestOk,int nIndex);
	BOOL GetFileLaserPower(int nHead,float &power,bool &bTestOk,int nIndex);//ly add 20130801
//	BOOL AutoLaserPowerTest(int nIndex);
//	BOOL AutoFileLaserPowerTest(int nIndex);//ly add 20130801
//	BOOL AutoAdjustPattern();
	BOOL SetHeadCorParam(int nHead, double nBitX, double nBitY,double dbAngle,double dbScalX,double dbScalY);
	BOOL GlvSubAreaProc(const SubArea &subarea,int Aptno);
	BOOL GlvSubAreaProc(const SubArea &subarea,int Aptno,BOOL bToolCycleMode);
//	BOOL SetCorParam(Coord crd,Coord center,PROCTAB proctab);
//	BOOL SetCorParam(Coord crd,int type,PROCTAB proctab);//ly add 20130603
//	BOOL SetCorParam(Coord crd,Coord Lcenter,Coord Rcenter);//ly add 20130603
//	void InitalCalcAndRectifyData();
//	void CalcAndRectifyData(HoleCoordV ExcData,HoleCoordV RealData,int nHead);
//	void CalcAndRectifyData(HoleCoordV ExcDataExt,HoleCoordV RealDataExt,HoleCoordV ExcDataInn,HoleCoordV RealDataInn,int nHead);
//	void CalcAndRectifyData(HoleCoordV ExcDataExt,HoleCoordV RealDataExt,HoleCoordV ExcDataInn,HoleCoordV RealDataInn,int nHead,Coord &center,int nIndex);
//	Coord GetGlvProcTablePos(Coord crd,int nHead);
//	Coord GetCCDProcTablePos(Coord crd,Coord center,int nHead);
//	Coord GetGlvProcGlvOffset(Coord crd,Coord center,int nHead);

	BOOL DrillRegionTest(int nHead);
	BOOL DrillStringTest(CString string,int nHead);
//	BOOL TestThickness(long thick[2],int nHead);
//	BOOL TestThicknessAL(long thick[2],int nHead);//�������淨
	BOOL TestThicknessAL(long thick[2],int nHead,Coord crd);		//20190725
	//���ɸ������������
//	int  BuildThicknessProg(int nHead,char* szBuf,int iBufSize,char* szLable);//
	BOOL LoadPcb();								//ԭ�е�ʹ��9112ʱʹ�õ�����

//	BOOL OverBoardLoadPCB();
//	BOOL OverBoardNG();

//	BOOL GetAutoFault() const;
//	void SetAutoFault(BOOL bFault);
//	BOOL DealMainFault();
	BOOL DealFault();
	BOOL DealWarner();
//	BOOL PeekAutoRunState() ;
//	BOOL PeekRunState(BOOL onlyOne=0);						//20190604
	long GetBetTwoPos(long posBetOne);

//	BOOL OnDealDataM(const SubArea& subarea,int iToolNo=0);
	enum MATCHMODE{AUTOMATCH,MANUMATCH};
	MATCHMODE GetMatchMode () const;
//	Coord WaitPitchMatchPointEx(long nHead);
	void SetManuPitchPointStatus(BOOL bStatus,int nHead=0);
//	BOOL WaitPitchMatchPoint(long nHead);
	void SetMatchMode(MATCHMODE mm);
	void SetProcedPCBNum(UINT ulNum);
	void SetFiducialMatchStatus(int nHead ,BOOL bStatus);
//	BOOL ManuFiducialPitch(PROCTAB proctab);
	BOOL GetFiducialMatchStatus(int nHead)const;
//	BOOL DrillString(const CString& str,const Coord& crd,int nDir,PROCTAB pb,float StrZoom) const;
//	BOOL DrillString(const CString& str,const Coord& crd, TextDir td,TextPosition tp,PROCTAB pb,float StrZoom);
//	BOOL DrillRegion(const Coord& crdPos,int nHead);
	BOOL DrillRegion(const Coord& crdPos,PROCTAB pb);
//	int DrillOneHole(const Coord& crdPos,int nHead,int iToolNo);//ly add 20110913
//	BOOL DrillScanLabRegion(int nHead) const;
	enum PROCMODE{MANUPROC,AUTOPROC,SELEPROC};
	long TableCompensate(int nAxis, long lDestPos, long lCurPos) const;

	BOOL LaserComRelease();
	Coord GetTablePos()const;
	void SetCCDLuminance(UINT ulData,UINT ulChan);
	void SetCCDCaxLuminance(UINT ulData,UINT ulChan);
	void SetCCDInFrared(UINT ulData, UINT ulChan);
	long GetPos(U32 ulAxisNo)const;
//	BOOL SetCorParam(PROCTAB proctab,int nSub);
//	Coord CorrectCenterCrd(const Coord& crd,const Coord& crdDest,long lWidth,long lHeight,double dbSX1,double dbSX2,double dbSy1,double dbSy2,double dbAngle);
//	BOOL TestCCDDistance(const Coord3D &triLaserPos, const Coord3D& triCCDLOffset,Coord& crdDistance,long lFocusCCDR);
//	BOOL ProcSelectBlock(int nHead=0);

//	BOOL GlovaAutoCalibrate(const Coord3D& triCrdProc,Coord3D& triCrdCali,long lHeadNo,bool &bTestOk);  //2010 0224
//	BOOL GlovaAutoCalibrateOld(const Coord3D& triCrdProc,Coord3D& triCrdCali,long lHeadNo,bool &bTestOk,int ftime);
	//yutingxun 7-18 END  CHANGGE RUN
	enum RUNSTATUS{RUN=1,PAUSE,CONT,END,MANU,OPERATE,OPERATEPAUSE,OPERATEWITHHAND,OPERATEWITHHANDPAUSE};		//20190604	//20190722	//20190723
	enum LOADERSTATUS{LPICKS=1,LPICKDOWN,LBEVACCUM,LPICKUP,LENDLOAD,LPICKSP,LHD1DOWN,LBEVACCUMH2,LHD1UP,LMOVETOA,LHD1DOWN2,LHD1UP2,LMOVETOL,LENDPITCH};	
	enum UNLOADERSTATUS{PICKDOWN=1,BEVACCUM,PICKUP,MOVETOU,PICKDOWNP,PICKUPP,ENDUNLOAD,PITCHUP,MOVETOA,HD2DOWN,HD2VACCUM,HD2UP,MOVETOUNL,HD2DOWN2,HD2UP2,PITCHS,ENDPITCH};
	enum LAMPSTATUS{ORDER=0,ERR,WARN};

//	BOOL GlovaCalibrateOffset(const Coord3D& crdLaserPos,Coord3D& triOffset,int Headno=0);
//	BOOL GlovaCalibrateOffset(const Coord3D &crdLaserPos, Coord3D &CCDOffset,int nHead,bool &bTestOk); //2010 0224

//	void TestPCBThickness( CRD& HightL,CRD& HightR,const CRD& ZPos,const Coord& TestPos,int HeadNo=0);
	long HomeAll();
	void SetRunState(RUNSTATUS rs);
	void SetLampStatus(LAMPSTATUS lamp);//const
	int  GetLampStatus()const;
	long GetRunState()const;
	BOOL LaserWarmup(int Time);
	long MoveTo(const Coord &crd);
//	BOOL WaitAxisStop2(U32 ulAxis,int times=32) const;//ly add 20130409
	BOOL WaitAxisStop(U32 ulAxis) const;
	long MoveTo(U32 ulAxis, long pos );

	long HomeAPT();//�����Ȧ 20150911
    long HomeBET();//����BET 20150911
//	long MoveToAPTAndBET(long moveAperture,long setShowAperture)const;

//	void HaltExcuitionProgram(int nRange, int nInCard)const;
	BOOL ChannelOutput(U32 ulData,char bState)const;

//  BOOL ChannelOutputOverBoard(int ioPinNumber=1000)const;
//	int QueryIOBitOverBoard(int queryCOMIO=0) const;

//	BOOL AutoProcWholePCB();
//	BOOL ManuProcWholePCB();
//	BOOL AutoProcOnePCB(int nHead);//ly add 20140114
//	BOOL TheBoardOnTable(int nHead,int repeattype=0);//ly add 20140114 ƽ̨���а�����0left1right2both3..��  repeattype�Ƿ񵯳����ԶԻ���=0ѭ�����α���=1�����Ի���ѯ��
	BOOL GetLaserPowerTest(int nHead,long time,float &power,int nIndex=0);
	BOOL DrillMatrix(int nSize,int nType,int nHead);
	BOOL DrillParamTest(int nHead,int iToolNo,double iTsize=0.0);

//	BOOL CycleDrillMatrix(int nSize,int nType,int nHead);
//	BOOL MarkBarCode(CString binstr,int nType,int nHead);
	BOOL ReleaseControl();
	BOOL InitalControl();
	int QueryIOBit(U32 Data,int queryCOMIO=0)const;//jpc change 20130912
	int QureyIOBit2(U32 Data)const;
	BOOL GetDoorWarning(int isCheck=1);//ly add 20140418
//	BOOL Input(U32 *Data,U32);
//	BOOL Output(U32 lData);
	BOOL LaserComInital();
//	BOOL FindFiducialRealPos(int nHead,const Coord& crdFiducial,long lMatchTimes,double &RealPosX,double &RealPosY);

	long GetCurDrillSubAreaNo() const;

//	BOOL LoadBothPcb()	const;
//	BOOL LoadPcbOnlyRight()const;

//	BOOL LoadPcbFormDepot();
//	BOOL UnloadPitchPcb() const;
	BOOL UnloadPcb();						//ԭ�е�ʹ��9112ʱʹ�õ�����
	void UnloadPcbAndNG();					//ԭ�е�ʹ��9112ʱʹ�õ�����
//	BOOL UnloadPcbOverBorad();
//	BOOL UnloadWaitForPcb();

	void EndProc(const Coord& crd,bool bXYMove=true);
	
	void ResetProcStatus();
//yutingxun 06-9
	BOOL LightTurnOn(UINT LayerSel);
	BOOL LightTurnOff();
    //2010-9-20
//	BOOL CheckHole(BOOL& bCheckOK);
//	BOOL GlovaOffsetCheck(const Coord3D &crdLaserPos, Coord3D CCDOffset,int nHead,bool &bTestOk,int ftime);
//	BOOL MainFiducialCheck(BOOL& bCheckOK);
//	BOOL AutoMachPreHot(int nLoopFlag=0);//����Ԥ��
	//�򿪴���,�����ò�����,ֹͣλ,��Чλ8,��У��λ
//	HANDLE OpenCOM(LPCTSTR lpCOMName,DWORD dwBaudRate,BYTE byteStopbit=ONESTOPBIT);
	//�رմ���
//	void   CloseCOM(HANDLE hCom);
	//Write to com,return writen number; 0:faile
//	DWORD  WriteDataToCom(HANDLE hCom,LPCVOID lpBuffer,DWORD dwNumberToWrite);
	//read data,return readed number,0:faile
//    DWORD  ReadDataFromCom(HANDLE hCom,LPVOID lpBuffer,DWORD dwNumberToRead);
	//analysic buf ,return number value
//	int  GetValueFromBuf(char* buf,int iSize);
//------------------------------------------------------||
	//��������������ھ��ֵ
//	void SetCntComHandle(HANDLE hVal);
	//��ȡ����������ھ��ֵ
//	HANDLE GetCntComHandle();
	//��ȡ��֮ǰ�������������
//	DWORD  GetBasePlusCount();
	//��ʼ��֮ǰ,��¼��ǰ�����������
//	void   SetBasePlusCount(DWORD dwBaseCnt);
	//��ʼ��֮ǰ����¼�����������,���ڲ���
	//BOOL   MarkBasePlusCount(int iResv1=0);
	//�ж��Ƿ���Ҫ����,���ڲ���
	//BOOL   CheckOverPlusCount(int iUnitPlusCnt);
	//�������subareaҪ����ܷ���
//	int    CalcUnitCommandPlusCount(const SubArea& subarea,int Aptno);
//	int    CalcUnitCommandPlusCount(const SubArea& subarea,int Aptno,BOOL bToolCycleMode);
	//���ӹ��������Ƿ��㹻,iResvUnit(������)-��Ϊ�˼�¼������־,���ڲ���
	//BOOL   CheckProcPlusCount(int iCommandCount,int iResvUnit=0);
	//��ȡ��ǰ����
//	BOOL   GetCurPlusCounter(DWORD& dwGetCnt);
	//��λ������
//	BOOL   ResetPlusCounter();
//	BOOL   OpenDebugFile();
//	BOOL   CloseDebugFile();
//	BOOL   WriteToDebugFile(char* buf,int iSize);
//------------------------------------------------------||
	BOOL	TunePos();
	BOOL    TunePosIm();

	void SetHandPause(BOOL stop);//ly add 20110815 ���������ϵ�״̬�л�

	virtual ~CControl();
protected:
	BOOL OnDealDataC(const SubArea& subarea,int iToolNo=0);    //chao 5.29
	BOOL OnDealDataC(const SubArea &subarea, int iToolNo,BOOL bToolCycleMode);
//	BOOL OnDealDataB(const SubArea& subarea,int iToolNo=0);
//	BOOL OnDealDataB2(const SubArea &subarea, int iToolNo=0);

//	BOOL WaitShutterOn(int nHead,BOOL bStatus);
	long AxisCompensate(int Axis, long lDestPos,long lCurPos) const;
//	BOOL ShutterOn(int nHead,BOOL bOn=TRUE);
//	BOOL PreAutoProcPCB(BOOL bTestThinkness);
//	void CalcAndRectifyData(PROCTAB procta);   //���� У�� ����

	CControl();
	friend CControl& GetControl();
	BOOL PeekRunState();

//	BOOL QueryProgramState(int nRange, int nInCard) const;

	
private:
	double m_PauseTimeInSec;								//20190612	����
	//��Ҫ��������̨��ʿ����ÿһ�Ű��ʵ��������Ҫ��¼����־�� 20150418
	double scaleLXInfo,scaleLYInfo,scaleRXInfo,scaleRYInfo;

	LAMPSTATUS m_LampStatus;

	HANDLE m_hCntCOM;//��������ô���
	DWORD  m_dwBasePlusCnt;//�����������
	DWORD  m_dwCommandPlusCnt;//Ӧ����ܷ���
	FILE* m_fpCnt;
	DWORD	m_dwActTotalPlusCnt;//ʵ�ʴ����������
	DWORD	m_dwCmmTotalPlusCnt;//����Ӧ�����������
//	BOOL bFaultRun;
	BOOL m_bOnlyOne;
	BOOL IsPassCrd( Coord* TempCrd,int const Cordsize);
	
//	CString ReadPowerPara(const char *filename);
//	BOOL DrillTextInfo(PROCTAB pb=PROCBOTH);  
//	BOOL DrillTextInfo();  
//	BOOL DrillFiducial(int nHead);
	BOOL DrillFiducial();											//20190124

//	BOOL SetHeadCorParam(int nHead, double nBitX, double nBitY,double dbAngle,double dbScalX,double dbScalY);

//	void CalculateProcFiduData(int nHead);
//	void CalculateProcGlvOffset(PROCTAB proctab);
//	BOOL MonitorProgramStatus(int nThreadNo, int nCardNo,int nMonitime,const CString& str);
//	BOOL PatternMatchCircle(int nHead,const Coord& crdTarget,int iCaptFocus, char* pSrcName, char* pDestName,int iTimes, float fMinScore,
//		              int iTop, int iLeft, int iWidth, int iHeight, double& dbDevX, double& dbDevY);
	long	m_lCurDrillSubAreaNo;
	long	m_lCurDrillHoleNo;//ly add 20110905

	long    m_Firstposx;
	long    m_Firstposy;

	BOOL	m_handfail;//ly use 20110816
	BOOL	m_handPauseL;//ly add 20110815
	BOOL	m_handPauseUnL;//ly add 20110815
	BOOL    m_bPitchPcbToProc;
	long    m_lLoadLeft;   // =0,���һ����ʱ���û�а壻=1ȡ�ڶ��Ű�ʱ�ŷ���û�а壬=>2�ϲ��й���İ�

	BOOL    m_bToManuPitchPointR;
	BOOL    m_bToManuPitchPointL;
//-------------------------------------------
	Coord	m_crdRealOffsetL;
	Coord	m_crdRealOffsetR; 

	Coord	m_crdGlvMidPos;

	double  m_dbScaleLX2, m_dbScaleLY2,m_dbScaleRX2, m_dbScaleRY2;		//���ű���
	double  m_dbScaleLX1, m_dbScaleLY1,m_dbScaleRX1, m_dbScaleRY1;		//���ű���
	double  m_dbAngleL,  m_dbAngleR;									//��ת�Ƕ�

	BOOL    m_bAbsorbedPCBLT;
	BOOL    m_bAbsorbedPCBRT;

	BOOL	m_bFoundFiducialPCB1;
	BOOL	m_bFoundFiducialPCB2;

	BOOL	m_bFoundLocalMarkPCB1;
	BOOL	m_bFoundLocalMarkPCB2;

	BOOL	m_bEnableProcPCB1;
	BOOL	m_bEnableProcPCB2;
//-------------------------------------------
	double  m_dbCAngleL, m_dbCAngleR;   //���̽Ƕ�

    UINT    m_uProcedPCBNum;
	time_t   m_StartTime,m_EndTime;
	
	Coord   m_crdFidRealOffset;

	RUNSTATUS m_rsCurRunState;	      //  RUN / PAUSE / END
	PROCTAB   m_ptCurProcTab;         
    MATCHMODE m_MatchMode;
    float m_OldpostBetOne;
    float m_OldpostBetTwo;
    BOOL	m_bCalibrate;
	long TestTotolTime;
   
	BOOL m_InnerMatch;//�ж��Ƿ���ƥ���ڲ��У����ڲ������ֵΪ1��cog��ʹ�ø����ӵ�ƥ���㷨��

private:
	CString m_LIncreasingStr,m_RIncreasingStr;
	BOOL isUseTimeLoadOpt;//��ʱ���Ż����ܣ���һ�����β����ܣ�����ΪFalse,��������ʱ���ΪTrue
	BOOL isControlLoadCommand,isControlUdLoadCommand;
	double m_processAllTime;

	Coord leftFiducialMoveCrd,rightFiducialMoveCrd;
	double distanceDentreDiagonal02,distanceDentreDiagonal13;
};

#endif // !defined(AFX_OPERATECONTROL_H__0CEC0F62_036E_45B4_94B0_A661FD58D4CB__INCLUDED_)





















