#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "Entity.h"
using namespace std;

class Client : public Entity {
private:
    string name;
    string surname;
    string phone;

public:
    Client();
    Client(int id, string name, string surname, string phone);
    string getName() const;
    string getSurname() const;
    string getPhone() const;
    void setName(string name);
    void setSurname(string surname);
    void setPhone(string phone);
    void show() const override;
};

#endif
