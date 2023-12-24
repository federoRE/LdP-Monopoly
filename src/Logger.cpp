#include "Logger.h"
#include <fstream>

Logger::Logger() {
}

void Logger::addLog(std::string log){
    logs.push(log);
}

std::string Logger::remLog(){
    std::string log = logs_.front();
    logs_.pop();
    return log;
}

void Logger::saveFile(){
    std::ofstream file;
    file.open("log.txt");
    while(!logs_.empty()){
        file << remLog() << std::endl;
    }
    file.close();
}
