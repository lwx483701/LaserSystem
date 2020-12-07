/// \file A3200Connection.h
/// \brief Contains the functions to establish control over A3200.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_CONNECTION_H__
#define __A3200_CONNECTION_H__

#include "A3200CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup connection Connection Functions
/// @{

/// \brief Connects to the A3200.
///
/// This function will either connect to an already running A3200, or
/// will initialize an A3200 if it is not already running.
/// In either case, the handle to a running A3200 will be returned.
/// Initialization involves sending parameters, calibration files, program automation, 
/// and other things.
///
/// To release this handle call A3200Disconnect()
///
/// \param[out] handle The handle to the A3200
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200Connect(A3200Handle* handle);

/// \brief Disconnects from the A3200.
///
/// This disconnects from the A3200.  The A3200 will keep running 
/// after this call.
///
/// \param[in] handle The handle to the A3200
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200Disconnect(A3200Handle handle);

/// \brief Resets the A3200.
///
/// This resets the A3200 system.  Calibration, program automation, etc.
/// will be reinitialized after this call.
///
/// \param[in] handle The handle to the A3200
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200Reset(A3200Handle handle);

/// \brief Checks if the A3200 system is initialized.
///
/// This checks to see if the A3200 system has been fully initialized.
/// If the system is not initialized, a call to A3200Connect() will perform
/// the initialization.
///
/// \param[out] isInitialized Set to TRUE if system is fully initialized,
/// FALSE if it is not.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200IsInitialized(BOOL* isInitialized);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_CONNECTION_H__
