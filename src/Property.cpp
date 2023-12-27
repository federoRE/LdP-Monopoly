#include "Property.h"

bool Property::isPropFree() const
{
    return (owner_ == nullptr);
}

bool Property::isUpgradeable() const
{
    return (level_ < 2);
}

void Property::upgrade()
{
    if (isUpgradeable())
    {
        level_++;
    }
}

void Property::setOwner(Player* owner)
{
    owner_ = owner;
}

void Property::setLegenda(std::string cell_id_legenda)
{
    cell_id_legenda_ = cell_id_legenda;
}

Player* Property::getOwner() const
{
    return owner_;
}

std::string Property::getLegenda() const
{
    return cell_id_legenda_;
}

char Property::getPropClass() const
{
    return prop_class_;
}

int Property::getLandValue() const
{
    return land_value_;
}

int Property::getHouseValue() const
{
    return house_value_;
}

int Property::getHotelValue() const
{
    return hotel_value_;
}

int Property::getHouseRent() const
{
    return house_rent_;
}

int Property::getHotelRent() const
{
    return hotel_rent_;
}

std::ostream& operator<<(std::ostream& os, const Property& property)
{
    os << "Property Details:" << std::endl;
    os << "Owner: " << (property.owner_ ? property.owner_->getName() : "None") << std::endl;
    os << "Legenda: " << property.cell_id_legenda_ << std::endl;
    os << "Property Class: " << property.prop_class_ << std::endl;
    os << "Land Value: " << property.land_value_ << std::endl;
    os << "House Value: " << property.house_value_ << std::endl;
    os << "Hotel Value: " << property.hotel_value_ << std::endl;
    os << "House Rent: " << property.house_rent_ << std::endl;
    os << "Hotel Rent: " << property.hotel_rent_ << std::endl;

    return os;
}

Property& Property::operator=(const Property& other)
{
    if (this != &other)
    {
        owner_ = other.owner_;
        cell_id_legenda_ = other.cell_id_legenda_;
        prop_class_ = other.prop_class_;
        land_value_ = other.land_value_;
        house_value_ = other.house_value_;
        hotel_value_ = other.hotel_value_;
        house_rent_ = other.house_rent_;
        hotel_rent_ = other.hotel_rent_;
    }
    return *this;
}

bool Property::operator==(const Property& other) const
{
    return (cell_id_legenda_ == other.cell_id_legenda_);
}

Property::~Property()
{
    // std::cout << "Property destroyed" << std::endl;
}