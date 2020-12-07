/// \file A3200StatusItemInfo.h
/// \brief Contains the defines for status item numbers.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
///

#ifndef __A3200_STATUS_ITEM_INFO_H__
#define __A3200_STATUS_ITEM_INFO_H__

typedef enum {
	/// \brief Axis signal. This item returns the position feedback. No extra argument.
	STATUSITEM_PositionFeedback = 0,
	/// \brief Axis signal. This item returns the position command. No extra argument.
	STATUSITEM_PositionCommand = 1,
	/// \brief Axis signal. This item returns the position error. No extra argument.
	STATUSITEM_PositionError = 2,
	/// \brief Axis signal. This item returns the velocity feedback. No extra argument.
	STATUSITEM_VelocityFeedback = 3,
	/// \brief Axis signal. This item returns the commanded velocity of the axis. No extra argument.
	STATUSITEM_VelocityCommand = 4,
	/// \brief Axis signal. This item returns the velocity error. No extra argument.
	STATUSITEM_VelocityError = 5,
	/// \brief Axis signal. This item returns the value of the acceleration command. No extra argument.
	STATUSITEM_AccelerationCommand = 6,
	/// \brief Axis signal. This item returns the current feedback. No extra argument.
	STATUSITEM_CurrentFeedback = 7,
	/// \brief Axis signal. This item returns the current command. No extra argument.
	STATUSITEM_CurrentCommand = 8,
	/// \brief Axis signal. This item returns the current error. No extra argument.
	STATUSITEM_CurrentError = 9,
	/// \brief Axis signal. This item returns the value of analog input 0. The returned value corresponds to channel 0 of $AI. No extra argument.
	STATUSITEM_AnalogInput0 = 10,
	/// \brief Axis signal. This item returns the value of analog input 1. The returned value corresponds to channel 1 of $AI. No extra argument.
	STATUSITEM_AnalogInput1 = 11,
	/// \brief Axis signal. This item returns the raw position command. No extra argument.
	STATUSITEM_PositionCommandRaw = 12,
	/// \brief Axis signal. This item returns the raw velocity command. No extra argument.
	STATUSITEM_VelocityCommandRaw = 13,
	/// \brief Axis signal. This item returns the position feedback from the auxiliary encoder. No extra argument.
	STATUSITEM_PositionFeedbackAuxiliary = 14,
	/// \brief Axis signal. This item returns the value of the 32-bit digital input word that is read from the drive. The returned value corresponds to the individual $DI bits. Extra argument: Mask.
	STATUSITEM_DigitalInput = 15,
	/// \brief Axis signal. This item returns the value of the 32-bit digital output word that is read from the drive. The returned value corresponds to the individual $DO bits. Extra argument: Mask.
	STATUSITEM_DigitalOutput = 16,
	/// \brief Axis signal. This item returns the value of the specified fixture offset. Extra argument: Fixture Offset Index.
	STATUSITEM_FixtureOffset = 18,
	/// \brief Axis signal. This item returns the value of analog input 2. The returned value corresponds to channel 2 of $AI. No extra argument.
	STATUSITEM_AnalogInput2 = 28,
	/// \brief Axis signal. This item returns the value of analog input 3. The returned value corresponds to channel 3 of $AI. No extra argument.
	STATUSITEM_AnalogInput3 = 29,
	/// \brief Axis signal. This item returns the value of analog output 0. The returned value corresponds to channel 0 of $AO. No extra argument.
	STATUSITEM_AnalogOutput0 = 36,
	/// \brief Axis signal. This item returns the value of analog output 1. The returned value corresponds to channel 1 of $AO. No extra argument.
	STATUSITEM_AnalogOutput1 = 37,
	/// \brief Axis signal. This item returns the value of analog output 2. The returned value corresponds to channel 2 of $AO. No extra argument.
	STATUSITEM_AnalogOutput2 = 38,
	/// \brief Axis signal. This item returns the value of analog output 3. The returned value corresponds to channel 3 of $AO. No extra argument.
	STATUSITEM_AnalogOutput3 = 39,
	/// \brief Axis signal. This item returns the coordinated target position command. No extra argument.
	STATUSITEM_CoordinatedPositionTarget = 46,
	/// \brief Axis signal. This item returns the value of the Drive Status word. Extra argument: Mask.
	STATUSITEM_DriveStatus = 47,
	/// \brief Axis signal. This item returns the value of the Axis Status word. Extra argument: Mask.
	STATUSITEM_AxisStatus = 48,
	/// \brief Axis signal. This item returns the value of the Axis Fault word. Extra argument: Mask.
	STATUSITEM_AxisFault = 49,
	/// \brief Axis signal. This item returns the value of the raw acceleration command. No extra argument.
	STATUSITEM_AccelerationCommandRaw = 50,
	/// \brief Axis signal. This item returns the 1D + 2D position calibration contribution with the backlash contribution. No extra argument.
	STATUSITEM_PositionCalibrationAll = 55,
	/// \brief Axis signal. This item returns the position feedback with rollover applied. No extra argument.
	STATUSITEM_PositionFeedbackRollover = 69,
	/// \brief Axis signal. This item returns the position command with rollover applied. No extra argument.
	STATUSITEM_PositionCommandRollover = 70,
	/// \brief Axis signal. This item returns the position feedback from the auxiliary encoder with rollover applied. No extra argument.
	STATUSITEM_PositionFeedbackAuxiliaryRollover = 71,
	/// \brief Axis signal. This item returns the average velocity feedback. The average value is calculated over a period of 100 milliseconds. No extra argument.
	STATUSITEM_VelocityFeedbackAverage = 72,
	/// \brief Axis signal. This item returns the average current feedback. The average value is calculated over a period of 100 milliseconds. No extra argument.
	STATUSITEM_CurrentFeedbackAverage = 73,
	/// \brief Axis signal. This item returns the value of an axis parameter. Extra argument: Parameter Index.
	STATUSITEM_AxisParameter = 76,
	/// \brief Axis signal. This item returns the peak current rating. No extra argument.
	STATUSITEM_PeakCurrent = 78,
	/// \brief Axis signal. This item returns the backlash contribution. No extra argument.
	STATUSITEM_Backlash = 81,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_HomeState = 82,
	/// \brief Axis signal. This item returns the 2D position calibration contribution. No extra argument.
	STATUSITEM_PositionCalibration2D = 83,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_NormalcyDebug = 84,
	/// \brief Axis signal. This item returns the total move time of the last move. No extra argument.
	STATUSITEM_TotalMoveTime = 85,
	/// \brief Axis signal. This item returns the stability 0 settle time. No extra argument.
	STATUSITEM_Stability0SettleTime = 86,
	/// \brief Axis signal. This item returns the stability 1 settle time. No extra argument.
	STATUSITEM_Stability1SettleTime = 87,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionFeedbackDrive = 88,
	/// \brief Axis signal. This item returns the raw jerk command. No extra argument.
	STATUSITEM_JerkCommandRaw = 89,
	/// \brief Axis signal. This item returns the program position command. Commanded program position of the axis in user units. The program position command is the position commanded to the motor as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	STATUSITEM_ProgramPositionCommand = 90,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GantryOffset = 91,
	/// \brief Axis signal. This item returns the value of the position offset. The position offset value is set using the POSOFFSET SET command and is cleared using the POSOFFSET CLEAR command. No extra argument.
	STATUSITEM_PositionOffset = 92,
	/// \brief Axis signal. This item returns the number of times that the A3200 did not have sufficient time to complete all of its operations. Refer to Optimizing A3200 Performance for instructions about how to optimize the controller settings and prevent this problem. No extra argument.
	STATUSITEM_CommunicationRealTimeErrors = 93,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionCommandRawBackwardsDiff = 96,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_VelocityCommandRawBackwardsDiffDelta = 97,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionCommandDrive = 98,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveStatusActual = 99,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GantryRealignState = 100,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_TransformAutoOffset = 101,
	/// \brief Axis signal. This item returns the program position feedback. Feedback program position of the axis in user units. The program position feedback is the position feedback of the motor as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	STATUSITEM_ProgramPositionFeedback = 107,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_JogTrajectoryStatus = 116,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PingTest = 117,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainKposScale = 126,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainKiScale = 127,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainKpScale = 128,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainKpiScale = 129,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainAffScale = 130,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainVffScale = 131,
	/// \brief Axis signal. This item returns the value of the acceleration time. Refer to the RAMP TIME command for more information on setting the acceleration time. No extra argument.
	STATUSITEM_AccelerationTime = 138,
	/// \brief Axis signal. This item returns the value of the Deceleration time. Refer to the RAMP TIME command for more information on setting the deceleration time. No extra argument.
	STATUSITEM_DecelerationTime = 139,
	/// \brief Axis signal. This item returns the value of the acceleration rate. Refer to the RAMP RATE command for more information on setting the acceleration rate. No extra argument.
	STATUSITEM_AccelerationRate = 140,
	/// \brief Axis signal. This item returns the value of the deceleration rate. Refer to the RAMP RATE command for more information on setting the deceleration rate. No extra argument.
	STATUSITEM_DecelerationRate = 141,
	/// \brief Axis signal. This item returns the acceleration type. Refer to the RAMP TYPE command for more information on setting the acceleration type. No extra argument.
	STATUSITEM_AccelerationType = 142,
	/// \brief Axis signal. This item returns the deceleration type. Refer to the RAMP TYPE command for more information on setting the deceleration type. No extra argument.
	STATUSITEM_DecelerationType = 143,
	/// \brief Axis signal. This item returns the acceleration mode. Refer to the RAMP MODE command for more information on setting the acceleration mode. No extra argument.
	STATUSITEM_AccelerationMode = 144,
	/// \brief Axis signal. This item returns the deceleration mode. Refer to the RAMP MODE command for more information on setting the deceleration mode. No extra argument.
	STATUSITEM_DecelerationMode = 145,
	/// \brief Axis signal. This item returns the program position. Program position of the axis in user units. The program position reflects the position that you specify in the user program and does not include the output of any of the transformations. Extra argument: Task Index.
	STATUSITEM_ProgramPosition = 156,
	/// \brief Axis signal. This item returns the target speed for an axis in a RAPID move. No extra argument.
	STATUSITEM_SpeedTarget = 160,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionCommandPacket = 163,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveSMCMotionState = 168,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionCommandRawCal = 178,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_VelocityCommandRawCal = 179,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_VelocityCommandDrive = 180,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_AccelerationCommandDrive = 181,
	/// \brief Axis signal. This item returns the raw value of the galvo laser output. Extra argument: Mask.
	STATUSITEM_GalvoLaserOutputRaw = 183,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketInt32 = 186,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketInt16 = 187,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketInt8 = 188,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketDouble = 189,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketFloat = 190,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfaceCommandCode = 191,
	/// \brief Axis signal. This item returns the value of the acceleration feedback. No extra argument.
	STATUSITEM_AccelerationFeedback = 192,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_AccelerationCommandRawCal = 193,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionCalibrationAllDrive = 194,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_BacklashTarget = 196,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveMotionRate = 198,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveMotionDelay = 199,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CalibrationAdjustmentValue = 200,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ServoRounding = 201,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FeedforwardCurrent = 208,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketInfoBitValue = 210,
	/// \brief Axis signal. This item returns the value of the acceleration error. No extra argument.
	STATUSITEM_AccelerationError = 223,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_SuppressedFaults = 225,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketStreamingData = 226,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_PositionCommandRawUnfiltered = 227,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_TransitionOffsetErrors = 228,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FreezeVelocityCommand = 238,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FreezeVelocityFeedback = 239,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_InternalPositionOffsets = 241,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_StatusHighLevelOffsetsLastMsec = 242,
	/// \brief Axis signal. This item returns the program velocity command. The program velocity command is the velocity command as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	STATUSITEM_ProgramVelocityCommand = 250,
	/// \brief Axis signal. This item returns the program velocity feedback. The program velocity feedback is the velocity feedback as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	STATUSITEM_ProgramVelocityFeedback = 251,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveMotionDelayLive = 252,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveCommunicationDelay = 253,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveCommunicationDelayLive = 254,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketResponseInt32 = 256,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketResponseInt16 = 257,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketResponseInt8 = 258,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketResponseDouble = 259,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketResponseFloat = 260,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketBit = 261,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveInterfacePacketResponseBit = 262,
	/// \brief Axis signal. This item returns the limited target speed for an axis in a RAPID move. No extra argument.
	STATUSITEM_SpeedTargetActual = 266,
	/// \brief Axis signal. This item returns the distance remaining in a coordinated motion. The distance remaining is defined as the coordinated target position minus the program position. The program position reflects the position specified in the program and does not include the output of any transformations. This item is valid only during coordinated motion. Its value is zero for all other types of motion. Extra argument: Task Index.
	STATUSITEM_CoordinatedDistanceRemaining = 272,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_SafeZoneState = 323,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainKd1Scale = 333,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GainKp1Scale = 334,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MoveReferencePosition = 339,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MoveReferenceCutterOffset = 358,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MoveReferenceCornerOffset = 359,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MoveReferenceTotalOffset = 360,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GantryMarkerLatchPosition = 368,
	/// \brief Axis signal. This item returns the voltage command for a piezo axis. No extra argument.
	STATUSITEM_PiezoVoltageCommand = 376,
	/// \brief Axis signal. This item returns voltage feedback for a piezo axis. No extra argument.
	STATUSITEM_PiezoVoltageFeedback = 377,
	/// \brief Axis signal. This item returns the total distance traveled by this axis. No extra argument.
	STATUSITEM_DistanceLog = 378,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_AutoFocusError = 410,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_GalvoLaserOutputRawAdvance = 411,
	/// \brief Axis signal. This item returns the time that the Nmark will command the laser to go on relative to the rising edge of the Galvo Laser Output signal. No extra argument.
	STATUSITEM_GalvoLaserOnDelay = 412,
	/// \brief Axis signal. This item returns the time that the Nmark will command the laser to go off relative to the falling edge of the Galvo Laser Output signal. No extra argument.
	STATUSITEM_GalvoLaserOffDelay = 413,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CalibrationAdjustmentState = 416,
	/// \brief Axis signal. This item returns the minimum position that is corrected by accuracy calibration. No extra argument.
	STATUSITEM_AccuracyCorrectionStartingPosition = 417,
	/// \brief Axis signal. This item returns the maximum position that is corrected by accuracy calibration. No extra argument.
	STATUSITEM_AccuracyCorrectionEndingPosition = 418,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveCommandsDelayed = 424,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveCommandsLost = 425,
	/// \brief Axis signal. This item returns the value of the STO Status word. Extra argument: Mask.
	STATUSITEM_STOStatus = 443,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveAssert = 453,
	/// \brief System signal. This item returns the value of a 16-bit virtual binary input word that corresponds to the individual $BI bits. Extra argument: 16-bit Word Index.
	STATUSITEM_VirtualBinaryInput = 51,
	/// \brief System signal. This item returns the value of a 16-bit virtual binary output word that corresponds to the individual $BO bits. Extra argument: 16-bit Word Index.
	STATUSITEM_VirtualBinaryOutput = 52,
	/// \brief System signal. This item returns the value of a double-precision floating-point virtual register input word that corresponds to the "Register" argument of $RI. Extra argument: Register Index.
	STATUSITEM_VirtualRegisterInput = 53,
	/// \brief System signal. This item returns the value of a double-precision floating-point virtual register output word that corresponds to the "Register" argument of $RO. Extra argument: Register Index.
	STATUSITEM_VirtualRegisterOutput = 54,
	/// \brief System signal. This item returns the value of a system timer. Extra argument: Timer Index.
	STATUSITEM_Timer = 56,
	/// \brief System signal. This item returns the value of a system performance timer. Extra argument: Timer Index.
	STATUSITEM_TimerPerformance = 57,
	/// \brief System signal. This item returns the value of a global variable. Extra argument: Variable Index.
	STATUSITEM_GlobalVariable = 74,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_LibraryCommand = 148,
	/// \brief System signal. This item returns the data collection sample time. No extra argument.
	STATUSITEM_DataCollectionSampleTime = 149,
	/// \brief System signal. This item returns the data collection sample index. No extra argument.
	STATUSITEM_DataCollectionSampleIndex = 161,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the first axis. No extra argument.
	STATUSITEM_ZYGOPosition1 = 164,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the second axis. No extra argument.
	STATUSITEM_ZYGOPosition2 = 165,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the third axis. No extra argument.
	STATUSITEM_ZYGOPosition3 = 166,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the fourth axis. No extra argument.
	STATUSITEM_ZYGOPosition4 = 167,
	/// \brief System signal. This item returns a boolean value that indicates if the connection is established. Extra argument: Connection Number.
	STATUSITEM_PCModbusMasterConnected = 170,
	/// \brief System signal. This item returns a boolean value that indicates if the connection is established. No extra argument.
	STATUSITEM_PCModbusSlaveConnected = 171,
	/// \brief System signal. This item returns the value of the last system error code to occur on this connection. Extra argument: Connection Number.
	STATUSITEM_PCModbusMasterErrorCode = 174,
	/// \brief System signal. This item returns the value of the last system error code to occur on this connection. No extra argument.
	STATUSITEM_PCModbusSlaveErrorCode = 175,
	/// \brief System signal. This item returns the value of the last system error location code to occur on this connection. Extra argument: Connection Number.
	STATUSITEM_PCModbusMasterErrorLocation = 176,
	/// \brief System signal. This item returns the value of the last system location code to occur on this connection. No extra argument.
	STATUSITEM_PCModbusSlaveErrorLocation = 177,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_StopWatchTimer = 197,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ScopetrigID = 209,
	/// \brief System signal. This item returns the estimated SMC processor usage as a percentage. No extra argument.
	STATUSITEM_EstimatedProcessorUsage = 236,
	/// \brief System signal. This item returns the value of the Data Collection Flags word. No extra argument.
	STATUSITEM_DataCollectionStatus = 255,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_SignalLogState = 270,
	/// \brief System signal. This item returns true if a connection to the Fieldbus slave is established. Extra argument: Device ID.
	STATUSITEM_FieldbusConnected = 284,
	/// \brief System signal. This item returns the current error code of the Fieldbus device. Extra argument: Device ID.
	STATUSITEM_FieldbusErrorCode = 285,
	/// \brief System signal. This item returns the current error location of the Fieldbus device. Extra argument: Device ID.
	STATUSITEM_FieldbusErrorLocation = 286,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FieldbusActiveConnections = 287,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FieldbusInactiveConnections = 288,
	/// \brief System signal. This item returns the mask of violated safe zones. Once a zone is violated it will remain violated until any one of the axes in the safe zone is moved again. No extra argument.
	STATUSITEM_SafeZoneViolationMask = 289,
	/// \brief System signal. This item returns the mask of active safe zones. No extra argument.
	STATUSITEM_SafeZoneActiveMask = 321,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FieldbusInputs = 340,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FieldbusOutputs = 341,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusMasterInputWords = 342,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusMasterOutputWords = 343,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusMasterInputBits = 344,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusMasterOutputBits = 345,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusMasterOutputStatusBits = 346,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusMasterOutputStatusWords = 347,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusSlaveInputWords = 348,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusSlaveOutputWords = 349,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusSlaveInputBits = 350,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ModbusSlaveOutputBits = 351,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveModbusMasterInputWords = 352,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveModbusMasterOutputWords = 353,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveModbusMasterInputBits = 354,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveModbusMasterOutputBits = 355,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveModbusMasterOutputStatusBits = 356,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_DriveModbusMasterOutputStatusWords = 357,
	/// \brief System signal. This item returns the value of a system parameter. Extra argument: Parameter Index.
	STATUSITEM_SystemParameter = 379,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ThermoCompSensorTemperature = 420,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ThermoCompControllingTemperature = 421,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ThermoCompCompensatingTemperature = 422,
	/// \brief System signal. If non-zero, the ThermoComp status word is masked with this value. Extra argument: Table Index.
	STATUSITEM_ThermoCompStatus = 423,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_StepperVerificationMask = 426,
	/// \brief Task signal. This item returns the value of the program line number. No extra argument.
	STATUSITEM_ProgramLineNumber = 17,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedFlags = 45,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedArcStartAngle = 58,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedArcEndAngle = 59,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedArcRadius = 60,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedArcRadiusError = 61,
	/// \brief Task signal. This item returns the coordinated position command. No extra argument.
	STATUSITEM_CoordinatedPositionCommand = 62,
	/// \brief Task signal. This item returns the absolute value of the coordinated velocity command. No extra argument.
	STATUSITEM_CoordinatedSpeedCommand = 63,
	/// \brief Task signal. This item returns the absolute value of the coordinated acceleration command. No extra argument.
	STATUSITEM_CoordinatedAccelerationCommand = 64,
	/// \brief Task signal. This item returns the total distance of the coordinated move. No extra argument.
	STATUSITEM_CoordinatedTotalDistance = 65,
	/// \brief Task signal. This item returns the percentage of the coordinated move that has been completed. No extra argument.
	STATUSITEM_CoordinatedPercentDone = 66,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedPositionCommandBackwardsDiff = 67,
	/// \brief Task signal. This item returns the value of a program variable. Extra argument: Variable Index.
	STATUSITEM_ProgramVariable = 75,
	/// \brief Task signal. This item returns the value of an task parameter. Extra argument: Parameter Index.
	STATUSITEM_TaskParameter = 77,
	/// \brief Task signal. This item returns the task error code that is currently active. No extra argument.
	STATUSITEM_TaskErrorCode = 79,
	/// \brief Task signal. This item returns the task warning code that is currently active. No extra argument.
	STATUSITEM_TaskWarningCode = 80,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_WaitCommandDuration = 103,
	/// \brief Task signal. This item returns the actual target speed for dominant axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity. No extra argument.
	STATUSITEM_CoordinatedSpeedTargetActual = 104,
	/// \brief Task signal. This item returns the actual target speed for dependent axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity. No extra argument.
	STATUSITEM_DependentCoordinatedSpeedTargetActual = 105,
	/// \brief Task signal. This item returns the one-based index of the active fixture offset. If zero is returned, then no fixture offsets are active. No extra argument.
	STATUSITEM_ActiveFixtureOffset = 106,
	/// \brief Task signal. This item returns the value of the Task Status 0 word. Extra argument: Mask.
	STATUSITEM_TaskStatus0 = 108,
	/// \brief Task signal. This item returns the value of the Task Status 1 word. Extra argument: Mask.
	STATUSITEM_TaskStatus1 = 109,
	/// \brief Task signal. This item returns the value of the Task Status 2 word. Extra argument: Mask.
	STATUSITEM_TaskStatus2 = 110,
	/// \brief Task signal. This item returns the spindle 0 target speed. No extra argument.
	STATUSITEM_Spindle0SpeedTarget = 112,
	/// \brief Task signal. This item returns the spindle 1 target speed. No extra argument.
	STATUSITEM_Spindle1SpeedTarget = 113,
	/// \brief Task signal. This item returns the spindle 2 target speed. No extra argument.
	STATUSITEM_Spindle2SpeedTarget = 114,
	/// \brief Task signal. This item returns the spindle 3 target speed. No extra argument.
	STATUSITEM_Spindle3SpeedTarget = 115,
	/// \brief Task signal. This item returns the axis index assigned to the I-axis of coordinate system 1. No extra argument.
	STATUSITEM_CoordinateSystem1I = 118,
	/// \brief Task signal. This item returns the axis index assigned to the J-axis of coordinate system 1. No extra argument.
	STATUSITEM_CoordinateSystem1J = 119,
	/// \brief Task signal. This item returns the axis index assigned to the K-axis of coordinate system 1. No extra argument.
	STATUSITEM_CoordinateSystem1K = 120,
	/// \brief Task signal. This item returns the active plane index for coordinate system 1. Refer to the G17, G18, and G19 commands for more information on coordinate system planes. No extra argument.
	STATUSITEM_CoordinateSystem1Plane = 121,
	/// \brief Task signal. This item returns the active tool that was set by the T command. This item returns zero if no tool is active. No extra argument.
	STATUSITEM_ToolNumberActive = 122,
	/// \brief Task signal. This item returns the MFO value. No extra argument.
	STATUSITEM_MFO = 123,
	/// \brief Task signal. This item returns the target speed for dominant axes in a coordinated move. The target speed is set using the F command. No extra argument.
	STATUSITEM_CoordinatedSpeedTarget = 124,
	/// \brief Task signal. This item returns the target speed for dependent axes in a coordinated move. The dependent target speed is set using the E command. No extra argument.
	STATUSITEM_DependentCoordinatedSpeedTarget = 125,
	/// \brief Task signal. This item returns the value of the coordinated acceleration rate. Refer to the RAMP RATE command for more information on setting the coordinated acceleration rate. No extra argument.
	STATUSITEM_CoordinatedAccelerationRate = 132,
	/// \brief Task signal. This item returns the value of the coordinated deceleration rate. Refer to the RAMP RATE command for more information on setting the coordinated deceleration rate. No extra argument.
	STATUSITEM_CoordinatedDecelerationRate = 133,
	/// \brief Task signal. This item returns the value of the coordinated acceleration time. Refer to the RAMP TIME command for more information on setting the coordinated acceleration time. No extra argument.
	STATUSITEM_CoordinatedAccelerationTime = 134,
	/// \brief Task signal. This item returns the value of the coordinated deceleration time. Refer to the RAMP TIME command for more information on setting the coordinated deceleration time. No extra argument.
	STATUSITEM_CoordinatedDecelerationTime = 135,
	/// \brief Task signal. This item returns the value of the Task Mode word. Extra argument: Mask.
	STATUSITEM_TaskMode = 137,
	/// \brief Task signal. This item returns the current Task State. No extra argument.
	STATUSITEM_TaskState = 146,
	/// \brief Task signal. This item returns the current internal task state and is for internal use only. No extra argument.
	STATUSITEM_TaskStateInternal = 147,
	/// \brief Task signal. This item returns the task execution mode. No extra argument.
	STATUSITEM_ExecutionMode = 151,
	/// \brief Task signal. This item returns the task error location code that is currently active. No extra argument.
	STATUSITEM_TaskErrorLocation = 152,
	/// \brief Task signal. This item returns the task warning location code that is currently active. No extra argument.
	STATUSITEM_TaskWarningLocation = 153,
	/// \brief Task signal. This item indicates that a program is persistent to this task. All associated programs that are not immediate commands are considered persistent. No extra argument.
	STATUSITEM_ProgramPersistent = 154,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ImmediateState = 155,
	/// \brief Task signal. This is an internal status item. No extra argument.
	STATUSITEM_EnableAlignmentAxes = 159,
	/// \brief Task signal. This item returns the value of the Queue Status word. Extra argument: Mask.
	STATUSITEM_QueueStatus = 162,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedGalvoLaserOutput = 169,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedMotionRate = 184,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedTaskCommand = 185,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FiberMoveCount = 195,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_EnableState = 224,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CannedFunctionID = 240,
	/// \brief Task signal. This item returns the value of a double-precision task variable. Extra argument: Variable Index.
	STATUSITEM_TaskDoubleVariable = 248,
	/// \brief Task signal. This item returns the value of a task info variable. Extra argument: Variable Index.
	STATUSITEM_TaskInfoVariable = 249,
	/// \brief Task signal. This item returns the value of the task return variable. No extra argument.
	STATUSITEM_TaskReturnVariable = 271,
	/// \brief Task signal. This item returns the most recent power sample from a fiber search. No extra argument.
	STATUSITEM_FiberPower = 273,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_FiberPowerOptimal = 274,
	/// \brief Task signal. This item returns the number of power samples performed in a fiber search. No extra argument.
	STATUSITEM_FiberPowerSampleCount = 275,
	/// \brief Task signal. This item returns information on the result of a fiber search. No extra argument.
	STATUSITEM_FiberSearchResult = 276,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_LookaheadMovesExamined = 278,
	/// \brief Task signal. This item returns the value of the program line number internal to the SMC. No extra argument.
	STATUSITEM_ProgramLineNumberInternal = 322,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ProfileControlMask = 324,
	/// \brief Task signal. This item returns the number of items loaded in the program queue. No extra argument.
	STATUSITEM_QueueLineCount = 325,
	/// \brief Task signal. This item returns the total capacity of the program queue. No extra argument.
	STATUSITEM_QueueLineCapacity = 326,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ImmediateCommandErrorCode = 329,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ImmediateCommandErrorLocation = 330,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedArcRadiusReciprocal = 363,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionEngineStage = 367,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedTimeScale = 370,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_CoordinatedTimeScaleDerivative = 371,
	/// \brief Task signal. This item returns the instantaneous speed scaling of your marking and non-marking moves in IFOV. A value of 1.0 indicates full programmed speed. No extra argument.
	STATUSITEM_IFOVSpeedScale = 380,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVSpeedScaleAverage = 381,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVGenerationFrameCounter = 382,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVGenerationTimeOriginal = 383,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVGenerationTimeModified = 384,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVCoordinatedPositionCommand = 385,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVCoordinatedSpeedCommand = 386,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVCenterPointH = 390,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVCenterPointV = 391,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVTrajectoryCount = 392,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVTrajectoryIndex = 393,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVAttemptCode = 394,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVGenerationFrameIndex = 395,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVMaximumVelocity = 396,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVIdealVelocity = 397,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_TaskInternalDebug = 398,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVCoordinatedAccelerationCommand = 399,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVFOVPositionH = 400,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVFOVPositionV = 401,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVFOVDimensionH = 402,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_IFOVFOVDimensionV = 403,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferElements = 427,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferMoves = 428,
	/// \brief Task signal. This item returns the program line number of the current move. No extra argument.
	STATUSITEM_MotionLineNumber = 429,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferRetraceMoves = 430,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferRetraceElements = 431,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferIndex = 432,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferIndexLookahead = 433,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_MotionBufferProcessingBlocked = 434,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_ActiveMoveValid = 435,
	/// \brief Task signal. This item returns the number of program lines executed during the last millisecond. No extra argument.
	STATUSITEM_TaskExecutionLines = 436,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_SchedulerTaskHolds = 437,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_SchedulerProgramLoopRuns = 438,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_SchedulerTaskBlocked = 439,
	/// \brief Task signal. This item returns whether or not the task is currently in a critical section. No extra argument.
	STATUSITEM_CriticalSectionActive = 440,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	STATUSITEM_AxesSlowdownReason = 448,
	/// \brief Task signal. This item returns the processor time used by the given task in the current millisecond. No extra argument.
	STATUSITEM_TaskExecutionTime = 450,
	/// \brief Task signal. This item returns the maximum processor time used by the given task. No extra argument.
	STATUSITEM_TaskExecutionTimeMaximum = 451,
	/// \brief Task signal. This item returns the maximum number of program lines executed by the task in a millisecond. No extra argument.
	STATUSITEM_TaskExecutionLinesMaximum = 452,
} STATUSITEM;

#endif // __A3200_STATUS_ITEM_INFO_H__
