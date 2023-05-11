#ifndef consoleSentinel_h
#define consoleSentinel_h

    #ifndef string
        #include <string>
    #endif

    std::string exec(const char* cmd);
    int getBrightness();
    void setBrightness(int level);

#endif