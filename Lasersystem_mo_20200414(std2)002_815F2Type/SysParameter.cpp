// SysParameter.cpp: implementation of the SysParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include "SysParameter.h"
#include "assert.h"
#include "registry.h"
#include "ToolParameter.h"
#include "WarningInfo.h"
#include "PointcontrlView.h"
#include "ToolUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define LOADTIME 60.0 //s//ly add 20120426
#define UNLOADTIME 10.0 //s//ly add 20120426

SystemDoc& GetDoc()
{
	static SystemDoc  doc;
	return doc;
}

MotionSpeed& GetMotionPara(int iAxisNo) 
{
	return GetDoc().m_sysMotionPara[iAxisNo];
}

void SystemDoc::SetCCDToGlvTestOffset(int iChannel, const Coord3D &crd)
{
	assert(iChannel==HeadLeft||iChannel==HeadRight);
	if(iChannel==HeadLeft)
	{
		m_triTestCCDToGlvOffL = crd;
	}
	else if(iChannel == HeadRight)
	{
		m_triTestCCDToGlvOffR = crd;
	}
}
//振镜校正 加工测试点位置(LASER POINT)
void SystemDoc::SetCCDToGlvTestOffset(const Coord3D &crd, long lHeadNo)
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly	
	if(lHeadNo == HeadLeft)
	{
		
#ifdef USELOG
		if(m_triTestCCDToGlvOffL!=crd)
		{	//"前:x%d y%d z%d"	
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triTestCCDToGlvOffL.x,m_triTestCCDToGlvOffL.y,m_triTestCCDToGlvOffL.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21088),m_triTestCCDToGlvOffL.x,m_triTestCCDToGlvOffL.y,m_triTestCCDToGlvOffL.z);
			//AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20054,BeforeStr);//"左头自动校正位置改变"

		}
#endif 
		m_triTestCCDToGlvOffL = crd;
		
		
	}
	else if(lHeadNo == HeadRight)
	{
		
#ifdef USELOG
			if(m_triTestCCDToGlvOffR!=crd)
		{//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triTestCCDToGlvOffR.x,m_triTestCCDToGlvOffR.y,m_triTestCCDToGlvOffR.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21088),m_triTestCCDToGlvOffR.x,m_triTestCCDToGlvOffR.y,m_triTestCCDToGlvOffR.z);
		//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20055,BeforeStr);//"右头自动校正位置改变"

		}
#endif 
		m_triTestCCDToGlvOffR = crd;
	}
}
//CCDTOCCD试点位置(LASER POINT)
void SystemDoc::SetCCDToCCDTestOffset(const Coord3D &crd, long lHeadNo)
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if(lHeadNo == HeadLeft)
	{
		
#ifdef USELOG
		if(m_triTestCCDToGlvOffL!=crd)
		{	//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triTestCCDToCCDOffL.x,m_triTestCCDToCCDOffL.y,m_triTestCCDToCCDOffL.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21088),m_triTestCCDToCCDOffL.x,m_triTestCCDToCCDOffL.y,m_triTestCCDToGlvOffL.z);
		//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20054,BeforeStr);//"左头自动校正位置改变"

		}
#endif 
		m_triTestCCDToCCDOffL = crd;
		
		
	}
	else if(lHeadNo == HeadRight)
	{
		
#ifdef USELOG
			if(m_triTestCCDToCCDOffR!=crd)
		{//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triTestCCDToCCDOffR.x,m_triTestCCDToCCDOffR.y,m_triTestCCDToCCDOffR.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21088),m_triTestCCDToCCDOffR.x,m_triTestCCDToCCDOffR.y,m_triTestCCDToGlvOffR.z);
			//AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20055,BeforeStr);//"右头自动校正位置改变"

		}
#endif 
		m_triTestCCDToCCDOffR = crd;
	}
}

void SystemDoc::SetLongPathCCDToGlvTestOffset(const Coord3D &crd, long lHeadNo)
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if(lHeadNo == HeadLeft)
	{
		
#ifdef USELOG
		if(m_triTestLongPathCCDToGlvOffL!=crd)
		{	//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triTestLongPathCCDToGlvOffL.x,m_triTestLongPathCCDToGlvOffL.y,m_triTestLongPathCCDToGlvOffL.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21088),m_triTestLongPathCCDToGlvOffL.x,m_triTestLongPathCCDToGlvOffL.y,m_triTestLongPathCCDToGlvOffL.z);
			//AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20056,BeforeStr);//"左头长激光路径自动校正位置改变"

		}
#endif 
		m_triTestLongPathCCDToGlvOffL = crd;
		
		
	}
	else if(lHeadNo == HeadRight)
	{
		
#ifdef USELOG
			if(m_triTestLongPathCCDToGlvOffR!=crd)
		{//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triTestLongPathCCDToGlvOffR.x,m_triTestLongPathCCDToGlvOffR.y,m_triTestLongPathCCDToGlvOffR.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21088),m_triTestLongPathCCDToGlvOffR.x,m_triTestLongPathCCDToGlvOffR.y,m_triTestLongPathCCDToGlvOffR.z);
		//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20057,BeforeStr);//"右头长激光路径自动校正位置改变"

		}
#endif 
		m_triTestLongPathCCDToGlvOffR = crd;
	}
}
//振镜校正 加工测试点位置(LASER POINT)
Coord3D SystemDoc::GetCCDToGlvTestOffset(long lHeadNo)  const
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if (lHeadNo==HeadLeft)
	{
		return m_triTestCCDToGlvOffL;
	}
	else if(lHeadNo==HeadRight)
	{
		return m_triTestCCDToGlvOffR;
	}
	else 
	{

		strncpy(ez,GetLang().GetWarningText(21065),256);
		AfxMessageBox(ez);//"获取测试CCD振镜偏置时索引号超出范围"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21066),256);
		tempstr.Format(ez,lHeadNo);//"引进的索引号是 :%d"
		GetLog().Append_pro(10095,20058);//"获取CCD偏置时索引号超出范围","GetCCDToGlvTestOffset"
#endif
		return Coord3D();
	}
}

//////////CCDTOCCD 加工测试点位置(LASER POINT)
Coord3D SystemDoc::GetCCDToCCDTestOffset(long lHeadNo)  const
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if (lHeadNo==HeadLeft)
	{
		return m_triTestCCDToCCDOffL;
	}
	else if(lHeadNo==HeadRight)
	{
		return m_triTestCCDToCCDOffR;
	}
	else 
	{		
		strncpy(ez,GetLang().GetWarningText(21065),256);
		AfxMessageBox(ez);//"获取测试CCD振镜偏置时索引号超出范围"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21066),256);
		tempstr.Format(ez,lHeadNo);//"引进的索引号是 :%d"
		GetLog().Append_pro(10095,20058);//"获取CCD偏置时索引号超出范围","GetCCDToGlvTestOffset"
#endif
		return Coord3D();
	}
}

Coord3D SystemDoc::GetLongPathCCDToGlvTestOffset(long lHeadNo)  const
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if (lHeadNo==HeadLeft)
	{
		return m_triTestLongPathCCDToGlvOffL;
	}
	else if(lHeadNo==HeadRight)
	{
		return m_triTestLongPathCCDToGlvOffR;
	}
	else 
	{		
		strncpy(ez,GetLang().GetWarningText(21065),256);
		AfxMessageBox(ez);//"获取测试CCD振镜偏置时索引号超出范围"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21066),256);
		tempstr.Format(ez,lHeadNo);//"引进的索引号是 :%d"
		GetLog().Append_pro(10095,20059);//"获取CCD偏置时索引号超出范围","GetLongPathCCDToGlvTestOffset"
#endif
		return Coord3D();
	}
}

void SystemDoc::SetCCDToGlvSysOffset(const Coord3D &crd, long lHeadNo)
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if(lHeadNo == HeadLeft)
	{
		if(!GetDoc().GetTechnicType())
		{
#ifdef USELOG
			if(m_triSCCDToGlvSysOffsetLT!=crd)
			{	//"前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21088),256);
				BeforeStr.Format(ez,m_triSCCDToGlvSysOffsetLT.x,m_triSCCDToGlvSysOffsetLT.y,m_triSCCDToGlvSysOffsetLT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21089),256);
				AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

				//BeforeStr.Format(GetLang().GetWarningText(21088),m_triSCCDToGlvSysOffsetLT.x,m_triSCCDToGlvSysOffsetLT.y,m_triSCCDToGlvSysOffsetLT.z);
			//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
				GetLog().Append_pro(AfterStr,20060,BeforeStr);//"短光路左头振镜和CCD相对位置改变"
			}
#endif 
			m_triSCCDToGlvSysOffsetLT = crd;
		}
		else
		{
#ifdef USELOG
			if(m_triLCCDToGlvSysOffsetLT!=crd)
			{	//"前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21088),256);
				BeforeStr.Format(ez,m_triLCCDToGlvSysOffsetLT.x,m_triLCCDToGlvSysOffsetLT.y,m_triLCCDToGlvSysOffsetLT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21089),256);
				AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

				//BeforeStr.Format(GetLang().GetWarningText(21088),m_triLCCDToGlvSysOffsetLT.x,m_triLCCDToGlvSysOffsetLT.y,m_triLCCDToGlvSysOffsetLT.z);
				//AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
				GetLog().Append_pro(AfterStr,20061,BeforeStr);//"长光路左头振镜和CCD相对位置改变"

			}
#endif 
			m_triLCCDToGlvSysOffsetLT = crd;
		}
	}
	else if(lHeadNo == HeadRight)
	{
		if(!GetDoc().GetTechnicType())
		{
#ifdef USELOG
			if(m_triSCCDToGlvSysOffsetRT!=crd)
			{//"前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21088),256);
				BeforeStr.Format(ez,m_triSCCDToGlvSysOffsetRT.x,m_triSCCDToGlvSysOffsetRT.y,m_triSCCDToGlvSysOffsetRT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21089),256);
				AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//	BeforeStr.Format(GetLang().GetWarningText(21088),m_triSCCDToGlvSysOffsetRT.x,m_triSCCDToGlvSysOffsetRT.y,m_triSCCDToGlvSysOffsetRT.z);
			//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
				GetLog().Append_pro(AfterStr,20062,BeforeStr);//"短光路右头振镜和CCD相对位置改变"

			}
#endif 
			m_triSCCDToGlvSysOffsetRT = crd;
		}
		else
		{
#ifdef USELOG
			if(m_triLCCDToGlvSysOffsetRT!=crd)
			{//"前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21088),256);
				BeforeStr.Format(ez,m_triLCCDToGlvSysOffsetRT.x,m_triLCCDToGlvSysOffsetRT.y,m_triLCCDToGlvSysOffsetRT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21089),256);
				AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

				//BeforeStr.Format(GetLang().GetWarningText(21088),m_triLCCDToGlvSysOffsetRT.x,m_triLCCDToGlvSysOffsetRT.y,m_triLCCDToGlvSysOffsetRT.z);
			//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
				GetLog().Append_pro(AfterStr,20063,BeforeStr);//"长光路右头振镜和CCD相对位置改变"

			}
#endif 
			m_triLCCDToGlvSysOffsetRT = crd;
		}
	}
	m_crdPathOffsetLT.x=(m_triLCCDToGlvSysOffsetLT.x-m_triSCCDToGlvSysOffsetLT.x)/2;
	m_crdPathOffsetLT.y=(m_triLCCDToGlvSysOffsetLT.y-m_triSCCDToGlvSysOffsetLT.y)/2;
	m_crdPathOffsetRT.x=(m_triLCCDToGlvSysOffsetRT.x-m_triSCCDToGlvSysOffsetRT.x)/2;
	m_crdPathOffsetRT.y=(m_triLCCDToGlvSysOffsetRT.y-m_triSCCDToGlvSysOffsetRT.y)/2;
}

BOOL SystemDoc::IsGlovCalibOffstOutofTol(const Coord3D& crdResult,long nHead)
{
	ASSERT( nHead==HeadLeft||nHead==HeadRight);
	char ez[256]={""};//ly 20110404
	//取偏差
	CString strLog1;
	CString strLog2;
	long nGlvCalibOffstTol = GetGlvCaliOffsetTol();
	if(nHead == HeadLeft)
	{
		if(!GetDoc().GetTechnicType())
		{
			if (m_triSCCDToGlvSysOffsetLT.x == 0 && m_triSCCDToGlvSysOffsetLT.y == 0)
			{//没有做过原点校正
				return TRUE;
			}
			if (GetTwoPoitDistance(crdResult,m_triSCCDToGlvSysOffsetLT) > nGlvCalibOffstTol)
			{
#ifdef USELOG//"前次:x%d y%d z%d"//"当前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21090),256);
				BeforeStr.Format(ez,m_triSCCDToGlvSysOffsetLT.x,m_triSCCDToGlvSysOffsetLT.y,m_triSCCDToGlvSysOffsetLT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21091),256);
				AfterStr.Format(ez,crdResult.x,crdResult.y,crdResult.z);//"后:%d"

				//strLog1.Format(GetLang().GetWarningText(21090),m_triSCCDToGlvSysOffsetLT.x,m_triSCCDToGlvSysOffsetLT.y,m_triSCCDToGlvSysOffsetLT.z);
				//strLog2.Format(GetLang().GetWarningText(21091),crdResult.x,crdResult.y,crdResult.z);
				GetLog().Append_pro(strLog2,20064,strLog1);//"短光路左头振镜和CCD相对位置校正偏差过大"
#endif
			}
			else
			{
				return TRUE;
			}
		}
		else
		{
			if (m_triLCCDToGlvSysOffsetLT.x == 0 && m_triLCCDToGlvSysOffsetLT.y == 0)
			{//没有做过原点校正
				return TRUE;
			}
			if (GetTwoPoitDistance(crdResult, m_triLCCDToGlvSysOffsetLT) > nGlvCalibOffstTol)
			{
#ifdef USELOG//"前次:x%d y%d z%d"//"当前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21090),256);
				BeforeStr.Format(ez,m_triLCCDToGlvSysOffsetLT.x,m_triLCCDToGlvSysOffsetLT.y,m_triLCCDToGlvSysOffsetLT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21091),256);
				AfterStr.Format(ez,crdResult.x,crdResult.y,crdResult.z);//"后:%d"

			//	strLog1.Format(GetLang().GetWarningText(21090),m_triLCCDToGlvSysOffsetLT.x,m_triLCCDToGlvSysOffsetLT.y,m_triLCCDToGlvSysOffsetLT.z);
			//	strLog2.Format(GetLang().GetWarningText(21091),crdResult.x,crdResult.y,crdResult.z);
				GetLog().Append_pro(strLog2,20065,strLog1);//"长光路左头振镜和CCD相对位置校正偏差过大"
#endif
			}
			else
			{
				return TRUE;
			}
		}
	
	}
	else
	{
		if(!GetDoc().GetTechnicType())
		{
			if (m_triSCCDToGlvSysOffsetRT.x == 0 && m_triSCCDToGlvSysOffsetRT.y == 0)
			{//没有做过原点校正
				return TRUE;
			}
			if (GetTwoPoitDistance(crdResult , m_triSCCDToGlvSysOffsetRT) > nGlvCalibOffstTol)
			{
#ifdef USELOG//"前次:x%d y%d z%d"//"当前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21090),256);
				BeforeStr.Format(ez,m_triSCCDToGlvSysOffsetRT.x,m_triSCCDToGlvSysOffsetRT.y,m_triSCCDToGlvSysOffsetRT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21091),256);
				AfterStr.Format(ez,crdResult.x,crdResult.y,crdResult.z);//"后:%d"

			//	strLog1.Format(GetLang().GetWarningText(21090),m_triSCCDToGlvSysOffsetRT.x,m_triSCCDToGlvSysOffsetRT.y,m_triSCCDToGlvSysOffsetRT.z);
			//strLog2.Format(GetLang().GetWarningText(21091),crdResult.x,crdResult.y,crdResult.z);
				GetLog().Append_pro(strLog2,20066,strLog1);//"短光路右头振镜和CCD相对位置校正偏差过大"
#endif
			}
			else
			{
				return TRUE;
			}
		}
		else
		{
			if (m_triLCCDToGlvSysOffsetRT.x == 0 && m_triLCCDToGlvSysOffsetRT.y == 0)
			{//没有做过原点校正
				return TRUE;
			}
			if (GetTwoPoitDistance(crdResult, m_triLCCDToGlvSysOffsetRT) > nGlvCalibOffstTol)
			{
#ifdef USELOG//"前次:x%d y%d z%d"//"当前:x%d y%d z%d"
				strncpy(ez,GetLang().GetWarningText(21090),256);
				BeforeStr.Format(ez,m_triLCCDToGlvSysOffsetRT.x,m_triLCCDToGlvSysOffsetRT.y,m_triLCCDToGlvSysOffsetRT.z);//"前:%d"
				strncpy(ez,GetLang().GetWarningText(21091),256);
				AfterStr.Format(ez,crdResult.x,crdResult.y,crdResult.z);//"后:%d"

				//strLog1.Format(GetLang().GetWarningText(21090),m_triLCCDToGlvSysOffsetRT.x,m_triLCCDToGlvSysOffsetRT.y,m_triLCCDToGlvSysOffsetRT.z);
			//	strLog2.Format(GetLang().GetWarningText(21091),crdResult.x,crdResult.y,crdResult.z);
				GetLog().Append_pro(strLog2,20067,strLog1);//"长光路右头振镜和CCD相对位置校正偏差过大"
#endif
			}
			else
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

long SystemDoc::GetTwoPoitDistance(const Coord& crd1,const Coord& crd2)
{
	return sqrt((long double)(crd1.x - crd2.x)*(crd1.x - crd2.x) + (long double)(crd1.y - crd2.y)*(crd1.y - crd2.y));
}

Coord3D SystemDoc::GetCCDToGlvSysOffset(long lHeadNo)  const
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	if (lHeadNo==HeadLeft)
	{
		if(!GetDoc().GetTechnicType())
		{
			return m_triSCCDToGlvSysOffsetLT;
		}
		else
		{
			return m_triLCCDToGlvSysOffsetLT;
		}
	}
	else if(lHeadNo==HeadRight)
	{
		if(!GetDoc().GetTechnicType())
		{
			return m_triSCCDToGlvSysOffsetRT;
		}
		else
		{
			return m_triLCCDToGlvSysOffsetRT;
		}
	}
	else 
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21067),256);
	    AfxMessageBox(ez);//"获取CCD偏置时索引号超出范围"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21066),256);
		tempstr.Format(ez,lHeadNo);//"引进的索引号是 :%d"
		GetLog().Append_pro(10095,"GetCCDToGlvSysOffset");//"获取CCD偏置时索引号超出范围",
#endif
		return Coord3D();
	}
}

Coord SystemDoc::GetPathOffset(long lHeadNo)  const
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	if (lHeadNo==HeadLeft)
	{
		return m_crdPathOffsetLT;
	}
	else
	{
		return m_crdPathOffsetRT;
	}
}

void SystemDoc::SetLaserPowerTestCrd(const Coord3D& crd , long  lHeadNo)
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
char ez[256]={""};//ly 20110404
	if (lHeadNo==HeadLeft)
	{
		
#ifdef USELOG
		if(m_triLaserPowerTestL!=crd)
		{//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triLaserPowerTestL.x,m_triLaserPowerTestL.y,m_triLaserPowerTestL.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21088),m_triLaserPowerTestL.x,m_triLaserPowerTestL.y,m_triLaserPowerTestL.z);
		//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20068,BeforeStr);//"左头激光能量测试位置改变"
		}
#endif
		m_triLaserPowerTestL = crd;
	}
	else if(lHeadNo==HeadRight)
	{
#ifdef USELOG
		if(m_triLaserPowerTestR!=crd)
		{//"前:x%d y%d z%d"
			strncpy(ez,GetLang().GetWarningText(21088),256);
			BeforeStr.Format(ez,m_triLaserPowerTestR.x,m_triLaserPowerTestR.y,m_triLaserPowerTestR.z);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21089),256);
			AfterStr.Format(ez,crd.x,crd.y,crd.z);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21088),m_triLaserPowerTestR.x,m_triLaserPowerTestR.y,m_triLaserPowerTestR.z);
		//	AfterStr.Format(GetLang().GetWarningText(21089),crd.x,crd.y,crd.z);//"后:x%d y%d z%d"
			GetLog().Append_pro(AfterStr,20069,BeforeStr);//"右头激光能量测试位置改变"
		}
#endif
		m_triLaserPowerTestR = crd;
	}
	
}

Coord3D SystemDoc::GetLaserPowerTestCrd(long lHeadNo) const
{
	ASSERT( lHeadNo==HeadLeft||lHeadNo==HeadRight);
	if (lHeadNo==HeadLeft)
	{
		return m_triLaserPowerTestL;
	}
	else if(lHeadNo==HeadRight)
	{
		return m_triLaserPowerTestR;
	}
	return 0,0,0;
}

long SystemDoc::GetDirMachSn() const
{
	return m_lDirMachSn;
}

long SystemDoc::GetDirManuDay() const
{
	return m_lDirManuDay;
}

long SystemDoc::GetDirManuTime() const
{
	return m_lDirManuTime;
}

void SystemDoc::SetDirMachSn( long lDir)
{
	m_lDirMachSn = lDir;
}

void SystemDoc::SetDirManuDay(long lDir)
{
    m_lDirManuDay = lDir;
}

void SystemDoc::SetDirManuTime(long lDir)
{
	m_lDirManuTime = lDir;
}

BOOL SystemDoc::GetEnMachSn() const
{
	return m_bEnMachSn;
}

BOOL SystemDoc::GetEnManuDay() const
{
	return m_bEnManuDay;
}

BOOL SystemDoc::GetEnManuTime() const
{
	return m_bEnManuTime;
}

BOOL SystemDoc::GetEnLOTSn() const
{
	return m_bEnLOTSn;
}

BOOL SystemDoc::GetEnLOTFix() const//ly add 20121127
{
	return m_bEnLOTFix;
}

BOOL SystemDoc::GetEnLOTInc() const//ly add 20121127
{
	return m_bEnLOTInc;
}

BOOL SystemDoc::GetEnLOTScale() const//ly add 20121127
{
	return m_bEnLOTScale;
}

BOOL SystemDoc::GetEnAxisNo() const//ly add 20121230
{
	return m_bEnAxisNo;
}

BOOL SystemDoc::GetEn3Fid() const//ly add 20130121
{
	return m_bEn3Fid;
}

BOOL SystemDoc::Get3Fid() const//ly add 20131108
{
	return m_bf3Fid;
}

BOOL SystemDoc::GetEnManuFid() const//ly add 20130121
{
	return m_bMaFindFid;
}

void SystemDoc::SetEnLOTFix(BOOL bEnable)//ly add 20121127
{
    m_bEnLOTFix = bEnable;
}

void SystemDoc::SetEnLOTInc(BOOL bEnable)//ly add 20121127
{
    m_bEnLOTInc = bEnable;
}

void SystemDoc::SetEnLOTScale(BOOL bEnable)//ly add 20121127
{
    m_bEnLOTScale = bEnable;
}
   
void SystemDoc::SetEnAxisNo(BOOL bEnable)//ly add 20121230
{
    m_bEnAxisNo = bEnable;
}

void SystemDoc::SetOneAxis(BOOL bEnable)//ly add 20140108
{
	m_bOneAxis = bEnable;
}

BOOL SystemDoc::GetOneAxis()//ly add 20140108
{
	return m_bOneAxis;
}

void SystemDoc::SetCurOneAxis(int axis)//ly add 20140108  0=left  1=right
{
	m_iCurOneAxis = axis;
}

int SystemDoc::GetCurOneAxis()//ly add 20140108
{
	return m_iCurOneAxis;
}


void SystemDoc::SetEn3Fid(BOOL bEnable)//ly add 20130121
{
    m_bEn3Fid = bEnable;
}

void SystemDoc::Set3Fid(BOOL bEnable)//ly add 20131108
{
#ifdef USELOG//ly add 20140527
	if(m_bf3Fid!=bEnable)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_bf3Fid);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,bEnable);//"后:%d"
		
		GetLog().Append_pro(AfterStr,20168,BeforeStr);//"允许三标靶加工改变"
	}
#endif
	m_bf3Fid = bEnable;
}

void SystemDoc::SetCheckManulScaleRange(bool bEnable)//ly add 20140702
{
#ifdef USELOG//ly add 20140527
	if(m_bChManScaleRange!=bEnable)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_bChManScaleRange);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,bEnable);//"后:%d"
		
		GetLog().Append_pro(AfterStr,20169,BeforeStr);//"手动设定加工涨缩阈值管控"
	}
#endif
	m_bChManScaleRange=bEnable;
}

BOOL SystemDoc::GetCheckManulScaleRange()//ly add 20140702
{
	return m_bChManScaleRange;
}

void SystemDoc::SetEnManuFid(BOOL bEnable)//ly add 20130121
{
    m_bMaFindFid = bEnable;
}

int	 SystemDoc::GetLFidNum() const//ly add 20130121
{
	return m_iLFidNum;
}

void SystemDoc::SetLFidNum(int num)//ly add 20130121
{
	m_iLFidNum = num;
}

int	 SystemDoc::GetRFidNum() const//ly add 20130121
{
	return m_iRFidNum;
}

void SystemDoc::SetRFidNum(int num)//ly add 20130121
{
	m_iRFidNum = num;
}

BOOL SystemDoc::GetLFidEn(int index)//ly add 20130121
{
	ASSERT(index<4);
	return m_bLFidEn[index];
}

void SystemDoc::SetLFidEn(BOOL enable,int index)//ly add 20130121
{
	ASSERT(index<4);
	m_bLFidEn[index]=enable;
}

BOOL SystemDoc::GetRFidEn(int index)//ly add 20130121
{
	ASSERT(index<4);
	return m_bRFidEn[index];
}

void SystemDoc::SetRFidEn(BOOL enable,int index)//ly add 20130121
{
	ASSERT(index<4);
	m_bRFidEn[index]=enable;
}

int	 SystemDoc::GetLInnFidNum() const//ly add 20130121
{
	return m_iLInnFidNum;
}

void SystemDoc::SetLInnFidNum(int num)//ly add 20130121
{
	m_iLInnFidNum = num;
}

int	 SystemDoc::GetRInnFidNum() const//ly add 20130121
{
	return m_iRInnFidNum;
}

void SystemDoc::SetRInnFidNum(int num)//ly add 20130121
{
	m_iRInnFidNum = num;
}

BOOL SystemDoc::GetLInnFidEn(int index)//ly add 20130121
{
//	ASSERT(index<4);			//内层6标靶功能
	ASSERT(index<6);
	return m_bLInnFidEn[index];
}

void SystemDoc::SetLInnFidEn(BOOL enable,int index)//ly add 20130121
{
//	ASSERT(index<4);
	ASSERT(index<6);
	m_bLInnFidEn[index]=enable;
}

BOOL SystemDoc::GetRInnFidEn(int index)//ly add 20130121
{
//	ASSERT(index<4);
	ASSERT(index<6);
	return m_bRInnFidEn[index];
}

void SystemDoc::SetRInnFidEn(BOOL enable,int index)//ly add 20130121
{
//	ASSERT(index<4);
	ASSERT(index<6);
	m_bRInnFidEn[index]=enable;
}

BOOL SystemDoc::GetEnManuString() const
{
	return m_bEnManuString;
}

void SystemDoc::SetEnMachSn(BOOL bEnable)
{
	m_bEnMachSn = bEnable;
}

void SystemDoc::SetEnManuTime(BOOL bEnable)
{
	m_bEnManuTime = bEnable;
}


void SystemDoc::SetEnManuDay(BOOL bEnable)
{
	m_bEnManuDay  = bEnable;
}

void SystemDoc::SetEnLOTSn(BOOL bEnable)
{
    m_bEnLOTSn = bEnable;
}

void SystemDoc::SetEnManuString(BOOL bEnable)
{
	m_bEnManuString = bEnable;
}

int SystemDoc::GetDataUnit() const//ly add 20120516 ---------------
{
	return m_fileunit;
}

int SystemDoc::GetCrdMode() const
{
	return m_filemode ;
}

int SystemDoc::GetDataFormat() const
{
	return m_fileformat;
}

int SystemDoc::GetDecimalNum() const
{
	return m_filedecnum;
}

int SystemDoc::GetIntegerNum() const
{
	return m_fileintnum;
}

void SystemDoc::SetDataUnit(int dataunit)
{
	m_fileunit = dataunit;
}

void SystemDoc::SetCrdMode(int mode) 
{
	m_filemode = mode;
}

void SystemDoc::SetDataFormat(int format) 
{
	m_fileformat = format;
}

void SystemDoc::SetDecimalNum(int decnum) 
{
	m_filedecnum = decnum;
}

void SystemDoc::SetIntegerNum(int intnum) //ly add 20120516 ---------------
{
	m_fileintnum = intnum;
}

void SystemDoc::SetTableClamp(BOOL clamp)//ly add 20120523
{
	m_bTableClamp = clamp;
}

BOOL  SystemDoc::GetTableClamp()//ly add 20120523
{
	return m_bTableClamp;
}

void SystemDoc::SetLaserPowerPattern(int laserPowerPattern)//jpc add 20130806
{
	m_ilaserPowerPattern = laserPowerPattern;
}

int  SystemDoc::GetLaserPowerPattern()//jpc add 20130806
{
	return m_ilaserPowerPattern;
}

void SystemDoc::SetUse9112(int temp)//ly add 20130807
{
	m_bUse9112 = temp;
}

int  SystemDoc::GetUse9112()//ly add 20130807
{
	return m_bUse9112;
}

void SystemDoc::SetPowerComHandle(HANDLE hPowerCom)//ly add 20130807
{
	m_hPowerCom = hPowerCom;
}

HANDLE  SystemDoc::GetPowerComHandle()//ly add 20130807
{
	return m_hPowerCom;
}

void SystemDoc::SetScaleUnit(BOOL temp)//ly add 20130625---------------------
{
	m_bScaleUnit = temp;
}

BOOL SystemDoc::GetScaleUnit()
{
	return m_bScaleUnit;
}

void SystemDoc::SetPowerMax(BOOL temp)
{
	m_bPowerMax = temp;
}

BOOL SystemDoc::GetPowerMax()
{
	return m_bPowerMax;
}

void SystemDoc::SetWaterYBJ(BOOL temp)
{
	m_bWaterYBJ = temp;
}

BOOL SystemDoc::GetWaterYBJ()
{
	return m_bWaterYBJ;
}

long SystemDoc::GetCCDContrastThrd()//ly add 20140328
{
	return m_lCCDContrastThrd;
}

BOOL SystemDoc::GetCongexErrorPoint()
{
	return m_bCongexErrorPoint;
}

void SystemDoc::SetCongexErrorPoint(BOOL congexErrorPoint)
{
	this->m_bCongexErrorPoint=congexErrorPoint;
}

int SystemDoc::GetCountCongexError()
{
	return m_iconutCongexError;
}

void SystemDoc::AddCongexError()
{
	m_iconutCongexError++;
}

void SystemDoc::SetCountCongexError(int conutCongexError)
{
	this->m_iconutCongexError=conutCongexError;
}

void SystemDoc::SetScanSizeMax(int temp)//ly add 20140308
{
	m_iScanSizeMax = temp;
}

int  SystemDoc::GetScanSizeMax()
{
	return m_iScanSizeMax;
}


void SystemDoc::SetDefineMatrixRange(long temp)//20150129
{
	m_DefineMatrixRange = temp;
}

long  SystemDoc::GetDefineMatrixRange()
{
	return m_DefineMatrixRange;
}

int SystemDoc::GetScanlabDeadTime()
{
	return m_iScanlabDeadTime;
}

void SystemDoc::SetLargeTable(int temp)
{
	m_iLargeTable = temp;
	if(m_iLargeTable==0)
	{
		m_lTableWidth =	550;
		m_lTableHeight=	650;
	}
	else
	{
		m_lTableWidth =	650;
		m_lTableHeight=	815;
	}
}

long  SystemDoc::GetTableWidth()
{
	return m_lTableWidth;
}

long  SystemDoc::GetTableHeight()
{
	return m_lTableHeight;
}

int  SystemDoc::GetLargeTable()//ly add 20140308
{
	return m_iLargeTable;
}

long SystemDoc::GetTableResetPosX(int TableType)//ly add 20140324
{
	long posx;
	if(TableType==0)
		posx=0;
	if(TableType==1)
		posx=80000;
	return	posx;
}


void SystemDoc::SetInfrared(int temp)//ly add 20140418
{
	m_isInfrared = temp;
}

int  SystemDoc::GetInfrared()
{
	return m_isInfrared;
}

void SystemDoc::SetHandCOMNum(int temp)
{
	m_isHandCOMNum = temp;
}
int  SystemDoc::GetHandCOMNum()
{
	return m_isHandCOMNum;
}
void SystemDoc::SetPowerCOMNum(int temp)
{
	m_isPowerCOMNum = temp;
}
int  SystemDoc::GetPowerCOMNum()
{
	return m_isPowerCOMNum;
}

void SystemDoc::SetDoorOpenWarning(int temp)//ly add 20140418
{
	m_iDoorOpen = temp;
}

int  SystemDoc::GetDoorOpenWarning()
{
	return m_iDoorOpen;
}

void SystemDoc::SetFZInnerMark(BOOL temp)
{
	m_bFZInnerMark = temp ;
}

BOOL SystemDoc::GetFZInnerMark()
{
	return m_bFZInnerMark;
}

void SystemDoc::SetGYDMirror(BOOL temp)
{
	m_bGYDmirror = temp ;
}

BOOL SystemDoc::GetGYDMirror()
{
	return m_bGYDmirror;
}

void SystemDoc::SetShunluoScale(BOOL temp)
{
	m_bShunluoScale = temp ;
}

BOOL SystemDoc::GetShunluoScale()
{
	return m_bShunluoScale;
}

void SystemDoc::SetShenLan3Fid(int temp)
{
	this->m_bShenLan3Fid = temp ;
}

int SystemDoc::GetShenLan3Fid()
{
	return m_bShenLan3Fid;
}

void SystemDoc::SetShowTool(BOOL temp)//ly add 20140520
{
	m_bShowTool = temp ;
}

BOOL SystemDoc::GetShowTool()//ly add 20140520
{
	return m_bShowTool;
}

void SystemDoc::SetLoadAfterPitch(BOOL temp)//ly add 20140520
{
	m_bLoadAfterPitch = temp ;
}

BOOL SystemDoc::GetLoadAfterPitch()//ly add 20140520
{
	return m_bLoadAfterPitch;
}

void SystemDoc::SetFileLPTest(BOOL temp)
{
	m_bFileLPowerTest = temp ;
}

BOOL SystemDoc::GetFileLPTest()
{
	return m_bFileLPowerTest;
}

void SystemDoc::SetFORWARDX(long temp)//ly add 20130805----
{
	m_lFORWARDX= temp+6000;
}
void SystemDoc::SetREVERSEX(long temp)
{
	m_lREVERSEX= temp-6000;
}
void SystemDoc::SetFORWARDY(long temp)
{
	m_lFORWARDY=temp+6000;
}
void SystemDoc::SetREVERSEY(long temp)
{
	m_lREVERSEY=temp-6000;
}

long SystemDoc::GetFORWARDX()
{
	return m_lFORWARDX;
}

long SystemDoc::GetREVERSEX()
{
	return m_lREVERSEX;
}

long SystemDoc::GetFORWARDY()
{
	return m_lFORWARDY;
}

long SystemDoc::GetREVERSEY()
{
	return m_lREVERSEY;
}

BOOL SystemDoc::GetAptDelayFile()
{
	CIniFile IniFile;
	CString str,path;
	long ltmp = 0;
	double dTemp=0.0;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\AptPower");
	IniFile.SetPath(path);       

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{	
		CString Release;
		Release.Format("delay");
		
		for(int nApt=1;nApt<=18;nApt++)
		{
			CString Apt;
			Apt.Format("%d",nApt);
			Apt="A"+Apt;
					
			if(!IniFile.GetItemInt(Apt,	 Release,  ltmp))//ly add 20130801
			{
				strncpy(ez,GetLang().GetWarningText(13029),256);
				CString str;
				str.Format(ez,nApt);
				AfxMessageBox(str,MB_OK);//"文件没有第%d光圈的首发延时值，请在功率文件里增添该内容！"

				IniFile.CloseIniFile();
				return false;
			}

			m_lAptDelay[nApt-1]=ltmp;
		}

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13021),256);
		AfxMessageBox(ez,MB_OK);//"无法导入版本参数！"
#ifdef USELOG
		GetLog().Append_pro(10115,"LoadAptPower");//"无法导入版本参数"
#endif
		return false;
	}

	return true;
}

long SystemDoc::GetAptDelay(int nApt)
{
#ifdef D2CTYPE
	return m_lAptDelay[nApt-1];
#else
	if((nApt<15)&&(m_lAptDelay[nApt-1]>500))												//20161219 增加加工效率约束
		return 500;

	return m_lAptDelay[nApt-1];
#endif

//	if((nApt<15)&&(m_lAptDelay[nApt-1]>500))												//20161219 增加加工效率约束
//		return 500;

//	return m_lAptDelay[nApt-1];
}

double SystemDoc::GetAptPower(int nApt,int nrelease)
{
	CIniFile IniFile;
	CString str,path;
	long ltmp = 0;
	double dTemp=0.0;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\AptPower");
	IniFile.SetPath(path); 

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		double temp;
		CString Apt;
		CString Release;
		Apt.Format("%d",nApt);
		Apt="A"+Apt;
		Release.Format("%d",nrelease);

		if(!IniFile.GetItemF64(Apt,	 Release,  m_dFileAptLPower))//ly add 20130801
		{
			strncpy(ez,GetLang().GetWarningText(13030),256);
			CString str;
			str.Format(ez,nApt,nrelease);
			AfxMessageBox(ez,MB_OK);//"文件没有第%d光圈脉宽%d的标准功率值，请在功率文件里增添该内容！"
			m_dFileAptLPower=0.0;
		}

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13021),256);
		AfxMessageBox(ez,MB_OK);//"无法导入版本参数！"
#ifdef USELOG
		GetLog().Append_pro(10115,"LoadAptPower");//"无法导入版本参数"
#endif
		m_dFileAptLPower=0.0;
	}

	return m_dFileAptLPower;
}

void SystemDoc::SetNewDelay(BOOL temp)
{
	m_bNewDelay = temp ;
}

BOOL SystemDoc::GetNewDelay()
{
	return m_bNewDelay;
}

long SystemDoc::GetBET1F()
{
	return m_lBET1F;
}

long SystemDoc::GetBET2F()
{
	return m_lBET2F;
}

long SystemDoc::GetBET3F()
{
	return m_lBET3F;
}

double SystemDoc::GetBET1TOBET2()
{
	return m_dBET1TOBET2;
}

double SystemDoc::GetBET2TOBET3()
{
	return m_dBET2TOBET3;
}

long SystemDoc::GetBETMAX()//ly add 20130625-----------------------
{
	return m_lBETMAX;
}

void SystemDoc::SetFitApt(BOOL temp)//ly add 20131223------------
{
	m_bFitApt= temp ;
}

BOOL SystemDoc::GetFitApt()//ly add 20131223------------
{
	return m_bFitApt;
}

void SystemDoc::SetDrillInc(BOOL temp)//ly add 20140702------------
{
	m_bDrillInc= temp ;
}

BOOL SystemDoc::GetDrillInc()//ly add 20140702------------
{
	return m_bDrillInc;
}

void SystemDoc::SetDrillH01H02(BOOL temp)//ly add 20140702------------
{
	m_bDrillH01H02= temp ;
}
BOOL SystemDoc::GetDrillH01H02()//ly add 20140702------------
{
	return m_bDrillH01H02;
}

BOOL SystemDoc::GetLaserPowerMode()//ly add 20140702------------
{
	return m_bLaserPowerMode;
}

void SystemDoc::SetLaserPowerMode(BOOL laserPowerMode)//ly add 20140702------------
{
	m_bLaserPowerMode= laserPowerMode ;
}


BOOL SystemDoc::GetLaserPowerShow()//ly add 20140702------------
{
	return m_bLaserPowerShow;
}

void SystemDoc::SetLaserPowerShow(BOOL laserPowerShow)//ly add 20140702------------
{
	this->m_bLaserPowerShow= laserPowerShow ;
}

long SystemDoc::GetLaserPowerDelayTime()//ly add 20140702------------
{
	return m_bLaserPowerDelayTime;
}

void SystemDoc::SetLaserPowerDelayTime(BOOL laserPowerDelayTime)//ly add 20140702------------
{
	this->m_bLaserPowerDelayTime= laserPowerDelayTime ;
}

long SystemDoc::GetLaserPowerTimes()
{
	return m_ilaserPowerTimes;
	
}
void SystemDoc::SetLaserPowerTimes(long laserPowerTimes)
{
	this->m_ilaserPowerTimes= laserPowerTimes ;
}

BOOL SystemDoc::GetIsNullPrecessHoles()	//20151204 设置是否空跑板，只计算板的涨缩，不加工移动平台
{
   return m_isNullPrecessHoles;
}
void SystemDoc::SetIsNullPrecessHoles(BOOL isNullPrecessHoles)
{
  	this->m_isNullPrecessHoles= isNullPrecessHoles ;
}

BOOL SystemDoc::GetBunchMode()//是否开启激光串模式加工
{
	return m_bBurstMode;
}

void SystemDoc::SetBunchMode(BOOL bBunchMode)//ly add 20140702------------
{
	m_bBurstMode= bBunchMode ;
}

void SystemDoc::SetFitBit(BOOL temp)//ly add 20130724------------
{
	m_bFitBit = temp ;
}

BOOL SystemDoc::GetFitBit()
{
	return m_bFitBit;
}

void SystemDoc::SetMatch(BOOL temp)
{
	m_bMatch = temp ;
}

BOOL SystemDoc::GetMatch()
{
	return m_bMatch;
}

void SystemDoc::SetMatchScore(double temp)
{
	m_bMatchScore = temp ;
}

double SystemDoc::GetMatchScore()//ly add 20130724----------
{
	return m_bMatchScore;
}

void SystemDoc::SetLAvgScaleX(double temp)//ly add 20131021----------
{
	m_dLScaleX = temp ;
}

double SystemDoc::GetLAvgScaleX()
{
	return m_dLScaleX;
}

void SystemDoc::SetLAvgScaleY(double temp)
{
	m_dLScaleY = temp ;
}

double SystemDoc::GetLAvgScaleY()
{
	return m_dLScaleY;
}

void SystemDoc::SetRAvgScaleX(double temp)
{
	m_dRScaleX = temp ;
}

double SystemDoc::GetRAvgScaleX()
{
	return m_dRScaleX;
}

void SystemDoc::SetRAvgScaleY(double temp)
{
	m_dRScaleY = temp ;
}

double SystemDoc::GetRAvgScaleY()
{
	return m_dRScaleY;
}

void SystemDoc::SetLNum(long temp)
{
	m_lLNum=temp;
}

long SystemDoc::GetLNum()
{
	return m_lLNum ;
}
void SystemDoc::SetRNum(long temp)
{
	m_lRNum=temp;
}

long SystemDoc::GetRNum()
{
	return m_lRNum;
}

void SystemDoc::SetLastFile(CString temp)
{
	m_strLastFile = temp;
}

CString SystemDoc::GetLastFile()//ly add 20131021----
{
	return m_strLastFile;
}

void SystemDoc::SetOutFidsOffset(int offset) //ly add 20140504
{
	m_iOutFidsOffset = offset;
}

int SystemDoc::GetOutFidsOffset()//ly add 20140504
{
	return m_iOutFidsOffset;
}

float SystemDoc::GetLaserPwAvg()//ly add 20140612
{
	float avg=0;
	float total=0.0;
	for(int index=0;index<5;index++)
	{
		total+=m_fLaserPw[index];
	}
	avg=total/5.0;
	return avg;
}

void SystemDoc::ResetLaserPw()//ly add 20140612
{
	for(int index=0;index<5;index++)
	{
		m_fLaserPw[index]=-1;
	}
	return;
}

void SystemDoc::SetLaserPw(int index,double pw)//ly add 20140527
{
	if((index>4)||(index<0))
		return;
	m_fLaserPw[index]=(float)pw;
}

float SystemDoc::GetLaserPw(int index)//ly add 20140527
{
	return m_fLaserPw[index];
}

float SystemDoc::GetLaserPwMax()//ly add 20140527
{
	float temp = m_fLaserPw[0] ;
	for(int i =1;i<5;i++)
	{
		if(temp<m_fLaserPw[i])
			temp=m_fLaserPw[i];
	}
	return temp;
}

float SystemDoc::GetLaserPwMin()//ly add 20140527
{
	float temp = m_fLaserPw[0] ;
	for(int i =1;i<5;i++)
	{
		if(temp>m_fLaserPw[i])
			temp=m_fLaserPw[i];
	}
	return temp;
}

void SystemDoc::SetFZInnerOffset(int offset) //ly add 20120522
{
	m_iFZInnerOffset = offset;
}

int SystemDoc::GetFZInnerOffset()//ly add 20120522
{
	return m_iFZInnerOffset;
}

void SystemDoc::SetFZInnerScale(double scale) //ly add 20120522
{
#ifdef USELOG													//20190711 增加
	if(m_fFZInnerScale!=scale)
	{
		BeforeStr.Format("前:%f",m_fFZInnerScale);
		AfterStr.Format("后:%f",scale);

		GetLog().Append_pro(AfterStr,"内标靶涨缩阈值改变",BeforeStr);
	}
#endif

	m_fFZInnerScale = scale;
}

double SystemDoc::GetFZInnerScale()//ly add 20120522
{
	return m_fFZInnerScale;
}

void SystemDoc::SetLaserComp(int comp) //ly add 20120919
{
	m_laserComp = comp;
}

long SystemDoc::GetLaserComp()//ly add 20120919
{
	return m_laserComp;
}

void SystemDoc::SetLaserTestComp(int comp) //ly add 20121227
{
	m_laserTestComp = comp;
}

long SystemDoc::GetLaserTestComp()//ly add 20121227
{
	return m_laserTestComp;
}

void SystemDoc::SetLoadOptimize(bool opt) //ly add 20120919
{
	m_LoadOptimize = opt;
}

long SystemDoc::GetLoadOptimize()//ly add 20120919
{
	return m_LoadOptimize;
}

long SystemDoc::GetCCDFocus(int nCCDNo) const
{
	ASSERT( nCCDNo==HeadLeft||nCCDNo==HeadRight);

	if(nCCDNo==0){
		return m_lCCDFocusPosL;
	}
	else if(nCCDNo ==1)
	{
		return m_lCCDFocusPosR;
	}
	else
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21068),256);
		AfxMessageBox(ez);//"CCD序号超出范围!"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21069),256);
		tempstr.Format(ez,nCCDNo);//"引进的CCD号是 :%d"
		GetLog().Append_pro(10096,"GetCCDFocus");//"CCD序号超出范围"
#endif
		return -1;
	}
}

void SystemDoc::SetCCDFocus(long lPos,int nCCDNo)
{
	ASSERT( nCCDNo==HeadLeft||nCCDNo==HeadRight);
	char ez[256]={""};//ly
	if(nCCDNo==0){
#ifdef USELOG
		if(m_lCCDFocusPosL!=lPos)
		{			
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_lCCDFocusPosL);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,lPos);//"后:%d"

			GetLog().Append_pro(AfterStr,20070,BeforeStr);//"左头CCD焦距改变"
		}
#endif
		m_lCCDFocusPosL = lPos;
	}
	else if(nCCDNo ==1)
	{
#ifdef USELOG
		if(m_lCCDFocusPosR!=lPos)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_lCCDFocusPosR);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,lPos);//"后:%d"

			GetLog().Append_pro(AfterStr,20071,BeforeStr);//"右头CCD焦距改变"
		}
#endif
		m_lCCDFocusPosR = lPos;
	}
}

long SystemDoc::GetLaserProcFocus(int nNo) const
{
	ASSERT( nNo==HeadLeft||nNo==HeadRight);
	char ez[256]={""};//ly 20110404

	if(nNo==0){
		return m_lLaserDrillPosL;
	}
	else if(nNo ==1)
	{
		return m_lLaserDrillPosR;
	}
	else
	{		
		strncpy(ez,GetLang().GetWarningText(21070),256);
		AfxMessageBox(ez);//"LaserProcFocus序号超出范围!"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21071),256);
		tempstr.Format(ez,nNo);//"引进的LaserHead是 :%d"
		GetLog().Append_pro(10097,"GetLaserProcFocus");//"LaserHead超出范围"
#endif
		return -1;
	}
}
long SystemDoc::GetLongPathLaserProcFocus(int nNo) const
{
	ASSERT( nNo==HeadLeft||nNo==HeadRight);
	char ez[256]={""};//ly 20110404

	if(nNo==0){
		return m_lLongPathLaserDrillPosL;
	}
	else if(nNo ==1)
	{
		return m_lLongPathLaserDrillPosR;
	}
	else
	{	
		strncpy(ez,GetLang().GetWarningText(21072),256);
		AfxMessageBox(ez);//"LongPathLaserProcFocus序号超出范围!"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21071),256);
		tempstr.Format(ez,nNo);//"引进的LaserHead是 :%d"
		GetLog().Append_pro(10097,"GetLongPathLaserProcFocus");//"LaserHead超出范围"
#endif
		return -1;
	}
}
void SystemDoc::SetLaserProcFocus(long lPos,int nNo)
{
	ASSERT( nNo==HeadLeft||nNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if(nNo==0)
	{
#ifdef USELOG
		if(m_lLaserDrillPosL!=lPos)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_lLaserDrillPosL);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,lPos);//"后:%d"

			GetLog().Append_pro(AfterStr,20072,BeforeStr);//"左头激光焦距改变"
		}
#endif
		m_lLaserDrillPosL = lPos;
	}
	else if(nNo ==1)
	{
#ifdef USELOG
		if(m_lLaserDrillPosR!=lPos)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_lLaserDrillPosR);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,lPos);//"后:%d"

			GetLog().Append_pro(AfterStr,20073,BeforeStr);//"右头激光焦距改变"
		}
#endif
		m_lLaserDrillPosR = lPos;
	}
}

void SystemDoc::SetLongPathLaserProcFocus(long lPos,int nNo)
{
	ASSERT( nNo==HeadLeft||nNo==HeadRight);
	char ez[256]={""};//ly 20110404
	if(nNo==0)
	{
#ifdef USELOG
		if(m_lLongPathLaserDrillPosL!=lPos)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_lLongPathLaserDrillPosL);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,lPos);//"后:%d"

			GetLog().Append_pro(AfterStr,20074,BeforeStr);//"左头长路径激光焦距改变"
		}
#endif
		m_lLongPathLaserDrillPosL = lPos;
	}
	else if(nNo ==1)
	{
#ifdef USELOG
		if(m_lLongPathLaserDrillPosR!=lPos)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_lLongPathLaserDrillPosR);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,lPos);//"后:%d"

			GetLog().Append_pro(AfterStr,20075,BeforeStr);//"右头长路径激光焦距改变"
		}
#endif
		m_lLongPathLaserDrillPosR = lPos;
	}
}

BOOL SystemDoc::InitializeSysDoc()
{
	if(!LoadVersionParam())
		return FALSE;

	if(!LoadMotionParam())
		return FALSE;

	if(!LoadProcessParam())
		return FALSE;

	if(!LoadCCDLuminancePara())
		return FALSE;

	if (!LoadWebServiceParam())
	{
		return FALSE;
	}
	
	if(!ReadCaliTimes())
		return FALSE;

#ifdef HIKAGV
	if (!LoadPartnerParam())
		return FALSE;
#endif

	return TRUE;
}

BOOL SystemDoc::ReleaseSysDoc()
{
//	SaveVersionParam();
	SaveMotionParam();
	SaveProcessParam();
//	SaveCCDLuminancePara();
//	WriteCaliTimes();

//	GetPointcontrlView().SaveToolColorToFile();
//	GetPointcontrlView().SaveAssisCrInfo();

	return TRUE;
}

BOOL SystemDoc::LoadMotionParam()
{
	CIniFile IniFile;
	CString str,path;
	char buf[16];
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\MotionPara");
	IniFile.SetPath(path);       

	BOOL bExist=IniFile.OpenIniFileForRead();
/*
	if(!bExist)
	{
		IniFile.SetName("param\\MotionParaBack");
		IniFile.SetPath(path);        

		bExist=IniFile.OpenIniFileForRead();
		if(!bExist)
		{
			strncpy(ez,GetLang().GetWarningText(13011),256);
			AfxMessageBox(ez,MB_OK);//"无法导入运动参数！"
#ifdef USELOG
			GetLog().Append_pro(10098,"LoadMotionParam");//"无法导入运动参数"
#endif
			return false;
		}
	}
*/
	if(bExist)
	{
		for(int i = 0; i<AXISNUM;++i)
		{
			sprintf(buf,"Axis%d\0",i);
		    if(!IniFile.GetItemInt(buf,"Start",GetMotionPara(i).lStart))
				GetMotionPara(i).lStart = 10000;	
		    if(!IniFile.GetItemInt(buf,"Max",GetMotionPara(i).lMax))
				GetMotionPara(i).lMax = 20000;	
		    if(!IniFile.GetItemInt(buf,"Acc",GetMotionPara(i).lAcc))
				GetMotionPara(i).lAcc = 1000;	
		    if(!IniFile.GetItemInt(buf,"Dec",GetMotionPara(i).lDec))
				GetMotionPara(i).lDec = 1000;	
		}

		// X 轴误差补偿值
		long nPosition;
		double dbErr;
		
		if(!IniFile.GetItemInt("AxisXPosErr","Interval",m_AxisXPosErr.nInterval))
			return false;
		if(!IniFile.GetItemInt("AxisXPosErr","Counter",m_AxisXPosErr.nCounters))
			return false;
		/*if(!IniFile.GetItemInt("AxisXPosErr","start",m_AxisXPosErr.nStart))//ly add 20110310
			m_AxisXPosErr.nStart=340000;//return false;//ly change 20111212
		if(!IniFile.GetItemInt("AxisXPosErr","end",m_AxisXPosErr.nEnd))//ly add 20110310
			m_AxisXPosErr.nEnd=-340000;//return false;//ly change 20111212  */
		m_AxisXPosErr.MaxRange=m_AxisXPosErr.nInterval*(m_AxisXPosErr.nCounters-1)/2;


        for(int n=0; n<m_AxisXPosErr.nCounters;++n)
		{
			sprintf(buf,"Position%d\0",n);
			if(!IniFile.GetItemInt("AxisXPosErr",buf,nPosition))
			   nPosition = n*m_AxisXPosErr.nInterval;
	
			sprintf(buf,"Err%d\0",n);
			if(!IniFile.GetItemF64("AxisXPosErr",buf,dbErr))
			   dbErr = 0;
            if(abs(dbErr)>TABLECOMPRANGE)
			{
				char ez[256]={""};//ly 20110404
				strncpy(ez,GetLang().GetWarningText(21073),256);
				AfxMessageBox(ez);//"请运动前检查运动补偿值"
#ifdef USELOG
				GetLog().Append_pro(10099,"LoadMotionParam");//"请运动前检查运动补偿值"
#endif
			}
			m_AxisXPosErr.PositionErr.push_back(PosErr(nPosition,dbErr));
		}

		if(!IniFile.GetItemInt("AxisYPosErr","Interval",m_AxisYPosErr.nInterval))
			return false;
		if(!IniFile.GetItemInt("AxisYPosErr","Counter",m_AxisYPosErr.nCounters))
			return false;
	/*	if(!IniFile.GetItemInt("AxisYPosErr","start",m_AxisYPosErr.nStart))//ly add 20110310
			m_AxisYPosErr.nStart=-480000;//return false;//ly change 20111212
		if(!IniFile.GetItemInt("AxisYPosErr","end",m_AxisYPosErr.nEnd))//ly add 20110310
			m_AxisYPosErr.nEnd=450000;//return false;//ly change 20111212*/
		m_AxisYPosErr.MaxRange=m_AxisYPosErr.nInterval*(m_AxisYPosErr.nCounters-1)/2;

        for(n=0; n<m_AxisYPosErr.nCounters;++n)
		{			
			sprintf(buf,"Position%d\0",n);
			if(!IniFile.GetItemInt("AxisYPosErr",buf,nPosition))
			   nPosition = n*m_AxisXPosErr.nInterval;
	
			sprintf(buf,"Err%d\0",n);
			if(!IniFile.GetItemF64("AxisYPosErr",buf,dbErr))
			   dbErr = 0;
            if(abs(dbErr)>TABLECOMPRANGE)
			{
				char ez[256]={""};//ly 20110404
				strncpy(ez,GetLang().GetWarningText(21073),256);
				AfxMessageBox(ez);//"请运动前检查运动补偿值"
#ifdef USELOG
				GetLog().Append_pro(10099,"LoadMotionParam");//"请运动前检查运动补偿值"
#endif
			}

			m_AxisYPosErr.PositionErr.push_back(PosErr(nPosition,dbErr));
		
		}
        //BET				
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"BETOFFSET%d\0",n);
			if(!IniFile.GetItemInt("BETOFFSET",buf,m_lBETOffset[n]))
				m_lBETOffset[n]=0;
		}
		//DOUBLEBET 20150911
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"BETOFFSET_2%d\0",n);
			if(!IniFile.GetItemInt("BETOFFSET",buf,m_lBETOffset2[n]))
				m_lBETOffset2[n]=0;
		}

		//////////////////////////////////////FactualAperture
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"Factual%d\0",n);
			if(!IniFile.GetItemInt("FactAperture",buf,m_lFactualAperture[n]))
				m_lFactualAperture[n]=0;
		}
		//DOUBLEBET 20150911
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"Factual_2%d\0",n);
			if(!IniFile.GetItemInt("FactAperture",buf,m_lFactualAperture2[n]))
				m_lFactualAperture2[n]=0;
		}
		/////////////////////////////////////////////////
		
		//运动控制卡号；
		if(!IniFile.GetItemInt("MotionCardSn","CardSn1",GetDoc().m_lMotionCardSn1))
			this->m_lMotionCardSn1 = 0;
		if(!IniFile.GetItemInt("MotionCardSn","CardSn2",GetDoc().m_lMotionCardSn2))
			this->m_lMotionCardSn2 = 0;
		if(!IniFile.GetItemInt("MotionCardSn","CardSn3",GetDoc().m_lMotionCardSn3))
			this->m_lMotionCardSn3 = 0;

		//AVT相机SN号																				//20170829
		if(!IniFile.GetItemString("AVTCameraSN","Camera1SNHigh",GetDoc().m_strCameraSNHigh[0]))		
			this->m_strCameraSNHigh[0] = "";
		if(!IniFile.GetItemString("AVTCameraSN","Camera1SNLow",GetDoc().m_strCameraSNLow[0]))
			this->m_strCameraSNLow[0] = "";
		if(!IniFile.GetItemString("AVTCameraSN","Camera2SNHigh",GetDoc().m_strCameraSNHigh[1]))
			this->m_strCameraSNHigh[1] = "";
		if(!IniFile.GetItemString("AVTCameraSN","Camera2SNLow",GetDoc().m_strCameraSNLow[1]))
			this->m_strCameraSNLow[1] = "";

		IniFile.CloseIniFile();		
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13011),256);
		AfxMessageBox(ez,MB_OK);//"无法导入运动参数！"
#ifdef USELOG
		GetLog().Append_pro(10098,"LoadMotionParam");//"无法导入运动参数"
#endif
		return false;
	}

	return TRUE;
}

BOOL SystemDoc::SaveMotionParam() const
{
	CIniFile IniFile;
	CString str,path;
	char buf[16];
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\MotionPara");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		for(int i = 0; i<AXISNUM;++i)
		{
			sprintf(buf,"Axis%d\0",i);
			IniFile.WriteSection(buf);
			IniFile.WriteItemInt("Start",GetMotionPara(i).lStart);
			IniFile.WriteItemInt("Max",GetMotionPara(i).lMax);
			IniFile.WriteItemInt("Acc",GetMotionPara(i).lAcc);
			IniFile.WriteItemInt("Dec",GetMotionPara(i).lDec);
			IniFile.WriteString("\n");
		}

		// X 轴误差补偿值
		IniFile.WriteSection("AxisXPosErr");
		IniFile.WriteItemInt("Interval",m_AxisXPosErr.nInterval);
		IniFile.WriteItemInt("Counter",m_AxisXPosErr.nCounters);
		/*IniFile.WriteItemInt("start",m_AxisXPosErr.nStart);//ly add 20110310
		IniFile.WriteItemInt("end",m_AxisXPosErr.nEnd);//ly add 20110310*/
//		IniFile.WriteItemInt("Range",m_AxisXPosErr.MaxRange);
 		IniFile.WriteString("\n");
       
	    for(int n=0; n<m_AxisXPosErr.PositionErr.size();n++)
		{
			PosErr posErr = m_AxisXPosErr.PositionErr[n];
			
			sprintf(buf,"Position%d\0",n);
			IniFile.WriteItemInt(buf,m_AxisXPosErr.PositionErr[n].nPos);
			sprintf(buf,"Err%d\0",n);
			IniFile.WriteItemF64(buf,m_AxisXPosErr.PositionErr[n].dbErr);
		}
		IniFile.WriteString("\n");
		// Y 轴误差补偿值
		IniFile.WriteSection("AxisYPosErr");
		IniFile.WriteItemInt("Interval",m_AxisYPosErr.nInterval);
		IniFile.WriteItemInt("Counter",m_AxisYPosErr.nCounters);
		/*IniFile.WriteItemInt("start",m_AxisYPosErr.nStart);//ly add 20110310
		IniFile.WriteItemInt("end",m_AxisYPosErr.nEnd);//ly add 20110310*/
//		IniFile.WriteItemInt("Range",m_AxisYPosErr.MaxRange);
  		IniFile.WriteString("\n");
      
	    for(n=0; n<m_AxisYPosErr.PositionErr.size();n++)
		{
			sprintf(buf,"Position%d\0",n);
			IniFile.WriteItemInt(buf,m_AxisYPosErr.PositionErr[n].nPos);
			sprintf(buf,"Err%d\0",n);
			IniFile.WriteItemF64(buf,m_AxisYPosErr.PositionErr[n].dbErr);
		}
		IniFile.WriteString("\n");

		IniFile.WriteSection("MotionCardSn");
		IniFile.WriteItemInt("CardSn1",   GetDoc().m_lMotionCardSn1);
		IniFile.WriteItemInt("CardSn2",   GetDoc().m_lMotionCardSn2);
		IniFile.WriteItemInt("CardSn3",   GetDoc().m_lMotionCardSn3);
		IniFile.WriteString("\n");

		//AVT相机SN号																	//20170829
		IniFile.WriteSection("AVTCameraSN");
		IniFile.WriteItemString("Camera1SNHigh",   GetDoc().m_strCameraSNHigh[0]);
		IniFile.WriteItemString("Camera1SNLow",   GetDoc().m_strCameraSNLow[0]);
		IniFile.WriteItemString("Camera2SNHigh",   GetDoc().m_strCameraSNHigh[1]);
		IniFile.WriteItemString("Camera2SNLow",   GetDoc().m_strCameraSNLow[1]);
		IniFile.WriteString("\n");		

		IniFile.WriteSection("BETOFFSET");
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"BETOFFSET%d\0",n);
			IniFile.WriteItemInt(buf,m_lBETOffset[n]);
		}
		//DOUBLEBET 20150911
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"BETOFFSET_2%d\0",n);
			IniFile.WriteItemInt(buf,m_lBETOffset2[n]);
		}		
//////////////////////////////////////////////////////////////FactualAperture
		IniFile.WriteString("\n");
		IniFile.WriteSection("FactAperture");
	    for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"Factual%d\0",n);
			IniFile.WriteItemInt(buf,m_lFactualAperture[n]);
		}
		//DOUBLEBET 20150911
		for(n=0; n<APTNUM; n++)
		{
			sprintf(buf,"Factual_2%d\0",n);
			IniFile.WriteItemInt(buf,m_lFactualAperture2[n]);
		}

  		IniFile.WriteString("\n");

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13012),256);
		AfxMessageBox(ez,MB_OK);//"无法保存 运动参数！"
#ifdef USELOG
		GetLog().Append_pro(10100,"SaveMotionParam");//"无法保存 运动参数"
#endif
	}

	return TRUE;
}


BOOL SystemDoc::SaveWebServiceParam() const
{
	CIniFile IniFile;
	CString str,path;
	char buf[16];
	char ez[256]={"无法保存 WebService参数"};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\WebServicePara");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		//WebService参数																
		IniFile.WriteSection("WebService");
		IniFile.WriteItemString("MachineSn",		GetDoc().m_strSysMachineSn);
		IniFile.WriteItemString("ImesURL",			GetDoc().m_strSysImesURL);
		IniFile.WriteItemInt("Timeout",				GetDoc().m_strSysTimeout);
		IniFile.WriteItemInt("IdtTime",				GetDoc().m_strSysIdtTime);
		IniFile.WriteItemInt("ModeSwitch",			GetDoc().m_SysModeSwitch);
		IniFile.WriteItemInt("UserControlSwitch",	GetDoc().m_SysUserControlSwitch);
		IniFile.WriteItemString("HeartbeatContent", GetDoc().m_strSysHeartbeatContent);
		IniFile.WriteItemString("HeartbeatFreq",	GetDoc().m_strSysHeartbeatFreq);

		IniFile.WriteString("\n");	
		
		//IngredientExplainSet
		char buf[16];
		std::vector<IngredientExplainSet>::iterator isv;
		IniFile.WriteSection("IngredientExplainSet");
		IniFile.WriteItemInt("ItemCount" ,GetDoc().GetSysIngredientExplainSetSize());
  	    IniFile.WriteString("\n");

	    for(int nn=0; nn<GetDoc().GetSysIngredientExplainSetSize();nn++)
		{
			isv=GetDoc().GetSysIngredientExplainSet(nn);

			sprintf(buf,"Label%d\0",nn);
			IniFile.WriteItemString(buf,isv->strLabel);
			sprintf(buf,"Explain%d\0",nn);
			IniFile.WriteItemString(buf,isv->strExplain);
  			IniFile.WriteString("\n");
		}

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13012),256);
		AfxMessageBox(ez,MB_OK);//"无法保存 WebService参数！"
#ifdef USELOG
		GetLog().Append_pro("无法保存 WebService参数","SaveMotionParam","");//"无法保存 WebService参数"
#endif
	}

	return TRUE;
}


BOOL SystemDoc::LoadVersionParam()
{
	CIniFile IniFile;
	CString str,path;
	long ltmp = 0;
	double dTemp=0.0;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\VersionPara");
	IniFile.SetPath(path);
	
	m_strAppPath = path;                   // 应用文件的执行路径   

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		long temp;
		double temp1;
//------------------------------------------------------------------------------//20160919
		if(!IniFile.GetItemInt("VersionConfig",	 "DeadTime",  temp))			
			temp = 0;//信息输入输出模式
		GetDoc().SetHdSysDeadTime(temp);

		if(!IniFile.GetItemInt("VersionConfig",	 "LaserTriggerAdjust",  temp))
			temp = 0;//信息输入输出模式
		GetDoc().SetHdSysLaserTriggerAdjust(temp);

		if(!IniFile.GetItemInt("VersionConfig",	 "PulseMode",  temp))			
			temp = 0;//信息输入输出模式
		GetDoc().SetHdSysPulseMode(temp);

		if(!IniFile.GetItemInt("VersionConfig",	 "AOMOnDelay",  temp))			
			temp = 14;//信息输入输出模式
//		if(temp<14)															//20190220 同步控制方式下进行了取消
//			temp = 14;
		GetDoc().SetHdSysAOMOnDelay(temp);

		if(!IniFile.GetItemInt("VersionConfig",	 "AOMOffAhead",  temp))			
			temp = 2;//信息输入输出模式
//		if(temp<2)
//			temp = 2;
		GetDoc().SetHdSysAOMOffAhead(temp);

		if(!IniFile.GetItemF64("VersionConfig",	 "LaserMAXDutyCycle",  temp1))			
			temp1 = 0.09;//信息输入输出模式
		GetDoc().SetHdSysLaserMAXDutyCycle(temp1);

		if(!IniFile.GetItemInt("VersionConfig",	 "MINLaserPeriod",  m_iMINlaserPeriod))		//20191219 增加
			m_iMINlaserPeriod =200;
//----------------------------------------------------------------------------------------
		if(!IniFile.GetItemInt("UI",	 "ManualSetScaleFlag",  temp))
			temp = 0;//0:手动设置涨缩不显示
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetUIManSetScale(temp);

		if(!IniFile.GetItemInt("UI",	 "ScaleUnitFlag",  temp))
			temp = 0;//0:涨缩单位选择不显示
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetScaleUnit(temp);

		if(!IniFile.GetItemInt("UI",	 "PowerMaxFlag",  temp))
			temp = 0;//0:功率上限不显示
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetPowerMax(temp);
//------------------------------------------------------------------------------------------
		if(!IniFile.GetItemInt("HW",	 "USE9112",  temp))
			temp = 1;//1:有9112卡
// 		if(temp!=0)
// 		{
// 			temp =1;
// 		}
		GetDoc().SetUse9112(temp);

		if(!IniFile.GetItemInt("HW",	 "ProcAOMLaserOnDelay",  GetDoc().m_AOMLaserOnDelay))//jpc add 20130815
			GetDoc().m_AOMLaserOnDelay =25;
		if(!IniFile.GetItemInt("HW",	 "ProcAOMLaserOffDelay",  GetDoc().m_AOMLaserOffDelay))
			GetDoc().m_AOMLaserOffDelay =4;

		if(!IniFile.GetItemInt("HW",	 "TableClamp",  temp))
			temp = 0;//0:不带夹钳
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetTableClamp(temp);

		if(!IniFile.GetItemInt("HW",	 "LaserPowerPattern",  temp))//jpc add 20130806
			temp = 0;//0:采用信号测试激光功率
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetLaserPowerPattern(temp);	

		if(!IniFile.GetItemInt("HW",	 "WaterYBJ",  temp))
			temp = 0;//0:无冷水机预报警
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetWaterYBJ(temp);

		if(!IniFile.GetItemInt("HW",	 "ScanSizeMax",  temp))//ly add 20140306
			temp = 65;//最大振镜分区范围
		GetDoc().SetScanSizeMax(temp);

		if(!IniFile.GetItemInt("HW",	 "MatrixRange",  temp))//20150129
			temp = 57000;//替换原来校正范围，这样避免版本问题
		if (temp<30000 || temp>70000)
			temp = 57000;//替换原来校正范围，这样避免版本问题
		GetDoc().SetDefineMatrixRange(temp);

		if(!IniFile.GetItemInt("HW",	 "ScanlabDeadTime",  temp))//20150129
			temp = 60;
		//if (temp<50 || temp>80)
		if (temp>80)
			 m_iScanlabDeadTime = 60;
		else if (temp<50)
			m_iScanlabDeadTime=0;
		else
			 m_iScanlabDeadTime=temp;
	
		if(!IniFile.GetItemInt("HW",	 "LargeTable",  temp))//ly add 20140306
			temp = 0;//0:正常平台大小   1:815大台面
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetLargeTable(temp);

		if(!IniFile.GetItemInt("HW",	 "DoorOpenWarning",  temp))//ly add 20140306
			temp = 0;//0:没有门打开报警功能，采用安全门对射被挡报警  1：门打开就报警，不用安全门对射报警信号，需要硬件更新。
		GetDoc().SetDoorOpenWarning(temp);

		if(!IniFile.GetItemInt("HW",	 "Infrared",  temp))//ly add 20140306
			temp = 0;//0:没有红外光源  1：红外光源生效。
		GetDoc().SetInfrared(temp);

		if(!IniFile.GetItemInt("HW",	 "HandCOMSerialNumber",  temp))//ly add 20140306
			temp = 2;//
		if(temp>10 || temp<0)
			temp=2;
		GetDoc().SetHandCOMNum(temp);

		if(!IniFile.GetItemInt("HW",	 "PowerCOMSerialNumber",  temp))//ly add 20140306
			temp = 3;//
		if(temp>10 || temp<0)
			temp=3;
		GetDoc().SetPowerCOMNum(temp);		

		if(!IniFile.GetItemInt("HW",	 "LANDULSYSTEM",  m_iLAndULSystem))		//20191219 增加
			m_iLAndULSystem =1;
//-----------------------------------------------------------------------------------------
		if(!IniFile.GetItemInt("Func",	 "FZInnerMark",  temp))
			temp = 0;//0:方正内标靶方式不启用
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetFZInnerMark(temp);

		if(!IniFile.GetItemInt("Func",	 "ZHANHUARotate",  temp))
			temp = 0;//展华旋转
		if(temp!=0)
		{
			temp =1;
		}
		m_bZHANHUARotate=temp;
		//GetDoc().SetZHANHUARotate(temp);


		//顺络涨缩scale
		if(!IniFile.GetItemInt("Func",	 "ShunluoScale",  temp))
			temp = 0;//顺络涨缩
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetShunluoScale(temp);	
		

		//深蓝允许三标靶模式，高级下面屏蔽
		if(!IniFile.GetItemInt("Func",	 "ShenLan3Fid",  temp))
			temp = 0;
		if(temp>3 || temp<0)
		{
			temp =0;
		}
		GetDoc().SetShenLan3Fid(temp);	


		if(!IniFile.GetItemInt("Func",	 "GYDMIRROR",  temp))
			temp = 0;//0:光韵达模式
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetGYDMirror(temp);

		
		if(!IniFile.GetItemInt("Func",	 "OverBorad",  temp))
			temp = 0;//1：翻板机功能
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetFunctionOverBorad(temp);


		if(!IniFile.GetItemInt("Func",	 "ShowTool",  temp))//ly add 20140520
			temp = 0;//0:点击开始，直接加工    1：点击“开始”，先进入刀具设置页面，确认刀具参数ok，然后开始。
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetShowTool(temp);

		if(!IniFile.GetItemInt("Func",	 "LoadAfterPitch",  temp))//ly add 20140520
			temp = 0;//0:点击开始，直接加工    1：点击“开始”，先进入刀具设置页面，确认刀具参数ok，然后开始。
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetLoadAfterPitch(temp);

		if(!IniFile.GetItemInt("Func",	 "FileLPTest",  temp))//ly add 20130801
			temp = 0;//1:超毅功率测试时，使用文件刀具信息做测试
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetFileLPTest(temp);

		if(!IniFile.GetItemInt("Func",	 "FitBit",  temp))//ly add 20130724
			temp = 1;//0:比特率匹配方式不启用，默认启用比特率匹配
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetFitBit(temp);

		if(!IniFile.GetItemInt("Func",	 "FitApt",  temp))//ly add 20131223
			temp = 0;//0:延时根据光圈大小选择延时时间，0表示不按光圈大小，采取统一首发延时。   1：首发延时按照光圈分别设置延时。延时时间放在AptPower.ini内。
		if(temp!=0)
		{
			temp =1;
			if(!GetDoc().GetAptDelayFile())//ly add 20140126
				return false;
		}
		GetDoc().SetFitApt(temp);

		if(!IniFile.GetItemInt("Func",	 "DrillInc",  temp))//ly add 20131223
			temp = 0;//0:流水号递加，左轴1，右轴2，左轴3，右轴4……   1：流水号左右轴1致，左轴1，右轴1，左轴2，右轴2……如遇左轴NG空出，如无左轴3，只有右轴3，然后左轴4，右轴4……
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetDrillInc(temp);

		//DrillH01H02
		if(!IniFile.GetItemInt("Func",	 "DrillH01H02",  temp))//ly add 20131223
			temp = 0;//0:流水号递加，左轴1，右轴2，左轴3，右轴4……   1：流水号左右轴1致，左轴1，右轴1，左轴2，右轴2……如遇左轴NG空出，如无左轴3，只有右轴3，然后左轴4，右轴4……
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetDrillH01H02(temp);


       	//LaserPowerMode
		if(!IniFile.GetItemInt("Func",	 "LaserPowerMode",  temp))
			temp = 0;//激光功率测试加工模式
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetLaserPowerMode(temp);

		if(!IniFile.GetItemInt("Func",	 "LaserPowerShow",  temp))
			temp = 0;//激光功率测试作假
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetLaserPowerShow(temp);
		
		if(!IniFile.GetItemInt("Func",	 "LaserPowerDelayTime",  temp))
			temp = 0;//激光功率延时
		if(temp<0 || temp>1000)
		{
			temp =0;
		}
		GetDoc().SetLaserPowerDelayTime(temp);

		if(!IniFile.GetItemInt("Func",	 "LaserPowerTimes",  temp))
			temp = 0;//激光功率测量次数 
		if(temp<1 || temp>4)
			temp =1;		
		GetDoc().SetLaserPowerTimes(temp);

		if(!IniFile.GetItemInt("Func",	 "BurstMode",  temp))
			temp = 0;//激光功率测试加工模式
		if(temp!=0)
		{
			temp =1;
		}
		GetDoc().SetBunchMode(temp);

		if(!IniFile.GetItemInt("Func",	 "InfoDBMode",  temp))			//20160901
			temp = 0;//信息输入输出模式
		GetDoc().SetSysInfoDBMode(temp);

		if(!IniFile.GetItemInt("Func",	 "ProcAxisMode",  temp))		//20191015 增加 0：双轴；1：左轴；2：右轴
			temp = 0;//加工时的轴模式
		if(temp>2)
			temp =0;
		GetDoc().SetProcAxisSelected(temp);

		if(!IniFile.GetItemInt("Func",	 "UNLOADISOK",  m_iUnloadIsOK))				//20191219 增加
			m_iUnloadIsOK =1;

		if(!IniFile.GetItemInt("Func",	 "TABLEABSORBFIRST",  m_iTableAbsorbFirst))
			m_iTableAbsorbFirst =1;

		if(!IniFile.GetItemInt("Func",	 "CUSTOMERSPECIAL",  m_iCustomerSpecial))	//0:标准 1:崇达 2:志浩 3:红板 4:方正	//20200326 增加	//20200921 增加
			m_iCustomerSpecial =0;
//--------------------------------------------------------------------------------------------
		if(!IniFile.GetItemInt("BET",	 "BET1F",  GetDoc().m_lBET1F))
			GetDoc().m_lBET1F = 100;//
		if(!IniFile.GetItemInt("BET",	 "BET2F",  GetDoc().m_lBET2F))
			GetDoc().m_lBET2F = 80;//
		if(!IniFile.GetItemInt("BET",	 "BET3F",  GetDoc().m_lBET3F))
			GetDoc().m_lBET3F = -150;//
		if(!IniFile.GetItemF64("BET",	 "BET1TOBET2",  GetDoc().m_dBET1TOBET2))
			GetDoc().m_dBET1TOBET2 = 30.0;//
		if(!IniFile.GetItemF64("BET",	 "BET2TOBET3",  GetDoc().m_dBET2TOBET3))
			GetDoc().m_dBET2TOBET3 = 244.0;//
		if(!IniFile.GetItemInt("BET",	 "BETMAX",  GetDoc().m_lBETMAX))
			GetDoc().m_lBETMAX = 50000;//

/*//20180611 由于L2需求进行取消更改
		if((GetDoc().m_lBET1F != 100)&&(GetDoc().m_lBET1F != 90)&&(GetDoc().m_lBET1F != 80))
		{
			strncpy(ez,GetLang().GetWarningText(13023),256);
			AfxMessageBox(ez,MB_OK);
			return false;
		}
		if(GetDoc().m_lBET2F != 80 && GetDoc().m_lBET2F != 100 && GetDoc().m_lBET2F != 90)
		{
			strncpy(ez,GetLang().GetWarningText(13024),256);
			AfxMessageBox(ez,MB_OK);
			return false;
		}
		if(GetDoc().m_lBET3F != -150)
		{
			strncpy(ez,GetLang().GetWarningText(13025),256);
			AfxMessageBox(ez,MB_OK);
			return false;
		}
		if(!((fabs(GetDoc().m_dBET1TOBET2-30)>0.0001)||(fabs(GetDoc().m_dBET1TOBET2-50)>0.0001)))
		{
			strncpy(ez,GetLang().GetWarningText(13026),256);
			AfxMessageBox(ez,MB_OK);
			return false;
		}
		if(!((fabs(GetDoc().m_dBET2TOBET3-233.3)>0.0001)||(fabs(GetDoc().m_dBET2TOBET3-234.0)>0.0001)||(fabs(GetDoc().m_dBET2TOBET3-244.0)>0.0001)||(fabs(GetDoc().m_dBET2TOBET3-300.0)>0.0001)))
		{
			strncpy(ez,GetLang().GetWarningText(13027),256);
			AfxMessageBox(ez,MB_OK);
			return false;
		}
		if((GetDoc().m_lBETMAX != 50000)&&(GetDoc().m_lBETMAX != 80000)&&(GetDoc().m_lBETMAX != 30000)&&(GetDoc().m_lBETMAX != 67000)&&(GetDoc().m_lBETMAX != 87000))
		{
			strncpy(ez,GetLang().GetWarningText(13028),256);
			AfxMessageBox(ez,MB_OK);
			return false;
		}
*/
		if(!IniFile.GetItemInt("TableConfig",	 "FORWARDX", m_AxisXPosErr.nStart ))
			m_AxisXPosErr.nStart=350000;
		if(!IniFile.GetItemInt("TableConfig",	 "REVERSEX",  m_AxisXPosErr.nEnd))
			m_AxisXPosErr.nEnd=-350000;
		if(!IniFile.GetItemInt("TableConfig",	 "FORWARDY",  m_AxisYPosErr.nEnd))
			m_AxisYPosErr.nEnd=460000;
		if(!IniFile.GetItemInt("TableConfig",	 "REVERSEY",  m_AxisYPosErr.nStart))
			m_AxisYPosErr.nStart=-490000;

		GetDoc().SetFORWARDX(m_AxisXPosErr.nStart);
		GetDoc().SetREVERSEX(m_AxisXPosErr.nEnd);
		GetDoc().SetFORWARDY(m_AxisYPosErr.nEnd);
		GetDoc().SetREVERSEY(m_AxisYPosErr.nStart);

		if(!IniFile.GetItemInt("ZAxisConfig",	 "FORWARDZ", m_lFORWARDZ ))			//20180912
			m_lFORWARDZ=55000;

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13021),256);
		AfxMessageBox(ez,MB_OK);//"无法导入版本参数！"
#ifdef USELOG
		GetLog().Append_pro(10115,"LoadVersionParam");//"无法导入版本参数"
#endif
		return false;
	}

	return true;
}

BOOL SystemDoc::LoadProcessParam()
{
	CIniFile IniFile;
	CString str,path;
	long ltmp = 0;
	double dTemp=0.0;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\ProcessPara");
	IniFile.SetPath(path);       

	BOOL bExist=IniFile.OpenIniFileForRead();
/*
	if(!bExist)
	{
		IniFile.SetName("param\\ProcessParaBack");
		IniFile.SetPath(path);      

		bExist=IniFile.OpenIniFileForRead();
		if(!bExist)
		{
			strncpy(ez,GetLang().GetWarningText(13013),256);
			AfxMessageBox(ez,MB_OK);//"无法导入加工参数！"
#ifdef USELOG
			GetLog().Append_pro(10101,"SaveMotionParam");//"无法导入加工参数"
#endif
			return false;
		}
	}
*/
	if(bExist)
	{
		// 有关CCD 参数
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset1_X",  GetDoc().m_triTestCCDToGlvOffL.x))
			GetDoc().m_triTestCCDToGlvOffL.x = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset1_Y",  GetDoc().m_triTestCCDToGlvOffL.y))
			GetDoc().m_triTestCCDToGlvOffL.y = 10000;
		if(!IniFile.GetItemInt ("CCDToGlvOffset","CCDOffset1_X",  GetDoc().m_triTestCCDToCCDOffL.x))
			GetDoc().m_triTestCCDToCCDOffL.x = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","CCDOffset1_Y",  GetDoc().m_triTestCCDToCCDOffL.y))
			GetDoc().m_triTestCCDToCCDOffL.y = 10000;

		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset1_Z",  GetDoc().m_triTestCCDToGlvOffL.z))
			GetDoc().m_triTestCCDToGlvOffL.z = 10000;
				
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset1_LongPathX",  GetDoc().m_triTestLongPathCCDToGlvOffL.x))
			GetDoc().m_triTestLongPathCCDToGlvOffL.x = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset1_LongPathY",  GetDoc().m_triTestLongPathCCDToGlvOffL.y))
			GetDoc().m_triTestLongPathCCDToGlvOffL.y = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset1_LongPathZ",  GetDoc().m_triTestLongPathCCDToGlvOffL.z))
			GetDoc().m_triTestLongPathCCDToGlvOffL.z = 10000;
		
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset2_X",  GetDoc().m_triTestCCDToGlvOffR.x))
			GetDoc().m_triTestCCDToGlvOffR.x = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset2_Y",  GetDoc().m_triTestCCDToGlvOffR.y))
			GetDoc().m_triTestCCDToGlvOffR.y = 10000;
		if(!IniFile.GetItemInt ("CCDToGlvOffset","CCDOffset2_X",  GetDoc().m_triTestCCDToCCDOffR.x))
			GetDoc().m_triTestCCDToCCDOffR.x = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","CCDOffset2_Y",  GetDoc().m_triTestCCDToCCDOffR.y))
			GetDoc().m_triTestCCDToCCDOffR.y = 10000;

		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset2_Z",  GetDoc().m_triTestCCDToGlvOffR.z))
			GetDoc().m_triTestCCDToGlvOffR.z = 10000;	

			if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset2_LongPathX",  GetDoc().m_triTestLongPathCCDToGlvOffR.x))
			GetDoc().m_triTestLongPathCCDToGlvOffR.x = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset2_LongPathY",  GetDoc().m_triTestLongPathCCDToGlvOffR.y))
			GetDoc().m_triTestLongPathCCDToGlvOffR.y = 10000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","Offset2_LongPathZ",  GetDoc().m_triTestLongPathCCDToGlvOffR.z))
			GetDoc().m_triTestLongPathCCDToGlvOffR.z = 10000;
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetLT_SX",  GetDoc().m_triSCCDToGlvSysOffsetLT.x))
			GetDoc().m_triSCCDToGlvSysOffsetLT.x = 0;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetLT_SY",  GetDoc().m_triSCCDToGlvSysOffsetLT.y))
			GetDoc().m_triSCCDToGlvSysOffsetLT.y = -130000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetLT_SZA", GetDoc().m_triSCCDToGlvSysOffsetLT.z))
			GetDoc().m_triSCCDToGlvSysOffsetLT.z = 2000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetLT_LX",  GetDoc().m_triLCCDToGlvSysOffsetLT.x))
			GetDoc().m_triLCCDToGlvSysOffsetLT.x = 0;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetLT_LY",  GetDoc().m_triLCCDToGlvSysOffsetLT.y))
			GetDoc().m_triLCCDToGlvSysOffsetLT.y = -130000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetLT_LZA", GetDoc().m_triLCCDToGlvSysOffsetLT.z))
			GetDoc().m_triLCCDToGlvSysOffsetLT.z = 2000;

		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetRT_SX",  GetDoc().m_triSCCDToGlvSysOffsetRT.x))
			GetDoc().m_triSCCDToGlvSysOffsetRT.x = 0;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetRT_SY",  GetDoc().m_triSCCDToGlvSysOffsetRT.y))
			GetDoc().m_triSCCDToGlvSysOffsetRT.y = -130000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetRT_SZA",  GetDoc().m_triSCCDToGlvSysOffsetRT.z))
			GetDoc().m_triSCCDToGlvSysOffsetRT.z = 2000;
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetRT_LX",  GetDoc().m_triLCCDToGlvSysOffsetRT.x))
			GetDoc().m_triLCCDToGlvSysOffsetRT.x = 0;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetRT_LY",  GetDoc().m_triLCCDToGlvSysOffsetRT.y))
			GetDoc().m_triLCCDToGlvSysOffsetRT.y = -130000;	
		if(!IniFile.GetItemInt ("CCDToGlvOffset","SysOffsetRT_LZA",  GetDoc().m_triLCCDToGlvSysOffsetRT.z))
			GetDoc().m_triLCCDToGlvSysOffsetRT.z = 2000;

		if(!IniFile.GetItemInt ("LaserTestCleanRefPos","CleanRefPos_X",  GetDoc().m_crdLaserTestCleanRef.x))
			GetDoc().m_crdLaserTestCleanRef.x = 1000;	
		if(!IniFile.GetItemInt ("LaserTestCleanRefPos","CleanRefPos_Y",  GetDoc().m_crdLaserTestCleanRef.y))
			GetDoc().m_crdLaserTestCleanRef.y = 0;	
         //CCD 相对距离
		if(!IniFile.GetItemInt ("CCDDistance","CCDDistance_X",  GetDoc().m_crdCCDDistance.x))
			GetDoc().m_crdCCDDistance.x = 1200000;	
		if(!IniFile.GetItemInt ("CCDDistance","CCDDistance_Y",  GetDoc().m_crdCCDDistance.y))
			GetDoc().m_crdCCDDistance.y = 0;	
 
		// SL Bit per mm
    	if(!IniFile.GetItemInt ("SLBitPermm","SLBitPermm", GetDoc().m_ulSLBitPermm))
			GetDoc().m_ulSLBitPermm = 1000;		
 
  		//正常加工时的CCD焦距 光源亮度
		if(!IniFile.GetItemInt("CCDProcParam","CCDFocusPosL", GetDoc().m_lCCDFocusPosL))
			GetDoc().m_lCCDFocusPosL = 10000;	
		if(!IniFile.GetItemInt("CCDProcParam","CCDFocusPosR", GetDoc().m_lCCDFocusPosR))
			GetDoc().m_lCCDFocusPosR = 10000;	

		 //激光测试等
		if(!IniFile.GetItemInt("LaserProPara",  "LaserPowTestPosLX", GetDoc().m_triLaserPowerTestL.x))
			GetDoc().m_triLaserPowerTestL.x = 10000;	
		if(!IniFile.GetItemInt("LaserProPara",  "LaserPowTestPosLY", GetDoc().m_triLaserPowerTestL.y))
			GetDoc().m_triLaserPowerTestL.y = 10000;	
		if(!IniFile.GetItemInt("LaserProPara",  "LaserPowTestPosLZ", GetDoc().m_triLaserPowerTestL.z))
			GetDoc().m_triLaserPowerTestL.z = 10000;

		if(!IniFile.GetItemInt("LaserProPara",  "LaserPowTestPosRX", GetDoc().m_triLaserPowerTestR.x))
			GetDoc().m_triLaserPowerTestR.x = 10000;	
		if(!IniFile.GetItemInt("LaserProPara",  "LaserPowTestPosRY", GetDoc().m_triLaserPowerTestR.y))
			GetDoc().m_triLaserPowerTestR.y = 10000;	
		if(!IniFile.GetItemInt("LaserProPara",  "LaserPowTestPosRZ", GetDoc().m_triLaserPowerTestR.z))
			GetDoc().m_triLaserPowerTestR.z = 10000;

		//测试板厚
		if(!IniFile.GetItemInt("Other",  "TestThicknessPos", GetDoc().m_TestThicknessZPos))
			GetDoc().m_TestThicknessZPos = 1000;
        //光圈偏置
		if(!IniFile.GetItemInt("Other",  "AptOffset", GetDoc().m_lAptOffsetCrd))
			GetDoc().m_lAptOffsetCrd = 0;
		//BET偏置
		if(!IniFile.GetItemInt("Other",  "BETPRIOffset", GetDoc().m_lBETPriOffset))
			GetDoc().m_lBETPriOffset = 0;
		if(!IniFile.GetItemInt("Other",  "BETSUBOffset", GetDoc().m_lBETOffsetCrd))
			GetDoc().m_lBETOffsetCrd = 0;

		//第二套BET光圈参数
		//光圈偏置
		if(!IniFile.GetItemInt("Other",  "AptOffset2", GetDoc().m_lAptOffsetCrd2))
			GetDoc().m_lAptOffsetCrd2 = 0;
		//BET偏置
		if(!IniFile.GetItemInt("Other",  "BETPRIOffset2", GetDoc().m_lBETPriOffset2))
			GetDoc().m_lBETPriOffset2 = 0;
		if(!IniFile.GetItemInt("Other",  "BETSUBOffset2", GetDoc().m_lBETSubOffsetCrd2))
			GetDoc().m_lBETSubOffsetCrd2 = 0; 
                         


        //PCB 厚度
//		if(!IniFile.GetItemInt("Other",  "PCBThickness", GetDoc().m_lPCBThickness))
//			GetDoc().m_lPCBThickness = 1000;
		
		//加工时的焦距
		if(!IniFile.GetItemInt("LaserProPara",  "LaserDrillPosL",	GetDoc().m_lLaserDrillPosL ))
			GetDoc().m_lLaserDrillPosL = 10000;
		if(!IniFile.GetItemInt("LaserProPara",  "LaserDrillPosR",	GetDoc().m_lLaserDrillPosR ))
			GetDoc().m_lLaserDrillPosR = 10000;

		if(!IniFile.GetItemInt("LaserProPara",  "LongPathLaserDrillPosL",	GetDoc().m_lLongPathLaserDrillPosL ))
			GetDoc().m_lLongPathLaserDrillPosL = 10000;
		if(!IniFile.GetItemInt("LaserProPara",  "LongPathLaserDrillPosR",	GetDoc().m_lLongPathLaserDrillPosR ))
			GetDoc().m_lLongPathLaserDrillPosL = 10000;

		//测试用能量等
		if(!IniFile.GetItemInt("TestParam",	"TestPlsRelease", GetDoc().m_lTestPlsRelease))
			GetDoc().m_lTestPlsRelease =20;
		if(!IniFile.GetItemInt("TestParam",	"WarmUpPlsRelease", GetDoc().m_lWarmUpPlsRelease))
			GetDoc().m_lWarmUpPlsRelease =20;//机器预热
		if(!IniFile.GetItemInt("TestParam",	"TestPlsPeriod",  GetDoc().m_lTestPlsPeriod))
			GetDoc().m_lTestPlsPeriod =200;
		if(!IniFile.GetItemInt("TestParam",	"TestLaserOnTime",GetDoc().m_lTestLaserOnTime))
			GetDoc().m_lTestLaserOnTime =30;
		if(!IniFile.GetItemInt("TestParam",	"TestJumpDelay",  GetDoc().m_lTestJumpDelay))
			GetDoc().m_lTestJumpDelay =1000;
		if(!IniFile.GetItemInt("TestParam",	"TestJumpSpeed",  GetDoc().m_lTestJumpSpeed))
			GetDoc().m_lTestJumpSpeed =3000;
		if(!IniFile.GetItemInt("TestParam",	"RTC5TestBasicDelay",GetDoc().m_iRTC5TestBasicDelay))
			GetDoc().m_iRTC5TestBasicDelay =1000;
		if (GetDoc().m_iRTC5TestBasicDelay<0 || GetDoc().m_iRTC5TestBasicDelay>10000)
			GetDoc().m_iRTC5TestBasicDelay=1000;
		GetDoc().m_lTestPlsPeriod =1000;//ly add 20111208
		GetDoc().m_lTestJumpSpeed =4000;//ly add 20111208
		GetDoc().m_lTestJumpDelay =400;//ly add 20111208

		if(!IniFile.GetItemInt("TestParam","GlvAdjustApt",GetDoc().m_lGlvAdjustApt))
			GetDoc().m_lGlvAdjustApt = 8;

#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
		if(GetDoc().m_lGlvAdjustApt>8)
		{
			GetDoc().m_lGlvAdjustApt = 8;
		}
#else//ly change 20110122 12光圈
		if(GetDoc().m_lGlvAdjustApt>12)
		{
			GetDoc().m_lGlvAdjustApt = 12;
		}
#endif
#endif
		if(!IniFile.GetItemInt("DrillRegion",	"RegionDim",  GetDoc().m_iRegionDim))
			GetDoc().m_iRegionDim =1000;

		//正常加工	
		if(!IniFile.GetItemInt("ProcParam",	 "ProcJumpDelay",  GetDoc().m_lProcJumpDelay))
			GetDoc().m_lProcJumpDelay =2000;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcJumpSpeed",  GetDoc().m_lProcJumpSpeed))
			GetDoc().m_lProcJumpSpeed =2000;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcJumpDelay0",  GetDoc().m_lProcJumpDelay0))//ly add 20111123
			GetDoc().m_lProcJumpDelay0 =260;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcJumpLenth",  GetDoc().m_lProcJumpLenth))//ly add 20111123
			GetDoc().m_lProcJumpLenth =6000;
		if(!IniFile.GetItemInt("ProcParam",	 "RTC5AddBasicDelay",  GetDoc().m_iRTC5AddBasicDelay))//ly add 20111123
			GetDoc().m_iRTC5AddBasicDelay =0;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcFirstJumpDelay",  GetDoc().m_lProcFirstJumpDelay))//ly add 20111123
			GetDoc().m_lProcFirstJumpDelay =0;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcFirstDelayGap",  GetDoc().m_lProcFirstDelayGap))//ly add 20111123
			GetDoc().m_lProcFirstDelayGap =470;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcOtherJumpDelay",  GetDoc().m_lProcOtherJumpDelay))//ly add 20120811
			GetDoc().m_lProcOtherJumpDelay =0;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcOtherDelayGap",  GetDoc().m_lProcOtherDelayGap))//ly add 20120811
			GetDoc().m_lProcOtherDelayGap =300;//470->300 ly change 20130508
		if(!IniFile.GetItemInt("ProcParam",	 "ProcDelayJump",  GetDoc().m_lProcDelayJump))//ly add 20130315
			GetDoc().m_lProcDelayJump =0;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcNULLMark",  GetDoc().m_lNULLMark))//ly add 20120206
			GetDoc().m_lNULLMark =0;
		if(!IniFile.GetItemInt("ProcParam",	 "ProcTestMode",  GetDoc().m_lTestMode))//ly add 20120208
			GetDoc().m_lTestMode =0;
		if(!IniFile.GetItemInt("ProcParam",	 "OutFidsOffSet",  GetDoc().m_iOutFidsOffset))//ly add 20140504
			GetDoc().m_iOutFidsOffset = 500;
		if(GetDoc().m_iOutFidsOffset>2000)
			GetDoc().m_iOutFidsOffset = 2000;
		if(!IniFile.GetItemInt("ProcParam",	 "FZInnerOffSet",  GetDoc().m_iFZInnerOffset))//ly add 20120522
			GetDoc().m_iFZInnerOffset = 500;
		if(GetDoc().m_iFZInnerOffset >1000)
			GetDoc().m_iFZInnerOffset = 1000;
		if(!IniFile.GetItemF64("ProcParam",	 "FZInnerScale",  GetDoc().m_fFZInnerScale))//ly add 20120522
			GetDoc().m_fFZInnerScale=0.0001;//ly add 20120522
		if(!IniFile.GetItemInt("ProcParam",	 "LaserComp",  GetDoc().m_laserComp))//ly add 20120919
			GetDoc().m_laserComp=0;//ly add 20120919
		if(!IniFile.GetItemInt("ProcParam",	 "LaserTestComp",  GetDoc().m_laserTestComp))//ly add 20121227
			GetDoc().m_laserTestComp=0;//ly add 20121227
		if(!IniFile.GetItemInt("ProcParam",	 "NewDelay",  ltmp))//ly add 20130821
			ltmp = 1;					//0:不启用
		GetDoc().SetNewDelay(ltmp);
		if(!IniFile.GetItemInt("ProcParam",	 "TableDelay",  GetDoc().m_lTableDelay))//ly add 20121013
			GetDoc().m_lTableDelay=50;//ly add 20121013
		if(GetDoc().m_lTableDelay<50)
			GetDoc().m_lTableDelay=50;//ly add 20121013
		if(!IniFile.GetItemF64("ProcParam",	 "DrilledHoles",  GetDoc().m_lDrldHolesSum))//ly add 20121230
			GetDoc().m_lDrldHolesSum=0;//ly add 20120919

		if(!IniFile.GetItemF64("ProcParam",	 "PowerScale",  GetDoc().m_lPowerScale))
			GetDoc().m_lPowerScale=1.0;
		if(GetDoc().m_lPowerScale>1.15 || GetDoc().m_lPowerScale<0.85)
           GetDoc().m_lPowerScale=1.0;

		//ly add 20130508------
		if(GetDoc().m_fFZInnerScale<0.0001||GetDoc().m_fFZInnerScale>0.002)//ly add 20130821
			GetDoc().m_fFZInnerScale = 0.0001;
        
		if(!IniFile.GetItemInt("ProcParam",	 "LoadPCBTime", ltmp ))
			GetDoc().m_lLoadPCBTime=0;
		else														//20181203
			GetDoc().m_lLoadPCBTime=ltmp;

		if(!IniFile.GetItemInt("ProcParam",	 "UnLoadPCBTime", ltmp ))
			GetDoc().m_lUnLoadPCBTime=0;
		else														//20181203
			GetDoc().m_lUnLoadPCBTime=ltmp;

		if(!IniFile.GetItemInt("ProcParam",	 "LaserComp1",  GetDoc().m_laserComp1))	//20200515
			GetDoc().m_laserComp1=0;
		if(!IniFile.GetItemInt("ProcParam",	 "LaserComp2",  GetDoc().m_laserComp2))
			GetDoc().m_laserComp2=0;
				
        // 开标靶
		if(!IniFile.GetItemInt("DrillRegion","JumpDelay",  GetDoc().m_lDrlRegJumpDelay))
			GetDoc().m_lDrlRegJumpDelay =2000;
		if(!IniFile.GetItemInt("DrillRegion","JumpSpeed", GetDoc().m_lDrlRegJumpSpeed))
			GetDoc().m_lDrlRegJumpSpeed =2000;
		if(!IniFile.GetItemInt("DrillRegion","Period",  GetDoc().m_lDrlRegPlsPeriod))
			GetDoc().m_lDrlRegPlsPeriod =2000;
		GetDoc().m_lDrlRegJumpDelay =1000;//ly add 20111208 
		GetDoc().m_lDrlRegJumpSpeed =4000;//ly add 20111208 
		GetDoc().m_lDrlRegPlsPeriod =1000;//ly add 20111208 
   
		if(!IniFile.GetItemInt("DrillRegion","Times",  GetDoc().m_lDrlRegPlsTimes))
			GetDoc().m_lDrlRegPlsTimes =5;
		if(!IniFile.GetItemInt("DrillRegion","RegionPointDis",  m_lDrlRegPointDis))
			m_lDrlRegPointDis =100;
		if(!IniFile.GetItemInt("DrillRegion","Release",  GetDoc().m_lDrlRegPlsRelease))
			GetDoc().m_lDrlRegPlsRelease =30;
		if(!IniFile.GetItemInt("DrillRegion","Release2",  GetDoc().m_lDrlRegPls2Release))
			GetDoc().m_lDrlRegPls2Release =30;
		if(!IniFile.GetItemInt("DrillRegion","Release3",  GetDoc().m_lDrlRegPls3Release))
			GetDoc().m_lDrlRegPls3Release =30;
		if(!IniFile.GetItemInt("DrillRegion","Release4",  GetDoc().m_lDrlRegPls4Release))
			GetDoc().m_lDrlRegPls4Release =30;
		if(!IniFile.GetItemInt("DrillRegion","Release5",  GetDoc().m_lDrlRegPls5Release))
			GetDoc().m_lDrlRegPls5Release =30;
		if(!IniFile.GetItemInt("DrillRegion","Aperture",  GetDoc().m_lDrlRegApertureNo))
			GetDoc().m_lDrlRegApertureNo =2;

#ifndef APERTURE18
#ifndef APERTURE12
		if(GetDoc().m_lDrlRegApertureNo>8)
			GetDoc().m_lDrlRegApertureNo = 8;
#else
		if(GetDoc().m_lDrlRegApertureNo>12)
			GetDoc().m_lDrlRegApertureNo = 12;
#endif
#endif
		if(!IniFile.GetItemInt("DrillRegion","Times",     GetDoc().m_lDrlRegPulseNum))
			GetDoc().m_lDrlRegPulseNum =2;
		if(!IniFile.GetItemInt("DrillRegion","DrillCoil", ltmp))							//20170224
			GetDoc().m_bDrillCoil=FALSE;
		else
			GetDoc().m_bDrillCoil=ltmp?TRUE:FALSE;
//校正	
		if(!IniFile.GetItemInt("AdjustLaserPara","GlvAdjRelease",  GetDoc().m_ulAdjPlslRelease))
			GetDoc().m_ulAdjPlslRelease =20;
		if(!IniFile.GetItemInt("AdjustLaserPara","GlvAdjPosX",  GetDoc().m_lAdjPosX))
			GetDoc().m_lAdjPosX =0;
		if(!IniFile.GetItemInt("AdjustLaserPara","GlvAdjPosY",  GetDoc().m_lAdjPosY))
			GetDoc().m_lAdjPosY =-400000;
		if(!IniFile.GetItemInt("AdjustLaserPara","JumpDelay",  GetDoc().m_lAdjustJumpDelay))
			GetDoc().m_lAdjustJumpDelay =1000;
		if(!IniFile.GetItemInt("AdjustLaserPara","JumpSpeed", GetDoc().m_lAdjustJumpSpeed))
			GetDoc().m_lAdjustJumpSpeed =4000;
		if(!IniFile.GetItemInt("AdjustLaserPara","Period",  GetDoc().m_lAdjustPlsPeriod))
			GetDoc().m_lAdjustPlsPeriod =1000;
		if(!IniFile.GetItemInt("AdjustLaserPara","Release",  GetDoc().m_lAdjustPlsRelease))
			GetDoc().m_lAdjustPlsRelease =30;
		if(!IniFile.GetItemInt("AdjustLaserPara","Aperture",  GetDoc().m_lAdjustApertureNo))
			GetDoc().m_lDrlRegApertureNo =2;
		GetDoc().m_lAdjustPlsPeriod =1000;//ly add 20111208
		GetDoc().m_lAdjustJumpSpeed =4000;//ly add 20111208
		GetDoc().m_lAdjustJumpDelay =1000;//ly add 20111208

#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
		if(GetDoc().m_lAdjustApertureNo>8)
		{
			GetDoc().m_lAdjustApertureNo = 8;
		}
#else//ly change 20110122 12光圈
		if(GetDoc().m_lAdjustApertureNo>12)
		{
			GetDoc().m_lAdjustApertureNo = 12;
		}
#endif
#endif

		if(!IniFile.GetItemInt("AdjustLaserPara","LongPathAperture",  GetDoc().m_lLongPathAdjustApertureNo))
			GetDoc().m_lLongPathAdjustApertureNo =2;

#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
		if(GetDoc().m_lLongPathAdjustApertureNo>8)
		{
			GetDoc().m_lLongPathAdjustApertureNo = 8;
		}
#else//ly change 20110122 12光圈
		if(GetDoc().m_lLongPathAdjustApertureNo>12)
		{
			GetDoc().m_lLongPathAdjustApertureNo = 12;
		}
#endif
#endif
	
		// 钻字符信息 yutingxun 8-23 06
		if(!IniFile.GetItemInt("WarningTime","AdjTime", GetDoc().m_ulAdjTime))
			GetDoc().m_ulAdjTime =120;
		if(!IniFile.GetItemInt("WarningTime","LaserPowerTime", GetDoc().m_ulLaserPowerTime))
			GetDoc().m_ulLaserPowerTime =120;
		if(!IniFile.GetItemString("WarningTime","OperationRateTime", GetDoc().m_OperationRateTime))
			GetDoc().m_OperationRateTime ="20:00:00";
		if(!IniFile.GetItemString("WarningTime","OperationRateTimeNight", GetDoc().m_OperationRateTimeNight))
			GetDoc().m_OperationRateTimeNight ="8:00:00";

	// 钻字符信息 yutingxun 7-5 06
		if(!IniFile.GetItemInt("DrillTxtInfo","TxtJumpDelay",  GetDoc().m_lDrlTxtJumpDelay))
			GetDoc().m_lDrlTxtJumpDelay =1000;
		if(!IniFile.GetItemInt("DrillTxtInfo","TxtJumpSpeed", GetDoc().m_lDrlTxtJumpSpeed))
			GetDoc().m_lDrlTxtJumpSpeed =4000;
		if(!IniFile.GetItemF64("DrillTxtInfo","TextHeigth", GetDoc().m_fTextHeigth))
			GetDoc().m_fTextHeigth =2.4;        
		if(!IniFile.GetItemInt("DrillTxtInfo","TxtPeriod",  GetDoc().m_lDrlTxtPlsPeriod))
			GetDoc().m_lDrlTxtPlsPeriod =1000;
		if(!IniFile.GetItemInt("DrillTxtInfo","TxtRelease",  GetDoc().m_lDrlTxtPlsRelease))
			GetDoc().m_lDrlTxtPlsRelease =30;
		GetDoc().m_lDrlTxtJumpSpeed =4000;//ly add 20111208
		GetDoc().m_lDrlTxtJumpDelay =1000;//ly add 20111208
		GetDoc().m_lDrlTxtPlsPeriod =1000;//ly add 20111208

		if(!IniFile.GetItemInt("DrillTxtInfo","TxtAperture",  GetDoc().m_lDrlTxtApertureNo))
			GetDoc().m_lDrlTxtApertureNo =2;

#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
		if(GetDoc().m_lDrlTxtApertureNo>8)
		{
			GetDoc().m_lDrlTxtApertureNo = 8;
		}
#else//ly change 20110122 12光圈
		if(GetDoc().m_lDrlTxtApertureNo>12)
		{
			GetDoc().m_lDrlTxtApertureNo = 12;
		}
#endif
#endif

		if(!IniFile.GetItemInt("DrillTxtInfo","TxtTimes",     GetDoc().m_lDrlTxtPulseNum))
			GetDoc().m_lDrlTxtPulseNum =2;
		//上下料
		if(!IniFile.GetItemInt("Load&Unload",	"LoadPitchPos",    GetDoc().m_LoadPitchPos))
			GetDoc().m_LoadPitchPos =22000;
		if(!IniFile.GetItemInt("Load&Unload",	"UnloadPitchPos",  GetDoc().m_UnloadPitchPos))
			GetDoc().m_UnloadPitchPos =22000;
		if(!IniFile.GetItemInt("Load&Unload",	"LoadBenchmark",   GetDoc().m_LoadBenchmark))
			GetDoc().m_LoadBenchmark =3000;

		if(!IniFile.GetItemInt("Load&Unload",	"LoadTune",   GetDoc().m_LoadTunePos))
			GetDoc().m_LoadTunePos =65000;
		if(!IniFile.GetItemInt("Load&Unload",	"UnLoadTune",   GetDoc().m_UnLoadTunePos))
			GetDoc().m_UnLoadTunePos =65000;

		if(!IniFile.GetItemInt("Load&Unload",	"UnloadBenchmark", GetDoc().m_UnloadBenchmark))
			GetDoc().m_UnloadBenchmark =3000;
		if(!IniFile.GetItemInt("Load&Unload",	"LoadLiftBenchmark",   GetDoc().m_LoadLiftBM))
			GetDoc().m_LoadLiftBM   =500;
		if(!IniFile.GetItemInt("Load&Unload",	"UnloadLiftBenchmark", GetDoc().m_UnloadLiftBM))
			GetDoc().m_UnloadLiftBM =500;

		if(!IniFile.GetItemInt("Load&Unload",	"LoadTransPos",    GetDoc().m_LoadTransPos))
			GetDoc().m_LoadTransPos =11000;
		if(!IniFile.GetItemInt("Load&Unload",	"UnloadTranshPos",  GetDoc().m_UnloadTransPos))
			GetDoc().m_UnloadTransPos =22000;
		if(!IniFile.GetItemInt("Load&Unload",	"LoadOptimize",  GetDoc().m_LoadOptimize))//ly add 20120919	//20190222
			GetDoc().m_LoadOptimize =60;												
//		if(!IniFile.GetItemInt("Load&Unload",	"NGSum",  GetDoc().m_lNgSum))//ly add 20121127
//			GetDoc().m_lNgSum =0;
		if(!IniFile.GetItemInt("Load&Unload",	"NGThred",  GetDoc().m_lNgThrd))//ly add 20121127
			GetDoc().m_lNgThrd =10;
		
		
		//平台
		if(!IniFile.GetItemInt("TabPos",	"TabBenchmarkX", GetDoc().m_crdTabBenchmark.x))
			GetDoc().m_crdTabBenchmark.x =-10000;
		if(!IniFile.GetItemInt("TabPos",	"TabBenchmarkY", GetDoc().m_crdTabBenchmark.y))
			GetDoc().m_crdTabBenchmark.y =-10000;

		if(!IniFile.GetItemInt("TabPos",	"TabLoadPosX",   GetDoc().m_crdTabLoadPos.x))
			GetDoc().m_crdTabLoadPos.x =30000;
		if(!IniFile.GetItemInt("TabPos",	"TabLoadPosY",   GetDoc().m_crdTabLoadPos.y))
			GetDoc().m_crdTabLoadPos.y =0;

		if(!IniFile.GetItemInt("TabPos",	"TabUnloadPosX",   GetDoc().m_crdTabUnloadPos.x))
			GetDoc().m_crdTabUnloadPos.x =-30000;
		if(!IniFile.GetItemInt("TabPos",	"TabUnloadPosY",   GetDoc().m_crdTabUnloadPos.y))
			GetDoc().m_crdTabUnloadPos.y =0;

		if(!IniFile.GetItemInt("TabPos",	"OVerTabLoadPosX",   GetDoc().m_crdOVerTabLoadPos.x))
			GetDoc().m_crdOVerTabLoadPos.x =30000;
		if(!IniFile.GetItemInt("TabPos",	"OVerTabLoadPosY",   GetDoc().m_crdOVerTabLoadPos.y))
			GetDoc().m_crdOVerTabLoadPos.y =0;		
		if(!IniFile.GetItemInt("TabPos",	"OVerTabUnloadPosX",   GetDoc().m_crdOVerTabUnloadPos.x))
			GetDoc().m_crdOVerTabUnloadPos.x =-30000;
		if(!IniFile.GetItemInt("TabPos",	"OVerTabUnloadPosY",   GetDoc().m_crdOVerTabUnloadPos.y))
			GetDoc().m_crdOVerTabUnloadPos.y =0;

		if(!IniFile.GetItemInt("TabPos",	"TabPitchDistanceX",   GetDoc().m_crdTabPitchDisXY.x))
			GetDoc().m_crdTabPitchDisXY.x =5000;
		if(!IniFile.GetItemInt("TabPos",	"TabPitchDistanceY",   GetDoc().m_crdTabPitchDisXY.y))
			GetDoc().m_crdTabPitchDisXY.y =5000;

		//加工方向
		if(!IniFile.GetItemInt("ProcessInfo",   "ProcessDir",GetDoc().m_lProcessDir ))
			GetDoc().m_lProcessDir = 0;
		if(!IniFile.GetItemInt("ProcessInfo",   "ProcessState",GetDoc().m_lAutoProc ))
			GetDoc().m_lAutoProc = 0;
		if(!IniFile.GetItemInt("ProcessInfo",   "ScanSize",	 GetDoc().m_lScanSize ))
			GetDoc().m_lScanSize = 65;
		if(!IniFile.GetItemInt("ProcessInfo",   "ProcMode",	 ltmp ))
		{
			GetDoc().m_ProcMode = EXTERNALMARKPROC;   
		}
		else
		{
			GetDoc().m_ProcMode = ltmp?INNERMARKPROC:EXTERNALMARKPROC;  
		}
		if (LSPATH_CHECKING)
		{
			if(!IniFile.GetItemInt("ProcessInfo",   "TechnicType",	 ltmp ))
			{
				GetDoc().m_TechnicType = FALSE;
				
			}
			else
			{
				GetDoc().m_TechnicType = ltmp?TRUE:FALSE;
			}
		}
		else
		{
			GetDoc().m_TechnicType = TRUE;//2010-11-19 默认为长光路
		}
		

     long tempThickingType=0;
	IniFile.GetItemInt("ProcessInfo",   "ThickingType",	tempThickingType);
	if(tempThickingType)
		GetDoc().m_ThickingType = TRUE;
	else
       GetDoc().m_ThickingType = FALSE;
	
	
	//CCD 
	if(!IniFile.GetItemInt("CCD Threshold","ProcThreshold",m_lCCDProcThreshold))
		m_lCCDProcThreshold = 80;
	
		if(!IniFile.GetItemInt("CCD Threshold","ProcInnerThreshold",m_lCCDProcInnerThreshold))
             m_lCCDProcInnerThreshold = 80;
		if(!IniFile.GetItemInt("CCD Threshold","ProcInnerRange",m_lCCDProcInnerRange))//ly add 20121009
             m_lCCDProcInnerRange = 250;
//		if(m_lCCDProcInnerRange >550)					//20190528
//			m_lCCDProcInnerRange = 550;
//		if(m_lCCDProcInnerRange <250)					//20200508(20190528)
//			m_lCCDProcInnerRange = 250;

		if(!IniFile.GetItemInt("CCD Threshold","AdjThreshold",m_lCCDAdjustThreshold))
             m_lCCDAdjustThreshold = 80;
		if(!IniFile.GetItemInt("CCD Threshold","ContrastThrd",m_lCCDContrastThrd))//ly add 20140328
             m_lCCDContrastThrd = 50;
		if(m_lCCDContrastThrd<20)
			m_lCCDContrastThrd=20;
		if(m_lCCDContrastThrd>80)
			m_lCCDContrastThrd=80;

		if(!IniFile.GetItemInt("CCD Threshold","DistanceCenterThrd",m_iDistanceCenterThreshold))//ly add 20140328
             m_iDistanceCenterThreshold = 75;
	
		if(!IniFile.GetItemInt("OtherThreshold","GlvThreshold",m_iGlvAdjustThreshold))
             m_iGlvAdjustThreshold = 10;
		if(!IniFile.GetItemF64("OtherThreshold","ScaleThreshold",m_fPCBScaleThreshold))
             m_fPCBScaleThreshold = 0.0001;
		if(!IniFile.GetItemInt("OtherThreshold","ScaleThrd",m_fPCBScaleThrd))//ly add 20120919
             m_fPCBScaleThrd = 500;
		if(!IniFile.GetItemInt("OtherThreshold","ScaleType",m_ScaleType))//ly add 20120919
             m_ScaleType = 0;
		if(!IniFile.GetItemInt("OtherThreshold","AutoThickError",m_iAutoThickError))
             m_iAutoThickError = 50;
		if(!IniFile.GetItemF64("OtherThreshold","LaserPowerTest",m_fLaserPowerTestSt))
             m_fLaserPowerTestSt = 7.0;
		if(!IniFile.GetItemF64("OtherThreshold","LaserPowerTestMax",m_fLaserPowerTestMax))//ly add 20120924
             m_fLaserPowerTestMax = 50.0;
		//标靶极性
		if(!IniFile.GetItemInt("FiducialPolarity","MainFiducial",m_lMainFiduPolarity))
             m_lMainFiduPolarity = 0;
		if(!IniFile.GetItemInt("FiducialPolarity","InnerFiducial",m_lInnerFiduPolarity))
             m_lInnerFiduPolarity = 0;

		if(!IniFile.GetItemString("MarkerInfo","MachineSn",GetDoc().m_strMachineSn))
			GetDoc().m_strMachineSn = "HANS";
		if(!IniFile.GetItemF64("MarkerInfo","LotIDHeigth",GetDoc().m_strZoomSn))
			GetDoc().m_strZoomSn = 2.4;
		if(!IniFile.GetItemString("MarkerInfo","LotIDFix",GetDoc().m_strLOTIdFix))//ly add 20121127
			GetDoc().m_strLOTIdFix = "LotID";
		if(!IniFile.GetItemString("MarkerInfo","LotIDInc",GetDoc().m_strLOTIdInc))//ly add 20121127
			GetDoc().m_strLOTIdInc = "01";
		if(!IniFile.GetItemInt("MarkerInfo","EnMachSn",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnMachSn = 0;
		}
		else
		{
			GetDoc().m_bEnMachSn=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnManuDay",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnManuDay = 0;
		}
		else
		{
			GetDoc().m_bEnManuDay=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnManuTime",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnManuTime = 0;
		}
		else
		{
			GetDoc().m_bEnManuTime=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnManuString",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnManuString = 0;
		}
		else
		{
			GetDoc().m_bEnManuString=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnLotID",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnLOTSn = 0;
		}
		else
		{
			GetDoc().m_bEnLOTSn=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnLotIDFix",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnLOTFix = 0;
		}
		else
		{
			GetDoc().m_bEnLOTFix=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnLotIDInc",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnLOTInc = 0;
		}
		else
		{
			GetDoc().m_bEnLOTInc=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("MarkerInfo","EnLotIDScale",ltmp))//ly add 20121127
		{
			GetDoc().m_bEnLOTScale = 0;
		}
		else
		{
			GetDoc().m_bEnLOTScale=ltmp?TRUE:FALSE;
		}

		if(!IniFile.GetItemInt("MarkerInfo","EnAxisNo",ltmp))//ly add 20121230
		{
			GetDoc().m_bEnAxisNo = 0;
		}
		else
		{
			GetDoc().m_bEnAxisNo=ltmp?TRUE:FALSE;
		}
		

		if(!IniFile.GetItemInt ("CaliBoardThick","CCDBoardThick",  GetDoc().m_lCCDBoardThick))
			GetDoc().m_lCCDBoardThick = 1000;	
		if(!IniFile.GetItemInt ("CaliBoardThick","GalvoBoardThick",  GetDoc().m_lGalvoBoardThick))
			GetDoc().m_lGalvoBoardThick = 1000;

		if(!IniFile.GetItemInt ("AutoThickingXY","ThicknessX",  GetDoc().m_lThicknessX))
			GetDoc().m_lThicknessX = 0;	
		if(!IniFile.GetItemInt ("AutoThickingXY","ThicknessY",  GetDoc().m_lThicknessY))
			GetDoc().m_lThicknessY = 0;
		
		if(!IniFile.GetItemInt("AutoTestFunction","PatternAdjust",ltmp ))
		{
			GetDoc().m_bEnableAutoAdjust=FALSE;
		}
		else
		{
			GetDoc().m_bEnableAutoAdjust=ltmp?TRUE:FALSE;
		}

		if(!IniFile.GetItemInt("AutoTestFunction","LaserPower",ltmp ))
		{
			GetDoc().m_bEnableAutoPower=FALSE;
		}
		else
		{
			GetDoc().m_bEnableAutoPower=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("AutoTestFunction","FidRetry",ltmp ))//ly add 20120202
		{
			GetDoc().m_bEnableFidRetry=FALSE;
		}
		else
		{
			GetDoc().m_bEnableFidRetry=ltmp?TRUE:FALSE;
		}

		/*if(!IniFile.GetItemInt("AutoTestFunction","ToolCycleMode",ltmp ))//ly add 20120705
		{
			GetDoc().m_bToolCycleMode=FALSE;
		}
		else
		{
			GetDoc().m_bToolCycleMode=ltmp?TRUE:FALSE;
		}
		if(!IniFile.GetItemInt("AutoTestFunction","En3Fid",ltmp ))//ly add 20130121
		{
			GetDoc().m_bEn3Fid=FALSE;
		}
		else
		{
			GetDoc().m_bEn3Fid=ltmp?TRUE:FALSE;
		}*///ly delete 20131226 不保存允许3标靶的状态
		if(!IniFile.GetItemInt("AutoTestFunction","ManuFindFid",ltmp ))//ly add 20130121
		{
			GetDoc().m_bMaFindFid=FALSE;
		}
		else
		{
			GetDoc().m_bMaFindFid=ltmp?TRUE:FALSE;
		}		

		if(!IniFile.GetItemInt ("FilePara","FileUnit",  GetDoc().m_fileunit))//ly add 20120516
			GetDoc().m_fileunit = 1;	
		if(!IniFile.GetItemInt ("FilePara","FileMode",  GetDoc().m_filemode))
			GetDoc().m_filemode = 1;
		if(!IniFile.GetItemInt ("FilePara","FileFormat",  GetDoc().m_fileformat))
			GetDoc().m_fileformat = 1;	
		if(!IniFile.GetItemInt ("FilePara","FileDecNum",  GetDoc().m_filedecnum))
			GetDoc().m_filedecnum = 3;
		if(!IniFile.GetItemInt ("FilePara","FileIntNum",  GetDoc().m_fileintnum))
			GetDoc().m_fileintnum = 2;
		
		if(!IniFile.GetItemInt ("CalibrateTol","GlvCaliOffsetTol",  m_lGlvCaliOffsetTol))
			m_lGlvCaliOffsetTol = 2000;	
		if(!IniFile.GetItemInt ("TestThickness","ZSafePos",  m_lTestThicknessZSafePos))
			m_lTestThicknessZSafePos = 20000;
		if(!IniFile.GetItemInt ("TestThickness","Z1Compensation",  m_lTestThicknessCompensation[0]))
			m_lTestThicknessCompensation[0] = 0;
		if(!IniFile.GetItemInt ("TestThickness","Z2Compensation",  m_lTestThicknessCompensation[1]))
			m_lTestThicknessCompensation[1] = 0;

//手动涨缩设定
		double fValX,fValY;

		if(!IniFile.GetItemF64("PCBScale",	 "ManualScaleX",  fValX))
			fValX = 1.0;
		if(!IniFile.GetItemF64("PCBScale",	 "ManualScaleY",  fValY))
			fValY = 1.0;

		InputManSetScaleVal(fValX,fValY);

//20160809
		if(!IniFile.GetItemInt ("BigHoleSet","BeamStep",  GetDoc().m_lSysBeamStep))
			GetDoc().m_lSysBeamStep = 80;	
		if(!IniFile.GetItemInt ("BigHoleSet","BeamDiameter",  GetDoc().m_lSysBeamDia))
			GetDoc().m_lSysBeamDia = 150;		
//20160812
		long iItemCount;
		char buf[16];
		ScaleSet ss;
		if(!IniFile.GetItemInt ("ScaleSet","ItemCount",  iItemCount))
			iItemCount = 0;

		for(int nn=0;nn<iItemCount;nn++)
		{
			sprintf(buf,"DownLimit%d\0",nn);
			if(!IniFile.GetItemF64 ("ScaleSet",buf,  ss.dbDownLimit))
				ss.dbDownLimit = 1.0;
			sprintf(buf,"UpLimit%d\0",nn);
			if(!IniFile.GetItemF64 ("ScaleSet",buf,  ss.dbUpLimit))
				ss.dbUpLimit = 1.0;
			sprintf(buf,"Char%d\0",nn);
			if(!IniFile.GetItemString ("ScaleSet",buf,  ss.strChar))
				ss.strChar = "A";
			
			GetDoc().AddSysScaleSet(ss);			
		}

		IniFile.CloseIniFile();	
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13013),256);
		AfxMessageBox(ez,MB_OK);//"无法导入加工参数！"
#ifdef USELOG
		GetLog().Append_pro(10101,"SaveMotionParam");//"无法导入加工参数"
#endif
		return false;
	}

	return TRUE;
}

BOOL SystemDoc::LoadCCDLuminancePara()
{
	CIniFile IniFile;
	CString str,path;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\CCDLuminacePara");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
//外层标靶		
		if(!IniFile.GetItemInt("ExtFiducial","ExtLeftCaxial", GetDoc().m_lCCDLumLC_OUT))
			GetDoc().m_lCCDLumLC_OUT = 60;	
		if(!IniFile.GetItemInt("ExtFiducial","ExtLeftRinged", GetDoc().m_lCCDLumLR_OUT))
			GetDoc().m_lCCDLumLR_OUT = 128;	
		if(!IniFile.GetItemInt("ExtFiducial","ExtRightCaxial", GetDoc().m_lCCDLumRC_OUT))
			GetDoc().m_lCCDLumRC_OUT = 60;	
		if(!IniFile.GetItemInt("ExtFiducial","ExtRightRinged", GetDoc().m_lCCDLumRR_OUT))
			GetDoc().m_lCCDLumRR_OUT = 128;
		if(!IniFile.GetItemInt("ExtFiducial","ExtLeftInfrared", GetDoc().m_infraredSetVakue[0][0]))
			GetDoc().m_infraredSetVakue[0][0] = 60;	
		if(!IniFile.GetItemInt("ExtFiducial","ExtRightInfrared", GetDoc().m_infraredSetVakue[0][1]))
			GetDoc().m_infraredSetVakue[0][1] = 128;
		
//内层标靶
		if(!IniFile.GetItemInt("InsideFiducial","InsLeftCaxial", GetDoc().m_lCCDLumLC_INS))
			GetDoc().m_lCCDLumLC_INS = 60;	
		if(!IniFile.GetItemInt("InsideFiducial","InsLeftRinged", GetDoc().m_lCCDLumLR_INS))
			GetDoc().m_lCCDLumLR_INS = 128;	
		if(!IniFile.GetItemInt("InsideFiducial","InsRightCaxial", GetDoc().m_lCCDLumRC_INS))
			GetDoc().m_lCCDLumRC_INS = 60;	
		if(!IniFile.GetItemInt("InsideFiducial","InsRightRinged", GetDoc().m_lCCDLumRR_INS))
			GetDoc().m_lCCDLumRR_INS = 128;	
		if(!IniFile.GetItemInt("InsideFiducial","InsLeftInfrared", GetDoc().m_infraredSetVakue[1][0]))
			GetDoc().m_infraredSetVakue[2][0] = 60;	
		if(!IniFile.GetItemInt("InsideFiducial","InsRightInfrared", GetDoc().m_infraredSetVakue[1][1]))
			GetDoc().m_infraredSetVakue[2][1] = 128;	

//点阵校正
		if(!IniFile.GetItemInt("GlvEmendation","GlvEmeLeftCaxial", GetDoc().m_lCCDLumLC_GLV))
			GetDoc().m_lCCDLumLC_GLV = 60;	
		if(!IniFile.GetItemInt("GlvEmendation","GlvEmeLeftRinged", GetDoc().m_lCCDLumLR_GLV))
			GetDoc().m_lCCDLumLR_GLV = 128;	
		if(!IniFile.GetItemInt("GlvEmendation","GlvEmeRightCaxial", GetDoc().m_lCCDLumRC_GLV))
			GetDoc().m_lCCDLumRC_GLV = 60;	
		if(!IniFile.GetItemInt("GlvEmendation","GlvEmeRightRinged", GetDoc().m_lCCDLumRR_GLV))
			GetDoc().m_lCCDLumRR_GLV = 128;			
		if(!IniFile.GetItemInt("GlvEmendation","GlvEmeLeftInfrared", GetDoc().m_infraredSetVakue[2][0]))
			GetDoc().m_infraredSetVakue[2][0] = 60;	
		if(!IniFile.GetItemInt("GlvEmendation","GlvEmeRightInfrared", GetDoc().m_infraredSetVakue[2][1]))
			GetDoc().m_infraredSetVakue[2][1] = 128;	

//原点校正
		if(!IniFile.GetItemInt("Emendation","OrgEmeLeftCaxial", GetDoc().m_lCCDLumLC_EME))
			GetDoc().m_lCCDLumLC_EME = 60;	
		if(!IniFile.GetItemInt("Emendation","OrgEmeLeftRinged", GetDoc().m_lCCDLumLR_EME))
			GetDoc().m_lCCDLumLR_EME = 128;	
		if(!IniFile.GetItemInt("Emendation","OrgEmeRightCaxial", GetDoc().m_lCCDLumRC_EME))
			GetDoc().m_lCCDLumRC_EME = 60;	
		if(!IniFile.GetItemInt("Emendation","OrgEmeRightRinged", GetDoc().m_lCCDLumRR_EME))
			GetDoc().m_lCCDLumRR_EME = 128;	
		if(!IniFile.GetItemInt("Emendation","OrgEmeLeftInfrared", GetDoc().m_infraredSetVakue[3][0]))
			GetDoc().m_infraredSetVakue[3][0] = 60;	
		if(!IniFile.GetItemInt("Emendation","OrgEmeRightInfrared", GetDoc().m_infraredSetVakue[3][1]))
			GetDoc().m_infraredSetVakue[3][1] = 128;	

//CCD校正
		if(!IniFile.GetItemInt("CCDInterval","CCDIntLeftCaxial", GetDoc().m_lCCDLumLC_CCD))
			GetDoc().m_lCCDLumLC_CCD = 60;	
		if(!IniFile.GetItemInt("CCDInterval","CCDIntLeftRinged", GetDoc().m_lCCDLumLR_CCD))
			GetDoc().m_lCCDLumLR_CCD = 128;	
		if(!IniFile.GetItemInt("CCDInterval","CCDIntRightCaxial", GetDoc().m_lCCDLumRC_CCD))
			GetDoc().m_lCCDLumRC_CCD = 60;	
		if(!IniFile.GetItemInt("CCDInterval","CCDIntRightRinged", GetDoc().m_lCCDLumRR_CCD))
			GetDoc().m_lCCDLumRR_CCD = 128;
		if(!IniFile.GetItemInt("CCDInterval","CCDIntLeftInfrared", GetDoc().m_infraredSetVakue[4][0]))
			GetDoc().m_infraredSetVakue[4][0] = 60;	
		if(!IniFile.GetItemInt("CCDInterval","CCDIntRightInfrared", GetDoc().m_infraredSetVakue[4][1]))
			GetDoc().m_infraredSetVakue[4][1] = 128;	
//内部标靶
		if(!IniFile.GetItemInt("LocalMark","LocalMarkLeftCaxial", GetDoc().m_lCCDLumLC_LM))
			GetDoc().m_lCCDLumLC_LM = 60;	
		if(!IniFile.GetItemInt("LocalMark","LocalMarkLeftRinged", GetDoc().m_lCCDLumLR_LM))
			GetDoc().m_lCCDLumLR_LM = 128;	
		if(!IniFile.GetItemInt("LocalMark","LocalMarkRightCaxial", GetDoc().m_lCCDLumRC_LM))
			GetDoc().m_lCCDLumRC_LM = 60;	
		if(!IniFile.GetItemInt("LocalMark","LocalMarkRightRinged", GetDoc().m_lCCDLumRR_LM))
			GetDoc().m_lCCDLumRR_LM = 128;
		if(!IniFile.GetItemInt("LocalMark","LocalMarkLeftInfrared", GetDoc().m_infraredSetVakue[5][0]))
			GetDoc().m_infraredSetVakue[5][0] = 60;	
		if(!IniFile.GetItemInt("LocalMark","LocalMarkRightInfrared", GetDoc().m_infraredSetVakue[5][1]))
			GetDoc().m_infraredSetVakue[5][1] = 128;	
		
		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13014),256);
		AfxMessageBox(ez,MB_OK);//"无法导入CCD照明参数！"
		return false;
	}

	return true;
}

BOOL SystemDoc::LoadWebServiceParam()
{
	CIniFile IniFile;
	CString str, path;
	char ez[256] = { "" };

	path = AfxGetApp()->m_pszHelpFilePath;
	str = AfxGetApp()->m_pszExeName;
	path = path.Left(path.ReverseFind('.') - str.GetLength());
	IniFile.SetName("param\\WebServicePara");
	IniFile.SetPath(path);

	BOOL bExist = IniFile.OpenIniFileForRead();
	if (bExist)
	{
		//Company
		if (!IniFile.GetItemInt("Company", "CompanyCode", GetDoc().m_SysCompanyCode))
			GetDoc().m_SysCompanyCode = 0;

		//WebService
		if (!IniFile.GetItemString("WebService", "MachineSn", GetDoc().m_strSysMachineSn))
			GetDoc().m_strSysMachineSn = "";
		if (!IniFile.GetItemString("WebService", "ImesURL", GetDoc().m_strSysImesURL))
			GetDoc().m_strSysImesURL = "";
		if (!IniFile.GetItemInt("WebService", "Timeout", GetDoc().m_strSysTimeout))
			GetDoc().m_strSysTimeout = 30;
		if (!IniFile.GetItemInt("WebService", "IdtTime", GetDoc().m_strSysIdtTime))
			GetDoc().m_strSysIdtTime = 10;
		if (!IniFile.GetItemInt("WebService", "ModeSwitch", GetDoc().m_SysModeSwitch))
			GetDoc().m_SysModeSwitch = 1;
		if (!IniFile.GetItemInt("WebService", "UserControlSwitch", GetDoc().m_SysUserControlSwitch))
			GetDoc().m_SysUserControlSwitch = 0;
		if (!IniFile.GetItemString("WebService", "HeartbeatContent", GetDoc().m_strSysHeartbeatContent))
			GetDoc().m_strSysHeartbeatContent = "OffLine";
		if (!IniFile.GetItemString("WebService", "HeartbeatFreq", GetDoc().m_strSysHeartbeatFreq))
			GetDoc().m_strSysHeartbeatFreq = "";

		//IngredientExplainSet
		long iItemCount;
		char buf[16];
		IngredientExplainSet is;
		if(!IniFile.GetItemInt ("IngredientExplainSet","ItemCount", iItemCount))
			iItemCount = 0;

		for(int nn=0;nn<iItemCount;nn++)
		{
			sprintf(buf,"Label%d\0",nn);
			if(!IniFile.GetItemString ("IngredientExplainSet",buf, is.strLabel))
				is.strLabel = "";
			sprintf(buf,"Explain%d\0",nn);
			if(!IniFile.GetItemString ("IngredientExplainSet",buf, is.strExplain))
				is.strExplain = "";	
			GetDoc().AddSysIngredientExplainSet(is);			
		}

		IniFile.CloseIniFile();
	}
	else
	{
		strncpy(ez, GetLang().GetWarningText(13014), 256);
		AfxMessageBox(ez, MB_OK);//"无法导入WebService参数！"
#ifdef USELOG
		GetLog().Append_pro(10117,"LoadWebServiceParam");//"无法导入WebService参数"
#endif
		return false;
	}
	return true;
}

BOOL SystemDoc::SaveCCDLuminancePara() const
{
	CIniFile IniFile;
	CString str,path;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\CCDLuminacePara");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		IniFile.WriteSection("ExtFiducial");
		IniFile.WriteItemInt("ExtLeftCaxial",GetDoc().m_lCCDLumLC_OUT);
		IniFile.WriteItemInt("ExtLeftRinged",GetDoc().m_lCCDLumLR_OUT);
		IniFile.WriteItemInt("ExtRightCaxial",GetDoc().m_lCCDLumRC_OUT);
		IniFile.WriteItemInt("ExtRightRinged",GetDoc().m_lCCDLumRR_OUT);
		IniFile.WriteItemInt("ExtLeftInfrared",GetDoc().m_infraredSetVakue[0][0]);
		IniFile.WriteItemInt("ExtRightInfrared",GetDoc().m_infraredSetVakue[0][1]);
		IniFile.WriteString("\n");

		IniFile.WriteSection("InsideFiducial");
		IniFile.WriteItemInt("InsLeftCaxial",GetDoc().m_lCCDLumLC_INS);
		IniFile.WriteItemInt("InsLeftRinged",GetDoc().m_lCCDLumLR_INS);
		IniFile.WriteItemInt("InsRightCaxial",GetDoc().m_lCCDLumRC_INS);
		IniFile.WriteItemInt("InsRightRinged",GetDoc().m_lCCDLumRR_INS);
		IniFile.WriteItemInt("InsLeftInfrared",GetDoc().m_infraredSetVakue[1][0]);
		IniFile.WriteItemInt("InsRightInfrared",GetDoc().m_infraredSetVakue[1][1]);
		IniFile.WriteString("\n");

		IniFile.WriteSection("GlvEmendation");
		IniFile.WriteItemInt("GlvEmeLeftCaxial",GetDoc().m_lCCDLumLC_GLV);
		IniFile.WriteItemInt("GlvEmeLeftRinged",GetDoc().m_lCCDLumLR_GLV);
		IniFile.WriteItemInt("GlvEmeRightCaxial",GetDoc().m_lCCDLumRC_GLV);
		IniFile.WriteItemInt("GlvEmeRightRinged",GetDoc().m_lCCDLumRR_GLV);
		IniFile.WriteItemInt("GlvEmeLeftInfrared",GetDoc().m_infraredSetVakue[2][0]);
		IniFile.WriteItemInt("GlvEmeRightInfrared",GetDoc().m_infraredSetVakue[2][1]);
		IniFile.WriteString("\n");

		IniFile.WriteSection("Emendation");
		IniFile.WriteItemInt("OrgEmeLeftCaxial",GetDoc().m_lCCDLumLC_EME);
		IniFile.WriteItemInt("OrgEmeLeftRinged",GetDoc().m_lCCDLumLR_EME);
		IniFile.WriteItemInt("OrgEmeRightCaxial",GetDoc().m_lCCDLumRC_EME);
		IniFile.WriteItemInt("OrgEmeRightRinged",GetDoc().m_lCCDLumRR_EME);
		IniFile.WriteItemInt("OrgEmeLeftInfrared",GetDoc().m_infraredSetVakue[3][0]);
		IniFile.WriteItemInt("OrgEmeRightInfrared",GetDoc().m_infraredSetVakue[3][1]);
		IniFile.WriteString("\n");

		IniFile.WriteSection("CCDInterval");
		IniFile.WriteItemInt("CCDIntLeftCaxial",GetDoc().m_lCCDLumLC_CCD);
		IniFile.WriteItemInt("CCDIntLeftRinged",GetDoc().m_lCCDLumLR_CCD);
		IniFile.WriteItemInt("CCDIntRightCaxial",GetDoc().m_lCCDLumRC_CCD);
		IniFile.WriteItemInt("CCDIntRightRinged",GetDoc().m_lCCDLumRR_CCD);
		IniFile.WriteItemInt("CCDIntLeftInfrared",GetDoc().m_infraredSetVakue[4][0]);
		IniFile.WriteItemInt("CCDIntRightInfrared",GetDoc().m_infraredSetVakue[4][1]);
		IniFile.WriteString("\n");

		IniFile.WriteSection("LocalMark");
		IniFile.WriteItemInt("LocalMarkLeftCaxial",GetDoc().m_lCCDLumLC_LM);
		IniFile.WriteItemInt("LocalMarkLeftRinged",GetDoc().m_lCCDLumLR_LM);
		IniFile.WriteItemInt("LocalMarkRightCaxial",GetDoc().m_lCCDLumRC_LM);
		IniFile.WriteItemInt("LocalMarkRightRinged",GetDoc().m_lCCDLumRR_LM);
		IniFile.WriteItemInt("LocalMarkLeftInfrared",GetDoc().m_infraredSetVakue[5][0]);
		IniFile.WriteItemInt("LocalMarkRightInfrared",GetDoc().m_infraredSetVakue[5][1]);
		IniFile.WriteString("\n");

		IniFile.CloseIniFile();
	}
	else  //未能打开
	{
		strncpy(ez,GetLang().GetWarningText(13015),256);
		AfxMessageBox(ez,MB_OK);//"无法保存 系统参数！"
#ifdef USELOG
		GetLog().Append_pro(10102,"SaveCCDLuminancePara");//"无法保存 系统参数"
#endif
	}

	return TRUE;
}

BOOL SystemDoc::SaveProcessParam() const
{
	CIniFile IniFile;
	CString str,path;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\ProcessPara");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		// 有关CCD 参数
		IniFile.WriteSection("CCDToGlvOffset");
		IniFile.WriteItemInt("Offset1_X",   GetDoc().m_triTestCCDToGlvOffL.x);
		IniFile.WriteItemInt("Offset1_Y",   GetDoc().m_triTestCCDToGlvOffL.y);

		IniFile.WriteItemInt("CCDOffset1_X",   GetDoc().m_triTestCCDToCCDOffL.x);
		IniFile.WriteItemInt("CCDOffset1_Y",   GetDoc().m_triTestCCDToCCDOffL.y);

		IniFile.WriteItemInt("Offset1_Z",   GetDoc().m_triTestCCDToGlvOffL.z);
		IniFile.WriteItemInt("Offset1_LongPathX",   GetDoc().m_triTestLongPathCCDToGlvOffL.x);
		IniFile.WriteItemInt("Offset1_LongPathY",   GetDoc().m_triTestLongPathCCDToGlvOffL.y);
		IniFile.WriteItemInt("Offset1_LongPathZ",   GetDoc().m_triTestLongPathCCDToGlvOffL.z);

		IniFile.WriteItemInt("Offset2_X",   GetDoc().m_triTestCCDToGlvOffR.x);
		IniFile.WriteItemInt("Offset2_Y",   GetDoc().m_triTestCCDToGlvOffR.y);

        IniFile.WriteItemInt("CCDOffset2_X",   GetDoc().m_triTestCCDToCCDOffR.x);
		IniFile.WriteItemInt("CCDOffset2_Y",   GetDoc().m_triTestCCDToCCDOffR.y);
		IniFile.WriteItemInt("Offset2_Z",   GetDoc().m_triTestCCDToGlvOffR.z);
		IniFile.WriteItemInt("Offset2_LongPathX",   GetDoc().m_triTestLongPathCCDToGlvOffR.x);
		IniFile.WriteItemInt("Offset2_LongPathY",   GetDoc().m_triTestLongPathCCDToGlvOffR.y);
		IniFile.WriteItemInt("Offset2_LongPathZ",   GetDoc().m_triTestLongPathCCDToGlvOffR.z);
/*
		IniFile.WriteItemInt("SysOffsetLT_X",   GetDoc().m_triCCDToGlvSysOffsetLT.x);
		IniFile.WriteItemInt("SysOffsetLT_Y",   GetDoc().m_triCCDToGlvSysOffsetLT.y);
		IniFile.WriteItemInt("SysOffsetLT_ZA",  GetDoc().m_triCCDToGlvSysOffsetLT.z);

		IniFile.WriteItemInt("SysOffsetRT_X",   GetDoc().m_triCCDToGlvSysOffsetRT.x);
		IniFile.WriteItemInt("SysOffsetRT_Y",   GetDoc().m_triCCDToGlvSysOffsetRT.y);
		IniFile.WriteItemInt("SysOffsetRT_ZA",  GetDoc().m_triCCDToGlvSysOffsetRT.z);
*/
		IniFile.WriteItemInt("SysOffsetLT_SX",   GetDoc().m_triSCCDToGlvSysOffsetLT.x);
		IniFile.WriteItemInt("SysOffsetLT_SY",   GetDoc().m_triSCCDToGlvSysOffsetLT.y);
		IniFile.WriteItemInt("SysOffsetLT_SZA",  GetDoc().m_triSCCDToGlvSysOffsetLT.z);
		IniFile.WriteItemInt("SysOffsetLT_LX",   GetDoc().m_triLCCDToGlvSysOffsetLT.x);
		IniFile.WriteItemInt("SysOffsetLT_LY",   GetDoc().m_triLCCDToGlvSysOffsetLT.y);
		IniFile.WriteItemInt("SysOffsetLT_LZA",  GetDoc().m_triLCCDToGlvSysOffsetLT.z);

		IniFile.WriteItemInt("SysOffsetRT_SX",   GetDoc().m_triSCCDToGlvSysOffsetRT.x);
		IniFile.WriteItemInt("SysOffsetRT_SY",   GetDoc().m_triSCCDToGlvSysOffsetRT.y);
		IniFile.WriteItemInt("SysOffsetRT_SZA",  GetDoc().m_triSCCDToGlvSysOffsetRT.z);
		IniFile.WriteItemInt("SysOffsetRT_LX",   GetDoc().m_triLCCDToGlvSysOffsetRT.x);
		IniFile.WriteItemInt("SysOffsetRT_LY",   GetDoc().m_triLCCDToGlvSysOffsetRT.y);
		IniFile.WriteItemInt("SysOffsetRT_LZA",  GetDoc().m_triLCCDToGlvSysOffsetRT.z);
		
//		IniFile.WriteItemInt("GlvAdjustApt",GetDoc().m_lGlvAdjustApt);
		IniFile.WriteString("\n");

		//正常加工时的CCD焦距 光源亮度
		IniFile.WriteSection("CCDProcParam");

		IniFile.WriteItemInt("CCDFocusPosL", GetDoc().m_lCCDFocusPosL);
		IniFile.WriteItemInt("CCDFocusPosR", GetDoc().m_lCCDFocusPosR);
	//	IniFile.WriteItemInt("CCDLightnessL", GetDoc().m_lCCDLumLR);
	//	IniFile.WriteItemInt("CCDLightnessR", GetDoc().m_lCCDLumRR);
		
		//
		IniFile.WriteString("\n");
	
		//有关Laser 参数
		IniFile.WriteSection("LaserProPara");
		IniFile.WriteItemInt("LaserPowTestPosLX", GetDoc().m_triLaserPowerTestL.x);
		IniFile.WriteItemInt("LaserPowTestPosLY", GetDoc().m_triLaserPowerTestL.y);
		IniFile.WriteItemInt("LaserPowTestPosLZ", GetDoc().m_triLaserPowerTestL.z);
		IniFile.WriteItemInt("LaserDrillPosL",	 GetDoc().m_lLaserDrillPosL);
		IniFile.WriteItemInt("LongPathLaserDrillPosL",	 GetDoc().m_lLongPathLaserDrillPosL);
		

		IniFile.WriteItemInt("LaserPowTestPosRX", GetDoc().m_triLaserPowerTestR.x);
		IniFile.WriteItemInt("LaserPowTestPosRY", GetDoc().m_triLaserPowerTestR.y);
		IniFile.WriteItemInt("LaserPowTestPosRZ", GetDoc().m_triLaserPowerTestR.z);
		IniFile.WriteItemInt("LaserDrillPosR",	 GetDoc().m_lLaserDrillPosR);
		IniFile.WriteItemInt("LongPathLaserDrillPosR",	 GetDoc().m_lLongPathLaserDrillPosR);

		IniFile.WriteString("\n");
		IniFile.WriteSection("LaserTestCleanRefPos");
		IniFile.WriteItemInt("CleanRefPos_X", GetDoc().m_crdLaserTestCleanRef.x);
		IniFile.WriteItemInt("CleanRefPos_Y", GetDoc().m_crdLaserTestCleanRef.y);
		IniFile.WriteString("\n");
   
		//CCD相对距离
		IniFile.WriteString("\n");
		IniFile.WriteSection("CCDDistance");
		IniFile.WriteItemInt("CCDDistance_X", GetDoc().m_crdCCDDistance.x);
		IniFile.WriteItemInt("CCDDistance_Y", GetDoc().m_crdCCDDistance.y);
		IniFile.WriteString("\n");
   
		// SL Bit per mm
		IniFile.WriteString("\n");
		IniFile.WriteSection("SLBitPermm");
		IniFile.WriteItemInt("SLBitPermm", GetDoc().m_ulSLBitPermm);
		IniFile.WriteString("\n");
  
		//测试用能量等
		IniFile.WriteSection("TestParam");
		IniFile.WriteItemInt("TestBoardThickness",GetDoc().m_ulTestBoardThickness);
		IniFile.WriteItemInt("GlvAdjustApt",GetDoc().m_lGlvAdjustApt);
		IniFile.WriteItemInt("TestPlsRelease", GetDoc().m_lTestPlsRelease);
		IniFile.WriteItemInt("WarmUpPlsRelease", GetDoc().m_lWarmUpPlsRelease);//机器预热
		IniFile.WriteItemInt("TestPlsPeriod",  GetDoc().m_lTestPlsPeriod);
		IniFile.WriteItemInt("TestLaserOnTime",GetDoc().m_lTestLaserOnTime);
		IniFile.WriteItemInt("TestJumpDelay",  GetDoc().m_lTestJumpDelay);
		IniFile.WriteItemInt("TestJumpSpeed",  GetDoc().m_lTestJumpSpeed);
				IniFile.WriteItemInt("RTC5TestBasicDelay",  GetDoc().m_iRTC5TestBasicDelay);
		IniFile.WriteString("\n");

		IniFile.WriteSection("ProcParam");
		IniFile.WriteItemInt("ProcJumpDelay",  GetDoc().m_lProcJumpDelay);
		IniFile.WriteItemInt("ProcJumpSpeed",  GetDoc().m_lProcJumpSpeed);
		IniFile.WriteItemInt("ProcJumpDelay0",  GetDoc().m_lProcJumpDelay0);//ly add 20111123
		IniFile.WriteItemInt("ProcJumpLenth",  GetDoc().m_lProcJumpLenth);//ly add 20111123
		IniFile.WriteItemInt("RTC5AddBasicDelay",  GetDoc().m_iRTC5AddBasicDelay);

		IniFile.WriteItemInt("ProcFirstJumpDelay",  GetDoc().m_lProcFirstJumpDelay);//ly add 20111123
		IniFile.WriteItemInt("ProcFirstDelayGap",  GetDoc().m_lProcFirstDelayGap);//ly add 20111123
		IniFile.WriteItemInt("ProcOtherJumpDelay",  GetDoc().m_lProcOtherJumpDelay);//ly add 20120811
		IniFile.WriteItemInt("ProcOtherDelayGap",  GetDoc().m_lProcOtherDelayGap);//ly add 20120811
		IniFile.WriteItemInt("ProcDelayJump",  GetDoc().m_lProcDelayJump);//ly add 20130315
		IniFile.WriteItemInt("ProcNULLMark",  GetDoc().m_lNULLMark);//ly add 20120206
		IniFile.WriteItemInt("ProcTestMode",  GetDoc().m_lTestMode);//ly add 20120208
		IniFile.WriteItemInt("OutFidsOffSet",  GetDoc().m_iOutFidsOffset);//ly add 20140504
		IniFile.WriteItemInt("FZInnerOffSet",  GetDoc().m_iFZInnerOffset);//ly add 20120522
		IniFile.WriteItemF64("FZInnerScale",GetDoc().m_fFZInnerScale);//ly add 20120522
		IniFile.WriteItemInt("LaserComp",GetDoc().m_laserComp);//ly add 20120919
		IniFile.WriteItemInt("LaserTestComp",GetDoc().m_laserTestComp);//ly add 20121227
		IniFile.WriteItemInt("NewDelay",  GetDoc().m_bNewDelay);//ly add 20130821
		IniFile.WriteItemInt("TableDelay", GetDoc().m_lTableDelay);//ly add 20121013
		IniFile.WriteItemF64("DrilledHoles",  GetDoc().m_lDrldHolesSum);//ly add 20121230
		IniFile.WriteItemF64("PowerScale",  GetDoc().m_lPowerScale);

		IniFile.WriteItemInt("LoadPCBTime",  GetDoc().m_lLoadPCBTime);
		IniFile.WriteItemInt("UnLoadPCBTime",  GetDoc().m_lUnLoadPCBTime);

		IniFile.WriteItemInt("LaserComp1",GetDoc().m_laserComp1);				//20200515
		IniFile.WriteItemInt("LaserComp2",GetDoc().m_laserComp2);

		IniFile.WriteString("\n");

		IniFile.WriteSection("DrillRegion");
	    IniFile.WriteItemInt("JumpDelay",  GetDoc().m_lDrlRegJumpDelay);
		IniFile.WriteItemInt("JumpSpeed",  GetDoc().m_lDrlRegJumpSpeed);
		IniFile.WriteItemInt("Period",     GetDoc().m_lDrlRegPlsPeriod);
		IniFile.WriteItemInt("Times",    GetDoc().m_lDrlRegPlsTimes);
		IniFile.WriteItemInt("RegionPointDis",    m_lDrlRegPointDis);
		IniFile.WriteItemInt("Release",    GetDoc().m_lDrlRegPlsRelease);
		IniFile.WriteItemInt("Release2",    GetDoc().m_lDrlRegPls2Release);
		IniFile.WriteItemInt("Release3",    GetDoc().m_lDrlRegPls3Release);
		IniFile.WriteItemInt("Release4",    GetDoc().m_lDrlRegPls4Release);
		IniFile.WriteItemInt("Release5",    GetDoc().m_lDrlRegPls5Release);
		IniFile.WriteItemInt("Aperture",   GetDoc().m_lDrlRegApertureNo);
		IniFile.WriteItemInt("RegionDim",  GetDoc().m_iRegionDim);
		IniFile.WriteItemInt("Times",      GetDoc().m_lDrlRegPulseNum);
	    IniFile.WriteItemInt("DrillCoil",  GetDoc().m_bDrillCoil);				//20170224
		IniFile.WriteString("\n");

		//yutingxun 7-5 06
		IniFile.WriteSection("DrillTxtInfo");
	    IniFile.WriteItemInt("TxtJumpDelay",  GetDoc().m_lDrlTxtJumpDelay);
		IniFile.WriteItemInt("TxtJumpSpeed",  GetDoc().m_lDrlTxtJumpSpeed);
		IniFile.WriteItemInt("TxtPeriod",     GetDoc().m_lDrlTxtPlsPeriod);
		IniFile.WriteItemInt("TxtRelease",    GetDoc().m_lDrlTxtPlsRelease);
		IniFile.WriteItemInt("TxtAperture",   GetDoc().m_lDrlTxtApertureNo);
		IniFile.WriteItemInt("TxtTimes",      GetDoc().m_lDrlTxtPulseNum);
		IniFile.WriteItemF64("TextHeigth",      GetDoc().m_fTextHeigth);
		IniFile.WriteString("\n");
			//yutingxun 8-23 06
		IniFile.WriteSection("WarningTime");
	    IniFile.WriteItemInt("AdjTime",  GetDoc().m_ulAdjTime);
		IniFile.WriteItemInt("LaserPowerTime",  GetDoc().m_ulLaserPowerTime);
		IniFile.WriteItemString("OperationRateTime",  GetDoc().m_OperationRateTime);
		IniFile.WriteItemString("OperationRateTimeNight",  GetDoc().m_OperationRateTimeNight);
		IniFile.WriteString("\n");
		IniFile.WriteSection("AdjustLaserPara");
		IniFile.WriteItemInt("Aperture",  GetDoc().m_lAdjustApertureNo);
		IniFile.WriteItemInt("LongPathAperture",  GetDoc().m_lLongPathAdjustApertureNo);
	    IniFile.WriteItemInt("JumpDelay",  GetDoc().m_lAdjustJumpDelay);
		IniFile.WriteItemInt("JumpSpeed",  GetDoc().m_lAdjustJumpSpeed);
		IniFile.WriteItemInt("Period",     GetDoc().m_lAdjustPlsPeriod);
		IniFile.WriteItemInt("Release",    GetDoc().m_lAdjustPlsRelease);
	//
		IniFile.WriteItemInt("GlvAdjRelease", GetDoc().m_ulAdjPlslRelease);
		IniFile.WriteItemInt("GlvAdjPosX",    GetDoc().m_lAdjPosX);
		IniFile.WriteItemInt("GlvAdjPosY",    GetDoc().m_lAdjPosY);
		IniFile.WriteString("\n");


		//测试板厚
	
		IniFile.WriteSection("Other");
		IniFile.WriteItemInt("TestThicknessPos",GetDoc().m_TestThicknessZPos);
		IniFile.WriteItemInt("AptOffset",       GetDoc().m_lAptOffsetCrd);
		//BET偏置
		IniFile.WriteItemInt("BETPRIOffset",       GetDoc().m_lBETPriOffset);
		IniFile.WriteItemInt("BETSUBOffset",       GetDoc().m_lBETOffsetCrd);
//		IniFile.WriteItemInt("PCBThickness",    GetDoc().m_lPCBThickness);

		//第二套BET光圈参数
		IniFile.WriteItemInt("AptOffset2",       GetDoc().m_lAptOffsetCrd2);
		IniFile.WriteItemInt("BETPRIOffset2",       GetDoc().m_lBETPriOffset2);
		IniFile.WriteItemInt("BETSUBOffset2",       GetDoc().m_lBETSubOffsetCrd2);	
		
		IniFile.WriteString("\n");
		
		//上下料
		IniFile.WriteSection("Load&Unload");
		IniFile.WriteItemInt("LoadPitchPos",	   GetDoc().m_LoadPitchPos);
	    IniFile.WriteItemInt("LoadBenchmark",	   GetDoc().m_LoadBenchmark);
		IniFile.WriteItemInt("LoadTransPos",	   GetDoc().m_LoadTransPos);
		IniFile.WriteItemInt("LoadLiftBenchmark",  GetDoc().m_LoadLiftBM);

		IniFile.WriteItemInt("LoadTune",			GetDoc().m_LoadTunePos);
		IniFile.WriteItemInt("UnLoadTune",			GetDoc().m_UnLoadTunePos);
		IniFile.WriteItemInt("UnloadPitchPos",	   GetDoc().m_UnloadPitchPos);
		IniFile.WriteItemInt("UnloadBenchmark",	   GetDoc().m_UnloadBenchmark);
		IniFile.WriteItemInt("UnloadTranshPos",	   GetDoc().m_UnloadTransPos);
		IniFile.WriteItemInt("UnloadLiftBenchmark",GetDoc().m_UnloadLiftBM);
		IniFile.WriteItemInt("LoadOptimize",GetDoc().m_LoadOptimize);//ly add 20120919
		IniFile.WriteItemInt("NGSum",GetDoc().m_lNgSum);//ly add 20121127
		IniFile.WriteItemInt("NGThred",GetDoc().m_lNgThrd);//ly add 20121127
		
		IniFile.WriteString("\n");
	
		//平台
		IniFile.WriteSection("TabPos");
		IniFile.WriteItemInt("TabBenchmarkX",	  GetDoc().m_crdTabBenchmark.x);
		IniFile.WriteItemInt("TabBenchmarkY",	  GetDoc().m_crdTabBenchmark.y);

		IniFile.WriteItemInt("TabLoadPosX",	       GetDoc().m_crdTabLoadPos.x);
		IniFile.WriteItemInt("TabLoadPosY",	       GetDoc().m_crdTabLoadPos.y);

		IniFile.WriteItemInt("TabUnloadPosX",	   GetDoc().m_crdTabUnloadPos.x);
		IniFile.WriteItemInt("TabUnloadPosY",	   GetDoc().m_crdTabUnloadPos.y);


		IniFile.WriteItemInt("OVerTabLoadPosX",	       GetDoc().m_crdOVerTabLoadPos.x);
		IniFile.WriteItemInt("OVerTabLoadPosY",	       GetDoc().m_crdOVerTabLoadPos.y);
		
		IniFile.WriteItemInt("OVerTabUnloadPosX",	   GetDoc().m_crdOVerTabUnloadPos.x);
		IniFile.WriteItemInt("OVerTabUnloadPosY",	   GetDoc().m_crdOVerTabUnloadPos.y);


		IniFile.WriteItemInt("TabPitchDistanceX",  GetDoc().m_crdTabPitchDisXY.x);
		IniFile.WriteItemInt("TabPitchDistanceY",  GetDoc().m_crdTabPitchDisXY.y);
	
		IniFile.WriteString("\n");
	
		IniFile.WriteSection("CCD Threshold");
		IniFile.WriteItemInt("ProcThreshold",m_lCCDProcThreshold);
		IniFile.WriteItemInt("ProcInnerThreshold",m_lCCDProcInnerThreshold);
		IniFile.WriteItemInt("ProcInnerRange",m_lCCDProcInnerRange);//ly add 20121009

		IniFile.WriteItemInt("AdjThreshold",m_lCCDAdjustThreshold);
		IniFile.WriteItemInt("ContrastThrd",m_lCCDContrastThrd);//ly add 20140328
		IniFile.WriteItemInt("DistanceCenterThrd",m_iDistanceCenterThreshold);//ly add 20140328

		IniFile.WriteString("\n");

		IniFile.WriteSection("OtherThreshold");
		IniFile.WriteItemInt("GlvThreshold",m_iGlvAdjustThreshold);
		IniFile.WriteItemF64("ScaleThreshold",m_fPCBScaleThreshold);
		IniFile.WriteItemInt("ScaleThrd",m_fPCBScaleThrd);//ly add 20120919
		IniFile.WriteItemInt("ScaleType",m_ScaleType);//ly add 20120919
		IniFile.WriteItemInt("AutoThickError",m_iAutoThickError);
		IniFile.WriteItemF64("LaserPowerTest",m_fLaserPowerTestSt);
		IniFile.WriteItemF64("LaserPowerTestMax",m_fLaserPowerTestMax);//ly add 20120924
		IniFile.WriteString("\n");
		//标靶极性-cognex use
		IniFile.WriteSection("FiducialPolarity");
		IniFile.WriteItemInt("MainFiducial",m_lMainFiduPolarity);
        IniFile.WriteItemInt("InnerFiducial",m_lInnerFiduPolarity);
		//有关标示	
		IniFile.WriteSection("MarkerInfo");
		IniFile.WriteItemString("MachineSn",GetDoc().m_strMachineSn);
		IniFile.WriteItemF64("LotIDHeigth",GetDoc().m_strZoomSn);
		IniFile.WriteItemString("LotIDFix",GetDoc().m_strLOTIdFix);//ly add 20121127
		IniFile.WriteItemString("LotIDInc",GetDoc().m_strLOTIdInc);//ly add 20121127
		IniFile.WriteItemInt("EnMachSn",GetDoc().m_bEnMachSn);//ly add 20121127
		IniFile.WriteItemInt("EnManuDay",GetDoc().m_bEnManuDay);//ly add 20121127
		IniFile.WriteItemInt("EnManuTime",GetDoc().m_bEnManuTime);//ly add 20121127
		IniFile.WriteItemInt("EnManuString",GetDoc().m_bEnManuString);//ly add 20121127
		IniFile.WriteItemInt("EnLotID",GetDoc().m_bEnLOTSn);//ly add 20121127
		IniFile.WriteItemInt("EnLotIDFix",GetDoc().m_bEnLOTFix);//ly add 20121127
		IniFile.WriteItemInt("EnLotIDInc",GetDoc().m_bEnLOTInc);//ly add 20121127
		IniFile.WriteItemInt("EnLotIDScale",GetDoc().m_bEnLOTScale);//ly add 20121127
		IniFile.WriteItemInt("EnAxisNo",GetDoc().m_bEnAxisNo);//ly add 20121230
	    IniFile.WriteString("\n");
	
		//有关 分区等信息
		IniFile.WriteSection("ProcessInfo");
		IniFile.WriteItemInt("ProcessDir" ,		GetDoc().m_lProcessDir );
		IniFile.WriteItemInt("ProcessState" ,		GetDoc().m_lAutoProc );
		IniFile.WriteItemInt("ScanSize",  GetDoc().m_lScanSize );
		IniFile.WriteItemInt("ThickingType",  (int)GetDoc().m_ThickingType );
		IniFile.WriteItemInt("ProcMode",  GetDoc().m_ProcMode);
		IniFile.WriteItemInt("TechnicType",  GetDoc().m_TechnicType);	
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("CaliBoardThick");
		IniFile.WriteItemInt("CCDBoardThick" ,	GetDoc().m_lCCDBoardThick );
		IniFile.WriteItemInt("GalvoBoardThick" , GetDoc().m_lGalvoBoardThick );	
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("AutoThickingXY");
		IniFile.WriteItemInt("ThicknessX" ,	GetDoc().m_lThicknessX );
		IniFile.WriteItemInt("ThicknessY" , GetDoc().m_lThicknessY );	
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("AutoTestFunction");
		IniFile.WriteItemInt("PatternAdjust" ,	GetDoc().m_bEnableAutoAdjust );
		IniFile.WriteItemInt("LaserPower" , GetDoc().m_bEnableAutoPower );	
		IniFile.WriteItemInt("FidRetry" , GetDoc().m_bEnableFidRetry);//ly add 20120202
//		IniFile.WriteItemInt("ToolCycleMode" , GetDoc().m_bToolCycleMode);//ly add 20120705
		/*IniFile.WriteItemInt("En3Fid" , GetDoc().m_bEn3Fid);//ly add 20130121 *///ly delete 20131226 不保存允许3标靶的状态
		IniFile.WriteItemInt("ManuFindFid" , GetDoc().m_bMaFindFid);//ly add 20130121
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("FilePara");
		IniFile.WriteItemInt("FileUnit" ,	GetDoc().m_fileunit );
		IniFile.WriteItemInt("FileMode" , GetDoc().m_filemode );	
		IniFile.WriteItemInt("FileFormat" , GetDoc().m_fileformat);
		IniFile.WriteItemInt("FileDecNum" , GetDoc().m_filedecnum );	
		IniFile.WriteItemInt("FileIntNum" , GetDoc().m_fileintnum);
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("CalibrateTol");
		IniFile.WriteItemInt("GlvCaliOffsetTol" ,m_lGlvCaliOffsetTol);
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("TestThickness");	
		IniFile.WriteItemInt("ZSafePos" , m_lTestThicknessZSafePos);
		IniFile.WriteItemInt("Z1Compensation" , m_lTestThicknessCompensation[0]);	
		IniFile.WriteItemInt("Z2Compensation" , m_lTestThicknessCompensation[1]);
  	    IniFile.WriteString("\n");

		IniFile.WriteSection("PCBScale");
		IniFile.WriteItemF64("ManualScaleX",m_fManualScaleX);
		IniFile.WriteItemF64("ManualScaleY",m_fManualScaleY);
		IniFile.WriteString("\n");
//20160809
		IniFile.WriteSection("BigHoleSet");
		IniFile.WriteItemInt("BeamStep" , GetDoc().m_lSysBeamStep );
		IniFile.WriteItemInt("BeamDiameter" , GetDoc().m_lSysBeamDia );
  	    IniFile.WriteString("\n");
//20160812
		char buf[16];
		std::vector<ScaleSet>::iterator ssv;
		IniFile.WriteSection("ScaleSet");
		IniFile.WriteItemInt("ItemCount" ,	GetDoc().GetSysScaleSetSize() );
  	    IniFile.WriteString("\n");

	    for(int nn=0; nn<GetDoc().GetSysScaleSetSize();nn++)
		{
			ssv=GetDoc().GetSysScaleSet(nn);

			sprintf(buf,"DownLimit%d\0",nn);
			IniFile.WriteItemF64(buf,ssv->dbDownLimit);
			sprintf(buf,"UpLimit%d\0",nn);
			IniFile.WriteItemF64(buf,ssv->dbUpLimit);
			sprintf(buf,"Char%d\0",nn);
			IniFile.WriteItemString(buf,ssv->strChar);
  			IniFile.WriteString("\n");
		}

		IniFile.CloseIniFile();
	}
	else  //未能打开
	{
		strncpy(ez,GetLang().GetWarningText(13015),256);
		AfxMessageBox(ez,MB_OK);//"无法保存 系统参数！"
#ifdef USELOG
		GetLog().Append_pro(10102,"SaveProcessParam");//"无法保存系统参数"
#endif
	}

	return TRUE;
}

long SystemDoc::GetMotionCardSn(long CardNo) const
{
	ASSERT(CardNo==0||CardNo==1||CardNo==2);

	switch(CardNo)
	{
	case 0:
		return m_lMotionCardSn1;
	case 1:
		return m_lMotionCardSn2;
	case 2:
		return m_lMotionCardSn3;
	}
	return 0;

}

void SystemDoc::SetMotionCardSn(long CardNo, long CardSn)
{
	ASSERT(CardNo==0||CardNo==1||CardNo==2);
	
	switch(CardNo)
	{
		case 0:
			 m_lMotionCardSn1 = CardSn;
			 break;
		case 1:
			 m_lMotionCardSn2 = CardSn;
			 break;
		case 2:
			 m_lMotionCardSn3 = CardSn;
			 break;
	}
}

/*CString SystemDoc::GetLOTID() const
{
	return m_strLOTId;
}

void SystemDoc::SetLOTID(const CString& strLotId)
{
#ifdef USELOG
	if(m_strLOTId!=strLotId)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez,GetLang().GetWarningText(21102),256);
		BeforeStr.Format("%s",ez);//"前:"
		strncpy(ez,GetLang().GetWarningText(21103),256);
		AfterStr.Format("%s",ez);//"后: "

		AfterStr += strLotId;
		BeforeStr += m_strLOTId;
		GetLog().Append_pro(AfterStr,20076,BeforeStr);//"后:"+strLotId,"LotId改变","前:"+m_strLOTId
	}
#endif
	m_strLOTId = strLotId;
	
}*/

CString SystemDoc::GetLOTIDFix() const//ly add 20121127
{
	return m_strLOTIdFix;
}

void SystemDoc::SetLOTIDFix(const CString& strFix)//ly add 20121127
{
#ifdef USELOG
	if(m_strLOTIdFix!=strFix)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez,GetLang().GetWarningText(21102),256);
		BeforeStr.Format("Fix:%s",ez);//"前:"
		strncpy(ez,GetLang().GetWarningText(21103),256);
		AfterStr.Format("%s",ez);//"后: "

		AfterStr += strFix;
		BeforeStr += m_strLOTIdFix;
		GetLog().Append_pro(AfterStr,20076,BeforeStr);//"后:"+strFix,"LotId改变","前:"+m_strLOTIdFix
	}
#endif
	m_strLOTIdFix = strFix;
	
}

CString SystemDoc::GetLOTIDInc() const//ly add 20121127
{
	return m_strLOTIdInc;
}

void SystemDoc::SetNoProcessID(const CString& noProcessID)
{
	m_strNoProcessID ="___"+ noProcessID;	
}

CString SystemDoc::GetNoProcessID() const
{
	return m_strNoProcessID;
}

void SystemDoc::SetLOTIDInc(const CString& strInc)//ly add 20121127
{
#ifdef USELOG
	if(m_strLOTIdInc!=strInc)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez,GetLang().GetWarningText(21102),256);
		BeforeStr.Format("Inc:%s",ez);//"前:"
		strncpy(ez,GetLang().GetWarningText(21103),256);
		AfterStr.Format("%s",ez);//"后: "

		AfterStr += strInc;
		BeforeStr += m_strLOTIdInc;
		GetLog().Append_pro(AfterStr,20076,BeforeStr);//"后:"+strInc,"LotId改变","前:"+m_strLOTIdInc
	}
#endif
	m_strLOTIdInc = strInc;	
}

CString SystemDoc::GetMachSn() const
{
	return m_strMachineSn;
}

double SystemDoc::GetStrZoomSn() const
{
	return m_strZoomSn;
}

void SystemDoc::SetMachSn(const CString& strMachSn)
{
#ifdef USELOG
	if(m_strMachineSn!=strMachSn)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez,GetLang().GetWarningText(21102),256);
		BeforeStr.Format("%s",ez);//"前:"
		strncpy(ez,GetLang().GetWarningText(21103),256);
		AfterStr.Format("%s",ez);//"后:
		AfterStr += strMachSn;
		BeforeStr += m_strMachineSn;
		GetLog().Append_pro(AfterStr,20077,BeforeStr);//"后:"+strMachSn,"机器号改变","前:"+m_strMachineSn
	}
#endif
	m_strMachineSn = strMachSn;
}

void SystemDoc::SetStrZoomSn(const double& strZoomSn)
{
	m_strZoomSn = strZoomSn;
}
void SystemDoc::SetScanSize(long lSize)
{
	//ASSERT(lSize>=0&&lSize<65);
	if(lSize>GetDoc().GetScanSizeMax() || lSize<SCANSIZEMIN)//ly change 20140308
	{
		CString txt;

		txt.Format("%d-%d",SCANSIZEMIN,GetDoc().GetScanSizeMax());
		AfxMessageBox(txt);
	}
	char ez[256]={""};//ly 20110404
#ifdef USELOG
	if(m_lScanSize!=lSize)
	{
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lScanSize);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lSize);//"后:%d"

		GetLog().Append_pro(AfterStr,20078,BeforeStr);//"扫描区域改变"
	}
#endif
	m_lScanSize = lSize;
}
long SystemDoc::GetScanSize() const
{
	return m_lScanSize;
}

long SystemDoc::GetProcessDir() const
{
	return m_lProcessDir;
}

void SystemDoc::SetProcessDir(long lDir)
{
	ASSERT(lDir==0||lDir==1);
	m_lProcessDir = lDir;
}

long SystemDoc::GetProcessState() const
{
	return m_lAutoProc;
}

bool SystemDoc::SetProcessState(long bAutoProc)
{
	bool hasChanged = false;
//#ifdef USELOG
	if(m_lAutoProc!=bAutoProc)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAutoProc);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,bAutoProc);//"后:%d"

		GetLog().Append_pro(AfterStr,20079,BeforeStr);//"加工方式改变"
		hasChanged = true;
	}
//#endif
	m_lAutoProc = bAutoProc;
	return hasChanged;
}

long SystemDoc::GetProcessSide() const
{
	return m_lProcSide;
}

void SystemDoc::SetProcessSide(long bProcSide)
{
	m_lProcSide = bProcSide;
}

UINT SystemDoc::GetProcedPCBNum() const
{
	return m_ulProcedPCBNum;
}

void SystemDoc::SetProcedPCBNum(UINT ulNum)
{
	m_ulProcedPCBNum = ulNum;
}

BOOL SystemDoc::DistributeSubarea()
{
	char ez[256]={""};//ly 20110405
	long rtn=0;

	if(!GetDoc().GetIsDoubleFileData())
	{
		if (m_bZHANHUARotate && GetExcellonData().CompareXAndY())
		{
			int nsel = AfxMessageBox("  X边大于Y边长度 \n点击'是'旋转90度,\n点击'否'不旋转导入",MB_YESNO);
			if(nsel == IDYES)
			{		  
				rtn = GetExcellonData().DistrbuteSubArea(GetDoc().GetScanSize()*1000,GetDoc().GetSLBitPerMM(),FALSE);
				rtn = GetExcellonData().DistrbuteSubAreaRotReverse();
			}
			else
				rtn = GetExcellonData().DistrbuteSubArea(GetDoc().GetScanSize()*1000,GetDoc().GetSLBitPerMM());
			
		}
		else	
			rtn = GetExcellonData().DistrbuteSubArea(GetDoc().GetScanSize()*1000,GetDoc().GetSLBitPerMM());
		
		if(rtn == FileHeightOutRange)    
		{ 
			strncpy(ez,GetLang().GetWarningText(11022),256);
			AfxMessageBox(ez);//"请检查文件数据的高度！"
			return FALSE;
		}
		else if(rtn ==FileWidthOutRange) 
		{
			strncpy(ez,GetLang().GetWarningText(11023),256);
			AfxMessageBox(ez);//"请检查文件数据的宽度！"
			return FALSE;
		}
	}
	else//----------------------------------------------------------------------------------20161109
	{
		Coord crdCenter0,crdCenter1;
		SetGlobalExcellonIndex(0);
		crdCenter0=GetExcellonData().GetInnerLayerCenter();
		SetGlobalExcellonIndex(1);
		crdCenter1=GetExcellonData().GetInnerLayerCenter();

		m_bExcellonData0IsUp=true;
		if(crdCenter0.y<crdCenter1.y)
			m_bExcellonData0IsUp=false;
		
		for(int index=0;index<2;index++)
		{
			SetGlobalExcellonIndex(index);
			rtn = GetExcellonData().DistrbuteSubArea(GetDoc().GetScanSize()*1000,GetDoc().GetSLBitPerMM());
		}
		
		if(rtn == FileHeightOutRange)    
		{ 
			strncpy(ez,GetLang().GetWarningText(11022),256);
			AfxMessageBox(ez);//"请检查文件数据的高度！"
			return FALSE;
		}
		else if(rtn ==FileWidthOutRange) 
		{
			strncpy(ez,GetLang().GetWarningText(11023),256);
			AfxMessageBox(ez);//"请检查文件数据的宽度！"
			return FALSE;
		}

		int rowCount=0;
		int colCount=0;
		SetGlobalExcellonIndex(0);
		colCount=GetExcellonData().GetSubAreaRow();
		rowCount=GetExcellonData().GetSubAreaCol();

		SetGlobalExcellonIndex(1);
		if(colCount<GetExcellonData().GetSubAreaRow())
			colCount=GetExcellonData().GetSubAreaRow();
		rowCount+=GetExcellonData().GetSubAreaCol();

		m_iDisplayColCount=colCount;
		m_iDisplayRowCount=rowCount;
	}
//--------------------------------------------------------------------------------------------	
	return TRUE;
}

long SystemDoc::GetTestPlsRelease() const
{
	return m_lTestPlsRelease;
}

void SystemDoc::SetTestPlsRelease(long lRelease)
{
#ifdef USELOG
	if(m_lTestPlsRelease!=lRelease)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lTestPlsRelease);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

		GetLog().Append_pro(AfterStr,20080,BeforeStr);//"测试脉冲宽度改变"
	}
#endif
	m_lTestPlsRelease = lRelease;
}

long SystemDoc::GetWarmUpPlsRelease() const//机器预热
{
	return m_lWarmUpPlsRelease;
}

void SystemDoc::SetWarmUpPlsRelease(long lRelease)//机器预热
{
#ifdef USELOG
	if(m_lWarmUpPlsRelease!=lRelease)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lWarmUpPlsRelease);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

		GetLog().Append_pro(AfterStr,20081,BeforeStr);//"预热测试脉冲宽度改变"
	}
#endif
	m_lWarmUpPlsRelease = lRelease;
}

void SystemDoc::SetTestPlsPeriod(long lPeriod)
{
#ifdef USELOG
	if(m_lTestPlsPeriod!=lPeriod)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lTestPlsPeriod);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPeriod);//"后:%d"

		GetLog().Append_pro(AfterStr,20082,BeforeStr);//"测试脉冲周期改变"
	}
#endif
	m_lTestPlsPeriod = 1000;//ly change 20111208 lPeriod;
}

long SystemDoc::GetTestPlsPeriod() const
{
	return m_lTestPlsPeriod;
}

void SystemDoc::SetTestLaserOnTime(long lTime)
{
#ifdef USELOG
	if(m_lTestLaserOnTime!=lTime)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lTestLaserOnTime);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lTime);//"后:%d"

		GetLog().Append_pro(AfterStr,20083,BeforeStr);//"测试激光时间改变"
	}
#endif
	m_lTestLaserOnTime = lTime;
}

long SystemDoc::GetTestLaserOnTime() const
{

	return m_lTestLaserOnTime;	
}
void SystemDoc::SetTestJumpSpeed(long lSpeed)
{
#ifdef USELOG
	if(m_lTestJumpSpeed!=lSpeed)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lTestJumpSpeed);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lSpeed);//"后:%d"

		GetLog().Append_pro(AfterStr,20084,BeforeStr);//"测试震镜跳转速度改变"
	}
#endif
	m_lTestJumpSpeed = 4000;//ly change 20111208 lSpeed;	
}

long SystemDoc::GetTestJumpSpeed() const
{

	return m_lTestJumpSpeed;
}

void SystemDoc::SetTestJumpDelay(long lDelay)
{
	#ifdef USELOG
	if(m_lTestJumpDelay!=lDelay)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lTestJumpDelay);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lDelay);//"后:%d"

		GetLog().Append_pro(AfterStr,20084,BeforeStr);//"测试震镜跳转速度改变"
	}
#endif
	m_lTestJumpDelay = 400;//ly change 20111208 lDelay;
}

long SystemDoc::GetTestJumpDelay() const
{
	return m_lTestJumpDelay;
}

void SystemDoc::SetBaseDelay(long lDelay)
{
	m_BaseDelay=lDelay;
}
long SystemDoc::GetBaseDelay() const
{
	return m_BaseDelay;
}

MotionSpeed SystemDoc::GetMoveParam(UINT ulAxis) const
{
	return m_sysMotionPara[ulAxis];
}

void SystemDoc::SetMoveParam(UINT ulAxis, const MotionSpeed &ms)
{
	m_sysMotionPara[ulAxis] = ms;
}

long SystemDoc::GetMoveAcc(UINT ulAxis) const
{
	switch(ulAxis)
	{
	case AXISTABX:
			return m_sysMotionPara[0].lAcc;
	case AXISTABY:
			return m_sysMotionPara[1].lAcc;
    case AXISTAB:
		    return m_sysMotionPara[2].lAcc;
	case AXISBETPRI:
	case AXISBETSUB:
			return m_sysMotionPara[3].lAcc;
	case AXISAPT:
			return m_sysMotionPara[4].lAcc;
	case AXISLOADX:
			return m_sysMotionPara[5].lAcc;
	case AXISLOADY:
			return m_sysMotionPara[6].lAcc;
	case AXISLEFTZ:
			return m_sysMotionPara[7].lAcc;
	case AXISRIGHTZ:
			return m_sysMotionPara[8].lAcc;
	case AXISUNLOADX:
			return m_sysMotionPara[9].lAcc;
	case AXISUNLOADY:
			return m_sysMotionPara[10].lAcc;
	default:
		return 0;
	}
}

long SystemDoc::GetMoveDec(UINT ulAxis) const
{
	switch(ulAxis)
	{
	case AXISTABX:
			return m_sysMotionPara[0].lDec;
	case AXISTABY:
			return m_sysMotionPara[1].lDec;
	case AXISTAB:
			return m_sysMotionPara[2].lDec;
	case AXISBETPRI:
	case AXISBETSUB:
			return m_sysMotionPara[3].lDec;
	case AXISAPT:
			return m_sysMotionPara[4].lDec;
	case AXISLOADX:
			return m_sysMotionPara[5].lDec;
	case AXISLOADY:
			return m_sysMotionPara[6].lDec;
	case AXISLEFTZ:
			return m_sysMotionPara[7].lDec;
	case AXISRIGHTZ:
			return m_sysMotionPara[8].lDec;
	case AXISUNLOADX:
			return m_sysMotionPara[9].lDec;
	case AXISUNLOADY:
			return m_sysMotionPara[10].lDec;
	default:
			return 0;
	}
}

long SystemDoc::GetMoveMaxSpeed(UINT ulAxis) const
{
	switch(ulAxis)
	{
	case AXISTABX:
			return m_sysMotionPara[0].lMax;
	case AXISTABY:
			return m_sysMotionPara[1].lMax;
	case AXISTAB:
			return m_sysMotionPara[2].lMax;
	case AXISBETPRI:
			return m_sysMotionPara[3].lMax;
	case AXISBETSUB:
			return m_sysMotionPara[3].lMax;
	case AXISAPT:
			return m_sysMotionPara[4].lMax;
	case AXISLOADX:
			return m_sysMotionPara[5].lMax;
	case AXISLOADY:
		    return	m_sysMotionPara[6].lMax;
	case AXISLEFTZ:
			return m_sysMotionPara[7].lMax;
	case AXISRIGHTZ:
			return m_sysMotionPara[8].lMax;
	case AXISUNLOADX:
			return m_sysMotionPara[9].lMax;
	case AXISUNLOADY:
			return m_sysMotionPara[10].lMax;
	default:
			return 0;
	}
}
void SystemDoc::SetMoveDec(UINT ulAxis, long nValue)
{
	char ez[256]={""};//ly 20110404
	switch(ulAxis)
	{
	case AXISTABX:
#ifdef USELOG
		if(m_sysMotionPara[0].lDec!=nValue)
		{			
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[0].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			GetLog().Append_pro(AfterStr,20085,BeforeStr);//"X轴减速度改变"
		}
#endif
		m_sysMotionPara[0].lDec = nValue;
		break;
	case AXISTABY:
#ifdef USELOG
		if(m_sysMotionPara[1].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[1].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[1].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20086,BeforeStr);//"Y轴减速度改变"
		}
#endif
		m_sysMotionPara[1].lDec = nValue;
		break;
	case AXISTAB:
#ifdef USELOG
		if(m_sysMotionPara[2].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[2].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[2].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20087,BeforeStr);//"XY轴减速度改变"
		}
#endif
		m_sysMotionPara[2].lDec = nValue;
		break;
	case AXISBETPRI:
#ifdef USELOG
		if(m_sysMotionPara[3].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[3].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[3].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20088,BeforeStr);//"光束调节减速度改变"
		}
#endif
			m_sysMotionPara[3].lDec = nValue;
			break;
	case AXISAPT:
#ifdef USELOG
		if(m_sysMotionPara[4].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[4].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[4].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20089,BeforeStr);//"光圈减速度改变"
		}
#endif
		m_sysMotionPara[4].lDec = nValue;
		break;
	case AXISLOADX:
#ifdef USELOG
		if(m_sysMotionPara[5].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[5].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[5].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20090,BeforeStr);//"上料升降减速度改变"
		}
#endif
		m_sysMotionPara[5].lDec = nValue;
		break;
	case AXISLOADY:
#ifdef USELOG
		if(m_sysMotionPara[6].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[6].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[6].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20091,BeforeStr);//"上料平移减速度改变"
		}
#endif
		m_sysMotionPara[6].lDec = nValue;
		break;
	case AXISLEFTZ:
#ifdef USELOG
		if(m_sysMotionPara[7].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[7].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[7].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20092,BeforeStr);//"左侧Z轴减速度改变"
		}
#endif
		m_sysMotionPara[7].lDec = nValue;
		break;
	case AXISRIGHTZ:
#ifdef USELOG
		if(m_sysMotionPara[8].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[8].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[8].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20093,BeforeStr);//"右侧Z轴减速度改变"
		}
#endif
	
		m_sysMotionPara[8].lDec = nValue;
		break;
	case AXISUNLOADX:
#ifdef USELOG
		if(m_sysMotionPara[9].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[9].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[9].lDec);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20094,BeforeStr);//"下料升降减速度改变"
		}
#endif
		m_sysMotionPara[9].lDec = nValue;
		break;
	case AXISUNLOADY:
#ifdef USELOG
		if(m_sysMotionPara[10].lDec!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[10].lDec);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[10].lDec);//"前:%d"
		//	AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20095,BeforeStr);//"下料平移减速度改变"
		}
#endif
		m_sysMotionPara[10].lDec = nValue;
			break;
	default:
			return ;
	}
}

void SystemDoc::SetMoveAcc(UINT ulAxis, long nValue)
{
	char ez[256]={""};//ly 20110404
	switch(ulAxis)
	{
	case AXISTABX:
#ifdef USELOG
		if(m_sysMotionPara[0].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[0].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[0].lAcc);//"前:%d"
		//	AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20096,BeforeStr);//"X轴加速度改变"
		}
#endif
		m_sysMotionPara[0].lAcc = nValue;
		break;
	case AXISTABY:
#ifdef USELOG
		if(m_sysMotionPara[1].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[1].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[1].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20097,BeforeStr);//"Y轴加速度改变"
		}
#endif
		m_sysMotionPara[1].lAcc = nValue;
		break;
	case AXISTAB:
#ifdef USELOG
		if(m_sysMotionPara[2].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[2].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[2].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20098,BeforeStr);//"XY轴加速度改变"
		}
#endif
		m_sysMotionPara[2].lAcc = nValue;
		break;
	case AXISBETPRI:
#ifdef USELOG
		if(m_sysMotionPara[3].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[3].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[3].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20099,BeforeStr);//"光束调节加速度改变"
		}
#endif
		m_sysMotionPara[3].lAcc = nValue;
		break;
	case AXISAPT:
#ifdef USELOG
		if(m_sysMotionPara[4].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[4].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[4].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20100,BeforeStr);//"光圈加速度改变"
		}
#endif
			m_sysMotionPara[4].lAcc = nValue;
			break;
	case AXISLOADX:
#ifdef USELOG
		if(m_sysMotionPara[5].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[5].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[5].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20101,BeforeStr);//"上料升降加速度改变"
		}
#endif
		m_sysMotionPara[5].lAcc = nValue;
		break;
	case AXISLOADY:
#ifdef USELOG
		if(m_sysMotionPara[6].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[6].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[6].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20104,BeforeStr);//"上料平移加速度改变"
		}
#endif
			m_sysMotionPara[6].lAcc = nValue;
			break;
	case AXISLEFTZ:
#ifdef USELOG
		if(m_sysMotionPara[7].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[7].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[7].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20102,BeforeStr);//"左侧Z轴加速度改变"
		}
#endif
			m_sysMotionPara[7].lAcc = nValue;
			break;
	case AXISRIGHTZ:
		#ifdef USELOG
		if(m_sysMotionPara[8].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[8].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[8].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20103,BeforeStr);//"右侧Z轴加速度改变"
		}
#endif
			m_sysMotionPara[8].lAcc = nValue;
			break;
	case AXISUNLOADX:
#ifdef USELOG
		if(m_sysMotionPara[9].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[9].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[9].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20105,BeforeStr);//"下料升降加速度改变"
		}
#endif
		m_sysMotionPara[9].lAcc = nValue;
		break;
	case AXISUNLOADY:
#ifdef USELOG
		if(m_sysMotionPara[10].lAcc!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[10].lAcc);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[10].lAcc);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20106,BeforeStr);//"下料平移加速度改变"
		}
#endif
		m_sysMotionPara[10].lAcc = nValue;
		break;
	default:
		return ;
	}
}

void SystemDoc::SetMoveMaxSpeed(UINT ulAxis, long nValue)
{
	char ez[256]={""};//ly 20110404
	switch(ulAxis)
	{
	case AXISTABX:
#ifdef USELOG
		if(m_sysMotionPara[0].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[0].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[0].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20107,BeforeStr);//"X轴最大速度改变"
		}
#endif
		m_sysMotionPara[0].lMax = nValue;
		break;
	case AXISTABY:
		#ifdef USELOG
		if(m_sysMotionPara[1].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[1].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[1].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20108,BeforeStr);//"Y轴最大速度改变"
		}
#endif
			m_sysMotionPara[1].lMax = nValue;
			break;
	case AXISTAB:
			#ifdef USELOG
		if(m_sysMotionPara[2].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[2].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[2].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20109,BeforeStr);//"XY最大速度改变"
		}
#endif
			m_sysMotionPara[2].lMax = nValue;
			break;
	case AXISBETPRI:
#ifdef USELOG
		if(m_sysMotionPara[3].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[3].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[3].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20110,BeforeStr);//"光束调节最大速度改变"
		}
#endif
			m_sysMotionPara[3].lMax = nValue;
			break;
	case AXISAPT:
#ifdef USELOG
		if(m_sysMotionPara[4].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[4].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[4].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20111,BeforeStr);//"光圈最大速度改变"
		}
#endif
		m_sysMotionPara[4].lMax = nValue;
		break;
	case AXISLOADX:
#ifdef USELOG
		if(m_sysMotionPara[5].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[5].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"
			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[5].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20112,BeforeStr);//"上料升降最大速度改变"
		}
#endif
			m_sysMotionPara[5].lMax = nValue;
			break;
	case AXISLOADY:
#ifdef USELOG
		if(m_sysMotionPara[6].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[6].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[6].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20113,BeforeStr);//"上料平移最大速度改变"
		}
#endif
		m_sysMotionPara[6].lMax = nValue;
			break;
	case AXISLEFTZ:
#ifdef USELOG
		if(m_sysMotionPara[7].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[7].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[7].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20114,BeforeStr);//"左侧Z轴最大速度改变"
		}
#endif
			m_sysMotionPara[7].lMax = nValue;
			break;
	case AXISRIGHTZ:
#ifdef USELOG
		if(m_sysMotionPara[8].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[8].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[8].lMax);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20115,BeforeStr);//"右侧Z轴最大速度改变"
		}
#endif
			m_sysMotionPara[8].lMax = nValue;
			break;
	case AXISUNLOADX:
#ifdef USELOG
		if(m_sysMotionPara[9].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[9].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[9].lMax);//"前:%d"
		//	AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20116,BeforeStr);//"下料升降轴最大速度改变"
		}
#endif
			m_sysMotionPara[9].lMax = nValue;
			break;
	case AXISUNLOADY:
#ifdef USELOG
		if(m_sysMotionPara[10].lMax!=nValue)
		{
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_sysMotionPara[10].lMax);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,nValue);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21092),m_sysMotionPara[10].lMax);//"前:%d"
		//	AfterStr.Format(GetLang().GetWarningText(21093),nValue);//"后:%d "
			GetLog().Append_pro(AfterStr,20117,BeforeStr);//"下料平移轴最大速度改变"
		}
#endif
		m_sysMotionPara[10].lMax = nValue;
			break;
	default:
			return ;
	}
}

CRD	 SystemDoc::GetLoadBenchMarkPos()const
{
	return  m_LoadBenchmark;
}

CRD  SystemDoc::GetUnloadBenchMarkPos() const
{
	return  m_UnloadBenchmark;
}

void SystemDoc::SetLoadBenchMarkPos(CRD pos)
{
#ifdef USELOG
		if(m_LoadBenchmark!=pos)
		{
			char ez[256]={""};//ly 20110404
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_LoadBenchmark);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,pos);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_LoadBenchmark);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
			GetLog().Append_pro(AfterStr,20118,BeforeStr);//"上料平移基准改变"
		}
#endif
	m_LoadBenchmark = pos;
}

void SystemDoc::SetLoadTunePos(CRD pos)
{
#ifdef USELOG
		if(m_LoadTunePos!=pos)
		{
			char ez[256]={""};//ly 20110404
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_LoadTunePos);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,pos);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_LoadTunePos);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
			GetLog().Append_pro(AfterStr,20119,BeforeStr);//"上料调整改变"
		}
#endif
	m_LoadTunePos = pos;
}
void SystemDoc::SetUnLoadTunePos(CRD pos)
{
#ifdef USELOG
		if(m_UnLoadTunePos!=pos)
		{
			char ez[256]={""};//ly 20110404
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_UnLoadTunePos);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,pos);//"后:%d"

			//BeforeStr.Format(GetLang().GetWarningText(21092),m_UnLoadTunePos);//"前:%d"
			//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
			GetLog().Append_pro(AfterStr,20120,BeforeStr);//"下料调整改变"
		}
#endif
	m_UnLoadTunePos = pos;
}




void SystemDoc::SetUnLoadBenchMarkPos(CRD pos)
{
#ifdef USELOG
	if(m_UnloadBenchmark!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_UnloadBenchmark);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_UnloadBenchmark);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20121,BeforeStr);//"下料平移基准改变"
	}
#endif
	m_UnloadBenchmark = pos;
}

CRD	 SystemDoc::GetLoadPitchPos()const
{
	return m_LoadPitchPos;
}
CRD  SystemDoc::GetUnloadPitchPos() const
{
	return m_UnloadPitchPos;
}
void SystemDoc::SetLoadPitchPos(CRD pos)
{
	#ifdef USELOG
	if(m_LoadPitchPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_LoadPitchPos);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_LoadPitchPos);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20122,BeforeStr);//"上料定位位置改变"
	}
#endif
	 m_LoadPitchPos = pos;
}
void SystemDoc::SetUnLoadPitchPos(CRD pos)
{
		#ifdef USELOG
	if(m_UnloadPitchPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_UnloadPitchPos);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_UnloadPitchPos);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20123,BeforeStr);//"下料定位位置改变"
	}
#endif
	 m_UnloadPitchPos = pos;
}	
CRD	SystemDoc::GetLoadLiftBMPos()const
{
	return m_LoadLiftBM;
}
CRD SystemDoc::GetUnloadLiftBMPos() const
{
	return m_UnloadLiftBM;
}
void SystemDoc::SetLoadLiftBMPos(CRD pos)
{
#ifdef USELOG
	if(m_LoadLiftBM!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_LoadLiftBM);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_LoadLiftBM);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20124,BeforeStr);//"上料升降基准改变"
	}
#endif
	m_LoadLiftBM = pos;
}
void SystemDoc::SetUnloadLiftBMPos(CRD pos)
{
	#ifdef USELOG
	if(m_UnloadLiftBM!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_UnloadLiftBM);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_UnloadLiftBM);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20125,BeforeStr);//"下料升降基准改变"
	}
#endif
	m_UnloadLiftBM = pos;
}

CRD  SystemDoc::GetTestThicknessPos() const
{
	return m_TestThicknessZPos;
}
void SystemDoc::SetTestThicknessPos(CRD pos)
{
#ifdef USELOG
	if(m_TestThicknessZPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_TestThicknessZPos);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_TestThicknessZPos);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20126,BeforeStr);//"测厚Z轴位置改变"
	}
#endif
	m_TestThicknessZPos = pos;
}
long SystemDoc::GetPCBThickness()const
{
	return m_lPCBThickness;
}

long SystemDoc::GetPCBThicknessStd()const
{
	return m_lPCBThicknessStd;
}

void SystemDoc::SetPCBThickness( long lThickness)
{
#ifdef USELOG
	if(m_lPCBThickness!=lThickness)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lPCBThickness);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lThickness);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lPCBThickness);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lThickness);//"后:%d "
		GetLog().Append_pro(AfterStr,20127,BeforeStr);//"PCB板厚改变"
	}
#endif
	m_lPCBThickness = lThickness;
}

void SystemDoc::SetPCBThicknessStd( long lThickness)
{
	m_lPCBThicknessStd = lThickness;
}

Coord SystemDoc::GetTabBenchmark()const
{
	return m_crdTabBenchmark;
}

void SystemDoc::SetTabBenchmark(const Coord& pos)
{
#ifdef USELOG
	if(m_crdTabBenchmark!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdTabBenchmark.x,m_crdTabBenchmark.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,pos.x,pos.y);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21094),m_crdTabBenchmark.x,m_crdTabBenchmark.y);//"前:%d %d"
		//AfterStr.Format(GetLang().GetWarningText(21095),pos.x,pos.y);//"后:%d %d"
		GetLog().Append_pro(AfterStr,20128,BeforeStr);//"平台相对坐标改变"
	}
#endif
	m_crdTabBenchmark = pos;
}
void SystemDoc::SetTabPitchDistanceXY(const Coord &crd)
{
#ifdef USELOG
	if(m_crdTabPitchDisXY!=crd)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdTabPitchDisXY.x,m_crdTabPitchDisXY.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,crd.x,crd.y);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21094),m_crdTabPitchDisXY.x,m_crdTabPitchDisXY.y);//"前:%d %d"
		//AfterStr.Format(GetLang().GetWarningText(21095),crd.x,crd.y);//"后:%d %d"
		GetLog().Append_pro(AfterStr,20129,BeforeStr);//"平台定位距离改变"
	}
#endif
   m_crdTabPitchDisXY = crd;
}


Coord SystemDoc::GetTabPitchDistanceXY() const
{
   return m_crdTabPitchDisXY;
}

Coord SystemDoc::GetTabLoadPos  () const
{
	return m_crdTabLoadPos;
}

void  SystemDoc::SetTabLoadPos  (const Coord& pos)
{
#ifdef USELOG
	if(m_crdTabLoadPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdTabLoadPos.x,m_crdTabLoadPos.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,pos.x,pos.y);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21094),m_crdTabLoadPos.x,m_crdTabLoadPos.y);//"前:%d %d"
	//	AfterStr.Format(GetLang().GetWarningText(21095),pos.x,pos.y);//"后:%d %d "
		GetLog().Append_pro(AfterStr,20130,BeforeStr);//"平台接料位置改变"
	}
#endif
	m_crdTabLoadPos = pos;
}

Coord SystemDoc::GetTabUnloadPos() const
{
	return m_crdTabUnloadPos;
}

void  SystemDoc::SetTabUnloadPos(const Coord& pos)
{
#ifdef USELOG
	if(m_crdTabUnloadPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdTabUnloadPos.x,m_crdTabUnloadPos.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,pos.x,pos.y);//"后:%d"
		
		//	BeforeStr.Format(GetLang().GetWarningText(21094),m_crdTabUnloadPos.x,m_crdTabUnloadPos.y);//"前:%d %d"
		//	AfterStr.Format(GetLang().GetWarningText(21095),pos.x,pos.y);//"后:%d %d"
		GetLog().Append_pro(AfterStr,20131,BeforeStr);//"平台送料位置改变"
	}
#endif
	m_crdTabUnloadPos = pos;
	
}


Coord SystemDoc::GetOverTabLoadPos() const
{
	return m_crdOVerTabLoadPos;
}

void  SystemDoc::SetOverTabLoadPos  (const Coord& pos)
{
#ifdef USELOG
	if(m_crdOVerTabLoadPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdOVerTabLoadPos.x,m_crdOVerTabLoadPos.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,pos.x,pos.y);//"后:%d"
		
		//	BeforeStr.Format(GetLang().GetWarningText(21094),m_crdTabLoadPos.x,m_crdTabLoadPos.y);//"前:%d %d"
		//	AfterStr.Format(GetLang().GetWarningText(21095),pos.x,pos.y);//"后:%d %d "
		GetLog().Append_pro(AfterStr,20130,BeforeStr);//"平台接料位置改变"
	}
#endif
	m_crdOVerTabLoadPos = pos;
}

Coord SystemDoc::GetOverTabUnloadPos() const
{
	return m_crdOVerTabUnloadPos;
}

void  SystemDoc::SetOverTabUnloadPos(const Coord& pos)
{
#ifdef USELOG
	if(m_crdOVerTabUnloadPos!=pos)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdOVerTabUnloadPos.x,m_crdOVerTabUnloadPos.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,pos.x,pos.y);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21094),m_crdTabUnloadPos.x,m_crdTabUnloadPos.y);//"前:%d %d"
	//	AfterStr.Format(GetLang().GetWarningText(21095),pos.x,pos.y);//"后:%d %d"
		GetLog().Append_pro(AfterStr,20131,BeforeStr);//"平台送料位置改变"
	}
#endif
	m_crdOVerTabUnloadPos = pos;

}

//文件系统与控制系统的相对位置关系
Coord SystemDoc::GetFileToRealRelative() const
{
	return m_crdFileToReal;
}

void SystemDoc::SetFileToRealRelative(const Coord& crd)
{
	m_crdFileToReal = crd;
}

Coord SystemDoc::GetFileToRealRelative2(int direction) const
{
	return m_crdFileToReal2[direction];
}

void SystemDoc::SetFileToRealRelative2(const Coord& crd,int direction)
{
	m_crdFileToReal2[direction] = crd;
}
//
void SystemDoc::SetTestAperture(int nApt)
{
#ifdef USELOG
	if(m_lGlvAdjustApt!=nApt)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lGlvAdjustApt);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,nApt);//"后:%d"
		GetLog().Append_pro(AfterStr,20132,BeforeStr);//"震镜校正光圈改变"
	}
#endif	
	m_lGlvAdjustApt = nApt;
}

/*
void SystemDoc::SetLongPathTestAperture(int nApt)
{
#ifdef USELOG
	if(m_lLongPathGlvAdjustApt!=nApt)
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lLongPathGlvAdjustApt);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,nApt);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lLongPathGlvAdjustApt);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),nApt);//"后:%d"
		GetLog().Append_pro(AfterStr,20133,BeforeStr);//"长路径震镜校正光圈改变"
	}
#endif	
	m_lLongPathGlvAdjustApt = nApt;
}
*/

long SystemDoc::GetTestAperture() const
{
	return m_lGlvAdjustApt;
//	return GetDoc().GetFactualAperture(m_lGlvAdjustApt);		//2009 12 23 liq
}
/*
long SystemDoc::GetTestShowAperture() const			//
{
	return m_lGlvAdjustApt;
}
*/
BOOL SystemDoc::GetFileOpenState() const
{
	return m_bFileOpen;
}
void SystemDoc::SetFileOpenState(BOOL bOpen)
{
	m_bFileOpen = bOpen;
} 
BOOL SystemDoc::GetLaserPowerTestState() const
{
	return m_bLaserPowerTest;
}
void SystemDoc::SetLaserPowerTestState(BOOL bTest)
{
	m_bLaserPowerTest = bTest;
} 
BOOL SystemDoc::GetLaserWarmupState() const
{
	return m_bLaserWarmup;
}
void SystemDoc::SetLaserWarmupState(BOOL bWarmup)
{
	m_bLaserWarmup = bWarmup;
} 
BOOL SystemDoc::GetLaserPowerState() const
{
	return m_bLaserPowerOn;
}
void SystemDoc::SetLaserPowerState(BOOL bPower)
{
	m_bLaserPowerOn=bPower;
}

void SystemDoc::SetMachinePowerState(BOOL bPower)
{
	#ifdef USELOG
	if(m_bMachinePowerOn!=bPower)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_bMachinePowerOn);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,bPower);//"后:%d"

		GetLog().Append_pro(AfterStr,20134,BeforeStr);//"机器上断电改变"
	}
#endif	
	m_bMachinePowerOn=bPower;
}

BOOL SystemDoc::GetMachinePowerState() const
{
	return m_bMachinePowerOn;
}
	
BOOL SystemDoc::GetScanLabState() const
{
	return m_bLaserWarmup ;
}

void SystemDoc::SetScanLabState(BOOL bTest)
{
	m_bLaserWarmup = bTest;
} 

BOOL SystemDoc::GetMotorState() const
{
	return m_bAllHomed;
}
BOOL SystemDoc::GetIsFiducialDo() const
{
	return m_bIsFiducialDo;
}

void SystemDoc::SetMotorState(BOOL bHome)
{
	#ifdef USELOG
	if(m_bAllHomed!=bHome)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_bAllHomed);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,bHome);//"后:%d"

		GetLog().Append_pro(AfterStr,20135,BeforeStr);//"回零状态变化"
	}
#endif	
	m_bAllHomed = bHome;
}

void SystemDoc::SetIsFiducialDo(BOOL bIsFicial)
{
	#ifdef USELOG
	if(m_bIsFiducialDo!=bIsFicial)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_bIsFiducialDo);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,bIsFicial);//"后:%d"

		GetLog().Append_pro(AfterStr,20135,BeforeStr);//"回零状态变化"
	}
#endif	
	m_bIsFiducialDo = bIsFicial;
}

void SystemDoc::SetIsFiducialDo2(BOOL bIsFicial,int direction)
{	
	m_bIsFiducialDo2[direction] = bIsFicial;
}

void SystemDoc::SetSecondReverse(BOOL isSecondReverse)
{
	this->m_isSecondReverse=isSecondReverse;
}

BOOL SystemDoc::GetSecondReverse()
{
	return	m_isSecondReverse;
}

BOOL SystemDoc::GetIsFiducialDo2(int direction) const
{	
	return m_bIsFiducialDo2[direction];
}

long SystemDoc::GetToolsCnt() const
{
	return m_tmToolsPara.size();
}

LayerToolPara SystemDoc::GetToolPara(int iToolNo,int iLayer) const
{
	ASSERT (iToolNo<m_tmToolsPara.size());
	return m_tmToolsPara[iToolNo].GetLayerToolPara(iLayer);
}

void SystemDoc::SetToolFileName(const CString &str)
{
	m_strToolFileName = str;
}

CString SystemDoc::GetToolFileName() const
{
	return m_strToolFileName;
}
void SystemDoc::SetFileName(const CString &str)
{
	m_strFileName = str;
}

CString SystemDoc::GetFileName() const
{
	return m_strFileName;
}
/*
void SystemDoc::AddUserTool(const int &iToolNo, const int &iDiameter, const int &iAperture)
{
	m_tmToolsPara.push_back(UserToolPara(iToolNo,iDiameter,iAperture));
}
*/
void SystemDoc::AddUserTool(const int &iToolNo, const int &iDiameter, const int &iAperture,const int &iSubAperture)
{
	m_tmToolsPara.push_back(UserToolPara(iToolNo,iDiameter,iAperture,iSubAperture));
}

long SystemDoc::GetToolNo(int nTpIndex)
{
    ASSERT(nTpIndex<m_tmToolsPara.size());
	return m_tmToolsPara[nTpIndex].GetToolNo();
}
//////////////////////////////////////////////////////////
long SystemDoc::GetToolDiameter(int nIndex)			//20160809
{
    ASSERT(nIndex<m_tmToolsPara.size());
	return m_tmToolsPara[nIndex].GetDiameter();
}
//////////////////////////////////////////////////////////
void SystemDoc::AddLayerToolPara(const int &iTool, const int &iLayer, const int &iDrillModel, const int &iOffset)
{
	ASSERT(iTool<m_tmToolsPara.size()&&iTool>=0);
	ASSERT(iLayer<m_tmToolsPara[iTool].GetLayerNum()+1&&iLayer>=0);

	m_tmToolsPara[iTool].InsertLayerToolPara(iLayer,LayerToolPara(iDrillModel,iOffset));
}

void SystemDoc::AddEnergyPara(const int &iTool, const int &iLayer, const int &iEnergyNo, const int &iModel, const int &iRelease, const int &iPeriod)
{
	ASSERT(iTool<m_tmToolsPara.size()&&iTool>=0);
	ASSERT(iLayer<m_tmToolsPara[iTool].GetLayerNum()&&iLayer>=0);
	ASSERT(iEnergyNo>=0&& iEnergyNo<iModel?m_tmToolsPara[iTool][iLayer].GetCycleNum()+1:m_tmToolsPara[iTool][iLayer].GetBurstNum()+1);

	if(iModel==0)
		m_tmToolsPara[iTool][iLayer].InsertBstEnergy(iEnergyNo,Energy(iPeriod,iRelease));
	else
		m_tmToolsPara[iTool][iLayer].InsertCycEnergy(iEnergyNo,Energy(iPeriod,iRelease));
	
}

void SystemDoc::ClearTools()
{
	if(!m_tmToolsPara.empty())
	{
		for(int i=0; i<m_tmToolsPara.size(); ++i)
		{
			if(!m_tmToolsPara[i].m_subToolPara.empty())
			{
				for(int j=0;j<m_tmToolsPara[i].m_subToolPara.size();++j)
				{
					m_tmToolsPara[i].m_subToolPara[j].m_pEBEnergy.clear();
					m_tmToolsPara[i].m_subToolPara[j].m_pECEnergy.clear();
				}				
			}
			m_tmToolsPara[i].m_subToolPara.clear();
		}
	}

	m_tmToolsPara.clear();

//	m_tmToolsPara.clear();
//	m_tmToolsParaSet.clear();
}

void SystemDoc::SetProcJumpDelay(UINT lJumpDelay)
{
#ifdef USELOG
	if(m_lProcJumpDelay!=lJumpDelay)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lProcJumpDelay);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lJumpDelay);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lProcJumpDelay);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lJumpDelay);//"后:%d"
		GetLog().Append_pro(AfterStr,20136,BeforeStr);//"加工时震镜跳转延时变化"
	}
#endif	
	m_lProcJumpDelay = lJumpDelay;
}

UINT SystemDoc::GetProcJumpDelay() const
{
	return m_lProcJumpDelay;
}

void SystemDoc::SetProcJumpDelay0(UINT lJumpDelay)//ly add 20111123
{
#ifdef USELOG
	if(m_lProcJumpDelay0!=lJumpDelay)
	{
		char ez[256]={""};
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lProcJumpDelay0);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lJumpDelay);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lProcJumpDelay);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lJumpDelay);//"后:%d"
		GetLog().Append_pro(AfterStr,20136,BeforeStr);//"加工时震镜跳转延时变化"
	}
#endif	
	m_lProcJumpDelay0 = lJumpDelay;
}

UINT SystemDoc::GetProcJumpDelay0() const //ly add 20111123
{
	return m_lProcJumpDelay0;
}

void SystemDoc::SetProcJumpLenth(UINT lJumpLenth)//ly add 20111123
{
#ifdef USELOG
	if(m_lProcJumpLenth!=lJumpLenth)
	{
		char ez[256]={""};
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lProcJumpLenth);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lJumpLenth);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lProcJumpDelay);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lJumpDelay);//"后:%d"
		GetLog().Append_pro(AfterStr,20136,BeforeStr);//"加工时震镜跳转延时变化"
	}
#endif	
	m_lProcJumpLenth = lJumpLenth;
}

long SystemDoc::GetRTC5AddBasicDelay() const //ly add 20111123
{
	return m_iRTC5AddBasicDelay;
}

long SystemDoc::GetRTC5TestBasicDelay() const //ly add 20111123
{
	return m_iRTC5TestBasicDelay;
}

UINT SystemDoc::GetProcJumpLenth() const //ly add 20111123
{
	return m_lProcJumpLenth;
}

int SystemDoc::GetFirstJumpDelay() const //ly add 20111123
{
	return m_lProcFirstJumpDelay;
}

UINT SystemDoc::GetFirstDelayPeriod() const //ly add 20111123 Gap->Period jpc change 20120419
{
	if(m_lProcFirstDelayGap>500)				//20161216 增加															//20161219 增加加工效率约束
		return 500;

	return m_lProcFirstDelayGap;
}

int SystemDoc::GetOtherJumpDelay() const //ly add 20120811
{
	return m_lProcOtherJumpDelay;
}

UINT SystemDoc::GetOtherDelayPeriod() const //ly add 20120811
{
	if(m_lProcOtherDelayGap>250)				//20161216 增加															//20161219 增加加工效率约束
		return 250;

	return m_lProcOtherDelayGap;
}

int SystemDoc::GetDelayJump() const //ly add 20130315
{
	return m_lProcDelayJump;
}

int SystemDoc::GetNULLMark() const //ly add 20120206
{
	return m_lNULLMark;
}

int SystemDoc::GetAOMLaserOnDelay() const//jpc add 20130815
{
	return m_AOMLaserOnDelay;
}

int SystemDoc::GetAOMLaserOffDelay() const
{
	return m_AOMLaserOffDelay;
}

int SystemDoc::GetTestMode() const //ly add 20120206
{
	return m_lTestMode;
}

void SystemDoc::SetMaxDutycycle(double duty)//ly add 20111209
{
	m_lMaxDutycycle = duty;
}

double SystemDoc::GetMaxDutycycle()//ly add 20111209
{
	return m_lMaxDutycycle;
}

void SystemDoc::SetProcJumpSpeed(UINT lJumpSpeed)
{
#ifdef USELOG
	if(m_lProcJumpSpeed!=lJumpSpeed)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lProcJumpSpeed);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lJumpSpeed);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lProcJumpSpeed);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lJumpSpeed);//"后:%d"
		GetLog().Append_pro(AfterStr,20137,BeforeStr);//"加工时震镜跳转速度变化"
	}
#endif	
	m_lProcJumpSpeed = lJumpSpeed;
}

UINT SystemDoc::GetProcJumpSpeed() const
{
	return m_lProcJumpSpeed;
}

Coord SystemDoc::GetLaserTestCleanRefPos() const
{
	return m_crdLaserTestCleanRef;
}

void SystemDoc::SetLaserTestCleanRefPos(const Coord &crd)
{
#ifdef USELOG
	if(m_crdLaserTestCleanRef!=crd)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdLaserTestCleanRef.x,m_crdLaserTestCleanRef.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,crd.x,crd.y);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21094),m_crdLaserTestCleanRef.x,m_crdLaserTestCleanRef.y);//"前:%d %d"
		//AfterStr.Format(GetLang().GetWarningText(21095),crd.x,crd.y);//"后:%d %d"
		GetLog().Append_pro(AfterStr,20138,BeforeStr);//"激光测量及清理位置变化"
	}
#endif
	m_crdLaserTestCleanRef = crd;
}

CString SystemDoc::GetAppPath() const
{
	return m_strAppPath;
}

void SystemDoc::ClearFiducailRealPos(int nHead)
{
	ASSERT(nHead==0||nHead==1||nHead==2);
	if(nHead==0){
		m_FiducialRealPosL.clear();
//		GetInfo().SaveToFile("FidNum.txt","L Empty\n");

	}
	else if(nHead==1)
	{
		m_FiducialRealPosR.clear();
//		GetInfo().SaveToFile("FidNum.txt","R Empty\n");
	}
	else
	{
		m_FiducialRealPosR.clear();
		m_FiducialRealPosL.clear();
//		GetInfo().SaveToFile("FidNum.txt","L Empty\n");
//		GetInfo().SaveToFile("FidNum.txt","R Empty\n");

	}
}

long SystemDoc::GetFiducialPosNum(int nHead) const
{
	ASSERT(nHead==0||nHead==1);
	if(nHead==0){
		return m_FiducialRealPosL.size();}
	else if(nHead==1)
	{
		return m_FiducialRealPosR.size();
	}
	else
	{
		return -1;
	}
}


void SystemDoc::AddFiducialPos(const Coord &crd, int nHead)
{
	ASSERT(nHead==0||nHead==1);
//	char buf[64];
	if(nHead==0){
		m_FiducialRealPosL.push_back(HoleData(crd));

//		sprintf(buf,"L No.%d X: %6d,Y: %6d \n",m_FiducialRealPosL.size(),crd.x,crd.y);
	}
	else if(nHead==1){
		m_FiducialRealPosR.push_back(HoleData(crd));
//		sprintf(buf,"R No.%d X: %6d,Y: %6d \n",m_FiducialRealPosR.size(),crd.x,crd.y);
	}
//	GetInfo().SaveToFile("FidNum.txt",buf);
}

//ly add 20110608
void SystemDoc::SetFiducialPos(const Coord &crd,int n, int nHead)
{
	ASSERT(nHead==0||nHead==1);
	ASSERT(n>=0&&n<4);
	//	char buf[64];
	if(nHead==0){
		m_FiducialRealPosL[n].x = crd.x;
		m_FiducialRealPosL[n].y = crd.y;		
	}
	else if(nHead==1){
		m_FiducialRealPosR[n].x = crd.x;
		m_FiducialRealPosR[n].y = crd.y;
	}
}

Coord SystemDoc::GetFiducialPos(int nIndex, int nHead)
{
	ASSERT(nHead==0||nHead==1);
	char ez[256]={""};//ly 20110404
	if(nHead==0)
	{
		if(nIndex<m_FiducialRealPosL.size())
		{
			return m_FiducialRealPosL[nIndex];
		}
		else
		{
			strncpy(ez,GetLang().GetWarningText(13016),256);
			AfxMessageBox(ez);//"读取靶标位置时左侧PCB板靶标索引号出错！"
#ifdef USELOG
			CString tempstr;
			strncpy(ez,GetLang().GetWarningText(21096),256);
			tempstr.Format(ez,nIndex);//"索引号为%d"
			GetLog().Append_pro(10103,"GetFiducialPos",tempstr);//"读取靶标位置时左侧PCB板靶标索引号出错！"
#endif
			return Coord();
		}
	}
	else if(nHead==1)
	{
		if(nIndex<m_FiducialRealPosR.size())
		{
			return m_FiducialRealPosR[nIndex];
		}
		else
		{
			strncpy(ez,GetLang().GetWarningText(13017),256);
			AfxMessageBox(ez);//"读取靶标位置时右侧PCB板靶标索引号出错！"
			#ifdef USELOG
			CString tempstr;
			strncpy(ez,GetLang().GetWarningText(21096),256);
			tempstr.Format(ez,nIndex);//"索引号为%d"
			GetLog().Append_pro(10104,"GetFiducialPos",tempstr);//"读取靶标位置时右侧PCB板靶标索引号出错！"
#endif

			return Coord();
		}
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(31034),256);
		AfxMessageBox(ez);//"工作头号出错！"
#ifdef USELOG
		CString tempstr;
		strncpy(ez,GetLang().GetWarningText(21097),256);
		tempstr.Format(ez,nHead);//"引进头号是%d"
		GetLog().Append_pro(10105,"GetFiducialPos",tempstr);//"工作头号出错！"
#endif
		return Coord();
	}
}

HoleCoordV SystemDoc::GetFiducial(int nHead)
{
	ASSERT(nHead==0||nHead==1);
	
	if(nHead==0)
	{
		return m_FiducialRealPosL;
	}
	else if(nHead==1)
	{
		return m_FiducialRealPosR;
	}
}

//两个CCD的间隔
Coord SystemDoc::GetCCDDistance()const
{
	return m_crdCCDDistance;
}

void SystemDoc::SetCCDDistance(const Coord &crd)
{
#ifdef USELOG
	if(m_crdCCDDistance!=crd)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21094),256);
		BeforeStr.Format(ez,m_crdCCDDistance.x,m_crdCCDDistance.y);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21095),256);
		AfterStr.Format(ez,crd.x,crd.y);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21094),m_crdCCDDistance.x,m_crdCCDDistance.y);//"前:%d %d"
	//	AfterStr.Format(GetLang().GetWarningText(21095),crd.x,crd.y);//"后:%d %d"
		GetLog().Append_pro(AfterStr,20139,BeforeStr);//"两CCD间的距离改变"
	}
#endif
    m_crdCCDDistance = crd;

//设定振镜之间的相对位置
	if(!GetDoc().GetTechnicType())
	{
		m_crdGlvDistance = crd + m_triSCCDToGlvSysOffsetLT - m_triSCCDToGlvSysOffsetRT;
	}
	else
	{
		m_crdGlvDistance = crd + m_triLCCDToGlvSysOffsetLT - m_triLCCDToGlvSysOffsetRT;
	}
}

Coord SystemDoc::GetGlvDistance() const
{
	return m_crdGlvDistance;
}	

Coord SystemDoc::GetProcGlvOffset() const
{
	return m_crdProcGlvOffset;
}

void SystemDoc::SetProcGlvOffset(const Coord &crd)
{
	m_crdProcGlvOffset = crd;
}

CString SystemDoc::GetCorPathName(int nHead) const
{	
	ASSERT(nHead==0||nHead==1);

#ifdef RTC5DLL		//RTC5
	if(nHead ==0)
	{
		if(GetDoc().GetTechnicType())
			return m_strAppPath+LPATHADJDIR+"CorL.ct5\0";
		else
			return m_strAppPath+SPATHADJDIR+"CorL.ct5\0";		
	}
	else
	{
		if(GetDoc().GetTechnicType())
			return m_strAppPath+LPATHADJDIR+"corR.ct5\0";
		else
			return m_strAppPath+SPATHADJDIR+"corR.ct5\0";		
	}
#else
#ifdef SMCCaliDLL
	if(nHead ==0)
	{
		if(GetDoc().GetTechnicType())
			return m_strAppPath+LPATHADJDIR+"CorL.xml\0";
		else
			return m_strAppPath+SPATHADJDIR+"CorL.xml\0";		
	}
	else
	{
		if(GetDoc().GetTechnicType())
			return m_strAppPath+LPATHADJDIR+"CorR.xml\0";
		else
			return m_strAppPath+SPATHADJDIR+"CorR.xml\0";		
	}
#else
	if(nHead ==0)
	{
		if(GetDoc().GetTechnicType())
			return m_strAppPath+LPATHADJDIR+"corL.ctb\0";
		else
			return m_strAppPath+SPATHADJDIR+"corL.ctb\0";		
	}
	else
	{
		if(GetDoc().GetTechnicType())
			return m_strAppPath+LPATHADJDIR+"corR.ctb\0";
		else
			return m_strAppPath+SPATHADJDIR+"corR.ctb\0";		
	}
#endif
#endif
}


long SystemDoc::GetSLBitPerMM() const
{
	return m_ulSLBitPermm;
}

void SystemDoc::SetSLBitPerMM(long ulBit)
{
	m_ulSLBitPermm = ulBit;
}
//设置亮度到内存变量
//lLum 亮度 lChan 左右通道  lType 同轴OR环形 Select 设置种类

void SystemDoc::SetCCDLightness(long lLum, long lChan,long lType ,UINT Select)
{
	ASSERT(lLum>=0||lLum<=255);
	ASSERT(lChan==0||lChan==1);
	ASSERT(lType==0||lType==1);
	ASSERT(Select==0||Select==1||Select==2||Select==3||Select==4||Select==5);
////////////外层标靶	
	if(Select == 0)
	{
		
		if(lChan==0)
		{
			if(lType == 0)
			{
				m_lCCDLumLC_OUT = lLum;
			}
			else
			{
				m_lCCDLumLR_OUT = lLum;
			}
			
		}
		else
		{
			if(lType == 0)
			{
				m_lCCDLumRC_OUT = lLum;
			}
			else
			{
				m_lCCDLumRR_OUT = lLum;
			}
		}
		
	}

//////////////////内层标靶

		if(Select == 1)
	{
		
		if(lChan==0)
		{
			if(lType == 0)
			{
				m_lCCDLumLC_INS = lLum;
			}
			else
			{
				m_lCCDLumLR_INS = lLum;
			}
			
		}
		else
		{
			if(lType == 0)
			{
				m_lCCDLumRC_INS = lLum;
			}
			else
			{
				m_lCCDLumRR_INS = lLum;
			}
		}
		
	}


////////////////////点阵校正

	if(Select ==2)
	{
		
		if(lChan==0)
		{
			if(lType == 0)
			{
				m_lCCDLumLC_GLV = lLum;
			}
			else
			{
				m_lCCDLumLR_GLV = lLum;
			}
			
		}
		else
		{
			if(lType == 0)
			{
				m_lCCDLumRC_GLV = lLum;
			}
			else
			{
				m_lCCDLumRR_GLV = lLum;
			}
		}
		
	}
	

////////////////////原点校正

	if(Select ==3)
	{
		
		if(lChan==0)
		{
			if(lType == 0)
			{
				m_lCCDLumLC_EME = lLum;
			}
			else
			{
				m_lCCDLumLR_EME = lLum;
			}
			
		}
		else
		{
			if(lType == 0)
			{
				m_lCCDLumRC_EME = lLum;
			}
			else
			{
				m_lCCDLumRR_EME = lLum;
			}
		}
		
	}
	
////////////////////CCD校正

	if(Select ==4)
	{
		
		if(lChan==0)
		{
			if(lType == 0)
			{
				m_lCCDLumLC_CCD = lLum;
			}
			else
			{
				m_lCCDLumLR_CCD = lLum;
			}
			
		}
		else
		{
			if(lType == 0)
			{
				m_lCCDLumRC_CCD = lLum;
			}
			else
			{
				m_lCCDLumRR_CCD = lLum;
			}
		}
		
	}
	
////////////////////内部标靶

	if(Select ==5)
	{
		
		if(lChan==0)
		{
			if(lType == 0)
			{
				m_lCCDLumLC_LM = lLum;
			}
			else
			{
				m_lCCDLumLR_LM = lLum;
			}
			
		}
		else
		{
			if(lType == 0)
			{
				m_lCCDLumRC_LM = lLum;
			}
			else
			{
				m_lCCDLumRR_LM = lLum;
			}
		}
		
	}
}

long SystemDoc::GetCCDLightness(long lChan,long lType,UINT select) const
{
	ASSERT(lChan==0||lChan==1);
	ASSERT(lType==0||lType==1);
	ASSERT(select==0||select==1||select == 2||select == 3||select==4||select==5);
	
//取得外层标靶亮度
	if(select == 0)
	{
		if(lChan==0)
		{
			if(lType == 0)
			{
				return m_lCCDLumLC_OUT;
			}
			else
			{
				return m_lCCDLumLR_OUT;
			}			
		}
		else
		{
			if(lType == 0)
			{
				return m_lCCDLumRC_OUT;
			}
			else
			{
				return m_lCCDLumRR_OUT;
			}			
		}		
	}
	
//取得内层标靶亮度	
	if(select == 1)
	{
		if(lChan==0)
		{
			if(lType == 0)
			{
				return m_lCCDLumLC_INS;
			}
			else
			{
				return m_lCCDLumLR_INS;
			}			
		}
		else
		{
			if(lType == 0)
			{
				return m_lCCDLumRC_INS;
			}
			else
			{
				return m_lCCDLumRR_INS;
			}			
		}		
	}

//取得点阵校正亮度	
	if(select == 2)
	{
		if(lChan==0)
		{
			if(lType == 0)
			{
				return m_lCCDLumLC_GLV;
			}
			else
			{
				return m_lCCDLumLR_GLV;
			}			
		}
		else
		{
			if(lType == 0)
			{
				return m_lCCDLumRC_GLV;
			}
			else
			{
				return m_lCCDLumRR_GLV;
			}			
		}		
	}

//取得原点校正亮度
	if(select == 3)
	{
		if(lChan==0)
		{
			if(lType == 0)
			{
				return m_lCCDLumLC_EME;
			}
			else
			{
				return m_lCCDLumLR_EME;
			}			
		}
		else
		{
			if(lType == 0)
			{
				return m_lCCDLumRC_EME;
			}
			else
			{
				return m_lCCDLumRR_EME;
			}			
		}	
	}

//取得CCD校正亮度
	if(select == 4)
	{
		if(lChan==0)
		{
			if(lType == 0)
			{
				return m_lCCDLumLC_CCD;
			}
			else
			{
				return m_lCCDLumLR_CCD;
			}			
		}
		else
		{
			if(lType == 0)
			{
				return m_lCCDLumRC_CCD;
			}
			else
			{
				return m_lCCDLumRR_CCD;
			}			
		}	
	}
	
//取得内部标靶亮度
	if(select == 5)
	{
		if(lChan==0)
		{
			if(lType == 0)
			{
				return m_lCCDLumLC_LM;
			}
			else
			{
				return m_lCCDLumLR_LM;
			}			
		}
		else
		{
			if(lType == 0)
			{
				return m_lCCDLumRC_LM;
			}
			else
			{
				return m_lCCDLumRR_LM;
			}			
		}	
	}

	return 0;
}

void SystemDoc::SetCCDInfrared(long lLum, long lChan,UINT Select)
{//设置红外线参数  lChan通道左右 Select类型 外标靶，内标靶，校正。。。。。
	ASSERT(lLum>=0||lLum<=255);
	ASSERT(lChan==0||lChan==1);
	ASSERT(Select==0||Select==1||Select==2||Select==3||Select==4||Select==5);	
	m_infraredSetVakue[Select][lChan]=lLum;
}

long SystemDoc::GetCCDInfrared(long lChan,UINT select) const
{//提取红外线参数  lChan通道左右 Select类型 外标靶，内标靶，校正。。。。。
	ASSERT(lChan==0||lChan==1);
	ASSERT(select==0||select==1||select == 2||select == 3||select==4||select==5);
	
	return m_infraredSetVakue[select][lChan];
}

double SystemDoc::GetAxisXErrVaule(long nPos)const
{
	//加判断 nPos有效性
#ifdef USEMOTION  
	ASSERT(m_AxisXPosErr.PositionErr.size()>0);
	double Err1,Err2;

//	double dbIndex = (nPos-m_AxisXPosErr.PositionErr[0].nPos)/(1.0*m_AxisXPosErr.nInterval);
	long dbIndex = (nPos-m_AxisXPosErr.PositionErr[0].nPos)/m_AxisXPosErr.nInterval;     
	
	if(nPos>=this->GetAxisXErrRange())
	{
	   return m_AxisXPosErr.PositionErr[m_AxisXPosErr.PositionErr.size()-1].dbErr;
	}
	else if(nPos<=-this->GetAxisXErrRange())
	{
	   return m_AxisXPosErr.PositionErr[0].dbErr;
	}
	else
	{
	
		long nIndex1 = dbIndex;
		long nIndex2 = nIndex1+1;
        if (nIndex2>=m_AxisXPosErr.PositionErr.size())
		{
		    Err2 = m_AxisXPosErr.PositionErr[m_AxisXPosErr.PositionErr.size()-1].dbErr;
		}
        else 
		{
		    Err2 = m_AxisXPosErr.PositionErr[nIndex2].dbErr;		
		}

		if (nIndex1 <0)
		{
		    Err1 = m_AxisXPosErr.PositionErr[0].dbErr;
		}
		else
		{
		    Err1 = m_AxisXPosErr.PositionErr[nIndex1].dbErr;
		}

		long nPos1 = m_AxisXPosErr.PositionErr[nIndex1].nPos;

		return (Err2-Err1)/m_AxisXPosErr.nInterval*(nPos-nPos1)+Err1;
	}
#else
	return 0;
#endif
}

double SystemDoc::GetAxisYErrVaule(long nPos) const
{
	//加判断 nPos有效性
#ifdef USEMOTION
	ASSERT(m_AxisYPosErr.PositionErr.size()>0);
	double Err1,Err2;
	
//	double dbIndex = (nPos-m_AxisYPosErr.PositionErr[0].nPos)/(m_AxisYPosErr.nInterval*1.0);
	long dbIndex = (nPos-m_AxisYPosErr.PositionErr[0].nPos)/m_AxisYPosErr.nInterval;

	if(nPos>=this->GetAxisYErrRange())
	{
	   return m_AxisYPosErr.PositionErr[m_AxisYPosErr.PositionErr.size()-1].dbErr;
	}
	else if(nPos<=-this->GetAxisYErrRange())
	{
	   return m_AxisYPosErr.PositionErr[0].dbErr;
	}
	else
	{
		long nIndex1 = dbIndex;
		long nIndex2 = nIndex1+1;
        if (nIndex2>=m_AxisYPosErr.PositionErr.size())
		{
		    Err2 = m_AxisYPosErr.PositionErr[m_AxisYPosErr.PositionErr.size()-1].dbErr;
		}
        else 
		{
		    Err2 = m_AxisYPosErr.PositionErr[nIndex2].dbErr;		
		}

		if (nIndex1 <0)
		{
		    Err1 = m_AxisYPosErr.PositionErr[0].dbErr;
		}
		else
		{
		    Err1 = m_AxisYPosErr.PositionErr[nIndex1].dbErr;
		}
/*
		if (nIndex2>=21)
		{
		    AfxMessageBox("nIndex2 out Range!");
#ifdef USELOG
			CString tempstr;
			tempstr.Format("nIndex2:%d",nIndex2);
			GetLog().Append_pro("nIndex2出错！","GetFiducialPos",tempstr);
#endif		 
		}
*/
		Err1 = m_AxisYPosErr.PositionErr[nIndex1].dbErr;
		Err2 = m_AxisYPosErr.PositionErr[nIndex2].dbErr;

		long nPos1 = m_AxisYPosErr.PositionErr[nIndex1].nPos;
		return (Err2-Err1)/m_AxisYPosErr.nInterval*(nPos-nPos1)+Err1;
	}
#else
	return 0;
#endif
}

double SystemDoc::GetAxisXErr(UINT ulIndex) const
{
//#ifdef USEMOTION													//20181106
    ASSERT(ulIndex<m_AxisXPosErr.PositionErr.size());
	return m_AxisXPosErr.PositionErr[ulIndex].dbErr;
//#else
//	return 0;
//#endif
}

double SystemDoc::GetAxisYErr(UINT ulIndex) const
{
//#ifdef USEMOTION													//20181106 
	ASSERT(ulIndex<m_AxisYPosErr.PositionErr.size());
	return m_AxisYPosErr.PositionErr[ulIndex].dbErr;
//#else
//	return  0;
//#endif
}

void SystemDoc::SetAxisXErr(UINT ulIndex,double dbErr)
{
#ifdef USEMOTION 
	ASSERT(ulIndex<m_AxisYPosErr.PositionErr.size());
    m_AxisXPosErr.PositionErr[ulIndex].dbErr = dbErr;  
#endif
}

void SystemDoc::SetAxisYErr(UINT ulIndex,double dbErr)
{
#ifdef USEMOTION
	ASSERT(ulIndex<m_AxisYPosErr.PositionErr.size());
    m_AxisYPosErr.PositionErr[ulIndex].dbErr = dbErr;  
#endif
}


void SystemDoc::SetAxisXErr(UINT ulIndex, const PosErr &poserr)
{
#ifdef USEMOTION
   ASSERT(ulIndex>=0);
   ASSERT(ulIndex<m_AxisXPosErr.PositionErr.size());

//  考虑当 ulIndex>m_AxisXPosErr.PositionErr.size() 的处理！
   if(ulIndex<m_AxisXPosErr.PositionErr.size())
      m_AxisXPosErr.PositionErr[ulIndex] = poserr;  
#endif  
}

void SystemDoc::SetAxisYErr(UINT ulIndex, const PosErr &poserr)
{
#ifdef USEMOTION 
   ASSERT(ulIndex>=0);
   ASSERT(ulIndex<m_AxisYPosErr.PositionErr.size());

//  考虑当 ulIndex>m_AxisYPosErr.PositionErr.size() 的处理！
	if(ulIndex<m_AxisYPosErr.PositionErr.size())
      m_AxisYPosErr.PositionErr[ulIndex] = poserr;  
#endif
}

long SystemDoc::GetAxisXErrRange(void)const  //
{
	return m_AxisXPosErr.MaxRange;

}

long SystemDoc::GetAxisYErrnInterval(void)const  //
{
	return m_AxisYPosErr.nInterval;

}

long SystemDoc::GetAxisXErrnInterval(void)const  //
{
	return m_AxisXPosErr.nInterval;

}

long SystemDoc::GetAxisXErrCounter(void)const //
{
	return m_AxisXPosErr.nCounters;

}

long SystemDoc::GetAxisYErrRange(void)const  //
{
	return m_AxisYPosErr.MaxRange;

}

long SystemDoc::GetAxisYErrCounter(void)const //
{
	return m_AxisYPosErr.nCounters;

}

long SystemDoc::GetAxisXErrStart(void)const//ly add 20110310
{
	return m_AxisXPosErr.nStart;
}

long SystemDoc::GetAxisXErrEnd(void)const//ly add 20110310
{
	return m_AxisXPosErr.nEnd;
}

long SystemDoc::GetAxisYErrStart(void)const//ly add 20110310
{
	return m_AxisYPosErr.nStart;
}

long SystemDoc::GetAxisYErrEnd(void)const//ly add 20110310
{
	return m_AxisYPosErr.nEnd;
}

void SystemDoc::SetUnloadTransPos(CRD pos)
{

	#ifdef USELOG
		if(m_UnloadTransPos!=pos)
		{
			char ez[256]={""};//ly
			strncpy(ez,GetLang().GetWarningText(21092),256);
			BeforeStr.Format(ez,m_UnloadTransPos);//"前:%d"
			strncpy(ez,GetLang().GetWarningText(21093),256);
			AfterStr.Format(ez,pos);//"后:%d"

		//	BeforeStr.Format(GetLang().GetWarningText(21092),m_UnloadTransPos);//"前:%d"
		//	AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
			GetLog().Append_pro(AfterStr,20140,BeforeStr);//"下料转接位置改变"
		}
#endif
    m_UnloadTransPos = pos;
}

void SystemDoc::SetLoadTransPos(CRD pos)
{
#ifdef USELOG
	if(m_LoadTransPos!=pos)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_LoadTransPos);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,pos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_LoadTransPos);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),pos);//"后:%d "
		GetLog().Append_pro(AfterStr,20141,BeforeStr);//"上料转接位置改变"
	}
#endif
    m_LoadTransPos = pos;
}

CRD SystemDoc::GetLoadTransPos() const
{
    return m_LoadTransPos;
}
CRD SystemDoc::GetLoadTunePos() const
{
    return m_LoadTunePos;
}
CRD SystemDoc::GetUnLoadTunePos() const
{
    return m_UnLoadTunePos;
}

CRD SystemDoc::GetUnloadTransPos() const
{
   return m_UnloadTransPos;
}

void SystemDoc::SetBETBenchmark(long lPos)
{
	
#ifdef USELOG
	if(m_lBETOffsetCrd!=lPos)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lBETOffsetCrd);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lBETOffsetCrd);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lPos);//"后:%d "
		GetLog().Append_pro(AfterStr,20142,BeforeStr);//"BET零点偏置改变"
	}
#endif
	m_lBETOffsetCrd =lPos;      // BET零点偏置
}

long SystemDoc::GetBETBenchmark() const
{
     return m_lBETOffsetCrd;
}

void SystemDoc::SetAptBenchmark(long lPos)
{
#ifdef USELOG
	if(m_lAptOffsetCrd!=lPos)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAptOffsetCrd);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPos);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lAptOffsetCrd);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lPos);//"后:%d "
		GetLog().Append_pro(AfterStr,20143,BeforeStr);//"光圈偏置改变"
	}
#endif
	m_lAptOffsetCrd = lPos;
}

long SystemDoc::GetAptBenchmark() const
{
    return m_lAptOffsetCrd;
}

void SystemDoc::SetAptBenchmark2(long lPos)
{
#ifdef USELOG
	if(m_lAptOffsetCrd2!=lPos)
	{
		char ez[256]={""};
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAptOffsetCrd2);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPos);//"后:%d"
		GetLog().Append_pro(AfterStr,20143,BeforeStr);//"光圈偏置改变"
	}
#endif
	m_lAptOffsetCrd2 = lPos;
}
long SystemDoc::GetAptBenchmark2() const
{
    return this->m_lAptOffsetCrd2;
}
void SystemDoc::SetBETSubOffset2(long lPos)
{	
#ifdef USELOG
	if(m_lBETSubOffsetCrd2!=lPos)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lBETSubOffsetCrd2);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPos);//"后:%d"
		GetLog().Append_pro(AfterStr,20142,BeforeStr);//"BET零点偏置改变"
	}
#endif
	m_lBETSubOffsetCrd2 =lPos;      // BET零点偏置
}
long SystemDoc::GetBETSubOffset2() const
{
	return this->m_lBETSubOffsetCrd2;
}
void SystemDoc::SetBETPriOffset2(long offset)
{
	m_lBETPriOffset2=offset;
}
long SystemDoc::GetBETPriOffset2()
{
	return this->m_lBETPriOffset2;
}

void SystemDoc::SetBETOffset(int nApt, long nOffset)//ly mark 20120117
{
    ASSERT(nApt>=0||nApt<APTNUM);

	m_lBETOffset[nApt] = nOffset;
}

void SystemDoc::SetFactualAperture(int nApt, long nOffset)
{
    ASSERT(nApt>=0||nApt<APTNUM);

	m_lFactualAperture[nApt] = nOffset;
}

long SystemDoc::GetBETOffset(int nApt) const
{
   ASSERT(nApt>=0||nApt<APTNUM);

   return m_lBETOffset[nApt];
}

long SystemDoc::GetFactualAperture(int nApt) const
{
   ASSERT(nApt>=1||nApt<=APTNUM);

   return m_lFactualAperture[nApt-1];
}

//DOUBLEBET 20150911
void SystemDoc::SetFactualAperture2(int nApt, long nOffset)
{
    ASSERT(nApt>=0||nApt<APTNUM);

	m_lFactualAperture2[nApt] = nOffset;
}

long SystemDoc::GetFactualAperture2(int nApt) const
{
	ASSERT(nApt>=1||nApt<=APTNUM);

	return m_lFactualAperture2[nApt-1];
}

long SystemDoc::GetBETOffset2(int nApt) const
{
	ASSERT(nApt>=0||nApt<APTNUM);

	return m_lBETOffset2[nApt];
}

void SystemDoc::SetBETOffset2(int nApt, long nOffset)
{
    ASSERT(nApt>=0||nApt<APTNUM);

	m_lBETOffset2[nApt] = nOffset;
}

CString SystemDoc::GetCurUserName() const
{
    return m_CurUserInfo.strUserName;
}

CString SystemDoc::GetCurUserDepartment() const
{
	return m_CurUserInfo.dept_id;
}
CString SystemDoc::GetCurUserShift()const
{
	return m_CurUserInfo.shift_id;	
}

long SystemDoc::GetCurUserLevel() const
{
    return m_CurUserInfo.nLevel;
}

void SystemDoc::SetCurUserLevel(long lLevel)
{
    m_CurUserInfo.nLevel = lLevel;
}

void SystemDoc::SetCurUserName(const CString &strName)
{
    m_CurUserInfo.strUserName = strName;
}

void SystemDoc::SetCurUserDepartment(const CString& dept)
{
	m_CurUserInfo.dept_id = dept;	
}

void SystemDoc::SetCurUserShift(const CString& shift)
{
	m_CurUserInfo.shift_id = shift;
}

void SystemDoc::AddUserInfo(const UserInfo &ulv)
{
    m_UserInfo.push_back(ulv);
}

long SystemDoc::GetLoginUserNum()
{
    return m_UserInfo.size();
}

UserInfo SystemDoc::GetLoginUserInfo(int nIndex) const
{
    ASSERT(nIndex<m_UserInfo.size());

	return m_UserInfo[nIndex];
}

BOOL SystemDoc::LoadUserInfo()
{    
	CRegistry reg;
 //   HKEY hKEY;
	CString KeyName="Software\\LaserSystem";
    CString str,strpath;
	LPCTSTR lp="Software\\LaserSystem";


	char  Name[32];
	char  Password[32];
    DWORD    value;

    m_UserInfo.clear();

	if(reg.Open(HKEY_LOCAL_MACHINE,KeyName))
	{
        int j= reg.GetSubKeyNum();

		for(int n=0;n< j/*reg.GetSubKeyNum()*/;++n)
		{
            reg.Open(HKEY_LOCAL_MACHINE,KeyName);
			str = reg.GetSubKeyName(n);
            strpath = KeyName+"\\"+str;

		    reg.Open(HKEY_LOCAL_MACHINE,strpath);
			reg.ReadString("Name",Name,256);
			reg.ReadString("PW",Password,256);
			reg.ReadDWORD("Level",&value);

			GetDoc().AddUserInfo(UserInfo(value,Name,Password));
		}
	}
    else
	{
	   reg.CreateKey(HKEY_LOCAL_MACHINE,lp,"2123");
	}
	return TRUE;
}

BOOL SystemDoc::SaveUserInfo()
{
    CRegistry reg;
	CString KeyName="Software\\LaserSystem";
    CString str,strpath;

	unsigned long n;
    if(reg.Open(HKEY_LOCAL_MACHINE,KeyName))
	{
        int nreg = reg.GetSubKeyNum();
		for( n=0;n<nreg;++n)
		{
//            reg.Open(HKEY_LOCAL_MACHINE,KeyName);
			str.Format("%d",n);
            
            strpath = KeyName+"\\"+str;

		    reg.DeleteKey(HKEY_LOCAL_MACHINE,strpath);		
		}
	}
    reg.Close();
	if(reg.CreateKey(HKEY_LOCAL_MACHINE,KeyName,NULL))
	{
		for( n=0;n<GetDoc().GetLoginUserNum();++n)
		{
            reg.Open(HKEY_LOCAL_MACHINE,KeyName);
			str.Format("%d",n);
            
            strpath = KeyName+"\\"+str;

		    reg.CreateKey(HKEY_LOCAL_MACHINE,strpath,NULL);
			reg.Open(HKEY_LOCAL_MACHINE,strpath);
			reg.WriteString("Name",const_cast<char*>((LPCTSTR)GetDoc().GetLoginUserInfo(n).strUserName));
			reg.WriteString("PW",  const_cast<char*>((LPCTSTR)GetDoc().GetLoginUserInfo(n).strPassword));
			reg.WriteDWORD ("Level",GetDoc().GetLoginUserInfo(n).nLevel);

		}
	}
    else
	{
	   reg.CreateKey(HKEY_LOCAL_MACHINE,KeyName,"2123");
	}
    return TRUE;
}

void SystemDoc::DeleteUserInfo(int nIndex)
{
    m_UserInfo.erase(m_UserInfo.begin()+nIndex);
}

void SystemDoc::DeleteUserInfoByName(CString userName)
{
	std::vector<UserInfo>::iterator it = m_UserInfo.begin();
	while (it != m_UserInfo.end())
	{
		if (it->strUserName == userName)
			m_UserInfo.erase(++it);
		else
			++it;
	}
}

void SystemDoc::SetUserPassword(int nIndex,const CString& str)
{
    ASSERT(nIndex<m_UserInfo.size());
	m_UserInfo[nIndex].strPassword = str;
}

void SystemDoc::AddFiducialOffset(const Coord &crd)
{
	m_FiducialOffset.push_back(HoleData(crd));
}

void SystemDoc::ClearFiducialOffsetData()
{
    m_FiducialOffset.clear();
}

Coord SystemDoc::GetFiducialOffset(int nIndex) const
{
    ASSERT(nIndex<m_FiducialOffset.size());
	return m_FiducialOffset[nIndex];
}

void SystemDoc::SetProcMode(enum PROCMODE pm)
{
     m_ProcMode = pm;
}

SystemDoc::PROCMODE SystemDoc::GetProcMode() const
{
     return m_ProcMode;
}

long SystemDoc::GetToolApertureNo(int nToolIndex) const
{
    ASSERT(nToolIndex<m_tmToolsPara.size());
//	return m_tmToolsPara[nToolIndex].GetApertureNo();      //2009 12 24 liq
//	return m_tmToolsPara[GetDoc().GetFactualAperture(nToolIndex)].GetApertureNo();      //2009 12 24 liq

	if(m_tmToolsPara[nToolIndex].GetApertureNo()>0)
	{
		return m_tmToolsPara[nToolIndex].GetApertureNo();
//		return GetDoc().GetFactualAperture(m_tmToolsPara[nToolIndex].GetApertureNo());      //2009 12 24 liq
	}
	else
		return 0;
}
/*
long SystemDoc::GetToolShowApertureNo(int nToolIndex) const      //2009 12 24 liq
{
    ASSERT(nToolIndex<m_tmToolsPara.size());
	return m_tmToolsPara[nToolIndex].GetApertureNo();
}
*/
long SystemDoc::GetToolSubApertureNo(int nToolIndex) const
{
    ASSERT(nToolIndex<m_tmToolsPara.size());
//	return m_tmToolsPara[nToolIndex].GetSubApertureNo();     //2009 12 24 liq
//	return m_tmToolsPara[GetDoc().GetFactualAperture(nToolIndex)].GetSubApertureNo();     //2009 12 24 liq

	if(m_tmToolsPara[nToolIndex].GetSubApertureNo()>0)
	{
		return m_tmToolsPara[nToolIndex].GetSubApertureNo();
//		return GetDoc().GetFactualAperture(m_tmToolsPara[nToolIndex].GetSubApertureNo());     //2009 12 24 liq
	}
	else
		return 0;
}
/*
long SystemDoc::GetToolSubShowApertureNo(int nToolIndex) const		//2009 12 24 liq
{
    ASSERT(nToolIndex<m_tmToolsPara.size());
	return m_tmToolsPara[nToolIndex].GetSubApertureNo();
}
*/
long SystemDoc::GetDrlRegJumpSpeed() const
{
    return m_lDrlRegJumpSpeed;
}

void SystemDoc::SetDrlRegJumpSpeed(long lSpeed)
{
#ifdef USELOG
	if(m_lDrlRegJumpSpeed!=lSpeed)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegJumpSpeed);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lSpeed);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegJumpSpeed);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lSpeed);//"后:%d "
		GetLog().Append_pro(AfterStr,20144,BeforeStr);//"开标靶跳转速度改变"
	}
#endif
    m_lDrlRegJumpSpeed = 4000;//ly change 20111208 lSpeed;
}

void SystemDoc::SetDrlRegJumpDelay(long lDelay)
{
#ifdef USELOG
	if(m_lDrlRegJumpDelay!=lDelay)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegJumpDelay);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lDelay);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegJumpDelay);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lDelay);//"后:%d "
		GetLog().Append_pro(AfterStr,20145,BeforeStr);//"开标靶跳转延时改变"
	}
#endif
	m_lDrlRegJumpDelay = 1000;//ly change 20111208 lDelay;
}

long SystemDoc::GetDrlRegJumpDelay() const
{
     return m_lDrlRegJumpDelay;
}

void SystemDoc::SetDrlRegPulseRelease(long lRelease)
{
    ASSERT(lRelease<=LASERMAXWIDTH);
	
#ifdef USELOG
	if(m_lDrlRegPlsRelease!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPlsRelease);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPlsRelease);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20146,BeforeStr);//"开标靶脉冲宽度改变"
	}
#endif
	m_lDrlRegPlsRelease = lRelease;
}

void SystemDoc::SetDrlRegPulse2Release(long lRelease)
{
    ASSERT(lRelease<=LASERMAXWIDTH);
	
#ifdef USELOG
	if(m_lDrlRegPls2Release!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPls2Release);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPls2Release);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20146,BeforeStr);//"开标靶脉冲宽度改变"
	}
#endif
	m_lDrlRegPls2Release = lRelease;
}


void SystemDoc::SetDrlRegPulse3Release(long lRelease)
{
    ASSERT(lRelease<=LASERMAXWIDTH);
	
#ifdef USELOG
	if(m_lDrlRegPls3Release!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPls2Release);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPls2Release);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20146,BeforeStr);//"开标靶脉冲宽度改变"
	}
#endif
	m_lDrlRegPls3Release = lRelease;
}
void SystemDoc::SetDrlRegPulse4Release(long lRelease)
{
    ASSERT(lRelease<=LASERMAXWIDTH);
	
#ifdef USELOG
	if(m_lDrlRegPls4Release!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPls2Release);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPls2Release);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20146,BeforeStr);//"开标靶脉冲宽度改变"
	}
#endif
	m_lDrlRegPls4Release = lRelease;
}

void SystemDoc::SetDrlRegPulse5Release(long lRelease)
{
    ASSERT(lRelease<=LASERMAXWIDTH);
	
#ifdef USELOG
	if(m_lDrlRegPls5Release!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPls2Release);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPls2Release);//"前:%d"
	//AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20146,BeforeStr);//"开标靶脉冲宽度改变"
	}
#endif
	m_lDrlRegPls5Release = lRelease;
}

void SystemDoc::SetDrlRegionPointDis(long lDis)
{
/*	
	if (lDis<80||lDis>120)								//20160919
	{
		//AfxMessageBox("点距设置错误，设置默认值100um");
        lDis=100;			
	}
*/
	m_lDrlRegPointDis=lDis;
}

long SystemDoc::GetDrlRegionPointDis()
{
	return m_lDrlRegPointDis;
}

long SystemDoc::GetDrlRegPulseTimes() const//ly add 20121030
{
    return m_lDrlRegPlsTimes;
}

void SystemDoc::SetDrlRegPulseTimes(long Times) //ly add 20121030
{
    m_lDrlRegPlsTimes = Times;
}

long SystemDoc::GetDrlRegPulseRelease() const
{
    return m_lDrlRegPlsRelease;
}

long SystemDoc::GetDrlRegPulse2Release() const
{
    return m_lDrlRegPls2Release;
}
long SystemDoc::GetDrlRegPulse3Release() const
{
    return m_lDrlRegPls3Release;
}
long SystemDoc::GetDrlRegPulse4Release() const
{
    return m_lDrlRegPls4Release;
}
long SystemDoc::GetDrlRegPulse5Release() const
{
    return m_lDrlRegPls5Release;
}

BOOL SystemDoc::GetIsDrillRegion() const
{
    return m_isDrillRegion;
}
void SystemDoc::SetIsDrillRegion(BOOL isDrillRegion) 
{
    this->m_isDrillRegion=isDrillRegion;
}

void SystemDoc::SetDrlRegPulsePeriod(long lPeriod)
{
#ifdef USELOG
	if(m_lDrlRegPlsPeriod!=lPeriod)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPlsPeriod);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPeriod);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPlsPeriod);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lPeriod);//"后:%d "
		GetLog().Append_pro(AfterStr,20147,BeforeStr);//"开标靶脉冲周期改变"
	}
#endif
    m_lDrlRegPlsPeriod = 1000;//ly change 20111208 lPeriod;  
}


long SystemDoc::GetDrlRegPulsePeriod() const
{
    return m_lDrlRegPlsPeriod;
}

void SystemDoc::SetDrlRegAperture(long lAptNo)
{
#ifdef USELOG
	if(m_lDrlRegApertureNo!=lAptNo)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegApertureNo);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lAptNo);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegApertureNo);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lAptNo);//"后:%d "
		GetLog().Append_pro(AfterStr,20148,BeforeStr);//"开标靶光圈改变"
	}
#endif
    m_lDrlRegApertureNo = lAptNo;
}

long SystemDoc::GetDrlRegAperture() const
{
    return m_lDrlRegApertureNo ;   //2009 12 24 
//	return GetDoc().GetFactualAperture(m_lDrlRegApertureNo);		//2009 12 23 liq	
}
/*
long SystemDoc::GetDrlRegShowAperture() const
{
    return m_lDrlRegApertureNo ;
}
*/
long SystemDoc::GetDrlRegPlsNum() const
{
    return m_lDrlRegPulseNum;
}

void SystemDoc::SetDrlRegPlsNum(long lNum)
{
#ifdef USELOG
	if(m_lDrlRegPulseNum!=lNum)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlRegPulseNum);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lNum);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlRegPulseNum);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lNum);//"后:%d "
		GetLog().Append_pro(AfterStr,20149,BeforeStr);//"开标靶脉冲数字改变"
	}
#endif
     m_lDrlRegPulseNum = lNum;
}

///////////yutingxun 7-5  06
long SystemDoc::GetDrlTxtJumpSpeed() const
{
    return m_lDrlTxtJumpSpeed;
}

void SystemDoc::SetDrlTxtJumpSpeed(long lSpeed)
{
#ifdef USELOG
	if(m_lDrlTxtJumpSpeed!=lSpeed)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlTxtJumpSpeed);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lSpeed);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlTxtJumpSpeed);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lSpeed);//"后:%d "
		GetLog().Append_pro(AfterStr,20150,BeforeStr);//"钻字符跳转速度改变"
	}
#endif
    m_lDrlTxtJumpSpeed = 4000;//ly change 20111208 lSpeed;
}

void SystemDoc::SetDrlTxtJumpDelay(long lDelay)
{
#ifdef USELOG
	if(m_lDrlTxtJumpDelay!=lDelay)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlTxtJumpDelay);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lDelay);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlTxtJumpDelay);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lDelay);//"后:%d "
		GetLog().Append_pro(AfterStr,20150,BeforeStr);//"钻字符跳转速度改变"
	}
#endif
	m_lDrlTxtJumpDelay = 1000;//ly change 20111208 lDelay;
}

long SystemDoc::GetDrlTxtJumpDelay() const
{
     return m_lDrlTxtJumpDelay;
}

void SystemDoc::SetDrlTxtPulseRelease(long lRelease)
{
    ASSERT(lRelease<=LASERMAXWIDTH);
	
#ifdef USELOG
	if(m_lDrlTxtPlsRelease!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlTxtPlsRelease);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlTxtPlsRelease);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20151,BeforeStr);//"钻字符脉冲宽度改变"
	}
#endif
	m_lDrlTxtPlsRelease = lRelease;
}


long SystemDoc::GetDrlTxtPulseRelease() const
{
    return m_lDrlTxtPlsRelease;
}


void SystemDoc::SetDrlTxtPulsePeriod(long lPeriod)
{
    m_lDrlTxtPlsPeriod = 1000;//ly change 20111208 lPeriod;  
}


long SystemDoc::GetDrlTxtPulsePeriod() const
{
    return m_lDrlTxtPlsPeriod;
}

void SystemDoc::SetDrlTxtAperture(long lAptNo)
{
	#ifdef USELOG
	if(m_lDrlTxtApertureNo!=lAptNo)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlTxtApertureNo);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lAptNo);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlTxtApertureNo);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lAptNo);//"后:%d "
		GetLog().Append_pro(AfterStr,20152,BeforeStr);//"钻字符光圈改变"
	}
#endif
    m_lDrlTxtApertureNo = lAptNo;
}

long SystemDoc::GetDrlTxtAperture() const
{
    return m_lDrlTxtApertureNo ;		//2009 12 24 liq
//	return GetDoc().GetFactualAperture(m_lDrlTxtApertureNo);		//2009 12 23 liq
}
/*
long SystemDoc::GetDrlTxtShowAperture() const		//2009 12 24 liq
{
    return m_lDrlTxtApertureNo ;
}
*/
long SystemDoc::GetDrlTxtPlsNum() const
{
    return m_lDrlTxtPulseNum;
}

void SystemDoc::SetDrlTxtPlsNum(long lNum)
{
#ifdef USELOG
	if(m_lDrlTxtPulseNum!=lNum)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lDrlTxtPulseNum);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lNum);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lDrlTxtPulseNum);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lNum);//"后:%d "
		GetLog().Append_pro(AfterStr,20153,BeforeStr);//"钻字符脉冲数改变"
	}
#endif
	m_lDrlTxtPulseNum = lNum;
}
////////////////////////////


void SystemDoc::SetAdjustPulsePeriod(long lPeriod)
{
#ifdef USELOG
	if(m_lAdjustPlsPeriod!=lPeriod)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAdjustPlsPeriod);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lPeriod);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lAdjustPlsPeriod);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lPeriod);//"后:%d "
		GetLog().Append_pro(AfterStr,20154,BeforeStr);//"校正脉冲周期改变"
	}
#endif
	m_lAdjustPlsPeriod  = 1000;//ly change 20111208 lPeriod;   //

}

long SystemDoc::GetAdjustPulsePeriod() const
{
	return  m_lAdjustPlsPeriod;   //

}

void SystemDoc::SetAdjustPulseRelease(long lRelease)
{
	ASSERT(lRelease<=LASERMAXWIDTH);
	#ifdef USELOG
	if(m_lAdjustPlsRelease!=lRelease)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAdjustPlsRelease);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lRelease);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lAdjustPlsRelease);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lRelease);//"后:%d "
		GetLog().Append_pro(AfterStr,20155,BeforeStr);//"校正脉冲时间改变"
	}
#endif
	m_lAdjustPlsRelease =  lRelease;  //
}

long SystemDoc::GetAdjustPulseRelease() const
{
    return m_lAdjustPlsRelease;
}
long SystemDoc::GetAdjustJumpSpeed() const
{
    return m_lAdjustJumpSpeed;
}

void SystemDoc::SetAdjustJumpSpeed(long lJmpSpeed)
{
    ASSERT(lJmpSpeed>=0||lJmpSpeed<=7000);
#ifdef USELOG
	if(m_lAdjustJumpSpeed!=lJmpSpeed)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAdjustJumpSpeed);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lJmpSpeed);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lAdjustJumpSpeed);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lJmpSpeed);//"后:%d "
		GetLog().Append_pro(AfterStr,20156,BeforeStr);//"校正震镜跳转速度改变"
	}
#endif
	m_lAdjustJumpSpeed = 4000;//ly change 20111208 lJmpSpeed;
}
///yutingxun 校正光圈的设置
void SystemDoc::SetAdjustAperture(long lAptNo)
{
	#ifdef USELOG
	if(m_lAdjustApertureNo!=lAptNo)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAdjustApertureNo);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lAptNo);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lAdjustApertureNo);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),lAptNo);//"后:%d "
		GetLog().Append_pro(AfterStr,20157,BeforeStr);//"校正光圈改变"
	}
#endif
    m_lAdjustApertureNo = lAptNo;
}
void SystemDoc::SetLongPathAdjustAperture(long lAptNo)
{
  	#ifdef USELOG
	if(m_lLongPathAdjustApertureNo!=lAptNo)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lLongPathAdjustApertureNo);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lAptNo);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_lLongPathAdjustApertureNo);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),lAptNo);//"后:%d "
		GetLog().Append_pro(AfterStr,20158,BeforeStr);//"长路径校正光圈改变"
	}
#endif
    m_lLongPathAdjustApertureNo = lAptNo;
}
long SystemDoc::GetAdjustAperture() const
{
    return m_lAdjustApertureNo ;
//  return GetDoc().GetFactualAperture(m_lAdjustApertureNo);  //2009 12 24 liq
}
/*
long SystemDoc::GetAdjustShowAperture() const		//20009 12 24  liq 
{
    return m_lAdjustApertureNo ;
}
*/
long SystemDoc::GetLongPathAdjustAperture() const
{
    return m_lLongPathAdjustApertureNo;
//	return GetDoc().GetFactualAperture(m_lLongPathAdjustApertureNo);		//2009 12 23 liq
}
/*
long SystemDoc::GetLongPathAdjustShowAperture() const		//2009 12 24 liq
{
    return m_lLongPathAdjustApertureNo;
}
*/
void SystemDoc::SetCCDProcThreshold(long dbThreshold)
{
#ifdef USELOG
	if(m_lCCDProcThreshold!=dbThreshold)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lCCDProcThreshold);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,dbThreshold);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lCCDProcThreshold);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),dbThreshold);//"后:%d "
		GetLog().Append_pro(AfterStr,20159,BeforeStr);//"CCD主标靶阈值改变"
	}
#endif
	m_lCCDProcThreshold = dbThreshold;
}

void SystemDoc::SetCCDProcInnerThreshold(long dbThreshold)
{
#ifdef USELOG
	if(m_lCCDProcInnerThreshold!=dbThreshold)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lCCDProcInnerThreshold);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,dbThreshold);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_lCCDProcInnerThreshold);//"前:%d"
		//AfterStr.Format(GetLang().GetWarningText(21093),dbThreshold);//"后:%d "
		GetLog().Append_pro(AfterStr,20160,BeforeStr);//"CCD内部标靶阈值改变"
	}
#endif
	m_lCCDProcInnerThreshold = dbThreshold;
}


long SystemDoc::GetCCDProcThreshold() const
{
    return m_lCCDProcThreshold;
}

long SystemDoc::GetCCDProcInnerThreshold() const
{
    return m_lCCDProcInnerThreshold;
}

long SystemDoc::GetCCDProcInnerRange() const//ly add 20121009
{
    return m_lCCDProcInnerRange;
}

long SystemDoc::GetTableDelay() const//ly add 20121013
{
    return m_lTableDelay;
}

void SystemDoc::SetCCDAdjThreshold(long dbThreshold)
{
#ifdef USELOG
	if(m_lCCDAdjustThreshold!=dbThreshold)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lCCDAdjustThreshold);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,dbThreshold);//"后:%d"

		GetLog().Append_pro(AfterStr,20161,BeforeStr);//"CCD校正阈值改变"
	}
#endif
      m_lCCDAdjustThreshold = dbThreshold;
}

long SystemDoc::GetCCDAdjThreshold() const
{
     return m_lCCDAdjustThreshold;
}

void SystemDoc::SetAdjustJumpDelay(long lDelay)
{ 
    ASSERT(lDelay>=0);
#ifdef USELOG
	if(m_lAdjustJumpDelay!=lDelay)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_lAdjustJumpDelay);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,lDelay);//"后:%d"

		GetLog().Append_pro(AfterStr,20162,BeforeStr);//"校正跳转延时改变"
	}
#endif
	m_lAdjustJumpDelay = 1000;
}

void SystemDoc::SetGlvAdjPlsRelease(UINT ulRelease)
{ 
    ASSERT(ulRelease>=0);
	m_ulAdjPlslRelease = ulRelease;
}

void SystemDoc::SetGlvAdjPosX(long lPos)
{ 
  //  ASSERT(lPos>=0);
	m_lAdjPosX = lPos;
}

void SystemDoc::SetGlvAdjPosY(long lPos)
{ 
 //   ASSERT(lPos>=0);
	m_lAdjPosY = lPos;
}

long SystemDoc::GetGlvAdjPosY() const
{
	return m_lAdjPosY;
}

long SystemDoc::GetGlvAdjPosX() const
{
	return m_lAdjPosX;
}

long SystemDoc::GetGlvCaliOffsetTol()
{
	return m_lGlvCaliOffsetTol;
}

int SystemDoc::GetTestThicknessZSafePos()
{
	return m_lTestThicknessZSafePos;
}

int SystemDoc::GetTestThicknessCompensation(int nHead)
{
	ASSERT( nHead==HeadLeft||nHead==HeadRight);

	return m_lTestThicknessCompensation[nHead];
}

UINT SystemDoc::GetGlvAdjPlsRelease() const
{
   return m_ulAdjPlslRelease;
}

long SystemDoc::GetAdjustJumpDelay() const
{
   return m_lAdjustJumpDelay;
}

BOOL SystemDoc::GetFidicialMatchMode() const
{
   return m_bManuFindFidcial;
}

void SystemDoc::SetFidicialMatchMode(BOOL bMatchMode)
{
    m_bManuFindFidcial = bMatchMode;
}

long SystemDoc::GetCurPCBHoleCount() const
{
    return m_lPCBHoleCount;
}

void SystemDoc::SetCurPCBHoleCount(long lCount)
{
     m_lPCBHoleCount = lCount;
}

long SystemDoc::GetCurPCBDrilledHoleCount() const//ly add 20110903
{
    return m_lPCBDrilledHoleCount;
}

void SystemDoc::SetCurPCBDrilledHoleCount(long lCount)//ly add 20110903
{
     m_lPCBDrilledHoleCount = lCount;
}

double SystemDoc::GetHolesSum() const//ly add 20121230
{
    return m_lDrldHolesSum;
}

double SystemDoc::GetPowerScale() const
{
    return m_lPowerScale;
}

int SystemDoc::GetLoadPCBTime() const
{
    return m_lLoadPCBTime;
}
int SystemDoc::GetUnLoadPCBTime() const
{
    return m_lUnLoadPCBTime;
}

void SystemDoc::SetLoadPCBTime(int loadtime) 
{
   this->m_lLoadPCBTime=loadtime;
}
void SystemDoc::SetUnLoadPCBTime(int unloadtime) 
{
    this->m_lUnLoadPCBTime=unloadtime;
}

void SystemDoc::SetHolesSum(double lCount)//ly add 20121230
{
     m_lDrldHolesSum = lCount;
}

int SystemDoc::GetErrorPCB() const//ly add 20120116
{
    return m_lErrorPCB;
}

void SystemDoc::SetErrorPCB(int lCount)//ly add 20120116
{
     m_lErrorPCB = lCount;
}

long SystemDoc::GetCurPCBDrilledArea() const//ly add 20111008
{
    return m_lPCBCurArea;
}

void SystemDoc::SetCurPCBDrilledArea(long lCount)//ly add 20111008
{
     m_lPCBCurArea = lCount;
}

void SystemDoc::SetSaveLogFlag(int iFlag)
{
	m_SaveLogFlag = iFlag;
}

int SystemDoc::GetSaveLogFlag() const
{
    return m_SaveLogFlag;
}

void SystemDoc::SetAdjTime(UINT ulTime)
{
#ifdef USELOG
	if(m_ulAdjTime!=ulTime)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_ulAdjTime);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,ulTime);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_ulAdjTime);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),ulTime);//"后:%d "
		GetLog().Append_pro(AfterStr,20163,BeforeStr);//"振镜校正时间间隔"
	}
#endif
      m_ulAdjTime = ulTime;
}

void SystemDoc::SetLaserTestTime(long ulTime)
{
#ifdef USELOG
	if(m_ulLaserPowerTime!=ulTime)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_ulLaserPowerTime);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,ulTime);//"后:%d"

		//BeforeStr.Format(GetLang().GetWarningText(21092),m_ulLaserPowerTime);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),ulTime);//"后:%d "
		GetLog().Append_pro(AfterStr,20163,BeforeStr);//"振镜校正时间间隔"
	}
#endif
      m_ulLaserPowerTime = ulTime;
}

void SystemDoc::SetOperationRateTime(CString ulTime)
{
#ifdef USELOG
	if(m_OperationRateTime!=ulTime)
	{
		BeforeStr.Format("前:%s",m_OperationRateTime);
		AfterStr.Format("后:%d",ulTime);

		GetLog().Append_pro(AfterStr,20163,BeforeStr);//"振镜校正时间间隔"
	}
#endif
      m_OperationRateTime = ulTime;
}

void SystemDoc::SetOperationRateTimeNight(CString ulTime)
{
#ifdef USELOG
	if(m_OperationRateTimeNight!=ulTime)
	{
		BeforeStr.Format("前:%s",m_OperationRateTimeNight);
		AfterStr.Format("后:%d",ulTime);

		GetLog().Append_pro(AfterStr,20163,BeforeStr);//"振镜校正时间间隔"
	}
#endif
	//string nowtime = ToolUtil::time_t2string();
      m_OperationRateTimeNight = ulTime;
}

void SystemDoc::SetTechnicType(bool ultype)
{
#ifdef USELOG
	if(m_TechnicType!=ultype)
	{
		char ez[256]={""};//ly
		strncpy(ez,GetLang().GetWarningText(21092),256);
		BeforeStr.Format(ez,m_TechnicType);//"前:%d"
		strncpy(ez,GetLang().GetWarningText(21093),256);
		AfterStr.Format(ez,ultype);//"后:%d"

	//	BeforeStr.Format(GetLang().GetWarningText(21092),m_TechnicType);//"前:%d"
	//	AfterStr.Format(GetLang().GetWarningText(21093),ultype);//"后:%d "
		GetLog().Append_pro(AfterStr,20163,BeforeStr);//"振镜校正时间间隔"
	}
#endif
      m_TechnicType = ultype;
}

bool SystemDoc::GetTechnicType() const
{
	return m_TechnicType;
}
long SystemDoc::GetLaserTestTime() const
{
	return m_ulLaserPowerTime;
}

long SystemDoc::GetAdjTime() const
{
	return  m_ulAdjTime;
}

CString SystemDoc::GetOperationRateTime() const
{
	return  m_OperationRateTime;
}

CString SystemDoc::GetOperationRateTimeNight() const
{
	return  m_OperationRateTimeNight;
}

void SystemDoc::SetAdjustTime(time_t ltime)
{
    m_lDoAdjtimer = ltime;
}

void SystemDoc::SetLaserTestCurTime(time_t ltime)
{
	m_lLaserTestTimer = ltime;
}

time_t SystemDoc::GetAdjustTime() const
{
	return  m_lDoAdjtimer;
}

time_t SystemDoc::GetLaserTestCurTime() const
{
	return  m_lLaserTestTimer;
}

BOOL SystemDoc::GetIsRecordPowerPara() const
{
	return m_bIsRecordPowerPara;
}

void SystemDoc::SetIsRecordPowerPara(BOOL bEnable) 
{
	 m_bIsRecordPowerPara = bEnable;
}

long SystemDoc::GetToolSetCnt() const
{
	return m_tmToolsParaSet.size();
}

void SystemDoc::AddEnergyParaSet(const int &iTool, const int &iLayer,  const BOOL &bCheck, const int &iPeriod,const int &iRelease,const int &iDrillMode,const int &iApertureNo, const int &iScanNum, const int &iFocusOffset)
{
//	ASSERT(iTool<m_tmToolsParaSet.size()&&iTool>=0);
    m_tmToolsParaSet[iTool].InsertEnergyData(iLayer,
	ProcParaSet(bCheck,iPeriod,iRelease,iDrillMode,iApertureNo,iScanNum,iFocusOffset));
}

int SystemDoc::GetToolItemDrillMode(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_iDrillMode;
}

long SystemDoc::GetToolLayerCnt(int iToolNo) const
{
	return m_tmToolsParaSet[iToolNo].GetLayerNum();
}

int SystemDoc::GetToolLayerNo(int iToolNo) const
{
	return m_tmToolsParaSet[iToolNo].GetLayerToolNo();
}

bool SystemDoc::GetToolLayerCheck(int iToolNo) const
{
	return m_tmToolsParaSet[iToolNo].GetLayerToolCheck();
}

int SystemDoc::GetToolItemPeriod(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_iPeriod;
}

float SystemDoc::GetToolLayerDiameter(int iToolNo) const
{
	return m_tmToolsParaSet[iToolNo].GetLayerToolDiameter();
}

int SystemDoc::GetToolItemRelease(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_iRelease;
}

int SystemDoc::GetToolItemScanNum(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_iScanNum;
}

int SystemDoc::GetToolItemFocusOffset(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_iFocusOffset;
}

int SystemDoc::GetToolItemApertureNo(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_iApertureNo;
}

bool SystemDoc::GetToolItemCheck(int iToolNo,int iLayerNo)
{
	ASSERT((iToolNo>=0)||(iToolNo<=m_tmToolsParaSet.size()));
	ASSERT((iLayerNo>=0)||iLayerNo<=m_tmToolsParaSet[iToolNo].GetLayerNum());
	return	m_tmToolsParaSet[iToolNo].GetLayerProcParaSet(iLayerNo).m_bCheck;
}

void SystemDoc::AddUserToolSet(const BOOL &bCheck, const float &fDiameter, const int &iToolNo)
{
	m_tmToolsParaSet.push_back(LayerToolParaSet(bCheck,fDiameter,iToolNo));
//	int ii= m_tmToolsParaSet.size();
}

BOOL SystemDoc::WriteCaliTimes()
{
	CIniFile IniFile;
	CString str,path;
	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\calitimes");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		IniFile.WriteSection("PatternTimes");
		IniFile.WriteItemInt("Left",GetDoc().m_iPatternTimes[0]);
		IniFile.WriteItemInt("Right",GetDoc().m_iPatternTimes[1]);
		IniFile.WriteString("\n");
		IniFile.WriteSection("OrgTimes");
		IniFile.WriteItemInt("Left",GetDoc().m_iOrgTimes[0]);
		IniFile.WriteItemInt("Right",GetDoc().m_iOrgTimes[1]);
		IniFile.WriteString("\n");

		IniFile.WriteSection("AccuracyTimes");//jpc add 20130304------
		IniFile.WriteItemInt("LeftX",GetDoc().m_PatternXTimes[0]);
		IniFile.WriteItemInt("RightX",GetDoc().m_PatternXTimes[1]);
		IniFile.WriteItemInt("LeftY",GetDoc().m_PatternYTimes[0]);
		IniFile.WriteItemInt("RightY",GetDoc().m_PatternYTimes[1]);
		IniFile.WriteString("\n");

		IniFile.CloseIniFile();
	}

	return true;
}

BOOL SystemDoc::ReadCaliTimes()
{
	CIniFile IniFile;
	CString str,path;
	char ez[256]={""};

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\calitimes");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		if(!IniFile.GetItemInt("PatternTimes","Left", GetDoc().m_iPatternTimes[0]))
			return false;	
		if(!IniFile.GetItemInt("PatternTimes","Right", GetDoc().m_iPatternTimes[1]))
			return false;	
		if(!IniFile.GetItemInt("OrgTimes","Left", GetDoc().m_iOrgTimes[0]))
			return false;	
		if(!IniFile.GetItemInt("OrgTimes","Right", GetDoc().m_iOrgTimes[1]))
			return false;

		if(!IniFile.GetItemInt("AccuracyTimes","LeftX", GetDoc().m_PatternXTimes[0]))	//jpc add 20130304
		{
			GetDoc().m_PatternXTimes[0]=0;	
		}
		if(!IniFile.GetItemInt("AccuracyTimes","RightX", GetDoc().m_PatternXTimes[1]))
		{
			GetDoc().m_PatternXTimes[1]=0;	
		}
		if(!IniFile.GetItemInt("AccuracyTimes","LeftY", GetDoc().m_PatternYTimes[0]))
		{
			GetDoc().m_PatternYTimes[0]=0;	
		}	
		if(!IniFile.GetItemInt("AccuracyTimes","RightY", GetDoc().m_PatternYTimes[1]))
		{
			GetDoc().m_PatternYTimes[1]=0;	
		}

		IniFile.CloseIniFile();	
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(13018),256);
		AfxMessageBox(ez,MB_OK);//"无法导入振镜校正次数参数！"	
	}

	return true;
}
/*
BOOL  SystemDoc::CalculateCalibratePosOffset()
{//计算校正的位置，替代编译开关
	if(GetDoc().GetLargeTable()==0)
	{
		if(GetDoc().GetTableClamp())//ly change 20120523
		{
			totalWidthCalibrate=220000;                               //#define TOTALWIDTH		220000		//校正板整板使用宽度
		}
		else
		{
			totalWidthCalibrate=500000;                               //#define TOTALWIDTH		500000		//校正板整板使用宽度
		}
		
		long iUseCalibrate=GetDoc().GetSLBitPerMM();              //1425,1000,800

		if (iUseCalibrate<950)//jpc change 20131217
		{
			totalHeightCalibrate=80000;                            //TOTALHEIGHT 80000 //校正板整板使用高度
			matrixTimesCalibrate=4;                                //MATRIXTIMES 2 //点阵校正时单方向复用次数  
			patternLongWidthCalibrate=78375;//jpc add 20120429------------
			if (iUseCalibrate<750)
			{//695
				totalHeightCalibrate=91000;                            //TOTALHEIGHT 80000 //校正板整板使用高度
				matrixTimesCalibrate=5;                                //MATRIXTIMES 2 //点阵校正时单方向复用次数  
				patternLongWidthCalibrate=90216;//jpc add 20120429------------
			}
		}
		else if (iUseCalibrate>1050)
		{
			totalHeightCalibrate=45000;                            //TOTALHEIGHT			80000		//校正板整板使用高度
			matrixTimesCalibrate=2;                                //MATRIXTIMES			2		//点阵校正时单方向复用次数 
			patternLongWidthCalibrate=44000;//jpc add 20120429------------
		}
		else
		{
			totalHeightCalibrate=65000;                            //TOTALHEIGHT			80000		//校正板整板使用高度
			matrixTimesCalibrate=3;                                //MATRIXTIMES			2		//点阵校正时单方向复用次数  
			patternLongWidthCalibrate=62700;//jpc add 20120429------------
		}
		patternMatrixWidthCalibrate=patternLongWidthCalibrate/PATTERNDOTNUM/matrixTimesCalibrate;//#define	PATTERNMATRIXWIDTH	PATTERNLONGWIDTH / PATTERNDOTNUM / MATRIXTIMES	//点阵校正时复用位移值
		offsetLongWidthCalibrate=15000;                           //#define	OFFSETLONGWIDTH  15000		//原点校正时的扫描宽度(占用宽度）
		offsetHeightCalibrate=5000;                               //#define	OFFSETHEIGHT	 5000		//原点校正时的高度位移值
	}
	else if(GetDoc().GetLargeTable()==1)
	{
		totalHeightCalibrate=340000;                               //#define TOTALWIDTH		500000		//校正板整板使用宽度
		
		long iUseCalibrate=GetDoc().GetSLBitPerMM();              //1425,1000,800
		if (iUseCalibrate<950)//jpc change 20131217
		{
			totalWidthCalibrate=80000;                            //TOTALHEIGHT 80000 //校正板整板使用高度
			matrixTimesCalibrate=4;                                //MATRIXTIMES 2 //点阵校正时单方向复用次数  
			patternLongWidthCalibrate=78375;//jpc add 20120429------------
			if (iUseCalibrate<750)
			{//695
				totalWidthCalibrate=91000;                            //TOTALHEIGHT 80000 //校正板整板使用高度
				matrixTimesCalibrate=5;                                //MATRIXTIMES 2 //点阵校正时单方向复用次数  
				patternLongWidthCalibrate=90216;//jpc add 20120429------------
			}
		}
		else if (iUseCalibrate>1050)
		{
			totalWidthCalibrate=45000;                            //TOTALHEIGHT			80000		//校正板整板使用高度
			matrixTimesCalibrate=2;                                //MATRIXTIMES			2		//点阵校正时单方向复用次数 
			patternLongWidthCalibrate=44000;//jpc add 20120429------------
		}
		else
		{
			totalWidthCalibrate=65000;                            //TOTALHEIGHT			80000		//校正板整板使用高度
			matrixTimesCalibrate=3;                                //MATRIXTIMES			2		//点阵校正时单方向复用次数  
			patternLongWidthCalibrate=62700;//jpc add 20120429------------
		}
		patternMatrixWidthCalibrate=patternLongWidthCalibrate/PATTERNDOTNUM/matrixTimesCalibrate;//#define	PATTERNMATRIXWIDTH	PATTERNLONGWIDTH / PATTERNDOTNUM / MATRIXTIMES	//点阵校正时复用位移值
		offsetLongWidthCalibrate=15000;                           //#define	OFFSETLONGWIDTH  15000		//原点校正时的扫描宽度(占用宽度）
		offsetHeightCalibrate=5000;                               //#define	OFFSETHEIGHT	 5000		//原点校正时的高度位移值
	}
	return true;
}
*/
BOOL  SystemDoc::CalculateCalibratePosOffset()									//20190102 修改
{
	long matrixSizeInUm=GetDoc().GetDefineMatrixRange()*1000/GetDoc().GetSLBitPerMM();
	long intervalInUm=1600;

	matrixTimesCalibrate=matrixSizeInUm/(PATTERNDOTNUM-1)/intervalInUm;			//点阵校正时单方向复用次数
	intervalInUm=matrixSizeInUm/(PATTERNDOTNUM-1)/matrixTimesCalibrate;
	patternLongWidthCalibrate=matrixSizeInUm+matrixTimesCalibrate*intervalInUm;	//点阵校正位置复用时的占用宽度（或占用高度）um
	patternMatrixWidthCalibrate=intervalInUm;									//点阵校正时复用位移值 um
	
	offsetLongWidthCalibrate=15000;												//原点校正时的占用宽度 um
	offsetHeightCalibrate=5000;													//原点校正时的高度位移值 um

	if(GetDoc().GetLargeTable()==0)
	{
		if(GetDoc().GetTableClamp())
			totalWidthCalibrate=220000;											//校正板整板可使用的左右宽度 um
		else
			totalWidthCalibrate=500000;

		totalHeightCalibrate=patternLongWidthCalibrate;							//校正板整板可使用的前后宽度 um
	}
	else if(GetDoc().GetLargeTable()==1)
	{
		totalWidthCalibrate=patternLongWidthCalibrate;							//校正板整板可使用的左右宽度 um
		totalHeightCalibrate=340000;											//校正板整板可使用的前后宽度 um
	}

	return true;
}

BOOL SystemDoc::GetAutoCalibrateFieldPosOffset(Coord &ReturnPos, int nHead)
{//文件校正
	CalculateCalibratePosOffset();
	BOOL RetVal;
	
	int i,j;
	if(GetDoc().GetLargeTable()==0)
	{
		i = m_iPatternTimes[nHead] % (matrixTimesCalibrate*matrixTimesCalibrate);
		if(i != 0)
		{   //不需要分配新的水平位置	
			ReturnPos.x = m_iPatternTimes[nHead]/(matrixTimesCalibrate*matrixTimesCalibrate)*patternLongWidthCalibrate
				+(i%matrixTimesCalibrate)*patternMatrixWidthCalibrate+patternLongWidthCalibrate/2;
			ReturnPos.y = -(i/matrixTimesCalibrate)*patternMatrixWidthCalibrate-patternLongWidthCalibrate/2;
			m_iPatternTimes[nHead]++;
			RetVal = true;
		}
		else
		{   //需要分配新的水平位置
			j = totalWidthCalibrate- (m_iPatternTimes[nHead]/(matrixTimesCalibrate*matrixTimesCalibrate))*patternLongWidthCalibrate 
				- ((m_iOrgTimes[nHead]>1?m_iOrgTimes[nHead]-1:0)/(totalHeightCalibrate/offsetHeightCalibrate)
				+ ((m_iOrgTimes[nHead]>1?m_iOrgTimes[nHead]-1:0)%(totalHeightCalibrate/offsetHeightCalibrate)==0?0:1))*offsetLongWidthCalibrate;
			
			if(j < patternLongWidthCalibrate)
			{
				
				m_iPatternTimes[nHead] = 0;
				m_iOrgTimes[nHead] = 0;
				RetVal = false;
			}
			else
			{
				ReturnPos.x = m_iPatternTimes[nHead]/(matrixTimesCalibrate*matrixTimesCalibrate)*patternLongWidthCalibrate+patternLongWidthCalibrate/2;
				ReturnPos.y = -patternLongWidthCalibrate/2;
				m_iPatternTimes[nHead]++;
				RetVal = true;
			}
		}	
	}
	else if(GetDoc().GetLargeTable()==1)
	{
		i = m_iPatternTimes[nHead] % (matrixTimesCalibrate*matrixTimesCalibrate);
		if(i != 0)
		{   //不需要分配新的水平位置	
			ReturnPos.y = totalHeightCalibrate-m_iPatternTimes[nHead]/(matrixTimesCalibrate*matrixTimesCalibrate)*patternLongWidthCalibrate
				-(i%matrixTimesCalibrate)*patternMatrixWidthCalibrate-patternLongWidthCalibrate/2;
			ReturnPos.x = -(i/matrixTimesCalibrate)*patternMatrixWidthCalibrate+patternLongWidthCalibrate/2;
			m_iPatternTimes[nHead]++;
			RetVal = true;
		}
		else
		{   //需要分配新的水平位置
			j = totalHeightCalibrate- (m_iPatternTimes[nHead]/(matrixTimesCalibrate*matrixTimesCalibrate))*patternLongWidthCalibrate 
				- ((m_iOrgTimes[nHead]>1?m_iOrgTimes[nHead]-1:0)/(totalWidthCalibrate/offsetLongWidthCalibrate)
				+ ((m_iOrgTimes[nHead]>1?m_iOrgTimes[nHead]-1:0)%(totalWidthCalibrate/offsetLongWidthCalibrate)==0?0:1))*offsetHeightCalibrate;
			
			if(j < patternLongWidthCalibrate)
			{
				m_iPatternTimes[nHead] = 0;
				m_iOrgTimes[nHead] = 0;
				RetVal = false;
			}
			else
			{
				ReturnPos.y = totalHeightCalibrate-m_iPatternTimes[nHead]/(matrixTimesCalibrate*matrixTimesCalibrate)*patternLongWidthCalibrate-patternLongWidthCalibrate/2;
				ReturnPos.x = patternLongWidthCalibrate/2;
				m_iPatternTimes[nHead]++;
				RetVal = true;
			}
		}	
	}
	
	
	return RetVal;
}

BOOL SystemDoc::GetAutoCalibrateOrgPosOffset(Coord &ReturnPos, int nHead)
{//原点校正
	BOOL RetVal;	
	int i,j;

	CalculateCalibratePosOffset();

	if(GetDoc().GetLargeTable()==0)
	{
		i = m_iOrgTimes[nHead] % (totalHeightCalibrate/offsetHeightCalibrate);
		if(i != 0)
		{  //不需要分配新的水平位置
			
			ReturnPos.x = totalWidthCalibrate-(m_iOrgTimes[nHead]/(totalHeightCalibrate/offsetHeightCalibrate)+1)*offsetLongWidthCalibrate;
			ReturnPos.y = -i*offsetHeightCalibrate;
			m_iOrgTimes[nHead]++;
			RetVal = true;
		}
		else
		{ //需要分配新的水平位置			
			j = totalWidthCalibrate - ((m_iPatternTimes[nHead]>1?m_iPatternTimes[nHead]-1:0)/(matrixTimesCalibrate*matrixTimesCalibrate)+1)*patternLongWidthCalibrate
				- (m_iOrgTimes[nHead]/(totalHeightCalibrate/offsetHeightCalibrate) + (m_iOrgTimes[nHead]%(totalHeightCalibrate/offsetHeightCalibrate)==0?0:1))*offsetLongWidthCalibrate;
			if(j < offsetLongWidthCalibrate)
			{
				m_iPatternTimes[nHead] = 0;
				m_iOrgTimes[nHead] = 0;
				RetVal = false;
			}
			else
			{
				ReturnPos.x = totalWidthCalibrate-(m_iOrgTimes[nHead]/(totalHeightCalibrate/offsetHeightCalibrate)+1)*offsetLongWidthCalibrate;;
				ReturnPos.y = 0;
				m_iOrgTimes[nHead]++;
				RetVal = true;
			}
		}
	}
	else if(GetDoc().GetLargeTable()==1)
	{
		i = m_iOrgTimes[nHead] % (totalWidthCalibrate/offsetLongWidthCalibrate);
		if(i != 0)
		{  //不需要分配新的水平位置
			ReturnPos.y = (m_iOrgTimes[nHead]/(totalWidthCalibrate/offsetLongWidthCalibrate)+1)*offsetHeightCalibrate;
			ReturnPos.x = i*offsetLongWidthCalibrate ;
			m_iOrgTimes[nHead]++;
			RetVal = true;
		}
		else
		{ //需要分配新的水平位置
			j = totalHeightCalibrate - ((m_iPatternTimes[nHead]>1?m_iPatternTimes[nHead]-1:0)/(matrixTimesCalibrate*matrixTimesCalibrate)+1)*patternLongWidthCalibrate
				- (m_iOrgTimes[nHead]/(totalWidthCalibrate/offsetLongWidthCalibrate) + (m_iOrgTimes[nHead]%(totalWidthCalibrate/offsetLongWidthCalibrate)==0?0:1))*offsetHeightCalibrate;
			if(j < offsetHeightCalibrate)
			{
				m_iPatternTimes[nHead] = 0;
				m_iOrgTimes[nHead] = 0;
				RetVal = false;
			}
			else
			{
				ReturnPos.y = (m_iOrgTimes[nHead]/(totalWidthCalibrate/offsetLongWidthCalibrate)+1)*offsetHeightCalibrate;
				ReturnPos.x = 0;
				m_iOrgTimes[nHead]++;
				RetVal = true;
			}
		}
	}

	return RetVal;
}
/*
int accuracyTestType
0 ---校正
1 ---测试11*11点
2 ---测试3*3个点
*/   //jpc add 20130304
BOOL SystemDoc::GetAutoCalibrateFieldPosOffsetForAccuracyTest(long SLBitPerMM,Coord &ReturnPos, int nHead,int accuracyTestType)
{//精度校正与测试
	if(GetDoc().GetLargeTable()==1)
	{
		long totalWidth=80000;//校正板整板使用宽度
		long totalHeight=340000;
		long matrixTimesX=3;//x
		long matrixTimesY=15;//y
		long patternLongWidth=85500;
		long patternLongWidthMove=62700;
		long patternMatrixWidth=1900;
		long offsetLongWidth=15000;                    
		long offsetHeight=5000;

		if (SLBitPerMM<950)//800//jpc change 20131217
		{
			totalWidth=80000;
			matrixTimesX=4;
			matrixTimesY=20;//ly mark 20140324
			patternLongWidth=106875;
			patternLongWidthMove=78375;
			patternMatrixWidth=1781;
			if (SLBitPerMM<750)
			{//695
				totalWidth=91000;
				matrixTimesX=5;
				matrixTimesY=25;
				patternLongWidth=135324;
				patternLongWidthMove=90216;
				patternMatrixWidth=1640;
			}
		}
		if (SLBitPerMM>1050)
		{//暂时
			totalWidth=45000;
			matrixTimesX=2;
			matrixTimesY=10;
			patternLongWidth=60000;
			patternLongWidthMove=44000;
			patternMatrixWidth=2250;
		}
		
		BOOL RetVal;	
		int i=0,j=0;	
		i = m_PatternXTimes[nHead] % matrixTimesX;
		if((i==0) && (m_PatternYTimes[nHead]==0))
		{  //需要分配新的水平位置
			j = totalHeight-(m_PatternXTimes[nHead]/matrixTimesX*patternLongWidth);
			if(j < patternLongWidth)
			{		
				m_PatternXTimes[nHead] = 0;
				m_PatternYTimes[nHead] = 0;
				RetVal = false;
			}
			else
			{
				ReturnPos.y =totalHeight-(m_PatternXTimes[nHead]/matrixTimesX*patternLongWidth)-patternLongWidthMove/2;
				ReturnPos.x =patternLongWidthMove/2;
				m_PatternYTimes[nHead]++;
				RetVal = true;
			}
		}
		else
		{ //不需要分配新的水平位置		
			ReturnPos.y = totalHeight-(m_PatternXTimes[nHead]/matrixTimesX*patternLongWidth)-m_PatternYTimes[nHead]*patternMatrixWidth-patternLongWidthMove/2;	
			ReturnPos.x = (m_PatternXTimes[nHead]%matrixTimesX)*patternMatrixWidth+patternLongWidthMove/2;
			m_PatternYTimes[nHead]++;
			if (m_PatternYTimes[nHead]==matrixTimesY)
			{
				m_PatternYTimes[nHead]=0;
				m_PatternXTimes[nHead]++;
			}
			RetVal = true;
		}	
		return RetVal;
	}
	long totalWidth=500000;//校正板整板使用宽度
	long totalHeight=65000;
	long matrixTimesX=15;//x
	long matrixTimesY=3;//y
	long patternLongWidth=85500;
	long patternLongWidthMove=62700;
	long patternMatrixWidth=1900;
	long offsetLongWidth=15000;                    
	long offsetHeight=5000;
	if(GetDoc().GetTableClamp())
	{
		totalWidth=220000;
	}
	/*if (SLBitPerMM<950)//800
	{
		totalHeight=80000;
		matrixTimesX=20;
		matrixTimesY=4;
		patternLongWidth=106875;
		patternLongWidthMove=78375;
		patternMatrixWidth=1781;
	}*/
	if (SLBitPerMM<950)//800//jpc change 20131217
	{
		totalHeight=80000;
		matrixTimesX=20;
		matrixTimesY=4;
		patternLongWidth=106875;
		patternLongWidthMove=78375;
		patternMatrixWidth=1781;
		if (SLBitPerMM<750)
		{//695
			totalHeight=91000;
			matrixTimesX=25;
			matrixTimesY=5;
			patternLongWidth=135324;
			patternLongWidthMove=90216;
			patternMatrixWidth=1640;
		}
	}
	if (SLBitPerMM>1050)
	{//暂时
		totalHeight=45000;
		matrixTimesX=10;
		matrixTimesY=2;
		patternLongWidth=60000;
		patternLongWidthMove=44000;
		patternMatrixWidth=2250;
	}
	
	BOOL RetVal;	
	int i=0,j=0;	
	i = m_PatternYTimes[nHead] % matrixTimesY;
	if((i==0) && (m_PatternXTimes[nHead]==0))
	{  //需要分配新的水平位置
		j = totalWidth-(m_PatternYTimes[nHead]/matrixTimesY*patternLongWidth);
		if(j < patternLongWidth)
		{		
			m_PatternXTimes[nHead] = 0;
			m_PatternYTimes[nHead] = 0;
			RetVal = false;
		}
		else
		{
			ReturnPos.x =(m_PatternYTimes[nHead]/matrixTimesY*patternLongWidth)+patternLongWidthMove/2;
			ReturnPos.y =-patternLongWidthMove/2;
			m_PatternXTimes[nHead]++;
			RetVal = true;
		}
	}
	else
	{ //不需要分配新的水平位置		
		ReturnPos.x = (m_PatternYTimes[nHead]/matrixTimesY*patternLongWidth)+m_PatternXTimes[nHead]*patternMatrixWidth+patternLongWidthMove/2;	
		ReturnPos.y = -(m_PatternYTimes[nHead]%matrixTimesY)*patternMatrixWidth-patternLongWidthMove/2;
		m_PatternXTimes[nHead]++;
		if (m_PatternXTimes[nHead]==matrixTimesX)
		{
			m_PatternXTimes[nHead]=0;
			m_PatternYTimes[nHead]++;
		}
		RetVal = true;
	}	
	return RetVal;
}

void SystemDoc::AccuracyTestChangeRow(int nHead)//jpc add 20130304
{//换行，
	if(GetDoc().GetLargeTable()==1)
	{
		if (m_PatternYTimes[nHead]!=0)
		{
			m_PatternXTimes[nHead]++;
			m_PatternYTimes[nHead]=0;
		}
	}
	else
	{
		if (m_PatternXTimes[nHead]!=0)
		{
			m_PatternYTimes[nHead]++;
			m_PatternXTimes[nHead]=0;
		}
	}
}

void SystemDoc::SetCCDBoardThick(long lThick)
{
	m_lCCDBoardThick = lThick;
}

long SystemDoc::GetCCDBoardThick() const
{
	return m_lCCDBoardThick;
}

void SystemDoc::SetGalvoBoardThick(long lThick)
{
	m_lGalvoBoardThick = lThick;
}

long SystemDoc::GetGalvoBoardThick() const
{
	return m_lGalvoBoardThick;
}

void SystemDoc::SetOrgTimes(int nHead,long lTimes)
{
	m_iOrgTimes[nHead] = lTimes;
}

long SystemDoc::GetOrgTimes(int nHead) 
{
	ASSERT( nHead==HeadLeft||nHead==HeadRight);

	return m_iOrgTimes[nHead];
}

void SystemDoc::SetPatternTimes(int nHead,long lTimes)
{
	m_iPatternTimes[nHead] = lTimes;
}

long SystemDoc::GetPatternTimes(int nHead) 
{
	ASSERT( nHead==HeadLeft||nHead==HeadRight);

	return m_iPatternTimes[nHead];
}

void SystemDoc::SetThicknessZero(long lThick,int nHead)
{
	ASSERT( nHead==HeadLeft||nHead==HeadRight);

	m_lThicknessZero[nHead]=lThick;
}

long SystemDoc::GetThicknessZero(int nHead) 
{
	ASSERT( nHead==HeadLeft||nHead==HeadRight);

	return m_lThicknessZero[nHead];
}

void SystemDoc::SetThicknessX(long lThicknessX)
{
	m_lThicknessX=lThicknessX;
}

long SystemDoc::GetThicknessX() 
{
	return m_lThicknessX;
}

void SystemDoc::SetThicknessY(long lThicknessY)
{
	m_lThicknessY=lThicknessY;
}

long SystemDoc::GetThicknessY()
{
	return m_lThicknessY;
}

void SystemDoc::SetThickingType(BOOL bType)
{
	m_ThickingType=bType;
}

BOOL SystemDoc::GetThickingType()
{
	return m_ThickingType;
}

void SystemDoc::SetTestBoardThickness(long nThickness)
{
	m_ulTestBoardThickness=nThickness;
}

long SystemDoc::GetTestBoardThickness()
{
	return m_ulTestBoardThickness;
}

void SystemDoc::SetRegionDim(long iRegionDim)
{
	m_iRegionDim=iRegionDim;
}

long SystemDoc::GetRegionDim()
{
	return m_iRegionDim;
}

void SystemDoc::SetBETPriOffset(long offset)
{
	m_lBETPriOffset=offset;
}

long SystemDoc::GetBETPriOffset()
{
	return m_lBETPriOffset;
}

void SystemDoc::SetTextTest(CString string)
{
	m_strTextTest=string;
}

CString SystemDoc::GetTextTest()
{
	return m_strTextTest;
}

void SystemDoc::SetTextHeigth(double heigth)
{
	m_fTextHeigth=heigth;
}

double SystemDoc::GetTextHeigth()
{
	return m_fTextHeigth;
}

void SystemDoc::SetFault(BOOL bFault)
{
	m_bFault=bFault;
}

BOOL SystemDoc::GetFault()
{
	return m_bFault;
}

void SystemDoc::SetWarner(BOOL BWarner)
{
	m_bWarner=BWarner;
}

BOOL SystemDoc::GetWarner()
{
	return m_bWarner;
}

void SystemDoc::SetLoadSubNo(int SubNo)//ly add 20120426
{
	m_LoadSubno = SubNo;
}

void SystemDoc::SetUnLoadSubNo(int SubNo)//ly add 20120426
{
	m_UnLoadSubno = SubNo;
}

int  SystemDoc::GetLoadSubNo()//ly add 20120426
{
	return m_LoadSubno;
}

int  SystemDoc::GetUnLoadSubNo()//ly add 20120426
{
	return m_UnLoadSubno;
}

SystemDoc::FILEMODE SystemDoc::GetFileMode()const
{
	return m_FileMode;
}

void SystemDoc::SetFileMode(FILEMODE fm)
{
	m_FileMode=fm;
}

Coord SystemDoc::GetLocalMarkDataRealPos(int DataIndex,int PosIndex,int nHead)
{
	ASSERT(nHead==0||nHead==1);

	if(nHead==0)
	{
		return m_LocalMarkDataRealPosL[DataIndex].m_LocalMarkData[PosIndex];
	}
	else if(nHead==1)
	{
		return m_LocalMarkDataRealPosR[DataIndex].m_LocalMarkData[PosIndex];
	}	
}

void SystemDoc::AddLocalMarkDataRealPos(const Coord& crd,int DataIndex,int nHead)
{
	ASSERT(nHead==0||nHead==1);

	if(nHead==0)
	{
		m_LocalMarkDataRealPosL[DataIndex].m_LocalMarkData.push_back(crd);
	}
	else if(nHead==1)
	{
		m_LocalMarkDataRealPosR[DataIndex].m_LocalMarkData.push_back(crd);
	}
}

long SystemDoc::GetLocalMarkDataRealPosNum(int DataIndex,int nHead)const
{
	ASSERT(nHead==0||nHead==1);

	if(nHead==0)
	{
		return m_LocalMarkDataRealPosL[DataIndex].m_LocalMarkData.size();
	}
	else if(nHead==1)
	{
		return m_LocalMarkDataRealPosR[DataIndex].m_LocalMarkData.size();
	}
}

void SystemDoc::ClearLocalMarkDataRealPos()
{
	std::vector<LocalMarkData>::iterator mi;

	for( mi=m_LocalMarkDataRealPosL.begin();mi!=m_LocalMarkDataRealPosL.end();++mi)
	{
		mi->m_LocalMarkData.clear();
	}
	m_LocalMarkDataRealPosL.clear();

	for( mi=m_LocalMarkDataRealPosR.begin();mi!=m_LocalMarkDataRealPosR.end();++mi)
	{
		mi->m_LocalMarkData.clear();
	}
	m_LocalMarkDataRealPosR.clear();
}

void SystemDoc::AddLocalMarkDataPosInfo(int DataIndex,int nHead)
{
	ASSERT(nHead==0||nHead==1);

	if(nHead==0)
	{
		m_LocalMarkDataRealPosL.push_back(LocalMarkData());
		m_LocalMarkDataRealPosL[m_LocalMarkDataRealPosL.size()-1].m_iIndex=DataIndex;
	}
	else if(nHead==1)
	{
		m_LocalMarkDataRealPosR.push_back(LocalMarkData());
		m_LocalMarkDataRealPosR[m_LocalMarkDataRealPosR.size()-1].m_iIndex=DataIndex;
	}
}

HoleCoordV SystemDoc::GetLocalMark(int DataIndex,int nHead)
{
	ASSERT(nHead==0||nHead==1);

	if(nHead==0)
	{
		return m_LocalMarkDataRealPosL[DataIndex].m_LocalMarkData;
	}
	else if(nHead==1)
	{
		return m_LocalMarkDataRealPosR[DataIndex].m_LocalMarkData;
	}
}

void SystemDoc::ClearInnerFiducailRealPos()
{
	m_InnerFiducialRealPosR.clear();
	m_InnerFiducialRealPosL.clear();
}

long SystemDoc::GetInnerFiducialPosNum(int nHead) const
{
	ASSERT(nHead==0||nHead==1);
	if(nHead==0)
	{
		return m_InnerFiducialRealPosL.size();
	}
	else if(nHead==1)
	{
		return m_InnerFiducialRealPosR.size();
	}
	else
	{
		return -1;
	}
}


void SystemDoc::AddInnerFiducialPos(const Coord &crd, int nHead)
{
	ASSERT(nHead==0||nHead==1);
	if(nHead==0)
	{
		m_InnerFiducialRealPosL.push_back(crd);
	}
	else if(nHead==1)
	{
		m_InnerFiducialRealPosR.push_back(crd);
	}
}

Coord SystemDoc::GetInnerFiducialPos(int nIndex, int nHead)
{
	ASSERT(nHead==0||nHead==1);
	
	if(nHead==0)
	{
		return m_InnerFiducialRealPosL[nIndex];
	}
	else if(nHead==1)
	{
		return m_InnerFiducialRealPosR[nIndex];
	}
}

HoleCoordV SystemDoc::GetInnerFiducial(int nHead)
{
	ASSERT(nHead==0||nHead==1);
	
	if(nHead==0)
	{
		return m_InnerFiducialRealPosL;
	}
	else if(nHead==1)
	{
		return m_InnerFiducialRealPosR;
	}
}

void SystemDoc::SetGlvAdjustThreshold(long threshold)
{
	m_iGlvAdjustThreshold=threshold;
}

long SystemDoc::GetGlvAdjustThreshold()
{
	return m_iGlvAdjustThreshold;
}

long SystemDoc::GetDistanceCenterThreshold()
{
	return m_iDistanceCenterThreshold;
}

void SystemDoc::SetDistanceCenterThreshold(long iDistanceCenterThreshold)
{
#ifdef USELOG													//20190711 增加
	if(m_iDistanceCenterThreshold!=iDistanceCenterThreshold)
	{
		BeforeStr.Format("前:%d",m_iDistanceCenterThreshold);
		AfterStr.Format("后:%d",iDistanceCenterThreshold);

		GetLog().Append_pro(AfterStr,"标靶误差容许阈值改变",BeforeStr);
	}
#endif

	 m_iDistanceCenterThreshold=iDistanceCenterThreshold;
}


void SystemDoc::SetPCBScaleThreshold(double threshold)
{
#ifdef USELOG													//20190711 增加
	if(m_fPCBScaleThreshold!=threshold)
	{
		BeforeStr.Format("前:%f",m_fPCBScaleThreshold);
		AfterStr.Format("后:%f",threshold);

		GetLog().Append_pro(AfterStr,"外标靶涨缩阈值改变",BeforeStr);
	}
#endif

	m_fPCBScaleThreshold=threshold;
}

double SystemDoc::GetPCBScaleThreshold()
{
	return m_fPCBScaleThreshold;
}

void SystemDoc::SetPCBScaleThrd(long threshold)//ly add 20120919
{
#ifdef USELOG													//20190711 增加
	if(m_fPCBScaleThrd!=threshold)
	{
		BeforeStr.Format("前:%d",m_fPCBScaleThrd);
		AfterStr.Format("后:%d",threshold);

		GetLog().Append_pro(AfterStr,"外标靶涨缩阈值改变",BeforeStr);
	}
#endif

	m_fPCBScaleThrd=threshold;
}

long SystemDoc::GetPCBScaleThrd()//ly add 20120919
{
	return m_fPCBScaleThrd;
}

void SystemDoc::SetLaserPowerTestSt(double power)
{
	m_fLaserPowerTestSt=power;
}

double SystemDoc::GetLaserPowerTestSt()
{
	return m_fLaserPowerTestSt;
}

void SystemDoc::SetLaserPowerTestMax(double power)//ly add 20120924
{
	m_fLaserPowerTestMax=power;
}

double SystemDoc::GetLaserPowerTestMax()//ly add 20120924
{
	if (GetDoc().GetDrillInc())//20150610
		return m_fLaserPowerTestSt;
	else
		return m_fLaserPowerTestMax;
}

/*void SystemDoc::SetLotIDMode(int nMode)
{
	m_iLotIDProMode=nMode;
}

int SystemDoc::GetLotIDMode()
{
	return m_iLotIDProMode;
}*/

long SystemDoc::GetAutoThickError()
{
	return m_iAutoThickError;
}

void SystemDoc::SetAutoThickError(long error)
{
	m_iAutoThickError=error;
}

long SystemDoc::GetCurAptNo()
{
	return m_iCurrentAptNo;
}

void SystemDoc::SetCurAptNo(long aptno)
{
	m_iCurrentAptNo=aptno;
}

BOOL SystemDoc::GetEnFiducial(int index)
{
	ASSERT(index<4);
	return m_bEnFiducial[index];
}

void SystemDoc::SetEnFiducial(BOOL enable,int index)
{
	ASSERT(index<4);
	m_bEnFiducial[index]=enable;
}

BOOL SystemDoc::GetToolCycleMode()
{
	return m_bToolCycleMode;
}

void SystemDoc::SetToolCycleMode(BOOL tcm)
{
	m_bToolCycleMode=tcm;
}

BOOL SystemDoc::GetAutoAdjustPattern(int index)
{
	ASSERT(index<2);
	return m_bAutoAdjustPattern[index];
}

void SystemDoc::SetAutoAdjustPattern(BOOL aap,int index)
{
	ASSERT(index<2);
	m_bAutoAdjustPattern[index]=aap;
}

BOOL SystemDoc::GetAutoLaserPowerTest(int index)
{
	ASSERT(index<2);
	return m_bAutoLaserPowerTest[index];
}

void SystemDoc::SetAutoLaserPowerTest(BOOL alpt,int index)
{
	ASSERT(index<2);
	m_bAutoLaserPowerTest[index]=alpt;
}

BOOL SystemDoc::GetEnAutoAdjust()
{
	return m_bEnableAutoAdjust;
}

void SystemDoc::SetEnAutoAdjust(BOOL enable)
{
	m_bEnableAutoAdjust=enable;
}

BOOL SystemDoc::GetEnAutoPower()
{
	return m_bEnableAutoPower;
}

void SystemDoc::SetEnAutoPower(BOOL enable)
{
	m_bEnableAutoPower=enable;
}

void SystemDoc::SetCTIHWWarning(BOOL enable)//ly add 20130708
{
	m_bCTIHWWarning = enable ;
}

BOOL SystemDoc::GetCTIHWWarning()// ly add 20130708
{
	return m_bCTIHWWarning;
}

BOOL SystemDoc::GetEnFidRetry()//ly add 20120202
{
	return m_bEnableFidRetry;
}

void SystemDoc::SetEnFidRetry(BOOL enable)//ly add 20120202
{
	m_bEnableFidRetry=enable;
}

int SystemDoc::GetNGSum()//ly add 20121127
{
	return m_lNgSum;
}

void SystemDoc::SetNGSum(int sum)//ly add 20121127
{
	m_lNgSum=sum;
}

int SystemDoc::GetNGThred()//ly add 20121127
{
	return m_lNgThrd;
}

void SystemDoc::SetNGThred(int thred)//ly add 20121127
{
	m_lNgThrd=thred;
}

int SystemDoc::GetLastWarningNo()
{
	return m_nWarningNo;
}

void SystemDoc::SetLastWarningNo(int wNo)
{
	m_nWarningNo=wNo;
	IsWarning();
}

int SystemDoc::GetLastAlarmId()
{
	return m_nAlarmId;
}

void SystemDoc::SetLastAlarmId(int alarmid)
{
	m_nAlarmId=alarmid;
}

void SystemDoc::SetLastWarningNoUM(int wNo)
{
	m_nWarningNo=wNo;
}

BOOL SystemDoc::GetFaultRun()
{
	return m_bFaultRun;
}

void SystemDoc::SetFaultRun(BOOL fr)
{
	m_bFaultRun=fr;
}

void SystemDoc::SetCheckPeriod(BOOL able)
{
	m_CheckPeriod=able;
}

BOOL SystemDoc::GetCheckPeriod() const
{
	return m_CheckPeriod;
}

BOOL SystemDoc::GetUIManSetScale()//ly add 20140504
{
	return m_bUIManSetScale;
}

void SystemDoc::SetUIManSetScale(BOOL bFlag)
{
	m_bUIManSetScale = bFlag;
}

BOOL SystemDoc::GetUseRefScale()//ly add 20140504
{
	return m_bUseRefScale;
}

void SystemDoc::SetUseRefScale(BOOL bFlag)
{
	if(m_bUIManSetScale==1)
	{
		m_bUseRefScale = bFlag;
	}
	else
	{
		m_bUseRefScale=0;
	}
}

////////////////////////////////////////////////////////////
BOOL SystemDoc::IsManSetScale()
{
//	return m_bManSetBoardScale;
//	return (m_bManSetBoardScale&&m_bManScaleisCheck);

	return m_bManScaleisCheck;
}

void SystemDoc::SetCheckManScale(BOOL isCheck)		//界面上无显示时，手工设定涨缩加工功能是无效的
{
	if(m_bUIManSetScale==1)
		m_bManScaleisCheck = isCheck;
	else
		m_bManScaleisCheck = false;

//	m_bManScaleisCheck = isCheck;
}
/*
void SystemDoc::CfgManSetScaleFlag(BOOL bFlag)
{
	if(m_bUIManSetScale==1)
		m_bManSetBoardScale = bFlag;
	else
		m_bManSetBoardScale = 0;
}
*/
////////////////////////////////////////////////////////////

int SystemDoc::InputManSetScaleVal(double fScaleX,double fScaleY)
{
	//涨缩范围-8.0% - 8.0%,参考Sieb&meyer help
	if(fScaleX < 0.92 || fScaleX > 1.08)
		return 0;
	if(fScaleY < 0.92 || fScaleY > 1.08) 
		return 0;
	m_fManualScaleX = fScaleX;
	m_fManualScaleY = fScaleY;
	return 1;
}

int SystemDoc::GetManSetScaleVal(double& fScaleX,double& fScaleY)
{
	fScaleX = m_fManualScaleX;
	fScaleY = m_fManualScaleY;
	return 1;
}

long SystemDoc::GetMainFiduPolarity()
{
#ifdef USERCOGNEX
	if (m_lMainFiduPolarity == 0)
	{
		return cogShapeExtractPolarityDarkOnLight;
	}
	return cogShapeExtractPolarityLightOnDark;
#else
	return m_lMainFiduPolarity;
#endif
}
long SystemDoc::GetInnerFiduPolarity()
{
#ifdef USERCOGNEX
	if (m_lInnerFiduPolarity == 0)
	{
		return cogShapeExtractPolarityDarkOnLight;
	}
	return cogShapeExtractPolarityLightOnDark;
#else
	return m_lInnerFiduPolarity;
#endif
}

void SystemDoc::SetMainFiduPolarity(long nPolarity)
{
	m_lMainFiduPolarity = nPolarity;
}
void SystemDoc::SetInnerFiduPolarity(long nPolarity)
{
	m_lInnerFiduPolarity = nPolarity;
}

int SystemDoc::GetPrecisionRowCount()
{//得到整版精度测试的行数
	return PrecisionCountRow;
}

void SystemDoc::SetPrecisionRowCount(int countRow)
{//保存整版精度测试的行数
	this->PrecisionCountRow=countRow;
}

int SystemDoc::GetPrecisionLineCount()
{//得到整版精度测试的列数
	return PrecisionCountLine;
}

void SystemDoc::SetPrecisionLineCount(int countLine)
{//保存整版精度测试的列数
	this->PrecisionCountLine=countLine;
}

int SystemDoc::GetPrecisionStepCount()
{//得到整版精度测试的步进
	return PrecisionCountStep;
}

void SystemDoc::SetPrecisionStepCount(int step)
{//保存整版精度测试的步进
	this->PrecisionCountStep=step;
}

int SystemDoc::GetPrecisionMoveCount()
{//得到整版精度测试的平移格数
	return PrecisionCountMove;
}

void SystemDoc::SetPrecisionMoveCount(int move)
{//保存整版精度测试的平移格数
	this->PrecisionCountMove=move;
}

long SystemDoc::GetPos(long ulAxisNo) const
{
	if(ulAxisNo==AXISTABX)
	{
		return m_CurPosX;
	}
	else if(ulAxisNo==AXISTABY)
	{	
		return m_CurPosY;
	}
	else
		return 0;
}

void SystemDoc::SetPos(long ulAxisNo,long fPos)
{
	if(ulAxisNo==AXISTABX)
	{
		m_CurPosX = fPos;
	}
	else if(ulAxisNo==AXISTABY)
	{	
		m_CurPosY = fPos;
	}
	else
		return ;
}

BOOL SystemDoc::GetTimeAnalyse()
{
	return isTimeAnalyse;
}

void SystemDoc::SetTimeAnalyse(BOOL isTimeAnalyse)
{
	this->isTimeAnalyse=isTimeAnalyse;
}

COleDateTime SystemDoc::GetBeginTimeAnalyse()
{
    return bigenTime;
}

void SystemDoc::SetBeginTimeAnalyse(COleDateTime bigenTime)
{
	this->bigenTime=bigenTime;
}

DWORD SystemDoc::GetCalculateBeginTime()
{
	return calculateBeginTime;
}

void SystemDoc::SetCalculateBeginTime(DWORD calculateBeginTime)
{
	this->calculateBeginTime=calculateBeginTime;
}

int  SystemDoc::GetIsOverBroad()
{
	return m_isOverBroad;
}

void SystemDoc::SetIsOverBroad(int isOverBroad)
{
	this->m_isOverBroad=isOverBroad;
}


int  SystemDoc::GetProcessModeToFile()
{
	return isProcessModeToFile;
}

void SystemDoc::SetProcessModeToFile(int isProcessModeToFile)
{
	this->isProcessModeToFile=isProcessModeToFile;
}

void SystemDoc::SetFunctionOverBorad(int temp)
{
	m_bFunctionOverBorad = temp ;
}

BOOL SystemDoc::GetFunctionOverBorad()
{
	return m_bFunctionOverBorad;
}

void SystemDoc::SetLaserWarning(BOOL laserWarning)
{
	this->m_bLaserWarning=laserWarning;
}

BOOL SystemDoc::GetLaserWarning()
{	
	return m_bLaserWarning;
}

void  SystemDoc::ReadLaserConfig()
{
	int  pinNumber=LoadConfig();

	if (pinNumber==88)
	{
		SaveConfig(0);
    	this->m_bLaserWarning=TRUE;
	}
	else
		this->m_bLaserWarning=FALSE;
}

int SystemDoc::LoadConfig()
{
	CFile File;
	int iLaserWarning=0;

	if(File.Open(_T("C:\\WINDOWS\\DataConfig.dat"), CFile::modeRead))
	{
		CArchive ar(&File, CArchive::load);
		ar >> iLaserWarning;
		ar.Close();
		File.Close();
	}
	
	return iLaserWarning;
}

BOOL SystemDoc::SaveConfig(int saveNumber)
{	
	CFile File;

	if(File.Open(_T("C:\\WINDOWS\\DataConfig.dat"), CFile::modeCreate|CFile::modeWrite| CFile::typeBinary ))
	{
		CArchive ar(&File, CArchive::store);
		ar << saveNumber;	
		ar.Close();
		File.Close();
	}
	
	return TRUE;
}

Coord SystemDoc::GetLeftRightFiducialMoveCrd(int index)
{
	return m_LeftRightFiducialMoveCrd[index];
}
void SystemDoc::SetLeftRightFiducialMoveCrd(int index,Coord crd)
{
	this->m_LeftRightFiducialMoveCrd[index]=crd;
}

//20160809
BOOL SystemDoc::GetSysCircleProcMode()
{
	return m_bSysCircleProcMode;
}

void SystemDoc::SetSysCircleProcMode(BOOL scpm)
{
	this->m_bSysCircleProcMode=scpm;
}

long SystemDoc::GetSysBeamDia()
{
	return m_lSysBeamDia;
}

void SystemDoc::SetSysBeamDia(long sbd)
{
	this->m_lSysBeamDia=sbd;
}

long SystemDoc::GetSysBeamStep()
{
	return m_lSysBeamStep;
}

void SystemDoc::SetSysBeamStep(long sbs)
{
	this->m_lSysBeamStep=sbs;
}
//20160812
void SystemDoc::AddSysScaleSet(ScaleSet ss)
{
    m_SysScaleSet.push_back(ss);
}

void SystemDoc::AddSysIngredientExplainSet(IngredientExplainSet is)
{
    m_SysIngredientExplainSetV.push_back(is);
}

void SystemDoc::DeleteSysScaleSet(int index)
{
    ASSERT(index<m_SysScaleSet.size());

    m_SysScaleSet.erase(m_SysScaleSet.begin()+index);
}
/*
ScaleSet SystemDoc::GetSysScaleSet(int index)
{
    ASSERT(index<m_SysScaleSet.size());

	return m_SysScaleSet[index];
}
*/
std::vector<ScaleSet>::iterator SystemDoc::GetSysScaleSet(int index)
{
    ASSERT(index<m_SysScaleSet.size());

	return (m_SysScaleSet.begin()+index);
}

std::vector<IngredientExplainSet>::iterator SystemDoc::GetSysIngredientExplainSet(int index)
{
    ASSERT(index<m_SysIngredientExplainSetV.size());

	return (m_SysIngredientExplainSetV.begin()+index);
}

int SystemDoc::GetSysScaleSetSize()
{
	return m_SysScaleSet.size();
}

int SystemDoc::GetSysIngredientExplainSetSize()
{
	return m_SysIngredientExplainSetV.size();
}

int SystemDoc::GetSysInfoDBMode()
{
	return m_iSysInfoDBMode;
}

void SystemDoc::SetSysInfoDBMode(int sidm)
{
	this->m_iSysInfoDBMode=sidm;
}

CString SystemDoc::GetSysProcFileName()
{
	return m_strSysProcFileName;
}

void SystemDoc::SetSysProcFileName(CString spfn)
{
	this->m_strSysProcFileName=spfn;
}

CString SystemDoc::GetSysMachineSn()
{
	return m_strSysMachineSn;
}

void SystemDoc::SetSysMachineSn(CString macSn)
{
	m_strSysMachineSn = macSn;
}

CString SystemDoc::GetSysImesURL()
{
	return m_strSysImesURL;
}

void SystemDoc::SetSysImesURL(CString url)
{
	m_strSysImesURL = url;
}

long SystemDoc::GetSysTimeout()
{
	return m_strSysTimeout;
}

void SystemDoc::SetSysTimeout(long timeOut)
{
	m_strSysTimeout = timeOut;
}

long SystemDoc::GetSysIdtTime()
{
	return m_strSysIdtTime;
}

void SystemDoc::SetSysIdtTime(long idtTime)
{
	m_strSysIdtTime = idtTime;
}

BOOL SystemDoc::GetSysUserControlSwitch()
{
	if (m_SysUserControlSwitch == 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL SystemDoc::GetSysModeSwitch()
{
	if (m_SysModeSwitch == 0)
	{
		return FALSE;
	}
	return TRUE;
}

void SystemDoc::SetSysModeSwitch(long modeSwit)
{
	m_SysModeSwitch = modeSwit;
}

void SystemDoc::SetSysUserControlSwitch(long userSwit)
{
	m_SysUserControlSwitch = userSwit;
}

CString SystemDoc::GetSysHeartbeatContent()
{
	return m_strSysHeartbeatContent;
}

void SystemDoc::SetSysHeartbeatContent(CString content)
{
	m_strSysHeartbeatContent = content;
}

CString SystemDoc::GetSysHeartbeatFreq()
{
	return m_strSysHeartbeatFreq;
}

void SystemDoc::SetSysHeartbeatFreq(CString freq)
{
	m_strSysHeartbeatFreq = freq;
}

long SystemDoc::GetCompanyCode()
{
	return m_SysCompanyCode;
}

CString SystemDoc::GetSysProcLOTID()
{
	return m_strSysProcLOTID;
}

void SystemDoc::SetSysProcLOTID(CString spli)
{
	this->m_strSysProcLOTID=spli;
}

CString SystemDoc::GetSysProcPRODID()
{
	return this->m_strSysProcPRODID;
}

void SystemDoc::SetSysProcPRODID(CString prod)
{
	this->m_strSysProcPRODID = prod;
}

CString SystemDoc::GetSysUserDEPTID()
{
	return this->m_strSysUserDEPTID;	
}

void SystemDoc::SetSysUserDEPTID(CString dept)
{
	this->m_strSysUserDEPTID = dept;
}

UINT SystemDoc::GetSysSNProcedPCBNum()
{
	return m_ulSysSNProcedPCBNum;
}

void SystemDoc::SetSysSNProcedPCBNum(UINT ulNum)
{
	this->m_ulSysSNProcedPCBNum=ulNum;
}

UINT SystemDoc::GetSysPCBCount()									//20180118
{
	return m_ulSysPCBCount;
}

void SystemDoc::SetSysPCBCount(UINT ulNum)
{
	this->m_ulSysPCBCount=ulNum;
}
//-------------------------------------------------------------------20160919
int SystemDoc::GetHdSysDeadTime()
{
	return m_iHdSysDeadTime;
}

void SystemDoc::SetHdSysDeadTime(int hsdt)
{
	this->m_iHdSysDeadTime=hsdt;
}

int SystemDoc::GetHdSysLaserTriggerAdjust()
{
	return m_iHdSysLaserTriggerAdjust;
}

void SystemDoc::SetHdSysLaserTriggerAdjust(int hslta)
{
	this->m_iHdSysLaserTriggerAdjust=hslta;
}

int SystemDoc::GetHdSysPulseMode()
{
	return m_iHdSysPulseMode;
}

void SystemDoc::SetHdSysPulseMode(int hspm)
{
	this->m_iHdSysPulseMode=hspm;
}

int SystemDoc::GetHdSysAOMOnDelay()
{
	return m_iHdSysAOMOnDelay;
}

void SystemDoc::SetHdSysAOMOnDelay(int hsaod)
{
	this->m_iHdSysAOMOnDelay=hsaod;
}

int SystemDoc::GetHdSysAOMOffAhead()
{
	return m_iHdSysAOMOffAhead;
}

void SystemDoc::SetHdSysAOMOffAhead(int hsaoa)
{
	this->m_iHdSysAOMOffAhead=hsaoa;
}

float SystemDoc::GetHdSysLaserMAXDutyCycle()
{
	return m_fHdSysLaserMAXDutyCycle;
}

void SystemDoc::SetHdSysLaserMAXDutyCycle(float hslmdc)
{
	this->m_fHdSysLaserMAXDutyCycle=hslmdc;
}
//-------------------------------------------------------------20161109
BOOL SystemDoc::GetIsDoubleFileData()
{
	return m_bDoubleFileData;
}

void SystemDoc::SetIsDoubleFileData(BOOL idfd)
{
	this->m_bDoubleFileData=idfd;
}

BOOL SystemDoc::GetExcellonData0IsUp()
{
	return m_bExcellonData0IsUp;
}

int SystemDoc::GetDisplayColCount()
{
	return m_iDisplayColCount;
}

int SystemDoc::GetDisplayRowCount()
{
	return m_iDisplayRowCount;
}

//循环加工用时监控											//20161212
long SystemDoc::GetProcTime()
{
	return m_iProcTime;
}

void SystemDoc::SetProcTime(long pt)
{
	this->m_iProcTime=pt;
}

//重构加工流程：20161123
int SystemDoc::GetFlowPathMode()
{
	return m_iFlowPathMode;
}

void SystemDoc::SetFlowPathMode(int fpm)
{
	this->m_iFlowPathMode=fpm;
}

int SystemDoc::GetProcAxisMode()
{
	return m_iProcAxisMode;
}

void SystemDoc::SetProcAxisMode(int pam)
{
	this->m_iProcAxisMode=pam;
}

BOOL SystemDoc::GetASideIsProcessing()
{
	return m_bASideIsProcessing;
}

void SystemDoc::SetASideIsProcessing(BOOL asip)
{
	this->m_bASideIsProcessing=asip;
}

BOOL SystemDoc::GetASideIsDisplay()
{
	return m_bASideIsDisplay;
}

void SystemDoc::SetASideIsDisplay(BOOL asid)
{
	this->m_bASideIsDisplay=asid;
}

Coord SystemDoc::GetFirstMarkPos(BOOL bSide)
{
	if(bSide)
		return m_crdFirstMarkA;
	else
		return m_crdFirstMarkB;
}

void SystemDoc::SetFirstMarkPos(Coord crd,BOOL bSide)
{
	if(bSide)
		this->m_crdFirstMarkA=crd;
	else
		this->m_crdFirstMarkB=crd;
}

//AVT相机																				//20170829
unsigned long SystemDoc::GetCameraSNHigh(int index)
{
	ASSERT(index==0||index==1);

	return atoi(m_strCameraSNHigh[index]);
}

unsigned long SystemDoc::GetCameraSNLow(int index)
{
	ASSERT(index==0||index==1);

	return atoi(m_strCameraSNLow[index]);
}

//文件优化状态												//20180116
BOOL SystemDoc::GetFileIsOptimized()
{
	return m_bFileIsOptimized;
}

void SystemDoc::SetFileIsOptimized(BOOL fio)
{
	this->m_bFileIsOptimized=fio;
}

//有关时间控制加密狗
#ifdef SENTINAL
BOOL SystemDoc::InitSentinal()								//20180126
{
	const hasp_feature_t feature = 1;	
//	hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
	m_timeHandle = HASP_INVALID_HANDLE_VALUE;
	hasp_status_t status;
	
	unsigned char vendor_code[] =
		"g2gfJoiJYIT+iIsVysRK36/hhrMLGTAHX29xXTgo84/x1E6BFLioB4FEBbu8V2K"
		"1a4UqkFFsHAXoE8yy8nTTMfSiTQYVYA1UipYU4xilfkKxJ7TMkTwG2TPHBzOi5R"
		"G67DjgHbxpcmVKtL9cawn1DWf8GO9o/88muNADbr/TvqPIzLTyMWcExQkCP8DIn"
		"eN5nM1fr8lS3T/ZNvLpv0+krlZOU0IdwV+RL9vVnplZ2zNKxuK8lbHr88rlqYBd"
		"iqGVUAJ2UDVJwDQnCVwX3j3wfObokyRvuSEglvXtjkGTxkHowonSBCYBTSBUMv7"
		"HR3NBA6g5W60KSDd8rzPSytJYmFaaWrUBrIGuIBXAOhbKVVlUMunxXwIs2gDxqK"
		"BLeLyOQrPam4hv2ZNa+6+Mll/IfT2VjND7z0Ea6yPNzvqsKPnGDU4IzG7S2Tnb0"
		"ecWjqCiH17dyNNoPqjlie0pEfvNDajCEDf+QCJTROlIqUcmaBTUTRQeJsPRjKf4"
		"HzbIFzDLdSc0ALhOI2LRn1MFe7Hv9PTvFC8BmWn81TDzOgRv+H5kDE9ffLa1GXu"
		"LiFNxZtXBi4P5CK+92llABSkiWAhcbIwVloOoYOJXtCGhRF+56wFx3MPkhqSC2N"
		"RRe9S8yUMAlPiAj6/Ka/j47WvJ5i2PGa00YtOZ3NXoM85BNPz3p2ydLdUXmgopg/"
		"nQuX1T/u6QJYi/HDZtmJGelVitJFHeZ3WGvrjLxgKcgtSvBVuw1YpxpfeF7IjMbx"
		"AafLHZwFSfkwXaToFc25k0IYZWSkIilpvFIuLtyRFp9ZDfqLp/jikT4RuZJy45Im"
		"Y430wPRiFb669s1cRVy1LSHo6dk9CEbNJ5kQbI/okEJk6EFQLxtQvzrcOsw8SVlN"
		"x8OqHd+Xke6lxcVMlJQ2DAN7EQX8dQcegbgn+NZGQh5A+S4HweHcW+aj0jYBhnzM"
		"tRJWGN1ATwDw/4UsgOT+Gg9m70ZwuiuQ==";
	
//	status = hasp_login(feature, vendor_code, &m_timeHandle);
	int ii=0;
	for(ii=0;ii<8;ii++)
	{
		status = hasp_login(feature, vendor_code, &m_timeHandle);
		
		if(status==HASP_STATUS_OK)
			break;
		
		Delay(1000);
	}
	
	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
        case HASP_FEATURE_NOT_FOUND:
            break;
        case HASP_HASP_NOT_FOUND:
            break;
        case HASP_OLD_DRIVER:
            break;
        case HASP_NO_DRIVER:
            break;
        case HASP_INV_VCODE:
            break;
        case HASP_FEATURE_TYPE_NOT_IMPL:
            break;
        case HASP_TMOF:
            break;
        case HASP_TS_DETECTED:
            break;
        default:
            break;
		}

		if(status==HASP_FEATURE_EXPIRED)
		{
			AfxMessageBox("设备的使用时间已到期，无法运行此设备，请确认！");
			return false;
		}
		
		AfxMessageBox("时间控制加密狗信息获取错误，无法运行此设备，请确认！");
		return false;
	}

	hasp_time_t timeForUse=0;
/*
	if(TimeController(timeForUse))
	{
		CString strInfo;
		if(timeForUse/86400<1)
			strInfo.Format("设备允许的使用时间已小于1天，请确认！");
		else
			strInfo.Format("设备的使用时间还有%d天，请确认！",timeForUse/86400);

		AfxMessageBox(strInfo);
	}
	else
		return false;
*/
	if(!TimeController(timeForUse))
		return false;

	return true;
}

BOOL SystemDoc::ReleaseSentinal()								//20180126
{
//	hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
	hasp_status_t status;

	status = hasp_logout(m_timeHandle);
	
	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
        case HASP_INV_HND:
            break;
        default:
            break;
		}
	}

	return true;
}

BOOL SystemDoc::TimeController(hasp_time_t& timeForUse)
{
	hasp_status_t status;
	char *info = 0;
	
	const char* format = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspformat root=\"hasp_info\">"
		"    <feature>"
		"        <attribute name=\"id\" />"
		"        <element name=\"license\" />"
		"        <hasp>"
		"          <attribute name=\"id\" />"
		"          <attribute name=\"type\" />"
		"        </hasp>"
		"    </feature>"
		"</haspformat>"
		"";
	
//	status = hasp_get_sessioninfo(m_timeHandle, format, &info);
	int ii=0;
	for(ii=0;ii<5;ii++)
	{
		status = hasp_get_sessioninfo(m_timeHandle, format, &info);
		
		if(status==HASP_STATUS_OK)
			break;

		hasp_free(info);
		Delay(1000);
	}
	
	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
        case HASP_FEATURE_NOT_FOUND:
            break;
        case HASP_INV_HND:
            break;
        case HASP_INV_FORMAT:
            break;
        default:
            break;
		}

		if(status==HASP_FEATURE_EXPIRED)
		{
			AfxMessageBox("设备的使用时间已到期，无法运行此设备，请确认！");
			hasp_free(info);
			return false;
		}

		AfxMessageBox("时间控制加密狗信息获取错误，无法运行此设备，请确认！");
		hasp_free(info);
		return false;
	}
	
	/* use the information, free it afterwards */
	if(strstr(info,"perpetual")!=NULL)						//20180126
	{
		hasp_free(info);
		return true;
	}

	const char* chStartTime="<time_start>";
	const char* chTotalTime="<total_time>";
	char* buf;
	char numBuf[32];
	int numLength=0;

	hasp_time_t secStartTime=0;
	hasp_time_t secTotalTime=0;
	hasp_time_t secTime=0;

	for(int kk=0;kk<2;kk++)
	{
		buf=NULL;
		if(kk==0)
			buf=strstr(info,chStartTime);
		else
			buf=strstr(info,chTotalTime);

		if(buf==NULL)
		{
			AfxMessageBox("时间控制加密狗信息获取错误，无法运行此设备，请确认！");
			hasp_free(info);
			return false;
		}
		
		buf=buf+12;
		memset(numBuf,'\0',32);
		
		while(isdigit(*buf))
		{
			sprintf(numBuf,"%s%c",numBuf,*buf);	//将连续数字量取出
			buf++;
		}
		
		numLength = strlen(numBuf);
		if(numLength==0)
		{
			AfxMessageBox("时间控制加密狗信息获取错误，无法运行此设备，请确认！");
			hasp_free(info);
			return false;
		}
		
		if(!sscanf(numBuf,"%d\n",&secTime))
		{
			AfxMessageBox("时间控制加密狗信息获取错误，无法运行此设备，请确认！");
			hasp_free(info);
			return false;
		}

		if(kk==0)
			secStartTime=secTime;
		else
			secTotalTime=secTime;
	}

	hasp_free(info);

	hasp_time_t time;
//	unsigned int day, month, year, hour, minute, second;
	
//	status = hasp_get_rtc(m_timeHandle, &time);
	for(ii=0;ii<5;ii++)
	{
		status = hasp_get_rtc(m_timeHandle, &time);
		
		if(status==HASP_STATUS_OK)
			break;
		
		Delay(1000);
	}
	
	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
        case HASP_INV_HND:
            break;
        case HASP_NO_TIME:
            break;
        default:
            break;
		}

		if(status==HASP_FEATURE_EXPIRED)
		{
			AfxMessageBox("设备的使用时间已到期，无法运行此设备，请确认！");
			return false;
		}

		AfxMessageBox("时间控制加密狗信息获取错误，无法运行此设备，请确认！");
		return false;
	}

//	status = hasp_hasptime_to_datetime(time, &day, &month, &year, &hour, &minute, &second);
	
//	if(status == HASP_INV_TIME)
//	{
		/* handle error */
//	}

	hasp_time_t remainTime=0;
	remainTime=secStartTime+secTotalTime-time;
	if(remainTime<=0)
	{
		AfxMessageBox("设备的使用时间已到期，无法运行此设备，请确认！");
		return false;
	}
	else
		timeForUse=remainTime;

	return true;
}

//登录信息保存至加密狗中									//20180126
BOOL SystemDoc::SaveUserInfoInSentinal()
{
 	hasp_status_t status;
	char data[1024];
	memset(data,'\0',1024);

	sprintf(data,"%d",GetDoc().GetLoginUserNum());

	for( int n=0;n<GetDoc().GetLoginUserNum();++n)
	{
		sprintf(data+4+n*100,
				"%s %s %d",
				(LPCTSTR)GetDoc().GetLoginUserInfo(n).strUserName,
				(LPCTSTR)GetDoc().GetLoginUserInfo(n).strPassword,
				GetDoc().GetLoginUserInfo(n).nLevel);
	}

	status = hasp_write(m_timeHandle, HASP_FILEID_RW, 0, 1024, data);
	
	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
        case HASP_FEATURE_NOT_FOUND:
            break;
        case HASP_INV_HND:
            break;
        case HASP_INV_FILEID:
            break;
        case HASP_MEM_RANGE:
            break;
        default:
            break;
		}
	}

    return TRUE;
}

BOOL SystemDoc::LoadUserInfoInSentinal()
{
 	hasp_status_t status;
	char data[1024];
	memset(data,'\0',1024);

	status = hasp_read(m_timeHandle, HASP_FILEID_RW, 0, 1024, data);
	
	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
        case HASP_FEATURE_NOT_FOUND:
            break;
        case HASP_INV_HND:
            break;
        case HASP_INV_FILEID:
            break;
        case HASP_MEM_RANGE:
            break;
        default:
            break;
		}
	}

	int count=0;
	char  Name[32];
	char  Password[32];
    DWORD    value;

    m_UserInfo.clear();

	sscanf(data,"%d",&count);

	for(int n=0;n< count;++n)
	{
		sscanf(data+4+n*100,"%s %s %d",Name,Password,&value);
		
		GetDoc().AddUserInfo(UserInfo(value,Name,Password));
	}

	return TRUE;
}
#endif

Coord SystemDoc::GetLBRefPoint()
{
	return m_crdLBRefPoint;
}

void SystemDoc::SetLBRefPoint(Coord crd)
{
	this->m_crdLBRefPoint=crd;
}

//平台玻璃尺2D校正
BOOL SystemDoc::GetTableIsCali()
{
	return m_bTableIsCali;
}

void SystemDoc::SetTableIsCali(int nHead,int label,BOOL tic)
{
/*
	ASSERT(nHead==0||nHead==1);
	ASSERT(label==0||label==1);

	if(nHead==0)
	{
		if(label==0)
			m_bTable00IsCali=tic;
		else
			m_bTable01IsCali=tic;
	}

	m_bTableIsCali=(m_bTable00IsCali||m_bTable01IsCali);
*/
	this->m_bTableIsCali=tic;													//20200414
}

BOOL SystemDoc::LoadTableCorParam()
{
	CIniFile IniFile;
	CString str,path;
	BOOL bExist=false;

//	int tempXPoints=14;
// 	int tempYPoints=11;
// 	int tempXPoints=30;															//20180525
//	int tempYPoints=24;
 	int tempXPoints=14;															//20200414
 	int tempYPoints=18;
	Coord crd;
	HoleCoordV crdCommandV;
	HoleCoordV crdActualV;

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetPath(path);

//	for(int label=0;label<2;label++)
	for(int label=0;label<1;label++)											//20200414
	{
		str.Format("param\\TableCorData0%d",label);
		IniFile.SetName(str);

		bExist=IniFile.OpenIniFileForRead();
		if(bExist)
		{
			crdCommandV.clear();
			crdActualV.clear();

			for(int n=0; n<tempYPoints*tempXPoints;n++)
			{
				str.Format("Pos%dCX\0",n);
				if(!IniFile.GetItemInt ("TablePosErr",str,crd.x))
					return false;
				str.Format("Pos%dCY\0",n);
				if(!IniFile.GetItemInt ("TablePosErr",str,crd.y))
					return false;

				crdCommandV.push_back(crd);

				str.Format("Pos%dAX\0",n);
				if(!IniFile.GetItemInt ("TablePosErr",str,crd.x))
					return false;
				str.Format("Pos%dAY\0",n);
				if(!IniFile.GetItemInt ("TablePosErr",str,crd.y))
					return false;

				crdActualV.push_back(crd);
			}

			CogSetNPointToNPointDOFConstants(cogNPointToNPointDOFScalingAspectRotationSkewAndTranslation);
			
			if(!CogTableTransform(0,label,crdCommandV,crdActualV))
			{
				AfxMessageBox("平台2D变换参数计算错误，请确认！");
				return false;
			}
			
			SetTableIsCali(0,label,false);
			
			IniFile.CloseIniFile();
		}
		else
		{
			AfxMessageBox("无法导入平台2D校正参数！");
			return false;
		}
	}

	return true;
}

//蚊香式开窗												//20170224
BOOL SystemDoc::GetDrillCoil()
{
	return m_bDrillCoil;
}

void SystemDoc::SetDrillCoil(BOOL dc)
{
	this->m_bDrillCoil=dc;
}

double SystemDoc::GetGlvAdjustPresionL()
{
	return m_dGlvAdjustPresionL;
}

void SystemDoc::SetGlvAdjustPresionL(double presion)
{
	this->m_dGlvAdjustPresionL=presion;
}

double SystemDoc::GetGlvAdjustPresionR()
{
	return m_dGlvAdjustPresionR;
}

void SystemDoc::SetGlvAdjustPresionR(double presion)
{
	this->m_dGlvAdjustPresionR=presion;
}

//加工时台面真空监测用										//20180821
BOOL SystemDoc::GetAxisIsRun(int nHead)
{
	return m_bAxisIsRun[nHead];
}

void SystemDoc::SetAxisIsRun(int nHead,BOOL air)
{
	this->m_bAxisIsRun[nHead]=air;
}

long SystemDoc::GetFORWARDZ()
{
	return m_lFORWARDZ;
}

BOOL SystemDoc::GetAutoGalvoAdjustIsTimed()
{
	return m_bAutoGalvoAdjustIsTimed;
}

void SystemDoc::SetAutoGalvoAdjustIsTimed(BOOL aga)
{
	this->m_bAutoGalvoAdjustIsTimed=aga;
}

BOOL SystemDoc::GetAutoLaserTestIsTimed()
{
	return m_bAutoLaserTestIsTimed;
}

void SystemDoc::SetAutoLaserTestIsTimed(BOOL alt)
{
	this->m_bAutoLaserTestIsTimed=alt;
}

int SystemDoc::GetProcAxisSelected()
{
	return m_iProcAxisSelected;
}

void SystemDoc::SetProcAxisSelected(int pas)
{
	this->m_iProcAxisSelected=pas;
}

BOOL SystemDoc::GetPCBBoardIsReady()
{
	return m_bPCBBoardIsReady;
}

void SystemDoc::SetPCBBoardIsReady(BOOL bir)
{
	this->m_bPCBBoardIsReady=bir;
}

CString SystemDoc::GetSysRCSIP()
{
	return m_strSysRCSIP;
}

CString SystemDoc::GetSysRCSPort()
{
	return m_strSysRCSPort;
}

CString SystemDoc::GetSysTaskTypeRise()
{
	return m_strSysTaskTypeRise;
}

CString SystemDoc::GetSysTaskTypeDown()
{
	return m_strSysTaskTypeDown;
}

CString SystemDoc::GetSysRiseStaPositionCode()
{
	return m_strSysRiseStaPositionCode;
}

CString SystemDoc::GetSysRiseEndPositionCode()
{
	return m_strSysRiseEndPositionCode;
}

CString SystemDoc::GetSysDownStaPositionCode()
{
	return m_strSysDownStaPositionCode;
}

CString SystemDoc::GetSysDownEndPositionCode()
{
	return m_strSysDownEndPositionCode;
}

BOOL SystemDoc::LoadPartnerParam()
{
	CIniFile IniFile;
	CString str, path;

	path = AfxGetApp()->m_pszHelpFilePath;
	str = AfxGetApp()->m_pszExeName;
	path = path.Left(path.ReverseFind('.') - str.GetLength());
	IniFile.SetName("param\\PartnerPara");
	IniFile.SetPath(path);

	BOOL bExist = IniFile.OpenIniFileForRead();
	if (bExist)
	{
		if (!IniFile.GetItemString("RCS", "RCSIP", GetDoc().m_strSysRCSIP))
			GetDoc().m_strSysRCSIP = "";
		if (!IniFile.GetItemString("RCS", "RCSPort", GetDoc().m_strSysRCSPort))
			GetDoc().m_strSysRCSPort = "";
		if (!IniFile.GetItemString("RCS", "TaskTypeRise", GetDoc().m_strSysTaskTypeRise))
			GetDoc().m_strSysTaskTypeRise = "";
		if (!IniFile.GetItemString("RCS", "RiseStaPositionCode", GetDoc().m_strSysRiseStaPositionCode))
			GetDoc().m_strSysRiseStaPositionCode = "";
		if (!IniFile.GetItemString("RCS", "RiseEndPositionCode", GetDoc().m_strSysRiseEndPositionCode))
			GetDoc().m_strSysRiseEndPositionCode = "";
		if (!IniFile.GetItemString("RCS", "TaskTypeDown", GetDoc().m_strSysTaskTypeDown))
			GetDoc().m_strSysTaskTypeDown = "";
		if (!IniFile.GetItemString("RCS", "DownStaPositionCode", GetDoc().m_strSysDownStaPositionCode))
			GetDoc().m_strSysDownStaPositionCode = "";
		if (!IniFile.GetItemString("RCS", "DownEndPositionCode", GetDoc().m_strSysDownEndPositionCode))
			GetDoc().m_strSysDownEndPositionCode = "";
		
		IniFile.CloseIniFile();
	}
	else
	{
		AfxMessageBox("无法导入合作方参数！");
		return false;
	}

	return true;
}

long SystemDoc::GetLAndULSystem()
{
	return m_iLAndULSystem;
}

long SystemDoc::GetUnloadIsOK()
{
	return m_iUnloadIsOK;
}

long SystemDoc::GetTableAbsorbFirst()
{
	return m_iTableAbsorbFirst;
}

long SystemDoc::GetCustomerSpecial()
{
	return m_iCustomerSpecial;
}

long SystemDoc::GetMINlaserPeriod()
{
	return m_iMINlaserPeriod;
}

long SystemDoc::GetLaserComp1()
{
	return m_laserComp1;
}

long SystemDoc::GetLaserComp2()
{
	return m_laserComp2;
}

