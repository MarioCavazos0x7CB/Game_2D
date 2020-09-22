#include <stdio.h>

#pragma warning(push, 3)
#include <Windows.h>
#pragma warning (pop)
#include "winMain.h"



INT WinMain(_In_ HINSTANCE Instance, _In_opt_ HINSTANCE PreviousInstance, _In_ PSTR CommandLine, _In_ INT CommandShow)
{

	UNREFERENCED_PARAMETER(PreviousInstance);
	UNREFERENCED_PARAMETER(CommandLine);
	UNREFERENCED_PARAMETER(CommandShow);

	if (CreateMainGameWindow() != ERROR_SUCCESS) {

		goto Exit;
	}

	MSG Message;

	while (GetMessageA(&Message, NULL, 0, 0) > 0) {

		TranslateMessage(&Message);

		DispatchMessageA(&Message);
	}

Exit:

	return (0);
}

LRESULT CALLBACK MainWindowProcedure(_In_ HWND WindowsHandle, _In_ UINT Message, _In_ WPARAM wParam, _In_ LPARAM LParam) {

	LRESULT Result = 0;

	switch (Message)
	{
	case WM_CLOSE: 
	{
		PostQuitMessage(0);
	}
	default: {

		Result = DefWindowProcA(WindowsHandle, Message, wParam, LParam);
	}
	}
	return (Result);
}


DWORD CreateMainGameWindow(void) {

	DWORD Result = ERROR_SUCCESS;

	WNDCLASSEXA WindowClass = { 0 };

	HWND WindowHandle = 0;

	WindowClass.cbSize = sizeof(WNDCLASSEXA);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = MainWindowProcedure;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = GetModuleHandleA(NULL);
	WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = "GAME_2D_WINDOWCLASS";

	if (RegisterClassExA(&WindowClass) == 0) {

		Result = GetLastError();

		MessageBoxA(NULL, "Windows Creation Failed", "Error!", MB_ICONEXCLAMATION | MB_OK);

		goto Exit;
	}

	WindowHandle = CreateWindowExA(WS_EX_CLIENTEDGE, WindowClass.lpszClassName, "Window Title", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, GetModuleHandleA(NULL), NULL);

	if (WindowHandle == NULL) {

		Result = GetLastError();

		MessageBoxA(NULL, "Windows Creation Failed", "Error!", MB_ICONEXCLAMATION | MB_OK);

		goto Exit;
	}



Exit:

	return(Result);

}