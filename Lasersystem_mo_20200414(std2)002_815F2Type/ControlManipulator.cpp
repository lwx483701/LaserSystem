// ControlManipulator.cpp: implementation of the CControlManipulator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include "ControlManipulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CString plcSignalOutput[24]=
CString plcSignalOutput[27]=								//20191107
{ 
	"00FFBW0M040801160",	//0   料仓再次加料
	"00FFBW0M040901161",	//1   平台取了完成
	"00FFBW0M041001159",	//2   下料准备取料
	"00FFBW0M04110115A",	//3   开始运行
	"00FFBW0M04120115B",	//4   左侧加工失败
	"00FFBW0M04130115C",	//5   右侧加工失败
	"00FFBW0M04140115D",	//6   平台可以上料
	"00FFBW0M04150115E",	//7   下料可以取料
	"00FFBW0M04160115F",	//8   整体回零
	"00FFBW0M041701160",	//9   结束运行
	"00FFBW0M041801161",	//10  暂停(含光幕)
	"00FFBW0M041901162",	//11  暂停复位
	"00FFBW0M04200115A",	//12  上料单循环
	"00FFBW0M04210115B",	//13  下料单循环 //一键下料
	"00FFBW0M04220115C",	//14  左轴加工循环 
	"00FFBW0M04230115D",	//15  右轴加工循环
	"00FFBW0M046701165",	//16  翻板循环
	"00FFBW0M046801166",	//17  逆向循环
	"00FFBW0M046901167",	//18  逆向平台可以上料
	"00FFBW0M04700115F",	//19  逆向平台取料完成
	"00FFBW0M047101160",	//20  逆向下料准备取料
	"00FFBW0M047201161",	//21  逆向下料可以取料
	"00FFBW0M047301162",	//22  逆向NG准备取料
	"00FFBW0M047401163",	//23  逆向NG可以取料
//	"00FFBW0M048301163",	//24  AGV收料准备				//20191107
//	"00FFBW0M048401164",	//25  AGV小车到位
//	"00FFBW0M048501165",	//26  AGV送料准备
	"00FFBW0M047901168",	//24  AGV收料					//20191120
	"00FFBW0M048001160",	//25  AGV送料
	"00FFBW0M048101161",	//26  AGV到位
};

//int plcSignalInput[67]=
//int plcSignalInput[69]=									//20190627
//int plcSignalInput[78]=									//20191107
int plcSignalInput[76]=										//20191120
{ 
	0,//0
	0,//1
	0,//2
	0,//3
	0,//4
	0,//5
	0,//6
	0,//7
	0,//8
	0,//9
	0,//10
	0,//11
	0,//12
	0,//13
	0,//14
	0,//15
	0,//回零完成		 16
	0,//上料准备完成	 17
	0,//上料撤出完成	 18
	0,//最后一张板		 19
	0,//下料撤出完成	 20
	0,//平台上料完成	 21
	0,//下料准备完成	 22
	0,//机械手暂停		 23   
	0,//电机报警		 24
	0,//料仓缺料		 25
	0,//坏料仓满		 26
	0,//上料超时报警	 27		//原来的上料超时报警11+16 现在修改为过渡盘有板报警
	0,//下料超时报警	 28		//原来的下料超时报警12+16 现在修改为机械手错误报警
	0,//29
	0,//30
	0,//31
	0,//32
	0,//33
	0,//34
	0,//35
	0,//36
	0,//37
	0,//38
	0,//39
	0,//40
	0,//41
	0,//42    
	0,//43
	0,//44
	0,//45
	0,//46
	0,//47
	0,//48
	0,//49
	0,//50
	0,//51
	0,//逆向NG准备完成	 52 
	0,//逆向NG撤出完成	 53
	0,//逆向平台上料完成 54
	0,//逆向上料准备完成 55
	0,//逆向上料撤出完成 56
	0,//逆向下料准备完成 57
	0,//逆向下料撤出完成 58
	0,//59
	0,//60  
	0,//61
	0,//62 
	0,//63
	0,//64
	0,//65
	0,//66
	0,//加工（下料）完成 67									//20190627
	0,//平台可以安全移动 68
	0,//AGV送料完成		 69									//20191107
	0,//AGV收料完成		 70
	0,//71
	0,//72
	0,//73
	0,//AGV提醒按下		 74									//20191120
	0,//AGV收送料异常	 75
//	0,//76
//	0,//77
};

CControlManipulator::CControlManipulator()
{
	strACK="ACKOK";
	sendTimerNumber=0;
}

CControlManipulator::~CControlManipulator()
{
	
}

CControlManipulator& GetControlManipulator()
{
	static CControlManipulator  controlManipulator;
	return controlManipulator;
}

CString CControlManipulator::AddHex(CString &strData)
{
	int sum=0;
	CString result="";
	CString temp="";
	char ch;
	for(int i = 0; i < strData.GetLength(); i++)
	{
		ch=strData[i];
		sum+=ch;
	}
	while(sum/16!=0)
	{
		temp+=IntToHex(sum%16);
		sum/=16;
		if (sum<16)
		{
			temp+=IntToHex(sum);
		}
	};
	for ( i=0;i<temp.GetLength();i++)
	{
		result+=temp.GetAt(temp.GetLength()-i-1);
	}
	result=result.Right(temp.GetLength()-1);
	return result;
}

CString CControlManipulator::IntToHex(int namber)
{
    CString reslut="";
	if (namber<10)
	{	
		reslut.Format("%d",namber);
	}
	else
	{
		if (namber==10)
		{
			reslut="A";
		}
		else if(namber==11)
		{
			reslut="B"; 
		}
		else if(namber==12)
		{
			reslut="C"; 
		}
		else if(namber==13)
		{
			reslut="D"; 
		}
		else if(namber==14)
		{
			reslut="E"; 
		}
		else if(namber==15)
		{
			reslut="F"; 
		}
		else
			reslut="F"; 
	}
	return reslut;
}

int CControlManipulator::Str2Hex(CString str, char* data)
{
	int t,t1;
	int rlen=0,len=str.GetLength();
	for(int i=0;i<len;)
	{
		char l,h=str[i];
		if(h==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	return rlen;
}

char CControlManipulator::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;
}

CString CControlManipulator::ReadWritePLC(HANDLE hCom,CString hexString)
{
	strAllCommand="";
	strAllCommand+=strBegin;
	strAllCommand+=hexString;
//	strAllCommand+=AddHex(hexString);
	strAllCommand+=strEnd;
	
	char buf[1024];
	memset(buf,0,1024);
	strncpy(buf,(LPCTSTR)strAllCommand,sizeof(buf)); 

	int countTimes=0;

	while(GetCOM(1).WriteDataToCom(buf,strlen(buf))==0)		//指令写入
	{
		countTimes++;

		Delay(200);

		if (countTimes==5)								//重复5次
		{
//			GetDoc().SetLastWarningNo(99);				//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
			return "WRITEERROR";
		}
	}

	memset(buf,0,1024);
	Delay(50);											//指令写入后延时一会儿

	if(GetCOM(1).ReadDataFromCom(buf,1024)<=0)				//指令写入后的信息读入
	{
//		GetDoc().SetLastWarningNo(100);					//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
		return "READERROR";
	}
	else
	{
		if (strCompare==buf)							//输出指令后的确认
		{
			return "ACKOK";
		}
		else											//输入指令后的读取和校验
		{
			hexString=buf;
			
//			if (hexString.GetLength()<77 || AddHex(hexString.Mid(1,74))!=hexString.Mid(75,2))//输入信息异常（字符数不对或者和校验未通过）//20190725 修改
//			if (hexString.GetLength()<86 || AddHex(hexString.Mid(1,83))!=hexString.Mid(84,2))			//20191107
			if (hexString.GetLength()<84 || AddHex(hexString.Mid(1,81))!=hexString.Mid(82,2))			//20191120
				return "READERROR";
			else
				return buf;
		}
	}
}

HANDLE CControlManipulator::InitPLCCOM()
{
	char szCOM[20]={0};
	sprintf(szCOM,"COM%d",GetDoc().GetHandCOMNum());

	HANDLE hCom = INVALID_HANDLE_VALUE;
	hCom = GetCOM(1).OpenCOM(szCOM,19200);

	if (hCom != INVALID_HANDLE_VALUE)
	{
		char buf[16];
		memset(buf,0,16);
		
		Str2Hex("05",buf);							
		strBegin=buf;								//串头
		Str2Hex("0D 0A",buf);
		strEnd=buf;									//串尾
		Str2Hex("06 30 30 46 46 0D 0A",buf);
		strCompare=buf;								//对比用串

//		if ("ACKOK"!=ReadWritePLC(hCom,"00FFBW0M04084500000000000000000000000000000000000000000000000000000000000000000000027"))			//20190725
//		if ("ACKOK"!=ReadWritePLC(hCom,"00FFBW0M04084E000000000000000000000000000000000000000000000000000000000000000000000000000000B7"))	//20191107
		if ("ACKOK"!=ReadWritePLC(hCom,"00FFBW0M04084C000000000000000000000000000000000000000000000000000000000000000000000000000085"))		//20191120
		{
			GetCOM(1).CloseCOM();
			return INVALID_HANDLE_VALUE;
		}
		
		Delay(200);
		ReadAllPLCStatus();
		
		return hCom;
	}

	return INVALID_HANDLE_VALUE;
}

void CControlManipulator::ReleasePLCCOM()
{
	GetCOM(1).CloseCOM();
}

BOOL CControlManipulator::OperatorManipulator(int pinNumber)
{
	if(hComPLC==INVALID_HANDLE_VALUE) 
	{
		GetDoc().SetLastWarningNo(98);					//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
		return false;
	}

	CString rtn="";
	int countTimes=0;

	do
	{
		countTimes++;

		rtn=ReadWritePLC(hComPLC,plcSignalOutput[pinNumber]);

		if(rtn=="WRITEERROR")
		{
			GetDoc().SetLastWarningNo(99);				//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
			return false;
		}

		if (countTimes==5)
		{
			GetDoc().SetLastWarningNo(100);				//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
			return false;
		}
	}while(rtn!="ACKOK");

	return TRUE;
}

int CControlManipulator::GetPLCBitStatus(int bitNumber,int queryCOMIO)//ly mark 20140520
{
	if (queryCOMIO==0)
 		ReadAllPLCStatus();	
//	ASSERT(-1<bitNumber && 50>bitNumber);
//	ASSERT(-1<bitNumber && 67>bitNumber);
//	ASSERT(-1<bitNumber && 69>bitNumber);					//20190627
//	ASSERT(-1<bitNumber && 78>bitNumber);					//20191107
	ASSERT(-1<bitNumber && 76>bitNumber);					//20191120

    return !plcSignalInput[bitNumber];
}

void CControlManipulator::ReadAllPLCStatus()
{
	if(hComPLC==INVALID_HANDLE_VALUE) 
	{
		GetDoc().SetLastWarningNo(98);					//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
		return;
	}	

	CString rtn="";
	CString stringControl="";

//	stringControl="00FFBR0M04084532";					//20190725
//	stringControl="00FFBR0M04084E42";					//20191107
	stringControl="00FFBR0M04084C40";					//20191120

	int countTimes=0;

	do
	{
		countTimes++;

		rtn=ReadWritePLC(hComPLC,stringControl);

		if(rtn=="WRITEERROR")
		{
			GetDoc().SetLastWarningNo(99);				//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
			return;
		}

		if (countTimes==5)
		{
			GetDoc().SetLastWarningNo(100);				//98 "打开串口失败",99 "写串口失败",100 "读串口失败"
			return;
		}
	}while(rtn=="READERROR");
		
	int steLength=rtn.GetLength();
	CString result=rtn.Right(steLength-5);
	CString tmep="",tmepresult="";

//	for (int i=0;i<69;i++)									//69个输入信号：正向+逆向		//20190725
//	for (int i=0;i<78;i++)									//78个输入信号：正向+逆向+AGV	//20191107
	for (int i=0;i<76;i++)									//76个输入信号：正向+逆向+AGV	//20191120
	{
		tmep=result.Left(1);
		tmepresult=result;
		plcSignalInput[i]=atoi(tmep);
		result=tmepresult.Right(tmepresult.GetLength()-1);
	}
}

