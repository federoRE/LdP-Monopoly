#include "Player.h"

Player::Player(bool bot){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    this->bot_ = bot;
}

int Player::getPos(){
    return position_;
}

int Player::getFiorini(){
    return fiorini_;
}

int Player::getRoll(){
    return roll_;
}

void Player::setPos(int position){
    this->position_ = position;
}

void Player::setFiorini(int fiorini){
    this->fiorini_ = fiorini;
}

void Player::setRoll(int roll){
    this->roll_ = roll;
}

bool Player::isBot(){
    return bot_;
}

bool Player::isLose(){
    return fiorini_ < 0;
}

void Player::incPos(int roll){
    position_ += roll;
}