/// \file A3200MessageCallbacks.h
/// \brief Contains convenience functions to interpret message callback arguments.
///
/// Copyright (c) Aerotech, Inc. 2010-2018.
/// 

#ifndef __A3200_MESSAGE_CALLBACKS_H__
#define __A3200_MESSAGE_CALLBACKS_H__

#include "A3200CommonTypes.h"
#include "A3200ParameterId.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \defgroup messagecallback Message Callback Functions
/// @{

#define SMC_STRING_SIZE 1024

/// The MessageDisplayData structure is used to return arguments passed in the MSGDISPLAY callback
typedef struct tagMessageDisplayData {
	INT priority; ///< The message priority
	char text[SMC_STRING_SIZE]; ///< The message text
} MessageDisplayData;

/// The MessageBoxData structure is used to return arguments passed in the MSGBOX callback
typedef struct tagMessageBoxData {
	DWORD type; ///< The message box options (icon, buttons, etc.)
	DWORD clickedButton; ///< A value representing which button was clicked. The user of the C library can set this value in their callback handling code
	char text[SMC_STRING_SIZE]; ///< The message box text
} MessageBoxData;

/// The MessageClearData structure is used to return arguments passed in the MSGCLEAR callback
typedef struct tagMessageClearData {
	INT priority; ///< The priority threshold of messages to clear. Messages with a priority less than this value should be cleared.
} MessageClearData;

// The MessageFileSelectData structure is used to return arguments passed in the MSGFILESELECT callback
typedef struct tagMessageFileSelectData {
	INT dialogKind; ///< The value "Open" or "Save" to be shown in the dialog box
	INPUTBOXCLICKEDBUTTON clickedButton; ///< The button clicked by the user. The callback handling code should set this value.
	char title [SMC_STRING_SIZE]; ///< The title to appear on top of the dialog box
	char initialDirectory [SMC_STRING_SIZE]; ///< The directory the dialog starts at
	char initialFile [SMC_STRING_SIZE]; ///< The initially selected file
	char filter [SMC_STRING_SIZE]; ///< The types of files to display, can contain multiple values separated by "|"
	char filePath [SMC_STRING_SIZE]; ///< The directory of the file selected by the user
} MessageFileSelectData;

/// The MessageLampData structure is used to return arguments passed in the MSGLAMP callback
typedef struct tagMessageLampData {
	DWORD number; ///< The lamp number to be illuminated
	COLORREF color; ///< The color (represented as an RGB value) of the lamp
	char text[SMC_STRING_SIZE]; ///< The text displayed in the lamp
} MessageLampData;

/// The MessageInputData structure is used to return arguments passed in the MSGINPUT callback
typedef struct tagMessageInputData {
	INPUTBOXKIND kind; ///< The input box type (for integer, double, or string input)
	INPUTBOXCLICKEDBUTTON clickedButton; ///< The button clicked by the user. The callback handling code should set this value.
	DWORD buttons; ///< The buttons to show on the dialog
	DWORD integerValue; ///< The default value to populate the input field with, if the input box kind is of type integer. Callback handling code sets this value to return user input.
	DOUBLE doubleValue; ///< The default value to populate the input field with, if the input box kind is of type double. Callback handling code sets this value to return user input.
	char stringValue[SMC_STRING_SIZE]; ///< The default value to populate the input field with, if the input box kind is of type string. Callback handling code sets this value to return user input.
	char title[SMC_STRING_SIZE]; ///< The title to appear on the top of the input box
	char promptText[SMC_STRING_SIZE]; ///< The text (generally a question to the user) that will be displayed in the input box
} MessageInputData;

/// The MessageMenuOption structure is returned by the MessageMenuData structure.
typedef struct tagMessageMenuOption{
	LPSTR optionLabel; ///< The text associated with the option
	INT optionNumber; ///< The number associated with the option.
} MessageMenuOption;

/// The MessageMenuData structure is used to return arguments passed in the MSGMENU_SHOW callback
typedef struct tagMessageMenuData {
	INT buttons; ///< The buttons to show on the dialog
	INT defaultId; ///< The number of the pre-highlighted selection
	INPUTBOXCLICKEDBUTTON clickedButton; ///< The button clicked by the user. The callback handling code should set this value.
	MessageMenuOption *optionList; ///< An array containing each option as a struct.
	INT optionsLength; ///< The number of items contained in optionList and optionNumbers
	INT optionSelected; ///< The number of the user's selection
	char title[SMC_STRING_SIZE]; ///< The title to appear on top of the dialog box
	char prompt[SMC_STRING_SIZE]; ///< The text that will be displayed above the selections
} MessageMenuData;

/// A structure containing function pointers to user callback handlers. When a callback of the specific type is raised, the appropriate user callback function is called.
typedef struct tagMessageCallbackHandlers {
	size_t structSize; // Reserved for internal use
	ErrorData (*messageDisplay)(A3200Handle, TASKID, MessageDisplayData*); ///< Function pointer to the user handler for MSGDISPLAY
	ErrorData (*messageInput)(A3200Handle, TASKID, MessageInputData*); ///< Function pointer to the user handler for MSGINPUT
	ErrorData (*messageLamp)(A3200Handle, TASKID, MessageLampData*); ///< Function pointer to the user handler for MSGLAMP
	ErrorData (*messageShow)(A3200Handle, TASKID); ///< Function pointer to the user handler for MSGSHOW
	ErrorData (*messageHide)(A3200Handle, TASKID); ///< Function pointer to the user handler for MSGHIDE
	ErrorData (*messageClear)(A3200Handle, TASKID, MessageClearData*); ///< Function pointer to the user handler for MSGCLEAR
	ErrorData (*messageBox)(A3200Handle, TASKID, MessageBoxData*); ///< Function pointer to the user handler for MSGBOX
	ErrorData (*messageFileSelect)(A3200Handle, TASKID, MessageFileSelectData*); ///< Function pointer to the user handler for MSGFILESELECT
	ErrorData (*messageMenuShow) (A3200Handle, TASKID, MessageMenuData*); ///< Function pointer to the user handle for MSGMENU
} MessageCallbackHandlers;

/// \brief Initializes the structure which contains user callback handler function pointers
///
/// This function initializes the structure used by the user to store function pointers to the user's callback handlers.
/// \param[in] handlers A pointer to the structure
/// \param[in] structSize The size of the structure, in bytes
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackInitializeMessageHandlers(MessageCallbackHandlers* handlers, size_t structSize);

/// \brief Waits for message callbacks on the specified task and executes user callback handlers
///
/// Waits for message callbacks on the specified task and calls the callback handling functions specified in the MessageCallbackHandlers structure. This function blocks until an error is encountered or another thread calls A3200CallbackWaitCancel.
/// \param[in] handle The handle to the A3200
/// \param[in] taskId The task to handle message callbacks on
/// \param[in] handlers A structure containing function pointers to user callback handling functions
/// \return TRUE on success, FALSE if an error occurred. Call A3200GetLastError() for more information.
BOOL DLLENTRYDECLARATION A3200CallbackHandleMessageCallbacks(A3200Handle handle, TASKID taskId, MessageCallbackHandlers* handlers);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __A3200_MESSAGE_CALLBACKS_H__
