/**
 * Author: Ujwal N K
 * Date Create: 12 May, 2023
 */

#ifndef fileSentinel_h
#define fileSentinel_h

	#ifndef bool
		#include <stdbool.h>
	#endif

	#ifndef string
		#include <string>
	#endif

    class FileSentinel{
        private:

			const std::string configFileName = ".config";

			struct configData{
				int maxBrightness = -1;
				int minBrightness = -1;
				bool useGammaRamp = false;
			} data;

            void readConfig();
			void writeConfig();
        public:
			FileSentinel();

			int getMaxBrightness();
			int getMinBrightness();
			bool getUseGammaRamp();

            void setMaxBrightness(int level);
			void setMinBrightness(int level);
			void setUseGammaRamp(bool b);            
    };

#endif