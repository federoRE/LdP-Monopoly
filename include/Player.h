#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Player{

    public:
        //Costruttori
        Player();

        /**
         * @brief Construct a new Player object
         * @param bot Booleano che indica se il giocatore e' un bot
        */
        Player(bool bot);

        //Getter
        int getPos() const;
        int getFiorini() const;
        int getRoll() const;
        std::string getName() const;
        bool getIsLose() const;
        bool isBot() const;

        //Setter
        void setPos(int position);
        void setFiorini(int fiorini);
        void setRoll(int roll);
        void setName(std::string name);
        void setIsLose(bool isLose);

        //Functions
        void incPos(int roll);

        //Operator
        friend std::ostream& operator<<(std::ostream& os, const Player& player);
        Player& operator=(const Player& other);

    private:
        int position_;
        int roll_;
        int fiorini_;
        bool bot_;
        bool isLose_;
        std::string name_;
};

#endif