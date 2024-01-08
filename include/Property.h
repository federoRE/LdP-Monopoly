#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <iostream>

#include "Player.h"

/**
 * @brief Property class
 * 
 * TODO: gestire nome casella ('H7' ecc)
 * TODO: gestire casella in corner
*/

class Property
{
private:
    // Property's status
    char prop_class_; // L, S or E
    Player* owner_; // Owner of the property

    // Property's value
    int land_value_;
    int house_value_;
    int hotel_value_;
    // Property's rent
    int house_rent_;
    int hotel_rent_;

    int level_; // Property's level: 0 = land, 1 = house, 2 = hotel)
    bool isEdge_; // Property's edge: true = edge, false = not edge

    std::string cell_id_legenda_; // Property's cell id

public:
    // Constructor
    /**
     * @brief Construct a new Property object
     * @param prop_class Property's class value
     * @param land_value Property's land value
     * @param house_value Property's house value
     * @param hotel_value Property's hotel value
     * @param house_rent Property's house rent
     * @param hotel_rent Property's hotel rent
    */
    Property() : owner_(nullptr), level_(0) {
        prop_class_ = ' ';
        land_value_ = 0;
        house_value_ = 0;
        hotel_value_ = 0;
        house_rent_ = 0;
        hotel_rent_ = 0;
        cell_id_legenda_ = " ";
        owner_ = nullptr;
        isEdge_ = false;
    };

    Property(
        char prop_class, 
        int land_value, 
        int house_value, 
        int hotel_value, 
        int house_rent, 
        int hotel_rent
        ) 
        : 
        owner_(nullptr), 
        level_(0) 
        {
            prop_class_ = prop_class;
            land_value_ = land_value;
            house_value_ = house_value;
            hotel_value_ = hotel_value;
            house_rent_ = house_rent;
            hotel_rent_ = hotel_rent;
            cell_id_legenda_ = " ";
            owner_ = nullptr;
            isEdge_ = false;
        };

    /**
     * @brief Construct a new Property object for edges
     * @param prop_class Property's class value ('P' or ' ')
    */
    Property(char prop_class) : owner_(nullptr), isEdge_(true), prop_class_(prop_class)
        {
            land_value_ = 0;
            house_value_ = 0;
            hotel_value_ = 0;
            house_rent_ = 0;
            hotel_rent_ = 0;
            cell_id_legenda_ = " ";
        };

    bool isPropFree() const;
    bool isPropOwned() const;
    bool isPropOwnedBy(Player* player) const;
    //bool isPropOwnedBy(int player_id) const;

    bool isUpgradeable() const;
    void reset();
    void upgrade();

    // Setters
    void setOwner(Player* owner);
    void setLegenda(std::string cell_id_legenda);
    void setEdge();

    // Getters
    Player* getOwner() const;
    std::string getLegenda() const;
    char getPropClass() const;
    int getLandValue() const;
    int getHouseValue() const;
    int getHotelValue() const;
    int getHouseRent() const;
    int getHotelRent() const;
    int getLevel() const;
    bool isEdge() const;

    Property& operator=(const Property& other);
    bool operator==(const Property& other) const;
    bool operator!=(const Property& other) const;
    bool operator<(const Property& other) const;
    bool operator>(const Property& other) const;
    bool operator<=(const Property& other) const;
    bool operator>=(const Property& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Property& property);
};

#endif // PROPERTY_H