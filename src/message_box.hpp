#pragma once

#define WIN32_LEAN_AND_MEAN // Avoid including some not-used headers in windows.h
#include <Windows.h>
#include <Winuser.h>

#include "charcoal/core/primitives_types.hpp"
using namespace charcoal;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
enum class MessageBoxIcon : u32::inner_type
{
	Error		= MB_ICONERROR,
	Information	= MB_ICONINFORMATION,
	Question	= MB_ICONQUESTION,
	Warning		= MB_ICONWARNING
};

enum class MessageBoxAction : u32::inner_type
{
	Ok 	= MB_OK,
	OkCancel	= MB_OKCANCEL,
	RetryCancel	= MB_RETRYCANCEL,
	YesNo		= MB_YESNO,
	YesNoCancel	= MB_YESNOCANCEL,
	Help		= MB_HELP,
	CancelTryContinue	= MB_CANCELTRYCONTINUE,
	AbortRetryIgnore	= MB_ABORTRETRYIGNORE
};

enum class MessageBoxDefButton : u32::inner_type
{
	Button1 = MB_DEFBUTTON1,
	Button2 = MB_DEFBUTTON2,
	Button3 = MB_DEFBUTTON3,
	Button4 = MB_DEFBUTTON4
};

enum class MessageBoxModality : u32::inner_type
{
	Application	= MB_APPLMODAL,
	System		= MB_SYSTEMMODAL,
	Task		= MB_TASKMODAL
};

// Multiple choices allowed for this one
enum class MessageBoxSettings : u32::inner_type
{
	DefaultDesktopOnly	= MB_DEFAULT_DESKTOP_ONLY,
	RightJustified		= MB_RIGHT,
	RightToLeftReading	= MB_RTLREADING,
	SetForeground		= MB_SETFOREGROUND,
	TopMost				= MB_TOPMOST,
	ServiceNotification	= MB_SERVICE_NOTIFICATION
};
DEFINE_ENUM_FLAG_OPERATORS( MessageBoxSettings );

enum class MessageBoxResult
{
	IDOk	= IDOK,
	IDYes	= IDYES,
	IDNo	= IDNO,
	IDAbort = IDABORT,
	IDContinue	= IDCONTINUE,
	IDCancel	= IDCANCEL,
	IDIgnore	= IDIGNORE,
	IDTryAgain	= IDTRYAGAIN,
	IDRetry		= IDRETRY
};

struct MessageBoxContent
{
	HWND				ownerHandle;
	MessageBoxIcon		icon;
	MessageBoxAction	action;
	MessageBoxDefButton defButton;
	MessageBoxModality	modality;
	MessageBoxSettings	settings;
	LPCSTR				title;
	LPCSTR				body;
};


inline auto message_box( MessageBoxContent const &content ) -> MessageBoxResult
{
	u32 const type( (uint32_t)content.action
		| (uint32_t)content.icon
		| (uint32_t)content.defButton
		| (uint32_t)content.modality
		| (uint32_t)content.settings
	);

	return MessageBoxResult( ::MessageBoxA(
		content.ownerHandle,
		content.body,
		content.title,
		type.as_inner()
	) );
}
