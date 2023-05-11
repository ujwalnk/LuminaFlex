#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

/**
 * Execute cmd in Windows Cmd
*/
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
    return atoi(exec("powershell -Command \"Get-Ciminstance -Namespace root/WMI -ClassName WmiMonitorBrightness | Select -ExpandProperty \"CurrentBrightness\"\"").c_str());
}

void setBrightness(int level){

    /*char* command = "powershell (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1,";
    sprintf(command, "%d", level);
    command = "powershell (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1,"
    ;
    cout << command;
*/


    string commandString = "powershell (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1,";
    commandString += to_string(level);
    commandString += ")";
    cout << commandString << endl;
    exec(commandString.c_str());
}