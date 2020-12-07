/// \file A3200Information.h
/// \brief  Contains the functions to get information about the A3200.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_INFORMATION_H__
#define __A3200_INFORMATION_H__

#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup information Controller Information Functions
/// @{

/// The Version structure is used to hold information about the version of a particular component
typedef struct tagVersion {
	DWORD major; ///< The major version number
	DWORD minor; ///< The minor version number
	DWORD patch; ///< The patch number
	DWORD build; ///< The build number
	DWORD spare[4]; ///< Reserved for future expansion
} Version;

/// \brief Retrieves the version information of the C library.
///
/// \param[out] pVersion A pointer to a Version struct to be populated with the version information of the C library.
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200InformationGetLibraryVersion(Version* pVersion);

/// @}

#ifdef __cplusplus
}
#endif

#endif
