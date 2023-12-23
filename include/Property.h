#include <string>
#include "Player.h"

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
    */
    Property(
        char* prop_class, 
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