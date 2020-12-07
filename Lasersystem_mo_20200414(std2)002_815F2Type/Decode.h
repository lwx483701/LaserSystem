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
	int  m_iIntegerNum;							//����λ��
	int  m_iDecimalNum;							//С��λ��
	BOOL m_bUnitIsMetric;						//���ƻ�Ӣ��
	BOOL m_bAbsoluteMode;						//����������������
	XYDateFormat m_DataFormat;					//���ݸ�ʽ��LZ��TZ

//	DataProperty  m_iDataProperty;				//��ǰ���ݵ���������
	DataMode	  m_iDataMode;					//��ǰ���ݵ�����
	MirrorModeV   m_iMirrorState;				//��ǰ����״̬
	BLOCKSTATE    m_iBlockState;				//��ǰBlock״̬
	CString		  m_strTextString;

	static HoleData m_crdHoleData;				//��ǰ����ֵ����
	static int  m_iToolNo;						//��ǰ���ߺ�
	static int	m_iCurLinkIndex;				//��ǰM02_M08��������
	static int  m_iCurBlockIndex;				//��ǰM25_M01��������

	static const char* ExcHeaderCommand[20];	//�ļ�ͷ����
	static const char* ExcBlockCommand[30];		//�ļ������
	static const char* ExcTextCommand[10];		//�ַ�������
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
	SADATAPROPERTY  m_iSADataProperty;			//��ǰ���ݵ���������
	SABLOCKSTATE    m_iSABlockState;			//��ǰBlock״̬
	int				m_iSACycleNum;

	HoleData m_crdSAHoleData;					//����ֵ����
	int  m_iSAToolNo;							//��ǰ���ߺ�
	int	m_iLMIndex;								//��ǰM02��������
	int	m_iSMIndex;								//��ǰM02��������
	int	m_iSAIndex;								//��ǰM02��������

	int	m_iTextDir;								//��ǰM02��������
	int	m_iTextPos;								//��ǰM02��������
	CString  m_iStrText;

	static const char* SADataCommand[32];		//�ļ�����
};

#endif // !defined(AFX_DECODE_H__70DFC325_23B2_4731_B6F7_BB2B10360CDB__INCLUDED_)

