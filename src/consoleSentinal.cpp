#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace std;

string exec(const char* cmd) {
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

int getBrightness(){
    return stoi(exec("powershell -Command \"Get-Ciminstance -Namespace root/WMI -ClassName WmiMonitorBrightness | Select -ExpandProperty \"CurrentBrightness\"\""));
}

void setBrightness(int level){
    exec("powershell (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1," + level + ')');
}