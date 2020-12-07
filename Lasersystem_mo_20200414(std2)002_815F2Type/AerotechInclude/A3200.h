/// \file A3200.h
/// \brief Contains the includes of all the other files that allow access to A3200.
///
/// Include this file to get all the functionality of the C library.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

/// \mainpage A3200 C Library
/// \brief This is documentation for the A3200 C Library.
///
/// The following is an example of enabling an axis:
/// \dontinclude "Examples.chh"
/// \skip GlobalSimpleExample
/// \until }
///
/// Example programs can be found in <b>[InstallDir]\\Samples\\Cpp\\CLibrary\\</b> and <b>[InstallDir]\\Samples\\C\\CLibrary\\</b>.
///
/// The C Library files can be found in <b>[InstallDir]\\CLibrary</b>.\n
/// 1) <b>include</b> directory contains the header files.\n
/// 2) <b>lib</b> and <b>lib64</b> directories contain the 32-bit and 64-bit lib files.\n
/// 3) <b>bin</b> and <b>bin64</b> directories contain the 32-bit and 64-bit dll files.
///
/// All of the files found in <b>bin</b> and <b>bin64</b> are required for proper operation.  Do one of the following for the 
/// application to load correctly:\n
/// 1) Add <b>[InstallDir]\\CLibrary\\bin\\</b> and <b>[InstallDir]\\CLibrary\\bin64\\</b> to the PATH.\n
/// 2) Copy all the the *.dll files from <b>[InstallDir]\\CLibrary\\bin\\</b> and <b>[InstallDir]\\CLibrary\\bin64\\</b> into the output directory.\n

#ifndef __A3200_H__
#define __A3200_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "A3200AeroBasicCommands.h"
#include "A3200CommonTypes.h"
#include "A3200CommonStructures.h"
#include "A3200Connection.h"
#include "A3200Commands.h"
#include "A3200Error.h"
#include "A3200ErrorCode.h"
#include "A3200Program.h"
#include "A3200Status.h"
#include "A3200StatusItemInfo.h"
#include "A3200Variable.h"
#include "A3200Parameter.h"
#include "A3200Callback.h"
#include "A3200DataCollection.h"
#include "A3200MessageCallbacks.h"
#include "A3200EnumNames.h"
#include "A3200Information.h"
#include "A3200Configuration.h"

#ifdef __cplusplus
}
#endif

#endif // __A3200_H__
