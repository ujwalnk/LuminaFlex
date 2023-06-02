/**
 * Author: Ujwal N K
 * Created On: June 1, 2023
 * Handle display GammaRamp to change brightness
**/

#include "GammaRamp.h"

#include <iostream>
#include <windows.h>

bool GammaRamp::setBrightness(WORD brightness){
    // Get the primary display device context
    HDC hdc = GetDC(NULL);
    if (hdc == NULL){
        std::cout << "Failed to get display device context." << std::endl;
        return false;
    }

    // Get the original gamma ramp
    WORD originalGammaRamp[3][256];
    if (!GetDeviceGammaRamp(hdc, originalGammaRamp)){
        std::cout << "Failed to get original gamma ramp." << std::endl;
        ReleaseDC(NULL, hdc);
        return false;
    }

    // Generate a new gamma ramp based on the brightness level
    WORD gammaRamp[3][256];
    for (int i = 0; i < 256; i++){
        gammaRamp[0][i] = gammaRamp[1][i] = gammaRamp[2][i] = (brightness * i) / 255;
    }

    // Set the new gamma ramp
    if (!SetDeviceGammaRamp(hdc, gammaRamp)){
        std::cout << "Failed to set gamma ramp." << std::endl;
        ReleaseDC(NULL, hdc);
        return false;
    }

    std::cout << "Brightness set to: " << brightness << std::endl;

    // Release the device context
    ReleaseDC(NULL, hdc);

    return true;
}

/*x
int main()
{
    // Set the brightness to 50 (adjust as needed)
    WORD brightnessLevel = 50;
    if (setBrightness(brightnessLevel))
    {
        std::cout << "Brightness changed successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to change brightness." << std::endl;
    }

    return 0;
}
bool GammaRamp::setBrightness(WORD brightness)*/