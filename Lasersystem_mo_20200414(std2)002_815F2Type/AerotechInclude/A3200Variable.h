/// \file A3200Variable.h
/// \brief Contains the functions to get and set Aerobasic variables.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_VARIABLE_H__
#define __A3200_VARIABLE_H__

#include "A3200CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup variable Variable Functions
/// @{

/// \brief Retrieves the value of a global double variable
///
/// This function will retrieve the value of one of the globally allocated
/// system doubles from the Aerobasic programs.  The
/// number of variables available is defined by the GlobalDoubles system
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] variableNumber The zero-based index of the variable to get.
/// \param[out] valueOut A pointer to the double to contain the retrieved value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetGlobalDouble(A3200Handle handle, DWORD variableNumber, DOUBLE* valueOut);

/// \brief Retrieves an array of global double variables
///
/// This function will retrieve the value of a set of consecutive globally allocated
/// system doubles from the Aerobasic programs.  The
/// number of variables available is defined by the GlobalDoubles system
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] startVariableNumber The zero-based index of the first variable to get.
/// \param[out] valuesOutArray A pointer to an array of doubles to contain the retrieved values.
/// This must be of size count or greater.
/// \param[in] count The number of variables to retrieve. (startVariableNumber + count) cannot
/// exceed the defined number of GlobalDoubles available.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetGlobalDoubles(A3200Handle handle, DWORD startVariableNumber, DOUBLE* valuesOutArray, DWORD count);

/// \brief Retrieves the value of a global string variable
///
/// This function will retrieve the value of one of the globally allocated
/// system strings from the Aerobasic programs.  The
/// number of variables available is defined by the GlobalStrings system
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] variableNumber The zero-based index of the variable to get.
/// \param[out] stringValueOut A pointer to the string to contain the retrieved value.
/// \param[in] bufferSizeInBytes The allocated size of the stringValueOut string, in bytes
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetGlobalString(A3200Handle handle, DWORD variableNumber, LPSTR stringValueOut, DWORD bufferSizeInBytes);

///////////////////////////////////////////////////////////////////////////

/// \brief Sets the value of a global double variable
///
/// This function will set the value of one of the globally allocated
/// system doubles in the Aerobasic programs.  The
/// number of variables available is defined by the GlobalDoubles system
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] variableNumber The zero-based index of the variable to set.
/// \param[in] value The double value to set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetGlobalDouble(A3200Handle handle, DWORD variableNumber, DOUBLE value);

/// \brief Sets an array of global double variables
///
/// This function will set the values of a set of consecutive globally allocated
/// system doubles in the Aerobasic programs.  The
/// number of variables available is defined by the GlobalDoubles system
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] startVariableNumber The zero-based index of the first variable to set.
/// \param[in] valuesArray A pointer to an array of doubles that contain the values to set.
/// This must be of size count or greater.
/// \param[in] count The number of variables to set. (startVariableNumber + count) cannot
/// exceed the defined number of GlobalDoubles available.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetGlobalDoubles(A3200Handle handle, DWORD startVariableNumber, DOUBLE* valuesArray, DWORD count);

/// \brief Sets the value of a global string variable
///
/// This function will set the value of one of the globally allocated
/// system strings in the Aerobasic programs.  The
/// number of variables available is defined by the GlobalStrings system
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] variableNumber The zero-based index of the variable to set.
/// \param[in] stringValue The string that is to be copied to the global string.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetGlobalString(A3200Handle handle, DWORD variableNumber, LPCSTR stringValue);

///////////////////////////////////////////////////////////////////////////

/// \brief Retrieves the value of a task double variable
///
/// This function will retrieve the value of one of the task allocated
/// doubles from the Aerobasic programs.  The
/// number of variables available is defined by the TaskDoubles task
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] variableNumber The zero-based index of the variable to get
/// \param[out] valueOut A pointer to the double to contain the retrieved value
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetTaskDouble(A3200Handle handle, TASKID taskId, DWORD variableNumber, DOUBLE* valueOut);

/// \brief Retrieves an array of task double variables
///
/// This function will retrieve the value of a set of consecutive task allocated
/// doubles from the Aerobasic programs.  The
/// number of variables available is defined by the TaskDoubles task
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] startVariableNumber The zero-based index of the first variable to get
/// \param[out] valuesOutArray A pointer to an array of doubles to contain the retrieved values
/// This must be of size count or greater
/// \param[in] count The number of variables to retrieve. (startVariableNumber + count) cannot
/// exceed the defined number of TaskDoubles available.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetTaskDoubles(A3200Handle handle, TASKID taskId, DWORD startVariableNumber, DOUBLE* valuesOutArray, DWORD count);

/// \brief Retrieves the value of a task string variable
///
/// This function will retrieve the value of one of the task allocated
/// strings from the Aerobasic programs.  The
/// number of variables available is defined by the TaskStrings task
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] variableNumber The zero-based index of the variable to get
/// \param[out] stringValueOut A pointer to the string to contain the retrieved value
/// \param[in] bufferSizeInBytes The allocated size of the stringValueOut string, in bytes
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetTaskString(A3200Handle handle, TASKID taskId, DWORD variableNumber, LPSTR stringValueOut, DWORD bufferSizeInBytes);

///////////////////////////////////////////////////////////////////////////

/// \brief Sets the value of a task double variable
///
/// This function will set the value of one of the task allocated
/// doubles in the Aerobasic programs.  The
/// number of variables available is defined by the TaskDoubles task
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] variableNumber The zero-based index of the variable to set
/// \param[in] value The double value to set
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetTaskDouble(A3200Handle handle, TASKID taskId, DWORD variableNumber, DOUBLE value);

/// \brief Sets an array of task double variables
///
/// This function will set the values of a set of consecutive task allocated
/// doubles in the Aerobasic programs.  The
/// number of variables available is defined by the TaskDoubles task
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] startVariableNumber The zero-based index of the first variable to set
/// \param[in] valuesArray A pointer to an array of doubles that contain the values to set
/// This must be of size count or greater.
/// \param[in] count The number of variables to set. (startVariableNumber + count) cannot
/// exceed the defined number of TaskDoubles available.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetTaskDoubles(A3200Handle handle, TASKID taskId, DWORD startVariableNumber, DOUBLE* valuesArray, DWORD count);

/// \brief Sets the value of a task string variable
///
/// This function will set the value of one of the task allocated
/// strings in the Aerobasic programs.  The
/// number of variables available is defined by the TaskStrings task
/// parameter.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The ID of the task to select
/// \param[in] variableNumber The zero-based index of the variable to set
/// \param[in] stringValue The string that is to be copied to the task string
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetTaskString(A3200Handle handle, TASKID taskId, DWORD variableNumber, LPCSTR stringValue);

/// \brief Retrieves the value of a string variable from the controller
///
/// This function will retrieve the value of a string variable 
/// from the controller.
/// When getting task based variables, pass the respective TaskID. 
/// When getting global and fieldbus variables, pass TaskID_TLibrary.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskID The TaskID of task variables.  Pass TaskID_TLibrary for global and fieldbus variables
/// \param[in] variableName The name of the variable to retrieve
/// \param[out] value The retrieved string value of the variable
/// \param[in] bufferSizeInBytes The allocated size of the value buffer, in bytes
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetValueStringByName(A3200Handle handle, TASKID taskID, LPCSTR variableName, LPSTR value, DWORD bufferSizeInBytes);

/// \brief Sets the value of a string variable on the controller
///
/// This function will set the value of a string variable 
/// on the controller.
/// When setting task based variables, pass the respective TaskID.
/// When setting global and fieldbus variables, pass TaskID_TLibrary.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskID The TaskID of task variables.  Pass TaskID_TLibrary for global and fieldbus variables
/// \param[in] variableName The name of the variable to set
/// \param[in] value The string value of the variable to be set
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetValueStringByName(A3200Handle handle, TASKID taskID, LPCSTR variableName, LPCSTR value);

/// \brief Retrieves the value of a non-string variable from the controller
///
/// This function will retrieve the value of a non-string variable
/// from the controller.
/// When getting task based variables, pass the respective TaskID. 
/// When getting global and fieldbus variables, pass TaskID_TLibrary.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskID The TaskID of task variables.  Pass TaskID_TLibrary for global and fieldbus variables
/// \param[in] variableName The name of the variable to retrieve
/// \param[out] value The retrieved non-string value of the variable
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableGetValueByName(A3200Handle handle, TASKID taskID, LPCSTR variableName, DOUBLE* value);

/// \brief Sets the value of a non-string variable on the controller
///
/// This function will set the value of a non-string variable
/// on the controller.
/// When setting task based variables, pass the respective TaskID.
/// When setting global and fieldbus variables, pass TaskID_TLibrary.
///
/// \param[in] handle The handle to the A3200
/// \param[in] taskID The TaskID of task variables.  Pass TaskID_TLibrary for global and fieldbus variables
/// \param[in] variableName The name of the variable to set
/// \param[in] value The non-string value of the variable to be set
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200VariableSetValueByName(A3200Handle handle, TASKID taskID, LPCSTR variableName, DOUBLE value);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_STATUS_H__
