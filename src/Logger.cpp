#include "Logger.h"
#include <iostream>
#include <fstream>

Logger::Logger() {
}

void Logger::addLog(std::string log){
    std::cout<<log<<std::endl;
    logs_.push(log);
}

std::string Logger::remLog(){
    std::string log = logs_.front();
    logs_.pop();
    return log;
}

void Logger::saveFile(){
    std::ofstream file;
    std::string log_pre = "log";
    std::string log_ext = ".txt";

    // Aggiungi il timestamp al nome del file di log
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%d%m%Y%H%M%S", std::localtime(&now));
    std::string log_filename = log_pre + "_" + timestamp + log_ext;

    file.open(log_filename, std::ios::out | std::ios::trunc);
    while(!logs_.empty()){
        file << logs_.front() << std::endl; 
        logs_.pop();
    }
    file.close();
}
