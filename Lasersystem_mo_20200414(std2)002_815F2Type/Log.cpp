// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include "Log.h"
#include "ToolUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define bzero(a, b)             memset(a, 0, b)
bool bConnectok =true;
CString strDataBase[6]=
{
	"CalcResult.mdb",
	"OperResult.mdb",
	"LaserPower.mdb",
	"FileParame.mdb",
	"TimeAnalyser.mdb",
	"ShenNanDB.mdb"
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog()
{

}

CLog::~CLog()
{
	ObjCalc.Close();
	ObjPro.Close();
	Objpower.Close();
	ObjPowerPara.Close();
	m_TimeAnalyerConnect.Close();

	if (m_SNDBConnect.IsOpen())				//20160901
		m_SNDBConnect.Close();
}

CLog& GetLog()
{
	static CLog  log;
	return log;
}

bool CLog::InitLog()   
{
	char ez[256] = {""};

	CString strpath = GetDoc().GetAppPath()+strDataBase[0];
	if (ObjCalc.ConnectAccess((LPCTSTR)strpath))
		GetBillHandCalc();
	else
	{
		strncpy(ez,GetLang().GetWarningText(14001),256);
		AfxMessageBox(ez);//"���ݿ�CalcResult.mdb����ʧ��!"
		bConnectok = false;
		return false;
	}
	
	strpath = GetDoc().GetAppPath()+strDataBase[1];
	if (ObjPro.ConnectAccess((LPCTSTR)strpath))
		GetBillHandPro();	
	else
	{
		strncpy(ez,GetLang().GetWarningText(14002),256);
		AfxMessageBox(ez);//"���ݿ�OperResult.mdb����ʧ��!"
		bConnectok = false;
		return false;
	}
	
	strpath = GetDoc().GetAppPath()+strDataBase[2];
	if (Objpower.ConnectAccess((LPCTSTR)strpath))
		GetBillHandPower();
	else
	{
		strncpy(ez,GetLang().GetWarningText(14003),256);
		AfxMessageBox(ez);//"���ݿ�LaserPower.mdb����ʧ��!"
		bConnectok = false;
		return false;
	}
	
	strpath = GetDoc().GetAppPath()+strDataBase[3];
	if (ObjPowerPara.ConnectAccess((LPCTSTR)strpath))
		GetBillHandPowerPara();
	else
	{
		strncpy(ez,GetLang().GetWarningText(14004),256);
		AfxMessageBox(ez);//"���ݿ�FileParame.mdb����ʧ��!"
		bConnectok = false;
		return false;
	}
	
//�ӹ���ʱ���ݿ��RUN->END
	strpath = GetDoc().GetAppPath()+strDataBase[4];
	if (m_TimeAnalyerConnect.ConnectAccess((LPCTSTR)strpath))
		GetBillHandTimeAnalyer();
	else
	{
		AfxMessageBox("TimeAnalyser.mdb connect ERROR!");//"���ݿ�TimeAnalyser.mdb����ʧ��!"
		bConnectok = false;
		return false;
	}

	if(GetDoc().GetSysInfoDBMode()==1)										//20160901
	{
		strpath = GetDoc().GetAppPath()+strDataBase[5];
		//strpath = "E:\\Code\\Lasersystem Project\\Lasersystem_mo_20180921_scc\\"+strDataBase[5];							//20161129
		if (m_SNDBConnect.ConnectAccess((LPCTSTR)strpath))
		{
			GetBillHandSNAlarm();
			GetBillHandSNAxisStatus();
			GetBillHandSNLightStatus();
			GetBillHandSNOtherStatus();
			GetBillHandSNWork();
		}
		else
		{
			AfxMessageBox("���ݿ�ShenNanDB.mdb����ʧ��!");//"���ݿ�ShenNanDB.mdb����ʧ��!"
			bConnectok = false;
			return false;
		}
	}

	return true;
}

_RecordsetPtr CLog::GetBillHandTimeAnalyer()
{
	m_TimeAnalyerRecordSet.Close();
	m_TimeAnalyerRecordSet.SetAdoConnection(&m_TimeAnalyerConnect);
	m_TimeAnalyerRecordSet.SetCursorLocation(adUseClient);
	m_TimeAnalyerRecordSet.Open("analyse", adCmdTable);
	
	if(m_TimeAnalyerRecordSet.GetRecordCount()>0)
	{
		if (!m_TimeAnalyerRecordSet.IsEOF())
			m_TimeAnalyerRecordSet.MoveLast();	
	}

	return m_TimeAnalyerRecordSet.GetRecordset();
}

void CLog::AppendTimeAnalyer(COleDateTime beginTime,COleDateTime endTime,int minutes)
{	
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	m_TimeAnalyerRecordSet.MoveLast();
	m_TimeAnalyerRecordSet.AddNew();

	m_TimeAnalyerRecordSet.PutCollect("begintime",beginTime);	
	m_TimeAnalyerRecordSet.PutCollect("endtime",endTime);	
	m_TimeAnalyerRecordSet.PutCollect("minutes",minutes);	
	m_TimeAnalyerRecordSet.Update();
	
	m_TimeAnalyerConnect.BeginTrans();	
	m_TimeAnalyerConnect.CommitTrans();
}

void CLog::Append_calc(CString head,CString PCBName,float x,float y,float PitchTime,CString isOK,long holes,CString filename1,CString fixedNo,CString increasingNo)
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	int number;
	char szRead[256]={""};
	CString str;
	
	ObjCalcSet.MoveLast();
	number=ObjCalcSet.GetRecordCount();
	ObjCalcSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjCalcSet.PutCollect(str,number+1);//"���"
	
	strncpy(szRead,GetLang().GetWarningText(10155),256);
	str.Format("%s",szRead);
	ObjCalcSet.PutCollect(str,head);//"����̨"
	
	strncpy(szRead,GetLang().GetWarningText(10156),256);
	str.Format("%s",szRead);
	ObjCalcSet.PutCollect(str,PCBName);//"PCB��"
	
	ObjCalcSet.PutCollect("X",x);
	ObjCalcSet.PutCollect("Y",y);
	
	strncpy(szRead,GetLang().GetWarningText(10157),256);
	str.Format("%s",szRead);
	ObjCalcSet.PutCollect(str,PitchTime);//"��ʱ"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjCalcSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"
	
	ObjCalcSet.PutCollect("NG_OK",isOK);//"����̨"
	ObjCalcSet.PutCollect("Holes",holes);//"����̨"
	ObjCalcSet.PutCollect("FileName1",filename1);//"����̨"
	ObjCalcSet.PutCollect("FixedNo",fixedNo);//"����̨"
	ObjCalcSet.PutCollect("IncreasingNo",increasingNo);//"����̨"

	ObjCalcSet.Update();
	
	ObjCalc.BeginTrans();
	ObjCalc.CommitTrans();
}

void CLog::Append_pro(CString operation,CString prompt,CString remark)//CString operation,CString prompt,CString  remark
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	int number;
	CString str;
	char szRead[256]={""};	

	number=ObjProSet.GetRecordCount();
	if(number>0)
		ObjProSet.MoveLast();
	ObjProSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,number+1);//"���"

	strncpy(szRead,GetLang().GetWarningText(10151),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,prompt);//"����"

	strncpy(szRead,GetLang().GetWarningText(10152),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,operation);//"��ʾ����"

	strncpy(szRead,GetLang().GetWarningText(10153),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,remark);//"��ע"

	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjProSet.Update();
	
	ObjPro.BeginTrans();
	ObjPro.CommitTrans();
}

void CLog::Append_pro(CString operation,long pro,CString remark)//CString operation,CString prompt,CString  remark
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	CString str;
	int number;
	CString prompt;
	char szRead[256]={""};	

	strncpy(szRead,GetLang().GetLogText("prompt",pro),256);
	prompt.Format("%s",szRead);
	
	number=ObjProSet.GetRecordCount();
	if(number>0)
		ObjProSet.MoveLast();
	ObjProSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,number+1);//"���"

	strncpy(szRead,GetLang().GetWarningText(10151),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,prompt);//"����"

	strncpy(szRead,GetLang().GetWarningText(10152),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,operation);//"��ʾ����"

	strncpy(szRead,GetLang().GetWarningText(10153),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,remark);//"��ע"

	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjProSet.Update();
	
	ObjPro.BeginTrans();
	ObjPro.CommitTrans();
}

void CLog::Append_pro(long op,long pro,long re)//CString operation,CString prompt,CString  remark
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	int number;
	CString str;	
	CString operation, prompt, remark;
	char szRead[256]={""};

	strncpy(szRead,GetLang().GetLogText("operation",op),256);
	operation.Format("%s",szRead);
	strncpy(szRead,GetLang().GetLogText("prompt",pro),256);
	prompt.Format("%s",szRead);
	strncpy(szRead,GetLang().GetLogText("remark",re),256);
	remark.Format("%s",szRead);
	
	number=ObjProSet.GetRecordCount();
	if(number>0)
		ObjProSet.MoveLast();
	ObjProSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,number+1);//"���"

	strncpy(szRead,GetLang().GetWarningText(10151),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,prompt);//"����"

	strncpy(szRead,GetLang().GetWarningText(10152),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,operation);//"��ʾ����"

	strncpy(szRead,GetLang().GetWarningText(10153),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,remark);//"��ע"

	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjProSet.Update();
	
	ObjPro.BeginTrans();
	ObjPro.CommitTrans();
}

void CLog::Append_pro(long op,long pro,CString remark)//CString operation,CString prompt,CString  remark
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	int number;
	CString str;	
	CString operation, prompt;
	char szRead[256]={""};

	strncpy(szRead,GetLang().GetLogText("operation",op),256);
	operation.Format("%s",szRead);
	strncpy(szRead,GetLang().GetLogText("prompt",pro),256);
	prompt.Format("%s",szRead);
	
	number=ObjProSet.GetRecordCount();
	if(number>0)
		ObjProSet.MoveLast();
	ObjProSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,number+1);//"���"

	strncpy(szRead,GetLang().GetWarningText(10151),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,prompt);//"����"

	strncpy(szRead,GetLang().GetWarningText(10152),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,operation);//"��ʾ����"

	strncpy(szRead,GetLang().GetWarningText(10153),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,remark);//"��ע"

	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjProSet.Update();
	
	ObjPro.BeginTrans();
	ObjPro.CommitTrans();
}

void CLog::Append_pro(long op,CString prompt,CString remark)//CString operation,CString prompt,CString  remark
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	int number;
	CString str;	
	CString operation;
	char szRead[256]={""};

	strncpy(szRead,GetLang().GetLogText("operation",op),256);
	operation.Format("%s",szRead);
	
	number=ObjProSet.GetRecordCount();
	if(number>0)
		ObjProSet.MoveLast();
	ObjProSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,number+1);//"���"

	strncpy(szRead,GetLang().GetWarningText(10151),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,prompt);//"����"

	strncpy(szRead,GetLang().GetWarningText(10152),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,operation);//"��ʾ����"

	strncpy(szRead,GetLang().GetWarningText(10153),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,remark);//"��ע"

	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjProSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjProSet.Update();
	
	ObjPro.BeginTrans();
	ObjPro.CommitTrans();
}

void CLog::Append_Power(CString head,float valuepower,CString TestTime,int TestPlsRelease,int TestPlsPeriod,int TestAperture)
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;
	
	int number;
	char szRead[256]={""};
	CString str;

	ObjPowerSet.MoveLast();
	number=ObjPowerSet.GetRecordCount();
	ObjPowerSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,number+1);//"���"
	
	strncpy(szRead,GetLang().GetWarningText(10159),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,head);//"����ͷ"
	
	strncpy(szRead,GetLang().GetWarningText(10158),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,valuepower);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10160),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestTime);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10161),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestPlsRelease);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10162),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestPlsPeriod);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10163),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestAperture);//"���Թ�Ȧ"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"
	
    if (GetDoc().GetDrillInc())
	{
		str.Format("%s","���");

        CString state="NG";
		if((valuepower>(GetDoc().GetLaserPowerTestSt()*0.9))&&(valuepower<(GetDoc().GetLaserPowerTestSt()*1.1)))
			state="OK";

		ObjPowerSet.PutCollect(str,state);//���Խ��
	}

	ObjPowerSet.Update();
	
	Objpower.BeginTrans();	
	Objpower.CommitTrans();	
}

void CLog::Append_Power(long hd,float value,CString TestTime,int TestPlsRelease,int TestPlsPeriod,int TestAperture)
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;
	
	int number;
	CString str;
	char szRead[256]={""};
	CString head;

	strncpy(szRead,GetLang().GetLogText("operation",hd),256);
	head.Format("%s",szRead);

	ObjPowerSet.MoveLast();
	number=ObjPowerSet.GetRecordCount();
	ObjPowerSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,number+1);//"���"
	
	strncpy(szRead,GetLang().GetWarningText(10159),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,head);//"����ͷ"
	
	strncpy(szRead,GetLang().GetWarningText(10158),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,value);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10160),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestTime);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10161),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestPlsRelease);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10162),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestPlsPeriod);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10163),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,TestAperture);//"���Թ�Ȧ"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjPowerSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjPowerSet.Update();
	
	Objpower.BeginTrans();	
	Objpower.CommitTrans();
}

void CLog::Append_PowerPara(CString sPcbName,CString PowerPara,CString sLotId)
{
	if(!bConnectok)
		return;

//	if((GetDoc().GetSysInfoDBMode()==1)&&(GetDoc().GetCurUserLevel()==SystemDoc::ADMIN))				//20160901
//		return;

	int number;
	char szRead[256]={""};
	CString str;

	ObjPowerParaSet.MoveLast();
	number=ObjPowerParaSet.GetRecordCount();
	ObjPowerParaSet.AddNew();
	
	strncpy(szRead,GetLang().GetWarningText(10150),256);
	str.Format("%s",szRead);
	ObjPowerParaSet.PutCollect(str,number+1);//"���"
	
	strncpy(szRead,GetLang().GetWarningText(10164),256);
	str.Format("%s",szRead);
	ObjPowerParaSet.PutCollect(str,sPcbName);//"�Ϻ�"
	
	ObjPowerParaSet.PutCollect("PowerPara",PowerPara);
	ObjPowerParaSet.PutCollect("LOTID",sLotId);
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjPowerParaSet.PutCollect(str,COleDateTime::GetCurrentTime());//"ʱ��"

	ObjPowerParaSet.Update();

	ObjPowerPara.BeginTrans();
	ObjPowerPara.CommitTrans();
}

_RecordsetPtr CLog::GetBillHandCalc()
{	   
	ObjCalcSet.Close();
	ObjCalcSet.SetAdoConnection(&ObjCalc);
	ObjCalcSet.SetCursorLocation(adUseClient);
	ObjCalcSet.Open("calculate", adCmdTable);

	if(ObjCalcSet.GetRecordCount()>0)
	{ 
		if (!ObjCalcSet.IsEOF())
			ObjCalcSet.MoveLast();  
	}
	   
	return ObjCalcSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandPower()
{
	ObjPowerSet.Close();
	ObjPowerSet.SetAdoConnection(&Objpower);
	ObjPowerSet.SetCursorLocation(adUseClient);
	ObjPowerSet.Open("LaserPower", adCmdTable);

	if(ObjPowerSet.GetRecordCount()>0)
	{ 
		if (!ObjPowerSet.IsEOF())
			ObjPowerSet.MoveLast();	   
	}

	return ObjPowerSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandPowerPara()
{
	ObjPowerParaSet.Close();
	ObjPowerParaSet.SetAdoConnection(&ObjPowerPara);
	ObjPowerParaSet.SetCursorLocation(adUseClient);
	ObjPowerParaSet.Open("PowerPara", adCmdTable);

	if(ObjPowerParaSet.GetRecordCount()>0)
	{	
		if (!ObjPowerParaSet.IsEOF())
			ObjPowerParaSet.MoveLast();
	}

	return ObjPowerParaSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandPro()
{
	ObjProSet.Close();
	ObjProSet.SetAdoConnection(&ObjPro);
	ObjProSet.SetCursorLocation(adUseClient);
	ObjProSet.Open("Errprompt", adCmdTable);

	if(ObjProSet.GetRecordCount()>0)
	{
		if (!ObjProSet.IsEOF())
			ObjProSet.MoveLast();	
	}
	
	return ObjProSet.GetRecordset();
}

bool CLog::DeleteRecord(int sel,CWnd* pParentWnd)
{
	char szRead[256]={""};

	CProgressWnd wndProgress(pParentWnd, "Progress", TRUE);
	strncpy(szRead,GetLang().GetWarningText(14005),256);
	wndProgress.SetText(szRead);//"������־�����Ժ�...\n"

	CAdoConnection* pConnection;
	CAdoRecordSet* pRecordSet;

	switch(sel)
	{
		case 0:
			pConnection=&ObjCalc;
			pRecordSet=&ObjCalcSet;
			break;
		case 1:
			pConnection=&ObjPro;
			pRecordSet=&ObjProSet;
			break;
		case 2:
			pConnection=&Objpower;
			pRecordSet=&ObjPowerSet;
			break;
		case 3:
			pConnection=&ObjPowerPara;
			pRecordSet=&ObjPowerParaSet;
			break;
		case 4:
			pConnection=&m_TimeAnalyerConnect;
			pRecordSet=&m_TimeAnalyerRecordSet;
			break;
		case 5:
			pConnection=&m_SNDBConnect;
			pRecordSet=&m_SNAlarmTableRecordSet;
			break;
		case 6:
			pConnection=&m_SNDBConnect;
			pRecordSet=&m_SNAxisStatusTableRecordSet;
			break;
		case 7:
			pConnection=&m_SNDBConnect;
			pRecordSet=&m_SNLightStatusTableRecordSet;
			break;
		case 8:
			pConnection=&m_SNDBConnect;
			pRecordSet=&m_SNOtherStatusTableRecordSet;
			break;
		case 9:
			pConnection=&m_SNDBConnect;
			pRecordSet=&m_SNWorkTableRecordSet;
			break;
		default:
			return false;
	}

	pRecordSet->MoveLast();

	long maxnumb = pRecordSet->GetAbsolutePosition();
	wndProgress.SetRange(0,maxnumb);
	
	if(pRecordSet->IsBOF == pRecordSet->IsEOF)
		return false;
	
	int i=0;
	while(!pRecordSet->IsBOF())
	{
		pRecordSet->Delete();
		pRecordSet->MovePrevious();
		
		wndProgress.StepIt();
		if (wndProgress.Cancelled()) 
			break;
		
		i++;
		if(i>maxnumb)
			break;
	}
	
	pConnection->BeginTrans();									//20190102 ����˳��BC
	pConnection->CommitTrans();	

	return true;
}

void CLog::SetSort()
{
	char szRead[256]={""};
	CString str;

	strncpy(szRead,GetLang().GetWarningText(10165),256);
	str.Format("%s",szRead);

	ObjCalcSet.SetSort(str);//"ʱ�� asc"
}

bool CLog::isCalcEOF()
{
	if(ObjCalcSet.IsEOF())
		return true;
	else
		return false;
}

void CLog::CalcMoveFirst()
{
	if(ObjCalcSet.GetRecordCount()>0)
		ObjCalcSet.MoveFirst();	
}

void CLog::CalcMoveNext()
{
	if(ObjCalcSet.GetRecordCount()>0)
		ObjCalcSet.MoveNext();	
}

void CLog::LoadCalc(CString &Head,CString &Pcbname, CString &x, CString &y, CString &PitchTime,CString &Time,int &holes,CString &isNgOK,CString &fileName1,CString &fixedNo,CString &increasingNo)
{
	float tempx,tempy;
	
	char szRead[256]={""};
	CString str;
	
	strncpy(szRead,GetLang().GetWarningText(10155),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,Head);//"����̨"
	
	strncpy(szRead,GetLang().GetWarningText(10156),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,Pcbname);//"PCB��"
	
	ObjCalcSet.GetCollect("X",tempx);
	ObjCalcSet.GetCollect("Y",tempy);
	
	strncpy(szRead,GetLang().GetWarningText(10157),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,PitchTime);//"��ʱ"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,Time);//"ʱ��"
	
	x.Format("%f",tempx);
	y.Format("%f",tempy);
	
	ObjCalcSet.GetCollect("Holes",holes);
	ObjCalcSet.GetCollect("NG_OK",isNgOK);
	ObjCalcSet.GetCollect("FileName1",fileName1);
	ObjCalcSet.GetCollect("FixedNo",fixedNo);
	ObjCalcSet.GetCollect("IncreasingNo",increasingNo);
}

void CLog::LoadCalcFuShikang(CString &Head,CString &Pcbname, CString &x, CString &y, CString &rPCBx, CString &rPCBy, CString &PitchTime,CString &Time,int &holes,CString &isNgOK,CString &fileName1,CString &fixedNo,CString &increasingNo)
{
	float tempx,tempy;
	
	char szRead[256]={""};
	CString str;
	
	strncpy(szRead,GetLang().GetWarningText(10155),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,Head);//"����̨"
	
	strncpy(szRead,GetLang().GetWarningText(10156),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,Pcbname);//"PCB��"
	
	ObjCalcSet.GetCollect("X",tempx);
	ObjCalcSet.GetCollect("Y",tempy);
	
	strncpy(szRead,GetLang().GetWarningText(10157),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,PitchTime);//"��ʱ"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjCalcSet.GetCollect(str,Time);//"ʱ��"
	
	x.Format("%f",tempx);
	y.Format("%f",tempy);
	
	ObjCalcSet.GetCollect("Holes",holes);
	ObjCalcSet.GetCollect("NG_OK",isNgOK);
	ObjCalcSet.GetCollect("FileName1",fileName1);

	CString fixedNoFromDB="";
	ObjCalcSet.GetCollect("FixedNo",fixedNoFromDB);
	CString trimScale="";
	int n=fixedNoFromDB.Find("@");
	if (n!=-1)
	{
		fixedNo=fixedNoFromDB.Left(n);
		trimScale=fixedNoFromDB.Right(fixedNoFromDB.GetLength()-n-1);
		n=trimScale.Find("@");
		if (n!=-1)
		{
			rPCBx=trimScale.Left(n);
			rPCBy=trimScale.Right(trimScale.GetLength()-n-1);
		}
		else
			rPCBx=rPCBy="0";
	}
	else
	{
      rPCBx=rPCBy="0"; 
	  fixedNo=fixedNoFromDB;
	}

	ObjCalcSet.GetCollect("IncreasingNo",increasingNo);
}

bool CLog::isProBOF()
{
	if(ObjProSet.IsBOF())
		return true;
	else
		return false;
}

bool CLog::isProEOF()
{
	if(ObjProSet.IsEOF())
		return true;
	else
		return false;
}

bool CLog::isStatusTableEOF()
{
	if(m_SNOtherStatusTableRecordSet.IsEOF())
		return true;
	else
		return false;
}

void CLog::StatusTableMoveNext()
{
	m_SNOtherStatusTableRecordSet.MoveNext();
}

bool CLog::isLightStatusTableEOF()
{
	if(m_SNLightStatusTableRecordSet.IsEOF())
		return true;
	else
		return false;
}


bool CLog::isPowerParaEOF()
{
	if(ObjPowerParaSet.IsEOF())
		return true;
	else
		return false;
}

void CLog::ProMoveFirst()
{
	if(ObjProSet.GetRecordCount()>0)
		ObjProSet.MoveFirst();
}

bool CLog::ProMovePrevious()
{
	if(ObjProSet.GetRecordCount()>0)
		return SUCCEEDED(ObjProSet.MovePrevious());
	else
	{
		return false;
	}	
}

void CLog::ProMoveNext()
{
	ObjProSet.MoveNext();
}

void CLog::ProMoveLast()
{
	if(ObjProSet.GetRecordCount()>0)
		ObjProSet.MoveLast();
}

void CLog::PowerParaMoveFirst()
{
	if(ObjPowerParaSet.GetRecordCount()>0)
		ObjPowerParaSet.MoveFirst();
}

void CLog::PowerParaMoveNext()
{
	if(ObjPowerParaSet.GetRecordCount()>0)
		ObjPowerParaSet.MoveNext();
}

void CLog::LoadPro(CString &Oprate,CString &Result, CString &Remark, CString &Time)
{
	char szRead[256]={""};
	CString str;
	
	strncpy(szRead,GetLang().GetWarningText(10151),256);
	str.Format("%s",szRead);
	ObjProSet.GetCollect(str,Oprate);//"����"
	
	strncpy(szRead,GetLang().GetWarningText(10152),256);
	str.Format("%s",szRead);
	ObjProSet.GetCollect(str,Result);//"��ʾ����"
	
	strncpy(szRead,GetLang().GetWarningText(10153),256);
	str.Format("%s",szRead);
	ObjProSet.GetCollect(str,Remark);//"��ע"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjProSet.GetCollect(str,Time);//"ʱ��"
	
}

void CLog::LoadStatusTable(CString &Sequence, CString &status, CString &Time)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		long maxnumb = m_SNOtherStatusTableRecordSet.GetAbsolutePosition();
		long count = m_SNOtherStatusTableRecordSet.GetRecordCount();
		
		m_SNOtherStatusTableRecordSet.MoveLast();
		m_SNOtherStatusTableRecordSet.GetCollect("���",Sequence);
		m_SNOtherStatusTableRecordSet.GetCollect("״̬�л�",status);
		m_SNOtherStatusTableRecordSet.GetCollect("����ʱ��",Time);	
	}
}

void CLog::LoadStatusTable(long &RecordSetPods, CString &Sequence, CString &status, CString &Time)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		long maxnumb = m_SNOtherStatusTableRecordSet.GetAbsolutePosition();
		RecordSetPods = maxnumb;
		long count = m_SNOtherStatusTableRecordSet.GetRecordCount();
		
		m_SNOtherStatusTableRecordSet.MoveLast();
		m_SNOtherStatusTableRecordSet.GetCollect("���",Sequence);
		m_SNOtherStatusTableRecordSet.GetCollect("״̬�л�",status);
		m_SNOtherStatusTableRecordSet.GetCollect("����ʱ��",Time);	
	}
}

long CLog::GetStatusTableAbsolutePosition()
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		return m_SNOtherStatusTableRecordSet.GetAbsolutePosition();
	}
}

void CLog::LoadStatusTableV(long &starPods,long &endPods,vector<CString> &csVet)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		CString status;
		if (starPods == -1)
		{
			m_SNOtherStatusTableRecordSet.SetAbsolutePosition(1);
		}
		else
		{
			m_SNOtherStatusTableRecordSet.SetAbsolutePosition(starPods+1);
		}
		long curPods = m_SNOtherStatusTableRecordSet.GetAbsolutePosition();
		while (!m_SNOtherStatusTableRecordSet.IsEOF() && curPods <= endPods)
		{
			m_SNOtherStatusTableRecordSet.GetCollect("״̬�л�",status);
			csVet.push_back(status);
			m_SNOtherStatusTableRecordSet.MoveNext();
			curPods++;
		}
		m_SNOtherStatusTableRecordSet.SetAbsolutePosition(endPods);
	}

}


void CLog::LoadProForUpload(CString &glvAdjPresionL,CString &glvAdjPresionR)
{
	char ez[256]={""};
	CString Opreate,Result,Remark,Time;
	bool hasValueL = false;
	bool hasValueR = false;
	GetLog().ProMoveLast();
	while(!GetLog().isProBOF())
	{
		GetLog().LoadPro(Opreate,Result,Remark,Time);
		if (Result=="�Ҳ��񾵲�����ƫ��" && !hasValueR)
		{
			glvAdjPresionR=Remark;	
			hasValueR = true;
		}
		if (Result=="����񾵲�����ƫ��" && !hasValueL)
		{
			glvAdjPresionL=Remark;
			hasValueL = true;
		}
		if(hasValueL && hasValueR)
		{
			break;
		}
		GetLog().ProMovePrevious();
	}
}


void CLog::LoadLightStatusTable(CString &lampStatus, COleDateTime &workTime)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		if(m_SNLightStatusTableRecordSet.GetRecordCount() == 0)
		{
			return;
		}
		m_SNLightStatusTableRecordSet.GetCollect("�̵�",lampStatus);//"�̵�"
		m_SNLightStatusTableRecordSet.GetCollect("����ʱ��",workTime);			
	}
}

void CLog::LightStatusTableMoveFirst()
{
	if(m_SNLightStatusTableRecordSet.GetRecordCount()>0)
		m_SNLightStatusTableRecordSet.MoveFirst();
}

void CLog::LightStatusTableMoveNext()
{
	if(m_SNLightStatusTableRecordSet.GetRecordCount()>0)
		m_SNLightStatusTableRecordSet.MoveNext();
}


void CLog::LoadPowerpara(CString &FileName, CString &PowerPara,CString &LotId, CString &Time)
{
	char szRead[256]={""};
	CString str;
	
	strncpy(szRead,GetLang().GetWarningText(10164),256);
	str.Format("%s",szRead);
	ObjPowerParaSet.GetCollect(str,FileName);//"�Ϻ�"
	
	ObjPowerParaSet.GetCollect("PowerPara",PowerPara);
	ObjPowerParaSet.GetCollect("LOTID",LotId);
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjPowerParaSet.GetCollect(str,Time);//"ʱ��"
}

bool CLog::isPowerEOF()
{
	if(ObjPowerSet.IsEOF())
		return true;
	else
		return false;
}

bool CLog::isPowerBOF()
{
	if(ObjPowerSet.IsBOF())
		return true;
	else
		return false;
}

void CLog::PowerMoveFirst()
{
	if(ObjPowerSet.GetRecordCount()>0)
		ObjPowerSet.MoveFirst();
}

void CLog::PowerMoveLast()
{
	if(ObjPowerSet.GetRecordCount()>0)
		ObjPowerSet.MoveLast();
}

bool CLog::PowerMovePrevious()
{
	if(ObjPowerSet.GetRecordCount()>0)
		return SUCCEEDED(ObjPowerSet.MovePrevious());
	else
	{
		return false;
	}	
}

void CLog::PowerMoveNext()
{
	if(ObjPowerSet.GetRecordCount()>0)
		ObjPowerSet.MoveNext();
}

void CLog::LoadPowerResult(CString &Head,CString &Power, CString &DiffTime1, CString &Time ,CString &TestPlsRelease, CString &TestPlsPeriod,CString &Aperture,CString &result)
{
	char szRead[256]={""};
	CString str;
	
	strncpy(szRead,GetLang().GetWarningText(10159),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Head);//"����ͷ"
	
	strncpy(szRead,GetLang().GetWarningText(10158),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Power);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10160),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,DiffTime1);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Time);//"ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10161),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,TestPlsRelease);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10162),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,TestPlsPeriod);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10163),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Aperture);//"���Թ�Ȧ"

	str="���";
	CString resultCheck="";
	ObjPowerSet.GetCollect(str,resultCheck);//"���"
	if (resultCheck.IsEmpty())
		result="OK";
	else
		result=resultCheck;	
}

void CLog::LoadPowerForUpload(CString &powerL,CString &powerR)
{
	CString Head,Power,DeffTime,Time,TestPlsRelease,TestPlsPeriod,Aperture;
	bool hasValueL = false;
	bool hasValueR = false;
	GetLog().PowerMoveLast();
	while(!GetLog().isPowerBOF())
	{
		GetLog().LoadPower(Head,Power,DeffTime,Time,TestPlsRelease,TestPlsPeriod,Aperture);
		if (Head=="��" && !hasValueL)
		{
			powerL=Power;	
			hasValueL = true;
		}
		if (Head=="��" && !hasValueR)
		{
			powerR=Power;
			hasValueR = true;
		}
		if(hasValueL && hasValueR)
		{
			break;
		}
		GetLog().PowerMovePrevious();
	}
}

void CLog::LoadPower(CString &Head,CString &Power, CString &DeffTime, CString &Time,CString &TestPlsRelease, CString &TestPlsPeriod,CString &Aperture)
{
	char szRead[256]={""};
	CString str;
	
	strncpy(szRead,GetLang().GetWarningText(10159),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Head);//"����ͷ"
	
	strncpy(szRead,GetLang().GetWarningText(10158),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Power);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10160),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,DeffTime);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10154),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Time);//"ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10161),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,TestPlsRelease);//"����ʱ��"
	
	strncpy(szRead,GetLang().GetWarningText(10162),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,TestPlsPeriod);//"��������"
	
	strncpy(szRead,GetLang().GetWarningText(10163),256);
	str.Format("%s",szRead);
	ObjPowerSet.GetCollect(str,Aperture);//"���Թ�Ȧ"	
}

BOOL CLog::BackupAllLogData(CWnd* pParent)
{
	DWORD dwAttrs; 
	char szOldPath[256]={""};
	char szNewPath[256]={""}; 
	CString strFileName;
	CString strpath = GetDoc().GetAppPath()+LOGFILEDIR;

	char daybuf[32];
	struct tm *NowTime;
	time_t ltime;
	time(&ltime);
	NowTime= localtime( &ltime );
	int mon=NowTime->tm_mon;
	if(mon==0)
	{
		int year=NowTime->tm_year;
		NowTime->tm_year=year-1;
		NowTime->tm_mon=11;
	}
	else
		NowTime->tm_mon=mon-1;
	strftime( daybuf, 32, "%Y%m", NowTime );

	if (!CreateDirectory(strpath, NULL))
	{ 
		if ( GetLastError() != ERROR_ALREADY_EXISTS ) 
		{
			AfxMessageBox("���ݿ��ļ�����Ŀ¼����ʧ�ܣ���ȷ�ϣ�");
			return false;
		}
	}

	int iDataBaseCount=5;
	if(GetDoc().GetSysInfoDBMode()==1)
		iDataBaseCount=6;

	for(int i=0;i<iDataBaseCount;i++)
	{
		lstrcpy(szNewPath, strpath);
		lstrcat(szNewPath, CString(daybuf)+strDataBase[i]);

		strFileName=GetDoc().GetAppPath()+strDataBase[i];
		lstrcpy(szOldPath, strFileName);		


		if (CopyFile(szOldPath, szNewPath, FALSE))
		{
			dwAttrs = GetFileAttributes(szOldPath); 

			if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) 
				SetFileAttributes(szNewPath, dwAttrs | FILE_ATTRIBUTE_READONLY); 

			if(i==5)
			{
				for(int j=0;j<5;j++)
				{
					if(!DeleteRecord(i+j,pParent))
						return false;
				}
			}
			else
			{
				if(!DeleteRecord(i,pParent))
					return false;
			}
		} 
		else 
		{ 
			if ( GetLastError() != ERROR_ACCESS_DENIED ) 
			{
				AfxMessageBox("���ݿ��ļ�����ʧ�ܣ���ȷ�ϣ�");
				return false;
			}
		} 
	}

	return TRUE;
}

bool CLog::ConnectCalcSet(CString &sLogName)
{
	if (ObjCalc.ConnectAccess((LPCTSTR)sLogName))
	{
		GetBillHandCalc();
		return true ;
	}
	else
		return false ;
}

bool CLog::ConnectProSet(CString &sLogName)
{
	if (ObjPro.ConnectAccess((LPCTSTR)sLogName))
	{
		GetBillHandPro();
		return true ;
	}
	else
		return false ;	
}

bool CLog::ConnectPowerSet(CString &sLogName)
{
	if (Objpower.ConnectAccess((LPCTSTR)sLogName))
	{
		GetBillHandPower();
		return true ;
	}
	else
		return false ;
}

bool CLog::ConnectPowerParaSet(CString &sLogName)
{
	if (ObjPowerPara.ConnectAccess((LPCTSTR)sLogName))
	{
		GetBillHandPowerPara();
		return true ;
	}
	else
		return false ;
}

//////////////////////////////////////////////////////						//20160901
_RecordsetPtr CLog::GetBillHandSNAlarm()
{
	m_SNAlarmTableRecordSet.Close();
	m_SNAlarmTableRecordSet.SetAdoConnection(&m_SNDBConnect);
	m_SNAlarmTableRecordSet.SetCursorLocation(adUseClient);
	m_SNAlarmTableRecordSet.Open("AlarmTable", adCmdTable);

	if(m_SNAlarmTableRecordSet.GetRecordCount()>0)
	{		
		if (!m_SNAlarmTableRecordSet.IsEOF())
			m_SNAlarmTableRecordSet.MoveLast();
	}
	   
	return m_SNAlarmTableRecordSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandSNAxisStatus()
{
	m_SNAxisStatusTableRecordSet.Close();
	m_SNAxisStatusTableRecordSet.SetAdoConnection(&m_SNDBConnect);
	m_SNAxisStatusTableRecordSet.SetCursorLocation(adUseClient);
	m_SNAxisStatusTableRecordSet.Open("AxisStatusTable", adCmdTable);

	if(m_SNAxisStatusTableRecordSet.GetRecordCount()>0)
	{		
		if (!m_SNAxisStatusTableRecordSet.IsEOF())
			m_SNAxisStatusTableRecordSet.MoveLast();
	}
	   
	return m_SNAxisStatusTableRecordSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandSNLightStatus()
{
	m_SNLightStatusTableRecordSet.Close();
	m_SNLightStatusTableRecordSet.SetAdoConnection(&m_SNDBConnect);
	m_SNLightStatusTableRecordSet.SetCursorLocation(adUseClient);
	m_SNLightStatusTableRecordSet.Open("LightStatusTable", adCmdTable);

	if(m_SNLightStatusTableRecordSet.GetRecordCount()>0)
	{		
		if (!m_SNLightStatusTableRecordSet.IsEOF())
			m_SNLightStatusTableRecordSet.MoveLast();
	}
	   
	return m_SNLightStatusTableRecordSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandSNOtherStatus()
{
	m_SNOtherStatusTableRecordSet.Close();
	m_SNOtherStatusTableRecordSet.SetAdoConnection(&m_SNDBConnect);
	m_SNOtherStatusTableRecordSet.SetCursorLocation(adUseClient);
	m_SNOtherStatusTableRecordSet.Open("OtherStatusTable", adCmdTable);

	long pods  = m_SNOtherStatusTableRecordSet.GetAbsolutePosition();
	if(m_SNOtherStatusTableRecordSet.GetRecordCount()>0)
	{		
		if (!m_SNOtherStatusTableRecordSet.IsEOF())
			m_SNOtherStatusTableRecordSet.MoveLast();
	}
	   
	return m_SNOtherStatusTableRecordSet.GetRecordset();
}

_RecordsetPtr CLog::GetBillHandSNWork()
{
	m_SNWorkTableRecordSet.Close();
	m_SNWorkTableRecordSet.SetAdoConnection(&m_SNDBConnect);
	m_SNWorkTableRecordSet.SetCursorLocation(adUseClient);
	m_SNWorkTableRecordSet.Open("WorkTable", adCmdTable);

	if(m_SNWorkTableRecordSet.GetRecordCount()>0)
	{		
		if (!m_SNWorkTableRecordSet.IsEOF())
			m_SNWorkTableRecordSet.MoveLast();
	}
	   
	return m_SNWorkTableRecordSet.GetRecordset();
}

void CLog::AppendSNAlarmTable(CString alarmMSG,COleDateTime  workTime)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		int number=m_SNAlarmTableRecordSet.GetRecordCount();
		if(number>0)
			m_SNAlarmTableRecordSet.MoveLast();
		m_SNAlarmTableRecordSet.AddNew();
		m_SNAlarmTableRecordSet.PutCollect("������Ϣ",alarmMSG);
		m_SNAlarmTableRecordSet.PutCollect("����ʱ��",workTime);			
		m_SNAlarmTableRecordSet.Update();
		
		m_SNDBConnect.BeginTrans();	
		m_SNDBConnect.CommitTrans();
	}

	return;
}

void CLog::AppendSNAxisStatusTable(CString leftStatus,CString rightStatus,COleDateTime  workTime)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		int number=m_SNAxisStatusTableRecordSet.GetRecordCount();
		if(number>0)
			m_SNAxisStatusTableRecordSet.MoveLast();
		m_SNAxisStatusTableRecordSet.AddNew();
		m_SNAxisStatusTableRecordSet.PutCollect("����",leftStatus);
		m_SNAxisStatusTableRecordSet.PutCollect("����",rightStatus);
		m_SNAxisStatusTableRecordSet.PutCollect("����ʱ��",workTime);		
		m_SNAxisStatusTableRecordSet.Update();
		
		m_SNDBConnect.BeginTrans();	
		m_SNDBConnect.CommitTrans();
	}

	return;
}

void CLog::AppendSNLightStatusTable(int type, COleDateTime workTime)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		CString redStatus="��";
		CString greenStatus="��";
		CString yellowStatus="��";
		int number=m_SNLightStatusTableRecordSet.GetRecordCount();
		if(number>0)
			m_SNLightStatusTableRecordSet.MoveLast();
		m_SNLightStatusTableRecordSet.AddNew();
		if(1==type)
			yellowStatus="��";
		if(2==type)
			greenStatus="��";
		if(3==type)
			redStatus="��";
		m_SNLightStatusTableRecordSet.PutCollect("���",redStatus);
		m_SNLightStatusTableRecordSet.PutCollect("�̵�",greenStatus);
		m_SNLightStatusTableRecordSet.PutCollect("�Ƶ�",yellowStatus);
		m_SNLightStatusTableRecordSet.PutCollect("����ʱ��",workTime);			
		m_SNLightStatusTableRecordSet.Update();
		
		m_SNDBConnect.BeginTrans();	
		m_SNDBConnect.CommitTrans();
	}

	return;
}

int API_StringToTimeEX2(char* strDateStr, time_t &timeData)
{
	char *pBeginPos = strDateStr;
	char *pPos = strstr(pBeginPos, "-");
	if (pPos == NULL)
	{
		printf("strDateStr[%s] err \n", strDateStr);
		return -1;
	}
	int iYear = atoi(pBeginPos);
	int iMonth = atoi(pPos + 1);
	pPos = strstr(pPos + 1, "-");
	if (pPos == NULL)
	{
		printf("strDateStr[%s] err \n", strDateStr);
		return -1;
	}
	int iDay = atoi(pPos + 1);
	int iHour = 0;
	int iMin = 0;
	int iSec = 0;
	pPos = strstr(pPos + 1, "T");
	//Ϊ�˼�����Щû��ȷ��ʱ�����
	if (pPos != NULL)
	{
		iHour = atoi(pPos + 1);
		pPos = strstr(pPos + 1, ":");
		if (pPos != NULL)
		{
			iMin = atoi(pPos + 1);
			pPos = strstr(pPos + 1, ":");
			if (pPos != NULL)
			{
				iSec = atoi(pPos + 1);
			}
		}
	}
	
	tm sourcedate;
	bzero((void*)&sourcedate, sizeof(sourcedate));
	sourcedate.tm_sec = iSec;
	sourcedate.tm_min = iMin;
	sourcedate.tm_hour = iHour+8;
	sourcedate.tm_mday = iDay;
	sourcedate.tm_mon = iMonth-1;
	sourcedate.tm_year = iYear-1900;
	timeData = mktime(&sourcedate);
	return 0;
}

void CLog::AppendSNOtherStatusTable(CString status,COleDateTime  workTime)
{
	time_t t1,t2;
	time(&t1);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&t1));
	t1 = ToolUtil::stringtotime_t(currentTime);
	
	CString seqNum,lastStatus,lastTime;
	if (!this->isStatusTableEOF())
	{
		this->LoadStatusTable(seqNum,lastStatus,lastTime);
	}

	if (lastTime!="")
	{
		t2 = ToolUtil::stringtotime_t(lastTime.GetBuffer(0));
		double nSecnonSpan = difftime(t1,t2);
		if (nSecnonSpan < GetDoc().GetSysIdtTime())
		{
			//return;
		}
	}

	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		if (lastStatus != status)
		{
			int number=m_SNOtherStatusTableRecordSet.GetRecordCount();
			if(number>0)
				m_SNOtherStatusTableRecordSet.MoveLast();
			m_SNOtherStatusTableRecordSet.AddNew();
			m_SNOtherStatusTableRecordSet.PutCollect("״̬�л�",status);
			m_SNOtherStatusTableRecordSet.PutCollect("����ʱ��",workTime);			
			m_SNOtherStatusTableRecordSet.Update();
			
			m_SNDBConnect.BeginTrans();	
			m_SNDBConnect.CommitTrans();
		}
	}

	return;
}

void CLog::AppendSNWorkTable(CString lotID,CString employeeID,CString program,CString procCount,COleDateTime  workTime)
{
	if(bConnectok&&(GetDoc().GetSysInfoDBMode()==1))
	{
		int number=m_SNWorkTableRecordSet.GetRecordCount();
		if(number>0)
			m_SNWorkTableRecordSet.MoveLast();
		m_SNWorkTableRecordSet.AddNew();
		m_SNWorkTableRecordSet.PutCollect("������",lotID);
		m_SNWorkTableRecordSet.PutCollect("������",employeeID);
		m_SNWorkTableRecordSet.PutCollect("��ʽ",program);
		m_SNWorkTableRecordSet.PutCollect("�ӹ������",procCount);
		m_SNWorkTableRecordSet.PutCollect("����ʱ��",workTime);			
		m_SNWorkTableRecordSet.Update();
		
		m_SNDBConnect.BeginTrans();	
		m_SNDBConnect.CommitTrans();
	}

	return;
}
