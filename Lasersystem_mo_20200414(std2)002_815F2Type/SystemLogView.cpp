// SystemLogView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "SystemLogView.h"
#include "operatecontrol.h"
#include "Log.h"
#include "LoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bConnectok;
extern CString strDataBase[6];
/////////////////////////////////////////////////////////////////////////////
// CSystemLogView

char * const TREE_SERVICES[4] = 
{
	"PCB�ӹ�����",	//1
	"��������ʾ",	//2
	"������������", //3		
	"�ļ��ӹ�����", //4			
};

char * const TREE_SERVICES_EN[4] = 
{
	"PCB processing data",	//1 PCB�ӹ�����",
	"operate & info",		//2 "��������ʾ",
	"Laser power measure",	//3	"������������", 
	"File attribute"		//4	"�ļ��ӹ�����", 
};

char * const TREE_FILENAMEFLAG[4] = 
{
	"CalcResult",	//1
	"OperResult",	//2
	"LaserPower",	//3		
	"FileParame",	//4			
};

IMPLEMENT_DYNCREATE(CSystemLogView, TVisualFormView)

CSystemLogView::CSystemLogView()
: TVisualFormView(CSystemLogView::IDD)
{	
	//{{AFX_DATA_INIT(CSystemLogView)
	m_tDataTimeBefor = COleDateTime::GetCurrentTime();
	m_tDateTimeAfter = COleDateTime::GetCurrentTime();
	m_tHistoryAfter = COleDateTime::GetCurrentTime();
	m_tHistoryBefor = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}

CSystemLogView::~CSystemLogView()
{

}

void CSystemLogView::DoDataExchange(CDataExchange* pDX)
{
	TVisualFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemLogView)
	DDX_Control(pDX, IDC_COMHISLOGSEL, m_HisLogSelect);
	DDX_Control(pDX, IDC_TREELOG, m_treeLog);
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_datadisplay);
	DDX_Control(pDX, IDC_BT_LOGSAVE, m_logSave);
	DDX_Control(pDX, IDC_BT_FITTER, m_logFilter);
	DDX_Control(pDX, IDC_COMLOGSEL, m_SetSelect);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMBEFOR, m_tDataTimeBefor);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEAFTER, m_tDateTimeAfter);
	DDX_DateTimeCtrl(pDX, IDC_DTHIAFTER, m_tHistoryAfter);
	DDX_DateTimeCtrl(pDX, IDC_DTHIBEFOR, m_tHistoryBefor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSystemLogView, TVisualFormView)
//{{AFX_MSG_MAP(CSystemLogView)
ON_BN_CLICKED(IDC_BT_FITTER, OnBtFitter)
ON_BN_CLICKED(IDC_BT_LOGSAVE, OnBtLogsave)
ON_NOTIFY(NM_DBLCLK, IDC_TREELOG, OnDblclkTreelog)
ON_BN_CLICKED(IDC_BT_OPENHISDISPLAY, OnBtOpenhisdisplay)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemLogView diagnostics

#ifdef _DEBUG
void CSystemLogView::AssertValid() const
{
	TVisualFormView::AssertValid();
}

void CSystemLogView::Dump(CDumpContext& dc) const
{
	TVisualFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSystemLogView message handlers
void CSystemLogView::SetUI()
{
	char szRead[20] = {""};

	GetLang().GetUIText("SystemLog","IDC_STATIC1",szRead,20);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("SystemLog","IDC_STATIC2",szRead,20);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("SystemLog","IDC_BT_FITTER",szRead,20);
	SetDlgItemText(IDC_BT_FITTER,szRead);
	GetLang().GetUIText("SystemLog","IDC_BT_OPENHISDISPLAY",szRead,20);
	SetDlgItemText(IDC_BT_OPENHISDISPLAY,szRead);
	GetLang().GetUIText("SystemLog","IDC_BT_LOGSAVE",szRead,20);
	SetDlgItemText(IDC_BT_LOGSAVE,szRead);
}

void CSystemLogView::OnInitialUpdate() 
{
	char szRead[20]={""};

	m_logFilter.SubclassDlgItem(IDC_BT_FITTER,this);
	m_logFilter.SetIcon(IDI_DISPLAY,IDI_DISPLAY);
	
	m_logSave.SubclassDlgItem(IDC_BT_LOGSAVE,this);
	m_logSave.SetIcon(IDI_SAVEP,IDI_SAVEP);
	
	TVisualFormView::OnInitialUpdate();

	if(GetLang().GetCurLanguage()==1)
		SetUI();
	
	strValueB =	m_tDataTimeBefor.Format("%Y-%m-%d"); 
	strValueA = m_tDateTimeAfter.Format("%Y-%m-%d")+"24";
	

	m_SetSelect.ResetContent();
	
	strncpy(szRead,GetLang().GetWarningText(10114),20);
	m_SetSelect.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10115),20);
	m_SetSelect.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10116),20);
	m_SetSelect.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10117),20);
	m_SetSelect.AddString(szRead);
	m_SetSelect.AddString("У������");
	m_SetSelect.AddString("ͳ������");
	
	m_SetSelect.SetCurSel(0);
/*	
	m_HisLogSelect.ResetContent();

	strncpy(szRead,GetLang().GetWarningText(10114),20);
	m_HisLogSelect.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10115),20);
	m_HisLogSelect.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10116),20);
	m_HisLogSelect.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10117),20);
	m_HisLogSelect.AddString(szRead);
	m_HisLogSelect.AddString("У������");
	m_HisLogSelect.AddString("ͳ������");
	
	m_HisLogSelect.SetCurSel(0);
*/	
	m_datadisplay.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	COLORREF bkColor=RGB(194,231,190);											//20160907
	m_datadisplay.SetBkColor(bkColor);									
	m_datadisplay.SetBakColor(bkColor);

	char string[256];
	strcpy(string, "");

	strncpy(szRead,GetLang().GetWarningText(10045),20);
	strcat( string,szRead );//"����,150;"
	strncpy(szRead,GetLang().GetWarningText(10046),20);
	strcat( string,szRead );//"��ʾ����,150;"
	strncpy(szRead,GetLang().GetWarningText(10047),20);
	strcat( string, szRead);//"��ע,150;"
	strncpy(szRead,GetLang().GetWarningText(10048),20);
	strcat( string, szRead);//"ʱ��,200"
	
	m_datadisplay.SetHeadings(_T(string));

	LoadHistoryLog();	
}

void CSystemLogView::OnBtFitter()
{
	UpdateData();
	char ez[256]={""};

//	if(	!GetLog().InitLog())
//		return;
	
	strValueB =	m_tDataTimeBefor.Format("%Y-%m-%d"); 
	strValueA = m_tDateTimeAfter.Format("%Y-%m-%d")+"24";

	switch(m_SetSelect.GetCurSel())
	{
	case 0:
		m_datadisplay.ClearList();
		SetCalcHead();
		LoadCalcToDisplay(strValueA,strValueB);
		break;
	case 1:
		m_datadisplay.ClearList();
		SetProHead();
		LoadProToDisplay(strValueA,strValueB);
		break;
	case 2:
		m_datadisplay.ClearList();
		SetPowerHead();
		LoadPowerToDisplay(strValueA,strValueB);
		break;
	case 3:
		m_datadisplay.ClearList();
		SetFilePropHead();
		LoadPowerParaToDisplay(strValueA,strValueB);
		break;
	case 4:
		m_datadisplay.ClearList();
		SetProHead();
		LoadProToDisplay(strValueA,strValueB,true);
		break;
	case 5:
		m_datadisplay.ClearList();
		SetCalcHead(1);
		LoadCalcAnalyse(strValueA,strValueB);
		break;
	default:
		strncpy(ez,GetLang().GetWarningText(14008),256);
		MessageBox(ez);//"���ڲ�����ʱ�����ڵı�"
	}
}

void CSystemLogView::OnBtLogsave()					//"������־"��ť
{	
	static char szFilter[] = "Csv Files (*.csv)|*.csv|Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";
    CFileDialog FileDlg(false,"csv",NULL,OFN_HIDEREADONLY,szFilter,NULL);
    
	if(FileDlg.DoModal())
	{
		CString str = FileDlg.GetPathName();
		if(str!="")
		{
			if(!ExportResult(str))
				MessageBox("��־����ʧ�ܣ�");
		}
	}
}

BOOL CSystemLogView::ExportResult(const CString strFilName) 
{
	FILE* fp;
	char buf[512];
	char ez[256]={""};
	CString strItem;
	CString strCol;
	int TImeColNumb=0;

	if(!(fp = fopen(strFilName,"a+")))
		return FALSE;

	va_list args;
	int nCount = m_datadisplay.GetItemCount();	//����
	int nColumns = m_datadisplay.GetColumns();	//����
	if(nCount==0)
	{
		strncpy(ez,GetLang().GetWarningText(14009),256);
		MessageBox(ez);//"����û�����ݣ�"

		fclose(fp);
		return FALSE;
	}

	for(int i=0;i<nColumns;i++)
	{
		CString strTemp=  GetListFieldName(i);
		strCol +=strTemp+",";
		
		strncpy(ez,GetLang().GetWarningText(10120),256);
		if(0==strcmp(strTemp,ez) )//"ʱ��"
			TImeColNumb= i;
	}

	m_datadisplay.Sort(TImeColNumb,TRUE);

	strCol = strCol+"\n";
	fputs(strCol,fp);

	for(int nRow = 0;nRow<nCount;nRow++)
	{
		CString strLine;
		for(int nCol = 0;nCol<nColumns;nCol++)
		{
			strItem = m_datadisplay.GetItemText(nRow,nCol);//�õ���nRow��,nCol������
			strItem += ",";
			strLine += strItem;
		}

		strLine += "\n";//����			
		va_start(args,strLine);
		vsprintf(buf,strLine,args);
		va_end(args);
		fputs(buf,fp);
	}

	fclose(fp);

	return TRUE;
}

void CSystemLogView::LoadCalcToDisplay(CString &TimeB,CString &TimeA)
{
	char ez[256]={""};
	int holes=0;	
	CString Head,FileName,Date,Time,x,y,PitchTime;
	CString isNgOK,fileName1,fixedNo,increasingNo;
	CString rPCBScaleX,rPCBScaleY;
	int index=0;
	CString Array[15];
	
	GetLog().SetSort();
	GetLog().CalcMoveFirst();

	while(!GetLog().isCalcEOF())
	{
		if (GetDoc().GetDrillInc())//��ʿ�����¶���
			GetLog().LoadCalcFuShikang(Head,FileName,x,y,rPCBScaleX,rPCBScaleY,PitchTime,Time,holes,isNgOK,fileName1,fixedNo,increasingNo);
		else//ԭ�еĲ��ı�
			GetLog().LoadCalc(Head,FileName,x,y,PitchTime,Time,holes,isNgOK,fileName1,fixedNo,increasingNo);

		index=0;
		if((TimeB>=Time)&&(TimeA<=Time))
		{
			Array[index] = Head;
			index++;

			Array[index] = FileName;
			index++;
			
			Array[index] = x;
			index++;
			
			Array[index] = y;
			index++;

			if (GetDoc().GetDrillInc())//��ʿ�����¶���
			{
				Array[index] = rPCBScaleX;
				index++;

				Array[index] = rPCBScaleY;
				index++;
			}
			
			Array[index] = PitchTime;
			index++;

			Array[index] = Time;
			index++;
			
            Array[index] = isNgOK;
			index++;
			
			CString tempTest="";
			tempTest.Format("%d",holes);
			Array[index] = tempTest;
			index++;
			
			Array[index] = fileName1;
			index++;
			
			Array[index] = fixedNo;
			index++;
			
			Array[index] = increasingNo;
			index++;
				
			if(index ==0)
			{
				strncpy(ez,GetLang().GetWarningText(14010),256);
				MessageBox(ez);//"����ܹص�������Ŀ��"
				return ;
			}

			m_datadisplay.AddItem(Array,15);

//			GetLog().CalcMoveNext();
//			continue;
		}

		GetLog().CalcMoveNext();		
	}
}

void CSystemLogView::LoadCalcAnalyse(CString &TimeB,CString &TimeA)
{//���ݼ�¼ɸѡ��ͳ�Ƽ�¼
	char ez[256]={""};
	int holes=0;	
	CString Head,FileName,Date,Time,x,y,PitchTime;
	CString isNgOK,fileName1,fixedNo,increasingNo,tempPitchTime;
	CString compareFileName,compareLotId,beginTime,endTime;	
	BOOL isFirstCompare=TRUE,isHaveReport=FALSE;
	int okPane=0,nGPanel=0,reportholes=0;
	CString tempTranStr="";
	isTagReportSanalyse isinfo;

	m_CArrayCountList.RemoveAll();

	GetLog().SetSort();
	GetLog().CalcMoveFirst();

	while(!GetLog().isCalcEOF())
	{
		GetLog().LoadCalc(Head,FileName,x,y,PitchTime,Time,holes,isNgOK,fileName1,fixedNo,increasingNo);

		if((TimeB>=Time)&&(TimeA<=Time))
		{
			isHaveReport=TRUE;

			if (isFirstCompare)
			{
				beginTime=endTime=Time;
				compareFileName=fileName1;
				compareLotId=fixedNo;
				reportholes=holes;
				tempPitchTime=PitchTime;
				isFirstCompare=FALSE;
			}

			if (compareFileName==fileName1&&compareLotId==fixedNo)
			{
				if (isNgOK=="OK")
				{
					okPane++;
					reportholes=holes;
				}
				else
					nGPanel++;			  
			}
			else
			{			   
				isinfo.m_FileName=compareFileName;
				isinfo.m_LotID=compareLotId;
				isinfo.m_SingleHoles=reportholes;
				isinfo.m_PitchTime=tempPitchTime;
				isinfo.m_BeginTime=beginTime;
				isinfo.m_EndTime=endTime;
				isinfo.m_OKPanel=okPane;
				isinfo.m_NGPanel=nGPanel;
				isinfo.m_TotalHoles=reportholes*okPane;
				isinfo.m_TotalPanel=okPane+nGPanel;
				
				COleDateTime beginTimeOleDateTime, endTimeOleDateTime;
				beginTimeOleDateTime.ParseDateTime(beginTime);
				endTimeOleDateTime.ParseDateTime(endTime);
				COleDateTimeSpan dTimeSpan = endTimeOleDateTime - beginTimeOleDateTime;

				isinfo.m_AllTimes=dTimeSpan.GetTotalSeconds();//tempTranStr;
				
				m_CArrayCountList.Add(isinfo);
				
				if (isNgOK=="OK")
				{
					okPane=1;
					nGPanel=0;
					reportholes=holes;
				}
				else
				{
					nGPanel=1;
					okPane=0;
				}

				beginTime=Time;
				reportholes=holes;
			}

			compareFileName=fileName1;
            compareLotId=fixedNo;
			endTime=Time;
			tempPitchTime=PitchTime;
			
//			GetLog().CalcMoveNext();
//			continue;
		}

		GetLog().CalcMoveNext();		
	}

	if (isHaveReport)
	{//ͳ�����һ������
		isinfo.m_FileName=compareFileName;
		isinfo.m_LotID=compareLotId;
		isinfo.m_SingleHoles=reportholes;
		isinfo.m_PitchTime=tempPitchTime;
		isinfo.m_BeginTime=beginTime;
		isinfo.m_EndTime=endTime;
		isinfo.m_OKPanel=okPane;
		isinfo.m_NGPanel=nGPanel;	
		isinfo.m_TotalHoles=reportholes*okPane;
		isinfo.m_TotalPanel=okPane+nGPanel;

		COleDateTime beginTimeOleDateTime, endTimeOleDateTime;
		beginTimeOleDateTime.ParseDateTime(beginTime);
		endTimeOleDateTime.ParseDateTime(endTime);
		COleDateTimeSpan dTimeSpan = endTimeOleDateTime - beginTimeOleDateTime;

		isinfo.m_AllTimes=dTimeSpan.GetTotalSeconds();//tempTranStr;
		
		m_CArrayCountList.Add(isinfo);  
	}
	
	CString Array[15];
	tempTranStr="";
	tagReportSanalyse tempResult;
	int index=0;

	for (int i=0;i<m_CArrayCountList.GetSize();i++)
	{
		tempResult=m_CArrayCountList.GetAt(i);
		
		index=0;
		Array[index]=tempResult.m_FileName;
		
		index++;
		Array[index]=tempResult.m_LotID;
		
		if (tempResult.m_BeginTime==tempResult.m_EndTime)
		{		
			long  tempuseTime=atoi(tempResult.m_PitchTime);
			long hours=tempuseTime/60/60,minute=tempuseTime/60%60,secondes=tempuseTime%60;
			CString sHours,sMinute,sSeconds;

			if (hours<10)
				sHours.Format("0%d:",hours);
			else
				sHours.Format("%d:",hours);	
			
			if (minute<10)
				sMinute.Format("0%d:",minute);
			else
				sMinute.Format("%d:",minute);
			
			if (secondes<10)
				sSeconds.Format("0%d",secondes);
			else
				sSeconds.Format("%d",secondes);			
			
			COleDateTime endTimeOleDateTime;
			endTimeOleDateTime.ParseDateTime(tempResult.m_BeginTime);
			
			COleDateTimeSpan dTimeSpan;
			dTimeSpan.SetDateTimeSpan(0,hours,minute,secondes);
			
			index++;
			Array[index]=(endTimeOleDateTime - dTimeSpan).Format("%Y-%m-%d %H:%M:%S").Left(10);
			
			index++;
			Array[index]=(endTimeOleDateTime - dTimeSpan).Format("%Y-%m-%d %H:%M:%S").Right(8);
			
			index++;
			Array[index]=tempResult.m_EndTime.Left(10);
			
			index++;
			Array[index]=tempResult.m_EndTime.Right(8);
			
			index++;		
			Array[index]=sHours+sMinute+sSeconds;
		}
		else
		{
			index++;
			Array[index]=tempResult.m_BeginTime.Left(10);
			
			index++;
			Array[index]=tempResult.m_BeginTime.Right(8);
			
			index++;
			Array[index]=tempResult.m_EndTime.Left(10);
			
			index++;
			Array[index]=tempResult.m_EndTime.Right(8);
			
			index++;
			long hours=tempResult.m_AllTimes/60/60,minute=tempResult.m_AllTimes/60%60,secondes=tempResult.m_AllTimes%60;
			CString sHours,sMinute,sSeconds;

			if (hours<10)
				sHours.Format("0%d:",hours);
			else
				sHours.Format("%d:",hours);
			
			if (minute<10)
				sMinute.Format("0%d:",minute);
			else
				sMinute.Format("%d:",minute);
			
			if (secondes<10)
				sSeconds.Format("0%d",secondes);
			else
				sSeconds.Format("%d",secondes);

			Array[index]=sHours+sMinute+sSeconds;//tempResult.m_AllTimes+"(Minutes)";
		}
		
		index++;
		tempTranStr.Format("%d",tempResult.m_OKPanel);
		Array[index]=tempTranStr;
		
		index++;
		tempTranStr.Format("%d",tempResult.m_NGPanel);
		Array[index]=tempTranStr;
		
		index++;
		tempTranStr.Format("%d",tempResult.m_TotalPanel);
		Array[index]=tempTranStr;
		
		index++;
		tempTranStr.Format("%d",tempResult.m_SingleHoles);
		Array[index]=tempTranStr;
		
		index++;
		tempTranStr.Format("%d",tempResult.m_TotalHoles);
		Array[index]=tempTranStr;
		
		m_datadisplay.AddItem(Array,15);
	}

	return;
}

void CSystemLogView::LoadProToDisplay(CString &TimeB,CString &TimeA,BOOL sift)
{
	char ez[256]={""};
	int index=0;
	CString Opreate,Result,Remark,Time;
	CString Array[10];

	GetLog().ProMoveFirst();

	while(!GetLog().isProEOF())
	{
		GetLog().LoadPro(Opreate,Result,Remark,Time);

		index=0;
		if((TimeB>=Time)&&(TimeA<=Time))
		{
			Array[index] = Opreate;
			index++;

			Array[index] = Result;
			index++;

			Array[index] = Remark;
			index++;

			Array[index] = Time;
			if (GetDoc().GetDrillInc())		//20160801
				index++;
			
			if(index ==0)
			{
				strncpy(ez,GetLang().GetWarningText(14010),256);
				MessageBox(ez);//"����ܹص�������Ŀ��"
				return ;
			}	
			
			if (sift)
			{
				if(GetDoc().GetDrillInc())		//20160801
				{
					if (Opreate=="�񾵵��󾫶�У��ǰ" || Opreate=="�񾵵��󾫶�У����" || Opreate=="�񾵵��󾫶�У��" || "Galvanometer dot-matrix precision calibration"==Opreate)
					{
						CString status="OK";
						char* max=(LPSTR)(LPCTSTR)Remark;
						int iMax=atoi(max);
//						if(abs(iMax)>GetDoc().GetGlvAdjustThreshold())
//							status="NG";
						if (Opreate=="�񾵵��󾫶�У��ǰ")								
							status="";
						if(abs(iMax)>GetDoc().GetGlvAdjustThreshold())						//20170410
						{
							if (Opreate=="�񾵵��󾫶�У��ǰ")
								status=" ";
							else
								status="NG";
						}						

						Array[index] = status;					
						m_datadisplay.AddItem(Array,10);
					}
				}
				else
				{
					if (Opreate=="�񾵵��󾫶�У��" || "Galvanometer dot-matrix precision calibration"==Opreate)
					{
						m_datadisplay.AddItem(Array,10);
					}
				}
			}
			else
				m_datadisplay.AddItem(Array,10);

//			GetLog().ProMoveNext();
//			continue;
		}

		GetLog().ProMoveNext();
	}
}

void CSystemLogView::LoadPowerToDisplay(CString &TimeB,CString &TimeA)
{
	char ez[256]={""};
	int index=0;
	CString Head,Power,DiffTime,Time,PlsRelease,PlsPeriod,Aperture,result;
	CString Array[10];

	GetLog().PowerMoveFirst();

	while(!GetLog().isPowerEOF())
	{
		if (GetDoc().GetDrillInc())
			GetLog().LoadPowerResult(Head,Power,DiffTime,Time,PlsRelease,PlsPeriod,Aperture,result);
		else
			GetLog().LoadPower(Head,Power,DiffTime,Time,PlsRelease,PlsPeriod,Aperture);

		index=0;
		if((TimeB>=Time)&&(TimeA<=Time))
		{ 
			Array[index] = Head;
			index++;

			Array[index] = Power;
			index++;

			Array[index] = DiffTime;
			index++;

			Array[index] = Time;
			index++;

			Array[index] = PlsRelease;
			index++;

			Array[index] = PlsPeriod;
			index++;

			Array[index] = Aperture;
			if (GetDoc().GetDrillInc())//20150610
				index++;

			if (GetDoc().GetDrillInc())//20150610
			 Array[index] = result;
			
			if(index ==0)
			{
				strncpy(ez,GetLang().GetWarningText(14010),256);
				MessageBox(ez);//"����ܹص�������Ŀ��"
				return ;
			}
			
			m_datadisplay.AddItem(Array,10);

//			GetLog().PowerMoveNext();
//			continue;
		}
		
		GetLog().PowerMoveNext();
	}
}

void CSystemLogView::LoadPowerParaToDisplay(CString &TimeB,CString &TimeA)
{
	char ez[256]={""};
	int index=0;
	CString FilepathAandName,LotId,PowerPara,Time;
	CString Array[10];

	GetLog().PowerParaMoveFirst();

	while(!GetLog().isPowerParaEOF())
	{
		GetLog().LoadPowerpara(FilepathAandName,PowerPara,LotId,Time);

		index=0;
		if((TimeB>=Time)&&(TimeA<=Time))
		{
			Array[index] = FilepathAandName;
			index++;

			Array[index] = PowerPara;
			index++;

			Array[index] = LotId;
			index++;

			Array[index] = Time;
			
			if(index ==0)
			{
				strncpy(ez,GetLang().GetWarningText(14010),256);
				MessageBox(ez);//"����ܹص�������Ŀ��"
				return ;
			}
			
			m_datadisplay.AddItem(Array,10);

//			GetLog().PowerParaMoveNext();
//			continue;
		}
		
		GetLog().PowerParaMoveNext();
	}	
}

void CSystemLogView::LoadHistoryLog()
{
	char szRead[20]={""};
	int	i,j;
	HTREEITEM hCur,hRoot;					//��Ŀ���
	TV_INSERTSTRUCT TCItem;					//�������������ݽṹ
	
	m_treeLog.DeleteAllItems();									//ɾ��

	DWORD dwStyles = GetWindowLong(m_treeLog,GWL_STYLE);		//��ȡ������ԭ���
	dwStyles |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	SetWindowLong(m_treeLog,GWL_STYLE,dwStyles);				//�����µķ��
	
	TCItem.hParent = TVI_ROOT;				//����
	TCItem.hInsertAfter = TVI_LAST;			//�������֮��
	TCItem.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;	//������
	strncpy(szRead,GetLang().GetWarningText(10118),20);
	TCItem.item.pszText = _T(szRead);		//"��־��ʷ��¼"
	
	hRoot = m_treeLog.InsertItem(&TCItem);						//���ظ�����

	bool fFinished = FALSE;
	HANDLE hSearch;
	WIN32_FIND_DATA FileData; 
	CString Path = GetDoc().GetAppPath()+LOGFILEDIR+"*.mdb";
	
	for(i=0;i<4;i++)
	{
		TCItem.hParent=hRoot;

		if(GetLang().GetCurLanguage()==1)
			TCItem.item.pszText = TREE_SERVICES_EN[i];
		else
			TCItem.item.pszText = TREE_SERVICES[i];

		hCur = m_treeLog.InsertItem(&TCItem);
		
		hSearch = FindFirstFile(Path, &FileData); 

		fFinished = FALSE;
		while(!fFinished)
		{
			CString str = FileData.cFileName;
			char dpstr[50] = "";
			strncpy(dpstr,str,16);

			int rev= str.Find(TREE_FILENAMEFLAG[i]);
			if(rev != -1)
			{
				TCItem.hParent=hCur;
				TCItem.item.pszText =dpstr;
				m_treeLog.InsertItem(&TCItem);
			}
			
			if (!FindNextFile(hSearch, &FileData)) 
			{
				if (GetLastError() == ERROR_NO_MORE_FILES) 
					fFinished = TRUE;  
			}	
		}

		FindClose(hSearch);
	}

	m_treeLog.Expand(hRoot,TVE_EXPAND);							//չ����һ����
}

void CSystemLogView::SetCalcHead(int mode)
{
	char strHead[256];
	strcpy( strHead, "" );
	char szRead[50]={""};

	if (mode)
	{
//		m_datadisplay.SetHeadings(_T("FileName,80;LotID,80;StartDay,80;StartTime,80;FinishDay,80;FinishTime,80;TotalTimes,80;OKPanel,80;NGPanel,80;TotalPanel,80;SingleHoles,80;TotalHoles,80"));
		m_datadisplay.SetHeadings(_T("�ļ���,80;LotID,80;��ʼ����,80;��ʼʱ��,80;��������,80;����ʱ��,80;��ʱ��,80;OK����,80;NG����,80;�ܰ���,80;�������,80;�ܿ���,80"));
		return;
	}
	
	strncpy(szRead,GetLang().GetWarningText(10130),30);
	strcat( strHead, szRead);//"����ͷ,60;"

	strncpy(szRead,GetLang().GetWarningText(10131),30);
	strcat( strHead, szRead );//"�ļ���,150;"

	strcat( strHead, "X,60;");
	strcat( strHead, "Y,60;");
	
	if (GetDoc().GetDrillInc())//��ʿ�����¶���
	{
		strcat( strHead, "RX,60;");
		strcat( strHead, "RY,60;");
	}

	strncpy(szRead,GetLang().GetWarningText(10132),30);
	strcat( strHead, szRead );//"��ʱ,150;"

	strncpy(szRead,GetLang().GetWarningText(10133),30);
	strcat( strHead,  szRead);//"ʱ��,200"
	
	strcat( strHead, ";�ӹ�״̬,100;");//�ӹ�״̬ NG_OK
	strcat( strHead, "�ӹ�����,100;");//�ӹ����� Holes
	strcat( strHead, "�ļ���,100;");//�ļ���   FileName1
	strcat( strHead, "�̶���,100;");//�̶���   FixedNo
	strcat( strHead, "��ˮ��,100");//��ˮ��   IncreasingNo
	
	m_datadisplay.SetHeadings(_T(strHead));	
}

void CSystemLogView::SetProHead()
{
	char strHead[256];
	strcpy( strHead, "" );
	char szRead[30]={""};
	
	strncpy(szRead,GetLang().GetWarningText(10134),30);
	strcat( strHead,  szRead);//"����,150;"

	strncpy(szRead,GetLang().GetWarningText(10135),30);
	strcat( strHead, szRead );//"��ʾ����,150;"

	strncpy(szRead,GetLang().GetWarningText(10136),30);
	strcat( strHead,  szRead);//"��ע,150;"

	strncpy(szRead,GetLang().GetWarningText(10133),30);
	strcat( strHead, szRead);// "ʱ��,200"

	if (GetDoc().GetDrillInc())	//20160801
    {
		strncpy(szRead,";���,100",30);
		strcat( strHead, szRead);//";���,100"
	}

	m_datadisplay.SetHeadings(_T(strHead));
//	m_datadisplay.SetHeadings("����,150;��ʾ����,150;��ע,150;ʱ��,200");//"����,150;��ʾ����,150;��ע,150;ʱ��,200"
}

void CSystemLogView::SetPowerHead()
{	
	char strHead[256];
	strcpy( strHead, "" );
	char szRead[30]={""};//ly 20110405

	strncpy(szRead,GetLang().GetWarningText(10130),30);
	strcat( strHead,  szRead);//"����ͷ,60;"

	strncpy(szRead,GetLang().GetWarningText(10137),30);
	strcat( strHead,  szRead);//"��������,100;"

	strncpy(szRead,GetLang().GetWarningText(10138),30);
	strcat( strHead,  szRead);//"����ʱ��(��),150;"

	strncpy(szRead,GetLang().GetWarningText(10139),30);
	strcat( strHead,  szRead);//"ʱ��,200;"

	strncpy(szRead,GetLang().GetWarningText(10140),30);
	strcat( strHead,  szRead);//"����ʱ��,100;"

	strncpy(szRead,GetLang().GetWarningText(10141),30);
	strcat( strHead,  szRead);//"��������,100;"

	strncpy(szRead,GetLang().GetWarningText(10142),30);
	strcat( strHead,  szRead);//"���Թ�Ȧ,100"
	
	if (GetDoc().GetDrillInc())//20150610
    {
		strncpy(szRead,";���,100",30);
		strcat( strHead,  szRead);//"���Թ�Ȧ,100"
	}

	m_datadisplay.SetHeadings(_T(strHead));
}

void CSystemLogView::SetFilePropHead()
{
	char strHead[256];
	strcpy( strHead, "" );
	char szRead[30]={""};//ly 20110405

	strncpy(szRead,GetLang().GetWarningText(10143),30);
	strcat( strHead,  szRead);//" �ļ���,300;"

	strncpy(szRead,GetLang().GetWarningText(10137),30);
	strcat( strHead, szRead);//"��������,100;"

	strcat( strHead, "LOTID,150;");

	strncpy(szRead,GetLang().GetWarningText(10133),30);
	strcat( strHead,  szRead);//"ʱ��,200"

	m_datadisplay.SetHeadings(_T(strHead));
}

void CSystemLogView::OnDblclkTreelog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(GetControl().GetRunState()==CControl::RUN)
	{
		AfxMessageBox("���������У����ܽ��д˲���!");
		return;
	}

	UpdateData();
	
	strValueB =	"2000-01-01";//m_tDataTimeBefor.Format("%Y-%m-%d"); 
	strValueA = "9999-99-99";//m_tDateTimeAfter.Format("%Y-%m-%d")+"24";
	CString DbBaseName;

	HTREEITEM hSel=m_treeLog.GetSelectedItem();				//ȡ��ѡ����;
	if(hSel==NULL) return;									//���κ�ѡ���򷵻�

	CString sTime=GetDoc().GetAppPath()+LOGFILEDIR+m_treeLog.GetItemText(hSel);//ȡ����������
	HTREEITEM ParentItem=m_treeLog.GetParentItem(hSel);
    CString  parentText= m_treeLog.GetItemText(ParentItem);
	
	char szRead[20]={""};
	char ez[256]={""};
	
	strncpy(ez,GetLang().GetWarningText(10118),256);
	if(strcmp(parentText,ez)==0)//parentText == "��־��ʷ��¼")
		return ;

	strncpy(ez,GetLang().GetWarningText(10114),256);
	if(strcmp(parentText,ez)==0)//parentText == "PCB�ӹ�����"
	{
		DbBaseName = sTime+ ".mdb";
		if(GetLog().ConnectCalcSet(DbBaseName))
		{
			m_datadisplay.ClearList();

			SetCalcHead();
			LoadCalcToDisplay(strValueA,strValueB);			
		}

		DbBaseName = GetDoc().GetAppPath()+strDataBase[0];
		if(!GetLog().ConnectCalcSet(DbBaseName))
		{
			AfxMessageBox("���ݿ�CalcResult.mdb����ʧ�ܣ�");
			bConnectok = false;
			return;
		}
	}

	strncpy(ez,GetLang().GetWarningText(10115),256);
	if(strcmp(parentText,ez)==0)//parentText == "��������ʾ")
	{
		DbBaseName = sTime+ ".mdb";
		if(GetLog().ConnectProSet(DbBaseName))
		{
			m_datadisplay.ClearList();

			SetProHead();
			LoadProToDisplay(strValueA,strValueB);
		}

		DbBaseName = GetDoc().GetAppPath()+strDataBase[1];
		if(!GetLog().ConnectProSet(DbBaseName))
		{
			AfxMessageBox("���ݿ�OperResult.mdb����ʧ�ܣ�");
			bConnectok = false;
			return;
		}
	}

	strncpy(ez,GetLang().GetWarningText(10116),256);
	if(strcmp(parentText,ez)==0)//parentText == "������������")
	{
		DbBaseName = sTime+ ".mdb";  
		if(GetLog().ConnectPowerSet(DbBaseName))
		{
			m_datadisplay.ClearList();
			
			SetPowerHead();
			LoadPowerToDisplay(strValueA,strValueB);
		}

		DbBaseName = GetDoc().GetAppPath()+strDataBase[2];
		if(!GetLog().ConnectPowerSet(DbBaseName))
		{
			AfxMessageBox("���ݿ�LaserPower.mdb����ʧ�ܣ�");
			bConnectok = false;
			return;
		}
	}

	strncpy(ez,GetLang().GetWarningText(10117),256);
	if(strcmp(parentText,ez)==0)//parentText == "�ļ��ӹ�����")
	{
		DbBaseName = sTime+ ".mdb"; 
		if(GetLog().ConnectPowerParaSet(DbBaseName))
		{
			m_datadisplay.ClearList();
			
			SetFilePropHead();
			LoadPowerParaToDisplay(strValueA,strValueB);
		}
		
		DbBaseName = GetDoc().GetAppPath()+strDataBase[3];
		if(!GetLog().ConnectPowerParaSet(DbBaseName))
		{
			AfxMessageBox("���ݿ�FileParame.mdb����ʧ�ܣ�");
			bConnectok = false;
			return;
		}
	}

	UpdateData(false);
	*pResult = 0;
}

void CSystemLogView::OnBtOpenhisdisplay() 
{
	UpdateData();
	char ez[256]={""};

	switch(m_SetSelect.GetCurSel())
	{
	case 0:
		LoadHistoryCalcDisplay();
		break;
	case 1:
		LoadHistoryProDisplay();
		break;
	case 2:
		LoadHistoryPowerDisplay();
		break;
	case 3:
		LoadHistoryPowerParaDisplay();
		break;
	case 4:
		LoadHistoryProDisplay(true);
		break;
	case 5:
		LoadHistoryCalcDisplay(1);
		break;
	default:
		strncpy(ez,GetLang().GetWarningText(14008),256);
		MessageBox(ez);//"���ڲ�����ʱ�����ڵı�"
	}
}

BOOL CSystemLogView::LoadHistoryCalcDisplay(BOOL sift)
{
	UpdateData(true);
	char ez[256]={""};

	m_datadisplay.ClearList();
	if (sift)
		SetCalcHead(1);
	else
		SetCalcHead();

	CString LogFileName;
	CString HisstrValueB,HisstrValueA;
	HisstrValueB = m_tDataTimeBefor.Format("%Y-%m-%d"); 
	HisstrValueA = m_tDateTimeAfter.Format("%Y-%m-%d")+"24";
	
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch; 	
	BOOL fFinished = FALSE; 
	CString strpath = GetDoc().GetAppPath() + LOGFILEDIR; 
	
	hSearch = FindFirstFile(strpath+"*CalcResult.mdb", &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
		return FALSE;

	while (!fFinished) 
	{
		LogFileName = CString(FileData.cFileName); 
		if(GetLog().ConnectCalcSet(strpath+LogFileName))
		{			
			if (sift)
				LoadCalcAnalyse(HisstrValueA,HisstrValueB);
			else
				LoadCalcToDisplay(HisstrValueA,HisstrValueB);
		}
		else
			continue;
		
		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
				fFinished = TRUE;  
		}
	} 

	if (!FindClose(hSearch)) 
	{ 
		strncpy(ez,GetLang().GetWarningText(14015),256);
		AfxMessageBox(ez); //"û�гɹ��ر��������"
	}

	LogFileName = GetDoc().GetAppPath()+strDataBase[0];
	if(!GetLog().ConnectCalcSet(LogFileName))
	{
		AfxMessageBox("���ݿ�CalcResult.mdb����ʧ�ܣ�");
		bConnectok = false;
		return FALSE;
	}

	return TRUE;
}

BOOL CSystemLogView::LoadHistoryProDisplay(BOOL sift)
{
	UpdateData(true);
	char ez[256]={""};

	m_datadisplay.ClearList();
	SetProHead();

	CString LogFileName;
	CString HisstrValueB,HisstrValueA;
	HisstrValueB = m_tDataTimeBefor.Format("%Y-%m-%d"); 
	HisstrValueA = m_tDateTimeAfter.Format("%Y-%m-%d")+"24";
	
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch; 
	BOOL fFinished = FALSE; 
	CString strpath = GetDoc().GetAppPath() + LOGFILEDIR; 
	
	hSearch = FindFirstFile(strpath+"*OperResult.mdb", &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE)  
		return FALSE;

	while (!fFinished) 
	{
		LogFileName = CString(FileData.cFileName); 
		if(GetLog().ConnectProSet(strpath+LogFileName))
			LoadProToDisplay(HisstrValueA,HisstrValueB,sift);
		else
			continue;
		
		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
				fFinished = TRUE;  
		}
	} 

	if (!FindClose(hSearch)) 
	{ 
		strncpy(ez,GetLang().GetWarningText(14015),256);
		AfxMessageBox(ez); //"û�гɹ��ر��������"
	}

	LogFileName = GetDoc().GetAppPath()+strDataBase[1];
	if(!GetLog().ConnectProSet(LogFileName))
	{
		AfxMessageBox("���ݿ�OperResult.mdb����ʧ�ܣ�");
		bConnectok = false;
		return FALSE;
	}

	return TRUE;
}

BOOL CSystemLogView::LoadHistoryPowerDisplay()
{
	UpdateData(true);
	char ez[256]={""};
	
	m_datadisplay.ClearList();
	SetPowerHead();

	CString LogFileName;
	CString HisstrValueB,HisstrValueA;
	HisstrValueB = m_tDataTimeBefor.Format("%Y-%m-%d"); 
	HisstrValueA = m_tDateTimeAfter.Format("%Y-%m-%d")+"24";
	
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch; 
	BOOL fFinished = FALSE; 
	CString strpath = GetDoc().GetAppPath() + LOGFILEDIR; 
	
	hSearch = FindFirstFile(strpath+"*LaserPower.mdb", &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
		return FALSE;

	while (!fFinished) 
	{
		LogFileName = CString(FileData.cFileName); 
	    if(GetLog().ConnectPowerSet(strpath+LogFileName))
			LoadPowerToDisplay(HisstrValueA,HisstrValueB);
		else
			continue;
		
		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
				fFinished = TRUE;
		}
	}

	if (!FindClose(hSearch)) 
	{ 
		strncpy(ez,GetLang().GetWarningText(14015),256);
		AfxMessageBox(ez); //"û�гɹ��ر��������"
	}	

	LogFileName = GetDoc().GetAppPath()+strDataBase[2];
	if(!GetLog().ConnectPowerSet(LogFileName))
	{
		AfxMessageBox("���ݿ�LaserPower.mdb����ʧ�ܣ�");
		bConnectok = false;
		return FALSE;
	}

	return TRUE;
}

BOOL CSystemLogView::LoadHistoryPowerParaDisplay()
{
	UpdateData(true);
	char ez[256]={""};
	
	m_datadisplay.ClearList();
	SetFilePropHead();

	CString LogFileName;
	CString HisstrValueB,HisstrValueA;
	HisstrValueB = m_tDataTimeBefor.Format("%Y-%m-%d"); 
	HisstrValueA = m_tDateTimeAfter.Format("%Y-%m-%d")+"24";
	
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch; 
	BOOL fFinished = FALSE; 
	CString strpath = GetDoc().GetAppPath() + LOGFILEDIR; 
	
	hSearch = FindFirstFile(strpath+"*FileParame.mdb", &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE)  
		return FALSE;

	while (!fFinished) 
	{
		LogFileName = CString(FileData.cFileName);	
		if(GetLog().ConnectPowerParaSet(strpath+LogFileName))
			LoadPowerParaToDisplay(HisstrValueA,HisstrValueB);
		else
			continue;
		
		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
				fFinished = TRUE; 
		}
	}

	if (!FindClose(hSearch)) 
	{ 
		strncpy(ez,GetLang().GetWarningText(14015),256);
		AfxMessageBox(ez); //"û�гɹ��ر��������"
	}	

	LogFileName = GetDoc().GetAppPath()+strDataBase[3];
	if(!GetLog().ConnectPowerParaSet(LogFileName))
	{
		AfxMessageBox("���ݿ�FileParame.mdb����ʧ�ܣ�");
		bConnectok = false;
		return FALSE;
	}

	return TRUE;
}

CString CSystemLogView:: GetListFieldName(int FieldNumb)
{
	HDITEM p;
	p.mask = HDI_TEXT; 
	TCHAR  lpBuffer[256];
	p.pszText = lpBuffer; 
	p.cchTextMax = 256; 
	CString str;
	
	m_datadisplay.GetHeaderCtrl()->GetItem(FieldNumb,&p);
	str = p.pszText;
	
	return  str;
} 

