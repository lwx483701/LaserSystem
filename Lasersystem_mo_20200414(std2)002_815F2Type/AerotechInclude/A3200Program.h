/// \file A3200Program.h
/// \brief Contains the functions to execute AeroBasic commands.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_PROGRAM_H__
#define __A3200_PROGRAM_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \brief A struct that contains data about a program added to the A3200 SMC.
///
/// This struct will be populated when retrieving the list of programs currently added to the A3200 SMC.
typedef struct tagA3200AddedProgram {
	CHAR name[128]; ///< The name of the program added to the SMC.
	TASKMASK associatedTasks; ///< The tasks on which the program is currently associated.
	DWORD spare[8]; ///< Currently not used but reserved for future use.
} A3200AddedProgram;

/// \defgroup programtask Program/Task Control Functions
/// @{

/// Runs an Aerobasic program.  The given Aerobasic file will be compiled,
/// downloaded to the SMC, associated with the given task number, and then executed.
///
/// This function does not wait for the program to finish running.  Use A3200ProgramGetTaskState() to
/// check for program completion.  Use A3200CommandExecute() to run short snippets of AeroBasic code.
///
/// \param[in] handle The handle to the A3200.
/// \param[in] taskId The ID of the task to run the program on.
/// \param[in] filePath The path to the Aerobasic source file.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramRun(A3200Handle handle, TASKID taskId, LPCSTR filePath);

/// Executes the program in buffered mode on the task, use if program is too big for A3200ProgramRun().
///
/// This mode can run programs of arbitrary size and should be used only if the A3200ProgramRun()
/// cannot run a program of given size.  This mode has major limitations in terms of programming
/// language features.  If this is used the task cannot be used for anything else until the program
/// execution is done or A3200ProgramStop() is called or A3200ProgramStopAndWait() is called.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] filePath The path to the Aerobasic source file
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramBufferedRun(A3200Handle handle, TASKID taskId, LPCSTR filePath);

/// Loads an Aerobasic program.  The given Aerobasic file will be compiled,
/// downloaded to the SMC, and associated with the given task number.  The program is fully
/// loaded and ready to execute.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] filePath The path to the Aerobasic source file
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramLoad(A3200Handle handle, TASKID taskId, LPCSTR filePath);

/// Associates an Aerobasic program with a task.  The given Aerobasic program 
/// will be associated with the given task number.  The program must already
/// be downloaded to the SMC.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] programName The name of the Aerobasic program
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramAssociate(A3200Handle handle, TASKID taskId, LPCSTR programName);

/// Adds an Aerobasic program to the SMC.  The given Aerobasic file will be 
/// compiled and downloaded to the SMC.
///
/// \param[in] handle The handle to the A3200
/// \param[in] filePath The path to the Aerobasic source file
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramAdd(A3200Handle handle, LPCSTR filePath);

/// Removes an Aerobasic program from the SMC.  The given Aerobasic file will be 
/// completely removed from the SMC. The program should not be associated with
/// any tasks.
///
/// \param[in] handle The handle to the A3200
/// \param[in] programName The name of the Aerobasic program
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramRemove(A3200Handle handle, LPCSTR programName);

/// Start the execution of an Aerobasic program on a task.  The given task
/// is started, and the associated Aerobasic program is executed. An error
/// will occur if no program is associated with the task.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramStart(A3200Handle handle, TASKID taskId);

/// Stop the execution of an Aerobasic program on a task.  The given task
/// is stopped immediately, and all motion is aborted.  This function returns 
/// immediately, and does not wait for the motion to decelerate.  After the stop
/// completes, the program will be disassociated.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramStop(A3200Handle handle, TASKID taskId);

/// Stop the execution of an Aerobasic program on a task.  The given task
/// is stopped immediately, and all motion is aborted.  This function blocks
/// until the axes have decelerated to a stop.  After the stop
/// completes, the program will be disassociated.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] msTimeOut The maximum time in milliseconds to wait before timing out
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramStopAndWait(A3200Handle handle, TASKID taskId, DWORD msTimeOut);

/// Pauses the execution of an Aerobasic program on a task.  The program on 
/// the given task will complete the currently executing line, and pause
/// before starting the next line.  This function returns immediately, and
/// does not wait for the line to complete its execution.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramPause(A3200Handle handle, TASKID taskId);

/// Pauses the execution of an Aerobasic program on a task.  The program on 
/// the given task will complete the currently executing line, and pause
/// before starting the next line.  This function blocks until the current
/// line execution has completed.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] msTimeOut The maximum time in milliseconds to wait before timing out
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramPauseAndWait(A3200Handle handle, TASKID taskId, DWORD msTimeOut);

/// Steps into one line of an Aerobasic program on a task.  The program currently associated with 
/// the given task will step into one line, and executes without regard to the 
/// current execution mode.  If the program is currently executing, then this
/// command has no effect.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramStepInto(A3200Handle handle, TASKID taskId);

/// Steps over one line of an Aerobasic program on a task.  The program currently associated with 
/// the given task will step over one line, and executes without regard to the 
/// current execution mode.  If the program is currently executing, then this
/// command has no effect.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramStepOver(A3200Handle handle, TASKID taskId);

/// Turns Retrace on or off on the given task. This is used to enable or disable
/// retrace mode on the given task. If the task is executing when this command is
/// issued, the program will be paused. The task can be resumed with A3200ProgramStart().
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] onOff ON to enable Retrace, OFF to disable
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramRetrace(A3200Handle handle, TASKID taskId, ONOFF onOff);

/// Gets the state of the given task. This function retrieves the execution state
/// of the given task. Refer to the TASKSTATE defines in A3200CommonStructures.h.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[out] taskState The retrieved state of the task
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramGetTaskState(A3200Handle handle, TASKID taskId, TASKSTATE* taskState);

/// Gets the state of the given task as a string. This function retrieves the execution state
/// of the given task and formats it into a human-readable string.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The zero-based index of the program task.
/// \param[out] nameString The retrieved name of the current execution state.
/// \param[in] stringBufferSizeBytes The allocated size of the nameString buffer.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramGetTaskStateString(A3200Handle handle, TASKID taskId, LPSTR nameString, ULONG stringBufferSizeBytes);

/// Puts the given task into the feedhold state.  The program currently associated with 
/// the given task will pause its execution, and the motion will be feedheld.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The zero-based index of the program task.
/// \param[in] feedholdEnabled Passing TRUE as the argument feedholds the task; FALSE releases the task.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramFeedhold(A3200Handle handle, TASKID taskId, BOOL feedholdEnabled);

/// Sets the program line number to a specific line.
/// 
/// The task will be in a TASKSTATE_ProgramPaused state after this function is called.
/// You do not need to call this function if you want the program to start from the beginning because
/// when a you call A3200ProgramLoad() the program starts on the first executable line.
/// It is not always safe to set the line number to an arbitrary line.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The zero-based index of the program task.
/// \param[in] lineNumber The one-based index of the line to be active.
BOOL DLLENTRYDECLARATION A3200ProgramSetLineNumber(A3200Handle handle, TASKID taskId, DWORD lineNumber);

/// \brief Initialize the queue on a task.
///
/// This function will determine the mode in which commands are executed on the task.
/// When Queue mode is enabled, consecutive commands are able to be quickly executed
/// by the system. When Queue mode is disabled, commands are executed one at a time.
/// To change the task to not execute commands in queue, call A3200ProgramStop() or
/// A3200ProgramStopAndWait().
///
/// The following example shows how to use a task's Queue mode.
/// \dontinclude "Examples.chh"
/// \skip InitializeQueue
/// \until A3200Disconnect
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramInitializeQueue(A3200Handle handle, TASKID taskId);

/// \brief Retrieves the number of programs that have been added to the A3200 SMC.
///
/// This function retrieves the number of programs that have been added to the A3200 SMC. An "added" program is a program that has been transferred to the SMC (and is resident in memory) but is not necessarily associated with a task.
///
/// \param[in] handle The handle to the A3200
/// \param[out] count The number of programs added to the SMC
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ProgramGetAddedProgramCount(A3200Handle handle, DWORD *count);

/// \brief Retrieves the list of programs currently added to the A3200 SMC.
///
/// This function retrieves a list of programs that are currently added to the A3200 SMC. An "added" program is a program that has been transferred to the SMC (and is resident in memory) but is not necessarily associated with a task.
///
/// \param[in] handle The handle to the A3200
/// \param[out] results The list of added programs.
/// \param[in] resultsCount The number of programs to retrieve. This value must match the number of elements in the array passed in the "results" parameter.
BOOL DLLENTRYDECLARATION A3200ProgramGetAddedPrograms(A3200Handle handle, A3200AddedProgram *results, DWORD resultsCount);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_PROGRAM_H__
