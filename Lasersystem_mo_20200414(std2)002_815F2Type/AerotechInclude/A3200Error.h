/// \file A3200Error.h
/// \brief Contains the functions to handle internal errors.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_ERROR_H__
#define __A3200_ERROR_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup error Error-Reporting Functions
/// @{

/// The BuildResult structure is used to return error/warning information output during the program build process
typedef struct tagBuildResult {
  CHAR filePath[MAX_PATH+1]; ///< The file path that corresponds to this result (most likely a source file)
  DWORD lineNumber; ///< The line number that corresponds to this result
  BUILDRESULTKIND kind; ///< The result kind (warning, error, etc.)
  CHAR message[512]; ///< The result text (textual description of a syntax error, etc.)
  DWORD spare[8]; ///< Reserved for future use
} BuildResult;

/// \brief Retrieves the last error that occurred
///
/// This function will retrieve the last error that was returned from
/// an A3200 system call.
///
/// \return The ErrorData structure containing the last recorded error.
ErrorData DLLENTRYDECLARATION A3200GetLastError();

/// \brief Retrieves the last error that occurred
///
/// This function will retrieve the last error that was returned from
/// an A3200 system call, and convert it to a human-readable string message.
///
/// \param[out] errorString A pointer to the string buffer to fill with the error message.
/// \param[in] bufferSizeInBytes The allocated size of the errorString buffer, in bytes.
/// \return TRUE on success, FALSE on failure. Failure indicates that the buffer size is too small.
BOOL DLLENTRYDECLARATION A3200GetLastErrorString(LPSTR errorString, DWORD bufferSizeInBytes);

/// \brief Retrieves the number of build results for the previous compile (program or command).
///
/// \param[in] handle The handle used for the previous compile
/// \param[out] count The number of errors/warnings that occurred during file compilation
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200GetLastBuildResultCount(A3200Handle handle, DWORD* count);

/// \brief Retrieves build result information for the previous compile (program or command).
///
/// \param[in] handle The handle used for the previous compile
/// \param[in] results A user-allocated buffer that build errors/warnings will be written to
/// \param[in] resultsCount The number of BuildResult elements the results buffer can store
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200GetLastBuildResults(A3200Handle handle, BuildResult* results, DWORD resultsCount);

/// \brief Retrieves the string representation of a task error.
///
/// This function will retrieve the task error of a task and return the string representation.
///
/// \param[in] handle The handle to the controller.
/// \param[in] taskId The id of the task for which to get the error string.
/// \param[out] errorString A pointer to the string buffer to fill with the error message.
/// \param[in] bufferSizeInBytes The allocated size of the errorString buffer, in bytes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200GetTaskErrorString(A3200Handle handle, TASKID taskId, LPSTR errorString, DWORD bufferSizeInBytes);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_ERROR_H__
