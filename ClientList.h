#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <vector>
#include <string>
#include "Client.h"
using namespace std;

class ClientList {
private:
    vector<Client> clients;
    int nextId;
    bool isPhoneCorrect(string phone);

public:
    ClientList();
    bool add(string name, string surname, string phone);
    Client* findById(int id);
    void showAll();
    int count();
};

#endif
