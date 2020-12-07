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

//ԭʼ�ļ�����ʱ��������ݽṹ����----------------------------------------------//
//M25�����ݽṹ
struct BlockDataInfo
{
	HolePositionV  m_BlockData;		//�����ݼ��ϣ��״�С�Ϳ�����
	int  m_iBlockIndex;				//�������� m_FileLayer.m_HoleBlockData[Index]

	CRD  m_iStartX;					//���½�X����
	CRD  m_iEndX;					//���Ͻ�X����
	CRD  m_iStartY;					//���½�Y����
	CRD  m_iEndY;					//���Ͻ�Y����	

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

//�ǿ����ݽṹ
struct NoBlockDataInfo
{
	HolePositionV  m_NoBlockData;	//�����ݼ��ϣ��״�С�Ϳ�����

	CRD  m_iStartX;					//���½�X����
	CRD  m_iEndX;					//���Ͻ�X����
	CRD  m_iStartY;					//���½�Y����
	CRD  m_iEndY;					//���Ͻ�Y����	

	NoBlockDataInfo()	
	{		
		m_iStartX=99999999;		
		m_iEndX=-99999999;			
		m_iStartY=99999999;		
		m_iEndY=-99999999;			 		
	}
};
		
typedef int MirrorMode;				//�����ϵ
typedef std::vector<MirrorMode> MirrorModeV;

//��ϵ���ݽṹ
struct BlockRelation
{
	CRD  m_iOffsetX;         		//��ƫ��ֵX
	CRD  m_iOffsetY;				//��ƫ��ֵY
	MirrorModeV	 m_iMirrorMode;		//�����ϵ����

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

//���ϵ���ݽṹ
struct BlockLinkInfo
{
	int m_iBlockIndex;				//�������ţ���BlockDataInfo:: m_iBlockIndex�൱
	BlockRelationV m_pSubBlock;		//M02���ϵ����

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

//LocalMark���ݽṹ
struct LocalMarkInfo
{
	int m_iBlockIndex;				//�������ţ���BlockDataInfo:: m_iBlockIndex�൱
	HoleCoordV m_LocalMark;			//LocalMark������꼯��
};

enum DataMode{ERRORDATA=-1,HOLEDATA,MACHINENOH,DATENOH,TIMENOH,LOTIDNOH,STRINGH,
		MACHINENOV,DATENOV,TIMENOV,LOTIDNOV,STRINGV,AXISNOH,AXISNOV,SCALEH,SCALEV};		//�ַ�����

//�ַ����ݽṹ
struct TextInfo   
{
	int m_iBlockIndex;				//�������ţ���BlockDataInfo:: m_iBlockIndex�൱
	int iToolNum;					//�ַ���С�����ߺ�
	CString m_strText;				//�ַ�����
	Coord	m_TextPos;				//�ַ�����λ��
	DataMode m_textmode;			//�ַ�����

	TextInfo()
	{
		m_strText="";
	}
};

//�������ݽṹ
struct ToolInfo
{
	int m_nToolIndex;				//���ߺ�
	double m_nToolX;				//���ߴ�СX
//	double m_nToolY;				//���ߴ�СY

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

//ԭʼ�ļ���Ϣ�ṹ
struct FileLayerInfo
{		
	BlockDataInfoV  m_HoleBlockData;		//M25�鼯��
	BlockLinkInfoV  m_LinkInfo;				//M02�鼯��
	ToolInfoV		m_ToolInfo;				//������Ϣ����
	TextInfoV		m_TextInfo;				//�ַ���Ϣ����
	NoBlockDataInfo m_ScatteredHole;		//�ǿ���Ϣ

	LocalMarkInfo	m_LocalMarkInfo;		//LocalMark��Ϣ

	CRD  m_iLayerStartX;					//ͼ���������½�X
	CRD  m_iLayerEndX;						//ͼ���������½�X
	CRD  m_iLayerStartY;					//ͼ���������½�Y
	CRD  m_iLayerEndY;						//ͼ���������½�Y
	
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

		return NOLINK;  //û�ҵ�
	}
};
//------------------------------------------------------------------------------//

//�ӹ�ʱLocalMark�����Ϣ
struct LocalMarkData
{
	int m_iIndex;						//������
	HoleCoordV m_LocalMarkData;			//LocalMark������꼯��

	CRD  m_iStartX;						//���½�X����
	CRD  m_iEndX;						//���Ͻ�X����
	CRD  m_iStartY;						//���½�Y����
	CRD  m_iEndY;						//���Ͻ�Y����

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

//�ӹ�ʱ�ַ������Ϣ
struct TextData   
{
	int iToolNo;							//�ַ����ߺ�
	CString m_strTextData;					//�ַ�����
	Coord	m_crdTextPos;					//�ַ�����λ��
	TextDir		m_iDirection;				//�ַ��ӹ�����
	TextPosition    m_TextPosition;         //�ַ��ӹ�λ��

	TextData()
	{
		m_strTextData="";
	    m_TextPosition = LEFTBOTTOM;
	}
};

//�ӹ�ʱ����������ݽṹ����----------------------------------------------------//

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
	Coord	   crdCenter;		//���������ĵ�
	HoleCrdV   hcvHoleData;		//�����еĵ�λ��Ϣ

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

//LocalMark��ʽ�ӹ�ʱ���������Ϣ
struct LocalMarkSubArea
{
	int  m_iLocalMarkIndex;			//LocalMark���������ţ���LocalMarkData:: m_iIndex�൱
	SubAreaV m_LocalMarkSA;			//LocalMark��������

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
	long DistrbuteSubAreaRotReverse();		//��ʱ����ת90
	long DistrbuteLocalMarkSubArea(int lScanSize,double dbScale);
	long DistrbuteOtherSubArea(int lScanSize,double dbScale);

	void OptimizePath(SubAreaV& sav);
	BOOL SADataTransSave(FILE* fp,int lScanSize,long lScanBit);
	void MirrorY(CRD& length,CRD& Min);		//��Y�᾵��				//20161109		
	void Rotate90();						//��ʱ��90����ת
	void Rotate180();						//��ʱ��180����ת
	void Rotate270();						//��ʱ��270����ת

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

//������������������ԭʼ�ļ�����ʱ����洢����������������

	void AddBlockDataInfo(const HoleData& crd,int iBlockIndex);									//�������
	void AddNoBlockDataInfo(const HoleData& crd);												//�ǿ������
	void AddBlockLinkInfo(const HoleData& crd,int iBlockIndex,int iLinkIndex,MirrorModeV mmode);//���ϵ
	void AddToolsInfo(const ToolInfo& tp);														//������Ϣ
    void AddFiducialData(const HoleData& crd);													//���б�����
	void AddInnerFiducialData(const HoleData& crd);												//InnerMark
	void AddLocalMarkInfo(const HoleData& crd,int iBlockIndex);									//LocalMard����
	void AddTextInfo(const HoleData& crd,DataMode dmode,CString str,int iBlockIndex=-1);		//�ַ���Ϣ
	void AddBlockData(int iBlockIndex);															//���ӿ�
	bool MakeAssistantData();																	//����LocalMark���ַ��ӹ�����
	TextDir GetTextDirection(CRD posx,CRD posy,CRD vx,CRD vy);									//��ȡ���ּӹ�������Ϣ
	TextPosition GetTextPositon(CRD posx,CRD posy,CRD vx,CRD vy,TextDir dir);					//��ȡ���ּӹ�λ����Ϣ
	TextPosition GetMirrorTextPositon(TextDir td,TextPosition tp);								//��ȡ������ַ��ӹ�����
	TextDir GetRotateTextDir(TextDir td,int Rotatetype=0);										//��ȡ��ת���ַ��ӹ�����
	TextPosition GetRotateTextPositon(TextDir td,TextPosition tp,int Rotatetype=0);				//��ȡ��ת���ַ��ӹ�λ��

//������������������SA�ļ�����ʱ����洢������������������
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
//�ļ�������õ��������ļ���Ϣ
	FileLayerInfo   m_FileLayer;     				
											
//�ӹ�ʱ�õ��ĸ���������Ϣ
	int m_iGlvScanSize;								//��ɨ�������С
	long m_lGlvScanBit;								//�񾵱�������
	int	m_iSubAreaRow;	 							//����ӹ�ʱ��������
	int	m_iSubAreaCol;	 							//����ӹ�ʱ��������

	HoleCoordV   	m_FiducialData;  				//�����
	HoleCoordV   	m_FiducialOffset;				//�����ƫ����
	HoleCoordV		m_InnerFiducialData;			//�ڲ���

	TextDataV		m_MachineSign;   				//������
	TextDataV		m_DaySign;						//���ں�
	TextDataV		m_TimeSign;						//ʱ���
	TextDataV		m_LotIdSign;     				//LotID��  
	TextDataV		m_AxisNoSign;     				//���
	TextDataV		m_ScaleSign;     				//����ֵ
	TextDataV		m_StrTextSign;     				//�ַ���

	SubAreaV		m_SubArea;						//����ӹ�ʱ��������

	LocalMarkV		m_LocalMarkV;					//LocalMark�ӹ�ʱ�ֲ���м���
	LocalMarkSubAreaV	m_LocalMarkSubArea;			//LocalMark�ӹ�ʱ�ֲ���������
	SubAreaV		m_OtherSubArea;					//LocalMark�ӹ�ʱ������������

	LocalMarkV		m_SALocalMarkV;					//�����ֲ��ӹ�ʱ�ֲ���м���
};

#endif // !defined(AFX_EXCELLON_H__82717E2C_CB9B_4FE4_BAB5_D7D7C023469A__INCLUDED_)


