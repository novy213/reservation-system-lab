#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <vector>
#include <iosfwd>
#include "Room.h"
#include "DateTime.h"
using namespace std;

class RoomList
{
private:
    struct Reservation
    {
        int roomNumber;
        int clientId;
        DateTime startDate;
        DateTime endDate;

        Reservation(int roomNumber, int clientId, DateTime startDate, DateTime endDate);
    };

    vector<Room> rooms;
    vector<Reservation> reservations;

public:
    bool add(int number, int beds, double pricePerNight);
    Room *findByNumber(int number);
    void showAll();
    void showWithMinBeds(int minBeds);
    int count();
    bool addReservation(int number, int clientId, DateTime startDate, DateTime endDate);
    bool checkAvailability(int number, DateTime startDate, DateTime endDate);
    void showReservationsForClient(int clientId);
    bool save(ostream& output);
    bool load(istream& input);
};

#endif
