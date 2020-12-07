// ControlManipulator.h: interface for the CControlManipulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLMANIPULATOR_H__0D19DF48_1A07_4BE9_9711_C1FB258324EC__INCLUDED_)
#define AFX_CONTROLMANIPULATOR_H__0D19DF48_1A07_4BE9_9711_C1FB258324EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CControlManipulator 
{
public:
	CControlManipulator();
	virtual ~CControlManipulator();
	
	friend CControlManipulator& GetControlManipulator(); 
	
	HANDLE InitPLCCOM();
	void ReleasePLCCOM();	

	BOOL OperatorManipulator(int pinNumber=-1);				//������е�� 0~15����Ԫ������
	int  GetPLCBitStatus(int bitNumber,int queryCOMIO=0);	//�õ�������Ԫ����״̬

    CString AddHex(CString &strData);
	CString strBegin,strEnd,strAllCommand,strCompare;

private:
	void ReadAllPLCStatus();								//һ��ȫ����ȡ���õ���Ҫ������PLC��Ԫ����״̬
	CString ReadWritePLC(HANDLE hCom,CString hexString);
	int Str2Hex(CString str, char *data);
	char HexChar(char c);
	CString IntToHex(int namber);

	HANDLE hComPLC;
	CString strACK;
	int sendTimerNumber;
};

#endif // !defined(AFX_CONTROLMANIPULATOR_H__0D19DF48_1A07_4BE9_9711_C1FB258324EC__INCLUDED_)
