/// @file A3200EnumNames.h
/// \brief Contains functions to retrieve the names of various enumeration values.
/// 
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_ENUM_NAMES__
#define __A3200_ENUM_NAMES__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"
/// @defgroup enumname Enumeration Name Functions

#ifdef __cplusplus
extern "C" {
#endif
/// \brief Retrieves the name of a TASKSTATE value.
///
/// @ingroup enumname
///
/// @param[in] value The TASKSTATE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTaskStateGetValueName(TASKSTATE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a MOTORTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The MOTORTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumMotorTypeGetValueName(MOTORTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a HOMETYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The HOMETYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumHomeTypeGetValueName(HOMETYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a POSITIONFEEDBACKTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The POSITIONFEEDBACKTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumPositionFeedbackTypeGetValueName(POSITIONFEEDBACKTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a VELOCITYFEEDBACKTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The VELOCITYFEEDBACKTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumVelocityFeedbackTypeGetValueName(VELOCITYFEEDBACKTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a TASKEXECUTIONMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The TASKEXECUTIONMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTaskExecutionModeGetValueName(TASKEXECUTIONMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a PROGRAMAUTOMATIONMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The PROGRAMAUTOMATIONMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumProgramAutomationModeGetValueName(PROGRAMAUTOMATIONMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a UNITSTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The UNITSTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumUnitsTypeGetValueName(UNITSTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a QUEUESTATUS bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The QUEUESTATUS enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumQueueStatusGetBitName(QUEUESTATUS bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a WAITOPTION value.
///
/// @ingroup enumname
///
/// @param[in] value The WAITOPTION enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumWaitOptionGetValueName(WAITOPTION value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a DATACOLLECTIONFLAGS bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The DATACOLLECTIONFLAGS enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumDataCollectionFlagsGetBitName(DATACOLLECTIONFLAGS bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a PIEZODEFAULTSERVOSTATE value.
///
/// @ingroup enumname
///
/// @param[in] value The PIEZODEFAULTSERVOSTATE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumPiezoDefaultServoStateGetValueName(PIEZODEFAULTSERVOSTATE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a RESOLUTESTATUS bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The RESOLUTESTATUS enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumResoluteStatusGetBitName(RESOLUTESTATUS bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a LOOPTRANSMISSIONMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The LOOPTRANSMISSIONMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumLoopTransmissionModeGetValueName(LOOPTRANSMISSIONMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a LOOPTRANSMISSIONTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The LOOPTRANSMISSIONTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumLoopTransmissionTypeGetValueName(LOOPTRANSMISSIONTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a ONOFF value.
///
/// @ingroup enumname
///
/// @param[in] value The ONOFF enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumOnOffGetValueName(ONOFF value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a PSOMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The PSOMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumPsoModeGetValueName(PSOMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a PSOWINDOWDEPENDANCE value.
///
/// @ingroup enumname
///
/// @param[in] value The PSOWINDOWDEPENDANCE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumPsoWindowDependanceGetValueName(PSOWINDOWDEPENDANCE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a REGISTERTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The REGISTERTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumRegisterTypeGetValueName(REGISTERTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a INPUTBOXCLICKEDBUTTON value.
///
/// @ingroup enumname
///
/// @param[in] value The INPUTBOXCLICKEDBUTTON enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumInputBoxClickedButtonGetValueName(INPUTBOXCLICKEDBUTTON value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a INPUTBOXKIND value.
///
/// @ingroup enumname
///
/// @param[in] value The INPUTBOXKIND enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumInputBoxKindGetValueName(INPUTBOXKIND value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a BUILDRESULTKIND value.
///
/// @ingroup enumname
///
/// @param[in] value The BUILDRESULTKIND enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumBuildResultKindGetValueName(BUILDRESULTKIND value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a AXISCALIBRATION value.
///
/// @ingroup enumname
///
/// @param[in] value The AXISCALIBRATION enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumAxisCalibrationGetValueName(AXISCALIBRATION value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a FLASHCONFIGSTATUS bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The FLASHCONFIGSTATUS enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumFlashConfigStatusGetBitName(FLASHCONFIGSTATUS bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a AXISSTATUS bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The AXISSTATUS enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumAxisStatusGetBitName(AXISSTATUS bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a AXISFAULT bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The AXISFAULT enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumAxisFaultGetBitName(AXISFAULT bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a DRIVESTATUS bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The DRIVESTATUS enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumDriveStatusGetBitName(DRIVESTATUS bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a TASKSTATUS0 bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The TASKSTATUS0 enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTaskStatus0GetBitName(TASKSTATUS0 bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a TASKSTATUS1 bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The TASKSTATUS1 enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTaskStatus1GetBitName(TASKSTATUS1 bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a TASKSTATUS2 bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The TASKSTATUS2 enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTaskStatus2GetBitName(TASKSTATUS2 bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a TASKMODE bit value.
///
/// @ingroup enumname
///
/// @param[in] bitValue The TASKMODE enumeration bit value for which to retrieve the string name. Note that this bit value must contain only one bit that is high.
/// @param[in] bitValueNameBuffer The output buffer that will contain the string name of the enumeration bit value.
/// @param[in] bitValueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration bit value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTaskModeGetBitName(TASKMODE bitValue, LPSTR bitValueNameBuffer, DWORD bitValueNameBufferSize);

/// \brief Retrieves the name of a RAMPTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The RAMPTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumRampTypeGetValueName(RAMPTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a RAMPMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The RAMPMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumRampModeGetValueName(RAMPMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a GEARINGTRACKINGMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The GEARINGTRACKINGMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumGearingTrackingModeGetValueName(GEARINGTRACKINGMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a CAMMINGTRACKINGMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The CAMMINGTRACKINGMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumCammingTrackingModeGetValueName(CAMMINGTRACKINGMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a CAMMINGINTERPOLATIONTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The CAMMINGINTERPOLATIONTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumCammingInterpolationTypeGetValueName(CAMMINGINTERPOLATIONTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a CAMMINGSYNCMODE value.
///
/// @ingroup enumname
///
/// @param[in] value The CAMMINGSYNCMODE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumCammingSyncModeGetValueName(CAMMINGSYNCMODE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a EDGE value.
///
/// @ingroup enumname
///
/// @param[in] value The EDGE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumEdgeGetValueName(EDGE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a TIMEUNIT value.
///
/// @ingroup enumname
///
/// @param[in] value The TIMEUNIT enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumTimeUnitGetValueName(TIMEUNIT value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a WINDOWEVENT value.
///
/// @ingroup enumname
///
/// @param[in] value The WINDOWEVENT enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumWindowEventGetValueName(WINDOWEVENT value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a FIBERSEARCHRESULT value.
///
/// @ingroup enumname
///
/// @param[in] value The FIBERSEARCHRESULT enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumFiberSearchResultGetValueName(FIBERSEARCHRESULT value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a CALLBACKARGUMENTTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The CALLBACKARGUMENTTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumCallbackArgumentTypeGetValueName(CALLBACKARGUMENTTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a SAFEZONETYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The SAFEZONETYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumSafeZoneTypeGetValueName(SAFEZONETYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a COMMANDOUTPUTTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The COMMANDOUTPUTTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumCommandOutputTypeGetValueName(COMMANDOUTPUTTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a DATACOLLECTIONSAMPLETRIGGER value.
///
/// @ingroup enumname
///
/// @param[in] value The DATACOLLECTIONSAMPLETRIGGER enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumDataCollectionSampleTriggerGetValueName(DATACOLLECTIONSAMPLETRIGGER value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a BINARYCALIBRATIONACTIONTABLETYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The BINARYCALIBRATIONACTIONTABLETYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumBinaryCalibrationActionTableTypeGetValueName(BINARYCALIBRATIONACTIONTABLETYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a BINARYCALIBRATIONACTIONSTATUS value.
///
/// @ingroup enumname
///
/// @param[in] value The BINARYCALIBRATIONACTIONSTATUS enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumBinaryCalibrationActionStatusGetValueName(BINARYCALIBRATIONACTIONSTATUS value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a POSITIONFEEDBACKCHANNEL value.
///
/// @ingroup enumname
///
/// @param[in] value The POSITIONFEEDBACKCHANNEL enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumPositionFeedbackChannelGetValueName(POSITIONFEEDBACKCHANNEL value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a VELOCITYFEEDBACKCHANNEL value.
///
/// @ingroup enumname
///
/// @param[in] value The VELOCITYFEEDBACKCHANNEL enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumVelocityFeedbackChannelGetValueName(VELOCITYFEEDBACKCHANNEL value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

/// \brief Retrieves the name of a DRIVECOMMUNICATIONTYPE value.
///
/// @ingroup enumname
///
/// @param[in] value The DRIVECOMMUNICATIONTYPE enumeration value for which to retrieve the string name.
/// @param[in] valueNameBuffer The output buffer that will contain the string name of the enumeration value.
/// @param[in] valueNameBufferSize The size, in bytes, of the output buffer that will contain the string name of the enumeration value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200EnumDriveCommunicationTypeGetValueName(DRIVECOMMUNICATIONTYPE value, LPSTR valueNameBuffer, DWORD valueNameBufferSize);

#ifdef __cplusplus
}
#endif
#endif // __A3200_ENUM_NAMES__

