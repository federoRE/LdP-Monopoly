#include <queue>
#include <string>

class Logger{
    public:
        Logger();
        void addLog(std::string log);
        std::string remLog();
        void saveFile();

    private:
        std::queue<std::string> logs;
};