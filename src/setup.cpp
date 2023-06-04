# include "setup.h"

# include <fstream>
# include <windows.h>
# include <iostream>

# include "fileSentinel.h"
# include "intensitySentinel.h"

using namespace std;

bool setup(){
    ifstream cFile(CONFIG_FILE_NAME);

	if(cFile.good()){
        return true;
    } else{
        FileSentinel fSentinel;
        IntensitySentinel iSentinel;

        ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

        // Get the dark luminance value
        Sleep(1000);
        float minLum = iSentinel.getIntensity();

        // Get the bright luminance value
        system("color f0");
        Sleep(5000);
        float maxLum = iSentinel.getIntensity();

        cout << minLum << " " << maxLum;

        fSentinel.setLum(maxLum, minLum);
        fSentinel.~FileSentinel();

        // Set the defaults back
        ShowWindow(GetConsoleWindow(), SW_NORMAL);
        system("color 07");
        ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
        return true;
    }

    return false;
}