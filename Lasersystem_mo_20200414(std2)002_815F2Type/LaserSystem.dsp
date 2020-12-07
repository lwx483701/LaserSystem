# Microsoft Developer Studio Project File - Name="LaserSystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LaserSystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LaserSystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LaserSystem.mak" CFG="LaserSystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LaserSystem - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LaserSystem - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LaserSystem - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32_LEAN_AND_MEAN" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"LaserSystem_re.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "LaserSystem - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"LaserSystem_de.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LaserSystem - Win32 Release"
# Name "LaserSystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdoClass\Ado.cpp
# End Source File
# Begin Source File

SOURCE=.\AdoClass\AdoCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\AdoClass\AdoRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\ColorComBox\BSColorComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\calc.cpp
# End Source File
# Begin Source File

SOURCE=.\CBmpMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\CCheckSK.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\CJColorPicker\CJColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\CJColorPicker\CJColorPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\ComboInListView.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlManipulator.cpp
# End Source File
# Begin Source File

SOURCE=".\Shared Classes\CSVLineParser\CSVLineParser.cpp"
# End Source File
# Begin Source File

SOURCE=.\Decode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRotate.cpp
# End Source File
# Begin Source File

SOURCE=.\Excellon.cpp
# End Source File
# Begin Source File

SOURCE=.\FileInfoSettingView.cpp
# End Source File
# Begin Source File

SOURCE=.\FilePointView.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxOutBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SmartEdit\GridCtrl.cpp
# ADD CPP /I "..\.."
# End Source File
# Begin Source File

SOURCE=.\HttpClient.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageParaSetView.cpp
# End Source File
# Begin Source File

SOURCE=.\ImesSettingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Info.cpp
# End Source File
# Begin Source File

SOURCE=.\IngredientInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SmartEdit\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\json_reader.cpp
# End Source File
# Begin Source File

SOURCE=.\json_value.cpp
# End Source File
# Begin Source File

SOURCE=.\json_writer.cpp
# End Source File
# Begin Source File

SOURCE=.\LampAdjDlgView.cpp
# End Source File
# Begin Source File

SOURCE=.\LaserSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\LaserSystem.rc
# End Source File
# Begin Source File

SOURCE=.\LaserSystemDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LaserSystemView.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\listeditctrl.cpp
# End Source File
# Begin Source File

SOURCE=".\Shared Classes\ListReport\ListItem.cpp"
# End Source File
# Begin Source File

SOURCE=".\Shared Classes\ListReport\ListReport.cpp"
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\ListTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainRunView.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkMake.cpp
# End Source File
# Begin Source File

SOURCE=.\MODESWITCHDIALOG.cpp
# End Source File
# Begin Source File

SOURCE=.\MotionControlTestView.cpp
# End Source File
# Begin Source File

SOURCE=.\MotionParameterView.cpp
# End Source File
# Begin Source File

SOURCE=.\OperateControl.cpp
# End Source File
# Begin Source File

SOURCE=.\OperateRefCoord.cpp
# End Source File
# Begin Source File

SOURCE=.\PointcontrlView.cpp
# End Source File
# Begin Source File

SOURCE=.\PositionErrValueView.cpp
# End Source File
# Begin Source File

SOURCE=.\PrecisionSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcLogin_FZ.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcLogin_SN.cpp
# End Source File
# Begin Source File

SOURCE=.\PROCPARAVIEW.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressCheckCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\Progress\ProgressWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ScaleSetDlgView.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalInputView.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalOutView.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SmartEdit\SmartEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SortListCtr\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SortListCtr\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticButton.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\supergridctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SysParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\SysParamView.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemLogView.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFunctionView.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolParaView.cpp
# End Source File
# Begin Source File

SOURCE=.\TransParentButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlTool\TreeCtrl\TreeCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualFx.cpp
# End Source File
# Begin Source File

SOURCE=.\WarningInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdoClass\Ado.h
# End Source File
# Begin Source File

SOURCE=.\AdoClass\AdoCommand.h
# End Source File
# Begin Source File

SOURCE=.\AdoClass\AdoRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\ColorComBox\BSColorComboBox.h
# End Source File
# Begin Source File

SOURCE=.\calc.h
# End Source File
# Begin Source File

SOURCE=.\CBmpMenu.h
# End Source File
# Begin Source File

SOURCE=.\CCheckSK.h
# End Source File
# Begin Source File

SOURCE=.\CheckerCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\CJColorPicker\CJColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\CJColorPicker\CJColorPopup.h
# End Source File
# Begin Source File

SOURCE=.\ColorProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\ComboInListView.h
# End Source File
# Begin Source File

SOURCE=.\ControlManipulator.h
# End Source File
# Begin Source File

SOURCE=".\Shared Classes\CSVLineParser\CSVLineParser.h"
# End Source File
# Begin Source File

SOURCE=.\Decode.h
# End Source File
# Begin Source File

SOURCE=.\DlgRotate.h
# End Source File
# Begin Source File

SOURCE=.\Excellon.h
# End Source File
# Begin Source File

SOURCE=.\FileComDefine.h
# End Source File
# Begin Source File

SOURCE=.\FileInfoSettingView.h
# End Source File
# Begin Source File

SOURCE=.\FilePointView.h
# End Source File
# Begin Source File

SOURCE=.\GfxOutBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SmartEdit\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\HttpClient.h
# End Source File
# Begin Source File

SOURCE=.\ImageParaSetView.h
# End Source File
# Begin Source File

SOURCE=.\ImesSettingDialog.h
# End Source File
# Begin Source File

SOURCE=.\Info.h
# End Source File
# Begin Source File

SOURCE=.\IngredientInfoView.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SmartEdit\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\LampAdjDlgView.h
# End Source File
# Begin Source File

SOURCE=.\LaserSystem.h
# End Source File
# Begin Source File

SOURCE=.\LaserSystemDoc.h
# End Source File
# Begin Source File

SOURCE=.\LaserSystemView.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\listeditctrl.h
# End Source File
# Begin Source File

SOURCE=".\Shared Classes\ListReport\ListItem.h"
# End Source File
# Begin Source File

SOURCE=".\Shared Classes\ListReport\ListReport.h"
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\ListTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\LoginDialog.h
# End Source File
# Begin Source File

SOURCE=.\LoginView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainRunView.h
# End Source File
# Begin Source File

SOURCE=.\MarkMake.h
# End Source File
# Begin Source File

SOURCE=.\MatchInclude\Match.h
# End Source File
# Begin Source File

SOURCE=.\MODESWITCHDIALOG.h
# End Source File
# Begin Source File

SOURCE=.\MotionControlTestView.h
# End Source File
# Begin Source File

SOURCE=.\MotionParameterView.h
# End Source File
# Begin Source File

SOURCE=.\OperateControl.h
# End Source File
# Begin Source File

SOURCE=.\OperateRefCoord.h
# End Source File
# Begin Source File

SOURCE=.\PointcontrlView.h
# End Source File
# Begin Source File

SOURCE=.\PositionErrValueView.h
# End Source File
# Begin Source File

SOURCE=.\PrecisionSelect.h
# End Source File
# Begin Source File

SOURCE=.\ProcLogin_FZ.h
# End Source File
# Begin Source File

SOURCE=.\ProcLogin_SN.h
# End Source File
# Begin Source File

SOURCE=.\PROCPARAVIEW.h
# End Source File
# Begin Source File

SOURCE=.\ProgressCheckCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\Progress\ProgressWnd.h
# End Source File
# Begin Source File

SOURCE=.\public.h
# End Source File
# Begin Source File

SOURCE=.\registry.h
# End Source File
# Begin Source File

SOURCE=.\AdoClass\resource.h
# End Source File
# Begin Source File

SOURCE=.\ScaleSetDlgView.h
# End Source File
# Begin Source File

SOURCE=.\SignalInputView.h
# End Source File
# Begin Source File

SOURCE=.\SignalOutView.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SmartEdit\SmartEdit.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SortListCtr\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SortListCtr\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StaticButton.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\SuperGrid\supergridctrl.h
# End Source File
# Begin Source File

SOURCE=.\SysParameter.h
# End Source File
# Begin Source File

SOURCE=.\SysParamView.h
# End Source File
# Begin Source File

SOURCE=.\SystemLogView.h
# End Source File
# Begin Source File

SOURCE=.\TestFunctionView.h
# End Source File
# Begin Source File

SOURCE=.\ToolParameter.h
# End Source File
# Begin Source File

SOURCE=.\ToolParaView.h
# End Source File
# Begin Source File

SOURCE=.\ToolUtil.h
# End Source File
# Begin Source File

SOURCE=.\TransParentButton.h
# End Source File
# Begin Source File

SOURCE=.\ControlTool\TreeCtrl\TreeCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\VisualFx.h
# End Source File
# Begin Source File

SOURCE=.\WarningInfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\2DN.ICO
# End Source File
# Begin Source File

SOURCE=.\res\2UP.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ADD.ico
# End Source File
# Begin Source File

SOURCE=.\res\AMGR.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ARW04LT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ARW04RT.ICO
# End Source File
# Begin Source File

SOURCE=".\res\BGA EditorDoc.ico"
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BLUEF~22.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BMPBACK.BMP
# End Source File
# Begin Source File

SOURCE=.\res\BMPGRAPH.BMP
# End Source File
# Begin Source File

SOURCE=.\res\chchangeL.ICO
# End Source File
# Begin Source File

SOURCE=.\res\chchangeR.ico
# End Source File
# Begin Source File

SOURCE=.\res\checked.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Clean.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor10.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor11.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor12.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor13.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor14.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor3.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor4.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor5.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor6.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor7.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor8.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor9.cur
# End Source File
# Begin Source File

SOURCE=.\res\DEL.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Delete1.ico
# End Source File
# Begin Source File

SOURCE=.\res\display.ico
# End Source File
# Begin Source File

SOURCE=.\res\dnunload.ico
# End Source File
# Begin Source File

SOURCE=.\res\DowN.ICO
# End Source File
# Begin Source File

SOURCE=.\res\END.ico
# End Source File
# Begin Source File

SOURCE=.\res\ENDE.ico
# End Source File
# Begin Source File

SOURCE=.\res\eraser.ico
# End Source File
# Begin Source File

SOURCE=.\res\EXIT.ico
# End Source File
# Begin Source File

SOURCE=.\res\fidpos.ico
# End Source File
# Begin Source File

SOURCE=.\res\fidpos1.ico
# End Source File
# Begin Source File

SOURCE=.\res\File.ico
# End Source File
# Begin Source File

SOURCE=".\res\fire-1.ico"
# End Source File
# Begin Source File

SOURCE=.\res\fire.ico
# End Source File
# Begin Source File

SOURCE=.\res\folders.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Home.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icr_hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\imageList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\KEY04.ICO
# End Source File
# Begin Source File

SOURCE=.\res\KEY041.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Lamp.ico
# End Source File
# Begin Source File

SOURCE=.\res\laser.ico
# End Source File
# Begin Source File

SOURCE=.\res\LaserSystem.ico
# End Source File
# Begin Source File

SOURCE=.\res\LaserSystem.rc2
# End Source File
# Begin Source File

SOURCE=.\res\LaserSystemDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ledgoff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ledgon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LedGreen.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedRedOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ledredon.ico
# End Source File
# Begin Source File

SOURCE=.\res\Left.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Lightning.ico
# End Source File
# Begin Source File

SOURCE=.\res\LIGHTOFF.ICO
# End Source File
# Begin Source File

SOURCE=.\res\LIGHTON.ICO
# End Source File
# Begin Source File

SOURCE=.\res\load.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Move.ico
# End Source File
# Begin Source File

SOURCE=.\res\OOFL.ICO
# End Source File
# Begin Source File

SOURCE=.\res\openfile.ico
# End Source File
# Begin Source File

SOURCE=.\res\pattern.ico
# End Source File
# Begin Source File

SOURCE=.\res\patternc.ICO
# End Source File
# Begin Source File

SOURCE=.\res\PAUSE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\piunload.ico
# End Source File
# Begin Source File

SOURCE=.\res\pload.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pnp1.ico
# End Source File
# Begin Source File

SOURCE=.\res\PnpDn.ico
# End Source File
# Begin Source File

SOURCE=.\res\punload.ico
# End Source File
# Begin Source File

SOURCE=.\res\reset.ico
# End Source File
# Begin Source File

SOURCE=.\res\Right.ICO
# End Source File
# Begin Source File

SOURCE=.\res\savePart.ICO
# End Source File
# Begin Source File

SOURCE=.\res\SELCUR.cur
# End Source File
# Begin Source File

SOURCE=.\res\SelPoint.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Set.ICO
# End Source File
# Begin Source File

SOURCE=.\res\showdn.ico
# End Source File
# Begin Source File

SOURCE=.\res\showUp.ico
# End Source File
# Begin Source File

SOURCE=.\res\Snap.ICO
# End Source File
# Begin Source File

SOURCE=".\res\Soap Bubbles.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Sorb.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ssharp.ico
# End Source File
# Begin Source File

SOURCE=.\res\stop.ICO
# End Source File
# Begin Source File

SOURCE=.\res\TabWnd.ico
# End Source File
# Begin Source File

SOURCE=.\res\TabWndDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\target.ico
# End Source File
# Begin Source File

SOURCE=.\res\toload.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeImageList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\unchecked.ICO
# End Source File
# Begin Source File

SOURCE=.\res\UP.ICO
# End Source File
# Begin Source File

SOURCE=.\res\upunload.ico
# End Source File
# Begin Source File

SOURCE=.\res\wReset.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZDOWN.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Zero.ico
# End Source File
# Begin Source File

SOURCE=.\res\Zoom.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZoomInM.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZoomNone.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZoomOut.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZUP.ICO
# End Source File
# End Group
# End Target
# End Project
# Section LaserSystem : {CDE57A41-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CDataGrid
# 	2:10:HeaderFile:datagrid.h
# 	2:8:ImplFile:datagrid.cpp
# End Section
# Section LaserSystem : {CDE57A50-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumns
# 	2:10:HeaderFile:columns.h
# 	2:8:ImplFile:columns.cpp
# End Section
# Section LaserSystem : {91EB06B8-46AC-4A44-A98A-CA59B94E87B8}
# 	1:25:IDD_DIALOG_COGNEXSHOWVIEW:102
# 	2:16:Resource Include:resource.h
# 	2:25:IDD_DIALOG_COGNEXSHOWVIEW:IDD_DIALOG_COGNEXSHOWVIEW
# 	2:10:ENUM: enum:enum
# 	2:22:CLASS: CCognexShowView:CCognexShowView
# 	2:16:CognexShowView.h:CognexShowView.h
# 	2:18:CognexShowView.cpp:CognexShowView.cpp
# 	2:19:Application Include:lasersystem.h
# End Section
# Section LaserSystem : {CDE57A4F-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumn
# 	2:10:HeaderFile:column.h
# 	2:8:ImplFile:column.cpp
# End Section
# Section LaserSystem : {E7F7370A-F830-4E35-BA49-05B7A92ABB82}
# 	2:16:ClientSocket.cpp:ClientSocket.cpp
# 	2:15:CLASS: userinfo:userinfo
# 	2:20:CLASS: CClientSocket:CClientSocket
# 	2:14:ClientSocket.h:ClientSocket.h
# 	2:19:Application Include:lasersystem.h
# End Section
# Section LaserSystem : {CDE57A43-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:21:DefaultSinkHeaderFile:datagrid.h
# 	2:16:DefaultSinkClass:CDataGrid
# End Section
