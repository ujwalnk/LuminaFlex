/**
 * Author: Ujwal N K
 * Date Create: 11 May, 2023
 * Write & Read Config Data from files
 */

# include <fstream>
# include <iostream>
# include <string>

# include "fileSentinel.h"

# pragma GCC optimize("Ofast")

using namespace std;

/**
 * Constructor: Read data from file on object created
*/
FileSentinel::FileSentinel(){
	readConfig();
}

/**
 * Read config file data into configData struct
*/
void FileSentinel::readConfig(){
	ifstream cFile(configFileName);

	if(cFile.good()){
		// Check if the file exists and read from it
		cFile >> data.maxBrightness;
		cFile >> data.minBrightness;
		cFile >> data.useGammaRamp;
	} else{
		// Create empty file if file not exists
		cFile.close();
		ofstream cFile(configFileName);
		cFile.close();
	}

	cFile.close();
}

/**
 * Store the config data into file
*/
void FileSentinel::writeConfig(){
	ofstream cfile(configFileName);
	cfile << data.maxBrightness << endl 
		  << data.minBrightness << endl 
		  << data.useGammaRamp << endl;

	cfile.close();
}

/**
 * Get maxBrightness 
 * @return (int): Maximum Brightness
*/
int FileSentinel::getMaxBrightness(){
	return data.maxBrightness;
}

/**
 * Get minBrightness 
 * @return (int): Minimum Brightness
*/
int FileSentinel::getMinBrightness(){
	return data.minBrightness;
}

/**
 * Get userGammaRamp
 * @return (bool): useGammaRamp
*/
bool FileSentinel::getUseGammaRamp(){
	return data.useGammaRamp;
}


void FileSentinel::setMaxBrightness(int level){
	data.maxBrightness = level;
}

void FileSentinel::setMinBrightness(int level){
	data.minBrightness = level;
}

void FileSentinel::setUseGammaRamp(bool b){
	data.useGammaRamp = b;
}