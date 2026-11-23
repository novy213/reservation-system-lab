#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
    int id;

protected:
    Entity();
    explicit Entity(int id);

public:
    virtual ~Entity();
    int getId() const;
    virtual void show() const = 0;
};

#endif
