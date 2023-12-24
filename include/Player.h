#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Player{

    public:
        //Costruttori
        Player();
        Player(bool bot);

        //Booleani
        bool isLose();
        bool isBot();

        //Getter
        int getPos() const;
        int getFiorini() const;
        int getRoll() const;
        std::string getName() const;

        //Setter
        void setPos(int position);
        void setFiorini(int fiorini);
        void setRoll(int roll);
        std::string setName(std::string name);

        //Functions
        void incPos(int roll);

        //Operator
        friend std::ostream& operator<<(std::ostream& os, const Player& player);

    private:
        int position_;
        int roll_;
        int fiorini_;
        bool bot_;
        std::string name_;
};

#endif