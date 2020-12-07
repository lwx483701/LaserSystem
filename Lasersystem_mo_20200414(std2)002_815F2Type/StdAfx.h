// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#if !defined(AFX_STDAFX_H__5D77F19A_9685_11D2_899F_0040055A6A93__INCLUDED_)
#define AFX_STDAFX_H__5D77F19A_9685_11D2_899F_0040055A6A93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <math.h>
#include <afxpriv.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif

#include "Visualfx.h"
#include "FileComDefine.h"
#include "resource.h"
#include "transParentButton.h"
#include "cchecksk.h"
#include "ControlTool/SmartEdit/SmartEdit.h"
#include "ControlTool/TreeCtrl/TreeCtrlEx.h"
#include "ControlTool/Progress/ProgressWnd.h"
#include "Log.h"
#include "info.h"
#include "inifile.h"
#include "SysParameter.h"

//----------------------------编译开关------------------------
//代工厂定制功能
//#define OEM											//20191219 取消

//纯文件导入功能
//#define ONLYFILE										//20190806 增加

#ifdef ONLYFILE
#define NEWE2
#else
//------------------------------------------------------
//时间控制加密狗编译开关
//#define SENTINAL
//#define DOUBLEPROTECT									//20190517 增加

//硬件功能编译开关
//#define HARDWARE

//系统登录功能编译开关
//#define LOGIN

//机型编译开关
#define NEWE2
//#define AOMTYPE
//#define F2TYPE
//#define L2TYPE001
//#define L2TYPE
//#define F2TYPE815										//20200818 增加

//-----------------------------------------------------
#endif

//无上下料系统时的版本
//#define NOLANDULSYSTEM				//20191203 增加	//20191219 取消
//上下料新指令
//#define UNLOADISOK					//20190627		//20191219 取消
//上料时平台真空释放方式
//#define TABLEADSORBFIRST								//20191219 取消
//#define HANDADSORBFIRST				//20181203		//20191219 取消
//厂家定制编译开关
//#define CHONGDA		//20170314 崇达 20180613追加	//20191219 取消
//#define ZHIHAO		//20171128 志浩					//20191219 取消
#define DINGYING										//20200707 定颖电子

//分区加工时进行位移量补偿
//#define SETPROCOFFSET									//20181203 L2-001

//用于2D平台校正
//#define TABLE2DCALI									//20180417
#define DIVIDINGLINE -13500		//-23500

//用于CPK精度测试
//#define CPKTEST										//20180515

//用于振镜精度测试时的精度数据记录
#define GALVOTEST										//20171129 增加

//用于保存识别失败的标靶的图像文件
//#define BMPFILETEST

//用于变换算法的对比测试
//#define TRANSFORMTEST									//20190403 增加	//20190731	//20191106 取消

//用于有上下料时的手动加工拷机测试
//#define MACHINEHOTTEST								//20190823

//SMC预加载功能测试（用于无上下料时的手动加工拷机测试）
//#define PRELOADTEST									//20180827 增加

//首发延时不设限（或用于延时放开测试）
//#define D2CTYPE										//20200330 增加

//矩阵路径优化测试
//#define MATRIXPATHTEST								//20200330 增加

//内存使用情况监测
#define MEMORYSTATUSMONITOR								//20200331 增加

//单轴变换(无振镜变换)模式相关测试						//20200402 增加
//#define ONEAXISDATATRANSFORMTEST						//OAM 单轴模式
//#define ONEAXISDATATRANSFORMANDPROC					//proc							
#define ONEAXISDATATRANSFORMANDFIND					//find
//#define ONEAXISDATATRANSFORMANDDRILL					//point
//-------------------------------------------------------------


#ifdef DINGYING
#include "Dynamic.h"
#pragma comment(lib,"userdll\\Dynamic.lib")
#endif

#ifdef SENTINAL
#pragma comment(lib,"userdll\\hasp_windows_23885.lib")
#endif

#ifdef HARDWARE
#define USEIMAGE
#define USEMOTION
#define USESCANLAB 
#define USEIOCARD
#define USECOM											//使用串口
#endif

#ifdef NEWE2
#define DOUBLEBET										//双BET系统
#define IOMODE					1
#define LASERMAXWIDTH			25						//用于单J5VV的脉宽设定 
#define APERTURE18

#define ADLINKIO

#define AVT
//#define PICOLO

#define NEWAVT											//20191015 用于百万像素相机的测试

//#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
#define RTC5DLL

#define USERCOGNEX
#endif

#ifdef AOMTYPE
#define HUAWEILASERSOURCE								//采用华为电源时增加的电源异常报警
//#define LASERMONITOR									//激光器状态网络监控
#define NOONEKEY										//无一键上下料功能		//20190927

#define IOMODE					0
#define LASERMAXWIDTH			15						//用于AOM方式的脉宽设定
#define APERTURE18

#define ADLINKIO

#define AVT
//#define PICOLO

#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
//#define RTC5DLL

#define USERCOGNEX
#endif

#ifdef F2TYPE
#define DOUBLEBET										//双BET系统
#define DOUBLELASER										//双激光器系统
#define APTMOTORISSERVO									//伺服光圈系统//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//用于单/双J5VV的脉宽设定 
#define APERTURE18

//#define HIKAGV											//20191107 增加

//#define USEDMSYSTEM

#ifdef USEDMSYSTEM										//20190305
#define AEROTECHDMSYSTEM								//Aerotech double motion system	
//#define ACSDMSYSTEM									//ACS double motion system
#endif

#define ADLINKIO

#define AVT
//#define PICOLO

#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
//#define RTC5DLL

#define USERCOGNEX
#endif

#ifdef L2TYPE001										//20200227 内容修改
//#define GREENOILBOARD									//20190402
#define DOUBLEBET										//双BET系统
#define DOUBLELASER										//双激光器系统
#define APTMOTORISSERVO									//伺服光圈系统//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//用于单/双J5VV的脉宽设定 
#define APERTURE18
#define APERTURE15

//#define ACSMOTION										//20200414	取消
//#define GALILMOTION									//20200414  取消

#define USEDMSYSTEM										//使用双运动系统(double motion system)

#ifdef USEDMSYSTEM
#define AEROTECHDMSYSTEM								//Aerotech double motion system	
//#define ACSDMSYSTEM									//ACS double motion system
#endif

#define ADLINKIO

//#define AVT
#define PICOLO

//#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
//#define RTC5DLL
#define SMCDMDLL

#define USERCOGNEX
#endif

#ifdef L2TYPE
#define DOUBLEBET										//双BET系统
#define DOUBLELASER										//双激光器系统
#define APTMOTORISSERVO									//伺服光圈系统//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//用于单/双J5VV的脉宽设定 
#define APERTURE18

#define USEDMSYSTEM										//使用双运动系统(double motion system)	//20190305

#ifdef USEDMSYSTEM										//20190305
//#define AEROTECHDMSYSTEM								//Aerotech double motion system	
#define ACSDMSYSTEM									//ACS double motion system
#endif

#define ADLINKIO

#define AVT
//#define PICOLO

#define NEWAVT											//20190517 增加

//#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
#define RTC5DLL
//#define SMCDMDLL										//20200731 增加

#define USERCOGNEX
#endif

#ifdef F2TYPE815
#define DOUBLEBET										//双BET系统
#define DOUBLELASER										//双激光器系统
#define APTMOTORISSERVO									//伺服光圈系统//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//用于单/双J5VV的脉宽设定 
#define APERTURE18

//#define HIKAGV											//20191107 增加

#define USEDMSYSTEM

#ifdef USEDMSYSTEM										//20190305
#define AEROTECHDMSYSTEM								//Aerotech double motion system	 修改点: 20200818  20200819
//#define ACSDMSYSTEM									//ACS double motion system
#endif

#define ADLINKIO

#define AVT
//#define PICOLO

#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
//#define RTC5DLL

#define USERCOGNEX
#endif

#include "COM_dll.h"
#pragma comment(lib,"userdll\\COM_dll.lib")

#include "Motion_Galil.h"
#pragma comment(lib,"userdll\\Motion_Galil.lib")

#ifdef AEROTECHDMSYSTEM
#include "Motion_Aerotech.h"
#pragma comment(lib,"userdll\\Motion_Aerotech.lib")
#endif

#ifdef ACSDMSYSTEM
#include "Motion_ACS_DM.h"
#pragma comment(lib,"userdll\\Motion_ACS_DM.lib")
#endif

#ifdef ADLINKIO
#include "AdlinkInclude\\AdlinkIO.h"
#pragma comment(lib,"userdll\\IO_Adlink.lib")
#endif

#ifdef AVT
#include "AVTInclude\Grabber_AVT.h"	
#pragma comment(lib,"userdll\\Grabber_AVT.lib")
//#pragma comment(lib,"userdll\\FGCamera.lib")
#endif

#ifdef PICOLO
#include "PicoloInclude\Grabber_Picolo.h"
#pragma comment(lib,"userdll\\Grabber_Picolo.lib")
#endif

#ifdef SMCDLL
#include "SMC.h"
#pragma comment(lib,"userdll\\Galvo_SMC.lib")
//SMC振镜系统测试时的分区加工时间异常判断
//#define SMCTEST							//20191219 取消
//#define SMCPreLoad						//20171122 增加	//NPL(NoPreLoad)
//#define SMCNewCorType						//20180423 增加
//#define SMCCaliDLL						//20190716 增加	//Ca(Cali)
#define SMCAdjust							//20190902 增加	//Ad(Adjust)
#endif

#ifdef SMCDMDLL
#include "SMC.h"
#pragma comment(lib,"userdll\\Galvo_SMC_DM.lib")
//#define SMCCaliDLL
#define SMCAdjust
#endif

#ifdef RTC3DLL
#include "RTC3.h"
#pragma comment(lib,"userdll\\Galvo_RTC3.lib")
#define CTI 
#endif

#ifdef RTC4DLL
#include "RTC4.h"
#pragma comment(lib,"userdll\\Galvo_RTC4.lib")
#define CTI 
#endif

#ifdef RTC5DLL
#include "RTC5.h"
#pragma comment(lib,"userdll\\Galvo_RTC5.lib")
#endif

#ifdef USERCOGNEX
#include "Finder_Cognex.h"
#pragma comment(lib,"userdll\\Finder_Cognex.lib")
#endif

//光圈位数编译开关
//#define APERTURE12

#ifdef APERTURE18
#ifndef APERTURE15
	#define APTCIRCLEPLS            2777.7778	//50000/18  //18光圈
#else
	#define APTCIRCLEPLS            3333.3333	//50000/15  //15光圈
#endif
#else
#ifndef APERTURE12
	#define APTCIRCLEPLS            6250		//50000/8   //8光圈
#else
	#define APTCIRCLEPLS            4166.6667	//50000/12  //12光圈
#endif
#endif

//测厚报警功能编译开关
#define USEAUTOTHICKERROR

//日志功能编译开关
#define USELOG

//使用PP型激光器时的编译开关
//#define PPLASER

//使用CCS环形光源时的编译开关
//#define CCSRING

//采用C型机硬件接口方案//ly add 20110115
//激光预热阀门，C型机取消激光预热功能，只有机器预热
#define IO_C

//有无长短光路切换,目前只有C#1号机要定义为0
#define LSPATH_CHECKING  0		//仅有长光路，无短光路
//#define LSPATH_CHECKING  1	//有长短两条光路，可进行切换

//高电平表示激光上电OK,新工艺都是高电平
#define IO_LASERONOK_HIGH 

//高电平表示门保护灯被挡,目前C#1是高电平被挡
//#define DoorPrt_HighLevel

//机器调试用版本编译开关
//#define LESSWARN

//调试用,MoveTo(...)无软限位限制
//#define NO_SOFT_LIMIT
//-------------------------------------------------------------------

extern  BOOL LeftPareSt;
extern  BOOL RightPareSt;

void  Delay(int milliseconds);
void  DoEvent();

typedef unsigned char			U8;
typedef short					I16;
typedef unsigned short			U16;
typedef long					I32;
typedef unsigned long			U32;
typedef float					F32;
typedef double					F64;
typedef double					angle_t;

#define WM_DISPFILEINFO			(WM_USER+511)
#define WM_DISPLAY				(WM_USER+512)
#define WM_UNDISPLAY			(WM_USER+513)
#define WM_DISPDRILLINFO        (WM_USER+514)
#define WM_DISPPROCINFO         (WM_USER+515)
#define WM_DISPMATCHINFO        (WM_USER+516)//ly add 20130724
#define WM_INPUTCHECK			(WM_USER+520)
#define WM_INPUTUNCHECK			(WM_USER+521)
#define WM_TOOLPARASHOW			(WM_USER+530)
#define WM_USERKEYUP            (WM_USER+540)
#define WM_USERKEYDOWN          (WM_USER+541)
#define WM_REFLASHPOINT         (WM_USER+542)
#define WM_USERUPDATESELECTFILE (WM_USER+543)
#define WM_USERUPDATESTATUSBAR  (WM_USER+544)
#define WM_USERUPDATERESPONSE   (WM_USER+545)
#define WM_USERUPDATEFILANAME	(WM_USER+546)
//#define MINLASERPERIOD		200						//20191216	//20191219 取消
#define DMCNOERROR              0						//由于ACS库的存在才增加的 20180523
#define MaxPathLen              256
#define PI						3.1415926
#define MAXTESTPOS				450000
#define OUTSIZETHRED			0.1						//Cognex特征阈值参数
#define	CCDLENSMAG				1						//CCD成像镜头放大倍数
#define TABLECOMPRANGE          1000
#define TABLERESETPOS			-465000
#define SCANSIZEMIN             30
#define LOADANDUNLOADDELAY		50
#define	PATTERNDOTNUM			11						//11 点阵校正时的加工点数		//20200417 test

#define TABADJRTLX				780000					//标准台面机型与大台面机型之间的差异
#define TABADJRTLY				-402000

//#define THICKNESSSCALE		2
//#define TABXYSCALE			2

#ifdef AVT
#ifdef NEWAVT
#define IMAGEPIXELX             4.65/0.996/CCDLENSMAG		//20190513 修改 1.04->0.996	 	 
#define IMAGEPIXELY             4.65/0.996/CCDLENSMAG
#else
#define IMAGEPIXELX             8.3/0.996/CCDLENSMAG		//CCD:780*580 8.3	//20190510	修正	//20190513 修改 1.04->0.996	 	 
#define IMAGEPIXELY             8.3/0.996/CCDLENSMAG		//CCD:780*580 8.3
#endif
#else
#define IMAGEPIXELX             8.6/1.04/CCDLENSMAG		//8.6/CCDLENSMAG	//CCD cs8620ci cell size:　8.6*8.3 um				 	 
#define IMAGEPIXELY             8.6/1.04/CCDLENSMAG		//8.3/CCDLENSMAG	//20190418  修改             
#endif 

#define IO_ON					1
#define IO_OFF					0

#define MIO_ON					1
#define MIO_OFF				    0

#define HeadLeft				0
#define HeadRight				1
#define HeadBoth                2

#define LEFTCHAN				0		//左通道
#define RIGHTCHAN				1		//右通道
#define COAXIAL					0		//同轴
#define	RINGED					1		//环形

#define OUTERMAINPATTERN		0    
#define INNERPATTERN			1  
#define GALNOMATRIX				2  
#define GALNOOFFSET				3
#define CCDINTERVAL				4
#define LOCALMARKPATTERN		5

#define TESTPATTERNNAMELP       "bmp\\LPointStd.bmp"
#define TESTPATTERNNAMESP       "bmp\\SPointStd.bmp"
#define GLASSPATTERN			"bmp\\GlassStd.bmp"
#define REPEATPATTERN			"bmp\\CrossStd.bmp"
#define TESTTARGETNAME          "bmp\\test.bmp"
#define BMPFILEDIR              "bmp\\"
#define TOOLPARAEXT             ".tpm"
#define INFODIR                 "info\\info.txt"
#define POWERDIR                "info\\power.txt"					//20180404 取消此处的记录
#define LOGFILEDIR              "log\\"
#define LPATHADJDIR             "LPathC\\"
#define SPATHADJDIR             "SPathC\\"
#define SCALEDIR                "info\\scale.txt"					//20180404 取消此处的记录

#define TABBASE					1
#define TABCAPT					12
#define GetFormNo(TabNo,FormNo) TABBASE+TabNo*TABCAPT+FormNo

#define VIEWBASE                GetFormNo(0,0)
#define FILEINFOSETBASE         GetFormNo(1,0)
#define FILEINFOSETTINGVIEW     GetFormNo(1,1)
#define TOOLPARAVIEW			GetFormNo(1,2)
#define IMAGEPARASETVIEW        GetFormNo(1,3)
#define INGREDIENTINFOVIEW		GetFormNo(1,4)

#define MAINRUNVIEW             GetFormNo(3,0)
             
#define MAINTAINBASE            GetFormNo(4,0) 
#define SIGNALINPUTVIEW         GetFormNo(4,1)
#define SIGNALOUTPUTVIEW        GetFormNo(4,2)
#define MOTIONCONTROLTESTVIEW   GetFormNo(4,3)
#define TESTFUCTIONVIEW         GetFormNo(4,4)
#define LOADUNLOADVIEW          GetFormNo(4,5)

#define PARAMETERBASE           GetFormNo(2,0) 
#define SYSPARAMVIEW            GetFormNo(2,1)
#define OPERATEREFCOORDVIEW     GetFormNo(2,2)
#define PROCPARAVIEW            GetFormNo(2,3)
#define MOTIONPARAMETERVIEW     GetFormNo(2,4)
#define MOTIONPOSITIONERRVIEW   GetFormNo(2,5)
#define USERINFOVIEW            GetFormNo(2,6)

//#define GetAxisNo(AXISNO)		(AXISNO&0x0007)
#define GetAxisNo(AXISNO)		(AXISNO&0x000f)
#define GetCardNo(IOBIT)        (IOBIT&0xf0000)>>16
#define GetIOBit(IOBIT)			(IOBIT&0x00ff) 

//Axis
#define AXISTAB					0x0000f		//TAB ID
//兼容性保留
#define AXISLOADX				0x20004     //上料升降
#define AXISLOADY				0x20005		//上料平移
#define AXISUNLOADX				0x20002		//下料仓升降电机
#define AXISUNLOADY				0x20006		//下料平移电机

#ifdef NEWE2
//card1
#define AXISTABX				0x00000
#define AXISTABY				0x00001
//card2
#define AXISLEFTZ				0x10000
#define AXISRIGHTZ				0x10001
#define AXISBETSUB				0x10002		//从动轴1
#define AXISBETPRI				0x10003		//主动轴1
//card3
#define AXISAPT					0x20000		//光圈1
#define AXISAPT2				0x20001		//光圈2
#define AXISBETSUB2				0x20002     //从动轴2
#define AXISBETPRI2				0x20003		//主动轴2	

#else	//NEWE2

#ifdef USEDMSYSTEM										//20190507
//card1
#define AXISTABX				0x00000
#define AXISTABY				0x00001
//card2
#define AXISLEFTZ				0x10000
#define AXISBETSUB				0x10001		//从动轴
#define AXISBETPRI				0x10002		//主动轴
#define AXISAPT					0x10003		//光圈
//card3
#define AXISRIGHTZ				0x20000
#define AXISBETSUB2				0x20001     //从动轴
#define AXISBETPRI2				0x20002		//主动轴
#define AXISAPT2				0x20003		//光圈
//测厚轴												//20190626
#define AXISLEFTZTHICK			0x10000
#define AXISRIGHTZTHICK			0x20001

#else	//USEDMSYSTEM
//card1
#define AXISTABX				0x00000
#define AXISTABY				0x00001
#define AXISBETSUB				0x00002		//从动轴
#define AXISBETPRI				0x00003		//主动轴
//card2
#define AXISLEFTZ				0x10000
#define AXISRIGHTZ				0x10001
#define AXISAPT					0x10003		//光圈
//card3
#define AXISBETSUB2				0x20000     //从动轴
#define AXISBETPRI2				0x20001		//主动轴
#define AXISAPT2				0x20003		//光圈

#endif	//USEDMSYSTEM
	
#endif	//NEWE2	
 
/*--------------------IO口定义---------------------------

  0xabcd  a: card no.        0:    1842-1
							 1:    1842-2
							 2:    1842-3
							 3:    7200-1
							 4:    7200-2
							 5:    9112 
      b&c&d: bit no.      0~1F: 0~1F

--------------------------------------------------------*/
/*--------------------输出口定义------------------------*/
///DMC-1842-3用I/O扩展板DB14064 DO 定义？？？
#define  OLOADUPRIGHT                   0x20011  //上料右侧机械手上 DO0
#define  OLOADUPLEFT                    0x20012  //上料左侧机械手上 DO1
#define  OLOADDOWNRIGHT                 0x20013  //上料右侧机械手下 DO2
#define  OLOADDOWNLEFT                  0x20014  //上料左侧机械手下 DO3
#define  OLOADVACUUMCHRIGHT             0x20015  //上料右侧机械手真空电磁阀
#define  OLOADVACUUMCHLEFT				0x20016  //
#define	 OLOADPUFF						0x20017  //上料吹料电磁阀
#define	 OLOADSHACKE					0x20018  //上料抖料电磁阀
#define  OLOADSNAPX       				0x20019  //定位X
#define  OLOADSNAPY       				0x2001A  //定位y 
#define  OLOADDOLLYLOCK					0x2001B  //上料小车锁定
///reserved
///reserved
///reserved
#define  OUNLOADUPLEFT                  0x2001F //下料左侧机械手上
#define  OUNLOADDOWNLEFT                0x20020//下料左侧机械手下
#define  OUNLOADUPRIGHT                 0x20021//下料右侧机械手上
#define  OUNLOADDOWNRIGHT               0x20022//下料右侧机械手下
#define  OUNLOADVACUUMCHLEFT	 		0x20023//下料左侧机械手真空电磁阀
#define  OUNLOADVACUUMCHRIGHT           0x20024//下料右侧机械手真空电磁阀
#define  OUNLOADDOLLYLOCK       	    0x20025//下料小车锁定

//********************输入端口定义*****************************
///DMC-1842-3用I/O扩展板DB14064 DI 定义
//#define  Input   N表示收缩 P表示伸出
#define  ILOADERLTHANDVN				 0x20028//上料左侧手气缸N 
#define  ILOADERRTHANDVN				 0x20029//上料右侧手气缸N
#define  ILOADERLTHANDVP				 0x2002A//上料左侧手气缸P
#define  ILOADERRTHANDVP				 0x2002B//上料右侧手气缸P
#define  ILOADERRSUCKOK1				 0x2002C//上料右侧手是不是吸住前	
#define  ILOADERRSUCKOK2				 0x2002D//上料右侧手是不是吸住后
#define  ILOADERLSUCKOK1				 0x2002E//上料左侧手是不是吸住前
#define  ILOADERLSUCKOK2				 0x2002F//上料左侧手是不是吸住后
#define  ILOADERDOLLYISLOCK              0x20030//上料小车是否锁定 
#define  ILOADERDOLLYARRIVE			     0x20031//上料小车推到位
#define  ILOADERDOLLYISRISEARRIVE        0x2003E//0x20032//上料小车是否上升到位 
#define  ILOADSNAPXN1					 0x20033//定位气缸XN1
#define  ILOADSNAPXN2					 0x20034//定位气缸XN2
#define  ILOADSNAPXP1					 0x20035//定位气缸XP1
#define  ILOADSNAPXP2				     0x20036//定位气缸XP2
#define  ILOADSNAPYN					 0x20037//定位气缸YN2
#define  ILOADSNAPYP					 0x20038//定位气缸YP2
#define  ILOADSHACKEN					 0x20039//抖料气缸N
#define  ILOADSHACKEP					 0x2003A//抖料气缸P
#define	 ILOADEREMPTY					 0x2003B//上料小车缺料
#define	 ILOADERLTHANDVPSEC				 0x2003C//上料左侧P2
#define  ILOADERRTHANDVPSEC				 0x2003D//上料右侧P2
//reserved
//reserved
#define  IUNLOADERLTHANDVN				 0x20040//下料左侧手收缩
#define  IUNLOADERLTHANDVP			     0x20041//下料左侧手伸出
#define  IUNLOADERRSUCKOK1				 0x20042//下料右侧手是不是吸住	
#define  IUNLOADERLSUCKOK2				 0x20043//下料右侧手是不是吸住
//reserved
#define  IUNLOADERDOLLYISRISEARRIVE		 0x20045
#define  IUNLOADERRTHANDVN				 0x20046//下料右侧手气缸N
#define  IUNLOADERRTHANDVP				 0x20047//下料右侧手气缸P
#define  IUNLOADERRSUCKOK2               0x20048//下料左侧手是否吸住检测信号
#define  IUNLOADERLSUCKOK1				 0x20049//下料左侧手是否吸住检测信号
#define  IUNLOADERDOLLYARRIVE			 0x2004A	  //下料小车推到位
#define  IUNLOADERDOLLYISLOCK            0x2004B  //下料小车是否锁定 
#define  IUNLOADERLTHANDVPSEC			 0x2004C   //下料左侧P2
#define  IUNLOADERRTHANDVPSEC            0x2004D  //下料右侧P2

//  ************** 9112 ****输出端口****************//ly:C型机和B型机此板卡端口不做改动

#define  RELOADBOARD          	     0x50000			//加工完一批后，再次往料仓内加板
#define  OSORBOK             	     0x50001			//平台取料完成
#define  OUNLOARDMOVETOTABLE  	     0x50002			//下料准备
#define  OAOTUBIGN        	         0x50003			//开始运行
#define  OLEFTERRO        	         0x50004			//左侧加工失败
#define  ORIGHTERRO        	         0x50005			//右侧加工失败
#define  OLOARDBORD       	         0x50006			//可以上料
#define  OUNLAORDBORD       	     0x50007			//可以下料
#define  OHOMEALL           	     0x50008			//上下料整体回零
#define  OPROCEXIT           	     0x50009			//结束运行
#define  STOPMOVE					 0x5000A			//安全门锁定上下料手臂 低电平锁定 ly add 20110813

#define  OCleartheCum				 0x5000F           //脉冲记数清0

//  ************** 9112 ****输入端口****************

#define  IHOMEALLOK				     0x50000			//上下料整体回零完成
#define  IREADYLOAD				     0x50001			//已经到完料，可以上板到平台
#define  ILOADOK				     0x50002			//上料完成
#define  IONLYLEFT				     0x50003			//最后一张板
#define  IUNLOADOK				     0x50004			//下料完成
#define  IALARM				         0x50005			//异常报警
#define  IDEPOTEMPTY		         0x50006			//上料无料
#define  IPUTBOARDONTABABLE	         0x50007			//放料到平台，可以吸附
#define  IREADYTOUNLOADOK      	     0x50008			//下料手准备完成
#define  IOVERTIMEALARM        	     0x50009			//超时报警
 
#define  IONGFULLALARM				 0x5000B			//NG料仓满的信号  低电平满  ly add 20110813
#define  MANIPULATORGERROR			 0x5000C			//原来的下料超时报警12+16 现在修改为机械手错误报警

#define  MANIPULATORLOADDOOR		 0x5001D			//上料安全门开29+16增加的上下料门报警
#define  MANIPULATORUNLOADDOOR		 0x5001E			//下料安全门开30+16

#ifdef NEWE2
// 	//***********************1842-1 ****输出端口C型机*********************
// 	#define  OSERVOALRAMCLEAR1			 0x00001			//X伺服报警清除
// 	#define  OSERVOALRAMCLEAR2			 0x00002			//Y伺服报警清除
// 	#define  OSERVOALRAMCLEAR6			 0x00003			//R伺服报警清除
// 	#define  OSERVOALRAMCLEAR5			 0x00004			//G伺服报警清除
// 	//***********************1842-2****输出端口C型机*********************
// 	#define  OSERVOALRAMCLEAR3           0x10001			//Z1伺服报警清除?????
// 	#define  OSERVOALRAMCLEAR4			 0x10002			//Z2伺服报警清除?????
	//***********************DMC-4040 ****输入端口E型机*********************

	//***********************MD-B140-1****输出端口E2型机*********************
	#define  OSERVOALRAMCLEAR3           0x00003			//四个轴报警复位清除//Z1伺服报警清除?????
	//***********************MD-B140-2****输出端口E2型机*********************  
	#define  OSERVOALRAMCLEAR6			 0x10003			//四个轴报警复位清除//R伺服报警清除

   //E2不使用，但是D2C定义了的
	#define  OSERVOALRAMCLEAR4			 0x10002			//Z2伺服报警清除?????
	#define  OSERVOALRAMCLEAR1			 0x00001			//X伺服报警清除
	#define  OSERVOALRAMCLEAR2			 0x00002			//Y伺服报警清除
	#define  OSERVOALRAMCLEAR5			 0x00004			//G伺服报警清除

	//  ************** HSL-DO32****输出端口E2型机****************
	#define  LEFTSHUTTERC                0x30000		   //左快门气缸电磁阀//D2C激光预热闸门                //ON_光通过
	#define  RIGHTSHUTTERC               0x30001		   //右快门气缸电磁阀//长短光路切换  (/激光快门1)	 //ON_长光路	
	#define  OTHETALENSPROTECT	         0x30002		   //镜头隔离气
	#define  OLASERPOWERCLEANER          0x30003		   //测功率吹气    (/平台夹钳)
	#define  OTESTTHICKNESSN1	         0x30004		   //测厚气缸1
	#define  OTESTTHICKNESSN2            0x30005		   //测厚气缸2
	#define  OTABLEVACUUMVALVE1          0x30006		   //平台真空吸附1	
	#define  OTABLEVACUUMVALVERE1        0x30007           //平台释放真空1
	#define  OTABLEVACUUMVALVE2          0x30008		   //平台真空吸附2
	#define  OTABLEVACUUMVALVERE2        0x30009		   //平台释放真空2
	#define  OTABLECLAMP				 0x3000A		   //平台夹钳
	#define  OFANPOWERON				 0x3000B		   //风机上电
	#define  OLAMPREDON					 0x3000C			//塔灯红灯
	#define  OLAMPGREENON				 0x3000D			//塔灯绿灯
	#define  OCOMMONALARM				 0x3000E			//蜂鸣器
	//测试AOM替代振镜卡端口高低
	#define  AOMTESTREPLACE              0x3000F//0x3000D//光路AOM调试  光路调试程序使用，大程序是没有使用这个端口
    //#define  OLASERON					 0x3001C			//OEM激光器激光使能上电
    #define  OLASERON2					 0x3001D			//激光器2激光使能上电
    #define  OLASERRESET1			     0x3001E			//激光器复位1 新增
    #define  OLASERRESET2				 0x3001F		    //激光器复位1 新增

    //不使用的
	#define  OLASERWARNUP				 0x30030			//激光预热闸门                //ON_光通过
	#define  OLASERSHUTTER1              0x30031			//长短光路切换  (/激光快门1)	 //ON_长光路
	#define  OLASERSHUTTERON			 0x30037			//激光器快门打开
    #define  OLASERSHUTTER2              0x30032			//TOPHAT光路切换(/激光快门2)
	// ************** HSL-DI16DO16-1 ****输出端口E型机****************
	#define  OCCDLIGHTONCOL				 0x40000			//同轴光源1开关(CH1)
	#define  OCCDLIGHTONCOR				 0x40001			//同轴光源2开关(CH2)
	#define  OCCDLIGHTONL				 0x40002			//环形光源1开关(CH3)
	#define  OCCDLIGHTONR				 0x40003			//环形光源2开关(CH4)
	#define  OLCHANNELSELECT			 0x40004			//CH-select1***原左轴光源切换
	#define  ORCHANNELSELECT			 0x40005			//CH-select2***原右轴光源切换
	#define  OCCDLIGHTSOURCEENABLE		 0x40006			//Write trgl亮度写入信号***原环形光源确认
	#define  OCCDLIGHTTUNELBIT0		     0x40007			//8位光源亮度控制：bit0~bit7
	#define  OCCDLIGHTTUNELBIT1	         0x40008			//
	#define  OCCDLIGHTTUNELBIT2			 0x40009			//
	#define  OCCDLIGHTTUNELBIT3	         0x4000A			//
	#define  OCCDLIGHTTUNELBIT4		     0x4000B			//
	#define  OCCDLIGHTTUNELBIT5	         0x4000C			//
	#define  OCCDLIGHTTUNELBIT6		     0x4000D		    //
	#define  OCCDLIGHTTUNELBIT7		     0x4000E		    //bit7
    #define  OLASERON					 0x4000F			//OEM激光器激光使能上电
    // ************** HSL-DI16DO16-2 ****输出端口E型机****************//以下预留，为4ccd备用
	#define  OCCDLIGHTONCOL1			 0x60000			//同轴光源1开关(CH1)
	#define  OCCDLIGHTONCOR1			 0x60001			//同轴光源2开关(CH2)
	#define  OCCDLIGHTONL1				 0x60002			//环形光源1开关(CH3)
	#define  OCCDLIGHTONR1				 0x60003			//环形光源2开关(CH4)
	#define  OCCDLIGHTTUNEHEADSEL1		 0x60004			//CH-select1***原背光灯通路选择
	#define  OCCDLIGHTCONTROLSEL1		 0x60005			//CH-select2***原环形光源内/外控选择
	#define  OCCD1						 0x60006			//Write trg2亮度写入信号
	#define  OCCDLIGHTTUNERBIT0          0x60007			//光源亮度控制：bit0~bit7
	#define  OCCDLIGHTTUNERBIT1          0x60008			//
	#define  OCCDLIGHTTUNERBIT2          0x60009			//
	#define  OCCDLIGHTTUNERBIT3          0x6000A			//
	#define  OCCDLIGHTTUNERBIT4          0x6000B			//
	#define  OCCDLIGHTTUNERBIT5          0x6000C			//	
	#define  OCCDLIGHTTUNERBIT6          0x6000D			//
	#define  OCCDLIGHTTUNERBIT7          0x6000E			//bit7

	//***********************DMC-4040 ****输入端口E型机*********************
	#define  IMANUXBTN					0x00002		//X
	#define  IMANUYBTN					0x00003		//Y
	#define  IMANUX1BTN					0x00004		//*10
	#define  IMANUX2BTN					0x00005		//*100
	#define  ISERVOALARMX				0x00006		//X轴伺服报警			
	#define  ISERVOALARMY				0x00007		//Y轴伺服报警
	//***********************MD-B140-1****输入端口E型机*********************
	#define  ITHICKNESSHOME1			 0x10000			//测厚光栅尺 Z1测厚
	#define  ITHICKNESSHOME2		 	 0x10001			//测厚光栅尺 Z2测厚
	#define  ISERVOALARMUNBETSUB		 0x10002			//R轴伺服报警
	#define  ISERVOALARMUNBETHOST		 0x10003			//G轴伺服报警
	//没有这两个报警
	#define  ISERVOALARMZLEFT		 	 0x10004			//Z1轴伺服报警			 
	#define  ISERVOALARMZRIGHT			 0x10005			//Z2轴伺服报警
	//***********************MD-B140-2****输入端口E型机*********************
	#define  ADRIVERWARNING		 	     0x20000			//A驱动报警		//新增
	#define  A1DRIVERWARNING		 	 0x20001			//A1驱动报警	//新增
	#define  G1DRIVERWARNING		 	 0x20002			//G1驱动报警	//新增
	#define  R1DRIVERWARNING		 	 0x20003			//R1驱动报警	//新增
	//  ************** HSL-DI32****输入端口E2型机****************
	#define  ILASERWARMUPN				0x30000			//预热闸门气缸N
	#define  ISWATERFAULT				0x30000			//刘源add 韩国C45号机。冷水机预报警，高电平报警  YBJ
	#define  ILASERWARMUPP				0x30001			//预热闸门气缸P
	#define  ILASERSHUTTERLTN			0x30002			//左轴短光路***原光路转换1N
	#define  ILASERSHUTTERLTP			0x30003			//左轴长光路***光路转换1P
	#define  ILASERSHUTTERRTN			0x30004			//右轴短光路***光路转换2N
	#define  ILASERSHUTTERRTP			0x30005			//右轴长光路***光路转换2P
	#define	 ITHICKNESS1N				0x30006			//测厚气缸1N 
	#define  ITHICKNESS1P				0x30007			//测厚气缸1P
	#define	 ITHICKNESS2N				0x30008			//测厚气缸2N
	#define  ITHICKNESS2P				0x30009			//测厚气缸2P
	#define  ISWATERCOOLFAULT			0x3000A			//小冷水机故障报警
	#define  IAOMTEMPROTECT				0x3000B			//AOM温度保护报警
	#define  IDOORPROTECT				0x3000C			//门对射安全保护报警
	#define  ILENSWINDOW1ERROR			0x3000D			//扫描镜保护窗1未到位报警
	#define  ILENSWINDOW2ERROR			0x3000E			//扫描镜保护窗2未到位报警
	#define  ITABLTVACUMM				0x3000F//0x4000D//PCB真空1 左平台真空
	#define  ITABRTVACUMM				0x30010//0x4000E//PCB真空2 右平台真空
	#define  ILASERGASFLUX				0x30011			//激光保护气流量报警
	#define  ITABLECLAMPN				0x30012			//平台夹钳气缸N 
	#define  ITABLECLAMPP				0x30013			//平台夹钳气缸P
	#define  IDUSTOUT1PRESSURE			0x30014			//左路抽尘静压
	#define  IDUSTOUT2PRESSURE			0x30015			//右路抽尘静压
	//#define  IDUSTOUT2PRESSURE			0x30016		    //激光器电源报警 新增
	#define  MOTIONSTOP					0x30017//0x4000A//急停
	#define  MOTIONSTOPRESET			0x30018//0x4000B//急停复位//ly change20110311 和急停信号对调C002反的
	#define	 IAIRPRESSURE              	0x30019//0x4000C//压缩空气气压
	#ifdef CTI
	#define	 ICTIOK					    0x3001A//0x3001E//低电平报警 CTI新报警 jpc add 20131129 
	#endif
	#define    LEFTTHICKNESS1N          0x3001B         //左轴快门气缸+
	#define    LEFTTHICKNESS1P          0x3001C         //左轴快门气缸-
	#define    RIGHTTHICKNESS1N         0x3001D         //右轴快门气缸+
	#define    RIGHTTHICKNESS1P         0x3001E         //右轴快门气缸-
	#define    IDOOROPENPROTECT			0x3001F//0x3000F//安全门限位开关 低电平报警

	//  ************** HSL-DI16DO16-1 ****输入端口E型机****************
	#define  ICOLIGHT1ERROR				0x40000			//同轴光1报警//新增ly
	#define  ICOLIGHT2ERROR				0x40001			//同轴光2报警//新增ly
	#define  IRINGLIGHT1ERROR			0x40002			//环形光1报警
	#define  IRINGLIGHT2ERROR			0x40003			//环形光2报警
	#define  DRILLMATRIXSWITCH			0x40005			//调光路用激光点动开关1
	#define  ITEMPERATUREFAULT			0x40006			//VSWR//激光器温度报警
	#define  IWATERFLOWPROTECT			0x40007			//System Warning 1//激光器水流报警
	#define	 ILASERONOK					0x40008			//System Fault1 //激光器上电OK
	#define  DRILLMATRIXSWITCH2			0x4000C			//调光路用激光点动开关2
	#define  ITEMPERATUREFAULT2			0x4000D			//VSWR//激光器温度报警2
	#define  IWATERFLOWPROTECT2			0x4000E			//System Warning 1//激光器水流报警2
	#define	 LASEROK2				    0x4000F			//System Fault1 //激光器2上电OK	
	//  ************** HSL-DI16DO16-2 ****输入端口E型机****************
	#define  ICOLIGHT1ERROR2			0x60000			//同轴光1报警//新增ly//4CCD备用
	#define  ICOLIGHT2ERROR2			0x60001			//同轴光2报警//新增ly//4CCD备用
	#define  IRINGLIGHT1ERROR2			0x60002			//环形光1报警//4CCD备用
	#define  IRINGLIGHT2ERROR2			0x60003			//环形光2报警//4CCD备用

	#define  ITOPHAT1N					0x30006			//平顶光束1***TopHat切换气缸1N 
	#define  ITOPHAT2N					0x30007			//高斯光束1***TopHat切换气缸2N
	#define  ITOPHAT1P					0x30008			//平顶光束2***TopHat切换气缸1P
	#define  ITOPHAT2P					0x30009			//高斯光束2***TopHat切换气缸2P
	#define  ITABXERROR				    0x40000			//X轴光栅尺错误
	#define  ITABYERROR					0x40001			//Y轴光栅尺错误 
	#define  IMANURUNBTN				0x40013			//手轮信号输入：06~0C
	#define  IMANUSTOPBTN				0x40014			//
	#define  IMANUX3BTN					0x40019			//
	#define  I1842_1ERROR				0x4001A			//运动卡1错误
	#define  I1842_2ERROR				0x4001B			//运动卡2错误

#else	//NEWE2

#ifdef IO_C//ly add 20110115

#ifdef USEDMSYSTEM										//20190507
//兼容保留
#define  OSERVOALRAMCLEAR1			 0x0000A			//X伺服报警清除
#define  OSERVOALRAMCLEAR2			 0x0000B			//Y伺服报警清除
//***********************18XX-1输出端口*********************
#define  OSERVOALRAMCLEAR3           0x00000			//Z1伺服报警清除?????
#define  OSERVOALRAMCLEAR6			 0x00001			//R1伺服报警清除
#define  OSERVOALRAMCLEAR5			 0x00002			//G1伺服报警清除
//***********************18XX-2输出端口*********************
#define  OSERVOALRAMCLEAR4			 0x10000			//Z2伺服报警清除?????
#define  OSERVOALRAMCLEAR7           0x10001			//G2伺服报警清除
#define  OSERVOALRAMCLEAR8			 0x10002			//R2伺服报警清除
#else
//***********************18XX-1输出端口*********************
#define  OSERVOALRAMCLEAR1			 0x00001			//X伺服报警清除
#define  OSERVOALRAMCLEAR2			 0x00002			//Y伺服报警清除
#define  OSERVOALRAMCLEAR6			 0x00003			//R伺服报警清除
#define  OSERVOALRAMCLEAR5			 0x00004			//G伺服报警清除
//***********************18XX-2输出端口*********************
#define  OSERVOALRAMCLEAR3           0x10001			//Z1伺服报警清除?????
#define  OSERVOALRAMCLEAR4			 0x10002			//Z2伺服报警清除?????
//***********************18XX-3输出端口*********************
#define  OSERVOALRAMCLEAR7           0x20001			//G1伺服报警清除
#define  OSERVOALRAMCLEAR8			 0x20002			//R1伺服报警清除
#endif

//  *********************7200-1输出端口*********************
#define  OLASERWARNUP                0x30000		   //激光预热闸门                //ON_光通过
#define  OLASERSHUTTER1              0x30001		   //长短光路切换  (/激光快门1)	 //ON_长光路
#define  OLASERSHUTTER2              0x30002		   //TOPHAT光路切换(/激光快门2)
#define  OTHETALENSPROTECT	         0x30003		   //镜头隔离气
#define  OLASERPOWERCLEANER          0x30004		   //测功率吹气    (/平台夹钳)
#define  OTESTTHICKNESSN1	         0x30005		   //测厚气缸1
#define  OTESTTHICKNESSN2            0x30006		   //测厚气缸2
#define  OTABLEVACUUMVALVE1          0x30007		   //平台真空吸附1	
#define  OTABLEVACUUMVALVERE1        0x30008           //平台释放真空1
#define  OTABLEVACUUMVALVE2          0x30009		   //平台真空吸附2
#define  OTABLEVACUUMVALVERE2        0x3000A		   //平台释放真空2
#define  OTABLECLAMP				 0x3000B		   //平台夹钳
#define  OFANPOWERON				 0x3000C		   //风机上电

#define  OLAMPREDON					 0x30013			//塔灯红灯
#define  OLAMPGREENON				 0x30014			//塔灯绿灯
#define  OCOMMONALARM				 0x30015			//蜂鸣器

#define  OLASERSHUTTERON			 0x30017			//激光器快门打开
#define  OLASERON					 0x30018			//激光器激光使能上电
#define  OLASERON2					 0x30019			//激光器2激光使能上电

//  ***********************7200-2输出端口*************************
#define  OCCDLIGHTONCOL				 0x40000			//同轴光源1开关(CH1)
#define  OCCDLIGHTONCOR				 0x40001			//同轴光源2开关(CH2)
#define  OCCDLIGHTONL				 0x40002			//环形光源1开关(CH3)
#define  OCCDLIGHTONR				 0x40003			//环形光源2开关(CH4)
#define  OLCHANNELSELECT			 0x40004			//CH-select1***原左轴光源切换
#define  ORCHANNELSELECT			 0x40005			//CH-select2***原右轴光源切换
#define  OCCDLIGHTSOURCEENABLE		 0x40006			//Write trgl亮度写入信号***原环形光源确认
#define  OCCDLIGHTTUNELBIT0		     0x40007			//8位光源亮度控制：bit0~bit7
#define  OCCDLIGHTTUNELBIT1	         0x40008			//
#define  OCCDLIGHTTUNELBIT2			 0x40009			//
#define  OCCDLIGHTTUNELBIT3	         0x4000A			//
#define  OCCDLIGHTTUNELBIT4		     0x4000B			//
#define  OCCDLIGHTTUNELBIT5	         0x4000C			//
#define  OCCDLIGHTTUNELBIT6		     0x4000D		    //
#define  OCCDLIGHTTUNELBIT7		     0x4000E		    //bit7

#define  OCCDLIGHTONCOL1			 0x40010			//同轴光源1开关(CH1)
#define  OCCDLIGHTONCOR1			 0x40011			//同轴光源2开关(CH2)
#define  OCCDLIGHTONL1				 0x40012			//环形光源1开关(CH3)
#define  OCCDLIGHTONR1				 0x40013			//环形光源2开关(CH4)
#define  OCCDLIGHTTUNEHEADSEL1		 0x40014			//CH-select1***原背光灯通路选择
#define  OCCDLIGHTCONTROLSEL1		 0x40015			//CH-select2***原环形光源内/外控选择
#define  OCCD1						 0x40016			//Write trg2亮度写入信号
#define  OCCDLIGHTTUNERBIT0          0x40017			//光源亮度控制：bit0~bit7
#define  OCCDLIGHTTUNERBIT1          0x40018			//
#define  OCCDLIGHTTUNERBIT2          0x40019			//
#define  OCCDLIGHTTUNERBIT3          0x4001A			//
#define  OCCDLIGHTTUNERBIT4          0x4001B			//
#define  OCCDLIGHTTUNERBIT5          0x4001C			//	
#define  OCCDLIGHTTUNERBIT6          0x4001D			//
#define  OCCDLIGHTTUNERBIT7          0x4001E			//bit7

#ifdef USEDMSYSTEM										//20190507
//兼容保留
#define  ISERVOALARMX				 0x0000A			//X轴伺服报警
#define  ISERVOALARMY				 0x0000B			//Y轴伺服报警
//***********************18XX-1输入端口*********************
#define  ITHICKNESSHOME1			 0x00000			//测厚光栅尺
#define  ISERVOALARMZLEFT		 	 0x00001			//Z1轴伺服报警
#define  ISERVOALARMUNBETHOST		 0x00004			//R1轴伺服报警
#define  ISERVOALARMUNBETSUB		 0x00005			//G1轴伺服报警
#define  ISERVOALARMAPT				 0x00007			//A1轴伺服报警
//***********************18XX-2输入端口*********************
#define  ITHICKNESSHOME2		 	 0x10000			//测厚光栅尺
#define  ISERVOALARMZRIGHT			 0x10001			//Z2轴伺服报警
#define  ISERVOALARMUNBETSUB1		 0x10004			//G2轴伺服报警
#define  ISERVOALARMUNBETHOST1		 0x10005			//R2轴伺服报警
#define  ISERVOALARMAPT1			 0x10007			//A2轴伺服报警
#else
//***********************18XX-1输入端口*********************
#define  ISERVOALARMX				 0x00004			//X轴伺服报警
#define  ISERVOALARMY				 0x00005			//Y轴伺服报警
#define  ISERVOALARMUNBETSUB		 0x00006			//G轴伺服报警
#define  ISERVOALARMUNBETHOST		 0x00007			//R轴伺服报警
//***********************18XX-2输入端口*********************
#define  ITHICKNESSHOME1			 0x10000			//测厚光栅尺
#define  ITHICKNESSHOME2		 	 0x10001			//测厚光栅尺
#define  ISERVOALARMZLEFT		 	 0x10004			//Z1轴伺服报警
#define  ISERVOALARMZRIGHT			 0x10005			//Z2轴伺服报警
#define  ISERVOALARMAPT				 0x10007			//A轴伺服报警
//***********************18XX-3输入端口*********************
#define  ISERVOALARMUNBETSUB1		 0x20004			//G1轴伺服报警
#define  ISERVOALARMUNBETHOST1		 0x20005			//R1轴伺服报警
#define  ISERVOALARMAPT1			 0x20007			//A1轴伺服报警
#endif

//  *********************7200-1输入端口***********************
#define  ILASERWARMUPN				0x30000			//预热闸门气缸N
#define  ISWATERFAULT				0x30000			//刘源add 韩国C45号机。冷水机预报警，高电平报警  YBJ
#define  ILASERWARMUPP				0x30001			//预热闸门气缸P //更新为华为激光电源的异常报警输入
#define  ILASERSHUTTERLTN			0x30002			//左轴短光路***原光路转换1N
#define  ILASERSHUTTERLTP			0x30003			//左轴长光路***光路转换1P
#define  ILASERSHUTTERRTN			0x30004			//右轴短光路***光路转换2N
#define  ILASERSHUTTERRTP			0x30005			//右轴长光路***光路转换2P
#define  ITOPHAT1N					0x30006			//未使用
#define  ITOPHAT2N					0x30007			//未使用
#define  ITOPHAT1P					0x30008			//未使用
#define  ITOPHAT2P					0x30009			//未使用
#define  ISWATERCOOLFAULT			0x3000A			//小冷水机故障报警
#define  IAOMTEMPROTECT				0x3000B			//AOM温度保护报警
#define  IDOORPROTECT				0x3000C			//门对射安全保护报警
#define  ILENSWINDOW1ERROR			0x3000D			//扫描镜保护窗1未到位报警
#define  ILENSWINDOW2ERROR			0x3000E			//扫描镜保护窗2未到位报警
#define  IDOOROPENPROTECT			0x3000F			//ly add 20140418 低电平报警

#define  ILASERGASFLUX				0x30011			//激光保护气流量报警
#define  ITABLECLAMPN				0x30012			//平台夹钳气缸N 
#define  ITABLECLAMPP				0x30013			//平台夹钳气缸P
#define  IDUSTOUT1PRESSURE			0x30014			//左路抽尘静压
#define  IDUSTOUT2PRESSURE			0x30015			//右路抽尘静压
#define  DRILLMATRIXSWITCH			0x30016			//调光路用激光点动开关
#define  ITEMPERATUREFAULT			0x30017			//激光器温度报警
#define  IWATERFLOWPROTECT			0x30018			//激光器水流报警
#define	 ILASERONOK					0x30019			//激光器上电OK

#ifdef CTI
#define	 ICTIOK						0x3001E			//低电平报警 CTI新报警 jpc add 20131129 
#endif

//  **********************7200-2输入端口**************************
#define  ITABXERROR				    0x40000			//X轴光栅尺错误
#define  ITABYERROR					0x40001			//Y轴光栅尺错误 
#define  ICOLIGHT1ERROR				0x40002			//同轴光1报警//新增ly
#define  ICOLIGHT2ERROR				0x40003			//同轴光2报警//新增ly
#define  IRINGLIGHT1ERROR			0x40004			//环形光1报警
#define  IRINGLIGHT2ERROR			0x40005			//环形光2报警
#define  ICOLIGHT1ERROR2			0x40006			//同轴光1报警//新增ly//4CCD备用
#define  ICOLIGHT2ERROR2			0x40007			//同轴光2报警//新增ly//4CCD备用
#define  IRINGLIGHT1ERROR2			0x40008			//环形光1报警//4CCD备用
#define  IRINGLIGHT2ERROR2			0x40009			//环形光2报警//4CCD备用
#define  MOTIONSTOP					0x4000A			//急停
#define  MOTIONSTOPRESET			0x4000B			//急停复位//ly change20110311 和急停信号对调C002反的

#ifdef SENTINAL
#define	 IAIRPRESSURE              	0x30010			//压缩空气气压
#else
#define	 IAIRPRESSURE              	0x4000C			//压缩空气气压
#endif

#define  ITABLTVACUMM				0x4000D			//PCB真空1
#define  ITABRTVACUMM				0x4000E			//PCB真空2
#define	 ITHICKNESS1N				0x4000F			//测厚气缸1N 
#define  ITHICKNESS1P				0x40010			//测厚气缸1P
#define	 ITHICKNESS2N				0x40011			//测厚气缸2N
#define  ITHICKNESS2P				0x40012			//测厚气缸2P
#define  IMANURUNBTN				0x40013			//手轮信号输入：06~0C
#define  IMANUSTOPBTN				0x40014			//
#define  IMANUXBTN					0x40015			//
#define  IMANUYBTN					0x40016			//
#define  IMANUX1BTN					0x40017			//
#define  IMANUX2BTN					0x40018			//
#define  IMANUX3BTN					0x40019			//
#define  I1842_1ERROR				0x4001A			//运动卡1错误
#define  I1842_2ERROR				0x4001B			//运动卡2错误

#define  LASEROK2 			    	0x4001E			//激光器2上电OK			 

#else  //IO_C

//  ************** 7200-1********************
#define  OLASERWARNUP                0x30000		   //激光预热闸门                //ON_光通过
#define  OLASERSHUTTER1              0x30001		   //长短光路切换  (/激光快门1)	 //ON_长光路
#define  OLASERSHUTTER2              0x30002		   //TOPHAT光路切换(/激光快门2)
#define  OTESTTHICKNESSN1	         0x30003		   //测厚气缸1
#define  OTESTTHICKNESSP1            0x30004		   //
#define  OTHETALENSPROTECT	         0x30005		   //镜头隔离气
#define  OLASERPOWERCLEANER          0x30006		   //测功率吹气    (/平台夹钳)
#define  OLASERPROTECTGAS            0x30007		   //激光气体保护
#define  OTABLEVACUUMVALVE1          0x30008		   //平台真空吸附1	
#define  OTABLEVACUUMVALVERE1        0x30009           //平台释放真空1
#define  OTABLEVACUUMVALVE2          0x3000A		   //平台真空吸附2
#define  OTABLEVACUUMVALVERE2        0x3000B		   //平台释放真空2
#define  OTESTTHICKNESSN2            0x3000C		   //测厚气缸2
#define  OTESTTHICKNESSP2            0x3000D		   //
#define  OFANPOWERON				 0x3000E		   //风机上电

#define  OTABLECLAMP				 0x30012		   //平台夹钳

#ifdef PPLASER
#define  OLASERSHUTTERCMD			 0x30018			//PP型激光器上电用：18~1E	
#define  OLASERA					 0x30019            // 
#define  OLASERB					 0x3001A            // 
#define  OLASERAIM					 0x3001B            //
#define  OLASERCLRFLT				 0x3001C			//
#define  OLASERRFENC				 0x3001D			//
#define  OLASERPWM					 0x3001E			//
#else
#define  OLCHANNELSELECT			 0x30018			//左轴光源切换
#define  ORCHANNELSELECT			 0x30019			//右轴光源切换

#define  OLASERON					 0x3001E			//激光器激光使能上电
#define  OLASERSHUTTERON			 0x3001F			//激光器快门打开
#endif

//  ************** 7200-2********************
#define  OLAMPREDON					 0x40000			//塔灯红灯
#define  OLAMPGREENON				 0x40001			//塔灯绿灯
#define  OCOMMONALARM				 0x40002			//蜂鸣器
#define  OSERVOALRAMCLEAR1			 0x40003			//X伺服报警清除
#define  OSERVOALRAMCLEAR2			 0x40004			//Y伺服报警清除
#define  OSERVOALRAMCLEAR3           0x40005			//Z1伺服报警清除
#define  OSERVOALRAMCLEAR4			 0x40006			//Z2伺服报警清除
#define  OSERVOALRAMCLEAR5			 0x40007			//G伺服报警清除
#define  OSERVOALRAMCLEAR6			 0x40008			//R伺服报警清除

#ifdef CCSRING
#define  OCCDLIGHTTUNEHEADSEL        0x40010			//背光灯通路选择
#define  OCCDLIGHTSOURCELEFT         0x40011			//环形光源1开关
#define  OCCDLIGHTSOURCERIGHT        0x40012			//环形光源2开关
#define  OCCDLIGHTCONTROLSEL         0x40013			//环形光源内/外控选择
#define  OCCDLIGHTSOURCEENABLE       0x40014		    //环形光源确认写入

#define  OCCDLIGHTTUNEBITLCEN        0x40016			//同轴光源1开关
#define  OCCDLIGHTTUNEBITRCEN        0x40017			//同轴光源2开关
#define  OCCDLIGHTTUNEBIT11          0x40018			//环形光源亮度控制：bit0~bit8
#define  OCCDLIGHTTUNEBIT12          0x40019			//
#define  OCCDLIGHTTUNEBIT13          0x4001A			//
#define  OCCDLIGHTTUNEBIT14          0x4001B			//
#define  OCCDLIGHTTUNEBIT15          0x4001C			//
#define  OCCDLIGHTTUNEBIT16          0x4001D			//	
#define  OCCDLIGHTTUNEBIT17          0x4001E			//
#define  OCCDLIGHTTUNEBIT18          0x4001F			//bit8
#else
#define  OCCDLIGHTONCOL				 0x4000C			//同轴光源1开关
#define  OCCDLIGHTONCOR				 0x4000D			//同轴光源2开关
#define  OCCDLIGHTTUNELBIT0		     0x4000E			//左侧环形光源亮度控制：bit0~bit7
#define  OCCDLIGHTTUNELBIT1	         0x4000F			//
#define  OCCDLIGHTTUNELBIT2			 0x40010			//
#define  OCCDLIGHTTUNELBIT3	         0x40011			//
#define  OCCDLIGHTTUNELBIT4		     0x40012			//
#define  OCCDLIGHTTUNELBIT5	         0x40013			//
#define  OCCDLIGHTTUNELBIT6		     0x40014		    //
#define  OCCDLIGHTTUNELBIT7		     0x40015		    //bit7
#define  OCCDLIGHTONL				 0x40016			//环形光源1开关
#define  OCCDLIGHTONR				 0x40017			//环形光源2开关
#define  OCCDLIGHTTUNERBIT0          0x40018			//右侧环形光源亮度控制：bit0~bit7
#define  OCCDLIGHTTUNERBIT1          0x40019			//
#define  OCCDLIGHTTUNERBIT2          0x4001A			//
#define  OCCDLIGHTTUNERBIT3          0x4001B			//
#define  OCCDLIGHTTUNERBIT4          0x4001C			//
#define  OCCDLIGHTTUNERBIT5          0x4001D			//	
#define  OCCDLIGHTTUNERBIT6          0x4001E			//
#define  OCCDLIGHTTUNERBIT7          0x4001F			//bit7
#endif

/*--------------------输入口定义------------------------*/
//  ************** 7200-1********************
#define  MOTIONSTOPRESET			0x30000			//急停复位
#define  MOTIONSTOP		            0x30001			//急停
#define	 IAIRPRESSURE              	0x30002			//压缩空气气压
#define  ITABLTVACUMM				0x30003			//PCB真空1
#define  ITABRTVACUMM				0x30004			//PCB真空2
#define  DRILLMATRIXSWITCH			0x30005			//调光路用激光点动开关
#define  IMANURUNBTN				0x30006			//手轮信号输入：06~0C
#define  IMANUSTOPBTN				0x30007			//
#define  IMANUXBTN					0x30008			//
#define  IMANUYBTN					0x30009			//
#define  IMANUX1BTN					0x3000A			//
#define  IMANUX2BTN					0x3000B			//
#define  IMANUX3BTN					0x3000C			//
#define  ILASERWARMUPN				0x3000D			//预热闸门气缸N
#define  ILASERWARMUPP				0x3000E			//预热闸门气缸P
#define  ILASERSHUTTERLTN			0x3000F			//光路转换1N
#define  ILASERSHUTTERLTP			0x30010			//光路转换1P
#define  ILASERSHUTTERRTN			0x30011			//光路转换2N
#define  ILASERSHUTTERRTP			0x30012			//光路转换2P
#define	 ITHICKNESS1N				0x30013			//测厚气缸1N 
#define  ITHICKNESS1P				0x30014			//测厚气缸1P
#define	 ITHICKNESS2N				0x30015			//测厚气缸2N
#define  ITHICKNESS2P				0x30016			//测厚气缸2P

#ifdef PPLASER
#define  ILASEROUT3					0x30019			//PP型激光器上电用：19~1E
#define  ILASEROUT2					0x3001A			// 
#define  ILASERSHUTTER_SENSOR		0x3001B		    //
#define	 ILASEROUT1					0x3001C			//
#define  ILASERALERT				0x3001D			//
#define  ILASEROUT0					0x3001E			//
#else
#define  ITEMPERATUREFAULT			0x3001C			//激光器温度报警
#define  IWATERFLOWPROTECT			0x3001D			//激光器水流报警
#define	 ILASERONOK					0x3001E			//激光器上电OK
#endif

//  ************** 7200-2********************
#define  I1842_1ERROR				0x40000			//运动卡1错误
#define  I1842_2ERROR				0x40001			//运动卡2错误			 
#define  ISERVOALARMX				0x40002			//X轴伺服报警			
#define  ISERVOALARMY				0x40003			//Y轴伺服报警			
#define  ISERVOALARMZLEFT			0x40004			//Z1轴伺服报警			 
#define  ISERVOALARMZRIGHT			0x40005			//Z2轴伺服报警			
#define  ISERVOALARMUNBETHOST		0x40006			//G轴伺服报警			
#define  ISERVOALARMUNBETSUB		0x40007			//R轴伺服报警
#define  ILASERGASFLUX				0x40008			//激光保护气流量报警
#define  ISWATERCOOLFAULT			0x40009			//小冷水机故障报警
#define  IAOMTEMPROTECT				0x4000A			//AOM温度保护报警
#define  IDOORPROTECT				0x4000B			//门对射安全保护报警
#define  ITABXERROR				    0x4000C			//X轴光栅尺错误
#define  ITABYERROR					0x4000D			//Y轴光栅尺错误 

#define  ITOPHAT1N					0x40010			//TopHat切换气缸1N 
#define  ITOPHAT1P					0x40011			//TopHat切换气缸1P
#define  ITOPHAT2N					0x40012			//TopHat切换气缸2N
#define  ITOPHAT2P					0x40013			//TopHat切换气缸2P
#define  ITHICKNESSERROR1			0x40014			//测厚光栅尺1错误
#define  ITHICKNESSERROR2			0x40015			//测厚光栅尺2错误
#define  IRINGLIGHT1ERROR			0x40016			//环形光1报警
#define  IRINGLIGHT2ERROR			0x40017			//环形光2报警

#define  ILENSWINDOW1ERROR			0x4000E			//扫描镜保护窗1未到位报警
#define  ILENSWINDOW2ERROR			0x4000F			//扫描镜保护窗2未到位报警
#define  ITABLECLAMPN				0x40018			//平台夹钳气缸N 
#define  ITABLECLAMPP				0x40019			//平台夹钳气缸P
#define  IDUSTOUT1PRESSURE			0x4001A			//左路抽尘静压
#define  IDUSTOUT2PRESSURE			0x4001B			//左路抽尘静压

#endif	//IO_C

#endif	//NEWE2
/*--------------------------------------------------------------------*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5D77F19A_9685_11D2_899F_0040055A6A93__INCLUDED_)
