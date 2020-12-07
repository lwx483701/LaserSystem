/// \file A3200Parameter.h
/// \brief Contains the functions to retrieve and send parameters from or to the SMC.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_PARAMETER_H__
#define __A3200_PARAMETER_H__

#include "A3200CommonTypes.h"
#include "A3200ParameterId.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup parameter Parameter Functions
/// @{

/// \brief Retrieves the value of a double parameter from the SMC.
///
/// This function will retrieve the value of one of the double type parameters to a double variable. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] parameterId The ID number of the parameter.
/// \param[in] index The index of axis or task. Ignored for system parameters.
/// \param[out] value The retrieved double value of the parameter.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterGetValue(A3200Handle handle, PARAMETERID parameterId, DWORD index, DOUBLE* value);

/// \brief Retrieves the value of a string parameter from the SMC.
///
/// This function will retrieve the value of one of the string type parameters to a string variable. 
///
/// Retrieve a string value of a parameter from te SMC.
///
/// \param[in] handle The handle to the A3200
/// \param[in] parameterId The ID number of the parameter.
/// \param[in] index The index of axis or task. Ignored for system parameters.
/// \param[in] size The number of characters to be retrieved
/// \param[out] value The retrieved string value of the parameter.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterGetValueString(A3200Handle handle, PARAMETERID parameterId, DWORD index, ULONG size, LPSTR value);

/// \brief Sets the value of a double parameter on the SMC.
///
/// This function will send the value of one of the double type parameters to the SMC. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] parameterId The ID number of the parameter.
/// \param[in] index The index of axis or task. Ignored for system parameters.
/// \param[in] value The double value of the parameter to be sent.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterSetValue(A3200Handle handle, PARAMETERID parameterId, DWORD index, DOUBLE value);

/// \brief Sends the value of a string parameter to the SMC.
///
/// This function will send the value of one of the string type parameters to the SMC. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] parameterId The ID number of the parameter.
/// \param[in] index The index of axis or task. Ignored for system parameters.
/// \param[in] value The string value of the parameter to be sent.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterSetValueString(A3200Handle handle, PARAMETERID parameterId, DWORD index, LPCSTR value);

/// \brief Gets the default parameter file.
///
/// This function will return a handle to the default parameter file.
///
/// \param[out] paramFile The handle to the parameter file.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileGetDefaults(A3200ParameterFile *paramFile);

/// \brief Opens the parameter file.
///
/// This function will open the given parameter file and return a handle to it.
///
/// \param[in] fileName The path to the parameter file.
/// \param[out] paramFile The handle to the parameter file.
/// \return TRUE on success, FALSE if an error occurred.  Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileOpen(LPCSTR fileName, A3200ParameterFile *paramFile);

/// \brief Closes the parameter file.
///
/// This function will close the given parameter file and free the memory allocated to it.
///
/// \param[in] paramFile The handle to the parameter file.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileClose(A3200ParameterFile paramFile);

/// \brief Saves the parameter file.
///
/// This function will save the given parameter file.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] fileName The path the parameter file will be saved to.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileSave(A3200ParameterFile paramFile, LPCSTR fileName);

/// \brief Retrieves the value of a string parameter from the parameter file.
///
/// This function will retrieve the value of one of the string type parameters to a string variable. 
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] parameterID The ID number of the parameter.
/// \param[in] index The index of axis or task. Pass 0 for system parameter.
/// \param[out] value The retrieved string value of the parameter.
/// \param[in] valueSize The size of the value buffer.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileGetValueString(A3200ParameterFile paramFile, PARAMETERID parameterID, DWORD index, LPSTR value, DWORD valueSize);

/// \brief Gets the value of a double parameter from the parameter file.
///
/// This function will get the value of one of the double type parameters to a double variable. 
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] parameterID The ID number of the parameter.
/// \param[in] index The index of axis or task. Pass 0 for system parameter.
/// \param[out] value The retrieved double value of the parameter.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileGetValue(A3200ParameterFile paramFile, PARAMETERID parameterID, DWORD index, DOUBLE* value);


/// \brief Sends the value of a string parameter to the parameter file.
///
/// This function will send the value of one of the string type parameters to the parameter file.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] parameterID The ID number of the parameter.
/// \param[in] index The index of axis or task. Pass 0 for system parameter.
/// \param[in] value The string value of the parameter to be set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileSetValueString(A3200ParameterFile paramFile, PARAMETERID parameterID, DWORD index, LPCSTR value);

/// \brief Sets the value of a double parameter to the parameter file.
///
/// This function will send the value of one of the double type parameters to the parameter file.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] parameterID The ID number of the parameter.
/// \param[in] index The index of axis or task. Pass 0 for system parameter.
/// \param[in] value The double value of the parameter to be set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileSetValue(A3200ParameterFile paramFile, PARAMETERID parameterID, DWORD index, DOUBLE value);

/// \brief Provides access to the user-customizable tag in the configuration file.
///
/// This function provides gets the user-customizable tag in the configuration file so users can store additional data that is not a parameter value.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] section The section of the user data to retrieve.
/// \param[out] data A buffer containing the user data section of the parameter file. Contains the outer node.
/// \param[in] dataSize The size of the buffer for the user data.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileGetData(A3200ParameterFile paramFile, LPCSTR section, LPSTR data, DWORD dataSize);

/// \brief Provides access to the user-customizable tag in the configuration file.
///
/// This function provides sets the user-customizable tag in the configuration file so users can store additional data that is not a parameter value.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] data The data to set. Should contain the outer node.  Ex. If you wish to set the element \<foo\> to 8, pass "<foo>8</foo>".
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileSetData(A3200ParameterFile paramFile, LPCSTR data);

/// \brief Gets the existing axis mask from the parameter file.
///
/// This function gets the existing axis mask from the parameter file.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[out] axisMask The retrieved axis mask.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileGetAxisMask(A3200ParameterFile paramFile, AXISMASK *axisMask);

/// \brief Sets the existing axis mask in the parameter file.
///
/// This function sets the existing axis mask in the parameter file.
///
/// \param[in] paramFile The handle to the parameter file.
/// \param[in] axisMask The axis mask to be set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterFileSetAxisMask(A3200ParameterFile paramFile, AXISMASK axisMask);

/// \brief Retrieves the parameters and places them in the specified file.
///
/// This function retrieves the parameters from a specified controller and places them in a designated file. To create a default parameter file to pass to this function, see A3200ParameterFileGetDefaults.
/// \param[in] handle The controller to retrieve the parameters from.
/// \param[in,out] parameterFile The already initialized file to place the parameters in.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ParameterRetrieveFromController(A3200Handle handle, A3200ParameterFile parameterFile);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_PARAMETER_H__
