/// \file A3200Commands.h
/// \brief Contains the functions to execute AeroBasic commands.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_COMMANDS_H__
#define __A3200_COMMANDS_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \ingroup root
///
/// \brief Executes an AeroBasic command in the given task.
///
/// The immediate command will be executed, and this function will wait
/// until the command is done executing. If the command string yields a value
/// (such as calling AXISSTATUS, etc.), then the returnValue can be used to
/// retrieve that value.  Multiple commands can be executed by adding newlines
/// between them.  The valued yielded by last command will be returned in returnValue.
/// Use A3200ProgramRun() to run a full AeroBasic program.
///
/// The following example shows how to get a value back from the executed code:
/// \dontinclude "Examples.chh"
/// \skip CommandExecuteReturnExample
/// \until }
///
/// \param[in] handle The handle to the A3200.
/// \param[in] taskId The task ID to execute the AeroBasic command(s) on.
/// \param[in] command The AeroBasic command(s) to execute.
/// \param[out] returnValue The return value of the command string. Pass NULL if the return value is not desired. If returnValue is not NULL and no command yielded a value an error is generated.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CommandExecute(A3200Handle handle, TASKID taskId, LPCSTR command, DOUBLE* returnValue);

/// \ingroup motion
///
/// \brief Aborts motion on given axes.
///
/// The motion on the given axes will be aborted.  This command does use
/// tasks and therefore will be executed asynchronously with regard to other commands.
/// This is an asynchronous call.  When this function returns the abort will be started, 
/// but it will not be finished.
///
/// \param[in] handle The handle to the A3200
/// \param[in] axisMask The mask of axes on which to abort motion
/// \return TRUE on success, FALSE if an error occured. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200MotionAbort(A3200Handle handle, AXISMASK axisMask);

/// \ingroup motion
///
/// \brief Waits for motion to be done on given axes.
///
/// The command will block until motion is done on given
/// axes with the given criteria, or the wait times out.
///
/// \param[in] handle The handle to the A3200
/// \param[in] axisMask The mask of axes on wait for motion to be done on
/// \param[in] waitOption Either WAITOPTION_MoveDone or WAITOPTION_InPosition
/// \param[in] timeout The timeout to wait for in milliseconds.  -1 means to wait forever, 0 means to not wait.
/// \param[out] timedOut Whether the wait timed out or not. This parameter can be NULL if the timeout information is not desired.
/// \return TRUE on success, FALSE if an error occured. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200MotionWaitForMotionDone(A3200Handle handle, AXISMASK axisMask, WAITOPTION waitOption, DWORD timeout, BOOL* timedOut);

#ifdef __cplusplus
}
#endif

#endif // __A3200_COMMANDS_H__
