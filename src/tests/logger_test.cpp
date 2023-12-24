#include <iostream>
#include "Logger.h"

using namespace std;

int main(void){
    Logger logger = Logger();
    logger.addLog("Riga uno");
    logger.addLog("Riga due");
    logger.addLog("Riga tre");
    logger.saveFile();
    return 0;
}