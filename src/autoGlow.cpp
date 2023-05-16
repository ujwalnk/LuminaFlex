/**
 * Author: Ujwal N K
 * Created On: 18 Apr, 2023
 * main Module for AutoGlow
**/

#include <iostream>
#include <math.h>
#include <Windows.h>

#include "fileSentinel.h"
#include "intensitySentinel.h"

#pragma GCC optimize("Ofast")
#pragma comment(lib, "gdi32.lib")

using namespace std;

int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
){
	// Read, store necessary configurations & free memory
	FileSentinel fSentinel;

	// TODO: Check for change in window

	// Read and change intensity
	IntensitySentinel iSentinel;

	Sleep(3000);
	cout << iSentinel.getIntensity();

	while(true){
		int prevInt = iSentinel.getIntensity();
		Sleep(3000);
		int currInt = iSentinel.getIntensity();
		cout << "Intensity: " << currInt << endl;

		if(abs(currInt - prevInt) >= 10){
			iSentinel.chgBrightness(fSentinel.getUseGammaRamp(), fSentinel.getDelta(), fSentinel.getMaxLum(), fSentinel.getMinLum());
		}
	}
	
	return 0;
}
