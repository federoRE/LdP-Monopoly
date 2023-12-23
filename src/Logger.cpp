#include "Logger.h"
#include <fstream>

Logger::Logger() {
}

void Logger::addLog(std::string log){
    logs.push(log);
}

std::string Logger::remLog(){
    std::string log = logs.front();
    logs.pop();
    return log;
}

void Logger::saveFile(){
    std::ofstream file;
    file.open("log.txt");
    while(!logs.empty()){
        file << remLog() << std::endl;
    }
    file.close();
}
