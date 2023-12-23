#include "Player.h"

Player::Player(bool bot){
    position = 0;
    roll = 1;
    fiorini = 100;
    this->bot = bot;
}

int Player::getPos(){
    return position;
}

int Player::getFiorini(){
    return fiorini;
}

int Player::getRoll(){
    return roll;
}

void Player::setPos(int position){
    this->position = position;
}

void Player::setFiorini(int fiorini){
    this->fiorini = fiorini;
}

void Player::setRoll(int roll){
    this->roll = roll;
}

bool Player::isBot(){
    return bot;
}

bool Player::isLose(){
    if (fiorini < 0)
        return true; 
}

void Player::incPos(int roll){
    position += roll;
}