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
    /**
     * @brief Get the Pos value
     * @return Player's position
    */
    int getPos() const;

    /**
     * @brief Get  Fiorini value
     * @return Player's fiorini
    */
    int getFiorini() const;

    /**
     * @brief Get the Roll value
     * @return Player's last roll
    */
    int getRoll() const;

    /**
     * @brief Get the Name of player
     * @return Player's name
    */
    std::string getName() const;

    /**
     * @brief Get if the player has lost
     * @return True if the player has lost
    */
    bool getIsLose() const;

    /**
     * @brief Get the Id of player
     * @return Player's id
    */
    int getId() const;

    /**
     * @brief Get if the player is a bot
     * @return True if the player is a bot
    */
    bool isBot() const;

    //Setter
    /**
     * @brief Set the Pos value
     * @param position The new position
    */
    void setPos(int position);

    /**
     * @brief Set Fiorini
     * @param fiorini The new value of fiorini
    */
    void setFiorini(int fiorini);

    /**
     * @brief Set the Roll value
     * @param roll The new value of roll
    */
    void setRoll(int roll);

    /**
     * @brief Set the Name of player
     * @param name The new name
    */
    void setName(std::string name);

    /**
     * @brief Set the Id of player
     * @param id The new id
    */
    void setId(int id);

    /**
     * @brief Set if the player has lost
     * @param isLose True if the player has lost
    */
    void setIsLose(bool isLose);

    //Functions
    /**
     * @brief Increment the player's position
     * @param roll The roll to add to the player's position
    */
    void incPos(int roll);

    /**
     * @brief Check if 2 players are equals
     * @param other The player to compare to
     * @return True if the 2 players are equals
    */
    bool equals(const Player& other) const;

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
    int id_;
};


#endif