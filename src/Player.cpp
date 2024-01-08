#include "Player.h"


// Constructor

Player::Player(){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    bot_ = true;
    isLose_ = false;
    id_ = -1;
}

Player::Player(bool bot){
    position_ = 0;
    roll_ = 1;
    fiorini_ = 100;
    bot_ = bot;
    isLose_ = false;
    id_ = -1;
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

int Player::getId() const{
    return id_;
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

void Player::setId(int id){
    id_ = id;
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

bool Player::equals(const Player& other) const {
    return this == &other;
}


// Operator

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Position: " << player.getPos() << ", ";
    os << "Fiorini: " << player.getFiorini() << ", ";
    os << "Last roll: " << player.getRoll();
    return os;
}


Player& Player::operator=(const Player& other) {
    if (this != &other) {
        position_ = other.position_;
        roll_ = other.roll_;
        fiorini_ = other.fiorini_;
        bot_ = other.bot_;
        isLose_ = other.isLose_;
        name_ = other.name_;
        id_ = other.id_;
    }
    return *this;
}

Player::Player(const Player& other) {
    position_ = other.position_;
    roll_ = other.roll_;
    fiorini_ = other.fiorini_;
    bot_ = other.bot_;
    isLose_ = other.isLose_;
    name_ = other.name_;
    id_ = other.id_;
}

Player::Player(Player&& other) {
    position_ = other.position_;
    roll_ = other.roll_;
    fiorini_ = other.fiorini_;
    bot_ = other.bot_;
    isLose_ = other.isLose_;
    name_ = other.name_;
    id_ = other.id_;
}

Player& Player::operator+(int roll) {
    this->position_ = (position_ + roll)%28;
    this->roll_ = roll;
    return *this;
}

Player& Player::operator-(int roll) {
    this->position_ -= (position_ - roll)%28;
    this->roll_ = roll;
    return *this;
}

Player& Player::operator+=(int roll) {
    this->position_ += roll;
    this->position_ %= 28;
    this->roll_ = roll;
    return *this;
}

Player& Player::operator-=(int roll) {
    this->position_ -= roll;
    this->position_ %= 28;
    this->roll_ = roll;
    return *this;
}

bool Player::operator<=(const int pos) const {
    return position_ <= pos;
}

bool Player::operator<(const int pos) const {
    return position_ < pos;
}


