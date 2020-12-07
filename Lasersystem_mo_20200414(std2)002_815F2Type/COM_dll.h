#include <afxwin.h>         // MFC core and standard components

class __declspec(dllexport) CCOM 
{
public:
	CCOM();
	virtual ~CCOM();
	
//�򿪴���,�����ò�����,ֹͣλ,��Чλ,У��λ
	HANDLE OpenCOM(LPCTSTR lpCOMName,DWORD dwBaudRate,BYTE byteStopbit=ONESTOPBIT);
//�رմ���
	void   CloseCOM();
//Write to com,return writen number; 0:fail
	DWORD  WriteDataToCom(LPCVOID lpBuffer,DWORD dwNumberToWrite);
//read data,return readed number,0:fail
    DWORD  ReadDataFromCom(LPVOID lpBuffer,DWORD dwNumberToRead);

	friend __declspec(dllexport) CCOM& GetCOM(int nChannel);		//nChannel��0->���⹦�ʲ�����1->�����Ͽ���

private:
	HANDLE m_hCOM;
};

