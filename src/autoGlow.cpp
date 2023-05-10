/**
 * Author: Ujwal N K
 * Created On: 18 Apr, 2023
 * main Module for AutoGlow
**/

#include <iostream>
#include <Windows.h>

#include "getScreenLuminance.h"
#include "gammaramp.h"

#pragma comment(lib, "gdi32.lib")

using namespace std;

int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
){
	
	cout << getScreenLuminance() << endl;
	
	CGammaRamp gammaRamp;

	// Make the screen darker
	gammaRamp.SetBrightness(NULL, 64);
	
	cout << "Set Brightness to 50%" << endl;

	Sleep(3000);

	// Return the screen brightness back to normal
	cout << "Return to normal";
	gammaRamp.SetBrightness(NULL, 128);
	
	return 0;
}

