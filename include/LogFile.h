//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_LOGFILE_H
#define MY_APPLICATION_LOGFILE_H

#include <fstream>

class LogFile {
private:
    std::ofstream file;
public:
    LogFile(std::string path);
    void write(const std::string fmt, ...);
};


#endif //MY_APPLICATION_LOGFILE_H
