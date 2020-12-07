/// \file A3200ErrorCode.h
/// \brief Contains the error code enumeration.
/// 
/// These are the different errors that you can get by calling A3200GetLastError()
/// 
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#if !defined(__A3200_ERROR_CODE_H__)
#define __A3200_ERROR_CODE_H__

/// \brief The enumeration containing the error codes that can be returned from the A3200 functions.
typedef enum {
	/// \brief No error
	ErrorCode_NoError = 0,
	/// \brief An incompatible version was detected: [Location]
	ErrorCode_VersionMismatch = 1,
	/// \brief A license error occurred: [Location]
	ErrorCode_FeatureLocked = 2,
	/// \brief A connected hardware type is no longer supported: [Location]
	ErrorCode_UnsupportedHardware = 3,
	/// \brief A timeout occurred while waiting for the controller reset to finish.
	ErrorCode_ResetTimeout = 6,
	/// \brief An attempt to allocate memory on the SMC failed: [Location]
	ErrorCode_AllocationFailed = 8,
	/// \brief The specified controller handle is invalid: [Location]
	ErrorCode_NotConnected = 9,
	/// \brief The specified axis index is invalid.
	ErrorCode_InvalidAxisIndex = 10,
	/// \brief A problem occurred with a tool table: [Location]
	ErrorCode_ToolTableError = 11,
	/// \brief A timeout occurred while waiting for a drive response: [Location]
	ErrorCode_DriveCommandResponse = 13,
	/// \brief An error occurred with isochronous communication: [Location]
	ErrorCode_IsochronousCommunicationError = 14,
	/// \brief An error occurred during an asynchronous communication: [Location]
	ErrorCode_AsynchronousCommunicationError = 15,
	/// \brief An error occurred with PC Modbus communication: [Location]
	ErrorCode_PCModbusError = 16,
	/// \brief Drive communications were interrupted.
	ErrorCode_CommunicationLost = 17,
	/// \brief Ethernet communications were interrupted: [Location]
	ErrorCode_EthernetCommunicationLost = 18,
	/// \brief Communication Service communications were interrupted: [Location]
	ErrorCode_ServiceCommunicationLost = 19,
	/// \brief The FireWire or HyperWire card configuration is invalid: [Location]
	ErrorCode_CommunicationsCardConfiguration = 20,
	/// \brief A problem exists with PCI card configuration: [Location]
	ErrorCode_PCICardError = 21,
	/// \brief An incorrect number of axes are attached: [Location]
	ErrorCode_AxisMismatch = 22,
	/// \brief An insufficient number of tasks are enabled.
	ErrorCode_TaskMismatch = 23,
	/// \brief An invalid SMC command line argument was specified.
	ErrorCode_InvalidCommandLine = 24,
	/// \brief An error occurred while accessing the machine configuration: [Location]
	ErrorCode_MachineConfiguration = 25,
	/// \brief An error was detected in the FireWire or HyperWire configuration: [Location]
	ErrorCode_CommunicationsConfiguration = 28,
	/// \brief An error gantry configuration was detected: [Location]
	ErrorCode_GantryConfiguration = 29,
	/// \brief A timeout occurred while responding to a callback.
	ErrorCode_CallbackTimeout = 31,
	/// \brief An error occurred while executing a callback: [Location]
	ErrorCode_CallbackError = 32,
	/// \brief The maximum number of status items was exceeded.
	ErrorCode_TooManyStatusItems = 33,
	/// \brief An error occurred in program execution: [Location]
	ErrorCode_ProgramError = 34,
	/// \brief The maximum string length was exceeded.
	ErrorCode_StringOverflow = 35,
	/// \brief A divide-by-zero was detected.
	ErrorCode_DivideByZero = 36,
	/// \brief A program timeout occurred: [Location]
	ErrorCode_ProgramTimeout = 37,
	/// \brief An error occurred in the execution queue: [Location]
	ErrorCode_ProfileQueueError = 38,
	/// \brief An invalid argument was specified: [Location]
	ErrorCode_InvalidArgument = 39,
	/// \brief A callstack argument was not passed to a subroutine.
	ErrorCode_ParameterNotPassed = 40,
	/// \brief The buffered program queue is full.
	ErrorCode_QueueBufferFull = 41,
	/// \brief A NULL code line pointer was specified.
	ErrorCode_NullProgramLine = 42,
	/// \brief The specified program number is outside of the valid range of values.
	ErrorCode_ProgramNumberOutOfBounds = 43,
	/// \brief An error occurred with a canned function: [Location]
	ErrorCode_CannedFunctionError = 44,
	/// \brief The move speed is zero: [Location]
	ErrorCode_ZeroSpeed = 46,
	/// \brief A stack error occurred: [Location]
	ErrorCode_StackError = 47,
	/// \brief An error occurred while executing the SLICE command: [Location]
	ErrorCode_SliceError = 48,
	/// \brief An error occurred while doing retrace: [Location]
	ErrorCode_RetraceError = 50,
	/// \brief An axis fault occurred.
	ErrorCode_AxisInFault = 51,
	/// \brief The axis is not enabled.
	ErrorCode_AxisNotEnabled = 52,
	/// \brief An error occurred with a motion command: [Location]
	ErrorCode_MotionError = 53,
	/// \brief An error occurred while performing gantry motion: [Location]
	ErrorCode_GantryMotionError = 54,
	/// \brief An error occurred while peforming cutter compensation: [Location]
	ErrorCode_CutterCompensationError = 55,
	/// \brief An error occurred while performing circular motion: [Location]
	ErrorCode_CircularMotionError = 56,
	/// \brief A circular radius error occurred: [Location]
	ErrorCode_CircularRadiusError = 57,
	/// \brief An error occurred while performing normalcy: [Location]
	ErrorCode_NormalcyError = 58,
	/// \brief A LINEAR move is required to execute this command.
	ErrorCode_MotionTypeMismatch = 59,
	/// \brief The specified spindle is not assigned to an axis.
	ErrorCode_SpindleNumberNotAssigned = 60,
	/// \brief An error occurred while performing elliptical motion: [Location]
	ErrorCode_EllipticalMotionError = 61,
	/// \brief Motion is already active: [Location]
	ErrorCode_MotionActive = 62,
	/// \brief This feature is only available on dependent axes.
	ErrorCode_AxisNotDependent = 63,
	/// \brief This feature is only available on dominant axes.
	ErrorCode_AxisNotDominant = 64,
	/// \brief No joystick groups have been specified.
	ErrorCode_NoJoystickGroups = 65,
	/// \brief An error occurred performing a transformation: [Location]
	ErrorCode_TransformationError = 66,
	/// \brief An error occurred with a calibration table: [Location]
	ErrorCode_CalibrationTableError = 67,
	/// \brief An error occurred with a cam table command: [Location]
	ErrorCode_CamTableError = 68,
	/// \brief Cannot enable - the MX hardware is still programming.
	ErrorCode_MxhProgramming = 70,
	/// \brief Contouring five or more axes is restricted by your license key.
	ErrorCode_CNCFiveError = 71,
	/// \brief A task monitor error occurred: [Location]
	ErrorCode_MonitorError = 72,
	/// \brief An ONGOSUB error occurred: [Location]
	ErrorCode_OnGoSubError = 73,
	/// \brief Time-based ramping is not supported while velocity profiling occurs.
	ErrorCode_CannotUseTimeRamp = 74,
	/// \brief This task cannot execute because the ExecuteNumLines parameter is set to zero.
	ErrorCode_InvalidNumberOfLines = 75,
	/// \brief The axis being commanded is in a fault condition.
	ErrorCode_AxisFaultError = 77,
	/// \brief The synchronous motion command was aborted.
	ErrorCode_RunningSynchronousMotion = 78,
	/// \brief The specified opcode was not implemented at Communication Service level.
	ErrorCode_ServiceNotImplemented = 79,
	/// \brief The specified axis is out of range.
	ErrorCode_ServiceInvalidAxisIndex = 81,
	/// \brief A Communication Service transmission error occurred: [Location]
	ErrorCode_ServiceTransmissionError = 82,
	/// \brief A Communication Service callback error occurred: [Location]
	ErrorCode_ServiceCallbackError = 83,
	/// \brief An initialization error occurred in the Communication Service: [Location]
	ErrorCode_ServiceInitializationError = 84,
	/// \brief Communication Service initialization exit code: [ExitCode]
	ErrorCode_ServiceInitializationExitCode = 85,
	/// \brief A Communication Service error occurred: [Location]
	ErrorCode_CommunicationServiceError = 86,
	/// \brief An out of memory error occurred.
	ErrorCode_OutOfMemory = 88,
	/// \brief An event handler error occurred: [Location]
	ErrorCode_EventHandleError = 90,
	/// \brief An invalid library argument was passed: [Location]
	ErrorCode_InvalidLibraryArgument = 92,
	/// \brief The Firmware Loader cannot be run while drives are enabled.
	ErrorCode_SmcRunning = 93,
	/// \brief A Firmware Loader error occurred: [Location]
	ErrorCode_FirmwareLoadError = 94,
	/// \brief A callback error occurred: [Location]
	ErrorCode_LibraryCallbackError = 95,
	/// \brief An event error occurred: [Location]
	ErrorCode_LibraryEventError = 96,
	/// \brief A callback argument error occurred: [Location]
	ErrorCode_CallbackArgumentError = 97,
	/// \brief An error occurred while responding to a callback: [Location]
	ErrorCode_CallbackException = 98,
	/// \brief An unknown error occurred while executing an EXE command.
	ErrorCode_UnknownError = 100,
	/// \brief A callback cannot load or run a program on the task that issued the callback.
	ErrorCode_CannotAbortCallingTask = 102,
	/// \brief An error occurred while opening the Digital Scope: {0}
	ErrorCode_ScopeTimeout = 103,
	/// \brief An invalid callback return variable was specified: [Location]
	ErrorCode_ReturnValue = 104,
	/// \brief An error occurred while executing a FILE command: [Location]
	ErrorCode_FileError = 105,
	/// \brief An error occurred while executing a data collection command: [Location]
	ErrorCode_DataCollectError = 106,
	/// \brief An invalid callback argument was specified: [ArgumentIndex]
	ErrorCode_InvalidCallbackArgument = 107,
	/// \brief An error occurred in the Console: [Location]
	ErrorCode_ConsoleError = 108,
	/// \brief An invalid I/O argument was specified: [Location]
	ErrorCode_InvalidIOArgument = 109,
	/// \brief The maximum number of I/O points that can be retrieved at one time was exceeded.
	ErrorCode_TooManyIO = 110,
	/// \brief The specified parameter cannot be found.
	ErrorCode_ParameterNotFound = 111,
	/// \brief The specified parameter type is invalid.
	ErrorCode_ParameterTypeInvalid = 112,
	/// \brief The parameter file cannot be located.
	ErrorCode_ParameterFileNotFound = 113,
	/// \brief The format of the parameter file is invalid: [Location]
	ErrorCode_InvalidParameterFileFormat = 114,
	/// \brief The end of file was encountered.
	ErrorCode_EndOfFileFound = 115,
	/// \brief Access to the file is denied: [Location]
	ErrorCode_FileAccessDenied = 116,
	/// \brief An error occurred while processing a calibration file: [Location]
	ErrorCode_CalibrationFileError = 117,
	/// \brief An error occurred while processing a cam file: [Location]
	ErrorCode_CamFileError = 118,
	/// \brief An error occurred while accessing the registry: [Location]
	ErrorCode_RegistryError = 119,
	/// \brief The Aerotech product key is invalid.
	ErrorCode_InvalidProductID = 120,
	/// \brief This action is not valid with the type of I/O specified.
	ErrorCode_InvalidOperation = 122,
	/// \brief A VME error occurred: [Location]
	ErrorCode_VmeError = 123,
	/// \brief A Galvo configuration error occurred: [Location]
	ErrorCode_GalvoConfiguration = 124,
	/// \brief A Galvo calibration error occurred: [Location]
	ErrorCode_GalvoCalibration = 125,
	/// \brief A Windows error occurred: [Win32ErrorCode]
	ErrorCode_WindowsError = 127,
	/// \brief A Winsock error occurred: [WinsockErrorCode]
	ErrorCode_WinsockError = 128,
	/// \brief Compiler Error: [Location]
	ErrorCode_CompilerError = 129,
	/// \brief The radius of the cutting tool is too large for the shape of the part. Program line: [ProgramLine]
	ErrorCode_CutterRadiusTooLargeForShape = 130,
	/// \brief A discontinuity of cam data at the master rollover was encountered.
	ErrorCode_CamRolloverJerk = 133,
	/// \brief A discontinuity of axis calibration at the rollover point was encountered.
	ErrorCode_CalRolloverJerk = 134,
	/// \brief Too many subinterval moves were encountered. Program line: [ProgramLine]
	ErrorCode_TooManySubIntervalMoves = 135,
	/// \brief The joystick interlock input is open.
	ErrorCode_JoystickInterlockOpen = 136,
	/// \brief The program buffered mode queue is empty.
	ErrorCode_QueueEmpty = 138,
	/// \brief A FireWire or HyperWire card was not detected. Only virtual execution is available.
	ErrorCode_NoCommunicationsCard = 140,
	/// \brief No selfIDs are detected on the network. Check the FireWire or HyperWire cable connections.
	ErrorCode_NoSelfIDSeen = 141,
	/// \brief No active link layers are detected on the network. Check the power to all drives.
	ErrorCode_NoLinkLayer = 142,
	/// \brief The drive communications test failed.
	ErrorCode_DrvCommTestFailed = 145,
	/// \brief The SMC shutdown handler cannot be opened.
	ErrorCode_CannotOpenShutdownHandler = 146,
	/// \brief The specified opcode is not implemented at the SMC level.
	ErrorCode_InvalidOpcode = 147,
	/// \brief An internal task error occurred: [Location]
	ErrorCode_TaskInternalError = 148,
	/// \brief An invalid internal argument was specified: [Location]
	ErrorCode_InvalidInternalArgument = 149,
	/// \brief An internal SMC error occurred: [Location]
	ErrorCode_SmcInternalError = 150,
	/// \brief An initialization error occurred: [Location]
	ErrorCode_InitializationError = 151,
	/// \brief The AerStatusGetItems test failed.
	ErrorCode_GetStatusBad = 152,
	/// \brief A profile error occurred: [Location]
	ErrorCode_ProfileError = 154,
	/// \brief An exception occurred while starting the SMC.
	ErrorCode_RestartLogicException = 155,
	/// \brief The Communication Service is not finished processing a command.
	ErrorCode_DrvCommandNotComplete = 157,
	/// \brief The previous command is not complete.
	ErrorCode_CommandNotComplete = 158,
	/// \brief An error occurred while loading a resource: [Location]
	ErrorCode_ResourceError = 162,
	/// \brief One or more axes are required but no axes were specified.
	ErrorCode_NoAxesSpecified = 164,
	/// \brief The program buffered mode queue was not initialized correctly.
	ErrorCode_QueueNotInitialized = 165,
	/// \brief A master/slave configuration error occurred: [Location]
	ErrorCode_MasterSlaveConfiguration = 168,
	/// \brief An error occurred in data collection: [Location]
	ErrorCode_DataCollection = 169,
	/// \brief A data collection configuration error occurred: [Location]
	ErrorCode_DataCollectionConfiguration = 170,
	/// \brief The parameter value specified is out of range.
	ErrorCode_ParameterValueOutOfRange = 171,
	/// \brief All sub-millisecond moves must use the same time interval.
	ErrorCode_SubmillisecondTimeInterval = 172,
	/// \brief A trajectory filter configuration error occurred: [Location]
	ErrorCode_TrajectoryFilterConfiguration = 173,
	/// \brief The PT command does not support the selected interpolation mode.
	ErrorCode_PTInterpolationMode = 174,
	/// \brief The enable alignment move could not be completed.
	ErrorCode_EnableAlignmentMove = 175,
	/// \brief Motion was commanded outside of the software limits: [Location]
	ErrorCode_MoveTargetViolatesSoftwareLimit = 176,
	/// \brief A FireWire or HyperWire communication error occurred: [Location]
	ErrorCode_CommunicationsFailure = 177,
	/// \brief A library communication error has occurred: [Location]
	ErrorCode_LibraryCommunicationsError = 178,
	/// \brief A math error occurred: [ErrorDescription]
	ErrorCode_MathError = 179,
	/// \brief A user-defined error occurred: [Location]
	ErrorCode_UserDefinedError = 180,
	/// \brief A user-defined warning occurred: [Location]
	ErrorCode_UserDefinedWarning = 181,
	/// \brief An unexpected error occurred: [Location]
	ErrorCode_UnexpectedFailure = 182,
	/// \brief A parser error occurred: [Location]
	ErrorCode_AntlrError = 183,
	/// \brief An INtime node error occurred: [Location]
	ErrorCode_INtimeNode = 186,
	/// \brief The controller is shutting down.
	ErrorCode_ControllerShuttingDown = 187,
	/// \brief A reset cannot be performed while another reset is in progress.
	ErrorCode_ResetInProgress = 188,
	/// \brief The analog output is under control of another task.
	ErrorCode_AnalogOutputLocked = 189,
	/// \brief An error occurred with Signal Log: [Location]
	ErrorCode_SignalLogError = 192,
	/// \brief The password provided does not match the password stored on the controller.
	ErrorCode_InvalidPassword = 194,
	/// \brief Fieldbus Driver Error Code: [ErrorCode]
	ErrorCode_FieldbusDriverError = 195,
	/// \brief A Fieldbus error has occurred: [Location]
	ErrorCode_FieldbusError = 196,
	/// \brief An error occurred during a fiber search: [Location]
	ErrorCode_FiberError = 197,
	/// \brief An error has occurred when connecting to the Fieldbus process: [Location]
	ErrorCode_FieldbusProcessConnectError = 198,
	/// \brief An error has occurred when sending a command to the Fieldbus process: [Location]
	ErrorCode_FieldbusProcessCommandError = 199,
	/// \brief An error has occurred when processing the Fieldbus data on the SMC: [Location]
	ErrorCode_FieldbusSmcError = 200,
	/// \brief An error has occurred when accessing the Fieldbus variables: [Location]
	ErrorCode_FieldbusVariablesError = 201,
	/// \brief An error occurred while accessing the Fieldbus mapping: [Location]
	ErrorCode_FieldbusMap = 203,
	/// \brief An error occurred while resetting the SMC.
	ErrorCode_ResetFailed = 204,
	/// \brief Safe Zone Configuration Error: [Location]
	ErrorCode_SafeZoneConfigurationError = 206,
	/// \brief An internal error occurred while computing the Bezier curve: [Location]
	ErrorCode_BezierInternalError = 207,
	/// \brief A compiler error occurred while computing the Bezier curve: [Location]
	ErrorCode_BezierCompilationError = 208,
	/// \brief Lookahead was aborted because MaxLookaheadMoves was exceeded. Program line: [ProgramLine]
	ErrorCode_MaxLookaheadMovesExceeded = 210,
	/// \brief A DriveOutputCommandDelay error has occurred: [Location]
	ErrorCode_DriveOutputCommandDelayError = 212,
	/// \brief [Location]
	ErrorCode_IncompatibleParameterFileVersion = 213,
	/// \brief The immediate command cannot execute while the axis is profiling.
	ErrorCode_ImmediateCommandCannotExecuteWhileProfiling = 214,
	/// \brief An error occurred while doing a network socket operation: [Location]
	ErrorCode_NetworkSocketError = 215,
	/// \brief Build Result: [BuildResult]
	ErrorCode_BuildResult = 216,
	/// \brief The operation that you requested is restricted and was ignored.
	ErrorCode_ProgramControlRestricted = 217,
	/// \brief An error occurred with an auxiliary device: [Location]
	ErrorCode_AuxiliaryDeviceError = 218,
	/// \brief An error occurred encoding a barcode: [Location]
	ErrorCode_BarcodeError = 219,
	/// \brief The radius of the cutting tool is too large for the curve. Program line: [ProgramLine]
	ErrorCode_CutterRadiusTooLargeForCurve = 221,
	/// \brief After cutter radius compensation completed, the arcs do not intersect.
	ErrorCode_CutterOvercutNoArcIntersection = 222,
	/// \brief Setting this parameter from an AeroBasic program does not have an effect on the controller. Program line: [ProgramLine]
	ErrorCode_ParameterSettingHasNoEffect = 223,
	/// \brief You cannot change one or more configuration settings because analog vector-tracking mode is on.
	ErrorCode_CannotChangeAnalogAxes = 224,
	/// \brief The operation cannot be done because the controller is resetting or the reset did not complete.
	ErrorCode_ControllerNotReset = 225,
	/// \brief A distance logging error occurred: [Location]
	ErrorCode_DistanceLoggingError = 227,
	/// \brief You tried to download a command to the program queue while the task was not operating in queue mode.
	ErrorCode_ProgramQueueNotActive = 228,
	/// \brief An Infinite Field of View error occurred: [Location]
	ErrorCode_IFOVError = 229,
	/// \brief A piezo error occurred: [Location]
	ErrorCode_PiezoError = 230,
	/// \brief A licensing error has occurred: [Location]
	ErrorCode_LicensingError = 231,
	/// \brief An error occurred loading a program: [Location]
	ErrorCode_ProgramLoadingError = 232,
	/// \brief The MOVEDELAY command can only be used at trajectory rates of 1kHz or more.
	ErrorCode_MoveDelayMotionRate = 233,
	/// \brief The controller stopped responding because a starvation occurred.
	ErrorCode_ControllerStarvation = 234,
	/// \brief This operation cannot be performed because autofocus is disabled.
	ErrorCode_AutofocusNotEnabled = 235,
	/// \brief A compiler error occurred while compiling line: [Location]
	ErrorCode_QueueModeCompilerError = 236,
	/// \brief The specified drive or stage does not support FlashConfig.
	ErrorCode_FlashConfigNotSupported = 237,
	/// \brief The drive could not read the FlashConfig memory from the stage for the specified axis.
	ErrorCode_FlashConfigReadFailed = 238,
	/// \brief The drive could not write to the FlashConfig memory on the stage for the specified axis.
	ErrorCode_FlashConfigWriteFailed = 239,
	/// \brief The serial number of a connected stage is not the expected serial number.
	ErrorCode_RequiredStageSerialMismatch = 240,
	/// \brief An OSCILLATE argument is incorrect: [Location]
	ErrorCode_OscillateCommandArgumentIncorrect = 241,
	/// \brief An error occurred during HyperWire communication: [Location]
	ErrorCode_HyperWireCommunicationError = 242,
	/// \brief An error occurred using the ThermoComp feature: [Location]
	ErrorCode_ThermoCompError = 243,
	/// \brief An error occurred while executing a PSO command: [Location]
	ErrorCode_PsoError = 244,
	/// \brief A HyperWire card firmware loading error occurred: [Location]
	ErrorCode_CardLoadingError = 245,
	/// \brief The HyperWire configuration is invalid: [Location]
	ErrorCode_HyperWireConfigurationError = 246,
	/// \brief An authorization error occurred: [Location]
	ErrorCode_AuthorizationError = 247,
	/// \brief A timeout occurred attempting to execute a library command.
	ErrorCode_LibraryCommandTimeout = 248,
	/// \brief A PULSE command error occurred: [Location]
	ErrorCode_PulseCommandError = 249,
}	ErrorCode;

/// \brief The number of error codes.
#define ErrorCode_COUNT 250


#pragma pack(push, aerotech_a3200_packing, 2)

/// The ErrorData structure is used to return detailed error information.
typedef struct
{
	ErrorCode Code; ///< A descriptive error code
	int Location; ///< The location the error originates from
} ErrorData;

#pragma pack(pop, aerotech_a3200_packing)

/// A No Error Constant
static const ErrorData ErrorData_NoError = {ErrorCode_NoError, 0};

#endif // __A3200_ERROR_CODE_H__


