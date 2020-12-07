// ToolParameter.cpp: implementation of the ToolParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include "ToolParameter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


Energy& Energy::operator =(const Energy &eng)
{
	this->m_iPeriod  = eng.m_iPeriod;
	this->m_iRelease = eng.m_iRelease;
	return *this;
}
ProcParaSet& ProcParaSet::operator =(const ProcParaSet &eng)
{
	this->m_bCheck  = eng.m_bCheck;
	this->m_iApertureNo = eng.m_iApertureNo;
	this->m_iDrillMode = eng.m_iDrillMode;
	this->m_iFocusOffset = eng.m_iFocusOffset;
	this->m_iPeriod = eng.m_iPeriod;
	this->m_iRelease = eng.m_iRelease;
	this->m_iScanNum = eng.m_iScanNum;
	return *this;
}


UserToolPara& UserToolPara::operator=(const UserToolPara& tp)
{
	if(this == &tp)
		return *this;
	this->m_iApertureNo = tp.m_iApertureNo;
	this->m_iDiameter = tp.m_iDiameter;
	if(tp.m_subToolPara.size()>0)
		this->m_subToolPara = tp.m_subToolPara;
	return *this;
}



LayerToolPara& LayerToolPara::operator =(const LayerToolPara& rht)
{
    if(this ==&rht)
        return *this;

	this->m_iDrillMode = rht.m_iDrillMode;
	this->m_iFocusOffset = rht.m_iFocusOffset;
	if(!rht.m_pEBEnergy.empty())
		this->m_pEBEnergy = rht.m_pEBEnergy;
	if(!rht.m_pECEnergy.empty())
		this->m_pECEnergy = rht.m_pECEnergy;

	return * this;
}


LayerToolParaSet& LayerToolParaSet::operator =(const LayerToolParaSet& rht)
{
    if(this ==&rht)
        return *this;
    this->m_bCheck = rht.m_bCheck;
	this->m_iDiameter = rht.m_iDiameter;
	this->m_iTool = rht.m_iTool;
	if(!rht.m_ProcParaSet.empty())
	this->m_ProcParaSet = rht.m_ProcParaSet;
	return * this;
}
//*/
void UserToolPara::SetApertureNo(const int& iAptNo)
{
	this->m_iApertureNo = iAptNo;
}

int UserToolPara::GetApertureNo() const
{
	return m_iApertureNo;
}

void UserToolPara::SetSubApertureNo(const int& iSubAptNo)
{
	this->m_iSubApertureNo = iSubAptNo;
}

int UserToolPara::GetSubApertureNo() const
{
	return m_iSubApertureNo;
}

int LayerToolPara::GetBurstNum() const
{
	return m_pEBEnergy.size();
}

int LayerToolPara::GetCycleNum() const
{
	return this->m_pECEnergy.size();
}
//iMode 0: Cycle,1:Burst;2: 0+1;3: 1=0
void LayerToolPara::SetDrillMode(const int iMode)
{
	this->m_iDrillMode = iMode;
	if(this->m_iDrillMode == 0)
	{
		m_pEBEnergy.clear();
	}
	else if(this->m_iDrillMode ==1)
	{
		m_pECEnergy.clear();
	}
}

int LayerToolPara::GetDrillMode() const
{
	return m_iDrillMode;
}

void LayerToolPara::SetFocusOffset(const int &iOffset)
{
	m_iFocusOffset = iOffset;
}

int LayerToolPara::GetFocusOffset() const
{
	return m_iFocusOffset;
}
void LayerToolPara::RemoveBstEnergy(const int &iBNo)
{
	m_pEBEnergy.erase(m_pEBEnergy.begin()+iBNo);
}

void LayerToolPara::RemoveCycEnergy(const int &iCNo)
{
	m_pECEnergy.erase(m_pECEnergy.begin()+iCNo);
}

BOOL LayerToolPara::InsertBstEnergy(const int &iBNo, const Energy &ePara)
{
	if( m_iDrillMode==CModel || iBNo>m_pEBEnergy.size())
		return FALSE;
//	if(iBNo<m_pEBEnergy.size())
//		m_pEBEnergy.insert(m_pEBEnergy.begin()+iBNo,ePara);
	else
		m_pEBEnergy.push_back(ePara);
	return TRUE;
}

BOOL LayerToolPara::InsertCycEnergy(const int &iCNo, const Energy &ePara)
{
	if(m_iDrillMode==BModel || iCNo>m_pECEnergy.size())
		return FALSE;
//	if(iCNo<m_pECEnergy.size())
//		m_pECEnergy.insert(m_pECEnergy.begin()+iCNo,ePara);	
	else
		m_pECEnergy.push_back(ePara);
	return TRUE;
}

BOOL LayerToolParaSet::InsertEnergyData(const int &iLayer,ProcParaSet& prPaSet)
{
  m_ProcParaSet.push_back(prPaSet);
 // int df = m_ProcParaSet.size();
  return TRUE;
}


BOOL LayerToolPara::SetCycEnergy(const int &iCNo, const Energy &ePara)
{
	if( m_iDrillMode == BModel || m_pECEnergy.size()<iCNo)
		return FALSE;
	if(iCNo == m_pECEnergy.size())
	{
		m_pECEnergy.push_back(ePara);
	}
	else
	{
		std::fill(m_pECEnergy.begin()+iCNo,m_pECEnergy.begin()+iCNo+1,ePara);
	}
	return TRUE;
}

BOOL LayerToolPara::SetBstEnergy(const int &iBNo, const Energy &ePara)
{
	if( m_iDrillMode==CModel || m_pEBEnergy.size()<iBNo)
		return FALSE;
	if(iBNo==m_pEBEnergy.size())
		m_pEBEnergy.push_back(ePara);
	else
	{
		std::fill(m_pEBEnergy.begin()+iBNo,m_pEBEnergy.begin()+iBNo+1,ePara);
	}
	return TRUE;
}

const Energy& LayerToolPara::GetBstEnergy(const int &iBNo) const
{
	if(iBNo<0||iBNo>=m_pEBEnergy.size())
		return m_pEBEnergy[m_pEBEnergy.size()-1];
	return m_pEBEnergy[iBNo];
}

const Energy& LayerToolPara::GetCycEnergy(const int &iCNo) const
{
	if(iCNo<0||iCNo>=m_pECEnergy.size())
		return m_pECEnergy[m_pECEnergy.size()-1];
	return m_pECEnergy[iCNo];
}

BOOL UserToolPara::InsertLayerToolPara(const int&iLayer, const LayerToolPara &ltp)
{
	if(m_subToolPara.size()<iLayer)
		return FALSE;
	else if(m_subToolPara.size()>iLayer)
		m_subToolPara.insert(m_subToolPara.begin()+iLayer,ltp);
	else
		m_subToolPara.push_back(ltp);
	return TRUE;
}

const LayerToolPara& UserToolPara::GetLayerToolPara(const int &iWhichLayer) const
{
	if(iWhichLayer<0||iWhichLayer>=this->m_subToolPara.size())
		return m_subToolPara[m_subToolPara.size()-1];
	return m_subToolPara[iWhichLayer];
}

void UserToolPara::RemoveLayerToolPara(const int &iWhichLayer)
{
	m_subToolPara.erase(m_subToolPara.begin()+iWhichLayer);
}

BOOL UserToolPara::SetLayerToolPara(const int &iWhichLayer, const LayerToolPara &ltp)
{

	if(iWhichLayer > m_subToolPara.size())
		return FALSE;
	else if(iWhichLayer == m_subToolPara.size())
		m_subToolPara.push_back(ltp);
	else
		std::fill(m_subToolPara.begin()+iWhichLayer,m_subToolPara.begin()+iWhichLayer+1,ltp);
	return TRUE;
}

LayerToolPara& UserToolPara::operator [](const int& iWhichLayer) 
{
	return m_subToolPara[iWhichLayer];
}

int UserToolPara::GetToolNo() const
{
	return this->m_iToolNo;
}

int UserToolPara::GetDiameter() const
{
	return this->m_iDiameter;
}

int UserToolPara::GetLayerNum() const
{
	return this->m_subToolPara.size();
}
int LayerToolParaSet::GetLayerNum() const
{
	return this->m_ProcParaSet.size();
}

bool LayerToolParaSet::GetLayerToolCheck() const
{
	return this->m_bCheck;
}

int LayerToolParaSet::GetLayerToolNo() const
{
	return this->m_iTool;
}
float LayerToolParaSet::GetLayerToolDiameter() const
{
    return this->m_iDiameter;
}

const ProcParaSet& LayerToolParaSet::GetLayerProcParaSet(const int &ToolNo) const
{
	if(ToolNo<0||ToolNo>=m_ProcParaSet.size())
		return m_ProcParaSet[m_ProcParaSet.size()-1];
	return m_ProcParaSet[ToolNo];
}