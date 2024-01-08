/**
 * @author Jaime Juan Claudio
 * @author JFK
*/

#include <queue>
#include <string>
#include <ctime>

#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"

class Logger{
    public:
        Logger();
        void addLog(std::string log);
        std::string remLog();
        void saveFile();

    private:
        std::queue<std::string> logs_;
};