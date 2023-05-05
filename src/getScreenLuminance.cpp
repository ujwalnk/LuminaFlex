/**
 * Author: Ujwal N K
 * Created On: 05 May, 2023
 * Get BitMap Image of the Screen & Calculate Luminesce 
**/

#include <Windows.h>
#include <stdint.h>

#include <iostream>

static int width;
static int height;

/**
 * Get the device context and dimensions of the primary display
 **/
void getScreenDimensions(HDC &hScreen) {
  hScreen = GetDC(NULL);
  width = GetDeviceCaps(hScreen, HORZRES);
  height = GetDeviceCaps(hScreen, VERTRES);
}

/**
 * Create compatible device context and bitmap for screen
 **/
HBITMAP createCompatibleScreenBitmap(HDC &hScreen, HDC &hDC) {
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

/**
 * Retrieve the bitmap data for specified bitmap
 **/
bool getBitmapData(HDC &hDC, HBITMAP &hBitmap, BITMAPINFO &bmi,
                   uint8_t *&data) {
  // Get Bitmap info
  if (GetDIBits(hDC, hBitmap, 0, bmi.bmiHeader.biHeight, NULL, &bmi,
                DIB_RGB_COLORS) > 0) {
    // Allocate memory to store bitmap data
    data = new uint8_t[bmi.bmiHeader.biSizeImage];

    // Store bit bitmap data into the buffer
    // Free on error
    if (GetDIBits(hDC, hBitmap, 0, bmi.bmiHeader.biHeight, data, &bmi,
                  DIB_RGB_COLORS) == 0) {
      delete[] data;
      data = NULL;
    }
  }
  return data != NULL;
}

/**
 * Calculate the luminance of a single pixel using the Rec. 709 formula
 **/
double calculatePixelLuminance(uint8_t *pixel) {
  uint8_t r = *(pixel + 2);
  uint8_t g = *(pixel + 1);
  uint8_t b = *pixel;
  return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

/**
 * Set Bitmap image parameters
 */
void setBitmapInfo(BITMAPINFO &bmi) {
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
double getScreenLuminance() {
  HDC hScreen, hDC;
  getScreenDimensions(hScreen);
  HBITMAP hBitmap = createCompatibleScreenBitmap(hScreen, hDC);

  BITMAPINFO bmi = {};
  setBitmapInfo(bmi);

  uint8_t *data = NULL;

  // Error & Return on fail
  if (!getBitmapData(hDC, hBitmap, bmi, data)) {
    std::cerr << "Failed to get screen bitmap data" << std::endl;
    return -1;
  }

  // Calculate Sum of Luminance values
  double totalLuminance = 0.0;
  for (int i = 0; i < (width * height); i++) {
    uint8_t *pixel = data + (i * 4);
    double luminance = calculatePixelLuminance(pixel);
    totalLuminance += luminance;
  }

  // Free and return average luminance
  delete[] data;

  return totalLuminance / (width * height);
}