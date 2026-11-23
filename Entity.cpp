#include "Entity.h"
#include <stdexcept>

Entity::Entity()
{
    id = 0;
}

Entity::Entity(int id)
{
    if (id <= 0)
    {
        throw std::invalid_argument("Id musi byc dodatnie");
    }
    this->id = id;
}

Entity::~Entity()
{
}

int Entity::getId() const
{
    return id;
}
