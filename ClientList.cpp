#include "ClientList.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

ClientList::ClientList() {
    nextId = 1;
}

bool ClientList::isPhoneCorrect(string phone, int ignoredId) {
    if (phone.length() != 9) {
        return false;
    }
    for (size_t i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].getId() != ignoredId && clients[i].getPhone() == phone) {
            return false;
        }
    }
    return true;
}

bool ClientList::add(string name, string surname, string phone) {
    if (name == "" || surname == "") {
        return false;
    }
    if (!isPhoneCorrect(phone)) {
        return false;
    }
    clients.push_back(Client(nextId, name, surname, phone));
    nextId++;
    return true;
}

bool ClientList::update(int id, string name, string surname, string phone) {
    Client* client = findById(id);
    if (client == NULL || name.empty() || surname.empty() ||
        !isPhoneCorrect(phone, id)) {
        return false;
    }
    client->setName(name);
    client->setSurname(surname);
    client->setPhone(phone);
    return true;
}

bool ClientList::remove(int id) {
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].getId() == id) {
            clients.erase(clients.begin() + i);
            return true;
        }
    }
    return false;
}

Client* ClientList::findById(int id) {
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].getId() == id) {
            return &clients[i];
        }
    }
    return NULL;
}

void ClientList::showAll() {
    if (clients.size() == 0) {
        cout << "Brak klientow" << endl;
        return;
    }
    for (size_t i = 0; i < clients.size(); i++) {
        const Entity* entity = &clients[i];
        entity->show();
    }
}

int ClientList::count() {
    return clients.size();
}

bool ClientList::save(ostream& output) {
    output << clients.size() << endl;
    for (size_t i = 0; i < clients.size(); i++) {
        output << clients[i].getId() << " "
               << clients[i].getName() << " "
               << clients[i].getSurname() << " "
               << clients[i].getPhone() << endl;
    }
    return output.good();
}

bool ClientList::load(istream& input) {
    int numberOfClients;
    if (!(input >> numberOfClients) || numberOfClients < 0) {
        return false;
    }

    ClientList loadedClients;
    int previousId = 0;
    for (int i = 0; i < numberOfClients; i++) {
        int id;
        string name, surname, phone;
        if (!(input >> id >> name >> surname >> phone) ||
            id <= previousId ||
            id == numeric_limits<int>::max() ||
            name.empty() ||
            surname.empty() ||
            !loadedClients.isPhoneCorrect(phone)) {
            return false;
        }
        try {
            loadedClients.clients.push_back(Client(id, name, surname, phone));
        } catch (const invalid_argument&) {
            return false;
        }
        previousId = id;
    }

    loadedClients.nextId = previousId + 1;
    *this = loadedClients;
    return true;
}
