#include <iostream>
#include <string>
#include <stdexcept>
#include "ClientList.h"
#include "RoomList.h"
using namespace std;

int readInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "To nie jest liczba, sprobuj jeszcze raz: ";
    }
    return x;
}

double readDouble() {
    double x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "To nie jest liczba, sprobuj jeszcze raz: ";
    }
    return x;
}

DateTime readDate(string message) {
    string date;
    while (true) {
        cout << message;
        cin >> date;
        try {
            return DateTime(date);
        } catch (const exception& e) {
            cout << "Blad daty: " << e.what() << endl;
        }
    }
}

void showMenu() {
    cout << endl;
    cout << "=== SYSTEM REZERWACJI ===" << endl;
    cout << "1. Dodaj klienta" << endl;
    cout << "2. Pokaz klientow" << endl;
    cout << "3. Dodaj pokoj" << endl;
    cout << "4. Pokaz pokoje" << endl;
    cout << "5. Szukaj pokoju (min. liczba lozek)" << endl;
    cout << "6. Dodaj rezerwacje" << endl;
    cout << "7. Sprawdz dostepnosc pokoju" << endl;
    cout << "0. Wyjscie" << endl;
    cout << "Wybor: ";
}

int main() {
    ClientList clients;
    RoomList rooms;
    int choice = -1;

    while (choice != 0) {
        showMenu();
        choice = readInt();

        if (choice == 1) {
            string name, surname, phone;
            cout << "Imie: ";
            cin >> name;
            cout << "Nazwisko: ";
            cin >> surname;
            cout << "Telefon (9 cyfr): ";
            cin >> phone;
            if (clients.add(name, surname, phone)) {
                cout << "Dodano klienta" << endl;
            } else {
                cout << "Blad: zly numer telefonu albo taki numer juz istnieje" << endl;
            }
        } else if (choice == 2) {
            clients.showAll();
        } else if (choice == 3) {
            cout << "Numer pokoju: ";
            int number = readInt();
            cout << "Liczba lozek: ";
            int beds = readInt();
            cout << "Cena za noc: ";
            double price = readDouble();
            if (rooms.add(number, beds, price)) {
                cout << "Dodano pokoj" << endl;
            } else {
                cout << "Blad: zle dane albo taki pokoj juz istnieje" << endl;
            }
        } else if (choice == 4) {
            rooms.showAll();
        } else if (choice == 5) {
            cout << "Ile lozek minimum: ";
            int minBeds = readInt();
            rooms.showWithMinBeds(minBeds);
        } else if (choice == 6) {
            cout << "Numer pokoju: ";
            int number = readInt();
            DateTime startDate = readDate("Data przyjazdu (rrrr-mm-dd): ");
            DateTime endDate = readDate("Data wyjazdu (rrrr-mm-dd): ");
            if (rooms.findByNumber(number) == NULL) {
                cout << "Nie ma takiego pokoju" << endl;
            } else if (endDate.date <= startDate.date) {
                cout << "Data wyjazdu musi byc pozniejsza niz przyjazdu" << endl;
            } else if (rooms.addReservation(number, startDate, endDate)) {
                cout << "Dodano rezerwacje" << endl;
            } else {
                cout << "Pokoj jest zajety w tym terminie" << endl;
            }
        } else if (choice == 7) {
            cout << "Numer pokoju: ";
            int number = readInt();
            DateTime startDate = readDate("Data przyjazdu (rrrr-mm-dd): ");
            DateTime endDate = readDate("Data wyjazdu (rrrr-mm-dd): ");
            if (rooms.findByNumber(number) == NULL) {
                cout << "Nie ma takiego pokoju" << endl;
            } else if (endDate.date <= startDate.date) {
                cout << "Data wyjazdu musi byc pozniejsza niz przyjazdu" << endl;
            } else if (rooms.checkAvailability(number, startDate, endDate)) {
                cout << "Pokoj jest dostepny" << endl;
            } else {
                cout << "Pokoj jest zajety w tym terminie" << endl;
            }
        } else if (choice != 0) {
            cout << "Nie ma takiej opcji" << endl;
        }
    }

    cout << "Koniec programu" << endl;
    return 0;
}
