/// \file A3200DataCollectionInfo.h
/// \brief Contains the defines for datacollection item numbers.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
///

#ifndef __A3200_DATACOLLECTION_INFO_H__
#define __A3200_DATACOLLECTION_INFO_H__

typedef enum {
	/// \brief Axis Extended signal. This item returns the current feedback. No extra argument.
	DATASIGNAL_CurrentFeedback = 7,
	/// \brief Axis Extended signal. This item returns the current command. No extra argument.
	DATASIGNAL_CurrentCommand = 8,
	/// \brief Axis Extended signal. This item returns the value of analog input 0. The returned value corresponds to channel 0 of $AI. No extra argument.
	DATASIGNAL_AnalogInput0 = 10,
	/// \brief Axis Extended signal. This item returns the value of analog input 1. The returned value corresponds to channel 1 of $AI. No extra argument.
	DATASIGNAL_AnalogInput1 = 11,
	/// \brief Axis Extended signal. This item returns the phase A current feedback. No extra argument.
	DATASIGNAL_PhaseACurrentFeedback = 24,
	/// \brief Axis Extended signal. This item returns the phase B current feedback. No extra argument.
	DATASIGNAL_PhaseBCurrentFeedback = 25,
	/// \brief Axis Extended signal. This item returns the encoder sine in A/D counts. Extra argument: Channel.
	DATASIGNAL_EncoderSine = 26,
	/// \brief Axis Extended signal. This item returns the encoder cosine in A/D counts. Extra argument: Channel.
	DATASIGNAL_EncoderCosine = 27,
	/// \brief Axis Extended signal. This item returns the value of analog input 2. The returned value corresponds to channel 2 of $AI. No extra argument.
	DATASIGNAL_AnalogInput2 = 28,
	/// \brief Axis Extended signal. This item returns the value of analog input 3. The returned value corresponds to channel 3 of $AI. No extra argument.
	DATASIGNAL_AnalogInput3 = 29,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_LoopTransmissionBefore = 30,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_LoopTransmissionAfter = 31,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ZHSDifference = 32,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ZHSSum = 33,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ZHSUnfiltered = 34,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ZHSFiltered = 35,
	/// \brief Axis Extended signal. This item returns the value of analog output 0. The returned value corresponds to channel 0 of $AO. No extra argument.
	DATASIGNAL_AnalogOutput0 = 36,
	/// \brief Axis Extended signal. This item returns the value of analog output 1. The returned value corresponds to channel 1 of $AO. No extra argument.
	DATASIGNAL_AnalogOutput1 = 37,
	/// \brief Axis Extended signal. This item returns the value of analog output 2. The returned value corresponds to channel 2 of $AO. No extra argument.
	DATASIGNAL_AnalogOutput2 = 38,
	/// \brief Axis Extended signal. This item returns the value of analog output 3. The returned value corresponds to channel 3 of $AO. No extra argument.
	DATASIGNAL_AnalogOutput3 = 39,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryInt32 = 40,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryFloat = 41,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryDouble = 42,
	/// \brief Axis Extended signal. This item returns the value of the PSO Status word. Extra argument: Mask.
	DATASIGNAL_PSOStatus = 43,
	/// \brief Axis Extended signal. This item returns the value of the timer returned by the drive. Extra argument: Timer Number.
	DATASIGNAL_DriveTimer = 44,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionFeedbackDrive = 88,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionCommandDrive = 98,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryInt16 = 157,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryInt8 = 158,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryInt32Pointer = 202,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryInt16Pointer = 203,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryInt8Pointer = 204,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryFloatPointer = 205,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMemoryDoublePointer = 206,
	/// \brief Axis Extended signal. This item returns the value of PSO counter 1 in counts. No extra argument.
	DATASIGNAL_PSOCounter1 = 229,
	/// \brief Axis Extended signal. This item returns the value of PSO counter 2 in counts. No extra argument.
	DATASIGNAL_PSOCounter2 = 230,
	/// \brief Axis Extended signal. This item returns the value of PSO counter 3 in counts. No extra argument.
	DATASIGNAL_PSOCounter3 = 231,
	/// \brief Axis Extended signal. This item returns the value of the PSO window 1 counter in counts. No extra argument.
	DATASIGNAL_PSOWindow1 = 232,
	/// \brief Axis Extended signal. This item returns the value of the PSO window 2 counter in counts. No extra argument.
	DATASIGNAL_PSOWindow2 = 233,
	/// \brief Axis Extended signal. This item returns the number of data acquisition samples that have been acquired. No extra argument.
	DATASIGNAL_DataAcquisitionSamples = 234,
	/// \brief Axis Extended signal. This item returns the common mode voltage for the Nmark CLS position detector circuit. No extra argument.
	DATASIGNAL_PositionDetectorVoltage = 235,
	/// \brief Axis Extended signal. This item returns the position command of the galvo scanner. This value represents the location of scanner within its field-of-view, including calibration, but does not include marking-on-the-fly. No extra argument.
	DATASIGNAL_PositionCommandGalvo = 237,
	/// \brief Axis Extended signal. This item returns the value of the first resolver channel in counts. No extra argument.
	DATASIGNAL_ResolverChannel1 = 267,
	/// \brief Axis Extended signal. This item returns the value of the second resolver channel in counts. No extra argument.
	DATASIGNAL_ResolverChannel2 = 268,
	/// \brief Axis Extended signal. This item returns the value of the EnDat absolute position in counts. No extra argument.
	DATASIGNAL_EnDatAbsolutePosition = 269,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ControlEffort = 282,
	/// \brief Axis Extended signal. This item returns the value of the specified bit from the Modbus MasterInputBits registers. Extra argument: Bit Number.
	DATASIGNAL_ModbusBitMasterInputBits = 290,
	/// \brief Axis Extended signal. This item returns the value of the specified bit from the Modbus MasterOutputBits registers. Extra argument: Bit Number.
	DATASIGNAL_ModbusBitMasterOutputBits = 291,
	/// \brief Axis Extended signal. This item returns the 16-bit integer value stored in the specified Modbus MasterInputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegInt16MasterInputWords = 292,
	/// \brief Axis Extended signal. This item returns the 16-bit integer value stored in the specified Modbus MasterOutputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegInt16MasterOutputWords = 293,
	/// \brief Axis Extended signal. This item returns the 32-bit integer value stored in the specified Modbus MasterInputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegInt32MasterInputWords = 294,
	/// \brief Axis Extended signal. This item returns the 32-bit integer value stored in the specified Modbus MasterOutputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegInt32MasterOutputWords = 295,
	/// \brief Axis Extended signal. This item returns the 32-bit floating point value stored in the specified Modbus MasterInputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegSingleMasterInputWords = 296,
	/// \brief Axis Extended signal. This item returns the 32-bit floating point value stored in the specified Modbus MasterOutputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegSingleMasterOutputWords = 297,
	/// \brief Axis Extended signal. This item returns the 64-bit floating point value stored in the specified Modbus MasterInputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegDoubleMasterInputWords = 298,
	/// \brief Axis Extended signal. This item returns the 64-bit floating point value stored in the specified Modbus MasterOutputWords register. Extra argument: Register Number.
	DATASIGNAL_ModbusRegDoubleMasterOutputWords = 299,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PhaseAVoltageCommand = 300,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PhaseBVoltageCommand = 301,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PhaseCVoltageCommand = 302,
	/// \brief Axis Extended signal. This item returns the peak current rating of the amplifier. No extra argument.
	DATASIGNAL_AmplifierPeakCurrent = 303,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FPGAVersion = 304,
	/// \brief Axis Extended signal. This item returns an ID number identifying the type of drive (e.g., CP, HPe, Npaq etc). No extra argument.
	DATASIGNAL_DriveTypeID = 305,
	/// \brief Axis Extended signal. This item returns the current array index for window 1 when using the PSOWINDOW RANGE ARRAY command. No extra argument.
	DATASIGNAL_PSOWindow1ArrayIndex = 306,
	/// \brief Axis Extended signal. This item returns the current array index for window 2 when using the PSOWINDOW RANGE ARRAY command. No extra argument.
	DATASIGNAL_PSOWindow2ArrayIndex = 307,
	/// \brief Axis Extended signal. This item returns the current array index for the PSODISTANCE ARRAY command. No extra argument.
	DATASIGNAL_PSODistanceArrayIndex = 308,
	/// \brief Axis Extended signal. This item returns the amplifier heat sink temperature in degrees Celsius. No extra argument.
	DATASIGNAL_AmplifierTemperature = 309,
	/// \brief Axis Extended signal. This item returns the current array index for the PSOOUTPUT BIT MAP or PSOOUTPUT PULSE BIT MASK commands. No extra argument.
	DATASIGNAL_PSOBitArrayIndex = 310,
	/// \brief Axis Extended signal. This item returns the absolute encoder angle for the optional Encoder Multiplier. Extra argument: Channel.
	DATASIGNAL_MXAbsolutePosition = 311,
	/// \brief Axis Extended signal. This item returns the servo update rate in kilohertz. No extra argument.
	DATASIGNAL_ServoUpdateRate = 312,
	/// \brief Axis Extended signal. This item returns the settling time in milliseconds for the most recently completed move. No extra argument.
	DATASIGNAL_SettlingTime = 313,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_InternalErrorCode = 314,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FirmwareVersionMajor = 315,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FirmwareVersionMinor = 316,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FirmwareVersionPatch = 317,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FirmwareVersionBuild = 318,
	/// \brief Axis Extended signal. This item returns the maximum value of the timer returned by the drive. Extra argument: Timer Number.
	DATASIGNAL_DriveTimerMax = 319,
	/// \brief Axis Extended signal. This item returns the distance in counts that was traveled while searching for the marker. No extra argument.
	DATASIGNAL_MarkerSearchDistance = 320,
	/// \brief Axis Extended signal. This item returns the position feedback of the galvo scanner. This value represents the location of scanner within its field-of-view, including calibration, but does not include marking-on-the-fly. No extra argument.
	DATASIGNAL_PositionFeedbackGalvo = 327,
	/// \brief Axis Extended signal. This item returns the position at which the marker was detected during the home cycle. No extra argument.
	DATASIGNAL_LatchedMarkerPosition = 331,
	/// \brief Axis Extended signal. This item returns the temperature as reported by the 1-Wire temperature sensor in degrees Celsius (Npaq only). Extra argument: Number.
	DATASIGNAL_TemperatureSensor = 332,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_EthernetDebuggingInformation = 365,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_NpaqSyncoutStatus = 366,
	/// \brief Axis Extended signal. This item returns the value of the Resolute absolute position in counts. No extra argument.
	DATASIGNAL_ResoluteAbsolutePosition = 369,
	/// \brief Axis Extended signal. This item returns the position at which the most recent axis fault occurred. No extra argument.
	DATASIGNAL_FaultPositionFeedback = 372,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotorCommutationAngle = 373,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IOBoardInstalled = 374,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_BusVoltage = 375,
	/// \brief Axis Extended signal. This item returns the voltage command for a piezo axis. No extra argument.
	DATASIGNAL_PiezoVoltageCommand = 376,
	/// \brief Axis Extended signal. This item returns voltage feedback for a piezo axis. No extra argument.
	DATASIGNAL_PiezoVoltageFeedback = 377,
	/// \brief Axis Extended signal. This item returns the amount of time since the last reset. No extra argument.
	DATASIGNAL_TimeSinceReset = 387,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MaximumVoltage = 388,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CommandOutputType = 389,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveFeedforwardOutput = 404,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_LastTickCounter = 405,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_BoardRevision = 407,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FirmwareRevision = 408,
	/// \brief Axis Extended signal. This item returns the value of the galvo laser output. Extra argument: Mask.
	DATASIGNAL_GalvoLaserOutput = 409,
	/// \brief Axis Extended signal. This item returns the value of the analog output after laser power correction is applied. If laser power correction is not enabled, it will return zero. Refer to Galvo Power Correction Overview for more information. No extra argument.
	DATASIGNAL_GalvoLaserPowerCorrectionOutput = 414,
	/// \brief Axis Extended signal. This item returns the raw reading from the capacitance sensor feedback device. No extra argument.
	DATASIGNAL_CapacitanceSensorRawPosition = 415,
	/// \brief Axis Extended signal. This item returns the 2D galvo calibration contribution. No extra argument.
	DATASIGNAL_PositionCalibrationGalvo = 419,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_BusVoltageNegative = 441,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ProcessorTemperature = 442,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_InternalErrorTimestamp = 444,
	/// \brief Axis Extended signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_AmplifierInformation = 445,
	/// \brief Axis Extended signal. This item returns the value of the specified analog sensor input. Extra argument: Sensor Input Number.
	DATASIGNAL_AnalogSensorInput = 446,
	/// \brief Axis Extended signal. This item returns the motor temperature in degrees Celsius. No extra argument.
	DATASIGNAL_MotorTemperature = 447,
	/// \brief Axis Extended signal. This item returns the value of the Resolute Status word. Extra argument: Mask.
	DATASIGNAL_ResoluteStatus = 449,
	/// \brief Axis signal. This item returns the position feedback. No extra argument.
	DATASIGNAL_PositionFeedback = 0,
	/// \brief Axis signal. This item returns the position command. No extra argument.
	DATASIGNAL_PositionCommand = 1,
	/// \brief Axis signal. This item returns the position error. No extra argument.
	DATASIGNAL_PositionError = 2,
	/// \brief Axis signal. This item returns the velocity feedback. No extra argument.
	DATASIGNAL_VelocityFeedback = 3,
	/// \brief Axis signal. This item returns the commanded velocity of the axis. No extra argument.
	DATASIGNAL_VelocityCommand = 4,
	/// \brief Axis signal. This item returns the velocity error. No extra argument.
	DATASIGNAL_VelocityError = 5,
	/// \brief Axis signal. This item returns the value of the acceleration command. No extra argument.
	DATASIGNAL_AccelerationCommand = 6,
	/// \brief Axis signal. This item returns the current error. No extra argument.
	DATASIGNAL_CurrentError = 9,
	/// \brief Axis signal. This item returns the raw position command. No extra argument.
	DATASIGNAL_PositionCommandRaw = 12,
	/// \brief Axis signal. This item returns the raw velocity command. No extra argument.
	DATASIGNAL_VelocityCommandRaw = 13,
	/// \brief Axis signal. This item returns the position feedback from the auxiliary encoder. No extra argument.
	DATASIGNAL_PositionFeedbackAuxiliary = 14,
	/// \brief Axis signal. This item returns the value of the 32-bit digital input word that is read from the drive. The returned value corresponds to the individual $DI bits. Extra argument: Mask.
	DATASIGNAL_DigitalInput = 15,
	/// \brief Axis signal. This item returns the value of the 32-bit digital output word that is read from the drive. The returned value corresponds to the individual $DO bits. Extra argument: Mask.
	DATASIGNAL_DigitalOutput = 16,
	/// \brief Axis signal. This item returns the value of the specified fixture offset. Extra argument: Fixture Offset Index.
	DATASIGNAL_FixtureOffset = 18,
	/// \brief Axis signal. This item returns the coordinated target position command. No extra argument.
	DATASIGNAL_CoordinatedPositionTarget = 46,
	/// \brief Axis signal. This item returns the value of the Drive Status word. Extra argument: Mask.
	DATASIGNAL_DriveStatus = 47,
	/// \brief Axis signal. This item returns the value of the Axis Status word. Extra argument: Mask.
	DATASIGNAL_AxisStatus = 48,
	/// \brief Axis signal. This item returns the value of the Axis Fault word. Extra argument: Mask.
	DATASIGNAL_AxisFault = 49,
	/// \brief Axis signal. This item returns the value of the raw acceleration command. No extra argument.
	DATASIGNAL_AccelerationCommandRaw = 50,
	/// \brief Axis signal. This item returns the 1D + 2D position calibration contribution with the backlash contribution. No extra argument.
	DATASIGNAL_PositionCalibrationAll = 55,
	/// \brief Axis signal. This item returns the position feedback with rollover applied. No extra argument.
	DATASIGNAL_PositionFeedbackRollover = 69,
	/// \brief Axis signal. This item returns the position command with rollover applied. No extra argument.
	DATASIGNAL_PositionCommandRollover = 70,
	/// \brief Axis signal. This item returns the position feedback from the auxiliary encoder with rollover applied. No extra argument.
	DATASIGNAL_PositionFeedbackAuxiliaryRollover = 71,
	/// \brief Axis signal. This item returns the average velocity feedback. The average value is calculated over a period of 100 milliseconds. No extra argument.
	DATASIGNAL_VelocityFeedbackAverage = 72,
	/// \brief Axis signal. This item returns the average current feedback. The average value is calculated over a period of 100 milliseconds. No extra argument.
	DATASIGNAL_CurrentFeedbackAverage = 73,
	/// \brief Axis signal. This item returns the value of an axis parameter. Extra argument: Parameter Index.
	DATASIGNAL_AxisParameter = 76,
	/// \brief Axis signal. This item returns the peak current rating. No extra argument.
	DATASIGNAL_PeakCurrent = 78,
	/// \brief Axis signal. This item returns the backlash contribution. No extra argument.
	DATASIGNAL_Backlash = 81,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_HomeState = 82,
	/// \brief Axis signal. This item returns the 2D position calibration contribution. No extra argument.
	DATASIGNAL_PositionCalibration2D = 83,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_NormalcyDebug = 84,
	/// \brief Axis signal. This item returns the total move time of the last move. No extra argument.
	DATASIGNAL_TotalMoveTime = 85,
	/// \brief Axis signal. This item returns the stability 0 settle time. No extra argument.
	DATASIGNAL_Stability0SettleTime = 86,
	/// \brief Axis signal. This item returns the stability 1 settle time. No extra argument.
	DATASIGNAL_Stability1SettleTime = 87,
	/// \brief Axis signal. This item returns the raw jerk command. No extra argument.
	DATASIGNAL_JerkCommandRaw = 89,
	/// \brief Axis signal. This item returns the program position command. Commanded program position of the axis in user units. The program position command is the position commanded to the motor as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	DATASIGNAL_ProgramPositionCommand = 90,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GantryOffset = 91,
	/// \brief Axis signal. This item returns the value of the position offset. The position offset value is set using the POSOFFSET SET command and is cleared using the POSOFFSET CLEAR command. No extra argument.
	DATASIGNAL_PositionOffset = 92,
	/// \brief Axis signal. This item returns the number of times that the A3200 did not have sufficient time to complete all of its operations. Refer to Optimizing A3200 Performance for instructions about how to optimize the controller settings and prevent this problem. No extra argument.
	DATASIGNAL_CommunicationRealTimeErrors = 93,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionCommandRawBackwardsDiff = 96,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_VelocityCommandRawBackwardsDiffDelta = 97,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveStatusActual = 99,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GantryRealignState = 100,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_TransformAutoOffset = 101,
	/// \brief Axis signal. This item returns the program position feedback. Feedback program position of the axis in user units. The program position feedback is the position feedback of the motor as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	DATASIGNAL_ProgramPositionFeedback = 107,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_JogTrajectoryStatus = 116,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PingTest = 117,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainKposScale = 126,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainKiScale = 127,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainKpScale = 128,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainKpiScale = 129,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainAffScale = 130,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainVffScale = 131,
	/// \brief Axis signal. This item returns the value of the acceleration time. Refer to the RAMP TIME command for more information on setting the acceleration time. No extra argument.
	DATASIGNAL_AccelerationTime = 138,
	/// \brief Axis signal. This item returns the value of the Deceleration time. Refer to the RAMP TIME command for more information on setting the deceleration time. No extra argument.
	DATASIGNAL_DecelerationTime = 139,
	/// \brief Axis signal. This item returns the value of the acceleration rate. Refer to the RAMP RATE command for more information on setting the acceleration rate. No extra argument.
	DATASIGNAL_AccelerationRate = 140,
	/// \brief Axis signal. This item returns the value of the deceleration rate. Refer to the RAMP RATE command for more information on setting the deceleration rate. No extra argument.
	DATASIGNAL_DecelerationRate = 141,
	/// \brief Axis signal. This item returns the acceleration type. Refer to the RAMP TYPE command for more information on setting the acceleration type. No extra argument.
	DATASIGNAL_AccelerationType = 142,
	/// \brief Axis signal. This item returns the deceleration type. Refer to the RAMP TYPE command for more information on setting the deceleration type. No extra argument.
	DATASIGNAL_DecelerationType = 143,
	/// \brief Axis signal. This item returns the acceleration mode. Refer to the RAMP MODE command for more information on setting the acceleration mode. No extra argument.
	DATASIGNAL_AccelerationMode = 144,
	/// \brief Axis signal. This item returns the deceleration mode. Refer to the RAMP MODE command for more information on setting the deceleration mode. No extra argument.
	DATASIGNAL_DecelerationMode = 145,
	/// \brief Axis signal. This item returns the program position. Program position of the axis in user units. The program position reflects the position that you specify in the user program and does not include the output of any of the transformations. Extra argument: Task Index.
	DATASIGNAL_ProgramPosition = 156,
	/// \brief Axis signal. This item returns the target speed for an axis in a RAPID move. No extra argument.
	DATASIGNAL_SpeedTarget = 160,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionCommandPacket = 163,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveSMCMotionState = 168,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionCommandRawCal = 178,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_VelocityCommandRawCal = 179,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_VelocityCommandDrive = 180,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_AccelerationCommandDrive = 181,
	/// \brief Axis signal. This item returns the raw value of the galvo laser output. Extra argument: Mask.
	DATASIGNAL_GalvoLaserOutputRaw = 183,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketInt32 = 186,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketInt16 = 187,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketInt8 = 188,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketDouble = 189,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketFloat = 190,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfaceCommandCode = 191,
	/// \brief Axis signal. This item returns the value of the acceleration feedback. No extra argument.
	DATASIGNAL_AccelerationFeedback = 192,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_AccelerationCommandRawCal = 193,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionCalibrationAllDrive = 194,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_BacklashTarget = 196,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMotionRate = 198,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMotionDelay = 199,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CalibrationAdjustmentValue = 200,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ServoRounding = 201,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FeedforwardCurrent = 208,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketInfoBitValue = 210,
	/// \brief Axis signal. This item returns the value of the acceleration error. No extra argument.
	DATASIGNAL_AccelerationError = 223,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_SuppressedFaults = 225,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketStreamingData = 226,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_PositionCommandRawUnfiltered = 227,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_TransitionOffsetErrors = 228,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FreezeVelocityCommand = 238,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FreezeVelocityFeedback = 239,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_InternalPositionOffsets = 241,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_StatusHighLevelOffsetsLastMsec = 242,
	/// \brief Axis signal. This item returns the program velocity command. The program velocity command is the velocity command as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	DATASIGNAL_ProgramVelocityCommand = 250,
	/// \brief Axis signal. This item returns the program velocity feedback. The program velocity feedback is the velocity feedback as it is represented in the program coordinate system. This item does not include the output of any of the transformations. Extra argument: Task Index.
	DATASIGNAL_ProgramVelocityFeedback = 251,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveMotionDelayLive = 252,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveCommunicationDelay = 253,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveCommunicationDelayLive = 254,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketResponseInt32 = 256,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketResponseInt16 = 257,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketResponseInt8 = 258,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketResponseDouble = 259,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketResponseFloat = 260,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketBit = 261,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveInterfacePacketResponseBit = 262,
	/// \brief Axis signal. This item returns the limited target speed for an axis in a RAPID move. No extra argument.
	DATASIGNAL_SpeedTargetActual = 266,
	/// \brief Axis signal. This item returns the distance remaining in a coordinated motion. The distance remaining is defined as the coordinated target position minus the program position. The program position reflects the position specified in the program and does not include the output of any transformations. This item is valid only during coordinated motion. Its value is zero for all other types of motion. Extra argument: Task Index.
	DATASIGNAL_CoordinatedDistanceRemaining = 272,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_SafeZoneState = 323,
	/// \brief Axis signal. This item returns the position error of the galvo scanner. No extra argument.
	DATASIGNAL_PositionErrorGalvo = 328,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainKd1Scale = 333,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GainKp1Scale = 334,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MoveReferencePosition = 339,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MoveReferenceCutterOffset = 358,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MoveReferenceCornerOffset = 359,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MoveReferenceTotalOffset = 360,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GantryMarkerLatchPosition = 368,
	/// \brief Axis signal. This item returns the total distance traveled by this axis. No extra argument.
	DATASIGNAL_DistanceLog = 378,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_AutoFocusError = 410,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_GalvoLaserOutputRawAdvance = 411,
	/// \brief Axis signal. This item returns the time that the Nmark will command the laser to go on relative to the rising edge of the Galvo Laser Output signal. No extra argument.
	DATASIGNAL_GalvoLaserOnDelay = 412,
	/// \brief Axis signal. This item returns the time that the Nmark will command the laser to go off relative to the falling edge of the Galvo Laser Output signal. No extra argument.
	DATASIGNAL_GalvoLaserOffDelay = 413,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CalibrationAdjustmentState = 416,
	/// \brief Axis signal. This item returns the minimum position that is corrected by accuracy calibration. No extra argument.
	DATASIGNAL_AccuracyCorrectionStartingPosition = 417,
	/// \brief Axis signal. This item returns the maximum position that is corrected by accuracy calibration. No extra argument.
	DATASIGNAL_AccuracyCorrectionEndingPosition = 418,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveCommandsDelayed = 424,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveCommandsLost = 425,
	/// \brief Axis signal. This item returns the value of the STO Status word. Extra argument: Mask.
	DATASIGNAL_STOStatus = 443,
	/// \brief Axis signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveAssert = 453,
	/// \brief System signal. This item returns the value of a 16-bit virtual binary input word that corresponds to the individual $BI bits. Extra argument: 16-bit Word Index.
	DATASIGNAL_VirtualBinaryInput = 51,
	/// \brief System signal. This item returns the value of a 16-bit virtual binary output word that corresponds to the individual $BO bits. Extra argument: 16-bit Word Index.
	DATASIGNAL_VirtualBinaryOutput = 52,
	/// \brief System signal. This item returns the value of a double-precision floating-point virtual register input word that corresponds to the "Register" argument of $RI. Extra argument: Register Index.
	DATASIGNAL_VirtualRegisterInput = 53,
	/// \brief System signal. This item returns the value of a double-precision floating-point virtual register output word that corresponds to the "Register" argument of $RO. Extra argument: Register Index.
	DATASIGNAL_VirtualRegisterOutput = 54,
	/// \brief System signal. This item returns the value of a system timer. Extra argument: Timer Index.
	DATASIGNAL_Timer = 56,
	/// \brief System signal. This item returns the value of a system performance timer. Extra argument: Timer Index.
	DATASIGNAL_TimerPerformance = 57,
	/// \brief System signal. This item returns the value of a global variable. Extra argument: Variable Index.
	DATASIGNAL_GlobalVariable = 74,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_LibraryCommand = 148,
	/// \brief System signal. This item returns the data collection sample time. No extra argument.
	DATASIGNAL_DataCollectionSampleTime = 149,
	/// \brief System signal. This item returns the data collection sample index. No extra argument.
	DATASIGNAL_DataCollectionSampleIndex = 161,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the first axis. No extra argument.
	DATASIGNAL_ZYGOPosition1 = 164,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the second axis. No extra argument.
	DATASIGNAL_ZYGOPosition2 = 165,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the third axis. No extra argument.
	DATASIGNAL_ZYGOPosition3 = 166,
	/// \brief System signal. This item returns the value of the ZYGO laser position for the fourth axis. No extra argument.
	DATASIGNAL_ZYGOPosition4 = 167,
	/// \brief System signal. This item returns a boolean value that indicates if the connection is established. Extra argument: Connection Number.
	DATASIGNAL_PCModbusMasterConnected = 170,
	/// \brief System signal. This item returns a boolean value that indicates if the connection is established. No extra argument.
	DATASIGNAL_PCModbusSlaveConnected = 171,
	/// \brief System signal. This item returns the value of the last system error code to occur on this connection. Extra argument: Connection Number.
	DATASIGNAL_PCModbusMasterErrorCode = 174,
	/// \brief System signal. This item returns the value of the last system error code to occur on this connection. No extra argument.
	DATASIGNAL_PCModbusSlaveErrorCode = 175,
	/// \brief System signal. This item returns the value of the last system error location code to occur on this connection. Extra argument: Connection Number.
	DATASIGNAL_PCModbusMasterErrorLocation = 176,
	/// \brief System signal. This item returns the value of the last system location code to occur on this connection. No extra argument.
	DATASIGNAL_PCModbusSlaveErrorLocation = 177,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_StopWatchTimer = 197,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ScopetrigID = 209,
	/// \brief System signal. This item returns the estimated SMC processor usage as a percentage. No extra argument.
	DATASIGNAL_EstimatedProcessorUsage = 236,
	/// \brief System signal. This item returns the value of the Data Collection Flags word. No extra argument.
	DATASIGNAL_DataCollectionStatus = 255,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_SignalLogState = 270,
	/// \brief System signal. This item returns true if a connection to the Fieldbus slave is established. Extra argument: Device ID.
	DATASIGNAL_FieldbusConnected = 284,
	/// \brief System signal. This item returns the current error code of the Fieldbus device. Extra argument: Device ID.
	DATASIGNAL_FieldbusErrorCode = 285,
	/// \brief System signal. This item returns the current error location of the Fieldbus device. Extra argument: Device ID.
	DATASIGNAL_FieldbusErrorLocation = 286,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FieldbusActiveConnections = 287,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FieldbusInactiveConnections = 288,
	/// \brief System signal. This item returns the mask of violated safe zones. Once a zone is violated it will remain violated until any one of the axes in the safe zone is moved again. No extra argument.
	DATASIGNAL_SafeZoneViolationMask = 289,
	/// \brief System signal. This item returns the mask of active safe zones. No extra argument.
	DATASIGNAL_SafeZoneActiveMask = 321,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FieldbusInputs = 340,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FieldbusOutputs = 341,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusMasterInputWords = 342,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusMasterOutputWords = 343,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusMasterInputBits = 344,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusMasterOutputBits = 345,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusMasterOutputStatusBits = 346,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusMasterOutputStatusWords = 347,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusSlaveInputWords = 348,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusSlaveOutputWords = 349,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusSlaveInputBits = 350,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ModbusSlaveOutputBits = 351,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveModbusMasterInputWords = 352,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveModbusMasterOutputWords = 353,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveModbusMasterInputBits = 354,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveModbusMasterOutputBits = 355,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveModbusMasterOutputStatusBits = 356,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_DriveModbusMasterOutputStatusWords = 357,
	/// \brief System signal. This item returns the value of a system parameter. Extra argument: Parameter Index.
	DATASIGNAL_SystemParameter = 379,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ThermoCompSensorTemperature = 420,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ThermoCompControllingTemperature = 421,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ThermoCompCompensatingTemperature = 422,
	/// \brief System signal. If non-zero, the ThermoComp status word is masked with this value. Extra argument: Table Index.
	DATASIGNAL_ThermoCompStatus = 423,
	/// \brief System signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_StepperVerificationMask = 426,
	/// \brief Task signal. This item returns the value of the program line number. No extra argument.
	DATASIGNAL_ProgramLineNumber = 17,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedFlags = 45,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedArcStartAngle = 58,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedArcEndAngle = 59,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedArcRadius = 60,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedArcRadiusError = 61,
	/// \brief Task signal. This item returns the coordinated position command. No extra argument.
	DATASIGNAL_CoordinatedPositionCommand = 62,
	/// \brief Task signal. This item returns the absolute value of the coordinated velocity command. No extra argument.
	DATASIGNAL_CoordinatedSpeedCommand = 63,
	/// \brief Task signal. This item returns the absolute value of the coordinated acceleration command. No extra argument.
	DATASIGNAL_CoordinatedAccelerationCommand = 64,
	/// \brief Task signal. This item returns the total distance of the coordinated move. No extra argument.
	DATASIGNAL_CoordinatedTotalDistance = 65,
	/// \brief Task signal. This item returns the percentage of the coordinated move that has been completed. No extra argument.
	DATASIGNAL_CoordinatedPercentDone = 66,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedPositionCommandBackwardsDiff = 67,
	/// \brief Task signal. This item returns the value of a program variable. Extra argument: Variable Index.
	DATASIGNAL_ProgramVariable = 75,
	/// \brief Task signal. This item returns the value of an task parameter. Extra argument: Parameter Index.
	DATASIGNAL_TaskParameter = 77,
	/// \brief Task signal. This item returns the task error code that is currently active. No extra argument.
	DATASIGNAL_TaskErrorCode = 79,
	/// \brief Task signal. This item returns the task warning code that is currently active. No extra argument.
	DATASIGNAL_TaskWarningCode = 80,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_WaitCommandDuration = 103,
	/// \brief Task signal. This item returns the actual target speed for dominant axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity. No extra argument.
	DATASIGNAL_CoordinatedSpeedTargetActual = 104,
	/// \brief Task signal. This item returns the actual target speed for dependent axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity. No extra argument.
	DATASIGNAL_DependentCoordinatedSpeedTargetActual = 105,
	/// \brief Task signal. This item returns the one-based index of the active fixture offset. If zero is returned, then no fixture offsets are active. No extra argument.
	DATASIGNAL_ActiveFixtureOffset = 106,
	/// \brief Task signal. This item returns the value of the Task Status 0 word. Extra argument: Mask.
	DATASIGNAL_TaskStatus0 = 108,
	/// \brief Task signal. This item returns the value of the Task Status 1 word. Extra argument: Mask.
	DATASIGNAL_TaskStatus1 = 109,
	/// \brief Task signal. This item returns the value of the Task Status 2 word. Extra argument: Mask.
	DATASIGNAL_TaskStatus2 = 110,
	/// \brief Task signal. This item returns the spindle 0 target speed. No extra argument.
	DATASIGNAL_Spindle0SpeedTarget = 112,
	/// \brief Task signal. This item returns the spindle 1 target speed. No extra argument.
	DATASIGNAL_Spindle1SpeedTarget = 113,
	/// \brief Task signal. This item returns the spindle 2 target speed. No extra argument.
	DATASIGNAL_Spindle2SpeedTarget = 114,
	/// \brief Task signal. This item returns the spindle 3 target speed. No extra argument.
	DATASIGNAL_Spindle3SpeedTarget = 115,
	/// \brief Task signal. This item returns the axis index assigned to the I-axis of coordinate system 1. No extra argument.
	DATASIGNAL_CoordinateSystem1I = 118,
	/// \brief Task signal. This item returns the axis index assigned to the J-axis of coordinate system 1. No extra argument.
	DATASIGNAL_CoordinateSystem1J = 119,
	/// \brief Task signal. This item returns the axis index assigned to the K-axis of coordinate system 1. No extra argument.
	DATASIGNAL_CoordinateSystem1K = 120,
	/// \brief Task signal. This item returns the active plane index for coordinate system 1. Refer to the G17, G18, and G19 commands for more information on coordinate system planes. No extra argument.
	DATASIGNAL_CoordinateSystem1Plane = 121,
	/// \brief Task signal. This item returns the active tool that was set by the T command. This item returns zero if no tool is active. No extra argument.
	DATASIGNAL_ToolNumberActive = 122,
	/// \brief Task signal. This item returns the MFO value. No extra argument.
	DATASIGNAL_MFO = 123,
	/// \brief Task signal. This item returns the target speed for dominant axes in a coordinated move. The target speed is set using the F command. No extra argument.
	DATASIGNAL_CoordinatedSpeedTarget = 124,
	/// \brief Task signal. This item returns the target speed for dependent axes in a coordinated move. The dependent target speed is set using the E command. No extra argument.
	DATASIGNAL_DependentCoordinatedSpeedTarget = 125,
	/// \brief Task signal. This item returns the value of the coordinated acceleration rate. Refer to the RAMP RATE command for more information on setting the coordinated acceleration rate. No extra argument.
	DATASIGNAL_CoordinatedAccelerationRate = 132,
	/// \brief Task signal. This item returns the value of the coordinated deceleration rate. Refer to the RAMP RATE command for more information on setting the coordinated deceleration rate. No extra argument.
	DATASIGNAL_CoordinatedDecelerationRate = 133,
	/// \brief Task signal. This item returns the value of the coordinated acceleration time. Refer to the RAMP TIME command for more information on setting the coordinated acceleration time. No extra argument.
	DATASIGNAL_CoordinatedAccelerationTime = 134,
	/// \brief Task signal. This item returns the value of the coordinated deceleration time. Refer to the RAMP TIME command for more information on setting the coordinated deceleration time. No extra argument.
	DATASIGNAL_CoordinatedDecelerationTime = 135,
	/// \brief Task signal. This item returns the value of the Task Mode word. Extra argument: Mask.
	DATASIGNAL_TaskMode = 137,
	/// \brief Task signal. This item returns the current Task State. No extra argument.
	DATASIGNAL_TaskState = 146,
	/// \brief Task signal. This item returns the current internal task state and is for internal use only. No extra argument.
	DATASIGNAL_TaskStateInternal = 147,
	/// \brief Task signal. This item returns the task execution mode. No extra argument.
	DATASIGNAL_ExecutionMode = 151,
	/// \brief Task signal. This item returns the task error location code that is currently active. No extra argument.
	DATASIGNAL_TaskErrorLocation = 152,
	/// \brief Task signal. This item returns the task warning location code that is currently active. No extra argument.
	DATASIGNAL_TaskWarningLocation = 153,
	/// \brief Task signal. This item indicates that a program is persistent to this task. All associated programs that are not immediate commands are considered persistent. No extra argument.
	DATASIGNAL_ProgramPersistent = 154,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ImmediateState = 155,
	/// \brief Task signal. This is an internal status item. No extra argument.
	DATASIGNAL_EnableAlignmentAxes = 159,
	/// \brief Task signal. This item returns the value of the Queue Status word. Extra argument: Mask.
	DATASIGNAL_QueueStatus = 162,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedGalvoLaserOutput = 169,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedMotionRate = 184,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedTaskCommand = 185,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FiberMoveCount = 195,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_EnableState = 224,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CannedFunctionID = 240,
	/// \brief Task signal. This item returns the value of a double-precision task variable. Extra argument: Variable Index.
	DATASIGNAL_TaskDoubleVariable = 248,
	/// \brief Task signal. This item returns the value of a task info variable. Extra argument: Variable Index.
	DATASIGNAL_TaskInfoVariable = 249,
	/// \brief Task signal. This item returns the value of the task return variable. No extra argument.
	DATASIGNAL_TaskReturnVariable = 271,
	/// \brief Task signal. This item returns the most recent power sample from a fiber search. No extra argument.
	DATASIGNAL_FiberPower = 273,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_FiberPowerOptimal = 274,
	/// \brief Task signal. This item returns the number of power samples performed in a fiber search. No extra argument.
	DATASIGNAL_FiberPowerSampleCount = 275,
	/// \brief Task signal. This item returns information on the result of a fiber search. No extra argument.
	DATASIGNAL_FiberSearchResult = 276,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_LookaheadMovesExamined = 278,
	/// \brief Task signal. This item returns the value of the program line number internal to the SMC. No extra argument.
	DATASIGNAL_ProgramLineNumberInternal = 322,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ProfileControlMask = 324,
	/// \brief Task signal. This item returns the number of items loaded in the program queue. No extra argument.
	DATASIGNAL_QueueLineCount = 325,
	/// \brief Task signal. This item returns the total capacity of the program queue. No extra argument.
	DATASIGNAL_QueueLineCapacity = 326,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ImmediateCommandErrorCode = 329,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ImmediateCommandErrorLocation = 330,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedArcRadiusReciprocal = 363,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionEngineStage = 367,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedTimeScale = 370,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_CoordinatedTimeScaleDerivative = 371,
	/// \brief Task signal. This item returns the instantaneous speed scaling of your marking and non-marking moves in IFOV. A value of 1.0 indicates full programmed speed. No extra argument.
	DATASIGNAL_IFOVSpeedScale = 380,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVSpeedScaleAverage = 381,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVGenerationFrameCounter = 382,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVGenerationTimeOriginal = 383,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVGenerationTimeModified = 384,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVCoordinatedPositionCommand = 385,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVCoordinatedSpeedCommand = 386,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVCenterPointH = 390,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVCenterPointV = 391,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVTrajectoryCount = 392,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVTrajectoryIndex = 393,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVAttemptCode = 394,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVGenerationFrameIndex = 395,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVMaximumVelocity = 396,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVIdealVelocity = 397,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_TaskInternalDebug = 398,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVCoordinatedAccelerationCommand = 399,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVFOVPositionH = 400,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVFOVPositionV = 401,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVFOVDimensionH = 402,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_IFOVFOVDimensionV = 403,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferElements = 427,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferMoves = 428,
	/// \brief Task signal. This item returns the program line number of the current move. No extra argument.
	DATASIGNAL_MotionLineNumber = 429,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferRetraceMoves = 430,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferRetraceElements = 431,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferIndex = 432,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferIndexLookahead = 433,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_MotionBufferProcessingBlocked = 434,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_ActiveMoveValid = 435,
	/// \brief Task signal. This item returns the number of program lines executed during the last millisecond. No extra argument.
	DATASIGNAL_TaskExecutionLines = 436,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_SchedulerTaskHolds = 437,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_SchedulerProgramLoopRuns = 438,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_SchedulerTaskBlocked = 439,
	/// \brief Task signal. This item returns whether or not the task is currently in a critical section. No extra argument.
	DATASIGNAL_CriticalSectionActive = 440,
	/// \brief Task signal. This is an internal signal, use only if directed by Aerotech.
	DATASIGNAL_AxesSlowdownReason = 448,
	/// \brief Task signal. This item returns the processor time used by the given task in the current millisecond. No extra argument.
	DATASIGNAL_TaskExecutionTime = 450,
	/// \brief Task signal. This item returns the maximum processor time used by the given task. No extra argument.
	DATASIGNAL_TaskExecutionTimeMaximum = 451,
	/// \brief Task signal. This item returns the maximum number of program lines executed by the task in a millisecond. No extra argument.
	DATASIGNAL_TaskExecutionLinesMaximum = 452,
} DATASIGNAL;

#endif // __A3200_DATACOLLECTION_INFO_H__
