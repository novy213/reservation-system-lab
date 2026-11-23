#include "Room.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

Room::Room() : Entity(), beds(0), pricePerNight(0)
{
}

Room::Room(int number, int beds, double pricePerNight)
    : Entity(number), beds(0), pricePerNight(0)
{
    setBeds(beds);
    setPricePerNight(pricePerNight);
}

int Room::getNumber() const {
    return getId();
}

int Room::getBeds() const {
    return beds;
}

double Room::getPricePerNight() const {
    return pricePerNight;
}

void Room::setBeds(int beds) {
    if (beds <= 0) {
        throw invalid_argument("Liczba lozek musi byc dodatnia");
    }
    this->beds = beds;
}

void Room::setPricePerNight(double pricePerNight) {
    if (!isfinite(pricePerNight) || pricePerNight <= 0) {
        throw invalid_argument("Cena musi byc dodatnia");
    }
    this->pricePerNight = pricePerNight;
}

void Room::show() const {
    cout << "Pokoj " << getNumber() << ", lozka: " << beds
         << ", cena za noc: " << pricePerNight << " zl" << endl;
}
