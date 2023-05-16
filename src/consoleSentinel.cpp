#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "consoleSentinel.h"

#pragma GCC optimize("Ofast")

using namespace std;

/**
 * Execute cmd in Windows Cmd
 * @param (const char*) cmd: command to execute
 */
string ConsoleSentinel::exec(const char* cmd) {
    char buffer[128];
    string result = "";

    // Open a pipe in read mode
    FILE* pipe = popen(cmd, "r");

    // Unable to Open pipe, throw error
    if (!pipe) throw runtime_error("popen() failed!");

    // Read contents line by line & append to buffer, result
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }

    // Close pipe & return
    pclose(pipe);
    return result;
}

/**
 * Get the current system brightness
 * @return (int): Brightness level of system
*/
int ConsoleSentinel::getBrightness() {
    return atoi(exec("powershell -Command \"Get-Ciminstance -Namespace root/WMI "
                   "-ClassName WmiMonitorBrightness | Select -ExpandProperty "
                   "\"CurrentBrightness\"\"")
                  .c_str());
}

/**
 * Set system brightness
 * @param (float) level: Brightness level
*/
void ConsoleSentinel::setBrightness(float level) {
    stringstream ss;
    ss << "powershell (Get-WmiObject -Namespace root/WMI -Class "
        << "WmiMonitorBrightnessMethods).WmiSetBrightness(1," << level << ')';
    exec(ss.str().c_str());
}