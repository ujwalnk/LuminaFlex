#ifndef consoleSentinel_h
#define consoleSentinel_h

    #ifndef string
        #include <string>
    #endif

    class ConsoleSentinel{
        private:
            std::string exec(const char* cmd);
        public:
            int getBrightness();
            void setBrightness(float level);
    };

#endif