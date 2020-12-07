/// \file A3200AeroBasicCommands.h
/// \brief Contains immediate commands
/// 
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_AEROBASIC_COMMANDS_H__
#define __A3200_AEROBASIC_COMMANDS_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"
#include "A3200StatusItemInfo.h"
#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup root Generic Commands

/// \defgroup motion Motion Commands
/// The C library expects array arguments to be packed when passed in conjunction with axis masks.  For example,
/// if the axis mask indicates the command will be executed on the first and third axis, the first index of the array should
/// refer to the argument value for the first axis, and the second index of the array should refer to the argument value for the third axis.

/// \defgroup motsetup Motion Setup Commands
/// The C library expects array arguments to be packed when passed in conjunction with axis masks.  For example,
/// if the axis mask indicates the command will be executed on the first and third axis, the first index of the array should
/// refer to the argument value for the first axis, and the second index of the array should refer to the argument value for the third axis.

/// \brief Specifies the ramp type to use.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TYPE_Command.html">RAMP TYPE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Type The ramp type to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTypeAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTypeAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, RAMPTYPE Type);

/// \brief Specifies the ramp mode calculation type to use.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP MODE_Command.html">RAMP MODE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Mode The ramp mode to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampModeAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampModeAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, RAMPMODE Mode);

/// \brief Specifies rate-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE_Command.html">RAMP RATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Specifies rate-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE_Command.html">RAMP RATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateAccelAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateAccelAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Specifies rate-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE_Command.html">RAMP RATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateDecelAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateDecelAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Specifies time-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TIME_Command.html">RAMP TIME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The acceleration and deceleration time.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTimeAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTimeAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Specifies time-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TIME_Command.html">RAMP TIME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The acceleration and deceleration time.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTimeAccelAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTimeAccelAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Specifies time-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TIME_Command.html">RAMP TIME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The acceleration and deceleration time.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTimeDecelAxis()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTimeDecelAxis(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Sets or clears an arbitrary program offset position.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/POSOFFSET_Command.html">POSOFFSET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Value The value at which to set the parameter.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupPosOffsetSet()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupPosOffsetSet(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Value);

/// \brief Sets or clears an arbitrary program offset position.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/POSOFFSET_Command.html">POSOFFSET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupPosOffsetClear()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupPosOffsetClear(A3200Handle handle, TASKID taskId, AXISMASK axisMask);


/// \defgroup advancedmot Motion Advanced Commands

/// \brief Asynchronously homes axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/HOMEASYNC_Command.html">HOMEASYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup advancedmot
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAdvancedHomeAsync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAdvancedHomeAsync(A3200Handle handle, TASKID taskId, AXISMASK axisMask);

/// \brief Asynchronously homes axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/HOMEASYNC_Command.html">HOMEASYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup advancedmot
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAdvancedHomeAsyncConditional()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAdvancedHomeAsyncConditional(A3200Handle handle, TASKID taskId, AXISMASK axisMask);


/// \brief Disables the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/DISABLE_Command.html">DISABLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionDisable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionDisable(A3200Handle handle, TASKID taskId, AXISMASK axisMask);

/// \brief Enables the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ENABLE_Command.html">ENABLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionEnable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionEnable(A3200Handle handle, TASKID taskId, AXISMASK axisMask);

/// \brief Acknowledges and clears the fault on axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FAULTACK_Command.html">FAULTACK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFaultAck()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFaultAck(A3200Handle handle, TASKID taskId, AXISMASK axisMask);

/// \brief Homes the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/HOME_Command.html">HOME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionHome()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionHome(A3200Handle handle, TASKID taskId, AXISMASK axisMask);

/// \brief Homes the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/HOME_Command.html">HOME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionHomeConditional()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionHomeConditional(A3200Handle handle, TASKID taskId, AXISMASK axisMask);

/// \brief Executes a linear move on axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/LINEAR_Command.html">LINEAR</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Distance The distance to move the axis.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionLinear()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionLinear(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Distance);

/// \brief Executes a linear move on axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/LINEAR_Command.html">LINEAR</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Distance The distance to move the axis.
/// \param[in] CoordinatedSpeed The vectorial speed at which to move the axes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionLinearVelocity()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionLinearVelocity(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Distance, DOUBLE CoordinatedSpeed);

/// \brief Executes single or multi-axis point-to-point motion.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAPID_Command.html">RAPID</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] Distance The distance to move the axis.
/// \param[in] Speed The speed at which to move an axis.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionRapid()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionRapid(A3200Handle handle, TASKID taskId, AXISMASK axisMask, DOUBLE* Distance, DOUBLE* Speed);


/// \defgroup io IO Commands

/// \brief Controls the output of the brake on the specified axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/BRAKE_Command.html">BRAKE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] axisMask The mask of axes to execute the command on
/// \param[in] OnOff Sets the brake to On or Off.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IOBrake()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IOBrake(A3200Handle handle, TASKID taskId, AXISMASK axisMask, ONOFF OnOff);



/// \defgroup root Generic Commands

/// \defgroup motion Motion Commands
/// The C library expects array arguments to be packed when passed in conjunction with axis masks.  For example,
/// if the axis mask indicates the command will be executed on the first and third axis, the first index of the array should
/// refer to the argument value for the first axis, and the second index of the array should refer to the argument value for the third axis.

/// \defgroup motsetup Motion Setup Commands
/// The C library expects array arguments to be packed when passed in conjunction with axis masks.  For example,
/// if the axis mask indicates the command will be executed on the first and third axis, the first index of the array should
/// refer to the argument value for the first axis, and the second index of the array should refer to the argument value for the third axis.

/// \brief Specifies the S-curve value to use.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SCURVE_Command.html">SCURVE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The value by which to S-curve.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupScurve()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupScurve(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Sets motion commands to be in absolute mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ABSOLUTE_Command.html">ABSOLUTE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupAbsolute()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupAbsolute(A3200Handle handle, TASKID taskId);

/// \brief Sets motion commands to be in incremental mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/INCREMENTAL_Command.html">INCREMENTAL</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupIncremental()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupIncremental(A3200Handle handle, TASKID taskId);

/// \brief Specifies the ramp type to use.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TYPE_Command.html">RAMP TYPE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Type The ramp type to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTypeCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTypeCoordinated(A3200Handle handle, TASKID taskId, RAMPTYPE Type);

/// \brief Specifies the ramp mode calculation type to use.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP MODE_Command.html">RAMP MODE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Mode The ramp mode to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampModeCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampModeCoordinated(A3200Handle handle, TASKID taskId, RAMPMODE Mode);

/// \brief Specifies rate-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE_Command.html">RAMP RATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateCoordinated(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies rate-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE_Command.html">RAMP RATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateAccelCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateAccelCoordinated(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies rate-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE_Command.html">RAMP RATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateDecelCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateDecelCoordinated(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies rate-based acceleration and deceleration on dependent axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE DEPENDENT_Command.html">RAMP RATE DEPENDENT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateDependentAccel()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateDependentAccel(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies rate-based acceleration and deceleration on dependent axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP RATE DEPENDENT_Command.html">RAMP RATE DEPENDENT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration rate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampRateDependentDecel()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampRateDependentDecel(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies time-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TIME_Command.html">RAMP TIME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration time.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTimeCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTimeCoordinated(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies time-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TIME_Command.html">RAMP TIME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration time.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTimeAccelCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTimeAccelCoordinated(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Specifies time-based acceleration and deceleration.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/RAMP TIME_Command.html">RAMP TIME</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Value The acceleration and deceleration time.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupRampTimeDecelCoordinated()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupRampTimeDecelCoordinated(A3200Handle handle, TASKID taskId, DOUBLE Value);

/// \brief Sets an arbitrary position value, in encoder counts, in external position register.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SETEXTPOS_Command.html">SETEXTPOS</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Value The value to set in external position register.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupSetExtPos()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupSetExtPos(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Value);

/// \brief Changes between open-loop and closed-loop mode for piezo stages.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SERVO ON_OFF_Command.html">SERVO ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motsetup
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OnOff Turns on or turns off closed-loop servo mode.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSetupServo()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSetupServo(A3200Handle handle, TASKID taskId, AXISINDEX Axis, ONOFF OnOff);


/// \defgroup advancedmot Motion Advanced Commands

/// \brief Moves an axis out of a limit condition.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MOVEOUTLIM_Command.html">MOVEOUTLIM</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup advancedmot
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAdvancedMoveOutLim()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAdvancedMoveOutLim(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Moves an axis into a limit condition.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MOVETOLIM_Command.html">MOVETOLIM</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup advancedmot
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAdvancedMoveToLimCW()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAdvancedMoveToLimCW(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Moves an axis into a limit condition.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MOVETOLIM_Command.html">MOVETOLIM</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup advancedmot
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAdvancedMoveToLimCCW()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAdvancedMoveToLimCCW(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Blends two moves (a scanning move and a stepping move) to make one coordinated move.

///
/// \ingroup advancedmot
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] FirstAxis First axis
/// \param[in] SecondAxis Second axis
/// \param[in] FirstAxisJumpPos First axis jump point position
/// \param[in] SecondAxisJumpPos Second axis jump point position
/// \param[in] FirstAxisEndPos First axis end point position
/// \param[in] SecondAxisEndPos Second axis end point position
/// \param[in] CoordinatedSpeed Coordinated speed of the scanning motion
/// \param[in] FirstAxisJumpSpeed First axis speed for the stepping motion
/// \param[in] SecondAxisJumpSpeed Second axis speed for the stepping motion
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAdvancedSlice()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAdvancedSlice(A3200Handle handle, TASKID taskId, AXISINDEX FirstAxis, AXISINDEX SecondAxis, DOUBLE FirstAxisJumpPos, DOUBLE SecondAxisJumpPos, DOUBLE FirstAxisEndPos, DOUBLE SecondAxisEndPos, DOUBLE CoordinatedSpeed, DOUBLE FirstAxisJumpSpeed, DOUBLE SecondAxisJumpSpeed);


/// \defgroup fiber Motion Fiber Commands

/// \brief Executes a Centroid 1D (one-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER CENTROID_Command.html">FIBER CENTROID</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberCentroid1D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberCentroid1D(A3200Handle handle, TASKID taskId);

/// \brief Executes a Centroid 1D (one-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER CENTROID_Command.html">FIBER CENTROID</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ControllerVariable The controller variable in which to store the calculated centroid coordinate.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberCentroid1DControllerVariable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberCentroid1DControllerVariable(A3200Handle handle, TASKID taskId, DOUBLE ControllerVariable);

/// \brief Executes a Centroid 2D (two-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER CENTROID2D_Command.html">FIBER CENTROID2D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberCentroid2D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberCentroid2D(A3200Handle handle, TASKID taskId);

/// \brief Executes a Centroid 2D (two-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER CENTROID2D_Command.html">FIBER CENTROID2D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ControllerVariable The first controller variable in which to store the calculated centroid coordinates.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberCentroid2DControllerVariable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberCentroid2DControllerVariable(A3200Handle handle, TASKID taskId, DOUBLE ControllerVariable);

/// \brief Executes a Centroid 3D (three-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER CENTROID3D_Command.html">FIBER CENTROID3D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberCentroid3D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberCentroid3D(A3200Handle handle, TASKID taskId);

/// \brief Executes a Centroid 3D (three-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER CENTROID3D_Command.html">FIBER CENTROID3D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ControllerVariable The first controller variable in which to store the calcuated centroid coordinates.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberCentroid3DControllerVariable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberCentroid3DControllerVariable(A3200Handle handle, TASKID taskId, DOUBLE ControllerVariable);

/// \brief Executes a FastAlign 2D (two-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER FASTALIGN_Command.html">FIBER FASTALIGN</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberFastAlign2D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberFastAlign2D(A3200Handle handle, TASKID taskId);

/// \brief Executes a FastAlign 3D (three-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER FASTALIGN3D_Command.html">FIBER FASTALIGN3D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberFastAlign3D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberFastAlign3D(A3200Handle handle, TASKID taskId);

/// \brief Executes a FastAlign 4D (four-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER FASTALIGN4D_Command.html">FIBER FASTALIGN4D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberFastAlign4D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberFastAlign4D(A3200Handle handle, TASKID taskId);

/// \brief Executes a FastAlign 5D (five-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER FASTALIGN5D_Command.html">FIBER FASTALIGN5D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberFastAlign5D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberFastAlign5D(A3200Handle handle, TASKID taskId);

/// \brief Executes a FastAlign 6D (six-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER FASTALIGN6D_Command.html">FIBER FASTALIGN6D</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberFastAlign6D()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberFastAlign6D(A3200Handle handle, TASKID taskId);

/// \brief Executes a GeoCenter 2D (two-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER GEOCENTER_Command.html">FIBER GEOCENTER</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberGeoCenter()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberGeoCenter(A3200Handle handle, TASKID taskId);

/// \brief Executes a HillClimb FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER HILLCLIMB_Command.html">FIBER HILLCLIMB</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberHillClimb()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberHillClimb(A3200Handle handle, TASKID taskId);

/// \brief Executes a rough Spiral 2D (two-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER SPROUGH_Command.html">FIBER SPROUGH</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberSpiralRough()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberSpiralRough(A3200Handle handle, TASKID taskId);

/// \brief Executes a fine Spiral 2D (two-dimensional) FIBER search routine.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FIBER SPFINE_Command.html">FIBER SPFINE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup fiber
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFiberSpiralFine()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFiberSpiralFine(A3200Handle handle, TASKID taskId);


/// \brief Executes a clockwise circular move on the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/CW_Command.html">CW</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis1 The first axis on which to do clockwise circular motion.
/// \param[in] Axis1Endpoint The end point of the movement on the first specified axis.
/// \param[in] Axis2 The second axis on which to do clockwise circular motion.
/// \param[in] Axis2Endpoint The end point of the movement on the second specified axis.
/// \param[in] Radius The radius of the circle to use.
/// \param[in] CoordinatedSpeed The speed of the coordinated circular motion.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionCWAxisRadius()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionCWAxisRadius(A3200Handle handle, TASKID taskId, AXISINDEX Axis1, DOUBLE Axis1Endpoint, AXISINDEX Axis2, DOUBLE Axis2Endpoint, DOUBLE Radius, DOUBLE CoordinatedSpeed);

/// \brief Executes a clockwise circular move on the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/CW_Command.html">CW</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis1 The first axis on which to do clockwise circular motion.
/// \param[in] Axis1Endpoint The end point of the movement on the first specified axis.
/// \param[in] Axis2 The second axis on which to do clockwise circular motion.
/// \param[in] Axis2Endpoint The end point of the movement on the second specified axis.
/// \param[in] Axis1Center The relative offset of the center point from the starting position of the first axis.
/// \param[in] Axis2Center The relative offset of the center point from the starting position of the second axis.
/// \param[in] CoordinatedSpeed The speed of the coordinated circular motion.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionCWAxisCenter()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionCWAxisCenter(A3200Handle handle, TASKID taskId, AXISINDEX Axis1, DOUBLE Axis1Endpoint, AXISINDEX Axis2, DOUBLE Axis2Endpoint, DOUBLE Axis1Center, DOUBLE Axis2Center, DOUBLE CoordinatedSpeed);

/// \brief Executes a counterclockwise circular move on axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/CCW_Command.html">CCW</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis1 The first axis on which to do counterclockwise circular motion.
/// \param[in] Axis1Endpoint The end point of the movement on the first specified axis.
/// \param[in] Axis2 The second axis on which to do counterclockwise circular motion.
/// \param[in] Axis2Endpoint The end point of the movement on the second specified axis.
/// \param[in] Radius The radius of the circle to use.
/// \param[in] CoordinatedSpeed The speed of the coordinated circular motion.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionCCWAxisRadius()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionCCWAxisRadius(A3200Handle handle, TASKID taskId, AXISINDEX Axis1, DOUBLE Axis1Endpoint, AXISINDEX Axis2, DOUBLE Axis2Endpoint, DOUBLE Radius, DOUBLE CoordinatedSpeed);

/// \brief Executes a counterclockwise circular move on axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/CCW_Command.html">CCW</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis1 The first axis on which to do counterclockwise circular motion.
/// \param[in] Axis1Endpoint The end point of the movement on the first specified axis.
/// \param[in] Axis2 The second axis on which to do counterclockwise circular motion.
/// \param[in] Axis2Endpoint The end point of the movement on the second specified axis.
/// \param[in] Axis1Center The relative offset of the center point from the starting position of the first axis.
/// \param[in] Axis2Center The relative offset of the center point from the starting position of the second axis.
/// \param[in] CoordinatedSpeed The speed of the coordinated circular motion.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionCCWAxisCenter()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionCCWAxisCenter(A3200Handle handle, TASKID taskId, AXISINDEX Axis1, DOUBLE Axis1Endpoint, AXISINDEX Axis2, DOUBLE Axis2Endpoint, DOUBLE Axis1Center, DOUBLE Axis2Center, DOUBLE CoordinatedSpeed);

/// \brief Offsets the position of the master axis that is specified in the cam table.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SLAVEOFFSET_Command.html">SLAVEOFFSET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the camming slave axis.
/// \param[in] OffsetUnits The distance of offset in user units. To shift the cam table in the negative direction, specify a positive value. To shift the cam table in the positive direction, specify a negative value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSlaveOffset()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSlaveOffset(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis, DOUBLE OffsetUnits);

/// \brief Freeruns the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FREERUN_Command.html">FREERUN</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Velocity The velocity at which to run the axes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFreeRun()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFreeRun(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Velocity);

/// \brief Freeruns the axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FREERUN_Command.html">FREERUN</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionFreeRunStop()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionFreeRunStop(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Executes an incremental move on axes.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MOVEINC_Command.html">MOVEINC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis to move.
/// \param[in] Distance Distance and direction to move relative to the present position. A distance of zero results in no motion.
/// \param[in] Speed The speed, in user units/time base, at which to move an axis. The arithmetical sign is ignored and a speed of zero causes a task error.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionMoveInc()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionMoveInc(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Distance, DOUBLE Speed);

/// \brief Executes an absolute move on an axis.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MOVEABS_Command.html">MOVEABS</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis to move.
/// \param[in] Position The absolute position to move to.
/// \param[in] Speed The speed, in user units/time base, at which to move an axis. The arithmetical sign is ignored and a speed of zero causes a task error.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionMoveAbs()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionMoveAbs(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Position, DOUBLE Speed);

/// \brief Sets the autofocus to On or Off.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/AUTOFOCUS_Command.html">AUTOFOCUS</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis of the drive.
/// \param[in] OnOff Sets the autofocus to On or Off.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionAutoFocus()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionAutoFocus(A3200Handle handle, TASKID taskId, AXISINDEX Axis, ONOFF OnOff);

/// \brief Turns on or turns off a safe zone.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SAFEZONE ON_OFF_Command.html">SAFEZONE ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Zone The zero-based index of the safe zone.
/// \param[in] OnOff Turns the safe zone ON or OFF.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSafeZone()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSafeZone(A3200Handle handle, TASKID taskId, DWORD Zone, ONOFF OnOff);

/// \brief Sets the safe zone type.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SAFEZONE TYPE_Command.html">SAFEZONE TYPE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Zone The zero-based index of the safe zone.
/// \param[in] Type The safe zone type.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSafeZoneType()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSafeZoneType(A3200Handle handle, TASKID taskId, DWORD Zone, SAFEZONETYPE Type);

/// \brief Sets the safe zone boundaries.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SAFEZONE SET_Command.html">SAFEZONE SET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Zone The zero-based index of the safe zone.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Low The safe zone low boundary, specified in user units.
/// \param[in] High The safe zone high boundary, specified in user units.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSafeZoneSet()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSafeZoneSet(A3200Handle handle, TASKID taskId, DWORD Zone, AXISINDEX Axis, DOUBLE Low, DOUBLE High);

/// \brief Clears the safe zone boundaries.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SAFEZONE CLEAR_Command.html">SAFEZONE CLEAR</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup motion
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Zone The zero-based index of the safe zone.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200MotionSafeZoneClear()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200MotionSafeZoneClear(A3200Handle handle, TASKID taskId, DWORD Zone, AXISINDEX Axis);


/// \defgroup units Units Commands

/// \brief Sets primary units on the current task.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PRIMARY_Command.html">PRIMARY</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup units
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200UnitsPrimary()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200UnitsPrimary(A3200Handle handle, TASKID taskId);

/// \brief Sets secondary units on the current task.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SECONDARY_Command.html">SECONDARY</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup units
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200UnitsSecondary()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200UnitsSecondary(A3200Handle handle, TASKID taskId);

/// \brief Sets the feedrate to distance units per minute.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MINUTES_Command.html">MINUTES</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup units
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200UnitsMinutes()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200UnitsMinutes(A3200Handle handle, TASKID taskId);

/// \brief Sets the feedrate to distance units per second.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SECONDS_Command.html">SECONDS</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup units
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200UnitsSeconds()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200UnitsSeconds(A3200Handle handle, TASKID taskId);


/// \defgroup io IO Commands

/// \brief Gets the value of a specified analog input.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/$AI_Function.html">$AI</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Channel The analog channel to get the value of.
/// \param[in] Axis The axis on which to execute the command
/// \param[out] returnValue The value of the specified analog input.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IOAnalogInput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IOAnalogInput(A3200Handle handle, TASKID taskId, DWORD Channel, AXISINDEX Axis, DOUBLE* returnValue);

/// \brief Accesses the value of a specified analog output.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/$AO_Command.html">$AO</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Channel The analog channel to access the value of.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Value The value to set the specified analog output to.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IOAnalogOutput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IOAnalogOutput(A3200Handle handle, TASKID taskId, DWORD Channel, AXISINDEX Axis, DOUBLE Value);

/// \brief Gets the value of a specified digital input word.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/$WI_Function.html">$WI</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Word The 16-bit input word to get the value of.
/// \param[in] Axis The axis on which to execute the command
/// \param[out] returnValue The value of the specified digital input word.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IODigitalInput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IODigitalInput(A3200Handle handle, TASKID taskId, DWORD Word, AXISINDEX Axis, DWORD* returnValue);

/// \brief Accesses the value of a specified digital output word.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/$WO_Command.html">$WO</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Word The 16-bit output word to access the value of.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Value The value to set the specified digital output word to.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IODigitalOutput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IODigitalOutput(A3200Handle handle, TASKID taskId, DWORD Word, AXISINDEX Axis, DWORD Value);

/// \brief Gets the value of a specified digital input bit.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/$DI_Function.html">$DI</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Bit The digital input bit to get the value of.
/// \param[in] Axis The axis on which to execute the command
/// \param[out] returnValue The value of the specified digital input bit.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IODigitalInputBit()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IODigitalInputBit(A3200Handle handle, TASKID taskId, DWORD Bit, AXISINDEX Axis, DWORD* returnValue);

/// \brief Accesses the value of a specified digital output bit.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/$DO_Command.html">$DO</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup io
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Bit The digital output bit to access the value of.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Value The value to set the specified digital output bit to.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200IODigitalOutputBit()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200IODigitalOutputBit(A3200Handle handle, TASKID taskId, DWORD Bit, AXISINDEX Axis, DWORD Value);


/// \defgroup tuning Tuning Commands

/// \brief Initiates loop transmission mode.

///
/// \ingroup tuning
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Mode Specifies the transmission mode.
/// \param[in] Amplitude Sets the maximum loop output as a percentage of max current for open loop or distance for white noise.
/// \param[in] Frequency The frequency of the disturbance generated, in hertz.
/// \param[in] Type The type of loop transmission to run.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TuningLoopTrans()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TuningLoopTrans(A3200Handle handle, TASKID taskId, AXISINDEX Axis, LOOPTRANSMISSIONMODE Mode, DOUBLE Amplitude, DOUBLE Frequency, LOOPTRANSMISSIONTYPE Type);

/// \brief Sends a direct current command to the servo loop.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MC_Command.html">MC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup tuning
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Current The current to output, in amperes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TuningMComm()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TuningMComm(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Current);

/// \brief Generates an open-loop current command.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MSET_Command.html">MSET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup tuning
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Current The current to output, in amperes.
/// \param[in] Angle The electrical angle, in degrees. 360 degrees is one electrical commutation cycle of the motor.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TuningMSet()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TuningMSet(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Current, DWORD Angle);

/// \brief Generates sinusoidal oscillation on an axis.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/OSCILLATE_Command.html">OSCILLATE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup tuning
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Distance Defines the peak-to-peak displacement of the motion. The amplitude of the oscillate sequence is 1/2 of the peak-to-peak displacement. The arithmetic sign specifies the initial direction of the motion.
/// \param[in] Frequency The frequency of oscillation, in hertz. You must specify a frequency that is greater than 0 Hz and less than or equal to 500 Hz. Because the controller generates sinusoidal positions and velocities at a 1 kHz rate, less accurate motion might occur if you specify higher oscillation frequencies to this command.
/// \param[in] Cycles The number of sinusoidal cycles to generate during the oscillate sequence. Each cycle is one full sinusoidal cycle.
/// \param[in] NumIterations The number of oscillate sequences to execute. After the controller executes the first oscillate sequence, the following changes occur for the subsequent execution of each of the other sequences. The amplitude of the motion decreases to 1/4 of its previous value, the frequency is doubled, and the number of cycles is doubled. If you do not specify a value for this argument, it defaults to a value of one.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TuningOscillate()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TuningOscillate(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE Distance, DOUBLE Frequency, DWORD Cycles, DWORD NumIterations);

/// \brief Sets four or nine servo loop gains at the same time.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SET GAIN_Command.html">SET GAIN</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup tuning
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] GainKpos The position loop gain for the axis.
/// \param[in] GainKi The integral gain of the velocity loop for the axis.
/// \param[in] GainKp The proportional gain of the velocity loop for the axis.
/// \param[in] GainAff The acceleration feedforward gain.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TuningSetGain()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TuningSetGain(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE GainKpos, DOUBLE GainKi, DOUBLE GainKp, DOUBLE GainAff);

/// \brief Sets four or nine servo loop gains at the same time.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/SET GAIN_Command.html">SET GAIN</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup tuning
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] GainKpos The position loop gain for the axis.
/// \param[in] GainKi The integral gain of the velocity loop for the axis.
/// \param[in] GainKp The proportional gain of the velocity loop for the axis.
/// \param[in] GainAff The acceleration feedforward gain.
/// \param[in] GainKd1 The derivative gain of the primary (position) loop.
/// \param[in] GainKpi The integral gain of the position loop.
/// \param[in] GainKp1 The proportional gain of the primary (position) loop.
/// \param[in] GainVff The velocity feedforward gain.
/// \param[in] GainPff The position feedforward gain.
/// \param[in] GainDff The acceleration feedforward gain that will be used when an axis is decelerating.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TuningSetGainAdvanced()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TuningSetGainAdvanced(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE GainKpos, DOUBLE GainKi, DOUBLE GainKp, DOUBLE GainAff, DOUBLE GainKd1, DOUBLE GainKpi, DOUBLE GainKp1, DOUBLE GainVff, DOUBLE GainPff, DOUBLE GainDff);


/// \defgroup program Tasks Commands

/// \brief Sets the MFO (manual feedrate override) for a task.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MFO_Command.html">MFO</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup program
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Task The task on which to set the MFO.
/// \param[in] Value The MFO percentage to set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TasksMFO()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TasksMFO(A3200Handle handle, TASKID taskId, TASKID Task, DOUBLE Value);

/// \brief Sets a user-defined task error on a task.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/USERTASKERROR_Command.html">USERTASKERROR</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup program
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Task The task on which to set the user-defined task error.
/// \param[in] ErrorLocation The error location to set as defined in the user-defined messages text file.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TasksUserTaskError()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TasksUserTaskError(A3200Handle handle, TASKID taskId, TASKID Task, DWORD ErrorLocation);

/// \brief Sets a user-defined task warning on a task.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/USERTASKWARNING_Command.html">USERTASKWARNING</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup program
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Task The task on which to set the user-defined task warning.
/// \param[in] WarningLocation The warning location to set as defined in the user-defined messages text file.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200TasksUserTaskWarning()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200TasksUserTaskWarning(A3200Handle handle, TASKID taskId, TASKID Task, DWORD WarningLocation);


/// \defgroup adv Advanced Commands

/// \defgroup analog Advanced Analog Commands

/// \brief Configures the system to continuously set an analog output to be a real-time internal servo loop value.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ANALOG TRACK_Command.html">ANALOG TRACK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup analog
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] AnalogOutput The analog output to which the value is sent.
/// \param[in] ServoValue Specifies the servo loop value that is tracked.
/// \param[in] ScaleFactor The value that you use to change the servo loop units to the analog output voltage.
/// \param[in] OffsetValue This value is applied with the tracking value to the analog output. Use this argument if you want to track position on a stage where the position can never be negative. The units are volts.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AdvancedAnalogTrack()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AdvancedAnalogTrack(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD AnalogOutput, DWORD ServoValue, DOUBLE ScaleFactor, DOUBLE OffsetValue);

/// \brief Configures the system to continuously set an analog output to be a real-time internal servo loop value.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ANALOG TRACK_Command.html">ANALOG TRACK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup analog
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] AnalogOutput The analog output to which the value is sent.
/// \param[in] ServoValue Specifies the servo loop value that is tracked.
/// \param[in] ScaleFactor The value that you use to change the servo loop units to the analog output voltage.
/// \param[in] OffsetValue This value is applied with the tracking value to the analog output. Use this argument if you want to track position on a stage where the position can never be negative. The units are volts.
/// \param[in] MinVoltage Specifies the minimum voltage for the analog output.
/// \param[in] MaxVoltage Specifies the maximum voltage for the analog output.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AdvancedAnalogTrackLimit()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AdvancedAnalogTrackLimit(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD AnalogOutput, DWORD ServoValue, DOUBLE ScaleFactor, DOUBLE OffsetValue, DOUBLE MinVoltage, DOUBLE MaxVoltage);

/// \brief Configures an axis to generate its position command based on an analog input signal.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ANALOG CONTROL ON_OFF_Command.html">ANALOG CONTROL ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup analog
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] AnalogInput The analog input to use as the input to this command.
/// \param[in] ScaleFactor The value that you use to scale the analog input voltage. The units are user units per volt.
/// \param[in] OffsetValue The value that specifies the voltage offset for the analog input signal. The units are volts.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AdvancedAnalogControlOn()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AdvancedAnalogControlOn(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD AnalogInput, DOUBLE ScaleFactor, DOUBLE OffsetValue);

/// \brief Configures an axis to generate its position command based on an analog input signal.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ANALOG CONTROL ON_OFF_Command.html">ANALOG CONTROL ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup analog
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] AnalogInput The analog input to use as the input to this command.
/// \param[in] ScaleFactor The value that you use to scale the analog input voltage. The units are user units per volt.
/// \param[in] OffsetValue The value that specifies the voltage offset for the analog input signal. The units are volts.
/// \param[in] SpeedValue Specifies the maximum speed at which the controller commands the axis to move while the axis is under the control of this command. The units are user units per second. If you do not specify this argument or if you specify a value of 0 for this argument, then the controller does not limit the maximum speed.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AdvancedAnalogControlOnSpeed()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AdvancedAnalogControlOnSpeed(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD AnalogInput, DOUBLE ScaleFactor, DOUBLE OffsetValue, DOUBLE SpeedValue);

/// \brief Configures an axis to generate its position command based on an analog input signal.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ANALOG CONTROL ON_OFF_Command.html">ANALOG CONTROL ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup analog
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AdvancedAnalogControlOff()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AdvancedAnalogControlOff(A3200Handle handle, TASKID taskId, AXISINDEX Axis);


/// \brief Determines if the specified password matches the password set on the controller.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/CHECKPASSWORD_Command.html">CHECKPASSWORD</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup adv
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Password Password to compare to the password stored on the controller.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AdvancedCheckPassword()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AdvancedCheckPassword(A3200Handle handle, TASKID taskId, const char* Password);


/// \defgroup gearing Gearing Commands

/// \brief Configures the master and slave relationship for gearing.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/GEAR MASTERCONFIG_Command.html">GEAR MASTERCONFIG</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup gearing
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \param[in] MasterAxis The axis that is set as the master axis.
/// \param[in] GearMode The master axis signal from which the slave axis is geared.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200GearingGearSetup()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200GearingGearSetup(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis, AXISINDEX MasterAxis, GEARINGTRACKINGMODE GearMode);

/// \brief Defines the ratio of movement between the master axis and slave axis. The slave axis moves SlaveValue counts for every MasterValue counts.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/GEAR RATIO_Command.html">GEAR RATIO</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup gearing
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \param[in] SlaveValue The number of counts the slave axis moves for every MasterValue counts of master axis motion.
/// \param[in] MasterValue The number of counts of master axis motion for which the slave axis moves SlaveValue counts.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200GearingGearRatio()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200GearingGearRatio(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis, DWORD SlaveValue, DWORD MasterValue);

/// \brief Connects or disconnects the slave axis to or from the master axis.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/GEAR ON_OFF_Command.html">GEAR ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup gearing
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200GearingGearOn()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200GearingGearOn(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis);

/// \brief Connects or disconnects the slave axis to or from the master axis.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/GEAR ON_OFF_Command.html">GEAR ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup gearing
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200GearingGearOnFiltered()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200GearingGearOnFiltered(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis);

/// \brief Connects or disconnects the slave axis to or from the master axis.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/GEAR ON_OFF_Command.html">GEAR ON/OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup gearing
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200GearingGearOff()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200GearingGearOff(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis);


/// \defgroup dataacq DataAcquisition Commands

/// \brief Configures the location in the drive array space where the captured data is stored and the number of data elements to collect. Enables data collection.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/DATAACQ ARRAY_Command.html">DATAACQ ARRAY</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup dataacq
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] ArrayStart The starting location where captured data is stored on the drive array. Each trigger event stores its data in the next sequential array location. If the subsequent index exceeds the size of the drive array, the index resets to zero so that collection can continue.
/// \param[in] NumberOfElements The number of elements to be collected. After the specified number of elements are collected, data acquisition turns off automatically. On multi-axis drives, more than one element can be collected at each trigger event. Thus, this argument must specify the number of data elements to store, not the number of trigger events.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200DataAcquisitionArraySetup()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200DataAcquisitionArraySetup(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD ArrayStart, DWORD NumberOfElements);

/// \brief Transfers drive array values into the specified controller array variables.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ARRAY READ_Command.html">ARRAY READ</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup dataacq
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] ControllerVariable The controller variable on which to write data that is read from the drive array.
/// \param[in] StartIndex The starting index of the drive array from which the data is read.
/// \param[in] NumberOfElements The number of elements to be read.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200DataAcquisitionArrayRead()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200DataAcquisitionArrayRead(A3200Handle handle, TASKID taskId, AXISINDEX Axis, const char* ControllerVariable, DWORD StartIndex, DWORD NumberOfElements);

/// \brief Transfers drive array values into the specified controller array variables.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ARRAY READ_Command.html">ARRAY READ</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup dataacq
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] ControllerVariable The controller variable on which to write data that is read from the drive array.
/// \param[in] StartIndex The starting index of the drive array from which the data is read.
/// \param[in] NumberOfElements The number of elements to be read.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200DataAcquisitionArrayReadFast()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200DataAcquisitionArrayReadFast(A3200Handle handle, TASKID taskId, AXISINDEX Axis, const char* ControllerVariable, DWORD StartIndex, DWORD NumberOfElements);

/// \brief Specifies the data element collected when a trigger occurs.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/DATAACQ INPUT_Command.html">DATAACQ INPUT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup dataacq
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] SourceSignal The source signal to be collected.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200DataAcquisitionInput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200DataAcquisitionInput(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD SourceSignal);

/// \brief Specifies which signal is monitored to collect data.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/DATAACQ TRIGGER_Command.html">DATAACQ TRIGGER</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup dataacq
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] TriggerSignal The signal to be triggered on.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200DataAcquisitionTrigger()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200DataAcquisitionTrigger(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD TriggerSignal);

/// \brief Use this command to turn data acquisition off. All previously specified DATAACQ command configurations are cleared and must be re-specified if required.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/DATAACQ OFF_Command.html">DATAACQ OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup dataacq
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200DataAcquisitionOff()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200DataAcquisitionOff(A3200Handle handle, TASKID taskId, AXISINDEX Axis);


/// \defgroup camming Camming Commands

/// \brief Starts synchronizing the master axis to the slave axis.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/CAMSYNC_Command.html">CAMSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup camming
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \param[in] TableNumber The table number, from 0 to 99.
/// \param[in] SyncMode The synchronization mode to use for camming.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200CammingCamSync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200CammingCamSync(A3200Handle handle, TASKID taskId, AXISINDEX SlaveAxis, DWORD TableNumber, CAMMINGSYNCMODE SyncMode);

/// \brief Loads a camming table from a file on the PC.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/LOADCAMTABLE_Command.html">LOADCAMTABLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup camming
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] MasterAxis The axis that is set as the master axis.
/// \param[in] TableNumber The table number, ranging from 0 to 99. Specify the same table number in the corresponding subsequent CAMSYNC command.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \param[in] InterpolationType The interpolation mode to use when calculating points between two points in the table. Set to 0 for linear splining or 1 for cubic splining.
/// \param[in] TrackingMode If the master axis is a real axis, use this argument to specify the tracking mode. Set this argument to 0 to have the slave track the master position feedback. Set it to 1 to have the slave track the master position command. Set it to 2 to have the slave track the master auxiliary encoder channel.
/// \param[in] FileName The name and path of the file that contains the cam table.
/// \param[in] Wrap Whether to wrap the table or not.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200CammingLoadCamTable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200CammingLoadCamTable(A3200Handle handle, TASKID taskId, AXISINDEX MasterAxis, DWORD TableNumber, AXISINDEX SlaveAxis, CAMMINGINTERPOLATIONTYPE InterpolationType, CAMMINGTRACKINGMODE TrackingMode, const char* FileName, BOOL Wrap);

/// \brief Uses global variables as the cam table.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/LOADCAMVAR_Command.html">LOADCAMVAR</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup camming
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] MasterAxis The axis that is set as the master axis.
/// \param[in] TableNumber The table number, from 0 to 99.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \param[in] InterpolationType The interpolation mode to use for camming. Set to 0 for linear splining or 1 for cubic splining.
/// \param[in] TrackingMode Set to 0 to have the slave axis track the position feedback of the master axis. Set to 1 to have the slave axis track the master axis position. Set to 2 to have the slave axis track the auxiliary encoder channel of the master axis.
/// \param[in] MasterStart The master axis starting position.
/// \param[in] MasterDelta The master axis position delta.
/// \param[in] VariableStart The variable where the table starts.
/// \param[in] VariableNumber The number of points in the variables to read.
/// \param[in] Wrap Whether to wrap the table or not.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200CammingLoadCamVariablesUnits()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200CammingLoadCamVariablesUnits(A3200Handle handle, TASKID taskId, AXISINDEX MasterAxis, DWORD TableNumber, AXISINDEX SlaveAxis, CAMMINGINTERPOLATIONTYPE InterpolationType, CAMMINGTRACKINGMODE TrackingMode, DOUBLE MasterStart, DOUBLE MasterDelta, DWORD VariableStart, DWORD VariableNumber, BOOL Wrap);

/// \brief Uses global variables as the cam table.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/LOADCAMVAR_Command.html">LOADCAMVAR</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup camming
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] MasterAxis The axis that is set as the master axis.
/// \param[in] TableNumber The table number, from 0 to 99.
/// \param[in] SlaveAxis The axis that is set as the slave axis.
/// \param[in] InterpolationType The interpolation mode to use for camming. Set to 0 for linear splining or 1 for cubic splining.
/// \param[in] TrackingMode Set to 0 to have the slave axis track the position feedback of the master axis. Set to 1 to have the slave axis track the master axis position. Set to 2 to have the slave axis track the auxiliary encoder channel of the master axis.
/// \param[in] MasterStart The master axis starting position.
/// \param[in] MasterDelta The master axis position delta.
/// \param[in] VariableStart The variable where the table starts.
/// \param[in] VariableNumber The number of points in the variables to read.
/// \param[in] Wrap Whether to wrap the table or not.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200CammingLoadCamVariablesCounts()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200CammingLoadCamVariablesCounts(A3200Handle handle, TASKID taskId, AXISINDEX MasterAxis, DWORD TableNumber, AXISINDEX SlaveAxis, CAMMINGINTERPOLATIONTYPE InterpolationType, CAMMINGTRACKINGMODE TrackingMode, DOUBLE MasterStart, DOUBLE MasterDelta, DWORD VariableStart, DWORD VariableNumber, BOOL Wrap);

/// \brief Frees a cam table from the controller memory.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/FREECAMTABLE_Command.html">FREECAMTABLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup camming
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] TableNumber The table number, from 0 to 99.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200CammingFreeCamTable()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200CammingFreeCamTable(A3200Handle handle, TASKID taskId, DWORD TableNumber);


/// \defgroup pso PSO Commands

/// \brief Writes data into the PSO array.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ARRAY WRITE_Command.html">ARRAY WRITE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] ControllerVariable The name of the first controller variable to write to the drive array.
/// \param[in] StartIndex The starting index of the drive array where controller variables are written.
/// \param[in] NumberOfElements The number of elements to send.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOArray()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOArray(A3200Handle handle, TASKID taskId, AXISINDEX Axis, const char* ControllerVariable, DWORD StartIndex, DWORD NumberOfElements);

/// \brief Enables and disables the PSO hardware.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOCONTROL_Command.html">PSOCONTROL</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Mode The mode of operation of the PSO hardware.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOControl()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOControl(A3200Handle handle, TASKID taskId, AXISINDEX Axis, PSOMODE Mode);

/// \brief Specifies the distance that an axis travels between firing events.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSODISTANCE_Command.html">PSODISTANCE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] FireDistance The distance, in encoder counts, that an axis must travel before a firing event triggers the pulse generator.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSODistanceFixed()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSODistanceFixed(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE FireDistance);

/// \brief Specifies the distance that an axis travels between firing events.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSODISTANCE_Command.html">PSODISTANCE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] StartIndex The element of the array that contains the first incremental firing distance.
/// \param[in] NumberOfFiringEvents The number of firing events.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSODistanceArray()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSODistanceArray(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD StartIndex, DWORD NumberOfFiringEvents);

/// \brief Specifies the distance that an axis travels between firing events.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSODISTANCE_Command.html">PSODISTANCE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSODistanceOff()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSODistanceOff(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE_Command.html">PSOOUTPUT PULSE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulse()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulse(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE2 WINDOW MASK_Command.html">PSOOUTPUT PULSE2 WINDOW MASK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulse2WindowMask()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulse2WindowMask(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE BIT MASK_Command.html">PSOOUTPUT PULSE BIT MASK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \param[in] StartIndex The index of the first array data in the drive memory where the bit map data is stored.
/// \param[in] NumElements The total number of bit map data elements that are stored in the drive memory.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseBitMask()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseBitMask(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect, DWORD StartIndex, DWORD NumElements);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE BIT MASK EXTSYNC_Command.html">PSOOUTPUT PULSE BIT MASK EXTSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] StartIndex The index of the first array data in the drive memory where the bit map data is stored.
/// \param[in] NumElements The total number of bit map data elements that are stored in the drive memory.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseBitMaskExtSync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseBitMaskExtSync(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD StartIndex, DWORD NumElements);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT TOGGLE_Command.html">PSOOUTPUT TOGGLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputToggle()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputToggle(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE LASER MASK_Command.html">PSOOUTPUT PULSE LASER MASK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseLaserMask()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseLaserMask(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE LASER MASK EXTSYNC_Command.html">PSOOUTPUT PULSE LASER MASK EXTSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseLaserMaskExtSync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseLaserMaskExtSync(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT WINDOW_Command.html">PSOOUTPUT WINDOW</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputWindow()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputWindow(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE WINDOW MASK_Command.html">PSOOUTPUT PULSE WINDOW MASK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \param[in] EdgeMode Specify pulse output behavior. This argument is required if you use the EDGE keyword.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseWindowMask()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseWindowMask(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect, DWORD EdgeMode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE WINDOW MASK_Command.html">PSOOUTPUT PULSE WINDOW MASK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \param[in] EdgeMode Specify pulse output behavior. This argument is required if you use the EDGE keyword.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseWindowMaskHard()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseWindowMaskHard(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect, DWORD EdgeMode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE WINDOW MASK EXTSYNC_Command.html">PSOOUTPUT PULSE WINDOW MASK EXTSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] EdgeMode Specify pulse output behavior. This argument is required if you use the EDGE keyword.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseWindowMaskExtSync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseWindowMaskExtSync(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD EdgeMode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE WINDOW MASK EXTSYNC_Command.html">PSOOUTPUT PULSE WINDOW MASK EXTSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] EdgeMode Specify pulse output behavior. This argument is required if you use the EDGE keyword.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseWindowMaskExtSyncHard()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseWindowMaskExtSyncHard(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD EdgeMode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE WINDOW BIT MASK_Command.html">PSOOUTPUT PULSE WINDOW BIT MASK</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] StartIndex The index of the first array data in the drive memory where the bit map data is stored.
/// \param[in] NumElements The total number of bit map data elements stored in the drive memory.
/// \param[in] EdgeMode Specifies the pulse output behavior. This argument is required if you use the EDGE keyword.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseWindowBitMask()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseWindowBitMask(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD StartIndex, DWORD NumElements, DWORD EdgeMode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE WINDOW BIT MASK EXTSYNC_Command.html">PSOOUTPUT PULSE WINDOW BIT MASK EXTSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] StartIndex The index of the first array data in the drive memory where the bit map data is stored.
/// \param[in] NumElements The total number of bit map data elements stored in the drive memory.
/// \param[in] EdgeMode Specifies the pulse output behavior. This argument is required if you use the EDGE keyword.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseWindowBitMaskExtSync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseWindowBitMaskExtSync(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD StartIndex, DWORD NumElements, DWORD EdgeMode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT CONTROL_Command.html">PSOOUTPUT CONTROL</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Pin Applies only to Npaq, Nservo, and XR3. Does not apply to Npaq MR. Specifies the pin number of PSO output.
/// \param[in] Mode Does not apply to the XR3. Used to select the mode of PSO output.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputControl()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputControl(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD Pin, DWORD Mode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT BIT MAP_Command.html">PSOOUTPUT BIT MAP</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] OutputSelect Applies only to Npaq and Nservo. Does not apply to Npaq MR. Selects the output module to which configuration commands are sent. If you do not specify this argument, or if you set the value to 0, then the first module is configured. Refer to Main Output and Auxiliary Output signals in the PSO Block Diagrams for more information.
/// \param[in] StartIndex The index of the first array data in the drive memory where the bit map data is stored.
/// \param[in] NumElements The total number of bit map data elements stored in the drive memory.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputBitMap()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputBitMap(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD OutputSelect, DWORD StartIndex, DWORD NumElements);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT BIT MAP_Command.html">PSOOUTPUT BIT MAP</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] StartIndex The index of the first array data in the drive memory where the bit map data is stored.
/// \param[in] NumElements The total number of bit map data elements stored in the drive memory.
/// \param[in] Mode Specifies the mode of operation for the BIT MAP functionality. If you do not specify this argument or if you set the value to 0, then the drive uses only the most significant bit of each array value, which is bit 31. If you set the value to 1, the drive uses all 32 bits of each array value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputBitMapMode()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputBitMapMode(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD StartIndex, DWORD NumElements, DWORD Mode);

/// \brief Sets the PSO combine mode (adding Aux. Output to the Main Output signal).

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT COMBINE_Command.html">PSOOUTPUT COMBINE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Mode A value of 0 disables Npaq combine mode. A value of 1 enables Npaq combine mode.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputCombine()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputCombine(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD Mode);

/// \brief Sets the PSO output mode.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOOUTPUT PULSE EXTSYNC_Command.html">PSOOUTPUT PULSE EXTSYNC</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOOutputPulseExtSync()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOOutputPulseExtSync(A3200Handle handle, TASKID taskId, AXISINDEX Axis);

/// \brief Configures the pulse sequence that is used for PSO.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOPULSE_Command.html">PSOPULSE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] TotalTime The total time of generated pulse in microseconds.
/// \param[in] OnTime The time of the cycle when the PSO output is in the ON state.
/// \param[in] NumCycles The number of pulses to generate in a single pulse event.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOPulseCyclesOnly()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOPulseCyclesOnly(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE TotalTime, DOUBLE OnTime, DOUBLE NumCycles);

/// \brief Configures the pulse sequence that is used for PSO.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOPULSE_Command.html">PSOPULSE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] TotalTime The total time of generated pulse in microseconds.
/// \param[in] OnTime The time of the cycle when the PSO output is in the ON state.
/// \param[in] DelayTime The quantity of time to delay between a fire event and the laser output.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOPulseDelayOnly()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOPulseDelayOnly(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE TotalTime, DOUBLE OnTime, DOUBLE DelayTime);

/// \brief Configures the pulse sequence that is used for PSO.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOPULSE_Command.html">PSOPULSE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] TotalTime The total time of generated pulse in microseconds.
/// \param[in] OnTime The time of the cycle when the PSO output is in the ON state.
/// \param[in] NumCycles The number of pulses to generate in a single pulse event.
/// \param[in] DelayTime The quantity of time to delay between a fire event and the laser output.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOPulseCyclesAndDelay()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOPulseCyclesAndDelay(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DOUBLE TotalTime, DOUBLE OnTime, DOUBLE NumCycles, DOUBLE DelayTime);

/// \brief Configures the PSO distance tracking counters.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOTRACK INPUT_Command.html">PSOTRACK INPUT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Source1 The encoder to use as the source for the first axis of tracking (use for single-axis).
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOTrackInput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOTrackInput(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD Source1);

/// \brief Configures the PSO distance tracking counters.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOTRACK INPUT_Command.html">PSOTRACK INPUT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Source1 The encoder to use as the source for the first axis of tracking (use for single-axis).
/// \param[in] Source2 The encoder to use as the source for the second axis of tracking (DO NOT use for single-axis).
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOTrackInputInput2()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOTrackInputInput2(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD Source1, DWORD Source2);

/// \brief Configures the PSO distance tracking counters.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOTRACK INPUT_Command.html">PSOTRACK INPUT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Source1 The encoder to use as the source for the first axis of tracking (use for single-axis).
/// \param[in] Source2 The encoder to use as the source for the second axis of tracking (DO NOT use for single-axis).
/// \param[in] Source3 The encoder to use as the source for the third axis of tracking (DO NOT use for single-axis).
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOTrackInputInput2Input3()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOTrackInputInput2Input3(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD Source1, DWORD Source2, DWORD Source3);

/// \brief Configures the PSO distance tracking counters.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOTRACK RESET_Command.html">PSOTRACK RESET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] RBitMask The mask of possible conditions that can hold the tracking counter in reset.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOTrackReset()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOTrackReset(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD RBitMask);

/// \brief Configures the PSO distance tracking counters.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOTRACK SCALE_Command.html">PSOTRACK SCALE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] PreScale1 The divisor applied to the encoder input to the first PSO channel.
/// \param[in] PreScale2 The divisor applied to the encoder input to the second PSO channel.
/// \param[in] PreScale3 The divisor applied to the encoder input to the third PSO channel.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOTrackScale()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOTrackScale(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD PreScale1, DWORD PreScale2, DWORD PreScale3);

/// \brief Configures the PSO distance tracking counters.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOTRACK DIRECTION_Command.html">PSOTRACK DIRECTION</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] DBitMask The mask of possible directions to be suppressed when tracking position.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOTrackDirection()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOTrackDirection(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD DBitMask);

/// \brief Enables the PSO Window Hardware.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW ON_Command.html">PSOWINDOW ON</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowOn()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowOn(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber);

/// \brief Enables the PSO Window Hardware.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW ON_Command.html">PSOWINDOW ON</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowOnInvert()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowOnInvert(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber);

/// \brief Disables the PSO Window Hardware.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW OFF_Command.html">PSOWINDOW OFF</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowOff()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowOff(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber);

/// \brief Configures which encoder channel is connected to each window.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW INPUT_Command.html">PSOWINDOW INPUT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \param[in] Source The encoder to use as the source for the first axis of tracking (use for single-axis).
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowInput()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowInput(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber, DWORD Source);

/// \brief Configures which encoder channel is connected to each window.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW INPUT_Command.html">PSOWINDOW INPUT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \param[in] Source The encoder to use as the source for the first axis of tracking (use for single-axis).
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowInputInvert()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowInputInvert(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber, DWORD Source);

/// \brief Resets the window counter to 0 based on the encoder marker signal.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW RESET_Command.html">PSOWINDOW RESET</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \param[in] BitMask The mask of possible conditions that hold the tracking counter in reset.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowReset()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowReset(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber, DWORD BitMask);

/// \brief Loads the specified window counter with a value.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW LOAD_Command.html">PSOWINDOW LOAD</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \param[in] Value The value to load into the specified window.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowLoad()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowLoad(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber, DWORD Value);

/// \brief Specifies the window range based on data in the PSO array.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW RANGE ARRAY_Command.html">PSOWINDOW RANGE ARRAY</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. Set to 1 or 2.
/// \param[in] StartIndex The index of the first array value to load into the window.
/// \param[in] NumElements The number of values to sequentially load into the window.
/// \param[in] EdgeCode An optional argument that lets the controller update the PSO window range based on how the axis exits the PSO window.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowRangeArray()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowRangeArray(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber, DOUBLE StartIndex, DOUBLE NumElements, DOUBLE EdgeCode);

/// \brief Specifies the low and high window-range values for the specified PSO window.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW RANGE_Command.html">PSOWINDOW RANGE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] WindowNumber The window to configure. The Ndrive CP, MP, QL, and Npaq MR with MP drives must be set to 1. All other drives can be set to 1 or 2.
/// \param[in] LowValue The low limit, in encoder counts, of the fixed window range.
/// \param[in] HighValue The high limit, in encoder counts, of the fixed window range.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowRange()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowRange(A3200Handle handle, TASKID taskId, AXISINDEX Axis, DWORD WindowNumber, DOUBLE LowValue, DOUBLE HighValue);

/// \brief Specifies that the two PSO window counters are either co-dependent or independent.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/PSOWINDOW CONTROL_Command.html">PSOWINDOW CONTROL</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup pso
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The axis on which to execute the command
/// \param[in] Mode The window control mode to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200PSOWindowControl()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200PSOWindowControl(A3200Handle handle, TASKID taskId, AXISINDEX Axis, PSOWINDOWDEPENDANCE Mode);


/// \defgroup Modbus Modbus Commands

/// \brief Provides access to a Modbus register set as 16-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT16_Function.html">MODBUSREGINT16</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 available only with the Professional option).
/// \param[in] RegName The register set to access (MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords). The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt16Write()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt16Write(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, DWORD Value);

/// \brief Provides access to a Modbus register set as 16-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT16_Function.html">MODBUSREGINT16</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 available only with the Professional option).
/// \param[in] RegName The register set to access (MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords). The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt16Read()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt16Read(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, DWORD* returnValue);

/// \brief Provides access to a Modbus register set as 16-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT16_Function.html">MODBUSREGINT16</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis Specify the name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access (MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords). The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt16WriteDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt16WriteDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, DWORD Value);

/// \brief Provides access to a Modbus register set as 16-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT16_Function.html">MODBUSREGINT16</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis Specify the name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access (MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords). The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt16ReadDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt16ReadDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, DWORD* returnValue);

/// \brief Provides access to a Modbus register set as 32-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT32_Function.html">MODBUSREGINT32</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (sets 1 - 15 are available only with the Professional option).
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt32Write()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt32Write(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, DWORD Value);

/// \brief Provides access to a Modbus register set as 32-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT32_Function.html">MODBUSREGINT32</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (sets 1 - 15 are available only with the Professional option).
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt32Read()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt32Read(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, DWORD* returnValue);

/// \brief Provides access to a Modbus register set as 32-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT32_Function.html">MODBUSREGINT32</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt32WriteDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt32WriteDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, DWORD Value);

/// \brief Provides access to a Modbus register set as 32-bit integer values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGINT32_Function.html">MODBUSREGINT32</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterInt32ReadDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterInt32ReadDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, DWORD* returnValue);

/// \brief Provides access to a Modbus register set as single-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGSINGLE_Function.html">MODBUSREGSINGLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 available only with the Professional option).
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterFloatWrite()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterFloatWrite(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, FLOAT Value);

/// \brief Provides access to a Modbus register set as single-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGSINGLE_Function.html">MODBUSREGSINGLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 available only with the Professional option).
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterFloatRead()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterFloatRead(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, FLOAT* returnValue);

/// \brief Provides access to a Modbus register set as single-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGSINGLE_Function.html">MODBUSREGSINGLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterFloatWriteDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterFloatWriteDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, FLOAT Value);

/// \brief Provides access to a Modbus register set as single-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGSINGLE_Function.html">MODBUSREGSINGLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterFloatReadDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterFloatReadDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, FLOAT* returnValue);

/// \brief Provides access to a Modbus register set as double-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGDOUBLE_Function.html">MODBUSREGDOUBLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 available only with the Professional option).
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterDoubleWrite()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterDoubleWrite(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, DOUBLE Value);

/// \brief Provides access to a Modbus register set as double-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGDOUBLE_Function.html">MODBUSREGDOUBLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 available only with the Professional option).
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterDoubleRead()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterDoubleRead(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE RegName, DWORD RegNumber, DOUBLE* returnValue);

/// \brief Provides access to a Modbus register set as double-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGDOUBLE_Function.html">MODBUSREGDOUBLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to store.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterDoubleWriteDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterDoubleWriteDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, DOUBLE Value);

/// \brief Provides access to a Modbus register set as double-precision floating-point values.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSREGDOUBLE_Function.html">MODBUSREGDOUBLE</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis on which to use the Modbus register set.
/// \param[in] RegName The register set to access. Either MasterInputWords, SlaveInputWords, MasterOutputWords, or SlaveOutputWords. The input words have read-only access, and the output words have read and write access.
/// \param[in] RegNumber The index number of the register to access. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusRegisterDoubleReadDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusRegisterDoubleReadDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE RegName, DWORD RegNumber, DOUBLE* returnValue);

/// \brief Provides access to a Modbus bit set.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSBIT_Function.html">MODBUSBIT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Identifies the Modbus connection to use. Specify the axis name on which to use the Modbus register set. Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 only available with the Professional option).
/// \param[in] BitName The bit set to access. Either MasterInputBits, SlaveInputBits, MasterOutputBits, or SlaveOutputBits. The input bits have read-only access, and the output bits have read and write access.
/// \param[in] BitNumber The bit number in the set. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to write to the bit. Either 0 or 1.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusBitWrite()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusBitWrite(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE BitName, DWORD BitNumber, DWORD Value);

/// \brief Provides access to a Modbus bit set.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSBIT_Function.html">MODBUSBIT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] ConnectionNumber Identifies the Modbus connection to use. Specify the axis name on which to use the Modbus register set. Specify a number from 0 - 15 to use the corresponding PC Modbus register set (1 - 15 only available with the Professional option).
/// \param[in] BitName The bit set to access. Either MasterInputBits, SlaveInputBits, MasterOutputBits, or SlaveOutputBits. The input bits have read-only access, and the output bits have read and write access.
/// \param[in] BitNumber The bit number in the set. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusBitRead()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusBitRead(A3200Handle handle, TASKID taskId, DWORD ConnectionNumber, REGISTERTYPE BitName, DWORD BitNumber, DWORD* returnValue);

/// \brief Provides access to a Modbus bit set.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSBIT_Function.html">MODBUSBIT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis for drive Modbus.
/// \param[in] BitName The bit set to access. Either MasterInputBits, SlaveInputBits, MasterOutputBits, or SlaveOutputBits. The input bits have read-only access, and the output bits have read and write access.
/// \param[in] BitNumber The bit number in the set. This argument can be an expression and must be a positive integer.
/// \param[in] Value The value to write to the bit. Either 0 or 1.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusBitWriteDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusBitWriteDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE BitName, DWORD BitNumber, DWORD Value);

/// \brief Provides access to a Modbus bit set.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/MODBUSBIT_Function.html">MODBUSBIT</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup Modbus
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \param[in] Axis The name of the axis for drive Modbus.
/// \param[in] BitName The bit set to access. Either MasterInputBits, SlaveInputBits, MasterOutputBits, or SlaveOutputBits. The input bits have read-only access, and the output bits have read and write access.
/// \param[in] BitNumber The bit number in the set. This argument can be an expression and must be a positive integer.
/// \param[out] returnValue The stored value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200ModbusBitReadDrive()
/// \until A3200Disconnect
DEPRECATED("This command is obsolete. The new Modbus implementation does not require this command. Refer to the Fieldbus Mapping Dialog help topic for more information. For more information, refer to the main A3200 Help file.") BOOL DLLENTRYDECLARATION A3200ModbusBitReadDrive(A3200Handle handle, TASKID taskId, AXISINDEX Axis, REGISTERTYPE BitName, DWORD BitNumber, DWORD* returnValue);


/// \brief Acknowledges all axis faults and clears all task errors.

/// \htmlonly This command is the same as "<a href="mk:@MSITStore:A3200.chm::/Commands/ACKNOWLEDGEALL_Command.html">ACKNOWLEDGEALL</a>" in AeroBasic.
/// \endhtmlonly
///
/// \ingroup root
///
/// \param[in] handle The handle to the controller on which to execute the command.
/// \param[in] taskId The ID of the task on which to execute the command.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
///
/// Example usage:
///
/// \dontinclude "CommandsDoc.h"
/// \skip A3200AcknowledgeAll()
/// \until A3200Disconnect
BOOL DLLENTRYDECLARATION A3200AcknowledgeAll(A3200Handle handle, TASKID taskId);



#ifdef __cplusplus
}
#endif

#endif // __A3200_AEROBASIC_COMMANDS_H__

