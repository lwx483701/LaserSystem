#include <afxwin.h>         // MFC core and standard components
#include "dmccom.h"
#include "public.h"

#define GetAxisNo(AXISNO)		(AXISNO&0x0007)
#define GetCardNo(AXISNO)       (AXISNO&0xF0000)>>16

#define HeadLeft				0
#define HeadRight				1
#define HeadBoth                2

#define THICKNESSSCALE			2
#define TABXYSCALE				2

#define AXISTABX				0x00000	
#define AXISTABY				0x00001
#define AXISTAB					0x0000f		//TAB ID
#define AXISTHICKNESSL			0x10004		//左侧测厚
#define AXISTHICKNESSR			0x10005		//左侧测厚

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

class  __declspec(dllimport) CMotion
{
public:
	long Inital(int nMode,long* lCardSN);	//nMode=0 单BET；nMode=1 双BET，PCI卡+伺服光圈电机；nMode=2 双BET，外置卡+步进光圈电机；
											//nMode=3 双运动系统，XX+Galil(1842*2)
	long Release();

	void ResetCard(int nInCard=0);
	void Stop(U32 iAxisNo);

	long Home(U32 ulAxisNo) const;
	BOOL WaitStopWhenProgramming(U32 ulAxis);

	long MoveTo(U32 ulAxisNo, long desPos,U32 ulAcc,U32 ulDec, U32 ulMaxSpeed,U32 ulStartSpeed=0) const;
	BOOL WaitXYStop(int times,int ntime) const;								//20180202
	BOOL WaitStop(U32 ulAxis,int time=25) const;

	long QueryLimit(UINT ulAxisNo);
	BOOL GetMationSH(U32 ulAxisNo) const;
	long GetPos(U32 ulAxis) const;
	void SetPos(U32 ulAxisNo,F64 fPos)const;

	int QueryIOBit(U32 Data,U32 CardNo) const;
	long ChannelOutput(U32 ChanNo, BOOL bState,U32 CardNo);

	BOOL SetTableManuMove(UINT ulAxisNo,long lScale,BOOL bEnable);
	BOOL Thick(int nHead,U32 ulAxisNo);
	BOOL GetThickness(int nHead,U32 ulAxisNo,long thick[2]);

	CMotion();
	virtual ~CMotion();

	friend __declspec(dllimport) CMotion& GetMotion();
};
