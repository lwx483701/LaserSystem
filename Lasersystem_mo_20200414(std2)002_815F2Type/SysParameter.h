// SysParameter.h: interface for the SysParameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSPARAMETER_H__A4EE69C3_0646_4077_9A2B_F65410B72EC7__INCLUDED_)
#define AFX_SYSPARAMETER_H__A4EE69C3_0646_4077_9A2B_F65410B72EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NULL 0
#include <windows.h>

#include "stdafx.h"
#include "ToolParameter.h"
#include "Excellon.h"

#include "hasp_api.h"			//SENTINAL
//#include "hasp_vcode.h"       /* contains HASP DEMOMA vendor code */

//#include "ClientSocket.h"

#include <afxtempl.h>
typedef CArray<int, int &> CArrayGetPrecisionSelect;

//Motion 
struct MotionSpeed
{
	long	lStart;
	long	lMax;
	long	lAcc;
	long	lDec;
	long	lAccRate;
	long	lDecRate;

	MotionSpeed(long start = 1000, long max = 10000, long acc = 20, long dec = 20, 
		long accrate = 10, long decrate = 10)
		: lStart(start), lMax(max), lAcc(acc), lDec(dec), lAccRate(accrate), lDecRate(decrate)
	{}

	MotionSpeed& operator=(const MotionSpeed& rht)
	{
		this->lStart = rht.lStart;
		this->lMax	 = rht.lMax;
		this->lAcc   = rht.lAcc;
		this->lDec   = rht.lDec;
		this->lAccRate = rht.lAccRate;
		this->lDecRate = rht.lDecRate;
		return *this;
	}
};

struct PosErr
{
	long nPos;
	double dbErr;
	PosErr(long nP=0,double dbE=0):nPos(nP),dbErr(dbE){}
};
typedef std::vector<PosErr>       PositionErrV;

struct AxisPosErr
{
	long nInterval;
	long MaxRange;
	long nCounters;
	long nStart;//add ly  20110310
	long nEnd;//ly add 20110310
	PositionErrV  PositionErr;
    AxisPosErr()
	{
		nInterval =50000;
	}
};

struct UserInfo
{
    int     nLevel;
	CString strUserName;
	CString strPassword;
	CString dept_id;			//部門/課別
	CString shift_id;			//班別（白班/晚班）	

	UserInfo(int nlev=2,const CString& strname="",const CString& strpassword="",const CString& dept = "",const CString& shift = "")
	{  
	     this->nLevel = nlev;
		 this->strUserName = strname;
		 this->strPassword = strpassword;
		 this->dept_id = dept;
		 this->shift_id = shift;
	}
};

struct ScaleSet						//20160812
{
    double dbDownLimit;
	double dbUpLimit;
	CString strChar;
};

struct IngredientExplainSet						
{
	CString strLabel;
	CString strExplain;
};

//键值对
struct  KEYVALUEINFO
{
	string keyName;
	string keyValue;
	string timeStamp;

	KEYVALUEINFO()
	{
		keyName = keyValue = timeStamp ="";
	}
};

typedef std::vector<ScaleSet> ScaleSetV;
typedef std::vector<IngredientExplainSet> IngredientExplainSetV;

typedef std::vector<UserToolPara> ToolModel;
typedef std::vector<LayerToolParaSet> ToolModelSet;
typedef std::vector<SubArea> SubareaV;
typedef std::vector<UserInfo> UserInfoV;

class SystemDoc
{
private:													//20200515
	long m_laserComp1,m_laserComp2;
public:
	long GetLaserComp1();
	long GetLaserComp2();

private:													//20191219
	long m_iLAndULSystem;
	long m_iUnloadIsOK;
	long m_iTableAbsorbFirst;
	long m_iCustomerSpecial;
	long m_iMINlaserPeriod;
public:
	long GetLAndULSystem();
	long GetUnloadIsOK();
	long GetTableAbsorbFirst();
	long GetCustomerSpecial();
	long GetMINlaserPeriod();

private:													//20191107
	BOOL m_bPCBBoardIsReady;

	CString m_strSysRCSIP;					//海康RCSIP
	CString m_strSysRCSPort;				//海康RCSPort
	CString m_strSysTaskTypeRise;			//上料任务类型编号
	CString m_strSysTaskTypeDown;			//下料任务类型编号
	CString m_strSysRiseStaPositionCode;	//上料区起点位置编号
	CString m_strSysRiseEndPositionCode;	//上料区终点位置编号
	CString m_strSysDownStaPositionCode;	//下料区起点位置编号
	CString m_strSysDownEndPositionCode;	//下料区终点位置编号
public:
	BOOL GetPCBBoardIsReady();
	void SetPCBBoardIsReady(BOOL bir);

	CString GetSysRCSIP();
	CString GetSysRCSPort();
	CString GetSysTaskTypeRise();
	CString GetSysTaskTypeDown();
	CString GetSysRiseStaPositionCode();
	CString GetSysRiseEndPositionCode();
	CString GetSysDownStaPositionCode();
	CString GetSysDownEndPositionCode();

	BOOL LoadPartnerParam();
private:													//20191015
	int m_iProcAxisSelected;
public:
	int GetProcAxisSelected();
	void SetProcAxisSelected(int pas);
private:													//20190711
	BOOL m_bAutoGalvoAdjustIsTimed;
	BOOL m_bAutoLaserTestIsTimed;
public:
	BOOL GetAutoGalvoAdjustIsTimed();
	void SetAutoGalvoAdjustIsTimed(BOOL aga);
	BOOL GetAutoLaserTestIsTimed();
	void SetAutoLaserTestIsTimed(BOOL alt);
//Z轴行程保护												//20180912
private:
	long m_lFORWARDZ;
public:
	long GetFORWARDZ();
//加工时台面真空监测用										//20180821
private:
	BOOL m_bAxisIsRun[2];									
public:
	BOOL GetAxisIsRun(int nHead);
	void SetAxisIsRun(int nHead,BOOL air);
//蚊香式开窗												//20170224
private:
	BOOL m_bDrillCoil;
public:
	BOOL GetDrillCoil();
	void SetDrillCoil(BOOL dc);

//平台玻璃尺2D校正											//20180417
private:
	BOOL m_bTableIsCali;
	BOOL m_bTable00IsCali;
	BOOL m_bTable01IsCali;
public:
	BOOL LoadTableCorParam();
	BOOL GetTableIsCali();
	void SetTableIsCali(int nHead,int label,BOOL tic);

private:
	long m_lGlvCaliOffsetTol;			//振镜原点校正前后值差异阈值
	long m_lTestThicknessZSafePos;
	long m_lTestThicknessCompensation[2];

private:													//20180301
	Coord m_crdLBRefPoint; 
public:
	Coord GetLBRefPoint();
	void SetLBRefPoint(Coord crd);
//登录信息保存至加密狗中									//20180126
public:
	BOOL SaveUserInfoInSentinal();
	BOOL LoadUserInfoInSentinal();
//有关时间控制加密狗	//SENTINAL
public:
	BOOL InitSentinal();									//20180126
	BOOL ReleaseSentinal();
	BOOL TimeController(hasp_time_t& timeForUse);
private:
	hasp_handle_t m_timeHandle;
//文件优化状态												//20180116
private:
	BOOL m_bFileIsOptimized;
public:
	BOOL GetFileIsOptimized();
	void SetFileIsOptimized(BOOL fio);
//AVT相机													//20170829
private:
	CString m_strCameraSNHigh[2];
	CString m_strCameraSNLow[2];
public:
	unsigned long GetCameraSNHigh(int index);
	unsigned long GetCameraSNLow(int index);

//重构加工流程：20161123
private:
	Coord m_crdFirstMarkA,m_crdFirstMarkB;					//第一标靶的文件坐标
	BOOL m_bASideIsDisplay;
	BOOL m_bASideIsProcessing;
	int m_iFlowPathMode;
	int m_iProcAxisMode;
public:
	Coord GetFirstMarkPos(BOOL bSide);
	void SetFirstMarkPos(Coord crd,BOOL bSide);
	BOOL GetASideIsDisplay();
	void SetASideIsDisplay(BOOL asid);
	BOOL GetASideIsProcessing();
	void SetASideIsProcessing(BOOL asip);
	int GetFlowPathMode();
	void SetFlowPathMode(int fpm);
	int GetProcAxisMode();
	void SetProcAxisMode(int pam);

//循环加工用时监控											//20161212
private:
	long m_iProcTime;
public:
	long GetProcTime();
	void SetProcTime(long pt);
/////////////////////////////////////////////////////////////////////
private:							//20161109
	int m_iDisplayColCount;
	int m_iDisplayRowCount;
	BOOL m_bExcellonData0IsUp;
	BOOL m_bDoubleFileData;
public:
	int GetDisplayColCount();
	int GetDisplayRowCount();
	BOOL GetExcellonData0IsUp();
	BOOL GetIsDoubleFileData();
	void SetIsDoubleFileData(BOOL idfd);
/////////////////////////////////////////////////////////////////////
private:							//20160919
	int m_iHdSysDeadTime;
	int m_iHdSysLaserTriggerAdjust;
	int m_iHdSysPulseMode;
	int m_iHdSysAOMOnDelay;
	int m_iHdSysAOMOffAhead;
	float m_fHdSysLaserMAXDutyCycle;
public:
	int GetHdSysDeadTime();
	void SetHdSysDeadTime(int hsdt);
	int GetHdSysLaserTriggerAdjust();
	void SetHdSysLaserTriggerAdjust(int hslta);
	int GetHdSysPulseMode();
	void SetHdSysPulseMode(int hspm);
	int GetHdSysAOMOnDelay();
	void SetHdSysAOMOnDelay(int hsaod);
	int GetHdSysAOMOffAhead();
	void SetHdSysAOMOffAhead(int hsaoa);
	float GetHdSysLaserMAXDutyCycle();
	void SetHdSysLaserMAXDutyCycle(float hslmdc);
/////////////////////////////////////////////////////////////////////
private:							//20160901
	int m_iSysInfoDBMode;			//信息输入与输出标志	0:标准(现有日志形式) 1：无锡深南需求 2：方正需求
	CString m_strSysProcFileName;	//输入的程式名
	CString m_strSysProcLOTID;		//输入的工单号(LOTID号)
	CString m_strSysProcPRODID;		//输入的料号（PRODID）
	CString m_strSysUserDEPTID;		//输入的员工课别(DEPTID号)
	UINT m_ulSysSNProcedPCBNum;		//自动加工方式下总的加工板数
	UINT m_ulSysPCBCount;			//输入的待加工板数						//20180118
	LONG	m_SysCompanyCode;		//厂商编号
	CString m_strSysMachineSn;		//设备编号
	CString m_strSysImesURL;		//Imes URL
	long	m_strSysTimeout;		//Imes超时时间
	long	m_strSysIdtTime;		//IDT Delay时间
	LONG	m_SysModeSwitch;		//模式开关
	LONG	m_SysUserControlSwitch;	//人员资质管控开关
	CString	m_strSysHeartbeatContent;	//心跳内容
	CString	m_strSysHeartbeatFreq;		//心跳频率
public:
	int GetSysInfoDBMode();
	void SetSysInfoDBMode(int sidm);
	CString GetSysProcFileName();		//钻孔程序
	void SetSysProcFileName(CString spfn);
	CString GetSysProcLOTID();			//工单号
	void SetSysProcLOTID(CString spli);
	CString GetSysProcPRODID();			//料号
	void SetSysProcPRODID(CString prod);
	CString GetSysUserDEPTID();			//员工课别
	void SetSysUserDEPTID(CString dept);
	UINT GetSysPCBCount();				//待加工数量
	void SetSysPCBCount(UINT ulNum);
	UINT GetSysSNProcedPCBNum();		
	void SetSysSNProcedPCBNum(UINT ulNum);
	CString GetSysMachineSn();
	void SetSysMachineSn(CString macSn);
	CString GetSysImesURL();
	void SetSysImesURL(CString url);
	long GetSysTimeout();
	void SetSysTimeout(long timeOut);
	long GetSysIdtTime();
	void SetSysIdtTime(long idtTime);
	CString GetSysInMaterialCode();
	void SetSysInMaterialCode(CString inCode);
	CString GetSysOutMaterialCode();
	void SetSysOutMaterialCode(CString outCode);
	BOOL GetSysModeSwitch();
	void SetSysModeSwitch(long modeSwit);
	BOOL GetSysNeedUpload();
	void SetSysNeedUpload(long needUpload);
	BOOL GetSysUserControlSwitch();
	void SetSysUserControlSwitch(long userSwit);
	CString GetSysHeartbeatContent();
	void SetSysHeartbeatContent(CString content);
	CString GetSysHeartbeatFreq();
	void SetSysHeartbeatFreq(CString freq);
	long GetCompanyCode();
	
	
/////////////////////////////////////////////////////////////////////
private:							//20160812
	ScaleSetV m_SysScaleSet;
	IngredientExplainSetV m_SysIngredientExplainSetV;
public:	
	void AddSysScaleSet(ScaleSet ss);
	void AddSysIngredientExplainSet(IngredientExplainSet is);
	void DeleteSysScaleSet(int index);
//	ScaleSet GetSysScaleSet(int index);
	std::vector<ScaleSet>::iterator GetSysScaleSet(int index);
	std::vector<IngredientExplainSet>::iterator GetSysIngredientExplainSet(int index);
	int GetSysScaleSetSize();
	int GetSysIngredientExplainSetSize();
/////////////////////////////////////////////////////////////////////
public:	//20160809
	typedef CArray<Coord, Coord &> CArrayBigHoleCPoint;
	CArrayBigHoleCPoint arrayBigHoleCPoint[20];

	BOOL GetSysCircleProcMode();
    void SetSysCircleProcMode(BOOL scpm);
	long GetSysBeamDia();
	void SetSysBeamDia(long sbd);
	long GetSysBeamStep();
	void SetSysBeamStep(long sbs);
	long GetToolDiameter(int nIndex);
private:
	BOOL m_bSysCircleProcMode;
	long m_lSysBeamDia;
	long m_lSysBeamStep;
/////////////////////////////////////////////////////////////////////

public:
	typedef std::vector<URECT> MotionPathV;
//激光器报警
	BOOL GetLaserWarning();
    void SetLaserWarning(BOOL laserWarning);
	BOOL SaveConfig(int saveNumber);
	int LoadConfig();
	void ReadLaserConfig();

	void SetLoadSubNo(int SubNo);//ly add 20120426
	int  GetLoadSubNo();//ly add 20120426
	void SetUnLoadSubNo(int SubNo);//ly add 20120426
	int  GetUnLoadSubNo();//ly add 20120426

	int  GetPrecisionRowCount();
	void SetPrecisionRowCount(int countRow);
	int  GetPrecisionLineCount();
	void SetPrecisionLineCount(int countLine);
	int  GetPrecisionStepCount();
	void SetPrecisionStepCount(int step);
	int  GetPrecisionMoveCount();
	void SetPrecisionMoveCount(int move);

	CArrayGetPrecisionSelect m_CArrayGetPrecisionSelect;

	BOOL GetAutoCalibrateFieldPosOffsetForAccuracyTest(long SLBitPerMM,Coord &ReturnPos, int nHead,int accuracyTestType);//jpc add 20130304
	void AccuracyTestChangeRow(int nHead);
	long m_PatternXTimes[2];
	long m_PatternYTimes[2];//jpc add 20130304----

	void SetDefineMatrixRange(long temp);
	long  GetDefineMatrixRange();
	int  GetScanlabDeadTime();

	void SetSecondReverse(BOOL isSecondReverse=FALSE);
    BOOL GetSecondReverse();

private:
	BOOL m_IsEndLoadUnloade; //为了避免机械手发生碰撞，增加标志位
    BOOL m_isSecondReverse;
	long m_DefineMatrixRange;
	int m_iScanlabDeadTime;
	int PrecisionCountRow;
	int PrecisionCountLine;
	int PrecisionCountStep;
	int PrecisionCountMove;
	long m_CurPosX;
	long m_CurPosY;

	BOOL m_bLaserSocetCheck;
	BOOL  m_bInitLaserSocet;
	BOOL m_bLaserWarning;
	BOOL m_bIsLaserReceive;

//	CClientSocket m_ClientSocket;

public:
	BOOL GetCongexErrorPoint();	//Cognex 中间出现异常的时候，增加的提示报警，暂时没有从根本上解决掉这个问题
	void SetCongexErrorPoint(BOOL congexErrorPoint=FALSE);
	int GetCountCongexError();	
	void AddCongexError();	
	void SetCountCongexError(int conutCongexError);

	//时间分析器计时
    BOOL GetTimeAnalyse();
	void SetTimeAnalyse(BOOL isTimeAnalyse);	
	COleDateTime GetBeginTimeAnalyse();
	void SetBeginTimeAnalyse(COleDateTime bigenTime);
    DWORD GetCalculateBeginTime();
	void SetCalculateBeginTime(DWORD calculateBeginTime);

	int GetIsOverBroad();
	void SetIsOverBroad(int isOverBroad=0);	
	int  GetProcessModeToFile();
	void SetProcessModeToFile(int isProcessModeToFile=0);
	void SetFunctionOverBorad(int temp=0);	
	BOOL GetFunctionOverBorad();

	long GetPos(long ulAxisNo) const;//ly add 20110928
	void SetPos(long ulAxisNo,long fPos);//ly add 20110928
	BOOL GetFaultRun();
	void SetFaultRun(BOOL fr);
	int  GetLastWarningNo();
	int  GetLastAlarmId();
	void SetLastWarningNo(int wNo);
	void SetLastAlarmId(int alarmid);
	void SetLastWarningNoUM(int wNo);

	BOOL GetEnAutoAdjust();
	void SetEnAutoAdjust(BOOL enable);
	BOOL GetEnAutoPower();
	void SetEnAutoPower(BOOL enable);
	void SetCTIHWWarning(BOOL enable);//ly add 20130708
	BOOL GetCTIHWWarning();// ly add 20130708
	BOOL GetEnFidRetry();//ly add 20120202
	void SetEnFidRetry(BOOL enable);//ly add 20120202
	int  GetNGSum();//ly add 20121127
	void SetNGSum(int sum);//ly add 20121127
	int  GetNGThred();//ly add 20121127
	void SetNGThred(int thred);//ly add 20121127

	BOOL GetAutoAdjustPattern(int index);
	void SetAutoAdjustPattern(BOOL aap,int index);
	BOOL GetAutoLaserPowerTest(int index);
	void SetAutoLaserPowerTest(BOOL alpt,int index);

	BOOL GetToolCycleMode();
	void SetToolCycleMode(BOOL tcm);
	Coord GetPathOffset(long lHeadNo)  const;
	BOOL GetEnFiducial(int index);
	void SetEnFiducial(BOOL enable,int index);
	long GetCurAptNo();
	void SetCurAptNo(long aptno);
	long GetAutoThickError();
	void SetAutoThickError(long error);
	//int GetLotIDMode();//ly delete 20121127
	//void SetLotIDMode(int nMode);//ly delete 20121127
	void SetGlvAdjustThreshold(long threshold);
	long GetGlvAdjustThreshold();
	long GetDistanceCenterThreshold();// 对角线中心点距离计算，标靶一个阈值管控
	void SetDistanceCenterThreshold(long iDistanceCenterThreshold);
	void SetPCBScaleThreshold(double threshold);
	double GetPCBScaleThreshold();
	void SetPCBScaleThrd(long threshold);//ly add 20120919
	long GetPCBScaleThrd();//ly add 20120919
	void SetLaserPowerTestSt(double power);
	double GetLaserPowerTestSt();
	void SetLaserPowerTestMax(double power);//ly add 20120924
	double GetLaserPowerTestMax();//ly add 20120924
	BOOL GetFault();
	void SetFault(BOOL bFault);
	void SetWarner(BOOL BWarner);
	BOOL GetWarner();
	double GetTextHeigth();
	void SetTextHeigth(double heigth);
	CString GetTextTest();
	void SetTextTest(CString string);
	long GetBETPriOffset();
	void SetBETPriOffset(long offset);
	long GetRegionDim();
	void SetRegionDim(long iRegionDim);
	long GetTestBoardThickness();
	void SetTestBoardThickness(long nThickness);
	BOOL GetThickingType();
	void SetThickingType(BOOL bType);
	long GetThicknessY();
	void SetThicknessY(long lThicknessY);
	long GetThicknessX();
	void SetThicknessX(long lThicknessX);
	long GetThicknessZero(int nHead);
	void SetThicknessZero(long lThick,int nHead);
	long GetPatternTimes(int nHead);
	void SetPatternTimes(int nHead,long lTimes);
	long GetOrgTimes(int nHead);
	void SetOrgTimes(int nHead,long lTimes);
	long GetGalvoBoardThick() const;
	void SetGalvoBoardThick(long lThick);
	long GetCCDBoardThick() const;
	void SetCCDBoardThick(long lThick);
	BOOL GetAutoCalibrateOrgPosOffset(Coord &ReturnPos,int nHead);
	BOOL GetAutoCalibrateFieldPosOffset(Coord &ReturnPos,int nHead);
	BOOL ReadCaliTimes();
	BOOL WriteCaliTimes();

//设置工艺类型，激光长路径还是短路径
	void SetTechnicType(bool ultype);
    bool GetTechnicType() const;
//激光能量测试时间段   yutingxun 06-8-23
	void SetLaserTestTime(long ulTime);
	long GetLaserTestTime() const;
//振动校正测试时间段   yutingxun 06-8-23
	void SetAdjTime(UINT ulTime);
    long GetAdjTime() const;

//设备稼动率上传时间早晚班
	void SetOperationRateTime(CString ulTime);
	CString GetOperationRateTime() const;
	void SetOperationRateTimeNight(CString ulTime);
	CString GetOperationRateTimeNight() const;

//激光能量测试时刻  yutingxun 06-8-23
	void SetLaserTestCurTime(time_t ltime);
	time_t GetLaserTestCurTime() const;
//振动校正测试时刻  yutingxun 06-8-23
	void SetAdjustTime(time_t ltime);
    time_t GetAdjustTime() const;
	
	BOOL	GetIsRecordPowerPara() const;
	void SetIsRecordPowerPara(BOOL bEnable=FALSE);
	
	void SetCheckPeriod(BOOL able);
	BOOL	GetCheckPeriod() const;

	//是不是要备分日志的标记号
	void SetSaveLogFlag(int iFlag = 0);//0为不记录
	int GetSaveLogFlag() const;
	void SetCurPCBHoleCount(long lCount);
	long GetCurPCBHoleCount() const;
	void SetCurPCBDrilledHoleCount(long lCount);//ly add 20110903
	long GetCurPCBDrilledHoleCount() const;//ly add 20110903
	void SetErrorPCB(int lCount);//ly add 20120116
	int GetErrorPCB() const;//ly add 20120116
	void SetCurPCBDrilledArea(long lCount);//ly add 20111008
	long GetCurPCBDrilledArea() const;//ly add 20111008
	void SetFidicialMatchMode(BOOL bMatchMode);
	BOOL GetFidicialMatchMode()const;
	long GetAdjustJumpDelay()const;
	void SetAdjustJumpDelay(long lDelay);
	void SetHolesSum(double lCount);//ly add 20121230
	double GetHolesSum() const;//ly add 20121230
	double GetPowerScale() const;

	int GetLoadPCBTime() const;
	int GetUnLoadPCBTime() const;	
	void SetLoadPCBTime(int loadtime=60); 
	void SetUnLoadPCBTime(int unloadtime=10);	
	//
    void SetGlvAdjPlsRelease(UINT ulRelease);
	void SetGlvAdjPosX(long lPos);
	void SetGlvAdjPosY(long lPos);
	UINT GetGlvAdjPlsRelease() const;
	long GetGlvAdjPosX() const;
	long GetGlvAdjPosY() const;
	long GetGlvCaliOffsetTol();//获取原点校正公差

	void SetAdjustJumpSpeed(long lJmpSpeed);
	long GetAdjustJumpSpeed() const;
	long GetCCDAdjThreshold() const;
	void SetCCDAdjThreshold(long dbThreshold);
	long GetCCDProcThreshold() const;
	void SetCCDProcThreshold(long dbThreshold);

	long GetCCDProcInnerThreshold() const;
	void SetCCDProcInnerThreshold(long dbThreshold);
	long GetCCDProcInnerRange() const;//ly add 20121009
	long GetTableDelay() const;//ly add 20121013

	long GetAdjustPulseRelease() const;
	void SetAdjustPulseRelease(long lRelease);
	long GetAdjustPulsePeriod()const;
	void SetAdjustPulsePeriod(long lPeriod);
	//yutingxun 7-6 校正时有自己的光圈
	long GetAdjustAperture()const;
//	long GetAdjustShowAperture()const;				//2009 12 24 liq
	long GetLongPathAdjustAperture()const;
//	long GetLongPathAdjustShowAperture()const;		//2009 12 24 liq
	void SetAdjustAperture(long lAptNo);
	void SetLongPathAdjustAperture(long lAptNo);
	void SetDrlRegPlsNum(long lNum);
	long GetDrlRegPlsNum()const;
	long GetDrlRegAperture()const;		    
//	long GetDrlRegShowAperture()const;		//2009 12 24 liq
	void SetDrlRegAperture(long lAptNo);
	long GetDrlRegPulsePeriod()const;
	void SetDrlRegPulsePeriod(long lPeriod);
	long GetDrlRegPulseRelease() const;
	long GetDrlRegPulse2Release() const;
	long GetDrlRegPulse3Release() const;
	long GetDrlRegPulse4Release() const;
	long GetDrlRegPulse5Release() const;

	BOOL GetIsDrillRegion() const;
	void SetIsDrillRegion(BOOL isDrillRegion) ;	

	long GetDrlRegPulseTimes() const;
	void SetDrlRegPulseTimes(long Times);
	void SetDrlRegPulseRelease(long lRelease);
	void SetDrlRegPulse2Release(long lRelease);
	void SetDrlRegPulse3Release(long lRelease);
	void SetDrlRegPulse4Release(long lRelease);
	void SetDrlRegPulse5Release(long lRelease);

	long GetDrlRegionPointDis();
	void SetDrlRegionPointDis(long lDis);

	long GetDrlRegJumpDelay()const;
	void SetDrlRegJumpDelay(long lDelay);
	void SetDrlRegJumpSpeed(long lSpeed);
	long GetDrlRegJumpSpeed()const;
//yutingxun 7-5  单独设置打字符的参数
	void SetDrlTxtPlsNum(long lNum);
	long GetDrlTxtPlsNum()const;
	long GetDrlTxtAperture()const;
//	long GetDrlTxtShowAperture()const;		//2009 12 24 liq
	void SetDrlTxtAperture(long lAptNo);
	long GetDrlTxtPulsePeriod()const;
	void SetDrlTxtPulsePeriod(long lPeriod);
	long GetDrlTxtPulseRelease() const;
	void SetDrlTxtPulseRelease(long lRelease);
	long GetDrlTxtJumpDelay()const;
	void SetDrlTxtJumpDelay(long lDelay);
	void SetDrlTxtJumpSpeed(long lSpeed);
	long GetDrlTxtJumpSpeed()const;

	long GetToolApertureNo(int nToolIndex)const;
//	long GetToolShowApertureNo(int nToolIndex)const;		//2009 12 24 liq
	long GetToolSubApertureNo(int nToolIndex)const;
//	long GetToolSubShowApertureNo(int nToolIndex)const;		//2009 12 24 liq

//  enum PROCMODE{CONMASK=0,LGWINDOW};
    enum PROCMODE{EXTERNALMARKPROC=0,INNERMARKPROC};

	PROCMODE GetProcMode()const;
	void SetProcMode(enum PROCMODE pm);

    enum FILEMODE{NORMALPROC=0,INNERMARK,LOCALMARKM02,LOCALMARKSA};
	FILEMODE GetFileMode()const;
	void SetFileMode(FILEMODE fm);

	Coord GetFiducialOffset(int nIndex)const;
	void ClearFiducialOffsetData();
	void AddFiducialOffset(const Coord&crd);

	void SetUserPassword(int nIndex,const CString& str);
	void DeleteUserInfo(int nIndex);
	void DeleteUserInfoByName(CString userName);
	BOOL SaveUserInfo();
	BOOL LoadUserInfo();
	UserInfo GetLoginUserInfo(int nIndex) const;
	long GetLoginUserNum();
	void AddUserInfo(const UserInfo& ulv);
	enum PRIORITY{PRIMARY,SUPEROR,ADMIN};//初级（生产权限），高级（售后权限），系统（研发权限）。ly mark 20111010
	enum ProcMode{MANUPROC,AUTOPROC,SELEPROC};
	void SetCurUserName(const CString& strName);
	void SetCurUserLevel(long lLevel);
	void SetCurUserDepartment(const CString& dept);
	void SetCurUserShift(const CString& shift);

	long GetBETOffset(int nApt)const;
	long GetFactualAperture(int nApt)const;      //2009 12 23 liq

//DOUBLEBET 20150911
	void SetFactualAperture2(int nApt, long nOffset);
	long GetFactualAperture2(int nApt) const;
	long GetBETOffset2(int nApt) const;
	void SetBETOffset2(int nApt, long nOffset);

	void SetBETOffset(int nApt,long nOffset);

	void SetFactualAperture(int nApt,long nOffset);   //2009 12 23 liq
	long GetToolNo(int nTpIndex);
	long GetAptBenchmark() const;
	void SetAptBenchmark(long lPos);
	long GetBETBenchmark()const;
	void SetBETBenchmark(long lPos);
//第二套BET光圈偏置参数
	void SetAptBenchmark2(long lPos);
	long GetAptBenchmark2() const;	
	void SetBETSubOffset2(long lPos);
	long GetBETSubOffset2() const;
	void SetBETPriOffset2(long offset);	
	long GetBETPriOffset2();

	Coord GetTabPitchDistanceXY()const;
	void SetTabPitchDistanceXY(const Coord& crd);
	CRD GetUnloadTransPos() const;
	CRD GetLoadTransPos() const;
	void SetLoadTransPos(CRD pos);
	void SetUnloadTransPos(CRD pos);
	void SetAxisYErr(UINT ulIndex,const PosErr& poserr);
	void SetAxisXErr(UINT ulIndex,const PosErr& poserr);
	void SetAxisYErr(UINT ulIndex,double dbErr);
	void SetAxisXErr(UINT ulIndex,double dbErr);
	double GetAxisYErr(UINT ulIndex)const;
	double GetAxisXErr(UINT ulIndex)const;
	double GetAxisYErrVaule(long nPos)const;
	double GetAxisXErrVaule(long nPos)const;

	long GetAxisXErrRange(void)const;  //
	long GetAxisXErrCounter(void)const;//
	long GetAxisXErrnInterval(void)const;
	long GetAxisYErrnInterval(void)const;
	long GetAxisYErrRange(void)const;  //
	long GetAxisYErrCounter(void)const;//
	long GetAxisXErrStart(void)const;//ly add 20110310
	long GetAxisXErrEnd(void)const;//ly add 20110310
	long GetAxisYErrStart(void)const;//ly add 20110310
	long GetAxisYErrEnd(void)const;//ly add 20110310
	
	long GetCCDLightness(long lChan=0,long lTpye=0,UINT select = 0)const;
	void SetCCDLightness(long lLum,long lChan=0,long lType =0,UINT Select = 0);
	//infrared
	void SetCCDInfrared(long lLum, long lChan= 0,UINT Select= 0);// lChan通道左右 Select类型 外标靶，内标靶，校正。。。。。
	long GetCCDInfrared(long lChan= 0,UINT select= 0) const;// lChan通道左右 Select类型 外标靶，内标靶，校正。。。。。

	void SetMoveMaxSpeed(UINT ulAxis,long nValue);
	void SetMoveAcc(UINT ulAxis,long nValue);
	void SetMoveDec(UINT ulAxis,long nValue);
	void SetSLBitPerMM(long ulBit);
	long GetSLBitPerMM()const;
	CString GetCorPathName(int nHeadNo)const;
	void SetProcGlvOffset(const Coord& crd);
	Coord GetProcGlvOffset()const;
	Coord GetGlvDistance()const;
	void SetCCDDistance(const Coord& crd);
	Coord GetCCDDistance()const;

	HoleCoordV GetFiducial(int nHead);
	void SetFiducialPos(const Coord &crd,int n, int nHead);
	Coord GetFiducialPos(int nIndex,int nHead=0);
	void AddFiducialPos(const Coord& crd,int nHead);
	long GetFiducialPosNum(int nHead=0)const;
	void ClearFiducailRealPos(int nHead=0);

	HoleCoordV GetInnerFiducial(int nHead);
	Coord GetInnerFiducialPos(int nIndex,int nHead=0);
	void AddInnerFiducialPos(const Coord& crd,int nHead);
	long GetInnerFiducialPosNum(int nHead=0)const;
	void ClearInnerFiducailRealPos();

	HoleCoordV GetLocalMark(int DataIndex,int nHead=0);
	Coord GetLocalMarkDataRealPos(int DataIndex,int PosIndex,int nHead=0);
	void AddLocalMarkDataPosInfo(int DataIndex,int nHead=0);
	void AddLocalMarkDataRealPos(const Coord& crd,int DataIndex,int nHead=0);
	long GetLocalMarkDataRealPosNum(int DataIndex,int nHead=0)const;
	void ClearLocalMarkDataRealPos();

	CString GetAppPath()const;
	void SetLaserTestCleanRefPos(const Coord& crd);
	Coord GetLaserTestCleanRefPos()const;
	UINT GetProcedPCBNum()const;
	void SetProcedPCBNum(UINT ulNum);

	UINT GetProcJumpSpeed()const;
	void SetProcJumpSpeed(UINT lJumpSpeed);
	UINT GetProcJumpDelay() const;
	void SetProcJumpDelay(UINT lJumpDelay);
	UINT GetProcJumpDelay0() const;     //ly add 20111123
	void SetProcJumpDelay0(UINT lJumpDelay);//ly add 20111123
	UINT GetProcJumpLenth() const;//ly add 20111123
	long GetRTC5AddBasicDelay() const;
	long GetRTC5TestBasicDelay() const;
	void SetProcJumpLenth(UINT lJumpLenth);//ly add 20111123
	int GetFirstJumpDelay() const ;//ly add 20111123
	UINT GetFirstDelayPeriod() const ;//ly add 20111123//-----
	int GetOtherJumpDelay() const ;//ly add 20120811
	UINT GetOtherDelayPeriod() const ;//ly add 20120811
	int GetDelayJump() const ;//ly add 20130315
	int GetNULLMark() const ;//ly add 20111123
	int GetAOMLaserOnDelay() const;//jpc add 20130815
	int GetAOMLaserOffDelay() const;//jpc add 20130815
	int GetTestMode() const ;//ly add 20120208
	double GetMaxDutycycle();//ly add 20111209
	void  SetMaxDutycycle(double duty);//ly add 20111209
	void ClearTools();
	CString GetToolFileName()const;
	void SetToolFileName(const CString& str);
	CString GetFileName()const;
	void SetFileName(const CString& str);
//  工具
	long GetToolSetCnt() const;
    void AddEnergyParaSet(const int &iTool, const int &iLayer,  const BOOL &bCheck, const int &iPeriod,const int &iRelease,const int &iDrillMode,const int &iApertureNo, const int &iScanNum, const int &iFocusOffset);
	int GetToolItemDrillMode(int iToolNo,int iLayerNo);
	long GetToolLayerCnt(int iToolNo) const;
	int GetToolLayerNo(int iToolNo) const;
	bool GetToolLayerCheck(int iToolNo) const;
	int GetToolItemPeriod(int iToolNo,int iLayerNo);
	float GetToolLayerDiameter(int iToolNo) const;
	int GetToolItemRelease(int iToolNo,int iLayerNo);
	int SystemDoc::GetToolItemScanNum(int iToolNo,int iLayerNo);
	int GetToolItemFocusOffset(int iToolNo,int iLayerNo);
	int GetToolItemApertureNo(int iToolNo,int iLayerNo);
	bool GetToolItemCheck(int iToolNo,int iLayerNo);
	void AddUserToolSet(const BOOL &bCheck, const float &fDiameter, const int &iToolNo);

	LayerToolPara GetToolPara(int iToolNo,int iLayer=0) const;	//得到相应工具号的能量参数
	long GetToolsCnt() const;

	void AddEnergyPara(const int &iTool, const int &iLayer,const int& iEnergyNo, const int &iModel, const int &iRelease, const int &iPeriod);
	void AddLayerToolPara(const int &iTool, const int &iLayer, const int &iDrillModel, const int &iOffset);
//	void AddUserTool(const int &iToolNo, const int &fDiameter, const int &iAperture);
	void AddUserTool(const int &iToolNo, const int &fDiameter, const int &iAperture,const int &iSubAperture);
	BOOL  GetIsFiducialDo() const;
	BOOL  GetIsFiducialDo2(int direction) const;
	BOOL GetMotorState() const;
	void SetMotorState(BOOL bHome=FALSE);
	void SetIsFiducialDo(BOOL bIsFicial=FALSE);
	void SetIsFiducialDo2(BOOL bIsFicial=FALSE,int direction=0);
	BOOL GetFileOpenState()const; 
	void SetFileOpenState(BOOL bOpen=FALSE); 

	BOOL GetLaserPowerTestState() const;
	void SetLaserPowerTestState(BOOL bTest=FALSE); 
	
	BOOL GetLaserWarmupState() const;
	void SetLaserWarmupState(BOOL bWarmup=FALSE); 

	BOOL GetLaserPowerState() const;
	void SetLaserPowerState(BOOL bPower=FALSE); 
	BOOL	GetMachinePowerState() const;
	void SetMachinePowerState(BOOL bPower=FALSE); 

	BOOL GetScanLabState() const;
	void SetScanLabState(BOOL bTest=FALSE); 
	
	long GetTestAperture()const;
//	long GetTestShowAperture()const;		//返回界面显示的光圈  2009 12 24 liq

	void SetTestAperture(int nApt);
//	void SetLongPathTestAperture(int nApt);
    //上下料位置	
	CRD	 GetLoadPitchPos()const;
	CRD  GetUnloadPitchPos() const;
	void SetLoadPitchPos(CRD pos);
	void SetUnLoadPitchPos(CRD pos);	
	CRD	 GetLoadBenchMarkPos()const;
	CRD  GetUnloadBenchMarkPos() const;
	void SetLoadBenchMarkPos(CRD pos);
	void SetUnLoadBenchMarkPos(CRD pos);
	void SetLoadTunePos(CRD pos);
	void SetUnLoadTunePos(CRD pos);

	CRD	 GetLoadTunePos()const;
	CRD  GetUnLoadTunePos() const;

	CRD	 GetLoadLiftBMPos()const;
	CRD  GetUnloadLiftBMPos() const;
	void SetLoadLiftBMPos(CRD pos);
	void SetUnloadLiftBMPos(CRD pos);

	CRD  GetTestThicknessPos() const;
	void SetTestThicknessPos(CRD pos);

	long GetPCBThickness()const;
	void SetPCBThickness(long lThickness);

	long GetPCBThicknessStd()const;
	void SetPCBThicknessStd(long lThickness);
	//平台
	Coord GetTabBenchmark() const;
	void  SetTabBenchmark(const Coord& pos);
	Coord GetTabLoadPos  () const;
	void  SetTabLoadPos  (const Coord& pos);
	Coord GetTabUnloadPos() const;
	void  SetTabUnloadPos(const Coord& pos);


	Coord GetOverTabLoadPos  () const;
	void  SetOverTabLoadPos  (const Coord& pos);
	Coord GetOverTabUnloadPos() const;
	void  SetOverTabUnloadPos(const Coord& pos);

	//文件系统与控制系统的相对位置关系
	Coord GetFileToRealRelative() const;
Coord GetFileToRealRelative2(int direction) const;
	void  SetFileToRealRelative(const Coord& crd);
	void  SetFileToRealRelative2(const Coord& crd,int direction);

	// 电机速度参数
	long GetMoveMaxSpeed(UINT ulAxis) const;
//	long GetMoveStartSpeed(UINT ulAxis) const;
	long GetMoveDec(UINT ulAxis) const;
	long GetMoveAcc(UINT ulAxis) const;
	void SetMoveParam(UINT ulAxis,const MotionSpeed& ms);
	MotionSpeed GetMoveParam(UINT ulAxis) const;

	void SetTestLaserOnTime(long lTime);
	long GetTestLaserOnTime() const;

	void SetTestJumpSpeed(long lSpeed);
	long GetTestJumpSpeed() const;
	void SetTestJumpDelay(long lDelay);
	long GetTestJumpDelay() const;

	void SetBaseDelay(long lDelay);
	long GetBaseDelay() const;

	void SetTestPlsPeriod(long lPeriod);
	long GetTestPlsPeriod() const;
	void SetTestPlsRelease(long lRelease);
	long GetTestPlsRelease() const;
	void SetWarmUpPlsRelease(long lRelease);//20110124
	long GetWarmUpPlsRelease() const;//20110124 机器预热

	BOOL DistributeSubarea();
	bool SetProcessState(long bAutoProc=0);
	long GetProcessState() const;
	void SetProcessSide(long bProcSide=0);
	long GetProcessSide() const;

	void SetProcessDir(long lDir);
	long GetProcessDir()const;


	//CString GetLOTID() const;
	//void SetLOTID(const CString& strLotId);
	CString GetLOTIDFix() const;//ly add 20121127
	void SetLOTIDFix(const CString& strLotId);//ly add 20121127
	CString GetLOTIDInc() const;//ly add 20121127
	void SetLOTIDInc(const CString& strLotId);//ly add 20121127

	void SetNoProcessID(const CString& noProcessID);//不加工的批号日志记录
	CString GetNoProcessID() const;

	CString GetMachSn() const;
	void SetMachSn(const CString& strMachSn);
	void SetStrZoomSn(const double& strZoomSn);//set string zoom
	double GetStrZoomSn() const;
	void SetScanSize(long lSize);
	long  GetScanSize() const;

	void SetMotionCardSn(long CardNo,long CardSn);
	long GetMotionCardSn(long CardNo) const;
	void SetEnLOTSn(BOOL bEnable=false);
	void SetEnManuDay(BOOL bEnable=false);
	void SetEnManuTime(BOOL bEnable=false);
	void SetEnBigTxt(BOOL bBig=false);
	void SetEnMachSn( BOOL  bEnable=false);
	void SetEnManuString( BOOL  bEnable=false);

	BOOL GetEnLOTSn() const;
	BOOL GetEnManuTime() const;
	BOOL GetEnManuDay() const;
	BOOL GetEnMachSn() const;
	BOOL GetEnManuString() const;

	BOOL GetEnLOTFix() const;//ly add 20121127
	void SetEnLOTFix(BOOL bEnable=false);//ly add 20121127
	BOOL GetEnLOTInc() const;//ly add 20121127
	void SetEnLOTInc(BOOL bEnable=false);//ly add 20121127
	BOOL GetEnLOTScale() const;//ly add 20121127
	void SetEnLOTScale(BOOL bEnable=false);//ly add 20121127
	BOOL GetEnAxisNo() const;//ly add 20121230
	void SetEnAxisNo(BOOL bEnable=false);//ly add 20121230
	void SetOneAxis(BOOL bEnable);//ly add 20140108
	BOOL GetOneAxis();//ly add 20140108
	void SetCurOneAxis(int axis);//ly add 20140108  0=left  1=right
	int	 GetCurOneAxis();//ly add 20140108
	BOOL GetEn3Fid() const;//ly add 20130121
	void SetEn3Fid(BOOL bEnable=false);//ly add 20130121
	BOOL Get3Fid() const;//ly add 20131108
	void Set3Fid(BOOL bEnable=false);//ly add 20131108
	void SetCheckManulScaleRange(bool temp);//ly add 20140702
	BOOL GetCheckManulScaleRange();//ly add 20140702
	BOOL GetEnManuFid() const;//ly add 20130121
	void SetEnManuFid(BOOL bEnable=false);//ly add 20130121
	int	 GetLFidNum() const;//ly add 20130121
	void SetLFidNum(int num);//ly add 20130121
	int	 GetRFidNum() const;//ly add 20130121
	void SetRFidNum(int num);//ly add 20130121
	BOOL GetLFidEn(int index);//ly add 20130121
	void SetLFidEn(BOOL enable,int index);//ly add 20130121
	BOOL GetRFidEn(int index);//ly add 20130121
	void SetRFidEn(BOOL enable,int index);//ly add 20130121
	int	 GetLInnFidNum() const;//ly add 20130121
	void SetLInnFidNum(int num);//ly add 20130121
	int	 GetRInnFidNum() const;//ly add 20130121
	void SetRInnFidNum(int num);//ly add 20130121
	BOOL GetLInnFidEn(int index);//ly add 20130121
	void SetLInnFidEn(BOOL enable,int index);//ly add 20130121
	BOOL GetRInnFidEn(int index);//ly add 20130121
	void SetRInnFidEn(BOOL enable,int index);//ly add 20130121

	int GetDataUnit() const;//ly add 20120516 ---------------
	int GetCrdMode() const;
	int GetDataFormat() const;
	int GetDecimalNum() const;
	int GetIntegerNum() const;

	void SetDataUnit(int dataunit);//ly add 20120516 ---------------
	void SetCrdMode(int mode) ;
	void SetDataFormat(int format) ;
	void SetDecimalNum(int decnum) ;
	void SetIntegerNum(int intnum) ;

	void SetTableClamp(BOOL clamp);//ly add 20120523
	BOOL  GetTableClamp();//ly add 20120523

	void SetLaserPowerPattern(int laserPowerPattern);//jpc add 20130806
	int GetLaserPowerPattern();//jpc add 20130806
	void SetUse9112(int temp);//ly add 20130806
	int GetUse9112();//ly add 20130806

	void SetPowerComHandle(HANDLE hPowerCom);
	HANDLE  GetPowerComHandle();

	void SetScaleUnit(BOOL temp);//ly add 20130625---------------------	
	BOOL GetScaleUnit();	
	void SetPowerMax(BOOL temp);	
	BOOL GetPowerMax();		
	void SetWaterYBJ(BOOL temp);	
	BOOL GetWaterYBJ();	
	long GetCCDContrastThrd();//ly add 20140328
	void SetScanSizeMax(int temp);//ly add 20140308
	int  GetScanSizeMax();
	void SetLargeTable(int temp);
	long  GetTableWidth();
	long  GetTableHeight();
	int  GetLargeTable();//ly add 20140308
	long GetTableResetPosX(int TableType);//ly add 20140324
	void SetDoorOpenWarning(int temp);//ly add 20140418
	int  GetDoorOpenWarning();
	void SetInfrared(int temp=0);
	int  GetInfrared();
	void SetHandCOMNum(int temp=2);
	int GetHandCOMNum();
	void SetPowerCOMNum(int temp=3);
	int  GetPowerCOMNum();
	void SetFZInnerMark(BOOL temp);
	BOOL GetFZInnerMark();	
	void SetGYDMirror(BOOL temp);	
	BOOL GetGYDMirror();
	void SetShunluoScale(BOOL temp=FALSE);//顺络需要的涨缩功能
	BOOL GetShunluoScale();
	void SetShenLan3Fid(BOOL temp);
	BOOL GetShenLan3Fid();
	void SetShowTool(BOOL temp);//ly add 20140520
	BOOL GetShowTool();//ly add 20140520
	void SetLoadAfterPitch(BOOL temp);//ly add 20140520
	BOOL GetLoadAfterPitch();//ly add 20140520
	void SetFileLPTest(BOOL temp);//ly add 20130801
	BOOL GetFileLPTest();//ly add 20130801
	void SetFORWARDX(long temp);//ly add 20130805---
	void SetREVERSEX(long temp);
	void SetFORWARDY(long temp);
	void SetREVERSEY(long temp);
	long GetFORWARDX();
	long GetREVERSEX();
	long GetFORWARDY();
	long GetREVERSEY();//ly add 20130805---
	double GetAptPower(int nApt,int nrelease);//ly add 20130801
	long GetAptDelay(int nApt);//ly add 20131223
	BOOL GetAptDelayFile();//ly add 20140126
	void SetNewDelay(BOOL temp);
	BOOL GetNewDelay();
	long GetBET1F();
	long GetBET2F();
	long GetBET3F();
	double GetBET1TOBET2();
	double GetBET2TOBET3();
	long GetBETMAX();//ly add 20130625-----------------------

	void SetFitApt(BOOL temp);//ly add 20131223------------
	BOOL GetFitApt();//ly add 20131223------------
	void SetDrillInc(BOOL temp);//ly add 20140702------------
	BOOL GetDrillInc();//ly add 20140702------------

	void SetDrillH01H02(BOOL temp);	
	BOOL GetDrillH01H02();	

	BOOL GetLaserPowerMode();	
	void SetLaserPowerMode(BOOL laserPowerMode);

	//20150930
	BOOL GetLaserPowerShow();	
	void SetLaserPowerShow(BOOL laserPowerShow);	
	long GetLaserPowerDelayTime();	
	void SetLaserPowerDelayTime(BOOL laserPowerDelayTime);

	long GetLaserPowerTimes();	//20151204 设置激光功率测试次数
	void SetLaserPowerTimes(long laserPowerTimes);

	BOOL GetIsNullPrecessHoles();	//20151204 设置是否空跑板，只计算板的涨缩，不加工移动平台
	void SetIsNullPrecessHoles(BOOL isNullPrecessHoles);

	BOOL GetBunchMode();//是否开启激光串模式加工	
	void SetBunchMode(BOOL bBunchMode=FALSE);

	void SetFitBit(BOOL temp);//ly add 20130724------------
	BOOL GetFitBit();
	void SetMatch(BOOL temp);
	BOOL GetMatch();
	void SetMatchScore(double temp);
	double GetMatchScore();//ly add 20130724------------
	void SetLAvgScaleX(double temp);//ly add 20131021----
	double GetLAvgScaleX();
	void SetLAvgScaleY(double temp);
	double GetLAvgScaleY();
	void SetRAvgScaleX(double temp);
	double GetRAvgScaleX();
	void SetRAvgScaleY(double temp);
	double GetRAvgScaleY();
	void SetLNum(long temp);
	long GetLNum();
	void SetRNum(long temp);
	long GetRNum();
	void SetLastFile(CString temp);
	CString GetLastFile();//ly add 20131021----

	float GetLaserPwAvg();//ly add 20140612
	void ResetLaserPw();//ly add 20140612
	void SetLaserPw(int index,double pw);//ly add 20140527
	float GetLaserPw(int index);//ly add 20140527
	float GetLaserPwMax();//ly add 20140527
	float GetLaserPwMin();//ly add 20140527
	void SetOutFidsOffset(int offset); //ly add 20140504
	int GetOutFidsOffset();//ly add 20140504
	void SetFZInnerOffset(int offset) ;//ly add 20120522
	int  GetFZInnerOffset();//ly add 20120522
	void SetFZInnerScale(double scale) ;//ly add 20120522
	double  GetFZInnerScale();//ly add 20120522
	void SetLaserComp(int comp); //ly add 20120919
	long GetLaserComp();//ly add 20120919
	void SetLaserTestComp(int comp); //ly add 20121227
	long GetLaserTestComp();//ly add 20121227
	void SetLoadOptimize(bool opt); //ly add 20120919
	long GetLoadOptimize();//ly add 20120919

	BOOL ReleaseSysDoc();
	BOOL InitializeSysDoc();
//  振镜校正 激光功率测试 
	void SetCCDToGlvTestOffset(const Coord3D& crd , long  lHeadNo=0);  //振镜校正 加工测试点位置
	void SetCCDToCCDTestOffset(const Coord3D& crd , long  lHeadNo=0);  //CCDTOCCD测试点位置
	Coord3D GetCCDToGlvTestOffset(long lHeadNo=0) const;
	Coord3D GetCCDToCCDTestOffset(long lHeadNo=0) const;
	
	double GetGlvAdjustPresionL();
	void SetGlvAdjustPresionL(double presion);
	double GetGlvAdjustPresionR();
	void SetGlvAdjustPresionR(double presion);

///长激光路径
	void SetLongPathCCDToGlvTestOffset(const Coord3D& crd , long  lHeadNo=0);  //振镜校正 加工测试点位置
	Coord3D GetLongPathCCDToGlvTestOffset(long lHeadNo=0) const;

	void SetCCDToGlvSysOffset(const Coord3D &crd, long lHeadNo=0);       //安装偏移
	//原点校正与上次比较是否超出偏差
	BOOL IsGlovCalibOffstOutofTol(const Coord3D& crdResult,long nHead);
	//获取两点间距离(xy平面)
	long GetTwoPoitDistance(const Coord& crd1,const Coord& crd2);

	long GetMainFiduPolarity();	
	long GetInnerFiduPolarity();
	void SetMainFiduPolarity(long nPolarity);
	void SetInnerFiduPolarity(long nPolarity);

	Coord3D GetCCDToGlvSysOffset(long lHeadNo=0)  const;

	void SetLaserPowerTestCrd(const Coord3D& crd , long  lHeadNo=0);   //激光测试
	Coord3D GetLaserPowerTestCrd(long lHeadNo=0) const;
	
	void SetCCDToGlvTestOffset(int   iChannel,    const Coord3D& crd);
	void SetCCDFocus	(long lPos,int nCCDNo=0);
	void SetLaserProcFocus(long lPos,int nNo=0);
	void SetLongPathLaserProcFocus(long lPos,int nNo=0);
	void SetDirManuTime (long lDir=0);
	void SetDirManuDay  (long lDir=0);
	void SetDirMachSn   (long lDir=0);

	long GetCCDFocus(int nCCDNo=0) const;     //正常加工时的CCD 取象位置
	long GetLaserProcFocus(int nNo) const;    //正常加工时的激光钻孔位置
	long GetLongPathLaserProcFocus(int nNo) const;
	long GetDirManuTime() const;
	long GetDirManuDay()  const;
	long GetDirMachSn()   const;

	long GetCurUserLevel()const;
	CString GetCurUserName()const;
	CString GetCurUserDepartment()const;
	CString GetCurUserShift()const;

	BOOL SaveCCDLuminancePara() const;
	BOOL LoadCCDLuminancePara();

	void SetMirrorFlag(int flag=0) { m_MirrorFlag = flag; };
	int	 GetMirrorFlag(void)const  { return m_MirrorFlag; };

	void SetRotateFlag(int flag=0) { m_RotateFlag = flag; };//ly add 20120828
	int	 GetRotateFlag(void)const  { return m_RotateFlag; };//ly add 20120828

	void SetScaleType(int flag=0) { m_ScaleType = flag; };//ly add 20120913
	int	 GetScaleType(void)const  { return m_ScaleType; };//ly add 20120913
//protected:
	BOOL LoadVersionParam();//ly add 20130625
	BOOL LoadProcessParam();
	BOOL LoadMotionParam();
	BOOL LoadWebServiceParam();    //ly add 20191023

//	BOOL SaveVersionParam() const;
	BOOL SaveProcessParam() const;
	BOOL SaveMotionParam()  const;
	BOOL SaveWebServiceParam()  const;

//	BOOL LoadScaleParam();//ly add 20131021
//	BOOL SaveScaleParam() const;
//	void ResetScaleParam(CString strName);//ly add 20131021

//	BOOL SaveBackProcessParam() const;
//	BOOL SaveBackMotionParam()  const;	

	BOOL GetUIManSetScale();//ly add 20140504
	void SetUIManSetScale(BOOL bFlag);
	BOOL GetUseRefScale();//ly add 20140504
	void SetUseRefScale(BOOL bFlag);
	BOOL IsManSetScale();//1:手工设定涨缩;0:自动
	void SetCheckManScale(BOOL isCheck);
//	void CfgManSetScaleFlag(BOOL bFlag);//配置"手动设定涨缩"标志
	int InputManSetScaleVal(double fScaleX,double fScaleY);//输入手动设定涨缩值.涨缩范围-8.0% - 8.0%
	int GetManSetScaleVal(double& fScaleX,double& fScaleY);//获取手动设定涨缩值

	int  GetTestThicknessZSafePos();//Z轴安全位置,即测厚汽缸打下不会接触到台面
	int  GetTestThicknessCompensation(int nHead);

	BOOL CalculateCalibratePosOffset();//计算校正的位置，替代编译开关

	Coord GetLeftRightFiducialMoveCrd(int index);
	void SetLeftRightFiducialMoveCrd(int index,Coord crd);
	
private://jpc add 20120419


	BOOL m_bCongexErrorPoint;
	int m_iconutCongexError;

	int m_isOverBroad;
	int isProcessModeToFile;
	
	BOOL isTimeAnalyse;
	COleDateTime bigenTime;
	DWORD calculateBeginTime;

	long  totalWidthCalibrate;//TOTALWIDTH			500000		//校正板整板使用宽度
    long  totalHeightCalibrate;//TOTALHEIGHT			45000		//校正板整板使用高度
	long  patternLongWidthCalibrate;//	PATTERNLONGWIDTH	44000		//点阵校正时的扫描宽度(占用宽度）
	long  patternDotWidthCalibrate;//	PATTERNDOTNUM		11		//点阵校正时的扫描点数
	long  matrixTimesCalibrate;//	MATRIXTIMES			2		//点阵校正时单方向复用次数
	long  patternMatrixWidthCalibrate;//#define	PATTERNMATRIXWIDTH	PATTERNLONGWIDTH / PATTERNDOTNUM / MATRIXTIMES	//点阵校正时复用位移值
	long  offsetLongWidthCalibrate;//#define	OFFSETLONGWIDTH		15000		//原点校正时的扫描宽度(占用宽度）
	long  offsetHeightCalibrate; //#define	OFFSETHEIGHT		5000		//原点校正时的高度位移值

	BOOL m_bFaultRun;
	int  m_nWarningNo;
	int  m_nAlarmId;

	bool m_bEnableAutoAdjust;
	bool m_bEnableAutoPower;
	bool m_bCTIHWWarning;//ly add 20130708
	bool m_bEnableFidRetry;//ly add 20120202
	long m_lNgSum;//ly add 20121127
	long m_lNgThrd;//ly add 20121127
	double m_lDrldHolesSum;//累计加工孔数  ly add 20121230
	double m_lPowerScale;
	int m_lLoadPCBTime,m_lUnLoadPCBTime;

	BOOL m_bAutoAdjustPattern[2];
	BOOL m_bAutoLaserPowerTest[2];

	BOOL m_bToolCycleMode;
	BOOL m_bEnFiducial[4];
	long m_iCurrentAptNo;
	long m_iAutoThickError;
	//int		m_iLotIDProMode;//ly delete 20121127
	long	m_iGlvAdjustThreshold;
	long m_iDistanceCenterThreshold;
	double	m_fPCBScaleThreshold;//涨缩阈值  百分比
	long	m_fPCBScaleThrd;//ly add 20120913 涨缩阈值  尺寸
	long	m_ScaleType;//ly add 20120913  涨缩类型选择
	long	m_laserComp;//ly add 20120919 激光功率补偿
	long	m_laserTestComp;//ly add 20121227 激光功率测试补偿
	long	m_LoadOptimize;//ly add 20120919 上下料是否升级1升级0老上下料流程
	double m_fFZInnerScale;//ly add 20120522
	double m_fLaserPowerTestSt;
	double m_fLaserPowerTestMax;//ly add 20120924

	double m_dGlvAdjustPresionL;//ljy 20200911
	double m_dGlvAdjustPresionR;

    HoleCoordV   m_InnerFiducialRealPosL; 
    HoleCoordV   m_InnerFiducialRealPosR; 
	LocalMarkV	m_LocalMarkDataRealPosL;
	LocalMarkV	m_LocalMarkDataRealPosR;
	FILEMODE m_FileMode;
	BOOL m_bFault;
	BOOL m_bWarner;
	int m_LoadSubno;//ly add 20120426
	int m_UnLoadSubno;//ly add 20120426
	double m_fTextHeigth;
	CString m_strTextTest;
	long m_lBETPriOffset;
	long m_iRegionDim;
	long m_ulTestBoardThickness;
	BOOL m_ThickingType;
	long m_lThicknessY;
	long m_lThicknessX;
	long m_lThicknessZero[2];
	long m_lCCDBoardThick;
	long m_lGalvoBoardThick;
	long m_iPatternTimes[2];
	long m_iOrgTimes[2];
    BOOL m_CheckPeriod;
	BOOL m_bUIManSetScale;//ly add 20140504
	BOOL m_bUseRefScale;//ly add 20140504
	BOOL m_bManSetBoardScale;//1:手工设定PCB涨缩;0:自动计算
	BOOL m_bManScaleisCheck;

	double m_fManualScaleX;//手工设定X涨缩比例,范围0.92 ~ 1.08
	double m_fManualScaleY;//手工设定Y涨缩比例,范围0.92 ~ 1.08
	long m_lMainFiduPolarity;
	long m_lInnerFiduPolarity;
	int	 m_iPlusCounterFunc;//脉冲计数功能开关
	long  m_BaseDelay;
	unsigned long m_lPlusCntCOM;

	Coord m_LeftRightFiducialMoveCrd[2];

	SystemDoc()
	{
		m_laserComp1=0;
		m_laserComp2=0;

		m_iLAndULSystem=1;
		m_iUnloadIsOK=1;
		m_iTableAbsorbFirst=1;
		m_iCustomerSpecial=0;
		m_iMINlaserPeriod=200;

		m_bPCBBoardIsReady=false;

		m_iProcAxisSelected=0;

		m_bAutoGalvoAdjustIsTimed=true;
		m_bAutoLaserTestIsTimed=true;

		m_lFORWARDZ=55000;

		m_bAxisIsRun[0]=false;
		m_bAxisIsRun[1]=false;
		
		m_bDrillCoil=false;

		m_bTableIsCali=true;

		m_bTable00IsCali=true;
		m_bTable01IsCali=true;

		m_lGlvCaliOffsetTol=2000;
		m_lTestThicknessZSafePos=20000;
		m_lTestThicknessCompensation[0]=0;
		m_lTestThicknessCompensation[1]=0;

		m_crdLBRefPoint=Coord(0,0);

		m_timeHandle=0;
		m_bFileIsOptimized=false;

		m_strCameraSNHigh[0]="";
		m_strCameraSNHigh[1]="";
		m_strCameraSNLow[0]="";
		m_strCameraSNLow[1]="";

		m_crdFirstMarkA=Coord(0,0);
		m_crdFirstMarkB=Coord(0,0);
		m_bASideIsDisplay=true;
		m_bASideIsProcessing=true;
		m_iFlowPathMode=1;
		m_iProcAxisMode=0;

		m_iProcTime=0;
		m_iDisplayColCount=0;
		m_iDisplayRowCount=0;
		m_bExcellonData0IsUp=true;
		m_bDoubleFileData=false;

		m_iHdSysDeadTime=0;
		m_iHdSysLaserTriggerAdjust=0;
		m_iHdSysPulseMode=0;
		m_iHdSysAOMOnDelay=0;
		m_iHdSysAOMOffAhead=0;
		m_fHdSysLaserMAXDutyCycle=0.09;

		m_iSysInfoDBMode=0;	
		
		m_ulSysPCBCount=0;

		for(int n=0;n<20;n++)
		{
			arrayBigHoleCPoint[n].RemoveAll();
		}
		m_bSysCircleProcMode=false;
		m_lSysBeamDia=100;
		m_lSysBeamStep=50;

        m_LeftRightFiducialMoveCrd[0].x=0;
		m_LeftRightFiducialMoveCrd[0].y=0;
		m_LeftRightFiducialMoveCrd[1].x=0;
		m_LeftRightFiducialMoveCrd[1].y=0;

		m_bCongexErrorPoint=FALSE;
		m_iconutCongexError=0;

		m_bLaserSocetCheck=TRUE;
	    m_bInitLaserSocet=FALSE;
	    m_bLaserWarning=FALSE;
		m_bIsLaserReceive=TRUE;

		m_IsEndLoadUnloade=FALSE;
		m_isSecondReverse=FALSE;
		m_DefineMatrixRange=57000;
		m_iScanlabDeadTime=60;
		m_isOverBroad=0;
		isProcessModeToFile=0;

		isTimeAnalyse=FALSE;
        calculateBeginTime=0;

		m_PatternXTimes[0]=0;//jpc add 20130304------
		m_PatternYTimes[0]=0;
		m_PatternXTimes[1]=0;
		m_PatternYTimes[1]=0;//jpc add 20130304

		m_bFaultRun=FALSE;
		m_nWarningNo=0;
		m_BaseDelay=0;
		m_nAlarmId=0;

		m_bEnableAutoAdjust=false;
		m_bEnableAutoPower=false;
		m_bCTIHWWarning = false;//ly add 20130708
		m_bEnableFidRetry=false;//ly add 20120202
		m_bToolCycleMode=false;//ly add 20120705
		m_lNgSum = 0;//ly add 20121127
		m_lNgThrd = 0;//ly add 20121127
		m_lDrldHolesSum=0.0;//ly add 20121230
		m_lPowerScale=1.0;

		m_lLoadPCBTime=0;									//20181203
		m_lUnLoadPCBTime=0;

		m_bAutoAdjustPattern[0]=true;
		m_bAutoLaserPowerTest[0]=true;
		m_bAutoAdjustPattern[1]=true;
		m_bAutoLaserPowerTest[1]=true;

		m_crdPathOffsetLT=Coord();
		m_crdPathOffsetRT=Coord();
		m_bEnFiducial[0]=true;
		m_bEnFiducial[1]=true;
		m_bEnFiducial[2]=true;
		m_bEnFiducial[3]=true;
		m_iCurrentAptNo=0;
		m_iAutoThickError=50;
		//m_iLotIDProMode=0;//ly delete 20121127
		m_iGlvAdjustThreshold=10;
		m_iDistanceCenterThreshold=75;
		m_fPCBScaleThreshold=0.0001;
		m_fPCBScaleThrd = 500;//ly add 20120913 涨缩阈值  尺寸
		m_ScaleType = 0;
		m_fLaserPw[0]=0.0;
		m_fLaserPw[1]=0.0;
		m_fLaserPw[2]=0.0;
		m_fLaserPw[3]=0.0;
		m_fLaserPw[4]=0.0;
		m_fFZInnerScale=0.0001;//ly add 20120522
		m_bTableClamp = false;//ly add 20120523
		m_bUse9112 = true;//ly add 20130807
		m_hPowerCom=INVALID_HANDLE_VALUE;
		m_ilaserPowerPattern=0;//jpc add 20130806
		m_bScaleUnit=false;//ly add 20130625----------------
		m_bPowerMax=false;
		m_bWaterYBJ=false;
		m_lCCDContrastThrd=50;//ly add 20140328
		m_iScanSizeMax=65;//ly add 20140308
		m_iLargeTable=0;//ly add 20140308  0,常用台面  1：大台面815
		m_iDoorOpen=0;//ly add 20140418
		m_isInfrared=0;
		m_isHandCOMNum=2;
		m_isPowerCOMNum=3;
		m_bFZInnerMark=false;
		m_bZHANHUARotate=FALSE;
		m_bShunluoScale=FALSE;
		m_bShenLan3Fid=0;
		m_bGYDmirror=FALSE;
		m_bFunctionOverBorad=0;
		m_bShowTool=false;//ly add 20140520
		m_bLoadAfterPitch=false;
		m_bFileLPowerTest=false;//ly add 20130801
		m_dFileAptLPower=0.0;//ly add 20130801
		//m_dFileAptDelay=600;//ly add 20131223
		for(int i=0;i<18;i++)//ly add 20140126
		{
			m_lAptDelay[i]=600;
		}
		m_lFORWARDX=350000;//ly add 20130805---
		m_lREVERSEX=-350000;
		m_lFORWARDY=455000;
		m_lREVERSEY=-485000;//ly add 20130805
		m_bNewDelay=true;//ly add 20130629
		m_lBET1F=100;					 
		m_lBET2F=80;				
		m_lBET3F=-150;					
		m_dBET1TOBET2=30.0;				
		m_dBET2TOBET3=244.0;			
		m_lBETMAX=50000;//ly add 20130625----------------
		m_bFitApt=false;//ly add 20131223
		m_bDrillInc=false;//ly add 20140702
		m_bDrillH01H02=FALSE;
		m_bLaserPowerMode=FALSE;
		m_bLaserPowerShow=FALSE;
		m_bLaserPowerDelayTime=0;
		m_ilaserPowerTimes=1;
		m_isNullPrecessHoles=TRUE;
		m_bBurstMode=FALSE;
		m_bFitBit=true;//ly add 20130724------
		m_bMatch=false;
		m_bMatchScore=0.0;//ly add 20130724-----
		m_dLScaleX=1.0;//ly add 20131021
		m_dLScaleY=1.0;
		m_dRScaleX=1.0;
		m_dRScaleY=1.0;
		m_lLNum=0;
		m_lRNum=0;
		m_strLastFile="";//ly add 20131021---
		m_fLaserPowerTestSt=0.0;
		m_fLaserPowerTestMax=0.0;//ly add 20120924
		m_dGlvAdjustPresionL;//ljy 20200911
		m_dGlvAdjustPresionR;
		m_MirrorFlag=0;
		m_RotateFlag=-1;//ly add 20120828
		m_ScaleType = -1;//ly add 20120913
		m_bFault=false;
		m_bWarner = false;
		m_LoadSubno = 0;//ly add 20120426
		m_UnLoadSubno = 0;//ly add 20120426
		m_fTextHeigth=2.4;
		m_strTextTest="HANS";
		m_lBETPriOffset=0;
		m_iRegionDim=1000;
		m_ulTestBoardThickness=0;
		m_ThickingType=false;
		m_lThicknessY=0;
		m_lThicknessX=0;
		m_lThicknessZero[0]=0;
		m_lThicknessZero[1]=0;
		m_lCCDBoardThick=1000;
		m_lGalvoBoardThick=1000;
		m_iPatternTimes[0]=0;
		m_iPatternTimes[1]=0;
		m_iOrgTimes[0]=0;
		m_iOrgTimes[1]=0;

		m_TechnicType=0;

		m_CheckPeriod = true;
	    m_triTestCCDToGlvOffL    = Coord3D();		// 振镜校正1位置
	    m_triTestCCDToGlvOffR    = Coord3D();		// 振镜校正2位置
	    
		m_triTestCCDToCCDOffL    = Coord3D();		// 振镜校正1位置
	    m_triTestCCDToCCDOffR    = Coord3D();		// 振镜校正2位置

		m_triLaserPowerTestL = Coord3D();		    // 激光测试位置
		m_triLaserPowerTestR = Coord3D();		    // 激光测试位置

//		m_triCCDToGlvSysOffsetLT  = Coord3D();
//		m_triCCDToGlvSysOffsetRT  = Coord3D();

   		m_triSCCDToGlvSysOffsetLT= Coord3D();  
   		m_triSCCDToGlvSysOffsetRT= Coord3D();   
   		m_triLCCDToGlvSysOffsetLT= Coord3D(); 
   		m_triLCCDToGlvSysOffsetRT= Coord3D(); 
		
		m_crdTabBenchmark    = Coord(-10000,-10000);  // 相对回零点的距离
		m_crdTabLoadPos      = Coord(30000,0);
		m_crdTabUnloadPos	 = Coord(-30000,0);
		m_crdOVerTabLoadPos      = Coord(30000,0);
		m_crdOVerTabUnloadPos	 = Coord(-30000,0);

        m_crdTabPitchDisXY   = Coord(5000,50000);   

		m_crdFileToReal		 = Coord();
		m_crdFileToReal2[0]= Coord(0,0);
		m_crdFileToReal2[1]= Coord(0,0);

	    m_crdCCDDistance     = Coord(600000,0);
	    m_crdGlvDistance     = Coord(600000,0);
		m_crdLaserTestCleanRef = Coord(0,7000);		  //功率测试位 与 清理位 相对位置
        m_crdProcGlvOffset  = Coord();                //加工过程中 右侧 Glavo 相对偏差
		
		m_lMotionCardSn1  =0;
		m_lMotionCardSn2  =0;
		m_lMotionCardSn3  =0;

		m_lGlvAdjustApt   =10;		 // 振镜校正glv光圈

		m_lAdjPosX=0;
		m_lAdjPosY=0;

		m_lAptOffsetCrd   =0;        // 光圈 零点偏置
		m_lBETOffsetCrd   =0;        // BET零点偏置
		
		m_lAptOffsetCrd2=0;     
		m_lBETPriOffset2=0;    
		m_lBETSubOffsetCrd2=0; 

		m_lCCDFocusPosL   =1000;     // CCD自动焦距自动加工 L
	    m_lCCDFocusPosR   =1000;     // CCD自动焦距自动加工 R
      //  m_lCCDLumL         =128;     // 光源亮度 
       // m_lCCDLumR         =128;

		m_lLaserDrillPosL =1000;	  // 激光自动加工打孔焦距 L
		m_lLaserDrillPosR =1000;	  // 激光自动加工打孔焦距 R

		m_lPCBRecorder    =2000;      // 已加工PCB板的总数	

		m_lProcessDir     =0;         // 加工方向
		m_lAutoProc       =0;		  // 是否手动加工  0: 手动 1： 自动 2：指定	
	    m_lScanSize       =65;        // 加工模块大小（方阵）
	

		m_lDirMachSn      =0;		  // 机器号方向
		m_lDirManuDay     =0;		  // 加工日期方向
		m_lDirManuTime    =0;	 	  // 加工时间方向
	    m_bEnMachSn       =0;		  // 是否加工机器号
	    m_bEnManuDay	  =0;		  // 是否加工日期
	    m_bEnManuTime     =0;		  // 是否加工时间
	    m_bEnLOTSn        =0;         // 是否加工LOT ID	
	    m_bEnManuString   =0;
		m_bEnLOTFix		  =0;           // 是否加工LOT ID	固定号 ly add 20121127
		m_bEnLOTInc		  =0;           // 是否加工LOT ID	流水号 ly add 20121127
		m_bEnLOTScale	  =0;			// 是否加工LOT ID	打涨缩 ly add 20121127
		m_bEnAxisNo		  =0;			// 是否加工轴号 ly add 20121230
		m_bOneAxis	 	  =0;//ly add 20140108
		m_iCurOneAxis	  =-1;//ly add 20140108
		m_bEn3Fid		  =0;           //是否允许3标靶加工 ly add 20130121
		m_bf3Fid		  =0;           //是否允许3标靶加工 综合上值及靶标勾选选项 ly add 20131108
		m_bChManScaleRange =0;//ly add 20140702  0手动设置涨缩值时不进行阈值管控，1手动设置涨缩值时进行阈值管控，超出阈值范围报警退出加工，阈值内的按照手动设定的涨缩加工
		m_bMaFindFid	  =0;			//是否允许手动找标靶 ly add 20130121

		m_strZoomSn	=2.4;
		m_bFileOpen		  =FALSE;	  //是否打开文件
		m_bToolsParaSet   =FALSE;	  //加工参数是否设定
		m_bLaserPowerTest =FALSE;	  //是否已激光功率测试
		m_bLaserWarmup	  =FALSE;	  //是否已激光预热
		m_bScanLabTest	  =FALSE;	  //是否振镜测试
		m_bAllHomed		  =FALSE;     //是否已回零
		m_bIsFiducialDo   =FALSE;	  //是否做过标靶定位
		m_bIsFiducialDo2[0]=FALSE;
		m_bIsFiducialDo2[1]=FALSE;
		m_bLaserPowerOn   =FALSE;     //激光是否上电
		m_bMachinePowerOn =TRUE;

		m_PCBWidth		  =0;		  // 当前PCB宽度
    	m_PCBHeight       =0;         // 当前PCB长度
		m_PCBCrdStartX    =0;		  // 当前PCB起始坐标X	
		m_PCBCrdStartY	  =0;		  // 当前PCB起始坐标Y

		//上下料
		m_LoadPitchPos	  =22000;    // 上料移动位置 (平台上方)	
		m_UnloadPitchPos  =22000;    // 下料移动位置 (平台上方)

		m_LoadBenchmark   =-2000;	  // 上料基准位置
		m_UnloadBenchmark =-2000;     // 下料基准位置
		m_LoadLiftBM	  =500;		  // 上料升降基准	
		m_UnloadLiftBM    =500;		  // 下料升降基准	
	    m_LoadTransPos    =11000;       // 上料转接位置（到转接板）
	    m_UnloadTransPos  =11000;       // 下料转接位置（到转接板）

		m_TestThicknessZPos	=1000;	  // 测试板厚的Z轴位置	
		m_lPCBThickness   =1000;		  // 当前Pcb板的厚度
		m_lPCBThicknessStd   =1000;		  // 当前Pcb板的标准厚度

		m_lTestPlsRelease =20;	      // 测试用脉冲时间	
		m_lTestPlsPeriod  =1000;		  // 测试用脉冲周期	
		m_lTestJumpDelay  =400;	  // 测试用脉冲时间	
		m_lTestJumpSpeed  =4000;	  // 测试用脉冲时间	
		m_lTestLaserOnTime=30;	      // 测试用脉冲时间	

	//正常加工时
		m_lProcJumpDelay  =1000;	// 加工用跳转延时	
		m_lProcJumpSpeed  =1000;	// 加工用跳转速度
		m_lProcJumpDelay0 =260;		// 零跳转延时  //ly add 20111123	
		m_lProcJumpLenth  =6000;	// 跳转阈值长度
		m_iRTC5AddBasicDelay=0;
		m_iRTC5TestBasicDelay=0;
		m_lProcFirstJumpDelay =0;		// 是否打开第一发人为延时功能  //ly add 20111123 =1	按照间距值，=2按照时间值
		m_lProcFirstDelayGap  =1000;	// 第一发人为延时，设置的间距值。小于此值进行人为延时。=470	// 第一发人为延时，设置的间距值。计算振镜跳转延时时间。人为延时将小于此时间的跳转人为延时到此延时时间。
		m_lProcOtherJumpDelay =0;		// ly add 20120811是否打开其他发人为延时功能   =1	按照间距值，=2按照时间值
		m_lProcOtherDelayGap  =1000;	//ly add 20120811 其他发人为延时，设置的间距值。小于此值进行人为延时。=470	// 其他发人为延时，设置的间距值。计算振镜跳转延时时间。人为延时将小于此时间的跳转人为延时到此延时时间。
		m_lProcDelayJump =0;//ly add 20130315  先延时后跳转或者先跳转后延时。  0：先延时后跳转   1：先跳转后延时
		m_lMaxDutycycle = 0.2;
		m_lNULLMark= 0;//ly add 20120206
		m_AOMLaserOnDelay=25;
		m_AOMLaserOffDelay=4;
		m_lTestMode=0;//ly add 20120208
		m_laserComp=0;//ly add 20120919 激光功率补偿
		m_laserTestComp=0;//ly add 20121227 激光功率测试补偿
		m_LoadOptimize=0;//ly add 20120919 

	    m_lDrlRegJumpSpeed   = 4000;   // 
	    m_lDrlRegJumpDelay   = 1000;   //
		m_lDrlRegPlsTimes = 5;
		m_lDrlRegPointDis = 100;
	    m_lDrlRegPlsRelease  = 10;     // 
		m_lDrlRegPls2Release  = 10;     // 
		m_lDrlRegPls3Release  = 10;     // 
		m_lDrlRegPls4Release  = 10;     // 
		m_lDrlRegPls5Release  = 10;     // 
	    m_lDrlRegPlsPeriod   = 1000;   //
        m_lDrlRegApertureNo  = 2;      //
	    m_lDrlRegPulseNum    = 2;      //
		m_isDrillRegion=TRUE;
   // 校正
	    m_lAdjustJumpSpeed   = 1000;   // 
	    m_lAdjustJumpDelay   = 1000;   //
	    m_lAdjustPlsRelease  = 10;     // 
	    m_lAdjustPlsPeriod   = 1000;   //

		m_strNoProcessID="";
		m_strMachineSn    = "HANS";      // 机器号
		m_strLOTId		  = "LotID";      // LOT ID号
		m_strLOTIdFix	  = "LotID";      // LOT ID号 固定号 ly add 20121127
		m_strLOTIdInc	  = "01";      // LOT ID号 流水号 ly add 20121127
		m_strToolFileName = "";
		m_strFileName     = "";	 
		m_ulProcedPCBNum  =0;
		m_ProcMode = EXTERNALMARKPROC;
        m_bManuFindFidcial = FALSE;

		m_lDoAdjtimer  =0;
		m_lLaserTestTimer = 0;
		m_bUIManSetScale=0;//ly add 20140504
		m_bUseRefScale=0;//ly add 20140504
		m_bManSetBoardScale = 0;//1:手工设定PCB涨缩;0:自动计算
		m_bManScaleisCheck=FALSE;
		m_fManualScaleX = 1.0;
		m_fManualScaleY = 1.0;
		m_lMainFiduPolarity = 0;
		m_lInnerFiduPolarity = 0;
		m_iPlusCounterFunc = 0;

		//infraed
		for (i=0;i<6;i++)
		  for (int j=0;j<2;j++)
		    	m_infraredSetVakue[i][j]=1;
	};
			
	BOOL		m_bIsRecordPowerPara;			// 记录是不是要记录能量参数
	int			m_SaveLogFlag;					// 日志是不是要存储的标记
	CString		BeforeStr,AfterStr;             // 用在日志上
	MotionSpeed m_sysMotionPara[AXISNUM];       // 运动参数

//	long		m_lBETType;                     // ly add 20110420 BET偏移类型，0-以前算法，根据第二镜片计算第三镜片，1-偏移方案1，2-偏移方案2
//	long		m_lBETFactor;                   // ly add 20110420 光束倍率 100:1.0;95:0.95...
//	long        m_lBETOffsetX[APTNUM];          // ly add 20110420 第二镜片偏移
//	long        m_lBETOffsetY[APTNUM];          // ly add 20110420 第三镜片偏移

    long        m_lBETOffset[APTNUM];			// 对应光圈1的偏移
	long        m_lFactualAperture[APTNUM];		// 对应实际光圈1编号
	long        m_lBETOffset2[APTNUM];          // 对应光圈2的偏移
	long        m_lFactualAperture2[APTNUM];	// 对应实际光圈2编号

	Coord3D		m_triTestLongPathCCDToGlvOffL;  // 振镜校正  长路径激光加工测试点位置
	Coord3D		m_triTestLongPathCCDToGlvOffR;	// 振镜校正  加工测试点位置
	Coord3D		m_triTestCCDToGlvOffL;			// 振镜校正  加工测试点位置
	Coord3D		m_triTestCCDToGlvOffR;			// 振镜校正  加工测试点位置
	Coord3D		m_triTestCCDToCCDOffL;			// CCDTOCCD测试点位置
	Coord3D		m_triTestCCDToCCDOffR;			// CCDTOCCD试点位置
	
//	Coord3D   	m_triCCDToGlvSysOffsetLT;		// 系统振镜与CCD之间安装偏移 CCD测试测试高度
//	Coord3D   	m_triCCDToGlvSysOffsetRT;		// 系统振镜与CCD之间安装偏移 CCD测试测试高度
	
	Coord3D   	m_triSCCDToGlvSysOffsetLT;		// 短光路系统振镜与CCD之间安装偏移 CCD测试测试高度
	Coord3D   	m_triSCCDToGlvSysOffsetRT;		// 短光路系统振镜与CCD之间安装偏移 CCD测试测试高度
	Coord3D   	m_triLCCDToGlvSysOffsetLT;		// 长光路系统振镜与CCD之间安装偏移 CCD测试测试高度
	Coord3D   	m_triLCCDToGlvSysOffsetRT;		// 长光路系统振镜与CCD之间安装偏移 CCD测试测试高度
	
	Coord		m_crdPathOffsetLT;
	Coord		m_crdPathOffsetRT;
	
	Coord3D		m_triLaserPowerTestL;		// 激光测试位置
	Coord3D		m_triLaserPowerTestR;		// 激光测试位置
	
	Coord  	    m_crdLaserTestCleanRef;		// 功率测试位 与 清理位 相对位置
	Coord       m_crdCCDDistance;			// 两个CCD位置间距  Unit: p
    Coord       m_crdGlvDistance;			// 两个振镜的 间距  Unit: p
    Coord       m_crdProcGlvOffset;			// 加工过程中右侧 Glavo 相对偏差 Unit: p
	
	long		m_lMotionCardSn1;			// 运动卡1的序列号
	long		m_lMotionCardSn2;			// 运动卡2的序列号
	long		m_lMotionCardSn3;			// 运动卡3的序列号	
	
	long		m_lGlvAdjustApt;			// 振镜校正glv光圈
	long		m_lLongPathGlvAdjustApt;	// 长路径振镜校正glv光圈
	long		m_lAptOffsetCrd;			// 光圈 零点偏置
	long        m_lBETOffsetCrd;			// BET零点偏置
//第二套BET光圈参数
    long		m_lAptOffsetCrd2;      
	long        m_lBETPriOffset2;      
	long        m_lBETSubOffsetCrd2;      
	
	long		m_lCCDFocusPosL;			// CCD自动加工焦距 L
	long		m_lCCDFocusPosR;			// CCD自动加工焦距 R
	
	//光源亮度参数 yutingxun-----------------------------
	//外层标靶
    long        m_lCCDLumLC_OUT;           // 光源亮度
    long        m_lCCDLumLR_OUT;   
	long        m_lCCDLumRC_OUT;           // 光源亮度
    long        m_lCCDLumRR_OUT;  
	//内层标靶	
	long        m_lCCDLumLC_INS;           // 光源亮度
    long        m_lCCDLumLR_INS;   
	long        m_lCCDLumRC_INS;           // 光源亮度
    long        m_lCCDLumRR_INS;  
	//原点校正
	long        m_lCCDLumLC_EME;           // 光源亮度
    long        m_lCCDLumLR_EME;   
	long        m_lCCDLumRC_EME;           // 光源亮度
    long        m_lCCDLumRR_EME;  
	//点阵校正
	long        m_lCCDLumLC_GLV;           // 光源亮度
    long        m_lCCDLumLR_GLV;   
	long        m_lCCDLumRC_GLV;           // 光源亮度
    long        m_lCCDLumRR_GLV;
	//CCD校正
	long        m_lCCDLumLC_CCD;           // 光源亮度
    long        m_lCCDLumLR_CCD;   
	long        m_lCCDLumRC_CCD;           // 光源亮度
    long        m_lCCDLumRR_CCD;
	//LocalMark
	long        m_lCCDLumLC_LM;           // 光源亮度
    long        m_lCCDLumLR_LM;   
	long        m_lCCDLumRC_LM;           // 光源亮度
    long        m_lCCDLumRR_LM;	
	//红外线光源
	long m_infraredSetVakue[6][2];
	///-------------------------------------------------
	long		m_lLaserDrillPosL;	  // 激光自动加工打孔焦距 L
	long		m_lLaserDrillPosR;    // 激光自动加工打孔焦距 R
	long		m_lLongPathLaserDrillPosL;	  // 长路径激光自动加工打孔焦距 L
	long		m_lLongPathLaserDrillPosR;    // 长路径激光自动加工打孔焦距 R
	long		m_lPCBRecorder;       // 已加工PCB板的总数	
	long        m_lPCBHoleCount;      // 孔数
	long        m_lPCBDrilledHoleCount;      //已加工孔数
	long        m_lPCBCurArea;      //当前加工区域
	long        m_lErrorPCB;      //当前涨缩超差的报错板数 ly add 20120116
	
	long		m_lProcessDir;        // 加工方向
	long		m_lAutoProc;		  // 是否手动加工
	long		m_lProcSide;		  // 加工标识面（正面/反面）
    long		m_LaserWorkTime;	  //激光器工作总时间
	time_t		LPStartTime,LPEndTime;//ly add 20130114
	long		m_lScanSize;          // 加工模块大小（方阵）
	//	long		m_AutoThithick;//自动测厚
	
	
	double      m_strZoomSn;			//字符大小
	long		m_lDirMachSn;		  // 机器号方向
	long		m_lDirManuDay;		  // 加工日期方向
	long		m_lDirManuTime;	 	  // 加工时间方向
	// 测试用
	long		m_lTestPlsRelease;	  // 测试用脉冲时间	
	long		m_lTestPlsPeriod;	  // 测试用脉冲周期	
	long		m_lTestJumpDelay;	  // 测试用跳转延时	
	long		m_lTestJumpSpeed;	  // 测试用跳转速度
	long		m_lTestLaserOnTime;	  // 测试用脉冲时间	
	long		m_lWarmUpPlsRelease;  // 预热测试用脉冲时间	//机器预热
	
	//正常加工时
	long		m_lProcJumpDelay;	  // 加工用跳转延时	
	long		m_lProcJumpSpeed;	  // 加工用跳转速度
	long		m_lProcJumpDelay0;	  // 零跳转延时	  //ly add 20111123
	long		m_lProcJumpLenth;	  // 跳转阈值长度  //ly add 20111123
	long         m_iRTC5AddBasicDelay;  //RTC5多台计算延时后认为改变一个数
	long m_iRTC5TestBasicDelay;//用于，振镜打字符，开窗，等测试的延时
	long        m_lProcFirstJumpDelay ;		// 是否打开第一发人为延时功能  //ly add 20111123	
	long		m_lProcFirstDelayGap  ;	// 第一发人为延时，设置的间距值。小于此值进行人为延时。
	long		m_lProcFirstDelayGapTime ;	// 第一发人为延时，设置的间距值。由此间距计算振镜跳转延时时间。人为延时将小于此时间的跳转人为延时到此延时时间。
	long        m_lProcOtherJumpDelay ;		// 是否打开其他发人为延时功能  //ly add 20120811	
	long		m_lProcOtherDelayGap  ;	// 其他发人为延时，设置的间距值。小于此值进行人为延时。//ly add 20120811
	long        m_lProcDelayJump ;		//ly add 20130315  先延时后跳转或者先跳转后延时。  0：先延时后跳转   1：先跳转后延时
	double		m_lMaxDutycycle;//占空比阈值
	long		m_lNULLMark;//ly add 20120206
	long		m_AOMLaserOnDelay;
	long		m_AOMLaserOffDelay;
	long		m_lTestMode;//ly add 20120208
	
    //加工内层标靶
	long        m_lDrlRegJumpSpeed;   // 
	long        m_lDrlRegJumpDelay;   //
	long        m_lDrlRegPlsTimes;  //
	long		m_lDrlRegPointDis;
	long        m_lDrlRegPlsRelease;  // 
	long        m_lDrlRegPls2Release;  // 
	long        m_lDrlRegPls3Release;  // 
	long        m_lDrlRegPls4Release;  // 
	long        m_lDrlRegPls5Release;  // 
	long        m_lDrlRegPlsPeriod;   //
    long        m_lDrlRegApertureNo;  //
	long        m_lDrlRegPulseNum;    //
	BOOL m_isDrillRegion;
	
	//加工字符参数
	long        m_lDrlTxtJumpSpeed;   // 
	long        m_lDrlTxtJumpDelay;   //
	long        m_lDrlTxtPlsRelease;  // 
	long        m_lDrlTxtPlsPeriod;   //
    long        m_lDrlTxtApertureNo;  //
	long        m_lDrlTxtPulseNum;    //
	
	//
	long		m_lAdjustApertureNo;
	long        m_lLongPathAdjustApertureNo;
	long        m_lAdjustJumpSpeed   ;   // 
	long        m_lAdjustJumpDelay   ;   //
	long        m_lAdjustPlsRelease  ;     // 
	long        m_lAdjustPlsPeriod   ;   //
	
	////////
	long        m_ulAdjPlslRelease;
    long       	m_lAdjPosX;
	long       	m_lAdjPosY;
	//CCD thredhold
    long		m_lCCDAdjustThreshold;
	long		m_lCCDProcThreshold;
	long		m_lCCDProcInnerThreshold;
	long		m_lCCDProcInnerRange;//ly add 20121009
	long		m_lTableDelay; //ly add 20121013
	long		m_ulAdjTime;     //振镜校正时间间隔
	long		m_ulLaserPowerTime; //激光能量测试时间间隔
	CString     m_OperationRateTime;
	CString     m_OperationRateTimeNight;
	
	long		m_lLaserTestTimer;   //测试激光能量时刻
	long		m_lDoAdjtimer;       //振镜校正时刻
	//
	UINT		m_ulProcedPCBNum;     //已经加工板数
    long        m_ulSLBitPermm;       //振镜每毫米的比特数
	
	CRD			m_PCBWidth;			  // 当前PCB宽度
    CRD			m_PCBHeight;          // 当前PCB长度
	CRD			m_PCBCrdStartX;		  // 当前PCB起始坐标X	
	CRD			m_PCBCrdStartY;		  // 当前PCB起始坐标Y
	
	Coord		m_crdFileToReal;	  // 文件与系统的相对位置
	Coord        m_crdFileToReal2[2];
	
	Coord		m_crdTabBenchmark;    // 相对回零点的距离
	Coord		m_crdTabLoadPos;	  // 平台接料位置	
	Coord		m_crdTabUnloadPos;	  // 平台送料位置 	
	
	Coord		m_crdOVerTabLoadPos;	  // 平台接料位置	
	Coord		m_crdOVerTabUnloadPos;	  // 平台送料位置 
	
    Coord       m_crdTabPitchDisXY;   // 平台定位时要移动的距离
	
	//上下料
	CRD			m_LoadPitchPos;		  // 上料移动位置 到平台上空	
	CRD			m_UnloadPitchPos;	  // 下料移动位置
	CRD	        m_LoadBenchmark;	  // 上料基准位置
	CRD 	    m_UnloadBenchmark;    // 下料基准位置
	CRD         m_LoadTransPos;       // 上料转接位置（到转接板）
	CRD         m_UnloadTransPos;       // 上料转接位置（到转接板）
	CRD			m_LoadTunePos;
	CRD			m_UnLoadTunePos;
	
	CRD			m_LoadLiftBM;		  // 上料升降基准	
	CRD			m_UnloadLiftBM;		  // 下料升降基准	
	
	CRD			m_TestThicknessZPos;  //测试板厚的Z轴位置	
	
	long		m_lPCBThickness;	  //当前PCB板的厚度
	long		m_lPCBThicknessStd;	  //当前PCB板的标准厚度	
	
	BOOL		m_bEnMachSn;		  // 是否加工机器号
	BOOL		m_bEnManuDay;		  // 是否加工日期
	BOOL		m_bEnManuTime;		  // 是否加工时间
	BOOL		m_bEnLOTSn;           // 是否加工LOT ID	
	BOOL		m_bEnManuString;
	BOOL		m_bEnLOTFix;           // 是否加工LOT ID	固定号 ly add 20121127
	BOOL		m_bEnLOTInc;           // 是否加工LOT ID	流水号 ly add 20121127
	BOOL		m_bEnLOTScale;           // 是否加工LOT ID	打涨缩 ly add 20121127
	BOOL		m_bEnAxisNo;    //ly add 20121230
	BOOL		m_bOneAxis;//ly add 20140108
	int			m_iCurOneAxis;//ly add 20140108
	BOOL		m_bEn3Fid;     //ly add 20130121
	BOOL		m_bf3Fid;     //ly add 20131108
	BOOL		m_bChManScaleRange;//ly add 20140702
	BOOL		m_bMaFindFid;     //ly add 20130121是否手动找标靶
	int			m_iLFidNum;//当前左平台板加工使用标靶数量//ly add 20130121
	int			m_iRFidNum;//当前右平台板加工使用标靶数量//ly add 20130121
	BOOL		m_bLFidEn[4];//ly add 20130121
	BOOL		m_bRFidEn[4];//ly add 20130121
	int			m_iLInnFidNum;//当前左平台板加工使用Inner标靶数量//ly add 20130121
	int			m_iRInnFidNum;//当前右平台板加工使用Inner标靶数量//ly add 20130121
	BOOL		m_bLInnFidEn[4];//ly add 20130121
	BOOL		m_bRInnFidEn[4];//ly add 20130121
	
	long		m_fileunit;//ly add 20120516 ---------------
	long		m_filemode ;
	long		m_fileformat;
	long		m_filedecnum;
	long		m_fileintnum;
	float		m_fLaserPw[5];//ly add 20140527
	long		m_iOutFidsOffset;//ly add 20140504
	long		m_iFZInnerOffset;//ly add 20120522
	BOOL		m_bTableClamp;//ly add 20120523
	int         m_ilaserPowerPattern;//jpc add 20130806
	BOOL		m_bUse9112;//ly add 20130807
	HANDLE m_hPowerCom;
	
	BOOL		m_bScaleUnit;//ly add 20130625----------------
	BOOL		m_bPowerMax;
	BOOL		m_bWaterYBJ;
	long		m_lCCDContrastThrd;//ly add 20140328
	int			m_iScanSizeMax;//ly add 20140308
	int			m_iLargeTable;
	long		m_lTableWidth;
	long		m_lTableHeight;//ly add 20140308
	int			m_iDoorOpen;//ly add 20140418
	int	m_isInfrared;
	int m_isHandCOMNum,m_isPowerCOMNum;
	
	BOOL		m_bFZInnerMark;
	BOOL		m_bZHANHUARotate;
	BOOL m_bShunluoScale;//顺络涨缩
	int m_bShenLan3Fid;
    BOOL m_bGYDmirror;//光韵达为了在高级用户下面屏蔽镜像功能
	int m_bFunctionOverBorad;//是否开启翻板机
	BOOL		m_bShowTool;//ly add 20140520
	BOOL		m_bLoadAfterPitch;//ly add 20140520
	BOOL		m_bFileLPowerTest;//ly add 20130801
	double		m_dFileAptLPower;//ly add 20130801
	long		m_lAptDelay[18];//ly add 20131223
	long		m_lFORWARDX;//ly add 20130805---
	long		m_lREVERSEX;
	long		m_lFORWARDY;
	long		m_lREVERSEY;//ly add 20130805---
	BOOL		m_bFitBit;//ly add 20130724
	BOOL		m_bFitApt;//ly add 20131223
	BOOL		m_bDrillInc;//ly add 20140702
	BOOL		m_bDrillH01H02;//ly add 20140702
    BOOL		m_bLaserPowerMode;//ly add 20140702
	BOOL		m_bLaserPowerShow;//ly add 20140702
	long		m_bLaserPowerDelayTime;
	int			m_ilaserPowerTimes;
	BOOL		m_isNullPrecessHoles;
	BOOL		m_bNewDelay;
	BOOL		m_bBurstMode;
	
	long		m_lBET1F;					 
	long		m_lBET2F;				
	long		m_lBET3F;					
	double		m_dBET1TOBET2;				
	double		m_dBET2TOBET3;			
	long		m_lBETMAX;//ly add 20130625-----------------
	
	BOOL		m_bMatch;//ly add 20130724
	double		m_bMatchScore;//ly add 20130724
	
	double		m_dLScaleX;//ly add 20131021
	double		m_dLScaleY;
	double		m_dRScaleX;
	double		m_dRScaleY;
	long		m_lLNum;
	long		m_lRNum;
	CString		m_strLastFile;//ly add 20131021---
	
	BOOL		m_bFileOpen;		  // 是否打开文件
	BOOL		m_bToolsParaSet;	  // 加工参数是否设定
	BOOL		m_bLaserPowerTest;	  // 是否已激光功率测试
	BOOL		m_bLaserWarmup;		  // 是否已激光预热
	BOOL		m_bScanLabTest;		  // 是否振镜测试
	BOOL  	    m_bAllHomed;	      // 是否已回零	
	BOOL		m_bIsFiducialDo;
	BOOL        m_bIsFiducialDo2[2];
	
	BOOL		m_bLaserPowerOn;      // 是否激光上电
	BOOL		m_bMachinePowerOn;		//是否机器上上电 7-19
	BOOL        m_bManuFindFidcial;   // 是否手动找标靶
    PROCMODE	m_ProcMode;
	
	CString		m_strMachineSn;       // 机器号
	CString		m_strNoProcessID;//不加工的批次号，专为烟台富士康
	CString		m_strLOTId;           // LOT ID号
	CString		m_strToolFileName;    // 工具文件
	CString		m_strFileName;		  // 工具文件
	CString		m_strLOTIdFix;           // LOT ID号 固定号 ly add 20121127
	CString		m_strLOTIdInc;           // LOT ID号 流水号 ly add 20121127
	
	CString     m_strAppPath;         // 应用文件的执行路径
	
	ToolModel   m_tmToolsPara;        // 工具刀具参数
	ToolModelSet m_tmToolsParaSet;    //新 工具刀具参数
	
	MotionPathV m_MotionPath;		  // 工作台的移动轨迹
	
	SubareaV	m_SubArea;			  // 分区 包括 （中点、每个孔的信息）
	
	//    HolePositionV   m_FiducialRealPosL;  // fiducial vector   Unit:mm
	//    HolePositionV   m_FiducialRealPosR;  // fiducial vector
	
    HoleCoordV   m_FiducialRealPosL;  // fiducial vector   Unit:mm
    HoleCoordV   m_FiducialRealPosR;  // fiducial vector
	
	HolePositionV   m_FiducialOffset;    // Large Window Offset
    AxisPosErr  m_AxisXPosErr;        //
	AxisPosErr  m_AxisYPosErr;        //轴误差补偿值
	
    UserInfo 	m_CurUserInfo;
    UserInfoV   m_UserInfo;
	///工艺类型
	bool        m_TechnicType;
	
	int			m_MirrorFlag;
	int			m_RotateFlag;//ly add 20120828
	

	friend SystemDoc& GetDoc();                           
	friend MotionSpeed& GetMotionPara(int iAxisNo);
};

#endif // !defined(AFX_SYSPARAMETER_H__A4EE69C3_0646_4077_9A2B_F65410B72EC7__INCLUDED_)
