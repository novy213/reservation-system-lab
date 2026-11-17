#ifndef CLIENT_H
#define CLIENT_H

#include <string>
using namespace std;

class Client {
private:
    int id;
    string name;
    string surname;
    string phone;

public:
    Client(int id, string name, string surname, string phone);
    int getId();
    string getName();
    string getSurname();
    string getPhone();
    void show();
};

#endif
