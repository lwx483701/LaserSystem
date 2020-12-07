/// \file A3200Status.h
/// \brief Contains the functions to obtain A3200 status information.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_STATUS_H__
#define __A3200_STATUS_H__

#include "A3200CommonTypes.h"
#include "A3200StatusItemInfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup status Status Commands
/// @{

/// \brief Retrieves multiple status items from the A3200.
///
/// This function will retrieve an array of status items. Provide
/// the item codes to collect, corresponding axes or tasks, and optional
/// extra data.  This function works similarly to the AXISSTATUS,
/// TASKSTATUS, and SYSTEMSTATUS AeroBasic functions.
///
/// The following example shows how to get multiple status values of different kind at once:
/// \dontinclude "Examples.chh"
/// \skip StatusItemsExample
/// \until }
/// \until }
/// \until }
/// \until }
///
/// \param[in] handle The handle to the A3200
/// \param[in] numberOfItems The number of items to retrieve.  The size
/// of the array arguments must be greater than or equal to this number.
/// \param[in] itemIndexArray An array of indices to specify which
/// axis, task, or channel index this status item is retrieved from.
/// \param[in] itemCodeArray An array of the item codes to retrieve.
/// \param[in] itemExtrasArray An array of additional data that may be
/// required by some item codes.
/// \param[out] itemValuesArray An array to contain the data retrieved.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200StatusGetItems(A3200Handle handle, DWORD numberOfItems, PWORD itemIndexArray, STATUSITEM* itemCodeArray, PDWORD itemExtrasArray, DOUBLE* itemValuesArray);

/// \brief Retrieves a single status item from the A3200.
///
/// This function will retrieve the specified status item. Provide
/// the item code to collect, corresponding axis or task, and optional
/// extra data.  This function works similarly to the AXISSTATUS,
/// TASKSTATUS, and SYSTEMSTATUS AeroBasic functions.
///
/// \param[in] handle The handle to the A3200
/// \param[in] itemIndex An index to specify which
/// axis, task, or channel index this status item is retrieved from.
/// \param[in] itemCode The item code to retrieve.
/// \param[in] itemExtra Additional data that may be required by some item codes.
/// \param[out] itemValue A pointer to a double to contain the retrieved value.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200StatusGetItem(A3200Handle handle, WORD itemIndex, STATUSITEM itemCode, DWORD itemExtra, DOUBLE* itemValue);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_STATUS_H__
