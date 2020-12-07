// WarningInfo.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "WarningInfo.h"
#include "OperateControl.h"
#include "SysParameter.h"
#include "MainRunView.h"
#include "stdio.h"
#include "MainFrm.h"
#include "ToolUtil.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////	

//int nWarningCount[200];
CWarningInfo DlgWarning;

typedef map<int, CString, less<int> > WARNINGINFO;
WARNINGINFO WarningMap;

BOOL g_bShowInfo=false;
BOOL bPause=false;
BOOL bDlgOpen=false;
AlarmInfo Alarm;

CString WarningInfo[]=
{
	"总气路气压低",					//0
	"保护气流量报警",               //1
	"冷水机报警",					//2
	"AOM错误报警",					//3
	"激光器报警",                   //4
	"左侧振镜未上电",				//5
	"右侧振镜未上电",				//6
    "左侧振镜温度低",				//7
    "右侧振镜温度低",				//8
    "运动卡1错误报警",				//9
    "运动卡2错误报警",				//10
    "X轴电机伺服报警",				//11
    "Y轴电机伺服报警",				//12
    "Z1轴电机伺服报警",				//13
    "Z2轴电机伺服报警",				//14 
    "BET主动轴伺服报警",			//15
    "BET从动轴伺服报警",			//16
	"电机未上电报警",               //17
    "X轴光栅尺错误",				//18 
    "Y轴光栅尺错误",				//19
    "左测厚光栅尺错误",				//20
	"右测厚光栅尺错误",             //21  
	"左吸尘静压报警",				//22
	"右吸尘静压报警",				//23
	"保护窗1报警",					//24
	"保护窗2报警",					//25
	"门安全保护报警",				//26
	"上下料机械手报警",				//27
	"长光路加工中切换气缸异常",		//28
	"短光路加工中切换气缸异常",		//29
	"加工中左平台真空吸附不够",		//30
	"加工中右平台真空吸附不够",		//31
	"冷水机预报警",					//32
	"激光器2报警",					//33
	"激光器+48V电源报警",			//34
	"光圈轴伺服报警",				//35
	"XY电机使能错误,请检查确认后重新回零",	//36
	"NG料仓已满，请清空",					//37
	"左轴PCB靶孔对位孔误差容许超出",		//38  靶孔对位孔误差容许
	"右轴PCB靶孔对位孔误差容许超出",		//39
	"左轴防呆标靶寻找失败",			//40
	"右轴防呆标靶寻找失败",			//41
	"左平台真空吸附不够",			//42
	"右平台真空吸附不够",			//43
	"平台夹钳未正常关闭",			//44
	"左轴主标靶寻找失败",			//45
	"右轴主标靶寻找失败",			//46
	"左台面线路板涨缩比超差",		//47
	"右台面线路板涨缩比超差",		//48
	"左轴未进行振镜校正",			//49
	"右轴未进行振镜校正",			//50
	"左轴未进行激光功率测试",		//51
	"右轴未进行激光功率测试",		//52
	"左轴内层标靶寻找失败",			//53
	"右轴内层标靶寻找失败",			//54
	"左轴内部标靶寻找失败",			//55
	"右轴内部标靶寻找失败",			//56
	"内部标靶寻找偏差过大",			//57
	"左轴振镜校正参数设定异常",		//58
	"右轴振镜校正参数设定异常",		//59
	"振镜工作超时异常",				//60
	"左台面线路板内层涨缩比超差",	//61
	"右台面线路板内层涨缩比超差",	//62
	"字符定义文件未正常打开",		//63
	"左轴测厚气缸下降未到位",		//64
	"左轴测厚气缸上升未到位",		//65
	"右轴测厚气缸下降未到位",		//66
	"右轴测厚气缸上升未到位",		//67
	"测厚气缸未在安全位置",			//68
	"上料倒料过程出现故障",			//69
	"上料放料过程出现故障",			//70
	"上料撤出过程出现故障",			//71
	"下料过程出现故障",				//72	//20190627	"最后一张板板厚测量偏差过大"
	"左轴板厚测量偏差过大",			//73
	"右轴板厚测量偏差过大",			//74
	"平台夹钳未正常打开",			//75
	"下料准备过程出现故障",			//76
	"下料取料过程出现故障",			//77
	"上料仓无板",					//78
	"左轴振镜点阵校正出现错误",		//79
	"右轴振镜点阵校正出现错误",		//80
	"左轴振镜点阵校正结果不满足要求",		//81
	"右轴振镜点阵校正结果不满足要求",		//82
	"左轴功率测试出现错误",			//83
	"右轴功率测试出现错误",			//84
	"左轴功率测试结果不满足要求",	//85
	"右轴功率测试结果不满足要求",	//86
	"左轴校正板已用满",				//87
	"右轴校正板已用满",				//88
	"左轴校正点图像识别失败",		//89
	"右轴校正点图像识别失败",		//90
	"左轴振镜原点校正出现错误",		//91
	"右轴振镜原点校正出现错误",		//92
	"左轴振镜原点校正结果不满足要求",		//93
	"右轴振镜原点校正结果不满足要求",		//94
	"校正区域有异常点",						//95
	"左轴振镜相邻两次原点校正偏差过大",		//96
	"右轴振镜相邻两次原点校正偏差过大",		//97
	"打开串口失败",					//98
	"写串口失败",					//99
	"读串口失败",					//100
	"激光脉冲输出与计数不相等",		//101
	"激光测厚校验失败",				//102
	"激光器水温报警",				//103
	"激光器水流报警",				//104
	"左侧振镜X轴电机报警",			//105
	"右侧振镜X轴电机报警",			//106
	"左侧振镜Y轴电机报警",			//107
	"右侧振镜Y轴电机报警",			//108
	"CTI振镜系统识别异常",			//109
	"CTI_HEAD_A电机运行异常",		//110
	"CTI_HEAD_B电机运行异常",		//111
	"IO检测电机运行异常",			//112 
	"机械手错误报警",				//113 
	"网络监控激光器VSWR异常",		//114
	"Cognex错误报警",				//115
};

CString WarningInfo_En[]=
{
	"Low air pressure",							//0
	"protect airflow warning",					//1
	"cold water warning",						//2
	"AOM warning",								//3
	"Laser warning",							//4
	"Left CCD is off",							//5
	"right CCD is off",							//6
	"left CCD low temperature",					//7
	"right CCD low temperature",				//8
	"Card1 Warning",							//9
	"Card2 Warning",							//10
	"X motor servo warning",					//11
	"Y motor servo warning",					//12
	"Z1 motor servo warning",					//13
	"Z2 motor servo warning",					//14
	"BET initiative servo warning",				//15
	"BET driven servo warning",					//16
	"motor is off",								//17
	"X grating scale is warning",				//18
	"Y grating scale is warning",				//19
	"left thickness measurement grating scale is error",			//20
	"right thickness measurement grating scale is error",			//21
	"left dust cleaner warning",				//22
	"right dust cleaner warning",				//23
	"protect window1 warning",					//24
	"protect window2 warning",					//25
	"protect door is warning",					//26
	"Loading/unloading robot alarm",			//27
	"switch cylinder alarm when processing for long optical path",	//28 
	"switch cylinder alarm when processing for short optical path ",//29
	"Left table failed to absorb PCB board when processing",		//30
	"Right table failed to absorb PCB board when processing",		//31
	"cold water pro-warning",					//32
	"Laser 2 warning",							//33
	"Laser +48V power error",					//34
	"APT servo warning",						//35
	"An error occurred to XY motor enable, please check and reset the motor!",	//36
	"NG unload is full,please move them out!",									//37
	"Diatance of the left board ERROR",			//38
	"Diatance of the right board ERROR",		//39
	"Failed to find fool-proof target at left",	//40
	"Failed to find fool-proof target at right",//41
	"Left table failed to absorb PCB board",	//42
	"Right table failed to absorb PCB board",	//43
	"Clamp of table can't close",				//44
	"Failed to find main target at left",		//45
	"Failed to find main target at right",		//46
	"Poor expansion-to-contraction ratio of layer of the left board",			//47
	"Poor expansion-to-contraction ratio of layer of the right board",			//48
	"The left head need to carry out galvanometer calibration!",				//49
	"The right head need to carry out galvanometer calibration!",				//50
	"The power of left axis haven't been tested",					//51
	"The power of right axis haven't been tested",					//52
	"Failed to find internal-layer target at left",					//53
	"Failed to find internal-layer target at right",				//54
	"Failed to find internal target at left",						//55
	"Failed to find internal target at right",						//56
	"Position deviation is too great when find internal target",	//57
	"Left galvanometer parameter setting error",					//58
	"Right galvanometer parameter setting error",					//59
	"Galvanometer timed out",										//60
	"Too great expansion-to-contraction ratio of internal layer of the left board",	//61
	"Too great expansion-to-contraction ratio of internal layer of the right board",//62
	"Failed to open the character file",											//63
	"Left thickness measurement cylinder failed to down to its specified place",	//64
	"Left thickness measurement cylinder failed to rise to its specified place",	//65
	"Right thickness measurement cylinder failed to down to its specified place",	//66
	"Right thickness measurement cylinder failed to rise to its specified place",	//67
	"thickness measurement cylinder is not stopped at the safe position",			//68
	"An fault occurred in the process of pouring material",							//69
	"Fault occurred during loading process",						//70
	"Fault occurred during loading arm retracting",					//71
	"Too great thickness measurement deviation of the last board",	//72
	"Too great thickness measurement deviation of the left board",	//73
	"Too great thickness measurement deviation of the right board",	//74
	"Clamp of table can't open",									//75
	"An fault occurred in the process of prepare unloading material",//76
	"An fault occurred in the process of unloading material",		//77
	"No loading material",											//78
	"The left head carry out galvanometer for dot-matrix calibration error",		//79
	"The right head carry out galvanometer for dot-matrix calibration error",		//80
	"The result of dot-matrix calibration for left galvanometer is incompetent",	//81
	"The result of dot-matrix calibration for right galvanometer is incompetent",	//82
	"The left head power test error",								//83
	"The right head power test error",								//84
	"The result of power test for left head is incompetent",		//85
	"The result of power test for right head is incompetent",		//86
	"The left board for calibration is full used",					//87
	"The right board for calibration is full used",					//88
	"Image recognition of calibration point failed at left",		//89
	"Image recognition of calibration point failed at right",		//90
	"Left-axis galvanometer origin calibration error",				//91
	"Right-axis galvanometer origin calibration error",				//92
	"The result of left-axis galvanometer origin calibration is incompetent",			//93
	"The result of right-axis galvanometer origin calibration is incompetent",			//94
	"Abnormal points are present in the calibration area",								//95
	"Position deviation is too great during left-axis galvanometer origin calibration",	//96
	"Position deviation is too great during right-axis galvanometer origin calibration",//97
	"Open serial port error",										//98
	"Write serial port error",										//99
	"Read serial port error",										//100
	"The laser pulse output count error",							//101
	"Laser thickness measurement checkout error",					//102
	"Laser water temperature alarm",								//103
	"Laser water flow alarm",										//104
	"X-Axis of left CCD is error",									//105
	"X-Axis of right CCD is error",									//106
	"Y-Axis of left CCD is error",									//107
	"Y-Axis of right CCD is error",									//108
	"CTI System is error",											//109
	"CTI_HEAD_A motor is error",									//110
	"CTI_HEAD_B motor is error",									//111
	"IO about CTI motor is error",									//112
	"Manipulator Error",											//113
	"VSWR Error from Socet",										//114 Conherent Laser 
	"Cognex Error",													//115
};

UINT ThreadProcAlarmReport(LPVOID pParam);

void SaveWarningInfo(int nIndex,BOOL bStatus)
{
	if((nIndex<0)||(nIndex>115))
		return;

	WARNINGINFO::iterator theIterator;
	theIterator = WarningMap.find(nIndex);
	
	if(theIterator != WarningMap.end())				//已经存在于报警序列里
	{
		//if(!bStatus)								//报警已消除
			//WarningMap.erase(theIterator);
		//else										//报警未消除则不如入map缓存
		//{
			return;
		//}
	}
	else											//新的报警
	{
		if(bStatus)
		{
			if(GetLang().GetCurLanguage()==0)
				WarningMap.insert(WARNINGINFO::value_type(nIndex,WarningInfo[nIndex]));
			else if(GetLang().GetCurLanguage()==1)
				WarningMap.insert(WARNINGINFO::value_type(nIndex,WarningInfo_En[nIndex]));
            g_bShowInfo = TRUE;
			Alarm.alarmId = nIndex;
			Alarm.alarmType = "S";
			AfxBeginThread(ThreadProcAlarmReport,&Alarm,0,0,0,NULL);
			Sleep(50);
		}
	}
}

UINT ThreadProcAlarmReport(LPVOID pParam)
{
	AlarmInfo *palarmInfo = (AlarmInfo *)pParam;
	DlgWarning.AlarmReport(palarmInfo->alarmId,palarmInfo->alarmType);
	return 0;
}


/*
void  SaveWarningInfo(int nIndex,BOOL bStatus)
{
	if((nIndex<0)||(nIndex>115))
		return;
	
	WARNINGINFO::iterator theIterator;
	theIterator = WarningMap.find(nIndex);
	if(theIterator != WarningMap.end())				//已经存在于报警序列里
	{
		return;
	}
	
	if(bStatus)											//实时报警
	{
		if(GetLang().GetCurLanguage()==0)
			WarningMap.insert(WARNINGINFO::value_type(nIndex,WarningInfo[nIndex]));
		else if(GetLang().GetCurLanguage()==1)
			WarningMap.insert(WARNINGINFO::value_type(nIndex,WarningInfo_En[nIndex]));
		
		g_bShowInfo = TRUE;
	}
	
	
	//	else
	//	{
	//		WARNINGINFO::iterator theIterator;
	//		theIterator = WarningMap.find(nIndex);
	//		
	//		if(theIterator != WarningMap.end())				//已经存在于报警序列里
	//		{
	//			if(!bStatus)								//实时消除报警
	//				WarningMap.erase(theIterator);
	//		}
	//	}
}*/

VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) 
{
//	WarningMap.clear();									//清除所有报警

//	for(int i=0;i<115;i++)
//	{
//		if ((i<40)||(i>109))
//			SaveWarningInfo(i,false);		
//	}
	
	if (GetDoc().GetTimeAnalyse())				//实际加工用时记录与统计
	{
		if (GetControl().GetRunState()==CControl::END)
		{
			GetLog().AppendTimeAnalyer(GetDoc().GetBeginTimeAnalyse(),COleDateTime::GetCurrentTime(),
										(int)((GetTickCount()-GetDoc().GetCalculateBeginTime())/1000.0));		
			GetDoc().SetTimeAnalyse(FALSE);
		}
	}
	
#ifndef LESSWARN
	
#ifdef USEIOCARD
	
	if(GetControl().GetRunState()==CControl::RUN)								//机器运行时
	{
		if(GetDoc().GetAxisIsRun(0))											//20180821
			SaveWarningInfo(30,(!GetControl().QueryIOBit(ITABLTVACUMM)));		//加工中左平台真空吸附实时监测
		
		if(GetDoc().GetAxisIsRun(1))
			SaveWarningInfo(31,(!GetControl().QueryIOBit(ITABRTVACUMM)));		//加工中右平台真空吸附实时监测

		if(GetControl().GetDoorWarning())
		{			
			GetControl().SetRunState(CControl::PAUSE);
			
			if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
			{
				if(GetDoc().GetUse9112())
					GetControl().ChannelOutput(STOPMOVE,MIO_ON);
				else
					GetControl().SetCOMOutput(10);				//机械手暂停  o正向：10，	i逆向：10

//				GetControl().SetHandPause(TRUE);				//标记手臂有暂停动作，避免在暂停时上下料过程中出现超时报警。
			}
			
			SaveWarningInfo(26,true);							// "门安全保护报警"
		}
	}
/*
	if(GetControl().GetRunState()==CControl::OPERATE)			//20190722 增加
	{
		if(GetControl().GetDoorWarning())
		{			
			GetControl().SetRunState(CControl::OPERATEPAUSE);
			
			SaveWarningInfo(26,true);							// "门安全保护报警"
		}
	}
*/
	if(GetControl().GetRunState()==CControl::OPERATEWITHHAND)	//20190723 增加
	{
		if(GetControl().GetDoorWarning())
		{			
			GetControl().SetRunState(CControl::OPERATEWITHHANDPAUSE);
			
			if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
			{
				if(GetDoc().GetUse9112())
					GetControl().ChannelOutput(STOPMOVE,MIO_ON);
				else
					GetControl().SetCOMOutput(10);				//机械手暂停  o正向：10，	i逆向：10
			}
			
			SaveWarningInfo(26,true);							// "门安全保护报警"
		}
	}
	
	if(GetControl().GetRunState()==CControl::PAUSE)
	{
		if((!GetControl().GetDoorWarning(0))&&(!bDlgOpen))
		{
			GetControl().SetRunState(CControl::RUN);
			
			if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
			{			
				if(GetDoc().GetUse9112())
					GetControl().ChannelOutput(STOPMOVE,MIO_OFF);
				else
					GetControl().SetCOMOutput(11);				//机械手暂停复位  o正向：11，	i逆向：11

//				GetControl().SetHandPause(FALSE);
			}	
		}
	}
/*
	if(GetControl().GetRunState()==CControl::OPERATEPAUSE)		//20190722 增加
	{
		if((!GetControl().GetDoorWarning(0))&&(!bDlgOpen))
		{
			GetControl().SetRunState(CControl::OPERATE);	
		}
	}
*/
	if(GetControl().GetRunState()==CControl::OPERATEWITHHANDPAUSE)	//20190723 增加
	{
		if((!GetControl().GetDoorWarning(0))&&(!bDlgOpen))
		{
			GetControl().SetRunState(CControl::OPERATEWITHHAND);
			
			if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
			{			
				if(GetDoc().GetUse9112())
					GetControl().ChannelOutput(STOPMOVE,MIO_OFF);
				else
					GetControl().SetCOMOutput(11);				//机械手暂停复位  o正向：11，	i逆向：11
			}	
		}
	}
/*																					//20190723 删除
	if(GetDoc().GetProcessState()==SystemDoc::AUTOPROC)
	{
		if(GetControl().GetRunState()==CControl::RUN)								//上下料运行时
		{	
			if(!GetDoc().GetWarner())
			{
				if(GetDoc().GetUse9112())
				{
					SaveWarningInfo(27,!GetControl().QueryIOBit(IALARM));			// "上下料机械手报警"
					SaveWarningInfo(37,!GetControl().QueryIOBit(IONGFULLALARM));	// "NG料仓已满，请清空"
				}
//				else										//20190718 修改
//				{
//					SaveWarningInfo(27,GetControl().QueryCOMInput(24,1));			// "上下料机械手报警"	20180913
//					SaveWarningInfo(27,GetControl().QueryCOMInput(28,1));			// "上下料机械手报警"
//					SaveWarningInfo(37,GetControl().QueryCOMInput(26,1));			// "NG料仓已满，请清空"	20161123	
//				}		
			}	
		}
	}
*/
	if(!GetDoc().GetFault())
	{			
		SaveWarningInfo(0,(GetControl().QueryIOBit(IAIRPRESSURE)));					// "总气路气压低"
		
		if(GetDoc().GetLaserPowerState())		//激光器在上电状态下才对相关报警进行监测
		{
			SaveWarningInfo(1,(!GetControl().QueryIOBit(ILASERGASFLUX)));			// "保护气流量报警"
			SaveWarningInfo(22,(!GetControl().QueryIOBit(IDUSTOUT1PRESSURE))&&(GetControl().GetRunState()==CControl::RUN));	// "左吸尘静压报警"
			SaveWarningInfo(23,(!GetControl().QueryIOBit(IDUSTOUT2PRESSURE))&&(GetControl().GetRunState()==CControl::RUN));	// "右吸尘静压报警"	

#ifdef AOMTYPE
			SaveWarningInfo(3,(!GetControl().QueryIOBit(IAOMTEMPROTECT)));			// "AOM错误报警"
	#ifdef HUAWEILASERSOURCE
			SaveWarningInfo(34,GetControl().QueryIOBit(ILASERWARMUPP));				// "激光器+48V电源报警"
	#endif
#endif
/*
#ifdef IO_LASERONOK_HIGH
			SaveWarningInfo(4,(!GetControl().QueryIOBit(ILASERONOK)));				// "激光器1报警"
#else
			SaveWarningInfo(4,(GetControl().QueryIOBit(ILASERONOK)));				// "激光器1报警"
#endif
#ifdef DOUBLELASER
			SaveWarningInfo(33,(!GetControl().QueryIOBit(LASEROK2)));				// "激光器2报警"
			SaveWarningInfo(34,GetControl().QueryIOBit(ILASERWARMUPP));				// "激光器+48V电源报警"
#endif
*/
#ifdef DOUBLELASER																	//20191015	
			if((GetDoc().GetProcAxisMode()==0)||(GetDoc().GetProcAxisMode()==1))
				SaveWarningInfo(4,(!GetControl().QueryIOBit(ILASERONOK)));			// "激光器1报警"
			if((GetDoc().GetProcAxisMode()==0)||(GetDoc().GetProcAxisMode()==2))
				SaveWarningInfo(33,(!GetControl().QueryIOBit(LASEROK2)));			// "激光器2报警"
			
			SaveWarningInfo(34,GetControl().QueryIOBit(ILASERWARMUPP));				// "激光器+48V电源报警"
#else
	#ifdef IO_LASERONOK_HIGH
			SaveWarningInfo(4,(!GetControl().QueryIOBit(ILASERONOK)));				// "激光器报警"
	#else
			SaveWarningInfo(4,(GetControl().QueryIOBit(ILASERONOK)));
	#endif
#endif

#ifdef IO_C
			SaveWarningInfo(2,(!GetControl().QueryIOBit(ISWATERCOOLFAULT)));												// "冷水机报警"	//HIKAGV test
			SaveWarningInfo(24,(!GetControl().QueryIOBit(ILENSWINDOW1ERROR))&&(GetControl().GetRunState()==CControl::RUN));	// "保护窗1报警"
			SaveWarningInfo(25,(!GetControl().QueryIOBit(ILENSWINDOW2ERROR))&&(GetControl().GetRunState()==CControl::RUN));	// "保护窗2报警"
			if(GetDoc().GetWaterYBJ())
				SaveWarningInfo(32,(GetControl().QueryIOBit(ISWATERFAULT)));												// "冷水机预报警"
#else
			SaveWarningInfo(2,(GetControl().QueryIOBit(ISWATERCOOLFAULT)));													// "冷水机报警"
			SaveWarningInfo(24,(GetControl().QueryIOBit(ILENSWINDOW1ERROR))&&(GetControl().GetRunState()==CControl::RUN));	// "保护窗1报警"
			SaveWarningInfo(25,(GetControl().QueryIOBit(ILENSWINDOW2ERROR))&&(GetControl().GetRunState()==CControl::RUN));	// "保护窗2报警"
#endif				
		}
	}

 	if (GetDoc().GetLaserWarning())
		SaveWarningInfo(114,TRUE);													// "网络监控激光器VSWR异常"

#endif
	
#ifdef USESCANLAB

	if(!GetDoc().GetFault())
	{	
#ifndef CTI
//		SaveWarningInfo(5,(!GalvoStatus(1)));										// "左侧振镜上电或温度异常"
//		SaveWarningInfo(6,(!GalvoStatus(2)));										// "右侧振镜上电或温度异常"

		if((GetDoc().GetProcAxisMode()==0)||(GetDoc().GetProcAxisMode()==1))		//20191015
			SaveWarningInfo(5,(!GalvoStatus(1)));									// "左侧振镜上电或温度异常"
		if((GetDoc().GetProcAxisMode()==0)||(GetDoc().GetProcAxisMode()==2))
			SaveWarningInfo(6,(!GalvoStatus(2)));									// "右侧振镜上电或温度异常"
#else
		SaveWarningInfo(112,(!GetControl().QueryIOBit(ICTIOK)));					// "IO检测电机运行异常"
#endif
	}	

#endif

#ifdef USEMOTION
#ifndef USEDMSYSTEM											//20190507
	if(!GetDoc().GetFault())
	{	
		if(GetDoc().GetMachinePowerState())					//在机器上电后才对相关报警进行监测		//20181129		
		{
#ifndef NEWE2			
			SaveWarningInfo(9,(!GetControl().QueryIOBit(I1842_1ERROR)));            // "运动卡1错误报警"
			SaveWarningInfo(10,(!GetControl().QueryIOBit(I1842_2ERROR)));           // "运动卡2错误报警"

			SaveWarningInfo(15,(!GetControl().QueryIOBit(ISERVOALARMUNBETHOST)));   // "BET主动轴伺服报警"
			SaveWarningInfo(16,(!GetControl().QueryIOBit(ISERVOALARMUNBETSUB)));	// "BET从动轴伺服报警"
#endif
			SaveWarningInfo(17,(GetControl().QueryIOBit(MOTIONSTOPRESET)));			// "电机未上电报警"
			SaveWarningInfo(11,(!GetControl().QueryIOBit(ISERVOALARMX)));			// "X轴电机伺服报警"
			SaveWarningInfo(12,(!GetControl().QueryIOBit(ISERVOALARMY)));			// "Y轴电机伺服报警"
			SaveWarningInfo(13,(!GetControl().QueryIOBit(ISERVOALARMZLEFT)));		// "Z1轴电机伺服报警"
			SaveWarningInfo(14,(!GetControl().QueryIOBit(ISERVOALARMZRIGHT)));		// "Z2轴电机伺服报警"
#ifdef F2TYPE
			SaveWarningInfo(15,(!GetControl().QueryIOBit(ISERVOALARMUNBETHOST1)));  // "BET主动轴伺服报警"
			SaveWarningInfo(16,(!GetControl().QueryIOBit(ISERVOALARMUNBETSUB1)));	// "BET从动轴伺服报警"
			SaveWarningInfo(35,(!GetControl().QueryIOBit(ISERVOALARMAPT)));			// "光圈轴伺服报警"
			SaveWarningInfo(35,(!GetControl().QueryIOBit(ISERVOALARMAPT1)));		// "光圈轴伺服报警"
#endif
		}
		
//		SaveWarningInfo(18,(!GetControl().QueryIOBit(ITABXERROR)));					// "X轴光栅尺错误"
//		SaveWarningInfo(19,(!GetControl().QueryIOBit(ITABYERROR)));					// "Y轴光栅尺错误"

//		if(GetDoc().GetMotorState())			//在机器回零后才对电机使能进行监测
//			SaveWarningInfo(36,(GetMotion().GetMationSH(AXISTABX))||(GetMotion().GetMationSH(AXISTABY)));// "XY电机使能错误"
	}
#endif
#endif

	if(g_bShowInfo&&!bDlgOpen)
	{
		bDlgOpen=true;
		DlgWarning.DoModal();
	}
	
#endif
}

VOID CALLBACK TimerProc1(  HWND hwnd,   UINT uMsg,    UINT idEvent,  DWORD dwTime) 
{
	if((GetControl().GetRunState()==CControl::END)&&(!bDlgOpen))	
		GetDoc().SetFault(false);
}

void IsWarning()
{
/*
	if(GetDoc().GetLastWarningNo()!=-1)
	{
		SaveWarningInfo(GetDoc().GetLastWarningNo(),true);
			
		if(g_bShowInfo&&!bDlgOpen)
		{
			bDlgOpen=true;
			DlgWarning.DoModal();
		}
	}
*/
	SaveWarningInfo(GetDoc().GetLastWarningNo(),true);
	
	if(g_bShowInfo&&!bDlgOpen)
	{
		bDlgOpen=true;
		DlgWarning.DoModal();
	}
}

CWarningInfo::CWarningInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CWarningInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarningInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CWarningInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarningInfo)
	DDX_Control(pDX, IDC_LIST_WARNINGINFO, m_listWarning);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWarningInfo, CDialog)
	//{{AFX_MSG_MAP(CWarningInfo)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarningInfo message handlers

void CWarningInfo::OnOK() 
{
// TODO: Add extra validation here
//	if(GetControl().GetRunState()==CControl::RUN)				//机器运行时
	if((GetControl().GetRunState()==CControl::RUN)||(GetControl().GetRunState()==CControl::PAUSE))		//20181106
		GetControl().SetLampStatus(CControl::ORDER);
	else
		GetControl().SetLampStatus(CControl::WARN);
	
	GetControl().ChannelOutput(OCOMMONALARM,IO_OFF);
	
	//	if(GetDoc().GetLastWarningNo()!=-1)
	//	{
	//		for(int i=40;i<110;i++)
	//		{
	//			SaveWarningInfo(i,false);
	//		}
	//
	//		GetDoc().SetLastWarningNo(-1);
	//	}
	
	GetDoc().SetLaserWarning(FALSE);

	WARNINGINFO::iterator theIterator;

	for(theIterator=WarningMap.begin();theIterator != WarningMap.end();  ++theIterator)
	{
		Alarm.alarmId = theIterator->first;
		Alarm.alarmType = "R";
		AfxBeginThread(ThreadProcAlarmReport,&Alarm,0,0,0,NULL);
		Sleep(50);
	}

	WarningMap.clear();	//清除所有报警
	GetDoc().SetLastAlarmId(0);
	g_bShowInfo=false;
	bDlgOpen=false;
	CDialog::OnOK();
}

//告警上报/解除
void CWarningInfo::AlarmReport(int alarmIndex,CString &alarmType)
{
	bool HandFail=false;
	bool HostFail=false;
	
	if ((alarmIndex<38)||(alarmIndex>109))					//0-38 109-115属于机器故障，其他的是工艺过程异常
	{
		if(alarmIndex!=26)									//排除门保护报警
		{
			if((alarmIndex==27)||(alarmIndex==37))			//机械手故障报警
			{
				HandFail=true;	
			}
			else											
			{
				HostFail=true;	
			}
		}	
	}

	//主机故障报警，此时机器须停止加工
	if (alarmType.Compare("S")==0 && HostFail)  
	{
		GetLog().AppendSNOtherStatusTable("故障状态",COleDateTime::GetCurrentTime());
		GetDoc().SetLastAlarmId(alarmIndex);
	}

	bool result = false;
	int times = 0;
	int errCode;
	
	Request req;
	Response rsp;
	CString uuid  = req.UuidGenerator();
	
	time_t timep;
	time(&timep);
	char currentTime[64];
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	CString failedDataBackup = GetDoc().GetAppPath()+"info\\"+"AlarmReport.txt";
	
	CString machineSn = GetDoc().GetSysMachineSn();
	CString imesURL = GetDoc().GetSysImesURL();
	int timeout = GetDoc().GetSysTimeout();
	
	Json::Value reqSetting;
	reqSetting["ImesURL"] = Json::Value(imesURL);
	reqSetting["Timeout"] = Json::Value(timeout);
	req.setReqSetting(reqSetting);
	
	Json::Value reqHead;
	reqHead["eqp_id"] = Json::Value(machineSn);
	reqHead["time_stamp"] = Json::Value(currentTime);
	reqHead["trx_id"] = Json::Value(uuid);
	req.setReqHead(reqHead);
	
	Json::Value reqBody;
	reqBody["report_dt"] = Json::Value(currentTime);
	reqBody["keep_reason"] = Json::Value("0");

	reqBody["alarm_type"] = Json::Value(alarmType);
	if (HostFail)
	{
		reqBody["alarm_code"] = Json::Value("A");
	}
	else
	{
		reqBody["alarm_code"] = Json::Value("W");
	}
	CString alarmid;
	alarmid.Format("%0.4d",alarmIndex);
	CString remarks;
	remarks.Format("%s_%s",alarmid,alarmType);
	if (alarmIndex<0)
	{
		reqBody["alarm_id"] = Json::Value("0000");
	}
	else
	{
		reqBody["alarm_id"] = Json::Value(alarmid);
	}
	CString alarmDesc;
	if ((alarmIndex>=0 && alarmIndex<=116))
	{
		 alarmDesc = ToolUtil::GbkToUtf8(WarningInfo[alarmIndex]);
	}
	TRACE("alarmDesc = %s \n",alarmDesc);
	reqBody["alarm_desc"] = Json::Value(alarmDesc);
	req.setReqBody(reqBody);
	
	GetMainFrame().cs_alarm.Lock();
	fstream file;
	streampos fp;
	file.open(failedDataBackup,ios::in);
	if (file.is_open())
	{
		file.seekg(0,ios::end);
		fp = file.tellg();
	}
	file.close();
	GetMainFrame().cs_alarm.Unlock();
	if (!GetDoc().GetSysModeSwitch() || (int(fp) != 0))//离线模式
	{
		if((int(fp) != 0) && GetDoc().GetSysModeSwitch())
		{
			reqBody["keep_reason"] = Json::Value("0");
		}
		else
		{
			reqBody["keep_reason"] = Json::Value("1");
		}
		req.setReqBody(reqBody);
		CString reqAndRsp;
		Json::FastWriter fast_writer;
		reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
			fast_writer.write(req.getReqHead()).c_str(),\
			fast_writer.write(req.getReqBody()).c_str());
		GetMainFrame().cs_alarm.Lock();
		GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
		GetMainFrame().cs_alarm.Unlock();
	}
	else
	{
		for (int i=0; i<3; i++)
		{
			errCode = GetWSInterfaceImplementor().AlarmReport(req, rsp);
			if (errCode == STS_OK)
			{
				result = true;
				times = 0;
				break;
			}
			else
			{
				times ++;
				CString tips;
				tips.Format("报警重传中,次数:%d,时间:%s",times,currentTime);
				::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
				result = false;
				continue;
			}
		}
		if (result)
		{
			CString tips;
			tips.Format("报警上传成功,时间:%s",currentTime);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
		}
		else
		{
			CString tips;
			CString reason;
			if(!rsp.getRspHead()["rtn_msg"].isNull())
				reason = rsp.getRspHead()["rtn_msg"].asCString();
			else
				reason = StringOfBaseStatus[errCode].pString;
			tips.Format("报警上传失败,原因:%s,时间:%s",reason,currentTime);
			GetLog().Append_pro(reason,"报警上传",remarks);
			::SendMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_USERUPDATESTATUSBAR,(WPARAM)(LPSTR)(LPCTSTR)tips,(LPARAM)0);
			
			reqBody["keep_reason"] = Json::Value("2");
			req.setReqBody(reqBody);
			CString reqAndRsp;
			Json::FastWriter fast_writer;
			reqAndRsp.Format("{\"requestHead\":%s,\"requestBody\":%s};",\
				fast_writer.write(req.getReqHead()).c_str(),\
				fast_writer.write(req.getReqBody()).c_str());
			GetMainFrame().cs_alarm.Lock();
			GetInfo().SaveToFile(failedDataBackup,"%s\n",reqAndRsp);
			GetMainFrame().cs_alarm.Unlock();
		}
	}
}

/*
void CWarningInfo::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	WARNINGINFO::iterator theIterator;
	bool HandFail=false;
	bool HostFail=false;
	
	// TODO: Add your message handler code here
	if(bShow)
	{
		if(GetControl().GetRunState()==CControl::RUN)			//机器运行时？
		{
			HandFail=false;
			HostFail=false;
			
			for(theIterator=WarningMap.begin();theIterator != WarningMap.end();  ++theIterator)
			{
				if ((theIterator->first<38)||(theIterator->first>109))					//机器故障，其他的是工艺过程异常
				{
					if(theIterator->first!=26)											//排除门保护报警
					{
						if((theIterator->first==27)||(theIterator->first==37))			//机械手故障报警
						{
							HandFail=true;	
						}
						else															//主机故障报警，此时机器须停止加工
						{
							HostFail=true;	
							GetDoc().SetFault(true);
							break;
						}
					}	
				}
			}

			if(HandFail&&(!HostFail))
				GetDoc().SetWarner(true);
		}
//		else
//			GetDoc().SetFault(true);

		if ((GetDoc().GetMachinePowerState())&&GetControl().QueryIOBit(MOTIONSTOPRESET))
		{
			GetMotion().ResetCard(0);
			GetMotion().ResetCard(1);
//#ifdef DOUBLEBET
//			GetMotion().ResetCard(2);
//#endif
#ifndef USEDMSYSTEM													//20190507
#ifdef DOUBLEBET
			GetMotion().ResetCard(2);
#endif
#endif
			GetDoc().SetMachinePowerState(FALSE);
			GetDoc().SetMotorState(FALSE);
			GetDoc().SetCurAptNo(0);
		}

		GetControl().SetLampStatus(CControl::ERR);
		GetControl().ChannelOutput(OCOMMONALARM,IO_ON);
		
		m_listWarning.ResetContent(); 
		
		for(theIterator=WarningMap.begin();theIterator != WarningMap.end();  ++theIterator)
		{
			m_listWarning.AddString (theIterator->second);
#ifdef USELOG
			GetLog().Append_pro(theIterator->second,20167);//"报警"												
			GetLog().AppendSNAlarmTable(theIterator->second,COleDateTime::GetCurrentTime());		//20160901
#endif 			
		}		
	}	
}
*/
void CWarningInfo::OnShowWindow(BOOL bShow, UINT nStatus)												//20190723 重写
{
	CDialog::OnShowWindow(bShow, nStatus);

	WARNINGINFO::iterator theIterator;
	
	// TODO: Add your message handler code here
	if(bShow)
	{
		if((GetControl().GetRunState()==CControl::RUN)||(GetControl().GetRunState()==CControl::OPERATE)||(GetControl().GetRunState()==CControl::OPERATEWITHHAND))
		{	
			for(theIterator=WarningMap.begin();theIterator != WarningMap.end();  ++theIterator)
			{
				if ((theIterator->first<38)||(theIterator->first>109))									//机器故障，其他的是工艺过程异常
				{
					if((theIterator->first!=26)&&(theIterator->first!=27)&&(theIterator->first!=37))	//排除门保护报警和机械手故障报警
					{	
						GetDoc().SetFault(true);
						break;
					}	
				}
			}
		}

		if ((GetDoc().GetMachinePowerState())&&GetControl().QueryIOBit(MOTIONSTOPRESET))
		{
			GetMotion().ResetCard(0);
			GetMotion().ResetCard(1);
//#ifdef DOUBLEBET
//			GetMotion().ResetCard(2);
//#endif
#ifndef USEDMSYSTEM													//20190507
#ifdef DOUBLEBET
			GetMotion().ResetCard(2);
#endif
#endif
			GetDoc().SetMachinePowerState(FALSE);
			GetDoc().SetMotorState(FALSE);
			GetDoc().SetCurAptNo(0);
		}

		GetControl().SetLampStatus(CControl::ERR);
		GetControl().ChannelOutput(OCOMMONALARM,IO_ON);
		
		m_listWarning.ResetContent(); 
		
		for(theIterator=WarningMap.begin();theIterator != WarningMap.end();  ++theIterator)
		{
			m_listWarning.AddString (theIterator->second);
#ifdef USELOG
			GetLog().Append_pro(theIterator->second,20167);//"报警"												
			GetLog().AppendSNAlarmTable(theIterator->second,COleDateTime::GetCurrentTime());		//20160901
#endif 			
		}		
	}	
}

BOOL CWarningInfo::PreTranslateMessage(MSG* pMsg) 
{
// TODO: Add your specialized code here and/or call the base class

	//按下enter键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnOK();
		return TRUE;
	}

	//按下esc键
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		OnOK();
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////add 20110301
CLangControl::CLangControl()
{
	m_nIDLan = 0;

	memset(m_tszUiTxtPath,0,sizeof(m_tszUiTxtPath));
	memset(m_tszErrTxtPath,0,sizeof(m_tszErrTxtPath));
	memset(m_tszLogTxtPath,0,sizeof(m_tszLogTxtPath));
}

CLangControl::~CLangControl()
{

}

CLangControl& GetLang()
{
	static CLangControl  LangControl;
	return LangControl;
}

int CLangControl::Init()
{
	CIniFile IniFile;
	CString str,path;
	long temp;

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\VersionPara");
	IniFile.SetPath(path); 

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		if(!IniFile.GetItemInt("UI",	 "Language",  temp))			
			temp = 0;

		IniFile.CloseIniFile();
	}
	else
		return 0;

	m_nIDLan=temp;

	if (m_nIDLan)
	{
		sprintf(m_tszUiTxtPath,"%sparam\\Text\\UIText_en.txt",path);
//		sprintf(m_tszErrTxtPath,"%sparam\\Text\\Errors_en.txt",path);
		sprintf(m_tszErrTxtPath,"param\\Text\\Errors_en");
//		sprintf(m_tszLogTxtPath,"%sparam\\Text\\LogText_en.txt",path);
		sprintf(m_tszLogTxtPath,"param\\Text\\LogText_en");
	}
	else
	{
		sprintf(m_tszUiTxtPath,"%sparam\\Text\\UIText_chn.txt",path);
//		sprintf(m_tszErrTxtPath,"%sparam\\Text\\Errors_chn.txt",path);
		sprintf(m_tszErrTxtPath,"param\\Text\\Errors_chn");
//		sprintf(m_tszLogTxtPath,"%sparam\\Text\\LogText_chn.txt",path);
		sprintf(m_tszLogTxtPath,"param\\Text\\LogText_chn");
	}

	if(!LoadLogText())
		return 0;

	if(!LoadWarningText())
		return 0;

	return 1;
}

int CLangControl::GetCurLanguage()
{
	return m_nIDLan;
}

void getstrzh(char* str1,char* str)//将读取的转行字符'\''n'转换为'\n'
{
	char* p=str;
	int len = strlen(str);
	for(int i=0;i<len-1;i++)
	{
		p=str+i;
		if((*p=='\\')&& (*(p+1)=='n'))
		{
			i++;
			strcat(str1,"\n");
		}
		else
			strncat(str1,p,1);		
	}
	strncat(str1,str+i,1);
	int x= strlen(str1);
	str1[x]='\0';
	
	return ;
}

int CLangControl::GetUIText(LPCTSTR lpApp,LPCTSTR lpKey,LPTSTR lpBuf,DWORD dwSize)
{
	return GetPrivateProfileString(lpApp,lpKey,_T(""),lpBuf,dwSize,m_tszUiTxtPath);
}

char* CLangControl::GetWarningText(int ErrNo)
{
/*
	char szRead[256] = {""};
	char szRead1[256] = {""};
	char Err[5] = {""};

	itoa(ErrNo,Err,10);
	GetPrivateProfileString("Message",Err,_T(""),szRead1,256,m_tszErrTxtPath);
	getstrzh(szRead,szRead1);

	return szRead;
*/
	CString str;
	char szRead[256] = {""};
	char szRead1[256] = {""};
	int label=ErrNo/1000;

	switch(label)
	{
	case 10:
		str=m_strWarningText10[ErrNo-10001];
		break;
	case 11:
		str=m_strWarningText11[ErrNo-11001];
		break;
	case 12:
		str=m_strWarningText12[ErrNo-12001];
		break;
	case 13:
		str=m_strWarningText13[ErrNo-13001];
		break;
	case 14:
		str=m_strWarningText14[ErrNo-14001];
		break;
	case 21:
		str=m_strWarningText21[ErrNo-21001];
		break;
	case 22:
		str=m_strWarningText22[ErrNo-22001];
		break;
	case 23:
		str=m_strWarningText23[ErrNo-23001];
		break;
	case 31:
		str=m_strWarningText31[ErrNo-31001];
		break;
	case 32:
		str=m_strWarningText32[ErrNo-32001];
		break;
	case 41:
		str=m_strWarningText41[ErrNo-41001];
		break;
	case 42:
		str=m_strWarningText42[ErrNo-42001];
		break;
	}

	sprintf(szRead1,"%s",str);
	getstrzh(szRead,szRead1);

	return szRead;
}

char* CLangControl::GetLogText(LPCSTR lpApp,int ErrNo)
{
/*
	char szRead[256] = {""};
	char Err[5] = {""};

	itoa(ErrNo,Err,10);
	GetPrivateProfileString(lpApp,Err,_T(""),szRead,256,m_tszLogTxtPath);

	return szRead;
*/
	CString str;
	char szRead[256] = {""};
	int label=ErrNo/1000;

	if(label==10)
		str=m_strLogText10[ErrNo-10001];

	if(label==20)
		str=m_strLogText20[ErrNo-20001];

	if(label==30)
		str=m_strLogText30[ErrNo-30001];

	sprintf(szRead,"%s",str);

	return szRead;
}

BOOL CLangControl::LoadLogText()
{
	CIniFile IniFile;
	CString str,path;

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName(m_tszLogTxtPath);
	IniFile.SetPath(path);       

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		int i;
		CString message;

		for(i=0;i<120;i++)
		{
			message.Format("%d",10001+i);
			if(!IniFile.GetItemString("operation",message,m_strLogText10[i]))		
				m_strLogText10[i] = "";
		}

		for(i=0;i<180;i++)
		{
			message.Format("%d",20001+i);
			if(!IniFile.GetItemString("prompt",message,m_strLogText20[i]))		
				m_strLogText20[i] = "";
		}

		for(i=0;i<10;i++)
		{
			message.Format("%d",30001+i);
			if(!IniFile.GetItemString("remark",message,m_strLogText30[i]))		
				m_strLogText30[i] = "";
		}

		IniFile.CloseIniFile();	
	}
	else
	{
		AfxMessageBox("语言信息导入失败！");
		return false;
	}

	return TRUE;
}

BOOL CLangControl::LoadWarningText()
{
	CIniFile IniFile;
	CString str,path;

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName(m_tszErrTxtPath);
	IniFile.SetPath(path);       

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		int i;
		CString message;

		for(i=0;i<200;i++)
		{
			message.Format("%d",10001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText10[i]))		
				m_strWarningText10[i] = "";
		}

		for(i=0;i<40;i++)
		{
			message.Format("%d",11001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText11[i]))		
				m_strWarningText11[i] = "";
		}

		for(i=0;i<20;i++)
		{
			message.Format("%d",12001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText12[i]))		
				m_strWarningText12[i] = "";
		}

		for(i=0;i<40;i++)
		{
			message.Format("%d",13001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText13[i]))		
				m_strWarningText13[i] = "";
		}

		for(i=0;i<125;i++)
		{
			message.Format("%d",14001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText14[i]))		
				m_strWarningText14[i] = "";
		}

		for(i=0;i<120;i++)
		{
			message.Format("%d",21001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText21[i]))		
				m_strWarningText21[i] = "";
		}

		for(i=0;i<60;i++)
		{
			message.Format("%d",22001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText22[i]))		
				m_strWarningText22[i] = "";
		}

		for(i=0;i<20;i++)
		{
			message.Format("%d",23001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText23[i]))		
				m_strWarningText23[i] = "";
		}

		for(i=0;i<50;i++)
		{
			message.Format("%d",31001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText31[i]))		
				m_strWarningText31[i] = "";
		}

		for(i=0;i<20;i++)
		{
			message.Format("%d",32001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText32[i]))		
				m_strWarningText32[i] = "";
		}

		for(i=0;i<50;i++)
		{
			message.Format("%d",41001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText41[i]))		
				m_strWarningText41[i] = "";
		}

		for(i=0;i<20;i++)
		{
			message.Format("%d",42001+i);
			if(!IniFile.GetItemString("Message",message,m_strWarningText42[i]))		
				m_strWarningText42[i] = "";
		}

		IniFile.CloseIniFile();	
	}
	else
	{
		AfxMessageBox("语言信息导入失败！");
		return false;
	}

	return TRUE;
}
