/// \file A3200CommonTypes.h
/// \brief Contains some common types that are used throughout the library.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_COMMONTYPES_H__
#define __A3200_COMMONTYPES_H__

#include <wtypes.h>
#include "A3200ErrorCode.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \brief The handle to the A3200.
///
/// This is used to communicate with an A3200.  You can
/// get one by calling A3200Connect().
typedef void* A3200Handle;

/// \brief The handle to an A3200 parameter file.
///
/// This is used to communicate with an A3200 parameter file.
/// You can get one by calling A3200ParameterFileGetDefault()
/// or by connecting to a stored file with A3200ParameterFileOpen()
typedef void* A3200ParameterFile;

/// \brief The handle to the A3200 Data Collection Configuration.
///
/// This is used to hold the A3200 Data Collection Configuration.
/// See A3200DataCollectionConfigCreate() for initialization details.
typedef void* A3200DataCollectConfigHandle;

/// \brief All available tasks to run commands or programs on.
///
typedef enum
{
	TASKID_Library = 0,
	TASKID_01 = 1,
	TASKID_02 = 2,
	TASKID_03 = 3,
	TASKID_04 = 4,
	TASKID_05 = 5,
	TASKID_06 = 6,
	TASKID_07 = 7,
	TASKID_08 = 8,
	TASKID_09 = 9,
	TASKID_10 = 10,
	TASKID_11 = 11,
	TASKID_12 = 12,
	TASKID_13 = 13,
	TASKID_14 = 14,
	TASKID_15 = 15,
	TASKID_16 = 16,
	TASKID_17 = 17,
	TASKID_18 = 18,
	TASKID_19 = 19,
	TASKID_20 = 20,
	TASKID_21 = 21,
	TASKID_22 = 22,
	TASKID_23 = 23,
	TASKID_24 = 24,
	TASKID_25 = 25,
	TASKID_26 = 26,
	TASKID_27 = 27,
	TASKID_28 = 28,
	TASKID_29 = 29,
	TASKID_30 = 30,
	TASKID_31 = 31,
} TASKID;

/// \brief All available axis indexes.
typedef enum
{
	AXISINDEX_00 =  0,
	AXISINDEX_01 =  1,
	AXISINDEX_02 =  2,
	AXISINDEX_03 =  3,
	AXISINDEX_04 =  4,
	AXISINDEX_05 =  5,
	AXISINDEX_06 =  6,
	AXISINDEX_07 =  7,
	AXISINDEX_08 =  8,
	AXISINDEX_09 =  9,

	AXISINDEX_10 = 10,
	AXISINDEX_11 = 11,
	AXISINDEX_12 = 12,
	AXISINDEX_13 = 13,
	AXISINDEX_14 = 14,
	AXISINDEX_15 = 15,
	AXISINDEX_16 = 16,
	AXISINDEX_17 = 17,
	AXISINDEX_18 = 18,
	AXISINDEX_19 = 19,

	AXISINDEX_20 = 20,
	AXISINDEX_21 = 21,
	AXISINDEX_22 = 22,
	AXISINDEX_23 = 23,
	AXISINDEX_24 = 24,
	AXISINDEX_25 = 25,
	AXISINDEX_26 = 26,
	AXISINDEX_27 = 27,
	AXISINDEX_28 = 28,
	AXISINDEX_29 = 29,

	AXISINDEX_30 = 30,
	AXISINDEX_31 = 31,
} AXISINDEX;

/// \brief All available axis masks.
typedef enum
{
	/// \brief No axes selected.
	AXISMASK_None = 0,

	AXISMASK_00 = (1 <<  0),
	AXISMASK_01 = (1 <<  1),
	AXISMASK_02 = (1 <<  2),
	AXISMASK_03 = (1 <<  3),
	AXISMASK_04 = (1 <<  4),
	AXISMASK_05 = (1 <<  5),
	AXISMASK_06 = (1 <<  6),
	AXISMASK_07 = (1 <<  7),
	AXISMASK_08 = (1 <<  8),
	AXISMASK_09 = (1 <<  9),

	AXISMASK_10 = (1 << 10),
	AXISMASK_11 = (1 << 11),
	AXISMASK_12 = (1 << 12),
	AXISMASK_13 = (1 << 13),
	AXISMASK_14 = (1 << 14),
	AXISMASK_15 = (1 << 15),
	AXISMASK_16 = (1 << 16),
	AXISMASK_17 = (1 << 17),
	AXISMASK_18 = (1 << 18),
	AXISMASK_19 = (1 << 19),

	AXISMASK_20 = (1 << 20),
	AXISMASK_21 = (1 << 21),
	AXISMASK_22 = (1 << 22),
	AXISMASK_23 = (1 << 23),
	AXISMASK_24 = (1 << 24),
	AXISMASK_25 = (1 << 25),
	AXISMASK_26 = (1 << 26),
	AXISMASK_27 = (1 << 27),
	AXISMASK_28 = (1 << 28),
	AXISMASK_29 = (1 << 29),

	AXISMASK_30 = (1 << 30),
	AXISMASK_31 = (1 << 31),

	/// \brief Maximum number of axes selected.
	AXISMASK_All = 0xffffffff,
} AXISMASK;

/// \brief All available task masks.
typedef enum
{
	/// \brief No tasks selected.
	TASKMASK_None = 0,

	TASKMASK_00 = (1 <<  0),
	TASKMASK_01 = (1 <<  1),
	TASKMASK_02 = (1 <<  2),
	TASKMASK_03 = (1 <<  3),
	TASKMASK_04 = (1 <<  4),
	TASKMASK_05 = (1 <<  5),
	TASKMASK_06 = (1 <<  6),
	TASKMASK_07 = (1 <<  7),
	TASKMASK_08 = (1 <<  8),
	TASKMASK_09 = (1 <<  9),

	TASKMASK_10 = (1 << 10),
	TASKMASK_11 = (1 << 11),
	TASKMASK_12 = (1 << 12),
	TASKMASK_13 = (1 << 13),
	TASKMASK_14 = (1 << 14),
	TASKMASK_15 = (1 << 15),
	TASKMASK_16 = (1 << 16),
	TASKMASK_17 = (1 << 17),
	TASKMASK_18 = (1 << 18),
	TASKMASK_19 = (1 << 19),

	TASKMASK_20 = (1 << 20),
	TASKMASK_21 = (1 << 21),
	TASKMASK_22 = (1 << 22),
	TASKMASK_23 = (1 << 23),
	TASKMASK_24 = (1 << 24),
	TASKMASK_25 = (1 << 25),
	TASKMASK_26 = (1 << 26),
	TASKMASK_27 = (1 << 27),
	TASKMASK_28 = (1 << 28),
	TASKMASK_29 = (1 << 29),

	TASKMASK_30 = (1 << 30),
	TASKMASK_31 = (1 << 31),

	/// \brief Maximum number of tasks selected.
	TASKMASK_All = 0xffffffff,
} TASKMASK;

/// \brief Define for specifying that the function is to be exported.
///
/// This is necessary to mark functions as exported from this library
/// and thus allowing other libraries and applications to call them.
///
/// This can be safely ignored by most users.
#ifdef __A3200_C_LIBRARY_INTERNAL__
	#define DLLENTRYDECLARATION      /*export uses *.def file*/ __stdcall
#else
	#define DLLENTRYDECLARATION       __declspec(dllimport) __stdcall
#endif

/// \brief Define for marking functions as obsolete or deprecated.
#if defined(__GCCXML__) || defined(__GNUC__)
	#define DEPRECATED(reason) __declspec(deprecated)
#elif _MSC_VER >= 1400
	#define DEPRECATED(reason) __declspec(deprecated(reason))
#elif _MSC_VER >= 1300
	#define DEPRECATED(reason) __declspec(deprecated)
#else
	#define DEPRECATED(reason) 
#endif

#ifdef __cplusplus
}
#endif

#endif // __A3200_COMMONTYPES_H__
