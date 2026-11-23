#include "Client.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Client::Client() : Entity(), name(""), surname(""), phone("")
{
}

Client::Client(int id, string name, string surname, string phone)
    : Entity(id), name(""), surname(""), phone("")
{
    setName(name);
    setSurname(surname);
    setPhone(phone);
}

string Client::getName() const {
    return name;
}

string Client::getSurname() const {
    return surname;
}

string Client::getPhone() const {
    return phone;
}

void Client::setName(string name) {
    if (name.empty()) {
        throw invalid_argument("Imie nie moze byc puste");
    }
    this->name = name;
}

void Client::setSurname(string surname) {
    if (surname.empty()) {
        throw invalid_argument("Nazwisko nie moze byc puste");
    }
    this->surname = surname;
}

void Client::setPhone(string phone) {
    if (phone.length() != 9) {
        throw invalid_argument("Telefon musi miec 9 cyfr");
    }
    for (size_t i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            throw invalid_argument("Telefon moze zawierac tylko cyfry");
        }
    }
    this->phone = phone;
}

void Client::show() const {
    cout << "[" << getId() << "] " << name << " " << surname << ", tel. " << phone << endl;
}
