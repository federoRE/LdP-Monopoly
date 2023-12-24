#include "Player.h"


// Constructor

Player::Player(){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    bot_ = true;
}

Player::Player(bool bot){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    bot_ = bot;
}


// Getter

int Player::getPos() const{
    return position_;
}

int Player::getFiorini() const{
    return fiorini_;
}

int Player::getRoll() const{
    return roll_;
}

std::string Player::getName() const{
    return name_;
}


// Setter

void Player::setPos(int position){
    position_ = position;
}

void Player::setFiorini(int fiorini){
    fiorini_ = fiorini;
}

void Player::setRoll(int roll){
    roll_ = roll;
}

std::string Player::setName(std::string name){
    name_ = name;
}


// Functions

bool Player::isBot(){
    return bot_;
}

bool Player::isLose(){
    return fiorini_ < 0;
}

void Player::incPos(int roll){
    position_ += roll;
}


// Operator

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Position: " << player.getPos() << ", ";
    os << "Fiorini: " << player.getFiorini() << ", ";
    os << "Roll: " << player.getRoll();
    return os;
}