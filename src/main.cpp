#include <iostream>
#include <Windows.h>

#include "getScreenLuminance.h"
#include "setScreenBrightness.h"

#pragma comment(lib, "gdi32.lib")

using namespace std;

int main(){
	
	cout << getScreenLuminance();
	return 0;
}

