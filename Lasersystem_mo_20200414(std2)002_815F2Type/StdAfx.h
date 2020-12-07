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

//----------------------------���뿪��------------------------
//���������ƹ���
//#define OEM											//20191219 ȡ��

//���ļ����빦��
//#define ONLYFILE										//20190806 ����

#ifdef ONLYFILE
#define NEWE2
#else
//------------------------------------------------------
//ʱ����Ƽ��ܹ����뿪��
//#define SENTINAL
//#define DOUBLEPROTECT									//20190517 ����

//Ӳ�����ܱ��뿪��
//#define HARDWARE

//ϵͳ��¼���ܱ��뿪��
//#define LOGIN

//���ͱ��뿪��
#define NEWE2
//#define AOMTYPE
//#define F2TYPE
//#define L2TYPE001
//#define L2TYPE
//#define F2TYPE815										//20200818 ����

//-----------------------------------------------------
#endif

//��������ϵͳʱ�İ汾
//#define NOLANDULSYSTEM				//20191203 ����	//20191219 ȡ��
//��������ָ��
//#define UNLOADISOK					//20190627		//20191219 ȡ��
//����ʱƽ̨����ͷŷ�ʽ
//#define TABLEADSORBFIRST								//20191219 ȡ��
//#define HANDADSORBFIRST				//20181203		//20191219 ȡ��
//���Ҷ��Ʊ��뿪��
//#define CHONGDA		//20170314 ��� 20180613׷��	//20191219 ȡ��
//#define ZHIHAO		//20171128 ־��					//20191219 ȡ��
#define DINGYING										//20200707 ��ӱ����

//�����ӹ�ʱ����λ��������
//#define SETPROCOFFSET									//20181203 L2-001

//����2Dƽ̨У��
//#define TABLE2DCALI									//20180417
#define DIVIDINGLINE -13500		//-23500

//����CPK���Ȳ���
//#define CPKTEST										//20180515

//�����񾵾��Ȳ���ʱ�ľ������ݼ�¼
#define GALVOTEST										//20171129 ����

//���ڱ���ʶ��ʧ�ܵı�е�ͼ���ļ�
//#define BMPFILETEST

//���ڱ任�㷨�ĶԱȲ���
//#define TRANSFORMTEST									//20190403 ����	//20190731	//20191106 ȡ��

//������������ʱ���ֶ��ӹ���������
//#define MACHINEHOTTEST								//20190823

//SMCԤ���ع��ܲ��ԣ�������������ʱ���ֶ��ӹ��������ԣ�
//#define PRELOADTEST									//20180827 ����

//�׷���ʱ�����ޣ���������ʱ�ſ����ԣ�
//#define D2CTYPE										//20200330 ����

//����·���Ż�����
//#define MATRIXPATHTEST								//20200330 ����

//�ڴ�ʹ��������
#define MEMORYSTATUSMONITOR								//20200331 ����

//����任(���񾵱任)ģʽ��ز���						//20200402 ����
//#define ONEAXISDATATRANSFORMTEST						//OAM ����ģʽ
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
#define USECOM											//ʹ�ô���
#endif

#ifdef NEWE2
#define DOUBLEBET										//˫BETϵͳ
#define IOMODE					1
#define LASERMAXWIDTH			25						//���ڵ�J5VV�������趨 
#define APERTURE18

#define ADLINKIO

#define AVT
//#define PICOLO

#define NEWAVT											//20191015 ���ڰ�����������Ĳ���

//#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
#define RTC5DLL

#define USERCOGNEX
#endif

#ifdef AOMTYPE
#define HUAWEILASERSOURCE								//���û�Ϊ��Դʱ���ӵĵ�Դ�쳣����
//#define LASERMONITOR									//������״̬������
#define NOONEKEY										//��һ�������Ϲ���		//20190927

#define IOMODE					0
#define LASERMAXWIDTH			15						//����AOM��ʽ�������趨
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
#define DOUBLEBET										//˫BETϵͳ
#define DOUBLELASER										//˫������ϵͳ
#define APTMOTORISSERVO									//�ŷ���Ȧϵͳ//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//���ڵ�/˫J5VV�������趨 
#define APERTURE18

//#define HIKAGV											//20191107 ����

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

#ifdef L2TYPE001										//20200227 �����޸�
//#define GREENOILBOARD									//20190402
#define DOUBLEBET										//˫BETϵͳ
#define DOUBLELASER										//˫������ϵͳ
#define APTMOTORISSERVO									//�ŷ���Ȧϵͳ//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//���ڵ�/˫J5VV�������趨 
#define APERTURE18
#define APERTURE15

//#define ACSMOTION										//20200414	ȡ��
//#define GALILMOTION									//20200414  ȡ��

#define USEDMSYSTEM										//ʹ��˫�˶�ϵͳ(double motion system)

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
#define DOUBLEBET										//˫BETϵͳ
#define DOUBLELASER										//˫������ϵͳ
#define APTMOTORISSERVO									//�ŷ���Ȧϵͳ//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//���ڵ�/˫J5VV�������趨 
#define APERTURE18

#define USEDMSYSTEM										//ʹ��˫�˶�ϵͳ(double motion system)	//20190305

#ifdef USEDMSYSTEM										//20190305
//#define AEROTECHDMSYSTEM								//Aerotech double motion system	
#define ACSDMSYSTEM									//ACS double motion system
#endif

#define ADLINKIO

#define AVT
//#define PICOLO

#define NEWAVT											//20190517 ����

//#define SMCDLL
//#define RTC3DLL
//#define RTC4DLL
#define RTC5DLL
//#define SMCDMDLL										//20200731 ����

#define USERCOGNEX
#endif

#ifdef F2TYPE815
#define DOUBLEBET										//˫BETϵͳ
#define DOUBLELASER										//˫������ϵͳ
#define APTMOTORISSERVO									//�ŷ���Ȧϵͳ//20160823

#define IOMODE					0
#define LASERMAXWIDTH			25						//���ڵ�/˫J5VV�������趨 
#define APERTURE18

//#define HIKAGV											//20191107 ����

#define USEDMSYSTEM

#ifdef USEDMSYSTEM										//20190305
#define AEROTECHDMSYSTEM								//Aerotech double motion system	 �޸ĵ�: 20200818  20200819
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
//SMC��ϵͳ����ʱ�ķ����ӹ�ʱ���쳣�ж�
//#define SMCTEST							//20191219 ȡ��
//#define SMCPreLoad						//20171122 ����	//NPL(NoPreLoad)
//#define SMCNewCorType						//20180423 ����
//#define SMCCaliDLL						//20190716 ����	//Ca(Cali)
#define SMCAdjust							//20190902 ����	//Ad(Adjust)
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

//��Ȧλ�����뿪��
//#define APERTURE12

#ifdef APERTURE18
#ifndef APERTURE15
	#define APTCIRCLEPLS            2777.7778	//50000/18  //18��Ȧ
#else
	#define APTCIRCLEPLS            3333.3333	//50000/15  //15��Ȧ
#endif
#else
#ifndef APERTURE12
	#define APTCIRCLEPLS            6250		//50000/8   //8��Ȧ
#else
	#define APTCIRCLEPLS            4166.6667	//50000/12  //12��Ȧ
#endif
#endif

//��񱨾����ܱ��뿪��
#define USEAUTOTHICKERROR

//��־���ܱ��뿪��
#define USELOG

//ʹ��PP�ͼ�����ʱ�ı��뿪��
//#define PPLASER

//ʹ��CCS���ι�Դʱ�ı��뿪��
//#define CCSRING

//����C�ͻ�Ӳ���ӿڷ���//ly add 20110115
//����Ԥ�ȷ��ţ�C�ͻ�ȡ������Ԥ�ȹ��ܣ�ֻ�л���Ԥ��
#define IO_C

//���޳��̹�·�л�,Ŀǰֻ��C#1�Ż�Ҫ����Ϊ0
#define LSPATH_CHECKING  0		//���г���·���޶̹�·
//#define LSPATH_CHECKING  1	//�г���������·���ɽ����л�

//�ߵ�ƽ��ʾ�����ϵ�OK,�¹��ն��Ǹߵ�ƽ
#define IO_LASERONOK_HIGH 

//�ߵ�ƽ��ʾ�ű����Ʊ���,ĿǰC#1�Ǹߵ�ƽ����
//#define DoorPrt_HighLevel

//���������ð汾���뿪��
//#define LESSWARN

//������,MoveTo(...)������λ����
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
//#define MINLASERPERIOD		200						//20191216	//20191219 ȡ��
#define DMCNOERROR              0						//����ACS��Ĵ��ڲ����ӵ� 20180523
#define MaxPathLen              256
#define PI						3.1415926
#define MAXTESTPOS				450000
#define OUTSIZETHRED			0.1						//Cognex������ֵ����
#define	CCDLENSMAG				1						//CCD����ͷ�Ŵ���
#define TABLECOMPRANGE          1000
#define TABLERESETPOS			-465000
#define SCANSIZEMIN             30
#define LOADANDUNLOADDELAY		50
#define	PATTERNDOTNUM			11						//11 ����У��ʱ�ļӹ�����		//20200417 test

#define TABADJRTLX				780000					//��׼̨��������̨�����֮��Ĳ���
#define TABADJRTLY				-402000

//#define THICKNESSSCALE		2
//#define TABXYSCALE			2

#ifdef AVT
#ifdef NEWAVT
#define IMAGEPIXELX             4.65/0.996/CCDLENSMAG		//20190513 �޸� 1.04->0.996	 	 
#define IMAGEPIXELY             4.65/0.996/CCDLENSMAG
#else
#define IMAGEPIXELX             8.3/0.996/CCDLENSMAG		//CCD:780*580 8.3	//20190510	����	//20190513 �޸� 1.04->0.996	 	 
#define IMAGEPIXELY             8.3/0.996/CCDLENSMAG		//CCD:780*580 8.3
#endif
#else
#define IMAGEPIXELX             8.6/1.04/CCDLENSMAG		//8.6/CCDLENSMAG	//CCD cs8620ci cell size:��8.6*8.3 um				 	 
#define IMAGEPIXELY             8.6/1.04/CCDLENSMAG		//8.3/CCDLENSMAG	//20190418  �޸�             
#endif 

#define IO_ON					1
#define IO_OFF					0

#define MIO_ON					1
#define MIO_OFF				    0

#define HeadLeft				0
#define HeadRight				1
#define HeadBoth                2

#define LEFTCHAN				0		//��ͨ��
#define RIGHTCHAN				1		//��ͨ��
#define COAXIAL					0		//ͬ��
#define	RINGED					1		//����

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
#define POWERDIR                "info\\power.txt"					//20180404 ȡ���˴��ļ�¼
#define LOGFILEDIR              "log\\"
#define LPATHADJDIR             "LPathC\\"
#define SPATHADJDIR             "SPathC\\"
#define SCALEDIR                "info\\scale.txt"					//20180404 ȡ���˴��ļ�¼

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
//�����Ա���
#define AXISLOADX				0x20004     //��������
#define AXISLOADY				0x20005		//����ƽ��
#define AXISUNLOADX				0x20002		//���ϲ��������
#define AXISUNLOADY				0x20006		//����ƽ�Ƶ��

#ifdef NEWE2
//card1
#define AXISTABX				0x00000
#define AXISTABY				0x00001
//card2
#define AXISLEFTZ				0x10000
#define AXISRIGHTZ				0x10001
#define AXISBETSUB				0x10002		//�Ӷ���1
#define AXISBETPRI				0x10003		//������1
//card3
#define AXISAPT					0x20000		//��Ȧ1
#define AXISAPT2				0x20001		//��Ȧ2
#define AXISBETSUB2				0x20002     //�Ӷ���2
#define AXISBETPRI2				0x20003		//������2	

#else	//NEWE2

#ifdef USEDMSYSTEM										//20190507
//card1
#define AXISTABX				0x00000
#define AXISTABY				0x00001
//card2
#define AXISLEFTZ				0x10000
#define AXISBETSUB				0x10001		//�Ӷ���
#define AXISBETPRI				0x10002		//������
#define AXISAPT					0x10003		//��Ȧ
//card3
#define AXISRIGHTZ				0x20000
#define AXISBETSUB2				0x20001     //�Ӷ���
#define AXISBETPRI2				0x20002		//������
#define AXISAPT2				0x20003		//��Ȧ
//�����												//20190626
#define AXISLEFTZTHICK			0x10000
#define AXISRIGHTZTHICK			0x20001

#else	//USEDMSYSTEM
//card1
#define AXISTABX				0x00000
#define AXISTABY				0x00001
#define AXISBETSUB				0x00002		//�Ӷ���
#define AXISBETPRI				0x00003		//������
//card2
#define AXISLEFTZ				0x10000
#define AXISRIGHTZ				0x10001
#define AXISAPT					0x10003		//��Ȧ
//card3
#define AXISBETSUB2				0x20000     //�Ӷ���
#define AXISBETPRI2				0x20001		//������
#define AXISAPT2				0x20003		//��Ȧ

#endif	//USEDMSYSTEM
	
#endif	//NEWE2	
 
/*--------------------IO�ڶ���---------------------------

  0xabcd  a: card no.        0:    1842-1
							 1:    1842-2
							 2:    1842-3
							 3:    7200-1
							 4:    7200-2
							 5:    9112 
      b&c&d: bit no.      0~1F: 0~1F

--------------------------------------------------------*/
/*--------------------����ڶ���------------------------*/
///DMC-1842-3��I/O��չ��DB14064 DO ���壿����
#define  OLOADUPRIGHT                   0x20011  //�����Ҳ��е���� DO0
#define  OLOADUPLEFT                    0x20012  //��������е���� DO1
#define  OLOADDOWNRIGHT                 0x20013  //�����Ҳ��е���� DO2
#define  OLOADDOWNLEFT                  0x20014  //��������е���� DO3
#define  OLOADVACUUMCHRIGHT             0x20015  //�����Ҳ��е����յ�ŷ�
#define  OLOADVACUUMCHLEFT				0x20016  //
#define	 OLOADPUFF						0x20017  //���ϴ��ϵ�ŷ�
#define	 OLOADSHACKE					0x20018  //���϶��ϵ�ŷ�
#define  OLOADSNAPX       				0x20019  //��λX
#define  OLOADSNAPY       				0x2001A  //��λy 
#define  OLOADDOLLYLOCK					0x2001B  //����С������
///reserved
///reserved
///reserved
#define  OUNLOADUPLEFT                  0x2001F //��������е����
#define  OUNLOADDOWNLEFT                0x20020//��������е����
#define  OUNLOADUPRIGHT                 0x20021//�����Ҳ��е����
#define  OUNLOADDOWNRIGHT               0x20022//�����Ҳ��е����
#define  OUNLOADVACUUMCHLEFT	 		0x20023//��������е����յ�ŷ�
#define  OUNLOADVACUUMCHRIGHT           0x20024//�����Ҳ��е����յ�ŷ�
#define  OUNLOADDOLLYLOCK       	    0x20025//����С������

//********************����˿ڶ���*****************************
///DMC-1842-3��I/O��չ��DB14064 DI ����
//#define  Input   N��ʾ���� P��ʾ���
#define  ILOADERLTHANDVN				 0x20028//�������������N 
#define  ILOADERRTHANDVN				 0x20029//�����Ҳ�������N
#define  ILOADERLTHANDVP				 0x2002A//�������������P
#define  ILOADERRTHANDVP				 0x2002B//�����Ҳ�������P
#define  ILOADERRSUCKOK1				 0x2002C//�����Ҳ����ǲ�����סǰ	
#define  ILOADERRSUCKOK2				 0x2002D//�����Ҳ����ǲ�����ס��
#define  ILOADERLSUCKOK1				 0x2002E//����������ǲ�����סǰ
#define  ILOADERLSUCKOK2				 0x2002F//����������ǲ�����ס��
#define  ILOADERDOLLYISLOCK              0x20030//����С���Ƿ����� 
#define  ILOADERDOLLYARRIVE			     0x20031//����С���Ƶ�λ
#define  ILOADERDOLLYISRISEARRIVE        0x2003E//0x20032//����С���Ƿ�������λ 
#define  ILOADSNAPXN1					 0x20033//��λ����XN1
#define  ILOADSNAPXN2					 0x20034//��λ����XN2
#define  ILOADSNAPXP1					 0x20035//��λ����XP1
#define  ILOADSNAPXP2				     0x20036//��λ����XP2
#define  ILOADSNAPYN					 0x20037//��λ����YN2
#define  ILOADSNAPYP					 0x20038//��λ����YP2
#define  ILOADSHACKEN					 0x20039//��������N
#define  ILOADSHACKEP					 0x2003A//��������P
#define	 ILOADEREMPTY					 0x2003B//����С��ȱ��
#define	 ILOADERLTHANDVPSEC				 0x2003C//�������P2
#define  ILOADERRTHANDVPSEC				 0x2003D//�����Ҳ�P2
//reserved
//reserved
#define  IUNLOADERLTHANDVN				 0x20040//�������������
#define  IUNLOADERLTHANDVP			     0x20041//������������
#define  IUNLOADERRSUCKOK1				 0x20042//�����Ҳ����ǲ�����ס	
#define  IUNLOADERLSUCKOK2				 0x20043//�����Ҳ����ǲ�����ס
//reserved
#define  IUNLOADERDOLLYISRISEARRIVE		 0x20045
#define  IUNLOADERRTHANDVN				 0x20046//�����Ҳ�������N
#define  IUNLOADERRTHANDVP				 0x20047//�����Ҳ�������P
#define  IUNLOADERRSUCKOK2               0x20048//����������Ƿ���ס����ź�
#define  IUNLOADERLSUCKOK1				 0x20049//����������Ƿ���ס����ź�
#define  IUNLOADERDOLLYARRIVE			 0x2004A	  //����С���Ƶ�λ
#define  IUNLOADERDOLLYISLOCK            0x2004B  //����С���Ƿ����� 
#define  IUNLOADERLTHANDVPSEC			 0x2004C   //�������P2
#define  IUNLOADERRTHANDVPSEC            0x2004D  //�����Ҳ�P2

//  ************** 9112 ****����˿�****************//ly:C�ͻ���B�ͻ��˰忨�˿ڲ����Ķ�

#define  RELOADBOARD          	     0x50000			//�ӹ���һ�����ٴ����ϲ��ڼӰ�
#define  OSORBOK             	     0x50001			//ƽ̨ȡ�����
#define  OUNLOARDMOVETOTABLE  	     0x50002			//����׼��
#define  OAOTUBIGN        	         0x50003			//��ʼ����
#define  OLEFTERRO        	         0x50004			//���ӹ�ʧ��
#define  ORIGHTERRO        	         0x50005			//�Ҳ�ӹ�ʧ��
#define  OLOARDBORD       	         0x50006			//��������
#define  OUNLAORDBORD       	     0x50007			//��������
#define  OHOMEALL           	     0x50008			//�������������
#define  OPROCEXIT           	     0x50009			//��������
#define  STOPMOVE					 0x5000A			//��ȫ�������������ֱ� �͵�ƽ���� ly add 20110813

#define  OCleartheCum				 0x5000F           //���������0

//  ************** 9112 ****����˿�****************

#define  IHOMEALLOK				     0x50000			//����������������
#define  IREADYLOAD				     0x50001			//�Ѿ������ϣ������ϰ嵽ƽ̨
#define  ILOADOK				     0x50002			//�������
#define  IONLYLEFT				     0x50003			//���һ�Ű�
#define  IUNLOADOK				     0x50004			//�������
#define  IALARM				         0x50005			//�쳣����
#define  IDEPOTEMPTY		         0x50006			//��������
#define  IPUTBOARDONTABABLE	         0x50007			//���ϵ�ƽ̨����������
#define  IREADYTOUNLOADOK      	     0x50008			//������׼�����
#define  IOVERTIMEALARM        	     0x50009			//��ʱ����
 
#define  IONGFULLALARM				 0x5000B			//NG�ϲ������ź�  �͵�ƽ��  ly add 20110813
#define  MANIPULATORGERROR			 0x5000C			//ԭ�������ϳ�ʱ����12+16 �����޸�Ϊ��е�ִ��󱨾�

#define  MANIPULATORLOADDOOR		 0x5001D			//���ϰ�ȫ�ſ�29+16���ӵ��������ű���
#define  MANIPULATORUNLOADDOOR		 0x5001E			//���ϰ�ȫ�ſ�30+16

#ifdef NEWE2
// 	//***********************1842-1 ****����˿�C�ͻ�*********************
// 	#define  OSERVOALRAMCLEAR1			 0x00001			//X�ŷ��������
// 	#define  OSERVOALRAMCLEAR2			 0x00002			//Y�ŷ��������
// 	#define  OSERVOALRAMCLEAR6			 0x00003			//R�ŷ��������
// 	#define  OSERVOALRAMCLEAR5			 0x00004			//G�ŷ��������
// 	//***********************1842-2****����˿�C�ͻ�*********************
// 	#define  OSERVOALRAMCLEAR3           0x10001			//Z1�ŷ��������?????
// 	#define  OSERVOALRAMCLEAR4			 0x10002			//Z2�ŷ��������?????
	//***********************DMC-4040 ****����˿�E�ͻ�*********************

	//***********************MD-B140-1****����˿�E2�ͻ�*********************
	#define  OSERVOALRAMCLEAR3           0x00003			//�ĸ��ᱨ����λ���//Z1�ŷ��������?????
	//***********************MD-B140-2****����˿�E2�ͻ�*********************  
	#define  OSERVOALRAMCLEAR6			 0x10003			//�ĸ��ᱨ����λ���//R�ŷ��������

   //E2��ʹ�ã�����D2C�����˵�
	#define  OSERVOALRAMCLEAR4			 0x10002			//Z2�ŷ��������?????
	#define  OSERVOALRAMCLEAR1			 0x00001			//X�ŷ��������
	#define  OSERVOALRAMCLEAR2			 0x00002			//Y�ŷ��������
	#define  OSERVOALRAMCLEAR5			 0x00004			//G�ŷ��������

	//  ************** HSL-DO32****����˿�E2�ͻ�****************
	#define  LEFTSHUTTERC                0x30000		   //��������׵�ŷ�//D2C����Ԥ��բ��                //ON_��ͨ��
	#define  RIGHTSHUTTERC               0x30001		   //�ҿ������׵�ŷ�//���̹�·�л�  (/�������1)	 //ON_����·	
	#define  OTHETALENSPROTECT	         0x30002		   //��ͷ������
	#define  OLASERPOWERCLEANER          0x30003		   //�⹦�ʴ���    (/ƽ̨��ǯ)
	#define  OTESTTHICKNESSN1	         0x30004		   //�������1
	#define  OTESTTHICKNESSN2            0x30005		   //�������2
	#define  OTABLEVACUUMVALVE1          0x30006		   //ƽ̨�������1	
	#define  OTABLEVACUUMVALVERE1        0x30007           //ƽ̨�ͷ����1
	#define  OTABLEVACUUMVALVE2          0x30008		   //ƽ̨�������2
	#define  OTABLEVACUUMVALVERE2        0x30009		   //ƽ̨�ͷ����2
	#define  OTABLECLAMP				 0x3000A		   //ƽ̨��ǯ
	#define  OFANPOWERON				 0x3000B		   //����ϵ�
	#define  OLAMPREDON					 0x3000C			//���ƺ��
	#define  OLAMPGREENON				 0x3000D			//�����̵�
	#define  OCOMMONALARM				 0x3000E			//������
	//����AOM����񾵿��˿ڸߵ�
	#define  AOMTESTREPLACE              0x3000F//0x3000D//��·AOM����  ��·���Գ���ʹ�ã��������û��ʹ������˿�
    //#define  OLASERON					 0x3001C			//OEM����������ʹ���ϵ�
    #define  OLASERON2					 0x3001D			//������2����ʹ���ϵ�
    #define  OLASERRESET1			     0x3001E			//��������λ1 ����
    #define  OLASERRESET2				 0x3001F		    //��������λ1 ����

    //��ʹ�õ�
	#define  OLASERWARNUP				 0x30030			//����Ԥ��բ��                //ON_��ͨ��
	#define  OLASERSHUTTER1              0x30031			//���̹�·�л�  (/�������1)	 //ON_����·
	#define  OLASERSHUTTERON			 0x30037			//���������Ŵ�
    #define  OLASERSHUTTER2              0x30032			//TOPHAT��·�л�(/�������2)
	// ************** HSL-DI16DO16-1 ****����˿�E�ͻ�****************
	#define  OCCDLIGHTONCOL				 0x40000			//ͬ���Դ1����(CH1)
	#define  OCCDLIGHTONCOR				 0x40001			//ͬ���Դ2����(CH2)
	#define  OCCDLIGHTONL				 0x40002			//���ι�Դ1����(CH3)
	#define  OCCDLIGHTONR				 0x40003			//���ι�Դ2����(CH4)
	#define  OLCHANNELSELECT			 0x40004			//CH-select1***ԭ�����Դ�л�
	#define  ORCHANNELSELECT			 0x40005			//CH-select2***ԭ�����Դ�л�
	#define  OCCDLIGHTSOURCEENABLE		 0x40006			//Write trgl����д���ź�***ԭ���ι�Դȷ��
	#define  OCCDLIGHTTUNELBIT0		     0x40007			//8λ��Դ���ȿ��ƣ�bit0~bit7
	#define  OCCDLIGHTTUNELBIT1	         0x40008			//
	#define  OCCDLIGHTTUNELBIT2			 0x40009			//
	#define  OCCDLIGHTTUNELBIT3	         0x4000A			//
	#define  OCCDLIGHTTUNELBIT4		     0x4000B			//
	#define  OCCDLIGHTTUNELBIT5	         0x4000C			//
	#define  OCCDLIGHTTUNELBIT6		     0x4000D		    //
	#define  OCCDLIGHTTUNELBIT7		     0x4000E		    //bit7
    #define  OLASERON					 0x4000F			//OEM����������ʹ���ϵ�
    // ************** HSL-DI16DO16-2 ****����˿�E�ͻ�****************//����Ԥ����Ϊ4ccd����
	#define  OCCDLIGHTONCOL1			 0x60000			//ͬ���Դ1����(CH1)
	#define  OCCDLIGHTONCOR1			 0x60001			//ͬ���Դ2����(CH2)
	#define  OCCDLIGHTONL1				 0x60002			//���ι�Դ1����(CH3)
	#define  OCCDLIGHTONR1				 0x60003			//���ι�Դ2����(CH4)
	#define  OCCDLIGHTTUNEHEADSEL1		 0x60004			//CH-select1***ԭ�����ͨ·ѡ��
	#define  OCCDLIGHTCONTROLSEL1		 0x60005			//CH-select2***ԭ���ι�Դ��/���ѡ��
	#define  OCCD1						 0x60006			//Write trg2����д���ź�
	#define  OCCDLIGHTTUNERBIT0          0x60007			//��Դ���ȿ��ƣ�bit0~bit7
	#define  OCCDLIGHTTUNERBIT1          0x60008			//
	#define  OCCDLIGHTTUNERBIT2          0x60009			//
	#define  OCCDLIGHTTUNERBIT3          0x6000A			//
	#define  OCCDLIGHTTUNERBIT4          0x6000B			//
	#define  OCCDLIGHTTUNERBIT5          0x6000C			//	
	#define  OCCDLIGHTTUNERBIT6          0x6000D			//
	#define  OCCDLIGHTTUNERBIT7          0x6000E			//bit7

	//***********************DMC-4040 ****����˿�E�ͻ�*********************
	#define  IMANUXBTN					0x00002		//X
	#define  IMANUYBTN					0x00003		//Y
	#define  IMANUX1BTN					0x00004		//*10
	#define  IMANUX2BTN					0x00005		//*100
	#define  ISERVOALARMX				0x00006		//X���ŷ�����			
	#define  ISERVOALARMY				0x00007		//Y���ŷ�����
	//***********************MD-B140-1****����˿�E�ͻ�*********************
	#define  ITHICKNESSHOME1			 0x10000			//����դ�� Z1���
	#define  ITHICKNESSHOME2		 	 0x10001			//����դ�� Z2���
	#define  ISERVOALARMUNBETSUB		 0x10002			//R���ŷ�����
	#define  ISERVOALARMUNBETHOST		 0x10003			//G���ŷ�����
	//û������������
	#define  ISERVOALARMZLEFT		 	 0x10004			//Z1���ŷ�����			 
	#define  ISERVOALARMZRIGHT			 0x10005			//Z2���ŷ�����
	//***********************MD-B140-2****����˿�E�ͻ�*********************
	#define  ADRIVERWARNING		 	     0x20000			//A��������		//����
	#define  A1DRIVERWARNING		 	 0x20001			//A1��������	//����
	#define  G1DRIVERWARNING		 	 0x20002			//G1��������	//����
	#define  R1DRIVERWARNING		 	 0x20003			//R1��������	//����
	//  ************** HSL-DI32****����˿�E2�ͻ�****************
	#define  ILASERWARMUPN				0x30000			//Ԥ��բ������N
	#define  ISWATERFAULT				0x30000			//��Դadd ����C45�Ż�����ˮ��Ԥ�������ߵ�ƽ����  YBJ
	#define  ILASERWARMUPP				0x30001			//Ԥ��բ������P
	#define  ILASERSHUTTERLTN			0x30002			//����̹�·***ԭ��·ת��1N
	#define  ILASERSHUTTERLTP			0x30003			//���᳤��·***��·ת��1P
	#define  ILASERSHUTTERRTN			0x30004			//����̹�·***��·ת��2N
	#define  ILASERSHUTTERRTP			0x30005			//���᳤��·***��·ת��2P
	#define	 ITHICKNESS1N				0x30006			//�������1N 
	#define  ITHICKNESS1P				0x30007			//�������1P
	#define	 ITHICKNESS2N				0x30008			//�������2N
	#define  ITHICKNESS2P				0x30009			//�������2P
	#define  ISWATERCOOLFAULT			0x3000A			//С��ˮ�����ϱ���
	#define  IAOMTEMPROTECT				0x3000B			//AOM�¶ȱ�������
	#define  IDOORPROTECT				0x3000C			//�Ŷ��䰲ȫ��������
	#define  ILENSWINDOW1ERROR			0x3000D			//ɨ�辵������1δ��λ����
	#define  ILENSWINDOW2ERROR			0x3000E			//ɨ�辵������2δ��λ����
	#define  ITABLTVACUMM				0x3000F//0x4000D//PCB���1 ��ƽ̨���
	#define  ITABRTVACUMM				0x30010//0x4000E//PCB���2 ��ƽ̨���
	#define  ILASERGASFLUX				0x30011			//���Ᵽ������������
	#define  ITABLECLAMPN				0x30012			//ƽ̨��ǯ����N 
	#define  ITABLECLAMPP				0x30013			//ƽ̨��ǯ����P
	#define  IDUSTOUT1PRESSURE			0x30014			//��·�鳾��ѹ
	#define  IDUSTOUT2PRESSURE			0x30015			//��·�鳾��ѹ
	//#define  IDUSTOUT2PRESSURE			0x30016		    //��������Դ���� ����
	#define  MOTIONSTOP					0x30017//0x4000A//��ͣ
	#define  MOTIONSTOPRESET			0x30018//0x4000B//��ͣ��λ//ly change20110311 �ͼ�ͣ�źŶԵ�C002����
	#define	 IAIRPRESSURE              	0x30019//0x4000C//ѹ��������ѹ
	#ifdef CTI
	#define	 ICTIOK					    0x3001A//0x3001E//�͵�ƽ���� CTI�±��� jpc add 20131129 
	#endif
	#define    LEFTTHICKNESS1N          0x3001B         //�����������+
	#define    LEFTTHICKNESS1P          0x3001C         //�����������-
	#define    RIGHTTHICKNESS1N         0x3001D         //�����������+
	#define    RIGHTTHICKNESS1P         0x3001E         //�����������-
	#define    IDOOROPENPROTECT			0x3001F//0x3000F//��ȫ����λ���� �͵�ƽ����

	//  ************** HSL-DI16DO16-1 ****����˿�E�ͻ�****************
	#define  ICOLIGHT1ERROR				0x40000			//ͬ���1����//����ly
	#define  ICOLIGHT2ERROR				0x40001			//ͬ���2����//����ly
	#define  IRINGLIGHT1ERROR			0x40002			//���ι�1����
	#define  IRINGLIGHT2ERROR			0x40003			//���ι�2����
	#define  DRILLMATRIXSWITCH			0x40005			//����·�ü���㶯����1
	#define  ITEMPERATUREFAULT			0x40006			//VSWR//�������¶ȱ���
	#define  IWATERFLOWPROTECT			0x40007			//System Warning 1//������ˮ������
	#define	 ILASERONOK					0x40008			//System Fault1 //�������ϵ�OK
	#define  DRILLMATRIXSWITCH2			0x4000C			//����·�ü���㶯����2
	#define  ITEMPERATUREFAULT2			0x4000D			//VSWR//�������¶ȱ���2
	#define  IWATERFLOWPROTECT2			0x4000E			//System Warning 1//������ˮ������2
	#define	 LASEROK2				    0x4000F			//System Fault1 //������2�ϵ�OK	
	//  ************** HSL-DI16DO16-2 ****����˿�E�ͻ�****************
	#define  ICOLIGHT1ERROR2			0x60000			//ͬ���1����//����ly//4CCD����
	#define  ICOLIGHT2ERROR2			0x60001			//ͬ���2����//����ly//4CCD����
	#define  IRINGLIGHT1ERROR2			0x60002			//���ι�1����//4CCD����
	#define  IRINGLIGHT2ERROR2			0x60003			//���ι�2����//4CCD����

	#define  ITOPHAT1N					0x30006			//ƽ������1***TopHat�л�����1N 
	#define  ITOPHAT2N					0x30007			//��˹����1***TopHat�л�����2N
	#define  ITOPHAT1P					0x30008			//ƽ������2***TopHat�л�����1P
	#define  ITOPHAT2P					0x30009			//��˹����2***TopHat�л�����2P
	#define  ITABXERROR				    0x40000			//X���դ�ߴ���
	#define  ITABYERROR					0x40001			//Y���դ�ߴ��� 
	#define  IMANURUNBTN				0x40013			//�����ź����룺06~0C
	#define  IMANUSTOPBTN				0x40014			//
	#define  IMANUX3BTN					0x40019			//
	#define  I1842_1ERROR				0x4001A			//�˶���1����
	#define  I1842_2ERROR				0x4001B			//�˶���2����

#else	//NEWE2

#ifdef IO_C//ly add 20110115

#ifdef USEDMSYSTEM										//20190507
//���ݱ���
#define  OSERVOALRAMCLEAR1			 0x0000A			//X�ŷ��������
#define  OSERVOALRAMCLEAR2			 0x0000B			//Y�ŷ��������
//***********************18XX-1����˿�*********************
#define  OSERVOALRAMCLEAR3           0x00000			//Z1�ŷ��������?????
#define  OSERVOALRAMCLEAR6			 0x00001			//R1�ŷ��������
#define  OSERVOALRAMCLEAR5			 0x00002			//G1�ŷ��������
//***********************18XX-2����˿�*********************
#define  OSERVOALRAMCLEAR4			 0x10000			//Z2�ŷ��������?????
#define  OSERVOALRAMCLEAR7           0x10001			//G2�ŷ��������
#define  OSERVOALRAMCLEAR8			 0x10002			//R2�ŷ��������
#else
//***********************18XX-1����˿�*********************
#define  OSERVOALRAMCLEAR1			 0x00001			//X�ŷ��������
#define  OSERVOALRAMCLEAR2			 0x00002			//Y�ŷ��������
#define  OSERVOALRAMCLEAR6			 0x00003			//R�ŷ��������
#define  OSERVOALRAMCLEAR5			 0x00004			//G�ŷ��������
//***********************18XX-2����˿�*********************
#define  OSERVOALRAMCLEAR3           0x10001			//Z1�ŷ��������?????
#define  OSERVOALRAMCLEAR4			 0x10002			//Z2�ŷ��������?????
//***********************18XX-3����˿�*********************
#define  OSERVOALRAMCLEAR7           0x20001			//G1�ŷ��������
#define  OSERVOALRAMCLEAR8			 0x20002			//R1�ŷ��������
#endif

//  *********************7200-1����˿�*********************
#define  OLASERWARNUP                0x30000		   //����Ԥ��բ��                //ON_��ͨ��
#define  OLASERSHUTTER1              0x30001		   //���̹�·�л�  (/�������1)	 //ON_����·
#define  OLASERSHUTTER2              0x30002		   //TOPHAT��·�л�(/�������2)
#define  OTHETALENSPROTECT	         0x30003		   //��ͷ������
#define  OLASERPOWERCLEANER          0x30004		   //�⹦�ʴ���    (/ƽ̨��ǯ)
#define  OTESTTHICKNESSN1	         0x30005		   //�������1
#define  OTESTTHICKNESSN2            0x30006		   //�������2
#define  OTABLEVACUUMVALVE1          0x30007		   //ƽ̨�������1	
#define  OTABLEVACUUMVALVERE1        0x30008           //ƽ̨�ͷ����1
#define  OTABLEVACUUMVALVE2          0x30009		   //ƽ̨�������2
#define  OTABLEVACUUMVALVERE2        0x3000A		   //ƽ̨�ͷ����2
#define  OTABLECLAMP				 0x3000B		   //ƽ̨��ǯ
#define  OFANPOWERON				 0x3000C		   //����ϵ�

#define  OLAMPREDON					 0x30013			//���ƺ��
#define  OLAMPGREENON				 0x30014			//�����̵�
#define  OCOMMONALARM				 0x30015			//������

#define  OLASERSHUTTERON			 0x30017			//���������Ŵ�
#define  OLASERON					 0x30018			//����������ʹ���ϵ�
#define  OLASERON2					 0x30019			//������2����ʹ���ϵ�

//  ***********************7200-2����˿�*************************
#define  OCCDLIGHTONCOL				 0x40000			//ͬ���Դ1����(CH1)
#define  OCCDLIGHTONCOR				 0x40001			//ͬ���Դ2����(CH2)
#define  OCCDLIGHTONL				 0x40002			//���ι�Դ1����(CH3)
#define  OCCDLIGHTONR				 0x40003			//���ι�Դ2����(CH4)
#define  OLCHANNELSELECT			 0x40004			//CH-select1***ԭ�����Դ�л�
#define  ORCHANNELSELECT			 0x40005			//CH-select2***ԭ�����Դ�л�
#define  OCCDLIGHTSOURCEENABLE		 0x40006			//Write trgl����д���ź�***ԭ���ι�Դȷ��
#define  OCCDLIGHTTUNELBIT0		     0x40007			//8λ��Դ���ȿ��ƣ�bit0~bit7
#define  OCCDLIGHTTUNELBIT1	         0x40008			//
#define  OCCDLIGHTTUNELBIT2			 0x40009			//
#define  OCCDLIGHTTUNELBIT3	         0x4000A			//
#define  OCCDLIGHTTUNELBIT4		     0x4000B			//
#define  OCCDLIGHTTUNELBIT5	         0x4000C			//
#define  OCCDLIGHTTUNELBIT6		     0x4000D		    //
#define  OCCDLIGHTTUNELBIT7		     0x4000E		    //bit7

#define  OCCDLIGHTONCOL1			 0x40010			//ͬ���Դ1����(CH1)
#define  OCCDLIGHTONCOR1			 0x40011			//ͬ���Դ2����(CH2)
#define  OCCDLIGHTONL1				 0x40012			//���ι�Դ1����(CH3)
#define  OCCDLIGHTONR1				 0x40013			//���ι�Դ2����(CH4)
#define  OCCDLIGHTTUNEHEADSEL1		 0x40014			//CH-select1***ԭ�����ͨ·ѡ��
#define  OCCDLIGHTCONTROLSEL1		 0x40015			//CH-select2***ԭ���ι�Դ��/���ѡ��
#define  OCCD1						 0x40016			//Write trg2����д���ź�
#define  OCCDLIGHTTUNERBIT0          0x40017			//��Դ���ȿ��ƣ�bit0~bit7
#define  OCCDLIGHTTUNERBIT1          0x40018			//
#define  OCCDLIGHTTUNERBIT2          0x40019			//
#define  OCCDLIGHTTUNERBIT3          0x4001A			//
#define  OCCDLIGHTTUNERBIT4          0x4001B			//
#define  OCCDLIGHTTUNERBIT5          0x4001C			//	
#define  OCCDLIGHTTUNERBIT6          0x4001D			//
#define  OCCDLIGHTTUNERBIT7          0x4001E			//bit7

#ifdef USEDMSYSTEM										//20190507
//���ݱ���
#define  ISERVOALARMX				 0x0000A			//X���ŷ�����
#define  ISERVOALARMY				 0x0000B			//Y���ŷ�����
//***********************18XX-1����˿�*********************
#define  ITHICKNESSHOME1			 0x00000			//����դ��
#define  ISERVOALARMZLEFT		 	 0x00001			//Z1���ŷ�����
#define  ISERVOALARMUNBETHOST		 0x00004			//R1���ŷ�����
#define  ISERVOALARMUNBETSUB		 0x00005			//G1���ŷ�����
#define  ISERVOALARMAPT				 0x00007			//A1���ŷ�����
//***********************18XX-2����˿�*********************
#define  ITHICKNESSHOME2		 	 0x10000			//����դ��
#define  ISERVOALARMZRIGHT			 0x10001			//Z2���ŷ�����
#define  ISERVOALARMUNBETSUB1		 0x10004			//G2���ŷ�����
#define  ISERVOALARMUNBETHOST1		 0x10005			//R2���ŷ�����
#define  ISERVOALARMAPT1			 0x10007			//A2���ŷ�����
#else
//***********************18XX-1����˿�*********************
#define  ISERVOALARMX				 0x00004			//X���ŷ�����
#define  ISERVOALARMY				 0x00005			//Y���ŷ�����
#define  ISERVOALARMUNBETSUB		 0x00006			//G���ŷ�����
#define  ISERVOALARMUNBETHOST		 0x00007			//R���ŷ�����
//***********************18XX-2����˿�*********************
#define  ITHICKNESSHOME1			 0x10000			//����դ��
#define  ITHICKNESSHOME2		 	 0x10001			//����դ��
#define  ISERVOALARMZLEFT		 	 0x10004			//Z1���ŷ�����
#define  ISERVOALARMZRIGHT			 0x10005			//Z2���ŷ�����
#define  ISERVOALARMAPT				 0x10007			//A���ŷ�����
//***********************18XX-3����˿�*********************
#define  ISERVOALARMUNBETSUB1		 0x20004			//G1���ŷ�����
#define  ISERVOALARMUNBETHOST1		 0x20005			//R1���ŷ�����
#define  ISERVOALARMAPT1			 0x20007			//A1���ŷ�����
#endif

//  *********************7200-1����˿�***********************
#define  ILASERWARMUPN				0x30000			//Ԥ��բ������N
#define  ISWATERFAULT				0x30000			//��Դadd ����C45�Ż�����ˮ��Ԥ�������ߵ�ƽ����  YBJ
#define  ILASERWARMUPP				0x30001			//Ԥ��բ������P //����Ϊ��Ϊ�����Դ���쳣��������
#define  ILASERSHUTTERLTN			0x30002			//����̹�·***ԭ��·ת��1N
#define  ILASERSHUTTERLTP			0x30003			//���᳤��·***��·ת��1P
#define  ILASERSHUTTERRTN			0x30004			//����̹�·***��·ת��2N
#define  ILASERSHUTTERRTP			0x30005			//���᳤��·***��·ת��2P
#define  ITOPHAT1N					0x30006			//δʹ��
#define  ITOPHAT2N					0x30007			//δʹ��
#define  ITOPHAT1P					0x30008			//δʹ��
#define  ITOPHAT2P					0x30009			//δʹ��
#define  ISWATERCOOLFAULT			0x3000A			//С��ˮ�����ϱ���
#define  IAOMTEMPROTECT				0x3000B			//AOM�¶ȱ�������
#define  IDOORPROTECT				0x3000C			//�Ŷ��䰲ȫ��������
#define  ILENSWINDOW1ERROR			0x3000D			//ɨ�辵������1δ��λ����
#define  ILENSWINDOW2ERROR			0x3000E			//ɨ�辵������2δ��λ����
#define  IDOOROPENPROTECT			0x3000F			//ly add 20140418 �͵�ƽ����

#define  ILASERGASFLUX				0x30011			//���Ᵽ������������
#define  ITABLECLAMPN				0x30012			//ƽ̨��ǯ����N 
#define  ITABLECLAMPP				0x30013			//ƽ̨��ǯ����P
#define  IDUSTOUT1PRESSURE			0x30014			//��·�鳾��ѹ
#define  IDUSTOUT2PRESSURE			0x30015			//��·�鳾��ѹ
#define  DRILLMATRIXSWITCH			0x30016			//����·�ü���㶯����
#define  ITEMPERATUREFAULT			0x30017			//�������¶ȱ���
#define  IWATERFLOWPROTECT			0x30018			//������ˮ������
#define	 ILASERONOK					0x30019			//�������ϵ�OK

#ifdef CTI
#define	 ICTIOK						0x3001E			//�͵�ƽ���� CTI�±��� jpc add 20131129 
#endif

//  **********************7200-2����˿�**************************
#define  ITABXERROR				    0x40000			//X���դ�ߴ���
#define  ITABYERROR					0x40001			//Y���դ�ߴ��� 
#define  ICOLIGHT1ERROR				0x40002			//ͬ���1����//����ly
#define  ICOLIGHT2ERROR				0x40003			//ͬ���2����//����ly
#define  IRINGLIGHT1ERROR			0x40004			//���ι�1����
#define  IRINGLIGHT2ERROR			0x40005			//���ι�2����
#define  ICOLIGHT1ERROR2			0x40006			//ͬ���1����//����ly//4CCD����
#define  ICOLIGHT2ERROR2			0x40007			//ͬ���2����//����ly//4CCD����
#define  IRINGLIGHT1ERROR2			0x40008			//���ι�1����//4CCD����
#define  IRINGLIGHT2ERROR2			0x40009			//���ι�2����//4CCD����
#define  MOTIONSTOP					0x4000A			//��ͣ
#define  MOTIONSTOPRESET			0x4000B			//��ͣ��λ//ly change20110311 �ͼ�ͣ�źŶԵ�C002����

#ifdef SENTINAL
#define	 IAIRPRESSURE              	0x30010			//ѹ��������ѹ
#else
#define	 IAIRPRESSURE              	0x4000C			//ѹ��������ѹ
#endif

#define  ITABLTVACUMM				0x4000D			//PCB���1
#define  ITABRTVACUMM				0x4000E			//PCB���2
#define	 ITHICKNESS1N				0x4000F			//�������1N 
#define  ITHICKNESS1P				0x40010			//�������1P
#define	 ITHICKNESS2N				0x40011			//�������2N
#define  ITHICKNESS2P				0x40012			//�������2P
#define  IMANURUNBTN				0x40013			//�����ź����룺06~0C
#define  IMANUSTOPBTN				0x40014			//
#define  IMANUXBTN					0x40015			//
#define  IMANUYBTN					0x40016			//
#define  IMANUX1BTN					0x40017			//
#define  IMANUX2BTN					0x40018			//
#define  IMANUX3BTN					0x40019			//
#define  I1842_1ERROR				0x4001A			//�˶���1����
#define  I1842_2ERROR				0x4001B			//�˶���2����

#define  LASEROK2 			    	0x4001E			//������2�ϵ�OK			 

#else  //IO_C

//  ************** 7200-1********************
#define  OLASERWARNUP                0x30000		   //����Ԥ��բ��                //ON_��ͨ��
#define  OLASERSHUTTER1              0x30001		   //���̹�·�л�  (/�������1)	 //ON_����·
#define  OLASERSHUTTER2              0x30002		   //TOPHAT��·�л�(/�������2)
#define  OTESTTHICKNESSN1	         0x30003		   //�������1
#define  OTESTTHICKNESSP1            0x30004		   //
#define  OTHETALENSPROTECT	         0x30005		   //��ͷ������
#define  OLASERPOWERCLEANER          0x30006		   //�⹦�ʴ���    (/ƽ̨��ǯ)
#define  OLASERPROTECTGAS            0x30007		   //�������屣��
#define  OTABLEVACUUMVALVE1          0x30008		   //ƽ̨�������1	
#define  OTABLEVACUUMVALVERE1        0x30009           //ƽ̨�ͷ����1
#define  OTABLEVACUUMVALVE2          0x3000A		   //ƽ̨�������2
#define  OTABLEVACUUMVALVERE2        0x3000B		   //ƽ̨�ͷ����2
#define  OTESTTHICKNESSN2            0x3000C		   //�������2
#define  OTESTTHICKNESSP2            0x3000D		   //
#define  OFANPOWERON				 0x3000E		   //����ϵ�

#define  OTABLECLAMP				 0x30012		   //ƽ̨��ǯ

#ifdef PPLASER
#define  OLASERSHUTTERCMD			 0x30018			//PP�ͼ������ϵ��ã�18~1E	
#define  OLASERA					 0x30019            // 
#define  OLASERB					 0x3001A            // 
#define  OLASERAIM					 0x3001B            //
#define  OLASERCLRFLT				 0x3001C			//
#define  OLASERRFENC				 0x3001D			//
#define  OLASERPWM					 0x3001E			//
#else
#define  OLCHANNELSELECT			 0x30018			//�����Դ�л�
#define  ORCHANNELSELECT			 0x30019			//�����Դ�л�

#define  OLASERON					 0x3001E			//����������ʹ���ϵ�
#define  OLASERSHUTTERON			 0x3001F			//���������Ŵ�
#endif

//  ************** 7200-2********************
#define  OLAMPREDON					 0x40000			//���ƺ��
#define  OLAMPGREENON				 0x40001			//�����̵�
#define  OCOMMONALARM				 0x40002			//������
#define  OSERVOALRAMCLEAR1			 0x40003			//X�ŷ��������
#define  OSERVOALRAMCLEAR2			 0x40004			//Y�ŷ��������
#define  OSERVOALRAMCLEAR3           0x40005			//Z1�ŷ��������
#define  OSERVOALRAMCLEAR4			 0x40006			//Z2�ŷ��������
#define  OSERVOALRAMCLEAR5			 0x40007			//G�ŷ��������
#define  OSERVOALRAMCLEAR6			 0x40008			//R�ŷ��������

#ifdef CCSRING
#define  OCCDLIGHTTUNEHEADSEL        0x40010			//�����ͨ·ѡ��
#define  OCCDLIGHTSOURCELEFT         0x40011			//���ι�Դ1����
#define  OCCDLIGHTSOURCERIGHT        0x40012			//���ι�Դ2����
#define  OCCDLIGHTCONTROLSEL         0x40013			//���ι�Դ��/���ѡ��
#define  OCCDLIGHTSOURCEENABLE       0x40014		    //���ι�Դȷ��д��

#define  OCCDLIGHTTUNEBITLCEN        0x40016			//ͬ���Դ1����
#define  OCCDLIGHTTUNEBITRCEN        0x40017			//ͬ���Դ2����
#define  OCCDLIGHTTUNEBIT11          0x40018			//���ι�Դ���ȿ��ƣ�bit0~bit8
#define  OCCDLIGHTTUNEBIT12          0x40019			//
#define  OCCDLIGHTTUNEBIT13          0x4001A			//
#define  OCCDLIGHTTUNEBIT14          0x4001B			//
#define  OCCDLIGHTTUNEBIT15          0x4001C			//
#define  OCCDLIGHTTUNEBIT16          0x4001D			//	
#define  OCCDLIGHTTUNEBIT17          0x4001E			//
#define  OCCDLIGHTTUNEBIT18          0x4001F			//bit8
#else
#define  OCCDLIGHTONCOL				 0x4000C			//ͬ���Դ1����
#define  OCCDLIGHTONCOR				 0x4000D			//ͬ���Դ2����
#define  OCCDLIGHTTUNELBIT0		     0x4000E			//��໷�ι�Դ���ȿ��ƣ�bit0~bit7
#define  OCCDLIGHTTUNELBIT1	         0x4000F			//
#define  OCCDLIGHTTUNELBIT2			 0x40010			//
#define  OCCDLIGHTTUNELBIT3	         0x40011			//
#define  OCCDLIGHTTUNELBIT4		     0x40012			//
#define  OCCDLIGHTTUNELBIT5	         0x40013			//
#define  OCCDLIGHTTUNELBIT6		     0x40014		    //
#define  OCCDLIGHTTUNELBIT7		     0x40015		    //bit7
#define  OCCDLIGHTONL				 0x40016			//���ι�Դ1����
#define  OCCDLIGHTONR				 0x40017			//���ι�Դ2����
#define  OCCDLIGHTTUNERBIT0          0x40018			//�Ҳ໷�ι�Դ���ȿ��ƣ�bit0~bit7
#define  OCCDLIGHTTUNERBIT1          0x40019			//
#define  OCCDLIGHTTUNERBIT2          0x4001A			//
#define  OCCDLIGHTTUNERBIT3          0x4001B			//
#define  OCCDLIGHTTUNERBIT4          0x4001C			//
#define  OCCDLIGHTTUNERBIT5          0x4001D			//	
#define  OCCDLIGHTTUNERBIT6          0x4001E			//
#define  OCCDLIGHTTUNERBIT7          0x4001F			//bit7
#endif

/*--------------------����ڶ���------------------------*/
//  ************** 7200-1********************
#define  MOTIONSTOPRESET			0x30000			//��ͣ��λ
#define  MOTIONSTOP		            0x30001			//��ͣ
#define	 IAIRPRESSURE              	0x30002			//ѹ��������ѹ
#define  ITABLTVACUMM				0x30003			//PCB���1
#define  ITABRTVACUMM				0x30004			//PCB���2
#define  DRILLMATRIXSWITCH			0x30005			//����·�ü���㶯����
#define  IMANURUNBTN				0x30006			//�����ź����룺06~0C
#define  IMANUSTOPBTN				0x30007			//
#define  IMANUXBTN					0x30008			//
#define  IMANUYBTN					0x30009			//
#define  IMANUX1BTN					0x3000A			//
#define  IMANUX2BTN					0x3000B			//
#define  IMANUX3BTN					0x3000C			//
#define  ILASERWARMUPN				0x3000D			//Ԥ��բ������N
#define  ILASERWARMUPP				0x3000E			//Ԥ��բ������P
#define  ILASERSHUTTERLTN			0x3000F			//��·ת��1N
#define  ILASERSHUTTERLTP			0x30010			//��·ת��1P
#define  ILASERSHUTTERRTN			0x30011			//��·ת��2N
#define  ILASERSHUTTERRTP			0x30012			//��·ת��2P
#define	 ITHICKNESS1N				0x30013			//�������1N 
#define  ITHICKNESS1P				0x30014			//�������1P
#define	 ITHICKNESS2N				0x30015			//�������2N
#define  ITHICKNESS2P				0x30016			//�������2P

#ifdef PPLASER
#define  ILASEROUT3					0x30019			//PP�ͼ������ϵ��ã�19~1E
#define  ILASEROUT2					0x3001A			// 
#define  ILASERSHUTTER_SENSOR		0x3001B		    //
#define	 ILASEROUT1					0x3001C			//
#define  ILASERALERT				0x3001D			//
#define  ILASEROUT0					0x3001E			//
#else
#define  ITEMPERATUREFAULT			0x3001C			//�������¶ȱ���
#define  IWATERFLOWPROTECT			0x3001D			//������ˮ������
#define	 ILASERONOK					0x3001E			//�������ϵ�OK
#endif

//  ************** 7200-2********************
#define  I1842_1ERROR				0x40000			//�˶���1����
#define  I1842_2ERROR				0x40001			//�˶���2����			 
#define  ISERVOALARMX				0x40002			//X���ŷ�����			
#define  ISERVOALARMY				0x40003			//Y���ŷ�����			
#define  ISERVOALARMZLEFT			0x40004			//Z1���ŷ�����			 
#define  ISERVOALARMZRIGHT			0x40005			//Z2���ŷ�����			
#define  ISERVOALARMUNBETHOST		0x40006			//G���ŷ�����			
#define  ISERVOALARMUNBETSUB		0x40007			//R���ŷ�����
#define  ILASERGASFLUX				0x40008			//���Ᵽ������������
#define  ISWATERCOOLFAULT			0x40009			//С��ˮ�����ϱ���
#define  IAOMTEMPROTECT				0x4000A			//AOM�¶ȱ�������
#define  IDOORPROTECT				0x4000B			//�Ŷ��䰲ȫ��������
#define  ITABXERROR				    0x4000C			//X���դ�ߴ���
#define  ITABYERROR					0x4000D			//Y���դ�ߴ��� 

#define  ITOPHAT1N					0x40010			//TopHat�л�����1N 
#define  ITOPHAT1P					0x40011			//TopHat�л�����1P
#define  ITOPHAT2N					0x40012			//TopHat�л�����2N
#define  ITOPHAT2P					0x40013			//TopHat�л�����2P
#define  ITHICKNESSERROR1			0x40014			//����դ��1����
#define  ITHICKNESSERROR2			0x40015			//����դ��2����
#define  IRINGLIGHT1ERROR			0x40016			//���ι�1����
#define  IRINGLIGHT2ERROR			0x40017			//���ι�2����

#define  ILENSWINDOW1ERROR			0x4000E			//ɨ�辵������1δ��λ����
#define  ILENSWINDOW2ERROR			0x4000F			//ɨ�辵������2δ��λ����
#define  ITABLECLAMPN				0x40018			//ƽ̨��ǯ����N 
#define  ITABLECLAMPP				0x40019			//ƽ̨��ǯ����P
#define  IDUSTOUT1PRESSURE			0x4001A			//��·�鳾��ѹ
#define  IDUSTOUT2PRESSURE			0x4001B			//��·�鳾��ѹ

#endif	//IO_C

#endif	//NEWE2
/*--------------------------------------------------------------------*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5D77F19A_9685_11D2_899F_0040055A6A93__INCLUDED_)
