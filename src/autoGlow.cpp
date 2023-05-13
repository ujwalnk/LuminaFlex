/**
 * Author: Ujwal N K
 * Created On: 18 Apr, 2023
 * main Module for AutoGlow
**/

#include <iostream>
#include <Windows.h>

#include "consoleSentinel.h"
#include "fileSentinel.h"
#include "gammaramp.h"
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
	
	CGammaRamp gammaRamp;
	IntensitySentinel iSentinel;
	ConsoleSentinel cSentinel;
	FileSentinel fSentinel;


	cout << iSentinel.getIntensity() << endl;
	
	// Make the screen darker
	// gammaRamp.SetBrightness(NULL, 64);
	
	cSentinel.setBrightness(50);
	cout << "Current Brightness" << cSentinel.getBrightness() << endl;

	Sleep(3000);

	// Return the screen brightness back to normal
	cout << "Return to normal";
	// gammaRamp.SetBrightness(NULL, 128);
	
	return 0;
}

