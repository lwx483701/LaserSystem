#include <afxwin.h>         // MFC core and standard components
#include "AerotechInclude\A3200.h"
#include "public.h"

#define HeadLeft				0
#define HeadRight				1
#define HeadBoth                2

typedef unsigned char			U8;
typedef short					I16;
typedef unsigned short			U16;
typedef long					I32;
typedef unsigned long			U32;
typedef float					F32;
typedef double					F64;
typedef double					angle_t;

using namespace std;

void  Delay(int milliseconds);
void  DoEvent();

class  __declspec(dllexport) CXYMotion
{
public:
	A3200Handle GetControlHandle();											//20200306 Ôö¼Ó
	BOOL Inital();
//	BOOL Inital(const char* strHomePathName[2]);							//20200304
	long Release();

	void ResetCard(int nInCard=0);											//NULL
	void Stop(U32 iAxisNo);

	long Home(U32 ulAxisNo) const;
	BOOL WaitStopWhenProgramming(U32 ulAxis);

//	long MoveTo(U32 ulAxisNo, long desPos,U32 ulAcc,U32 ulDec,U32 ulMaxSpeed,U32 ulStartSpeed=0) const;
	long MoveTo(U32 ulAxisNo,double desPos,double acc,double dec,double speed);				//20200310
//	long MoveTo(long desPosX,long desPosY);
	long MoveTo(double desPosX,double desPosY,double* acc,double* dec,double* speed);		//20200310
	BOOL WaitStop(U32 ulAxis,int time=25);
//	long GetPos(U32 ulAxis) const;											//20200304
	long GetFPos(U32 ulAxis) const;
	long GetRPos(U32 ulAxis) const;
//	void SetPos(U32 ulAxisNo,F64 fPos)const;

	long QueryLimit(UINT ulAxisNo);
	BOOL GetMationSH(U32 ulAxisNo) const;
	int QueryIOBit(U32 Data,U32 CardNo) const;								//NULL
	long ChannelOutput(U32 ChanNo, BOOL bState,U32 CardNo);					//NULL

	BOOL SetTableManuMove(UINT ulAxisNo,long lScale,BOOL bEnable);

	CXYMotion();
	virtual ~CXYMotion();

	friend __declspec(dllexport) CXYMotion& GetXYMotion();

private:
	BOOL WasStopWhenProgramming(U32 ulAxis);
//	BOOL WasStop(U32 ulAxis);

	A3200Handle m_hControl;
	char* m_strHomePathName[2];													//20200304
};

