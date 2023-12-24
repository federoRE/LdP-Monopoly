#include "Logger.h"
#include <fstream>

Logger::Logger() {
}

void Logger::addLog(std::string log){
    logs_.push(log);
}

// integrabile in saveFile
std::string Logger::remLog(){
    std::string log = logs_.front();
    logs_.pop();
    return log;
}

void Logger::saveFile(){
    std::ofstream file;
    file.open("log.txt");
    while(!logs_.empty()){
        file << logs_.front() << std::endl; 
        logs_.pop();
    }
    file.close();
}
