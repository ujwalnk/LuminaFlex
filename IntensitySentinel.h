#pragma once

/**
 * Author: Ujwal N K
 * Created On: 05 May, 2023
 **/

#ifndef IntensitySentinel_h
#define IntensitySentinel_h

#include <stdint.h>
#include <windows.h>

class IntensitySentinel {
public:
	double getIntensity();
	//void chgBrightness(bool useGammaRamp, int delta, float maxL, float minL);

private:
	double calculatePixelLuminance(uint8_t* pixel);
	HBITMAP createCompatibleScreenBitmap(HDC& hScreen, HDC& hDC);
	void getScreenDimensions(HDC& hScreen);
	bool getBitmapData(HDC& hDC, HBITMAP& hBitmap, BITMAPINFO& bmi, uint8_t*& data);
	void setBitmapInfo(BITMAPINFO& bmi);
};

#endif