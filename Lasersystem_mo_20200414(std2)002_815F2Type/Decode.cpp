// Decode.cpp: implementation of the Decode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Decode.h"
#include "Filecomdefine.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int AXISX = 0;
const int AXISY = 1;

#define LineLength  128

extern bool IsNum(char ch);
extern bool IsAvaliableChar(char ch);
extern long UserAtoL(char* buf);
extern double UserAtoF(char* buf);
extern void LeftMove(char* buf,long lbit);
extern BOOL EndOfLine(const char* buf);

HoleData DecodeExcellon::m_crdHoleData = HoleData();

int   DecodeExcellon::m_iCurBlockIndex   =-1; 
int   DecodeExcellon::m_iCurLinkIndex    =-1;
int   DecodeExcellon::m_iToolNo			 =-1;					//当前数据工具号暂存

const char* DecodeExcellon::ExcHeaderCommand[]={
 ExcHeaderBegin,			
 ExcHeaderEnd,		
 ExcHeaderRewindStop,
 ExcHeaderFormat,		
 ExcHeaderUnit_Inch,	
 ExcHeaderUnit_Metric,
 ExcHeaderUnitLeadZero,
 ExcHeaderLeadZero,	
 ExcHeaderUnitTrailZero,
 ExcHeaderTrailZero,	
 ExcHeaderCrdMode,		
 ExcHeaderToolIndicate,
 NULL
};

const char* DecodeExcellon::ExcBlockCommand[]={
 ExcToolIndicate,		//  "T"       0

 ExcBlockPatternEnd,	//	"M01"     1
 ExcBlockPatternOffset,	//	"M02"     2
 ExcBlockStepRepeatEnd,	// 	"M08"     3
 ExcBlockPatternBegin,	//	"M25"     4

 ExcBlockDrillTextH,	//	"M97"     5
 ExcBlockDrillTextV,	//	"M98"     6
  
 ExcBlockUnit_Metric,	//	"M71"     7
 ExcBlockUnit_Inch,		//	"M72"     8

 ExcRepeatIndicate,		//	"R"       9

 ExcZeroSet,			//	"G92"     10
 ExcZeroSet1,			//  "G93"     11

 ExcFiducialIndicate1,	//	"G82"	  12
 ExcFiducialIndicate2,	//	"G83"	  13

 ExcLocalMarkIndicate,	//	"A"		  14

 ExcBlockX_CrdIndicate,	//	"X"	      15
 ExcBlockY_CrdIndicate,	//	"Y"	      16 

 EXcBlockMirrorX,		//	"M80"     17
 EXcBlockMirrorY,		//	"M90"     18
 ExcBlockSwapAxis,		//	"M70"     19

 ExcFileEnd,			//  "M30"     20

 ExcFileSplitter,		//	"M29"     21							//20161109

 NULL
};

const char* DecodeExcellon::ExcTextCommand[]=
{
	"$MACHINE",
	"$DATE",
	"$TIME",
	"$LOTID",
	"$AXISNO",//ly add 20121230
	"$SCALE",//ly add 20131104
	NULL
};

DecodeExcellon& GetDecodeExcellon()
{
	static DecodeExcellon decExc2;
	return decExc2;
}

void DecodeExcellon::SetCrdMode(BOOL bIsAbs)
{
	m_bAbsoluteMode = bIsAbs;
}

void DecodeExcellon::SetDecimalNum(int iDecNum)
{
	m_iDecimalNum = iDecNum;
}

void DecodeExcellon::SetIntegerNum(int iInteger)
{
	m_iIntegerNum = iInteger;
}

void DecodeExcellon::SetDataUnit(BOOL bIsMetric)
{
	m_bUnitIsMetric = bIsMetric;
}

int DecodeExcellon::GetUnitInfo(const char *buf, float &fDataFormat, bool &bLeadZero) const
{
	char* pbuf;

	if((pbuf=strpbrk(buf,"1234567890"))!=NULL)//找倒数字
	{
		sscanf(pbuf,"%f\n",&fDataFormat);	
	}
	if((pbuf=strpbrk(buf,ExcFileComma))!=NULL)
	{
		if(strstr(buf,"LZ")!=NULL)
		{
			bLeadZero = true;
		}
		if(strstr(buf,"TZ")!=NULL)
		{
			bLeadZero = false;			
		}
		else
			return FileReadCommandError;
	}
	else
		bLeadZero = true;
	return FileReadSuccess;
}

int DecodeExcellon::DecodeFile(const char *pchFileName)
{
	FILE* fp;

	if(!(fp = fopen(pchFileName,"r")))
		return FileReadFalse;
	
	if(DecodeExcHeader(fp)==FileUnknowFileFormat)
	{
		fclose(fp);
//		AfxMessageBox("文件格式不正确!");
		return FileUnknowFileFormat;
	}

	if(	DecodeDataBlock(fp))
	{
		fclose(fp);
//		AfxMessageBox("文件格式不正确!");
		return FileUnknowFileFormat;
	}

	fclose(fp);
	return FileReadSuccess;
}

int DecodeExcellon::DecodeExcHeader(FILE* fp)
{
	char buf[LineLength];	
	ToolInfo ti;

	fgets(buf,sizeof(buf),fp);
	while(strstr(buf,ExcHeaderBegin)==NULL)
	{
		fgets(buf,sizeof(buf),fp);
		if(feof(fp))
			return FileUnknowFileFormat;
	}

	fgets(buf,sizeof(buf),fp);
	while(!feof(fp))
	{
		for(int i=0; ExcHeaderCommand[i]!=NULL;++i)
		{
			if(strstr(buf,ExcHeaderCommand[i])!=NULL)
			{
				switch(i)
				{
				case 0:
					break;
				case 1:
				case 2:
					return FileReadSuccess;
				case 3: //FMAT
					break;
				case 4: //Inch
//					m_bUnitIsMetric = false;
					break;
				case 5:	//Metric
//					m_bUnitIsMetric = true;
					break;
				case 6:
				case 7:
//					m_bDataIsLeadZero = true;
					break;
				case 8:
				case 9:
//					m_bDataIsLeadZero =false;
					break;					
				case 10:	//ICI Absolute&&increament
					break;
				case 11:	//T toolNum
					LeftMove(buf,1);			
					if(!GetToolInfo(buf,ti))
					{
//						GetExcellonData().AddToolsInfo(ti);

						SetGlobalExcellonIndex(0);													
						GetExcellonData().AddToolsInfo(ti);
						SetGlobalExcellonIndex(1);			
						GetExcellonData().AddToolsInfo(ti);
					}
					break;
				}
			}
		}
		fgets(buf,sizeof(buf),fp);
	}

	return FileReadSuccess;
}

int DecodeExcellon::DecodeDataBlock(FILE* fp)
{
	bool bCoord=false;
	int rtn=0;
	char buf[LineLength];
//	char *pbuf;

	m_iBlockState = BLOCK_END;	//缺省没有M25块
	m_iDataMode=HOLEDATA;

	m_iCurBlockIndex =-1;
	m_iMirrorState.push_back(-1);
	m_strTextString="";

	SetGlobalExcellonIndex(0);									//20161109
	
	fgets(buf,sizeof(buf),fp);
	while(!feof(fp))
	{
/*
		pbuf=buf;
		while(!EndOfLine(pbuf))
		{
			if(!IsAvaliableChar(*pbuf))
			{
				return FileReadDataError;
			}
			pbuf++;
		}
*/
		for(int i=0; ExcBlockCommand[i]!=NULL&&(!EndOfLine(buf));++i)
		{
			if(strstr(buf,ExcBlockCommand[i])!=NULL)
			{
				switch (i)
				{
				case 0:										//"T"
					bCoord=false;
					m_iDataMode=HOLEDATA;
					if(buf[0]!='T')
						break;
					LeftMove( buf,1);				
					m_iToolNo =  UserAtoL(buf);
					break;
				case 1:										//"M01"
					bCoord=false;
					m_iBlockState = BLOCK_CLOSE;
					m_iDataMode=HOLEDATA;
//					LeftMove( buf,3);							
					break;
				case 2:										//"M02"
					bCoord=false;
					m_iBlockState = BLOCK_LINK;
					m_iDataMode=HOLEDATA;
					++m_iCurLinkIndex;
					m_iMirrorState.clear();
					LeftMove( buf,3);
					break;
				case 3:										//"M08"
					bCoord=false;
					m_iBlockState = BLOCK_END;
					m_iDataMode=HOLEDATA;
					m_iCurLinkIndex=-1;
//					LeftMove( buf,3);				
					break;
				case 4:										//"M25"
					bCoord=false;
					GetExcellonData().AddBlockData(++m_iCurBlockIndex);
					m_iBlockState	= BLOCK_OPEN;
					m_iDataMode=HOLEDATA;					
//					LeftMove( buf,3);				
					break;
				case 5:										//"M97"
					bCoord=false;
					LeftMove( buf,4);					
					m_iDataMode = GetStringMode(buf,true);
					break;
				case 6:										//"M98"
					bCoord=false;
					LeftMove( buf,4);				
					m_iDataMode = GetStringMode(buf,false);
					break;
				case 7:			// ExcBlockUnit_Metric,		//"M71"
					bCoord=false;
					LeftMove( buf,3);					
					break;
				case 8:			// ExcBlockUnit_Inch		//"M72"
					bCoord=false;
					LeftMove( buf,3);					
					break;
				case 9:			// ExcRepeatIndicate,		//"R" 
					bCoord=false;
					LeftMove( buf,1);			
					break;
				case 10:		// ExcZeroSet,				//"G92" 
					bCoord=false;
					LeftMove( buf,3);				
					break;
				case 11:		// ExcZeroSet1,				//"G93"
					bCoord=false;
					LeftMove( buf,3);					
					break;
				case 12:									//"G82"
					bCoord=false;
					m_iBlockState = PATTERNDATA;
					m_iDataMode=HOLEDATA;
//					LeftMove( buf,3);					
					break;
				case 13:									//"G83"
					bCoord=false;
					m_iBlockState = INNERMARKDATA;
					m_iDataMode=HOLEDATA;
//					LeftMove( buf,3);					
					break;
				case 14:		// ExcLocalMarkIndicate,	//"A"
					bCoord=false;
					m_iBlockState = LOCALMARKDATA;
					m_iDataMode=HOLEDATA;					
					LeftMove( buf,1);					
					break;
				case 15:		// ExcBlockX_CrdIndicate,	//"X"
					bCoord=true;
					LeftMove( buf,1);							
					if(rtn = GetCrdData(buf,AXISX,m_crdHoleData.x))
						return rtn;						
					break;
				case 16:		// ExcBlockY_CrdIndicate,	//"Y"
					bCoord=true;
					LeftMove( buf,1);			
					if(rtn = GetCrdData(buf,AXISY,m_crdHoleData.y))
						return rtn;	
					break;
				case 17:		// EXcBlockMirrorX,			//"M80" 
					m_iMirrorState.push_back(0);				
					break;
				case 18:		// EXcBlockMirrorY,			//"M90"   
					m_iMirrorState.push_back(1);				
					break;
				case 19:		// ExcBlockSwapAxis,		//"M70" 
					m_iMirrorState.push_back(2);					
					break;
				case 20:		// ExcFileEnd,				//"M30"
					return FileReadSuccess;	
//----------------------------------------------------------------------------------------//20161109
				case 21:		// ExcFileSplitter,			//"M29"
					bCoord=false;
					rtn=0;

					m_iBlockState = BLOCK_END;	//缺省没有M25块
					m_iDataMode=HOLEDATA;
					
					m_iCurBlockIndex =-1;
					m_iMirrorState.push_back(-1);
					m_strTextString="";

					SetGlobalExcellonIndex(1);
					break;
//----------------------------------------------------------------------------------------
				}
			}
		}
	
		m_crdHoleData.iToolNo = m_iToolNo;
		if(bCoord)
			SaveData(m_crdHoleData,m_iDataMode,m_iMirrorState);

		fgets(buf,sizeof(buf),fp);
	}

	return FileReadSuccess;
}

void DecodeExcellon::SaveData(const HoleData &crd,DataMode datamode,MirrorModeV mmode)
{
	switch(m_iBlockState)
	{
	case BLOCK_OPEN:
		if(HOLEDATA==datamode)
		{
			GetExcellonData().AddBlockDataInfo(crd, m_iCurBlockIndex);
		}
		else
		{
			GetExcellonData().AddTextInfo(crd,datamode,m_strTextString,m_iCurBlockIndex);	
		}
		break;
	case BLOCK_END:	//缺省没有M25块，如果有M25块，但没有M02_M08定义，则相当于块一直OPEN
		if(HOLEDATA==datamode)
		{
			GetExcellonData().AddNoBlockDataInfo(crd);
		}
		else
		{
			GetExcellonData().AddTextInfo(crd,datamode,m_strTextString);	
		}
		break;
	case BLOCK_LINK:
		GetExcellonData().AddBlockLinkInfo(crd,m_iCurBlockIndex,m_iCurLinkIndex,mmode);
		break;
	case PATTERNDATA:
		GetExcellonData().AddFiducialData(crd);
		break;
	case INNERMARKDATA:
		GetExcellonData().AddInnerFiducialData(crd);
		break;
	case LOCALMARKDATA:
		GetExcellonData().AddLocalMarkInfo(crd,m_iCurBlockIndex);
		break;
	}
}

int DecodeExcellon::GetCrdData( char*  buf,const int &iAxis, CRD &iCrdData)
{
	char *pbuf;
	char seps[]   = " XYxy";
	char NumBuf[16];
	int nlen;
	double dbCrdData;
	ASSERT(iAxis==0||iAxis==1);
	
	memset(NumBuf,'\0',16);
	pbuf = buf;
	
	while(IsNum(*pbuf))
	{
		sprintf(NumBuf,"%s%c",NumBuf,*pbuf);
		pbuf++;
	}
	
	nlen = strlen(NumBuf);
	
	if(!strchr(NumBuf,'.'))
	{
		if(m_DataFormat == DecodeExcellon::LEAD)
		{
			if(NumBuf[nlen-1] == 0)
			{
				return FileReadDataError;
			}
			if(!sscanf(NumBuf,"%d\n",&iCrdData))
			{
				return FileReadDataError;
			}
			if (m_bUnitIsMetric)
			{
				iCrdData = iCrdData/pow(10,nlen-m_iIntegerNum-(iCrdData>0?3:4));		
			}
			else
			{
				iCrdData =25.4*iCrdData/pow(10,nlen-m_iIntegerNum-(iCrdData>0?3:4));		
			}
		}
		else if(m_DataFormat == DecodeExcellon::TRAIL)
		{
			if(NumBuf[0]==0)
			{
				return FileReadDataError;
			}
			if(!sscanf(NumBuf,"%d\n",&iCrdData))
			{
				return FileReadDataError;
			}
			
			if (m_bUnitIsMetric)
			{
				iCrdData = iCrdData/pow(10,m_iDecimalNum-3);		
			}
			else
			{
				iCrdData =25.4*iCrdData/pow(10,m_iDecimalNum-3);		
			}
		}
		else // None
		{
			if(!sscanf(NumBuf,"%d\n",&iCrdData))
			{
				return FileReadDataError;
			}
			
		}
	}
	else
	{
		dbCrdData = UserAtoF(NumBuf);
		iCrdData = CRD(dbCrdData*pow(10,m_iDecimalNum));
		
		if (m_bUnitIsMetric)
		{
			iCrdData = iCrdData;		
		}
		else
		{
			iCrdData =25.4*iCrdData;		
		}
	}
	
	strcpy(buf,pbuf);
	return FileReadSuccess;
}

int DecodeExcellon::GetToolInfo(char *buf, ToolInfo &ti)
{
	char *pbuf;
	char seps[]   = "CcOo";
	char NumBuf[16];
	int nlen;
	int ntemp;
	double dbDm;
//	ASSERT(iAxis==0||iAxis==1);

	memset(NumBuf,'\0',16);
	pbuf = buf;

	if(!isdigit(*pbuf))
		return FileReadDataError;

	while(isdigit(*pbuf))
	{
		sprintf(NumBuf,"%s%c",NumBuf,*pbuf);	//将连续数字量取出
		pbuf++;
	}

	nlen = strlen(NumBuf);
	if(nlen>10)
		return FileReadDataError;

	if(!sscanf(NumBuf,"%d\n",&ti.m_nToolIndex))	//取出刀具索引号
		return FileReadDataError;
/////////////////////////////////////////////////////////////////////////
	if((strstr(pbuf,"C")!=NULL)||(strstr(pbuf,"c")!=NULL))	//20160809
	{
		ntemp = strcspn(pbuf,seps);
		if(strcspn(pbuf,seps)>=strlen(pbuf))
		{
			return FileReadDataError;
		}
		
		LeftMove( pbuf,ntemp+1);
		
		dbDm = UserAtoF(pbuf);
	}
	else
	{
		dbDm = 0.0;
	}
#ifdef DINGYING
	if (m_bUnitIsMetric)
	{	
		ti.m_nToolX = dbDm*1;
	}
	else
	{
		ti.m_nToolX = dbDm*25.4;
	}
#else
/////////////////////////////////////////////////////////////////////////	
	if (m_bUnitIsMetric)
	{	
		ti.m_nToolX = dbDm*1000;
	}
	else
	{
		ti.m_nToolX = dbDm*25400;
	}
#endif

	return FileReadSuccess;
}

char* DecodeExcellon::GetText(char *buf) const
{
	return 0;
}

void DecodeExcellon::SetDataFormat(XYDateFormat dataformat)
{
	m_DataFormat = dataformat;
}

DataMode DecodeExcellon::GetStringMode(char *buf,bool dir)
{
	char *pbuf;
	char NumBuf[32];

	memset(NumBuf,'\0',32);
	pbuf = buf;

	while(!EndOfLine(pbuf))
	{
		sprintf(NumBuf,"%s%c",NumBuf,*pbuf);
		pbuf++;
	}

	bool bIsString=true;
	for(int i=0; ExcTextCommand[i]!=NULL&&(!EndOfLine(buf));++i)
	{
		if(strstr(buf,ExcTextCommand[i])!=NULL)
		{
//			return i;
			if(dir)
			{
				switch(i)
				{
				case 0:
					strcpy(buf,pbuf);
					return MACHINENOH;
				case 1:
					strcpy(buf,pbuf);
					return DATENOH;
				case 2:
					strcpy(buf,pbuf);
					return TIMENOH;
				case 3:
					strcpy(buf,pbuf);
					return LOTIDNOH;
				case 4://ly add 20121230
					strcpy(buf,pbuf);
					return AXISNOH;
				case 5://ly add 20131104
					strcpy(buf,pbuf);
					return SCALEH;
				}
			}
			else
			{
				switch(i)
				{
				case 0:
					strcpy(buf,pbuf);
					return MACHINENOV;
				case 1:
					strcpy(buf,pbuf);
					return DATENOV;
				case 2:
					strcpy(buf,pbuf);
					return TIMENOV;
				case 3:
					strcpy(buf,pbuf);
					return LOTIDNOV;
				case 4://ly add 20121230
					strcpy(buf,pbuf);
					return AXISNOV;
				case 5://ly add 20131104
					strcpy(buf,pbuf);
					return SCALEV;
				}
			}
			bIsString=false;
		}
	}

	if(bIsString)
	{
		m_strTextString.Format("%s",NumBuf);

		if(dir)
		{
			strcpy(buf,pbuf);
			return STRINGH;
		}
		else
		{
			strcpy(buf,pbuf);
			return STRINGV;
		}
	}

	strcpy(buf,pbuf);
	return ERRORDATA;
}
//---------------------------------------------------------------------------------

DecodeSA& GetDecodeSA()
{
	static DecodeSA decSA;
	return decSA;
}

//HoleData m_crdSAHoleData=HoleData();

//int  m_iSAToolNo=-1;				
//int	m_iLMIndex=-1;					
//int	m_iSMIndex=-1;					
//int	m_iSAIndex=-1;					

//int	m_iTextDir=-1;					
//int	m_iTextPos=-1;					
	
const char* DecodeSA::SADataCommand[]={
 Glv_ScanSize,
 Glv_ScanBit,//ly add 20130412
 SubAreaRowNum,
 SubAreaColNum,
 SAToolBlock,			
 SAMainDataBlock,		
 SALocalMarkBlock,
 SAOtherDataBlock,		
 SATextBlock,	
 SACenter,
 StrText,
 MText,
 DText,	
 TText,
 LText,
 SText,
 AText,//ly add 20121230
 SCText,//ly add 20131104    //ly move up 20131209 需要在T前面？
 Tool,
 TextDirect,		
 TextPos,
 PatternData,
 InnerMarkData,
 M02LocalMarkZone,	
 SALocalMarkZone,
 SubAreaZone,			
 M02LocalMark,
 SALocalMark,
 X_crd,
 Y_crd,
 SAFileEnd,
 NULL
};

int DecodeSA::DecodeSAFile(const char *pchFileName)
{
	char *pbuf;
	FILE* fp;

	if(!(fp = fopen(pchFileName,"r")))
		return FileReadFalse;

//	GetExcellonData().ClearAll();

	int rtn;
//	bool bIsRecognizable;
	ToolInfo ti;
	char buf[LineLength];
	m_iSABlockState = NOSABLOCK;
	m_crdSAHoleData=HoleData();

	m_iSAToolNo=-1;				
	m_iLMIndex=-1;					
	m_iSMIndex=-1;					
	m_iSAIndex=-1;					

	m_iTextDir=-1;					
	m_iTextPos=-1;
	m_iStrText="";
	m_iSACycleNum=-1;

	SetGlobalExcellonIndex(0);									//20161109
		
	fgets(buf,sizeof(buf),fp);
	while(!feof(fp))
	{
		pbuf=buf;
		while(!EndOfLine(pbuf))
		{
			if(!IsAvaliableChar(*pbuf))
			{
				fclose(fp);
//				GetExcellonData().ClearAll();
				return FileReadDataError;
			}
			pbuf++;
		}

//		bIsRecognizable=false;
		for(int i=0; SADataCommand[i]!=NULL&&(!EndOfLine(buf));++i)
		{
			if(strstr(buf,SADataCommand[i])!=NULL)
			{	
//				bIsRecognizable=true;
				switch (i)
				{
				case 0:										//"SCANSIZE"
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,8);
					GetExcellonData().AddGlvScanSize(UserAtoL(buf));
					break;
				case 1:		//ly add 20130412								//"SCANBIT"       
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,7);
					GetExcellonData().AddGlvScanBit(UserAtoL(buf));
					break;
				case 2:										//"SUBAREAROW"
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,10);
					GetExcellonData().AddSubAreaRowNum(UserAtoL(buf));					
					break;
				case 3:										//"SUBAREACOL"
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,10);
					GetExcellonData().AddSubAreaColNum(UserAtoL(buf));					
					break;
				case 4:										//"[TOOL]"
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = SATOOL;
					LeftMove( buf,6);				
					break;
				case 5:										//"[MAINDATA]"
					if(GetExcellonData().GetGlvScanBit()==0)							//20180911
					{
						AfxMessageBox("SA文件中没有比特因子数据，请重新导入原始数据文件！");
						return FileReadDataError;
					}
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = SAMAINDATA;
					LeftMove( buf,10);				
					break;
				case 6:										//"[LOCALMARK]"
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = M02LOCALMARK;
					LeftMove( buf,11);				
					break;
				case 7:										//"[OTHERDATA]"
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = M02OTHERDATA;
					LeftMove( buf,11);				
					break;
				case 8:										//"[TEXT]" 
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = SATEXT;
					LeftMove( buf,6);				
					break;
				case 9:										//"CENTER"
					m_iSADataProperty = SACENTERDATA;
					LeftMove( buf,6);					
					break;
				case 10:										//"STRING="
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,7);
					GetStrText(buf);
					break;
				case 11:										//"$M$"
					m_iSADataProperty = SAMTEXTDATA;				
					LeftMove( buf,3);				
					break;
				case 12:										//"$D$"
					m_iSADataProperty = SADTEXTDATA;				
					LeftMove( buf,3);				
					break;
				case 13:										//"$T$"
					m_iSADataProperty = SATTEXTDATA;				
					LeftMove( buf,3);				
					break;
				case 14:										//"$L$"       
					m_iSADataProperty = SALTEXTDATA;				
					LeftMove( buf,3);				
					break;
				case 15:										//"$S$"       
					m_iSADataProperty = SASTEXTDATA;				
					LeftMove( buf,3);				
					break;
				case 16:		//ly add 20121230								//"$A$"       
					m_iSADataProperty = SAATEXTDATA;				
					LeftMove( buf,3);				
					break;
				case 17:		//ly add 20131104								//"$SC$"       
					m_iSADataProperty = SASCTEXTDATA;				
					LeftMove( buf,4);				
					break;
				case 18:									//"T" 
					if(m_iSABlockState != SATEXT)
					{
						m_iSADataProperty = SATOOLDATA;
					}				
					LeftMove( buf,1);
					if(m_iSABlockState == SATOOL)
					{
						if(GetSAToolInfo(buf,ti))
						{
							GetExcellonData().AddSAToolsInfo(ti);
						}			
					}
					else
					{
						m_iSAToolNo =  UserAtoL(buf);
						m_crdSAHoleData.iToolNo = m_iSAToolNo;
					}
					break;
				case 19:									//"DIR"     
					LeftMove( buf,3);
					m_iTextDir=UserAtoL(buf);
					break;
				case 20:									//"POS"     
					LeftMove( buf,3);
					m_iTextPos=UserAtoL(buf);
					break;
				case 21:									//"G82"
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = SAPATTERNDATA;
					LeftMove( buf,3);					
					break;
				case 22:									//"G83"
					m_iSADataProperty = SABLOCKDATA;
					m_iSABlockState = SAINNERMARK;
					LeftMove( buf,3);					
					break;
				case 23:									//"LM" 	
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,2);
					m_iLMIndex=UserAtoL(buf)-1;
					GetExcellonData().AddLMInfo(m_iLMIndex);
					break;
				case 24:									//"SM"
					m_iSADataProperty = SABLOCKDATA;
					m_iSACycleNum++;					
					LeftMove( buf,2);
					m_iSMIndex=UserAtoL(buf)-1;
					GetExcellonData().AddSMInfo(m_iSMIndex);
					break;
				case 25:									//"SA" 	
					m_iSADataProperty = SABLOCKDATA;
					LeftMove( buf,2);
					m_iSAIndex=UserAtoL(buf)-1;
					addSAInfo();
					break;
				case 26:									//"A" 
					m_iSADataProperty = M02LOCALMARKDATA;
					LeftMove( buf,1);					
					break;
				case 27:									//"B"   
					m_iSADataProperty = SALOCALMARKDATA;
					LeftMove( buf,1);					
					break;
				case 28:									//"X"
//					m_iSADataProperty = SACOORDDATA;					
					LeftMove( buf,1);							
					if(rtn = GetSACrdData(buf,AXISX,m_crdSAHoleData.x))
					{
						fclose(fp);
						return rtn;	
					}										
					break;
				case 29:									//"Y"
//					m_iSADataProperty = SACOORDDATA;					
					LeftMove( buf,1);			
					if(rtn = GetSACrdData(buf,AXISY,m_crdSAHoleData.y))
					{
						fclose(fp);
						return rtn;	
					}
					break;
				case 30:									//"M30"     
					fclose(fp);
					return FileReadSuccess;		
				}
			}
		}

//		if(!bIsRecognizable)
//		{
//			GetExcellonData().ClearAll();
//			return FileReadDataError;
//		}
		if(m_iSABlockState == SATEXT)
		{
			SaveSAData(m_crdSAHoleData,m_iSADataProperty,m_iStrText,m_iTextDir,m_iTextPos);					
		}
		else 
		{
			SaveSAData(m_crdSAHoleData,m_iSADataProperty,m_iLMIndex,m_iSMIndex,m_iSAIndex,m_iSACycleNum);
		}		

		fgets(buf,sizeof(buf),fp);
	}

	fclose(fp);
	return FileReadSuccess;
}

int DecodeSA::GetSAToolInfo(char *buf, ToolInfo &ti)
{
	char *pbuf;
	char seps[]   = "CcOo";
	char NumBuf[16];
	int nlen;
	int ntemp;
	double dbDm;

	memset(NumBuf,'\0',16);
	pbuf = buf;

	if(!IsNum(*pbuf))
		return 0;

	while(IsNum(*pbuf))
	{
		sprintf(NumBuf,"%s%c",NumBuf,*pbuf);
		pbuf++;
	}

	nlen = strlen(NumBuf);

	if(!sscanf(NumBuf,"%d\n",&ti.m_nToolIndex))	//分析出刀具索引号
	{
		return FileReadDataError;
	}

	ntemp = strcspn(pbuf,seps);
	
	if(strcspn(pbuf,seps)>=strlen(pbuf))
	{
		return FileReadDataError;
	}
	
	LeftMove( pbuf,ntemp+1);

	dbDm = UserAtoF(pbuf);
		
	ti.m_nToolX = dbDm;

	strcpy(buf,pbuf);
}

int DecodeSA::GetSACrdData( char*  buf,const int &iAxis, CRD &iCrdData)
{
	char *pbuf;
	char seps[]   = " XYxy";
	char NumBuf[16];
	int nlen;
	CRD dataXY;
	ASSERT(iAxis==0||iAxis==1);

	memset(NumBuf,'\0',16);
	pbuf = buf;

	while(IsNum(*pbuf))
	{
		sprintf(NumBuf,"%s%c",NumBuf,*pbuf);
		pbuf++;
	}

	nlen = strlen(NumBuf);

//	if(!sscanf(NumBuf,"%d\n",&iCrdData))
//	{
//		return FileReadDataError;
//	}

	if(!sscanf(NumBuf,"%d\n",&dataXY))									//20180911
	{
		return FileReadDataError;
	}

	if(m_iSADataProperty == SACOORDDATA)
	{
		if((m_iSABlockState==SAMAINDATA)||(m_iSABlockState==M02LOCALMARK)||(m_iSABlockState==M02OTHERDATA))
			iCrdData=dataXY*GetDoc().GetSLBitPerMM()/GetExcellonData().GetGlvScanBit();
		else
			iCrdData=dataXY;
	}
	else
		iCrdData=dataXY;

	strcpy(buf,pbuf);

	return FileReadSuccess;
}

void DecodeSA::SaveSAData(const HoleData& crd,const SADATAPROPERTY& property,CString str,int iDir,int iPos)
{
	switch(property)
	{
	case SATOOLDATA:  			
		break;
	case SACOORDDATA:  			
		break;
	case SACENTERDATA:		
		break;
	case M02LOCALMARKDATA:		
		break;
	case SALOCALMARKDATA:		
		break;
	case SAMTEXTDATA:			
		GetExcellonData().AddSAMTextInfo(crd,iDir,iPos);	
		break;
	case SADTEXTDATA:			
		GetExcellonData().AddSADTextInfo(crd,iDir,iPos);	
		break;
	case SATTEXTDATA:			
		GetExcellonData().AddSATTextInfo(crd,iDir,iPos);	
		break;
	case SALTEXTDATA:			
		GetExcellonData().AddSALTextInfo(crd,iDir,iPos);	
		break;
	case SAATEXTDATA://ly add 20121230			
		GetExcellonData().AddSAATextInfo(crd,iDir,iPos);	
		break;
	case SASTEXTDATA:			
		GetExcellonData().AddSASTextInfo(crd,str,iDir,iPos);	
		break;
	case SASCTEXTDATA://ly add 20131104			
		GetExcellonData().AddSASCTextInfo(crd,iDir,iPos);	
		break;
	case SABLOCKDATA:  			
		break;
	}
}

void DecodeSA::SaveSAData(const HoleData& crd,const SADATAPROPERTY& property,int lmIndex,int smIndex,int saIndex,int iSACycleNum)
{
	switch(property)
	{
	case SATOOLDATA: 
		m_iSADataProperty = SACOORDDATA;		
		break;
	case SACOORDDATA: 
		if(m_iSABlockState==SAMAINDATA)
		{
			GetExcellonData().AddSAMainData(crd,saIndex);
		}
//		else if(m_iSABlockState==SALOCALMARK)
//		{
//			GetExcellonData().AddSALocalMarkData(crd,smIndex,saIndex);
//		}
		else if(m_iSABlockState==M02LOCALMARK)
		{
			GetExcellonData().AddM02LocalMarkData(crd,lmIndex,saIndex);
		}
		else if(m_iSABlockState==M02OTHERDATA)
		{
			GetExcellonData().AddM02OtherData(crd,saIndex);
		}
		else if(m_iSABlockState==SAPATTERNDATA)
		{
			GetExcellonData().AddMainMark(crd);
		}
		else if(m_iSABlockState==SAINNERMARK)
		{
			GetExcellonData().AddInnerMark(crd);
		}
		break;
	case SACENTERDATA:
		if(m_iSABlockState==SAMAINDATA)
		{
			GetExcellonData().AddSAMainDataCenter(crd,saIndex);
		}
		else if(m_iSABlockState==M02LOCALMARK)
		{
			GetExcellonData().AddM02LocalMarkDataCenter(crd,lmIndex,saIndex);
		}
		else if(m_iSABlockState==M02OTHERDATA)
		{
			GetExcellonData().AddM02OtherDataCenter(crd,saIndex);
		}
		m_iSADataProperty = SACOORDDATA;		
		break;
	case M02LOCALMARKDATA:
		if(m_iSABlockState==M02LOCALMARK)
		{
			GetExcellonData().AddM02LocalMark(crd,lmIndex);
		}
		m_iSADataProperty = SACOORDDATA;		
		break;
	case SALOCALMARKDATA:
		if(m_iSABlockState==SAMAINDATA)
		{
			GetExcellonData().AddSALocalMark(crd,iSACycleNum);
		}
		m_iSADataProperty = SACOORDDATA;		
		break;
	case SAMTEXTDATA:				
		break;
	case SADTEXTDATA:				
		break;
	case SATTEXTDATA:				
		break;
	case SALTEXTDATA:				
		break;
	case SAATEXTDATA://ly add 20121230				
		break;
	case SASTEXTDATA:				
		break;
	case SASCTEXTDATA://ly add 20131104				
		break;
	case SABLOCKDATA:
		m_iSADataProperty = SACOORDDATA;		
		break;
	}
}

void DecodeSA::addSAInfo()
{
	if(m_iSABlockState==SAMAINDATA)
	{
		GetExcellonData().AddSAMainInfo();
	}
	else if(m_iSABlockState==M02LOCALMARK)
	{
		GetExcellonData().AddSAM02LocalMarkInfo(m_iLMIndex);
	}
	else if(m_iSABlockState==M02OTHERDATA)
	{
		GetExcellonData().AddSAM02OtherInfo();
	}
}

void DecodeSA::GetStrText(char *buf)
{
	char *pbuf;
	pbuf = buf;

	while(!EndOfLine(pbuf))
	{
		pbuf++;
	}

	m_iStrText.Format("%s",buf);

	strcpy(buf,pbuf);
}
