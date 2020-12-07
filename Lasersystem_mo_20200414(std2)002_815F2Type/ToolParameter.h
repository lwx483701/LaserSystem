// ToolParameter.h: interface for the ToolParameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLPARAMETER_H__9B5B2164_7EE4_4C81_9F14_95993DD67A09__INCLUDED_)
#define AFX_TOOLPARAMETER_H__9B5B2164_7EE4_4C81_9F14_95993DD67A09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

struct Energy
{
public:
	Energy()
	{
		m_iPeriod = 200;
		m_iRelease =15;
	}
	Energy(int iPeriod,int iRelease)
	{
		m_iPeriod = iPeriod;
		m_iRelease = iRelease;
	}
	Energy& operator =(const Energy &eng);
	int m_iPeriod;
	int m_iRelease;
};

struct LayerToolPara
{
	typedef std::vector<Energy> EnergyV;
	enum DRILLMODE{BModel=0,CModel,BCModel,CBModel};
//private:
    int m_iDrillMode;			//加工方式
    int m_iFocusOffset;			
    EnergyV m_pEBEnergy;
	EnergyV m_pECEnergy;
public:
	BOOL InsertCycEnergy(const int& iCNo,const Energy& ePara);
	BOOL InsertBstEnergy(const int& iBNo, const Energy& ePara);
	void RemoveCycEnergy(const int& iCNo);
	void RemoveBstEnergy(const int& iBNo);
	const Energy& GetCycEnergy(const int& iCNo)const;
	const Energy& GetBstEnergy(const int& iCNo)const;
	BOOL SetBstEnergy(const int& iBNo,const Energy& ePara);
	BOOL SetCycEnergy(const int& iCNo,const Energy& ePara);
	void SetFocusOffset(const int& iOffset);
	void SetDrillMode(const int iMode);
	int  GetFocusOffset() const;
	int  GetDrillMode()   const;
	int  GetCycleNum()    const;
	int  GetBurstNum()    const;

	LayerToolPara& operator=(const LayerToolPara& rht);
	LayerToolPara()
	{
        m_iDrillMode   = 1;  //    加工方式
        m_iFocusOffset = 0;
	}
	LayerToolPara(const int& iDrillMode,const int& iFocusOffset)
				:m_iDrillMode(iDrillMode),m_iFocusOffset(iFocusOffset)
	{}
};
/*
struct UserToolPara
{
	typedef std::vector<LayerToolPara> LayerToolParaV;
//private:
	int m_iToolNo;
	int	m_iDiameter;
    int m_iApertureNo;
	LayerToolParaV m_subToolPara;
public:
	int GetLayerNum()const;
	int GetDiameter()const;
	int GetToolNo() const;
	BOOL SetLayerToolPara(const int& iWhichLayer,const LayerToolPara& ltp);
	void RemoveLayerToolPara(const int& iWhichLayer);
	const LayerToolPara& GetLayerToolPara(const int& iWhichLayer)const;
	BOOL InsertLayerToolPara(const int& iLayer, const LayerToolPara& ltp);
	UserToolPara(){
		m_iDiameter    = 125;
		m_iApertureNo  = 12;
		m_iToolNo = 11;
    }
	UserToolPara(const int& iToolNo,const int& iDiameter,const int& iAperture)
		:m_iDiameter(iDiameter),m_iApertureNo(iAperture),m_iToolNo(iToolNo)
	{}

	~UserToolPara(){
	}
	void SetApertureNo(const int& iAptNo);
	int  GetApertureNo()const;
	UserToolPara& operator=(const UserToolPara& tp);
	LayerToolPara& operator[](const int& iWhichLayer) ;
};
*/

struct UserToolPara
{
	typedef std::vector<LayerToolPara> LayerToolParaV;
//private:
	int m_iToolNo;
	int	m_iDiameter;
    int m_iApertureNo;
	int m_iSubApertureNo;
	LayerToolParaV m_subToolPara;
public:
	int GetLayerNum()const;
	int GetDiameter()const;
	int GetToolNo() const;
	BOOL SetLayerToolPara(const int& iWhichLayer,const LayerToolPara& ltp);
	void RemoveLayerToolPara(const int& iWhichLayer);
	const LayerToolPara& GetLayerToolPara(const int& iWhichLayer)const;
	BOOL InsertLayerToolPara(const int& iLayer, const LayerToolPara& ltp);
	UserToolPara(){
		m_iDiameter    = 125;
		m_iApertureNo  = 12;
		m_iSubApertureNo=0;
		m_iToolNo = 11;
    }
	UserToolPara(const int& iToolNo,const int& iDiameter,const int& iAperture,const int& iSubAperture)
		:m_iDiameter(iDiameter),m_iApertureNo(iAperture),m_iSubApertureNo(iSubAperture),m_iToolNo(iToolNo)
	{}

	~UserToolPara(){
	}
	void SetApertureNo(const int& iAptNo);
	int  GetApertureNo()const;
	void SetSubApertureNo(const int& iSubAptNo);
	int  GetSubApertureNo()const;
	UserToolPara& operator=(const UserToolPara& tp);
	LayerToolPara& operator[](const int& iWhichLayer) ;
};

struct ProcParaSet
{
public:
	ProcParaSet()
	{
		m_bCheck= TRUE;
		m_iPeriod = 200;
		m_iRelease =15;
		m_iDrillMode=0;
		m_iApertureNo=11;
		m_iScanNum =1;
		m_iFocusOffset=0;

	}
	ProcParaSet(BOOL bIsCheck,int iPeriod,int iRelease,int iDrillMode,int iApertureNo,int iScanNum,int iFocusOffset)
	{
		m_bCheck= bIsCheck;
		m_iPeriod = iPeriod;
		m_iRelease = iRelease;
		m_iDrillMode=iDrillMode;
		m_iApertureNo=iApertureNo;
		m_iScanNum=iScanNum;
		m_iFocusOffset= iFocusOffset;
	}
	ProcParaSet& operator =(const ProcParaSet &eng);
	bool m_bCheck;// 是否选中
	int m_iPeriod;//脉冲周期
	int m_iRelease;//脉冲宽度
	int m_iDrillMode;//钻孔模式
	int m_iApertureNo;//光圈
	int m_iScanNum;//扫描次数
	int m_iFocusOffset;	//焦距偏移量
};

struct LayerToolParaSet
{
	typedef std::vector<ProcParaSet> ProcParaSetV;
private:
	bool m_bCheck;			//是否要加工
	float  m_iDiameter;
	int  m_iTool;
	ProcParaSetV m_ProcParaSet;
public:
	int GetLayerNum()const;
	LayerToolParaSet(const bool& bCheck,const float&iDiameter,const int&iTool)	
		:m_bCheck(bCheck),m_iDiameter(iDiameter),m_iTool(iTool){}
	LayerToolParaSet& operator=(const LayerToolParaSet& rht);
	BOOL InsertEnergyData(const int &iLayer,ProcParaSet& prPaSet);
	LayerToolParaSet()
	{
		m_bCheck   = 1;  //    是否要加工
		m_iDiameter  =125.0;
		m_iTool = 0;
	}
	int  GetLayerToolNo() const;
	float  GetLayerToolDiameter() const;
	bool GetLayerToolCheck() const;
   const ProcParaSet& GetLayerProcParaSet(const int &ToolNo) const;
	AddLayerToolParaSet(const int& iTypeNo,const ProcParaSetV& pToolPara);
};



#endif // !defined(AFX_TOOLPARAMETER_H__9B5B2164_7EE4_4C81_9F14_95993DD67A09__INCLUDED_)
