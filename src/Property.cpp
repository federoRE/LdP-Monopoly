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