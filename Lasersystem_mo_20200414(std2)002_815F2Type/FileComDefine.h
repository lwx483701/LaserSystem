#ifndef _FILECOMDEFINE_H
#define _FILECOMDEFINE_H

//Excellon 1
//ExcHeader

//#define TABLEWIDTH				550
//#define TABLEHEIGHT				650

#define ExcFileComma			_T(",")
#define ExcToolsMaxNum			32
#define ExcHeaderBegin			_T("M48")
#define ExcHeaderEnd			_T("M95")
#define ExcHeaderFormat			_T("FMAT")
#define ExcHeaderUnit_Inch		_T("INCH")
#define ExcHeaderUnit_Metric	_T("METRIC")
#define ExcHeaderUnitLeadZero	_T("LZ")
#define ExcHeaderUnitTrailZero	_T("TZ")

#define ExcHeaderLeadZero		_T("LEAD")
#define ExcHeaderTrailZero		_T("TRAIL")	
	
#define ExcHeaderCrdMode		_T("ICI")
#define ExcHeaderToolIndicate	_T("T")	 
#define ExcHeaderRewindStop 	_T("%")
//Body
#define ExcBlockX_CrdIndicate	_T("X")	
#define ExcBlockY_CrdIndicate	_T("Y")	
#define	ExcBlockCrdModeAbs		_T("G90")	
#define ExcBlockCrdModeInc		_T("G91")
#define ExcZeroSet				_T("G92")
#define ExcZeroSet1				_T("G93")	
#define ExcFiducialIndicate1	_T("G82")
#define ExcFiducialIndicate2	_T("G83")


#define ExcBlockPatternEnd		_T("M01")
#define ExcBlockPatternOffset	_T("M02")
#define ExcBlockStepRepeatEnd 	_T("M08")
#define ExcBlockPatternBegin	_T("M25")

#define ExcBlockUnit_Metric		_T("M71")
#define ExcBlockUnit_Inch		_T("M72")
#define ExcBlockSwapAxis		_T("M70")
#define EXcBlockMirrorX			_T("M80")
#define EXcBlockMirrorY			_T("M90")

#define ExcBlockDrillTextH		_T("M97")
#define ExcBlockDrillTextV		_T("M98")

#define ExcRepeatIndicate		_T("R")
#define ExcToolIndicate			_T("T")

#define ExcFileEnd				_T("M30")

#define ExcFileSplitter			_T("M29")							//20161109

#define ExcLocalMarkIndicate	_T("A")
		
//Excellon 2
//Gerber

#define FileReadSuccess			0
#define FileReadFalse			1
#define FileReadUnfind			2
#define FileReadCommandError	3
#define FileReadDataError		4
#define FileUnknowFileFormat    5
#define FileWidthOutRange       6
#define FileHeightOutRange      7



#define NumString	 _T("0123456789-")
#define MachineText  _T("MACHINE")
#define DayText		 _T("DAY")
#define TimeText	 _T("TIME")
#define LOTIDText    _T("LOTID")
#define AXISNOText    _T("AXISNO")//ly add 20121230
#define SCALEText    _T("SCALE")//ly add 20131104

//SA
 #define Glv_ScanSize		_T("SCANSIZE")
 #define Glv_ScanBit		_T("SCANBIT")//ly add 20130412
 #define SubAreaRowNum		_T("SUBAREAROW")
 #define SubAreaColNum		_T("SUBAREACOL")
 #define SAToolBlock		_T("[TOOL]"	)		
 #define SAMainDataBlock	_T("[MAINDATA]"	)	
 #define SALocalMarkBlock	_T("[LOCALMARK]")
 #define SAOtherDataBlock	_T("[OTHERDATA]")
 #define SATextBlock		_T("[TEXT]"	)
 #define SACenter			_T("CENTER")
 #define StrText			_T("STRING=")
 #define MText				_T("$M$")
 #define DText				_T("$D$")
 #define TText				_T("$T$")
 #define LText				_T("$L$")
 #define AText				_T("$A$")//ly add 20121230
 #define SCText				_T("$SC$")//ly add 20131104
 #define SText				_T("$S$")	
 #define TextDirect			_T("DIR")
 #define TextPos			_T("POS")
 #define PatternData		_T("G82")
 #define InnerMarkData		_T("G83")
 #define M02LocalMarkZone	_T("LM")
 #define SALocalMarkZone	_T("SM")	
 #define SubAreaZone		_T("SA")
 #define Tool				_T("T")
 #define M02LocalMark		_T("A")
 #define SALocalMark		_T("B")
 #define X_crd				_T("X")
 #define Y_crd				_T("Y")
 #define SAFileEnd			_T("M30")

////////////////////////////////////////
#endif