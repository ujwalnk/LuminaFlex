/**
 * Source: Nir Sofer http://www.nirsoft.net/vc/change_screen_brightness.html
 * Copied On: 10 May, 2023
 */

#ifndef GAMMARAMP_H_
#define GAMMARAMP_H_

	#include <windows.h>

	class CGammaRamp {
		protected:
			HMODULE hGDI32;
			HDC hScreenDC;
			typedef BOOL(WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);

			Type_SetDeviceGammaRamp pGetDeviceGammaRamp;
			Type_SetDeviceGammaRamp pSetDeviceGammaRamp;

		public:
			CGammaRamp();
			~CGammaRamp();
			BOOL LoadLibrary();
			void FreeLibrary();
			BOOL LoadLibraryIfNeeded();
			BOOL SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
			BOOL GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
			BOOL SetBrightness(HDC hDC, WORD wBrightness);
	};
	
#endif