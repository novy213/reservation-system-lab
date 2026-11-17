#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <vector>
#include "Room.h"
using namespace std;

class RoomList {
private:
    vector<Room> rooms;

public:
    bool add(int number, int beds, double pricePerNight);
    Room* findByNumber(int number);
    void showAll();
    void showWithMinBeds(int minBeds);
    int count();
};

#endif
