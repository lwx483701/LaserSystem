#include <afxwin.h>         // MFC core and standard components

class __declspec(dllexport) CCOM 
{
public:
	CCOM();
	virtual ~CCOM();
	
//打开串口,并配置波特率,停止位,有效位,校验位
	HANDLE OpenCOM(LPCTSTR lpCOMName,DWORD dwBaudRate,BYTE byteStopbit=ONESTOPBIT);
//关闭串口
	void   CloseCOM();
//Write to com,return writen number; 0:fail
	DWORD  WriteDataToCom(LPCVOID lpBuffer,DWORD dwNumberToWrite);
//read data,return readed number,0:fail
    DWORD  ReadDataFromCom(LPVOID lpBuffer,DWORD dwNumberToRead);

	friend __declspec(dllexport) CCOM& GetCOM(int nChannel);		//nChannel：0->激光功率测量；1->上下料控制

private:
	HANDLE m_hCOM;
};

