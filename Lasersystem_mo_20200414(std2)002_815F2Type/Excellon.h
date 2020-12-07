// Excellon.h: interface for the Excellon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELLON_H__82717E2C_CB9B_4FE4_BAB5_D7D7C023469A__INCLUDED_)
#define AFX_EXCELLON_H__82717E2C_CB9B_4FE4_BAB5_D7D7C023469A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"

enum TextDir{HorizontalText, VerticalText};
enum TextPosition{LEFTBOTTOM,LEFTTOP,RIGHTTOP,RIGHTBOTTOM};

void SetGlobalExcellonIndex(int index);								//20161109
int GetGlobalExcellonIndex();

//原始文件分析时的相关数据结构定义----------------------------------------------//
//M25块数据结构
struct BlockDataInfo
{
	HolePositionV  m_BlockData;		//孔数据集合：孔大小和孔坐标
	int  m_iBlockIndex;				//块索引号 m_FileLayer.m_HoleBlockData[Index]

	CRD  m_iStartX;					//左下角X坐标
	CRD  m_iEndX;					//右上角X坐标
	CRD  m_iStartY;					//左下角Y坐标
	CRD  m_iEndY;					//右上角Y坐标	

	BlockDataInfo()	
	{		
		m_iStartX=99999999;		
		m_iEndX=-99999999;			
		m_iStartY=99999999;		
		m_iEndY=-99999999;

		m_iBlockIndex=-1;			 		
	}

	BlockDataInfo& operator=(const BlockDataInfo& bdi)
	{
		if(this==&bdi)
			return *this;

		this->m_iStartX = bdi.m_iStartX;	
		this->m_iEndX   = bdi.m_iEndX;		
		this->m_iStartY = bdi.m_iStartY;	
		this->m_iEndY   = bdi.m_iEndY;			
   
		this->m_iBlockIndex = bdi.m_iBlockIndex;			
            
		if(!bdi.m_BlockData.empty())
            this->m_BlockData = bdi.m_BlockData;

		return *this;
	}
};

//非块数据结构
struct NoBlockDataInfo
{
	HolePositionV  m_NoBlockData;	//孔数据集合：孔大小和孔坐标

	CRD  m_iStartX;					//左下角X坐标
	CRD  m_iEndX;					//右上角X坐标
	CRD  m_iStartY;					//左下角Y坐标
	CRD  m_iEndY;					//右上角Y坐标	

	NoBlockDataInfo()	
	{		
		m_iStartX=99999999;		
		m_iEndX=-99999999;			
		m_iStartY=99999999;		
		m_iEndY=-99999999;			 		
	}
};
		
typedef int MirrorMode;				//镜像关系
typedef std::vector<MirrorMode> MirrorModeV;

//关系数据结构
struct BlockRelation
{
	CRD  m_iOffsetX;         		//块偏移值X
	CRD  m_iOffsetY;				//块偏移值Y
	MirrorModeV	 m_iMirrorMode;		//镜像关系集合

	BlockRelation()
	{
		m_iOffsetX    = 0;         
		m_iOffsetY    = 0;
	}

    BlockRelation& operator=(const BlockRelation& br)
	{
		if(this==&br)
			return *this;

		this->m_iOffsetX = br.m_iOffsetX;
		this->m_iOffsetY = br.m_iOffsetY;
		this->m_iMirrorMode = br.m_iMirrorMode;

		return *this;
	}
};

typedef std::vector<BlockRelation> BlockRelationV;

//块关系数据结构
struct BlockLinkInfo
{
	int m_iBlockIndex;				//块索引号，与BlockDataInfo:: m_iBlockIndex相当
	BlockRelationV m_pSubBlock;		//M02块关系集合

	BlockLinkInfo()
	{
		m_iBlockIndex=-1;
	}
	
    BlockLinkInfo& operator=(const BlockLinkInfo& bli)
	{
		if(this==&bli)
			return *this;

		this->m_iBlockIndex = bli.m_iBlockIndex;
		if(!bli.m_pSubBlock.empty())
			this->m_pSubBlock = bli.m_pSubBlock;
        
		return *this;
	}
};

//LocalMark数据结构
struct LocalMarkInfo
{
	int m_iBlockIndex;				//块索引号，与BlockDataInfo:: m_iBlockIndex相当
	HoleCoordV m_LocalMark;			//LocalMark标靶坐标集合
};

enum DataMode{ERRORDATA=-1,HOLEDATA,MACHINENOH,DATENOH,TIMENOH,LOTIDNOH,STRINGH,
		MACHINENOV,DATENOV,TIMENOV,LOTIDNOV,STRINGV,AXISNOH,AXISNOV,SCALEH,SCALEV};		//字符属性

//字符数据结构
struct TextInfo   
{
	int m_iBlockIndex;				//块索引号，与BlockDataInfo:: m_iBlockIndex相当
	int iToolNum;					//字符大小：刀具号
	CString m_strText;				//字符内容
	Coord	m_TextPos;				//字符坐标位置
	DataMode m_textmode;			//字符属性

	TextInfo()
	{
		m_strText="";
	}
};

//刀具数据结构
struct ToolInfo
{
	int m_nToolIndex;				//刀具号
	double m_nToolX;				//刀具大小X
//	double m_nToolY;				//刀具大小Y

	ToolInfo()
	{
		 m_nToolIndex=0;
		 m_nToolX = 0;
//		 m_nToolY = 0;
	}

	ToolInfo& operator=(const ToolInfo& rht)
	{
		this->m_nToolX = rht.m_nToolX;
//		this->m_nToolY = rht.m_nToolY;
		this->m_nToolIndex = rht.m_nToolIndex;

		return *this;
	}
};

typedef std::vector<BlockDataInfo> BlockDataInfoV;
typedef std::vector<BlockLinkInfo> BlockLinkInfoV;
typedef std::vector<ToolInfo>     ToolInfoV;
typedef std::vector<TextInfo>     TextInfoV;

//原始文件信息结构
struct FileLayerInfo
{		
	BlockDataInfoV  m_HoleBlockData;		//M25块集合
	BlockLinkInfoV  m_LinkInfo;				//M02块集合
	ToolInfoV		m_ToolInfo;				//刀具信息集合
	TextInfoV		m_TextInfo;				//字符信息集合
	NoBlockDataInfo m_ScatteredHole;		//非块信息

	LocalMarkInfo	m_LocalMarkInfo;		//LocalMark信息

	CRD  m_iLayerStartX;					//图层数据左下角X
	CRD  m_iLayerEndX;						//图层数据右下角X
	CRD  m_iLayerStartY;					//图层数据左下角Y
	CRD  m_iLayerEndY;						//图层数据右下角Y
	
	CRD	 m_iBlockRefX;
	CRD	 m_iBlockRefY;

	FileLayerInfo()
	{
		m_iLayerStartX = 99999999;	
		m_iLayerEndX   =-99999999;	
		m_iLayerStartY = 99999999;	
		m_iLayerEndY   =-99999999;

		m_iBlockRefX=0;
		m_iBlockRefY=0;
	}

public:
	BOOL IsLinked(int iBlockIndex) const
	{
		for(int i=0; i<m_LinkInfo.size(); ++i)
		{
			if(m_LinkInfo[i].m_iBlockIndex == iBlockIndex)
				return TRUE;						
		}

		return FALSE;
	}

	int GetSameLinkIndex(int iBlockIndex) const
	{
		for(int i=0; i<m_LinkInfo.size(); ++i)
		{
			if(m_LinkInfo[i].m_iBlockIndex == iBlockIndex)
				return i;						
		}

		return NOLINK;  //没找到
	}
};
//------------------------------------------------------------------------------//

//加工时LocalMark相关信息
struct LocalMarkData
{
	int m_iIndex;						//索引号
	HoleCoordV m_LocalMarkData;			//LocalMark标靶坐标集合

	CRD  m_iStartX;						//左下角X坐标
	CRD  m_iEndX;						//右上角X坐标
	CRD  m_iStartY;						//左下角Y坐标
	CRD  m_iEndY;						//右上角Y坐标

	LocalMarkData()
	{
		m_iStartX=99999999;		
		m_iEndX=-99999999;			
		m_iStartY=99999999;		
		m_iEndY=-99999999;
		m_iIndex=-1;			
	}
	
	LocalMarkData& operator=(const LocalMarkData &lmd)
	{
		if(this==&lmd)
			return *this;

		this->m_iIndex  = lmd.m_iIndex;			

		if(!lmd.m_LocalMarkData.empty())
			this->m_LocalMarkData = lmd.m_LocalMarkData;

		return *this;
	}
};

//加工时字符相关信息
struct TextData   
{
	int iToolNo;							//字符刀具号
	CString m_strTextData;					//字符内容
	Coord	m_crdTextPos;					//字符坐标位置
	TextDir		m_iDirection;				//字符加工方向
	TextPosition    m_TextPosition;         //字符加工位置

	TextData()
	{
		m_strTextData="";
	    m_TextPosition = LEFTBOTTOM;
	}
};

//加工时分区相关数据结构定义----------------------------------------------------//

struct HoleClass
{
   
	int nToolNo;
    HoleCoordV  hcvHolePos;

	HoleClass(int nT=0)
	{
       nToolNo =nT;
	}   
};

typedef std::vector<HoleClass> HoleCrdV;

struct SubArea
{
	Coord	   crdCenter;		//分区的中心点
	HoleCrdV   hcvHoleData;		//分区中的点位信息

public:
	int GetToolsCount()
	{
         return hcvHoleData.size();
	}

    int GetSameToolIndex(int iToolIndex) const
    {
	  for(int i=0; i<hcvHoleData.size(); ++i)
	  {
		if(hcvHoleData[i].nToolNo == iToolIndex)
			return i;						
	  }
	  return NOLINK; 
	}

   	int operator<(const SubArea& right) 
	{
		if(this->crdCenter.y != right.crdCenter.y)
			return this->crdCenter.y < right.crdCenter.y;
		else
			return this->crdCenter.x < right.crdCenter.x;
	}
};

typedef std::vector<SubArea>	   SubAreaV;

//LocalMark方式加工时分区相关信息
struct LocalMarkSubArea
{
	int  m_iLocalMarkIndex;			//LocalMark分区索引号，与LocalMarkData:: m_iIndex相当
	SubAreaV m_LocalMarkSA;			//LocalMark分区集合

	LocalMarkSubArea()
	{
		m_iLocalMarkIndex=-1;			
	}
	
	LocalMarkSubArea& operator=(const LocalMarkSubArea &lms)
	{
		if(this==&lms)
			return *this;

		this->m_iLocalMarkIndex  = lms.m_iLocalMarkIndex;			

		if(!lms.m_LocalMarkSA.empty())
			this->m_LocalMarkSA = lms.m_LocalMarkSA;

		return *this;
	}
};

//------------------------------------------------------------------------------//

typedef std::vector<TextData>  TextDataV;
typedef std::vector<LocalMarkData> LocalMarkV;
typedef std::vector<LocalMarkSubArea>  LocalMarkSubAreaV;

struct ThreadParams																//20190820
{
	SubAreaV* sav;
    int nIndex;
	int nThreadCount;															//20200422
};

class ExcellonData
{
public:
	friend DWORD WINAPI StartAddress(LPVOID lpParameter);						//20190820
public:
	long DistrbuteSubArea(int lScanSize,double dbScale,BOOL isJudgeFileLimits=TRUE);
	long DistrbuteSubAreaRotReverse();		//逆时针旋转90
	long DistrbuteLocalMarkSubArea(int lScanSize,double dbScale);
	long DistrbuteOtherSubArea(int lScanSize,double dbScale);

	void OptimizePath(SubAreaV& sav);
	BOOL SADataTransSave(FILE* fp,int lScanSize,long lScanBit);
	void MirrorY(CRD& length,CRD& Min);		//沿Y轴镜像				//20161109		
	void Rotate90();						//逆时针90度旋转
	void Rotate180();						//逆时针180度旋转
	void Rotate270();						//逆时针270度旋转

	SubAreaV& GetSubArea();
	SubAreaV& GetLocalMarkSubArea(int nIndex);
	SubAreaV& GetOtherSubArea();
	void SortSubArea(SubAreaV& sav);
	void SortSubArea(SubAreaV& sav,int nSaIndex);

	void CheckFileRange();
	BOOL CompareXAndY();

	void ClearSubArea();
	void ClearSubAreaIndex(SubAreaV& sav,int index);
	void ClearAll();

	Coord GetSubAreaCenter(int iSubAreaNo) const;
	SubArea& GetSubAreaData(int nIndex) ;
	long GetSubAreaHoleCount( int iSubAreaNo );
	long GetSubAreaRow() const;
	long GetSubAreaCol() const;
	long GetSubAreaCnt() const;
	BOOL GetSubAreaIsEmpty(int iSubArea) const;

	Coord GetLayerCenter()const;
	Coord GetInnerLayerCenter() const;
	CRD GetLayerHeight() const;
	CRD GetLayerWidth() const;
	CRD GetLayerEndY() const;
	CRD GetLayerEndX() const;
	CRD GetLayerStartY() const;
	CRD GetLayerStartX() const;

	void SetLayerEndY(CRD temp);
	void SetLayerEndX(CRD temp);
	void SetLayerStartY(CRD temp);
	void SetLayerStartX(CRD temp);

//MachineSign
	TextDir GetMachineSignDir(int index=0) const;
	Coord GetMachineSignPos(int index=0) const;
	long GetMachineSignCount() const;
	TextPosition GetMachineTextPosition(int index=0) const;

//DaySign
	TextDir GetDaySignDir(int index=0) const;
	Coord GetDaySignPos(int index=0) const;
	long GetDaySignCount()const;
	TextPosition GetDayTextPosition(int index=0) const;

//TimeSign	
	TextDir GetTimeSignDir(int index=0) const;
	Coord GetTimeSignPos(int index=0) const;
	long GetTimeSignCount()const;
	TextPosition GetTimeTextPosition(int index=0) const;

//LotIDSign
	TextDir GetLotIDSignDir(int index) const;
	Coord GetLotIDSignPos(int index) const;
	long GetLotIDSignCount()const;
	TextPosition GetLotIDTextPosition(int index) const;

//AxisNoSign
	TextDir GetAxisNoSignDir(int index) const;
	Coord GetAxisNoSignPos(int index) const;
	long GetAxisNoSignCount()const;
	TextPosition GetAxisNoTextPosition(int index) const;

//ScaleSign
	TextDir GetScaleSignDir(int index) const;
	Coord GetScaleSignPos(int index) const;
	long GetScaleSignCount()const;
	TextPosition GetScaleTextPosition(int index) const;

//StrTextSign
	TextDir GetStrTextSignDir(int index) const;
	Coord GetStrTextSignPos(int index) const;
	long GetStrTextSignCount()const;
	TextPosition GetStrTextPosition(int index) const;
	CString GetStrText(int index) const;

//FiducialData
	HoleCoordV GetFiducial() const;
    Coord GetFiducialPos(long lIndex=0)const;
	long GetFiducialNum() const;
	void SortFiducialData();

//InnerMark
	HoleCoordV GetInnerFiducial() const;
    Coord GetInnerFiducialPos(long lIndex=0)const;
	long GetInnerFiducialNum() const;
	void SortInnerFiducialData();

//LocalMark
	HoleCoordV GetLocalMark(int DataIndex) const;
	Coord GetLocalMarkDataPos(int DataIndex,int PosIndex);
	long GetLocalMarkNum() const;
	long GetLocalMarkDataCount() const;
	void SortLocalMarkData();

	BOOL GetLocalMarkSubAreaIsEmpty(int nIndex,int iSubArea) const;
	BOOL GetOtherSubAreaIsEmpty(int iSubArea) const;
	long GetLocalMarkSubAreaCnt(int nIndex) const;
	long GetOtherSubAreaCnt() const;
	long GetOtherSubAreaHoleCount( int iSubAreaNo );
	
	SubArea& GetLocalMarkSubAreaData(int nIndex,int iSubArea);
	SubArea& GetOtherSubAreaData(int iSubArea);
	long GetLocalMarkSubAreaHoleCount(int nIndex,int iSubAreaNo);
	Coord GetLocalMarkSubAreaCenter(int nIndex,int iSubArea) const;
	Coord GetOtherSubAreaCenter(int iSubArea) const;
	Coord GetLocalAreaCenter(int nIndex)const;

	void ClearLocalMarkSubArea();
	void ClearOtherSubArea();

//Tools
	long GetToolsNum() const;
	ToolInfo GetToolInfo(int nToolIndex) const;

//SALocalMark
	HoleCoordV	GetSALocalMark(int DataIndex) const;
	Coord GetSALocalMarkDataPos(int DataIndex,int PosIndex);
	long GetSALocalMarkDataCount() const;
	BOOL SortSALocalMarkData();

	Coord GetSALocalAreaCenter(int nIndex) const;
	int GetSALocalMarkProcStartIndex(int nIndex) const;

//－－－－－－－－－原始文件分析时分类存储－－－－－－－－

	void AddBlockDataInfo(const HoleData& crd,int iBlockIndex);									//块孔数据
	void AddNoBlockDataInfo(const HoleData& crd);												//非块孔数据
	void AddBlockLinkInfo(const HoleData& crd,int iBlockIndex,int iLinkIndex,MirrorModeV mmode);//块关系
	void AddToolsInfo(const ToolInfo& tp);														//刀具信息
    void AddFiducialData(const HoleData& crd);													//主靶标数据
	void AddInnerFiducialData(const HoleData& crd);												//InnerMark
	void AddLocalMarkInfo(const HoleData& crd,int iBlockIndex);									//LocalMard数据
	void AddTextInfo(const HoleData& crd,DataMode dmode,CString str,int iBlockIndex=-1);		//字符信息
	void AddBlockData(int iBlockIndex);															//增加块
	bool MakeAssistantData();																	//生成LocalMark及字符加工数据
	TextDir GetTextDirection(CRD posx,CRD posy,CRD vx,CRD vy);									//获取文字加工方向信息
	TextPosition GetTextPositon(CRD posx,CRD posy,CRD vx,CRD vy,TextDir dir);					//获取文字加工位置信息
	TextPosition GetMirrorTextPositon(TextDir td,TextPosition tp);								//获取镜像后字符加工方向
	TextDir GetRotateTextDir(TextDir td,int Rotatetype=0);										//获取旋转后字符加工方向
	TextPosition GetRotateTextPositon(TextDir td,TextPosition tp,int Rotatetype=0);				//获取旋转后字符加工位置

//－－－－－－－－－SA文件分析时分类存储－－－－－－－－－
	void AddLMInfo(int iLMIndex);
	void AddSMInfo(int iSMIndex);
	void AddSAMainInfo();
	void AddSAM02OtherInfo();
	void AddSAM02LocalMarkInfo(int iLMIndex);
	void AddSAMainData(const HoleData& crd,int iSAIndex);
	void AddM02LocalMarkData(const HoleData& crd,int iLMIndex,int iSAIndex);
	void AddM02OtherData(const HoleData& crd,int iSAIndex);
	void AddSAMainDataCenter(const HoleData& crd,int iSAIndex);
	void AddM02LocalMarkDataCenter(const HoleData& crd,int iLMIndex,int iSAIndex);
	void AddM02OtherDataCenter(const HoleData& crd,int iSAIndex);
	void AddM02LocalMark(const HoleData& crd,int iLMIndex);
	void AddSALocalMark(const HoleData& crd,int iSACycleNum);
	void AddMainMark(const HoleData& crd);
	void AddInnerMark(const HoleData& crd);
	void AddSAToolsInfo(const ToolInfo& tp);
	void AddSAMTextInfo(const HoleData& crd,int iDir,int iPos);
	void AddSADTextInfo(const HoleData& crd,int iDir,int iPos);
	void AddSATTextInfo(const HoleData& crd,int iDir,int iPos);
	void AddSALTextInfo(const HoleData& crd,int iDir,int iPos);
	void AddSAATextInfo(const HoleData& crd,int iDir,int iPos);
	void AddSASCTextInfo(const HoleData& crd,int iDir,int iPos);
	void AddSASTextInfo(const HoleData& crd,CString str,int iDir,int iPos);
	void AddGlvScanSize(int iScanSize);
	void AddGlvScanBit(long iScanBit);
	int  GetGlvScanSize() const;
	long GetGlvScanBit() const;
	void AddSubAreaRowNum(int iNum);
	void AddSubAreaColNum(int iNum);
//----------------------------------------------------
	ExcellonData();
	virtual ~ExcellonData();

	friend ExcellonData& GetExcellonData();
            
private:
	BOOL InSubArea(const HoleData& hole, long lLx,long lTy,long lRx,long lBy, BOOL bInX, BOOL bInY);
	Coord GetSubAreaNewCenter(SubArea sa);
	void DynamicSubArea(int lScanSize,double dbScale,AreaHoleV ahv,RECT rt,SubAreaV& sav);

private:
//文件分析后得到的整个文件信息
	FileLayerInfo   m_FileLayer;     				
											
//加工时用到的各种数据信息
	int m_iGlvScanSize;								//振镜扫描分区大小
	long m_lGlvScanBit;								//振镜比例因子
	int	m_iSubAreaRow;	 							//整板加工时分区行数
	int	m_iSubAreaCol;	 							//整板加工时分区列数

	HoleCoordV   	m_FiducialData;  				//主标靶
	HoleCoordV   	m_FiducialOffset;				//主标靶偏移量
	HoleCoordV		m_InnerFiducialData;			//内层标靶

	TextDataV		m_MachineSign;   				//机器号
	TextDataV		m_DaySign;						//日期号
	TextDataV		m_TimeSign;						//时间号
	TextDataV		m_LotIdSign;     				//LotID号  
	TextDataV		m_AxisNoSign;     				//轴号
	TextDataV		m_ScaleSign;     				//涨缩值
	TextDataV		m_StrTextSign;     				//字符串

	SubAreaV		m_SubArea;						//整板加工时分区集合

	LocalMarkV		m_LocalMarkV;					//LocalMark加工时局部标靶集合
	LocalMarkSubAreaV	m_LocalMarkSubArea;			//LocalMark加工时局部分区集合
	SubAreaV		m_OtherSubArea;					//LocalMark加工时其他分区集合

	LocalMarkV		m_SALocalMarkV;					//分区局部加工时局部标靶集合
};

#endif // !defined(AFX_EXCELLON_H__82717E2C_CB9B_4FE4_BAB5_D7D7C023469A__INCLUDED_)


