#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdint.h>

#pragma comment(lib, "gdi32.lib")

using namespace std;

double GetScreenLuminance(){
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    int width = GetDeviceCaps(hScreen, HORZRES);
    int height = GetDeviceCaps(hScreen, VERTRES);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    HGDIOBJ hOld = SelectObject(hDC, hBitmap);
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);
    SelectObject(hDC, hOld);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down bitmap
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;

    uint8_t* data = NULL;
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hDC, hBitmap);
    if (GetDIBits(hDC, hBitmap, 0, height, NULL, &bmi, DIB_RGB_COLORS) > 0) {
        data = new uint8_t[bmi.bmiHeader.biSizeImage];
        if (GetDIBits(hDC, hBitmap, 0, height, data, &bmi, DIB_RGB_COLORS) == 0) {
            delete[] data;
            data = NULL;
        }
    }
    SelectObject(hDC, hBitmapOld);
    DeleteObject(hBitmap);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);

    if (!data) {
        std::cerr << "Failed to get screen bitmap data" << std::endl;
        return -1;
    }

    double totalLuminance = 0.0;
    int numPixels = width * height;
    for (int i = 0; i < numPixels; i++) {
        // Get the RGB values from the bitmap data (assuming 32 bits per pixel)
        uint8_t* pixel = data + (i * 4);
        uint8_t r = *(pixel + 2);
        uint8_t g = *(pixel + 1);
        uint8_t b = *pixel;

        // Convert RGB to luminance using the Rec. 709 formula
        double luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b;

        // Add to the total luminance
        totalLuminance += luminance;
    }

    delete[] data;

    // Calculate the average luminance for the screen
    return totalLuminance / numPixels;
}

int main(){
	cout << GetScreenLuminance();
	return 0;
}

