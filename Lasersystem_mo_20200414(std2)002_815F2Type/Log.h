// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__9FC5695A_D904_489C_B0F9_B022C90C20C6__INCLUDED_)
#define AFX_LOG_H__9FC5695A_D904_489C_B0F9_B022C90C20C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AdoClass/ado.h"
#include <Vector>
///////////////////
class CLog  
{
/////////////////////////////////////////////////////////////////
public:												//20160901
	_RecordsetPtr GetBillHandSNAlarm();
	_RecordsetPtr GetBillHandSNAxisStatus();
	_RecordsetPtr GetBillHandSNLightStatus();
	_RecordsetPtr GetBillHandSNOtherStatus();
	_RecordsetPtr GetBillHandSNWork();

	void AppendSNAlarmTable(CString alarmMSG,COleDateTime  workTime);
	void AppendSNAxisStatusTable(CString leftStatus,CString rightStatus,COleDateTime  workTime);
	void AppendSNLightStatusTable(int type,COleDateTime  workTime);
	void AppendSNOtherStatusTable(CString status,COleDateTime  workTime);
	void AppendSNWorkTable(CString lotID,CString employeeID,CString program,CString procCount,COleDateTime  workTime);
/////////////////////////////////////////////////////////////////
public:
	CLog();
	virtual ~CLog();
public:
	bool InitLog();
	BOOL BackupAllLogData(CWnd* pParent);

	void LoadCalc(CString &Head,CString &Pcbname, CString &x, CString &y, CString &PitchTime,CString &Time,int &holes,CString &isNgOK,CString &fileName1,CString &fixedNo,CString &increasingNo);
	void LoadCalcFuShikang(CString &Head,CString &Pcbname, CString &x, CString &y, CString &rPCBx, CString &rPCBy, CString &PitchTime,CString &Time,int &holes,CString &isNgOK,CString &fileName1,CString &fixedNo,CString &increasingNo);
	void CalcMoveNext();
	void CalcMoveFirst();
	bool isCalcEOF();
	void SetSort();
	
	void LoadProForUpload(CString &glvAdjPresionL,CString &glvAdjPresionR);
	void LoadPro(CString &Oprate,CString &Result, CString &Remark, CString &Time);
	void ProMoveNext();
	void ProMoveFirst();
	void ProMoveLast();
	bool ProMovePrevious();
	bool isProEOF();
	bool isProBOF();

	void LoadStatusTableV(long &starPods,long &endPods,vector<CString> &csVet);
	void LoadStatusTable(CString &Sequence, CString &status, CString &Time);
	void LoadStatusTable(long &RecordSetPods, CString &Sequence, CString &status, CString &Time);
	long GetStatusTableAbsolutePosition();
	void StatusTableMoveNext();
	bool isStatusTableEOF();

	void LoadLightStatusTable(CString &lampStatus, COleDateTime &workTime);
	bool isLightStatusTableEOF();
	void LightStatusTableMoveFirst();
	void LightStatusTableMoveNext();

	void LoadPowerForUpload(CString &powerL,CString &powerR);
	void LoadPower(CString &Head,CString &Power, CString &DiffTime, CString &Time ,CString &TestPlsRelease, CString &TestPlsPeriod,CString &Aperture);
	void LoadPowerResult(CString &Head,CString &Power, CString &DiffTime1, CString &Time ,CString &TestPlsRelease, CString &TestPlsPeriod,CString &Aperture,CString &result);
	void PowerMoveNext();
	void PowerMoveFirst();
	void PowerMoveLast();
	bool PowerMovePrevious();
	bool isPowerEOF();
	bool isPowerBOF();

	void LoadPowerpara(CString &FileName, CString &PowerPara,CString &LotId, CString &Time);
	void PowerParaMoveNext();
	void PowerParaMoveFirst();
	bool isPowerParaEOF();

	_RecordsetPtr GetBillHandCalc();
	_RecordsetPtr GetBillHandPro();
	_RecordsetPtr GetBillHandPower();
	_RecordsetPtr GetBillHandPowerPara();
	_RecordsetPtr GetBillHandTimeAnalyer();

	void Append_calc(CString head,CString PCBName,float x,float y,float PitchTime,CString isOK="NG",long holes=0,CString filename1="NO",CString fixedNo="NO",CString increasingNo="NO");

	void Append_pro(CString operation,CString prompt,CString remark = " ");//TestTime
	void Append_pro(CString operation,long pro,CString remark = " ");//TestTime
	void Append_pro(long op,long pro,long re);
	void Append_pro(long op,long pro,CString remark="");
	void Append_pro(long op,CString prompt,CString remark="");

	void Append_Power(CString head,float valuepower,CString TestTime = "0",int TestPlsRelease=0,int TestPlsPeriod=0,int  TestAperture =0);
	void Append_Power(long hd,float value,CString TestTime,int TestPlsRelease,int TestPlsPeriod,int TestAperture);//ly add 20110530

	void Append_PowerPara(CString sPcbName,CString PowerPara,CString sLotId = "");

	void AppendTimeAnalyer(COleDateTime  beginTime,COleDateTime endTime,int minutes);
	
	bool ConnectCalcSet(CString &sLogName);
	bool ConnectProSet(CString &sLogName);
	bool ConnectPowerSet(CString &sLogName);
	bool ConnectPowerParaSet(CString &sLogName);

	friend CLog& GetLog();

private:
	bool DeleteRecord(int sel,CWnd* pParentWnd);
	
	CAdoConnection ObjCalc;							//加工轴、料号、涨缩、用时、孔数等相关信息
	CAdoRecordSet  ObjCalcSet;

	CAdoConnection ObjPro;							//参数设置变化、异常信息等
	CAdoRecordSet  ObjProSet;

	CAdoConnection Objpower;						//激光功率测量相关信息
	CAdoRecordSet  ObjPowerSet;

	CAdoConnection ObjPowerPara;					//加工用料号及能量设定相关参数
	CAdoRecordSet  ObjPowerParaSet;	

	CAdoConnection m_TimeAnalyerConnect;			//机器正常加工的用时统计	
	CAdoRecordSet  m_TimeAnalyerRecordSet;

	CAdoConnection m_SNDBConnect;					//20160901 深南电路用的相关信息收集
	CAdoRecordSet m_SNAlarmTableRecordSet,m_SNAxisStatusTableRecordSet,m_SNLightStatusTableRecordSet;
	CAdoRecordSet m_SNOtherStatusTableRecordSet,m_SNWorkTableRecordSet;
};

#endif // !defined(AFX_LOG_H__9FC5695A_D904_489C_B0F9_B022C90C20C6__INCLUDED_)
