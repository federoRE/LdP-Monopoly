#include <iostream>
#include "Logger.h"

using namespace std;

int main(void){
    Logger logger = Logger();
    try{
        logger.addLog("Riga uno");
        logger.addLog("Riga due");
        logger.addLog("Riga tre");
        //logger.saveFile();
    }catch(...){
        return 1;
    }
    return 0;
}