// Decode.h: interface for the Decode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECODE_H__70DFC325_23B2_4731_B6F7_BB2B10360CDB__INCLUDED_)
#define AFX_DECODE_H__70DFC325_23B2_4731_B6F7_BB2B10360CDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Excellon.h"

class DecodeExcellon
{
public:
	enum XYDateFormat{LEAD,TRAIL,NONE};	
//	enum DataProperty{COORDDATA,TOOLDATA,BLOCKDATA};
	enum BLOCKSTATE{NOBLOCK=-1,BLOCK_START,BLOCK_OPEN,BLOCK_CLOSE,BLOCK_LINK,BLOCK_END,INNERMARKDATA,PATTERNDATA,LOCALMARKDATA,BLOCK_T};//ly add 20140630 BLOCK_T

	void SetDataUnit(BOOL bIsMetric);
	void SetCrdMode (BOOL bIsAbs);
	void SetDecimalNum(int iDecNum);
	void SetIntegerNum(int iInteger);
	void SetDataFormat( XYDateFormat dataformat);

	int DecodeFile(const char* pchFileName);

	friend DecodeExcellon& GetDecodeExcellon();

protected:
	int DecodeExcHeader(FILE* fp);
	int DecodeDataBlock(FILE* fp);
//	void SaveData(const HoleData& crd,const DataProperty& property,DataMode datamode,MirrorModeV mmode);
	void SaveData(const HoleData& crd,DataMode datamode,MirrorModeV mmode);

private:
	DecodeExcellon(){};
	int GetUnitInfo(const char* buf,float& fDataFormat,bool& bLeadZero) const;
	int  GetCrdData( char*  buf,const int& iAxis,CRD& fCrdData);
	char* GetText(char *buf) const;
	DataMode GetStringMode(char* buf,bool dir);
	int GetToolInfo(char*buf,ToolInfo& ti);

private:
	int  m_iIntegerNum;							//整数位数
	int  m_iDecimalNum;							//小数位数
	BOOL m_bUnitIsMetric;						//公制或英制
	BOOL m_bAbsoluteMode;						//绝对坐标或相对坐标
	XYDateFormat m_DataFormat;					//数据格式：LZ或TZ

//	DataProperty  m_iDataProperty;				//当前数据的数据特征
	DataMode	  m_iDataMode;					//当前数据的意义
	MirrorModeV   m_iMirrorState;				//当前镜像状态
	BLOCKSTATE    m_iBlockState;				//当前Block状态
	CString		  m_strTextString;

	static HoleData m_crdHoleData;				//当前坐标值数据
	static int  m_iToolNo;						//当前刀具号
	static int	m_iCurLinkIndex;				//当前M02_M08块索引号
	static int  m_iCurBlockIndex;				//当前M25_M01块索引号

	static const char* ExcHeaderCommand[20];	//文件头代码
	static const char* ExcBlockCommand[30];		//文件体代码
	static const char* ExcTextCommand[10];		//字符串代码
};

class DecodeSA
{
//	enum SADATAPROPERTY{SATOOLDATA,SACOORDDATA,SACENTERDATA,M02LOCALMARKDATA,SALOCALMARKDATA,SAMTEXTDATA,
//		SADTEXTDATA,SATTEXTDATA,SALTEXTDATA,SABLOCKDATA};
	enum SADATAPROPERTY{SATOOLDATA,SACOORDDATA,SACENTERDATA,M02LOCALMARKDATA,SALOCALMARKDATA,SAMTEXTDATA,
		SADTEXTDATA,SATTEXTDATA,SALTEXTDATA,SASTEXTDATA,SABLOCKDATA,SAATEXTDATA,SASCTEXTDATA};//ly add 20121230 AxisNo  add 20131104 Scale
//	enum SABLOCKSTATE{NOSABLOCK=-1,SATOOL,SAMAINDATA,SALOCALMARK,M02LOCALMARK,M02OTHERDATA,SATEXT,SAPATTERNDATA,SAINNERMARK};
	enum SABLOCKSTATE{NOSABLOCK=-1,SATOOL,SAMAINDATA,M02LOCALMARK,M02OTHERDATA,SATEXT,SAPATTERNDATA,SAINNERMARK};
	
public:
	int GetSAToolInfo(char*buf,ToolInfo& ti);
	int DecodeSAFile(const char *pchFileName);

	friend DecodeSA& GetDecodeSA();

protected:
	void addSAInfo();
	void SaveSAData(const HoleData& crd,const SADATAPROPERTY& property,CString str,int iDir,int iPos);
	void SaveSAData(const HoleData& crd,const SADATAPROPERTY& property,int lmIndex,int smIndex,int saIndex,int iSACycleNum);

private:
	int  GetSACrdData( char*  buf,const int& iAxis,CRD& fCrdData);
	void GetStrText(char *buf);
//	char* GetSAText(char *buf) const;
//	DataMode GetStringMode(char* buf,bool dir);
	DecodeSA(){};

private:
	SADATAPROPERTY  m_iSADataProperty;			//当前数据的数据特征
	SABLOCKSTATE    m_iSABlockState;			//当前Block状态
	int				m_iSACycleNum;

	HoleData m_crdSAHoleData;					//坐标值数据
	int  m_iSAToolNo;							//当前刀具号
	int	m_iLMIndex;								//当前M02块索引号
	int	m_iSMIndex;								//当前M02块索引号
	int	m_iSAIndex;								//当前M02块索引号

	int	m_iTextDir;								//当前M02块索引号
	int	m_iTextPos;								//当前M02块索引号
	CString  m_iStrText;

	static const char* SADataCommand[32];		//文件代码
};

#endif // !defined(AFX_DECODE_H__70DFC325_23B2_4731_B6F7_BB2B10360CDB__INCLUDED_)

