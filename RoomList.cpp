#include "RoomList.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

RoomList::Reservation::Reservation(int roomNumber, int clientId, DateTime startDate, DateTime endDate)
    : roomNumber(roomNumber), clientId(clientId), startDate(startDate), endDate(endDate)
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

bool RoomList::addReservation(int number, int clientId, DateTime startDate, DateTime endDate)
{
    if (clientId <= 0 || endDate.date <= startDate.date)
    {
        return false;
    }
    if (!checkAvailability(number, startDate, endDate))
    {
        return false;
    }
    reservations.push_back(Reservation(number, clientId, startDate, endDate));
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

void RoomList::showReservationsForClient(int clientId)
{
    bool found = false;
    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].clientId == clientId)
        {
            cout << "Pokoj " << reservations[i].roomNumber
                 << ", od " << reservations[i].startDate.date
                 << " do " << reservations[i].endDate.date << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Brak rezerwacji dla tego klienta" << endl;
    }
}

bool RoomList::save(ostream& output)
{
    output << rooms.size() << endl;
    output << setprecision(17);
    for (int i = 0; i < rooms.size(); i++)
    {
        output << rooms[i].getNumber() << " "
               << rooms[i].getBeds() << " "
               << rooms[i].getPricePerNight() << endl;
    }

    output << reservations.size() << endl;
    for (int i = 0; i < reservations.size(); i++)
    {
        output << reservations[i].roomNumber << " "
               << reservations[i].clientId << " "
               << reservations[i].startDate.date << " "
               << reservations[i].endDate.date << endl;
    }
    return output.good();
}

bool RoomList::load(istream& input)
{
    int numberOfRooms;
    if (!(input >> numberOfRooms) || numberOfRooms < 0)
    {
        return false;
    }

    RoomList loadedRooms;
    for (int i = 0; i < numberOfRooms; i++)
    {
        int number, beds;
        double price;
        if (!(input >> number >> beds >> price) ||
            !loadedRooms.add(number, beds, price))
        {
            return false;
        }
    }

    int numberOfReservations;
    if (!(input >> numberOfReservations) || numberOfReservations < 0)
    {
        return false;
    }

    for (int i = 0; i < numberOfReservations; i++)
    {
        int number, clientId;
        string startDateText, endDateText;
        if (!(input >> number >> clientId >> startDateText >> endDateText))
        {
            return false;
        }
        try
        {
            DateTime startDate(startDateText);
            DateTime endDate(endDateText);
            if (!loadedRooms.addReservation(number, clientId, startDate, endDate))
            {
                return false;
            }
        }
        catch (const exception&)
        {
            return false;
        }
    }

    rooms = loadedRooms.rooms;
    reservations = loadedRooms.reservations;
    return true;
}