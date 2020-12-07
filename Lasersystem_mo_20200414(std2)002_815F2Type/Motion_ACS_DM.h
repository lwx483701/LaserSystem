#include <afxwin.h>         // MFC core and standard components
#include "ACSC.h"
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

void  Delay(int milliseconds);
void  DoEvent();

class  __declspec(dllexport) CXYMotion
{
public:
	BOOL Inital();
	long Release();

	void ResetCard(int nInCard=0);											//NULL
	void Stop(U32 iAxisNo);

	long Home(U32 ulAxisNo) const;
	BOOL WaitStopWhenProgramming(U32 ulAxis);

	long MoveTo(U32 ulAxisNo, long desPos,U32 ulAcc,U32 ulDec,U32 ulMaxSpeed,U32 ulStartSpeed=0) const;
	long MoveTo(long desPosX,long desPosY);
	BOOL WaitStop(U32 ulAxis,int time=25);
	long GetPos(U32 ulAxis) const;
//	void SetPos(U32 ulAxisNo,F64 fPos)const;

	long QueryLimit(UINT ulAxisNo);
	BOOL GetMationSH(U32 ulAxisNo) const;
	int QueryIOBit(U32 Data,U32 CardNo) const;
	long ChannelOutput(U32 ChanNo, BOOL bState,U32 CardNo);					//NULL

	void InitalTableManuMove(UINT ulAxisNo,double dbFactor);
	BOOL SetTableManuMove(UINT ulAxisNo,long lScale,BOOL bEnable);

	CXYMotion();
	virtual ~CXYMotion();

	friend __declspec(dllexport) CXYMotion& GetXYMotion();

private:
	BOOL WasStopWhenProgramming(U32 ulAxis);
	long WasStop(U32 ulAxis) const;

	HANDLE m_hComm;		// communication handle

	UINT m_nMasterAxisNo;
	double m_dbWheelFactor;
};
