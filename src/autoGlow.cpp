/**
 * Author: Ujwal N K
 * Created On: 18 Apr, 2023
 * main Module for AutoGlow
 **/

#include <Windows.h>
#include <math.h>

#include <iostream>

#include "fileSentinel.h"
#include "intensitySentinel.h"

#pragma GCC optimize("Ofast")
#pragma comment(lib, "gdi32.lib")

using namespace std;

HINSTANCE hInst;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE:{
            // Create the textbox control
            HWND deltaTB = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                10, 10, 200, 25, hwnd, (HMENU)1002, hInst, NULL);
            break;
        }

    	case WM_DESTROY:
      		PostQuitMessage(0);
      		return 0;     

        case WM_COMMAND:{
            if (LOWORD(wParam) == 1002 && HIWORD(wParam) == EN_CHANGE){
                // Handle textbox value change here
                HWND deltaTB = GetDlgItem(hwnd, 1002);
                char buffer[256];
                GetWindowText(deltaTB, buffer, sizeof(buffer));

                // Perform validation
                int value = atoi(buffer);
                if (value < 5 || value > 100){
                    // Input is outside the valid range, show an error message or take appropriate action
                    MessageBox(hwnd, "Please enter a number between 5 and 100.", "Invalid Input", MB_OK | MB_ICONERROR);
                }
            }
            break;
        }
	}

  	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,      // handle to current instance
                   HINSTANCE hPrevInstance,  // handle to previous instance
                   LPSTR lpCmdLine,          // command line
                   int nCmdShow              // show state
) {
	const char* CLASS_NAME = "MyWindowClass";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	hInst = hInstance;

	RegisterClass(&wc);

	// Creating a window
  	HWND hwnd =	CreateWindowEx(0,                    // Optional window styles.
						CLASS_NAME,           // Window class
						"Auto Glow",		    // Window text
						WS_OVERLAPPEDWINDOW,  // Window style

						// Size and position
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

						NULL,       // Parent window
						NULL,       // Menu
						hInstance,  // Instance handle
						NULL        // Additional application data
	);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// HWND hwndTextbox;
	// hwndTextbox = CreateWindowEx(0, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 10, 10, 200, 25, hwnd, (HMENU)1001, hInstance, NULL);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

/**
 * Core functionality of the application
*/
void core(){
	
	// Read, store necessary configurations & free memory
	FileSentinel fSentinel;

	// Read and change intensity
	IntensitySentinel iSentinel;

	// TODO: Check for change in window
	while(true){

		int prevInt = iSentinel.getIntensity();
		Sleep(3000);
		int currInt = iSentinel.getIntensity();
		cout << "Intensity: " << currInt << endl;

		if (abs(currInt - prevInt) >= 10) {
			iSentinel.chgBrightness(fSentinel.getUseGammaRamp(), fSentinel.getDelta(), fSentinel.getMaxLum(), fSentinel.getMinLum());
		}
	}
}
