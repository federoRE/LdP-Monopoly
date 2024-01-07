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
    
    /**
     * @brief Check if property is free
     * @return True if property is free, false otherwise
    */
    bool isPropFree() const;

    /**
     * @brief Check if property is owned
     * @return True if property is owned, false otherwise
    */
    bool isPropOwned() const;

    /**
     * @brief Check if property is owned by a specific player
     * @param player Player to check
     * @return True if property is owned by player, false otherwise
    */
    bool isPropOwnedBy(Player* player) const;

    /**
     * @brief Check if property is upgradeable
     * @return True if property is upgradeable, false otherwise
    */
    bool isUpgradeable() const;

    /**
     * @brief Upgrade property if possible
    */
    void upgrade();

    // Setters
    /**
     * @brief Set property's owner
     * @param owner Property's owner
    */
    void setOwner(Player* owner);

    /**
     * @brief Set property's cell id legenda
     * @param cell_id_legenda Property's cell id legenda
    */
    void setLegenda(std::string cell_id_legenda);

    /**
     * @brief Set if property's edge
    */
    void setEdge();

    // Getters
    /**
     * @brief Get property's owner
     * @return Property's owner
    */
    Player* getOwner() const;

    /**
     * @brief Get property's cell id legenda
     * @return Property's cell id legenda
    */
    std::string getLegenda() const;

    /**
     * @brief Get property's class
     * @return Property's class
    */
    char getPropClass() const;

    /**
     * @brief Get property's land value
     * @return Property's land value
    */
    int getLandValue() const;

    /**
     * @brief Get property's house value
     * @return Property's house value
    */
    int getHouseValue() const;

    /**
     * @brief Get property's hotel value
     * @return Property's hotel value
    */
    int getHotelValue() const;

    /**
     * @brief Get property's house rent
     * @return Property's house rent
    */
    int getHouseRent() const;

    /**
     * @brief Get property's hotel rent
     * @return Property's hotel rent
    */
    int getHotelRent() const;

    /**
     * @brief Get property's level
     * @return Property's level
    */
    int getLevel() const;

    /**
     * @brief Check if is edge
     * @return True if is edge, false otherwise
    */
    bool isEdge() const;

    // Operators
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