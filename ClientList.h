#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <vector>
#include <string>
#include <iosfwd>
#include "Client.h"
using namespace std;

class ClientList {
private:
    vector<Client> clients;
    int nextId;
    bool isPhoneCorrect(string phone, int ignoredId = 0);

public:
    ClientList();
    bool add(string name, string surname, string phone);
    bool update(int id, string name, string surname, string phone);
    bool remove(int id);
    Client* findById(int id);
    void showAll();
    int count();
    bool save(ostream& output);
    bool load(istream& input);
};

#endif
