#ifndef ROOM_H
#define ROOM_H

class Room {
private:
    int number;
    int beds;
    double pricePerNight;

public:
    Room(int number, int beds, double pricePerNight);
    int getNumber();
    int getBeds();
    double getPricePerNight();
    void show();
};

#endif
