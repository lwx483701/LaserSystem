// Excellon.cpp: implementation of the Excellon class.
//

//Modify Data: 2/22  modify push SubArea
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <algorithm>
#include <math.h>

#include "Excellon.h"
#include "Info.h"
#include "FileComDefine.h"
#include "warninginfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
ExcellonData& GetExcellonData()
{
	static ExcellonData excellondata;
	return excellondata;
}
*/
//-------------------------------------------------------------------------------------20161109
int globalExcellonIndex=0;								//多数据文件格式下的文件索引	

void SetGlobalExcellonIndex(int index)
{
	globalExcellonIndex=index;
}

int GetGlobalExcellonIndex()
{
	return globalExcellonIndex;
}

ExcellonData& GetExcellonData()											
{
	static ExcellonData excellondata0,excellondata1;
	if(globalExcellonIndex==0)
		return excellondata0;
	else
		return excellondata1;
}
//--------------------------------------------------------------------------------------
ExcellonData::ExcellonData()
{

}

ExcellonData::~ExcellonData()
{
	
}

bool IsNum(char ch)
{
    if (isdigit(ch) || ch=='-' || ch=='+' || ch=='.') 
		return true;
    else 
		return false;
}

bool IsAvaliableChar(char ch)
{
    if (isalnum(ch) || ch=='-' || ch=='+' || ch=='.'||ch==' '||ch=='$'||ch=='['||ch==']'||ch=='='||ch==','||ch=='%') 
		return true;
    else 
		return false;
}

BOOL EndOfLine(const char *buf) 
{
	if( *buf=='\n' || *buf=='\r' || *buf=='\0' )
		return TRUE;
	else 
		return FALSE;
}

long UserAtoL(char* buf)
{
	ASSERT(buf);
	char *pbuf;
    int rtn =0 ;
	
	pbuf = buf;
	
	if(EndOfLine(pbuf))
		return 0;
	rtn = atol(pbuf);
	while(IsNum(*pbuf))
	{
		pbuf++;
	}
	strcpy(buf,pbuf);
	
	pbuf = NULL;
	return rtn;
}
double UserAtoF(char* buf)
{
	ASSERT(buf);
	char *pbuf;
    double rtn =0 ;
	
	pbuf = buf;
	
	if(EndOfLine(pbuf))
		return 0;
	rtn = atof(pbuf);
	while(IsNum(*pbuf))
	{
		pbuf++;
	}
	strcpy(buf,pbuf);
	
	pbuf = NULL;
	return rtn;
	
}

void LeftMove(char* buf,long lbit)
{
	ASSERT(buf);
	ASSERT(lbit>=0);
	
	char *pbuf;
	
	if(lbit == 0)
		return ;
	pbuf = buf;
	
	while((lbit--))
	{
		pbuf++;
	}
	strcpy(buf,pbuf);
	
}

//MachineSign
Coord ExcellonData::GetMachineSignPos(int index) const
{
	return m_MachineSign[index].m_crdTextPos;
}

TextDir ExcellonData::GetMachineSignDir(int index) const
{
	return m_MachineSign[index].m_iDirection;
}

//DaySign
Coord ExcellonData::GetDaySignPos(int index) const
{
	return m_DaySign[index].m_crdTextPos;
}

TextDir ExcellonData::GetDaySignDir(int index) const
{
	return m_DaySign[index].m_iDirection;
}

Coord ExcellonData::GetTimeSignPos(int index) const
{
	return m_TimeSign[index].m_crdTextPos;
}

TextDir ExcellonData::GetTimeSignDir(int index) const
{
	return m_TimeSign[index].m_iDirection;
}

Coord ExcellonData::GetFiducialPos(long lIndex) const
{
   	ASSERT(lIndex<m_FiducialData.size());
	
	return Coord(m_FiducialData[lIndex].x+m_FiducialOffset[lIndex].x,
		m_FiducialData[lIndex].y+m_FiducialOffset[lIndex].y);
}

HoleCoordV ExcellonData::GetFiducial() const
{
	return m_FiducialData;
}

long ExcellonData::GetFiducialNum() const
{
	return m_FiducialData.size();
}

Coord ExcellonData::GetInnerFiducialPos(long lIndex) const
{
   	ASSERT(lIndex<m_InnerFiducialData.size());
	
	return m_InnerFiducialData[lIndex];
}

HoleCoordV ExcellonData::GetInnerFiducial() const
{
	return m_InnerFiducialData;
}

long ExcellonData::GetInnerFiducialNum() const
{
	return m_InnerFiducialData.size();
}
//---------------------------------------------------------------------------------------------
void ExcellonData::AddFiducialData(const HoleData& crd)
{
	m_FiducialData.push_back(Coord(crd.x,crd.y));
	m_FiducialOffset.push_back(Coord(0,0));
}

void ExcellonData::AddInnerFiducialData(const HoleData& crd)
{
	m_InnerFiducialData.push_back(Coord(crd.x,crd.y));
}

void ExcellonData::AddLocalMarkInfo(const HoleData& crd,int iBlockIndex)
{
	m_FileLayer.m_LocalMarkInfo.m_iBlockIndex=iBlockIndex;
	m_FileLayer.m_LocalMarkInfo.m_LocalMark.push_back(Coord(crd.x,crd.y));
}

void ExcellonData::AddTextInfo(const HoleData& crd,DataMode dmode,CString str,int iBlockIndex)
{
	TextInfo textinfo;
	textinfo.m_iBlockIndex=iBlockIndex;
	textinfo.iToolNum=crd.iToolNo;
	textinfo.m_TextPos=Coord(crd.x,crd.y);
	textinfo.m_textmode=dmode;
	if(STRINGH==dmode||STRINGV==dmode)
	{
		textinfo.m_strText=str;
	}
	m_FileLayer.m_TextInfo.push_back(textinfo);
	
	if(iBlockIndex!=-1)
	{
		if(crd.x<m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iStartX)
			m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iStartX = crd.x;
		if(crd.y<m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iStartY)
			m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iStartY = crd.y;
		
		if(crd.x>m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iEndX)
			m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iEndX = crd.x;
		if(crd.y>m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iEndY)
			m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iEndY = crd.y;
	}
	if(crd.x<m_FileLayer.m_iLayerStartX)
		m_FileLayer.m_iLayerStartX = crd.x;
	if(crd.y<m_FileLayer.m_iLayerStartY)
		m_FileLayer.m_iLayerStartY = crd.y;
	
	if(crd.x>m_FileLayer.m_iLayerEndX)
		m_FileLayer.m_iLayerEndX = crd.x;
	if(crd.y>m_FileLayer.m_iLayerEndY)
		m_FileLayer.m_iLayerEndY = crd.y;
}

void ExcellonData::AddNoBlockDataInfo(const HoleData& crd)
{
	if(crd.x<m_FileLayer.m_ScatteredHole.m_iStartX)
		m_FileLayer.m_ScatteredHole.m_iStartX = crd.x;
	if(crd.y<m_FileLayer.m_ScatteredHole.m_iStartY)
		m_FileLayer.m_ScatteredHole.m_iStartY = crd.y;
	
	if(crd.x>m_FileLayer.m_ScatteredHole.m_iEndX)
		m_FileLayer.m_ScatteredHole.m_iEndX = crd.x;
	if(crd.y>m_FileLayer.m_ScatteredHole.m_iEndY)
		m_FileLayer.m_ScatteredHole.m_iEndY = crd.y;
	
	if(crd.x<m_FileLayer.m_iLayerStartX)
		m_FileLayer.m_iLayerStartX = crd.x;
	if(crd.y<m_FileLayer.m_iLayerStartY)
		m_FileLayer.m_iLayerStartY = crd.y;
	
	if(crd.x>m_FileLayer.m_iLayerEndX)
		m_FileLayer.m_iLayerEndX = crd.x;
	if(crd.y>m_FileLayer.m_iLayerEndY)
		m_FileLayer.m_iLayerEndY = crd.y;
	
	m_FileLayer.m_ScatteredHole.m_NoBlockData.push_back(crd);
}

void ExcellonData::AddBlockData(int iBlockIndex)
{
	m_FileLayer.m_HoleBlockData.push_back(BlockDataInfo());
	m_FileLayer.m_HoleBlockData[m_FileLayer.m_HoleBlockData.size()-1].m_iBlockIndex=iBlockIndex;
}

void ExcellonData::AddBlockDataInfo(const HoleData& crd,int iBlockIndex)//ly mark 20131021
{
	ASSERT(iBlockIndex<m_FileLayer.m_HoleBlockData.size());		//检查块索引号
	
	//	if(!m_FileLayer.m_HoleBlockData[iBlockIndex].m_BlockData.empty())
	//	{
	if(crd.x<m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartX)
		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartX = crd.x;
	if(crd.y<m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartY)
		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartY = crd.y;
	
	if(crd.x>m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndX)
		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndX = crd.x;
	if(crd.y>m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndY)
		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndY = crd.y;
	//	}
	//	else
	//	{
	//		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartX = crd.x;
	//		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartY = crd.y;
	//		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndX = crd.x;
	//		m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndY = crd.y;
	//	}
	
	if(crd.x<m_FileLayer.m_iLayerStartX)
		m_FileLayer.m_iLayerStartX = crd.x;
	if(crd.y<m_FileLayer.m_iLayerStartY)
		m_FileLayer.m_iLayerStartY = crd.y;
	
	if(crd.x>m_FileLayer.m_iLayerEndX)
		m_FileLayer.m_iLayerEndX = crd.x;
	if(crd.y>m_FileLayer.m_iLayerEndY)
		m_FileLayer.m_iLayerEndY = crd.y;
	
	m_FileLayer.m_HoleBlockData[iBlockIndex].m_BlockData.push_back(crd);
}

void ExcellonData::AddToolsInfo(const ToolInfo& tp)
{
	m_FileLayer.m_ToolInfo.push_back(tp);
}

void ExcellonData::AddBlockLinkInfo(const HoleData& crd,int iBlockIndex,int iLinkIndex,MirrorModeV mmode)//ly mark 20131021
{
	//	ASSERT( iBlockIndex<=m_FileLayer.m_LinkInfo.size() );		//检查块索引号
	CRD holex1,holey1,holex2,holey2,holetemp;
	
	if(!m_FileLayer.IsLinked(iBlockIndex))			
	{
		BlockLinkInfo linkinfo;
		linkinfo.m_iBlockIndex = iBlockIndex;
		m_FileLayer.m_LinkInfo.push_back(linkinfo);
	}
	
	int blockindex=m_FileLayer.GetSameLinkIndex(iBlockIndex);						//有M25块不一定就有M02块跟其link
	m_FileLayer.m_LinkInfo[blockindex].m_pSubBlock.push_back(BlockRelation());		//M02块索引与m_pSubBlock数组序号相同
	
	m_FileLayer.m_LinkInfo[blockindex].m_pSubBlock[iLinkIndex].m_iOffsetX=crd.x;
	m_FileLayer.m_LinkInfo[blockindex].m_pSubBlock[iLinkIndex].m_iOffsetY=crd.y;
	m_FileLayer.m_LinkInfo[blockindex].m_pSubBlock[iLinkIndex].m_iMirrorMode=mmode;
	
	if(iLinkIndex==0)
	{
		m_FileLayer.m_iBlockRefX = 0;
		m_FileLayer.m_iBlockRefY = 0;
	}
	
	m_FileLayer.m_iBlockRefX += crd.x;
	m_FileLayer.m_iBlockRefY += crd.y;
	
	holex1=m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartX ;
	holey1=m_FileLayer.m_HoleBlockData[iBlockIndex].m_iStartY ;
	holex2=m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndX ;
	holey2=m_FileLayer.m_HoleBlockData[iBlockIndex].m_iEndY ;
	
	if(!mmode.empty())
	{
		for(int count=0;count<mmode.size();++count)
		{
			switch(mmode[count])
			{
			case 0:
				holex1=-holex1;
				holex2=-holex2;
				break;
			case 1:
				holey1=-holey1;
				holey2=-holey2;
				break;
			case 2:
				holetemp=holex1;
				holex1=holey1;
				holey1=holetemp;
				holetemp=holex2;
				holex2=holey2;
				holey2=holetemp;
				break;
			}
		}
	}
	
	holex1+=m_FileLayer.m_iBlockRefX;
	holey1+=m_FileLayer.m_iBlockRefY;
	holex2+=m_FileLayer.m_iBlockRefX;
	holey2+=m_FileLayer.m_iBlockRefY;
	
	if(holex1<m_FileLayer.m_iLayerStartX)
		m_FileLayer.m_iLayerStartX = holex1;
	if(holey1<m_FileLayer.m_iLayerStartY)
		m_FileLayer.m_iLayerStartY = holey1;
	
	if(holex1>m_FileLayer.m_iLayerEndX)
		m_FileLayer.m_iLayerEndX = holex1;
	if(holey1>m_FileLayer.m_iLayerEndY)
		m_FileLayer.m_iLayerEndY = holey1;
	
	if(holex2<m_FileLayer.m_iLayerStartX)
		m_FileLayer.m_iLayerStartX = holex2;
	if(holey2<m_FileLayer.m_iLayerStartY)
		m_FileLayer.m_iLayerStartY = holey2;
	
	if(holex2>m_FileLayer.m_iLayerEndX)
		m_FileLayer.m_iLayerEndX = holex2;
	if(holey2>m_FileLayer.m_iLayerEndY)
		m_FileLayer.m_iLayerEndY = holey2;
}

bool ExcellonData::MakeAssistantData()
{
	CRD holex,holex1,holex2,holey,holey1,holey2,holetemp,offsetx,offsety,vectorx,vectory;
	std::vector<BlockRelation>::iterator link;
	int linkindex,index,m,n;
	LocalMarkData lmd;
	TextData td;
	
	//生成LocalMark信息
	if(!m_FileLayer.m_LocalMarkInfo.m_LocalMark.empty())
	{
		index=0;
		lmd.m_iIndex=0;
		lmd.m_LocalMarkData=m_FileLayer.m_LocalMarkInfo.m_LocalMark;
		lmd.m_iStartX=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iStartX;		
		lmd.m_iEndX=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iEndX;			
		lmd.m_iStartY=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iStartY;		
		lmd.m_iEndY=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iEndY;
		m_LocalMarkV.push_back(lmd);
		
		linkindex = m_FileLayer.GetSameLinkIndex(m_FileLayer.m_LocalMarkInfo.m_iBlockIndex);
		
		offsetx=0;
		offsety=0;
		
		if(linkindex!=NOLINK)
		{
			for(link = m_FileLayer.m_LinkInfo[linkindex].m_pSubBlock.begin();
			link !=m_FileLayer.m_LinkInfo[linkindex].m_pSubBlock.end();++link)
			{
				index++;
				lmd.m_iIndex=index;
				
				offsetx += link->m_iOffsetX;
				offsety += link->m_iOffsetY;
				
				lmd.m_iStartX=99999999;		
				lmd.m_iEndX=-99999999;			
				lmd.m_iStartY=99999999;		
				lmd.m_iEndY=-99999999;
				
				holex1=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iStartX ;
				holey1=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iStartY ;
				holex2=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iEndX ;
				holey2=m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_iEndY ;
				
				for(n=0;n<m_FileLayer.m_LocalMarkInfo.m_LocalMark.size();++n)
				{
					holex=m_FileLayer.m_LocalMarkInfo.m_LocalMark[n].x;
					holey=m_FileLayer.m_LocalMarkInfo.m_LocalMark[n].y;
					
					if(!link->m_iMirrorMode.empty())
					{
						for(int count=0;count<link->m_iMirrorMode.size();++count)
						{
							switch(link->m_iMirrorMode[count])
							{
							case 0:
								holex=-holex;
								break;
							case 1:
								holey=-holey;
								break;
							case 2:
								holetemp=holex;
								holex=holey;
								holey=holetemp;
								break;
							}
						}
					}
					holex+=offsetx;
					holey+=offsety;
					lmd.m_LocalMarkData[n].x=holex;
					lmd.m_LocalMarkData[n].y=holey;
				}
				
				if(!link->m_iMirrorMode.empty())
				{
					for(int count1=0;count1<link->m_iMirrorMode.size();++count1)
					{
						switch(link->m_iMirrorMode[count1])
						{
						case 0:
							holex1=-holex1;
							holex2=-holex2;
							break;
						case 1:
							holey1=-holey1;
							holey2=-holey2;
							break;
						case 2:
							holetemp=holex1;
							holex1=holey1;
							holey1=holetemp;
							holetemp=holex2;
							holex2=holey2;
							holey2=holetemp;
							break;
						}
					}
				}
				
				holex1+=offsetx;
				holey1+=offsety;
				holex2+=offsetx;
				holey2+=offsety;
				
				if(holex1<lmd.m_iStartX)
					lmd.m_iStartX = holex1;
				if(holey1<lmd.m_iStartY)
					lmd.m_iStartY = holey1;
				
				if(holex1>lmd.m_iEndX)
					lmd.m_iEndX = holex1;
				if(holey1>lmd.m_iEndY)
					lmd.m_iEndY = holey1;
				
				if(holex2<lmd.m_iStartX)
					lmd.m_iStartX = holex2;
				if(holey2<lmd.m_iStartY)
					lmd.m_iStartY = holey2;
				
				if(holex2>lmd.m_iEndX)
					lmd.m_iEndX = holex2;
				if(holey2>lmd.m_iEndY)
					lmd.m_iEndY = holey2;
				
				m_LocalMarkV.push_back(lmd);
			}
		}
	}
	
	//生成字符加工信息
	if(!m_FileLayer.m_TextInfo.empty())
	{
		for(m=0;m<m_FileLayer.m_TextInfo.size();++m)
		{
			td.iToolNo=m_FileLayer.m_TextInfo[m].iToolNum;
			td.m_crdTextPos=m_FileLayer.m_TextInfo[m].m_TextPos;
			
			switch(m_FileLayer.m_TextInfo[m].m_textmode)
			{
			case 1:
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_MachineSign.push_back(td);
				break;
			case 2:
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_DaySign.push_back(td);
				break;
			case 3:
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_TimeSign.push_back(td);
				break;
			case 4:
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_LotIdSign.push_back(td);
				break;
			case 5:
				td.m_strTextData=m_FileLayer.m_TextInfo[m].m_strText;
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_StrTextSign.push_back(td);
				break;
			case 6:
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_MachineSign.push_back(td);
				break;
			case 7:
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_DaySign.push_back(td);
				break;
			case 8:
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_TimeSign.push_back(td);
				break;
			case 9:
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_LotIdSign.push_back(td);
				break;
			case 10:
				td.m_strTextData=m_FileLayer.m_TextInfo[m].m_strText;
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_StrTextSign.push_back(td);
				break;
			case 11://ly add 20121230
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_AxisNoSign.push_back(td);
				break;
			case 12://ly add 20121230
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_AxisNoSign.push_back(td);
				break;
			case 13://ly add 20131104
				td.m_iDirection=HorizontalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_ScaleSign.push_back(td);
				break;
			case 14://ly add 20131104
				td.m_iDirection=VerticalText;
				td.m_TextPosition=LEFTBOTTOM;
				m_ScaleSign.push_back(td);
				break;
			}
			
			linkindex = m_FileLayer.GetSameLinkIndex(m_FileLayer.m_TextInfo[m].m_iBlockIndex);
			offsetx=0;
			offsety=0;
			
			if(linkindex!=NOLINK)
			{
				td.iToolNo=m_FileLayer.m_TextInfo[m].iToolNum;
				
				for(link = m_FileLayer.m_LinkInfo[linkindex].m_pSubBlock.begin();
				link !=m_FileLayer.m_LinkInfo[linkindex].m_pSubBlock.end();++link)
				{
					holex=m_FileLayer.m_TextInfo[m].m_TextPos.x;
					holey=m_FileLayer.m_TextInfo[m].m_TextPos.y;
					
					if(m_FileLayer.m_TextInfo[m].m_textmode<MACHINENOV)
					{
						vectorx=holex+50;
						vectory=holey+20;
					}
					else
					{
						vectorx=holex-20;
						vectory=holey+50;
					}
					
					offsetx += link->m_iOffsetX;
					offsety += link->m_iOffsetY;
					
					if(!link->m_iMirrorMode.empty())
					{
						for(int count=0;count<link->m_iMirrorMode.size();++count)
						{
							switch(link->m_iMirrorMode[count])
							{
							case 0:
								holex=-holex;
								vectorx=-vectorx;
								break;
							case 1:
								holey=-holey;
								vectory=-vectory;
								break;
							case 2:
								holetemp=holex;
								holex=holey;
								holey=holetemp;
								holetemp=vectorx;
								vectorx=vectory;
								vectory=holetemp;
								break;
							}
						}
					}
					
					holex+=offsetx;
					holey+=offsety;
					td.m_crdTextPos.x=holex;
					td.m_crdTextPos.y=holey;
					
					if(td.m_crdTextPos.x<m_FileLayer.m_iLayerStartX)
						m_FileLayer.m_iLayerStartX = td.m_crdTextPos.x;
					if(td.m_crdTextPos.y<m_FileLayer.m_iLayerStartY)
						m_FileLayer.m_iLayerStartY = td.m_crdTextPos.y;
					
					if(td.m_crdTextPos.x>m_FileLayer.m_iLayerEndX)
						m_FileLayer.m_iLayerEndX = td.m_crdTextPos.x;
					if(td.m_crdTextPos.y>m_FileLayer.m_iLayerEndY)
						m_FileLayer.m_iLayerEndY = td.m_crdTextPos.y;
					
					vectorx+=offsetx;
					vectory+=offsety;
					
					switch(m_FileLayer.m_TextInfo[m].m_textmode)
					{
					case 1:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_MachineSign.push_back(td);
						break;
					case 2:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_DaySign.push_back(td);
						break;
					case 3:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_TimeSign.push_back(td);
						break;
					case 4:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_LotIdSign.push_back(td);
						break;
					case 5:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_StrTextSign.push_back(td);
						break;
					case 6:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_MachineSign.push_back(td);
						break;
					case 7:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_DaySign.push_back(td);
						break;
					case 8:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_TimeSign.push_back(td);
						break;
					case 9:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_LotIdSign.push_back(td);
						break;
					case 10:
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_StrTextSign.push_back(td);
						break;
					case 11://ly add 20121230
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_AxisNoSign.push_back(td);
						break;
					case 12://ly add 20121230
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_AxisNoSign.push_back(td);
						break;
					case 13://ly add 20131104
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_ScaleSign.push_back(td);
						break;
					case 14://ly add 20131104
						td.m_iDirection=GetTextDirection(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory);
						td.m_TextPosition=GetTextPositon(td.m_crdTextPos.x,td.m_crdTextPos.y,vectorx,vectory,td.m_iDirection);
						m_ScaleSign.push_back(td);
						break;
					}
				}
			}
		}
	}
	return true;
}

TextDir ExcellonData::GetTextDirection(CRD posx,CRD posy,CRD vx,CRD vy)
{
	if(labs(vx-posx)>labs(vy-posy))
	{
		return HorizontalText;
	}
	else
	{
		return VerticalText;
	}
}

TextPosition ExcellonData::GetTextPositon(CRD posx,CRD posy,CRD vx,CRD vy,TextDir dir)
{
	if(HorizontalText==dir)
	{
		if(vx>posx&&vy>posy)
			return LEFTBOTTOM;
		if(vx<posx&&vy>posy)
			return RIGHTBOTTOM;
		if(vx<posx&&vy<posy)
			return RIGHTTOP;
		if(vx>posx&&vy<posy)
			return LEFTTOP;
	}
	
	if(VerticalText==dir)
	{
		if(vx>posx&&vy>posy)
			return LEFTTOP;
		if(vx<posx&&vy>posy)
			return LEFTBOTTOM;
		if(vx<posx&&vy<posy)
			return RIGHTBOTTOM;
		if(vx>posx&&vy<posy)
			return RIGHTTOP;
	}		
}

//---------------------------------------------------------------------------------------------------

void ExcellonData::SortSubArea(SubAreaV& sav,int nSaIndex)
{
	ASSERT(nSaIndex<sav.size());
	
	std::vector<Coord>::iterator ithole;
	std::vector<Coord>::iterator itholeT1;
	std::vector<Coord>::iterator itholeT2;
	std::vector<HoleClass>::iterator hcv;
	
	double xt1,xt2;
	bool breverse =false;
	
	std::vector<SubArea>::iterator itsa;
	
	for( hcv=sav[nSaIndex].hcvHoleData.begin(); hcv!=sav[nSaIndex].hcvHoleData.end();hcv++)
	{
		std::sort( hcv->hcvHolePos.begin(),hcv->hcvHolePos.end() );
		
        hcv->hcvHolePos.push_back(Coord(99999,99999)); 
		itholeT1=hcv->hcvHolePos.begin();
		itholeT2=hcv->hcvHolePos.begin();
        
		xt1 = itholeT1->x;
		xt2 = itholeT1->x;
		
		int nNum=0;
		for(ithole=hcv->hcvHolePos.begin();ithole!=hcv->hcvHolePos.end();++ithole)
		{
			if(xt1==ithole->x)
			{
				nNum++;	
				continue;
			}
			else
			{
				if(breverse)
				{
					std::reverse(ithole-nNum,ithole);
					nNum=1;
				}
				else
				{
					nNum=1;
				}
				xt1=ithole->x;
				breverse= breverse?false:true;
			}
		}
		hcv->hcvHolePos.pop_back();
	}
}

void ExcellonData::SortFiducialData()
{
	Coord crd=Coord();
	int where[4];
	char ez[256]={""};//ly 20110404
	
	for(int p=0; p<GetFiducialNum(); ++p)
	{
		crd+=GetFiducialPos(p);
	}
	
	crd=crd/GetFiducialNum();
	
	if(m_FiducialData.size()==4||m_FiducialData.size()==3)
	{
		for(int m=0; m<GetFiducialNum(); ++m)
        {
			if(m_FiducialData[m].x>=crd.x)
			{
				if(m_FiducialData[m].y>=crd.y)
				{
					where[m]=2;
				}
				else
				{
					where[m]=3;
				}
			}
			else
			{
				if(m_FiducialData[m].y>=crd.y)
				{
					where[m]=1;
				}
				else
				{
					where[m]=0;
				}		      
			}
		}
		
		for(int i=0;i<GetFiducialNum()-1;i++)
		{
			for(int j=i+1;j<GetFiducialNum();j++)
			{	
				if(where[j]<where[i])
				{
					std::swap(where[j],where[i]);
					std::swap(m_FiducialData[j],m_FiducialData[i]);
				}
			}
		}
	}
	else
	{
		strncpy(ez,GetLang().GetWarningText(22001),256);
		AfxMessageBox(ez);//"主标靶数量不对，请确认!"
	}
}

void ExcellonData::SortInnerFiducialData()
{
	std::sort(m_InnerFiducialData.begin(),m_InnerFiducialData.end());
	
	if(m_InnerFiducialData.size()==4)
	{
		for(int n=0; n<4; ++n)
        {
			if(m_InnerFiducialData[n].x>=GetInnerLayerCenter().x)
			{
				if(m_InnerFiducialData[n].y>=GetInnerLayerCenter().y)
				{
					std::swap(m_InnerFiducialData[n],m_InnerFiducialData[2]);
				}
				else
				{
					std::swap(m_InnerFiducialData[n],m_InnerFiducialData[3]);
				}
			}
			else
			{
				if(m_InnerFiducialData[n].y>=GetInnerLayerCenter().y)
				{
					std::swap(m_InnerFiducialData[n],m_InnerFiducialData[1]);
				}
				else
				{
					std::swap(m_InnerFiducialData[n],m_InnerFiducialData[0]);
				}
				
			}
		}
	}
	else if(m_InnerFiducialData.size()==2)
	{
		if(m_InnerFiducialData[0].x>=GetInnerLayerCenter().x)
		{
			std::swap(m_InnerFiducialData[0],m_InnerFiducialData[1]);
		}		
	}
	else if(m_InnerFiducialData.size()==6)
	{
		for(int i=0;i<m_InnerFiducialData.size();i++)
		{
			for(int j=i+1;j<m_InnerFiducialData.size();j++)	
			{
				if(m_InnerFiducialData[i].y>m_InnerFiducialData[j].y)
				{
					std::swap(m_InnerFiducialData[i],m_InnerFiducialData[j]);
				}
			}
		}

		for(int k=0;k<m_InnerFiducialData.size();k+=2)
		{
			if(m_InnerFiducialData[k].x>m_InnerFiducialData[k+1].x)
				std::swap(m_InnerFiducialData[k],m_InnerFiducialData[k+1]);
		}

		for(int m=0;m<m_InnerFiducialData.size();m++)
		{
			Coord crd = m_InnerFiducialData[m];
		}
	}
	else
	{
		char ez[256]={""};//ly 20110404
		strncpy(ez,GetLang().GetWarningText(22002),256);
		AfxMessageBox(ez);//"内层(或者内部)标靶数量不对，请确认!"
	}
}

void ExcellonData::SortLocalMarkData()
{
	for(int index=0;index<m_LocalMarkV.size();++index)
	{
		std::sort(m_LocalMarkV[index].m_LocalMarkData.begin(),m_LocalMarkV[index].m_LocalMarkData.end());
		
		if(m_LocalMarkV[index].m_LocalMarkData.size()==4)
		{
			for(int n=0; n<4; ++n)
			{
				if(m_LocalMarkV[index].m_LocalMarkData[n].x>=GetLocalAreaCenter(index).x)
				{
					if(m_LocalMarkV[index].m_LocalMarkData[n].y>=GetLocalAreaCenter(index).y)
					{
						std::swap(m_LocalMarkV[index].m_LocalMarkData[n],m_LocalMarkV[index].m_LocalMarkData[2]);
					}
					else
					{
						std::swap(m_LocalMarkV[index].m_LocalMarkData[n],m_LocalMarkV[index].m_LocalMarkData[3]);
					}
				}
				else
				{
					if(m_LocalMarkV[index].m_LocalMarkData[n].y>=GetLocalAreaCenter(index).y)
					{
						std::swap(m_LocalMarkV[index].m_LocalMarkData[n],m_LocalMarkV[index].m_LocalMarkData[1]);
					}
					else
					{
						std::swap(m_LocalMarkV[index].m_LocalMarkData[n],m_LocalMarkV[index].m_LocalMarkData[0]);
					}
					
				}
			}
		}
		else
		{
			char ez[256]={""};//ly 20110404
			strncpy(ez,GetLang().GetWarningText(22003),256);
			AfxMessageBox(ez);//"局部标靶数量不对，请确认!"
		}	
	}
}

BOOL ExcellonData::SortSALocalMarkData()
{	
	for(int index=0;index<m_SALocalMarkV.size();++index)
	{
		std::sort(m_SALocalMarkV[index].m_LocalMarkData.begin(),m_SALocalMarkV[index].m_LocalMarkData.end());
		
		if(m_SALocalMarkV[index].m_LocalMarkData.size()==4)
		{
			for(int n=0; n<4; ++n)
			{
				if(m_SALocalMarkV[index].m_LocalMarkData[n].x>=GetSALocalAreaCenter(index).x)
				{
					if(m_SALocalMarkV[index].m_LocalMarkData[n].y>=GetSALocalAreaCenter(index).y)
					{
						std::swap(m_SALocalMarkV[index].m_LocalMarkData[n],m_SALocalMarkV[index].m_LocalMarkData[2]);
					}
					else
					{
						std::swap(m_SALocalMarkV[index].m_LocalMarkData[n],m_SALocalMarkV[index].m_LocalMarkData[3]);
					}
				}
				else
				{
					if(m_SALocalMarkV[index].m_LocalMarkData[n].y>=GetSALocalAreaCenter(index).y)
					{
						std::swap(m_SALocalMarkV[index].m_LocalMarkData[n],m_SALocalMarkV[index].m_LocalMarkData[1]);
					}
					else
					{
						std::swap(m_SALocalMarkV[index].m_LocalMarkData[n],m_SALocalMarkV[index].m_LocalMarkData[0]);
					}
					
				}
			}
		}
		else
		{
			char ez[256]={""};//ly 20110404
			strncpy(ez,GetLang().GetWarningText(22003),256);
			AfxMessageBox(ez);//"局部标靶数量不对，请确认!"
			return false;
		}	
	}

	return true;
}

void ExcellonData::SetLayerEndY(CRD temp) //ly add for sa rotate 20140318
{
	m_FileLayer.m_iLayerEndY=temp;
}

void ExcellonData::SetLayerEndX(CRD temp) 
{
	m_FileLayer.m_iLayerEndX=temp;
}

void ExcellonData::SetLayerStartY(CRD temp) 
{
	m_FileLayer.m_iLayerStartY=temp;
}

void ExcellonData::SetLayerStartX(CRD temp) 
{
	m_FileLayer.m_iLayerStartX =temp;
}

CRD ExcellonData::GetLayerStartX()const
{
	return m_FileLayer.m_iLayerStartX;
}

CRD ExcellonData::GetLayerStartY()const
{	
	return m_FileLayer.m_iLayerStartY;
}

CRD ExcellonData::GetLayerEndX() const
{	
	return m_FileLayer.m_iLayerEndX;
}

CRD ExcellonData::GetLayerEndY() const
{
	return m_FileLayer.m_iLayerEndY;	
}

Coord ExcellonData::GetLayerCenter() const
{
    Coord crd=Coord();
	
	for(int n=0; n<GetFiducialNum(); ++n)
	{
		crd+=GetFiducialPos(n);
	}

	crd=crd/GetFiducialNum();
	
	return crd;
}

Coord ExcellonData::GetInnerLayerCenter() const
{
    Coord crd=Coord();
	
	for(int n=0; n<GetInnerFiducialNum(); ++n)
	{
		crd+=GetInnerFiducialPos(n);
	}

	crd=crd/GetInnerFiducialNum();
	
	return crd;
}

void ExcellonData::CheckFileRange()//ly add 20131225
{
	if(abs(m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX)<1)
	{
		m_FileLayer.m_iLayerEndX = m_FileLayer.m_iLayerStartX+1;
	}
	if(abs(m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY)<1)
	{
		m_FileLayer.m_iLayerEndY = m_FileLayer.m_iLayerStartY+1;
	}
}

CRD ExcellonData::GetLayerWidth() const
{
	return abs(m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX);	
}

CRD ExcellonData::GetLayerHeight() const
{
	return abs(m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY);
}

BOOL ExcellonData::CompareXAndY()
{
	long	iWidth = m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX;
	long	iLength = m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY;
	if (iWidth<=iLength)
		return FALSE;
	else
		return TRUE;
}

//需增加此功能：当文件尺寸超过台面大小时，分析一下是否可以旋转90后放置，如果可以，正常导入后旋转一下
long ExcellonData::DistrbuteSubArea(int lScanSize,double dbScale,BOOL isJudgeFileLimits)
{
	ASSERT(lScanSize>=25000&&lScanSize<=75000);
	RECT rect;
	HoleData hole;
	CRD offsetx,offsety;
	int n,LinkIndex,iWidth,iLength;
	CRD holex,holey,holetemp;
	AreaHoleData ahd;
	AreaHoleV ah;
	
	std::vector<HoleData>::iterator w;
	std::vector<BlockRelation>::iterator link;
	
	//	if(!ah.empty())
	//		ah.clear();//...............
	
	ClearSubArea();
	//	ClearOtherSubArea();
	
	iWidth = m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX;
	iLength = m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY;
	
	if (isJudgeFileLimits)
	{	
		if(iWidth>GetDoc().GetTableWidth()*1000)
			return FileWidthOutRange;
		if (iLength>GetDoc().GetTableHeight()*1000)
			return FileHeightOutRange;
	}
	
	m_iSubAreaRow = iWidth /(lScanSize) +(iWidth %(lScanSize)==0?0:1);
	m_iSubAreaCol = iLength/(lScanSize) +(iLength%(lScanSize)==0?0:1);
	
	for( n=0; n<m_FileLayer.m_HoleBlockData.size(); ++n)
	{
		LinkIndex = m_FileLayer.GetSameLinkIndex(n);
		
        for(w = m_FileLayer.m_HoleBlockData[n].m_BlockData.begin();
		w != m_FileLayer.m_HoleBlockData[n].m_BlockData.end(); w++)
		{
			hole = *w;
			
			ahd.x=hole.x;
			ahd.y=hole.y;
			ahd.iToolNo=hole.iToolNo;
			ahd.bSubarea=false;
			ah.push_back(ahd);
			
			offsetx=0;
			offsety=0;
			
			if(LinkIndex!=NOLINK)
			{
				for(link = m_FileLayer.m_LinkInfo[LinkIndex].m_pSubBlock.begin();
				link !=m_FileLayer.m_LinkInfo[LinkIndex].m_pSubBlock.end();++link)
				{
					holex=hole.x;
					holey=hole.y;
					
					if(!link->m_iMirrorMode.empty())
					{
						for(int count=0;count<link->m_iMirrorMode.size();++count)
						{
							switch(link->m_iMirrorMode[count])
							{
							case 0:
								holex=-holex;
								break;
							case 1:
								holey=-holey;
								break;
							case 2:
								holetemp=holex;
								holex=holey;
								holey=holetemp;
								break;
							}
						}
					}
					
					offsetx += link->m_iOffsetX;
					offsety += link->m_iOffsetY;
					holex+=offsetx;
					holey+=offsety;
					
					ahd.x=holex;
					ahd.y=holey;
					ahd.iToolNo=hole.iToolNo;
					ahd.bSubarea=false;
					ah.push_back(ahd);
				}
			}	
		}
	}
	
	for( n=0; n<m_FileLayer.m_ScatteredHole.m_NoBlockData.size(); ++n)
	{
		hole = m_FileLayer.m_ScatteredHole.m_NoBlockData[n];
		
		ahd.x=hole.x;
		ahd.y=hole.y;
		ahd.iToolNo=hole.iToolNo;
		ahd.bSubarea=false;
		ah.push_back(ahd);
	}
	
	rect.left=m_FileLayer.m_iLayerStartX;
	rect.bottom=m_FileLayer.m_iLayerStartY;
	rect.right=m_FileLayer.m_iLayerEndX;
	rect.top=m_FileLayer.m_iLayerEndY;
	
	DynamicSubArea(lScanSize,dbScale,ah,rect,m_SubArea);
		
	SortSubArea(m_SubArea);

	SortFiducialData();
	
	if(m_InnerFiducialData.size()>0)
	{
		SortInnerFiducialData();
	}
	
	if(m_LocalMarkV.size()>0)
	{
		DistrbuteLocalMarkSubArea(lScanSize,dbScale);
	}
	
	return FileReadSuccess;
}

long ExcellonData::DistrbuteSubAreaRotReverse()
{
	int iLength,iWidth;

	iWidth = m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY;
	iLength = m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX; 
	
	if(iWidth>GetDoc().GetTableWidth()*1000)
		return FileWidthOutRange;
	if (iLength>GetDoc().GetTableHeight()*1000)
		return FileHeightOutRange;

    Rotate90();
	
	return FileReadSuccess;
}

long ExcellonData::DistrbuteLocalMarkSubArea(int lScanSize,double dbScale)
{
	ASSERT(lScanSize>=25000&&lScanSize<=75000);
	
	RECT rect;
	HoleData hole;
	CRD offsetx,offsety;
	int n,index,LinkIndex;
	CRD holex,holey,holetemp;
	AreaHoleData ahd;
	AreaHoleV ah;
	char ez[256]={""};//ly 20110404
	
	std::vector<HoleData>::iterator w;
	std::vector<BlockRelation>::iterator link;
	
	ClearLocalMarkSubArea();
	
	if(m_FileLayer.m_LocalMarkInfo.m_iBlockIndex!=0)
	{
		strncpy(ez,GetLang().GetWarningText(22004),256);
		AfxMessageBox(ez);//"M02局部标靶功能只对第1个M25块有效，局部标靶分区失败!"
		m_LocalMarkV.clear();
		return 1;
	}
	
	LinkIndex =m_FileLayer.GetSameLinkIndex(m_FileLayer.m_LocalMarkInfo.m_iBlockIndex);
	
	if(LinkIndex==NOLINK)
	{
		strncpy(ez,GetLang().GetWarningText(22005),256);
		AfxMessageBox(ez);//"没有发现M02功能块，局部标靶分区失败!"
		m_LocalMarkV.clear();
		return 1;
	}
	
	index=0;
	
	for(w = m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_BlockData.begin();
	w != m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_BlockData.end(); w++)
	{
		hole = *w;
		
		ahd.x=hole.x;
		ahd.y=hole.y;
		ahd.iToolNo=hole.iToolNo;
		ahd.bSubarea=false;
		ah.push_back(ahd);
	}
	
	m_LocalMarkSubArea.push_back(LocalMarkSubArea());
	
	rect.left=m_LocalMarkV[index].m_iStartX;
	rect.bottom=m_LocalMarkV[index].m_iStartY;
	rect.right=m_LocalMarkV[index].m_iEndX;
	rect.top=m_LocalMarkV[index].m_iEndY;
	
	DynamicSubArea(lScanSize,dbScale,ah,rect,m_LocalMarkSubArea[index].m_LocalMarkSA);			//原始块分区
	
	offsetx = 0;
	offsety = 0;
	
	for(link = m_FileLayer.m_LinkInfo[LinkIndex].m_pSubBlock.begin();
	link !=m_FileLayer.m_LinkInfo[LinkIndex].m_pSubBlock.end();++link)
	{
		index++;
		ah.clear();
		
		offsetx += link->m_iOffsetX;
		offsety += link->m_iOffsetY;
		
		for(w = m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_BlockData.begin();
		w != m_FileLayer.m_HoleBlockData[m_FileLayer.m_LocalMarkInfo.m_iBlockIndex].m_BlockData.end(); w++)
		{
			hole = *w;
			holex=hole.x;
			holey=hole.y;
			
			if(!link->m_iMirrorMode.empty())
			{
				for(int count=0;count<link->m_iMirrorMode.size();++count)
				{
					switch(link->m_iMirrorMode[count])
					{
					case 0:
						holex=-holex;
						break;
					case 1:
						holey=-holey;
						break;
					case 2:
						holetemp=holex;
						holex=holey;
						holey=holetemp;
						break;
					}
				}
			}
			
			holex+=offsetx;
			holey+=offsety;
			
			ahd.x=holex;
			ahd.y=holey;
			ahd.iToolNo=hole.iToolNo;
			ahd.bSubarea=false;
			ah.push_back(ahd);
		}
		
		m_LocalMarkSubArea.push_back(LocalMarkSubArea());
		
		rect.left=m_LocalMarkV[index].m_iStartX;
		rect.bottom=m_LocalMarkV[index].m_iStartY;
		rect.right=m_LocalMarkV[index].m_iEndX;
		rect.top=m_LocalMarkV[index].m_iEndY;
		
		DynamicSubArea(lScanSize,dbScale,ah,rect,m_LocalMarkSubArea[index].m_LocalMarkSA);		//Link块分区
	}
	
	for(int index1=0;index1<m_LocalMarkV.size();++index1)
	{
		SortSubArea(m_LocalMarkSubArea[index1].m_LocalMarkSA);		
	}
	
	SortLocalMarkData();
	
	DistrbuteOtherSubArea(lScanSize,dbScale);
	
	return FileReadSuccess;				
}

long ExcellonData::DistrbuteOtherSubArea(int lScanSize,double dbScale)
{
	ASSERT(lScanSize>=25000&&lScanSize<=75000);
	
	RECT rect;
	HoleData hole;
	CRD offsetx,offsety;
	int n,LinkIndex;
	CRD holex,holey,holetemp;
	AreaHoleData ahd;
	AreaHoleV ah;
	
	std::vector<HoleData>::iterator w;
	std::vector<BlockRelation>::iterator link;
	
	ClearOtherSubArea();
	
	for( n=0; n<m_FileLayer.m_HoleBlockData.size(); ++n)
	{
		if(n==m_FileLayer.m_LocalMarkInfo.m_iBlockIndex)
			continue;
		
		LinkIndex = m_FileLayer.GetSameLinkIndex(n);
		
        for(w = m_FileLayer.m_HoleBlockData[n].m_BlockData.begin();
		w != m_FileLayer.m_HoleBlockData[n].m_BlockData.end(); w++)
		{
			hole = *w;
			
			ahd.x=hole.x;
			ahd.y=hole.y;
			ahd.iToolNo=hole.iToolNo;
			ahd.bSubarea=false;
			ah.push_back(ahd);
			
			offsetx=0;
			offsety=0;
			
			if(LinkIndex!=NOLINK)
			{
				for(link = m_FileLayer.m_LinkInfo[LinkIndex].m_pSubBlock.begin();
				link !=m_FileLayer.m_LinkInfo[LinkIndex].m_pSubBlock.end();++link)
				{
					holex=hole.x;
					holey=hole.y;
					
					if(!link->m_iMirrorMode.empty())
					{
						for(int count=0;count<link->m_iMirrorMode.size();++count)
						{
							switch(link->m_iMirrorMode[count])
							{
							case 0:
								holex=-holex;
								break;
							case 1:
								holey=-holey;
								break;
							case 2:
								holetemp=holex;
								holex=holey;
								holey=holetemp;
								break;
							}
						}
					}
					
					offsetx += link->m_iOffsetX;
					offsety += link->m_iOffsetY;
					holex+=offsetx;
					holey+=offsety;
					
					ahd.x=holex;
					ahd.y=holey;
					ahd.iToolNo=hole.iToolNo;
					ahd.bSubarea=false;
					ah.push_back(ahd);
				}
			}	
		}
	}
	
	for( n=0; n<m_FileLayer.m_ScatteredHole.m_NoBlockData.size(); ++n)
	{
		hole = m_FileLayer.m_ScatteredHole.m_NoBlockData[n];
		
		ahd.x=hole.x;
		ahd.y=hole.y;
		ahd.iToolNo=hole.iToolNo;
		ahd.bSubarea=false;
		ah.push_back(ahd);
	}
	
	rect.left=m_FileLayer.m_iLayerStartX;
	rect.bottom=m_FileLayer.m_iLayerStartY;
	rect.right=m_FileLayer.m_iLayerEndX;
	rect.top=m_FileLayer.m_iLayerEndY;
	
	DynamicSubArea(lScanSize,dbScale,ah,rect,m_OtherSubArea);
	
	SortSubArea(m_OtherSubArea);
	
	return FileReadSuccess;
}
/*
void ExcellonData::OptimizePath(SubAreaV& sav)
{
	// 	std::vector<HoleData>::iterator hd;  
	std::vector<SubArea>::iterator sa;
	std::vector<HoleClass>::iterator hc;  
	SubAreaV savDest=sav;
	
	//	std::vector<Coord>::iterator cdi,cd1,cd2,cdmin;
	//	std::vector<Coord>::iterator cdj;
	//  int lAreaIndex=0;
	
	Coord crd,crd1;
	double dbDist;
	long lDistMin,lPos0,lPos;
	
	double DistA=0.0,DistB=0.0;
	CString InforStr;
	
	for(sa = savDest.begin();sa != savDest.end();++sa)
	{
		for(hc = sa->hcvHoleData.begin();hc != sa->hcvHoleData.end();++hc)
		{
			for( int p=0;p<hc->hcvHolePos.size()-1;++p)
			{  		  
				crd = hc->hcvHolePos[p];
				crd1 = hc->hcvHolePos[p+1];
				DistB += sqrt(pow(crd1.x-crd.x,2)+pow(crd1.y-crd.y,2))/1000.0;
			}
		}
	}
	
	//	InforStr.Format("优化前路径长度为%fmm.",DistB);				
	//	AfxMessageBox(InforStr);
	
	for(int nIndex=0;nIndex<savDest.size();++nIndex)
		SortSubArea(savDest,nIndex);
	
	for(sa = savDest.begin();sa != savDest.end();++sa)
	{
		//      long ln =0;
		//		lAreaIndex++;
		
		for(hc = sa->hcvHoleData.begin();hc != sa->hcvHoleData.end();++hc)
		{
			//			Coord crd = *hc->hcvHolePos.begin();
			//			long lPos,curPos,i=0,j=2;
			//			Coord crd1,crdmin;			
			//          double dbDist;
			//			ln ++;

            for( int i=0;i<hc->hcvHolePos.size()-1;++i)
			{  		  
				//				int size = hc->hcvHolePos.size();
				//				long lIndex = i+1;
				//              long lDist,lDistMin=9999999999;
				
				lDistMin=9999999999;
				crd = hc->hcvHolePos[i];
				
				for( int j=i+1;j<hc->hcvHolePos.size();++j)
				{
					crd1 = hc->hcvHolePos[j];
					dbDist = (pow(crd1.x-crd.x,2)+pow(crd1.y-crd.y,2))/1000.0;
					
					if(dbDist<lDistMin)
					{
						//						crdmin=crd1;
						lDistMin = dbDist;
						lPos = j;
					}
				}
				std::swap(hc->hcvHolePos[i+1],hc->hcvHolePos[lPos]);
			}
			
			for( int n=0;n<hc->hcvHolePos.size()-1;++n)
			{  		  
				crd = hc->hcvHolePos[n];
				crd1 = hc->hcvHolePos[n+1];
				DistA += sqrt(pow(crd1.x-crd.x,2)+pow(crd1.y-crd.y,2))/1000.0;
			}
		}
	}
	
	//	InforStr.Format("优化后路径长度为%fmm.",DistA);				
	//	AfxMessageBox(InforStr);
	if(DistA<DistB)
	{
		sav=savDest;		
	}
}
*/

#ifdef MATRIXPATHTEST

void ExcellonData::OptimizePath(SubAreaV& sav)								//20200330 MatrixOptimizePath
{
	SubAreaV savDest=sav;

	for(int nIndex=0;nIndex<savDest.size();++nIndex)
		SortSubArea(savDest,nIndex);

	sav=savDest;
}

#else

void ExcellonData::OptimizePath(SubAreaV& sav)								//20190820 改写
{
	std::vector<SubArea>::iterator sa;
	std::vector<HoleClass>::iterator hc;
	SubAreaV savDest=sav;
	
	Coord crd,crd1;
	double dbDist;
	long lDistMin,lPos;
	
	double DistA=0.0,DistB=0.0;
	CString InforStr;
	
	for(sa = savDest.begin();sa != savDest.end();++sa)
	{
		for(hc = sa->hcvHoleData.begin();hc != sa->hcvHoleData.end();++hc)
		{
			for( int p=0;p<hc->hcvHolePos.size()-1;++p)
			{  		  
				crd = hc->hcvHolePos[p];
				crd1 = hc->hcvHolePos[p+1];
				DistB += sqrt(pow(crd1.x-crd.x,2)+pow(crd1.y-crd.y,2))/1000.0;
			}
		}
	}
	
//	InforStr.Format("优化前路径长度为%fmm.",DistB);				
//	AfxMessageBox(InforStr);
	
	for(int nIndex=0;nIndex<savDest.size();++nIndex)
		SortSubArea(savDest,nIndex);

//-------------------------------------------------------------------------------

	HANDLE hThreads[4];													//最多4个线程
	ThreadParams params[4];

	int threadCount=savDest.size();										//20200422
	if(threadCount>4)
		threadCount=4;

//	for(int index=0;index<4;index++)
	for(int index=0;index<threadCount;index++)
	{
		params[index].sav=&savDest;
		params[index].nIndex=index;
		params[index].nThreadCount=threadCount;

		hThreads[index]=CreateThread(NULL,0,StartAddress,&params[index],0,NULL);
	}

	WaitForMultipleObjects(threadCount,hThreads,true,INFINITE);			//20200422

	for(int index1=0;index1<threadCount;index1++)
	{
		CloseHandle(hThreads[index1]);
	}

//--------------------------------------------------------------------------------------
	for(sa = savDest.begin();sa != savDest.end();++sa)
	{
		for(hc = sa->hcvHoleData.begin();hc != sa->hcvHoleData.end();++hc)
		{		
			for( int n=0;n<hc->hcvHolePos.size()-1;++n)
			{  		  
				crd = hc->hcvHolePos[n];
				crd1 = hc->hcvHolePos[n+1];
				DistA += sqrt(pow(crd1.x-crd.x,2)+pow(crd1.y-crd.y,2))/1000.0;
			}
		}
	}
	
//	InforStr.Format("优化后路径长度为%fmm.",DistA);				
//	AfxMessageBox(InforStr);

	if(DistA<DistB)
		sav=savDest;		
}

#endif

DWORD WINAPI StartAddress(LPVOID lpParameter)
{
	ThreadParams* params=(ThreadParams*)lpParameter;

	int start,offset;
/*
	int count=params->sav->size()%4;
	if(count!=0)
	{
		count=params->sav->size()/4+1;
		start=params->nIndex*count;
		offset=(params->nIndex+1)*count;
		if(params->nIndex==3)
			offset=params->sav->size();
	}
	else
	{
		count=params->sav->size()/4;
		start=params->nIndex*count;
		offset=(params->nIndex+1)*count;
	}
*/
	int threadCount=params->nThreadCount;								//20200422
	int count=params->sav->size()/threadCount;
//	if(params->sav->size()%threadCount!=0)
//		count++;

	start=params->nIndex*count;
	offset=(params->nIndex+1)*count;
	if(params->nIndex==(threadCount-1))
		offset=params->sav->size();

	std::vector<SubArea>::iterator sa;
	std::vector<HoleClass>::iterator hc;
	
	Coord crd,crd1;
	double dbDist;
	long lDistMin,lPos;

	for(sa = (params->sav->begin()+start);sa <(params->sav->begin()+offset);++sa)
	{
		for(hc = sa->hcvHoleData.begin();hc != sa->hcvHoleData.end();++hc)
		{
            for( int i=0;i<hc->hcvHolePos.size()-1;++i)
			{			
				lDistMin=9999999999;
				crd = hc->hcvHolePos[i];
				
				for( int j=i+1;j<hc->hcvHolePos.size();++j)
				{
					crd1 = hc->hcvHolePos[j];
					dbDist = (pow(crd1.x-crd.x,2)+pow(crd1.y-crd.y,2))/1000.0;
					
					if(dbDist<lDistMin)
					{
						lDistMin = dbDist;
						lPos = j;
					}
				}

				std::swap(hc->hcvHolePos[i+1],hc->hcvHolePos[lPos]);
			}
		}
	}

	return 0;
}
//清除只分区中的数据
void ExcellonData::ClearSubArea()
{
	if(!m_SubArea.empty())
	{
		for(int i=0; i<m_SubArea.size(); ++i)
		{
			if(!m_SubArea[i].hcvHoleData.empty())
			{
				m_SubArea[i].hcvHoleData.clear();
			}
		}
	}
	m_SubArea.clear();
}

void ExcellonData::ClearOtherSubArea()
{
	if(!m_OtherSubArea.empty())
	{
		for(int i=0; i<m_OtherSubArea.size(); ++i)
		{
			if(!m_OtherSubArea[i].hcvHoleData.empty())
			{
				m_OtherSubArea[i].hcvHoleData.clear();
			}
		}
	}
	m_OtherSubArea.clear();
}

//清除所有的数据
void ExcellonData::ClearAll()
{
	std::vector<BlockDataInfo>::iterator bi;
	std::vector<BlockLinkInfo>::iterator li;
	std::vector<BlockRelation>::iterator ri;
	std::vector<LocalMarkData>::iterator mi;
	
	for( bi=m_FileLayer.m_HoleBlockData.begin();bi!=m_FileLayer.m_HoleBlockData.end();++bi)
	{
		bi->m_BlockData.clear();
	}
	m_FileLayer.m_HoleBlockData.clear();
	
	for( li=m_FileLayer.m_LinkInfo.begin();li!=m_FileLayer.m_LinkInfo.end();++li)
	{
		for( ri=li->m_pSubBlock.begin();ri!=li->m_pSubBlock.end();++ri)
		{
			ri->m_iMirrorMode.clear();
		}
		li->m_pSubBlock.clear();
	}
	m_FileLayer.m_LinkInfo.clear();
	m_FileLayer.m_ScatteredHole.m_NoBlockData.clear();
	m_FileLayer.m_LocalMarkInfo.m_LocalMark.clear();
	m_FileLayer.m_TextInfo.clear();
	m_FileLayer.m_ToolInfo.clear();
	
	m_FileLayer.m_iLayerStartX = 99999999;	
	m_FileLayer.m_iLayerEndX   =-99999999;	
	m_FileLayer.m_iLayerStartY = 99999999;	
	m_FileLayer.m_iLayerEndY   =-99999999;
	m_FileLayer.m_iBlockRefX=0;
	m_FileLayer.m_iBlockRefY=0;
	
    m_FiducialData.clear();
	m_FiducialOffset.clear();
	m_InnerFiducialData.clear();
	
	m_MachineSign.clear();   	
	m_DaySign.clear();				
	m_TimeSign.clear();					
	m_LotIdSign.clear();
	m_AxisNoSign.clear();//ly add 20121230
	m_ScaleSign.clear();//ly add 20131104
	m_StrTextSign.clear();
	
	for( mi=m_LocalMarkV.begin();mi!=m_LocalMarkV.end();++mi)
	{
		mi->m_LocalMarkData.clear();
	}
	m_LocalMarkV.clear();
	
	for( mi=m_SALocalMarkV.begin();mi!=m_SALocalMarkV.end();++mi)
	{
		mi->m_LocalMarkData.clear();
	}
	m_SALocalMarkV.clear();	
	
	ClearSubArea();
	ClearLocalMarkSubArea();
	ClearOtherSubArea();
	
	m_iSubAreaRow=0;
	m_iSubAreaCol=0;
	m_iGlvScanSize=50;
	m_lGlvScanBit=0;//ly add 20130412
}

BOOL ExcellonData::GetSubAreaIsEmpty(int iSubArea) const
{
	//	ASSERT(iSubArea<m_SubArea.size());	//20150215
	if (iSubArea>=m_SubArea.size())//避免无效区域加工
		return TRUE;
	return m_SubArea[iSubArea].hcvHoleData.empty();
}

long ExcellonData::GetSubAreaCol() const
{
	return m_iSubAreaCol;
}

long ExcellonData::GetSubAreaRow() const
{
	return m_iSubAreaRow;
}
long ExcellonData::GetSubAreaCnt() const
{
	return m_SubArea.size();
}
SubArea& ExcellonData::GetSubAreaData(int nIndex) 
{
	return m_SubArea[nIndex];
}

long ExcellonData::GetSubAreaHoleCount(int iSubAreaNo) //const
{
	std::vector<HoleClass>::iterator hc;
	int nHoleCount =0;
	for(hc= m_SubArea[iSubAreaNo].hcvHoleData.begin();hc!=m_SubArea[iSubAreaNo].hcvHoleData.end();hc++ )
	{
		nHoleCount+= hc->hcvHolePos.size();
		TRACE1("--HoleCnt:%d\n",hc->hcvHolePos.size());
	}
    return nHoleCount;
	//	return m_SubArea[iSubAreaNo].hcvHoleData.size();
}

Coord ExcellonData::GetSubAreaCenter(int iSubAreaNo) const
{
	return m_SubArea[iSubAreaNo].crdCenter;
}

ToolInfo ExcellonData::GetToolInfo(int nToolIndex) const
{	
	return m_FileLayer.m_ToolInfo[nToolIndex];
}

long ExcellonData::GetToolsNum() const
{
	return m_FileLayer.m_ToolInfo.size();
}

BOOL ExcellonData::InSubArea(const HoleData &hole, long lLx, long lTy, long lRx,long lBy,
							 BOOL bInX, BOOL bInY)
{
	if( hole.x >= lLx && hole.y >= lBy)
	{
		if( bInX ? (hole.x<=lRx):(hole.x<lRx) )
		{	
			if(bInY?(hole.y<=lTy):(hole.y<lTy))
			{
				return TRUE;
			}
			else 
				return FALSE;
		}
		else
			return FALSE;
		
	}
	else
		return FALSE;
	
}

Coord ExcellonData::GetLotIDSignPos(int index) const
{	
	return m_LotIdSign[index].m_crdTextPos;
}

TextDir ExcellonData::GetLotIDSignDir(int index) const
{
	return m_LotIdSign[index].m_iDirection;
}

long ExcellonData::GetLotIDSignCount() const
{
	return m_LotIdSign.size();
}

Coord ExcellonData::GetAxisNoSignPos(int index) const//ly add 20121230--------
{	
	return m_AxisNoSign[index].m_crdTextPos;
}

TextDir ExcellonData::GetAxisNoSignDir(int index) const
{
	return m_AxisNoSign[index].m_iDirection;
}

long ExcellonData::GetAxisNoSignCount() const//ly add 20121230--------
{
	return m_AxisNoSign.size();
}

Coord ExcellonData::GetScaleSignPos(int index) const//ly add 20131104--------
{	
	return m_ScaleSign[index].m_crdTextPos;
}

TextDir ExcellonData::GetScaleSignDir(int index) const
{
	return m_ScaleSign[index].m_iDirection;
}

long ExcellonData::GetScaleSignCount() const//ly add 20131104--------
{
	return m_ScaleSign.size();
}

long ExcellonData::GetMachineSignCount()const
{
	return m_MachineSign.size();
}

long ExcellonData::GetDaySignCount()const
{
	return m_DaySign.size();
}

long ExcellonData::GetTimeSignCount()const
{
	return m_TimeSign.size();
}

TextPosition ExcellonData::GetMachineTextPosition(int index) const
{
	return m_MachineSign[index].m_TextPosition;
}

TextPosition ExcellonData::GetDayTextPosition(int index) const
{
	return m_DaySign[index].m_TextPosition;
}

TextPosition ExcellonData::GetTimeTextPosition(int index) const
{
	return m_TimeSign[index].m_TextPosition;
}

TextPosition ExcellonData::GetLotIDTextPosition(int index) const
{
	return m_LotIdSign[index].m_TextPosition;
}

TextPosition ExcellonData::GetAxisNoTextPosition(int index) const//ly add 20121230
{
	return m_AxisNoSign[index].m_TextPosition;
}

TextPosition ExcellonData::GetScaleTextPosition(int index) const//ly add 20131104
{
	return m_ScaleSign[index].m_TextPosition;
}

HoleCoordV	ExcellonData::GetLocalMark(int DataIndex) const
{
	return m_LocalMarkV[DataIndex].m_LocalMarkData;
}

long ExcellonData::GetLocalMarkNum() const
{
	return m_FileLayer.m_LocalMarkInfo.m_LocalMark.size();
}

long ExcellonData::GetLocalMarkDataCount() const
{
	return m_LocalMarkV.size();
}

Coord ExcellonData::GetLocalMarkDataPos(int DataIndex,int PosIndex)
{
	return m_LocalMarkV[DataIndex].m_LocalMarkData[PosIndex];
}

BOOL ExcellonData::GetLocalMarkSubAreaIsEmpty(int nIndex,int iSubArea) const
{
	ASSERT(nIndex<m_LocalMarkSubArea.size());	
	return m_LocalMarkSubArea[nIndex].m_LocalMarkSA[iSubArea].hcvHoleData.empty();
}

BOOL ExcellonData::GetOtherSubAreaIsEmpty(int iSubArea) const
{
	ASSERT(iSubArea<m_OtherSubArea.size());	
	return m_OtherSubArea[iSubArea].hcvHoleData.empty();
}

long ExcellonData::GetLocalMarkSubAreaCnt(int nIndex) const
{
	ASSERT(nIndex<m_LocalMarkSubArea.size());	
	return m_LocalMarkSubArea[nIndex].m_LocalMarkSA.size();
}

long ExcellonData::GetOtherSubAreaCnt() const
{	
	return m_OtherSubArea.size();
}

SubArea& ExcellonData::GetLocalMarkSubAreaData(int nIndex,int iSubArea) 
{
	ASSERT(nIndex<m_LocalMarkSubArea.size());
	return m_LocalMarkSubArea[nIndex].m_LocalMarkSA[iSubArea];
}

SubArea& ExcellonData::GetOtherSubAreaData(int iSubArea)
{
	ASSERT(iSubArea<m_OtherSubArea.size());	
	return m_OtherSubArea[iSubArea];
}

long ExcellonData::GetLocalMarkSubAreaHoleCount(int nIndex,int iSubAreaNo) 
{
	std::vector<HoleClass>::iterator hc;
	int nHoleCount =0;
	for(hc= m_LocalMarkSubArea[nIndex].m_LocalMarkSA[iSubAreaNo].hcvHoleData.begin();hc!=m_LocalMarkSubArea[nIndex].m_LocalMarkSA[iSubAreaNo].hcvHoleData.end();hc++ )
	{
		nHoleCount+= hc->hcvHolePos.size();
		TRACE1("--HoleCnt:%d\n",hc->hcvHolePos.size());
	}
    return nHoleCount;
}

Coord ExcellonData::GetLocalMarkSubAreaCenter(int nIndex,int iSubArea) const
{
	return m_LocalMarkSubArea[nIndex].m_LocalMarkSA[iSubArea].crdCenter;
}

Coord ExcellonData::GetOtherSubAreaCenter(int iSubArea) const
{
	return m_OtherSubArea[iSubArea].crdCenter;
}

void ExcellonData::ClearLocalMarkSubArea()
{
	if(!m_LocalMarkSubArea.empty())
	{
		for(int i=0; i<m_LocalMarkSubArea.size(); ++i)
		{
			if(!m_LocalMarkSubArea[i].m_LocalMarkSA.empty())
			{
				for(int j=0; j<m_LocalMarkSubArea[i].m_LocalMarkSA.size(); ++j)
				{
					if(!m_LocalMarkSubArea[i].m_LocalMarkSA[j].hcvHoleData.empty())
					{
						m_LocalMarkSubArea[i].m_LocalMarkSA[j].hcvHoleData.clear();
					}
				}
			}
			m_LocalMarkSubArea[i].m_LocalMarkSA.clear();
		}
	}
	m_LocalMarkSubArea.clear();
}

Coord ExcellonData::GetLocalAreaCenter(int nIndex)const
{
	ASSERT(nIndex<m_LocalMarkV.size());	
	
	Coord crd=Coord();
	
	for(int n=0;n<GetLocalMark(nIndex).size();++n)
	{
		crd+=m_LocalMarkV[nIndex].m_LocalMarkData[n];			
	}
	crd/=GetLocalMark(nIndex).size();
	
	return crd;
}

SubAreaV& ExcellonData::GetSubArea()
{
	return m_SubArea;
}

SubAreaV& ExcellonData::GetLocalMarkSubArea(int nIndex)
{
	return m_LocalMarkSubArea[nIndex].m_LocalMarkSA;
}

SubAreaV& ExcellonData::GetOtherSubArea()
{
	return m_OtherSubArea;
}

void ExcellonData::MirrorY(CRD& length,CRD& Min)		//沿Y轴镜像
{
	Coord TxtPos;
	Coord FidPos;
	
	Coord crdDest;
	int nCommandCnt=0,m;
	int curSubAreaNo = 0;
	
	CRD MinX = 99999999,MaxX = -99999999;
	CRD lenth;
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			crdDest = GetSubAreaCenter(curSubAreaNo);
			
			if(MinX > crdDest.x)
				MinX = crdDest.x;
			if(MaxX <crdDest.x)
				MaxX = crdDest.x;
		}
	}//得到有点的分区范围
	lenth = MaxX - MinX ;

	if(length==-1)													//20161109
	{
		length=lenth;	
		Min=MinX;	
	}
	else
	{
		lenth=length;
		MinX=Min;
	}

	//日期，机器号等
	if(GetDaySignCount()>0)                      
	{
		for(m = 0; m<GetDaySignCount(); ++m)
		{
			TxtPos = GetDaySignPos(m);
			m_DaySign[m].m_TextPosition=GetMirrorTextPositon(GetDaySignDir(m),GetDayTextPosition(m));
			m_DaySign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	
	if(GetTimeSignCount()>0)
	{
		for(m = 0; m<GetTimeSignCount(); ++m)
		{
			TxtPos = GetTimeSignPos(m);
			m_TimeSign[m].m_TextPosition=GetMirrorTextPositon(GetTimeSignDir(m),GetTimeTextPosition(m));
			m_TimeSign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	
	if(GetMachineSignCount()>0)
	{
		for(m = 0; m<GetMachineSignCount(); ++m)
		{
			TxtPos = GetMachineSignPos(m);
			m_MachineSign[m].m_TextPosition=GetMirrorTextPositon(GetMachineSignDir(m),GetMachineTextPosition(m));
			m_MachineSign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	
	if(GetLotIDSignCount()>0)
	{
		for(m = 0; m<GetLotIDSignCount(); ++m)
		{
			TxtPos=GetLotIDSignPos(m);
			m_LotIdSign[m].m_TextPosition=GetMirrorTextPositon(GetLotIDSignDir(m),GetLotIDTextPosition(m));
			m_LotIdSign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	
	if(GetAxisNoSignCount()>0)//ly add 20121230
	{
		for(m = 0; m<GetAxisNoSignCount(); ++m)
		{
			TxtPos=GetAxisNoSignPos(m);
			m_AxisNoSign[m].m_TextPosition=GetMirrorTextPositon(GetAxisNoSignDir(m),GetAxisNoTextPosition(m));
			m_AxisNoSign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	
	if(GetScaleSignCount()>0)//ly add 20131104
	{
		for(m = 0; m<GetScaleSignCount(); ++m)
		{
			TxtPos=GetScaleSignPos(m);
			m_ScaleSign[m].m_TextPosition=GetMirrorTextPositon(GetScaleSignDir(m),GetScaleTextPosition(m));
			m_ScaleSign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	
	if(GetStrTextSignCount()>0)
	{
		for(m = 0; m<GetStrTextSignCount(); ++m)
		{
			TxtPos=GetStrTextSignPos(m);
			m_StrTextSign[m].m_TextPosition=GetMirrorTextPositon(GetStrTextSignDir(m),GetStrTextPosition(m));
			m_StrTextSign[m].m_crdTextPos.x = lenth - (TxtPos.x-MinX) + MinX;
		}
	}
	//主标靶
	for(int FidIdex=0;FidIdex<GetFiducialNum();FidIdex++)
	{
		FidPos = GetFiducialPos(FidIdex);	
		m_FiducialData[FidIdex].x = lenth - (FidPos.x-MinX) + MinX;
	}
	SortFiducialData();
	
	//整板分区
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		crdDest = GetSubAreaCenter(curSubAreaNo);
		//lenth - crdDest.y;
		SubArea& subarea = GetSubAreaData(curSubAreaNo);
		subarea.crdCenter.x = lenth - (crdDest.x-MinX) + MinX;
		
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			//处理文件头没有刀具信息，而有点的问题
			//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
			if(GetToolsNum()==0)
			{
				
				for(int n=0;n<subarea.hcvHoleData.size();n++)
				{
					int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						//GetExcellonData().GetSubAreaData(curSubAreaNo).
						Holecrd->y = - Holecrd->y;
						nCommandCnt++;
					}					
				}				
			}			
			else
			{		
				for(int it=0;it<GetToolsNum();++it)
				{   
					ToolInfo nToolNo = GetToolInfo(it);
					int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
					if(nSubToolIndex==-1)
						continue;
					
					int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						Holecrd->y = - Holecrd->y;
						nCommandCnt++;
					}
				}			
			}						
		}
	}
	//	SortSubArea(m_SubArea);
	
	if(GetLocalMarkDataCount()>0)
	{
		for(int index=0;index<GetLocalMarkDataCount();index++)
		{
			for(int n=0;n<GetLocalMark(index).size();n++)
			{
				FidPos = GetLocalMarkDataPos(index,n);
				m_LocalMarkV[index].m_LocalMarkData[n].x = lenth - (FidPos.x-MinX) + MinX;
			}
			
			for(curSubAreaNo=0;curSubAreaNo<GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
			{
				crdDest = GetLocalMarkSubAreaCenter(index,curSubAreaNo);
				//lenth - crdDest.y;
				SubArea& subarea = GetLocalMarkSubAreaData(index,curSubAreaNo);
				subarea.crdCenter.x = lenth - (crdDest.x-MinX) + MinX;
				
				if(!GetLocalMarkSubAreaIsEmpty(index,curSubAreaNo)) 
				{
					//处理文件头没有刀具信息，而有点的问题
					//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
					if(GetToolsNum()==0)
					{
						
						for(int n=0;n<subarea.hcvHoleData.size();n++)
						{
							int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								//GetExcellonData().GetSubAreaData(curSubAreaNo).
								Holecrd->y = - Holecrd->y;
								nCommandCnt++;
							}					
						}				
					}			
					else
					{		
						for(int it=0;it<GetToolsNum();++it)
						{   
							ToolInfo nToolNo = GetToolInfo(it);
							int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
							if(nSubToolIndex==-1)
								continue;
							
							int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								Holecrd->y = - Holecrd->y;
								nCommandCnt++;
							}
						}			
					}						
				}
			}
			//	SortSubArea(m_LocalMarkSubArea[index].m_LocalMarkSA);
		}
		
		SortLocalMarkData();
		
		for(curSubAreaNo=0;curSubAreaNo<GetOtherSubAreaCnt();++curSubAreaNo)
		{
			crdDest = GetOtherSubAreaCenter(curSubAreaNo);
			//lenth - crdDest.y;
			SubArea& subarea = GetOtherSubAreaData(curSubAreaNo);
			subarea.crdCenter.x = lenth - (crdDest.x-MinX) + MinX;
			
			if(!GetOtherSubAreaIsEmpty(curSubAreaNo)) 
			{
				//处理文件头没有刀具信息，而有点的问题
				//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
				if(GetToolsNum()==0)
				{
					
					for(int n=0;n<subarea.hcvHoleData.size();n++)
					{
						int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							//GetExcellonData().GetSubAreaData(curSubAreaNo).
							Holecrd->y = - Holecrd->y;
							nCommandCnt++;
						}					
					}				
				}			
				else
				{		
					for(int it=0;it<GetToolsNum();++it)
					{   
						ToolInfo nToolNo = GetToolInfo(it);
						int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
						if(nSubToolIndex==-1)
							continue;
						
						int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							Holecrd->y = - Holecrd->y;
							nCommandCnt++;
						}
					}			
				}						
			}
		}
		//	SortSubArea(m_OtherSubArea);
	}
	
	if(GetSALocalMarkDataCount()>0)
	{
		for(int indexSA=0;indexSA<GetSALocalMarkDataCount();indexSA++)
		{
			for(m=0;m<GetSALocalMark(indexSA).size();m++)
			{
				FidPos = GetSALocalMarkDataPos(indexSA,m);
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].x = lenth - (FidPos.x-MinX) + MinX;
			}
		}
		SortSALocalMarkData();
	}
	
	if(GetInnerFiducialNum()>0)
	{
		for(int nIndex=0;nIndex<GetInnerFiducialNum();nIndex++)
		{
			FidPos = GetInnerFiducialPos(nIndex);	
			m_InnerFiducialData[nIndex].x = lenth - (FidPos.x-MinX) + MinX;
		}
		SortInnerFiducialData();
	}
}

void ExcellonData::Rotate90()		//逆时针90度旋转
{
	Coord TxtPos;
	Coord FidPos;
	Coord crdHole;
	
	double dbDist;
	long lDistMin,lPos0;
	
	Coord crdDest,crdMid,crdOrg;
	int nCommandCnt=0,m;
	int curSubAreaNo = 0;
	
	char ez[256]={""};//ly 20110404
	
	CRD MinX = 99999999,MaxX = -99999999;
	CRD lenth;
	
	int iWidth = m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY;
	int iLength = m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX;
	
	if(iWidth>GetDoc().GetTableWidth()*1000)
	{
		strncpy(ez,GetLang().GetWarningText(11002),256);
		AfxMessageBox(ez);//"数据宽度超出加工范围!"
		return;
	}
	
	if (iLength>GetDoc().GetTableHeight()*1000)
	{
		strncpy(ez,GetLang().GetWarningText(11003),256);
		AfxMessageBox(ez);//"数据高度超出加工范围!"
		return;
	}
	
	crdMid.x=(m_FileLayer.m_iLayerEndX+m_FileLayer.m_iLayerStartX)/2;
	crdMid.y=(m_FileLayer.m_iLayerEndY+m_FileLayer.m_iLayerStartY)/2;
	
	lDistMin=9999999999;
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			crdDest = GetSubAreaCenter(curSubAreaNo);
			dbDist = (pow((crdDest.x-crdMid.x),2)+pow((crdDest.y-crdMid.y),2))/1000.0;
			
			if(dbDist<lDistMin)
			{
				lDistMin = dbDist;
				lPos0 = curSubAreaNo;
			}
		}
	}
	
	crdOrg = GetSubAreaCenter(lPos0);
	
	m_iSubAreaRow = iWidth /GetDoc().GetScanSize()/1000 +(iWidth %(GetDoc().GetScanSize()*1000)==0?0:1);
	m_iSubAreaCol = iLength/GetDoc().GetScanSize()/1000 +(iLength%(GetDoc().GetScanSize()*1000)==0?0:1);
	
	//日期，机器号等
	if(GetDaySignCount()>0)
	{
		for(m = 0; m<GetDaySignCount(); ++m)
		{
			TxtPos = GetDaySignPos(m);
			m_DaySign[m].m_TextPosition=GetRotateTextPositon(GetDaySignDir(m),GetDayTextPosition(m));
			m_DaySign[m].m_iDirection=GetRotateTextDir(GetDaySignDir(m));
			m_DaySign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_DaySign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetTimeSignCount()>0)
	{
		for(m = 0; m<GetTimeSignCount(); ++m)
		{
			TxtPos = GetTimeSignPos(m);
			m_TimeSign[m].m_TextPosition=GetRotateTextPositon(GetTimeSignDir(m),GetTimeTextPosition(m));
			m_TimeSign[m].m_iDirection=GetRotateTextDir(GetTimeSignDir(m));
			m_TimeSign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_TimeSign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetMachineSignCount()>0)
	{
		for(m = 0; m<GetMachineSignCount(); ++m)
		{
			TxtPos = GetMachineSignPos(m);
			m_MachineSign[m].m_TextPosition=GetRotateTextPositon(GetMachineSignDir(m),GetMachineTextPosition(m));
			m_MachineSign[m].m_iDirection=GetRotateTextDir(GetMachineSignDir(m));
			m_MachineSign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_MachineSign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetLotIDSignCount()>0)
	{
		for(m = 0; m<GetLotIDSignCount(); ++m)
		{
			TxtPos=GetLotIDSignPos(m);
			m_LotIdSign[m].m_TextPosition=GetRotateTextPositon(GetLotIDSignDir(m),GetLotIDTextPosition(m));
			m_LotIdSign[m].m_iDirection=GetRotateTextDir(GetLotIDSignDir(m));
			m_LotIdSign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_LotIdSign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetAxisNoSignCount()>0)//ly add 20121230
	{
		for(m = 0; m<GetAxisNoSignCount(); ++m)
		{
			TxtPos=GetAxisNoSignPos(m);
			m_AxisNoSign[m].m_TextPosition=GetRotateTextPositon(GetAxisNoSignDir(m),GetAxisNoTextPosition(m));
			m_AxisNoSign[m].m_iDirection=GetRotateTextDir(GetAxisNoSignDir(m));
			m_AxisNoSign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_AxisNoSign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetScaleSignCount()>0)//ly add 20131104
	{
		for(m = 0; m<GetScaleSignCount(); ++m)
		{
			TxtPos=GetScaleSignPos(m);
			m_ScaleSign[m].m_TextPosition=GetRotateTextPositon(GetScaleSignDir(m),GetScaleTextPosition(m));
			m_ScaleSign[m].m_iDirection=GetRotateTextDir(GetScaleSignDir(m));
			m_ScaleSign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_ScaleSign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetStrTextSignCount()>0)
	{
		for(m = 0; m<GetStrTextSignCount(); ++m)
		{
			TxtPos=GetStrTextSignPos(m);
			m_StrTextSign[m].m_TextPosition=GetRotateTextPositon(GetStrTextSignDir(m),GetStrTextPosition(m));
			m_StrTextSign[m].m_iDirection=GetRotateTextDir(GetStrTextSignDir(m));
			m_StrTextSign[m].m_crdTextPos.x = crdOrg.y-TxtPos.y+crdOrg.x;
			m_StrTextSign[m].m_crdTextPos.y = TxtPos.x-crdOrg.x+crdOrg.y;
		}
	}
	//主标靶
	for(int FidIdex=0;FidIdex<GetFiducialNum();FidIdex++)
	{
		FidPos = GetFiducialPos(FidIdex);	
		m_FiducialData[FidIdex].x = crdOrg.y-FidPos.y+crdOrg.x;
		m_FiducialData[FidIdex].y = FidPos.x-crdOrg.x+crdOrg.y;
	}
	SortFiducialData();
	
	//整板分区
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		crdDest = GetSubAreaCenter(curSubAreaNo);
		//lenth - crdDest.y;
		SubArea& subarea = GetSubAreaData(curSubAreaNo);
		subarea.crdCenter.x = crdOrg.y-crdDest.y+crdOrg.x;
		subarea.crdCenter.y = crdDest.x-crdOrg.x+crdOrg.y;
		
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			//处理文件头没有刀具信息，而有点的问题
			//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
			if(GetToolsNum()==0)
			{
				
				for(int n=0;n<subarea.hcvHoleData.size();n++)
				{
					int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						crdHole.x =Holecrd->x;
						crdHole.y =Holecrd->y;
						Holecrd->x = - crdHole.y;
						Holecrd->y =  crdHole.x;
						nCommandCnt++;
					}					
				}				
			}			
			else
			{		
				for(int it=0;it<GetToolsNum();++it)
				{   
					ToolInfo nToolNo = GetToolInfo(it);
					int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
					if(nSubToolIndex==-1)
						continue;
					
					int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						crdHole.x =Holecrd->x;
						crdHole.y =Holecrd->y;
						Holecrd->x = - crdHole.y;
						Holecrd->y =  crdHole.x;
						nCommandCnt++;
					}
				}			
			}						
		}
	}
	//	SortSubArea(m_SubArea);
	
	if(GetLocalMarkDataCount()>0)
	{
		for(int index=0;index<GetLocalMarkDataCount();index++)
		{
			for(int n=0;n<GetLocalMark(index).size();n++)
			{
				FidPos = GetLocalMarkDataPos(index,n);
				m_LocalMarkV[index].m_LocalMarkData[n].x = crdOrg.y-FidPos.y+crdOrg.x;
				m_LocalMarkV[index].m_LocalMarkData[n].y = FidPos.x-crdOrg.x+crdOrg.y;
			}
			
			for(curSubAreaNo=0;curSubAreaNo<GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
			{
				crdDest = GetLocalMarkSubAreaCenter(index,curSubAreaNo);
				//lenth - crdDest.y;
				SubArea& subarea = GetLocalMarkSubAreaData(index,curSubAreaNo);
				subarea.crdCenter.x = crdOrg.y-crdDest.y+crdOrg.x;
				subarea.crdCenter.y = crdDest.x-crdOrg.x+crdOrg.y;
				
				if(!GetLocalMarkSubAreaIsEmpty(index,curSubAreaNo)) 
				{
					//处理文件头没有刀具信息，而有点的问题
					//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
					if(GetToolsNum()==0)
					{
						
						for(int n=0;n<subarea.hcvHoleData.size();n++)
						{
							int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								crdHole.x =Holecrd->x;
								crdHole.y =Holecrd->y;
								Holecrd->x = - crdHole.y;
								Holecrd->y =  crdHole.x;
								nCommandCnt++;
							}					
						}				
					}			
					else
					{		
						for(int it=0;it<GetToolsNum();++it)
						{   
							ToolInfo nToolNo = GetToolInfo(it);
							int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
							if(nSubToolIndex==-1)
								continue;
							
							int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								crdHole.x =Holecrd->x;
								crdHole.y =Holecrd->y;
								Holecrd->x = - crdHole.y;
								Holecrd->y =  crdHole.x;
								nCommandCnt++;
							}
						}			
					}						
				}
			}
			//	SortSubArea(m_LocalMarkSubArea[index].m_LocalMarkSA);
		}
		
		SortLocalMarkData();
		
		for(curSubAreaNo=0;curSubAreaNo<GetOtherSubAreaCnt();++curSubAreaNo)
		{
			crdDest = GetOtherSubAreaCenter(curSubAreaNo);
			//lenth - crdDest.y;
			SubArea& subarea = GetOtherSubAreaData(curSubAreaNo);
			subarea.crdCenter.x = crdOrg.y-crdDest.y+crdOrg.x;
			subarea.crdCenter.y = crdDest.x-crdOrg.x+crdOrg.y;
			
			if(!GetOtherSubAreaIsEmpty(curSubAreaNo)) 
			{
				//处理文件头没有刀具信息，而有点的问题
				//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
				if(GetToolsNum()==0)
				{
					
					for(int n=0;n<subarea.hcvHoleData.size();n++)
					{
						int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							crdHole.x =Holecrd->x;
							crdHole.y =Holecrd->y;
							Holecrd->x = - crdHole.y;
							Holecrd->y =  crdHole.x;
							nCommandCnt++;
						}					
					}				
				}			
				else
				{		
					for(int it=0;it<GetToolsNum();++it)
					{   
						ToolInfo nToolNo = GetToolInfo(it);
						int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
						if(nSubToolIndex==-1)
							continue;
						
						int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							crdHole.x =Holecrd->x;
							crdHole.y =Holecrd->y;
							Holecrd->x = - crdHole.y;
							Holecrd->y =  crdHole.x;
							nCommandCnt++;
						}
					}			
				}						
			}
		}
		//	SortSubArea(m_OtherSubArea);
	}
	
	if(GetSALocalMarkDataCount()>0)
	{
		for(int indexSA=0;indexSA<GetSALocalMarkDataCount();indexSA++)
		{
			for(m=0;m<GetSALocalMark(indexSA).size();m++)
			{
				FidPos = GetSALocalMarkDataPos(indexSA,m);
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].x = crdOrg.y-FidPos.y+crdOrg.x;
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].y = FidPos.x-crdOrg.x+crdOrg.y;
			}
		}
		SortSALocalMarkData();
	}
	
	if(GetInnerFiducialNum()>0)
	{
		for(int nIndex=0;nIndex<GetInnerFiducialNum();nIndex++)
		{
			FidPos = GetInnerFiducialPos(nIndex);	
			m_InnerFiducialData[nIndex].x = crdOrg.y-FidPos.y+crdOrg.x;
			m_InnerFiducialData[nIndex].y = FidPos.x-crdOrg.x+crdOrg.y;
		}
		SortInnerFiducialData();
	}
	return;
}

void ExcellonData::Rotate180()		//逆时针180度旋转  ly add 20120901
{
	Coord TxtPos;
	Coord FidPos;
	Coord crdHole;
	
	double dbDist;
	long lDistMin,lPos0;
	
	Coord crdDest,crdMid,crdOrg;
	int nCommandCnt=0,m;
	int curSubAreaNo = 0;
	
	char ez[256]={""};//ly 20110404
	
	CRD MinX = 99999999,MaxX = -99999999;
	CRD lenth;
	
	int iLength = m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY;//长宽不变
	int iWidth = m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX;
	
	if(iWidth>GetDoc().GetTableWidth()*1000)
	{
		strncpy(ez,GetLang().GetWarningText(11002),256);
		AfxMessageBox(ez);//"数据宽度超出加工范围!"
		return;
	}
	
	if (iLength>GetDoc().GetTableHeight()*1000)
	{
		strncpy(ez,GetLang().GetWarningText(11003),256);
		AfxMessageBox(ez);//"数据高度超出加工范围!"
		return;
	}
	
	crdMid.x=(m_FileLayer.m_iLayerEndX+m_FileLayer.m_iLayerStartX)/2;
	crdMid.y=(m_FileLayer.m_iLayerEndY+m_FileLayer.m_iLayerStartY)/2;//文件中心点
	
	lDistMin=9999999999;
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			crdDest = GetSubAreaCenter(curSubAreaNo);
			dbDist = (pow((crdDest.x-crdMid.x),2)+pow((crdDest.y-crdMid.y),2))/1000.0;
			
			if(dbDist<lDistMin)
			{
				lDistMin = dbDist;
				lPos0 = curSubAreaNo;//得到与中心点最近的分区序号
			}
		}
	}
	
	crdOrg = GetSubAreaCenter(lPos0);//最靠中心分区的坐标值
	
	m_iSubAreaRow = iWidth /GetDoc().GetScanSize()/1000 +(iWidth %(GetDoc().GetScanSize()*1000)==0?0:1);
	m_iSubAreaCol = iLength/GetDoc().GetScanSize()/1000 +(iLength%(GetDoc().GetScanSize()*1000)==0?0:1);//计算文件分区行列数
	
	//日期，机器号等
	if(GetDaySignCount()>0)
	{
		for(m = 0; m<GetDaySignCount(); ++m)
		{
			TxtPos = GetDaySignPos(m);
			m_DaySign[m].m_TextPosition=GetRotateTextPositon(GetDaySignDir(m),GetDayTextPosition(m),1);
			m_DaySign[m].m_iDirection=GetRotateTextDir(GetDaySignDir(m),1);
			m_DaySign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_DaySign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	
	if(GetTimeSignCount()>0)
	{
		for(m = 0; m<GetTimeSignCount(); ++m)
		{
			TxtPos = GetTimeSignPos(m);
			m_TimeSign[m].m_TextPosition=GetRotateTextPositon(GetTimeSignDir(m),GetTimeTextPosition(m),1);
			m_TimeSign[m].m_iDirection=GetRotateTextDir(GetTimeSignDir(m),1);
			m_TimeSign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_TimeSign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	
	if(GetMachineSignCount()>0)
	{
		for(m = 0; m<GetMachineSignCount(); ++m)
		{
			TxtPos = GetMachineSignPos(m);
			m_MachineSign[m].m_TextPosition=GetRotateTextPositon(GetMachineSignDir(m),GetMachineTextPosition(m),1);
			m_MachineSign[m].m_iDirection=GetRotateTextDir(GetMachineSignDir(m),1);
			m_MachineSign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_MachineSign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	
	if(GetLotIDSignCount()>0)
	{
		for(m = 0; m<GetLotIDSignCount(); ++m)
		{
			TxtPos=GetLotIDSignPos(m);
			m_LotIdSign[m].m_TextPosition=GetRotateTextPositon(GetLotIDSignDir(m),GetLotIDTextPosition(m),1);
			m_LotIdSign[m].m_iDirection=GetRotateTextDir(GetLotIDSignDir(m),1);
			m_LotIdSign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_LotIdSign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	
	if(GetAxisNoSignCount()>0)//ly add 20121230
	{
		for(m = 0; m<GetAxisNoSignCount(); ++m)
		{
			TxtPos=GetAxisNoSignPos(m);
			m_AxisNoSign[m].m_TextPosition=GetRotateTextPositon(GetAxisNoSignDir(m),GetAxisNoTextPosition(m),1);
			m_AxisNoSign[m].m_iDirection=GetRotateTextDir(GetAxisNoSignDir(m),1);
			m_AxisNoSign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_AxisNoSign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	
	if(GetScaleSignCount()>0)//ly add 20121230
	{
		for(m = 0; m<GetScaleSignCount(); ++m)
		{
			TxtPos=GetScaleSignPos(m);
			m_ScaleSign[m].m_TextPosition=GetRotateTextPositon(GetScaleSignDir(m),GetScaleTextPosition(m),1);
			m_ScaleSign[m].m_iDirection=GetRotateTextDir(GetScaleSignDir(m),1);
			m_ScaleSign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_ScaleSign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	
	if(GetStrTextSignCount()>0)
	{
		for(m = 0; m<GetStrTextSignCount(); ++m)
		{
			TxtPos=GetStrTextSignPos(m);
			m_StrTextSign[m].m_TextPosition=GetRotateTextPositon(GetStrTextSignDir(m),GetStrTextPosition(m),1);
			m_StrTextSign[m].m_iDirection=GetRotateTextDir(GetStrTextSignDir(m),1);
			m_StrTextSign[m].m_crdTextPos.x = crdOrg.x+crdOrg.x-TxtPos.x;//ly change 20120903
			m_StrTextSign[m].m_crdTextPos.y = crdOrg.y+crdOrg.y-TxtPos.y;
		}
	}
	//主标靶
	for(int FidIdex=0;FidIdex<GetFiducialNum();FidIdex++)
	{
		FidPos = GetFiducialPos(FidIdex);	
		m_FiducialData[FidIdex].x = crdOrg.x+crdOrg.x-FidPos.x;//ly change 20120903
		m_FiducialData[FidIdex].y = crdOrg.y+crdOrg.y-FidPos.y;
	}
	SortFiducialData();
	
	//整板分区
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		crdDest = GetSubAreaCenter(curSubAreaNo);
		//lenth - crdDest.y;
		SubArea& subarea = GetSubAreaData(curSubAreaNo);
		subarea.crdCenter.x = crdOrg.x+crdOrg.x-crdDest.x;//ly change 20120903
		subarea.crdCenter.y = crdOrg.y+crdOrg.y-crdDest.y;
		
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			//处理文件头没有刀具信息，而有点的问题
			//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
			if(GetToolsNum()==0)
			{
				
				for(int n=0;n<subarea.hcvHoleData.size();n++)
				{
					int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						crdHole.x =Holecrd->x;
						crdHole.y =Holecrd->y;
						Holecrd->x = - crdHole.x;
						Holecrd->y = - crdHole.y;//ly change 20120903
						nCommandCnt++;
					}					
				}				
			}			
			else
			{		
				for(int it=0;it<GetToolsNum();++it)
				{   
					ToolInfo nToolNo = GetToolInfo(it);
					int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
					if(nSubToolIndex==-1)
						continue;
					
					int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						crdHole.x =Holecrd->x;
						crdHole.y =Holecrd->y;
						Holecrd->x = - crdHole.x;
						Holecrd->y = - crdHole.y;//ly change 20120903
						nCommandCnt++;
					}
				}			
			}						
		}
	}
	//	SortSubArea(m_SubArea);
	
	if(GetLocalMarkDataCount()>0)
	{
		for(int index=0;index<GetLocalMarkDataCount();index++)
		{
			for(int n=0;n<GetLocalMark(index).size();n++)
			{
				FidPos = GetLocalMarkDataPos(index,n);
				m_LocalMarkV[index].m_LocalMarkData[n].x = crdOrg.x+crdOrg.x-FidPos.x;//ly change 20120903
				m_LocalMarkV[index].m_LocalMarkData[n].y = crdOrg.y+crdOrg.y-FidPos.y;
			}
			
			for(curSubAreaNo=0;curSubAreaNo<GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
			{
				crdDest = GetLocalMarkSubAreaCenter(index,curSubAreaNo);
				//lenth - crdDest.y;
				SubArea& subarea = GetLocalMarkSubAreaData(index,curSubAreaNo);
				subarea.crdCenter.x = crdOrg.x+crdOrg.x-crdDest.x;//ly change 20120903
				subarea.crdCenter.y = crdOrg.y+crdOrg.y-crdDest.y;
				
				if(!GetLocalMarkSubAreaIsEmpty(index,curSubAreaNo)) 
				{
					//处理文件头没有刀具信息，而有点的问题
					//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
					if(GetToolsNum()==0)
					{
						
						for(int n=0;n<subarea.hcvHoleData.size();n++)
						{
							int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								crdHole.x =Holecrd->x;
								crdHole.y =Holecrd->y;
								Holecrd->x = - crdHole.x;
								Holecrd->y = - crdHole.y;//ly change 20120903
								nCommandCnt++;
							}					
						}				
					}			
					else
					{		
						for(int it=0;it<GetToolsNum();++it)
						{   
							ToolInfo nToolNo = GetToolInfo(it);
							int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
							if(nSubToolIndex==-1)
								continue;
							
							int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								crdHole.x =Holecrd->x;
								crdHole.y =Holecrd->y;
								Holecrd->x = - crdHole.x;
								Holecrd->y = - crdHole.y;//ly change 20120903
								nCommandCnt++;
							}
						}			
					}						
				}
			}
			//	SortSubArea(m_LocalMarkSubArea[index].m_LocalMarkSA);
		}
		
		SortLocalMarkData();
		
		for(curSubAreaNo=0;curSubAreaNo<GetOtherSubAreaCnt();++curSubAreaNo)
		{
			crdDest = GetOtherSubAreaCenter(curSubAreaNo);
			//lenth - crdDest.y;
			SubArea& subarea = GetOtherSubAreaData(curSubAreaNo);
			subarea.crdCenter.x = crdOrg.x+crdOrg.x-crdDest.x;//ly change 20120903
			subarea.crdCenter.y = crdOrg.y+crdOrg.y-crdDest.y;
			
			if(!GetOtherSubAreaIsEmpty(curSubAreaNo)) 
			{
				//处理文件头没有刀具信息，而有点的问题
				//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
				if(GetToolsNum()==0)
				{
					
					for(int n=0;n<subarea.hcvHoleData.size();n++)
					{
						int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							crdHole.x =Holecrd->x;
							crdHole.y =Holecrd->y;
							Holecrd->x = - crdHole.x;
							Holecrd->y = - crdHole.y;//ly change 20120903
							nCommandCnt++;
						}					
					}				
				}			
				else
				{		
					for(int it=0;it<GetToolsNum();++it)
					{   
						ToolInfo nToolNo = GetToolInfo(it);
						int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
						if(nSubToolIndex==-1)
							continue;
						
						int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							crdHole.x =Holecrd->x;
							crdHole.y =Holecrd->y;
							Holecrd->x = - crdHole.x;
							Holecrd->y = - crdHole.y;//ly change 20120903
							nCommandCnt++;
						}
					}			
				}						
			}
		}
		//	SortSubArea(m_OtherSubArea);
	}
	
	if(GetSALocalMarkDataCount()>0)
	{
		for(int indexSA=0;indexSA<GetSALocalMarkDataCount();indexSA++)
		{
			for(m=0;m<GetSALocalMark(indexSA).size();m++)
			{
				FidPos = GetSALocalMarkDataPos(indexSA,m);
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].x = crdOrg.x+crdOrg.x-FidPos.x;//ly change 20120903
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].y = crdOrg.y+crdOrg.y-FidPos.y;
			}
		}
		SortSALocalMarkData();
	}
	
	if(GetInnerFiducialNum()>0)
	{
		for(int nIndex=0;nIndex<GetInnerFiducialNum();nIndex++)
		{
			FidPos = GetInnerFiducialPos(nIndex);	
			m_InnerFiducialData[nIndex].x = crdOrg.x+crdOrg.x-FidPos.x;//ly change 20120903
			m_InnerFiducialData[nIndex].y = crdOrg.y+crdOrg.y-FidPos.y;
		}
		SortInnerFiducialData();
	}
	return;
}

void ExcellonData::Rotate270()		//逆时针270度旋转
{
	Coord TxtPos;
	Coord FidPos;
	Coord crdHole;
	
	double dbDist;
	long lDistMin,lPos0;
	
	Coord crdDest,crdMid,crdOrg;
	int nCommandCnt=0,m;
	int curSubAreaNo = 0;
	
	char ez[256]={""};//ly 20110404
	
	CRD MinX = 99999999,MaxX = -99999999;
	CRD lenth;
	
	int iWidth = m_FileLayer.m_iLayerEndY-m_FileLayer.m_iLayerStartY;
	int iLength = m_FileLayer.m_iLayerEndX-m_FileLayer.m_iLayerStartX;
	
	if(iWidth>GetDoc().GetTableWidth()*1000)
	{
		strncpy(ez,GetLang().GetWarningText(11002),256);
		AfxMessageBox(ez);//"数据宽度超出加工范围!"
		return;
	}
	
	if (iLength>GetDoc().GetTableHeight()*1000)
	{
		strncpy(ez,GetLang().GetWarningText(11003),256);
		AfxMessageBox(ez);//"数据高度超出加工范围!"
		return;
	}
	
	crdMid.x=(m_FileLayer.m_iLayerEndX+m_FileLayer.m_iLayerStartX)/2;
	crdMid.y=(m_FileLayer.m_iLayerEndY+m_FileLayer.m_iLayerStartY)/2;
	
	lDistMin=9999999999;
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			crdDest = GetSubAreaCenter(curSubAreaNo);
			dbDist = (pow((crdDest.x-crdMid.x),2)+pow((crdDest.y-crdMid.y),2))/1000.0;
			
			if(dbDist<lDistMin)
			{
				lDistMin = dbDist;
				lPos0 = curSubAreaNo;
			}
		}
	}
	
	crdOrg = GetSubAreaCenter(lPos0);
	
	m_iSubAreaRow = iWidth /GetDoc().GetScanSize()/1000 +(iWidth %(GetDoc().GetScanSize()*1000)==0?0:1);
	m_iSubAreaCol = iLength/GetDoc().GetScanSize()/1000 +(iLength%(GetDoc().GetScanSize()*1000)==0?0:1);
	
	//日期，机器号等
	if(GetDaySignCount()>0)
	{
		for(m = 0; m<GetDaySignCount(); ++m)
		{
			TxtPos = GetDaySignPos(m);
			m_DaySign[m].m_TextPosition=GetRotateTextPositon(GetDaySignDir(m),GetDayTextPosition(m),2);
			m_DaySign[m].m_iDirection=GetRotateTextDir(GetDaySignDir(m),2);
			m_DaySign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_DaySign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetTimeSignCount()>0)
	{
		for(m = 0; m<GetTimeSignCount(); ++m)
		{
			TxtPos = GetTimeSignPos(m);
			m_TimeSign[m].m_TextPosition=GetRotateTextPositon(GetTimeSignDir(m),GetTimeTextPosition(m),2);
			m_TimeSign[m].m_iDirection=GetRotateTextDir(GetTimeSignDir(m),2);
			m_TimeSign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_TimeSign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetMachineSignCount()>0)
	{
		for(m = 0; m<GetMachineSignCount(); ++m)
		{
			TxtPos = GetMachineSignPos(m);
			m_MachineSign[m].m_TextPosition=GetRotateTextPositon(GetMachineSignDir(m),GetMachineTextPosition(m),2);
			m_MachineSign[m].m_iDirection=GetRotateTextDir(GetMachineSignDir(m),2);
			m_MachineSign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_MachineSign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetLotIDSignCount()>0)
	{
		for(m = 0; m<GetLotIDSignCount(); ++m)
		{
			TxtPos=GetLotIDSignPos(m);
			m_LotIdSign[m].m_TextPosition=GetRotateTextPositon(GetLotIDSignDir(m),GetLotIDTextPosition(m),2);
			m_LotIdSign[m].m_iDirection=GetRotateTextDir(GetLotIDSignDir(m),2);
			m_LotIdSign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_LotIdSign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetAxisNoSignCount()>0)//ly add 20121230
	{
		for(m = 0; m<GetAxisNoSignCount(); ++m)
		{
			TxtPos=GetAxisNoSignPos(m);
			m_AxisNoSign[m].m_TextPosition=GetRotateTextPositon(GetAxisNoSignDir(m),GetAxisNoTextPosition(m),2);
			m_AxisNoSign[m].m_iDirection=GetRotateTextDir(GetAxisNoSignDir(m),2);
			m_AxisNoSign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_AxisNoSign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetScaleSignCount()>0)//ly add 20131104
	{
		for(m = 0; m<GetScaleSignCount(); ++m)
		{
			TxtPos=GetScaleSignPos(m);
			m_ScaleSign[m].m_TextPosition=GetRotateTextPositon(GetScaleSignDir(m),GetScaleTextPosition(m),2);
			m_ScaleSign[m].m_iDirection=GetRotateTextDir(GetScaleSignDir(m),2);
			m_ScaleSign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_ScaleSign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	
	if(GetStrTextSignCount()>0)
	{
		for(m = 0; m<GetStrTextSignCount(); ++m)
		{
			TxtPos=GetStrTextSignPos(m);
			m_StrTextSign[m].m_TextPosition=GetRotateTextPositon(GetStrTextSignDir(m),GetStrTextPosition(m),2);
			m_StrTextSign[m].m_iDirection=GetRotateTextDir(GetStrTextSignDir(m),2);
			m_StrTextSign[m].m_crdTextPos.x = -crdOrg.y+TxtPos.y+crdOrg.x;//ly change 20120903
			m_StrTextSign[m].m_crdTextPos.y = -TxtPos.x+crdOrg.x+crdOrg.y;
		}
	}
	//主标靶
	for(int FidIdex=0;FidIdex<GetFiducialNum();FidIdex++)
	{
		FidPos = GetFiducialPos(FidIdex);	
		m_FiducialData[FidIdex].x = -crdOrg.y+FidPos.y+crdOrg.x;//ly change 20120903
		m_FiducialData[FidIdex].y = -FidPos.x+crdOrg.x+crdOrg.y;
	}
	SortFiducialData();
	
	//整板分区
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{
		crdDest = GetSubAreaCenter(curSubAreaNo);
		//lenth - crdDest.y;
		SubArea& subarea = GetSubAreaData(curSubAreaNo);
		subarea.crdCenter.x = -crdOrg.y+crdDest.y+crdOrg.x;//ly change 20120903
		subarea.crdCenter.y = -crdDest.x+crdOrg.x+crdOrg.y;
		
		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
		{
			//处理文件头没有刀具信息，而有点的问题
			//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
			if(GetToolsNum()==0)
			{
				
				for(int n=0;n<subarea.hcvHoleData.size();n++)
				{
					int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						crdHole.x =Holecrd->x;
						crdHole.y =Holecrd->y;
						Holecrd->x =  crdHole.y;//ly change 20120903
						Holecrd->y = - crdHole.x;
						nCommandCnt++;
					}					
				}				
			}			
			else
			{		
				for(int it=0;it<GetToolsNum();++it)
				{   
					ToolInfo nToolNo = GetToolInfo(it);
					int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
					if(nSubToolIndex==-1)
						continue;
					
					int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
					if (holecnt<=0) continue ;
					std::vector<HoleClass>::iterator hcv;
					hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
					std::vector<Coord>::iterator Holecrd;
					nCommandCnt = 0;
					while(nCommandCnt<holecnt)
					{
						Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
						crdHole.x =Holecrd->x;
						crdHole.y =Holecrd->y;
						Holecrd->x =  crdHole.y;//ly change 20120903
						Holecrd->y = - crdHole.x;
						nCommandCnt++;
					}
				}			
			}						
		}
	}
	//	SortSubArea(m_SubArea);
	
	if(GetLocalMarkDataCount()>0)
	{
		for(int index=0;index<GetLocalMarkDataCount();index++)
		{
			for(int n=0;n<GetLocalMark(index).size();n++)
			{
				FidPos = GetLocalMarkDataPos(index,n);
				m_LocalMarkV[index].m_LocalMarkData[n].x = -crdOrg.y+FidPos.y+crdOrg.x;//ly change 20120903
				m_LocalMarkV[index].m_LocalMarkData[n].y = -FidPos.x+crdOrg.x+crdOrg.y;
			}
			
			for(curSubAreaNo=0;curSubAreaNo<GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
			{
				crdDest = GetLocalMarkSubAreaCenter(index,curSubAreaNo);
				//lenth - crdDest.y;
				SubArea& subarea = GetLocalMarkSubAreaData(index,curSubAreaNo);
				subarea.crdCenter.x = -crdOrg.y+crdDest.y+crdOrg.x;//ly change 20120903
				subarea.crdCenter.y = -crdDest.x+crdOrg.x+crdOrg.y;
				
				if(!GetLocalMarkSubAreaIsEmpty(index,curSubAreaNo)) 
				{
					//处理文件头没有刀具信息，而有点的问题
					//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
					if(GetToolsNum()==0)
					{
						
						for(int n=0;n<subarea.hcvHoleData.size();n++)
						{
							int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								crdHole.x =Holecrd->x;
								crdHole.y =Holecrd->y;
								Holecrd->x =  crdHole.y;//ly change 20120903
								Holecrd->y = - crdHole.x;
								nCommandCnt++;
							}					
						}				
					}			
					else
					{		
						for(int it=0;it<GetToolsNum();++it)
						{   
							ToolInfo nToolNo = GetToolInfo(it);
							int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
							if(nSubToolIndex==-1)
								continue;
							
							int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
							if (holecnt<=0) continue ;
							std::vector<HoleClass>::iterator hcv;
							hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
							std::vector<Coord>::iterator Holecrd;
							nCommandCnt = 0;
							while(nCommandCnt<holecnt)
							{
								Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
								crdHole.x =Holecrd->x;
								crdHole.y =Holecrd->y;
								Holecrd->x =  crdHole.y;//ly change 20120903
								Holecrd->y = - crdHole.x;
								nCommandCnt++;
							}
						}			
					}						
				}
			}
			//	SortSubArea(m_LocalMarkSubArea[index].m_LocalMarkSA);
		}
		
		SortLocalMarkData();
		
		for(curSubAreaNo=0;curSubAreaNo<GetOtherSubAreaCnt();++curSubAreaNo)
		{
			crdDest = GetOtherSubAreaCenter(curSubAreaNo);
			//lenth - crdDest.y;
			SubArea& subarea = GetOtherSubAreaData(curSubAreaNo);
			subarea.crdCenter.x = -crdOrg.y+crdDest.y+crdOrg.x;//ly change 20120903
			subarea.crdCenter.y = -crdDest.x+crdOrg.x+crdOrg.y;
			
			if(!GetOtherSubAreaIsEmpty(curSubAreaNo)) 
			{
				//处理文件头没有刀具信息，而有点的问题
				//			if((GetToolsNum()==0)&&(GetDoc().GetCurPCBHoleCount()>0))
				if(GetToolsNum()==0)
				{
					
					for(int n=0;n<subarea.hcvHoleData.size();n++)
					{
						int holecnt = subarea.hcvHoleData[n].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+n);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							crdHole.x =Holecrd->x;
							crdHole.y =Holecrd->y;
							Holecrd->x = crdHole.y;//ly change 20120903
							Holecrd->y = -  crdHole.x;
							nCommandCnt++;
						}					
					}				
				}			
				else
				{		
					for(int it=0;it<GetToolsNum();++it)
					{   
						ToolInfo nToolNo = GetToolInfo(it);
						int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
						if(nSubToolIndex==-1)
							continue;
						
						int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
						if (holecnt<=0) continue ;
						std::vector<HoleClass>::iterator hcv;
						hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
						std::vector<Coord>::iterator Holecrd;
						nCommandCnt = 0;
						while(nCommandCnt<holecnt)
						{
							Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
							crdHole.x =Holecrd->x;
							crdHole.y =Holecrd->y;
							Holecrd->x =  crdHole.y;//ly change 20120903
							Holecrd->y = - crdHole.x;
							nCommandCnt++;
						}
					}			
				}						
			}
		}
		//	SortSubArea(m_OtherSubArea);
	}
	
	if(GetSALocalMarkDataCount()>0)
	{
		for(int indexSA=0;indexSA<GetSALocalMarkDataCount();indexSA++)
		{
			for(m=0;m<GetSALocalMark(indexSA).size();m++)
			{
				FidPos = GetSALocalMarkDataPos(indexSA,m);
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].x = -crdOrg.y+FidPos.y+crdOrg.x;//ly change 20120903
				m_SALocalMarkV[indexSA].m_LocalMarkData[m].y = -FidPos.x+crdOrg.x+crdOrg.y;
			}
		}
		SortSALocalMarkData();
	}
	
	if(GetInnerFiducialNum()>0)
	{
		for(int nIndex=0;nIndex<GetInnerFiducialNum();nIndex++)
		{
			FidPos = GetInnerFiducialPos(nIndex);	
			m_InnerFiducialData[nIndex].x = -crdOrg.y+FidPos.y+crdOrg.x;//ly change 20120903
			m_InnerFiducialData[nIndex].y = -FidPos.x+crdOrg.x+crdOrg.y;
		}
		SortInnerFiducialData();
	}
	return;
}

void ExcellonData::SortSubArea(SubAreaV& sav)			// 分区排序
{
//	std::vector<SubArea>::iterator itsa,itsa1,itsa2; 
	int lScanSize=GetDoc().GetScanSize()*1000;
	Coord crd1,crd2;
	long lDistMin;
	long lDist=0,lPos;
	bool bResult;
	
//	for(itsa1 = sav.begin();itsa1!=(sav.end()-1);++itsa1)
//	for(int i=0;i<sav.size()-1;i++)
	for(int i=0;i<sav.size()-1;i++)
	{
		lDistMin=9999999999;
//		crd1 = itsa1->crdCenter;
		crd1 = sav[i].crdCenter;
		bResult=false;
		
//		for(itsa2 = itsa1+1;itsa2!=sav.end();++itsa2)
		for(int j=i+1;j<sav.size();j++)
		{
//			crd2 = itsa2->crdCenter;
			crd2 = sav[j].crdCenter;
			lDist = abs(crd2.x-crd1.x);
			
			if(crd2.y>(crd1.y-lScanSize/2)&&crd2.y<=(crd1.y+lScanSize/2)&&lDist<lDistMin)
			{
				lDistMin = lDist;
//				itsa = itsa2;
				lPos = j;
				bResult=true;
			}
		}
		
		if(bResult)
		{
			std::swap(sav[i+1],sav[lPos]);
		}
		else
		{
			lDistMin=9999999999;
			
//			for(itsa2 = itsa1+1;itsa2!=sav.end();++itsa2)
			for(int j=i+1;j<sav.size();j++)
			{
//				crd2 = itsa2->crdCenter;
				crd2 = sav[j].crdCenter;
				lDist = sqrt(pow(crd2.x-crd1.x,2)+pow(crd2.y-crd1.y,2));
				
				if(lDist<lDistMin)
				{
					lDistMin = lDist;
//					itsa = itsa2;
					lPos = j;
				}
			}
			std::swap(sav[i+1],sav[lPos]);
		}
	}
}

TextPosition ExcellonData::GetMirrorTextPositon(TextDir td,TextPosition tp)
{
	if(HorizontalText==td)
	{
		switch(tp)
		{
		case 0:
			return RIGHTBOTTOM;
		case 1:
			return RIGHTTOP;
		case 2:
			return LEFTTOP;
		case 3:
			return LEFTBOTTOM;
		default:
			return RIGHTBOTTOM;
		}
	}
	else if(VerticalText==td)
	{
		switch(tp)
		{
		case 0:
			return LEFTTOP;
		case 1:
			return LEFTBOTTOM;
		case 2:
			return RIGHTBOTTOM;
		case 3:
			return RIGHTTOP;
		default:
			return LEFTTOP;
		}
	}		
}

TextDir ExcellonData::GetRotateTextDir(TextDir td,int Rotatetype)
{
	if(Rotatetype==1)//180
	{
		if(HorizontalText==td)
		{
			return HorizontalText;	
		}
		else if(VerticalText==td)
		{
			return VerticalText;
		}
	}
	else//90,270
	{
		if(HorizontalText==td)
		{
			return VerticalText;	
		}
		else if(VerticalText==td)
		{
			return HorizontalText;
		}
	}
}

TextPosition ExcellonData::GetRotateTextPositon(TextDir td,TextPosition tp,int Rotatetype)
{
	if(Rotatetype==0)//90
	{
		if(VerticalText==td)
		{
			switch(tp)
			{
			case 0:
				return RIGHTTOP;
			case 1:
				return RIGHTBOTTOM;
			case 2:
				return LEFTBOTTOM;
			case 3:
				return LEFTTOP;
			default:
				return RIGHTTOP;
			}
		}
		else//HorizontalText
		{
			return tp;
		}
	}
	else if(Rotatetype==1)//180
	{
		if(VerticalText==td)
		{
			switch(tp)
			{
			case 0:
				return RIGHTTOP  ;
			case 1:
				return RIGHTBOTTOM  ;
			case 2:
				return LEFTBOTTOM;
			case 3:
				return LEFTTOP;
			default:
				return RIGHTTOP;
			}
		}
		else//HorizontalText
		{
			switch(tp)
			{
			case 0:
				return RIGHTTOP;
			case 1:
				return RIGHTBOTTOM;
			case 2:
				return LEFTBOTTOM;
			case 3:
				return LEFTTOP;
			default:
				return RIGHTTOP;
			}
		}
	}
	else if(Rotatetype==2)//270
	{
		if(VerticalText==td)
		{
			return tp;
		}
		else//HorizontalText
		{
			switch(tp)
			{
			case 0:
				return RIGHTTOP;
			case 1:
				return RIGHTBOTTOM;
			case 2:
				return LEFTBOTTOM;
			case 3:
				return LEFTTOP;
			default:
				return RIGHTTOP;
			}			
		}
	}
}
//------------------------------------------------------------------------------------	  
BOOL ExcellonData::SADataTransSave(FILE* fp,int lScanSize,long lScanBit)
{
	int curSubAreaNo,m,n,nTool,holecount=0,lmholecount=0;
	long hole;
	CString InforStr;
	
	InforStr.Format("SCANSIZE%d\n",lScanSize);				
	GetInfo().SaveDataToFile(fp,InforStr);
	
	InforStr.Format("SCANBIT%d\n",lScanBit);	//ly add 20130412			
	GetInfo().SaveDataToFile(fp,InforStr);
	
	InforStr.Format("SUBAREAROW%d\n",m_iSubAreaRow);				
	GetInfo().SaveDataToFile(fp,InforStr);
	
	InforStr.Format("SUBAREACOL%d\n",m_iSubAreaCol);				
	GetInfo().SaveDataToFile(fp,InforStr);
	
	GetInfo().SaveDataToFile(fp,"[TOOL]\n");
	
	for(nTool=0;nTool<GetToolsNum();++nTool)
	{
		InforStr.Format("T%dC%.4f\n",GetToolInfo(nTool).m_nToolIndex,GetToolInfo(nTool).m_nToolX);
		GetInfo().SaveDataToFile(fp,InforStr);
	}
	
	GetInfo().SaveDataToFile(fp,"[MAINDATA]\n");
	
	n=0;
	for(curSubAreaNo=0;curSubAreaNo<GetSubAreaCnt();++curSubAreaNo)
	{		
//		if(!GetSubAreaIsEmpty(curSubAreaNo)) 
//		{
		InforStr.Format("SA%d\n",++n);
		GetInfo().SaveDataToFile(fp,InforStr);
		
		InforStr.Format("CENTERX%dY%d\n",GetSubAreaCenter(curSubAreaNo).x,GetSubAreaCenter(curSubAreaNo).y);
		GetInfo().SaveDataToFile(fp,InforStr);
		
		for(nTool=0;nTool<GetSubAreaData(curSubAreaNo).hcvHoleData.size();++nTool)
		{
			InforStr.Format("T%d\n",GetSubAreaData(curSubAreaNo).hcvHoleData[nTool].nToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			for(hole=0;hole<GetSubAreaData(curSubAreaNo).hcvHoleData[nTool].hcvHolePos.size();++hole)
			{
				holecount++;
				InforStr.Format("X%dY%d\n",GetSubAreaData(curSubAreaNo).hcvHoleData[nTool].hcvHolePos[hole].x,
					GetSubAreaData(curSubAreaNo).hcvHoleData[nTool].hcvHolePos[hole].y);
				GetInfo().SaveDataToFile(fp,InforStr);					
			}
		}
//		}
	}
	
	if(GetLocalMarkDataCount()>0)
	{
		GetInfo().SaveDataToFile(fp,"[LOCALMARK]\n");
		
		for(int index=0;index<GetLocalMarkDataCount();index++)
		{
			InforStr.Format("LM%d\n",index+1);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			for(m=0;m<GetLocalMark(index).size();++m)
			{
				InforStr.Format("AX%dY%d\n",GetLocalMarkDataPos(index,m).x,GetLocalMarkDataPos(index,m).y);
				GetInfo().SaveDataToFile(fp,InforStr);
			}
			
			n=0;
			for(curSubAreaNo=0;curSubAreaNo<GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
			{
				if(!GetLocalMarkSubAreaIsEmpty(index,curSubAreaNo)) 
				{
					InforStr.Format("SA%d\n",++n);
					GetInfo().SaveDataToFile(fp,InforStr);
					
					InforStr.Format("CENTERX%dY%d\n",GetLocalMarkSubAreaCenter(index,curSubAreaNo).x,
						GetLocalMarkSubAreaCenter(index,curSubAreaNo).y);
					GetInfo().SaveDataToFile(fp,InforStr);
					
					for(nTool=0;nTool<GetLocalMarkSubAreaData(index,curSubAreaNo).hcvHoleData.size();++nTool)
					{
						InforStr.Format("T%d\n",GetLocalMarkSubAreaData(index,curSubAreaNo).hcvHoleData[nTool].nToolNo);
						GetInfo().SaveDataToFile(fp,InforStr);
						
						for(hole=0;hole<GetLocalMarkSubAreaData(index,curSubAreaNo).hcvHoleData[nTool].hcvHolePos.size();++hole)
						{
							lmholecount++;
							InforStr.Format("X%dY%d\n",GetLocalMarkSubAreaData(index,curSubAreaNo).hcvHoleData[nTool].hcvHolePos[hole].x,
								GetLocalMarkSubAreaData(index,curSubAreaNo).hcvHoleData[nTool].hcvHolePos[hole].y);
							GetInfo().SaveDataToFile(fp,InforStr);					
						}
					}
				}
			}
		}
		
		GetInfo().SaveDataToFile(fp,"[OTHERDATA]\n");
		
		n=0;
		for(curSubAreaNo=0;curSubAreaNo<GetOtherSubAreaCnt();++curSubAreaNo)
		{
			if(!GetOtherSubAreaIsEmpty(curSubAreaNo)) 
			{
				InforStr.Format("SA%d\n",++n);
				GetInfo().SaveDataToFile(fp,InforStr);
				
				InforStr.Format("CENTERX%dY%d\n",GetOtherSubAreaCenter(curSubAreaNo).x,GetOtherSubAreaCenter(curSubAreaNo).y);
				GetInfo().SaveDataToFile(fp,InforStr);
				
				for(nTool=0;nTool<GetOtherSubAreaData(curSubAreaNo).hcvHoleData.size();++nTool)
				{
					InforStr.Format("T%d\n",GetOtherSubAreaData(curSubAreaNo).hcvHoleData[nTool].nToolNo);
					GetInfo().SaveDataToFile(fp,InforStr);
					
					for(hole=0;hole<GetOtherSubAreaData(curSubAreaNo).hcvHoleData[nTool].hcvHolePos.size();++hole)
					{
						lmholecount++;
						InforStr.Format("X%dY%d\n",GetOtherSubAreaData(curSubAreaNo).hcvHoleData[nTool].hcvHolePos[hole].x,
							GetOtherSubAreaData(curSubAreaNo).hcvHoleData[nTool].hcvHolePos[hole].y);
						GetInfo().SaveDataToFile(fp,InforStr);					
					}
				}
			}
		}
	}
	
	GetInfo().SaveDataToFile(fp,"[TEXT]\n");
	
	if(GetDaySignCount()>0)
	{
		for(m = 0; m<GetDaySignCount(); ++m)
		{
			GetInfo().SaveDataToFile(fp,"$D$");
			
			InforStr.Format("T%d",m_DaySign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetDaySignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetDayTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetDaySignPos(m).x,GetDaySignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	if(GetTimeSignCount()>0)
	{
		for(m = 0; m<GetTimeSignCount(); ++m)
		{
			GetInfo().SaveDataToFile(fp,"$T$");
			
			InforStr.Format("T%d",m_TimeSign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetTimeSignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetTimeTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetTimeSignPos(m).x,GetTimeSignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	if(GetMachineSignCount()>0)
	{
		for(m = 0; m<GetMachineSignCount(); ++m)
		{
			GetInfo().SaveDataToFile(fp,"$M$");
			
			InforStr.Format("T%d",m_MachineSign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetMachineSignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetMachineTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetMachineSignPos(m).x,GetMachineSignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	if(GetLotIDSignCount()>0)
	{
		for(m = 0; m<GetLotIDSignCount(); ++m)
		{
			GetInfo().SaveDataToFile(fp,"$L$");
			
			InforStr.Format("T%d",m_LotIdSign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetLotIDSignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetLotIDTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetLotIDSignPos(m).x,GetLotIDSignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	if(GetAxisNoSignCount()>0)//ly add 20121230
	{
		for(m = 0; m<GetAxisNoSignCount(); ++m)
		{
			GetInfo().SaveDataToFile(fp,"$A$");
			
			InforStr.Format("T%d",m_AxisNoSign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetAxisNoSignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetAxisNoTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetAxisNoSignPos(m).x,GetAxisNoSignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	if(GetScaleSignCount()>0)//ly add 20131104
	{
		for(m = 0; m<GetScaleSignCount(); ++m)
		{
			GetInfo().SaveDataToFile(fp,"$SC$");
			
			InforStr.Format("T%d",m_ScaleSign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetScaleSignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetScaleTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetScaleSignPos(m).x,GetScaleSignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	if(GetStrTextSignCount()>0)
	{
		for(m = 0; m<GetStrTextSignCount(); ++m)
		{
			InforStr.Format("STRING=%s\n",m_StrTextSign[m].m_strTextData);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			GetInfo().SaveDataToFile(fp,"$S$");
			
			InforStr.Format("T%d",m_StrTextSign[m].iToolNo);
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("DIR%d",GetStrTextSignDir(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("POS%d",GetStrTextPosition(m));
			GetInfo().SaveDataToFile(fp,InforStr);
			
			InforStr.Format("X%dY%d\n",GetStrTextSignPos(m).x,GetStrTextSignPos(m).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}
	
	GetInfo().SaveDataToFile(fp,"G82\n");
	
	for(int FidIdex=0;FidIdex<GetFiducialNum();FidIdex++)
	{
		InforStr.Format("X%dY%d\n",GetFiducialPos(FidIdex).x,GetFiducialPos(FidIdex).y);
		GetInfo().SaveDataToFile(fp,InforStr);			
	}
	
	if(GetInnerFiducialNum()>0)
	{
		GetInfo().SaveDataToFile(fp,"G83\n");
		
		for(int nIndex=0;nIndex<GetInnerFiducialNum();nIndex++)
		{
			InforStr.Format("X%dY%d\n",GetInnerFiducialPos(nIndex).x,GetInnerFiducialPos(nIndex).y);
			GetInfo().SaveDataToFile(fp,InforStr);
		}
	}	
	
	InforStr.Format("M30\nHoleCount=%d\nlmHoleCount=%d\n",holecount,lmholecount);
	GetInfo().SaveDataToFile(fp,InforStr);
	
	return true;
}

void ExcellonData::AddLMInfo(int iLMIndex)
{
	LocalMarkData lmd;
	lmd.m_iIndex=iLMIndex;
	m_LocalMarkV.push_back(lmd);
	
	m_LocalMarkSubArea.push_back(LocalMarkSubArea());
	m_LocalMarkSubArea[m_LocalMarkSubArea.size()-1].m_iLocalMarkIndex=iLMIndex;
	
	ASSERT(iLMIndex==m_LocalMarkSubArea.size()-1);
}

void ExcellonData::AddSMInfo(int iSMIndex)
{
	LocalMarkData lmd;
	lmd.m_iIndex=iSMIndex;
	m_SALocalMarkV.push_back(lmd);
}

void ExcellonData::AddSAMainInfo()
{
	m_SubArea.push_back(SubArea());
}

void ExcellonData::AddSAM02OtherInfo()
{
	m_OtherSubArea.push_back(SubArea());
}

void ExcellonData::AddSAM02LocalMarkInfo(int iLMIndex)
{
	ASSERT(iLMIndex==m_LocalMarkSubArea.size()-1);
	
	m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA.push_back(SubArea());
}

void ExcellonData::AddSAMainData(const HoleData& crd,int iSAIndex)
{
	ASSERT(iSAIndex==m_SubArea.size()-1);
	
	int ToolIndex = m_SubArea[iSAIndex].GetSameToolIndex(crd.iToolNo);
	
	if(ToolIndex!=NOLINK)
	{
		m_SubArea[iSAIndex].hcvHoleData[ToolIndex].hcvHolePos.push_back(Coord(crd.x,crd.y));
	}
	else
	{
		m_SubArea[iSAIndex].hcvHoleData.push_back(HoleClass(crd.iToolNo));
		ToolIndex = m_SubArea[iSAIndex].GetSameToolIndex(crd.iToolNo);
		m_SubArea[iSAIndex].hcvHoleData[ToolIndex].hcvHolePos.push_back(Coord(crd.x,crd.y));
	}
}

void ExcellonData::AddM02LocalMarkData(const HoleData& crd,int iLMIndex,int iSAIndex)
{
	ASSERT(iLMIndex==m_LocalMarkSubArea.size()-1);
	ASSERT(iSAIndex==m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA.size()-1);
	
	int ToolIndex = m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA[iSAIndex].GetSameToolIndex(crd.iToolNo);
	
	if(ToolIndex!=NOLINK)
	{
		m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA[iSAIndex].hcvHoleData[ToolIndex].hcvHolePos.push_back(Coord(crd.x,crd.y));
	}
	else
	{
		m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA[iSAIndex].hcvHoleData.push_back(HoleClass(crd.iToolNo));
		ToolIndex = m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA[iSAIndex].GetSameToolIndex(crd.iToolNo);
		m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA[iSAIndex].hcvHoleData[ToolIndex].hcvHolePos.push_back(Coord(crd.x,crd.y));
	}
}

void ExcellonData::AddM02OtherData(const HoleData& crd,int iSAIndex)
{
	ASSERT(iSAIndex==m_OtherSubArea.size()-1);
	
	int ToolIndex = m_OtherSubArea[iSAIndex].GetSameToolIndex(crd.iToolNo);
	
	if(ToolIndex!=NOLINK)
	{
		m_OtherSubArea[iSAIndex].hcvHoleData[ToolIndex].hcvHolePos.push_back(Coord(crd.x,crd.y));
	}
	else
	{
		m_OtherSubArea[iSAIndex].hcvHoleData.push_back(HoleClass(crd.iToolNo));
		ToolIndex = m_OtherSubArea[iSAIndex].GetSameToolIndex(crd.iToolNo);
		m_OtherSubArea[iSAIndex].hcvHoleData[ToolIndex].hcvHolePos.push_back(Coord(crd.x,crd.y));
	}
}

void ExcellonData::AddSAMainDataCenter(const HoleData& crd,int iSAIndex)
{
	ASSERT(iSAIndex==m_SubArea.size()-1);
	
	m_SubArea[iSAIndex].crdCenter=Coord(crd.x,crd.y);
}

void ExcellonData::AddM02LocalMarkDataCenter(const HoleData& crd,int iLMIndex,int iSAIndex)
{
	ASSERT(iLMIndex==m_LocalMarkSubArea.size()-1);
	ASSERT(iSAIndex==m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA.size()-1);
	
	m_LocalMarkSubArea[iLMIndex].m_LocalMarkSA[iSAIndex].crdCenter=Coord(crd.x,crd.y);
}

void ExcellonData::AddM02OtherDataCenter(const HoleData& crd,int iSAIndex)
{
	ASSERT(iSAIndex==m_OtherSubArea.size()-1);
	
	m_OtherSubArea[iSAIndex].crdCenter=Coord(crd.x,crd.y);
}

void ExcellonData::AddM02LocalMark(const HoleData& crd,int iLMIndex)
{
	ASSERT(iLMIndex==m_LocalMarkV.size()-1);
	
	m_LocalMarkV[iLMIndex].m_LocalMarkData.push_back(Coord(crd.x,crd.y));
}

void ExcellonData::AddSALocalMark(const HoleData& crd,int iSACycleNum)
{
	ASSERT(iSACycleNum==m_SALocalMarkV.size()-1);
	
	m_SALocalMarkV[iSACycleNum].m_LocalMarkData.push_back(Coord(crd.x,crd.y));
}

void ExcellonData::AddMainMark(const HoleData& crd)
{
	m_FiducialData.push_back(Coord(crd.x,crd.y));
	m_FiducialOffset.push_back(Coord(0,0));
}

void ExcellonData::AddInnerMark(const HoleData& crd)
{
	m_InnerFiducialData.push_back(Coord(crd.x,crd.y));
}

void ExcellonData::AddSAToolsInfo(const ToolInfo& tp)
{
	m_FileLayer.m_ToolInfo.push_back(tp);
}

void ExcellonData::AddSAMTextInfo(const HoleData& crd,int iDir,int iPos)
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_MachineSign.push_back(td);
}

void ExcellonData::AddSADTextInfo(const HoleData& crd,int iDir,int iPos)
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_DaySign.push_back(td);
}

void ExcellonData::AddSATTextInfo(const HoleData& crd,int iDir,int iPos)
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_TimeSign.push_back(td);
}

void ExcellonData::AddSALTextInfo(const HoleData& crd,int iDir,int iPos)
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_LotIdSign.push_back(td);
}

void ExcellonData::AddSAATextInfo(const HoleData& crd,int iDir,int iPos)//ly add 20121230
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_AxisNoSign.push_back(td);
}

void ExcellonData::AddSASCTextInfo(const HoleData& crd,int iDir,int iPos)//ly add 20131104
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_ScaleSign.push_back(td);
}

void ExcellonData::AddSASTextInfo(const HoleData& crd,CString str,int iDir,int iPos)
{
	TextData td;
	td.iToolNo=crd.iToolNo;
	td.m_strTextData=str;
	td.m_crdTextPos=Coord(crd.x,crd.y);
	td.m_iDirection=(TextDir)iDir;
	td.m_TextPosition=(TextPosition)iPos;
	m_StrTextSign.push_back(td);
}

HoleCoordV	ExcellonData::GetSALocalMark(int DataIndex) const
{
	return m_SALocalMarkV[DataIndex].m_LocalMarkData;
}

long ExcellonData::GetSALocalMarkDataCount() const
{
	return m_SALocalMarkV.size();
}

Coord ExcellonData::GetSALocalMarkDataPos(int DataIndex,int PosIndex)
{
	return m_SALocalMarkV[DataIndex].m_LocalMarkData[PosIndex];
}

Coord ExcellonData::GetSALocalAreaCenter(int nIndex) const
{
	ASSERT(nIndex<m_SALocalMarkV.size());	
	
	Coord crd=Coord();
	
	for(int n=0;n<GetSALocalMark(nIndex).size();++n)
	{
		crd+=m_SALocalMarkV[nIndex].m_LocalMarkData[n];			
	}
	crd/=GetSALocalMark(nIndex).size();
	
	return crd;
}

int ExcellonData::GetSALocalMarkProcStartIndex(int nIndex) const
{
	ASSERT(nIndex<m_SALocalMarkV.size());
	
	return m_SALocalMarkV[nIndex].m_iIndex;
}

void ExcellonData::AddGlvScanSize(int iScanSize)
{
	ASSERT(iScanSize>=SCANSIZEMIN&&iScanSize<=GetDoc().GetScanSizeMax());
	
	m_iGlvScanSize=iScanSize;
}

int ExcellonData::GetGlvScanSize() const
{
	return m_iGlvScanSize;
}

void ExcellonData::AddGlvScanBit(long iScanBit)//ly add 20130412
{
	m_lGlvScanBit=iScanBit;
}

long ExcellonData::GetGlvScanBit() const//ly add 20130412
{
	return m_lGlvScanBit;
}

void ExcellonData::AddSubAreaRowNum(int iNum)
{
	m_iSubAreaRow=iNum;
}

void ExcellonData::AddSubAreaColNum(int iNum)
{
	m_iSubAreaCol=iNum;
}

TextDir ExcellonData::GetStrTextSignDir(int index) const
{
	return m_StrTextSign[index].m_iDirection;
}

Coord ExcellonData::GetStrTextSignPos(int index) const
{	
	return m_StrTextSign[index].m_crdTextPos;
}

long ExcellonData::GetStrTextSignCount()const
{
	return m_StrTextSign.size();
}

TextPosition ExcellonData::GetStrTextPosition(int index) const
{
	return m_StrTextSign[index].m_TextPosition;
}

CString ExcellonData::GetStrText(int index) const
{
	return m_StrTextSign[index].m_strTextData;
}

void ExcellonData::DynamicSubArea(int lScanSize,double dbScale,AreaHoleV ahv,RECT rt,SubAreaV& sav)
{
	int ToolIndex,iWidth,iLength;
	URECT rect;
	HoleData hole;
	Coord crd0,crd,HoleCrd;
	bool bHasHole;
	int distance;
	int Row,Col;
	long startX,startY,endX,endY;
	
	std::vector<AreaHoleData>::iterator u;
	
	startX=rt.left;
	startY=rt.bottom;
	endX=rt.right;
	endY=rt.top;
	
	iWidth = endX-startX;
	iLength = endY-startY;
	
	if(iWidth==0)
	{
		Row=1;
	}
	else
	{
		Row = iWidth /(lScanSize) +(iWidth %(lScanSize)==0?0:1);
	}
	
	if(iLength==0)
	{
		Col=1;
	}
	else
	{
		Col = iLength/(lScanSize) +(iLength%(lScanSize)==0?0:1);
	}
	
	//	Row = iWidth /(lScanSize) +(iWidth %(lScanSize)==0?0:1);
	//	Col = iLength/(lScanSize) +(iLength%(lScanSize)==0?0:1);
	
	for( int i=0; i<Col ;++i)  // 行
	{
		for( int j=0; j<Row;++j)	// 列
		{
			sav.push_back(SubArea());
			bHasHole=false;
			rect.SetRect(j*lScanSize+startX,(i+1)*lScanSize+startY,(j+1)*lScanSize+startX,i*lScanSize+startY);
			
			crd.x = rect.CenterPoint().x;
			crd.y = rect.CenterPoint().y;
			
			do{
				ClearSubAreaIndex(sav,sav.size()-1);
				sav[sav.size()-1].crdCenter.x=crd.x;
				sav[sav.size()-1].crdCenter.y=crd.y;
				
				for(u = ahv.begin();u != ahv.end(); u++)
				{
					if(u->bSubarea)
						continue;
					
					hole.x = u->x;
					hole.y = u->y;
					hole.iToolNo = u->iToolNo;
					
					if(InSubArea(hole,crd.x-lScanSize/2,crd.y+lScanSize/2,crd.x+lScanSize/2,crd.y-lScanSize/2,
						j==Row-1,i==Col-1))
					{
						HoleCrd = Coord(-dbScale*(hole.y-crd.y)/1000,dbScale*(hole.x-crd.x)/1000);
						ToolIndex = sav[sav.size()-1].GetSameToolIndex(hole.iToolNo);
						if(ToolIndex!=NOLINK)
						{
							sav[sav.size()-1].hcvHoleData[ToolIndex].hcvHolePos.push_back(HoleCrd);
						}
						else
						{
							sav[sav.size()-1].hcvHoleData.push_back(HoleClass(hole.iToolNo));
							ToolIndex = sav[sav.size()-1].GetSameToolIndex(hole.iToolNo);
							sav[sav.size()-1].hcvHoleData[ToolIndex].hcvHolePos.push_back(HoleCrd);
						}
					}
				}
				
				crd0= GetSubAreaNewCenter(sav[sav.size()-1]);//bit //ly add 20111223
				
				crd0.x = crd0.x*1000/dbScale;//bit->um
				crd0.y = crd0.y*1000/dbScale;//bit->um
				
				crd=crd0 +sav[sav.size()-1].crdCenter;//um  新计算分区中心crd可能计入下一循环，必须存在
				
				distance=sqrt(pow(crd0.x,2)+pow(crd0.y,2));//-sav[sav.size()-1].crdCenter.x//-sav[sav.size()-1].crdCenter.y
			}while(distance>1000);
			
			for(u = ahv.begin();u != ahv.end(); u++)
			{
				if(u->bSubarea)
					continue;
				
				hole.x = u->x;
				hole.y = u->y;
				
				if(InSubArea(hole,sav[sav.size()-1].crdCenter.x-lScanSize/2,sav[sav.size()-1].crdCenter.y+lScanSize/2,
					sav[sav.size()-1].crdCenter.x+lScanSize/2,sav[sav.size()-1].crdCenter.y-lScanSize/2,
					j==Row-1,i==Col-1))
				{
					u->bSubarea=true;
					bHasHole=true;
				}
			}
			
			if(!bHasHole)
			{
				sav.pop_back();
			}
		}
    }
}

Coord ExcellonData::GetSubAreaNewCenter(SubArea sa) 
{
	long StartX,StartY,EndX,EndY;
	Coord crd;
	std::vector<HoleClass>::iterator hc; 
	
	StartX=99999999;		
	StartY=99999999;		
	EndX=-99999999;			
	EndY=-99999999;		
	
	for(hc = sa.hcvHoleData.begin();hc != sa.hcvHoleData.end();++hc)
	{
		for( int p=0;p<hc->hcvHolePos.size();++p)
		{  		  
			crd = hc->hcvHolePos[p];
			
			if(crd.y<StartX)
				StartX = crd.y;
			if(-crd.x<StartY)
				StartY = -crd.x;
			
			if(crd.y>EndX)
				EndX = crd.y;
			if(-crd.x>EndY)
				EndY = -crd.x;
		}
	}
	
	return Coord((StartX+EndX)/2,(StartY+EndY)/2);
}

void ExcellonData::ClearSubAreaIndex(SubAreaV& sav,int index)
{
	if(!sav[index].hcvHoleData.empty())
	{
		sav[index].hcvHoleData.clear();
	}
}

long ExcellonData::GetOtherSubAreaHoleCount(int iSubAreaNo) //const
{
	ASSERT(iSubAreaNo<m_OtherSubArea.size());	
	std::vector<HoleClass>::iterator hc;
	int nHoleCount =0;
	for(hc= m_OtherSubArea[iSubAreaNo].hcvHoleData.begin();hc!=m_OtherSubArea[iSubAreaNo].hcvHoleData.end();hc++ )
	{
		nHoleCount+= hc->hcvHolePos.size();
		TRACE1("--HoleCnt:%d\n",hc->hcvHolePos.size());
	}
    return nHoleCount;
	//	return m_SubArea[iSubAreaNo].hcvHoleData.size();
}