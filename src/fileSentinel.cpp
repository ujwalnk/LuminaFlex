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
	ifstream cFile(CONFIG_FILE_NAME);

	if(cFile.good()){
		// Check if the file exists and read from it
		cFile >> data.delta;
		cFile >> data.useGammaRamp;
		cFile >> data.maxLum;
		cFile >> data.minLum;
	} else{
		// Create file with defaults if file not exists
		cFile.close();
		ofstream cFile(CONFIG_FILE_NAME);
		
		cFile << 0 << endl
		      << false << endl
			  << -1 << endl
			  << -1 << endl;

		cFile.close();
	}

	cFile.close();
}

/**
 * Store the config data into file
*/
void FileSentinel::writeConfig(){
	ofstream cfile(CONFIG_FILE_NAME);
	cfile << data.delta << endl 
		  << data.useGammaRamp << endl
		  << data.maxLum << endl
		  << data.minLum;

	cfile.close();
}

/**
 * Getter: delta
 * @return (int): Delta
*/
int FileSentinel::getDelta(){
	return data.delta;
}

/**
 * Getter: maxBrightness 
 * @return (float): Maximum Brightness
*/
float FileSentinel::getMaxLum(){
	return data.maxLum;
}

/**
 * Getter: mixBrightness 
 * @return (float): Minimum Brightness
*/
float FileSentinel::getMinLum(){
	return data.minLum;
}

/**
 * Getter: userGammaRamp
 * @return (bool): useGammaRamp
*/
bool FileSentinel::getUseGammaRamp(){
	return data.useGammaRamp;
}

/**
 * Setter: Delta
 * @param level(int): Delta Quantity
*/
void FileSentinel::setDelta(int level){
	data.delta = level;
}

/**
 * Setter: Min, Max Brightness
 * @param max(float): Maximum Lum
 * @param min(float): Minimum Lum
*/
void FileSentinel::setLum(float max, float min){
	data.maxLum = max;
	data.minLum = min;

}

/**
 * Setter: useGammaRamp
 * @param b(bool): true / false
*/
void FileSentinel::setUseGammaRamp(bool b){
	data.useGammaRamp = b;
}