/// \file A3200DataCollection.h
/// \brief Contains the functions to handle data collection.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_DATACOLLECTION_H__
#define __A3200_DATACOLLECTION_H__

#include "A3200CommonTypes.h"
#include "A3200DataCollectionInfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup datacollection Data Collection Functions
/// @{

/// \brief Data collection status struct.
///
/// This struct will be filled when checking data collection status. 
typedef struct {
	DATACOLLECTIONFLAGS     dataCollectionStatus;   ///< The status code, defined in A3200CommonStructures.h
	DWORD                   samplePointAllocated;   ///< The number of sample points per signal requested
	DWORD                   samplePointCollected;   ///< The number of sample points per signal collected
	DWORD                   samplePointRetrieved;   ///< The number of sample points per signal retrieved
	DWORD                   placeHolder[4];         ///< Reserved for future expansion
} A3200_DATACOLLECTION_STATUS;

/// \brief Creates a new data collection configuration.
///
/// This function creates a new data collection configuration object. 
/// Initial collection period is 1 msec.
///
/// \param[in] handle The handle to the A3200
/// \param[out] DCCHandle The handle to an A3200 Data Collection Configuration object
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigCreate(A3200Handle handle, A3200DataCollectConfigHandle *DCCHandle);

/// \brief Frees the data collection configuration.
///
/// This function frees memory of a data collection configuration object. 
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigFree(A3200DataCollectConfigHandle DCCHandle);

/// \brief Sets the number of sample points to collect per signal.
///
/// This function sets number of points per signal to collect. 
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object
/// \param[in] numberOfPoints The number of sample points per signal to collect
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigSetSamples(A3200DataCollectConfigHandle DCCHandle, DWORD numberOfPoints);

/// \brief Sets how frequently a sample point will be collect on each signal.
///
/// This function sets the time period between two consecutive sample points of point per signal to collect. 
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object
/// \param[in] collectionPeriod The time period between two samples in msec
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigSetPeriod(A3200DataCollectConfigHandle DCCHandle, DOUBLE collectionPeriod);

/// \brief Sets the condition for when a sample point will be collected on each signal.
///
/// This function configures the condition that has to be met for a sample point to be collected.
/// The condition is monitored at 1 msec.  This mode is mutually exclusive with A3200DataCollectionConfigSetPeriod().
///
/// The following example shows how to sample data on a rising edge of a digital input:
/// \dontinclude "Examples.chh"
/// \skip DataCollectionSampleTrigger
/// \until A3200Disconnect
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object.
/// \param[in] dataItem The item to monitor for changes.
/// \param[in] itemIndex The index of axis, task, or card on which to monitor the signal.
/// \param[in] additionalInformation Other argument for the signal to monitor. See topic "DATACOLLECT ITEM Command" in the A3200 Help.
/// \param[in] condition The condition to meet for the sample to be collected.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigSetSampleTrigger(A3200DataCollectConfigHandle DCCHandle, STATUSITEM dataItem, WORD itemIndex, DWORD additionalInformation, DATACOLLECTIONSAMPLETRIGGER condition);

/// \brief Adds a signal at the end of the configuration.
///
/// This function adds a signal to the end in the data collection configuration. 
/// Refer to topic "DATACOLLECT ITEM" in the A3200 Help for signal category, index, name, and additional.
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object.
/// \param[in] signal The name of the signal. Defined in A3200DataCollectionInfo.h as DATASIGNAL_xxxx
/// \param[in] itemIndex The index of axis, task, or card on which the signal to be collected.
/// \param[in] additionalInformation Other argument for the signal. See topic "DATACOLLECT ITEM Command" in the A3200 Help.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigAddSignal(A3200DataCollectConfigHandle DCCHandle, DATASIGNAL signal, WORD itemIndex, DWORD additionalInformation);

/// \brief Retrieves the number of signals added to a data collection configuration.
///
/// This function retrieves the number of signals added to a data collection configuration.
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object.
/// \param[out] signalCount The number of signals currently added to the data collection configuration.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigGetSignalCount(A3200DataCollectConfigHandle DCCHandle, WORD* signalCount); 

/// \brief Removes all signals from configuration.
///
/// This function will remove all existing signals in the data collection configuration. 
/// The configuration will become invalid.
///
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigRemoveSignalAll(A3200DataCollectConfigHandle DCCHandle);

/// \brief Applies data collection configuration to the A3200.
///
/// This function will send a data collection configuration to the A3200. 
///
/// \param[in] handle The handle to the A3200
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionConfigApply(A3200Handle handle, A3200DataCollectConfigHandle DCCHandle);

/// \brief Starts data collection immediately.
///
/// This function will send a data collection configuration to the A3200 and start data collection immediately. 
///
/// The following example shows how to collect data and retrieve it in chunks of 512 points:
/// \dontinclude "Examples.chh"
/// \skip DataCollectionNonContinuous
/// \until A3200Disconnect
///
/// \param[in] handle The handle to the A3200.
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object. If NULL, previous sent configuration will be used.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionStart(A3200Handle handle, A3200DataCollectConfigHandle DCCHandle);

/// \brief Starts data collection immediately in continuous mode.
///
/// This function will send a data collection configuration to the A3200 and start data collection immediately. 
/// Data collection will continue until A3200DataCollectionStop is called.  Data can be retrieved before
/// the buffer is fully filled.
///
/// The following example shows how to collect data continuously and retrieve it in chunks of 512 points:
/// \dontinclude "Examples.chh"
/// \skip DataCollectionContinuous
/// \until A3200Disconnect
///
/// \param[in] handle The handle to the A3200.
/// \param[in] DCCHandle The handle to an A3200 Data Collection Configuration object. If NULL, previous sent configuration will be used.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionStartContinuous(A3200Handle handle, A3200DataCollectConfigHandle DCCHandle);

/// \brief Aborts data collection.
///
/// This function will abort data collection. 
///
/// \param[in] handle The handle to the A3200
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionStop(A3200Handle handle);

/// \brief Retrieves data collection status.
///
/// This function will retrieve data collection status. 
///
/// \param[in] handle The handle to the A3200
/// \param[out] status The status code, point allocated and collected
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionGetStatus(A3200Handle handle, A3200_DATACOLLECTION_STATUS *status); 

/// \brief Retrieves all sample points from the A3200.
///
/// This function will retrieve all the sample points from the A3200. 
/// Caller must declare data[numberOfSignals][numberOfSamples] to match the number of signals and samples in the configuration
/// Use (DOUBLE *)data or &data[0][0] when passing data to this function.
///
/// In normal mode, calling this function several times will result in the same data being returned.  In continuous mode, calling 
/// this function several times will result in subsequent data to be returned.
///
/// \param[in] handle The handle to the A3200.
/// \param[in] signalCount The number of signals currently in the data collection configuration. Must match what is in the configuration.
/// \param[in] sampleCount The number of sample points per signal to retrieve.
/// \param[out] data The retrieved sample point in format data[signal][sample].
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200DataCollectionDataRetrieve(A3200Handle handle, WORD signalCount, DWORD sampleCount, DOUBLE *data);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_DATACOLLECTION_H__
