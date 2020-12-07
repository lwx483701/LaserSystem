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
	"00FFBW0M040801160",	//0   �ϲ��ٴμ���
	"00FFBW0M040901161",	//1   ƽ̨ȡ�����
	"00FFBW0M041001159",	//2   ����׼��ȡ��
	"00FFBW0M04110115A",	//3   ��ʼ����
	"00FFBW0M04120115B",	//4   ���ӹ�ʧ��
	"00FFBW0M04130115C",	//5   �Ҳ�ӹ�ʧ��
	"00FFBW0M04140115D",	//6   ƽ̨��������
	"00FFBW0M04150115E",	//7   ���Ͽ���ȡ��
	"00FFBW0M04160115F",	//8   �������
	"00FFBW0M041701160",	//9   ��������
	"00FFBW0M041801161",	//10  ��ͣ(����Ļ)
	"00FFBW0M041901162",	//11  ��ͣ��λ
	"00FFBW0M04200115A",	//12  ���ϵ�ѭ��
	"00FFBW0M04210115B",	//13  ���ϵ�ѭ�� //һ������
	"00FFBW0M04220115C",	//14  ����ӹ�ѭ�� 
	"00FFBW0M04230115D",	//15  ����ӹ�ѭ��
	"00FFBW0M046701165",	//16  ����ѭ��
	"00FFBW0M046801166",	//17  ����ѭ��
	"00FFBW0M046901167",	//18  ����ƽ̨��������
	"00FFBW0M04700115F",	//19  ����ƽ̨ȡ�����
	"00FFBW0M047101160",	//20  ��������׼��ȡ��
	"00FFBW0M047201161",	//21  �������Ͽ���ȡ��
	"00FFBW0M047301162",	//22  ����NG׼��ȡ��
	"00FFBW0M047401163",	//23  ����NG����ȡ��
//	"00FFBW0M048301163",	//24  AGV����׼��				//20191107
//	"00FFBW0M048401164",	//25  AGVС����λ
//	"00FFBW0M048501165",	//26  AGV����׼��
	"00FFBW0M047901168",	//24  AGV����					//20191120
	"00FFBW0M048001160",	//25  AGV����
	"00FFBW0M048101161",	//26  AGV��λ
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
	0,//�������		 16
	0,//����׼�����	 17
	0,//���ϳ������	 18
	0,//���һ�Ű�		 19
	0,//���ϳ������	 20
	0,//ƽ̨�������	 21
	0,//����׼�����	 22
	0,//��е����ͣ		 23   
	0,//�������		 24
	0,//�ϲ�ȱ��		 25
	0,//���ϲ���		 26
	0,//���ϳ�ʱ����	 27		//ԭ�������ϳ�ʱ����11+16 �����޸�Ϊ�������а屨��
	0,//���ϳ�ʱ����	 28		//ԭ�������ϳ�ʱ����12+16 �����޸�Ϊ��е�ִ��󱨾�
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
	0,//����NG׼�����	 52 
	0,//����NG�������	 53
	0,//����ƽ̨������� 54
	0,//��������׼����� 55
	0,//�������ϳ������ 56
	0,//��������׼����� 57
	0,//�������ϳ������ 58
	0,//59
	0,//60  
	0,//61
	0,//62 
	0,//63
	0,//64
	0,//65
	0,//66
	0,//�ӹ������ϣ���� 67									//20190627
	0,//ƽ̨���԰�ȫ�ƶ� 68
	0,//AGV�������		 69									//20191107
	0,//AGV�������		 70
	0,//71
	0,//72
	0,//73
	0,//AGV���Ѱ���		 74									//20191120
	0,//AGV�������쳣	 75
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

	while(GetCOM(1).WriteDataToCom(buf,strlen(buf))==0)		//ָ��д��
	{
		countTimes++;

		Delay(200);

		if (countTimes==5)								//�ظ�5��
		{
//			GetDoc().SetLastWarningNo(99);				//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
			return "WRITEERROR";
		}
	}

	memset(buf,0,1024);
	Delay(50);											//ָ��д�����ʱһ���

	if(GetCOM(1).ReadDataFromCom(buf,1024)<=0)				//ָ��д������Ϣ����
	{
//		GetDoc().SetLastWarningNo(100);					//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
		return "READERROR";
	}
	else
	{
		if (strCompare==buf)							//���ָ����ȷ��
		{
			return "ACKOK";
		}
		else											//����ָ���Ķ�ȡ��У��
		{
			hexString=buf;
			
//			if (hexString.GetLength()<77 || AddHex(hexString.Mid(1,74))!=hexString.Mid(75,2))//������Ϣ�쳣���ַ������Ի��ߺ�У��δͨ����//20190725 �޸�
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
		strBegin=buf;								//��ͷ
		Str2Hex("0D 0A",buf);
		strEnd=buf;									//��β
		Str2Hex("06 30 30 46 46 0D 0A",buf);
		strCompare=buf;								//�Ա��ô�

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
		GetDoc().SetLastWarningNo(98);					//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
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
			GetDoc().SetLastWarningNo(99);				//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
			return false;
		}

		if (countTimes==5)
		{
			GetDoc().SetLastWarningNo(100);				//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
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
		GetDoc().SetLastWarningNo(98);					//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
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
			GetDoc().SetLastWarningNo(99);				//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
			return;
		}

		if (countTimes==5)
		{
			GetDoc().SetLastWarningNo(100);				//98 "�򿪴���ʧ��",99 "д����ʧ��",100 "������ʧ��"
			return;
		}
	}while(rtn=="READERROR");
		
	int steLength=rtn.GetLength();
	CString result=rtn.Right(steLength-5);
	CString tmep="",tmepresult="";

//	for (int i=0;i<69;i++)									//69�������źţ�����+����		//20190725
//	for (int i=0;i<78;i++)									//78�������źţ�����+����+AGV	//20191107
	for (int i=0;i<76;i++)									//76�������źţ�����+����+AGV	//20191120
	{
		tmep=result.Left(1);
		tmepresult=result;
		plcSignalInput[i]=atoi(tmep);
		result=tmepresult.Right(tmepresult.GetLength()-1);
	}
}

