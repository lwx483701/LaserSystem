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
	unsigned int deadTime;				//����ʱ��
	int laserTriggerAdjust;				//���弤�����巢��ʱ���
	unsigned int laserSyncWidth;		//����ͬ��ģʽ�µļ���������
	unsigned int laserSyncPeriod;		//����ͬ��ģʽ�µļ�����������
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
	unsigned int laserPulsePeriod;		//�����������ڣ������������壺
										//1�����ʲ���ʱ���������ڣ�
										//2���񾵼ӹ�ʱ�������ࣨ���趨�������С�������
	unsigned long laserPulseCount;		//�������������������������壺
										//1�����ʲ���ʱ���������������ڼ�ʱ����
										//2���񾵼ӹ�ʱ��������ű�ʶ�����ڶ���cycle��burst�����������ģʽ����
	bool allLaserOn;					//���������Ƿ�ȫ������
	unsigned int xOffset;				//�������ݵ���λֵ
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