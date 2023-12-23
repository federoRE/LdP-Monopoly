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

