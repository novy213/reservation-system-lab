#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"

class Room : public Entity {
private:
    int beds;
    double pricePerNight;

public:
    Room();
    Room(int number, int beds, double pricePerNight);
    int getNumber() const;
    int getBeds() const;
    double getPricePerNight() const;
    void setBeds(int beds);
    void setPricePerNight(double pricePerNight);
    void show() const override;
};

#endif
