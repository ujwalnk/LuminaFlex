/**
 * Author: Ujwal N K
 * Created On: 18 Apr, 2023
 * main Module for AutoGlow
 **/

#include <iostream>
#include <math.h>
#include <Windows.h>

#include "fileSentinel.h"
#include "hookSentinel.h"
#include "intensitySentinel.h"

#pragma GCC optimize("Ofast")
#pragma comment(lib, "gdi32.lib")

using namespace std;

void core();

int WINAPI WinMain(HINSTANCE hInstance,      // handle to current instance
                   HINSTANCE hPrevInstance,  // handle to previous instance
                   LPSTR lpCmdLine,          // command line
                   int nCmdShow              // show state
) {
	core();

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
	// while(true){

	// HHOOK SetWindowsHookExA(WH_CALLWNDPROCRET, )

	SetHook();
	
	MSG msg;

	while(1){

		GetMessage(&msg, NULL, 0, 0);

		int prevInt = iSentinel.getIntensity();
		Sleep(3000);
		int currInt = iSentinel.getIntensity();
		cout << "Intensity: " << currInt << endl;

		if (abs(currInt - prevInt) >= 10) {
			iSentinel.chgBrightness(fSentinel.getUseGammaRamp(), fSentinel.getDelta(), fSentinel.getMaxLum(), fSentinel.getMinLum());
		}
	}
}
