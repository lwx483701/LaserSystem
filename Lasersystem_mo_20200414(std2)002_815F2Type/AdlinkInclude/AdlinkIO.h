#include <afxwin.h>         // MFC core and standard components

typedef unsigned char			U8;
typedef short					I16;
typedef unsigned short			U16;
typedef long					I32;
typedef unsigned long			U32;
typedef float					F32;
typedef double					F64;
typedef double					angle_t;

class __declspec(dllexport) CAdlinkIO
{
public:
	BOOL Inital(U32 CardNo);
    BOOL Release(U32 CardNo);

	int DigitalInput(U32 CardNo,U16 PortNo);
	BOOL DigitalOutput(U32 CardNo,U16 PortNo,U16 State);

	double AnalogInput(U32 CardNo,U16 ChanNo);
	BOOL AnalogOutput(U32 CardNo,U16 ChanNo,F64 Data);
	
	CAdlinkIO(int nMode);
	virtual ~CAdlinkIO();

	friend __declspec(dllexport) CAdlinkIO& GetIO(int nMode);
	
private:	
	int m_nIOMode;				//0£ºPCI¿¨£»1£º·Ö²¼Ê½
};

