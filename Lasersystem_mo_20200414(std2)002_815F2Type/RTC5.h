#include <afxwin.h>         // MFC core and standard components
#include <string>
#include <vector>
using namespace std;

typedef enum
{
    SH_Head1,		// 0: XY2-100 Extended, GSBus Head 2
	SH_Head2,		// 1: XY2-100,  GSBus Head 1
	SH_HeadBoth		// 2: both at the same time
} ScanHead;

struct LaserPmr
{
	unsigned int deadTime;				//死区时间
	int laserTriggerAdjust;				//定义激光脉冲发射时间点
	unsigned int laserSyncWidth;		//定义同步模式下的激光脉冲宽度
	unsigned int laserSyncPeriod;		//定义同步模式下的激光脉冲周期
};

struct GalvoPmr
{
	unsigned int jumpSpeed;
	unsigned int jumpDelay;
	unsigned int jumpZeroLengthDelay;
	unsigned int jumpLengthLimit;
	unsigned int markSpeed;
	unsigned int markDelay;
	unsigned int polyDelay;
};

struct PulsePmr
{
	unsigned int laserOnTime;
	unsigned int laser1;
	unsigned int laser2;
	unsigned int laserOnDelay;
	unsigned int laserOffDelay;
	unsigned int laserPulsePeriod;		//定义脉冲周期，它有两种意义：
										//1、功率测量时的脉冲周期；
										//2、振镜加工时的脉冲间距（或设定间隔或最小间隔）；
	unsigned long laserPulseCount;		//激光脉冲数量，它有两种意义：
										//1、功率测量时的脉冲数量（用于计时）；
										//2、振镜加工时的脉冲序号标识（用于定义cycle、burst或者组合脉冲模式）；
	bool allLaserOn;					//坐标数据是否全部出光
	unsigned int xOffset;				//坐标数据的移位值
	unsigned int yOffset;
};
typedef vector<PulsePmr> PulsePmrV;

struct XYData
{
	int coordX;
	int coordY;
	bool laserON;
};
typedef vector<XYData> XYDataV;

struct BlockData
{
	int subAreaNo;
	int toolNo;
};

enum JobMode {DRILLMODE=0,DRILLBLOCKMODE,POWERMODE,POWERBLOCKMODE};
enum PulseMode {AOMMODE=0,LASERSYNCMODE,DOUBLELASERMODE,SINGLELASERMODE};
enum SettleMode {CLOSELOOP=0,SEMIOPENLOOP,FULLOPENLOOP};
enum ProcMode {CYCLEONLY=0,BURSTONLY,CYCLEANDBURST};

typedef vector<CString> CStringV;
typedef vector<int> BurstV;

BOOL _declspec(dllexport) GalvoInit(LaserPmr lp,PulseMode pm,SettleMode sm,CStringV& csV);
BOOL _declspec(dllexport) GalvoRelease();
BOOL _declspec(dllexport) GalvoStatus(int nHeadNo);
BOOL _declspec(dllexport) GalvoCorrectionCreate(const char* corFile, short corTable);
BOOL _declspec(dllexport) GalvoCorrectionLoad(const char* corFile, short corTable, double kx, double ky,double phi, double xOffset, double yOffset);
BOOL _declspec(dllexport) GalvoJobLoad(JobMode jm);
BOOL _declspec(dllexport) GalvoJobExecute(ScanHead sh,GalvoPmr gp,PulsePmrV& ppV,XYDataV& xyV,XYDataV& xySubV,BlockData bd,JobMode jm);
void _declspec(dllexport) GalvoCorrectionSetup(int nHead, double kx, double ky,double phi, double xOffset, double yOffset);

BOOL StdProc(ScanHead sh,PulsePmrV& ppV,XYDataV& xyV,XYDataV& xySubV);
BOOL PreLoadProc(ScanHead sh,PulsePmrV& ppV,BlockData bd);
BOOL StdPower(ScanHead sh,PulsePmrV& ppV,XYDataV& xyV);
BOOL PreLoadPower(ScanHead sh,PulsePmrV& ppV,BlockData bd);

ProcMode ProcModeAnalyze(PulsePmrV& ppV,int& cycleCount,BurstV& burstCountV);
BOOL StdProcCycleOnly(ScanHead sh,PulsePmrV& ppV,int cycleCount,XYDataV& xyV,XYDataV& xySubV);

void ComSleep(int delay);
BOOL WaitListFinished(long lTimeInSeconds=60);
//int GetJumpTimeInUs(long distInBit,int jumpDelay);
int GetScannerDelay(long distInBit);