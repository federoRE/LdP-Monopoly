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
        Player& operator=(const Player& other);
        Player(const Player& other);
        Player(Player&& other);
        /**
         * @brief Overload of operator +
         * @param roll The roll to add to the player's position
         * @return The player's position after the roll
        */
        Player& operator+(int roll);

        /**
         * @brief Overload of operator -
         * @param roll The roll to subtract to the player's position
         * @return The player's position after the roll
        */
        Player& operator-(int roll);

        /**
         * @brief Overload of operator +=
         * @param roll The roll to add to the player's position
         * @return The player's position after the roll
        */
        Player& operator+=(int roll);

        /**
         * @brief Overload of operator -=
         * @param roll The roll to subtract to the player's position
         * @return The player's position after the roll
        */
        Player& operator-=(int roll);
        
        /**
         * @brief Overload of operator <=
         * @param pos The position to compare to
         * @return True if the player's position is less than or equal to the specified position
        */
        bool operator<=(const int pos) const;
        bool operator<(const int pos) const;
        friend std::ostream& operator<<(std::ostream& os, const Player& player);

    private:
        int position_;
        int roll_;
        int fiorini_;
        bool bot_;
        bool isLose_;
        std::string name_;
};


#endif