#include <stdio.h>

#pragma warning(push, 3)
#include <Windows.h>
#pragma warning (pop)

LRESULT CALLBACK MainWindowProcedure(HWND WindowsHandle, UINT Message, WPARAM wParam, LPARAM LParam);

DWORD CreateMainGameWindow(_In_ HANDLE Instance);

int WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, PSTR CommandLine, INT CommandShow)
{

	UNREFERENCED_PARAMETER(PreviousInstance);
	UNREFERENCED_PARAMETER(CommandLine);
	UNREFERENCED_PARAMETER(CommandShow);

	if (CreateMainGameWindow(Instance) != ERROR_SUCCESS) {

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

LRESULT CALLBACK MainWindowProcedure(HWND WindowsHandle, UINT Message, WPARAM wParam, LPARAM LParam) {

		LRESULT Result = 0;

		switch (Message)
		{
		default: {

			Result = DefWindowProcA(WindowsHandle, Message, wParam, LParam);
			}
		}
		return (Result);
	}


DWORD CreateMainGameWindow (_In_ HANDLE Instance) {

	DWORD Result = ERROR_SUCCESS;

	WNDCLASSEXA WindowClass = { 0 };
	
	HWND WindowHandle = 0;

	WindowClass.cbSize = sizeof(WNDCLASSEXA);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = MainWindowProcedure;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = Instance;
	WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = "GAME_2D_WINDOWCLASS";

	if (RegisterClassExA(&WindowClass) == 0){

		Result = GetLastError();

		MessageBoxA(NULL, "Windows Creation Failed", "Error!", MB_ICONEXCLAMATION | MB_OK);

		goto Exit;
	}

	WindowHandle = CreateWindowExA(WS_EX_CLIENTEDGE, WindowClass.lpszClassName, "Window Title", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, Instance, NULL);

	if (WindowHandle == NULL) {

		Result = GetLastError();

		MessageBoxA(NULL, "Windows Creation Failed", "Error!", MB_ICONEXCLAMATION | MB_OK);

		goto Exit;
	}


		
Exit:

	return(Result);

}


