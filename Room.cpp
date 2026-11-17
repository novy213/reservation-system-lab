#include "Room.h"
#include <iostream>
using namespace std;

Room::Room(int number, int beds, double pricePerNight) {
    this->number = number;
    this->beds = beds;
    this->pricePerNight = pricePerNight;
}

int Room::getNumber() {
    return number;
}

int Room::getBeds() {
    return beds;
}

double Room::getPricePerNight() {
    return pricePerNight;
}

void Room::show() {
    cout << "Pokoj " << number << ", lozka: " << beds << ", cena za noc: " << pricePerNight << " zl" << endl;
}
