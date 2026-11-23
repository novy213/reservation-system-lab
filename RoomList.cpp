#include "RoomList.h"
#include <iostream>
using namespace std;

RoomList::Reservation::Reservation(int roomNumber, DateTime startDate, DateTime endDate)
    : roomNumber(roomNumber), startDate(startDate), endDate(endDate)
{
}

bool RoomList::add(int number, int beds, double pricePerNight)
{
    if (number <= 0 || beds <= 0 || pricePerNight <= 0)
    {
        return false;
    }
    if (findByNumber(number) != NULL)
    {
        return false;
    }
    rooms.push_back(Room(number, beds, pricePerNight));
    return true;
}

Room *RoomList::findByNumber(int number)
{
    for (int i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].getNumber() == number)
        {
            return &rooms[i];
        }
    }
    return NULL;
}

void RoomList::showAll()
{
    if (rooms.size() == 0)
    {
        cout << "Brak pokoi" << endl;
        return;
    }
    for (int i = 0; i < rooms.size(); i++)
    {
        rooms[i].show();
    }
}

void RoomList::showWithMinBeds(int minBeds)
{
    bool found = false;
    for (int i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].getBeds() >= minBeds)
        {
            rooms[i].show();
            found = true;
        }
    }
    if (!found)
    {
        cout << "Nie ma pokoju z taka liczba lozek" << endl;
    }
}

int RoomList::count()
{
    return rooms.size();
}

bool RoomList::addReservation(int number, DateTime startDate, DateTime endDate)
{
    if (endDate.date <= startDate.date)
    {
        return false;
    }
    if (!checkAvailability(number, startDate, endDate))
    {
        return false;
    }
    reservations.push_back(Reservation(number, startDate, endDate));
    return true;
}

bool RoomList::checkAvailability(int number, DateTime startDate, DateTime endDate)
{
    if (findByNumber(number) == NULL || endDate.date <= startDate.date)
    {
        return false;
    }
    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].roomNumber == number &&
            startDate.date < reservations[i].endDate.date &&
            endDate.date > reservations[i].startDate.date)
        {
            return false;
        }
    }
    return true;
}