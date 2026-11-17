#include "Client.h"
#include <iostream>
using namespace std;

Client::Client(int id, string name, string surname, string phone) {
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->phone = phone;
}

int Client::getId() {
    return id;
}

string Client::getName() {
    return name;
}

string Client::getSurname() {
    return surname;
}

string Client::getPhone() {
    return phone;
}

void Client::show() {
    cout << "[" << id << "] " << name << " " << surname << ", tel. " << phone << endl;
}
