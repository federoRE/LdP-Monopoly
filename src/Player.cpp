#include "Player.h"


// Constructor

Player::Player(){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    bot_ = true;
    isLose_ = false;
}

Player::Player(bool bot){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    bot_ = bot;
    isLose_ = false;
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

bool Player::getIsLose() const{
    return isLose_;
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

void Player::setName(std::string name){
    name_ = name;
}

void Player::setIsLose(bool isLose){
    isLose_ = isLose;
}


// Functions

bool Player::isBot() const{
    return bot_;
}

void Player::incPos(int roll){
    position_ += roll;
}


// Operator

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Position: " << player.getPos() << ", ";
    os << "Fiorini: " << player.getFiorini() << ", ";
    os << "Last roll: " << player.getRoll();
    return os;
}