#include <afxwin.h>         // MFC core and standard components
#include <atlbase.h>
#include "public.h"	

#pragma warning(disable:4192 4146)
// Cognex Display Controls
#import "Cognex_6_2_32-bit\CogDisplay.ocx" raw_interfaces_only, raw_native_types, no_namespace, named_guids, no_implementation
// Cognex Core Type Library
#import "Cognex_6_2_32-bit\cogxstd.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids, no_implementation
// Cognex Calibration and Fixturing Type Library
#import "Cognex_6_2_32-bit\cogxcalibfix.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids, no_implementation
// Cognex Image File Type Library
#import "Cognex_6_2_32-bit\cogxidb.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids, no_implementation
// Cognex PatMax Alignment Type Library
#import "Cognex_6_2_32-bit\cogxpma.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids, no_implementation
// Cognex ToolGroup Type Library
#import "Cognex_6_2_32-bit\cogxtoolgrp.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids, no_implementation
// Cognex Image File Edit Controls
#import "Cognex_6_2_32-bit\CogImageFileCtl.ocx" raw_interfaces_only, raw_native_types, no_implementation
// Cognex PatMax Alignment Edit Controls
#import "Cognex_6_2_32-bit\CogPMAlignCtl.ocx" raw_interfaces_only, raw_native_types, no_implementation
#pragma warning(default:4192 4146)

#include <afxdlgs.h>

BOOL __declspec(dllexport) CogInit();
void __declspec(dllexport) CogSetShapePolarity(CogShapeExtractPolarityConstants nShapePolarity);
void __declspec(dllexport) CogSetTrainParam(int glas,double glc,double glf);
BOOL __declspec(dllexport) CogTrain(char *TrainFileName,bool isHighSensitivityUsed=false);						//20170103
BOOL __declspec(dllexport) CogFind(char *SearchFileName, double &fXOffect, double &fYOffect, double minScore,double& Score,double dbOutsideThreadHold,long contrast);//ly add Score 20130724 得到当前匹配值，保存并显示

BOOL __declspec(dllexport) CogSetMapPoint(int nHead,Coord crdSource,Coord& crdTarget);
void __declspec(dllexport) CogSetNPointToNPointDOFConstants(CogNPointToNPointDOFConstants ptpDOF);
BOOL __declspec(dllexport) CogGetTransform(int nHead,HoleCoordV& crdSourceV,HoleCoordV& crdTargetV,TransformParam& tfParam);
BOOL __declspec(dllexport) CogSetTransform(int nHead,double ScalingX,double ScalingY,double RotationX,double RotationY,double TranslationX,double TranslationY);
BOOL __declspec(dllexport) CogTableMapPoint(int nHead,int label,Coord crdSource,Coord& crdTarget);
BOOL __declspec(dllexport) CogTableTransform(int nHead,int label,HoleCoordV& crdSourceV,HoleCoordV& crdTargetV);
void __declspec(dllexport) CogRelease();
