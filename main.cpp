#include <iostream>
#include <fstream>
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

void clearScreen() {
    cout << "\033[2J\033[H";
}

void waitForEnter() {
    cout << endl << "Nacisnij Enter, aby wrocic do menu...";
    cin.ignore(1000, '\n');
    cin.get();
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

bool saveState(ClientList& clients, RoomList& rooms) {
    ofstream output("stan_aplikacji.txt");
    if (!output) {
        return false;
    }
    if (!clients.save(output) || !rooms.save(output)) {
        return false;
    }
    output.close();
    return output.good();
}

bool loadState(ClientList& clients, RoomList& rooms) {
    ifstream input("stan_aplikacji.txt");
    ClientList loadedClients;
    RoomList loadedRooms;
    if (!loadedClients.load(input) ||
        !loadedRooms.load(input)) {
        return false;
    }
    string extraData;
    if (input >> extraData) {
        return false;
    }

    clients = loadedClients;
    rooms = loadedRooms;
    return true;
}

void showMenu(int clientCount, int roomCount) {
    cout << endl;
    cout << "========================================" << endl;
    cout << "           SYSTEM REZERWACJI" << endl;
    cout << "========================================" << endl;
    cout << "Klienci: " << clientCount << " | Pokoje: " << roomCount << endl;
    cout << "----------------------------------------" << endl;
    cout << "KLIENCI" << endl;
    cout << "  [1] Dodaj klienta" << endl;
    cout << "  [2] Pokaz klientow" << endl;
    cout << "  [10] Historia rezerwacji klienta" << endl;
    cout << "  [11] Edytuj klienta" << endl;
    cout << "  [12] Usun klienta" << endl;
    cout << endl;
    cout << "POKOJE I REZERWACJE" << endl;
    cout << "  [3] Dodaj pokoj" << endl;
    cout << "  [4] Pokaz pokoje" << endl;
    cout << "  [5] Szukaj pokoju wedlug liczby lozek" << endl;
    cout << "  [6] Dodaj rezerwacje" << endl;
    cout << "  [7] Sprawdz dostepnosc pokoju" << endl;
    cout << "  [13] Edytuj pokoj" << endl;
    cout << "  [14] Usun pokoj" << endl;
    cout << endl;
    cout << "ZAPIS I ODCZYT" << endl;
    cout << "  [8] Zapisz stan aplikacji" << endl;
    cout << "  [9] Odczytaj stan aplikacji" << endl;
    cout << "----------------------------------------" << endl;
    cout << "  [0] Wyjscie" << endl;
    cout << "Wybor: ";
}

int main() {
    ClientList clients;
    RoomList rooms;
    int choice = -1;

    while (choice != 0) {
        clearScreen();
        showMenu(clients.count(), rooms.count());
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
            cout << "ID klienta: ";
            int clientId = readInt();
            cout << "Numer pokoju: ";
            int number = readInt();
            DateTime startDate = readDate("Data przyjazdu (rrrr-mm-dd): ");
            DateTime endDate = readDate("Data wyjazdu (rrrr-mm-dd): ");
            if (clients.findById(clientId) == NULL) {
                cout << "Nie ma takiego klienta" << endl;
            } else if (rooms.findByNumber(number) == NULL) {
                cout << "Nie ma takiego pokoju" << endl;
            } else if (!(startDate < endDate)) {
                cout << "Data wyjazdu musi byc pozniejsza niz przyjazdu" << endl;
            } else if (rooms.addReservation(number, clientId, startDate, endDate)) {
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
            } else if (!(startDate < endDate)) {
                cout << "Data wyjazdu musi byc pozniejsza niz przyjazdu" << endl;
            } else if (rooms.checkAvailability(number, startDate, endDate)) {
                cout << "Pokoj jest dostepny" << endl;
            } else {
                cout << "Pokoj jest zajety w tym terminie" << endl;
            }
        } else if (choice == 10) {
            cout << "ID klienta: ";
            int clientId = readInt();
            if (clients.findById(clientId) == NULL) {
                cout << "Nie ma takiego klienta" << endl;
            } else {
                rooms.showReservationsForClient(clientId);
            }
        } else if (choice == 11) {
            cout << "ID klienta: ";
            int id = readInt();
            string name, surname, phone;
            cout << "Nowe imie: ";
            cin >> name;
            cout << "Nowe nazwisko: ";
            cin >> surname;
            cout << "Nowy telefon (9 cyfr): ";
            cin >> phone;
            if (clients.update(id, name, surname, phone)) {
                cout << "Zmieniono dane klienta" << endl;
            } else {
                cout << "Blad: nie ma klienta albo dane sa niepoprawne" << endl;
            }
        } else if (choice == 12) {
            cout << "ID klienta: ";
            int id = readInt();
            if (rooms.hasReservationsForClient(id)) {
                cout << "Nie mozna usunac klienta z rezerwacjami" << endl;
            } else if (clients.remove(id)) {
                cout << "Usunieto klienta" << endl;
            } else {
                cout << "Nie ma takiego klienta" << endl;
            }
        } else if (choice == 8) {
            if (saveState(clients, rooms)) {
                cout << "Zapisano stan aplikacji w pliku stan_aplikacji.txt" << endl;
            } else {
                cout << "Blad zapisu stanu aplikacji" << endl;
            }
        } else if (choice == 9) {
            if (loadState(clients, rooms)) {
                cout << "Wczytano stan aplikacji z pliku stan_aplikacji.txt" << endl;
            } else {
                cout << "Blad odczytu stanu aplikacji; obecny stan pozostaje bez zmian" << endl;
            }
        } else if (choice == 13) {
            cout << "Numer pokoju: ";
            int number = readInt();
            cout << "Nowa liczba lozek: ";
            int beds = readInt();
            cout << "Nowa cena za noc: ";
            double price = readDouble();
            if (rooms.update(number, beds, price)) {
                cout << "Zmieniono pokoj" << endl;
            } else {
                cout << "Blad: nie ma pokoju albo dane sa niepoprawne" << endl;
            }
        } else if (choice == 14) {
            cout << "Numer pokoju: ";
            int number = readInt();
            if (rooms.remove(number)) {
                cout << "Usunieto pokoj" << endl;
            } else {
                cout << "Nie mozna usunac pokoju z rezerwacjami albo pokoj nie istnieje" << endl;
            }
        } else if (choice != 0) {
            cout << "Nie ma takiej opcji" << endl;
        }
        if (choice != 0) {
            waitForEnter();
        }
    }

    cout << "Koniec programu" << endl;
    return 0;
}
