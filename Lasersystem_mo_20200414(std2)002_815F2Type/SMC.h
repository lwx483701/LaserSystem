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

typedef struct
{
    int x;
    int y;
    unsigned int laserData;
} JumpAndFirePoint2D;

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
	long holeCount;
};

enum JobMode {DRILLMODE=0,DRILLBLOCKMODE,POWERMODE,POWERBLOCKMODE,WINDOWBLOCKMODE};
enum PulseMode {AOMMODE=0,LASERSYNCMODE,DOUBLELASERMODE,SINGLELASERMODE};
enum SettleMode {CLOSELOOP=0,SEMIOPENLOOP,FULLOPENLOOP};
enum ProcMode {CYCLEONLY=0,BURSTONLY,CYCLEANDBURST};

typedef vector<CString> CStringV;
typedef vector<int> BurstV;

BOOL _declspec(dllexport) GalvoInit(LaserPmr lp,PulseMode pm,SettleMode sm,CStringV& csV);
//BOOL _declspec(dllexport) GalvoInit(LaserPmr lp,PulseMode pm,SettleMode sm,const char* filePath);

BOOL _declspec(dllexport) GalvoRelease();
BOOL _declspec(dllexport) GalvoStatus(int nHeadNo);
BOOL _declspec(dllexport) GalvoCorrectionCreate(const char* corFile, short corTable);
BOOL _declspec(dllexport) GalvoCorrectionLoad(const char* corFile, short corTable, double kx, double ky,double phi, double xOffset, double yOffset);

BOOL _declspec(dllexport) GalvoJobLoadInit();
BOOL _declspec(dllexport) GalvoJobLoad(char* segmentName,unsigned short numPoints, JumpAndFirePoint2D *points,unsigned int laserOnTime);

//BOOL _declspec(dllexport) GalvoPmrSet(GalvoPmr gp);
BOOL _declspec(dllexport) GalvoJobExecute(ScanHead sh,GalvoPmr gp,PulsePmrV& ppV,XYDataV& xyV,XYDataV& xySubV,BlockData bd,JobMode jm);
BOOL _declspec(dllexport) GalvoCorrectionSetup(ScanHead sh, double kx, double ky,double phi, double xOffset, double yOffset);
BOOL _declspec(dllexport) GalvoJobExecuteNew(ScanHead sh,GalvoPmr gp,PulsePmrV& ppV,XYDataV& xyVL,XYDataV& xyVR,XYDataV& xySubV);	//20200729

BOOL StdProc(ScanHead sh,PulsePmrV& ppV,XYDataV& xyV,XYDataV& xySubV);
BOOL PreLoadProc(ScanHead sh,PulsePmrV& ppV,BlockData bd);
BOOL StdPower(ScanHead sh,PulsePmrV& ppV,XYDataV& xyV);
BOOL PreLoadPower(ScanHead sh,PulsePmrV& ppV);
BOOL PreLoadWindow(ScanHead sh,PulsePmrV& ppV,BlockData bd);

ProcMode ProcModeAnalyze(PulsePmrV& ppV,int& cycleCount,BurstV& burstCountV);
BOOL StdProcCycleOnly(ScanHead sh,PulsePmrV& ppV,int cycleCount,XYDataV& xyV,XYDataV& xySubV);
BOOL PreLoadProcCycleOnly(ScanHead sh,PulsePmrV& ppV,int cycleCount,BlockData bd);
BOOL StdProcCycleOnlyNew(ScanHead sh,PulsePmrV& ppV,int cycleCount,XYDataV& xyVL,XYDataV& xyVR,XYDataV& xySubV);	//20200729

//bool DoJumpTimeCalibration(unsigned int fieldSizeInBits, unsigned int minStepSizeInBits);
bool DoJumpTimeCalibration(ScanHead sh,unsigned int fieldSizeInBits, unsigned int minStepSizeInBits);		//20191015
void ResetJobState();
bool IsJobError();
bool IsJobAbort();
//bool SetGalvoFaultCheckMode(bool enable);
bool SetGalvoFaultCheckMode(ScanHead sh,bool enable);														//20191015
bool WaitPacketFinished(long lTimeInSeconds=20);
bool WaitJobStart(long lTimeInSeconds=20);
bool WaitJobFinished(long lTimeInSeconds=20);