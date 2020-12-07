/// \file A3200Configuration.h
/// \brief Contains the function to configure the A3200.
///
/// Copyright (c) Aerotech, Inc. 2013-2018.
///

#ifndef __A3200_CONFIGURATION_H__
#define __A3200_CONFIGURATION_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup configuration Configuration Functions
/// @{

/// \brief The handle to the A3200 configuration.
typedef void* A3200ConfigurationHandle;

/// \brief The A3200ProgramAutomationFile represents a file in program automation configuration.
typedef struct {
	char programPath[MAX_PATH]; ///< The path to the program on which to operate.
	PROGRAMAUTOMATIONMODE mode; ///< What to do with the programPath.
	TASKMASK taskMask; ///< The tasks to which to apply the program.
	DWORD spare[4]; ///< Reserved for future expansion.
} A3200ProgramAutomationFile;

/// \brief The A3200CalibrationGCalFile represent a GCal calibration file in the configuration.
typedef struct {
	char filePath[MAX_PATH]; ///< The path to the GCal calibration file.
	DWORD axisIndex; ///< The index of the axis this calibration file is for.
	DWORD spare[4]; ///< Reserved for future expansion.
} A3200CalibrationGCalFile;

/// \brief Opens the current configuration.
///
/// This function opens the current configuration file and stores it in memory.  The object can then be 
/// used to configure different A3200 settings.
/// \param[out] handle A pointer to a handle for the A3200 Configuration object.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationOpen(A3200ConfigurationHandle* handle);
/// \brief Saves the configuration.
///
/// \param[in] handle A pointer to the A3200 Configuration object to save.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationSave(A3200ConfigurationHandle handle);

/// \brief Closes a configuration, releasing any memory.
///
/// This function closes and cleans up the A3200 Configuration object.  To save the configuration, call
/// A3200ConfigurationSave().
/// \param[in] handle A pointer to the A3200 Configuration object to close.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationClose(A3200ConfigurationHandle handle);

/// \brief Sets the parameter file path.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] filePath The file path of the parameter file to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationParameterFileSet(A3200ConfigurationHandle handle, char* filePath);

/// \brief Gets the parameter file path.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[out] filePath The buffer to store the file path in.
/// \param[in] filePathCount The size of filePath buffer in bytes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationParameterFileGet(A3200ConfigurationHandle handle, char* filePath, DWORD filePathCount);

/// \brief Sets the distance logging file path.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] filePath The file path of the distance logging file to use.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationDistanceLoggingFileSet(A3200ConfigurationHandle handle, char* filePath);

/// \brief Gets the distance logging file path.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[out] filePath The buffer to store the file path in.
/// \param[in] filePathCount The size of filePath buffer in bytes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationDistanceLoggingFileGet(A3200ConfigurationHandle handle, char* filePath, DWORD filePathCount);

/// \brief Set the OGM file destination.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] filePath The desired destination for an OGM file. 
/// \return TRUE on success, FALSE if an error occurred.  Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCompilerOutputDirectorySet(A3200ConfigurationHandle handle, char* filePath);

/// \brief Get the OGM file destination.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[out] filePath The buffer to store the file path in.
/// \param[in] filePathCount The size of the filePath buffer in bytes.
/// \return TRUE on success, FALSE if an error occurred.  Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCompilerOutputDirectoryGet(A3200ConfigurationHandle handle, char* filePath, DWORD filePathCount);

/// \brief Sets the calibration file path.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] type The calibration file type to set.
/// \param[in] filePath The file path.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationFileSet(A3200ConfigurationHandle handle, AXISCALIBRATION type, char* filePath);

/// \brief Gets the calibration file path.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] type The calibration file type to get.
/// \param[out] filePath The buffer to store the file path in.
/// \param[in] filePathCount The size of filePath buffer in bytes.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationFileGet(A3200ConfigurationHandle handle, AXISCALIBRATION type, char* filePath, DWORD filePathCount);

/// \brief Gets the count of entries in GCal calibration.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[out] count The number of entries in GCal calibration.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationGCalGetCount(A3200ConfigurationHandle handle, DWORD* count);

/// \brief Sets an entry in GCal calibration.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] index The index of the entry to set.
/// \param[in] entry The information to set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationGCalSet(A3200ConfigurationHandle handle, DWORD index, A3200CalibrationGCalFile entry);

/// \brief Gets an entry in GCal calibration.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] index The index of the entry to get.
/// \param[out] entry The entry information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationGCalGet(A3200ConfigurationHandle handle, DWORD index, A3200CalibrationGCalFile* entry);

/// \brief Adds an entry to GCal calibration.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] entry The entry information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationGCalAdd(A3200ConfigurationHandle handle, A3200CalibrationGCalFile entry);

/// \brief Removes an entry from GCal calibration.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] index The index of the entry to remove.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationCalibrationGCalRemove(A3200ConfigurationHandle handle, DWORD index);

/// \brief Gets the count of entries in program automation.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[out] count The number of entries in program automation.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationProgramAutomationGetCount(A3200ConfigurationHandle handle, DWORD* count);

/// \brief Sets an entry in program automation.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] index The index of the entry to set.
/// \param[in] entry The information to set.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationProgramAutomationSet(A3200ConfigurationHandle handle, DWORD index, A3200ProgramAutomationFile entry);

/// \brief Gets an entry in program automation.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] index The index of the entry to get.
/// \param[out] entry The entry information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationProgramAutomationGet(A3200ConfigurationHandle handle, DWORD index, A3200ProgramAutomationFile* entry);

/// \brief Adds an entry to program automation.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] entry The entry information.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationProgramAutomationAdd(A3200ConfigurationHandle handle, A3200ProgramAutomationFile entry);

/// \brief Removes an entry from program automation.
///
/// \param[in] handle A pointer to the A3200 Configuration object to use.
/// \param[in] index The index of the entry to remove.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200ConfigurationProgramAutomationRemove(A3200ConfigurationHandle handle, DWORD index);

/// @}

#ifdef __cplusplus
}
#endif

#endif
