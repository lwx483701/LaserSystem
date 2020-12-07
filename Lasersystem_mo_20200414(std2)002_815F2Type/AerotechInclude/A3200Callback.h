/// \file A3200Callback.h
/// \brief Contains the functions to handle Callbacks.
///
/// \dontinclude "Examples.chh"
/// \skip CustomCallbackExample
/// \until }
/// \until }
/// \until }
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_CALLBACK_H__
#define __A3200_CALLBACK_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup genericcallback Generic Callback Functions
/// @{

/// \brief Registers a callback on task.
///
/// This function registers a callback on a task. A single A3200Handle can be used to register for up to 63 callbacks (including message callbacks).
/// If you wish to register for more than 63 callbacks, then you will need to open several A3200Handles by calling A3200Connect() multiple times and register for all desired callbacks on multiple A3200Handles.
/// In addition, callback numbers are expected to be in the range of 0-999. Registering for a callback number outside of this range may interfere with the operation of built-in callback commands such as FILEREAD, SCOPEOPEN, etc.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID
/// \param[in] callbackNumber Callback ID
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackRegistrationAdd(A3200Handle handle, TASKID taskId, DWORD callbackNumber);

/// \brief Unregisters a callback from task.
///
/// This function unregisters a callback from a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID
/// \param[in] callbackNumber Callback ID
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackRegistrationRemove(A3200Handle handle, TASKID taskId, DWORD callbackNumber);

/// \brief Waits for a callback from task.
///
/// This function waits for a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[out] taskId Task ID of the callback is on
/// \param[out] callbackNumber Callback ID of the callback
/// \param[in] timeout Timeout in milliseconds. Specifying INFINITE (-1) will cause the function to wait forever.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackWait(A3200Handle handle, TASKID* taskId, DWORD* callbackNumber, DWORD timeout);

/// \brief Cancels waiting for callback.
///
/// This function cancels the wait for all callbacks. 
///
/// \param[in] handle The handle to the A3200
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackWaitCancel(A3200Handle handle);


/// \brief Gets the number of arguments of a callback on task.
///
/// This function gets the number of arguments of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID the callback is on
/// \param[out] count Number of arguments of the callback
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackArgsGetCount(A3200Handle handle, TASKID taskId, DWORD* count);

/// \brief Gets the type of an argument of a callback on task.
///
/// This function gets the argument type of a callback on a task.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] argNumber Argument ID
/// \param[out] type Type of the argument
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackArgsGetType(A3200Handle handle, TASKID taskId, DWORD argNumber, CALLBACKARGUMENTTYPE* type);

/// \brief Gets the integer value of an argument of a callback on task.
///
/// This function gets the value of an integer argument of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] argNumber Argument ID
/// \param[out] value Value of the integer argument
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackArgsGetInteger(A3200Handle handle, TASKID taskId, DWORD argNumber, INT* value);

/// \brief Gets the double value of an argument of a callback on task.
///
/// This function gets the value of a double argument of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on.
/// \param[in] argNumber Argument ID.
/// \param[out] value Value of the double argument.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackArgsGetDouble(A3200Handle handle, TASKID taskId, DWORD argNumber, DOUBLE* value);

/// \brief Gets the string value of an argument of a callback on task.
///
/// This function gets the value of a string argument of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] argNumber Argument ID
/// \param[out] value Value of the string argument
/// \param[in] maxStringSize Maximum string size
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackArgsGetString(A3200Handle handle, TASKID taskId, DWORD argNumber, LPSTR value, DWORD maxStringSize);


/// \brief Sets the task error and info variables of a callback on task with no return value.
///
/// This function does not return a value to the caller but instead sets the task error and info variables of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] taskError Task Error Data
/// \param[in] infoVar0 Error code info variable
/// \param[in] infoVar1 Error location info variable
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackReturnVoid(A3200Handle handle, TASKID taskId, ErrorData taskError, DOUBLE infoVar0, DOUBLE infoVar1);

/// \brief Sets a double value to be returned and sets task error and info variables of a callback on task.
///
/// This function returns a double value to the caller and sets the task error and info variables of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] returnValue The double value to be returned to caller
/// \param[in] taskError Task Error Data
/// \param[in] infoVar0 Error code info variable
/// \param[in] infoVar1 Error location info variable
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackReturnDouble(A3200Handle handle, TASKID taskId, DOUBLE returnValue, ErrorData taskError, DOUBLE infoVar0, DOUBLE infoVar1);

/// \brief Sets a string value to be returned and sets task error and info variables of a callback on task.
///
/// This function returns a string value to the caller and set the task error and info variables of a callback on a task. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] returnValue The string value to be returned to caller
/// \param[in] taskError Task Error Data
/// \param[in] infoVar0 Error code info variable
/// \param[in] infoVar1 Error location info variable
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackReturnString(A3200Handle handle, TASKID taskId, LPCSTR returnValue, ErrorData taskError, DOUBLE infoVar0, DOUBLE infoVar1);


/// \brief Constructs a string of the callback arguments.
///
/// This function constructs a string of callback arguments from the given first argument ID to the last one. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId Task ID of the callback is on
/// \param[in] argNumber The first argument to be in the string
/// \param[out] string The result text string
/// \param[in] maxStringSize Size of the string buffer
/// \param[in] flags A value of 1 specifies padding between each argument with a space; 0 specifies no padding.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackArgsMakeString(A3200Handle handle, TASKID taskId, DWORD argNumber, LPSTR string, DWORD maxStringSize, DWORD flags);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_CALLBACK_H__
