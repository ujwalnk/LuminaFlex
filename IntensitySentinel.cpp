/**
 * Author: Ujwal N K
 * Created On: 05 May, 2023
 * Get BitMap Image of the Screen & Calculate Luminesce
**/

#include "intensitySentinel.h"

#include <gdiplus.h>
#include <iostream>
#include <stdint.h>
#include <Windows.h>

//#include "consoleSentinel.h"
//#include "gammaRamp.h"

//#pragma GCC optimize("Ofast")

static int width;
static int height;

//static ConsoleSentinel cSentinel;
//static CGammaRamp gammaRamp;

float map(float in, float inMin, float inMax, float outMin, float outMax);

/**
 * Get the device context and dimensions of the primary display
 **/
void IntensitySentinel::getScreenDimensions(HDC& hScreen) {
	hScreen = GetDC(NULL);
	width = GetDeviceCaps(hScreen, HORZRES);
	height = GetDeviceCaps(hScreen, VERTRES);
}

/**
 * Create compatible device context and bitmap for screen
 **/
HBITMAP IntensitySentinel::createCompatibleScreenBitmap(HDC& hScreen, HDC& hDC) {
	// Create bitmap for the screen
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
	hDC = CreateCompatibleDC(hScreen);

	// Select new bitmap to DC & Copy screen contents
	HGDIOBJ hOld = SelectObject(hDC, hBitmap);
	BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

	// Select old bitmap back into DC
	SelectObject(hDC, hOld);
	return hBitmap;
}

//void IntensitySentinel::chgBrightness(bool useGammaRamp, int delta, float maxL, float minL) {
//	std::cout << cSentinel.getBrightness();
//
//	float deltaBrightness = map(getIntensity(), minL, maxL, -delta / 2, delta / 2);
//	cSentinel.setBrightness(cSentinel.getBrightness() - deltaBrightness);
//
//	std::cout << " - " << deltaBrightness << " = " << cSentinel.getBrightness() << std::endl;
//}

/**
 * Retrieve the bitmap data for specified bitmap
 **/
bool IntensitySentinel::getBitmapData(HDC& hDC, HBITMAP& hBitmap, BITMAPINFO& bmi, uint8_t*& data) {
	// Get Bitmap info
	if (GetDIBits(hDC, hBitmap, 0, bmi.bmiHeader.biHeight, NULL, &bmi, DIB_RGB_COLORS) > 0) {
		// Allocate memory to store bitmap data
		data = new uint8_t[bmi.bmiHeader.biSizeImage];

		// Store bit bitmap data into the buffer
		// Free on error
		if (GetDIBits(hDC, hBitmap, 0, bmi.bmiHeader.biHeight, data, &bmi, DIB_RGB_COLORS) == 0) {
			delete[] data;
			data = NULL;
		}
	}
	return data != NULL;
}

/**
 * Calculate the luminance of a single pixel using the Rec. 709 formula
 **/
double IntensitySentinel::calculatePixelLuminance(uint8_t* pixel) {
	uint8_t r = *(pixel + 2);
	uint8_t g = *(pixel + 1);
	uint8_t b = *pixel;
	return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

/**
 * Set Bitmap image parameters
 */
void IntensitySentinel::setBitmapInfo(BITMAPINFO& bmi) {
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;  // inverted bitmap
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
}

/**
 * Calculate average luminance of entire screen
 **/
double IntensitySentinel::getIntensity() {
	HDC hScreen, hDC;
	getScreenDimensions(hScreen);
	HBITMAP hBitmap = createCompatibleScreenBitmap(hScreen, hDC);

	BITMAPINFO bmi = {};
	setBitmapInfo(bmi);

	uint8_t* data = NULL;

	// Error & Return on fail
	if (!getBitmapData(hDC, hBitmap, bmi, data)) {
		std::cerr << "Failed to get screen bitmap data" << std::endl;
		return -1;
	}

	// Calculate Sum of Luminance values
	double totalLuminance = 0.0;
	for (int i = 0; i < (width * height); i++) {
		uint8_t* pixel = data + (i * 4);
		double luminance = calculatePixelLuminance(pixel);
		totalLuminance += luminance;
	}

	// Free and return average luminance
	delete[] data;

	return totalLuminance / (width * height);
}

/**
 * Source: https://stackoverflow.com/questions/345187/math-mapping-numbers
 * Function for standard mathematical mapping of two ranges and get a number in between as output for defined input
 * @param in(float): Input Value to be mapped
 * @param inMin(float): Input Range Minimum
 * @param inMax(float): Input Range Maximum
 * @param outMin(float): Output Range Minimum
 * @param outMax(float): Output Range Maximum
 * @return (float): Mapped output for given input
*/
float map(float in, float inMin, float inMax, float outMin, float outMax) {
	return ((in - inMin) / (inMax - inMin) * (outMax - outMin) + outMin);
}