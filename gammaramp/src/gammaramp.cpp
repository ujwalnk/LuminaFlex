/**
 * Source: Nir Sofer http://www.nirsoft.net/vc/change_screen_brightness.html
 * Copied On: 10 May, 2023
 * Module Info: Encapsulates the GammaRamp API and changes the brightness of the
 * entire screen
 *
 * Change the brightness of the screen using GammaRamp API
 */

#include "gammaRamp.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

#define SYNTAX_INCORRECT_MSG "Command syntax incorrect, try .\\gammaramp.exe --help for help"

using namespace std;

#pragma comment(lib, "gdi32.lib")

bool isNumber(char number[]){
  if (number[0] == '-')
    for (int i = 1; number[i] != 0; i++){
      if (!isdigit(number[i]))
        return false;
    }
  return true;
}

CGammaRamp::CGammaRamp() {
  // Initialize all variables.
  hGDI32 = NULL;
  hScreenDC = NULL;
  pGetDeviceGammaRamp = NULL;
  pSetDeviceGammaRamp = NULL;
}

CGammaRamp::~CGammaRamp() { FreeLibrary(); }

BOOL CGammaRamp::LoadLibrary() {
  BOOL bReturn = FALSE;

  FreeLibrary();
  // Load the GDI library.
  hGDI32 = ::LoadLibrary("gdi32.dll");
  if (hGDI32 != NULL) {
    // Get the addresses of GetDeviceGammaRamp and SetDeviceGammaRamp API
    // functions.
    pGetDeviceGammaRamp =
        (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");

    pSetDeviceGammaRamp =
        (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");

    // Return TRUE only if these functions exist.
    if (pGetDeviceGammaRamp == NULL || pSetDeviceGammaRamp == NULL)
      FreeLibrary();
    else
      bReturn = TRUE;
  }

  return bReturn;
}

void CGammaRamp::FreeLibrary() {
  // Free the GDI library.
  if (hGDI32 != NULL) {
    ::FreeLibrary(hGDI32);
    hGDI32 = NULL;
  }
}

BOOL CGammaRamp::LoadLibraryIfNeeded() {
  BOOL bReturn = FALSE;

  if (hGDI32 == NULL) LoadLibrary();

  if (pGetDeviceGammaRamp != NULL && pSetDeviceGammaRamp != NULL)
    bReturn = TRUE;

  return bReturn;
}

BOOL CGammaRamp::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp) {
  // Call to SetDeviceGammaRamp only if this function is successfully loaded.
  if (LoadLibraryIfNeeded()) {
    return pSetDeviceGammaRamp(hDC, lpRamp);
  } else
    return FALSE;
}

BOOL CGammaRamp::GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp) {
  // Call to GetDeviceGammaRamp only if this function is successfully loaded.
  if (LoadLibraryIfNeeded()) {
    return pGetDeviceGammaRamp(hDC, lpRamp);
  } else
    return FALSE;
}

BOOL CGammaRamp::SetBrightness(HDC hDC, WORD wBrightness) {
  /*
  Changes the brightness of the entire screen.
  This function may not work properly in some video cards.

  The wBrightness value should be a number between 0 and 255.
  128 = Regular brightness
  above 128 = brighter
  below 128 = darker

If hDC is NULL, SetBrightness automatically load and release
  the display device context for you.

  */
  BOOL bReturn = FALSE;
  HDC hGammaDC = hDC;

  // Load the display device context of the entire screen if hDC is NULL.
  if (hDC == NULL) hGammaDC = GetDC(NULL);

  if (hGammaDC != NULL) {
    // Generate the 256-colors array for the specified wBrightness value.
    WORD GammaArray[3][256];

    for (int iIndex = 0; iIndex < 256; iIndex++) {
      int iArrayValue = iIndex * (wBrightness + 128);

      if (iArrayValue > 65535) iArrayValue = 65535;

      GammaArray[0][iIndex] = GammaArray[1][iIndex] = GammaArray[2][iIndex] =
          (WORD)iArrayValue;
    }

    // Set the GammaArray values into the display device context.
    bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
  }

  if (hDC == NULL) ReleaseDC(NULL, hGammaDC);

  return bReturn;
}

int main(int argc, char** argv) {

  if (argc > 1) {
    if(isNumber(argv[1])){
      int userInput = atoi(argv[1]);
      if(userInput <= 255 && userInput >= 0){
        CGammaRamp gRamp;
        gRamp.SetBrightness(NULL, userInput);
      } else{
        cout << SYNTAX_INCORRECT_MSG << endl << endl;
      }
    }
    else if ((!strcmp(argv[1], "-h")) || (!strcmp(argv[1], "--help"))) {
      cout << "Sets the gammaramp of the display" << endl
           << endl
           << "gammaramp [wBrightness] [-h][-l]" << endl
           << "wBrightness: Value between 0 to 255" << endl
           << endl
           << "   wBrightness < 128 : Darker" << endl
           << "   wBrightness = 128 : Regular" << endl
           << "   wBrightness > 128 : Brighter" << endl << endl
           << "-h --help: Display this help menu" << endl
           << "-l --license: Display the license" << endl
           << endl;
    }

    else if ((!strcmp(argv[1], "-l")) || (!strcmp(argv[1], "--license"))) {
      cout << "License: MIT " << endl
           << "Copyright <2023> <Ujwal N K>" << endl
           << endl
           << "Permission is hereby granted, free of charge, to any person "
              "obtaining a copy of this software and associated documentation "
              "files (the \"Software\"), to deal in the Software without "
              "restriction, including without limitation the rights to use, "
              "copy, "
              "modify, merge, publish, distribute, sublicense, and/or sell "
              "copies "
              "of the Software, and to permit persons to whom the Software is "
              "furnished to do so, subject to the following conditions:"
           << endl
           << "The above copyright notice and this permission notice shall be "
              "included in all copies or substantial portions of the Software."
           << endl
           << endl
           << "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY "
              "KIND, "
              "EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES "
              "OF "
              "MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND "
              "NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT "
              "HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, "
              "WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING "
              "FROM, "
              "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER "
              "DEALINGS IN THE SOFTWARE."
           << endl << endl;
    } else{
      cout << SYNTAX_INCORRECT_MSG << endl << endl;
    }
  } else{
    cout << SYNTAX_INCORRECT_MSG << endl << endl;

  }

  return 0;
}