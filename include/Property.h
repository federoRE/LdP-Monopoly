#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
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
    char prop_class_; // Low, Medium, High value
    Player* owner_; // Owner of the property

    // Property's value
    int land_value_;
    int house_value_;
    int hotel_value_;
    // Property's rent
    int house_rent_;
    int hotel_rent_;

    int level_; // Property's level: 0 = land, 1 = house, 2 = hotel)

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
        {};


    bool isPropFree() const;

    bool isUpgradeable() const;

    void upgrade();

    // Setters
    void setOwner(Player* owner);
    void setLegenda(std::string cell_id_legenda);

    // Getters
    Player* getOwner() const;
    std::string getLegenda() const;

};

#endif // PROPERTY_H