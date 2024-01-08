/**
 * @author Anastasia Jevremova
 * @author JFK
*/

#include <iostream>
#include "Logger.h"

using namespace std;

int main(void){
    Logger logger = Logger();
    logger.addLog("Riga wibgdauywbgd");
    logger.addLog("Riga dawdwadaw");
    logger.addLog("Riga trwwwwwwwe");
    logger.saveFile();
    return 0;
}