/**
 * Author: Ujwal N K
 * Date Create: 12 May, 2023
 */

#ifndef fileSentinel_h
#define fileSentinel_h

	#ifndef bool
		#include <stdbool.h>
	#endif

	#define CONFIG_FILE_NAME ".config"

    class FileSentinel{
        private:

			struct configData{
				int delta = 0;
				float interval = 5;
				float maxLum = -1;
				float minLum = -1;
				bool useGammaRamp = false;
			} data;

            void readConfig();
			void writeConfig();
        public:
			FileSentinel();

			int getDelta();
			float getInterval();
			float getMaxLum();
			float getMinLum();
			bool getUseGammaRamp();

			void setDelta(int level);
			void setInterval(float interval);
			void setLum(float max, float min);
			void setUseGammaRamp(bool b);            
    };

#endif