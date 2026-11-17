#include "ClientList.h"
#include <iostream>
using namespace std;

ClientList::ClientList() {
    nextId = 1;
}

bool ClientList::isPhoneCorrect(string phone) {
    if (phone.length() != 9) {
        return false;
    }
    for (int i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i].getPhone() == phone) {
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

Client* ClientList::findById(int id) {
    for (int i = 0; i < clients.size(); i++) {
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
    for (int i = 0; i < clients.size(); i++) {
        clients[i].show();
    }
}

int ClientList::count() {
    return clients.size();
}
